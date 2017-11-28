#ifndef __TC_COMMON__H__
#define __TC_COMMON__H__
#pragma pack(1)

#ifdef ASELIB_API
	// �ƻ�����������Ϣ
	typedef LONG (CALLBACK* PTCFUNC)(DWORD_PTR dwTaskData,DWORD_PTR dwTaskId);
	typedef struct ASELIB_API tagTCTASKSETINFO
	{	DWORD			m_tBeginTime;			// �ƻ�����ʼִ��ʱ��
		DWORD			m_dwTaskData;			// �ƻ���������
		DWORD			m_dwPeriod;				// ִ������
		DWORD			m_bSkipOnBusy;			// �Ƿ��ڷ�æ��ʱ�����
		PTCFUNC			m_pfnTaskFunc;			// ����ص�����
		tagTCTASKSETINFO()
		{	memset(this,0,sizeof(tagTCTASKSETINFO));
		}
	} TCTASKSETINFO,*LPTCTASKSETINFO;
	// ԭʼ����
	typedef LONG (CALLBACK* PTCRAWCALLFN)(PVOID pFuncCnt,LPBYTE lpIn,DWORD cbIn,LPBYTE lpOut,DWORD cbOutMax,DWORD& cbOut);
	typedef struct ASELIB_API tagTCRAWCALL
	{	WORD		   m_wReqNo;				// Э���
		LPCSTR		   m_lpszCmdDesc;			// Э������
		BYTE		   m_cThreadType;			// �߳�����: 0-ͨѶ�߳� 1-�����߳� 2-�����߳�
		BYTE		   m_cWriteBufType;			// д���������: 0-С�Ͱ���С 1-�еȰ���С 2-���Ͱ���С 3-�޴����С 100-Ĭ�ϴ�С
		BYTE		   m_cEncrpyted;			// �Ƿ�Ҫ����� 0-��Ҫ����� 1-�������
		WORD		   m_wMinReqLen;			// ��С�������С(�ֽ�)
		WORD		   m_wMinAnsLen;			// ��СӦ�����С(�ֽ�)
		PTCRAWCALLFN  m_pfnRawCallFn;			// ���ܻص�����
	} TCRAWCALL,*LPTCRAWCALL;

	// �����û�����
	typedef struct ASELIB_API tagLOCALUINFO
	{	DWORD		   m_dwSessionID;			// �ỰID
		DWORD		   m_dwBranchID;			// Ӫҵ��ID
 		CHAR		   m_szKHH[UID_SIZE];		// �ͻ�����Ϣ
		DWORD		   m_dwData;				// ��������
	} LOCALUINFO,*LPLOCALUINFO;
	// ȫ���û�����
	typedef struct ASELIB_API tagGLOBALUINFO
	{	WORD		   m_wUOrg;					// Ӫҵ��ID(ȫ��ģʽ)
		CHAR		   m_szUID[UID_GSIZE];		// �ͻ�����Ϣ(ȫ��ģʽ)
		BYTE		   m_cServId;				// ������ID(0XFFΪ��)
	} GLOBALUINFO,*LPGLOBALUINFO;

	// ֪ͨ��Ϣ
	typedef struct ASELIB_API tagTCNOTIFYINFO
	{	DWORD		   m_dwBranchID;			// Ӫҵ��ID
		CHAR		   m_szKHH[MAX_PATH];		// �ͻ�����Ϣ
		BYTE		   m_cFuncType;				// ��������
		WORD		   m_wFuncID;				// ���ܺ�
		DWORD		   m_dwReserved;			// �����ֶ�
	} TCNOTIFYINFO,*LPTCNOTIFYINFO;
	// ֪ͨ��Ϣ(ԭʼ��ʽ)
	typedef struct ASELIB_API tagTCRAWNOTIFYINFO
	{	DWORD		   m_dwSessionID;			// �ỰID
 		DWORD		   m_dwBranchID;			// Ӫҵ��ID
 		CHAR		   m_szKHH[MAX_PATH];		// �ͻ�����Ϣ
		BYTE		   m_cFuncType;				// ��������
		WORD		   m_wFuncID;				// ���ܺ�
		DWORD		   m_dwReserved;			// �����ֶ�
	} RAWTCNOTIFYINFO,*LPTCRAWNOTIFYINFO;
	// ת����Ϣ
	typedef struct ASELIB_API tagTCRELAYINFO
	{	DWORD		   m_dwSessionID;			// Դ�ỰID(ȷ����Ϣʱ������д)
		WORD		   m_wUOrg;					// Ӫҵ��ID(ȫ��ģʽ)
		CHAR		   m_szUID[UID_GSIZE];		// �ͻ�����Ϣ(ȫ��ģʽ)
		BYTE		   m_cFuncType;				// ��������
		WORD		   m_wFuncID;				// ���ܺ�
		BYTE		   m_cFlags;				// ��־λ
		DWORD		   m_dwReserved;			// ����
	} TCRELAYINFO,*LPTCRELAYINFO;
