//////////////////////////////////////////////////////////////////////////
// ��׼����Э��淶�����ļ�
// ���ļ�����:
//		1.���л���Э�鶨�� (Э��ŷ�Χ: 4450-4470)
//		2.�ⲿ����Э�鶨��,���ں��ⲿ������֮���ͨѶ (Э��ŷ�Χ: 4470-4490)
//		3.�ڲ�����Э�鶨��,�����ڲ�������֮���ͨѶ (Э��ŷ�Χ: 4490-4506)
#ifndef __ASE_STDPROT_INTER__H__
#define __ASE_STDPROT_INTER__H__
#pragma pack(1)





// �ⲿ����Э��(����ͨ��)
STD_PROT SHORT TC50_EXTRN_PREPARE_LOGIN		= 4470;			// (�ⲿ����)��¼׼��(����Э��汾>=5.12.0195)
STD_PROT SHORT TC50_EXTRN_LOGIN				= 4471;			// (�ⲿ����)��¼(����Э��汾>=5.12.0195)
STD_PROT SHORT TC50_EXTRN_ALIVE				= 4472;			// (�ⲿ����)����(����Э��汾>=5.12.0195)
STD_PROT SHORT TC50_EXTRN_GET_SERVER_INFO	= 4473;			// (�ⲿ����)��ȡ����������(����Э��汾>=5.12.0195)

// �ڲ�����Э���״̬����Э��(����ͨ��)
STD_PROT SHORT TC50_INTRA_ALIVE				= 4500;			// (�ڲ�����)����
STD_PROT SHORT TC50_INTRA_GET_SERVER_INFO	= 4501;			// (�ڲ�����)��ȡ����������
STD_PROT SHORT TC50_INTRA_PREPARE_LOGIN		= 4502;			// (�ڲ�����)��¼׼��
STD_PROT SHORT TC50_INTRA_LOGIN				= 4503;			// (�ڲ�����)��¼
STD_PROT SHORT TC50_INTRA_ALIVE_REPORT		= 4504;			// (�ڲ�����)�¼��ڵ����(���10��)
STD_PROT SHORT TC50_INTRA_STATUS_REPORT		= 4505;			// (�ڲ�����)�¼��ڵ�״̬����(���1����)







//////////////////////////////////////////////////////////////////////////
// �ⲿ����Э��(����RSA��Կ����)

// �ⲿ������¼׼��(TC50_EXTRN_PREPARE_LOGIN)
// �Ǽǿͻ��˲���IP/MAC,�ͻ��˰汾��Ϣ,������Կ��
struct tc50_extrn_prepare_login_req
{	IPV4		m_InetIp;									// �ͻ���IP��ַ(��¼��Ϣ)
	MAC			m_Mac;										// �ͻ���MAC��ַ(��¼��Ϣ)
	WORD		m_wClientType;								// �ͻ�������
	WORD		m_wClientVer;								// �ͻ��˰汾
	WORD		m_wReleaseVer;								// ���а汾
	DWORD		m_bPeerPubKey:1;							// �ͻ��˹�Կ��־
	DWORD		m_bReserved:31;								// ����λ,����ȫ��
	USHORT		m_nPeerPubKeyLen;							// �ͻ��˹�Կ���ܺ󳤶�
	BYTE		m_szPeerPubKey[516];						// �ͻ��˹�Կ��Ϣ(ʹ�÷������˼���) (BUGBUG:�����°汾,����ط�����,����ֿ�����)
															// RSA�㷨λ��,�ֿ��С����Կ���ȵĹ�ϵΪ:�ֿ��С=(��Կ����+7)/8
															// ��:INT((KEY_BIT+7)/8)
															// ϵͳĿǰ֧�����1024λ,�ֿ��СΪ128�ֽ�,�Ժ��������2048/4096λ
															// �ֿ��С�ֱ�Ϊ256�ֽ��Լ�512�ֽ�
															// �������ݻ�������С��ԭʼ��С�Ĺ�ϵ��:���ܴ�С=(ԭʼ��С+�ֿ��С-1)/�ֿ��С*�ֿ��С+4
															// ��INT((LENGTH+BLOCK_SIZE-1)/BLOCK_SIZE)*BLOCK_SIZE+4
															// RSA��Կ��Ϣ����260�ֽ�,����ܻ��������ȷֱ���
															// 1024λ:(260+128-1)/128*128+4=388�ֽ�
															// 2048λ:(260+256-1)/256*256+4=516�ֽ�
															// 4096λ:(260+512-1)/512*512+4=516�ֽ�
															// �μ�<<RSA���ܻ��������ȼ���.XLS>>
	DWORD		m_dwExtSize;								// ��չ������(����,δʹ��)
	BYTE		m_szExtData[1];								// ��չ������(����,δʹ��)
};
struct tc50_extrn_prepare_login_ans
{	USHORT		m_nSessionKeyLen;							// SESSION_KEY���ܺ󳤶�
	BYTE		m_szSessionKey[516];						// SESSION_KEY(ʹ�ÿͻ��˹�Կ����)
															// RSA�㷨λ��,�ֿ��С����Կ���ȵĹ�ϵΪ:�ֿ��С=(��Կ����+7)/8
															// ��:INT((KEY_BIT+7)/8)
															// ϵͳĿǰ֧�����1024λ,�ֿ��СΪ128�ֽ�,�Ժ��������2048/4096λ
															// �ֿ��С�ֱ�Ϊ256�ֽ��Լ�512�ֽ�
															// �������ݻ�������С��ԭʼ��С�Ĺ�ϵ��:���ܴ�С=(ԭʼ��С+�ֿ��С-1)/�ֿ��С*�ֿ��С+4
															// ��INT((LENGTH+BLOCK_SIZE-1)/BLOCK_SIZE)*BLOCK_SIZE+4
															// SESSION_KEY��Ϣ�������1024λ,��128�ֽ�,����ܻ��������ȷֱ���
															// 1024λ:(128+128-1)/128*128+4=132�ֽ�
															// 2048λ:(128+256-1)/256*256+4=260�ֽ�
															// 4096λ:(128+512-1)/512*512+4=516�ֽ�
															// �μ�<<RSA���ܻ��������ȼ���.XLS>>
	DWORD		m_dwExtSize;								// ��չ���ݴ�С(����,δʹ��)
	BYTE		m_szExtData[1];								// ��չ���ݻ�����(����,δʹ��)
};


