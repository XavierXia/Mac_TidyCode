//////////////////////////////////////////////////////////////////////////
// 标准客户端协议规范定义文件
//		1.客户端标准协议 (协议号范围: 3000-4200)
//		2.包含和客户端通讯的IX协议
// 当前文件包含:
//		Part.I		协议定义
//		Part.II		内部结构
//		Part.III	协议定义
//		Part.IV		错误号宏(PROTERR)
#ifndef __ASE_STDPROT_CLI__H__
#define __ASE_STDPROT_CLI__H__
#pragma pack(1)



//========================================================================================================================
// Part.I 协议号定义


// 客户端基本协议
//		客户端基本协议主要为客户端提供辅助性功能,客户端通过这些辅助性功能
//		和服务器完成登录准备、登录等工作
// 有关用户验证请求
// 会连续多次发起请求:
//		1.按照验证后得内容进行登录
//		2.按照登录得到的结果决定下一步处理
//		3.如果后台冻结,那么立即冻结处理
//		4.如果后台失败,那么立即冻结处理
//		5.如果后台故障,那么立即失败
//		6.如果后台正常,立即从结果中取得营业部以及
//        完整资金帐号,并发往安全中心进行数据验证
//		7.然后客户端进入程序并下载通告等一系列的信息
//		8.公告信息直接弹出
//		9.如果后台返回逻辑有问题,那么将进一步进行处理
STD_PROT SHORT TC50_GET_LOADER					= 3000;			// 读取服务器负载状况
STD_PROT SHORT TC50_ALIVE						= 3001;			// 客户端存活报告
STD_PROT SHORT TC50_GET_SERVER_INFO				= 3002;			// 获取服务器端基本配置
STD_PROT SHORT TC50_CHECK_UPDATE				= 3003;			// 获取最新版本信息
STD_PROT SHORT TC50_GET_INET_IP					= 3004;			// 获取客户端公网地址
STD_PROT SHORT TC50_PREPARE_LOGIN				= 3005;			// 准备登录协议
STD_PROT SHORT TC50_LOGIN						= 3006;			// 登录协议
STD_PROT SHORT TC50_GET_LOGIN_INFO				= 3007;			// 读取服务器登录信息
STD_PROT SHORT TC50_GET_CALLBOARD				= 3008;			// 获取服务器系统通告
STD_PROT SHORT TC50_GET_URGENT					= 3009;			// 获取服务器营业部公告
STD_PROT SHORT TC50_GET_BRANCH_LOADER			= 3010;			// 读取营业部负载状况(限制协议版本>=5.12.0149|5.10sp7)
STD_PROT SHORT TC50_HTTP_AGENT					= 3011;			// HTTP请求(限制协议版本>=5.12.0169)
STD_PROT SHORT TC50_RAW_CALL					= 3012;			// 简单调用
STD_PROT SHORT TC50_SIMP_CALL					= 3013;			// 原始调用
STD_PROT SHORT TC50_GET_DICT					= 3014;			// 获取字典

// 功能调用
//		功能调用的主要作用是对TC50屏蔽业务细节
//		目前主要的功能调用被应用于交易业务/安全帐号管理/呼叫中心/信息中心
//			交易业务功能调用--交易相关的全部功能
//			安全中心功能调用--安全帐号以及帐号管理相关的全部功能
//			呼叫中心功能调用--短讯服务等增值服务
//			信息中心功能调用--P2P以及经纪业务等功能
STD_PROT SHORT TC50_FUNC_CALL					= 4000;			// 交易业务功能调用
















//////////////////////////////////////////////////////////////////////////
// Part.II 内部结构定义

// IP_TACKER工作模式
#define IPTRACKMODE_LAN			(0)					// IPTRACKER模式:获取本地地址
#define IPTRACKMODE_THESERVER	(1)					// IPTRACKER模式:从服务器获取
#define IPTRACKMODE_3RDSERVER	(2)					// IPTRACKER模式:从其他服务器获取















//////////////////////////////////////////////////////////////////////////
// Part.III 协议定义

// 全局协议字典字段结构
#define REQ_ITEM_QSID				0				// 客户端券商标识(限制协议版本>=5.12.0171)
#define REQ_ITEM_PID				1				// 客户端产品标识(限制协议版本>=5.12.0171)
#define REQ_ITEM_LOGIN_DICT_LEN		2				// 登录字典长度(LOGIN_DICT,限制协议版本>=5.12.0171)
#define REQ_ITEM_SIGNATURE			3				// 证书签名(限制协议版本>=5.12.0178)
#define REQ_ITEM_SVRCODEPAGE		4				// 服务器代码页(限制协议版本>=5.12.0188)
#define REQ_ITEM_DICCODEPAGE		5				// 业务代码页(限制协议版本>=5.12.0188)

