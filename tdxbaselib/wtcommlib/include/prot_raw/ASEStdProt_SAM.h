//////////////////////////////////////////////////////////////////////////
// 标准互联协议规范定义文件
// 本文件定义:
//		1.监控协议(Surveillance and Monitoring)定义 (协议号范围: 4400-4450)
// 协议编码段:
//		Part.I   监控功能号定义
//		Part.II  监控相关结构定义
//		Part.III 监控协议定义
//		Part.IV  监控错误号定义(PROTERR)
#ifndef __ASE_STDPROT_SAM__H__
#define __ASE_STDPROT_SAM__H__
// 协议部分,使用1字节对齐
#pragma pack(1)

// 管理端协议
//		管理客户端协议,从本版本开始,全部服务器端监控均使用安全验证,客户端必须经过
//		验证才允许访问服务器监控信息,包括当前连接人数等
STD_PROT SHORT SAM_ADMIN_ALIVE					= 4400;			// 管理用户存活包信息(组合协议)(限制协议版本>=5.12.0156)
STD_PROT SHORT SAM_ADMIN_GET_SERVER_INFO		= 4401;			// 管理用户获取服务器信息(组合协议)(限制协议版本>=5.12.0156)
STD_PROT SHORT SAM_ADMIN_LOGIN					= 4402;			// 管理用户登录协议(组合协议)(限制协议版本>=5.12.0156)
STD_PROT SHORT SAM_ADMIN_CHGINFO				= 4403;			// 管理用户修改用户信息(限制协议版本>=5.12.0156)
STD_PROT SHORT SAM_ADMIN_RUNCMD					= 4404;			// 管理请求(限制协议版本>=5.12.0156)

STD_PROT SHORT SAM_GET_SIMP_STATUS				= 4405;			// 得到简单服务器状态(限制协议版本>=5.12.0156)
STD_PROT SHORT SAM_GET_FULL_STATUS				= 4406;			// 得到详细服务器状态

STD_PROT SHORT SAM_LIST_ENTRYPOINTS				= 4407;			// 列出全部入口点信息(限制协议版本>=5.12.0156)
STD_PROT SHORT SAM_LIST_BRANCHS					= 4408;			// 列出全部营业部信息(限制协议版本>=5.12.0156)
STD_PROT SHORT SAM_GET_ENTRYPOINT_STATUS		= 4409;			// 得到入口点状态
STD_PROT SHORT SAM_GET_BRANCH_STATUS			= 4410;			// 得到营业部状态

STD_PROT SHORT SAM_PUT_CALLBOARD				= 4411;			// 张贴服务器系统通知(限制协议版本>=5.12.0156)
STD_PROT SHORT SAM_PUT_URGENT					= 4412;			// 张贴服务器营业部公告(限制协议版本>=5.12.0156)

STD_PROT SHORT SAM_LIST_NETWORK					= 4413;			// 列出交易架构(节点集)

STD_PROT SHORT SAM_LIST_DIR						= 4414;			// 列出目录全部内容(限制协议版本>=5.12.0156)
STD_PROT SHORT SAM_MAKE_DIR						= 4415;			// 创建目录(限制协议版本>=5.12.0156)
STD_PROT SHORT SAM_GET_FILELEN					= 4416;			// 得到文件长度(限制协议版本>=5.12.0156)
STD_PROT SHORT SAM_GET_FILE						= 4417;			// 读取文件片断(限制协议版本>=5.12.0156)
STD_PROT SHORT SAM_PUT_FILE						= 4418;			// 上传文件片断(限制协议版本>=5.12.0156)

STD_PROT SHORT SAM_REBOOT						= 4419;			// 重新启动服务(限制协议版本>=5.12.0156)

STD_PROT SHORT SAM_LIST_COUNTERS				= 4420;			// 列出柜台信息
STD_PROT SHORT SAM_GET_COUNTER_STATUS			= 4421;			// 得到柜台状态

STD_PROT SHORT SAM_CLIENT_LIST					= 4422;			// 列出全部客户(限制协议版本>=5.12.0156)
STD_PROT SHORT SAM_CLIENT_DROP					= 4423;			// 断开指定客户连接(限制协议版本>=5.12.0156)
STD_PROT SHORT SAM_CLIENT_MESSAGE				= 4424;			// 向指定客户发送消息(限制协议版本>=5.12.0156)

STD_PROT SHORT SAM_RAWIP_LIST					= 4425;			// 列出接入物理节点(限制协议版本>=5.12.0156)
STD_PROT SHORT SAM_RAWIP_DROP					= 4426;			// 退出当前连接(限制协议版本>=5.12.0156)
STD_PROT SHORT SAM_RAWIP_FREEZE					= 4427;			// 冻结接入地址(限制协议版本>=5.12.0156)
STD_PROT SHORT SAM_RAWIP_UNFREEZE				= 4428;			// 解冻接入地址(限制协议版本>=5.12.0156)
STD_PROT SHORT SAM_RAWIP_CREDIT					= 4429;			// 接入IP信用获取和修改(限制协议版本>=5.12.0156)

STD_PROT SHORT SAM_IP_LIST						= 4430;			// IP地址列表(限制协议版本>=5.12.0156)
STD_PROT SHORT SAM_IP_FREEZE					= 4431;			// IP地址冻结(注*,安全中心冻结需要通过SAM_FUNC_CALL实现)(限制协议版本>=5.12.0156)
STD_PROT SHORT SAM_IP_UNFREEZE					= 4432;			// IP地址解冻(限制协议版本>=5.12.0156)
STD_PROT SHORT SAM_IP_CREDIT					= 4433;			// IP信用获取和修改(限制协议版本>=5.12.0156)

STD_PROT SHORT SAM_MAC_LIST						= 4434;			// MAC地址列表(限制协议版本>=5.12.0156)
STD_PROT SHORT SAM_MAC_FREEZE					= 4435;			// MAC地址冻结(注*,安全中心冻结需要通过SAM_FUNC_CALL实现)(限制协议版本>=5.12.0156)
STD_PROT SHORT SAM_MAC_UNFREEZE					= 4436;			// MAC地址解冻(限制协议版本>=5.12.0156)
STD_PROT SHORT SAM_MAC_CREDIT					= 4437;			// MAC信用获取和修改(限制协议版本>=5.12.0156)

STD_PROT SHORT SAM_THREAD_LIST					= 4438;			// 线程列表(限制协议版本>=5.12.0156)
STD_PROT SHORT SAM_THREAD_STATE					= 4439;			// 线程状态获取和修改(限制协议版本>=5.12.0156)

STD_PROT SHORT SAM_FUNCS_LIST					= 4440;			// 功能列表(限制协议版本>=5.12.0156)
STD_PROT SHORT SAM_FUNCS_ENABLE					= 4441;			// 禁止和允许指定功能(限制协议版本>=5.12.0156)

STD_PROT SHORT SAM_ROUTES_LIST					= 4442;			// 列出路由项(限制协议版本>=5.12.0156)
STD_PROT SHORT SAM_ROUTES_RESET					= 4443;			// 重新连接对应的路由项(限制协议版本>=5.12.0156)

STD_PROT SHORT SAM_BLACKLIST_LIST				= 4444;			// 黑名单列表(注*,黑名单分为静态和动态)(限制协议版本>=5.12.0156)
STD_PROT SHORT SAM_BLACKLIST_ADD				= 4445;			// 黑名单增加(注*,黑名单分为静态和动态)(限制协议版本>=5.12.0156)
STD_PROT SHORT SAM_BLACKLIST_DEL				= 4446;			// 黑名单删除(限制协议版本>=5.12.0156)

