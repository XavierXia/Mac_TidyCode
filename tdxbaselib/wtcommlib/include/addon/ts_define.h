//////////////////////////////////////////////////////////////////////////
// 接口定义
// 系统结构
//                     |                   |                   |                                          |
//                     |     主框架        |       协议簇      |                  执行层                  |
//                     |                   |                   |                                          |
//   +---------+       |   +---------+     |   +-----------+   |                                          |
//   |         |---------->| PACKAGE |-------->|   BINARY  |   |           +-------------+                |
//   |         |       |   +---------+     |   |           |-------------->|     RAW     |--------+---+   |
//   |         |       |                +----->|   TUNNEL  |   |           +-------------+        |   |   |
//   |         |       |   +---------+  |  |   +-----------+   |                                  |   |   |
//   |         |---------->|  HTTP   |--+  |                   |                                  |   |   |
//   |         |       |   +---------+  |  |   +-----------+   |                                  |   |   |
//   | 客户端  |       |                +----->|   HTTP    |   |           +-------------+        |   |   |
//   |         |       |                   |   |           |-------------->|     HTTP    |----+---+---+   |
//   |         |       |                   |   |  HTTP(x)  |   |           +-------------+    |   |   |   |
//   |         |       |                   |   +-----------+   |                              |   |   |   |
//   |         |       |                   |                   |                              |   |   |   |
//   |         |       |   +---------+     |   +-----------+   |           +-------------+    |   |   |   |
//   |         |---------->|   FIX   |-------->|    FIX    |-------------->|     FIX     |----|---+---+   |
//   +---------+       |   +---------+     |   +-----------+   |           +-------------+    |   |   |   |
//                     |                   |                   |                              |   |   |   |
//                     |                   |                   |                              |   |   |   |
//                     |                   |                   |                              |   |   |   |
//                     |                   |                   |                              |   |   |   |
//                     | +-------------+   |                   |                              |   |   |   |
//                     | |  HTTPPARSER |<-----------------------------------------------------+   |   |   |
//                     | +-------------+   |                   |                                  |   |   |
//                     |                   |                   |                                  |   |   |
//                     | +-------------+   |                   |                                  |   |   |
//                     | | IX HANDLER  |<---------------------------------------------------------+   |   |
//                     | +-------------+   |                   |                                      |   | 
//                     |                   |                   |                                      |   |
//                     | +-------------+   |                   |                                      |   |
//                     | |   SESSION   |<-------------------------------------------------------------+   |
//                     | +-------------+   |                   |                                          |
// 
// 配置文件结构
//	Manufacturer.manifest
//		maincenter.ini
//		tdx.ini
//		Services.xml
//			服务器.ini
//			其他配置
#ifndef __TS_DEFINE__H__
#define __TS_DEFINE__H__
#pragma pack(1)

#ifndef T2EE_SDKVER
	#define T2EE_SDKVER
	#define T2EESDKVER_DEPRECATION		0
	#define T2EESDKVER_1_00				1
	#define T2EESDKVER_2_00				2
	#define T2EESDKVER_2_01				3
	#define T2EESDKVER_2_02				4
	#define T2EESDKVER_2_03				4
	#define T2EESDKVER_LASTEST			T2EESDKVER_2_03
#endif


#ifdef ASELIB_LIB
	#define interface struct
	#define PURE =0
#endif


//////////////////////////////////////////////////////////////////////////
// 外部依赖的相关定义
#ifndef WITH_SAFEVCRT
	typedef enum enumINDICTYPE
	{	INDIC_LV,
		INDIC_FLOW,
		INDIC_STAT,
	} INDICTYPE;
#endif


#ifndef WITH_CLIBHLPR
	// 协议类型(参阅: iocpsvrmodel.h)
	#define PROTOCOLTYPE_UNKNOWN		(0)				// 协议类别: 未知协议
	#define PROTOCOLTYPE_HTTP			(1)				// 协议类别: HTTP协议
	#define PROTOCOLTYPE_HTTPX			(2)				// 协议类别: HTTPx协议
	#define PROTOCOLTYPE_TUNNEL			(3)				// 协议类别: 二进制协议(有协议版本)
	#define PROTOCOLTYPE_BINARY			(4)				// 协议类别: 二进制协议(有协议版本)
	#define PROTOCOLTYPE_SIP			(5)				// 协议类别: SIP协议
	#define PROTOCOLTYPE_FIX			(6)				// 协议类别: FIX协议
	#define PROTOCOLTYPE_T2				(7)				// 协议类型: 恒生T2协议
	#define PROTOCOLTYPE_KCXP			(8)				// 协议类型: 金证KCXP协议
#endif


#ifndef WITH_CLIBHLPR
	// 事务处理结果(参阅: iocpsvrmodel.h)
	typedef enum enumIOCPBPR
	{
		// 基本和功能实现错误
		BPR_BASE_ERROR				=  0,	// 未知错误
		BPR_INTERNAL_ERROR			= -1,	// 内部错误
		BPR_NOT_SUPPORT				= -2,	// 功能未支持
		BPR_NOT_IMPLEMENT			= -3,	// 功能未实现
		BPR_MANUAL_CLOSE			= -4,	// 手工关闭

		// 缓冲区错误
		BPR_NO_MEMORY				=-10,	// 内存不足
		BPR_NO_BUFFER				=-11,	// 缓冲区不足
		BPR_NO_BCSTACKSPACE			=-12,	// 事务上下文栈不足
		BPR_NO_SCSTACKSPACE			=-13,	// 会话上下文栈不足
		BPR_NO_BUSINESSSPACE		=-14,	// 事务池配额不足
		BPR_NO_BUSINESQUOTA			=-15,	// 事务池配额不足
		BPR_BUFSIZE_TOOSMALL		=-16,	// 缓冲区大小太小
		BPR_OPTSIZE_TOOLARGE		=-17,	// 选项大小太大
		BPR_OPTSIZE_NOTPROPER		=-18,	// 选项大小不恰当
		BPR_OPTREAD_ERROR			=-19,	// 选项读取错误
		BPR_OPTWRITE_ERROR			=-20,	// 选项写入错误
		BPR_DATSIZE_TOOLARGE		=-21,	// 数据大小太大
		BPR_DATSIZE_NOTPROPER		=-22,	// 数据大小不恰当
		BPR_DATREAD_ERROR			=-23,	// 数据读取错误
		BPR_DATWRITE_ERROR			=-24,	// 数据写入错误
		BPR_UNHANDLEDEXCEPTION		=-25,	// 在不恰当的地方抛出的协议异常

		// 上下文错误
		BPR_BUSINESS_MISSING		=-30,	// 事务已经丢失
		BPR_CONNECT_MISSING			=-31,	// 连接已经丢失(关闭)
		BPR_CONNECT_CLOSED			=-32,	// 事务在接收和入队时发生错误,连接已经被关闭
		BPR_CONNECT_FINALY			=-33,	// 事务在连接关闭时发现尚未被处理或尚未发送完成
		BPR_SESSION_MISSING			=-34,	// 会话已经丢失(关闭)
		BPR_SESSION_MISTAKE			=-35,	// 会话信息无效
		BPR_SESSION_CREATEFAIL		=-36,	// 创建会话信息失败
		BPR_SESSION_VERIFYFAIL		=-37,	// 校验会话信息失败
		BPR_SESSION_EXISTFAIL		=-38,	// 会话已经存在,禁止重复创建
		BPR_SESSION_OPENFAIL		=-39,	// 会话信息打开失败
		BPR_SESSION_NOTONLINE		=-40,	// 会话不在线
		BPR_SESSION_NOTAUTHORITY	=-41,	// 会话未被授权进行对应操作

		// 底层通讯错误
		BPR_CONSISTENCY_CHECK		=-50,	// 一致性检查错误
		BPR_PACKAGE_ERROR			=-51,	// 错误包
		BPR_BUSINESSSEND_FAIL		=-52,	// 事务发送失败(会强制关闭连接)
		BPR_FRAGMENTSEND_FAIL		=-53,	// 事务发送分配分片失败
		BPR_TRAFFIC_LIMIT			=-54,	// 流量限制
		BPR_HUGERECURSIVE_LIMIT		=-55,	// 循环转发层次太深
		BPR_PRIVATEBRIDGE_BREAK		=-56,	// 私有桥断开
		BPR_APPLAYER_BREAK			=-57,	// 应用层断开

		// 调用相关错误
		BPR_BADPARAMETER			=-60,	// 参数错误
		BPR_UNHANDLEDTIMEOUT		=-61,	// 超时未处理
		BPR_PROCEDURE				=-62,	// 子过程错误

		// 协议结构检查和调用错误
		BPR_UNPACK_ERROR			=-70,	// 消息解包失败
		BPR_PACK_ERROR				=-71,	// 消息封包失败
		BPR_ASSEMBLE_ERROR			=-72,	// 应用填包错误
		BPR_SOURCEIP_DANGER			=-73,	// 连接源地址不受信任
		BPR_CLIENTID_EMPTY			=-74,	// 客户号信息为空
		BPR_CLIENTID_DANGER			=-75,	// 客户号信息不受信任
		BPR_USER_NOTMATCH			=-76,	// 客户号不匹配
		BPR_USER_NOTLOGINED			=-77,	// 客户尚未进行登录
		BPR_USER_NORELOGIN			=-78,	// 客户已经登录,禁止重复登录
		BPR_BAD_COMPRESSTYPE		=-79,	// 压缩方式或者压缩类型非法
		BPR_BAD_ENCRYPTTYPE			=-80,	// 加密方式或者加密类型非法
		BPR_BAD_REQLEN				=-81,	// 请求长度错误
		BPR_BAD_REQSTRU				=-82,	// 请求结构错误
		BPR_BAD_OPTIONLEN			=-83,	// 选项区长度错误
		BPR_NO_PROTOCOLFAMILY		=-84,	// 协议簇无效
		BPR_NO_HANDLER				=-85,	// 处理模块不存在或无效
		BPR_NULL_ANS				=-86,	// 应答为空

		// IX协议相关错误
		BPR_IX_NOHANDLER			=-90,	// 找不到对应IX处理模块或IX处理模块无效
		BPR_IX_NOBUFFER				=-91,	// 对应IX协议应答缓冲区不足
		BPR_IX_BADSTRUCT			=-92,	// 创建IX结构失败

		// 其他错误
		BPR_EXCHG_KEY_ERROR			=-100,	// 密钥交换失败

		// 正确的编码
		BPR_SUCCESS					= 1,	// (任意过程)处理成功
		BPR_PENDING					= 2,	// (处理过程)事务正在处理过程中,需要进一步处理
		BPR_NORESULT				= 3,	// (处理过程)事务处理完成,但是不需要应答包
	} IOCPBPR;

	// 事务类型(参阅: iocpsvrmodel.h)
	typedef enum enumIOCPBTYPE
	{	BTYPE_ROSE,							// 客户端到服务器的请求(接收时分配)
		BTYPE_RROSE,						// 服务器到客户端的请求(发送时分配)
		BTYPE_OPUSHING,						// 出站推送(发送时分配)
		BTYPE_IPUSHING,						// 入站推送(接收时分配)
		BTYPE_INPROCESS,					// 进程内事务(调用时分配)
	} IOCPBTYPE;

	// 用户访问控制代码(参阅: iocpsvrcommon.h)
	typedef enum enumUSERACCESSCODE
	{	UAC_DEFAULT=0X0000000,					// 默认值
		UAC_AUTHORIZED=0X0000001,				// 授权用户
		UAC_PRIMARY=0X0000002,					// 主(界面)会话
		UAC_SERVANT=0X0000004,					// 服务会话
		UAC_PUSHABLE=0X0000008,					// 推送标志
	} USERACCESSCODE;
#endif
typedef IOCPBPR BPR;
typedef IOCPBTYPE BUTYPE;