// �ⲿ������¼(TC50_EXTRN_LOGIN)
// �����̻߳��ⲿ����
struct tc50_extrn_login_req
{	CHAR		m_szUOrg[UORG_SIZE];						// ����
	CHAR		m_szUID[UID_SIZE];							// �û�
};
struct tc50_extrn_login_ans
{	CHAR		m_szUOrg[UORG_SIZE];						// ����
	CHAR		m_szUID[UID_SIZE];							// �û�
	LONG		m_nRetCode;									// ��¼���ؽ��
};

// �ⲿ��������(TC50_EXTRN_ALIVE,����Э��汾>=5.12.0151)
struct tc50_extrn_alive_req
{	CHAR		m_cReserved;								// �����ֶ�
};
struct tc50_extrn_alive_ans
{	CHAR		m_cReserved;								// �����ֶ�
};

// �ⲿ������ȡ��������Ϣ(TC50_EXTRN_GET_SERVER_INFO,����Э��汾>=5.12.0151)
struct tc50_extrn_get_server_info_req
{	CHAR		m_cReserved;								// �����ֶ�
};
struct tc50_extrn_get_server_info_ans
{	CHAR		m_cReserved;								// �����ֶ�
};








//////////////////////////////////////////////////////////////////////////
// �ڲ�����Э��

// �ڲ���������(TC50_INTRA_ALIVE)
// ͨѶ�̴߳���(�ϸ��ֹ���ܺ�ѹ��)
struct tc50_intra_alive_req
{	BYTE		m_cReserved;								// ������Ϣ
};
struct tc50_intra_alive_ans
{	BYTE		m_cReserved;								// ������Ϣ
};

// �ڲ�����ȡ��������Ϣ(TC50_INTRA_GET_SERVER_INFO)
// ��ȡ��һ�������������¼��������Ľ����ַ
struct tc50_intra_get_server_info_req
{	BYTE		m_cReserved;								// ������Ϣ
};
struct tc50_intra_get_server_info_ans
{	IPV4		m_InetIp;									// �ͻ��˹���IP
};

// �ڲ�����׼����¼(TC50_INTRA_PREPARE_LOGIN)
// �Ǽǿͻ��˲���IP/MAC,�ͻ��˰汾��Ϣ
struct tc50_intra_prepare_login_req
{	IPV4		m_InetIp;									// �ͻ���IP��ַ(����IP)
	MAC			m_Mac;										// �ͻ���MAC��ַ(����MAC)
	WORD		m_wClientType;								// �ͻ�������
	WORD		m_wClientVer;								// �ͻ��˰汾
	WORD		m_wReleaseVer;								// ���а汾
};
struct tc50_intra_prepare_login_ans
{	BYTE		m_cReserved;								// �����ֶ�
};


// �ڲ�������¼(TC50_INTRA_LOGIN)
// �����̻߳��ⲿ����
// �ͻ������û�����ȡ��¼���
struct tc50_intra_login_req
{	CHAR		m_szUOrg[UORG_SIZE];						// ����
	CHAR		m_szUID[UID_SIZE];							// �û�
};
struct tc50_intra_login_ans
{	CHAR		m_szUOrg[UORG_SIZE];						// ����
	CHAR		m_szUID[UID_SIZE];							// �û�
	LONG		m_nRetCode;									// ��½���ؽ��
};

// �¼��ڵ����(���10��)(TC50_INTRA_ALIVE_REPORT)
struct tc50_intra_alive_report
{	BYTE		m_cReserved;								// �����ֶ�
};

// �¼��ڵ�״̬����(���1����)(TC50_INTRA_STATUS_REPORT)
struct tc50_intra_status_report
{	BYTE		m_cReserved;								// �����ֶ�
};


#pragma pack()
#endif
