//////////////////////////////////////////////////////////////////////////
// �ӿڶ���
// ϵͳ�ṹ
//                     |                   |                   |                                          |
//                     |     �����        |       Э���      |                  ִ�в�                  |
//                     |                   |                   |                                          |
//   +---------+       |   +---------+     |   +-----------+   |                                          |
//   |         |---------->| PACKAGE |-------->|   BINARY  |   |           +-------------+                |
//   |         |       |   +---------+     |   |           |-------------->|     RAW     |--------+---+   |
//   |         |       |                +----->|   TUNNEL  |   |           +-------------+        |   |   |
//   |         |       |   +---------+  |  |   +-----------+   |                                  |   |   |
//   |         |---------->|  HTTP   |--+  |                   |                                  |   |   |
//   |         |       |   +---------+  |  |   +-----------+   |                                  |   |   |
//   | �ͻ���  |       |                +----->|   HTTP    |   |           +-------------+        |   |   |
//   |         |       |                   |   |           |-------------->|     HTTP    |----+---+---+   |
//   |         |       |                   |   |  HTTP(x)  |   |           +-------------+    |   |   |   |
//   |         |       |                   |   +-----------+   |                              |   |   |   |
//   |         |       |                   |                   |                              |   |   |   |
//   |         |       |   +---------+     |   +-----------+   |           +-------------+    |   |   |   |
//   |         |---------->|   FIX   |-------->|    FIX    |-------------->|     FIX     |----|---+---+   |
//   +---------+       |   +---------+     |   +-----------+   |           +-------------+    |   |   |   |
//                     |                   |                   |                              |   |   |   |
//                     |                   |                   |                              |   |   |   |
//                     |                   |                   |                              |   |   |   |
//                     |                   |                   |                              |   |   |   |
//                     | +-------------+   |                   |                              |   |   |   |
//                     | |  HTTPPARSER |<-----------------------------------------------------+   |   |   |
//                     | +-------------+   |                   |                                  |   |   |
//                     |                   |                   |                                  |   |   |
//                     | +-------------+   |                   |                                  |   |   |
//                     | | IX HANDLER  |<---------------------------------------------------------+   |   |
//                     | +-------------+   |                   |                                      |   | 
//                     |                   |                   |                                      |   |
//                     | +-------------+   |                   |                                      |   |
//                     | |   SESSION   |<-------------------------------------------------------------+   |
//                     | +-------------+   |                   |                                          |
// 
// �����ļ��ṹ
//	Manufacturer.manifest
//		maincenter.ini
//		tdx.ini
//		Services.xml
//			������.ini
//			��������
#ifndef __TS_DEFINE__H__
#define __TS_DEFINE__H__
#pragma pack(1)

#ifndef T2EE_SDKVER
	#define T2EE_SDKVER
	#define T2EESDKVER_DEPRECATION		0
	#define T2EESDKVER_1_00				1
	#define T2EESDKVER_2_00				2
	#define T2EESDKVER_2_01				3
	#define T2EESDKVER_2_02				4
	#define T2EESDKVER_2_03				4
	#define T2EESDKVER_LASTEST			T2EESDKVER_2_03
#endif


#ifdef ASELIB_LIB
	#define interface struct
	#define PURE =0
#endif


//////////////////////////////////////////////////////////////////////////
// �ⲿ��������ض���
#ifndef WITH_SAFEVCRT
	typedef enum enumINDICTYPE
	{	INDIC_LV,
		INDIC_FLOW,
		INDIC_STAT,
	} INDICTYPE;
#endif


#ifndef WITH_CLIBHLPR
	// Э������(����: iocpsvrmodel.h)
	#define PROTOCOLTYPE_UNKNOWN		(0)				// Э�����: δ֪Э��
	#define PROTOCOLTYPE_HTTP			(1)				// Э�����: HTTPЭ��
	#define PROTOCOLTYPE_HTTPX			(2)				// Э�����: HTTPxЭ��
	#define PROTOCOLTYPE_TUNNEL			(3)				// Э�����: ������Э��(��Э��汾)
	#define PROTOCOLTYPE_BINARY			(4)				// Э�����: ������Э��(��Э��汾)
	#define PROTOCOLTYPE_SIP			(5)				// Э�����: SIPЭ��
	#define PROTOCOLTYPE_FIX			(6)				// Э�����: FIXЭ��
	#define PROTOCOLTYPE_T2				(7)				// Э������: ����T2Э��
	#define PROTOCOLTYPE_KCXP			(8)				// Э������: ��֤KCXPЭ��
#endif


#ifndef WITH_CLIBHLPR
	// ��������(����: iocpsvrmodel.h)
	typedef enum enumIOCPBPR
	{
		// �����͹���ʵ�ִ���
		BPR_BASE_ERROR				=  0,	// δ֪����
		BPR_INTERNAL_ERROR			= -1,	// �ڲ�����
		BPR_NOT_SUPPORT				= -2,	// ����δ֧��
		BPR_NOT_IMPLEMENT			= -3,	// ����δʵ��
		BPR_MANUAL_CLOSE			= -4,	// �ֹ��ر�

		// ����������
		BPR_NO_MEMORY				=-10,	// �ڴ治��
		BPR_NO_BUFFER				=-11,	// ����������
		BPR_NO_BCSTACKSPACE			=-12,	// ����������ջ����
		BPR_NO_SCSTACKSPACE			=-13,	// �Ự������ջ����
		BPR_NO_BUSINESSSPACE		=-14,	// ���������
		BPR_NO_BUSINESQUOTA			=-15,	// ���������
		BPR_BUFSIZE_TOOSMALL		=-16,	// ��������С̫С
		BPR_OPTSIZE_TOOLARGE		=-17,	// ѡ���С̫��
		BPR_OPTSIZE_NOTPROPER		=-18,	// ѡ���С��ǡ��
		BPR_OPTREAD_ERROR			=-19,	// ѡ���ȡ����
		BPR_OPTWRITE_ERROR			=-20,	// ѡ��д�����
		BPR_DATSIZE_TOOLARGE		=-21,	// ���ݴ�С̫��
		BPR_DATSIZE_NOTPROPER		=-22,	// ���ݴ�С��ǡ��
		BPR_DATREAD_ERROR			=-23,	// ���ݶ�ȡ����
		BPR_DATWRITE_ERROR			=-24,	// ����д�����
		BPR_UNHANDLEDEXCEPTION		=-25,	// �ڲ�ǡ���ĵط��׳���Э���쳣

		// �����Ĵ���
		BPR_BUSINESS_MISSING		=-30,	// �����Ѿ���ʧ
		BPR_CONNECT_MISSING			=-31,	// �����Ѿ���ʧ(�ر�)
		BPR_CONNECT_CLOSED			=-32,	// �����ڽ��պ����ʱ��������,�����Ѿ����ر�
		BPR_CONNECT_FINALY			=-33,	// ���������ӹر�ʱ������δ���������δ�������
		BPR_SESSION_MISSING			=-34,	// �Ự�Ѿ���ʧ(�ر�)
		BPR_SESSION_MISTAKE			=-35,	// �Ự��Ϣ��Ч
		BPR_SESSION_CREATEFAIL		=-36,	// �����Ự��Ϣʧ��
		BPR_SESSION_VERIFYFAIL		=-37,	// У��Ự��Ϣʧ��
		BPR_SESSION_EXISTFAIL		=-38,	// �Ự�Ѿ�����,��ֹ�ظ�����
		BPR_SESSION_OPENFAIL		=-39,	// �Ự��Ϣ��ʧ��
		BPR_SESSION_NOTONLINE		=-40,	// �Ự������
		BPR_SESSION_NOTAUTHORITY	=-41,	// �Ựδ����Ȩ���ж�Ӧ����

		// �ײ�ͨѶ����
		BPR_CONSISTENCY_CHECK		=-50,	// һ���Լ�����
		BPR_PACKAGE_ERROR			=-51,	// �����
		BPR_BUSINESSSEND_FAIL		=-52,	// ������ʧ��(��ǿ�ƹر�����)
		BPR_FRAGMENTSEND_FAIL		=-53,	// �����ͷ����Ƭʧ��
		BPR_TRAFFIC_LIMIT			=-54,	// ��������
		BPR_HUGERECURSIVE_LIMIT		=-55,	// ѭ��ת�����̫��
		BPR_PRIVATEBRIDGE_BREAK		=-56,	// ˽���ŶϿ�
		BPR_APPLAYER_BREAK			=-57,	// Ӧ�ò�Ͽ�

		// ������ش���
		BPR_BADPARAMETER			=-60,	// ��������
		BPR_UNHANDLEDTIMEOUT		=-61,	// ��ʱδ����
		BPR_PROCEDURE				=-62,	// �ӹ��̴���

		// Э��ṹ���͵��ô���
		BPR_UNPACK_ERROR			=-70,	// ��Ϣ���ʧ��
		BPR_PACK_ERROR				=-71,	// ��Ϣ���ʧ��
		BPR_ASSEMBLE_ERROR			=-72,	// Ӧ���������
		BPR_SOURCEIP_DANGER			=-73,	// ����Դ��ַ��������
		BPR_CLIENTID_EMPTY			=-74,	// �ͻ�����ϢΪ��
		BPR_CLIENTID_DANGER			=-75,	// �ͻ�����Ϣ��������
		BPR_USER_NOTMATCH			=-76,	// �ͻ��Ų�ƥ��
		BPR_USER_NOTLOGINED			=-77,	// �ͻ���δ���е�¼
		BPR_USER_NORELOGIN			=-78,	// �ͻ��Ѿ���¼,��ֹ�ظ���¼
		BPR_BAD_COMPRESSTYPE		=-79,	// ѹ����ʽ����ѹ�����ͷǷ�
		BPR_BAD_ENCRYPTTYPE			=-80,	// ���ܷ�ʽ���߼������ͷǷ�
		BPR_BAD_REQLEN				=-81,	// ���󳤶ȴ���
		BPR_BAD_REQSTRU				=-82,	// ����ṹ����
		BPR_BAD_OPTIONLEN			=-83,	// ѡ�������ȴ���
		BPR_NO_PROTOCOLFAMILY		=-84,	// Э�����Ч
		BPR_NO_HANDLER				=-85,	// ����ģ�鲻���ڻ���Ч
		BPR_NULL_ANS				=-86,	// Ӧ��Ϊ��

		// IXЭ����ش���
		BPR_IX_NOHANDLER			=-90,	// �Ҳ�����ӦIX����ģ���IX����ģ����Ч
		BPR_IX_NOBUFFER				=-91,	// ��ӦIXЭ��Ӧ�𻺳�������
		BPR_IX_BADSTRUCT			=-92,	// ����IX�ṹʧ��

		// ��������
		BPR_EXCHG_KEY_ERROR			=-100,	// ��Կ����ʧ��

		// ��ȷ�ı���
		BPR_SUCCESS					= 1,	// (�������)����ɹ�
		BPR_PENDING					= 2,	// (�������)�������ڴ��������,��Ҫ��һ������
		BPR_NORESULT				= 3,	// (�������)���������,���ǲ���ҪӦ���
	} IOCPBPR;

	// ��������(����: iocpsvrmodel.h)
	typedef enum enumIOCPBTYPE
	{	BTYPE_ROSE,							// �ͻ��˵�������������(����ʱ����)
		BTYPE_RROSE,						// ���������ͻ��˵�����(����ʱ����)
		BTYPE_OPUSHING,						// ��վ����(����ʱ����)
		BTYPE_IPUSHING,						// ��վ����(����ʱ����)
		BTYPE_INPROCESS,					// ����������(����ʱ����)
	} IOCPBTYPE;

	// �û����ʿ��ƴ���(����: iocpsvrcommon.h)
	typedef enum enumUSERACCESSCODE
	{	UAC_DEFAULT=0X0000000,					// Ĭ��ֵ
		UAC_AUTHORIZED=0X0000001,				// ��Ȩ�û�
		UAC_PRIMARY=0X0000002,					// ��(����)�Ự
		UAC_SERVANT=0X0000004,					// ����Ự
		UAC_PUSHABLE=0X0000008,					// ���ͱ�־
	} USERACCESSCODE;
#endif
typedef IOCPBPR BPR;
typedef IOCPBTYPE BUTYPE;


