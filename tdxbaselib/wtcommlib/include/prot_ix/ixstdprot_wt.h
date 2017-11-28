//////////////////////////////////////////////////////////////////////////
// 创建日期:2006/07/20
// 功能说明:标准数据字典字段号以及功能号定义
//			本文结构
//				Part.I    基本定义限制
//				Part.II   数据类型
//				Part.III  对齐显示类型
//				Part.IV   数据字段ID定义
//				Part.V    功能ID定义
//				Part.VI   帐号类型定义以及其他字典用枚举型标志定义
//				Part.VII  基本限制字段
//				Part.VIII 客户端类型
//				Part.IX   客户端支持的安全级别以及认证方式
//				Part.X    功能类型定义
//				Part.XI   DLL券商ID定义
//				Part.XII  市场信息结构
//				Part.XIII 功能调用接口800
#ifndef  __IX_STDPROT_WT__H__
#define  __IX_STDPROT_WT__H__
#ifdef WIN32
#pragma warning (push)			// 移植到VS2005
#pragma warning (disable:4819)	// 禁用UNICODE检测
#endif


//---------------------------------------------------------------------------
// Part.I 基本定义限制
//---------------------------------------------------------------------------

#define TDX_FID_SYS_NORMAL_FIRST		    (50)	// 系统常规字段开始ID
#define TDX_FID_SYS_NORMAL_LAST			(5050-1)	// 系统常规字段结束ID
#define TDX_FID_CLIENT_INNER_FIRST		  (5050)	// 客户端内部字段开始ID
#define TDX_FID_CLIENT_INNER_LAST		(5250-1)	// 客户端内部字段结束ID
#define TDX_FID_SYS_CACHE_FIRST			  (5250)	// 系统缓存字段开始ID
#define TDX_FID_SYS_CACHE_LAST			(5300-1)	// 系统缓存字段结束ID
#define TDX_FID_ITQ_NORMAL_FIRST		  (5300)	// ITQ(智能委托查询)常规字段开始ID
#define TDX_FID_ITQ_NORMAL_LAST         (5450-1)    // ITQ(智能委托查询)常规字段结束ID
#define TDX_FID_ITQ_CACHE_FIRST			  (5450)	// ITQ(智能委托查询)缓存字段开始ID
#define TDX_FID_ITQ_CACHE_LAST			(5500-1)    // ITQ(智能委托查询)缓存字段结束ID
#define TDX_FID_SDK_NORMAL_FIRST		  (5500)	// SDK常规字段开始ID
#define TDX_FID_SDK_NORMAL_LAST			(5950-1)	// SDK常规字段结束ID
#define TDX_FID_SDK_CACHE_FIRST			  (5950)	// SDK缓存字段开始ID
#define TDX_FID_SDK_CACHE_LAST			(6000-1)	// SDK缓存字段结束ID
#define TDX_FID_MAXID					  (6000)	// 最大字段ID

#define TDX_ID_FUNC_SYSFIRST			   (100)	// 系统功能开始ID
#define TDX_ID_FUNC_ITQFRIST			  (5300)	// ITQ(智能委托查询)功能开始ID
#define TDX_ID_FUNC_SDKFRIST			  (5500)	// SDK功能开始ID
#define TDX_ID_FUNC_MAXID				  (6000)	// 最大功能ID


//---------------------------------------------------------------------------
// Part.II 数据类型
//---------------------------------------------------------------------------
#define	TDX_DT_CHAR							1		
#define TDX_DT_SHORT						2
#define TDX_DT_LONG							3
#define TDX_DT_LONGLONG						4
#define TDX_DT_FLOAT						5
#define TDX_DT_DOUBLE						6
#define TDX_DT_LONGDOUBLE					7
#define TDX_DT_DATE							8
#define	TDX_DT_TIME							9
#define	TDX_DT_STRING						10
#define TDX_DT_MEMO							11
#define TDX_DT_BINARY						12
#define TDX_DT_RECORDSET					13



//---------------------------------------------------------------------------
// Part.III 对齐显示类型
//---------------------------------------------------------------------------
#define TDX_DISP_TOP						0x00
#define TDX_DISP_LEFT						0x00
#define TDX_DISP_CENTER						0x01
#define TDX_DISP_RIGHT						0x02
#define TDX_DISP_VCENTER					0x04
#define TDX_DISP_BOTTOM						0x08
#define TDX_DISP_NONE						TDX_DISP_RIGHT


//---------------------------------------------------------------------------
// Part.IV 数据字段ID定义
//---------------------------------------------------------------------------

// 基本类
#define TDX_ID_PARAM_YHSXX					85			// (参数)印花税下限
#define TDX_ID_PARAM_SXFXX					86			// (参数)手续费下限
#define TDX_ID_PARAM_GHFXX					87			// (参数)过户费下限
#define TDX_ID_PARAM_QTJEFXX				88			// (参数)其他金额费下限
#define TDX_ID_PARAM_QTSLFXX				89			// (参数)其他数量费下限
#define TDX_ID_ZQJYBS						90			// 证券交易标识 '1'为不支持 其他为支持
#define TDX_ID_PARAM_CBJE					91			// (参数)成本金额
#define TDX_ID_PARAM_CBSL					92			// (参数)成本数量
#define TDX_ID_PARAM_YHSL					93			// (参数)印花税率
#define TDX_ID_PARAM_SXFL					94			// (参数)手续费率
#define TDX_ID_PARAM_GHFL					95			// (参数)过户费率
#define TDX_ID_PARAM_QTJEFL					96			// (参数)其他金额费率
#define TDX_ID_PARAM_QTSLFL					97			// (参数)其他数量费率
#define TDX_ID_FQSL							98			// 放弃数量
#define TDX_ID_MC							99			// 名次

#define TDX_ID_SCFLAG						100			// 交易所代码
#define TDX_ID_SCNAME						101			// 交易所名称
#define TDX_ID_YYB							102			// 营业部代码
#define TDX_ID_YYBMC						103			// 营业部名称
#define TDX_ID_TDX_OEM_FLAG					104			// #define TDX_ID_TDX_OEM_FLAG				7001
#define TDX_ID_JYYDM						105			// 交易员代码
#define TDX_ID_LXRXM						106			// 联系人姓名
#define TDX_ID_LXFS							107			// 联系方式
#define TDX_ID_NC							108			// 昵称
#define TDX_ID_LMQX							109			// 栏目权限
#define TDX_ID_OP_WTFS						110			// 委托方式
#define TDX_ID_OP_GYDM						111			// 柜员代码
#define TDX_ID_OP_GYMM						112			// 柜员密码
#define TDX_ID_CZBZ							113			// 操作标志
#define TDX_ID_CZZT							114			// 操作状态
#define TDX_ID_HZHGZT						115			// 合作回购状态
#define TDX_ID_ZDJYBZ						116			// 指定交易（0：未指定 1:指定）
#define TDX_ID_SQKTWZ						117			// 申请开通的网址
#define TDX_ID_HZHGDM						118			// 合作回购代码
#define TDX_ID_HZPSDM						119			// 合作配售代码
#define TDX_ID_KHH							120			// 客户号
#define TDX_ID_ZJZH							121			// 资金帐号
#define TDX_ID_KHMC							122			// 客户名称
#define TDX_ID_GDDM							123			// 股东代码
#define TDX_ID_GDMC							124			// 股东名称		
#define TDX_ID_ZHLB							125			// 帐号类别
#define TDX_ID_KSRQ							126			// 开始日期
#define TDX_ID_ZZRQ							127			// 终止日期
#define TDX_ID_USERPHONE					128			// 用户联系方式
#define TDX_ID_USEREMAIL					129			// 用户EMAIL
#define TDX_ID_MMBZ							130			// 买卖标志  0:买入 1:卖出 2:撤单 3:撤买 4:撤卖
#define	TDX_ID_MMBZSM						131			// 买卖标志说明
#define TDX_ID_BZ							132			// 币种 0:RMB 1:MY 2:GB
#define TDX_ID_JYDW							133			// 交易单位	 0:股 1:手 2:张
#define TDX_ID_JYMM							134			// 交易密码
#define TDX_ID_ZJMM							135			// 资金密码
#define TDX_ID_XJYMM						136			// 新交易密码
#define TDX_ID_XZJMM						137			// 新资金密码
#define TDX_ID_TXMM							138			// 通讯密码
#define TDX_ID_SECURETYPE					139			// 安全方式
#define TDX_ID_ZQDM							140			// 证券代码
#define TDX_ID_ZQMC							141			// 证券名称
#define TDX_ID_WTRQ							142			// 委托日期	YYYYMMDD
#define TDX_ID_WTSJ							143			// 委托时间 HHMMSS
#define TDX_ID_WTSL							144			// 委托数量
#define TDX_ID_WTJG							145			// 委托价格
#define TDX_ID_WTBH							146			// 委托编号
#define TDX_ID_ZTSM							147			// 状态说明
#define TDX_ID_WTJE							148			// 委托金额
#define TDX_ID_RETINFO						149			// 返回信息,(151 字节)
#define TDX_ID_CJRQ							150			// 成交日期
#define TDX_ID_CJSJ							151			// 成交时间 
#define TDX_ID_CJSL							152			// 成交数量
#define TDX_ID_CJJG							153			// 成交价格
#define TDX_ID_CJJE							154			// 成交金额
#define TDX_ID_CJBH							155			// 成交编号
#define TDX_ID_HZPSZT						156			// 合作配售状态
#define TDX_ID_HFBZ							157			// 合法标志
#define TDX_ID_DFMM							158			// 对方密码(金证柜台里面的证券资金帐号对应的密码,也就是银证转帐的地方的资金密码)
#define TDX_ID_HFBZSM						159			// 合法标志说明
#define TDX_ID_DJSL							160			// 冻结数量
#define TDX_ID_DJZJ							161			// 冻结资金
#define TDX_ID_CDSL							162			// 撤单数量
#define TDX_ID_CDBZSM						163			// 撤单标志说明
#define TDX_ID_LESSPRESSURE					164			// 银证通用户减轻柜台资金查询请求压力
#define TDX_ID_FIRSTZJCX					165			// 银证通用户第一次登陆查询资金
#define TDX_ID_WTFS							166			// (委托方式)市价委托方式
#define TDX_ID_CDBZ							167			// 撤单标志 1撤单  20061108 gxzq 当日成交查询返回隐藏的撤单标志给客户端,让客户端可以选择是否过滤掉撤单费单等非正常成交记录
#define	TDX_ID_KCDBZ						168			// 可撤单标志
#define	TDX_ID_LSH							169			// 流水号
#define TDX_ID_PHRQ							170			// 配号日期
#define TDX_ID_QSPH							171			// 起始配号
#define	TDX_ID_PHSL							172			// 配号数量
#define TDX_ID_XWDM							173			// 席位代码
#define TDX_ID_ZQS							174			// 中签数
#define TDX_ID_PHSLPHCX						175			// 配号数量(东莞的特殊处理)
#define TDX_ID_ZQRQ							176			// 中签日期
#define TDX_ID_QZLX							177			// 权证类型
#define TDX_ID_XQFS							178			// 行权方式
#define TDX_ID_XQBL							179			// 行权比例
#define TDX_ID_JSFS							180			// 结算方式
#define	TDX_ID_FXBZ							181			// 风险标志
#define	TDX_ID_FXSM							182			// 风险说明
#define	TDX_ID_JGRQ							183			// 交割日期
#define	TDX_ID_KHLBSM						184			// 客户类别说明
#define	TDX_ID_KHXZSM						185			// 客户性质说明
#define	TDX_ID_KHZTSM						186			// 客户状态说明
#define TDX_ID_ZXJYGS						187			// 最小交易股数
#define	TDX_ID_SHGD							188			// 上海股东
#define	TDX_ID_SZGD							189			// 深圳股东
#define TDX_ID_QZKTBZ						190			// 权证开通标志
#define TDX_ID_SGRDM						191			// 收购人代码
#define TDX_ID_YYSL							192			// 要约数量
#define TDX_ID_SBSL							193			// 申报数量
//#define TDX_ID_WTFS						166			// (委托方式)市价委托方式
#define TDX_ID_WTFSSM						194			// 市价委托方式说明
#define	TDX_ID_XTXMM						195			// 新通讯密码
#define TDX_ID_DZDLX						196			// 对帐单类型
#define TDX_ID_XXSL							197			// 选项数量
#define TDX_ID_DQCB							198			// 当前成本
#define TDX_ID_ZTSL							199			// 在途数量

#define TDX_ID_ZQSL							200			// 证券数量
#define TDX_ID_KMSL							201			// 可卖数量
#define TDX_ID_CBJ							202			// 成本价
#define TDX_ID_ZXJ							203			// 最新价
#define TDX_ID_FDYK							204			// 浮动盈亏
#define TDX_ID_ZXSZ							205			// 最新市值
#define TDX_ID_YJ							206			// 佣金
#define TDX_ID_KHF							207			// 过户费
#define TDX_ID_CJF							208			// 成交费
#define TDX_ID_JSF							209			// 结算费
#define TDX_ID_YHS							210			// 印花税
#define TDX_ID_ZDKM							211			// 最大可买
#define TDX_ID_SXF							212			// 手续费(期货手续费:小于零时为交易金额的万分比，大于零为元/手)
#define TDX_ID_GPLX							213			// 股票类型
#define TDX_ID_GTZDKMBS						214			// 取柜台最大可买标识
#define TDX_ID_DRMRSL						215			// 当日买入数量
#define TDX_ID_GPLBP						216			// 股票篮买入价
#define TDX_ID_GPLBV						217			// 股票篮买入量
#define TDX_ID_GPLSP						218			// 股票篮卖出价
#define TDX_ID_GPLSV						219			// 股票篮卖出量
#define TDX_ID_KHQXDM						220			// 客户权限代码
#define TDX_ID_KHQXMC						221			// 客户权限名称
#define TDX_ID_BBJ							222			// 保本价
#define TDX_ID_YWTSL						223			// 原委托数量
#define TDX_ID_YWTJG						224			// 原委托价格
#define TDX_ID_QTF							225			// 其他费
#define TDX_ID_ZXMRBDJW						226			// 最小买入变动价位
#define TDX_ID_ZXMCBDJW						227			// 最小卖出变动价位
#define TDX_ID_ZCZJZH						228			// 转出资金帐号
#define TDX_ID_ZRZJZH						229			// 转入资金帐号
#define TDX_ID_YKBL							230			// 盈亏比例
#define	TDX_ID_ZJZHEX						231			// 广发附属资金帐号
#define	TDX_ID_SXYK							232			// 实现盈亏
#define	TDX_ID_TBYK							233			// 摊薄盈亏
#define	TDX_ID_LX							234			// 类型
#define	TDX_ID_CJDF							235			// 成交单费
#define	TDX_ID_WTDF							236			// 委托单费
#define TDX_ID_JJRDM						237			// 经纪人代码
#define TDX_ID_ZHZT							238			// 帐户状态
#define TDX_ID_KGDBZ						239			// 可改单标志
#define TDX_ID_MAILADDRESS					240			// 邮寄地址
#define TDX_ID_YDXH							241			// 约定序号
#define TDX_ID_DFXWDM						242			// 对方席位代码
#define TDX_ID_DFZJZH						243			// 对方资金帐号
#define TDX_ID_DFGDDM						244			// 对方股东代码
#define TDX_ID_DFZHLB						245			// 对方帐号类别
#define TDX_ID_ZZHBZ						246			// 主帐号标志
#define TDX_ID_SBXH							247			// 申报序号
#define TDX_ID_LMDM							248			// 栏目代码
#define TDX_ID_LMMC							249			// 栏目名称
#define TDX_ID_TSXX0						250			// 提示信息0
#define TDX_ID_TSXX1						251			// 提示信息1
#define TDX_ID_TSXX2						252			// 提示信息2
#define TDX_ID_TSXX3						253			// 提示信息3
#define TDX_ID_TSXX4						254			// 提示信息4
#define TDX_ID_TSXX5						255			// 提示信息5
#define TDX_ID_TSXX6						256			// 提示信息6
#define TDX_ID_TSXX7						257			// 提示信息7
#define TDX_ID_TSXX8						258			// 提示信息8
#define TDX_ID_TSXX9						259			// 提示信息9

// (服务)"资金流水"应答字段[260 ~ 272]
#define TDX_ID_ZJLS_FSRQ					260			// 发生日期
#define TDX_ID_ZJLS_FSSJ					261			// 发生时间
#define TDX_ID_ZJLS_YWDM					262			// 业务代码
#define TDX_ID_ZJLS_YWMC					263			// 业务名称
#define TDX_ID_ZJLS_HBDM					264			// 货币代码
#define TDX_ID_ZJLS_FSJE					265			// 发生金额
#define TDX_ID_ZJLS_SYJE					266			// 剩余金额
#define TDX_ID_ZJLS_ZQDM					267			// 证券代码
#define TDX_ID_ZJLS_ZQMC					268			// 证券名称
#define TDX_ID_ZJLS_FSJG					269			// 发生价格
#define TDX_ID_ZJLS_FSSL					270			// 发生数量
#define TDX_ID_ZJLS_SYSL					271			// 剩余数量
#define TDX_ID_ZJLS_GDDM					272			// 股东代码

#define	TDX_ID_OTCJYBS						276			// 支持OTC交易用户标志
#define TDX_ID_DFBZ							277			// 对方币种
#define TDX_ID_DQHL							278			// 当前汇率
#define	TDX_ID_JYGF							279			// 交易规费
#define	TDX_ID_ZTZJ							280			// 在途资金
#define	TDX_ID_XYJYBS						281			// 支持信用交易用户标志
#define	TDX_ID_SFCGBS						282			// 三方存管标识
#define TDX_ID_ZZFS							283			// 转帐方式
#define TDX_ID_ZZQD							284			// 转帐渠道
#define TDX_ID_ZZBH							285			// 转帐编号
#define TDX_ID_FPYH							286			// 发票银行
#define TDX_ID_ZPBH							287			// 支票编号
#define TDX_ID_ZJCJSL						288			// 最近成交数量
#define TDX_ID_ZJCDSL						289			// 最近撤单数量
#define TDX_ID_KHBS							290			// 客户标识
#define TDX_ID_ZDDM							291			// 字段代码
#define TDX_ID_ZDQZ							292			// 字段取值
#define TDX_ID_YLXX							293			// 预留信息
#define TDX_ID_FJZH							294			// 附加账号
#define TDX_ID_XYJYTSXX						295			// 信用交易提示信息
#define TDX_ID_JZC							296			// 净资产
#define TDX_ID_SGKYS						297			// 申购可用数
#define TDX_ID_DFKHDM						298			// 对方客户代码
#define TDX_ID_DFFZDM						299			// 对方分支代码

#define TDX_ID_ZJYE							300			// 资金余额
#define TDX_ID_KYZJ							301			// 可用资金
#define TDX_ID_KQZJ							302			// 可取资金
#define TDX_ID_OCCURJE						303			// 发生金额
#define TDX_ID_POSTJE						304			// 剩余金额	
#define TDX_ID_ZY							305			// 摘要
#define TDX_ID_YWMC							306			// 业务名称
#define TDX_ID_YWDM							307			// 业务代码
#define TDX_ID_MRDJZJ						308			// 买入冻结资金
#define TDX_ID_YZT_YHXZTS					309			// 选择银行提市标志
#define TDX_ID_GTZZC						310			// 柜台总资产
#define TDX_ID_CJLX							311			// 成交类型
#define	TDX_ID_JYDJZJ						312			// 交易冻结资金
#define	TDX_ID_YCDJZJ						313			// 异常冻结资金
#define	TDX_ID_ZTKYZJ						314			// 在途可用资金
#define	TDX_ID_XJKQZJ						315			// 现金可取资金
#define	TDX_ID_ZPKQZJ						316			// 支票可取资金
#define	TDX_ID_KZZJ							317			// 可转资金
#define	TDX_ID_LXJE							318			// 利息金额
#define	TDX_ID_LXS							319			// 利息税
#define	TDX_ID_SYSL							320			// 剩余数量
#define	TDX_ID_FJF							321			// 附加费
#define	TDX_ID_SXJE							322			// 所需金额
#define	TDX_ID_MMCB							323			// 买卖成本
#define	TDX_ID_MRCB							324			// 买入成本
#define TDX_ID_ZGF							325			// 证管费
#define TDX_ID_FCJL							326			// 分仓基量
#define TDX_ID_ZYK							327			// 总盈亏
#define TDX_ID_TBCBJ						328			// 摊薄成本价
#define TDX_ID_TBBBJ						329			// 摊薄保本价
#define TDX_ID_TBFDYK						330			// 摊薄浮动盈亏
#define TDX_ID_FADM							331			// 方案代码
#define TDX_ID_FAMC							332			// 方案名称
#define TDX_ID_FALX							333			// 方案类型
#define TDX_ID_TPDM							334			// 投票代码
#define TDX_ID_TPJG							335			// 投票结果
#define TDX_ID_CFDM							336			// 成分代码
#define TDX_ID_CFMC							337			// 成分名称
#define TDX_ID_CFQZ							338			// 成分权重(%)
#define TDX_ID_MRXX							339			// 默认选项
#define TDX_ID_XXNR0						340			// 选项内容0
#define TDX_ID_XXNR1						341			// 选项内容1
#define TDX_ID_XXNR2						342			// 选项内容2
#define TDX_ID_XXNR3						343			// 选项内容3
#define TDX_ID_XXNR4						344			// 选项内容4
#define TDX_ID_XXNR5						345			// 选项内容5
#define TDX_ID_XXNR6						346			// 选项内容6
#define TDX_ID_XXNR7						347			// 选项内容7
#define TDX_ID_XXNR8						348			// 选项内容8
#define TDX_ID_XXNR9						349			// 选项内容9
#define TDX_ID_ZZC							350			// 总资产
#define TDX_ID_SYL							351			// 收益率
#define TDX_ID_HYZS							352			// 活跃指数
#define TDX_ID_RMBZZC						353			// 人民币总资产
#define TDX_ID_MYZZC						354			// 美元总资产
#define TDX_ID_GYZZC						355			// 港元总资产
#define TDX_ID_SYLTJRQ						356			// 收益率统计日期
#define TDX_ID_SYLTJSJ						357			// 收益率统计时间
#define TDX_ID_ZZHZYE						358			// 子账户总余额
#define TDX_ID_HGJE							359			// 回购金额
#define TDX_ID_MOCK_ZHTYPE					360			// 账号类型 0:股票 1:期货 2:外汇

#define TDX_ID_RQSL							370			// 融券数量(一个融券单位：10000股)
#define TDX_ID_RQJG							371			// 融券价格
#define TDX_ID_RQZQ							372			// 融券周期
#define TDX_ID_RQCZLX						374			// 融券操作类型(0:融券 1:还券 2:展期)
#define TDX_ID_RQRQ							375			// 融券日期
#define TDX_ID_RQSJ							376			// 融券时间
#define TDX_ID_HTBH							377			// 合同编号
#define TDX_ID_JDJSJET						378			// 净待交收金额(T日)
#define TDX_ID_JDJSJET1						379			// 净待交收金额(T+1日)
#define TDX_ID_JDJSJET2						380			// 净待交收金额(T+2日)
#define TDX_ID_ZPDJSJE						381			// 支票待交收金额
#define TDX_ID_XYSZ							382			// 信用市值
#define TDX_ID_GJBZQGML						383			// 高级别证券购买力
#define TDX_ID_XYGJBZQGML					384			// 信用高级别证券购买力
#define TDX_ID_DJBZQGML						385			// 低级别证券购买力
#define TDX_ID_XYDJBZQGML					386			// 信用低级别证券购买力

// 开放式基金类
#define TDX_ID_YXSBCS						387			// 有效失败次数
#define TDX_ID_SFFSSM						388			// 收费方式说明
#define	TDX_ID_CPJZ							389			// 产品净值
#define	TDX_ID_LCZH							390			// 理财账户
#define	TDX_ID_CPDM							391			// 产品代码
#define	TDX_ID_CPMC							392			// 产品名称
#define	TDX_ID_CPGSDM						393			// 产品公司代码
#define	TDX_ID_CPGSMC						394			// 产品公司名称
#define	TDX_ID_CPZT							395			// 产品状态
#define	TDX_ID_QRJZ							396			// 前日净值(前一个交易日的净值)
#define	TDX_ID_CPBZ							397			// 产品标志(0:普通基金产品,1:券商理财产品)
#define	TDX_ID_KTBZ							398			// 开通标志
#define	TDX_ID_KFSJJ_LJJZ					399			// 累计净值

#define TDX_ID_KFSJJ_MMBZ					400			// 0:认购 1：申购 2：赎回 3:预约申购 4:预约赎回
#define TDX_ID_KFSJJ_JJGSMC					401			// 基金公司名称
#define TDX_ID_KFSJJ_JJDM					402			// 基金代码
#define	TDX_ID_KFSJJ_JJMC					403			// 基金名称
#define TDX_ID_KFSJJ_JJFE					404			// 基金份额
#define TDX_ID_KFSJJ_JYJE					405			// 交易金额
#define TDX_ID_KFSJJ_JJJZ					406			// 基金净值
#define TDX_ID_KFSJJ_ZHDM					407			// 基金转换代码
#define TDX_ID_KFSJJ_DIVIDENMETHOD			408			// 基金分红方式	    ‘0’-红利转股、‘1’//现金分红、‘2’-利得现金增值再投资、‘3’//-增值现金利得再
#define TDX_ID_KFSJJ_FSRQ					409			// 发生日期
#define TDX_ID_KFSJJ_KYFE					410			// 可用份额
#define TDX_ID_KFSJJ_JJBS					411			// 开放式基金标识 0：不支持 1：支持
#define TDX_ID_KFSJJ_QSSL					412			// 起始数量
#define TDX_ID_KFSJJ_DQSL					413			// 当前数量
#define TDX_ID_KFSJJ_WTFE					414			// 委托份额
#define TDX_ID_KFSJJ_CJFE					415			// 成交份额
#define TDX_ID_KFSJJ_CJJE					416			// 成交金额
#define TDX_ID_KFSJJ_JJZH					417			// 基金帐户
#define TDX_ID_KFSJJ_FXJG					418			// 发行价格
#define TDX_ID_KFSJJ_GRZDRGJE				419			// 个人最低认购金额
#define TDX_ID_KFSJJ_FRZDRGJE				420			// 法人最低认购金额
#define TDX_ID_KFSJJ_ZDCYFE					421			// 最低持有份额
#define TDX_ID_KFSJJ_ZGSHFE					422			// 最高赎回份额
#define TDX_ID_KFSJJ_GRZGCYBL				423			// 个人最高持有比例
#define TDX_ID_KFSJJ_FRZGCYBL				424			// 法人最高持有比例
#define TDX_ID_KFSJJ_JJZT					425			// 基金状态
#define TDX_ID_KFSJJ_JJGSDM					426			// 基金公司代码
#define TDX_ID_KFSJJ_FXZS					427			// 发行总数
#define TDX_ID_KFSJJ_ZDSHFE					428			// 最低赎回份额
#define TDX_ID_SFFS							429			// 收费方式
#define TDX_ID_KFSJJ_JGZGBL					430			// 机构最高比例
#define TDX_ID_KFSJJ_GRZGBL					431			// 个人最高比例
#define TDX_ID_KFSJJ_GRZGRGZJ				432			// 个人最高认购金额
#define TDX_ID_KFSJJ_FRZGRGZJ				433			// 法人最高认购金额
#define TDX_ID_KFSJJ_GRSCSGZDZJ				434			// 个人首次申购最低资金
#define TDX_ID_KFSJJ_FRSCSGZDZJ				435			// 法人首次申购最低资金
#define TDX_ID_KFSJJ_GRZJSGZDZJ				436			// 个人追加申购最低资金
#define TDX_ID_KFSJJ_FRZJSGZDZJ				437			// 法人追加申购最低资金
#define TDX_ID_KFSJJ_GRJJZSSHFE				438			// 个人基金最少赎回份额
#define TDX_ID_KFSJJ_FRJJZSSHFE				439			// 法人基金最少赎回份额
#define TDX_ID_KFSJJ_GRJJZSZHFE				440			// 个人基金最少转换份额
#define TDX_ID_KFSJJ_FRJJZSZHFE				441			// 法人基金最少转换份额
#define TDX_ID_KFSJJ_TADM					442			// TA 代码
#define TDX_ID_KFSJJ_GTGSBZ					443			// 开放式基金柜台公司标志
#define TDX_ID_KFSJJ_FHFSDM					444			// 分红方式代码
#define	TDX_ID_KFSJJ_FHFSMC					445			// 分红方式名称
#define TDX_ID_LSDJ							446			// 临时冻结
#define TDX_ID_MCWTSL						447			// 卖出冻结
#define TDX_ID_KFSJJ_PZDM					448			// 申购品种代码
#define TDX_ID_KFSJJ_MYKKRQ					449			// 每月扣款日期
#define TDX_ID_KHTYPE						450			// 开户类别，个人，机构
#define TDX_ID_KFSJJ_DQSGNS					451			// 申购年数
#define TDX_ID_ZJLB							452			// 证件类别
#define TDX_ID_JYZH							453			// 交易帐户
#define TDX_ID_ZJHM							454			// 证件号码
#define TDX_ID_MOBILEPHONE					455			// 移动电话
#define TDX_ID_HOMEPHONE					456			// 住宅电话
#define TDX_ID_FAX							457			// 传真
#define TDX_ID_EDU							458			// 教育程度
#define TDX_ID_SALARY						459			// 年收入
#define TDX_ID_XLYZT_DLSGFLAG				460			// 代理申购标志   0：未开通，1：开通 
#define TDX_ID_XLYZT_DLPGFLAG				461			// 代理配股标志   0：未开通，1：开通 
#define TDX_ID_XLYZT_DLPSFLAG				462			// 代理配售标志   0：未开通，1：开通 
#define TDX_ID_WORKPHONE					463			// 单位电话
#define TDX_ID_NAME							464			// 姓名
#define TDX_ID_VOCATION						465			// 职业
#define TDX_ID_FHBZ							466			// 分红标志
#define TDX_ID_DZDBZ						467			// 对帐单标志
#define TDX_ID_SHFS							468			// 赎回方式
#define TDX_ID_FHBL							469			// 分红比例
#define TDX_ID_FHRQ							470			// 分红日期
#define TDX_ID_FHJE							471			// 分红金额
#define TDX_ID_FHSL							472			// 分红数量
#define TDX_ID_MGFHJE						473			// 每股分红金额
#define TDX_ID_ZDBZ							474			// 指定标志
#define TDX_ID_FHFS							475			// 分红方式
#define TDX_ID_KHRQ							476			// 开户日期
#define TDX_ID_KHQC							477			// 客户全称
#define TDX_ID_BPCALL						478			// 寻呼机号
#define TDX_ID_ZBDLJYXX						479			// 周边登录校验信息
#define TDX_ID_KFSJJ_JGZDTZ					480			// 机构最低投资
#define TDX_ID_KFSJJ_GRZDTZ					481			// 个人最低投资
#define TDX_ID_KFSJJ_JGZDZJ					482			// 机构最低追加
#define TDX_ID_KFSJJ_GRZDZJ					483			// 个人最低追加
#define TDX_ID_SPEL_GX_HZXGSGZT				484			// 国信查询合作新股申购状态
#define	TDX_ID_TJRDM						485			// 推荐人代码
#define	TDX_ID_PROVINCE						486			// 省份
#define	TDX_ID_CITY							487			// 城市
#define	TDX_ID_SECTION						488			// 辖区
#define TDX_ID_IDADDRESS					489			// 证件地址
#define TDX_ID_FRDBXM						490			// 法人代表姓名
#define TDX_ID_FRDBZJLX						491			// 法人代表证件类型
#define TDX_ID_FRDBZJHM						492			// 法人代表证件号码
#define TDX_ID_LXRZJLX						493			// 联系人证件类型
#define TDX_ID_LXRZJHM						494			// 联系人证件号码
#define TDX_ID_LXRDH						495			// 联系人电话
#define TDX_ID_DZDJSFS						496			// 对帐单寄送方式
#define TDX_ID_JJDTBZ						497			// 基金定投标志
#define TDX_ID_XSRDM						498			// 销售人代码
#define TDX_ID_XSRMC						499			// 销售人名称

// 模拟期货类	
#define TDX_ID_QHZHBS						500			// 期货账号标识 1:期货帐号 0: 非期货帐号
#define TDX_ID_QHZH							501			// 期货账号
#define TDX_ID_HYDM1						502			// 合约代码1
#define TDX_ID_HYDM2						503			// 合约代码2
#define TDX_ID_HYDM3						504			// 合约代码3
#define TDX_ID_HYDM4						505			// 合约代码4
#define TDX_ID_HYMC1						506			// 合约名称1
#define TDX_ID_HYMC2						507			// 合约名称2
#define TDX_ID_HYMC3						508			// 合约名称3
#define TDX_ID_HYMC4						509			// 合约名称4
#define TDX_ID_HYDM							510			// 合约代码
#define TDX_ID_HYMC							511			// 合约名称
#define TDX_ID_PZ							512			// 品种
#define TDX_ID_KPBZ							513			// 开平标志 0:开仓 1:平仓
#define TDX_ID_TBBZ							514			// 投保标志 0:投机 1:套期保值
#define TDX_ID_JKCFLAG						515			// 今仓标志 0:历史仓 1:今开仓
#define TDX_ID_CJSX							516			// 成交属性
#define TDX_ID_CJSXSM						517			// 成交属性说明
#define TDX_ID_ZHLX							518			// 组合类型
#define TDX_ID_ZHLXSM						519			// 组合类型说明
#define TDX_ID_KCJG							520			// 开仓价
#define TDX_ID_CCSL							521			// 持仓量
#define TDX_ID_KCRQ							522			// 开仓日期
#define TDX_ID_CJJJ							523			// 成交均价
#define TDX_ID_CBJJ							524			// 成本均价
#define TDX_ID_BZJJE						525			// 保证金金额
#define TDX_ID_SXFJE						526			// 手续费金额
#define TDX_ID_MRJJ							527			// 买入均价
#define TDX_ID_CCJJ							528			// 持仓均价
#define TDX_ID_ZHTS							529			// 组合腿数
#define TDX_ID_DJBZJ						530			// 冻结保证金
#define TDX_ID_QCZJ							531			// 期初资金
#define TDX_ID_KHQYZJ						532			// 客户权益资金
#define	TDX_ID_KKCSL						533			// 可开仓数量
#define	TDX_ID_KPCSL						534			// 可平仓数量
#define	TDX_ID_KPJSL						535			// 可平今数量
#define TDX_ID_ZHHYDM						536			// 组合合约代码
#define TDX_ID_ZHHYMC						537			// 组合合约名称
#define TDX_ID_CFJG							538			// 触发价格
#define TDX_ID_MZL							539			// 命中率
#define TDX_ID_JGY							540			// 交割月份
#define TDX_ID_BZJ							541			// 保证金
#define TDX_ID_QHJYDW						542			// 交易单位(吨/手)
#define TDX_ID_QHBJDW						543			// 报价单位(元/吨)
#define TDX_ID_ZXBDJW						544			// 最小变动价位(元/吨)
#define TDX_ID_JGBDFD						545			// 价格波动幅度(小于零时单位为百分比,大于零时单位为元)
#define TDX_ID_BZJBL						546			// 保证金比例
	