#define ANS_ITEM_URL				0				// 升级地址,最大256字节
#define ANS_ITEM_COMMENT			1				// 升级备注信息,最大2048字节
#define ANS_ITEM_ABSTRACT			2				// 升级摘要信息,最大2048字节,(各模块的MD5描述)
#define ANS_ITEM_IPTRACKER			3				// 服务器地址报告信息,不超过256字节,(存在公网地址报告服务器时返回)
#define ANS_ITEM_PLUGINFOS			4				// 服务器端插件MD5表(不匹配时候返回)
#define ANS_ITEM_ENTRYPOINTIDXS		5				// 营业部列表(不匹配时候返回)
#define ANS_ITEM_PUBLICKEY			6				// 服务器公钥(不匹配时候返回)
#define ANS_ITEM_SCINFOS			7				// 市场配置信息(不匹配时候返回)
#define ANS_ITEM_CALLBOARDTITLE		8				// 系统公告(标题)
#define ANS_ITEM_CALLBOARDSOURCE	9				// 系统公告(来源)
#define ANS_ITEM_CALLBOARDTEXT		10				// 系统公告(正文)
#define ANS_ITEM_URGENTTITLE		11				// 营业部公告(标题)
#define ANS_ITEM_URGENTSOURCE		12				// 营业部公告(来源)
#define ANS_ITEM_URGENTTEXT			13				// 营业部公告(正文)
#define ANS_ITEM_LOGIN_CCF			14				// 登录配置信息(LOGIN.CCF)
#define ANS_ITEM_LOGIN_DICT			15				// 登录字典(LOGIN_DICT)
#define ANS_ITEM_TRADE_CCF			16				// 交易配置
#define ANS_ITEM_TCNTR_DICT			17				// 交易中心数据字典
#define ANS_ITEM_SCNTR_DICT			18				// 安全中心数据字典
#define ANS_ITEM_ICNTR_DICT			19				// 信息中心数据字典
#define ANS_ITEM_CCNTR_DICT			20				// 呼叫中心数据字典
#define ANS_ITEM_BRANCHNAME			21				// 营业部名称
#define ANS_ITEM_ALARMTEXT			22				// 系统紧急状态提示文本(限制协议版本>=5.12.0141)
#define ANS_ITEM_DSNSEED			23				// DSN验证种子串(限制协议版本>=5.12.0149)
#define ANS_ITEM_SERVDESC			24				// 服务器描述(限制协议版本>=5.12.0156)
#define ANS_ITEM_SERVVERS			25				// 服务器版本(限制协议版本>=5.12.0171)
#define ANS_ITEM_UCNTR_DICT			26				// 用户管理中心数据字典(限制协议版本>=5.12.0171)
#define ANS_ITEM_ECNTR_DICT			27				// 客户服务平台数据字典(限制协议版本>=5.12.0171)
#define ANS_ITEM_CUSTOMPATCH		28				// 客户端用户补丁或者配置(限制协议版本>=5.12.0174)
#define ANS_ITEM_SIGNATURE			29				// 证书签名(限制协议版本>=5.12.0178)
#define ANS_ITEM_SERVTIME			30				// 服务器时间(限制协议版本>=5.12.0179)
#define ANS_ITEM_SERVID				31				// 服务器ID(限制协议版本>=5.12.0179)
#define ANS_ITEM_CONNID				32				// 连接ID(限制协议版本>=5.12.0179)
#define ANS_ITEM_SVRCODEPAGE		33				// 服务器代码页(限制协议版本>=5.12.0188)
#define ANS_ITEM_DICCODEPAGE		34				// 业务代码页(限制协议版本>=5.12.0188)

#define ANS_ITEM_TCNTR_DICT_V3		35				// 交易中心数据字典(限制协议版本>=5.12.0200)
#define ANS_ITEM_SCNTR_DICT_V3		36				// 安全中心数据字典(限制协议版本>=5.12.0200)
#define ANS_ITEM_ICNTR_DICT_V3		37				// 信息中心数据字典(限制协议版本>=5.12.0200)
#define ANS_ITEM_CCNTR_DICT_V3		38				// 呼叫中心数据字典(限制协议版本>=5.12.0200)

