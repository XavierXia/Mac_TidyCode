#ifndef __VFS__H__
#define __VFS__H__
#include "../safevcrt.h"
#include "imagefile.h"
#ifdef PLATFORM_WINDOWS
#include <new.h>
#include <WINSOCK.H>
#else
#include <new>
#endif // PLATFORM_WINDOWS

// ϵͳ��ȫ�����ھ����ļ��ķ��ʿ���
//	CVFS					// �����ļ�ϵͳ
//		CVFSNet				// ����������ļ�ϵͳ
//			SOCKET			//		����SOCKET����
//		CVFSImage			// ���ھ�����ļ�ϵͳ
//			CImageFS		//		�ṩ�����ļ���֧��
//			CAnyFile		//		�ṩ���ݷ��ʵ�֧��

// �����ļ�������
typedef DWORD_PTR HVFSITEM;

// ��������ļ�ϵͳ·��
#define MAX_VFSPATH	512

// �����ļ�����FAT�ṹ
typedef struct tagVFSITEMINFO
{	CHAR	m_szName[MAX_VFSPATH];			// ����·��
	LONG	m_nLength;						// ���󳤶�
	BOOL	m_bDirectory;					// �����Ƿ�ΪĿ¼
	time_t	m_tLastModify;					// ��������޸�ʱ��(��ȷ����)
} _PACKED VFSITEMINFO;
typedef VFSITEMINFO* LPVFSITEMINFO;


// �����ļ�ϵͳ��,֧��WINDOWS��LINUX
// ֧���������
class LITEFILEIO_IMP CVFS
{
public:
	CVFS(LPCTSTR lpszRoot,BOOL bUnixStyle);
	virtual~CVFS();
	enum enumCOPYOPT
	{	COPYOPT_DELNOTEXIST	= 0X00000001,	// ����������ļ�
		COPYOPT_APPENDNEW	= 0X00000002,	// д�����ļ�
		COPYOPT_UPDATEFORCE	= 0X00000004,	// ����ȫ�����ļ�
		COPYOPT_UPDATECHGED	= 0X00000008,	// �������±��޸Ĺ����ļ�
		COPYOPT_TOUPPER		= 0X00000010,	// �ļ���ת��Ϊ��д
		COPYOPT_TOLOWER		= 0X00000020,	// �ļ���ת��ΪСд
		COPYOPT_DELETESRC	= 0X00000040,	// ɾ��Դ�ļ�
		COPYOPT_NODIR		= 0X00000080,	// ����Ŀ¼
	};
	enum enumOPENMODE
	{	VFSOPENMODE_RD	= 0X00000001,		// ��ֻ����ʽ��
		VFSOPENMODE_WR	= 0X00000002,		// ��ֻд��ʽ��
		VFSOPENMODE_RW	= 0X00000003,		// �Զ�д��ʽ��
	};
	enum enumSEEKORG
	{	VFSSEEK_END,						// ��β��λ���ƶ�
		VFSSEEK_CUR,						// �ӵ�ǰλ���ƶ�
		VFSSEEK_SET,						// �ӿ�ʼλ���ƶ�
	};
	enum enumCOPYVFSACT
	{	COPYVFSACT_CREATEFILE,				// �����ļ�
		COPYVFSACT_UPDATEFILE,				// �����ļ�
		COPYVFSACT_IGNOREFILE,				// �����ļ�
		COPYVFSACT_COPYSUBDIR,				// ������Ŀ¼
		COPYVFSACT_DELETEITEM,				// ɾ������
		COPYVFSACT_SOURCEFAIL,				// Դ�ļ���ʧ��
		COPYVFSACT_TARGETFAIL,				// Ŀ���ļ���ʧ��
	};
	enum enumCOPYVFSCBRET
	{	COPYVFSCBRET_ACCEPT,				// ȷ�ϲ���
		COPYVFSCBRET_IGNORE,				// ���Բ���
		COPYVFSCBRET_ABORT,					// ��ֹ����
	};
	enum enumCOPYVFSRET
	{	COPYVFSRET_FINISH,					// �������
		COPYVFSRET_ABORT,					// ���Ʊ�ȡ��
		COPYVFSRET_ERROR,					// ���Ʊ���ֹ
	};
public:
	// �������ļ�ϵͳ֮�����Ŀ¼����
	typedef DWORD (*PFNCPVFSCALLBACK)(CVFS* pFrom,CVFS* pTo,LPVFSITEMINFO lpVFSItemInfo,DWORD dwAct,DWORD dwCallBackParam);
	virtual DWORD CopyVFSDir(CVFS* pTo,DWORD dwCopyOpt,PFNCPVFSCALLBACK pfnCpVfsCallback,DWORD dwCallBackParam);
	virtual BOOL CopyVFSFile(CVFS* pTo,LPCTSTR lpszFromDir,LPCTSTR lpszFromName,LPCTSTR lpszToDir,LPCTSTR lpszToName);