#define TDX_ID_QHHQ_KCL						550			// 开仓量(行情)
#define TDX_ID_QHHQ_CCL						551			// 持仓量
#define TDX_ID_QHHQ_QJS						552			// 前结算
#define TDX_ID_QHHQ_ZS						553			// 总手
	
//港股
#define TDX_ID_GGZHBS						580			// 港股账号标识 1:港股帐号 0: 非港股帐号

// 其他交易类	
#define	TDX_ID_ETFBS						600			// ETF标识 0表示不支持， 1表示支持
#define TDX_ID_ETFDM						601			// ETF代码
#define	TDX_ID_ETFMC						602			// ETF名称
#define	TDX_ID_ETFMMBS						603			// 0:申购 1:赎回 2:股票认购 3：现金认购
#define TDX_ID_ETFRGSL						604			// 认购数量
#define TDX_ID_ETFRGJE						605			// 认购金额
#define TDX_ID_PCH							606			// 批次号
#define TDX_ID_ETFXJTDMZ					607			// 现金替代标志 /'0'不允许，'1'允许，'2'必须 
#define TDX_ID_ETFYJBL						608			// 溢价比例
#define TDX_ID_ETFXJTDJE					609			// 现金替代金额
#define TDX_ID_QSRQ							610			// 清算日期
#define TDX_ID_CLDM							611			// 策略代码
#define TDX_ID_CLMC							612			// 策略名称
#define TDX_ID_ZSDM							613			// 指数代码
#define TDX_ID_ZSMC							614			// 指数名称
#define TDX_ID_CDDDSJ						615			// 撤单等待时间
#define TDX_ID_WTDDSJ						616			// 委托等待时间
#define TDX_ID_WTCS							617			// 委托次数
#define TDX_ID_JGBZ							618			// 价格标志
#define TDX_ID_ZDCD							619			// 自动撤单
#define TDX_ID_CFSL							620			// 成分数量
#define TDX_ID_KCSL							621			// 库存数量
#define TDX_ID_BLSL							622			// 保留数量
#define TDX_ID_XJBZ							623			// 现金标志
#define TDX_ID_JSBZ							624			// 结束标志
#define TDX_ID_CJZT							625			// 成交状态
#define TDX_ID_XJTDSM						626			// 现金替代标志说明
#define TDX_ID_QKSL							627			// 缺口数量
#define TDX_ID_XYZJ							628			// 需要资金
#define TDX_ID_ZRKC							629			// 昨日库存
#define TDX_ID_JRMRJE						630			// 今日买入金额
#define TDX_ID_JRMCSL						631			// 今日卖出数量
#define TDX_ID_JRMCJE						632			// 今日卖出金额
#define TDX_ID_MBFE							633			// 目标份额
#define TDX_ID_KSSJ							634			// 开始时间
#define TDX_ID_ZZSJ							635			// 终止时间
#define TDX_ID_CSWTSL						636			// 初始委托数量
#define TDX_ID_ZWTCS						637			// 总委托次数
#define TDX_ID_ZHDM							638			// 组合代码
#define TDX_ID_ZHMC							639			// 组合名称
#define TDX_ID_KZYHZHBM						640			// 扩展银行账户编码
#define TDX_ID_KZYHZHBM1					641			// 扩展银行账户编码1
#define TDX_ID_KZYHZHBM2					642			// 扩展银行账户编码2
#define TDX_ID_KZYHZHBM3					643			// 扩展银行账户编码3
#define TDX_ID_KZYHZHBM4					644			// 扩展银行账户编码4
#define TDX_ID_KZYHZHMC						645			// 扩展银行账户名称
#define TDX_ID_KZYHZHMC1					646			// 扩展银行账户名称1
#define TDX_ID_KZYHZHMC2					647			// 扩展银行账户名称2
#define TDX_ID_KZYHZHMC3					648			// 扩展银行账户名称3
#define TDX_ID_KZYHZHMC4					649			// 扩展银行账户名称4
#define TDX_ID_DJGSDM						650			// 登记公司代码
#define TDX_ID_DJGSJC						651			// 登记公司简称
#define TDX_ID_DJGSQC						652			// 登记公司全称
#define TDX_ID_QZFS							653			// 权重方式
#define TDX_ID_DWSZ							654			// 单位市值
#define TDX_ID_XHZH							655			// 现货账号
#define TDX_ID_XHZHLX						656			// 现货账号类型
#define TDX_ID_PCHLX						657			// 批次号类型
#define TDX_ID_DKBZ							658			// 多空标志
#define TDX_ID_TZSL							659			// 投资数量
#define TDX_ID_BJFS							660			// 报价方式
#define TDX_ID_DFBJFS						661			// 对方报价方式
#define TDX_ID_SYKCBJ						662			// 使用库存标记
#define TDX_ID_SYFZXHBJ						663			// 使用辅助现货标记
#define TDX_ID_MCYGBJ						664			// 卖出余股标记
#define TDX_ID_ZDWTBJ						665			// 自动委托标记
#define TDX_ID_ZDWTCS						666			// 自动委托次数
#define TDX_ID_PCHRQ						667			// 批次号日期
#define TDX_ID_JC							668			// 基差
#define TDX_ID_MRJEJSJZ						669			// 买入金额计算基准
#define TDX_ID_MRJE							670			// 买入金额
#define TDX_ID_FZXHDM						671			// 辅助现货代码
#define TDX_ID_FZXHMC						672			// 辅助现货名称
#define TDX_ID_PDDM1						673			// 配对代码1
#define TDX_ID_PDMC1						674			// 配对名称1
#define TDX_ID_PDDM2						675			// 配对代码2
#define TDX_ID_PDMC2						676			// 配对名称2
#define TDX_ID_PDBL							677			// 配对比例
#define TDX_ID_JCRQ							678			// 建仓日期
#define TDX_ID_JCJG1						679			// 建仓价格1
#define TDX_ID_JCSL1						680			// 建仓数量1
#define TDX_ID_JCBH1						681			// 建仓编号1
#define TDX_ID_JCJG2						682			// 建仓价格2
#define TDX_ID_JCSL2						683			// 建仓数量2
#define TDX_ID_JCBH2						684			// 建仓编号2

// 期货类
#define	TDX_ID_FXD							700			// 风险度
#define	TDX_ID_KHAQLB						701			// 客户安全类别
#define	TDX_ID_KHAQLBSM						702			// 客户安全类别说明
#define	TDX_ID_ZJBZJ						703			// 追加保证金
#define	TDX_ID_ZRJSJ						704			// 昨日结算价
#define	TDX_ID_SBMRJ						705			// 申报买入价
#define	TDX_ID_SBMCJ						706			// 申报卖出价
#define	TDX_ID_SBMRL						707			// 申报买入量
#define	TDX_ID_SBMCL						708			// 申报卖出量
#define	TDX_ID_MCDJZJ						709			// 卖出冻结资金
#define	TDX_ID_MRBZJ						710			// 买入保证金
#define	TDX_ID_MCBZJ						711			// 卖出保证金
#define	TDX_ID_YLJE							712			// 盈利金额
#define	TDX_ID_KSJE							713			// 亏损金额
#define	TDX_ID_DTQY							714			// 动态权益
#define	TDX_ID_DTFX							715			// 动态风险
#define	TDX_ID_PCYK							716			// 平仓盈亏
#define	TDX_ID_DRCRJ						717			// 当日出入金
#define	TDX_ID_XTZXH						718			// 系统中心号
#define	TDX_ID_KPBZSM						719			// 开平标志说明
#define	TDX_ID_TBBZSM						720			// 投保标志说明
#define	TDX_ID_MRCC							721			// 买入持仓
#define	TDX_ID_MRFDYK						722			// 买入浮动盈亏
#define	TDX_ID_MCCC							723			// 卖出持仓
#define	TDX_ID_MCJJ							724			// 卖出均价
#define	TDX_ID_MCFDYK						725			// 卖出浮动盈亏
#define	TDX_ID_JF							726			// 借方
#define	TDX_ID_DF							727			// 贷方
#define	TDX_ID_QHTJ							728			// 期货投机
#define	TDX_ID_QHBZ							729			// 期货保值
#define	TDX_ID_ZDSS							730			// 最大手数
#define	TDX_ID_ZDCC							731			// 最大持仓
#define	TDX_ID_WCJSL						732			// 未成交数量
#define	TDX_ID_SBSJ							733			// 申报时间
#define	TDX_ID_CDSJ							734			// 撤单时间
#define	TDX_ID_FSZ							735			// 发送者
#define	TDX_ID_XXLX							736			// 信息类型
#define	TDX_ID_XXLXSM						737			// 信息类型说明
#define TDX_ID_ZYZJ							738			// 质押资金
#define TDX_ID_ZJFXL						739			// 资金风险率
#define TDX_ID_JYSFXL						740			// 交易所风险率
#define TDX_ID_QCQY							741			// 期初权益
#define TDX_ID_DPPCYK						742			// 盯盘平仓盈亏
#define TDX_ID_FDPCYK						743			// 浮动平仓盈亏
#define TDX_ID_DPCCYK						744			// 盯盘持仓盈亏
#define TDX_ID_FDCCYK						745			// 浮动持仓盈亏
#define TDX_ID_DPZYK						746			// 盯盘总盈亏
#define TDX_ID_FDZYK						747			// 浮动总盈亏
#define TDX_ID_QHJYTSXX						748			// 期货交易提示信息
#define TDX_ID_KMRKCSL						749			// 可买入开仓数量
#define TDX_ID_KMCKCSL						750			// 可卖出开仓数量
#define TDX_ID_KMRPCSL						751			// 可买入平仓数量
#define TDX_ID_KMCPCSL						752			// 可卖出平仓数量
#define TDX_ID_KMRPJSL						753			// 可买入平今数量
#define TDX_ID_KMCPJSL						754			// 可卖出平今数量
#define TDX_ID_JKKY							755			// 今开可用
#define TDX_ID_LSKKY						756			// 历史开可用
#define TDX_ID_DSYK							757			// 盯市盈亏
#define TDX_ID_YKDS							758			// 盈亏点数
#define TDX_ID_HYBH							759			// 合约编号


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 安全中心类(800~899)
#define TDX_ID_CA_KHH						800			// 客户号							
#define TDX_ID_CA_KHMC						801			// 客户名称
#define TDX_ID_CA_SQBZ						802			// 申请标志
#define TDX_ID_CA_TXMM						803			// 认证口令
#define TDX_ID_CA_XTXMM						804			// 新认证口令
#define TDX_ID_CA_ZSXH						805			// 证书序号
#define TDX_ID_CA_AQJB						806			// 安全级别
#define TDX_ID_CA_YHFJ						807			// 用户分级
#define TDX_ID_CA_YHJBMS					808			// 用户级别描述
#define TDX_ID_CA_YHQX						809			// 用户权限
#define TDX_ID_CA_KJYBZ						810			// 可交易标志
#define TDX_ID_CA_ZSSHBZ					811			// 证书审核标志
#define TDX_ID_CA_ZSXZBZ					812			// 证书下载标志
#define TDX_ID_CA_ZSQSID					813			// 证书券商ID
#define TDX_ID_CA_ZSBFJG					814			// 证书颁发机构
#define TDX_ID_CA_ZSBFYH					815			// 证书颁发用户
#define TDX_ID_CA_ZSQSRQ					816			// 证书申请日期
#define TDX_ID_CA_ZSJZRQ					817			// 证书截止日期
#define TDX_ID_CA_ZSWS						818			// 证书位数
#define TDX_ID_CA_ZSGY						819			// 证书公钥匙
#define TDX_ID_CA_CZJG						820			// 操作机构
#define TDX_ID_CA_CZY						821			// 操作员
#define TDX_ID_CA_CZMM						822			// 操作密码
#define TDX_ID_CA_CZSX						823			// 操作属性
#define TDX_ID_CA_CZBZ						824			// 操作标志
#define TDX_ID_CA_RESV						825			// 保留字段
#define IDX_ID_CA_ZSKGXBZ					826			// 证书可更新标志
#define TDX_ID_CA_ZSJYGXBZ					827			// 证书建议更新标志
#define TDX_ID_CA_ZSSYYXTS					828			// 证书剩余有效天数
#define TDX_ID_CA_ZHLB						829			// CA账号类别(0:客户号 1:TQ号 2:TQ邮件)
#define TDX_ID_CA_TQID						830			// 用户TQ号
#define TDX_ID_CA_TQMAIL					831			// 用户TQ邮件
#define TDX_ID_CA_XGTXMMBZ					832			// 修改通讯密码标识(0:密码正常 1:密码必须修改)
#define TDX_ID_CA_L2USER					833			// LEVEL2绑定账号
#define TDX_ID_CA_L2PASS					834			// LEVEL2绑定密码
#define TDX_ID_CA_YHJBZT					835			// 用户级别状态(-1:未申请 0:已申请待审核 1:已经审核)
#define TDX_ID_CA_YHJBBZ					836			// 用户级别备注
#define TDX_ID_CA_ISVIPHOST					837			// VIP主站标识
// 我的问题相关字段
#define TDX_ID_CA_KHJL						838			// 客户经理编号
#define TDX_ID_CA_TOPICID					839			// 我的问题:主题ID
#define TDX_ID_CA_TOPICTITLE				840			// 我的问题:主题标题
#define TDX_ID_CA_CONTENT					841			// 我的问题:主题内容或者回复内容
#define TDX_ID_CA_QUERYDATE					842			// 我的问题:查询此日期后的所有数据
#define TDX_ID_CA_REQDATE					843			// 我的问题:发布日期
#define TDX_ID_CA_REQTIME					844			// 我的问题:发布日期
#define TDX_ID_CA_VALDATE					845			// 我的问题:此主题有效日期
#define TDX_ID_CA_CLOSEFLAG					846			// 我的问题:主题关闭标志
#define TDX_ID_CA_BRANCHMSGID				847			// 我的问题:营业部信息ID
#define TDX_ID_CA_SATISFAC					848			// 我的问题:满意度
#define TDX_ID_CA_REMINDFLAG				849			// 我的问题:是否提示关闭主题
#define TDX_ID_CA_NEWANSFLAG				850			// 我的问题:是否有最新回复
#define TDX_ID_CA_ANSWERID					851			// 我的问题:回复ID
#define TDX_ID_CA_WHOANS					852			// 我的问题:发布人
#define TDX_ID_CA_QUERYALL					853			// 我的问题:为0查询所有有状态的主题,-1为查询所有未关闭主题
#define TDX_ID_CA_NEWMSGNUM					854			// 我的问题:新信息条数
#define TDX_ID_CA_NOREADMSGNUM				855			// 我的问题:未读信息条数
#define TDX_ID_CA_RESETFLAG					856			// 重置标志

// 光大定制
#define TDX_ID_CA_SJH						860			// 客户手机号
#define TDX_ID_CA_ZJHM						861			// 客户证件号码
#define TDX_ID_CA_KHXB						862			// 客户性别
#define TDX_ID_CA_EMAIL						863			// 客户电子邮件
#define TDX_ID_CA_JHM						865			// 激活码
#define TDX_ID_CA_DRZB						866			// 当日指标
#define TDX_ID_CA_LEVELNAME					867			// 等级名称
#define	TDX_ID_CA_ZBMAX						868			// 指标上限
#define	TDX_ID_CA_ZBMIN						869			// 指标下限
#define	TDX_ID_CA_PROTOC					870			// 指标申请协议
#define	TDX_ID_CA_COMMISION					871			// 佣金
#define TDX_ID_CA_BIRTHTITIP				872			// 是否需要生日提醒
#define TDX_ID_CA_NOTICETITLE				873			// 公告标题
#define TDX_ID_CA_NOTICECONTENT				875			// 公告正文内容
#define	TDX_ID_CA_TSUPDATE					878			// 提示升级
#define TDX_ID_CA_NOWLEVELNO				879			// 当前等级编号
#define TDX_ID_CA_NOWLEVELNAME				880			// 当前等级名称
#define TDX_ID_CA_CANLEVELNO				881			// 可申请等级编号
#define TDX_ID_CA_CANLEVELNAME				882			// 可申请等级名称
#define TDX_ID_CA_MENU						883			// 可见栏目

#define TDX_ID_CA_LASTIP					890			// 上次登陆IP
#define TDX_ID_CA_NEWIP						891			// 本次登陆IP
#define TDX_ID_CA_LASPROV					892			// 上次登陆省份
#define TDX_ID_CA_NEWPROV					893			// 本次登陆省份
#define TDX_ID_CA_LASSITE					894			// 上次登陆城市
#define TDX_ID_CA_NEWSITE					895			// 本次登陆城市 
#define TDX_ID_CA_QSRQ						896			// 起始查询时间
#define TDX_ID_CA_ZZRQ						897			// 终止查询时间
#define TDX_ID_CA_DLSJ						898			// 登陆时间
#define TDX_ID_CA_DLRQ						899			// 登陆日期



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// 行情类字段	
#define TDX_ID_HQ_MRSL1						900			// 买一量
#define TDX_ID_HQ_MRSL2						901			// 买二量
#define TDX_ID_HQ_MRSL3						902			// 买三量
#define TDX_ID_HQ_MRSL4						903			// 买四量
#define TDX_ID_HQ_MRSL5						904			// 买五量
#define TDX_ID_HQ_MRSL6						905			// 买六量
#define TDX_ID_HQ_MRSL7						906			// 买七量
#define TDX_ID_HQ_MRSL8						907			// 买八量
#define TDX_ID_HQ_MRSL9						908			// 买九量
#define TDX_ID_HQ_MRSL0						909			// 买十量

#define TDX_ID_HQ_MRLG1						910			// 买一价
#define TDX_ID_HQ_MRLG2						911			// 买二价
#define TDX_ID_HQ_MRLG3						912			// 买三价
#define TDX_ID_HQ_MRLG4						913			// 买四价
#define TDX_ID_HQ_MRLG5						914			// 买五价
#define TDX_ID_HQ_MRLG6						915			// 买六价
#define TDX_ID_HQ_MRLG7						916			// 买七价
#define TDX_ID_HQ_MRLG8						917			// 买八价
#define TDX_ID_HQ_MRLG9						918			// 买九价
#define TDX_ID_HQ_MRLG0						919			// 买十价

#define TDX_ID_HQ_MCSL1						920			// 卖一量
#define TDX_ID_HQ_MCSL2						921			// 卖二量
#define TDX_ID_HQ_MCSL3						922			// 卖三量
#define TDX_ID_HQ_MCSL4						923			// 卖四量
#define TDX_ID_HQ_MCSL5						924			// 卖五量
#define TDX_ID_HQ_MCSL6						925			// 卖六量
#define TDX_ID_HQ_MCSL7						926			// 卖七量
#define TDX_ID_HQ_MCSL8						927			// 卖八量
#define TDX_ID_HQ_MCSL9						928			// 卖九量
#define TDX_ID_HQ_MCSL0						929			// 卖十量

#define TDX_ID_HQ_MCJS1						930			// 卖一价
#define TDX_ID_HQ_MCJS2						931			// 卖二价
#define TDX_ID_HQ_MCJS3						932			// 卖三价
#define TDX_ID_HQ_MCJS4						933			// 卖四价
#define TDX_ID_HQ_MCJS5						934			// 卖五价
#define TDX_ID_HQ_MCJS6						935			// 卖六价
#define TDX_ID_HQ_MCJS7						936			// 卖七价
#define TDX_ID_HQ_MCJS8						937			// 卖八价
#define TDX_ID_HQ_MCJS9						938			// 卖九价
#define TDX_ID_HQ_MCJS0						939			// 卖十价

#define TDX_ID_HQ_ZTJG						940			// 涨停价格
#define TDX_ID_HQ_DTJG						941			// 跌停价格
#define TDX_ID_HQ_ZGJG						942			// 最高价
#define TDX_ID_HQ_ZDJG						943			// 最低价
#define TDX_ID_HQ_GZQJ						944			// 国债全价
#define TDX_ID_HQ_OPEN						945			// 今开价
#define TDX_ID_HQ_CLOSE						946			// 昨收价
#define TDX_ID_HQ_TPBZ						947			// 停牌标志	1:停牌
#define TDX_ID_GZLX							948			// 国债利息
#define	TDX_ID_NOW							949			// 当前价
#define TDX_ID_USERADDRESS					950			// 用户通讯地址
#define TDX_ID_IDENTITYCARD					951			// 身份证
#define TDX_ID_SEX							952			// 性别
#define TDX_ID_POSTALCODE					953			// 邮政编码
#define TDX_ID_HQ_ZDF						954			// 涨跌幅
#define TDX_ID_HQ_ZDZ						955			// 涨跌值
#define TDX_ID_GETGTHQ						956			// 取柜台行情  主要用于统计涨跌停及涨跌幅度
#define TDX_ID_MBYLX						957			// 每百元利息
#define TDX_ID_GZBS							958			// 国债标识(0--国债现货,1--债券,2--可转换债券,3--国债回购,255(-1)--非债券)
#define TDX_ID_ZQXXYXBZ						959			// 证券信息有效标志
#define TDX_ID_ZQLB							960			// 证券类别(0--通常状态,1--首日上市,2--增发股份上市,3--上网定价发行,4--上网竞价发行,5--国债挂牌分销)
#define TDX_ID_ZGSL							961			// 最高数量
#define TDX_ID_ZDSL							962			// 最低数量


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 日志查看类字段(1000~1099)
#define TDX_ID_RZ_STARTTIME					1000		// 查询开始时间
#define TDX_ID_RZ_ENDTIME					1001		// 查询结束时间
#define TDX_ID_RZ_TCTIME					1002		// 查询交易中心时间
#define TDX_ID_RZ_APITIME					1003		// 查询API时间
#define TDX_ID_RZ_QUEUETIME					1004		// 查询排队时间
#define TDX_ID_RZ_FUNCID					1005		// 操作功能号
#define TDX_ID_RZ_FLAGRESULT				1006		// 处理结果标志
#define TDX_ID_RZ_LOGID						1007		// 日志编号
#define TDX_ID_RZ_TCIP						1008		// 交易中心IP
#define TDX_ID_RZ_LOGTIME					1009		// 日志时间
#define TDX_ID_RZ_LEVER						1010		// 用户级别
#define TDX_ID_RZ_PAGEINDEX					1011		// 页码序号
#define TDX_ID_RZ_FUNCNUM					1012		// 操作数目
#define TDX_ID_RZ_FUNCBL					1013		// 操作比例
#define	TDX_ID_RZ_FUNCOKNUM					1014		// 调用功能成功数目
#define	TDX_ID_RZ_FUNCFAILNUM				1015		// 调用功能失败数目
#define TDX_ID_RZ_ITEMNUM					1016		// 记录条数
#define TDX_ID_RZ_AVGTCTIME					1017		// 查询交易中心平均时间
#define TDX_ID_RZ_AVGAPITIME				1018		// 查询API平均时间
#define TDX_ID_RZ_AVGQUEUETIME				1019		// 查询排队平均时间
#define TDX_ID_RZ_CXFLAG					1020		// 查询标志
#define TDX_ID_RZ_DAY						1021		// 日期时间


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	
// 银证业务类	
#define TDX_ID_YZZZ_YHDM					1101		// 银行代码
#define TDX_ID_YZZZ_YHMC					1102		// 银行名称
#define TDX_ID_YZZZ_YHZH					1103		// 银行帐号
#define TDX_ID_YZZZ_YHMM					1104		// 银行密码
#define TDX_ID_YZZZ_XYHMM					1105		// 新银行密码
#define TDX_ID_YZZZ_YHLSH					1106		// 银行流水号
#define TDX_ID_YZZZ_ZZJE					1107		// 转帐金额
#define TDX_ID_YZZZ_ZZFX					1108		// 转帐方向
#define TDX_ID_YZZZ_YHYE					1109		// 银行余额
#define TDX_ID_YZZZ_ZZRQ					1110		// 转帐日期
#define TDX_ID_YZZZ_ZZSJ					1111		// 转帐时间
#define TDX_ID_YZZZ_ZZFXSM					1112		// 转帐说明
#define TDX_ID_YZTYH						1113		// 银证通用户 0:否 1:是
#define	TDX_ID_YZZZ_NEEDZJMM				1114		// 需要资金密码
#define TDX_ID_YZZZ_NEEDYHMM				1115		// 需要银行密码
#define	TDX_ID_YZZZ_SUPPORTYHYE				1116		// 支持查银行余额
#define TDX_ID_BANKCODE						1117		// 银行代码
#define TDX_ID_BANKYYB						1118		// 银行营业部 (招商证券)
#define TDX_ID_BANKGDTYPE					1119		// 银行股东代码登陆的市场 (招商证券)
//0不需要密码 1 需要取款密码(资金密码) 2 需要银行密码 3 需要取款/银行密码
#define	TDX_ID_YZZZ_ZRMM					1120		// 银证转入密码情况
#define TDX_ID_YZZZ_ZCMM					1121		// 银证转出密码情况
#define	TDX_ID_YZZZ_SHOWYHYE				1122		// 显示查银行余额
#define	TDX_ID_YZZZ_YHYEMM					1123		// 查银行余额密码情况  20060328 配合国信linux 客户端
#define TDX_ID_ZRYHDM						1124		// 转入银行代码
#define TDX_ID_ZCYHDM						1125		// 转出银行代码
#define TDX_ID_ZRYHZH						1126		// 转入银行帐号
#define TDX_ID_ZCYHZH						1127		// 转出银行帐号
#define TDX_ID_ZJYHDM						1128		// 中继银行代码
#define TDX_ID_ZJYHMC						1129		// 中继银行名称
#define TDX_ID_ZJYHZH						1130		// 中继银行帐号
#define TDX_ID_ZJYHZHMC						1131		// 中继银行帐号名称
#define TDX_ID_YHKH							1132		// 银行卡号
#define TDX_ID_YHQC							1133		// 银行全称
#define TDX_ID_ZKBZ							1134		// 主卡标志
#define TDX_ID_JQBZ							1135		// 鉴权标志
#define TDX_ID_YHCPDM						1136		// 银行产品代码
#define TDX_ID_YHCPMC						1137		// 银行产品名称
#define TDX_ID_XTCPDM						1138		// 信托产品代码
#define TDX_ID_XTCPMC						1139		// 信托产品名称
#define TDX_ID_YHZHBM						1140		// 银行账户编码
#define TDX_ID_YHZHBM1						1141		// 银行账户编码1
#define TDX_ID_YHZHBM2						1142		// 银行账户编码2
#define TDX_ID_YHZHBM3						1143		// 银行账户编码3
#define TDX_ID_YHZHBM4						1144		// 银行账户编码4
#define TDX_ID_YHZHMC						1145		// 银行账户名称
#define TDX_ID_YHZHMC1						1146		// 银行账户名称1
#define TDX_ID_YHZHMC2						1147		// 银行账户名称2
#define TDX_ID_YHZHMC3						1148		// 银行账户名称3
#define TDX_ID_YHZHMC4						1149		// 银行账户名称4
//融资融券
#define	TDX_ID_RZLX							1150		// 账户融资利息
#define	TDX_ID_XYZ							1151		// 账户信用值
#define	TDX_ID_ZHWBXY						1152		// 账户外部信用
#define	TDX_ID_XYSX							1153		// 账户信用上限
#define	TDX_ID_RZSX							1154		// 融资信用上限
#define	TDX_ID_RQSX							1155		// 融券信用上限
#define	TDX_ID_XYCPBS						1156		// 信用产品标示(mmbz)
#define	TDX_ID_DYZC							1157		// 抵押资产
#define	TDX_ID_PCBZ							1158		// 平仓标志
#define	TDX_ID_RZSXF						1159		// 融资管理费
#define	TDX_ID_RQMCZJ						1160		// 融券卖出资金
#define	TDX_ID_RZFX							1161		// 融资方向
#define	TDX_ID_GHSL							1162		// 归还数量
#define	TDX_ID_RZFZ							1163		// 融资负债
#define	TDX_ID_RQSZ							1164		// 融券市值
#define	TDX_ID_QSJE							1165		// 清算金额
#define	TDX_ID_KYXYED						1166		// 可用信用额度
#define	TDX_ID_YYXYED						1167		// 已用信用额度
#define	TDX_ID_RZJE							1168		// 融资金额
#define	TDX_ID_RQJE							1169		// 融券金额
#define	TDX_ID_RQLX							1170		// 融券利息
#define	TDX_ID_RQSXF						1171		// 融券管理费
#define	TDX_ID_DBBL							1172		// 担保比例
#define	TDX_ID_KYBZJ						1173		// 可用保证金
#define	TDX_ID_YYBZJ						1174		// 已用保证金
#define	TDX_ID_RQSYSL						1175		// 融券使用数量
#define	TDX_ID_PCRQ							1176		// 平仓日期
#define	TDX_ID_XYHYLX						1177		// 合约类型
#define	TDX_ID_CHSL							1178		// 偿还数量
#define	TDX_ID_CHJE							1179		// 偿还金额
#define	TDX_ID_SSCHSL						1180		// 实时偿还数量
#define	TDX_ID_SSCHJE						1181		// 实时偿还金额
#define	TDX_ID_CHLX							1182		// 偿还利息
#define	TDX_ID_HYSXF						1183		// 合约费用
#define	TDX_ID_HYLL							1184		// 合约利率
#define	TDX_ID_HYLXJE						1185		// 合约利息
#define	TDX_ID_RZBL							1186		// 融资比例
#define TDX_ID_GPZSL						1187		// 股票折算率
#define TDX_ID_XYJB							1188		// 信用级别
#define TDX_ID_FXZT							1189		// 风险状态
#define TDX_ID_RZBZJBL						1190		// 融资保证金比例
#define TDX_ID_RQBZJBL						1191		// 融券保证金比例
#define TDX_ID_RZRQLXFY						1192		// 融资融券利息费用
#define TDX_ID_ZFZ							1193		// 总负债
#define TDX_ID_FZBL							1194		// 负债比例
#define TDX_ID_HYQX							1195		// 合约期限
#define	TDX_ID_SYRZED						1196		// 剩余融资额度
#define	TDX_ID_SYRQED						1197		// 剩余融券额度
#define TDX_ID_TQZZLL						1198		// 提前终止利率
#define TDX_ID_DQR							1199		// 到期日

// 系统类	
#define TDX_ID_XT_ERRCODE					1200		// 错误号 0:成功 其他为处理失败,具体错误信息在ERRMSG中返回
#define TDX_ID_XT_ERRMSG					1201		// 错误信息
#define	TDX_ID_XT_FUNCNO					1202		// 功能编号
#define	TDX_ID_XT_CLIVER					1203		// 客户端版本
#define	TDX_ID_XT_MACADDR					1204		// MAC地址
#define TDX_ID_XT_IPADDR					1205		// IP地址
#define	TDX_ID_XT_CLITYPE					1206		// 客户类别	参见:CLITYPE_XXX宏定义
#define TDX_ID_XT_STARTPOS					1207		// 起始序号
#define TDX_ID_XT_AUTH_NEWINFO				1208		// 安全中心验证新信息(口令/密钥等)
#define TDX_ID_XT_OEM_FLAG					1209		// OEM标志
#define TDX_ID_XT_AUTH_MODE					1210		// 安全中心验证方式(取值见"安全级别定义")
#define TDX_ID_XT_AUTH_INFO					1211		// 安全中心验证信息(口令/密钥等)
#define TDX_ID_XT_BRANCHID					1212		// 所在营业部ID
#define TDX_ID_XT_RESERVED					1213		// 系统保留
#define	TDX_ID_XT_RECONNECTFLAG				1214		// 断线重联标志(0-客户登录,1-断线重联)
#define	TDX_ID_XT_COUNTERSTATUS				1215		// (券商)柜台状态
#define	TDX_ID_XT_VIPFLAG					1216		// VIP标志
#define	TDX_ID_XT_REMARK					1217		// 备注
#define	TDX_ID_XT_CLIENTRIGHTS				1218		// 客户权限
#define TDX_ID_XT_LAST_LOGIN_DATE			1219		// 上次登录日期
#define TDX_ID_XT_LAST_LOGIN_TIME			1220		// 上次登录时间
#define TDX_ID_XT_AHTHCHAR1					1221		// 验证字符1
#define TDX_ID_XT_AHTHCHAR2					1222		// 验证字符2
#define	TDX_ID_XT_CHECKRISKFLAG				1223		// 检查风险标志
#define	TDX_ID_XT_FJYZHBZ					1224		// 非交易帐号标志
#define	TDX_ID_XT_JZJJKHBZ					1225		// 禁止基金开户标志
#define TDX_ID_XT_INCREMENTMODE				1226		// 增量模式开关
#define TDX_ID_XT_PARAM						1227		// 参数
#define TDX_ID_XT_MODE						1228		// 模式
#define TDX_ID_XT_DESCRIPTION				1229		// 描述
#define TDX_ID_XT_QUERYMODE					1230		// 查询模式
#define TDX_ID_XT_DISPLAYCOLOR				1231		// 显示颜色(RGB值,供客户端显示参考)
#define TDX_ID_XT_PASSWORDFLAG				1232		// 密码标志
#define TDX_ID_XT_HANDLE					1233		// 句柄
#define TDX_ID_XT_GTLB						1234		// 柜台类别(0:默认 1:信用交易 2:股票 3:基金 4:商品期货 5:金融期货 6:港股)
#define TDX_ID_XT_MACHINEINFO				1235		// 机器信息(格式[大项分号分隔,子项逗号分隔]: 内网IP;机器名;用户名;内存;CPU信息;CPUID;系统版本;IP列表;MAC地址列表;硬盘序列号列表;BIOS版本; )
														// 中信机器特征码=[标志*4][CPUID*8][DISKSN*20][MAC*12][BIOSDATE*10]
