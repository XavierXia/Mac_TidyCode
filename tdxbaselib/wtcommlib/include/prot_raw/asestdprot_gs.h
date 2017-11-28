//////////////////////////////////////////////////////////////////////////
// 通讯网关(消息中继/安全网关)协议规范定义文件
//	1.通讯网关相关的协议定义 (协议号范围: 4510-4560)
//	2.通讯网关主要实现包括: 消息中继,安全网关
// 当前文件包含:
//		Part.I		协议定义
//		Part.II		内部结构
//		Part.III	协议定义
//		Part.IV		错误号宏(PROTERR)
#ifndef __ASE_STDPROT_GS__H__
#define __ASE_STDPROT_GS__H__
#pragma pack(1)


//////////////////////////////////////////////////////////////////////////
// Part.I 协议定义
STD_PROT SHORT TC50_GS_CP_REG				= 4510;			// (中继)接入点注册(限制协议版本>=5.12.0190)
STD_PROT SHORT TC50_GS_CI_SYN_START			= 4511;			// (中继)准备同步在线状态(限制协议版本>=5.12.0190)
STD_PROT SHORT TC50_GS_CI_SYN_RUN			= 4512;			// (中继)同步在线状态(限制协议版本>=5.12.0190)
STD_PROT SHORT TC50_GS_CI_SYN_END			= 4513;			// (中继)确认在线状态同步(限制协议版本>=5.12.0190)
STD_PROT SHORT TC50_GS_CP_GOREADY			= 4514;			// (中继)接入点进入就绪状态(限制协议版本>=5.12.0190)
STD_PROT SHORT TC50_GS_CI_UPLOAD			= 4540;			// (中继)接入信息更新(限制协议版本>=5.12.0190)
STD_PROT SHORT TC50_GS_CP_WHOONLINE			= 4541;			// (中继)获取在线用户列表(限制协议版本>=5.12.0190)
STD_PROT SHORT TC50_GS_CP_WHOHACKER			= 4542;			// (中继)获取安全地址管理信息(限制协议版本>=5.12.0190)
STD_PROT SHORT TC50_GS_CD_RELAY				= 4550;			// (中继)中继转发
STD_PROT SHORT TC50_GS_CD_INBOX				= 4551;			// (中继)收到转发
STD_PROT SHORT TC50_GS_CD_KICK				= 4552;			// (中继)踢出连接


//////////////////////////////////////////////////////////////////////////
// Part.II 内部结构
// 接入点->连接信息
typedef enum enumCPCONNSTAT
{	CPCONNST_NOUSED,										// 未使用
	CPCONNST_ONLINE,										// 用户在线
	CPCONNST_OFFLINE,										// 用户退出
	CPCONNST_STATLOST1,										// 状态丢失(接入点重启)
	CPCONNST_STATLOST2,										// 状态丢失(失步断开,连接被复用)
	CPCONNST_STATLOST3,										// 状态丢失(失步断开)
	CPCONNST_STATLOST4,										// 状态丢失(维护断开,连接被复用)
	CPCONNST_UNKNOWN,										// 未知状态(等待同步确认)
} CPCONNSTAT;	
typedef struct tagCPCONNINFO	
{	CPCONNSTAT	m_eState;									// 当前记录是否有效(在线)
	SESSIONID	m_idSession;								// 当前会话ID
	systm_t		m_tCreated;									// 会话建立时间
	IPV4		m_SourceIp;									// 会话来源IP
	WORD		m_wClientType;								// 客户端类型
	DWORD		m_dwClientVer;								// 客户端版本
	IPV4		m_InternetIp;								// IP地址(准备登录送入)
	MAC			m_Mac;										// MAC地址(准备登录送入)
	WORD		m_wUOrgID;									// 机构(全局)
	CHAR		m_szUID[UID_GSIZE];							// 用户(全局)
} CPCONNINFO;	
	
	
// 接入点->事件信息
typedef enum enumCPCONNACTTYPE
{	CPCONNACT_ONLINE,										// 用户上线
	CPCONNACT_OFFLINE,										// 用户下线
	CPCONNACT_REFUSE,										// 连接拒绝
	CPCONNACT_CRISIS,										// 信用值变化
} CPCONNACTTYPE;	
typedef struct tagCPCONNACT	
{	BYTE		m_cType;	
	union	
	{	struct OfOnline	
		{	WORD		m_wSessionNo;						// 会话号
			SESSIONID	m_idSession;						// 当前会话ID
			IPV4		m_SourceIp;							// 会话来源IP
			systm_t		m_tCreated;							// 会话建立时间
			WORD		m_wClientType;						// 客户端类型
			DWORD		m_dwClientVer;						// 客户端版本
			IPV4		m_InternetIp;						// IP地址
			MAC			m_Mac;								// MAC地址
			WORD		m_wUOrgID;							// 机构(全局)
			CHAR		m_szUID[UID_GSIZE];					// 用户(全局)
		} m_OfOnline;	
		struct OfOffline	
		{	WORD		m_wSessionNo;						// 会话号
			SESSIONID	m_idSession;						// 当前会话ID
			UINT		m_nUnused1;							// 保留字段(原:退出原因)
			UINT		m_nUnused2;							// 保留字段(原:退出原因参数)
		} m_OfOffline;	
		struct	
		{	IPV4		m_SourceIp;							// 接入IP
			WORD		m_wSourcePort;						// 接入端口
			UINT		m_nCause;							// 拒绝原因
		} m_OfRefuse;	
		struct	
		{	WORD		m_wSessionNo;						// 会话号
			SESSIONID	m_idSession;						// 当前会话ID
			WORD		m_wUOrgID;							// 机构(全局)
			CHAR		m_szUID[UID_GSIZE];					// 用户(全局)
			IPV4		m_SourceIp;							// 接入IP
			IPV4		m_InternetIp;						// IP地址
			MAC			m_Mac;								// MAC地址
			UINT		m_nCause;							// 退出原因
			UINT		m_nCauseParam;						// 退出原因参数
		} m_OfCrisis;	
	} m_Data;	
} CPCONNACT;	
	
