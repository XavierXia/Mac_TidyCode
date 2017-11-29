//
//  wtstruct.h
//  tdxiphone
//
//  Created by tdx on 11-2-23.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#import "macro.h"
#import "jyconfig.h"
#import "struct.h"
@interface  GdmxInfo	: NSObject<NSCoding>					//存放股东列表
{  
	int	 wttype;							//市场类型
	int	 specTrade;						//0--未指定交易  1--指定交易  2--当日新指定
	BOOL	 bxyjygd;							// 信用交易标识
	NSString  *gdmc;							//股东名称
	NSString  *gddm;							//股东代码
	NSString  *zjzh;							//资金帐号
	NSString  *xwdm;							//席位代码
	NSString  *memo;							// 备注
}
@property(nonatomic,retain) NSString*	gdmc;
@property(nonatomic,retain) NSString*	gddm;
@property(nonatomic) int wttype;
@property(nonatomic) int specTrade;
@property(nonatomic,retain) NSString* zjzh;
@property(nonatomic,retain) NSString* xwdm;
@property(nonatomic,retain) NSString* memo;
@property(nonatomic) BOOL bxyjygd;

+(NSString *)GetWtTypeStr2:(int)nwttype;
-(NSString *)GetWtTypeStr;
-(NSString *)GetGdDescribe;
-(GdmxInfo *)deepcopy;
@end

@interface  GpdmlInfo	: NSObject<NSCoding>					//存放代码链
{  
	NSMutableArray   * szGPArray;//深圳
	NSMutableArray * shGPArray;//上海
	NSDate     *savedate;
}
@property(nonatomic,retain) NSMutableArray   *szGPArray;
@property(nonatomic,retain) NSMutableArray   *shGPArray;
@property(nonatomic,retain) NSDate *savedate;

-(void)releasegpdml;

@end

@interface GdInfo : NSObject<NSCoding>
{
	NSMutableArray   *gddms;//GdmxInfo
	NSDate     *savedate;
	GdmxInfo  *m_SZA_MainGd;
	GdmxInfo  *m_SZB_MainGd;
	GdmxInfo  *m_SHA_MainGd;
	GdmxInfo  *m_SHB_MainGd;
	GdmxInfo  *m_SBA_MainGd;
	GdmxInfo  *m_SBB_MainGd;
	GdmxInfo  *m_SBG_MainGd;
	GdmxInfo  *m_SZA_MainxyGd;
	GdmxInfo  *m_SZB_MainxyGd;
	GdmxInfo  *m_SHA_MainxyGd;
	GdmxInfo  *m_SHB_MainxyGd;
	GdmxInfo  *m_SBA_MainxyGd;
	GdmxInfo  *m_SBB_MainxyGd;
	GdmxInfo  *m_SBG_MainxyGd;
	short	m_SZA_MainFlag;
	short	m_SZB_MainFlag;
	short	m_SHA_MainFlag;
	short	m_SHB_MainFlag;
	short	m_SBA_MainFlag;
	short	m_SBB_MainFlag;
	short	m_SBG_MainFlag;
	short	m_SZA_MainxyFlag;
	short	m_SZB_MainxyFlag;
	short	m_SHA_MainxyFlag;
	short	m_SHB_MainxyFlag;
	short	m_SBA_MainxyFlag;
	short	m_SBB_MainxyFlag;
	short	m_SBG_MainxyFlag;
	short	m_SZAGDNUM;
	short	m_SZBGDNUM;
	short	m_SHAGDNUM;
	short	m_SHBGDNUM;
	short	m_SBAGDNUM;
	short	m_SBBGDNUM;
	short	m_SBGGDNUM;
	short       m_gdcount;
	BOOL	m_bsfcguser;			// 是否三方存管用户
}
@property(nonatomic,retain) NSMutableArray   *gddms;
@property(nonatomic,retain) NSDate *savedate;
@property(nonatomic,retain) GdmxInfo  *m_SZA_MainGd;
@property(nonatomic,retain) GdmxInfo  *m_SZB_MainGd;
@property(nonatomic,retain) GdmxInfo  *m_SHA_MainGd;
@property(nonatomic,retain) GdmxInfo  *m_SHB_MainGd;
@property(nonatomic,retain) GdmxInfo  *m_SBA_MainGd;
@property(nonatomic,retain) GdmxInfo  *m_SBB_MainGd;
@property(nonatomic,retain) GdmxInfo  *m_SBG_MainGd;
@property(nonatomic,retain) GdmxInfo  *m_SZA_MainxyGd;
@property(nonatomic,retain) GdmxInfo  *m_SZB_MainxyGd;
@property(nonatomic,retain) GdmxInfo  *m_SHA_MainxyGd;
@property(nonatomic,retain) GdmxInfo  *m_SHB_MainxyGd;
@property(nonatomic,retain) GdmxInfo  *m_SBA_MainxyGd;
@property(nonatomic,retain) GdmxInfo  *m_SBB_MainxyGd;
@property(nonatomic,retain) GdmxInfo  *m_SBG_MainxyGd;
@property(nonatomic) short	m_SZA_MainFlag;
@property(nonatomic) short	m_SZB_MainFlag;
@property(nonatomic) short	m_SHA_MainFlag;
@property(nonatomic) short	m_SHB_MainFlag;
@property(nonatomic) short	m_SBA_MainFlag;
@property(nonatomic) short	m_SBB_MainFlag;
@property(nonatomic) short	m_SBG_MainFlag;
@property(nonatomic) short	m_SZA_MainxyFlag;
@property(nonatomic) short	m_SZB_MainxyFlag;
@property(nonatomic) short	m_SHA_MainxyFlag;
@property(nonatomic) short	m_SHB_MainxyFlag;
@property(nonatomic) short	m_SBA_MainxyFlag;
@property(nonatomic) short	m_SBB_MainxyFlag;
@property(nonatomic) short	m_SBG_MainxyFlag;
@property(nonatomic) short	m_SZAGDNUM;
@property(nonatomic) short	m_SZBGDNUM;
@property(nonatomic) short	m_SHAGDNUM;
@property(nonatomic) short	m_SHBGDNUM;
@property(nonatomic) short	m_SBAGDNUM;
@property(nonatomic) short	m_SBBGDNUM;
@property(nonatomic) short	m_SBGGDNUM;
@property(nonatomic) short	m_gdcount;
@property(nonatomic) BOOL	m_bsfcguser;

