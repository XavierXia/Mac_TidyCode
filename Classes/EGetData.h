//
//  EGetData.h
//  tdxiphone
//
//  Created by 魏 文敏 on 09-12-29.
//  Copyright 2009 武汉. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "EComm.h"
#import "macro.h"
#import "struct.h"
#import "wtstruct.h"
#import "SinHqInfo.h"
#import "ETradeComm.h"
#import "ParseRecv.h"
#import "des.h"
#import "Delegate.h"
#import "Reachability.h"
#import "Delegate.h"

typedef enum tradeType //信用交易交易类型
{
    DBPBuy = 0, //担保品买入
    DBPSell,    //担保品卖出
    RZBuy,      //融资买入
    RZSell,     //融资卖出
    DBPHZ = 8,     //担保品划转
    XYZCCX,     //信用资产查询
    XYFZCX,     //信用负债查询
    XYSXCX,     //信用上限查询
    XYRZHYCX,   //信用融资合约查询
    XYRQHYCX,   //信用融券合约查询
    DBPZQCX,    //担保品证券查询
    ZQCX,       //中签查询
    MQHK = 20, //卖券还款
    MQHQ,      //买券还券
    XJHK,      //现金还款
    XQHQ,      //现券还券
    XGSG,      //新股申购
}tradeType;

typedef enum HZFX //信用交易担保品划转方向
{
    HRXY = 0, //划入信用帐户
    HCXY,     //划出信用帐户
}HZFX;


@interface EGetData : NSObject  <NSXMLParserDelegate,TradeComDelegate,getdataDelegate,NSAlertDelegate>{
	//线程类
	NSThread * wtCHBThread;
	NSTimer * wtCHBTimer;
	NSOperationQueue * operationQueue;
	NSCondition* dataCondition;
	
	EComm * g_pEComm;
	SinHqInfo * currHpAns;
	NSMutableArray * codeinfo_data;
	NSMutableArray * minute_data;
	NSMutableArray * analyse_data;
	NSMutableArray * f10title_data;
	NSMutableArray * tick_data;
	NSString * f10Txt_data;
	NSString * info_data;
	NSString *logpath;
	//交易相关
	ETradeComm * g_TradeComm;
	BOOL tradeLoginFlag;
	InputSave * inputSave;
	DateSave * saveDate;
	ParseRecv * parseRecv;
	NSMutableArray* jjcodeArray;
	NSMutableArray* fecxArray ;
	NSMutableArray*	lxfsArray;
	ClientInfo      *clientinfos;//客户登录后的相关信息
	float refreshTime;//行情刷新时间
    float njylockspan;//交易锁屏间隔
	float sortRefreshTime;//排行刷新时间
	BOOL  theRefreshFLag;
	int hourDiff;
	int minuteDiff;
	int secondDiff;
	int yearDiff;
	int monthDiff;
	int dayDiff;
	int sysYMD;
	short b_yesterday;
	short bakFunc;
	
	float dataSend;
	float dataRec;
	float dataSend_3G;
	float dataRec_3G;
	
	//资讯相关
	NSXMLParser* xmlData;
	NSMutableArray* contentArray;
	NSString* currentString;
	NSString * currTitleString;
	NSString * currTimeString;
	
	NSArray * timeArray;
	BOOL showMineFlag;
	//状态相关 
	NetworkStatus netStat;
	BOOL showAlertFlag;
	BOOL clickAlertFlag;
	short hostTransferCount;
	BOOL initStockChainFlag;
	//查找最快
	BOOL	 bfindbestjy;
	BOOL	 bfindbesthq;
	int		_threadCount;
	NSCondition *_myCondition;
	NSCondition *_myHqCondition;
	id<asynclogindelegate> myjyasyncdelegate;
	id<RefreshDelegate> refreshdelegate;
	
	//代码链相关
	short szStockNum;
	short shStockNum;
	short szStockRec;
	short shStockRec;
	NSMutableArray * szStockArray;
	NSMutableArray * shStockArray;
	NSMutableArray * commandArray;
	
	GpdmlInfo * gpdmlInfo;
	NSString * logcachefile;
    
