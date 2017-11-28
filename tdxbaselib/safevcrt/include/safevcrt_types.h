//////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2006 - All Rights Reserved
//  模块名称: SafeVCRT(常用类型定义)
//  创建日期: 2006/07/28
//  代码编写: zhanglijun
//  功能说明: 安全的VC运行库
//            当前库主要封装VCRT/STD_C++库的常用操作,为了应对广泛采用中的带来的交叉关联问题
// 
// 字长列表
// ===========================================================================================================================
//	类型		WIN32	WIN64	RHEL32	RHEL64	FREEBSD32 FREEBSD64 MacOSX32 MacOSX64 Android iPhoneOS	iPhoneSimulator
//	void*		4		8		4		8		4		  8			4		 8		  4		  4			4
//	short		2		2		2		2		2		  2			2		 2		  2		  2			2
//	long		4		4		4		8		4		  8			4		 8		  4		  4			4
//	int			4		4		4		4		4		  4			4		 4		  4		  4			4
//	long int	4		4		4		8		4		  8			4		 8		  4		  4			4
//	long long	8		8		8		8		8		  8			8		 8		  8		  8			8
//	size_t		4		8		4		8		4		  8			4		 8		  4		  4			4	
//
//	INT			4
//	INT64		8
//	SHORT		2
//	WORD		2
//	LONG		4
//	DWORD		4
//

// ===========================================================================================================================
//	平台		WIN32	WIN64	RHEL32	RHEL64	FREEBSD32 FREEBSD64 MacOSX32 MacOSX64 Android iPhoneOS	iPhoneSimulator
//	支持列表	YES		YES		YES		YES		YES		  YES		YES		 YES	  YES	  YES		YES
// 
//	模式		API		COM		JNI
//				YES		YES		YES


//  引用示例: 
//  修改记录:
//////////////////////////////////////////////////////////////////////////
#ifndef __SAFE_VCRT_TYPES__H__
#define __SAFE_VCRT_TYPES__H__
#if !defined(__SAFE_VCRT__H__) || !defined(__SAFE_VCRT_OS__H__) 
	#error safevcrt.h must be included
#endif

// 调试版本支持
#ifdef _DEBUG
	#ifndef DEBUG
		#define DEBUG
	#endif
	#ifndef TDX_DEBUG
		#define TDX_DEBUG
	#endif
#endif

// BOOL类型宏定义
#ifndef TRUE
	#define TRUE	1
	#define FALSE	0
#endif

// 空指针定义
#ifndef NULL
	#define NULL	0
#endif

// 入参出参定义
#ifndef IN
	#define IN
#endif
#ifndef OUT
	#define OUT
#endif
#ifndef INOUT
	#define INOUT
#endif
#ifndef PURE
	#define PURE = 0
#endif
#ifndef ASYNCLOCK
	#define ASYNCLOCK
#endif
#ifndef VOLATILE
	#define VOLATILE
#endif
#ifndef INTERNAL
	#define INTERNAL
#endif

// ANSI_C++标准返回值类型
#ifndef ESUCCESS
	#define ESUCCESS (0)
#endif
#ifndef EUNKNOWN
	#define EUNKNOWN (-1)
#endif

// 其他辅助宏定义
#ifndef UNUSED_ALWAYS
	#if defined(PLATFORM_WINDOWS)
		#define UNUSED_ALWAYS(X) (x)
	#else
		#define UNUSED_ALWAYS(X)
	#endif
#endif
#ifndef UNREFERENCED_PARAMETER
	#if defined(PLATFORM_WINDOWS)
		#define UNREFERENCED_PARAMETER(x) (x)
	#else
		#define UNREFERENCED_PARAMETER(x) 
	#endif
#endif

// 对齐方式
#ifdef PLATFORM_WINDOWS
	#define _PACKED
#else
	#define _PACKED	__attribute__((packed))
#endif


// 多字节字符串声明
#define _ANSI(psz)	(psz)
#define _MSG(psz)	(psz)


// 基本类型定义
#if defined(PLATFORM_WINDOWS)
	typedef unsigned __int64 __uint64;
	typedef size_t ssize_t;
	typedef int socklen_t;
	typedef int mode_t;
