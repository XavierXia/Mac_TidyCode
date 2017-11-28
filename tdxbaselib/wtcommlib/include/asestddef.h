//////////////////////////////////////////////////////////////////////////
// ASE(Adaptive Server Environment)�ܹ��µı�׼����
// ��Щ������ASE������ͨ��
#ifndef __ASE_STDDEF__H__
#define __ASE_STDDEF__H__
#pragma pack(1)


// IP��ַ����
// IP��ַ����(����: SafeVCRT.h)
#ifndef IP_DEFINED
	#define IP_DEFINED
	#define IPV6_API
	#define IPV6_ON

	typedef struct tagIPV4
	{	BYTE m_acIpData[4];
	} IPV4;

	typedef struct tagIPV6
	{	BYTE m_acIpData[16];
	} IPV6;

	#define IPV6_LEGAL
	#ifndef IPV6_LEGAL
		typedef IPV4 IP;
	#else
		typedef IPV6 IP;
	#endif

#endif


// MAC�Ķ���(����: SafeVCRT.h)
#ifndef MAC_DEFINED
	#define MAC_DEFINED
	typedef struct tagMAC
	{	BYTE m_acMacData[6];
	} MAC;
#endif


// MD5�Ķ���
// MD5����������(����: SafeVCRT.h)
#ifndef MD5BIN_DEFINED
	#define MD5BIN_DEFINED
	typedef struct tagMD5BIN							// MD5��ṹ
	{	BYTE m_szMD5[16];								// MD5�뻺����
	} MD5BIN,*LPMD5BIN;
	typedef const MD5BIN* LPCMD5BIN;
	const MD5BIN md5Null={{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
#endif

// ��ĿHASH����(����: SafeVCRT.h)
#ifndef IHASH_DEFINED
	#define IHASH_DEFINED
	typedef struct tagIHASH								// ��ĿHASH�ṹ
	{	DWORD m_dwSize;									// ��Ŀ��С
		BYTE m_acHash[16];								// ��ĿHASH
	} IHASH,*LPIHASH;
	const IHASH ihashNull={0,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
#endif

// ��׼���Ͷ���(����: SafeVCRT_Types.h,WTCommLib/StdAfx.h)
#ifndef STDTYPE_DEFINED
	// LPCBYTE
	typedef const BYTE* LPCBYTE;
	// UINT64����
	typedef unsigned __int64 __uint64;
	// interface����(����: SafeVCRT_Types.h)
	#ifndef interface
		#define interface struct
	#endif
	#ifndef PURE
		#define PURE =0
	#endif
	// �����궨��
	#if !defined(VERIFY) && defined(CLIBVERIFY)
		#define VERIFY(a)	CLIBVERIFY(a)
	#endif
	#if !defined(ASSERT) && defined(CLIBASSERT)
		#define ASSERT(a)	CLIBASSERT(a)
	#endif
#endif

#ifndef max_of
	#define max_of(a,b)			(((a) > (b)) ? (a) : (b))
#endif
#ifndef max
	#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif
#ifndef min_of
	#define min_of(a,b)			(((a) < (b)) ? (a) : (b))
#endif
#ifndef min
	#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#ifndef size_of
	#define size_of(a)			((DWORD)sizeof(a))
#endif
#ifndef ARRAYSIZE
	#define SIZEOF(a)			((DWORD)sizeof(a))
	#define ARRAYSIZE(a)		((DWORD)((sizeof(a)/sizeof(a[0]))))
#endif

// ����ȵ�����(����: SafeVCRT_Types.h)
#ifndef SIZED_TYPE
#define SIZED_TYPE
	// int8/int16/int32/int64/uint8/uint16/uint32/uint64����
	typedef char              int8;
	typedef short             int16;
	typedef int               int32;
	typedef __int64           int64;
	typedef unsigned char     uint8;
	typedef unsigned short    uint16;
	typedef unsigned int      uint32;
	typedef __uint64		  uint64;
	// byte/word8/word16/word32/word64����
	typedef unsigned char     byte;
	typedef unsigned char     word8;
	typedef unsigned short    word16;
	typedef unsigned int      word32;
	typedef __uint64          word64;
#endif

// λ�ö���(����: SafeVCRT_Types.h)
#ifndef BEFORE_START_POSITION
	struct __POSITION {};
	typedef __POSITION* POSITION;
	#define BEFORE_START_POSITION ((POSITION)-1L)
#endif

// ʱ�䶨��(����: SafeVCRT_Types.h)
#ifndef SYSTM_T
#define SYSTM_T
	typedef int64 systm_t;
#endif

// ��Ƭ���(����: SafeVCRT_Types.h)
#ifndef FRAGMENT_MAX
	#define FRAGMENT_MAX ((BYTE)100)
	#define FRAGMENT_DEFAULT FRAGMENT_MAX
#endif

// ������(����: SafeVCRT.h)
#ifndef EMBED_OBJECT
#define EMBED_OBJECT
	typedef VOID (* DESTRUCTOR)(VOID*);
	#define DECLARE_DESTRUCT(CLASS)												\
		public:																	\
		static VOID __Destructor(LPVOID pvSelf)									\
		{	CLASS* pSelf=(CLASS*)pvSelf;										\
			if(pSelf!=NULL) pSelf->~CLASS();									\
		}
	typedef VOID* (* CONNECTOR)(VOID*);
	#define DECLARE_CONNECTOR(CLASS,TYPE)										\
		public:																	\
		static VOID* __Connector(LPVOID pvSelf)									\
		{	CLASS* pSelf=(CLASS*)pvSelf;										\
			if(pSelf!=NULL) return (VOID*)((TYPE*)pSelf);						\
			return NULL;														\
		}
	#define DECLARE_CONNECTOR_EX(CLASS,BYCLASS,TYPE)							\
		public:																	\
		static VOID* __Connector(LPVOID pvSelf)									\
		{	CLASS* pSelf=(CLASS*)pvSelf;										\
			if(pSelf!=NULL) return (VOID*)(TYPE*)static_cast<BYCLASS*>(pvSelf);	\
			return NULL;														\
		}
#endif


// �û���غ궨��(����: SafeVCRT.h)
#ifndef UINFO_DEFINED
	#define UINFO_DEFINED
	#define AP_SIZE					(64)				// 64�ֽڵ�AP��Ϣ
	#define UORG_DEFID				(0)					// �û�����Ĭ��ID
	#define UORG_SIZE				(41)				// �û�������󳤶�
	#define UID_SIZE				(41)				// �û��ʺ���󳤶�
	#define UNAME_SIZE				(41)				// �û�������󳤶�
	#define UID_GSIZE				(13)				// �û��ʺ���󳤶�(ȫ��,Ӫҵ������ʹ��WORD��)
#endif




// ������/��Ȩ����(�Զ�����ʹ��,��ϸ�汾����)
#define LICTYPE_INVALID				0
#define LICTYPE_TC50				1001
#define LICTYPE_SC50				1002
#define LICTYPE_IMSERVER			1003
#define LICTYPE_PTSERVER			1004
#define LICTYPE_MOBILEPORTAL		1005
#define LICTYPE_TDXPORTAL			1006
#define LICTYPE_TSERVER				1007
#define LICTYPE_TDXBP				1010


// �ͻ�������(�Զ�����ʹ��,��ϸ�汾����)
#define CLIENTTYPE_UNKNOWN			0					// δ֪����
#define CLIENTTYPE_INVALID			0					// δ֪����

#define WTCLIENT_MAX_TYPE			CLIENTTYPE_MAX
#define WTCLIENT_INVALID			0					// δ֪����
#define WTCLIENT_NODICT_GX			1					// (����) ���Ű�,     ����, 3.X�ͻ���
#define WTCLIENT_DICT_NORMAL		2					// (����) ��׼��,     ����, 4.X�ͻ���
#define WTCLIENT_DICT_GX			3					// (����) ���Ű�,     ����, 4.X�ͻ���
#define WTCLIENT_DICT_DYCY			4					// (����) ��һ��ҵ��, ����, 4.X�ͻ���
#define WTCLIENT_DICT_PHONE			5					// (����) �绰ί�а�, ����, 4.X�ͻ���
#define WTCLIENT_DICT_BIG5_NORMAL	6					// (����) ��׼��,     ����, 4.X�ͻ���
#define WTCLIENT_JGB				7					// (����) ������,     ����, 4.X�ͻ���
#define WTCLIENT_JGB_BIG5			8					// (����) ������,     ����, 4.X�ͻ���
#define WTCLIENT_SERVER_TC50		9					// ������(����)
#define WTCLIENT_JKTOOL_TC50		10					// ��ع���
#define WTCLIENT_ADMTOOL_TC50		11					// (����)������
#define WTCLIENT_DLL_TC50			12					// ��׼DLL��,				����, 5.X�ͻ���
#define WTCLIENT_DLL_TC50_BIG5		13					// ��׼DLL��,				����, 5.X�ͻ���
#define WTCLIENT_STANDARD_TC50		14					// ��׼EXE��(TCSDK��),		����, 5.X�ͻ���
#define WTCLIENT_STANDARD_TC50_BIG5	15					// ��׼EXE��,				����, 5.X�ͻ���
#define WTCLIENT_JGB_TC50			16					// ������,					����, 5.X�ͻ���
#define WTCLIENT_JGB_TC50_BIG5		17					// ������,					����, 5.X�ͻ���
#define WTCLIENT_LINUX_TC50			18					// LINUX��,					����, 5.X�ͻ���
#define WTCLIENT_WEB_TC50			19					// WEB��(ISAPI��TCAPI),		����, 5.X�ͻ���
#define WTCLIENT_MOBILE_TC50		20					// (����)�ֻ���,			����, 5.X�ͻ���
#define WTCLIENT_VIP_TC50			21					// (����)VIP�ն˰�,			����, 5.X�ͻ���
#define WTCLIENT_SERVER_SC50		22					// (����)��ȫ����
#define WTCLIENT_SERVER_IC50		23					// (����)��Ϣ����
#define WTCLIENT_SERVER_CC50		24					// (����)��������
#define WTCLIENT_SERVER_LC50		25					// (����)��־����
#define WTCLIENT_EXTRA_OTHER		26					// �����ⲿ�����ڵ�
#define WTCLIENT_EXTRA_SL			27					// ʤ�����������õ��ⲿ�����ڵ�(TC����������ɲ���)
#define WTCLIENT_EXTRA_JZX			28					// ���������������õ��ⲿ�����ڵ�(TC����������ɲ���)
#define WTCLIENT_EXTRA_RYKJ			29					// ���׿Ƽ����������õ��ⲿ�ڵ�(HTTP)
#define WTCLIENT_DLL_TC50_ENU		30					// ��׼DLL��,				Ӣ��, 5.X�ͻ���
#define WTCLIENT_STANDARD_TC50_ENU	31					// ��׼EXE��,				Ӣ��, 5.X�ͻ���
#define WTCLIENT_JGB_TC50_ENU		32					// ������,					Ӣ��, 5.X�ͻ���

#define CLIENTTYPE_HTTP				33							// HTTP��
#define CLIENTTYPE_MOBILE			34							// Mobile��
#define CLIENTTYPE_IPHONE			35							// iPhone��
#define CLIENTTYPE_IPAD				36							// iPad��
#define CLIENTTYPE_ANDROIDPHONE		37							// AndroidPhone��
#define CLIENTTYPE_ANDROIDPAD		38							// AndroidPad��
#define CLIENTTYPE_IMAC				39							// iMac��
#define CLIENTTYPE_CRM				40							// CRMϵͳ

#define CLIENTTYPE_INTRAHOST		99							// �ڲ�����
#define CLIENTTYPE_UNKNOWNHOST		(CLIENTTYPE_INTRAHOST+0)	// δ֪�������
#define CLIENTTYPE_TDXPORTAL		(CLIENTTYPE_INTRAHOST+1)	// TP������
#define CLIENTTYPE_TDXSERVER		(CLIENTTYPE_INTRAHOST+2)	// TS������
#define CLIENTTYPE_MOBILEPORTAL		(CLIENTTYPE_INTRAHOST+3)	// MP������
#define CLIENTTYPE_RPCAPI			(CLIENTTYPE_INTRAHOST+21)	// RPC-API
#define CLIENTTYPE_MAX				128							// ���ͻ��������



// ����������
#ifndef JYS_DEFINED
#define JYS_DEFINED
	#define INVALID_JYS				0XFF				// ��������Ч(��ָ��)
	#define SZ						0					// �����г�,�����г�(�������)
	#define SH						1					// �����г�,�Ϻ��г�
	#define HK						2					// ����г�,
	#define ZZQHJYS					21					// ֣���ڻ�������
	#define SHQHJYS					22					// �Ϻ��ڻ�������
	#define DLQHJYS					23					// �����ڻ�������
	#define ZJQHJYS					26					// �н��ڻ�������
#endif


// ֤ȯ��������ƴ�С
#define ZQDM_SIZE					7					// ֤ȯ���볤��,���������ַ�
#define ZQMC_SIZE					9					// ֤ȯ���Ƴ���,���������ַ�
#define HKZQDM_SIZE					9					// (�۹�)֤ȯ���볤��,���������ַ�
#define HKZQMC_SIZE					17					// (�۹�)֤ȯ���Ƴ���,���������ַ�


// ֤ȯ���ƺͱ�ʶ��С
#define QSMC_SIZE					65					// ȯ������(��Ӣ��)����,���������ַ�
#define QSID_SIZE					11					// ȯ�̱�ʶ(��Ӣ��)����,���������ַ�


// �г�����ṹ
// ע:�г���Ϣ��֧�������汾SCINFO1�Լ�SCINFO2
//    SCINFO1��SCINFO2�ڽṹ��С�Ͳ����ֶ�����ȫ����
//    SCINFO2�ĺ�SCINFO1��Ҫ��ͬ��:
//    1.SCINFO1�������ݴ������ж�,�������������г�,���ڱȽ϶���������,�ڴ������ƥ��������Լ��
//      �粻��ʱ�������ý��ᵼ���ʺ����ƥ�����Ӷ������޷����н���,SCINFO2���ȼ���������ʷ�����
//      ȷ�Ͻ�����,Ȼ���ڽ������ڰ������ƥ��������ƥ��,SCINFO2��������Ϊ����,����ȡ����ʧ�ܵ����
//      �»�����δ��ʱ���µ������,ͨ�������������ƥ�佻����,���������ƥ��ʧ�ܻ��߹���ƥ��ʧ��
//      �������˽�����ͻ�����Ӧ�ı��,�ͻ��˿��Ը����Ƿ�ȡ�������������Լ��Ƿ���ҵ��г��������Ƿ���
//      ʾ�ͻ�ѡȡ�ɶ�����ֱ��ʹ��A���ʺ�
//    2.SCINFO1��SCINFO2���ڴ�ṹ����ȫһ��,���ں��ϵͳ����Ҫ����֧��SCINFO2����չ����
//    3.ϵͳ�Զ��жϵ�ǰ�ṹ��SCINFO1����SCINFO2,�������������ļ���Ҳ��һ�µ�,������ͨ�����汾���
#ifdef ASELIB_API
	// �����г��ṹ
	typedef struct tagSCINFO1
	{	CHAR	zhlb;									// �г����(��A,��B,��A,��B�ȵ�)
		CHAR	lbname[17];								// �г�����
		CHAR	zqdm[ZQDM_SIZE];						// ֤ȯ����(�����Ǿ���Ĵ���,Ҳ���Ա�ʾһ�ֹ���,���������λ���ʾ�������)
		CHAR	unused1;								// (����)���뷽ʽ,��֤ȯ�����Ǵ������,
														// 0:��ʾzqdm�������
														// 1:��ʾzqdm���Ҷ���
														// �����Ǵ������,���ֶ���Ч
		SHORT	floatlen;								// �����Ӧ���۵�С��λ��
		CHAR	unused2;								// (����)(������Ϊ���������ڲ���ʶ)0:��(��ծΪ��) 1:��
		CHAR	unused3;								// (����)(���½ṹ��ʹ���µĶ���)�Ƿ�֧�ֹ�Ʊ���	0:����� 1:���
		LONG	unused4;								// (����)(���½ṹ��ʹ���µĶ���)������ÿ�ν�������(�䵥λ��jydw��Ӧ),��Ϊ0���ʾû������
		LONG	unused5;								// (����)(���½ṹ��ʹ���µĶ���)������ÿ�ν�������(�䵥λ��jydw��Ӧ),��Ϊ0���ʾû������
		CHAR	bz;										// ��Ӧ���� 0:����� 1:��Բ 2:�۱�
		CHAR	gzbs;									// ��ծ��־ 0:��ծ�ֻ� 1:ծȯ 2:��ת��ծȯ 3:��ծ�ع�
		CHAR	reserved[8];							// ����
	} SCINFO1,*LPSCINFO1,SCSTRUC1,*LPSCSTRUC1,SCSTRUC,*LPSCSTRUC;
	typedef struct tagSCINFO2
	{	CHAR	setcode;								// �г�(0:����,������ 1:�Ϻ�)
		CHAR	rule[ZQDM_SIZE];						// �������
		CHAR	splb;									// ��Ʒ���
		CHAR	zhlb;									// �ʺ����(��A,��B,��A,��B�ȵ�)
		CHAR	lbname[17];								// �������(����ʾ��;)
		SHORT	floatlen;								// �����Ӧ���۵�С��λ��
		CHAR	bz;										// ��Ӧ���� 0:����� 1:��Բ 2:�۱�
		CHAR	gzbs;									// ��ծ��־ 0:��ծ�ֻ� 1:ծȯ 2:��ת��ծȯ 3:��ծ�ع�
		CHAR	jldw[8];								// ������λ
		CHAR	xsdw;									// ���ֵ�λ
		CHAR	zsdw;									// ���ֵ�λ
		CHAR	kcdw;									// ��浥λ
		CHAR	sbdw;									// �걨��λ(ǰ��)
		LONG	sbxx;									// �걨����(ǰ��,������λ)
		LONG	sbsx;									// �걨����(ǰ��,�������λ)
		FLOAT	sxfl;									// ��������
		FLOAT	sxfqd;									// ���������
		CHAR	reserved[16];							// ����
	} SCINFO2,*LPSCINFO2,SCSTRUC2,*LPSCSTRUC2;

	// ������Ϣ
	typedef struct ASELIB_API tagHQINFO
	{	CHAR		   setcode;					// �г�,SZ OR SH
		CHAR		   zqdm[ZQDM_SIZE];			// ֤ȯ����
		CHAR		   zqmc[ZQMC_SIZE];			// ֤ȯ����
		CHAR           tp_flag;					// ͣ�Ʊ�־
		FLOAT          Close;					// ǰ���̼�,ָ��
		FLOAT          Open;					// ���̼�,ָ��
		FLOAT          Now;						// �ּ�,���ָ��
		FLOAT		   Gzlx;					// ��ծ��Ϣ
		FLOAT          Buyp[5];					// ��������,�����ݽӿ�
		DWORD          Buyv[5];					// ��Ӧ�������۵��������
		FLOAT          Sellp[5];				// ���������
		DWORD          Sellv[5];				// ��Ӧ��������۵��������
		LONG		   reserved[1];				// �����ֽ�(����ȫ��)
	} HQINFO,*LPHQINFO;
	typedef struct ASELIB_API tagHQSCINFO
	{	CHAR		   bGetHqAns;				// ������Ϣ�Ƿ�ɹ�
		HQINFO		   HqInfo;					// ������Ϣ
		CHAR		   bGetScStruc;				// �г���Ϣ�Ƿ��ȡ�ɹ� 1:�ɹ�,0:ƥ�䲻��
		SCSTRUC1	   ScStruc;					// �Ĺ�Ʊ��Ӧ��һЩ�г���Ϣ
		tagHQSCINFO()
		{	memset(this,0,size_of(tagHQSCINFO));
		}
	} HQSCINFO1,*LPHQSCINFO1,HQSCINFO,*LPHQSCINFO;
	typedef struct ASELIB_API tagHQSCINFO2
	{	CHAR		   bGetHqAns;				// ������Ϣ�Ƿ�ɹ�
		HQINFO		   HqInfo;					// ������Ϣ
		CHAR		   bGetScStruc;				// �г���Ϣ�Ƿ��ȡ�ɹ� 1:�ɹ�,0:ƥ�䲻��
		SCSTRUC2	   ScStruc;					// �Ĺ�Ʊ��Ӧ��һЩ�г���Ϣ
		tagHQSCINFO2()
		{	memset(this,0,size_of(tagHQSCINFO2));
		}
	} HQSCINFO2,*LPHQSCINFO2;
	// �۹�������Ϣ
	typedef struct ASELIB_API tagHKHQINFO
	{	CHAR		   setcode;					// �г�,HK
		CHAR		   zqdm[HKZQDM_SIZE];		// ֤ȯ����
		CHAR		   zqmc[HKZQMC_SIZE];		// ֤ȯ����
		FLOAT          Close;					// ǰ���̼�,ָ��
		FLOAT          Open;					// ���̼�,ָ��
		FLOAT          Now;						// �ּ�,���ָ��
		FLOAT          Buyp[5];					// ��������,�����ݽӿ�
		DWORD          Buyv[5];					// ��Ӧ�������۵��������
		FLOAT          Sellp[5];				// ���������
		DWORD          Sellv[5];				// ��Ӧ��������۵��������
		DWORD		   PreVol;					// ��С���׹���
		WORD		   HSpread;					// ��С�����ҵ����׵�λ
		WORD		   LSpread;					// ��С����ҵ����׵�λ
		LONG		   reserved[1];				// �����ֽ�(����ȫ��)
	} HKHQINFO,*LPHKHQINFO;
	// ����������Ϣ
	typedef struct ASELIB_API tagL2HQINFO
	{	CHAR		   setcode;					// �г�,L2
		CHAR		   zqdm[ZQDM_SIZE];			// ֤ȯ����
		CHAR		   zqmc[ZQMC_SIZE];			// ֤ȯ����
		FLOAT		   Close;					// ǰ���̼�
		FLOAT   	   Open;       				// ���̼�
		FLOAT   	   Max;        				// ��߼�
		FLOAT   	   Min;        				// ��ͼ�
		FLOAT   	   Now;        				// �ּ�
		FLOAT		   Buyp[10];				// �����
		DWORD   	   Buyv[10];				// ��Ӧ����۵�����
		FLOAT   	   Sellp[10];				// ������
		DWORD   	   Sellv[10];				// ��Ӧ�����۵�����
		DWORD   	   Volume;     				// ����
		FLOAT   	   Amount;     				// �ܳɽ����
		DWORD		   RestVol;					// �ɽ����
		DWORD		   CJBS;					// �ɽ�����
		FLOAT		   Gzlx;					// ��ծ��Ϣ
		FLOAT		   Jjjz;					// ETF��ֵ
		LONG		   reserved[1];				// �����ֽ�(����ȫ��)
	} L2HQINFO,*LPL2HQINFO;
#endif





// �Զ�����ģʽ(�����ϰ汾����)
#define UPGRADE_NO				(0)					// �Զ�����ģʽ:���Զ�����
#define UPGRADE_PACKAGE			(1)					// �Զ�����ģʽ:�������
#define UPGRADE_PIECE			(2)					// �Զ�����ģʽ:����ģ������


// ���������Ϣ(�����ϰ汾����)
typedef struct tagPLUGININFO
{	CHAR	m_szModule[32];							// ����ļ���(�ļ�����λ��PLUGINĿ¼��)
	MD5BIN  m_md5Module;							// ����ļ�MD5��Ϣ(��̬����)
} PLUGININFO,*LPPLUGININFO;


// ��ڵ�������Ϣ(�������ݸ��ͻ���)(�����ϰ汾����)
typedef struct tagENTRYPOINTIDX
{	WORD    m_wEntryPointID;						// ��ڵ�ID
	CHAR	m_szDescription[41];					// ��ڵ���
} ENTRYPOINTIDX,*LPENTRYPOINTIDX;




// Э��ǰ׺
#define STD_PROT					CONST		// ��׼Э�鼯














#pragma pack()
#endif