//////////////////////////////////////////////////////////////////////////
// ԭ��Э���ڲ���ʶ
#ifndef PROT_FLAGS
#define PROT_FLAGS
	#define PF_MASK_ANSBUFTYPE		0X000F				// Ӧ�𻺳�����
	#define PF_DEFSIZE				0X0000				// Ĭ�ϰ���С
	#define PF_SMALL				0X0001				// С�Ͱ���С
	#define PF_MEDIUM				0X0002				// �еȰ���С
	#define PF_LARGE				0X0003				// ���Ͱ���С
	#define PF_HUGE					0X0004				// �޴����С

	#define PF_MASK_THREADTYPE		0X00F0				// �߳�����(����)
	#define PF_COMM_THREAD			0X0010				// ͨѶ��������
	#define PF_CORE_THREAD			0X0020				// �ڲ���������
	#define PF_SCHED_BUSINESS		0X0030				// ���ȹ�����������
	#define PF_BINDED_BUSINESS		0X0040				// �󶨹�����������

	#define PF_MASK_PROTFLAG		0X0F00				// Э���ʶ(����)
	#define PF_SECPROT				0X0100				// ��ȫЭ��(Ӧǿ�Ƽ���)
	#define PF_IXPROT				0X0200				// ��Ϣ����Э��(Ӧ������־�͸���)
	#define PF_DISABLED				0X0400				// Э���ֹ(��ֹע��)

	#define PF_MASK_EXTEND			0XF000				// ��չ��ʶ(����)
	#define PF_EXT_ANSASYNC			0X1000				// �첽Ӧ��(�ӳٻ���������)
	#define PF_EXT_TRACER			0X2000				// Э����Ը���
	#define PF_EXT_LOGGER			0X4000				// Э�������־
	#define PF_EXT_RETOUCH			0X8000				// ��Ҫ���¹����Ự

	#define PF_MASK_SESSION			0X000F0000			// �Ự��־
	#define PF_SESSION_NONE			0X00000000			// ����Ҫ�Ự
	#define PF_SESSION_PERSIST		0X00010000			// ��Ҫ�����Ự(������)
	#define PF_SESSION_NPERSIST		0X00020000			// ��Ҫ�����Ự(������)
	#define PF_SESSION_REFER		0X00030000			// ��Ҫ���ûỰ
	#define PF_SESSION_OPTIONAL		0X00040000			// ��Ҫ���������ûỰ
#endif


// ԭ��Э����󼶱�ʹ������
#define EL_NOERROR					(0)				// �޴���
#define EL_PROTERROR				(1)				// Э���쳣
#define EL_APPERROR					(2)				// IX�������
#define EC_NOERROR					(0)				// �޴���


// ����Э��궨��
#define PFS_CommCall			PF_COMM_THREAD|PF_DEFSIZE
#define PFS_CommSmallCall		PF_COMM_THREAD|PF_SMALL
#define PFS_CoreCall			PF_CORE_THREAD|PF_DEFSIZE
#define PFS_CoreSmallCall		PF_CORE_THREAD|PF_SMALL
#define PFS_CoreAsyncCall		PF_CORE_THREAD|PF_EXT_ANSASYNC|PF_DEFSIZE
#define PFS_BindedCall			PF_BINDED_BUSINESS|PF_DEFSIZE
#define PFS_BindedSmallCall		PF_BINDED_BUSINESS|PF_SMALL
#define PFS_SchedCall			PF_SCHED_BUSINESS|PF_DEFSIZE
#define PFS_SchedSmallCall		PF_SCHED_BUSINESS|PF_SMALL

#define PFS_TouchCall			PF_CORE_THREAD|PF_SESSION_PERSIST|PF_DEFSIZE
#define PFS_TouchCallEx			PF_CORE_THREAD|PF_DEFSIZE
#define PFS_CommAppCall			PF_COMM_THREAD|PF_SESSION_REFER|PF_DEFSIZE
#define PFS_CoreAppCall			PF_CORE_THREAD|PF_SESSION_REFER|PF_DEFSIZE
#define PFS_CoreAsyncAppCall	PF_CORE_THREAD|PF_SESSION_REFER|PF_EXT_ANSASYNC|PF_DEFSIZE
#define PFS_SchedAppCall		PF_SCHED_BUSINESS|PF_SESSION_REFER|PF_DEFSIZE

#define PFS_TouchWebCall		PF_CORE_THREAD|PF_EXT_RETOUCH|PF_SMALL
#define PFS_CoreWebCall			PF_CORE_THREAD|PF_EXT_RETOUCH|PF_DEFSIZE
#define PFS_CoreWebSmallCall	PF_CORE_THREAD|PF_EXT_RETOUCH|PF_SMALL
#define PFS_SchedWebCall		PF_SCHED_BUSINESS|PF_EXT_RETOUCH|PF_DEFSIZE



// ��Ҫ�ӿ�
interface INull;						// �սӿ�
interface IObject;						// ���Ķ���ӿ�
	interface IReferObject;				// ���Ķ���ӿ�(�����ö���)
	interface IRemovableObject;			// ���Ķ���ӿ�(�ɳ�������)
	interface IProtectedObject;			// ���Ķ���ӿ�(�ɱ�������)
	interface IReferObjectList;			// ���Ķ����б�
	interface IReferObjectArray;		// ���Ķ�������
	interface IServer;					// ����ģ��ӿ�
	interface INotifySink;				// ֪ͨ������
		interface INSSessionManager;	// �Ự����֪ͨ������
		interface INSSSManager;			// �Ự״̬֪ͨ������
		interface INSConnectManager;	// ���ӹ���֪ͨ������
		interface INSMemoryDraft;		// �ڴ��ˮ����֪ͨ������
	interface IUser;					// �û�����
	interface ISession;					// SESSION�ӿ�
	interface IRoamSession;				// ����SESSION�ӿ�
	interface IConnect;					// ���ӽӿ�
	interface IStreamWriter;			// ������������
	interface IBusiness;				// ����ӿ�
interface IIXCategory;					// IXЭ�����

// ģ��ʵ�ֵ�Э��
interface ISDKInfo;						// SDK��Ϣ
interface ICoreModule;					// ����ģ��
interface IServlet;						// Ӧ�ýӿ�
interface IService;						// ����ӿ�
interface IProtocolDiscover;			// Э������
interface IProtocolFamily;				// ģʽЭ���
interface IProtocolEncoder;				// Э�������
interface IProtocolDecoder;				// Э�������
interface IProtocolDebugger;			// Э�������
interface IHandler;						// Э�鴦����
	
interface IAsyncHandler;				// �첽Э�鴦�����ӿ�
interface IAsyncObject;					// �첽���ö���
interface IDbgHandler;					// �ɼ��Э�鴦�����ӿ�
interface IPushingHandler;				// ���ʹ������ӿ�




// �ն���ӿ�
// (��IID����)
interface INull {};
interface INull1 {};
interface INull2 {};
interface INull3 {};
interface INull4 {};
interface INull5 {};
interface INull6 {};


// ��������ӿ�
// {CEE531B0-C2E5-49b2-A1EF-A91F6807961B}
static const IID IID_IObject = { 0xcee531b0, 0xc2e5, 0x49b2, { 0xa1, 0xef, 0xa9, 0x1f, 0x68, 0x7, 0x96, 0x1b } };
interface IObject
{	virtual LPVOID Cast(const IID & riid) PURE;
	virtual LPVOID GetObjectPtr() PURE;
	virtual BOOL IsObjectNull() const PURE;
};







//////////////////////////////////////////////////////////////////////////
// Э�鶨����ؽṹ







// IXЭ�鶨��
typedef struct tagIXPROTDEF
{	WORD		m_wFuncID;				// ����ID
	LPCSTR		m_pszName;				// ��������
	WPARAM		m_wParam;				// ���ܲ���(һ��洢IX���̱�־)
	LPARAM		m_lParam;				// ���ܲ���(һ��洢IX����ָ��)
} IXPROTDEF;
typedef IXPROTDEF* LPIXPROTDEF;


// Э������(����Э��Ĵ�����)
typedef struct tagPROTINFO
{	BYTE		m_cProtVer;				// ��ǰ����İ汾��
	WORD		m_wCmdNo;				// ��ǰ�����Э���
	CHAR		m_szCmdDesc[64];		// ��������
	DWORD		m_dwProtFlag;			// �ڲ���ʶ(�����߳����,�Ƿ�IXЭ��,�Ƿ���Ҫ��־�͸��ٵ�)
	DWORD		m_dwExtendPoolNo;		// �̳߳�(�����߳���Ч)
	DWORD		m_dwThreadSelector;		// �̺߳�(�����߳���Ч)
	IHandler*	m_pIHandler;			// �������
	LPVOID		m_pProtDef;				// Э�鶨��
	BYTE		m_cFuncType;			// ��������
	WORD		m_wFuncID;				// ����ID
} PROTINFO;
typedef PROTINFO* LPPROTINFO;



//////////////////////////////////////////////////////////////////////////
// �����Ķ�����غ궨��
#define CNTX_INVALID	((BYTE)(~0))	// ��Ч����
#define CNTX_ZERO		((BYTE)0)		// �ն���
#define CNTX_TEST		((BYTE)127)		// ���Զ���
#define CNTX_USER		((BYTE)128)		// �û�����(˳�����)


// �Ự����������
#define SCNTX_SESSIONREF			1		// �Ự���ö���
#define SCNTX_PRIVATEBRIDGECOUPLER	2		// ˽����(����������Ž�DTEͨ��,���԰������ͨ��)
#define SCNTX_SHAREBRIDGECOUPLER	3		// ������(����������Ž�DTE������)
#define SCNTX_RPCNODE				4		// RPCNode��Ϣ
#define SCNTX_ARPCSESSION			5		// ARPC�Ự����


// ���Ӵ���������
#define CCNTX_CONNECTREF			1		// �������ö���
#define CCNTX_STREAMWRITER_0		2		// ��д����(�׸�)
#define CCNTX_STREAMWRITER_MAX		11		// ��д����(���һ��)


// Э�鴦��������
#define BCNTX_BUSINESSREF			1		// �������ö���
#define BCNTX_PARSERDATA			2		// Э���������(���հ�����)
#define BCNTX_ENCODERPARAM			3		// ����������(���Ͱ�����)
#define BCNTX_PROTOCOLDECODER		4		// Ĭ�Ͻ���������
#define BCNTX_PROTOCOLENCODER		5		// Ĭ�ϱ���������

#define BCNTX_IXHANDLER				6		// IX������������(���������,��IXЭ����Ч),BUGBUG,��ȥ��,�ͼܹ��г�ͻ

#define BCNTX_RAWREQ				10		// ԭʼ����������
#define BCNTX_RAWANS				11		// ԭʼӦ��������

#define BCNTX_HTTPREQ				13		// HTTP����������
#define BCNTX_HTTPANS				14		// HTTPӦ��������

#define BCNTX_SIPREQ				15		// HTTP����������
#define BCNTX_SIPANS				16		// HTTPӦ��������

#define BCNTX_FIXREQ				17		// HTTP����������
#define BCNTX_FIXANS				18		// HTTPӦ��������

#define BCNTX_IXREQ					19		// IX����������,BUGBUG,��ȥ��,�ͼܹ��г�ͻ
#define BCNTX_IXANS					20		// IXӦ��������,BUGBUG,��ȥ��,�ͼܹ��г�ͻ

#define BCNTX_ASYNCREPLY			21		// �첽Ӧ��ӿ�



















//////////////////////////////////////////////////////////////////////////
// �߼�������


// �����ö���ӿ�
// {384DE26B-4C22-4068-B01A-0B27E98A818A}
static const IID IID_IReferObject = { 0x384de26b, 0x4c22, 0x4068, { 0xb0, 0x1a, 0xb, 0x27, 0xe9, 0x8a, 0x81, 0x8a } };
interface IReferObject : public IObject
{	virtual VOID AddRefObject() PURE;
	virtual VOID ReleaseObject() PURE;
};


// ���Ƴ����Ķ���ӿ�
// {79199CCF-C798-4fc6-8E3A-5800EFFEFB03}
static const IID IID_IRemovableObject = { 0x79199ccf, 0xc798, 0x4fc6, { 0x8e, 0x3a, 0x58, 0x0, 0xef, 0xfe, 0xfb, 0x3 } };
interface IRemovableObject : public IObject
{	virtual VOID ReleaseObject() PURE;
};

// �ܱ������Ķ���ӿ�
// {A4315B73-43B8-4fed-9524-E270A51BB624}
static const IID IID_IProtectedObject = { 0xa4315b73, 0x43b8, 0x4fed, { 0x95, 0x24, 0xe2, 0x70, 0xa5, 0x1b, 0xb6, 0x24 } };
interface IProtectedObject : public IObject
{	virtual VOID EnterAccess(BOOL bToRead) PURE;
	virtual VOID LeaveAccess(BOOL bToRead) PURE;
};