//////////////////////////////////////////////////////////////////////////
// 原生协议内部标识
#ifndef PROT_FLAGS
#define PROT_FLAGS
	#define PF_MASK_ANSBUFTYPE		0X000F				// 应答缓冲类型
	#define PF_DEFSIZE				0X0000				// 默认包大小
	#define PF_SMALL				0X0001				// 小型包大小
	#define PF_MEDIUM				0X0002				// 中等包大小
	#define PF_LARGE				0X0003				// 大型包大小
	#define PF_HUGE					0X0004				// 巨大包大小

	#define PF_MASK_THREADTYPE		0X00F0				// 线程类型(掩码)
	#define PF_COMM_THREAD			0X0010				// 通讯类型事务
	#define PF_CORE_THREAD			0X0020				// 内部类型事务
	#define PF_SCHED_BUSINESS		0X0030				// 调度工作类型事务
	#define PF_BINDED_BUSINESS		0X0040				// 绑定工作类型事务

	#define PF_MASK_PROTFLAG		0X0F00				// 协议标识(掩码)
	#define PF_SECPROT				0X0100				// 安全协议(应强制加密)
	#define PF_IXPROT				0X0200				// 信息交换协议(应允许日志和跟踪)
	#define PF_DISABLED				0X0400				// 协议禁止(禁止注册)

	#define PF_MASK_EXTEND			0XF000				// 扩展标识(掩码)
	#define PF_EXT_ANSASYNC			0X1000				// 异步应答(延迟缓冲区申请)
	#define PF_EXT_TRACER			0X2000				// 协议可以跟踪
	#define PF_EXT_LOGGER			0X4000				// 协议可以日志
	#define PF_EXT_RETOUCH			0X8000				// 需要重新关联会话

	#define PF_MASK_SESSION			0X000F0000			// 会话标志
	#define PF_SESSION_NONE			0X00000000			// 不需要会话
	#define PF_SESSION_PERSIST		0X00010000			// 需要创建会话(长连接)
	#define PF_SESSION_NPERSIST		0X00020000			// 需要创建会话(短连接)
	#define PF_SESSION_REFER		0X00030000			// 需要引用会话
	#define PF_SESSION_OPTIONAL		0X00040000			// 需要创建或引用会话
#endif


// 原生协议错误级别和错误代码
#define EL_NOERROR					(0)				// 无错误
#define EL_PROTERROR				(1)				// 协议异常
#define EL_APPERROR					(2)				// IX处理错误
#define EC_NOERROR					(0)				// 无错误


// 常用协议宏定义
#define PFS_CommCall			PF_COMM_THREAD|PF_DEFSIZE
#define PFS_CommSmallCall		PF_COMM_THREAD|PF_SMALL
#define PFS_CoreCall			PF_CORE_THREAD|PF_DEFSIZE
#define PFS_CoreSmallCall		PF_CORE_THREAD|PF_SMALL
#define PFS_CoreAsyncCall		PF_CORE_THREAD|PF_EXT_ANSASYNC|PF_DEFSIZE
#define PFS_BindedCall			PF_BINDED_BUSINESS|PF_DEFSIZE
#define PFS_BindedSmallCall		PF_BINDED_BUSINESS|PF_SMALL
#define PFS_SchedCall			PF_SCHED_BUSINESS|PF_DEFSIZE
#define PFS_SchedSmallCall		PF_SCHED_BUSINESS|PF_SMALL

#define PFS_TouchCall			PF_CORE_THREAD|PF_SESSION_PERSIST|PF_DEFSIZE
#define PFS_TouchCallEx			PF_CORE_THREAD|PF_DEFSIZE
#define PFS_CommAppCall			PF_COMM_THREAD|PF_SESSION_REFER|PF_DEFSIZE
#define PFS_CoreAppCall			PF_CORE_THREAD|PF_SESSION_REFER|PF_DEFSIZE
#define PFS_CoreAsyncAppCall	PF_CORE_THREAD|PF_SESSION_REFER|PF_EXT_ANSASYNC|PF_DEFSIZE
#define PFS_SchedAppCall		PF_SCHED_BUSINESS|PF_SESSION_REFER|PF_DEFSIZE

#define PFS_TouchWebCall		PF_CORE_THREAD|PF_EXT_RETOUCH|PF_SMALL
#define PFS_CoreWebCall			PF_CORE_THREAD|PF_EXT_RETOUCH|PF_DEFSIZE
#define PFS_CoreWebSmallCall	PF_CORE_THREAD|PF_EXT_RETOUCH|PF_SMALL
#define PFS_SchedWebCall		PF_SCHED_BUSINESS|PF_EXT_RETOUCH|PF_DEFSIZE



// 主要接口
interface INull;						// 空接口
interface IObject;						// 核心对象接口
	interface IReferObject;				// 核心对象接口(可引用对象)
	interface IRemovableObject;			// 核心对象接口(可撤销对象)
	interface IProtectedObject;			// 核心对象接口(可保护对象)
	interface IReferObjectList;			// 核心对象列表
	interface IReferObjectArray;		// 核心对象数组
	interface IServer;					// 主控模块接口
	interface INotifySink;				// 通知接收器
		interface INSSessionManager;	// 会话管理通知接收器
		interface INSSSManager;			// 会话状态通知接收器
		interface INSConnectManager;	// 连接管理通知接收器
		interface INSMemoryDraft;		// 内存吃水管理通知接收器
	interface IUser;					// 用户对象
	interface ISession;					// SESSION接口
	interface IRoamSession;				// 漫游SESSION接口
	interface IConnect;					// 连接接口
	interface IStreamWriter;			// 连接流控制器
	interface IBusiness;				// 事务接口
interface IIXCategory;					// IX协议分类

// 模块实现的协议
interface ISDKInfo;						// SDK信息
interface ICoreModule;					// 核心模块
interface IServlet;						// 应用接口
interface IService;						// 服务接口
interface IProtocolDiscover;			// 协议检测器
interface IProtocolFamily;				// 模式协议簇
interface IProtocolEncoder;				// 协议编码器
interface IProtocolDecoder;				// 协议解码器
interface IProtocolDebugger;			// 协议调试器
interface IHandler;						// 协议处理器
	
interface IAsyncHandler;				// 异步协议处理器接口
interface IAsyncObject;					// 异步调用对象
interface IDbgHandler;					// 可监控协议处理器接口
interface IPushingHandler;				// 推送处理器接口




// 空对象接口
// (无IID定义)
interface INull {};
interface INull1 {};
interface INull2 {};
interface INull3 {};
interface INull4 {};
interface INull5 {};
interface INull6 {};


// 基本对象接口
// {CEE531B0-C2E5-49b2-A1EF-A91F6807961B}
static const IID IID_IObject = { 0xcee531b0, 0xc2e5, 0x49b2, { 0xa1, 0xef, 0xa9, 0x1f, 0x68, 0x7, 0x96, 0x1b } };
interface IObject
{	virtual LPVOID Cast(const IID & riid) PURE;
	virtual LPVOID GetObjectPtr() PURE;
	virtual BOOL IsObjectNull() const PURE;
};







//////////////////////////////////////////////////////////////////////////
// 协议定义相关结构







// IX协议定义
typedef struct tagIXPROTDEF
{	WORD		m_wFuncID;				// 功能ID
	LPCSTR		m_pszName;				// 功能名称
	WPARAM		m_wParam;				// 功能参数(一般存储IX过程标志)
	LPARAM		m_lParam;				// 功能参数(一般存储IX过程指针)
} IXPROTDEF;
typedef IXPROTDEF* LPIXPROTDEF;


// 协议描述(分析协议的处理结果)
typedef struct tagPROTINFO
{	BYTE		m_cProtVer;				// 当前事务的版本号
	WORD		m_wCmdNo;				// 当前事务的协议号
	CHAR		m_szCmdDesc[64];		// 请求描述
	DWORD		m_dwProtFlag;			// 内部标识(定义线程类别,是否IX协议,是否需要日志和跟踪等)
	DWORD		m_dwExtendPoolNo;		// 线程池(工作线程有效)
	DWORD		m_dwThreadSelector;		// 线程号(工作线程有效)
	IHandler*	m_pIHandler;			// 处理过程
	LPVOID		m_pProtDef;				// 协议定义
	BYTE		m_cFuncType;			// 功能类型
	WORD		m_wFuncID;				// 功能ID
} PROTINFO;
typedef PROTINFO* LPPROTINFO;



//////////////////////////////////////////////////////////////////////////
// 上下文定义相关宏定义
#define CNTX_INVALID	((BYTE)(~0))	// 无效对象
#define CNTX_ZERO		((BYTE)0)		// 空对象
#define CNTX_TEST		((BYTE)127)		// 测试对象
#define CNTX_USER		((BYTE)128)		// 用户对象(顺序分配)


// 会话处理上下文
#define SCNTX_SESSIONREF			1		// 会话引用对象
#define SCNTX_PRIVATEBRIDGECOUPLER	2		// 私有桥(接入服务器桥接DTE通道,可以包含多个通道)
#define SCNTX_SHAREBRIDGECOUPLER	3		// 共享桥(接入服务器桥接DTE服务器)
#define SCNTX_RPCNODE				4		// RPCNode信息
#define SCNTX_ARPCSESSION			5		// ARPC会话对象


// 连接处理上下文
#define CCNTX_CONNECTREF			1		// 连接引用对象
#define CCNTX_STREAMWRITER_0		2		// 流写出器(首个)
#define CCNTX_STREAMWRITER_MAX		11		// 流写出器(最后一个)


// 协议处理上下文
#define BCNTX_BUSINESSREF			1		// 事务引用对象
#define BCNTX_PARSERDATA			2		// 协议分析数据(接收包处理)
#define BCNTX_ENCODERPARAM			3		// 编码器参数(发送包处理)
#define BCNTX_PROTOCOLDECODER		4		// 默认解码器对象
#define BCNTX_PROTOCOLENCODER		5		// 默认编码器对象

#define BCNTX_IXHANDLER				6		// IX处理器上下文(框架上下文,仅IX协议有效),BUGBUG,将去掉,和架构有冲突

#define BCNTX_RAWREQ				10		// 原始请求上下文
#define BCNTX_RAWANS				11		// 原始应答上下文

#define BCNTX_HTTPREQ				13		// HTTP请求上下文
#define BCNTX_HTTPANS				14		// HTTP应答上下文

#define BCNTX_SIPREQ				15		// HTTP请求上下文
#define BCNTX_SIPANS				16		// HTTP应答上下文

#define BCNTX_FIXREQ				17		// HTTP请求上下文
#define BCNTX_FIXANS				18		// HTTP应答上下文

#define BCNTX_IXREQ					19		// IX请求上下文,BUGBUG,将去掉,和架构有冲突
#define BCNTX_IXANS					20		// IX应答上下文,BUGBUG,将去掉,和架构有冲突

#define BCNTX_ASYNCREPLY			21		// 异步应答接口



















//////////////////////////////////////////////////////////////////////////
// 高级对象定义


// 可引用对象接口
// {384DE26B-4C22-4068-B01A-0B27E98A818A}
static const IID IID_IReferObject = { 0x384de26b, 0x4c22, 0x4068, { 0xb0, 0x1a, 0xb, 0x27, 0xe9, 0x8a, 0x81, 0x8a } };
interface IReferObject : public IObject
{	virtual VOID AddRefObject() PURE;
	virtual VOID ReleaseObject() PURE;
};


// 可移除核心对象接口
// {79199CCF-C798-4fc6-8E3A-5800EFFEFB03}
static const IID IID_IRemovableObject = { 0x79199ccf, 0xc798, 0x4fc6, { 0x8e, 0x3a, 0x58, 0x0, 0xef, 0xfe, 0xfb, 0x3 } };
interface IRemovableObject : public IObject
{	virtual VOID ReleaseObject() PURE;
};

// 受保护核心对象接口
// {A4315B73-43B8-4fed-9524-E270A51BB624}
static const IID IID_IProtectedObject = { 0xa4315b73, 0x43b8, 0x4fed, { 0x95, 0x24, 0xe2, 0x70, 0xa5, 0x1b, 0xb6, 0x24 } };
interface IProtectedObject : public IObject
{	virtual VOID EnterAccess(BOOL bToRead) PURE;
	virtual VOID LeaveAccess(BOOL bToRead) PURE;
};


