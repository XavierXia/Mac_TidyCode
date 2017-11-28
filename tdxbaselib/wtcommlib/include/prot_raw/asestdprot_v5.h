//////////////////////////////////////////////////////////////////////////
// ��׼�ͻ���Э��淶�����ļ�
//		1.�ͻ��˱�׼Э�� (Э��ŷ�Χ: 3000-4200)
//		2.�����Ϳͻ���ͨѶ��IXЭ��
// ��ǰ�ļ�����:
//		Part.I		Э�鶨��
//		Part.II		�ڲ��ṹ
//		Part.III	Э�鶨��
//		Part.IV		����ź�(PROTERR)
#ifndef __ASE_STDPROT_CLI__H__
#define __ASE_STDPROT_CLI__H__
#pragma pack(1)



//========================================================================================================================
// Part.I Э��Ŷ���


// �ͻ��˻���Э��
//		�ͻ��˻���Э����ҪΪ�ͻ����ṩ�����Թ���,�ͻ���ͨ����Щ�����Թ���
//		�ͷ�������ɵ�¼׼������¼�ȹ���
// �й��û���֤����
// ��������η�������:
//		1.������֤������ݽ��е�¼
//		2.���յ�¼�õ��Ľ��������һ������
//		3.�����̨����,��ô�������ᴦ��
//		4.�����̨ʧ��,��ô�������ᴦ��
//		5.�����̨����,��ô����ʧ��
//		6.�����̨����,�����ӽ����ȡ��Ӫҵ���Լ�
//        �����ʽ��ʺ�,��������ȫ���Ľ���������֤
//		7.Ȼ��ͻ��˽����������ͨ���һϵ�е���Ϣ
//		8.������Ϣֱ�ӵ���
//		9.�����̨�����߼�������,��ô����һ�����д���
STD_PROT SHORT TC50_GET_LOADER					= 3000;			// ��ȡ����������״��
STD_PROT SHORT TC50_ALIVE						= 3001;			// �ͻ��˴���
STD_PROT SHORT TC50_GET_SERVER_INFO				= 3002;			// ��ȡ�������˻�������
STD_PROT SHORT TC50_CHECK_UPDATE				= 3003;			// ��ȡ���°汾��Ϣ
STD_PROT SHORT TC50_GET_INET_IP					= 3004;			// ��ȡ�ͻ��˹�����ַ
STD_PROT SHORT TC50_PREPARE_LOGIN				= 3005;			// ׼����¼Э��
STD_PROT SHORT TC50_LOGIN						= 3006;			// ��¼Э��
STD_PROT SHORT TC50_GET_LOGIN_INFO				= 3007;			// ��ȡ��������¼��Ϣ
STD_PROT SHORT TC50_GET_CALLBOARD				= 3008;			// ��ȡ������ϵͳͨ��
STD_PROT SHORT TC50_GET_URGENT					= 3009;			// ��ȡ������Ӫҵ������
STD_PROT SHORT TC50_GET_BRANCH_LOADER			= 3010;			// ��ȡӪҵ������״��(����Э��汾>=5.12.0149|5.10sp7)
STD_PROT SHORT TC50_HTTP_AGENT					= 3011;			// HTTP����(����Э��汾>=5.12.0169)
STD_PROT SHORT TC50_RAW_CALL					= 3012;			// �򵥵���
STD_PROT SHORT TC50_SIMP_CALL					= 3013;			// ԭʼ����
STD_PROT SHORT TC50_GET_DICT					= 3014;			// ��ȡ�ֵ�

// ���ܵ���
//		���ܵ��õ���Ҫ�����Ƕ�TC50����ҵ��ϸ��
//		Ŀǰ��Ҫ�Ĺ��ܵ��ñ�Ӧ���ڽ���ҵ��/��ȫ�ʺŹ���/��������/��Ϣ����
//			����ҵ���ܵ���--������ص�ȫ������
//			��ȫ���Ĺ��ܵ���--��ȫ�ʺ��Լ��ʺŹ�����ص�ȫ������
//			�������Ĺ��ܵ���--��Ѷ�������ֵ����
//			��Ϣ���Ĺ��ܵ���--P2P�Լ�����ҵ��ȹ���
STD_PROT SHORT TC50_FUNC_CALL					= 4000;			// ����ҵ���ܵ���
















//////////////////////////////////////////////////////////////////////////
// Part.II �ڲ��ṹ����

// IP_TACKER����ģʽ
#define IPTRACKMODE_LAN			(0)					// IPTRACKERģʽ:��ȡ���ص�ַ
#define IPTRACKMODE_THESERVER	(1)					// IPTRACKERģʽ:�ӷ�������ȡ
#define IPTRACKMODE_3RDSERVER	(2)					// IPTRACKERģʽ:��������������ȡ















