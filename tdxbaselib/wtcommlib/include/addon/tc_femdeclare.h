//////////////////////////////////////////////////////////////////////////
// ��������:2006/07/20
// ����˵��:��׼/�û�FEM/FEBʵ������
// �����¼:
//          2006/07/21 ֧��TC50�ӿ�Э��
//          2008/03/11 ��ֲ��linux
#ifndef __TC_FEMDECLARE__H__
#define __TC_FEMDECLARE__H__


//////////////////////////////////////////////////////////////////////////
// ȫ���ṹʹ��1�ֽڶ���
#pragma pack(1)




//------------------------------------------------------------------------
// Part.I ��������
//------------------------------------------------------------------------
extern "C"
{
	//////////////////////////////////////////////////////////////////////////
	// ȡ�ð汾��Ϣ
	// ����:
	//      lpFEMInfo[OUT]				ģ����Ϣ
	// ����:
	//      ��
	DLLEXPORT VOID FEM_GetInformation(LPFEMINFO lpFEMInfo);




	//////////////////////////////////////////////////////////////////////////
	// ȡժҪ�нṹ����(��������ժҪ�Լ�״̬ժҪ)
	// ����:
	//		dwSummaryType[IN]			ժҪ������
	//		lpFEMSummary[OUT]			�ж���
	//		dwMaxCount[IN]				���ժҪ�и���(һ�㲻����10��)
	// ����:
	//      ����ժҪ�и���
	DLLEXPORT DWORD FEM_GetSummaryCols(DWORD dwSummaryType,LPFEMSUMMARY lpFEMSummary,DWORD dwMaxCount);




	//////////////////////////////////////////////////////////////////////////
	// ȡ������ժҪ���ֶ�
	// ����:
	//      lpszFilePath[IN]			�����ļ�·��
	//		lpszBranchSection[IN]		Ӫҵ����Ӧ�Ľ���
	//		dwColType[IN]				������
	//      dwMaxSize[IN]				����С
	//		lpszSummary[OUT]			ժҪ��Ϣ
	// ����:
	//      ��
	DLLEXPORT VOID FEM_GetOptionSummary(LPCSTR lpszFilePath,LPCSTR lpszBranchSection,DWORD dwColType,DWORD dwMaxSize,LPSTR lpszSummary);




	//////////////////////////////////////////////////////////////////////////
	// ��ʾ���������޸ĶԻ���
	// ����:
	//		hParent[IN]					���öԻ��򸸶Ի���
	//      lpszFilePath[IN]			�����ļ�·��
	//      lpszSection[IN]				����(�������û�ĳӪҵ������)
	//      bPublicOption				�Ƿ��ǹ�������
	// ����:
	//      �����Ƿ��޸�
	DLLEXPORT BOOL FEM_ShowOptionDialog(HWND hParent,LPCSTR lpszFilePath,LPCSTR lpszSection,BOOL bPublicOption);
	
	
	
	
	//////////////////////////////////////////////////////////////////////////
	// ������ȫ�ֳ�ʼ��
	// ����:
	//      lpFEMParam[IN]									��ʼ������
	// ����:
	//      ��
	DLLEXPORT BOOL FEM_InitInst(LPFEMPARAM lpFEMParam);
	
	
	
	
	//////////////////////////////////////////////////////////////////////////
	// ������ȫ�ֹرպ���
	// ����:
	//      ��
	// ����:
	//      ��
	DLLEXPORT VOID FEM_ExitInst();
	
	
	
	
	//////////////////////////////////////////////////////////////////////////
	// ȡ�������ֵ�
	// ����:
	//      dwType[IN]:       �ֵ�����
	//      dwMaxSize[IN]:    ����������С
	//      lpDict[OUT]:      �ֵ仺����
	// ����:
	//      �ֵ䳤��
	DLLEXPORT DWORD FEM_GetDicts(DWORD dwType,DWORD dwMaxSize,LPBYTE lpDict);
	
	
	
	
	//////////////////////////////////////////////////////////////////////////
	// ���������
	// ��������>=0,����ɹ�,����������Ӧ����ͻ�
	// ��������<0,����ʧ��,�ͻ����յ��쳣����֪ͨ,�������֪ͨ�ͻ�
	// DLL�ķ��ط�ΧΪ-10000<=RETCODE<=+10000
	DLLEXPORT LONG FEM_BusinessProc(PVOID pFuncCnt,DWORD dwBranchID,LPFUNCHDR lpFuncHdr,LPFUNCBDY lpFuncReq,LPFUNCBDY lpFuncAns);




	//////////////////////////////////////////////////////////////////////////
	// ȡ��ǰӪҵ��״̬(��̨״̬)
	// ����:
	//      dwBranchID					Ӫҵ����
	// ����:
	//      Ӫҵ����̨�����Ƿ����
	DLLEXPORT BOOL FEM_IsBranchAvailable(DWORD dwBranchID);




	//////////////////////////////////////////////////////////////////////////
	// ȡ��״̬ժҪ��
	// ����:
	//		dwColType[IN]				������
	//      dwMaxSize[IN]				����С
	//		lpszSummary[OUT]			ժҪ��Ϣ
	// ����:
	//      ��
	DLLEXPORT VOID FEM_GetStatusSummary(DWORD dwBranchID,DWORD dwColType,DWORD dwMaxSize,LPSTR lpszSummary);

}

#pragma pack()


#endif