-(void)resetflag;
-(void)releasegdmxs;
-(void)CalcGdInfo:(int)nloginWtType withrawzjzh:(NSString *)rawzjzh;
-(int)GetZhlbFromGddm:(NSString *)gddm;
-(BOOL)IsMainGd:(NSString *)gddm;
-(NSString *)GetMainGdStr:(NSString *)gddm;
-(int)GetGdCountBySc:(int)ntype;
-(GdmxInfo *)GetGdMxByScIndex:(int)ntype withindex:(int)index;
-(int)GetGdIndexBySc:(int)ntype withgdmx:(GdmxInfo *)pgdmx;
-(GdmxInfo *)GetGddm:(NSString *)strgddm;
@end

@interface Yhxxmx : NSObject<NSCoding>
{
	NSString *yhdm;//银行代码
	NSString *yhmc;//银行名称
	NSString *yhzh;//银行帐号
    NSString *zjzh;//资金帐号
	int   nbz;//币种
	int   nzcmmflag;//转入密码标志   0 none 1 资金密码 2 银行密码 3 both
	int   nzrmmflag;//转出密码标志
	int   nyemmflag;//银行余额密码标志
}
@property(nonatomic) int nbz;
@property(nonatomic,retain) NSString *yhdm;
@property(nonatomic,retain) NSString *yhmc;
@property(nonatomic,retain) NSString *yhzh;
@property(nonatomic,retain) NSString *zjzh;
@property(nonatomic) int  nzcmmflag;
@property(nonatomic) int  nzrmmflag;
@property(nonatomic) int  nyemmflag;

-(NSString *)GetBzStr;
-(Yhxxmx *)deepcopy;
@end

@interface YhxxInfo : NSObject<NSCoding>
{
	NSMutableArray *yhmxs;//Yhxxmx
	NSDate     *savedate;
	BOOL bqueryyhflag;
}
@property(nonatomic)	BOOL bqueryyhflag;
@property (nonatomic,retain) NSMutableArray *yhmxs;
@property(nonatomic,retain) NSDate *savedate;

-(void)releaseyhmxs;
-(Yhxxmx *)GetYhmxFromYhmc:(NSString *)yhmc;
-(Yhxxmx *)GetYhmxFromzjzh:(NSString *)zjzh;
@end

