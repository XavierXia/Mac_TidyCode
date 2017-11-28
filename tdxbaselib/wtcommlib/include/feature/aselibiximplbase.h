//////////////////////////////////////////////////////////////////////////
// ��������:2013/03/19
// ����˵��:�����ֵ䴦����
// �����¼:  
#ifndef __ASE_LIB_IX_IMPL_BASE__H__
#define __ASE_LIB_IX_IMPL_BASE__H__
#pragma pack(1)
#ifndef ASELIB_API
	#error "ASELib.h" must be included.
#endif

// �ֶζ���(�����ֵ��ֶζ���)
typedef struct ASELIB_API tagFIELDINFO
{	WORD	fieldID;				// �ֶ�����
	BYTE	dataType;				// ��������
	BYTE	dispFlag;				// ��ʾ������
	WORD	expType;				// ������ʾ����
	CHAR	fieldName[21];			// �ֶ�˵��
	BYTE	showflag;				// �Ƿ�Ϊ�����ֶ�
	BYTE	cacheflag;				// �Ƿ�Ϊ�����ֶ�
	WORD	structID;				// �ṹID(2013-03-18)
	WORD	unused3;				// ����
	WORD	unused4;				// ����
} FIELDINFO,*LPFIELDINFO;			// �ֶζ���

// �ֶ�Ӧ��
typedef struct ASELIB_API tagFIELDREF
{	WORD	structID;				// �ṹID(2013-03-18)
	WORD	fieldID;				// �ֶ�ID
	WORD	aliasID;				// ����ID
} FIELDREF,*LPFIELDREF;





// Э���ֶμ�����(��һ���͵ڶ���Э��)
typedef struct ASELIB_API tagWTSTRUCT_INFO
{	WORD	m_wStructID;			// �ṹID
	WORD	m_wFieldNum;			// �ֶ���
	LPWORD	m_pFieldID;				// ���ܵĽṹ����
	tagWTSTRUCT_INFO()
	{	memset(this,0,size_of(tagWTSTRUCT_INFO));
	}
} WTSTRUCT_INFO,*LPWTSTRUCT_INFO;
// ����/Ӧ�𻺳����ṹ(��һ���͵ڶ���Э��)
typedef struct ASELIB_API tagWTCOMMON_STRC
{	LPSTR			m_pBuffer;		// ������
	WORD			m_wStructID;	// �ṹ����
	LPWTSTRUCT_INFO	m_pStructInfo;	// �ṹ��Ϣ
	tagWTCOMMON_STRC() { memset(this,0,size_of(tagWTCOMMON_STRC)); }
} WTCOMMON_STRC,*LPWTCOMMON_STRC;




// Э���ֶμ�����(������)
typedef struct ASELIB_API tagIXSTRUCTINFO
{	WORD		m_wStructID;		// �ṹID
	WORD		m_wFieldNum;		// �ֶ���
	FIELDREF*	m_pFieldRefs;		// ���ܵ��ֶ����ö���
} IXSTRUCTINFO,*LPIXSTRUCTINFO;




// �ֶλ��滺�����ṹ
#define MAX_CACHE_SIZE (8*1024)
typedef struct ASELIB_API tagWTCACHE_STRC
{	WORD			m_wFieldID;
	WORD			m_wFieldSize;
	LPBYTE			m_pBuffer;
	tagWTCACHE_STRC() { memset(this,0,size_of(tagWTCACHE_STRC)); }
} WTCACHE_STRC, *LPWTCACHE_STRC;
typedef WTCACHE_STRC CACHESTRUCT;
typedef LPWTCACHE_STRC LPCACHESTRUCT;



