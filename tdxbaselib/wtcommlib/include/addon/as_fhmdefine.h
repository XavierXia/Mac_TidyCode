//////////////////////////////////////////////////////////////////////////
// ��������:2006/07/20
// ����˵��:
// �����¼:
#ifndef __AS_FHMDEFINE__H__
#define __AS_FHMDEFINE__H__
#pragma pack(1)





//------------------------------------------------------------------------
// Part.I �������ݽṹ����
//------------------------------------------------------------------------

// ���ݴ洢���
typedef struct tagFHMSTORAGEAREA{}* HFHMSTORAGEAREA;
typedef struct tagFHMSQLCONNECT{}* HFHMSQLCONNECT;
// ���ݴ洢����
typedef struct tagFHMSQLCONNECTDATA
{	DWORD	m_cbData;				// ���ݽṹ��С
	BOOL	m_bIsPrimary;			// �Ƿ���������
	LPVOID	m_pAdoDatabase;			// ���ݿ�����
} FHMSQLCONNECTDATA,*LPFHMSQLCONNECTDATA;





//------------------------------------------------------------------------
// Part.II ���ݻص�
//------------------------------------------------------------------------

// �ص��������Ͷ���
//      dwIoType									wParam				lParam					dwReserved	Result
#define FHMIO_ALLOCSQLCONNECT			1000	//	(HFHMSTORAGEAREA)	(�Ƿ��Զ�ѡ��)			N/A			(HFHMSQLCONNECT)
#define FHMIO_GETSQLCONNECTDATA			1001	//	(HFHMSQLCONNECT)	(LPFHMSQLCONNECTDATA)	N/A			(BOOL)
#define FHMIO_DROPSQLCONNECT			1002	//	(HFHMSQLCONNECT)	N/A						N/A			(BOOL)
#define FHMIO_FREESQLCONNECT			1003	//	(HFHMSQLCONNECT)	N/A						N/A			(BOOL)

// ����IO�ص�
typedef LONG (CALLBACK* PFHMDATAIO)(DWORD dwIoType,DWORD wParam,DWORD lParam,DWORD_PTR dwIoParam,DWORD dwReserved);






//------------------------------------------------------------------------
// Part.III �ӿڶ���
//------------------------------------------------------------------------

// �ӿڳ�ʼ������
typedef struct tagFHMPARAM
{	DWORD			m_cbFHMParam;					// ������С
	CHAR			m_szQsId[QSID_SIZE];			// ȯ�̱�ʶ
	CHAR			m_szHomeDir[MAX_PATH];			// ������·��
	CHAR			m_szOptionFile[MAX_PATH];		// �����ļ�·��
	PFHMDATAIO		m_pfnDataIo;					// ����IO�ص�����
	DWORD_PTR		m_dwIoParam;					// ����IO�ص�����
	BYTE			m_szReserved2[64];				// �����ֽ�,ȫ��
} FHMPARAM,*LPFHMPARAM;
typedef BOOL (* FHM_INITIALIZEHANDLER)(LPFHMPARAM pFHMParam);

// �ӿ��ͷź���
typedef BOOL (* FHM_UNINITIALIZEHANDLER)();

// �ֵ��ȡ
typedef DWORD (* FHM_GETDICTIONARY)(LPBYTE pBuffer,DWORD cbBuffer);

// ���������
// ��������>=0,����ɹ�,����������Ӧ����ͻ�
// ��������<0,����ʧ��,�ͻ����յ��쳣����֪ͨ,�������֪ͨ�ͻ�
// DLL�ķ��ط�ΧΪ-10000<=RETCODE<=+10000
typedef enum enumFHMFUNCHANDLERET
{	FHM_FHR_FAIL=-1,								// DLL����ʧ��
	FHM_FHR_SUCCESS=0,								// DLL����ɹ�
} FHMFUNCHANDLERET;
typedef struct tagFHMFUNCCNT
{	DWORD			m_cbFuncCnt;					// �ṹ����
	HFHMSTORAGEAREA	m_hStorageArea;					// �洢����
} FHMFUNCCNT,*LPFHMFUNCCNT;
typedef LONG (* FHM_FUNCHANDLER)(LPFHMFUNCCNT lpFuncCnt,LPFUNCHDR lpFuncHdr,LPFUNCBDY lpFuncReq,LPFUNCBDY lpFuncAns,UINT nMaxAnsBodyLen);

// ���ݿ�ά��
typedef VOID (* FHM_MAINTENANCE)(HFHMSTORAGEAREA hStorageArea);




#pragma pack()
#endif

