//////////////////////////////////////////////////////////////////////////
// ������������Э��淶�����ļ�
// 1.������������Э���������  (Э��ŷ�Χ: 9900-10000)
// 2.������������Э����ݶ���  (Э��ŷ�Χ: 3000-4200)
#ifndef __ASE_STDPROT_INET__H__
#define __ASE_STDPROT_INET__H__
#pragma pack(1)
#if defined(_COMPILE_BY_MSC_)
	#pragma warning(push)
	#pragma warning(disable:4200)
#endif

//////////////////////////////////////////////////////////////////////////
// ���ܺŶ���

// �������ܺŶ���
STD_PROT WORD INET_BALANCE					= 9900;		// ����Э��
STD_PROT WORD INET_TOUCH					= 9901;		// ����Э��
STD_PROT WORD INET_SSLSHAKE					= 9902;		// SSL��Կ����Э��
STD_PROT WORD INET_TQL						= 9803;		// TQLЭ��(ROSEЭ��)
STD_PROT WORD INET_TJS						= 9804;		// TJSЭ��(ROSEЭ��)
STD_PROT WORD INET_ALIVE					= 9905;		// ����Э��
STD_PROT WORD INET_QUIT						= 9906;		// �ǳ�Э��
STD_PROT WORD INET_9907						= 9907;		// (�ѷ���,ԭIXЭ�����,����TQL��TJS����)
STD_PROT WORD INET_REDIRECT					= 9908;		// ת��Э�����
STD_PROT WORD INET_VERSION					= 9909;		// �汾��ѯ
STD_PROT WORD INET_PATCH					= 9910;		// ���ز���
STD_PROT WORD INET_DOWNLOAD					= 9911;		// �����ļ�
STD_PROT WORD INET_PUBLISH					= 9912;		// ����Э��
STD_PROT WORD INET_FINDSYMBOL				= 9913;		// ������Ʊ
STD_PROT WORD INET_BRIDGE					= 9914;		// ���ӻỰ��


// ���ݹ��ܺŶ���(������ֵĹ��ܺź�ԭ��ϵͳ��ͻ)
STD_PROT WORD DEPRECATION_INET_BALANCE		= 3000;		// ����Э��
STD_PROT WORD DEPRECATION_INET_TOUCH		= 3001;		// ����Э��
STD_PROT WORD DEPRECATION_INET_ALIVE		= 3002;		// ����Э��
STD_PROT WORD DEPRECATION_INET_QUIT			= 3003;		// �ǳ�Э��
STD_PROT WORD DEPRECATION_INET_3004			= 3004;		// (�ѷ���,ԭIXЭ�����,����TQL��TJS����)
STD_PROT WORD DEPRECATION_INET_REDIRECT		= 3005;		// ת��Э�����
STD_PROT WORD DEPRECATION_INET_VERSION		= 3006;		// �汾��ѯ
STD_PROT WORD DEPRECATION_INET_PATCH		= 3007;		// ���ز���
STD_PROT WORD DEPRECATION_INET_DOWNLOAD		= 3008;		// �����ļ�
STD_PROT WORD DEPRECATION_INET_PUBLISH		= 3009;		// ����Э��



//////////////////////////////////////////////////////////////////////////
// Э��ṹ����


// ����Э��
struct inet_balance_req
{	WORD	m_wEntryPointID;				// ��ڵ�ID
	IPV6	m_EthernetIp;					// �ͻ�IP��ַ��Ϣ(������)
	MAC		m_Mac;							// �ͻ�MAC��ַ��Ϣ
	WORD	m_wClientType;					// �ͻ������
	DWORD	m_dwClientVer;					// �ͻ��˰汾
};
struct inet_balance_ans
{	BYTE	m_cFlag;						// ��־
	DWORD	m_dwMaxSession;					// ������֧�ֵ����Ự��
	DWORD	m_dwNowSession;					// ��������ǰ�ĻỰ��
	DWORD	m_dwMaxConnect;					// ������֧�ֵ����������
	DWORD	m_dwNowConnect;					// ��������ǰ��������
	LONG	m_tStartup;						// ����������ʱ��
	LONG	m_tNow;							// ��������ǰʱ��
};


// ����Э��
struct inet_touch_req
{	CHAR	m_szDevice[16];					// �豸����
	IPV6	m_EthernetIp;					// �ͻ�IP��ַ��Ϣ(������)
	MAC		m_Mac;							// �ͻ�MAC��ַ��Ϣ
	CHAR	m_szBuildName[16];				// �汾��(��iPad,iPhone,iMac)
	WORD	m_wClientType;					// �ͻ������
	DWORD	m_dwClientVer;					// �ͻ��˰汾
	WORD	m_wEntryPointID;				// ��ڵ�ID
	BYTE	m_cPersistentFlag;				// 0:������ 1:������
	CHAR	m_szTouchKey[17];				// �Ự��Կ(�ԳƼ���:������Ӧ�����ݼ�����Կ)
	BYTE	m_cEncryptLv;					// 0:������ 1:�ͼ������ 2:SSL
	BYTE	m_cLatestPKIType;				// �ͻ���֧�ֵ�����PKI����
};
struct inet_touch_ans
{	IPV6	m_InternetIp;					// ����IP��ַ��Ϣ
	DWORD	m_dwMaxSession;					// ������֧�ֵ����Ự��
	DWORD	m_dwNowSession;					// ��������ǰ�ĻỰ��
	DWORD	m_dwMaxConnect;					// ������֧�ֵ����������
	DWORD	m_dwNowConnect;					// ��������ǰ��������
	LONG	m_tStartup;						// ����������ʱ��
	LONG	m_tNow;							// ��������ǰʱ��
	BYTE	m_acOptional[0];				// ѡ����Ϣ����
};