#define TDX_ID_XT_LOGINTYPE					1236		// [只出现在登录字典中]登录类型(登录适用)
#define TDX_ID_XT_LOGINID					1237		// [只出现在登录字典中]登录帐号(登录适用)
#define TDX_ID_XT_LOGINPASSWD				1238		// [只出现在登录字典中]登录密码(登录适用)
#define TDX_ID_XT_COMMPASSWD				1239		// [只出现在登录字典中]通讯密码(登录适用)
#define TDX_ID_XT_FUNCID					1240		// [只出现在登录字典中]功能号
#define TDX_ID_XT_FUNCDICTTAG				1241		// [只出现在登录字典中]功能字典标识
#define TDX_ID_XT_FUNCCONTENT				1242		// [只出现在登录字典中]功能内容
#define TDX_ID_XT_LIMITMODE					1243		// 受限模式
#define TDX_ID_XT_MACHINECODE				1244		// 机器特征码(针对不同券商格式化后的字符串)
#define TDX_ID_XT_MOBILECHECKCODE			1245		// 手机校验码
#define TDX_ID_XT_BRANCHMODIFY				1246		// 营业部改变
#define TDX_ID_XT_NEEDEDAUTHMODE			1247		// 所需认证方式(使用"安全级别定义",按位表示)
#define TDX_ID_XT_SESSION					1248		// 会话信息
#define TDX_ID_XT_URL						1249		// URL
#define TDX_ID_XT_INFOCOLUMN				1250		// 资讯栏目
#define TDX_ID_XT_REALCLIENTVERSION			1251		// 内部客户端版本
#define TDX_ID_XT_CN						1252		// CN
#define TDX_ID_XT_SN						1253		// SN
#define TDX_ID_XT_DN						1254		// DN
#define TDX_ID_XT_NEEDCONFIRMFLAGS			1255		// 需确认的标识串(逗号分隔,各子项与170功能的CZBZ对应)
														// (1--确认账单,其他--未定)
#define TDX_ID_XT_URL2						1256		// URL2
#define TDX_ID_XT_REDIRECTFLAG				1257		// 重定向标志
#define TDX_ID_XT_REDIRECTINFO				1258		// 重定向信息
#define TDX_ID_XT_LAST_LOGIN_LOCATION		1259		// 上次登录位置
#define TDX_ID_XT_SLOTID					1260		// 证书容器ID
#define TDX_ID_XT_CID						1261		// 证书厂商ID
#define TDX_ID_XT_INPUTPARAM				1262		// 输入参数
#define TDX_ID_XT_OUTPUTPARAM				1263		// 输出参数
#define TDX_ID_XT_TOKEN						1264		// 令牌
#define TDX_ID_XT_PREPASSWORD0				1265		// [只出现在登录字典中]预处理密码0
#define TDX_ID_XT_PREPASSWORD1				1266		// [只出现在登录字典中]预处理密码1
#define TDX_ID_XT_PREPASSWORD2				1267		// [只出现在登录字典中]预处理密码2
#define TDX_ID_XT_PREPASSWORD3				1268		// [只出现在登录字典中]预处理密码3
#define TDX_ID_XT_PREPASSWORD4				1269		// [只出现在登录字典中]预处理密码4
#define TDX_ID_XT_PREPARAM0					1270		// [只出现在登录字典中]预处理参数0
#define TDX_ID_XT_PREPARAM1					1271		// [只出现在登录字典中]预处理参数1
#define TDX_ID_XT_PREPARAM2					1272		// [只出现在登录字典中]预处理参数2
#define TDX_ID_XT_PREPARAM3					1273		// [只出现在登录字典中]预处理参数3
#define TDX_ID_XT_PREPARAM4					1274		// [只出现在登录字典中]预处理参数4
#define TDX_ID_XT_PREPARAM5					1275		// [只出现在登录字典中]预处理参数5
#define TDX_ID_XT_PREPARAM6					1276		// [只出现在登录字典中]预处理参数6
#define TDX_ID_XT_PREPARAM7					1277		// [只出现在登录字典中]预处理参数7
#define TDX_ID_XT_PREPARAM8					1278		// [只出现在登录字典中]预处理参数8
#define TDX_ID_XT_PREPARAM9					1279		// [只出现在登录字典中]预处理参数9
#define TDX_ID_XT_LOGINEMAIL				1280		// 登录Email
#define TDX_ID_XT_TRADEEMAIL				1281		// 交易Email
#define TDX_ID_XT_MULTINITICE				1282		// [只出现在登录字典中]多提示信息
#define TDX_ID_XT_MESSAGEID					1283		// 信息编号
#define TDX_ID_XT_MESSAGETITLE				1284		// 信息标题
#define TDX_ID_XT_MESSAGECONTENT			1285		// 信息内容
#define TDX_ID_XT_POSITIONSTRING			1286		// 定位字串
#define TDX_ID_XT_BEGINLINE					1287		// 起始行号
#define TDX_ID_XT_REQUESTLINE				1288		// 请求行数
#define TDX_ID_XT_TOTALLINE					1289		// 总共行数
#define TDX_ID_XT_RISKPARAM					1290		// 风险参数
#define TDX_ID_XT_LOGINRETURNPARAM			1291		// 登录返回参数
#define TDX_ID_XT_MOBILEMACHINEINFO			1292		// 手机机器信息
#define TDX_ID_XT_PACKAGELIST				1293		// 套餐列表
#define TDX_ID_XT_PRODUCTLIST				1294		// 产品列表
#define TDX_ID_XT_FEATURELIST				1295		// 功能列表
#define TDX_ID_XT_CONFIGLIST				1296		// 配置列表
#define TDX_ID_XT_LOGINENTERPARAM			1297		// 登录输入参数
#define TDX_ID_XT_ALGORIGHTLIST				1298		// 算法权限列表
#define TDX_ID_XT_FUNCTIONVERSION			1299		// 功能版本
#define TDX_ID_XT_CLIENTINVERSION			1300		// 客户端内部版本
#define TDX_ID_XT_VERSIONSTRING				1301		// 版本字符串

// 其他	
#define TDX_ID_XLYZT_XGKT_FLAG				3101		// 修改开通标记 

//	1 代理配股开通
//	2 代理配股取消
//	3 代理申购开通
//	4 代理申购取消
//	5 代理配售开通
//	6 代理配售取消
	
#define TDX_ID_XLYZT_START_DATE				3104		// 生效时间
#define TDX_ID_XLYZT_END_DATE				3105		// 失效时间
#define TDX_ID_XLYZT_DEBT_KIND				3106		// 回购品种 '3''7''14''28''63''91''182''273
#define TDX_ID_XLYZT_JE_MIN					3107		// 资金下限，单位：元
#define TDX_ID_XLYZT_JE_MAX					3108		// 资金上限，单位：元

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CA扩展字段

#define TDX_ID_CA_JQTZM						4201		// 机器特征码
#define TDX_ID_CA_PWDQACZBZ					4202		// 密码保护问题操作标志 ( 0-申请,1-修改 )
#define TDX_ID_CA_CONNID					4203		// 用户连接ID
#define TDX_ID_CA_MACHINENAME				4204		// 机器昵称
#define TDX_ID_CA_PROVISIONAL				4205		// 临时标志
#define TDX_ID_CA_TZZB						4206		// 挑战坐标
#define TDX_ID_CA_CSCS						4207		// 重试次数
#define TDX_ID_CA_ISDLWZTS					4208		// 是否支持登陆位置提示
#define TDX_ID_CA_ISMMBHWT					4209		// 是否支持密码保护问题
#define TDX_ID_CA_ISJQTZMBD					4210		// 是否支持机器特征码绑定
#define TDX_ID_CA_MAC						4211		// 用户MAC地址
#define TDX_ID_CA_YLWT						4212		// 预留问题
#define TDX_ID_CA_ISYLWT					4213		// 是否支持预留问题

#define TDX_ID_CA_CERTREQ					4214		// 证书申请请求(P10)
#define TDX_ID_CA_USERCERDN					4215		// 证书DN信息
#define TDX_ID_CA_CERTTOKEN					4216		// 证书业务号
#define TDX_ID_CA_CERTINFO					4217		// 证书内容
#define TDX_ID_CA_SLOTSN					4218		// 装载证书容器SN
#define TDX_ID_CA_CERTSN					4219		// 证书编号
#define	TDX_ID_CA_CID						4220		// 三方安全机构ID(颁发/验证)
#define	TDX_ID_CA_SEEDINFO					4221		// 种子信息
#define	TDX_ID_CA_OTPSN						4222		// OTPSN序号

#define TDX_ID_CA_BINDNUM					4223		// 已绑定机器特征码机器台数
#define TDX_ID_CA_IDCARD					4224		// 用户身份证号码
#define TDX_ID_CA_YZM						4225		// 验证码

#define	TDX_ID_CA_VER						4226		// 版本信息
#define	TDX_ID_CA_PWDPROQUESTION			4227		// 密码保护问题(问题格式: 编号:问题内容)
#define	TDX_ID_CA_MACHINEBINDTIME			4228		// 机器绑定时间

// 修改密码保护问题宏定义,原定义宏值改变,预留宏空间(4230-4250)
#define TDX_ID_CA_MMBHWT					4230		// 密码保护问题
#define TDX_ID_CA_MMBHWT1	(TDX_ID_CA_MMBHWT+1)		// 密码保护问题1
#define TDX_ID_CA_MMBHWT2	(TDX_ID_CA_MMBHWT+2)		// 密码保护问题2
#define TDX_ID_CA_MMBHWT3	(TDX_ID_CA_MMBHWT+3)		// 密码保护问题3
#define TDX_ID_CA_MMBHWT4	(TDX_ID_CA_MMBHWT+4)		// 密码保护问题4
#define TDX_ID_CA_MMBHWT_LAST				4250		// 预留空间

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define TDX_ID_UM_BROKERCODE				4251		// 经纪人代码
#define TDX_ID_UM_BROKERBRANCH				4252		// 经纪人营业部
#define TDX_ID_UM_BROKERNAME				4253		// 经纪人名称
#define TDX_ID_UM_BROKERSTATUS				4254		// 经纪人状态
#define TDX_ID_UM_BROKERLEVEL				4255		// 经纪人级别
#define TDX_ID_UM_UPBROKER					4256		// 上级经纪人
#define TDX_ID_UM_BROKERNATIONALITY			4257		// 经纪人国籍
#define TDX_ID_UM_BROKERPHONECODE			4258		// 经纪人电话
#define TDX_ID_UM_BROKERMOPHONE				4259		// 经纪人移动电话
#define TDX_ID_UM_BROKEREMAIL				4260		// 经纪人电子邮件
#define TDX_ID_UM_BROKERMSN					4261		// 经纪人MSN
#define TDX_ID_UM_BROKERQQ					4262		// 经纪人QQ
#define TDX_ID_UM_BROKERSEX					4263		// 经纪人性别
#define TDX_ID_UM_BROKERAGE					4264		// 经纪人年龄
#define TDX_ID_UM_BROKERDEGREE				4265		// 经纪人学历
#define TDX_ID_UM_BROKERFAVOR				4266		// 经纪人操作习惯
#define TDX_ID_UM_BROKERNATIVEPLACE			4267		// 经纪人个人谏言
#define TDX_ID_UM_BROKERQUAL				4268		// 经纪人从业资格
#define TDX_ID_UM_BROKERSATISLEV			4269		// 经纪人投资顾问满意度级别
#define TDX_ID_UM_BROKERPHOTOS				4270		// 经纪人照片
#define TDX_ID_UM_BROKERNOTES				4271		// 经纪人备注
#define TDX_ID_UM_BRANCHNAME				4272		// 营业部名称
#define TDX_ID_UM_COMHOTLINE				4273		// 公司客户热线
#define TDX_ID_UM_BRANCHTRADEASK			4274		// 营业部交易咨询电话
#define TDX_ID_UM_BRANCHINVESTASK			4275		// 营业部投资咨询电话
#define TDX_ID_UM_PASSEXAM					4276		// 是否通过考试
#define TDX_ID_UM_PRACTISETIME				4277		// 从业时间

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define	TDX_ID_CA_USERNICK					4230		// 用户昵称
#define	TDX_ID_CA_CARDTYPE					4231		// 证件类型
#define	TDX_ID_CA_BIRTH						4232		// 出生日期
#define	TDX_ID_CA_POSTCODE					4233		// 邮政编码
#define	TDX_ID_CA_ADDRESS					4234		// 联系地址
#define	TDX_ID_CA_OFFPHONE					4235		// 办公电话
#define	TDX_ID_CA_HOMEPHONE					4236		// 家庭电话
#define	TDX_ID_CA_FAXPHONE					4237		// 传真电话
#define	TDX_ID_CA_EDUCATION					4238		// 学历
#define	TDX_ID_CA_TOKEN						4239		// 令牌
#define TDX_ID_CA_YYBID						4240		// 营业部ID
#define TDX_ID_CA_USERSTOCK					4241		// 用户自选股
#define TDX_ID_CA_GD_DATE					4242		// 日期
#define TDX_ID_CA_GD_TIME					4243		// 时间
#define TDX_ID_CA_GD_HARDINFO				4244		// 计算机特征码信息
#define TDX_ID_CA_GD_MOREINFO				4245		// 计算机昵称
#define TDX_ID_CA_GD_TERMINALTYPE			4246		// 终端类型
#define TDX_ID_CA_GD_XH						4247		// 序号
#define TDX_ID_CA_TRADETIME					4248		// 交易时间
#define TDX_ID_CA_TRADETYPE					4249		// 交易类型
#define TDX_ID_CA_SCORE						4250		// 积分值

#define TDX_ID_CA_SID						4501		// 序号
#define TDX_ID_CA_BINDTINE					4502		// 绑定时间
#define TDX_ID_CA_UMAC						4503		// MAC地址
#define TDX_ID_CA_REMARK					4504		// 计算机备注
#define TDX_ID_CA_HARDINFO					4505		// 隐藏硬件信息


	
// 最大字段ID	
#define TDX_ID_FIELD_MAXID					6000		// 最大字段ID



//---------------------------------------------------------------------------
// Part.V 功能ID定义
//---------------------------------------------------------------------------
	
	
// 系统部分
#define TDX_ID_FUNC_REQ_GETDICT				1		// 取数据字典
#define TDX_ID_FUNC_ANS_GETDICT				2

// 委托功能部分
#define TDX_ID_FUNC_REQ_ZHYCL				94		// 账号预处理 94
#define TDX_ID_FUNC_ANS_ZHYCL				95

#define TDX_ID_FUNC_REQ_DLYCL				96		// 登录预处理 96
#define TDX_ID_FUNC_ANS_DLYCL				97

#define TDX_ID_FUNC_REQ_JCKHJY				98		// 集成客户校验 98
#define TDX_ID_FUNC_ANS_JCKHJY				99

#define TDX_ID_FUNC_REQ_KHJY				100		// 客户校验 100
#define TDX_ID_FUNC_ANS_KHJY				101

#define TDX_ID_FUNC_REQ_SIMPDICTMAX			100		// 简单字典内的最大功能号
	
#define TDX_ID_FUNC_REQ_CXHQ				102		// 查询行情 102
#define TDX_ID_FUNC_ANS_CXHQ				103		
	
#define TDX_ID_FUNC_REQ_ZJYE				104		// 资金余额 104
#define TDX_ID_FUNC_ANS_ZJYE				105
	
#define TDX_ID_FUNC_REQ_XGMM				106		// 修改密码 106
#define TDX_ID_FUNC_ANS_XGMM				107
	
#define TDX_ID_FUNC_REQ_XGZJMM				108		// 修改资金密码 108
#define TDX_ID_FUNC_ANS_XGZJMM				109
	
#define TDX_ID_FUNC_REQ_JSKMS				110		// 计算可买(卖)数 110
#define TDX_ID_FUNC_ANS_JSKMS				111
	
#define	TDX_ID_FUNC_REQ_CACHE				112		// 取缓存信息 112
#define	TDX_ID_FUNC_ANS_CACHE				113

#define	TDX_ID_FUNC_REQ_XGGLZJZH			114		// 修改关联资金帐号 114
#define	TDX_ID_FUNC_ANS_XGGLZJZH			115

#define TDX_ID_FUNC_REQ_KHZX				116		// 客户注销 116
#define TDX_ID_FUNC_ANS_KHZX				117

#define	TDX_ID_FUNC_REQ_DYQXDZD				118		// 订阅取消对帐单(邮寄) 118
#define	TDX_ID_FUNC_ANS_DYQXDZD				119
	
#define TDX_ID_FUNC_REQ_WTDJZJ				120		// 委托冻结资金 120
#define TDX_ID_FUNC_ANS_WTDJZJ				121

#define TDX_ID_FUNC_REQ_PRINTDZD			122		// 打印对帐单 122
#define TDX_ID_FUNC_ANS_PRINTDZD			123
	
#define TDX_ID_FUNC_REQ_PRINTHZDZD			124		// 打印汇总对帐单 124
#define TDX_ID_FUNC_ANS_PRINTHZDZD			125
	
#define TDX_ID_FUNC_REQ_PRINTJGD			126		// 打印交割单 126
#define TDX_ID_FUNC_ANS_PRINTJGD			127

#define	TDX_ID_FUNC_REQ_XGTXMM				128		// 修改通讯密码 128
#define	TDX_ID_FUNC_ANS_XGTXMM				129

#define TDX_ID_FUNC_REQ_ZHJD				130		// 帐号解冻 130
#define TDX_ID_FUNC_ANS_ZHJD				131

#define TDX_ID_FUNC_REQ_ZJGJ				132		// 资金归集 132
#define TDX_ID_FUNC_ANS_ZJGJ				133

#define TDX_ID_FUNC_REQ_ZJZHJZZ				134		// 资金帐号间转帐 134
#define TDX_ID_FUNC_ANS_ZJZHJZZ				135

#define	TDX_ID_FUNC_REQ_TJWJJG				136		// 提交问卷结果 136
#define	TDX_ID_FUNC_ANS_TJWJJG				137

#define	TDX_ID_FUNC_REQ_HQWJNR				138		// 获取问卷内容 138
#define	TDX_ID_FUNC_ANS_HQWJNR				139

#define	TDX_ID_FUNC_REQ_HQZHZTBZ			140		// 获取帐号状态标志 140
#define	TDX_ID_FUNC_ANS_HQZHZTBZ			141

#define	TDX_ID_FUNC_REQ_CLCXMM				142		// 处理查询密码 142
#define	TDX_ID_FUNC_ANS_CLCXMM				143

#define	TDX_ID_FUNC_REQ_TSZC				144		// 推送注册 144
#define	TDX_ID_FUNC_ANS_TSZC				145

#define	TDX_ID_FUNC_REQ_TSZX				146		// 推送注销 146
#define	TDX_ID_FUNC_ANS_TSZX				147

#define TDX_ID_FUNC_REQ_ZZHCX				148		// 子帐号查询 148
#define TDX_ID_FUNC_ANS_ZZHCX				149

#define TDX_ID_FUNC_REQ_CLRZXX				150		// 处理认证信息 150
#define TDX_ID_FUNC_ANS_CLRZXX				151

#define TDX_ID_FUNC_REQ_RZXXCX				152		// 认证信息查询 152
#define TDX_ID_FUNC_ANS_RZXXCX				153

#define TDX_ID_FUNC_REQ_KHJBXXCX			154		// 客户基本信息查询 154
#define TDX_ID_FUNC_ANS_KHJBXXCX			155

#define TDX_ID_FUNC_REQ_DZHTQY				156		// 电子合同签约 156
#define TDX_ID_FUNC_ANS_DZHTQY				157

#define TDX_ID_FUNC_REQ_DZHTQYCX			158		// 电子合同签约查询 158
#define TDX_ID_FUNC_ANS_DZHTQYCX			159

#define TDX_ID_FUNC_REQ_DZHTLBCX			160		// 电子合同列表查询 160
#define TDX_ID_FUNC_ANS_DZHTLBCX			161

#define TDX_ID_FUNC_REQ_DZHTXXCX			162		// 电子合同信息查询 162
#define TDX_ID_FUNC_ANS_DZHTXXCX			163

#define TDX_ID_FUNC_REQ_RZLSCX				164		// 认证流水查询 164
#define TDX_ID_FUNC_ANS_RZLSCX				165

#define TDX_ID_FUNC_REQ_KHYLXXCX			166		// 客户预留信息查询 166
#define TDX_ID_FUNC_ANS_KHYLXXCX			167

#define TDX_ID_FUNC_REQ_KHYLXXXG			168		// 客户预留信息修改 168
#define TDX_ID_FUNC_ANS_KHYLXXXG			169

#define TDX_ID_FUNC_REQ_KHCZQR				170		// 客户操作确认 170
#define TDX_ID_FUNC_ANS_KHCZQR				171

#define TDX_ID_FUNC_REQ_FYZDCX				172		// 翻译字典查询 172
#define TDX_ID_FUNC_ANS_FYZDCX				173

#define TDX_ID_FUNC_REQ_UPDATESESSION		174		// 更新会话信息 174
#define TDX_ID_FUNC_ANS_UPDATESESSION		175

#define TDX_ID_FUNC_REQ_WJLSCX				176		// 问卷流水查询 176
#define TDX_ID_FUNC_ANS_WJLSCX				177

#define TDX_ID_FUNC_REQ_SCINFO				178		// 获取市场信息 178
#define TDX_ID_FUNC_ANS_SCINFO				179

// 委托买卖类
#define TDX_ID_FUNC_REQ_WTCD				200		// 委托撤单 200
#define TDX_ID_FUNC_ANS_WTCD				201	
	
#define TDX_ID_FUNC_REQ_PTGPWT				202		// 普通股票委托 202
#define TDX_ID_FUNC_ANS_PTGPWT				203

#define TDX_ID_FUNC_REQ_ZQZGHS				204		// 债券转股回售 204
#define TDX_ID_FUNC_ANS_ZQZGHS				205

#define TDX_ID_FUNC_REQ_XGDD				206		// 修改订单 206
#define TDX_ID_FUNC_ANS_XGDD				207

#define TDX_ID_FUNC_REQ_SGXG				208		// 申购新股 208
#define TDX_ID_FUNC_ANS_SGXG				209

#define TDX_ID_FUNC_REQ_XGSGXG				210		// 新股申购修改 210
#define TDX_ID_FUNC_ANS_XGSGXG				211

#define TDX_ID_FUNC_REQ_XGSGCD				212		// 新股申购撤单 212
#define TDX_ID_FUNC_ANS_XGSGCD				213

#define TDX_ID_FUNC_REQ_PLWT				214		// 批量委托 214
#define TDX_ID_FUNC_ANS_PLWT				215

#define TDX_ID_FUNC_REQ_PLCD				216		// 批量撤单 216
#define TDX_ID_FUNC_ANS_PLCD				217

#define TDX_ID_FUNC_REQ_XZDDJC				218		// 新增订单检查 218
#define TDX_ID_FUNC_ANS_XZDDJC				219

#define TDX_ID_FUNC_REQ_XGDDJC				220		// 修改订单检查 220
#define TDX_ID_FUNC_ANS_XGDDJC				221

// 闪电手
#define TDX_ID_FUNC_REQ_SDSZJCX				250		// 闪电手资金查询 250
#define TDX_ID_FUNC_ANS_SDSZJCX				251

#define TDX_ID_FUNC_REQ_SDSGFCX				252		// 闪电手股份查询 252
#define TDX_ID_FUNC_ANS_SDSGFCX				253

#define TDX_ID_FUNC_REQ_SDSWTCX				254		// 闪电手委托查询 254
#define TDX_ID_FUNC_ANS_SDSWTCX				255

#define TDX_ID_FUNC_REQ_SDSCJCX				256		// 闪电手成交查询 256
#define TDX_ID_FUNC_ANS_SDSCJCX				257

#define TDX_ID_FUNC_REQ_SDSLSCX				258		// 闪电手流水查询 258
#define TDX_ID_FUNC_ANS_SDSLSCX				259

#define TDX_ID_FUNC_REQ_SDSXYZCCX			260		// 闪电手信用资产查询 260
#define TDX_ID_FUNC_ANS_SDSXYZCCX			261

#define TDX_ID_FUNC_REQ_SDSZQXXCX			262		// 闪电手证券信息查询 262
#define TDX_ID_FUNC_ANS_SDSZQXXCX			263

#define TDX_ID_FUNC_REQ_SDSKMSLCX			264		// 闪电手可买(卖)数量查询 264
#define TDX_ID_FUNC_ANS_SDSKMSLCX			265

// 委托买卖扩展(以及服务类型)
#define TDX_ID_FUNC_REQ_FQZQ				300		// 放弃中签 300
#define TDX_ID_FUNC_ANS_FQZQ				301

#define TDX_ID_FUNC_REQ_FW_KHZLCX			302		// (服务)客户资料查询 302
#define TDX_ID_FUNC_ANS_FW_KHZLCX			303

#define TDX_ID_FUNC_REQ_FW_HQDTKL			304		// (服务)获取动态口令 304
#define TDX_ID_FUNC_ANS_FW_HQDTKL			305

#define TDX_ID_FUNC_REQ_FW_CPDGPZ			306		// (服务)产品定购品种 306
#define TDX_ID_FUNC_ANS_FW_CPDGPZ			307

#define TDX_ID_FUNC_REQ_FW_CPDGCX			308		// (服务)产品定购查询 308
#define TDX_ID_FUNC_ANS_FW_CPDGCX			309

#define TDX_ID_FUNC_REQ_FW_CPDGSZ			310		// (服务)产品定购设置 310
#define TDX_ID_FUNC_ANS_FW_CPDGSZ			311

#define TDX_ID_FUNC_REQ_FW_CPDGXG			312		// (服务)产品定购修改 312
#define TDX_ID_FUNC_ANS_FW_CPDGXG			313

#define TDX_ID_FUNC_REQ_FW_CPDGQX			314		// (服务)产品定购取消 314
#define TDX_ID_FUNC_ANS_FW_CPDGQX			315

#define TDX_ID_FUNC_REQ_FW_ZJLS				316		// (服务)资金流水 316
#define TDX_ID_FUNC_ANS_FW_ZJLS				317

#define TDX_ID_FUNC_REQ_FW_PLHQCX			318		// (服务)批量行情查询 318
#define TDX_ID_FUNC_ANS_FW_PLHQCX			319

#define TDX_ID_FUNC_REQ_FW_ZXLMCX			320		// (服务)资讯栏目查询 320
#define TDX_ID_FUNC_ANS_FW_ZXLMCX			321

#define TDX_ID_FUNC_REQ_FW_HQTSXX			322		// (服务)获取提示信息 322
#define TDX_ID_FUNC_ANS_FW_HQTSXX			323

#define TDX_ID_FUNC_REQ_FW_TPFACX			324		// (服务)投票方案查询 324
#define TDX_ID_FUNC_ANS_FW_TPFACX			325

#define TDX_ID_FUNC_REQ_FW_TPXXCX			326		// (服务)投票信息查询 326
#define TDX_ID_FUNC_ANS_FW_TPXXCX			327

#define TDX_ID_FUNC_REQ_FW_TPJGTJ			328		// (服务)投票结果提交 328
#define TDX_ID_FUNC_ANS_FW_TPJGTJ			329

#define TDX_ID_FUNC_REQ_FW_TPJGCX			330		// (服务)投票结果查询 330
#define TDX_ID_FUNC_ANS_FW_TPJGCX			331

#define TDX_ID_FUNC_REQ_FW_TPTJCX			332		// (服务)投票统计查询 332
#define TDX_ID_FUNC_ANS_FW_TPTJCX			333

#define TDX_ID_FUNC_REQ_FW_TLZHDMCX			334		// (服务)套利组合代码查询 334
#define TDX_ID_FUNC_ANS_FW_TLZHDMCX			335

#define TDX_ID_FUNC_REQ_FW_TLZHCFCX			336		// (服务)套利组合成分查询 336
#define TDX_ID_FUNC_ANS_FW_TLZHCFCX			337

#define TDX_ID_FUNC_REQ_FW_DDDLCZ			338		// (服务)单点登录操作 338
#define TDX_ID_FUNC_ANS_FW_DDDLCZ			339

#define TDX_ID_FUNC_REQ_FW_PLXJCX			340		// (服务)批量现价查询 340
#define TDX_ID_FUNC_ANS_FW_PLXJCX			341

#define TDX_ID_FUNC_REQ_FW_XXDY				342		// (服务)信息订阅 342
#define TDX_ID_FUNC_ANS_FW_XXDY				343

#define TDX_ID_FUNC_REQ_FW_KHKCL			344		// (服务)客户卡处理 344
#define TDX_ID_FUNC_ANS_FW_KHKCL			345

#define TDX_ID_FUNC_REQ_FW_SCPZXX			346		// (服务)上传配置信息 346
#define TDX_ID_FUNC_ANS_FW_SCPZXX			347

#define TDX_ID_FUNC_REQ_FW_XZPZXX			348		// (服务)下载配置信息 348
#define TDX_ID_FUNC_ANS_FW_XZPZXX			349

#define TDX_ID_FUNC_REQ_FW_PZXXZYCX			350		// (服务)配置信息摘要查询 350
#define TDX_ID_FUNC_ANS_FW_PZXXZYCX			351

#define TDX_ID_FUNC_REQ_FW_CLKHCS			352		// (服务)处理客户参数 352
#define TDX_ID_FUNC_ANS_FW_CLKHCS			353

#define TDX_ID_FUNC_REQ_FW_PDLBCX			354		// (服务)配对列表查询 354
#define TDX_ID_FUNC_ANS_FW_PDLBCX			355

#define TDX_ID_FUNC_REQ_FW_PDLSLR			356		// (服务)配对流水录入 356
#define TDX_ID_FUNC_ANS_FW_PDLSLR			357

#define TDX_ID_FUNC_REQ_FW_PDLSCX			358		// (服务)配对流水查询 358
#define TDX_ID_FUNC_ANS_FW_PDLSCX			359

#define TDX_ID_FUNC_REQ_FW_ZZYWSF			360		// (服务)增值业务收费 360
#define TDX_ID_FUNC_ANS_FW_ZZYWSF			361

// 推送功能(只有应答有效)
#define TDX_ID_FUNC_REQ_PUSH_QZTC			400		// (推送)强制退出 400 [推送功能,请求不使用]
#define TDX_ID_FUNC_ANS_PUSH_QZTC			401		// (推送)强制退出 401

#define TDX_ID_FUNC_REQ_PUSH_XXTZ			402		// (推送)消息通知 402 [推送功能,请求不使用]
#define TDX_ID_FUNC_ANS_PUSH_XXTZ			403		// (推送)消息通知 403

#define TDX_ID_FUNC_REQ_PUSH_GGXX			404		// (推送)公告消息 404 [推送功能,请求不使用]
#define TDX_ID_FUNC_ANS_PUSH_GGXX			405		// (推送)公告消息 405

// 手机功能
#define TDX_ID_FUNC_REQ_MOBILE_ZQCX			500		// (手机)证券查询 500
#define TDX_ID_FUNC_ANS_MOBILE_ZQCX			501

#define TDX_ID_FUNC_REQ_MOBILE_GFCX			502		// (手机)股份查询 502
#define TDX_ID_FUNC_ANS_MOBILE_GFCX			503

#define TDX_ID_FUNC_REQ_MOBILE_ZJCX			504		// (手机)资金查询 504
#define TDX_ID_FUNC_ANS_MOBILE_ZJCX			505

#define TDX_ID_FUNC_REQ_MOBILE_CDCX			506		// (手机)撤单查询 506
#define TDX_ID_FUNC_ANS_MOBILE_CDCX			507

#define TDX_ID_FUNC_REQ_MOBILE_WTCX			508		// (手机)委托查询 508
#define TDX_ID_FUNC_ANS_MOBILE_WTCX			509

#define TDX_ID_FUNC_REQ_MOBILE_CJCX			510		// (手机)成交查询 510
#define TDX_ID_FUNC_ANS_MOBILE_CJCX			511

#define TDX_ID_FUNC_REQ_MOBILE_ZZCX			512		// (手机)转账查询 512
#define TDX_ID_FUNC_ANS_MOBILE_ZZCX			513

#define TDX_ID_FUNC_REQ_MOBILE_LSCX			514		// (手机)流水查询 514
#define TDX_ID_FUNC_ANS_MOBILE_LSCX			515

#define TDX_ID_FUNC_REQ_MOBILE_JGCX			516		// (手机)交割查询 516
#define TDX_ID_FUNC_ANS_MOBILE_JGCX			517

#define TDX_ID_FUNC_REQ_MOBILE_DZCX			518		// (手机)对账查询 518
#define TDX_ID_FUNC_ANS_MOBILE_DZCX			519

#define TDX_ID_FUNC_REQ_MOBILE_YXSBHQCX		520		// (手机)意向申报行情查询 520
#define TDX_ID_FUNC_ANS_MOBILE_YXSBHQCX		521

#define TDX_ID_FUNC_REQ_MOBILE_LSWTCX		522		// (手机)历史委托查询 522
#define TDX_ID_FUNC_ANS_MOBILE_LSWTCX		523

#define TDX_ID_FUNC_REQ_MOBILE_LSCJCX		524		// (手机)历史成交查询 524
#define TDX_ID_FUNC_ANS_MOBILE_LSCJCX		525

#define TDX_ID_FUNC_REQ_MOBILE_PHZQCX		526		// (手机)配号中签查询 526
#define TDX_ID_FUNC_ANS_MOBILE_PHZQCX		527

#define TDX_ID_FUNC_REQ_MOBILE_RZLSCX		528		// (手机)认证流水查询 528
#define TDX_ID_FUNC_ANS_MOBILE_RZLSCX		529

#define TDX_ID_FUNC_REQ_MOBILE_JJCDCX		530		// (手机)基金撤单查询 530
#define TDX_ID_FUNC_ANS_MOBILE_JJCDCX		531

#define TDX_ID_FUNC_REQ_MOBILE_JJDRWTCX		532		// (手机)基金当日委托查询 532
#define TDX_ID_FUNC_ANS_MOBILE_JJDRWTCX		533

#define TDX_ID_FUNC_REQ_MOBILE_JJLSWTCX		534		// (手机)基金历史委托查询 534
#define TDX_ID_FUNC_ANS_MOBILE_JJLSWTCX		535

#define TDX_ID_FUNC_REQ_MOBILE_JJDRCJCX		536		// (手机)基金当日成交查询 536
#define TDX_ID_FUNC_ANS_MOBILE_JJDRCJCX		537

#define TDX_ID_FUNC_REQ_MOBILE_JJLSCJCX		538		// (手机)基金历史成交查询 538
#define TDX_ID_FUNC_ANS_MOBILE_JJLSCJCX		539

#define TDX_ID_FUNC_REQ_MOBILE_JJZHCX		540		// (手机)基金账号查询 540
#define TDX_ID_FUNC_ANS_MOBILE_JJZHCX		541

#define TDX_ID_FUNC_REQ_MOBILE_JJGSCX		542		// (手机)基金公司查询 542
#define TDX_ID_FUNC_ANS_MOBILE_JJGSCX		543

#define TDX_ID_FUNC_REQ_MOBILE_JJDMCX		544		// (手机)基金代码查询 544
#define TDX_ID_FUNC_ANS_MOBILE_JJDMCX		545

#define TDX_ID_FUNC_REQ_MOBILE_JJFECX		546		// (手机)基金份额查询 546
#define TDX_ID_FUNC_ANS_MOBILE_JJFECX		547

#define TDX_ID_FUNC_REQ_MOBILE_JJDZCX		548		// (手机)基金对账查询 548
#define TDX_ID_FUNC_ANS_MOBILE_JJDZCX		549

#define TDX_ID_FUNC_REQ_MOBILE_JJJGCX		550		// (手机)基金交割查询 550
#define TDX_ID_FUNC_ANS_MOBILE_JJJGCX		551