// 保护访问
class CProtectedAccess
{
public:
	CProtectedAccess(IObject* pIObject,BOOL bToRead)
		{	m_pIObject=pIObject;
			m_bToRead=bToRead;
			if(m_pIObject!=NULL)
			{	IProtectedObject* pIProtectedObject=(IProtectedObject*)m_pIObject->Cast(IID_IProtectedObject);
				if(pIProtectedObject!=NULL) pIProtectedObject->EnterAccess(bToRead);
			}
		}
	virtual~CProtectedAccess()
		{	Leave();
		}
	VOID Leave()
		{	if(m_pIObject!=NULL)
			{	IProtectedObject* pIProtectedObject=(IProtectedObject*)m_pIObject->Cast(IID_IProtectedObject);
				if(pIProtectedObject!=NULL) pIProtectedObject->LeaveAccess(m_bToRead);
				m_pIObject=NULL;
			}
		}
private:
	IObject* m_pIObject;
	BOOL m_bToRead;
};



// 对象列表
// {5E8245E0-44A0-4c1a-8F00-FB91A65F0AAC}
static const IID IID_IReferObjectList = { 0x5e8245e0, 0x44a0, 0x4c1a, { 0x8f, 0x0, 0xfb, 0x91, 0xa6, 0x5f, 0xa, 0xac } };
interface IReferObjectList : public IReferObject
{	virtual VOID RemoveAll() PURE;
	virtual BOOL IsEmpty() PURE;
	virtual LONG GetCount() PURE;
	virtual POSITION Find(IReferObject* pIReferObject,POSITION posStartAfter) const PURE;
	virtual POSITION FindIndex(LONG nIndex) const PURE;
	virtual POSITION GetHeadPosition() const PURE;
	virtual POSITION GetTailPosition() const PURE;
	virtual IReferObject* GetNext(POSITION& posObject) PURE;
	virtual IReferObject* GetPrev(POSITION& posObject) PURE;
	virtual IReferObject* GetAt(POSITION posObject) PURE;
	virtual IReferObject* GetNext(POSITION& posObject) const PURE;
	virtual IReferObject* GetPrev(POSITION& posObject) const PURE;
	virtual IReferObject* GetAt(POSITION posObject) const PURE;
	virtual POSITION AddHead(IReferObject* pIReferObject) PURE;
	virtual POSITION AddTail(IReferObject* pIReferObject) PURE;
	virtual POSITION InsertBefore(POSITION posObject,IReferObject* pIReferObject) PURE;
	virtual POSITION InsertAfter(POSITION posObject,IReferObject* pIReferObject) PURE;
	virtual VOID SetAt(POSITION posObject,IReferObject* pIReferObject) PURE;
	virtual VOID AddHead(IReferObjectList* pIReferObjectList) PURE;
	virtual VOID AddTail(IReferObjectList* pIReferObjectList) PURE;
	virtual IReferObject* RemoveHead() PURE;
	virtual IReferObject* RemoveTail() PURE;
	virtual VOID RemoveAt(POSITION posObject) PURE;
};



// 对象数组
// {E78EA95E-04DE-46ac-94C9-2A61A7B51D55}
static const IID IID_IReferObjectArray = { 0xe78ea95e, 0x4de, 0x46ac, { 0x94, 0xc9, 0x2a, 0x61, 0xa7, 0xb5, 0x1d, 0x55 } };
interface IReferObjectArray : public IReferObject
{	virtual VOID RemoveAll() PURE;
	virtual BOOL IsEmpty() PURE;
	virtual LONG GetSize() PURE;
	virtual VOID SetSize(LONG nSize) PURE;
	virtual VOID SetAt(LONG nIndex,IReferObject* pIReferObject) PURE;
	virtual IReferObject* GetAt(LONG nIndex) PURE;
};



// 用户标识信息
typedef struct tagUSERID
{	DWORD	m_dwUOrgID;			// 用户分支机构
	CHAR	m_szUID[UID_SIZE];	// 用户ID
} USERID;


// 主控模块(接口)
// {9D6558B5-F570-4b83-9717-2432D223199B}
static const IID IID_IServer = { 0x9d6558b5, 0xf570, 0x4b83, { 0x97, 0x17, 0x24, 0x32, 0xd2, 0x23, 0x19, 0x9b } };
interface IServer : public IObject
{
	// 注册和常量获取
	virtual LPCSTR GetHomeDir() const PURE;
	virtual LPCSTR GetConfigDir() const PURE;
	virtual LPCSTR GetLogDir() const PURE;
	virtual LPCSTR GetSwapDir() const PURE;
	virtual FLOAT  GetArchVer() const PURE;
	virtual LPCSTR GetArchBuild() const PURE;
	virtual LPCSTR GetArchIni() const PURE;
	virtual LPCSTR GetServicesXml() const PURE;
	virtual WORD GetServType() const PURE;
	virtual LONG GetLicenseType() const PURE;
	virtual LPCSTR GetLicenseFile() const PURE;
	virtual LONG GetLicenseStatus() const PURE;

	// 服务器控制
	typedef enum enumSERVERCONTROL
	{	SERVERCONTROL_STOP,
		SERVERCONTROL_RESTART,
	} SERVERCONTROL;
	virtual VOID ServerControl(SERVERCONTROL eServerControl) PURE;

	// 服务器服务信息
	virtual BOOL IsLoggerOn() const PURE;
	virtual LPCSTR GetQSID() const PURE;
	virtual DWORD GetServID() const PURE;
	virtual LPCSTR GetServName() const PURE;
	virtual LPCSTR GetServDesc() const PURE;
	virtual DWORD GetServVer() const PURE;
	virtual BYTE GetSessionAlgoType() const PURE;
	virtual BYTE GetSessionKeyLenIdx() const PURE;
	virtual BYTE IsInternalSignalOn() const PURE;
	virtual BYTE IsExternalSignalOn() const PURE;
	virtual BYTE GetHashAlgoType() const PURE;
	virtual BOOL IsCertificateOn() const PURE;
	virtual LONG GetStartupTime() const PURE;
	virtual LPCSTR GetAppShortName() const PURE;
	virtual LPCSTR GetAppName() const PURE;
	virtual DWORD GetMaxSessionNum() const PURE;
	virtual DWORD GetNowSessionNum() const PURE;
	virtual DWORD GetMaxConnectNum() const PURE;
	virtual DWORD GetNowConnectNum() const PURE;
	virtual DWORD GetMaxBufSize() const PURE;
	virtual DWORD GetReqUnitSize() const PURE;
	virtual DWORD GetAnsUnitSize() const PURE;

	// 服务器预警信息
	virtual BOOL GetAlarmStatus() const PURE;
	virtual VOID GetAlarmText(LPSTR pszAlarmText,DWORD cbAlarmText) const PURE;

	// 用户管理
	virtual IUser* GetSysUser() PURE;
	virtual IUser* GetConUser() PURE;
	virtual IUser* GetMACUser() PURE;
	virtual IUser* CreateUser() PURE;
	virtual BOOL SerializeUserR(IUser* pIUser,LPBYTE pArchive,DWORD cbArchive) PURE;
	virtual BOOL SerializeUserW(IUser* pIUser,LPBYTE pArchive,DWORD cbArchiveMax,DWORD& cbArchive) PURE;

	// 服务注册
	virtual BOOL RegisterModule(ICoreModule* pICoreModule) PURE;
	virtual BOOL RegisterService(LPCSTR pszService,IService* pIService) PURE;
	virtual BOOL RegisterServlet(LPCSTR pszServlet,IServlet* pIServlet) PURE;
	virtual BOOL RegisterProtocolDiscover(IProtocolDiscover* pIProtocolDiscover) PURE;
	virtual BOOL RegisterProtocolFamily(LPCSTR pszProtocolFamily,IProtocolFamily* pIProtocolFamily) PURE;
	virtual BOOL RegisterHandler(IHandler* pIHandler) PURE;
	virtual BOOL RegisterNotifySink(INotifySink* pINotifySink) PURE;
	virtual BOOL DeclareDependency(IService* pIService,LPCSTR pszServiceNeed) PURE;
	virtual BOOL DeclareExtend(LPCSTR pszMainService,IService* pIService) PURE;

	// 性能指示器
	virtual BOOL RegisterIndicator(LPCSTR pszName,BOOL bFlowOrLv,HANDLE hIndicator) PURE;
	virtual POSITION GetIndicator(LPCSTR pszName) PURE;
	virtual POSITION GetFirstIndicator() PURE;
	virtual VOID GetNextIndicator(POSITION& posIndicator) PURE;
	virtual LPCSTR GetIndicatorName(POSITION posIndicator) PURE;
	virtual BOOL GetIndicatorIsFlowOrLv(POSITION posIndicator) PURE;
	virtual HANDLE GetIndicatorHandle(POSITION posIndicator) PURE;

	// 用户上下文对象分配
	typedef enum enumUCCATEGORY
	{	UCCATEGORY_SC,
		UCCATEGORY_CC,
		UCCATEGORY_BC,
	} UCCATEGORY;
	virtual BYTE RegisterUserCntxClass(UCCATEGORY eUCCategory,LPCSTR pszName,DWORD cbObject,DESTRUCTOR pfnDestructor,CONNECTOR pfnConnector) PURE;
	virtual BYTE GetUserCntxClass(UCCATEGORY eUCCategory,LPCSTR pszName) PURE;
	virtual LPVOID AllocUserCntxObj(UCCATEGORY eUCCategory,BYTE cClassId,LPVOID pOwner) PURE;

	// 线程分配表注册
	virtual LONG RegisterTAT(LPCSTR pszName,DWORD dwThreadNum,LPCSTR pszComment) PURE;
	virtual LONG GetRegisteredTAT(LPCSTR pszName) PURE;
	virtual LONG GetThreadOffInTAT(LONG nTATDef) PURE;
	virtual LONG GetThreadNumInTAT(LONG nTATDef) PURE;

	// 日志处理
	virtual VOID AddInfoLog(LPCSTR lpszFmt,...) PURE;
	virtual VOID AddInfoLogV(LPCSTR lpszFmt,va_list args) PURE;
	virtual VOID AddErrorLog(LPCSTR lpszFmt,...) PURE;
	virtual VOID AddErrorLogV(LPCSTR lpszFmt,va_list args) PURE;
	virtual VOID AddRawCallLog(BOOL bResult,LPBYTE lpData,DWORD cbData) PURE;
	virtual VOID DirectLogger(DWORD dwSlotNo,LPBYTE lpData,DWORD cbData) PURE;
	virtual VOID DirectTracer(LPCSTR lpszFmt,...) PURE;
	virtual VOID DirectTracerV(LPCSTR lpszFmt,va_list args) PURE;

	// 事务日志转换输出
	virtual VOID BusinessToLogger(HANDLE hLogger,LPCBYTE pszBuf,DWORD cbBuf) PURE;
	virtual VOID BusinessToTraceWnd(HANDLE hTraceWnd,LPCSTR pszInfo) PURE;

	// 对象列表和数组处理
	virtual IReferObjectList* CreateObjectList(LONG nBlockSize) PURE;
	virtual IReferObjectArray* CreateObjectArray(LONG nGrowBy) PURE;

	// 服务,应用,协议簇注册访问
	virtual LPVOID GetRegisteredService(LPCSTR pszService,const IID & riid,BOOL bAddRef) PURE;
	virtual LPVOID GetRegisteredServlet(LPCSTR pszServlet,const IID & riid,BOOL bAddRef) PURE;
	virtual IProtocolFamily* GetRegisteredProtocolFamily(LPCSTR pszProtocolFamily) PURE;

	// 连接和会话处理
	virtual VOID EnumOnlineSessions(IReferObjectList* pIReferObjectList,BOOL bSkipShortLink) PURE;
	virtual VOID EnumNamedSessions(IReferObjectList* pIReferObjectList,BOOL bSkipShortLink,BOOL bMatchPrimary,DWORD dwUOrgID,LPCSTR pszUID) PURE;
	virtual VOID EnumOnlineConnects(IReferObjectList* pIReferObjectList,BOOL bHasSession) PURE;
	virtual ISession* OpenSession(DWORD idSession) PURE;
	virtual IConnect* OpenConnect(DWORD idConnect) PURE;
	virtual BOOL ShutdownSession(ISession* pISession,BPR nBPR) PURE;
	virtual BOOL ShutdownConnect(IConnect* pIConnect,BPR nBPR) PURE;
	virtual BOOL ShutdownSessionByID(DWORD idSession,BPR nBPR) PURE;
	virtual BOOL ShutdownConnectByID(DWORD idConnect,BPR nBPR) PURE;