// ��������
class CProtectedAccess
{
public:
	CProtectedAccess(IObject* pIObject,BOOL bToRead)
		{	m_pIObject=pIObject;
			m_bToRead=bToRead;
			if(m_pIObject!=NULL)
			{	IProtectedObject* pIProtectedObject=(IProtectedObject*)m_pIObject->Cast(IID_IProtectedObject);
				if(pIProtectedObject!=NULL) pIProtectedObject->EnterAccess(bToRead);
			}
		}
	virtual~CProtectedAccess()
		{	Leave();
		}
	VOID Leave()
		{	if(m_pIObject!=NULL)
			{	IProtectedObject* pIProtectedObject=(IProtectedObject*)m_pIObject->Cast(IID_IProtectedObject);
				if(pIProtectedObject!=NULL) pIProtectedObject->LeaveAccess(m_bToRead);
				m_pIObject=NULL;
			}
		}
private:
	IObject* m_pIObject;
	BOOL m_bToRead;
};



// �����б�
// {5E8245E0-44A0-4c1a-8F00-FB91A65F0AAC}
static const IID IID_IReferObjectList = { 0x5e8245e0, 0x44a0, 0x4c1a, { 0x8f, 0x0, 0xfb, 0x91, 0xa6, 0x5f, 0xa, 0xac } };
interface IReferObjectList : public IReferObject
{	virtual VOID RemoveAll() PURE;
	virtual BOOL IsEmpty() PURE;
	virtual LONG GetCount() PURE;
	virtual POSITION Find(IReferObject* pIReferObject,POSITION posStartAfter) const PURE;
	virtual POSITION FindIndex(LONG nIndex) const PURE;
	virtual POSITION GetHeadPosition() const PURE;
	virtual POSITION GetTailPosition() const PURE;
	virtual IReferObject* GetNext(POSITION& posObject) PURE;
	virtual IReferObject* GetPrev(POSITION& posObject) PURE;
	virtual IReferObject* GetAt(POSITION posObject) PURE;
	virtual IReferObject* GetNext(POSITION& posObject) const PURE;
	virtual IReferObject* GetPrev(POSITION& posObject) const PURE;
	virtual IReferObject* GetAt(POSITION posObject) const PURE;
	virtual POSITION AddHead(IReferObject* pIReferObject) PURE;
	virtual POSITION AddTail(IReferObject* pIReferObject) PURE;
	virtual POSITION InsertBefore(POSITION posObject,IReferObject* pIReferObject) PURE;
	virtual POSITION InsertAfter(POSITION posObject,IReferObject* pIReferObject) PURE;
	virtual VOID SetAt(POSITION posObject,IReferObject* pIReferObject) PURE;
	virtual VOID AddHead(IReferObjectList* pIReferObjectList) PURE;
	virtual VOID AddTail(IReferObjectList* pIReferObjectList) PURE;
	virtual IReferObject* RemoveHead() PURE;
	virtual IReferObject* RemoveTail() PURE;
	virtual VOID RemoveAt(POSITION posObject) PURE;
};



// ��������
// {E78EA95E-04DE-46ac-94C9-2A61A7B51D55}
static const IID IID_IReferObjectArray = { 0xe78ea95e, 0x4de, 0x46ac, { 0x94, 0xc9, 0x2a, 0x61, 0xa7, 0xb5, 0x1d, 0x55 } };
interface IReferObjectArray : public IReferObject
{	virtual VOID RemoveAll() PURE;
	virtual BOOL IsEmpty() PURE;
	virtual LONG GetSize() PURE;
	virtual VOID SetSize(LONG nSize) PURE;
	virtual VOID SetAt(LONG nIndex,IReferObject* pIReferObject) PURE;
	virtual IReferObject* GetAt(LONG nIndex) PURE;
};



// �û���ʶ��Ϣ
typedef struct tagUSERID
{	DWORD	m_dwUOrgID;			// �û���֧����
	CHAR	m_szUID[UID_SIZE];	// �û�ID
} USERID;


// ����ģ��(�ӿ�)
// {9D6558B5-F570-4b83-9717-2432D223199B}
static const IID IID_IServer = { 0x9d6558b5, 0xf570, 0x4b83, { 0x97, 0x17, 0x24, 0x32, 0xd2, 0x23, 0x19, 0x9b } };
interface IServer : public IObject
{
	// ע��ͳ�����ȡ
	virtual LPCSTR GetHomeDir() const PURE;
	virtual LPCSTR GetConfigDir() const PURE;
	virtual LPCSTR GetLogDir() const PURE;
	virtual LPCSTR GetSwapDir() const PURE;
	virtual FLOAT  GetArchVer() const PURE;
	virtual LPCSTR GetArchBuild() const PURE;
	virtual LPCSTR GetArchIni() const PURE;
	virtual LPCSTR GetServicesXml() const PURE;
	virtual WORD GetServType() const PURE;
	virtual LONG GetLicenseType() const PURE;
	virtual LPCSTR GetLicenseFile() const PURE;
	virtual LONG GetLicenseStatus() const PURE;

	// ����������
	typedef enum enumSERVERCONTROL
	{	SERVERCONTROL_STOP,
		SERVERCONTROL_RESTART,
	} SERVERCONTROL;
	virtual VOID ServerControl(SERVERCONTROL eServerControl) PURE;

	// ������������Ϣ
	virtual BOOL IsLoggerOn() const PURE;
	virtual LPCSTR GetQSID() const PURE;
	virtual DWORD GetServID() const PURE;
	virtual LPCSTR GetServName() const PURE;
	virtual LPCSTR GetServDesc() const PURE;
	virtual DWORD GetServVer() const PURE;
	virtual BYTE GetSessionAlgoType() const PURE;
	virtual BYTE GetSessionKeyLenIdx() const PURE;
	virtual BYTE IsInternalSignalOn() const PURE;
	virtual BYTE IsExternalSignalOn() const PURE;
	virtual BYTE GetHashAlgoType() const PURE;
	virtual BOOL IsCertificateOn() const PURE;
	virtual LONG GetStartupTime() const PURE;
	virtual LPCSTR GetAppShortName() const PURE;
	virtual LPCSTR GetAppName() const PURE;
	virtual DWORD GetMaxSessionNum() const PURE;
	virtual DWORD GetNowSessionNum() const PURE;
	virtual DWORD GetMaxConnectNum() const PURE;
	virtual DWORD GetNowConnectNum() const PURE;
	virtual DWORD GetMaxBufSize() const PURE;
	virtual DWORD GetReqUnitSize() const PURE;
	virtual DWORD GetAnsUnitSize() const PURE;

	// ������Ԥ����Ϣ
	virtual BOOL GetAlarmStatus() const PURE;
	virtual VOID GetAlarmText(LPSTR pszAlarmText,DWORD cbAlarmText) const PURE;

	// �û�����
	virtual IUser* GetSysUser() PURE;
	virtual IUser* GetConUser() PURE;
	virtual IUser* GetMACUser() PURE;
	virtual IUser* CreateUser() PURE;
	virtual BOOL SerializeUserR(IUser* pIUser,LPBYTE pArchive,DWORD cbArchive) PURE;
	virtual BOOL SerializeUserW(IUser* pIUser,LPBYTE pArchive,DWORD cbArchiveMax,DWORD& cbArchive) PURE;

	// ����ע��
	virtual BOOL RegisterModule(ICoreModule* pICoreModule) PURE;
	virtual BOOL RegisterService(LPCSTR pszService,IService* pIService) PURE;
	virtual BOOL RegisterServlet(LPCSTR pszServlet,IServlet* pIServlet) PURE;
	virtual BOOL RegisterProtocolDiscover(IProtocolDiscover* pIProtocolDiscover) PURE;
	virtual BOOL RegisterProtocolFamily(LPCSTR pszProtocolFamily,IProtocolFamily* pIProtocolFamily) PURE;
	virtual BOOL RegisterHandler(IHandler* pIHandler) PURE;
	virtual BOOL RegisterNotifySink(INotifySink* pINotifySink) PURE;
	virtual BOOL DeclareDependency(IService* pIService,LPCSTR pszServiceNeed) PURE;
	virtual BOOL DeclareExtend(LPCSTR pszMainService,IService* pIService) PURE;

	// ����ָʾ��
	virtual BOOL RegisterIndicator(LPCSTR pszName,BOOL bFlowOrLv,HANDLE hIndicator) PURE;
	virtual POSITION GetIndicator(LPCSTR pszName) PURE;
	virtual POSITION GetFirstIndicator() PURE;
	virtual VOID GetNextIndicator(POSITION& posIndicator) PURE;
	virtual LPCSTR GetIndicatorName(POSITION posIndicator) PURE;
	virtual BOOL GetIndicatorIsFlowOrLv(POSITION posIndicator) PURE;
	virtual HANDLE GetIndicatorHandle(POSITION posIndicator) PURE;

	// �û������Ķ������
	typedef enum enumUCCATEGORY
	{	UCCATEGORY_SC,
		UCCATEGORY_CC,
		UCCATEGORY_BC,
	} UCCATEGORY;
	virtual BYTE RegisterUserCntxClass(UCCATEGORY eUCCategory,LPCSTR pszName,DWORD cbObject,DESTRUCTOR pfnDestructor,CONNECTOR pfnConnector) PURE;
	virtual BYTE GetUserCntxClass(UCCATEGORY eUCCategory,LPCSTR pszName) PURE;
	virtual LPVOID AllocUserCntxObj(UCCATEGORY eUCCategory,BYTE cClassId,LPVOID pOwner) PURE;

	// �̷߳����ע��
	virtual LONG RegisterTAT(LPCSTR pszName,DWORD dwThreadNum,LPCSTR pszComment) PURE;
	virtual LONG GetRegisteredTAT(LPCSTR pszName) PURE;
	virtual LONG GetThreadOffInTAT(LONG nTATDef) PURE;
	virtual LONG GetThreadNumInTAT(LONG nTATDef) PURE;

	// ��־����
	virtual VOID AddInfoLog(LPCSTR lpszFmt,...) PURE;
	virtual VOID AddInfoLogV(LPCSTR lpszFmt,va_list args) PURE;
	virtual VOID AddErrorLog(LPCSTR lpszFmt,...) PURE;
	virtual VOID AddErrorLogV(LPCSTR lpszFmt,va_list args) PURE;
	virtual VOID AddRawCallLog(BOOL bResult,LPBYTE lpData,DWORD cbData) PURE;
	virtual VOID DirectLogger(DWORD dwSlotNo,LPBYTE lpData,DWORD cbData) PURE;
	virtual VOID DirectTracer(LPCSTR lpszFmt,...) PURE;
	virtual VOID DirectTracerV(LPCSTR lpszFmt,va_list args) PURE;

	// ������־ת�����
	virtual VOID BusinessToLogger(HANDLE hLogger,LPCBYTE pszBuf,DWORD cbBuf) PURE;
	virtual VOID BusinessToTraceWnd(HANDLE hTraceWnd,LPCSTR pszInfo) PURE;

	// �����б�����鴦��
	virtual IReferObjectList* CreateObjectList(LONG nBlockSize) PURE;
	virtual IReferObjectArray* CreateObjectArray(LONG nGrowBy) PURE;

	// ����,Ӧ��,Э���ע�����
	virtual LPVOID GetRegisteredService(LPCSTR pszService,const IID & riid,BOOL bAddRef) PURE;
	virtual LPVOID GetRegisteredServlet(LPCSTR pszServlet,const IID & riid,BOOL bAddRef) PURE;
	virtual IProtocolFamily* GetRegisteredProtocolFamily(LPCSTR pszProtocolFamily) PURE;

	// ���ӺͻỰ����
	virtual VOID EnumOnlineSessions(IReferObjectList* pIReferObjectList,BOOL bSkipShortLink) PURE;
	virtual VOID EnumNamedSessions(IReferObjectList* pIReferObjectList,BOOL bSkipShortLink,BOOL bMatchPrimary,DWORD dwUOrgID,LPCSTR pszUID) PURE;
	virtual VOID EnumOnlineConnects(IReferObjectList* pIReferObjectList,BOOL bHasSession) PURE;
	virtual ISession* OpenSession(DWORD idSession) PURE;
	virtual IConnect* OpenConnect(DWORD idConnect) PURE;
	virtual BOOL ShutdownSession(ISession* pISession,BPR nBPR) PURE;
	virtual BOOL ShutdownConnect(IConnect* pIConnect,BPR nBPR) PURE;
	virtual BOOL ShutdownSessionByID(DWORD idSession,BPR nBPR) PURE;
	virtual BOOL ShutdownConnectByID(DWORD idConnect,BPR nBPR) PURE;