#define TDX_ID_FUNC_REQ_MOBILE_JJFJYWTCX	552		// (手机)基金非交易委托查询 552
#define TDX_ID_FUNC_ANS_MOBILE_JJFJYWTCX	553

#define TDX_ID_FUNC_REQ_MOBILE_QHHYCX		560		// (手机)期货合约查询 560
#define TDX_ID_FUNC_ANS_MOBILE_QHHYCX		561

#define TDX_ID_FUNC_REQ_MOBILE_QHZHHYCX		562		// (手机)期货组合合约查询 562
#define TDX_ID_FUNC_ANS_MOBILE_QHZHHYCX		563

#define TDX_ID_FUNC_REQ_MOBILE_QHZHCCCX		564		// (手机)期货组合持仓查询 564
#define TDX_ID_FUNC_ANS_MOBILE_QHZHCCCX		565

#define TDX_ID_FUNC_REQ_MOBILE_QHZHWTCX		566		// (手机)期货组合委托查询 566
#define TDX_ID_FUNC_ANS_MOBILE_QHZHWTCX		567

#define TDX_ID_FUNC_REQ_MOBILE_QHZHCLCX		568		// (手机)期货组合策略查询 568
#define TDX_ID_FUNC_ANS_MOBILE_QHZHCLCX		569

#define TDX_ID_FUNC_REQ_MOBILE_GFHZCX		570		// (手机)股份汇总查询 570
#define TDX_ID_FUNC_ANS_MOBILE_GFHZCX		571

#define TDX_ID_FUNC_REQ_MOBILE_WTHZCX		572		// (手机)委托汇总查询 572
#define TDX_ID_FUNC_ANS_MOBILE_WTHZCX		573

#define TDX_ID_FUNC_REQ_MOBILE_CJHZCX		574		// (手机)成交汇总查询 574
#define TDX_ID_FUNC_ANS_MOBILE_CJHZCX		575

#define TDX_ID_FUNC_REQ_MOBILE_CJMXCX		576		// (手机)成交明细查询 576
#define TDX_ID_FUNC_ANS_MOBILE_CJMXCX		577


#define TDX_ID_FUNC_REQ_MOBILE_XYRZMRPTCX	600		// (手机)信用融资买入配套查询 600
#define TDX_ID_FUNC_ANS_MOBILE_XYRZMRPTCX	601

#define TDX_ID_FUNC_REQ_MOBILE_XYRQMCPTCX	602		// (手机)信用融券卖出配套查询 602
#define TDX_ID_FUNC_ANS_MOBILE_XYRQMCPTCX	603

#define TDX_ID_FUNC_REQ_MOBILE_XYMCHKPTCX	604		// (手机)信用卖出还款配套查询 604
#define TDX_ID_FUNC_ANS_MOBILE_XYMCHKPTCX	605

#define TDX_ID_FUNC_REQ_MOBILE_XYMRHQPTCX	606		// (手机)信用买入还券配套查询 606
#define TDX_ID_FUNC_ANS_MOBILE_XYMRHQPTCX	607

#define TDX_ID_FUNC_REQ_MOBILE_XYXJHKPTCX	608		// (手机)信用现金还款配套查询 608
#define TDX_ID_FUNC_ANS_MOBILE_XYXJHKPTCX	609

#define TDX_ID_FUNC_REQ_MOBILE_XYXQHQPTCX	610		// (手机)信用现券还券配套查询 610
#define TDX_ID_FUNC_ANS_MOBILE_XYXQHQPTCX	611

#define TDX_ID_FUNC_REQ_MOBILE_XYYQHZPTCX	612		// (手机)信用余券划转配套查询 612
#define TDX_ID_FUNC_ANS_MOBILE_XYYQHZPTCX	613

#define TDX_ID_FUNC_REQ_MOBILE_XYDBHZPTCX	614		// (手机)信用担保划转配套查询 614
#define TDX_ID_FUNC_ANS_MOBILE_XYDBHZPTCX	615

#define TDX_ID_FUNC_REQ_MOBILE_XYDBZRPTCX	616		// (手机)信用担保转入配套查询 616
#define TDX_ID_FUNC_ANS_MOBILE_XYDBZRPTCX	617

#define TDX_ID_FUNC_REQ_MOBILE_XYDBZCPTCX	618		// (手机)信用担保转出配套查询 618
#define TDX_ID_FUNC_ANS_MOBILE_XYDBZCPTCX	619

#define TDX_ID_FUNC_REQ_MOBILE_XYZCXXCX		620		// (手机)信用资产信息查询 620
#define TDX_ID_FUNC_ANS_MOBILE_XYZCXXCX		621

#define TDX_ID_FUNC_REQ_MOBILE_XYGFXXCX		622		// (手机)信用股份信息查询 622
#define TDX_ID_FUNC_ANS_MOBILE_XYGFXXCX		623

#define TDX_ID_FUNC_REQ_MOBILE_XYBDZQCX		624		// (手机)信用标的证券查询 624
#define TDX_ID_FUNC_ANS_MOBILE_XYBDZQCX		625

#define TDX_ID_FUNC_REQ_MOBILE_XYZJHZCX		626		// (手机)信用直接划转查询 626
#define TDX_ID_FUNC_ANS_MOBILE_XYZJHZCX		627

#define TDX_ID_FUNC_REQ_MOBILE_XYLXFYCX		628		// (手机)信用利息费用查询 628
#define TDX_ID_FUNC_ANS_MOBILE_XYLXFYCX		629

#define TDX_ID_FUNC_REQ_MOBILE_XYWPHYCX		630		// (手机)信用未平合约查询 630
#define TDX_ID_FUNC_ANS_MOBILE_XYWPHYCX		631

#define TDX_ID_FUNC_REQ_MOBILE_XYYPHYCX		632		// (手机)信用已平合约查询 632
#define TDX_ID_FUNC_ANS_MOBILE_XYYPHYCX		633

#define TDX_ID_FUNC_REQ_MOBILE_XYDRHYCX		634		// (手机)信用当日合约查询 634
#define TDX_ID_FUNC_ANS_MOBILE_XYDRHYCX		635

#define TDX_ID_FUNC_REQ_MOBILE_XYRZHYCX		636		// (手机)信用融资合约查询 636
#define TDX_ID_FUNC_ANS_MOBILE_XYRZHYCX		637

#define TDX_ID_FUNC_REQ_MOBILE_XYRQHYCX		638		// (手机)信用融券合约查询 638
#define TDX_ID_FUNC_ANS_MOBILE_XYRQHYCX		639

#define TDX_ID_FUNC_REQ_MOBILE_XYZJFZCX		640		// (手机)信用资金负债查询 640
#define TDX_ID_FUNC_ANS_MOBILE_XYZJFZCX		641

#define TDX_ID_FUNC_REQ_MOBILE_XYGFFZCX		642		// (手机)信用股份负债查询 642
#define TDX_ID_FUNC_ANS_MOBILE_XYGFFZCX		643

#define TDX_ID_FUNC_REQ_MOBILE_XYJYDBPZQCX	644		// (手机)信用交易担保品证券查询 644
#define TDX_ID_FUNC_ANS_MOBILE_XYJYDBPZQCX	645

#define TDX_ID_FUNC_REQ_MOBILE_XYJYFJYHZCX	646		// (手机)信用交易非交易化转查询 646
#define TDX_ID_FUNC_ANS_MOBILE_XYJYFJYHZCX	647

#define TDX_ID_FUNC_REQ_MOBILE_XYJYFZLSCX	648		// (手机)信用交易负债流水查询 648
#define TDX_ID_FUNC_ANS_MOBILE_XYJYFZLSCX	649	

#define TDX_ID_FUNC_REQ_MOBILE_ETFWTCX		700		// (手机)ETF委托查询 700
#define TDX_ID_FUNC_ANS_MOBILE_ETFWTCX		701

#define TDX_ID_FUNC_REQ_MOBILE_ETFCJCX		702		// (手机)ETF成交查询 702
#define TDX_ID_FUNC_ANS_MOBILE_ETFCJCX		703


#define	TDX_ID_FUNC_REQ_MOBILE_LCCPFECX		750		// (手机)理财产品份额查询 750
#define	TDX_ID_FUNC_ANS_MOBILE_LCCPFECX		751

#define	TDX_ID_FUNC_REQ_MOBILE_LCCPWTCX		752		// (手机)理财产品委托查询 752
#define	TDX_ID_FUNC_ANS_MOBILE_LCCPWTCX		753

#define	TDX_ID_FUNC_REQ_MOBILE_LCCPCJCX		754		// (手机)理财产品成交查询 754
#define	TDX_ID_FUNC_ANS_MOBILE_LCCPCJCX		755

#define	TDX_ID_FUNC_REQ_MOBILE_LCCPDMCX		756		// (手机)理财产品代码查询 756
#define	TDX_ID_FUNC_ANS_MOBILE_LCCPDMCX		757

#define	TDX_ID_FUNC_REQ_MOBILE_LCCPDQDESGCX	758		// (手机)理财产品定期定额申购查询 758
#define	TDX_ID_FUNC_ANS_MOBILE_LCCPDQDESGCX	759

#define	TDX_ID_FUNC_REQ_MOBILE_YHLCCPDMCX	790		// (手机)银行理财产品代码查询 790
#define	TDX_ID_FUNC_ANS_MOBILE_YHLCCPDMCX	791

#define	TDX_ID_FUNC_REQ_MOBILE_YHLCCPFECX	792		// (手机)银行理财产品份额查询 792
#define	TDX_ID_FUNC_ANS_MOBILE_YHLCCPFECX	793

#define	TDX_ID_FUNC_REQ_MOBILE_YHLCCPWTCX	794		// (手机)银行理财产品委托查询 794
#define	TDX_ID_FUNC_ANS_MOBILE_YHLCCPWTCX	795

#define	TDX_ID_FUNC_REQ_MOBILE_YHLCCPCJCX	796		// (手机)银行理财产品成交查询 796
#define	TDX_ID_FUNC_ANS_MOBILE_YHLCCPCJCX	797

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 安全中心协议及其他服务器协议(800~899)
#define TDX_ID_FUNC_REQ_CA_ZHSQ				800		// CA账户申请 800
#define TDX_ID_FUNC_ANS_CA_ZHSQ				801

#define TDX_ID_FUNC_REQ_CA_ZHCX				802		// CA帐号查询 802
#define TDX_ID_FUNC_ANS_CA_ZHCX				803

#define TDX_ID_FUNC_REQ_CA_ZHJY				804		// CA账户校验 804
#define TDX_ID_FUNC_ANS_CA_ZHJY				805

#define TDX_ID_FUNC_REQ_CA_TXMMXG			806		// CA认证口令修改 806
#define TDX_ID_FUNC_ANS_CA_TXMMXG			807

#define TDX_ID_FUNC_REQ_CA_TXMMCX			808		// CA认证口令查询 808
#define TDX_ID_FUNC_ANS_CA_TXMMCX			809

#define TDX_ID_FUNC_REQ_CA_ZSXZ				810		// CA证书下载 810
#define TDX_ID_FUNC_ANS_CA_ZSXZ				811

#define TDX_ID_FUNC_REQ_CA_ZSXZQR			812		// CA证书下载确认 812
#define TDX_ID_FUNC_ANS_CA_ZSXZQR			813

#define TDX_ID_FUNC_REQ_CA_ZTXM				814		// CA状态修改 814
#define TDX_ID_FUNC_ANS_CA_ZTXM				815

#define TDX_ID_FUNC_REQ_CA_ZSGX				816		// CA证书更新 816
#define TDX_ID_FUNC_ANS_CA_ZSGX				817

#define TDX_ID_FUNC_REQ_CA_YHFJCX			818		// 用户分级查询 818
#define TDX_ID_FUNC_ANS_CA_YHFJCX			819

#define TDX_ID_FUNC_REQ_CA_YHFJSQ			820		// 用户分级申请 820
#define TDX_ID_FUNC_ANS_CA_YHFJSQ			821

#define TDX_ID_FUNC_REQ_CA_HTTPYHFJCX		822		// HTTP用户分级查询 822
#define TDX_ID_FUNC_ANS_CA_HTTPYHFJCX		823

#define TDX_ID_FUNC_REQ_CA_ANONUSER			824		// 注册匿名用户 824
#define TDX_ID_FUNC_ANS_CA_ANONUSER			825

#define TDX_ID_FUNC_REQ_CA_XJZT				826		// 新建主题 826
#define TDX_ID_FUNC_ANS_CA_XJZT				827

#define TDX_ID_FUNC_REQ_CA_CXZT				828		// 查询主题 828
#define TDX_ID_FUNC_ANS_CA_CXZT				829

#define TDX_ID_FUNC_REQ_CA_CXHF				830		// 查询回复 830
#define TDX_ID_FUNC_ANS_CA_CXHF				831

#define TDX_ID_FUNC_REQ_CA_HFZT				832		// 回复主题 832
#define TDX_ID_FUNC_ANS_CA_HFZT				833

#define TDX_ID_FUNC_REQ_CA_GBZT				834		// 问题解决关闭主题 834
#define TDX_ID_FUNC_ANS_CA_GBZT				835

#define TDX_ID_FUNC_REQ_CA_USERMESSAGE		836		// 用户消息 836
#define TDX_ID_FUNC_ANS_CA_USERMESSAGE		837

#define TDX_ID_FUNC_REQ_CA_USERACTION		838		// 匿名用户激活 838
#define TDX_ID_FUNC_ANS_CA_USERACTION		839

#define TDX_ID_FUNC_REQ_CA_ANONYLOGIN		840		// 匿名用户登录 840
#define TDX_ID_FUNC_ANS_CA_ANONYLOGIN		841

#define TDX_ID_FUNC_REQ_CA_QUERYMSG			842		// 查询是否有最新留言 842
#define TDX_ID_FUNC_ANS_CA_QUERYMSG			843

#define TDX_ID_FUNC_REQ_CA_READED			844		// 已阅读留言 844
#define TDX_ID_FUNC_ANS_CA_READED			845

#define TDX_ID_FUNC_REQ_CA_NOTICEINFO		846		// 用户公告及生日提醒信息 846
#define TDX_ID_FUNC_ANS_CA_NOTICEINFO		847

#define TDX_ID_FUNC_REQ_CA_INFOFEEDBACK		848		// 用户资讯信息反馈 848
#define TDX_ID_FUNC_ANS_CA_INFOFEEDBACK		849
// 用户服务器协议
#define TDX_ID_FUNC_REQ_TQ_KHJY				860		// TQ客户端校验 860
#define TDX_ID_FUNC_ANS_TQ_KHJY				861

#define TDX_ID_FUNC_REQ_UM_UBROKER			862		// 西南证券用户投资顾问信息 862
#define TDX_ID_FUNC_ANS_UM_UBROKER			863

#define TDX_ID_FUNC_REQ_UC_QXCX				876		// 权限查询 876
#define TDX_ID_FUNC_ANS_UC_QXCX				876

#define TDX_ID_FUNC_REQ_UC_QXSQ				878		// 权限申请 878
#define TDX_ID_FUNC_ANS_UC_QXSQ				879

// 光大定制
#define TDX_ID_FUNC_REQ_CA_SYZC_GD			880		// 试用用户注册 880
#define TDX_ID_FUNC_ANS_CA_SYZC_GD			881

#define TDX_ID_FUNC_REQ_CA_XXLR_GD			882		// 详细信息录入 882
#define TDX_ID_FUNC_ANS_CA_XXLR_GD			883

#define TDX_ID_FUNC_REQ_CA_SYJH_GD			884		// 试用用户激活 884
#define TDX_ID_FUNC_ANS_CA_SYJH_GD			885

#define TDX_ID_FUNC_REQ_CA_ZHJY_GD			886		// 账户校验 886
#define TDX_ID_FUNC_ANS_CA_ZHJY_GD			887

#define TDX_ID_FUNC_REQ_CA_DJCX_GD			888		// 等级查询 888
#define TDX_ID_FUNC_ANS_CA_DJCX_GD			889

#define TDX_ID_FUNC_REQ_CA_KSJCX_GD			890		// 可申请级别查询 890
#define TDX_ID_FUNC_ANS_CA_KSJCX_GD			891

#define TDX_ID_FUNC_REQ_CA_KHSQ_GD			892		// 客户申请级别 892
#define TDX_ID_FUNC_ANS_CA_KHSQ_GD			893

#define TDX_ID_FUNC_REQ_CA_YHZXQX_GD		894		// 用户资讯权限 894
#define TDX_ID_FUNC_ANS_CA_YHZXQX_GD		895

#define TDX_ID_FUNC_REQ_CA_YHQXZX			896		// 用户权限注销 896
#define TDX_ID_FUNC_ANS_CA_YHQXZX			897

#define TDX_ID_FUNC_REQ_CA_CXDLLS			898		// 查询登陆历史 898
#define TDX_ID_FUNC_ANS_CA_CXDLLS			899	


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// 银证转帐类	
#define TDX_ID_FUNC_REQ_YZZZ				900		// 银证转帐 900
#define TDX_ID_FUNC_ANS_YZZZ				901
	
#define TDX_ID_FUNC_REQ_YHLS				902		// 银行流水 902
#define TDX_ID_FUNC_ANS_YHLS				903
	
#define TDX_ID_FUNC_REQ_YHYE				904		// 银行余额 904
#define TDX_ID_FUNC_ANS_YHYE				905
	
#define	TDX_ID_FUNC_REQ_XGYHMM				906		// 修改银行密码 906
#define	TDX_ID_FUNC_ANS_XGYHMM				907

#define TDX_ID_FUNC_REQ_YHXX				908		// 查询银行信息 908
#define TDX_ID_FUNC_ANS_YHXX				909

#define	TDX_ID_FUNC_REQ_SFCGZZ				910		// 三方存管转帐 910
#define	TDX_ID_FUNC_ANS_SFCGZZ				911

#define	TDX_ID_FUNC_REQ_SFZZCX				912		// 三方转帐查询 912
#define	TDX_ID_FUNC_ANS_SFZZCX				913

#define	TDX_ID_FUNC_REQ_SFYECX				914		// 三方余额查询 914
#define	TDX_ID_FUNC_ANS_SFYECX				915

#define	TDX_ID_FUNC_REQ_ZZXG				916		// 转帐修改 916
#define	TDX_ID_FUNC_ANS_ZZXG				917

#define	TDX_ID_FUNC_REQ_ZZQX				918		// 转帐取消 918
#define	TDX_ID_FUNC_ANS_ZZQX				919

#define	TDX_ID_FUNC_REQ_KQZJCX				920		// 可取资金查询 920
#define	TDX_ID_FUNC_ANS_KQZJCX				921

#define	TDX_ID_FUNC_REQ_ZZYHCX				922		// 转帐银行查询 922
#define	TDX_ID_FUNC_ANS_ZZYHCX				923

#define	TDX_ID_FUNC_REQ_YHZHJZZ				924		// 银行账户间转帐 924
#define	TDX_ID_FUNC_ANS_YHZHJZZ				925

#define	TDX_ID_FUNC_REQ_YDZJZZ				926		// 远端资金转账 926
#define	TDX_ID_FUNC_ANS_YDZJZZ				927

#define	TDX_ID_FUNC_REQ_YDZZCX				928		// 远端转账查询 928
#define	TDX_ID_FUNC_ANS_YDZZCX				929

#define	TDX_ID_FUNC_REQ_YDZJCX				930		// 远端资金查询 930
#define	TDX_ID_FUNC_ANS_YDZJCX				931

#define	TDX_ID_FUNC_REQ_YDKZCX				932		// 远端可转查询 932
#define	TDX_ID_FUNC_ANS_YDKZCX				933

#define	TDX_ID_FUNC_REQ_YHKLBCX				934		// 银行卡列表查询 934
#define	TDX_ID_FUNC_ANS_YHKLBCX				935

#define	TDX_ID_FUNC_REQ_YHKXXCX				936		// 银行卡信息查询 936
#define	TDX_ID_FUNC_ANS_YHKXXCX				937

#define	TDX_ID_FUNC_REQ_YHKXXXG				938		// 银行卡信息修改 938
#define	TDX_ID_FUNC_ANS_YHKXXXG				939

#define	TDX_ID_FUNC_REQ_YHKBGCZ				940		// 银行卡变更操作 940
#define	TDX_ID_FUNC_ANS_YHKBGCZ				941

#define	TDX_ID_FUNC_REQ_YHKFLCX				942		// 银行卡费率查询 942
#define	TDX_ID_FUNC_ANS_YHKFLCX				943

#define	TDX_ID_FUNC_REQ_ZHJZZLSCX			944		// 账号间转账流水查询 944
#define	TDX_ID_FUNC_ANS_ZHJZZLSCX			945

#define	TDX_ID_FUNC_REQ_ZHJZZDRLSCX			946		// 账号间转账当日流水查询 946
#define	TDX_ID_FUNC_ANS_ZHJZZDRLSCX			947

#define	TDX_ID_FUNC_REQ_YHYELSCX			948		// 银行余额流水查询 948
#define	TDX_ID_FUNC_ANS_YHYELSCX			949

#define	TDX_ID_FUNC_REQ_JHZZLSCX			950		// 计划转账流水查询 950
#define	TDX_ID_FUNC_ANS_JHZZLSCX			951

#define	TDX_ID_FUNC_REQ_DCGYHLSCX			952		// 多存管银行流水查询 952
#define	TDX_ID_FUNC_ANS_DCGYHLSCX			953

#define	TDX_ID_FUNC_REQ_DCGZHTB				954		// 多存管账号同步 954
#define	TDX_ID_FUNC_ANS_DCGZHTB				955

#define	TDX_ID_FUNC_REQ_HHYWCZ				990		// 换汇业务操作 990
#define	TDX_ID_FUNC_ANS_HHYWCZ				991

#define	TDX_ID_FUNC_REQ_HHYHCX				992		// 换汇银行查询 992
#define	TDX_ID_FUNC_ANS_HHYHCX				993

#define	TDX_ID_FUNC_REQ_HHHLCX				994		// 换汇汇率查询 994
#define	TDX_ID_FUNC_ANS_HHHLCX				995

#define	TDX_ID_FUNC_REQ_HHWTCX				996		// 换汇委托查询 996
#define	TDX_ID_FUNC_ANS_HHWTCX				997


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 日志查看类(1000~1099)
#define TDX_ID_FUNC_REQ_RZ_KHJY				1000	// 日志客户校验 1000
#define TDX_ID_FUNC_ANS_RZ_KHJY				1001

#define TDX_ID_FUNC_REQ_RZ_KHCZJLCX			1002	// 客户操作记录查询 1002
#define TDX_ID_FUNC_ANS_RZ_KHCZJLCX			1003

#define TDX_ID_FUNC_REQ_RZ_ZHSQ				1004	// 帐号申请 1004
#define TDX_ID_FUNC_ANS_RZ_ZHSQ				1005

#define TDX_ID_FUNC_REQ_RZ_ZHDJJD			1006	// 帐号冻结解冻 1006
#define TDX_ID_FUNC_ANS_RZ_ZHDJJD			1007

#define TDX_ID_FUNC_REQ_RZ_CXTJFX			1008	// 查询统计分析 1008
#define TDX_ID_FUNC_ANS_RZ_CXTJFX			1009

#define TDX_ID_FUNC_REQ_RZ_QDYGBCX			1010	// 启动与关闭查询 1010
#define TDX_ID_FUNC_ANS_RZ_QDYGBCX			1011

#define TDX_ID_FUNC_REQ_RZ_HTFMCD			1012	// 后台繁忙程度 1012
#define TDX_ID_FUNC_ANS_RZ_HTFMCD			1013

#define TDX_ID_FUNC_REQ_RZ_HTCFHCX			1014	// 后台超负荷查询 1014
#define TDX_ID_FUNC_ANS_RZ_HTCFHCX			1015

#define TDX_ID_FUNC_REQ_RZ_FXIPPM			1016	// 风险IP排名 1016
#define TDX_ID_FUNC_ANS_RZ_FXIPPM			1017

#define TDX_ID_FUNC_REQ_RZ_FXZH				1018	// 风险账号 1018
#define TDX_ID_FUNC_ANS_RZ_FXZH				1019

#define TDX_ID_FUNC_REQ_RZ_FXXXXX			1020	// 风险详细信息 1020
#define TDX_ID_FUNC_ANS_RZ_FXXXXX			1021

#define TDX_ID_FUNC_REQ_RZ_HTFMCDXX			1022	// 后台繁忙程度详细 1022
#define TDX_ID_FUNC_ANS_RZ_HTFMCDXX			1023

#define TDX_ID_FUNC_REQ_RZ_TCIP				1024	// 交易中心IP 1024
#define TDX_ID_FUNC_ANS_RZ_TCIP				1025


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// 查询类	
#define TDX_ID_FUNC_REQ_CDCX				1100	// 可撤单查询 1100
#define TDX_ID_FUNC_ANS_CDCX				1101
	
#define TDX_ID_FUNC_REQ_DRWTCX				1102	// 当日委托查询 1102
#define TDX_ID_FUNC_ANS_DRWTCX				1103

#define TDX_ID_FUNC_REQ_LSWTCX				1104	// 历史委托查询 1104
#define TDX_ID_FUNC_ANS_LSWTCX				1105

#define TDX_ID_FUNC_REQ_WTCX				1106	// 委托查询 1106
#define TDX_ID_FUNC_ANS_WTCX				1107

#define TDX_ID_FUNC_REQ_DRCJCX				1108	// 当日成交查询 1108
#define TDX_ID_FUNC_ANS_DRCJCX				1109

#define TDX_ID_FUNC_REQ_LSCJCX				1110	// 历史成交查询 1110
#define TDX_ID_FUNC_ANS_LSCJCX				1111

#define TDX_ID_FUNC_REQ_CJCX				1112	// 成交查询 1112
#define TDX_ID_FUNC_ANS_CJCX				1113

#define	TDX_ID_FUNC_REQ_GFCX				1114	// 股份查询 1114
#define	TDX_ID_FUNC_ANS_GFCX				1115

#define	TDX_ID_FUNC_REQ_XGPH				1116	// 新股配号 1116
#define	TDX_ID_FUNC_ANS_XGPH				1117

#define TDX_ID_FUNC_REQ_ZJLS				1118	// 资金流水 1118
#define TDX_ID_FUNC_ANS_ZJLS				1119

#define TDX_ID_FUNC_REQ_JGD					1120	// 交割单 1120
#define TDX_ID_FUNC_ANS_JGD					1121

#define TDX_ID_FUNC_REQ_GDCX				1122	// 股东查询 1122
#define TDX_ID_FUNC_ANS_GDCX				1123

#define TDX_ID_FUNC_REQ_ZQXX				1124	// 取证券信息 1124
#define TDX_ID_FUNC_ANS_ZQXX				1125

#define TDX_ID_FUNC_REQ_ZQCX				1126	// 中签查询 1126
#define TDX_ID_FUNC_ANS_ZQCX				1127

#define TDX_ID_FUNC_REQ_XGCBJ				1128	// 修改成本价 1128
#define TDX_ID_FUNC_ANS_XGCBJ				1129	

#define TDX_ID_FUNC_REQ_XGLXFS				1130	// (查询)修改联系方式 1130
#define TDX_ID_FUNC_ANS_XGLXFS				1131

#define TDX_ID_FUNC_REQ_DZD					1132	// 对帐单 1132
#define TDX_ID_FUNC_ANS_DZD					1133

#define TDX_ID_FUNC_REQ_PSQYCX				1134	// 配售权益查询 1134
#define TDX_ID_FUNC_ANS_PSQYCX				1135

#define TDX_ID_FUNC_REQ_QZXXCX				1136	// 权证信息查询 1136
#define TDX_ID_FUNC_ANS_QZXXCX				1137

#define TDX_ID_FUNC_REQ_CJHZCX				1138	// 成交汇总查询 1138
#define TDX_ID_FUNC_ANS_CJHZCX				1139

#define TDX_ID_FUNC_REQ_GFHZCX				1140	// 股份汇总查询 1140
#define TDX_ID_FUNC_ANS_GFHZCX				1141

#define TDX_ID_FUNC_REQ_KTXY				1142	// 开通取消协议 1142
#define TDX_ID_FUNC_ANS_KTXY				1143

#define TDX_ID_FUNC_REQ_YWTCX				1144	// 欲委托查询 1144
#define TDX_ID_FUNC_ANS_YWTCX				1145

#define TDX_ID_FUNC_REQ_QDXY				1146	// 签订协议 1146
#define TDX_ID_FUNC_ANS_QDXY				1147

#define TDX_ID_FUNC_REQ_ZTZJCX				1148	// 在途资金查询 1148
#define TDX_ID_FUNC_ANS_ZTZJCX				1149

#define TDX_ID_FUNC_REQ_JGXZZ				1150	// 金股信转帐 1150
#define TDX_ID_FUNC_ANS_JGXZZ				1151

#define TDX_ID_FUNC_REQ_FZDM				1152	// 东莞获取网点代码 1152
#define TDX_ID_FUNC_ANS_FZDM				1153

#define TDX_ID_FUNC_REQ_HQXYNR				1154	// 获取协议内容 1154
#define TDX_ID_FUNC_ANS_HQXYNR				1155

#define TDX_ID_FUNC_REQ_HQIPOLB				1156	// 获取IPO列表 1156
#define TDX_ID_FUNC_ANS_HQIPOLB				1157

#define TDX_ID_FUNC_REQ_IPOXXCX				1158	// IPO信息查询 1158
#define TDX_ID_FUNC_ANS_IPOXXCX				1159

#define TDX_ID_FUNC_REQ_YYCX				1160	// 预受要约查询 1160
#define TDX_ID_FUNC_ANS_YYCX				1161

#define TDX_ID_FUNC_REQ_YYCD				1162	// 预受要约撤单 1162
#define TDX_ID_FUNC_ANS_YYCD				1163

#define TDX_ID_FUNC_REQ_YYSB				1164	// 预受要约申报 1164
#define TDX_ID_FUNC_ANS_YYSB				1165

#define TDX_ID_FUNC_REQ_ZYHG				1166	// 质押回购 1166
#define TDX_ID_FUNC_ANS_ZYHG				1167

#define TDX_ID_FUNC_REQ_WJSCJMXCX			1168	// 未交收成交明细查询 1168
#define TDX_ID_FUNC_ANS_WJSCJMXCX			1169

#define TDX_ID_FUNC_REQ_CGYYCQ				1170	// 存管预约存取业务 1170
#define TDX_ID_FUNC_ANS_CGYYCQ				1171

#define TDX_ID_FUNC_REQ_CGYYCQCX			1172	// 存管预约存取业务查询 1172
#define TDX_ID_FUNC_ANS_CGYYCQCX			1173

#define	TDX_ID_FUNC_REQ_WTHZCX				1174	// 委托汇总查询 1174
#define	TDX_ID_FUNC_ANS_WTHZCX				1175

#define	TDX_ID_FUNC_REQ_ZJMXCX				1176	// 资金明细查询 1176
#define	TDX_ID_FUNC_ANS_ZJMXCX				1177

#define	TDX_ID_FUNC_REQ_CXXZCGYH			1178	// 查询选择存管银行 1178
#define	TDX_ID_FUNC_ANS_CXXZCGYH			1179

#define	TDX_ID_FUNC_REQ_XZCGYH				1180	// 选择存管银行 1180
#define	TDX_ID_FUNC_ANS_XZCGYH				1181

#define	TDX_ID_FUNC_REQ_CXXYXX				1182	// 查询协议信息 1182
#define	TDX_ID_FUNC_ANS_CXXYXX				1183

#define	TDX_ID_FUNC_REQ_LSCJHZCX			1184	// 历史成交汇总查询 1184
#define	TDX_ID_FUNC_ANS_LSCJHZCX			1185

#define	TDX_ID_FUNC_REQ_CJMXCX				1186	// 成交明细查询 1186
#define	TDX_ID_FUNC_ANS_CJMXCX				1187

#define	TDX_ID_FUNC_REQ_WTCXMX				1188	// 委托查询明细 1188
#define	TDX_ID_FUNC_ANS_WTCXMX				1189

#define	TDX_ID_FUNC_REQ_CJCXMX				1190	// 成交查询明细 1190
#define	TDX_ID_FUNC_ANS_CJCXMX				1191

#define	TDX_ID_FUNC_REQ_YXSBHQCX			1192	// 意向申报行情查询 1192
#define	TDX_ID_FUNC_ANS_YXSBHQCX			1193

#define	TDX_ID_FUNC_REQ_PLWTCX				1194	// 批量委托查询 1194
#define	TDX_ID_FUNC_ANS_PLWTCX				1195

#define	TDX_ID_FUNC_REQ_LOFHBXGDMCX			1196	// LOF合并相关代码查询 1196
#define	TDX_ID_FUNC_ANS_LOFHBXGDMCX			1197

#define	TDX_ID_FUNC_REQ_LOFFCXGDMCX			1198	// LOF分拆相关代码查询 1198
#define	TDX_ID_FUNC_ANS_LOFFCXGDMCX			1199

#define	TDX_ID_FUNC_REQ_LOFPHYWDRWTCX		1200	// LOF盘后业务当日委托查询 1200
#define	TDX_ID_FUNC_ANS_LOFPHYWDRWTCX		1201

#define	TDX_ID_FUNC_REQ_LOFPHYWLSWTCX		1202	// LOF盘后业务历史委托查询 1202
#define	TDX_ID_FUNC_ANS_LOFPHYWLSWTCX		1203

#define	TDX_ID_FUNC_REQ_LOFPHYWDRCJCX		1204	// LOF盘后业务当日成交查询 1204
#define	TDX_ID_FUNC_ANS_LOFPHYWDRCJCX		1205

#define	TDX_ID_FUNC_REQ_LOFPHYWLSCJCX		1206	// LOF盘后业务历史成交查询 1206
#define	TDX_ID_FUNC_ANS_LOFPHYWLSCJCX		1207

#define	TDX_ID_FUNC_REQ_LOFPHYWCDCX			1208	// LOF盘后业务撤单查询 1208
#define	TDX_ID_FUNC_ANS_LOFPHYWCDCX			1209

#define	TDX_ID_FUNC_REQ_FSGFCX				1210	// 附属股份查询 1210
#define	TDX_ID_FUNC_ANS_FSGFCX				1211

#define	TDX_ID_FUNC_REQ_ZQFSXXCX			1212	// 证券附属信息查询 1212
#define	TDX_ID_FUNC_ANS_ZQFSXXCX			1213

#define	TDX_ID_FUNC_REQ_BJZRCDCX			1214	// 报价转让撤单查询 1214
#define	TDX_ID_FUNC_ANS_BJZRCDCX			1215

#define	TDX_ID_FUNC_REQ_BJZRWTCX			1216	// 报价转让委托查询 1216
#define	TDX_ID_FUNC_ANS_BJZRWTCX			1217

#define	TDX_ID_FUNC_REQ_BJZRCJCX			1218	// 报价转让成交查询 1218
#define	TDX_ID_FUNC_ANS_BJZRCJCX			1219