#define ANS_ITEM_DICT_ALONE			39				// 单独获取数据字典(限制协议版本>=5.12.0201)



//////////////////////////////////////////////////////////////////////////
// 取得服务器负载信息(TC50_GET_LOADER)
// 通讯线程处理(严格禁止加密和压缩)
struct tc50_get_loader_req
{	WORD		m_wReserved;						// (废弃,必须为空)入口点ID
};													// 5.10sp7前的版本未检查客户端入参会导致崩溃,干脆送空
struct tc50_get_loader_ans
{	DWORD		m_dwNowConnectNum;					// 当前在线人数(含管理和监控连接)
	DWORD		m_dwMaxConnectNum;					// 最大允许在线人数(含管理和监控连接)
	DWORD		m_bBackEndException:1;				// 是否柜台异常(限制协议版本>=5.12.0173)
	DWORD		m_dwReserved:31;					// (保留,对5.10等版本,本处返回空)
};

//////////////////////////////////////////////////////////////////////////
// 客户端存活报告(TC50_ALIVE)
// 通讯线程处理(严格禁止加密和压缩)
struct tc50_alive_req
{	DWORD		m_dwBranchID;						// 客户端营业部ID(如为空,不返回营业部公告信息)
	DWORD		m_tCallboard;						// 客户端缓存的最后系统公告的发布时间
	DWORD		m_tUrgent;							// 客户端缓存的最后营业部公告的发布时间
};
struct tc50_alive_ans
{	DWORD		m_bCallboardFlag:1;					// 公告牌刷新标志
	DWORD		m_bUrgentFlag:1;					// 营业部公告刷新标志
	DWORD		m_bReserved:30;						// 保留位,全空
};