STD_PROT SHORT SAM_INFO_MORE					= 4447;			// 获取更多主站信息
STD_PROT SHORT SAM_INFO_VERSIONS				= 4448;			// 获取版本统计信息					



// 性能监视文件(交易中心)
typedef struct tagTCPERFSNAPSHOT
{	DWORD			m_cbPerfMonItem;					// 当前结构大小
	DWORD			m_cbData;							// 数据记录大小(包含线程数据和功能数据)
	LONG			m_tUpdate;							// 记录更新时间
	LONG			m_tStartup;							// 系统启动日期
	WORD			m_wCpuUsage;						// CPU利用率
	WORD			m_wMemUsage;						// 内存利用率
	DWORD			m_dwTotalPhys;						// 物理内存总数
    DWORD			m_dwAvailPhys;						// 物理内存可用数
    DWORD			m_dwTotalPageFile;					// 内存页面总数
    DWORD			m_dwAvailPageFile;					// 内存页面可用
    DWORD			m_dwTotalVirtual;					// 虚拟内存总数
    DWORD			m_dwAvailVirtual;					// 虚拟内存可用
	DWORD			m_dwUsedConnectNum;					// 总计连接数(统计数据)
	DWORD			m_dwTopConnectNum;					// 历史最大连接数(统计数据)
	DWORD			m_dwNowConnectNum;					// 当前连接数
	DWORD			m_dwMaxConnectNum;					// 最大连接数
	DWORD			m_dwHisRecvd;						// 历史接收字节数(统计数据)
	DWORD			m_dwHisSent;						// 历史发送字节数(统计数据)
	LONG			m_nBroadcastBusinessNum;			// 广播事务数
	LONG			m_nMulticastBusinessNum;			// 组播事务数
	LONG			m_nUnicastBusinessNum;				// 单播事务数
	LONG			m_nIncomeBusinessNum;				// 入站请求数(连接被断开时候的异常请求减少)
	LONG			m_nTopIncomeBusinessNum;			// 历史最大入站请求数
	LONG			m_nHisIncomeBusinessNum;			// 累计的入站请求数
	LONG			m_nHisFailBusinessNum;				// 累计失败请求数
	LONG			m_nHisSuccessBusinessNum;			// 累计成功请求数
	DWORD			m_dwActiveThreadsNum;				// 当前活动线程数(=处理中的事务数,统计数据)
	DWORD			m_dwTopActiveThreadsNum;			// 峰值最大活动线程数(=处理中的事务数,统计数据)
	DWORD			m_dwActiveCoreThreadNum;			// 当前活动线程数(=处理中的事务数,统计数据)
	DWORD			m_dwTopActiveCoreThreadNum;			// 峰值最大活动线程数(=处理中的事务数,统计数据)
	DWORD			m_dwActiveCommThreadNum;			// 当前活动线程数(=处理中的事务数,统计数据)
	DWORD			m_dwTopActiveCommThreadNum;			// 峰值最大活动线程数(=处理中的事务数,统计数据)
	DWORD			m_dwHisRecvdLast;					// 历史接收字节数(上秒,统计数据)
	DWORD			m_dwRecvdInSec;						// 接收字节数(每秒,统计数据)
	DWORD			m_dwTopRecvdInSec;					// 峰值接收字节数(每秒,统计数据)
	DWORD			m_dwHisSentLast;					// 历史发送字节数(上秒,统计数据)
	DWORD			m_dwSentInSec;						// 发送字节数(每秒,统计数据)
	DWORD			m_dwTopSentInSec;					// 峰值发送字节数(每秒,统计数据)
	LONG			m_nBroadcastBusinessNumLast;		// 历史广播事务数(上秒,统计数据)
	LONG			m_nBroadcastBusinessNumInSec;		// 广播事务数(每秒,统计数据)
	LONG			m_nTopBroadcastBusinessNumInSec;	// 峰值广播事务数(每秒,统计数据)
	LONG			m_nMulticastBusinessNumLast;		// 历史组播事务数(上秒,统计数据)
	LONG			m_nMulticastBusinessNumInSec;		// 组播事务数(每秒,统计数据)
	LONG			m_nTopMulticastBusinessNumInSec;	// 峰值组播事务数(每秒,统计数据)
	LONG			m_nUnicastBusinessNumLast;			// 历史单播事务数(上秒,统计数据)
	LONG			m_nUnicastBusinessNumInSec;			// 单播事务数(每秒,统计数据)
	LONG			m_nTopUnicastBusinessNumInSec;		// 峰值单播事务数(每秒,统计数据)
	LONG			m_nHisIncomeBusinessNumLast;		// 历史入站事务数(上秒,统计数据)
	LONG			m_nIncomeBusinessNumInSec;			// 处理事务数(每秒,统计数据)
	LONG			m_nTopIncomeBusinessNumInSec;		// 峰值处理事务数(每秒,统计数据)
	DWORD			m_dwHisFuncCallNumLast;				// 历史完成的功能数
	DWORD			m_dwFuncCallNumInSec;				// 处理事务数(每秒,统计数据)
	DWORD			m_dwTopFuncCallNumInSec;			// 峰值处理事务数(每秒,统计数据)
	DWORD			m_cbThreadItem;						// 线程记录项大小
	DWORD			m_dwThreadNum;						// 线程数(线程快照的线程数)
	DWORD			m_cbFuncItem;						// 功能记录项大小
	DWORD			m_dwFuncNum;						// 功能数
} TCPERFSNAPSHOT,*LPTCPERFSNAPSHOT;
typedef struct tagTCTHREADSNAPSHOT
{	DWORD			m_dwType;							// 线程类型
	DWORD			m_dwThreadNo;						// 线程号
	systm_t			m_tLastIdle;						// 上次空闲时间(线程)
	UINT			m_nId;								// 线程ID
	LBOOL			m_bBusy;							// 是否繁忙(线程)
	systm_t			m_tLastActive;						// 上次激活时间(线程)
	systm_t			m_tBusinessCreated;					// 事务创建时间(解包前)
	systm_t			m_tBusinessEntry;					// 事务进入处理时间(解包后)
	WORD			m_wReqNo;							// 当前事务的请求号
	CHAR			m_szCmdDesc[64];					// 当前事务的描述
	DWORD			m_dwInWaitTime;						// 在处理上消耗的时间(毫秒)
	DWORD			m_dwInProcTime;						// 在处理上消耗的时间(毫秒)
	DWORD			m_dwInApiTime;						// 在API上消耗的时间(毫秒)
	DWORD			m_dwHisBusinessNum;					// 累计处理事务数
	CHAR			m_szComment[64];					// 线程备注信息
} TCTHREADSNAPSHOT,*LPTCTHREADSNAPSHOT;
typedef struct tagTCFUNCSNAPSHOT
{	BYTE			m_cFuncType;						// 功能类型
	WORD			m_wFuncID;							// 功能ID
	CHAR			m_szDescription[41];				// 功能描述
	LBOOL			m_bNeedLog;							// 功能是否需要日志(其他配置)
	LBOOL			m_bTimeLimit;						// 功能是否限时开放(其他配置)
	LBOOL			m_bBoostLimit;						// 功能是否限制最大流量(进入处理功能数/秒,其他配置)
	LBOOL			m_bMassBoostLimit;					// 分组流量控制
	LONG			m_nBoostLimit;						// 功能限制流量(进入处理功能数/秒,其他配置)
	LBOOL			m_bParallelLimit;					// 功能是否限制最大并行(其他配置)
	LBOOL			m_bMassParallelLimit;				// 分组并行控制
	LONG			m_nParallelLimit;					// 功能限制并行(其他配置)
	LBOOL			m_bDisabled;						// 功能是否临时禁用(动态数据)
	LONG			m_nBoostCount;						// 功能流量(进入处理/每秒)次数(动态数据)
	LONG			m_nOutFlowCount;					// 功能流量(退出处理/每秒)次数(动态数据)
	LONG			m_nParallelCount;					// 功能并行度(正在处理)次数(动态数据)
	LONG			m_nHitCount;						// 功能调用次数(动态数据)
	FLOAT			m_fAverageTime;						// 功能平均耗时(退出队列计算)
	LONG			m_nBoostHitCount;					// 分组流量控制(动态数据,控制数据)
	LONG			m_nParallelHitCount;				// 分组并行控制(动态数据,控制数据)
} TCFUNCSNAPSHOT,*LPTCFUNCSNAPSHOT;