@interface ScStrucInfo : NSObject<NSCoding>
{
	int  setcode;//市场 0－－深市  1－－沪市
	int  ntype;//类型
	int  nzhlb;//账户类别
	int  nxsflag;//小数位数
	int  nbz;//币种
	int  ngzbz;//国债标志
	int  nxsdw;//现手单位
	int  nzsdw;//总手单位
	int  nkcdw;//库存单位
	int  nsbdw;//申报单位
	int  nsbxx;//申报下限
	int  nsbsx;//申报上限(万)
	float  fyj;//佣金
	float  fqbj;//佣金起步价
	NSString *zqdm;//代码规则
	NSString *lbname;//类别名称
	NSString *jldw;//计量单位
}
@property(nonatomic) int setcode;
@property(nonatomic) int ntype;
@property(nonatomic) int nzhlb;
@property(nonatomic) int nxsflag;
@property(nonatomic) int nbz;
@property(nonatomic) int ngzbz;
@property(nonatomic,retain) NSString *jldw;
@property(nonatomic) int nxsdw;
@property(nonatomic) int nzsdw;
@property(nonatomic) int nkcdw;
@property(nonatomic) int nsbdw;
@property(nonatomic) int nsbxx;
@property(nonatomic) int nsbsx;
@property(nonatomic) float   fyj;
@property(nonatomic) float   fqbj;
@property(nonatomic,retain) NSString *zqdm;
@property(nonatomic,retain) NSString *lbname;

-(ScStrucInfo *)deepcopy;
@end

@interface ScInfo : NSObject<NSCoding>
{
	NSMutableArray *m_scinfos;//ScStrucInfo
	BOOL	  m_bHasSCStruc;//是否获得了市场结构
	NSDate     *savedate;//保存日期
}
@property(nonatomic) BOOL m_bHasSCStruc;
@property(nonatomic,retain) NSMutableArray *m_scinfos;
@property(nonatomic,retain) NSDate *savedate;

-(void)loadScInfos;
-(void)releasescinfos;
@end

@interface JjZhInfo : NSObject<NSCoding>
{
	NSString *jjgsdm;//基金公司代码
	NSString *jjgsmc;//基金公司名称
	NSString *jjzh;//基金账户
	NSString *khmc;//客户名称
	NSString *zjhm;//证件号码
}

@property(nonatomic,retain) NSString *jjgsdm;
@property(nonatomic,retain) NSString *jjgsmc;
@property(nonatomic,retain) NSString *jjzh;
@property(nonatomic,retain) NSString *khmc;
@property(nonatomic,retain) NSString *zjhm;

-(JjZhInfo *)deepcopy;
@end

@interface JjgsInfo : NSObject<NSCoding>
{
	int  njjbs;
	NSString *jjgsdm;
	NSString *jjgsmc;
	NSString *jjgsdesc;
}
@property(nonatomic) int njjbs;
@property(nonatomic,retain) NSString *jjgsdm;
@property(nonatomic,retain) NSString *jjgsmc;
@property(nonatomic,retain) NSString *jjgsdesc;

-(JjgsInfo *)deepcopy;
@end


@interface JjdmInfo : NSObject<NSCoding>
{
	int      njjbs;
	float    zdcyfe;//最低持有份额
	double    zgshfe;//最高赎回份额
	float     jjjz;// 基金净值 
	float     grzdsgje;//个人最低申购金额
	float     frzdsgje;//法人最低申购金额
	int    njjjyzt;//基金交易状态
	NSString *jjgsdm;//基金公司代码
	NSString *jjdm;//基金代码
	NSString *jjmc;//基金名称
	NSString *jjjyzt;//基金交易状态
}
@property (nonatomic) int njjbs;
@property (nonatomic) int njjjyzt;
@property (nonatomic) float zdcyfe;
@property (nonatomic) double zgshfe;
@property (nonatomic) float jjjz;
@property(nonatomic) float grzdsgje;
@property(nonatomic) float frzdsgje;
@property(nonatomic,retain) NSString *jjgsdm;
@property(nonatomic,retain) NSString *jjdm;
@property(nonatomic,retain) NSString *jjmc;
@property(nonatomic,retain) NSString *jjjyzt;

-(NSString *)GetJjDescribe;
-(NSString *)GetJjDescribe2;

-(JjdmInfo *)deepcopy;
@end

