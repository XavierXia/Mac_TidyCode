#ifndef __TC_COMMON__H__
#define __TC_COMMON__H__
#pragma pack(1)

#ifdef ASELIB_API
	// 计划任务设置信息
	typedef LONG (CALLBACK* PTCFUNC)(DWORD_PTR dwTaskData,DWORD_PTR dwTaskId);
	typedef struct ASELIB_API tagTCTASKSETINFO
	{	DWORD			m_tBeginTime;			// 计划任务开始执行时间
		DWORD			m_dwTaskData;			// 计划任务数据
		DWORD			m_dwPeriod;				// 执行周期
		DWORD			m_bSkipOnBusy;			// 是否在繁忙的时候忽略
		PTCFUNC			m_pfnTaskFunc;			// 任务回调过程
		tagTCTASKSETINFO()
		{	memset(this,0,sizeof(tagTCTASKSETINFO));
		}
	} TCTASKSETINFO,*LPTCTASKSETINFO;
	// 原始调用
	typedef LONG (CALLBACK* PTCRAWCALLFN)(PVOID pFuncCnt,LPBYTE lpIn,DWORD cbIn,LPBYTE lpOut,DWORD cbOutMax,DWORD& cbOut);
	typedef struct ASELIB_API tagTCRAWCALL
	{	WORD		   m_wReqNo;				// 协议号
		LPCSTR		   m_lpszCmdDesc;			// 协议秒数
		BYTE		   m_cThreadType;			// 线程类型: 0-通讯线程 1-核心线程 2-工作线程
		BYTE		   m_cWriteBufType;			// 写缓冲区类别: 0-小型包大小 1-中等包大小 2-大型包大小 3-巨大包大小 100-默认大小
		BYTE		   m_cEncrpyted;			// 是否要求加密 0-不要求加密 1-必须加密
		WORD		   m_wMinReqLen;			// 最小请求包大小(字节)
		WORD		   m_wMinAnsLen;			// 最小应答包大小(字节)
		PTCRAWCALLFN  m_pfnRawCallFn;			// 功能回调函数
	} TCRAWCALL,*LPTCRAWCALL;

	// 本地用户对象
	typedef struct ASELIB_API tagLOCALUINFO
	{	DWORD		   m_dwSessionID;			// 会话ID
		DWORD		   m_dwBranchID;			// 营业部ID
 		CHAR		   m_szKHH[UID_SIZE];		// 客户号信息
		DWORD		   m_dwData;				// 扩充数据
	} LOCALUINFO,*LPLOCALUINFO;
	// 全局用户对象
	typedef struct ASELIB_API tagGLOBALUINFO
	{	WORD		   m_wUOrg;					// 营业部ID(全局模式)
		CHAR		   m_szUID[UID_GSIZE];		// 客户号信息(全局模式)
		BYTE		   m_cServId;				// 服务器ID(0XFF为空)
	} GLOBALUINFO,*LPGLOBALUINFO;

	// 通知信息
	typedef struct ASELIB_API tagTCNOTIFYINFO
	{	DWORD		   m_dwBranchID;			// 营业部ID
		CHAR		   m_szKHH[MAX_PATH];		// 客户号信息
		BYTE		   m_cFuncType;				// 功能类型
		WORD		   m_wFuncID;				// 功能号
		DWORD		   m_dwReserved;			// 保留字段
	} TCNOTIFYINFO,*LPTCNOTIFYINFO;
	// 通知信息(原始方式)
	typedef struct ASELIB_API tagTCRAWNOTIFYINFO
	{	DWORD		   m_dwSessionID;			// 会话ID
 		DWORD		   m_dwBranchID;			// 营业部ID
 		CHAR		   m_szKHH[MAX_PATH];		// 客户号信息
		BYTE		   m_cFuncType;				// 功能类型
		WORD		   m_wFuncID;				// 功能号
		DWORD		   m_dwReserved;			// 保留字段
	} RAWTCNOTIFYINFO,*LPTCRAWNOTIFYINFO;
	// 转发消息
	typedef struct ASELIB_API tagTCRELAYINFO
	{	DWORD		   m_dwSessionID;			// 源会话ID(确认消息时必须填写)
		WORD		   m_wUOrg;					// 营业部ID(全局模式)
		CHAR		   m_szUID[UID_GSIZE];		// 客户号信息(全局模式)
		BYTE		   m_cFuncType;				// 功能类型
		WORD		   m_wFuncID;				// 功能号
		BYTE		   m_cFlags;				// 标志位
		DWORD		   m_dwReserved;			// 保留
	} TCRELAYINFO,*LPTCRELAYINFO;