//////////////////////////////////////////////////////////////////////////
// 管理用请求
// 管理用户存活包信息(SAM_ADMIN_ALIVE,限制协议版本>=5.12.0156)
struct sam_admin_alive_req
{	BYTE		m_cReserved;
};
struct sam_admin_alive_ans
{	BYTE		m_cReserved;
};

// 管理用户获取登录参数(SAM_ADMIN_GET_SERVER_INFO,限制协议版本>=5.12.0156)
struct sam_admin_get_server_info_req
{	BYTE		m_cReserved;
};
struct sam_admin_get_server_info_ans
{	IPV4		m_InetIp;						// 客户端公网IP
	CHAR		m_szQsid[QSID_SIZE];			// 券商标识
	CHAR		m_szDesc[41];					// 服务器描述
	DWORD		m_dwReserved;					// 保留字段
};
struct sam_admin_get_server_info_ans2 : public sam_admin_get_server_info_ans
{	WORD		m_wServType;					// 服务器类型
	DWORD		m_dwServVer;					// 服务器版本
	LONG		m_nLicenseType;					// 授权类型
	CHAR		m_szLicenseFile[MAX_PATH];		// 授权文件
	LONG		m_nLicenseStatus;				// 授权状态
	DWORD		m_dwServID;						// 服务器ID
	CHAR		m_szServName[32];				// 服务器名称
};


// 管理用户登录协议(SAM_ADMIN_LOGIN,限制协议版本>=5.12.0156)
struct sam_admin_login_req
{	IPV4		m_InetIp;						// 客户端公网IP
	MAC			m_Mac;							// 客户端MAC地址(登录信息)
	WORD		m_wClientType;					// 客户端类型
	WORD		m_wClientVer;					// 客户端版本
	WORD		m_wReleaseVer;					// 发行版本
	CHAR		m_szUserName[41];				// 用户名称
	CHAR		m_szPassword[41];				// 用户密码
	DWORD		m_dwReserved;					// 保留字段
};
struct sam_admin_login_ans
{	LBOOL		m_bLocalLogin:1;				// 权限:本地登录(只能使用私网地址登录)
	LBOOL		m_bNetLogin:1;					// 权限:网络访问(可以使用任意网络地址登录)
	LBOOL		m_bReboot:1;					// 权限:重新启动(以及系统相关其他操作,例如目录查看删除等)
	LBOOL		m_bNotice:1;					// 权限:通告发布(一种是所有营业部的,可以发布系统公告和营业部公告,否则只能发营业部公告)
	LBOOL		m_bMonitor:1;					// 权限:监控权限(取连接人数/列营业部状态)
	LBOOL		m_bMoreAdmin:1;					// 权限:网络管理
	LBOOL		m_bLogView:1;					// 权限:日志查看
	LBOOL		m_bUserAdmin:1;					// 权限:帐号管理
	LBOOL		m_bPassChange:1;				// 权限:密码修改(可以修改密码)
	LBOOL		m_bUnused:23;					// 保留位
	DWORD		m_dwReserved;					// 保留字段
};

// 管理用户修改用户信息(SAM_ADMIN_CHGINFO,限制协议版本>=5.12.0156)
struct sam_admin_chginfo_req
{	CHAR		m_szUserName[41];				// 用户名称
	CHAR		m_szPassword[41];				// 用户密码
	CHAR		m_szNewPassword[41];			// 新用户密码
	DWORD		m_dwReserved;					// 保留字段
};
struct sam_admin_chginfo_ans
{	BYTE		m_cReserved;					// 保留字段
};

// 管理用户SHELL命令(SAM_ADMIN_RUNCMD,限制协议版本>=5.12.0156 NOT_IMPL)
struct sam_admin_runcmd_req
{	CHAR		m_szUserName[41];				// 用户名称
	CHAR		m_szPassword[41];				// 用户密码
	CHAR		m_szCmd[512];					// 命令行内容
	DWORD		m_dwReserved;					// 保留字段
};
struct sam_admin_runcmd_ans
{	BYTE		m_cReserved;					// 保留字段
};


// 得到简单服务器状态(SAM_GET_SIMP_STATUS,限制协议版本>=5.12.0156)
struct sam_get_simp_status_req
{	CHAR		m_szUserName[41];				// 用户名称
	CHAR		m_szPassword[41];				// 用户密码
	DWORD		m_dwReserved;					// 保留字段
};
struct sam_get_simp_status_ans
{	FLOAT		m_fVersion;						// 服务器版本
	CHAR		m_szBuild[32];					// 服务器编译号
	LONG		m_tStartupTime;					// 服务器启动时间
	LONG		m_bLogOn;						// 服务器是否开放日志
	
	DWORD		m_dwMaxConnectNum;				// 服务器允许的最大人数
	DWORD		m_dwNowConnectNum;				// 当前人数
	DWORD		m_dwTopConnectNum;				// 人数峰值
	DWORD		m_dwUsedConnectNum;				// 累计使用过的人数

	DWORD		m_dwHisRecvd;					// 历史接收字节数(统计数据)
	DWORD		m_dwHisSent;					// 历史发送字节数(统计数据)

	LONG		m_nIncomeBusinessNum;			// 入站请求数(连接被断开时候的异常请求减少)
	LONG		m_nTopIncomeBusinessNum;		// 历史最大入站请求数

	LONG		m_nHisIncomeBusinessNum;		// 累计的入站请求数
	LONG		m_nHisFailBusinessNum;			// 累计失败请求数
	LONG		m_nHisSuccessBusinessNum;		// 累计成功请求数

	DWORD		m_dwActiveThreadsNum;			// 当前活动线程数(=处理中的事务数,统计数据)
	DWORD		m_dwTopActiveThreadsNum;		// 峰值最大活动线程数(=处理中的事务数,统计数据)
	DWORD		m_dwActiveCoreThreadNum;		// 当前活动线程数(=处理中的事务数,统计数据)
	DWORD		m_dwTopActiveCoreThreadNum;		// 峰值最大活动线程数(=处理中的事务数,统计数据)
	DWORD		m_dwActiveCommThreadNum;		// 当前活动线程数(=处理中的事务数,统计数据)
	DWORD		m_dwTopActiveCommThreadNum;		// 峰值最大活动线程数(=处理中的事务数,统计数据)
	
