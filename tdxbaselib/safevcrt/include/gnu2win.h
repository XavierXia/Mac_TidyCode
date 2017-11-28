#ifndef __GNU_2_WIN__H__
#define __GNU_2_WIN__H__
#if defined(_COMPILE_BY_GCC_)
#define __SAFE_VCRT_TYPES__H__
#if !defined(__SAFE_VCRT__H__) || !defined(__SAFE_VCRT_OS__H__) 
#error safevcrt.h must be included
#endif

// ���Ժ���
#define TRACE	CLIBTRACE
#define ASSERT	CLIBASSERT
#define VERIFY	CLIBVERIFY
SAFEVCRT_IMP VOID OutputDebugString(LPCSTR lpOutputString);
SAFEVCRT_IMP BOOL IsBadReadPtr(LPCVOID lp,UINT ucb);
SAFEVCRT_IMP BOOL IsBadWritePtr(LPCVOID lp,UINT ucb);
SAFEVCRT_IMP BOOL GetLastError();

// ϵͳ�ͻ�����������
SAFEVCRT_IMP DWORD GetTickCount();
SAFEVCRT_IMP BOOL GetComputerName(LPSTR lpBuffer,LPDWORD pnSize);
SAFEVCRT_IMP BOOL GetUserName(LPSTR lpBuffer,LPDWORD pnSize);
SAFEVCRT_IMP BOOL SetEnvironmentVariable(LPCSTR lpName,LPCSTR lpValue);
SAFEVCRT_IMP DWORD GetEnvironmentVariable(LPCSTR lpName,LPSTR lpBuffer,DWORD nSize);


// ����������
SAFEVCRT_IMP LONG InterlockedCompareExchange(LONG volatile *Target,LONG Value,LONG compare);
SAFEVCRT_IMP LONG InterlockedExchange(LONG volatile *Target,LONG Value);
SAFEVCRT_IMP LONG InterlockedExchangeAdd(LONG volatile *Target,LONG Value);
SAFEVCRT_IMP LONG InterlockedIncrement(LONG volatile *Target);
SAFEVCRT_IMP LONG InterlockedDecrement(LONG volatile *Target);




// �ٽ�������
typedef pthread_mutex_t CRITICAL_SECTION,*LPCRITICAL_SECTION;
SAFEVCRT_IMP VOID InitializeCriticalSection(LPCRITICAL_SECTION lpCriticalSection);
SAFEVCRT_IMP VOID EnterCriticalSection(LPCRITICAL_SECTION lpCriticalSection);
SAFEVCRT_IMP VOID LeaveCriticalSection(LPCRITICAL_SECTION lpCriticalSection);
SAFEVCRT_IMP VOID DeleteCriticalSection(LPCRITICAL_SECTION lpCriticalSection);


// ���ߴ���
#define	Sleep(dwMilliseconds)	usleep(dwMilliseconds*1000)


// ��̬�����
SAFEVCRT_IMP HMODULE LoadLibrary(LPCSTR lpLibFileName);
SAFEVCRT_IMP BOOL FreeLibrary(HMODULE hLibModule);
typedef int (CALLBACK *FARPROC)();
SAFEVCRT_IMP FARPROC GetProcAddress(HMODULE hLibModule,LPCSTR lpProcName);
SAFEVCRT_IMP DWORD GetModuleFileName(HMODULE hLibModule,LPSTR lpFilename,DWORD nSize);


// �ļ�����(C���п�)
#define _A_NORMAL	0x00    // �ļ�
#define _A_SUBDIR	0x10    // Ŀ¼
struct _finddata_t {
    unsigned    attrib;
    time_t      time_create;
    time_t      time_access;
    time_t      time_write;
    size_t		size;
    char        name[260];
};
SAFEVCRT_IMP INT_PTR _findfirst(const char* filespec,struct _finddata_t* fileinfo);
SAFEVCRT_IMP int _findnext(INT_PTR handle,struct _finddata_t * fileinfo);
SAFEVCRT_IMP int _findclose(INT_PTR handle);


