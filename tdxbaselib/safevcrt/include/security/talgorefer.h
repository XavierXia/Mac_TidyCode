#ifndef	__TALGO_REREF__H__
#define __TALGO_REREF__H__
#if _MSC_VER > 1000
#pragma once
#endif

// 移位算法
template <class T> inline T rotl(T x, unsigned int y)
{
	return ((x<<y) | (x>>(size_of(T)*8-y)));
}

template <class T> inline T rotr(T x, unsigned int y)
{
	return ((x>>y) | (x<<(size_of(T)*8-y)));
}

template<> inline unsigned short rotl<unsigned short>(unsigned short x, unsigned int y)
{
	return (unsigned short)((x<<y) | (x>>(16-y)));
}

template<> inline unsigned short rotr<unsigned short>(unsigned short x, unsigned int y)
{
	return (unsigned short)((x>>y) | (x<<(16-y)));
}

template<> inline unsigned long rotl<unsigned long>(unsigned long x, unsigned int y)
{
	return _lrotl(x, y);
}

template<> inline unsigned long rotr<unsigned long>(unsigned long x, unsigned int y)
{
	return _lrotr(x, y);
}


// 数据块操作
#define SecAlloc(type, number) (new type[(number)])
#define SecFree(ptr, number) (delete [] (ptr))
template <class T> struct TSecBlock
{
	TSecBlock(unsigned int size=0)
		: size(size) {ptr = SecAlloc(T, size);}
	TSecBlock(const TSecBlock<T> &t)
		: size(t.size) {ptr = SecAlloc(T, size); CopyFrom(t);}
	TSecBlock(const T *t, unsigned int size)
		: size(size) {ptr = SecAlloc(T, size); memcpy(ptr, t, size*size_of(T));}
	~TSecBlock()
		{SecFree(ptr, size);}

#if defined(__GNUC__) || defined(__BCPLUSPLUS__)
	operator const void *() const
		{return ptr;}
	operator void *()
		{return ptr;}
#endif

	operator const T *() const
		{return ptr;}
	operator T *()
		{return ptr;}

#ifndef _MSC_VER
	T *operator +(int offset)
		{return ptr+offset;}
	const T *operator +(int offset) const
		{return ptr+offset;}
	T& operator[](int index)
		{ CLIBASSERT(index<(int)size); return ptr[index];}
	const T& operator[](int index) const
		{CLIBASSERT(index<size); return ptr[index];}
#endif

	const T* Begin() const
		{return ptr;}
	T* Begin()
		{return ptr;}
	const T* End() const
		{return ptr+size;}
	T* End()
		{return ptr+size;}

	void CopyFrom(const TSecBlock<T> &t)
	{
		New(t.size);
		memcpy(ptr, t.ptr, size*size_of(T));
	}

	TSecBlock& operator=(const TSecBlock<T> &t)
	{
		CopyFrom(t);
		return *this;
	}

	bool operator==(const TSecBlock<T> &t) const
	{
		return size == t.size && memcmp(ptr, t.ptr, size*size_of(T)) == 0;
	}

	void New(unsigned int newSize)
	{
		if (newSize != size)
		{
			T *newPtr = SecAlloc(T, newSize);
			SecFree(ptr, size);
			ptr = newPtr;
			size = newSize;
		}
	}

	void CleanNew(unsigned int newSize)
	{
		if (newSize != size)
		{
			T *newPtr = SecAlloc(T, newSize);
			SecFree(ptr, size);
			ptr = newPtr;
			size = newSize;
		}
		memset(ptr, 0, size*size_of(T));
	}

	void Grow(unsigned int newSize)
	{
		if (newSize > size)
		{
			T *newPtr = SecAlloc(T, newSize);
			memcpy(newPtr, ptr, size*size_of(T));
			SecFree(ptr, size);
			ptr = newPtr;
			size = newSize;
		}
	}

	void CleanGrow(unsigned int newSize)
	{
		if (newSize > size)
		{
			T *newPtr = SecAlloc(T, newSize);
			memcpy(newPtr, ptr, size*size_of(T));
			memset(newPtr+size, 0, (newSize-size)*size_of(T));
			SecFree(ptr, size);
			ptr = newPtr;
			size = newSize;
		}
	}

	void Resize(unsigned int newSize)
	{
		if (newSize != size)
		{
			T *newPtr = SecAlloc(T, newSize);
			memcpy(newPtr, ptr, min_of(newSize, size)*size_of(T));
			SecFree(ptr, size);
			ptr = newPtr;
			size = newSize;
		}
	}

	unsigned int size;
	T *ptr;
};

typedef TSecBlock<byte> SecByteBlock;
inline word32 byteReverse(word32 value)
{
#ifdef FAST_ROTATE
	// 5 instructions with rotate instruction, 9 without
	return (rotr(value, 8U) & 0xff00ff00) | (rotl(value, 8U) & 0x00ff00ff);
#else
	// 6 instructions with rotate instruction, 8 without
	value = ((value & 0xFF00FF00) >> 8) | ((value & 0x00FF00FF) << 8);
	return rotl(value, 16U);
#endif
}

template <class T> void byteReverse(T *out, const T *in, unsigned int byteCount)
{
	if(byteCount%size_of(T) != 0) return;
	byteCount /= size_of(T);
	for (unsigned i=0; i<byteCount; i++)
		out[i] = byteReverse(in[i]);
}

#ifdef _MSC_VER
	#define ROTL(x,y) (_rotl((x), (unsigned int)(y)))
	#define ROTR(x,y) (_rotr((x), (unsigned int)(y)))
#else
	#define ROTL(x,y) (rotl((x), (unsigned int)(y) % (size_of(word32)*8)))
	#define ROTR(x,y) (rotr((x), (unsigned int)(y) % (size_of(word32)*8)))
#endif



#endif