// 接入点<-通知信息	
typedef enum enumCPNOTIFYTYPE
{	CPNOTIFY_FREEZE,										// 地址冻结
	CPNOTIFY_LOADPOLICY,									// 重新装载策略
	CPNOTIFY_KICKOUT,										// 用户踢出
} CPNOTIFYTYPE;	
typedef struct tagCPNOTIFY	
{	BYTE		m_cType;	
	union	
	{	struct OfFreeze	
		{	BYTE		m_cLockFlag;						// 锁定标志
			LONG		m_tRestoreTime;						// 恢复时间(-1:黑名单,0:白名单,n:预计恢复时间)
			IPV4		m_SourceIp;							// 接入IP
			IPV4		m_InternetIp;						// 客户IP
			MAC			m_Mac;								// 客户MAC
		} m_OfFreeze;	
		struct OfLoadPolicy	
		{	
		} m_OfLoadPolicy;	
		struct OfKickout	
		{	WORD		m_wSessionNo;						// 会话号
			SESSIONID	m_idSession;						// 当前会话ID
		} m_OfKickout;	
	} m_Data;	
} CPNOTIFY;	
	
	




//////////////////////////////////////////////////////////////////////////
// Part.III 协议定义

// 接入点注册(TC50_GS_REG_CP,限制协议版本>=5.12.0188)
struct tc50_gs_cp_reg_req
{	BYTE		m_bPriConn;							// 主要连接(需要进行同步信息)
	BYTE		m_cServId;							// 接入点ID
	MAC			m_ServMac;							// 服务器MAC地址
	CHAR		m_szServName[64];					// 服务器名称
	DWORD		m_dwMaxConnectNum;					// 接入点支持的最大连接数
	UINT		m_nSynAnsBufSize;					// 同步缓冲区长度(应答)
	UINT		m_nExchangeAnsBufSize;				// 交换缓冲区长度(应答)
	systm_t		m_tCPTime;							// 接入点时间
	LONG		m_tStartTime;						// 接入点启动时间
	DWORD		m_dwEC;								// 接入点错误检测数
	DWORD		m_dwFinalActIndex;					// 最后一次同步的起始事务位置
};
struct tc50_gs_cp_reg_ans
{	DWORD		m_dwPrevEC;							// 接入点错误检测数
	UINT		m_nSynReqBufSize;					// 同步缓冲区长度(请求)
	UINT		m_nExchangeReqBufSize;				// 交换缓冲区长度(请求)
	DWORD		m_bReset:1;							// 是否服务数据被重置
	DWORD		m_bSynch:1;							// 是否需要重新同步
	DWORD		m_dwReserved:30;					// 保留字段
};