//////////////////////////////////////////////////////////////////////////
// Part.III Э�鶨��

// ȫ��Э���ֵ��ֶνṹ
#define REQ_ITEM_QSID				0				// �ͻ���ȯ�̱�ʶ(����Э��汾>=5.12.0171)
#define REQ_ITEM_PID				1				// �ͻ��˲�Ʒ��ʶ(����Э��汾>=5.12.0171)
#define REQ_ITEM_LOGIN_DICT_LEN		2				// ��¼�ֵ䳤��(LOGIN_DICT,����Э��汾>=5.12.0171)
#define REQ_ITEM_SIGNATURE			3				// ֤��ǩ��(����Э��汾>=5.12.0178)
#define REQ_ITEM_SVRCODEPAGE		4				// ����������ҳ(����Э��汾>=5.12.0188)
#define REQ_ITEM_DICCODEPAGE		5				// ҵ�����ҳ(����Э��汾>=5.12.0188)

#define ANS_ITEM_URL				0				// ������ַ,���256�ֽ�
#define ANS_ITEM_COMMENT			1				// ������ע��Ϣ,���2048�ֽ�
#define ANS_ITEM_ABSTRACT			2				// ����ժҪ��Ϣ,���2048�ֽ�,(��ģ���MD5����)
#define ANS_ITEM_IPTRACKER			3				// ��������ַ������Ϣ,������256�ֽ�,(���ڹ�����ַ���������ʱ����)
#define ANS_ITEM_PLUGINFOS			4				// �������˲��MD5��(��ƥ��ʱ�򷵻�)
#define ANS_ITEM_ENTRYPOINTIDXS		5				// Ӫҵ���б�(��ƥ��ʱ�򷵻�)
#define ANS_ITEM_PUBLICKEY			6				// ��������Կ(��ƥ��ʱ�򷵻�)
#define ANS_ITEM_SCINFOS			7				// �г�������Ϣ(��ƥ��ʱ�򷵻�)
#define ANS_ITEM_CALLBOARDTITLE		8				// ϵͳ����(����)
#define ANS_ITEM_CALLBOARDSOURCE	9				// ϵͳ����(��Դ)
#define ANS_ITEM_CALLBOARDTEXT		10				// ϵͳ����(����)
#define ANS_ITEM_URGENTTITLE		11				// Ӫҵ������(����)
#define ANS_ITEM_URGENTSOURCE		12				// Ӫҵ������(��Դ)
#define ANS_ITEM_URGENTTEXT			13				// Ӫҵ������(����)
#define ANS_ITEM_LOGIN_CCF			14				// ��¼������Ϣ(LOGIN.CCF)
#define ANS_ITEM_LOGIN_DICT			15				// ��¼�ֵ�(LOGIN_DICT)
#define ANS_ITEM_TRADE_CCF			16				// ��������
#define ANS_ITEM_TCNTR_DICT			17				// �������������ֵ�
#define ANS_ITEM_SCNTR_DICT			18				// ��ȫ���������ֵ�
#define ANS_ITEM_ICNTR_DICT			19				// ��Ϣ���������ֵ�
#define ANS_ITEM_CCNTR_DICT			20				// �������������ֵ�
#define ANS_ITEM_BRANCHNAME			21				// Ӫҵ������
#define ANS_ITEM_ALARMTEXT			22				// ϵͳ����״̬��ʾ�ı�(����Э��汾>=5.12.0141)
#define ANS_ITEM_DSNSEED			23				// DSN��֤���Ӵ�(����Э��汾>=5.12.0149)
#define ANS_ITEM_SERVDESC			24				// ����������(����Э��汾>=5.12.0156)
#define ANS_ITEM_SERVVERS			25				// �������汾(����Э��汾>=5.12.0171)
#define ANS_ITEM_UCNTR_DICT			26				// �û��������������ֵ�(����Э��汾>=5.12.0171)
#define ANS_ITEM_ECNTR_DICT			27				// �ͻ�����ƽ̨�����ֵ�(����Э��汾>=5.12.0171)
#define ANS_ITEM_CUSTOMPATCH		28				// �ͻ����û�������������(����Э��汾>=5.12.0174)
#define ANS_ITEM_SIGNATURE			29				// ֤��ǩ��(����Э��汾>=5.12.0178)
#define ANS_ITEM_SERVTIME			30				// ������ʱ��(����Э��汾>=5.12.0179)
#define ANS_ITEM_SERVID				31				// ������ID(����Э��汾>=5.12.0179)
#define ANS_ITEM_CONNID				32				// ����ID(����Э��汾>=5.12.0179)
#define ANS_ITEM_SVRCODEPAGE		33				// ����������ҳ(����Э��汾>=5.12.0188)
#define ANS_ITEM_DICCODEPAGE		34				// ҵ�����ҳ(����Э��汾>=5.12.0188)

