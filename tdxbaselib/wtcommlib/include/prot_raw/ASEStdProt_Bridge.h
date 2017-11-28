//////////////////////////////////////////////////////////////////////////
// RPC调用协议规范
// 1.桥相关协议      (协议号范围: 4600-4650)
#ifndef __ASE_STDPROT_BRIDGE__H__
#define __ASE_STDPROT_BRIDGE__H__
#pragma pack(1)

// 基本协议和协议段
STD_PROT SHORT BRIDGE_PUSHING		=	4600;					// 桥推送



// 心跳协议(BRIDGE_PUSHING)
struct bridge_pushing_aopt
{	DWORD	m_idSession;
	DWORD	m_dwTunnelData;
	WORD	m_wOrgAnsNo;
};
struct bridge_pushing_ans
{
};

#pragma pack()
#endif