@interface JjInfo : NSObject<NSCoding>
{
	BOOL       bqueryjjzhflag;//是否已经查询了基金账户
	short       njjzhztbz;//基金账户状态标志
	short	njjnum;//基金总数
	short       nkrgjjnum;//可认购基金数量
	short       nksgjjnum;//可申购基金数量
	NSString  *strjjzhztbz;//基金账户状态标志描述
	NSMutableDictionary *jjzhdict;//基金账户信息 ,JjZhInfo
	NSMutableDictionary *jjdmdict;//基金代码信息 JjdmInfo
	NSMutableArray  *jjsgdminfo;//基金申购代码
	NSMutableArray  *jjrgdminfo;//基金认购代码
	NSDate     *savedate;//保存日期
	NSMutableArray *jjgsinfo;//基金公司信息  JjgsInfo
	NSMutableArray *jjzhinfo;//基金账户信息 ,JjZhInfo
	NSMutableArray *jjdminfo;//基金代码信息 JjdmInfo
}
@property(nonatomic) short njjnum;
@property(nonatomic) short nkrgjjnum;
@property(nonatomic) short nksgjjnum;
@property (nonatomic) BOOL bqueryjjzhflag;
@property(nonatomic,retain) NSString  *strjjzhztbz;
@property(nonatomic,retain) NSMutableArray *jjzhinfo;
@property(nonatomic,retain) NSMutableArray *jjdminfo;
@property(nonatomic,retain) NSMutableDictionary *jjzhdict;
@property(nonatomic,retain) NSMutableDictionary *jjdmdict;
@property(nonatomic) short njjzhztbz;
@property(nonatomic,retain) NSMutableArray *jjsgdminfo;
@property(nonatomic,retain) NSMutableArray *jjrgdminfo;
@property(nonatomic,retain) NSMutableArray *jjgsinfo;
@property(nonatomic,retain) NSDate *savedate;

-(id)init;
-(void)dealloc;
-(void)releasejjinfos;
-(NSString *)GetJJDescribe:(NSString *)jjdm;
-(JjdmInfo *)GetJjdmInfo:(NSString *)jjdm;
@end

typedef struct st_zjgfinfo
{
	double  ye[3];//余额
	double  keyong[3];//可用
	double  kqzj[3];//可取
	double  ztzj[3];//在途资金
	double  djzj[3];//冻结资金
	double  zsz[3];//总市值
	double  fdyk[3];//浮动盈亏
	double  zzc[3];//总资产
	double  gtzzc[3];//柜台总资产
	double jjzzc[3];//基金总资产
	double jjfdyk[3];//基金浮动盈亏
	double jjzsz[3];//基金总市值
	double lczzc[3];//理财总资产
	double lcfdyk[3];//理财浮动盈亏
	double lczsz[3];//理财总市值
    double lastzsz[3];
}ST_ZJGFINFO;

@interface Gsdm_Selgd : NSObject
{
	int type;
	NSString *gsdm;
}
@property(nonatomic,retain) NSString *gsdm;
@property(nonatomic) int type;
 
@end


@interface Tradeccf : NSObject
{
	BOOL bweaktip;
	int    nszgzdw;//深圳国债单位
	int    nshgzdw;//上海国债单位
	BOOL m_bjjzndtex;//是否新版智能定投
	NSMutableArray *lcgsdm;//NSString 理财公司代码
	NSMutableArray *exceptlcgsdm;//基金公司代码中去除的理财公司代码
	NSMutableArray *zyckgpdms;//质押出库股票代码
	NSMutableArray *gsdm_selgds;//Gsdm_Selgd根据基金公司代码判断是否选择股东
    int nLSWTJGTS; //历史查询间隔天数
}
@property(nonatomic) BOOL m_bjjzndtex;
@property(nonatomic) int nszgzdw;
@property(nonatomic) int nshgzdw;
@property(nonatomic) BOOL bweaktip;
@property(nonatomic,retain) NSMutableArray *lcgsdm;
@property(nonatomic,retain) NSMutableArray *exceptlcgsdm;
@property(nonatomic,retain) NSMutableArray *zyckgpdms;
@property(nonatomic,retain) NSMutableArray *gsdm_selgds;
@property(nonatomic) int nLSWTJGTS;

-(void)loadTradeccf;//登录成功后加载
-(BOOL)Islcgsdm:(NSString *)gsdm;
-(BOOL)IsExceptLcgsdm:(NSString *)gsdm;
-(BOOL)IsZyckgpdm:(NSString *)gpdm;
-(int)GetGsType:(NSString *)jjgsdm;
@end


