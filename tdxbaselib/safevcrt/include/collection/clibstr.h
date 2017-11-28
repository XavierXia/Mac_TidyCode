//////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2007 - All Rights Reserved
//  模块名称: str
//  创建日期: 2004/05/26
//  代码编写: zhanglijun
//  功能说明: 字符串处理类
//  引用示例: 
//  修改记录:
//////////////////////////////////////////////////////////////////////////
#ifndef __CLIB_STR__H__
#define __CLIB_STR__H__

// 外部依赖类
class CXMLProfileSection;



// 字符串数据
struct COLLECTION_IMP TClibStrData
{	LONG nRefs;										// 引用记数(应用数据不修改时不重新分配缓冲区)
	int nDataLength;        						// 数据长度(包括'\0')
	int nAllocLength;       						// 数据分配的长度
	CHAR* data() { return (CHAR*)(this+1); }		// CHAR data[nAllocLength]
};

// 字符串类
class TClibStr;
class COLLECTION_IMP TClibStr
{
public:
	// 构造函数
	TClibStr();												// 构造空串
	TClibStr(const TClibStr& stringSrc);					// 通过复制构造字符串
	TClibStr(CHAR ch,int nRepeat=1);						// 通过重复填充构造字符串
	TClibStr(LPCSTR lpsz);									// 通过MULITIBYTE字符串(含'\0')构造
	TClibStr(LPCWSTR lpsz);									// 通过UNICODE字符串(含'\0')构造
	TClibStr(LPCSTR lpch,int nLength);						// 通过MULITIBYTE字符串构造(指定长度)
	TClibStr(LPCWSTR lpch,int nLength);						// 通过UNICODE字符串构造(指定长度)
	TClibStr(const unsigned char* psz);						// 通过BYTE序列(含'\0')构造
	~TClibStr();

	// 数据和基本操作
	int GetLength() const;									// 获取字符串长度
	int GetAllocLength() const;								// 获取字符串已分配缓冲区长度
	BOOL IsEmpty() const;									// 判断字符串是否为空
	void Empty();											// 清空字符串
	CHAR GetAt(int nIndex) const;							// 取第nIndex个字符
	CHAR operator[](int nIndex) const;						// 取第nIndex个字符
	void SetAt(int nIndex,CHAR ch);							// 设置第nIndex个字符
	operator LPCSTR() const;								// 取字符串内容指针

	// 重载赋值操作
	const TClibStr& operator=(const TClibStr& stringSrc);	// 通过TClibStr赋值
	const TClibStr& operator=(CHAR ch);						// 通过字符赋值
	const TClibStr& operator=(LPCSTR lpsz);					// 通过MULTIBYTE赋值
	const TClibStr& operator=(LPCWSTR lpsz);				// 通过UNICODE赋值
	const TClibStr& operator=(const unsigned char* psz);	// 通过BYTE序列(含'\0')赋值

	// 追加操作
	const TClibStr& operator+=(const TClibStr& string);
	const TClibStr& operator+=(CHAR ch);
	const TClibStr& operator+=(LPCSTR lpsz);

	// 字符串合并操作
	friend SAFEVCRT_IMP TClibStr CLIBAPI operator+(const TClibStr& string1,const TClibStr& string2);
	friend SAFEVCRT_IMP TClibStr CLIBAPI operator+(const TClibStr& string,CHAR ch);
	friend SAFEVCRT_IMP TClibStr CLIBAPI operator+(CHAR ch,const TClibStr& string);
	friend SAFEVCRT_IMP TClibStr CLIBAPI operator+(const TClibStr& string,LPCSTR lpsz);
	friend SAFEVCRT_IMP TClibStr CLIBAPI operator+(LPCSTR lpsz,const TClibStr& string);

	// 字符串比较
	int Compare(LPCSTR lpsz) const;							// 直接比较
	int CompareNoCase(LPCSTR lpsz) const;					// 忽略大小写比较