	// 加密处理(用于额外加密和解密)
	virtual BYTE GetPKIBitIdx(BYTE cPKIType) const PURE;
	virtual LPCMD5BIN GetServPubKeyMD5(BYTE cPKIType) const PURE;
	virtual LPCBYTE GetServPubKeyPtr(BYTE cPKIType) const PURE;
	virtual LONG GetServPubKeyLen(BYTE cPKIType) const PURE;
	virtual LPCBYTE GetServPubKeySignPtr(BYTE cPKIType) const PURE;
	virtual DWORD GetServPubKeySignLen(BYTE cPKIType) const PURE;
	virtual BOOL BlowfishLightlyEncrypt(LPBYTE lpBuffer,int nLength) PURE;
	virtual BOOL BlowfishLightlyDecrypt(LPBYTE lpBuffer,int nLength) PURE;
	virtual BOOL Des3LightlyEncrypt(LPBYTE lpBuffer,int nLength) PURE;
	virtual BOOL Des3LightlyDecrypt(LPBYTE lpBuffer,int nLength) PURE;

	// 编码和解码处理
	virtual BPR BusinessDecoding(ISession* pISession,IConnect* pIConnect,IBusiness* pIBusiness,LONG nLevel) PURE;
	virtual BPR BusinessEncoding(ISession* pISession,IConnect* pIConnect,IBusiness* pIBusiness,LONG nLevel) PURE;

	// 封包和解包处理
	virtual BPR UnpackStdBuffer(ISession* pISession,IConnect* pIConnect,IBusiness* pIBusiness,
		LPBYTE pReqBody,DWORD cbPacket,DWORD cbRawLen,BYTE cCompressType,BYTE cEncryptType) PURE;
	virtual BPR PackStdBuffer(ISession* pISession,IConnect* pIConnect,IBusiness* pIBusiness,
		LPBYTE pAnsBody,DWORD cbRawLen,DWORD cbMaxAnsBody,BYTE& cCompressType,BYTE& cEncryptType,DWORD& cbPacket) PURE;
	virtual VOID GetSuggestPackStdParam(ISession* pISession,IConnect* pIConnect,IBusiness* pIBusiness,
		DWORD cbData,BYTE cDefEncryptType,BYTE& cCompressType,BYTE& cEncryptType) PURE;

	// 事务缓冲区处理
	virtual BPR PrepareWriteBufAndEncoder(IConnect* pIConnect,IBusiness* pIBusiness) PURE;

	// 协议异常处理
	virtual BPR ThrowProtocolError(IConnect* pIConnect,IBusiness* pIBusiness,LONG nFailCode,LPCSTR pszFormat,...) PURE;
	virtual BPR ThrowProtocolError(IConnect* pIConnect,IBusiness* pIBusiness,BOOL bAddPrefix,LONG nFailCode,LPCSTR pszFormat,...) PURE;
	virtual BPR ThrowProtocolErrorV(IConnect* pIConnect,IBusiness* pIBusiness,LONG nFailCode,LPCSTR pszFormat,va_list args) PURE;
	virtual BPR ThrowProtocolErrorV(IConnect* pIConnect,IBusiness* pIBusiness,BOOL bAddPrefix,LONG nFailCode,LPCSTR pszFormat,va_list args) PURE;

	// 异步事务处理(包含多包处理)
	virtual BPR AsyncAnswerBuffer(IBusiness* pIBusiness) PURE;
	virtual BPR AsyncComplete(IBusiness* pIBusiness,BOOL bEOR) PURE;
	virtual VOID AsyncException(IBusiness* pIBusiness,BOOL bAddPrefix,LONG nFailCode,LPCSTR pszFormat,...) PURE;
	virtual VOID AsyncExceptionV(IBusiness* pIBusiness,BOOL bAddPrefix,LONG nFailCode,LPCSTR pszFormat,va_list args) PURE;

	// 推送处理和反向事务处理基本方法
	virtual BPR CreateOPushingBusinessSpace(HANDLE& hBusinessSpace,LONG nBusinessNum) PURE;
	virtual VOID ReleaseBusinessSpace(HANDLE hBusinessSpace) PURE;
	virtual IBusiness* StrippingBusiness(HANDLE hBusinessSpace) PURE;
	virtual BPR CreateOPushingBusiness(IBusiness*& pIBusiness,HANDLE hBusinessSpace,DWORD idSession,LPCSTR pszEncoders,...) PURE;
	virtual BPR CreateReverseBusiness(IBusiness*& pIBusiness,HANDLE hBusinessSpace,DWORD idSession,LPCSTR pszEncoders,...) PURE;
	virtual BPR CompleteAndSendBusinessLL(IConnect* pIConnect,IBusiness* pIBusiness) PURE;
	virtual VOID AbortUnmanagedBusiness(IBusiness* pIBusiness,BPR nBPR) PURE;


	// AP节点管理和路由信息维护
	virtual BOOL RegisterAPNode(DWORD idAPNode,DWORD idSession) PURE;
	virtual BOOL UnregisterAPNode(DWORD idAPNode,DWORD idSession) PURE;
	virtual DWORD GetAvailableSessionOfAPNode(DWORD idAPNode) PURE;
	virtual ISession* OpenRouteSessionOfAPNode(DWORD idAPNodeUplink,DWORD idAPNode,DWORD idSession,BOOL bAlternate) PURE;
	virtual ISession* OpenRoamSessionOfAPNode(DWORD idAPNode,DWORD idSession) PURE;



	// 原始推送(低阶推送,分片推送,对端推送,不支持多级或需要自行处理路由转发)
	virtual BPR PushingLL(ISession* pISession,IConnect* pIConnect,LPCBYTE pOption,DWORD cbOption,LPBYTE pBody,DWORD cbBody,DWORD dwTransKey,WORD wCmdNo,LPCSTR pszCmdDesc,DWORD dwFragmentNo) PURE;
	virtual BPR PushingFragment(ISession* pISession,IConnect* pIConnect,IBusiness* pIBusiness,LPCBYTE pOption,DWORD cbOption,LPBYTE pBody,DWORD cbBody,DWORD dwFragmentNo) PURE;
	virtual BPR PushingS2C(ISession* pISession,IConnect* pIConnect,IUser* pIUser,LPCBYTE pOption,DWORD cbOption,LPBYTE pBody,DWORD cbBody,WORD wCmdNo,LPCSTR pszCmdDesc) PURE;



	// 直接推送(不支持多级别,因此不支持反射处理)
	virtual BPR PushingBySession(HANDLE hBusinessSpace,ISession* pISession,LPCSTR pszDesc,DWORD idPushingType,DWORD dwPushingOption,...) PURE;
	virtual BPR PushingBySessionV(HANDLE hBusinessSpace,ISession* pISession,LPCSTR pszDesc,DWORD idPushingType,DWORD dwPushingOption,va_list args) PURE;
	// 直接推送
	virtual BPR PushingDR_KICKOUT(HANDLE hBusinessSpace,ISession* pISession,LPCSTR pszDesc,LPCSTR pszAPFrom,IPV6 IpFrom,systm_t tOccur) PURE;
	virtual BPR PushingDR_MSGLL(HANDLE hBusinessSpace,ISession* pISession,LPCSTR pszDesc,LPCSTR pszMsg) PURE;
	virtual BPR PushingDR_MSG(HANDLE hBusinessSpace,ISession* pISession,LPCSTR pszDesc,LPCSTR pszFormat,...) PURE;
	virtual BPR PushingDR_IX20(HANDLE hBusinessSpace,ISession* pISession,LPCSTR pszDesc,BYTE cFuncType,WORD wFuncID,DWORD dwUOrgID,LPCBYTE pData,DWORD cbData)  PURE;
	virtual BPR PushingDR_TQL(HANDLE hBusinessSpace,ISession* pISession,LPCSTR pszDesc,LPCBYTE pData,DWORD cbData) PURE;
	virtual BPR PushingDR_TJS(HANDLE hBusinessSpace,ISession* pISession,LPCSTR pszDesc,LPCBYTE pData,DWORD cbData) PURE;
	virtual BPR PushingDR_LASTWORD(HANDLE hBusinessSpace,ISession* pISession,LPCSTR pszDesc,LPCSTR pszLastword) PURE;
	virtual BPR PushingDR_NOTICE(HANDLE hBusinessSpace,ISession* pISession,LPCSTR pszDesc,time_t tTime,LPCSTR pszNotice) PURE;
	virtual BPR PushingDR_URGENT(HANDLE hBusinessSpace,ISession* pISession,LPCSTR pszDesc,time_t tTime,DWORD dwUOrgID,LPCSTR pszUrgent) PURE;
	virtual BPR PushingDR_INSTRUCT(HANDLE hBusinessSpace,ISession* pISession,LPCSTR pszDesc,LPCSTR pszInstruct) PURE;


	// 路由推送路径处理
	virtual BOOL MakeSimpleAP(ISession* pISession,IConnect* pIConnect,LPSTR pszAP,DWORD cbAPMax) PURE;
	virtual DWORD GetAPLv(LPCSTR pszAP) PURE;
	virtual LPCSTR GetFortressAPNode(LPCSTR pszAP,LPSTR pszAPNode,DWORD cbAPNode) PURE;
	virtual LPCSTR GetNearAPNode(LPCSTR pszAP) PURE;
	virtual DWORD GetAPNodeID(LPCSTR pszAPNode) PURE;
	virtual DWORD GetAPNodeSessionID(LPCSTR pszAPNode) PURE;
	virtual LPCSTR GetAPNodeTracker(LPCSTR pszAPNode) PURE;
	virtual BOOL AddToAPNode(LPSTR pszAP,DWORD cbAPMax,ISession* pISession,IConnect* pIConnect) PURE;
	virtual BOOL PulloutNearAPNode(LPSTR pszAP) PURE;
	// 路由推送以及相关的推送反射
	virtual BPR PushingByRoute(HANDLE hBusinessSpace,LPCSTR pszAP,BOOL bUserID,LPVOID pUser,LPCSTR pszDesc,DWORD idPushingType,DWORD dwPushingOption,...) PURE;
	virtual BPR PushingByRouteV(HANDLE hBusinessSpace,LPCSTR pszAP,BOOL bUserID,LPVOID pUser,LPCSTR pszDesc,DWORD idPushingType,DWORD dwPushingOption,va_list args) PURE;
	virtual BPR PushingReflectByRoute(DWORD idPushingType,DWORD dwPushingOption,LPBYTE pSequence,DWORD cbSequeue) PURE;
	// 路由推送相关高级功能
	virtual BPR PushingRT_KICKOUT(HANDLE hBusinessSpace,LPCSTR pszAP,BOOL bUserID,LPVOID pUser,LPCSTR pszDesc,LPCSTR pszAPFrom,IP IpFrom,systm_t tOccur) PURE;
	virtual BPR PushingRT_MSGLL(HANDLE hBusinessSpace,LPCSTR pszAP,BOOL bUserID,LPVOID pUser,LPCSTR pszDesc,LPCSTR pszMsg) PURE;
	virtual BPR PushingRT_MSG(HANDLE hBusinessSpace,LPCSTR pszAP,BOOL bUserID,LPVOID pUser,LPCSTR pszDesc,LPCSTR pszFormat,...) PURE;
	virtual BPR PushingRT_IX20(HANDLE hBusinessSpace,LPCSTR pszAP,BOOL bUserID,LPVOID pUser,LPCSTR pszDesc,BYTE cFuncType,WORD wFuncID,DWORD dwUOrgID,LPCBYTE pData,DWORD cbData) PURE;
	virtual BPR PushingRT_TQL(HANDLE hBusinessSpace,LPCSTR pszAP,BOOL bUserID,LPVOID pUser,LPCSTR pszDesc,LPCBYTE pData,DWORD cbData) PURE;
	virtual BPR PushingRT_TJS(HANDLE hBusinessSpace,LPCSTR pszAP,BOOL bUserID,LPVOID pUser,LPCSTR pszDesc,LPCBYTE pData,DWORD cbData) PURE;
	virtual BPR PushingRT_LASTWORD(HANDLE hBusinessSpace,LPCSTR pszAP,BOOL bUserID,LPVOID pUser,LPCSTR pszDesc,LPCSTR pszLastword) PURE;
	virtual BPR PushingRT_NOTICE(HANDLE hBusinessSpace,LPCSTR pszAP,BOOL bUserID,LPVOID pUser,LPCSTR pszDesc,time_t tTime,LPCSTR pszNotice) PURE;
	virtual BPR PushingRT_URGENT(HANDLE hBusinessSpace,LPCSTR pszAP,BOOL bUserID,LPVOID pUser,LPCSTR pszDesc,time_t tTime,DWORD dwUOrgID,LPCSTR pszUrgent) PURE;
	virtual BPR PushingRT_INSTRUCT(HANDLE hBusinessSpace,LPCSTR pszAP,BOOL bUserID,LPVOID pUser,LPCSTR pszDesc,LPCSTR pszInstruct) PURE;