#else
	// int64扩展
	typedef long long __int64;
	typedef unsigned long long __uint64;

	// 常量类型
	#ifndef CONST
		#define CONST	const
	#endif

	// 空类型
	#ifndef VOID
		#define VOID void
	#endif
	typedef void *LPVOID,*PVOID;
	typedef CONST void *LPCVOID,*PCVOID;

	// 逻辑类型
	#if defined(PLATFORM_IOS)
		typedef signed char BOOL;
	#else
		typedef int BOOL;
	#endif
	typedef BOOL *LPBOOL,*PBOOL;

	// 字符类型
	typedef char CHAR;
	typedef CHAR *LPSTR,*PSTR;
	typedef CONST CHAR *LPCSTR,*PCSTR;

	// 宽字符类型
	typedef wchar_t WCHAR;
	typedef WCHAR *LPWSTR,*PWSTR;
	typedef CONST WCHAR *LPCWSTR,*PCWSTR;

	// FLOAT/DOUBLE类型
	typedef float FLOAT;
	typedef FLOAT *PFLOAT;
	typedef double DOUBLE;
	typedef DOUBLE *PDOUBLE;

	// BYTE/WORD/DWORD类型
	typedef unsigned char BYTE;
	typedef unsigned char UCHAR;
	typedef BYTE *PBYTE,*LPBYTE;
	typedef unsigned short WORD;
	typedef WORD *PWORD,*LPWORD;
	typedef unsigned int DWORD;
	typedef DWORD *PDWORD,*LPDWORD;

	// INT类型
	typedef int INT;
	typedef INT *PINT,*LPINT;
	typedef unsigned int UINT;
	typedef UINT *PUINT,*LPUINT;

	// SHORT/USHORT/LONG/ULONG类型
	typedef short SHORT;
	typedef SHORT *PSHORT;
	typedef unsigned short USHORT;
	typedef USHORT *PUSHORT;
	typedef int LONG;
	typedef unsigned int ULONG;
	typedef LONG *PLONG,*LPLONG;
	typedef ULONG *PULONG,*LPULONG;

	// LONG32/ULONG32/LONG64/ULONG64类型
	typedef int LONG32;
	typedef unsigned int ULONG32;
	typedef __int64 LONG64;
	typedef __uint64 ULONG64;

	// INT8/INT16/INT32/INT64类型
	typedef int INT32;
	typedef INT32 *PINT32;
	typedef __int64 INT64;
	typedef INT64 *PINT64;

	// UINT8/UINT16/UINT32/UINT64类型
	typedef unsigned int UINT32;
	typedef UINT32 *PUINT32;
	typedef __uint64 UINT64;
	typedef UINT64 *PUINT64;

	// SOCKET类型
	typedef struct sockaddr_in SOCKADDR_IN;
	typedef struct sockaddr_in* LPSOCKADDR_IN;
	typedef struct sockaddr_in6 SOCKADDR_IN6;
	typedef struct sockaddr_in6* LPSOCKADDR_IN6;
	typedef struct hostent HOSTENT;
	typedef struct hostent* LPHOSTENT;
	typedef struct in_addr IN_ADDR;
	typedef struct in_addr* LPIN_ADDR;
	typedef struct sockaddr* LPSOCKADDR;
	typedef struct sockaddr SOCKADDR;
	typedef int SOCKET;

	// 文件偏移
	typedef long _off_t;

	// 句柄定义
	typedef long HRESULT;
	typedef void* HANDLE,*PHANDLE,*LPHANDLE;
	typedef void* HMODULE;
	typedef void* HINSTANCE;
	typedef void* HWND;
	typedef struct hostent *PHOSTENT;

	// 其他类型
	typedef bool BOOLEAN;

	// 可和指针复用的字段
	#if defined(_ARCH_IA32_) || defined(_ARCH_ARM_)
		typedef int SIGNED_INTPTR;
		typedef unsigned int UNSIGNED_INTPTR;
	#else
		typedef long long SIGNED_INTPTR;
		typedef unsigned long long UNSIGNED_INTPTR;
	#endif
	typedef SIGNED_INTPTR INT_PTR;
	typedef UNSIGNED_INTPTR UINT_PTR;
	typedef SIGNED_INTPTR LONG_PTR;
	typedef UNSIGNED_INTPTR ULONG_PTR;
	typedef UNSIGNED_INTPTR* PULONG_PTR;
	typedef UNSIGNED_INTPTR DWORD_PTR;
	typedef UNSIGNED_INTPTR WPARAM;
	typedef UNSIGNED_INTPTR LPARAM;
	typedef UNSIGNED_INTPTR LRESULT;

	#define MAKEWORD(l, h)      ((WORD)(((BYTE)(l)) | ((WORD)((BYTE)(h))) << 8))
	#define MAKELONG(l, h)      ((LONG)(((WORD)(l)) | ((DWORD)((WORD)(h))) << 16))
	#define MAKEWPARAM(l, h)	((WPARAM)(DWORD)MAKELONG(l, h))
	#define MAKELPARAM(l, h)	((LPARAM)(DWORD)MAKELONG(l, h))
	#define MAKELRESULT(l, h)	((LRESULT)(DWORD)MAKELONG(l, h))
	#define LOWORD(l)           ((WORD)(l))
	#define HIWORD(l)           ((WORD)(((DWORD)(l) >> 16) & 0xFFFF))
	#define LOBYTE(w)           ((BYTE)(w))
	#define HIBYTE(w)           ((BYTE)(((WORD)(w) >> 8) & 0xFF))

	// TCHAR类型定义
	#ifdef UNICODE
		typedef WCHAR TCHAR;
		typedef LPCWSTR LPCTSTR;
		typedef LPWSTR LPTSTR;
		typedef WCHAR _TUCHAR;
		#define _T(x) L ## x
	#else
		typedef CHAR TCHAR;
		typedef LPCSTR LPCTSTR;
		typedef LPSTR LPTSTR;
		typedef UCHAR _TUCHAR;
		#define _T(x) (x)
	#endif

	// 系统GDI常用类型
	typedef struct tagPOINT
    {	LONG	x;
		LONG	y;
    } POINT,*PPOINT,*NPPOINT,*LPPOINT;
	typedef struct tagSIZE
	{	LONG	cx;
		LONG	cy;
	} SIZE, *PSIZE, *LPSIZE;
	typedef struct tagRECT
	{	LONG	left;
		LONG    top;
		LONG    right;
		LONG    bottom;
	} RECT,*PRECT,*NPRECT,*LPRECT;

	// GUID和IID相关定义
	typedef struct tagGUID
	{	unsigned int Data1;
		unsigned short Data2;
		unsigned short Data3;
		unsigned char Data4[8];
	} GUID;
	typedef GUID IID;
	inline int IsEqualGUID(const GUID& rguid1, const GUID& rguid2) { return !memcmp(&rguid1,&rguid2,sizeof(GUID)); }
	inline int operator==(const GUID& guidOne,const GUID& guidOther) { return IsEqualGUID(guidOne,guidOther); }



	// 接口类型
	#define interface struct