	// 子串操作
	TClibStr Mid(int nFirst,int nCount) const;
	TClibStr Mid(int nFirst) const;
	TClibStr Left(int nCount) const;
	TClibStr Right(int nCount) const;
	TClibStr SpanIncluding(LPCSTR lpszCharSet) const;		// 获取只包含指定字符集的子串
	TClibStr SpanExcluding(LPCSTR lpszCharSet) const;		// 获取不包含指定字符集的子串
	BOOL SpanAndShift(CHAR chSplitter,TClibStr& strSub);
	BOOL SpanAndShift(LPCSTR pszSplitter,TClibStr& strSub);

	// 大小写转换
	void MakeUpper();
	void MakeLower();
	void MakeReverse();

	// 整理操作
	void TrimRight();
	void TrimLeft();
	void TrimAll() { TrimRight(); TrimLeft(); }

	// 有条件整理操作
	void TrimRight(CHAR chTarget);
	void TrimRight(LPCSTR lpszTargets);
	void TrimLeft(CHAR chTarget);
	void TrimLeft(LPCSTR lpszTargets);

	// 高级操作
	int Delete(int nIndex,int nCount=1);
	int Insert(int nIndex,CHAR ch);
	int Insert(int nIndex,LPCSTR pstr);
	int Replace(CHAR chOld,CHAR chNew);
	int Replace(LPCSTR lpszOld,LPCSTR lpszNew);
	int Remove(CHAR chRemove);
		
	// 字符串查找
	int Find(CHAR ch) const;
	int Find(CHAR ch,int nStart) const;
	int FindOneOf(LPCSTR lpszCharSet) const;
	int ReverseFind(CHAR ch) const;
	int Find(LPCSTR lpszSub) const;
	int Find(LPCSTR lpszSub,int nStart) const;

	// 格式化
	void CLIBCDECL Format(LPCTSTR pszFormat,...);
	void FormatV(LPCTSTR pszFormat,va_list argList);


	// OLE支持
	#ifdef PLATFORM_WINDOWS
		BSTR AllocSysString() const;
		BSTR SetSysString(BSTR* pbstr) const;
	#endif // PLATFORM_WINDOWS

	// 缓冲区操作
	LPSTR GetBuffer(int nMinBufLength);
	void ReleaseBuffer(int nNewLength=-1);
	LPSTR GetBufferSetLength(int nNewLength);
	void FreeExtra();
	LPSTR LockBuffer();
	void UnlockBuffer();
protected:
	LPSTR m_pchData;
	TClibStrData* GetData() const;
	void Init();
	void AllocCopy(TClibStr& dest,int nCopyLen,int nCopyIndex,int nExtraLen) const;
	void AllocBuffer(int nLen);
	void AssignCopy(int nSrcLen,LPCSTR lpszSrcData);
	void ConcatCopy(int nSrc1Len,LPCSTR lpszSrc1Data,int nSrc2Len,LPCSTR lpszSrc2Data);
	void ConcatInPlace(int nSrcLen,LPCSTR lpszSrcData);
	void CopyBeforeWrite();
	void AllocBeforeWrite(int nLen);
	void Release();
	static void PASCAL Release(TClibStrData* pData);
	static int PASCAL SafeStrlen(LPCSTR lpsz);
	static void CLIBFASTCALL FreeData(TClibStrData* pData);
};

