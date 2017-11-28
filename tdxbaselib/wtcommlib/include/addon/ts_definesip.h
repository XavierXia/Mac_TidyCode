

// SIP处理相关上下文

// SIP请求信息
// {B1D03F71-011F-4392-922B-0420BA5CA753}
static const IID IID_ISIPReqCntx = { 0xb1d03f71, 0x11f, 0x4392, { 0x92, 0x2b, 0x4, 0x20, 0xba, 0x5c, 0xa7, 0x53 } };
interface ISIPReqCntx : public IObject
{	virtual VOID ParseHeader(LPBYTE pSIPHeader,DWORD cbSIPHeader) PURE;
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

// SIP应答信息
// {A4718763-05D3-4780-8EB2-F62098AD26E4}
static const IID IID_ISIPAnsCntx = { 0xa4718763, 0x5d3, 0x4780, { 0x8e, 0xb2, 0xf6, 0x20, 0x98, 0xad, 0x26, 0xe4 } };
interface ISIPAnsCntx : public IObject
{
public:
	typedef enum enumCACHEMODE
	{	SIP_CACHE_DEFAULT,
		SIP_CACHE_NOSTORE,
		SIP_CACHE_NOCACHE,
	} CACHEMODE;
public:
	WORD	m_wStatusNo;				// 状态代码("200","404"等)
	LPCSTR	m_pszStatus;				// 状态信息("OK"等)
	LPCSTR	m_pszContentType;			// 内容类型("application/octet-stream","text/plain"等)
	BYTE	m_cCompressType:2;			// 压缩模式(COMPRESSTYPE_XXX)
	BYTE	m_cCacheType:2;				// 缓存状态(SIP_CACHE_XXX)
	BOOL	m_bKeepAlive:1;				// 保存存活状态
	BYTE	m_cReserved:5;				// 保留字段
	CHAR	m_szHeaders[64];			// 更多的头部信息
	LPBYTE	m_pBody;					// 应答缓冲区指针
	DWORD	m_cbBodyMax;				// 应答最大长度
	DWORD	m_cbBody;					// 应答长度
};

// 请求和应答上下文获取
#define USING_SIP_REQCNTX()																					\
	ISIPReqCntx* pISIPReqCntx=(ISIPReqCntx*)pIBusiness->FindCntxObj(BCNTX_SIPREQ,IID_ISIPReqCntx);			\
	CLIBVERIFY(pISIPReqCntx!=NULL);																			\

#define USING_SIP_ANSCNTX()																					\
	BPR nBPR=m_pIServer->PrepareWriteBufAndEncoder(pIConnect,pIBusiness);									\
	if(nBPR!=BPR_SUCCESS) return nBPR;																		\
	ISIPAnsCntx* pISIPAnsCntx=(ISIPAnsCntx*)pIBusiness->FindCntxObj(BCNTX_SIPANS,IID_ISIPAnsCntx);			\
	CLIBVERIFY(pISIPAnsCntx!=NULL&&pISIPAnsCntx->m_pBody!=NULL);											\

#define USING_SIP_REQANSCNTX()																				\
	USING_SIP_REQCNTX()																						\
	USING_SIP_ANSCNTX()																						\


// SIP协议定义
typedef struct tagSIPPROTDEF
{	LPCSTR		m_pszVerb;				// 谓词
	LPCSTR		m_pszURL;				// 链接
	BOOL		m_bPrefix;				// 前缀
	WORD		m_wID;					// SIP协议ID
	LPCSTR		m_pszCmdDesc;			// 协议描述
	DWORD		m_dwProtFlag;			// 协议标识(定义线程类别,是否IX协议,是否需要日志和跟踪等)
} SIPPROTDEF;
typedef SIPPROTDEF* LPSIPPROTDEF;


// SIP协议处理器
// {1FAF676B-4817-413d-B191-C22F943C4B98}
static const IID IID_ISIPHandler = { 0x1faf676b, 0x4817, 0x413d, { 0xb1, 0x91, 0xc2, 0x2f, 0x94, 0x3c, 0x4b, 0x98 } };
interface ISIPHandler : public IHandler
{	virtual BPR ParseInfo(IConnect* pIConnect,IBusiness* pIBusiness,LPSIPPROTDEF pSIPProtDef,LPPROTINFO pProtInfo) PURE;
	virtual BPR PreExecute(ISession* pISession,IConnect* pIConnect,IBusiness* pIBusiness) PURE;
	virtual BPR Execute(ISession* pISession,IConnect* pIConnect,IBusiness* pIBusiness) PURE;
};
