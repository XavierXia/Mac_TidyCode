interface IRawHandler;				// 协议处理器(PROTOCOLTYPE_TUNNEL,PROTOCOLTYPE_BINARY)


// 原始请求信息
typedef struct tagRAWREQCNTX
{	LPBYTE m_pOption;					// 选项区指针
	DWORD m_cbOption;					// 选项区大小
	LPBYTE m_pBody;						// 消息缓冲区指针
	DWORD m_cbBody;						// 消息大小
	DWORD m_cbPackage;					// 消息缓冲区大小(解包前)
	BYTE m_cCompressType;				// 压缩模式
	BYTE m_cEncryptType;				// 加密类型
} RAWREQCNTX;

// 原始应答信息
typedef struct tagRAWANSCNTX
{	LPBYTE m_pOption;					// 选项区指针
	DWORD m_cbOption;					// 选项区大小
	LPBYTE m_pBody;						// 消息缓冲区指针
	DWORD m_cbBodyMax;					// 消息缓冲区最大长度
	DWORD m_cbBody;						// 消息大小
	BOOL m_bExternPacker;				// 外部封包器
	BYTE m_cCompressType;				// 压缩模式(原始大小,外部封包)
	BYTE m_cEncryptType;				// 加密类型(原始大小,外部封包)
	WORD m_wRawLen;						// 应答长度(原始大小,外部封包)
} RAWANSCNTX;

// 请求和应答上下文获取
#define USING_RAW_REQCNTX()																			\
	RAWREQCNTX* pRawReqCntx=(RAWREQCNTX*)pIBusiness->FindCntxObj(BCNTX_RAWREQ);						\
	CLIBVERIFY(pRawReqCntx!=NULL);																	\

#define USING_RAW_ANSCNTX()																			\
	BPR nBPR=m_pIServer->PrepareWriteBufAndEncoder(pIConnect,pIBusiness);							\
	if(nBPR!=BPR_SUCCESS) return nBPR;																\
	RAWANSCNTX* pRawAnsCntx=(RAWANSCNTX*)pIBusiness->FindCntxObj(BCNTX_RAWANS);						\
	CLIBVERIFY(pRawAnsCntx!=NULL&&pRawAnsCntx->m_pBody!=NULL);										\

#define USING_RAW_REQANSCNTX()																		\
	USING_RAW_REQCNTX()																				\
	USING_RAW_ANSCNTX()																				\



// RAW协议定义
typedef struct tagRAWPROTDEF
{	WORD		m_wCmdNoMin;			// 协议号(起始)
	WORD		m_wCmdNoMax;			// 协议号(结束)
	LPCSTR		m_pszCmdDesc;			// 协议描述
	DWORD		m_dwProtFlag;			// 协议标识(定义缓冲区类别,加密等线程类别,是否IX协议,是否需要日志和跟踪等)
	WORD		m_wOptionLen;			// 包头信息块长度
	WORD		m_wMinReqLen;			// 最小请求长度
	WORD		m_wMinAnsBuf;			// 最小应答长度
} RAWPROTDEF;
typedef RAWPROTDEF* LPRAWPROTDEF;



// RAW协议处理器
// {BA74AD15-6531-4a7a-8D3A-9D5ADCA549BB}
static const IID IID_IRawHandler = { 0xba74ad15, 0x6531, 0x4a7a, { 0x8d, 0x3a, 0x9d, 0x5a, 0xdc, 0xa5, 0x49, 0xbb } };
interface IRawHandler : public IHandler
{	virtual BPR ParseInfo(IConnect* pIConnect,IBusiness* pIBusiness,LPRAWPROTDEF pProtDef,LPPROTINFO pProtInfo) PURE;
	virtual BPR PreExecute(ISession* pISession,IConnect* pIConnect,IBusiness* pIBusiness) PURE;
	virtual BPR Execute(ISession* pISession,IConnect* pIConnect,IBusiness* pIBusiness) PURE;
};