	DWORD		m_dwHisRecvdLast;				// 历史接收字节数(上秒,统计数据)
	DWORD		m_dwRecvdInSec;					// 接收字节数(每秒,统计数据)
	DWORD		m_dwTopRecvdInSec;				// 峰值接收字节数(每秒,统计数据)

	DWORD		m_dwHisSentLast;				// 历史发送字节数(上秒,统计数据)
	DWORD		m_dwSentInSec;					// 发送字节数(每秒,统计数据)
	DWORD		m_dwTopSentInSec;				// 峰值发送字节数(每秒,统计数据)

	LONG		m_nBroadcastBusinessNumLast;	// 历史广播事务数(上秒,统计数据)
	LONG		m_nBroadcastBusinessNumInSec;	// 广播事务数(每秒,统计数据)
	LONG		m_nTopBroadcastBusinessNumInSec;// 峰值广播事务数(每秒,统计数据)

	LONG		m_nMulticastBusinessNumLast;	// 历史组播事务数(上秒,统计数据)
	LONG		m_nMulticastBusinessNumInSec;	// 组播事务数(每秒,统计数据)
	LONG		m_nTopMulticastBusinessNumInSec;// 峰值组播事务数(每秒,统计数据)

	LONG		m_nUnicastBusinessNumLast;		// 历史单播事务数(上秒,统计数据)
	LONG		m_nUnicastBusinessNumInSec;		// 单播事务数(每秒,统计数据)
	LONG		m_nTopUnicastBusinessNumInSec;	// 峰值单播事务数(每秒,统计数据)

	LONG		m_nHisIncomeBusinessNumLast;	// 历史入站事务数(上秒,统计数据)
	LONG		m_nIncomeBusinessNumInSec;		// 处理事务数(每秒,统计数据)
	LONG		m_nTopIncomeBusinessNumInSec;	// 峰值处理事务数(每秒,统计数据)

	WORD		m_wLastCpuUsage;				// 上一秒CPU利用率
	WORD		m_wLastMemUsage;				// 上一秒MEM利用率

	CHAR		m_szHomePath[MAX_PATH];			// 工作路径
	DWORD		m_dwReserved;					// 保留字节
};
struct sam_get_simp_status_ans2 : public sam_get_simp_status_ans
{	UINT64		m_nMemTotal;					// 内存总量
	UINT64		m_nMemUsed;						// 内存用量
	UINT64		m_nDiskTotal;					// 磁盘总量
	UINT64		m_nDiskUsed;					// 磁盘用量
};


// 得到详细服务器状态(SAM_GET_FULL_STATUS,限制协议版本>=5.12.0150)
struct sam_get_full_status_req
{	CHAR		m_szUserName[41];				// 用户名称
	CHAR		m_szPassword[41];				// 用户密码
	BYTE		m_cReserved;					// 保留字段
};
struct sam_get_full_status_ans
{	BYTE		m_cReserved;
};


// 列出全部入口点信息(SAM_LIST_ENTRYPOINTS,限制协议版本>=5.12.0150)
struct sam_list_entrypoints_req
{	CHAR		m_szUserName[41];				// 用户名称
	CHAR		m_szPassword[41];				// 用户密码
	DWORD		m_dwReserved;					// 保留字段
};
struct sam_list_entrypoints
{	WORD		m_wEntryPointID;				// 入口点ID
	CHAR		m_szName[41];					// 入口点名称
};
struct sam_list_entrypoints_ans
{	WORD		m_wCount;						// 入口点个数
	DWORD		m_dwReserved;					// 保留字段
	sam_list_entrypoints m_Data[1];			// 入口点数据
};

// 列出全部营业部信息(SAM_LIST_BRANCHS,限制协议版本>=5.12.0150)
struct sam_list_branchs_req
{	CHAR		m_szUserName[41];				// 用户名称
	CHAR		m_szPassword[41];				// 用户密码
	DWORD		m_dwReserved;					// 保留字段
};
struct sam_list_branchs
{	DWORD		m_dwBranchID;					// 营业部ID
	CHAR		m_szName[41];					// 营业部名称
};
struct sam_list_branchs_ans
{	WORD		m_wCount;						// 营业部个数
	DWORD		m_dwReserved;					// 保留字段
	sam_list_branchs m_Data[1];				// 营业部数据
};

// 得到入口点状态(SAM_GET_ENTRYPOINT_STATUS,限制协议版本>=5.12.0150)
struct sam_get_entrypoint_status_req
{	CHAR		m_szUserName[41];				// 用户名称
	CHAR		m_szPassword[41];				// 用户密码
	BYTE		m_cReserved;					// 保留字段
};
struct sam_get_entrypoint_status_ans
{	BYTE		m_cReserved;
};

// 得到营业部状态(SAM_GET_BRANCH_STATUS,限制协议版本>=5.12.0150)
struct sam_get_branch_status_req
{	CHAR		m_szUserName[41];				// 用户名称
	CHAR		m_szPassword[41];				// 用户密码
	BYTE		m_cReserved;					// 保留字段
};
struct sam_get_branch_status_ans
{	BYTE		m_cReserved;
};

// 张贴服务器系统通知(SAM_PUT_CALLBOARD,限制协议版本>=5.12.0150)
struct sam_put_callboard_req
{	CHAR		m_szUserName[41];				// 用户名称
	CHAR		m_szPassword[41];				// 用户密码
	WORD		m_wCallboardLen;				// 公告文本长度
	DWORD		m_dwReserved;					// 保留字段
	CHAR		m_szCallboard[1];				// 公告文本
};
struct sam_put_callboard_ans
{	BYTE		m_cReserved;					// 保留字段
};

// 张贴服务器营业部公告(SAM_PUT_URGENT,限制协议版本>=5.12.0150)
struct sam_put_urgent_req
{	CHAR		m_szUserName[41];				// 用户名称
	CHAR		m_szPassword[41];				// 用户密码
	DWORD		m_dwBranchID;					// 营业部ID
	WORD		m_wUrgentLen;					// 公告文本长度
	DWORD		m_dwReserved;					// 保留字段
	CHAR		m_szUrgent[1];					// 公告文本
};
struct sam_put_urgent_ans
{	BYTE		m_cReserved;					// 保留字段
};

// 列出目录全部内容(SAM_LIST_DIR,限制协议版本>=5.12.0156)
struct sam_list_dir_req
{	CHAR		m_szUserName[41];				// 用户名称
	CHAR		m_szPassword[41];				// 用户密码
	CHAR		m_szDir[256];					// 查看的目录
	LONG		m_nOffset;						// 起始序号
	WORD		m_wWantNum;						// 增加获取得记录条数
	DWORD		m_dwReserved;					// 保留字段
};
struct sam_list_dir
{	CHAR		m_szName[41];					// 文件或者文件夹名
	LBOOL		m_bDir:1;						// 是否是目录名
	LBOOL		m_bUnused:31;					// 保留位
	DWORD		m_dwLength;						// 文件大小
	LONG		m_tModified;					// 文件修改时间
};
struct sam_list_dir_ans
{	WORD		m_wCount;						// 目录或文件个数
	DWORD		m_dwReserved;					// 保留字段
	sam_list_dir m_Data[1];					// 目录或文件内容列表
};