#endif

#ifndef RELAY_FLAGS
#define RELAY_FLAGS
	#define RELAYF_USECOUNTER	0X01			// ʹ���м̼�����
	#define RELAYF_ADDCOUNTER	0X02			// �м̼���������(����:���ӽ����߼��� ȷ��:�������߼���)
	#define RELAYF_COMPRESS		0X04			// ǿ��ʹ��ѹ��ģʽ
	#define RELAYF_ENCRYPTED	0X08			// ǿ��ʹ�ü���ģʽ
#endif

// �ص��������Ͷ���
//		nDataType							lpCode				lpData			cbData			dwReserved		Result		����
#define SYSTEM_INFO_DATA		200		//	N/A					(LPCSTR)		N/A				N/A				0			��ʾϵͳ��Ϣ,��ʾ��Ϣ����,��\0��β
#define SYSTEM_ERROR_DATA		201		//	N/A					(LPCSTR)		N/A				N/A				0			��ʾ������Ϣ,��ʾ��Ϣ����,��\0��β
#define FEM_INFO_LOG			203		//	N/A					��־����		��־����		LOWORD=���ܺ�	0			д��ҵ����־(����)
#define FEM_ERROR_LOG			204		// 	N/A					��־����		��־����		LOWORD=���ܺ�	0			д��ҵ����־(����)
#define FEM_INSERTTASK_DATA		205		//	(LPTASKSETINFO)		(LPDWORD)����ID	sizeof(DWORD)	N/A				0			����ƻ�����
#define FEM_REMOVETASK_DATA		206		//	N/A					(DWORD)����ID	N/A				N/A				0			ɾ���ƻ�����

#define FEM_REGISTERRAWCALL		207		//  N/A					(LPTCRAWCALL)	����������		N/A				0			�Ǽ�ԭʼ������ڵ�ַ(��ԭ��ģʽ֧��)

#define FEM_GETMEMPOOLUSED		208		//  N/A					(LPLONG)����	sizeof(LONG)	N/A				0			��ȡ��ǰ�ڴ��ʵ��
#define FEM_GETMEMPOOLMAX		209		//  N/A					(LPLONG)����	sizeof(LONG)	N/A				0			��ȡ��ǰ�ڴ�����

#define FEM_FINBUSINESSASYNC	210		//  N/A					(HANDLE)���	BCRET_PROC_XX	N/A				0			�����첽����(��ԭ��ģʽ֧��)

#define FEM_GETCASTPOOLUSED		211		//  N/A					(LPLONG)����	sizeof(LONG)	N/A				0			��ȡ��ǰ�㲥�ڴ��ʵ��
#define FEM_GETCASTPOOLALERT	212		//  N/A					(LPLONG)����	sizeof(LONG)	N/A				0			��ȡ��ǰ�㲥�ڴ�ؾ���
#define FEM_GETCASTPOOLMAX		213		//  N/A					(LPLONG)���	sizeof(LONG)	N/A				0			��ȡ��ǰ�㲥�ڴ�����

#define FEM_GETRELAYCOUNTERS	214		//  N/A					(LPLOCALUINFO)	����������		N/A				0			��ȡָ��(����)�û��м̼�����
#define FEM_RSTRELAYCOUNTERS	215		//  N/A					(LPLOCALUINFO)	����������		N/A				0			����ָ��(����)�û��м̼�����

#define FEM_GETLOCALCONNS		216		//  N/A					(LPLOCALUINFO)	����������		N/A				ʵ������	��ȡ��վ������Ϣ
#define FEM_GETLOCALNEWCONNS	217		//  (CONNECTID)			(LPLOCALUINFO)	����������		N/A				ʵ������	��ȡ������վ������Ϣ
#define FEM_GETLOCALUSERS		218		//  N/A					(LPLOCALUINFO)	����������		N/A				ʵ������	��ȡ��վ�û���Ϣ
#define FEM_GETLOCALNEWUSERS	219		//  (CONNECTID)			(LPLOCALUINFO)	����������		N/A				ʵ������	��ȡ������վ�û���Ϣ

#define FEM_GETGLOBALUSERS		220		//  N/A					(LPGLOBALUINFO)	����������		N/A				ʵ������	��ȡȫ���û���Ϣ(�Ǻ�̨����)
#define FEM_GETGLOBALUSERSTATE	221		//  N/A					(LPGLOBALUINFO)	����������		N/A				��¼����	��ȡȫ���û�״̬(�Ǻ�̨����)