@interface LoginInfo : NSObject<NSCoding>
{
	BOOL       bsavezh;
	int		naqfs;
	int           m_loginWtType;
	NSString *m_rawzjzh;
	NSString *m_rawbranchid;
	NSString *m_strzhlx;
}
@property(nonatomic) int m_loginWtType;
@property(nonatomic,retain) NSString *m_rawzjzh;
@property(nonatomic,retain) NSString *m_rawbranchid;
@property(nonatomic,retain) NSString *m_strzhlx;
@property(nonatomic) int naqfs;
@property(nonatomic) BOOL bsavezh;


-(void)releasecontent;
-(LoginInfo *)deepcopy;
-(NSString *)GetZhDescribe:(int)nqsbs;
@end

@interface MultizhLogininfo : NSObject<NSCoding>
{
	NSMutableArray *zhinfos;//LoginInfo
}

@property(nonatomic,retain) NSMutableArray *zhinfos;

-(int)getIndex:(LoginInfo *)prawLogin;
-(int)getIndex:(NSString *)account withzhlx:(LoginMode *)ploginmode;
-(void)releasezhinfos;
-(void)releasezhinfos2;
@end

@interface TradeSiteInfo : NSObject<NSCoding>
{
	BOOL  bfindbest;//是否查找最快站点
	int   nlastindex;//上次登录的站点
	NSMutableArray  *tradesites;//TradeSite自定义交易中心
}
@property(nonatomic) BOOL bfindbest;
@property(nonatomic) int nlastindex;
@property(nonatomic,retain) NSMutableArray  *tradesites;

-(void)releaseSiteinfos;
@end

@interface DataLitj : NSObject<NSCoding>
{
	float Wifisndlen;//Wifi发送
	float Wifircvlen;//Wifi接收
	float g3sndlen;//3G发送
	float g3rcvlen;//3G接收
	NSDate *savedate;//保存时间
	NSDate *cleandate;//清零时间
}
@property(nonatomic) float  Wifisndlen;
@property(nonatomic) float  Wifircvlen;
@property(nonatomic) float  g3sndlen;
@property(nonatomic) float  g3rcvlen;
@property(nonatomic,retain) NSDate *savedate;
@property(nonatomic,retain) NSDate *cleandate;

-(DataLitj *)deepcopy;
-(void)clean;
@end



@interface HttpProxyInfo : NSObject<NSCoding>
{
	BOOL  beUsedFlag;
	NSString *httpProxyAddress;//
	NSString *httpProxyPort;//
	NSString *httpProxyUsername;//
	NSString *httpProxyPassword;//
}

@property BOOL beUsedFlag;
@property(nonatomic,retain) NSString *httpProxyAddress;
@property(nonatomic,retain) NSString *httpProxyPort;
@property(nonatomic,retain) NSString *httpProxyUsername;
@property(nonatomic,retain) NSString *httpProxyPassword;

-(HttpProxyInfo *)deepcopy;
@end



@interface gridCellInfoForCache : NSObject<NSCoding>
{
	NSMutableArray  *gridCellInfoArray;
}
@property(nonatomic,retain) NSMutableArray  *gridCellInfoArray;

-(void)releaseSiteinfos;
@end