#endif

#ifndef RELAY_FLAGS
#define RELAY_FLAGS
	#define RELAYF_USECOUNTER	0X01			// 使用中继记数器
	#define RELAYF_ADDCOUNTER	0X02			// 中继计数器增减(发送:增加接收者记数 确认:减发送者记数)
	#define RELAYF_COMPRESS		0X04			// 强制使用压缩模式
	#define RELAYF_ENCRYPTED	0X08			// 强制使用加密模式
#endif

// 回调过程类型定义
//		nDataType							lpCode				lpData			cbData			dwReserved		Result		功能
#define SYSTEM_INFO_DATA		200		//	N/A					(LPCSTR)		N/A				N/A				0			显示系统信息,提示信息内容,以\0结尾
#define SYSTEM_ERROR_DATA		201		//	N/A					(LPCSTR)		N/A				N/A				0			显示错误信息,提示信息内容,以\0结尾
#define FEM_INFO_LOG			203		//	N/A					日志内容		日志长度		LOWORD=功能号	0			写入业务日志(正常)
#define FEM_ERROR_LOG			204		// 	N/A					日志内容		日志长度		LOWORD=功能号	0			写入业务日志(错误)
#define FEM_INSERTTASK_DATA		205		//	(LPTASKSETINFO)		(LPDWORD)任务ID	sizeof(DWORD)	N/A				0			插入计划任务
#define FEM_REMOVETASK_DATA		206		//	N/A					(DWORD)任务ID	N/A				N/A				0			删除计划任务

#define FEM_REGISTERRAWCALL		207		//  N/A					(LPTCRAWCALL)	缓冲区长度		N/A				0			登记原始调用入口地址(非原生模式支持)

#define FEM_GETMEMPOOLUSED		208		//  N/A					(LPLONG)已用	sizeof(LONG)	N/A				0			获取当前内存池实用
#define FEM_GETMEMPOOLMAX		209		//  N/A					(LPLONG)可用	sizeof(LONG)	N/A				0			获取当前内存池最大

#define FEM_FINBUSINESSASYNC	210		//  N/A					(HANDLE)句柄	BCRET_PROC_XX	N/A				0			结束异步事务(非原生模式支持)

#define FEM_GETCASTPOOLUSED		211		//  N/A					(LPLONG)已用	sizeof(LONG)	N/A				0			获取当前广播内存池实用
#define FEM_GETCASTPOOLALERT	212		//  N/A					(LPLONG)警戒	sizeof(LONG)	N/A				0			获取当前广播内存池警戒
#define FEM_GETCASTPOOLMAX		213		//  N/A					(LPLONG)最大	sizeof(LONG)	N/A				0			获取当前广播内存池最大

#define FEM_GETRELAYCOUNTERS	214		//  N/A					(LPLOCALUINFO)	缓冲区长度		N/A				0			获取指定(本地)用户中继计数器
#define FEM_RSTRELAYCOUNTERS	215		//  N/A					(LPLOCALUINFO)	缓冲区长度		N/A				0			重置指定(本地)用户中继计数器

#define FEM_GETLOCALCONNS		216		//  N/A					(LPLOCALUINFO)	缓冲区长度		N/A				实际条数	获取本站连接信息
#define FEM_GETLOCALNEWCONNS	217		//  (CONNECTID)			(LPLOCALUINFO)	缓冲区长度		N/A				实际条数	获取增量本站连接信息
#define FEM_GETLOCALUSERS		218		//  N/A					(LPLOCALUINFO)	缓冲区长度		N/A				实际条数	获取本站用户信息
#define FEM_GETLOCALNEWUSERS	219		//  (CONNECTID)			(LPLOCALUINFO)	缓冲区长度		N/A				实际条数	获取增量本站用户信息

#define FEM_GETGLOBALUSERS		220		//  N/A					(LPGLOBALUINFO)	缓冲区长度		N/A				实际条数	获取全网用户信息(非后台连接)
#define FEM_GETGLOBALUSERSTATE	221		//  N/A					(LPGLOBALUINFO)	缓冲区长度		N/A				记录条数	获取全网用户状态(非后台连接)

