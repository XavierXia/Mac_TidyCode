#ifndef __MINI_ARCHIVE__H__
#define __MINI_ARCHIVE__H__
#include "../safevcrt.h"
#if defined(PLATFORM_WINDOWS)
#include <new.h>
#else
#include <new>
#endif // PLATFORM_WINDOWS

class CAnyFile;
class CArch;
template <class elemtype> class COurArray;


//////////////////////////////////////////////////////////////////////////
// 虚拟文件
class LITEFILEIO_IMP CAnyFile
{
public:
	virtual LONG GetLength() PURE;
	virtual BOOL Write(IN LPCVOID lpBuffer,IN LONG nLength) PURE;
	virtual BOOL Read(OUT LPVOID lpBuffer,IN LONG nLength) PURE;
	virtual BOOL Seek(IN LONG nTo,IN LONG nFlag) PURE;
	virtual LONG Tell() PURE;
	virtual BOOL SetLength(IN LONG nNewLength) PURE;
	virtual BOOL IsFileOpened() PURE;
public:
	BOOL SeekToBegin();
	BOOL SeekToEnd();
	BOOL SeekTo(IN LONG nTo);
	BOOL Rewind();
	BOOL SetEndOfFile();
	BOOL Printf(const char* lpszFmt,...);
};
#define Printf0(a)				Printf(a)
#define Printf1(a,b)			Printf(a,b)
#define Printf2(a,b,c)			Printf(a,b,c)
#define Printf3(a,b,c,d)		Printf(a,b,c,d)
#define Printf4(a,b,c,d,e)		Printf(a,b,c,d,e)
#define Printf5(a,b,c,d,e,f)	Printf(a,b,c,d,e,f)


//////////////////////////////////////////////////////////////////////////
// 包格式(允复制,强烈推荐使用引用)
class LITEFILEIO_IMP CArch
{
public:
	CArch(IN CAnyFile* pAnyFile,IN BOOL bBeToLoad);
	virtual~CArch();
	BOOL IsLoading() const;
	BOOL IsStoring() const;
	BOOL Write(IN LPCVOID lpBuffer,IN LONG nLength);
	BOOL Read(OUT LPVOID lpBuffer,IN LONG nLength);
	BOOL SetBeToLoad(IN BOOL bBeToLoad);
public:
	CArch& operator<<(BYTE by);
	CArch& operator<<(WORD w);
	#if defined(_COMPILE_BY_MSC_)
		CArch& operator<<(DWORD dw);
		CArch& operator<<(LONG l);
	#endif
	CArch& operator<<(float f);
	CArch& operator<<(double d);
	
	CArch& operator<<(int i);
	CArch& operator<<(short w);
	CArch& operator<<(char ch);
	CArch& operator<<(unsigned u);
	
	CArch& operator>>(BYTE& by);
	CArch& operator>>(WORD& w);
	#if defined(_COMPILE_BY_MSC_)
		CArch& operator>>(DWORD& dw);
		CArch& operator>>(LONG& l);
	#endif
	CArch& operator>>(float& f);
	CArch& operator>>(double& d);
	
	CArch& operator>>(int& i);
	CArch& operator>>(short& w);
	CArch& operator>>(char& ch);
	CArch& operator>>(unsigned& u);

protected:
	CAnyFile* m_pAnyFile;
	BOOL m_bBeToLoad;
};