	// �õ��ļ��е�ȫ����С(ȫ���ļ���С������LONG_MAX)
	// �ɹ�����ȫ���ļ��Ĵ�С
	// ʧ�ܷ���-1
	virtual LONG GetTotalSize(LPCTSTR lpszCurDir);

	// ����ָ���ļ����µ��ļ���Ŀ(�ļ�����������LONG_MAX)
	// �ɹ����ز��ҵ��ļ�����
	// ʧ�ܷ���-1
	virtual LONG FindItems(LPCTSTR lpszCurDir,LPVFSITEMINFO& lpVFSItemInfos);

	// �������ļ�ϵͳ��ָ���ļ�
	// �ɹ����ؾ��
	// ʧ�ܷ���NULL
	virtual HVFSITEM OpenItem(LPCTSTR lpszCurDir,LPCTSTR lpszName,DWORD dwOpenMode);

	// ��ȡ�ļ�����
	// �ɹ������ļ�����
	// ʧ�ܷ���-1
	virtual LONG GetItemLength(HVFSITEM hVFSItem);

	// �����ļ�����
	// �ɹ�����TRUE
	// ʧ�ܷ���FALSE
	virtual BOOL SetItemLength(HVFSITEM hVFSItem,LONG nLength);

	// �ƶ��ļ�ָ��
	// �ɹ�����0
	// ʧ�ܷ��ط�0
	virtual LONG SeekItem(HVFSITEM hVFSItem,LONG nOffset,LONG nOrigin);

	// �����ļ�ָ��
	// �ɹ������ļ�ָ��
	// ʧ�ܷ���-1
	virtual LONG TellItem(HVFSITEM hVFSItem);

	// ��ȡ�ļ�
	// �ɹ����ض�ȡ���ֽ���
	// ʧ�ܷ���-1
	virtual LONG ReadItem(HVFSITEM hVFSItem,LPBYTE lpBuffer,LONG nLength);

	// д���ļ�
	// �ɹ�����д����ֽ���
	// ʧ�ܷ���-1
	virtual LONG WriteItem(HVFSITEM hVFSItem,LPCBYTE lpBuffer,LONG nLength);

	// �ر��ļ�
	virtual VOID CloseItem(HVFSITEM hVFSItem);

	// �����ļ�
	// �ɹ�����д�볤��
	// ʧ�ܷ���-1
	virtual LONG PutItem(LPCTSTR lpszCurDir,LPCTSTR lpszName,LPBYTE lpBuffer,LONG nLength,time_t tLastModify);
	
	// ȡ���ļ�
	// �ɹ�д���ļ�����д�볤��
	// �ɹ���ȡ��Ϣ����0
	// ʧ�ܷ���-1
	virtual LONG GetItem(LPCTSTR lpszCurDir,LPCTSTR lpszName,LPBYTE lpBuffer,LONG& nLength,time_t& tLastModify);

	// ɾ���ļ������ļ���,�������Ϊ��,��ɾ��Ŀ¼�µ�ȫ���Ӷ���
	// �ɹ�����TRUE
	// ʧ�ܷ���FALSE
	virtual BOOL DeleteItems(LPCTSTR lpszCurDir,LPCTSTR lpszName);

	// ɾ���ļ������ļ���,�������Ϊ��,��ɾ��Ŀ¼�µ�ȫ���Ӷ���,����ֻ����ָ���Ķ����µĶ���
	// �ɹ�����TRUE
	// ʧ�ܷ���FALSE
	virtual BOOL DeleteItemsExclude(LPCTSTR lpszCurDir,LPCTSTR lpszDirName,LPTSTR* lpExclude);