#define	TDX_ID_FUNC_REQ_DTGFCX				1220	// 动态股份查询 1220
#define	TDX_ID_FUNC_ANS_DTGFCX				1221

#define	TDX_ID_FUNC_REQ_ZQZYKCX				1222	// 债券质押库查询 1222
#define	TDX_ID_FUNC_ANS_ZQZYKCX				1223

#define	TDX_ID_FUNC_REQ_DCGZJMXCX			1224	// 多存管资金明细查询 1224
#define	TDX_ID_FUNC_ANS_DCGZJMXCX			1225

#define	TDX_ID_FUNC_REQ_LSCCCX				1226	// 历史持仓查询 1226
#define	TDX_ID_FUNC_ANS_LSCCCX				1227

#define	TDX_ID_FUNC_REQ_GFMXCX				1228	// 股份明细查询 1228
#define	TDX_ID_FUNC_ANS_GFMXCX				1229

#define	TDX_ID_FUNC_REQ_GFCX_SECOND			1230	// 股份查询(2nd版) 1230
#define	TDX_ID_FUNC_ANS_GFCX_SECOND			1231

#define	TDX_ID_FUNC_REQ_GFCX_THIRD			1232	// 股份查询(3rd版) 1232
#define	TDX_ID_FUNC_ANS_GFCX_THIRD			1233

#define	TDX_ID_FUNC_REQ_ZQHGHYCX			1234	// 债券回购合约查询 1234
#define	TDX_ID_FUNC_ANS_ZQHGHYCX			1235

#define	TDX_ID_FUNC_REQ_KHDZXXCX			1236	// 客户对账信息查询 1236
#define	TDX_ID_FUNC_ANS_KHDZXXCX			1237

#define	TDX_ID_FUNC_REQ_ZHXYHQCX			1238	// 综合协议行情查询 1238
#define	TDX_ID_FUNC_ANS_ZHXYHQCX			1239

#define	TDX_ID_FUNC_REQ_BZQHZCX				1240	// 标准券汇总查询 1240
#define	TDX_ID_FUNC_ANS_BZQHZCX				1241

#define	TDX_ID_FUNC_REQ_GTZQHQCX			1242	// 柜台债券行情查询 1242
#define	TDX_ID_FUNC_ANS_GTZQHQCX			1243

#define	TDX_ID_FUNC_REQ_RZXQHYCX			1244	// 融资行权合约查询 1244
#define	TDX_ID_FUNC_ANS_RZXQHYCX			1245

#define	TDX_ID_FUNC_REQ_RZXQKHXXCX			1246	// 融资行权客户信息查询 1246
#define	TDX_ID_FUNC_ANS_RZXQKHXXCX			1247

#define	TDX_ID_FUNC_REQ_ZQHGLSCX			1248	// 债券回购历史查询 1248
#define	TDX_ID_FUNC_ANS_ZQHGLSCX			1249

#define	TDX_ID_FUNC_REQ_QQDMCX				1250	// 期权代码查询 1250
#define	TDX_ID_FUNC_ANS_QQDMCX				1251

#define	TDX_ID_FUNC_REQ_QQCCCX				1252	// 期权持仓查询 1252
#define	TDX_ID_FUNC_ANS_QQCCCX				1253

#define	TDX_ID_FUNC_REQ_QQSDSCX				1254	// 期权所得税查询 1254
#define	TDX_ID_FUNC_ANS_QQSDSCX				1255

#define	TDX_ID_FUNC_REQ_QQDRWTCX			1256	// 期权当日委托查询 1256
#define	TDX_ID_FUNC_ANS_QQDRWTCX			1257

#define	TDX_ID_FUNC_REQ_QQLSWTCX			1258	// 期权历史委托查询 1258
#define	TDX_ID_FUNC_ANS_QQLSWTCX			1259


// 期货交易类
#define TDX_ID_FUNC_REQ_QHWT				1500	// 期货委托 1500
#define TDX_ID_FUNC_ANS_QHWT				1501

#define TDX_ID_FUNC_REQ_CXQHCC				1502	// 查询期货持仓 1502
#define TDX_ID_FUNC_ANS_CXQHCC				1503

#define TDX_ID_FUNC_REQ_CXHYXX				1504	// 查询期货合约信息 1504
#define TDX_ID_FUNC_ANS_CXHYXX				1505

#define TDX_ID_FUNC_REQ_CXKJYHY				1506	// 查询可交易合约 1506
#define TDX_ID_FUNC_ANS_CXKJYHY				1507

#define TDX_ID_FUNC_REQ_DRZJLS				1508	// 当日资金流水 1508
#define TDX_ID_FUNC_ANS_DRZJLS				1509

#define	TDX_ID_FUNC_REQ_QHWTZTCX			1510	// 期货委托状态查询 1510
#define	TDX_ID_FUNC_ANS_QHWTZTCX			1511

#define	TDX_ID_FUNC_REQ_QHWTHB				1512	// 期货委托回报 1512 [推送功能,请求不使用]
#define	TDX_ID_FUNC_ANS_QHWTHB				1513	// 期货委托回报 1513

#define	TDX_ID_FUNC_REQ_QHCDHB				1514	// 期货撤单回报 1514 [推送功能,请求不使用]
#define	TDX_ID_FUNC_ANS_QHCDHB				1515	// 期货撤单回报 1515

#define	TDX_ID_FUNC_REQ_QHCJHB				1516	// 期货成交回报 1516 [推送功能,请求不使用]
#define	TDX_ID_FUNC_ANS_QHCJHB				1517	// 期货成交回报 1517

#define	TDX_ID_FUNC_REQ_QHXXFB				1518	// 期货信息发布 1518 [推送功能,请求不使用]
#define	TDX_ID_FUNC_ANS_QHXXFB				1519	// 期货信息发布 1519

#define	TDX_ID_FUNC_REQ_QHJYSZTGB			1520	// 期货交易所状态改变 1520 [推送功能,请求不使用]
#define TDX_ID_FUNC_ANS_QHJYSZTGB			1521	// 期货交易所状态改变 1521

#define	TDX_ID_FUNC_REQ_QHZHHYBG			1522	// 期货组合合约变更 1522 [推送功能,请求不使用]
#define TDX_ID_FUNC_ANS_QHZHHYBG			1523	// 期货组合合约变更 1523

#define	TDX_ID_FUNC_REQ_QHZHWTHB			1524	// 期货组合委托回报 1524 [推送功能,请求不使用]
#define TDX_ID_FUNC_ANS_QHZHWTHB			1525	// 期货组合委托回报 1525

#define	TDX_ID_FUNC_REQ_QHZHCDHB			1526	// 期货组合撤单回报 1526 [推送功能,请求不使用]
#define TDX_ID_FUNC_ANS_QHZHCDHB			1527	// 期货组合撤单回报 1527

#define	TDX_ID_FUNC_REQ_QHDDLXCX			1528	// 期货订单类型查询 1528
#define	TDX_ID_FUNC_ANS_QHDDLXCX			1529

#define	TDX_ID_FUNC_REQ_QHZHWT				1530	// 期货组合委托 1530
#define	TDX_ID_FUNC_ANS_QHZHWT				1531

#define	TDX_ID_FUNC_REQ_QHZHCD				1532	// 期货组合撤单 1532
#define	TDX_ID_FUNC_ANS_QHZHCD				1533

#define	TDX_ID_FUNC_REQ_QHZHHYCX			1534	// 期货组合合约查询 1534
#define	TDX_ID_FUNC_ANS_QHZHHYCX			1535

#define	TDX_ID_FUNC_REQ_QHZHCCCX			1536	// 期货组合持仓查询 1536
#define	TDX_ID_FUNC_ANS_QHZHCCCX			1537

#define	TDX_ID_FUNC_REQ_QHZHWTCX			1538	// 期货组合委托查询 1538
#define	TDX_ID_FUNC_ANS_QHZHWTCX			1539

#define	TDX_ID_FUNC_REQ_QHZHJSKWTS			1540	// 期货组合计算可委托数 1540
#define	TDX_ID_FUNC_ANS_QHZHJSKWTS			1541

#define	TDX_ID_FUNC_REQ_QHZHCLCX			1542	// 期货组合策略查询 1542
#define	TDX_ID_FUNC_ANS_QHZHCLCX			1543

// 回购类
#define TDX_ID_FUNC_REQ_GPZYHG				1800	// 股票质押回购 1800
#define TDX_ID_FUNC_ANS_GPZYHG				1801

#define TDX_ID_FUNC_REQ_GPZYHG_SQCX			1802	// 股票质押回购申请查询 1802
#define TDX_ID_FUNC_ANS_GPZYHG_SQCX			1803

#define TDX_ID_FUNC_REQ_GPZYHG_HTCX			1804	// 股票质押回购合同查询 1804
#define TDX_ID_FUNC_ANS_GPZYHG_HTCX			1805

#define TDX_ID_FUNC_REQ_GPZYHG_QYCX			1806	// 股票质押回购权益查询 1806
#define TDX_ID_FUNC_ANS_GPZYHG_QYCX			1807

#define TDX_ID_FUNC_REQ_GPZYHG_QXLLCX		1808	// 股票质押回购期限利率查询 1808
#define TDX_ID_FUNC_ANS_GPZYHG_QXLLCX		1809

#define TDX_ID_FUNC_REQ_GPZYHG_LSCX			1810	// 股票质押回购流水查询 1810
#define TDX_ID_FUNC_ANS_GPZYHG_LSCX			1811

#define TDX_ID_FUNC_REQ_GPZYHG_RCFCX		1812	// 股票质押回购融出方查询 1812
#define TDX_ID_FUNC_ANS_GPZYHG_RCFCX		1813

#define TDX_ID_FUNC_REQ_GPZYHG_LXCX			1814	// 股票质押回购利息查询 1814
#define TDX_ID_FUNC_ANS_GPZYHG_LXCX			1815

#define TDX_ID_FUNC_REQ_GPZYHG_LSHTCX		1816	// 股票质押回购历史合同查询 1816
#define TDX_ID_FUNC_ANS_GPZYHG_LSHTCX		1817

#define TDX_ID_FUNC_REQ_GPZYHG_BDZQCX		1818	// 股票质押回购标的证券查询 1818
#define TDX_ID_FUNC_ANS_GPZYHG_BDZQCX		1819

#define TDX_ID_FUNC_REQ_TSHG				1830	// 特色回购 1830
#define TDX_ID_FUNC_ANS_TSHG				1831

#define TDX_ID_FUNC_REQ_TSHG_XXCX			1832	// 特色回购信息查询 1832
#define TDX_ID_FUNC_ANS_TSHG_XXCX			1833

#define TDX_ID_FUNC_REQ_TSHG_SQCX			1834	// 特色回购申请查询 1834
#define TDX_ID_FUNC_ANS_TSHG_SQCX			1835

#define TDX_ID_FUNC_REQ_TSHG_DMCX			1836	// 特色回购代码查询 1836
#define TDX_ID_FUNC_ANS_TSHG_DMCX			1837

#define TDX_ID_FUNC_REQ_TSHG_YZT			1838	// 特色回购银证通 1838
#define TDX_ID_FUNC_ANS_TSHG_YZT			1839

#define TDX_ID_FUNC_REQ_TSHG_ZZJHCX			1840	// 特色回购转账计划查询 1840
#define TDX_ID_FUNC_ANS_TSHG_ZZJHCX			1841

#define TDX_ID_FUNC_REQ_TSHG_LSCX			1842	// 特色回购流水查询 1842
#define TDX_ID_FUNC_ANS_TSHG_LSCX			1843


#define TDX_ID_FUNC_REQ_PSZTSZ				2000	// 配售状态设置(查询) 2000
#define TDX_ID_FUNC_ANS_PSZTSZ				2001

#define TDX_ID_FUNC_REQ_HZHG				2002	// 合作回购 2002
#define TDX_ID_FUNC_ANS_HZHG				2003

#define TDX_ID_FUNC_REQ_HZHGZT				2004	// 合作回购状态(查询) 2004
#define TDX_ID_FUNC_ANS_HZHGZT				2005

#define TDX_ID_FUNC_REQ_HZSGZT				2006	// 合作申购状态(查询) 2006
#define TDX_ID_FUNC_ANS_HZSGZT				2007

#define TDX_ID_FUNC_REQ_HZHGCPDMCX			2008	// 合作回购产品代码查询 2008
#define TDX_ID_FUNC_ANS_HZHGCPDMCX			2009

#define TDX_ID_FUNC_REQ_HZHGCPXXCX			2010	// 合作回购产品信息查询 2010
#define TDX_ID_FUNC_ANS_HZHGCPXXCX			2011

#define TDX_ID_FUNC_REQ_HZHGTQZZCX			2012	// 合作回购提前终止查询 2012
#define TDX_ID_FUNC_ANS_HZHGTQZZCX			2013

#define TDX_ID_FUNC_REQ_HZHGDRWTCX			2014	// 合作回购当日委托查询 2014
#define TDX_ID_FUNC_ANS_HZHGDRWTCX			2015

#define TDX_ID_FUNC_REQ_HZHGDRCJCX			2016	// 合作回购当日成交查询 2016
#define TDX_ID_FUNC_ANS_HZHGDRCJCX			2017

#define TDX_ID_FUNC_REQ_HZHGLSWTCX			2018	// 合作回购历史委托查询 2018
#define TDX_ID_FUNC_ANS_HZHGLSWTCX			2019

#define TDX_ID_FUNC_REQ_HZHGLSCJCX			2020	// 合作回购历史成交查询 2020
#define TDX_ID_FUNC_ANS_HZHGLSCJCX			2021

#define TDX_ID_FUNC_REQ_HZHGQNHYCX			2022	// 合作回购期内合约查询 2022
#define TDX_ID_FUNC_ANS_HZHGQNHYCX			2023

#define TDX_ID_FUNC_REQ_HZHGCDCX			2024	// 合作回购撤单查询 2024
#define TDX_ID_FUNC_ANS_HZHGCDCX			2025

#define TDX_ID_FUNC_REQ_HZHGXYCX			2026	// 合作回购续约查询 2026
#define TDX_ID_FUNC_ANS_HZHGXYCX			2027

#define TDX_ID_FUNC_REQ_HZHGXYZZCX			2028	// 合作回购续约终止查询 2028
#define TDX_ID_FUNC_ANS_HZHGXYZZCX			2029

#define TDX_ID_FUNC_REQ_HZHGTQZZYYCX		2030	// 合作回购提前终止预约查询 2030
#define TDX_ID_FUNC_ANS_HZHGTQZZYYCX		2031

#define TDX_ID_FUNC_REQ_HZHGTQZZYYCXCX		2032	// 合作回购提前终止预约撤销查询 2032
#define TDX_ID_FUNC_ANS_HZHGTQZZYYCXCX		2033

#define TDX_ID_FUNC_REQ_HZHGDYZYWCX			2034	// 合作回购对应质押物查询 2034
#define TDX_ID_FUNC_ANS_HZHGDYZYWCX			2035

#define TDX_ID_FUNC_REQ_HZHGXYCDCX			2036	// 合作回购续约撤单查询 2036
#define TDX_ID_FUNC_ANS_HZHGXYCDCX			2037

#define TDX_ID_FUNC_REQ_HZHGDRDQCX			2038	// 合作回购当日到期查询 2038
#define TDX_ID_FUNC_ANS_HZHGDRDQCX			2039

#define TDX_ID_FUNC_REQ_HZHGLSDQCX			2040	// 合作回购历史到期查询 2040
#define TDX_ID_FUNC_ANS_HZHGLSDQCX			2041

#define TDX_ID_FUNC_REQ_HZHGXZZZYYCX		2042	// 合作回购续作终止预约查询 2042
#define TDX_ID_FUNC_ANS_HZHGXZZZYYCX		2043

#define TDX_ID_FUNC_REQ_HZHGXZZZYYCXCX		2044	// 合作回购续作终止预约撤销查询 2044
#define TDX_ID_FUNC_ANS_HZHGXZZZYYCXCX		2045

#define TDX_ID_FUNC_REQ_HZHGXYBGCX			2046	// 合作回购续约变更查询 2046
#define TDX_ID_FUNC_ANS_HZHGXYBGCX			2047

#define TDX_ID_FUNC_REQ_HZHGHYSYCX			2048	// 合作回购合约收益查询 2048
#define TDX_ID_FUNC_ANS_HZHGHYSYCX			2049

#define TDX_ID_FUNC_REQ_SZBJHGCPDMCX		2050	// 深圳报价回购产品代码查询 2050
#define TDX_ID_FUNC_ANS_SZBJHGCPDMCX		2051

#define TDX_ID_FUNC_REQ_SZBJHGQNHYCX		2052	// 深圳报价回购期内合约查询 2052
#define TDX_ID_FUNC_ANS_SZBJHGQNHYCX		2053

#define TDX_ID_FUNC_REQ_HZHGXYSZPTCX		2054	// 合作回购协议设置配套查询 2054
#define TDX_ID_FUNC_ANS_HZHGXYSZPTCX		2055

#define TDX_ID_FUNC_REQ_YDHGCSJYPTCX		2070	// 约定回购初始交易配套查询 2070
#define TDX_ID_FUNC_ANS_YDHGCSJYPTCX		2071

#define TDX_ID_FUNC_REQ_YDHGLYBZPTCX		2072	// 约定回购履约保障配套查询 2072
#define TDX_ID_FUNC_ANS_YDHGLYBZPTCX		2073

#define TDX_ID_FUNC_REQ_YDHGTQGHPTCX		2074	// 约定回购提前购回配套查询 2074
#define TDX_ID_FUNC_ANS_YDHGTQGHPTCX		2075

#define TDX_ID_FUNC_REQ_YDHGYQSQPTCX		2076	// 约定回购延期申请配套查询 2076
#define TDX_ID_FUNC_ANS_YDHGYQSQPTCX		2077

#define TDX_ID_FUNC_REQ_YDHGJYCDPTCX		2078	// 约定回购交易撤单配套查询 2078
#define TDX_ID_FUNC_ANS_YDHGJYCDPTCX		2079

#define TDX_ID_FUNC_REQ_YDHGDQHYCX			2080	// 约定回购当前合约查询 2080
#define TDX_ID_FUNC_ANS_YDHGDQHYCX			2081

#define TDX_ID_FUNC_REQ_YDHGLSHYCX			2082	// 约定回购历史合约查询 2082
#define TDX_ID_FUNC_ANS_YDHGLSHYCX			2083

#define TDX_ID_FUNC_REQ_YDHGJXHYCX			2084	// 约定回购进行合约查询 2084
#define TDX_ID_FUNC_ANS_YDHGJXHYCX			2085

#define TDX_ID_FUNC_REQ_YDHGZZHYCX			2086	// 约定回购终止合约查询 2086
#define TDX_ID_FUNC_ANS_YDHGZZHYCX			2087

#define TDX_ID_FUNC_REQ_YDHGBDZQCX			2088	// 约定回购标的证券查询 2088
#define TDX_ID_FUNC_ANS_YDHGBDZQCX			2089

#define TDX_ID_FUNC_REQ_YDHGCPXXCX			2090	// 约定回购产品信息查询 2090
#define TDX_ID_FUNC_ANS_YDHGCPXXCX			2091

#define TDX_ID_FUNC_REQ_YDHGZHXXCX			2092	// 约定回购综合信息查询 2092
#define TDX_ID_FUNC_ANS_YDHGZHXXCX			2093

#define TDX_ID_FUNC_REQ_YDHGYWCZ			2098	// 约定回购业务操作(信息查询) 2098
#define TDX_ID_FUNC_ANS_YDHGYWCZ			2099

// 开放式基金类
#define TDX_ID_FUNC_REQ_KFSJJWT				2100	// 开放式基金委托 2100
#define TDX_ID_FUNC_ANS_KFSJJWT				2101

#define TDX_ID_FUNC_REQ_KFSJJWTCD			2102	// 基金委托撤单 2102
#define TDX_ID_FUNC_ANS_KFSJJWTCD			2103

#define TDX_ID_FUNC_REQ_KFSJJZH				2104	// 转换 2104
#define TDX_ID_FUNC_ANS_KFSJJZH				2105

#define TDX_ID_FUNC_REQ_KFSJJFECX			2106	// 份额查询 2106
#define TDX_ID_FUNC_ANS_KFSJJFECX			2107

#define TDX_ID_FUNC_REQ_KFSJJWTCX			2108	// 基金委托查询 2108
#define TDX_ID_FUNC_ANS_KFSJJWTCX			2109

#define TDX_ID_FUNC_REQ_KFSJJXXCX			2110	// 基金相关信息查询 2110
#define TDX_ID_FUNC_ANS_KFSJJXXCX			2111

#define TDX_ID_FUNC_REQ_KFSJJCJCX			2112	// 成交查询 2112
#define TDX_ID_FUNC_ANS_KFSJJCJCX			2113

#define TDX_ID_FUNC_REQ_KFSJJFH				2114	// 基金分红 2114
#define TDX_ID_FUNC_ANS_KFSJJFH				2115

#define TDX_ID_FUNC_REQ_KFSJJDMCX			2116	// 查基金代码 2116
#define TDX_ID_FUNC_ANS_KFSJJDMCX			2117

#define TDX_ID_FUNC_REQ_KFSJJZJZHKH			2118	// 基金资金帐号开户 2118
#define TDX_ID_FUNC_ANS_KFSJJZJZHKH			2119

#define TDX_ID_FUNC_REQ_KFSJJZJZHZC			2120	// 基金资金帐号注册 2120
#define TDX_ID_FUNC_ANS_KFSJJZJZHZC			2121

#define TDX_ID_FUNC_REQ_KFSJJKHZLXG			2122	// 客户资料修改 2122
#define TDX_ID_FUNC_ANS_KFSJJKHZLXG			2123

#define TDX_ID_FUNC_REQ_KFSJJCXGSDM			2124	// 查询基金公司代码 2124
#define TDX_ID_FUNC_ANS_KFSJJCXGSDM			2125

#define TDX_ID_FUNC_REQ_KFSJJZHCX			2126	// 查询基金帐号 2126
#define TDX_ID_FUNC_ANS_KFSJJZHCX			2127

#define TDX_ID_FUNC_REQ_KFSJJLSWTCX			2128	// 基金历史委托查询 2128
#define TDX_ID_FUNC_ANS_KFSJJLSWTCX			2129

#define TDX_ID_FUNC_REQ_KFSJJDSDESGSZ		2130	// 定时定额申购设置 2130
#define TDX_ID_FUNC_ANS_KFSJJDSDESGSZ		2131 

#define TDX_ID_FUNC_REQ_KFSJJDSDESGQX		2132	// 定时定额申购取消 2132
#define TDX_ID_FUNC_ANS_KFSJJDSDESGQX		2133 

#define TDX_ID_FUNC_REQ_KFSJJCXDQDESGPZ		2134	// 查询定期定额申购品种 2134
#define TDX_ID_FUNC_ANS_KFSJJCXDQDESGPZ		2135 

#define TDX_ID_FUNC_REQ_KFSJJDRWTCX			2136	// 开放式基金当日委托查询 2136
#define TDX_ID_FUNC_ANS_KFSJJDRWTCX			2137
	
#define TDX_ID_FUNC_REQ_KFSJJFHCX			2138	// 基金分红查询 2138
#define TDX_ID_FUNC_ANS_KFSJJFHCX			2139

#define TDX_ID_FUNC_REQ_LOFJJFHCX			2140	// LOF基金分红查询 2140
#define TDX_ID_FUNC_ANS_LOFJJFHCX			2141

#define TDX_ID_FUNC_REQ_LOFJJFH				2142	// LOF基金分红设置 2142
#define TDX_ID_FUNC_ANS_LOFJJFH				2143

#define TDX_ID_FUNC_REQ_KFSJJFXXXCX			2144	// 开放式基金基金风险信息查询 2144
#define TDX_ID_FUNC_ANS_KFSJJFXXXCX			2145

#define TDX_ID_FUNC_REQ_KFSJJZZKH			2146	// 基金转帐开户 2146
#define TDX_ID_FUNC_ANS_KFSJJZZKH			2147

#define TDX_ID_FUNC_REQ_KFSJJJYKH			2148	// 基金交易开户 2148
#define TDX_ID_FUNC_ANS_KFSJJJYKH			2149

#define TDX_ID_FUNC_REQ_KFSJJDRCJCX			2150	// 基金当日成交查询 2150
#define TDX_ID_FUNC_ANS_KFSJJDRCJCX			2151

#define TDX_ID_FUNC_REQ_KFSJJLSCJCX			2152	// 基金历史成交查询 2152
#define TDX_ID_FUNC_ANS_KFSJJLSCJCX			2153

#define TDX_ID_FUNC_REQ_KFSJJJZCX			2154	// 基金净值查询 2154
#define TDX_ID_FUNC_ANS_KFSJJJZCX			2155

#define TDX_ID_FUNC_REQ_KFSJJXYCXKT			2156	// 基金协议查询开通 2156
#define TDX_ID_FUNC_ANS_KFSJJXYCXKT			2157

#define TDX_ID_FUNC_REQ_KFSJJFHMXCX			2158	// 基金分红明细查询 2158
#define TDX_ID_FUNC_ANS_KFSJJFHMXCX			2159

#define TDX_ID_FUNC_REQ_DQDESZCX			2160	// 定期定额申购设置查询 2160
#define TDX_ID_FUNC_ANS_DQDESZCX			2161

#define TDX_ID_FUNC_REQ_KFSJJFJYWTCX		2162	// 开放式基金非交易委托查询 2162
#define TDX_ID_FUNC_ANS_KFSJJFJYWTCX		2163

#define TDX_ID_FUNC_REQ_KFSJJFJYDRWTCX		2164	// 开放式基金非交易当日委托查询 2164
#define TDX_ID_FUNC_ANS_KFSJJFJYDRWTCX		2165

#define TDX_ID_FUNC_REQ_KFSJJFXKCSDMCX		2166	// 开放式基金风险可承受代码查询 2166
#define TDX_ID_FUNC_ANS_KFSJJFXKCSDMCX		2167

#define TDX_ID_FUNC_REQ_KFSJJFLCX			2168	// 开放式基金费率查询 2168
#define TDX_ID_FUNC_ANS_KFSJJFLCX			2169

#define TDX_ID_FUNC_REQ_KFSJJDQDESHSZ		2170	// 开放式基金定期定额赎回设置 2170
#define TDX_ID_FUNC_ANS_KFSJJDQDESHSZ		2171

#define TDX_ID_FUNC_REQ_KFSJJDQDESHQX		2172	// 开放式基金定期定额赎回取消 2172
#define TDX_ID_FUNC_ANS_KFSJJDQDESHQX		2173

#define TDX_ID_FUNC_REQ_KFSJJDQDESHCX		2174	// 开放式基金定期定额赎回查询 2174
#define TDX_ID_FUNC_ANS_KFSJJDQDESHCX		2175

#define TDX_ID_FUNC_REQ_KFSJJDQDESHPZ		2176	// 开放式基金定期定额赎回品种 2176
#define TDX_ID_FUNC_ANS_KFSJJDQDESHPZ		2177

#define TDX_ID_FUNC_REQ_KFSJJDMXGXXCX		2178	// 开放式基金代码相关信息查询 2178
#define TDX_ID_FUNC_ANS_KFSJJDMXGXXCX		2179

#define TDX_ID_FUNC_REQ_KFSJJGSXGXXCX		2180	// 开放式基金公司相关信息查询 2180
#define TDX_ID_FUNC_ANS_KFSJJGSXGXXCX		2181

#define TDX_ID_FUNC_REQ_KFSJJDZDCX			2182	// 开放式基金对账单查询 2182
#define TDX_ID_FUNC_ANS_KFSJJDZDCX			2183

#define TDX_ID_FUNC_REQ_KFSJJJGDCX			2184	// 开放式基金交割单查询 2184
#define TDX_ID_FUNC_ANS_KFSJJJGDCX			2185

// 理财产品
#define	TDX_ID_FUNC_REQ_LCCPFECX			2200	// 理财产品份额查询 2200
#define	TDX_ID_FUNC_ANS_LCCPFECX			2201

#define	TDX_ID_FUNC_REQ_LCCPWTCX			2202	// 理财产品委托查询 2202
#define	TDX_ID_FUNC_ANS_LCCPWTCX			2203

#define	TDX_ID_FUNC_REQ_LCCPCJCX			2204	// 理财产品成交查询 2204
#define	TDX_ID_FUNC_ANS_LCCPCJCX			2205

#define	TDX_ID_FUNC_REQ_LCCPDRWTCX			2206	// 理财产品当日委托查询 2206
#define	TDX_ID_FUNC_ANS_LCCPDRWTCX			2207

#define	TDX_ID_FUNC_REQ_LCCPDMCX			2208	// 理财产品代码查询 2208
#define	TDX_ID_FUNC_ANS_LCCPDMCX			2209

#define	TDX_ID_FUNC_REQ_LCCPZHCX			2210	// 理财产品帐号查询 2210
#define	TDX_ID_FUNC_ANS_LCCPZHCX			2211

#define	TDX_ID_FUNC_REQ_LCCPDQDESGCX		2212	// 理财产品定期定额申购查询 2212
#define	TDX_ID_FUNC_ANS_LCCPDQDESGCX		2213

#define	TDX_ID_FUNC_REQ_LCCPDQDESGPZ		2214	// 理财产品定期定额申购品种 2214
#define	TDX_ID_FUNC_ANS_LCCPDQDESGPZ		2215

#define	TDX_ID_FUNC_REQ_LCCPZZJHLBCX		2216	// 理财产品增值计划列表查询 2216
#define	TDX_ID_FUNC_ANS_LCCPZZJHLBCX		2217

#define	TDX_ID_FUNC_REQ_LCCPZZJHXXCX		2218	// 理财产品增值计划信息查询 2218
#define	TDX_ID_FUNC_ANS_LCCPZZJHXXCX		2219

#define	TDX_ID_FUNC_REQ_LCCPZZJHJESZ		2220	// 理财产品增值计划金额设置 2220
#define	TDX_ID_FUNC_ANS_LCCPZZJHJESZ		2221

#define	TDX_ID_FUNC_REQ_LCCPZZJHZTSZ		2222	// 理财产品增值计划状态设置 2222
#define	TDX_ID_FUNC_ANS_LCCPZZJHZTSZ		2223

#define	TDX_ID_FUNC_REQ_LCCPZZJHJCXY		2224	// 理财产品增值计划解除协议 2224
#define	TDX_ID_FUNC_ANS_LCCPZZJHJCXY		2225

#define	TDX_ID_FUNC_REQ_LCCPZZJHFECX		2226	// 理财产品增值计划份额查询 2226
#define	TDX_ID_FUNC_ANS_LCCPZZJHFECX		2227

#define	TDX_ID_FUNC_REQ_LCCPZZJHCDCX		2228	// 理财产品增值计划撤单查询 2228
#define	TDX_ID_FUNC_ANS_LCCPZZJHCDCX		2229

#define	TDX_ID_FUNC_REQ_LCCPZZJHXXXG		2230	// 理财产品增值计划信息修改 2230
#define	TDX_ID_FUNC_ANS_LCCPZZJHXXXG		2231

#define	TDX_ID_FUNC_REQ_LCCPZZJHFESH		2232	// 理财产品增值计划份额赎回 2232
#define	TDX_ID_FUNC_ANS_LCCPZZJHFESH		2233

#define	TDX_ID_FUNC_REQ_LCCPZZJHWTCD		2234	// 理财产品增值计划委托撤单 2234
#define	TDX_ID_FUNC_ANS_LCCPZZJHWTCD		2235

#define	TDX_ID_FUNC_REQ_LCCPZZJHYYQKCZ		2236	// 理财产品增值计划预约取款操作 2236
#define	TDX_ID_FUNC_ANS_LCCPZZJHYYQKCZ		2237

#define	TDX_ID_FUNC_REQ_LCCPZZJHYYQKCX		2238	// 理财产品增值计划预约取款查询 2238
#define	TDX_ID_FUNC_ANS_LCCPZZJHYYQKCX		2239

#define	TDX_ID_FUNC_REQ_LCCPZZJHLSSYCX		2240	// 理财产品增值计划历史收益查询 2240
#define	TDX_ID_FUNC_ANS_LCCPZZJHLSSYCX		2241

#define	TDX_ID_FUNC_REQ_DQLCCPSHXXCX		2242	// 短期理财产品赎回信息查询 2242
#define	TDX_ID_FUNC_ANS_DQLCCPSHXXCX		2243

#define	TDX_ID_FUNC_REQ_LCCPZRDMCX			2244	// 理财产品转让代码查询 2244
#define	TDX_ID_FUNC_ANS_LCCPZRDMCX			2245

#define	TDX_ID_FUNC_REQ_LCCPZRHQCX			2246	// 理财产品转让行情查询 2246
#define	TDX_ID_FUNC_ANS_LCCPZRHQCX			2247

#define	TDX_ID_FUNC_REQ_LCCPZRCDCX			2248	// 理财产品转让撤单查询 2248
#define	TDX_ID_FUNC_ANS_LCCPZRCDCX			2249

#define	TDX_ID_FUNC_REQ_LCCPZRWTCX			2250	// 理财产品转让委托查询 2250
#define	TDX_ID_FUNC_ANS_LCCPZRWTCX			2251

#define	TDX_ID_FUNC_REQ_LCCPZRCJCX			2252	// 理财产品转让成交查询 2252
#define	TDX_ID_FUNC_ANS_LCCPZRCJCX			2253

#define TDX_ID_FUNC_REQ_LCCPQYJYCX			2254	// 理财产品签约解约查询 2254
#define TDX_ID_FUNC_ANS_LCCPQYJYCX			2255

#define	TDX_ID_FUNC_REQ_YHLCCPDMCX			2256	// 银行理财产品代码查询 2256
#define	TDX_ID_FUNC_ANS_YHLCCPDMCX			2257

#define	TDX_ID_FUNC_REQ_YHLCCPFECX			2258	// 银行理财产品份额查询 2258
#define	TDX_ID_FUNC_ANS_YHLCCPFECX			2259

#define	TDX_ID_FUNC_REQ_YHLCCPWTCX			2260	// 银行理财产品委托查询 2260
#define	TDX_ID_FUNC_ANS_YHLCCPWTCX			2261

#define	TDX_ID_FUNC_REQ_YHLCCPZHCX			2262	// 银行理财产品帐号查询 2262
#define	TDX_ID_FUNC_ANS_YHLCCPZHCX			2263

#define	TDX_ID_FUNC_REQ_YHLCCPCJCX			2264	// 银行理财产品成交查询 2264
#define	TDX_ID_FUNC_ANS_YHLCCPCJCX			2265

#define	TDX_ID_FUNC_REQ_OTCFECX				2266	// OTC份额查询 2266
#define	TDX_ID_FUNC_ANS_OTCFECX				2267

#define	TDX_ID_FUNC_REQ_OTCRSSCX			2268	// OTC认申赎查询 2268
#define	TDX_ID_FUNC_ANS_OTCRSSCX			2269