// 创建目录(SAM_MAKE_DIR,限制协议版本>=5.12.0156)
struct sam_make_dir_req
{	CHAR		m_szUserName[41];				// 用户名称
	CHAR		m_szPassword[41];				// 用户密码
	CHAR		m_szDir[256];					// 创建或者删除目录
	LBOOL		m_bNewOrDel:1;					// 创建或删除标志
	LBOOL		m_bUnused:31;					// 保留位
	DWORD		m_dwReserved;					// 保留字段
};
struct sam_make_dir_ans
{	BYTE		m_cReserved;					// 保留字段
};

// 得到文件长度(SAM_GET_FILELEN,限制协议版本>=5.12.0156)
struct sam_get_filelen_req
{	CHAR		m_szUserName[41];				// 用户名称
	CHAR		m_szPassword[41];				// 用户密码
	WORD		m_wPathLen;						// 路径长度
	DWORD		m_dwReserved;					// 保留字段
	CHAR		m_szPath[1];					// 路径文本
};
struct sam_get_filelen_ans
{	DWORD		m_dwReserved;					// 保留字段
	DWORD		m_dwLength;						// 文件长度
};


// 读取文件片断(SAM_GET_FILE,限制协议版本>=5.12.0156)
struct sam_get_file_req
{	CHAR		m_szUserName[41];				// 用户名称
	CHAR		m_szPassword[41];				// 用户密码
	DWORD		m_dwOffset;						// 文件中的偏移
	WORD		m_wWantLen;						// 读取的长度
	WORD		m_wPathLen;						// 路径长度
	DWORD		m_dwReserved;					// 保留字段
	CHAR		m_szPath[1];					// 路径文本
};
struct sam_get_file_ans
{	WORD		m_wGotLen;						// 读取的长度
	BYTE		m_cReserved;					// 保留字段
	BYTE		m_acBuffer[1];					// 缓冲区
};

// 上传文件片断(SAM_PUT_FILE,限制协议版本>=5.12.0156)
struct sam_put_file_req
{	CHAR		m_szUserName[41];				// 用户名称
 	CHAR		m_szPassword[41];				// 用户密码
	CHAR		m_szPath[128];					// 文件路径
	DWORD		m_dwOffset;						// 文件偏移
	WORD		m_wBufferLen;					// 缓冲区长度
	DWORD		m_dwReserved;					// 保留字段
	BYTE		m_acBuffer[1];					// 缓冲区
};
struct sam_put_file_ans
{	WORD		m_wWroteLen;					// 写入长度
	BYTE		m_cReserved;					// 保留字段
};

// 重新启动服务(SAM_REBOOT,限制协议版本>=5.12.0156)
struct sam_reboot_req
{	CHAR		m_szUserName[41];				// 用户名称
	CHAR		m_szPassword[41];				// 用户密码
	DWORD		m_dwReserved;					// 保留字段
};
struct sam_reboot_ans
{	BYTE		m_cReserved;					// 保留字段
};

// 列出柜台信息(SAM_LIST_COUNTERS)
struct sam_list_counters_req
{	CHAR		m_szUserName[41];				// 用户名称
	CHAR		m_szPassword[41];				// 用户密码
	BYTE		m_cReserved;					// 保留字段
};
struct sam_list_counters_ans
{	BYTE		m_cReserved;
};

// 得到柜台状态(SAM_GET_COUNTER_STATUS)
struct sam_get_counter_status_req
{	CHAR		m_szUserName[41];				// 用户名称
	CHAR		m_szPassword[41];				// 用户密码
	BYTE		m_cReserved;					// 保留字段
};
struct sam_get_counter_status_ans
{	BYTE		m_cReserved;
};

// 列出全部客户(SAM_CLIENT_LIST,限制协议版本>=5.12.0156)
enum enumCLIENTSORTFLAG {CLIENT_SORTFLAG_NONE,CLIENT_SORTFLAG_HOT};
enum enumCLIENTFILTER {CLIENT_FILTER_NONE,CLIENT_FILTER_SOURCEIP,CLIENT_FILTER_INTERNETIP,CLIENT_FILTER_MAC,CLIENT_FILTER_OPUID};
struct sam_client_list_req
{	CHAR		m_szUserName[41];				// 用户名称
	CHAR		m_szPassword[41];				// 用户密码
	WORD		m_wType;						// 获取方式(0:获取全部 1:连接IP过滤 2:客户IP过滤 3:客户MAC过滤 4:客户号过滤)
	WORD		m_wSortFlag;					// 排序方式(0:不排序 1:按照调用次数排序)
	CHAR		m_szFilter[41];					// 过滤的相关信息,字符串或者IP信息
	DWORD		m_dwOffset;						// 开始序号
	WORD		m_wWantNum;						// 读取的个数
	DWORD		m_dwReserved;					// 保留字段
};
struct sam_client_list
{	DWORD		m_dwSessionID;					// 会话ID
	DWORD		m_dwSessionNo;					// 会话号
	IPV4		m_SourceIp;						// 来源地址
	systm_t		m_tCreated;						// 会话建立时间
	WORD		m_wClientType;					// 客户端类型
	DWORD		m_dwClientVer;					// 客户端版本
	IPV4		m_InternetIp;					// 操作IP
	MAC			m_Mac;							// 操作MAC
	CHAR		m_szUOrg[UORG_SIZE];			// 操作机构
	CHAR		m_szUID[UID_SIZE];				// 操作帐号
	DWORD		m_dwHisAppCallNum;				// 累计功能调用
};
struct sam_client_list_ans
{	WORD		m_wCount;						// 客户个数
	DWORD		m_dwReserved;					// 保留字段
	sam_client_list m_Data[1];					// 客户数据
};

// 断开指定客户连接(SAM_CLIENT_DROP,限制协议版本>=5.12.0156)
struct sam_client_drop_req
{	CHAR		m_szUserName[41];				// 用户名称
	CHAR		m_szPassword[41];				// 用户密码
	DWORD		m_dwChannelID;					// 通道ID
	DWORD		m_dwReserved;					// 保留字段
};
struct sam_client_drop_ans
{	BYTE		m_cReserved;					// 保留字段
};

// 向指定客户发送消息(SAM_CLIENT_MESSAGE,限制协议版本>=5.12.0156)
struct sam_client_message_req
{	CHAR		m_szUserName[41];				// 用户名称
	CHAR		m_szPassword[41];				// 用户密码
	DWORD		m_dwChannelID;					// 通道ID
	WORD		m_wMessageLen;					// 消息文本长度
	DWORD		m_dwReserved;					// 保留字段
	CHAR		m_szMessage[1];					// 消息文本
};
struct sam_client_message_ans
{	BYTE		m_cReserved;					// 保留字段
};