	// ���ܴ���(���ڶ�����ܺͽ���)
	virtual BYTE GetPKIBitIdx(BYTE cPKIType) const PURE;
	virtual LPCMD5BIN GetServPubKeyMD5(BYTE cPKIType) const PURE;
	virtual LPCBYTE GetServPubKeyPtr(BYTE cPKIType) const PURE;
	virtual LONG GetServPubKeyLen(BYTE cPKIType) const PURE;
	virtual LPCBYTE GetServPubKeySignPtr(BYTE cPKIType) const PURE;
	virtual DWORD GetServPubKeySignLen(BYTE cPKIType) const PURE;
	virtual BOOL BlowfishLightlyEncrypt(LPBYTE lpBuffer,int nLength) PURE;
	virtual BOOL BlowfishLightlyDecrypt(LPBYTE lpBuffer,int nLength) PURE;
	virtual BOOL Des3LightlyEncrypt(LPBYTE lpBuffer,int nLength) PURE;
	virtual BOOL Des3LightlyDecrypt(LPBYTE lpBuffer,int nLength) PURE;

	// ����ͽ��봦��
	virtual BPR BusinessDecoding(ISession* pISession,IConnect* pIConnect,IBusiness* pIBusiness,LONG nLevel) PURE;
	virtual BPR BusinessEncoding(ISession* pISession,IConnect* pIConnect,IBusiness* pIBusiness,LONG nLevel) PURE;

	// ����ͽ������
	virtual BPR UnpackStdBuffer(ISession* pISession,IConnect* pIConnect,IBusiness* pIBusiness,
		LPBYTE pReqBody,DWORD cbPacket,DWORD cbRawLen,BYTE cCompressType,BYTE cEncryptType) PURE;
	virtual BPR PackStdBuffer(ISession* pISession,IConnect* pIConnect,IBusiness* pIBusiness,
		LPBYTE pAnsBody,DWORD cbRawLen,DWORD cbMaxAnsBody,BYTE& cCompressType,BYTE& cEncryptType,DWORD& cbPacket) PURE;
	virtual VOID GetSuggestPackStdParam(ISession* pISession,IConnect* pIConnect,IBusiness* pIBusiness,
		DWORD cbData,BYTE cDefEncryptType,BYTE& cCompressType,BYTE& cEncryptType) PURE;

	// ���񻺳�������
	virtual BPR PrepareWriteBufAndEncoder(IConnect* pIConnect,IBusiness* pIBusiness) PURE;

	// Э���쳣����
	virtual BPR ThrowProtocolError(IConnect* pIConnect,IBusiness* pIBusiness,LONG nFailCode,LPCSTR pszFormat,...) PURE;
	virtual BPR ThrowProtocolError(IConnect* pIConnect,IBusiness* pIBusiness,BOOL bAddPrefix,LONG nFailCode,LPCSTR pszFormat,...) PURE;
	virtual BPR ThrowProtocolErrorV(IConnect* pIConnect,IBusiness* pIBusiness,LONG nFailCode,LPCSTR pszFormat,va_list args) PURE;
	virtual BPR ThrowProtocolErrorV(IConnect* pIConnect,IBusiness* pIBusiness,BOOL bAddPrefix,LONG nFailCode,LPCSTR pszFormat,va_list args) PURE;

	// �첽������(�����������)
	virtual BPR AsyncAnswerBuffer(IBusiness* pIBusiness) PURE;
	virtual BPR AsyncComplete(IBusiness* pIBusiness,BOOL bEOR) PURE;
	virtual VOID AsyncException(IBusiness* pIBusiness,BOOL bAddPrefix,LONG nFailCode,LPCSTR pszFormat,...) PURE;
	virtual VOID AsyncExceptionV(IBusiness* pIBusiness,BOOL bAddPrefix,LONG nFailCode,LPCSTR pszFormat,va_list args) PURE;

	// ���ʹ���ͷ����������������
	virtual BPR CreateOPushingBusinessSpace(HANDLE& hBusinessSpace,LONG nBusinessNum) PURE;
	virtual VOID ReleaseBusinessSpace(HANDLE hBusinessSpace) PURE;
	virtual IBusiness* StrippingBusiness(HANDLE hBusinessSpace) PURE;
	virtual BPR CreateOPushingBusiness(IBusiness*& pIBusiness,HANDLE hBusinessSpace,DWORD idSession,LPCSTR pszEncoders,...) PURE;
	virtual BPR CreateReverseBusiness(IBusiness*& pIBusiness,HANDLE hBusinessSpace,DWORD idSession,LPCSTR pszEncoders,...) PURE;
	virtual BPR CompleteAndSendBusinessLL(IConnect* pIConnect,IBusiness* pIBusiness) PURE;
	virtual VOID AbortUnmanagedBusiness(IBusiness* pIBusiness,BPR nBPR) PURE;


	// AP�ڵ�����·����Ϣά��
	virtual BOOL RegisterAPNode(DWORD idAPNode,DWORD idSession) PURE;
	virtual BOOL UnregisterAPNode(DWORD idAPNode,DWORD idSession) PURE;
	virtual DWORD GetAvailableSessionOfAPNode(DWORD idAPNode) PURE;
	virtual ISession* OpenRouteSessionOfAPNode(DWORD idAPNodeUplink,DWORD idAPNode,DWORD idSession,BOOL bAlternate) PURE;
	virtual ISession* OpenRoamSessionOfAPNode(DWORD idAPNode,DWORD idSession) PURE;



	// ԭʼ����(�ͽ�����,��Ƭ����,�Զ�����,��֧�ֶ༶����Ҫ���д���·��ת��)
	virtual BPR PushingLL(ISession* pISession,IConnect* pIConnect,LPCBYTE pOption,DWORD cbOption,LPBYTE pBody,DWORD cbBody,DWORD dwTransKey,WORD wCmdNo,LPCSTR pszCmdDesc,DWORD dwFragmentNo) PURE;
	virtual BPR PushingFragment(ISession* pISession,IConnect* pIConnect,IBusiness* pIBusiness,LPCBYTE pOption,DWORD cbOption,LPBYTE pBody,DWORD cbBody,DWORD dwFragmentNo) PURE;
	virtual BPR PushingS2C(ISession* pISession,IConnect* pIConnect,IUser* pIUser,LPCBYTE pOption,DWORD cbOption,LPBYTE pBody,DWORD cbBody,WORD wCmdNo,LPCSTR pszCmdDesc) PURE;



	// ֱ������(��֧�ֶ༶��,��˲�֧�ַ��䴦��)
	virtual BPR PushingBySession(HANDLE hBusinessSpace,ISession* pISession,LPCSTR pszDesc,DWORD idPushingType,DWORD dwPushingOption,...) PURE;
	virtual BPR PushingBySessionV(HANDLE hBusinessSpace,ISession* pISession,LPCSTR pszDesc,DWORD idPushingType,DWORD dwPushingOption,va_list args) PURE;
	// ֱ������
	virtual BPR PushingDR_KICKOUT(HANDLE hBusinessSpace,ISession* pISession,LPCSTR pszDesc,LPCSTR pszAPFrom,IPV6 IpFrom,systm_t tOccur) PURE;
	virtual BPR PushingDR_MSGLL(HANDLE hBusinessSpace,ISession* pISession,LPCSTR pszDesc,LPCSTR pszMsg) PURE;
	virtual BPR PushingDR_MSG(HANDLE hBusinessSpace,ISession* pISession,LPCSTR pszDesc,LPCSTR pszFormat,...) PURE;
	virtual BPR PushingDR_IX20(HANDLE hBusinessSpace,ISession* pISession,LPCSTR pszDesc,BYTE cFuncType,WORD wFuncID,DWORD dwUOrgID,LPCBYTE pData,DWORD cbData)  PURE;
	virtual BPR PushingDR_TQL(HANDLE hBusinessSpace,ISession* pISession,LPCSTR pszDesc,LPCBYTE pData,DWORD cbData) PURE;
	virtual BPR PushingDR_TJS(HANDLE hBusinessSpace,ISession* pISession,LPCSTR pszDesc,LPCBYTE pData,DWORD cbData) PURE;
	virtual BPR PushingDR_LASTWORD(HANDLE hBusinessSpace,ISession* pISession,LPCSTR pszDesc,LPCSTR pszLastword) PURE;
	virtual BPR PushingDR_NOTICE(HANDLE hBusinessSpace,ISession* pISession,LPCSTR pszDesc,time_t tTime,LPCSTR pszNotice) PURE;
	virtual BPR PushingDR_URGENT(HANDLE hBusinessSpace,ISession* pISession,LPCSTR pszDesc,time_t tTime,DWORD dwUOrgID,LPCSTR pszUrgent) PURE;
	virtual BPR PushingDR_INSTRUCT(HANDLE hBusinessSpace,ISession* pISession,LPCSTR pszDesc,LPCSTR pszInstruct) PURE;


	// ·������·������
	virtual BOOL MakeSimpleAP(ISession* pISession,IConnect* pIConnect,LPSTR pszAP,DWORD cbAPMax) PURE;
	virtual DWORD GetAPLv(LPCSTR pszAP) PURE;
	virtual LPCSTR GetFortressAPNode(LPCSTR pszAP,LPSTR pszAPNode,DWORD cbAPNode) PURE;
	virtual LPCSTR GetNearAPNode(LPCSTR pszAP) PURE;
	virtual DWORD GetAPNodeID(LPCSTR pszAPNode) PURE;
	virtual DWORD GetAPNodeSessionID(LPCSTR pszAPNode) PURE;
	virtual LPCSTR GetAPNodeTracker(LPCSTR pszAPNode) PURE;
	virtual BOOL AddToAPNode(LPSTR pszAP,DWORD cbAPMax,ISession* pISession,IConnect* pIConnect) PURE;
	virtual BOOL PulloutNearAPNode(LPSTR pszAP) PURE;
	// ·�������Լ���ص����ͷ���
	virtual BPR PushingByRoute(HANDLE hBusinessSpace,LPCSTR pszAP,BOOL bUserID,LPVOID pUser,LPCSTR pszDesc,DWORD idPushingType,DWORD dwPushingOption,...) PURE;
	virtual BPR PushingByRouteV(HANDLE hBusinessSpace,LPCSTR pszAP,BOOL bUserID,LPVOID pUser,LPCSTR pszDesc,DWORD idPushingType,DWORD dwPushingOption,va_list args) PURE;
	virtual BPR PushingReflectByRoute(DWORD idPushingType,DWORD dwPushingOption,LPBYTE pSequence,DWORD cbSequeue) PURE;
	// ·��������ظ߼�����
	virtual BPR PushingRT_KICKOUT(HANDLE hBusinessSpace,LPCSTR pszAP,BOOL bUserID,LPVOID pUser,LPCSTR pszDesc,LPCSTR pszAPFrom,IP IpFrom,systm_t tOccur) PURE;
	virtual BPR PushingRT_MSGLL(HANDLE hBusinessSpace,LPCSTR pszAP,BOOL bUserID,LPVOID pUser,LPCSTR pszDesc,LPCSTR pszMsg) PURE;
	virtual BPR PushingRT_MSG(HANDLE hBusinessSpace,LPCSTR pszAP,BOOL bUserID,LPVOID pUser,LPCSTR pszDesc,LPCSTR pszFormat,...) PURE;
	virtual BPR PushingRT_IX20(HANDLE hBusinessSpace,LPCSTR pszAP,BOOL bUserID,LPVOID pUser,LPCSTR pszDesc,BYTE cFuncType,WORD wFuncID,DWORD dwUOrgID,LPCBYTE pData,DWORD cbData) PURE;
	virtual BPR PushingRT_TQL(HANDLE hBusinessSpace,LPCSTR pszAP,BOOL bUserID,LPVOID pUser,LPCSTR pszDesc,LPCBYTE pData,DWORD cbData) PURE;
	virtual BPR PushingRT_TJS(HANDLE hBusinessSpace,LPCSTR pszAP,BOOL bUserID,LPVOID pUser,LPCSTR pszDesc,LPCBYTE pData,DWORD cbData) PURE;
	virtual BPR PushingRT_LASTWORD(HANDLE hBusinessSpace,LPCSTR pszAP,BOOL bUserID,LPVOID pUser,LPCSTR pszDesc,LPCSTR pszLastword) PURE;
	virtual BPR PushingRT_NOTICE(HANDLE hBusinessSpace,LPCSTR pszAP,BOOL bUserID,LPVOID pUser,LPCSTR pszDesc,time_t tTime,LPCSTR pszNotice) PURE;
	virtual BPR PushingRT_URGENT(HANDLE hBusinessSpace,LPCSTR pszAP,BOOL bUserID,LPVOID pUser,LPCSTR pszDesc,time_t tTime,DWORD dwUOrgID,LPCSTR pszUrgent) PURE;
	virtual BPR PushingRT_INSTRUCT(HANDLE hBusinessSpace,LPCSTR pszAP,BOOL bUserID,LPVOID pUser,LPCSTR pszDesc,LPCSTR pszInstruct) PURE;




