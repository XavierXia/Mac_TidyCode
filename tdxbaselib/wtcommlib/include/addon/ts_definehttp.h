interface IHttpHandler;				// 协议处理器(PROTOCOLTYPE_HTTP,PROTOCOLTYPE_HTTPX)



// HTTP处理相关上下文

// HTTP请求信息
// {2D9B0558-0242-4ebc-9777-271D68A3D151}
static const IID IID_IHttpReqCntx = { 0x2d9b0558, 0x242, 0x4ebc, { 0x97, 0x77, 0x27, 0x1d, 0x68, 0xa3, 0xd1, 0x51 } };
interface IHttpReqCntx : public IObject
{	virtual VOID ParseHeader(LPBYTE pHttpHeader,DWORD cbHttpHeader) PURE;
	virtual VOID SetFormData(LPBYTE pFormData,DWORD cbFormData) PURE;
	virtual VOID ParseForm() PURE;
	virtual LPCSTR GetVerb() PURE;
	virtual LPCSTR GetFile() PURE;
	virtual LPCSTR GetProtocol() PURE;

	virtual LONG GetParamCount() PURE;
	virtual LPCSTR ParamNameAt(LONG nIndex) PURE;
	virtual LPCSTR ParamValueAt(LONG nIndex) PURE;
	virtual LPCSTR GetParam(LPCSTR pszName) PURE;
	
	virtual LONG GetCookieCount() PURE;
	virtual LPCSTR CookieNameAt(LONG nIndex) PURE;
	virtual LPCSTR CookieValueAt(LONG nIndex) PURE;
	virtual LPCSTR GetCookie(LPCSTR pszName) PURE;
	
	virtual LONG GetHeaderVarCount() PURE;
	virtual LPCSTR HeaderVarNameAt(LONG nIndex) PURE;
	virtual LPCSTR HeaderVarValueAt(LONG nIndex) PURE;
	virtual LPCSTR GetHeaderVar(LPCSTR pszName) PURE;

	virtual LPBYTE GetFormDataPtr() PURE;
	virtual DWORD GetFormDataSize() PURE;
	virtual LONG GetFormVarCount() PURE;
	virtual LPCSTR FormVarNameAt(LONG nIndex) PURE;
	virtual LPCSTR FormVarValueAt(LONG nIndex) PURE;
	virtual LPCSTR GetFormVar(LPCSTR pszName) PURE;
};

// HTTP应答信息
// {E946A286-1D87-4147-B3E1-D1B6609753EB}
static const IID IID_IHttpAnsCntx = { 0xe946a286, 0x1d87, 0x4147, { 0xb3, 0xe1, 0xd1, 0xb6, 0x60, 0x97, 0x53, 0xeb } };
interface IHttpAnsCntx : public IObject
{
public:
	typedef enum enumCACHEMODE
	{	HTTP_CACHE_DEFAULT,
		HTTP_CACHE_NOSTORE,
		HTTP_CACHE_NOCACHE,
	} CACHEMODE;
public:
	WORD	m_wStatusNo;				// 状态代码("200","404"等)
	LPCSTR	m_pszStatus;				// 状态信息("OK"等)
	LPCSTR	m_pszContentType;			// 内容类型("application/octet-stream","text/plain"等)
	BYTE	m_cCompressType:2;			// 压缩模式(COMPRESSTYPE_XXX)
	BYTE	m_cCacheType:2;				// 缓存状态(HTTP_CACHE_XXX)
	BYTE	m_bKeepAlive:1;				// 保存存活状态
	BYTE	m_cReserved:3;				// 保留字段
	CHAR	m_szHeaders[64];			// 更多的头部信息
	LPBYTE	m_pBody;					// 应答缓冲区指针
	DWORD	m_cbHeaderRESV;				// 头部保留长度
	DWORD	m_cbBodyMax;				// 应答最大长度
	DWORD	m_cbBody;					// 应答长度
	DWORD	m_cbTotalBody;				// 全部数据长度
	BYTE	m_bHeaderSent;				// 是否头部已经发送
};

// 请求和应答上下文获取
#define USING_HTTP_REQCNTX()																					\
	IHttpReqCntx* pIHttpReqCntx=(IHttpReqCntx*)pIBusiness->FindCntxObj(BCNTX_HTTPREQ,IID_IHttpReqCntx);			\
	CLIBVERIFY(pIHttpReqCntx!=NULL);																			\

#define USING_HTTP_ANSCNTX()																					\
	BPR nBPR=m_pIServer->PrepareWriteBufAndEncoder(pIConnect,pIBusiness);										\
	if(nBPR!=BPR_SUCCESS) return nBPR;																			\
	IHttpAnsCntx* pIHttpAnsCntx=(IHttpAnsCntx*)pIBusiness->FindCntxObj(BCNTX_HTTPANS,IID_IHttpAnsCntx);			\
	CLIBVERIFY(pIHttpAnsCntx!=NULL&&pIHttpAnsCntx->m_pBody!=NULL);												\

#define USING_HTTP_REQANSCNTX()																					\
	USING_HTTP_REQCNTX()																						\
	USING_HTTP_ANSCNTX()																						\






// HTTP协议定义
typedef struct tagHTTPPROTDEF
{	LPCSTR		m_pszVerb;				// 谓词
	LPCSTR		m_pszURL;				// 链接
	BOOL		m_bPrefix;				// 前缀
	WORD		m_wID;					// HTTP协议ID
	LPCSTR		m_pszCmdDesc;			// 协议描述
	DWORD		m_dwProtFlag;			// 协议标识(定义线程类别,是否IX协议,是否需要日志和跟踪等)
} HTTPPROTDEF;
typedef HTTPPROTDEF* LPHTTPPROTDEF;


// HTTP协议处理器
// {1FAF676B-4817-413d-B191-C22F943C4B98}
static const IID IID_IHttpHandler = { 0x1faf676b, 0x4817, 0x413d, { 0xb1, 0x91, 0xc2, 0x2f, 0x94, 0x3c, 0x4b, 0x98 } };
interface IHttpHandler : public IHandler
{	virtual BPR ParseInfo(IConnect* pIConnect,IBusiness* pIBusiness,LPHTTPPROTDEF pHttpProtDef,LPPROTINFO pProtInfo) PURE;
	virtual BPR PreExecute(ISession* pISession,IConnect* pIConnect,IBusiness* pIBusiness) PURE;
	virtual BPR Execute(ISession* pISession,IConnect* pIConnect,IBusiness* pIBusiness) PURE;
};
