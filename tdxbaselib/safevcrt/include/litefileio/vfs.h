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

// 系统中全部关于镜像文件的访问控制
//	CVFS					// 本地文件系统
//		CVFSNet				// 基于网络的文件系统
//			SOCKET			//		基于SOCKET运行
//		CVFSImage			// 基于镜像的文件系统
//			CImageFS		//		提供镜像文件的支持
//			CAnyFile		//		提供数据访问的支持

// 虚拟文件对象句柄
typedef DWORD_PTR HVFSITEM;

// 最长的虚拟文件系统路径
#define MAX_VFSPATH	512

// 虚拟文件对象FAT结构
typedef struct tagVFSITEMINFO
{	CHAR	m_szName[MAX_VFSPATH];			// 对象路径
	LONG	m_nLength;						// 对象长度
	BOOL	m_bDirectory;					// 对象是否为目录
	time_t	m_tLastModify;					// 对象最后修改时间(精确到秒)
} _PACKED VFSITEMINFO;
typedef VFSITEMINFO* LPVFSITEMINFO;


// 虚拟文件系统类,支持WINDOWS和LINUX
// 支持网络访问
class LITEFILEIO_IMP CVFS
{
public:
	CVFS(LPCTSTR lpszRoot,BOOL bUnixStyle);
	virtual~CVFS();
	enum enumCOPYOPT
	{	COPYOPT_DELNOTEXIST	= 0X00000001,	// 清除不存在文件
		COPYOPT_APPENDNEW	= 0X00000002,	// 写入新文件
		COPYOPT_UPDATEFORCE	= 0X00000004,	// 更新全部旧文件
		COPYOPT_UPDATECHGED	= 0X00000008,	// 仅仅更新被修改过的文件
		COPYOPT_TOUPPER		= 0X00000010,	// 文件名转换为大写
		COPYOPT_TOLOWER		= 0X00000020,	// 文件名转换为小写
		COPYOPT_DELETESRC	= 0X00000040,	// 删除源文件
		COPYOPT_NODIR		= 0X00000080,	// 忽略目录
	};
	enum enumOPENMODE
	{	VFSOPENMODE_RD	= 0X00000001,		// 以只读方式打开
		VFSOPENMODE_WR	= 0X00000002,		// 以只写方式打开
		VFSOPENMODE_RW	= 0X00000003,		// 以读写方式打开
	};
	enum enumSEEKORG
	{	VFSSEEK_END,						// 从尾部位置移动
		VFSSEEK_CUR,						// 从当前位置移动
		VFSSEEK_SET,						// 从开始位置移动
	};
	enum enumCOPYVFSACT
	{	COPYVFSACT_CREATEFILE,				// 创建文件
		COPYVFSACT_UPDATEFILE,				// 更新文件
		COPYVFSACT_IGNOREFILE,				// 忽略文件
		COPYVFSACT_COPYSUBDIR,				// 复制子目录
		COPYVFSACT_DELETEITEM,				// 删除对象
		COPYVFSACT_SOURCEFAIL,				// 源文件打开失败
		COPYVFSACT_TARGETFAIL,				// 目标文件打开失败
	};
	enum enumCOPYVFSCBRET
	{	COPYVFSCBRET_ACCEPT,				// 确认操作
		COPYVFSCBRET_IGNORE,				// 忽略操作
		COPYVFSCBRET_ABORT,					// 中止操作
	};
	enum enumCOPYVFSRET
	{	COPYVFSRET_FINISH,					// 复制完成
		COPYVFSRET_ABORT,					// 复制被取消
		COPYVFSRET_ERROR,					// 复制被中止
	};
public:
	// 在虚拟文件系统之间进行目录复制
	typedef DWORD (*PFNCPVFSCALLBACK)(CVFS* pFrom,CVFS* pTo,LPVFSITEMINFO lpVFSItemInfo,DWORD dwAct,DWORD dwCallBackParam);
	virtual DWORD CopyVFSDir(CVFS* pTo,DWORD dwCopyOpt,PFNCPVFSCALLBACK pfnCpVfsCallback,DWORD dwCallBackParam);
	virtual BOOL CopyVFSFile(CVFS* pTo,LPCTSTR lpszFromDir,LPCTSTR lpszFromName,LPCTSTR lpszToDir,LPCTSTR lpszToName);