	// ���������Լ���ص����ͷ���
	virtual BPR PushingByRoam(HANDLE hBusinessSpace,IRoamSession* pIRoamSession,LPCSTR pszDesc,DWORD idPushingType,DWORD dwPushingOption,...) PURE;
	virtual BPR PushingByRoamV(HANDLE hBusinessSpace,IRoamSession* pIRoamSession,LPCSTR pszDesc,DWORD idPushingType,DWORD dwPushingOption,va_list args) PURE;
	virtual BPR PushingReflectByRoam(DWORD idPushingType,DWORD dwPushingOption,LPBYTE pSequence,DWORD cbSequeue) PURE;
	// ����������ظ߼�����
	virtual BPR PushingRO_KICKOUT(HANDLE hBusinessSpace,IRoamSession* pIRoamSession,LPCSTR pszDesc,LPCSTR pszAPFrom,IP IpFrom,systm_t tOccur) PURE;
	virtual BPR PushingRO_MSGLL(HANDLE hBusinessSpace,IRoamSession* pIRoamSession,LPCSTR pszDesc,LPCSTR pszMsg) PURE;
	virtual BPR PushingRO_MSG(HANDLE hBusinessSpace,IRoamSession* pIRoamSession,LPCSTR pszDesc,LPCSTR pszFormat,...) PURE;
	virtual BPR PushingRO_IX20(HANDLE hBusinessSpace,IRoamSession* pIRoamSession,LPCSTR pszDesc,BYTE cFuncType,WORD wFuncID,DWORD dwUOrgID,LPCBYTE pData,DWORD cbData) PURE;
	virtual BPR PushingRO_TQL(HANDLE hBusinessSpace,IRoamSession* pIRoamSession,LPCSTR pszDesc,LPCBYTE pData,DWORD cbData) PURE;
	virtual BPR PushingRO_TJS(HANDLE hBusinessSpace,IRoamSession* pIRoamSession,LPCSTR pszDesc,LPCBYTE pData,DWORD cbData) PURE;
	virtual BPR PushingRO_LASTWORD(HANDLE hBusinessSpace,IRoamSession* pIRoamSession,LPCSTR pszDesc,LPCSTR pszLastWord) PURE;
	virtual BPR PushingRO_NOTICE(HANDLE hBusinessSpace,IRoamSession* pIRoamSession,LPCSTR pszDesc,time_t tTime,LPCSTR pszNotice) PURE;
	virtual BPR PushingRO_URGENT(HANDLE hBusinessSpace,IRoamSession* pIRoamSession,LPCSTR pszDesc,time_t tTime,DWORD dwUOrgID,LPCSTR pszUrgent) PURE;
	virtual BPR PushingRO_INSTRUCT(HANDLE hBusinessSpace,IRoamSession* pIRoamSession,LPCSTR pszDesc,LPCSTR pszInstruct) PURE;




	// ��ʽ�����Լ���ص����ͷ���
	virtual BPR PushingByChain(IBusiness* pIBusiness,LPCSTR pszDesc,DWORD idPushingType,DWORD dwPushingOption,...) PURE;
	virtual BPR PushingByChainV(IBusiness* pIBusiness,LPCSTR pszDesc,DWORD idPushingType,DWORD dwPushingOption,va_list args) PURE;
	virtual BPR PushingReflectByChain(IBusiness* pIBusinessHost,DWORD idPushingType,DWORD dwPushingOption,LPBYTE pSequence,DWORD cbSequeue) PURE;
	// ��ʽ������ظ߼�����(�û��й�,Ȩ�޹���,QOS����,�û�״̬����)
	virtual BPR ManageEndingUser(IBusiness* pIBusiness,BYTE cZoneID,DWORD dwUOrgID,LPCSTR pszUOrg,LPCSTR pszUID,DWORD dwRoleID,LPCSTR pszUName,DWORD dwAccessCode) PURE;
	virtual BPR ManagePermission(IBusiness* pIBusiness,LPCSTR pszPermission) PURE;
	virtual BPR ManageQOSOption(IBusiness* pIBusiness,BOOL bHAMode,LONG nSoftQPC,LONG nSoftCPC,LONG nSoftFPC) PURE;
	virtual BPR ManageSessionStatus(IBusiness* pIBusiness,DWORD dwAddFlags,DWORD dwRemoveFlags,DWORD dwData1,DWORD dwData2) PURE;



	// �����������ʹ���
	virtual BPR S2SPushingDispatch(ISession* pISession,IConnect* pIConnect,IBusiness* pIBusinessHost,DWORD dwPushingLv,DWORD idPushingType,DWORD dwPushingOption,LPBYTE pSequence,DWORD cbSequence) PURE;



	// �������ڲ�����(�û��й�)
	virtual BPR ManageLocalUser(ISession* pISession,IConnect* pIConnect,IBusiness* pIBusiness) PURE;



	// �������ڲ�����(��ȫ,�汾,�ڴ�,�߳�)
	virtual DWORD GetDefaultCredit() const PURE;
	virtual DWORD GetCrisisCredit() const PURE;
	virtual VOID ChangeCreditOfSourceIp(IP Ip,DWORD dwToCredit,IUser* pIUser,LPCSTR pszDescription) PURE;
	virtual VOID ChangeCreditOfClientIp(IP Ip,DWORD dwToCredit,IUser* pIUser) PURE;
	virtual VOID ChangeCreditOfClientMac(MAC Mac,DWORD dwToCredit,IUser* pIUser) PURE;
	virtual VOID RestoreCreditOfSourceIp(IP Ip,IUser* pIUser) PURE;
	virtual VOID RestoreCreditOfClientIp(IP Ip,IUser* pIUser) PURE;
	virtual VOID RestoreCreditOfClientMac(MAC Mac,IUser* pIUser) PURE;
	virtual BOOL IsSourceIpFrozen(IP Ip) PURE;
	virtual BOOL IsClientIpFrozen(IP Ip) PURE;
	virtual BOOL IsClientMacFrozen(MAC Mac) PURE;
	virtual VOID EnumSourceIps(VOID (*pfnCallback)(IP&,LPVOID,LPVOID),LPVOID pParam) PURE;
	virtual VOID EnumClientIps(VOID (*pfnCallback)(IP&,LPVOID,LPVOID),LPVOID pParam) PURE;
	virtual VOID EnumClientMacs(VOID (*pfnCallback)(MAC&,LPVOID,LPVOID),LPVOID pParam) PURE;
	virtual VOID EnumVersions(VOID (*pfnCallback)(LPVOID,LPVOID),LPVOID pParam) PURE;
	virtual VOID EnumMemorys() PURE;
	virtual VOID EnumThreads() PURE;
};


// ֪ͨ������
// {ADAAA54A-66FC-41af-808B-A35C787E2BEE}
static const IID IID_INotifySink = { 0xadaaa54a, 0x66fc, 0x41af, { 0x80, 0x8b, 0xa3, 0x5c, 0x78, 0x7e, 0x2b, 0xee } };
interface INotifySink : public IObject
{
};


// �Ự����֪ͨ������
// {27D4A505-6142-45dc-B1C7-EEF83E47CDD1}
static const IID IID_INSSessionManager = { 0x27d4a505, 0x6142, 0x45dc, { 0xb1, 0xc7, 0xee, 0xf8, 0x3e, 0x47, 0xcd, 0xd1 } };
interface INSSessionManager : public INotifySink
{	virtual VOID OnSessionOnline(ISession* pISession) PURE;
	virtual VOID OnSessionOffline(ISession* pISession) PURE;
};

// �Ự״̬֪ͨ������
// {4CB72F15-B0DC-4807-9B1F-1F515968BA36}
static const IID IID_INSSSManager = { 0x4cb72f15, 0xb0dc, 0x4807, { 0x9b, 0x1f, 0x1f, 0x51, 0x59, 0x68, 0xba, 0x36 } };
interface INSSSManager : public INotifySink
{	virtual VOID OnSessionSSModified(ISession* pISession) PURE;

};

// ���ӹ���֪ͨ������
// {92CC2E5B-8D77-4368-8E94-446F75C101F1}
static const IID IID_INSConnectManager = { 0x92cc2e5b, 0x8d77, 0x4368, { 0x8e, 0x94, 0x44, 0x6f, 0x75, 0xc1, 0x1, 0xf1 } };
interface INSConnectManager : public INotifySink
{	virtual VOID OnConnectRejected(IP SourceIp,WORD wSourcePort,LONG nCause) PURE;
	virtual VOID OnConnectCreated(IConnect* pIConnect) PURE;
	virtual VOID OnConnectDestroyed(IConnect* pIConnect,LONG nCause,LONG nCauseParam) PURE;
	virtual VOID OnAutoReduceCreditOfConnect(IConnect* pIConnect,LONG nCause,LONG nCauseParam,DWORD dwReduceCredit) PURE;
};


// �ڴ��ˮ����֪ͨ������
// {839F5A55-8D6B-47c4-B1DE-9A206B0051D8}
static const IID IID_INSMemoryDraft = { 0x839f5a55, 0x8d6b, 0x47c4, { 0xb1, 0xde, 0x9a, 0x20, 0x6b, 0x0, 0x51, 0xd8 } };
interface INSMemoryDraft : public INotifySink
{	virtual VOID OnMemoryDraftLvChanged(LONG nOldMemoryDraftLv,LONG nNewMemoryDraftLv) PURE;
};


// �û�����ӿ�
// {F4BE5923-6C46-40ef-865E-48E94D550039}
static const IID IID_IUser = { 0xf4be5923, 0x6c46, 0x40ef, { 0x86, 0x5e, 0x48, 0xe9, 0x4d, 0x55, 0x0, 0x39 } };
interface IUser : public IRemovableObject
{
	// ��������
	virtual VOID EmptyAPInfo() PURE;
	virtual VOID EmptyConnectInfo() PURE;
	virtual VOID EmptyEntryPoint() PURE;
	virtual VOID EmptyUserInfo() PURE;
	virtual VOID UpdateAPInfo(IUser* pIUser) PURE;
	virtual VOID UpdateConnectInfo(IUser* pIUser) PURE;
	virtual VOID UpdateEntryPoint(IUser* pIUser) PURE;
	virtual VOID UpdateUserProfile(IUser* pIUser) PURE;
	
	virtual VOID ZeroUser() PURE;
	virtual VOID CopyUserData(IUser* pIUser) PURE;
	virtual VOID CopyUserData(BOOL bUserID,LPVOID pUser) PURE;

	// ��¼λ���������
	virtual VOID SetAPInfo(DWORD dwAPServID,DWORD dwAPSessionID) PURE;
	virtual DWORD GetAPServID() const PURE;
	virtual DWORD GetAPSessionID() const PURE;

	// ���λ�úͰ汾��Ϣ
	virtual VOID SetConnectInfo(LPCSTR pszDevice,const IP& EthernetIp,const IP& InternetIp,const MAC& Mac,LPCSTR pszBuildName,WORD wType,DWORD dwVersion) PURE;
	virtual VOID SetDevice(LPCSTR pszDevice) PURE;
	virtual VOID SetEthernetIp(const IP& Ip) PURE;
	virtual VOID SetInternetIp(const IP& Ip) PURE;
	virtual VOID SetMac(const MAC& Mac) PURE;
	virtual VOID SetBuildName(LPCSTR pszBuildName) PURE;
	virtual VOID SetClientType(WORD wType) PURE;
	virtual VOID SetClientVer(DWORD dwVersion) PURE;
	virtual LPCSTR GetDevice() const PURE;
	virtual IP GetEthernetIp() const PURE;
	virtual IP GetInternetIp() const PURE;
	virtual MAC GetMac() const PURE;
	virtual LPCSTR GetBuildName() const PURE;
	virtual WORD GetClientType() const PURE;
	virtual DWORD GetClientVer() const PURE;

