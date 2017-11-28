//////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2007 - All Rights Reserved
//  ģ������: str
//  ��������: 2004/05/26
//  �����д: zhanglijun
//  ����˵��: �ַ���������
//  ����ʾ��: 
//  �޸ļ�¼:
//////////////////////////////////////////////////////////////////////////
#ifndef __CLIB_STR__H__
#define __CLIB_STR__H__

// �ⲿ������
class CXMLProfileSection;



// �ַ�������
struct COLLECTION_IMP TClibStrData
{	LONG nRefs;										// ���ü���(Ӧ�����ݲ��޸�ʱ�����·��仺����)
	int nDataLength;        						// ���ݳ���(����'\0')
	int nAllocLength;       						// ���ݷ���ĳ���
	CHAR* data() { return (CHAR*)(this+1); }		// CHAR data[nAllocLength]
};

// �ַ�����
class TClibStr;
class COLLECTION_IMP TClibStr
{
public:
	// ���캯��
	TClibStr();												// ����մ�
	TClibStr(const TClibStr& stringSrc);					// ͨ�����ƹ����ַ���
	TClibStr(CHAR ch,int nRepeat=1);						// ͨ���ظ���乹���ַ���
	TClibStr(LPCSTR lpsz);									// ͨ��MULITIBYTE�ַ���(��'\0')����
	TClibStr(LPCWSTR lpsz);									// ͨ��UNICODE�ַ���(��'\0')����
	TClibStr(LPCSTR lpch,int nLength);						// ͨ��MULITIBYTE�ַ�������(ָ������)
	TClibStr(LPCWSTR lpch,int nLength);						// ͨ��UNICODE�ַ�������(ָ������)
	TClibStr(const unsigned char* psz);						// ͨ��BYTE����(��'\0')����
	~TClibStr();

	// ���ݺͻ�������
	int GetLength() const;									// ��ȡ�ַ�������
	int GetAllocLength() const;								// ��ȡ�ַ����ѷ��仺��������
	BOOL IsEmpty() const;									// �ж��ַ����Ƿ�Ϊ��
	void Empty();											// ����ַ���
	CHAR GetAt(int nIndex) const;							// ȡ��nIndex���ַ�
	CHAR operator[](int nIndex) const;						// ȡ��nIndex���ַ�
	void SetAt(int nIndex,CHAR ch);							// ���õ�nIndex���ַ�
	operator LPCSTR() const;								// ȡ�ַ�������ָ��

	// ���ظ�ֵ����
	const TClibStr& operator=(const TClibStr& stringSrc);	// ͨ��TClibStr��ֵ
	const TClibStr& operator=(CHAR ch);						// ͨ���ַ���ֵ
	const TClibStr& operator=(LPCSTR lpsz);					// ͨ��MULTIBYTE��ֵ
	const TClibStr& operator=(LPCWSTR lpsz);				// ͨ��UNICODE��ֵ
	const TClibStr& operator=(const unsigned char* psz);	// ͨ��BYTE����(��'\0')��ֵ

	// ׷�Ӳ���
	const TClibStr& operator+=(const TClibStr& string);
	const TClibStr& operator+=(CHAR ch);
	const TClibStr& operator+=(LPCSTR lpsz);

	// �ַ����ϲ�����
	friend SAFEVCRT_IMP TClibStr CLIBAPI operator+(const TClibStr& string1,const TClibStr& string2);
	friend SAFEVCRT_IMP TClibStr CLIBAPI operator+(const TClibStr& string,CHAR ch);
	friend SAFEVCRT_IMP TClibStr CLIBAPI operator+(CHAR ch,const TClibStr& string);
	friend SAFEVCRT_IMP TClibStr CLIBAPI operator+(const TClibStr& string,LPCSTR lpsz);
	friend SAFEVCRT_IMP TClibStr CLIBAPI operator+(LPCSTR lpsz,const TClibStr& string);

