//////////////////////////////////////////////////////////////////////////
// 创建日期:2013/03/19
// 功能说明:数据字典处理类
// 变更记录:  
#ifndef __ASE_LIB_IX_IMPL_BASE__H__
#define __ASE_LIB_IX_IMPL_BASE__H__
#pragma pack(1)
#ifndef ASELIB_API
	#error "ASELib.h" must be included.
#endif

// 字段定义(数据字典字段定义)
typedef struct ASELIB_API tagFIELDINFO
{	WORD	fieldID;				// 字段类型
	BYTE	dataType;				// 数据类型
	BYTE	dispFlag;				// 显示对齐标记
	WORD	expType;				// 内容显示方法
	CHAR	fieldName[21];			// 字段说明
	BYTE	showflag;				// 是否为隐藏字段
	BYTE	cacheflag;				// 是否为缓存字段
	WORD	structID;				// 结构ID(2013-03-18)
	WORD	unused3;				// 保留
	WORD	unused4;				// 保留
} FIELDINFO,*LPFIELDINFO;			// 字段定义

// 字段应用
typedef struct ASELIB_API tagFIELDREF
{	WORD	structID;				// 结构ID(2013-03-18)
	WORD	fieldID;				// 字段ID
	WORD	aliasID;				// 别名ID
} FIELDREF,*LPFIELDREF;





// 协议字段集定义(第一代和第二代协议)
typedef struct ASELIB_API tagWTSTRUCT_INFO
{	WORD	m_wStructID;			// 结构ID
	WORD	m_wFieldNum;			// 字段数
	LPWORD	m_pFieldID;				// 功能的结构定义
	tagWTSTRUCT_INFO()
	{	memset(this,0,size_of(tagWTSTRUCT_INFO));
	}
} WTSTRUCT_INFO,*LPWTSTRUCT_INFO;
// 请求/应答缓冲区结构(第一代和第二代协议)
typedef struct ASELIB_API tagWTCOMMON_STRC
{	LPSTR			m_pBuffer;		// 缓冲区
	WORD			m_wStructID;	// 结构定义
	LPWTSTRUCT_INFO	m_pStructInfo;	// 结构信息
	tagWTCOMMON_STRC() { memset(this,0,size_of(tagWTCOMMON_STRC)); }
} WTCOMMON_STRC,*LPWTCOMMON_STRC;




// 协议字段集定义(第三代)
typedef struct ASELIB_API tagIXSTRUCTINFO
{	WORD		m_wStructID;		// 结构ID
	WORD		m_wFieldNum;		// 字段数
	FIELDREF*	m_pFieldRefs;		// 功能的字段引用定义
} IXSTRUCTINFO,*LPIXSTRUCTINFO;