//////////////////////////////////////////////////////////////////////////
// 获取服务器信息(TC50_GET_SERVER_INFO)
// 通讯线程处理(严格禁止加密和压缩)
struct tc50_get_server_info_req
{	DWORD		m_bWantEntryPointList:1;			// 是否需要获取入口点列表
	DWORD		m_bWantCallboard:1;					// 是否需要获取系统公告
	DWORD		m_bScInfo2Supported:1;				// 客户端是否支持SCINFO2.INI(限制协议版本>=5.12.0149)
	DWORD		m_bWantLoginCcf:1;					// 是否需要获取登录配置(LOGIN.CCF,限制协议版本>=5.12.0149)
	DWORD		m_bDSNSupported:1;					// 客户端是否支持DSN验证(限制协议版本>=5.12.0149)
	DWORD		m_dwClientType:16;					// 客户端类别(登录类别,限制协议版本>=5.12.0149或5.10sp7)
	DWORD		m_bBroadcastSupported:1;			// 客户端是否支持广播(限制协议版本>=5.12.0149或5.10sp7)
	DWORD		m_bBrokerClient:1;					// 客户端是否为机构版客户端,超过客户端对业务频度不检查(限制协议版本>=5.12.0156)
	DWORD		m_bDownPatch:1;						// 客户端是否需要下载补丁(限制协议版本>=5.12.0174)
	DWORD		m_bV6OrMoreHigh:1;					// 客户端是否是V6以上的版本
	DWORD		m_bBkgdConn:1;						// 后台连接
	DWORD		m_bPKIV2:1;							// 使用2代PKI标准(支持RSA2048和ECC,限制协议版本>5.13)
	DWORD		m_bReserved:5;						// 保留位,必须全空
	MD5BIN		m_md5PluginInfos;					// 插件信息MD5,MD5BIN结构
	MD5BIN		m_md5EntryPointIdxs;				// 入口点列表MD5,MD5BIN结构
	MD5BIN		m_md5PublicKey;						// 服务器公钥MD5,MD5BIN结构
	MD5BIN		m_md5ScInfos;						// 市场配置信息MD5,MD5BIN结构
	DWORD		m_tCallboard;						// 客户端缓存的最后系统公告的发布时间
};
struct tc50_get_server_info_req1 :  public tc50_get_server_info_req
{	MD5BIN		m_md5LoginCcf;						// 登录配置MD5(限制协议版本>=5.12.0149)
	DWORD		m_dwExtSize;						// 扩展数据项(限制协议版本>=5.12.0149)
	BYTE		m_szExtData[1];						// 扩展数据区(限制协议版本>=5.12.0149)
};
// + ANS_ITEM_IPTRACKER								// 服务器地址报告信息,不超过256字节,(存在公网地址报告服务器时返回)
// + ANS_ITEM_PLUGINFOS								// 服务器端插件MD5表(不匹配时候返回)
// + ANS_ITEM_ENTRYPOINTIDXS						// 营业部列表(不匹配时候返回)
// + ANS_ITEM_PUBLICKEY								// 服务器公钥(不匹配时候返回)
// + ANS_ITEM_SCINFOS								// 市场配置信息(不匹配时候返回)
// + ANS_ITEM_CALLBOARDTITLE						// 系统公告(标题)
// + ANS_ITEM_CALLBOARDSOURCE						// 系统公告(来源)
// + ANS_ITEM_CALLBOARDTEXT							// 系统公告(正文)
// + ANS_ITEM_ALARMTEXT								// 系统紧急状态提示文本(文本,限制协议版本>=5.12.0141)
// + ANS_ITEM_LOGIN_CCF								// 登录配置信息(LOGIN.CCF,限制协议版本>=5.12.0149)
// + ANS_ITEM_DSNSEED								// DSN验证种子序列(限制协议版本>=5.12.0149)
// + ANS_ITEM_SERVDESC								// 服务器描述(限制协议版本>=5.12.0156)
// + ANS_ITEM_SERVVERS								// 服务器版本(限制协议版本>=5.12.0171)
struct tc50_get_server_info_ans
{	IPV4		m_InetIp;							// 客户端公网IP
	WORD		m_wDefEntryPointID;					// 默认入口点ID
	CHAR		m_szQsid[QSID_SIZE];				// 券商标识
	BYTE		m_nIpTrackerMode;					// IPTRACKER工作方式
	BYTE		m_nUpgradeMode;						// 自动升级模式
	BYTE		m_bHasSSL;							// 安全方式[是否支持SSL]
	BYTE		m_bHasAuthpass;						// 安全方式[是否支持认证口令]
	BYTE		m_bHasDigitCert;					// 安全方式[是否支持软证书]
	BYTE		m_bHasOTP;							// 安全方式[是否支持令牌卡]
	BYTE		m_bHasUkey;							// 安全方式[是否支持UKEY]
	BYTE		m_bHasSMSAuth:1;					// 安全方式[是否支持短信口令]
	BYTE		m_bHasRCAuth:1;						// 安全方式[是否支持矩阵卡]
	BYTE		m_bHasMOTPAuth:1;					// 安全方式[是否支持手机令牌]
	BYTE		m_bHasElseAuthority:3;				// 安全方式[保留]
	BYTE		m_nPKIType:2;						// PKI类型
	BYTE		m_cPKIBitIdx;						// PKI密钥位数索引
	BYTE		m_cSessionAlgoType;					// SESSION算法类型
	BYTE		m_cSessionKeyLenIdx;				// SESSION密钥长度索引
	BYTE		m_cInternalSignal:1;				// 是否支持包内数字签名
	BYTE		m_cExternalSignal:1;				// 是否支持封包数字签名
	BYTE		m_bScntrSupported:1;				// 服务器支持安全中心(限制协议版本>5.12.0140,对应tc50_prepare_login_req1)
	BYTE		m_bAlarmStatus:1;					// 系统紧急状态(限制协议版本>=5.12.0141)
	BYTE		m_bScntrErrCtlOn:1;					// 服务器是否指出安全中心容错机制(限制协议版本>=5.12.0143)
	BYTE		m_bScInfo2Supported:1;				// 服务器是否支持SCINFO2.INI(LOGIN.CCF,限制协议版本>=5.12.0149)
	BYTE		m_bDSNSupported:1;					// 服务器是否支持DSN验证(限制协议版本>=5.12.0149)
	BYTE		m_bClientTypePermit:1;				// 客户端类型是否准许接入(限制协议版本>=5.12.0149或5.10sp7)
	BYTE		m_cHashAlgoType;					// HASH算法类型
	WORD		m_bReserved2:1;						// (废弃)对客户端的公钥进行加密传送(限制协议版本<5.12.0149或5.10sp7)
	WORD		m_bHasScntr:1;						// 是否支持安全中心
	WORD		m_bHasIcntr:1;						// 是否支持信息中心
	WORD		m_bHasCcntr:1;						// 是否支持呼叫中心
	WORD		m_bLimitedMode:1;					// 客户端是否使用受限风格(限制协议版本>=5.12.0149或5.10sp7)
	WORD		m_bBroadcastSupported:1;			// 客户端是否支持广播(限制协议版本>=5.12.0149或5.10sp7)
	WORD		m_bIsV2_PrepareLogin:1;				// 是否支持服务器预登录扩展协议V2(限制协议版本>=5.12.0149,对应tc50_prepare_login_req2)
	WORD		m_bVipHost:1;						// 是否为VIP主站(限制协议版本>=5.12.0172)
	WORD		m_bJCKHJY:1;						// 是否支持集成客户校验
	WORD		m_bBackEndException:1;				// 后端连接是否正常(最少存在一个后端存在故障)
	WORD		m_bIsV1_GetLoginInfo:1;				// 是否支持获取登录信息V1(限制协议版本>=5.12.0182,对应tc50_get_logininfo_req1)
	WORD		m_bIsV3_IX:1;						// 是否支持新字典格式(限制协议版本>=5.12.0200,对应tc50_get_logininfo_req1)
	WORD		m_bReserved3:4;						// 保留5位,全空
	DWORD		m_dwCallboardUpDate;				// 系统公告截至日期(YYYYMMDD格式,如果为0表示无公告)
	DWORD		m_tCallboard;						// 系统公告发布时间(如果为0表示无公告)
	DWORD		m_dwExtSize;						// 扩展数据项
	BYTE		m_szExtData[1];						// 扩展数据区
};