	// ��������Ŀ¼
	// �ɹ�����TRUE
	// ʧ�ܷ���FALSE
	virtual BOOL CreateDirs(LPCTSTR lpszCurDir,LPCTSTR lpszName);

	// �õ�������Ϣ
	// �ɹ�����TRUE
	// ʧ�ܷ���FALSE
	virtual BOOL GetItemInfo(LPCTSTR lpszCurDir,LPCTSTR lpszName,LPVFSITEMINFO lpVFSItemInfo);

	// ���ö���ʱ��
	// �ɹ�����TRUE
	// ʧ�ܷ���FALSE
	virtual BOOL SetItemTime(LPCTSTR lpszCurDir,LPCTSTR lpszName,time_t tLastModify);

protected:
	virtual CVFS* CreateSubDirObj(LPCTSTR lpszCurDir);
	virtual VOID DestroySubDirObj(CVFS* pSubVFSObj);
public:
	VOID CreateFullPathString(LPTSTR lpszPath,LPCTSTR lpszCurDir,LPCTSTR lpszName,BOOL bDirectory);
	VOID JoinPathString(LPTSTR lpszPath,LPCTSTR lpszCurDir,LPCTSTR lpszName,BOOL bDirectory);
protected:
	BOOL CompareItemAttr(LPVFSITEMINFO lpItemInfo1,LPVFSITEMINFO lpItemInfo2);
	#ifdef PLATFORM_WINDOWS
		BOOL GMTTimeToFileTime(const time_t tTime,FILETIME* pFileTime);
		BOOL FileTimeToGMTTime(const FILETIME* pFileTime,time_t& tTime);
	#endif // PLATFORM_WINDOWS
protected:
	CHAR m_szRoot[MAX_VFSPATH];
	BOOL m_bUnixStyle;
	BOOL m_bCaseSensitive;
	CHAR m_cSpliter;
};



#ifdef VFSNET_USED
	//////////////////////////////////////////////////////////////////////////
	// �����ļ�ϵͳ����ͻ���
	// �����ļ�ϵͳ����
	typedef struct tagVFSREQ
	{	DWORD m_dwProt;							// Э���
		DWORD m_dwVer;							// Э��汾
		DWORD m_dwParamSize;					// �����������(��������������)
	} _PACKED VFSREQ;
	typedef VFSREQ* LPVFSREQ;
	// �����ļ�ϵͳӦ��
	typedef struct tagVFSANS
	{	DWORD m_dwProt;							// Э���
		DWORD m_dwVer;							// Э��汾
		DWORD m_dwRetSize;						// ����ֵ����(��������������)
	} _PACKED VFSANS;
	typedef VFSANS* LPVFSANS;
	// ��������������ļ�ϵͳ
	class LITEFILEIO_IMP CVFSNet : public CVFS
	{
	public:
		CVFSNet(LPCTSTR lpszRoot,BOOL bUnixStyle,SOCKET hSocket);
		virtual~CVFSNet();
		BOOL LoginVFSServer(LPCTSTR lpszUser,LPCTSTR lpszPass);
		BOOL LogoutVFSServer();
		SOCKET GetSocket();
	public:
		virtual LONG GetTotalSize(LPCTSTR lpszCurDir);
		virtual LONG FindItems(LPCTSTR lpszCurDir,LPVFSITEMINFO& lpVFSItemInfos);
		virtual HVFSITEM OpenItem(LPCTSTR lpszCurDir,LPCTSTR lpszName,DWORD dwOpenMode);
		virtual LONG GetItemLength(HVFSITEM hVFSItem);
		virtual BOOL SetItemLength(HVFSITEM hVFSItem,LONG nLength);
		virtual LONG SeekItem(HVFSITEM hVFSItem,LONG nOffset,LONG nOrigin);
		virtual LONG TellItem(HVFSITEM hVFSItem);
		virtual LONG ReadItem(HVFSITEM hVFSItem,LPBYTE lpBuffer,LONG nLength);
		virtual LONG WriteItem(HVFSITEM hVFSItem,LPCBYTE lpBuffer,LONG nLength);
		virtual VOID CloseItem(HVFSITEM hVFSItem);
		virtual LONG PutItem(LPCTSTR lpszCurDir,LPCTSTR lpszName,LPBYTE lpBuffer,LONG nLength,time_t tLastModify);
		virtual LONG GetItem(LPCTSTR lpszCurDir,LPCTSTR lpszName,LPBYTE lpBuffer,LONG& nLength,time_t& tLastModify);
		virtual BOOL DeleteItems(LPCTSTR lpszCurDir,LPCTSTR lpszName);
		virtual BOOL CreateDirs(LPCTSTR lpszCurDir,LPCTSTR lpszName);
		virtual BOOL GetItemInfo(LPCTSTR lpszCurDir,LPCTSTR lpszName,LPVFSITEMINFO lpVFSItemInfo);
		virtual BOOL SetItemTime(LPCTSTR lpszCurDir,LPCTSTR lpszName,time_t tLastModify);
	protected:
		virtual CVFS* CreateSubDirObj(LPCTSTR lpszCurDir);
		virtual VOID DestroySubDirObj(CVFS* pSubVFSObj);
	protected:
		enum enumVFSCALLERR { VFSCALLERR_NONE,VFSCALLERR_SENDFAIL,VFSCALLERR_RECVFAIL,VFSCALLERR_PROTMISS,VFSCALLERR_VERMISS };
		LONG VfsCall(DWORD dwProt,char* lpszParam,DWORD dwParamSize,LPVFSANS lpVfsAns,char** lppszRet,DWORD* pdwRetSize);
		LONG OnVfsCallFailed(int nVfsCallErr);
		int SendData(const void* lpBuf,int nBufLen);
		int ReceiveData(void* lpBuf,int nBufLen);
	protected:
		SOCKET m_hSocket;
	};