//////////////////////////////////////////////////////////////////////////
// �������(�ɰ�)
#define WTCOMM_ERR_NULL			0		// �޴���
#define WTCOMM_ERR_OVERFLOW		1		// �����������(��������)
#define WTCOMM_ERR_ENCRYPT		2		// ���ܴ���(��������)
#define WTCOMM_ERR_UUENCODE		3		// BASE64�������(��������)
#define WTCOMM_ERR_ESCAPECODE	4		// ESCAPE�������(��������)
#define WTCOMM_ERR_STACK		5		// ��ջ����(�޶�ջ����)
#define WTCOMM_ERR_BUFTOOLONG	6		// ������̫��
#define WTCOMM_ERR_RETOVERFLOW	7		// ������Ϣ���
#define WTCOMM_ERR_ATTOVERFLOW	8		// �������
#define WTCOMM_ERR_FIELD_MISS	600		// ��Ӳ������ֶ�
#define WTCOMM_ERR_NULL_STRUCT	601		// ��ͼ�Կսṹ����ֶ�
#define WTCOMM_ERR_INDEX_MISS	601		// �ֶ�����������
#define WTCOMM_ERR_EXCEPTION	602		// �쳣
// �������(�°�)
#define IXCOMM_ERR_NULL			0		// �޴���
#define IXCOMM_ERR_OVERFLOW		1		// �����������(��������)
#define IXCOMM_ERR_ENCRYPT		2		// ���ܴ���(��������)
#define IXCOMM_ERR_UUENCODE		3		// BASE64�������(��������)
#define IXCOMM_ERR_ESCAPECODE	4		// ESCAPE�������(��������)
#define IXCOMM_ERR_STACK		5		// ��ջ����(�޶�ջ����)
#define IXCOMM_ERR_BUFTOOLONG	6		// ������̫��
#define IXCOMM_ERR_RETOVERFLOW	7		// ������Ϣ���
#define IXCOMM_ERR_ATTOVERFLOW	8		// �������
#define IXCOMM_ERR_FIELD_MISS	600		// ��Ӳ������ֶ�
#define IXCOMM_ERR_NULL_STRUCT	601		// ��ͼ�Կսṹ����ֶ�
#define IXCOMM_ERR_INDEX_MISS	601		// �ֶ�����������
#define IXCOMM_ERR_EXCEPTION	602		// �쳣
#define IXCOMM_ERR_BADPARAM		603		// ��������
#define IXCOMM_ERR_IMPROPER		604		// ��ǡ������(�����ڶ�ȡ��ʱ�������д���API����д���ʱ������˶�ȡ��API)
#define IXCOMM_ERR_TOOMANYFLD	605		// �ֶ���Ϣ����
// ��������
#define DICT_TERMINAL			'\0'	// ���ݽ����ַ�
#define FIELD_SPERATOR			'|'		// ���м���"|"�ָ�
#define LINE_SPERATOR			'\r'	// �������м���"\r\n"�ָ�
#define IXPKGVER_TAG			"IX,"	// IX���ı�ʶ

typedef DWORD ATTACHSIZE;
#define ATTACH_TERMINAL			'\f'	// ���������ַ�
#define ATTACH_PKGSIZE(cbAtt)	(1+(cbAtt)+size_of(ATTACHSIZE)+1)






//////////////////////////////////////////////////////////////////////////
// ������
//////////////////////////////////////////////////////////////////////////
void ASELIB_API WTCommLibRedirect(FILE* pFile);
void ASELIB_API WTCommLibTrace(LPCSTR lpszFormat,...);
void ASELIB_API WTCommLibDump(LPCSTR lpszFormat,...);
void ASELIB_API WTCommLibAssertEx(LPCSTR lpszFile,LONG nLine,LPCSTR lpszExpr);
void ASELIB_API WTCommLibVerifyEx(LPCSTR lpszFile,LONG nLine,LPCSTR lpszExpr);
#ifdef _DEBUG
	#ifndef WTCOMM_TRACE
		#define WTCOMM_TRACE WTCommLibTrace
	#endif
	#ifndef WTCOMM_ASSERT
		#define WTCOMM_ASSERT(expr)	{if(!(expr)) { WTCommLibAssertEx(__FILE__, __LINE__,#expr); }}
	#endif
	#ifndef WTCOMM_VERIFY
		#define WTCOMM_VERIFY(expr)	{if(!(expr)) { WTCommLibVerifyEx(__FILE__, __LINE__,#expr); }}
	#endif
#else
	#ifndef WTCOMM_TRACE
		#define WTCOMM_TRACE		1?(void)0:WTCommLibTrace
	#endif
	#ifndef WTCOMM_ASSERT
		#define WTCOMM_ASSERT(expr)	((void)0)
	#endif
	#ifndef WTCOMM_VERIFY
		#define WTCOMM_VERIFY(expr)	{if(!(expr)) { WTCommLibVerifyEx(__FILE__, __LINE__,#expr); }}
	#endif