	// 漫游推送以及相关的推送反射
	virtual BPR PushingByRoam(HANDLE hBusinessSpace,IRoamSession* pIRoamSession,LPCSTR pszDesc,DWORD idPushingType,DWORD dwPushingOption,...) PURE;
	virtual BPR PushingByRoamV(HANDLE hBusinessSpace,IRoamSession* pIRoamSession,LPCSTR pszDesc,DWORD idPushingType,DWORD dwPushingOption,va_list args) PURE;
	virtual BPR PushingReflectByRoam(DWORD idPushingType,DWORD dwPushingOption,LPBYTE pSequence,DWORD cbSequeue) PURE;
	// 漫游推送相关高级功能
	virtual BPR PushingRO_KICKOUT(HANDLE hBusinessSpace,IRoamSession* pIRoamSession,LPCSTR pszDesc,LPCSTR pszAPFrom,IP IpFrom,systm_t tOccur) PURE;
	virtual BPR PushingRO_MSGLL(HANDLE hBusinessSpace,IRoamSession* pIRoamSession,LPCSTR pszDesc,LPCSTR pszMsg) PURE;
	virtual BPR PushingRO_MSG(HANDLE hBusinessSpace,IRoamSession* pIRoamSession,LPCSTR pszDesc,LPCSTR pszFormat,...) PURE;
	virtual BPR PushingRO_IX20(HANDLE hBusinessSpace,IRoamSession* pIRoamSession,LPCSTR pszDesc,BYTE cFuncType,WORD wFuncID,DWORD dwUOrgID,LPCBYTE pData,DWORD cbData) PURE;
	virtual BPR PushingRO_TQL(HANDLE hBusinessSpace,IRoamSession* pIRoamSession,LPCSTR pszDesc,LPCBYTE pData,DWORD cbData) PURE;
	virtual BPR PushingRO_TJS(HANDLE hBusinessSpace,IRoamSession* pIRoamSession,LPCSTR pszDesc,LPCBYTE pData,DWORD cbData) PURE;
	virtual BPR PushingRO_LASTWORD(HANDLE hBusinessSpace,IRoamSession* pIRoamSession,LPCSTR pszDesc,LPCSTR pszLastWord) PURE;
	virtual BPR PushingRO_NOTICE(HANDLE hBusinessSpace,IRoamSession* pIRoamSession,LPCSTR pszDesc,time_t tTime,LPCSTR pszNotice) PURE;
	virtual BPR PushingRO_URGENT(HANDLE hBusinessSpace,IRoamSession* pIRoamSession,LPCSTR pszDesc,time_t tTime,DWORD dwUOrgID,LPCSTR pszUrgent) PURE;
	virtual BPR PushingRO_INSTRUCT(HANDLE hBusinessSpace,IRoamSession* pIRoamSession,LPCSTR pszDesc,LPCSTR pszInstruct) PURE;




	// 链式推送以及相关的推送反射
	virtual BPR PushingByChain(IBusiness* pIBusiness,LPCSTR pszDesc,DWORD idPushingType,DWORD dwPushingOption,...) PURE;
	virtual BPR PushingByChainV(IBusiness* pIBusiness,LPCSTR pszDesc,DWORD idPushingType,DWORD dwPushingOption,va_list args) PURE;
	virtual BPR PushingReflectByChain(IBusiness* pIBusinessHost,DWORD idPushingType,DWORD dwPushingOption,LPBYTE pSequence,DWORD cbSequeue) PURE;
	// 链式推送相关高级功能(用户托管,权限管理,QOS管理,用户状态管理)
	virtual BPR ManageEndingUser(IBusiness* pIBusiness,BYTE cZoneID,DWORD dwUOrgID,LPCSTR pszUOrg,LPCSTR pszUID,DWORD dwRoleID,LPCSTR pszUName,DWORD dwAccessCode) PURE;
	virtual BPR ManagePermission(IBusiness* pIBusiness,LPCSTR pszPermission) PURE;
	virtual BPR ManageQOSOption(IBusiness* pIBusiness,BOOL bHAMode,LONG nSoftQPC,LONG nSoftCPC,LONG nSoftFPC) PURE;
	virtual BPR ManageSessionStatus(IBusiness* pIBusiness,DWORD dwAddFlags,DWORD dwRemoveFlags,DWORD dwData1,DWORD dwData2) PURE;



	// 服务器内推送处理
	virtual BPR S2SPushingDispatch(ISession* pISession,IConnect* pIConnect,IBusiness* pIBusinessHost,DWORD dwPushingLv,DWORD idPushingType,DWORD dwPushingOption,LPBYTE pSequence,DWORD cbSequence) PURE;



	// 服务器内部管理(用户托管)
	virtual BPR ManageLocalUser(ISession* pISession,IConnect* pIConnect,IBusiness* pIBusiness) PURE;



	// 服务器内部管理(安全,版本,内存,线程)
	virtual DWORD GetDefaultCredit() const PURE;
	virtual DWORD GetCrisisCredit() const PURE;
	virtual VOID ChangeCreditOfSourceIp(IP Ip,DWORD dwToCredit,IUser* pIUser,LPCSTR pszDescription) PURE;
	virtual VOID ChangeCreditOfClientIp(IP Ip,DWORD dwToCredit,IUser* pIUser) PURE;
	virtual VOID ChangeCreditOfClientMac(MAC Mac,DWORD dwToCredit,IUser* pIUser) PURE;
	virtual VOID RestoreCreditOfSourceIp(IP Ip,IUser* pIUser) PURE;
	virtual VOID RestoreCreditOfClientIp(IP Ip,IUser* pIUser) PURE;
	virtual VOID RestoreCreditOfClientMac(MAC Mac,IUser* pIUser) PURE;
	virtual BOOL IsSourceIpFrozen(IP Ip) PURE;
	virtual BOOL IsClientIpFrozen(IP Ip) PURE;
	virtual BOOL IsClientMacFrozen(MAC Mac) PURE;
	virtual VOID EnumSourceIps(VOID (*pfnCallback)(IP&,LPVOID,LPVOID),LPVOID pParam) PURE;
	virtual VOID EnumClientIps(VOID (*pfnCallback)(IP&,LPVOID,LPVOID),LPVOID pParam) PURE;
	virtual VOID EnumClientMacs(VOID (*pfnCallback)(MAC&,LPVOID,LPVOID),LPVOID pParam) PURE;
	virtual VOID EnumVersions(VOID (*pfnCallback)(LPVOID,LPVOID),LPVOID pParam) PURE;
	virtual VOID EnumMemorys() PURE;
	virtual VOID EnumThreads() PURE;
};


// 通知接收器
// {ADAAA54A-66FC-41af-808B-A35C787E2BEE}
static const IID IID_INotifySink = { 0xadaaa54a, 0x66fc, 0x41af, { 0x80, 0x8b, 0xa3, 0x5c, 0x78, 0x7e, 0x2b, 0xee } };
interface INotifySink : public IObject
{
};


// 会话管理通知接收器
// {27D4A505-6142-45dc-B1C7-EEF83E47CDD1}
static const IID IID_INSSessionManager = { 0x27d4a505, 0x6142, 0x45dc, { 0xb1, 0xc7, 0xee, 0xf8, 0x3e, 0x47, 0xcd, 0xd1 } };
interface INSSessionManager : public INotifySink
{	virtual VOID OnSessionOnline(ISession* pISession) PURE;
	virtual VOID OnSessionOffline(ISession* pISession) PURE;
};

// 会话状态通知接收器
// {4CB72F15-B0DC-4807-9B1F-1F515968BA36}
static const IID IID_INSSSManager = { 0x4cb72f15, 0xb0dc, 0x4807, { 0x9b, 0x1f, 0x1f, 0x51, 0x59, 0x68, 0xba, 0x36 } };
interface INSSSManager : public INotifySink
{	virtual VOID OnSessionSSModified(ISession* pISession) PURE;

};

// 连接管理通知接收器
// {92CC2E5B-8D77-4368-8E94-446F75C101F1}
static const IID IID_INSConnectManager = { 0x92cc2e5b, 0x8d77, 0x4368, { 0x8e, 0x94, 0x44, 0x6f, 0x75, 0xc1, 0x1, 0xf1 } };
interface INSConnectManager : public INotifySink
{	virtual VOID OnConnectRejected(IP SourceIp,WORD wSourcePort,LONG nCause) PURE;
	virtual VOID OnConnectCreated(IConnect* pIConnect) PURE;
	virtual VOID OnConnectDestroyed(IConnect* pIConnect,LONG nCause,LONG nCauseParam) PURE;
	virtual VOID OnAutoReduceCreditOfConnect(IConnect* pIConnect,LONG nCause,LONG nCauseParam,DWORD dwReduceCredit) PURE;
};


// 内存吃水管理通知接收器
// {839F5A55-8D6B-47c4-B1DE-9A206B0051D8}
static const IID IID_INSMemoryDraft = { 0x839f5a55, 0x8d6b, 0x47c4, { 0xb1, 0xde, 0x9a, 0x20, 0x6b, 0x0, 0x51, 0xd8 } };
interface INSMemoryDraft : public INotifySink
{	virtual VOID OnMemoryDraftLvChanged(LONG nOldMemoryDraftLv,LONG nNewMemoryDraftLv) PURE;
};


// 用户对象接口
// {F4BE5923-6C46-40ef-865E-48E94D550039}
static const IID IID_IUser = { 0xf4be5923, 0x6c46, 0x40ef, { 0x86, 0x5e, 0x48, 0xe9, 0x4d, 0x55, 0x0, 0x39 } };
interface IUser : public IRemovableObject
{
	// 基本操作
	virtual VOID EmptyAPInfo() PURE;
	virtual VOID EmptyConnectInfo() PURE;
	virtual VOID EmptyEntryPoint() PURE;
	virtual VOID EmptyUserInfo() PURE;
	virtual VOID UpdateAPInfo(IUser* pIUser) PURE;
	virtual VOID UpdateConnectInfo(IUser* pIUser) PURE;
	virtual VOID UpdateEntryPoint(IUser* pIUser) PURE;
	virtual VOID UpdateUserProfile(IUser* pIUser) PURE;
	
	virtual VOID ZeroUser() PURE;
	virtual VOID CopyUserData(IUser* pIUser) PURE;
	virtual VOID CopyUserData(BOOL bUserID,LPVOID pUser) PURE;

	// 登录位置相关属性
	virtual VOID SetAPInfo(DWORD dwAPServID,DWORD dwAPSessionID) PURE;
	virtual DWORD GetAPServID() const PURE;
	virtual DWORD GetAPSessionID() const PURE;

	// 相关位置和版本信息
	virtual VOID SetConnectInfo(LPCSTR pszDevice,const IP& EthernetIp,const IP& InternetIp,const MAC& Mac,LPCSTR pszBuildName,WORD wType,DWORD dwVersion) PURE;
	virtual VOID SetDevice(LPCSTR pszDevice) PURE;
	virtual VOID SetEthernetIp(const IP& Ip) PURE;
	virtual VOID SetInternetIp(const IP& Ip) PURE;
	virtual VOID SetMac(const MAC& Mac) PURE;
	virtual VOID SetBuildName(LPCSTR pszBuildName) PURE;
	virtual VOID SetClientType(WORD wType) PURE;
	virtual VOID SetClientVer(DWORD dwVersion) PURE;
	virtual LPCSTR GetDevice() const PURE;
	virtual IP GetEthernetIp() const PURE;
	virtual IP GetInternetIp() const PURE;
	virtual MAC GetMac() const PURE;
	virtual LPCSTR GetBuildName() const PURE;
	virtual WORD GetClientType() const PURE;
	virtual DWORD GetClientVer() const PURE;

