//////////////////////////////////////////////////////////////////////////
// ���Է���Э��淶�����ļ�
// 1.���Է���Э���������  (Э��ŷ�Χ: 9800-9900)
#ifndef __ASE_STDPROT_TEST__H__
#define __ASE_STDPROT_TEST__H__
#pragma pack(1)
#if defined(_COMPILE_BY_MSC_)
	#pragma warning(push)
	#pragma warning(disable:4200)
#endif


//////////////////////////////////////////////////////////////////////////
// ���ܺŶ���
STD_PROT WORD TEST_LOGIN			= 9802;		// LOGINЭ��(ROSEЭ��)
STD_PROT WORD TEST_ECHO				= 9805;		// ECHOЭ��(ROSEЭ��)
STD_PROT WORD TEST_ENDORSEMENT		= 9806;		// ENDORSEMENTЭ��(ROSEЭ��)
STD_PROT WORD TEST_UPLOAD			= 9807;		// UPLOADЭ��(ROSEЭ��,���)
STD_PROT WORD TEST_DOWNLOAD			= 9808;		// DOWNLOADЭ��(ROSEЭ��,���)
STD_PROT WORD TEST_LONGTALK			= 9809;		// LONGTALKЭ��(ROSEЭ��,���)


STD_PROT WORD TEST_RECHO			= 9810;		// ����ECHOЭ��(ROSEЭ��)
STD_PROT WORD TEST_RECHOMULTI		= 9811;		// ����ECHOЭ��(ROSEЭ��,���)
STD_PROT WORD TEST_MQ_IN			= 9812;		// ��Ϣ����(��Ϣ����)
STD_PROT WORD TEST_MQ_OUT			= 9813;		// ��Ϣ���(��Ϣ����)


STD_PROT WORD TEST_HEY				= 9820;		// ���ͱ���






//////////////////////////////////////////////////////////////////////////
// Ӧ�ü��쳣�����
// (���Է���Э�鲿��)
// (�μ�:ASE_Err.h)



//////////////////////////////////////////////////////////////////////////
// Э��ṹ����

// LOGIN����
struct test_login_req
{	CHAR	m_szLoginID[64];				// �˺���Ϣ
	CHAR	m_szLoginPass[64];				// ������Ϣ
};
struct test_login_ans
{	CHAR	m_szUID[64];					// �˺���Ϣ
	BYTE	m_cReserved;
};




// ECHO����
struct test_echo_ropt
{	BYTE	m_cReserved;					// �����ֽ�
};
struct test_echo_req
{	BYTE	m_cReserved;					// �����ֽ�
	CHAR	m_szInfo[0];					// ��Ϣ����
};
struct test_echo_aopt
{	BYTE	m_cReserved;					// �����ֽ�
};
struct test_echo_ans
{	BYTE	m_cReserved;					// �����ֽ�
	CHAR	m_szUID[32];					// �û�ID
	CHAR	m_szInfo[0];					// ��Ϣ����
};

// ENDORSEMENT����
struct test_endorsement_ropt
{	BYTE	m_cReserved;					// �����ֽ�
};
struct test_endorsement_req
{	CHAR	m_szDevice[16];					// �豸��
	IPV6	m_EthernetIp;					// �ͻ�IP(˽��)
	IPV6	m_InternetIp;					// �ͻ�IP(����)
	MAC		m_Mac;							// �ͻ�MAC
	CHAR	m_szBuildName[16];				// �汾������
	WORD	m_wClientType;					// �ͻ������
	DWORD	m_dwClientVer;					// �ͻ��˰汾
	TCHAR	m_szUID[32];					// �û�ID
	CHAR	m_szInfo[0];					// ��Ϣ����
};
struct test_endorsement_aopt
{	BYTE	m_cReserved;					// �����ֽ�
};
struct test_endorsement_ans
{	CHAR	m_szInfo[0];					// ��Ϣ����
};



// UPLOAD����
struct test_upload_req
{	BYTE	m_cTestType;					// ��������(0:�������� 1:�쳣��ֹ 2:������Ƭ��)
	CHAR	m_szAsFile[64];					// Ŀ���ļ���
	LONG	m_nLength;						// �ļ���С
	LONG	m_nOffset;						// ƫ��
	CHAR	m_szInfo[0];					// ������
};
struct test_upload_ans
{	BYTE	m_cResult;						// ���״̬
};




// DOWNLOAD����
struct test_download_req
{	CHAR m_szFile[64];						// �ļ���
	LONG m_nOffset;							// �ļ�ƫ��
	LONG m_nReadSize;						// ��ȡ��С
};
struct test_download_ans
{	LONG m_nOffset;							// �ļ�ƫ��
	CHAR m_szInfo[0];						// ���ص��ļ���Ϣ
};




// LONGTALK����
struct test_longtalk_ropt
{	BYTE	m_cReserved;					// �����ֽ�
};
struct test_longtalk_req
{	BYTE	m_cReserved;					// �����ֽ�
	CHAR	m_szInfo[0];					// ��Ϣ����
};
struct test_longtalk_aopt
{	BYTE	m_cReserved;					// �����ֽ�
};
struct test_longtalk_ans
{	BYTE	m_cReserved;					// �����ֽ�
	CHAR	m_szInfo[0];					// ��Ϣ����
};




// HEY����
struct test_hey_aopt
{	BYTE	m_cReserved;					// �����ֽ�
};
struct test_hey_ans
{	BYTE	m_cReserved;					// �����ֽ�
	CHAR	m_szSentence[0];				// ��Ϣ
};

#if defined(_COMPILE_BY_MSC_)
	#pragma warning(pop)
#endif
#pragma pack()
#endif