#endif
#define IXCOMM_TRACE	WTCOMM_TRACE
#define IXCOMM_ASSERT	WTCOMM_ASSERT
#define IXCOMM_VERIFY	WTCOMM_VERIFY


//////////////////////////////////////////////////////////////////////////
// �õ��汾
//////////////////////////////////////////////////////////////////////////
void ASELIB_API WTCommLibGetVer(LPSTR lpszVer,DWORD dwSize);



class CWtCookies;	// Cookies��
class CWtCache;		// ����(CACHE��COOKIES)������
typedef CWtCache CIXCache;
typedef CWtCookies CIXCookies;
class CPolymer;		// ���ݰ�
class CByteStream;	// ����������


//////////////////////////////////////////////////////////////////////////
//  �ֵ��ֶλ�������(��CACHE��COOKIES)��
//////////////////////////////////////////////////////////////////////////
class ASELIB_API CWtCache
{
public:
	CWtCache();
	virtual ~CWtCache();
public:
	// ���úͻ�ȡ�����ֶ�(ע:���ﱣ���Ϊԭʼ��ʽ,�ַ��������������ַ�,�����Ƕ�����)
	BOOL SetCacheItemAsBinary(WORD wFieldID,CONST LPBYTE lpBuffer,WORD wSize);
	BOOL GetCacheItemAsBinary(WORD wFieldID,WORD wMaxSize,LPBYTE lpBuffer,WORD* pwSize);
	POSITION GetFirstCachePosition();
	WORD GetNextCache(POSITION& posCache);
protected:
	LONG FindOrAllocCacheItem(WORD wFieldID);
	LONG FindCacheItem(WORD wFieldID);
private:
	WTCACHE_STRC* m_pCacheItem;
	WORD m_wCacheCount;
	WORD m_wAllocCount;
};

//////////////////////////////////////////////////////////////////////////
// �ֵ�COOKIES������
//////////////////////////////////////////////////////////////////////////
class ASELIB_API CWtCookies
{
public:
	CWtCookies();
	virtual~CWtCookies();
	BOOL AddCookies(WORD wFieldID,LPSTR pszCookies);
	DWORD GetCookiesLength();
	LPCSTR GetCookies();
protected:
	DWORD	m_adwReserved[4];
	CHAR	m_szCookies[2048];
	DWORD	m_dwUsedLength;
};






// ���ú궨��
#define GetItemChArrayValueFromID(ID,CHARRAY)		GetItemValueFromID(ID,CHARRAY,size_of(CHARRAY))
#define GetItemSecChArrayValueFromID(ID,CHARRAY)	GetItemValueFromID(ID,CHARRAY,size_of(CHARRAY),TRUE)

// ����ֶη��صĽṹ(����ֱ�ӷ���)
typedef struct tagPOLYMERINFO
{	LPDWORD	m_lpcbUsed;		// ʹ���еĻ�����ָ��
	LPBYTE	m_lpItem;		// ��ǰ������ָ��
	DWORD	m_cbItem;		// ��ǰ�������С
	DWORD	m_dwMaxSize;	// ����������С
} POLYMERINFO,*LPPOLYMERINFO;


class ASELIB_API CPolymer
{
public:
	CPolymer();
	virtual~CPolymer();

	// �����ۺ�������(��������С9�ֽ�)
	// ����:	lpBuffer	�ⲿ������
	//			cbBuffer	�ⲿ��������С
	//			cbUsed		��ʹ�õ��ֽ���,Ϊ0�������´���
	// ����:	(BOOL)		�Ƿ񴴽��ɹ�
	BOOL Create(LPBYTE lpBuffer,DWORD cbBuffer,DWORD cbUsed);

	// �õ�ʹ���е���������С
	DWORD GetUsedLength();

	// ���������
	// ����:	cKey		������
	//			lpData		���ݻ�����
	//			cbData		���ݴ�С
	// ����:	(BOOL)		�Ƿ���ӳɹ�
	BOOL SetData(BYTE cKey,const LPBYTE lpData,DWORD cbData,LPPOLYMERINFO lpPolymerInfo=NULL);