#endif
#ifndef interface
	#define interface struct
#endif
#define STDTYPE_DEFINED


// BYTE/LPCVOID/FLAG
typedef const unsigned char* LPCBYTE;
typedef const void* LPCVOID;
typedef CHAR FLAG;

// FLOAT/DOUBLE类型定义
typedef FLOAT *LPFLOAT;
// SHORT类型定义
typedef SHORT *LPSHORT;
typedef USHORT *LPUSHORT;
// LONG32/ULONG32/LONG64/ULONG64类型定义
typedef LONG32 *LPLONG32;
typedef ULONG32 *LPULONG32;
typedef LONG64 *LPLONG64;
typedef ULONG64 *LPULONG64;
// INT8/INT16/INT32/INT64类型定义
typedef signed char INT8;
typedef INT8 *PINT8,*LPINT8;
typedef short INT16;
typedef INT16 *PINT16,*LPINT16;
typedef INT32 *LPINT32;
typedef INT64 *LPINT64;
// UINT8/UINT16/UINT32/UINT64类型定义
typedef unsigned char UINT8;
typedef UINT8 *PUINT8,*LPUINT8;
typedef unsigned short UINT16;
typedef UINT16 *PUINT16,*LPUINT16;
typedef UINT32 *LPUINT32;
typedef UINT64 *LPUINT64;
// POINTER/UINT2/UINT4定义
typedef unsigned char*	   POINTER;
typedef unsigned short int UINT2;
typedef unsigned int	   UINT4;
// LONGINT定义
typedef long int LONGINT;
typedef unsigned long int ULONGINT;
// LBOOL
#ifndef LBOOL
	#if defined(PLATFORM_IOS)
		#define LBOOL LONG
	#else
		#define LBOOL BOOL
	#endif