    BOOL  bexitsysflag;
    time_t m_nlastopertime;
    BOOL  m_bpcywflag;
    tradeType tradeType;
    HZFX HZFX;  //担保品划转方向
    int nyybsHT; //eTrade.xml中 Branch里面的 hostType的值,0为登录的 普通交易,1为登录的 融资融券;
    NSMutableArray*	gddmDBPHZ;
    NSMutableArray* DBPHZGDDMArray;
}
@property(nonatomic,assign)tradeType tradeType;
@property(nonatomic,assign)HZFX HZFX;
@property(nonatomic) time_t m_nlastopertime;
@property(nonatomic,retain)NSString *logpath;
@property BOOL bexitsysflag;
@property BOOL initStockChainFlag;
@property BOOL showMineFlag;
@property short b_yesterday;
@property short szStockNum;
@property short shStockNum;
@property short szStockRec;
@property short shStockRec;
@property (nonatomic,retain) NSMutableArray * szStockArray;
@property (nonatomic,retain) NSMutableArray * shStockArray;
@property (nonatomic,retain) GpdmlInfo * gpdmlInfo;
@property short bakFunc;
@property float njylockspan;
@property float refreshTime;
@property float sortRefreshTime;
@property BOOL  theRefreshFLag;
@property BOOL showAlertFlag;
@property BOOL clickAlertFlag;
@property int hourDiff;
@property int minuteDiff;
@property int secondDiff;
@property int yearDiff;
@property int monthDiff;
@property int dayDiff;
@property int sysYMD;
@property float dataSend;
@property float dataRec;
@property float dataSend_3G;
@property float dataRec_3G;
@property  short hostTransferCount;
@property int nyybsHT;

@property(nonatomic,assign) id<asynclogindelegate> myjyasyncdelegate;
@property(nonatomic,assign) id<RefreshDelegate> refreshdelegate;
@property (nonatomic,retain) NSTimer * wtCHBTimer;
@property (nonatomic,retain) NSThread * wtCHBThread;
@property (nonatomic,retain) NSOperationQueue * operationQueue;
@property (nonatomic,retain) NSCondition* dataCondition;
@property (nonatomic,retain) EComm *g_pEComm;
@property (nonatomic,retain) SinHqInfo * currHpAns;
@property (nonatomic,retain) NSMutableArray * codeinfo_data;
@property (nonatomic,retain) NSMutableArray * minute_data;
@property (nonatomic,retain) NSMutableArray * analyse_data;
@property (nonatomic,retain) NSMutableArray * f10title_data;
@property (nonatomic,retain) NSMutableArray * tick_data;
@property (nonatomic,retain) NSString * f10Txt_data;
@property (nonatomic,retain) NSString * info_data;

//交易相关
@property (nonatomic,retain) ETradeComm * g_TradeComm;
@property BOOL tradeLoginFlag;
@property (nonatomic,retain) InputSave * inputSave;
@property (nonatomic,retain) ParseRecv * parseRecv;
@property (nonatomic,retain) NSMutableArray * jjcodeArray;
@property (nonatomic,retain) NSMutableArray * fecxArray;
@property (nonatomic,retain) NSMutableArray * lxfsArray;
@property (nonatomic,retain) NSMutableArray * gddmDBPHZ;
@property (nonatomic,retain) NSMutableArray * DBPHZGDDMArray;
@property (nonatomic,retain) ClientInfo*		clientinfos;
@property (nonatomic,retain) DateSave * saveDate;

//资讯相关
@property (nonatomic,retain)  NSString* currentString;
@property (nonatomic,retain) NSString * currTitleString;
@property (nonatomic,retain) NSString * currTimeString;


//状态相关
@property NetworkStatus netStat;

-(void)setTradeType:(tradeType)tradeType;
-(void)setHZFX:(HZFX)HZFX;
//字符处理
-(NSString *)trim:(NSString *)str;

-(void)SetLog:(NSString *)_theLog;
-(void)handleResult:(NSAlert *)alert withResult:(NSInteger)result;

-(NSMutableDictionary *)getAttributes:(NSString *)_fontName fontSize:(CGFloat)_fontSize theColor:(NSColor *)_theColor theAliment:(int)_theAliment;
-(StockInfo *)searchNextStockInfo:(NSString *)_gpcode gpSetcode:(int)_setcode;
-(StockInfo *)searchPreStockInfo:(NSString *)_gpcode gpSetcode:(int)_setcode;
-(NSString *)searchStockName:(NSString *)_gpcode gpSetcode:(int)_setcode;

-(int)getMinuteFromFZ:(int)xh fzNum:(int)_fznum;
-(int)getTdxMinute:(int)_hours theMinute:(int)_minutes;