//////////////////////////////////////////////////////////////////////////
// 检查自动升级(TC50_CHECK_UPDATE)
// 通讯线程处理(严格禁止加密和压缩)
struct tc50_check_update_req
{	WORD		m_wClientType;						// 客户端类型
	WORD		m_wClientVer;						// 客户端版本
	WORD		m_wReleaseVer;						// 发行版本
	DWORD		m_bWantURL:1;						// 是否需要升级地址
	DWORD		m_bWantComment:1;					// 是否需要升级备注信息
	DWORD		m_bWantAbstract:1;					// 是否需要升级摘要文件
	DWORD		m_bReserved:29;						// 保留位,必须全空
};
// + ANS_ITEM_URL									// 升级地址,最大256字节
// + ANS_ITEM_COMMENT								// 升级备注信息,最大2048字节
// + ANS_ITEM_ABSTRACT								// 升级摘要信息,最大2048字节,(各模块的MD5描述)
struct tc50_check_update_ans
{	DWORD		m_bIsLastestVer:1;					// 是否是最新版本
	DWORD		m_bDiscardVer:1;					// 是否版本已经不可用(强制升级)
	DWORD		m_bReserved:30;						// 保留位,全空
	WORD		m_wClientVer;						// 客户端版本
	WORD		m_wReleaseVer;						// 发行版本
	DWORD		m_dwExtSize;						// 扩展数据项
	BYTE		m_szExtData[1];						// 扩展数据区
};

//////////////////////////////////////////////////////////////////////////
// 公网地址报告协议(TC50_GET_INET_IP,存在公网地址报告服务器时调用)
// 通讯线程处理(严格禁止加密和压缩)
struct tc50_get_inet_ip_req
{
};
struct tc50_get_inet_ip_ans
{	IPV4		m_InetIp;							// 客户端公网IP
};