	// �ַ����Ƚ�
	int Compare(LPCSTR lpsz) const;							// ֱ�ӱȽ�
	int CompareNoCase(LPCSTR lpsz) const;					// ���Դ�Сд�Ƚ�

	// �Ӵ�����
	TClibStr Mid(int nFirst,int nCount) const;
	TClibStr Mid(int nFirst) const;
	TClibStr Left(int nCount) const;
	TClibStr Right(int nCount) const;
	TClibStr SpanIncluding(LPCSTR lpszCharSet) const;		// ��ȡֻ����ָ���ַ������Ӵ�
	TClibStr SpanExcluding(LPCSTR lpszCharSet) const;		// ��ȡ������ָ���ַ������Ӵ�
	BOOL SpanAndShift(CHAR chSplitter,TClibStr& strSub);
	BOOL SpanAndShift(LPCSTR pszSplitter,TClibStr& strSub);

	// ��Сдת��
	void MakeUpper();
	void MakeLower();
	void MakeReverse();

	// �������
	void TrimRight();
	void TrimLeft();
	void TrimAll() { TrimRight(); TrimLeft(); }

	// �������������
	void TrimRight(CHAR chTarget);
	void TrimRight(LPCSTR lpszTargets);
	void TrimLeft(CHAR chTarget);
	void TrimLeft(LPCSTR lpszTargets);

	// �߼�����
	int Delete(int nIndex,int nCount=1);
	int Insert(int nIndex,CHAR ch);
	int Insert(int nIndex,LPCSTR pstr);
	int Replace(CHAR chOld,CHAR chNew);
	int Replace(LPCSTR lpszOld,LPCSTR lpszNew);
	int Remove(CHAR chRemove);
		
	// �ַ�������
	int Find(CHAR ch) const;
	int Find(CHAR ch,int nStart) const;
	int FindOneOf(LPCSTR lpszCharSet) const;
	int ReverseFind(CHAR ch) const;
	int Find(LPCSTR lpszSub) const;
	int Find(LPCSTR lpszSub,int nStart) const;

	// ��ʽ��
	void CLIBCDECL Format(LPCTSTR pszFormat,...);
	void FormatV(LPCTSTR pszFormat,va_list argList);


	// OLE֧��
	#ifdef PLATFORM_WINDOWS
		BSTR AllocSysString() const;
		BSTR SetSysString(BSTR* pbstr) const;
	#endif // PLATFORM_WINDOWS

	// ����������
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

// �Ƚϲ�������
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

// ת�������Ϳմ�����
COLLECTION_IMP int CLIBCDECL clibwcstombsz(char* mbstr,const wchar_t* wcstr,size_t count);
COLLECTION_IMP int CLIBCDECL clibmbstowcsz(wchar_t* wcstr,const char* mbstr,size_t count);
COLLECTION_IMP const TClibStr& CLIBAPI clibGetEmptyString();
#define clibEmptyString clibGetEmptyString()


// ������մ���
COLLECTION_IMP void clibFreeEnvs();






// �������Բ���
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

// ȡ������������ʼ����ȡ������
CLIB_INLINE TClibStrData* TClibStr::GetData() const
	{ CLIBASSERT(m_pchData!=NULL); return ((TClibStrData*)m_pchData)-1; }
CLIB_INLINE void TClibStr::Init()
	{ m_pchData=clibEmptyString.m_pchData; }
CLIB_INLINE int PASCAL TClibStr::SafeStrlen(LPCSTR lpsz)
	{ return (int)((lpsz==NULL) ? 0 : lstrlenA(lpsz)); }

// �Ƚϲ���
CLIB_INLINE int TClibStr::Compare(LPCSTR lpsz) const
	{ return strcmp(m_pchData,lpsz); }
CLIB_INLINE int TClibStr::CompareNoCase(LPCSTR lpsz) const
	{ return stricmp(m_pchData,lpsz); }

// �Ƚϲ�������(ʵ��)
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
// ��Ӧģ����ĸ�������
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