	// 入口点信息
	virtual VOID SetEntryPoint(WORD wEntryPoint) PURE;
	virtual WORD GetEntryPoint() PURE;

	// 相关用户信息
	virtual VOID SetUserProfile(BYTE cZoneID,DWORD dwUOrgID,LPCSTR pszUOrg,LPCSTR pszUID,DWORD dwRoleID,LPCSTR pszUName,DWORD dwAccessCode) PURE;
	virtual VOID SetZoneID(BYTE cZoneID) PURE;
	virtual VOID SetUOrgID(DWORD dwUOrgID) PURE;
	virtual VOID SetUOrg(LPCSTR pszUOrg) PURE;
	virtual VOID SetUID(LPCSTR pszUID) PURE;
	virtual VOID SetRoleID(DWORD dwRoleID) PURE;
	virtual VOID SetUName(LPCSTR pszUName) PURE;
	virtual VOID SetAccessCode(DWORD dwAccessCode) PURE;
	virtual BYTE GetZoneID() PURE;
	virtual DWORD GetUOrgID() PURE;
	virtual LPCSTR GetUOrg() PURE;
	virtual LPCSTR GetUID() PURE;
	virtual DWORD GetRoleID() PURE;
	virtual LPCSTR GetUName() PURE;
	virtual DWORD GetAccessCode() PURE;
};
// 常用角色ID定义
#define ROLE_ANONYMOUS		0
#define ROLE_UNKNOWNUSR		1
#define ROLE_SYSTEMS		100000
#define ROLE_SYSTEM			(ROLE_SYSTEMS+0)
#define ROLE_CONSOLE		(ROLE_SYSTEMS+1)
#define ROLE_MACHINE		(ROLE_SYSTEMS+2)
#define ROLE_RPCUSER		(ROLE_SYSTEMS+3)




// SESSION接口
// {096A963F-4CDE-42a3-9578-A5EBD3AAAA51}
static const IID IID_ISession = { 0x96a963f, 0x4cde, 0x42a3, { 0x95, 0x78, 0xa5, 0xeb, 0xd3, 0xaa, 0xaa, 0x51 } };
interface ISession : public IReferObject
{
	// 获取会话ID
	virtual DWORD GetSessionNo() const PURE;
	virtual DWORD GetSessionID() const PURE;
	virtual BOOL IsPersistentMode() const PURE;

	// 会话基本数据
	virtual const systm_t GetCreatedTime() const PURE;
	virtual const systm_t GetAnnounceTime() const PURE;

	// 密钥交换
	virtual BOOL ExchangeSessionKeyPKI(BYTE cPKIType,LPBYTE pClientPubKey,LONG cbClientPubKey,LPBYTE lpSignature,DWORD cbSignature,LPBYTE pSessionKey,LONG cbSessionKey,WORD* lpwSessionKey) PURE;
	virtual BOOL ExchangeSessionKeyNoPKI(LPCSTR pszSessionKey) PURE;
	virtual BOOL ExchangeSessionKeyNoPKI(LPSTR pszSessionKey,DWORD cbSessionKey) PURE;
	virtual BOOL SetBlowfishKey(LPCSTR pszKey) PURE;
	virtual BOOL SetDes3Key(LPCSTR pszKey) PURE;
	virtual BOOL IsSessionKeyValid() PURE;
	virtual BOOL IsBlowfishKeyValid() PURE;
	virtual BOOL IsDes3KeyValid() PURE;

	// 设置和获取会话属性(连接信息,入口点,用户信息,登录标志)
	virtual VOID UpdateConnectInfo(IUser* pIUser) PURE;
	virtual VOID UpdateEntryPoint(IUser* pIUser) PURE;
	virtual VOID UpdateUserProfile(IUser* pIUser) PURE;
	virtual VOID UpdateUserData(IUser* pIUser) PURE;
	virtual IUser* GetCreator() PURE;

	// 上下文对象
	virtual LPVOID AllocCntxObj(BYTE cType,LPCSTR pszName,DWORD cbObject,DESTRUCTOR pfnDestructor,CONNECTOR pfnConnector) PURE;
	virtual LPVOID FindCntxObj(BYTE cType) PURE;
	virtual LPVOID FindCntxObj(BYTE cType,const IID & riid) PURE;
	virtual VOID DestroyCntxObjs() PURE;
	#define CREATE_SC_OBJECT(SESSION,TYPE,NAME,CLASS) ::new(SESSION->AllocCntxObj(TYPE,NAME,sizeof(CLASS),&CLASS::__Destructor,&CLASS::__Connector)) CLASS
	#define CREATE_SC_STRUCT(SESSION,TYPE,NAME,CLASS) ::new(SESSION->AllocCntxObj(TYPE,NAME,sizeof(CLASS),NULL,NULL)) CLASS
	#define CREATE_SC_BUFFER(SESSION,TYPE,NAME,BUFSIZE) (LPBYTE)SESSION->AllocCntxObj(TYPE,NAME,BUFSIZE,NULL,NULL)
	#define CREATE_SUC_OBJECT(SESSION,TYPE,CLASS) ::new(m_pIServer->AllocUserCntxObj(IServer::UCCATEGORY_SC,TYPE,(LPVOID)((ISession*)SESSION))) CLASS
	#define CREATE_SUC_STRUCT(SESSION,TYPE,CLASS) ::new(m_pIServer->AllocUserCntxObj(IServer::UCCATEGORY_SC,TYPE,(LPVOID)((ISession*)SESSION))) CLASS
	#define CREATE_SUC_BUFFER(SESSION,TYPE) (LPBYTE)m_pIServer->AllocUserCntxObj(IServer::UCCATEGORY_SC,TYPE,(LPVOID)((ISession*)SESSION)))

	// 会话其他属性
	virtual const BOOL IsSessionOnline() const PURE;
	virtual const BOOL IsAuthorized() const PURE;
	virtual const BOOL IsPrimary() const PURE;
	virtual const BOOL IsServant() const PURE;
	virtual const BOOL IsPushable() const PURE;
	virtual const BOOL IsEndPointSession() const PURE;

	// 会话缓存信息控制
	virtual BOOL LockSessionExData(LPBYTE& pData,LPDWORD& pcbUsed,DWORD& cbMax) PURE;
	virtual VOID UnlockSessionExData() PURE;

	// 会话销毁
	virtual VOID DestroyTheSession() PURE;

	// 获取关联的连接ID
	virtual BOOL IsConnectRelated() const PURE;
	virtual DWORD GetRelatedConnectID() const PURE;
	virtual IConnect* QueryRelatedConnect() PURE;

	// 会话锁定
	virtual VOID LockSession() PURE;
	virtual VOID UnlockSession() PURE;

	// 状态管理
	virtual VOID ModifySS(DWORD dwAddFlags,DWORD dwRemoveFlags,DWORD dwData1,DWORD dwData2) PURE;
	virtual DWORD GetSSFlags() const PURE;
	virtual DWORD GetSSData1() const PURE;
	virtual DWORD GetSSData2() const PURE;

	// 更新应用统计数据
	virtual VOID CounterAppCall(LPCSTR pszAppCallName) PURE;
	virtual const systm_t GetLastAppCallTime() const PURE;
	virtual const LPCTSTR GetLastAppCallName() const PURE;
	virtual const DWORD GetHisAppCallNum() const PURE;
};



// 漫游SESSION接口
// {697364E5-FD3A-4769-90C9-B488A09F3A9B}
static const IID IID_IRoamSession = { 0x697364e5, 0xfd3a, 0x4769, { 0x90, 0xc9, 0xb4, 0x88, 0xa0, 0x9f, 0x3a, 0x9b } };
interface IRoamSession : public IReferObject
{	virtual DWORD GetAPNodeID() const PURE;
	virtual DWORD GetSessionID() const PURE;
	virtual DWORD GetUOrgID() const PURE;
	virtual LPCSTR GetUID() const PURE;
	virtual DWORD GetUserStatus() const PURE;
	virtual DWORD GetUserData1() const PURE;
	virtual DWORD GetUserData2() const PURE;
};


// 连接接口
// {FF64D81A-ACE6-441d-A473-240A42D93E81}
static const IID IID_IConnect = { 0xff64d81a, 0xace6, 0x441d, { 0xa4, 0x73, 0x24, 0xa, 0x42, 0xd9, 0x3e, 0x81 } };
interface IConnect : public IReferObject
{
	// 对象处理
	virtual IProtocolFamily* GetProtocolFamily() PURE;
	virtual DWORD GetConnectID() const PURE;

	// 连接相关信息设置
	virtual VOID SetProtocolInfo(IProtocolFamily* pIProtocolFamily,WORD wProtocolType,WORD wProtocolVer) PURE;
	virtual VOID SetSourceIp(const IP& Ip) PURE;
	virtual VOID SetMultiplexerMode() PURE;
	virtual VOID SetHAMode(BOOL bHAMode) PURE;
	virtual VOID SetSoftQPC(LONG nSoftQPC) PURE;
	virtual VOID SetSoftCPC(LONG nSoftCPC) PURE;
	virtual VOID SetSoftFPC(LONG nSoftFPC) PURE;

	// 连接相关信息获取
	virtual BOOL IsProtocolKnown() const PURE;
	virtual IProtocolFamily* GetProtocolFamily() const PURE;
	virtual WORD GetProtocolType() const PURE;
	virtual WORD GetProtocolVer() const PURE;
	virtual IP GetSourceIp() const PURE;
	virtual BOOL IsMultiplexerMode() const PURE;

	// 上下文对象
	virtual LPVOID AllocCntxObj(BYTE cType,LPCSTR pszName,DWORD cbObject,DESTRUCTOR pfnDestructor,CONNECTOR pfnConnector) PURE;
	virtual LPVOID FindCntxObj(BYTE cType) PURE;
	virtual LPVOID FindCntxObj(BYTE cType,const IID & riid) PURE;
	virtual VOID DestroyCntxObjs() PURE;
	#define CREATE_CC_OBJECT(CONNECT,TYPE,NAME,CLASS) ::new(CONNECT->AllocCntxObj(TYPE,NAME,sizeof(CLASS),&CLASS::__Destructor,&CLASS::__Connector)) CLASS
	#define CREATE_CC_STRUCT(CONNECT,TYPE,NAME,CLASS) ::new(CONNECT->AllocCntxObj(TYPE,NAME,sizeof(CLASS),NULL,NULL)) CLASS
	#define CREATE_CC_BUFFER(CONNECT,TYPE,NAME,BUFSIZE) (LPBYTE)CONNECT->AllocCntxObj(TYPE,NAME,BUFSIZE,NULL,NULL)
	#define CREATE_CUC_OBJECT(CONNECT,TYPE,CLASS) ::new(m_pIServer->AllocUserCntxObj(IServer::UCCATEGORY_CC,TYPE,(LPVOID)((IConnect*)CONNECT))) CLASS
	#define CREATE_CUC_STRUCT(CONNECT,TYPE,CLASS) ::new(m_pIServer->AllocUserCntxObj(IServer::UCCATEGORY_CC,TYPE,(LPVOID)((IConnect*)CONNECT))) CLASS
	#define CREATE_CUC_BUFFER(CONNECT,TYPE) (LPBYTE)m_pIServer->AllocUserCntxObj(IServer::UCCATEGORY_CC,TYPE,(LPVOID)((IConnect*)CONNECT)))

	// 会话相关处理
	virtual BOOL IsSessionRelated() const PURE;
	virtual DWORD GetRelatedSessionID() const PURE;
	virtual ISession* QueryRelatedSession() PURE;
	virtual ISession* CreateRelatedSession(BOOL bPersistentMode) PURE;
	virtual VOID DestroyRelatedSession() PURE;
	virtual UINT64 GetRelatedSessionGUID() const PURE;

	// 数据流处理
	virtual BOOL CreateStreamWriter(BYTE cType,LPCSTR pszName,WORD wCmdNo,DWORD cbCache) PURE;
	virtual IStreamWriter* GetStreamWriter(BYTE cType) PURE;
};