//////////////////////////////////////////////////////////////////////////
// 登录准备过程(TC50_PREPARE_LOGIN)
// 事务线程处理或远程处理
// 登记客户端操作IP/MAC,客户端版本信息,交换密钥匙,获取登陆相关参数
struct tc50_prepare_login_hdr
{	WORD		m_wEntryPointID;					// 入口点ID
};
struct tc50_prepare_login_req
{	IPV4		m_InetIp;							// 客户端IP地址(登录信息)
	MAC			m_Mac;								// 客户端MAC地址(登录信息)
	WORD		m_wClientType;						// 客户端类型
	WORD		m_wClientVer;						// 客户端版本
	WORD		m_wReleaseVer;						// 发行版本
	DWORD		m_bPeerPubKey:1;					// 客户端公钥标志
	DWORD		m_bWantLoginCcf:1;					// 是否需要获取登录设置(LOGIN.CCF,限制协议版本>=5.12.0149)
	DWORD		m_bSuperVersion:1;					// 是否是超级版本(非超级版本会验证版本信息)(限制协议版本>=5.12.0191)
	DWORD		m_bReserved:29;						// 保留位,必须全空
	USHORT		m_nPeerPubKeyLen;					// 客户端公钥加密后长度
	BYTE		m_szPeerPubKey[516];				// 客户端公钥信息(使用服务器端加密)(BUGBUG:对于新版本,这个地方不够,必须分开保存)
													// RSA算法位数,分块大小和密钥长度的关系为:分块大小=(密钥长度+7)/8
													// 即:INT((KEY_BIT+7)/8)
													// 系统目前支持最大1024位,分块大小为128字节,以后可扩充至2048/4096位
													// 分块大小分别为256字节以及512字节
													// 加密数据缓冲区大小和原始大小的关系是:加密大小=(原始大小+分块大小-1)/分块大小*分块大小+4
													// 即INT((LENGTH+BLOCK_SIZE-1)/BLOCK_SIZE)*BLOCK_SIZE+4
													// RSA公钥信息长度260字节,其加密缓冲区长度分别是
													// 1024位:(260+128-1)/128*128+4=388字节
													// 2048位:(260+256-1)/256*256+4=516字节
													// 4096位:(260+512-1)/512*512+4=516字节
													// 参见<<RSA加密缓冲区长度计算.XLS>>
	MD5BIN		m_md5LoginCcfDiscard;				// 登录配置MD5(废弃,限制协议版本<5.12.0149)
	MD5BIN		m_md5LoginDict;						// 登录字典的MD5
};
struct tc50_prepare_login_req1 : public tc50_prepare_login_req
{	MD5BIN		m_md5ScntrDict;						// 安全中心字典的MD5(限制协议版本>=5.12.0140)
};
struct tc50_prepare_login_req2 : public tc50_prepare_login_req1
{	DWORD		m_dwExtSize;						// 扩展数据项(限制协议版本>=5.12.0149)
	BYTE		m_szExtData[1];						// 扩展数据区(限制协议版本>=5.12.0149)
};
// - ANS_ITEM_LOGIN_CCF								// 登录配置信息(LOGIN.CCF,限制协议版本<5.12.0149)
// + ANS_ITEM_LOGIN_DICT							// 登录字典(LOGIN_DICT)
// + ANS_ITEM_SCNTR_DICT							// 安全中心字典(SCNTR_DICT,限制协议版本>=5.12.0140)
struct tc50_prepare_login_ans
{	USHORT		m_nSessionKeyLen;					// SESSION_KEY加密后长度
	BYTE		m_szSessionKey[516];				// SESSION_KEY(使用客户端公钥加密)
													// RSA算法位数,分块大小和密钥长度的关系为:分块大小=(密钥长度+7)/8
													// 即:INT((KEY_BIT+7)/8)
													// 系统目前支持最大1024位,分块大小为128字节,以后可扩充至2048/4096位
													// 分块大小分别为256字节以及512字节
													// 加密数据缓冲区大小和原始大小的关系是:加密大小=(原始大小+分块大小-1)/分块大小*分块大小+4
													// 即INT((LENGTH+BLOCK_SIZE-1)/BLOCK_SIZE)*BLOCK_SIZE+4
													// SESSION_KEY信息长度最高1024位,即128字节,其加密缓冲区长度分别是
													// 1024位:(128+128-1)/128*128+4=132字节
													// 2048位:(128+256-1)/256*256+4=260字节
													// 4096位:(128+512-1)/512*512+4=516字节
													// 参见<<RSA加密缓冲区长度计算.XLS>>
	DWORD		m_dwExtSize;						// 扩展数据大小
	BYTE		m_szExtData[1];						// 扩展数据缓冲区
};


//////////////////////////////////////////////////////////////////////////
// 登录完成(TC50_LOGIN)
// 事务线程或外部处理
struct tc50_login_hdr
{	DWORD		m_tStartupTime;						// 上次连接时,服务器启动时间
	WORD		m_wEntryPointID;					// 登录时的入口点ID
	FUNCHDR		m_hdr;								// 功能调用头信息(包括客户端地址信息以及营业部信息)
};
struct tc50_login_req
{	FUNCBDY		m_bdy;								// 请求数据体(包含客户端认证信息)
};
struct tc50_login_ans
{	DWORD		m_bNeedGetLoginInfo:1;				// 客户端重新启动标志(服务器因某种原因被重置)
	DWORD		m_bReserved:31;						// 保留位,全空
	DWORD		m_tStartupTime;						// 上次连接时,服务器启动时间
	LONG		m_nRetCode;							// DLL返回结果
	FUNCBDY		m_bdy;								// 应答数据体(包含营业部ID,认证状态,新生成的SESSION_KEY)
};