// 列出接入物理节点(SAM_RAWIP_LIST,限制协议版本>=5.12.0156)
enum enumRAWIPSORTFLAG {RAWIP_SORTFLAG_NONE,RAWIP_SORTFLAG_REFNUM,RAWIP_SORTFLAG_HISREFNUM,RAWIP_SORTFLAG_CREDIT,RAWIP_SORTFLAG_HISDENY};
enum enumRAWIPFILTER {RAWIP_FILTER_NONE,RAWIP_FILTER_DANGER,RAWIP_FILTER_FROZEN,RAWIP_FILTER_ACTIVE};
struct sam_rawip_list_req
{	CHAR		m_szUserName[41];				// 用户名称
	CHAR		m_szPassword[41];				// 用户密码
	DWORD		m_dwType;						// 获取方式(0:获取全部 1:获取危险地址 2:获取冻结地址 3:获取联机地址)
	WORD		m_wSortFlag;					// 排序方式(0:不排序 1:按照活动连接 2:按照累计连接 3.按照可信度 4.按照累计拒绝)
	DWORD		m_dwOffset;						// 开始序号
	WORD		m_wWantNum;						// 读取的个数
	DWORD		m_dwReserved;					// 保留字段
};
struct sam_rawip_list
{	IPV4		m_RawIp;						// 接入地址
	LONG		m_nAddrState;					// 当前状态
	DWORD		m_dwHisRefNum;					// 累计引用数
	DWORD		m_dwRefNum;						// 引用计数
	systm_t		m_tLastRef;						// 最后访问时间(不论是否被拒绝)
	DWORD		m_dwCredit;						// 信用值
	systm_t		m_tLastDanger;					// 最后进入危险状态时间
	systm_t		m_tLastFrozen;					// 最后进入冻结状态时间
	CHAR		m_szByUOrg[UORG_SIZE];			// 冻结机构
	CHAR		m_szByUID[UID_SIZE];			// 冻结用户
	systm_t		m_tLastDeny;					// 最后拒绝时间
	DWORD		m_dwHisDenyNum;					// 累计遭受攻击次数
};
struct sam_rawip_list_ans
{	WORD		m_wCount;						// 接入地址个数
	DWORD		m_dwReserved;					// 保留字段
	sam_rawip_list m_Data[1];					// 接入地址数据
};


// 退出当前连接(SAM_RAWIP_DROP,限制协议版本>=5.12.0156)
struct sam_rawip_drop_req
{	CHAR		m_szUserName[41];				// 用户名称
	CHAR		m_szPassword[41];				// 用户密码
	IPV4		m_RawIp;						// 接入地址
	DWORD		m_dwReserved;					// 保留字段
};
struct sam_rawip_drop_ans
{	BYTE		m_cReserved;					// 保留字段
};


// 冻结接入地址(SAM_RAWIP_FREEZE,限制协议版本>=5.12.0156)
struct sam_rawip_freeze_req
{	CHAR		m_szUserName[41];				// 用户名称
	CHAR		m_szPassword[41];				// 用户密码
	IPV4		m_RawIp;						// 接入地址
	DWORD		m_dwReserved;					// 保留字段
};
struct sam_rawip_freeze_ans
{	BYTE		m_cReserved;					// 保留字段
};


// 解冻接入地址(SAM_RAWIP_UNFREEZE,限制协议版本>=5.12.0156)
struct sam_rawip_unfreeze_req
{	CHAR		m_szUserName[41];				// 用户名称
	CHAR		m_szPassword[41];				// 用户密码
	IPV4		m_RawIp;						// 接入地址
	DWORD		m_dwReserved;					// 保留字段
};
struct sam_rawip_unfreeze_ans
{	BYTE		m_cReserved;					// 保留字段
};

// 接入IP信用获取和修改(SAM_RAWIP_CREDIT,限制协议版本>=5.12.0156)
struct sam_rawip_credit_req
{	CHAR		m_szUserName[41];				// 用户名称
	CHAR		m_szPassword[41];				// 用户密码
	IPV4		m_RawIp;						// 接入地址
	DWORD		m_dwCredit;						// 修改信用值
	DWORD		m_dwReserved;					// 保留字段
};
struct sam_rawip_credit_ans
{	BYTE		m_cReserved;					// 保留字段
};


// IP地址列表(SAM_IP_LIST,限制协议版本>=5.12.0156)
enum enumIPSORTFLAG {IP_SORTFLAG_NONE,IP_SORTFLAG_CREDIT,IP_SORTFLAG_HISDENY};
enum enumIPFILTER {IP_FILTER_NONE,IP_FILTER_DANGER,IP_FILTER_FROZEN,IP_FILTER_ACTIVE};
struct sam_ip_list_req
{	CHAR		m_szUserName[41];				// 用户名称
	CHAR		m_szPassword[41];				// 用户密码
	DWORD		m_dwType;						// 获取方式(0:获取全部 1:获取危险地址 2:获取冻结地址)
	WORD		m_wSortFlag;					// 排序方式(0:不排序 1.按照可信度 2.按照累计拒绝)
	DWORD		m_dwOffset;						// 开始序号
	WORD		m_wWantNum;						// 读取的个数
	DWORD		m_dwReserved;					// 保留字段
};
struct sam_ip_list
{	IPV4		m_ClientIp;						// 客户地址
	LONG		m_nAddrState;					// 当前状态
	systm_t		m_tLastRegister;				// 最后登记时间
	DWORD		m_dwCredit;						// 信用值
	systm_t		m_tLastDanger;					// 最后进入危险状态时间
	systm_t		m_tLastFrozen;					// 最后进入冻结状态时间
	CHAR		m_szByClientUOrg[UORG_SIZE];	// 冻结机构
	CHAR		m_szByClientUID[UID_SIZE];		// 冻结用户
	systm_t		m_tLastDeny;					// 最后拒绝时间
	DWORD		m_dwHisDenyNum;					// 累计遭受攻击次数
};
struct sam_ip_list_ans
{	WORD		m_wCount;						// 客户地址个数
	DWORD		m_dwReserved;					// 保留字段
	sam_ip_list m_Data[1];						// 客户地址数据
};


// IP地址冻结(注*,安全中心冻结需要通过SAM_FUNC_CALL实现)(SAM_IP_FREEZE,限制协议版本>=5.12.0156)
struct sam_ip_freeze_req
{	CHAR		m_szUserName[41];				// 用户名称
	CHAR		m_szPassword[41];				// 用户密码
	IPV4		m_ClientIp;						// 客户地址
	DWORD		m_dwReserved;					// 保留字段
};
struct sam_ip_freeze_ans
{	BYTE		m_cReserved;					// 保留字段
};


// IP地址解冻(SAM_IP_UNFREEZE,限制协议版本>=5.12.0156)
struct sam_ip_unfreeze_req
{	CHAR		m_szUserName[41];				// 用户名称
	CHAR		m_szPassword[41];				// 用户密码
	IPV4		m_ClientIp;						// 客户地址
	DWORD		m_dwReserved;					// 保留字段
};
struct sam_ip_unfreeze_ans
{	BYTE		m_cReserved;					// 保留字段
};


// IP信用获取和修改(SAM_IP_CREDIT,限制协议版本>=5.12.0156)
struct sam_ip_credit_req
{	CHAR		m_szUserName[41];				// 用户名称
	CHAR		m_szPassword[41];				// 用户密码
	IPV4		m_ClientIp;						// 客户地址
	DWORD		m_dwCredit;						// 修改信用值
	DWORD		m_dwReserved;					// 保留字段
};
struct sam_ip_credit_ans
{	BYTE		m_cReserved;					// 保留字段
};



