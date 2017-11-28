//////////////////////////////////////////////////////////////////////////
// 创建日期:2006/07/20
// 功能说明:标准数据字典的字段定义
// 变更记录:
//            2007/04/29 为规范全部请求格式
// 特别注释:
//            1.对于招商证券招行卡号方式,每次请求均要送入一个股东代码类型和股东代码,不合理但必须兼容保留
//              这里约定:
//                a.客户端每次均送入股东代码类型以及股东代码
//                b.如字段本身作为保留字段,则送入股东代码列表的最后一次选中的股东代码类型和股东代码
//                c.如字段本身已使用了有意义的,不需要更改其原有含义
//                d.本约定将只对招商证券招行卡号方式有效,其他所有标记保留的字段均在一定程度上扩大了
//                  程序对带宽的占用率,也是一种对程序理解的障碍
//              以后类似情况均要采用静态缓存处理,不再使用影响系统架构的方法.
//            2.对于保留字段,客户端除特例情况不应该送入任何信息,这些字段随时会有其他含义.
//            3.对于可选字段其本身代表特殊含义并暗示一种特殊功能,后台可以对这些字段提供的功能选择性支持
//              但这些功能未必客户端需要使用或者已经使用的,也就是说是非必要的(对于当日委托查询字段此处将
//              做一些特殊处理)
//            4.对于撤单需要送入更多请求的方法采用请求自动填充的方法
//              即撤单请求中如果包含有可撤单查询返回的字段,应该首先通过可撤单查询返回的结果填充这些字段
//            5.系统从当前版本将支持动态缓存交换(Cookies),需要CWtCache2,CWtCommon2和CWtDict3支持
//              缓存的交换策略为:
//                    CACHE容器-->COOKIES
//                    REQ|COOKIES-->服务器
//                    客户端<--ANS|COOKIES
//                    CACHE容器<--COOKIES
//            6.对于安全中心相关的处理逻辑
//              a.服务器未配置安全中心路由
//                a).客户端按照EMBWT.CFG控制客户端登录显示界面
//                b).客户端自动忽略安全的相关协议(登录时)
//                c).客户端不显示安全相关的服务界面(例如安全管理)
//              b.服务器配置有安全中心路由
//                a).客户端按照EMBWT.CFG控制客户端登录显示界面
//                b).客户端任何安全业务相关的协议时都必须送到服务器(登录时)
//                c).客户端根据服务器支持的安全方式控制安全的相关界面
//                   若服务器不支持认证口令和数字证书,(不显示安全相关界面)
//              c.登录时,异常和容错处理
//                a).安全中心配置字典为空,等同于客户端未配置安全中心(不显示安全相关界面)
//                b).客户端登录时候返回路由繁忙,等同于客户端未配置安全中心
//                c).客户端登录时候返回数据库繁忙,等同于客户端未配置安全中心
#ifndef __IX_STDPROT_WT_STRU__H__
#define __IX_STDPROT_WT_STRU__H__
#pragma pack(1)
#ifndef ASELIB_API
	#error "ASELib.h" must be included.
#endif
#ifndef ASELIBIMPL_DEFINED
	#error "ASELibIXImpl.h" must be included.
#endif


//---------------------------------------------------------------------------
// Part.I 辅助宏
//---------------------------------------------------------------------------

	// 结构-字段定义
	typedef struct tagSTRUCTFIELD
	{	WORD			m_wStruID;
		LPWORD			m_pwFields;
		WORD			m_wFieldNum;
	} STRUCTFIELD;

	// 开始结构字段定义
	#define BEGIN_STRUCT_FIELD_DEF(NAME)		\
		const STRUCTFIELD NAME[]={

	// 定义结构字段
	#define DECLARE_STRUCT_FIELD(STRU_ID,STRU_DEF)	\
		{STRU_ID,(LPWORD)STRU_DEF,size_of(STRU_DEF)/size_of(STRU_DEF[0])},

	// 结束结构字段定义
	#define END_STRUCT_FIELD_DEF(NAME)			\
		};

	// 字段初始化函数
	inline BOOL InitDict(CWtDict *pDict,
					const FIELDINFO* pFieldInfo,WORD wFieldNum,
					const WORD* pwStructInfo,WORD wStructNum,
					const STRUCTFIELD* pStructFieldInfo,WORD wStructFieldNum)
	{	if(!pDict->RegisterFieldInfo(pFieldInfo,wFieldNum)) return FALSE;
		if(!pDict->RegisterStruct(pwStructInfo,wStructNum)) return FALSE;
		for(WORD i=0; i<wStructFieldNum; i++)
		{	if(!pDict->RegisterStructField(pStructFieldInfo[i].m_wStruID,pStructFieldInfo[i].m_pwFields,pStructFieldInfo[i].m_wFieldNum))
				return FALSE;
		}
		return TRUE;
	}


	#define INIT_SIMPLE_DICT(pDict)																						\
			InitDict(pDict,tdxSimpleFieldInfo,size_of(tdxSimpleFieldInfo)/size_of(tdxSimpleFieldInfo[0]),				\
					tdxSimpleStructInfo,size_of(tdxSimpleStructInfo)/size_of(tdxSimpleStructInfo[0]),					\
					tdxSimpleStructFieldInfo,size_of(tdxSimpleStructFieldInfo)/size_of(tdxSimpleStructFieldInfo[0]))

	#define INIT_COMMON_DICT(pDict)																						\
			InitDict(pDict,tdxCommonFieldInfo,size_of(tdxCommonFieldInfo)/size_of(tdxCommonFieldInfo[0]),				\
					tdxCommonStructInfo,size_of(tdxCommonStructInfo)/size_of(tdxCommonStructInfo[0]),					\
					tdxCommonStructFieldInfo,size_of(tdxCommonStructFieldInfo)/size_of(tdxCommonStructFieldInfo[0]))

	#define INIT_SCNTR_DICT(pDict)																						\
			InitDict(pDict,tdxScntrFieldInfo,size_of(tdxScntrFieldInfo)/size_of(tdxScntrFieldInfo[0]),					\
					tdxScntrStructInfo,size_of(tdxScntrStructInfo)/size_of(tdxScntrStructInfo[0]),						\
					tdxScntrStructFieldInfo,size_of(tdxScntrStructFieldInfo)/size_of(tdxScntrStructFieldInfo[0]))
	
	#define INIT_RZ_DICT(pDict)																							\
			InitDict(pDict,tdxRZFieldInfo,size_of(tdxRZFieldInfo)/size_of(tdxRZFieldInfo[0]),							\
					tdxRZStructInfo,size_of(tdxRZStructInfo)/size_of(tdxRZStructInfo[0]),								\
					tdxRZStructFieldInfo,size_of(tdxRZStructFieldInfo)/size_of(tdxRZStructFieldInfo[0]))


//---------------------------------------------------------------------------
// Part.II 标准字段定义
//---------------------------------------------------------------------------

// 简化字典字段定义
const FIELDINFO tdxSimpleFieldInfo[]=
{
//	{	字段类型,					数据类型,		显示(对齐)方法,宽度,	字段说明,				其它标记,	},

	{	TDX_ID_ZQJYBS,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"证券交易标识",			1,0,0,0,0,	},
	{	TDX_ID_YYB,					TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"营业部代码",			0,0,0,0,0,	},
	{	TDX_ID_OP_WTFS,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"委托方式",				0,0,0,0,0,	},
	{	TDX_ID_CZBZ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"操作标志",				1,0,0,0,0,	},
	{	TDX_ID_KHH,					TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"客户号",				0,0,0,0,0,	},
	{	TDX_ID_ZJZH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"资金帐号",				0,0,0,0,0,	},
	{	TDX_ID_KHMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"客户名称",				0,0,0,0,0,	},
	{	TDX_ID_GDDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"股东代码",				0,0,0,0,0,	},
	{	TDX_ID_ZHLB,				TDX_DT_STRING,	TDX_DISP_RIGHT,   2,	"帐号类别",				1,0,0,0,0,	},
	{	TDX_ID_JYMM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"交易密码",				1,0,0,0,0,	},
	{	TDX_ID_TXMM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"通讯密码",				1,0,0,0,0,	},
	{	TDX_ID_WTFS,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"委托方式",				1,0,0,0,0,	},
	{	TDX_ID_QZKTBZ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"权证开通标志",			1,0,0,0,0,	},
	{	TDX_ID_GTZDKMBS,			TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"取柜台可买数量",		1,0,0,0,0,	},
	{	TDX_ID_KHQXDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"客户权限代码",			0,0,0,0,0,	},
	{	TDX_ID_KHQXMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"客户权限名称",			0,0,0,0,0,	},
	{	TDX_ID_OTCJYBS,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"OTC交易标志",			1,0,0,0,0,	},
	{	TDX_ID_XYJYBS,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"融资融券标识",			1,0,0,0,0,	},
	{	TDX_ID_SFCGBS,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"三方存管标识",			1,0,0,0,0,	},
	{	TDX_ID_DFKHDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"对方客户代码",			0,0,0,0,0,	},
	{	TDX_ID_DFFZDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"对方分支代码",			0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_JJBS,			TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"开放式基金标识",		0,0,0,0,0,	},
	{	TDX_ID_ZDJYBZ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"指定交易标识",			1,0,0,0,0,	},
	{	TDX_ID_ETFBS,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"ETF标识",				1,0,0,0,0,	},
                                                                        	
	{	TDX_ID_BANKCODE,			TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"银行代码",				0,0,0,0,0,	},
	{	TDX_ID_BANKYYB,				TDX_DT_STRING,	TDX_DISP_RIGHT,  40,	"银行营业部",			0,0,0,0,0,	},
	{	TDX_ID_BANKGDTYPE,			TDX_DT_STRING,	TDX_DISP_RIGHT,   2,	"银行股东代码登录市场",	0,0,0,0,0,	},
                                                                        	
	{	TDX_ID_ZJHM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"证件号码",				0,0,0,0,0,	},
	{	TDX_ID_MOBILEPHONE,			TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"移动电话",				0,0,0,0,0,	},
	{	TDX_ID_USERPHONE,			TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"住宅电话",				0,0,0,0,0,	},
	{	TDX_ID_USEREMAIL,			TDX_DT_STRING,	TDX_DISP_RIGHT,  40,	"用户EMAIL",			0,0,0,0,0,	},
	{	TDX_ID_SHGD,				TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"上海股东",				0,0,0,0,0,	},
	{	TDX_ID_SZGD,				TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"深圳股东",				0,0,0,0,0,	},
	{	TDX_ID_KHTYPE,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"开户类别",				0,0,0,0,0,	},

	{	TDX_ID_TSXX0,				TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"提示信息0",			0,0,0,0,0,	},
	{	TDX_ID_TSXX1,				TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"提示信息1",			0,0,0,0,0,	},
	{	TDX_ID_TSXX2,				TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"提示信息2",			0,0,0,0,0,	},
	{	TDX_ID_TSXX3,				TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"提示信息3",			0,0,0,0,0,	},
	{	TDX_ID_TSXX4,				TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"提示信息4",			0,0,0,0,0,	},
	{	TDX_ID_TSXX5,				TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"提示信息5",			0,0,0,0,0,	},
	{	TDX_ID_TSXX6,				TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"提示信息6",			0,0,0,0,0,	},
	{	TDX_ID_TSXX7,				TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"提示信息7",			0,0,0,0,0,	},
	{	TDX_ID_TSXX8,				TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"提示信息8",			0,0,0,0,0,	},
	{	TDX_ID_TSXX9,				TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"提示信息9",			0,0,0,0,0,	},

	{	TDX_ID_FJZH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"附加账号",				0,0,0,0,0,	},
	{	TDX_ID_XYJYTSXX,			TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"信用交易提示信息",	    0,0,0,0,0,	},

	{	TDX_ID_QHJYTSXX,			TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"期货交易提示信息",		0,0,0,0,0,	},

	{	TDX_ID_XT_ERRCODE,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"错误号",				0,0,0,0,0,	},
	{	TDX_ID_XT_ERRMSG,			TDX_DT_STRING,	TDX_DISP_RIGHT,  80,	"错误信息",				0,0,0,0,0,	},                       	
	{	TDX_ID_XT_MACADDR,			TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"MAC地址",				0,0,0,0,0,	},
	{	TDX_ID_XT_CLITYPE,			TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"客户类别",				0,0,0,0,0,	},
	{	TDX_ID_XT_OEM_FLAG,			TDX_DT_CHAR,	TDX_DISP_RIGHT,  16,	"OEM标识",				0,0,0,0,0,	},
	{	TDX_ID_XT_AUTH_MODE,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"认证方式",				0,0,0,0,0,	},
	{	TDX_ID_XT_AUTH_INFO,		TDX_DT_CHAR,	TDX_DISP_RIGHT, 512,	"认证信息",				0,0,0,0,0,	},
	{	TDX_ID_XT_AUTH_NEWINFO,		TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"认证新信息",			0,0,0,0,0,	},
	{	TDX_ID_XT_BRANCHID,			TDX_DT_CHAR,	TDX_DISP_RIGHT,  10,	"营业部ID",				0,0,0,0,0,	},
	{	TDX_ID_XT_RESERVED,			TDX_DT_STRING,	TDX_DISP_RIGHT,  80,	"保留信息",				1,0,0,0,0,	},
	{	TDX_ID_RETINFO,				TDX_DT_STRING,	TDX_DISP_RIGHT,  80,	"返回信息",				0,0,0,0,0,	},
	{	TDX_ID_XT_RECONNECTFLAG,	TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"断线重联标志",			1,0,0,0,0,	},
	{	TDX_ID_XT_COUNTERSTATUS,	TDX_DT_STRING,	TDX_DISP_RIGHT,  80,	"柜台状态",				0,0,0,0,0,	},
	{	TDX_ID_XT_VIPFLAG,			TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"VIP标志",				1,0,0,0,0,	},
	{	TDX_ID_XT_CLIENTRIGHTS,		TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"客户权限",				1,0,0,0,0,	},
	{	TDX_ID_XT_LAST_LOGIN_DATE,	TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"上次登录日期",			1,0,0,0,0,	},
	{	TDX_ID_XT_LAST_LOGIN_TIME,	TDX_DT_TIME,	TDX_DISP_RIGHT,   8,	"上次登录时间",			1,0,0,0,0,	},
	{	TDX_ID_XT_AHTHCHAR1,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"验证字符1",			1,0,0,0,0,	},
	{	TDX_ID_XT_AHTHCHAR2,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"验证字符2",			1,0,0,0,0,	},
	{	TDX_ID_XT_CHECKRISKFLAG,	TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"检查风险标志",			1,0,0,0,0,	},
	{	TDX_ID_XT_FJYZHBZ,			TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"非交易帐号标志",		1,0,0,0,0,	},
	{	TDX_ID_XT_JZJJKHBZ,			TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"禁止基金开户标志",		1,0,0,0,0,	},
	{	TDX_ID_RZ_LEVER,			TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"用户级别",				0,0,0,0,0,	},
	{	TDX_ID_XT_INCREMENTMODE,	TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"增量模式开关",			0,0,0,0,0,	},
	{	TDX_ID_XT_PARAM,			TDX_DT_STRING,	TDX_DISP_RIGHT,  80,	"参数",					0,0,0,0,0,	},
	{	TDX_ID_XT_MODE,				TDX_DT_STRING,	TDX_DISP_RIGHT,  80,	"模式",					0,0,0,0,0,	},
	{	TDX_ID_XT_DESCRIPTION,		TDX_DT_STRING,	TDX_DISP_RIGHT,  80,	"描述",					0,0,0,0,0,	},
	{	TDX_ID_XT_QUERYMODE,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"查询模式",				0,0,0,0,0,	},
	{	TDX_ID_XT_PASSWORDFLAG,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"密码标志",				0,0,0,0,0,	},
	{	TDX_ID_XT_HANDLE,			TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"句柄",					1,0,0,0,0,	},
	{	TDX_ID_XT_GTLB,				TDX_DT_STRING,	TDX_DISP_RIGHT,   1,	"柜台类别",				1,0,0,0,0,	},
	{	TDX_ID_XT_MACHINEINFO,		TDX_DT_STRING,	TDX_DISP_RIGHT, 800,	"机器信息",				0,0,0,0,0,	},
	{	TDX_ID_XT_CLIVER,			TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"客户端版本",			0,0,0,0,0,	},
	{	TDX_ID_XT_LOGINTYPE,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"登录帐号类别",			0,0,0,0,0,	},
	{	TDX_ID_XT_LOGINID,			TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"登录ID",				0,0,0,0,0,	},
	{	TDX_ID_XT_LOGINPASSWD,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"登录密码",				0,0,0,0,0,	},
	{	TDX_ID_XT_COMMPASSWD,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"通讯密码",				0,0,0,0,0,	},
	{	TDX_ID_XT_FUNCID,			TDX_DT_CHAR,	TDX_DISP_RIGHT,   3,	"功能ID",				0,0,0,0,0,	},
	{	TDX_ID_XT_FUNCDICTTAG,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   3,	"功能字典标识",			0,0,0,0,0,	},
	{	TDX_ID_XT_FUNCCONTENT,		TDX_DT_CHAR,	TDX_DISP_RIGHT, 800,	"功能内容",				0,0,0,0,0,	},
	{	TDX_ID_XT_LIMITMODE,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"受限模式",				0,0,0,0,0,	},
	{	TDX_ID_XT_MACHINECODE,		TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"机器特征码",			0,0,0,0,0,	},
	{	TDX_ID_XT_MOBILECHECKCODE,	TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"手机校验码",			0,0,0,0,0,	},
	{	TDX_ID_XT_BRANCHMODIFY,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"营业部改变",			0,0,0,0,0,	},
	{	TDX_ID_XT_NEEDEDAUTHMODE,	TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"所需认证方式",			0,0,0,0,0,	},
	{	TDX_ID_XT_SESSION,			TDX_DT_STRING,	TDX_DISP_RIGHT, 128,	"SESSION信息",			0,0,0,0,0,	},
	{	TDX_ID_XT_URL,				TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"URL",					0,0,0,0,0,	},
	{	TDX_ID_XT_INFOCOLUMN,		TDX_DT_STRING,	TDX_DISP_RIGHT, 128,	"资讯栏目",				0,0,0,0,0,	},
	{	TDX_ID_XT_REALCLIENTVERSION,TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"内部客户端版本",		0,0,0,0,0,	},
	{	TDX_ID_XT_NEEDCONFIRMFLAGS,	TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"需确认的标识串",		0,0,0,0,0,	},
	{	TDX_ID_XT_URL2,				TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"URL2",					0,0,0,0,0,	},
	{	TDX_ID_XT_REDIRECTFLAG,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"重定向标志",			0,0,0,0,0,	},
	{	TDX_ID_XT_REDIRECTINFO,		TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"重定向信息",			0,0,0,0,0,	},
	{	TDX_ID_XT_LAST_LOGIN_LOCATION,TDX_DT_STRING,TDX_DISP_RIGHT, 128,	"上次登录位置",			1,0,0,0,0,	},
	{	TDX_ID_XT_TOKEN,			TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"令牌",					0,0,0,0,0,	},
	{	TDX_ID_XT_PREPASSWORD0,		TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"预处理密码0",			0,0,0,0,0,	},
	{	TDX_ID_XT_PREPASSWORD1,		TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"预处理密码1",			0,0,0,0,0,	},
	{	TDX_ID_XT_PREPASSWORD2,		TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"预处理密码2",			0,0,0,0,0,	},
	{	TDX_ID_XT_PREPASSWORD3,		TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"预处理密码3",			0,0,0,0,0,	},
	{	TDX_ID_XT_PREPASSWORD4,		TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"预处理密码4",			0,0,0,0,0,	},
	{	TDX_ID_XT_PREPARAM0,		TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"预处理参数0",			0,0,0,0,0,	},
	{	TDX_ID_XT_PREPARAM1,		TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"预处理参数1",			0,0,0,0,0,	},
	{	TDX_ID_XT_PREPARAM2,		TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"预处理参数2",			0,0,0,0,0,	},
	{	TDX_ID_XT_PREPARAM3,		TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"预处理参数3",			0,0,0,0,0,	},
	{	TDX_ID_XT_PREPARAM4,		TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"预处理参数4",			0,0,0,0,0,	},
	{	TDX_ID_XT_PREPARAM5,		TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"预处理参数5",			0,0,0,0,0,	},
	{	TDX_ID_XT_PREPARAM6,		TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"预处理参数6",			0,0,0,0,0,	},
	{	TDX_ID_XT_PREPARAM7,		TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"预处理参数7",			0,0,0,0,0,	},
	{	TDX_ID_XT_PREPARAM8,		TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"预处理参数8",			0,0,0,0,0,	},
	{	TDX_ID_XT_PREPARAM9,		TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"预处理参数9",			0,0,0,0,0,	},
	{	TDX_ID_XT_LOGINEMAIL,		TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"登录Email",			0,0,0,0,0,	},
	{	TDX_ID_XT_TRADEEMAIL,		TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"交易Email",			0,0,0,0,0,	},
	{	TDX_ID_XT_MULTINITICE,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"多提示信息",			1,0,0,0,0,	},
	{	TDX_ID_XT_RISKPARAM,		TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"风险参数",				1,0,0,0,0,	},
	{	TDX_ID_XT_LOGINRETURNPARAM,	TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"登录返回参数",			1,0,0,0,0,	},
	{	TDX_ID_XT_MOBILEMACHINEINFO,TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"手机机器信息",			1,0,0,0,0,	},
	{	TDX_ID_XT_PACKAGELIST,		TDX_DT_STRING,	TDX_DISP_RIGHT,1024,	"套餐列表",				1,0,0,0,0,	},
	{	TDX_ID_XT_PRODUCTLIST,		TDX_DT_STRING,	TDX_DISP_RIGHT,1024,	"产品列表",				1,0,0,0,0,	},
	{	TDX_ID_XT_FEATURELIST,		TDX_DT_STRING,	TDX_DISP_RIGHT,1024,	"功能列表",				1,0,0,0,0,	},
	{	TDX_ID_XT_CONFIGLIST,		TDX_DT_STRING,	TDX_DISP_RIGHT,1024,	"配置列表",				1,0,0,0,0,	},
	{	TDX_ID_XT_LOGINENTERPARAM,	TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"登录输入参数",			1,0,0,0,0,	},
	{	TDX_ID_XT_ALGORIGHTLIST,	TDX_DT_STRING,	TDX_DISP_RIGHT,1024,	"算法权限列表",			1,0,0,0,0,	},
	{	TDX_ID_XT_FUNCTIONVERSION,	TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"功能版本",				1,0,0,0,0,	},
	{	TDX_ID_XT_CLIENTINVERSION,	TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"客户端内部版本",		1,0,0,0,0,	},
	{	TDX_ID_XT_VERSIONSTRING,	TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"版本字符串",			1,0,0,0,0,	},
};

// 标准字典字段定义
const FIELDINFO tdxCommonFieldInfo[]=
{
//	{	字段类型,					数据类型,		显示(对齐)方法,宽度,	字段说明,				其它标记,	},

	{	TDX_ID_PARAM_YHSXX,			TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"(参数)印花税下限",		1,0,0,0,0,	},
	{	TDX_ID_PARAM_SXFXX,			TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"(参数)手续费下限",		1,0,0,0,0,	},
	{	TDX_ID_PARAM_GHFXX,			TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"(参数)过户费下限",		1,0,0,0,0,	},
	{	TDX_ID_PARAM_QTJEFXX,		TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"(参数)其他金额费下限",	1,0,0,0,0,	},
	{	TDX_ID_PARAM_QTSLFXX,		TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"(参数)其他数量费下限",	1,0,0,0,0,	},
	{	TDX_ID_ZQJYBS,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"证券交易标识",			1,0,0,0,0,	},
	{	TDX_ID_PARAM_CBJE,			TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"(参数)成本金额",		1,0,0,0,0,	},
	{	TDX_ID_PARAM_CBSL,			TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"(参数)成本数量",		1,0,0,0,0,	},
	{	TDX_ID_PARAM_YHSL,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"(参数)印花税率",		1,0,0,0,0,	},
	{	TDX_ID_PARAM_SXFL,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"(参数)手续费率",		1,0,0,0,0,	},
	{	TDX_ID_PARAM_GHFL,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"(参数)过户费率",		1,0,0,0,0,	},
	{	TDX_ID_PARAM_QTJEFL,		TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"(参数)其他金额费率",	1,0,0,0,0,	},
	{	TDX_ID_PARAM_QTSLFL,		TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"(参数)其他数量费率",	1,0,0,0,0,	},
	{	TDX_ID_FQSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"放弃数量",				0,0,0,0,0,	},
	{	TDX_ID_MC,					TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"名次",					0,0,0,0,0,	},

	{	TDX_ID_SCFLAG,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"交易所代码",			1,0,0,0,0,	},
	{	TDX_ID_SCNAME,				TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"交易所名称",			0,0,0,0,0,	},
	{	TDX_ID_YYB,					TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"营业部代码",			0,0,0,0,0,	},
	{	TDX_ID_YYBMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,  40,	"营业部名称",			0,0,0,0,0,	},
	{	TDX_ID_TDX_OEM_FLAG,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"OEM标志",				1,0,0,0,0,	},
	{	TDX_ID_JYYDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"交易员代码",			0,0,0,0,0,	},
	{	TDX_ID_LXRXM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"联系人姓名",			0,0,0,0,0,	},
	{	TDX_ID_LXFS,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"联系方式",				0,0,0,0,0,	},
	{	TDX_ID_NC,					TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"昵称",					0,0,0,0,0,	},
	{	TDX_ID_LMQX,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"栏目权限",				0,0,0,0,0,	},
	{	TDX_ID_OP_WTFS,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"委托方式",				0,0,0,0,0,	},
	{	TDX_ID_OP_GYDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"柜员代码",				0,0,0,0,0,	},
	{	TDX_ID_OP_GYMM,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"柜员密码",				0,0,0,0,0,	},
	{	TDX_ID_CZBZ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"操作标志",				1,0,0,0,0,	},
	{	TDX_ID_CZZT,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"操作状态",				1,0,0,0,0,	},
	{	TDX_ID_HZHGZT,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"合作回购状态",			0,0,0,0,0,	},
	{	TDX_ID_ZDJYBZ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"指定交易",				0,0,0,0,0,	},
	{	TDX_ID_SQKTWZ,				TDX_DT_STRING,	TDX_DISP_RIGHT,  40,	"申请开通的网址",		0,0,0,0,0,	},
	{	TDX_ID_HZHGDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"合作回购代码",			0,0,0,0,0,	},
	{	TDX_ID_HZPSDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"合作配售代码",			0,0,0,0,0,	},
	{	TDX_ID_KHH,					TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"客户号",				0,0,0,0,0,	},
	{	TDX_ID_ZJZH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"资金帐号",				0,0,0,0,0,	},
	{	TDX_ID_KHMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"客户名称",				0,0,0,0,0,	},
	{	TDX_ID_GDDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"股东代码",				0,0,0,0,0,	},
	{	TDX_ID_GDMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"股东名称",				0,0,0,0,0,	},
	{	TDX_ID_ZHLB,				TDX_DT_STRING,	TDX_DISP_RIGHT,   2,	"帐号类别",				1,0,0,0,0,	},
	{	TDX_ID_KSRQ,				TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"开始日期",				0,0,0,0,0,	},
	{	TDX_ID_ZZRQ,				TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"终止日期",				0,0,0,0,0,	},
	{	TDX_ID_USERPHONE,			TDX_DT_STRING,	TDX_DISP_RIGHT,  40,	"用户联系方式",			0,0,0,0,0,	},
	{	TDX_ID_USEREMAIL,			TDX_DT_STRING,	TDX_DISP_RIGHT,  40,	"用户EMAIL",			0,0,0,0,0,	},
	{	TDX_ID_MMBZ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"买卖标志",				1,0,0,0,0,	},
	{	TDX_ID_MMBZSM,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   8,	"买卖标志",				0,0,0,0,0,	},
	{	TDX_ID_BZ,					TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"币种",					0,0,0,0,0,	},
	{	TDX_ID_JYDW,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"交易单位",				0,0,0,0,0,	},
	{	TDX_ID_JYMM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"交易密码",				1,0,0,0,0,	},
	{	TDX_ID_ZJMM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"资金密码",				1,0,0,0,0,	},
	{	TDX_ID_XJYMM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"新交易密码",			1,0,0,0,0,	},
	{	TDX_ID_XZJMM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"新资金密码",			1,0,0,0,0,	},
	{	TDX_ID_TXMM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"通讯密码",				1,0,0,0,0,	},
	{	TDX_ID_SECURETYPE,			TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"安全方式",				0,0,0,0,0,	},
	{	TDX_ID_ZQDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"证券代码",				0,0,0,0,0,	},
	{	TDX_ID_ZQMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"证券名称",				0,0,0,0,0,	},
	{	TDX_ID_WTRQ,				TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"委托日期",				0,0,0,0,0,	},
	{	TDX_ID_WTSJ,				TDX_DT_TIME,	TDX_DISP_RIGHT,   8,	"委托时间",				0,0,0,0,0,	},
	{	TDX_ID_WTSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"委托数量",				0,0,0,0,0,	},
	{	TDX_ID_WTJG,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"委托价格",				0,0,0,0,0,	},
	{	TDX_ID_WTBH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"委托编号",				0,0,0,0,0,	},
	{	TDX_ID_ZTSM,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"状态说明",				0,0,0,0,0,	},
	{	TDX_ID_WTJE,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"委托金额",				0,0,0,0,0,	},
	{	TDX_ID_RETINFO,				TDX_DT_STRING,	TDX_DISP_RIGHT,  80,	"返回信息",				0,0,0,0,0,	},
	{	TDX_ID_CJRQ,				TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"成交日期",				0,0,0,0,0,	},
	{	TDX_ID_CJSJ,				TDX_DT_TIME,	TDX_DISP_RIGHT,   8,	"成交时间",				0,0,0,0,0,	}, 
	{	TDX_ID_CJSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"成交数量",				0,0,0,0,0,	},
	{	TDX_ID_CJJG,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"成交价格",				0,0,0,0,0,	},
	{	TDX_ID_CJJE,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"成交金额",				0,0,0,0,0,	},
	{	TDX_ID_CJBH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"成交编号",				0,0,0,0,0,	},
	{	TDX_ID_HZPSZT,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"合作配售状态",			1,0,0,0,0,	},
	{	TDX_ID_HFBZ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"合法标志",				1,0,0,0,0,	},
	{	TDX_ID_DFMM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"对方密码",				1,0,0,0,0,	},
	{	TDX_ID_HFBZSM,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"合法标志",				0,0,0,0,0,	},
	{	TDX_ID_CDBZ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"撤单标志",				1,0,0,0,0,	},
	{	TDX_ID_KCDBZ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"可撤单标志",			1,0,0,0,0,	},
	{	TDX_ID_LSH,					TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"流水号",				0,0,0,0,0,	},
	{	TDX_ID_DJSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"冻结数量",				0,0,0,0,0,	},
	{	TDX_ID_DJZJ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"冻结资金",				0,0,0,0,0,	},
	{	TDX_ID_CDSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"撤单数量",				0,0,0,0,0,	},
	{	TDX_ID_CDBZSM,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"撤单标志",				0,0,0,0,0,	},
	{	TDX_ID_LESSPRESSURE,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"减轻柜台压力",			1,0,0,0,0,	},
	{	TDX_ID_FIRSTZJCX,			TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"第一次查询资金",		1,0,0,0,0,	},
	{	TDX_ID_WTFS,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"委托方式",				1,0,0,0,0,	},
	{	TDX_ID_PHRQ,				TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"配号日期",				0,0,0,0,0,	},
	{	TDX_ID_QSPH,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"起始配号",				0,0,0,0,0,	},
	{	TDX_ID_PHSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"配号数量",				0,0,0,0,0,	},
	{	TDX_ID_XWDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"席位代码",				0,0,0,0,0,	},
	{	TDX_ID_ZQS,					TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"中签数",				0,0,0,0,0,	},
	{	TDX_ID_PHSLPHCX,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"配号数量",				0,0,0,0,0,	},
	{	TDX_ID_ZQRQ,				TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"中签日期",				0,0,0,0,0,	},
	{	TDX_ID_QZLX,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"权证类型",				0,0,0,0,0,	},
	{	TDX_ID_XQFS,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"行权方式",				0,0,0,0,0,	},
	{	TDX_ID_XQBL,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"行权比例",				0,0,0,0,0,	},
	{	TDX_ID_JSFS,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"结算方式",				0,0,0,0,0,	},
	{	TDX_ID_FXBZ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"风险标志",				0,0,0,0,0,	},
	{	TDX_ID_FXSM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  80,	"风险说明",				0,0,0,0,0,	},
	{	TDX_ID_JGRQ,				TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"交割日期",				0,0,0,0,0,	},
	{	TDX_ID_KHLBSM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  80,	"客户类别说明",			0,0,0,0,0,	},
	{	TDX_ID_KHXZSM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  80,	"客户性质说明",			0,0,0,0,0,	},
	{	TDX_ID_KHZTSM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  80,	"客户状态说明",			0,0,0,0,0,	},
	{	TDX_ID_ZXJYGS,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"最小交易股数",			0,0,0,0,0,	},
	{	TDX_ID_SHGD,				TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"上海股东",				0,0,0,0,0,	},
	{	TDX_ID_SZGD,				TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"深圳股东",				0,0,0,0,0,	},
	{	TDX_ID_QZKTBZ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"权证开通标志",			1,0,0,0,0,	},
	{	TDX_ID_SGRDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"收购人代码",			0,0,0,0,0,	},
	{	TDX_ID_YYSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"要约数量",				0,0,0,0,0,	},
	{	TDX_ID_SBSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"申报数量",				0,0,0,0,0,	},
	{	TDX_ID_WTFSSM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  40,	"报价方式",				0,0,0,0,0,	},
	{	TDX_ID_XTXMM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"新通讯密码",			1,0,0,0,0,	},
	{	TDX_ID_DZDLX,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"对帐单类型",			0,0,0,0,0,	},
	{	TDX_ID_XXSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"选项数量",				0,0,0,0,0,	},
	{	TDX_ID_ZTSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"在途数量",				0,0,0,0,0,	},

	{	TDX_ID_ZQSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"证券数量",				0,0,0,0,0,	},
	{	TDX_ID_KMSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"可卖数量",				0,0,0,0,0,	},
	{	TDX_ID_CBJ,					TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"成本价",				0,0,0,0,0,	},
	{	TDX_ID_DQCB,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"当前成本",				0,0,0,0,0,	},
	{	TDX_ID_ZXJ,					TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"最新价",				0,0,0,0,0,	},
	{	TDX_ID_FDYK,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"浮动盈亏",				0,0,0,0,0,	},
	{	TDX_ID_ZXSZ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"最新市值",				0,0,0,0,0,	},
	{	TDX_ID_YJ,					TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"佣金",					0,0,0,0,0,	},
	{	TDX_ID_KHF,					TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"过户费",				0,0,0,0,0,	},
	{	TDX_ID_CJF,					TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"成交费",				0,0,0,0,0,	},
	{	TDX_ID_JSF,					TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"结算费",				0,0,0,0,0,	},
	{	TDX_ID_YHS,					TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"印花税",				0,0,0,0,0,	},
	{	TDX_ID_ZDKM,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"最大可买",				0,0,0,0,0,	},
	{	TDX_ID_SXF,					TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"手续费",				0,0,0,0,0,	},
	{	TDX_ID_GPLX,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"股票类型",				0,0,0,0,0,	},
	{	TDX_ID_GTZDKMBS,			TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"取柜台可买数量",		1,0,0,0,0,	},
	{	TDX_ID_DRMRSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"今买数量",				0,0,0,0,0,	},
	{	TDX_ID_GPLBP,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"股票篮买入价",			0,0,0,0,0,	},
	{	TDX_ID_GPLBV,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"股票篮买入量",			0,0,0,0,0,	},
	{	TDX_ID_GPLSP,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"股票篮卖出价",			0,0,0,0,0,	},
	{	TDX_ID_GPLSV,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"股票篮卖出量",			0,0,0,0,0,	},
	{	TDX_ID_KHQXDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"客户权限代码",			0,0,0,0,0,	},
	{	TDX_ID_KHQXMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"客户权限名称",			0,0,0,0,0,	},
	{	TDX_ID_BBJ,					TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"保本价",				0,0,0,0,0,	},
	{	TDX_ID_YWTSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"原委托数量",			0,0,0,0,0,	},
	{	TDX_ID_YWTJG,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"原委托价格",			0,0,0,0,0,	},
	{	TDX_ID_QTF,					TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"其他费",				0,0,0,0,0,	},
	{	TDX_ID_ZXMRBDJW,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"最小买入变动价位",		0,0,0,0,0,	},
	{	TDX_ID_ZXMCBDJW,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"最小卖出变动价位",		0,0,0,0,0,	},
	{	TDX_ID_ZCZJZH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"转出资金帐号",			0,0,0,0,0,	},
	{	TDX_ID_ZRZJZH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"转入资金帐号",			0,0,0,0,0,	},
	{	TDX_ID_YKBL,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"盈亏比例(%)",			0,0,0,0,0,	},
	{	TDX_ID_ZJZHEX,				TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"资金帐号",				0,0,0,0,0,	},
	{	TDX_ID_SXYK,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"实现盈亏",				0,0,0,0,0,	},
	{	TDX_ID_TBYK,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"摊薄盈亏",				0,0,0,0,0,	},
	{	TDX_ID_LX,					TDX_DT_DOUBLE,	TDX_DISP_RIGHT,   1,	"类型",					0,0,0,0,0,	},
	{	TDX_ID_CJDF,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"成交单费",				0,0,0,0,0,	},
	{	TDX_ID_WTDF,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"委托单费",				0,0,0,0,0,	},
	{	TDX_ID_JJRDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"经纪人代码",			0,0,0,0,0,	},
	{	TDX_ID_ZHZT,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"帐户状态",				0,0,0,0,0,	},
	{	TDX_ID_KGDBZ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"可改单标志",			1,0,0,0,0,	},
	{	TDX_ID_MAILADDRESS,			TDX_DT_STRING,	TDX_DISP_RIGHT,  80,	"邮寄地址",				0,0,0,0,0,	},
	{	TDX_ID_YDXH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"约定序号",				0,0,0,0,0,	},
	{	TDX_ID_DFXWDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"对方席位代码",			0,0,0,0,0,	},
	{	TDX_ID_DFZJZH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"对方资金帐号",			0,0,0,0,0,	},
	{	TDX_ID_DFGDDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"对方股东代码",			0,0,0,0,0,	},
	{	TDX_ID_DFZHLB,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"对方帐号类别",			1,0,0,0,0,	},
	{	TDX_ID_ZZHBZ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"主帐号标志",			1,0,0,0,0,	},
	{	TDX_ID_SBXH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"申报序号",				0,0,0,0,0,	},
	{	TDX_ID_LMDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"栏目代码",				0,0,0,0,0,	},
	{	TDX_ID_LMMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"栏目名称",				0,0,0,0,0,	},
	{	TDX_ID_TSXX0,				TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"提示信息0",			0,0,0,0,0,	},
	{	TDX_ID_TSXX1,				TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"提示信息1",			0,0,0,0,0,	},
	{	TDX_ID_TSXX2,				TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"提示信息2",			0,0,0,0,0,	},
	{	TDX_ID_TSXX3,				TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"提示信息3",			0,0,0,0,0,	},
	{	TDX_ID_TSXX4,				TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"提示信息4",			0,0,0,0,0,	},
	{	TDX_ID_TSXX5,				TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"提示信息5",			0,0,0,0,0,	},
	{	TDX_ID_TSXX6,				TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"提示信息6",			0,0,0,0,0,	},
	{	TDX_ID_TSXX7,				TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"提示信息7",			0,0,0,0,0,	},
	{	TDX_ID_TSXX8,				TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"提示信息8",			0,0,0,0,0,	},
	{	TDX_ID_TSXX9,				TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"提示信息9",			0,0,0,0,0,	},

	{	TDX_ID_ZJLS_FSRQ,			TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"发生日期",				0,0,0,0,0,	},
	{	TDX_ID_ZJLS_FSSJ,			TDX_DT_TIME,	TDX_DISP_RIGHT,   8,	"发生时间",				0,0,0,0,0,	},
	{	TDX_ID_ZJLS_YWDM,			TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"业务代码",				0,0,0,0,0,	},
	{	TDX_ID_ZJLS_YWMC,			TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"业务名称",				0,0,0,0,0,	},
	{	TDX_ID_ZJLS_HBDM,			TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"货币代码",				0,0,0,0,0,	},
	{	TDX_ID_ZJLS_FSJE,			TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"发生金额",				0,0,0,0,0,	},
	{	TDX_ID_ZJLS_SYJE,			TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"剩余金额",				0,0,0,0,0,	},
	{	TDX_ID_ZJLS_ZQDM,			TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"证券代码",				0,0,0,0,0,	},
	{	TDX_ID_ZJLS_ZQMC,			TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"证券名称",				0,0,0,0,0,	},
	{	TDX_ID_ZJLS_FSJG,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"发生价格",				0,0,0,0,0,	},
	{	TDX_ID_ZJLS_FSSL,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"发生数量",				0,0,0,0,0,	},
	{	TDX_ID_ZJLS_SYSL,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"剩余数量",				0,0,0,0,0,	},
	{	TDX_ID_ZJLS_GDDM,			TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"股东代码",				0,0,0,0,0,	},

	{	TDX_ID_DFBZ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"对方币种",				0,0,0,0,0,	},
	{	TDX_ID_DQHL,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"当前汇率",				0,0,0,0,0,	},
	{	TDX_ID_JYGF,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"交易规费",				0,0,0,0,0,	},
	{	TDX_ID_ZTZJ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"在途资金",				0,0,0,0,0,	},
	{	TDX_ID_OTCJYBS,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"OTC交易标志",			1,0,0,0,0,	},
	{	TDX_ID_XYJYBS,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"融资融券标识",			1,0,0,0,0,	},
	{	TDX_ID_SFCGBS,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"三方存管标识",			1,0,0,0,0,	},
	{	TDX_ID_ZZFS,				TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"转帐方式",				0,0,0,0,0,	},
	{	TDX_ID_ZZQD,				TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"转帐渠道",				0,0,0,0,0,	},
	{	TDX_ID_ZZBH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"转帐编号",				0,0,0,0,0,	},
	{	TDX_ID_FPYH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"发票银行",				0,0,0,0,0,	},
	{	TDX_ID_ZPBH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"支票编号",				0,0,0,0,0,	},
	{	TDX_ID_ZJCJSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"最近成交数量",			0,0,0,0,0,	},
	{	TDX_ID_ZJCDSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"最近撤单数量",			0,0,0,0,0,	},
	{	TDX_ID_KHBS,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"客户标识",				0,0,0,0,0,	},
	{	TDX_ID_ZDDM,				TDX_DT_SHORT,	TDX_DISP_RIGHT,   4,	"字段代码",				0,0,0,0,0,	},
	{	TDX_ID_ZDQZ,				TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"字段取值",				0,0,0,0,0,	},
	{	TDX_ID_YLXX,				TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"预留信息",				0,0,0,0,0,	},
	{	TDX_ID_FJZH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"附加账号",				0,0,0,0,0,	},
	{	TDX_ID_XYJYTSXX,			TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"信用交易提示信息",		0,0,0,0,0,	},
	{	TDX_ID_JZC,					TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"净资产",				0,0,0,0,0,	},
	{	TDX_ID_SGKYS,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"申购可用数",			0,0,0,0,0,	},
	{	TDX_ID_DFKHDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"对方客户代码",			0,0,0,0,0,	},
	{	TDX_ID_DFFZDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"对方分支代码",			0,0,0,0,0,	},

	{	TDX_ID_ZJYE,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"资金余额",				0,0,0,0,0,	},
	{	TDX_ID_KYZJ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"可用资金",				0,0,0,0,0,	},
	{	TDX_ID_KQZJ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"可取资金",				0,0,0,0,0,	},
	{	TDX_ID_OCCURJE,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"发生金额",				0,0,0,0,0,	},
	{	TDX_ID_POSTJE,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"剩余金额",				0,0,0,0,0,	},
	{	TDX_ID_ZY,					TDX_DT_STRING,	TDX_DISP_RIGHT,  40,	"摘要",					0,0,0,0,0,	},
	{	TDX_ID_YWMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"业务名称",				0,0,0,0,0,	},
	{	TDX_ID_YWDM,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"业务代码",				1,0,0,0,0,	},
	{	TDX_ID_MRDJZJ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"买入冻结资金",			0,0,0,0,0,	},
	{	TDX_ID_YZT_YHXZTS,			TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"提示选择银行标志",		1,0,0,0,0,	},
	{	TDX_ID_GTZZC,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"总资产",				0,0,0,0,0,	},
	{	TDX_ID_CJLX,				TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"成交类型",				0,0,0,0,0,	},
	{	TDX_ID_JYDJZJ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"交易冻结",				0,0,0,0,0,	},
	{	TDX_ID_YCDJZJ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"异常冻结",				0,0,0,0,0,	},
	{	TDX_ID_ZTKYZJ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"在途可用",				0,0,0,0,0,	},
	{	TDX_ID_XJKQZJ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"可取现金",				0,0,0,0,0,	},
	{	TDX_ID_ZPKQZJ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"可取支票",				0,0,0,0,0,	},
	{	TDX_ID_KZZJ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"可转资金",				0,0,0,0,0,	},
	{	TDX_ID_LXJE,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"利息",					0,0,0,0,0,	},
	{	TDX_ID_LXS,					TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"利息税",				0,0,0,0,0,	},
	{	TDX_ID_SYSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"剩余数量",				0,0,0,0,0,	},
	{	TDX_ID_FJF,					TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"附加费",				0,0,0,0,0,	},
	{	TDX_ID_SXJE,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"所需金额",				0,0,0,0,0,	},
	{	TDX_ID_MMCB,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"买卖成本",				0,0,0,0,0,	},
	{	TDX_ID_MRCB,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"买入成本",				0,0,0,0,0,	},
	{	TDX_ID_ZGF,					TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"证管费",				0,0,0,0,0,	},
	{	TDX_ID_FCJL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"分仓基量",				0,0,0,0,0,	},
	{	TDX_ID_ZYK,					TDX_DT_FLOAT,	TDX_DISP_RIGHT,   6,	"总盈亏",				0,0,0,0,0,	},
	{	TDX_ID_TBCBJ,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   6,	"摊薄成本价",			0,0,0,0,0,	},
	{	TDX_ID_TBBBJ,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   6,	"摊薄保本价",			0,0,0,0,0,	},
	{	TDX_ID_TBFDYK,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   6,	"摊薄浮动盈亏",			0,0,0,0,0,	},
	{	TDX_ID_FADM,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"方案代码",				0,0,0,0,0,	},
	{	TDX_ID_FAMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"方案名称",				0,0,0,0,0,	},
	{	TDX_ID_FALX,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"方案类型",				0,0,0,0,0,	},
	{	TDX_ID_TPDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"投票代码",				0,0,0,0,0,	},
	{	TDX_ID_TPJG,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"投票结果",				0,0,0,0,0,	},
	{	TDX_ID_CFDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"成分代码",				0,0,0,0,0,	},
	{	TDX_ID_CFMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"成分名称",				0,0,0,0,0,	},
	{	TDX_ID_CFQZ,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"成分权重(%)",			0,0,0,0,0,	},
	{	TDX_ID_MRXX,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"默认选项",				0,0,0,0,0,	},
	{	TDX_ID_XXNR0,				TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"选项内容0",			0,0,0,0,0,	},
	{	TDX_ID_XXNR1,				TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"选项内容1",			0,0,0,0,0,	},
	{	TDX_ID_XXNR2,				TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"选项内容2",			0,0,0,0,0,	},
	{	TDX_ID_XXNR3,				TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"选项内容3",			0,0,0,0,0,	},
	{	TDX_ID_XXNR4,				TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"选项内容4",			0,0,0,0,0,	},
	{	TDX_ID_XXNR5,				TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"选项内容5",			0,0,0,0,0,	},
	{	TDX_ID_XXNR6,				TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"选项内容6",			0,0,0,0,0,	},
	{	TDX_ID_XXNR7,				TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"选项内容7",			0,0,0,0,0,	},
	{	TDX_ID_XXNR8,				TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"选项内容8",			0,0,0,0,0,	},
	{	TDX_ID_XXNR9,				TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"选项内容9",			0,0,0,0,0,	},
	{	TDX_ID_ZZC,					TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"总资产",				0,0,0,0,0,	},
	{	TDX_ID_SYL,					TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"收益率",				0,0,0,0,0,	},
	{	TDX_ID_HYZS,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"活跃指数",				0,0,0,0,0,	},
	{	TDX_ID_RMBZZC,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"人民币总资产",			0,0,0,0,0,	},
	{	TDX_ID_MYZZC,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"美元总资产",			0,0,0,0,0,	},
	{	TDX_ID_GYZZC,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"港元总资产",			0,0,0,0,0,	},
	{	TDX_ID_SYLTJRQ,				TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"收益率统计日期",		0,0,0,0,0,	},
	{	TDX_ID_SYLTJSJ,				TDX_DT_TIME,	TDX_DISP_RIGHT,   8,	"收益率统计时间",		0,0,0,0,0,	},
	{	TDX_ID_ZZHZYE,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"子账号总余额",			0,0,0,0,0,	},
	{	TDX_ID_HGJE,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"回购金额",				0,0,0,0,0,	},
	{	TDX_ID_MOCK_ZHTYPE,			TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"账号类型",				0,0,0,0,0,	},

	{	TDX_ID_RQSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"融券数量",				0,0,0,0,0,	},
	{	TDX_ID_RQJG,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"融券价格",				0,0,0,0,0,	},
	{	TDX_ID_RQZQ,				TDX_DT_SHORT,	TDX_DISP_RIGHT,   4,	"融券周期",				0,0,0,0,0,	},
	{	TDX_ID_RQCZLX,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"融券操作类型",			0,0,0,0,0,	},
	{	TDX_ID_RQRQ,				TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"融券日期",				0,0,0,0,0,	},
	{	TDX_ID_RQSJ,				TDX_DT_TIME,	TDX_DISP_RIGHT,   8,	"融券时间",				0,0,0,0,0,	},
	{	TDX_ID_HTBH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"合同编号",				0,0,0,0,0,	},
	{	TDX_ID_JDJSJET,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"净待交收金额(T日)",	0,0,0,0,0,	},
	{	TDX_ID_JDJSJET1,			TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"净待交收金额(T+1日)",	0,0,0,0,0,	},
	{	TDX_ID_JDJSJET2,			TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"净待交收金额(T+2日)",	0,0,0,0,0,	},
	{	TDX_ID_ZPDJSJE,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"支票待交收金额",		0,0,0,0,0,	},
	{	TDX_ID_XYSZ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"信用市值",				0,0,0,0,0,	},
	{	TDX_ID_GJBZQGML,			TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"高级别证券购买力",		0,0,0,0,0,	},
	{	TDX_ID_XYGJBZQGML,			TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"信用高级别证券购买力",	0,0,0,0,0,	},
	{	TDX_ID_DJBZQGML,			TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"低级别证券购买力",		0,0,0,0,0,	},
	{	TDX_ID_XYDJBZQGML,			TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"信用低级别证券购买力",	0,0,0,0,0,	},
	{	TDX_ID_YXSBCS,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"有效失败次数",			0,0,0,0,0,	},
	{	TDX_ID_SFFSSM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"收费方式",				0,0,0,0,0,	},
	{	TDX_ID_CPJZ,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"产品净值",				0,0,0,0,0,	},
	{	TDX_ID_LCZH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"理财账户",				0,0,0,0,0,	},
	{	TDX_ID_CPDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"产品代码",				0,0,0,0,0,	},
	{	TDX_ID_CPMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"产品名称",				0,0,0,0,0,	},
	{	TDX_ID_CPGSDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"产品公司代码",			0,0,0,0,0,	},
	{	TDX_ID_CPGSMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"产品公司名称",			0,0,0,0,0,	},
	{	TDX_ID_CPZT,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"产品状态",				1,0,0,0,0,	},
	{	TDX_ID_QRJZ,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"前日净值",				0,0,0,0,0,	},
	{	TDX_ID_CPBZ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"产品标志",				1,0,0,0,0,	},	
	{	TDX_ID_KTBZ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"开通标志",				1,0,0,0,0,	},
	{	TDX_ID_KFSJJ_LJJZ,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"累计净值",				0,0,0,0,0,	},

	{	TDX_ID_KFSJJ_MMBZ,			TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"交易标志",				1,0,0,0,0,	},
	{	TDX_ID_KFSJJ_JJGSMC,		TDX_DT_STRING,	TDX_DISP_RIGHT,   1,	"基金公司名称",			0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_JJDM,			TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"基金代码",				0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_JJMC,			TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"基金名称",				0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_JJFE,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"基金份额",				0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_JYJE,			TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"交易金额",				0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_JJJZ,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"基金净值",				0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_ZHDM,			TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"基金转换代码",			0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_DIVIDENMETHOD,	TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"基金分红方式",			0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_FSRQ,			TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"发生日期",				0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_KYFE,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"可用份额",				0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_JJBS,			TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"开放式基金标识",		1,0,0,0,0,	},
	{	TDX_ID_KFSJJ_QSSL,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"起始数量",				0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_DQSL,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"当前数量",				0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_WTFE,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"委托份额",				0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_CJFE,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"成交份额",				0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_CJJE,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"成交金额",				0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_JJZH,			TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"基金帐户",				0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_FXJG,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"发行价格",				0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_GRZDRGJE,		TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"个人最低认购金额",		0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_FRZDRGJE,		TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"法人最低认购金额",		0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_ZDCYFE,		TDX_DT_LONG,	TDX_DISP_RIGHT,  12,	"最低持有份额",			0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_ZGSHFE,		TDX_DT_LONG,	TDX_DISP_RIGHT,  12,	"最高赎回份额",			0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_GRZGCYBL,		TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"个人最高持有比例",		0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_FRZGCYBL,		TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"法人最高持有比例",		0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_JJZT,			TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"基金状态",				1,0,0,0,0,	},
	{	TDX_ID_KFSJJ_JJGSDM,		TDX_DT_SHORT,	TDX_DISP_RIGHT,   4,	"基金公司代码",			0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_FXZS,			TDX_DT_LONG,	TDX_DISP_RIGHT,  12,	"发行总数",				0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_ZDSHFE,		TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"最低赎回份额",			0,0,0,0,0,	},
	{	TDX_ID_SFFS,				TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"收费方式",				1,0,0,0,0,	},
	{	TDX_ID_KFSJJ_JGZGBL,		TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"机构最高比例",			0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_GRZGBL,		TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"个人最高比例",			0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_GRZGRGZJ,		TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"个人最高认购金额",		0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_FRZGRGZJ,		TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"法人最高认购金额",		0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_GRSCSGZDZJ,	TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"个人首次申购最低资金",	0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_FRSCSGZDZJ,	TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"法人首次申购最低资金",	0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_GRZJSGZDZJ,	TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"个人追加申购最低资金",	0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_FRZJSGZDZJ,	TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"法人追加申购最低资金",	0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_GRJJZSSHFE,	TDX_DT_LONG,	TDX_DISP_RIGHT,  12,	"个人基金最少赎回份额",	0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_FRJJZSSHFE,	TDX_DT_LONG,	TDX_DISP_RIGHT,  12,	"法人基金最少赎回份额",	0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_GRJJZSZHFE,	TDX_DT_LONG,	TDX_DISP_RIGHT,  12,	"个人基金最少转换份额",	0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_FRJJZSZHFE,	TDX_DT_LONG,	TDX_DISP_RIGHT,  12,	"法人基金最少转换份额",	0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_TADM,			TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"TA 代码",				0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_GTGSBZ,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"基金柜台公司标志",		1,0,0,0,0,	},
	{	TDX_ID_KFSJJ_FHFSDM,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"分红方式代码",			1,0,0,0,0,	},
	{	TDX_ID_KFSJJ_FHFSMC,		TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"分红方式名称",			0,0,0,0,0,	},
	{	TDX_ID_LSDJ,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"临时冻结",				0,0,0,0,0,	},
	{	TDX_ID_MCWTSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"卖出冻结",				0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_PZDM,			TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"品种代码",				0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_MYKKRQ,		TDX_DT_SHORT,	TDX_DISP_RIGHT,   2,	"每月扣款日期",			0,0,0,0,0,	},
	{	TDX_ID_KHTYPE,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"开户类别",				0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_DQSGNS,		TDX_DT_SHORT,	TDX_DISP_RIGHT,   4,	"申购年数",				0,0,0,0,0,	},
	{	TDX_ID_ZJLB,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"证件类别",				0,0,0,0,0,	},
	{	TDX_ID_JYZH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"交易帐户",				0,0,0,0,0,	},
	{	TDX_ID_ZJHM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"证件号码",				0,0,0,0,0,	},
	{	TDX_ID_MOBILEPHONE,			TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"移动电话",				0,0,0,0,0,	},
	{	TDX_ID_HOMEPHONE,			TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"住宅电话",				0,0,0,0,0,	},
	{	TDX_ID_FAX,					TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"传真",					0,0,0,0,0,	},
	{	TDX_ID_EDU,					TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"教育程度",				0,0,0,0,0,	},
	{	TDX_ID_SALARY,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"年收入",				0,0,0,0,0,	},
	{	TDX_ID_XLYZT_DLSGFLAG,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"代理申购标志",			0,0,0,0,0,	},
	{	TDX_ID_XLYZT_DLPGFLAG,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"代理配股标志",			0,0,0,0,0,	},
	{	TDX_ID_XLYZT_DLPSFLAG,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"代理配售标志",			0,0,0,0,0,	},
	{	TDX_ID_WORKPHONE,			TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"单位电话",				0,0,0,0,0,	},
	{	TDX_ID_NAME,				TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"姓名",					0,0,0,0,0,	},
	{	TDX_ID_VOCATION,			TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"职业",					0,0,0,0,0,	},
	{	TDX_ID_FHBZ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"分红标志",				0,0,0,0,0,	},
	{	TDX_ID_DZDBZ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"对帐单标志",			0,0,0,0,0,	},
	{	TDX_ID_SHFS,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"赎回方式",				0,0,0,0,0,	},
	{	TDX_ID_FHBL,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"分红比例",				0,0,0,0,0,	},
	{	TDX_ID_FHRQ,				TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"分红日期",				0,0,0,0,0,	},
	{	TDX_ID_FHJE,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"分红金额",				0,0,0,0,0,	},
	{	TDX_ID_FHSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"分红数量",				0,0,0,0,0,	},
	{	TDX_ID_MGFHJE,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"每股分红金额",			0,0,0,0,0,	},
	{	TDX_ID_ZDBZ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"指定标志",				0,0,0,0,0,	},
	{	TDX_ID_FHFS,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"分红方式",				0,0,0,0,0,	},
	{	TDX_ID_KHRQ,				TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"开户日期",				0,0,0,0,0,	},
	{	TDX_ID_KHQC,				TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"客户全称",				0,0,0,0,0,	},
	{	TDX_ID_BPCALL,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"寻呼机号",				0,0,0,0,0,	},
	{	TDX_ID_ZBDLJYXX,			TDX_DT_STRING,	TDX_DISP_RIGHT,1024,	"周边登录校验信息",		0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_JGZDTZ,		TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"机构最低投资",			0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_GRZDTZ,		TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"个人最低投资",			0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_JGZDZJ,		TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"机构最低追加",			0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_GRZDZJ,		TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"个人最低追加",			0,0,0,0,0,	},
	{	TDX_ID_SPEL_GX_HZXGSGZT,	TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"合作新股申购",			0,0,0,0,0,	},
	{	TDX_ID_TJRDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"推荐人代码",			0,0,0,0,0,	},
	{	TDX_ID_PROVINCE,			TDX_DT_STRING,	TDX_DISP_RIGHT,  10,	"省份",					0,0,0,0,0,	},
	{	TDX_ID_CITY,				TDX_DT_STRING,	TDX_DISP_RIGHT,  20,	"城市",					0,0,0,0,0,	},
	{	TDX_ID_SECTION,				TDX_DT_STRING,	TDX_DISP_RIGHT,  20,	"辖区",					0,0,0,0,0,	},
	{	TDX_ID_IDADDRESS,			TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"证件地址",				0,0,0,0,0,	},
	{	TDX_ID_FRDBXM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"法人代表姓名",			0,0,0,0,0,	},
	{	TDX_ID_FRDBZJLX,			TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"法人代表证件类型",		0,0,0,0,0,	},
	{	TDX_ID_FRDBZJHM,			TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"法人代表证件号码",		0,0,0,0,0,	},
	{	TDX_ID_LXRZJLX,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"联系人证件类型",		0,0,0,0,0,	},
	{	TDX_ID_LXRZJHM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"联系人证件号码",		0,0,0,0,0,	},
	{	TDX_ID_LXRDH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"联系人电话",			0,0,0,0,0,	},
	{	TDX_ID_DZDJSFS,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"对帐单寄送方式",		0,0,0,0,0,	},
	{	TDX_ID_JJDTBZ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"基金定投标志",			0,0,0,0,0,	},
	{	TDX_ID_XSRDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"销售人代码",			0,0,0,0,0,	},
	{	TDX_ID_XSRMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"销售人名称",			0,0,0,0,0,	},

	{	TDX_ID_QHZHBS,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"期货账号标识",			0,0,0,0,0,	},
	{	TDX_ID_QHZH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"期货账号",				0,0,0,0,0,	},
	{	TDX_ID_HYDM1,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32 ,	"合约代码1",			0,0,0,0,0,	},
	{	TDX_ID_HYDM2,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32 ,	"合约代码2",			0,0,0,0,0,	},
	{	TDX_ID_HYDM3,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32 ,	"合约代码3",			0,0,0,0,0,	},
	{	TDX_ID_HYDM4,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32 ,	"合约代码4",			0,0,0,0,0,	},
	{	TDX_ID_HYMC1,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32 ,	"合约名称1",			0,0,0,0,0,	},
	{	TDX_ID_HYMC2,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32 ,	"合约名称2",			0,0,0,0,0,	},
	{	TDX_ID_HYMC3,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32 ,	"合约名称3",			0,0,0,0,0,	},
	{	TDX_ID_HYMC4,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32 ,	"合约名称4",			0,0,0,0,0,	},
	{	TDX_ID_HYDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"合约代码",				0,0,0,0,0,	},
	{	TDX_ID_HYMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"合约名称",				0,0,0,0,0,	},
	{	TDX_ID_PZ,					TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"品种",					0,0,0,0,0,	},
	{	TDX_ID_KPBZ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"开平标志",				1,0,0,0,0,	},
	{	TDX_ID_TBBZ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"投保标志",				1,0,0,0,0,	},
	{	TDX_ID_JKCFLAG,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"今仓标志",				0,0,0,0,0,	},
	{	TDX_ID_CJSX,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"成交属性",				1,0,0,0,0,	},
	{	TDX_ID_CJSXSM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"成交属性说明",			0,0,0,0,0,	},
	{	TDX_ID_ZHLX,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"组合类型",				0,0,0,0,0,	},
	{	TDX_ID_ZHLXSM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"组合类型说明",			0,0,0,0,0,	},
	{	TDX_ID_KCJG,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"开仓价",				0,0,0,0,0,	},
	{	TDX_ID_CCSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"持仓量",				0,0,0,0,0,	},
	{	TDX_ID_KCRQ,				TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"开仓日期",				0,0,0,0,0,	},
	{	TDX_ID_CJJJ,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"成交均价",				0,0,0,0,0,	},
	{	TDX_ID_CBJJ,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"成本均价",				0,0,0,0,0,	},
	{	TDX_ID_BZJJE,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"保证金",				0,0,0,0,0,	},
	{	TDX_ID_SXFJE,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"手续费",				0,0,0,0,0,	},
	{	TDX_ID_MRJJ,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"买均价",				0,0,0,0,0,	},
	{	TDX_ID_CCJJ,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"持仓均价",				0,0,0,0,0,	},
	{	TDX_ID_ZHTS,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"组合腿数",				0,0,0,0,0,	},
	{	TDX_ID_DJBZJ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"冻结保证金",			0,0,0,0,0,	},
	{	TDX_ID_QCZJ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"期初资金",				0,0,0,0,0,	},
	{	TDX_ID_KHQYZJ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"客户权益资金",			0,0,0,0,0,	},
	{	TDX_ID_KKCSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"可开仓数量",			0,0,0,0,0,	},
	{	TDX_ID_KPCSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"可平仓数量",			0,0,0,0,0,	},
	{	TDX_ID_KPJSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"可平今数量",			0,0,0,0,0,	},
	{	TDX_ID_ZHHYDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"组合合约代码",			0,0,0,0,0,	},
	{	TDX_ID_ZHHYMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"组合合约名称",			0,0,0,0,0,	},
	{	TDX_ID_CFJG,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"触发价格",				0,0,0,0,0,	},
	{	TDX_ID_MZL,					TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"命中率",				0,0,0,0,0,	},
	{	TDX_ID_JGY,					TDX_DT_SHORT,	TDX_DISP_RIGHT,   4,	"交割月份",				0,0,0,0,0,	},
	{	TDX_ID_BZJ,					TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"保证金",				0,0,0,0,0,	},
	{	TDX_ID_QHJYDW,				TDX_DT_SHORT,	TDX_DISP_RIGHT,   4,	"交易单位",				0,0,0,0,0,	},
	{	TDX_ID_QHBJDW,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"报价单位",				0,0,0,0,0,	},
	{	TDX_ID_ZXBDJW,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"最小变动价位",			0,0,0,0,0,	},
	{	TDX_ID_JGBDFD,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"价格波动幅度",			0,0,0,0,0,	},
	{	TDX_ID_BZJBL,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"保证金比例",			0,0,0,0,0,	},

	{	TDX_ID_QHHQ_KCL,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"开仓量",				0,0,0,0,0,	},
	{	TDX_ID_QHHQ_CCL,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"持仓量",				0,0,0,0,0,	},
	{	TDX_ID_QHHQ_QJS,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"前结算",				0,0,0,0,0,	},
	{	TDX_ID_QHHQ_ZS,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"总手",					0,0,0,0,0,	},

	{	TDX_ID_GGZHBS,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"港股账号标识",			1,0,0,0,0,	},

	{	TDX_ID_ETFBS,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"ETF标识",				0,0,0,0,0,	},
	{	TDX_ID_ETFDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"ETF代码",				0,0,0,0,0,	},
	{	TDX_ID_ETFMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"ETF名称",				0,0,0,0,0,	},
	{	TDX_ID_ETFMMBS,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"交易类型",				0,0,0,0,0,	},
	{	TDX_ID_ETFRGSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"认购数量",				0,0,0,0,0,	},
	{	TDX_ID_ETFRGJE,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"认购金额",				0,0,0,0,0,	},
	{	TDX_ID_PCH,					TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"批次号",				0,0,0,0,0,	},
	{	TDX_ID_ETFXJTDMZ,			TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"替代标志",				0,0,0,0,0,	},
	{	TDX_ID_ETFYJBL,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"溢价比例",				0,0,0,0,0,	},
	{	TDX_ID_ETFXJTDJE,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"现金替代金额",			0,0,0,0,0,	},
	{	TDX_ID_QSRQ,				TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"清算周期",				0,0,0,0,0,	},
	{	TDX_ID_CLDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"策略代码",				0,0,0,0,0,	},
	{	TDX_ID_CLMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"策略名称",				0,0,0,0,0,	},
	{	TDX_ID_ZSDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"指数代码",				0,0,0,0,0,	},
	{	TDX_ID_ZSMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"指数名称",				0,0,0,0,0,	},
	{	TDX_ID_CDDDSJ,				TDX_DT_SHORT,	TDX_DISP_RIGHT,   4,	"撤单等待时间",			0,0,0,0,0,	},
	{	TDX_ID_WTDDSJ,				TDX_DT_SHORT,	TDX_DISP_RIGHT,   4,	"委托等待时间",			0,0,0,0,0,	},
	{	TDX_ID_WTCS,				TDX_DT_SHORT,	TDX_DISP_RIGHT,   4,	"委托次数",				0,0,0,0,0,	},
	{	TDX_ID_JGBZ,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"价格标志",				0,0,0,0,0,	},
	{	TDX_ID_ZDCD,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"自动撤单",				0,0,0,0,0,	},
	{	TDX_ID_CFSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"成分数量",				0,0,0,0,0,	},
	{	TDX_ID_KCSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"库存数量",				0,0,0,0,0,	},
	{	TDX_ID_BLSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"保留数量",				0,0,0,0,0,	},
	{	TDX_ID_XJBZ,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"现金标志",				0,0,0,0,0,	},
	{	TDX_ID_JSBZ,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"结束标志",				0,0,0,0,0,	},
	{	TDX_ID_CJZT,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"成交状态",				0,0,0,0,0,	},
	{	TDX_ID_XJTDSM,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"现金替代",				0,0,0,0,0,	},
	{	TDX_ID_QKSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"缺口数量",				0,0,0,0,0,	},
	{	TDX_ID_XYZJ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"需要资金",				0,0,0,0,0,	},
	{	TDX_ID_ZRKC,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"昨日库存",				0,0,0,0,0,	},
	{	TDX_ID_JRMRJE,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"今买金额",				0,0,0,0,0,	},
	{	TDX_ID_JRMCSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"今卖数量",				0,0,0,0,0,	},
	{	TDX_ID_JRMCJE,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"今卖金额",				0,0,0,0,0,	},
	{	TDX_ID_MBFE,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"目标份额",				0,0,0,0,0,	},
	{	TDX_ID_KSSJ,				TDX_DT_TIME,	TDX_DISP_RIGHT,   8,	"开始时间",				0,0,0,0,0,	},
	{	TDX_ID_ZZSJ,				TDX_DT_TIME,	TDX_DISP_RIGHT,   8,	"终止时间",				0,0,0,0,0,	},
	{	TDX_ID_CSWTSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"初始委托数量",			0,0,0,0,0,	},
	{	TDX_ID_ZWTCS,				TDX_DT_SHORT,	TDX_DISP_RIGHT,   4,	"总委托次数",			0,0,0,0,0,	},
	{	TDX_ID_ZHDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"组合代码",				0,0,0,0,0,	},
	{	TDX_ID_ZHMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"组合名称",				0,0,0,0,0,	},
	{	TDX_ID_KZYHZHBM,			TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"扩展银行账户编码",		0,0,0,0,0,	},
	{	TDX_ID_KZYHZHBM1,			TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"扩展银行账户编码1",	0,0,0,0,0,	},
	{	TDX_ID_KZYHZHBM2,			TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"扩展银行账户编码2",	0,0,0,0,0,	},
	{	TDX_ID_KZYHZHBM3,			TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"扩展银行账户编码3",	0,0,0,0,0,	},
	{	TDX_ID_KZYHZHBM4,			TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"扩展银行账户编码4",	0,0,0,0,0,	},
	{	TDX_ID_KZYHZHMC,			TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"扩展银行账户名称",		0,0,0,0,0,	},
	{	TDX_ID_KZYHZHMC1,			TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"扩展银行账户名称1",	0,0,0,0,0,	},
	{	TDX_ID_KZYHZHMC2,			TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"扩展银行账户名称2",	0,0,0,0,0,	},
	{	TDX_ID_KZYHZHMC3,			TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"扩展银行账户名称3",	0,0,0,0,0,	},
	{	TDX_ID_KZYHZHMC4,			TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"扩展银行账户名称4",	0,0,0,0,0,	},
	{	TDX_ID_DJGSDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"登记公司代码",			0,0,0,0,0,	},
	{	TDX_ID_DJGSJC,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"登记公司简称",			0,0,0,0,0,	},
	{	TDX_ID_DJGSQC,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"登记公司全称",			0,0,0,0,0,	},
	{	TDX_ID_QZFS,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"权重方式",				1,0,0,0,0,	},
	{	TDX_ID_DWSZ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"单位市值",				0,0,0,0,0,	},
	{	TDX_ID_XHZH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"现货账号",				0,0,0,0,0,	},
	{	TDX_ID_XHZHLX,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"现货账号类型",			1,0,0,0,0,	},
	{	TDX_ID_PCHLX,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"批次号类型",			1,0,0,0,0,	},
	{	TDX_ID_DKBZ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"多空标志",				1,0,0,0,0,	},
	{	TDX_ID_TZSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"投资数量",				0,0,0,0,0,	},
	{	TDX_ID_BJFS,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"报价方式",				1,0,0,0,0,	},
	{	TDX_ID_DFBJFS,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"对方报价方式",			1,0,0,0,0,	},
	{	TDX_ID_SYKCBJ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"使用库存标记",			1,0,0,0,0,	},
	{	TDX_ID_SYFZXHBJ,			TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"使用辅助现货标记",		1,0,0,0,0,	},
	{	TDX_ID_MCYGBJ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"卖出余股标记",			1,0,0,0,0,	},
	{	TDX_ID_ZDWTBJ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"自动委托标记",			1,0,0,0,0,	},
	{	TDX_ID_ZDWTCS,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"自动委托次数",			0,0,0,0,0,	},
	{	TDX_ID_PCHRQ,				TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"批次号日期",			0,0,0,0,0,	},
	{	TDX_ID_JC,					TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"基差",					0,0,0,0,0,	},
	{	TDX_ID_MRJEJSJZ,			TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"买入金额计算基准",		1,0,0,0,0,	},
	{	TDX_ID_MRJE,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"买入金额",				1,0,0,0,0,	},
	{	TDX_ID_FZXHDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"辅助现货代码",			0,0,0,0,0,	},
	{	TDX_ID_FZXHMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"辅助现货名称",			0,0,0,0,0,	},
	{	TDX_ID_PDDM1,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"配对代码1",			0,0,0,0,0,	},
	{	TDX_ID_PDMC1,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"配对名称1",			0,0,0,0,0,	},
	{	TDX_ID_PDDM2,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"配对代码2",			0,0,0,0,0,	},
	{	TDX_ID_PDMC2,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"配对名称2",			0,0,0,0,0,	},
	{	TDX_ID_PDBL,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"配对比例",				0,0,0,0,0,	},
	{	TDX_ID_JCRQ,				TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"建仓日期",				0,0,0,0,0,	},
	{	TDX_ID_JCJG1,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"建仓价格1",			0,0,0,0,0,	},
	{	TDX_ID_JCSL1,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"建仓数量1",			0,0,0,0,0,	},
	{	TDX_ID_JCBH1,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"建仓编号1",			0,0,0,0,0,	},
	{	TDX_ID_JCJG2,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"建仓价格2",			0,0,0,0,0,	},
	{	TDX_ID_JCSL2,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"建仓数量2",			0,0,0,0,0,	},
	{	TDX_ID_JCBH2,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"建仓编号2",			0,0,0,0,0,	},

	{	TDX_ID_FXD,					TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"风险度",				0,0,0,0,0,	},
	{	TDX_ID_KHAQLB,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"客户安全类别",			0,0,0,0,0,	},
	{	TDX_ID_KHAQLBSM,			TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"客户安全类别说明",		0,0,0,0,0,	},
	{	TDX_ID_ZJBZJ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"追加保证金",			0,0,0,0,0,	},
	{	TDX_ID_ZRJSJ,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"昨日结算价",			0,0,0,0,0,	},
	{	TDX_ID_SBMRJ,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"买入价",				0,0,0,0,0,	},
	{	TDX_ID_SBMCJ,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"卖出价",				0,0,0,0,0,	},
	{	TDX_ID_SBMRL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"买入量",				0,0,0,0,0,	},
	{	TDX_ID_SBMCL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"卖出量",				0,0,0,0,0,	},
	{	TDX_ID_MCDJZJ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"卖出冻结资金",			0,0,0,0,0,	},
	{	TDX_ID_MRBZJ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"买入保证金",			0,0,0,0,0,	},
	{	TDX_ID_MCBZJ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"卖出保证金",			0,0,0,0,0,	},
	{	TDX_ID_YLJE,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"盈利金额",				0,0,0,0,0,	},
	{	TDX_ID_KSJE,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"亏损金额",				0,0,0,0,0,	},
	{	TDX_ID_DTQY,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"动态权益",				0,0,0,0,0,	},
	{	TDX_ID_DTFX,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"动态风险",				0,0,0,0,0,	},
	{	TDX_ID_PCYK,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"平仓盈亏",				0,0,0,0,0,	},
	{	TDX_ID_DRCRJ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"当日出入金",			0,0,0,0,0,	},
	{	TDX_ID_XTZXH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"系统中心号",			0,0,0,0,0,	},
	{	TDX_ID_KPBZSM,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"开平标志",				0,0,0,0,0,	},
	{	TDX_ID_TBBZSM,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"投保标志",				0,0,0,0,0,	},
	{	TDX_ID_MRCC,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"买持仓",				0,0,0,0,0,	},
	{	TDX_ID_MRFDYK,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"买盈亏",				0,0,0,0,0,	},
	{	TDX_ID_MCCC,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"卖持仓",				0,0,0,0,0,	},
	{	TDX_ID_MCJJ,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"卖均价",				0,0,0,0,0,	},
	{	TDX_ID_MCFDYK,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"卖盈亏",				0,0,0,0,0,	},
	{	TDX_ID_LSH,					TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"流水号",				0,0,0,0,0,	},
	{	TDX_ID_JF,					TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"出金",					0,0,0,0,0,	},
	{	TDX_ID_DF,					TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"入金",					0,0,0,0,0,	},
	{	TDX_ID_QHTJ,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"投机",					0,0,0,0,0,	},
	{	TDX_ID_QHBZ,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"保值",					0,0,0,0,0,	},
	{	TDX_ID_ZDSS,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"最大手数",				0,0,0,0,0,	},
	{	TDX_ID_ZDCC,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"最大持仓",				0,0,0,0,0,	},
	{	TDX_ID_WCJSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"未成交数量",			0,0,0,0,0,	},
	{	TDX_ID_SBSJ,				TDX_DT_TIME,	TDX_DISP_RIGHT,   8,	"申报时间",				0,0,0,0,0,	},
	{	TDX_ID_CDSJ,				TDX_DT_TIME,	TDX_DISP_RIGHT,   8,	"撤单时间",				0,0,0,0,0,	},
	{	TDX_ID_FSZ,					TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"发送者",				0,0,0,0,0,	},
	{	TDX_ID_XXLX,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"信息类型",				0,0,0,0,0,	},
	{	TDX_ID_XXLXSM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"信息类型",				0,0,0,0,0,	},
	{	TDX_ID_ZYZJ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"质押资金",				0,0,0,0,0,	},
	{	TDX_ID_ZJFXL,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"资金风险率",			0,0,0,0,0,	},
	{	TDX_ID_JYSFXL,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"交易所风险率",			0,0,0,0,0,	},
	{	TDX_ID_QCQY,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"期初权益",				0,0,0,0,0,	},
	{	TDX_ID_DPPCYK,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"盯盘平仓盈亏",			0,0,0,0,0,	},
	{	TDX_ID_FDPCYK,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"浮动平仓盈亏",			0,0,0,0,0,	},
	{	TDX_ID_DPCCYK,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"盯盘持仓盈亏",			0,0,0,0,0,	},
	{	TDX_ID_FDCCYK,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"浮动持仓盈亏",			0,0,0,0,0,	},
	{	TDX_ID_DPZYK,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"盯盘总盈亏",			0,0,0,0,0,	},
	{	TDX_ID_FDZYK,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"浮动总盈亏",			0,0,0,0,0,	},
	{	TDX_ID_QHJYTSXX,			TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"期货交易提示信息",		0,0,0,0,0,	},
	{	TDX_ID_KMRKCSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"可买入开仓数量",		0,0,0,0,0,	},
	{	TDX_ID_KMCKCSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"可卖出开仓数量",		0,0,0,0,0,	},
	{	TDX_ID_KMRPCSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"可买入平仓数量",		0,0,0,0,0,	},
	{	TDX_ID_KMCPCSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"可卖出平仓数量",		0,0,0,0,0,	},
	{	TDX_ID_KMRPJSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"可买入平今数量",		0,0,0,0,0,	},
	{	TDX_ID_KMCPJSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"可卖出平今数量",		0,0,0,0,0,	},
	{	TDX_ID_JKKY,				TDX_DT_LONG,	TDX_DISP_RIGHT,	  8,	"今开可用",				0,0,0,0,0,	},
	{	TDX_ID_LSKKY,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"历史开可用",			0,0,0,0,0,	},
	{	TDX_ID_DSYK,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"盯市盈亏",				0,0,0,0,0,	},
	{	TDX_ID_YKDS,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"盈亏点数",				0,0,0,0,0,	},
	{	TDX_ID_HYBH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"合约编号",				0,0,0,0,0,	},


	{	TDX_ID_HQ_MRSL1,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"买一量",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MRSL2,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"买二量",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MRSL3,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"买三量",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MRSL4,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"买四量",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MRSL5,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"买五量",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MRSL6,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"买六量",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MRSL7,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"买七量",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MRSL8,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"买八量",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MRSL9,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"买九量",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MRSL0,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"买十量",				0,0,0,0,0,	},

	{	TDX_ID_HQ_MRLG1,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"买一价",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MRLG2,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"买二价",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MRLG3,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"买三价",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MRLG4,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"买四价",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MRLG5,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"买五价",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MRLG6,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"买六价",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MRLG7,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"买七价",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MRLG8,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"买八价",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MRLG9,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"买九价",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MRLG0,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"买十价",				0,0,0,0,0,	},

	{	TDX_ID_HQ_MCSL1,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"卖一量",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MCSL2,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"卖二量",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MCSL3,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"卖三量",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MCSL4,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"卖四量",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MCSL5,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"卖五量",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MCSL6,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"卖六量",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MCSL7,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"卖七量",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MCSL8,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"卖八量",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MCSL9,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"卖九量",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MCSL0,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"卖十量",				0,0,0,0,0,	},

	{	TDX_ID_HQ_MCJS1,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"卖一价",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MCJS2,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"卖二价",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MCJS3,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"卖三价",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MCJS4,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"卖四价",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MCJS5,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"卖五价",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MCJS6,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"卖六价",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MCJS7,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"卖七价",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MCJS8,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"卖八价",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MCJS9,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"卖九价",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MCJS0,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"卖十价",				0,0,0,0,0,	},

	{	TDX_ID_HQ_ZTJG,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"涨停价格",				0,0,0,0,0,	},
	{	TDX_ID_HQ_DTJG,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"跌停价格",				0,0,0,0,0,	},
	{	TDX_ID_HQ_ZGJG,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"最高价",				0,0,0,0,0,	},
	{	TDX_ID_HQ_ZDJG,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"最低价",				0,0,0,0,0,	},
	{	TDX_ID_HQ_GZQJ,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"国债全价",				0,0,0,0,0,	},
	{	TDX_ID_HQ_OPEN,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"今开价",				0,0,0,0,0,	},
	{	TDX_ID_HQ_CLOSE,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"昨收价",				0,0,0,0,0,	},
	{	TDX_ID_HQ_TPBZ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"停牌标志",				0,0,0,0,0,	},
	{	TDX_ID_GZLX,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"国债利息",				0,0,0,0,0,	},
	{	TDX_ID_NOW,					TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"当前价",				0,0,0,0,0,	},
	{	TDX_ID_USERADDRESS,			TDX_DT_STRING,	TDX_DISP_RIGHT,  80,	"用户通讯地址",			0,0,0,0,0,	},
	{	TDX_ID_IDENTITYCARD,		TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"身份证",				0,0,0,0,0,	},
	{	TDX_ID_SEX,					TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"性别",					0,0,0,0,0,	},
	{	TDX_ID_POSTALCODE,			TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"邮政编码",				0,0,0,0,0,	},
	{	TDX_ID_HQ_ZDF,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"涨跌幅",				0,0,0,0,0,	},
	{	TDX_ID_HQ_ZDZ,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"涨跌值",				0,0,0,0,0,	},
	{	TDX_ID_GETGTHQ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"取柜台行情",			0,0,0,0,0,	},
	{	TDX_ID_MBYLX,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"每百元利息",			0,0,0,0,0,	},
	{	TDX_ID_GZBS,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"国债标识",				1,0,0,0,0,	},
	{	TDX_ID_ZQXXYXBZ,			TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"证券信息有效标志",		0,0,0,0,0,	},
	{	TDX_ID_ZQLB,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"证券类别",				0,0,0,0,0,	},
	{	TDX_ID_ZGSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"最高数量",				0,0,0,0,0,	},
	{	TDX_ID_ZDSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"最低数量",				0,0,0,0,0,	},

	{	TDX_ID_YZZZ_YHDM,			TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"银行代码",				0,0,0,0,0,	},
	{	TDX_ID_YZZZ_YHMC,			TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"银行名称",				0,0,0,0,0,	},
	{	TDX_ID_YZZZ_YHZH,			TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"银行帐号",				0,0,0,0,0,	},
	{	TDX_ID_YZZZ_YHMM,			TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"银行密码",				0,0,0,0,0,	},
	{	TDX_ID_YZZZ_XYHMM,			TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"新银行密码",			0,0,0,0,0,	},
	{	TDX_ID_YZZZ_YHLSH,			TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"银行流水号",			0,0,0,0,0,	},
	{	TDX_ID_YZZZ_ZZJE,			TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"转帐金额",				0,0,0,0,0,	},
	{	TDX_ID_YZZZ_ZZFX,			TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"转帐方向",				0,0,0,0,0,	},
	{	TDX_ID_YZZZ_YHYE,			TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"银行余额",				0,0,0,0,0,	},
	{	TDX_ID_YZZZ_ZZRQ,			TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"转帐日期",				0,0,0,0,0,	},
	{	TDX_ID_YZZZ_ZZSJ,			TDX_DT_TIME,	TDX_DISP_RIGHT,   8,	"转帐时间",				0,0,0,0,0,	},
	{	TDX_ID_YZZZ_ZZFXSM,			TDX_DT_STRING,	TDX_DISP_RIGHT, 40,		"转帐说明",				0,0,0,0,0,	},
	{	TDX_ID_YZTYH,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"银证通用户",			0,0,0,0,0,	},
	{	TDX_ID_YZZZ_NEEDZJMM,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"需要资金密码",			0,0,0,0,0,	},
	{	TDX_ID_YZZZ_NEEDYHMM,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"需要银行密码",			0,0,0,0,0,	},
	{	TDX_ID_YZZZ_SUPPORTYHYE,	TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"支持查银行余额",		0,0,0,0,0,	},
	{	TDX_ID_BANKCODE,			TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"银行代码",				0,0,0,0,0,	},
	{	TDX_ID_BANKYYB,				TDX_DT_STRING,	TDX_DISP_RIGHT,  40,	"银行营业部",			0,0,0,0,0,	},
	{	TDX_ID_BANKGDTYPE,			TDX_DT_STRING,	TDX_DISP_RIGHT,   2,	"银行股东代码登录市场",	0,0,0,0,0,	},
	{	TDX_ID_YZZZ_ZRMM,			TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"银证转入密码情况",		0,0,0,0,0,	},
	{	TDX_ID_YZZZ_ZCMM,			TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"银证转出密码情况",		0,0,0,0,0,	},
	{	TDX_ID_YZZZ_SHOWYHYE,		TDX_DT_CHAR,	TDX_DISP_RIGHT,  1,		"显示查银行余额",		0,0,0,0,0,	},
	{	TDX_ID_YZZZ_YHYEMM,			TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"查银行余额密码情况",	0,0,0,0,0,	},
	{	TDX_ID_ZRYHDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"转入银行代码",			0,0,0,0,0,	},
	{	TDX_ID_ZCYHDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"转出银行代码",			0,0,0,0,0,	},
	{	TDX_ID_ZRYHZH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"转入银行帐号",			0,0,0,0,0,	},
	{	TDX_ID_ZCYHZH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"转出银行帐号",			0,0,0,0,0,	},
	{	TDX_ID_ZJYHDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"中转银行代码",			0,0,0,0,0,	},
	{	TDX_ID_ZJYHMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"中转银行名称",			0,0,0,0,0,	},
	{	TDX_ID_ZJYHZH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"中转银行帐号",			0,0,0,0,0,	},
	{	TDX_ID_ZJYHZHMC,			TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"中转银行帐号名称",		0,0,0,0,0,	},
	{	TDX_ID_YHKH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"银行卡号",				0,0,0,0,0,	},
	{	TDX_ID_YHQC,				TDX_DT_STRING,	TDX_DISP_RIGHT, 128,	"银行全称",				0,0,0,0,0,	},
	{	TDX_ID_ZKBZ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"主卡标志",				0,0,0,0,0,	},
	{	TDX_ID_JQBZ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"鉴权标志",				0,0,0,0,0,	},

	{	TDX_ID_YHZHBM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"银行账户编码",			0,0,0,0,0,	},
	{	TDX_ID_YHZHBM1,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"银行账户编码1",		0,0,0,0,0,	},
	{	TDX_ID_YHZHBM2,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"银行账户编码2",		0,0,0,0,0,	},
	{	TDX_ID_YHZHBM3,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"银行账户编码3",		0,0,0,0,0,	},
	{	TDX_ID_YHZHBM4,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"银行账户编码4",		0,0,0,0,0,	},
	{	TDX_ID_YHZHMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"银行账户名称",			0,0,0,0,0,	},
	{	TDX_ID_YHZHMC1,				TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"银行账户名称1",		0,0,0,0,0,	},
	{	TDX_ID_YHZHMC2,				TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"银行账户名称2",		0,0,0,0,0,	},
	{	TDX_ID_YHZHMC3,				TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"银行账户名称3",		0,0,0,0,0,	},
	{	TDX_ID_YHZHMC4,				TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"银行账户名称4",		0,0,0,0,0,	},
	
	{	TDX_ID_YHCPDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"银行产品代码",			0,0,0,0,0,	},
	{	TDX_ID_YHCPMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"银行产品名称",			0,0,0,0,0,	},		
	{	TDX_ID_XTCPDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"信托产品代码",			0,0,0,0,0,	},
	{	TDX_ID_XTCPMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"信托产品名称",			0,0,0,0,0,	},	

	{	TDX_ID_RZLX,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"融资利息",				0,0,0,0,0,	},
	{	TDX_ID_XYZ,					TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"账户信用值",			0,0,0,0,0,	},
	{	TDX_ID_ZHWBXY,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"账户外部信用",			0,0,0,0,0,	},
	{	TDX_ID_XYSX,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"信用上限",				0,0,0,0,0,	},
	{	TDX_ID_RZSX,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"融资信用上限",			0,0,0,0,0,	},
	{	TDX_ID_RQSX,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"融券信用上限",			0,0,0,0,0,	},
	{	TDX_ID_XYCPBS,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"信用产品标示",			0,0,0,0,0,	},
	{	TDX_ID_DYZC,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"抵押资产",				0,0,0,0,0,	},
	{	TDX_ID_PCBZ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"平仓标志",				0,0,0,0,0,	},
	{	TDX_ID_RZSXF,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"融资管理费",			0,0,0,0,0,	},
	{	TDX_ID_RQMCZJ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"融券卖出资金",			0,0,0,0,0,	},
	{	TDX_ID_RZFX,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"融资方向",				0,0,0,0,0,	},
	{	TDX_ID_GHSL,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"归还数量",				0,0,0,0,0,	},
	{	TDX_ID_RZFZ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"融资负债",				0,0,0,0,0,	},
	{	TDX_ID_RQSZ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"融券市值",				0,0,0,0,0,	},
	{	TDX_ID_QSJE,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"清算金额",				0,0,0,0,0,	},
	{	TDX_ID_KYXYED,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"可用信用额度",			0,0,0,0,0,	},
	{	TDX_ID_YYXYED,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"已用信用额度",			0,0,0,0,0,	},
	{	TDX_ID_RZJE,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"融资金额",				0,0,0,0,0,	},
	{	TDX_ID_RQJE,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"融券金额",				0,0,0,0,0,	},
	{	TDX_ID_RQLX,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"融券利息",				0,0,0,0,0,	},
	{	TDX_ID_RQSXF,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"融券管理费",			0,0,0,0,0,	},
	{	TDX_ID_DBBL,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"担保比例",				0,0,0,0,0,	},
	{	TDX_ID_KYBZJ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"可用保证金",			0,0,0,0,0,	},
	{	TDX_ID_YYBZJ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"已用保证金",			0,0,0,0,0,	},
	{	TDX_ID_RQSYSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,  12,	"融券使用数量",			0,0,0,0,0,	},
	{	TDX_ID_PCRQ,				TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"平仓日期",				0,0,0,0,0,	},
	{	TDX_ID_XYHYLX,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"合约类型",				0,0,0,0,0,	},
	{	TDX_ID_CHSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,  12,	"偿还数量",				0,0,0,0,0,	},
	{	TDX_ID_CHJE,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"偿还金额",				0,0,0,0,0,	},
	{	TDX_ID_SSCHSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,  12,	"实时偿还数量",			0,0,0,0,0,	},
	{	TDX_ID_SSCHJE,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"实时偿还金额",			0,0,0,0,0,	},
	{	TDX_ID_CHLX,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"偿还利息",				0,0,0,0,0,	},
	{	TDX_ID_HYSXF,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"合约费用",				0,0,0,0,0,	},
	{	TDX_ID_HYLL,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"合约利率",				0,0,0,0,0,	},
	{	TDX_ID_HYLXJE,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"合约利息",				0,0,0,0,0,	},
	{	TDX_ID_RZBL,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"融资比例",				0,0,0,0,0,	},
	{	TDX_ID_GPZSL,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"股票折算率",			0,0,0,0,0,	},
	{	TDX_ID_XYJB,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"信用级别",				0,0,0,0,0,	},
	{	TDX_ID_FXZT,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"风险状态",				0,0,0,0,0,	},
	{	TDX_ID_RZBZJBL,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"融资保证金比例",		0,0,0,0,0,	},
	{	TDX_ID_RQBZJBL,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"融券保证金比例",		0,0,0,0,0,	},
	{	TDX_ID_RZRQLXFY,			TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"融资融券利息费用",		0,0,0,0,0,	},
	{	TDX_ID_ZFZ,					TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"总负债",				0,0,0,0,0,	},
	{	TDX_ID_FZBL,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"负债比例",				0,0,0,0,0,	},
	{	TDX_ID_HYQX,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"合约期限",				0,0,0,0,0,	},
	{	TDX_ID_SYRZED,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"剩余融资额度",			0,0,0,0,0,	},
	{	TDX_ID_SYRQED,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"剩余容券额度",			0,0,0,0,0,	},
	{	TDX_ID_TQZZLL,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"提前终止利率",			0,0,0,0,0,	},
	{	TDX_ID_DQR,					TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"到期日",				0,0,0,0,0,	},

	{	TDX_ID_XT_ERRCODE,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"错误号",				0,0,0,0,0,	},
	{	TDX_ID_XT_ERRMSG,			TDX_DT_STRING,	TDX_DISP_RIGHT,  80,	"错误信息",				0,0,0,0,0,	},
	{	TDX_ID_XT_FUNCNO,			TDX_DT_SHORT,	TDX_DISP_RIGHT,   4,	"功能编号",				0,0,0,0,0,	},
	{	TDX_ID_XT_CLIVER,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"客户端版本",			0,0,0,0,0,	},
	{	TDX_ID_XT_MACADDR,			TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"MAC地址",				0,0,0,0,0,	},
	{	TDX_ID_XT_IPADDR,			TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"IP地址",				0,0,0,0,0,	},
	{	TDX_ID_XT_CLITYPE,			TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"客户类别",				0,0,0,0,0,	},
	{	TDX_ID_XT_STARTPOS,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"起始序号",				0,0,0,0,0,	},
	{	TDX_ID_XT_AUTH_NEWINFO,		TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"认证新信息",			0,0,0,0,0,	},
	{	TDX_ID_XT_OEM_FLAG,			TDX_DT_CHAR,	TDX_DISP_RIGHT,  16,	"OEM标识",				0,0,0,0,0,	},
	{	TDX_ID_XT_AUTH_MODE,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"认证方式",				0,0,0,0,0,	},
	{	TDX_ID_XT_AUTH_INFO,		TDX_DT_CHAR,	TDX_DISP_RIGHT, 512,	"认证信息",				0,0,0,0,0,	},
	{	TDX_ID_XT_BRANCHID,			TDX_DT_CHAR,	TDX_DISP_RIGHT,  10,	"营业部ID",				0,0,0,0,0,	},
	{	TDX_ID_XT_RESERVED,			TDX_DT_STRING,	TDX_DISP_RIGHT,  80,	"保留信息",				1,0,0,0,0,	},
	{	TDX_ID_XT_RECONNECTFLAG,	TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"断线重联标志",			1,0,0,0,0,	},
	{	TDX_ID_XT_COUNTERSTATUS,	TDX_DT_STRING,	TDX_DISP_RIGHT,  80,	"柜台状态",				0,0,0,0,0,	},
	{	TDX_ID_XT_VIPFLAG,			TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"VIP标志",				1,0,0,0,0,	},
	{	TDX_ID_XT_REMARK,			TDX_DT_STRING,	TDX_DISP_RIGHT,  80,	"备注",					0,0,0,0,0,	},
	{	TDX_ID_XT_CLIENTRIGHTS,		TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"客户权限",				1,0,0,0,0,	},
	{	TDX_ID_XT_LAST_LOGIN_DATE,	TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"上次登录日期",			1,0,0,0,0,	},
	{	TDX_ID_XT_LAST_LOGIN_TIME,	TDX_DT_TIME,	TDX_DISP_RIGHT,   8,	"上次登录时间",			1,0,0,0,0,	},
	{	TDX_ID_XT_AHTHCHAR1,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"验证字符1",			1,0,0,0,0,	},
	{	TDX_ID_XT_AHTHCHAR2,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"验证字符2",			1,0,0,0,0,	},
	{	TDX_ID_XT_CHECKRISKFLAG,	TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"检查风险标志",			1,0,0,0,0,	},
	{	TDX_ID_XT_FJYZHBZ,			TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"非交易帐号标志",		1,0,0,0,0,	},
	{	TDX_ID_XT_JZJJKHBZ,			TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"禁止基金开户标志",		1,0,0,0,0,	},
	{	TDX_ID_XT_INCREMENTMODE,	TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"增量模式开关",			0,0,0,0,0,	},
	{	TDX_ID_XT_PARAM,			TDX_DT_STRING,	TDX_DISP_RIGHT,  80,	"参数",					0,0,0,0,0,	},
	{	TDX_ID_XT_MODE,				TDX_DT_STRING,	TDX_DISP_RIGHT,  80,	"模式",					0,0,0,0,0,	},
	{	TDX_ID_XT_DESCRIPTION,		TDX_DT_STRING,	TDX_DISP_RIGHT,  80,	"描述",					0,0,0,0,0,	},
	{	TDX_ID_XT_QUERYMODE,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"查询模式",				0,0,0,0,0,	},
	{	TDX_ID_XT_DISPLAYCOLOR,		TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"显示颜色",				1,0,0,0,0,	},
	{	TDX_ID_XT_PASSWORDFLAG,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"密码标志",				0,0,0,0,0,	},
	{	TDX_ID_XT_HANDLE,			TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"句柄",					1,0,0,0,0,	},
	{	TDX_ID_XT_GTLB,				TDX_DT_STRING,	TDX_DISP_RIGHT,   1,	"柜台类别",				1,0,0,0,0,	},
	{	TDX_ID_XT_MACHINEINFO,		TDX_DT_STRING,	TDX_DISP_RIGHT, 800,	"机器信息",				0,0,0,0,0,	},
	{	TDX_ID_XT_LIMITMODE,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"受限模式",				0,0,0,0,0,	},
	{	TDX_ID_XT_MACHINECODE,		TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"机器特征码",			0,0,0,0,0,	},
	{	TDX_ID_XT_MOBILECHECKCODE,	TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"手机校验码",			0,0,0,0,0,	},
	{	TDX_ID_XT_BRANCHMODIFY,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"营业部改变",			0,0,0,0,0,	},
	{	TDX_ID_XT_NEEDEDAUTHMODE,	TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"所需认证方式",			0,0,0,0,0,	},
	{	TDX_ID_XT_SESSION,			TDX_DT_STRING,	TDX_DISP_RIGHT, 128,	"SESSION信息",			0,0,0,0,0,	},
	{	TDX_ID_XT_URL,				TDX_DT_STRING,	TDX_DISP_RIGHT, 128,	"URL",					0,0,0,0,0,	},
	{	TDX_ID_XT_INFOCOLUMN,		TDX_DT_STRING,	TDX_DISP_RIGHT, 128,	"资讯栏目",				0,0,0,0,0,	},
	{	TDX_ID_XT_REALCLIENTVERSION,TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"内部客户端版本",		0,0,0,0,0,	},
	{	TDX_ID_XT_CN,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"CN",					0,0,0,0,0,	},
	{	TDX_ID_XT_SN,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"SN",					0,0,0,0,0,	},
	{	TDX_ID_XT_DN,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"DN",					0,0,0,0,0,	},
	{	TDX_ID_XT_NEEDCONFIRMFLAGS,	TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"需确认的标识串",		0,0,0,0,0,	},
	{	TDX_ID_XT_URL2,				TDX_DT_STRING,	TDX_DISP_RIGHT, 128,	"URL2",					0,0,0,0,0,	},
	{	TDX_ID_XT_REDIRECTFLAG,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"重定向标志",			0,0,0,0,0,	},
	{	TDX_ID_XT_REDIRECTINFO,		TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"重定向信息",			0,0,0,0,0,	},
	{	TDX_ID_XT_LAST_LOGIN_LOCATION,TDX_DT_STRING,TDX_DISP_RIGHT, 128,	"上次登录位置",			1,0,0,0,0,	},
	{	TDX_ID_XT_SLOTID,			TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"证书容器ID",			0,0,0,0,0,	},
	{	TDX_ID_XT_CID,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"证书厂商ID",			0,0,0,0,0,	},
	{	TDX_ID_XT_INPUTPARAM,		TDX_DT_STRING,	TDX_DISP_RIGHT,1024,	"输入参数",				0,0,0,0,0,	},
	{	TDX_ID_XT_OUTPUTPARAM,		TDX_DT_STRING,	TDX_DISP_RIGHT,8192,	"输出参数",				0,0,0,0,0,	},
	{	TDX_ID_XT_TOKEN,			TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"令牌",					0,0,0,0,0,	},
	{	TDX_ID_XT_LOGINEMAIL,		TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"登录Email",			0,0,0,0,0,	},
	{	TDX_ID_XT_TRADEEMAIL,		TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"交易Email",			0,0,0,0,0,	},
	{	TDX_ID_XT_MESSAGEID,		TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"信息编号",				0,0,0,0,0,	},
	{	TDX_ID_XT_MESSAGETITLE,		TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"信息标题",				0,0,0,0,0,	},
	{	TDX_ID_XT_MESSAGECONTENT,	TDX_DT_STRING,	TDX_DISP_RIGHT,8192,	"信息内容",				0,0,0,0,0,	},
	{	TDX_ID_XT_POSITIONSTRING,	TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"定位字串",				1,0,0,0,0,	},
	{	TDX_ID_XT_BEGINLINE,		TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"起始行号",				1,0,0,0,0,	},
	{	TDX_ID_XT_REQUESTLINE,		TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"请求行数",				1,0,0,0,0,	},
	{	TDX_ID_XT_TOTALLINE,		TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"总共行数",				1,0,0,0,0,	},
	{	TDX_ID_XT_RISKPARAM,		TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"风险参数",				1,0,0,0,0,	},
	{	TDX_ID_XT_LOGINRETURNPARAM,	TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"登录返回参数",			1,0,0,0,0,	},
	{	TDX_ID_XT_MOBILEMACHINEINFO,TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"手机机器信息",			1,0,0,0,0,	},
	{	TDX_ID_XT_PACKAGELIST,		TDX_DT_STRING,	TDX_DISP_RIGHT,1024,	"套餐列表",				1,0,0,0,0,	},
	{	TDX_ID_XT_PRODUCTLIST,		TDX_DT_STRING,	TDX_DISP_RIGHT,1024,	"产品列表",				1,0,0,0,0,	},
	{	TDX_ID_XT_FEATURELIST,		TDX_DT_STRING,	TDX_DISP_RIGHT,1024,	"功能列表",				1,0,0,0,0,	},
	{	TDX_ID_XT_CONFIGLIST,		TDX_DT_STRING,	TDX_DISP_RIGHT,1024,	"配置列表",				1,0,0,0,0,	},
	{	TDX_ID_XT_LOGINENTERPARAM,	TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"登录输入参数",			1,0,0,0,0,	},
	{	TDX_ID_XT_ALGORIGHTLIST,	TDX_DT_STRING,	TDX_DISP_RIGHT,1024,	"算法权限列表",			1,0,0,0,0,	},
	{	TDX_ID_XT_FUNCTIONVERSION,	TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"功能版本",				1,0,0,0,0,	},
	{	TDX_ID_XT_CLIENTINVERSION,	TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"客户端内部版本",		1,0,0,0,0,	},
	{	TDX_ID_XT_VERSIONSTRING,	TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"版本字符串",			1,0,0,0,0,	},

	{	TDX_ID_XLYZT_XGKT_FLAG,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"修改开通标记",			0,0,0,0,0,	},

	{	TDX_ID_XLYZT_START_DATE,	TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"生效日期",				0,0,0,0,0,	},
	{	TDX_ID_XLYZT_END_DATE,		TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"失效日期",				0,0,0,0,0,	},
	{	TDX_ID_XLYZT_DEBT_KIND,		TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"回购品种",				0,0,0,0,0,	},
	{	TDX_ID_XLYZT_JE_MIN,		TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"资金下限",				0,0,0,0,0,	},
	{	TDX_ID_XLYZT_JE_MAX,		TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"资金上限",				0,0,0,0,0,	},
};

const FIELDINFO tdxScntrFieldInfo[]=
{
//	{	字段类型,					数据类型,		显示(对齐)方法,宽度,	字段说明,				其它标记,	},

	{	TDX_ID_CA_KHH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"客户号",				0,0,0,0,0,	},
	{	TDX_ID_ZHLB,				TDX_DT_STRING,	TDX_DISP_RIGHT,   2,	"帐号类别",				1,0,0,0,0,	},
	{	TDX_ID_XT_GTLB,				TDX_DT_STRING,	TDX_DISP_RIGHT,   1,	"柜台类别",				1,0,0,0,0,	},
	{	TDX_ID_CA_KHMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"客户名称",				0,0,0,0,0,	},
	{	TDX_ID_CA_SQBZ,				TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"申请标志",				0,0,0,0,0,	},
	{	TDX_ID_CA_TXMM,				TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"认证口令",				0,0,0,0,0,	},
	{	TDX_ID_CA_XTXMM,			TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"新认证口令",			0,0,0,0,0,	},
	{	TDX_ID_CA_ZSXH,				TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"证书序号",				0,0,0,0,0,	},
	{	TDX_ID_CA_AQJB,				TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"安全级别",				0,0,0,0,0,	},
	{	TDX_ID_CA_YHFJ,				TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"用户分级",				0,0,0,0,0,	},
	{	TDX_ID_CA_YHJBMS,			TDX_DT_STRING,	TDX_DISP_LEFT,    4,	"用户级别描述",			0,0,0,0,0,	},
	{	TDX_ID_CA_YHQX,				TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"用户权限",				0,0,0,0,0,	},
	{	TDX_ID_CA_KJYBZ,			TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"可交易标志",			0,0,0,0,0,	},
	{	TDX_ID_CA_ZSSHBZ,			TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"证书审核标志",			0,0,0,0,0,	},
	{	TDX_ID_CA_ZSXZBZ,			TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"证书下载标志",			0,0,0,0,0,	},
	{	TDX_ID_CA_ZSQSID,			TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"证书券商ID",			0,0,0,0,0,	},
	{	TDX_ID_CA_ZSBFJG,			TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"证书颁发机构",			0,0,0,0,0,	},
	{	TDX_ID_CA_ZSBFYH,			TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"证书颁发用户",			0,0,0,0,0,	},
	{	TDX_ID_CA_ZSQSRQ,			TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"证书申请日期",			0,0,0,0,0,	},
	{	TDX_ID_CA_ZSJZRQ,			TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"证书截止日期",			0,0,0,0,0,	},
	{	TDX_ID_CA_ZSWS,				TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"证书位数",				0,0,0,0,0,	},
	{	TDX_ID_CA_ZSGY,				TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"证书公钥",				0,0,0,0,0,	},
	{	TDX_ID_CA_CZJG,				TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"操作机构",				0,0,0,0,0,	},
	{	TDX_ID_CA_CZY,				TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"操作员",				0,0,0,0,0,	},
	{	TDX_ID_CA_CZMM,				TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"操作密码",				0,0,0,0,0,	},
	{	TDX_ID_CA_CZSX,				TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"操作属性",				0,0,0,0,0,	},
	{	TDX_ID_CA_CZBZ,				TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"操作标志",				0,0,0,0,0,	},
	{	TDX_ID_CA_RESV, 			TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"保留字段",				0,0,0,0,0,	},
	{	IDX_ID_CA_ZSKGXBZ,			TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"证书可更新标志",		0,0,0,0,0,	},
	{	TDX_ID_CA_ZSJYGXBZ,			TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"证书建议更新标志",		0,0,0,0,0,	},
	{	TDX_ID_CA_ZSSYYXTS,			TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"证书剩余有效天数",		0,0,0,0,0,	},
	{	TDX_ID_CA_ZHLB,				TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"账号类别",				0,0,0,0,0,	},
	{	TDX_ID_CA_TQID,				TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"TQ号",					0,0,0,0,0,	},
	{	TDX_ID_CA_TQMAIL,			TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"TQ邮件",				0,0,0,0,0,	},
	{	TDX_ID_CA_XGTXMMBZ,			TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"认证口令修改标记",		0,0,0,0,0,	},
	{	TDX_ID_CA_L2USER,			TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"LEVEL2账号",			0,0,0,0,0,	},
	{	TDX_ID_CA_L2PASS,			TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"LEVEL2密码",			0,0,0,0,0,	},
	{	TDX_ID_CA_YHJBZT,			TDX_DT_STRING,	TDX_DISP_LEFT,    4,	"用户级别状态",			0,0,0,0,0,	},
	{	TDX_ID_CA_YHJBBZ,			TDX_DT_STRING,	TDX_DISP_LEFT,  256,	"用户级别备注",			0,0,0,0,0,	},
	{	TDX_ID_CA_ISVIPHOST,		TDX_DT_STRING,	TDX_DISP_RIGHT,   1,	"VIP主站标识",			0,0,0,0,0,	},
	{	TDX_ID_CA_KHJL,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"客户经理编号",			0,0,0,0,0,	},
	{	TDX_ID_CA_TOPICID,			TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"主题编号",				0,0,0,0,0,	},
	{	TDX_ID_CA_TOPICTITLE,		TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"主题标题",				0,0,0,0,0,	},
	{	TDX_ID_CA_CONTENT,			TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"主题正文",				0,0,0,0,0,	},
	{	TDX_ID_CA_QUERYDATE,		TDX_DT_STRING,	TDX_DISP_RIGHT,   9,	"查询日期",				0,0,0,0,0,	},
	{	TDX_ID_CA_REQDATE,			TDX_DT_STRING,	TDX_DISP_RIGHT,   9,	"主题发布日期",			0,0,0,0,0,	},
	{	TDX_ID_CA_REQTIME,			TDX_DT_STRING,	TDX_DISP_RIGHT,   9,	"主题发布时间",			0,0,0,0,0,	},
	{	TDX_ID_CA_VALDATE,			TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"主题有效天数",			0,0,0,0,0,	},
	{	TDX_ID_CA_CLOSEFLAG,		TDX_DT_STRING,	TDX_DISP_RIGHT,   2,	"关闭标志",				0,0,0,0,0,	},
	{	TDX_ID_CA_SATISFAC,			TDX_DT_STRING,	TDX_DISP_RIGHT,  10,	"满意度",				0,0,0,0,0,	},
	{	TDX_ID_CA_REMINDFLAG,		TDX_DT_STRING,	TDX_DISP_RIGHT,   2,	"提示关标志闭",			0,0,0,0,0,	},
	{	TDX_ID_CA_NEWANSFLAG,		TDX_DT_STRING,	TDX_DISP_RIGHT,   2,	"最新回复提示",			0,0,0,0,0,	},
	{	TDX_ID_CA_ANSWERID,			TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"回复编号",				0,0,0,0,0,	},
	{	TDX_ID_CA_WHOANS,			TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"回复人",				0,0,0,0,0,	},
	{	TDX_ID_CA_QUERYALL,			TDX_DT_STRING,	TDX_DISP_RIGHT,   2,	"是否查询所有",			0,0,0,0,0,	},
	{	TDX_ID_CA_BRANCHMSGID,		TDX_DT_STRING,	TDX_DISP_RIGHT,   2,	"营业部信息ID",			0,0,0,0,0,	},
	{	TDX_ID_CA_NEWMSGNUM,		TDX_DT_STRING,	TDX_DISP_RIGHT,   2,	"新消息条数",			0,0,0,0,0,	},
	{	TDX_ID_CA_NOREADMSGNUM,		TDX_DT_STRING,	TDX_DISP_RIGHT,   2,	"未读消息条数",			0,0,0,0,0,	},
	{	TDX_ID_CA_RESETFLAG,		TDX_DT_STRING,	TDX_DISP_RIGHT,   2,	"重置标志",				0,0,0,0,0,	},
                                                                                                	
	{	TDX_ID_CA_SJH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"手机号",				0,0,0,0,0,	},
	{	TDX_ID_CA_ZJHM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  20,	"证件号码",				0,0,0,0,0,	},
	{	TDX_ID_CA_KHXB,				TDX_DT_STRING,	TDX_DISP_RIGHT,   5,	"客户性别",				0,0,0,0,0,	},
	{	TDX_ID_CA_EMAIL,			TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"电子邮件",				0,0,0,0,0,	},
	{	TDX_ID_CA_JHM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  20,	"激活码",				0,0,0,0,0,	},
	{	TDX_ID_CA_DRZB,				TDX_DT_STRING,	TDX_DISP_RIGHT,  20,	"当日指标",				0,0,0,0,0,	},
	{	TDX_ID_CA_LEVELNAME,		TDX_DT_STRING,	TDX_DISP_RIGHT,  20,	"等级名称",				0,0,0,0,0,	},
	{	TDX_ID_CA_ZBMAX,			TDX_DT_STRING,	TDX_DISP_RIGHT,  20,	"指标上限",				0,0,0,0,0,	},
	{	TDX_ID_CA_ZBMIN,			TDX_DT_STRING,	TDX_DISP_RIGHT,  20,	"指标下限",				0,0,0,0,0,	},
	{	TDX_ID_CA_PROTOC,			TDX_DT_STRING,	TDX_DISP_RIGHT,1024,	"升级协议",				0,0,0,0,0,	},
	{	TDX_ID_CA_COMMISION,		TDX_DT_STRING,	TDX_DISP_RIGHT,  20,	"佣金",					0,0,0,0,0,	},
	{	TDX_ID_CA_BIRTHTITIP,		TDX_DT_STRING,	TDX_DISP_RIGHT,   2,	"是否需要生日提醒",		0,0,0,0,0,	},
	{	TDX_ID_CA_NOTICETITLE,		TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"公告标题",				0,0,0,0,0,	},
	{	TDX_ID_CA_NOTICECONTENT,	TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"公告正文内容",			0,0,0,0,0,	},
	{	TDX_ID_CA_TSUPDATE,			TDX_DT_STRING,	TDX_DISP_RIGHT,   5,	"提示升级",				0,0,0,0,0,	},
	{	TDX_ID_CA_NOWLEVELNO,		TDX_DT_STRING,	TDX_DISP_RIGHT,   5,	"当前等级编号",			0,0,0,0,0,	},
	{	TDX_ID_CA_NOWLEVELNAME,		TDX_DT_STRING,	TDX_DISP_RIGHT,  20,	"当前等级名称",			0,0,0,0,0,	},
	{	TDX_ID_CA_CANLEVELNO,		TDX_DT_STRING,	TDX_DISP_RIGHT,  20,	"可申请等级编号",		0,0,0,0,0,	},
	{	TDX_ID_CA_CANLEVELNAME,		TDX_DT_STRING,	TDX_DISP_RIGHT,  20,	"可申请等级名称",		0,0,0,0,0,	},
	{	TDX_ID_CA_MENU,				TDX_DT_STRING,	TDX_DISP_RIGHT,  20,	"可见栏目",				0,0,0,0,0,	},

	{	TDX_ID_CA_LASTIP,			TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"上次登录IP",			0,0,0,0,0,	},
	{	TDX_ID_CA_NEWIP,			TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"上次登录IP",			0,0,0,0,0,	},
	{	TDX_ID_CA_LASPROV,			TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"上次登录省份",			0,0,0,0,0,	},
	{	TDX_ID_CA_NEWPROV,			TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"本次登录省份",			0,0,0,0,0,	},
	{	TDX_ID_CA_LASSITE,			TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"上次登录位置",			0,0,0,0,0,	},
	{	TDX_ID_CA_NEWSITE,			TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"本次登录位置",			0,0,0,0,0,	},
	{	TDX_ID_CA_QSRQ,				TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"起始查询时间",			0,0,0,0,0,	},
	{	TDX_ID_CA_ZZRQ,				TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"终止查询时间",			0,0,0,0,0,	},
	{	TDX_ID_CA_DLSJ,				TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"登录时间",				0,0,0,0,0,	},
	{	TDX_ID_CA_DLRQ,				TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"登录日期",				0,0,0,0,0,	},
	{	TDX_ID_CA_MMBHWT,			TDX_DT_STRING,	TDX_DISP_RIGHT,1024,	"密码保护问题",			0,0,0,0,0,	},
	{	TDX_ID_CA_MMBHWT1,			TDX_DT_STRING,	TDX_DISP_RIGHT,1024,	"密码保护问题1",		0,0,0,0,0,	},
	{	TDX_ID_CA_MMBHWT2,			TDX_DT_STRING,	TDX_DISP_RIGHT,1024,	"密码保护问题2",		0,0,0,0,0,	},
	{	TDX_ID_CA_MMBHWT3,			TDX_DT_STRING,	TDX_DISP_RIGHT,1024,	"密码保护问题3",		0,0,0,0,0,	},
	{	TDX_ID_CA_MMBHWT4,			TDX_DT_STRING,	TDX_DISP_RIGHT,1024,	"密码保护问题4",		0,0,0,0,0,	},
	{	TDX_ID_CA_JQTZM,			TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"机器特征码",			0,0,0,0,0,	},
	{	TDX_ID_CA_TZZB,				TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"挑战坐标",				0,0,0,0,0,	},
	{	TDX_ID_CA_CSCS,				TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"尝试次数",				0,0,0,0,0,	},
	{	TDX_ID_CA_ISDLWZTS,			TDX_DT_STRING,	TDX_DISP_RIGHT,   2,	"是否支持登录位置提示",	0,0,0,0,0,	},
	{	TDX_ID_CA_ISMMBHWT,			TDX_DT_STRING,	TDX_DISP_RIGHT,   2,	"是否支持密码保护问题",	0,0,0,0,0,	},
	{	TDX_ID_CA_ISJQTZMBD,		TDX_DT_STRING,	TDX_DISP_RIGHT,   2,	"是否支持特征码绑定",	0,0,0,0,0,	},
	{	TDX_ID_CA_MAC,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"机器MAC地址",			0,0,0,0,0,	},
	{	TDX_ID_CA_YLWT,				TDX_DT_STRING,	TDX_DISP_RIGHT,1024,	"预留问题",				0,0,0,0,0,	},
	{	TDX_ID_CA_ISYLWT,			TDX_DT_STRING,	TDX_DISP_RIGHT,   2,	"是否支持预留问题",		0,0,0,0,0,	},
	{	TDX_ID_CA_CERTREQ,			TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"申请请求",				0,0,0,0,0,	},
	{	TDX_ID_CA_USERCERDN,		TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"证书DN信息",			0,0,0,0,0,	},
	{	TDX_ID_CA_CERTTOKEN,		TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"证书业务号",			0,0,0,0,0,	},
	{	TDX_ID_CA_CERTINFO,			TDX_DT_STRING,	TDX_DISP_RIGHT,8192,	"证书内容",				0,0,0,0,0,	},
	{	TDX_ID_CA_SLOTSN,			TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"装载证书容器SN",		0,0,0,0,0,	},
	{	TDX_ID_CA_CERTSN,			TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"证书SN号",				0,0,0,0,0,	},
	{	TDX_ID_CA_CID,				TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"三方机构ID",			0,0,0,0,0,	},
	{	TDX_ID_CA_SEEDINFO,			TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"OTP种子信息",			0,0,0,0,0,	},
	{	TDX_ID_CA_OTPSN,			TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"OTPSN",				0,0,0,0,0,	},
	{	TDX_ID_CA_BINDNUM,			TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"已绑定的机器台数",		0,0,0,0,0,	},
	{	TDX_ID_CA_IDCARD,			TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"身份证号码",			0,0,0,0,0,	},
	{	TDX_ID_CA_YZM,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"验证码",				0,0,0,0,0,	},
	{	TDX_ID_XT_STARTPOS,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"起始序号",				0,0,0,0,0,	},
	{	TDX_ID_XT_STARTPOS,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"起始序号",				0,0,0,0,0,	},
	{	TDX_ID_CA_VER,				TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"密保问题版本",			0,0,0,0,0,	},
	{	TDX_ID_CA_PWDPROQUESTION,	TDX_DT_STRING,	TDX_DISP_RIGHT, 128,	"密保问题",				0,0,0,0,0,	},
	{	TDX_ID_CA_PWDQACZBZ,		TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"密保问题操作标志",		0,0,0,0,0,	},
	{	TDX_ID_CA_CONNID,			TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"用户连接ID",			0,0,0,0,0,	},
	{	TDX_ID_UM_BROKERCODE,		TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"经纪人代码",			0,0,0,0,0,	},
	{	TDX_ID_UM_BROKERBRANCH,		TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"经纪人营业部",			0,0,0,0,0,	},
	{	TDX_ID_UM_BROKERNAME,		TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"经纪人姓名",			0,0,0,0,0,	},
	{	TDX_ID_UM_BROKERSTATUS,		TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"经纪人状态",			0,0,0,0,0,	},
	{	TDX_ID_UM_BROKERLEVEL,		TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"经纪人级别",			0,0,0,0,0,	},
	{	TDX_ID_UM_UPBROKER,			TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"上级经纪人",			0,0,0,0,0,	},
	{	TDX_ID_UM_BROKERNATIONALITY,TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"经纪人国籍",			0,0,0,0,0,	},
	{	TDX_ID_UM_BROKERPHONECODE,	TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"经纪人电话",			0,0,0,0,0,	},
	{	TDX_ID_UM_BROKERMOPHONE,	TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"经纪人移动电话",		0,0,0,0,0,	},
	{	TDX_ID_UM_BROKEREMAIL,		TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"经纪人电子邮件",		0,0,0,0,0,	},
	{	TDX_ID_UM_BROKERMSN,		TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"经纪人MSN",			0,0,0,0,0,	},
	{	TDX_ID_UM_BROKERQQ,			TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"经纪人QQ",				0,0,0,0,0,	},
	{	TDX_ID_UM_BROKERSEX,		TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"经纪人性别",			0,0,0,0,0,	},
	{	TDX_ID_UM_BROKERAGE,		TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"经纪人年龄",			0,0,0,0,0,	},
	{	TDX_ID_UM_BROKERDEGREE,		TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"经纪人学历",			0,0,0,0,0,	},
	{	TDX_ID_UM_BROKERFAVOR,		TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"经纪人操作习惯",		0,0,0,0,0,	},
	{	TDX_ID_UM_BROKERNATIVEPLACE,TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"经纪人个人谏言",		0,0,0,0,0,	},
	{	TDX_ID_UM_BROKERQUAL,		TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"经纪人从业资格",		0,0,0,0,0,	},
	{	TDX_ID_UM_BROKERSATISLEV,	TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"经纪人满意度级别",		0,0,0,0,0,	},
	{	TDX_ID_UM_BROKERPHOTOS,		TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"经纪人照片",			0,0,0,0,0,	},
	{	TDX_ID_UM_BROKERNOTES,		TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"经纪人备注",			0,0,0,0,0,	},
	{	TDX_ID_UM_BRANCHNAME,		TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"营业部名称",			0,0,0,0,0,	},
	{	TDX_ID_UM_COMHOTLINE,		TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"公司客户热线",			0,0,0,0,0,	},
	{	TDX_ID_UM_BRANCHTRADEASK,	TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"营业部交易咨询电话",	0,0,0,0,0,	},
	{	TDX_ID_UM_BRANCHINVESTASK,	TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"营业部投资咨询电话",	0,0,0,0,0,	},
	{	TDX_ID_UM_PASSEXAM,			TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"是否通过考试",			0,0,0,0,0,	},
	{	TDX_ID_UM_PRACTISETIME,		TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"从业时间",				0,0,0,0,0,	},
	{	TDX_ID_CA_MACHINENAME,		TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"机器昵称",				0,0,0,0,0,	},
	{	TDX_ID_CA_PROVISIONAL,		TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"临时标志",				0,0,0,0,0,	},
	{	TDX_ID_CA_MACHINEBINDTIME,	TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"绑定时间",				0,0,0,0,0,	},
	{	TDX_ID_CA_USERNICK,			TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"用户昵称",				0,0,0,0,0,	},
	{	TDX_ID_CA_CARDTYPE,			TDX_DT_STRING,	TDX_DISP_RIGHT,  4,		"证件类型",				0,0,0,0,0,	},
	{	TDX_ID_CA_BIRTH,			TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"出生日期",				0,0,0,0,0,	},
	{	TDX_ID_CA_POSTCODE,			TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"邮政编码",				0,0,0,0,0,	},
	{	TDX_ID_CA_ADDRESS,			TDX_DT_STRING,	TDX_DISP_RIGHT,  128,	"联系地址",				0,0,0,0,0,	},
	{	TDX_ID_CA_OFFPHONE,			TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"办公电话",				0,0,0,0,0,	},
	{	TDX_ID_CA_HOMEPHONE,		TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"家庭电话",				0,0,0,0,0,	},
	{	TDX_ID_CA_FAXPHONE,			TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"传真电话",				0,0,0,0,0,	},
	{	TDX_ID_CA_EDUCATION,		TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"学历",					0,0,0,0,0,	},
	{	TDX_ID_CA_TOKEN,			TDX_DT_STRING,	TDX_DISP_RIGHT,  512,	"令牌",					0,0,0,0,0,	},
	{	TDX_ID_JYMM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"交易密码",				0,0,0,0,0,	},
	{	TDX_ID_CA_YYBID,			TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"营业部ID",				0,0,0,0,0,	},
	{	TDX_ID_CA_GD_XH,			TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"序号",					0,0,0,0,0,	},
	{	TDX_ID_CA_GD_DATE,			TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"日期",					0,0,0,0,0,	},
	{	TDX_ID_CA_GD_TIME,			TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"时间",					0,0,0,0,0,	},
	{	TDX_ID_CA_GD_HARDINFO,		TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"计算机特征码信息",		0,0,0,0,0,	},
	{	TDX_ID_CA_GD_MOREINFO,		TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"计算机昵称",			0,0,0,0,0,	},
	{	TDX_ID_CA_GD_TERMINALTYPE,	TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"终端类型",				0,0,0,0,0,	},
	{	TDX_ID_CA_USERSTOCK,		TDX_DT_STRING,	TDX_DISP_RIGHT,  1024,	"用户自选股",			0,0,0,0,0,	},
	{	TDX_ID_XT_PARAM,			TDX_DT_STRING,	TDX_DISP_RIGHT,  80,	"参数",					0,0,0,0,0,	},
	{	TDX_ID_XT_MODE,				TDX_DT_STRING,	TDX_DISP_RIGHT,  80,	"模式",					0,0,0,0,0,	},
	{	TDX_ID_XT_DESCRIPTION,		TDX_DT_STRING,	TDX_DISP_RIGHT,  80,	"描述",					0,0,0,0,0,	},
	{	TDX_ID_XT_REMARK,			TDX_DT_STRING,	TDX_DISP_RIGHT,  80,	"备注",					0,0,0,0,0,	},
	{	TDX_ID_CA_TRADETIME,		TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"交易时间",				0,0,0,0,0,	},
	{	TDX_ID_CA_TRADETYPE,		TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"交易类型",				0,0,0,0,0,	},
	{	TDX_ID_CA_SCORE,			TDX_DT_LONG,	TDX_DISP_RIGHT,  8,		"积分值",				0,0,0,0,0,	},
	{	TDX_ID_CA_SID,				TDX_DT_LONG,	TDX_DISP_RIGHT,  8,		"序号",					0,0,0,0,0,	},
	{	TDX_ID_CA_BINDTINE,			TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"绑定时间",				0,0,0,0,0,	},
	{	TDX_ID_CA_UMAC,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"MAC地址",				0,0,0,0,0,	},
	{	TDX_ID_CA_REMARK,			TDX_DT_STRING,	TDX_DISP_RIGHT,  128,	"计算机备注",			0,0,0,0,0,	},
	{	TDX_ID_CA_HARDINFO,			TDX_DT_STRING,	TDX_DISP_RIGHT,  128,	"隐藏硬件信息",			1,0,0,0,0,	},
};

const FIELDINFO tdxRZFieldInfo[]=
{
//	{	字段类型,					数据类型,		显示(对齐)方法,宽度,	字段说明,				其它标记,	},

	{	TDX_ID_RZ_STARTTIME,		TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"开始时间",				0,0,0,0,0,	},
	{	TDX_ID_RZ_ENDTIME,			TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"结束时间",				0,0,0,0,0,	},
	{	TDX_ID_RZ_TCTIME,			TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"交易中心耗时",			0,0,0,0,0,	},
	{	TDX_ID_RZ_APITIME,			TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"API耗时",				0,0,0,0,0,	},
	{	TDX_ID_RZ_QUEUETIME,		TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"排队耗时",				0,0,0,0,0,	},
	{	TDX_ID_RZ_AVGTCTIME,		TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"交易中心平均耗时",		0,0,0,0,0,	},
	{	TDX_ID_RZ_AVGAPITIME,		TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"API平均耗时",			0,0,0,0,0,	},
	{	TDX_ID_RZ_AVGQUEUETIME,		TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"排队平均耗时",			0,0,0,0,0,	},
	{	TDX_ID_RZ_FUNCID,			TDX_DT_STRING,	TDX_DISP_RIGHT,  50,	"调用功能ID",			0,0,0,0,0,	},
	{	TDX_ID_RZ_FLAGRESULT,		TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"处理结果标志",			0,0,0,0,0,	},
	{	TDX_ID_RZ_LOGID,			TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"日志记录编号",			0,0,0,0,0,	},
	{	TDX_ID_RZ_TCIP,				TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"交易中心IP",			0,0,0,0,0,	},
	{	TDX_ID_RZ_LOGTIME,			TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"日志记录时间",			0,0,0,0,0,	},
	{	TDX_ID_KHH,					TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"客户号",				0,0,0,0,0,	},
	{	TDX_ID_KHMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"客户名称",				0,0,0,0,0,	},
	{	TDX_ID_XT_BRANCHID,			TDX_DT_CHAR,	TDX_DISP_RIGHT,  10,	"营业部ID",				0,0,0,0,0,	},
	{	TDX_ID_XT_IPADDR,			TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"IP地址",				0,0,0,0,0,	},
	{	TDX_ID_XT_MACADDR,			TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"MAC地址",				0,0,0,0,0,	},
	{	TDX_ID_ZJZH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"资金帐号",				0,0,0,0,0,	},
	{	TDX_ID_RETINFO,				TDX_DT_STRING,	TDX_DISP_RIGHT,  80,	"返回信息",				0,0,0,0,0,	},
	{	TDX_ID_JYMM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"交易密码",				1,0,0,0,0,	},
	{	TDX_ID_XJYMM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"新交易密码",			1,0,0,0,0,	},
	{	TDX_ID_RZ_LEVER,			TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"用户级别",				0,0,0,0,0,	},
	{	TDX_ID_XT_STARTPOS,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"起始序号",				0,0,0,0,0,	},
	{	TDX_ID_KHQXDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"客户权限代码",			0,0,0,0,0,	},
	{	TDX_ID_KHQXMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"客户权限名称",			0,0,0,0,0,	},
	{	TDX_ID_RZ_PAGEINDEX,		TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"页码序号",				1,0,0,0,0,	},
	{	TDX_ID_CZBZ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"操作标志",				1,0,0,0,0,	},
	{	TDX_ID_RZ_FUNCNUM,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"调用数目",				0,0,0,0,0,	},
	{	TDX_ID_RZ_FUNCBL,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"调用比例",				0,0,0,0,0,	},
	{	TDX_ID_YWMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"功能名称",				0,0,0,0,0,	},
	{	TDX_ID_RZ_FUNCOKNUM,		TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"成功数目",				0,0,0,0,0,	},
	{	TDX_ID_RZ_FUNCFAILNUM,		TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"失败数目",				0,0,0,0,0,	},
	{	TDX_ID_RZ_ITEMNUM,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"记录条数",				1,0,0,0,0,	},
	{	TDX_ID_RZ_CXFLAG,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"查询类别",				1,0,0,0,0,	},
	{	TDX_ID_RZ_DAY,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"日期时间",				0,0,0,0,0,	},
};


//---------------------------------------------------------------------------
// Part.III 标准结构定义
//---------------------------------------------------------------------------

// 简化字典
const WORD tdxSimpleStructInfo[]=
{	// 登录协议
	TDX_ID_FUNC_REQ_ZHYCL,			// 账号预处理 94
	TDX_ID_FUNC_ANS_ZHYCL,
	TDX_ID_FUNC_REQ_DLYCL,			// 登录预处理 96
	TDX_ID_FUNC_ANS_DLYCL,
	TDX_ID_FUNC_REQ_JCKHJY,			// 集成客户校验 98
	TDX_ID_FUNC_ANS_JCKHJY,
	TDX_ID_FUNC_REQ_KHJY,			// 客户校验 100
	TDX_ID_FUNC_ANS_KHJY,
};

// 完整字典
const WORD tdxCommonStructInfo[]=
{
	// 委托功能部分
	TDX_ID_FUNC_REQ_KHJY,			// 客户校验 100
	TDX_ID_FUNC_ANS_KHJY,
	TDX_ID_FUNC_REQ_CXHQ,			// 查询行情 102
	TDX_ID_FUNC_ANS_CXHQ,
	TDX_ID_FUNC_REQ_ZJYE,			// 资金余额 104
	TDX_ID_FUNC_ANS_ZJYE,
	TDX_ID_FUNC_REQ_XGMM,			// 修改密码 106
	TDX_ID_FUNC_ANS_XGMM,
	TDX_ID_FUNC_REQ_XGZJMM,			// 修改资金密码 108
	TDX_ID_FUNC_ANS_XGZJMM,
	TDX_ID_FUNC_REQ_JSKMS,			// 计算可买(卖)数 110
	TDX_ID_FUNC_ANS_JSKMS,
	TDX_ID_FUNC_REQ_CACHE,			// 取缓存信息 112
	TDX_ID_FUNC_ANS_CACHE,
	TDX_ID_FUNC_REQ_XGGLZJZH,		// 修改关联资金帐号 114
	TDX_ID_FUNC_ANS_XGGLZJZH,
	TDX_ID_FUNC_REQ_KHZX,			// 客户注销 116
	TDX_ID_FUNC_ANS_KHZX,
	TDX_ID_FUNC_REQ_DYQXDZD,		// 订阅取消对帐单(邮寄) 118
	TDX_ID_FUNC_ANS_DYQXDZD,
	TDX_ID_FUNC_REQ_WTDJZJ,			// 委托冻结资金 120
	TDX_ID_FUNC_ANS_WTDJZJ,
	TDX_ID_FUNC_REQ_PRINTDZD,		// 打印对帐单 122
	TDX_ID_FUNC_ANS_PRINTDZD,
	TDX_ID_FUNC_REQ_PRINTHZDZD,		// 打印汇总对帐单 124
	TDX_ID_FUNC_ANS_PRINTHZDZD,
	TDX_ID_FUNC_REQ_PRINTJGD,		// 打印交割单(营业部独立交割单程序使用) 126
	TDX_ID_FUNC_ANS_PRINTJGD,
	TDX_ID_FUNC_REQ_XGTXMM,			// 修改通讯密码 128
	TDX_ID_FUNC_ANS_XGTXMM,
	TDX_ID_FUNC_REQ_ZHJD,			// 帐号解冻 130
	TDX_ID_FUNC_ANS_ZHJD,
	TDX_ID_FUNC_REQ_ZJGJ,			// 资金归集 132
	TDX_ID_FUNC_ANS_ZJGJ,
	TDX_ID_FUNC_REQ_ZJZHJZZ,		// 资金帐号间转帐 134
	TDX_ID_FUNC_ANS_ZJZHJZZ,
	TDX_ID_FUNC_REQ_TJWJJG,			// 提交问卷结果 136
	TDX_ID_FUNC_ANS_TJWJJG,
	TDX_ID_FUNC_REQ_HQWJNR,			// 获取问卷内容 138
	TDX_ID_FUNC_ANS_HQWJNR,
	TDX_ID_FUNC_REQ_HQZHZTBZ,		// 获取帐号状态标志 140
	TDX_ID_FUNC_ANS_HQZHZTBZ,
	TDX_ID_FUNC_REQ_CLCXMM,			// 处理查询密码 142
	TDX_ID_FUNC_ANS_CLCXMM,
	TDX_ID_FUNC_REQ_TSZC,			// 推送注册 144
	TDX_ID_FUNC_ANS_TSZC,
	TDX_ID_FUNC_REQ_TSZX,			// 推送注销 146
	TDX_ID_FUNC_ANS_TSZX,
	TDX_ID_FUNC_REQ_ZZHCX,			// 子帐号查询 148
	TDX_ID_FUNC_ANS_ZZHCX,
	TDX_ID_FUNC_REQ_CLRZXX,			// 处理认证信息 150
	TDX_ID_FUNC_ANS_CLRZXX,
	TDX_ID_FUNC_REQ_RZXXCX,			// 认证信息查询 152
	TDX_ID_FUNC_ANS_RZXXCX,
	TDX_ID_FUNC_REQ_KHJBXXCX,		// 客户基本信息查询 154
	TDX_ID_FUNC_ANS_KHJBXXCX,
	TDX_ID_FUNC_REQ_DZHTQY,			// 电子合同签约 156
	TDX_ID_FUNC_ANS_DZHTQY,
	TDX_ID_FUNC_REQ_DZHTQYCX,		// 电子合同签约查询 158
	TDX_ID_FUNC_ANS_DZHTQYCX,
	TDX_ID_FUNC_REQ_DZHTLBCX,		// 电子合同列表查询 160
	TDX_ID_FUNC_ANS_DZHTLBCX,
	TDX_ID_FUNC_REQ_DZHTXXCX,		// 电子合同信息查询 162
	TDX_ID_FUNC_ANS_DZHTXXCX,
	TDX_ID_FUNC_REQ_RZLSCX,			// 认证流水查询 164
	TDX_ID_FUNC_ANS_RZLSCX,
	TDX_ID_FUNC_REQ_KHYLXXCX,		// 客户预留信息查询 166
	TDX_ID_FUNC_ANS_KHYLXXCX,
	TDX_ID_FUNC_REQ_KHYLXXXG,		// 客户预留信息修改 168
	TDX_ID_FUNC_ANS_KHYLXXXG,
	TDX_ID_FUNC_REQ_KHCZQR,			// 客户操作确认 170
	TDX_ID_FUNC_ANS_KHCZQR,
	TDX_ID_FUNC_REQ_FYZDCX,			// 翻译字典查询 172
	TDX_ID_FUNC_ANS_FYZDCX,
	TDX_ID_FUNC_REQ_UPDATESESSION,	// 更新会话信息 174
	TDX_ID_FUNC_ANS_UPDATESESSION,
	TDX_ID_FUNC_REQ_WJLSCX,			// 问卷流水查询 176
	TDX_ID_FUNC_ANS_WJLSCX,
	TDX_ID_FUNC_REQ_SCINFO,			// 获取市场信息 178
	TDX_ID_FUNC_ANS_SCINFO,

	// 委托买卖类                                   
	TDX_ID_FUNC_REQ_WTCD,			// 委托撤单 200
	TDX_ID_FUNC_ANS_WTCD,
	TDX_ID_FUNC_REQ_PTGPWT,			// 普通股票委托 202
	TDX_ID_FUNC_ANS_PTGPWT,
	TDX_ID_FUNC_REQ_ZQZGHS,			// 债券转股回售 204
	TDX_ID_FUNC_ANS_ZQZGHS,
	TDX_ID_FUNC_REQ_XGDD,			// 修改订单 206
	TDX_ID_FUNC_ANS_XGDD,
	TDX_ID_FUNC_REQ_SGXG,			// 申购新股 208
	TDX_ID_FUNC_ANS_SGXG,
	TDX_ID_FUNC_REQ_XGSGXG,			// 新股申购修改 210
	TDX_ID_FUNC_ANS_XGSGXG,
	TDX_ID_FUNC_REQ_XGSGCD,			// 新股申购撤单 212
	TDX_ID_FUNC_ANS_XGSGCD,
	TDX_ID_FUNC_REQ_PLWT,			// 批量委托 214
	TDX_ID_FUNC_ANS_PLWT,
	TDX_ID_FUNC_REQ_PLCD,			// 批量撤单 216
	TDX_ID_FUNC_ANS_PLCD,
	TDX_ID_FUNC_REQ_XZDDJC,			// 新增订单检查 218
	TDX_ID_FUNC_ANS_XZDDJC,
	TDX_ID_FUNC_REQ_XGDDJC,			// 修改订单检查 220
	TDX_ID_FUNC_ANS_XGDDJC,

	// 闪电手
	TDX_ID_FUNC_REQ_SDSZJCX,		// 闪电手资金查询 250
	TDX_ID_FUNC_ANS_SDSZJCX,
	TDX_ID_FUNC_REQ_SDSGFCX,		// 闪电手股份查询 252
	TDX_ID_FUNC_ANS_SDSGFCX,
	TDX_ID_FUNC_REQ_SDSWTCX,		// 闪电手委托查询 254
	TDX_ID_FUNC_ANS_SDSWTCX,
	TDX_ID_FUNC_REQ_SDSCJCX,		// 闪电手成交查询 256
	TDX_ID_FUNC_ANS_SDSCJCX,
	TDX_ID_FUNC_REQ_SDSLSCX,		// 闪电手流水查询 258
	TDX_ID_FUNC_ANS_SDSLSCX,
	TDX_ID_FUNC_REQ_SDSXYZCCX,		// 闪电手信用资产查询 260
	TDX_ID_FUNC_ANS_SDSXYZCCX,
	TDX_ID_FUNC_REQ_SDSZQXXCX,		// 闪电手证券信息查询 262
	TDX_ID_FUNC_ANS_SDSZQXXCX,
	TDX_ID_FUNC_REQ_SDSKMSLCX,		// 闪电手可买(卖)数量查询 264
	TDX_ID_FUNC_ANS_SDSKMSLCX,

	// 委托买卖扩展(以及服务类型)
	TDX_ID_FUNC_REQ_FQZQ,			// 放弃中签 300
	TDX_ID_FUNC_ANS_FQZQ,
	TDX_ID_FUNC_REQ_FW_KHZLCX,		// (服务)客户资料查询 302
	TDX_ID_FUNC_ANS_FW_KHZLCX,
	TDX_ID_FUNC_REQ_FW_HQDTKL,		// (服务)获取动态口令 304
	TDX_ID_FUNC_ANS_FW_HQDTKL,
	TDX_ID_FUNC_REQ_FW_CPDGPZ,		// (服务)产品定购品种 306
	TDX_ID_FUNC_ANS_FW_CPDGPZ,
	TDX_ID_FUNC_REQ_FW_CPDGCX,		// (服务)产品定购查询 308
	TDX_ID_FUNC_ANS_FW_CPDGCX,
	TDX_ID_FUNC_REQ_FW_CPDGSZ,		// (服务)产品定购设置 310
	TDX_ID_FUNC_ANS_FW_CPDGSZ,
	TDX_ID_FUNC_REQ_FW_CPDGXG,		// (服务)产品定购修改 312
	TDX_ID_FUNC_ANS_FW_CPDGXG,
	TDX_ID_FUNC_REQ_FW_CPDGQX,		// (服务)产品定购取消 314
	TDX_ID_FUNC_ANS_FW_CPDGQX,
	TDX_ID_FUNC_REQ_FW_ZJLS,		// (服务)资金流水 316
	TDX_ID_FUNC_ANS_FW_ZJLS,
	TDX_ID_FUNC_REQ_FW_PLHQCX,		// (服务)批量行情查询 318
	TDX_ID_FUNC_ANS_FW_PLHQCX,
	TDX_ID_FUNC_REQ_FW_ZXLMCX,		// (服务)资讯栏目查询 320
	TDX_ID_FUNC_ANS_FW_ZXLMCX,
	TDX_ID_FUNC_REQ_FW_HQTSXX,		// (服务)获取提示信息 322
	TDX_ID_FUNC_ANS_FW_HQTSXX,
	TDX_ID_FUNC_REQ_FW_TPFACX,		// (服务)投票方案查询 324
	TDX_ID_FUNC_ANS_FW_TPFACX,
	TDX_ID_FUNC_REQ_FW_TPXXCX,		// (服务)投票信息查询 326
	TDX_ID_FUNC_ANS_FW_TPXXCX,
	TDX_ID_FUNC_REQ_FW_TPJGTJ,		// (服务)投票结果提交 328
	TDX_ID_FUNC_ANS_FW_TPJGTJ,
	TDX_ID_FUNC_REQ_FW_TPJGCX,		// (服务)投票结果查询 330
	TDX_ID_FUNC_ANS_FW_TPJGCX,
	TDX_ID_FUNC_REQ_FW_TPTJCX,		// (服务)投票统计查询 332
	TDX_ID_FUNC_ANS_FW_TPTJCX,
	TDX_ID_FUNC_REQ_FW_TLZHDMCX,	// (服务)套利组合代码查询 334
	TDX_ID_FUNC_ANS_FW_TLZHDMCX,
	TDX_ID_FUNC_REQ_FW_TLZHCFCX,	// (服务)套利组合成分查询 336
	TDX_ID_FUNC_ANS_FW_TLZHCFCX,
	TDX_ID_FUNC_REQ_FW_DDDLCZ,		// (服务)单点登录操作 338
	TDX_ID_FUNC_ANS_FW_DDDLCZ,
	TDX_ID_FUNC_REQ_FW_PLXJCX,		// (服务)批量现价查询 340
	TDX_ID_FUNC_ANS_FW_PLXJCX,
	TDX_ID_FUNC_REQ_FW_XXDY,		// (服务)信息订阅 342
	TDX_ID_FUNC_ANS_FW_XXDY,
	TDX_ID_FUNC_REQ_FW_KHKCL,		// (服务)客户卡处理 344
	TDX_ID_FUNC_ANS_FW_KHKCL,
	TDX_ID_FUNC_REQ_FW_SCPZXX,		// (服务)上传配置信息 346
	TDX_ID_FUNC_ANS_FW_SCPZXX,
	TDX_ID_FUNC_REQ_FW_XZPZXX,		// (服务)下载配置信息 348
	TDX_ID_FUNC_ANS_FW_XZPZXX,
	TDX_ID_FUNC_REQ_FW_PZXXZYCX,	// (服务)配置信息摘要查询 350
	TDX_ID_FUNC_ANS_FW_PZXXZYCX,
	TDX_ID_FUNC_REQ_FW_CLKHCS,		// (服务)处理客户参数 352
	TDX_ID_FUNC_ANS_FW_CLKHCS,
	TDX_ID_FUNC_REQ_FW_PDLBCX,		// (服务)配对列表查询 354
	TDX_ID_FUNC_ANS_FW_PDLBCX,
	TDX_ID_FUNC_REQ_FW_PDLSLR,		// (服务)配对流水录入 356
	TDX_ID_FUNC_ANS_FW_PDLSLR,
	TDX_ID_FUNC_REQ_FW_PDLSCX,		// (服务)配对流水查询 358
	TDX_ID_FUNC_ANS_FW_PDLSCX,
	TDX_ID_FUNC_REQ_FW_ZZYWSF,		// (服务)增值业务收费 360
	TDX_ID_FUNC_ANS_FW_ZZYWSF,

	// 推送功能(只有应答有效)
	TDX_ID_FUNC_REQ_PUSH_QZTC,		// (推送)强制退出 400 [推送功能,请求不使用]
	TDX_ID_FUNC_ANS_PUSH_QZTC,		// (推送)强制退出 401
	TDX_ID_FUNC_REQ_PUSH_XXTZ,		// (推送)消息通知 402 [推送功能,请求不使用]
	TDX_ID_FUNC_ANS_PUSH_XXTZ,		// (推送)消息通知 403
	TDX_ID_FUNC_REQ_PUSH_GGXX,		// (推送)公告消息 404 [推送功能,请求不使用]
	TDX_ID_FUNC_ANS_PUSH_GGXX,		// (推送)公告消息 405

	// 手机功能
	TDX_ID_FUNC_REQ_MOBILE_ZQCX,	// (手机)证券查询 500
	TDX_ID_FUNC_ANS_MOBILE_ZQCX,
	TDX_ID_FUNC_REQ_MOBILE_GFCX,	// (手机)股份查询 502
	TDX_ID_FUNC_ANS_MOBILE_GFCX,
	TDX_ID_FUNC_REQ_MOBILE_ZJCX,	// (手机)资金查询 504
	TDX_ID_FUNC_ANS_MOBILE_ZJCX,
	TDX_ID_FUNC_REQ_MOBILE_CDCX,	// (手机)撤单查询 506
	TDX_ID_FUNC_ANS_MOBILE_CDCX,
	TDX_ID_FUNC_REQ_MOBILE_WTCX,	// (手机)委托查询 508
	TDX_ID_FUNC_ANS_MOBILE_WTCX,
	TDX_ID_FUNC_REQ_MOBILE_CJCX,	// (手机)成交查询 510
	TDX_ID_FUNC_ANS_MOBILE_CJCX,
	TDX_ID_FUNC_REQ_MOBILE_ZZCX,	// (手机)转账查询 512
	TDX_ID_FUNC_ANS_MOBILE_ZZCX,
	TDX_ID_FUNC_REQ_MOBILE_LSCX,	// (手机)流水查询 514
	TDX_ID_FUNC_ANS_MOBILE_LSCX,
	TDX_ID_FUNC_REQ_MOBILE_JGCX,	// (手机)交割查询 516
	TDX_ID_FUNC_ANS_MOBILE_JGCX,
	TDX_ID_FUNC_REQ_MOBILE_DZCX,	// (手机)对账查询 518
	TDX_ID_FUNC_ANS_MOBILE_DZCX,
	TDX_ID_FUNC_REQ_MOBILE_YXSBHQCX,// (手机)意向申报行情查询 520
	TDX_ID_FUNC_ANS_MOBILE_YXSBHQCX,
	TDX_ID_FUNC_REQ_MOBILE_LSWTCX,	// (手机)历史委托查询 522
	TDX_ID_FUNC_ANS_MOBILE_LSWTCX,
	TDX_ID_FUNC_REQ_MOBILE_LSCJCX,	// (手机)历史成交查询 524
	TDX_ID_FUNC_ANS_MOBILE_LSCJCX,
	TDX_ID_FUNC_REQ_MOBILE_PHZQCX,	// (手机)配号中签查询 526
	TDX_ID_FUNC_ANS_MOBILE_PHZQCX,
	TDX_ID_FUNC_REQ_MOBILE_RZLSCX,	// (手机)认证流水查询 528
	TDX_ID_FUNC_ANS_MOBILE_RZLSCX,
	TDX_ID_FUNC_REQ_MOBILE_JJCDCX,	// (手机)基金撤单查询 530
	TDX_ID_FUNC_ANS_MOBILE_JJCDCX,
	TDX_ID_FUNC_REQ_MOBILE_JJDRWTCX,// (手机)基金当日委托查询 532
	TDX_ID_FUNC_ANS_MOBILE_JJDRWTCX,
	TDX_ID_FUNC_REQ_MOBILE_JJLSWTCX,// (手机)基金历史委托查询 534
	TDX_ID_FUNC_ANS_MOBILE_JJLSWTCX,
	TDX_ID_FUNC_REQ_MOBILE_JJDRCJCX,// (手机)基金当日成交查询 536
	TDX_ID_FUNC_ANS_MOBILE_JJDRCJCX,
	TDX_ID_FUNC_REQ_MOBILE_JJLSCJCX,// (手机)基金历史成交查询 538
	TDX_ID_FUNC_ANS_MOBILE_JJLSCJCX,
	TDX_ID_FUNC_REQ_MOBILE_JJZHCX,	// (手机)基金账号查询 540
	TDX_ID_FUNC_ANS_MOBILE_JJZHCX,
	TDX_ID_FUNC_REQ_MOBILE_JJGSCX,	// (手机)基金公司查询 542
	TDX_ID_FUNC_ANS_MOBILE_JJGSCX,
	TDX_ID_FUNC_REQ_MOBILE_JJDMCX,	// (手机)基金代码查询 544
	TDX_ID_FUNC_ANS_MOBILE_JJDMCX,
	TDX_ID_FUNC_REQ_MOBILE_JJFECX,	// (手机)基金份额查询 546
	TDX_ID_FUNC_ANS_MOBILE_JJFECX,
	TDX_ID_FUNC_REQ_MOBILE_JJDZCX,	// (手机)基金对账查询 548
	TDX_ID_FUNC_ANS_MOBILE_JJDZCX,
	TDX_ID_FUNC_REQ_MOBILE_JJJGCX,	// (手机)基金交割查询 550
	TDX_ID_FUNC_ANS_MOBILE_JJJGCX,
	TDX_ID_FUNC_REQ_MOBILE_JJFJYWTCX,// (手机)基金非交易委托查询 552
	TDX_ID_FUNC_ANS_MOBILE_JJFJYWTCX,

	TDX_ID_FUNC_REQ_MOBILE_QHHYCX,	// (手机)期货合约查询 560
	TDX_ID_FUNC_ANS_MOBILE_QHHYCX,
	TDX_ID_FUNC_REQ_MOBILE_QHZHHYCX,// (手机)期货组合合约查询 562
	TDX_ID_FUNC_ANS_MOBILE_QHZHHYCX,
	TDX_ID_FUNC_REQ_MOBILE_QHZHCCCX,// (手机)期货组合持仓查询 564
	TDX_ID_FUNC_ANS_MOBILE_QHZHCCCX,
	TDX_ID_FUNC_REQ_MOBILE_QHZHWTCX,// (手机)期货组合委托查询 566
	TDX_ID_FUNC_ANS_MOBILE_QHZHWTCX,
	TDX_ID_FUNC_REQ_MOBILE_QHZHCLCX,// (手机)期货组合策略查询 568
	TDX_ID_FUNC_ANS_MOBILE_QHZHCLCX,
	TDX_ID_FUNC_REQ_MOBILE_GFHZCX,	// (手机)股份汇总查询 570
	TDX_ID_FUNC_ANS_MOBILE_GFHZCX,
	TDX_ID_FUNC_REQ_MOBILE_WTHZCX,	// (手机)委托汇总查询 572
	TDX_ID_FUNC_ANS_MOBILE_WTHZCX,
	TDX_ID_FUNC_REQ_MOBILE_CJHZCX,	// (手机)成交汇总查询 574
	TDX_ID_FUNC_ANS_MOBILE_CJHZCX,
	TDX_ID_FUNC_REQ_MOBILE_CJMXCX,	// (手机)成交明细查询 576
	TDX_ID_FUNC_ANS_MOBILE_CJMXCX,

	TDX_ID_FUNC_REQ_MOBILE_XYRZMRPTCX,	// (手机)信用融资买入配套查询 600
	TDX_ID_FUNC_ANS_MOBILE_XYRZMRPTCX,
	TDX_ID_FUNC_REQ_MOBILE_XYRQMCPTCX,	// (手机)信用融券卖出配套查询 602
	TDX_ID_FUNC_ANS_MOBILE_XYRQMCPTCX,
	TDX_ID_FUNC_REQ_MOBILE_XYMCHKPTCX,	// (手机)信用卖出还款配套查询 604
	TDX_ID_FUNC_ANS_MOBILE_XYMCHKPTCX,
	TDX_ID_FUNC_REQ_MOBILE_XYMRHQPTCX,	// (手机)信用买入还券配套查询 606
	TDX_ID_FUNC_ANS_MOBILE_XYMRHQPTCX,
	TDX_ID_FUNC_REQ_MOBILE_XYXJHKPTCX,	// (手机)信用现金还款配套查询 608
	TDX_ID_FUNC_ANS_MOBILE_XYXJHKPTCX,
	TDX_ID_FUNC_REQ_MOBILE_XYXQHQPTCX,	// (手机)信用现券还券配套查询 610
	TDX_ID_FUNC_ANS_MOBILE_XYXQHQPTCX,
	TDX_ID_FUNC_REQ_MOBILE_XYYQHZPTCX,	// (手机)信用余券划转配套查询 612
	TDX_ID_FUNC_ANS_MOBILE_XYYQHZPTCX,
	TDX_ID_FUNC_REQ_MOBILE_XYDBHZPTCX,	// (手机)信用担保划转配套查询 614
	TDX_ID_FUNC_ANS_MOBILE_XYDBHZPTCX,
	TDX_ID_FUNC_REQ_MOBILE_XYDBZRPTCX,	// (手机)信用担保转入配套查询 616
	TDX_ID_FUNC_ANS_MOBILE_XYDBZRPTCX,
	TDX_ID_FUNC_REQ_MOBILE_XYDBZCPTCX,	// (手机)信用担保转出配套查询 618
	TDX_ID_FUNC_ANS_MOBILE_XYDBZCPTCX,
	TDX_ID_FUNC_REQ_MOBILE_XYZCXXCX,	// (手机)信用资产信息查询 620
	TDX_ID_FUNC_ANS_MOBILE_XYZCXXCX,
	TDX_ID_FUNC_REQ_MOBILE_XYGFXXCX,	// (手机)信用股份信息查询 622
	TDX_ID_FUNC_ANS_MOBILE_XYGFXXCX,
	TDX_ID_FUNC_REQ_MOBILE_XYBDZQCX,	// (手机)信用标的证券查询 624
	TDX_ID_FUNC_ANS_MOBILE_XYBDZQCX,
	TDX_ID_FUNC_REQ_MOBILE_XYZJHZCX,	// (手机)信用直接划转查询 626
	TDX_ID_FUNC_ANS_MOBILE_XYZJHZCX,
	TDX_ID_FUNC_REQ_MOBILE_XYLXFYCX,	// (手机)信用利息费用查询 628
	TDX_ID_FUNC_ANS_MOBILE_XYLXFYCX,
	TDX_ID_FUNC_REQ_MOBILE_XYWPHYCX,	// (手机)信用未平合约查询 630
	TDX_ID_FUNC_ANS_MOBILE_XYWPHYCX,
	TDX_ID_FUNC_REQ_MOBILE_XYYPHYCX,	// (手机)信用已平合约查询 632
	TDX_ID_FUNC_ANS_MOBILE_XYYPHYCX,
	TDX_ID_FUNC_REQ_MOBILE_XYDRHYCX,	// (手机)信用当日合约查询 634
	TDX_ID_FUNC_ANS_MOBILE_XYDRHYCX,
	TDX_ID_FUNC_REQ_MOBILE_XYRZHYCX,	// (手机)信用融资合约查询 636
	TDX_ID_FUNC_ANS_MOBILE_XYRZHYCX,
	TDX_ID_FUNC_REQ_MOBILE_XYRQHYCX,	// (手机)信用融券合约查询 638
	TDX_ID_FUNC_ANS_MOBILE_XYRQHYCX,
	TDX_ID_FUNC_REQ_MOBILE_XYZJFZCX,	// (手机)信用资金负债查询 640
	TDX_ID_FUNC_ANS_MOBILE_XYZJFZCX,
	TDX_ID_FUNC_REQ_MOBILE_XYGFFZCX,	// (手机)信用股份负债查询 642
	TDX_ID_FUNC_ANS_MOBILE_XYGFFZCX,
	TDX_ID_FUNC_REQ_MOBILE_XYJYDBPZQCX,	// (手机)信用交易担保品证券查询 644
	TDX_ID_FUNC_ANS_MOBILE_XYJYDBPZQCX,
	TDX_ID_FUNC_REQ_MOBILE_XYJYFJYHZCX,	// (手机)信用交易非交易化转查询 646
	TDX_ID_FUNC_ANS_MOBILE_XYJYFJYHZCX,	
	TDX_ID_FUNC_REQ_MOBILE_XYJYFZLSCX,	// (手机)信用交易负债流水查询 648
	TDX_ID_FUNC_ANS_MOBILE_XYJYFZLSCX,

	TDX_ID_FUNC_REQ_MOBILE_ETFWTCX,		// (手机)ETF委托查询 700
	TDX_ID_FUNC_ANS_MOBILE_ETFWTCX,
	TDX_ID_FUNC_REQ_MOBILE_ETFCJCX,		// (手机)ETF成交查询 702
	TDX_ID_FUNC_ANS_MOBILE_ETFCJCX,

	TDX_ID_FUNC_REQ_MOBILE_LCCPFECX,	// (手机)理财产品份额查询 750
	TDX_ID_FUNC_ANS_MOBILE_LCCPFECX,
	TDX_ID_FUNC_REQ_MOBILE_LCCPWTCX,	// (手机)理财产品委托查询 752
	TDX_ID_FUNC_ANS_MOBILE_LCCPWTCX,
	TDX_ID_FUNC_REQ_MOBILE_LCCPCJCX,	// (手机)理财产品成交查询 754
	TDX_ID_FUNC_ANS_MOBILE_LCCPCJCX,
	TDX_ID_FUNC_REQ_MOBILE_LCCPDMCX,	// (手机)理财产品代码查询 756
	TDX_ID_FUNC_ANS_MOBILE_LCCPDMCX,
	TDX_ID_FUNC_REQ_MOBILE_LCCPDQDESGCX,// (手机)理财产品定期定额申购查询 758
	TDX_ID_FUNC_ANS_MOBILE_LCCPDQDESGCX,

	TDX_ID_FUNC_REQ_MOBILE_YHLCCPDMCX,	// (手机)银行理财产品代码查询 790
	TDX_ID_FUNC_ANS_MOBILE_YHLCCPDMCX,	
	TDX_ID_FUNC_REQ_MOBILE_YHLCCPFECX,	// (手机)银行理财产品份额查询 792
	TDX_ID_FUNC_ANS_MOBILE_YHLCCPFECX,	
	TDX_ID_FUNC_REQ_MOBILE_YHLCCPWTCX,	// (手机)银行理财产品委托查询 794
	TDX_ID_FUNC_ANS_MOBILE_YHLCCPWTCX,	
	TDX_ID_FUNC_REQ_MOBILE_YHLCCPCJCX,	// (手机)银行理财产品成交查询 796
	TDX_ID_FUNC_ANS_MOBILE_YHLCCPCJCX,

	// 银证转帐类
	TDX_ID_FUNC_REQ_YZZZ,			// 银证转帐 900
	TDX_ID_FUNC_ANS_YZZZ,
	TDX_ID_FUNC_REQ_YHLS,			// 银行流水 902
	TDX_ID_FUNC_ANS_YHLS,
	TDX_ID_FUNC_REQ_YHYE,			// 银行余额 904
	TDX_ID_FUNC_ANS_YHYE,
	TDX_ID_FUNC_REQ_XGYHMM,			// 修改银行密码 906
	TDX_ID_FUNC_ANS_XGYHMM,
	TDX_ID_FUNC_REQ_YHXX,			// 查询银行信息 908
	TDX_ID_FUNC_ANS_YHXX,
	// 三方存管
	TDX_ID_FUNC_REQ_SFCGZZ,			// 三方存管转帐 910
	TDX_ID_FUNC_ANS_SFCGZZ,
	TDX_ID_FUNC_REQ_SFZZCX,			// 三方转帐查询 912
	TDX_ID_FUNC_ANS_SFZZCX,
	TDX_ID_FUNC_REQ_SFYECX,			// 三方余额查询 914
	TDX_ID_FUNC_ANS_SFYECX,
	// 转帐扩展(包括港股等其他市场及扩展业务)
	TDX_ID_FUNC_REQ_ZZXG,			// 转帐修改 916
	TDX_ID_FUNC_ANS_ZZXG,
	TDX_ID_FUNC_REQ_ZZQX,			// 转帐取消 918
	TDX_ID_FUNC_ANS_ZZQX,
	TDX_ID_FUNC_REQ_KQZJCX,			// 可取资金查询 920
	TDX_ID_FUNC_ANS_KQZJCX,
	TDX_ID_FUNC_REQ_ZZYHCX,			// 转帐银行查询 922
	TDX_ID_FUNC_ANS_ZZYHCX,
	TDX_ID_FUNC_REQ_YHZHJZZ,		// 银行账户间转帐 924
	TDX_ID_FUNC_ANS_YHZHJZZ,
	TDX_ID_FUNC_REQ_YDZJZZ,			// 远端资金转账 926
	TDX_ID_FUNC_ANS_YDZJZZ,
	TDX_ID_FUNC_REQ_YDZZCX,			// 远端转账查询 928
	TDX_ID_FUNC_ANS_YDZZCX,
	TDX_ID_FUNC_REQ_YDZJCX,			// 远端资金查询 930
	TDX_ID_FUNC_ANS_YDZJCX,
	TDX_ID_FUNC_REQ_YDKZCX,			// 远端可转查询 932
	TDX_ID_FUNC_ANS_YDKZCX,
	TDX_ID_FUNC_REQ_YHKLBCX,		// 银行卡列表查询 934
	TDX_ID_FUNC_ANS_YHKLBCX,
	TDX_ID_FUNC_REQ_YHKXXCX,		// 银行卡信息查询 936
	TDX_ID_FUNC_ANS_YHKXXCX,
	TDX_ID_FUNC_REQ_YHKXXXG,		// 银行卡信息修改 938
	TDX_ID_FUNC_ANS_YHKXXXG,
	TDX_ID_FUNC_REQ_YHKBGCZ,		// 银行卡变更操作 940
	TDX_ID_FUNC_ANS_YHKBGCZ,
	TDX_ID_FUNC_REQ_YHKFLCX,		// 银行卡费率查询 942
	TDX_ID_FUNC_ANS_YHKFLCX,
	TDX_ID_FUNC_REQ_ZHJZZLSCX,		// 账号间转账流水查询 944
	TDX_ID_FUNC_ANS_ZHJZZLSCX,
	TDX_ID_FUNC_REQ_ZHJZZDRLSCX,	// 账号间转账当日流水查询 946
	TDX_ID_FUNC_ANS_ZHJZZDRLSCX,
	TDX_ID_FUNC_REQ_YHYELSCX,		// 银行余额流水查询 948
	TDX_ID_FUNC_ANS_YHYELSCX,
	TDX_ID_FUNC_REQ_JHZZLSCX,		// 计划转账流水查询 950
	TDX_ID_FUNC_ANS_JHZZLSCX,
	TDX_ID_FUNC_REQ_DCGYHLSCX,		// 多存管银行流水查询 952
	TDX_ID_FUNC_ANS_DCGYHLSCX,
	TDX_ID_FUNC_REQ_DCGZHTB,		// 多存管账号同步 954
	TDX_ID_FUNC_ANS_DCGZHTB,
	TDX_ID_FUNC_REQ_HHYWCZ,			// 换汇业务操作 990
	TDX_ID_FUNC_ANS_HHYWCZ,
	TDX_ID_FUNC_REQ_HHYHCX,			// 换汇银行查询 992
	TDX_ID_FUNC_ANS_HHYHCX,
	TDX_ID_FUNC_REQ_HHHLCX,			// 换汇汇率查询 994
	TDX_ID_FUNC_ANS_HHHLCX,
	TDX_ID_FUNC_REQ_HHWTCX,			// 换汇委托查询 996
	TDX_ID_FUNC_ANS_HHWTCX,

	// 查询类
	TDX_ID_FUNC_REQ_CDCX,			// 可撤单查询 1100
	TDX_ID_FUNC_ANS_CDCX,
	TDX_ID_FUNC_REQ_DRWTCX,			// 当日委托查询 1102
	TDX_ID_FUNC_ANS_DRWTCX,
	TDX_ID_FUNC_REQ_LSWTCX,			// 历史委托查询 1104
	TDX_ID_FUNC_ANS_LSWTCX,
	TDX_ID_FUNC_REQ_WTCX,			// 委托查询(含当日和历史委托) 1106
	TDX_ID_FUNC_ANS_WTCX,
	TDX_ID_FUNC_REQ_DRCJCX,			// 当日成交查询 1108
	TDX_ID_FUNC_ANS_DRCJCX,
	TDX_ID_FUNC_REQ_LSCJCX,			// 历史成交查询 1110
	TDX_ID_FUNC_ANS_LSCJCX,
	TDX_ID_FUNC_REQ_CJCX,			// 成交查询(含当日和历史成交) 1112
	TDX_ID_FUNC_ANS_CJCX,
	TDX_ID_FUNC_REQ_GFCX,			// 股份查询 1114
	TDX_ID_FUNC_ANS_GFCX,
	TDX_ID_FUNC_REQ_XGPH,			// 新股配号 1116
	TDX_ID_FUNC_ANS_XGPH,
	TDX_ID_FUNC_REQ_ZJLS,			// 资金流水 1118
	TDX_ID_FUNC_ANS_ZJLS,
	TDX_ID_FUNC_REQ_JGD,			// 交割单 1120
	TDX_ID_FUNC_ANS_JGD,
	TDX_ID_FUNC_REQ_GDCX,			// 股东查询 1122
	TDX_ID_FUNC_ANS_GDCX,
	TDX_ID_FUNC_REQ_ZQXX,			// 取证券信息 1124
	TDX_ID_FUNC_ANS_ZQXX,
	TDX_ID_FUNC_REQ_ZQCX,			// 中签查询 1126
	TDX_ID_FUNC_ANS_ZQCX,
	TDX_ID_FUNC_REQ_XGCBJ,			// 修改成本价 1128
	TDX_ID_FUNC_ANS_XGCBJ,
	TDX_ID_FUNC_REQ_XGLXFS,			// (查询)修改联系方式 1130
	TDX_ID_FUNC_ANS_XGLXFS,
	TDX_ID_FUNC_REQ_DZD,			// 对帐单 1132
	TDX_ID_FUNC_ANS_DZD,
	TDX_ID_FUNC_REQ_PSQYCX,			// 配售权益查询 1134
	TDX_ID_FUNC_ANS_PSQYCX,
	TDX_ID_FUNC_REQ_QZXXCX,			// 权证信息查询 1136
	TDX_ID_FUNC_ANS_QZXXCX,
	TDX_ID_FUNC_REQ_CJHZCX,			// 成交汇总查询 1138
	TDX_ID_FUNC_ANS_CJHZCX,
	TDX_ID_FUNC_REQ_GFHZCX,			// 股份汇总查询 1140
	TDX_ID_FUNC_ANS_GFHZCX,
	TDX_ID_FUNC_REQ_KTXY,			// 权证开通取消 1142
	TDX_ID_FUNC_ANS_KTXY,
	TDX_ID_FUNC_REQ_YWTCX,			// 欲委托查询 1144
	TDX_ID_FUNC_ANS_YWTCX,
	TDX_ID_FUNC_REQ_QDXY,			// 签订协议 1146
	TDX_ID_FUNC_ANS_QDXY,
	TDX_ID_FUNC_REQ_ZTZJCX,			// 在途资金查询(平安证券) 1148
	TDX_ID_FUNC_ANS_ZTZJCX,
	TDX_ID_FUNC_REQ_JGXZZ,			// 金股信转帐 1150
	TDX_ID_FUNC_ANS_JGXZZ,
	TDX_ID_FUNC_REQ_FZDM,			// 东莞获取网点代码 1152
	TDX_ID_FUNC_ANS_FZDM,
	TDX_ID_FUNC_REQ_HQXYNR,			// 获取协议内容 1154
	TDX_ID_FUNC_ANS_HQXYNR,
	TDX_ID_FUNC_REQ_HQIPOLB,		// 获取IPO列表 1156
	TDX_ID_FUNC_ANS_HQIPOLB,
	TDX_ID_FUNC_REQ_IPOXXCX,		// IPO信息查询 1158
	TDX_ID_FUNC_ANS_IPOXXCX,
	TDX_ID_FUNC_REQ_YYCX,			// 预受要约查询 1160
	TDX_ID_FUNC_ANS_YYCX,
	TDX_ID_FUNC_REQ_YYCD,			// 预受要约撤单 1162
	TDX_ID_FUNC_ANS_YYCD,
	TDX_ID_FUNC_REQ_YYSB,			// 预受要约申报 1164
	TDX_ID_FUNC_ANS_YYSB,
	TDX_ID_FUNC_REQ_ZYHG,			// 质押回购 1166
	TDX_ID_FUNC_ANS_ZYHG,
	TDX_ID_FUNC_REQ_WJSCJMXCX,		// 未交收成交明细查询 1168
	TDX_ID_FUNC_ANS_WJSCJMXCX,
	TDX_ID_FUNC_REQ_CGYYCQ,			// 存管预约存取业务 1170
	TDX_ID_FUNC_ANS_CGYYCQ,
	TDX_ID_FUNC_REQ_CGYYCQCX,		// 存管预约存取业务查询 1172
	TDX_ID_FUNC_ANS_CGYYCQCX,
	TDX_ID_FUNC_REQ_WTHZCX,			// 委托汇总查询 1174
	TDX_ID_FUNC_ANS_WTHZCX,
	TDX_ID_FUNC_REQ_ZJMXCX,			// 资金明细查询 1176
	TDX_ID_FUNC_ANS_ZJMXCX,
	TDX_ID_FUNC_REQ_CXXZCGYH,		// 查询选择存管银行 1178
	TDX_ID_FUNC_ANS_CXXZCGYH,
	TDX_ID_FUNC_REQ_XZCGYH,			// 选择存管银行 1180
	TDX_ID_FUNC_ANS_XZCGYH,
	TDX_ID_FUNC_REQ_CXXYXX,			// 查询协议信息 1182
	TDX_ID_FUNC_ANS_CXXYXX,
	TDX_ID_FUNC_REQ_LSCJHZCX,		// 历史成交汇总查询 1184
	TDX_ID_FUNC_ANS_LSCJHZCX,
	TDX_ID_FUNC_REQ_CJMXCX,			// 成交明细查询 1186
	TDX_ID_FUNC_ANS_CJMXCX,
	TDX_ID_FUNC_REQ_WTCXMX,			// 委托查询明细 1188
	TDX_ID_FUNC_ANS_WTCXMX,
	TDX_ID_FUNC_REQ_CJCXMX,			// 成交查询明细 1190
	TDX_ID_FUNC_ANS_CJCXMX,
	TDX_ID_FUNC_REQ_YXSBHQCX,		// 意向申报行情查询 1192
	TDX_ID_FUNC_ANS_YXSBHQCX,
	TDX_ID_FUNC_REQ_PLWTCX,			// 批量委托查询 1194
	TDX_ID_FUNC_ANS_PLWTCX,
	TDX_ID_FUNC_REQ_LOFHBXGDMCX,	// LOF合并相关代码查询 1196
	TDX_ID_FUNC_ANS_LOFHBXGDMCX,
	TDX_ID_FUNC_REQ_LOFFCXGDMCX,	// LOF分拆相关代码查询 1198
	TDX_ID_FUNC_ANS_LOFFCXGDMCX,
	TDX_ID_FUNC_REQ_LOFPHYWDRWTCX,	// LOF盘后业务当日委托查询 1200
	TDX_ID_FUNC_ANS_LOFPHYWDRWTCX,
	TDX_ID_FUNC_REQ_LOFPHYWLSWTCX,	// LOF盘后业务历史委托查询 1202
	TDX_ID_FUNC_ANS_LOFPHYWLSWTCX,
	TDX_ID_FUNC_REQ_LOFPHYWDRCJCX,	// LOF盘后业务当日成交查询 1204
	TDX_ID_FUNC_ANS_LOFPHYWDRCJCX,
	TDX_ID_FUNC_REQ_LOFPHYWLSCJCX,	// LOF盘后业务历史成交查询 1206
	TDX_ID_FUNC_ANS_LOFPHYWLSCJCX,
	TDX_ID_FUNC_REQ_LOFPHYWCDCX,	// LOF盘后业务撤单查询 1208
	TDX_ID_FUNC_ANS_LOFPHYWCDCX,
	TDX_ID_FUNC_REQ_FSGFCX,			// 附属股份查询 1210
	TDX_ID_FUNC_ANS_FSGFCX,
	TDX_ID_FUNC_REQ_ZQFSXXCX,		// 证券附属信息查询 1212
	TDX_ID_FUNC_ANS_ZQFSXXCX,
	TDX_ID_FUNC_REQ_BJZRCDCX,		// 报价转让撤单查询 1214
	TDX_ID_FUNC_ANS_BJZRCDCX,
	TDX_ID_FUNC_REQ_BJZRWTCX,		// 报价转让委托查询 1216
	TDX_ID_FUNC_ANS_BJZRWTCX,
	TDX_ID_FUNC_REQ_BJZRCJCX,		// 报价转让成交查询 1218
	TDX_ID_FUNC_ANS_BJZRCJCX,
	TDX_ID_FUNC_REQ_DTGFCX,			// 动态股份查询 1220
	TDX_ID_FUNC_ANS_DTGFCX,
	TDX_ID_FUNC_REQ_ZQZYKCX,		// 债券质押库查询 1222
	TDX_ID_FUNC_ANS_ZQZYKCX,
	TDX_ID_FUNC_REQ_DCGZJMXCX,		// 多存管资金明细查询 1224
	TDX_ID_FUNC_ANS_DCGZJMXCX,
	TDX_ID_FUNC_REQ_LSCCCX,			// 历史持仓查询 1226
	TDX_ID_FUNC_ANS_LSCCCX,
	TDX_ID_FUNC_REQ_GFMXCX,			// 股份明细查询 1228
	TDX_ID_FUNC_ANS_GFMXCX,
	TDX_ID_FUNC_REQ_GFCX_SECOND,	// 股份查询(2nd版) 1230
	TDX_ID_FUNC_ANS_GFCX_SECOND,
	TDX_ID_FUNC_REQ_GFCX_THIRD,		// 股份查询(3rd版) 1232
	TDX_ID_FUNC_ANS_GFCX_THIRD,
	TDX_ID_FUNC_REQ_ZQHGHYCX,		// 债券回购合约查询 1234
	TDX_ID_FUNC_ANS_ZQHGHYCX,
	TDX_ID_FUNC_REQ_KHDZXXCX,		// 客户对账信息查询 1236
	TDX_ID_FUNC_ANS_KHDZXXCX,
	TDX_ID_FUNC_REQ_ZHXYHQCX,		// 综合协议行情查询 1238
	TDX_ID_FUNC_ANS_ZHXYHQCX,
	TDX_ID_FUNC_REQ_BZQHZCX,		// 标准券汇总查询 1240
	TDX_ID_FUNC_ANS_BZQHZCX,
	TDX_ID_FUNC_REQ_GTZQHQCX,		// 柜台债券行情查询 1242
	TDX_ID_FUNC_ANS_GTZQHQCX,
	TDX_ID_FUNC_REQ_RZXQHYCX,		// 融资行权合约查询 1244
	TDX_ID_FUNC_ANS_RZXQHYCX,
	TDX_ID_FUNC_REQ_RZXQKHXXCX,		// 融资行权客户信息查询 1246
	TDX_ID_FUNC_ANS_RZXQKHXXCX,
	TDX_ID_FUNC_REQ_ZQHGLSCX,		// 债券回购历史查询 1248
	TDX_ID_FUNC_ANS_ZQHGLSCX,
	TDX_ID_FUNC_REQ_QQDMCX,			// 期权代码查询 1250
	TDX_ID_FUNC_ANS_QQDMCX,
	TDX_ID_FUNC_REQ_QQCCCX,			// 期权持仓查询 1252
	TDX_ID_FUNC_ANS_QQCCCX,
	TDX_ID_FUNC_REQ_QQSDSCX,		// 期权所得税查询 1254
	TDX_ID_FUNC_ANS_QQSDSCX,
	TDX_ID_FUNC_REQ_QQDRWTCX,		// 期权当日委托查询 1256
	TDX_ID_FUNC_ANS_QQDRWTCX,
	TDX_ID_FUNC_REQ_QQLSWTCX,		// 期权历史委托查询 1258
	TDX_ID_FUNC_ANS_QQLSWTCX,

	// 期货交易类
	TDX_ID_FUNC_REQ_QHWT,			// 期货委托 1500
	TDX_ID_FUNC_ANS_QHWT,
	TDX_ID_FUNC_REQ_CXQHCC,			// 查询期货持仓 1502
	TDX_ID_FUNC_ANS_CXQHCC,
	TDX_ID_FUNC_REQ_CXHYXX,			// 查询期货合约信息 1504
	TDX_ID_FUNC_ANS_CXHYXX,
	TDX_ID_FUNC_REQ_CXKJYHY,		// 查询可交易合约 1506
	TDX_ID_FUNC_ANS_CXKJYHY,
	TDX_ID_FUNC_REQ_DRZJLS,			// 当日资金流水 1508
	TDX_ID_FUNC_ANS_DRZJLS,
	TDX_ID_FUNC_REQ_QHWTZTCX,		// 期货委托状态查询 1510
	TDX_ID_FUNC_ANS_QHWTZTCX,
	TDX_ID_FUNC_REQ_QHWTHB,			// 期货委托回报 1512 [推送功能,请求不使用]
	TDX_ID_FUNC_ANS_QHWTHB,			// 期货委托回报 1513
	TDX_ID_FUNC_REQ_QHCDHB,			// 期货撤单回报 1514 [推送功能,请求不使用]
	TDX_ID_FUNC_ANS_QHCDHB,			// 期货撤单回报 1515
	TDX_ID_FUNC_REQ_QHCJHB,			// 期货成交回报 1516 [推送功能,请求不使用]
	TDX_ID_FUNC_ANS_QHCJHB,			// 期货成交回报 1517
	TDX_ID_FUNC_REQ_QHXXFB,			// 期货信息发布 1518 [推送功能,请求不使用]
	TDX_ID_FUNC_ANS_QHXXFB,			// 期货信息发布 1519
	TDX_ID_FUNC_REQ_QHJYSZTGB,		// 期货交易所状态改变 1520 [推送功能,请求不使用]
	TDX_ID_FUNC_ANS_QHJYSZTGB,		// 期货交易所状态改变 1521
	TDX_ID_FUNC_REQ_QHZHHYBG,		// 期货组合合约变更 1522 [推送功能,请求不使用]
	TDX_ID_FUNC_ANS_QHZHHYBG,		// 期货组合合约变更 1523
	TDX_ID_FUNC_REQ_QHZHWTHB,		// 期货组合委托回报 1524 [推送功能,请求不使用]
	TDX_ID_FUNC_ANS_QHZHWTHB,		// 期货组合委托回报 1525
	TDX_ID_FUNC_REQ_QHZHCDHB,		// 期货组合撤单回报 1526 [推送功能,请求不使用]
	TDX_ID_FUNC_ANS_QHZHCDHB,		// 期货组合撤单回报 1527
	TDX_ID_FUNC_REQ_QHDDLXCX,		// 期货订单类型查询 1528
	TDX_ID_FUNC_ANS_QHDDLXCX,
	TDX_ID_FUNC_REQ_QHZHWT,			// 期货组合委托 1530
	TDX_ID_FUNC_ANS_QHZHWT,
	TDX_ID_FUNC_REQ_QHZHCD,			// 期货组合撤单 1532
	TDX_ID_FUNC_ANS_QHZHCD,
	TDX_ID_FUNC_REQ_QHZHHYCX,		// 期货组合合约查询 1534
	TDX_ID_FUNC_ANS_QHZHHYCX,
	TDX_ID_FUNC_REQ_QHZHCCCX,		// 期货组合持仓查询 1536
	TDX_ID_FUNC_ANS_QHZHCCCX,
	TDX_ID_FUNC_REQ_QHZHWTCX,		// 期货组合委托查询 1538
	TDX_ID_FUNC_ANS_QHZHWTCX,
	TDX_ID_FUNC_REQ_QHZHJSKWTS,		// 期货组合计算可委托数 1540
	TDX_ID_FUNC_ANS_QHZHJSKWTS,
	TDX_ID_FUNC_REQ_QHZHCLCX,		// 期货组合策略查询 1542
	TDX_ID_FUNC_ANS_QHZHCLCX,

	// 回购类
	TDX_ID_FUNC_REQ_GPZYHG,			// 股票质押回购 1800
	TDX_ID_FUNC_ANS_GPZYHG,
	TDX_ID_FUNC_REQ_GPZYHG_SQCX,	// 股票质押回购申请查询 1802
	TDX_ID_FUNC_ANS_GPZYHG_SQCX,
	TDX_ID_FUNC_REQ_GPZYHG_HTCX,	// 股票质押回购合同查询 1804
	TDX_ID_FUNC_ANS_GPZYHG_HTCX,
	TDX_ID_FUNC_REQ_GPZYHG_QYCX,	// 股票质押回购权益查询 1806
	TDX_ID_FUNC_ANS_GPZYHG_QYCX,
	TDX_ID_FUNC_REQ_GPZYHG_QXLLCX,	// 股票质押回购期限利率查询 1808
	TDX_ID_FUNC_ANS_GPZYHG_QXLLCX,
	TDX_ID_FUNC_REQ_GPZYHG_LSCX,	// 股票质押回购流水查询 1810
	TDX_ID_FUNC_ANS_GPZYHG_LSCX,
	TDX_ID_FUNC_REQ_GPZYHG_RCFCX,	// 股票质押回购融出方查询 1812
	TDX_ID_FUNC_ANS_GPZYHG_RCFCX,
	TDX_ID_FUNC_REQ_GPZYHG_LXCX,	// 股票质押回购利息查询 1814
	TDX_ID_FUNC_ANS_GPZYHG_LXCX,
	TDX_ID_FUNC_REQ_GPZYHG_LSHTCX,	// 股票质押回购历史合同查询 1816
	TDX_ID_FUNC_ANS_GPZYHG_LSHTCX,
	TDX_ID_FUNC_REQ_GPZYHG_BDZQCX,	// 股票质押回购标的证券查询 1818
	TDX_ID_FUNC_ANS_GPZYHG_BDZQCX,
	TDX_ID_FUNC_REQ_TSHG,			// 特色回购 1830
	TDX_ID_FUNC_ANS_TSHG,
	TDX_ID_FUNC_REQ_TSHG_XXCX,		// 特色回购信息查询 1832
	TDX_ID_FUNC_ANS_TSHG_XXCX,
	TDX_ID_FUNC_REQ_TSHG_SQCX,		// 特色回购申请查询 1834
	TDX_ID_FUNC_ANS_TSHG_SQCX,
	TDX_ID_FUNC_REQ_TSHG_DMCX,		// 特色回购代码查询 1836
	TDX_ID_FUNC_ANS_TSHG_DMCX,
	TDX_ID_FUNC_REQ_TSHG_YZT,		// 特色回购银证通 1838
	TDX_ID_FUNC_ANS_TSHG_YZT,
	TDX_ID_FUNC_REQ_TSHG_ZZJHCX,	// 特色回购转账计划查询 1840
	TDX_ID_FUNC_ANS_TSHG_ZZJHCX,
	TDX_ID_FUNC_REQ_TSHG_LSCX,		// 特色回购流水查询 1842
	TDX_ID_FUNC_ANS_TSHG_LSCX,

	TDX_ID_FUNC_REQ_PSZTSZ,			// 配售状态设置(查询) 2000
	TDX_ID_FUNC_ANS_PSZTSZ,
	TDX_ID_FUNC_REQ_HZHG,			// 合作回购 2002
	TDX_ID_FUNC_ANS_HZHG,
	TDX_ID_FUNC_REQ_HZHGZT,			// 合作回购状态(查询) 2004
	TDX_ID_FUNC_ANS_HZHGZT,
	TDX_ID_FUNC_REQ_HZSGZT,			// 合作申购状态(查询) 2006
	TDX_ID_FUNC_ANS_HZSGZT,
	TDX_ID_FUNC_REQ_HZHGCPDMCX,		// 合作回购产品代码查询 2008
	TDX_ID_FUNC_ANS_HZHGCPDMCX,
	TDX_ID_FUNC_REQ_HZHGCPXXCX,		// 合作回购产品信息查询 2010
	TDX_ID_FUNC_ANS_HZHGCPXXCX,
	TDX_ID_FUNC_REQ_HZHGTQZZCX,		// 合作回购提前终止查询 2012
	TDX_ID_FUNC_ANS_HZHGTQZZCX,
	TDX_ID_FUNC_REQ_HZHGDRWTCX,		// 合作回购当日委托查询 2014
	TDX_ID_FUNC_ANS_HZHGDRWTCX,
	TDX_ID_FUNC_REQ_HZHGDRCJCX,		// 合作回购当日成交查询 2016
	TDX_ID_FUNC_ANS_HZHGDRCJCX,
	TDX_ID_FUNC_REQ_HZHGLSWTCX,		// 合作回购历史委托查询 2018
	TDX_ID_FUNC_ANS_HZHGLSWTCX,
	TDX_ID_FUNC_REQ_HZHGLSCJCX,		// 合作回购历史成交查询 2020
	TDX_ID_FUNC_ANS_HZHGLSCJCX,
	TDX_ID_FUNC_REQ_HZHGQNHYCX,		// 合作回购期内合约查询 2022
	TDX_ID_FUNC_ANS_HZHGQNHYCX,
	TDX_ID_FUNC_REQ_HZHGCDCX,		// 合作回购撤单查询 2024
	TDX_ID_FUNC_ANS_HZHGCDCX,
	TDX_ID_FUNC_REQ_HZHGXYCX,		// 合作回购续约查询 2026
	TDX_ID_FUNC_ANS_HZHGXYCX,
	TDX_ID_FUNC_REQ_HZHGXYZZCX,		// 合作回购续约终止查询 2028
	TDX_ID_FUNC_ANS_HZHGXYZZCX,
	TDX_ID_FUNC_REQ_HZHGTQZZYYCX,	// 合作回购提前终止预约查询 2030
	TDX_ID_FUNC_ANS_HZHGTQZZYYCX,
	TDX_ID_FUNC_REQ_HZHGTQZZYYCXCX,	// 合作回购提前终止预约撤销查询 2032
	TDX_ID_FUNC_ANS_HZHGTQZZYYCXCX,
	TDX_ID_FUNC_REQ_HZHGDYZYWCX,	// 合作回购对应质押物查询 2034
	TDX_ID_FUNC_ANS_HZHGDYZYWCX,
	TDX_ID_FUNC_REQ_HZHGXYCDCX,		// 合作回购续约撤单查询 2036
	TDX_ID_FUNC_ANS_HZHGXYCDCX,
	TDX_ID_FUNC_REQ_HZHGDRDQCX,		// 合作回购当日到期查询 2038
	TDX_ID_FUNC_ANS_HZHGDRDQCX,
	TDX_ID_FUNC_REQ_HZHGLSDQCX,		// 合作回购历史到期查询 2040
	TDX_ID_FUNC_ANS_HZHGLSDQCX,
	TDX_ID_FUNC_REQ_HZHGXZZZYYCX,	// 合作回购续作终止预约查询 2042
	TDX_ID_FUNC_ANS_HZHGXZZZYYCX,
	TDX_ID_FUNC_REQ_HZHGXZZZYYCXCX,	// 合作回购续作终止预约撤销查询 2044
	TDX_ID_FUNC_ANS_HZHGXZZZYYCXCX,
	TDX_ID_FUNC_REQ_HZHGXYBGCX,		// 合作回购续约变更查询 2046
	TDX_ID_FUNC_ANS_HZHGXYBGCX,
	TDX_ID_FUNC_REQ_HZHGHYSYCX,		// 合作回购合约收益查询 2048
	TDX_ID_FUNC_ANS_HZHGHYSYCX,
	TDX_ID_FUNC_REQ_SZBJHGCPDMCX,	// 深圳报价回购产品代码查询 2050
	TDX_ID_FUNC_ANS_SZBJHGCPDMCX,	
	TDX_ID_FUNC_REQ_SZBJHGQNHYCX,	// 深圳报价回购期内合约查询 2052
	TDX_ID_FUNC_ANS_SZBJHGQNHYCX,
	TDX_ID_FUNC_REQ_HZHGXYSZPTCX,	// 合作回购协议设置配套查询 2054
	TDX_ID_FUNC_ANS_HZHGXYSZPTCX,


	TDX_ID_FUNC_REQ_YDHGCSJYPTCX,	// 约定回购初始交易配套查询 2070
	TDX_ID_FUNC_ANS_YDHGCSJYPTCX,
	TDX_ID_FUNC_REQ_YDHGLYBZPTCX,	// 约定回购履约保障配套查询 2072
	TDX_ID_FUNC_ANS_YDHGLYBZPTCX,
	TDX_ID_FUNC_REQ_YDHGTQGHPTCX,	// 约定回购提前购回配套查询 2074
	TDX_ID_FUNC_ANS_YDHGTQGHPTCX,
	TDX_ID_FUNC_REQ_YDHGYQSQPTCX,	// 约定回购延期申请配套查询 2076
	TDX_ID_FUNC_ANS_YDHGYQSQPTCX,
	TDX_ID_FUNC_REQ_YDHGJYCDPTCX,	// 约定回购交易撤单配套查询 2078
	TDX_ID_FUNC_ANS_YDHGJYCDPTCX,
	TDX_ID_FUNC_REQ_YDHGDQHYCX,		// 约定回购当前合约查询 2080
	TDX_ID_FUNC_ANS_YDHGDQHYCX,
	TDX_ID_FUNC_REQ_YDHGLSHYCX,		// 约定回购历史合约查询 2082
	TDX_ID_FUNC_ANS_YDHGLSHYCX,
	TDX_ID_FUNC_REQ_YDHGJXHYCX,		// 约定回购进行合约查询 2084
	TDX_ID_FUNC_ANS_YDHGJXHYCX,
	TDX_ID_FUNC_REQ_YDHGZZHYCX,		// 约定回购终止合约查询 2086
	TDX_ID_FUNC_ANS_YDHGZZHYCX,
	TDX_ID_FUNC_REQ_YDHGBDZQCX,		// 约定回购标的证券查询 2088
	TDX_ID_FUNC_ANS_YDHGBDZQCX,
	TDX_ID_FUNC_REQ_YDHGCPXXCX,		// 约定回购产品信息查询 2090
	TDX_ID_FUNC_ANS_YDHGCPXXCX,
	TDX_ID_FUNC_REQ_YDHGZHXXCX,		// 约定回购综合信息查询 2092
	TDX_ID_FUNC_ANS_YDHGZHXXCX,
	TDX_ID_FUNC_REQ_YDHGYWCZ,		// 约定回购业务操作(信息查询) 2098
	TDX_ID_FUNC_ANS_YDHGYWCZ,

	// 开放式基金类
	TDX_ID_FUNC_REQ_KFSJJWT,		// 开放式基金委托 2100
	TDX_ID_FUNC_ANS_KFSJJWT,
	TDX_ID_FUNC_REQ_KFSJJWTCD,		// 基金委托撤单 2102
	TDX_ID_FUNC_ANS_KFSJJWTCD,
	TDX_ID_FUNC_REQ_KFSJJZH,		// 转换 2104
	TDX_ID_FUNC_ANS_KFSJJZH,
	TDX_ID_FUNC_REQ_KFSJJFECX,		// 份额查询 2106
	TDX_ID_FUNC_ANS_KFSJJFECX,
	TDX_ID_FUNC_REQ_KFSJJWTCX,		// 基金委托查询 2108
	TDX_ID_FUNC_ANS_KFSJJWTCX,
	TDX_ID_FUNC_REQ_KFSJJXXCX,		// 基金相关信息查询 2110
	TDX_ID_FUNC_ANS_KFSJJXXCX,
	TDX_ID_FUNC_REQ_KFSJJCJCX,		// 成交查询 2112
	TDX_ID_FUNC_ANS_KFSJJCJCX,
	TDX_ID_FUNC_REQ_KFSJJFH,		// 基金分红 2114
	TDX_ID_FUNC_ANS_KFSJJFH,
	TDX_ID_FUNC_REQ_KFSJJDMCX,		// 查基金代码 2116
	TDX_ID_FUNC_ANS_KFSJJDMCX,
	TDX_ID_FUNC_REQ_KFSJJZJZHKH,	// 基金资金帐号开户 2118
	TDX_ID_FUNC_ANS_KFSJJZJZHKH,
	TDX_ID_FUNC_REQ_KFSJJZJZHZC,	// 基金资金帐号注册 2120
	TDX_ID_FUNC_ANS_KFSJJZJZHZC,
	TDX_ID_FUNC_REQ_KFSJJKHZLXG,	// 客户资料修改 2122
	TDX_ID_FUNC_ANS_KFSJJKHZLXG,
	TDX_ID_FUNC_REQ_KFSJJCXGSDM,	// 查询基金公司代码 2124
	TDX_ID_FUNC_ANS_KFSJJCXGSDM,
	TDX_ID_FUNC_REQ_KFSJJZHCX,		// 查询基金帐号 2126
	TDX_ID_FUNC_ANS_KFSJJZHCX,
	TDX_ID_FUNC_REQ_KFSJJLSWTCX,	// 基金历史委托查询 2128
	TDX_ID_FUNC_ANS_KFSJJLSWTCX,
	TDX_ID_FUNC_REQ_KFSJJDSDESGSZ,	// 定时定额申购设置 2130
	TDX_ID_FUNC_ANS_KFSJJDSDESGSZ,
	TDX_ID_FUNC_REQ_KFSJJDSDESGQX,	// 定时定额申购取消 2132
	TDX_ID_FUNC_ANS_KFSJJDSDESGQX,
	TDX_ID_FUNC_REQ_KFSJJCXDQDESGPZ,// 查询定期定额申购品种 2134
	TDX_ID_FUNC_ANS_KFSJJCXDQDESGPZ,
	TDX_ID_FUNC_REQ_KFSJJDRWTCX,	// 开放式基金当日委托查询 2136
	TDX_ID_FUNC_ANS_KFSJJDRWTCX,
	TDX_ID_FUNC_REQ_KFSJJFHCX,		// 基金分红查询 2138
	TDX_ID_FUNC_ANS_KFSJJFHCX,
	TDX_ID_FUNC_REQ_LOFJJFHCX,		// LOF基金分红查询 2140
	TDX_ID_FUNC_ANS_LOFJJFHCX,
	TDX_ID_FUNC_REQ_LOFJJFH,		// LOF基金分红设置 2142
	TDX_ID_FUNC_ANS_LOFJJFH,
	TDX_ID_FUNC_REQ_KFSJJFXXXCX,	// 开放式基金基金风险信息查询 2144
	TDX_ID_FUNC_ANS_KFSJJFXXXCX,
	TDX_ID_FUNC_REQ_KFSJJZZKH,		// 基金转帐开户 2146
	TDX_ID_FUNC_ANS_KFSJJZZKH,
	TDX_ID_FUNC_REQ_KFSJJJYKH,		// 基金交易开户 2148
	TDX_ID_FUNC_ANS_KFSJJJYKH,
	TDX_ID_FUNC_REQ_KFSJJDRCJCX,	// 基金当日成交查询 2150
	TDX_ID_FUNC_ANS_KFSJJDRCJCX,
	TDX_ID_FUNC_REQ_KFSJJLSCJCX,	// 基金历史成交查询 2152
	TDX_ID_FUNC_ANS_KFSJJLSCJCX,
	TDX_ID_FUNC_REQ_KFSJJJZCX,		// 基金净值查询 2154
	TDX_ID_FUNC_ANS_KFSJJJZCX,
	TDX_ID_FUNC_REQ_KFSJJXYCXKT,	// 基金协议查询开通 2156
	TDX_ID_FUNC_ANS_KFSJJXYCXKT,
	TDX_ID_FUNC_REQ_KFSJJFHMXCX,	// 基金分红明细查询 2158
	TDX_ID_FUNC_ANS_KFSJJFHMXCX,
	TDX_ID_FUNC_REQ_DQDESZCX,		// 定期定额设置查询 2160
	TDX_ID_FUNC_ANS_DQDESZCX,
	TDX_ID_FUNC_REQ_KFSJJFJYWTCX,	// 开放式基金非交易委托查询 2162
	TDX_ID_FUNC_ANS_KFSJJFJYWTCX,
	TDX_ID_FUNC_REQ_KFSJJFJYDRWTCX,	// 开放式基金非交易当日委托查询 2164
	TDX_ID_FUNC_ANS_KFSJJFJYDRWTCX,
	TDX_ID_FUNC_REQ_KFSJJFXKCSDMCX,	// 开放式基金风险可承受代码查询 2166
	TDX_ID_FUNC_ANS_KFSJJFXKCSDMCX,
	TDX_ID_FUNC_REQ_KFSJJFLCX,		// 开放式基金费率查询 2168
	TDX_ID_FUNC_ANS_KFSJJFLCX,
	TDX_ID_FUNC_REQ_KFSJJDQDESHSZ,	// 开放式基金定期定额赎回设置 2170
	TDX_ID_FUNC_ANS_KFSJJDQDESHSZ,
	TDX_ID_FUNC_REQ_KFSJJDQDESHQX,	// 开放式基金定期定额赎回取消 2172
	TDX_ID_FUNC_ANS_KFSJJDQDESHQX,
	TDX_ID_FUNC_REQ_KFSJJDQDESHCX,	// 开放式基金定期定额赎回查询 2174
	TDX_ID_FUNC_ANS_KFSJJDQDESHCX,
	TDX_ID_FUNC_REQ_KFSJJDQDESHPZ,	// 开放式基金定期定额赎回品种 2176
	TDX_ID_FUNC_ANS_KFSJJDQDESHPZ,
	TDX_ID_FUNC_REQ_KFSJJDMXGXXCX,	// 开放式基金代码相关信息查询 2178
	TDX_ID_FUNC_ANS_KFSJJDMXGXXCX,
	TDX_ID_FUNC_REQ_KFSJJGSXGXXCX,	// 开放式基金公司相关信息查询 2180
	TDX_ID_FUNC_ANS_KFSJJGSXGXXCX,
	TDX_ID_FUNC_REQ_KFSJJDZDCX,		// 开放式基金对账单查询 2182
	TDX_ID_FUNC_ANS_KFSJJDZDCX,
	TDX_ID_FUNC_REQ_KFSJJJGDCX,		// 开放式基金交割单查询 2184
	TDX_ID_FUNC_ANS_KFSJJJGDCX,

	// 理财产品
	TDX_ID_FUNC_REQ_LCCPFECX,		// 理财产品份额查询 2200
	TDX_ID_FUNC_ANS_LCCPFECX,
	TDX_ID_FUNC_REQ_LCCPWTCX,		// 理财产品委托查询 2202
	TDX_ID_FUNC_ANS_LCCPWTCX,
	TDX_ID_FUNC_REQ_LCCPCJCX,		// 理财产品成交查询 2204
	TDX_ID_FUNC_ANS_LCCPCJCX,
	TDX_ID_FUNC_REQ_LCCPDRWTCX,		// 理财产品当日委托查询 2206
	TDX_ID_FUNC_ANS_LCCPDRWTCX,
	TDX_ID_FUNC_REQ_LCCPDMCX,		// 理财产品代码查询 2208
	TDX_ID_FUNC_ANS_LCCPDMCX,
	TDX_ID_FUNC_REQ_LCCPZHCX,		// 理财产品帐号查询 2210
	TDX_ID_FUNC_ANS_LCCPZHCX,
	TDX_ID_FUNC_REQ_LCCPDQDESGCX,	// 理财产品定期定额申购查询 2212
	TDX_ID_FUNC_ANS_LCCPDQDESGCX,
	TDX_ID_FUNC_REQ_LCCPDQDESGPZ,	// 理财产品定期定额申购品种 2214
	TDX_ID_FUNC_ANS_LCCPDQDESGPZ,
	TDX_ID_FUNC_REQ_LCCPZZJHLBCX,	// 理财产品增值计划列表查询 2216
	TDX_ID_FUNC_ANS_LCCPZZJHLBCX,
	TDX_ID_FUNC_REQ_LCCPZZJHXXCX,	// 理财产品增值计划信息查询 2218
	TDX_ID_FUNC_ANS_LCCPZZJHXXCX,
	TDX_ID_FUNC_REQ_LCCPZZJHJESZ,	// 理财产品增值计划金额设置 2220
	TDX_ID_FUNC_ANS_LCCPZZJHJESZ,
	TDX_ID_FUNC_REQ_LCCPZZJHZTSZ,	// 理财产品增值计划状态设置 2222
	TDX_ID_FUNC_ANS_LCCPZZJHZTSZ,
	TDX_ID_FUNC_REQ_LCCPZZJHJCXY,	// 理财产品增值计划解除协议 2224
	TDX_ID_FUNC_ANS_LCCPZZJHJCXY,
	TDX_ID_FUNC_REQ_LCCPZZJHFECX,	// 理财产品增值计划份额查询 2226
	TDX_ID_FUNC_ANS_LCCPZZJHFECX,
	TDX_ID_FUNC_REQ_LCCPZZJHCDCX,	// 理财产品增值计划撤单查询 2228
	TDX_ID_FUNC_ANS_LCCPZZJHCDCX,
	TDX_ID_FUNC_REQ_LCCPZZJHXXXG,	// 理财产品增值计划信息修改 2230
	TDX_ID_FUNC_ANS_LCCPZZJHXXXG,
	TDX_ID_FUNC_REQ_LCCPZZJHFESH,	// 理财产品增值计划份额赎回 2232
	TDX_ID_FUNC_ANS_LCCPZZJHFESH,
	TDX_ID_FUNC_REQ_LCCPZZJHWTCD,	// 理财产品增值计划委托撤单 2234
	TDX_ID_FUNC_ANS_LCCPZZJHWTCD,
	TDX_ID_FUNC_REQ_LCCPZZJHYYQKCZ,	// 理财产品增值计划预约取款操作 2236
	TDX_ID_FUNC_ANS_LCCPZZJHYYQKCZ,
	TDX_ID_FUNC_REQ_LCCPZZJHYYQKCX,	// 理财产品增值计划预约取款查询 2238
	TDX_ID_FUNC_ANS_LCCPZZJHYYQKCX,
	TDX_ID_FUNC_REQ_LCCPZZJHLSSYCX,	// 理财产品增值计划历史收益查询 2240
	TDX_ID_FUNC_ANS_LCCPZZJHLSSYCX,
	TDX_ID_FUNC_REQ_DQLCCPSHXXCX,	// 短期理财产品赎回信息查询 2242
	TDX_ID_FUNC_ANS_DQLCCPSHXXCX,
	TDX_ID_FUNC_REQ_LCCPZRDMCX,		// 理财产品转让代码查询 2244
	TDX_ID_FUNC_ANS_LCCPZRDMCX,
	TDX_ID_FUNC_REQ_LCCPZRHQCX,		// 理财产品转让行情查询 2246
	TDX_ID_FUNC_ANS_LCCPZRHQCX,
	TDX_ID_FUNC_REQ_LCCPZRCDCX,		// 理财产品转让撤单查询 2248
	TDX_ID_FUNC_ANS_LCCPZRCDCX,
	TDX_ID_FUNC_REQ_LCCPZRWTCX,		// 理财产品转让委托查询 2250
	TDX_ID_FUNC_ANS_LCCPZRWTCX,
	TDX_ID_FUNC_REQ_LCCPZRCJCX,		// 理财产品转让成交查询 2252
	TDX_ID_FUNC_ANS_LCCPZRCJCX,
	TDX_ID_FUNC_REQ_LCCPQYJYCX,		// 理财产品签约解约查询 2254
	TDX_ID_FUNC_ANS_LCCPQYJYCX,
	TDX_ID_FUNC_REQ_YHLCCPDMCX,		// 银行理财产品代码查询 2256
	TDX_ID_FUNC_ANS_YHLCCPDMCX,
	TDX_ID_FUNC_REQ_YHLCCPFECX,		// 银行理财产品份额查询 2258
	TDX_ID_FUNC_ANS_YHLCCPFECX,
	TDX_ID_FUNC_REQ_YHLCCPWTCX,		// 银行查理财产品委托查询 2260
	TDX_ID_FUNC_ANS_YHLCCPWTCX,
	TDX_ID_FUNC_REQ_YHLCCPZHCX,		// 银行理财产品帐号查询 2262
	TDX_ID_FUNC_ANS_YHLCCPZHCX,
	TDX_ID_FUNC_REQ_YHLCCPCJCX,		// 银行理财产品成交查询 2264
	TDX_ID_FUNC_ANS_YHLCCPCJCX,
	TDX_ID_FUNC_REQ_OTCFECX,		// OTC份额查询 2266
	TDX_ID_FUNC_ANS_OTCFECX,
	TDX_ID_FUNC_REQ_OTCRSSCX,		// OTC认申赎查询 2268
	TDX_ID_FUNC_ANS_OTCRSSCX,
	TDX_ID_FUNC_REQ_OTCYXSBCX,		// OTC意向申报查询 2270
	TDX_ID_FUNC_ANS_OTCYXSBCX,
	TDX_ID_FUNC_REQ_OTCCJSBCX,		// OTC成交申报查询 2272
	TDX_ID_FUNC_ANS_OTCCJSBCX,
	TDX_ID_FUNC_REQ_OTCCPHYCX,		// OTC产品合约查询 2274
	TDX_ID_FUNC_ANS_OTCCPHYCX,
	TDX_ID_FUNC_REQ_OTCBJXXCX,		// OTC报价信息查询 2276
	TDX_ID_FUNC_ANS_OTCBJXXCX,
	TDX_ID_FUNC_REQ_OTCHQXXCX,		// OTC行情信息查询 2278
	TDX_ID_FUNC_ANS_OTCHQXXCX,
	TDX_ID_FUNC_REQ_OTCDZHTLBCX,	// OTC电子合同列表查询 2280
	TDX_ID_FUNC_ANS_OTCDZHTLBCX,
	TDX_ID_FUNC_REQ_OTCDZHTCX,		// OTC电子合同查询 2282
	TDX_ID_FUNC_ANS_OTCDZHTCX,
	TDX_ID_FUNC_REQ_XTCPDMCX,		// 信托产品代码查询 2300
	TDX_ID_FUNC_ANS_XTCPDMCX,
	TDX_ID_FUNC_REQ_XTCPFECX,		// 信托产品份额查询 2302
	TDX_ID_FUNC_ANS_XTCPFECX,
	TDX_ID_FUNC_REQ_XTCPZHCX,		// 信托产品帐号查询 2304
	TDX_ID_FUNC_ANS_XTCPZHCX,
	TDX_ID_FUNC_REQ_XTCPWTCX,		// 信托产品委托查询 2306
	TDX_ID_FUNC_ANS_XTCPWTCX,
	TDX_ID_FUNC_REQ_XTCPCJCX,		// 信托产品成交查询 2308
	TDX_ID_FUNC_ANS_XTCPCJCX,
	TDX_ID_FUNC_REQ_XTCPLSWTCX,		// 信托产品历史委托查询 2310
	TDX_ID_FUNC_ANS_XTCPLSWTCX,
		
	// 基金直销
	TDX_ID_FUNC_REQ_JJZXRG,			// 基金直销认购 2500
	TDX_ID_FUNC_ANS_JJZXRG,
	TDX_ID_FUNC_REQ_JJZXSG,			// 基金直销申购 2502
	TDX_ID_FUNC_ANS_JJZXSG,
	TDX_ID_FUNC_REQ_JJZXSH,			// 基金直销赎回 2504
	TDX_ID_FUNC_ANS_JJZXSH,
	TDX_ID_FUNC_REQ_JJZXFH,			// 基金直销分红 2506
	TDX_ID_FUNC_ANS_JJZXFH,
	TDX_ID_FUNC_REQ_JJZXZH,			// 基金直销转换 2508
	TDX_ID_FUNC_ANS_JJZXZH,
	TDX_ID_FUNC_REQ_JJZXZTG,		// 基金直销转托管 2510
	TDX_ID_FUNC_ANS_JJZXZTG,
	TDX_ID_FUNC_REQ_JJZXCD,			// 基金直销撤单 2512
	TDX_ID_FUNC_ANS_JJZXCD,
	TDX_ID_FUNC_REQ_JJZXFLCX,		// 基金直销费率查询 2514
	TDX_ID_FUNC_ANS_JJZXFLCX,
	TDX_ID_FUNC_REQ_JJZXYHZF,		// 基金直销银行支付 2516
	TDX_ID_FUNC_ANS_JJZXYHZF,
	TDX_ID_FUNC_REQ_JJZXXSRDMCX,	// 基金直销销售人代码查询 2518
	TDX_ID_FUNC_ANS_JJZXXSRDMCX,
	TDX_ID_FUNC_REQ_JJZXXXJC,		// 基金直销信息检查 2520
	TDX_ID_FUNC_ANS_JJZXXXJC,

	// 交易所场内基金
	TDX_ID_FUNC_REQ_JYSCNJJDMCX,	// 交易所场内基金代码查询 2850
	TDX_ID_FUNC_ANS_JYSCNJJDMCX,
	TDX_ID_FUNC_REQ_JYSCNJJCFGCX,	// 交易所场内基金成分股查询 2852
	TDX_ID_FUNC_ANS_JYSCNJJCFGCX,

	// ETF
	TDX_ID_FUNC_REQ_ETFSHKJSGPTCX,	// ETF上海跨境申购配套查询 2950
	TDX_ID_FUNC_ANS_ETFSHKJSGPTCX,
	TDX_ID_FUNC_REQ_ETFSZKJSGPTCX,	// ETF深圳跨境申购配套查询 2952
	TDX_ID_FUNC_ANS_ETFSZKJSGPTCX,
	TDX_ID_FUNC_REQ_ETFSHKJSHPTCX,	// ETF上海跨境赎回配套查询 2954
	TDX_ID_FUNC_ANS_ETFSHKJSHPTCX,
	TDX_ID_FUNC_REQ_ETFSZKJSHPTCX,	// ETF深圳跨境赎回配套查询 2956
	TDX_ID_FUNC_ANS_ETFSZKJSHPTCX,
	TDX_ID_FUNC_REQ_ETFSHKJWTCDCX,	// ETF上海跨境委托撤单查询 2958
	TDX_ID_FUNC_ANS_ETFSHKJWTCDCX,
	TDX_ID_FUNC_REQ_ETFSZKJWTCDCX,	// ETF深圳跨境委托撤单查询 2960
	TDX_ID_FUNC_ANS_ETFSZKJWTCDCX,
	TDX_ID_FUNC_REQ_ETFSHKJDRWTCX,	// ETF上海跨境当日委托查询 2962
	TDX_ID_FUNC_ANS_ETFSHKJDRWTCX,
	TDX_ID_FUNC_REQ_ETFSZKJDRWTCX,	// ETF深圳跨境当日委托查询 2964
	TDX_ID_FUNC_ANS_ETFSZKJDRWTCX,
	TDX_ID_FUNC_REQ_ETFSHKJDRCJCX,	// ETF上海跨境当日成交查询 2966
	TDX_ID_FUNC_ANS_ETFSHKJDRCJCX,
	TDX_ID_FUNC_REQ_ETFSZKJDRCJCX,	// ETF深圳跨境当日成交查询 2968
	TDX_ID_FUNC_ANS_ETFSZKJDRCJCX,
	TDX_ID_FUNC_REQ_ETFSHKJLSWTCX,	// ETF上海跨境历史委托查询 2970
	TDX_ID_FUNC_ANS_ETFSHKJLSWTCX,
	TDX_ID_FUNC_REQ_ETFSZKJLSWTCX,	// ETF深圳跨境历史委托查询 2972
	TDX_ID_FUNC_ANS_ETFSZKJLSWTCX,
	TDX_ID_FUNC_REQ_ETFSHKJLSCJCX,	// ETF上海跨境历史成交查询 2974
	TDX_ID_FUNC_ANS_ETFSHKJLSCJCX,
	TDX_ID_FUNC_REQ_ETFSZKJLSCJCX,	// ETF深圳跨境历史成交查询 2976
	TDX_ID_FUNC_ANS_ETFSZKJLSCJCX,
	TDX_ID_FUNC_REQ_ETFWXXJRGPTCX,	// ETF网下现金认购配套查询 2980
	TDX_ID_FUNC_ANS_ETFWXXJRGPTCX,
	TDX_ID_FUNC_REQ_ETFWXGFRGPTCX,	// ETF网下股份认购配套查询 2982
	TDX_ID_FUNC_ANS_ETFWXGFRGPTCX,
	TDX_ID_FUNC_REQ_ETFWXXJRGCDCX,	// ETF网下现金认购撤单查询 2984
	TDX_ID_FUNC_ANS_ETFWXXJRGCDCX,
	TDX_ID_FUNC_REQ_ETFWXGFRGCDCX,	// ETF网下股份认购撤单查询 2986
	TDX_ID_FUNC_ANS_ETFWXGFRGCDCX,
	TDX_ID_FUNC_REQ_ETFWXXJRGXXCX,	// ETF网下现金认购信息查询 2988
	TDX_ID_FUNC_ANS_ETFWXXJRGXXCX,
	TDX_ID_FUNC_REQ_ETFWXGFRGXXCX,	// ETF网下股份认购信息查询 2990
	TDX_ID_FUNC_ANS_ETFWXGFRGXXCX,
	TDX_ID_FUNC_REQ_ETFWXXJRGLSCX,	// ETF网下现金认购流水查询 2992
	TDX_ID_FUNC_ANS_ETFWXXJRGLSCX,
	TDX_ID_FUNC_REQ_ETFWXGFRGLSCX,	// ETF网下股份认购流水查询 2994
	TDX_ID_FUNC_ANS_ETFWXGFRGLSCX,
	TDX_ID_FUNC_REQ_ETFMM,			// ETF买卖 3000
	TDX_ID_FUNC_ANS_ETFMM,
	TDX_ID_FUNC_REQ_ETFXXCX,		// ETF信息查询 3002
	TDX_ID_FUNC_ANS_ETFXXCX,
	TDX_ID_FUNC_REQ_ETFRGCX,		// ETF认购查询 3004
	TDX_ID_FUNC_ANS_ETFRGCX,
	TDX_ID_FUNC_REQ_ETFRGCD,		// ETF认购撤单 3006
	TDX_ID_FUNC_ANS_ETFRGCD,
	TDX_ID_FUNC_REQ_ETFPCH,			// ETF取批次号 3008
	TDX_ID_FUNC_ANS_ETFPCH,
	TDX_ID_FUNC_REQ_ETFGPLMM,		// ETF股票篮买卖 3010
	TDX_ID_FUNC_ANS_ETFGPLMM,
	TDX_ID_FUNC_REQ_ETFGPLCX,		// ETF股票篮查询 3012
	TDX_ID_FUNC_ANS_ETFGPLCX,
	TDX_ID_FUNC_REQ_ETFYGCX,		// ETF上证50拥股查询 3014
	TDX_ID_FUNC_ANS_ETFYGCX,
	TDX_ID_FUNC_REQ_ETFWTCX,		// ETF委托查询 3016
	TDX_ID_FUNC_ANS_ETFWTCX,
	TDX_ID_FUNC_REQ_ETFCJCX,		// ETF成交查询 3018
	TDX_ID_FUNC_ANS_ETFCJCX,
	TDX_ID_FUNC_REQ_ETFCLCX,		// ETF策略查询 3020
	TDX_ID_FUNC_ANS_ETFCLCX,
	TDX_ID_FUNC_REQ_ETFZSDMCX,		// ETF指数代码查询 3022
	TDX_ID_FUNC_ANS_ETFZSDMCX,
	TDX_ID_FUNC_REQ_ETFQR,			// ETF(委托)确认 3024
	TDX_ID_FUNC_ANS_ETFQR,
	TDX_ID_FUNC_REQ_ETFWTCXMX,		// ETF委托查询明细 3026
	TDX_ID_FUNC_ANS_ETFWTCXMX,
	TDX_ID_FUNC_REQ_ETFRGCDCX,		// ETF认购撤单查询 3028
	TDX_ID_FUNC_ANS_ETFRGCDCX,
	TDX_ID_FUNC_REQ_ETFZSCFCX,		// ETF指数成分查询 3030
	TDX_ID_FUNC_ANS_ETFZSCFCX,
	TDX_ID_FUNC_REQ_ETFGFCX,		// ETF股份查询 3032
	TDX_ID_FUNC_ANS_ETFGFCX,
	TDX_ID_FUNC_REQ_ETFKSGCFGCX,	// ETF可申购成分股查询 3034
	TDX_ID_FUNC_ANS_ETFKSGCFGCX,
	TDX_ID_FUNC_REQ_ETFGPLCD,		// ETF股票篮撤单 3036
	TDX_ID_FUNC_ANS_ETFGPLCD,
	TDX_ID_FUNC_REQ_ETFGPLCDCX,		// ETF股票篮撤单查询 3038
	TDX_ID_FUNC_ANS_ETFGPLCDCX,
	TDX_ID_FUNC_REQ_ETFKSCDPCX,		// ETF跨市场对盘查询
	TDX_ID_FUNC_ANS_ETFKSCDPCX,

	// 组合通业务
	TDX_ID_FUNC_REQ_ZHTPCH,			// 组合通批次号 3050
	TDX_ID_FUNC_ANS_ZHTPCH,
	TDX_ID_FUNC_REQ_ZHTGPLMM,		// 组合通股票篮买卖 3052
	TDX_ID_FUNC_ANS_ZHTGPLMM,
	TDX_ID_FUNC_REQ_ZHTGPLCX,		// 组合通股票篮查询 3054
	TDX_ID_FUNC_ANS_ZHTGPLCX,
	TDX_ID_FUNC_REQ_ZHTYGCX,		// 组合通拥股查询 3056
	TDX_ID_FUNC_ANS_ZHTYGCX,
	TDX_ID_FUNC_REQ_ZHTWTCX,		// 组合通委托查询 3058
	TDX_ID_FUNC_ANS_ZHTWTCX,
	TDX_ID_FUNC_REQ_ZHTCJCX,		// 组合通成交查询 3060
	TDX_ID_FUNC_ANS_ZHTCJCX,
	TDX_ID_FUNC_REQ_ZHTCLCX,		// 组合通策略查询 3062
	TDX_ID_FUNC_ANS_ZHTCLCX,
	TDX_ID_FUNC_REQ_ZHTZSDMCX,		// 组合通指数代码查询 3064
	TDX_ID_FUNC_ANS_ZHTZSDMCX,
	TDX_ID_FUNC_REQ_ZHTQR,			// 组合通确认 3066
	TDX_ID_FUNC_ANS_ZHTQR,
	TDX_ID_FUNC_REQ_ZHTLSCX,		// 组合通历史查询 3068
	TDX_ID_FUNC_ANS_ZHTLSCX,
	TDX_ID_FUNC_REQ_ZHTLSCXMX,		// 组合通历史查询明细 3070
	TDX_ID_FUNC_ANS_ZHTLSCXMX,
	TDX_ID_FUNC_REQ_ZHTWTCXMX,		// 组合通委托查询明细 3072
	TDX_ID_FUNC_ANS_ZHTWTCXMX,
	TDX_ID_FUNC_REQ_ZHTCJCXMX,		// 组合通成交查询明细 3074
	TDX_ID_FUNC_ANS_ZHTCJCXMX,
	TDX_ID_FUNC_REQ_ZHTZSCFCX,		// 组合通指数成分查询 3076
	TDX_ID_FUNC_ANS_ZHTZSCFCX,

	// 套利交易
	TDX_ID_FUNC_REQ_TL_HQHHH,		// (套利)获取会话号 3100
	TDX_ID_FUNC_ANS_TL_HQHHH,
	TDX_ID_FUNC_REQ_TL_ZHDMCX,		// (套利)组合代码查询 3102
	TDX_ID_FUNC_ANS_TL_ZHDMCX,
	TDX_ID_FUNC_REQ_TL_ZHCFCX,		// (套利)组合成分查询 3104
	TDX_ID_FUNC_ANS_TL_ZHCFCX,
	TDX_ID_FUNC_REQ_TL_ZHDMCZ,		// (套利)组合代码操作 3106
	TDX_ID_FUNC_ANS_TL_ZHDMCZ,
	TDX_ID_FUNC_REQ_TL_ZHCFCZ,		// (套利)组合成分操作 3108
	TDX_ID_FUNC_ANS_TL_ZHCFCZ,
	TDX_ID_FUNC_REQ_TL_CLDMCX,		// (套利)策略代码查询 3110
	TDX_ID_FUNC_ANS_TL_CLDMCX,
	TDX_ID_FUNC_REQ_TL_CLCFCX,		// (套利)策略成分查询 3112
	TDX_ID_FUNC_ANS_TL_CLCFCX,
	TDX_ID_FUNC_REQ_TL_CLDMCZ,		// (套利)策略代码操作 3114
	TDX_ID_FUNC_ANS_TL_CLDMCZ,
	TDX_ID_FUNC_REQ_TL_CLCFCZ,		// (套利)策略成分操作 3116
	TDX_ID_FUNC_ANS_TL_CLCFCZ,
	TDX_ID_FUNC_REQ_TL_PHCZ,		// (套利)批号操作 3118
	TDX_ID_FUNC_ANS_TL_PHCZ,
	TDX_ID_FUNC_REQ_TL_PHCX,		// (套利)批号查询 3120
	TDX_ID_FUNC_ANS_TL_PHCX,
	TDX_ID_FUNC_REQ_TL_PHWTLB,		// (套利)批号委托列表 3122
	TDX_ID_FUNC_ANS_TL_PHWTLB,
	TDX_ID_FUNC_REQ_TL_PHWTZX,		// (套利)批号委托执行 3124
	TDX_ID_FUNC_ANS_TL_PHWTZX,
	TDX_ID_FUNC_REQ_TL_PHWTCX,		// (套利)批号委托查询 3126
	TDX_ID_FUNC_ANS_TL_PHWTCX,
	TDX_ID_FUNC_REQ_TL_PHCCCX,		// (套利)批号持仓查询 3128
	TDX_ID_FUNC_ANS_TL_PHCCCX,

	// 算法交易
	TDX_ID_FUNC_REQ_SFJY_DDCZ,		// (算法交易)订单操作 3190
	TDX_ID_FUNC_ANS_SFJY_DDCZ,
	TDX_ID_FUNC_REQ_SFJY_DDLBCX,	// (算法交易)订单列表查询 3192
	TDX_ID_FUNC_ANS_SFJY_DDLBCX,
	TDX_ID_FUNC_REQ_SFJY_DDJGCX,	// (算法交易)订单结果查询 3194
	TDX_ID_FUNC_ANS_SFJY_DDJGCX,

	//信用交易
	TDX_ID_FUNC_REQ_XYZCCX,			// 信用资产查询 3200
	TDX_ID_FUNC_ANS_XYZCCX,
	TDX_ID_FUNC_REQ_XYGFCX,			// 信用股份查询 3202
	TDX_ID_FUNC_ANS_XYGFCX,
	TDX_ID_FUNC_REQ_XYHYCX,			// 默认未平仓合约查询查询 3204
	TDX_ID_FUNC_ANS_XYHYCX,
	TDX_ID_FUNC_REQ_XYHYYPCCX,		// 已平仓合约查询 3206
	TDX_ID_FUNC_ANS_XYHYYPCCX,
	TDX_ID_FUNC_REQ_XYSXCX,			// 信用上限查询 3208
	TDX_ID_FUNC_ANS_XYSXCX,
	TDX_ID_FUNC_REQ_XYFZCX,			// 信用负债查询 3210
	TDX_ID_FUNC_ANS_XYFZCX,
	TDX_ID_FUNC_REQ_FXYZCCX,		// 非信用资产查询 3212
	TDX_ID_FUNC_ANS_FXYZCCX,
	TDX_ID_FUNC_REQ_XYHYDRCX,		// 信用合约当日查询 3214
	TDX_ID_FUNC_ANS_XYHYDRCX,
	TDX_ID_FUNC_REQ_XYJYBDZQCX,		// 信用交易标的证券查询 3216
	TDX_ID_FUNC_ANS_XYJYBDZQCX,
	TDX_ID_FUNC_REQ_XYJYZHXXCX,		// 信用交易综合信息查询 3218
	TDX_ID_FUNC_ANS_XYJYZHXXCX,
	TDX_ID_FUNC_REQ_XYJYDBPZQCX,	// 信用交易担保品证券查询 3220
	TDX_ID_FUNC_ANS_XYJYDBPZQCX,
	TDX_ID_FUNC_REQ_XYJYRZMRZQCX,	// 信用交易融资买入证券查询 3222
	TDX_ID_FUNC_ANS_XYJYRZMRZQCX,
	TDX_ID_FUNC_REQ_XYJYRQMCZQCX,	// 信用交易融券卖出证券查询 3224
	TDX_ID_FUNC_ANS_XYJYRQMCZQCX,
	TDX_ID_FUNC_REQ_XYJYDMTSXXCX,	// 信用交易代码提示信息查询 3226
	TDX_ID_FUNC_ANS_XYJYDMTSXXCX,
	TDX_ID_FUNC_REQ_XYJYHYHZCX,		// 信用交易合约汇总查询 3228
	TDX_ID_FUNC_ANS_XYJYHYHZCX,
	TDX_ID_FUNC_REQ_XYJYRZMRPTCX,	// 信用交易融资买入配套查询 3230
	TDX_ID_FUNC_ANS_XYJYRZMRPTCX,
	TDX_ID_FUNC_REQ_XYJYRQMCPTCX,	// 信用交易融券卖出配套查询 3232
	TDX_ID_FUNC_ANS_XYJYRQMCPTCX,
	TDX_ID_FUNC_REQ_XYJYMQHQPTCX,	// 信用交易买券还券配套查询 3234
	TDX_ID_FUNC_ANS_XYJYMQHQPTCX,
	TDX_ID_FUNC_REQ_XYJYYQHZPTCX,	// 信用交易余券划转配套查询 3236
	TDX_ID_FUNC_ANS_XYJYYQHZPTCX,
	TDX_ID_FUNC_REQ_XYJYXQHQPTCX,	// 信用交易现券还券配套查询 3238
	TDX_ID_FUNC_ANS_XYJYXQHQPTCX,
	TDX_ID_FUNC_REQ_XYJYDBPHZPTCX,	// 信用交易担保品划转配套查询 3240
	TDX_ID_FUNC_ANS_XYJYDBPHZPTCX,
	TDX_ID_FUNC_REQ_XYJYDBPHRPTCX,	// 信用交易担保品划入配套查询 3242
	TDX_ID_FUNC_ANS_XYJYDBPHRPTCX,
	TDX_ID_FUNC_REQ_XYJYDBPHCPTCX,	// 信用交易担保品划出配套查询 3244
	TDX_ID_FUNC_ANS_XYJYDBPHCPTCX,
	TDX_ID_FUNC_REQ_XYJYXJHKPTCX,	// 信用交易现金还款配套查询 3246
	TDX_ID_FUNC_ANS_XYJYXJHKPTCX,
	TDX_ID_FUNC_REQ_XYJYMQHKPTCX,	// 信用交易卖券还款配套查询 3248
	TDX_ID_FUNC_ANS_XYJYMQHKPTCX,
	TDX_ID_FUNC_REQ_XYJYRZPCMCPTCX,	// 信用交易融资平仓卖出配套查询 3250
	TDX_ID_FUNC_ANS_XYJYRZPCMCPTCX,
	TDX_ID_FUNC_REQ_XYJYRQPCMRPTCX,	// 信用交易融券平仓买入配套查询 3252
	TDX_ID_FUNC_ANS_XYJYRQPCMRPTCX,
	TDX_ID_FUNC_REQ_XYJYLLXXCX,		// 信用交易利率信息查询 3254
	TDX_ID_FUNC_ANS_XYJYLLXXCX,
	TDX_ID_FUNC_REQ_XYJYRQYECX,		// 信用交易融券余额查询 3256
	TDX_ID_FUNC_ANS_XYJYRQYECX,
	TDX_ID_FUNC_REQ_XYJYRZYECX,		// 信用交易融资余额查询 3258
	TDX_ID_FUNC_ANS_XYJYRZYECX,
	TDX_ID_FUNC_REQ_XYJYFJYHZCX,	// 信用交易非交易化转查询 3260
	TDX_ID_FUNC_ANS_XYJYFJYHZCX,
	TDX_ID_FUNC_REQ_XYJYLXFYCX,		// 信用交易利息费用查询 3262
	TDX_ID_FUNC_ANS_XYJYLXFYCX,
	TDX_ID_FUNC_REQ_XYJYZJFZCX,		// 信用交易资金负债查询 3264
	TDX_ID_FUNC_ANS_XYJYZJFZCX,
	TDX_ID_FUNC_REQ_XYJYZQFZCX,		// 信用交易证券负债查询 3266
	TDX_ID_FUNC_ANS_XYJYZQFZCX,
	TDX_ID_FUNC_REQ_XYJYKHQYCX,		// 信用交易客户签约查询 3268
	TDX_ID_FUNC_ANS_XYJYKHQYCX,
	TDX_ID_FUNC_REQ_XYJYKHXYCL,		// 信用交易客户协议处理 3270
	TDX_ID_FUNC_ANS_XYJYKHXYCL,
	TDX_ID_FUNC_REQ_XYJYCHMXCX,		// 信用交易偿还明细查询 3272
	TDX_ID_FUNC_ANS_XYJYCHMXCX,
	TDX_ID_FUNC_REQ_XYJYRZHYCX,		// 信用交易融资合约查询 3274
	TDX_ID_FUNC_ANS_XYJYRZHYCX,
	TDX_ID_FUNC_REQ_XYJYRQHYCX,		// 信用交易融券合约查询 3276
	TDX_ID_FUNC_ANS_XYJYRQHYCX,
	TDX_ID_FUNC_REQ_XYJYDBPHZCX,	// 信用交易担保品划转查询 3278
	TDX_ID_FUNC_ANS_XYJYDBPHZCX,
	TDX_ID_FUNC_REQ_XYJYMRDBPPTCX,	// 信用交易买入担保品配套查询 3280
	TDX_ID_FUNC_ANS_XYJYMRDBPPTCX,
	TDX_ID_FUNC_REQ_XYJYMCDBPPTCX,	// 信用交易卖出担保品配套查询 3282
	TDX_ID_FUNC_ANS_XYJYMCDBPPTCX,
	TDX_ID_FUNC_REQ_XYJYGHRQFYPTCX,	// 信用交易归还融券费用配套查询 3284
	TDX_ID_FUNC_ANS_XYJYGHRQFYPTCX,
	TDX_ID_FUNC_REQ_XYJYFZLSCX,		// 信用交易负债流水查询 3286
	TDX_ID_FUNC_ANS_XYJYFZLSCX,
	TDX_ID_FUNC_REQ_XYJYXJTDHQPTCX, // 信用交易现金替代还券配套查询 3288
	TDX_ID_FUNC_ANS_XYJYXJTDHQPTCX,
	TDX_ID_FUNC_REQ_XYJYWCDBBLCX,	// 信用交易维持担保比率查询 3290
	TDX_ID_FUNC_ANS_XYJYWCDBBLCX,
	TDX_ID_FUNC_REQ_XYJYEDGL,		// 信用交易额度管理 3292
	TDX_ID_FUNC_ANS_XYJYEDGL,
	TDX_ID_FUNC_REQ_XYJYEDBGCX,		// 信用交易额度变更查询 3294
	TDX_ID_FUNC_ANS_XYJYEDBGCX,
	TDX_ID_FUNC_REQ_XYJYPCRZHYCX,	// 信用交易平仓融资合约查询 3296
	TDX_ID_FUNC_ANS_XYJYPCRZHYCX,
	TDX_ID_FUNC_REQ_XYJYPCRQHYCX,	// 信用交易平仓融券合约查询 3298
	TDX_ID_FUNC_ANS_XYJYPCRQHYCX,

	// 转融通
	TDX_ID_FUNC_REQ_ZRTYWCZ,		// 转融通业务操作 3400
	TDX_ID_FUNC_ANS_ZRTYWCZ,
	TDX_ID_FUNC_REQ_ZRTBDZQCX,		// 转融通标的证券查询 3402
	TDX_ID_FUNC_ANS_ZRTBDZQCX,
	TDX_ID_FUNC_REQ_ZRTZJXXCX,		// 转融通资金信息查询 3404
	TDX_ID_FUNC_ANS_ZRTZJXXCX,
	TDX_ID_FUNC_REQ_ZRTGFXXCX,		// 转融通股份信息查询 3406
	TDX_ID_FUNC_ANS_ZRTGFXXCX,
	TDX_ID_FUNC_REQ_ZRTRZMRPTCX,	// 转融通融资买入配套查询 3408
	TDX_ID_FUNC_ANS_ZRTRZMRPTCX,
	TDX_ID_FUNC_REQ_ZRTRQMCPTCX,	// 转融通融券卖出配套查询 3410
	TDX_ID_FUNC_ANS_ZRTRQMCPTCX,
	TDX_ID_FUNC_REQ_ZRTZJJRSQPTCX,	// 转融通资金借入申请配套查询 3412
	TDX_ID_FUNC_ANS_ZRTZJJRSQPTCX,
	TDX_ID_FUNC_REQ_ZRTGFJRSQPTCX,	// 转融通股份借入申请配套查询 3414
	TDX_ID_FUNC_ANS_ZRTGFJRSQPTCX,
	TDX_ID_FUNC_REQ_ZRTJRZQSQPTCX,	// 转融通借入展期申请配套查询 3416
	TDX_ID_FUNC_ANS_ZRTJRZQSQPTCX,
	TDX_ID_FUNC_REQ_ZRTTQGHSQPTCX,	// 转融通提前归还申请配套查询 3418
	TDX_ID_FUNC_ANS_ZRTTQGHSQPTCX,
	TDX_ID_FUNC_REQ_ZRTJRYWCDCX,	// 转融通借入业务撤单查询 3420
	TDX_ID_FUNC_ANS_ZRTJRYWCDCX,
	TDX_ID_FUNC_REQ_ZRTJRYWDRCX,	// 转融通借入业务当日查询 3422
	TDX_ID_FUNC_ANS_ZRTJRYWDRCX,
	TDX_ID_FUNC_REQ_ZRTJRYWLSCX,	// 转融通借入业务历史查询 3424
	TDX_ID_FUNC_ANS_ZRTJRYWLSCX,
	TDX_ID_FUNC_REQ_ZRTDRJRHYCX,	// 转融通当日借入合约查询 3426
	TDX_ID_FUNC_ANS_ZRTDRJRHYCX,
	TDX_ID_FUNC_REQ_ZRTWLJRHYCX,	// 转融通未了借入合约查询 3428
	TDX_ID_FUNC_ANS_ZRTWLJRHYCX,
	TDX_ID_FUNC_REQ_ZRTYLJRHYCX,	// 转融通已了借入合约查询 3430
	TDX_ID_FUNC_ANS_ZRTYLJRHYCX,
	TDX_ID_FUNC_REQ_ZRTZJCJSQPTCX,	// 转融通资金出借申请配套查询 3432
	TDX_ID_FUNC_ANS_ZRTZJCJSQPTCX,
	TDX_ID_FUNC_REQ_ZRTGFCJSQPTCX,	// 转融通股份出借申请配套查询 3434
	TDX_ID_FUNC_ANS_ZRTGFCJSQPTCX,
	TDX_ID_FUNC_REQ_ZRTZJCJQDPTCX,	// 转融通资金出借确定配套查询 3436
	TDX_ID_FUNC_ANS_ZRTZJCJQDPTCX,
	TDX_ID_FUNC_REQ_ZRTGFCJQDPTCX,	// 转融通股份出借确定配套查询 3438
	TDX_ID_FUNC_ANS_ZRTGFCJQDPTCX,
	TDX_ID_FUNC_REQ_ZRTCJYWCDCX,	// 转融通出借业务撤单查询 3440
	TDX_ID_FUNC_ANS_ZRTCJYWCDCX,
	TDX_ID_FUNC_REQ_ZRTCJYWDRCX,	// 转融通出借业务当日查询 3442
	TDX_ID_FUNC_ANS_ZRTCJYWDRCX,
	TDX_ID_FUNC_REQ_ZRTCJYWLSCX,	// 转融通出借业务历史查询 3444
	TDX_ID_FUNC_ANS_ZRTCJYWLSCX,
	TDX_ID_FUNC_REQ_ZRTCJTQSHPTCX,	// 转融通出借提前索还配套查询 3446
	TDX_ID_FUNC_ANS_ZRTCJTQSHPTCX,
	TDX_ID_FUNC_REQ_ZRTCJTYZQPTCX,	// 转融通出借同意展期配套查询 3448
	TDX_ID_FUNC_ANS_ZRTCJTYZQPTCX,
	TDX_ID_FUNC_REQ_ZRTQXFLCX,		// 转融通期限费率查询 3450
	TDX_ID_FUNC_ANS_ZRTQXFLCX,
	TDX_ID_FUNC_REQ_ZRTCJHYCX,		// 转融通出借合约查询 3452
	TDX_ID_FUNC_ANS_ZRTCJHYCX,
	TDX_ID_FUNC_REQ_ZRTCJLSHYCX,	// 转融通出借历史合约查询 3454
	TDX_ID_FUNC_ANS_ZRTCJLSHYCX,
	TDX_ID_FUNC_REQ_ZRTMCHKPTCX,	// 转融通卖出还款配套查询 3456
	TDX_ID_FUNC_ANS_ZRTMCHKPTCX,
	TDX_ID_FUNC_REQ_ZRTMRHQPTCX,	// 转融通买入还券配套查询 3458
	TDX_ID_FUNC_ANS_ZRTMRHQPTCX,
	TDX_ID_FUNC_REQ_ZRTXJHKPTCX,	// 转融通现金还款配套查询 3460
	TDX_ID_FUNC_ANS_ZRTXJHKPTCX,
	TDX_ID_FUNC_REQ_ZRTXQHQPTCX,	// 转融通现券还券配套查询 3462
	TDX_ID_FUNC_ANS_ZRTXQHQPTCX,
	TDX_ID_FUNC_REQ_ZRTKCJXXCX,		// 转融通可出借信息查询 3464
	TDX_ID_FUNC_ANS_ZRTKCJXXCX,
	TDX_ID_FUNC_REQ_ZRTJRTYSHPTCX,	// 转融通借入同意索还配套查询 3466
	TDX_ID_FUNC_ANS_ZRTJRTYSHPTCX,
	TDX_ID_FUNC_REQ_ZRTCJZHXXCX,	// 转融通出借账户信息查询 3468
	TDX_ID_FUNC_ANS_ZRTCJZHXXCX,

	// 其他
	TDX_ID_FUNC_REQ_XLYZT_KTQXZDDL,	// (新利)开通/取消自动代理配售/申购/配股 4100
	TDX_ID_FUNC_ANS_XLYZT_KTQXZDDL,
	TDX_ID_FUNC_REQ_XLYZT_KTHZPS,	// (新利)开通合作配售 4102
	TDX_ID_FUNC_ANS_XLYZT_KTHZPS,
	TDX_ID_FUNC_REQ_XLYZT_QXHZPS,	// (新利)取消合作配售 4104
	TDX_ID_FUNC_ANS_XLYZT_QXHZPS,
	TDX_ID_FUNC_REQ_XLYZT_KTHZHG,	// (新利)开通合作回购 4106
	TDX_ID_FUNC_ANS_XLYZT_KTHZHG,
	TDX_ID_FUNC_REQ_XLYZT_QXHZHG,	// (新利)取消合作回购 4108
	TDX_ID_FUNC_ANS_XLYZT_QXHZHG,
	TDX_ID_FUNC_REQ_XLYZT_KTHZSG,	// (新利)开通合作申购 4110
	TDX_ID_FUNC_ANS_XLYZT_KTHZSG,
	TDX_ID_FUNC_REQ_XLYZT_QXHZSG,	// (新利)取消合作申购 4112
	TDX_ID_FUNC_ANS_XLYZT_QXHZSG,
	TDX_ID_FUNC_REQ_XLYZT_DLGNCX,	// 查询代理开通信息 4114
	TDX_ID_FUNC_ANS_XLYZT_DLGNCX,
	TDX_ID_FUNC_REQ_SYLPM,			// 收益率排名 5000
	TDX_ID_FUNC_ANS_SYLPM,
	TDX_ID_FUNC_REQ_ZHRQ,			// 帐户融券 5002
	TDX_ID_FUNC_ANS_ZHRQ,
	TDX_ID_FUNC_REQ_RQCX,			// 融券查询 5004
	TDX_ID_FUNC_ANS_RQCX,
	TDX_ID_FUNC_REQ_ZHHQZQ,			// 帐户还券展期 5006
	TDX_ID_FUNC_ANS_ZHHQZQ,
	TDX_ID_FUNC_REQ_TCMONITOR,		// 交易中心监控 5008
	TDX_ID_FUNC_ANS_TCMONITOR,
	TDX_ID_FUNC_REQ_TSROUTING,		// TS路由 5010
	TDX_ID_FUNC_ANS_TSROUTING,
};

// 安全中心字典
const WORD tdxScntrStructInfo[]=
{
	// 安全中心协议
	TDX_ID_FUNC_REQ_CA_ZHSQ,		// CA账户申请 800
	TDX_ID_FUNC_ANS_CA_ZHSQ,
	TDX_ID_FUNC_REQ_CA_ZHCX,		// CA帐号查询 802
	TDX_ID_FUNC_ANS_CA_ZHCX,
	TDX_ID_FUNC_REQ_CA_ZHJY,		// CA账户校验 804
	TDX_ID_FUNC_ANS_CA_ZHJY,
	TDX_ID_FUNC_REQ_CA_TXMMXG,		// CA认证口令修改 806
	TDX_ID_FUNC_ANS_CA_TXMMXG,
	TDX_ID_FUNC_REQ_CA_TXMMCX,		// CA认证口令查询 808
	TDX_ID_FUNC_ANS_CA_TXMMCX,
	TDX_ID_FUNC_REQ_CA_ZSXZ,		// CA证书下载 810
	TDX_ID_FUNC_ANS_CA_ZSXZ,
	TDX_ID_FUNC_REQ_CA_ZSXZQR,		// CA证书下载确认 812
	TDX_ID_FUNC_ANS_CA_ZSXZQR,
	TDX_ID_FUNC_REQ_CA_ZTXM,		// CA状态修改 814
	TDX_ID_FUNC_ANS_CA_ZTXM,
	TDX_ID_FUNC_REQ_CA_ZSGX,		// CA证书更新 816
	TDX_ID_FUNC_ANS_CA_ZSGX,
	TDX_ID_FUNC_REQ_CA_YHFJCX,		// 用户分级查询 818
	TDX_ID_FUNC_ANS_CA_YHFJCX,
	TDX_ID_FUNC_REQ_CA_YHFJSQ,		// 用户分级申请 820
	TDX_ID_FUNC_ANS_CA_YHFJSQ,
	TDX_ID_FUNC_REQ_CA_HTTPYHFJCX,	// HTTP用户分级查询 822
	TDX_ID_FUNC_ANS_CA_HTTPYHFJCX,
	TDX_ID_FUNC_REQ_CA_ANONUSER,	// (注册)匿名用户 824
	TDX_ID_FUNC_ANS_CA_ANONUSER,

	TDX_ID_FUNC_REQ_CA_XJZT,			// 新建主题 826
	TDX_ID_FUNC_ANS_CA_XJZT,
	TDX_ID_FUNC_REQ_CA_CXZT,			// 查询主题 828
	TDX_ID_FUNC_ANS_CA_CXZT,
	TDX_ID_FUNC_REQ_CA_CXHF,			// 查询回复 830
	TDX_ID_FUNC_ANS_CA_CXHF,
	TDX_ID_FUNC_REQ_CA_HFZT,			// 回复主题 832
	TDX_ID_FUNC_ANS_CA_HFZT,
	TDX_ID_FUNC_REQ_CA_GBZT,			// (问题解决)关闭主题 834
	TDX_ID_FUNC_ANS_CA_GBZT,
	TDX_ID_FUNC_REQ_CA_USERMESSAGE,		// 用户(留言)信息 836
	TDX_ID_FUNC_ANS_CA_USERMESSAGE,
	TDX_ID_FUNC_REQ_CA_USERACTION,		// 匿名用户激活 838
	TDX_ID_FUNC_ANS_CA_USERACTION,
	TDX_ID_FUNC_REQ_CA_ANONYLOGIN,		// 匿名用户登录 840
	TDX_ID_FUNC_ANS_CA_ANONYLOGIN,
	TDX_ID_FUNC_REQ_CA_QUERYMSG,		// 查询是否有最新留言 842
	TDX_ID_FUNC_ANS_CA_QUERYMSG,
	TDX_ID_FUNC_REQ_CA_READED,			// 已阅读留言 844
	TDX_ID_FUNC_ANS_CA_READED,
	TDX_ID_FUNC_REQ_CA_NOTICEINFO,		// 用户公告及生日提醒信息 846
	TDX_ID_FUNC_ANS_CA_NOTICEINFO,
	TDX_ID_FUNC_REQ_CA_INFOFEEDBACK,	// 用户资讯信息反馈 848
	TDX_ID_FUNC_ANS_CA_INFOFEEDBACK,

	TDX_ID_FUNC_REQ_TQ_KHJY,			// TQ校验 860
	TDX_ID_FUNC_ANS_TQ_KHJY,
	TDX_ID_FUNC_REQ_UM_UBROKER,			// 西南证券用户投资顾问信息 862
	TDX_ID_FUNC_ANS_UM_UBROKER,

	TDX_ID_FUNC_REQ_CA_SYZC_GD,			// 试用(用户)注册 880
	TDX_ID_FUNC_ANS_CA_SYZC_GD,		
	TDX_ID_FUNC_REQ_CA_XXLR_GD,			// (详细)信息录入 882
	TDX_ID_FUNC_ANS_CA_XXLR_GD,		
	TDX_ID_FUNC_REQ_CA_SYJH_GD,			// 试用(用户)激活 884
	TDX_ID_FUNC_ANS_CA_SYJH_GD,		
	TDX_ID_FUNC_REQ_CA_ZHJY_GD,			// 账户校验 886
	TDX_ID_FUNC_ANS_CA_ZHJY_GD,		
	TDX_ID_FUNC_REQ_CA_DJCX_GD,			// 等级查询 888
	TDX_ID_FUNC_ANS_CA_DJCX_GD,		
	TDX_ID_FUNC_REQ_CA_KSJCX_GD,		// 可申(请)级(别)查询 890
	TDX_ID_FUNC_ANS_CA_KSJCX_GD,	
	TDX_ID_FUNC_REQ_CA_KHSQ_GD,			// 客户申请(级别) 892
	TDX_ID_FUNC_ANS_CA_KHSQ_GD,
	TDX_ID_FUNC_REQ_CA_YHZXQX_GD,		// 用户资讯权限 894
	TDX_ID_FUNC_ANS_CA_YHZXQX_GD,
	TDX_ID_FUNC_REQ_CA_YHQXZX,			// 用户权限注销 896
	TDX_ID_FUNC_ANS_CA_YHQXZX,
	TDX_ID_FUNC_REQ_CA_CXDLLS,			// 查询登录历史 898
	TDX_ID_FUNC_ANS_CA_CXDLLS,

	TDX_ID_FUNC_REQ_CA_AQGNSQ,			// 安全功能申请 4200
	TDX_ID_FUNC_ANS_CA_AQGNSQ,
	TDX_ID_FUNC_REQ_CA_AQGNCX,			// 安全功能撤销 4202
	TDX_ID_FUNC_ANS_CA_AQGNCX,
	TDX_ID_FUNC_REQ_CA_MMBHWTJY,		// 密码保护问题校验 4204
	TDX_ID_FUNC_ANS_CA_MMBHWTJY,
	TDX_ID_FUNC_REQ_CA_GETTZZB,			// 获取挑战坐标 4206
	TDX_ID_FUNC_ANS_CA_GETTZZB,
	TDX_ID_FUNC_REQ_CA_ZXJZK,			// 注销矩阵卡 4208
	TDX_ID_FUNC_ANS_CA_ZXJZK,
	TDX_ID_FUNC_REQ_CA_YLWT,			// 预留问题 4210
	TDX_ID_FUNC_ANS_CA_YLWT,
	TDX_ID_FUNC_REQ_CA_CERRAREQ,		// 证书申请 4212
	TDX_ID_FUNC_ANS_CA_CERRAREQ,
	TDX_ID_FUNC_REQ_CA_CERAUDIT,		// 证书审核 4214
	TDX_ID_FUNC_ANS_CA_CERAUDIT,
	TDX_ID_FUNC_REQ_CA_CERDOWNLOAD,		// 证书下载 4216
	TDX_ID_FUNC_ANS_CA_CERDOWNLOAD,
	TDX_ID_FUNC_REQ_CA_CERDLCONFIRM,	// 证书下载确认 4218
	TDX_ID_FUNC_ANS_CA_CERDLCONFIRM,
	TDX_ID_FUNC_REQ_CA_ADDYHXX,			// 添加用户信息 4220
	TDX_ID_FUNC_ANS_CA_ADDYHXX,
	TDX_ID_FUNC_REQ_CA_XGYHXX,			// 修改用户信息 4222
	TDX_ID_FUNC_ANS_CA_XGYHXX,
	TDX_ID_FUNC_REQ_CA_CXYHXX,			// 查询用户信息 4224
	TDX_ID_FUNC_ANS_CA_CXYHXX,
	TDX_ID_FUNC_REQ_CA_GETYZM,			// 获取手机验证码 4226
	TDX_ID_FUNC_ANS_CA_GETYZM,
	TDX_ID_FUNC_REQ_CA_YZMJY,			// 验证码校验 4228
	TDX_ID_FUNC_ANS_CA_YZMJY,
	TDX_ID_FUNC_REQ_OTHERCA_BASEFUN,	// 其他安全认证校验 4230
	TDX_ID_FUNC_ANS_OTHERCA_BASEFUN,
	TDX_ID_FUNC_REQ_CA_MMBHWTCX,		// 查询密码保护问题 4232
	TDX_ID_FUNC_ANS_CA_MMBHWTCX,
	TDX_ID_FUNC_REQ_CA_XGMMBHWT,		// 修改密码保护问题 4234
	TDX_ID_FUNC_ANS_CA_XGMMBHWT,
	TDX_ID_FUNC_REQ_CA_XGYLWT,			// 修改预留问题 4236
	TDX_ID_FUNC_ANS_CA_XGYLWT,
	TDX_ID_FUNC_REQ_CA_PWDPROTQUEQU,	// 密码保护问题列表查询 4238
	TDX_ID_FUNC_ANS_CA_PWDPROTQUEQU,
	TDX_ID_FUNC_REQ_CA_APPLYPWDQA,		// 申请密码保护问题 4240
	TDX_ID_FUNC_ANS_CA_APPLYPWDQA,
	TDX_ID_FUNC_REQ_CA_BINDMACHINE,		// 申请机器特征码绑定 4242
	TDX_ID_FUNC_ANS_CA_BINDMACHINE,
	TDX_ID_FUNC_REQ_CA_QUEBINDINFO,		// 查询绑定信息 4244
	TDX_ID_FUNC_ANS_CA_QUEBINDINFO,
	TDX_ID_FUNC_REQ_CA_CANCELBIND,		// 取消绑定信息 4246
	TDX_ID_FUNC_ANS_CA_CANCELBIND,
	TDX_ID_FUNC_REQ_CA_SAFEMODQUE,		// 安全申请状态查询 4248
	TDX_ID_FUNC_ANS_CA_SAFEMODQUE,
	TDX_ID_FUNC_REQ_CA_ABUSERLV,		// 核销用户安全级别 4248
	TDX_ID_FUNC_ANS_CA_ABUSERLV,
	TDX_ID_FUNC_REQ_CA_USERLOGOUT,		// 用户离线 4252
	TDX_ID_FUNC_ANS_CA_USERLOGOUT,
	TDX_ID_FUNC_REQ_CA_USERALIVE,		// 用户在线心跳 4254
	TDX_ID_FUNC_ANS_CA_USERALIVE,
	TDX_ID_FUNC_REQ_CA_CANCELLV,		// 取消用户级别 4256
	TDX_ID_FUNC_ANS_CA_CANCELLV,
	TDX_ID_FUNC_REQ_CA_GETPROINFO,		// 获取产品名称 4258
	TDX_ID_FUNC_ANS_CA_GETPROINFO,
	TDX_ID_FUNC_REQ_CA_REGUSER,			// 注册用户 4280
	TDX_ID_FUNC_ANS_CA_REGUSER,
	TDX_ID_FUNC_REQ_CA_ALTERREGPWD,		// 修改注册密码 4283
	TDX_ID_FUNC_ANS_CA_ALTERREGPWD,
	TDX_ID_FUNC_REQ_CA_SSO,				// 单点登陆令牌操作 4284
	TDX_ID_FUNC_ANS_CA_SSO,
	TDX_ID_FUNC_REQ_CA_SSOYHXX,			// 单点登陆根据令牌取用户信息 4286
	TDX_ID_FUNC_ANS_CA_SSOYHXX,
	TDX_ID_FUNC_REQ_CA_CERDEL,			// 证书吊销
	TDX_ID_FUNC_ANS_CA_CERDEL,
	TDX_ID_FUNC_REQ_CA_OTPSYN,			//	OTP同步
	TDX_ID_FUNC_ANS_CA_OTPSYN,
	TDX_ID_FUNC_REQ_CA_CHECKRECORD,		// 检查数据一致性
	TDX_ID_FUNC_ANS_CA_CHECKRECORD,
	TDX_ID_FUNC_REQ_CA_PAAUTH,			// 用户认证 4284
	TDX_ID_FUNC_ANS_CA_PAAUTH,
	TDX_ID_FUNC_REQ_CA_ACCREPORT,		// 投顾诊断报告
	TDX_ID_FUNC_ANS_CA_ACCREPORT,
	TDX_ID_FUNC_REQ_CA_OTPTEMP,			// OTP豁免
	TDX_ID_FUNC_ANS_CA_OTPTEMP,
	TDX_ID_FUNC_REQ_OTHERCA_GETYZM,		// 获取核新手机验证码 4300
	TDX_ID_FUNC_ANS_OTHERCA_GETYZM,
	TDX_ID_FUNC_REQ_OPMYSTOCK,			// 自选股上传下载 4302
	TDX_ID_FUNC_ANS_OPMYSTOCK,
	TDX_ID_FUNC_REQ_FETCHPWD,			// 找回用户密码 4304
	TDX_ID_FUNC_ANS_FETCHPWD,			
	TDX_ID_FUNC_REQ_FETCHUSERACCOUNT,	// 找回用户帐号 4306
	TDX_ID_FUNC_ANS_FETCHUSERACCOUNT,
	TDX_ID_FUNC_REQ_QUERYSCORE,			// 积分查询 4308
	TDX_ID_FUNC_ANS_QUERYSCORE,	
	TDX_ID_FUNC_REQ_QUERYREGUDATA,		// 注册用户信息查询 4310
	TDX_ID_FUNC_ANS_QUERYREGUDATA,
	TDX_ID_FUNC_REQ_GETACTIVECODE,		// 获取激活码 4312
	TDX_ID_FUNC_ANS_GETACTIVECODE,
	TDX_ID_FUNC_REQ_QRYSCFUNC,			// 安全功能查询	4500
	TDX_ID_FUNC_ANS_QRYSCFUNC,
	TDX_ID_FUNC_REQ_SWITCHSCFUNC,		// 开启/关闭安全功能 4502
	TDX_ID_FUNC_ANS_SWITCHSCFUNC,
	TDX_ID_FUNC_REQ_UNIAUTH,			// 统一认证 4504
	TDX_ID_FUNC_ANS_UNIAUTH,
	TDX_ID_FUNC_REQ_REQAPWD,			// 申请认证口令 4506
	TDX_ID_FUNC_ANS_REQAPWD,
	TDX_ID_FUNC_REQ_MODAPWD,			// 修改认证口令 4508
	TDX_ID_FUNC_ANS_MODAPWD,
	TDX_ID_FUNC_REQ_RESETAPWD,			// 重置认证口令 4510
	TDX_ID_FUNC_ANS_RESETAPWD,
	TDX_ID_FUNC_REQ_SYNOTP,				// 同步OTP 4512
	TDX_ID_FUNC_ANS_SYNOTP,
	TDX_ID_FUNC_REQ_GETCSIGNKEY,		// 获取证书签名码 4514
	TDX_ID_FUNC_ANS_GETCSIGNKEY,
	TDX_ID_FUNC_REQ_UPDCERT,			// 更新证书 4516
	TDX_ID_FUNC_ANS_UPDCERT,
	TDX_ID_FUNC_REQ_GETCCODE,			// 获取手机动态码 4518
	TDX_ID_FUNC_ANS_GETCCODE,
	TDX_ID_FUNC_REQ_PERMITMACHINE,		// 授权计算机 4520
	TDX_ID_FUNC_ANS_PERMITMACHINE,
	TDX_ID_FUNC_REQ_FREEMACHINE,		// 解除计算机授权 4522
	TDX_ID_FUNC_ANS_FREEMACHINE,
	TDX_ID_FUNC_REQ_QRYPERMITION,		// 查询授权 4524
	TDX_ID_FUNC_ANS_QRYPERMITION,
	TDX_ID_FUNC_REQ_UPDSELFINFO,		// 更新预留信息 4526
	TDX_ID_FUNC_ANS_UPDSELFINFO,
	TDX_ID_FUNC_REQ_QRYUSERCOMMON,		// 查询用户常用信息 4528
	TDX_ID_FUNC_ANS_QRYUSERCOMMON,
	TDX_ID_FUNC_REQ_QRYUDATA,			// 用户资料查询 4530
	TDX_ID_FUNC_ANS_QRYUDATA,
	TDX_ID_FUNC_REQ_UPDUDATA,			// 更新用户资料 4532
	TDX_ID_FUNC_ANS_UPDUDATA,
	TDX_ID_FUNC_REQ_QRYIMPOTOP,			// 关键操作查询 4534
	TDX_ID_FUNC_ANS_QRYIMPOTOP,
	TDX_ID_FUNC_REQ_RCDIMPOTOP,			// 关键操作记录 4536
	TDX_ID_FUNC_ANS_RCDIMPOTOP,
	TDX_ID_FUNC_REQ_QRYAUTHHIS,			// 认证历史查询 4538
	TDX_ID_FUNC_ANS_QRYAUTHHIS,
	TDX_ID_FUNC_REQ_REQQAPROT,			// 密码保护问题申请 4540
	TDX_ID_FUNC_ANS_REQQAPROT,
	TDX_ID_FUNC_REQ_MODQAPROT,			// 密码保护问题修改 4542
	TDX_ID_FUNC_ANS_MODQAPROT,
	TDX_ID_FUNC_REQ_AUTHQAPROT,			// 密码保护校验 4544
	TDX_ID_FUNC_ANS_AUTHQAPROT,
	TDX_ID_FUNC_REQ_RESVPWD,			// 应急密码 4546
	TDX_ID_FUNC_ANS_RESVPWD,
	TDX_ID_FUNC_REQ_CONSIS,				// 请求服务器签名信息
	TDX_ID_FUNC_ANS_CONSIS,
};


// 日志查看字典
const WORD tdxRZStructInfo[]=
{	
	TDX_ID_FUNC_REQ_KHJY,			// 客户校验 100
	TDX_ID_FUNC_ANS_KHJY,	
	TDX_ID_FUNC_REQ_CACHE,			// 取缓存信息 112
	TDX_ID_FUNC_ANS_CACHE,
	TDX_ID_FUNC_REQ_GDCX,			// 股东查询 1122
	TDX_ID_FUNC_ANS_GDCX,
	TDX_ID_FUNC_REQ_YHXX,			// 银行信息 908
	TDX_ID_FUNC_ANS_YHXX,
	TDX_ID_FUNC_REQ_XGMM,			// 修改密码 106
	TDX_ID_FUNC_ANS_XGMM,

	TDX_ID_FUNC_REQ_RZ_KHCZJLCX,	// 客户操作记录查询 1002
	TDX_ID_FUNC_ANS_RZ_KHCZJLCX,
	TDX_ID_FUNC_REQ_RZ_ZHSQ,		// 账号申请 1004
	TDX_ID_FUNC_ANS_RZ_ZHSQ,
	TDX_ID_FUNC_REQ_RZ_ZHDJJD,		// 账号冻结解冻 1006
	TDX_ID_FUNC_ANS_RZ_ZHDJJD,
	TDX_ID_FUNC_REQ_RZ_CXTJFX,		// 查询统计分析 1008
	TDX_ID_FUNC_ANS_RZ_CXTJFX,
	TDX_ID_FUNC_REQ_RZ_QDYGBCX,		// 启动与关闭查询 1010
	TDX_ID_FUNC_ANS_RZ_QDYGBCX,
	TDX_ID_FUNC_REQ_RZ_HTFMCD,		// 后台繁忙程度 1012
	TDX_ID_FUNC_ANS_RZ_HTFMCD,
	TDX_ID_FUNC_REQ_RZ_HTCFHCX,		// 后台超负荷查询 1014
	TDX_ID_FUNC_ANS_RZ_HTCFHCX,
	TDX_ID_FUNC_REQ_RZ_FXIPPM,		// 风险IP排名 1016
	TDX_ID_FUNC_ANS_RZ_FXIPPM,
	TDX_ID_FUNC_REQ_RZ_FXZH,		// 风险账号 1018
	TDX_ID_FUNC_ANS_RZ_FXZH,
	TDX_ID_FUNC_REQ_RZ_FXXXXX,		// 风险账号 1020
	TDX_ID_FUNC_ANS_RZ_FXXXXX,
	TDX_ID_FUNC_REQ_RZ_HTFMCDXX,	// 后台繁忙程度详细 1022
	TDX_ID_FUNC_ANS_RZ_HTFMCDXX,
	TDX_ID_FUNC_REQ_RZ_TCIP,		// 交易中心IP 1024
	TDX_ID_FUNC_ANS_RZ_TCIP,
};


//---------------------------------------------------------------------------
// Part.IV 结构对应的字段定义
//---------------------------------------------------------------------------


// 示例(普通)
const WORD tdxFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号
	TDX_ID_ZHLB,				// 帐号类别
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 委托方式
};

// 示例(开放式基金)
const WORD tdxKFSJJFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号
	TDX_ID_ZHLB,				// 帐号类别
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// 基金公司代码
	TDX_ID_KFSJJ_JJZH,			// 基金帐号
	TDX_ID_KFSJJ_JJDM,			// 基金代码
};

// 账号预处理 94
const WORD tdxZHYCLFieldReq[]=
{
	TDX_ID_XT_LOGINID,			// 登录帐号(股东代码资金帐号等校验帐号)
	TDX_ID_XT_LOGINPASSWD,		// 登录密码(加密字段)
	TDX_ID_XT_COMMPASSWD,		// 通讯密码(柜台登录用通讯密码)
	TDX_ID_XT_LOGINTYPE,		// 登录帐号类别
	TDX_ID_XT_AUTH_MODE,		// (柜台,扩充)认证模式(取值见"安全级别定义")
	TDX_ID_XT_AUTH_INFO,		// (柜台,扩充)认证信息
	TDX_ID_XT_CLITYPE,			// 客户类型
	TDX_ID_XT_CLIVER,			// 客户端版本

	TDX_ID_CZBZ,				// 操作标志
	TDX_ID_XT_PREPASSWORD0,		// 预处理密码0
	TDX_ID_XT_PREPASSWORD1,		// 预处理密码1
	TDX_ID_XT_PREPASSWORD2,		// 预处理密码2
	TDX_ID_XT_PREPASSWORD3,		// 预处理密码3
	TDX_ID_XT_PREPASSWORD4,		// 预处理密码4
	TDX_ID_XT_PREPARAM0,		// 预处理参数0
	TDX_ID_XT_PREPARAM1,		// 预处理参数1
	TDX_ID_XT_PREPARAM2,		// 预处理参数2
	TDX_ID_XT_PREPARAM3,		// 预处理参数3
	TDX_ID_XT_PREPARAM4,		// 预处理参数4
	TDX_ID_XT_PREPARAM5,		// 预处理参数5
	TDX_ID_XT_PREPARAM6,		// 预处理参数6
	TDX_ID_XT_PREPARAM7,		// 预处理参数7
	TDX_ID_XT_PREPARAM8,		// 预处理参数8
	TDX_ID_XT_PREPARAM9,		// 预处理参数9
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
};

// 登录预处理 96
const WORD tdxDLYCLFieldReq[]=
{
	TDX_ID_XT_LOGINID,			// 登录帐号(股东代码资金帐号等校验帐号)
	TDX_ID_XT_LOGINPASSWD,		// 登录密码(加密字段)
	TDX_ID_XT_COMMPASSWD,		// 通讯密码(柜台登录用通讯密码)
	TDX_ID_XT_LOGINTYPE,		// 登录帐号类别
	TDX_ID_XT_AUTH_MODE,		// (柜台,扩充)认证模式(取值见"安全级别定义")
	TDX_ID_XT_AUTH_INFO,		// (柜台,扩充)认证信息
	TDX_ID_XT_CLITYPE,			// 客户类型
	TDX_ID_XT_CLIVER,			// 客户端版本

	TDX_ID_CZBZ,				// 操作标志(0/(-1)--正常处理,1--获取随机码)
	TDX_ID_XT_MACHINEINFO,		// 机器信息(格式同"集成客户校验 98"/"客户校验 100")
	TDX_ID_XT_MACHINECODE,		// 机器特征码(针对不同券商格式化后的字符串)
	TDX_ID_XT_CLIENTINVERSION,	// 客户端内部版本
	TDX_ID_XT_VERSIONSTRING,	// 版本字符串
};

// 集成客户校验 98
const WORD tdxJCKHJYFieldReq[]=
{
	TDX_ID_XT_LOGINID,			// 登录帐号(股东代码资金帐号等校验帐号)
	TDX_ID_XT_LOGINPASSWD,		// 登录密码(加密字段)
	TDX_ID_XT_COMMPASSWD,		// 通讯密码(柜台登录用通讯密码)
	TDX_ID_XT_LOGINTYPE,		// 登录帐号类别
	TDX_ID_XT_AUTH_MODE,		// (柜台,扩充)认证模式(取值见"安全级别定义")
	TDX_ID_XT_AUTH_INFO,		// (柜台,扩充)认证信息
	TDX_ID_XT_CLITYPE,			// 客户类型
	TDX_ID_XT_CLIVER,			// 客户端版本
                            	
	TDX_ID_KHMC,				// (网上交易开通)客户名称
	TDX_ID_ZJZH,				// (网上交易开通)资金帐号
	TDX_ID_ZJHM,				// (网上交易开通)证件号码
	TDX_ID_MOBILEPHONE,			// (网上交易开通)移动电话
	TDX_ID_USERPHONE,			// (网上交易开通)固定电话
	TDX_ID_USEREMAIL,			// (网上交易开通)电子邮件
	TDX_ID_SHGD,				// (网上交易开通)上海股东代码
	TDX_ID_SZGD,				// (网上交易开通)深圳股东代码
                            	
	TDX_ID_XT_GTLB,				// 柜台类别(0:默认 1:信用交易 2:股票 3:基金 4:商品期货 5:金融期货 6:港股),原信用交易标识字段
	TDX_ID_XT_RECONNECTFLAG,	// 断线重联标志
	TDX_ID_XT_QUERYMODE,		// 查询模式标志
	TDX_ID_XT_VIPFLAG,			// VIP标志
	TDX_ID_XT_MACHINEINFO,		// 机器信息(格式[大项分号分隔,子项逗号分隔]: 内网IP;机器名;用户名;内存;CPU信息;CPUID;系统版本;IP列表;MAC地址列表;硬盘序列号列表;BIOS版本...)
	TDX_ID_XT_LIMITMODE,		// 受限模式(1--支持受限模式,0/其它--不支持受限模式)
	TDX_ID_XT_SESSION,			// 会话信息
	TDX_ID_YYB,					// (发生)营业部
	TDX_ID_CZBZ,				// 操作标志(0/(-1)--正常登陆,1--获取短信认证码)
	TDX_ID_XT_REALCLIENTVERSION,// 内部客户端版本
	TDX_ID_XT_REDIRECTFLAG,		// 重定向标志(1--重定向登录,其他--正常)
	TDX_ID_XT_REDIRECTINFO,		// 重定向信息(重定向标志=1时有效)
	TDX_ID_XT_MULTINITICE,		// 多提示信息
	TDX_ID_XT_LOGINENTERPARAM,	// 登录输入参数
	TDX_ID_XT_MACHINECODE,		// 机器特征码(针对不同券商格式化后的字符串)
	TDX_ID_XT_CLIENTINVERSION,	// 客户端内部版本
	TDX_ID_XT_VERSIONSTRING,	// 版本字符串
};

// 集成客户校验 99
const WORD tdxJCKHJYFieldAns[]=
{
	TDX_ID_XT_FUNCID,			// 应答包含的功能ID
	TDX_ID_XT_FUNCDICTTAG,		// 应答包含的功能字典标识
	TDX_ID_XT_FUNCCONTENT,		// 应答包含的功能内容
	TDX_ID_XT_RESERVED,			// 调试信息
};

// 客户校验 100
const WORD tdxKHJYFieldReq[]=
{
	TDX_ID_KHH,					// 客户号(股东代码资金帐号等校验帐号)
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// (网上交易开通)资金帐号
	TDX_ID_ZHLB,				// 帐号类别(登录帐号类别)
	TDX_ID_GDDM,				// 股东代码(等于TDX_ID_KHH内容)
	TDX_ID_XT_CLITYPE,			// 客户端类型
	TDX_ID_XT_AUTH_MODE,		// (柜台,扩充)认证模式(取值见"安全级别定义")
	TDX_ID_XT_AUTH_INFO,		// (柜台,扩充)认证信息
                            	
	TDX_ID_KHMC,				// (网上交易开通)客户名称
	TDX_ID_ZJHM,				// (网上交易开通)证件号码
	TDX_ID_MOBILEPHONE,			// (网上交易开通)移动电话
	TDX_ID_USERPHONE,			// (网上交易开通)固定电话
	TDX_ID_USEREMAIL,			// (网上交易开通)电子邮件
	TDX_ID_SHGD,				// (网上交易开通)上海股东代码
	TDX_ID_SZGD,				// (网上交易开通)深圳股东代码
	TDX_ID_TXMM,				// (登录)通讯密码
                            	
	TDX_ID_BANKCODE,			// (招行卡号,废弃)银行代码
	TDX_ID_BANKYYB,				// (招行卡号,废弃)银行营业部代码(实际营业部代码)
	TDX_ID_BANKGDTYPE,			// (招行卡号,废弃)银行股东类别
                            	
	TDX_ID_XT_GTLB,				// 客户类别(0:默认 1:信用交易 2:股票 3:基金 4:商品期货 5:金融期货 6:港股),原信用交易标识字段
	TDX_ID_XT_RECONNECTFLAG,	// 断线重联标志
	TDX_ID_XT_QUERYMODE,		// 查询模式
	TDX_ID_XT_VIPFLAG,			// VIP标志
	TDX_ID_XT_MACHINEINFO,		// 机器信息(格式[大项分号分隔,子项逗号分隔]: 内网IP;机器名;用户名;内存;CPU信息;CPUID;系统版本;IP列表;MAC地址列表;硬盘序列号列表;BIOS版本;...)
	TDX_ID_XT_LIMITMODE,		// 受限模式(1--支持受限模式,0/其它--不支持受限模式)
	TDX_ID_XT_SESSION,			// 会话信息
	TDX_ID_XT_REDIRECTFLAG,		// 重定向标志(1--重定向登录,其他--正常)
	TDX_ID_XT_REDIRECTINFO,		// 重定向信息(重定向标志=1时有效)
	TDX_ID_XT_MOBILEMACHINEINFO,// 手机机器信息
	TDX_ID_XT_LOGINENTERPARAM,	// 登录输入参数
	TDX_ID_XT_MACHINECODE,		// 机器特征码(针对不同券商格式化后的字符串)
	TDX_ID_XT_CLIENTINVERSION,	// 客户端内部版本
	TDX_ID_XT_VERSIONSTRING,	// 版本字符串
};                          	

// 查询行情 102
const WORD tdxCXHQFieldReq[]=
{
	TDX_ID_KHH,					// 客户号(股东代码资金帐号等校验帐号)
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (期货)帐号类别
	TDX_ID_GDDM,				// (期货)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_SCFLAG,				// (保留)市场代码
	TDX_ID_ZQDM,				// 证券代码
	TDX_ID_HYDM,				// (废弃,期货)合约代码(期货使用)
	TDX_ID_CZBZ,				// 操作标志(1--返回证券代码相关提示信息[TDX_ID_RETINFO],默认--0)
};

// 资金余额 104
const WORD tdxZJYEFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式
	TDX_ID_BZ,					// (可选)币种(CZBZ=1时有效)
	TDX_ID_CZBZ,				// (可选)操作标志(1--[国信证券]可取资金查询,0/...--可用资金查询)
	TDX_ID_XT_MODE,				// 模式(按位置标志)
};

// 修改(交易)密码 106
const WORD tdxXGMMFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式
	
	TDX_ID_XJYMM,				// 新交易密码
	TDX_ID_ZJMM,				// 资金密码(港股使用)
	TDX_ID_XZJMM,				// 新资金密码(港股使用)
	TDX_ID_XT_SESSION,			// 会话信息
};

// 修改资金密码 108
const WORD tdxXGZJMMFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_ZJMM,				// 资金密码
	TDX_ID_XZJMM,				// 新资金密码
	TDX_ID_XT_PARAM,			// 参数
};

// 计算可买(卖)数 110
const WORD tdxJSKMSFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_ZQDM,				// 证券代码
	TDX_ID_MMBZ,				// 买卖标志(0-限价买入 1-限价卖出 'C'-市价买入 ...)
	TDX_ID_NOW,					// 委托价格
	TDX_ID_KYZJ,				// 可用资金
	TDX_ID_WTFS,				// 委托类型(市价类型)

	TDX_ID_HYDM,				// (废弃,期货)合约代码
	TDX_ID_KPBZ,				// (期货)开平标志
	TDX_ID_TBBZ,				// (期货)投保标志
	TDX_ID_XWDM,				// (期货)席位代码

	TDX_ID_DFXWDM,				// 对方席位代码
	TDX_ID_DFZJZH,				// 对方资金帐号
	TDX_ID_DFGDDM,				// 对方股东代码
	TDX_ID_DFZHLB,				// 对方帐号类别

	TDX_ID_CZBZ,				// 操作标志(0--普通操作,1--批量操作,2--忽略买卖标志,3--只返回费用信息,4--转融通开仓买入,5--转融通平仓卖出,6--转融通转换,其他--未定)
	TDX_ID_DFFZDM,				// 对方分支代码
	TDX_ID_DFKHDM,				// 对方客户代码
	TDX_ID_DFMM,				// 对方密码

	TDX_ID_SBMRJ,				// 申报买入价(CZBZ=2时有效)
	TDX_ID_SBMCJ,				// 申报卖出价(CZBZ=2时有效)
	TDX_ID_XT_CHECKRISKFLAG,	// 检查风险标志
	TDX_ID_WTBH,				// 委托编号
	TDX_ID_XT_FUNCTIONVERSION,	// 功能版本
	TDX_ID_WTRQ,				// 委托日期
};

// 取缓存信息 112
const WORD tdxCACHEFieldReq[]=
{
	TDX_ID_KHH,					// 客户号(股东代码资金帐号等校验帐号)
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(登录帐号类别)
	TDX_ID_GDDM,				// 股东代码(等于TDX_ID_KHH内容)
	TDX_ID_OP_WTFS,				// 操作方式
	
	TDX_ID_BANKCODE,			// (招行卡号,废弃)银行代码
	TDX_ID_BANKYYB,				// (招行卡号,废弃)银行营业部代码(实际营业部代码)
	TDX_ID_BANKGDTYPE,			// (招行卡号,废弃)银行股东类别
	
	TDX_ID_XT_GTLB,				// 客户类别(0:默认 1:信用交易 2:股票 3:基金 4:商品期货 5:金融期货 6:港股),原信用交易标识字段
	TDX_ID_TXMM,				// 通信密码
	TDX_ID_XT_QUERYMODE,		// 查询模式
	TDX_ID_YYB,					// 营业部(招商使用,送发起营业部)
	TDX_ID_XT_MACHINEINFO,		// 机器信息(格式[大项分号分隔,子项逗号分隔]: 内网IP;机器名;用户名;内存;CPU信息;CPUID;系统版本;IP列表;MAC地址列表;硬盘序列号列表;BIOS版本;...)
	TDX_ID_XT_MACHINECODE,		// 机器特征码(针对不同券商格式化后的字符串)
};

// 修改关联资金帐号 114
const WORD tdxXGGLZJZHFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式
};

// 客户注销 116
const WORD tdxKHZXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 委托方式
};

// 订阅取消对帐单(邮寄) 118
const WORD tdxDYQXDZDFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(保留)
	TDX_ID_GDDM,				// 股东代码(保留)
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_CZBZ,				// 操作标志(0:开通,1:取消,2:查询)
	TDX_ID_DZDLX,				// 对帐单类型(0:月对帐单)
	TDX_ID_POSTALCODE,			// 邮政编码
	TDX_ID_USERADDRESS,			// 通讯地址
};


// 委托冻结资金 120
const WORD tdxWTDJZJFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式
};

// 打印对帐单 122
const WORD tdxPRINTDZDFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式
	
	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_CZBZ,				// 操作标志(0:正常对帐单,1:汇总对帐单,2 期货结算单,3 格式对帐单[只返回一条记录--对帐单格式配置文件])
	TDX_ID_BZ,					// 币种(一般不用)
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期(期货不用这个)
	
	TDX_ID_LX,					// (期货)(帐单)类型(0:日结算单,1:月结算单)
};

// 打印汇总对帐单 124 (保留)
const WORD tdxPRINTHZDZDFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式
	
	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_BZ,					// 币种(一般不用)
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

// 打印交割单 126 (营业部用)
const WORD tdxPRINTJGDFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_BZ,					// (保留)币种
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 修改认证口令 128
const WORD tdxXGTXMMFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_TXMM,				// 通讯密码
	TDX_ID_XTXMM,				// 新通讯密码
};

// 帐号解冻 130
const WORD tdxZHJDFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式
};

// 资金归集 132
const WORD tdxZJGJFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_BZ,					// 币种

	TDX_ID_CZBZ,				// 操作标志(1--计划转帐,其它--实时转帐)
	TDX_ID_WTRQ,				// 委托日期(计划转帐日期,CZBZ=1时有效)
	TDX_ID_WTSJ,				// 委托时间(计划转帐时间,CZBZ=1时有效)
	TDX_ID_ZJMM,				// 资金密码
	TDX_ID_ZCZJZH,				// 转出资金帐号(逗号分隔的账号列表,空表示所有账号向指定账号归集)
	TDX_ID_ZRZJZH,				// 转入资金帐号(转入的账号,空表示转入主账号)
};

// 资金帐号间转帐 134
const WORD tdxZJZHJZZFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_ZCZJZH,				// 转出资金帐号
	TDX_ID_ZRZJZH,				// 转入资金帐号
	TDX_ID_BZ,					// 币种
	TDX_ID_YZZZ_ZZJE,			// 转帐金额
	TDX_ID_ZJMM,				// 资金密码(转出资金帐号)

	TDX_ID_CZBZ,				// 操作标志(1--计划转帐,其它--实时转帐)
	TDX_ID_WTRQ,				// 委托日期(计划转帐日期,CZBZ=1时有效)
	TDX_ID_WTSJ,				// 委托时间(计划转帐时间,CZBZ=1时有效)
};

// 提交问卷结果 136
const WORD tdxTJWJJGFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_LX,					// 类型(0--基金风险评估)
	TDX_ID_RETINFO,				// 返回信息(用于提交客户问卷结果,各项之间以分号";"分割)
	TDX_ID_CZBZ,				// 操作标志(0--正常提交,1--取消提交问卷[后台进行默认处理])
	TDX_ID_XT_FUNCTIONVERSION,	// 功能版本	
};

// 获取问卷内容 138
const WORD tdxHQWJNRFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_LX,					// 类型(0--基金风险评估)
	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_XT_FUNCTIONVERSION,	// 功能版本
};

// 获取帐号状态标志 140
const WORD tdxHQZHZTBZFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_LX,					// 类型(0--基金风险评估)
	TDX_ID_CZBZ,				// 操作标志(保留)
	TDX_ID_XXLX,				// 信息类型
};

// 处理查询密码 142
const WORD tdxCLCXMMFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_CZBZ,				// 操作标志(0--停用,1--开启,2--修改)
	TDX_ID_ZJMM,				// 资金密码(查询密码,CZBZ=2有效)
	TDX_ID_XZJMM,				// 新资金密码(新查询密码,CZBZ=1/2有效)
};

// 推送注册 144
const WORD tdxTSZCFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// (保留)资金帐号
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式
};

// 推送注销 146
const WORD tdxTSZXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// (保留)资金帐号
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式
};

// 子帐号查询 148
const WORD tdxZZHCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// (保留)资金帐号
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式
};

// 处理认证信息 150
const WORD tdxCLRZXXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_CZBZ,				// 操作标志(0--停用,1--开启,2--修改,3--绑定申请,4--撤销绑定,5--临时解除,6--延期)
	TDX_ID_XT_AUTH_MODE,		// 认证模式(取值见"安全级别定义")
	TDX_ID_XT_AUTH_INFO,		// 认证信息
	TDX_ID_XT_AUTH_NEWINFO,		// 认证新信息
	TDX_ID_XT_MACHINEINFO,		// 机器信息
	TDX_ID_XT_PARAM,			// 参数(填充相关数据,各接口自行约定)
	TDX_ID_XT_MOBILECHECKCODE,	// 手机校验码
	TDX_ID_XT_CN,				// CN
	TDX_ID_XT_SN,				// SN
	TDX_ID_XT_DN,				// DN
	TDX_ID_XT_SLOTID,			// 证书容器ID
	TDX_ID_XT_CID,				// 证书厂商ID
};

// 认证信息查询 152
const WORD tdxRZXXCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_AUTH_MODE,		// 安全中心验证方式
	TDX_ID_MOBILEPHONE,			// 手机号码
};

// 客户基本信息查询 154
const WORD tdxKHJBXXCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_ZJLB,				// 证件类别
	TDX_ID_ZJHM,				// 证件号码
};

// 电子合同签约 156
const WORD tdxDZHTQYFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_LX,					// 类型(电子合同类型,各接口/券商自行定义)
	TDX_ID_CZBZ,				// 操作标志(0--签约,1--取消,其他--保留)
	TDX_ID_ZQDM,				// 证券代码
	TDX_ID_XT_PARAM,			// 参数(各接口自定义)
	TDX_ID_XT_CHECKRISKFLAG,	// 检查风险标志
	TDX_ID_KFSJJ_JYJE,			// 交易金额(资金保留额度)
	TDX_ID_DZDJSFS,				// 对帐单寄送方式( 1--短信,2--邮寄,3--电子邮箱)
};

// 电子合同签约查询 158
const WORD tdxDZHTQYCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_LX,					// 类型(-1/255--全部,其他--指定类型)
	TDX_ID_ZQDM,				// 证券代码(空--全部,其他--指定证券代码)
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

// 电子合同列表查询 160
const WORD tdxDZHTLBCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_ZQDM,				// 证券代码(空--全部,其他--指定证券代码)
	TDX_ID_CZBZ,				// 操作标志(0--全部,其他--各券商自定义)
};

// 电子合同信息查询 162
const WORD tdxDZHTXXCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_LX,					// 类型(必须指定类型)
	TDX_ID_ZQDM,				// 证券代码
};

// 认证流水查询 164
const WORD tdxRZLSCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_AUTH_MODE,		// 安全中心验证方式((-1)--全部)
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 客户预留信息查询 166
const WORD tdxKHYLXXCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式
};

// 客户预留信息修改 168
const WORD tdxKHYLXXXGFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_CZBZ,				// 操作标志(0/(-1)--直接执行,其他--未定义)
	TDX_ID_ZDDM,				// 字段代码
	TDX_ID_ZDQZ,				// 字段取值
};

// 客户操作确认 170
const WORD tdxKHCZQRFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_CZBZ,				// 操作标志(与TDX_ID_XT_NEEDCONFIRMFLAGS字段定义相关,1--账单确认,其他--未定义)
	TDX_ID_XT_MESSAGETITLE,		// 信息标题
	TDX_ID_XT_MESSAGECONTENT,	// 信息内容
	TDX_ID_XXLX,				// 信息类型
	TDX_ID_KHMC,				// 客户名称
	TDX_ID_XT_CHECKRISKFLAG,	// 检查风险标志
};

// 翻译字典查询 172
const WORD tdxFYZDCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_XT_MODE,				// 模式(字典类型)
	TDX_ID_XT_PARAM,			// 参数(字典标志)
};

const WORD tdxFYZDCXFieldAns[]=
{
	TDX_ID_XT_MODE,				// 模式(字典类型)
	TDX_ID_XT_PARAM,			// 参数(字典标志)
	TDX_ID_XT_DESCRIPTION,		// 描述(字典名称)
	TDX_ID_XT_REMARK,			// 备注(字典备注)
	TDX_ID_XT_DISPLAYCOLOR,		// 显示颜色

	TDX_ID_XT_RESERVED,			// 调试信息
};

// 更新会话信息 174
const WORD tdxUPDATESESSIONFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_SESSION,			// 会话信息
	TDX_ID_XT_MODE,				// 模式
	TDX_ID_XT_PARAM,			// 参数
	TDX_ID_XT_DESCRIPTION,		// 描述
};

const WORD tdxUPDATESESSIONFieldAns[]=
{
	TDX_ID_XT_SESSION,			// 会话信息
	TDX_ID_XT_MODE,				// 模式
	TDX_ID_XT_PARAM,			// 参数
	TDX_ID_XT_DESCRIPTION,		// 描述
	TDX_ID_RETINFO,				// 返回信息

	TDX_ID_XT_RESERVED,			// 调试信息
};

// 问卷流水查询 176
const WORD tdxWJLSCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_LX,					// 类型
};

// 获取市场信息 178
const WORD tdxSCINFOFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_ZQDM,				// 证券代码
};

//////////////////////////////////////////////////////////////////////////
//	委托买卖类
//////////////////////////////////////////////////////////////////////////

// 委托撤单 200
const WORD tdxWTCDFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_SCFLAG,				// 市场代码(必送,不要用TDX_ID_ZHLB)
	TDX_ID_ZQDM,				// 证券代码
	TDX_ID_CZBZ,				// (保留)操作标志
	TDX_ID_WTBH,				// 委托编号(为空撤全部委托)

	TDX_ID_HYDM,				// (废弃,期货)合约代码
	TDX_ID_CDSL,				// (期货)撤单数量
	TDX_ID_XWDM,				// 席位代码
	TDX_ID_XTZXH,				// (期货)系统中心号

	TDX_ID_WTRQ,				// 委托日期

	TDX_ID_MMBZ,				// 买卖标志(0-限价买入 1-限价卖出 'C'-市价买入 ...)
	TDX_ID_TBBZ,				// (期货)投保标志
	TDX_ID_KPBZ,				// (期货)开平标志
	TDX_ID_WTSL,				// (期货)委托数量
	TDX_ID_WTJG,				// (期货)委托价格

	TDX_ID_HTBH,				// 合同编号
	TDX_ID_ZJMM,				// 资金密码(港股--可能用作下单密码)
	TDX_ID_WTSJ,				// 委托时间
	TDX_ID_CJSJ,				// 成交时间
	TDX_ID_XT_PARAM,			// 参数(接口约定,客户端从"撤单查询"/"当日委托查询"取出,原封送回)
	TDX_ID_CJSX,				// 成交属性(客户端从"撤单查询"/"当日委托查询"取出,原封送回)
};

// 普通股票委托 202
const WORD tdxPTGPWTFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_MMBZ,				// 买卖标志(0-限价买入 1-限价卖出 'C'-市价买入 ...)
	TDX_ID_TXMM,				// (保留)通讯密码
	TDX_ID_SCFLAG,				// (保留)市场标志
	TDX_ID_ZQDM,				// 证券代码
	TDX_ID_WTJG,				// 委托价格
	TDX_ID_JYDW,				// 交易单位
	TDX_ID_WTSL,				// 委托数量
	TDX_ID_WTFS,				// 委托方式(和买卖标志相关)

	TDX_ID_BZ,					// (可选,预委托)币种
	TDX_ID_WTJE,				// (可选,预委托)委托金额
	TDX_ID_WTRQ,				// (可选,预委托)委托日期(YYYYMMDD)
	TDX_ID_WTSJ,				// (可选,预委托)委托时间(HHMMSS)
	TDX_ID_WTBH,				// (保留)委托编号
	TDX_ID_PCH,					// 批次号(支持时送)
	TDX_ID_XWDM,				// 席位代码(支持时送)

	TDX_ID_HYDM,				// (废弃,期货)合约代码
	TDX_ID_KPBZ,				// (期货)开平标志
	TDX_ID_TBBZ,				// (期货)投保标志

	TDX_ID_XT_CHECKRISKFLAG,	// 检查风险标志

	TDX_ID_FCJL,				// 分仓基量
	TDX_ID_ZJMM,				// 资金密码(港股--可能用作下单密码)

	TDX_ID_YDXH,				// 约定序号
	TDX_ID_DFXWDM,				// 对方席位代码
	TDX_ID_DFZJZH,				// 对方资金帐号
	TDX_ID_DFGDDM,				// 对方股东代码
	TDX_ID_DFZHLB,				// 对方帐号类别

	TDX_ID_CJSX,				// (期货)成交属性
	TDX_ID_CFJG,				// (期货)触发价格
	TDX_ID_DFFZDM,				// 对方分支代码
	TDX_ID_DFKHDM,				// 对方客户代码
	TDX_ID_DFMM,				// 对方密码
	TDX_ID_TJRDM,				// 推荐人代码
	TDX_ID_XT_TOKEN,			// 令牌
	TDX_ID_LXRXM,				// 联系人姓名
	TDX_ID_LXFS,				// 联系方式
};

// 债券转股回售 204
const WORD tdxZQZGHSFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_MMBZ,				// 买卖标志(0-转股 1-回售)
	TDX_ID_ZQDM,				// 证券代码
	TDX_ID_WTSL,				// 委托数量
	TDX_ID_WTJG,				// 委托价格
};

// 修改订单 206
const WORD tdxXGDDFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_WTBH,				// 委托编号(原订单编号)
	TDX_ID_MMBZ,				// 买卖标志(0-买入 1-卖出 ...)
	TDX_ID_ZQDM,				// 证券代码
	TDX_ID_WTJG,				// 委托价格
	TDX_ID_JYDW,				// 交易单位
	TDX_ID_WTSL,				// 委托数量
	TDX_ID_WTFS,				// 委托方式(和买卖标志相关)

	TDX_ID_BZ,					// (可选,预委托)币种
	TDX_ID_WTJE,				// (可选,预委托)委托金额
	TDX_ID_WTRQ,				// (可选,预委托)委托日期(YYYYMMDD)
	TDX_ID_WTSJ,				// (可选,预委托)委托时间(HHMMSS)
	TDX_ID_PCH,					// 批次号(支持时送)
	TDX_ID_XWDM,				// 席位代码(支持时送)

	TDX_ID_KPBZ,				// (期货)开平标志
	TDX_ID_TBBZ,				// (期货)投保标志

	TDX_ID_YWTSL,				// 原委托数量
	TDX_ID_YWTJG,				// 原委托价格
	TDX_ID_HTBH,				// 合同编号
	TDX_ID_ZJMM,				// 资金密码(港股--可能用作下单密码)
	TDX_ID_WCJSL,				// 未成交数量
	TDX_ID_XT_PARAM,			// 参数(接口约定,客户端从"撤单查询"/"当日委托查询"取出,原封送回)
	TDX_ID_CJSX,				// 成交属性
	TDX_ID_XT_TOKEN,			// 令牌
};

// 申购新股 208
const WORD tdxSGXGFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_MMBZ,				// 买卖标志(申购类型)
	TDX_ID_ZQDM,				// 证券代码
	TDX_ID_WTSL,				// 委托数量(申购数量)
	TDX_ID_RZJE,				// 融资金额
	TDX_ID_RZBL,				// 融资比例
	TDX_ID_SXF,					// 手续费(申购费用)
	TDX_ID_LX,					// 类型(融资类型)
};

// 新股申购修改 210
const WORD tdxXGSGXGFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_MMBZ,				// 买卖标志(申购类型)
	TDX_ID_ZQDM,				// 证券代码
	TDX_ID_WTSL,				// 委托数量(申购数量)
	TDX_ID_RZJE,				// 融资金额
	TDX_ID_RZBL,				// 融资比例
	TDX_ID_SXF,					// 手续费(申购费用)
	TDX_ID_LX,					// 类型(融资类型)
	TDX_ID_WTBH,				// 委托编号
};

// 新股申购撤单 212
const WORD tdxXGSGCDFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_MMBZ,				// 买卖标志(申购类型)
	TDX_ID_ZQDM,				// 证券代码
	TDX_ID_WTSL,				// 委托数量(申购数量)
	TDX_ID_RZJE,				// 融资金额
	TDX_ID_RZBL,				// 融资比例
	TDX_ID_SXF,					// 手续费(申购费用)
	TDX_ID_LX,					// 类型(融资类型)
	TDX_ID_WTBH,				// 委托编号
};

// 批量委托 214
const WORD tdxPLWTFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_MMBZ,				// 买卖标志
	TDX_ID_WTFS,				// 委托类别
	TDX_ID_ZQDM,				// 证券代码
	TDX_ID_WTJG,				// 委托价格
	TDX_ID_WTSL,				// 委托数量
	TDX_ID_WTCS,				// 委托次数
	TDX_ID_XWDM,				// 席位代码(支持时送)
	TDX_ID_XT_CHECKRISKFLAG,	// 检查风险标志
};

// 批量撤单 216
const WORD tdxPLCDFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_ZQDM,				// 证券代码
	TDX_ID_PCH,					// 批次号
	TDX_ID_XWDM,				// 席位代码
	TDX_ID_WTRQ,				// 委托日期
};

// 新增订单检查 218
const WORD tdxXZDDJCFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_MMBZ,				// 买卖标志(0-限价买入 1-限价卖出 'C'-市价买入 ...)
	TDX_ID_TXMM,				// (保留)通讯密码
	TDX_ID_SCFLAG,				// (保留)市场标志
	TDX_ID_ZQDM,				// 证券代码
	TDX_ID_WTJG,				// 委托价格
	TDX_ID_JYDW,				// 交易单位
	TDX_ID_WTSL,				// 委托数量
	TDX_ID_WTFS,				// 委托方式(和买卖标志相关)

	TDX_ID_BZ,					// (可选,预委托)币种
	TDX_ID_WTJE,				// (可选,预委托)委托金额
	TDX_ID_WTRQ,				// (可选,预委托)委托日期(YYYYMMDD)
	TDX_ID_WTSJ,				// (可选,预委托)委托时间(HHMMSS)
	TDX_ID_WTBH,				// (保留)委托编号
	TDX_ID_PCH,					// 批次号(支持时送)
	TDX_ID_XWDM,				// 席位代码(支持时送)

	TDX_ID_HYDM,				// (废弃,期货)合约代码
	TDX_ID_KPBZ,				// (期货)开平标志
	TDX_ID_TBBZ,				// (期货)投保标志

	TDX_ID_XT_CHECKRISKFLAG,	// 检查风险标志

	TDX_ID_FCJL,				// 分仓基量
	TDX_ID_ZJMM,				// 资金密码(港股--可能用作下单密码)

	TDX_ID_YDXH,				// 约定序号
	TDX_ID_DFXWDM,				// 对方席位代码
	TDX_ID_DFZJZH,				// 对方资金帐号
	TDX_ID_DFGDDM,				// 对方股东代码
	TDX_ID_DFZHLB,				// 对方帐号类别

	TDX_ID_CJSX,				// (期货)成交属性
	TDX_ID_CFJG,				// (期货)触发价格
	TDX_ID_DFFZDM,				// 对方分支代码
	TDX_ID_DFKHDM,				// 对方客户代码
	TDX_ID_DFMM,				// 对方密码
};

// 修改订单检查 220
const WORD tdxXGDDJCFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_WTBH,				// 委托编号(原订单编号)
	TDX_ID_MMBZ,				// 买卖标志(0-买入 1-卖出 ...)
	TDX_ID_ZQDM,				// 证券代码
	TDX_ID_WTJG,				// 委托价格
	TDX_ID_JYDW,				// 交易单位
	TDX_ID_WTSL,				// 委托数量
	TDX_ID_WTFS,				// 委托方式(和买卖标志相关)

	TDX_ID_BZ,					// (可选,预委托)币种
	TDX_ID_WTJE,				// (可选,预委托)委托金额
	TDX_ID_WTRQ,				// (可选,预委托)委托日期(YYYYMMDD)
	TDX_ID_WTSJ,				// (可选,预委托)委托时间(HHMMSS)
	TDX_ID_PCH,					// 批次号(支持时送)
	TDX_ID_XWDM,				// 席位代码(支持时送)

	TDX_ID_KPBZ,				// (期货)开平标志
	TDX_ID_TBBZ,				// (期货)投保标志

	TDX_ID_YWTSL,				// 原委托数量
	TDX_ID_YWTJG,				// 原委托价格
	TDX_ID_HTBH,				// 合同编号
	TDX_ID_ZJMM,				// 资金密码(港股--可能用作下单密码)
	TDX_ID_WCJSL,				// 未成交数量
	TDX_ID_XT_PARAM,			// 参数(接口约定,客户端从"撤单查询"/"当日委托查询"取出,原封送回)
	TDX_ID_CJSX,				// 成交属性
};

// 闪电手资金查询 250
const WORD tdxSDSZJCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式
	
	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_CZBZ,				// 操作标志
};

// 闪电手股份查询 252
const WORD tdxSDSGFCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式
	
	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 闪电手委托查询 254
const WORD tdxSDSWTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式
	
	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 闪电手成交查询 256
const WORD tdxSDSCJCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式
	
	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_LSH,					// 流水号(用于增量查询)
	TDX_ID_CZBZ,				// 操作标志
};

// 闪电手流水查询 258
const WORD tdxSDSLSCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式
	
	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_LSH,					// 流水号(用于增量查询)
	TDX_ID_CZBZ,				// 操作标志
	TDX_ID_BZ,					// 币种
};

// 闪电手信用资产查询 260
const WORD tdxSDSXYZCCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 闪电手证券信息查询 262
const WORD tdxSDSZQXXCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_ZQDM,				// 证券代码
	TDX_ID_MMBZ,				// 买卖标志
	TDX_ID_WTFS,				// 委托类别
	TDX_ID_CZBZ,				// 操作标志
};

// 闪电手可买(卖)数量查询 264
const WORD tdxSDSKMSLCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_ZQDM,				// 证券代码
	TDX_ID_MMBZ,				// 买卖标志
	TDX_ID_WTFS,				// 委托类别
	TDX_ID_WTJG,				// 委托价格
	TDX_ID_CZBZ,				// 操作标志
};

// 放弃中签 300 (保留)
const WORD tdxFQZQFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式
	
	TDX_ID_SCFLAG,				// 市场代码
	TDX_ID_ZQDM,				// 证券代码
	TDX_ID_ZQSL,				// 证券数量
};

// (服务)客户资料查询 302
const WORD tdxFWKHZLCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号(各种帐号)
	TDX_ID_JYMM,				// 交易密码(保留)
	TDX_ID_ZJZH,				// 资金帐号(保留)
	TDX_ID_ZHLB,				// 帐号类别("客户号"中帐号的类型)
	TDX_ID_GDDM,				// 股东代码(保留)
	TDX_ID_OP_WTFS,				// 操作方式(为空的时候使用"客户端类型"的值翻译)

	TDX_ID_XT_CLITYPE,			// 客户端类型("操作方式"为空的时候使用)
};

// (服务)获取动态口令 304
const WORD tdxFWHQDTKLFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_LX,					// 类型(0--默认,1--获取动态口令,2--获取客户权限,3--获取手机验证码)
	TDX_ID_CZBZ,				// 操作标志(用于区分不同需求)
	TDX_ID_XT_PARAM,			// 参数(用于携带相关参数)
	TDX_ID_XT_AUTH_MODE,		// 认证模式(用于区分不同需求)
};

// (服务)产品定购品种 306
const WORD tdxFWCPDGPZFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_CPDM,				// 产品代码
};

// (服务)产品定购查询 308
const WORD tdxFWCPDGCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_CPDM,				// 产品代码
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

// (服务)产品定购设置 310
const WORD tdxFWCPDGSZFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_CPDM,				// 产品代码
	TDX_ID_XT_PARAM,			// 参数(用于携带相关参数)
	TDX_ID_KHMC,				// 客户名称
	TDX_ID_ZJHM,				// 证件号码
	TDX_ID_USEREMAIL,			// 用户Email
	TDX_ID_USERPHONE,			// 联系电话
	TDX_ID_MOBILEPHONE,			// 移动电话
	TDX_ID_FAX,					// 传真电话
	TDX_ID_USERADDRESS,			// 通讯地址
	TDX_ID_POSTALCODE,			// 邮政编码
	TDX_ID_PROVINCE,			// 省份
	TDX_ID_CITY,				// 城市
	TDX_ID_SECTION,				// 辖区
	TDX_ID_ZJLB,				// 证件类别
	TDX_ID_XT_AUTH_MODE,		// 认证模式
	TDX_ID_XT_AUTH_INFO,		// 认证信息
};

// (服务)产品定购修改 312
const WORD tdxFWCPDGXGFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_CPDM,				// 产品代码
	TDX_ID_XT_PARAM,			// 参数(用于携带相关参数)
	TDX_ID_LSH,					// 流水号
	TDX_ID_KHMC,				// 客户名称
	TDX_ID_ZJHM,				// 证件号码
	TDX_ID_USEREMAIL,			// 用户Email
	TDX_ID_USERPHONE,			// 联系电话
	TDX_ID_MOBILEPHONE,			// 移动电话
	TDX_ID_FAX,					// 传真电话
	TDX_ID_USERADDRESS,			// 通讯地址
	TDX_ID_POSTALCODE,			// 邮政编码
	TDX_ID_PROVINCE,			// 省份
	TDX_ID_CITY,				// 城市
	TDX_ID_SECTION,				// 辖区
	TDX_ID_ZJLB,				// 证件类别
	TDX_ID_XT_AUTH_MODE,		// 认证模式
	TDX_ID_XT_AUTH_INFO,		// 认证信息
};

// (服务)产品定购取消 314
const WORD tdxFWCPDGQXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_CPDM,				// 产品代码
	TDX_ID_LSH,					// 流水号
	TDX_ID_CZBZ,				// 操作标志(0--普通,1--展期,默认--0)
};

// (服务)资金流水 316
const WORD tdxFWZJLSFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_XT_STARTPOS,			// 起始序号
};

const WORD tdxFWZJLSFieldAns[]=
{
	TDX_ID_ZJLS_FSRQ,			// 发生日期
	TDX_ID_ZJLS_FSSJ,			// 发生时间
	TDX_ID_ZJLS_YWDM,			// 业务代码
	TDX_ID_ZJLS_YWMC,			// 业务名称
	TDX_ID_ZJLS_HBDM,			// 货币代码
	TDX_ID_ZJLS_FSJE,			// 发生金额
	TDX_ID_ZJLS_SYJE,			// 剩余金额
	TDX_ID_ZJLS_ZQDM,			// 证券代码
	TDX_ID_ZJLS_ZQMC,			// 证券名称
	TDX_ID_ZJLS_FSJG,			// 发生价格
	TDX_ID_ZJLS_FSSL,			// 发生数量
	TDX_ID_ZJLS_SYSL,			// 剩余数量
	TDX_ID_ZJLS_GDDM,			// 股东代码
};

// (服务)批量行情查询 318
const WORD tdxFWPLHQCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_SCFLAG,				// 交易所代码
	TDX_ID_ZQDM,				// 证券代码(多个证券代码,默认由逗号","分隔)
	TDX_ID_XT_PARAM,			// 参数(指定分隔符,非空时第一个字节有效,用于替代默认分隔符)
	TDX_ID_XT_MODE,				// 模式(指定代码组合,"证券代码"为空时有效)
};

// (服务)资讯栏目查询 320
const WORD tdxFWZXLMCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// (服务)获取提示信息 322
const WORD tdxFWHQTSXXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_XXLX,				// 信息类型(逗号分隔的多个需要返回的信息类型)
	TDX_ID_XT_PARAM,			// 参数(客户端和接口约定的相关参数)
};

// (服务)投票方案查询 324
const WORD tdxFWTPFACXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_TPDM,				// 投票代码(空--查全部)
	TDX_ID_FADM,				// 方案代码(空--查全部)
	TDX_ID_ZQDM,				// 证券代码(空--查全部)
};

// (服务)投票信息查询 326
const WORD tdxFWTPXXCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_TPDM,				// 投票代码(必填)
	TDX_ID_FADM,				// 方案代码(必填)

};

// (服务)投票结果提交 328
const WORD tdxFWTPJGTJFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_TPDM,				// 投票代码
	TDX_ID_FADM,				// 方案代码
	TDX_ID_TPJG,				// 投票结果(1--同意,2--反对,3--弃权)
	TDX_ID_XT_PARAM,			// 参数(是否存在关系,0--存在关系,2--不存在关系)
	TDX_ID_FALX,				// 方案类型(0--投票,1--选举)
	TDX_ID_WTSL,				// 投票数量
};

// (服务)投票结果查询 330
const WORD tdxFWTPJGCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_TPDM,				// 投票代码(空--查全部)
	TDX_ID_FADM,				// 方案代码(空--查全部)
	TDX_ID_ZQDM,				// 证券代码(空--查全部)
};

// (服务)投票统计查询 332
const WORD tdxFWTPTJCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_TPDM,				// 投票代码(空--查全部)
	TDX_ID_FADM,				// 方案代码(空--查全部)
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_XT_PARAM,			// 参数(是否存在关系,0--存在关系,2--不存在关系)
	TDX_ID_ZQDM,				// 证券代码(空--查全部)
};

// (服务)套利组合代码查询 334
const WORD tdxFWTLZHDMCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// (服务)套利组合成分查询 336
const WORD tdxFWTLZHCFCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_ZSDM,				// 指数代码
};

// (服务)单点登录操作 338
const WORD tdxFWDDDLCZFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_CZBZ,				// 操作标志(0--获取令牌,1--校验令牌)
	TDX_ID_XT_TOKEN,			// 令牌
};

// (服务)批量现价查询 340
const WORD tdxFWPLXJCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_SCFLAG,				// 交易所代码
	TDX_ID_ZQDM,				// 证券代码(多个证券代码,默认由逗号","分隔)
	TDX_ID_XT_PARAM,			// 参数(指定分隔符,非空时第一个字节有效,用于替代默认分隔符)
	TDX_ID_XT_MODE,				// 模式(指定代码组合,"证券代码"为空时有效)
};

// (服务)信息订阅 342
const WORD tdxFWXXDYFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_CZBZ,				// 操作标志(默认--0)
	TDX_ID_LX,					// 类型(默认--0)
	TDX_ID_XT_PARAM,			// 参数(默认--空)
};

// (服务)客户卡处理 344
const WORD tdxFWKHKCLFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_CZBZ,				// 操作标志(0--查询,1--挂失)
	TDX_ID_XT_PARAM,			// 参数(默认--空)
};

// (服务)上传配置信息 346
const WORD tdxFWSCPZXXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_MODE,				// 模式(配置类型)
	TDX_ID_XT_PARAM,			// 参数(配置信息)
	TDX_ID_XT_DESCRIPTION,		// 描述(配置描述)
	TDX_ID_XT_REMARK,			// 备注(配置分组)
	TDX_ID_XT_INPUTPARAM,		// 输入参数
};

// (服务)下载配置信息 348
const WORD tdxFWXZPZXXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_XT_MODE,				// 模式(配置类型,空表示全部)
	TDX_ID_XT_REMARK,			// 备注(配置分组)
	TDX_ID_XT_INPUTPARAM,		// 输入参数
};

// (服务)配置信息摘要查询 350
const WORD tdxFWPZXXZYCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_MODE,				// 模式(配置类型,空表示全部)
	TDX_ID_XT_REMARK,			// 备注(配置分组)
	TDX_ID_XT_INPUTPARAM,		// 输入参数
};

// (服务)处理客户参数 352
const WORD tdxFWCLKHCSFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_LX,					// 类型(1--成本价类型;...)
	TDX_ID_CZBZ,				// 操作标志(0--查询;1--预提交;2--提交)
	TDX_ID_RETINFO,				// 提交的选项(有多项时,逗号分隔)
};

// (服务)配对列表查询 354
const WORD tdxFWPDLBCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// (服务)配对流水录入 356
const WORD tdxFWPDLSLRFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_JCRQ,				// 建仓日期
	TDX_ID_PDDM1,				// 配对代码1
	TDX_ID_PDMC1,				// 配对名称1
	TDX_ID_JCJG1,				// 建仓价格1
	TDX_ID_JCSL1,				// 建仓数量1
	TDX_ID_JCBH1,				// 建仓编号1
	TDX_ID_PDDM2,				// 配对代码2
	TDX_ID_PDMC2,				// 配对名称2
	TDX_ID_JCJG2,				// 建仓价格2
	TDX_ID_JCSL2,				// 建仓数量2
	TDX_ID_JCBH2,				// 建仓编号2
};

// (服务)配对流水查询 358
const WORD tdxFWPDLSCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

// (服务)增值业务收费 360
const WORD tdxFWZZYWSFFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_CZBZ,				// 操作标志(1--下单,2--改单,3--撤单)
	TDX_ID_WTBH,				// 委托编号(改单/撤单使用)
	TDX_ID_YWDM,				// 业务代码(客户端/接口--自行约定收费类型)
	TDX_ID_BZ,					// 币种
	TDX_ID_JYDW,				// 交易单位
	TDX_ID_WTSL,				// 委托数量
	TDX_ID_WTJG,				// 委托价格
	TDX_ID_WTJE,				// 委托金额
	TDX_ID_YZZZ_YHDM,			// 银行代码
	TDX_ID_YZZZ_YHZH,			// 银行账号
	TDX_ID_YZZZ_YHMM,			// 银行密码
	TDX_ID_XT_REMARK,			// 备注
};

//////////////////////////////////////////////////////////////////////////

// (推送)强制退出 400 [推送功能,请求不使用]
const WORD tdxQZTCFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式
};

// (推送)强制退出 401

// (推送)消息通知 402 [推送功能,请求不使用]
const WORD tdxXXTZFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式
};

// (推送)消息通知 403

// (推送)公告消息 404 [推送功能,请求不使用]
const WORD tdxGGXXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式
};

// (推送)公告消息 405

// (手机)证券查询 500
const WORD tdxMOBILEZQCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_ZQDM,				// 证券代码
	TDX_ID_WTJG,				// 委托价格
	TDX_ID_MMBZ,				// 买卖标志
	TDX_ID_WTFS,				// 委托类别
	TDX_ID_CZBZ,				// 操作标志
	TDX_ID_XT_CHECKRISKFLAG,	// 检查风险标志
	TDX_ID_SBMRJ,				// 申报买入价(CZBZ=2时有效)
	TDX_ID_SBMCJ,				// 申报卖出价(CZBZ=2时有效)
	TDX_ID_TBBZ,				// 投保标志

	TDX_ID_DFFZDM,				// 对方分支代码
	TDX_ID_DFKHDM,				// 对方客户代码
	TDX_ID_DFMM,				// 对方密码
	TDX_ID_DFXWDM,				// 对方席位代码
	TDX_ID_DFZJZH,				// 对方资金帐号
	TDX_ID_DFGDDM,				// 对方股东代码
	TDX_ID_DFZHLB,				// 对方帐号类别
	TDX_ID_XT_FUNCTIONVERSION,	// 功能版本
};

// (手机)股份查询 502
const WORD tdxMOBILEGFCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数
};

// (手机)资金查询 504
const WORD tdxMOBILEZJCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数
};

// (手机)撤单查询 506
const WORD tdxMOBILECDCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数
};

// (手机)委托查询 508
const WORD tdxMOBILEWTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数
};

// (手机)成交查询 510
const WORD tdxMOBILECJCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数
};

// (手机)转账查询 512
const WORD tdxMOBILEZZCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_YZZZ_YHDM,			// 银行代码
};

// (手机)流水查询 514
const WORD tdxMOBILELSCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

// (手机)交割查询 516
const WORD tdxMOBILEJGCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

// (手机)对账查询 518
const WORD tdxMOBILEDZCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

// (手机)意向申报行情查询 520
const WORD tdxMOBILEYXSBHQCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数

	TDX_ID_MMBZ,				// 买卖标志
	TDX_ID_WTFS,				// 委托类别
	TDX_ID_ZQDM,				// 证券代码
};

// (手机)历史委托查询 522
const WORD tdxMOBILELSWTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

// (手机)历史成交查询 524
const WORD tdxMOBILELSCJCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_CZBZ,				// 操作标志
};

// (手机)配号中签查询 526
const WORD tdxMOBILEPHZQCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

// (手机)认证流水查询 528
const WORD tdxMOBILERZLSCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_XT_AUTH_MODE,		// 安全中心验证方式((-1)--全部)
};

// (手机)基金撤单查询 530
const WORD tdxMOBILEJJCDCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数
};

// (手机)基金当日委托查询 532
const WORD tdxMOBILEJJDRWTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数
};

// (手机)基金历史委托查询 534
const WORD tdxMOBILEJJLSWTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数

	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

// (手机)基金当日成交查询 536
const WORD tdxMOBILEJJDRCJCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数
};

// (手机)基金历史成交查询 538
const WORD tdxMOBILEJJLSCJCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数

	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

// (手机)基金账号查询 540
const WORD tdxMOBILEJJZHCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数
};

// (手机)基金公司查询 542
const WORD tdxMOBILEJJGSCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数
};

// (手机)基金代码查询 544
const WORD tdxMOBILEJJDMCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数
};

// (手机)基金份额查询 546
const WORD tdxMOBILEJJFECXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数
};

// (手机)基金对账查询 548
const WORD tdxMOBILEJJDZCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数

	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

// (手机)基金交割查询 550
const WORD tdxMOBILEJJJGCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数

	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

// (手机)基金非交易委托查询 552
const WORD tdxMOBILEJJFJYWTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数

	TDX_ID_KSRQ,				// 查询开始日期
	TDX_ID_ZZRQ,				// 查询结束日期
	TDX_ID_LX,					// (0、当日 1、历史)
};

// (手机)期货合约查询 560
const WORD tdxMOBILEQHHYCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数

	TDX_ID_CZBZ,				// 操作标志(0--查询全部合约,1--查询指定市场的可用合约,默认--0)
	TDX_ID_SCFLAG,				// 市场代码(CZBZ=1时有效)
};

// (手机)期货组合合约查询 562
const WORD tdxMOBILEQHZHHYCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数
};

// (手机)期货组合持仓查询 564
const WORD tdxMOBILEQHZHCCCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数
};

// (手机)期货组合委托查询 566
const WORD tdxMOBILEQHZHWTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数
};

// (手机)期货组合策略查询 568
const WORD tdxMOBILEQHZHCLCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数

	TDX_ID_CLDM,				// 策略代码
	TDX_ID_ZHLX,				// 组合类型
};

// (手机)股份汇总查询 570
const WORD tdxMOBILEGFHZCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数
};

// (手机)委托汇总查询 572
const WORD tdxMOBILEWTHZCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数
};

// (手机)成交汇总查询 574
const WORD tdxMOBILECJHZCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数
};

// (手机)成交明细查询 576
const WORD tdxMOBILECJMXCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数
};

// (手机)信用融资买入配套查询 600
const WORD tdxMOBILEXYRZMRPTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数
};

// (手机)信用融券卖出配套查询 602
const WORD tdxMOBILEXYRQMCPTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数
};

// (手机)信用卖出还款配套查询 604
const WORD tdxMOBILEXYMCHKPTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数
};

// (手机)信用买入还券配套查询 606
const WORD tdxMOBILEXYMRHQPTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数
};

// (手机)信用现金还款配套查询 608
const WORD tdxMOBILEXYXJHKPTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数
};

// (手机)信用现券还券配套查询 610
const WORD tdxMOBILEXYXQHQPTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数
};

// (手机)信用余券划转配套查询 612
const WORD tdxMOBILEXYYQHZPTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数
};

// (手机)信用担保划转配套查询 614
const WORD tdxMOBILEXYDBHZPTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数

	TDX_ID_WTFS,				// 委托类别(划入/划出)
	TDX_ID_DFFZDM,				// 对方分支代码
	TDX_ID_DFKHDM,				// 对方客户代码
	TDX_ID_DFMM,				// 对方密码
};

// (手机)信用担保转入配套查询 616
const WORD tdxMOBILEXYDBZRPTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数

	TDX_ID_DFFZDM,				// 对方分支代码
	TDX_ID_DFKHDM,				// 对方客户代码
	TDX_ID_DFMM,				// 对方密码
};

// (手机)信用担保转出配套查询 618
const WORD tdxMOBILEXYDBZCPTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数
};

// (手机)信用资产信息查询 620
const WORD tdxMOBILEXYZCXXCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数
};

// (手机)信用股份信息查询 622
const WORD tdxMOBILEXYGFXXCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数
};

// (手机)信用标的证券查询 624
const WORD tdxMOBILEXYBDZQCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数

	TDX_ID_MMBZ,				// 买卖标志
	TDX_ID_WTFS,				// 委托类别
	TDX_ID_ZQDM,				// 证券代码
};

// (手机)信用直接划转查询 626
const WORD tdxMOBILEXYZJHZCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数

	TDX_ID_KSRQ,				// 查询开始日期
	TDX_ID_ZZRQ,				// 查询终止日期
};

// (手机)信用利息费用查询 628
const WORD tdxMOBILEXYLXFYCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数
};

// (手机)信用未平合约查询 630
const WORD tdxMOBILEXYWPHYCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数

	TDX_ID_KSRQ,				// 查询开始日期
	TDX_ID_ZZRQ,				// 查询终止日期
	TDX_ID_CZBZ,				// 操作标志(0--全部,1--融资,2--融券,默认--0)
};

// (手机)信用已平合约查询 632
const WORD tdxMOBILEXYYPHYCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数

	TDX_ID_KSRQ,				// 查询开始日期
	TDX_ID_ZZRQ,				// 查询终止日期
	TDX_ID_CZBZ,				// 操作标志(0--全部,1--融资,2--融券,默认--0)
};

// (手机)信用当日合约查询 634
const WORD tdxMOBILEXYDRHYCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数
};

// (手机)信用融资合约查询 636
const WORD tdxMOBILEXYRZHYCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数

	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_CZBZ,				// 操作标志(0--全部,1--未了结,2--已了结,默认--0)
};

// (手机)信用融券合约查询 638
const WORD tdxMOBILEXYRQHYCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数

	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_CZBZ,				// 操作标志(0--全部,1--未了结,2--已了结,默认--0)
};

// (手机)信用资金负债查询 640
const WORD tdxMOBILEXYZJFZCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数

	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

// (手机)信用股份负债查询 642
const WORD tdxMOBILEXYGFFZCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数

	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

// (手机)信用交易担保品证券查询 644
const WORD tdxMOBILEXYJYDBPZQCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数
	
	TDX_ID_ZQDM,				// 证券代码
};

// (手机)信用交易非交易化转查询 646
const WORD tdxMOBILEXYJYFJYHZCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数

	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

// (手机)信用交易负债流水查询 648
const WORD tdxMOBILEXYJYFZLSCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数

	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};
//////////////////////////////////////////////////////////////////////////

// (手机)ETF委托查询 700
const WORD tdxMOBILEETFWTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数

	TDX_ID_CZBZ,				// 操作标志(0--查所有委托,1--查可撤单委托,默认--0)
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_ZSDM,				// 指数代码
	TDX_ID_PCH,					// 批次号(0--查所有记录,其他--查对应记录)
};

// (手机)ETF成交查询 702
const WORD tdxMOBILEETFCJCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数

	TDX_ID_WTRQ,				// 委托日期
	TDX_ID_ZSDM,				// 指数代码
	TDX_ID_PCH,					// 批次号
};

//////////////////////////////////////////////////////////////////////////

// (手机)理财产品份额查询 750
const WORD tdxMOBILELCCPFECXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数

	TDX_ID_CZBZ,				// 操作标志
};

// (手机)理财产品委托查询 752
const WORD tdxMOBILELCCPWTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数

	TDX_ID_CZBZ,				// 操作标志
	TDX_ID_LX,					// (0、当日 1、历史)
};

// (手机)理财产品成交查询 754
const WORD tdxMOBILELCCPCJCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数

	TDX_ID_CZBZ,				// 操作标志
};

// (手机)理财产品代码查询 756
const WORD tdxMOBILELCCPDMCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数

	TDX_ID_CZBZ,				// 操作标志
};

// (手机)理财产品定期定额申购查询 758
const WORD tdxMOBILELCCPDQDESGCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数
};

// (手机)银行理财产品代码查询 790
const WORD tdxMOBILEYHLCCPDMCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数

	TDX_ID_CZBZ,				// 操作标志
};

// (手机)银行理财产品份额查询 792
const WORD tdxMOBILEYHLCCPFECXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数

	TDX_ID_CZBZ,				// 操作标志
};

// (手机)银行理财产品委托查询 794
const WORD tdxMOBILEYHLCCPWTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数

	TDX_ID_CZBZ,				// 操作标志
};

// (手机)银行理财产品成交查询 796
const WORD tdxMOBILEYHLCCPCJCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期

	TDX_ID_XT_POSITIONSTRING,	// 定位字串
	TDX_ID_XT_BEGINLINE,		// 起始行号
	TDX_ID_XT_REQUESTLINE,		// 请求行数
	TDX_ID_XT_TOTALLINE,		// 总共行数

	TDX_ID_CZBZ,				// 操作标志
};

//////////////////////////////////////////////////////////////////////////
//	安全中心类
//////////////////////////////////////////////////////////////////////////

// CA账户申请 800
const WORD tdxCAZHSQFieldReq[]=
{
	TDX_ID_CA_KHH,				// 800 完整客户号
	TDX_ID_CA_KHMC,				// 801 客户名称
	TDX_ID_CA_TXMM,				// 803 认证口令
	TDX_ID_CA_ZSXH,				// 805 证书序号(客户端生成)
	TDX_ID_CA_AQJB,				// 806 申请的安全级别(组合: 1,SLL 2,认证口令 4,数字证书,8硬件OTP,64 手机OTP)
	TDX_ID_CA_SEEDINFO,			// 4221 种子信息
	TDX_ID_CA_OTPSN,			// 4222 OTPSN序号
	TDX_ID_CA_CID,				// 4220 三方安全机构ID(颁发/验证)
};
const WORD tdxCAZHSQFieldAns[]=
{
	TDX_ID_CA_TXMM,				// 803 认证口令
	TDX_ID_CA_ZSXH,				// 805 证书序号
	TDX_ID_CA_AQJB,				// 806 安全级别
	TDX_ID_CA_YHFJ,				// 807 用户分级
	TDX_ID_CA_YHJBMS,			// 808 用户级别描述
	TDX_ID_CA_YHQX,				// 809 用户权限(ASCII字符串)
	TDX_ID_CA_ZSSHBZ,			// 811 证书审核标志(0,已经通过审核 1,正在等待审核)
	TDX_ID_CA_ZSXZBZ,			// 812 证书下载标志(0,当前请求未携带下载 1,当前请求携带有证书内容)
	TDX_ID_CA_ZSQSID,			// 813 证书的券商ID
	TDX_ID_CA_ZSBFJG,			// 814 证书颁发机构
	TDX_ID_CA_ZSBFYH,			// 815 证书颁发用户
	TDX_ID_CA_ZSQSRQ,			// 816 证书起始日期
	TDX_ID_CA_ZSJZRQ,			// 817 证书截止日期
	TDX_ID_CA_ZSWS,				// 818 证书位数
	TDX_ID_CA_ZSGY,				// 819 证书公钥
};

// CA帐号查询 802
const WORD tdxCAZHCXFieldReq[]=
{
	TDX_ID_CA_KHH,				// 完整客户号
};
const WORD tdxCAZHCXFieldAns[]=
{
	TDX_ID_CA_AQJB,				// 当前申请的安全级别
	TDX_ID_CA_ZSSHBZ,			// 证书审核标志
};

// CA账户校验 804
const WORD tdxCAZHJYFieldReq[]=
{
	TDX_ID_CA_KHH,				// 完整客户号
	TDX_ID_CA_KHMC,				// 客户名称
	TDX_ID_CA_AQJB,				// 登录安全级别
	TDX_ID_CA_TXMM,				// 认证口令(如果使用认证口令方式)
	TDX_ID_CA_ZSGY,				// 证书公钥(如果使用数字证书方式)
	TDX_ID_CA_ISVIPHOST,		// VIP主站标识
	TDX_ID_CA_NEWIP,			// 本次登陆IP
	TDX_ID_CA_JQTZM,			// 机器特征码
	TDX_ID_CA_SJH,				// 客户手机号
};
const WORD tdxCAZHJYFieldAns[]=
{
	TDX_ID_CA_SQBZ,				// 申请标志(0:已经申请 1:未申请,必须立即申请)
	TDX_ID_CA_AQJB,				// 安全级别(若申请标志为0,为用户当前安全级别 若申请标志为1:为服务器支持的最低安全级别)
	TDX_ID_CA_YHFJ,				// 用户分级
	TDX_ID_CA_YHJBMS,			// 用户级别描述
	TDX_ID_CA_YHQX,				// 用户权限
	TDX_ID_CA_ZSSHBZ,			// 证书审核标志
	TDX_ID_CA_KJYBZ,			// 可交易标志(0:不可交易,只可进行安全管理 1:可正常交易)
	TDX_ID_CA_ZSXZBZ,			// 证书下载标志(0:无证书内容附加 1:存在证书附加,需要下载确认)
	TDX_ID_CA_ZSQSID,			// 证书的券商ID
	TDX_ID_CA_ZSBFJG,			// 证书颁发机构
	TDX_ID_CA_ZSBFYH,			// 证书颁发用户
	TDX_ID_CA_ZSQSRQ,			// 证书起始日期(YYYYMMDD)
	TDX_ID_CA_ZSJZRQ,			// 证书截止日期(YYYYMMDD)
	TDX_ID_CA_ZSWS,				// 证书位数
	TDX_ID_CA_ZSGY,				// 证书公钥
	IDX_ID_CA_ZSKGXBZ,			// 证书可更新标志(0:不可更新 1:证书可更新)
	TDX_ID_CA_ZSJYGXBZ,			// 证书建议更新标志(0:不必要建议用户更新 1:建议用户立即更新)
	TDX_ID_CA_ZSSYYXTS,			// 证书剩余有效天数(>=0)
	TDX_ID_CA_XGTXMMBZ,			// 认证口令强制修改标志
	TDX_ID_CA_L2USER,			// LEVEL2账号
	TDX_ID_CA_L2PASS,			// LEVEL2密码
	TDX_ID_CA_ISDLWZTS,			// 是否支持登陆位置提示
	TDX_ID_CA_ISMMBHWT,			// 是否支持密码保护问题
	TDX_ID_CA_ISJQTZMBD,		// 是否支持机器特征码绑定
	TDX_ID_CA_ISYLWT,			// 是否支持预留问题
	TDX_ID_CA_YLWT,				// 预留问题
	TDX_ID_CA_LASTIP,			// 上次登陆IP

	TDX_ID_CA_LASPROV,			// 上次登陆省份
	TDX_ID_CA_NEWPROV,			// 本次登陆省份
	TDX_ID_CA_LASSITE,			// 上次登陆位置
	TDX_ID_CA_NEWSITE,			// 本次登陆位置
	TDX_ID_CA_DLSJ,				// 登陆时间
	
	TDX_ID_CA_BINDNUM,			// 已绑定机器特征码机器的台数
	TDX_ID_CA_MAC,				// 机器MAC地址
	TDX_ID_CA_MACHINENAME,		// 上次登陆机器昵称
};

// CA认证口令修改 806
const WORD tdxCATXMMXGFieldReq[]=
{
	TDX_ID_CA_KHH,				// 完整客户号
	TDX_ID_CA_TXMM,				// 认证口令
	TDX_ID_CA_XTXMM,			// 新认证口令
	TDX_ID_CA_RESETFLAG,		// 重置标志
};
const WORD tdxCATXMMXGFieldAns[]=
{
	TDX_ID_CA_RESV,				// (保留)保留字段
};

// CA认证口令查询 808
const WORD tdxCATXMMCXFieldReq[]=
{
	TDX_ID_CA_KHH,				// 完整客户号
};
const WORD tdxCATXMMCXFieldAns[]=
{
	TDX_ID_CA_TXMM,				// 认证口令
	TDX_ID_CA_RESV,				// (保留)保留字段
};

// CA证书下载 810
const WORD tdxCAZSXZFieldReq[]=
{
	TDX_ID_CA_KHH,				// 完整客户号
	TDX_ID_CA_ZSXH,				// 证书序号
};
const WORD tdxCAZSXZFieldAns[]=
{
	TDX_ID_CA_AQJB,				// 安全级别
	TDX_ID_CA_ZSSHBZ,			// 证书审核标志(0:已经审核 1:正在等待审核)
	TDX_ID_CA_ZSXZBZ,			// 证书下载标志(0:不附加证书内容 1:附加证书内容)
	TDX_ID_CA_ZSQSID,			// 证书的券商ID
	TDX_ID_CA_ZSBFJG,			// 证书颁发机构
	TDX_ID_CA_ZSBFYH,			// 证书颁发用户
	TDX_ID_CA_ZSQSRQ,			// 证书起始日期(YYYYMMDD)
	TDX_ID_CA_ZSJZRQ,			// 证书截止日期(YYYYMMDD)
	TDX_ID_CA_ZSWS,				// 证书位数
	TDX_ID_CA_ZSGY,				// 证书公钥
};

// CA证书下载确认 812
const WORD tdxCAZSXZQRFieldReq[]=
{
	TDX_ID_CA_KHH,				// 完整客户号
};
const WORD tdxCAZSXZQRFieldAns[]=
{
	TDX_ID_CA_RESV,				// (保留)保留字段
};

// CA账户状态修改 814
const WORD tdxCAZTXGFieldReq[]=
{	TDX_ID_CA_KHH,				// 完整客户号
	TDX_ID_CA_CZJG,				// 操作结构
	TDX_ID_CA_CZY,				// 操作员
	TDX_ID_CA_CZMM,				// 操作密码
	TDX_ID_CA_CZSX,				// 操作属性
	TDX_ID_CA_CZBZ,				// 操作标志
};
const WORD tdxCAZTXGFieldAns[]=
{	TDX_ID_CA_RESV,				// (保留)保留字段
};

// CA证书更新 816
const WORD tdxCAZSGXFieldReq[]=
{
	TDX_ID_CA_KHH,				// 完整客户号
};
const WORD tdxCAZSGXFieldAns[]=
{
	TDX_ID_CA_AQJB,				// 当前用户安全级别
	TDX_ID_CA_ZSSHBZ,			// 证书审核标志(0,通过审核 1,正在等待审核)
	TDX_ID_CA_ZSXZBZ,			// 证书下载标志(0,未附加证书 1,附加有证书)
	TDX_ID_CA_ZSQSID,			// 证书券商ID
	TDX_ID_CA_ZSBFJG,			// 证书发布机构
	TDX_ID_CA_ZSBFYH,			// 证书颁发用户
	TDX_ID_CA_ZSQSRQ,			// 证书起始日期
	TDX_ID_CA_ZSJZRQ,			// 证书截至日期
	TDX_ID_CA_ZSWS,				// 证书位数
	TDX_ID_CA_ZSGY,				// 证书公钥
};


// 用户分级查询 818
const WORD tdxCAYHFJCXFieldReq[]=
{
	TDX_ID_CA_KHH,				// 完整客户号
};
const WORD tdxCAYHFJCXFieldAns[]=
{
	TDX_ID_CA_YHFJ,				// 用户分级
	TDX_ID_CA_YHJBMS,			// 用户级别描述
	TDX_ID_CA_YHJBZT,			// 用户级别状态
	TDX_ID_CA_YHJBBZ,			// 用户级别备注
};

// 用户分级申请 820
const WORD tdxCAYHFJSQFieldReq[]=
{
	TDX_ID_CA_KHH,				// 完整客户号
	TDX_ID_CA_YHFJ,				// 用户分级
};
const WORD tdxCAYHFJSQFieldAns[]=
{	TDX_ID_CA_YHFJ,				// 用户分级
	TDX_ID_CA_YHJBMS,			// 用户级别描述
	TDX_ID_CA_YHQX,				// 用户权限
};

// HTTP用户分级查询 822
const WORD tdxCAHTTPYHFJCXFieldReq[]=
{
	TDX_ID_CA_KHH,				// 完整客户号
};
const WORD tdxCAHTTPYHFJCXFieldAns[]=
{
	TDX_ID_CA_YHFJ,				// 用户分级
	TDX_ID_CA_YHJBMS,			// 用户级别描述
	TDX_ID_CA_YHQX,				// 用户权限
};

// 匿名用户申请 824
const WORD tdxCANMZCFieldReq[]=
{
	TDX_ID_CA_SJH,				// 客户号,用户手机号
	TDX_ID_CA_EMAIL,			// 用户email
	TDX_ID_CA_KHMC,				// 用户名称
};
const WORD tdxCANMZCFieldAns[]=
{
	TDX_ID_CA_RESV,				// 保留字段
};

// 新建主题 826
const WORD tdxCAXJZTFieldReq[]=
{
	TDX_ID_CA_KHH,
	TDX_ID_CA_KHJL,
	TDX_ID_CA_TOPICTITLE,
	TDX_ID_CA_CONTENT,
};
const WORD tdxCAXJZTFieldAns[]=
{
	TDX_ID_CA_TOPICID,
};

// 查询主题 828
const WORD tdxCACXZTFieldReq[]=
{
	TDX_ID_CA_KHH,
	TDX_ID_CA_QUERYDATE,
	TDX_ID_CA_QUERYALL,
	TDX_ID_CA_CLOSEFLAG,
};
const WORD tdxCACXZTFieldAns[]=
{
	TDX_ID_CA_TOPICID,
	TDX_ID_CA_TOPICTITLE,
	TDX_ID_CA_REMINDFLAG,
	TDX_ID_CA_NEWANSFLAG,
	TDX_ID_CA_CLOSEFLAG,
	TDX_ID_CA_KHJL,
	TDX_ID_CA_REQDATE,
	TDX_ID_CA_VALDATE,
};

// 查询回复 830
const WORD tdxCACXHFFieldReq[]=
{
	TDX_ID_CA_TOPICID,
};
const WORD tdxCACXHFFieldAns[]=
{
	TDX_ID_CA_ANSWERID,
	TDX_ID_CA_REQDATE,
	TDX_ID_CA_REQTIME,
	TDX_ID_CA_VALDATE,
	TDX_ID_CA_WHOANS,
	TDX_ID_CA_CONTENT,
	TDX_ID_CA_SATISFAC,
};

// 回复主题 832
const WORD tdxCAHFZTFieldReq[]=
{
	TDX_ID_CA_TOPICID,
	TDX_ID_CA_CONTENT,
};
const WORD tdxCAHFZTFieldAns[]=
{
	TDX_ID_CA_ANSWERID,
};

// (问题解决)关闭主题 834
const WORD tdxCAGBZTFieldReq[]=
{
	TDX_ID_CA_TOPICID,
	TDX_ID_CA_SATISFAC,
};
const WORD tdxCAGBZTFieldAns[]=
{
	TDX_ID_CA_TOPICID,
};

// 用户(留言)信息 836
const WORD tdxCAYHLYFieldReq[]=
{
	TDX_ID_CA_KHH,
	TDX_ID_CA_BRANCHMSGID,
};
const WORD tdxCAYHLYFieldAns[]=
{
	TDX_ID_CA_TOPICID,
	TDX_ID_CA_TOPICTITLE,
	TDX_ID_CA_CONTENT,
	TDX_ID_CA_REQDATE,
	TDX_ID_CA_CLOSEFLAG,
};

// 匿名用户激活 838
const WORD tdxCANMJHFieldReq[]=
{
	TDX_ID_CA_KHH,
	TDX_ID_CA_JHM,
};
const WORD tdxCANMJHFieldAns[]=
{
	TDX_ID_CA_RESV,				// 保留字段
};

// 匿名用户登录 840
const WORD tdxCANMDLFieldReq[]=
{
	TDX_ID_CA_KHH,
	TDX_ID_CA_TXMM,
};
const WORD tdxCANMDLFieldAns[]=
{
	TDX_ID_CA_RESV,				// 保留字段
};

// 查询是否有最新留言 842
const WORD tdxCANEWMSGFieldReq[]=
{
	TDX_ID_CA_KHH,
	TDX_ID_CA_BRANCHMSGID,
};
const WORD tdxCANEWMSGFieldAns[]=
{
	TDX_ID_CA_NEWMSGNUM,		// 我的问题:新信息条数
	TDX_ID_CA_NOREADMSGNUM,		// 我的问题:未读信息条数
	TDX_ID_CA_RESV,				// 保留字段
};

// 已阅读留言 844
const WORD tdxCAREADMSGFieldReq[]=
{
	TDX_ID_CA_TOPICID,			// 我的问题:主题ID
};
const WORD tdxCAREADMSGFieldAns[]=
{
	TDX_ID_CA_RESV,				// 保留字段
};

// 用户公告及生日提醒信息 846
const WORD tdxNOTICEINFOFieldReq[]=
{
	TDX_ID_CA_KHH,				// 客户号
	TDX_ID_XT_STARTPOS,			// 起始序号
};
const WORD tdxNOTICEINFOFieldAns[]=
{
	TDX_ID_CA_BIRTHTITIP,
	TDX_ID_CA_NOTICETITLE,
	TDX_ID_CA_NOTICECONTENT,
	TDX_ID_CA_RESV,
};

// 用户资讯信息反馈 848
const WORD tdxINFOFEEDBACKFieldReq[]=
{
	TDX_ID_CA_KHH,				// 客户号
	TDX_ID_CA_MENU,				// 栏目
	TDX_ID_CA_SJH,				// 手机号
	TDX_ID_CA_EMAIL,			// 电子邮件
	TDX_ID_CA_CONTENT,			// 建议正文
	TDX_ID_CA_CZBZ,				// 操作标志
};
const WORD tdxINFOFEEDBACKFieldAns[]=
{
	TDX_ID_CA_RESV,
};

// TQ客户校验 860
const WORD tdxTQKHJYFieldReq[]=
{	TDX_ID_CA_ZHLB,				// 账号类别(0:客户号 1:TQ号 2:TQ邮件)
	TDX_ID_CA_KHH,				// 账号信息
};
const WORD tdxTQKHJYFieldAns[]=
{	TDX_ID_CA_ZHLB,				// 账号类别
	TDX_ID_CA_KHH,				// 账号信息
	TDX_ID_CA_KHMC,				// 客户名称
	TDX_ID_CA_AQJB,				// 当前用户安全级别(1:SSL客户 2:通讯口令客户 4:证书客户)
	TDX_ID_CA_YHFJ,				// 用户分级
	TDX_ID_CA_YHJBMS,			// 用户级别描述
	TDX_ID_CA_YHQX,				// 用户权限
	TDX_ID_CA_TQID,				// 用户TQ号
	TDX_ID_CA_TQMAIL,			// 用户TQ邮件
};

// 西南证券用户投资顾问信息 862
const WORD  tdxUMUBROKERFieldReq[]=
{
	TDX_ID_CA_KHH,				// 客户号
	TDX_ID_CA_VER,				// 投资顾问资料版本
};
const WORD   tdxUMUBROKERFieldAns[]=
{
	TDX_ID_UM_BROKERCODE,		// 经纪人代码
	TDX_ID_UM_BROKERBRANCH,		// 经纪人营业部
	TDX_ID_UM_BROKERNAME,		// 经纪人名称
	TDX_ID_UM_BROKERSTATUS,		// 经纪人状态
	TDX_ID_UM_BROKERLEVEL,		// 经纪人级别
	TDX_ID_UM_UPBROKER,			// 上级经纪人
	TDX_ID_UM_BROKERNATIONALITY,// 经纪人国籍
	TDX_ID_UM_BROKERPHONECODE,	// 经纪人电话
	TDX_ID_UM_BROKERMOPHONE,	// 经纪人移动电话
	TDX_ID_UM_BROKEREMAIL,		// 经纪人电子邮件
	TDX_ID_UM_BROKERMSN,		// 经纪人MSN
	TDX_ID_UM_BROKERQQ,			// 经纪人QQ
	TDX_ID_UM_BROKERSEX,		// 经纪人性别
	TDX_ID_UM_BROKERAGE,		// 经纪人年龄
	TDX_ID_UM_BROKERDEGREE,		// 经纪人学历	
	TDX_ID_UM_PASSEXAM,			// 是否通过考试
	TDX_ID_UM_PRACTISETIME,		// 从业时间
	TDX_ID_UM_BROKERFAVOR,		// 经纪人操作习惯
	TDX_ID_UM_BROKERNATIVEPLACE,// 经纪人个人谏言
	TDX_ID_UM_BROKERQUAL,		// 经纪人从业资格
	TDX_ID_UM_BROKERSATISLEV,	// 经纪人投资顾问满意度级别
	TDX_ID_UM_BROKERPHOTOS,		// 经纪人照片
	TDX_ID_UM_BROKERNOTES,		// 经纪人备注
	TDX_ID_UM_BRANCHNAME,		// 营业部名称
	TDX_ID_UM_COMHOTLINE,		// 公司客户热线
	TDX_ID_UM_BRANCHTRADEASK,	// 营业部交易咨询电话
	TDX_ID_UM_BRANCHINVESTASK,	// 营业部投资咨询电话
	TDX_ID_CA_VER,				// 投资顾问资料版本
	TDX_ID_CA_RESV,				// 预留
};

// 试用(用户)注册 880
const WORD tdxCASYZCGDFieldReq[]=
{
	TDX_ID_CA_KHH,
};
const WORD tdxCASYZCGDFieldAns[]=
{
	TDX_ID_CA_RESV,
};

// (详细)信息录入 882
const WORD tdxCAXXLRGDFieldReq[]=
{
	TDX_ID_CA_KHH,
	TDX_ID_CA_KHMC,
	TDX_ID_CA_KHXB,
	TDX_ID_CA_ZJHM,
	TDX_ID_CA_EMAIL,
};
const WORD tdxCAXXLRGDFieldAns[]=
{
	TDX_ID_CA_JHM,
};

// 试用(用户)激活 884
const WORD tdxCASYJHGDFieldReq[]=
{
	TDX_ID_CA_KHH,
	TDX_ID_CA_JHM,
};
const WORD tdxCASYJHGDFieldAns[]=
{
	TDX_ID_CA_RESV,
};

// 账户校验 886
const WORD tdxCAZHJYGDFieldReq[]=
{
	TDX_ID_CA_KHH,
	TDX_ID_CA_TXMM,
	TDX_ID_CA_AQJB,				// 登录安全级别
	TDX_ID_CA_ZSGY,
	TDX_ID_CA_CERTSN,
	TDX_ID_CA_CZBZ,
	TDX_ID_CA_RESV,				// 请求预留信息
};
const WORD tdxCAZHJYGDFieldAns[]=
{
	TDX_ID_CA_KHMC,
	TDX_ID_CA_RESV,
	TDX_ID_CA_NOWLEVELNO,
	TDX_ID_CA_NOWLEVELNAME,
	TDX_ID_CA_CANLEVELNO,
	TDX_ID_CA_CANLEVELNAME,
};

// 等级查询 888
const WORD tdxCADJCXGDFieldReq[]=
{
	TDX_ID_CA_KHH,
};
const WORD tdxCADJCXGDFieldAns[]=
{
	TDX_ID_CA_YHFJ,
	TDX_ID_CA_LEVELNAME,
	TDX_ID_CA_ZBMAX,
	TDX_ID_CA_ZBMIN,
	TDX_ID_CA_TSUPDATE,
	TDX_ID_CA_PROTOC,
	TDX_ID_CA_COMMISION,
};

// 可申(请)级(别)查询 890
const WORD tdxCAKSJCXGDFieldReq[]=
{
	TDX_ID_CA_KHH,
	TDX_ID_CA_DRZB,
};
const WORD tdxCAKSJCXGDFieldAns[]=
{
	TDX_ID_CA_RESV,
};

// 客户申请(级别) 892
const WORD tdxCAKHSQGDFieldReq[]=
{
	TDX_ID_CA_KHH,
	TDX_ID_CA_AQJB,
};
const WORD tdxCAKHSQGDFieldAns[]=
{
	TDX_ID_CA_RESV,
};

// 用户资讯权限 894
const WORD tdxCAYHZXQXFieldReq[]=
{
	TDX_ID_CA_KHH,
};
const WORD tdxCAYHZXQXFieldAns[]=
{
	TDX_ID_CA_MENU,			// 可见栏目
	TDX_ID_CA_RESV,			// 保留字段,存放栏目显示方式
};

// 用户权限注销 896
const WORD tdxCAYHQXZXFieldReq[]=
{
	TDX_ID_CA_KHH,			// 完整客户号
};
const WORD tdxCAYHQXZXFieldAns[]=
{
	TDX_ID_CA_AQJB,			// 当前申请的安全级别
	TDX_ID_CA_ZSSHBZ,		// 证书审核标志
};

// 查询登陆历史 898
const WORD tdxCACXDLLSFieldReq[]=
{
	TDX_ID_CA_KHH,			// 800 完整客户号
 	TDX_ID_CA_QSRQ,			// 896 起始查询时间
 	TDX_ID_CA_ZZRQ,			// 897 终止查询时间
};
const WORD tdxCACXDLLSFieldAns[]=
{
	TDX_ID_CA_DLRQ,			// 899 登陆日期
	TDX_ID_CA_DLSJ,			// 898 登陆时间
	TDX_ID_CA_LASPROV,		// 892 登陆省份
	TDX_ID_CA_LASSITE,		// 894 登陆地点
	TDX_ID_CA_LASTIP,		// 890 登陆IP
	TDX_ID_CA_MAC,			// 4211 机器MAC地址
	TDX_ID_CA_JQTZM,		// 4201 机器特征码
};

//////////////////////////////////////////////////////////////////////////
//	银证转帐类
//////////////////////////////////////////////////////////////////////////

// 银证转帐 900
const WORD tdxYZZZFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式
	
	TDX_ID_ZJMM,				// 资金密码
	TDX_ID_YZZZ_ZZFX,			// 转帐方向(0-转入,1-转出)
	TDX_ID_YZZZ_YHDM,			// 银行代码
	TDX_ID_YZZZ_YHMM,			// 银行密码
	TDX_ID_YZZZ_ZZJE,			// 转帐金额

	TDX_ID_YZZZ_YHZH,			// (可选)银行帐号(如果"银行信息"功能返回了就送)
	TDX_ID_BZ,					// (可选)币种(如果"银行信息"功能返回了就送)

	TDX_ID_ZZFS,				// 转帐方式(港股转帐)
	TDX_ID_ZZQD,				// 转帐渠道(港股转帐)
	TDX_ID_ZZBH,				// 转帐编号(港股转帐)
	TDX_ID_FPYH,				// 发票银行(港股转帐)
	TDX_ID_ZPBH,				// 支票编号(港股转帐)

	TDX_ID_CZBZ,				// 操作标志(0--实时转帐,1--计划转帐,2--特殊转账判断请求,3--特殊转账执行请求)
	TDX_ID_WTRQ,				// 委托日期(计划转帐日期,CZBZ=1时有效)
	TDX_ID_WTSJ,				// 委托时间(计划转帐时间,CZBZ=1时有效)

	TDX_ID_ZJYHDM,				// 中继银行代码(港股转帐)
	TDX_ID_ZJYHMC,				// 中继银行名称(港股转帐)
	TDX_ID_ZJYHZH,				// 中继银行帐号(港股转帐)
	TDX_ID_ZJYHZHMC,			// 中继银行帐号名称(港股转帐)
	TDX_ID_XT_PARAM,			// 参数(特殊转账相关参数,CZBZ=3时有效)

	TDX_ID_ZRZJZH,				// 转入资金帐号
	TDX_ID_ZRYHDM,				// 转入银行代码
	TDX_ID_ZRYHZH,				// 转入银行帐号
	TDX_ID_ZCZJZH,				// 转出资金帐号
	TDX_ID_ZCYHDM,				// 转出银行代码
	TDX_ID_ZCYHZH,				// 转出银行帐号
};

// 银行流水 902
const WORD tdxYHLSFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式
	
	TDX_ID_YZZZ_YHDM,			// 银行代码
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_BZ,					// (可选)币种,送空查全部币种
	TDX_ID_YZZZ_YHZH,			// (可选)银行帐号(如果"银行信息"功能返回了就送)
};

// 银行余额 904
const WORD tdxYHYEFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式
	
	TDX_ID_ZJMM,				// 资金密码
	TDX_ID_YZZZ_YHDM,			// 银行代码
	TDX_ID_YZZZ_YHMM,			// 银行密码

	TDX_ID_YZZZ_YHZH,			// (可选)银行帐号(如果"银行信息"功能返回了就送)
	TDX_ID_BZ,					// 币种
	TDX_ID_CZBZ,				// 操作标志(0-发请求,1-取结果)
	TDX_ID_YZZZ_YHLSH,			// 银行流水号(TDX_ID_CZBZ==1时,用于查询结果)
};

// 修改银行密码 906
const WORD tdxXGYHMMFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式
	
	TDX_ID_YZZZ_YHDM,			// 银行代码
	TDX_ID_YZZZ_YHMM,			// 银行密码
	TDX_ID_YZZZ_XYHMM,			// 新银行密码

	TDX_ID_BZ,					// (保留)币种
	TDX_ID_YZZZ_YHZH,			// 银行帐号(如果"银行信息"功能返回了就送)
};

// 银行信息 908
const WORD tdxYHXXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式
};

// 三方存管转帐 910
const WORD tdxSFCGZZFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式
	
	TDX_ID_ZJMM,				// 资金密码
	TDX_ID_YZZZ_ZZFX,			// 转帐方向(0-转入,1-转出)
	TDX_ID_YZZZ_YHMM,			// 银行密码
	TDX_ID_YZZZ_ZZJE,			// 转帐金额
};

// 三方转帐查询 912
const WORD tdxSFZZCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式
	
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 三方余额查询 914
const WORD tdxSFYECXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式
	
	TDX_ID_ZJMM,				// 资金密码
	TDX_ID_YZZZ_YHMM,			// 银行密码
	TDX_ID_BZ,					// 币种
};

// 转帐修改 916
const WORD tdxZZXGFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式
	
	TDX_ID_ZJMM,				// 资金密码
	TDX_ID_YZZZ_ZZFX,			// 转帐方向(0-转入,1-转出)
	TDX_ID_YZZZ_YHDM,			// 银行代码
	TDX_ID_YZZZ_YHMM,			// 银行密码
	TDX_ID_YZZZ_ZZJE,			// 转帐金额

	TDX_ID_YZZZ_YHZH,			// (可选)银行帐号(如果"银行信息"功能返回了就送)
	TDX_ID_BZ,					// (可选)币种(如果"银行信息"功能返回了就送)

	TDX_ID_ZZFS,				// 转帐方式(港股转帐)
	TDX_ID_ZZQD,				// 转帐渠道(港股转帐)
	TDX_ID_ZZBH,				// 转帐编号(港股转帐)
	TDX_ID_FPYH,				// 发票银行(港股转帐)
	TDX_ID_ZPBH,				// 支票编号(港股转帐)

	TDX_ID_YZZZ_YHLSH,			// 银行流水号

	TDX_ID_ZJYHDM,				// 中继银行代码(港股转帐)
	TDX_ID_ZJYHMC,				// 中继银行名称(港股转帐)
	TDX_ID_ZJYHZH,				// 中继银行帐号(港股转帐)
	TDX_ID_ZJYHZHMC,			// 中继银行帐号名称(港股转帐)
	TDX_ID_WTRQ,				// 委托日期
	TDX_ID_WTSJ,				// 委托时间

	TDX_ID_CZBZ,				// 操作标志(与"银证转帐 900"功能相同)
	TDX_ID_ZRZJZH,				// 转入资金帐号
	TDX_ID_ZRYHDM,				// 转入银行代码
	TDX_ID_ZRYHZH,				// 转入银行帐号
	TDX_ID_ZCZJZH,				// 转出资金帐号
	TDX_ID_ZCYHDM,				// 转出银行代码
	TDX_ID_ZCYHZH,				// 转出银行帐号
};

// 转帐取消 918
const WORD tdxZZQXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_YZZZ_YHLSH,			// 银行流水号
	TDX_ID_CZBZ,				// 操作标志(与"银证转帐 900"功能相同)
	TDX_ID_YZZZ_YHDM,			// 银行代码
	TDX_ID_YZZZ_YHZH,			// 银行账号
	TDX_ID_YZZZ_ZZFX,			// 转账方向
	TDX_ID_YZZZ_ZZJE,			// 转账金额
	TDX_ID_BZ,					// 币种
	TDX_ID_WTRQ,				// 委托日期
	TDX_ID_WTSJ,				// 委托金额
};

// 可取资金查询 920
const WORD tdxKQZJCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_BZ,					// 币种
};

// 转帐银行查询 922
const WORD tdxZZYHCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号且有需要时送,否则送空,空--全部)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_BZ,					// 币种(查询指定币种,接口实现可能忽略,255(-1)--全部)
	TDX_ID_YZZZ_YHDM,			// 银行代码(查询指定银行信息,空--全部)
	TDX_ID_YZZZ_ZZFX,			// 转帐方向(0--转入,1--转出,255(-1)--全部)
	TDX_ID_ZZFS,				// 转帐方式(港股转帐,接口实现可能忽略,空--全部)
	TDX_ID_ZZQD,				// 转帐渠道(港股转帐,接口实现可能忽略,空--全部)
	TDX_ID_CZBZ,				// 操作标志

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 银行账户间转帐 924
const WORD tdxYHZHJZZFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号且有需要时送,否则送空,空--全部)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_CZBZ,				// 操作标志(1--计划转帐,其它--实时转帐)
	TDX_ID_WTRQ,				// 委托日期(计划转帐日期,CZBZ=1时有效)
	TDX_ID_WTSJ,				// 委托时间(计划转帐时间,CZBZ=1时有效)
	TDX_ID_BZ,					// 币种
	TDX_ID_YZZZ_ZZJE,			// 转帐金额
	TDX_ID_ZRYHDM,				// 转入银行代码
	TDX_ID_ZCYHDM,				// 转出银行代码
	TDX_ID_ZRYHZH,				// 转入银行帐号
	TDX_ID_ZCYHZH,				// 转出银行帐号
};

// 远端资金转帐 926
const WORD tdxYDZJZZFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_BZ,					// 币种
	TDX_ID_YZZZ_ZZFX,			// 转帐方向(0-转入,1-转出)
	TDX_ID_YZZZ_ZZJE,			// 转帐金额
};

// 远端转帐查询 928
const WORD tdxYDZZCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 远端资金查询 930
const WORD tdxYDZJCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 远端可转查询 932
const WORD tdxYDKZCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_BZ,					// 币种
	TDX_ID_YZZZ_ZZFX,			// 转账方向
};

// 银行卡列表查询 934
const WORD tdxYHKLBCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_ZJLB,				// 证件类别
	TDX_ID_ZJHM,				// 证件号码
	TDX_ID_KHMC,				// 客户名称
};

// 银行卡信息查询 936
const WORD tdxYHKXXCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_YZZZ_YHDM,			// 银行代码
	TDX_ID_YZZZ_YHMC,			// 银行名称
	TDX_ID_YHQC,				// 银行全称
	TDX_ID_YHKH,				// 银行卡号
	TDX_ID_ZJLB,				// 证件类别
	TDX_ID_ZJHM,				// 证件号码
	TDX_ID_KHMC,				// 客户名称
};

// 银行卡信息修改 938
const WORD tdxYHKXXXGFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_YZZZ_YHDM,			// 银行代码
	TDX_ID_YZZZ_YHMC,			// 银行名称
	TDX_ID_YHQC,				// 银行全称
	TDX_ID_YHKH,				// 银行卡号
	TDX_ID_ZJLB,				// 证件类别
	TDX_ID_ZJHM,				// 证件号码
	TDX_ID_KHMC,				// 客户名称
	TDX_ID_PROVINCE,			// 省份
	TDX_ID_CITY,				// 城市
};

// 银行卡变更操作 940
const WORD tdxYHKBGCZFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_CZBZ,				// 操作标志(0--鉴权,1--新增,2--删除,3--换卡,其他--未定义)
	TDX_ID_YZZZ_YHDM,			// 银行代码
	TDX_ID_YZZZ_YHMC,			// 银行名称
	TDX_ID_YHQC,				// 银行全称
	TDX_ID_YHKH,				// 银行卡号
	TDX_ID_ZJLB,				// 证件类别
	TDX_ID_ZJHM,				// 证件号码
	TDX_ID_KHMC,				// 客户名称
	TDX_ID_PROVINCE,			// 省份
	TDX_ID_CITY,				// 城市
	TDX_ID_SECTION,				// 辖区
	TDX_ID_DZDBZ,				// 对账单标志
	TDX_ID_DZDJSFS				// 对帐单寄送方式
};

// 银行卡费率查询 942
const WORD tdxYHKFLCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_YZZZ_YHDM,			// 银行代码
	TDX_ID_YZZZ_YHMC,			// 银行名称
	TDX_ID_YHQC,				// 银行全称
	TDX_ID_YHKH,				// 银行卡号
	TDX_ID_ZJLB,				// 证件类别
	TDX_ID_ZJHM,				// 证件号码
	TDX_ID_KHMC,				// 客户名称
};

// 账号间转账流水查询 944
const WORD tdxZHJZZLSCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

// 账号间转账当日流水查询 946
const WORD tdxZHJZZDRLSCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 银行余额流水查询 948
const WORD tdxYHYELSCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_YZZZ_YHDM,			// 银行代码
	TDX_ID_BZ,					// 币种
};

// 计划转账流水查询 950
const WORD tdxJHZZLSCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_YZZZ_YHDM,			// 银行代码
	TDX_ID_BZ,					// 币种
};

// 多存管银行流水查询 952
const WORD tdxDCGYHLSCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式
	
	TDX_ID_YZZZ_YHDM,			// 银行代码
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_BZ,					// (可选)币种,送空查全部币种
	TDX_ID_YZZZ_YHZH,			// (可选)银行帐号(如果"银行信息"功能返回了就送)
};

// 多存管账号同步 954
const WORD tdxDCGZHTBFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_CZBZ,				// 操作标志(1--同步资金密码,2--同步账号信息)
};

// 换汇业务操作 990
const WORD tdxHHYWCZFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_CZBZ,				// 操作标志(偶数--信息查询,奇数--业务操作,详见"标识字段统计")
	TDX_ID_XT_PARAM,			// 参数(用于从其他查询传递参数到"业务操作")
	TDX_ID_ZJMM,				// 资金密码
	TDX_ID_YZZZ_YHDM,			// 银行代码
	TDX_ID_YZZZ_YHMM,			// 银行密码
	TDX_ID_YZZZ_ZZJE,			// 转账金额(换汇金额)
	TDX_ID_BZ,					// 币种(换出货币)
	TDX_ID_DFBZ,				// 对方币种(换入货币)
	TDX_ID_DQHL,				// 当前汇率
};

// 换汇银行查询 992
const WORD tdxHHYHCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_YZZZ_YHDM,			// 银行代码
};

// 换汇汇率查询 994
const WORD tdxHHHLCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_YZZZ_YHDM,			// 银行代码
	TDX_ID_BZ,					// 币种(换出货币)
	TDX_ID_DFBZ,				// 对方币种(换入货币)
};

// 换汇委托查询 996
const WORD tdxHHWTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

////////////////////////////////////////////////////////////////////////////
//日志查看类
////////////////////////////////////////////////////////////////////////////

// (日志)客户校验 100
const WORD tdxRZKHJYFieldReq[]=
{
	TDX_ID_KHH,				// 客户号
	TDX_ID_JYMM,			// 客户密码	
};

// (日志)取缓存信息 112
const WORD tdxRZCACHEFieldReq[]=
{
	TDX_ID_KHH,				// 客户号
	TDX_ID_JYMM,			// 客户密码	
};

// (日志)股东查询 1122
const WORD tdxRZGDCXFieldReq[]=
{
	TDX_ID_KHH,				// 客户号
	TDX_ID_JYMM,			// 客户密码	
};

// (日志)银行信息 908
const WORD tdxRZYHXXFieldReq[]=
{
	TDX_ID_KHH,				// 客户号
	TDX_ID_JYMM,			// 客户密码	
};

// (日志)修改密码 106
const WORD tdxRZXGMMFieldReq[]=
{
	TDX_ID_KHH,						// 申请账号
	TDX_ID_JYMM,					// 账号密码
	TDX_ID_XJYMM,					// 新账号密码
};

// 客户操作记录查询 1002
const WORD tdxRZKHCZJLCXFieldReq[]=
{
	TDX_ID_RZ_STARTTIME,			// 查询开始时间
	TDX_ID_RZ_ENDTIME,				// 查询结束时间
	TDX_ID_RZ_TCTIME,				// 查询交易中心时间
	TDX_ID_RZ_APITIME,				// 查询API时间
	TDX_ID_RZ_QUEUETIME,			// 查询排队时间
	TDX_ID_RZ_FUNCID,				// 操作功能号
	TDX_ID_KHH,						// 客户号
	TDX_ID_XT_BRANCHID,				// 真实营业部
	TDX_ID_XT_STARTPOS,				// 起始序号
	TDX_ID_ZJZH,					// 资金账号
	TDX_ID_RETINFO,					// 错误信息
	TDX_ID_RZ_PAGEINDEX,			// 页码序号
	TDX_ID_RZ_CXFLAG,				// 查询类别
	TDX_ID_RZ_DAY,					// 查询日期
};
const WORD tdxRZKHCZJLCXFieldAns[]=
{
	TDX_ID_RZ_LOGID,				// 日志记录标号
	TDX_ID_RZ_TCIP,					// 交易中心IP
	TDX_ID_RZ_LOGTIME,				// 日志记录时间
	TDX_ID_XT_IPADDR,				// 客户端IP
	TDX_ID_XT_MACADDR,				// 客户端MAC
	TDX_ID_KHH,						// 客户号
	TDX_ID_XT_BRANCHID,				// 实际营业部ID
	TDX_ID_ZJZH,					// 资金账号
	TDX_ID_RZ_FUNCID,				// 操作功能ID
	TDX_ID_RZ_FLAGRESULT,			// 处理结果标志
	TDX_ID_RZ_TCTIME,				// 交易中心耗时
	TDX_ID_RZ_APITIME,				// API耗时
	TDX_ID_RZ_QUEUETIME,			// 排队耗时
	TDX_ID_RETINFO,					// 错误信息
	TDX_ID_RZ_PAGEINDEX,			// 页码序号
};

// 帐号申请 1004
const WORD tdxRZZHSQFieldReq[]=
{
	TDX_ID_ZJZH,					// 申请账号
	TDX_ID_JYMM,					// 账号密码
	TDX_ID_KHMC,					// 账号名称
	TDX_ID_XT_BRANCHID,				// 营业部
	TDX_ID_RZ_LEVER,				// 用户等级
};

// 帐号冻结解冻 1006
const WORD tdxRZZHDJJDFieldReq[]=
{
	TDX_ID_CZBZ,					// 操作标志（冻结1，解冻2）
	TDX_ID_ZJZH,					// 冻结、解冻账号
	TDX_ID_RZ_LEVER,				// 操作者用户等级
};

// 查询统计分析 1008
const WORD tdxRZCXTJFXFieldReq[]=
{
	TDX_ID_RZ_STARTTIME,			// 查询开始时间
	TDX_ID_RZ_ENDTIME,				// 查询结束时间
	TDX_ID_RZ_FUNCID,				// 操作功能ID
	TDX_ID_XT_STARTPOS,				// 起始序号
	TDX_ID_RZ_PAGEINDEX,			// 页码序号
};

// 启动与关闭查询 1010
const WORD tdxRZQDYGBCXFieldReq[]=
{
	TDX_ID_RZ_STARTTIME,			// 查询开始时间
	TDX_ID_RZ_ENDTIME,				// 查询结束时间
	TDX_ID_XT_STARTPOS,				// 起始序号
	TDX_ID_RZ_PAGEINDEX,			// 页码序号
};

// 后台繁忙程度1012
const WORD tdxRZHTFMCDFieldReq[]=
{
	TDX_ID_RZ_STARTTIME,			// 查询开始时间
	TDX_ID_RZ_ENDTIME,				// 查询结束时间
	TDX_ID_RZ_ITEMNUM,				// 记录条数
	TDX_ID_XT_STARTPOS,				// 起始序号
	TDX_ID_RZ_PAGEINDEX,			// 页码序号
};

// 后台超负荷查询 1014
const WORD tdxRZHTCFHCXFieldReq[]=
{
	TDX_ID_RZ_STARTTIME,			// 查询开始时间
	TDX_ID_RZ_ENDTIME,				// 查询结束时间
	TDX_ID_XT_STARTPOS,				// 起始序号
	TDX_ID_RZ_PAGEINDEX,			// 页码序号
};

// 风险IP排名 1016
const WORD tdxRZFXIPPMFieldReq[]=
{
	TDX_ID_RZ_STARTTIME,			// 查询开始时间
	TDX_ID_RZ_ENDTIME,				// 查询结束时间
	TDX_ID_RZ_ITEMNUM,				// 记录条数
	TDX_ID_XT_STARTPOS,				// 起始序号
	TDX_ID_RZ_PAGEINDEX,			// 页码序号
};

// 风险账号 1018
const WORD tdxRZFXZHFieldReq[]=
{
	TDX_ID_RZ_STARTTIME,			// 查询开始时间
	TDX_ID_RZ_ENDTIME,				// 查询结束时间
	TDX_ID_RZ_ITEMNUM,				// 记录条数
	TDX_ID_XT_STARTPOS,				// 起始序号
	TDX_ID_RZ_PAGEINDEX,			// 页码序号
};

// 风险详细信息 1020
const WORD tdxRZFXXXXXFieldReq[]=
{
	TDX_ID_RZ_STARTTIME,			// 查询开始时间
	TDX_ID_RZ_ENDTIME,				// 查询结束时间
	TDX_ID_ZJZH,					// 资金账号
	TDX_ID_XT_IPADDR,				// 客户IP
	TDX_ID_XT_STARTPOS,				// 起始序号
	TDX_ID_RZ_PAGEINDEX,			// 页码序号
};

// 后台繁忙程度详细 1022
const WORD tdxRZHTFMCDXXFieldReq[]=
{
	TDX_ID_RZ_STARTTIME,			// 查询开始时间
	TDX_ID_RZ_ENDTIME,				// 查询结束时间
	TDX_ID_RZ_TCIP,					// 交易中心IP
	TDX_ID_XT_STARTPOS,				// 起始序号
};

// 交易中心IP 1024
const WORD tdxRZTCIPFieldReq[] =
{
	TDX_ID_KHH,				// 客户号
	TDX_ID_JYMM,			// 客户密码	
};

//////////////////////////////////////////////////////////////////////////
//	查询类
//////////////////////////////////////////////////////////////////////////

// 撤单查询 1100
const WORD tdxCDCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号

	TDX_ID_KSRQ,				// (保留,期货)开始日期
	TDX_ID_ZZRQ,				// (保留,期货)终止日期
};

// 当日委托查询 1102
const WORD tdxDRWTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_XT_PARAM,			// 参数
};

// 历史委托查询 1104 (可选)
const WORD tdxLSWTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_ZQDM,				// (可选)证券代码,送空查全部股票
};

// 委托查询 1106　(可选)
const WORD tdxWTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 当日成交查询 1108
const WORD tdxDRCJCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_CJBH,				// 成交编号
};

// 历史成交查询 1110
const WORD tdxLSCJCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_ZQDM,				// (可选)证券代码,送空查全部股票
};

// 成交查询 1112
const WORD tdxCJCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 股份查询 1114
const WORD tdxGFCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式
	
	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_ZQDM,				// 证券代码
	TDX_ID_CZBZ,				// 操作标志(1--信用交易时查普通账号股份)
	TDX_ID_XT_MODE,				// 模式(客户端可选的字段内容控制,按位设置,0x00000001--浮动盈亏不带手续费)
	TDX_ID_XT_FUNCTIONVERSION,	// 功能版本
};

// 新股配号 1116
const WORD tdxXGPHFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 资金流水 1118
const WORD tdxZJLSFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式
	
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_BZ,					// (可选)币种(一般不用)
	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 交割单 1120
const WORD tdxJGDFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_ZQDM,				// (可选)证券代码,送空查全部股票
};

// 股东查询 1122
const WORD tdxGDCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_CZBZ,				// 操作标志(1--信用交易时查普通账号股东)
	TDX_ID_DFFZDM,				// 对方分支代码
	TDX_ID_DFKHDM,				// 对方客户代码
	TDX_ID_DFZJZH,				// 对方资金账号(支持多资金帐号时送,否则送空)
	TDX_ID_DFMM,				// 对方密码
};

// 证券信息 1124
const WORD tdxZQXXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_MMBZ,				// 买卖标志(0-限价买入 1-限价卖出 'C'-市价买入 ...)
	TDX_ID_ZQDM,				// 证券代码
	TDX_ID_HYDM,				// (废弃,期货)合约代码
	TDX_ID_ZQXXYXBZ,			// 证券信息有效标志(1--需要查询额外的证券信息)
	TDX_ID_XT_CHECKRISKFLAG,	// 检查风险标志
	TDX_ID_XT_FUNCTIONVERSION,	// 功能版本
};

// 中签查询 1126
const WORD tdxZQCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式
	
	TDX_ID_SCFLAG,				// (保留)市场代码
	TDX_ID_ZQDM,				// 证券代码
	TDX_ID_XT_STARTPOS,			// 起始序号
	
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

// 修改成本价 1128
const WORD tdxXGCBJFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_SCFLAG,				// 市场代码(必送,不要用TDX_ID_ZHLB)
	TDX_ID_ZQDM,				// 证券代码
	TDX_ID_CBJ,					// 新成本价
	TDX_ID_XWDM,				// 席位代码("股份查询"返回了就送)
	TDX_ID_MRJJ,				// 买入均价
	TDX_ID_CCJJ,				// 持仓均价
	TDX_ID_SXYK,				// 实现盈亏
};

// (查询)修改联系方式 1130
const WORD tdxXGLXFSFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式
	
	TDX_ID_CZBZ,				// 操作标志(0-查询,1-修改)
	TDX_ID_USERPHONE,			// 用户联系电话
	TDX_ID_USEREMAIL,			// 用户EMAIL
	TDX_ID_USERADDRESS,			// 用户通讯地址

    TDX_ID_KHMC,				// (可选)客户名称
    TDX_ID_ZJHM,				// (可选)证件号码
    TDX_ID_POSTALCODE,			// 邮政编码
    TDX_ID_MOBILEPHONE,			// 移动电话
	TDX_ID_WORKPHONE,			// 单位电话
	TDX_ID_HOMEPHONE,			// 住宅电话
	TDX_ID_MAILADDRESS,			// 邮寄地址
	TDX_ID_XT_PARAM,			// 参数
	TDX_ID_FAX,					// 传真
	TDX_ID_EDU,					// 教育程度
	TDX_ID_VOCATION,			// 职业
	TDX_ID_PROVINCE,			// 省份
	TDX_ID_CITY,				// 城市
	TDX_ID_SECTION,				// 辖区名称
	TDX_ID_BPCALL,				// 寻呼机号
	TDX_ID_ZBDLJYXX,			// 周边登录校验信息
	TDX_ID_XT_LOGINEMAIL,		// 登录Email
	TDX_ID_XT_TRADEEMAIL,		// 交易Email
	TDX_ID_XT_MOBILECHECKCODE,	// 手机验证码
	TDX_ID_SALARY,				// 收入
};

// 对帐单 1132
const WORD tdxDZDFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式
	
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_BZ,					// (可选)币种(一般不用)
	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 配售权益查询 1134
const WORD tdxPSQYCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 权证信息查询 1136
const WORD tdxQZXXCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_ZQDM,				// 证券代码
	TDX_ID_MMBZ,				// 买卖标志
	TDX_ID_CZBZ,				// 操作标记(0--权证信息 1--期权信息)
};

// 成交汇总查询 1138
const WORD tdxCJHZCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 股份汇总查询 1140
const WORD tdxGFHZCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 权证开通取消 1142
const WORD tdxQZKTQXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式
	
	TDX_ID_CZBZ,				// 操作标志(0-开通,1-取消)
	TDX_ID_LX,					// (协议)类型(各个dll自己定义,交易中心配置)
};

// 预委托查询 1144
const WORD tdxYWTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 签订协议 1146
const WORD tdxQDXYFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_LX,					// 类型(0--电子约定书,1--债券回购,)
	TDX_ID_CZBZ,				// 操作标志(1--开通,2--取消,)
};


// 在途资金查询 1148 (保留)
const WORD tdxZTZJCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式
};

// 金股信转帐 1150 (保留)
const WORD tdxJGXZZFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式
	
	TDX_ID_WTJE,				// 委托金额
};

// 分支代码 1152(保留)
const WORD tdxFZDMFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式
};

// 获取协议内容 1154
const WORD tdxHQXYNRFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_LX,					// (协议)类型(各个dll自己确定,交易中心配置)
};

// 获取IPO列表 1156
const WORD tdxHQIPOLBFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式
	
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_XT_STARTPOS,			// 起始序号
};

// IPO信息查询 1158
const WORD tdxIPOXXCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_ZQDM,				// 证券代码
};

// 预受要约查询 1160
const WORD tdxYYCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

// 预受要约撤单 1162
const WORD tdxYYCDFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式
	
	TDX_ID_ZQDM,				// 证券代码
	TDX_ID_YYSL,				// 要约数量
	TDX_ID_SGRDM,				// 申购人代码
};

// 预受要约申报 1164
const WORD tdxYYSBFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式
	
	TDX_ID_MMBZ,				// (保留)买卖标志(0-限价买入 1-限价卖出 'C'-市价买入 ...)
	TDX_ID_SGRDM,				// 申购人代码
	TDX_ID_TXMM,				// (保留)通讯密码
	TDX_ID_SCFLAG,				// (保留)市场代码
	TDX_ID_ZQDM,				// 证券代码
	TDX_ID_WTJG,				// (保留)委托价格
	TDX_ID_JYDW,				// (保留)交易单位
	TDX_ID_WTSL,				// 委托数量*
};

// 质押回购 1166
const WORD tdxZYHGFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式
	TDX_ID_MMBZ,				// 买卖标志(0-质押 1-回购)
	TDX_ID_TXMM,				// (保留)通讯密码
	TDX_ID_SCFLAG,				// (保留)市场代码
	TDX_ID_ZQDM,				// 证券代码
	TDX_ID_WTJG,				// 委托价格(客户端送1)
	TDX_ID_JYDW,				// (保留)交易单位
	TDX_ID_WTSL,				// 委托数量
	TDX_ID_WTFS,				// (保留)委托方式
};

// 未交收成交明细查询 1168
const WORD tdxWJSCJMXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式
	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 存管预约存取业务 1170
const WORD tdxCGYYCQFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_BZ,					// 币种
	TDX_ID_YZZZ_ZZJE,			// 取款金额
	TDX_ID_KSRQ,				// 发生日期
	TDX_ID_ZY,					// 摘要
	TDX_ID_YZZZ_YHDM,			// 银行代码
};

// 存管预约存取业务查询 1172
const WORD tdxCGYYCQCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_CZBZ,				// 标志	 (0:"查询全部",1:"审核完成",2:"不通过",3:"待审核")
	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 委托汇总查询 1174
const WORD tdxWTHZCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 资金明细查询 1176
const WORD tdxZJMXCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 查询选择存管银行 1178
const WORD tdxCXXZCGYHFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式
};

// 选择存管银行 1180
const WORD tdxXZCGYHFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_YZZZ_YHDM,			// 银行代码
	TDX_ID_YZZZ_YHZH,			// 银行帐号
};

// 查询协议信息 1182
const WORD tdxCXXYXXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式
};

// 历史成交汇总查询 1184
const WORD tdxLSCJHZCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 成交明细查询 1186
const WORD tdxCJMXCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 委托查询明细 1188
const WORD tdxWTCXMXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_WTRQ,				// 委托日期
	TDX_ID_WTBH,				// 委托编号
	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_ZQDM,				// 证券代码
	TDX_ID_ZQMC,				// 证券名称
	TDX_ID_MMBZ,				// 买卖标志
	TDX_ID_MMBZSM,				// 买卖标志说明
	TDX_ID_WTFS,				// 委托类别
	TDX_ID_WTFSSM,				// 委托类别说明
	TDX_ID_CJSX,				// 成交属性
};

// 成交查询明细 1190
const WORD tdxCJCXMXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_WTRQ,				// 委托日期
	TDX_ID_WTBH,				// 委托编号
	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_ZQDM,				// 证券代码
	TDX_ID_ZQMC,				// 证券名称
	TDX_ID_MMBZ,				// 买卖标志
	TDX_ID_MMBZSM,				// 买卖标志说明
	TDX_ID_WTFS,				// 委托类别
	TDX_ID_WTFSSM,				// 委托类别说明
	TDX_ID_CJSX,				// 成交属性
};

// 意向申报行情查询 1192
const WORD tdxYXSBHQCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_MMBZ,				// 买卖标志
	TDX_ID_WTFS,				// (买卖标志相关)委托方式
	TDX_ID_ZQDM,				// 证券代码
	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 批量委托查询 1194
const WORD tdxPLWTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_ZQDM,				// 证券代码
	TDX_ID_XT_STARTPOS,			// 起始序号
};

// LOF合并相关代码查询 1196
const WORD tdxLOFHBXGDMCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_ZQDM,				// 证券代码
};

// LOF分拆相关代码查询 1198
const WORD tdxLOFFCXGDMCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_ZQDM,				// 证券代码
};

// LOF盘后业务当日委托查询 1200
const WORD tdxLOFPHYWDRWTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// LOF盘后业务历史委托查询 1202
const WORD tdxLOFPHYWLSWTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

// LOF盘后业务当日成交查询 1204
const WORD tdxLOFPHYWDRCJCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// LOF盘后业务历史成交查询 1206
const WORD tdxLOFPHYWLSCJCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

// LOF盘后业务撤单查询 1208
const WORD tdxLOFPHYWCDCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 附属股份查询 1210
const WORD tdxFSGFCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 证券附属信息查询 1212
const WORD tdxZQFSXXCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_ZQDM,				// 证券代码
};

// 报价转让撤单查询 1214
const WORD tdxBJZRCDCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 报价转让委托查询 1216
const WORD tdxBJZRWTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 报价转让成交查询 1218
const WORD tdxBJZRCJCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 动态股份查询 1220
const WORD tdxDTGFCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_XT_MODE,				// 模式
	TDX_ID_XT_FUNCTIONVERSION,	// 功能版本
	TDX_ID_CZBZ,				// 操作标志
};

// 债券质押库查询 1222
const WORD tdxZQZYKCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_MMBZ,				// 买卖标志
	TDX_ID_ZQDM,				// 证券代码
	TDX_ID_CZBZ,				// 操作标志
};

// 多存管资金明细查询 1224
const WORD tdxDCGZJMXCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 历史持仓查询 1226
const WORD tdxLSCCCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

// 股份明细查询 1228
const WORD tdxGFMXCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 股份查询(2nd版) 1230
const WORD tdxGFCXSECONDFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式
	
	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_ZQDM,				// 证券代码
	TDX_ID_CZBZ,				// 操作标志(1--信用交易时查普通账号股份)
	TDX_ID_XT_MODE,				// 模式(客户端可选的字段内容控制,按位设置,0x00000001--浮动盈亏不带手续费)
};

// 股份查询(3rd版) 1232
const WORD tdxGFCXTHIRDFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_ZQDM,				// 证券代码
	TDX_ID_CZBZ,				// 操作标志(1--信用交易时查普通账号股份)
	TDX_ID_XT_MODE,				// 模式(客户端可选的字段内容控制,按位设置,0x00000001--浮动盈亏不带手续费)
};

// 债券回购合约查询 1234
const WORD tdxZQHGHYCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

// 客户对账信息查询 1236
const WORD tdxKHDZXXCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

// 综合协议行情查询 1238
const WORD tdxZHXYHQCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_MMBZ,				// 买卖标志
	TDX_ID_WTFS,				// (买卖标志相关)委托方式
	TDX_ID_ZQDM,				// 证券代码
	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 标准券汇总查询 1240
const WORD tdxBZQHZCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 柜台债券行情查询 1242
const WORD tdxGTZQHQCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_MMBZ,				// 买卖标志
	TDX_ID_WTFS,				// (买卖标志相关)委托方式
	TDX_ID_ZQDM,				// 证券代码
};

// 融资行权合约查询 1244
const WORD tdxRZXQHYCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_CZZT,				// 操作状态(-1/0--全部;其余按位设置:0x1--可还合约,0x2--待交收,0x4--交收失败,0x8--已了结)
};

// 融资行权客户信息查询 1246
const WORD tdxRZXQKHXXCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 债券回购历史查询 1248
const WORD tdxZQHGLSCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

// 期权代码查询 1250
const WORD tdxQQDMCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 期权持仓查询 1252
const WORD tdxQQCCCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 期权所得税查询 1254
const WORD tdxQQSDSCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

// 期权当日委托查询 1256
const WORD tdxQQDRWTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_CZBZ,				// 操作标志(0--查询全部委托,1--查询可撤单委托)
};

// 期权历史委托查询 1258
const WORD tdxQQLSWTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

//////////////////////////////////////////////////////////////////////////
//	期货交易类(原用于模拟环境,现部分用于生产环境)
//////////////////////////////////////////////////////////////////////////

// 期货委托 1500 (保留)
const WORD tdxQHWTFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式
	
	TDX_ID_MMBZ,				// 买卖标志(0-限价买入 1-限价卖出 'C'-市价买入 ...)
	TDX_ID_KPBZ,				// 开平标志
	TDX_ID_QHZH,				// 期货帐号
	TDX_ID_TXMM,				// (保留)通讯密码
	TDX_ID_SCFLAG,				// (保留)市场代码
	TDX_ID_HYDM,				// 和约代码
	TDX_ID_WTJG,				// 委托价格
	TDX_ID_JYDW,				// 交易单位
	TDX_ID_WTSL,				// 委托数量
};

// 查询期货持仓 1502 (保留)
const WORD tdxCXQHCCFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式
	
	TDX_ID_QHZH,				// 期货帐号
};

// 查询合约信息 1504 (保留)
const WORD tdxCXHYXXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东类别)
	TDX_ID_GDDM,				// 股东代码
	TDX_ID_OP_WTFS,				// 操作方式
	
	TDX_ID_QHZH,				// 期货帐号
	TDX_ID_HYDM,				// 合约代码
};

// 查询可交易合约 1506
const WORD tdxCXKJYHYFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式
	
	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_CZBZ,				// 操作标志(0--查询全部合约,1--查询指定市场的可用合约,默认--0)
	TDX_ID_SCFLAG,				// 市场代码(CZBZ=1时有效)
};

// 当日资金流水 1508
const WORD tdxDRZJLSFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式
	
	TDX_ID_BZ,					// (可选)币种(一般不用)
	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 期货委托状态查询 1510
const WORD tdxQHWTZTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式
	
	TDX_ID_WTBH,				// 委托编号
};

// 期货委托回报 1512 [推送功能,请求不使用]
const WORD tdxQHWTHBFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式
};

// 期货委托回报 1513

// 期货撤单回报 1514 [推送功能,请求不使用]
const WORD tdxQHCDHBFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式
};

// 期货撤单回报 1515

// 期货成交回报 1516 [推送功能,请求不使用]
const WORD tdxQHCJHBFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式
};

// 期货成交回报 1517

// 期货信息发布 1518 [推送功能,请求不使用]
const WORD tdxQHXXFBFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式
};

// 期货信息发布 1519

// 期货交易所状态改变 1520 [推送功能,请求不使用]
const WORD tdxQHJYSZTGBFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式
};

// 期货交易所状态改变 1521

// 期货组合合约变更 1522 [推送功能,请求不使用]
const WORD tdxQHZHHYBGFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式
};

// 期货组合合约变更 1523

// 期货组合委托回报 1524 [推送功能,请求不使用]
const WORD tdxQHZHWTHBFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式
};

// 期货组合委托回报 1525

// 期货组合撤单回报 1526 [推送功能,请求不使用]
const WORD tdxQHZHCDHBFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式
};

// 期货组合撤单回报 1527

// 期货订单类型查询 1528
const WORD tdxQHDDLXCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_MODE,				// 模式(0--非组合,1--组合,空--全部)
	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 期货组合委托 1530
const WORD tdxQHZHWTFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XWDM,				// 席位代码
	TDX_ID_WTSL,				// 委托数量
	TDX_ID_WTJG,				// 委托价格
	TDX_ID_CLDM,				// 策略代码
	TDX_ID_WTFS,				// 委托类型
	TDX_ID_CJSX,				// 成交属性
	TDX_ID_ZHLX,				// 组合类型
	TDX_ID_MMBZ,				// 买卖标志
	TDX_ID_KPBZ,				// 开平标志
	TDX_ID_TBBZ,				// 投保标志
	TDX_ID_HYDM1,				// 合约代码1
	TDX_ID_HYDM2,				// 合约代码2
	TDX_ID_HYDM3,				// 合约代码3
	TDX_ID_HYDM4,				// 合约代码4
	TDX_ID_XT_TOKEN,			// 令牌
};

// 期货组合撤单 1532
const WORD tdxQHZHCDFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XWDM,				// 席位代码
	TDX_ID_WTBH,				// 委托编号
	TDX_ID_XT_PARAM,			// 参数
};

// 期货组合合约查询 1534
const WORD tdxQHZHHYCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 期货组合持仓查询 1536
const WORD tdxQHZHCCCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 期货组合委托查询 1538
const WORD tdxQHZHWTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 期货组合计算可委托数 1540
const WORD tdxQHZHJSKWTSFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_XWDM,				// 席位代码
	TDX_ID_CLDM,				// 策略代码
	TDX_ID_MMBZ,				// 买卖标志
	TDX_ID_TBBZ,				// 投保标志
	TDX_ID_HYDM1,				// 合约代码1
	TDX_ID_HYDM2,				// 合约代码2
	TDX_ID_HYDM3,				// 合约代码3
	TDX_ID_HYDM4,				// 合约代码4
	TDX_ID_ZHLX,				// 组合类型
};

// 期货组合策略查询 1542
const WORD tdxQHZHCLCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 操作方式

	TDX_ID_CLDM,				// 策略代码
	TDX_ID_ZHLX,				// 组合类型
	TDX_ID_XT_STARTPOS,			// 起始序号
};

//////////////////////////////////////////////////////////////////////////
//	回购类
//////////////////////////////////////////////////////////////////////////
// 股票质押回购 1800
const WORD tdxGPZYHGFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_HZHGZT,				// 回购状态(1--初始交易申请,2--补充质押申请,3--部分解除质押申请,4--购回申请,5--申报撤销)
	TDX_ID_LX,					// 类型(1--到期购回,2--提前购回,3--延期购回)
	TDX_ID_CPDM,				// 产品代码
	TDX_ID_WTSL,				// 委托数量
	TDX_ID_WTJE,				// 委托金额
	TDX_ID_WTRQ,				// 委托日期
	TDX_ID_WTBH,				// 委托编号
	TDX_ID_CJRQ,				// 成交日期
	TDX_ID_CJBH,				// 成交编号
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_SCFLAG,				// 市场代码
	
	TDX_ID_XWDM,				// 席位代码
	TDX_ID_DFXWDM,				// 对方席位代码
	TDX_ID_DFGDDM,				// 对方股东代码
};

// 股票质押回购申请查询 1802
const WORD tdxGPZYHGSQCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 股票质押回购合同查询 1804
const WORD tdxGPZYHGHTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 股票质押回购权益查询 1806
const WORD tdxGPZYHGQYCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 股票质押回购期限利率查询 1808
const WORD tdxGPZYHGQXLLCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 股票质押回购流水查询 1810
const WORD tdxGPZYHGLSCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 股票质押回购融出方查询 1812
const WORD tdxGPZYHGRCFCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 股票质押回购利息查询 1814
const WORD tdxGPZYHGLXCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 股票质押回购历史合同查询 1816
const WORD tdxGPZYHGLSHTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 股票质押回购标的证券查询 1818
const WORD tdxGPZYHGBDZQCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 特色回购 1830
const WORD tdxTSHGFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_HZHGZT,				// 回购状态(1--登记,2--修改,3--取消)
	TDX_ID_CPDM,				// 产品代码
	TDX_ID_WTSL,				// 委托数量
	TDX_ID_WTJE,				// 委托金额
	TDX_ID_WTRQ,				// 委托日期
	TDX_ID_WTBH,				// 委托编号
	TDX_ID_CJRQ,				// 成交日期
	TDX_ID_CJBH,				// 成交编号
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_SCFLAG,				// 市场代码
	
	TDX_ID_XWDM,				// 席位代码
	TDX_ID_DFXWDM,				// 对方席位代码
	TDX_ID_DFGDDM,				// 对方股东代码
};

// 特色回购信息查询 1832
const WORD tdxTSHGXXCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_CPDM,				// 产品代码
	TDX_ID_LX,					// 类型(0--泉购通 1-泉银通)
};

// 特色回购申请查询 1834
const WORD tdxTSHGSQCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 特色回购代码查询 1836
const WORD tdxTSHGDMCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 特色回购银证通 1838
const WORD tdxTSHGYZTFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_ZJMM,				// 资金密码
	TDX_ID_YZZZ_ZZFX,			// 转帐方向
	TDX_ID_YZZZ_YHDM,			// 银行代码
	TDX_ID_YZZZ_YHMM,			// 银行密码
	TDX_ID_YZZZ_ZZJE,			// 转帐金额

	TDX_ID_CZBZ,				// 操作标志(1--登记,2--修改,3--取消)
	TDX_ID_WTRQ,				// 委托日期
	TDX_ID_WTSJ,				// 委托时间
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_CZZT,				// 操作状态(0--正常 1--暂停)
};

// 特色回购转账计划查询 1840
const WORD tdxTSHGZZJHCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 特色回购流水查询 1842
const WORD tdxTSHGLSCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 配售状态设置(查询) 2000
const WORD tdxPSZTSZFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_CZZT,				// 操作标志
	TDX_ID_WTSL,				// 委托数量
	TDX_ID_WTJG,				// 委托价格
	TDX_ID_WTJE,				// 委托金额
	TDX_ID_WTRQ,				// 委托日期
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_XT_REMARK,			// 备注
	TDX_ID_XT_PARAM,			// 参数
};

// 合作回购 2002
const WORD tdxHZHGFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式
	
	TDX_ID_HZHGZT,				// 合作回购状态(0--申请买入,1--提前终止,2--撤单.3--续约,4--续约终止,5--提前终止预约,6--提前终止预约撤销)
	TDX_ID_CPDM,				// 产品代码
	TDX_ID_WTSL,				// 委托数量
	TDX_ID_CJRQ,				// 成交日期
	TDX_ID_CJBH,				// 成交编号
	TDX_ID_WTRQ,				// 委托日期
	TDX_ID_WTBH,				// 委托编号
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_ZDWTBJ,				// 自动委托标记(0--不自动展期,1--自动展期,默认--0)
	TDX_ID_CJJG,				// 成交价格
	TDX_ID_CJSL,				// 成交数量
	TDX_ID_XT_PARAM,			// 参数(接口查询功能给出,客户端原封返回)
	TDX_ID_XT_CHECKRISKFLAG,	// 检查风险标志(1--检查是否拥有签署报价回购权限)
	TDX_ID_CZBZ,				// 操作标志(0--上海报价回购,1--深圳报价回购,默认--0,不送等同0)
};

// 合作回购状态(查询) 2004
const WORD tdxHZHGZTFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

// 合作申购状态(查询) 2006
const WORD tdxHZSGZTFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

// 合作回购产品代码查询 2008
const WORD tdxHZHGCPDMCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_CZBZ,				// 操作标志(0--上海报价回购,1--深圳报价回购,默认--0,不送等同0)
};

// 合作回购产品信息查询 2010
const WORD tdxHZHGCPXXCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_CPDM,				// 产品代码
	TDX_ID_CZBZ,				// 操作标志(0--上海报价回购,1--深圳报价回购,默认--0,不送等同0)
};

// 合作回购提前终止查询 2012
const WORD tdxHZHGTQZZCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_CZBZ,				// 操作标志(0--上海报价回购,1--深圳报价回购,默认--0,不送等同0)
};

// 合作回购当日委托查询 2014
const WORD tdxHZHGDRWTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_CZBZ,				// 操作标志(0--上海报价回购,1--深圳报价回购,默认--0,不送等同0)
	TDX_ID_XT_FUNCTIONVERSION,	// 功能版本
};

// 合作回购当日成交查询 2016
const WORD tdxHZHGDRCJCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 合作回购历史委托查询 2018
const WORD tdxHZHGLSWTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_CZBZ,				// 操作标志(0--上海报价回购,1--深圳报价回购,默认--0,不送等同0)
};

// 合作回购历史成交查询 2020
const WORD tdxHZHGLSCJCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

// 合作回购期内合约查询 2022
const WORD tdxHZHGQNHYCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_CZBZ,				// 操作标志(0--上海报价回购,1--深圳报价回购,默认--0,不送等同0)
	TDX_ID_XT_FUNCTIONVERSION,	// 功能版本
};

// 合作回购撤单查询 2024
const WORD tdxHZHGCDCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_CZBZ,				// 操作标志(0--上海报价回购,1--深圳报价回购,默认--0,不送等同0)
};

// 合作回购续约查询 2026
const WORD tdxHZHGXYCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_CZBZ,				// 操作标志(0--上海报价回购,1--深圳报价回购,默认--0,不送等同0)
};

// 合作回购续约终止查询 2028
const WORD tdxHZHGXYZZCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_CZBZ,				// 操作标志(0--上海报价回购,1--深圳报价回购,默认--0,不送等同0)
};

// 合作回购提前终止预约查询 2030
const WORD tdxHZHGTQZZYYCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_CZBZ,				// 操作标志(0--上海报价回购,1--深圳报价回购,默认--0,不送等同0)
};

// 合作回购提前终止预约撤销查询 2032
const WORD tdxHZHGTQZZYYCXCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_CZBZ,				// 操作标志(0--作为配套查询,1--作为独立查询,默认--0)
	TDX_ID_LX,					// 类型(0--提前购回 1-自动续作)
	TDX_ID_CZBZ,				// 操作标志(0--上海报价回购,1--深圳报价回购,默认--0,不送等同0)
};

// 合作回购对应质押物查询 2034
const WORD tdxHZHGDYZYWCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_CJRQ,				// 成交日期
	TDX_ID_CJBH,				// 成交编号
};

// 合作回购续约撤单查询 2036
const WORD tdxHZHGXYCDCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_CZBZ,				// 操作标志(0--上海报价回购,1--深圳报价回购,默认--0,不送等同0)
};

// 合作回购当日到期查询 2038
const WORD tdxHZHGDRDQCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 合作回购历史到期查询 2040
const WORD tdxHZHGLSDQCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

// 合作回购续作终止预约查询 2042
const WORD tdxHZHGXZZZYYCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 合作回购续作终止预约撤销查询 2044
const WORD tdxHZHGXZZZYYCXCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 合作回购续约变更查询 2046
const WORD tdxHZHGXYBGCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 合作回购合约收益查询 2048
const WORD tdxHZHGHYSYCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

// 深圳报价回购产品代码查询 2050
const WORD tdxSZBJHGCPDMCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_CZBZ,				// 操作标志(0--现有,1--历史,默认--0,不送等同0)

	TDX_ID_XT_STARTPOS,			// 起始序号
};

//  深圳报价回购期内合约查询 2052
const WORD tdxSZBJHGQNHYCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_CZBZ,				// 操作标志
	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 合作回购协议设置配套查询 2054
const WORD tdxHZHGXYSZPTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_CZBZ,				// 操作标志(0--报价回购协议设置,1--自动扫单协议设置 默认--0 不送等同0)
	TDX_ID_XT_STARTPOS,			// 起始序号
};


//////////////////////////////////////////////////////////////////////////

// 约定回购初始交易配套查询 2070
const WORD tdxYDHGCSJYPTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 约定回购履约保障配套查询 2072
const WORD tdxYDHGLYBZPTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 约定回购提前购回配套查询 2074
const WORD tdxYDHGTQGHPTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 约定回购延期申请配套查询 2076
const WORD tdxYDHGYQSQPTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 约定回购交易撤单配套查询 2078
const WORD tdxYDHGJYCDPTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 约定回购当前合约查询 2080
const WORD tdxYDHGDQHYCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_TSXX1,				// 提示信息1(合约状态,柜台原封字段)
};

// 约定回购历史合约查询 2082
const WORD tdxYDHGLSHYCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

// 约定回购进行合约查询 2084
const WORD tdxYDHGJXHYCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

// 约定回购终止合约查询 2086
const WORD tdxYDHGZZHYCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

// 约定回购标的证券查询 2088
const WORD tdxYDHGBDZQCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_ZQDM,				// 证券代码
	TDX_ID_TSXX1,				// 提示信息1(证券类别,柜台原封字段)
	TDX_ID_SCFLAG,				// 市场代码
};

// 约定回购产品信息查询 2090
const WORD tdxYDHGCPXXCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_HYQX,				// 合约期限
};

// 约定回购综合信息查询 2092
const WORD tdxYDHGZHXXCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_CZBZ,				// 操作标志
};

// 约定回购业务操作(信息查询) 2098
const WORD tdxYDHGYWCZFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别(股东类别)
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_CZBZ,				// 操作标志
	TDX_ID_XT_PARAM,			// 参数
	TDX_ID_ZQDM,				// 证券代码
	TDX_ID_WTSL,				// 委托数量
	TDX_ID_WTJE,				// 委托金额
	TDX_ID_WTRQ,				// 委托日期
	TDX_ID_WTBH,				// 委托编号
	TDX_ID_DQR,					// 到期日
	TDX_ID_YDXH,				// 约定序号
	TDX_ID_XT_REMARK,			// 备注
};

//////////////////////////////////////////////////////////////////////////
//	开放式基金类
//////////////////////////////////////////////////////////////////////////

// 开放式基金委托 2100
const WORD tdxKFSJJWTFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// 基金公司代码
	TDX_ID_KFSJJ_JJZH,			// 基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// 基金代码
	
	TDX_ID_KFSJJ_MMBZ,			// 开放式基金买卖标志(0,认购 1,申购 2,赎回 3,预约申购 4,预约赎回 5,定期申购 6 预约认购)
	TDX_ID_KFSJJ_JYJE,			// 认购/申购金额
	TDX_ID_KFSJJ_JJFE,			// 赎回份额
	TDX_ID_KFSJJ_FSRQ,			// (预申购赎回/预约认购)发生日期

	TDX_ID_SHFS,				// (赎回/预约赎回)巨额赎回方式
	TDX_ID_TJRDM,				// (可选)(申购/认购)推荐人代码
	TDX_ID_IDENTITYCARD,		// 身份证
	TDX_ID_SFFS,				// 收费方式
	TDX_ID_XT_CHECKRISKFLAG,	// 检查风险标志
	TDX_ID_CPBZ,				// 产品标志

	TDX_ID_WTSL,				// 委托数量
	TDX_ID_WTJG,				// 委托价格
	TDX_ID_LXFS,				// 联系方式
	TDX_ID_LXRXM,				// 联系人姓名
	TDX_ID_DFXWDM,				// 对方席位代码
	TDX_ID_YDXH,				// 约定序号
	TDX_ID_CZBZ,				// 操作标志
};

// 开放式基金委托撤单 2102
const WORD tdxKFSJJWTCDFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// 基金公司代码
	TDX_ID_KFSJJ_JJZH,			// 基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// 基金代码
	
	TDX_ID_WTRQ,				// 委托提交日期
	TDX_ID_KFSJJ_JJFE,			// 委托提交份额
	TDX_ID_KFSJJ_JYJE,			// 委托提交金额
	TDX_ID_WTBH,				// 委托编号
	TDX_ID_SFFS,				// 收费方式
	TDX_ID_KFSJJ_MMBZ,			// 开放式基金买卖标志
	TDX_ID_CZBZ,				// 操作标志
	TDX_ID_CPBZ,				// 产品标志
};

// 开放式基金转换 2104
const WORD tdxKFSJJZHFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// 基金公司代码
	TDX_ID_KFSJJ_JJZH,			// 基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// 基金代码(转出代码)

	TDX_ID_KFSJJ_ZHDM,			// 转换代码(转入代码)
	TDX_ID_KFSJJ_JYJE,			// 交易金额(转换份额)

	TDX_ID_SHFS,				// 巨额赎回方式: 0,赎回取消 1,赎回顺延
	TDX_ID_SFFS,				// 收费方式(转出代码)
	TDX_ID_XT_CHECKRISKFLAG,	// 检查风险标志
	TDX_ID_CPBZ,				// 产品标志
};

// 开放式基金份额查询 2106
const WORD tdxKFSJJFECXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_XT_STARTPOS,			// 查询起始序号
	TDX_ID_CPBZ,				// 产品标志
};

// 开放式基金委托查询 2108
const WORD tdxKFSJJWTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_KSRQ,				// 查询开始日期
	TDX_ID_ZZRQ,				// 查询结束日期
	TDX_ID_XT_STARTPOS,			// 查询起始序号
	TDX_ID_CPBZ,				// 产品标志
};

// 开放式基金信息查询 2110
const WORD tdxKFSJJXXCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// 基金公司代码
	TDX_ID_KFSJJ_JJZH,			// 基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// 基金代码

	TDX_ID_KFSJJ_MMBZ,			// 0,认购 1,申购 2,赎回 3,预约申购 4,预约赎回 5,定期申购 6,预约认购
	TDX_ID_XT_CHECKRISKFLAG,	// 检查风险标志
	TDX_ID_CPBZ,				// 产品标志
	TDX_ID_WTJG,				// 委托价格
	TDX_ID_XT_PARAM,			// 参数
};

// 开放式基金成交查询 2112
const WORD tdxKFSJJCJCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_KSRQ,				// 查询开始日期
	TDX_ID_ZZRQ,				// 查询结束日期
	TDX_ID_XT_STARTPOS,			// 查询起始序号
	TDX_ID_CPBZ,				// 产品标志
};

// 开放式基金分红设定 2114
const WORD tdxKFSJJFHFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// 基金公司代码
	TDX_ID_KFSJJ_JJZH,			// 基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// 基金代码
	
	TDX_ID_KFSJJ_DIVIDENMETHOD,	// 新分红方式 0,红利转股 1,现金分红 2,-利得现金增值再投资 3,增值现金利得再
	TDX_ID_SFFS,				// 收费方式
	TDX_ID_CPBZ,				// 产品标志
};

// 开放式基金代码查询 2116
const WORD tdxKFSJJDMCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_XT_STARTPOS,			// 查询起始序号
	TDX_ID_CPBZ,				// 产品标志
};

// 开放式基金资金帐户开户 2118
const WORD tdxKFSJJZJZHKHFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// 帐号类别(股东代码类别,绑定的股东代码类别)
	TDX_ID_GDDM,				// 股东代码(绑定的股东代码,为空不绑定)
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// 基金公司代码
	TDX_ID_KFSJJ_JJZH,			// 基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码
	
	TDX_ID_CZBZ,				// 开户标志 0,首开 1,已通过其他渠道开通
	TDX_ID_KHMC,				// 客户名称
	TDX_ID_USERADDRESS,			// 客户地址
	TDX_ID_USERPHONE,			// 联系电话
	TDX_ID_USEREMAIL,			// 客户邮件
	TDX_ID_KHTYPE,				// 开户类别 0,个人 1,机构
	TDX_ID_ZJHM,				// 证件号码
	TDX_ID_MOBILEPHONE,			// 移动电话
	TDX_ID_HOMEPHONE,			// 住宅电话
	TDX_ID_WORKPHONE,			// 工作电话
	TDX_ID_FAX,					// 传真号码
	TDX_ID_EDU,					// 教育程度
	TDX_ID_SALARY,				// 年收入
	TDX_ID_VOCATION,			// 职业
	TDX_ID_DZDBZ,				// 对帐单寄送方式 0,不寄送 1,按月 2,按季 3,半年 4,一年
	TDX_ID_SEX,					// 性别
	TDX_ID_POSTALCODE,			// 邮政编码

	TDX_ID_ZJLB,				// 证件类别
	TDX_ID_FHBZ,				// 分红标志
	TDX_ID_NAME,				// 用户名
	TDX_ID_SHFS,				// 收费方式
	TDX_ID_FHBL,				// 分红比例

	TDX_ID_FRDBXM,				// 法人代表姓名
	TDX_ID_FRDBZJLX,			// 法人代表证件类型
	TDX_ID_FRDBZJHM,			// 法人代表证件号码
	TDX_ID_LXRXM,				// 联系人姓名
	TDX_ID_LXRZJLX,				// 联系人证件类型
	TDX_ID_LXRZJHM,				// 联系人证件号码
	TDX_ID_LXRDH,				// 联系人电话
	TDX_ID_CPBZ,				// 产品标志
};

// 开放式基金资金帐户注册 2120 (保留)
const WORD tdxKFSJJZJZHZCFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// 基金公司代码
	TDX_ID_KFSJJ_JJZH,			// 基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码
	
	TDX_ID_KHMC,				// 客户名称
	TDX_ID_ZJMM,				// 资金密码
	TDX_ID_USERADDRESS,			// 用户通讯地址
	TDX_ID_ZJHM,				// 身份证
	TDX_ID_SEX,					// 性别
	TDX_ID_POSTALCODE,			// 邮政编码
};

// 开放式基金客户资料修改 2122
const WORD tdxKFSJJKHZLXGFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// 基金公司代码
	TDX_ID_KFSJJ_JJZH,			// 基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码
	
	TDX_ID_CZBZ,				// 操作标志(0-查询,1-修改)
	TDX_ID_USERADDRESS,			// 联系地址
	TDX_ID_USERPHONE,			// 电话号码
	TDX_ID_USEREMAIL,			// 电子邮件
	TDX_ID_MOBILEPHONE,			// 手机号码
	TDX_ID_POSTALCODE,			// 邮政编码
	TDX_ID_HOMEPHONE,			// 住宅电话
	TDX_ID_WORKPHONE,			// 单位电话号码
	TDX_ID_FAX,					// 传真

	TDX_ID_KHMC,				// 客户名称
	TDX_ID_ZJHM,				// 证件号码
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_XT_PARAM,			// 参数
};

// 开放式基金查询公司代码 2124
const WORD tdxKFSJJCXGSDMFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_CZZT,				// 0,查所有 1,查已经登记的基金公司  2、查询银行理财的银行
	TDX_ID_XT_STARTPOS,			// 查询起始序号
	TDX_ID_CPBZ,				// 产品标志
};

// 开放式基金帐号查询 2126
const WORD tdxKFSJJZHCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_XT_STARTPOS,			// 查询起始序号
	TDX_ID_CPBZ,				// 产品标志
};

// 开放式基金历史委托查询 2128
const WORD tdxKFSJJLSWTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码
	
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_XT_STARTPOS,			// 查询起始序号
	TDX_ID_CPBZ,				// 产品标志
};

// 开放式基金定时定额申购设置 2130
const WORD tdxKFSJJDSDESGSZFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// 基金公司代码
	TDX_ID_KFSJJ_JJZH,			// 基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// 基金代码

	TDX_ID_KFSJJ_JYJE,			// 交易金额(委托金额)
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_KFSJJ_MYKKRQ,		// 每月扣款日期
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_CZBZ,				// 操作标志(0--添加,1--修改)
	TDX_ID_SFFS,				// 收费方式
	TDX_ID_LX,					// 类型(期满种类:0--日期区间,1--成功次数,2--成功金额)
	TDX_ID_XT_PARAM,			// 参数(期满参数:TDX_ID_LX=1--表示成功次数最大限值,TDX_ID_LX=2--表示成功金额最大限值)
	TDX_ID_XT_MODE,				// 模式(扣款周期:0--每月,1--每季,2--每天,3--每周)
	TDX_ID_XT_DESCRIPTION,		// 描述
	TDX_ID_WTRQ,				// 委托日期(修改时有效)
	TDX_ID_WTBH,				// 委托编号(修改时有效)
	TDX_ID_LSH,					// 流水号(修改时有效)
	TDX_ID_XT_REMARK,			// 备注
	TDX_ID_XT_CHECKRISKFLAG,	// 检查风险标志
	TDX_ID_TJRDM,				// 推荐人代码
	TDX_ID_KFSJJ_PZDM,			// 品种代码
	TDX_ID_YXSBCS,				// 有效失败次数
};

// 开放式基金定时定额申购取消 2132
const WORD tdxKFSJJDSDESGQXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// 基金公司代码
	TDX_ID_KFSJJ_JJZH,			// 基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// 基金代码

	TDX_ID_WTBH,				// 委托编号
	TDX_ID_WTRQ,				// 委托日期
	TDX_ID_LSH,					// 流水号
	TDX_ID_KFSJJ_JYJE,			// 交易金额(委托金额)
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_KFSJJ_MYKKRQ,		// 每月扣款日期
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_SFFS,				// 收费方式
	TDX_ID_LX,					// 类型(期满种类:0--日期区间,1--成功次数,2--成功金额)
	TDX_ID_XT_PARAM,			// 参数(期满参数:TDX_ID_LX=1--表示成功次数最大限值,TDX_ID_LX=2--表示成功金额最大限值)
	TDX_ID_XT_MODE,				// 模式(扣款周期:0--每月,1--每季,2--每天,3--每周)
	TDX_ID_XT_DESCRIPTION,		// 描述
	TDX_ID_XT_REMARK,			// 备注
};

// 开放式基金查询定期定额申购品种 2134
const WORD tdxKFSJJCXDQDESGPZFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式
	
	TDX_ID_KFSJJ_JJGSDM,		// 基金公司代码
	TDX_ID_KFSJJ_JJZH,			// 基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// 基金代码

	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

// 开放式基金查询定期定额申购设置查询 2160
const WORD tdxKFSJJDSDESZCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式
	
	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_XT_STARTPOS,			// 查询起始序号
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_CPBZ,				// 产品标志
};

// 开放式基金当日委托查询 2136
const WORD tdxKFSJJDRWTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式
	
	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码
		
	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

// 开放式基金分红查询 2138
const WORD tdxKFSJJFHCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式
	
	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// 基金代码
};

// LOF基金分红查询 2140 
const WORD tdxLOFJJFHCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式
};

// LOF基金分红 2142 
const WORD tdxLOFJJFHFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式
	TDX_ID_KFSJJ_JJDM,			// 基金代码 
	TDX_ID_KFSJJ_DIVIDENMETHOD,	// 新分红方式 0,红利转股 1,现金分红 2,-利得现金增值再投资 3,增值现金利得再
	TDX_ID_XWDM,				// 席位代码
};

// 开放式基金风险信息查询 2144
const WORD tdxKFSJJFXXXCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式
	
	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_LX,					// 类型(0--基金风险信息,4--创业板风险信息,其它--默认返回基金风险信息)
};

// 开放式基金转帐开户 2146 (废弃)
const WORD tdxKFSJJZZKHFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式
	
	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码
};

// 开放式基金交易开户 2148 (废弃)
const WORD tdxKFSJJJYKHFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式
	
	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码
};

// 开放式基金当日成交查询 2150
const WORD tdxKFSJJDRCJCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式
	
	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

// 开放式基金历史成交查询 2152
const WORD tdxKFSJJLSCJCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式
	
	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

// 开放式基金净值查询 2154
const WORD tdxKFSJJJZCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式
	
	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期

	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

// 基金协议查询开通 2156
const WORD tdxKFSJJXYCXKTFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式
	
	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_CZBZ,				// 操作标志(0:查询,1:开通)
	TDX_ID_KHMC,				// 客户名称
	TDX_ID_USERPHONE,			// 用户联系方式
	TDX_ID_MOBILEPHONE,			// 移动电话
	TDX_ID_USEREMAIL,			// 用户EMAIL
	TDX_ID_USERADDRESS,			// 用户通讯地址
};

// 基金分红明细查询 2158
const WORD tdxKFSJJFHMXCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式
	
	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

// 开放式基金非交易委托查询 2162
const WORD tdxKFSJJFJYWTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_KSRQ,				// 查询开始日期
	TDX_ID_ZZRQ,				// 查询结束日期
	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

// 开放式基金非交易当日委托查询 2164
const WORD tdxKFSJJFJYDRWTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

// 开放式基金风险可承受代码查询 2166
const WORD tdxKFSJJFXKCSDMCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_FXBZ,				// 风险标志(客户风险等级,非空查询指定客户风险等级对应的基金代码)
	TDX_ID_XT_STARTPOS,			// 查询起始序号
	TDX_ID_CPBZ,				// 产品标志
};

// 开放式基金费率查询 2168
const WORD tdxKFSJJFLCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

// 开放式基金定期定额赎回设置 2170
const WORD tdxKFSJJDQDESHSZFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// 基金公司代码
	TDX_ID_KFSJJ_JJZH,			// 基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// 基金代码

	TDX_ID_KFSJJ_JJFE,			// 基金份额(赎回份额)
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_KFSJJ_MYKKRQ,		// 每月扣款日期
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_CZBZ,				// 操作标志(0--添加,1--修改)
	TDX_ID_SFFS,				// 收费方式
	TDX_ID_XT_MODE,				// 模式(扣款周期:0--每月,1--每周)
	TDX_ID_WTRQ,				// 委托日期(修改时有效)
	TDX_ID_WTBH,				// 委托编号(修改时有效)
	TDX_ID_LSH,					// 流水号(修改时有效)
	TDX_ID_XT_REMARK,			// 备注
	TDX_ID_XT_CHECKRISKFLAG,	// 检查风险标志
	TDX_ID_SHFS,				// 赎回方式
};

// 开放式基金定期定额赎回取消 2172
const WORD tdxKFSJJDQDESHQXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// 基金公司代码
	TDX_ID_KFSJJ_JJZH,			// 基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// 基金代码

	TDX_ID_WTBH,				// 委托编号
	TDX_ID_WTRQ,				// 委托日期
	TDX_ID_LSH,					// 流水号
	TDX_ID_KFSJJ_JJFE,			// 基金份额(赎回份额)
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_KFSJJ_MYKKRQ,		// 每月扣款日期
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_SFFS,				// 收费方式
	TDX_ID_XT_MODE,				// 模式(扣款周期:0--每月,1--每周)
	TDX_ID_XT_REMARK,			// 备注
	TDX_ID_SHFS,				// 赎回方式
};

// 开放式基金定期定额赎回查询 2174
const WORD tdxKFSJJDQDESHCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// 基金公司代码
	TDX_ID_KFSJJ_JJZH,			// 基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// 基金代码

	TDX_ID_XT_STARTPOS,			// 查询起始序号
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

// 开放式基金定期定额赎回品种 2176
const WORD tdxKFSJJDQDESHPZFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// 基金公司代码
	TDX_ID_KFSJJ_JJZH,			// 基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// 基金代码

	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

// 开放式基金代码相关信息查询 2178
const WORD tdxKFSJJDMXGXXCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// 基金公司代码
	TDX_ID_KFSJJ_JJZH,			// 基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// 基金代码

	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

// 开放式基金公司相关信息查询 2180
const WORD tdxKFSJJGSXGXXCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// 基金公司代码
	TDX_ID_KFSJJ_JJZH,			// 基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// 基金代码

	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

// 开放式基金对账单查询 2182
const WORD tdxKFSJJDZDCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// 基金公司代码
	TDX_ID_KFSJJ_JJZH,			// 基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// 基金代码

	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

// 开放式基金交割单查询 2184
const WORD tdxKFSJJJGDCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// 基金公司代码
	TDX_ID_KFSJJ_JJZH,			// 基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// 基金代码

	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

//////////////////////////////////////////////////////////////////////////
//	理财产品类
//////////////////////////////////////////////////////////////////////////

// 理财产品份额查询 2200
const WORD tdxLCCPFECXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式
	
	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码
		
	TDX_ID_XT_STARTPOS,			// 查询起始序号
	TDX_ID_CZBZ,				// 操作标志
	TDX_ID_CPBZ,				// 产品标志
};

// 理财产品委托查询 2202
const WORD tdxLCCPWTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式
	
	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期

	TDX_ID_XT_STARTPOS,			// 查询起始序号
	TDX_ID_CZBZ,				// 操作标志
};

// 理财产品成交查询 2204
const WORD tdxLCCPCJCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式
	
	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期

	TDX_ID_XT_STARTPOS,			// 查询起始序号
	TDX_ID_CZBZ,				// 操作标志

};

// 理财产品当日委托查询 2206
const WORD tdxLCCPDRWTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式
	
	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_XT_STARTPOS,			// 查询起始序号
	TDX_ID_CZBZ,				// 操作标志
	TDX_ID_LX,					// (0、查全部 1、查可撤单)
};

// 理财产品代码查询 2208
const WORD tdxLCCPDMCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式
	
	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_XT_STARTPOS,			// 查询起始序号
	TDX_ID_CZBZ,				// 操作标志
};

// 理财产品帐号查询 2210
const WORD tdxLCCPZHCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式
	
	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_XT_STARTPOS,			// 查询起始序号
	TDX_ID_CZBZ,				// 操作标志
};

// 理财产品定期定额申购查询 2212
const WORD tdxLCCPDQDESGCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式
	
	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

// 理财产品定期定额申购品种 2214
const WORD tdxLCCPDQDESGPZFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式
	
	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_XT_STARTPOS,			// 查询起始序号
	TDX_ID_CZBZ,				// 操作标志
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

// 理财产品增值计划列表查询 2216
const WORD tdxLCCPZZJHLBCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式
	
	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_XT_STARTPOS,			// 查询起始序号
	TDX_ID_CZZT,				// 操作状态(用于过滤,空--全部)
};

// 理财产品增值计划信息查询 2218
const WORD tdxLCCPZZJHXXCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_XT_STARTPOS,			// 查询起始序号
	TDX_ID_XT_CHECKRISKFLAG,	// 检查风险标志(1--检查是否签署电子合同)
	TDX_ID_XT_PARAM,			// 参数
};

// 理财产品增值计划金额设置 2220
const WORD tdxLCCPZZJHJESZFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式
	
	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// 基金代码

	TDX_ID_KFSJJ_JYJE,			// 交易金额
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_XT_PARAM,			// 参数
	TDX_ID_XT_REMARK,			// 备注
	TDX_ID_CZBZ,				// 操作标志 0:正常 1:暂停
};

// 理财产品增值计划状态设置 2222
const WORD tdxLCCPZZJHZTSZFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式
	
	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_CZBZ,				// 操作标志(0--正常,1--暂停)
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_XT_PARAM,			// 参数
	TDX_ID_XT_REMARK,			// 备注
};

// 理财产品增值计划解除协议 2224
const WORD tdxLCCPZZJHJCXYFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式
	
	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_XT_PARAM,			// 参数
	TDX_ID_XT_REMARK,			// 备注
};

// 理财产品增值计划份额查询 2226
const WORD tdxLCCPZZJHFECXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式
	
	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

// 理财产品增值计划撤单查询 2228
const WORD tdxLCCPZZJHCDCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式
	
	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

// 理财产品增值计划信息修改 2230
const WORD tdxLCCPZZJHXXXGFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式
	
	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_CZBZ,				// 操作标志(0--登记产品;其余为按位标识[修改对应字段]:0x1--协议状态,0x2--资金保留额度,0x4--暂停有效期截止日,0x8--额度有效期截止日;0xffffffff[-1]--全部修改[接口自行选择处理])
	TDX_ID_CZZT,				// 操作状态(协议状态,0--正常,1--暂停)
	TDX_ID_KFSJJ_JYJE,			// 交易金额(资金保留额度)
	TDX_ID_ZZRQ,				// 终止日期(暂停有效期截止日)
	TDX_ID_PCRQ,				// 平仓日期(额度有效期截止日)
	TDX_ID_XT_PARAM,			// 参数
	TDX_ID_XT_REMARK,			// 备注
	TDX_ID_TJRDM,				// 推荐人代码
	TDX_ID_XT_CHECKRISKFLAG,	// 检查风险标志
};

// 理财产品增值计划份额赎回 2232
const WORD tdxLCCPZZJHFESHFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式
	
	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_KFSJJ_JJFE,			// 赎回份额
	TDX_ID_SHFS,				// 赎回方式
};

// 理财产品增值计划委托撤单 2234
const WORD tdxLCCPZZJHWTCDFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式
	
	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_WTRQ,				// 委托日期
	TDX_ID_WTBH,				// 委托编号
	TDX_ID_XT_PARAM,			// 参数
};

// 理财产品增值计划预约取款操作 2236
const WORD tdxLCCPZZJHYYQKCZFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式
	
	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_CZBZ,				// 操作标志(0--查询新增信息,1--新增记录,2--查询修改信息,3--修改记录,4--查询删除信息,5--删除记录)
	TDX_ID_XT_PARAM,			// 参数(和"理财产品增值计划预约取款查询 2238"的同名应答字段相对应)
	TDX_ID_WTRQ,				// 委托日期
	TDX_ID_WTJE,				// 委托金额
};

// 理财产品增值计划预约取款查询 2238
const WORD tdxLCCPZZJHYYQKCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式
	
	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

// 理财产品增值计划历史收益查询 2240
const WORD tdxLCCPZZJHLSSYCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式
	
	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_XT_STARTPOS,			// 查询起始序号
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

// 短期理财产品赎回信息查询 2242
const WORD tdxDQLCCPSHXXCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_XT_STARTPOS,			// 查询起始序号
	TDX_ID_KFSJJ_FSRQ,			// 发生日期
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_CZBZ,				// 操作标志
};

// 理财产品转让代码查询 2244
const WORD tdxLCCPZRDMCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_XT_STARTPOS,			// 查询起始序号
	TDX_ID_CZBZ,				// 操作标志
};

// 理财产品转让行情查询 2246
const WORD tdxLCCPZRHQCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_XT_STARTPOS,			// 查询起始序号
	TDX_ID_CZBZ,				// 操作标志
};

// 理财产品转让撤单查询 2248
const WORD tdxLCCPZRCDCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_XT_STARTPOS,			// 查询起始序号
	TDX_ID_CZBZ,				// 操作标志
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

// 理财产品转让委托查询 2250
const WORD tdxLCCPZRWTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_XT_STARTPOS,			// 查询起始序号
	TDX_ID_CZBZ,				// 操作标志
};

// 理财产品转让成交查询 2252
const WORD tdxLCCPZRCJCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_XT_STARTPOS,			// 查询起始序号
	TDX_ID_CZBZ,				// 操作标志
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

// 理财产品签约解约查询 2254
const WORD tdxLCCPQYJYCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_XT_STARTPOS,			// 查询起始序号
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_CZBZ,				// 操作标志
};

// 银行理财产品代码查询 2256
const WORD tdxYHLCCPDMCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_XT_STARTPOS,			// 查询起始序号
	TDX_ID_CZBZ,				// 操作标志
};

// 银行理财产品份额查询 2258
const WORD tdxYHLCCPFECXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_XT_STARTPOS,			// 查询起始序号
	TDX_ID_CZBZ,				// 操作标志
};

// 银行理财产品委托查询 2260
const WORD tdxYHLCCPWTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期

	TDX_ID_XT_STARTPOS,			// 查询起始序号
	TDX_ID_CZBZ,				// 操作标志
};

// 银行理财产品帐号查询 2262
const WORD tdxYHLCCPZHCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_XT_STARTPOS,			// 查询起始序号
	TDX_ID_CZBZ,				// 操作标志
};

// 银行理财产品成交查询 2264
const WORD tdxYHLCCPCJCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期

	TDX_ID_XT_STARTPOS,			// 查询起始序号
	TDX_ID_CZBZ,				// 操作标志
};

// OTC份额查询 2266
const WORD tdxOTCFECXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

// OTC认申赎查询 2268
const WORD tdxOTCRSSCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期

	TDX_ID_CZBZ,				// 操作标记
	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

// OTC意向申报查询 2270
const WORD tdxOTCYXSBCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期

	TDX_ID_CZBZ,				// 操作标记
	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

// OTC成交申报查询 2272
const WORD tdxOTCCJSBCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式
	
	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
	
	TDX_ID_CZBZ,				// 操作标记
	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

// OTC产品合约查询 2274
const WORD tdxOTCCPHYCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

// OTC报价信息查询 2276
const WORD tdxOTCBJXXCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

// OTC行情信息查询 2278
const WORD tdxOTCHQXXCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期	
	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

// OTC电子合同列表查询 2280
const WORD tdxOTCDZHTLBCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

// OTC电子合同查询 2282
const WORD tdxOTCDZHTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// (保留)基金代码

	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

// 信托产品代码查询 2300
const WORD tdxXTCPDMCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_XTCPDM,				// (保留)信托产品代码

	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

// 信托产品份额查询 2302
const WORD tdxXTCPFECXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_XTCPDM,				// (保留)信托产品代码

	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

// 信托产品帐号查询 2304
const WORD tdxXTCPZHCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_XTCPDM,				// (保留)信托产品代码

	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

// 信托产品委托查询 2306
const WORD tdxXTCPWTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_XTCPDM,				// (保留)信托产品代码

	TDX_ID_KSRQ,				// 查询开始日期
	TDX_ID_ZZRQ,				// 查询结束日期
	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

// 信托产品成交查询 2308
const WORD tdxXTCPCJCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_XTCPDM,				// (保留)信托产品代码

	TDX_ID_KSRQ,				// 查询开始日期
	TDX_ID_ZZRQ,				// 查询结束日期
	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

// 信托产品历史委托查询 2310
const WORD tdxXTCPLSWTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// (保留)基金公司代码
	TDX_ID_KFSJJ_JJZH,			// (保留)基金帐号代码
	TDX_ID_XTCPDM,				// (保留)信托产品代码
	
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

//////////////////////////////////////////////////////////////////////////
//	基金直销
//////////////////////////////////////////////////////////////////////////

// 基金直销认购	2500
const WORD tdxJJZXRGFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// 基金公司代码
	TDX_ID_KFSJJ_JJZH,			// 基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// 基金代码

	TDX_ID_KFSJJ_JYJE,			// 认购/申购金额
	TDX_ID_KFSJJ_JJFE,			// 赎回份额
	TDX_ID_KFSJJ_FSRQ,			// (预申购赎回/预约认购)发生日期

	TDX_ID_SHFS,				// (赎回/预约赎回)巨额赎回方式
	TDX_ID_TJRDM,				// (可选)(申购/认购)推荐人代码
	TDX_ID_BANKCODE,			// 银行代码	
	TDX_ID_IDENTITYCARD,		// 身份证
	TDX_ID_SFFS,				// 收费方式
	TDX_ID_XT_CHECKRISKFLAG,	// 检查风险标志
};

// 基金直销申购	2502
const WORD tdxJJZXSGFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// 基金公司代码
	TDX_ID_KFSJJ_JJZH,			// 基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// 基金代码

	TDX_ID_KFSJJ_JYJE,			// 认购/申购金额
	TDX_ID_KFSJJ_JJFE,			// 赎回份额
	TDX_ID_KFSJJ_FSRQ,			// (预申购赎回/预约认购)发生日期

	TDX_ID_SHFS,				// (赎回/预约赎回)巨额赎回方式
	TDX_ID_TJRDM,				// (可选)(申购/认购)推荐人代码
	TDX_ID_IDENTITYCARD,		// 身份证
	TDX_ID_SFFS,				// 收费方式
	TDX_ID_XT_CHECKRISKFLAG,	// 检查风险标志
};

// 基金直销赎回	2504
const WORD tdxJJZXSHFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// 基金公司代码
	TDX_ID_KFSJJ_JJZH,			// 基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// 基金代码

	TDX_ID_KFSJJ_JYJE,			// 认购/申购金额
	TDX_ID_KFSJJ_JJFE,			// 赎回份额
	TDX_ID_KFSJJ_FSRQ,			// (预申购赎回/预约认购)发生日期

	TDX_ID_SHFS,				// (赎回/预约赎回)巨额赎回方式
	TDX_ID_TJRDM,				// (可选)(申购/认购)推荐人代码
	TDX_ID_IDENTITYCARD,		// 身份证
	TDX_ID_SFFS,				// 收费方式
	TDX_ID_XT_CHECKRISKFLAG,	// 检查风险标志
};

// 基金直销分红	2506
const WORD tdxJJZXFHFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// 基金公司代码
	TDX_ID_KFSJJ_JJZH,			// 基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// 基金代码
	
	TDX_ID_KFSJJ_DIVIDENMETHOD,	// 新分红方式 0,红利转股 1,现金分红
	TDX_ID_SFFS,				// 收费方式
};

// 基金直销转换	2508
const WORD tdxJJZXZHFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// 基金公司代码
	TDX_ID_KFSJJ_JJZH,			// 基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// 基金代码(转出代码)

	TDX_ID_KFSJJ_ZHDM,			// 转换代码(转入代码)
	TDX_ID_KFSJJ_JYJE,			// 交易金额(转换份额)

	TDX_ID_SHFS,				// 巨额赎回方式: 0,赎回取消 1,赎回顺延
	TDX_ID_SFFS,				// 收费方式(转出代码)
	TDX_ID_XT_CHECKRISKFLAG,	// 检查风险标志
};

// 基金直销转托管 2510
const WORD tdxJJZXZTGFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// 基金公司代码
	TDX_ID_KFSJJ_JJZH,			// 基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// 基金代码(转出代码)

	TDX_ID_KFSJJ_ZHDM,			// 转换代码(转入代码)
	TDX_ID_KFSJJ_JYJE,			// 交易金额(转换份额)

	TDX_ID_SHFS,				// 巨额赎回方式: 0,赎回取消 1,赎回顺延
	TDX_ID_SFFS,				// 收费方式(转出代码)
	TDX_ID_XT_CHECKRISKFLAG,	// 检查风险标志
};

// 基金直销撤单 2512
const WORD tdxJJZXCDFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// 基金公司代码
	TDX_ID_KFSJJ_JJZH,			// 基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// 基金代码
	
	TDX_ID_WTRQ,				// 委托提交日期
	TDX_ID_KFSJJ_JJFE,			// 委托提交份额
	TDX_ID_KFSJJ_JYJE,			// 委托提交金额
	TDX_ID_WTBH,				// 委托编号
	TDX_ID_SFFS,				// 收费方式
};

// 基金直销费率查询 2514
const WORD tdxJJZXFLCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// 基金公司代码
	TDX_ID_KFSJJ_JJZH,			// 基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// 基金代码

	TDX_ID_YZZZ_YHDM,			// 银行代码(网点代码)
	TDX_ID_JYZH,				// 交易账号
	TDX_ID_KFSJJ_ZHDM,			// 转换代码
	TDX_ID_KFSJJ_JJFE,			// 委托提交份额
	TDX_ID_KFSJJ_JYJE,			// 委托提交金额
	TDX_ID_KFSJJ_MMBZ,			// 基金买卖标志
	TDX_ID_SFFS,				// 收费方式
	TDX_ID_LX,					// 类型(费用类别,0--全部,1--手续费,2--印花税,3--过户费,5--后端折扣率,9--默认折扣率,其他--未定义)
};

// 基金直销银行支付 2516
const WORD tdxJJZXYHZFFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// 基金公司代码
	TDX_ID_KFSJJ_JJZH,			// 基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// 基金代码

	TDX_ID_YZZZ_YHDM,			// 银行代码(网点代码)
	TDX_ID_JYZH,				// 交易账号
	TDX_ID_KFSJJ_JJFE,			// 委托提交份额
	TDX_ID_KFSJJ_JYJE,			// 委托提交金额
	TDX_ID_KFSJJ_MMBZ,			// 基金买卖标志
	TDX_ID_ZJLB,				// 证件类别
	TDX_ID_ZJHM,				// 证件号码
	TDX_ID_WTBH,				// 委托编号
	TDX_ID_YZZZ_YHZH,			// 银行账号(投资人账户)
	TDX_ID_KHMC,				// 客户名称(投资人名称)
	TDX_ID_KFSJJ_JJMC,			// 基金名称
	TDX_ID_XT_PARAM,			// 参数
};

// 基金直销销售人代码查询 2518
const WORD tdxJJZXXSRDMCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// 基金公司代码
	TDX_ID_KFSJJ_JJZH,			// 基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// 基金代码

	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

// 基金直销信息检查 2520
const WORD tdxJJZXXXJCFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// 基金公司代码
	TDX_ID_KFSJJ_JJZH,			// 基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// 基金代码

	TDX_ID_CZBZ,				// 操作标志(0--开户检查昵称,1--修改资料检查昵称)
	TDX_ID_XT_PARAM,			// 参数
	TDX_ID_NC,					// 昵称
};

// 交易所场内基金代码查询 2850
const WORD tdxJYSCNJJDMCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// 基金公司代码
	TDX_ID_KFSJJ_JJZH,			// 基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// 基金代码

	TDX_ID_XT_STARTPOS,			// 查询起始序号
	TDX_ID_CZBZ,				// 操作标志
	TDX_ID_XT_PARAM,			// 参数
};

// 交易所场内基金成分股查询 2852
const WORD tdxJYSCNJJCFGCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KFSJJ_JJGSDM,		// 基金公司代码
	TDX_ID_KFSJJ_JJZH,			// 基金帐号代码
	TDX_ID_KFSJJ_JJDM,			// 基金代码

	TDX_ID_XT_STARTPOS,			// 查询起始序号
	TDX_ID_CZBZ,				// 操作标志
	TDX_ID_XT_PARAM,			// 参数
};

//////////////////////////////////////////////////////////////////////////
//	ETF
//////////////////////////////////////////////////////////////////////////

// ETF上海跨境申购配套查询 2950
const WORD tdxETFSHKJSGPTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

// ETF深圳跨境申购配套查询 2952
const WORD tdxETFSZKJSGPTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

// ETF上海跨境赎回配套查询 2954
const WORD tdxETFSHKJSHPTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

// ETF深圳跨境赎回配套查询 2956
const WORD tdxETFSZKJSHPTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

// ETF上海跨境委托撤单查询 2958
const WORD tdxETFSHKJWTCDCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

// ETF深圳跨境委托撤单查询 2960
const WORD tdxETFSZKJWTCDCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

// ETF上海跨境当日委托查询 2962
const WORD tdxETFSHKJDRWTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

// ETF深圳跨境当日委托查询 2964
const WORD tdxETFSZKJDRWTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

// ETF上海跨境当日成交查询 2966
const WORD tdxETFSHKJDRCJCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

// ETF深圳跨境当日成交查询 2968
const WORD tdxETFSZKJDRCJCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

// ETF上海跨境历史委托查询 2970
const WORD tdxETFSHKJLSWTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询起始序号
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

// ETF深圳跨境历史委托查询 2972
const WORD tdxETFSZKJLSWTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询起始序号
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

// ETF上海跨境历史成交查询 2974
const WORD tdxETFSHKJLSCJCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询起始序号
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

// ETF深圳跨境历史成交查询 2976
const WORD tdxETFSZKJLSCJCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询起始序号
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

// ETF网下现金认购配套查询 2980
const WORD tdxETFWXXJRGPTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

// ETF网下股份认购配套查询 2982
const WORD tdxETFWXGFRGPTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询起始序号
	TDX_ID_ETFDM,				// ETF代码
};

// ETF网下现金认购撤单查询 2984
const WORD tdxETFWXXJRGCDCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

// ETF网下股份认购撤单查询 2986
const WORD tdxETFWXGFRGCDCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

// ETF网下现金认购信息查询 2988
const WORD tdxETFWXXJRGXXCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

// ETF网下股份认购信息查询 2990
const WORD tdxETFWXGFRGXXCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

// ETF网下现金认购流水查询 2992
const WORD tdxETFWXXJRGLSCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

// ETF网下股份认购流水查询 2994
const WORD tdxETFWXGFRGLSCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

// ETF买卖 3000
const WORD tdxETFMMFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_ETFMMBS,				// 0,申购,1,赎回,2,股票认购,3,现金认购
	TDX_ID_ETFDM,				// ETF代码(注:这里不采用证券代码)
	TDX_ID_ZQDM,				// 股票代码(股票认购时,该字段有效)
	TDX_ID_WTJG,				// (保留)委托价格
	TDX_ID_ETFRGSL,				// 数量
	TDX_ID_DFZHLB,				// 对方帐号类别
	TDX_ID_DFGDDM,				// 对方股东代码
	TDX_ID_TJRDM,				// 推荐人代码
};

// ETF信息查询 3002
const WORD tdxETFXXCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式
	
	TDX_ID_ETFMMBS,				// 0,申购,1,赎回,2,股票认购,3,现金认购
	TDX_ID_ETFDM,				// ETF代码(注:这里不采用证券代码)
	TDX_ID_ZQDM,				// 股票代码(股票认购时,该字段有效)
	TDX_ID_WTJG,				// (保留)委托价格
	TDX_ID_DFZHLB,				// 对方帐号类别
	TDX_ID_DFGDDM,				// 对方股东代码
	TDX_ID_KFSJJ_JJDM,			// 基金代码(可能同时存在"认购代码"/"基金代码"时,放置"基金代码")
};

// ETF认购查询 3004
const WORD tdxETFRGCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询起始序号
	TDX_ID_QSRQ,				// 清算日期
};

// ETF认购撤单 3006
const WORD tdxETFRGCDFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_ZSDM,				// 指数代码
	TDX_ID_PCH,					// 批次号
	TDX_ID_QSRQ,				// 清算日期
	TDX_ID_WTBH,				// 委托编号
	TDX_ID_ETFMMBS,				// ETF买卖标识
	TDX_ID_ZQDM,				// 证券代码(成分股代码)
	TDX_ID_CDSL,				// 撤单数量
};

// ETF批次号 3008
const WORD tdxETFPCHFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

// ETF股票篮买卖 3010
const WORD tdxETFGPLMMFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式
	
	TDX_ID_MMBZ,				// 0,买篮,1,卖篮
	TDX_ID_ETFDM,				// ETF代码
	TDX_ID_PCH,					// 批次号
	TDX_ID_QSRQ,				// 清算日期
	TDX_ID_CLDM,				// 策略代码
	TDX_ID_ZSDM,				// 指数代码
	TDX_ID_ZQDM,				// 证券代码
	TDX_ID_WTJG,				// 委托价格
	TDX_ID_WTSL,				// 委托数量
	TDX_ID_BLSL,				// 保留数量
	TDX_ID_CZBZ,				// (保留)操作标志
};

// ETF股票篮查询 3012
const WORD tdxETFGPLCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式
	
	TDX_ID_ETFDM,				// ETF代码
	TDX_ID_ZSDM,				// 指数代码
	TDX_ID_MMBZ,				// 买卖标志
	TDX_ID_PCH,					// 批次号
	TDX_ID_QSRQ,				// 清算日期
	TDX_ID_WTSL,				// 委托数量
	TDX_ID_WTJG,				// 委托价格
	TDX_ID_XT_STARTPOS,			// 查询起始序号
	
	TDX_ID_CZBZ,				// 操作标志(是否使用库存:1--是,2--否)
};

// ETF拥股查询 3014
const WORD tdxETFYGCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式
	
	TDX_ID_ETFDM,				// ETF代码
	TDX_ID_ZSDM,				// 指数代码(同ETF代码)
	TDX_ID_PCH,					// 批次号
	TDX_ID_QSRQ,				// 清算日期
	TDX_ID_XT_STARTPOS,			// 查询起始序号
	TDX_ID_WTSL,				// 委托数量
};

// ETF委托查询 3016
const WORD tdxETFWTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_PCH,					// 0:查所有 否则查对应
	TDX_ID_ZSDM,				// 指数代码(同ETF代码)
	TDX_ID_ETFDM,				// ETF代码
	TDX_ID_KSRQ,				// 查询开始日期
	TDX_ID_ZZRQ,				// 查询终止日期
	TDX_ID_CZBZ,				// 0,查所有 1,查可撤单委托
	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

// ETF成交查询 3018
const WORD tdxETFCJCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_WTRQ,				// 委托日期
	TDX_ID_ZSDM,				// 指数代码
	TDX_ID_PCH,					// 批次号
	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

// ETF策略查询 3020
const WORD tdxETFCLCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式
};

// ETF指数代码查询 3022
const WORD tdxETFZSDMCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_ZSDM,				// 指数代码
	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

// ETF(委托)确认 3024
const WORD tdxETFQRFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_PCH,					// 批次号
	TDX_ID_CLDM,				// 策略代码
	TDX_ID_ZSDM,				// 指数代码
	TDX_ID_CZBZ,				// 操作标志(0--按批次号处理(其他按指数代码处理),1--开仓,2--平仓,3--补仓,4--清仓,默认--0)
	TDX_ID_WTSL,				// 委托数量(篮子数量)
	TDX_ID_JGBZ,				// 价格标志
	TDX_ID_MZL,					// 命中率
};

// ETF委托查询明细 3026
const WORD tdxETFWTCXMXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_ZSDM,				// 指数代码
	TDX_ID_PCH,					// 批次号
	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

// ETF认购撤单查询 3028
const WORD tdxETFRGCDCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询起始序号
	TDX_ID_QSRQ,				// 清算日期
};

// ETF指数成分查询 3030
const WORD tdxETFZSCFCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_ZSDM,				// 指数代码
	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

// ETF股份查询 3032
const WORD tdxETFGFCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_ZQDM,				// 证券代码(非空查指定代码)
	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

// ETF可申购成分股查询 3034
const WORD tdxETFKSGCFGCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_ZSDM,				// 指数代码
	TDX_ID_WTSL,				// 委托数量(篮子数量)
	TDX_ID_XT_STARTPOS,			// 查询起始序号
};

// ETF股票篮撤单 3036
const WORD tdxETFGPLCDFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_ZSDM,				// 指数代码
	TDX_ID_PCH,					// 批次号
	TDX_ID_WTRQ,				// 委托日期
};

// ETF股票篮撤单查询 3038
const WORD tdxETFGPLCDCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询起始序号
	TDX_ID_ZSDM,				// 指数代码
};

// ETF跨市场对盘查询 3040
const WORD tdxETFKSCDPCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询起始序号
	TDX_ID_ZSDM,				// 指数代码
	TDX_ID_CJRQ,				// 成交日期
};

//////////////////////////////////////////////////////////////////////////
//	组合通
//////////////////////////////////////////////////////////////////////////

// 组合通批次号 3050
const WORD tdxZHTPCHFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式
};

// 组合通股票篮买卖 3052
const WORD tdxZHTGPLMMFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式
	
	TDX_ID_PCH,					// 批次号
	TDX_ID_QSRQ,				// 清算日期
	TDX_ID_CLDM,				// 策略代码
	TDX_ID_ZSDM,				// 指数代码
	TDX_ID_ZQDM,				// 证券代码
	TDX_ID_WTJG,				// 委托价格
	TDX_ID_WTSL,				// 委托数量
	TDX_ID_BLSL,				// 保留数量

	TDX_ID_XT_PARAM,			// 参数
};

// 组合通股票篮查询 3054
const WORD tdxZHTGPLCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_ZSDM,				// 指数代码
	TDX_ID_PCH,					// 批次号
	TDX_ID_QSRQ,				// 清算日期
	TDX_ID_MMBZ,				// 买卖标志
	TDX_ID_WTSL,				// 委托数量
	TDX_ID_WTJG,				// 委托价格
	TDX_ID_XT_STARTPOS,			// 查询开始位置

	TDX_ID_ZHDM,				// 组合代码
};

// 组合通拥股查询 3056
const WORD tdxZHTYGCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_ZSDM,				// 指数代码
	TDX_ID_PCH,					// 批次号
	TDX_ID_CZBZ,				// 操作标志(0、查询全部 1、可撤销 2、可转换)

	TDX_ID_XT_STARTPOS,			// 查询开始位置
};

// 组合通委托查询 3058
const WORD tdxZHTWTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_ZSDM,				// 指数代码
	TDX_ID_PCH,					// 批次号

	TDX_ID_XT_STARTPOS,			// 查询开始位置
};

// 组合通成交查询 3060
const WORD tdxZHTCJCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_ZQDM,				// 指数代码
	TDX_ID_PCH,					// 批次号
	TDX_ID_XT_STARTPOS,			// 查询开始位置
};

// 组合通策略查询 3062
const WORD tdxZHTCLCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询开始位置
};

// 组合通指数代码查询 3064
const WORD tdxZHTZSDMCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_ZSDM,				// 指数代码

	TDX_ID_XT_STARTPOS,			// 查询开始位置
};

// 组合通确认 3066
const WORD tdxZHTQRFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_PCH,					// 批次号
	TDX_ID_CLDM,				// 策略代码
};

// 组合通历史查询 3068
const WORD tdxZHTLSCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_KSRQ,				// 查询开始日期
	TDX_ID_ZZRQ,				// 查询终止日期
	TDX_ID_XT_STARTPOS,			// 查询开始位置
};

// 组合通历史查询明细 3070
const WORD tdxZHTLSCXMXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_ZSDM,				// 指数代码
	TDX_ID_PCH,					// 批次号
	TDX_ID_XT_STARTPOS,			// 查询开始位置
	
	TDX_ID_QSRQ,				// 清算日期
	TDX_ID_KSRQ,				// 查询开始日期
	TDX_ID_ZZRQ,				// 查询终止日期
};

// 组合通委托查询明细 3072
const WORD tdxZHTWTCXMXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_ZSDM,				// 指数代码
	TDX_ID_PCH,					// 批次号

	TDX_ID_XT_STARTPOS,			// 查询开始位置
};

// 组合通成交查询明细 3074
const WORD tdxZHTCJCXMXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_ZSDM,				// 指数代码
	TDX_ID_PCH,					// 批次号
	TDX_ID_XT_STARTPOS,			// 查询开始位置

	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

// 组合通指数成分查询 3076
const WORD tdxZHTZSCFCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_ZSDM,				// 指数代码
	TDX_ID_PCH,					// 批次号
	TDX_ID_XT_STARTPOS,			// 查询开始位置
};

// (套利)获取会话号 3100
const WORD tdxTLHQHHHFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_DFKHDM,				// 对方客户代码
	TDX_ID_DFMM,				// 对方密码
	TDX_ID_DFZJZH,				// 对方资金账号
	TDX_ID_DFZHLB,				// 对方账号类别
	TDX_ID_DFGDDM,				// 对方股东代码
	TDX_ID_XHZHLX,				// 现货账号类型
};

// (套利)组合代码查询 3102
const WORD tdxTLZHDMCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_DFKHDM,				// 对方客户代码
	TDX_ID_DFMM,				// 对方密码
	TDX_ID_DFZJZH,				// 对方资金账号
	TDX_ID_DFZHLB,				// 对方账号类别
	TDX_ID_DFGDDM,				// 对方股东代码
	TDX_ID_XHZHLX,				// 现货账号类型

	TDX_ID_XT_TOKEN,			// 令牌
	TDX_ID_XT_STARTPOS,			// 查询开始位置
	TDX_ID_ZHDM,				// 组合代码
};

// (套利)组合成分查询 3104
const WORD tdxTLZHCFCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_DFKHDM,				// 对方客户代码
	TDX_ID_DFMM,				// 对方密码
	TDX_ID_DFZJZH,				// 对方资金账号
	TDX_ID_DFZHLB,				// 对方账号类别
	TDX_ID_DFGDDM,				// 对方股东代码
	TDX_ID_XHZHLX,				// 现货账号类型

	TDX_ID_XT_TOKEN,			// 令牌
	TDX_ID_XT_STARTPOS,			// 查询开始位置
	TDX_ID_ZHDM,				// 组合代码
	TDX_ID_ZQDM,				// 证券代码
};

// (套利)组合代码操作 3106
const WORD tdxTLZHDMCZFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_DFKHDM,				// 对方客户代码
	TDX_ID_DFMM,				// 对方密码
	TDX_ID_DFZJZH,				// 对方资金账号
	TDX_ID_DFZHLB,				// 对方账号类别
	TDX_ID_DFGDDM,				// 对方股东代码
	TDX_ID_XHZHLX,				// 现货账号类型

	TDX_ID_XT_TOKEN,			// 令牌
	TDX_ID_CZBZ,				// 操作标志(0--增加,1--删除)
	TDX_ID_ZHDM,				// 组合代码
	TDX_ID_ZHMC,				// 组合名称
	TDX_ID_ZHLX,				// 组合类型
	TDX_ID_QZFS,				// 权重方式
	TDX_ID_DWSZ,				// 单位市值
	TDX_ID_XYJYBS,				// 信用交易标识
};

// (套利)组合成分操作 3108
const WORD tdxTLZHCFCZFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_DFKHDM,				// 对方客户代码
	TDX_ID_DFMM,				// 对方密码
	TDX_ID_DFZJZH,				// 对方资金账号
	TDX_ID_DFZHLB,				// 对方账号类别
	TDX_ID_DFGDDM,				// 对方股东代码
	TDX_ID_XHZHLX,				// 现货账号类型

	TDX_ID_XT_TOKEN,			// 令牌
	TDX_ID_CZBZ,				// 操作标志(0--增加,1--删除)
	TDX_ID_ZHDM,				// 组合代码
	TDX_ID_ZQDM,				// 证券代码
	TDX_ID_ZQMC,				// 证券名称
	TDX_ID_CFQZ,				// 成分权重
	TDX_ID_CFSL,				// 成分数量
	TDX_ID_XYJYBS,				// 信用交易标识
};

// (套利)策略代码查询 3110
const WORD tdxTLCLDMCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_DFKHDM,				// 对方客户代码
	TDX_ID_DFMM,				// 对方密码
	TDX_ID_DFZJZH,				// 对方资金账号
	TDX_ID_DFZHLB,				// 对方账号类别
	TDX_ID_DFGDDM,				// 对方股东代码
	TDX_ID_XHZHLX,				// 现货账号类型

	TDX_ID_XT_TOKEN,			// 令牌
	TDX_ID_XT_STARTPOS,			// 查询开始位置
	TDX_ID_CLDM,				// 策略代码
};

// (套利)策略成分查询 3112
const WORD tdxTLCLCFCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_DFKHDM,				// 对方客户代码
	TDX_ID_DFMM,				// 对方密码
	TDX_ID_DFZJZH,				// 对方资金账号
	TDX_ID_DFZHLB,				// 对方账号类别
	TDX_ID_DFGDDM,				// 对方股东代码
	TDX_ID_XHZHLX,				// 现货账号类型

	TDX_ID_XT_TOKEN,			// 令牌
	TDX_ID_XT_STARTPOS,			// 查询开始位置
	TDX_ID_CLDM,				// 策略代码
	TDX_ID_ZQDM,				// 证券代码
};

// (套利)策略代码操作 3114
const WORD tdxTLCLDMCZFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_DFKHDM,				// 对方客户代码
	TDX_ID_DFMM,				// 对方密码
	TDX_ID_DFZJZH,				// 对方资金账号
	TDX_ID_DFZHLB,				// 对方账号类别
	TDX_ID_DFGDDM,				// 对方股东代码
	TDX_ID_XHZHLX,				// 现货账号类型

	TDX_ID_XT_TOKEN,			// 令牌
	TDX_ID_CZBZ,				// 操作标志
	TDX_ID_CLDM,				// 策略代码
	TDX_ID_CLMC,				// 策略名称
	TDX_ID_HYDM,				// 合约代码
	TDX_ID_QZFS,				// 券种方式
	TDX_ID_ZHDM,				// 组合代码
	TDX_ID_WTJE,				// 委托金额
	TDX_ID_MRJEJSJZ,			// 买入金额计算基准
};

// (套利)策略成分操作 3116
const WORD tdxTLCLCFCZFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_DFKHDM,				// 对方客户代码
	TDX_ID_DFMM,				// 对方密码
	TDX_ID_DFZJZH,				// 对方资金账号
	TDX_ID_DFZHLB,				// 对方账号类别
	TDX_ID_DFGDDM,				// 对方股东代码
	TDX_ID_XHZHLX,				// 现货账号类型

	TDX_ID_XT_TOKEN,			// 令牌
	TDX_ID_CZBZ,				// 操作标志
	TDX_ID_CLDM,				// 策略代码
	TDX_ID_ZQDM,				// 证券代码
	TDX_ID_ZQMC,				// 证券名称
	TDX_ID_CFQZ,				// 成分权重
	TDX_ID_CFSL,				// 成分数量
	TDX_ID_XYJYBS,				// 信用交易标识
};

// (套利)批号操作 3118
const WORD tdxTLPHCZFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_DFKHDM,				// 对方客户代码
	TDX_ID_DFMM,				// 对方密码
	TDX_ID_DFZJZH,				// 对方资金账号
	TDX_ID_DFZHLB,				// 对方账号类别
	TDX_ID_DFGDDM,				// 对方股东代码
	TDX_ID_XHZHLX,				// 现货账号类型

	TDX_ID_XT_TOKEN,			// 令牌
	TDX_ID_CZBZ,				// 操作标志(0--申请,1--设置,2--暂停交易股票,3--恢复交易股票)
	TDX_ID_ZQDM,				// 证券代码
	TDX_ID_PCH,					// 批次号
	TDX_ID_PCHLX,				// 批次号类型
	TDX_ID_ZHDM,				// 组合代码
	TDX_ID_CLDM,				// 策略代码
	TDX_ID_DKBZ,				// 多空标志
	TDX_ID_TZSL,				// 投资数量
	TDX_ID_BJFS,				// 报价方式
	TDX_ID_DFBJFS,				// 对方报价方式
	TDX_ID_MCYGBJ,				// 卖出余股标记
	TDX_ID_SYKCBJ,				// 使用库存标记
	TDX_ID_SYFZXHBJ,			// 使用辅助现货标记
	TDX_ID_ZDWTBJ,				// 自动委托标记
	TDX_ID_ZDWTCS,				// 自动委托次数
	TDX_ID_ZQMC,				// 证券名称
};

// (套利)批号查询 3120
const WORD tdxTLPHCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_DFKHDM,				// 对方客户代码
	TDX_ID_DFMM,				// 对方密码
	TDX_ID_DFZJZH,				// 对方资金账号
	TDX_ID_DFZHLB,				// 对方账号类别
	TDX_ID_DFGDDM,				// 对方股东代码
	TDX_ID_XHZHLX,				// 现货账号类型

	TDX_ID_XT_TOKEN,			// 令牌
	TDX_ID_XT_STARTPOS,			// 查询开始位置
	TDX_ID_PCH,					// 批次号
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_CZZT,				// 操作状态
};

// (套利)批号委托列表 3122
const WORD tdxTLPHWTLBFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_DFKHDM,				// 对方客户代码
	TDX_ID_DFMM,				// 对方密码
	TDX_ID_DFZJZH,				// 对方资金账号
	TDX_ID_DFZHLB,				// 对方账号类别
	TDX_ID_DFGDDM,				// 对方股东代码
	TDX_ID_XHZHLX,				// 现货账号类型

	TDX_ID_XT_TOKEN,			// 令牌
	TDX_ID_XT_STARTPOS,			// 查询开始位置
	TDX_ID_PCH,					// 批次号
	TDX_ID_PCHRQ,				// 批次号日期
	TDX_ID_CZBZ,				// 操作标志(0--默认,1--建仓,2--平仓,3--撤单,4--调整)
	TDX_ID_ZHDM,				// 组合代码
	TDX_ID_BJFS,				// 报价方式
	TDX_ID_DFBJFS,				// 对方报价方式
	TDX_ID_MCYGBJ,				// 卖出余股标记
};

// (套利)批号委托执行 3124
const WORD tdxTLPHWTZXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_DFKHDM,				// 对方客户代码
	TDX_ID_DFMM,				// 对方密码
	TDX_ID_DFZJZH,				// 对方资金账号
	TDX_ID_DFZHLB,				// 对方账号类别
	TDX_ID_DFGDDM,				// 对方股东代码
	TDX_ID_XHZHLX,				// 现货账号类型

	TDX_ID_XT_TOKEN,			// 令牌
	TDX_ID_PCH,					// 批次号
	TDX_ID_PCHRQ,				// 批次号日期
	TDX_ID_CZBZ,				// 操作标志
	TDX_ID_ZHDM,				// 组合代码
	TDX_ID_JC,					// 基差
	TDX_ID_LX,					// 类型
	TDX_ID_BJFS,				// 报价方式
	TDX_ID_DFBJFS,				// 对方报价方式
	TDX_ID_MCYGBJ,				// 卖出余股标记
};

// (套利)批号委托查询 3126
const WORD tdxTLPHWTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_DFKHDM,				// 对方客户代码
	TDX_ID_DFMM,				// 对方密码
	TDX_ID_DFZJZH,				// 对方资金账号
	TDX_ID_DFZHLB,				// 对方账号类别
	TDX_ID_DFGDDM,				// 对方股东代码
	TDX_ID_XHZHLX,				// 现货账号类型

	TDX_ID_XT_TOKEN,			// 令牌
	TDX_ID_XT_STARTPOS,			// 查询开始位置
	TDX_ID_PCH,					// 批次号
};

// (套利)批号持仓查询 3128
const WORD tdxTLPHCCCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_DFKHDM,				// 对方客户代码
	TDX_ID_DFMM,				// 对方密码
	TDX_ID_DFZJZH,				// 对方资金账号
	TDX_ID_DFZHLB,				// 对方账号类别
	TDX_ID_DFGDDM,				// 对方股东代码
	TDX_ID_XHZHLX,				// 现货账号类型

	TDX_ID_XT_TOKEN,			// 令牌
	TDX_ID_XT_STARTPOS,			// 查询开始位置
	TDX_ID_PCH,					// 批次号
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

// (算法交易)订单操作 3190
const WORD tdxSFJYDDCZFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_CZBZ,				// 操作标志(0--新增,1--修改,3--撤销,其他--不支持)
	TDX_ID_ZQDM,				// 证券代码
	TDX_ID_XT_MODE,				// 模式(算法类型)
	TDX_ID_XT_PARAM,			// 参数(算法参数集)
	TDX_ID_LSH,					// 流水号(算法订单序号)
};

// (算法交易)订单列表查询 3192
const WORD tdxSFJYDDLBCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询开始位置
	TDX_ID_LSH,					// 流水号(算法订单序号,空--全部)
	TDX_ID_KGDBZ,				// 可改单标志(0--全部,1--只返回可改单,默认--0)
	TDX_ID_KCDBZ,				// 可撤单标志(0--全部,1--只返回可撤单,默认--0)
	TDX_ID_CDBZ,				// 撤单标志(0--全部,1--只返回未撤单,默认--0)
	TDX_ID_XT_MODE,				// 模式(算法类型)
	TDX_ID_CZBZ,				// 操作标志
};

// (算法交易)订单结果查询 3194
const WORD tdxSFJYDDJGCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询开始位置
	TDX_ID_LSH,					// 流水号(算法订单序号,空--全部)
	TDX_ID_XT_MODE,				// 模式(算法类型)
	TDX_ID_CZBZ,				// 操作标志
};

//////////////////////////////////////////////////////////////////////////
//	信用交易
//////////////////////////////////////////////////////////////////////////

// 信用资产查询 3200
const WORD tdxXYZCCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询开始位置
	TDX_ID_ZQDM,				// 证券代码
	TDX_ID_MMBZ,				// 买卖标志
	TDX_ID_WTFS,				// 委托方式(和买卖标志相关)
};

// 信用股份查询 3202
const WORD tdxXYGFCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询开始位置
	TDX_ID_MMBZ,				// 买卖标志(只处理信用交易的买卖标志,其它的默认返回"已融券股份")
	TDX_ID_WTFS,				// 委托方式(和买卖标志相关)
	TDX_ID_ZQDM,				// 证券代码
};

// 信用合约查询(默认未平仓) 3204
const WORD tdxXYHYCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询开始位置
	TDX_ID_KSRQ,				// 查询开始日期
	TDX_ID_ZZRQ,				// 查询终止日期
	TDX_ID_MMBZ,				// 买卖标志
	TDX_ID_WTFS,				// 委托方式(和买卖标志相关)
	TDX_ID_CZBZ,				// 操作标志(0--全部,1--融资,2--融券,默认--0)
};

// 信用合约已平仓查询 3206
const WORD tdxXYHYYPCCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询开始位置

	TDX_ID_KSRQ,				// 查询开始日期
	TDX_ID_ZZRQ,				// 查询终止日期
	TDX_ID_CZBZ,				// 操作标志(0--全部,1--融资,2--融券,默认--0)
};

// 信用上限查询 3208
const WORD tdxXYSXCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询开始位置
	TDX_ID_ZQDM,				// 证券代码
	TDX_ID_MMBZ,				// 买卖标志
	TDX_ID_WTFS,				// 委托方式(和买卖标志相关)
};

// 信用负债查询 3210
const WORD tdxXYFZCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询开始位置
	TDX_ID_BZ,					// (保留)币种标识
};

// 非信用资产查询 3212
const WORD tdxFXYZCCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询开始位置
	TDX_ID_BZ,					// (保留)币种标识
};

// 信用合约当日查询 3214
const WORD tdxXYHYDRCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询开始位置
};

// 信用交易标的证券查询 3216
const WORD tdxXYJYBDZQCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询开始位置
	TDX_ID_MMBZ,				// 买卖标志
	TDX_ID_WTFS,				// 委托方式
	TDX_ID_ZQDM,				// 证券代码
};

// 信用交易综合信息查询 3218
const WORD tdxXYJYZHXXCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询开始位置
};

// 信用交易担保品证券查询 3220
const WORD tdxXYJYDBPZQCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询开始位置
	TDX_ID_ZQDM,				// 证券代码
};

// 信用交易融资买入证券查询 3222
const WORD tdxXYJYRZMRZQCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询开始位置
};

// 信用交易融券卖出证券查询 3224
const WORD tdxXYJYRQMCZQCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询开始位置
};

// 信用交易代码提示信息查询 3226
const WORD tdxXYJYDMTSXXCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询开始位置
	TDX_ID_MMBZ,				// 买卖标志
	TDX_ID_WTFS,				// 委托类型
	TDX_ID_ZQDM,				// 证券代码
};

// 信用交易合约汇总查询 3228
const WORD tdxXYJYHYHZCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询开始位置
	TDX_ID_KSRQ,				// 查询开始日期
	TDX_ID_ZZRQ,				// 查询终止日期
	TDX_ID_MMBZ,				// 买卖标志
	TDX_ID_WTFS,				// 委托方式(和买卖标志相关)
};

// 信用交易融资买入配套查询 3230
const WORD tdxXYJYRZMRPTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询开始位置
};

// 信用交易融券卖出配套查询 3232
const WORD tdxXYJYRQMCPTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询开始位置
};

// 信用交易买券还券配套查询 3234
const WORD tdxXYJYMQHQPTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询开始位置
};

// 信用交易余券划转配套查询 3236
const WORD tdxXYJYYQHZPTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询开始位置
};

// 信用交易现券还券配套查询 3238
const WORD tdxXYJYXQHQPTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询开始位置
};

// 信用交易担保品划转配套查询 3240
const WORD tdxXYJYDBPHZPTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询开始位置
	TDX_ID_WTFS,				// 委托类别(划入/划出)
	TDX_ID_DFFZDM,				// 对方分支代码
	TDX_ID_DFKHDM,				// 对方客户代码
	TDX_ID_DFMM,				// 对方密码
};

// 信用交易担保品划入配套查询 3242
const WORD tdxXYJYDBPHRPTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询开始位置
	TDX_ID_DFFZDM,				// 对方分支代码
	TDX_ID_DFKHDM,				// 对方客户代码
	TDX_ID_DFMM,				// 对方密码
};

// 信用交易担保品划出配套查询 3244
const WORD tdxXYJYDBPHCPTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询开始位置
	TDX_ID_DFFZDM,				// 对方分支代码
	TDX_ID_DFKHDM,				// 对方客户代码
	TDX_ID_DFMM,				// 对方密码
};

// 信用交易现金还款配套查询 3246
const WORD tdxXYJYXJHKPTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询开始位置
};

// 信用交易卖券还款配套查询 3248
const WORD tdxXYJYMQHKPTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询开始位置
};

// 信用交易融资平仓卖出配套查询 3250
const WORD tdxXYJYRZPCMCPTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询开始位置
};

// 信用交易融券平仓买入配套查询 3252
const WORD tdxXYJYRQPCMRPTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询开始位置
};

// 信用交易利率信息查询 3254
const WORD tdxXYJYLLXXCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询开始位置
};

// 信用交易融券余额查询 3256
const WORD tdxXYJYRQYECXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询开始位置
};

// 信用交易融资余额查询 3258
const WORD tdxXYJYRZYECXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询开始位置
};

// 信用交易非交易化转查询 3260
const WORD tdxXYJYFJYHZCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式
	
	TDX_ID_XT_STARTPOS,			// 查询开始位置
	TDX_ID_KSRQ,				// 查询开始日期
	TDX_ID_ZZRQ,				// 查询终止日期
};

// 信用交易利息费用查询 3262
const WORD tdxXYJYLXFYCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询开始位置
};

// 信用交易资金负债查询 3264
const WORD tdxXYJYZJFZCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询开始位置
	TDX_ID_KSRQ,				// 查询开始日期
	TDX_ID_ZZRQ,				// 查询终止日期
};

// 信用交易证券负债查询 3266
const WORD tdxXYJYZQFZCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询开始位置
	TDX_ID_KSRQ,				// 查询开始日期
	TDX_ID_ZZRQ,				// 查询终止日期
};

// 信用交易客户签约查询 3268
const WORD tdxXYJYKHQYCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询开始位置
};

// 信用交易客户协议处理 3270
const WORD tdxXYJYKHXYCLFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_LX,					// 类型(0--自动还款)
	TDX_ID_CZBZ,				// 操作标志(0--查询,1--开通,2--取消,默认--0)
};

// 信用交易偿还明细查询 3272
const WORD tdxXYJYCHMXCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询开始位置
};

// 信用交易融资合约查询 3274
const WORD tdxXYJYRZHYCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_CZBZ,				// 操作标志(0--全部,1--未了结,2--已了结,默认--0)
};

// 信用交易融券合约查询 3276
const WORD tdxXYJYRQHYCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
	TDX_ID_CZBZ,				// 操作标志(0--全部,1--未了结,2--已了结,默认--0)
};

// 信用交易担保品划转查询 3278
const WORD tdxXYJYDBPHZCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

// 信用交易买入担保品配套查询 3280
const WORD tdxXYJYMRDBPPTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 信用交易卖出担保品配套查询 3282
const WORD tdxXYJYMCDBPPTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 信用交易归还融券费用配套查询 3284
const WORD tdxXYJYGHRQFYPTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 信用交易负债流水查询 3286
const WORD tdxXYJYFZLSCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

// 信用交易现金替代还券配套查询 3288
const WORD tdxXYJYXJTDHQPTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 信用交易维持担保比率查询 3290
const WORD tdxXYJYWCDBBLCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 信用交易额度管理 3292
const WORD tdxXYJYEDGLFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_CZBZ,				// 操作标志(0--查询,1--调整 2--申请)
	TDX_ID_RZSX,				// 融资信用上限
	TDX_ID_RQSX,				// 融券信用上限
	TDX_ID_BZ,					// 币种
	TDX_ID_XT_REMARK,			// 备注
};

// 信用交易额度变更查询 3294
const WORD tdxXYJYEDBGCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

// 信用交易平仓融资合约查询 3296
const WORD tdxXYJYPCRZHYCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

// 信用交易平仓融券合约查询 3298
const WORD tdxXYJYPCRQHYCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

//////////////////////////////////////////////////////////////////////////
//	转融通
//////////////////////////////////////////////////////////////////////////

// 转融通业务操作 3400
const WORD tdxZRTYWCZFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_CZBZ,				// 操作标志(偶数--信息,奇数--操作,具体见"标识字段统计"文档)
	TDX_ID_XT_PARAM,			// 参数(所有"转融通"功能约定相同序列,以'\1'分割,尽量避免客户端定点取其他字段)
	TDX_ID_BZ,					// 币种
	TDX_ID_ZQDM,				// 证券代码
	TDX_ID_HYQX,				// 合约期限(约定的期限天数)
	TDX_ID_HYLL,				// 合约利率(约定年利率)
	TDX_ID_TQZZLL,				// 提前终止利率(提前归还利率)
	TDX_ID_WTJE,				// 委托金额
	TDX_ID_WTSL,				// 委托数量
	TDX_ID_WTRQ,				// 委托日期(开始使用日期)
	TDX_ID_WTBH,				// 委托编号
	TDX_ID_PCH,					// 批次号
	TDX_ID_DFXWDM,				// 对方席位代码
	TDX_ID_DFGDDM,				// 对方股东代码
	TDX_ID_YDXH,				// 约定序号
	TDX_ID_TSXX1,				// 提示信息1(可选期限天数)
	TDX_ID_XWDM,				// 席位代码
};

// 转融通标的证券查询 3402
const WORD tdxZRTBDZQCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_ZQDM,				// 证券代码
	TDX_ID_HYQX,				// 合约期限
};

// 转融通资金信息查询 3404
const WORD tdxZRTZJXXCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 转融通股份信息查询 3406
const WORD tdxZRTGFXXCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 转融通融资买入配套查询 3408
const WORD tdxZRTRZMRPTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 转融通融券卖出配套查询 3410
const WORD tdxZRTRQMCPTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 转融通资金借入申请配套查询 3412
const WORD tdxZRTZJJRSQPTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 转融通股份借入申请配套查询 3414
const WORD tdxZRTGFJRSQPTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 转融通借入展期申请配套查询 3416
const WORD tdxZRTJRZQSQPTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 转融通提前归还申请配套查询 3418
const WORD tdxZRTTQGHSQPTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 转融通借入业务撤单查询 3420
const WORD tdxZRTJRYWCDCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 转融通借入业务当日查询 3422
const WORD tdxZRTJRYWDRCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 转融通借入业务历史查询 3424
const WORD tdxZRTJRYWLSCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

// 转融通当日借入合约查询 3426
const WORD tdxZRTDRJRHYCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 转融通未了借入合约查询 3428
const WORD tdxZRTWLJRHYCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

// 转融通已了借入合约查询 3430
const WORD tdxZRTYLJRHYCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

// 转融通资金出借申请配套查询 3432
const WORD tdxZRTZJCJSQPTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 转融通股份出借申请配套查询 3434
const WORD tdxZRTGFCJSQPTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 转融通资金出借确定配套查询 3436
const WORD tdxZRTZJCJQDPTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 转融通股份出借确定配套查询 3438
const WORD tdxZRTGFCJQDPTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 转融通出借业务撤单查询 3440
const WORD tdxZRTCJYWCDCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 转融通出借业务当日查询 3442
const WORD tdxZRTCJYWDRCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 转融通出借业务历史查询 3444
const WORD tdxZRTCJYWLSCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

// 转融通出借提前索还配套查询 3446
const WORD tdxZRTCJTQSHPTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 转融通出借同意展期配套查询 3448
const WORD tdxZRTCJTYZQPTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 转融通期限费率查询 3450
const WORD tdxZRTQXFLCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_CZBZ,				// 操作标志(与"转融通业务操作 3400"功能相同)
	TDX_ID_ZQDM,				// 证券代码
};

// 转融通出借合约查询 3452
const WORD tdxZRTCJHYCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

// 转融通出借历史合约查询 3454
const WORD tdxZRTCJLSHYCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
	TDX_ID_KSRQ,				// 开始日期
	TDX_ID_ZZRQ,				// 终止日期
};

// 转融通卖出还款配套查询 3456
const WORD tdxZRTMCHKPTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 转融通买入还券配套查询 3458
const WORD tdxZRTMRHQPTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 转融通现金还款配套查询 3460
const WORD tdxZRTXJHKPTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 转融通现券还券配套查询 3462
const WORD tdxZRTXQHQPTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 转融通可出借信息查询 3464
const WORD tdxZRTKCJXXCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 转融通借入同意索还配套查询 3466
const WORD tdxZRTJRTYSHPTCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

// 转融通出借账户信息查询 3468
const WORD tdxZRTCJZHXXCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 起始序号
};

//////////////////////////////////////////////////////////////////////////
//	其他
//////////////////////////////////////////////////////////////////////////

// 新利开通取消自动代理 4100
const WORD tdxXLKTQXZDDLFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XLYZT_XGKT_FLAG,		// 开通标记
};

// 新利开通合作配售 4102
const WORD tdxXLKTHZPSFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XLYZT_START_DATE,	// 合作配售生效日期
	TDX_ID_XLYZT_END_DATE,		// 合作配售终止日期
};

// 新利取消合作配售 4104
const WORD tdxXLQXHZPSFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式
};

// 新利开通合作回购 4106
const WORD tdxXLKTHZHGFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XLYZT_DEBT_KIND,		// 回购品种
	TDX_ID_XLYZT_JE_MIN,		// 资金下限
	TDX_ID_XLYZT_JE_MAX,		// 资金上限
	TDX_ID_XLYZT_START_DATE,	// 合作配售生效日期
	TDX_ID_XLYZT_END_DATE,		// 合作配售终止日期
};

// 新利取消合作回购 4108
const WORD tdxXLQXHZHGFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式
};

// 新利开通合作申购 4110
const WORD tdxXLKTHZSGFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XLYZT_JE_MIN,		// 资金下限
	TDX_ID_XLYZT_JE_MAX,		// 资金上限
	TDX_ID_XLYZT_START_DATE,	// 合作配售生效日期
	TDX_ID_XLYZT_END_DATE,		// 合作配售终止日期
};

// 新利取消合作申购 4112
const WORD tdxXLQXHZSGFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式
};

// 新利代理功能查询 4114
const WORD tdxXLDLGNCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式
};

//////////////////////////////////////////////////////////////////////////
//  安全功能扩展
//////////////////////////////////////////////////////////////////////////

//安全功能申请 4200
const WORD tdxCAAQGNSQFieldReq[]=
{
	TDX_ID_CA_KHH,			// 完整客户号
	TDX_ID_CA_AQJB,			// 安全级别
	TDX_ID_CA_NEWIP,		// IP信息
	TDX_ID_CA_MMBHWT,		// 密码保护问题
	TDX_ID_CA_JQTZM,		// 机器特征码
};
const WORD tdxCAAQGNSQFieldAns[]=
{
	TDX_ID_CA_RESV,				// (保留)保留字段
};

// 安全功能撤销 4202
const WORD tdxCAAQGNCXFieldReq[]=
{
	TDX_ID_CA_KHH,			// 完整客户号
	TDX_ID_CA_AQJB,			// 安全级别
	TDX_ID_CA_JQTZM,		// 机器特征码
};
const WORD tdxCAAQGNCXFieldAns[]=
{
	TDX_ID_CA_RESV,				// (保留)保留字段
};

//密码保护问题校验 4204
const WORD tdxCAMMBHWTJYFieldReq[]=
{
	TDX_ID_CA_KHH,			// 800 完整客户号
	TDX_ID_CA_MMBHWT1,		// 4231 密码保护问题1
	TDX_ID_CA_MMBHWT2,		// 4232 密码保护问题2
	TDX_ID_CA_MMBHWT3,		// 4233 密码保护问题3
	TDX_ID_CA_MMBHWT4,		// 4234 密码保护问题4
};
const WORD tdxCAMMBHWTJYFieldAns[]=
{
	TDX_ID_CA_MMBHWT1,		// 4231 密码保护问题1
	TDX_ID_CA_MMBHWT2,		// 4232 密码保护问题2
	TDX_ID_CA_MMBHWT3,		// 4233 密码保护问题3
	TDX_ID_CA_MMBHWT4,		// 4234 密码保护问题4
	TDX_ID_CA_RESV,			// 825 (保留)保留字段
};

// 获取挑战坐标 4206
const WORD tdxCAGETTZZBFieldReq[]=
{
	TDX_ID_CA_KHH,			// 完整客户号
};
const WORD tdxCAGETTZZBFieldAns[]=
{
	TDX_ID_CA_TZZB,				// 挑战坐标
	TDX_ID_CA_CSCS,				// 尝试次数
	TDX_ID_CA_RESV,				// (保留)保留字段
};

// 注销矩阵卡 4208
const WORD tdxCAZXJZKFieldReq[]=
{
	TDX_ID_CA_KHH,			// 完整客户号
};
const WORD tdxCAZXJZKFieldAns[]=
{
	TDX_ID_CA_RESV,				// (保留)保留字段
};

// 预留问题 4210
const WORD tdxCAYLWTFieldReq[]=
{
	TDX_ID_CA_KHH,			// 800 完整客户号
	TDX_ID_CA_YLWT,			// 4212 预留问题
};
const WORD tdxCAYLWTFieldAns[]=
{
	TDX_ID_CA_RESV,				// 825 (保留)保留字段
};

// 证书申请 4212
const WORD tdxCACERRAREQFieldReq[]=
{
	TDX_ID_CA_KHH,			// 客户号
	TDX_ID_CA_SLOTSN,		// 装载证书容器SN
	TDX_ID_CA_CID,			// 三方安全机构ID(颁发/验证)
	TDX_ID_CA_CERTREQ,		// 证书申请请求
	TDX_ID_CA_USERCERDN,	// 证书DN
};
const WORD tdxCACERRAREQFieldAns[]=
{
	TDX_ID_CA_CERTTOKEN,	// 证书业务流水号
	TDX_ID_CA_CERTSN,		// 证书编号(只有当开启自动审核并且能立即获取证书时)
	TDX_ID_CA_CERTINFO,		// 证书内容
};

// 证书审核 4214
const WORD tdxCACERAUDITFieldReq[]=
{
	TDX_ID_CA_KHH,			// 完整客户号
};
const WORD tdxCACERAUDITFieldAns[]=
{
	TDX_ID_CA_RESV,			// 保留字段
};

// 证书下载 4216
const WORD tdxCACERDOWNLOADFieldReq[]=
{
	TDX_ID_CA_KHH,			// 完整客户号
	TDX_ID_CA_SLOTSN,		// 装载证书容器SN
};
const WORD tdxCACERDOWNLOADFieldAns[]=
{
	TDX_ID_CA_CERTTOKEN,	// 证书业务号
	TDX_ID_CA_CERTSN,		// 证书编号
	TDX_ID_CA_CERTINFO,		// 证书内容
	TDX_ID_CA_RESV,			// 保留字段
};

// 证书下载确认 4218
const WORD tdxCACERDLCONFIRMFieldReq[]=
{
	TDX_ID_CA_KHH,			// 完整客户号
};
const WORD tdxCACERDLCONFIRMFieldAns[]=
{
	TDX_ID_CA_RESV,			// 保留字段
};

// 添加用户信息 4220
const WORD tdxCAADDYHXXFieldReq[]=
{
	TDX_ID_CA_KHH,			// 完整客户号
	TDX_ID_CA_IDCARD,		// 身份证号
	TDX_ID_CA_SJH,			// 手机号
};
const WORD tdxCAADDYHXXFieldAns[]=
{
	TDX_ID_CA_SJH,			// 手机号
	TDX_ID_CA_RESV,			// (保留)保留字段
};

// 修改用户信息 4222
const WORD tdxCAXGYHXXFieldReq[]=
{
	TDX_ID_CA_KHH,			// 完整客户号
	TDX_ID_CA_SJH,			// 手机号
};
const WORD tdxCAXGYHXXFieldAns[]=
{
	TDX_ID_CA_SJH,				// 手机号
	TDX_ID_CA_RESV,				// (保留)保留字段
};

// 查询用户信息 4224
const WORD tdxCACXYHXXFieldReq[]=
{
	TDX_ID_CA_KHH,			// 完整客户号
};
const WORD tdxCACXYHXXFieldAns[]=
{
	TDX_ID_CA_SJH,				// 手机号
	TDX_ID_CA_RESV,				// (保留)保留字段
};

// 获取手机验证码 4226
const WORD tdxCAGETYZMFieldReq[]=
{
	TDX_ID_CA_KHH,			// 完整客户号
	TDX_ID_CA_USERNICK,		// 用户昵称
	TDX_ID_CA_SJH,			// 客户手机号
	TDX_ID_CA_YZM,			// 验证码
};
const WORD tdxCAGETYZMFieldAns[]=
{
	TDX_ID_CA_YZM,				// 验证码
	TDX_ID_CA_RESV,				// (保留)保留字段
};

// 校验验证码 4228
const WORD tdxCAYZMJYFieldReq[]=
{
	TDX_ID_CA_KHH,			// 完整客户号
	TDX_ID_CA_YZM,			// 验证码
};
const WORD tdxCAYZMJYFieldAns[]=
{	
	TDX_ID_CA_RESV,				// (保留)保留字段
};

// 其他安全认证校验 4230
const WORD tdxOTHCABASEFUNFieldReq[]=
{
	TDX_ID_CA_KHH,			// 完整客户号
	TDX_ID_JYMM,			// 交易密码
	TDX_ID_CA_SQBZ,			// 申请标志
	TDX_ID_CA_AQJB,			// 安全级别
	TDX_ID_CA_KHMC,			// 客户名称
	TDX_ID_CA_TXMM,			// 认证口令
	TDX_ID_CA_XTXMM,		// 新认证口令
	TDX_ID_CA_ZSGY,			// 证书公钥匙
	TDX_ID_CA_SJH,			// 客户手机号
	TDX_ID_CA_ZJHM,			// 客户证件号码
	TDX_ID_CA_KHXB,			// 客户性别
	TDX_ID_CA_EMAIL,		// 客户电子邮件
	TDX_ID_CA_JHM,			// 激活码
	TDX_ID_CA_DRZB,			// 当日指标(根据后端指定客户指标类型,客户端需要定制,例如,当日持仓,当日佣金)
	TDX_ID_CA_NEWIP,		// 本次登陆IP
	TDX_ID_CA_QSRQ,			// 起始查询时间(登录历史信息查询)
	TDX_ID_CA_ZZRQ,			// 终止查询时间(登录历史信息查询)
	TDX_ID_CA_JQTZM,		// 机器特征码
	TDX_ID_CA_MMBHWT1,		// 密码保护问题1
	TDX_ID_CA_MMBHWT2,		// 密码保护问题2
	TDX_ID_CA_MMBHWT3,		// 密码保护问题3
	TDX_ID_CA_MMBHWT4,		// 密码保护问题4
	TDX_ID_CA_MAC,			// 用户MAC地址
	TDX_ID_CA_YLWT,			// 预留问题
	TDX_ID_CA_CERTREQ,		// 证书申请请求(P10)
	TDX_ID_CA_USERCERDN,	// 证书DN信息
	TDX_ID_CA_SEEDINFO,		// 种子信息
	TDX_ID_CA_OTPSN,		// OTPSN序号
	TDX_ID_CA_IDCARD,		// 用户身份证号码
	TDX_ID_CA_YZM,			// 验证码
	TDX_ID_CA_MACHINENAME,	// 机器昵称
};
const WORD tdxOTHCABASEFUNFieldAns[]=
{
	TDX_ID_CA_YHFJ,			// 用户分级
	TDX_ID_CA_YHJBMS,		// 用户级别描述
	TDX_ID_CA_YHQX,			// 用户权限
	TDX_ID_CA_LASTIP,		// 上次登陆IP
	TDX_ID_CA_NEWIP,		// 本次登陆IP
	TDX_ID_CA_LASPROV,		// 上次登录省份
	TDX_ID_CA_NEWPROV,		// 本次登录省份
	TDX_ID_CA_LASSITE,		// 上次登陆城市
	TDX_ID_CA_NEWSITE,		// 本次登陆城市 
	TDX_ID_CA_DLSJ,			// 登陆时间
	TDX_ID_CA_DLRQ,			// 登陆日期
	TDX_ID_CA_TZZB,			// 挑战坐标
	TDX_ID_CA_CSCS,			// 重试次数
	TDX_ID_CA_MAC,			// 用户MAC地址
	TDX_ID_CA_RESV,			// (保留)保留字段
	TDX_ID_CA_YLWT,			// 预留信息
	TDX_ID_CA_BINDNUM,		// 绑定机器台数
	TDX_ID_CA_KJYBZ,		// 可交易标志 此处用作特殊判断标志
	TDX_ID_CA_MACHINENAME,		// 4204 机器昵称
	TDX_ID_CA_JQTZM,			// 4201 机器特征码	
	TDX_ID_CA_MACHINEBINDTIME,	// 4228 机器绑定时间
	TDX_ID_CA_GD_XH,			// 4241	序号
	TDX_ID_CA_GD_DATE,			// 4242	日期
	TDX_ID_CA_GD_TIME,			// 4243	时间
	TDX_ID_CA_GD_HARDINFO,		// 4244 计算机特征码信息
	TDX_ID_CA_GD_MOREINFO,		// 4245	计算机昵称
	TDX_ID_CA_GD_TERMINALTYPE,	// 4246 终端类型
};

// 查询密码保护问题 4232
const WORD tdxCAMMBHWTCXFieldReq[]=
{
	TDX_ID_CA_KHH,			// 完整客户号
};
const WORD tdxCAMMBHWTCXFieldAns[]=
{	
	TDX_ID_CA_MMBHWT,			// 密码保护问题
	TDX_ID_CA_RESV,				// (保留)保留字段
};

// 修改密码保护问题 4234
const WORD tdxCAXGMMBHWTFieldReq[]=
{
	TDX_ID_CA_KHH,				// 完整客户号
	TDX_ID_CA_MMBHWT,			// 密码保护问题
};
const WORD tdxCAXGMMBHWTFieldAns[]=
{	
	TDX_ID_CA_RESV,				// (保留)保留字段
};

// 修改预留问题 4236
const WORD tdxCAXGYLWTFieldReq[]=
{
	TDX_ID_CA_KHH,				// 完整客户号
	TDX_ID_CA_YLWT,				// 密码保护问题
};
const WORD tdxCAXGYLWTFieldAns[]=
{
	TDX_ID_CA_RESV,				// (保留)保留字段
};

// 密码保护问题列表查询 4238
const WORD tdxPWDPROTQUEQUFieldReq[]=
{
	TDX_ID_CA_KHH,					// 800 完整客户号
	TDX_ID_CA_VER,					// 4226 密码保护问题列表版本
};
const WORD tdxPWDPROTQUEQUFieldAns[]=
{
	TDX_ID_CA_VER,					// 4226 密码保护问题列表当前版本
	TDX_ID_CA_PWDPROQUESTION,		// 4227 密码保护问题
	TDX_ID_CA_RESV,					// 825 (保留)保留字段
};

// 申请密码保护问题 4240
const WORD tdxAPPLYPWDQAFieldReq[]=
{
	TDX_ID_CA_KHH,					// 800 完整客户号
	TDX_ID_CA_PWDQACZBZ,			// 4202 密码保护问题操作标志 ( 0-申请,1-修改 )
	TDX_ID_CA_MMBHWT1,				// 4231 密码保护问题1
	TDX_ID_CA_MMBHWT2,				// 4232 密码保护问题2
	TDX_ID_CA_MMBHWT3,				// 4233 密码保护问题3
	TDX_ID_CA_MMBHWT4,				// 4234 密码保护问题4
};
const WORD tdxAPPLYPWDQAFieldAns[]=
{
	TDX_ID_CA_RESV,					// (保留)保留字段
};

// 申请机器特征码绑定 4242
const WORD tdxBINDINFOFieldReq[]=
{
	TDX_ID_CA_KHH,				// 800 客户号							
	TDX_ID_CA_JQTZM,			// 4201 机器特征码
	TDX_ID_CA_MACHINENAME,		// 4204 机器昵称
};
const WORD tdxBINDINFOFieldAns[]=
{
	TDX_ID_CA_RESV,				// 825 保留字段
};

// 查询绑定信息 4244
const WORD tdxQUEBINDINFOFieldReq[]=
{
	TDX_ID_CA_KHH,				// 800 客户号							
};
const WORD tdxQUEBINDINFOFieldAns[]=
{
	TDX_ID_CA_MACHINENAME,		// 4204 机器昵称
	TDX_ID_CA_JQTZM,			// 4201 机器特征码
	TDX_ID_CA_MACHINEBINDTIME,	// 4228 机器绑定时间
};

// 取消绑定 4246
const WORD tdxCANCELBINDFieldReq[]=
{
	TDX_ID_CA_KHH,				// 800 客户号
	TDX_ID_CA_PROVISIONAL,		// 4205 临时标志
	TDX_ID_CA_MACHINENAME,		// 4204 机器昵称
};
const WORD tdxCANCELBINDFieldAns[]=
{
	TDX_ID_CA_RESV,				// 825 保留字段
};

// 安全申请状态查询 4248
const WORD tdxSAFEMODQUEFieldReq[]=
{
	TDX_ID_CA_KHH,				// 800 客户号
	TDX_ID_CA_CZBZ,				// 824 操作标志
};
const WORD tdxSAFEMODQUEFieldAns[]=
{
	TDX_ID_CA_SQBZ,				// 802 申请标志
	TDX_ID_CA_RESV,				// 825 保留字段
};

// 核销用户安全级别 4250
const WORD tdxABUSERLVFieldReq[]=
{
	TDX_ID_CA_KHH,				// 800 客户号
};
const WORD tdxABUSERLVFieldAns[]=
{
	TDX_ID_CA_RESV,				// 825 保留字段
};

// 用户离线 4252
const WORD tdxUSERLOGOUTFieldReq[]=
{
	TDX_ID_CA_KHH,				// 800 客户号
	TDX_ID_CA_CONNID,			// 4203 户连接ID
};
const WORD tdxUSERLOGOUTFieldAns[]=
{
	TDX_ID_CA_RESV,				// 825 保留字段
};

// 用户在线心跳 4254
const WORD tdxUSERALIVEFieldReq[]=
{
	TDX_ID_CA_KHH,				// 800 客户号
	TDX_ID_CA_CONNID,			// 4203 户连接ID
};
const WORD tdxUSERALIVEFieldAns[]=
{
	TDX_ID_CA_RESV,				// 825 保留字段
};

// 取消用户级别 4256
const WORD tdxCANCELLVFieldReq[]=
{
	TDX_ID_CA_KHH,				// 800 客户号
	TDX_ID_CA_CZBZ,				// 824 操作标志
	TDX_ID_CA_AQJB,				// 806 安全级别
	TDX_ID_CA_OTPSN,			// 4222 OTPsn
};
const WORD tdxCANCELLVFieldAns[]=
{
	TDX_ID_CA_RESV,				// 825 保留字段
};

// 获取产品名称 4258
const WORD tdxGETPROINFOFieldReq[]=
{
	TDX_ID_CA_KHH,				// 800 客户号
};
const WORD tdxGETPROINFOFieldAns[]=
{
	TDX_ID_CA_QSRQ ,			// 896 起始时间
	TDX_ID_CA_ZZRQ ,			// 897 终止时间
	TDX_ID_CA_RESETFLAG ,		// 856 有效标志
	TDX_ID_CA_YHQX ,			// 809 用户权限
	TDX_ID_CA_YHJBBZ ,			// 836 用户级别备注
};


// 注册用户 4280
const WORD tdxREGUSERFieldReq[]= 
{
	TDX_ID_CA_KHMC,				// 801 客户名称
	TDX_ID_CA_USERNICK,			// 4229 用户昵称
	TDX_ID_CA_TXMM,				// 803 认证口令
	TDX_ID_CA_CARDTYPE,			// 4231	证件类型
	TDX_ID_CA_IDCARD,			// 4224 用户身份证号码
	TDX_ID_CA_KHXB,				// 862 客户性别
	TDX_ID_CA_BIRTH,			// 4232 出生日期
	TDX_ID_CA_POSTCODE,			// 4233 邮政编码
	TDX_ID_CA_ADDRESS,			// 4234 联系地址
	TDX_ID_CA_OFFPHONE,			// 4235 办公电话
	TDX_ID_CA_HOMEPHONE,		// 4236 家庭电话
	TDX_ID_CA_FAXPHONE,			// 4237 传真电话
	TDX_ID_CA_SJH,				// 860 客户手机号
	TDX_ID_CA_EMAIL,			// 863 客户电子邮件
	TDX_ID_CA_EDUCATION,		// 4238 学历
	TDX_ID_CA_YZM,				// 4225 短信验证码
	TDX_ID_CA_CZSX,				// 823 操作属性
	TDX_ID_CA_ISVIPHOST,		// 837 是否VIP, 不用校验手机动态码
};
const WORD tdxREGUSERFieldAns[]=
{
	TDX_ID_CA_KHH,				// 800 客户号
	TDX_ID_CA_RESV,				// 825 保留字段
};

// 修改注册密码 4282
const WORD tdxALTERREGPWDFieldReq[]=
{
	TDX_ID_CA_KHH,				// 800 客户号
	TDX_ID_CA_TXMM,				// 803 认证口令
	TDX_ID_CA_XTXMM,			// 804 新认证口令
};
const WORD tdxALTERREGPWDFieldAns[]=
{
	TDX_ID_CA_RESV,				// 825 保留字段
};

// 单点登陆令牌操作 4284
const WORD tdxSSOFieldReq[]=
{
	TDX_ID_CA_KHH,				// 800 客户号
	TDX_ID_CA_CZBZ,				// 824 操作标示(0 生成令牌 1 校验令牌)
	TDX_ID_CA_TOKEN,			// 4239 令牌
	TDX_ID_CA_RESV,				// 825 保留字段
};
const WORD tdxSSOFieldAns[]=
{
	TDX_ID_CA_TOKEN,			// 4239 令牌
	TDX_ID_CA_RESV,				// 825 保留字段
};
// 单点登陆根据令牌取用户信息 4286
const WORD tdxSSOYHXXFieldReq[]=
{
	TDX_ID_CA_TOKEN,			// 4239 令牌
};
const WORD tdxSSOYHXXFieldAns[]=
{
	TDX_ID_CA_KHH,				// 800 客户号
};
// 证书吊销
const WORD tdxCERDELFieldReq[]=
{
	TDX_ID_CA_KHH,			// 800 客户号	
	TDX_ID_CA_SLOTSN,		// 装载证书容器SN
	TDX_ID_CA_CERTSN,		// 证书编号
};
const WORD tdxCERDELFieldAns[]=
{
	TDX_ID_CA_RESV,				// 825 保留字段
};
// OTP同步
const WORD tdxOTPSYNFieldReq[]=
{
	TDX_ID_CA_KHH,			// 800 客户号
	TDX_ID_CA_YYBID,		// 营业部ID
	TDX_ID_CA_TXMM,			// 第一次动态口令
	TDX_ID_CA_XTXMM,		// 第二次动态口令
	TDX_ID_CA_CZBZ,			// 824 操作标示(0-客户端请求 1-HTTP请求)
	TDX_ID_CA_RESV,			// 825 保留字段(0-OTP同步,1-OTP认证)
};
const WORD tdxOTPSYNFieldAns[]=
{
	TDX_ID_CA_RESV,				// 825 保留字段
};
// 检查数据一致性
const WORD tdxCHECKRECORDFieldReq[]=
{
	TDX_ID_CA_KHH,			// 800 客户号
};
const WORD tdxCHECKRECORDFieldAns[]=
{
	TDX_ID_CA_RESV,				// 825 保留字段
};
// 用户认证 4294
const WORD tdxPAAUTHFieldReq[]=
{
	TDX_ID_CA_KHH,				// 800 客户号
	TDX_ID_CA_TXMM,				// 803 认证口令
	TDX_ID_CA_CZY,				// 821 操作员
};
const WORD tdxPAAUTHFieldAns[]=
{
	TDX_ID_CA_YHFJ,				// 用户分级
	TDX_ID_CA_RESV,				// 825 保留字段
};
const WORD tdxPAACCREPORTFieldReq[]=
{
	TDX_ID_CA_KHH,				// 800 客户号
};
const WORD tdxPAACCREPORTFieldAns[]=
{
	TDX_ID_CA_RESV,				// 825 保留字段
};
// OTP豁免
const WORD tdxOTPTEMPFieldReq[]=
{
	TDX_ID_CA_KHH,				// 800 客户号
	TDX_ID_CA_CZBZ,				// 824 操作标示
};
const WORD tdxOTPTEMPFieldAns[]=
{
	TDX_ID_CA_RESV,				// 825 保留字段
};
// 其他安全认证获取验证码 4300
const WORD tdxOTHCAGETYZMFUNFieldReq[]=
{
	TDX_ID_CA_KHH,			// 完整客户号
	TDX_ID_CA_SQBZ,			// 申请标志
	TDX_ID_CA_AQJB,			// 安全级别
	TDX_ID_CA_KHMC,			// 客户名称
	TDX_ID_CA_TXMM,			// 认证口令
	TDX_ID_CA_XTXMM,		// 新认证口令
	TDX_ID_CA_ZSGY,			// 证书公钥匙
	TDX_ID_CA_SJH,			// 客户手机号
	TDX_ID_CA_ZJHM,			// 客户证件号码
	TDX_ID_CA_KHXB,			// 客户性别
	TDX_ID_CA_EMAIL,		// 客户电子邮件
	TDX_ID_CA_JHM,			// 激活码
	TDX_ID_CA_DRZB,			// 当日指标(根据后端指定客户指标类型,客户端需要定制,例如,当日持仓,当日佣金)
	TDX_ID_CA_NEWIP,		// 本次登陆IP
	TDX_ID_CA_QSRQ,			// 起始查询时间(登录历史信息查询)
	TDX_ID_CA_ZZRQ,			// 终止查询时间(登录历史信息查询)
	TDX_ID_CA_JQTZM,		// 机器特征码
	TDX_ID_CA_MMBHWT1,		// 密码保护问题1
	TDX_ID_CA_MMBHWT2,		// 密码保护问题2
	TDX_ID_CA_MMBHWT3,		// 密码保护问题3
	TDX_ID_CA_MMBHWT4,		// 密码保护问题4
	TDX_ID_CA_MAC,			// 用户MAC地址
	TDX_ID_CA_YLWT,			// 预留问题
	TDX_ID_CA_CERTREQ,		// 证书申请请求(P10)
	TDX_ID_CA_USERCERDN,	// 证书DN信息
	TDX_ID_CA_SEEDINFO,		// 种子信息
	TDX_ID_CA_OTPSN,		// OTPSN序号
	TDX_ID_CA_IDCARD,		// 用户身份证号码
	TDX_ID_CA_YZM,			// 验证码
	TDX_ID_CA_MACHINENAME,	// 机器昵称
};
const WORD tdxOTHCAGETYZMFUNFieldAns[]=
{
	TDX_ID_CA_YHFJ,			// 用户分级
	TDX_ID_CA_YHJBMS,		// 用户级别描述
	TDX_ID_CA_YHQX,			// 用户权限
	TDX_ID_CA_LASTIP,		// 上次登陆IP
	TDX_ID_CA_NEWIP,		// 本次登陆IP
	TDX_ID_CA_LASPROV,		// 上次登录省份
	TDX_ID_CA_NEWPROV,		// 本次登录省份
	TDX_ID_CA_DLSJ,			// 登陆时间
	TDX_ID_CA_DLRQ,			// 登陆日期
	TDX_ID_CA_TZZB,			// 挑战坐标
	TDX_ID_CA_CSCS,			// 重试次数
	TDX_ID_CA_MAC,			// 用户MAC地址
	TDX_ID_CA_YLWT,			// 预留信息
	TDX_ID_CA_BINDNUM,		// 绑定机器台数
	TDX_ID_CA_KJYBZ,		// 可交易标志 此处用作特殊判断标志
	TDX_ID_CA_MACHINENAME,	// 机器昵称
	TDX_ID_CA_JQTZM,		// 机器特征码
	TDX_ID_CA_RESV,			// (保留)保留字段
};

// 自选股上传下载
const WORD tdxOPMYSTOCKFUNFieldReq[]=
{
	TDX_ID_CA_KHH,			// (800) 完整客户号
	TDX_ID_CA_CZBZ,			// (824) 操作标志 0- 下载, 1上传
	TDX_ID_CA_USERSTOCK,	// (4241) 自选股信息
	TDX_ID_XT_MODE,			// 模式(配置类型)
	TDX_ID_XT_PARAM,		// 参数(配置信息)
	TDX_ID_XT_DESCRIPTION,	// 描述(配置描述)
	TDX_ID_XT_REMARK,		// 备注(配置分组)
};
const WORD tdxOPMYSTOCKFUNFieldAns[]=
{
	TDX_ID_CA_CZBZ,			// (824) 操作标志 0- 下载, 1上传
	TDX_ID_CA_USERSTOCK,	// (4241) 自选股信息
	TDX_ID_XT_MODE,			// 模式(配置类型)
	TDX_ID_XT_PARAM,		// 参数(配置信息)
	TDX_ID_XT_DESCRIPTION,	// 描述(配置描述)
	TDX_ID_CA_RESV,			// (825) 预留信息
};

// 找回用户密码 4304
const WORD tdxFETCHPWDFUNFieldReq[]=
{
	TDX_ID_CA_KHH,			// (800) 完整客户号
	TDX_ID_CA_TXMM,			// 新用户密码
	TDX_ID_CA_USERNICK,		// 4229 用户昵称
	TDX_ID_CA_YZM,			// 4225 验证码
};
const WORD tdxFETCHPWDFUNFieldAns[]=
{
	TDX_ID_CA_RESV,			// (825) 预留信息
};

// 注册用户信息查询
const WORD tdxQUERYREGUDATAFUNFieldReq[]=
{
	TDX_ID_CA_KHH,			// (800) 完整客户号
	TDX_ID_CA_TXMM,			// 803 认证口令
};
const WORD tdxQUERYREGUDATAFUNFieldAns[]=
{
	TDX_ID_CA_KHMC,				// 801 客户名称
	TDX_ID_CA_USERNICK,			// 4229 用户昵称
	TDX_ID_CA_CARDTYPE,			// 4231	证件类型
	TDX_ID_CA_IDCARD,			// 4224 用户身份证号码
	TDX_ID_CA_KHXB,				// 862 客户性别
	TDX_ID_CA_BIRTH,			// 4232 出生日期
	TDX_ID_CA_POSTCODE,			// 4233 邮政编码
	TDX_ID_CA_ADDRESS,			// 4234 联系地址
	TDX_ID_CA_OFFPHONE,			// 4235 办公电话
	TDX_ID_CA_HOMEPHONE,		// 4236 家庭电话
	TDX_ID_CA_FAXPHONE,			// 4237 传真电话
	TDX_ID_CA_SJH,				// 860 客户手机号
	TDX_ID_CA_EMAIL,			// 863 客户电子邮件
	TDX_ID_CA_EDUCATION,		// 4238 学历
};


// 找回用户帐号 4306
const WORD tdxFETCHUSERACCOUNTFUNFieldReq[]=
{
	TDX_ID_CA_KHH,			// (800) 完整客户号
	TDX_ID_CA_TXMM,			// 新用户密码
	TDX_ID_CA_SJH,			// 手机号
	TDX_ID_CA_YZM,			// 手机动态码
};
const WORD tdxFETCHUSERACCOUNTFUNFieldAns[]=
{
	TDX_ID_CA_RESV,			// (825) 预留信息
};

// 积分查询
const WORD tdxQUERYSCOREFUNFieldReq[]=
{
	TDX_ID_CA_KHH,			// (800) 完整客户号
	TDX_ID_CA_QSRQ,			// (896) 起始查询时间
	TDX_ID_CA_ZZRQ,			// (897) 终止查询时间
	TDX_ID_CA_TRADETYPE,	// (4249)交易类型
};
const WORD tdxQUERYSCOREFUNFieldAns[]=
{
	TDX_ID_CA_TRADETIME,	// 交易时间
	TDX_ID_CA_TRADETYPE,	// 交易类型
	TDX_ID_CA_SCORE,		// 积分值
	TDX_ID_XT_REMARK,		// 备注
};

// 获取激活码 4312
const WORD tdxGETACTIVECODEFUNFieldReq[]=
{
	TDX_ID_CA_SJH,			// 手机号
	TDX_ID_CA_TXMM,			// 种子信息
	TDX_ID_CA_XTXMM,		// 手机OTPID
	TDX_ID_CA_RESV,			// 保留信息
};
const WORD tdxGETACTIVECODEFUNFieldAns[]=
{
	TDX_ID_CA_TOKEN,	// 激活码
	TDX_ID_CA_RESV,		// 备注
};

// 新版本安全功能( 4500 - 4600)

// 安全功能查询 4500
const WORD tdxQRYSCFUNCFUNFieldReq[]=
{
	TDX_ID_CA_KHH,				// (800) 完整客户号
	TDX_ID_CA_VER,				// (4226) 版本信息( 格式: 公司代码(通达信/核心/恒生);客户端类型(客户端/web/手机);版本号(V1.0);...扩展字段)
};
const WORD tdxQRYSCFUNCFUNFieldAns[]=
{// 按照多记录集返回
	TDX_ID_CA_AQJB,				// (806) 登录安全级别
	TDX_ID_CA_OTPSN,			// (4222) OTPSN序号 ( 当安全级别包含OTP时有效)
	TDX_ID_CA_CERTSN,			// (4219) 证书编号( 当安全级别中包含证书级别时有效)
	TDX_ID_CA_ZSQSRQ,			// (816) 级别生效日期
	TDX_ID_CA_ZSJZRQ,			// (817) 级别失效日期( 永久有效时填0)
	TDX_ID_CA_RESV,				// (825) 保留字段
};

// 开启/关闭安全功能 4502
const WORD tdxSWITCHSCFUNCFUNFieldReq[]=
{
	TDX_ID_CA_KHH,				// (800) 完整客户号
	TDX_ID_JYMM,				// (134) 交易密码
	TDX_ID_CA_AQJB,				// (806) 登录安全级别
	TDX_ID_CA_TXMM,				// (803) 认证信息( 根据安全级别, 为认证口令, OTP密码, 证书签名, 短信验证码等)(标准证书签名采用格式: 证书SN;签名原文;证书信息;签名信息;扩展, 不需要时字段填空)
	TDX_ID_CA_CZBZ,				// (824) 操作标志( 0-取消, 1-开通, 2-临时取消)
	TDX_ID_CA_ZSJZRQ,			// (817) 临时取消到期时间( 仅临时取消时有效 以到期日00:00计算)
	TDX_ID_CA_VER,				// (4226) 版本信息( 格式: 公司代码(通达信/核心/恒生);客户端类型(客户端/web/手机);版本号(V1.0);...扩展字段)
};
const WORD tdxSWITCHSCFUNCFUNFieldAns[]=
{
	TDX_ID_CA_RESV,				// (825) 保留字段
};

// 统一认证 4504
const WORD tdxUNIAUTHFUNFieldReq[]=
{
	TDX_ID_CA_KHH,				// (800) 完整客户号
	TDX_ID_ZHLB,				// (125) 帐号类别
	TDX_ID_XT_GTLB,				// (1234) 柜台类别(0:默认 1:信用交易 2:股票 3:基金 4:商品期货 5:金融期货 6:港股),原信用交易标识字段
	TDX_ID_JYMM,				// (134) 交易密码
	TDX_ID_CA_VER,				// (4226) 版本信息( 格式: 公司代码(通达信/核心/恒生);客户端类型(客户端/web/手机);版本号(V1.0);...扩展字段)

	TDX_ID_CA_KHMC,				// (801) 客户名称
	TDX_ID_CA_AQJB,				// (806) 登录安全级别
	TDX_ID_CA_TXMM,				// (803) 认证信息( 根据安全级别, 为认证口令, OTP密码, 证书签名, 短信验证码等)(标准证书签名采用格式: 证书SN;签名原文;证书信息;签名信息;扩展, 不需要时字段填空)
	TDX_ID_CA_ISVIPHOST,		// (837) VIP主站标识
	TDX_ID_CA_JQTZM,			// (4201) 机器特征码
};
const WORD tdxUNIAUTHFUNFieldAns[]=
{
	TDX_ID_CA_KJYBZ,			// (810) 可交易标志(0:不可交易,只可进行安全管理() 1:可正常交易)
	TDX_ID_CA_RESV,				// (825) 返回信息
};

// 申请认证口令 4506
const WORD tdxREQAPWDFUNFieldReq[]=
{
	TDX_ID_CA_KHH,				// (800) 完整客户号
	TDX_ID_JYMM,				// (134) 交易密码
	TDX_ID_CA_TXMM,				// (803) 认证口令
	TDX_ID_CA_VER,				// (4226) 版本信息( 格式: 公司代码(通达信/核心/恒生);客户端类型(客户端/web/手机);版本号(V1.0);...扩展字段)
};
const WORD tdxREQAPWDFUNFieldAns[]=
{
	TDX_ID_CA_RESV,				// (825) 保留字段
};

// 修改认证口令 4508
const WORD tdxMODAPWDFUNFieldReq[]=
{
	TDX_ID_CA_KHH,				// (800) 完整客户号
	TDX_ID_JYMM,				// (134) 交易密码
	TDX_ID_CA_TXMM,				// (803) 认证信息
	TDX_ID_CA_VER,				// (4226) 版本信息( 格式: 公司代码(通达信/核心/恒生);客户端类型(客户端/web/手机);版本号(V1.0);...扩展字段)
	
	TDX_ID_CA_XTXMM,			// (804) 新认证口令
};
const WORD tdxMODAPWDFUNFieldAns[]=
{
	TDX_ID_CA_RESV,				// (825) 保留字段
};

// 重置认证口令 4510
const WORD tdxRESETAPWDFUNFieldReq[]=
{
	TDX_ID_CA_KHH,				// (800) 完整客户号
	TDX_ID_JYMM,				// (134) 交易密码
	TDX_ID_CA_TXMM,				// (803) 认证信息( 辅助认证方式, 例如短信口令)
	TDX_ID_CA_VER,				// (4226) 版本信息( 格式: 公司代码(通达信/核心/恒生);客户端类型(客户端/web/手机);版本号(V1.0);...扩展字段)

	TDX_ID_CA_XTXMM,			// (804) 新认证口令
};
const WORD tdxRESETAPWDFUNFieldAns[]=
{
	TDX_ID_CA_RESV,				// (825) 保留字段
};

// 同步OTP 4512
const WORD tdxSYNOTPFUNFieldReq[]=
{
	TDX_ID_CA_KHH,				// (800) 完整客户号
	TDX_ID_JYMM,				// (134) 交易密码
	TDX_ID_CA_TXMM,				// (803) 校准信息( 格式:第一个动态口令;第二个动态口令)
	TDX_ID_CA_VER,				// (4226) 版本信息( 格式: 公司代码(通达信/核心/恒生);客户端类型(客户端/web/手机);版本号(V1.0);...扩展字段)
};
const WORD tdxSYNOTPFUNFieldAns[]=
{
	TDX_ID_CA_RESV,				// (825) 保留字段
};

// 获取证书签名码 4514
const WORD tdxGETCSIGNKEYFUNFieldReq[]=
{
	TDX_ID_CA_KHH,				// (800) 完整客户号
	TDX_ID_JYMM,				// (134) 交易密码
	TDX_ID_CA_VER,				// (4226) 版本信息( 格式: 公司代码(通达信/核心/恒生);客户端类型(客户端/web/手机);版本号(V1.0);...扩展字段)
};
const WORD tdxGETCSIGNKEYFUNFieldAns[]=
{
	TDX_ID_CA_YZM,				// (4225) 证书签名原文
	TDX_ID_CA_RESV,				// (825) 保留字段
};

// 更新证书 4516
const WORD tdxUPDCERTFUNFieldReq[]=
{
	TDX_ID_CA_KHH,				// (800) 完整客户号
	TDX_ID_JYMM,				// (134) 交易密码
	TDX_ID_CA_VER,				// (4226) 版本信息( 格式: 公司代码(通达信/核心/恒生);客户端类型(客户端/web/手机);版本号(V1.0);...扩展字段)

	TDX_ID_CA_SLOTSN,			// (4218) 装载证书容器SN
	TDX_ID_CA_CID,				// (4220) 三方安全机构ID(颁发/验证)
	TDX_ID_CA_CERTREQ,			// (4214) 证书更新请求
	TDX_ID_CA_USERCERDN,		// (4215) 证书DN
	TDX_ID_CA_ZSQSRQ,			// (816) 证书申请日期
	TDX_ID_CA_ZSJZRQ,			// (817) 证书到期日期
};
const WORD tdxUPDCERTFUNFieldAns[]=
{
	TDX_ID_CA_CERTSN,			// (4219) 证书编号
	TDX_ID_CA_CERTINFO,			// (4217) 证书内容
	TDX_ID_CA_RESV,				// (825) 保留字段
};

// 获取手机动态码 4518
const WORD tdxGETCCODEFUNFieldReq[]=
{
	TDX_ID_CA_KHH,				// (800) 完整客户号
	TDX_ID_JYMM,				// (134) 交易密码
	TDX_ID_CA_VER,				// (4226) 版本信息( 格式: 公司代码(通达信/核心/恒生);客户端类型(客户端/web/手机);版本号(V1.0);...扩展字段)
};
const WORD tdxGETCCODEFUNFieldAns[]=
{
	TDX_ID_CA_RESV,				// (825) 保留字段
};

// 授权计算机 4520
const WORD tdxPERMITMACHINEFUNFieldReq[]=
{
	TDX_ID_CA_KHH,				// (800) 完整客户号
	TDX_ID_JYMM,				// (134) 交易密码
	TDX_ID_CA_TXMM,				// (803) 认证信息( 根据安全级别, 为认证口令, OTP密码, 证书签名, 短信验证码等)(标准证书签名采用格式: 证书SN;签名原文;证书信息;签名信息;扩展, 不需要时字段填空)
	TDX_ID_CA_VER,				// (4226) 版本信息( 格式: 公司代码(通达信/核心/恒生);客户端类型(客户端/web/手机);版本号(V1.0);...扩展字段)
	
	TDX_ID_CA_MACHINENAME,		// (4204) 机器昵称
	TDX_ID_CA_JQTZM,			// (4201) 机器特征码
};
const WORD tdxPERMITMACHINEFUNFieldAns[]=
{
	TDX_ID_CA_RESV,				// (825) 保留字段
};

// 解除计算机授权 4522
const WORD tdxFREEMACHINEFUNFieldReq[]=
{
	TDX_ID_CA_KHH,				// (800) 完整客户号
	TDX_ID_JYMM,				// (134) 交易密码
	TDX_ID_CA_TXMM,				// (803) 认证信息( 根据安全级别, 为认证口令, OTP密码, 证书签名, 短信验证码等)(标准证书签名采用格式: 证书SN;签名原文;证书信息;签名信息;扩展, 不需要时字段填空)
	TDX_ID_CA_VER,				// (4226) 版本信息( 格式: 公司代码(通达信/核心/恒生);客户端类型(客户端/web/手机);版本号(V1.0);...扩展字段)
	
	TDX_ID_CA_MACHINENAME,		// (4204) 机器昵称
	TDX_ID_CA_CZBZ,				// (824) 操作标志( 0-解除, 1-恢复临时解除, 2-临时取消)
	TDX_ID_CA_ZSJZRQ,			// (817) 临时取消到期时间( 仅临时取消时有效 以到期日00:00计算)
};
const WORD tdxFREEMACHINEFUNFieldAns[]=
{
	TDX_ID_CA_RESV,				// (825) 保留字段
};

// 查询授权
const WORD tdxQRYPERMITIONFUNFieldReq[]=
{
	TDX_ID_CA_KHH,				// (800) 完整客户号
	TDX_ID_JYMM,				// (134) 交易密码
	TDX_ID_CA_TXMM,				// (803) 认证信息( 根据安全级别, 为认证口令, OTP密码, 证书签名, 短信验证码等)(标准证书签名采用格式: 证书SN;签名原文;证书信息;签名信息;扩展, 不需要时字段填空)
	TDX_ID_CA_VER,				// (4226) 版本信息( 格式: 公司代码(通达信/核心/恒生);客户端类型(客户端/web/手机);版本号(V1.0);...扩展字段)
};
const WORD tdxQRYPERMITIONFUNFieldAns[]=
{
	TDX_ID_CA_SID,			// (4501) 序号
	TDX_ID_CA_BINDTINE,		// (4502) 绑定时间
	TDX_ID_CA_UMAC,			// (4503) MAC地址
	TDX_ID_CA_REMARK,		// (4504) 计算机备注
	TDX_ID_CA_HARDINFO,		// (4505) 机器特征信息
};
// const WORD tdxQRYPERMITIONFUNFieldAns[]=
// {
// 	TDX_ID_CA_MACHINENAME,		// (4204) 机器昵称
// 	TDX_ID_CA_JQTZM,			// (4201) 机器特征码
// 	TDX_ID_CA_ZSQSRQ,			// (816) 绑定时间
// 	TDX_ID_CA_ZSJZRQ,			// (817) 临时取消到期时间( 仅临时取消时有效 以到期日00:00计算)
// 	TDX_ID_CA_VER,				// (4226) 版本信息( 格式: 公司代码(通达信/核心/恒生)客户端类型(客户端/web/手机)版本号(V1.0) 例如:通达信客户端V6.01)
// 	TDX_ID_CA_RESV,				// (825) 保留字段
// };

// 更新预留信息 4526
const WORD tdxUPDSELFINFOFUNFieldReq[]=
{
	TDX_ID_CA_KHH,				// (800) 完整客户号
	TDX_ID_JYMM,				// (134) 交易密码
	TDX_ID_CA_TXMM,				// (803) 认证信息( 根据安全级别, 为认证口令, OTP密码, 证书签名, 短信验证码等)(标准证书签名采用格式: 证书SN;签名原文;证书信息;签名信息;扩展, 不需要时字段填空)
	TDX_ID_CA_VER,				// (4226) 版本信息( 格式: 公司代码(通达信/核心/恒生);客户端类型(客户端/web/手机);版本号(V1.0);...扩展字段)
	
	TDX_ID_CA_RESV,				// (825) 预留信息
};
const WORD tdxUPDSELFINFOFUNFieldAns[]=
{
	TDX_ID_CA_RESV,				// (825) 保留字段
};

// 查询用户常用信息 4528
const WORD tdxQRYUSERCOMMONFUNFieldReq[]=
{
	TDX_ID_CA_KHH,				// (800) 完整客户号
	TDX_ID_JYMM,				// (134) 交易密码
	TDX_ID_CA_TXMM,				// (803) 认证信息( 根据安全级别, 为认证口令, OTP密码, 证书签名, 短信验证码等)(标准证书签名采用格式: 证书SN;签名原文;证书信息;签名信息;扩展, 不需要时字段填空)
	TDX_ID_CA_VER,				// (4226) 版本信息( 格式: 公司代码(通达信/核心/恒生);客户端类型(客户端/web/手机);版本号(V1.0);...扩展字段)
};
const WORD tdxQRYUSERCOMMONFUNFieldAns[]=
{
	TDX_ID_CA_DLSJ,				// (898) 上次登陆时间 (格式:(YYYY/MM/DD HH:MI:SS))
	TDX_ID_CA_LASTIP,			// (890) 上次登录地址
	TDX_ID_CA_MAC,				// (4211) 上次登录MAC地址
	TDX_ID_CA_VER,				// (4226) 上次登录版本信息( 格式: 公司代码(通达信/核心/恒生)客户端类型(客户端/web/手机)版本号(V1.0) 例如:通达信客户端V6.01)
	TDX_ID_CA_CSCS,				// (4207) 总登陆次数
	TDX_ID_CA_RESV,				// (825) 预留信息
};

// 用户资料查询 4530
const WORD tdxQRYUDATAFUNFieldReq[]=
{
	TDX_ID_CA_KHH,				// (800) 完整客户号
	TDX_ID_JYMM,				// (134) 交易密码
	TDX_ID_CA_TXMM,				// (803) 认证信息( 根据安全级别, 为认证口令, OTP密码, 证书签名, 短信验证码等)(标准证书签名采用格式: 证书SN;签名原文;证书信息;签名信息;扩展, 不需要时字段填空)
	TDX_ID_CA_VER,				// (4226) 版本信息( 格式: 公司代码(通达信/核心/恒生);客户端类型(客户端/web/手机);版本号(V1.0);...扩展字段)
};
const WORD tdxQRYUDATAFUNFieldAns[]=
{
	TDX_ID_CA_SJH,				// (860) 客户手机号
	TDX_ID_CA_ZJHM,				// (861) 客户证件号码
	TDX_ID_CA_RESV,				// (825) 保留字段
};

// 更新用户资料 4532
const WORD tdxUPDUDATAFUNFieldReq[]=
{
	TDX_ID_CA_KHH,				// (800) 完整客户号
	TDX_ID_JYMM,				// (134) 交易密码
	TDX_ID_CA_TXMM,				// (803) 认证信息( 根据安全级别, 为认证口令, OTP密码, 证书签名, 短信验证码等)(标准证书签名采用格式: 证书SN;签名原文;证书信息;签名信息;扩展, 不需要时字段填空)
	TDX_ID_CA_VER,				// (4226) 版本信息( 格式: 公司代码(通达信/核心/恒生);客户端类型(客户端/web/手机);版本号(V1.0);...扩展字段)

	TDX_ID_CA_SJH,				// (860) 客户手机号
	TDX_ID_CA_ZJHM				// (861) 客户证件号码
};
const WORD tdxUPDUDATAFUNFieldAns[]=
{
	TDX_ID_CA_RESV,				// (825) 保留字段
};

// 关键操作查询 4534
const WORD tdxQRYIMPOTOPFUNFieldReq[]=
{
	TDX_ID_CA_KHH,				// (800) 完整客户号
	TDX_ID_JYMM,				// (134) 交易密码
	TDX_ID_CA_TXMM,				// (803) 认证信息( 根据安全级别, 为认证口令, OTP密码, 证书签名, 短信验证码等)(标准证书签名采用格式: 证书SN;签名原文;证书信息;签名信息;扩展, 不需要时字段填空)
	TDX_ID_CA_VER,				// (4226) 版本信息( 格式: 公司代码(通达信/核心/恒生);客户端类型(客户端/web/手机);版本号(V1.0);...扩展字段)
};
const WORD tdxQRYIMPOTOPFUNFieldAns[]=
{
	TDX_ID_CA_CZBZ,				// (824) 操作标志(为功能号或者其他)
	TDX_ID_CA_RESV,				// (825) 操作说明
};

// 关键操作记录 4536
const WORD tdxRCDIMPOTOPFUNFieldReq[]=
{
	TDX_ID_CA_KHH,				// (800) 完整客户号
	TDX_ID_JYMM,				// (134) 交易密码
	TDX_ID_CA_TXMM,				// (803) 认证信息( 根据安全级别, 为认证口令, OTP密码, 证书签名, 短信验证码等)(标准证书签名采用格式: 证书SN;签名原文;证书信息;签名信息;扩展, 不需要时字段填空)
	TDX_ID_CA_VER,				// (4226) 版本信息( 格式: 公司代码(通达信/核心/恒生);客户端类型(客户端/web/手机);版本号(V1.0);...扩展字段)

	TDX_ID_CA_CZBZ,				// (824) 操作标志(可以为功能号, 或者其他)
	TDX_ID_CA_RESV,				// (825) 操作说明
};
const WORD tdxRCDIMPOTOPFUNFieldAns[]=
{
	TDX_ID_CA_RESV,				// (825) 保留字段
};

// 认证历史查询 4538
const WORD tdxQRYAUTHHISFUNFieldReq[]=
{
	TDX_ID_CA_KHH,				// (800) 完整客户号
	TDX_ID_JYMM,				// (134) 交易密码
	TDX_ID_CA_TXMM,				// (803) 认证信息( 根据安全级别, 为认证口令, OTP密码, 证书签名, 短信验证码等)(标准证书签名采用格式: 证书SN;签名原文;证书信息;签名信息;扩展, 不需要时字段填空)
	TDX_ID_CA_VER,				// (4226) 版本信息( 格式: 公司代码(通达信/核心/恒生);客户端类型(客户端/web/手机);版本号(V1.0);...扩展字段)

	TDX_ID_CA_QSRQ,				// (896) 起始查询时间
 	TDX_ID_CA_ZZRQ,				// (897) 终止查询时间
};
const WORD tdxQRYAUTHHISFUNFieldAns[]=
{
	TDX_ID_CA_DLSJ,				// (898) 上次登陆时间 (格式:(YYYY/MM/DD HH:MI:SS))
	TDX_ID_CA_AQJB,				// (806) 安全级别
	TDX_ID_CA_LASTIP,			// (890) 登陆IP
	TDX_ID_CA_MAC,				// (4211) 机器MAC地址
	TDX_ID_CA_JQTZM,			// (4201) 机器特征码
	TDX_ID_CA_VER,				// (4226) 版本信息( 格式: 公司代码(通达信/核心/恒生);客户端类型(客户端/web/手机);版本号(V1.0);...扩展字段)
	TDX_ID_CA_RESV,				// (825) 认证结果
};

// 密码保护问题申请 4540
const WORD tdxREQQAPROTFUNFieldReq[]=
{
	TDX_ID_CA_KHH,				// (800) 完整客户号
	TDX_ID_JYMM,				// (134) 交易密码
	TDX_ID_CA_TXMM,				// (803) 认证信息( 根据安全级别, 为认证口令, OTP密码, 证书签名, 短信验证码等)(标准证书签名采用格式: 证书SN;签名原文;证书信息;签名信息;扩展, 不需要时字段填空)
	TDX_ID_CA_VER,				// (4226) 版本信息( 格式: 公司代码(通达信/核心/恒生);客户端类型(客户端/web/手机);版本号(V1.0);...扩展字段)
	// 暂不支持
};
const WORD tdxREQQAPROTFUNFieldAns[]=
{
	TDX_ID_CA_RESV,				// (825) 保留字段
};

// 密码保护问题修改 4542
const WORD tdxMODQAPROTFUNFieldReq[]=
{
	TDX_ID_CA_KHH,				// (800) 完整客户号
	TDX_ID_JYMM,				// (134) 交易密码
	TDX_ID_CA_TXMM,				// (803) 认证信息( 根据安全级别, 为认证口令, OTP密码, 证书签名, 短信验证码等)(标准证书签名采用格式: 证书SN;签名原文;证书信息;签名信息;扩展, 不需要时字段填空)
	TDX_ID_CA_VER,				// (4226) 版本信息( 格式: 公司代码(通达信/核心/恒生);客户端类型(客户端/web/手机);版本号(V1.0);...扩展字段)
	// 暂不支持
};
const WORD tdxMODQAPROTFUNFieldAns[]=
{
	TDX_ID_CA_RESV,				// (825) 保留字段
};

// 密码保护校验 4544
const WORD tdxAUTHQAPROTFUNFieldReq[]=
{
	TDX_ID_CA_KHH,				// (800) 完整客户号
	TDX_ID_JYMM,				// (134) 交易密码
	TDX_ID_CA_TXMM,				// (803) 认证信息( 根据安全级别, 为认证口令, OTP密码, 证书签名, 短信验证码等)(标准证书签名采用格式: 证书SN;签名原文;证书信息;签名信息;扩展, 不需要时字段填空)
	TDX_ID_CA_VER,				// (4226) 版本信息( 格式: 公司代码(通达信/核心/恒生);客户端类型(客户端/web/手机);版本号(V1.0);...扩展字段)
	// 暂不支持
};
const WORD tdxAUTHQAPROTFUNFieldAns[]=
{
	TDX_ID_CA_RESV,				// (825) 保留字段
};

// 应急密码 4546
const WORD tdxRESVPWDFUNFieldReq[]=
{
	TDX_ID_CA_KHH,				// (800) 完整客户号
	TDX_ID_JYMM,				// (134) 交易密码
	TDX_ID_CA_TXMM,				// (803) 认证信息( 根据安全级别, 为认证口令, OTP密码, 证书签名, 短信验证码等)(标准证书签名采用格式: 证书SN;签名原文;证书信息;签名信息;扩展, 不需要时字段填空)
	TDX_ID_CA_VER,				// (4226) 版本信息( 格式: 公司代码(通达信/核心/恒生);客户端类型(客户端/web/手机);版本号(V1.0);...扩展字段)
	// 暂不支持
};
const WORD tdxRESVPWDFUNFieldAns[]=
{
	TDX_ID_CA_RESV,				// (825) 保留字段
};

const WORD tdxCONSISFUNFieldReq[]=
{
	TDX_ID_CA_KHH,				// (800) 完整客户号
	TDX_ID_JYMM,				// (134) 交易密码
	TDX_ID_CA_GD_HARDINFO,		// (4244) 计算机特征码信息
};
const WORD tdxCONSISFUNFieldAns[]=
{
	TDX_ID_CA_REMARK,			// (4504) 计算机签名信息
	TDX_ID_CA_RESV,				// (825) 保留字段
};


// 新版本安全功能( 4500 - 4600)

//////////////////////////////////////////////////////////////////////////
//	模拟交易相关
//////////////////////////////////////////////////////////////////////////

// 收益率排名 5000
const WORD tdxSYLPMFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_STARTPOS,			// 查询开始位置
};

// 帐户融券 5002 (N/A)
const WORD tdxZHRQFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式
};

// 融券查询 5004 (N/A)
const WORD tdxRQCXFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式
};

// 帐户还券展期 5006 (N/A)
const WORD tdxZHHQZQFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式
};

// 交易中心监控 5008
const WORD tdxTCMONITORFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_INPUTPARAM,		// 输入参数
};

// TS路由 5010
const WORD tdxTSROUTINGFieldReq[]=
{
	TDX_ID_KHH,					// 客户号
	TDX_ID_JYMM,				// 交易密码
	TDX_ID_ZJZH,				// 资金帐号(支持多资金帐号时送,否则送空)
	TDX_ID_ZHLB,				// (保留)帐号类别
	TDX_ID_GDDM,				// (保留)股东代码
	TDX_ID_OP_WTFS,				// 委托方式

	TDX_ID_XT_FUNCNO,			// 功能编号(过程名称)
	TDX_ID_XT_MODE,				// 模式(入参格式类型)
	TDX_ID_XT_PARAM,			// 参数(入参序列)
	TDX_ID_XT_REMARK,			// 备注(路由信息)
	TDX_ID_XT_DESCRIPTION,		// 描述(调用说明,自行使用)
};

const WORD tdxTSROUTINGFieldAns[]=
{
	TDX_ID_XT_FUNCNO,			// 功能编号(过程名称)
	TDX_ID_XT_MODE,				// 模式(出参格式类型)
	TDX_ID_XT_PARAM,			// 参数(出参序列)
	TDX_ID_XT_REMARK,			// 备注(路由信息)
	TDX_ID_XT_DESCRIPTION,		// 描述(应答说明,自行使用)
	TDX_ID_XT_ERRCODE,			// 错误代码(业务错误代码)
	TDX_ID_XT_ERRMSG,			// 错误信息(业务错误信息)

	TDX_ID_XT_RESERVED,			// 调试信息
};


//---------------------------------------------------------------------------
// Part.V 结构-字段定义
//---------------------------------------------------------------------------

// 简单字典定义
BEGIN_STRUCT_FIELD_DEF(tdxSimpleStructFieldInfo)
	// 账号预处理 94
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZHYCL,tdxZHYCLFieldReq)
	// 登录预处理 96
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_DLYCL,tdxDLYCLFieldReq)
	// 集成客户校验 98|99
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_JCKHJY,tdxJCKHJYFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_JCKHJY,tdxJCKHJYFieldAns)
	// 客户校验 100
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KHJY,tdxKHJYFieldReq)
END_STRUCT_FIELD_DEF(tdxSimpleStructFieldInfo)

// 完整字典定义
BEGIN_STRUCT_FIELD_DEF(tdxCommonStructFieldInfo)
	// 客户校验 100
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KHJY,tdxKHJYFieldReq)
	// 行情查询 102
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CXHQ,tdxCXHQFieldReq)
	// 资金余额 104
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZJYE,tdxZJYEFieldReq)
	// 修改密码 106
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XGMM,tdxXGMMFieldReq)
	// 修改资金密码 108
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XGZJMM,tdxXGZJMMFieldReq)
	// 计算可买(卖)数 110
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_JSKMS,tdxJSKMSFieldReq)
	// 取缓存信息 112
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CACHE,tdxCACHEFieldReq)
	// 修改关联资金帐号 114
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XGGLZJZH,tdxXGGLZJZHFieldReq)
	// 客户注销 116
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KHZX,tdxKHZXFieldReq)
	// 订阅取消对帐单(邮寄) 118
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_DYQXDZD,tdxDYQXDZDFieldReq)
	// 委托冻结资金 120
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_WTDJZJ,tdxWTDJZJFieldReq)
	// 打印对帐单 122
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_PRINTDZD,tdxPRINTDZDFieldReq)
	// 打印汇总对帐单 124
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_PRINTHZDZD,tdxPRINTHZDZDFieldReq)
	// 打印交割单 126
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_PRINTJGD,tdxPRINTJGDFieldReq)
	// 修改认证口令 128
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XGTXMM,tdxXGTXMMFieldReq)
	// 帐号解冻 130
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZHJD,tdxZHJDFieldReq)
	// 资金归集 132
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZJGJ,tdxZJGJFieldReq)
	// 资金帐号间转帐 134
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZJZHJZZ,tdxZJZHJZZFieldReq)
	// 提交问卷结果 136
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_TJWJJG,tdxTJWJJGFieldReq)
	// 获取问卷内容 138
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HQWJNR,tdxHQWJNRFieldReq)
	// 获取帐号状态标志 140
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HQZHZTBZ,tdxHQZHZTBZFieldReq)
	// 处理查询密码 142
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CLCXMM,tdxCLCXMMFieldReq)
	// 推送注册 144
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_TSZC,tdxTSZCFieldReq)
	// 推送注销 146
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_TSZX,tdxTSZXFieldReq)
	// 子帐号查询 148
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZZHCX,tdxZZHCXFieldReq)
	// 处理认证信息 150
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CLRZXX,tdxCLRZXXFieldReq)
	// 认证信息查询 152
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_RZXXCX,tdxRZXXCXFieldReq)
	// 客户基本信息查询 154
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KHJBXXCX,tdxKHJBXXCXFieldReq)
	// 电子合同签约 156
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_DZHTQY,tdxDZHTQYFieldReq)
	// 电子合同签约查询 158
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_DZHTQYCX,tdxDZHTQYCXFieldReq)
	// 电子合同列表查询 160
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_DZHTLBCX,tdxDZHTLBCXFieldReq)
	// 电子合同信息查询 162
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_DZHTXXCX,tdxDZHTXXCXFieldReq)
	// 认证流水查询 164
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_RZLSCX,tdxRZLSCXFieldReq)
	// 客户预留信息查询 166
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KHYLXXCX,tdxKHYLXXCXFieldReq)
	// 客户预留信息修改 168
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KHYLXXXG,tdxKHYLXXXGFieldReq)
	// 客户操作确认 170
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KHCZQR,tdxKHCZQRFieldReq)
	// 翻译字典查询 172
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FYZDCX,tdxFYZDCXFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_FYZDCX,tdxFYZDCXFieldAns)
	// 更新会话信息 174
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_UPDATESESSION,tdxUPDATESESSIONFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_UPDATESESSION,tdxUPDATESESSIONFieldAns)
	// 问卷流水查询 176
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_WJLSCX,tdxWJLSCXFieldReq)
	// 获取市场信息 178
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_SCINFO,tdxSCINFOFieldReq)

	// 委托撤单 200
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_WTCD,tdxWTCDFieldReq)
	// 普通股票委托 202
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_PTGPWT,tdxPTGPWTFieldReq)
	// 债券转股回售 204
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZQZGHS,tdxZQZGHSFieldReq)
	// 修改订单 206
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XGDD,tdxXGDDFieldReq)
	// 申购新股 208
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_SGXG,tdxSGXGFieldReq)
	// 新股申购修改 210
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XGSGXG,tdxXGSGXGFieldReq)
	// 新股申购撤单 212
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XGSGCD,tdxXGSGCDFieldReq)
	// 批量委托 214
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_PLWT,tdxPLWTFieldReq)
	// 批量撤单 216
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_PLCD,tdxPLCDFieldReq)
	// 新增订单检查 218
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XZDDJC,tdxXZDDJCFieldReq)
	// 修改订单检查 220
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XGDDJC,tdxXGDDJCFieldReq)

	// 闪电手资金查询 250
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_SDSZJCX,tdxSDSZJCXFieldReq)
	// 闪电手股份查询 252
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_SDSGFCX,tdxSDSGFCXFieldReq)
	// 闪电手委托查询 254
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_SDSWTCX,tdxSDSWTCXFieldReq)
	// 闪电手成交查询 256
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_SDSCJCX,tdxSDSCJCXFieldReq)
	// 闪电手流水查询 258
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_SDSLSCX,tdxSDSLSCXFieldReq)
	// 闪电手信用资产查询 260
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_SDSXYZCCX,tdxSDSXYZCCXFieldReq)
	// 闪电手证券信息查询 262
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_SDSZQXXCX,tdxSDSZQXXCXFieldReq)
	// 闪电手可买(卖)数量查询 264
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_SDSKMSLCX,tdxSDSKMSLCXFieldReq)

	// 放弃中签 300
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FQZQ,tdxFQZQFieldReq)
	// (服务)客户资料查询 302
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_KHZLCX,tdxFWKHZLCXFieldReq)
	// (服务)获取动态口令 304
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_HQDTKL,tdxFWHQDTKLFieldReq)
	// (服务)产品定购品种 306
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_CPDGPZ,tdxFWCPDGPZFieldReq)
	// (服务)产品定购查询 308
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_CPDGCX,tdxFWCPDGCXFieldReq)
	// (服务)产品定购设置 310
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_CPDGSZ,tdxFWCPDGSZFieldReq)
	// (服务)产品定购修改 312
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_CPDGXG,tdxFWCPDGXGFieldReq)
	// (服务)产品定购取消 314
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_CPDGQX,tdxFWCPDGQXFieldReq)
	// (服务)资金流水 316
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_ZJLS,tdxFWZJLSFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_FW_ZJLS,tdxFWZJLSFieldAns)
	// (服务)批量行情查询 318
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_PLHQCX,tdxFWPLHQCXFieldReq)
	// (服务)资讯栏目查询 320
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_ZXLMCX,tdxFWZXLMCXFieldReq)
	// (服务)获取提示信息 322
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_HQTSXX,tdxFWHQTSXXFieldReq)
	// (服务)投票方案查询 324
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_TPFACX,tdxFWTPFACXFieldReq)
	// (服务)投票信息查询 326
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_TPXXCX,tdxFWTPXXCXFieldReq)
	// (服务)投票结果提交 328
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_TPJGTJ,tdxFWTPJGTJFieldReq)
	// (服务)投票结果查询 330
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_TPJGCX,tdxFWTPJGCXFieldReq)
	// (服务)投票统计查询 332
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_TPTJCX,tdxFWTPTJCXFieldReq)
	// (服务)套利组合代码查询 334
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_TLZHDMCX,tdxFWTLZHDMCXFieldReq)
	// (服务)套利组合成分查询 336
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_TLZHCFCX,tdxFWTLZHCFCXFieldReq)
	// (服务)单点登录操作 338
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_DDDLCZ,tdxFWDDDLCZFieldReq)
	// (服务)批量现价查询 340
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_PLXJCX,tdxFWPLXJCXFieldReq)
	// (服务)信息订阅 342
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_XXDY,tdxFWXXDYFieldReq)
	// (服务)客户卡处理 344
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_KHKCL,tdxFWKHKCLFieldReq)
	// (服务)上传配置信息 346
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_SCPZXX,tdxFWSCPZXXFieldReq)
	// (服务)下载配置信息 348
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_XZPZXX,tdxFWXZPZXXFieldReq)
	// (服务)配置信息摘要查询 350
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_PZXXZYCX,tdxFWPZXXZYCXFieldReq)
	// (服务)处理客户参数 352
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_CLKHCS,tdxFWCLKHCSFieldReq)
	// (服务)配对列表查询 354
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_PDLBCX,tdxFWPDLBCXFieldReq)
	// (服务)配对流水录入 356
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_PDLSLR,tdxFWPDLSLRFieldReq)
	// (服务)配对流水查询 358
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_PDLSCX,tdxFWPDLSCXFieldReq)
	// (服务)增值业务收费 360
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_ZZYWSF,tdxFWZZYWSFFieldReq)

	// (推送)强制退出 400 [推送功能,请求不使用]
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_PUSH_QZTC,tdxQZTCFieldReq)
	// (推送)消息通知 402 [推送功能,请求不使用]
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_PUSH_XXTZ,tdxXXTZFieldReq)
	// (推送)公告消息 404 [推送功能,请求不使用]
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_PUSH_GGXX,tdxGGXXFieldReq)

	// (手机)证券查询 500
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_ZQCX,tdxMOBILEZQCXFieldReq)
	// (手机)股份查询 502
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_GFCX,tdxMOBILEGFCXFieldReq)
	// (手机)资金查询 504
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_ZJCX,tdxMOBILEZJCXFieldReq)
	// (手机)撤单查询 506
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_CDCX,tdxMOBILECDCXFieldReq)
	// (手机)委托查询 508
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_WTCX,tdxMOBILEWTCXFieldReq)
	// (手机)成交查询 510
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_CJCX,tdxMOBILECJCXFieldReq)
	// (手机)转账查询 512
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_ZZCX,tdxMOBILEZZCXFieldReq)
	// (手机)流水查询 514
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_LSCX,tdxMOBILELSCXFieldReq)
	// (手机)交割查询 516
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_JGCX,tdxMOBILEJGCXFieldReq)
	// (手机)对账查询 518
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_DZCX,tdxMOBILEDZCXFieldReq)
	// (手机)意向申报行情查询 520
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_YXSBHQCX,tdxMOBILEYXSBHQCXFieldReq)
	// (手机)历史委托查询 522
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_LSWTCX,tdxMOBILELSWTCXFieldReq)
	// (手机)历史成交查询 524
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_LSCJCX,tdxMOBILELSCJCXFieldReq)
	// (手机)配号中签查询 526
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_PHZQCX,tdxMOBILEPHZQCXFieldReq)
	// (手机)认证流水查询 528
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_RZLSCX,tdxMOBILERZLSCXFieldReq)
	// (手机)基金撤单查询 530
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_JJCDCX,tdxMOBILEJJCDCXFieldReq)
	// (手机)基金当日委托查询 532
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_JJDRWTCX,tdxMOBILEJJDRWTCXFieldReq)
	// (手机)基金历史委托查询 534
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_JJLSWTCX,tdxMOBILEJJLSWTCXFieldReq)
	// (手机)基金当日成交查询 536
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_JJDRCJCX,tdxMOBILEJJDRCJCXFieldReq)
	// (手机)基金历史成交查询 538
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_JJLSCJCX,tdxMOBILEJJLSCJCXFieldReq)
	// (手机)基金账号查询 540
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_JJZHCX,tdxMOBILEJJZHCXFieldReq)
	// (手机)基金公司查询 542
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_JJGSCX,tdxMOBILEJJGSCXFieldReq)
	// (手机)基金代码查询 544
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_JJDMCX,tdxMOBILEJJDMCXFieldReq)
	// (手机)基金份额查询 546
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_JJFECX,tdxMOBILEJJFECXFieldReq)
	// (手机)基金对账查询 548
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_JJDZCX,tdxMOBILEJJDZCXFieldReq)
	// (手机)基金交割查询 550
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_JJJGCX,tdxMOBILEJJJGCXFieldReq)
	// (手机)基金非交易委托查询 552
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_JJFJYWTCX,tdxMOBILEJJFJYWTCXFieldReq)
	// (手机)期货合约查询 560
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_QHHYCX,tdxMOBILEQHHYCXFieldReq)
	// (手机)期货组合合约查询 562
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_QHZHHYCX,tdxMOBILEQHZHHYCXFieldReq)
	// (手机)期货组合持仓查询 564
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_QHZHCCCX,tdxMOBILEQHZHCCCXFieldReq)
	// (手机)期货组合委托查询 566
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_QHZHWTCX,tdxMOBILEQHZHWTCXFieldReq)
	// (手机)期货组合策略查询 568
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_QHZHCLCX,tdxMOBILEQHZHCLCXFieldReq)
	// (手机)股份汇总查询 570
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_GFHZCX,tdxMOBILEGFHZCXFieldReq)
	// (手机)委托汇总查询 572
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_WTHZCX,tdxMOBILEWTHZCXFieldReq)
	// (手机)成交汇总查询 574
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_CJHZCX,tdxMOBILECJHZCXFieldReq)
	// (手机)成交明细查询 576
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_CJMXCX,tdxMOBILECJMXCXFieldReq)

	// (手机)信用融资买入配套查询 600
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_XYRZMRPTCX,tdxMOBILEXYRZMRPTCXFieldReq)
	// (手机)信用融券卖出配套查询 602
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_XYRQMCPTCX,tdxMOBILEXYRQMCPTCXFieldReq)
	// (手机)信用卖出还款配套查询 604
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_XYMCHKPTCX,tdxMOBILEXYMCHKPTCXFieldReq)
	// (手机)信用买入还券配套查询 606
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_XYMRHQPTCX,tdxMOBILEXYMRHQPTCXFieldReq)
	// (手机)信用现金还款配套查询 608
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_XYXJHKPTCX,tdxMOBILEXYXJHKPTCXFieldReq)
	// (手机)信用现券还券配套查询 610
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_XYXQHQPTCX,tdxMOBILEXYXQHQPTCXFieldReq)
	// (手机)信用余券划转配套查询 612
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_XYYQHZPTCX,tdxMOBILEXYYQHZPTCXFieldReq)
	// (手机)信用担保划转配套查询 614
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_XYDBHZPTCX,tdxMOBILEXYDBHZPTCXFieldReq)
	// (手机)信用担保转入配套查询 616
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_XYDBZRPTCX,tdxMOBILEXYDBZRPTCXFieldReq)
	// (手机)信用担保转出配套查询 618
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_XYDBZCPTCX,tdxMOBILEXYDBZCPTCXFieldReq)
	// (手机)信用资产信息查询 620
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_XYZCXXCX,tdxMOBILEXYZCXXCXFieldReq)
	// (手机)信用股份信息查询 622
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_XYGFXXCX,tdxMOBILEXYGFXXCXFieldReq)
	// (手机)信用标的证券查询 624
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_XYBDZQCX,tdxMOBILEXYBDZQCXFieldReq)
	// (手机)信用直接划转查询 626
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_XYZJHZCX,tdxMOBILEXYZJHZCXFieldReq)
	// (手机)信用利息费用查询 628
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_XYLXFYCX,tdxMOBILEXYLXFYCXFieldReq)
	// (手机)信用未平合约查询 630
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_XYWPHYCX,tdxMOBILEXYWPHYCXFieldReq)
	// (手机)信用已平合约查询 632
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_XYYPHYCX,tdxMOBILEXYYPHYCXFieldReq)
	// (手机)信用当日合约查询 634
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_XYDRHYCX,tdxMOBILEXYDRHYCXFieldReq)
	// (手机)信用融资合约查询 636
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_XYRZHYCX,tdxMOBILEXYRZHYCXFieldReq)
	// (手机)信用融券合约查询 638
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_XYRQHYCX,tdxMOBILEXYRQHYCXFieldReq)
	// (手机)信用资金负债查询 640
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_XYZJFZCX,tdxMOBILEXYZJFZCXFieldReq)
	// (手机)信用股份负债查询 642
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_XYGFFZCX,tdxMOBILEXYGFFZCXFieldReq)
	// (手机)信用交易担保品证券查询 644
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_XYJYDBPZQCX,tdxMOBILEXYJYDBPZQCXFieldReq)
	// (手机)信用交易非交易化转查询 646
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_XYJYFJYHZCX,tdxMOBILEXYJYFJYHZCXFieldReq)
	// (手机)信用交易负债流水查询 648
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_XYJYFZLSCX,tdxMOBILEXYJYFZLSCXFieldReq)
	
	// (手机)ETF委托查询 700
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_ETFWTCX,tdxMOBILEETFWTCXFieldReq)
	// (手机)ETF成交查询 702
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_ETFCJCX,tdxMOBILEETFCJCXFieldReq)

	// (手机)理财产品份额查询 750
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_LCCPFECX,tdxMOBILELCCPFECXFieldReq)
	// (手机)理财产品委托查询 752
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_LCCPWTCX,tdxMOBILELCCPWTCXFieldReq)
	// (手机)理财产品成交查询 754
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_LCCPCJCX,tdxMOBILELCCPCJCXFieldReq)
	// (手机)理财产品代码查询 756
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_LCCPDMCX,tdxMOBILELCCPDMCXFieldReq)
	// (手机)理财产品定期定额申购查询 758
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_LCCPDQDESGCX,tdxMOBILELCCPDQDESGCXFieldReq)
	// (手机)银行理财产品代码查询 790
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_YHLCCPDMCX,tdxMOBILEYHLCCPDMCXFieldReq)
	// (手机)银行理财产品份额查询 792
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_YHLCCPFECX,tdxMOBILEYHLCCPFECXFieldReq)
	// (手机)银行理财产品委托查询 794
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_YHLCCPWTCX,tdxMOBILEYHLCCPWTCXFieldReq)
	// (手机)银行理财产品成交查询 796
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_YHLCCPCJCX,tdxMOBILEYHLCCPCJCXFieldReq)

	// 银证转帐 900
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YZZZ,tdxYZZZFieldReq)
	// 银行流水 902
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YHLS,tdxYHLSFieldReq)
	// 银行余额 904
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YHYE,tdxYHYEFieldReq)
	// 修改银行密码 906
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XGYHMM,tdxXGYHMMFieldReq)
	// 银行信息 908
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YHXX,tdxYHXXFieldReq)
	
	// 三方存管转帐 910
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_SFCGZZ,tdxSFCGZZFieldReq)
	// 三方转帐查询 912
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_SFZZCX,tdxSFZZCXFieldReq)
	// 三方余额查询 914
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_SFYECX,tdxSFYECXFieldReq)

	// 转帐修改 916
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZZXG,tdxZZXGFieldReq)
	// 转帐取消 918
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZZQX,tdxZZQXFieldReq)
	// 可取资金查询 920
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KQZJCX,tdxKQZJCXFieldReq)
	// 转帐银行查询 922
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZZYHCX,tdxZZYHCXFieldReq)
	// 银行账户间转帐 924
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YHZHJZZ,tdxYHZHJZZFieldReq)
	// 远端资金转账 926
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YDZJZZ,tdxYDZJZZFieldReq)
	// 远端转账查询 928
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YDZZCX,tdxYDZZCXFieldReq)
	// 远端资金查询 930
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YDZJCX,tdxYDZJCXFieldReq)
	// 远端可转查询 932
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YDKZCX,tdxYDKZCXFieldReq)
	// 银行卡列表查询 934
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YHKLBCX,tdxYHKLBCXFieldReq)
	// 银行卡信息查询 936
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YHKXXCX,tdxYHKXXCXFieldReq)
	// 银行卡信息修改 938
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YHKXXXG,tdxYHKXXXGFieldReq)
	// 银行卡变更操作 940
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YHKBGCZ,tdxYHKBGCZFieldReq)
	// 银行卡费率查询 942
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YHKFLCX,tdxYHKFLCXFieldReq)
	// 账号间转账流水查询 944
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZHJZZLSCX,tdxZHJZZLSCXFieldReq)
	// 账号间转账当日流水查询 946
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZHJZZDRLSCX,tdxZHJZZDRLSCXFieldReq)
	// 银行余额流水查询 948
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YHYELSCX,tdxYHYELSCXFieldReq)
	// 计划转账流水查询 950
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_JHZZLSCX,tdxJHZZLSCXFieldReq)
	// 多存管银行流水查询 952
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_DCGYHLSCX,tdxDCGYHLSCXFieldReq)
	// 多存管账号同步 954
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_DCGZHTB,tdxDCGZHTBFieldReq)
	// 换汇业务操作 990
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HHYWCZ,tdxHHYWCZFieldReq)
	// 换汇银行查询 992
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HHYHCX,tdxHHYHCXFieldReq)
	// 换汇汇率查询 994
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HHHLCX,tdxHHHLCXFieldReq)
	// 换汇委托查询 996
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HHWTCX,tdxHHWTCXFieldReq)

	// 撤单查询 1100
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CDCX,tdxCDCXFieldReq)
	// 当日委托查询 1102
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_DRWTCX,tdxDRWTCXFieldReq)
	// 历史委托查询 1104
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LSWTCX,tdxLSWTCXFieldReq)
	// 委托查询 1106
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_WTCX,tdxWTCXFieldReq)
	// 当日成交查询 1108
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_DRCJCX,tdxDRCJCXFieldReq)
	// 历史成交查询 1110
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LSCJCX,tdxLSCJCXFieldReq)
	// 成交查询 1112
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CJCX,tdxCJCXFieldReq)
	// 股份查询 1114
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_GFCX,tdxGFCXFieldReq)
	// 新股配号 1116
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XGPH,tdxXGPHFieldReq)
	// 资金流水 1118
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZJLS,tdxZJLSFieldReq)
	// 交割单 1120
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_JGD,tdxJGDFieldReq)
	// 股东查询 1122
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_GDCX,tdxGDCXFieldReq)
	// 证券信息 1124
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZQXX,tdxZQXXFieldReq)
	// 中签查询 1126
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZQCX,tdxZQCXFieldReq)
	// 修改成本价 1128
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XGCBJ,tdxXGCBJFieldReq)
	// (查询)修改联系方式 1130
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XGLXFS,tdxXGLXFSFieldReq)
	// 对帐单 1132
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_DZD,tdxDZDFieldReq)
	// 配售权益查询 1134
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_PSQYCX,tdxPSQYCXFieldReq)
	// 权证信息查询 1136
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_QZXXCX,tdxQZXXCXFieldReq)
	// 成交汇总查询 1138
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CJHZCX,tdxCJHZCXFieldReq)
	// 股份汇总查询 1140
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_GFHZCX,tdxGFHZCXFieldReq)
	// 权证开通取消 1142
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KTXY,tdxQZKTQXFieldReq)
	// 预委托查询 1144
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YWTCX,tdxYWTCXFieldReq)
	// 签订协议 1146
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_QDXY,tdxQDXYFieldReq)
	// 在途资金查询 1148
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZTZJCX,tdxZTZJCXFieldReq)
	// 金股信转帐 1150
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_JGXZZ,tdxJGXZZFieldReq)
	// 分支代码 1152
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FZDM,tdxFZDMFieldReq)
	// 获取协议内容 1154
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HQXYNR,tdxHQXYNRFieldReq)
	// 获取IPO列表 1156
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HQIPOLB,tdxHQIPOLBFieldReq)
	// IPO信息查询 1158
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_IPOXXCX,tdxIPOXXCXFieldReq)
	// 预受要约查询 1160
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YYCX,tdxYYCXFieldReq)
	// 预受要约撤单 1162
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YYCD,tdxYYCDFieldReq)
	// 预受要约申报 1164
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YYSB,tdxYYSBFieldReq)
	// 质压回购 1166
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZYHG,tdxZYHGFieldReq)
	// 未交收成交明细查询 1168
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_WJSCJMXCX,tdxWJSCJMXFieldReq)
	// 存管预约存取业务 1170
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CGYYCQ,tdxCGYYCQFieldReq)
	// 存管预约存取业务查询 1172
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CGYYCQCX,tdxCGYYCQCXFieldReq)
	// 委托汇总查询 1174
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_WTHZCX,tdxWTHZCXFieldReq)
	// 资金明细查询 1176
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZJMXCX,tdxZJMXCXFieldReq)
	// 查询选择存管银行 1178
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CXXZCGYH,tdxCXXZCGYHFieldReq)
	// 选择存管银行 1180
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XZCGYH,tdxXZCGYHFieldReq)
	// 查询协议信息 1182
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CXXYXX,tdxCXXYXXFieldReq)
	// 历史成交汇总查询 1184
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LSCJHZCX,tdxLSCJHZCXFieldReq)
	// 成交明细查询 1186
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CJMXCX,tdxCJMXCXFieldReq)
	// 委托查询明细 1188
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_WTCXMX,tdxWTCXMXFieldReq)
	// 成交查询明细 1190
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CJCXMX,tdxCJCXMXFieldReq)
	// 意向申报行情查询 1192
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YXSBHQCX,tdxYXSBHQCXFieldReq)
	// 批量委托查询 1194
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_PLWTCX,tdxPLWTCXFieldReq)
	// LOF合并相关代码查询 1196
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LOFHBXGDMCX,tdxLOFHBXGDMCXFieldReq)
	// LOF分拆相关代码查询 1198
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LOFFCXGDMCX,tdxLOFFCXGDMCXFieldReq)
	// LOF盘后业务当日委托查询 1200
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LOFPHYWDRWTCX,tdxLOFPHYWDRWTCXFieldReq)
	// LOF盘后业务历史委托查询 1202
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LOFPHYWLSWTCX,tdxLOFPHYWLSWTCXFieldReq)
	// LOF盘后业务当日成交查询 1204
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LOFPHYWDRCJCX,tdxLOFPHYWDRCJCXFieldReq)
	// LOF盘后业务历史成交查询 1206
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LOFPHYWLSCJCX,tdxLOFPHYWLSCJCXFieldReq)
	// LOF盘后业务撤单查询 1208
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LOFPHYWCDCX,tdxLOFPHYWCDCXFieldReq)
	// 附属股份查询 1210
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FSGFCX,tdxFSGFCXFieldReq)
	// 证券附属信息查询 1212
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZQFSXXCX,tdxZQFSXXCXFieldReq)
	// 报价转让撤单查询 1214
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_BJZRCDCX,tdxBJZRCDCXFieldReq)
	// 报价转让委托查询 1216
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_BJZRWTCX,tdxBJZRWTCXFieldReq)
	// 报价转让成交查询 1218
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_BJZRCJCX,tdxBJZRCJCXFieldReq)
	// 动态股份查询 1220
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_DTGFCX,tdxDTGFCXFieldReq)
	// 债券质押库查询 1222
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZQZYKCX,tdxZQZYKCXFieldReq)
	// 多存管资金明细查询 1224
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_DCGZJMXCX,tdxDCGZJMXCXFieldReq)
	// 历史持仓查询 1226
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LSCCCX,tdxLSCCCXFieldReq)
	// 股份明细查询 1228
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_GFMXCX,tdxGFMXCXFieldReq)
	// 股份查询(2nd版) 1230
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_GFCX_SECOND,tdxGFCXSECONDFieldReq)
	// 股份查询(3rd版) 1232
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_GFCX_THIRD,tdxGFCXTHIRDFieldReq)
	// 债券回购合约查询 1234
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZQHGHYCX,tdxZQHGHYCXFieldReq)
	// 客户对账信息查询 1236
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KHDZXXCX,tdxKHDZXXCXFieldReq)
	// 综合协议行情查询 1238
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZHXYHQCX,tdxZHXYHQCXFieldReq)
	// 标准券汇总查询 1240
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_BZQHZCX,tdxBZQHZCXFieldReq)
	// 柜台债券行情查询 1242
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_GTZQHQCX,tdxGTZQHQCXFieldReq)
	// 融资行权合约查询 1244
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_RZXQHYCX,tdxRZXQHYCXFieldReq)
	// 融资行权客户信息查询 1246
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_RZXQKHXXCX,tdxRZXQKHXXCXFieldReq)
	// 债券回购历史查询 1248
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZQHGLSCX,tdxZQHGLSCXFieldReq)
	// 期权代码查询 1250
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_QQDMCX,tdxQQDMCXFieldReq)
	// 期权持仓查询 1252
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_QQCCCX,tdxQQCCCXFieldReq)
	// 期权所得税查询 1254
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_QQSDSCX,tdxQQSDSCXFieldReq)
	// 期权当日委托查询 1256
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_QQDRWTCX,tdxQQDRWTCXFieldReq)
	// 期权历史委托查询 1258
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_QQLSWTCX,tdxQQLSWTCXFieldReq)

	// 期货委托 1500
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_QHWT,tdxQHWTFieldReq)
	// 查询期货持仓 1502
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CXQHCC,tdxCXQHCCFieldReq)
	// 查询合约信息 1504
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CXHYXX,tdxCXHYXXFieldReq)
	// 查询可交易合同 1506
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CXKJYHY,tdxCXKJYHYFieldReq)
	// 当日资金流水 1508
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_DRZJLS,tdxDRZJLSFieldReq)
	// 期货委托状态查询 1510
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_QHWTZTCX,tdxQHWTZTCXFieldReq)
	// 期货委托回报 1512 [推送功能,请求不使用]
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_QHWTHB,tdxQHWTHBFieldReq)
	// 期货委托回报 1513
	// 期货撤单回报 1514 [推送功能,请求不使用]
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_QHCDHB,tdxQHCDHBFieldReq)
	// 期货撤单回报 1515
	// 期货成交回报 1516 [推送功能,请求不使用]
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_QHCJHB,tdxQHCJHBFieldReq)
	// 期货成交回报 1517
	// 期货信息发布 1518 [推送功能,请求不使用]
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_QHXXFB,tdxQHXXFBFieldReq)
	// 期货信息发布 1519
	// 期货交易所状态改变 1520 [推送功能,请求不使用]
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_QHJYSZTGB,tdxQHJYSZTGBFieldReq)
	// 期货交易所状态改变 1521
	// 期货组合合约变更 1522 [推送功能,请求不使用]
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_QHZHHYBG,tdxQHZHHYBGFieldReq)
	// 期货组合合约变更 1523
	// 期货组合委托回报 1524 [推送功能,请求不使用]
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_QHZHWTHB,tdxQHZHWTHBFieldReq)
	// 期货组合委托回报 1525
	// 期货组合撤单回报 1526 [推送功能,请求不使用]
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_QHZHCDHB,tdxQHZHCDHBFieldReq)
	// 期货组合撤单回报 1527
	// 期货订单类型查询 1528
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_QHDDLXCX,tdxQHDDLXCXFieldReq)
	// 期货组合委托 1530
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_QHZHWT,tdxQHZHWTFieldReq)
	// 期货组合撤单 1532
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_QHZHCD,tdxQHZHCDFieldReq)
	// 期货组合合约查询 1534
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_QHZHHYCX,tdxQHZHHYCXFieldReq)
	// 期货组合持仓查询 1536
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_QHZHCCCX,tdxQHZHCCCXFieldReq)
	// 期货组合委托查询 1538
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_QHZHWTCX,tdxQHZHWTCXFieldReq)
	// 期货组合计算可委托数 1540
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_QHZHJSKWTS,tdxQHZHJSKWTSFieldReq)
	// 期货组合策略查询 1542
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_QHZHCLCX,tdxQHZHCLCXFieldReq)

	// 股票质押回购 1800
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_GPZYHG,tdxGPZYHGFieldReq)
	// 股票质押回购申请查询 1802
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_GPZYHG_SQCX,tdxGPZYHGSQCXFieldReq)
	// 股票质押回购合同查询 1804
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_GPZYHG_HTCX,tdxGPZYHGHTCXFieldReq)
	// 股票质押回购权益查询 1806
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_GPZYHG_QYCX,tdxGPZYHGQYCXFieldReq)
	// 股票质押回购期限利率查询 1808
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_GPZYHG_QXLLCX,tdxGPZYHGQXLLCXFieldReq)
	// 股票质押回购流水查询 1810
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_GPZYHG_LSCX,tdxGPZYHGLSCXFieldReq)
	// 股票质押回购融出方查询 1812
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_GPZYHG_RCFCX,tdxGPZYHGRCFCXFieldReq)
	// 股票质押回购利息查询 1814
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_GPZYHG_LXCX,tdxGPZYHGLXCXFieldReq)
	// 股票质押回购历史合同查询 1816
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_GPZYHG_LSHTCX,tdxGPZYHGLSHTCXFieldReq)
	// 股票质押回购标的证券查询 1818
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_GPZYHG_BDZQCX,tdxGPZYHGBDZQCXFieldReq)
	// 特色回购 1830
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_TSHG,tdxTSHGFieldReq)
	// 特色回购信息查询 1832
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_TSHG_XXCX,tdxTSHGXXCXFieldReq)
	// 特色回购申请查询 1834
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_TSHG_SQCX,tdxTSHGSQCXFieldReq)
	// 特色回购代码查询 1836
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_TSHG_DMCX,tdxTSHGDMCXFieldReq)
	// 特色回购银证通 1838
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_TSHG_YZT,tdxTSHGYZTFieldReq)
	// 特色回购转账计划查询 1840
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_TSHG_ZZJHCX,tdxTSHGZZJHCXFieldReq)
	// 特色回购流水查询 1842
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_TSHG_LSCX,tdxTSHGLSCXFieldReq)							
	// 配售状态设置(查询) 2000
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_PSZTSZ,tdxPSZTSZFieldReq)
	// 合作回购 2002
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HZHG,tdxHZHGFieldReq)
	// 合作回购状态(查询) 2004
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HZHGZT,tdxHZHGZTFieldReq)
	// 合作申购状态(查询) 2006
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HZSGZT,tdxHZSGZTFieldReq)
	// 合作回购产品代码查询 2008
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HZHGCPDMCX,tdxHZHGCPDMCXFieldReq)
	// 合作回购产品信息查询 2010
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HZHGCPXXCX,tdxHZHGCPXXCXFieldReq)
	// 合作回购提前终止查询 2012
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HZHGTQZZCX,tdxHZHGTQZZCXFieldReq)
	// 合作回购当日委托查询 2014
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HZHGDRWTCX,tdxHZHGDRWTCXFieldReq)
	// 合作回购当日成交查询 2016
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HZHGDRCJCX,tdxHZHGDRCJCXFieldReq)
	// 合作回购历史委托查询 2018
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HZHGLSWTCX,tdxHZHGLSWTCXFieldReq)
	// 合作回购历史成交查询 2020
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HZHGLSCJCX,tdxHZHGLSCJCXFieldReq)
	// 合作回购期内合约查询 2022
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HZHGQNHYCX,tdxHZHGQNHYCXFieldReq)
	// 合作回购撤单查询 2024
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HZHGCDCX,tdxHZHGCDCXFieldReq)
	// 合作回购续约查询 2026
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HZHGXYCX,tdxHZHGXYCXFieldReq)
	// 合作回购续约终止查询 2028
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HZHGXYZZCX,tdxHZHGXYZZCXFieldReq)
	// 合作回购提前终止预约查询 2030
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HZHGTQZZYYCX,tdxHZHGTQZZYYCXFieldReq)
	// 合作回购提前终止预约撤销查询 2032
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HZHGTQZZYYCXCX,tdxHZHGTQZZYYCXCXFieldReq)
	// 合作回购对应质押物查询 2034
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HZHGDYZYWCX,tdxHZHGDYZYWCXFieldReq)
	// 合作回购续约撤单查询 2036
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HZHGXYCDCX,tdxHZHGXYCDCXFieldReq)
	// 合作回购当日到期查询 2038
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HZHGDRDQCX,tdxHZHGDRDQCXFieldReq)
	// 合作回购历史到期查询 2040
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HZHGLSDQCX,tdxHZHGLSDQCXFieldReq)
	// 合作回购续作终止预约查询 2042
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HZHGXZZZYYCX,tdxHZHGXZZZYYCXFieldReq)
	// 合作回购续作终止预约撤销查询 2044
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HZHGXZZZYYCXCX,tdxHZHGXZZZYYCXCXFieldReq)
	// 合作回购续约变更查询 2046
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HZHGXYBGCX,tdxHZHGXYBGCXFieldReq)
	// 合作回购合约收益查询 2048
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HZHGHYSYCX,tdxHZHGHYSYCXFieldReq)
	// 深圳报价回购产品代码查询 2050
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_SZBJHGCPDMCX,tdxSZBJHGCPDMCXFieldReq)
	// 深圳报价回购期内合约查询 2052
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_SZBJHGQNHYCX,tdxSZBJHGQNHYCXFieldReq)
	// 合作回购协议设置配套查询 2054
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HZHGXYSZPTCX,tdxHZHGXYSZPTCXFieldReq)


	// 约定回购初始交易配套查询 2070
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YDHGCSJYPTCX,tdxYDHGCSJYPTCXFieldReq)
	// 约定回购履约保障配套查询 2072
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YDHGLYBZPTCX,tdxYDHGLYBZPTCXFieldReq)
	// 约定回购提前购回配套查询 2074
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YDHGTQGHPTCX,tdxYDHGTQGHPTCXFieldReq)
	// 约定回购延期申请配套查询 2076
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YDHGYQSQPTCX,tdxYDHGYQSQPTCXFieldReq)
	// 约定回购交易撤单配套查询 2078
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YDHGJYCDPTCX,tdxYDHGJYCDPTCXFieldReq)
	// 约定回购当前合约查询 2080
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YDHGDQHYCX,tdxYDHGDQHYCXFieldReq)
	// 约定回购历史合约查询 2082
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YDHGLSHYCX,tdxYDHGLSHYCXFieldReq)
	// 约定回购进行合约查询 2084
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YDHGJXHYCX,tdxYDHGJXHYCXFieldReq)
	// 约定回购终止合约查询 2086
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YDHGZZHYCX,tdxYDHGZZHYCXFieldReq)
	// 约定回购标的证券查询 2088
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YDHGBDZQCX,tdxYDHGBDZQCXFieldReq)
	// 约定回购产品信息查询 2090
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YDHGCPXXCX,tdxYDHGCPXXCXFieldReq)
	// 约定回购综合信息查询 2092
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YDHGZHXXCX,tdxYDHGZHXXCXFieldReq)
	// 约定回购业务操作(信息查询) 2098
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YDHGYWCZ,tdxYDHGYWCZFieldReq)

	// 开放式基金委托 2100
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJWT,tdxKFSJJWTFieldReq)
	// 开放式基金委托撤单 2102
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJWTCD,tdxKFSJJWTCDFieldReq)
	// 开放式基金转换 2104
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJZH,tdxKFSJJZHFieldReq)
	// 开放式基金份额查询 2106
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJFECX,tdxKFSJJFECXFieldReq)
	// 开放式基金委托查询 2108
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJWTCX,tdxKFSJJWTCXFieldReq)
	// 开放式基金信息查询 2110
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJXXCX,tdxKFSJJXXCXFieldReq)
	// 开放式基金成交查询 2112
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJCJCX,tdxKFSJJCJCXFieldReq)
	// 开放式基金分红设定 2114
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJFH,tdxKFSJJFHFieldReq)
	// 开放式基金代码查询 2116
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJDMCX,tdxKFSJJDMCXFieldReq)
	// 开放式基金资金帐户开户 2118
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJZJZHKH,tdxKFSJJZJZHKHFieldReq)
	// 开放式基金资金帐户注册 2120
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJZJZHZC,tdxKFSJJZJZHZCFieldReq)
	// 开放式基金客户资料修改 2122
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJKHZLXG,tdxKFSJJKHZLXGFieldReq)
	// 开放式基金查询公司代码 2124
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJCXGSDM,tdxKFSJJCXGSDMFieldReq)
	// 开放式基金帐户查询 2126
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJZHCX,tdxKFSJJZHCXFieldReq)
	// 开放式基金委托查询 2128
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJLSWTCX,tdxKFSJJLSWTCXFieldReq)
	// 开放式基金定时定额申购设置 2130
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJDSDESGSZ,tdxKFSJJDSDESGSZFieldReq)
	// 开放式基金定时定额申购取消 2132
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJDSDESGQX,tdxKFSJJDSDESGQXFieldReq)
	//开放式基金定时定额申购设置查询
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_DQDESZCX,tdxKFSJJDSDESZCXFieldReq)
	// 开放式基金定期定额申购品种 2134
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJCXDQDESGPZ,tdxKFSJJCXDQDESGPZFieldReq)
	// 开放式基金当日委托查询 2136
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJDRWTCX,tdxKFSJJDRWTCXFieldReq)
	// 开放式基金分红查询 2138
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJFHCX,tdxKFSJJFHCXFieldReq)
	// LOF基金分红查询 2140
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LOFJJFHCX,tdxLOFJJFHCXFieldReq)
	// LOF基金分红设定 2142
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LOFJJFH,tdxLOFJJFHFieldReq)
	// 开放式基金风险信息查询 2144
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJFXXXCX,tdxKFSJJFXXXCXFieldReq)
	// 开放式基金转帐开户 2146
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJZZKH,tdxKFSJJZZKHFieldReq)
	// 开放式基金交易开户 2148
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJJYKH,tdxKFSJJJYKHFieldReq)
	// 当日成交查询 2150
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJDRCJCX,tdxKFSJJDRCJCXFieldReq)
	// 历史成交查询 2152
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJLSCJCX,tdxKFSJJLSCJCXFieldReq)
	// 开放式基金净值查询 2154
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJJZCX,tdxKFSJJJZCXFieldReq)
	// 开放式基金协议查询开通 2156
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJXYCXKT,tdxKFSJJXYCXKTFieldReq)
	// 开放式基金分红明细查询 2158
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJFHMXCX,tdxKFSJJFHMXCXFieldReq)
	// 开放式基金非交易委托查询 2162
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJFJYWTCX,tdxKFSJJFJYWTCXFieldReq)
	// 开放式基金非交易当日委托查询 2164
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJFJYDRWTCX,tdxKFSJJFJYDRWTCXFieldReq)
	// 开放式基金风险可承受代码查询 2166
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJFXKCSDMCX,tdxKFSJJFXKCSDMCXFieldReq)
	// 开放式基金费率查询 2168
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJFLCX,tdxKFSJJFLCXFieldReq)
	// 开放式基金定期定额赎回设置 2170
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJDQDESHSZ,tdxKFSJJDQDESHSZFieldReq)
	// 开放式基金定期定额赎回取消 2172
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJDQDESHQX,tdxKFSJJDQDESHQXFieldReq)
	// 开放式基金定期定额赎回查询 2174
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJDQDESHCX,tdxKFSJJDQDESHCXFieldReq)
	// 开放式基金定期定额赎回品种 2176
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJDQDESHPZ,tdxKFSJJDQDESHPZFieldReq)
	// 开放式基金代码相关信息查询 2178
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJDMXGXXCX,tdxKFSJJDMXGXXCXFieldReq)
	// 开放式基金公司相关信息查询 2180
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJGSXGXXCX,tdxKFSJJGSXGXXCXFieldReq)
	// 开放式基金对账单查询 2182
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJDZDCX,tdxKFSJJDZDCXFieldReq)
	// 开放式基金交割单查询 2184
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJJGDCX,tdxKFSJJJGDCXFieldReq)

	// 理财产品份额查询 2200
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LCCPFECX,tdxLCCPFECXFieldReq)
	// 理财产品委托查询 2202
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LCCPWTCX,tdxLCCPWTCXFieldReq)
	// 理财产品成交查询 2204
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LCCPCJCX,tdxLCCPCJCXFieldReq)
	// 理财产品当日委托查询 2206
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LCCPDRWTCX,tdxLCCPDRWTCXFieldReq)
	// 理财产品代码查询 2208
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LCCPDMCX,tdxLCCPDMCXFieldReq)
	// 理财产品帐号查询 2210
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LCCPZHCX,tdxLCCPZHCXFieldReq)
	// 理财产品定期定额申购查询 2212
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LCCPDQDESGCX,tdxLCCPDQDESGCXFieldReq)
	// 理财产品定期定额申购品种 2214
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LCCPDQDESGPZ,tdxLCCPDQDESGPZFieldReq)
	// 理财产品增值计划列表查询 2216
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LCCPZZJHLBCX,tdxLCCPZZJHLBCXFieldReq)
	// 理财产品增值计划信息查询 2218
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LCCPZZJHXXCX,tdxLCCPZZJHXXCXFieldReq)
	// 理财产品增值计划金额设置 2220
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LCCPZZJHJESZ,tdxLCCPZZJHJESZFieldReq)
	// 理财产品增值计划状态设置 2222
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LCCPZZJHZTSZ,tdxLCCPZZJHZTSZFieldReq)
	// 理财产品增值计划解除协议 2224
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LCCPZZJHJCXY,tdxLCCPZZJHJCXYFieldReq)
	// 理财产品增值计划份额查询 2226
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LCCPZZJHFECX,tdxLCCPZZJHFECXFieldReq)
	// 理财产品增值计划撤单查询 2228
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LCCPZZJHCDCX,tdxLCCPZZJHCDCXFieldReq)
	// 理财产品增值计划信息修改 2230
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LCCPZZJHXXXG,tdxLCCPZZJHXXXGFieldReq)
	// 理财产品增值计划份额赎回 2232
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LCCPZZJHFESH,tdxLCCPZZJHFESHFieldReq)
	// 理财产品增值计划委托撤单 2234
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LCCPZZJHWTCD,tdxLCCPZZJHWTCDFieldReq)
	// 理财产品增值计划预约取款操作 2236
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LCCPZZJHYYQKCZ,tdxLCCPZZJHYYQKCZFieldReq)
	// 理财产品增值计划预约取款查询 2238
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LCCPZZJHYYQKCX,tdxLCCPZZJHYYQKCXFieldReq)
	// 理财产品增值计划历史收益查询 2240
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LCCPZZJHLSSYCX,tdxLCCPZZJHLSSYCXFieldReq)
	// 短期理财产品赎回信息查询 2242
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_DQLCCPSHXXCX,tdxDQLCCPSHXXCXFieldReq)
	// 理财产品转让代码查询 2244
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LCCPZRDMCX,tdxLCCPZRDMCXFieldReq)
	// 理财产品转让行情查询 2246
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LCCPZRHQCX,tdxLCCPZRHQCXFieldReq)
	// 理财产品转让撤单查询 2248
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LCCPZRCDCX,tdxLCCPZRCDCXFieldReq)
	// 理财产品转让委托查询 2250
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LCCPZRWTCX,tdxLCCPZRWTCXFieldReq)
	// 理财产品转让成交查询 2252
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LCCPZRCJCX,tdxLCCPZRCJCXFieldReq)
	// 理财产品签约解约查询 2254
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LCCPQYJYCX,tdxLCCPQYJYCXFieldReq)
	// 银行理财产品代码查询 2256
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YHLCCPDMCX,tdxYHLCCPDMCXFieldReq)
	// 银行理财产品份额查询 2258
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YHLCCPFECX,tdxYHLCCPFECXFieldReq)
	// 银行理财产品委托查询 2260
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YHLCCPWTCX,tdxYHLCCPWTCXFieldReq)
	// 银行理财产品帐号查询 2262
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YHLCCPZHCX,tdxYHLCCPZHCXFieldReq)
	// 银行理财产品成交查询 2264
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YHLCCPCJCX,tdxYHLCCPCJCXFieldReq)
	// OTC份额查询 2266
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_OTCFECX,tdxOTCFECXFieldReq)
	// OTC认申赎查询 2268
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_OTCRSSCX,tdxOTCRSSCXFieldReq)
	// OTC意向申报查询 2270
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_OTCYXSBCX,tdxOTCYXSBCXFieldReq)
	// OTC成交申报查询 2272
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_OTCCJSBCX,tdxOTCCJSBCXFieldReq)
	// OTC产品合约查询 2274
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_OTCCPHYCX,tdxOTCCPHYCXFieldReq)
	// OTC报价信息查询 2276
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_OTCBJXXCX,tdxOTCBJXXCXFieldReq)
	// OTC行情信息查询 2278
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_OTCHQXXCX,tdxOTCHQXXCXFieldReq)
	// OTC电子合同列表查询 2280
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_OTCDZHTLBCX,tdxOTCDZHTLBCXFieldReq)
	// OTC电子合同查询 2282
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_OTCDZHTCX,tdxOTCDZHTCXFieldReq)	
	// 信托产品代码查询 2300
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XTCPDMCX,tdxXTCPDMCXFieldReq)
	// 信托产品份额查询 2302
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XTCPFECX,tdxXTCPFECXFieldReq)
	// 信托产品帐号查询 2304
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XTCPZHCX,tdxXTCPZHCXFieldReq)
	// 信托产品委托查询 2306
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XTCPWTCX,tdxXTCPWTCXFieldReq)		
	// 信托产品成交查询 2308
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XTCPCJCX,tdxXTCPCJCXFieldReq)
	// 信托产品历史委托查询 2310
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XTCPLSWTCX,tdxXTCPLSWTCXFieldReq)

	// 基金直销认购 2500
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_JJZXRG,tdxJJZXRGFieldReq)
	// 基金直销申购 2502
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_JJZXSG,tdxJJZXSGFieldReq)
	// 基金直销赎回 2504
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_JJZXSH,tdxJJZXSHFieldReq)
	// 基金直销分红 2506
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_JJZXFH,tdxJJZXFHFieldReq)
	// 基金直销转换 2508
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_JJZXZH,tdxJJZXZHFieldReq)
	// 基金直销转托管 2510
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_JJZXZTG,tdxJJZXZTGFieldReq)
	// 基金直销撤单 2512
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_JJZXCD,tdxJJZXCDFieldReq)
	// 基金直销费率查询 2514
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_JJZXFLCX,tdxJJZXFLCXFieldReq)
	// 基金直销银行支付 2516
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_JJZXYHZF,tdxJJZXYHZFFieldReq)
	// 基金直销销售人代码查询 2518
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_JJZXXSRDMCX,tdxJJZXXSRDMCXFieldReq)
	// 基金直销信息检查 2520
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_JJZXXXJC,tdxJJZXXXJCFieldReq)
	
	// 交易所场内基金代码查询 2850
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_JYSCNJJDMCX,tdxJYSCNJJDMCXFieldReq)
	// 交易所场内基金成分股查询 2852
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_JYSCNJJCFGCX,tdxJYSCNJJCFGCXFieldReq)

	// ETF上海跨境申购配套查询 2950
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFSHKJSGPTCX,tdxETFSHKJSGPTCXFieldReq)
	// ETF深圳跨境申购配套查询 2952
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFSZKJSGPTCX,tdxETFSZKJSGPTCXFieldReq)
	// ETF上海跨境赎回配套查询 2954
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFSHKJSHPTCX,tdxETFSHKJSHPTCXFieldReq)
	// ETF深圳跨境赎回配套查询 2956
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFSZKJSHPTCX,tdxETFSZKJSHPTCXFieldReq)
	// ETF上海跨境委托撤单查询 2958
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFSHKJWTCDCX,tdxETFSHKJWTCDCXFieldReq)
	// ETF深圳跨境委托撤单查询 2960
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFSZKJWTCDCX,tdxETFSZKJWTCDCXFieldReq)
	// ETF上海跨境当日委托查询 2962
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFSHKJDRWTCX,tdxETFSHKJDRWTCXFieldReq)
	// ETF深圳跨境当日委托查询 2964
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFSZKJDRWTCX,tdxETFSZKJDRWTCXFieldReq)
	// ETF上海跨境当日成交查询 2966
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFSHKJDRCJCX,tdxETFSHKJDRCJCXFieldReq)
	// ETF深圳跨境当日成交查询 2968
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFSZKJDRCJCX,tdxETFSZKJDRCJCXFieldReq)
	// ETF上海跨境历史委托查询 2970
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFSHKJLSWTCX,tdxETFSHKJLSWTCXFieldReq)
	// ETF深圳跨境历史委托查询 2972
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFSZKJLSWTCX,tdxETFSZKJLSWTCXFieldReq)
	// ETF上海跨境历史成交查询 2974
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFSHKJLSCJCX,tdxETFSHKJLSCJCXFieldReq)
	// ETF深圳跨境历史成交查询 2976
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFSZKJLSCJCX,tdxETFSZKJLSCJCXFieldReq)
	// ETF网下现金认购配套查询 2980
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFWXXJRGPTCX,tdxETFWXXJRGPTCXFieldReq)
	// ETF网下股份认购配套查询 2982
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFWXGFRGPTCX,tdxETFWXGFRGPTCXFieldReq)
	// ETF网下现金认购撤单查询 2984
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFWXXJRGCDCX,tdxETFWXXJRGCDCXFieldReq)
	// ETF网下股份认购撤单查询 2986
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFWXGFRGCDCX,tdxETFWXGFRGCDCXFieldReq)
	// ETF网下现金认购信息查询 2988
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFWXXJRGXXCX,tdxETFWXXJRGXXCXFieldReq)
	// ETF网下股份认购信息查询 2990
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFWXGFRGXXCX,tdxETFWXGFRGXXCXFieldReq)
	// ETF网下现金认购流水查询 2992
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFWXXJRGLSCX,tdxETFWXXJRGLSCXFieldReq)
	// ETF网下股份认购流水查询 2994
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFWXGFRGLSCX,tdxETFWXGFRGLSCXFieldReq)
	// ETF买卖 3000
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFMM,tdxETFMMFieldReq)
	// ETF信息查询 3002
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFXXCX,tdxETFXXCXFieldReq)
	// ETF认购查询 3004
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFRGCX,tdxETFRGCXFieldReq)
	// ETF认购撤单 3006
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFRGCD,tdxETFRGCDFieldReq)
	// ETF批次号 3008
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFPCH,tdxETFPCHFieldReq)
	// ETF股票篮买卖 3010
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFGPLMM,tdxETFGPLMMFieldReq)
	// ETF股票篮查询 3012
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFGPLCX,tdxETFGPLCXFieldReq)
	// ETF预购查询 3014
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFYGCX,tdxETFYGCXFieldReq)
	// ETF委托撤单 3016
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFWTCX,tdxETFWTCXFieldReq)
	// ETF成交查询 3018
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFCJCX,tdxETFCJCXFieldReq)
	// ETF策略查询 3020
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFCLCX,tdxETFCLCXFieldReq)
	// ETF指数代码查询 3022
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFZSDMCX,tdxETFZSDMCXFieldReq)
	// ETF(委托)确认 3024
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFQR,tdxETFQRFieldReq)
	// ETF委托查询明细 3026
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFWTCXMX,tdxETFWTCXMXFieldReq)
	// ETF认购撤单查询 3028
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFRGCDCX,tdxETFRGCDCXFieldReq)
	// ETF指数成分查询 3030
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFZSCFCX,tdxETFZSCFCXFieldReq)
	// ETF股份查询 3032
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFGFCX,tdxETFGFCXFieldReq)
	// ETF可申购成分股查询 3034
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFKSGCFGCX,tdxETFKSGCFGCXFieldReq)
	// ETF股票篮撤单 3036
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFGPLCD,tdxETFGPLCDFieldReq)
	// ETF股票篮撤单查询 3038
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFGPLCDCX,tdxETFGPLCDCXFieldReq)
	// ETF跨市场对盘查询 3040
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFKSCDPCX,tdxETFKSCDPCXFieldReq)

	// 组合通批次号 3050
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZHTPCH,tdxZHTPCHFieldReq)
	// 组合通股票篮买卖 3052
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZHTGPLMM,tdxZHTGPLMMFieldReq)
	// 组合通股票篮查询 3054
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZHTGPLCX,tdxZHTGPLCXFieldReq)
	// 组合通拥股查询 3056
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZHTYGCX,tdxZHTYGCXFieldReq)
	// 组合通委托查询 3058
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZHTWTCX,tdxZHTWTCXFieldReq)
	// 组合通成交查询 3060
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZHTCJCX,tdxZHTCJCXFieldReq)
	// 组合通策略查询 3062
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZHTCLCX,tdxZHTCLCXFieldReq)
	// 组合通指数代码查询 3064
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZHTZSDMCX,tdxZHTZSDMCXFieldReq)
	// 组合通确认 3066
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZHTQR,tdxZHTQRFieldReq)
	// 组合通历史查询 3068
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZHTLSCX,tdxZHTLSCXFieldReq)
	// 组合通历史查询明细 3070
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZHTLSCXMX,tdxZHTLSCXMXFieldReq)
	// 组合通委托查询明细 3072
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZHTWTCXMX,tdxZHTWTCXMXFieldReq)
	// 组合通成交查询明细 3074
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZHTCJCXMX,tdxZHTCJCXMXFieldReq)
	// 组合通指数成分查询 3076
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZHTZSCFCX,tdxZHTZSCFCXFieldReq)

	// (套利)获取会话号 3100
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_TL_HQHHH,tdxTLHQHHHFieldReq)
	// (套利)组合代码查询 3102
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_TL_ZHDMCX,tdxTLZHDMCXFieldReq)
	// (套利)组合成分查询 3104
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_TL_ZHCFCX,tdxTLZHCFCXFieldReq)
	// (套利)组合代码操作 3106
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_TL_ZHDMCZ,tdxTLZHDMCZFieldReq)
	// (套利)组合成分操作 3108
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_TL_ZHCFCZ,tdxTLZHCFCZFieldReq)
	// (套利)策略代码查询 3110
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_TL_CLDMCX,tdxTLCLDMCXFieldReq)
	// (套利)策略成分查询 3112
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_TL_CLCFCX,tdxTLCLCFCXFieldReq)
	// (套利)策略代码操作 3114
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_TL_CLDMCZ,tdxTLCLDMCZFieldReq)
	// (套利)策略成分操作 3116
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_TL_CLCFCZ,tdxTLCLCFCZFieldReq)
	// (套利)批号操作 3118
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_TL_PHCZ,tdxTLPHCZFieldReq)
	// (套利)批号查询 3120
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_TL_PHCX,tdxTLPHCXFieldReq)
	// (套利)批号委托列表 3122
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_TL_PHWTLB,tdxTLPHWTLBFieldReq)
	// (套利)批号委托执行 3124
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_TL_PHWTZX,tdxTLPHWTZXFieldReq)
	// (套利)批号委托查询 3126
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_TL_PHWTCX,tdxTLPHWTCXFieldReq)
	// (套利)批号持仓查询 3128
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_TL_PHCCCX,tdxTLPHCCCXFieldReq)

	// (算法交易)订单操作 3190
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_SFJY_DDCZ,tdxSFJYDDCZFieldReq)
	// (算法交易)订单列表查询 3192
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_SFJY_DDLBCX,tdxSFJYDDLBCXFieldReq)
	// (算法交易)订单结果查询 3194
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_SFJY_DDJGCX,tdxSFJYDDJGCXFieldReq)

	// 信用资产查询 3200
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYZCCX,tdxXYZCCXFieldReq)
	// 信用股份查询 3202
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYGFCX,tdxXYGFCXFieldReq)
	// 信用合约查询(默认未平仓) 3204
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYHYCX,tdxXYHYCXFieldReq)
	// 信用合约已平仓查询 3206
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYHYYPCCX,tdxXYHYCXFieldReq)
	// 信用上限查询 3208
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYSXCX,tdxXYSXCXFieldReq)
	// 信用负债查询 3210
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYFZCX,tdxXYFZCXFieldReq)
	// 非信用资产查询 3212
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FXYZCCX,tdxFXYZCCXFieldReq)
	// 信用合约当日查询 3214
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYHYDRCX,tdxXYHYDRCXFieldReq)
	// 信用交易标的证券查询 3216
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYBDZQCX,tdxXYJYBDZQCXFieldReq)
	// 信用交易综合信息查询 3218
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYZHXXCX,tdxXYJYZHXXCXFieldReq)
	// 信用交易担保品证券查询 3220
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYDBPZQCX,tdxXYJYDBPZQCXFieldReq)
	// 信用交易融资买入证券查询 3222
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYRZMRZQCX,tdxXYJYRZMRZQCXFieldReq)
	// 信用交易融券卖出证券查询 3224
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYRQMCZQCX,tdxXYJYRQMCZQCXFieldReq)
	// 信用交易代码提示信息查询 3226
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYDMTSXXCX,tdxXYJYDMTSXXCXFieldReq)
	// 信用交易合约汇总查询 3228
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYHYHZCX,tdxXYJYHYHZCXFieldReq)
	// 信用交易融资买入配套查询 3230
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYRZMRPTCX,tdxXYJYRZMRPTCXFieldReq)
	// 信用交易融券卖出配套查询 3232
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYRQMCPTCX,tdxXYJYRQMCPTCXFieldReq)
	// 信用交易买券还券配套查询 3234
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYMQHQPTCX,tdxXYJYMQHQPTCXFieldReq)
	// 信用交易余券划转配套查询 3236
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYYQHZPTCX,tdxXYJYYQHZPTCXFieldReq)
	// 信用交易现券还券配套查询 3238
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYXQHQPTCX,tdxXYJYXQHQPTCXFieldReq)
	// 信用交易担保品划转配套查询 3240
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYDBPHZPTCX,tdxXYJYDBPHZPTCXFieldReq)
	// 信用交易担保品划入配套查询 3242
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYDBPHRPTCX,tdxXYJYDBPHRPTCXFieldReq)
	// 信用交易担保品划出配套查询 3244
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYDBPHCPTCX,tdxXYJYDBPHCPTCXFieldReq)
	// 信用交易现金还款配套查询 3246
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYXJHKPTCX,tdxXYJYXJHKPTCXFieldReq)
	// 信用交易卖券还款配套查询 3248
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYMQHKPTCX,tdxXYJYMQHKPTCXFieldReq)
	// 信用交易融资平仓卖出配套查询 3250
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYRZPCMCPTCX,tdxXYJYRZPCMCPTCXFieldReq)
	// 信用交易融券平仓买入配套查询 3252
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYRQPCMRPTCX,tdxXYJYRQPCMRPTCXFieldReq)
	// 信用交易利率信息查询 3254
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYLLXXCX,tdxXYJYLLXXCXFieldReq)
	// 信用交易融券余额查询 3256
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYRQYECX,tdxXYJYRQYECXFieldReq)
	// 信用交易融资余额查询 3258
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYRZYECX,tdxXYJYRZYECXFieldReq)
	// 信用交易非交易化转查询 3260
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYFJYHZCX,tdxXYJYFJYHZCXFieldReq)
	// 信用交易利息费用查询 3262
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYLXFYCX,tdxXYJYLXFYCXFieldReq)
	// 信用交易资金负债查询 3264
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYZJFZCX,tdxXYJYZJFZCXFieldReq)
	// 信用交易证券负债查询 3266
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYZQFZCX,tdxXYJYZQFZCXFieldReq)
	// 信用交易客户签约查询 3268
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYKHQYCX,tdxXYJYKHQYCXFieldReq)
	// 信用交易客户协议处理 3270
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYKHXYCL,tdxXYJYKHXYCLFieldReq)
	// 信用交易偿还明细查询 3272
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYCHMXCX,tdxXYJYCHMXCXFieldReq)
	// 信用交易融资合约查询 3274
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYRZHYCX,tdxXYJYRZHYCXFieldReq)
	// 信用交易融券合约查询 3276
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYRQHYCX,tdxXYJYRQHYCXFieldReq)
	// 信用交易担保品划转查询 3278
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYDBPHZCX,tdxXYJYDBPHZCXFieldReq)
	// 信用交易买入担保品配套查询 3280
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYMRDBPPTCX,tdxXYJYMRDBPPTCXFieldReq)
	// 信用交易卖出担保品配套查询 3282
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYMCDBPPTCX,tdxXYJYMCDBPPTCXFieldReq)
	// 信用交易归还融券费用配套查询 3284
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYGHRQFYPTCX,tdxXYJYGHRQFYPTCXFieldReq)
	// 信用交易负债流水查询 3286
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYFZLSCX,tdxXYJYFZLSCXFieldReq)
	// 信用交易现金替代还券配套查询 3288
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYXJTDHQPTCX,tdxXYJYXJTDHQPTCXFieldReq)
	// 信用交易维持担保比率查询 3290
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYWCDBBLCX,tdxXYJYWCDBBLCXFieldReq)
	// 信用交易额度管理 3292
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYEDGL,tdxXYJYEDGLFieldReq)
	// 信用交易额度变更查询 3294
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYEDBGCX,tdxXYJYEDBGCXFieldReq)
	// 信用交易平仓融资合约查询 3296
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYPCRZHYCX,tdxXYJYPCRZHYCXFieldReq)
	// 信用交易平仓融券合约查询 3298
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYPCRQHYCX,tdxXYJYPCRQHYCXFieldReq)

	// 转融通业务操作 3400
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTYWCZ,tdxZRTYWCZFieldReq)
	// 转融通标的证券查询 3402
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTBDZQCX,tdxZRTBDZQCXFieldReq)
	// 转融通资金信息查询 3404
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTZJXXCX,tdxZRTZJXXCXFieldReq)
	// 转融通股份信息查询 3406
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTGFXXCX,tdxZRTGFXXCXFieldReq)
	// 转融通融资买入配套查询 3408
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTRZMRPTCX,tdxZRTRZMRPTCXFieldReq)
	// 转融通融券卖出配套查询 3410
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTRQMCPTCX,tdxZRTRQMCPTCXFieldReq)
	// 转融通资金借入申请配套查询 3412
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTZJJRSQPTCX,tdxZRTZJJRSQPTCXFieldReq)
	// 转融通股份借入申请配套查询 3414
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTGFJRSQPTCX,tdxZRTGFJRSQPTCXFieldReq)
	// 转融通借入展期申请配套查询 3416
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTJRZQSQPTCX,tdxZRTJRZQSQPTCXFieldReq)
	// 转融通提前归还申请配套查询 3418
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTTQGHSQPTCX,tdxZRTTQGHSQPTCXFieldReq)
	// 转融通借入业务撤单查询 3420
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTJRYWCDCX,tdxZRTJRYWCDCXFieldReq)
	// 转融通借入业务当日查询 3422
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTJRYWDRCX,tdxZRTJRYWDRCXFieldReq)
	// 转融通借入业务历史查询 3424
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTJRYWLSCX,tdxZRTJRYWLSCXFieldReq)
	// 转融通当日借入合约查询 3426
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTDRJRHYCX,tdxZRTDRJRHYCXFieldReq)
	// 转融通未了借入合约查询 3428
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTWLJRHYCX,tdxZRTWLJRHYCXFieldReq)
	// 转融通已了借入合约查询 3430
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTYLJRHYCX,tdxZRTYLJRHYCXFieldReq)
	// 转融通资金出借申请配套查询 3432
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTZJCJSQPTCX,tdxZRTZJCJSQPTCXFieldReq)
	// 转融通股份出借申请配套查询 3434
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTGFCJSQPTCX,tdxZRTGFCJSQPTCXFieldReq)
	// 转融通资金出借确定配套查询 3436
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTZJCJQDPTCX,tdxZRTZJCJQDPTCXFieldReq)
	// 转融通股份出借确定配套查询 3438
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTGFCJQDPTCX,tdxZRTGFCJQDPTCXFieldReq)
	// 转融通出借业务撤单查询 3440
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTCJYWCDCX,tdxZRTCJYWCDCXFieldReq)
	// 转融通出借业务当日查询 3442
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTCJYWDRCX,tdxZRTCJYWDRCXFieldReq)
	// 转融通出借业务历史查询 3444
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTCJYWLSCX,tdxZRTCJYWLSCXFieldReq)
	// 转融通出借提前索还配套查询 3446
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTCJTQSHPTCX,tdxZRTCJTQSHPTCXFieldReq)
	// 转融通出借同意展期配套查询 3448
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTCJTYZQPTCX,tdxZRTCJTYZQPTCXFieldReq)
	// 转融通期限费率查询 3450
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTQXFLCX,tdxZRTQXFLCXFieldReq)
	// 转融通出借合约查询 3452
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTCJHYCX,tdxZRTCJHYCXFieldReq)
	// 转融通出借历史合约查询 3454
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTCJLSHYCX,tdxZRTCJLSHYCXFieldReq)
	// 转融通卖出还款配套查询 3456
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTMCHKPTCX,tdxZRTMCHKPTCXFieldReq)
	// 转融通买入还券配套查询 3458
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTMRHQPTCX,tdxZRTMRHQPTCXFieldReq)
	// 转融通现金还款配套查询 3460
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTXJHKPTCX,tdxZRTXJHKPTCXFieldReq)
	// 转融通现券还券配套查询 3462
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTXQHQPTCX,tdxZRTXQHQPTCXFieldReq)
	// 转融通可出借信息查询 3464
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTKCJXXCX,tdxZRTKCJXXCXFieldReq)
	// 转融通借入同意索还配套查询 3466
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTJRTYSHPTCX,tdxZRTJRTYSHPTCXFieldReq)
	// 转融通出借账户信息查询 3468
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTCJZHXXCX,tdxZRTCJZHXXCXFieldReq)

	// (新利)开通取消自动代理 4100
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XLYZT_KTQXZDDL,tdxXLKTQXZDDLFieldReq)
	// (新利)开通合作配售 4102
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XLYZT_KTHZPS,tdxXLKTHZPSFieldReq)
	// (新利)取消合作配售 4104
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XLYZT_QXHZPS,tdxXLQXHZPSFieldReq)
	// (新利)开通合作回购 4106
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XLYZT_KTHZHG,tdxXLKTHZHGFieldReq)
	// (新利)取消合作回购 4108
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XLYZT_QXHZHG,tdxXLQXHZHGFieldReq)
	// (新利)开通合作申购 4110
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XLYZT_KTHZSG,tdxXLKTHZSGFieldReq)
	// (新利)取消合作申购 4112
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XLYZT_QXHZSG,tdxXLQXHZSGFieldReq)
	// (新利)代理功能查询 4114
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XLYZT_DLGNCX,tdxXLDLGNCXFieldReq)
	// 收益率排名 5000
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_SYLPM,tdxSYLPMFieldReq)
	// 帐户融券 5002
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZHRQ,tdxZHRQFieldReq)
	// 融券查询 5004
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_RQCX,tdxRQCXFieldReq)
	// 帐户还券展期 5006
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZHHQZQ,tdxZHHQZQFieldReq)
	// 交易中心监控 5008
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_TCMONITOR,tdxTCMONITORFieldReq)
	// TS路由 5010
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_TSROUTING,tdxTSROUTINGFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_TSROUTING,tdxTSROUTINGFieldAns)
END_STRUCT_FIELD_DEF(tdxCommonStructFieldInfo)

// 安全中心字典定义
BEGIN_STRUCT_FIELD_DEF(tdxScntrStructFieldInfo)
	// 安全中心协议

	// CA账户申请 800
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_ZHSQ,tdxCAZHSQFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_ZHSQ,tdxCAZHSQFieldAns)

	// CA帐号查询 802
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_ZHCX,tdxCAZHCXFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_ZHCX,tdxCAZHCXFieldAns)

	// CA账户校验 804
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_ZHJY,tdxCAZHJYFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_ZHJY,tdxCAZHJYFieldAns)

	// CA认证口令修改 806
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_TXMMXG,tdxCATXMMXGFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_TXMMXG,tdxCATXMMXGFieldAns)

	// CA认证口令查询 808
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_TXMMCX,tdxCATXMMCXFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_TXMMCX,tdxCATXMMCXFieldAns)

	// CA证书下载 810
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_ZSXZ,tdxCAZSXZFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_ZSXZ,tdxCAZSXZFieldAns)

	// CA证书下载确认 812
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_ZSXZQR,tdxCAZSXZQRFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_ZSXZQR,tdxCAZSXZQRFieldAns)

	// 帐号状态修改 814
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_ZTXM,tdxCAZTXGFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_ZTXM,tdxCAZTXGFieldAns)

	// CA证书更新 816
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_ZSGX,tdxCAZSGXFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_ZSGX,tdxCAZSGXFieldAns)

	// 用户分级查询 818
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_YHFJCX,tdxCAYHFJCXFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_YHFJCX,tdxCAYHFJCXFieldAns)

	// 用户分级申请 820
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_YHFJSQ,tdxCAYHFJSQFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_YHFJSQ,tdxCAYHFJSQFieldAns)

	// HTTP用户分级查询 822
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_HTTPYHFJCX,tdxCAHTTPYHFJCXFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_HTTPYHFJCX,tdxCAHTTPYHFJCXFieldAns)

	// (注册)匿名用户 824
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_ANONUSER,tdxCANMZCFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_ANONUSER,tdxCANMZCFieldAns)
	
	// 新建主题 826
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_XJZT,tdxCAXJZTFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_XJZT,tdxCAXJZTFieldAns)
	
	// 查询主题 828
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_CXZT,tdxCACXZTFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_CXZT,tdxCACXZTFieldAns)
	
	// 查询回复 830
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_CXHF,tdxCACXHFFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_CXHF,tdxCACXHFFieldAns)
	
	// 回复主题 832
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_HFZT,tdxCAHFZTFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_HFZT,tdxCAHFZTFieldAns)
	
	// (问题解决)关闭主题 834
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_GBZT,tdxCAGBZTFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_GBZT,tdxCAGBZTFieldAns)
	
	// 用户(留言)信息 836
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_USERMESSAGE,tdxCAYHLYFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_USERMESSAGE,tdxCAYHLYFieldAns)

	// 匿名用户激活 838
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_USERACTION,tdxCANMJHFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_USERACTION,tdxCANMJHFieldAns)

	// 匿名用户登录 840
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_ANONYLOGIN,tdxCANMDLFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_ANONYLOGIN,tdxCANMDLFieldAns)

	// 查询是否有最新留言 842
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_QUERYMSG,tdxCANEWMSGFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_QUERYMSG,tdxCANEWMSGFieldAns)

	// 已阅读留言 844
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_READED,tdxCAREADMSGFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_READED,tdxCAREADMSGFieldAns)

	// 用户公告及生日提醒信息 846
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_NOTICEINFO,tdxNOTICEINFOFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_NOTICEINFO,tdxNOTICEINFOFieldAns)

	// 用户资讯信息反馈 848
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_INFOFEEDBACK,tdxINFOFEEDBACKFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_INFOFEEDBACK,tdxINFOFEEDBACKFieldAns)

	// TQ校验 860
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_TQ_KHJY,tdxTQKHJYFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_TQ_KHJY,tdxTQKHJYFieldAns)

	// 西南证券用户投资顾问信息 862
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_UM_UBROKER,tdxUMUBROKERFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_UM_UBROKER,tdxUMUBROKERFieldAns)

	// 试用(用户)注册 880
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_SYZC_GD,tdxCASYZCGDFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_SYZC_GD,tdxCASYZCGDFieldAns)

	// (详细)信息录入 882
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_XXLR_GD,tdxCAXXLRGDFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_XXLR_GD,tdxCAXXLRGDFieldAns)

	// 试用(用户)激活 884
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_SYJH_GD,tdxCASYJHGDFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_SYJH_GD,tdxCASYJHGDFieldAns)
	
	// 账户校验 886
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_ZHJY_GD,tdxCAZHJYGDFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_ZHJY_GD,tdxCAZHJYGDFieldAns)
	
	// 等级查询 888
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_DJCX_GD,tdxCADJCXGDFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_DJCX_GD,tdxCADJCXGDFieldAns)

	// 可申(请)级(别)查询 890
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_KSJCX_GD,tdxCAKSJCXGDFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_KSJCX_GD,tdxCAKSJCXGDFieldAns)

	// 客户申请(级别) 892
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_KHSQ_GD,tdxCAKHSQGDFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_KHSQ_GD,tdxCAKHSQGDFieldAns)

	// 用户资讯权限 894
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_YHZXQX_GD,tdxCAYHZXQXFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_YHZXQX_GD,tdxCAYHZXQXFieldAns)

	// 用户权限注销 896
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_YHQXZX,tdxCAYHQXZXFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_YHQXZX,tdxCAYHQXZXFieldAns)

	// 查询登陆历史 898
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_CXDLLS,tdxCACXDLLSFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_CXDLLS,tdxCACXDLLSFieldAns)

 	// 安全功能申请 4200
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_AQGNSQ,tdxCAAQGNSQFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_AQGNSQ,tdxCAAQGNSQFieldAns)

	//安全功能撤销 4202
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_AQGNCX,tdxCAAQGNCXFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_AQGNCX,tdxCAAQGNCXFieldAns)

	// 密码保护问题校验 4204
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_MMBHWTJY,tdxCAMMBHWTJYFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_MMBHWTJY,tdxCAMMBHWTJYFieldAns)

	// 获取挑战坐标 4206
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_GETTZZB,tdxCAGETTZZBFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_GETTZZB,tdxCAGETTZZBFieldAns)

	// 注销矩阵卡 4208
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_ZXJZK,tdxCAZXJZKFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_ZXJZK,tdxCAZXJZKFieldAns)

	// 预留问题 4210
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_YLWT,tdxCAYLWTFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_YLWT,tdxCAYLWTFieldAns)

	// 证书申请 4212
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_CERRAREQ,tdxCACERRAREQFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_CERRAREQ,tdxCACERRAREQFieldAns)

	// 证书审核 4214
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_CERAUDIT,tdxCACERAUDITFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_CERAUDIT,tdxCACERAUDITFieldAns)

	// 证书下载 4216
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_CERDOWNLOAD,tdxCACERDOWNLOADFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_CERDOWNLOAD,tdxCACERDOWNLOADFieldAns)

	// 证书下载确认 4218
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_CERDLCONFIRM,tdxCACERDLCONFIRMFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_CERDLCONFIRM,tdxCACERDLCONFIRMFieldAns)
	
	// 添加用户信息 4220
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_ADDYHXX,tdxCAADDYHXXFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_ADDYHXX,tdxCAADDYHXXFieldAns)

	// 修改用户信息 4222
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_XGYHXX,tdxCAXGYHXXFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_XGYHXX,tdxCAXGYHXXFieldAns)

	// 查询用户信息 4224
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_CXYHXX,tdxCACXYHXXFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_CXYHXX,tdxCACXYHXXFieldAns)

	// 获取手机验证码 4226
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_GETYZM,tdxCAGETYZMFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_GETYZM,tdxCAGETYZMFieldAns)

	// 验证码校验 4228
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_YZMJY,tdxCAYZMJYFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_YZMJY,tdxCAYZMJYFieldAns)

	// 其他安全认证校验 4230
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_OTHERCA_BASEFUN,tdxOTHCABASEFUNFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_OTHERCA_BASEFUN,tdxOTHCABASEFUNFieldAns)

	// 查询密码保护问题 4232
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_MMBHWTCX,tdxCAMMBHWTCXFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_MMBHWTCX,tdxCAMMBHWTCXFieldAns)

	// 修改密码保护问题 4234
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_XGMMBHWT,tdxCAXGMMBHWTFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_XGMMBHWT,tdxCAXGMMBHWTFieldAns)

	// 修改预留问题 4236
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_XGYLWT,tdxCAXGYLWTFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_XGYLWT,tdxCAXGYLWTFieldAns)

	// 密码保护问题列表查询 4238
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_PWDPROTQUEQU,tdxPWDPROTQUEQUFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_PWDPROTQUEQU,tdxPWDPROTQUEQUFieldAns)

	// 申请密码保护问题 4240
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_APPLYPWDQA,tdxAPPLYPWDQAFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_APPLYPWDQA,tdxAPPLYPWDQAFieldAns)

	// 申请机器特征码绑定 4242
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_BINDMACHINE,tdxBINDINFOFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_BINDMACHINE,tdxBINDINFOFieldAns)

	// 查询绑定信息 4244
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_QUEBINDINFO,tdxQUEBINDINFOFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_QUEBINDINFO,tdxQUEBINDINFOFieldAns)

	// 取消绑定信息 4246
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_CANCELBIND,tdxCANCELBINDFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_CANCELBIND,tdxCANCELBINDFieldAns)

	// 安全申请状态查询 4248
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_SAFEMODQUE,tdxSAFEMODQUEFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_SAFEMODQUE,tdxSAFEMODQUEFieldAns)

	// 核销用户安全级别 4250
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_ABUSERLV,tdxABUSERLVFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_ABUSERLV,tdxABUSERLVFieldAns)

	// 用户离线 4252
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_CA_USERLOGOUT, tdxUSERLOGOUTFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_CA_USERLOGOUT, tdxUSERLOGOUTFieldAns)

	// 用户在线心跳 4254
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_CA_USERALIVE, tdxUSERALIVEFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_CA_USERALIVE, tdxUSERALIVEFieldAns)

	// 取消用户级别 4256
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_CA_CANCELLV, tdxCANCELLVFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_CA_CANCELLV, tdxCANCELLVFieldAns)

	// 获取产品名称 4258
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_CA_GETPROINFO, tdxGETPROINFOFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_CA_GETPROINFO, tdxGETPROINFOFieldAns)

	// 注册用户 4280
 	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_CA_REGUSER, tdxREGUSERFieldReq)
 	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_CA_REGUSER, tdxREGUSERFieldAns)
	
	// 修改注册密码 4282
 	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_CA_ALTERREGPWD, tdxALTERREGPWDFieldReq)
 	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_CA_ALTERREGPWD, tdxALTERREGPWDFieldAns)
	// 单点登陆令牌操作 4284
 	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_CA_SSO, tdxSSOFieldReq)
 	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_CA_SSO, tdxSSOFieldAns)
	// 单点登陆根据令牌取用户信息 4286
 	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_CA_SSOYHXX, tdxSSOYHXXFieldReq)
 	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_CA_SSOYHXX, tdxSSOYHXXFieldAns)
	// 证书吊销
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_CA_CERDEL, tdxCERDELFieldReq)
 	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_CA_CERDEL, tdxCERDELFieldAns)
	// 动态口令同步
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_CA_OTPSYN, tdxOTPSYNFieldReq)
 	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_CA_OTPSYN, tdxOTPSYNFieldAns)
	// 检查数据一致性
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_CA_CHECKRECORD, tdxCHECKRECORDFieldReq)
 	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_CA_CHECKRECORD, tdxCHECKRECORDFieldAns)
	// 用户认证 4294
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_CA_PAAUTH, tdxPAAUTHFieldReq)
 	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_CA_PAAUTH, tdxPAAUTHFieldAns)
	// 投顾诊断报告 4296
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_CA_ACCREPORT, tdxPAACCREPORTFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_CA_ACCREPORT, tdxPAACCREPORTFieldAns)
	// OTP豁免		4298
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_CA_OTPTEMP, tdxOTPTEMPFieldReq)
 	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_CA_OTPTEMP, tdxOTPTEMPFieldAns)
	// 获取核新手机验证码 4300
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_OTHERCA_GETYZM, tdxOTHCAGETYZMFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_OTHERCA_GETYZM, tdxOTHCAGETYZMFUNFieldAns)
	// 自选股上传下载
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_OPMYSTOCK, tdxOPMYSTOCKFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_OPMYSTOCK, tdxOPMYSTOCKFUNFieldAns)

	// 找回用户密码 4304
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_FETCHPWD, tdxFETCHPWDFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_FETCHPWD, tdxFETCHPWDFUNFieldAns)

	// 注册用户信息查询 4310
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_QUERYREGUDATA, tdxQUERYREGUDATAFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_QUERYREGUDATA, tdxQUERYREGUDATAFUNFieldAns)

	// 找回用户帐号 4306
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_FETCHUSERACCOUNT, tdxFETCHUSERACCOUNTFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_FETCHUSERACCOUNT, tdxFETCHUSERACCOUNTFUNFieldAns)

	// 积分查询
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_QUERYSCORE, tdxQUERYSCOREFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_QUERYSCORE, tdxQUERYSCOREFUNFieldAns)

	// 获取激活码 4312
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_GETACTIVECODE, tdxGETACTIVECODEFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_GETACTIVECODE, tdxGETACTIVECODEFUNFieldAns)

	// 安全功能查询 4500
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_QRYSCFUNC, tdxQRYSCFUNCFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_QRYSCFUNC, tdxQRYSCFUNCFUNFieldAns)

	// 开启/关闭安全功能 4502
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_SWITCHSCFUNC, tdxSWITCHSCFUNCFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_SWITCHSCFUNC, tdxSWITCHSCFUNCFUNFieldAns)

	// 统一认证 4504
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_UNIAUTH, tdxUNIAUTHFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_UNIAUTH, tdxUNIAUTHFUNFieldAns)

	// 申请认证口令 4506
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_REQAPWD, tdxREQAPWDFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_REQAPWD, tdxREQAPWDFUNFieldAns)

	// 修改认证口令 4508
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_MODAPWD, tdxMODAPWDFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_MODAPWD, tdxMODAPWDFUNFieldAns)

	// 重置认证口令 4510
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_RESETAPWD, tdxRESETAPWDFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_RESETAPWD, tdxRESETAPWDFUNFieldAns)

	// 同步OTP 4512
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_SYNOTP, tdxSYNOTPFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_SYNOTP, tdxSYNOTPFUNFieldAns)
	
	// 获取证书签名码 4514
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_GETCSIGNKEY, tdxGETCSIGNKEYFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_GETCSIGNKEY, tdxGETCSIGNKEYFUNFieldAns)

	// 更新证书 4516
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_UPDCERT, tdxUPDCERTFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_UPDCERT, tdxUPDCERTFUNFieldAns)

	// 获取手机动态码 4518
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_GETCCODE, tdxGETCCODEFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_GETCCODE, tdxGETCCODEFUNFieldAns)

	// 授权计算机 4520
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_PERMITMACHINE, tdxPERMITMACHINEFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_PERMITMACHINE, tdxPERMITMACHINEFUNFieldAns)

	// 解除计算机授权 4522
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_FREEMACHINE, tdxFREEMACHINEFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_FREEMACHINE, tdxFREEMACHINEFUNFieldAns)

	// 查询授权 4524
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_QRYPERMITION, tdxQRYPERMITIONFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_QRYPERMITION, tdxQRYPERMITIONFUNFieldAns)

	// 更新预留信息 4526
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_UPDSELFINFO, tdxUPDSELFINFOFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_UPDSELFINFO, tdxUPDSELFINFOFUNFieldAns)
		
	// 查询用户常用信息 4528
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_QRYUSERCOMMON, tdxQRYUSERCOMMONFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_QRYUSERCOMMON, tdxQRYUSERCOMMONFUNFieldAns)
		
	// 用户资料查询 4530
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_QRYUDATA, tdxQRYUDATAFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_QRYUDATA, tdxQRYUDATAFUNFieldAns)
		
	// 更新用户资料 4532
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_UPDUDATA, tdxUPDUDATAFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_UPDUDATA, tdxUPDUDATAFUNFieldAns)
		
	// 关键操作查询 4534
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_QRYIMPOTOP, tdxQRYIMPOTOPFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_QRYIMPOTOP, tdxQRYIMPOTOPFUNFieldAns)
		
	// 关键操作记录 4536
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_RCDIMPOTOP, tdxRCDIMPOTOPFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_RCDIMPOTOP, tdxRCDIMPOTOPFUNFieldAns)
		
	// 认证历史查询 4538
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_QRYAUTHHIS, tdxQRYAUTHHISFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_QRYAUTHHIS, tdxQRYAUTHHISFUNFieldAns)
		
	// 密码保护问题申请 4540
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_REQQAPROT, tdxREQQAPROTFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_REQQAPROT, tdxREQQAPROTFUNFieldAns)
		
	// 密码保护问题修改 4542
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_MODQAPROT, tdxMODQAPROTFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_MODQAPROT, tdxMODQAPROTFUNFieldAns)
		
	// 密码保护校验 4544
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_AUTHQAPROT, tdxAUTHQAPROTFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_AUTHQAPROT, tdxAUTHQAPROTFUNFieldAns)
	
	// 应急密码 4546
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_RESVPWD, tdxRESVPWDFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_RESVPWD, tdxRESVPWDFUNFieldAns)

	// 请求服务器签名信息 4548
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_CONSIS, tdxCONSISFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_CONSIS, tdxCONSISFUNFieldAns)
	
END_STRUCT_FIELD_DEF(tdxCommonStructFieldInfo)


// 日志查看字典定义
BEGIN_STRUCT_FIELD_DEF(tdxRZStructFieldInfo)

	// (日志)客户校验 100
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KHJY,tdxRZKHJYFieldReq)

	// (日志)取缓存信息 112
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CACHE,tdxRZCACHEFieldReq)

	// (日志)股东查询 1122
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_GDCX,tdxRZGDCXFieldReq)

	// (日志)银行信息 908
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YHXX,tdxRZYHXXFieldReq)

	// (日志)修改密码 106
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XGMM,tdxRZXGMMFieldReq)

	// 客户操作记录查询 1002
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_RZ_KHCZJLCX,tdxRZKHCZJLCXFieldReq)

	// 账号申请 1004
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_RZ_ZHSQ,tdxRZZHSQFieldReq)

	// 账号冻结解冻 1006
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_RZ_ZHDJJD,tdxRZZHDJJDFieldReq)

	// 查询统计分析 1008
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_RZ_CXTJFX,tdxRZCXTJFXFieldReq)

	// 启动与关闭查询 1010
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_RZ_QDYGBCX,tdxRZQDYGBCXFieldReq)

	// 后台繁忙程度 1012
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_RZ_HTFMCD,tdxRZHTFMCDFieldReq)

	// 后台超负荷查询 1014
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_RZ_HTCFHCX,tdxRZHTCFHCXFieldReq)

	// 风险IP排名 1016
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_RZ_FXIPPM,tdxRZFXIPPMFieldReq)

	// 风险账号 1018
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_RZ_FXZH,tdxRZFXZHFieldReq)

	// 风险详细信息 1020
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_RZ_FXXXXX,tdxRZFXXXXXFieldReq)

	// 后台繁忙程度详细 1022
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_RZ_HTFMCDXX,tdxRZHTFMCDXXFieldReq)

	// 交易中心IP 1024
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_RZ_TCIP,tdxRZTCIPFieldReq)
	
END_STRUCT_FIELD_DEF(tdxCommonStructFieldInfo)

#pragma pack()
#endif