-(NSMutableData *) getSoftVerReq;
-(void) getSoftVerAns:(HqResultData * )_hqresult Result:(NSMutableDictionary *)_result;

-(id) initWithComm :(EComm *) theComm tradeComm:(ETradeComm *)theTradeComm;
-(BOOL) testZS:(NSString *)gpcode setcode:(int)setcode;
-(int) getDataPre:(NSString *)gpcode ; 
-(NSMutableData *) getHostBaseDataReq;
-(void) getHostBaseDataAns:(HqResultData * )_hqresult;
-(NSMutableData *) getHostBaseDataReqEx;
-(void) getHostBaseDataAnsEx:(HqResultData * )_hqresult;
-(void) getSearchResult:(NSString *) _theString KeyArray:(NSMutableArray *)_keyArray;
-(int)CustomCompareString:(NSString *)_oriString ComString:(NSString *)_comString;

-(void) getMultiCurrStockDataReq:(int)setDomain coltType:(int)coltType startXH:(int)startxh wantNum:(int)wantnum sortType:(int) sorttype ;
-(NSMutableData *) getMultiCurrStockDataReqEx:(int)setDomain coltType:(int)coltType startXH:(int)startxh wantNum:(int)wantnum sortType:(int) sorttype ;
-(void) getMultiCurrStockDataAsn:(NSMutableArray *) gridData TotalNum:(void *)_totalNum hqResult:(HqResultData * )_hqresult;
-(void) getCurrStockReq : (NSString *) gpcode setcode:(int) setcode;
-(void) getCurrStockAsn;
-(void) getMinuteDataReq : (NSString *) gpcode setcode:(int) setcode;
-(void) getMinuteDataAsn ;
-(NSMutableData *) getHisMinuteDataReq : (NSString *) gpcode setcode:(int) setcode theDate:(int)_ldate;
-(void) getHisMinuteDataAsn :(void *)_pClose dataArray:(NSMutableArray *) ansArray hqResult:(HqResultData * )_hqresult;
-(void) getAnalyseDataReq : (NSString *) gpcode setcode:(int) setcode period:(int)m_period mulNum:(int)mulnum startxh:(int)startxh recNum:(int)num ;
-(void) getAnalyseDataAsn ;
-(NSMutableData *) getF10CFGReq : (NSString *) gpcode setcode:(int) setcode;
-(void) getF10CFGAsn:(HqResultData * )_hqresult;
-(NSMutableData *) getF10CFGReq_ALL : (NSString *) gpcode setcode:(int) setcode;
-(void) getF10CFGAsn_ALL:(HqResultData * )_hqresult DataArray:(NSMutableArray *)_dataArray;
-(NSMutableData *) getF10TxtReq : (NSString *) gpcode setcode:(int) setcode which:(int)which path:(NSString *)path nOffset:(int)nOffset nLength:(int)nLength;
-(NSString *) getF10TxtAsn:(HqResultData * )_hqresult ;
-(NSMutableData *) getF10TxtReqEx : (NSString *) gpcode setcode:(int) setcode which:(int)which path:(NSString *)path nOffset:(int)nOffset nLength:(int)nLength;
-(NSString *) getF10TxtAsnEx:(HqResultData * )_hqresult DataString:(NSString *)_dataString;
-(void) getSCVersionReq : (int) setcode major:(int) _major minor:(int)_minor;
-(void) getSCVersionAsn;
-(void) getStockChainReq : (int) setcode offset:(int) _offset wantnum:(int)_wantNum updatetype:(BOOL)_updateNum;
-(int) getStockChainAsn;
-(NSMutableData *) getAllStockChainReq : (int) setcode offset:(int) _offset wantnum:(int)_wantNum;
-(int) getAllStockChainAsn:(HqResultData * )_hqresult;
-(void) getTickDataReq:(NSString *) gpcode setcode:(int) setcode startx:(int)startx wantnum:(int) num;
-(NSMutableData *) getTickDataReqEx:(NSString *) gpcode setcode:(int) setcode startx:(int)startx wantnum:(int) num;
-(void) getTIckDaraAns:(NSMutableArray *) ansArray hqResult:(HqResultData * )_hqresult;
-(unsigned long) getTIckDaraAnsEx:(NSMutableArray *) ansArray hqResult:(HqResultData * )_hqresult;
-(NSMutableData *) getCombDataReq:(NSString *) gpcode setcode:(int) setcode flags:(int) _flags period:(int)m_period mulNum:(int)mulnum startxh:(int)startxh recNum:(int)num tickStartx:(int)tickStartx tickWantnum:(int) tickNum;
-(NSMutableData *) getCombDataReqEx:(NSString *) gpcode setcode:(int) setcode flags:(int) _flags period:(int)m_period mulNum:(int)mulnum startxh:(int)startxh recNum:(int)num tickStartx:(int)tickStartx tickWantnum:(int) tickNum wParam:(int)_wParam lParam:(int)_lParam;
-(void) getCombDataAns:(HqResultData * )_hqresult Result:(NSMutableDictionary *)_result;
-(NSMutableData *) getCombHQMaskReq:(NSString *) gpcode  flags:(int) _flags wantNum:(short)_num;
-(void) getCombHQMaskAns:(NSMutableArray *) gridData hqResult:(HqResultData * )_hqresult;
-(NSMutableData *) getCombHQReq:(NSString *) gpcode  wantNum:(short)_num;
-(void) getCombHQAns:(NSMutableArray *) gridData hqResult:(HqResultData * )_hqresult;
-(NSMutableData *) getPYXGReq:(NSString *) seachString ;
-(BOOL) getPYXGAns:(HqResultData * )_hqresult Result:(NSMutableDictionary *)_result;