	// ����ַ���������
	// ����:	cKey		������
	//			nMaxLength	���������
	//			lpString	���ݻ�����
	//			nLength		�ļ�����,���<0���Զ��ж�
	// ����:	(BOOL)		�Ƿ���ӳɹ�
	BOOL SetString(BYTE cKey,LONG nMaxLength,LPCSTR lpString,LONG nLength);

	// ɾ��������
	// ����:	cKey		������
	// ����:	(BOOL)		�Ƿ�ɾ���ɹ�
	BOOL DelData(BYTE cKey);
	
	// �ж��������Ƿ����
	// ����:	cKey		������
	// ����:	(BOOL)		�Ƿ����ݴ���
	BOOL IsDataExist(BYTE cKey);
	
	// ���������ʼ��ַ
	// ����:	cKey		������
	// ����:	(LPBYTE)	�����ʼλ��,���������,�򷵻�NULL
	LPBYTE GetDataAddr(BYTE cKey);

	// �õ��������
	// ����:	cKey		������
	// ����:	(DWORD)		���ݳ���,(DWORD)-1�������ݲ�����
	DWORD GetDataLength(BYTE cKey);

	// �õ��������(���ݻ������ᱻ����)
	// ����:	cKey		������
	//			lpBuffer	���ݻ�����
	//			cbBuffer	���ݻ�������С
	// ����:	(DWORD)		���ݳ���,(DWORD)-1�������ݲ����ڻ������ݳ�������
	DWORD GetData(BYTE cKey,LPBYTE lpBuffer,DWORD cbBuffer);

protected:
	// ��������ʽ
	typedef struct tagDATIDX
	{	BYTE  m_cKey;
		DWORD m_cbData;
	} DATIDX,*LPDATIDX;
	// �õ�ÿ�������������ɵ����������
	inline BYTE CalcIdxNumPerBlk()
	{	return (BYTE)4;
	}
	// �õ�ÿ����������Ĵ�С
	inline DWORD CalcIdxBufSizePerBlk()
	{	return CalcIdxNumPerBlk()*size_of(DATIDX);
	}
	// ���������ΪcKeyNumʱ������������������������������������
	// ע:������������Ϊ��
	inline BYTE CalcMaxIdxNum(BYTE cKeyNum)
	{	return (BYTE)max_of((cKeyNum+CalcIdxNumPerBlk()-1)/CalcIdxNumPerBlk()*CalcIdxNumPerBlk(),CalcIdxNumPerBlk());
	}
	// ���������ΪcKeyNumʱ��������������������������Ĵ�С
	inline DWORD CalcIdxBufSize(BYTE cKeyNum)
	{	return CalcMaxIdxNum(cKeyNum)*size_of(DATIDX);
	}
protected:
	DWORD FindKeyOffset(BYTE cKey,LPBYTE lpIdx);
protected:
	BOOL		m_bCreated;		// �Ƿ񱻴���
	LPBYTE		m_lpBuffer;		// ������
	DWORD		m_cbBuffer;		// ��������С
	DWORD		m_cbUsed;		// ʹ���еĻ�����
	LPBYTE		m_lpcDatsNum;	// ������
	LPDATIDX	m_lpDatIdxs;	// ������ָ��
	LPBYTE		m_lpDatas;		// ���ݻ�����ָ��
};




class ASELIB_API CByteStream
{
public:
	CByteStream(LPBYTE lpBuffer,DWORD cbBuffer,DWORD cbUsed=0);
	virtual~CByteStream();

	DWORD GetBufferSize() { return m_cbBuffer; }
	DWORD GetFreeSize() { return m_cbBuffer-m_cbUsed; }
	DWORD GetUsed() { return m_cbUsed; }
	VOID SeekToBegin() { m_dwOffset=0; }
	VOID SeekToEnd() { m_dwOffset=m_cbUsed; }
	VOID SeekTo(DWORD dwOffset) { m_dwOffset=dwOffset; }
	VOID Truncate() { m_cbUsed=m_dwOffset=0; }

