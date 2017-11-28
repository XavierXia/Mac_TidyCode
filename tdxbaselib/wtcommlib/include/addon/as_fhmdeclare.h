//////////////////////////////////////////////////////////////////////////
// 创建日期:2008/08/12
// 功能说明:标准/用户FHM/FHB实现声明
// 变更记录:
#ifndef __AS_FHMDECLARE__H__
#define __AS_FHMDECLARE__H__
#pragma pack(1)

#ifdef WIN32


//------------------------------------------------------------------------
// Part.I 功能处理模块函数导出
//------------------------------------------------------------------------
extern "C"
{
	//////////////////////////////////////////////////////////////////////////
	// 处理模块初始化
	// 参数:
	//      pfnFHMDataIo[IN]			数据IO回调信息
	// 返回:
	//      是否成功
	DLLEXPORT BOOL FHM_InitializeHandler(LPFHMPARAM pFHMParam);




	//////////////////////////////////////////////////////////////////////////
	// 处理模块数据释放
	// 参数:
	// 返回:
	//      是否成功
	DLLEXPORT BOOL FHM_UninitializeHandler();




	//////////////////////////////////////////////////////////////////////////
	// 获取数据字典
	// 参数:
	//		LPBYTE pBuffer				字典缓冲区
	//		DWORD cbBuffer				字典缓冲区长度
	// 返回:
	//      字段长度
	DLLEXPORT DWORD FHM_GetDictionary(LPBYTE pBuffer,DWORD cbBuffer);




	//////////////////////////////////////////////////////////////////////////
	// 功能处理
	// 参数:
	//		LPFHMFUNCCNT lpFuncCnt		调用上下文
	//		LPFUNCHDR lpFuncHdr			请求头部
	//		LPFUNCBDY lpFuncReq			请求数据
	//		LPFUNCBDY lpFuncAns			应答数据
	//		UINT nMaxAnsBodyLen		
	// 返回:
	//      处理状态(FHM_FHR_XXXX)
	DLLEXPORT LONG FHM_FuncHandler(LPFHMFUNCCNT lpFuncCnt,LPFUNCHDR lpFuncHdr,LPFUNCBDY lpFuncReq,LPFUNCBDY lpFuncAns,UINT nMaxAnsBodyLen);

	

	//////////////////////////////////////////////////////////////////////////
	// 数据维护
	// 参数:
	//		HFHMSTORAGEAREA hStorageArea	存储区域
	//		HFHMSQLCONNECT hSqlConnect		数据库连接
	// 返回:
	//      是否成功
	DLLEXPORT VOID FHM_Maintenance(HFHMSTORAGEAREA hStorageArea);


}




//------------------------------------------------------------------------
// Part.II 功能处理模块基类
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
	// 数据处理过程
	virtual LONG FuncHandler(LPFHMFUNCCNT lpFuncCnt,LPFUNCHDR lpFuncHdr,LPFUNCBDY lpFuncReq,LPFUNCBDY lpFuncAns,UINT nMaxAnsBodyLen)
	{	VERIFY(lpFuncCnt!=NULL);
		VERIFY(lpFuncHdr!=NULL);
		VERIFY(lpFuncReq!=NULL);
		VERIFY(lpFuncAns!=NULL);
		// 初始化返回并创建请求和应答结构
		lpFuncAns->m_dwSize=0;
		// 创建请求结构
		CWtCommon Req;
		Req.SetDict(&m_Dict);
		if(Req.CreateStruct(lpFuncHdr->m_wFuncID,lpFuncReq->m_szBuffer,lpFuncReq->m_dwSize)!=0)
			return FHM_FHR_FAIL;
		// 创建应答结构
		CWtCommon Ans(&m_Dict,NULL,TRUE);
		if(Ans.CreateStruct((WORD)(lpFuncHdr->m_wFuncID+1),lpFuncAns->m_szBuffer,nMaxAnsBodyLen)!=0)
			return FHM_FHR_FAIL;
		Ans.InitBuffer();

		// 检查字典编译号
		if(	(lpFuncHdr->m_wBuild!=0&&lpFuncHdr->m_wBuild!=m_Dict.GetBuildNo()) ||
			(lpFuncHdr->m_wVersion!=0&&lpFuncHdr->m_wVersion!=m_Dict.GetVersion()) )
		{	TCHAR szError[MAX_PATH]={0};
			nsprintf(szError,size_of(szError),"数据字典版本不匹配(服务器已经升级,请退出客户端重新进入更新字典信息)");
			Ans.SetReturn(DICTRET_PROC_FAIL,szError,0);
		}
		// 判断存储区是否存在
		else if(lpFuncCnt->m_hStorageArea==NULL)
		{	TCHAR szError[MAX_PATH]={0};
			nsprintf(szError,size_of(szError),"营业部(R%08d)不存在存储区。",lpFuncHdr->m_dwBranchID);
			Ans.SetReturn(DICTRET_PROC_FAIL,szError,0);
		}
		// 进行业务处理
		else
		{	LONG nProcRet=FuncHandlerSub(lpFuncCnt,lpFuncHdr,&Req,&Ans);
			if(nProcRet<=FHM_FHR_FAIL) return nProcRet;
		}
		lpFuncAns->m_dwSize=Ans.GetUsedBufferLen();
		return FHM_FHR_SUCCESS;
	}
	// 数据维护过程
	virtual VOID Maintenance(HFHMSTORAGEAREA hStorageArea)
	{	MaintenanceSub(hStorageArea);
	}
