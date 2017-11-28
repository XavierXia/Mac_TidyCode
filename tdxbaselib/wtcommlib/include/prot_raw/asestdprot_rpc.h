//////////////////////////////////////////////////////////////////////////
// RPC����Э��淶
// 1.RPC�������Э��      (Э��ŷ�Χ: 4560-4600)
#ifndef __ASE_STDPROT_RPC__H__
#define __ASE_STDPROT_RPC__H__
#pragma pack(1)
#if defined(_COMPILE_BY_MSC_)
	#pragma warning(push)
	#pragma warning(disable:4200)
#endif

// ����Э���Э���
STD_PROT SHORT RPC_ALIVE		=	4560;					// RPC����
STD_PROT SHORT RPC_TOUCH		=	4561;					// RPC����
STD_PROT SHORT RPC_SESSIONKEY	=	4562;					// RPC������Կ
STD_PROT SHORT RPC_LOGIN		=	4563;					// RPC��¼
STD_PROT SHORT RPC_INVOKE		=	4565;					// RPC����
STD_PROT SHORT RPC_REGARPC		=	4566;					// RPCע���ΪARPC�ڵ�
STD_PROT SHORT RPC_ARPCEXEC		=	4580;					// RPC�������(ARPC)



// ����Э��(RPC_ALIVE)
struct rpc_alive_req
{
};
struct rpc_alive_ans
{
};


// ����Э��(RPC_TOUCH)
struct rpc_touch_req
{	CHAR m_szDevice[16];				// �豸��
	IPV6 m_EthernetIp;					// �ͻ���IP
	MAC m_Mac;							// �ͻ���MAC
	CHAR m_szBuildName[16];				// �ͻ��˱���汾
	WORD m_wClientType;					// �ͻ�������
	DWORD m_dwClientVer;				// �ͻ��˰汾
	BYTE m_cReserved;					// �����ֶ�
};

struct rpc_touch_ans
{	IPV6 m_InternetIp;					// ����IP
	BYTE m_cReserved;					// �����ֶ�
};



// ������ԿЭ��(RPC_SESSIONKEY)
struct rpc_sessionkey_req
{	IPV6		m_InternetIp;			// ����IP
	BYTE		m_cReserved;			// �����ֶ�
};

struct rpc_sessionkey_ans
{	BYTE		m_cReserved;			// �����ֶ�
};



// ����Э��(RPC_LOGIN)
struct rpc_login_req
{	DWORD		m_dwServID;				// ������ID(����ȫ��Ψһ)
	CHAR		m_szUsername[16];		// �û���
	CHAR		m_szPassword[16];		// ����
	BYTE		m_cReserved;			// �����ֶ�
};

struct rpc_login_ans
{	BYTE		m_cReserved;			// �����ֶ�
};


// ����Э��(RPC_INVOKE)
struct rpc_invoke_req
{	BYTE		m_acSequence[1];		// ����
};
struct rpc_invoke_aopt
{	BYTE		m_acSequence[0];		// ����
};
struct rpc_invoke_ans
{	BYTE		m_acSequence[1];		// ����
};


// RPCע���ΪARPC�ڵ�(RPC_REGARPC)
struct rpc_regarpc_req
{	DWORD		m_dwServID;				// ������ID
	CHAR		m_szSlotName[32];		// RPCע��������
};
struct rpc_regarpc_ans
{	BYTE		m_cReserved;			// �����ֶ�
};


// RPC�������(ARPC)����(RPC_ARPCEXEC)
struct rpc_arpcexec_Issued
{	BYTE		m_acSequence[1];		// ����
};

// RPC�������(ARPC)ȷ��(RPC_ARPCEXEC)
struct rpc_arpcexec_confirm
{	BYTE		m_acSequence[1];		// ����
};


#if defined(_COMPILE_BY_MSC_)
	#pragma warning(pop)
#endif
#pragma pack()
#endif
