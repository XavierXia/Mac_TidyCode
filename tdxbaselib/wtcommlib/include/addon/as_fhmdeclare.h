//////////////////////////////////////////////////////////////////////////
// ��������:2008/08/12
// ����˵��:��׼/�û�FHM/FHBʵ������
// �����¼:
#ifndef __AS_FHMDECLARE__H__
#define __AS_FHMDECLARE__H__
#pragma pack(1)

#ifdef WIN32


//------------------------------------------------------------------------
// Part.I ���ܴ���ģ�麯������
//------------------------------------------------------------------------
extern "C"
{
	//////////////////////////////////////////////////////////////////////////
	// ����ģ���ʼ��
	// ����:
	//      pfnFHMDataIo[IN]			����IO�ص���Ϣ
	// ����:
	//      �Ƿ�ɹ�
	DLLEXPORT BOOL FHM_InitializeHandler(LPFHMPARAM pFHMParam);




	//////////////////////////////////////////////////////////////////////////
	// ����ģ�������ͷ�
	// ����:
	// ����:
	//      �Ƿ�ɹ�
	DLLEXPORT BOOL FHM_UninitializeHandler();




	//////////////////////////////////////////////////////////////////////////
	// ��ȡ�����ֵ�
	// ����:
	//		LPBYTE pBuffer				�ֵ仺����
	//		DWORD cbBuffer				�ֵ仺��������
	// ����:
	//      �ֶγ���
	DLLEXPORT DWORD FHM_GetDictionary(LPBYTE pBuffer,DWORD cbBuffer);




	//////////////////////////////////////////////////////////////////////////
	// ���ܴ���
	// ����:
	//		LPFHMFUNCCNT lpFuncCnt		����������
	//		LPFUNCHDR lpFuncHdr			����ͷ��
	//		LPFUNCBDY lpFuncReq			��������
	//		LPFUNCBDY lpFuncAns			Ӧ������
	//		UINT nMaxAnsBodyLen		
	// ����:
	//      ����״̬(FHM_FHR_XXXX)
	DLLEXPORT LONG FHM_FuncHandler(LPFHMFUNCCNT lpFuncCnt,LPFUNCHDR lpFuncHdr,LPFUNCBDY lpFuncReq,LPFUNCBDY lpFuncAns,UINT nMaxAnsBodyLen);

	

	//////////////////////////////////////////////////////////////////////////
	// ����ά��
	// ����:
	//		HFHMSTORAGEAREA hStorageArea	�洢����
	//		HFHMSQLCONNECT hSqlConnect		���ݿ�����
	// ����:
	//      �Ƿ�ɹ�
	DLLEXPORT VOID FHM_Maintenance(HFHMSTORAGEAREA hStorageArea);


}