#endif


//////////////////////////////////////////////////////////////////////////
// �����ļ�ϵͳ
class LITEFILEIO_IMP CVFSImage : public CVFS
{
public:
	CVFSImage(LPCTSTR lpszRoot,CImageFS* pImageFS);
	virtual~CVFSImage();
public:
	virtual LONG GetTotalSize(LPCTSTR lpszCurDir);
	virtual LONG FindItems(LPCTSTR lpszCurDir,LPVFSITEMINFO& lpVFSItemInfos);
	virtual HVFSITEM OpenItem(LPCTSTR lpszCurDir,LPCTSTR lpszName,DWORD dwOpenMode);
	virtual LONG GetItemLength(HVFSITEM hVFSItem);
	virtual BOOL SetItemLength(HVFSITEM hVFSItem,LONG nLength);
	virtual LONG SeekItem(HVFSITEM hVFSItem,LONG nOffset,LONG nOrigin);
	virtual LONG TellItem(HVFSITEM hVFSItem);
	virtual LONG ReadItem(HVFSITEM hVFSItem,LPBYTE lpBuffer,LONG nLength);
	virtual LONG WriteItem(HVFSITEM hVFSItem,LPCBYTE lpBuffer,LONG nLength);
	virtual VOID CloseItem(HVFSITEM hVFSItem);
	virtual LONG PutItem(LPCTSTR lpszCurDir,LPCTSTR lpszName,LPBYTE lpBuffer,LONG nLength,time_t tLastModify);
	virtual LONG GetItem(LPCTSTR lpszCurDir,LPCTSTR lpszName,LPBYTE lpBuffer,LONG& nLength,time_t& tLastModify);
	virtual BOOL DeleteItems(LPCTSTR lpszCurDir,LPCTSTR lpszName);
	virtual BOOL CreateDirs(LPCTSTR lpszCurDir,LPCTSTR lpszName);
	virtual BOOL GetItemInfo(LPCTSTR lpszCurDir,LPCTSTR lpszName,LPVFSITEMINFO lpVFSItemInfo);
	virtual BOOL SetItemTime(LPCTSTR lpszCurDir,LPCTSTR lpszName,time_t tLastModify);
protected:
	virtual CVFS* CreateSubDirObj(LPCTSTR lpszCurDir);
	virtual VOID DestroySubDirObj(CVFS* pSubVFSObj);
protected:
	CImageFS* m_pImageFS;
};


#endif