// �ļ�����(API)
#define FILE_ATTRIBUTE_READONLY			0x00000001		// ֻ������
#define FILE_ATTRIBUTE_HIDDEN			0x00000002		// ��������
#define FILE_ATTRIBUTE_SYSTEM			0x00000004		// ϵͳ����
#define FILE_ATTRIBUTE_DIRECTORY		0x00000010		// Ŀ¼����
#define FILE_ATTRIBUTE_NORMAL			0x00000080		// �ļ�����
typedef time_t FILETIME,*LPFILETIME;
typedef struct _WIN32_FIND_DATAA {
    DWORD dwFileAttributes;
    CHAR  cFileName[MAX_PATH];
	DWORD nFileSizeHigh;
    DWORD nFileSizeLow;
	FILETIME ftCreationTime;
    FILETIME ftLastAccessTime;
    FILETIME ftLastWriteTime;
} WIN32_FIND_DATA,*LPWIN32_FIND_DATA;
SAFEVCRT_IMP HANDLE FindFirstFile(LPCSTR lpFileName,LPWIN32_FIND_DATA lpFindFileData);
SAFEVCRT_IMP BOOL FindNextFile(HANDLE hFindFile,LPWIN32_FIND_DATA lpFindFileData);
SAFEVCRT_IMP BOOL FindClose(HANDLE hFindFile);



// �ļ�ʱ��ת��
typedef struct _SYSTEMTIME {
    WORD wYear;
    WORD wMonth;
    WORD wDayOfWeek;
    WORD wDay;
    WORD wHour;
    WORD wMinute;
    WORD wSecond;
    WORD wMilliseconds;
} SYSTEMTIME, *PSYSTEMTIME, *LPSYSTEMTIME;
SAFEVCRT_IMP VOID GetLocalTime(LPSYSTEMTIME lpSystemTime);
SAFEVCRT_IMP BOOL SystemTimeToFileTime(CONST SYSTEMTIME *lpSystemTime,LPFILETIME lpFileTime);
SAFEVCRT_IMP BOOL LocalFileTimeToFileTime(CONST FILETIME *lpLocalFileTime,LPFILETIME lpFileTime);


// �ļ����Բ���
SAFEVCRT_IMP DWORD GetFileAttributes(LPCSTR lpFileName);
SAFEVCRT_IMP BOOL SetFileAttributes(LPCSTR lpFileName,DWORD dwFileAttributes);

// Ŀ¼����
SAFEVCRT_IMP BOOL CreateDirectory(LPCSTR lpPathName,LPVOID pUnused);
SAFEVCRT_IMP BOOL RemoveDirectory(LPCSTR lpPathName);

// �ļ�����
SAFEVCRT_IMP BOOL CopyFile(LPCSTR lpExistingFileName,LPCSTR lpNewFileName,BOOL bFailIfExists);
SAFEVCRT_IMP BOOL DeleteFile(LPCSTR lpFileName);

// �ļ�����
#ifndef S_IREAD
	#define S_IREAD       0400
	#define S_IWRITE      0200
	#define S_IEXEC       0100
#endif