// 接入信息同步(TC50_GS_CI_SYN_START,限制协议版本>=5.12.0188)
struct tc50_gs_ci_syn_start_req
{	BYTE		m_cServId;							// 接入点ID
	DWORD		m_bForceSync:1;						// 强制同步标志
	DWORD		m_dwReserved:31;					// 保留字段
};
struct tc50_gs_ci_syn_start_ans
{	DWORD		m_dwReserved;						// 保留字段
};


// 接入信息同步(TC50_GS_CI_SYN_RUN,限制协议版本>=5.12.0188)
struct tc50_gs_ci_syn_run_req
{	BYTE		m_cServId;							// 接入点ID
	WORD		m_wSessionFrom;						// 开始会话号
	WORD		m_wSessionEnd;						// 结束会话号
	WORD		m_wSessionCount;					// 会话数
	DWORD		m_dwReserved;						// 保留字段
	WORD		m_cbBuffer;							// 缓冲区长度
	BYTE		m_acBuffer[1];						// 缓冲区
};
struct tc50_gs_ci_syn_run_ans
{	WORD		m_wNextSessionNo;					// 下次同步的会话号
};

// 接入信息同步完成(TC50_GS_CI_SYN_END,限制协议版本>=5.12.0188)
struct tc50_gs_ci_syn_end_req
{	BYTE		m_cServId;							// 接入点ID
	DWORD		m_dwEC;								// 接入点错误检测数
};
struct tc50_gs_ci_syn_end_ans
{	DWORD		m_dwPrevEC;							// 接入点错误检测数
	DWORD		m_dwNewActIndex;					// 同步后新的起始事务位置
	DWORD		m_dwReserved;						// 保留字段
};




// 获取在线状态列表(TC50_GS_CP_WHOONLINE,限制协议版本>=5.12.0188)
struct tc50_gs_cp_whoonline_req
{	BYTE		m_cServId;							// 接入点ID
	systm_t		m_tDataStamp;						// 列表时间戳(GW重新启动会重置,数据越界会重置)
	systm_t		m_tSnapStamp;						// 快照时间戳(GW重新启动会重置,数据越界会重置)
	LONG		m_nOffset;							// 数据偏移(-1:创建快照并获取第一个包,>=0:已经完成的个数)
	LONG		m_nAfterVersion;					// 接入点记录的最高版本
	BYTE		m_cReserved;						// 保留字段
};
#define WOF_ONLINE		0X01						// 用户上线
#define WOF_OFFLINE		0X02						// 用户离线
struct tc50_gs_cp_whoonline_ans
{	systm_t		m_tDataStamp;						// 列表时间戳(GW重新启动会重置,数据越界会重置)
	systm_t		m_tSnapStamp;						// 快照时间戳(GW重新启动会重置,数据越界会重置)
	LONG		m_nCount;							// 数据个数
	BYTE		m_bOverwriteAll:1;					// 需要完全覆盖本地数据
	BYTE		m_bReSnapshot:1;					// 需要重建同步快照
	BYTE		m_cReserved:6;						// 保留字段
	WORD		m_cbBuffer;							// 缓冲区长度
	BYTE		m_acBuffer[1];						// 缓冲区
};




// 获取安全地址管理信息(TC50_GS_CP_WHOHACKER,限制协议版本>=5.12.0188)
struct tc50_gs_cp_whohacker_req
{	BYTE		m_cServId;							// 接入点ID
	systm_t		m_tDataStamp;						// 列表时间戳(GW重新启动会重置,数据越界会重置)
	systm_t		m_tSnapStamp;						// 快照时间戳(GW重新启动会重置,数据越界会重置)
	LONG		m_nOffset;							// 数据偏移(-1:创建快照并获取第一个包,>=0:已经完成的个数)
	LONG		m_nAfterVersion;					// 接入点记录的最高版本
	BYTE		m_cReserved;						// 保留字段
};
struct tc50_gs_cp_whohacker_ans
{	systm_t		m_tDataStamp;						// 列表时间戳(GW重新启动会重置,数据越界会重置)
	systm_t		m_tSnapStamp;						// 快照时间戳(GW重新启动会重置,数据越界会重置)
	LONG		m_nCount;							// 数据个数
	BYTE		m_bOverwriteAll:1;					// 需要完全覆盖本地数据
	BYTE		m_bReSnapshot:1;					// 需要重建同步快照
	BYTE		m_cReserved:6;						// 保留字段
	WORD		m_cbBuffer;							// 缓冲区长度
	BYTE		m_acBuffer[1];						// 缓冲区
};