#define	FEM_GETHSGPHQDATA1		101		//	股票代码			(LPHQSCINFO)	缓冲区长度		LOWORD=市场+1	成功返回0	获取行情数据
#define FEM_NOTIFY				102		//	(LPTCNOTIFYINFO)	通知数据		通知数据长度	N/A				0			发送通知数据
#define FEM_GETHSGPHQDATA2		103		//	股票代码			(LPHQSCINFO2)	缓冲区长度		LOWORD=市场+1	成功返回0	获取行情数据
#define FEM_GETHQSTATE			104		//	N/A					(LPBOOL)		N/A				N/A				0			获取行情数据状态
#define FEM_GETHKGPHQDATA		105		//	股票代码			(LPHKHQINFO)	缓冲区长度		LOWORD=市场		成功返回0	获取港股行情数据
#define FEM_GETHKHQSTATE		106		//	N/A					(LPBOOL)		N/A				N/A				0			获取港股行情数据状态
#define FEM_GETSTOCKENUNAME		107		//	股票代码			英文名缓冲区	缓冲区长度		N/A				成功返回0	获取证券英文名称
#define FEM_RAWNOTIFY			108		//	(LPTCRAWNOTIFYINFO)通知数据		通知数据长度		N/A				成功返回0	发送通知数据
#define FEM_MONITOR				109		//  N/A					(LPFEMMONITOR)	缓冲区长度		N/A				0			输出统一监控信息
#define	FEM_GETL2L1HQDATA		110		//	股票代码			(LPHQSCINFO)	缓冲区长度		LOWORD=市场+1	成功返回0	获取行情数据(5档盘口,优先高速行情)
#define FEM_GETL2GPHQDATA		111		//	股票代码			(LPL2HQINFO)	缓冲区长度		LOWORD=市场+1	成功返回0	获取高速行情数据(10档盘口,高速行情)
#define FEM_GETL2HQSTATE		112		//	N/A					(LPBOOL)		N/A				N/A				0			获取高速行情数据状态

#define FEM_RELAY				113		//  (LPTCRELAYINFO)	中继数据		中继数据长度		N/A				0			发送中继数据

// 兼容别名
#define	GPHQ_DATA				FEM_GETHSGPHQDATA1
#define NOTIFY_DATA				FEM_NOTIFY
#define GPHQ2_DATA				FEM_GETHSGPHQDATA2




// 错误信息
#define IOERR_NOERROR				(0)			// 无错误

#define IOERR_INVALID_TYPE			(-1)		// 非法数据类型
#define IOERR_INVALID_PARAM			(-2)		// 无效参数
#define IOERR_INVALID_SYMBOL		(-3)		// 无效商品
#define IOERR_SVC_NOT_RUN			(-4)		// 服务未运行
#define IOERR_NOT_SUPPORT			(-5)		// 功能暂不支持
#define IOERR_BUSINESS_FATAL		(-6)		// 事务内部错误
#define IOERR_CONNECT_MISSING		(-7)		// 连接已经关闭

#define IOERR_INVALID_BUSINESS		(-10)		// 无效事务

#define IOERR_CAST_NO_CFG			(-20)		// 无推送配置
#define IOERR_CAST_USERNOTONLINE	(-21)		// 用户不在线
#define IOERR_CAST_USER_NOCASTABLE	(-22)		// 用户未登录或是后台连接(按照客户号推送时有效)
#define IOERR_CAST_USERNOTMATCH		(-23)		// 用户不匹配(按照客户号推送时有效)
#define IOERR_CAST_TOOMUCH			(-24)		// 太多的推送消息(按照客户号推送时有效)
#define IOERR_CAST_LOWLEVELERROR	(-25)		// 推送时低级错误
#define IOERR_CAST_NOMATCHEDUSER	(-26)		// 无满足要求的用户在线
#define IOERR_CAST_PACKERROR		(-27)		// 封包错误


#define IOERR_RELAY_NOEXCHANGE		(-40)		// 配置禁止信息交换
#define IOERR_RELAY_CONNNOTREADY	(-41)		// 互连协议未就绪
#define IOERR_RELAY_REQTOOLONG		(-42)		// 请求缓冲区太长
#define IOERR_RELAY_PACKERROR		(-43)		// 中继封包错误
#define IOERR_RELAY_BADSETTING		(-50)		// 设置错误

// 数据回调过程
// 参数:	lpCode		股票代码
//			nDataType	数据类型,目前只支持股票数据
//			lpData		返回数据缓冲区
//			cbData		数据缓冲区大小
//			dwIoParam	IO参数,初始化的时候传入
//			dwReserved	保留字段(必须全空)
// 返回:	(LONG)		>=0成功,<0失败,返回错误代码
typedef LONG (CALLBACK* PFEMDATAIO)(LPSTR lpszCode,SHORT nDataType,LPVOID lpData,
	DWORD cbData,DWORD_PTR dwIoParam,DWORD dwReserved);
typedef PFEMDATAIO PDATAIOFUNC;


#pragma pack()
#endif
