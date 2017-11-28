//////////////////////////////////////////////////////////////////////////
// ��������:2006/07/20
// ����˵��:TC50/�ӿ�DLL(FEM/FEB)������ؽӿ�
//          TC50���ṩ����Ҫ�ӿڰ������¼���
//          (1).�ӿ���Ϣ��ѯ
//				FEM_GetInformation
//				FEM_GetSummaryCols
//          (2).������ؽӿ�
//				FEM_GetOptionSummary
//			    FEM_ShowOptionDialog
//          (3).�ӿڳ�ʼ���Լ��˳�����
//				FEM_InitInst
//				FEM_ExitInst
//          (4).�ӿ���������(��ʼ������Ч)
//				FEM_GetDicts
//				FEM_BusinessProc
//          (5).״̬��غ���(��ʼ������Ч)
//				FEM_IsBranchAvailable
//				FEM_GetStatusSummary
// �����¼:
//            2006/07/21 ֧��TC50Э��
//            2006/07/25 �������
//            2008/03/11 ��ֲ��linux
#ifndef __TC_FEMDEFINE__H__
#define __TC_FEMDEFINE__H__



//------------------------------------------------------------------------
// Part.III �ӿڶ���
//------------------------------------------------------------------------
// ǿ��1�ֽڶ���
#pragma pack(1)


	// ȡ�ð汾��Ϣ
	typedef struct tagFEMINFO
	{	CHAR m_szFileName[33];								// �����ļ���
		CHAR m_szName[33];									// �ӿ����� 
		FLOAT m_fVersion;									// �ӿڰ汾
		DWORD m_dwDate;										// ��������
		DWORD m_bHasPublicOption:1;							// �Ƿ��й������öԻ���
		DWORD m_bHasBranchOption:1;							// �Ƿ���Ӫҵ�����öԻ���
		DWORD m_bHasSyncProc:1;								// �Ƿ�߱�ͬ����������
		DWORD m_bHasAsyncProc:1;							// �Ƿ�߱��첽��������
		DWORD m_bHasTradeCcf:1;								// �Ƿ���ڽ�������
		DWORD m_abReserved:27;								// ����λ,����ȫ��
		BYTE  m_szReserved[64];								// �����ֽ�,����ȫ��
	} FEMINFO,*LPFEMINFO;
	typedef VOID (* FEM_GETINFORMATION)(LPFEMINFO lpFEMInfo);


	// ȡժҪ�нṹ����(��������ժҪ�Լ�״̬ժҪ)
	enum enumFEMSUMMARYTYPE
	{	FEM_SUMMARY_TYPE_OPTION,							// ����ժҪ,����ѡ����ʾ
		FEM_SUMMARY_TYPE_STATUS,							// ״̬ժҪ,����״̬��ʾ
	};
	#define FEM_SUMMARY_TYPE_GTDZ				0			// ��̨��ַ(����ժҪ)
	#define FEM_SUMMARY_TYPE_GYH				1			// ��Ա��(����ժҪ)
	#define FEM_SUMMARY_TYPE_LOAD				2			// ���ر���(״̬ժҪ)
	#define FEM_SUMMARY_TYPE_FZYWS				3			// �������ҵ����(״̬ժҪ)
	#define FEM_SUMMARY_TYPE_AVGRESPONSETICK	4			// ��һ����ҵ��ƽ����Ӧʱ��(TICK��)(״̬ժҪ)
	typedef struct tagFEMSUMMARY
	{	DWORD  m_dwColType;									// ������
		CHAR  m_szColName[33];								// ������
		DWORD  m_dwColWidth;								// �п��
	} FEMSUMMARY,*LPFEMSUMMARY;
	typedef DWORD (* FEM_GETSUMMARYCOLS)(DWORD dwSummaryType,LPFEMSUMMARY lpFEMSummary,DWORD dwMaxCount);


	// ȡ������ժҪ��
	typedef VOID (* FEM_GETOPTIONSUMMARY)(LPCSTR lpszFilePath,LPCSTR lpszBranchSection,DWORD dwColType,DWORD dwMaxSize,LPSTR lpszSummary);



	// ��ʾ���������޸ĶԻ���
	typedef BOOL (* FEM_SHOWOPTIONDIALOG)(HWND hParent,LPCSTR lpszFilePath,LPCSTR lpszSection,BOOL bPublicOption);


	// ������ȫ�ֳ�ʼ��
	typedef struct tagFEMBRANCHINFO
	{	DWORD   m_dwBranchID;								// Ӫҵ��ID
		DWORD	m_dwMinThreadNum;							// ��Ӫҵ����Ӧ����С�߳���
		DWORD	m_dwMaxThreadNum;							// ��Ӫҵ����Ӧ������߳���
		CHAR	m_szBranchSection[MAX_PATH];				// Ӫҵ�����ý�
	} FEMBRANCHINFO,*LPFEMBRANCHINFO;
	typedef struct tagFEMPARAM
	{	DWORD				m_dwReserved1;					// �Ƿ����첽��ʽ����
		LPVOID				m_pfnDataIO;					// ����IO�ص�����
		DWORD_PTR			m_dwIoParam;					// ����IO�ص�����
		DWORD				m_dwMaxAnsBufLen;				// ���Ӧ�𻺳�������
		DWORD				m_dwBranchNum;					// Ӫҵ����
		CHAR				m_szOptionFile[MAX_PATH];		// �����ļ�
		CHAR				m_szPublicSection[MAX_PATH];	// �������ý�
		LPFEMBRANCHINFO		m_lpBranchInfos;				// Ӫҵ������
		BYTE				m_szReserved2[64];				// �����ֽ�,ȫ��
	} FEMPARAM,*LPFEMPARAM;
	typedef BOOL (* FEM_INITINST)(LPFEMPARAM lpFEMParam);


	// ������ȫ�ֹرպ���
	typedef VOID (* FEM_EXITINST)();


	// ȡ�������ֵ�
	enum enumDICTTYPE
	{	DICTTYPE_SIMPLE,									// ���ֵ�,��Ҫ���ڵ�¼����
		DICTTYPE_FULL,										// �����ֵ�,��Ҫ����ҵ����
	};
	typedef DWORD (* FEM_GETDICTS)(DWORD dwType,DWORD dwMaxSize,LPBYTE lpDict);


	// ���������
	// ��������>=0,����ɹ�,����������Ӧ����ͻ�
	// ��������<0,����ʧ��,�ͻ����յ��쳣����֪ͨ,�������֪ͨ�ͻ�
	// DLL�ķ��ط�ΧΪ-10000<=RETCODE<=+10000
	enum enumBUSINESSPROCRET
	{	BCRET_PROC_PENDING=-2,							// DLL����ȴ��첽���
		BCRET_PROC_FAIL=-1,								// DLL����ʧ��
		BCRET_PROC_SUCCESS=0,							// DLL����ɹ�
	};
	// �ṹ����
	typedef struct tagFEMFUNCCNT
	{	DWORD	m_cbFuncCnt;							// �ṹ����
		HANDLE	m_hBusiness;							// ������
		DWORD	m_dwRawIP;								// �ͻ������ӵ�ַ(������)
		LPCSTR	m_pszUOrg;								// ��ǰ����Ļ���
		LPCSTR	m_pszUID;								// ��ǰ������ʺ�
		LPDWORD	m_pdwInApiTime;							// ��API�����ĵ�ʱ��(����)
		WORD	m_wReqNo;								// ��ǰ�����Э���(��ʼ����д)
		LPCSTR	m_pszCmdDesc;							// ��ǰ���������(��ʼ����д)
		LPCSTR	m_pszClientUOrg;						// ��ǰ����Ŀͻ�����(���ܲ�����,������Ϊϵͳ����)
		LPCSTR	m_pszClientUID;							// ��ǰ����Ŀͻ��ʺ�(���ܲ�����,������Ϊϵͳ����)
		DWORD	m_idSession;							// ��ǰ����ĻỰID(ԭ�ỰID)
		#if defined(ASE_BACKWARD_COMPATIBILITY)
		DWORD	m_idBussiness;							// ��ǰ���������ID
		#else
		DWORD	m_idBusiness;							// ��ǰ���������ID
		#endif
		DWORD	m_dwTransKey;							// ��ǰ����Ĵ����
		WORD	m_wClientType;							// �ͻ�������
		DWORD	m_dwClientVer;							// �ͻ��˰汾
		IPV4	m_ClientIP;								// �ͻ�IP
		MAC		m_ClientMac;							// �ͻ�MAC
		DWORD	m_bV6OrMoreHigh:1;						// �ͻ����Ƿ���V6����߰汾(>=5.12.0180)
		DWORD	m_bBkgdConn:1;							// �ͻ����Ƿ��Ǻ�̨����(>=5.12.0188)
		DWORD	m_bWapConn:1;							// �ͻ����Ƿ�WAP�ͻ���
		DWORD	m_bWantGTSessionID:1;					// �Ƿ���Ҫ��̨SESSIONID
		DWORD	m_dwReserved:28;						// �����ֶ�
		DWORD	m_dwGTSessionID;						// ��̨SESSIONID
	} FEMFUNCCNT,*LPFEMFUNCCNT;
	typedef LONG (* FEM_BUSINESSPROC)(PVOID pFuncCnt,DWORD dwBranchID,LPFUNCHDR lpFuncHdr,
		LPFUNCBDY lpFuncReq,LPFUNCBDY lpFuncAns);


	// ȡ��ǰӪҵ��״̬(��̨״̬)
	typedef BOOL (* FEM_ISBRANCHAVAILABLE)(DWORD dwBranchID);


	// ȡ��״̬ժҪ��
	typedef VOID (* FEM_GETSTATUSSUMMARY)(DWORD dwBranchID,DWORD dwColType,DWORD dwMaxSize,LPSTR lpszSummary);


	// ֪ͨ�ӿ�״̬
	enum enumFEMNCODE
	{	NC_CONNECTLOST,					// �ͻ��Ͽ�����(�Ѿ���֤�ͻ����)
		NC_UNAMEDCLOSED,				// δ֪���ӶϿ�(δ��֤���)
		NC_CONNECTAUDIT,				// �ͻ���������(�Ѿ���֤�ͻ����,�Ǻ�̨����)
	};
	typedef BOOL (* FEM_STATENOTIFY)(DWORD idSession,DWORD dwSessionData,DWORD dwBranchID,LPCSTR pszClientUID,DWORD dwNotifyCode,DWORD dwParam);

#pragma pack()
#endif