// 字段缓存缓冲区结构
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
// 错误代码(旧版)
#define WTCOMM_ERR_NULL			0		// 无错误
#define WTCOMM_ERR_OVERFLOW		1		// 数据溢出错误(致命错误)
#define WTCOMM_ERR_ENCRYPT		2		// 加密错误(致命错误)
#define WTCOMM_ERR_UUENCODE		3		// BASE64编码错误(致命错误)
#define WTCOMM_ERR_ESCAPECODE	4		// ESCAPE编码错误(致命错误)
#define WTCOMM_ERR_STACK		5		// 堆栈错误(无堆栈可用)
#define WTCOMM_ERR_BUFTOOLONG	6		// 缓冲区太长
#define WTCOMM_ERR_RETOVERFLOW	7		// 返回信息溢出
#define WTCOMM_ERR_ATTOVERFLOW	8		// 附件溢出
#define WTCOMM_ERR_FIELD_MISS	600		// 添加不存在字段
#define WTCOMM_ERR_NULL_STRUCT	601		// 企图对空结构添加字段
#define WTCOMM_ERR_INDEX_MISS	601		// 字段索引不存在
#define WTCOMM_ERR_EXCEPTION	602		// 异常
// 错误代码(新版)
#define IXCOMM_ERR_NULL			0		// 无错误
#define IXCOMM_ERR_OVERFLOW		1		// 数据溢出错误(致命错误)
#define IXCOMM_ERR_ENCRYPT		2		// 加密错误(致命错误)
#define IXCOMM_ERR_UUENCODE		3		// BASE64编码错误(致命错误)
#define IXCOMM_ERR_ESCAPECODE	4		// ESCAPE编码错误(致命错误)
#define IXCOMM_ERR_STACK		5		// 堆栈错误(无堆栈可用)
#define IXCOMM_ERR_BUFTOOLONG	6		// 缓冲区太长
#define IXCOMM_ERR_RETOVERFLOW	7		// 返回信息溢出
#define IXCOMM_ERR_ATTOVERFLOW	8		// 附件溢出
#define IXCOMM_ERR_FIELD_MISS	600		// 添加不存在字段
#define IXCOMM_ERR_NULL_STRUCT	601		// 企图对空结构添加字段
#define IXCOMM_ERR_INDEX_MISS	601		// 字段索引不存在
#define IXCOMM_ERR_EXCEPTION	602		// 异常
#define IXCOMM_ERR_BADPARAM		603		// 参数错误
#define IXCOMM_ERR_IMPROPER		604		// 不恰当调用(例如在读取的时候调用了写入的API或者写入的时候调用了读取的API)
#define IXCOMM_ERR_TOOMANYFLD	605		// 字段信息过长
// 其他定义
#define DICT_TERMINAL			'\0'	// 数据结束字符
#define FIELD_SPERATOR			'|'		// 域中间以"|"分隔
#define LINE_SPERATOR			'\r'	// 行与行中间以"\r\n"分隔
#define IXPKGVER_TAG			"IX,"	// IX报文标识

typedef DWORD ATTACHSIZE;
#define ATTACH_TERMINAL			'\f'	// 附件结束字符
#define ATTACH_PKGSIZE(cbAtt)	(1+(cbAtt)+size_of(ATTACHSIZE)+1)






//////////////////////////////////////////////////////////////////////////
// 调试类
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
// 得到版本
//////////////////////////////////////////////////////////////////////////
void ASELIB_API WTCommLibGetVer(LPSTR lpszVer,DWORD dwSize);



class CWtCookies;	// Cookies类
class CWtCache;		// 缓存(CACHE和COOKIES)处理类
typedef CWtCache CIXCache;
typedef CWtCookies CIXCookies;
class CPolymer;		// 数据包
class CByteStream;	// 网络数据流


//////////////////////////////////////////////////////////////////////////
//  字典字段缓存容器(含CACHE和COOKIES)类
//////////////////////////////////////////////////////////////////////////
class ASELIB_API CWtCache
{
public:
	CWtCache();
	virtual ~CWtCache();
public:
	// 设置和获取缓存字段(注:这里保存的为原始格式,字符串不包括结束字符,可以是二进制)
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
// 字典COOKIES处理类
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






// 常用宏定义
#define GetItemChArrayValueFromID(ID,CHARRAY)		GetItemValueFromID(ID,CHARRAY,size_of(CHARRAY))
#define GetItemSecChArrayValueFromID(ID,CHARRAY)	GetItemValueFromID(ID,CHARRAY,size_of(CHARRAY),TRUE)

// 添加字段返回的结构(便于直接访问)
typedef struct tagPOLYMERINFO
{	LPDWORD	m_lpcbUsed;		// 使用中的缓冲区指针
	LPBYTE	m_lpItem;		// 当前数据项指针
	DWORD	m_cbItem;		// 当前数据项大小
	DWORD	m_dwMaxSize;	// 数据项最大大小
} POLYMERINFO,*LPPOLYMERINFO;


class ASELIB_API CPolymer
{
public:
	CPolymer();
	virtual~CPolymer();

	// 创建聚合数据区(缓冲区最小9字节)
	// 参数:	lpBuffer	外部缓冲区
	//			cbBuffer	外部缓冲区大小
	//			cbUsed		已使用的字节数,为0表明重新创建
	// 返回:	(BOOL)		是否创建成功
	BOOL Create(LPBYTE lpBuffer,DWORD cbBuffer,DWORD cbUsed);

	// 得到使用中的数据区大小
	DWORD GetUsedLength();

