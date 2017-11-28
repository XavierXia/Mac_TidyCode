//////////////////////////////////////////////////////////////////////////
// 基本公网服务协议规范定义文件
// 1.基本公网服务协议基本定义  (协议号范围: 9900-10000)
// 2.基本公网服务协议兼容定义  (协议号范围: 3000-4200)
#ifndef __ASE_STDPROT_INET__H__
#define __ASE_STDPROT_INET__H__
#pragma pack(1)
#if defined(_COMPILE_BY_MSC_)
	#pragma warning(push)
	#pragma warning(disable:4200)
#endif

//////////////////////////////////////////////////////////////////////////
// 功能号定义

// 基本功能号定义
STD_PROT WORD INET_BALANCE					= 9900;		// 均衡协议
STD_PROT WORD INET_TOUCH					= 9901;		// 握手协议
STD_PROT WORD INET_SSLSHAKE					= 9902;		// SSL密钥交换协议
STD_PROT WORD INET_TQL						= 9803;		// TQL协议(ROSE协议)
STD_PROT WORD INET_TJS						= 9804;		// TJS协议(ROSE协议)
STD_PROT WORD INET_ALIVE					= 9905;		// 存活包协议
STD_PROT WORD INET_QUIT						= 9906;		// 登出协议
STD_PROT WORD INET_9907						= 9907;		// (已废弃,原IX协议调用,并入TQL和TJS处理)
STD_PROT WORD INET_REDIRECT					= 9908;		// 转向协议调用
STD_PROT WORD INET_VERSION					= 9909;		// 版本查询
STD_PROT WORD INET_PATCH					= 9910;		// 下载补丁
STD_PROT WORD INET_DOWNLOAD					= 9911;		// 下载文件
STD_PROT WORD INET_PUBLISH					= 9912;		// 公告协议
STD_PROT WORD INET_FINDSYMBOL				= 9913;		// 搜索股票
STD_PROT WORD INET_BRIDGE					= 9914;		// 增加会话桥


// 兼容功能号定义(这个部分的功能号和原有系统冲突)
STD_PROT WORD DEPRECATION_INET_BALANCE		= 3000;		// 均衡协议
STD_PROT WORD DEPRECATION_INET_TOUCH		= 3001;		// 握手协议
STD_PROT WORD DEPRECATION_INET_ALIVE		= 3002;		// 存活包协议
STD_PROT WORD DEPRECATION_INET_QUIT			= 3003;		// 登出协议
STD_PROT WORD DEPRECATION_INET_3004			= 3004;		// (已废弃,原IX协议调用,并入TQL和TJS处理)
STD_PROT WORD DEPRECATION_INET_REDIRECT		= 3005;		// 转向协议调用
STD_PROT WORD DEPRECATION_INET_VERSION		= 3006;		// 版本查询
STD_PROT WORD DEPRECATION_INET_PATCH		= 3007;		// 下载补丁
STD_PROT WORD DEPRECATION_INET_DOWNLOAD		= 3008;		// 下载文件
STD_PROT WORD DEPRECATION_INET_PUBLISH		= 3009;		// 公告协议



//////////////////////////////////////////////////////////////////////////
// 协议结构定义


// 均衡协议
struct inet_balance_req
{	WORD	m_wEntryPointID;				// 入口点ID
	IPV6	m_EthernetIp;					// 客户IP地址信息(主机序)
	MAC		m_Mac;							// 客户MAC地址信息
	WORD	m_wClientType;					// 客户端类别
	DWORD	m_dwClientVer;					// 客户端版本
};
struct inet_balance_ans
{	BYTE	m_cFlag;						// 标志
	DWORD	m_dwMaxSession;					// 服务器支持的最大会话数
	DWORD	m_dwNowSession;					// 服务器当前的会话数
	DWORD	m_dwMaxConnect;					// 服务器支持的最大连接数
	DWORD	m_dwNowConnect;					// 服务器当前的连接数
	LONG	m_tStartup;						// 服务器启动时间
	LONG	m_tNow;							// 服务器当前时间
};


// 握手协议
struct inet_touch_req
{	CHAR	m_szDevice[16];					// 设备名字
	IPV6	m_EthernetIp;					// 客户IP地址信息(主机序)
	MAC		m_Mac;							// 客户MAC地址信息
	CHAR	m_szBuildName[16];				// 版本名(如iPad,iPhone,iMac)
	WORD	m_wClientType;					// 客户端类别
	DWORD	m_dwClientVer;					// 客户端版本
	WORD	m_wEntryPointID;				// 入口点ID
	BYTE	m_cPersistentFlag;				// 0:短连接 1:长连接
	CHAR	m_szTouchKey[17];				// 会话密钥(对称加密:服务器应答数据加密密钥)
	BYTE	m_cEncryptLv;					// 0:不加密 1:低级别加密 2:SSL
	BYTE	m_cLatestPKIType;				// 客户端支持的最新PKI类型
};
struct inet_touch_ans
{	IPV6	m_InternetIp;					// 公网IP地址信息
	DWORD	m_dwMaxSession;					// 服务器支持的最大会话数
	DWORD	m_dwNowSession;					// 服务器当前的会话数
	DWORD	m_dwMaxConnect;					// 服务器支持的最大连接数
	DWORD	m_dwNowConnect;					// 服务器当前的连接数
	LONG	m_tStartup;						// 服务器启动时间
	LONG	m_tNow;							// 服务器当前时间
	BYTE	m_acOptional[0];				// 选项信息内容
};


