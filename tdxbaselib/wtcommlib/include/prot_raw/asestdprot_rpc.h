//////////////////////////////////////////////////////////////////////////
// RPC调用协议规范
// 1.RPC调用相关协议      (协议号范围: 4560-4600)
#ifndef __ASE_STDPROT_RPC__H__
#define __ASE_STDPROT_RPC__H__
#pragma pack(1)
#if defined(_COMPILE_BY_MSC_)
	#pragma warning(push)
	#pragma warning(disable:4200)
#endif

// 基本协议和协议段
STD_PROT SHORT RPC_ALIVE		=	4560;					// RPC存活包
STD_PROT SHORT RPC_TOUCH		=	4561;					// RPC握手
STD_PROT SHORT RPC_SESSIONKEY	=	4562;					// RPC交换密钥
STD_PROT SHORT RPC_LOGIN		=	4563;					// RPC登录
STD_PROT SHORT RPC_INVOKE		=	4565;					// RPC调用
STD_PROT SHORT RPC_REGARPC		=	4566;					// RPC注册成为ARPC节点
STD_PROT SHORT RPC_ARPCEXEC		=	4580;					// RPC反向调用(ARPC)



// 心跳协议(RPC_ALIVE)
struct rpc_alive_req
{
};
struct rpc_alive_ans
{
};


// 握手协议(RPC_TOUCH)
struct rpc_touch_req
{	CHAR m_szDevice[16];				// 设备名
	IPV6 m_EthernetIp;					// 客户端IP
	MAC m_Mac;							// 客户端MAC
	CHAR m_szBuildName[16];				// 客户端编译版本
	WORD m_wClientType;					// 客户端类型
	DWORD m_dwClientVer;				// 客户端版本
	BYTE m_cReserved;					// 保留字段
};

struct rpc_touch_ans
{	IPV6 m_InternetIp;					// 公网IP
	BYTE m_cReserved;					// 保留字段
};



// 交换密钥协议(RPC_SESSIONKEY)
struct rpc_sessionkey_req
{	IPV6		m_InternetIp;			// 公网IP
	BYTE		m_cReserved;			// 保留字段
};

struct rpc_sessionkey_ans
{	BYTE		m_cReserved;			// 保留字段
};



// 握手协议(RPC_LOGIN)
struct rpc_login_req
{	DWORD		m_dwServID;				// 服务器ID(必须全局唯一)
	CHAR		m_szUsername[16];		// 用户名
	CHAR		m_szPassword[16];		// 密码
	BYTE		m_cReserved;			// 保留字段
};

struct rpc_login_ans
{	BYTE		m_cReserved;			// 保留字段
};


// 调用协议(RPC_INVOKE)
struct rpc_invoke_req
{	BYTE		m_acSequence[1];		// 序列
};
struct rpc_invoke_aopt
{	BYTE		m_acSequence[0];		// 序列
};
struct rpc_invoke_ans
{	BYTE		m_acSequence[1];		// 序列
};


// RPC注册成为ARPC节点(RPC_REGARPC)
struct rpc_regarpc_req
{	DWORD		m_dwServID;				// 服务器ID
	CHAR		m_szSlotName[32];		// RPC注册服务槽名
};
struct rpc_regarpc_ans
{	BYTE		m_cReserved;			// 保留字段
};


// RPC反向调用(ARPC)发起(RPC_ARPCEXEC)
struct rpc_arpcexec_Issued
{	BYTE		m_acSequence[1];		// 序列
};

// RPC反向调用(ARPC)确认(RPC_ARPCEXEC)
struct rpc_arpcexec_confirm
{	BYTE		m_acSequence[1];		// 序列
};


#if defined(_COMPILE_BY_MSC_)
	#pragma warning(pop)
#endif
#pragma pack()
#endif