	// 添加数据项
	// 参数:	cKey		数据项
	//			lpData		数据缓冲区
	//			cbData		数据大小
	// 返回:	(BOOL)		是否添加成功
	BOOL SetData(BYTE cKey,const LPBYTE lpData,DWORD cbData,LPPOLYMERINFO lpPolymerInfo=NULL);

	// 添加字符串数据项
	// 参数:	cKey		数据项
	//			nMaxLength	最大允许长度
	//			lpString	数据缓冲区
	//			nLength		文件长度,如果<0则自动判断
	// 返回:	(BOOL)		是否添加成功
	BOOL SetString(BYTE cKey,LONG nMaxLength,LPCSTR lpString,LONG nLength);

	// 删除数据项
	// 参数:	cKey		数据项
	// 返回:	(BOOL)		是否删除成功
	BOOL DelData(BYTE cKey);
	
	// 判断数据项是否存在
	// 参数:	cKey		数据项
	// 返回:	(BOOL)		是否数据存在
	BOOL IsDataExist(BYTE cKey);
	
	// 查找数据项开始地址
	// 参数:	cKey		数据项
	// 返回:	(LPBYTE)	数据项开始位置,如果不存在,则返回NULL
	LPBYTE GetDataAddr(BYTE cKey);

	// 得到数据项长度
	// 参数:	cKey		数据项
	// 返回:	(DWORD)		数据长度,(DWORD)-1表明数据不存在
	DWORD GetDataLength(BYTE cKey);

	// 得到数据项长度(数据缓冲区会被清零)
	// 参数:	cKey		数据项
	//			lpBuffer	数据缓冲区
	//			cbBuffer	数据缓冲区大小
	// 返回:	(DWORD)		数据长度,(DWORD)-1表明数据不存在或者数据超过长度
	DWORD GetData(BYTE cKey,LPBYTE lpBuffer,DWORD cbBuffer);

protected:
	// 索引区格式
	typedef struct tagDATIDX
	{	BYTE  m_cKey;
		DWORD m_cbData;
	} DATIDX,*LPDATIDX;
	// 得到每个索引区块容纳的数据项个数
	inline BYTE CalcIdxNumPerBlk()
	{	return (BYTE)4;
	}
	// 得到每个索引区块的大小
	inline DWORD CalcIdxBufSizePerBlk()
	{	return CalcIdxNumPerBlk()*size_of(DATIDX);
	}
	// 计算键个数为cKeyNum时候键索引缓冲区包含的索引区的数据项个数
	// 注:索引区不允许为空
	inline BYTE CalcMaxIdxNum(BYTE cKeyNum)
	{	return (BYTE)max_of((cKeyNum+CalcIdxNumPerBlk()-1)/CalcIdxNumPerBlk()*CalcIdxNumPerBlk(),CalcIdxNumPerBlk());
	}
	// 计算键个数为cKeyNum时候键索引缓冲区包含的索引区的大小
	inline DWORD CalcIdxBufSize(BYTE cKeyNum)
	{	return CalcMaxIdxNum(cKeyNum)*size_of(DATIDX);
	}
protected:
	DWORD FindKeyOffset(BYTE cKey,LPBYTE lpIdx);
protected:
	BOOL		m_bCreated;		// 是否被创建
	LPBYTE		m_lpBuffer;		// 缓冲区
	DWORD		m_cbBuffer;		// 缓冲区大小
	DWORD		m_cbUsed;		// 使用中的缓冲区
	LPBYTE		m_lpcDatsNum;	// 数据项
	LPDATIDX	m_lpDatIdxs;	// 数据项指针
	LPBYTE		m_lpDatas;		// 数据缓冲区指针
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

	// 基本类型数据写入和读取
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

	// 数据块写入和读取
	BOOL WriteBinary(LPCVOID lpBuffer,DWORD cbBuffer);
	BOOL ReadBinary(LPVOID lpBuffer,DWORD cbBuffer);

	// 字符串写入和读取
	BOOL WriteString(LPCSTR lpString);
	BOOL ReadString(LPSTR lpBuffer,DWORD cbBuffer);

	// 检溢出
	BOOL IsOverflow() { return m_bOverflow; }

	// 节处理
	DWORD BeginSection();
	BOOL EndSection(DWORD dwSectionOffset);
	
	// 缓冲区处理
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