	// 得到文件夹的全部大小(全部文件大小不超过LONG_MAX)
	// 成功返回全部文件的大小
	// 失败返回-1
	virtual LONG GetTotalSize(LPCTSTR lpszCurDir);

	// 查找指定文件夹下的文件项目(文件个数不超过LONG_MAX)
	// 成功返回查找到文件个数
	// 失败返回-1
	virtual LONG FindItems(LPCTSTR lpszCurDir,LPVFSITEMINFO& lpVFSItemInfos);

	// 在虚拟文件系统打开指定文件
	// 成功返回句柄
	// 失败返回NULL
	virtual HVFSITEM OpenItem(LPCTSTR lpszCurDir,LPCTSTR lpszName,DWORD dwOpenMode);

	// 获取文件长度
	// 成功返回文件长度
	// 失败返回-1
	virtual LONG GetItemLength(HVFSITEM hVFSItem);

	// 设置文件长度
	// 成功返回TRUE
	// 失败返回FALSE
	virtual BOOL SetItemLength(HVFSITEM hVFSItem,LONG nLength);

	// 移动文件指针
	// 成功返回0
	// 失败返回非0
	virtual LONG SeekItem(HVFSITEM hVFSItem,LONG nOffset,LONG nOrigin);

	// 返回文件指针
	// 成功返回文件指针
	// 失败返回-1
	virtual LONG TellItem(HVFSITEM hVFSItem);

	// 读取文件
	// 成功返回读取的字节数
	// 失败返回-1
	virtual LONG ReadItem(HVFSITEM hVFSItem,LPBYTE lpBuffer,LONG nLength);

	// 写入文件
	// 成功返回写入的字节数
	// 失败返回-1
	virtual LONG WriteItem(HVFSITEM hVFSItem,LPCBYTE lpBuffer,LONG nLength);

	// 关闭文件
	virtual VOID CloseItem(HVFSITEM hVFSItem);

	// 复制文件
	// 成功返回写入长度
	// 失败返回-1
	virtual LONG PutItem(LPCTSTR lpszCurDir,LPCTSTR lpszName,LPBYTE lpBuffer,LONG nLength,time_t tLastModify);
	
	// 取得文件
	// 成功写入文件返回写入长度
	// 成功获取信息返回0
	// 失败返回-1
	virtual LONG GetItem(LPCTSTR lpszCurDir,LPCTSTR lpszName,LPBYTE lpBuffer,LONG& nLength,time_t& tLastModify);

	// 删除文件或者文件夹,如果名称为空,则删除目录下得全部子对象
	// 成功返回TRUE
	// 失败返回FALSE
	virtual BOOL DeleteItems(LPCTSTR lpszCurDir,LPCTSTR lpszName);

	// 删除文件或者文件夹,如果名称为空,则删除目录下得全部子对象,否则只包括指定的对象下的对象
	// 成功返回TRUE
	// 失败返回FALSE
	virtual BOOL DeleteItemsExclude(LPCTSTR lpszCurDir,LPCTSTR lpszDirName,LPTSTR* lpExclude);

	// 创建虚拟目录
	// 成功返回TRUE
	// 失败返回FALSE
	virtual BOOL CreateDirs(LPCTSTR lpszCurDir,LPCTSTR lpszName);

	// 得到对象信息
	// 成功返回TRUE
	// 失败返回FALSE
	virtual BOOL GetItemInfo(LPCTSTR lpszCurDir,LPCTSTR lpszName,LPVFSITEMINFO lpVFSItemInfo);

	// 设置对象时间
	// 成功返回TRUE
	// 失败返回FALSE
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
	// 虚拟文件系统网络客户端
	// 虚拟文件系统请求
	typedef struct tagVFSREQ
	{	DWORD m_dwProt;							// 协议号
		DWORD m_dwVer;							// 协议版本
		DWORD m_dwParamSize;					// 送入参数长度(后续缓冲区长度)
	} _PACKED VFSREQ;
	typedef VFSREQ* LPVFSREQ;
	// 虚拟文件系统应答
	typedef struct tagVFSANS
	{	DWORD m_dwProt;							// 协议号
		DWORD m_dwVer;							// 协议版本
		DWORD m_dwRetSize;						// 返回值长度(后续缓冲区长度)
	} _PACKED VFSANS;
	typedef VFSANS* LPVFSANS;
	// 基于网络的虚拟文件系统
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
// 镜像文件系统
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