#endif


// 带宽度的类型(参阅: ASEStdDef.h)
#ifndef SIZED_TYPE
#define SIZED_TYPE
	// int8/int16/int32/int64/uint8/uint16/uint32/uint64定义
	typedef char              int8;
	typedef short             int16;
	typedef int               int32;
	typedef __int64           int64;
	typedef unsigned char     uint8;
	typedef unsigned short    uint16;
	typedef unsigned int      uint32;
	typedef __uint64		  uint64;
	// byte/word8/word16/word32/word64定义
	typedef unsigned char     byte;
	typedef unsigned char     word8;
	typedef unsigned short    word16;
	typedef unsigned int      word32;
	typedef __uint64          word64;
#endif


// 位置定义(参阅: ASEStdDef.h)
#ifndef BEFORE_START_POSITION
	struct __POSITION {};
	typedef __POSITION* POSITION;
	#define BEFORE_START_POSITION ((POSITION)-1L)
#endif

// 时间定义(参阅: ASEStdDef.h)
#ifndef SYSTM_T
#define SYSTM_T
	typedef int64 systm_t;
#endif



#define MAKEINT64(LO,HI) (((INT64)(LO))|(((INT64)(HI))<<32))
#define LODWORD(I64)	 ((DWORD)(I64))
#define HIDWORD(I64)	 ((DWORD)((I64)>>32))

#ifndef min_of
	#define min_of(a,b) ((a)<(b)?(a):(b))
#endif
#ifndef MIN
	#define MIN(a,b) ((a)<(b)?(a):(b))
#endif
#ifndef min
	#define min MIN
#endif

#ifndef max_of
	#define max_of(a,b) ((a)>(b)?(a):(b))
#endif
#ifndef MAX
	#define MAX(a,b) ((a)>(b)?(a):(b))
#endif
#ifndef max
	#define max MAX
#endif

#ifndef size_of
	#define size_of(a)			((DWORD)sizeof(a))
#endif
#ifndef ARRAYSIZE
	#define SIZEOF(a)			((DWORD)sizeof(a))
	#define ARRAYSIZE(a)		((DWORD)((sizeof(a)/sizeof(a[0]))))
#endif

#ifndef MEMBER_OFFSET
	#define MEMBER_OFFSET(theClass,theMember) ((DWORD)&((theClass*)0)->theMember)
#endif
#ifndef MEMBER_SIZE
	#define MEMBER_SIZE(theClass,theMember) size_of(((theClass*)0)->theMember)
#endif

#ifndef offset_of
	#define offset_of(s,m)		(size_t)&(((s*)0)->m)
#endif

#ifndef ex_offset_of
	#define ex_offset_of(s,m)	((size_t)&(((s*)0x8)->m)-0x8)
#endif

#if defined(_COMPILE_BY_GCC_)

	#ifndef FAR
		#define FAR
	#endif
	#ifndef PASCAL
		#define PASCAL
	#endif
	#ifndef CALLBACK
		#define CALLBACK
	#endif
	#ifndef WINAPI
		#define WINAPI
	#endif

	#ifndef MAX_PATH
		#define MAX_PATH  260
	#endif
#endif

// size_t最大值
#ifndef BYTE_MAX
	#define BYTE_MAX	(0XFF)
#endif
#ifndef WORD_MAX
	#define WORD_MAX	(0XFFFF)
#endif
#ifndef UINT_MAX
	#define UINT_MAX	(0XFFFFFFFF)
#endif
#ifndef DWORD_MAX
	#define DWORD_MAX	(0XFFFFFFFF)
#endif
#ifndef SIZE_T_MAX
	#define SIZE_T_MAX UINT_MAX
#endif