// 接入点通知订阅(TC50_GS_CP_GOREADY,限制协议版本>=5.12.0188)
struct tc50_gs_cp_goready_req
{	BYTE		m_cServId;							// 接入点ID
	DWORD		m_dwReserved;						// 保留字段
};
struct tc50_gs_cp_goready_ans
{	DWORD		m_dwReserved;						// 保留字段
};


// 接入信息更新(TC50_GS_CI_UPLOAD,限制协议版本>=5.12.0188)
struct tc50_gs_ci_upload_req
{	BYTE		m_cServId;							// 接入点ID
	DWORD		m_dwEC;								// 接入点错误检测数
	DWORD		m_dwActIndex;						// 起始事务位置
	DWORD		m_dwActCount;						// 更新的事务数
	WORD		m_cbBuffer;							// 缓冲区长度
	BYTE		m_acBuffer[1];						// 缓冲区
};
struct tc50_gs_ci_upload_ans
{	DWORD		m_dwPrevEC;							// 接入点错误检测数
	DWORD		m_dwNewActIndex;					// 新的起始事务位置
	DWORD		m_dwDropActCount;					// 需要删除的事务数
	DWORD		m_dwReserved;						// 保留字段
};


// 请求转发(TC50_GS_CD_RELAY,限制协议版本>=5.12.0191)
struct tc50_gs_cd_relay
{	WORD		m_wUOrgID;							// 机构(全局)
	CHAR		m_szUID[UID_GSIZE];					// 用户(全局)
	BYTE		m_cFuncType;						// 功能类型
	WORD		m_wFuncID;							// 功能号
	BYTE		m_cFlags;							// 标志位(RELAYF_XXXXX)
	DWORD		m_dwReserved;						// 保留
	WORD		m_cbBuffer;							// 缓冲区长度
	BYTE		m_acBuffer[1];						// 缓冲区
};
// 中继标识(参阅: ASEStdProt_GS.h)
#ifndef RELAY_FLAGS
	#define RELAY_FLAGS
	#define RELAYF_USECOUNTER	0X01				// 使用中继记数器
	#define RELAYF_ADDCOUNTER	0X02				// 中继计数器增减(发送:增加接收者记数 确认:减发送者记数)
	#define RELAYF_COMPRESS		0X04				// 强制使用压缩模式
	#define RELAYF_ENCRYPTED	0X08				// 强制使用加密模式
#endif


// 收到转发(TC50_GS_CD_INBOX,限制协议版本>=5.12.0191)
struct tc50_gs_cd_inbox
{	WORD		m_wUOrgID;							// 机构(全局)
	CHAR		m_szUID[UID_GSIZE];					// 用户(全局)
	BYTE		m_cFuncType;						// 功能类型
	WORD		m_wFuncID;							// 功能号
	BYTE		m_cFlags;							// 标志位(RELAYF_XXXXX)
	DWORD		m_dwReserved;						// 保留
	WORD		m_cbBuffer;							// 缓冲区长度
	BYTE		m_acBuffer[1];						// 缓冲区
};

// 踢出连接(TC50_GS_CD_KICK,限制协议版本>=5.12.0191)
struct tc50_gs_cd_kick
{	BYTE		m_cServId;							// 新服务器ID
	CPCONNINFO	m_CI;								// 新连接信息
	BYTE		m_cServIdToKick;					// 踢出的服务器ID
	SESSIONID	m_idSessionToKick;					// 踢出的会话ID
	DWORD		m_dwReserved;						// 保留
};



//////////////////////////////////////////////////////////////////////////
// Part.IV 扩充错误号宏(PROTERR)
// (安全网关部分)
// (参见:ASE_Err.h)

#pragma pack()
#endif