// 比较操作重载
COLLECTION_IMP bool CLIBAPI operator==(const TClibStr& s1,const TClibStr& s2);
COLLECTION_IMP bool CLIBAPI operator==(const TClibStr& s1,LPCSTR s2);
COLLECTION_IMP bool CLIBAPI operator==(LPCSTR s1,const TClibStr& s2);
COLLECTION_IMP bool CLIBAPI operator!=(const TClibStr& s1,const TClibStr& s2);
COLLECTION_IMP bool CLIBAPI operator!=(const TClibStr& s1,LPCSTR s2);
COLLECTION_IMP bool CLIBAPI operator!=(LPCSTR s1,const TClibStr& s2);
COLLECTION_IMP bool CLIBAPI operator<(const TClibStr& s1,const TClibStr& s2);
COLLECTION_IMP bool CLIBAPI operator<(const TClibStr& s1,LPCSTR s2);
COLLECTION_IMP bool CLIBAPI operator<(LPCSTR s1,const TClibStr& s2);
COLLECTION_IMP bool CLIBAPI operator>(const TClibStr& s1,const TClibStr& s2);
COLLECTION_IMP bool CLIBAPI operator>(const TClibStr& s1,LPCSTR s2);
COLLECTION_IMP bool CLIBAPI operator>(LPCSTR s1,const TClibStr& s2);
COLLECTION_IMP bool CLIBAPI operator<=(const TClibStr& s1,const TClibStr& s2);
COLLECTION_IMP bool CLIBAPI operator<=(const TClibStr& s1,LPCSTR s2);
COLLECTION_IMP bool CLIBAPI operator<=(LPCSTR s1,const TClibStr& s2);
COLLECTION_IMP bool CLIBAPI operator>=(const TClibStr& s1,const TClibStr& s2);
COLLECTION_IMP bool CLIBAPI operator>=(const TClibStr& s1,LPCSTR s2);
COLLECTION_IMP bool CLIBAPI operator>=(LPCSTR s1,const TClibStr& s2);

// 转换操作和空串处理
COLLECTION_IMP int CLIBCDECL clibwcstombsz(char* mbstr,const wchar_t* wcstr,size_t count);
COLLECTION_IMP int CLIBCDECL clibmbstowcsz(wchar_t* wcstr,const char* mbstr,size_t count);
COLLECTION_IMP const TClibStr& CLIBAPI clibGetEmptyString();
#define clibEmptyString clibGetEmptyString()


// 环境清空处理
COLLECTION_IMP void clibFreeEnvs();






// 常用属性操作
CLIB_INLINE int TClibStr::GetLength() const
	{ return GetData()->nDataLength; }
CLIB_INLINE int TClibStr::GetAllocLength() const
	{ return GetData()->nAllocLength; }
CLIB_INLINE BOOL TClibStr::IsEmpty() const
	{ return GetData()->nDataLength==0; }
CLIB_INLINE CHAR TClibStr::GetAt(int nIndex) const
	{	CLIBASSERT(nIndex>=0);
		CLIBASSERT(nIndex<GetData()->nDataLength);
		return m_pchData[nIndex];
	}
CLIB_INLINE CHAR TClibStr::operator[](int nIndex) const
	{	CLIBASSERT(nIndex>=0);
		CLIBASSERT(nIndex<GetData()->nDataLength);
		return m_pchData[nIndex];
	}
CLIB_INLINE TClibStr::operator LPCSTR() const
	{ return m_pchData; }

// 取缓冲区、串初始化、取串长度
CLIB_INLINE TClibStrData* TClibStr::GetData() const
	{ CLIBASSERT(m_pchData!=NULL); return ((TClibStrData*)m_pchData)-1; }
CLIB_INLINE void TClibStr::Init()
	{ m_pchData=clibEmptyString.m_pchData; }
CLIB_INLINE int PASCAL TClibStr::SafeStrlen(LPCSTR lpsz)
	{ return (int)((lpsz==NULL) ? 0 : lstrlenA(lpsz)); }

// 比较操作
CLIB_INLINE int TClibStr::Compare(LPCSTR lpsz) const
	{ return strcmp(m_pchData,lpsz); }
CLIB_INLINE int TClibStr::CompareNoCase(LPCSTR lpsz) const
	{ return stricmp(m_pchData,lpsz); }

// 比较操作重载(实现)
COLLECTION_IMP CLIB_INLINE bool CLIBAPI operator==(const TClibStr& s1,const TClibStr& s2)
	{ return s1.Compare(s2)==0; }
COLLECTION_IMP CLIB_INLINE bool CLIBAPI operator==(const TClibStr& s1,LPCSTR s2)
	{ return s1.Compare(s2)==0; }
COLLECTION_IMP CLIB_INLINE bool CLIBAPI operator==(LPCSTR s1,const TClibStr& s2)
	{ return s2.Compare(s1)==0; }
COLLECTION_IMP CLIB_INLINE bool CLIBAPI operator!=(const TClibStr& s1,const TClibStr& s2)
	{ return s1.Compare(s2)!=0; }