@interface localCache : NSObject {
	NSString *gddmcachefile;//存盘文件名
	NSString *yhxxcachefile;//存盘文件名
	NSString *jjxxcachefile;//基金信息存盘文件名
	NSString *lcxxcachefile;//理财信息存盘文件名
	NSString *logincachefile;//登录信息存盘文件名
	NSString *scinfocachefile;//市场info存盘文件名
	NSString *multilogincachefile;//多账户登录信息存盘文件名
	NSString *localjysitecachefile;//本地交易中心存盘文件名
	NSString *localhqsitecachefile;//本地行情中心存盘文件名
	NSString *localhqparamcachefile;//本地行情参数存盘文件名
	NSString *locallltjcachefile;//本地流量统计存盘文件名
	NSString *localzxlinkcachefile;//本地资讯链接存盘文件名
	NSString *localjyparamcachefile;//本地行情参数存盘文件名
	NSString *m_qsjc;
	NSString *gpdmlcachefile;//代码链存放文件名
	NSString *versionparamcachefile;//版本参数存盘文件名
	NSString *styleparamcachefile;//风格存盘文件名
	NSString *gridcellparamcachefile;//列表信息存盘文件名
	NSString *httpproxyinfoparamcachefile;//http代理信息存盘文件名
}
-(id)initloginInfo:(NSString *)qsjc;
-(void)initWithtoken:(NSString *)strtoken;
-(void)SaveHttpProxyInfo:(HttpProxyInfo*) httpproxyinfocache;//写http代理信息
-(HttpProxyInfo *)loadHttpProxyInfo;//读http代理信息
-(void)SaveGridCellInfo:(gridCellInfoForCache*) gridcellinfocache;//写列表信息
-(BOOL)loadGridcCellInfo:(gridCellInfoForCache*) gridcellinfocache;//读列表信息
-(void)SaveStyleParam:(StyleParams*) styleinfo;//写风格信息
-(StyleParams*)loadStyleParam;//读风格信息
-(void)SaveVersionParam:(VersionParam*) versioninfo;//写版本信息
-(BOOL)loadVersionParam:(VersionParam*) versioninfo;//读版本信息
-(void)SaveGpdml:(GpdmlInfo *)pgdmlinfo;//保存代码链
-(BOOL)loadGpdml:(GpdmlInfo *)pgdmlinfo;//读取代码链
-(void)SaveGddm:(GdInfo *)pgdinfo;//保存股东代码
-(BOOL)loadGddm:(GdInfo *)pgdinfo;//读取股东代码
-(void)SaveYhxx:(YhxxInfo *)pYhInfo;//保存银行信息
-(BOOL)loadYhxx:(YhxxInfo *)pYhInfo;//读取银行信息
-(void)SaveJjxx:(JjInfo *)pJjinfos;//保存基金信息
-(BOOL)loadJjxx:(JjInfo *)pJjinfos;//读取基金信息
-(void)SaveLcxx:(JjInfo *)pLcinfos;//保存理财信息
-(BOOL)loadLcxx:(JjInfo *)pLcinfos;//读取理财信息
-(void)SaveScInfo:(ScInfo *)pScInfo;//保存市场信息
-(BOOL)DeleteLoginInfo;
-(void)SaveLoginInfo:(LoginInfo *)plogininfo;//保存登录信息
-(LoginInfo *)loadLoginInfo;//读取登录信息
-(void)SaveScInfo:(ScInfo *)pScInfo;//保存市场信息
-(BOOL)loadScInfo:(ScInfo *)pScinfos;//读取市场信息
-(BOOL)DeleteMultiloginInfo;//删除多账户登录信息
-(void)SaveMultiloginInfo:(MultizhLogininfo *)pMultizhinfos;//保存多账户登录信息
-(BOOL)loadMultiloginInfo:(MultizhLogininfo *)pMultizhinfos;//读取多账户登录信息
-(void)SaveLocalJySite:(TradeSiteInfo *)pSiteInfo;//保存站点信息
-(BOOL)loadLocalJySite:(TradeSiteInfo *)pSiteInfo;//读取站点信息
-(void)SaveLocalHqSite:(TradeSiteInfo *)pSiteInfo;//保存站点信息
-(BOOL)loadLocalHqSite:(TradeSiteInfo *)pSiteInfo;//读取站点信息
-(void)SaveHqParamInfo:(HqParamInfo *)pHqParamInfo;//保存行情参数
-(HqParamInfo *)loadHqParamInfo;//读取行情参数
-(void)SaveDataLltjInfo:(DataLitj *)pDatainfo;//保存流量信息
-(DataLitj *)loadDataLltjInfo;//读取流量信息
-(void)SaveZxLinkInfo:(ZxLinkInfo *)pZxLinks;//保存资讯链接信息
-(BOOL)loadZxLinkInfo:(ZxLinkInfo *)pZxLinks;//读取资讯链接信息
-(void)SaveJyParamInfo:(JyParamInfo *)pJyParamInfo;//保存交易参数
-(JyParamInfo *)loadJyParamInfo;//读取交易参数
@end

@interface ZjgfInfoClass : NSObject
{
	ST_ZJGFINFO stzjgf;
}

@property(nonatomic) ST_ZJGFINFO stzjgf;

@end



@interface ClientInfo : NSObject
{
    