	// ��ڵ���Ϣ
	virtual VOID SetEntryPoint(WORD wEntryPoint) PURE;
	virtual WORD GetEntryPoint() PURE;

	// ����û���Ϣ
	virtual VOID SetUserProfile(BYTE cZoneID,DWORD dwUOrgID,LPCSTR pszUOrg,LPCSTR pszUID,DWORD dwRoleID,LPCSTR pszUName,DWORD dwAccessCode) PURE;
	virtual VOID SetZoneID(BYTE cZoneID) PURE;
	virtual VOID SetUOrgID(DWORD dwUOrgID) PURE;
	virtual VOID SetUOrg(LPCSTR pszUOrg) PURE;
	virtual VOID SetUID(LPCSTR pszUID) PURE;
	virtual VOID SetRoleID(DWORD dwRoleID) PURE;
	virtual VOID SetUName(LPCSTR pszUName) PURE;
	virtual VOID SetAccessCode(DWORD dwAccessCode) PURE;
	virtual BYTE GetZoneID() PURE;
	virtual DWORD GetUOrgID() PURE;
	virtual LPCSTR GetUOrg() PURE;
	virtual LPCSTR GetUID() PURE;
	virtual DWORD GetRoleID() PURE;
	virtual LPCSTR GetUName() PURE;
	virtual DWORD GetAccessCode() PURE;
};
// ���ý�ɫID����
#define ROLE_ANONYMOUS		0
#define ROLE_UNKNOWNUSR		1
#define ROLE_SYSTEMS		100000
#define ROLE_SYSTEM			(ROLE_SYSTEMS+0)
#define ROLE_CONSOLE		(ROLE_SYSTEMS+1)
#define ROLE_MACHINE		(ROLE_SYSTEMS+2)
#define ROLE_RPCUSER		(ROLE_SYSTEMS+3)




// SESSION�ӿ�
// {096A963F-4CDE-42a3-9578-A5EBD3AAAA51}
static const IID IID_ISession = { 0x96a963f, 0x4cde, 0x42a3, { 0x95, 0x78, 0xa5, 0xeb, 0xd3, 0xaa, 0xaa, 0x51 } };
interface ISession : public IReferObject
{
	// ��ȡ�ỰID
	virtual DWORD GetSessionNo() const PURE;
	virtual DWORD GetSessionID() const PURE;
	virtual BOOL IsPersistentMode() const PURE;

	// �Ự��������
	virtual const systm_t GetCreatedTime() const PURE;
	virtual const systm_t GetAnnounceTime() const PURE;

	// ��Կ����
	virtual BOOL ExchangeSessionKeyPKI(BYTE cPKIType,LPBYTE pClientPubKey,LONG cbClientPubKey,LPBYTE lpSignature,DWORD cbSignature,LPBYTE pSessionKey,LONG cbSessionKey,WORD* lpwSessionKey) PURE;
	virtual BOOL ExchangeSessionKeyNoPKI(LPCSTR pszSessionKey) PURE;
	virtual BOOL ExchangeSessionKeyNoPKI(LPSTR pszSessionKey,DWORD cbSessionKey) PURE;
	virtual BOOL SetBlowfishKey(LPCSTR pszKey) PURE;
	virtual BOOL SetDes3Key(LPCSTR pszKey) PURE;
	virtual BOOL IsSessionKeyValid() PURE;
	virtual BOOL IsBlowfishKeyValid() PURE;
	virtual BOOL IsDes3KeyValid() PURE;

	// ���úͻ�ȡ�Ự����(������Ϣ,��ڵ�,�û���Ϣ,��¼��־)
	virtual VOID UpdateConnectInfo(IUser* pIUser) PURE;
	virtual VOID UpdateEntryPoint(IUser* pIUser) PURE;
	virtual VOID UpdateUserProfile(IUser* pIUser) PURE;
	virtual VOID UpdateUserData(IUser* pIUser) PURE;
	virtual IUser* GetCreator() PURE;

	// �����Ķ���
	virtual LPVOID AllocCntxObj(BYTE cType,LPCSTR pszName,DWORD cbObject,DESTRUCTOR pfnDestructor,CONNECTOR pfnConnector) PURE;
	virtual LPVOID FindCntxObj(BYTE cType) PURE;
	virtual LPVOID FindCntxObj(BYTE cType,const IID & riid) PURE;
	virtual VOID DestroyCntxObjs() PURE;
	#define CREATE_SC_OBJECT(SESSION,TYPE,NAME,CLASS) ::new(SESSION->AllocCntxObj(TYPE,NAME,sizeof(CLASS),&CLASS::__Destructor,&CLASS::__Connector)) CLASS
	#define CREATE_SC_STRUCT(SESSION,TYPE,NAME,CLASS) ::new(SESSION->AllocCntxObj(TYPE,NAME,sizeof(CLASS),NULL,NULL)) CLASS
	#define CREATE_SC_BUFFER(SESSION,TYPE,NAME,BUFSIZE) (LPBYTE)SESSION->AllocCntxObj(TYPE,NAME,BUFSIZE,NULL,NULL)
	#define CREATE_SUC_OBJECT(SESSION,TYPE,CLASS) ::new(m_pIServer->AllocUserCntxObj(IServer::UCCATEGORY_SC,TYPE,(LPVOID)((ISession*)SESSION))) CLASS
	#define CREATE_SUC_STRUCT(SESSION,TYPE,CLASS) ::new(m_pIServer->AllocUserCntxObj(IServer::UCCATEGORY_SC,TYPE,(LPVOID)((ISession*)SESSION))) CLASS
	#define CREATE_SUC_BUFFER(SESSION,TYPE) (LPBYTE)m_pIServer->AllocUserCntxObj(IServer::UCCATEGORY_SC,TYPE,(LPVOID)((ISession*)SESSION)))

	// �Ự��������
	virtual const BOOL IsSessionOnline() const PURE;
	virtual const BOOL IsAuthorized() const PURE;
	virtual const BOOL IsPrimary() const PURE;
	virtual const BOOL IsServant() const PURE;
	virtual const BOOL IsPushable() const PURE;
	virtual const BOOL IsEndPointSession() const PURE;

	// �Ự������Ϣ����
	virtual BOOL LockSessionExData(LPBYTE& pData,LPDWORD& pcbUsed,DWORD& cbMax) PURE;
	virtual VOID UnlockSessionExData() PURE;

	// �Ự����
	virtual VOID DestroyTheSession() PURE;

	// ��ȡ����������ID
	virtual BOOL IsConnectRelated() const PURE;
	virtual DWORD GetRelatedConnectID() const PURE;
	virtual IConnect* QueryRelatedConnect() PURE;

	// �Ự����
	virtual VOID LockSession() PURE;
	virtual VOID UnlockSession() PURE;

	// ״̬����
	virtual VOID ModifySS(DWORD dwAddFlags,DWORD dwRemoveFlags,DWORD dwData1,DWORD dwData2) PURE;
	virtual DWORD GetSSFlags() const PURE;
	virtual DWORD GetSSData1() const PURE;
	virtual DWORD GetSSData2() const PURE;

	// ����Ӧ��ͳ������
	virtual VOID CounterAppCall(LPCSTR pszAppCallName) PURE;
	virtual const systm_t GetLastAppCallTime() const PURE;
	virtual const LPCTSTR GetLastAppCallName() const PURE;
	virtual const DWORD GetHisAppCallNum() const PURE;
};



// ����SESSION�ӿ�
// {697364E5-FD3A-4769-90C9-B488A09F3A9B}
static const IID IID_IRoamSession = { 0x697364e5, 0xfd3a, 0x4769, { 0x90, 0xc9, 0xb4, 0x88, 0xa0, 0x9f, 0x3a, 0x9b } };
interface IRoamSession : public IReferObject
{	virtual DWORD GetAPNodeID() const PURE;
	virtual DWORD GetSessionID() const PURE;
	virtual DWORD GetUOrgID() const PURE;
	virtual LPCSTR GetUID() const PURE;
	virtual DWORD GetUserStatus() const PURE;
	virtual DWORD GetUserData1() const PURE;
	virtual DWORD GetUserData2() const PURE;
};


// ���ӽӿ�
// {FF64D81A-ACE6-441d-A473-240A42D93E81}
static const IID IID_IConnect = { 0xff64d81a, 0xace6, 0x441d, { 0xa4, 0x73, 0x24, 0xa, 0x42, 0xd9, 0x3e, 0x81 } };
interface IConnect : public IReferObject
{
	// ������
	virtual IProtocolFamily* GetProtocolFamily() PURE;
	virtual DWORD GetConnectID() const PURE;

	// ���������Ϣ����
	virtual VOID SetProtocolInfo(IProtocolFamily* pIProtocolFamily,WORD wProtocolType,WORD wProtocolVer) PURE;
	virtual VOID SetSourceIp(const IP& Ip) PURE;
	virtual VOID SetMultiplexerMode() PURE;
	virtual VOID SetHAMode(BOOL bHAMode) PURE;
	virtual VOID SetSoftQPC(LONG nSoftQPC) PURE;
	virtual VOID SetSoftCPC(LONG nSoftCPC) PURE;
	virtual VOID SetSoftFPC(LONG nSoftFPC) PURE;

	// ���������Ϣ��ȡ
	virtual BOOL IsProtocolKnown() const PURE;
	virtual IProtocolFamily* GetProtocolFamily() const PURE;
	virtual WORD GetProtocolType() const PURE;
	virtual WORD GetProtocolVer() const PURE;
	virtual IP GetSourceIp() const PURE;
	virtual BOOL IsMultiplexerMode() const PURE;

	// �����Ķ���
	virtual LPVOID AllocCntxObj(BYTE cType,LPCSTR pszName,DWORD cbObject,DESTRUCTOR pfnDestructor,CONNECTOR pfnConnector) PURE;
	virtual LPVOID FindCntxObj(BYTE cType) PURE;
	virtual LPVOID FindCntxObj(BYTE cType,const IID & riid) PURE;
	virtual VOID DestroyCntxObjs() PURE;
	#define CREATE_CC_OBJECT(CONNECT,TYPE,NAME,CLASS) ::new(CONNECT->AllocCntxObj(TYPE,NAME,sizeof(CLASS),&CLASS::__Destructor,&CLASS::__Connector)) CLASS
	#define CREATE_CC_STRUCT(CONNECT,TYPE,NAME,CLASS) ::new(CONNECT->AllocCntxObj(TYPE,NAME,sizeof(CLASS),NULL,NULL)) CLASS
	#define CREATE_CC_BUFFER(CONNECT,TYPE,NAME,BUFSIZE) (LPBYTE)CONNECT->AllocCntxObj(TYPE,NAME,BUFSIZE,NULL,NULL)
	#define CREATE_CUC_OBJECT(CONNECT,TYPE,CLASS) ::new(m_pIServer->AllocUserCntxObj(IServer::UCCATEGORY_CC,TYPE,(LPVOID)((IConnect*)CONNECT))) CLASS
	#define CREATE_CUC_STRUCT(CONNECT,TYPE,CLASS) ::new(m_pIServer->AllocUserCntxObj(IServer::UCCATEGORY_CC,TYPE,(LPVOID)((IConnect*)CONNECT))) CLASS
	#define CREATE_CUC_BUFFER(CONNECT,TYPE) (LPBYTE)m_pIServer->AllocUserCntxObj(IServer::UCCATEGORY_CC,TYPE,(LPVOID)((IConnect*)CONNECT)))

	// �Ự��ش���
	virtual BOOL IsSessionRelated() const PURE;
	virtual DWORD GetRelatedSessionID() const PURE;
	virtual ISession* QueryRelatedSession() PURE;
	virtual ISession* CreateRelatedSession(BOOL bPersistentMode) PURE;
	virtual VOID DestroyRelatedSession() PURE;
	virtual UINT64 GetRelatedSessionGUID() const PURE;

	// ����������
	virtual BOOL CreateStreamWriter(BYTE cType,LPCSTR pszName,WORD wCmdNo,DWORD cbCache) PURE;
	virtual IStreamWriter* GetStreamWriter(BYTE cType) PURE;
};