// MAC地址列表(SAM_MAC_LIST,限制协议版本>=5.12.0156)
enum enumMACSORTFLAG {MAC_SORTFLAG_NONE,MAC_SORTFLAG_CREDIT,MAC_SORTFLAG_HISDENY};
enum enumMACFILTER {MAC_FILTER_NONE,MAC_FILTER_DANGER,MAC_FILTER_FROZEN,MAC_FILTER_ACTIVE};
struct sam_mac_list_req
{	CHAR		m_szUserName[41];				// 用户名称
	CHAR		m_szPassword[41];				// 用户密码
	DWORD		m_dwType;						// 获取方式(0:获取全部 1:获取危险地址 2:获取冻结地址)
	WORD		m_wSortFlag;					// 排序方式(0:不排序 1.按照可信度 2.按照累计拒绝)
	DWORD		m_dwOffset;						// 开始序号
	WORD		m_wWantNum;						// 读取的个数
	DWORD		m_dwReserved;					// 保留字段
};
struct sam_mac_list
{	MAC			m_ClientMac;					// 客户端地址
	LONG		m_nAddrState;					// 当前状态
	systm_t		m_tLastRegister;				// 最后登记时间
	DWORD		m_dwCredit;						// 信用值
	systm_t		m_tLastDanger;					// 最后进入危险状态时间
	systm_t		m_tLastFrozen;					// 最后进入冻结状态时间
	CHAR		m_szByClientUOrg[UORG_SIZE];	// 冻结机构
	CHAR		m_szByClientUID[UID_SIZE];		// 冻结用户
	systm_t		m_tLastDeny;					// 最后拒绝时间
	DWORD		m_dwHisDenyNum;					// 累计遭受攻击次数
};
struct sam_mac_list_ans
{	WORD		m_wCount;						// 客户地址个数
	DWORD		m_dwReserved;					// 保留字段
	sam_mac_list m_Data[1];					// 客户地址数据
};


// MAC地址冻结(注*,安全中心冻结需要通过SAM_FUNC_CALL实现)(SAM_MAC_FREEZE,限制协议版本>=5.12.0156)
struct sam_mac_freeze_req
{	CHAR		m_szUserName[41];				// 用户名称
	CHAR		m_szPassword[41];				// 用户密码
	MAC			m_ClientMac;					// 客户地址
	DWORD		m_dwReserved;					// 保留字段
};
struct sam_mac_freeze_ans
{	BYTE		m_cReserved;					// 保留字段
};


// MAC地址解冻(SAM_MAC_UNFREEZE,限制协议版本>=5.12.0156)
struct sam_mac_unfreeze_req
{	CHAR		m_szUserName[41];				// 用户名称
	CHAR		m_szPassword[41];				// 用户密码
	MAC			m_ClientMac;					// 客户地址
	DWORD		m_dwReserved;					// 保留字段
};
struct sam_mac_unfreeze_ans
{	BYTE		m_cReserved;					// 保留字段
};


// MAC信用获取和修改(SAM_MAC_CREDIT,限制协议版本>=5.12.0156)
struct sam_mac_credit_req
{	CHAR		m_szUserName[41];				// 用户名称
	CHAR		m_szPassword[41];				// 用户密码
	MAC			m_ClientMac;					// 客户地址
	DWORD		m_dwCredit;						// 修改信用值
	DWORD		m_dwReserved;					// 保留字段
};
struct sam_mac_credit_ans
{	BYTE		m_cReserved;					// 保留字段
};


// 线程列表(SAM_THREAD_LIST,限制协议版本>=5.12.0156)
enum enumTHREADSORTFLAG {THREAD_SORTFLAG_NONE,THREAD_SORTFLAG_ALIVE,THREAD_SORTFLAG_LASTCALL,THREAD_SORTFLAG_LASTBUSINESS,THREAD_SORTFLAG_WAITTIME,THREAD_SORTFLAG_PROCTIME,THREAD_SORTFLAG_HISCALL};
enum enumTHREADFILTER {THREAD_FILTER_NONE};
struct sam_thread_list_req
{	CHAR		m_szUserName[41];				// 用户名称
	CHAR		m_szPassword[41];				// 用户密码
	DWORD		m_dwType;						// 获取方式(0:获取全部)
	WORD		m_wSortFlag;					// 排序方式(0:不排序 1.上次心跳时间 2.上次调度时间 3.上次事务时间 4.等待时间 5.处理时间 6.累计事务)
	DWORD		m_dwOffset;						// 开始序号
	WORD		m_wWantNum;						// 读取的个数
	DWORD		m_dwReserved;					// 保留字段
};
struct sam_thread_list
{	DWORD			m_dwType;					// 线程类型
	DWORD			m_dwThreadID;				// 线程ID
	LBOOL			m_bBusy;					// 是否繁忙(线程)
	systm_t			m_tLastIdle;				// 上次空闲时间(线程)
	systm_t			m_tLastActive;				// 上次激活时间(线程)
	systm_t			m_tBusinessCreated;			// 事务创建时间(解包前)
	systm_t			m_tBusinessEntry;			// 事务进入处理时间(解包后)
	WORD			m_wReqNo;					// 当前事务的请求号
	CHAR			m_szCmdDesc[64];			// 当前事务的描述
	DWORD			m_dwInWaitTime;				// 在处理上消耗的时间(毫秒)
	DWORD			m_dwInProcTime;				// 在处理上消耗的时间(毫秒)
	DWORD			m_dwInApiTime;				// 在API上消耗的时间(毫秒)
	DWORD			m_dwHisBusinessNum;			// 累计处理事务数
};
struct sam_thread_list_ans
{	WORD		m_wCount;						// 线程个数
	DWORD		m_dwReserved;					// 保留字段
	sam_thread_list m_Data[1];					// 线程列表
};


// 线程状态获取和修改(SAM_THREAD_STATE,限制协议版本>=5.12.0156)
struct sam_thread_state_req
{	CHAR		m_szUserName[41];				// 用户名称
	CHAR		m_szPassword[41];				// 用户密码
	BYTE		m_cReserved;					// 保留字段
};
struct sam_thread_state_ans
{	BYTE		m_cReserved;					// 保留字段
};

// 功能列表(SAM_FUNCS_LIST,限制协议版本>=5.12.0156)
enum enumFUNCSORTFLAG {FUNC_SORTFLAG_NONE,FUNC_SORTFLAG_BOOSTLIMIT,FUNC_SORTFLAG_NEARIN,FUNC_SORTFLAG_AVGTIME,FUNC_SORTFLAG_HISCALL};
enum enumFUNCFILTER {FUNC_FILTER_NONE,FUNC_FILTER_CALLED,FUNC_FILTER_DISABLED,FUNC_FILTER_TIMELIMITED,FUNC_FILTER_BOOSTLIMITED,FUNC_FILTER_BOOSTREACH};
struct sam_funcs_list_req
{	CHAR		m_szUserName[41];				// 用户名称
	CHAR		m_szPassword[41];				// 用户密码
	DWORD		m_dwType;						// 获取方式(0:获取全部 1:获取调用过的 2:获取被禁用 3:获取限时开放 4:流量限制 5:流量超载)
	WORD		m_wSortFlag;					// 排序方式(0:不排序 1.流量上限 2.最近入站 3.平均耗时 4.累计调用)
	DWORD		m_dwOffset;						// 开始序号
	WORD		m_wWantNum;						// 读取的个数
	DWORD		m_dwReserved;					// 保留字段
};
struct sam_funcs_list
{	BYTE		m_cFuncType;					// 功能类型
	WORD		m_wFuncID;						// 功能ID
	CHAR		m_szDescription[41];			// 功能描述
	LBOOL		m_bNeedLog;						// 功能是否需要日志(其他配置)
	LBOOL		m_bTimeLimit;					// 功能是否限时开放(其他配置)
	LBOOL		m_bBoostLimit;					// 功能是否限制最大流量(其他配置)
	LONG		m_nBoostLimit;					// 功能限制流量数(其他配置)
	LBOOL		m_bDisabled;					// 功能是否临时禁用(动态数据)
	LONG		m_nHitCount;					// 功能调用次数(动态数据)
	LONG		m_nBoostCount;					// 功能流量(进入处理/每秒)次数(动态数据)
	LONG		m_nOutFlowCount;				// 功能流量(退出处理/每秒)次数(动态数据)
	FLOAT		m_fAverageTime;					// 功能平均耗时(退出队列计算)
};
struct sam_funcs_list_ans
{	WORD		m_wCount;						// 功能个数
	DWORD		m_dwReserved;					// 保留字段
	sam_funcs_list m_Data[1];					// 功能列表
};

