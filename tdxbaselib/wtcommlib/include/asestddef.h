//////////////////////////////////////////////////////////////////////////
// ASE(Adaptive Server Environment)架构下的标准定义
// 这些定义在ASE各环节通用
#ifndef __ASE_STDDEF__H__
#define __ASE_STDDEF__H__
#pragma pack(1)


// IP地址定义
// IP地址定义(参阅: SafeVCRT.h)
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


// MAC的定义(参阅: SafeVCRT.h)
#ifndef MAC_DEFINED
	#define MAC_DEFINED
	typedef struct tagMAC
	{	BYTE m_acMacData[6];
	} MAC;
#endif


// MD5的定义
// MD5二进制描述(参阅: SafeVCRT.h)
#ifndef MD5BIN_DEFINED
	#define MD5BIN_DEFINED
	typedef struct tagMD5BIN							// MD5码结构
	{	BYTE m_szMD5[16];								// MD5码缓冲区
	} MD5BIN,*LPMD5BIN;
	typedef const MD5BIN* LPCMD5BIN;
	const MD5BIN md5Null={{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
#endif

// 项目HASH描述(参阅: SafeVCRT.h)
#ifndef IHASH_DEFINED
	#define IHASH_DEFINED
	typedef struct tagIHASH								// 项目HASH结构
	{	DWORD m_dwSize;									// 项目大小
		BYTE m_acHash[16];								// 项目HASH
	} IHASH,*LPIHASH;
	const IHASH ihashNull={0,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
#endif

// 标准类型定义(参阅: SafeVCRT_Types.h,WTCommLib/StdAfx.h)
#ifndef STDTYPE_DEFINED
	// LPCBYTE
	typedef const BYTE* LPCBYTE;
	// UINT64定义
	typedef unsigned __int64 __uint64;
	// interface定义(参阅: SafeVCRT_Types.h)
	#ifndef interface
		#define interface struct
	#endif
	#ifndef PURE
		#define PURE =0
	#endif
	// 其他宏定义
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

// 带宽度的类型(参阅: SafeVCRT_Types.h)
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

// 位置定义(参阅: SafeVCRT_Types.h)
#ifndef BEFORE_START_POSITION
	struct __POSITION {};
	typedef __POSITION* POSITION;
	#define BEFORE_START_POSITION ((POSITION)-1L)
#endif

// 时间定义(参阅: SafeVCRT_Types.h)
#ifndef SYSTM_T
#define SYSTM_T
	typedef int64 systm_t;
#endif

// 分片序号(参阅: SafeVCRT_Types.h)
#ifndef FRAGMENT_MAX
	#define FRAGMENT_MAX ((BYTE)100)
	#define FRAGMENT_DEFAULT FRAGMENT_MAX
#endif

// 析构器(参阅: SafeVCRT.h)
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


// 用户相关宏定义(参阅: SafeVCRT.h)
#ifndef UINFO_DEFINED
	#define UINFO_DEFINED
	#define AP_SIZE					(64)				// 64字节的AP信息
	#define UORG_DEFID				(0)					// 用户机构默认ID
	#define UORG_SIZE				(41)				// 用户机构最大长度
	#define UID_SIZE				(41)				// 用户帐号最大长度
	#define UNAME_SIZE				(41)				// 用户名称最大长度
	#define UID_GSIZE				(13)				// 用户帐号最大长度(全局,营业部代码使用WORD型)
#endif




// 服务器/授权类型(自动升级使用,详细版本类型)
#define LICTYPE_INVALID				0
#define LICTYPE_TC50				1001
#define LICTYPE_SC50				1002
#define LICTYPE_IMSERVER			1003
#define LICTYPE_PTSERVER			1004
#define LICTYPE_MOBILEPORTAL		1005
#define LICTYPE_TDXPORTAL			1006
#define LICTYPE_TSERVER				1007
#define LICTYPE_TDXBP				1010


// 客户端类型(自动升级使用,详细版本类型)
#define CLIENTTYPE_UNKNOWN			0					// 未知类型
#define CLIENTTYPE_INVALID			0					// 未知类型

#define WTCLIENT_MAX_TYPE			CLIENTTYPE_MAX
#define WTCLIENT_INVALID			0					// 未知类型
#define WTCLIENT_NODICT_GX			1					// (废弃) 国信版,     简体, 3.X客户端
#define WTCLIENT_DICT_NORMAL		2					// (废弃) 标准版,     简体, 4.X客户端
#define WTCLIENT_DICT_GX			3					// (废弃) 国信版,     简体, 4.X客户端
#define WTCLIENT_DICT_DYCY			4					// (废弃) 第一创业版, 简体, 4.X客户端
#define WTCLIENT_DICT_PHONE			5					// (废弃) 电话委托版, 简体, 4.X客户端
#define WTCLIENT_DICT_BIG5_NORMAL	6					// (废弃) 标准版,     繁体, 4.X客户端
#define WTCLIENT_JGB				7					// (废弃) 机构版,     简体, 4.X客户端
#define WTCLIENT_JGB_BIG5			8					// (废弃) 机构版,     繁体, 4.X客户端
#define WTCLIENT_SERVER_TC50		9					// 服务器(级联)
#define WTCLIENT_JKTOOL_TC50		10					// 监控工具
#define WTCLIENT_ADMTOOL_TC50		11					// (暂无)管理工具
#define WTCLIENT_DLL_TC50			12					// 标准DLL版,				简体, 5.X客户端
#define WTCLIENT_DLL_TC50_BIG5		13					// 标准DLL版,				繁体, 5.X客户端
#define WTCLIENT_STANDARD_TC50		14					// 标准EXE版(TCSDK版),		简体, 5.X客户端
#define WTCLIENT_STANDARD_TC50_BIG5	15					// 标准EXE版,				繁体, 5.X客户端
#define WTCLIENT_JGB_TC50			16					// 机构版,					简体, 5.X客户端
#define WTCLIENT_JGB_TC50_BIG5		17					// 机构版,					繁体, 5.X客户端
#define WTCLIENT_LINUX_TC50			18					// LINUX版,					简体, 5.X客户端
#define WTCLIENT_WEB_TC50			19					// WEB版(ISAPI或TCAPI),		简体, 5.X客户端
#define WTCLIENT_MOBILE_TC50		20					// (暂无)手机版,			简体, 5.X客户端
#define WTCLIENT_VIP_TC50			21					// (暂无)VIP终端版,			简体, 5.X客户端
#define WTCLIENT_SERVER_SC50		22					// (暂无)安全中心
#define WTCLIENT_SERVER_IC50		23					// (暂无)信息中心
#define WTCLIENT_SERVER_CC50		24					// (暂无)呼叫中心
#define WTCLIENT_SERVER_LC50		25					// (暂无)日志中心
#define WTCLIENT_EXTRA_OTHER		26					// 其他外部互联节点
#define WTCLIENT_EXTRA_SL			27					// 胜龙三方开发用的外部互连节点(TC开发包的组成部分)
#define WTCLIENT_EXTRA_JZX			28					// 金轴线三方开发用的外部互连节点(TC开发包的组成部分)
#define WTCLIENT_EXTRA_RYKJ			29					// 容易科技三方开发用的外部节点(HTTP)
#define WTCLIENT_DLL_TC50_ENU		30					// 标准DLL版,				英文, 5.X客户端
#define WTCLIENT_STANDARD_TC50_ENU	31					// 标准EXE版,				英文, 5.X客户端
#define WTCLIENT_JGB_TC50_ENU		32					// 机构版,					英文, 5.X客户端

#define CLIENTTYPE_HTTP				33							// HTTP版
#define CLIENTTYPE_MOBILE			34							// Mobile版
#define CLIENTTYPE_IPHONE			35							// iPhone版
#define CLIENTTYPE_IPAD				36							// iPad版
#define CLIENTTYPE_ANDROIDPHONE		37							// AndroidPhone版
#define CLIENTTYPE_ANDROIDPAD		38							// AndroidPad版
#define CLIENTTYPE_IMAC				39							// iMac版
#define CLIENTTYPE_CRM				40							// CRM系统

#define CLIENTTYPE_INTRAHOST		99							// 内部主机
#define CLIENTTYPE_UNKNOWNHOST		(CLIENTTYPE_INTRAHOST+0)	// 未知类别主机
#define CLIENTTYPE_TDXPORTAL		(CLIENTTYPE_INTRAHOST+1)	// TP服务器
#define CLIENTTYPE_TDXSERVER		(CLIENTTYPE_INTRAHOST+2)	// TS服务器
#define CLIENTTYPE_MOBILEPORTAL		(CLIENTTYPE_INTRAHOST+3)	// MP服务器
#define CLIENTTYPE_RPCAPI			(CLIENTTYPE_INTRAHOST+21)	// RPC-API
#define CLIENTTYPE_MAX				128							// 最大客户端类别数



// 交易所定义
#ifndef JYS_DEFINED
#define JYS_DEFINED
	#define INVALID_JYS				0XFF				// 交易所无效(或不指定)
	#define SZ						0					// 行情市场,深圳市场(含三板等)
	#define SH						1					// 行情市场,上海市场
	#define HK						2					// 香港市场,
	#define ZZQHJYS					21					// 郑州期货交易所
	#define SHQHJYS					22					// 上海期货交易所
	#define DLQHJYS					23					// 大连期货交易所
	#define ZJQHJYS					26					// 中金期货交易所
#endif


// 证券代码和名称大小
#define ZQDM_SIZE					7					// 证券代码长度,包含结束字符
#define ZQMC_SIZE					9					// 证券名称长度,包含结束字符
#define HKZQDM_SIZE					9					// (港股)证券代码长度,包含结束字符
#define HKZQMC_SIZE					17					// (港股)证券名称长度,包含结束字符


// 证券名称和标识大小
#define QSMC_SIZE					65					// 券商名称(中英文)长度,包含结束字符
#define QSID_SIZE					11					// 券商标识(中英文)长度,包含结束字符


// 市场定义结构
// 注:市场信息共支持两个版本SCINFO1以及SCINFO2
//    SCINFO1和SCINFO2在结构大小和部分字段上完全兼容
//    SCINFO2的和SCINFO1主要不同是:
//    1.SCINFO1单纯依据代码来判断,不检查代码所在市场,存在比较多的特例情况,在代码最大匹配规则的制约下
//      如不及时更新配置将会导致帐号类别匹配错误从而导致无法进行交易,SCINFO2首先检查行情和历史代码表
//      确认交易所,然后在交易所内按照最大匹配规则进行匹配,SCINFO2仅仅抽象为规则,当获取行情失败的情况
//      下或代码表未及时更新的情况下,通过缓存的码表进行匹配交易所,如果交易所匹配失败或者规则匹配失败
//      服务器端将给予客户端相应的标记,客户端可以根据是否取到交易所代码以及是否查找到市场来决定是否提
//      示客户选取股东或是直接使用A股帐号
//    2.SCINFO1和SCINFO2在内存结构上完全一致,对于后端系统不需要考虑支持SCINFO2的扩展部分
//    3.系统自动判断当前结构是SCINFO1还是SCINFO2,这两者在配置文件上也是一致的,服务器通过检查版本标记
#ifdef ASELIB_API
	// 定义市场结构
	typedef struct tagSCINFO1
	{	CHAR	zhlb;									// 市场类别(深A,深B,沪A,沪B等等)
		CHAR	lbname[17];								// 市场名称
		CHAR	zqdm[ZQDM_SIZE];						// 证券代码(可以是具体的代码,也可以表示一种规则,如果不足六位则表示代码规则)
		CHAR	unused1;								// (废弃)对齐方式,若证券代码是代码规则,
														// 0:表示zqdm是左对齐
														// 1:表示zqdm是右对齐
														// 若不是代码规则,该字段无效
		SHORT	floatlen;								// 代码对应报价的小数位数
		CHAR	unused2;								// (废弃)(保留作为交易中心内部标识)0:股(国债为张) 1:手
		CHAR	unused3;								// (废弃)(在新结构中使用新的定义)是否支持股票拆分	0:不拆分 1:拆分
		LONG	unused4;								// (废弃)(在新结构中使用新的定义)交易所每次交易上限(其单位与jydw对应),若为0则表示没有上限
		LONG	unused5;								// (废弃)(在新结构中使用新的定义)交易所每次交易下限(其单位与jydw对应),若为0则表示没有下限
		CHAR	bz;										// 对应币种 0:人民币 1:美圆 2:港币
		CHAR	gzbs;									// 国债标志 0:国债现货 1:债券 2:可转换债券 3:国债回购
		CHAR	reserved[8];							// 保留
	} SCINFO1,*LPSCINFO1,SCSTRUC1,*LPSCSTRUC1,SCSTRUC,*LPSCSTRUC;
	typedef struct tagSCINFO2
	{	CHAR	setcode;								// 市场(0:深圳,含三板 1:上海)
		CHAR	rule[ZQDM_SIZE];						// 代码规则
		CHAR	splb;									// 商品类别
		CHAR	zhlb;									// 帐号类别(深A,深B,沪A,沪B等等)
		CHAR	lbname[17];								// 类别名称(仅显示用途)
		SHORT	floatlen;								// 代码对应报价的小数位数
		CHAR	bz;										// 对应币种 0:人民币 1:美圆 2:港币
		CHAR	gzbs;									// 国债标志 0:国债现货 1:债券 2:可转换债券 3:国债回购
		CHAR	jldw[8];								// 计量单位
		CHAR	xsdw;									// 现手单位
		CHAR	zsdw;									// 总手单位
		CHAR	kcdw;									// 库存单位
		CHAR	sbdw;									// 申报单位(前端)
		LONG	sbxx;									// 申报下限(前端,计量单位)
		LONG	sbsx;									// 申报上限(前端,万计量单位)
		FLOAT	sxfl;									// 手续费率
		FLOAT	sxfqd;									// 手续费起点
		CHAR	reserved[16];							// 保留
	} SCINFO2,*LPSCINFO2,SCSTRUC2,*LPSCSTRUC2;

	// 行情信息
	typedef struct ASELIB_API tagHQINFO
	{	CHAR		   setcode;					// 市场,SZ OR SH
		CHAR		   zqdm[ZQDM_SIZE];			// 证券代码
		CHAR		   zqmc[ZQMC_SIZE];			// 证券名称
		CHAR           tp_flag;					// 停牌标志
		FLOAT          Close;					// 前收盘价,指数
		FLOAT          Open;					// 今开盘价,指数
		FLOAT          Now;						// 现价,最近指数
		FLOAT		   Gzlx;					// 国债利息
		FLOAT          Buyp[5];					// 五个叫买价,新数据接口
		DWORD          Buyv[5];					// 对应五个叫买价的五个买盘
		FLOAT          Sellp[5];				// 五个叫卖价
		DWORD          Sellv[5];				// 对应五个叫卖价的五个卖盘
		LONG		   reserved[1];				// 保留字节(必须全空)
	} HQINFO,*LPHQINFO;
	typedef struct ASELIB_API tagHQSCINFO
	{	CHAR		   bGetHqAns;				// 行情信息是否成功
		HQINFO		   HqInfo;					// 行情信息
		CHAR		   bGetScStruc;				// 市场信息是否获取成功 1:成功,0:匹配不到
		SCSTRUC1	   ScStruc;					// 改股票对应的一些市场信息
		tagHQSCINFO()
		{	memset(this,0,size_of(tagHQSCINFO));
		}
	} HQSCINFO1,*LPHQSCINFO1,HQSCINFO,*LPHQSCINFO;
	typedef struct ASELIB_API tagHQSCINFO2
	{	CHAR		   bGetHqAns;				// 行情信息是否成功
		HQINFO		   HqInfo;					// 行情信息
		CHAR		   bGetScStruc;				// 市场信息是否获取成功 1:成功,0:匹配不到
		SCSTRUC2	   ScStruc;					// 改股票对应的一些市场信息
		tagHQSCINFO2()
		{	memset(this,0,size_of(tagHQSCINFO2));
		}
	} HQSCINFO2,*LPHQSCINFO2;
	// 港股行情信息
	typedef struct ASELIB_API tagHKHQINFO
	{	CHAR		   setcode;					// 市场,HK
		CHAR		   zqdm[HKZQDM_SIZE];		// 证券代码
		CHAR		   zqmc[HKZQMC_SIZE];		// 证券名称
		FLOAT          Close;					// 前收盘价,指数
		FLOAT          Open;					// 今开盘价,指数
		FLOAT          Now;						// 现价,最近指数
		FLOAT          Buyp[5];					// 五个叫买价,新数据接口
		DWORD          Buyv[5];					// 对应五个叫买价的五个买盘
		FLOAT          Sellp[5];				// 五个叫卖价
		DWORD          Sellv[5];				// 对应五个叫卖价的五个卖盘
		DWORD		   PreVol;					// 最小交易股数
		WORD		   HSpread;					// 最小卖出挂单交易单位
		WORD		   LSpread;					// 最小买入挂单交易单位
		LONG		   reserved[1];				// 保留字节(必须全空)
	} HKHQINFO,*LPHKHQINFO;
	// 高速行情信息
	typedef struct ASELIB_API tagL2HQINFO
	{	CHAR		   setcode;					// 市场,L2
		CHAR		   zqdm[ZQDM_SIZE];			// 证券代码
		CHAR		   zqmc[ZQMC_SIZE];			// 证券名称
		FLOAT		   Close;					// 前收盘价
		FLOAT   	   Open;       				// 今开盘价
		FLOAT   	   Max;        				// 最高价
		FLOAT   	   Min;        				// 最低价
		FLOAT   	   Now;        				// 现价
		FLOAT		   Buyp[10];				// 叫买价
		DWORD   	   Buyv[10];				// 对应叫买价的买盘
		FLOAT   	   Sellp[10];				// 叫卖价
		DWORD   	   Sellv[10];				// 对应叫卖价的卖盘
		DWORD   	   Volume;     				// 总手
		FLOAT   	   Amount;     				// 总成交金额
		DWORD		   RestVol;					// 成交碎股
		DWORD		   CJBS;					// 成交笔数
		FLOAT		   Gzlx;					// 国债利息
		FLOAT		   Jjjz;					// ETF净值
		LONG		   reserved[1];				// 保留字节(必须全空)
	} L2HQINFO,*LPL2HQINFO;
#endif





// 自动升级模式(兼容老版本定义)
#define UPGRADE_NO				(0)					// 自动升级模式:不自动升级
#define UPGRADE_PACKAGE			(1)					// 自动升级模式:打包升级
#define UPGRADE_PIECE			(2)					// 自动升级模式:按照模块升级


// 插件配置信息(兼容老版本定义)
typedef struct tagPLUGININFO
{	CHAR	m_szModule[32];							// 插件文件名(文件必须位于PLUGIN目录下)
	MD5BIN  m_md5Module;							// 插件文件MD5信息(动态构建)
} PLUGININFO,*LPPLUGININFO;


// 入口点索引信息(将被传递给客户端)(兼容老版本定义)
typedef struct tagENTRYPOINTIDX
{	WORD    m_wEntryPointID;						// 入口点ID
	CHAR	m_szDescription[41];					// 入口点名
} ENTRYPOINTIDX,*LPENTRYPOINTIDX;




// 协议前缀
#define STD_PROT					CONST		// 标准协议集














#pragma pack()
#endif