// �������ӿ�
// {7AF0F422-AEA8-4b7e-96F1-8C57C6B40A9E}
static const IID IID_IStreamWriter = { 0x7af0f422, 0xaea8, 0x4b7e, { 0x96, 0xf1, 0x8c, 0x57, 0xc6, 0xb4, 0xa, 0x9e } };
interface IStreamWriter : public IObject
{	virtual VOID LockUpdate() PURE;
	virtual VOID UnlockUpdate() PURE;
	virtual BOOL Write(LPBYTE pData,DWORD cbData) PURE;
};




// ����ӿ�
// {91232EA6-30DD-4dbb-88D2-8676F3F7BC82}
static const IID IID_IBusiness = { 0x91232ea6, 0x30dd, 0x4dbb, { 0x88, 0xd2, 0x86, 0x76, 0xf3, 0xf7, 0xbc, 0x82 } };
interface IBusiness : public IReferObject
{
	// ���ID����ر�־��ȡ
	virtual DWORD GetConnectID() const PURE;
	virtual DWORD GetBusinessID() const PURE;
	virtual DWORD GetBusinessType() const PURE;
	virtual BOOL IsNetDrive() const PURE;
	virtual BOOL IsPassive() const PURE;

	// ���뻺�����Լ������Ϣ��ȡ
	virtual LPBYTE GetReadBuf() PURE;
	virtual DWORD GetReadBufSize() const PURE;
	virtual DWORD GetReadLength() const PURE;
	virtual BYTE GetReadProtVer() const PURE;
	virtual WORD GetReadCmdNo() const PURE;
	virtual DWORD GetReadFragmentNo() const PURE;

	// �����Ķ���(Э�鴦��ջ)
	virtual LPVOID AllocCntxObj(BYTE cType,LPCSTR pszName,DWORD cbObject,DESTRUCTOR pfnDestructor,CONNECTOR pfnConnector) PURE;
	virtual LPVOID FindCntxObj(BYTE cType) PURE;
	virtual LPVOID FindCntxObj(BYTE cType,const IID & riid) PURE;
	virtual VOID DestroyCntxObjs() PURE;
	#define CREATE_BC_OBJECT(BUSINESS,TYPE,NAME,CLASS) ::new(BUSINESS->AllocCntxObj(TYPE,NAME,sizeof(CLASS),&CLASS::__Destructor,&CLASS::__Connector)) CLASS
	#define CREATE_BC_STRUCT(BUSINESS,TYPE,NAME,CLASS) ::new(BUSINESS->AllocCntxObj(TYPE,NAME,sizeof(CLASS),NULL,NULL)) CLASS
	#define CREATE_BC_BUFFER(BUSINESS,TYPE,NAME,BUFSIZE) (LPBYTE)BUSINESS->AllocCntxObj(TYPE,NAME,BUFSIZE,NULL,NULL)
	#define CREATE_BUC_OBJECT(BUSINESS,TYPE,CLASS) ::new(m_pIServer->AllocUserCntxObj(IServer::UCCATEGORY_BC,TYPE,(LPVOID)((IBusiness*)BUSINESS))) CLASS
	#define CREATE_BUC_STRUCT(BUSINESS,TYPE,CLASS) ::new(m_pIServer->AllocUserCntxObj(IServer::UCCATEGORY_BC,TYPE,(LPVOID)((IBusiness*)BUSINESS))) CLASS
	#define CREATE_BUC_BUFFER(BUSINESS,TYPE) (LPBYTE)m_pIServer->AllocUserCntxObj(IServer::UCCATEGORY_BC,TYPE,(LPVOID)((IBusiness*)BUSINESS)))

	// ���������Ϣ��ȡ�͸���
	virtual DWORD GetTransKey() const PURE;
	virtual WORD GetCmdNo() const PURE;
	virtual LPCSTR GetCmdDesc() const PURE;
	virtual LPVOID GetHandler(const IID & riid) PURE;
	virtual BYTE GetIXFuncType() const PURE;
	virtual WORD GetIXFuncID() const PURE;
	virtual LPVOID GetIXHandler(const IID & riid) PURE;
	virtual VOID RenewTransKey(DWORD dwTransKey) PURE;
	virtual VOID RenewCmdNo(WORD wCmdNo) PURE;
	virtual VOID RenewCmdDesc(LPCSTR pszCmdDesc) PURE;
	virtual VOID SetForceCompressZlib() PURE;
	virtual VOID SetForceEncryptSession() PURE;
	virtual VOID SetForceEncryptBlowfish() PURE;
	virtual VOID SetForceEncryptDes3() PURE;

	// �û�λ�ð汾��Ϣ�Լ��û�������Ϣ
	// ��ο�ISession::SetConnectInfo,ISession::SetUserProfile
	virtual IUser* GetCaller() PURE;
	virtual VOID SetToBeOnline() PURE;
	virtual VOID SetToBeShutSend() PURE;
	virtual VOID SetToBeDisconnect() PURE;

	// Ӧ�𻺳�������
	virtual LPBYTE GetWriteBuf() PURE;
	virtual DWORD GetWriteBufSize() const PURE;	
	virtual DWORD GetWriteLength() const PURE;
	virtual BYTE GetWriteProtVer() const PURE;
	virtual WORD GetWriteCmdNo() const PURE;
	virtual DWORD GetWriteFragmentNo() const PURE;

	// ����Ӧ�𻺳�������ʹ���״̬��ȡ
	virtual VOID SetAnsState(LONG nErrorLevel,LONG nErrorCode,LPCSTR pszState) PURE;
	virtual VOID SetAnsCompleted(WORD wAnsNo,DWORD dwFragmentNo) PURE;
	virtual VOID SetWriteLength(DWORD cbWrite) PURE;
	virtual BOOL IsAnsCompleted() const PURE;
	virtual BOOL IsExceptionAns() const PURE;
	virtual DWORD GetFailCode() const PURE;

	// ������Ϣ
	virtual VOID SetInfo(DWORD cbTotalLength) PURE;
	virtual DWORD GetTotalLength() const PURE;
};





















// SDK��Ϣ
// {2236FAC0-6D2C-4250-BEF3-6D396717A2E7}
static const IID IID_ISDKInfo = { 0x2236fac0, 0x6d2c, 0x4250, { 0xbe, 0xf3, 0x6d, 0x39, 0x67, 0x17, 0xa2, 0xe7 } };
interface ISDKInfo : public IObject
{	virtual DWORD GetSDKVer() const PURE;
};


// ����ģ��
// {FEE61687-CC0F-4337-A5A4-39A4414D39DF}
static const IID IID_ICoreModule = { 0xfee61687, 0xcc0f, 0x4337, { 0xa5, 0xa4, 0x39, 0xa4, 0x41, 0x4d, 0x39, 0xdf } };
interface ICoreModule : public IObject
{	virtual LPCSTR GetName() const PURE;
	virtual BOOL Start() PURE;
	virtual BOOL Ready() PURE;
	virtual VOID Shut() PURE;
	virtual VOID Stop() PURE;
	virtual VOID Final() PURE;
};


// Ӧ�ýӿ�
// {5B944A34-F78A-46ea-B6BF-B59AC953E5C2}
static const IID IID_IServlet= { 0x5b944a34, 0xf78a, 0x46ea, { 0xb6, 0xbf, 0xb5, 0x9a, 0xc9, 0x53, 0xe5, 0xc2 } };
interface IServlet : public IObject
{	virtual LPCSTR GetName() const PURE;
	virtual ICoreModule* GetModule() const PURE;
	virtual VOID AddCaller() PURE;
	virtual LONG GetCallerCnt() PURE;
	virtual BOOL Configure() PURE;
	virtual BOOL Start() PURE;
	virtual BOOL Ready() PURE;
	virtual VOID Shut() PURE;
	virtual VOID Stop() PURE;
	virtual VOID Final() PURE;
};


// ����ӿ�
//		�йط����ʼ��˳��ͽӿڹ�ϵ
//			��������:
//				1.ģ��װ��:		�����̲�������ʵ��,��ģ���ֹ�໥����
//				2.Configure:	��ģ�����ù���,���Բ���ģ��,����������ϵ(DeclareDependency),����ģ������ýӿ�
//				3.Start:		ģ������(���߳�),���Ե�������ģ��(���ܲ���ȫ)
//			���й���:
//				1.ģ������:		ģ�����н׶�,���Զ�ȫ��������а�ȫ����
//			ֹͣ����:
//				1.Shut:			ģ��ر�,�жϸ�ģ�����,�ر�ȫ����̨�߳�,���Ե�������ģ��(���ܲ���ȫ)
//				2.�̻߳���:		����ȫ���ⲿ�߳�,�ж϶�ģ��ĵ���
//				3.Stop:			ģ��ֹͣ(���߳�),��������Դ
//				4.Final:		ģ���ڲ���Դ����
//				5.ģ��ж��:		ģ��ɾ�ж��
// {126EFC39-9EB6-497c-9397-0A0210B0D0CA}
static const IID IID_IService = { 0x126efc39, 0x9eb6, 0x497c, { 0x93, 0x97, 0xa, 0x2, 0x10, 0xb0, 0xd0, 0xca } };
interface IService : public IObject
{
	// ��������
	typedef enum enumSERVICESTYLE
	{	SERVICE_CORE=1,			// ���ķ���(����Ҫ����)
		SERVICE_EXTEND=2,		// ��չ����(��Ҫ����)
		SERVICE_OPTIONAL=4,		// ��ѡ����(�����ò�����)
	} SERVICESTYLE;
	// ����״̬
	typedef enum enumSERVICESTATUS
	{	SERVICEST_NOTRUNNING,	// δ����
		SERVICEST_RUNNING,		// ��������
		SERVICEST_SHUTDOWNING,	// ���ڹر�
		SERVICEST_SHUTDOWN,		// �Ѿ��ر�
		SERVICEST_STOPING,		// ����ֹͣ
		SERVICEST_STOPPED,		// �Ѿ�ֹͣ
	} SERVICESTATUS;
	// ��������ӿ�
	virtual LPCSTR GetName() const PURE;
	virtual ICoreModule* GetModule() const PURE;
	virtual VOID AddCaller() PURE;
	virtual LONG GetCallerCnt() PURE;
	virtual SERVICESTYLE GetServiceStyle() PURE;
	virtual SERVICESTATUS GetServiceStatus() PURE;
	virtual VOID UpdateServiceStatus(SERVICESTATUS eServiceStatus) PURE;
	virtual BOOL Configure() PURE;
	virtual BOOL Start() PURE;
	virtual BOOL Ready() PURE;
	virtual VOID Shut() PURE;
	virtual VOID Stop() PURE;
	virtual VOID Final() PURE;
};


// Э�������
// {5EF022F2-43A6-4480-BC82-154E2DE5F210}
static const GUID IID_IProtocolDiscover = { 0x5ef022f2, 0x43a6, 0x4480, { 0xbc, 0x82, 0x15, 0x4e, 0x2d, 0xe5, 0xf2, 0x10 } };
interface IProtocolDiscover : public IObject
{
	// �õ�ģ��
	virtual ICoreModule* GetModule() const PURE;

	// Э����
	virtual VOID CollectProtocolFamilys() PURE;
	virtual BOOL DetectProtocolInfo(IConnect* pIConnect,LPCBYTE pReq,DWORD cbReq,DWORD& cbPrefix) PURE;
};


// ��������(����:�Զ�·������,��ʽ����,����������,�μ�:�ͻ�������ģ��)
typedef enum enumPUSHINGTYPE
{	PUSHING_UNKNOWN,			// δ֪����

	PUSHING_S2C=100,			// ���������ͻ�������
	PUSHING_SHOUT,				//		����֪ͨ(��ʱ��֧��)
	PUSHING_KICKOUT,			//		�߳�֪ͨ(LPCSTR pszAPFrom,IPV6 IpFrom,systm_t tOccur)
	PUSHING_MSG,				//		��Ϣ֪ͨ(LPCSTR pszMsg)
	PUSHING_IX20,				//		��ͳIXЭ��(BYTE cFuncType,WORD wFuncID,DWORD dwUOrgID,LPCBYTE pData,DWORD cbData)
	PUSHING_TQL,				//		TQLЭ��(LPCBYTE pData,DWORD cbData)
	PUSHING_TJS,				//		TJSЭ��(LPCBYTE pData,DWORD cbData)
	PUSHING_LASTWORD,			//		�������������(LPCSTR pszMsg)
	PUSHING_NOTICE,				//		�������µķ���������(time_t tTime,LPCSTR pszNotice)
	PUSHING_URGENT,				//		�������µķ�֧��������(time_t tTime,DWORD dwUOrgID,LPCSTR pszUrgent)
	PUSHING_INSTRUCT,			//		ָ֪ͨ��(LPCSTR pszInstruct)

	PUSHING_S2S=600,			// ������������������
	PUSHING_USERMANAGE,			//		�û��й�(�޲���)
	PUSHING_CONNRESET,			//		��������(�޲���)
	PUSHING_PERMISSION,			//		�û�Ȩ�޹���
	PUSHING_QOSCTRL,			//		QOS����(���Ӷ���,���������,��������,�߿�������
	PUSHING_SSMANAGE,			//		״̬����(�û�״̬,״̬����123)
	PUSHING_MAXTYPE,			// �������
} PUSHINGTYPE;