#define	TDX_ID_FUNC_REQ_OTCYXSBCX			2270	// OTC意向申报查询 2270
#define	TDX_ID_FUNC_ANS_OTCYXSBCX			2271

#define	TDX_ID_FUNC_REQ_OTCCJSBCX			2272	// OTC成交申报查询 2272
#define	TDX_ID_FUNC_ANS_OTCCJSBCX			2273

#define	TDX_ID_FUNC_REQ_OTCCPHYCX			2274	// OTC产品合约查询 2274
#define	TDX_ID_FUNC_ANS_OTCCPHYCX			2275

#define	TDX_ID_FUNC_REQ_OTCBJXXCX			2276	// OTC报价信息查询 2276
#define	TDX_ID_FUNC_ANS_OTCBJXXCX			2277

#define	TDX_ID_FUNC_REQ_OTCHQXXCX			2278	// OTC行情信息查询 2278
#define	TDX_ID_FUNC_ANS_OTCHQXXCX			2279

#define	TDX_ID_FUNC_REQ_OTCDZHTLBCX			2280	// OTC电子合同列表查询 2280
#define	TDX_ID_FUNC_ANS_OTCDZHTLBCX			2281

#define	TDX_ID_FUNC_REQ_OTCDZHTCX			2282	// OTC电子合同查询 2282
#define	TDX_ID_FUNC_ANS_OTCDZHTCX			2283

#define	TDX_ID_FUNC_REQ_XTCPDMCX			2300	// 信托产品代码查询 2300
#define	TDX_ID_FUNC_ANS_XTCPDMCX			2301	

#define	TDX_ID_FUNC_REQ_XTCPFECX			2302	// 信托产品份额查询 2302
#define	TDX_ID_FUNC_ANS_XTCPFECX			2303	

#define	TDX_ID_FUNC_REQ_XTCPZHCX			2304	// 信托产品帐号查询 2304
#define	TDX_ID_FUNC_ANS_XTCPZHCX			2305
	
#define	TDX_ID_FUNC_REQ_XTCPWTCX			2306	// 信托产品委托查询 2306
#define	TDX_ID_FUNC_ANS_XTCPWTCX			2307

#define	TDX_ID_FUNC_REQ_XTCPCJCX			2308	// 信托产品成交查询 2308
#define	TDX_ID_FUNC_ANS_XTCPCJCX			2309
	
#define	TDX_ID_FUNC_REQ_XTCPLSWTCX			2310	// 信托产品历史委托查询 2310
#define	TDX_ID_FUNC_ANS_XTCPLSWTCX			2311	

// 基金直销
#define	TDX_ID_FUNC_REQ_JJZXRG				2500	// 基金直销认购 2500
#define	TDX_ID_FUNC_ANS_JJZXRG				2501	

#define	TDX_ID_FUNC_REQ_JJZXSG				2502	// 基金直销申购 2502
#define	TDX_ID_FUNC_ANS_JJZXSG				2503

#define	TDX_ID_FUNC_REQ_JJZXSH				2504	// 基金直销赎回 2504
#define	TDX_ID_FUNC_ANS_JJZXSH				2505	 

#define	TDX_ID_FUNC_REQ_JJZXFH				2506	// 基金直销分红 2506
#define	TDX_ID_FUNC_ANS_JJZXFH				2507

#define	TDX_ID_FUNC_REQ_JJZXZH				2508	// 基金直销转换 2508
#define	TDX_ID_FUNC_ANS_JJZXZH				2509

#define	TDX_ID_FUNC_REQ_JJZXZTG				2510	// 基金直销转托管 2510
#define	TDX_ID_FUNC_ANS_JJZXZTG				2511

#define	TDX_ID_FUNC_REQ_JJZXCD				2512	// 基金直销撤单 2512
#define	TDX_ID_FUNC_ANS_JJZXCD				2513

#define	TDX_ID_FUNC_REQ_JJZXFLCX			2514	// 基金直销费率查询 2514
#define	TDX_ID_FUNC_ANS_JJZXFLCX			2515

#define	TDX_ID_FUNC_REQ_JJZXYHZF			2516	// 基金直销银行支付 2516
#define	TDX_ID_FUNC_ANS_JJZXYHZF			2517

#define	TDX_ID_FUNC_REQ_JJZXXSRDMCX			2518	// 基金直销销售人代码查询 2518
#define	TDX_ID_FUNC_ANS_JJZXXSRDMCX			2519

#define	TDX_ID_FUNC_REQ_JJZXXXJC			2520	// 基金直销信息检查 2520
#define	TDX_ID_FUNC_ANS_JJZXXXJC			2521

// 场内基金
#define	TDX_ID_FUNC_REQ_JYSCNJJDMCX			2850	// 交易所场内基金代码查询 2850
#define	TDX_ID_FUNC_ANS_JYSCNJJDMCX			2851

#define	TDX_ID_FUNC_REQ_JYSCNJJCFGCX		2852	// 交易所场内基金成分股查询 2852
#define	TDX_ID_FUNC_ANS_JYSCNJJCFGCX		2853

// ETF
#define TDX_ID_FUNC_REQ_ETFSHKJSGPTCX		2950	// ETF上海跨境申购配套查询 2950
#define TDX_ID_FUNC_ANS_ETFSHKJSGPTCX		2951

#define TDX_ID_FUNC_REQ_ETFSZKJSGPTCX		2952	// ETF深圳跨境申购配套查询 2952
#define TDX_ID_FUNC_ANS_ETFSZKJSGPTCX		2953

#define TDX_ID_FUNC_REQ_ETFSHKJSHPTCX		2954	// ETF上海跨境赎回配套查询 2954
#define TDX_ID_FUNC_ANS_ETFSHKJSHPTCX		2955

#define TDX_ID_FUNC_REQ_ETFSZKJSHPTCX		2956	// ETF深圳跨境赎回配套查询 2956
#define TDX_ID_FUNC_ANS_ETFSZKJSHPTCX		2957

#define TDX_ID_FUNC_REQ_ETFSHKJWTCDCX		2958	// ETF上海跨境委托撤单查询 2958
#define TDX_ID_FUNC_ANS_ETFSHKJWTCDCX		2959

#define TDX_ID_FUNC_REQ_ETFSZKJWTCDCX		2960	// ETF深圳跨境委托撤单查询 2960
#define TDX_ID_FUNC_ANS_ETFSZKJWTCDCX		2961

#define TDX_ID_FUNC_REQ_ETFSHKJDRWTCX		2962	// ETF上海跨境当日委托查询 2962
#define TDX_ID_FUNC_ANS_ETFSHKJDRWTCX		2963

#define TDX_ID_FUNC_REQ_ETFSZKJDRWTCX		2964	// ETF深圳跨境当日委托查询 2964
#define TDX_ID_FUNC_ANS_ETFSZKJDRWTCX		2965

#define TDX_ID_FUNC_REQ_ETFSHKJDRCJCX		2966	// ETF上海跨境当日成交查询 2966
#define TDX_ID_FUNC_ANS_ETFSHKJDRCJCX		2967

#define TDX_ID_FUNC_REQ_ETFSZKJDRCJCX		2968	// ETF深圳跨境当日成交查询 2968
#define TDX_ID_FUNC_ANS_ETFSZKJDRCJCX		2969

#define TDX_ID_FUNC_REQ_ETFSHKJLSWTCX		2970	// ETF上海跨境历史委托查询 2970
#define TDX_ID_FUNC_ANS_ETFSHKJLSWTCX		2971

#define TDX_ID_FUNC_REQ_ETFSZKJLSWTCX		2972	// ETF深圳跨境历史委托查询 2972
#define TDX_ID_FUNC_ANS_ETFSZKJLSWTCX		2973

#define TDX_ID_FUNC_REQ_ETFSHKJLSCJCX		2974	// ETF上海跨境历史成交查询 2974
#define TDX_ID_FUNC_ANS_ETFSHKJLSCJCX		2975

#define TDX_ID_FUNC_REQ_ETFSZKJLSCJCX		2976	// ETF深圳跨境历史成交查询 2976
#define TDX_ID_FUNC_ANS_ETFSZKJLSCJCX		2977

#define TDX_ID_FUNC_REQ_ETFWXXJRGPTCX		2980	// ETF网下现金认购配套查询 2980
#define TDX_ID_FUNC_ANS_ETFWXXJRGPTCX		2981

#define TDX_ID_FUNC_REQ_ETFWXGFRGPTCX		2982	// ETF网下股份认购配套查询 2982
#define TDX_ID_FUNC_ANS_ETFWXGFRGPTCX		2983

#define TDX_ID_FUNC_REQ_ETFWXXJRGCDCX		2984	// ETF网下现金认购撤单查询 2984
#define TDX_ID_FUNC_ANS_ETFWXXJRGCDCX		2985

#define TDX_ID_FUNC_REQ_ETFWXGFRGCDCX		2986	// ETF网下股份认购撤单查询 2986
#define TDX_ID_FUNC_ANS_ETFWXGFRGCDCX		2987

#define TDX_ID_FUNC_REQ_ETFWXXJRGXXCX		2988	// ETF网下现金认购信息查询 2988
#define TDX_ID_FUNC_ANS_ETFWXXJRGXXCX		2989

#define TDX_ID_FUNC_REQ_ETFWXGFRGXXCX		2990	// ETF网下股份认购信息查询 2990
#define TDX_ID_FUNC_ANS_ETFWXGFRGXXCX		2991

#define TDX_ID_FUNC_REQ_ETFWXXJRGLSCX		2992	// ETF网下现金认购流水查询 2992
#define TDX_ID_FUNC_ANS_ETFWXXJRGLSCX		2993

#define TDX_ID_FUNC_REQ_ETFWXGFRGLSCX		2994	// ETF网下股份认购流水查询 2994
#define TDX_ID_FUNC_ANS_ETFWXGFRGLSCX		2995

#define TDX_ID_FUNC_REQ_ETFMM				3000	// ETF买卖 3000
#define TDX_ID_FUNC_ANS_ETFMM				3001

#define TDX_ID_FUNC_REQ_ETFXXCX				3002	// ETF信息查询 3002
#define TDX_ID_FUNC_ANS_ETFXXCX				3003

#define TDX_ID_FUNC_REQ_ETFRGCX				3004	// ETF认购查询 3004
#define TDX_ID_FUNC_ANS_ETFRGCX				3005

#define TDX_ID_FUNC_REQ_ETFRGCD				3006	// ETF认购撤单 3006
#define TDX_ID_FUNC_ANS_ETFRGCD				3007

#define TDX_ID_FUNC_REQ_ETFPCH				3008	// ETF取批次号 3008
#define TDX_ID_FUNC_ANS_ETFPCH				3009

#define TDX_ID_FUNC_REQ_ETFGPLMM			3010	// ETF股票篮买卖 3010
#define TDX_ID_FUNC_ANS_ETFGPLMM			3011

#define TDX_ID_FUNC_REQ_ETFGPLCX			3012	// ETF股票篮查询 3012
#define TDX_ID_FUNC_ANS_ETFGPLCX			3013

#define TDX_ID_FUNC_REQ_ETFYGCX				3014	// ETF上证50拥股查询 3014
#define TDX_ID_FUNC_ANS_ETFYGCX				3015

#define TDX_ID_FUNC_REQ_ETFWTCX				3016	// ETF委托查询 3016
#define TDX_ID_FUNC_ANS_ETFWTCX				3017

#define TDX_ID_FUNC_REQ_ETFCJCX				3018	// ETF成交查询 3018
#define TDX_ID_FUNC_ANS_ETFCJCX				3019
                                        	
#define TDX_ID_FUNC_REQ_ETFCLCX				3020	// ETF策略查询 3020
#define TDX_ID_FUNC_ANS_ETFCLCX				3021    
                                        	
#define TDX_ID_FUNC_REQ_ETFZSDMCX			3022	// ETF指数代码查询 3022
#define TDX_ID_FUNC_ANS_ETFZSDMCX			3023
                                        	
#define TDX_ID_FUNC_REQ_ETFQR				3024	// ETF(委托)确认 3024
#define TDX_ID_FUNC_ANS_ETFQR				3025
                                        	
#define TDX_ID_FUNC_REQ_ETFWTCXMX			3026	// ETF委托查询明细 3026
#define TDX_ID_FUNC_ANS_ETFWTCXMX			3027

#define TDX_ID_FUNC_REQ_ETFRGCDCX			3028	// ETF认购撤单查询 3028
#define TDX_ID_FUNC_ANS_ETFRGCDCX			3029

#define TDX_ID_FUNC_REQ_ETFZSCFCX			3030	// ETF指数成分查询 3030
#define TDX_ID_FUNC_ANS_ETFZSCFCX			3031

#define TDX_ID_FUNC_REQ_ETFGFCX				3032	// ETF股份查询 3032
#define TDX_ID_FUNC_ANS_ETFGFCX				3033

#define TDX_ID_FUNC_REQ_ETFKSGCFGCX			3034	// ETF可申购成分股查询 3034
#define TDX_ID_FUNC_ANS_ETFKSGCFGCX			3035

#define TDX_ID_FUNC_REQ_ETFGPLCD			3036	// ETF股票篮撤单 3036
#define TDX_ID_FUNC_ANS_ETFGPLCD			3037

#define TDX_ID_FUNC_REQ_ETFGPLCDCX			3038	// ETF股票篮撤单查询 3038
#define TDX_ID_FUNC_ANS_ETFGPLCDCX			3039

#define TDX_ID_FUNC_REQ_ETFKSCDPCX			3040	// ETF跨市场对盘查询 3040
#define TDX_ID_FUNC_ANS_ETFKSCDPCX			3041

// 组合通业务
#define TDX_ID_FUNC_REQ_ZHTPCH				3050	// 组合通批次号 3050
#define TDX_ID_FUNC_ANS_ZHTPCH				3051
                                        	
#define TDX_ID_FUNC_REQ_ZHTGPLMM			3052	// 组合通股票篮买卖 3052
#define TDX_ID_FUNC_ANS_ZHTGPLMM			3053
                                        	
#define TDX_ID_FUNC_REQ_ZHTGPLCX			3054	// 组合通股票篮查询 3054
#define TDX_ID_FUNC_ANS_ZHTGPLCX			3055
                                        	
#define TDX_ID_FUNC_REQ_ZHTYGCX				3056	// 组合通拥股查询 3056
#define TDX_ID_FUNC_ANS_ZHTYGCX				3057
                                        	
#define TDX_ID_FUNC_REQ_ZHTWTCX				3058	// 组合通委托查询 3058
#define TDX_ID_FUNC_ANS_ZHTWTCX				3059
                                        	
#define TDX_ID_FUNC_REQ_ZHTCJCX				3060	// 组合通成交查询 3060
#define TDX_ID_FUNC_ANS_ZHTCJCX				3061
                                        	
#define TDX_ID_FUNC_REQ_ZHTCLCX				3062	// 组合通策略查询 3062
#define TDX_ID_FUNC_ANS_ZHTCLCX				3063    
                                        	
#define TDX_ID_FUNC_REQ_ZHTZSDMCX			3064	// 组合通指数代码查询 3064
#define TDX_ID_FUNC_ANS_ZHTZSDMCX			3065
                                        	
#define TDX_ID_FUNC_REQ_ZHTQR				3066	// 组合通确认 3066
#define TDX_ID_FUNC_ANS_ZHTQR				3067
                                        	
#define TDX_ID_FUNC_REQ_ZHTLSCX				3068	// 组合通历史查询 3068
#define TDX_ID_FUNC_ANS_ZHTLSCX				3069
                                        	
#define TDX_ID_FUNC_REQ_ZHTLSCXMX			3070	// 组合通历史查询明细 3070
#define TDX_ID_FUNC_ANS_ZHTLSCXMX			3071
                                        	
#define TDX_ID_FUNC_REQ_ZHTWTCXMX			3072	// 组合通委托查询明细 3072
#define TDX_ID_FUNC_ANS_ZHTWTCXMX			3073
                                        	
#define TDX_ID_FUNC_REQ_ZHTCJCXMX			3074	// 组合通成交查询明细 3074
#define TDX_ID_FUNC_ANS_ZHTCJCXMX			3075

#define TDX_ID_FUNC_REQ_ZHTZSCFCX			3076	// 组合通指数成分查询 3076
#define TDX_ID_FUNC_ANS_ZHTZSCFCX			3077

// 套利交易
#define TDX_ID_FUNC_REQ_TL_HQHHH			3100	// (套利)获取会话号 3100
#define TDX_ID_FUNC_ANS_TL_HQHHH			3101

#define TDX_ID_FUNC_REQ_TL_ZHDMCX			3102	// (套利)组合代码查询 3102
#define TDX_ID_FUNC_ANS_TL_ZHDMCX			3103

#define TDX_ID_FUNC_REQ_TL_ZHCFCX			3104	// (套利)组合成分查询 3104
#define TDX_ID_FUNC_ANS_TL_ZHCFCX			3105

#define TDX_ID_FUNC_REQ_TL_ZHDMCZ			3106	// (套利)组合代码操作 3106
#define TDX_ID_FUNC_ANS_TL_ZHDMCZ			3107

#define TDX_ID_FUNC_REQ_TL_ZHCFCZ			3108	// (套利)组合成分操作 3108
#define TDX_ID_FUNC_ANS_TL_ZHCFCZ			3109

#define TDX_ID_FUNC_REQ_TL_CLDMCX			3110	// (套利)策略代码查询 3110
#define TDX_ID_FUNC_ANS_TL_CLDMCX			3111

#define TDX_ID_FUNC_REQ_TL_CLCFCX			3112	// (套利)策略成分查询 3112
#define TDX_ID_FUNC_ANS_TL_CLCFCX			3113

#define TDX_ID_FUNC_REQ_TL_CLDMCZ			3114	// (套利)策略代码操作 3114
#define TDX_ID_FUNC_ANS_TL_CLDMCZ			3115

#define TDX_ID_FUNC_REQ_TL_CLCFCZ			3116	// (套利)策略成分操作 3116
#define TDX_ID_FUNC_ANS_TL_CLCFCZ			3117

#define TDX_ID_FUNC_REQ_TL_PHCZ				3118	// (套利)批号操作 3118
#define TDX_ID_FUNC_ANS_TL_PHCZ				3119

#define TDX_ID_FUNC_REQ_TL_PHCX				3120	// (套利)批号查询 3120
#define TDX_ID_FUNC_ANS_TL_PHCX				3121

#define TDX_ID_FUNC_REQ_TL_PHWTLB			3122	// (套利)批号委托列表 3122
#define TDX_ID_FUNC_ANS_TL_PHWTLB			3123

#define TDX_ID_FUNC_REQ_TL_PHWTZX			3124	// (套利)批号委托执行 3124
#define TDX_ID_FUNC_ANS_TL_PHWTZX			3125

#define TDX_ID_FUNC_REQ_TL_PHWTCX			3126	// (套利)批号委托查询 3126
#define TDX_ID_FUNC_ANS_TL_PHWTCX			3127

#define TDX_ID_FUNC_REQ_TL_PHCCCX			3128	// (套利)批号持仓查询 3128
#define TDX_ID_FUNC_ANS_TL_PHCCCX			3129

// 算法交易
#define TDX_ID_FUNC_REQ_SFJY_DDCZ			3190	// (算法交易)订单操作 3190
#define TDX_ID_FUNC_ANS_SFJY_DDCZ			3191

#define TDX_ID_FUNC_REQ_SFJY_DDLBCX			3192	// (算法交易)订单列表查询 3192
#define TDX_ID_FUNC_ANS_SFJY_DDLBCX			3193

#define TDX_ID_FUNC_REQ_SFJY_DDJGCX			3194	// (算法交易)订单结果查询 3194
#define TDX_ID_FUNC_ANS_SFJY_DDJGCX			3195

// 信用交易
#define TDX_ID_FUNC_REQ_XYZCCX				3200	// 信用资产查询 3200
#define TDX_ID_FUNC_ANS_XYZCCX				3201

#define TDX_ID_FUNC_REQ_XYGFCX				3202	// 信用股份查询 3202
#define TDX_ID_FUNC_ANS_XYGFCX				3203

#define TDX_ID_FUNC_REQ_XYHYCX				3204	// 默认未平仓合约查询查询 3204
#define TDX_ID_FUNC_ANS_XYHYCX				3205

#define TDX_ID_FUNC_REQ_XYHYYPCCX			3206	// 已平仓合约查询 3206
#define TDX_ID_FUNC_ANS_XYHYYPCCX			3207

#define TDX_ID_FUNC_REQ_XYSXCX				3208	// 信用上限查询 3208
#define TDX_ID_FUNC_ANS_XYSXCX				3209

#define TDX_ID_FUNC_REQ_XYFZCX				3210	// 信用负债查询 3210
#define TDX_ID_FUNC_ANS_XYFZCX				3211

#define TDX_ID_FUNC_REQ_FXYZCCX				3212	// 非信用资产查询 3212
#define TDX_ID_FUNC_ANS_FXYZCCX				3213

#define	TDX_ID_FUNC_REQ_XYHYDRCX			3214	// 信用合约当日查询 3214
#define	TDX_ID_FUNC_ANS_XYHYDRCX			3215

#define	TDX_ID_FUNC_REQ_XYJYBDZQCX			3216	// 信用交易标的证券查询 3216
#define	TDX_ID_FUNC_ANS_XYJYBDZQCX			3217

#define	TDX_ID_FUNC_REQ_XYJYZHXXCX			3218	// 信用交易综合信息查询 3218
#define	TDX_ID_FUNC_ANS_XYJYZHXXCX			3219

#define	TDX_ID_FUNC_REQ_XYJYDBPZQCX			3220	// 信用交易担保品证券查询 3220
#define	TDX_ID_FUNC_ANS_XYJYDBPZQCX			3221

#define	TDX_ID_FUNC_REQ_XYJYRZMRZQCX		3222	// 信用交易融资买入证券查询 3222
#define	TDX_ID_FUNC_ANS_XYJYRZMRZQCX		3223

#define	TDX_ID_FUNC_REQ_XYJYRQMCZQCX		3224	// 信用交易融券卖出证券查询 3224
#define	TDX_ID_FUNC_ANS_XYJYRQMCZQCX		3225

#define	TDX_ID_FUNC_REQ_XYJYDMTSXXCX		3226	// 信用交易代码提示信息查询 3226
#define	TDX_ID_FUNC_ANS_XYJYDMTSXXCX		3227

#define	TDX_ID_FUNC_REQ_XYJYHYHZCX			3228	// 信用交易合约汇总查询 3228
#define	TDX_ID_FUNC_ANS_XYJYHYHZCX			3229

#define	TDX_ID_FUNC_REQ_XYJYRZMRPTCX		3230	// 信用交易融资买入配套查询 3230
#define	TDX_ID_FUNC_ANS_XYJYRZMRPTCX		3231

#define	TDX_ID_FUNC_REQ_XYJYRQMCPTCX		3232	// 信用交易融券卖出配套查询 3232
#define	TDX_ID_FUNC_ANS_XYJYRQMCPTCX		3233

#define	TDX_ID_FUNC_REQ_XYJYMQHQPTCX		3234	// 信用交易买券还券配套查询 3234
#define	TDX_ID_FUNC_ANS_XYJYMQHQPTCX		3235

#define	TDX_ID_FUNC_REQ_XYJYYQHZPTCX		3236	// 信用交易余券划转配套查询 3236
#define	TDX_ID_FUNC_ANS_XYJYYQHZPTCX		3237

#define	TDX_ID_FUNC_REQ_XYJYXQHQPTCX		3238	// 信用交易现券还券配套查询 3238
#define	TDX_ID_FUNC_ANS_XYJYXQHQPTCX		3239

#define	TDX_ID_FUNC_REQ_XYJYDBPHZPTCX		3240	// 信用交易担保品划转配套查询 3240
#define	TDX_ID_FUNC_ANS_XYJYDBPHZPTCX		3241

#define	TDX_ID_FUNC_REQ_XYJYDBPHRPTCX		3242	// 信用交易担保品划入配套查询 3242
#define	TDX_ID_FUNC_ANS_XYJYDBPHRPTCX		3243

#define	TDX_ID_FUNC_REQ_XYJYDBPHCPTCX		3244	// 信用交易担保品划出配套查询 3244
#define	TDX_ID_FUNC_ANS_XYJYDBPHCPTCX		3245

#define	TDX_ID_FUNC_REQ_XYJYXJHKPTCX		3246	// 信用交易现金还款配套查询 3246
#define	TDX_ID_FUNC_ANS_XYJYXJHKPTCX		3247

#define	TDX_ID_FUNC_REQ_XYJYMQHKPTCX		3248	// 信用交易卖券还款配套查询 3248
#define	TDX_ID_FUNC_ANS_XYJYMQHKPTCX		3249

#define	TDX_ID_FUNC_REQ_XYJYRZPCMCPTCX		3250	// 信用交易融资平仓卖出配套查询 3250
#define	TDX_ID_FUNC_ANS_XYJYRZPCMCPTCX		3251

#define	TDX_ID_FUNC_REQ_XYJYRQPCMRPTCX		3252	// 信用交易融券平仓买入配套查询 3252
#define	TDX_ID_FUNC_ANS_XYJYRQPCMRPTCX		3253

#define	TDX_ID_FUNC_REQ_XYJYLLXXCX			3254	// 信用交易利率信息查询 3254
#define	TDX_ID_FUNC_ANS_XYJYLLXXCX			3255

#define	TDX_ID_FUNC_REQ_XYJYRQYECX			3256	// 信用交易融券余额查询 3256
#define	TDX_ID_FUNC_ANS_XYJYRQYECX			3257

#define	TDX_ID_FUNC_REQ_XYJYRZYECX			3258	// 信用交易融资余额查询 3258
#define	TDX_ID_FUNC_ANS_XYJYRZYECX			3259

#define	TDX_ID_FUNC_REQ_XYJYFJYHZCX			3260	// 信用交易非交易化转查询 3260
#define	TDX_ID_FUNC_ANS_XYJYFJYHZCX			3261

#define	TDX_ID_FUNC_REQ_XYJYLXFYCX			3262	// 信用交易利息费用查询 3262
#define	TDX_ID_FUNC_ANS_XYJYLXFYCX			3263

#define	TDX_ID_FUNC_REQ_XYJYZJFZCX			3264	// 信用交易资金负债查询 3264
#define	TDX_ID_FUNC_ANS_XYJYZJFZCX			3265

#define	TDX_ID_FUNC_REQ_XYJYZQFZCX			3266	// 信用交易证券负债查询 3266
#define	TDX_ID_FUNC_ANS_XYJYZQFZCX			3267

#define	TDX_ID_FUNC_REQ_XYJYKHQYCX			3268	// 信用交易客户签约查询 3268
#define	TDX_ID_FUNC_ANS_XYJYKHQYCX			3269

#define	TDX_ID_FUNC_REQ_XYJYKHXYCL			3270	// 信用交易客户协议处理 3270
#define	TDX_ID_FUNC_ANS_XYJYKHXYCL			3271

#define	TDX_ID_FUNC_REQ_XYJYCHMXCX			3272	// 信用交易偿还明细查询 3272
#define	TDX_ID_FUNC_ANS_XYJYCHMXCX			3273

#define	TDX_ID_FUNC_REQ_XYJYRZHYCX			3274	// 信用交易融资合约查询 3274
#define	TDX_ID_FUNC_ANS_XYJYRZHYCX			3275

#define	TDX_ID_FUNC_REQ_XYJYRQHYCX			3276	// 信用交易融券合约查询 3276
#define	TDX_ID_FUNC_ANS_XYJYRQHYCX			3277

#define	TDX_ID_FUNC_REQ_XYJYDBPHZCX			3278	// 信用交易担保品划转查询 3278
#define	TDX_ID_FUNC_ANS_XYJYDBPHZCX			3279

#define	TDX_ID_FUNC_REQ_XYJYMRDBPPTCX		3280	// 信用交易买入担保品配套查询 3280
#define	TDX_ID_FUNC_ANS_XYJYMRDBPPTCX		3281

#define	TDX_ID_FUNC_REQ_XYJYMCDBPPTCX		3282	// 信用交易卖出担保品配套查询 3282
#define	TDX_ID_FUNC_ANS_XYJYMCDBPPTCX		3283

#define	TDX_ID_FUNC_REQ_XYJYGHRQFYPTCX		3284	// 信用交易归还融券费用配套查询 3284
#define	TDX_ID_FUNC_ANS_XYJYGHRQFYPTCX		3285

#define	TDX_ID_FUNC_REQ_XYJYFZLSCX			3286	// 信用交易负债流水查询 3286
#define	TDX_ID_FUNC_ANS_XYJYFZLSCX			3287

#define	TDX_ID_FUNC_REQ_XYJYXJTDHQPTCX		3288	// 信用交易现金替代还券配套查询 3288
#define	TDX_ID_FUNC_ANS_XYJYXJTDHQPTCX		3289

#define	TDX_ID_FUNC_REQ_XYJYWCDBBLCX		3290	// 信用交易维持担保比率查询 3290
#define	TDX_ID_FUNC_ANS_XYJYWCDBBLCX		3291

#define	TDX_ID_FUNC_REQ_XYJYEDGL			3292	// 信用交易额度管理 3292
#define	TDX_ID_FUNC_ANS_XYJYEDGL			3293

#define	TDX_ID_FUNC_REQ_XYJYEDBGCX			3294	// 信用交易额度变更查询 3294
#define	TDX_ID_FUNC_ANS_XYJYEDBGCX			3295

#define	TDX_ID_FUNC_REQ_XYJYPCRZHYCX		3296	// 信用交易平仓融资合约查询 3296
#define	TDX_ID_FUNC_ANS_XYJYPCRZHYCX		3297

#define	TDX_ID_FUNC_REQ_XYJYPCRQHYCX		3298	// 信用交易平仓融券合约查询 3298
#define	TDX_ID_FUNC_ANS_XYJYPCRQHYCX		3299

// 转融通
#define	TDX_ID_FUNC_REQ_ZRTYWCZ				3400	// 转融通业务操作 3400
#define	TDX_ID_FUNC_ANS_ZRTYWCZ				3401

#define	TDX_ID_FUNC_REQ_ZRTBDZQCX			3402	// 转融通标的证券查询 3402
#define	TDX_ID_FUNC_ANS_ZRTBDZQCX			3403

#define	TDX_ID_FUNC_REQ_ZRTZJXXCX			3404	// 转融通资金信息查询 3404
#define	TDX_ID_FUNC_ANS_ZRTZJXXCX			3405

#define	TDX_ID_FUNC_REQ_ZRTGFXXCX			3406	// 转融通股份信息查询 3406
#define	TDX_ID_FUNC_ANS_ZRTGFXXCX			3407

#define	TDX_ID_FUNC_REQ_ZRTRZMRPTCX			3408	// 转融通融资买入配套查询 3408
#define	TDX_ID_FUNC_ANS_ZRTRZMRPTCX			3409

#define	TDX_ID_FUNC_REQ_ZRTRQMCPTCX			3410	// 转融通融券卖出配套查询 3410
#define	TDX_ID_FUNC_ANS_ZRTRQMCPTCX			3411

#define	TDX_ID_FUNC_REQ_ZRTZJJRSQPTCX		3412	// 转融通资金借入申请配套查询 3412
#define	TDX_ID_FUNC_ANS_ZRTZJJRSQPTCX		3413

#define	TDX_ID_FUNC_REQ_ZRTGFJRSQPTCX		3414	// 转融通股份借入申请配套查询 3414
#define	TDX_ID_FUNC_ANS_ZRTGFJRSQPTCX		3415

#define	TDX_ID_FUNC_REQ_ZRTJRZQSQPTCX		3416	// 转融通借入展期申请配套查询 3416
#define	TDX_ID_FUNC_ANS_ZRTJRZQSQPTCX		3417

#define	TDX_ID_FUNC_REQ_ZRTTQGHSQPTCX		3418	// 转融通提前归还申请配套查询 3418
#define	TDX_ID_FUNC_ANS_ZRTTQGHSQPTCX		3419

#define	TDX_ID_FUNC_REQ_ZRTJRYWCDCX			3420	// 转融通借入业务撤单查询 3420
#define	TDX_ID_FUNC_ANS_ZRTJRYWCDCX			3421

#define	TDX_ID_FUNC_REQ_ZRTJRYWDRCX			3422	// 转融通借入业务当日查询 3422
#define	TDX_ID_FUNC_ANS_ZRTJRYWDRCX			3423

#define	TDX_ID_FUNC_REQ_ZRTJRYWLSCX			3424	// 转融通借入业务历史查询 3424
#define	TDX_ID_FUNC_ANS_ZRTJRYWLSCX			3425

#define	TDX_ID_FUNC_REQ_ZRTDRJRHYCX			3426	// 转融通当日借入合约查询 3426
#define	TDX_ID_FUNC_ANS_ZRTDRJRHYCX			3427

#define	TDX_ID_FUNC_REQ_ZRTWLJRHYCX			3428	// 转融通未了借入合约查询 3428
#define	TDX_ID_FUNC_ANS_ZRTWLJRHYCX			3429

#define	TDX_ID_FUNC_REQ_ZRTYLJRHYCX			3430	// 转融通已了借入合约查询 3430
#define	TDX_ID_FUNC_ANS_ZRTYLJRHYCX			3431

#define	TDX_ID_FUNC_REQ_ZRTZJCJSQPTCX		3432	// 转融通资金出借申请配套查询 3432
#define	TDX_ID_FUNC_ANS_ZRTZJCJSQPTCX		3433

#define	TDX_ID_FUNC_REQ_ZRTGFCJSQPTCX		3434	// 转融通股份出借申请配套查询 3434
#define	TDX_ID_FUNC_ANS_ZRTGFCJSQPTCX		3435

#define	TDX_ID_FUNC_REQ_ZRTZJCJQDPTCX		3436	// 转融通资金出借确定配套查询 3436
#define	TDX_ID_FUNC_ANS_ZRTZJCJQDPTCX		3437

#define	TDX_ID_FUNC_REQ_ZRTGFCJQDPTCX		3438	// 转融通股份出借确定配套查询 3438
#define	TDX_ID_FUNC_ANS_ZRTGFCJQDPTCX		3439

#define	TDX_ID_FUNC_REQ_ZRTCJYWCDCX			3440	// 转融通出借业务撤单查询 3440
#define	TDX_ID_FUNC_ANS_ZRTCJYWCDCX			3441

#define	TDX_ID_FUNC_REQ_ZRTCJYWDRCX			3442	// 转融通出借业务当日查询 3442
#define	TDX_ID_FUNC_ANS_ZRTCJYWDRCX			3443

#define	TDX_ID_FUNC_REQ_ZRTCJYWLSCX			3444	// 转融通出借业务历史查询 3444
#define	TDX_ID_FUNC_ANS_ZRTCJYWLSCX			3445