//========================================================================================================================
// URL相关长度
#define CLIBINET_MAX_HOST_NAME_LENGTH   256				// 站点名最大长度
#define CLIBINET_MAX_USER_NAME_LENGTH   128				// 用户名最大长度
#define CLIBINET_MAX_PASSWORD_LENGTH    128				// 密码最大长度
#define CLIBINET_MAX_DOMAIN_LENGTH		128				// 域名称最大长度
#define CLIBINET_MAX_PORT_NUMBER_LENGTH 5				// 端口号最大长度
#define CLIBINET_MAX_PORT_NUMBER_VALUE  65535			// 最大端口数
#define CLIBINET_MAX_PATH_LENGTH        2048			// 最大路径深度
#define CLIBINET_MAX_SCHEME_LENGTH      32				// 最大协议名长度
#define CLIBINET_MAX_URL_LENGTH         (CLIBINET_MAX_SCHEME_LENGTH+size_of("://")+CLIBINET_MAX_PATH_LENGTH)

// URL相关长度定义
#ifndef MAX_INET_URL_LEN
	#define MAX_INET_URL_LEN			CLIBINET_MAX_URL_LENGTH
	#define MAX_INET_PATH_LEN			CLIBINET_MAX_PATH_LENGTH
	#define MAX_INET_SCHEME_LEN			CLIBINET_MAX_SCHEME_LENGTH
	#define MAX_INET_HOSTNAME_LEN		CLIBINET_MAX_HOST_NAME_LENGTH
	#define MAX_INET_USERNAME_LEN		CLIBINET_MAX_USER_NAME_LENGTH
	#define MAX_INET_PASSWORD_LEN		CLIBINET_MAX_PASSWORD_LENGTH
	#define MAX_INET_DOMAIN_LEN			CLIBINET_MAX_DOMAIN_LENGTH
#endif


//========================================================================================================================
// PROXY的类型
const UINT PROXY_NONE					= 0;			// 不使用代理(支持所有协议)
const UINT PROXY_HTTPCONNECT			= 1;			// HTTP代理+HTTP_CONNECT方式(支持TCP应用的所有协议)
const UINT PROXY_SOCKS4					= 2;			// SOCKS4代理方式
const UINT PROXY_SOCKS4A				= 3;			// SOCKS4A代理方式
const UINT PROXY_SOCKS5					= 4;			// SOCKS5代理方式
const UINT PROXY_TDXPROXY1				= 5;			// 绿色通道方式(兼容版本)
const UINT PROXY_TDXPROXY2				= 6;			// 绿色通道方式(包过滤穿透)

//========================================================================================================================
// 基本常量定义
const LONG SOCKET_SUCCESS				= 0;			// SOCKET成功返回


//========================================================================================================================
// 缺省端口号
const USHORT INVALID_PORT_NUMBER		= 0;			// 无效端口
const USHORT DEFAULT_FTP_PORT 			= 21;			// 缺省FTP端口
const USHORT DEFAULT_GOPHER_PORT		= 70;			// 缺省GOPHER端口
const USHORT DEFAULT_HTTP_PORT 			= 80;			// 缺省HTTP端口
const USHORT DEFAULT_HTTPS_PORT 		= 443;			// 缺省HTTPS端口
const USHORT DEFAULT_SOCKS_PORT 		= 1080;			// 缺省SOCKS端口	




//========================================================================================================================
// 用户相关宏定义(参阅: ASEStdDef.h)
#ifndef UINFO_DEFINED
	#define UINFO_DEFINED
	#define AP_SIZE					(64)				// 64字节的AP信息
	#define UORG_DEFID				(0)					// 用户机构默认ID
	#define UORG_SIZE				(41)				// 用户机构最大长度
	#define UID_SIZE				(41)				// 用户帐号最大长度
	#define UNAME_SIZE				(41)				// 用户名称最大长度
	#define UID_GSIZE				(13)				// 用户帐号最大长度(全局,营业部代码使用WORD型)
#endif





// 加密级别(参阅: ASEStdProt_Header.h)
#ifndef ENCRYPTLV_DEFINED
	#define ENCRYPTLV_DEFINED
	typedef enum enumENCRYPTLV
	{	ENCRYPTLV_NONE,								// 加密级别: 不加密
		ENCRYPTLV_LL,								// 加密级别: 低级别,对称加密(服务器选择是否交换密钥)
		ENCRYPTLV_SSL,								// 加密级别: 高级别,SSL加密
	} ENCRYPTLV;
#endif