#define	FEM_GETHSGPHQDATA1		101		//	��Ʊ����			(LPHQSCINFO)	����������		LOWORD=�г�+1	�ɹ�����0	��ȡ��������
#define FEM_NOTIFY				102		//	(LPTCNOTIFYINFO)	֪ͨ����		֪ͨ���ݳ���	N/A				0			����֪ͨ����
#define FEM_GETHSGPHQDATA2		103		//	��Ʊ����			(LPHQSCINFO2)	����������		LOWORD=�г�+1	�ɹ�����0	��ȡ��������
#define FEM_GETHQSTATE			104		//	N/A					(LPBOOL)		N/A				N/A				0			��ȡ��������״̬
#define FEM_GETHKGPHQDATA		105		//	��Ʊ����			(LPHKHQINFO)	����������		LOWORD=�г�		�ɹ�����0	��ȡ�۹���������
#define FEM_GETHKHQSTATE		106		//	N/A					(LPBOOL)		N/A				N/A				0			��ȡ�۹���������״̬
#define FEM_GETSTOCKENUNAME		107		//	��Ʊ����			Ӣ����������	����������		N/A				�ɹ�����0	��ȡ֤ȯӢ������
#define FEM_RAWNOTIFY			108		//	(LPTCRAWNOTIFYINFO)֪ͨ����		֪ͨ���ݳ���		N/A				�ɹ�����0	����֪ͨ����
#define FEM_MONITOR				109		//  N/A					(LPFEMMONITOR)	����������		N/A				0			���ͳһ�����Ϣ
#define	FEM_GETL2L1HQDATA		110		//	��Ʊ����			(LPHQSCINFO)	����������		LOWORD=�г�+1	�ɹ�����0	��ȡ��������(5���̿�,���ȸ�������)
#define FEM_GETL2GPHQDATA		111		//	��Ʊ����			(LPL2HQINFO)	����������		LOWORD=�г�+1	�ɹ�����0	��ȡ������������(10���̿�,��������)
#define FEM_GETL2HQSTATE		112		//	N/A					(LPBOOL)		N/A				N/A				0			��ȡ������������״̬

#define FEM_RELAY				113		//  (LPTCRELAYINFO)	�м�����		�м����ݳ���		N/A				0			�����м�����

// ���ݱ���
#define	GPHQ_DATA				FEM_GETHSGPHQDATA1
#define NOTIFY_DATA				FEM_NOTIFY
#define GPHQ2_DATA				FEM_GETHSGPHQDATA2




// ������Ϣ
#define IOERR_NOERROR				(0)			// �޴���

#define IOERR_INVALID_TYPE			(-1)		// �Ƿ���������
#define IOERR_INVALID_PARAM			(-2)		// ��Ч����
#define IOERR_INVALID_SYMBOL		(-3)		// ��Ч��Ʒ
#define IOERR_SVC_NOT_RUN			(-4)		// ����δ����
#define IOERR_NOT_SUPPORT			(-5)		// �����ݲ�֧��
#define IOERR_BUSINESS_FATAL		(-6)		// �����ڲ�����
#define IOERR_CONNECT_MISSING		(-7)		// �����Ѿ��ر�

#define IOERR_INVALID_BUSINESS		(-10)		// ��Ч����

#define IOERR_CAST_NO_CFG			(-20)		// ����������
#define IOERR_CAST_USERNOTONLINE	(-21)		// �û�������
#define IOERR_CAST_USER_NOCASTABLE	(-22)		// �û�δ��¼���Ǻ�̨����(���տͻ�������ʱ��Ч)
#define IOERR_CAST_USERNOTMATCH		(-23)		// �û���ƥ��(���տͻ�������ʱ��Ч)
#define IOERR_CAST_TOOMUCH			(-24)		// ̫���������Ϣ(���տͻ�������ʱ��Ч)
#define IOERR_CAST_LOWLEVELERROR	(-25)		// ����ʱ�ͼ�����
#define IOERR_CAST_NOMATCHEDUSER	(-26)		// ������Ҫ����û�����
#define IOERR_CAST_PACKERROR		(-27)		// �������


#define IOERR_RELAY_NOEXCHANGE		(-40)		// ���ý�ֹ��Ϣ����
#define IOERR_RELAY_CONNNOTREADY	(-41)		// ����Э��δ����
#define IOERR_RELAY_REQTOOLONG		(-42)		// ���󻺳���̫��
#define IOERR_RELAY_PACKERROR		(-43)		// �м̷������
#define IOERR_RELAY_BADSETTING		(-50)		// ���ô���

// ���ݻص�����
// ����:	lpCode		��Ʊ����
//			nDataType	��������,Ŀǰֻ֧�ֹ�Ʊ����
//			lpData		�������ݻ�����
//			cbData		���ݻ�������С
//			dwIoParam	IO����,��ʼ����ʱ����
//			dwReserved	�����ֶ�(����ȫ��)
// ����:	(LONG)		>=0�ɹ�,<0ʧ��,���ش������
typedef LONG (CALLBACK* PFEMDATAIO)(LPSTR lpszCode,SHORT nDataType,LPVOID lpData,
	DWORD cbData,DWORD_PTR dwIoParam,DWORD dwReserved);
typedef PFEMDATAIO PDATAIOFUNC;


#pragma pack()
#endif
