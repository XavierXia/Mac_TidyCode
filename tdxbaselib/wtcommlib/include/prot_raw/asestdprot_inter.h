//////////////////////////////////////////////////////////////////////////
// 标准互联协议规范定义文件
// 本文件定义:
//		1.共有互联协议定义 (协议号范围: 4450-4470)
//		2.外部互联协议定义,用于和外部服务器之间的通讯 (协议号范围: 4470-4490)
//		3.内部互联协议定义,用于内部服务器之间的通讯 (协议号范围: 4490-4506)
#ifndef __ASE_STDPROT_INTER__H__
#define __ASE_STDPROT_INTER__H__
#pragma pack(1)





// 外部互联协议(共享通道)
STD_PROT SHORT TC50_EXTRN_PREPARE_LOGIN		= 4470;			// (外部互联)登录准备(限制协议版本>=5.12.0195)
STD_PROT SHORT TC50_EXTRN_LOGIN				= 4471;			// (外部互联)登录(限制协议版本>=5.12.0195)
STD_PROT SHORT TC50_EXTRN_ALIVE				= 4472;			// (外部互联)存活包(限制协议版本>=5.12.0195)
STD_PROT SHORT TC50_EXTRN_GET_SERVER_INFO	= 4473;			// (外部互联)获取服务器配置(限制协议版本>=5.12.0195)

// 内部互联协议和状态交换协议(共享通道)
STD_PROT SHORT TC50_INTRA_ALIVE				= 4500;			// (内部互联)存活包
STD_PROT SHORT TC50_INTRA_GET_SERVER_INFO	= 4501;			// (内部互联)获取服务器配置
STD_PROT SHORT TC50_INTRA_PREPARE_LOGIN		= 4502;			// (内部互联)登录准备
STD_PROT SHORT TC50_INTRA_LOGIN				= 4503;			// (内部互联)登录
STD_PROT SHORT TC50_INTRA_ALIVE_REPORT		= 4504;			// (内部互联)下级节点存活报告(间隔10秒)
STD_PROT SHORT TC50_INTRA_STATUS_REPORT		= 4505;			// (内部互联)下级节点状态报告(间隔1分钟)







//////////////////////////////////////////////////////////////////////////
// 外部互联协议(必须RSA密钥交换)

// 外部互联登录准备(TC50_EXTRN_PREPARE_LOGIN)
// 登记客户端操作IP/MAC,客户端版本信息,交换密钥匙
struct tc50_extrn_prepare_login_req
{	IPV4		m_InetIp;									// 客户端IP地址(登录信息)
	MAC			m_Mac;										// 客户端MAC地址(登录信息)
	WORD		m_wClientType;								// 客户端类型
	WORD		m_wClientVer;								// 客户端版本
	WORD		m_wReleaseVer;								// 发行版本
	DWORD		m_bPeerPubKey:1;							// 客户端公钥标志
	DWORD		m_bReserved:31;								// 保留位,必须全空
	USHORT		m_nPeerPubKeyLen;							// 客户端公钥加密后长度
	BYTE		m_szPeerPubKey[516];						// 客户端公钥信息(使用服务器端加密) (BUGBUG:对于新版本,这个地方不够,必须分开保存)
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
	DWORD		m_dwExtSize;								// 扩展数据项(保留,未使用)
	BYTE		m_szExtData[1];								// 扩展数据区(保留,未使用)
};
struct tc50_extrn_prepare_login_ans
{	USHORT		m_nSessionKeyLen;							// SESSION_KEY加密后长度
	BYTE		m_szSessionKey[516];						// SESSION_KEY(使用客户端公钥加密)
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
	DWORD		m_dwExtSize;								// 扩展数据大小(保留,未使用)
	BYTE		m_szExtData[1];								// 扩展数据缓冲区(保留,未使用)
};


// 外部互联登录(TC50_EXTRN_LOGIN)
// 事务线程或外部处理
struct tc50_extrn_login_req
{	CHAR		m_szUOrg[UORG_SIZE];						// 机构
	CHAR		m_szUID[UID_SIZE];							// 用户
};
struct tc50_extrn_login_ans
{	CHAR		m_szUOrg[UORG_SIZE];						// 机构
	CHAR		m_szUID[UID_SIZE];							// 用户
	LONG		m_nRetCode;									// 登录返回结果
};

// 外部互联存活包(TC50_EXTRN_ALIVE,限制协议版本>=5.12.0151)
struct tc50_extrn_alive_req
{	CHAR		m_cReserved;								// 保留字段
};
struct tc50_extrn_alive_ans
{	CHAR		m_cReserved;								// 保留字段
};

// 外部互联获取服务器信息(TC50_EXTRN_GET_SERVER_INFO,限制协议版本>=5.12.0151)
struct tc50_extrn_get_server_info_req
{	CHAR		m_cReserved;								// 保留字段
};
struct tc50_extrn_get_server_info_ans
{	CHAR		m_cReserved;								// 保留字段
};








//////////////////////////////////////////////////////////////////////////
// 内部互联协议

// 内部互联存活包(TC50_INTRA_ALIVE)
// 通讯线程处理(严格禁止加密和压缩)
struct tc50_intra_alive_req
{	BYTE		m_cReserved;								// 保留信息
};
struct tc50_intra_alive_ans
{	BYTE		m_cReserved;								// 保留信息
};

// 内部互联取服务器信息(TC50_INTRA_GET_SERVER_INFO)
// 获取上一级服务器接入下级服务器的接入地址
struct tc50_intra_get_server_info_req
{	BYTE		m_cReserved;								// 保留信息
};
struct tc50_intra_get_server_info_ans
{	IPV4		m_InetIp;									// 客户端公网IP
};

// 内部互联准备登录(TC50_INTRA_PREPARE_LOGIN)
// 登记客户端操作IP/MAC,客户端版本信息
struct tc50_intra_prepare_login_req
{	IPV4		m_InetIp;									// 客户端IP地址(操作IP)
	MAC			m_Mac;										// 客户端MAC地址(操作MAC)
	WORD		m_wClientType;								// 客户端类型
	WORD		m_wClientVer;								// 客户端版本
	WORD		m_wReleaseVer;								// 发行版本
};
struct tc50_intra_prepare_login_ans
{	BYTE		m_cReserved;								// 保留字段
};


// 内部互联登录(TC50_INTRA_LOGIN)
// 事务线程或外部处理
// 送机构和用户并获取登录结果
struct tc50_intra_login_req
{	CHAR		m_szUOrg[UORG_SIZE];						// 机构
	CHAR		m_szUID[UID_SIZE];							// 用户
};
struct tc50_intra_login_ans
{	CHAR		m_szUOrg[UORG_SIZE];						// 机构
	CHAR		m_szUID[UID_SIZE];							// 用户
	LONG		m_nRetCode;									// 登陆返回结果
};

// 下级节点存活报告(间隔10秒)(TC50_INTRA_ALIVE_REPORT)
struct tc50_intra_alive_report
{	BYTE		m_cReserved;								// 保留字段
};

// 下级节点状态报告(间隔1分钟)(TC50_INTRA_STATUS_REPORT)
struct tc50_intra_status_report
{	BYTE		m_cReserved;								// 保留字段
};


#pragma pack()
#endif