//------------------------------------------------------------------------
// Part.II ���ܴ���ģ�����
//------------------------------------------------------------------------
class CADODatabase;
template<class IMPL_TYPE>
class CFuncHandlerBase
{
public:
	CFuncHandlerBase(LPCSTR pszTime)
		: m_Dict(pszTime)
	{	memset(&m_FHMParam,0,size_of(m_FHMParam));
	}
	virtual~CFuncHandlerBase()
	{
	}
public:
	virtual BOOL InitializeHandler(LPFHMPARAM pFHMParam)
	{	VERIFY(pFHMParam!=NULL);
		VERIFY(pFHMParam->m_pfnDataIo!=NULL);
		m_FHMParam=*pFHMParam;
		return TRUE;
	}
	virtual BOOL UninitializeHandler()
	{	memset(&m_FHMParam,0,size_of(m_FHMParam));
		return TRUE;
	}
	virtual DWORD GetDictionary(LPBYTE pBuffer,DWORD cbBuffer)
	{	DWORD cbDict=cbBuffer;
		if(!m_Dict.ExportCommon(pBuffer,cbDict)) return 0;
		return cbDict;
	}
	// ���ݴ������
	virtual LONG FuncHandler(LPFHMFUNCCNT lpFuncCnt,LPFUNCHDR lpFuncHdr,LPFUNCBDY lpFuncReq,LPFUNCBDY lpFuncAns,UINT nMaxAnsBodyLen)
	{	VERIFY(lpFuncCnt!=NULL);
		VERIFY(lpFuncHdr!=NULL);
		VERIFY(lpFuncReq!=NULL);
		VERIFY(lpFuncAns!=NULL);
		// ��ʼ�����ز����������Ӧ��ṹ
		lpFuncAns->m_dwSize=0;
		// ��������ṹ
		CWtCommon Req;
		Req.SetDict(&m_Dict);
		if(Req.CreateStruct(lpFuncHdr->m_wFuncID,lpFuncReq->m_szBuffer,lpFuncReq->m_dwSize)!=0)
			return FHM_FHR_FAIL;
		// ����Ӧ��ṹ
		CWtCommon Ans(&m_Dict,NULL,TRUE);
		if(Ans.CreateStruct((WORD)(lpFuncHdr->m_wFuncID+1),lpFuncAns->m_szBuffer,nMaxAnsBodyLen)!=0)
			return FHM_FHR_FAIL;
		Ans.InitBuffer();

		// ����ֵ�����
		if(	(lpFuncHdr->m_wBuild!=0&&lpFuncHdr->m_wBuild!=m_Dict.GetBuildNo()) ||
			(lpFuncHdr->m_wVersion!=0&&lpFuncHdr->m_wVersion!=m_Dict.GetVersion()) )
		{	TCHAR szError[MAX_PATH]={0};
			nsprintf(szError,size_of(szError),"�����ֵ�汾��ƥ��(�������Ѿ�����,���˳��ͻ������½�������ֵ���Ϣ)");
			Ans.SetReturn(DICTRET_PROC_FAIL,szError,0);
		}
		// �жϴ洢���Ƿ����
		else if(lpFuncCnt->m_hStorageArea==NULL)
		{	TCHAR szError[MAX_PATH]={0};
			nsprintf(szError,size_of(szError),"Ӫҵ��(R%08d)�����ڴ洢����",lpFuncHdr->m_dwBranchID);
			Ans.SetReturn(DICTRET_PROC_FAIL,szError,0);
		}
		// ����ҵ����
		else
		{	LONG nProcRet=FuncHandlerSub(lpFuncCnt,lpFuncHdr,&Req,&Ans);
			if(nProcRet<=FHM_FHR_FAIL) return nProcRet;
		}
		lpFuncAns->m_dwSize=Ans.GetUsedBufferLen();
		return FHM_FHR_SUCCESS;
	}
	// ����ά������
	virtual VOID Maintenance(HFHMSTORAGEAREA hStorageArea)
	{	MaintenanceSub(hStorageArea);
	}
protected:
	// ���ӹ������Լ����ӽӿ�
	class CSqlConnect
	{
	public:
		CSqlConnect(CFuncHandlerBase* pHandler,HFHMSTORAGEAREA hStorageArea,BOOL bAutoSelArray)
		{	// ��������ͳ�ʼ������
			VERIFY(m_pHandler!=NULL);
			m_pHandler=pHandler;
			m_bExternConnect=FALSE;
			m_hStorageArea=hStorageArea;
			m_hSqlConnect=NULL;
			memset(&m_SqlConnectData,0,size_of(m_SqlConnectData));
			// ��ȡIO����
			DWORD_PTR dwIoParam=0;
			PFHMDATAIO pDataIo=m_pHandler->GetDataIoEntry(dwIoParam);
			// ��ȡSQL���ݿ�����
			m_hSqlConnect=(HFHMSQLCONNECT)(*pDataIo)(FHMIO_ALLOCSQLCONNECT,(WPARAM)hStorageArea,(LPARAM)bAutoSelArray,dwIoParam,FALSE);
			if(m_hSqlConnect!=NULL)
			{	m_SqlConnectData.m_cbData=size_of(m_SqlConnectData);
				if(!(*pDataIo)(FHMIO_GETSQLCONNECTDATA,(WPARAM)m_hSqlConnect,(LPARAM)&m_SqlConnectData,dwIoParam,0))
				{	(*pDataIo)(FHMIO_FREESQLCONNECT,(WPARAM)m_hSqlConnect,(LPARAM)0,dwIoParam,0);
					memset(&m_SqlConnectData,0,size_of(m_SqlConnectData));
					m_hSqlConnect=NULL;
				}
			}
		}
		CSqlConnect(CFuncHandlerBase* pHandler,HFHMSTORAGEAREA hStorageArea,BOOL bAutoSelArray,BOOL bSelSlave)
		{	// ��������ͳ�ʼ������
			VERIFY(m_pHandler!=NULL);
			m_pHandler=pHandler;
			m_bExternConnect=FALSE;
			m_hStorageArea=hStorageArea;
			m_hSqlConnect=NULL;
			memset(&m_SqlConnectData,0,size_of(m_SqlConnectData));
			// ��ȡIO����
			DWORD_PTR dwIoParam=0;
			PFHMDATAIO pDataIo=m_pHandler->GetDataIoEntry(dwIoParam);
			// ��ȡSQL���ݿ�����
			m_hSqlConnect=(HFHMSQLCONNECT)(*pDataIo)(FHMIO_ALLOCSQLCONNECT,(WPARAM)hStorageArea,(LPARAM)bAutoSelArray,dwIoParam,bSelSlave);
			if(m_hSqlConnect!=NULL)
			{	m_SqlConnectData.m_cbData=size_of(m_SqlConnectData);
				if(!(*pDataIo)(FHMIO_GETSQLCONNECTDATA,(WPARAM)m_hSqlConnect,(LPARAM)&m_SqlConnectData,dwIoParam,0))
				{	(*pDataIo)(FHMIO_FREESQLCONNECT,(WPARAM)m_hSqlConnect,(LPARAM)0,dwIoParam,0);
					memset(&m_SqlConnectData,0,size_of(m_SqlConnectData));
					m_hSqlConnect=NULL;
				}
			}
		}
		CSqlConnect(CFuncHandlerBase* pHandler,HFHMSTORAGEAREA hStorageArea,HFHMSQLCONNECT hSqlConnect)
		{	// ��������ͳ�ʼ������
			VERIFY(m_pHandler!=NULL);
			m_pHandler=pHandler;
			m_bExternConnect=TRUE;
			m_hStorageArea=hStorageArea;
			m_hSqlConnect=hSqlConnect;
			memset(&m_SqlConnectData,0,size_of(m_SqlConnectData));
			// ��ȡIO����
			DWORD_PTR dwIoParam=0;
			PFHMDATAIO pDataIo=m_pHandler->GetDataIoEntry(dwIoParam);
			// ��ȡSQL���ݿ�����
			if(m_hSqlConnect!=NULL)
			{	m_SqlConnectData.m_cbData=size_of(m_SqlConnectData);
				if(!(*pDataIo)(FHMIO_GETSQLCONNECTDATA,(WPARAM)m_hSqlConnect,(LPARAM)&m_SqlConnectData,dwIoParam,0))
				{	memset(&m_SqlConnectData,0,size_of(m_SqlConnectData));
					m_hSqlConnect=NULL;
				}
			}
		}
		virtual ~CSqlConnect()
		{	if(m_hSqlConnect!=NULL)
			{	if(!m_bExternConnect)
				{	// ��ȡIO����
					DWORD_PTR dwIoParam=0;
					PFHMDATAIO pDataIo=m_pHandler->GetDataIoEntry(dwIoParam);
					// ��ȡSQL���ݿ�����
					(*pDataIo)(FHMIO_FREESQLCONNECT,(WPARAM)m_hSqlConnect,(LPARAM)0,dwIoParam,0);
				}
				memset(&m_SqlConnectData,0,size_of(m_SqlConnectData));
				m_hSqlConnect=NULL;
			}
		}
		VOID DropSqlConnect()
		{	if(m_hSqlConnect!=NULL)
			{	// ��ȡIO����
				DWORD_PTR dwIoParam=0;
				PFHMDATAIO pDataIo=m_pHandler->GetDataIoEntry(dwIoParam);
				// ��ȡSQL���ݿ�����
				(*pDataIo)(FHMIO_DROPSQLCONNECT,(WPARAM)m_hSqlConnect,(LPARAM)0,dwIoParam,0);
			}
		}
		BOOL IsSqlConnectNull() const { return m_hSqlConnect==NULL; }
		operator HFHMSTORAGEAREA() const { return m_hStorageArea; }
		operator HFHMSQLCONNECT() const { return m_hSqlConnect; }
		CADODatabase* operator->() { return (CADODatabase*)m_SqlConnectData.m_pAdoDatabase; }
		operator CADODatabase*() { return (CADODatabase*)m_SqlConnectData.m_pAdoDatabase; }
		BOOL IsPrimary() { return m_bIsPrimary; }
		LONG GetArrayNo() { return m_nArrayNo; }
		LONG GetIndexInArray() { return m_nIndexInArray; }
	protected:
		CFuncHandlerBase* m_pHandler;			// ������ָ��
		BOOL m_bExternConnect;					// �ⲿ(����)����
		HFHMSTORAGEAREA m_hStorageArea;			// �洢�����
		HFHMSQLCONNECT m_hSqlConnect;			// SQL���Ӿ��
		FHMSQLCONNECTDATA m_SqlConnectData;		// SQL��������
	};
	friend class CSqlConnect;
	PFHMDATAIO GetDataIoEntry(DWORD_PTR& dwIoParam)
	{	dwIoParam=m_FHMParam.m_dwIoParam;
		return m_FHMParam.m_pfnDataIo;
	}
	virtual LONG FuncHandlerSub(LPFHMFUNCCNT lpFuncCnt,LPFUNCHDR lpFuncHdr,CWtCommon* pReq,CWtCommon* pAns)
	{	UNREFERENCED_PARAMETER(lpFuncCnt);
		UNREFERENCED_PARAMETER(lpFuncHdr);
		UNREFERENCED_PARAMETER(pReq);
		pAns->SetReturn(DICTRET_PROC_FAIL,"ϵͳ��ʱ��֧�ִ˹���",0);
		return FHM_FHR_SUCCESS;
	}
	virtual VOID MaintenanceSub(HFHMSTORAGEAREA hStorageArea)
	{	UNREFERENCED_PARAMETER(hStorageArea);
		return;
	}
protected:
	FHMPARAM m_FHMParam;
	CWtDict2 m_Dict;
};




