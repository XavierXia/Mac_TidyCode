//////////////////////////////////////////////////////////////////////////
// 创建日期:2006/07/20
// 功能说明:TC50/接口DLL(FEM/FEB)调用相关接口
//          TC50中提供的主要接口包括以下几种
//          (1).接口信息查询
//				FEM_GetInformation
//				FEM_GetSummaryCols
//          (2).配置相关接口
//				FEM_GetOptionSummary
//			    FEM_ShowOptionDialog
//          (3).接口初始化以及退出函数
//				FEM_InitInst
//				FEM_ExitInst
//          (4).接口事务处理函数(初始化后有效)
//				FEM_GetDicts
//				FEM_BusinessProc
//          (5).状态监控函数(初始化后有效)
//				FEM_IsBranchAvailable
//				FEM_GetStatusSummary
// 变更记录:
//            2006/07/21 支持TC50协议
//            2006/07/25 代码对齐
//            2008/03/11 移植到linux
#ifndef __TC_FEMDEFINE__H__
#define __TC_FEMDEFINE__H__



//------------------------------------------------------------------------
// Part.III 接口定义
//------------------------------------------------------------------------
// 强制1字节对齐
#pragma pack(1)


	// 取得版本信息
	typedef struct tagFEMINFO
	{	CHAR m_szFileName[33];								// 设置文件名
		CHAR m_szName[33];									// 接口名称 
		FLOAT m_fVersion;									// 接口版本
		DWORD m_dwDate;										// 编译日期
		DWORD m_bHasPublicOption:1;							// 是否有公用设置对话框
		DWORD m_bHasBranchOption:1;							// 是否有营业部设置对话框
		DWORD m_bHasSyncProc:1;								// 是否具备同步处理能力
		DWORD m_bHasAsyncProc:1;							// 是否具备异步处理能力
		DWORD m_bHasTradeCcf:1;								// 是否存在交易配置
		DWORD m_abReserved:27;								// 保留位,必须全空
		BYTE  m_szReserved[64];								// 保留字节,必须全空
	} FEMINFO,*LPFEMINFO;
	typedef VOID (* FEM_GETINFORMATION)(LPFEMINFO lpFEMInfo);


	// 取摘要列结构定义(包括配置摘要以及状态摘要)
	enum enumFEMSUMMARYTYPE
	{	FEM_SUMMARY_TYPE_OPTION,							// 设置摘要,用于选项显示
		FEM_SUMMARY_TYPE_STATUS,							// 状态摘要,用于状态显示
	};
	#define FEM_SUMMARY_TYPE_GTDZ				0			// 柜台地址(配置摘要)
	#define FEM_SUMMARY_TYPE_GYH				1			// 柜员号(配置摘要)
	#define FEM_SUMMARY_TYPE_LOAD				2			// 负载比率(状态摘要)
	#define FEM_SUMMARY_TYPE_FZYWS				3			// 最近分钟业务数(状态摘要)
	#define FEM_SUMMARY_TYPE_AVGRESPONSETICK	4			// 近一分钟业务平均响应时间(TICK数)(状态摘要)
	typedef struct tagFEMSUMMARY
	{	DWORD  m_dwColType;									// 列类型
		CHAR  m_szColName[33];								// 列名称
		DWORD  m_dwColWidth;								// 列宽度
	} FEMSUMMARY,*LPFEMSUMMARY;
	typedef DWORD (* FEM_GETSUMMARYCOLS)(DWORD dwSummaryType,LPFEMSUMMARY lpFEMSummary,DWORD dwMaxCount);


	// 取得设置摘要列
	typedef VOID (* FEM_GETOPTIONSUMMARY)(LPCSTR lpszFilePath,LPCSTR lpszBranchSection,DWORD dwColType,DWORD dwMaxSize,LPSTR lpszSummary);



	// 显示公用设置修改对话框
	typedef BOOL (* FEM_SHOWOPTIONDIALOG)(HWND hParent,LPCSTR lpszFilePath,LPCSTR lpszSection,BOOL bPublicOption);


	// 运行期全局初始化
	typedef struct tagFEMBRANCHINFO
	{	DWORD   m_dwBranchID;								// 营业部ID
		DWORD	m_dwMinThreadNum;							// 该营业部对应的最小线程数
		DWORD	m_dwMaxThreadNum;							// 该营业部对应的最大线程数
		CHAR	m_szBranchSection[MAX_PATH];				// 营业部配置节
	} FEMBRANCHINFO,*LPFEMBRANCHINFO;
	typedef struct tagFEMPARAM
	{	DWORD				m_dwReserved1;					// 是否以异步方式启动
		LPVOID				m_pfnDataIO;					// 数据IO回调函数
		DWORD_PTR			m_dwIoParam;					// 数据IO回调参数
		DWORD				m_dwMaxAnsBufLen;				// 最大应答缓冲区长度
		DWORD				m_dwBranchNum;					// 营业部数
		CHAR				m_szOptionFile[MAX_PATH];		// 配置文件
		CHAR				m_szPublicSection[MAX_PATH];	// 公用设置节
		LPFEMBRANCHINFO		m_lpBranchInfos;				// 营业部设置
		BYTE				m_szReserved2[64];				// 保留字节,全空
	} FEMPARAM,*LPFEMPARAM;
	typedef BOOL (* FEM_INITINST)(LPFEMPARAM lpFEMParam);


	// 运行期全局关闭函数
	typedef VOID (* FEM_EXITINST)();


	// 取得数据字典
	enum enumDICTTYPE
	{	DICTTYPE_SIMPLE,									// 简化字典,主要用于登录处理
		DICTTYPE_FULL,										// 完整字典,主要用于业务处理
	};
	typedef DWORD (* FEM_GETDICTS)(DWORD dwType,DWORD dwMaxSize,LPBYTE lpDict);


	// 事务处理过程
	// 返回数据>=0,处理成功,返回数据随应答包送回
	// 返回数据<0,处理失败,客户端收到异常处理通知,错误号随通知送回
	// DLL的返回范围为-10000<=RETCODE<=+10000
	enum enumBUSINESSPROCRET
	{	BCRET_PROC_PENDING=-2,							// DLL处理等待异步结果
		BCRET_PROC_FAIL=-1,								// DLL处理失败
		BCRET_PROC_SUCCESS=0,							// DLL处理成功
	};
	// 结构定义
	typedef struct tagFEMFUNCCNT
	{	DWORD	m_cbFuncCnt;							// 结构长度
		HANDLE	m_hBusiness;							// 事务句柄
		DWORD	m_dwRawIP;								// 客户端连接地址(主机序)
		LPCSTR	m_pszUOrg;								// 当前事务的机构
		LPCSTR	m_pszUID;								// 当前事务的帐号
		LPDWORD	m_pdwInApiTime;							// 在API上消耗的时间(毫秒)
		WORD	m_wReqNo;								// 当前事务的协议号(初始化填写)
		LPCSTR	m_pszCmdDesc;							// 当前事务的描述(初始化填写)
		LPCSTR	m_pszClientUOrg;						// 当前事务的客户机构(可能不存在,不存在为系统功能)
		LPCSTR	m_pszClientUID;							// 当前事务的客户帐号(可能不存在,不存在为系统功能)
		DWORD	m_idSession;							// 当前事务的会话ID(原会话ID)
		#if defined(ASE_BACKWARD_COMPATIBILITY)
		DWORD	m_idBussiness;							// 当前事务的事务ID
		#else
		DWORD	m_idBusiness;							// 当前事务的事务ID
		#endif
		DWORD	m_dwTransKey;							// 当前事务的传输键
		WORD	m_wClientType;							// 客户端类型
		DWORD	m_dwClientVer;							// 客户端版本
		IPV4	m_ClientIP;								// 客户IP
		MAC		m_ClientMac;							// 客户MAC
		DWORD	m_bV6OrMoreHigh:1;						// 客户端是否是V6或更高版本(>=5.12.0180)
		DWORD	m_bBkgdConn:1;							// 客户端是否是后台连接(>=5.12.0188)
		DWORD	m_bWapConn:1;							// 客户端是否WAP客户端
		DWORD	m_bWantGTSessionID:1;					// 是否需要柜台SESSIONID
		DWORD	m_dwReserved:28;						// 保留字段
		DWORD	m_dwGTSessionID;						// 柜台SESSIONID
	} FEMFUNCCNT,*LPFEMFUNCCNT;
	typedef LONG (* FEM_BUSINESSPROC)(PVOID pFuncCnt,DWORD dwBranchID,LPFUNCHDR lpFuncHdr,
		LPFUNCBDY lpFuncReq,LPFUNCBDY lpFuncAns);


	// 取当前营业部状态(后台状态)
	typedef BOOL (* FEM_ISBRANCHAVAILABLE)(DWORD dwBranchID);


	// 取得状态摘要列
	typedef VOID (* FEM_GETSTATUSSUMMARY)(DWORD dwBranchID,DWORD dwColType,DWORD dwMaxSize,LPSTR lpszSummary);


	// 通知接口状态
	enum enumFEMNCODE
	{	NC_CONNECTLOST,					// 客户断开连接(已经验证客户身份)
		NC_UNAMEDCLOSED,				// 未知连接断开(未验证身份)
		NC_CONNECTAUDIT,				// 客户建立连接(已经验证客户身份,非后台连接)
	};
	typedef BOOL (* FEM_STATENOTIFY)(DWORD idSession,DWORD dwSessionData,DWORD dwBranchID,LPCSTR pszClientUID,DWORD dwNotifyCode,DWORD dwParam);

#pragma pack()
#endif