// 登录预处理(TC50_SIMP_CALL)
// 事务线程或外部处理
struct tc50_simp_call_hdr
{	WORD		m_wEntryPointID;					// 登录时的入口点ID
	FUNCHDR		m_hdr;								// 功能调用头信息(包括客户端地址信息以及营业部信息)
};
struct tc50_simp_call_req
{	FUNCBDY		m_bdy;								// 请求数据体(包含客户端认证信息)
};
struct tc50_simp_call_ans
{	DWORD		m_bReserved;						// 保留位,全空
	LONG		m_nRetCode;							// DLL返回结果
	FUNCBDY		m_bdy;								// 应答数据体(包含营业部ID,认证状态,新生成的SESSION_KEY)
};

//////////////////////////////////////////////////////////////////////////
// 获取用户配置(TC50_GET_LOGIN_INFO)
// 事务线程或外部处理
struct tc50_get_logininfo_hdr
{	DWORD		m_dwBranchID;						// 营业部ID
};
struct tc50_get_logininfo_req
{	DWORD		m_bWantUrgent:1;					// 是否需要获取营业部公告
	DWORD		m_bWantScntrDict:1;					// 是否需要安全字典(限制协议版本>=5.12.0149)
	DWORD		m_bGetDictAlone:1;					// 是否可以支持大字典获取(限制协议版本>=5.12.201)
	DWORD		m_bReserved:29;						// 保留位,必须全空
	DWORD		m_tUrgent;							// 客户端缓存的最后营业部公告的发布时间
	MD5BIN		m_md5TradeCcf;						// TRADE_CCF文件的MD5信息
	MD5BIN		m_amd5Dicts[6];						// 当前数据字典的MD5信息(5.12.0171更新扩充)
};
struct tc50_get_logininfo_req1 : public tc50_get_logininfo_req
{	WORD		m_acbDicts[6];						// 当前数据字典的长度信息(5.12.0171更新扩充)
};
// + ANS_ITEM_URGENTTITLE							// 营业部公告标题
// + ANS_ITEM_URGENTSOURCE							// 营业部公告来源
// + ANS_ITEM_URGENTTEXT							// 营业部公告正文
// + ANS_ITEM_TRADE_CCF								// 交易配置
// + ANS_ITEM_TCNTR_DICT							// 交易中心数据字典
// + ANS_ITEM_SCNTR_DICT							// 安全中心数据字典(限制协议版本>=5.12.0149)
// + ANS_ITEM_ICNTR_DICT							// 信息中心数据字典(限制协议版本>=5.12.0149)
// + ANS_ITEM_CCNTR_DICT							// 呼叫中心数据字典(限制协议版本>=5.12.0149)
// + ANS_ITEM_BRANCHNAME							// 营业部名称
// + ANS_ITEM_UCNTR_DICT							// 用户管理中心数据字典(限制协议版本>=5.12.0171)
// + ANS_ITEM_ECNTR_DICT							// 客户服务平台数据字典(限制协议版本>=5.12.0171)
struct tc50_get_logininfo_ans
{	DWORD		m_dwUrgentUpDate;					// 营业部公告截至日期(YYYYMMDD格式,如果为0表示无公告)
	DWORD		m_tUrgent;							// 营业部通告更新时间(如果为0表示无公告)
	DWORD		m_dwExtSize;						// 扩展数据大小
	BYTE		m_szExtData[1];						// 扩展数据缓冲区
};


//////////////////////////////////////////////////////////////////////////
// 获取服务器系统通告(TC50_GET_DICT,限制协议版本>=5.12.0201)
// 通讯线程处理
struct tc50_get_dict_req
{	DWORD		m_dwBranchID;						// 营业部ID
	BYTE		m_cFuncType;						// 功能类型
	MD5BIN		m_md5Dict;							// 当前数据字典的MD5信息
	DWORD		m_cbDict;							// 当前数据字典的大小
	DWORD		m_cbOffset;							// 字典偏移位置
};
struct tc50_get_dict_ans
{	MD5BIN		m_md5Dict;							// 当前数据字典的MD5信息
	DWORD		m_cbDict;							// 全部长度
	DWORD		m_cbOffset;							// 字典偏移位置
	DWORD		m_cbPart;							// 返回长度
	BYTE		m_acDict[1];						// 字典内容
};