//------------------------------------------------------------------------
// Part.III ���ܴ���ģ�����ʵ������
//------------------------------------------------------------------------
#define DECLARE_FHM_FUNC_HANDLER(FundHandlerClass)																						\
	FundHandlerClass g_FuncHandler;																										\
	BOOL FHM_InitializeHandler(LPFHMPARAM pFHMParam)																					\
		{ return g_FuncHandler.InitializeHandler(pFHMParam); }																			\
	BOOL FHM_UninitializeHandler()																										\
		{ return g_FuncHandler.UninitializeHandler(); }																					\
	DWORD FHM_GetDictionary(LPBYTE pBuffer,DWORD cbBuffer)																				\
		{ return g_FuncHandler.GetDictionary(pBuffer,cbBuffer); }																		\
	LONG FHM_FuncHandler(LPFHMFUNCCNT lpFuncCnt,LPFUNCHDR lpFuncHdr,LPFUNCBDY lpFuncReq,LPFUNCBDY lpFuncAns,UINT nMaxAnsBodyLen)		\
		{ return g_FuncHandler.FuncHandler(lpFuncCnt,lpFuncHdr,lpFuncReq,lpFuncAns,nMaxAnsBodyLen); }									\
	VOID FHM_Maintenance(HFHMSTORAGEAREA hStorageArea)																					\
		{ g_FuncHandler.Maintenance(hStorageArea); }																					\

#endif

#pragma pack()
#endif