-(NSMutableData *) getInfoTitleDataReq:(short)infoType startx:(int)_startx wantnum:(short) num gpcode:(NSString *) _gpcode setcode:(int) _setcode hyStr:(NSString *)_hyStr flStr:(NSString *)_flStr;
-(void) getInfoTitleDataAns:(HqResultData * )_hqresult Result:(NSMutableDictionary *)_result;
-(NSMutableData *) getInfoTextDataReq:(int)flags startx:(int)_startx wantnum:(short) num fileName:(NSString *)_fileName;
-(void) getInfoTextDataAns:(HqResultData * )_hqresult Result:(NSMutableDictionary *)_result;



//交易
-(void)sendTradePasswordData:(short)nIndex objIndex:(short)windindex Session:(uint64_t)dwEssion OldPassword:(NSString *)_oldPassword  NewPassword:(NSString *)_newPassword;
-(void)sendTradeQueryData:(short)nIndex pageIndex:(short)pageindex objIndex:(short)windindex Session:(uint64_t)dwEssion StartIndex:(int)startindex ReqLines:(int)reqlines TotleLine:(int)totleline  positionstr:(NSString *)posstr;
-(void)setExtendHead:(NSMutableData *) newdata Session:(uint64_t)dwEssion transkey:(unsigned long)dtranskey;
-(void)sendTradeQueryData:(short)nIndex objIndex:(short)windindex Session:(uint64_t)dwEssion;
-(void)sendTradeWTData:(short)nIndex objIndex:(short)windindex Session:(uint64_t)dwEssion gpCode:(NSString*)gpcode gpPrice:(NSString *)gpprice gpNum:(int)gpnum bsFlag:(int)bsflag;
-(void)sendTradeWTData:(short)nIndex objIndex:(short)windindex Session:(uint64_t)dwEssion gpCode:(NSString*)gpcode gpPrice:(NSString *)gpprice gpNum:(int)gpnum bsFlag:(int)bsflag zqflag:(BOOL)bzqflag  wtfs:(int)nwtfs;
-(void)sendTradeWTData:(short)nIndex objIndex:(short)windindex Session:(uint64_t)dwEssion jjCode:(NSString* )jjcode jjGsdm:(NSString*)jjgsdm jjZhdm:(NSString*)jjzhdm WTValue:(NSString *)WTvalue WTNum:(int)WTnum SFFS:(int)sffs SHFS:(int)shfs FHFS:(int)fhfs WTFlag:(int)Wtflag tjr:(NSString *)strtjr;
-(void)sendTradeWTData:(short)nIndex objIndex:(short)windindex Session:(uint64_t)dwEssion jjGsdm:(NSString*)jjgsdm jjzhdm:(NSString*)jjzhdm OutCode:(NSString*)outcode InCode:(NSString*)incode ZhValue:(NSString *)zhValue SHFS:(int)shfs SFFS:(int)sffs;
-(void) sendTradeWTData:(short)nIndex objIndex:(short)windindex Sessiomn:(uint64_t)dwEssion jjCode:(NSString*)jjcode jjGsdm:(NSString*)jjgsdm jjZhdm:(NSString*)jjzhdm WTDate:(NSString*)wtdate WTNumber:(NSString*) wtNumber WTValue:(NSString*)wtValue WTIndex:(NSString*)wtIndex;
-(void) sendTradeWTData:(short)nIndex objIndex:(short)windindex Session:(uint64_t)dwEssion wtArray:(NSMutableArray*)wtArray selectArray:(NSMutableArray*)array;
-(void)sendTradeWTData:(short)nIndex objIndex:(short)windindex Session:(uint64_t)dwEssion gpCode:(NSString *)gpcode gpPrice:(NSString *)gpprice gpNum:(int)gpnum bsFlag:(int)bsflag kyzj:(float)kyzj;
-(void)sendTradeWTData:(short)nIndex objIndex:(short)windindex Session:(uint64_t)dwEssion gpCode:(NSString *)gpcode Wtbhs:(NSString *)wtbh scflags:(NSString *)scflag zhlbs:(NSString *)nzhlb gddms:(NSString *)gddm mmbzs:(NSString *)nmmbz;
-(void) sendTradeWTData:(short)nIndex objIndex:(short)windindex Sessiomn:(uint64_t)dwEssion jjCode:(NSString*)jjcode jjGsdm:(NSString*)jjgsdm jjZhdm:(NSString*)jjzhdm WTBH:(NSString*)wtbh WTLX:(NSString*)lx MYKKRQ:(NSString*)mykkrq KSRQ:(NSString*)ksrq ZZRQ:(NSString *)zzrq JYJE:(NSString *)jyje LSH:(NSString *)lsh QMTJ:(NSString *)qmtj  MODE:(NSString *)kkzqbh WTRQ:(NSString *)wtrq;
-(void)sendTradeWTData:(short)nIndex objIndex:(short)windindex Session:(uint64_t)dwEssion jjCode:(NSString* )jjcode jjGsdm:(NSString*)jjgsdm jjZhdm:(NSString*)jjzhdm WTValue:(NSString *)WTvalue WTNum:(int)WTnum SFFS:(int)sffs SHFS:(int)shfs FHFS:(int)fhfs WTFlag:(int)Wtflag tjr:(NSString *)strtjr xgflag:(BOOL)bxgflag WTRQ:(NSString *)wtrq WTBH:(NSString *)wtbh LSH:(NSString *)lsh;
//处理查询类
-(BOOL) getKHJYInfo:(ParseRecv *)pParsers;
-(BOOL) getReloginInfo:(ParseRecv *)pParsers;
-(BOOL) getGDCXInfo:(ParseRecv *)pParsers;
-(BOOL) getYHXXInfo:(ParseRecv *)pParsers;
-(BOOL) getLXCXInfo:(ParseRecv *)pParsers;
-(BOOL) getCDCXInfo:(NSMutableArray *)showData;
-(BOOL) getGFCXInfoHK:(NSMutableArray *)showData;
-(BOOL) getDRWTInfoHK:(NSMutableArray *)showData;
-(BOOL) getWTCXInfoHK:(NSMutableArray*) showData;
-(BOOL) getCJCXInfoHK:(NSMutableArray*) showData;
-(BOOL) getGFBDInfoHK:(NSMutableArray*) showData;
-(BOOL) getZJLSInfoHK:(NSMutableArray*) showData;
-(BOOL) getIPOLBInfoHK:(NSMutableArray*) showData;
-(BOOL) getIPOPHInfoHK:(NSMutableArray*) showData;
-(BOOL) getJjdmInfo:(ParseRecv *)pParsers;
-(BOOL) getJjZhInfo:(ParseRecv *)pParsers;
-(BOOL) getJjgsInfo:(ParseRecv *)pParsers;
-(BOOL) getLcdmInfo:(ParseRecv *)pParsers;
-(BOOL) getLcZhInfo:(ParseRecv *)pParsers;
-(BOOL) getLcgsInfo:(ParseRecv *)pParsers;
-(void)GetGfcxInfo:(ParseRecv *)pParsers;
-(void)GetFecxInfo2:(ParseRecv *)pParsers;
-(void)GetLcFecxInfo2:(ParseRecv *)pParsers;
-(NSString *) getCXInfo:(ParseRecv *)pParsers withparse2:(ParseRecv *)pParsers2 listdata:(NSMutableArray *)showData withqueryindex:(int)queryindex withrownum:(int *)ntotalline withsucflag:(BOOL *)bsucflag;
-(NSString *) getCXInfo:(ParseRecv *)pParsers listdata:(NSMutableArray *)showData withqueryindex:(int)queryindex withrownum:(int *)ntotalline withsucflag:(BOOL *)bsucflag;
-(NSString *)GetKmsl:(ParseRecv *)pParsers zqdm:(NSString *)zqdm gddm:(NSString *)gddm xwdm:(NSString *)xwdm zjzh:(NSString *)zjzh;