// ����ѡ��
typedef enum enumPUSHINGOPTION
{	PUSHING_TO_DEFAULT=0,		// ����Ĭ��ѡ��
	PUSHING_TO_WHERE=0XF,		// Ŀ�������
	PUSHING_TO_LOCAL=1,			// ��������
	PUSHING_TO_CLIENT=2,		// ���͵��ͻ���
	PUSHING_TO_PORTAL=3,		// ���͵����������
	PUSHING_TO_NEIGHBOR=4,		// ���͵��ھӷ�����
} PUSHINGOPTION;



// Э���
// {82A0928C-959F-4cc0-9FA8-5F344CC162C4}
static const IID IID_IProtocolFamily = { 0x82a0928c, 0x959f, 0x4cc0, { 0x9f, 0xa8, 0x5f, 0x34, 0x4c, 0xc1, 0x62, 0xc4 } };
interface IProtocolFamily : public IObject
{
	// ��ȡ����ģ��
	virtual ICoreModule* GetModule() const PURE;

	// ����ģ��ע��ʹ���
	virtual VOID OnFamilyRegistered() PURE;
	virtual VOID OnFamilyToBeReady() PURE;
	virtual BOOL RegisterProtocols(IHandler* pIHandler,LPVOID pProtDefs,LONG nCount,DWORD cbProtDef) PURE;

	// Э�����
	virtual DWORD MessageSeparate(IConnect* pIConnect,LPCBYTE pReq,DWORD cbReq,DWORD& dwTransKey,DWORD& eMsgType,DWORD& dwFragmentNo,DWORD& cbMsgBufNeed,DWORD& dwRelatedBufType,LPBYTE pParserData,DWORD cbMaxParserData,DWORD& cbParserData) const PURE;

	// �����ʼ��
	virtual BPR BusinessInitializeForeign(IConnect* pIConnect,IBusiness* pIBusiness,LPBYTE pParserData,DWORD cbParserData) PURE;
	virtual BPR BusinessInitializeLocal(IConnect* pIConnect,IBusiness* pIBusiness,LPCSTR pszEncoders,va_list argsEncoders) PURE;
	virtual BPR BusinessRenderEncoders(IBusiness* pIBusiness,LPCSTR pszEncoders,...) PURE;
	virtual BPR BusinessRenderEncodersV(IBusiness* pIBusiness,LPCSTR pszEncoders,va_list argsEncoders) PURE;

	// ����׼��
	virtual BPR ParseInfo(IConnect* pIConnect,IBusiness* pIBusiness,LPPROTINFO pProtInfo) PURE;

	// �Ự�ָ�
	virtual UINT64 GetRelatedSessionGUIDToTouch(IConnect* pIConnect,IBusiness* pIBusiness) PURE;

	// Э��Ԥ����ʹ���
	virtual BPR PreExecute(ISession* pISession,IConnect* pIConnect,IBusiness* pIBusiness) PURE;
	virtual BPR Execute(ISession* pISession,IConnect* pIConnect,IBusiness* pIBusiness) PURE;

	// ����Э����װ
	virtual BPR AssembleProtocolError(IConnect* pIConnect,IBusiness* pIBusiness,BOOL bAddPrefix,LONG nFailCode,LPCSTR pszFormat,va_list args) PURE;

	// ���ʹ���
	virtual BPR ForwardPushingLL(ISession* pISession,IConnect* pIConnect,LPCBYTE pOption,DWORD cbOption,LPBYTE pBody,DWORD cbBody,DWORD dwTransKey,WORD wCmdNo,LPCSTR pszCmdDesc,DWORD dwFragmentNo) PURE;
	virtual BPR ForwardPushingFragment(ISession* pISession,IConnect* pIConnect,IBusiness* pIBusiness,LPCBYTE pOption,DWORD cbOption,LPBYTE pBody,DWORD cbBody,DWORD dwFragmentNo) PURE;
	virtual BPR ForwardPushingS2C(ISession* pISession,IConnect* pIConnect,IUser* pIUser,LPCBYTE pOption,DWORD cbOption,LPBYTE pBody,DWORD cbBody,WORD wCmdNo,LPCSTR pszCmdDesc) PURE;
	virtual BPR ForwardPushingBySession(HANDLE hBusinessSpace,ISession* pISession,IConnect* pIConnect,LPCSTR pszDesc,DWORD dwPushingLv,DWORD idPushingType,DWORD dwPushingOption,DWORD_PTR wParam,DWORD_PTR lParam) PURE;
	virtual BPR ForwardPushingByRoute(HANDLE hBusinessSpace,ISession* pISession,IConnect* pIConnect,LPCSTR pszAP,BOOL bUserID,LPVOID pUser,LPCSTR pszDesc,DWORD dwPushingLv,DWORD idPushingType,DWORD dwPushingOption,DWORD_PTR wParam,DWORD_PTR lParam) PURE;
	virtual BPR ForwardPushingByRoam(HANDLE hBusinessSpace,ISession* pISession,IConnect* pIConnect,DWORD idAPNode,DWORD idSession,DWORD dwUOrgID,LPCSTR pszUID,LPCSTR pszDesc,DWORD dwPushingLv,DWORD idPushingType,DWORD dwPushingOption,DWORD_PTR wParam,DWORD_PTR lParam) PURE;
	virtual BPR ForwardPushingByChain(ISession* pISession,IConnect* pIConnect,IBusiness* pIBusinessHost,LPCSTR pszDesc,DWORD dwPushingLv,DWORD idPushingType,DWORD dwPushingOption,DWORD_PTR wParam,DWORD_PTR lParam) PURE;

	// ������������
	virtual VOID WriteBusinessToLogger(ISession* pISession,IConnect* pIConnect,IBusiness* pIBusiness,BOOL bRequest,HANDLE hWriter) PURE;
	virtual VOID WriteBusinessToTracer(ISession* pISession,IConnect* pIConnect,IBusiness* pIBusiness,BOOL bRequest,HANDLE hTraceWnd) PURE;
};


// Э�������
// {B0AF603D-0118-484f-9CE6-A19845292049}
static const IID IID_IProtocolEncoder = { 0xb0af603d, 0x118, 0x484f, { 0x9c, 0xe6, 0xa1, 0x98, 0x45, 0x29, 0x20, 0x49 } };
interface IProtocolEncoder : public IObject
{	virtual LONG EncoderGetLevel() PURE;
	virtual BPR EncoderFormat(ISession* pISession,IConnect* pIConnect,IBusiness* pIBusiness) PURE;
	virtual BPR EncoderRewind(ISession* pISession,IConnect* pIConnect,IBusiness* pIBusiness) PURE;
	virtual BPR EncoderRendering(ISession* pISession,IConnect* pIConnect,IBusiness* pIBusiness) PURE;
};


// Э�������
// {6C11AE6C-7F5C-49f6-9C1F-B598AE9F354B}
static const IID IID_IProtocolDecoder = { 0x6c11ae6c, 0x7f5c, 0x49f6, { 0x9c, 0x1f, 0xb5, 0x98, 0xae, 0x9f, 0x35, 0x4b } };
interface IProtocolDecoder : public IObject
{	virtual LONG DecoderGetLevel() PURE;
	virtual BPR DecoderRendering(ISession* pISession,IConnect* pIConnect,IBusiness* pIBusiness) PURE;
};


// Э�������
// {AD97B734-374F-4cf4-ABA9-05EC75A4B24E}
static const IID IID_IProtocolDebugger = { 0xad97b734, 0x374f, 0x4cf4, { 0xab, 0xa9, 0x5, 0xec, 0x75, 0xa4, 0xb2, 0x4e } };
interface IProtocolDebugger : public IObject
{
};


// Э�鴦��������
// {02F7CDED-B595-4f1b-9D4A-6CEED744C56D}
static const IID IID_IHandler = { 0x2f7cded, 0xb595, 0x4f1b, { 0x9d, 0x4a, 0x6c, 0xee, 0xd7, 0x44, 0xc5, 0x6d } };
interface IHandler : public IObject
{	virtual ICoreModule* GetModule() const PURE;
	virtual BOOL Configure() PURE;
	virtual BOOL AttachServer() PURE;
	virtual BOOL AttachBackstage() PURE;
	virtual VOID DetachServer() PURE;
};


//////////////////////////////////////////////////////////////////////////
// ��Э�鴦���������ʶ����Э�鴦������
#include "ts_defineraw.h"
#include "ts_definehttp.h"
#include "ts_definesip.h"
#include "ts_definefix.h"






// �첽Э�鴦�����ӿ�
// {5E1ACBB6-1F8F-4d91-918B-972DD79D5F72}
static const IID IID_IAsyncHandler = { 0x5e1acbb6, 0x1f8f, 0x4d91, { 0x91, 0x8b, 0x97, 0x2d, 0xd7, 0x9d, 0x5f, 0x72 } };
interface IAsyncHandler : public IObject
{	virtual BOOL GetAsyncBuffer(IBusiness* pIBusiness,LPBYTE& pAnsBody,DWORD& cbAnsBodyMax) PURE;
	virtual BOOL SetAsyncDataReady(IBusiness* pIBusiness,IObject* pIObject) PURE;
};


// �첽���ö���
// {4CA90C71-E0A6-4e65-87A4-EE3FC0618FBC}
static const IID IID_IAsyncObject = { 0x4ca90c71, 0xe0a6, 0x4e65, { 0x87, 0xa4, 0xee, 0x3f, 0xc0, 0x61, 0x8f, 0xbc } };
interface IAsyncObject : public IObject
{	virtual BOOL IsFailed() const PURE;
	virtual LONG GetFailCode() const PURE;
	virtual LPCSTR GetFailInfo() const PURE;
	virtual DWORD GetTotalLength() const PURE;
	virtual DWORD GetFragmentNo() const PURE;
	virtual LPBYTE GetReply() const PURE;
	virtual DWORD GetReplySize() const PURE;
};



// �ɼ��Э�鴦�����ӿ�
//		��ǰ�ӿ�����ʵ������������еı���׼��־���������
//		ʵ��ʵ��:
//			m_pIServer->BusinessToLogger(hLogger,(LPCBYTE)"HANDLE:HELLO\r\n",12);
//			m_pIServer->BusinessToTraceWnd(hTraceWnd,"HANDLE:HELLO\r\n");
// {0D5FC4D1-640D-47f9-8414-DA7BE629E6FB}
static const IID IID_IDbgHandler = { 0xd5fc4d1, 0x640d, 0x47f9, { 0x84, 0x14, 0xda, 0x7b, 0xe6, 0x29, 0xe6, 0xfb } };
interface IDbgHandler : public IObject
{	virtual VOID WriteBusinessToLogger(ISession* pISession,IConnect* pIConnect,IBusiness* pIBusiness,BOOL bRequest,HANDLE hLogger) PURE;
	virtual VOID WriteBusinessToTracer(ISession* pISession,IConnect* pIConnect,IBusiness* pIBusiness,BOOL bRequest,HANDLE hTraceWnd) PURE;
};



// ���ʹ�����
// {58F4CBFE-98FA-49be-B3A6-88BAE31FF32B}
static const IID IID_IPushingHandler = { 0x58f4cbfe, 0x98fa, 0x49be, { 0xb3, 0xa6, 0x88, 0xba, 0xe3, 0x1f, 0xf3, 0x2b } };
interface IPushingHandler : public IObject
{	virtual BPR OnPushing(ISession* pISession,IConnect* pIConnect,IBusiness* pIBusinessHost,DWORD dwPushingLv,DWORD idPushingType,DWORD dwPushingOption,LPBYTE pSequence,DWORD cbSequence) PURE;
};



#include "ts_easyuse.inl"


#define USE_DEPRECATION
#ifdef USE_DEPRECATION
	#define INMServer IServer
	#define INMSession ISession
	#define INMConnect IConnect
	#define INMBusiness IBusiness
#endif

#pragma pack()
#endif
