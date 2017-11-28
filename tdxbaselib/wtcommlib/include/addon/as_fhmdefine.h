//////////////////////////////////////////////////////////////////////////
// 创建日期:2006/07/20
// 功能说明:
// 变更记录:
#ifndef __AS_FHMDEFINE__H__
#define __AS_FHMDEFINE__H__
#pragma pack(1)





//------------------------------------------------------------------------
// Part.I 基础数据结构定义
//------------------------------------------------------------------------

// 数据存储句柄
typedef struct tagFHMSTORAGEAREA{}* HFHMSTORAGEAREA;
typedef struct tagFHMSQLCONNECT{}* HFHMSQLCONNECT;
// 数据存储连接
typedef struct tagFHMSQLCONNECTDATA
{	DWORD	m_cbData;				// 数据结构大小
	BOOL	m_bIsPrimary;			// 是否连接主库
	LPVOID	m_pAdoDatabase;			// 数据库连接
} FHMSQLCONNECTDATA,*LPFHMSQLCONNECTDATA;





//------------------------------------------------------------------------
// Part.II 数据回调
//------------------------------------------------------------------------

// 回调过程类型定义
//      dwIoType									wParam				lParam					dwReserved	Result
#define FHMIO_ALLOCSQLCONNECT			1000	//	(HFHMSTORAGEAREA)	(是否自动选库)			N/A			(HFHMSQLCONNECT)
#define FHMIO_GETSQLCONNECTDATA			1001	//	(HFHMSQLCONNECT)	(LPFHMSQLCONNECTDATA)	N/A			(BOOL)
#define FHMIO_DROPSQLCONNECT			1002	//	(HFHMSQLCONNECT)	N/A						N/A			(BOOL)
#define FHMIO_FREESQLCONNECT			1003	//	(HFHMSQLCONNECT)	N/A						N/A			(BOOL)

// 数据IO回调
typedef LONG (CALLBACK* PFHMDATAIO)(DWORD dwIoType,DWORD wParam,DWORD lParam,DWORD_PTR dwIoParam,DWORD dwReserved);






//------------------------------------------------------------------------
// Part.III 接口定义
//------------------------------------------------------------------------

// 接口初始化函数
typedef struct tagFHMPARAM
{	DWORD			m_cbFHMParam;					// 参数大小
	CHAR			m_szQsId[QSID_SIZE];			// 券商标识
	CHAR			m_szHomeDir[MAX_PATH];			// 主程序路径
	CHAR			m_szOptionFile[MAX_PATH];		// 配置文件路径
	PFHMDATAIO		m_pfnDataIo;					// 数据IO回调函数
	DWORD_PTR		m_dwIoParam;					// 数据IO回调参数
	BYTE			m_szReserved2[64];				// 保留字节,全空
} FHMPARAM,*LPFHMPARAM;
typedef BOOL (* FHM_INITIALIZEHANDLER)(LPFHMPARAM pFHMParam);

// 接口释放函数
typedef BOOL (* FHM_UNINITIALIZEHANDLER)();

// 字典获取
typedef DWORD (* FHM_GETDICTIONARY)(LPBYTE pBuffer,DWORD cbBuffer);

// 事务处理过程
// 返回数据>=0,处理成功,返回数据随应答包送回
// 返回数据<0,处理失败,客户端收到异常处理通知,错误号随通知送回
// DLL的返回范围为-10000<=RETCODE<=+10000
typedef enum enumFHMFUNCHANDLERET
{	FHM_FHR_FAIL=-1,								// DLL处理失败
	FHM_FHR_SUCCESS=0,								// DLL处理成功
} FHMFUNCHANDLERET;
typedef struct tagFHMFUNCCNT
{	DWORD			m_cbFuncCnt;					// 结构长度
	HFHMSTORAGEAREA	m_hStorageArea;					// 存储区域
} FHMFUNCCNT,*LPFHMFUNCCNT;
typedef LONG (* FHM_FUNCHANDLER)(LPFHMFUNCCNT lpFuncCnt,LPFUNCHDR lpFuncHdr,LPFUNCBDY lpFuncReq,LPFUNCBDY lpFuncAns,UINT nMaxAnsBodyLen);

// 数据库维护
typedef VOID (* FHM_MAINTENANCE)(HFHMSTORAGEAREA hStorageArea);




#pragma pack()
#endif