#define ANS_ITEM_TCNTR_DICT_V3		35				// �������������ֵ�(����Э��汾>=5.12.0200)
#define ANS_ITEM_SCNTR_DICT_V3		36				// ��ȫ���������ֵ�(����Э��汾>=5.12.0200)
#define ANS_ITEM_ICNTR_DICT_V3		37				// ��Ϣ���������ֵ�(����Э��汾>=5.12.0200)
#define ANS_ITEM_CCNTR_DICT_V3		38				// �������������ֵ�(����Э��汾>=5.12.0200)

#define ANS_ITEM_DICT_ALONE			39				// ������ȡ�����ֵ�(����Э��汾>=5.12.0201)



//////////////////////////////////////////////////////////////////////////
// ȡ�÷�����������Ϣ(TC50_GET_LOADER)
// ͨѶ�̴߳���(�ϸ��ֹ���ܺ�ѹ��)
struct tc50_get_loader_req
{	WORD		m_wReserved;						// (����,����Ϊ��)��ڵ�ID
};													// 5.10sp7ǰ�İ汾δ���ͻ�����λᵼ�±���,�ɴ��Ϳ�
struct tc50_get_loader_ans
{	DWORD		m_dwNowConnectNum;					// ��ǰ��������(������ͼ������)
	DWORD		m_dwMaxConnectNum;					// ���������������(������ͼ������)
	DWORD		m_bBackEndException:1;				// �Ƿ��̨�쳣(����Э��汾>=5.12.0173)
	DWORD		m_dwReserved:31;					// (����,��5.10�Ȱ汾,�������ؿ�)
};

//////////////////////////////////////////////////////////////////////////
// �ͻ��˴���(TC50_ALIVE)
// ͨѶ�̴߳���(�ϸ��ֹ���ܺ�ѹ��)
struct tc50_alive_req
{	DWORD		m_dwBranchID;						// �ͻ���Ӫҵ��ID(��Ϊ��,������Ӫҵ��������Ϣ)
	DWORD		m_tCallboard;						// �ͻ��˻�������ϵͳ����ķ���ʱ��
	DWORD		m_tUrgent;							// �ͻ��˻�������Ӫҵ������ķ���ʱ��
};
struct tc50_alive_ans
{	DWORD		m_bCallboardFlag:1;					// ������ˢ�±�־
	DWORD		m_bUrgentFlag:1;					// Ӫҵ������ˢ�±�־
	DWORD		m_bReserved:30;						// ����λ,ȫ��
};