// 数据流接口
// {7AF0F422-AEA8-4b7e-96F1-8C57C6B40A9E}
static const IID IID_IStreamWriter = { 0x7af0f422, 0xaea8, 0x4b7e, { 0x96, 0xf1, 0x8c, 0x57, 0xc6, 0xb4, 0xa, 0x9e } };
interface IStreamWriter : public IObject
{	virtual VOID LockUpdate() PURE;
	virtual VOID UnlockUpdate() PURE;
	virtual BOOL Write(LPBYTE pData,DWORD cbData) PURE;
};




// 事务接口
// {91232EA6-30DD-4dbb-88D2-8676F3F7BC82}
static const IID IID_IBusiness = { 0x91232ea6, 0x30dd, 0x4dbb, { 0x88, 0xd2, 0x86, 0x76, 0xf3, 0xf7, 0xbc, 0x82 } };
interface IBusiness : public IReferObject
{
	// 相关ID和相关标志获取
	virtual DWORD GetConnectID() const PURE;
	virtual DWORD GetBusinessID() const PURE;
	virtual DWORD GetBusinessType() const PURE;
	virtual BOOL IsNetDrive() const PURE;
	virtual BOOL IsPassive() const PURE;

	// 输入缓冲区以及相关信息获取
	virtual LPBYTE GetReadBuf() PURE;
	virtual DWORD GetReadBufSize() const PURE;
	virtual DWORD GetReadLength() const PURE;
	virtual BYTE GetReadProtVer() const PURE;
	virtual WORD GetReadCmdNo() const PURE;
	virtual DWORD GetReadFragmentNo() const PURE;

	// 上下文对象(协议处理栈)
	virtual LPVOID AllocCntxObj(BYTE cType,LPCSTR pszName,DWORD cbObject,DESTRUCTOR pfnDestructor,CONNECTOR pfnConnector) PURE;
	virtual LPVOID FindCntxObj(BYTE cType) PURE;
	virtual LPVOID FindCntxObj(BYTE cType,const IID & riid) PURE;
	virtual VOID DestroyCntxObjs() PURE;
	#define CREATE_BC_OBJECT(BUSINESS,TYPE,NAME,CLASS) ::new(BUSINESS->AllocCntxObj(TYPE,NAME,sizeof(CLASS),&CLASS::__Destructor,&CLASS::__Connector)) CLASS
	#define CREATE_BC_STRUCT(BUSINESS,TYPE,NAME,CLASS) ::new(BUSINESS->AllocCntxObj(TYPE,NAME,sizeof(CLASS),NULL,NULL)) CLASS
	#define CREATE_BC_BUFFER(BUSINESS,TYPE,NAME,BUFSIZE) (LPBYTE)BUSINESS->AllocCntxObj(TYPE,NAME,BUFSIZE,NULL,NULL)
	#define CREATE_BUC_OBJECT(BUSINESS,TYPE,CLASS) ::new(m_pIServer->AllocUserCntxObj(IServer::UCCATEGORY_BC,TYPE,(LPVOID)((IBusiness*)BUSINESS))) CLASS
	#define CREATE_BUC_STRUCT(BUSINESS,TYPE,CLASS) ::new(m_pIServer->AllocUserCntxObj(IServer::UCCATEGORY_BC,TYPE,(LPVOID)((IBusiness*)BUSINESS))) CLASS
	#define CREATE_BUC_BUFFER(BUSINESS,TYPE) (LPBYTE)m_pIServer->AllocUserCntxObj(IServer::UCCATEGORY_BC,TYPE,(LPVOID)((IBusiness*)BUSINESS)))

	// 事务相关信息获取和更新
	virtual DWORD GetTransKey() const PURE;
	virtual WORD GetCmdNo() const PURE;
	virtual LPCSTR GetCmdDesc() const PURE;
	virtual LPVOID GetHandler(const IID & riid) PURE;
	virtual BYTE GetIXFuncType() const PURE;
	virtual WORD GetIXFuncID() const PURE;
	virtual LPVOID GetIXHandler(const IID & riid) PURE;
	virtual VOID RenewTransKey(DWORD dwTransKey) PURE;
	virtual VOID RenewCmdNo(WORD wCmdNo) PURE;
	virtual VOID RenewCmdDesc(LPCSTR pszCmdDesc) PURE;
	virtual VOID SetForceCompressZlib() PURE;
	virtual VOID SetForceEncryptSession() PURE;
	virtual VOID SetForceEncryptBlowfish() PURE;
	virtual VOID SetForceEncryptDes3() PURE;

	// 用户位置版本信息以及用户资料信息
	// 请参考ISession::SetConnectInfo,ISession::SetUserProfile
	virtual IUser* GetCaller() PURE;
	virtual VOID SetToBeOnline() PURE;
	virtual VOID SetToBeShutSend() PURE;
	virtual VOID SetToBeDisconnect() PURE;

	// 应答缓冲区处理
	virtual LPBYTE GetWriteBuf() PURE;
	virtual DWORD GetWriteBufSize() const PURE;	
	virtual DWORD GetWriteLength() const PURE;
	virtual BYTE GetWriteProtVer() const PURE;
	virtual WORD GetWriteCmdNo() const PURE;
	virtual DWORD GetWriteFragmentNo() const PURE;

	// 事务应答缓冲区处理和处理状态获取
	virtual VOID SetAnsState(LONG nErrorLevel,LONG nErrorCode,LPCSTR pszState) PURE;
	virtual VOID SetAnsCompleted(WORD wAnsNo,DWORD dwFragmentNo) PURE;
	virtual VOID SetWriteLength(DWORD cbWrite) PURE;
	virtual BOOL IsAnsCompleted() const PURE;
	virtual BOOL IsExceptionAns() const PURE;
	virtual DWORD GetFailCode() const PURE;

	// 事务信息
	virtual VOID SetInfo(DWORD cbTotalLength) PURE;
	virtual DWORD GetTotalLength() const PURE;
};





















// SDK信息
// {2236FAC0-6D2C-4250-BEF3-6D396717A2E7}
static const IID IID_ISDKInfo = { 0x2236fac0, 0x6d2c, 0x4250, { 0xbe, 0xf3, 0x6d, 0x39, 0x67, 0x17, 0xa2, 0xe7 } };
interface ISDKInfo : public IObject
{	virtual DWORD GetSDKVer() const PURE;
};


// 核心模块
// {FEE61687-CC0F-4337-A5A4-39A4414D39DF}
static const IID IID_ICoreModule = { 0xfee61687, 0xcc0f, 0x4337, { 0xa5, 0xa4, 0x39, 0xa4, 0x41, 0x4d, 0x39, 0xdf } };
interface ICoreModule : public IObject
{	virtual LPCSTR GetName() const PURE;
	virtual BOOL Start() PURE;
	virtual BOOL Ready() PURE;
	virtual VOID Shut() PURE;
	virtual VOID Stop() PURE;
	virtual VOID Final() PURE;
};


// 应用接口
// {5B944A34-F78A-46ea-B6BF-B59AC953E5C2}
static const IID IID_IServlet= { 0x5b944a34, 0xf78a, 0x46ea, { 0xb6, 0xbf, 0xb5, 0x9a, 0xc9, 0x53, 0xe5, 0xc2 } };
interface IServlet : public IObject
{	virtual LPCSTR GetName() const PURE;
	virtual ICoreModule* GetModule() const PURE;
	virtual VOID AddCaller() PURE;
	virtual LONG GetCallerCnt() PURE;
	virtual BOOL Configure() PURE;
	virtual BOOL Start() PURE;
	virtual BOOL Ready() PURE;
	virtual VOID Shut() PURE;
	virtual VOID Stop() PURE;
	virtual VOID Final() PURE;
};


// 服务接口
//		有关服务初始化顺序和接口关系
//			启动过程:
//				1.模块装载:		本过程产生服务实例,各模块禁止相互调用
//				2.Configure:	各模块配置过程,可以查找模块,声明依赖关系(DeclareDependency),调用模块的配置接口
//				3.Start:		模块启动(单线程),可以调用依赖模块(可能不安全)
//			运行过程:
//				1.模块运行:		模块运行阶段,可以对全部服务进行安全调用
//			停止过程:
//				1.Shut:			模块关闭,切断各模块关联,关闭全部后台线程,可以调用依赖模块(可能不安全)
//				2.线程回收:		回收全部外部线程,切断对模块的调用
//				3.Stop:			模块停止(单线程),回收其资源
//				4.Final:		模块内部资源回收
//				5.模块卸载:		模块干净卸载
// {126EFC39-9EB6-497c-9397-0A0210B0D0CA}
static const IID IID_IService = { 0x126efc39, 0x9eb6, 0x497c, { 0x93, 0x97, 0xa, 0x2, 0x10, 0xb0, 0xd0, 0xca } };
interface IService : public IObject
{
	// 服务类型
	typedef enum enumSERVICESTYLE
	{	SERVICE_CORE=1,			// 核心服务(不需要配置)
		SERVICE_EXTEND=2,		// 扩展服务(需要配置)
		SERVICE_OPTIONAL=4,		// 可选服务(有引用才启动)
	} SERVICESTYLE;
	// 服务状态
	typedef enum enumSERVICESTATUS
	{	SERVICEST_NOTRUNNING,	// 未运行
		SERVICEST_RUNNING,		// 正在运行
		SERVICEST_SHUTDOWNING,	// 正在关闭
		SERVICEST_SHUTDOWN,		// 已经关闭
		SERVICEST_STOPING,		// 正在停止
		SERVICEST_STOPPED,		// 已经停止
	} SERVICESTATUS;
	// 服务基本接口
	virtual LPCSTR GetName() const PURE;
	virtual ICoreModule* GetModule() const PURE;
	virtual VOID AddCaller() PURE;
	virtual LONG GetCallerCnt() PURE;
	virtual SERVICESTYLE GetServiceStyle() PURE;
	virtual SERVICESTATUS GetServiceStatus() PURE;
	virtual VOID UpdateServiceStatus(SERVICESTATUS eServiceStatus) PURE;
	virtual BOOL Configure() PURE;
	virtual BOOL Start() PURE;
	virtual BOOL Ready() PURE;
	virtual VOID Shut() PURE;
	virtual VOID Stop() PURE;
	virtual VOID Final() PURE;
};


// 协议管理器
// {5EF022F2-43A6-4480-BC82-154E2DE5F210}
static const GUID IID_IProtocolDiscover = { 0x5ef022f2, 0x43a6, 0x4480, { 0xbc, 0x82, 0x15, 0x4e, 0x2d, 0xe5, 0xf2, 0x10 } };
interface IProtocolDiscover : public IObject
{
	// 得到模块
	virtual ICoreModule* GetModule() const PURE;

	// 协议检测
	virtual VOID CollectProtocolFamilys() PURE;
	virtual BOOL DetectProtocolInfo(IConnect* pIConnect,LPCBYTE pReq,DWORD cbReq,DWORD& cbPrefix) PURE;
};


// 推送类型(包括:对端路由推送,链式推送,服务器推送,参见:客户端推送模型)
typedef enum enumPUSHINGTYPE
{	PUSHING_UNKNOWN,			// 未知类型

	PUSHING_S2C=100,			// 服务器到客户端推送
	PUSHING_SHOUT,				//		呼叫通知(暂时不支持)
	PUSHING_KICKOUT,			//		踢出通知(LPCSTR pszAPFrom,IPV6 IpFrom,systm_t tOccur)
	PUSHING_MSG,				//		消息通知(LPCSTR pszMsg)
	PUSHING_IX20,				//		传统IX协议(BYTE cFuncType,WORD wFuncID,DWORD dwUOrgID,LPCBYTE pData,DWORD cbData)
	PUSHING_TQL,				//		TQL协议(LPCBYTE pData,DWORD cbData)
	PUSHING_TJS,				//		TJS协议(LPCBYTE pData,DWORD cbData)
	PUSHING_LASTWORD,			//		服务器挂起错误(LPCSTR pszMsg)
	PUSHING_NOTICE,				//		发布有新的服务器公告(time_t tTime,LPCSTR pszNotice)
	PUSHING_URGENT,				//		发布有新的分支机构公告(time_t tTime,DWORD dwUOrgID,LPCSTR pszUrgent)
	PUSHING_INSTRUCT,			//		通知指令(LPCSTR pszInstruct)

	PUSHING_S2S=600,			// 服务器到服务器推送
	PUSHING_USERMANAGE,			//		用户托管(无参数)
	PUSHING_CONNRESET,			//		连接重置(无参数)
	PUSHING_PERMISSION,			//		用户权限管理
	PUSHING_QOSCTRL,			//		QOS控制(连接队列,事务链深度,流量限制,高可用设置
	PUSHING_SSMANAGE,			//		状态控制(用户状态,状态数据123)
	PUSHING_MAXTYPE,			// 最大类型
} PUSHINGTYPE;