#define	TDX_ID_FUNC_REQ_ZRTCJTQSHPTCX		3446	// 转融通出借提前索还配套查询 3446
#define	TDX_ID_FUNC_ANS_ZRTCJTQSHPTCX		3447

#define	TDX_ID_FUNC_REQ_ZRTCJTYZQPTCX		3448	// 转融通出借同意展期配套查询 3448
#define	TDX_ID_FUNC_ANS_ZRTCJTYZQPTCX		3449

#define	TDX_ID_FUNC_REQ_ZRTQXFLCX			3450	// 转融通期限费率查询 3450
#define	TDX_ID_FUNC_ANS_ZRTQXFLCX			3451

#define	TDX_ID_FUNC_REQ_ZRTCJHYCX			3452	// 转融通出借合约查询 3452
#define	TDX_ID_FUNC_ANS_ZRTCJHYCX			3453

#define	TDX_ID_FUNC_REQ_ZRTCJLSHYCX			3454	// 转融通出借历史合约查询 3454
#define	TDX_ID_FUNC_ANS_ZRTCJLSHYCX			3455

#define	TDX_ID_FUNC_REQ_ZRTMCHKPTCX			3456	// 转融通卖出还款配套查询 3456
#define	TDX_ID_FUNC_ANS_ZRTMCHKPTCX			3457

#define	TDX_ID_FUNC_REQ_ZRTMRHQPTCX			3458	// 转融通买入还券配套查询 3458
#define	TDX_ID_FUNC_ANS_ZRTMRHQPTCX			3459

#define	TDX_ID_FUNC_REQ_ZRTXJHKPTCX			3460	// 转融通现金还款配套查询 3460
#define	TDX_ID_FUNC_ANS_ZRTXJHKPTCX			3461

#define	TDX_ID_FUNC_REQ_ZRTXQHQPTCX			3462	// 转融通现券还券配套查询 3462
#define	TDX_ID_FUNC_ANS_ZRTXQHQPTCX			3463

#define	TDX_ID_FUNC_REQ_ZRTKCJXXCX			3464	// 转融通可出借信息查询 3464
#define	TDX_ID_FUNC_ANS_ZRTKCJXXCX			3465

#define	TDX_ID_FUNC_REQ_ZRTJRTYSHPTCX		3466	// 转融通借入同意索还配套查询 3466
#define	TDX_ID_FUNC_ANS_ZRTJRTYSHPTCX		3467

#define	TDX_ID_FUNC_REQ_ZRTCJZHXXCX			3468	// 转融通出借账户信息查询 3468
#define	TDX_ID_FUNC_ANS_ZRTCJZHXXCX			3469

// 其他
#define TDX_ID_FUNC_REQ_XLYZT_BEGIN			4100

#define TDX_ID_FUNC_REQ_XLYZT_KTQXZDDL		4100	// 新利 开通/取消自动代理配售、申购、配股 4100
#define TDX_ID_FUNC_ANS_XLYZT_KTQXZDDL		4101

#define TDX_ID_FUNC_REQ_XLYZT_KTHZPS		4102	// 新利 开通合作配售 4102
#define TDX_ID_FUNC_ANS_XLYZT_KTHZPS		4103

#define TDX_ID_FUNC_REQ_XLYZT_QXHZPS		4104	// 新利 取消合作配售 4104
#define TDX_ID_FUNC_ANS_XLYZT_QXHZPS		4105

#define TDX_ID_FUNC_REQ_XLYZT_KTHZHG		4106	// 新利 开通合作回购 4106
#define TDX_ID_FUNC_ANS_XLYZT_KTHZHG		4107	

#define TDX_ID_FUNC_REQ_XLYZT_QXHZHG		4108	// 新利 取消合作回购 4108
#define TDX_ID_FUNC_ANS_XLYZT_QXHZHG		4109

#define TDX_ID_FUNC_REQ_XLYZT_KTHZSG		4110	// 新利 开通合作申购 4110
#define TDX_ID_FUNC_ANS_XLYZT_KTHZSG		4111

#define TDX_ID_FUNC_REQ_XLYZT_QXHZSG		4112	// 新利 取消合作申购 4112
#define TDX_ID_FUNC_ANS_XLYZT_QXHZSG		4113

#define TDX_ID_FUNC_REQ_XLYZT_DLGNCX		4114	// 查询代理开通信息 4114
#define TDX_ID_FUNC_ANS_XLYZT_DLGNCX		4115		

#define TDX_ID_FUNC_REQ_XLYZT_END			4200


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 安全部分扩展功能

#define TDX_ID_FUNC_REQ_CA_AQGNSQ			4200	// 安全功能申请 4200
#define TDX_ID_FUNC_ANS_CA_AQGNSQ			4201

#define TDX_ID_FUNC_REQ_CA_AQGNCX			4202	// 安全功能撤销 4202
#define TDX_ID_FUNC_ANS_CA_AQGNCX			4203

#define TDX_ID_FUNC_REQ_CA_MMBHWTJY			4204	// 密码保护问题校验 4204
#define TDX_ID_FUNC_ANS_CA_MMBHWTJY			4205

// 广发证券矩阵卡
#define TDX_ID_FUNC_REQ_CA_GETTZZB			4206	// 获取挑战坐标 4206
#define TDX_ID_FUNC_ANS_CA_GETTZZB			4207

#define TDX_ID_FUNC_REQ_CA_ZXJZK			4208	// 注销矩阵卡 4208
#define TDX_ID_FUNC_ANS_CA_ZXJZK			4209

// 预留问题
#define TDX_ID_FUNC_REQ_CA_YLWT				4210	// 预留问题 4210	
#define TDX_ID_FUNC_ANS_CA_YLWT				4211

// 多因子认证
#define TDX_ID_FUNC_REQ_CA_CERRAREQ			4212	// 证书申请 4212
#define TDX_ID_FUNC_ANS_CA_CERRAREQ			4213

#define TDX_ID_FUNC_REQ_CA_CERAUDIT			4214	// 证书审核 4214
#define TDX_ID_FUNC_ANS_CA_CERAUDIT			4215

#define TDX_ID_FUNC_REQ_CA_CERDOWNLOAD		4216	// 证书下载 4216
#define TDX_ID_FUNC_ANS_CA_CERDOWNLOAD		4217

#define TDX_ID_FUNC_REQ_CA_CERDLCONFIRM		4218	// 证书下载确认 4218
#define TDX_ID_FUNC_ANS_CA_CERDLCONFIRM		4219

// 机器特征码相关
#define TDX_ID_FUNC_REQ_CA_ADDYHXX			4220	// 添加用户信息 4220
#define TDX_ID_FUNC_ANS_CA_ADDYHXX			4221

#define TDX_ID_FUNC_REQ_CA_XGYHXX			4222	// 修改用户信息 4222
#define TDX_ID_FUNC_ANS_CA_XGYHXX			4223

#define TDX_ID_FUNC_REQ_CA_CXYHXX			4224	// 查询用户信息 4224
#define TDX_ID_FUNC_ANS_CA_CXYHXX			4225	

#define TDX_ID_FUNC_REQ_CA_GETYZM			4226	// 获取手机验证码 4226
#define TDX_ID_FUNC_ANS_CA_GETYZM			4227

#define TDX_ID_FUNC_REQ_CA_YZMJY			4228	// 验证码校验 4228
#define TDX_ID_FUNC_ANS_CA_YZMJY			4229	

// 其他集中认证校验
#define	TDX_ID_FUNC_REQ_OTHERCA_BASEFUN		4230	// 其他安全认证校验 4230
#define	TDX_ID_FUNC_ANS_OTHERCA_BASEFUN		4231

// 查询密码保护问题
#define TDX_ID_FUNC_REQ_CA_MMBHWTCX			4232	// 密码保护问题查询 4232
#define TDX_ID_FUNC_ANS_CA_MMBHWTCX			4233	 

// 修改密码保护问题
#define TDX_ID_FUNC_REQ_CA_XGMMBHWT			4234	// 修改密码保护问题 4234
#define TDX_ID_FUNC_ANS_CA_XGMMBHWT			4235

//	修改预留问题
#define TDX_ID_FUNC_REQ_CA_XGYLWT			4236	// 修改预留问题 4236
#define TDX_ID_FUNC_ANS_CA_XGYLWT			4237

// 密码保护问题列表查询
#define TDX_ID_FUNC_REQ_CA_PWDPROTQUEQU		4238	// 密码保护问题列表查询 4238
#define TDX_ID_FUNC_ANS_CA_PWDPROTQUEQU		4239

// 申请密码保护问题
#define TDX_ID_FUNC_REQ_CA_APPLYPWDQA		4240	// 申请密码保护问题 4240
#define TDX_ID_FUNC_ANS_CA_APPLYPWDQA		4241

// 申请机器特征码绑定
#define TDX_ID_FUNC_REQ_CA_BINDMACHINE		4242	// 申请机器特征码绑定 4242
#define TDX_ID_FUNC_ANS_CA_BINDMACHINE		4243

// 查询绑定信息
#define TDX_ID_FUNC_REQ_CA_QUEBINDINFO		4244	// 查询绑定信息 4244
#define TDX_ID_FUNC_ANS_CA_QUEBINDINFO		4245

// 取消绑定信息
#define TDX_ID_FUNC_REQ_CA_CANCELBIND		4246	// 取消绑定信息 4246
#define TDX_ID_FUNC_ANS_CA_CANCELBIND		4247

// 安全申请状态查询
#define TDX_ID_FUNC_REQ_CA_SAFEMODQUE		4248	// 安全申请状态查询 4248
#define TDX_ID_FUNC_ANS_CA_SAFEMODQUE		4249

// 核销用户安全级别
#define TDX_ID_FUNC_REQ_CA_ABUSERLV			4250	// 核销用户安全级别 4250
#define TDX_ID_FUNC_ANS_CA_ABUSERLV			4251

// 用户离线
#define TDX_ID_FUNC_REQ_CA_USERLOGOUT		4252	// 用户离线 4252
#define TDX_ID_FUNC_ANS_CA_USERLOGOUT		4253

// 用户在线心跳
#define TDX_ID_FUNC_REQ_CA_USERALIVE		4254	// 用户在线心跳 4254
#define TDX_ID_FUNC_ANS_CA_USERALIVE		4255

// 取消用户级别
#define TDX_ID_FUNC_REQ_CA_CANCELLV			4256	// 取消用户级别 4256
#define TDX_ID_FUNC_ANS_CA_CANCELLV			4257

// 获取产品名称
#define TDX_ID_FUNC_REQ_CA_GETPROINFO		4258	// 获取产品名称 4258
#define TDX_ID_FUNC_ANS_CA_GETPROINFO		4259

// 光大证券安全相关功能
// 客户证书绑定
#define TDX_ID_FUNC_REQ_CA_BINDCERT_GD		4260	// 客户证书绑定 4260
#define TDX_ID_FUNC_ANS_CA_BINDCERT_GD		4261

// 客户预留信息
#define TDX_ID_FUNC_REQ_CA_RESER_GD			4262	// 用户在线心跳 4262
#define TDX_ID_FUNC_ANS_CA_RESER_GD			4263


// 注册用户相关功能
#define TDX_ID_FUNC_REQ_CA_REGUSER			4280	// 注册用户
#define TDX_ID_FUNC_ANS_CA_REGUSER			4281

#define TDX_ID_FUNC_REQ_CA_ALTERREGPWD		4282	// 修改注册密码
#define TDX_ID_FUNC_ANS_CA_ALTERREGPWD		4283

// 单点登陆相关
#define TDX_ID_FUNC_REQ_CA_SSO				4284	// 单点登陆令牌操作
#define TDX_ID_FUNC_ANS_CA_SSO				4285
#define TDX_ID_FUNC_REQ_CA_SSOYHXX			4286	// 单点登陆根据令牌取用户信息
#define TDX_ID_FUNC_ANS_CA_SSOYHXX			4287
// 新版本证书
#define TDX_ID_FUNC_REQ_CA_CERDEL			4288	// 证书吊销
#define TDX_ID_FUNC_ANS_CA_CERDEL			4289
// OTP同步
#define TDX_ID_FUNC_REQ_CA_OTPSYN			4290	//	OTP同步
#define TDX_ID_FUNC_ANS_CA_OTPSYN			4291
// 检查数据一致性
#define TDX_ID_FUNC_REQ_CA_CHECKRECORD		4292	//	检查数据一致性
#define TDX_ID_FUNC_ANS_CA_CHECKRECORD		4293	//	
#define TDX_ID_FUNC_REQ_CA_PAAUTH			4294	// 修改注册密码
#define TDX_ID_FUNC_ANS_CA_PAAUTH			4295
#define TDX_ID_FUNC_REQ_CA_ACCREPORT		4296	// 投顾诊断报告
#define TDX_ID_FUNC_ANS_CA_ACCREPORT		4297
// OTP豁免
#define TDX_ID_FUNC_REQ_CA_OTPTEMP			4298	// OTP豁免
#define TDX_ID_FUNC_ANS_CA_OTPTEMP			4299
// 获取核新手机验证码
#define	TDX_ID_FUNC_REQ_OTHERCA_GETYZM		4300	// 获取核新手机验证码
#define	TDX_ID_FUNC_ANS_OTHERCA_GETYZM		4301

// 自选股上传下载
#define	TDX_ID_FUNC_REQ_OPMYSTOCK			4302	// 自选股上传下载
#define	TDX_ID_FUNC_ANS_OPMYSTOCK			4303

// 找回密码
#define	TDX_ID_FUNC_REQ_FETCHPWD			4304	// 找回用户密码
#define	TDX_ID_FUNC_ANS_FETCHPWD			4305

// 找回用户名
#define	TDX_ID_FUNC_REQ_FETCHUSERACCOUNT	4306	// 找回用户帐号
#define	TDX_ID_FUNC_ANS_FETCHUSERACCOUNT	4307

// 积分查询
#define	TDX_ID_FUNC_REQ_QUERYSCORE			4308	// 积分查询
#define	TDX_ID_FUNC_ANS_QUERYSCORE			4309

// 注册用户信息查询
#define	TDX_ID_FUNC_REQ_QUERYREGUDATA		4310	// 注册用户信息查询
#define	TDX_ID_FUNC_ANS_QUERYREGUDATA		4311

// 获取激活码
#define TDX_ID_FUNC_REQ_GETACTIVECODE		4312	// 获取激活码
#define TDX_ID_FUNC_ANS_GETACTIVECODE		4313


// 新版本安全功能( 4500 - 4600)

#define TDX_ID_FUNC_REQ_QRYSCFUNC			4500	// 安全功能查询 ( 用户开启的安全级别, OPT序列号, 证书有效期)
#define TDX_ID_FUNC_ANS_QRYSCFUNC			4501

#define TDX_ID_FUNC_REQ_SWITCHSCFUNC		4502	// 开启/关闭安全功能
#define TDX_ID_FUNC_ANS_SWITCHSCFUNC		4503

#define TDX_ID_FUNC_REQ_UNIAUTH				4504	// 统一认证
#define TDX_ID_FUNC_ANS_UNIAUTH				4505

#define TDX_ID_FUNC_REQ_REQAPWD				4506	// 申请认证口令
#define TDX_ID_FUNC_ANS_REQAPWD				4507

#define TDX_ID_FUNC_REQ_MODAPWD				4508	// 修改认证口令
#define TDX_ID_FUNC_ANS_MODAPWD				4509

#define TDX_ID_FUNC_REQ_RESETAPWD			4510	// 重置认证口令
#define TDX_ID_FUNC_ANS_RESETAPWD			4511

#define TDX_ID_FUNC_REQ_SYNOTP				4512	// 同步OTP
#define TDX_ID_FUNC_ANS_SYNOTP				4513

#define TDX_ID_FUNC_REQ_GETCSIGNKEY			4514	// 获取证书签名码
#define TDX_ID_FUNC_ANS_GETCSIGNKEY			4515

#define TDX_ID_FUNC_REQ_UPDCERT				4516	// 更新证书
#define TDX_ID_FUNC_ANS_UPDCERT				4517

#define TDX_ID_FUNC_REQ_GETCCODE			4518	// 获取手机动态码
#define TDX_ID_FUNC_ANS_GETCCODE			4519

#define TDX_ID_FUNC_REQ_PERMITMACHINE		4520	// 授权计算机 ( CPU, MAC列表, HDD列表, BIOS) ( 允许选择认证, 使用手机动态码或者密码保护问题,或者安全方式, 必须选择一种)
#define TDX_ID_FUNC_ANS_PERMITMACHINE		4521

#define TDX_ID_FUNC_REQ_FREEMACHINE			4522	// 解除计算机授权( 允许选择认证, 使用手机动态码或者密码保护问题,或者安全方式, 必须选择一种)
#define TDX_ID_FUNC_ANS_FREEMACHINE			4523

#define TDX_ID_FUNC_REQ_QRYPERMITION		4524	// 查询授权
#define TDX_ID_FUNC_ANS_QRYPERMITION		4525

#define TDX_ID_FUNC_REQ_UPDSELFINFO			4526	// 更新预留信息
#define TDX_ID_FUNC_ANS_UPDSELFINFO			4527

#define TDX_ID_FUNC_REQ_QRYUSERCOMMON		4528	// 查询用户常用信息( 上次登录IP, 上次登录MAC, 上次使用版本, 总登录次数, 预留信息)
#define TDX_ID_FUNC_ANS_QRYUSERCOMMON		4529

#define TDX_ID_FUNC_REQ_QRYUDATA			4530	// 用户资料查询 ( 手机号, 身份证号等)
#define TDX_ID_FUNC_ANS_QRYUDATA			4531

#define TDX_ID_FUNC_REQ_UPDUDATA			4532	// 更新用户资料
#define TDX_ID_FUNC_ANS_UPDUDATA			4533

#define TDX_ID_FUNC_REQ_QRYIMPOTOP			4534	// 关键操作查询
#define TDX_ID_FUNC_ANS_QRYIMPOTOP			4535

#define TDX_ID_FUNC_REQ_RCDIMPOTOP			4536	// 关键操作记录( 功能号, 功能名称, 操作说明)
#define TDX_ID_FUNC_ANS_RCDIMPOTOP			4537

#define TDX_ID_FUNC_REQ_QRYAUTHHIS			4538	// 认证历史查询( 认证时间, 安全方式, 认证结果, IP, MAC, 机器信息, 客户端版本)
#define TDX_ID_FUNC_ANS_QRYAUTHHIS			4539

#define TDX_ID_FUNC_REQ_REQQAPROT			4540	// 密码保护问题申请
#define TDX_ID_FUNC_ANS_REQQAPROT			4541

#define TDX_ID_FUNC_REQ_MODQAPROT			4542	// 密码保护问题修改
#define TDX_ID_FUNC_ANS_MODQAPROT			4543

#define TDX_ID_FUNC_REQ_AUTHQAPROT			4544	// 密码保护校验
#define TDX_ID_FUNC_ANS_AUTHQAPROT			4545

#define TDX_ID_FUNC_REQ_RESVPWD				4546	// 应急密码
#define TDX_ID_FUNC_ANS_RESVPWD				4547

#define TDX_ID_FUNC_REQ_CONSIS				4548	// 请求服务器签名信息
#define TDX_ID_FUNC_ANS_CONSIS				4549

// 新版本安全功能( 4500 - 4600)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// 模拟交易相关
#define TDX_ID_FUNC_REQ_SYLPM				5000	// 收益率排名 5000
#define TDX_ID_FUNC_ANS_SYLPM				5001

#define TDX_ID_FUNC_REQ_ZHRQ				5002	// 帐户融券 5002
#define TDX_ID_FUNC_ANS_ZHRQ				5003

#define TDX_ID_FUNC_REQ_RQCX				5004	// 融券查询 5004
#define TDX_ID_FUNC_ANS_RQCX				5005

#define	TDX_ID_FUNC_REQ_ZHHQZQ				5006	// 帐户还券展期 5006
#define	TDX_ID_FUNC_ANS_ZHHQZQ				5007

#define	TDX_ID_FUNC_REQ_TCMONITOR			5008	// 交易中心监控 5008
#define	TDX_ID_FUNC_ANS_TCMONITOR			5009

#define	TDX_ID_FUNC_REQ_TSROUTING			5010	// TS路由 5010
#define	TDX_ID_FUNC_ANS_TSROUTING			5011


//---------------------------------------------------------------------------
// Part.VI 帐号类型定义以及其他字典用枚举型标志定义
//---------------------------------------------------------------------------

// 账号类别
#define SZAG				0						// 深圳A股
#define SHAG				1						// 上海A股
#define SZBG				2						// 深圳B股
#define SHBG				3						// 上海B股
#define SZGZ				4						// 深圳国债
#define SHGZ				5						// 上海国债
#define DFGT				6						// 地方柜台
#define QHWT				7						// 期货委托
#define SHHY				8						// 深沪合一(资金帐号)
#define KHWT				9						// 客户号委托
//#define SHWT				10						// 客户号委托
#define SZCY				11						// 深圳创业
#define SBAG				12						// 三板A股
#define SBBG				13 						// 三板B股
#define SBGB				14						// 三板G股
#define KSJJ				15						// 开放式基金
#define SZHG				16						// 深证回购
#define SHHG				17						// 上海回购
#define ZBZH				18						// 主板帐户
#define SBZH				19						// 三板帐户
#define QHZH				20						// 期货帐号
#define ZZQH				21						// 郑州期货
#define SHQH				22						// 上海期货
#define DLQH				23						// 大连期货
#define KHKH				24						// 客户卡号
#define YHWT				25						// 招商银行方式登录	
#define ZJQH				26						// 中金期货
#define GGJYZH				27						// 港股交易帐号
#define ZCYH				28						// 注册用户(仅使用匿名帐号校验,不登录界面,仅再)
#define FWYH				29						// 服务用户(到后台进行服务帐号验证,校验不登录界面)
#define YHZH				30						// 银行账号
#define LMKH				31						// 联名卡号
#define NAME				32						// 昵称(到后台进行服务帐号验证,校验不登录界面)
#define SFZH				33						// 身份证(到后台进行服务帐号验证,校验不登录界面)
#define SJH					34						// 手机号(到后台进行服务帐号验证,校验不登录界面)
#define SVYH_NB				35						// 内部员工号(到后台进行服务帐号验证,校验不登录界面
#define TYYH				36						// 体验用户(所有操作到体验柜台中完成)


// 买卖标志(TDX_ID_MMBZ)
#define TDX_FLAG_MMBZ_MR		0					// 买入
#define TDX_FLAG_MMBZ_MC		1					// 卖出
#define TDX_FLAG_MMBZ_CD		2					// 撤单(仅查询返回)
#define TDX_FLAG_MMBZ_MRCD		3					// 撤买(仅查询返回)
#define TDX_FLAG_MMBZ_MCCD		4					// 撤卖(仅查询返回)
#define TDX_FLAG_MMBZ_KZZZG		5					// 可转债转股(仅查询入参)
#define TDX_FLAG_MMBZ_KZZHS		6					// 可转债回售(仅查询入参)
#define TDX_FLAG_MMBZ_DQDESG	5					// 定期定额申购(废弃)
#define TDX_FLAG_MMBZ_RQ		6					// 融券(废弃)
#define TDX_FLAG_MMBZ_HQ		7					// 还券(废弃)
#define TDX_FLAG_MMBZ_ZQ		8					// 展期(废弃)
#define TDX_FLAG_MMBZ_YMR		9					// 预买
#define TDX_FLAG_MMBZ_YMC		10					// 预卖
#define TDX_FLAG_MMBZ_XGYWT		11					// 修改预委托
#define TDX_FLAG_MMBZ_LOFHB		12					// LOF合并
#define TDX_FLAG_MMBZ_LOFFC		13					// LOF分拆
#define TDX_FLAG_MMBZ_LOFZH		14					// LOF转换
#define TDX_FLAG_MMBZ_MRDBP		15					// 买入担保品
#define TDX_FLAG_MMBZ_MCDBP		16					// 买出担保品
#define TDX_FLAG_MMBZ_YHK		17					// 预还款
#define TDX_FLAG_MMBZ_YHQ		18					// 预还券
#define TDX_FLAG_MMBZ_HGRZ		19					// 回购融资
#define TDX_FLAG_MMBZ_HGRQ		20					// 回购融券
#define TDX_FLAG_MMBZ_ZDSHMR	21					// 自动赎回买入
#define TDX_FLAG_MMBZ_XJTDHQ	22					// (融券)现金替代还券
#define TDX_FLAG_MMBZ_ZRTRZMR	23					// 转融通融资买入
#define TDX_FLAG_MMBZ_ZRTRQMC	24					// 转融通融券卖出
#define TDX_FLAG_MMBZ_ZHXYYXMR	25					// 综合协议意向买入
#define TDX_FLAG_MMBZ_ZHXYYXMC	26					// 综合协议意向卖出
#define TDX_FLAG_MMBZ_ZHXYDJMR	27					// 综合协议定价买入
#define TDX_FLAG_MMBZ_ZHXYDJMC	28					// 综合协议定价卖出
#define TDX_FLAG_MMBZ_ZHXYCJMR	29					// 综合协议成交买入
#define TDX_FLAG_MMBZ_ZHXYCJMC	30					// 综合协议成交卖出
#define TDX_FLAG_MMBZ_ZQZYCK	31					// 债券质押出库
#define TDX_FLAG_MMBZ_ZQZYRK	32					// 债券质押入库
#define TDX_FLAG_MMBZ_ZRTMCHK	33					// 转融通卖出还款
#define TDX_FLAG_MMBZ_ZRTMRHQ	34					// 转融通买入还券
#define TDX_FLAG_MMBZ_ZRTXJHK	35					// 转融通现金还款
#define TDX_FLAG_MMBZ_ZRTXQHQ	36					// 转融通现券还券
#define TDX_FLAG_MMBZ_GTZQYXMR	37					// 柜台债券意向买入
#define TDX_FLAG_MMBZ_GTZQYXMC	38					// 柜台债券意向卖出
#define TDX_FLAG_MMBZ_GTZQDEMR	39					// 柜台债券大额买入
#define TDX_FLAG_MMBZ_GTZQDEMC	40					// 柜台债券大额卖出
#define TDX_FLAG_MMBZ_GTZQXEMR	41					// 柜台债券小额买入
#define TDX_FLAG_MMBZ_GTZQXEMC	42					// 柜台债券小额卖出
#define TDX_FLAG_MMBZ_GTZQCJMR	43					// 柜台债券成交买入
#define TDX_FLAG_MMBZ_GTZQCJMC	44					// 柜台债券成交卖出
#define TDX_FLAG_MMBZ_JYSHBJJSG	45					// 交易所货币基金申购
#define TDX_FLAG_MMBZ_JYSHBJJSH	46					// 交易所货币基金赎回
#define TDX_FLAG_MMBZ_RZXQWT	47					// 融资行权委托
#define TDX_FLAG_MMBZ_RZXQMCHK	48					// 融资行权卖出还款
#define TDX_FLAG_MMBZ_RZXQXJHK	49					// 融资行权现金还款
#define TDX_FLAG_MMBZ_NBGFHZ	50					// 内部股份划转
#define TDX_FLAG_MMBZ_QQZZXQ	51					// 期权自主行权
#define TDX_FLAG_MMBZ_TJQQSDS	52					// 提交期权所得税
#define TDX_FLAG_MMBZ_FQZQ		'A'					// [65]放弃中签(废弃,已采用单独功能)
#define TDX_FLAG_MMBZ_GHRQFY	'B'					// [66]归还融券费用
#define TDX_FLAG_MMBZ_SJMR		'C'					// [67]市价买入
#define TDX_FLAG_MMBZ_SJMC		'D'					// [68]市价卖出
#define TDX_FLAG_MMBZ_RZMR		'E'					// [69]融资买入
#define TDX_FLAG_MMBZ_RQMC		'F'					// [70]融券卖出
#define TDX_FLAG_MMBZ_MRHQ		'G'					// [71](融券)买券还券
#define TDX_FLAG_MMBZ_YQHZ		'H'					// [72]余券划转
#define TDX_FLAG_MMBZ_XQHQ		'I'					// [73](融券)现券还券
#define TDX_FLAG_MMBZ_DBPHZ		'J'					// [74]担保品划转
#define TDX_FLAG_MMBZ_HK		'K'					// [75](融资现金)还款
#define TDX_FLAG_MMBZ_XQHK		'L'					// [76](融资)现券还款[融资卖券还款]
#define TDX_FLAG_MMBZ_RZPCMC	'M'					// [77]融资平仓卖出
#define TDX_FLAG_MMBZ_RQPCMR	'N'					// [78]融券平仓买入
#define TDX_FLAG_MMBZ_LOFSG		'O'					// [79]LOF申购
#define TDX_FLAG_MMBZ_LOFSH		'P'					// [80]LOF赎回
#define TDX_FLAG_MMBZ_LOFRG		'Q'					// [81]LOF认购
#define TDX_FLAG_MMBZ_YXWTMR	'R'					// [82]意向委托买入
#define TDX_FLAG_MMBZ_YXWTMC	'S'					// [83]意向委托卖出
#define TDX_FLAG_MMBZ_DJWTMR	'T'					// [84]定价委托买入
#define TDX_FLAG_MMBZ_DJWTMC	'U'					// [85]定价委托卖出
#define TDX_FLAG_MMBZ_QZXQ		'V'					// [86]权证行权
#define TDX_FLAG_MMBZ_CJQRMR	'W'					// [87]成交确认买入
#define TDX_FLAG_MMBZ_CJQRMC	'X'					// [88]成交确认卖出
#define TDX_FLAG_MMBZ_YYSB		'Y'					// [89]要约申报
#define TDX_FLAG_MMBZ_YYJC		'Z'					// [90]要约解除

// ETF买卖标识(TDX_ID_ETFMMBS)
#define TDX_FLAG_ETF_MMBS_SG		0				// ETF申购
#define TDX_FLAG_ETF_MMBS_SH		1				// ETF赎回
#define TDX_FLAG_ETF_MMBS_GPRG		2				// ETF股份认购(包括网上/网下,接口根据配置区分)
#define TDX_FLAG_ETF_MMBS_XJRG		3				// ETF现金认购(包括网上/网下,接口根据配置区分)
#define TDX_FLAG_ETF_MMBS_WSGPRG	4				// ETF网上股份认购
#define TDX_FLAG_ETF_MMBS_WSXJRG	5				// ETF网上现金认购
#define TDX_FLAG_ETF_MMBS_WXGPRG	6				// ETF网下股份认购
#define TDX_FLAG_ETF_MMBS_WXXJRG	7				// ETF网下现金认购
#define TDX_FLAG_ETF_MMBS_SWSG		8				// ETF(跨市场)实物申购
#define TDX_FLAG_ETF_MMBS_SWSH		9				// ETF(跨市场)实物赎回
#define TDX_FLAG_ETF_MMBS_SWRG		10				// ETF(跨市场)实物认购
#define TDX_FLAG_ETF_MMBS_KJXJSG	11				// ETF跨境现金申购
#define TDX_FLAG_ETF_MMBS_KJXJSH	12				// ETF跨境现金赎回
#define TDX_FLAG_ETF_MMBS_KJXJRG	13				// ETF跨境现金认购

// 基金买卖标志(TDX_ID_KFSJJ_MMBZ)
// 查询通过TDX_ID_MMBZ返回(0-买 1-卖 2-撤或其他 3-撤买 4-撤卖)
#define TDX_FLAG_JJ_MMBZ_JJRG		0				// 基金认购
#define TDX_FLAG_JJ_MMBZ_JJSG		1				// 基金申购
#define TDX_FLAG_JJ_MMBZ_CYLC		1				// 参与理财
#define TDX_FLAG_JJ_MMBZ_JJSH		2				// 基金赎回
#define TDX_FLAG_JJ_MMBZ_LCTC		2				// 理财退出
#define TDX_FLAG_JJ_MMBZ_YYSG		3				// 预约申购
#define TDX_FLAG_JJ_MMBZ_YYSH		4				// 预约赎回
#define TDX_FLAG_JJ_MMBZ_DQSG		5				// 定期申购
#define TDX_FLAG_JJ_MMBZ_YYRG		6				// 预约认购
#define TDX_FLAG_JJ_MMBZ_JJZH		7				// 基金转换
#define TDX_FLAG_JJ_MMBZ_LCZRYXMR	8				// 理财转让意向买入
#define TDX_FLAG_JJ_MMBZ_LCZRYXMC	9				// 理财转让意向卖出
#define TDX_FLAG_JJ_MMBZ_LCZRDJMR	10				// 理财转让定价买入
#define TDX_FLAG_JJ_MMBZ_LCZRDJMC	11				// 理财转让定价卖出
#define TDX_FLAG_JJ_MMBZ_LCZRQDMR	12				// 理财转让确定买入
#define TDX_FLAG_JJ_MMBZ_LCZRQDMC	13				// 理财转让确定卖出
#define TDX_FLAG_JJ_MMBZ_LCCPSG		14				// 理财产品申购
#define TDX_FLAG_JJ_MMBZ_LCCPSH		15				// 理财产品赎回

#define TDX_FLAG_JJ_MMBZ_LCZRDEMR	31				// 理财转让大额成交买入
#define TDX_FLAG_JJ_MMBZ_LCZRDEMC	32				// 理财转让大额成交卖出
#define TDX_FLAG_JJ_MMBZ_LCZRXEMR	33				// 理财转让小额成交买入
#define TDX_FLAG_JJ_MMBZ_LCZRXEMC	34				// 理财转让小额成交卖出
#define TDX_FLAG_JJ_MMBZ_LCZRCJMR	35				// 理财转让意向成交买入
#define TDX_FLAG_JJ_MMBZ_LCZRCJMC	36				// 理财转让意向成交卖出


// 产品标志(TDX_ID_CPBZ)
#define TDX_FLAG_CPBZ_JJCP		((BYTE)0)			// 基金产品
#define TDX_FLAG_CPBZ_LCCP		((BYTE)1)			// 理财产品
#define TDX_FLAG_CPBZ_XJCP		((BYTE)2)			// 现金产品
#define TDX_FLAG_CPBZ_YHCP		((BYTE)3)			// 银行产品
#define TDX_FLAG_CPBZ_DXCP		((BYTE)4)			// 代销产品
#define TDX_FLAG_CPBZ_XTCP		((BYTE)5)			// 信托产品
#define TDX_FLAG_CPBZ_ALL		((BYTE)(-1))		// 全部(用于查询)

// 产品查询操作标志(TDX_ID_CZBZ)
// 对应的"产品标志(TDX_ID_CPBZ)"减1
#define TDX_FLAG_CPCX_CZBZ_LCCP	((BYTE)0)			// 理财产品
#define TDX_FLAG_CPCX_CZBZ_XJCP	((BYTE)1)			// 现金产品
#define TDX_FLAG_CPCX_CZBZ_YHCP	((BYTE)2)			// 银行产品
#define TDX_FLAG_CPCX_CZBZ_DXCP	((BYTE)3)			// 代销产品
#define TDX_FLAG_CPCX_CZBZ_ALL	((BYTE)(-1))		// 全部