#define	_fsopen(a,b,c)				fopen(a,b)
#define	sopen(a,b,c)				open(a,b)
#define _locking(a,b,c)				flock(a,b)
#define tell(a)						lseek(a,0,SEEK_CUR)
#define chsize(handle,length)		ftruncate(handle,length)
#define _chsize(handle,length)		ftruncate(handle,length)
#define _LK_NBLCK					LOCK_EX
#define _LK_UNLCK					LOCK_UN
#define O_BINARY					(0)
#define _O_BINARY					O_BINARY
#define _O_RDONLY					O_RDONLY
#define _O_WRONLY					O_WRONLY
#define _O_RDWR						O_RDWR
#define _O_APPEND					O_APPEND
#define _O_CREAT					O_CREAT
#define _O_TRUNC					O_TRUNC
#define _O_EXCL						O_EXCL
#define _O_TEXT						O_TEXT
#define _S_IFDIR					(S_IFDIR)		// Ŀ¼�ļ�����
#define _S_IFREG					(S_IFREG)		// ��ͨ�ļ�����
#define _S_IREAD					(S_IREAD)		// �����ߵĶ�Ȩ��
#define _S_IWRITE					(S_IWRITE)		// �����ߵ�дȨ��
#define _S_IEXEC					(S_IEXEC)		// �����ߵ�ִ�С�����Ȩ��
#define _stat						stat
#define _access						access
#define _filelength(a)				filelength(a)
SAFEVCRT_IMP long filelength(int fn);



// ��ɫ����
typedef DWORD COLORREF;
#define GetRValue(rgb)				((BYTE)(rgb))
#define GetGValue(rgb)      		((BYTE)(((WORD)(rgb)) >> 8))
#define GetBValue(rgb)      		((BYTE)((rgb)>>16))
#define RGB(r,g,b)          		((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))














































// ����ҳת��
// ���ֽ�֧��
// BUGBUG: ���ֽ�֧����Ҫȥ��!!!
#define CP_ACP							0
#define CP_UTF8							65001
#define CP_UTF7							65000
#define LANG_CHINESE					0x04
#define MAKELANGID(p,s)					((((WORD)(s)) << 10) | (WORD)(p))
#define PRIMARYLANGID(lgid)				((WORD)(lgid) & 0x3ff)
#define SUBLANGID(lgid)					((WORD)(lgid) >> 10)
#define SUBLANG_CHINESE_SIMPLIFIED		0x02
#define SORT_CHINESE_BIG5               0x0
#define SORT_CHINESE_PRC				0x2
#define LCMAP_SIMPLIFIED_CHINESE		0x02000000
#define LCMAP_TRADITIONAL_CHINESE		0x04000000
#define MAKELCID(lgid, srtid)			((DWORD)((((DWORD)((WORD)(srtid)))<<16)|((DWORD)((WORD)(lgid)))))
typedef DWORD LCID;
SAFEVCRT_IMP int LCMapString(LCID Locale,DWORD dwMapFlags,LPCSTR lpSrcStr,int cchSrc,LPSTR lpDestStr,int cchDest);
SAFEVCRT_IMP int WideCharToMultiByte(UINT CodePage,DWORD dwFlags,LPCWSTR lpWideCharStr,int cchWideChar,LPSTR lpMultiByteStr,int cbMultiByte,LPCSTR lpDefaultChar,LPBOOL lpUsedDefaultChar);
SAFEVCRT_IMP int MultiByteToWideChar(UINT CodePage,DWORD dwFlags,LPCSTR lpMultiByteStr,int cbMultiByte,LPWSTR lpWideCharStr,int cchWideChar);


// �ַ�������
SAFEVCRT_IMP char* strupr(char* pszStr);
SAFEVCRT_IMP char* strlwr(char* pszStr);
SAFEVCRT_IMP char* strrev(char* pszStr);
SAFEVCRT_IMP char* strinc(const char* pszStr);




// �������
typedef enum tagCOINIT
{	COINIT_APARTMENTTHREADED  = 0x2,
	COINIT_MULTITHREADED      = 0x0,
	COINIT_DISABLE_OLE1DDE    = 0x4,
	COINIT_SPEED_OVER_MEMORY  = 0x8,
} COINIT;
SAFEVCRT_IMP HRESULT CoInitializeEx(LPVOID pvReserved,DWORD dwCoInit);
SAFEVCRT_IMP HRESULT CoInitialize(LPVOID pvReserved);
SAFEVCRT_IMP VOID CoUninitialize();

#define ZeroMemory(p,z)	memset(p,0,z)

#endif
#endif