// 加密标志(参阅: ASEStdProt_Header.h)
#ifndef ENCRYPTTYPE_DEFINED
	#define ENCRYPTTYPE_DEFINED
	typedef enum enumENCRYPTTYPE
	{	ENCRYPTTYPE_NO,								// 未加密
		ENCRYPTTYPE_SESSION,						// 使用SESSION_KEY加密
		ENCRYPTTYPE_BLOWFISH,						// 使用BLOWFISH加密
		ENCRYPTTYPE_DES3,							// 使用DES3加密
	} ENCRYPTTYPE;
#endif


// 压缩模式(参阅: ASEStdProt_Header.h)
#ifndef COMPRESSMODE_DEFINED
	#define COMPRESSMODE_DEFINED
	typedef enum enumCOMPRESSMODE
	{	COMPRESS_NONE,								// 不做压缩
		COMPRESS_SMART,								// 智能压缩(大数据包压缩)
		COMPRESS_FULL,								// 完全压缩(全部事务均压缩)
	} COMPRESSMODE;
#endif


// 压缩类别(参阅: ASEStdProt_Header.h)
#ifndef COMPRESSTYPE_DEFINED
	#define COMPRESSTYPE_DEFINED
	typedef enum enumCOMPRESSTYPE
	{	COMPRESSTYPE_NONE,							// 不做压缩
		COMPRESSTYPE_GZIP,							// 使用GZIP压缩
		COMPRESSTYPE_DEFLATE,						// 使用DEFLATE压缩
		COMPRESSTYPE_ZLIB,							// 使用ZLIB压缩
		COMPRESSTYPE_MAX=COMPRESSTYPE_ZLIB,			// 压缩类型最大值
	} COMPRESSTYPE;
#endif


// 消息类别(参阅: ASEStdProt_Header.h)
#ifndef MSGTYPE_DEFINED
	#define MSGTYPE_DEFINED
	typedef enum enumMSGTYPE
	{	MSGTYPE_ROSE,								// ROSE协议
		MSGTYPE_RROSE,								// RROSE协议
		MSGTYPE_PUSHING,							// 推送
		MSGTYPE_UNKNOWN,							// 未知
	} MSGTYPE;
	#define MSGTYPE_DEFAULT MSGTYPE_ROSE
#endif


// 分片序号(参阅: ASEStdProt_Header.h)
#ifndef FRAGMENT_MAX
	#define FRAGMENT_MAX ((BYTE)100)
	#define FRAGMENT_DEFAULT FRAGMENT_MAX
#endif


// 协议相关宏定义
#if defined(PLATFORM_WINDOWS)
	#define PROTOCOL_WIN32								// WIN平台协议
#else
	#define PROTOCOL_LINUX								// LINUX平台协议
#endif
#define SEPARATOR_NUM			7654321					// 分割数字,用于拆分应答包处理



// 协议部分,使用1字节对齐
#pragma pack(1)