// 禁止和允许指定功能(SAM_FUNCS_ENABLE,限制协议版本>=5.12.0156)
struct sam_funcs_enable_req
{	CHAR		m_szUserName[41];				// 用户名称
	CHAR		m_szPassword[41];				// 用户密码
	BYTE		m_cFuncType;					// 功能类型
	WORD		m_wFuncID;						// 功能ID
	LBOOL		m_bEnable:1;					// 使用允许和关闭功能
	LBOOL		m_bUnused:31;					// 其他字段
	DWORD		m_dwReserved;					// 保留字段
};
struct sam_funcs_enable_ans
{	BYTE		m_cReserved;					// 保留字段	
};


// 列出路由项(SAM_ROUTES_LIST,限制协议版本>=5.12.0156)
enum enumROUTESORTFLAG {ROUTE_SORTFLAG_NONE};
enum enumROUTEFILTER {ROUTE_FILTER_NONE};
struct sam_routes_list_req
{	CHAR		m_szUserName[41];				// 用户名称
	CHAR		m_szPassword[41];				// 用户密码
	DWORD		m_dwType;						// 获取方式(0:获取全部)
	WORD		m_wSortFlag;					// 排序方式(0:不排序)
	DWORD		m_dwOffset;						// 开始序号
	WORD		m_wWantNum;						// 读取的个数
	DWORD		m_dwReserved;					// 保留字段
};
struct sam_routes_list
{	LONG		m_nRouteNo;						// 路由号
	LONG		m_nRouteGuid;					// 路由项唯一ID
	BYTE		m_cFuncType;					// 功能类型
	BYTE		m_cRouteType;					// 路由类型(远程/本地)
	TCHAR		m_szRouteDesc[64];				// 路由描述
	LBOOL		m_bRouteError;					// 路由状态
	TCHAR		m_szRouteMemo[64];				// 路由备注
	DWORD		m_dwBalanceMode;				// 均衡模式
	LBOOL		m_bBalanceAsWhole;				// 对等均衡
	LONG		m_nMaxConnect;					// 最大连接数
};
struct sam_routes_list_ans
{	WORD		m_wCount;						// 路由个数
	DWORD		m_dwReserved;					// 保留字段
	sam_routes_list m_Data[1];					// 路由列表
};

// 重新连接对应的路由项(SAM_ROUTES_RESET,限制协议版本>=5.12.0156)
struct sam_routes_reset_req
{	CHAR		m_szUserName[41];				// 用户名称
	CHAR		m_szPassword[41];				// 用户密码
	LONG		m_nRouteGuid;					// 路由项唯一ID
	DWORD		m_dwReserved;					// 保留字段
};
struct sam_routes_reset_ans
{	BYTE		m_cReserved;					// 保留字段	
};


// 黑名单列表(注*,黑名单分为静态和动态)(SAM_BLACKLIST_LIST,限制协议版本>=5.12.0156)
struct sam_blacklist_list_req
{	CHAR		m_szUserName[41];				// 用户名称
	CHAR		m_szPassword[41];				// 用户密码
	DWORD		m_dwType;						// 类型
	DWORD		m_dwOffset;						// 开始序号
	DWORD		m_dwReserved;					// 保留字段
};
struct sam_blacklist_list
{	DWORD		m_dwRecNo;						// 记录序号
	DWORD		m_dwRawIp;						// 接入地址
};
struct sam_blacklist_list_ans
{	WORD		m_wCount;						// 黑名单个数
	DWORD		m_dwReserved;					// 保留字段
	sam_blacklist_list m_Data[1];				// 黑名单列表
};

// 黑名单增加(注*,黑名单分为静态和动态)(SAM_BLACKLIST_ADD,限制协议版本>=5.12.0156)
struct sam_blacklist_add_req
{	CHAR		m_szUserName[41];				// 用户名称
	CHAR		m_szPassword[41];				// 用户密码
	IPV4		m_IpFrom;						// 黑名单地址(起始)
	IPV4		m_IpEnd;						// 黑名单地址(结束)
	DWORD		m_dwReserved;					// 保留字段
};
struct sam_blacklist_add_ans
{	DWORD		m_dwRecNo;						// 记录序号
};

// 黑名单删除(SAM_BLACKLIST_DEL,限制协议版本>=5.12.0156)
struct sam_blacklist_del_req
{	CHAR		m_szUserName[41];				// 用户名称
	CHAR		m_szPassword[41];				// 用户密码
	DWORD		m_dwRecNo;						// 记录序号
	DWORD		m_dwReserved;					// 保留字段
};
struct sam_blacklist_del_ans
{	BYTE		m_cReserved;					// 保留字段
};


// 获取更多主站信息(SAM_INFO_MORE)
struct sam_info_more_req
{	CHAR		m_szUserName[41];				// 用户名称
	CHAR		m_szPassword[41];				// 用户密码
};
struct sam_info_more_ans
{	LONG		m_nModuleNum;					// 模块数
	struct  
	{	time_t	m_tLastLoginSucess;				// 最后一次成功登录时间
		LONG	m_nKeepLoginFailNum;			// 持续失败次数
		time_t	m_tLastAccessSucess;			// 最后一次成功访问时间
		LONG	m_nKeepAccessFailNum;			// 持续访问次数
		systm_t	m_tLast30Delays;				// 最近30笔
	} m_aModuleStatic[8];
	LONG		m_nQueueDepth;					// 当前队列深度
	LONG		m_nHisIncomeBusinessNum;		// 累计的入站请求数
	LONG		m_nHisFailBusinessNum;			// 累计失败请求数
	LONG		m_nHisSuccessBusinessNum;		// 累计成功请求数
	LONG		m_nHisTimeoutBusinessNum;		// 累计的超时请求数
	LONG		m_nHisOverflowBusinessNum;		// 累计的溢出请求数
	LONG		m_nHisInactiveConnectNum;		// 累计客户端异常数
	LONG		m_nHisViciousConnectNum;		// 累计恶意连接数
};

// 获取版本统计信息(SAM_INFO_VERSIONS)
struct sam_info_versions_req
{	CHAR		m_szUserName[41];				// 用户名称
	CHAR		m_szPassword[41];				// 用户密码
};
struct sam_info_veritem
{	WORD	m_wClientType;						// 客户端类型
	DWORD	m_dwClientVer;						// 客户端版本
	LONG	m_nTotalHit;						// 累计登录数
	LONG	m_nOnline;							// 在线人数
};
struct sam_info_versions_ans
{	LONG				m_nVersionNum;			// 版本数
	sam_info_veritem	m_aVersionStatic[1];	// 版本统计
};


//////////////////////////////////////////////////////////////////////////
// 标准错误号宏(PROTERR)
// (标准监控协议部分)
// (参见:ASE_Err.h)

#pragma pack()
#endif