//////////////////////////////////////////////////////////////////////////
// ��ȡ��������Ϣ(TC50_GET_SERVER_INFO)
// ͨѶ�̴߳���(�ϸ��ֹ���ܺ�ѹ��)
struct tc50_get_server_info_req
{	DWORD		m_bWantEntryPointList:1;			// �Ƿ���Ҫ��ȡ��ڵ��б�
	DWORD		m_bWantCallboard:1;					// �Ƿ���Ҫ��ȡϵͳ����
	DWORD		m_bScInfo2Supported:1;				// �ͻ����Ƿ�֧��SCINFO2.INI(����Э��汾>=5.12.0149)
	DWORD		m_bWantLoginCcf:1;					// �Ƿ���Ҫ��ȡ��¼����(LOGIN.CCF,����Э��汾>=5.12.0149)
	DWORD		m_bDSNSupported:1;					// �ͻ����Ƿ�֧��DSN��֤(����Э��汾>=5.12.0149)
	DWORD		m_dwClientType:16;					// �ͻ������(��¼���,����Э��汾>=5.12.0149��5.10sp7)
	DWORD		m_bBroadcastSupported:1;			// �ͻ����Ƿ�֧�ֹ㲥(����Э��汾>=5.12.0149��5.10sp7)
	DWORD		m_bBrokerClient:1;					// �ͻ����Ƿ�Ϊ������ͻ���,�����ͻ��˶�ҵ��Ƶ�Ȳ����(����Э��汾>=5.12.0156)
	DWORD		m_bDownPatch:1;						// �ͻ����Ƿ���Ҫ���ز���(����Э��汾>=5.12.0174)
	DWORD		m_bV6OrMoreHigh:1;					// �ͻ����Ƿ���V6���ϵİ汾
	DWORD		m_bBkgdConn:1;						// ��̨����
	DWORD		m_bPKIV2:1;							// ʹ��2��PKI��׼(֧��RSA2048��ECC,����Э��汾>5.13)
	DWORD		m_bReserved:5;						// ����λ,����ȫ��
	MD5BIN		m_md5PluginInfos;					// �����ϢMD5,MD5BIN�ṹ
	MD5BIN		m_md5EntryPointIdxs;				// ��ڵ��б�MD5,MD5BIN�ṹ
	MD5BIN		m_md5PublicKey;						// ��������ԿMD5,MD5BIN�ṹ
	MD5BIN		m_md5ScInfos;						// �г�������ϢMD5,MD5BIN�ṹ
	DWORD		m_tCallboard;						// �ͻ��˻�������ϵͳ����ķ���ʱ��
};
struct tc50_get_server_info_req1 :  public tc50_get_server_info_req
{	MD5BIN		m_md5LoginCcf;						// ��¼����MD5(����Э��汾>=5.12.0149)
	DWORD		m_dwExtSize;						// ��չ������(����Э��汾>=5.12.0149)
	BYTE		m_szExtData[1];						// ��չ������(����Э��汾>=5.12.0149)
};
// + ANS_ITEM_IPTRACKER								// ��������ַ������Ϣ,������256�ֽ�,(���ڹ�����ַ���������ʱ����)
// + ANS_ITEM_PLUGINFOS								// �������˲��MD5��(��ƥ��ʱ�򷵻�)
// + ANS_ITEM_ENTRYPOINTIDXS						// Ӫҵ���б�(��ƥ��ʱ�򷵻�)
// + ANS_ITEM_PUBLICKEY								// ��������Կ(��ƥ��ʱ�򷵻�)
// + ANS_ITEM_SCINFOS								// �г�������Ϣ(��ƥ��ʱ�򷵻�)
// + ANS_ITEM_CALLBOARDTITLE						// ϵͳ����(����)
// + ANS_ITEM_CALLBOARDSOURCE						// ϵͳ����(��Դ)
// + ANS_ITEM_CALLBOARDTEXT							// ϵͳ����(����)
// + ANS_ITEM_ALARMTEXT								// ϵͳ����״̬��ʾ�ı�(�ı�,����Э��汾>=5.12.0141)
// + ANS_ITEM_LOGIN_CCF								// ��¼������Ϣ(LOGIN.CCF,����Э��汾>=5.12.0149)
// + ANS_ITEM_DSNSEED								// DSN��֤��������(����Э��汾>=5.12.0149)
// + ANS_ITEM_SERVDESC								// ����������(����Э��汾>=5.12.0156)
// + ANS_ITEM_SERVVERS								// �������汾(����Э��汾>=5.12.0171)
struct tc50_get_server_info_ans
{	IPV4		m_InetIp;							// �ͻ��˹���IP
	WORD		m_wDefEntryPointID;					// Ĭ����ڵ�ID
	CHAR		m_szQsid[QSID_SIZE];				// ȯ�̱�ʶ
	BYTE		m_nIpTrackerMode;					// IPTRACKER������ʽ
	BYTE		m_nUpgradeMode;						// �Զ�����ģʽ
	BYTE		m_bHasSSL;							// ��ȫ��ʽ[�Ƿ�֧��SSL]
	BYTE		m_bHasAuthpass;						// ��ȫ��ʽ[�Ƿ�֧����֤����]
	BYTE		m_bHasDigitCert;					// ��ȫ��ʽ[�Ƿ�֧����֤��]
	BYTE		m_bHasOTP;							// ��ȫ��ʽ[�Ƿ�֧�����ƿ�]
	BYTE		m_bHasUkey;							// ��ȫ��ʽ[�Ƿ�֧��UKEY]
	BYTE		m_bHasSMSAuth:1;					// ��ȫ��ʽ[�Ƿ�֧�ֶ��ſ���]
	BYTE		m_bHasRCAuth:1;						// ��ȫ��ʽ[�Ƿ�֧�־���]
	BYTE		m_bHasMOTPAuth:1;					// ��ȫ��ʽ[�Ƿ�֧���ֻ�����]
	BYTE		m_bHasElseAuthority:3;				// ��ȫ��ʽ[����]
	BYTE		m_nPKIType:2;						// PKI����
	BYTE		m_cPKIBitIdx;						// PKI��Կλ������
	BYTE		m_cSessionAlgoType;					// SESSION�㷨����
	BYTE		m_cSessionKeyLenIdx;				// SESSION��Կ��������
	BYTE		m_cInternalSignal:1;				// �Ƿ�֧�ְ�������ǩ��
	BYTE		m_cExternalSignal:1;				// �Ƿ�֧�ַ������ǩ��
	BYTE		m_bScntrSupported:1;				// ������֧�ְ�ȫ����(����Э��汾>5.12.0140,��Ӧtc50_prepare_login_req1)
	BYTE		m_bAlarmStatus:1;					// ϵͳ����״̬(����Э��汾>=5.12.0141)
	BYTE		m_bScntrErrCtlOn:1;					// �������Ƿ�ָ����ȫ�����ݴ����(����Э��汾>=5.12.0143)
	BYTE		m_bScInfo2Supported:1;				// �������Ƿ�֧��SCINFO2.INI(LOGIN.CCF,����Э��汾>=5.12.0149)
	BYTE		m_bDSNSupported:1;					// �������Ƿ�֧��DSN��֤(����Э��汾>=5.12.0149)
	BYTE		m_bClientTypePermit:1;				// �ͻ��������Ƿ�׼�����(����Э��汾>=5.12.0149��5.10sp7)
	BYTE		m_cHashAlgoType;					// HASH�㷨����
	WORD		m_bReserved2:1;						// (����)�Կͻ��˵Ĺ�Կ���м��ܴ���(����Э��汾<5.12.0149��5.10sp7)
	WORD		m_bHasScntr:1;						// �Ƿ�֧�ְ�ȫ����
	WORD		m_bHasIcntr:1;						// �Ƿ�֧����Ϣ����
	WORD		m_bHasCcntr:1;						// �Ƿ�֧�ֺ�������
	WORD		m_bLimitedMode:1;					// �ͻ����Ƿ�ʹ�����޷��(����Э��汾>=5.12.0149��5.10sp7)
	WORD		m_bBroadcastSupported:1;			// �ͻ����Ƿ�֧�ֹ㲥(����Э��汾>=5.12.0149��5.10sp7)
	WORD		m_bIsV2_PrepareLogin:1;				// �Ƿ�֧�ַ�����Ԥ��¼��չЭ��V2(����Э��汾>=5.12.0149,��Ӧtc50_prepare_login_req2)
	WORD		m_bVipHost:1;						// �Ƿ�ΪVIP��վ(����Э��汾>=5.12.0172)
	WORD		m_bJCKHJY:1;						// �Ƿ�֧�ּ��ɿͻ�У��
	WORD		m_bBackEndException:1;				// ��������Ƿ�����(���ٴ���һ����˴��ڹ���)
	WORD		m_bIsV1_GetLoginInfo:1;				// �Ƿ�֧�ֻ�ȡ��¼��ϢV1(����Э��汾>=5.12.0182,��Ӧtc50_get_logininfo_req1)
	WORD		m_bIsV3_IX:1;						// �Ƿ�֧�����ֵ��ʽ(����Э��汾>=5.12.0200,��Ӧtc50_get_logininfo_req1)
	WORD		m_bReserved3:4;						// ����5λ,ȫ��
	DWORD		m_dwCallboardUpDate;				// ϵͳ�����������(YYYYMMDD��ʽ,���Ϊ0��ʾ�޹���)
	DWORD		m_tCallboard;						// ϵͳ���淢��ʱ��(���Ϊ0��ʾ�޹���)
	DWORD		m_dwExtSize;						// ��չ������
	BYTE		m_szExtData[1];						// ��չ������
};