//////////////////////////////////////////////////////////////////////////
// 在函数中使用数组作为局部变量
// 1.不能在栈中开大数组,栈使用过大会导致系统堆栈溢出
// 2.使用动态分配,不能象堆栈中的变量一样自动释放
// 这里试图在堆中开辟大数组
template <class elemtype>
class COurArray
{
public:
	COurArray()
	{	m_nElemCount=0;
		m_pElems=NULL;
	}
	COurArray(LONG nElemsCount)
	{	m_nElemCount=0;
		m_pElems=NULL;
		SetCount(nElemsCount);
	}
	virtual~COurArray()
	{	SetCount(0);
	}
	VOID SetCount(LONG nCount)
	{	elemtype* pNewElems=NULL;
		LONG nNewElemCount=0;
		if(nCount>0)
		{	nNewElemCount=nCount;
			pNewElems=new elemtype[nNewElemCount];
			LONG nCopyCount=m_nElemCount;
			if(nCopyCount>nNewElemCount) nCopyCount=nNewElemCount;
			for(int i=0; i<nCopyCount; i++)
				pNewElems[i]=m_pElems[i];
		}
		// 释放原有数据
		if(m_pElems) delete[] m_pElems;
		// 保存新数据
		m_pElems=pNewElems;
		m_nElemCount=nNewElemCount;
	}
	LONG GetCount() const
	{	return m_nElemCount;
	}
	BOOL SetElem(LONG nIndex,elemtype& elem)
	{	m_pElems[nIndex]=elem;
		return TRUE;
	}
	BOOL AddElem(IN elemtype& elem)
	{	SetCount(GetCount()+1);
		m_pElems[GetCount()-1]=elem;
		return TRUE;
	}
	BOOL DeleteAt(IN LONG nIndex)
	{	if(nIndex<0||nIndex>=m_nElemCount)
			return FALSE;
		if(m_nElemCount==1)
		{	SetCount(0);
			return TRUE;
		}
		for(LONG nMov=nIndex; nMov<m_nElemCount-1; nMov++)
			(*this)[nMov]=(*this)[nMov+1];
		SetCount(m_nElemCount-1);
		return TRUE;
	}
	BOOL InsertAt(IN LONG nIndex,IN elemtype& elem)
	{	if(nIndex<0||nIndex>m_nElemCount)
			return FALSE;
		SetCount(GetCount()+1);
		for(int nMov=GetCount()-1; nMov>nIndex; nMov--)
			(*this)[nMov]=(*this)[nMov-1];
		(*this)[nIndex]=elem;
		return TRUE;
	}
	BOOL Serialize(CArch& ar)
	{	if(ar.IsLoading())
		{	LONG nCount=0;
			if(!ar.Read(&nCount,size_of(nCount))) return FALSE;
			SetCount(nCount);
			for(int i=0; i<m_nElemCount; i++)
			{	if(m_pElems[i].Serialize(ar)) continue;
				return FALSE;
			}
		}
		else
		{	LONG nCount=GetCount();
			if(!ar.Write(&nCount,size_of(nCount))) return FALSE;
			SetCount(nCount);
			for(int i=0; i<m_nElemCount; i++)
			{	if(m_pElems[i].Serialize(ar)) continue;
				return FALSE;
			}
		}
		return TRUE;
	}
	operator elemtype*() const
	{	return m_pElems;
	}
	const COurArray& operator= (IN COurArray& OurArray)
	{	SetCount(OurArray.GetCount());
		for(LONG i=0; i<GetCount(); i++)
			(*this)[i]=OurArray[i];
		return (*this);
	}
protected:
	elemtype* m_pElems;
	LONG m_nElemCount;
};

class COurString
{
public:
	COurString();
	COurString(LPCTSTR lpszText);
	~COurString();
	void SetString(LPCSTR lpszText);
	BOOL FromFile(char* lpszFileName);
	BOOL ToFile(char* lpszFileName);
	BOOL Serialize(CArch& ar);
	operator const CHAR*() const;
	const COurString& operator=(IN COurString& OurString);
	friend bool operator==(const COurString& s1,const COurString& s2);
	friend bool operator==(const COurString& s1,LPCTSTR s2);
	friend bool operator==(LPCTSTR s1,const COurString& s2);
	friend bool operator!=(const COurString& s1,const COurString& s2);
	friend bool operator!=(const COurString& s1,LPCTSTR s2);
	friend bool operator!=(LPCTSTR s1,const COurString& s2);
	friend bool operator<(const COurString& s1,const COurString& s2);
	friend bool operator<(const COurString& s1,LPCTSTR s2);
	friend bool operator<(LPCTSTR s1,const COurString& s2);
	friend bool operator>(const COurString& s1,const COurString& s2);
	friend bool operator>(const COurString& s1,LPCTSTR s2);
	friend bool operator>(LPCTSTR s1,const COurString& s2);
	friend bool operator<=(const COurString& s1,const COurString& s2);
	friend bool operator<=(const COurString& s1,LPCTSTR s2);
	friend bool operator<=(LPCTSTR s1,const COurString& s2);
	friend bool operator>=(const COurString& s1,const COurString& s2);
	friend bool operator>=(const COurString& s1,LPCTSTR s2);
	friend bool operator>=(LPCTSTR s1,const COurString& s2);
protected:
	CHAR* m_lpString;
};

typedef COurArray<COurString> COurStringArray;


#endif // THIS_FILE


