//////////////////////////////////////////////////////////////////////////
// RPC����Э��淶
// 1.�����Э��      (Э��ŷ�Χ: 4600-4650)
#ifndef __ASE_STDPROT_BRIDGE__H__
#define __ASE_STDPROT_BRIDGE__H__
#pragma pack(1)

// ����Э���Э���
STD_PROT SHORT BRIDGE_PUSHING		=	4600;					// ������



// ����Э��(BRIDGE_PUSHING)
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