//////////////////////////////////////////////////////////////////////////
// ����Զ�����(TC50_CHECK_UPDATE)
// ͨѶ�̴߳���(�ϸ��ֹ���ܺ�ѹ��)
struct tc50_check_update_req
{	WORD		m_wClientType;						// �ͻ�������
	WORD		m_wClientVer;						// �ͻ��˰汾
	WORD		m_wReleaseVer;						// ���а汾
	DWORD		m_bWantURL:1;						// �Ƿ���Ҫ������ַ
	DWORD		m_bWantComment:1;					// �Ƿ���Ҫ������ע��Ϣ
	DWORD		m_bWantAbstract:1;					// �Ƿ���Ҫ����ժҪ�ļ�
	DWORD		m_bReserved:29;						// ����λ,����ȫ��
};
// + ANS_ITEM_URL									// ������ַ,���256�ֽ�
// + ANS_ITEM_COMMENT								// ������ע��Ϣ,���2048�ֽ�
// + ANS_ITEM_ABSTRACT								// ����ժҪ��Ϣ,���2048�ֽ�,(��ģ���MD5����)
struct tc50_check_update_ans
{	DWORD		m_bIsLastestVer:1;					// �Ƿ������°汾
	DWORD		m_bDiscardVer:1;					// �Ƿ�汾�Ѿ�������(ǿ������)
	DWORD		m_bReserved:30;						// ����λ,ȫ��
	WORD		m_wClientVer;						// �ͻ��˰汾
	WORD		m_wReleaseVer;						// ���а汾
	DWORD		m_dwExtSize;						// ��չ������
	BYTE		m_szExtData[1];						// ��չ������
};

//////////////////////////////////////////////////////////////////////////
// ������ַ����Э��(TC50_GET_INET_IP,���ڹ�����ַ���������ʱ����)
// ͨѶ�̴߳���(�ϸ��ֹ���ܺ�ѹ��)
struct tc50_get_inet_ip_req
{
};
struct tc50_get_inet_ip_ans
{	IPV4		m_InetIp;							// �ͻ��˹���IP
};