// 推送选项
typedef enum enumPUSHINGOPTION
{	PUSHING_TO_DEFAULT=0,		// 推送默认选项
	PUSHING_TO_WHERE=0XF,		// 目标服务器
	PUSHING_TO_LOCAL=1,			// 本服务器
	PUSHING_TO_CLIENT=2,		// 推送到客户端
	PUSHING_TO_PORTAL=3,		// 推送到接入服务器
	PUSHING_TO_NEIGHBOR=4,		// 推送到邻居服务器
} PUSHINGOPTION;



// 协议簇
// {82A0928C-959F-4cc0-9FA8-5F344CC162C4}
static const IID IID_IProtocolFamily = { 0x82a0928c, 0x959f, 0x4cc0, { 0x9f, 0xa8, 0x5f, 0x34, 0x4c, 0xc1, 0x62, 0xc4 } };
interface IProtocolFamily : public IObject
{
	// 获取所在模块
	virtual ICoreModule* GetModule() const PURE;

	// 处理模块注册和处理
	virtual VOID OnFamilyRegistered() PURE;
	virtual VOID OnFamilyToBeReady() PURE;
	virtual BOOL RegisterProtocols(IHandler* pIHandler,LPVOID pProtDefs,LONG nCount,DWORD cbProtDef) PURE;

	// 协议分析
	virtual DWORD MessageSeparate(IConnect* pIConnect,LPCBYTE pReq,DWORD cbReq,DWORD& dwTransKey,DWORD& eMsgType,DWORD& dwFragmentNo,DWORD& cbMsgBufNeed,DWORD& dwRelatedBufType,LPBYTE pParserData,DWORD cbMaxParserData,DWORD& cbParserData) const PURE;

	// 事务初始化
	virtual BPR BusinessInitializeForeign(IConnect* pIConnect,IBusiness* pIBusiness,LPBYTE pParserData,DWORD cbParserData) PURE;
	virtual BPR BusinessInitializeLocal(IConnect* pIConnect,IBusiness* pIBusiness,LPCSTR pszEncoders,va_list argsEncoders) PURE;
	virtual BPR BusinessRenderEncoders(IBusiness* pIBusiness,LPCSTR pszEncoders,...) PURE;
	virtual BPR BusinessRenderEncodersV(IBusiness* pIBusiness,LPCSTR pszEncoders,va_list argsEncoders) PURE;

	// 事务准备
	virtual BPR ParseInfo(IConnect* pIConnect,IBusiness* pIBusiness,LPPROTINFO pProtInfo) PURE;

	// 会话恢复
	virtual UINT64 GetRelatedSessionGUIDToTouch(IConnect* pIConnect,IBusiness* pIBusiness) PURE;

	// 协议预处理和处理
	virtual BPR PreExecute(ISession* pISession,IConnect* pIConnect,IBusiness* pIBusiness) PURE;
	virtual BPR Execute(ISession* pISession,IConnect* pIConnect,IBusiness* pIBusiness) PURE;

	// 错误协议组装
	virtual BPR AssembleProtocolError(IConnect* pIConnect,IBusiness* pIBusiness,BOOL bAddPrefix,LONG nFailCode,LPCSTR pszFormat,va_list args) PURE;

	// 推送处理
	virtual BPR ForwardPushingLL(ISession* pISession,IConnect* pIConnect,LPCBYTE pOption,DWORD cbOption,LPBYTE pBody,DWORD cbBody,DWORD dwTransKey,WORD wCmdNo,LPCSTR pszCmdDesc,DWORD dwFragmentNo) PURE;
	virtual BPR ForwardPushingFragment(ISession* pISession,IConnect* pIConnect,IBusiness* pIBusiness,LPCBYTE pOption,DWORD cbOption,LPBYTE pBody,DWORD cbBody,DWORD dwFragmentNo) PURE;
	virtual BPR ForwardPushingS2C(ISession* pISession,IConnect* pIConnect,IUser* pIUser,LPCBYTE pOption,DWORD cbOption,LPBYTE pBody,DWORD cbBody,WORD wCmdNo,LPCSTR pszCmdDesc) PURE;
	virtual BPR ForwardPushingBySession(HANDLE hBusinessSpace,ISession* pISession,IConnect* pIConnect,LPCSTR pszDesc,DWORD dwPushingLv,DWORD idPushingType,DWORD dwPushingOption,DWORD_PTR wParam,DWORD_PTR lParam) PURE;
	virtual BPR ForwardPushingByRoute(HANDLE hBusinessSpace,ISession* pISession,IConnect* pIConnect,LPCSTR pszAP,BOOL bUserID,LPVOID pUser,LPCSTR pszDesc,DWORD dwPushingLv,DWORD idPushingType,DWORD dwPushingOption,DWORD_PTR wParam,DWORD_PTR lParam) PURE;
	virtual BPR ForwardPushingByRoam(HANDLE hBusinessSpace,ISession* pISession,IConnect* pIConnect,DWORD idAPNode,DWORD idSession,DWORD dwUOrgID,LPCSTR pszUID,LPCSTR pszDesc,DWORD dwPushingLv,DWORD idPushingType,DWORD dwPushingOption,DWORD_PTR wParam,DWORD_PTR lParam) PURE;
	virtual BPR ForwardPushingByChain(ISession* pISession,IConnect* pIConnect,IBusiness* pIBusinessHost,LPCSTR pszDesc,DWORD dwPushingLv,DWORD idPushingType,DWORD dwPushingOption,DWORD_PTR wParam,DWORD_PTR lParam) PURE;

	// 其他辅助处理
	virtual VOID WriteBusinessToLogger(ISession* pISession,IConnect* pIConnect,IBusiness* pIBusiness,BOOL bRequest,HANDLE hWriter) PURE;
	virtual VOID WriteBusinessToTracer(ISession* pISession,IConnect* pIConnect,IBusiness* pIBusiness,BOOL bRequest,HANDLE hTraceWnd) PURE;
};


// 协议编码器
// {B0AF603D-0118-484f-9CE6-A19845292049}
static const IID IID_IProtocolEncoder = { 0xb0af603d, 0x118, 0x484f, { 0x9c, 0xe6, 0xa1, 0x98, 0x45, 0x29, 0x20, 0x49 } };
interface IProtocolEncoder : public IObject
{	virtual LONG EncoderGetLevel() PURE;
	virtual BPR EncoderFormat(ISession* pISession,IConnect* pIConnect,IBusiness* pIBusiness) PURE;
	virtual BPR EncoderRewind(ISession* pISession,IConnect* pIConnect,IBusiness* pIBusiness) PURE;
	virtual BPR EncoderRendering(ISession* pISession,IConnect* pIConnect,IBusiness* pIBusiness) PURE;
};


// 协议解码器
// {6C11AE6C-7F5C-49f6-9C1F-B598AE9F354B}
static const IID IID_IProtocolDecoder = { 0x6c11ae6c, 0x7f5c, 0x49f6, { 0x9c, 0x1f, 0xb5, 0x98, 0xae, 0x9f, 0x35, 0x4b } };
interface IProtocolDecoder : public IObject
{	virtual LONG DecoderGetLevel() PURE;
	virtual BPR DecoderRendering(ISession* pISession,IConnect* pIConnect,IBusiness* pIBusiness) PURE;
};


// 协议调试器
// {AD97B734-374F-4cf4-ABA9-05EC75A4B24E}
static const IID IID_IProtocolDebugger = { 0xad97b734, 0x374f, 0x4cf4, { 0xab, 0xa9, 0x5, 0xec, 0x75, 0xa4, 0xb2, 0x4e } };
interface IProtocolDebugger : public IObject
{
};


// 协议处理器基类
// {02F7CDED-B595-4f1b-9D4A-6CEED744C56D}
static const IID IID_IHandler = { 0x2f7cded, 0xb595, 0x4f1b, { 0x9d, 0x4a, 0x6c, 0xee, 0xd7, 0x44, 0xc5, 0x6d } };
interface IHandler : public IObject
{	virtual ICoreModule* GetModule() const PURE;
	virtual BOOL Configure() PURE;
	virtual BOOL AttachServer() PURE;
	virtual BOOL AttachBackstage() PURE;
	virtual VOID DetachServer() PURE;
};


//////////////////////////////////////////////////////////////////////////
// 各协议处理器上下问对象和协议处理器类
#include "ts_defineraw.h"
#include "ts_definehttp.h"
#include "ts_definesip.h"
#include "ts_definefix.h"






// 异步协议处理器接口
// {5E1ACBB6-1F8F-4d91-918B-972DD79D5F72}
static const IID IID_IAsyncHandler = { 0x5e1acbb6, 0x1f8f, 0x4d91, { 0x91, 0x8b, 0x97, 0x2d, 0xd7, 0x9d, 0x5f, 0x72 } };
interface IAsyncHandler : public IObject
{	virtual BOOL GetAsyncBuffer(IBusiness* pIBusiness,LPBYTE& pAnsBody,DWORD& cbAnsBodyMax) PURE;
	virtual BOOL SetAsyncDataReady(IBusiness* pIBusiness,IObject* pIObject) PURE;
};


// 异步调用对象
// {4CA90C71-E0A6-4e65-87A4-EE3FC0618FBC}
static const IID IID_IAsyncObject = { 0x4ca90c71, 0xe0a6, 0x4e65, { 0x87, 0xa4, 0xee, 0x3f, 0xc0, 0x61, 0x8f, 0xbc } };
interface IAsyncObject : public IObject
{	virtual BOOL IsFailed() const PURE;
	virtual LONG GetFailCode() const PURE;
	virtual LPCSTR GetFailInfo() const PURE;
	virtual DWORD GetTotalLength() const PURE;
	virtual DWORD GetFragmentNo() const PURE;
	virtual LPBYTE GetReply() const PURE;
	virtual DWORD GetReplySize() const PURE;
};



// 可监控协议处理器接口
//		当前接口用于实现事务处理过程中的本标准日志和输出过程
//		实现实例:
//			m_pIServer->BusinessToLogger(hLogger,(LPCBYTE)"HANDLE:HELLO\r\n",12);
//			m_pIServer->BusinessToTraceWnd(hTraceWnd,"HANDLE:HELLO\r\n");
// {0D5FC4D1-640D-47f9-8414-DA7BE629E6FB}
static const IID IID_IDbgHandler = { 0xd5fc4d1, 0x640d, 0x47f9, { 0x84, 0x14, 0xda, 0x7b, 0xe6, 0x29, 0xe6, 0xfb } };
interface IDbgHandler : public IObject
{	virtual VOID WriteBusinessToLogger(ISession* pISession,IConnect* pIConnect,IBusiness* pIBusiness,BOOL bRequest,HANDLE hLogger) PURE;
	virtual VOID WriteBusinessToTracer(ISession* pISession,IConnect* pIConnect,IBusiness* pIBusiness,BOOL bRequest,HANDLE hTraceWnd) PURE;
};



// 推送处理器
// {58F4CBFE-98FA-49be-B3A6-88BAE31FF32B}
static const IID IID_IPushingHandler = { 0x58f4cbfe, 0x98fa, 0x49be, { 0xb3, 0xa6, 0x88, 0xba, 0xe3, 0x1f, 0xf3, 0x2b } };
interface IPushingHandler : public IObject
{	virtual BPR OnPushing(ISession* pISession,IConnect* pIConnect,IBusiness* pIBusinessHost,DWORD dwPushingLv,DWORD idPushingType,DWORD dwPushingOption,LPBYTE pSequence,DWORD cbSequence) PURE;
};



#include "ts_easyuse.inl"


#define USE_DEPRECATION
#ifdef USE_DEPRECATION
	#define INMServer IServer
	#define INMSession ISession
	#define INMConnect IConnect
	#define INMBusiness IBusiness
#endif

#pragma pack()
#endif
