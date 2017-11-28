#ifndef __TS_EASY_USE__H__
#define __TS_EASY_USE__H__

// 没有SAFEVCRT支持的情况下
#if defined(WITH_SAFEVCRT)
	#define TSVERIFY(f)	CLIBVERIFY(f)
#else
	#define TSVERIFY(f) ((void)(f))
#endif



// 基本对象接口实现
#define IMPLEMENT_OBJECT_INTERFACE(__INTERFACE)																\
	virtual LPVOID Cast(const IID & riid)																	\
		{	if(riid==IID_##__INTERFACE) return (__INTERFACE*)this;											\
			return NULL;																					\
		}																									\
	virtual LPVOID GetObjectPtr() { return this; }															\
	virtual BOOL IsObjectNull() const { return this==NULL; }												\


#define IMPLEMENT_OBJECT_INTERFACE_EX1(__CLASS,__INTERFACE)													\
	virtual LPVOID Cast(const IID & riid)																	\
		{	if(riid==IID_##__INTERFACE) return (__INTERFACE*)this;											\
			return NULL;																					\
		}																									\
	virtual LPVOID GetObjectPtr() { return (LPVOID)((__CLASS*)this); }										\
	virtual BOOL IsObjectNull() const { return this==NULL; }												\


#define IMPLEMENT_OBJECT_INTERFACE_EX2(__INTERFACE,__MEMBER)												\
	virtual LPVOID Cast(const IID & riid)																	\
		{	if(riid==IID_##__INTERFACE) return (__INTERFACE*)this;											\
			return NULL;																					\
		}																									\
	virtual LPVOID GetObjectPtr() { return __MEMBER; }														\
	virtual BOOL IsObjectNull() const { return this==NULL||__MEMBER==NULL; }								\


#define IMPLEMENT_OBJECT_INTERFACE_DUAL(__INTERFACE1,__INTERFACE2)											\
	virtual LPVOID Cast(const IID & riid)																	\
		{	if(riid==IID_##__INTERFACE1) return (__INTERFACE1*)this;										\
			if(riid==IID_##__INTERFACE2) return (__INTERFACE2*)this;										\
			return NULL;																					\
		}																									\
	virtual LPVOID GetObjectPtr() { return this; }															\
	virtual BOOL IsObjectNull() const { return this==NULL; }												\


#define IMPLEMENT_OBJECT_INTERFACE_TRIPLE(__INTERFACE1,__INTERFACE2,__INTERFACE3)							\
	virtual LPVOID Cast(const IID & riid)																	\
		{	if(riid==IID_##__INTERFACE1) return (__INTERFACE1*)this;										\
			if(riid==IID_##__INTERFACE2) return (__INTERFACE2*)this;										\
			if(riid==IID_##__INTERFACE3) return (__INTERFACE3*)this;										\
			return NULL;																					\
		}																									\
	virtual LPVOID GetObjectPtr() { return this; }															\
	virtual BOOL IsObjectNull() const { return this==NULL; }												\

#define IMPLEMENT_OBJECT_INTERFACE_FOUR(__INTERFACE1,__INTERFACE2,__INTERFACE3,__INTERFACE4)				\
	virtual LPVOID Cast(const IID & riid)																	\
		{	if(riid==IID_##__INTERFACE1) return (__INTERFACE1*)this;										\
			if(riid==IID_##__INTERFACE2) return (__INTERFACE2*)this;										\
			if(riid==IID_##__INTERFACE3) return (__INTERFACE3*)this;										\
			if(riid==IID_##__INTERFACE4) return (__INTERFACE4*)this;										\
			return NULL;																					\
		}																									\
		virtual LPVOID GetObjectPtr() { return this; }														\
		virtual BOOL IsObjectNull() const { return this==NULL; }											\

#define IMPLEMENT_OBJECT_INTERFACE_FIVE(__INTERFACE1,__INTERFACE2,__INTERFACE3,__INTERFACE4,__INTERFACE5)	\
	virtual LPVOID Cast(const IID & riid)																	\
		{	if(riid==IID_##__INTERFACE1) return (__INTERFACE1*)this;										\
			if(riid==IID_##__INTERFACE2) return (__INTERFACE2*)this;										\
			if(riid==IID_##__INTERFACE3) return (__INTERFACE3*)this;										\
			if(riid==IID_##__INTERFACE4) return (__INTERFACE4*)this;										\
			if(riid==IID_##__INTERFACE5) return (__INTERFACE5*)this;										\
			return NULL;																					\
		}																									\
		virtual LPVOID GetObjectPtr() { return this; }														\
		virtual BOOL IsObjectNull() const { return this==NULL; }											\






















// 模块基类
template<class TYPE1=INull1,class TYPE2=INull2,class TYPE3=INull3,class TYPE4=INull4,class TYPE5=INull5,class TYPE6=INull6>
class CModuleBase : public ICoreModule,public ISDKInfo,public TYPE1,public TYPE2,public TYPE3,public TYPE4,public TYPE5,public TYPE6
{
public:
	CModuleBase(IServer* pIServer,LPCSTR pszName) { m_pIServer=pIServer; m_pszModuleName=pszName; }
	virtual~CModuleBase(){}
	ICoreModule* This() { return this; }
protected:
	// IObject接口
	IMPLEMENT_OBJECT_INTERFACE_DUAL(ICoreModule,ISDKInfo);
	// ICoreModule接口
	virtual LPCSTR GetName() const { return m_pszModuleName; }
	virtual BOOL Configure() { return TRUE; }
	virtual BOOL Start() PURE;
	virtual BOOL Ready() { return TRUE; }
	virtual VOID Shut() {}
	virtual VOID Stop() {}
	virtual VOID Final() { if(this==NULL) return; delete this; }
	// ISDKInfo接口
	virtual DWORD GetSDKVer() const { return T2EESDKVER_LASTEST; }
protected:
	IServer*	m_pIServer;			// 主控模块
	LPCSTR		m_pszModuleName;	// 模块名称
};
















// 服务模块基类
typedef IService::SERVICESTYLE _SERVICESTYLE;
typedef IService::SERVICESTATUS _SERVICESTATUS;
template<class TYPE1=INull1,class TYPE2=INull2,class TYPE3=INull3,class TYPE4=INull4,class TYPE5=INull5,class TYPE6=INull6>
class CServiceBase : public TYPE1,public TYPE2,public TYPE3,public TYPE4,public TYPE5,public TYPE6
{
public:
	// 构造和析构
	CServiceBase(IServer* pIServer,LPCSTR pszName,ICoreModule* pICoreModule,IID iidInterface)
		{	m_pIServer=pIServer;
			m_pszServiceName=pszName;
			m_pICoreModule=pICoreModule;
			m_iidInterface=iidInterface;
			m_nCallerCnt=0;
			m_eServiceStatus=IService::SERVICEST_NOTRUNNING;
		}
	virtual~CServiceBase()
		{
		}
protected:
	// IObject接口
	virtual LPVOID Cast(const IID & riid) { return (riid==m_iidInterface)?(TYPE1*)this:((riid==IID_IService)?(IService*)this:NULL); }
	virtual LPVOID GetObjectPtr() { return this; }
	virtual BOOL IsObjectNull() const { return this==NULL; }
	// IService接口
	virtual LPCSTR GetName() const { return m_pszServiceName; }
	virtual ICoreModule* GetModule() const { return m_pICoreModule; }
	virtual VOID AddCaller() { InterlockedIncrement(&m_nCallerCnt); }
	virtual LONG GetCallerCnt() { return m_nCallerCnt; }
	virtual _SERVICESTYLE GetServiceStyle() { return (_SERVICESTYLE)(IService::SERVICE_EXTEND|IService::SERVICE_OPTIONAL); }
	virtual _SERVICESTATUS GetServiceStatus() { return m_eServiceStatus; }
	virtual VOID UpdateServiceStatus(_SERVICESTATUS eServiceStatus) { m_eServiceStatus=eServiceStatus; }
	virtual BOOL Configure() { return TRUE; }
	virtual BOOL Start() PURE;
	virtual BOOL Ready() { return TRUE; }
	virtual VOID Shut() {}
	virtual VOID Stop() {}
	virtual VOID Final() {}
protected:
	IServer*				m_pIServer;			// 主控模块
	LPCSTR					m_pszServiceName;	// 服务名称
	ICoreModule*			m_pICoreModule;		// 模块接口
	IID						m_iidInterface;		// 服务接口
	LONG					m_nCallerCnt;		// 引用记数
	_SERVICESTATUS			m_eServiceStatus;	// 服务状态
};







// 原始协议处理模块基类
template<class TYPE1=INull1,class TYPE2=INull2,class TYPE3=INull3,class TYPE4=INull4,class TYPE5=INull5,class TYPE6=INull6>
class CRawHandlerBase : public TYPE1,public TYPE2,public TYPE3,public TYPE4,public TYPE5,public TYPE6
{
public:
	// 构造和析构
	CRawHandlerBase(IServer* pIServer,LPCSTR pszName,ICoreModule* pICoreModule)
		{	m_pIServer=pIServer;
			m_pszHandlerName=pszName;
			m_pICoreModule=pICoreModule;
		}
	virtual~CRawHandlerBase()
		{
		}
protected:
	// IObject接口
	IMPLEMENT_OBJECT_INTERFACE(IRawHandler);
	// IHandler接口
	virtual LPCSTR GetName() const { return m_pszHandlerName; }
	virtual ICoreModule* GetModule() const { return m_pICoreModule; }
	virtual BOOL Configure() PURE;
	virtual BOOL AttachServer() PURE;
	virtual BOOL AttachBackstage() { return TRUE; }
	virtual VOID DetachServer() {}
public:
	// 同步事务信息
	VOID SetBusinessInfo(IBusiness* pIBusiness,RAWANSCNTX* pRawAnsCntx,DWORD cbTotal)
	{	UNREFERENCED_PARAMETER(pRawAnsCntx);
		CLIBASSERT(pIBusiness!=NULL);
		pIBusiness->SetInfo(cbTotal);
	}
	// 同步事务完成
	VOID SetBusinessCompleted(IBusiness* pIBusiness,RAWANSCNTX* pRawAnsCntx,DWORD cbBody,WORD wCmdNo=USHRT_MAX,DWORD dwFragmentNo=FRAGMENT_DEFAULT)
	{	CLIBASSERT(pIBusiness!=NULL);
		CLIBASSERT(pRawAnsCntx!=NULL);
		if(wCmdNo==USHRT_MAX) wCmdNo=pIBusiness->GetCmdNo();
		pRawAnsCntx->m_cbBody=cbBody;
		pIBusiness->SetAnsState(EL_NOERROR,EC_NOERROR,"处理完成");
		pIBusiness->SetAnsCompleted(wCmdNo,dwFragmentNo);
	}
protected:
	IServer*		m_pIServer;			// 主控模块
	LPCSTR			m_pszHandlerName;	// 处理器名称
	ICoreModule*	m_pICoreModule;		// 模块接口
};







// HTTP协议处理模块基类
template<class TYPE1=INull1,class TYPE2=INull2,class TYPE3=INull3,class TYPE4=INull4,class TYPE5=INull5,class TYPE6=INull6>
class CHttpHandlerBase : public TYPE1,public TYPE2,public TYPE3,public TYPE4,public TYPE5,public TYPE6
{
public:
	// 构造和析构
	CHttpHandlerBase(IServer* pIServer,LPCSTR pszName,ICoreModule* pICoreModule)
		{	m_pIServer=pIServer;
			m_pszHandlerName=pszName;
			m_pICoreModule=pICoreModule;
		}
	virtual~CHttpHandlerBase()
		{
		}
protected:
	// IObject接口
	IMPLEMENT_OBJECT_INTERFACE(IHttpHandler);
	// IHandler接口
	virtual LPCSTR GetName() const { return m_pszHandlerName; }
	virtual ICoreModule* GetModule() const { return m_pICoreModule; }
	virtual BOOL Configure() PURE;
	virtual BOOL AttachServer() PURE;
	virtual BOOL AttachBackstage() { return TRUE; }
	virtual VOID DetachServer() {}
public:
	// 同步事务信息
	VOID SetBusinessInfo(IBusiness* pIBusiness,IHttpAnsCntx* pIHttpAnsCntx,DWORD cbTotal)
	{	UNREFERENCED_PARAMETER(pIHttpAnsCntx);
		CLIBASSERT(pIBusiness!=NULL);
		pIBusiness->SetInfo(cbTotal);
	}
	// 同步事务完成
	VOID SetBusinessCompleted(IBusiness* pIBusiness,IHttpAnsCntx* pIHttpAnsCntx,DWORD cbBody,DWORD dwFragmentNo=FRAGMENT_DEFAULT)
	{	CLIBASSERT(pIHttpAnsCntx!=NULL);
		CLIBASSERT(pIBusiness!=NULL);
		pIHttpAnsCntx->m_cbBody=cbBody;
		pIBusiness->SetAnsState(EL_NOERROR,EC_NOERROR,"处理完成");
		pIBusiness->SetAnsCompleted(pIBusiness->GetCmdNo(),dwFragmentNo);
	}
	// 设置其他错误
	BPR ThrowHttpError(IBusiness* pIBusiness,IHttpAnsCntx* pIHttpAnsCntx,WORD wStatusNo,LPCSTR pszStatus)
	{	pIHttpAnsCntx->m_wStatusNo=wStatusNo;
		pIHttpAnsCntx->m_pszStatus=pszStatus;
		SetBusinessCompleted(pIBusiness,pIHttpAnsCntx,0);
		return BPR_SUCCESS;
	}
protected:
	IServer*		m_pIServer;			// 主控模块
	LPCSTR			m_pszHandlerName;	// 处理器名称
	ICoreModule*	m_pICoreModule;		// 模块接口
};












//////////////////////////////////////////////////////////////////////////
// 可删除对象自动类
template <class TYPE>
class CAutoRemovableObject
{
public:
	CAutoRemovableObject(TYPE* pObject)
	{	m_pObject=(TYPE*)pObject;
	}
	virtual~CAutoRemovableObject()
	{	if(m_pObject!=NULL) m_pObject->ReleaseObject();
	}
	VOID SetObject(TYPE* pObject)
	{	if(m_pObject==pObject) return;
		if(m_pObject!=NULL) m_pObject->ReleaseObject();
		m_pObject=pObject;
	}
	const CAutoRemovableObject& operator=(TYPE* pObject) { SetObject(pObject); return (*this); }
	BOOL IsNull() { return m_pObject==NULL; }
	operator TYPE* () const { return m_pObject; }
	TYPE* operator->() { TSVERIFY(m_pObject!=NULL); return m_pObject; }
protected:
	TYPE* m_pObject;
};



//////////////////////////////////////////////////////////////////////////
// 智能指针定义
#ifndef DECLARE_SMARTPTR_DEFINED
#define DECLARE_SMARTPTR_DEFINED
	#define DECLARE_SMARTPTR(CLASSNAME,PTRTYPE)											\
	class CLASSNAME																		\
	{																					\
	public:																				\
		CLASSNAME(PTRTYPE* pPtr)														\
			{	m_pPtr=pPtr;															\
			}																			\
		virtual~CLASSNAME()																\
			{	if(m_pPtr!=NULL)														\
				{	m_pPtr->ReleaseObject();											\
					m_pPtr=NULL;														\
				}																		\
			}																			\
		VOID SetPtr(PTRTYPE* pPtr)														\
			{	if(m_pPtr!=NULL) m_pPtr->ReleaseObject();								\
				m_pPtr=pPtr;															\
			}																			\
		const CLASSNAME& operator=(PTRTYPE* pPtr)										\
			{	SetPtr(pPtr);															\
				return (*this);															\
			}																			\
		BOOL IsNull() { return m_pPtr==NULL; }											\
		BOOL IsValid() { return m_pPtr!=NULL; }											\
		operator PTRTYPE* () const { return m_pPtr; }									\
		PTRTYPE* operator->() { TSVERIFY(m_pPtr!=NULL); return m_pPtr; }				\
	protected:																			\
		PTRTYPE* m_pPtr;																\
	};																					\

#endif


//////////////////////////////////////////////////////////////////////////
// 基本智能指针定义
DECLARE_SMARTPTR(CSessionPtr,ISession);
DECLARE_SMARTPTR(CConnectPtr,IConnect);
DECLARE_SMARTPTR(CBusinessPtr,IBusiness);


//////////////////////////////////////////////////////////////////////////
// 会话锁对象
class CAutoSessionLocker
{
public:
	CAutoSessionLocker(ISession* pISession) { ManualLock(pISession); }
	virtual~CAutoSessionLocker() { ManualUnlock(); }
	VOID ManualLock(ISession* pISession) { m_pISession=pISession; if(m_pISession!=NULL) m_pISession->LockSession(); }
	VOID ManualUnlock() { if(m_pISession!=NULL) m_pISession->UnlockSession(); m_pISession=NULL; }
protected:
	ISession* m_pISession;
};

//////////////////////////////////////////////////////////////////////////
// 上下文对象转换
LPVOID inline CNTXOBJECTCAST(LPVOID pCntxObject,const IID & riid) { return (pCntxObject==NULL)?NULL:((IObject*)pCntxObject)->Cast(riid); }


#endif