// IP地址定义(参阅: ASEStdDef.h)
#ifndef IP_DEFINED
	#define IP_DEFINED
	#define IPV6_API
	#define IPV6_ON

	// IPV4地址定义
	typedef struct tagIPV4
	{	BYTE m_acIpData[4];
	} IPV4;													// IPV4定义
	static const IPV4 EMPTY_IPV4={{0,0,0,0}};				// 空IPV4地址
	static const IPV4 LOOPBACK_IPV4={{127,0,0,1}};			// LOOPBACK的IPV4地址
	static const IPV4 NONE_IPV4={{0XFF,0XFF,0XFF,0XFF}};	// 任意IPV4地址

	// IPV4地址范围
	typedef struct tagIPRANGEV4
	{	IPV4	m_From;
		IPV4	m_End;
	} IPRANGEV4,*LPIPRANGEV4;


	// IPV6地址定义
	typedef struct tagIPV6
	{	BYTE m_acIpData[16];
	} IPV6;																												// IPV6定义
	static const IPV6 EMPTY_IPV6={{0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,0}};												// 空IPV6地址
	static const IPV6 LOOPBACK_IPV6={{0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,1}};											// LOOPBACK的IPV6地址
	static const IPV6 NONE_IPV6={{0XFF,0XFF,0XFF,0XFF, 0XFF,0XFF,0XFF,0XFF, 0XFF,0XFF,0XFF,0XFF, 0XFF,0XFF,0XFF,0XFF}};	// 任意IPV4地址

	// IPV6地址范围
	typedef struct tagIPRANGEV6
	{	IPV6	m_From;
		IPV6	m_End;
	} IPRANGEV6,*LPIPRANGEV6;

	#define IPV6_LEGAL
	#ifndef IPV6_LEGAL
		typedef IPV4 IP;
		typedef IPRANGEV4 IPRANGE;
		typedef LPIPRANGEV4 LPIPRANGE;
		#define SOCKADDRIN				SOCKADDR_IN
		#define EMPTY_IP				EMPTY_IPV4
		#define LOOPBACK_IP				LOOPBACK_IPV4
		#define NONE_IP					NONE_IPV4
		#define SockAddrToIP			SockAddrToIPv4
		#define SockAddrToPort			SockAddrToPortIPv4
		#define BytesToIP				BytesToIPv4
		#define StringToIP				StringToIPv4
		#define StringToSubNetIP		StringToSubNetIPv4
		#define IPToSockAddr			IPv4ToSockAddr
		#define IPToBytes				IPv4ToBytes
		#define IPToString				IPv4ToString
		#define IPToCommaString			IPv4ToCommaString
		#define SubNetIPToString		SubNetIPv4ToString
		#define AddIP					AddIPv4
		#define SubIP					SubIPv4
		#define SpanToIP				SpanToIPv4
		#define SpanBetweenIP			SpanBetweenIPv4
		#define CompareIP				CompareIPv4
		#define MaskIP					MaskIPv4
		#define IsIPv4IP(a)				(TRUE)
		#define IsLoopbackIP			IsLoopbackIPv4
		#define IsBoardcastIP			IsBoardcastIPv4
		#define IsEthernetIP			IsEthernetIPv4
		#define IsInternetIP			IsInternetIPv4
		#define IPConvert4ToLegal(a)	(a)
		#define IPConvert6ToLegal(a)	IPConvert6To4(a)
		#define IPConvertLegalTo4(a)	(a)
		#define IPConvertLegalTo6(a)	IPConvert4To6(a)
	#else
		typedef IPV6 IP;
		typedef IPRANGEV6 IPRANGE;
		typedef LPIPRANGEV6 LPIPRANGE;
		#define SOCKADDRIN				SOCKADDR_IN6
		#define EMPTY_IP				EMPTY_IPV6
		#define LOOPBACK_IP				LOOPBACK_IPV6
		#define NONE_IP					NONE_IPV6
		#define SockAddrToIP			SockAddrToIPv6
		#define SockAddrToPort			SockAddrToPortIPv6
		#define BytesToIP				BytesToIPv6
		#define StringToIP				StringToIPv6
		#define StringToSubNetIP		StringToSubNetIPv6
		#define IPToSockAddr			IPv6ToSockAddr
		#define IPToBytes				IPv6ToBytes
		#define IPToString				IPv6ToString
		#define IPToCommaString			IPv6ToCommaString
		#define SubNetIPToString		SubNetIPv6ToString
		#define AddIP					AddIPv6
		#define SubIP					SubIPv6
		#define SpanToIP				SpanToIPv6
		#define SpanBetweenIP			SpanBetweenIPv6
		#define CompareIP				CompareIPv6
		#define MaskIP					MaskIPv6
		#define IsIPv4IP				IsIPv4
		#define IsLoopbackIP			IsLoopbackIPv6
		#define IsBoardcastIP			IsBoardcastIPv6
		#define IsEthernetIP			IsEthernetIPv6
		#define IsInternetIP			IsInternetIPv6
		#define IPConvert4ToLegal(a)	IPConvert4To6(a)
		#define IPConvert6ToLegal(a)	(a)
		#define IPConvertLegalTo4(a)	IPConvert6To4(a)
		#define IPConvertLegalTo6(a)	(a)
	#endif
#endif





// MAC地址定义(参阅: ASEStdDef.h)
#ifndef MAC_DEFINED
	#define MAC_DEFINED
	typedef struct tagMAC
	{
		// 地址数据
		BYTE m_acMacData[6];
		// 赋值和特殊构造
		static inline tagMAC FromBytes(LPBYTE pBytes) { tagMAC Mac; memcpy(Mac.m_acMacData,pBytes,size_of(Mac.m_acMacData)); return Mac; }
	} MAC;
	static const MAC EMPTY_MAC={{0,0,0,0,0,0}};		// 空MAC地址
#endif

#pragma pack()

#endif