	BOOL	  m_blocking;//是否正在锁屏
    BOOL      m_DBPHZblocking;//担保品划转中是否正在锁屏
	short         m_nQsbs;//券商标志 
	short         m_TdxRealBranchID;
	short         m_nKhqx;
	BOOL	  m_bKfsjjflag;//是否基金用户
	BOOL	  m_bggflag;
	BOOL	  m_bqhflag;
	BOOL	  m_bgpflag;
	BOOL	  m_bGetMaxBuy;
	BOOL	  m_bxyjyflag;
	BOOL	  m_bgtbs;
	BOOL	  m_bonlyinithqinfo;
	BOOL	  m_blcflag;//是否理财用户 
	short	  m_nZhlb;
	short	  m_nRealZjzhNum;
	short	  m_nrealIndex;
	time_t	  m_nlastjyopertime;//交易上次操作时间
	NSMutableArray  *m_realzjzh;
	Tradeccf   *tradeccf;//交易配置
	ST_ZJGFINFO   stzjgf;//资金股份统计信息
	ST_ZJGFINFO   stzjgfjj;//资金股份统计信息
	ST_ZJGFINFO   stzjgflc;//资金股份统计信息
	ST_ZJGFINFO   strawzjgf;//资金股份统计信息
	ST_ZJGFINFO   strawzjgfjj;//资金股份统计信息
	ST_ZJGFINFO   strawzjgflc;//资金股份统计信息
	NSString   *m_strKhqxmc;//客户权限名称
	NSString	 *m_strTdxWtfs;
	NSString    *m_zjzh;
	NSString    *m_jjzjzh;
	NSString	 *m_username;
	GdInfo	 *gdinfos;//股东代码
	ScInfo       *scinfos;//市场结构
	JjInfo        *jjinfos;//基金相关信息 
	JjInfo        *lcinfos;//理财相关信息 
	localCache *caches;//缓存
	YhxxInfo   *yhxxs;//银行信息
	LoginInfo	  *logininfos;//登录信息 
	QsConfig     *qsconfigs;//交易配置信息
	MultizhLogininfo *multilogininfos;//已登录帐户缓存
	TradeSiteInfo  *localjysites;//本地的交易中心列表
	TradeSiteInfo  *localhqsites;//本地的行情中心列表
	HqParamInfo  *hqParams;//本地行情参数
	DataLitj	 *dataLltjs;//数据流量统计
	ZxLinkInfo  *zxLinks;//资讯链接
	JyParamInfo  *jyParams;//本地行情参数
	VersionParam * versionParams;
	StyleParams * styleParams;//风格参数
	gridCellInfoForCache * gridCellCache;//列表参数
	HttpProxyInfo * httpProxyInfo;
    NSString *dldzxy; //登录定制消息;
}
@property(nonatomic) time_t	  m_nlastjyopertime;
@property(nonatomic) BOOL	  m_blocking;
@property(nonatomic) BOOL	  m_bonlyinithqinfo;
@property(nonatomic,retain) Tradeccf   *tradeccf;
@property(nonatomic) short m_nrealIndex;
@property(nonatomic) short m_TdxRealBranchID;
@property(nonatomic) BOOL      m_DBPHZblocking;
@property(nonatomic) short m_nKhqx;
@property(nonatomic) BOOL m_bgtbs;
@property(nonatomic) BOOL m_bKfsjjflag;
@property(nonatomic) BOOL m_blcflag;
@property(nonatomic) BOOL m_bggflag;
@property(nonatomic) BOOL m_bgpflag;
@property(nonatomic) BOOL m_bqhflag;
@property(nonatomic) BOOL m_bGetMaxBuy;
@property(nonatomic,assign) BOOL m_bxyjyflag;
@property(nonatomic) short  m_nZhlb;
@property(nonatomic) short  m_nRealZjzhNum;
@property(nonatomic,retain) NSMutableArray *m_realzjzh;
@property(nonatomic,retain) NSString *m_strKhqxmc;
@property(nonatomic,retain) NSString *m_strTdxWtfs;
@property(nonatomic,retain) NSString *m_username;
@property(nonatomic,retain) NSString *m_jjzjzh;
@property(nonatomic,retain) NSString *dldzxy;
@property(nonatomic,retain) GdInfo *gdinfos;
@property(nonatomic,retain) ScInfo   *scinfos;
@property(nonatomic,retain) JjInfo   *jjinfos;
@property(nonatomic,retain) JjInfo   *lcinfos;
@property(nonatomic) short m_nQsbs;
@property(nonatomic,retain)localCache *caches;
@property(nonatomic,retain)NSString *m_zjzh;
@property(nonatomic,retain)YhxxInfo *yhxxs;
@property(nonatomic) ST_ZJGFINFO   stzjgf;
@property(nonatomic) ST_ZJGFINFO   stzjgfjj;
@property(nonatomic) ST_ZJGFINFO   stzjgflc;
@property(nonatomic) ST_ZJGFINFO  strawzjgf;
@property(nonatomic) ST_ZJGFINFO  strawzjgfjj;
@property(nonatomic) ST_ZJGFINFO  strawzjgflc;
@property(nonatomic,retain) LoginInfo	  *logininfos;
@property(nonatomic,retain)QsConfig     *qsconfigs;
@property(nonatomic,retain) MultizhLogininfo *multilogininfos;
@property(nonatomic,retain) TradeSiteInfo  *localjysites;
@property(nonatomic,retain) TradeSiteInfo  *localhqsites;
@property(nonatomic,retain) HqParamInfo  *hqParams;
@property(nonatomic,retain) JyParamInfo  *jyParams;
@property(nonatomic,retain) DataLitj	 *dataLltjs;
@property(nonatomic,retain) ZxLinkInfo  *zxLinks;
@property(nonatomic,retain) VersionParam * versionParams;
@property(nonatomic,retain) StyleParams * styleParams;
@property(nonatomic,retain) gridCellInfoForCache * gridCellCache;
@property(nonatomic,retain) HttpProxyInfo * httpProxyInfo;
-(int) GetNowSC:(const char *)code setcode:(int)nsetcode;
-(int) GetDomainFromCode:(const char*)code withsetcode:(int)nsetcode;
-(short) GetScNoZS_FromCode:(const char*)code withsetcode:(int)nsetcode;
-(GdmxInfo *) AutoChangeGddm:(GdmxInfo *)gdinfo withzqdm:(const char*)code withxyflag:(BOOL) bxyflag withsetcode:(int)nsetcode;
-(void)initcache;
-(int)GetBzFromZhlb:(int)nzhlb;
-(NSString *)GetZjzh;
-(NSColor *)GetUIColorFromJjbs:(int )jjbs;
-(NSString *)GetGdCacheInfo:(NSMutableArray *)showData withparse:(id)pParses StartIndex:(int)nstartindex ReqLines:(int)npagenum withrownum:(int *)ntotalline withsucflag:(BOOL *)bsucflag;
-(NSString *)GetJjgsCacheInfo:(NSMutableArray *)showData withparse:(id)pParses StartIndex:(int)nstartindex ReqLines:(int)npagenum withrownum:(int *)ntotalline withsucflag:(BOOL *)bsucflag;
-(NSString *)GetJjzhCacheInfo:(NSMutableArray *)showData withparse:(id)pParses StartIndex:(int)nstartindex ReqLines:(int)npagenum withrownum:(int *)ntotalline withsucflag:(BOOL *)bsucflag;
-(NSString *)GetJjdmCacheInfo:(NSMutableArray *)showData withparse:(id)pParses StartIndex:(int)nstartindex ReqLines:(int)npagenum withrownum:(int *)ntotalline withsucflag:(BOOL *)bsucflag;
-(NSString *)GetLcgsCacheInfo:(NSMutableArray *)showData withparse:(id)pParses StartIndex:(int)nstartindex ReqLines:(int)npagenum withrownum:(int *)ntotalline withsucflag:(BOOL *)bsucflag;
-(NSString *)GetLczhCacheInfo:(NSMutableArray *)showData withparse:(id)pParses StartIndex:(int)nstartindex ReqLines:(int)npagenum withrownum:(int *)ntotalline withsucflag:(BOOL *)bsucflag;
-(NSString *)GetLcdmCacheInfo:(NSMutableArray *)showData withparse:(id)pParses StartIndex:(int)nstartindex ReqLines:(int)npagenum withrownum:(int *)ntotalline withsucflag:(BOOL *)bsucflag;

-(ScStrucInfo *)GetScStructInfo:(const char *)zqdm setcode:(int)nsetcode;
-(NSColor *)GetUIColorFromfdyk:(float )fdyk;
-(NSString *)GetBzStr:(int)nbz;

-(BOOL)IsJyAutoLock;
-(void)jyhasoper;
-(NSMutableDictionary *)getAttributes:(NSString *)_fontName fontSize:(CGFloat)_fontSize theColor:(NSColor *)_theColor theAliment:(int)_theAliment;
-(BOOL)m_bxyjyflag;
-(void)setM_bxyjyflag:(BOOL)m_bxyjyflag;

@end

@interface NSData (TdxNSExtendedData)
- (void)getTdxBytes:(void *)buffer range:(NSRange)range;
@end

@implementation NSData (TdxNSExtendedData)

- (void)getTdxBytes:(void *)buffer range:(NSRange)range
{
    if(range.location==NSNotFound)
        return;
    if((range.location+range.length)>[self length])
        return;
    
    [self getBytes:buffer range:range];
}

@end