	// ������������д��Ͷ�ȡ
	#define DECLARE_WRITE_STREAM_X(FUNC,TYPE)							\
		BOOL FUNC(TYPE xValue)											\
			{	if(m_dwOffset+size_of(TYPE)>=m_cbBuffer)				\
				{	m_bOverflow=TRUE;									\
					return FALSE;										\
				}														\
				*((TYPE*)(m_lpBuffer+m_dwOffset))=xValue;				\
				m_dwOffset+=size_of(TYPE);								\
				if(m_dwOffset>m_cbUsed) m_cbUsed=m_dwOffset;			\
				return TRUE;											\
			}
	DECLARE_WRITE_STREAM_X(WriteChar,CHAR);
	DECLARE_WRITE_STREAM_X(WriteByte,BYTE);
	DECLARE_WRITE_STREAM_X(WriteShort,SHORT);
	DECLARE_WRITE_STREAM_X(WriteUShort,USHORT);
	DECLARE_WRITE_STREAM_X(WriteLong,LONG);
	DECLARE_WRITE_STREAM_X(WriteULong,ULONG);
	DECLARE_WRITE_STREAM_X(WriteInt,INT);
	DECLARE_WRITE_STREAM_X(WriteUint,UINT);
	DECLARE_WRITE_STREAM_X(WriteWord,WORD);
	DECLARE_WRITE_STREAM_X(WriteDWord,DWORD);
	DECLARE_WRITE_STREAM_X(WriteBool,BOOL);
	DECLARE_WRITE_STREAM_X(WriteFloat,FLOAT);
	DECLARE_WRITE_STREAM_X(WriteDouble,double);
	#undef DECLARE_WRITE_STREAM_X

	#define DECLARE_READ_STREAM_X(FUNC,TYPE)							\
		BOOL FUNC(TYPE& xValue)											\
			{	if(m_dwOffset+size_of(TYPE)>m_cbUsed) return FALSE;		\
				xValue=*((TYPE*)(m_lpBuffer+m_dwOffset));				\
				m_dwOffset+=size_of(TYPE);								\
				return TRUE;											\
			}
	DECLARE_READ_STREAM_X(ReadChar,CHAR);
	DECLARE_READ_STREAM_X(ReadByte,BYTE);
	DECLARE_READ_STREAM_X(ReadShort,SHORT);
	DECLARE_READ_STREAM_X(ReadUShort,USHORT);
	DECLARE_READ_STREAM_X(ReadLong,LONG);
	DECLARE_READ_STREAM_X(ReadULong,ULONG);
	DECLARE_READ_STREAM_X(ReadInt,INT);
	DECLARE_READ_STREAM_X(ReadUint,UINT);
	DECLARE_READ_STREAM_X(ReadWord,WORD);
	DECLARE_READ_STREAM_X(ReadDWord,DWORD);
	DECLARE_READ_STREAM_X(ReadBool,BOOL);
	DECLARE_READ_STREAM_X(ReadFloat,FLOAT);
	DECLARE_READ_STREAM_X(ReadDouble,double);
	#undef DECLARE_READ_STREAM_X

	// ���ݿ�д��Ͷ�ȡ
	BOOL WriteBinary(LPCVOID lpBuffer,DWORD cbBuffer);
	BOOL ReadBinary(LPVOID lpBuffer,DWORD cbBuffer);

	// �ַ���д��Ͷ�ȡ
	BOOL WriteString(LPCSTR lpString);
	BOOL ReadString(LPSTR lpBuffer,DWORD cbBuffer);

	// �����
	BOOL IsOverflow() { return m_bOverflow; }

	// �ڴ���
	DWORD BeginSection();
	BOOL EndSection(DWORD dwSectionOffset);
	
	// ����������
	BOOL WriteBuffer(LPBYTE pBuffer,DWORD cbData);
	BOOL WriteLiteBuffer(LPBYTE pBuffer,DWORD cbData);
	BOOL ReadBuffer(LPBYTE pBuffer,DWORD cbBuffer,DWORD& cbData);
	BOOL ReadLiteBuffer(LPBYTE pBuffer,DWORD cbBuffer,DWORD& cbData);

protected:
	LPBYTE m_lpBuffer;
	DWORD m_cbBuffer;
	DWORD m_cbUsed;
	DWORD m_dwOffset;
	BOOL m_bOverflow;
};



#pragma pack()
#endif