//////////////////////////////////////////////////////////////////////////
// ��¼׼������(TC50_PREPARE_LOGIN)
// �����̴߳����Զ�̴���
// �Ǽǿͻ��˲���IP/MAC,�ͻ��˰汾��Ϣ,������Կ��,��ȡ��½��ز���
struct tc50_prepare_login_hdr
{	WORD		m_wEntryPointID;					// ��ڵ�ID
};
struct tc50_prepare_login_req
{	IPV4		m_InetIp;							// �ͻ���IP��ַ(��¼��Ϣ)
	MAC			m_Mac;								// �ͻ���MAC��ַ(��¼��Ϣ)
	WORD		m_wClientType;						// �ͻ�������
	WORD		m_wClientVer;						// �ͻ��˰汾
	WORD		m_wReleaseVer;						// ���а汾
	DWORD		m_bPeerPubKey:1;					// �ͻ��˹�Կ��־
	DWORD		m_bWantLoginCcf:1;					// �Ƿ���Ҫ��ȡ��¼����(LOGIN.CCF,����Э��汾>=5.12.0149)
	DWORD		m_bSuperVersion:1;					// �Ƿ��ǳ����汾(�ǳ����汾����֤�汾��Ϣ)(����Э��汾>=5.12.0191)
	DWORD		m_bReserved:29;						// ����λ,����ȫ��
	USHORT		m_nPeerPubKeyLen;					// �ͻ��˹�Կ���ܺ󳤶�
	BYTE		m_szPeerPubKey[516];				// �ͻ��˹�Կ��Ϣ(ʹ�÷������˼���)(BUGBUG:�����°汾,����ط�����,����ֿ�����)
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
	MD5BIN		m_md5LoginCcfDiscard;				// ��¼����MD5(����,����Э��汾<5.12.0149)
	MD5BIN		m_md5LoginDict;						// ��¼�ֵ��MD5
};
struct tc50_prepare_login_req1 : public tc50_prepare_login_req
{	MD5BIN		m_md5ScntrDict;						// ��ȫ�����ֵ��MD5(����Э��汾>=5.12.0140)
};
struct tc50_prepare_login_req2 : public tc50_prepare_login_req1
{	DWORD		m_dwExtSize;						// ��չ������(����Э��汾>=5.12.0149)
	BYTE		m_szExtData[1];						// ��չ������(����Э��汾>=5.12.0149)
};
// - ANS_ITEM_LOGIN_CCF								// ��¼������Ϣ(LOGIN.CCF,����Э��汾<5.12.0149)
// + ANS_ITEM_LOGIN_DICT							// ��¼�ֵ�(LOGIN_DICT)
// + ANS_ITEM_SCNTR_DICT							// ��ȫ�����ֵ�(SCNTR_DICT,����Э��汾>=5.12.0140)
struct tc50_prepare_login_ans
{	USHORT		m_nSessionKeyLen;					// SESSION_KEY���ܺ󳤶�
	BYTE		m_szSessionKey[516];				// SESSION_KEY(ʹ�ÿͻ��˹�Կ����)
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
	DWORD		m_dwExtSize;						// ��չ���ݴ�С
	BYTE		m_szExtData[1];						// ��չ���ݻ�����
};


//////////////////////////////////////////////////////////////////////////
// ��¼���(TC50_LOGIN)
// �����̻߳��ⲿ����
struct tc50_login_hdr
{	DWORD		m_tStartupTime;						// �ϴ�����ʱ,����������ʱ��
	WORD		m_wEntryPointID;					// ��¼ʱ����ڵ�ID
	FUNCHDR		m_hdr;								// ���ܵ���ͷ��Ϣ(�����ͻ��˵�ַ��Ϣ�Լ�Ӫҵ����Ϣ)
};
struct tc50_login_req
{	FUNCBDY		m_bdy;								// ����������(�����ͻ�����֤��Ϣ)
};
struct tc50_login_ans
{	DWORD		m_bNeedGetLoginInfo:1;				// �ͻ�������������־(��������ĳ��ԭ������)
	DWORD		m_bReserved:31;						// ����λ,ȫ��
	DWORD		m_tStartupTime;						// �ϴ�����ʱ,����������ʱ��
	LONG		m_nRetCode;							// DLL���ؽ��
	FUNCBDY		m_bdy;								// Ӧ��������(����Ӫҵ��ID,��֤״̬,�����ɵ�SESSION_KEY)
};


