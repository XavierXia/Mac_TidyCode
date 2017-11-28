//////////////////////////////////////////////////////////////////////////
// 创建日期:2006/07/20
// 功能说明:标准/用户FEM/FEB实现声明
// 变更记录:
//          2006/07/21 支持TC50接口协议
//          2008/03/11 移植到linux
#ifndef __TC_FEMDECLARE__H__
#define __TC_FEMDECLARE__H__


//////////////////////////////////////////////////////////////////////////
// 全部结构使用1字节对齐
#pragma pack(1)




//------------------------------------------------------------------------
// Part.I 函数导出
//------------------------------------------------------------------------
extern "C"
{
	//////////////////////////////////////////////////////////////////////////
	// 取得版本信息
	// 参数:
	//      lpFEMInfo[OUT]				模块信息
	// 返回:
	//      无
	DLLEXPORT VOID FEM_GetInformation(LPFEMINFO lpFEMInfo);




	//////////////////////////////////////////////////////////////////////////
	// 取摘要列结构定义(包括配置摘要以及状态摘要)
	// 参数:
	//		dwSummaryType[IN]			摘要列类型
	//		lpFEMSummary[OUT]			列定义
	//		dwMaxCount[IN]				最大摘要列个数(一般不超过10个)
	// 返回:
	//      设置摘要列个数
	DLLEXPORT DWORD FEM_GetSummaryCols(DWORD dwSummaryType,LPFEMSUMMARY lpFEMSummary,DWORD dwMaxCount);




	//////////////////////////////////////////////////////////////////////////
	// 取得设置摘要列字段
	// 参数:
	//      lpszFilePath[IN]			配置文件路径
	//		lpszBranchSection[IN]		营业部对应的节名
	//		dwColType[IN]				列类型
	//      dwMaxSize[IN]				最大大小
	//		lpszSummary[OUT]			摘要信息
	// 返回:
	//      无
	DLLEXPORT VOID FEM_GetOptionSummary(LPCSTR lpszFilePath,LPCSTR lpszBranchSection,DWORD dwColType,DWORD dwMaxSize,LPSTR lpszSummary);




	//////////////////////////////////////////////////////////////////////////
	// 显示公用设置修改对话框
	// 参数:
	//		hParent[IN]					配置对话框父对话框
	//      lpszFilePath[IN]			配置文件路径
	//      lpszSection[IN]				节名(公用配置或某营业部配置)
	//      bPublicOption				是否是公用设置
	// 返回:
	//      参数是否被修改
	DLLEXPORT BOOL FEM_ShowOptionDialog(HWND hParent,LPCSTR lpszFilePath,LPCSTR lpszSection,BOOL bPublicOption);
	
	
	
	
	//////////////////////////////////////////////////////////////////////////
	// 运行期全局初始化
	// 参数:
	//      lpFEMParam[IN]									初始化参数
	// 返回:
	//      无
	DLLEXPORT BOOL FEM_InitInst(LPFEMPARAM lpFEMParam);
	
	
	
	
	//////////////////////////////////////////////////////////////////////////
	// 运行期全局关闭函数
	// 参数:
	//      无
	// 返回:
	//      无
	DLLEXPORT VOID FEM_ExitInst();
	
	
	
	
	//////////////////////////////////////////////////////////////////////////
	// 取得数据字典
	// 参数:
	//      dwType[IN]:       字典类型
	//      dwMaxSize[IN]:    缓冲区最大大小
	//      lpDict[OUT]:      字典缓冲区
	// 返回:
	//      字典长度
	DLLEXPORT DWORD FEM_GetDicts(DWORD dwType,DWORD dwMaxSize,LPBYTE lpDict);
	
	
	
	
	//////////////////////////////////////////////////////////////////////////
	// 事务处理过程
	// 返回数据>=0,处理成功,返回数据随应答包送回
	// 返回数据<0,处理失败,客户端收到异常处理通知,错误号随通知送回
	// DLL的返回范围为-10000<=RETCODE<=+10000
	DLLEXPORT LONG FEM_BusinessProc(PVOID pFuncCnt,DWORD dwBranchID,LPFUNCHDR lpFuncHdr,LPFUNCBDY lpFuncReq,LPFUNCBDY lpFuncAns);




	//////////////////////////////////////////////////////////////////////////
	// 取当前营业部状态(后台状态)
	// 参数:
	//      dwBranchID					营业部号
	// 返回:
	//      营业部后台连接是否可用
	DLLEXPORT BOOL FEM_IsBranchAvailable(DWORD dwBranchID);




	//////////////////////////////////////////////////////////////////////////
	// 取得状态摘要列
	// 参数:
	//		dwColType[IN]				列类型
	//      dwMaxSize[IN]				最大大小
	//		lpszSummary[OUT]			摘要信息
	// 返回:
	//      无
	DLLEXPORT VOID FEM_GetStatusSummary(DWORD dwBranchID,DWORD dwColType,DWORD dwMaxSize,LPSTR lpszSummary);

}

#pragma pack()


#endif