// 分红标志(TDX_ID_KFSJJ_DIVIDENMETHOD,TDX_ID_FHBZ)
#define TDX_FLAG_FHBZ_HLZG		0					// 红利转股
#define TDX_FLAG_FHBZ_XJFH		1					// 现金分红
#define TDX_FLAG_FHBZ_LDXJZZZTZ	2					// 利得现金增值再投资
#define TDX_FLAG_FHBZ_ZZXJLDZTZ	3					// 增值现金利得再投资
#define TDX_FLAG_FHBZ_CANNOTSET	99					// 不能设置(用于客户端特殊控制)

// 基金收费方式(TDX_ID_SFFS)
#define TDX_FLAG_JJ_SFFS_QD		1					// 前端
#define TDX_FLAG_JJ_SFFS_HD		2					// 后端
#define TDX_FLAG_JJ_SFFS_CL		4					// C类

// 基金巨额赎回方式(TDX_ID_SHFS)
#define TDX_FLAG_JJ_JESHFS_QX	0					// 取消
#define TDX_FLAG_JJ_JESHFS_SY	1					// 顺延

// 委托类别(TDX_ID_WTFS)--国内股票
#define TDX_FLAG_WTLB_XJWT		0					// [限价委托]限价
#define TDX_FLAG_WTLB_DFZY		1					// [对方最优]对手方最优价格
#define TDX_FLAG_WTLB_BFZY		2					// [本方最有]本方最优价格
#define TDX_FLAG_WTLB_JCSC		3					// [即成剩撤]即时成交剩余撤销
#define TDX_FLAG_WTLB_WDSC		4					// [五档剩撤]最优五档即时成交剩余撤销
#define TDX_FLAG_WTLB_QEWT		5					// [全额委托]全额成交或撤销
#define TDX_FLAG_WTLB_WDSZ		6					// [五档剩转]最优五档即时成交剩余转限价

// 委托类别(TDX_ID_WTFS)--国内期货
#define TDX_FLAG_WTLB_QH_XJWT	0					// 限价委托
#define TDX_FLAG_WTLB_QH_SJWT	1					// 市价委托
#define TDX_FLAG_WTLB_QH_SJZS	2					// 市价止损
#define TDX_FLAG_WTLB_QH_SJZY	3					// 市价止盈
#define TDX_FLAG_WTLB_QH_XJZS	4					// 限价止损
#define TDX_FLAG_WTLB_QH_XJZY	5					// 限价止盈
#define TDX_FLAG_WTLB_QH_ZYJ	6					// 最优价

// 委托类别(TDX_ID_WTFS)--外盘交易
#define TDX_FLAG_WTLB_WP_LO		0					// 限价盘(Limit Order)
#define TDX_FLAG_WTLB_WP_AO		1					// 竞价盘(Auction Order)
#define TDX_FLAG_WTLB_WP_ALO	2					// 竞价限价盘(Auction Limit Order)
#define TDX_FLAG_WTLB_WP_ELO	3					// 增强限价盘(Enhanced Limit Order)
#define TDX_FLAG_WTLB_WP_SLO	4					// 特别限价盘(Special Limit Order)
#define TDX_FLAG_WTLB_WP_MO		5					// 市价盘(Market Order)
#define TDX_FLAG_WTLB_WP_SELO	6					// 超级增强限价盘(Super Enhanced Limit Order)
#define TDX_FLAG_WTLB_WP_SSLO	7					// 超级特别限价盘(Super Special Limit Order)
#define TDX_FLAG_WTLB_WP_LLO	8					// (?)限价盘(? Limit Order) -- 可根据时间段自动转换成 LO 或 AO

// 期货开平标志(TDX_ID_KPBZ)
#define TDX_FLAG_QH_KPBZ_KC		0					// 开仓
#define TDX_FLAG_QH_KPBZ_PC		1					// 平仓
#define TDX_FLAG_QH_KPBZ_PJ		2					// 平今
#define TDX_FLAG_QH_KPBZ_QP		3					// 强平

// 期货投保标志(TDX_ID_TBBZ)
#define TDX_FLAG_QH_TBBZ_TJ		0					// 投机
#define TDX_FLAG_QH_TBBZ_BZ		1					// 保值
#define TDX_FLAG_QH_TBBZ_TL		2					// 套利

// 成交属性(TDX_ID_CJSX)[可以按位叠加]
#define TDX_FLAG_CJSX_SDJY		(0x00000001)		// 锁定交易(不可撤单)

// 期货成交属性(TDX_ID_CJSX)
#define TDX_FLAG_QH_CJSX_DRYX	0					// 当日有效[GFD]
#define TDX_FLAG_QH_CJSX_QCHC	1					// 全成或撤[FOK]
#define TDX_FLAG_QH_CJSX_SYJC	2					// 剩余即撤[FAK]

// 外盘成交属性(TDX_ID_CJSX)[可以按位叠加]
#define TDX_FLAG_WP_CJSX_PF		(0x00000001)		// 部分执行(partial fill)
#define TDX_FLAG_WP_CJSX_PM		(0x00000002)		// 盘前交易(pre market)
#define TDX_FLAG_WP_CJSX_OL		(0x00000004)		// 零股交易(odd lot)
#define TDX_FLAG_WP_CJSX_SS		(0x00000008)		// 沽空交易(short sell)

// 期货组合类型(TDX_ID_ZHLX)
#define TDX_FLAG_QH_ZHLX_TL		0					// 套利
#define TDX_FLAG_QH_ZHLX_HH		1					// 互换

// 转账方向(TDX_ID_YZZZ_ZZFX)
#define TDX_FLAG_ZZFX_ZR		0					// 转入
#define TDX_FLAG_ZZFX_ZC		1					// 转出
#define TDX_FLAG_ZZFX_ALL		((BYTE)(-1))		// 全部(用于查询)

// 合作回购状态(TDX_ID_HZHGZT)
#define TDX_FLAG_HZHGZT_SQMR	0					// 申请买入
#define TDX_FLAG_HZHGZT_TQZZ	1					// 提前终止

// 登录输入参数(TDX_ID_XT_LOGINENTERPARAM)
#define TDX_FLAG_LEP_ZJZHDL		('1')				// 追加账号登录

// 登录返回参数(TDX_ID_XT_LOGINRETURNPARAM)
#define TDX_FLAG_LRP_DZJZH		('1')				// [49]多资金账号
#define TDX_FLAG_LRP_JYDCG		('2')				// [50]禁用多存管
#define TDX_FLAG_LRP_YSZMB		('3')				// [51]已设置密保
#define TDX_FLAG_LRP_JQWBD		('4')				// [52]机器未绑定
#define TDX_FLAG_LRP_YXSFJY		('5')				// [53]允许算法交易
#define TDX_FLAG_LRP_JYBJHG		('6')				// [54]禁用报价回购
#define TDX_FLAG_LRP_YXDZHJGJY	('7')				// [55]允许多账户机构交易
#define TDX_FLAG_LRP_YXDZHXGSG	('8')				// [56]允许多账户新股申购
#define TDX_FLAG_LRP_TSGXJYMM	('9')				// [57]提示更新交易密码
#define TDX_FLAG_LRP_YXZRTJR	('A')				// [65]允许转融通借入
#define TDX_FLAG_LRP_YXZRTCJ	('B')				// [66]允许转融通出借
#define TDX_FLAG_LRP_YXSYZXTC	('C')				// [67]允许使用专项头寸
#define TDX_FLAG_LRP_JZYDHG		('D')				// [68]禁止约定回购

#define TDX_FLAG_LRP_XGMMXYJY	('a')				// [97]修改密码需要校验
#define TDX_FLAG_LRP_ZQZYHXYJY	('b')				// [98]证券转银行需要校验
#define TDX_FLAG_LRP_BZHTCTS	('c')				// [99]B转H弹出提示

// 主账号标志(TDX_ID_ZZHBZ)
#define TDX_FLAG_ZZHBZ_ASSIST	((BYTE)0)			// 辅
#define TDX_FLAG_ZZHBZ_MAIN		((BYTE)1)			// 主
#define TDX_FLAG_ZZHBZ_OTHER	((BYTE)2)			// 其他
#define TDX_FLAG_ZZHBZ_NOFUND	((BYTE)97)			// 没有资金(不能内转)
#define TDX_FLAG_ZZHBZ_NOBANK	((BYTE)98)			// 没有银行代码
#define TDX_FLAG_ZZHBZ_CANNEL	((BYTE)99)			// 已注销

// 现货账户类型(TDX_ID_XHZHLX)
#define TDX_FLAG_XHZHLX_DEFAULT	((BYTE)0)			// 默认
#define TDX_FLAG_XHZHLX_NORMAL	((BYTE)1)			// 普通
#define TDX_FLAG_XHZHLX_FUTURES	((BYTE)2)			// 期货
#define TDX_FLAG_XHZHLX_CREDIT	((BYTE)3)			// 信用

// 组合类型(TDX_ID_ZHLX)
#define TDX_FLAG_ZHLX_DEFAULT	((BYTE)0)			// 默认
#define TDX_FLAG_ZHLX_CUSTOMER	((BYTE)1)			// 用户自定义
#define TDX_FLAG_ZHLX_BROKER	((BYTE)2)			// 券商自定义

// 批次号类型(TDX_ID_PCHLX)
#define TDX_FLAG_PCHLX_DEFAULT		((BYTE)0)		// 默认
#define TDX_FLAG_PCHLX_PHASE		((BYTE)1)		// 期现套利
#define TDX_FLAG_PCHLX_ALPHA		((BYTE)2)		// Alpha套利
#define TDX_FLAG_PCHLX_PORTFOLIO	((BYTE)3)		// 股票组合委托

// 权重方式(TDX_ID_QZFS)
#define TDX_FLAG_QZFS_DEFAULT	((BYTE)0)			// 默认
#define TDX_FLAG_QZFS_RATIO		((BYTE)1)			// 比例
#define TDX_FLAG_QZFS_QUANTITY	((BYTE)2)			// 数量

// 买入金额计算基准(TDX_ID_MRJEJSJZ)
#define TDX_FLAG_MRJEJSJZ_DEFAULT	((BYTE)0)		// 默认
#define TDX_FLAG_MRJEJSJZ_AMOUNT	((BYTE)1)		// 金额
#define TDX_FLAG_MRJEJSJZ_FUTURES	((BYTE)2)		// 期货
#define TDX_FLAG_MRJEJSJZ_INDEX		((BYTE)3)		// 指数


//---------------------------------------------------------------------------
// Part.VII 基本限制字段(其他头文件中有定义)
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
// Part.VIII 客户端类型(自动升级使用,详细版本类型)(其他头文件中有定义)
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
// 客户类型(决定佣金比率)
//---------------------------------------------------------------------------
#define CLITYPE_INVALID				0				// 未知类型
#define CLITYPE_INTERNET			12				// 网上交易用户
#define CLITYPE_FLOOR				18				// 场内交易用户
#define CLITYPE_WEB					19				// WEB交易用户	
#define CLITYPE_MOBILE				20				// 移动交易用户
#define CLITYPE_BROKER				21				// 经纪人用户



//---------------------------------------------------------------------------
// Part.IX 客户端支持的安全级别以及认证方式
//---------------------------------------------------------------------------
// 安全级别定义
#define SCLV_SIMPLE					1				// 帐户验证方式(交易密码+验证码)
#define SCLV_AUTHPASS				2				// 帐户验证+认证口令方式(交易密码+认证口令|通讯密码,三方有申请按钮)
#define SCLV_CA						4				// 帐户验证+认证证书方式(包括三方文件证书,交易密码+证书密码,有证书管理)
#define SCLV_OTP					8				// 帐号验证+OTP(交易密码+动态口令,有同步按钮,取决于是否支持同步)
#define SCLV_UKEY					16				// 帐号验证+UKEY(三方硬证书,交易密码+证书密码,有证书管理)
#define SCLV_RC						32				// 帐号验证+矩阵卡(交易密码+验证码)
#define SCLV_MOTP					64				// 帐号验证+手机OTP(交易密码+动态口令,有同步按钮,取决于是否支持同步)
#define SCLV_SMSC					128				// 帐号验证+短信口令(支持任何方式下的,交易密码+动态口令,有获取按钮)

// 服务器支持的安全模式
#define TDXSSL_AUTHORITY			0				// 通达信SSL加密
#define AUTHPASS_AUTHORITY			1				// 认证口令
#define DIGITCERT_AUTHORITY			2				// 数字证书(包括三方文件证书)
#define OTP_AUTHORITY				3				// OTP验证(包括口令卡)
#define UKEY_AUTHORITY				4				// UKEY验证(三方硬证书)
#define RC_AUTHORITY				5				// 矩阵卡
#define MOTP_AUTHORITY				6				// 手机OTP
#define SMSC_AUTHORITY				7				// 短信口令

#define SERVICE_AUTHORITY			64				// 服务密码(仅限于交易中心使用)
#define QUESTION_AUTHORITY			65				// 密保问题(仅限于交易中心使用)
#define SSO_AUTHORITY				66				// SSO验证(仅限于交易中心使用)
#define CAROLLBACK_AUTHORITY		67				// CA回滚验证(仅限于交易中心使用,一般用于外部工具回滚操作使用)
#define TELLEROPER_AUTHORITY		68				// 柜员操作验证(仅限于交易中心使用,一般用于外部工具到柜台的一次性操作)

//新增服务器支持的安全方式
#define SCLV_DLWZTS					10				// 登陆位置提示
#define SCLV_MMBHWT					11				// 密码保护问题
#define SCLV_JQTZMBD				12				// 机器特征码绑定	


//---------------------------------------------------------------------------
// Part.X 功能类型定义(其他头文件中有定义)
//---------------------------------------------------------------------------




//---------------------------------------------------------------------------
// Part.XI DLL券商ID定义
//---------------------------------------------------------------------------
#define NORMAL_DLL						0			// 通用
#define	CJZQ_DLL						1			// 长江证券
#define	DYCY_DLL						2			// 第一创业
#define	DGZQ_DLL						3			// 东莞证券
#define	GXZQ_DLL						4			// 国信证券
#define	HTZQ_DLL						5			// 汉唐证券
#define	LHZQ_DLL						6			// 联合证券
#define	PAZQ_DLL						7			// 平安证券
#define	TQZQ_DLL						8			// 天勤证券
#define	MAZQ_DLL						9			// 民安证券
#define	JQZQ_DLL						10			// 健桥证券
#define	TTZQ_DLL						11			// 天同证券
#define	GFZQ_DLL						12			// 广发证券
#define DTZQ_DLL						13			// 大通证券
#define	HXZQ_DLL						14			// 华西证券
#define	XYZQ_DLL						15			// 兴业证券
#define	ZSZQ_DLL						16			// 招商证券
#define	JYZQ_DLL						17			// 金元证券
#define	ZXJT_DLL						18			// 中信建投
#define	YNHT_DLL						19			// 红塔证券
#define	CCZQ_DLL						20			// 长城证券
#define	HYZQ_DLL						21			// 宏源证券
#define	GTJA_DLL						22			// 国泰君安
#define	SJZQ_DLL						23			// 世纪证券
#define	AXZQ_DLL						24			// 安信证券
#define	CFZQ_DLL						25			// 财富证券
#define	DXZQ_DLL						26			// 东兴证券(闽发证券)
#define	YHZQ_DLL						27			// 银河证券
#define	GDZQ_DLL						28			// 光大证券
#define YDZQ_DLL						29			// 英大证券
#define DBZQ_DLL						30			// 德邦证券
#define	NJZQ_DLL						31			// 南京证券
#define ZXZQ_DLL						32			// 中信证券
#define SHZQ_DLL						33			// 上海证券
#define HBZQ_DLL						34			// 华宝证券
#define AJZQ_DLL						35			// 爱建证券
#define QLZQ_DLL						36			// 齐鲁证券
#define ZYGJ_DLL						37			// 中银国际
#define MZZQ_DLL						38			// 民族证券
#define XCZQ_DLL						39			// 湘财证券
#define GJZQ_DLL						40			// 国金证券
#define SCZQ_DLL						41			// 首创证券
#define GLZQ_DLL						42			// 国联证券
#define HLZQ_DLL						43			// 华林证券
#define HFZQ_DLL						44			// 华福证券
#define GYZQ_DLL						45			// 国元证券
#define GZZQ_DLL						46			// 广州证券
#define FZZQ_DLL						47			// 方正证券
#define BHZQ_DLL						48			// 渤海证券
#define XNZQ_DLL						49			// 西南证券
#define XSDZQ_DLL						50			// 新时代证券
#define ZTZQ_DLL						51			// 中投证券
#define HRZQ_DLL						52			// 华融证券
#define SYWG_DLL						53			// 申银万国
#define SHHX_DLL						54			// 华鑫证券
#define NJHT_DLL						55			// 华泰证券
#define JLDB_DLL						56			// 东北证券
#define MSZQ_DLL						57			// 民生证券
#define SXDT_DLL						58			// 大同证券
#define ZCZQ_DLL						59			// 众成证券
#define XMZQ_DLL						60			// 厦门证券
#define DFZQ_DLL						61			// 东方证券
#define YTZQ_DLL						62			// 银泰证券
#define ZXGJHK_DLL						63			// 中信国际HK
#define GDKGHK_DLL						64			// 光大控股HK
#define ZSXGHK_DLL						65			// 招商香港HK
#define BDZQHK_DLL						66			// 博大证券HK
#define JNZQ_DLL						67			// 江南证券
#define WHZQ_DLL						68			// 万和证券
#define HKZQ_DLL						69			// 航空证券
#define ZXWT_DLL						70			// 中信万通
#define XDZQ_DLL						71			// 信达证券
#define WKZQ_DLL						72			// 五矿证券
#define JHZQ_DLL						73			// 江海证券
#define HCZQ_DLL						74			// 华创证券
#define TPYZQ_DLL						75			// 太平洋证券
#define GHZQ_DLL						76			// 国海证券
#define DHZQ_DLL						77			// 东海证券
#define XBZQ_DLL						78			// 西部证券
#define SXZQ_DLL						79			// 山西证券
#define KYZQ_DLL						80			// 开源证券
#define HAZQ_DLL						81			// 华安证券
#define GXZQHK_DLL						82			// 国信证券HK
#define GSZQ_DLL						83			// 国盛证券
#define ZJZXJT_DLL						84			// 中信金通
#define SCHX_DLL						85			// 和兴证券
#define XHJHK_DLL						86			// 新鸿基HK
#define QFZQHK_DLL						87			// 侨丰证券HK
#define RFZQHK_DLL						88			// 日发证券HK
#define WLZQ_DLL						89			// 万联证券
#define LNZT_DLL						90			// 中天证券
#define XDGJHK_DLL						91			// 信达国际HK
#define NMHT_DLL						92			// 恒泰证券
#define TFZQ_DLL						93			// 天风证券
#define GSHL_DLL						94			// 华龙证券
#define RXZQ_DLL						95			// 日信证券
#define ZHZQ_DLL						96			// 中航证券
#define DFXGHK_DLL						97			// 东方香港HK
#define CTZQ_DLL						98			// 财通证券
#define YFJHK_DLL						99			// 永丰金HK
#define NFJJ_DLL						100			// 南方基金
#define YXZQHK_DLL						101			// 越秀证券HK
#define SHHT_DLL						102			// 海通证券
#define DWZQ_DLL						103			// 东吴证券
#define ZJZS_DLL						104			// 浙商证券
#define JDTZHK_DLL						105			// 金道投资HK
#define LXZQ_DLL						106			// 联讯证券
#define CFLA_DLL						107			// 财富里昂
#define GYXGHK_DLL						108			// 国元香港HK
#define XZTX_DLL						109			// 西藏同信
#define ZYZQ_DLL						110			// 中原证券
#define BJGD_DLL						111			// 国都证券
#define QLGJHK_DLL						112			// 齐鲁国际HK
#define JHZQHK_DLL						113			// 金辉证券HK
#define ZJZQ_DLL						114			// 中金证券

#define	MAX_QSID						114			// 最大券商ID

#if !defined(NO_QSIDS)

typedef struct tagQSIDInfo
{
	DWORD	dwQSID;
	CHAR	szQSSX[6+1];
	CHAR	szQSMC[12+1];
} QSID_INFO, *LPQSID_INFO;

const QSID_INFO tdxQSIDInfo[]=
{
//	券商ID		券商拼音缩写(最多6字节)	券商汉字名称(最多6汉字)
	{	NORMAL_DLL,	"",						"",					},
	{	CJZQ_DLL,	"CJZQ",					"长江证券",			},
	{	DYCY_DLL,	"DYCY",					"第一创业",			},
	{	DGZQ_DLL,	"DGZQ",					"东莞证券",			},
	{	GXZQ_DLL,	"GXZQ",					"国信证券",			},
	{	HTZQ_DLL,	"HTZQ",					"汉唐证券",			},
	{	LHZQ_DLL,	"LHZQ",					"联合证券",			},
	{	PAZQ_DLL,	"PAZQ",					"平安证券",			},
	{	TQZQ_DLL,	"TQZQ",					"天勤证券",			},
	{	MAZQ_DLL,	"MAZQ",					"民安证券",			},
	{	JQZQ_DLL,	"JQZQ",					"健桥证券",			},
	{	TTZQ_DLL,	"TTZQ",					"天同证券",			},
	{	GFZQ_DLL,	"GFZQ",					"广发证券",			},
	{	DTZQ_DLL,	"DTZQ",					"大通证券",			},
	{	HXZQ_DLL,	"HXZQ",					"华西证券",			},
	{	XYZQ_DLL,	"XYZQ",					"兴业证券",			},
	{	ZSZQ_DLL,	"ZSZQ",					"招商证券",			},
	{	JYZQ_DLL,	"JYZQ",					"金元证券",			},
	{	ZXJT_DLL,	"ZXJT",					"中信建投",			},
	{	YNHT_DLL,	"YNHT",					"红塔证券",			},
	{	CCZQ_DLL,	"CCZQ",					"长城证券",			},
	{	HYZQ_DLL,	"HYZQ",					"宏源证券",			},
	{	GTJA_DLL,	"GTJA",					"国泰君安",			},
	{	SJZQ_DLL,	"SJZQ",					"世纪证券",			},
	{	AXZQ_DLL,	"AXZQ",					"安信证券",			},
	{	CFZQ_DLL,	"CFZQ",					"财富证券",			},
	{	DXZQ_DLL,	"DXZQ",					"东兴证券",			},
	{	YHZQ_DLL,	"YHZQ",					"银河证券",			},
	{	GDZQ_DLL,	"GDZQ",					"光大证券",			},
	{	YDZQ_DLL,	"YDZQ",					"英大证券",			},
	{	DBZQ_DLL,	"DBZQ",					"德邦证券",			},
	{	NJZQ_DLL,	"NJZQ",					"南京证券",			},
	{	ZXZQ_DLL,	"ZXZQ",					"中信证券",			},
	{	SHZQ_DLL,	"SHZQ",					"上海证券",			},
	{	HBZQ_DLL,	"HBZQ",					"华宝证券",			},
	{	AJZQ_DLL,	"AJZQ",					"爱建证券",			},
	{	QLZQ_DLL,	"QLZQ",					"齐鲁证券",			},
	{	ZYGJ_DLL,	"ZYGJ",					"中银国际",			},
	{	MZZQ_DLL,	"MZZQ",					"民族证券",			},
	{	XCZQ_DLL,	"XCZQ",					"湘财证券",			},
	{	GJZQ_DLL,	"GJZQ",					"国金证券",			},
	{	SCZQ_DLL,	"SCZQ",					"首创证券",			},
	{	GLZQ_DLL,	"GLZQ",					"国联证券",			},
	{	HLZQ_DLL,	"HLZQ",					"华林证券",			},
	{	HFZQ_DLL,	"HFZQ",					"华福证券",			},
	{	GYZQ_DLL,	"GYZQ",					"国元证券",			},
	{	GZZQ_DLL,	"GZZQ",					"广州证券",			},
	{	FZZQ_DLL,	"FZZQ",					"方正证券",			},
	{	BHZQ_DLL,	"BHZQ",					"渤海证券",			},
	{	XNZQ_DLL,	"XNZQ",					"西南证券",			},
	{	XSDZQ_DLL,	"XSDZQ",				"新时代证券",		},
	{	ZTZQ_DLL,	"ZTZQ",					"中投证券",			},
	{	HRZQ_DLL,	"HRZQ",					"华融证券",			},
	{	SYWG_DLL,	"SYWG",					"申银万国",			},
	{	SHHX_DLL,	"SHHX",					"华鑫证券",			},
	{	NJHT_DLL,	"NJHT",					"华泰证券",			},
	{	JLDB_DLL,	"JLDB",					"东北证券",			},
	{	MSZQ_DLL,	"MSZQ",					"民生证券",			},
	{	SXDT_DLL,	"SXDT",					"大同证券",			},
	{	ZCZQ_DLL,	"ZCZQ",					"众成证券",			},
	{	XMZQ_DLL,	"XMZQ",					"厦门证券",			},
	{	DFZQ_DLL,	"DFZQ",					"东方证券",			},
	{	YTZQ_DLL,	"YTZQ",					"银泰证券",			},
	{	ZXGJHK_DLL,	"ZXGJHK",				"中信国际HK",		},
	{	GDKGHK_DLL,	"GDKGHK",				"光大控股HK",		},
	{	ZSXGHK_DLL,	"ZSXGHK",				"招商香港HK",		},
	{	BDZQHK_DLL,	"BDZQHK",				"博大证券HK",		},
	{	JNZQ_DLL,	"JNZQ",					"江南证券",			},
	{	WHZQ_DLL,	"WHZQ",					"万和证券",			},
	{	HKZQ_DLL,	"HKZQ",					"航空证券",			},
	{	ZXWT_DLL,	"ZXWT",					"中信万通",			},
	{	XDZQ_DLL,	"XDZQ",					"信达证券",			},
	{	WKZQ_DLL,	"WKZQ",					"五矿证券",			},
	{	JHZQ_DLL,	"JHZQ",					"江海证券",			},
	{	HCZQ_DLL,	"HCZQ",					"华创证券",			},
	{	TPYZQ_DLL,	"TPYZQ",				"太平洋证券",		},
	{	GHZQ_DLL,	"GHZQ",					"国海证券",			},
	{	DHZQ_DLL,	"DHZQ",					"东海证券",			},
	{	XBZQ_DLL,	"XBZQ",					"西部证券",			},
	{	SXZQ_DLL,	"SXZQ",					"山西证券",			},
	{	KYZQ_DLL,	"KYZQ",					"开源证券",			},
	{	HAZQ_DLL,	"HAZQ",					"华安证券",			},
	{	GXZQHK_DLL,	"GXZQHK",				"国信证券HK",		},
	{	GSZQ_DLL,	"GSZQ",					"国盛证券",			},
	{	ZJZXJT_DLL,	"ZJZXJT",				"中信金通",			},
	{	SCHX_DLL,	"SCHX",					"和兴证券",			},
	{	XHJHK_DLL,	"XHJHK",				"新鸿基HK",			},
	{	QFZQHK_DLL,	"QFZQHK",				"侨丰证券HK",		},
	{	RFZQHK_DLL,	"RFZQHK",				"日发证券HK",		},
	{	WLZQ_DLL,	"WLZQ",					"万联证券",			},
	{	LNZT_DLL,	"LNZT",					"中天证券",			},
	{	XDGJHK_DLL,	"XDGJHK",				"信达国际HK",		},
	{	NMHT_DLL,	"NMHT",					"恒泰证券",			},
	{	TFZQ_DLL,	"TFZQ",					"天风证券",			},
	{	GSHL_DLL,	"GSHL",					"华龙证券",			},
	{	RXZQ_DLL,	"RXZQ",					"日信证券",			},
	{	ZHZQ_DLL,	"ZHZQ",					"中航证券",			},
	{	DFXGHK_DLL,	"DFXGHK",				"东方香港HK",		},
	{	CTZQ_DLL,	"CTZQ",					"财通证券",			},
	{	YFJHK_DLL,	"YFJHK",				"永丰金HK",			},
	{	NFJJ_DLL,	"NFJJ",					"南方基金",			},
	{	YXZQHK_DLL,	"YXZQHK",				"越秀证券HK",		},
	{	SHHT_DLL,	"SHHT",					"海通证券",			},
	{	DWZQ_DLL,	"DWZQ",					"东吴证券",			},
	{	ZJZS_DLL,	"ZJZS",					"浙商证券",			},
	{	JDTZHK_DLL,	"JDTZHK",				"金道投资HK",		},
	{	LXZQ_DLL,	"LXZQ",					"联讯证券",			},
	{	CFLA_DLL,	"CFLA",					"财富里昂",			},
	{	GYXGHK_DLL,	"GYXGHK",				"国元香港HK",		},
	{	XZTX_DLL,	"XZTX",					"西藏同信",			},
	{	ZYZQ_DLL,	"ZYZQ",					"中原证券",			},
	{	BJGD_DLL,	"BJGD",					"国都证券",			},
	{	QLGJHK_DLL,	"QLGJHK",				"齐鲁国际HK",		},
	{	JHZQHK_DLL,	"JHZQHK",				"金辉证券HK",		},
	{	ZJZQ_DLL,	"ZJZQ",					"中金证券",			},
};

inline LPCSTR GetQsName( DWORD dwQSID )
{
	for ( LONG i=0; i<(LONG)(sizeof(tdxQSIDInfo)/sizeof(QSID_INFO)); i++ )
	{
		if ( dwQSID == tdxQSIDInfo[i].dwQSID ) return tdxQSIDInfo[i].szQSMC;
	}
	return "";
}

inline LPCSTR GetQssx( DWORD dwQSID )
{
	for ( LONG i=0; i<(LONG)(sizeof(tdxQSIDInfo)/sizeof(QSID_INFO)); i++ )
	{
		if ( dwQSID == tdxQSIDInfo[i].dwQSID ) return tdxQSIDInfo[i].szQSSX;
	}
	return "";
}

#endif

//---------------------------------------------------------------------------
// Part.XII 市场信息结构(其他头文件中有定义)
//---------------------------------------------------------------------------
#ifndef MARKETINFO_TYPE
#define MARKETINFO_TYPE
	// 商品类别
	enum enumSPLB
	{	SPLB_ZS=1,			// 指数
		SPLB_AG=2,			// A股
		SPLB_AGQZ=3,		// A股权证
		SPLB_AGTP=4,		// A股投票
		SPLB_AGQZXQ=5,		// A股权证行权
		SPLB_BG=6,			// B股
		SPLB_BGQZ=7,		// B股权证
		SPLB_BGTP=8,		// B股投票
		SPLB_BGQZXQ=9,		// B股权证行权
		SPLB_ZF=10,			// 增发
		SPLB_PS=11,			// 配售
		SPLB_PZ=12,			// 配债
		SPLB_PG=13,			// 配股
		SPLB_ZXB=14,		// 中小板
		SPLB_ZXBTP=15,		// 中小板投票
		SPLB_SBRMB=16,		// 三板人民币
		SPLB_XSBRMB=17,		// 新三板人民币
		SPLB_SBMY=18,		// 三板美元
		SPLB_SBGY=19,		// 三板港元
		SPLB_GZ=20,			// 国债
		SPLB_QZ=21,			// 企债
		SPLB_ZZ=22,			// 转债
		SPLB_FZ=23,			// 发债
		SPLB_ZG=24,			// 转股
		SPLB_GZZYHG=25,		// 国债质押回购
		SPLB_QZZYHG=26,		// 企债质押回购
		SPLB_GZMDSHG=27,	// 国债买断式回购
		SPLB_GZXZYHG=28,	// 国债新质押回购
		SPLB_GZXZYHGSB=29,	// 国债新质押申报
		SPLB_QTHG=30,		// 其它回购
		SPLB_FBJJ=31,		// 封闭基金
		SPLB_KFSJJ=32,		// 开放基金
		SPLB_KFSJJGN=33,	// 基金功能码
		SPLB_ETF=34,		// ETF基金
		SPLB_LOF=35,		// LOF基金
		SPLB_GZFX=36,		// 国债分销代码
		SPLB_QT=37,			// 其它
		SPLB_BZH=38,		// B转H
	};
	// 币种标识
	enum enumBZBS
	{	BZ_RMB=0,		// 人民币
		BZ_MY=1,		// 美元
		BZ_GY=2,		// 港币

		BZ_CNY=BZ_RMB,	// 人民币
		BZ_USD=BZ_MY,	// 美元
		BZ_HKD=BZ_GY,	// 港元
		BZ_EUR=3,		// 欧元
		BZ_JPY=4,		// 日元
		BZ_SGD=5,		// 新加坡元
		BZ_AUD=6,		// 澳元
		BZ_CAD=7,		// 加元
		BZ_GBP=8,		// 英镑
		BZ_IDR=9,		// 印尼盾
		BZ_MYR=10,		// 马元
		BZ_NOK=11,		// 挪威克朗
		BZ_THB=12,		// 泰铢
		BZ_TWD=13,		// 新台币
		BZ_PHP=14,		// 菲律宾比索
	};
	// 国债标识
	enum enumGZBS
	{	GZBS_NULL=-1,	// 非国债
		GZBS_GZXH=0,	// 国债现货
		GZBS_QZ=1,		// 企业债
		GZBS_ZZ=2,		// 可转债
		GZBS_GZHG=3,	// 国债回购
	};
#endif
	
	
	
	//---------------------------------------------------------------------------
	// Part.XIII 功能调用接口(其他头文件中有定义)
	//---------------------------------------------------------------------------
	// 业务返回
	enum enumDICTRET
	{	DICTRET_PROC_SUCCESS=0,			// 功能调用成功
		DICTRET_PROC_FAIL=-1,			// 功能调用常规错误
		DICTRET_FATAL_FAIL=-2,			// 数据字典致命错误
		DICTRET_LOGIN_SCNTR_FAIL=-3,	// 功能(登录请求)调用,安全登录错误(帐号错误或者密码错误)
		DICTRET_LOGIN_FAIL=-4,			// 功能(登录请求)调用,登录错误(帐号错误或者密码错误)
		DICTRET_PROC_KICKOUT=-5,		// 功能调用,被踢出(有相同帐号登录,先登录者被踢出)
		DICTRET_PROC_SQLBUSY=-6,		// 功能调用,数据库繁忙
		DICTRET_PROC_LINKBUSY=-7,		// 功能调用,链路已满
		DICTRET_PROC_WARNING=-8,		// 功能调用,功能警告
		DICTRET_LOGIN_NOTVIP=-9,		// 功能(登录请求)调用,非VIP客户登录VIP主站错误
		DICTRET_LOGIN_GETSMS=-10,		// 功能(登录请求)调用,获取手机短信(成功)
	};
	
	
	// 标准错误号宏(PROTERR)
	// 定义已转入各类协议定义头文件
	// 已按照协议类型分解进入各协议定义。
	
	// 移植到VS2005
#ifdef WIN32
#pragma warning (pop)
#endif
	
#endif