// ��¼Ԥ����(TC50_SIMP_CALL)
// �����̻߳��ⲿ����
struct tc50_simp_call_hdr
{	WORD		m_wEntryPointID;					// ��¼ʱ����ڵ�ID
	FUNCHDR		m_hdr;								// ���ܵ���ͷ��Ϣ(�����ͻ��˵�ַ��Ϣ�Լ�Ӫҵ����Ϣ)
};
struct tc50_simp_call_req
{	FUNCBDY		m_bdy;								// ����������(�����ͻ�����֤��Ϣ)
};
struct tc50_simp_call_ans
{	DWORD		m_bReserved;						// ����λ,ȫ��
	LONG		m_nRetCode;							// DLL���ؽ��
	FUNCBDY		m_bdy;								// Ӧ��������(����Ӫҵ��ID,��֤״̬,�����ɵ�SESSION_KEY)
};

//////////////////////////////////////////////////////////////////////////
// ��ȡ�û�����(TC50_GET_LOGIN_INFO)
// �����̻߳��ⲿ����
struct tc50_get_logininfo_hdr
{	DWORD		m_dwBranchID;						// Ӫҵ��ID
};
struct tc50_get_logininfo_req
{	DWORD		m_bWantUrgent:1;					// �Ƿ���Ҫ��ȡӪҵ������
	DWORD		m_bWantScntrDict:1;					// �Ƿ���Ҫ��ȫ�ֵ�(����Э��汾>=5.12.0149)
	DWORD		m_bGetDictAlone:1;					// �Ƿ����֧�ִ��ֵ��ȡ(����Э��汾>=5.12.201)
	DWORD		m_bReserved:29;						// ����λ,����ȫ��
	DWORD		m_tUrgent;							// �ͻ��˻�������Ӫҵ������ķ���ʱ��
	MD5BIN		m_md5TradeCcf;						// TRADE_CCF�ļ���MD5��Ϣ
	MD5BIN		m_amd5Dicts[6];						// ��ǰ�����ֵ��MD5��Ϣ(5.12.0171��������)
};
struct tc50_get_logininfo_req1 : public tc50_get_logininfo_req
{	WORD		m_acbDicts[6];						// ��ǰ�����ֵ�ĳ�����Ϣ(5.12.0171��������)
};
// + ANS_ITEM_URGENTTITLE							// Ӫҵ���������
// + ANS_ITEM_URGENTSOURCE							// Ӫҵ��������Դ
// + ANS_ITEM_URGENTTEXT							// Ӫҵ����������
// + ANS_ITEM_TRADE_CCF								// ��������
// + ANS_ITEM_TCNTR_DICT							// �������������ֵ�
// + ANS_ITEM_SCNTR_DICT							// ��ȫ���������ֵ�(����Э��汾>=5.12.0149)
// + ANS_ITEM_ICNTR_DICT							// ��Ϣ���������ֵ�(����Э��汾>=5.12.0149)
// + ANS_ITEM_CCNTR_DICT							// �������������ֵ�(����Э��汾>=5.12.0149)
// + ANS_ITEM_BRANCHNAME							// Ӫҵ������
// + ANS_ITEM_UCNTR_DICT							// �û��������������ֵ�(����Э��汾>=5.12.0171)
// + ANS_ITEM_ECNTR_DICT							// �ͻ�����ƽ̨�����ֵ�(����Э��汾>=5.12.0171)
struct tc50_get_logininfo_ans
{	DWORD		m_dwUrgentUpDate;					// Ӫҵ�������������(YYYYMMDD��ʽ,���Ϊ0��ʾ�޹���)
	DWORD		m_tUrgent;							// Ӫҵ��ͨ�����ʱ��(���Ϊ0��ʾ�޹���)
	DWORD		m_dwExtSize;						// ��չ���ݴ�С
	BYTE		m_szExtData[1];						// ��չ���ݻ�����
};


//////////////////////////////////////////////////////////////////////////
// ��ȡ������ϵͳͨ��(TC50_GET_DICT,����Э��汾>=5.12.0201)
// ͨѶ�̴߳���
struct tc50_get_dict_req
{	DWORD		m_dwBranchID;						// Ӫҵ��ID
	BYTE		m_cFuncType;						// ��������
	MD5BIN		m_md5Dict;							// ��ǰ�����ֵ��MD5��Ϣ
	DWORD		m_cbDict;							// ��ǰ�����ֵ�Ĵ�С
	DWORD		m_cbOffset;							// �ֵ�ƫ��λ��
};
struct tc50_get_dict_ans
{	MD5BIN		m_md5Dict;							// ��ǰ�����ֵ��MD5��Ϣ
	DWORD		m_cbDict;							// ȫ������
	DWORD		m_cbOffset;							// �ֵ�ƫ��λ��
	DWORD		m_cbPart;							// ���س���
	BYTE		m_acDict[1];						// �ֵ�����
};