// SSL密钥交换
struct inet_sslshake_req
{	BYTE	m_cReserved;					// 保留信息
	BYTE	m_acOptional[0];				// 选项信息内容
};
struct inet_sslshake_ans
{	BYTE	m_cReserved;					// 保留信息
	BYTE	m_acOptional[0];				// 选项信息内容
};




// TQL调用
struct inet_tql_req { BYTE m_acSeq[0]; };
struct inet_tql_ans { BYTE m_acSeq[0]; };


// TJS调用
struct inet_tjs_req { BYTE m_acSeq[0]; };
struct inet_tjs_ans { BYTE m_acSeq[0]; };


// 心跳协议
struct inet_alive_req
{	BYTE	m_cUnused;						// (保留未用)
};
struct inet_alive_ans
{	BYTE	m_cUnused;						// (保留未用)
};


// 退出协议
struct inet_quit_req
{	BYTE	m_cUnused;						// (保留未用)
};
struct inet_quit_ans
{	BYTE	m_cUnused;						// (保留未用)
};



// INET_9907和DEPRECATION_INET_3004
// 已废弃,原IX协议调用,并入TQL和TJS处理)



// 转发协议
struct inet_redirect_ropt
{	WORD		m_wReqNo;					// 请求号
	BYTE		m_cTarget;					// 转发目标
};
struct inet_redirect_ropt1 : public inet_redirect_ropt
{	BYTE		m_bUseBridge;				// 桥标志
};



// 版本查询
struct inet_version_req
{	CHAR	m_szBuildName[16];				// 版本名称(比如iPhone,iPad)
	WORD	m_wClientType;					// 客户端类别
	DWORD	m_dwClientVer;					// 客户端版本
};
struct inet_version_ans
{	WORD	m_wOptionalLen;					// 选项信息长度
	BYTE	m_acOptional[1];				// 选项信息内容(升级信息)
};


// 补丁获取
struct inet_patch_req
{	CHAR	m_szBuildName[16];				// 版本名称(比如iPhone,iPad)
	LONG	m_nOffset;						// 读取偏移
	WORD	m_wPartLen;						// 读取大小
	IHASH	m_Hash;							// 补丁HASH
};
struct inet_patch_ans
{	IHASH	m_Hash;							// 文件的HASH结构
	WORD	m_wPartLen;						// 分段大小
	BYTE	m_acPart[1];					// 分段内容
};


// 下载文件
struct inet_download_req
{	CHAR	m_szName[16];					// 共享
	CHAR	m_szPath[32];					// 文件路径(全小写)
	LONG	m_nOffset;						// 读取偏移
	WORD	m_wPartLen;						// 读取大小
	IHASH	m_Hash;							// 补丁HASH
};
struct inet_download_ans
{	IHASH	m_Hash;							// 文件的HASH结构
	WORD	m_wPartLen;						// 分段大小
	BYTE	m_acPart[1];					// 分段内容
};


// 获取公告
struct inet_publish_req
{	CHAR	m_szPath[32];					// 文件路径(全小写)
	LONG	m_nOffset;						// 读取偏移
	WORD	m_wPartLen;						// 读取大小
	IHASH	m_Hash;							// 补丁HASH
};
struct inet_publish_ans
{	IHASH	m_Hash;							// 文件的HASH结构
	WORD	m_wPartLen;						// 分段大小
	BYTE	m_acPart[1];					// 分段内容
};


// 搜索代码
struct inet_findsymbol_req
{	CHAR	m_szCode[7];					// 代码(\0结束)
	LONG	m_nOffset;						// 偏移
	BYTE	m_cWantCount;					// 请求个数
	BYTE	m_bRestrict:1;					// 精确匹配
	BYTE	m_bFindByClass:1;				// 分类查找
	BYTE	m_bFindSHSZ:1;					// 查找深沪市场
	BYTE	m_bFindHK:1;					// 查找港股市场
	BYTE	m_bFindQH:1;					// 查找期货市场
	BYTE	m_cReserved:3;					// 保留字节
};
struct inet_findsymbol_ans
{	BYTE	m_cGotCount;					// 实际读取到的个数
	BYTE	m_cReserved;					// 保留字节
	WORD	m_cbSymbolInfos;				// 符号区长度
	BYTE	m_acSymbolInfos[1];				// 符号区内容
};


// 会话桥
struct inet_bridge_req
{	BYTE	m_cTarget;						// 创建到某目标的桥
};
struct inet_bridge_ans
{	BYTE	m_cStatus;						// 状态
};




//////////////////////////////////////////////////////////////////////////
// 应用级异常错误号
// (基本公网服务协议部分)
// (参见:ASE_Err.h)

#if defined(_COMPILE_BY_MSC_)
	#pragma warning(pop)
#endif
#pragma pack()
#endif