COLLECTION_IMP CLIB_INLINE bool CLIBAPI operator!=(const TClibStr& s1,LPCSTR s2)
	{ return s1.Compare(s2)!=0; }
COLLECTION_IMP CLIB_INLINE bool CLIBAPI operator!=(LPCSTR s1,const TClibStr& s2)
	{ return s2.Compare(s1)!=0; }
COLLECTION_IMP CLIB_INLINE bool CLIBAPI operator<(const TClibStr& s1,const TClibStr& s2)
	{ return s1.Compare(s2)<0; }
COLLECTION_IMP CLIB_INLINE bool CLIBAPI operator<(const TClibStr& s1,LPCSTR s2)
	{ return s1.Compare(s2)<0; }
COLLECTION_IMP CLIB_INLINE bool CLIBAPI operator<(LPCSTR s1,const TClibStr& s2)
	{ return s2.Compare(s1)>0; }
COLLECTION_IMP CLIB_INLINE bool CLIBAPI operator>(const TClibStr& s1,const TClibStr& s2)
	{ return s1.Compare(s2)>0; }
COLLECTION_IMP CLIB_INLINE bool CLIBAPI operator>(const TClibStr& s1,LPCSTR s2)
	{ return s1.Compare(s2)>0; }
COLLECTION_IMP CLIB_INLINE bool CLIBAPI operator>(LPCSTR s1,const TClibStr& s2)
	{ return s2.Compare(s1)<0; }
COLLECTION_IMP CLIB_INLINE bool CLIBAPI operator<=(const TClibStr& s1,const TClibStr& s2)
	{ return s1.Compare(s2)<=0; }
COLLECTION_IMP CLIB_INLINE bool CLIBAPI operator<=(const TClibStr& s1,LPCSTR s2)
	{ return s1.Compare(s2)<=0; }
COLLECTION_IMP CLIB_INLINE bool CLIBAPI operator<=(LPCSTR s1,const TClibStr& s2)
	{ return s2.Compare(s1)>=0; }
COLLECTION_IMP CLIB_INLINE bool CLIBAPI operator>=(const TClibStr& s1,const TClibStr& s2)
	{ return s1.Compare(s2)>=0; }
COLLECTION_IMP CLIB_INLINE bool CLIBAPI operator>=(const TClibStr& s1,LPCSTR s2)
	{ return s1.Compare(s2)>=0; }
COLLECTION_IMP CLIB_INLINE bool CLIBAPI operator>=(LPCSTR s1,const TClibStr& s2)
	{ return s2.Compare(s1)<=0; }


//////////////////////////////////////////////////////////////////////////
// 适应模版类的辅助函数
COLLECTION_IMP void CLIBAPI CollConstructElements(UNALIGNED TClibStr* pElements,int nCount);
COLLECTION_IMP void CLIBAPI CollDestructElements(UNALIGNED TClibStr* pElements,int nCount);
COLLECTION_IMP void CLIBAPI CollCopyElements(UNALIGNED TClibStr* pDest,const UNALIGNED TClibStr* pSrc,int nCount);
COLLECTION_IMP void CLIBAPI CollCopyElements(UNALIGNED TClibStr* pDest,const UNALIGNED LPCSTR* pSrc,int nCount);
COLLECTION_IMP BOOL CLIBAPI CollCompareElements(const UNALIGNED TClibStr* pElement1,const UNALIGNED TClibStr* pElement2);
COLLECTION_IMP BOOL CLIBAPI CollCompareElements(const UNALIGNED TClibStr* pElement1,const UNALIGNED LPCSTR* pElement2);
COLLECTION_IMP BOOL CLIBAPI CollDoDataEPXElements(UNALIGNED TClibStr* pElement,CXMLProfileSection* pPX,LPCSTR pszName);
COLLECTION_IMP UINT CLIBAPI GenHashKey(TClibStr& Key,UINT nKeyOffset);

#define TClibStrArray TArray<TClibStr,LPCSTR>
#define TClibStrList TList<TClibStr,LPCSTR>

#endif