//////////////////////////////////////////////////////////////////////////
// ��ȡ������ϵͳͨ��(TC50_GET_CALLBOARD)
// ͨѶ�̴߳���
struct tc50_get_callboard_req
{
};
// + ANS_ITEM_CALLBOARDTITLE						// ϵͳ����(����)
// + ANS_ITEM_CALLBOARDSOURCE						// ϵͳ����(��Դ)
// + ANS_ITEM_CALLBOARDTEXT							// ϵͳ����(����)
struct tc50_get_callboard_ans
{	DWORD		m_dwCallboardUpDate;				// ϵͳ�����������(YYYYMMDD��ʽ,���Ϊ0��ʾ�޹���)
	DWORD		m_tCallboard;						// ϵͳ���淢��ʱ��(���Ϊ0��ʾ�޹���)
	DWORD		m_dwExtSize;						// ��չ���ݴ�С
	BYTE		m_szExtData[1];						// ��չ���ݻ�����(������/��Դ/����)
};


//////////////////////////////////////////////////////////////////////////
// ��ȡӪҵ������(TC50_GET_URGENT)
// ͨѶ�̴߳���
struct tc50_get_urgent_req
{	DWORD		m_dwBranchID;						// Ӫҵ��ID
};
// + ANS_ITEM_URGENTTITLE							// Ӫҵ���������
// + ANS_ITEM_URGENTSOURCE							// Ӫҵ��������Դ
// + ANS_ITEM_URGENTTEXT							// Ӫҵ����������
struct tc50_get_urgent_ans
{	DWORD		m_dwUrgentUpDate;					// Ӫҵ�������������(YYYYMMDD��ʽ,���Ϊ0��ʾ�޹���)
	DWORD		m_tUrgent;							// Ӫҵ�����淢��ʱ��(���Ϊ0��ʾ�޹���)
	DWORD		m_dwExtSize;						// ��չ���ݴ�С
	BYTE		m_szExtData[1];						// ��չ���ݻ�����(������/��Դ/����)
};


//////////////////////////////////////////////////////////////////////////
// ȡ��Ӫҵ��������Ϣ(TC50_GET_BRANCH_LOADER,����Э��汾>=5.12.0149��5.10sp7)
// ͨѶ�̴߳���(�ϸ��ֹ���ܺ�ѹ��)
struct tc50_get_branch_loader_req
{	WORD		m_wEntryPointID;					// ��ڵ�ID
};
struct tc50_get_branch_loader_ans
{	DWORD		m_dwNowConnectNum;					// ��ǰ��������(������ͼ������)
	DWORD		m_dwMaxConnectNum;					// ���������������(������ͼ������)
	DWORD		m_dwGuessLoader;					// ����(����������ڵ�ID�ǿ��򷵻ض�ӦӪҵ���ĸ���)
};


//////////////////////////////////////////////////////////////////////////
// ����ҵ���ܵ���(TC50_FUNC_CALL)
// �����̻߳��ⲿ����
struct tc50_func_call_hdr
{	BYTE		m_cFlag;							// ��־�ֶ�
	FUNCHDR		m_hdr;								// ���ܵ���ͷ��Ϣ
};
struct tc50_func_call_req
{	FUNCBDY		m_bdy;								// ����������
};
struct tc50_func_call_ans
{	LONG		m_nRetCode;							// DLL��������
	FUNCBDY		m_bdy;								// ����������
};



//////////////////////////////////////////////////////////////////////////
// ԭʼ���ܵ���(TC50_RAW_CALL)
// �����̻߳��ⲿ����
struct tc50_raw_call_req
{	DWORD		m_dwSize;							// ���󳤶�
	BYTE		m_szBuffer[1];						// ���󻺳���
};
struct tc50_raw_call_ans
{	LONG		m_nRetCode;							// DLL��������
	DWORD		m_dwSize;							// Ӧ�𳤶�
	BYTE		m_szBuffer[1];						// Ӧ�𻺳���
};












//////////////////////////////////////////////////////////////////////////
// Part.IV ����ź궨��
// (�������ĺ�IMSERVER����������)
// (�μ�:ASE_Err.h)





//////////////////////////////////////////////////////////////////////////
// Part.V ���ݾɰ汾�Ķ���,��������
#define NULL_TDXBRANCHID			NULL_ENTRYPOINTID		// ����ڵ�ID(ԭ����Ӫҵ��)
#define NULL_REALBRANCHID			NULL_BRANCHID			// ��Ӫҵ��ID(ԭӪҵ��)
#define ANS_ITEM_TDXBRANCHIDXS		ANS_ITEM_ENTRYPOINTIDXS
typedef ENTRYPOINTIDX TDXBRANCHIDX,*LPTDXBRANCHIDX;





#pragma pack()
#endif