// SSL��Կ����
struct inet_sslshake_req
{	BYTE	m_cReserved;					// ������Ϣ
	BYTE	m_acOptional[0];				// ѡ����Ϣ����
};
struct inet_sslshake_ans
{	BYTE	m_cReserved;					// ������Ϣ
	BYTE	m_acOptional[0];				// ѡ����Ϣ����
};




// TQL����
struct inet_tql_req { BYTE m_acSeq[0]; };
struct inet_tql_ans { BYTE m_acSeq[0]; };


// TJS����
struct inet_tjs_req { BYTE m_acSeq[0]; };
struct inet_tjs_ans { BYTE m_acSeq[0]; };


// ����Э��
struct inet_alive_req
{	BYTE	m_cUnused;						// (����δ��)
};
struct inet_alive_ans
{	BYTE	m_cUnused;						// (����δ��)
};


// �˳�Э��
struct inet_quit_req
{	BYTE	m_cUnused;						// (����δ��)
};
struct inet_quit_ans
{	BYTE	m_cUnused;						// (����δ��)
};



// INET_9907��DEPRECATION_INET_3004
// �ѷ���,ԭIXЭ�����,����TQL��TJS����)



// ת��Э��
struct inet_redirect_ropt
{	WORD		m_wReqNo;					// �����
	BYTE		m_cTarget;					// ת��Ŀ��
};
struct inet_redirect_ropt1 : public inet_redirect_ropt
{	BYTE		m_bUseBridge;				// �ű�־
};



// �汾��ѯ
struct inet_version_req
{	CHAR	m_szBuildName[16];				// �汾����(����iPhone,iPad)
	WORD	m_wClientType;					// �ͻ������
	DWORD	m_dwClientVer;					// �ͻ��˰汾
};
struct inet_version_ans
{	WORD	m_wOptionalLen;					// ѡ����Ϣ����
	BYTE	m_acOptional[1];				// ѡ����Ϣ����(������Ϣ)
};


// ������ȡ
struct inet_patch_req
{	CHAR	m_szBuildName[16];				// �汾����(����iPhone,iPad)
	LONG	m_nOffset;						// ��ȡƫ��
	WORD	m_wPartLen;						// ��ȡ��С
	IHASH	m_Hash;							// ����HASH
};
struct inet_patch_ans
{	IHASH	m_Hash;							// �ļ���HASH�ṹ
	WORD	m_wPartLen;						// �ֶδ�С
	BYTE	m_acPart[1];					// �ֶ�����
};


// �����ļ�
struct inet_download_req
{	CHAR	m_szName[16];					// ����
	CHAR	m_szPath[32];					// �ļ�·��(ȫСд)
	LONG	m_nOffset;						// ��ȡƫ��
	WORD	m_wPartLen;						// ��ȡ��С
	IHASH	m_Hash;							// ����HASH
};
struct inet_download_ans
{	IHASH	m_Hash;							// �ļ���HASH�ṹ
	WORD	m_wPartLen;						// �ֶδ�С
	BYTE	m_acPart[1];					// �ֶ�����
};


// ��ȡ����
struct inet_publish_req
{	CHAR	m_szPath[32];					// �ļ�·��(ȫСд)
	LONG	m_nOffset;						// ��ȡƫ��
	WORD	m_wPartLen;						// ��ȡ��С
	IHASH	m_Hash;							// ����HASH
};
struct inet_publish_ans
{	IHASH	m_Hash;							// �ļ���HASH�ṹ
	WORD	m_wPartLen;						// �ֶδ�С
	BYTE	m_acPart[1];					// �ֶ�����
};


// ��������
struct inet_findsymbol_req
{	CHAR	m_szCode[7];					// ����(\0����)
	LONG	m_nOffset;						// ƫ��
	BYTE	m_cWantCount;					// �������
	BYTE	m_bRestrict:1;					// ��ȷƥ��
	BYTE	m_bFindByClass:1;				// �������
	BYTE	m_bFindSHSZ:1;					// ������г�
	BYTE	m_bFindHK:1;					// ���Ҹ۹��г�
	BYTE	m_bFindQH:1;					// �����ڻ��г�
	BYTE	m_cReserved:3;					// �����ֽ�
};
struct inet_findsymbol_ans
{	BYTE	m_cGotCount;					// ʵ�ʶ�ȡ���ĸ���
	BYTE	m_cReserved;					// �����ֽ�
	WORD	m_cbSymbolInfos;				// ����������
	BYTE	m_acSymbolInfos[1];				// ����������
};


// �Ự��
struct inet_bridge_req
{	BYTE	m_cTarget;						// ������ĳĿ�����
};
struct inet_bridge_ans
{	BYTE	m_cStatus;						// ״̬
};




//////////////////////////////////////////////////////////////////////////
// Ӧ�ü��쳣�����
// (������������Э�鲿��)
// (�μ�:ASE_Err.h)

#if defined(_COMPILE_BY_MSC_)
	#pragma warning(pop)
#endif
#pragma pack()
#endif