-(NSString *)GetBzStr:(int)nbz;
//存活包
-(void) initCHBThread;
-(void) startSendCHB;
-(void) stopSendCHB;
//银证业务
-(void)sendTradeBankData:(short)nIndex objIndex:(short)windindex Session:(uint64_t)dwEssion SecPassword:(NSString *)secpass TransferType:(int)transtype BankCode:(NSString *)yhdm BankPassword:(NSString *)yhmm MoneyNum:(NSString *)money BankID:(NSString *)yhzh MoneyType:(int)moneyType;
-(unsigned long)makedword:(short)lowvalue high:(short)highvalue;
//加密  压缩
-(void)getEncrypted:(NSMutableData *) theData;
-(NSString *)getDecrypt:(NSMutableData *) theData BodyFlag:(int)flag ;
-(NSString *)getDepress:(NSMutableData *) theData  BodyFlag:(int)flag RawLength:(int) rawLen;


//咨讯
-(void)getInformationTitleData:(NSString *)urlString theData:(NSMutableArray *) infoData;
-(NSString *)getInformationTextData:(NSString *)urlString;
-(void)SetSessionID:(UInt64)usessionid;

//退出交易
-(void)logoutTrade;
-(void)InitClientInfo;
-(void)InitHqInfo;
//查找最快
-(BOOL)FindFastedHqSite;
-(BOOL)FindFastedJySite;
-(void)GetFastedResult;
-(void)GetJySiteConnTime:(NSString *)indexstr;
-(void)doAfterFindBest;
-(void)signallock;
//查客户信息
-(NSString *)GetMachinInfo;
-(NSString *)GetCompileDate;//得到编译日期
-(NSString *)GetIMEI;
//设置股东信息
-(void)setInputSaveInfo;
-(NSString *)GetBzDesc:(NSString *)bzstr;
//流量处理
-(void)readDataLLTJ;
-(void)saveDataLLTJ;
//更换主站
-(void)changeHQHost;
-(void)changeJYHost;
//行情通讯报错
-(void)dealHqTimeout;
-(void)dealNetError;
-(void)dealConnError;
-(void)refreshAllData;
-(short) GetStockType:(short)setcode zqdm:(const char *)Code;
-(float) GetTPPrice:(const char *)Name zqdm:(const char *)Code scflag:(short) setcode withclose:(float)Close withzdflag:(BOOL)bUp withxsflag:(int)xsflag;
//密码
-(void)EncryptJymm:(NSString *)strjymm;
-(NSString *)GetJymmString;
-(void)EncryptauthPass:(NSString *)strauthpass;
-(NSString *)GetauthpassString;
-(void)EncryptReloginSession:(NSString *)strsession;
-(NSString *)GetReloginSessionString;

//信息地雷
-(void)getMineInfo:(NSString *)_gpcode InfoType:(int)_infoType Result:(NSMutableDictionary *)_result HostString:(NSString *)_hostString;
-(NSString *)GetHardUUid;
-(NSString *)GetHardSerial;
-(NSString *)GetGfGddm:(ParseRecv *)pParsers zqdm:(NSString *)zqdm;
-(NSString *)getip;
-(int)GetMemSize;
-(NSString *)GetUserName;
-(NSString *)GetInterNetIp;
-(NSString *)GetIpUrl;
-(int)GetStartIndex;

-(void)sendTradeWTData:(short)nIndex objIndex:(short)windindex Session:(uint64_t)dwEssion yzm:(NSString *)yzmstr;
-(void)SetDesKey:(NSString *)sslkey;
-(void)ResetDesKey;
-(void)sendTradeBankData2:(short)nIndex objIndex:(short)windindex Session:(uint64_t)dwEssion SecPassword:(NSString *)secpass TransferType:(int)transtype BankCode:(NSString *)yhdm BankPassword:(NSString *)yhmm MoneyNum:(NSString *)money BankID:(NSString *)yhzh MoneyType:(int)moneyType czbz:(int)nczbz yhlsh:(NSString *)strlsh;
@end