//////////////////////////////////////////////////////////////////////////
// 获取服务器系统通告(TC50_GET_CALLBOARD)
// 通讯线程处理
struct tc50_get_callboard_req
{
};
// + ANS_ITEM_CALLBOARDTITLE						// 系统公告(标题)
// + ANS_ITEM_CALLBOARDSOURCE						// 系统公告(来源)
// + ANS_ITEM_CALLBOARDTEXT							// 系统公告(正文)
struct tc50_get_callboard_ans
{	DWORD		m_dwCallboardUpDate;				// 系统公告截至日期(YYYYMMDD格式,如果为0表示无公告)
	DWORD		m_tCallboard;						// 系统公告发布时间(如果为0表示无公告)
	DWORD		m_dwExtSize;						// 扩展数据大小
	BYTE		m_szExtData[1];						// 扩展数据缓冲区(含标题/来源/正文)
};


//////////////////////////////////////////////////////////////////////////
// 获取营业部公告(TC50_GET_URGENT)
// 通讯线程处理
struct tc50_get_urgent_req
{	DWORD		m_dwBranchID;						// 营业部ID
};
// + ANS_ITEM_URGENTTITLE							// 营业部公告标题
// + ANS_ITEM_URGENTSOURCE							// 营业部公告来源
// + ANS_ITEM_URGENTTEXT							// 营业部公告正文
struct tc50_get_urgent_ans
{	DWORD		m_dwUrgentUpDate;					// 营业部公告截至日期(YYYYMMDD格式,如果为0表示无公告)
	DWORD		m_tUrgent;							// 营业部公告发布时间(如果为0表示无公告)
	DWORD		m_dwExtSize;						// 扩展数据大小
	BYTE		m_szExtData[1];						// 扩展数据缓冲区(含标题/来源/正文)
};


//////////////////////////////////////////////////////////////////////////
// 取得营业部负载信息(TC50_GET_BRANCH_LOADER,限制协议版本>=5.12.0149或5.10sp7)
// 通讯线程处理(严格禁止加密和压缩)
struct tc50_get_branch_loader_req
{	WORD		m_wEntryPointID;					// 入口点ID
};
struct tc50_get_branch_loader_ans
{	DWORD		m_dwNowConnectNum;					// 当前在线人数(含管理和监控连接)
	DWORD		m_dwMaxConnectNum;					// 最大允许在线人数(含管理和监控连接)
	DWORD		m_dwGuessLoader;					// 负载(如果送入的入口点ID非空则返回对应营业部的负载)
};


//////////////////////////////////////////////////////////////////////////
// 交易业务功能调用(TC50_FUNC_CALL)
// 事务线程或外部处理
struct tc50_func_call_hdr
{	BYTE		m_cFlag;							// 标志字段
	FUNCHDR		m_hdr;								// 功能调用头信息
};
struct tc50_func_call_req
{	FUNCBDY		m_bdy;								// 请求数据体
};
struct tc50_func_call_ans
{	LONG		m_nRetCode;							// DLL返回数据
	FUNCBDY		m_bdy;								// 请求数据体
};



//////////////////////////////////////////////////////////////////////////
// 原始功能调用(TC50_RAW_CALL)
// 事务线程或外部处理
struct tc50_raw_call_req
{	DWORD		m_dwSize;							// 请求长度
	BYTE		m_szBuffer[1];						// 请求缓冲区
};
struct tc50_raw_call_ans
{	LONG		m_nRetCode;							// DLL返回数据
	DWORD		m_dwSize;							// 应答长度
	BYTE		m_szBuffer[1];						// 应答缓冲区
};












//////////////////////////////////////////////////////////////////////////
// Part.IV 错误号宏定义
// (交易中心和IMSERVER服务器部分)
// (参见:ASE_Err.h)





//////////////////////////////////////////////////////////////////////////
// Part.V 兼容旧版本的定义,物理含义变更
#define NULL_TDXBRANCHID			NULL_ENTRYPOINTID		// 无入口点ID(原虚拟营业部)
#define NULL_REALBRANCHID			NULL_BRANCHID			// 无营业部ID(原营业部)
#define ANS_ITEM_TDXBRANCHIDXS		ANS_ITEM_ENTRYPOINTIDXS
typedef ENTRYPOINTIDX TDXBRANCHIDX,*LPTDXBRANCHIDX;





#pragma pack()
#endif