protected:
	// 连接管理器以及连接接口
	class CSqlConnect
	{
	public:
		CSqlConnect(CFuncHandlerBase* pHandler,HFHMSTORAGEAREA hStorageArea,BOOL bAutoSelArray)
		{	// 保存参数和初始化数据
			VERIFY(m_pHandler!=NULL);
			m_pHandler=pHandler;
			m_bExternConnect=FALSE;
			m_hStorageArea=hStorageArea;
			m_hSqlConnect=NULL;
			memset(&m_SqlConnectData,0,size_of(m_SqlConnectData));
			// 获取IO参数
			DWORD_PTR dwIoParam=0;
			PFHMDATAIO pDataIo=m_pHandler->GetDataIoEntry(dwIoParam);
			// 获取SQL数据库连接
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
		{	// 保存参数和初始化数据
			VERIFY(m_pHandler!=NULL);
			m_pHandler=pHandler;
			m_bExternConnect=FALSE;
			m_hStorageArea=hStorageArea;
			m_hSqlConnect=NULL;
			memset(&m_SqlConnectData,0,size_of(m_SqlConnectData));
			// 获取IO参数
			DWORD_PTR dwIoParam=0;
			PFHMDATAIO pDataIo=m_pHandler->GetDataIoEntry(dwIoParam);
			// 获取SQL数据库连接
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
		{	// 保存参数和初始化数据
			VERIFY(m_pHandler!=NULL);
			m_pHandler=pHandler;
			m_bExternConnect=TRUE;
			m_hStorageArea=hStorageArea;
			m_hSqlConnect=hSqlConnect;
			memset(&m_SqlConnectData,0,size_of(m_SqlConnectData));
			// 获取IO参数
			DWORD_PTR dwIoParam=0;
			PFHMDATAIO pDataIo=m_pHandler->GetDataIoEntry(dwIoParam);
			// 获取SQL数据库连接
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
				{	// 获取IO参数
					DWORD_PTR dwIoParam=0;
					PFHMDATAIO pDataIo=m_pHandler->GetDataIoEntry(dwIoParam);
					// 获取SQL数据库连接
					(*pDataIo)(FHMIO_FREESQLCONNECT,(WPARAM)m_hSqlConnect,(LPARAM)0,dwIoParam,0);
				}
				memset(&m_SqlConnectData,0,size_of(m_SqlConnectData));
				m_hSqlConnect=NULL;
			}
		}
		VOID DropSqlConnect()
		{	if(m_hSqlConnect!=NULL)
			{	// 获取IO参数
				DWORD_PTR dwIoParam=0;
				PFHMDATAIO pDataIo=m_pHandler->GetDataIoEntry(dwIoParam);
				// 获取SQL数据库连接
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
		CFuncHandlerBase* m_pHandler;			// 处理类指针
		BOOL m_bExternConnect;					// 外部(分配)连接
		HFHMSTORAGEAREA m_hStorageArea;			// 存储区句柄
		HFHMSQLCONNECT m_hSqlConnect;			// SQL连接句柄
		FHMSQLCONNECTDATA m_SqlConnectData;		// SQL连接数据
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
		pAns->SetReturn(DICTRET_PROC_FAIL,"系统暂时不支持此功能",0);
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
// Part.III 功能处理模块基类实现声明
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
