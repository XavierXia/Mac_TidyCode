//
//  EGetData.m
//  tdxiphone
//
//  Created by 魏 文敏 on 09-12-29.
//  Copyright 2009 武汉. All rights reserved.
//
NSString * desKey = @"HTTP#$7718#12";
NSString * desIP = @"192.168.4.22";
NSString * infoHost = @"211.139.150.8:7979";
int desPort = 7709;
#import "EGetData.h"
#import "GTMBase64.h"
#include <sys/sysctl.h>
#include <net/if.h>
#include <net/if_dl.h>
#import "macro.h"
#import "AsyncSocket.h"

#define EXTEND_HEAD_LEN 20
#define HOST_TRAN_NUM 3

static char m_compressType =1;
static char m_cEncrypted = 1;
static char m_showtimeout = 1; 
static char m_showneterror = 0; 
static char m_showconnerror = 1; 

@implementation EGetData

@synthesize g_pEComm,currHpAns,minute_data,analyse_data,f10title_data,codeinfo_data,operationQueue;
@synthesize g_TradeComm,tradeLoginFlag,inputSave,parseRecv,wtCHBThread,wtCHBTimer,tick_data,f10Txt_data,info_data,dataCondition;
@synthesize clientinfos,saveDate,jjcodeArray,fecxArray,lxfsArray,currentString,netStat,myjyasyncdelegate,refreshTime,theRefreshFLag;
@synthesize hourDiff,minuteDiff,dataSend ,dataRec,dataSend_3G,dataRec_3G,secondDiff,sysYMD,sortRefreshTime,showAlertFlag;
@synthesize refreshdelegate,clickAlertFlag,hostTransferCount,b_yesterday,showMineFlag,currTitleString,currTimeString,njylockspan;
@synthesize szStockNum,shStockNum,szStockRec,shStockRec,szStockArray,shStockArray,bakFunc,gpdmlInfo,initStockChainFlag;
@synthesize yearDiff,monthDiff,dayDiff,bexitsysflag,m_nlastopertime,tradeType,HZFX;

-(id) initWithComm :(EComm *) theComm tradeComm:(ETradeComm *)theTradeComm{
	if (self = [super init]) {
		
		operationQueue = [[NSOperationQueue alloc] init];
		[operationQueue setMaxConcurrentOperationCount:200];
		dataCondition=  [[NSCondition alloc] init];
		self.hostTransferCount = 0;
		self.hourDiff = 0;
		self.minuteDiff = 0;
		self.secondDiff = 0;
		self.yearDiff = 0;
		self.monthDiff = 0;
		self.dayDiff = 0;
		self.sysYMD =0 ;
		self.dataSend = 0;
		self.dataRec = 0;
		bexitsysflag=NO;
		theRefreshFLag = YES;
		showMineFlag = YES;
		initStockChainFlag = NO;
        self.HZFX = HRXY;
        
		g_pEComm = theComm;
		g_TradeComm = theTradeComm;
		g_TradeComm.mygetDataDelegate=self;
		g_TradeComm.myDelegate=(id)self;
		g_pEComm.mygetDataDelegate=self;
		currHpAns = [[SinHqInfo alloc] init];
		analyse_data = [[NSMutableArray alloc] init];
		minute_data = [[NSMutableArray alloc] init];
		f10title_data = [[NSMutableArray alloc] init];
		tick_data = [[NSMutableArray alloc] init];
        m_nlastopertime=time(NULL);
		tradeLoginFlag = NO;
		inputSave = [[InputSave alloc] init];
		parseRecv = [[ParseRecv alloc] init];
		saveDate = [[DateSave alloc] init];
		jjcodeArray = [[NSMutableArray alloc] init];
		fecxArray = [[NSMutableArray alloc] init];
		lxfsArray = [[NSMutableArray alloc] init];
		const char * pdyKey = [desKey UTF8String];
		setKey(pdyKey, 0);
		
		clientinfos=nil;
		bfindbestjy=NO;
		bfindbesthq=NO;
		_threadCount=0;
		_myCondition = [[NSCondition alloc] init];
		_myHqCondition = [[NSCondition alloc] init];
        
        m_bpcywflag=NO;
     
#ifdef IMAC_GHZQ
        m_bpcywflag=YES;
#endif
#ifdef IMAC_GXZQ
        m_bpcywflag=YES;
#endif
#ifdef IMAC_XNZQ
        m_bpcywflag=YES;
#endif
#ifdef IMAC_HXZQ
        m_bpcywflag=YES;
#endif
#ifdef IMAC_ZTZQ
        m_bpcywflag=YES;
#endif
#ifdef IMAC_GDZQ
        m_bpcywflag=YES;
#endif
#ifdef IMAC_TPY
        m_bpcywflag=YES;
#endif
#ifdef IMAC_PAZQ
        m_bpcywflag=YES;
#endif
		
        NSArray* pathArray = NSSearchPathForDirectoriesInDomains(NSApplicationSupportDirectory, NSUserDomainMask, YES);
		
		int pathLen = [pathArray count];
		//NSLog(@"path number is:%d",pathLen);
		
		NSString* filePath = nil;
        NSString* curuserpath = nil;
		for(int i=0;i<pathLen;i++)
		{
			filePath = [pathArray objectAtIndex:i];
            curuserpath = [pathArray objectAtIndex:i];
			
		}
		//NSLog(@"%@",filePath);
		filePath = [filePath stringByAppendingString:MAC_PATHSTRING];
		//NSLog(@"%@",filePath);
		logpath=[[NSString alloc] initWithFormat:@"%@/log.rtf",filePath];
		
        
		showAlertFlag = NO;
		clickAlertFlag = NO;
		timeArray=[[NSArray alloc]initWithObjects:@"570",@"690",@"780",@"900",@"900",@"900",@"900",@"900",nil];
	
		logcachefile = @"";
		
		commandArray = [[NSMutableArray alloc] init];
		NSDictionary  * myDict;
		//市场
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"1",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"上证A股",@"gpname",@"1",@"sign",@"6004",@"typeid",@"0",@"paraone",@"0",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"2",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"上证B股",@"gpname",@"2",@"sign",@"6004",@"typeid",@"1",@"paraone",@"0",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"3",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"深证A股",@"gpname",@"3",@"sign",@"6004",@"typeid",@"2",@"paraone",@"0",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"4",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"深证B股",@"gpname",@"4",@"sign",@"6004",@"typeid",@"3",@"paraone",@"0",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"5",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"上证债券",@"gpname",@"5",@"sign",@"6004",@"typeid",@"4",@"paraone",@"0",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"6",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"深证债券",@"gpname",@"6",@"sign",@"6004",@"typeid",@"5",@"paraone",@"0",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"7",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"沪深A股",@"gpname",@"7",@"sign",@"6004",@"typeid",@"6",@"paraone",@"0",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"8",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"沪深B股",@"gpname",@"8",@"sign",@"6004",@"typeid",@"7",@"paraone",@"0",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"9",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"中小企业",@"gpname",@"9",@"sign",@"6004",@"typeid",@"12",@"paraone",@"0",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"11",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"沪深权证",@"gpname",@"11",@"sign",@"6004",@"typeid",@"13",@"paraone",@"0",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"12",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"创业板",@"gpname",@"12",@"sign",@"6004",@"typeid",@"14",@"paraone",@"0",@"paratwo",nil];
		[commandArray addObject:myDict];
		
		
		//涨幅排名
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"61",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"沪A涨幅排名",@"gpname",@"61",@"sign",@"6004",@"typeid",@"0",@"paraone",@"14",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"62",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"沪B涨幅排名",@"gpname",@"62",@"sign",@"6004",@"typeid",@"1",@"paraone",@"14",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"63",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"深A涨幅排名",@"gpname",@"63",@"sign",@"6004",@"typeid",@"2",@"paraone",@"14",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"64",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"深B涨幅排名",@"gpname",@"64",@"sign",@"6004",@"typeid",@"3",@"paraone",@"14",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"65",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"沪债涨幅排名",@"gpname",@"65",@"sign",@"6004",@"typeid",@"4",@"paraone",@"14",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"66",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"深债涨幅排名",@"gpname",@"66",@"sign",@"6004",@"typeid",@"5",@"paraone",@"14",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"67",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"沪深A涨幅排名",@"gpname",@"67",@"sign",@"6004",@"typeid",@"6",@"paraone",@"14",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"68",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"沪深B涨幅排名",@"gpname",@"68",@"sign",@"6004",@"typeid",@"7",@"paraone",@"14",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"69",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"中小企业涨幅排名",@"gpname",@"69",@"sign",@"6004",@"typeid",@"12",@"paraone",@"14",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"611",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"沪深权证涨幅排名",@"gpname",@"611",@"sign",@"6004",@"typeid",@"13",@"paraone",@"14",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"612",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"创业板涨幅排名",@"gpname",@"612",@"sign",@"6004",@"typeid",@"14",@"paraone",@"14",@"paratwo",nil];
		[commandArray addObject:myDict];
		//功能
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"10",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"基本资料",@"gpname",@"10",@"sign",@"6006",@"typeid",@"-1",@"paraone",@"-1",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"06",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"自选股",@"gpname",@"06",@"sign",@"6004",@"typeid",@"100",@"paraone",@"0",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"05",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"类型切换",@"gpname",@"05",@"sign",@"6010",@"typeid",@"-1",@"paraone",@"-1",@"paratwo",nil];
		[commandArray addObject:myDict];
		//大盘指数
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"03",@"showcode",@"999999",@"gpcode",@"1",@"setcode",@"上证领先指标",@"gpname",@"03",@"sign",@"6001",@"typeid",@"1",@"paraone",@"-1",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"04",@"showcode",@"399001",@"gpcode",@"0",@"setcode",@"深证领先指标",@"gpname",@"04",@"sign",@"6001",@"typeid",@"1",@"paraone",@"-1",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"300",@"showcode",@"399300",@"gpcode",@"0",@"setcode",@"沪深300走势",@"gpname",@"300",@"sign",@"6001",@"typeid",@"1",@"paraone",@"-1",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"180",@"showcode",@"000010",@"gpcode",@"1",@"setcode",@"上证180走势",@"gpname",@"180",@"sign",@"6001",@"typeid",@"1",@"paraone",@"-1",@"paratwo",nil];
		[commandArray addObject:myDict];
		//指标
		
		//交易
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"21",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"闪电买入",@"gpname",@"21",@"sign",@"6100",@"typeid",@"0",@"paraone",@"－1",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"23",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"闪电卖出",@"gpname",@"23",@"sign",@"6100",@"typeid",@"1",@"paraone",@"－1",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"22",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"委托撤单",@"gpname",@"22",@"sign",@"6104",@"typeid",@"7",@"paraone",@"－1",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"221",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"普通买入",@"gpname",@"221",@"sign",@"6106",@"typeid",@"0",@"paraone",@"－1",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"223",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"普通卖出",@"gpname",@"223",@"sign",@"6106",@"typeid",@"1",@"paraone",@"－1",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"20",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"交易委托",@"gpname",@"20",@"sign",@"6108",@"typeid",@"-1",@"paraone",@"－1",@"paratwo",nil];
		[commandArray addObject:myDict];

		
		//K线周期
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"DAY",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"日线",@"gpname",@"DAY",@"sign",@"6002",@"typeid",@"4",@"paraone",@"－1",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"WEEK",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"周线",@"gpname",@"WEEK",@"sign",@"6002",@"typeid",@"5",@"paraone",@"－1",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"MONTH",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"月线",@"gpname",@"MONTH",@"sign",@"6002",@"typeid",@"6",@"paraone",@"－1",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"M5",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"5分钟线",@"gpname",@"M5",@"sign",@"6002",@"typeid",@"0",@"paraone",@"－1",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"M15",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"15分钟线",@"gpname",@"M15",@"sign",@"6002",@"typeid",@"1",@"paraone",@"－1",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"M30",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"30分钟线",@"gpname",@"M30",@"sign",@"6002",@"typeid",@"2",@"paraone",@"－1",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"M60",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"60分钟线",@"gpname",@"M60",@"sign",@"6002",@"typeid",@"3",@"paraone",@"－1",@"paratwo",nil];
		[commandArray addObject:myDict];
		
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"96",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"日线",@"gpname",@"96",@"sign",@"6002",@"typeid",@"4",@"paraone",@"－1",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"97",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"周线",@"gpname",@"97",@"sign",@"6002",@"typeid",@"5",@"paraone",@"－1",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"98",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"月线",@"gpname",@"98",@"sign",@"6002",@"typeid",@"6",@"paraone",@"－1",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"92",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"5分钟线",@"gpname",@"92",@"sign",@"6002",@"typeid",@"0",@"paraone",@"－1",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"93",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"15分钟线",@"gpname",@"93",@"sign",@"6002",@"typeid",@"1",@"paraone",@"－1",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"94",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"30分钟线",@"gpname",@"94",@"sign",@"6002",@"typeid",@"2",@"paraone",@"－1",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"95",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"60分钟线",@"gpname",@"95",@"sign",@"6002",@"typeid",@"3",@"paraone",@"－1",@"paratwo",nil];
		[commandArray addObject:myDict];
		
		//K线指标
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"MACD",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"平滑异同平均",@"gpname",@"MACD",@"sign",@"6002",@"typeid",@"-1",@"paraone",@"0",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"KDJ",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"经典版KDJ",@"gpname",@"KDJ",@"sign",@"6002",@"typeid",@"-1",@"paraone",@"1",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"RSI",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"相对强弱指标",@"gpname",@"RSI",@"sign",@"6002",@"typeid",@"-1",@"paraone",@"2",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"BIAS",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"乖离率",@"gpname",@"BIAS",@"sign",@"6002",@"typeid",@"-1",@"paraone",@"3",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"DMA",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"平均差",@"gpname",@"DMA",@"sign",@"6002",@"typeid",@"-1",@"paraone",@"4",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"OBV",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"积累能量线",@"gpname",@"OBV",@"sign",@"6002",@"typeid",@"-1",@"paraone",@"5",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"ROC",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"变动率指标",@"gpname",@"ROC",@"sign",@"6002",@"typeid",@"-1",@"paraone",@"6",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"MTM",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"动量线",@"gpname",@"MTM",@"sign",@"6002",@"typeid",@"-1",@"paraone",@"7",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"CR",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"带状能量线",@"gpname",@"CR",@"sign",@"6002",@"typeid",@"-1",@"paraone",@"8",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"DMI",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"趋向指标",@"gpname",@"DMI",@"sign",@"6002",@"typeid",@"-1",@"paraone",@"9",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"BRAR",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"情绪指标",@"gpname",@"BRAR",@"sign",@"6002",@"typeid",@"-1",@"paraone",@"10",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"VR",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"成交量变动率",@"gpname",@"VR",@"sign",@"6002",@"typeid",@"-1",@"paraone",@"11",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"TRIX",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"三重指数平均线",@"gpname",@"TRIX",@"sign",@"6002",@"typeid",@"-1",@"paraone",@"12",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"EMV",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"简易波动指标",@"gpname",@"EMV",@"sign",@"6002",@"typeid",@"-1",@"paraone",@"13",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"WR",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"威廉指标",@"gpname",@"WR",@"sign",@"6002",@"typeid",@"-1",@"paraone",@"14",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"CCI",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"商品路径指标",@"gpname",@"CCI",@"sign",@"6002",@"typeid",@"-1",@"paraone",@"15",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"PSY",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"心理线",@"gpname",@"PSY",@"sign",@"6002",@"typeid",@"-1",@"paraone",@"16",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"DPO",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"区间震荡线",@"gpname",@"DPO",@"sign",@"6002",@"typeid",@"-1",@"paraone",@"17",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"BOLL",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"布林线",@"gpname",@"BOLL",@"sign",@"6002",@"typeid",@"-1",@"paraone",@"18",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"ASI",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"振动升降指标",@"gpname",@"ASI",@"sign",@"6002",@"typeid",@"-1",@"paraone",@"19",@"paratwo",nil];
		[commandArray addObject:myDict];
		myDict = [NSDictionary dictionaryWithObjectsAndKeys:@"SAR",@"showcode",@"",@"gpcode",@"-1",@"setcode",@"抛物线指标",@"gpname",@"SAR",@"sign",@"6002",@"typeid",@"-1",@"paraone",@"20",@"paratwo",nil];
		[commandArray addObject:myDict];
		
		gpdmlInfo = [[GpdmlInfo alloc] init];
	}	
	return self;
}

- (void) dealloc
{
	[gpdmlInfo release];
	[szStockArray release];
	[shStockArray release];
	[commandArray release];
	
	
	[timeArray release];
	[wtCHBTimer release];
	[wtCHBThread release];
	[operationQueue release];
	[parseRecv release];
	[inputSave release];
	[saveDate release];
	[analyse_data release];
	[minute_data release];
	[f10title_data release];
	[f10Txt_data release];
	[tick_data release];
	[g_pEComm release];
	[g_TradeComm release];
	[currHpAns release];
	[codeinfo_data release];
	[info_data release];
	[dataCondition release];
	[jjcodeArray release];
	[fecxArray release];
	//交易相关
	
	[clientinfos release];
	[wtCHBTimer release];
	
	[xmlData release];
	[contentArray release];
	[currentString release];
	[_myCondition release];
    [logpath release];
	[super dealloc];
}

#pragma mark imac attributes相关
-(NSMutableDictionary *)getAttributes:(NSString *)_fontName fontSize:(CGFloat)_fontSize theColor:(NSColor *)_theColor theAliment:(int)_theAliment{
	NSMutableDictionary * attributes = [[NSMutableDictionary alloc] init] ;
	
	NSMutableParagraphStyle * tempStyle = [[NSMutableParagraphStyle alloc]init] ;
	[tempStyle setLineBreakMode:NSLineBreakByTruncatingTail];
	[tempStyle setAlignment:_theAliment];
	
	[attributes setObject:[NSFont systemFontOfSize:_fontSize] forKey:NSFontAttributeName];
	[attributes setObject:_theColor forKey:NSForegroundColorAttributeName];
	[attributes setObject:tempStyle forKey:NSParagraphStyleAttributeName];
	[tempStyle release];
	return [attributes autorelease];
}

-(StockInfo *)searchNextStockInfo:(NSString *)_gpcode gpSetcode:(int)_setcode{
	int i;
	int j;
	StockInfo * tempInfo;
	if (_setcode == 0) {
		for (i=0;i<szStockNum; i++) {
			tempInfo = [szStockArray objectAtIndex:i];
			if ([tempInfo.gpcode isEqualToString:_gpcode] && tempInfo.setcode == _setcode) {
				j = i+1;
				if (j == szStockNum) {
					j=0;
				}
				return [szStockArray objectAtIndex:j];
			}
		}
	}
	else if(_setcode  == 1){
		for (i=0;i<shStockNum ; i++) {
			tempInfo = [shStockArray objectAtIndex:i];
			if ([tempInfo.gpcode isEqualToString:_gpcode] && tempInfo.setcode == _setcode) {
				j = i+1;
				if (j == shStockNum) {
					j=0;
				}
				return [shStockArray objectAtIndex:j];
			}
		}
		
	}
	
	return nil;
}
-(StockInfo *)searchPreStockInfo:(NSString *)_gpcode gpSetcode:(int)_setcode{
	int i;
	int j;
	StockInfo * tempInfo;
	if (_setcode == 0) {
		for (i=0;i<szStockNum ; i++) {
			tempInfo = [szStockArray objectAtIndex:i];
			if ([tempInfo.gpcode isEqualToString:_gpcode] && tempInfo.setcode == _setcode) {
				j = i-1;
				if (j <0 ) {
					j = szStockNum - 1;
				}
				return [szStockArray objectAtIndex:j];
			}
		}
	}
	else if(_setcode  == 1){
		for (i=0;i<shStockNum ; i++) {
			tempInfo = [shStockArray objectAtIndex:i];
			if ([tempInfo.gpcode isEqualToString:_gpcode] && tempInfo.setcode == _setcode) {
				j = i-1;
				if (j < 0) {
					j= shStockNum -1;
				}
				return [shStockArray objectAtIndex:j];
			}
		}
		
	}
	return nil;
}


-(NSString *)searchStockName:(NSString *)_gpcode gpSetcode:(int)_setcode{
	int i;
	StockInfo * tempInfo;
	for (i=0;i<szStockNum ; i++) {
		tempInfo = [szStockArray objectAtIndex:i];
		if ([tempInfo.gpcode isEqualToString:_gpcode] && tempInfo.setcode == _setcode) {
			return tempInfo.gpname;
		}
	}
	for (i=0;i<shStockNum ; i++) {
		tempInfo = [shStockArray objectAtIndex:i];
		if ([tempInfo.gpcode isEqualToString:_gpcode] && tempInfo.setcode == _setcode) {
			return tempInfo.gpname;
		}
	}
	return @"";
}

#pragma mark 字符处理相关
-(NSString *)trim:(NSString *)str{
	if(str && [str length] > 0){
		NSData * tempData = [str dataUsingEncoding:NSUTF8StringEncoding];
		char rawChar[[tempData length]];
		int i;
		memcpy(rawChar, [tempData bytes], [tempData length]);
		for (i = 0; i<[tempData length];i++) {
			if (rawChar[i] == '\0') {
				break;
			}
		}
		//NSLog(@"%i",i);
		return [[[NSString alloc] initWithData:[tempData subdataWithRange:NSMakeRange(0, i)] encoding:CFStringConvertEncodingToNSStringEncoding (kCFStringEncodingGB_18030_2000)] autorelease];
	}
	return @"";
	
}

#pragma mark 定时更新相关
-(int)getTdxMinute:(int)_hours theMinute:(int)_minutes{
	int m_num =  _hours * 60 + _minutes;
	int itemnum=0;
    if ([timeArray count] && m_num <= [[timeArray objectAtIndex:0] intValue]) {
		itemnum = 1;
	} else if ([timeArray count]>1 && m_num < [[timeArray objectAtIndex:1] intValue]) {
		itemnum = m_num - [[timeArray objectAtIndex:0] intValue] + 1;
	} else if ([timeArray count]>2 && m_num < [[timeArray objectAtIndex:2] intValue]) {
		itemnum = [[timeArray objectAtIndex:1] intValue] - [[timeArray objectAtIndex:0] intValue];
	} else if ([timeArray count]>3 && m_num < [[timeArray objectAtIndex:3] intValue]) {
		itemnum = m_num - [[timeArray objectAtIndex:2] intValue] + 1 + ([[timeArray objectAtIndex:1] intValue] - [[timeArray objectAtIndex:0] intValue]);
	} else if ([timeArray count]>4 && m_num < [[timeArray objectAtIndex:4] intValue]) {
		itemnum = [[timeArray objectAtIndex:3] intValue] - [[timeArray objectAtIndex:2] intValue] + ([[timeArray objectAtIndex:1] intValue] - [[timeArray objectAtIndex:0] intValue]);
	} else if ([timeArray count]>5 && m_num < [[timeArray objectAtIndex:5] intValue]) {
		itemnum = m_num - [[timeArray objectAtIndex:4] intValue] + 1 + ([[timeArray objectAtIndex:3] intValue] - [[timeArray objectAtIndex:2] intValue]) + ([[timeArray objectAtIndex:1] intValue] - [[timeArray objectAtIndex:0] intValue]);
	} else if ([timeArray count]>6 && m_num < [[timeArray objectAtIndex:6] intValue]) {
		itemnum = [[timeArray objectAtIndex:5] intValue] - [[timeArray objectAtIndex:4] intValue] + ([[timeArray objectAtIndex:3] intValue] - [[timeArray objectAtIndex:2] intValue]) + ([[timeArray objectAtIndex:1] intValue] - [[timeArray objectAtIndex:0] intValue]);
	} else if ([timeArray count]>7 && m_num < [[timeArray objectAtIndex:7] intValue]) {
		itemnum = m_num - [[timeArray objectAtIndex:6] intValue] + 1 + ([[timeArray objectAtIndex:5] intValue] - [[timeArray objectAtIndex:4] intValue]) + ([[timeArray objectAtIndex:3] intValue] - [[timeArray objectAtIndex:2] intValue]) +
		([[timeArray objectAtIndex:1] intValue] - [[timeArray objectAtIndex:0] intValue]);
	} else if([timeArray count]>7){
		itemnum = [[timeArray objectAtIndex:7] intValue] - [[timeArray objectAtIndex:6] intValue] + ([[timeArray objectAtIndex:5] intValue] - [[timeArray objectAtIndex:4] intValue]) + ([[timeArray objectAtIndex:3] intValue] - [[timeArray objectAtIndex:2] intValue]) +
		([[timeArray objectAtIndex:1] intValue] - [[timeArray objectAtIndex:0] intValue]);
	}
	return itemnum;
}
-(int)getMinuteFromFZ:(int)xh fzNum:(int)_fznum{
	int i ;
    if([timeArray count]<=0)
    {
        return 0;
    }
	i = [[timeArray objectAtIndex:0] intValue] + (xh + 1) * _fznum;
	if ([timeArray count]>2 && i >= [[timeArray objectAtIndex:1] intValue]) {
		i += [[timeArray objectAtIndex:2] intValue] - [[timeArray objectAtIndex:1] intValue];
	}
	if ([timeArray count]>4 && i >= [[timeArray objectAtIndex:3] intValue]) {
		i += [[timeArray objectAtIndex:4] intValue] - [[timeArray objectAtIndex:3] intValue];
	}
	if ([timeArray count]>6 && i >= [[timeArray objectAtIndex:5] intValue]) {
		i += [[timeArray objectAtIndex:6] intValue] - [[timeArray objectAtIndex:5] intValue];
	}
	if ([timeArray count]>7 && i >= [[timeArray objectAtIndex:7] intValue]) {
		i = [[timeArray objectAtIndex:7] intValue];
	}
	return i;
}

#pragma mark delegate相关
-(void)SetCHBSessionID:(UInt64)usessionid
{
	[self SetSessionID:usessionid];
}

-(TradeSite *)GetJyLoginSite:(BOOL)blastflag
{
	if(clientinfos.localjysites.tradesites==nil)
		return nil;
	if([clientinfos.localjysites.tradesites count]<=0)
		return nil;
	if([clientinfos.localjysites.tradesites count]==1)
	{
		clientinfos.localjysites.nlastindex=0;
        LogIt2(2)
        return [clientinfos.localjysites.tradesites objectAtIndex:0];
	}
	if(clientinfos.localjysites.bfindbest && blastflag==NO)
	{
		
	}
	else 
	{
        LogIt2(21)
		if(clientinfos.localjysites.nlastindex>=0 && clientinfos.localjysites.nlastindex<[clientinfos.localjysites.tradesites count])
        {
            LogIt2(22)
            return [clientinfos.localjysites.tradesites objectAtIndex:clientinfos.localjysites.nlastindex];
        }
        else
        {
            clientinfos.localjysites.nlastindex=0;
            LogIt2(3)
            if([clientinfos.localjysites.tradesites count])
                return [clientinfos.localjysites.tradesites objectAtIndex:clientinfos.localjysites.nlastindex];
        }
	}
	return nil;
}

-(TradeSite *)GetHqLoginSite:(BOOL)blastflag
{
	if(clientinfos.localhqsites.tradesites==nil)
		return nil;
	if([clientinfos.localhqsites.tradesites count]<=0)
		return nil;
	if([clientinfos.localhqsites.tradesites count]==1)
	{
		clientinfos.localhqsites.nlastindex=0;
		return [clientinfos.localhqsites.tradesites objectAtIndex:0];
	}
	if(clientinfos.localhqsites.bfindbest && blastflag==NO)
	{
		
	}
	else 
	{
		if(clientinfos.localhqsites.nlastindex>=0 && clientinfos.localhqsites.nlastindex<[clientinfos.localhqsites.tradesites count])
			return [clientinfos.localhqsites.tradesites objectAtIndex:clientinfos.localhqsites.nlastindex];
        else
        {
            clientinfos.localhqsites.nlastindex=0;
            if([clientinfos.localhqsites.tradesites count])
                return [clientinfos.localhqsites.tradesites objectAtIndex:0];
        }
	}
	return nil;
}

-(BOOL)IsNetWorkOk
{
	if(netStat==NotReachable)
		return NO;
	return YES;
}

-(BOOL)IsJyLocking
{
	return clientinfos.m_blocking;
}


-(TradeSite *)getNextHqLoginSite{
	if ([self.clientinfos.localhqsites.tradesites count] <= 1) {
		return nil;
	}
	int tempInt,nextindex;
	tempInt=self.clientinfos.localhqsites.nlastindex;
	nextindex=tempInt+1;
	if(nextindex>=[self.clientinfos.localhqsites.tradesites count])
		nextindex=0;
	return [self.clientinfos.localhqsites.tradesites objectAtIndex:nextindex];
}
-(void)dealChangeNextHqSite{
	if ([self.clientinfos.localhqsites.tradesites count] <= 1) {
		return;
	}
	int tempInt,nextindex;
	tempInt=self.clientinfos.localhqsites.nlastindex;
	nextindex=tempInt+1;
	if(nextindex>=[self.clientinfos.localhqsites.tradesites count])
		nextindex=0;
	
	
	self.clientinfos.localhqsites.nlastindex = nextindex;
	[self.clientinfos.caches SaveLocalHqSite:self.clientinfos.localhqsites];
	[self changeHQHost];
	[g_pEComm sendnextreq];
	
}

-(void)writeLog:(NSString *)_log{
	[self SetLog:_log];
}


-(int)getHourDiff{
	return hourDiff;
}
-(int)getMinuteDiff{
	return minuteDiff;
}
-(int)getSecondDiff{
	return secondDiff;
}

-(BOOL)IsHttpProxyWork{
	return self.clientinfos.httpProxyInfo.beUsedFlag;
}
-(NSString *)getHttpProxyAddress{
	return self.clientinfos.httpProxyInfo.httpProxyAddress;
}
-(NSString *)getHttpProxyPort{
	return self.clientinfos.httpProxyInfo.httpProxyPort;
}
-(NSString *)getHttpProxyUsername{
	return self.clientinfos.httpProxyInfo.httpProxyUsername;
}
-(NSString *)getHttpProxyPassword{
	return self.clientinfos.httpProxyInfo.httpProxyPassword;
}

#pragma mark 行情协议
-(void) getTest{
	NSMutableData *newdata = [[NSMutableData alloc] init];
	short  req = STKVERSION_NREQ;
	[newdata appendBytes:(void *)&req length:sizeof(short)];
	
	
	[g_pEComm sendIt:newdata length:[newdata length]];
	[newdata release];
	
}


-(NSMutableData *) getSoftVerReq{
	NSMutableData *newdata = [[[NSMutableData alloc] init] autorelease];
	short  req = SOFTVER_NREQ;
	short  tempShort = 4;
	[newdata appendBytes:(void *)&req length:sizeof(short)];	
	[newdata appendBytes:(void *)&tempShort length:sizeof(short)];	
	[newdata appendBytes:(void *)&tempShort length:sizeof(short)];	
	[newdata appendBytes:(void *)&tempShort length:sizeof(short)];	
	
	return newdata;
}
-(void) getSoftVerAns:(HqResultData * )_hqresult Result:(NSMutableDictionary *)_result{
	NSData * theData = [[NSData alloc] initWithData:_hqresult.resultData];
	
	[_result setObject:[NSString stringWithFormat:@"%i",_hqresult.resultStat] forKey:@"RESULTSTAT"];
	
	int nf = 16;
	short majorVer=0,minorVer=0;
	char tempChar=0;
	
	[theData getTdxBytes:&majorVer range:NSMakeRange(nf, sizeof(short))];
	
	[_result setObject:[NSString stringWithFormat:@"%i",majorVer] forKey:@"MAJORVER"];
	
	nf += sizeof(short);
	
	[theData getTdxBytes:&minorVer range:NSMakeRange(nf, sizeof(short))];
	
	[_result setObject:[NSString stringWithFormat:@"%i",minorVer] forKey:@"MINORVER"];
	
	nf += sizeof(short);
	
	[theData getTdxBytes:&tempChar range:NSMakeRange(nf, sizeof(char))];
	[_result setObject:[NSString stringWithFormat:@"%i",tempChar] forKey:@"QUITFLAG"];
	[theData release];
}

-(NSMutableData *) getHostBaseDataReq{
	NSMutableData *newdata = [[[NSMutableData alloc] init] autorelease];
	short  req = HOSTINFO_NREQ;
	char tempChar = 8;
	NSString * tempString = @"123456";
	int tempInt =  4000;
	[newdata appendBytes:(void *)&req length:sizeof(short)];	
	[newdata appendBytes:(void *)&tempChar length:sizeof(char)];
	[newdata appendBytes:(void *)&tempString length:11];
	[newdata appendBytes:(void *)&tempInt length:sizeof(int)];
	[newdata appendBytes:(void *)&tempInt length:sizeof(int)];
	

	return newdata;
}
-(void) getHostBaseDataAns:(HqResultData * )_hqresult{
	NSData * theData = [[NSData alloc] initWithData:_hqresult.resultData];
	
	int nf = 16;
	nf +=5;
	int tempInt=0,tempMinute=0,tempSec=0;
	[theData getTdxBytes:&tempInt range:NSMakeRange(nf, sizeof(int))];
	sysYMD = tempInt;
	nf += 4;
	[theData getTdxBytes:&tempInt range:NSMakeRange(nf, sizeof(int))];
	nf +=4;
	char tempChar;
	[theData getTdxBytes:&tempChar range:NSMakeRange(nf, sizeof(char))];
	
	self.b_yesterday = tempChar;

	
	NSDateFormatter *dateFormatter=[[[NSDateFormatter alloc] init]autorelease]; 
	[dateFormatter setDateFormat:@"HH-mm-ss"];
	NSString * localTime = [dateFormatter stringFromDate:[NSDate date]];
	NSArray * tempArray = [localTime componentsSeparatedByString:@"-"];
	
    if([tempArray count]<2)
    {
        self.hourDiff = 0;
        self.minuteDiff = 0;
        self.secondDiff = 0;
    }
    else
    {
        self.hourDiff = tempInt / 10000  - [[tempArray objectAtIndex:0]intValue];
        tempMinute = tempInt % 10000;
        self.minuteDiff = tempMinute/100 - [[tempArray objectAtIndex:1]intValue];
        tempSec = tempMinute % 100;
        self.secondDiff = tempSec - [[tempArray objectAtIndex:2]intValue];
    }
	
	
	
	
	[theData release];
}


-(NSMutableData *) getHostBaseDataReqEx{
	NSMutableData *newdata = [[[NSMutableData alloc] init] autorelease];
	short  req = HOSTINFO_ORI;
	char tempChar = 8;
	NSString * tempString = @"123456";
	int tempInt =  4000;
	[newdata appendBytes:(void *)&req length:sizeof(short)];	
	[newdata appendBytes:(void *)&tempChar length:sizeof(char)];
	[newdata appendBytes:(void *)&tempString length:11];
	[newdata appendBytes:(void *)&tempInt length:sizeof(int)];
	[newdata appendBytes:(void *)&tempInt length:sizeof(int)];
	
	return newdata;
	
}
-(void) getHostBaseDataAnsEx:(HqResultData * )_hqresult{
	NSData * theData = [[NSData alloc] initWithData:_hqresult.resultData];
	
	int nf = 16;
	nf +=5;
	int tempInt=0,tempMinute=0,tempSec=0;
	[theData getTdxBytes:&tempInt range:NSMakeRange(nf, sizeof(int))];
	sysYMD = tempInt;
	nf += 4;
	[theData getTdxBytes:&tempInt range:NSMakeRange(nf, sizeof(int))];
	nf +=4;
	
	nf+=32;
	char tempChar=0;
	[theData getTdxBytes:&tempChar range:NSMakeRange(nf, sizeof(char))];
	
	self.b_yesterday = tempChar;
	
	
	NSDateFormatter *dateFormatter=[[[NSDateFormatter alloc] init]autorelease]; 
	[dateFormatter setDateFormat:@"YYYY-MM-dd-HH-mm-ss"];
	NSString * localTime = [dateFormatter stringFromDate:[NSDate date]];
	NSArray * tempArray = [localTime componentsSeparatedByString:@"-"];
    
	int tempDate = sysYMD;
	int tempMonth,tempDay;
    if([tempArray count]<5)
    {
        self.yearDiff = 0;
        self.monthDiff = 0;
        self.dayDiff = 0;
        
        self.hourDiff = 0;
        self.minuteDiff =0;
        self.secondDiff = 0;
    }
    else
    {
        self.yearDiff = tempDate / 10000 - [[tempArray objectAtIndex:0]intValue];
        tempMonth = tempDate%10000;
        self.monthDiff = tempMonth/100 - [[tempArray objectAtIndex:1]intValue];
        tempDay = tempMonth%100;
        self.dayDiff = tempDay -[[tempArray objectAtIndex:2]intValue];
        
        
        self.hourDiff = tempInt / 10000  - [[tempArray objectAtIndex:3]intValue];
        tempMinute = tempInt % 10000;
        self.minuteDiff = tempMinute/100 - [[tempArray objectAtIndex:4]intValue];
        tempSec = tempMinute % 100;
        self.secondDiff = tempSec - [[tempArray objectAtIndex:5]intValue];
    }
	
	
	nf+=18;
	
	short tempShort=0;
	[theData getTdxBytes:&tempShort range:NSMakeRange(nf, sizeof(short))];
	self.szStockNum = tempShort;
	nf+=2;
	[theData getTdxBytes:&tempShort range:NSMakeRange(nf, sizeof(short))];
	self.shStockNum = tempShort;
	
	self.szStockRec = 0;
	self.shStockRec = 0;
	
	szStockArray = [[NSMutableArray alloc] initWithCapacity:szStockNum+1];
	shStockArray = [[NSMutableArray alloc] initWithCapacity:shStockNum+1];
	
	[theData release];
}


-(NSMutableData *) getAllStockChainReq : (int) setcode offset:(int) _offset wantnum:(int)_wantNum{
	NSMutableData *newdata = [[[NSMutableData alloc] init] autorelease];
	short  req = STOCKCHAIN_ORI;

	[newdata appendBytes:(void *)&req length:sizeof(short)];	
	[newdata appendBytes:(void *)&setcode length:sizeof(short)];
	[newdata appendBytes:(void *)&_offset length:sizeof(short)];
	[newdata appendBytes:(void *)&_wantNum length:sizeof(short)];
	
	return newdata;
	
}
-(int) getAllStockChainAsn:(HqResultData * )_hqresult{
	NSData * theData = [[NSData alloc] initWithData:_hqresult.resultData];
	
	int nf = 16;

	short num=0 ;
	[theData getTdxBytes:&num range:NSMakeRange(nf, sizeof(short))];
	nf += sizeof(short);
	
	for (int i =0 ; i<num; i++) {
		StockInfo * tempInfo = [[StockInfo alloc] init];
		
		short tempShort=0;
		NSString * tempString;
		[theData getTdxBytes:&tempShort range:NSMakeRange(nf, sizeof(short))];
		tempInfo.setcode = tempShort;
		
		nf += sizeof(short);
		
		tempString = [[NSString alloc] initWithData:[theData subdataWithRange:NSMakeRange(nf, 6)] encoding:NSUTF8StringEncoding];
		tempInfo.gpcode = tempString;
		[tempString release];
		
		nf += 6;
		nf += 2;
		tempString = [[NSString alloc] initWithData:[theData subdataWithRange:NSMakeRange(nf, 8)] encoding:CFStringConvertEncodingToNSStringEncoding (kCFStringEncodingGB_18030_2000)];
		tempInfo.gpname = tempString;
		[tempString release];
		
		nf += 8;
		nf +=8;
		tempString = [[NSString alloc] initWithData:[theData subdataWithRange:NSMakeRange(nf, 4)] encoding:NSUTF8StringEncoding];
		tempInfo.gpspell = tempString;
		[tempString release];
		
		nf +=4;
		
		if (tempInfo.setcode > 0) {
			[self.shStockArray addObject:tempInfo];
		}
		else {
			[self.szStockArray addObject:tempInfo];
		}

		[tempInfo release];
	}
	
	[theData release];
	return num;
}

-(void) getSearchResult:(NSString *) _theString KeyArray:(NSMutableArray *)_keyArray{
	NSString * tempString;
	tempString = [_theString substringWithRange:NSMakeRange(0, 1)];
	NSData * tempData = [tempString dataUsingEncoding:NSUTF8StringEncoding];
	
	short tempShort =0 ;
	[tempData getTdxBytes:&tempShort range:NSMakeRange(0, sizeof(char))];
	
	
	int j = 0;
	int i ;
	StockInfo * tempInfo;
	ProcessInfo * ansInfo;
	//先查找命令和指标
	for (i=0; i<[commandArray count]; i++) {
		NSDictionary * tempDict = [commandArray objectAtIndex:i];
		
		if ([[tempDict objectForKey:@"sign"] compare:_theString options:NSCaseInsensitiveSearch range:NSMakeRange(0, [_theString length])]== NSOrderedSame) {
			ansInfo = [[ProcessInfo alloc]init];
			ansInfo.showcode = [NSString stringWithFormat:@"%@",[tempDict objectForKey:@"showcode"]];
			ansInfo.gpcode = [NSString stringWithFormat:@"%@",[tempDict objectForKey:@"gpcode"]];
			ansInfo.gpname = [NSString stringWithFormat:@"%@",[tempDict objectForKey:@"gpname"]];
			ansInfo.setcode = [[tempDict objectForKey:@"setcode"] intValue];
			ansInfo.typeID = [[tempDict objectForKey:@"typeid"] intValue];
			ansInfo.paraOne = [[tempDict objectForKey:@"paraone"] intValue];
			ansInfo.paraTwo = [[tempDict objectForKey:@"paratwo"] intValue];
			
			[_keyArray addObject:ansInfo];
			[ansInfo release];
			j++;
			if (j == STOCKCHAIN_ANSNUM) {
				return;
			}
		
		}
		
		
	}
	//再查找代码链
	if (tempShort >= 48 && tempShort <= 57) {
		for (i = 0; i < self.szStockNum && i<[szStockArray count]; i++) {
			tempInfo = [szStockArray objectAtIndex:i];
			if (([tempInfo.gpcode compare:_theString options:NSCaseInsensitiveSearch range:NSMakeRange(0, [_theString length])]== NSOrderedSame)||(([tempInfo.gpcode rangeOfString:_theString].location!=NSNotFound) && ([tempInfo.gpcode rangeOfString:_theString].length == [_theString length]))){

				ansInfo = [[ProcessInfo alloc]init];
				ansInfo.showcode = [NSString stringWithFormat:@"%@",tempInfo.gpcode];
				ansInfo.gpcode = [NSString stringWithFormat:@"%@",tempInfo.gpcode];
				ansInfo.gpname = [NSString stringWithFormat:@"%@",tempInfo.gpname];
				ansInfo.setcode = tempInfo.setcode;
				ansInfo.typeID = MAC_ZST_FUNC;
				ansInfo.paraOne = -1;
				ansInfo.paraTwo = -1;
				
				
				[_keyArray addObject:ansInfo];
				[ansInfo release];
				j++;
				if (j == STOCKCHAIN_ANSNUM) {
					return;
				}
			}
			
		}
		
		for (i = 0; i < self.shStockNum && i<[shStockArray count]; i++) {
			tempInfo = [shStockArray objectAtIndex:i];
			if (([tempInfo.gpcode compare:_theString options:NSCaseInsensitiveSearch range:NSMakeRange(0, [_theString length])]== NSOrderedSame)||(([tempInfo.gpcode rangeOfString:_theString].location!=NSNotFound) && ([tempInfo.gpcode rangeOfString:_theString].length == [_theString length]))){
				ansInfo = [[ProcessInfo alloc]init];
				ansInfo.showcode = [NSString stringWithFormat:@"%@",tempInfo.gpcode];
				ansInfo.gpcode = [NSString stringWithFormat:@"%@",tempInfo.gpcode];
				ansInfo.gpname = [NSString stringWithFormat:@"%@",tempInfo.gpname];
				ansInfo.setcode = tempInfo.setcode;
				ansInfo.typeID = MAC_ZST_FUNC;
				ansInfo.paraOne = -1;
				ansInfo.paraTwo = -1;
				
				
				[_keyArray addObject:ansInfo];
				[ansInfo release];
				j++;
				if (j == STOCKCHAIN_ANSNUM) {
					return;
				}
			}
			
		}
	}
	else if(tempShort > 64 && tempShort < 91){
		for (i = 0; i < self.szStockNum && i<[szStockArray count]; i++) {
			tempInfo = [szStockArray objectAtIndex:i];
        	if ([self CustomCompareString:_theString ComString:tempInfo.gpspell] >0) {
				ansInfo = [[ProcessInfo alloc]init];
				ansInfo.showcode = [NSString stringWithFormat:@"%@",tempInfo.gpcode];
				ansInfo.gpcode = [NSString stringWithFormat:@"%@",tempInfo.gpcode];
				ansInfo.gpname = [NSString stringWithFormat:@"%@",tempInfo.gpname];
				ansInfo.setcode = tempInfo.setcode;
				ansInfo.typeID = MAC_ZST_FUNC;
				ansInfo.paraOne = -1;
				ansInfo.paraTwo = -1;
				
				
				[_keyArray addObject:ansInfo];
				[ansInfo release];
				j++;
				if (j == STOCKCHAIN_ANSNUM) {
					return;
				}
			}
			
		}
		
		for (i = 0; i < self.shStockNum && i<[shStockArray count]; i++) {
			tempInfo = [shStockArray objectAtIndex:i];
			if ([self CustomCompareString:_theString ComString:tempInfo.gpspell] >0) {
				ansInfo = [[ProcessInfo alloc]init];
				ansInfo.showcode = [NSString stringWithFormat:@"%@",tempInfo.gpcode];
				ansInfo.gpcode = [NSString stringWithFormat:@"%@",tempInfo.gpcode];
				ansInfo.gpname = [NSString stringWithFormat:@"%@",tempInfo.gpname];
				ansInfo.setcode = tempInfo.setcode;
				ansInfo.typeID = MAC_ZST_FUNC;
				ansInfo.paraOne = -1;
				ansInfo.paraTwo = -1;
				
				
				[_keyArray addObject:ansInfo];
				[ansInfo release];
				j++;
				if (j == STOCKCHAIN_ANSNUM) {
					return;
				}
			}
			
		}
	}
}

-(int)CustomCompareString:(NSString *)_oriString ComString:(NSString *)_comString{
	if ([_comString compare:_oriString options:NSCaseInsensitiveSearch range:NSMakeRange(0, [_oriString length])] == NSOrderedSame) {
		return 1;
	}
	NSString * tempString;
	
	NSRange range1;
    range1=[_comString rangeOfString:_oriString];
    if (range1.location!=NSNotFound && range1.length==[_oriString length]) {
        return 1;
    }
	range1 = [_oriString rangeOfString:@"X"];
	if (range1.location != NSNotFound && range1.location <[_oriString length]) {
		tempString = [_oriString stringByReplacingOccurrencesOfString:@"X" withString:@"H"];
		
		if ([_comString compare:tempString options:NSCaseInsensitiveSearch range:NSMakeRange(0, [tempString length])] == NSOrderedSame) {
			return 1;
		}
	}
	
	range1 = [_oriString rangeOfString:@"H"];
	if (range1.location != NSNotFound && range1.location <[_oriString length]) {
		tempString = [_oriString stringByReplacingOccurrencesOfString:@"H" withString:@"X"];
		
		if ([_comString compare:tempString options:NSCaseInsensitiveSearch range:NSMakeRange(0, [tempString length])] == NSOrderedSame) {
			return 1;
		}
	}
	
	range1 = [_oriString rangeOfString:@"L"];
	if (range1.location != NSNotFound && range1.location <[_oriString length]) {
		tempString = [_oriString stringByReplacingOccurrencesOfString:@"L" withString:@"N"];
		
		if ([_comString compare:tempString options:NSCaseInsensitiveSearch range:NSMakeRange(0, [tempString length])] == NSOrderedSame) {
			return 1;
		}
	}
	
	range1 = [_oriString rangeOfString:@"N"];
	if (range1.location != NSNotFound && range1.location <[_oriString length]) {
		tempString = [_oriString stringByReplacingOccurrencesOfString:@"N" withString:@"L"];
		
		if ([_comString compare:tempString options:NSCaseInsensitiveSearch range:NSMakeRange(0, [tempString length])] == NSOrderedSame) {
			return 1;
		}
	}
	
	range1 = [_oriString rangeOfString:@"C"];
	if (range1.location != NSNotFound && range1.location <[_oriString length]) {
		tempString = [_oriString stringByReplacingOccurrencesOfString:@"C" withString:@"Z"];
		
		if ([_comString compare:tempString options:NSCaseInsensitiveSearch range:NSMakeRange(0, [tempString length])] == NSOrderedSame) {
			return 1;
		}
	}
	
	range1 = [_oriString rangeOfString:@"Z"];
	if (range1.location != NSNotFound && range1.location <[_oriString length]) {
		tempString = [_oriString stringByReplacingOccurrencesOfString:@"Z" withString:@"C"];
		
		if ([_comString compare:tempString options:NSCaseInsensitiveSearch range:NSMakeRange(0, [tempString length])] == NSOrderedSame) {
			return 1;
		}
	}
	
	
	
	return -1;
}


-(void) getMultiCurrStockDataReq:(int)setDomain coltType:(int)coltType startXH:(int)startxh wantNum:(int)wantnum sortType:(int) sorttype {
	NSMutableData *newdata = [[NSMutableData alloc] init];
	short  req = MULTIHQ2_5MMP_NREQ;
	[newdata appendBytes:(void *)&req length:sizeof(short)];
	[newdata appendBytes:(void *)&setDomain length:sizeof(short)];
	[newdata appendBytes:(void *)&coltType length:sizeof(short)];
	[newdata appendBytes:(void *)&startxh length:sizeof(short)];
	[newdata appendBytes:(void *)&wantnum length:sizeof(short)];
	[newdata appendBytes:(void *)&sorttype length:sizeof(short)];
	
	[g_pEComm sendIt:newdata length:[newdata length]];
	[newdata release];
}

-(NSMutableData *) getMultiCurrStockDataReqEx:(int)setDomain coltType:(int)coltType startXH:(int)startxh wantNum:(int)wantnum sortType:(int) sorttype {
	NSMutableData *newdata = [[[NSMutableData alloc] init] autorelease];
	short  req = MULTIHQ2_5MMP_NREQ;
	[newdata appendBytes:(void *)&req length:sizeof(short)];
	[newdata appendBytes:(void *)&setDomain length:sizeof(short)];
	[newdata appendBytes:(void *)&coltType length:sizeof(short)];
	[newdata appendBytes:(void *)&startxh length:sizeof(short)];
	[newdata appendBytes:(void *)&wantnum length:sizeof(short)];
	[newdata appendBytes:(void *)&sorttype length:sizeof(short)];
	
	return newdata;
}



-(void) getMultiCurrStockDataAsn:(NSMutableArray *) gridArray TotalNum:(void *)_totalNum hqResult:(HqResultData * )_hqresult{
	NSData * theData = [[NSData alloc] initWithData:_hqresult.resultData];
	[gridArray removeAllObjects];
	
	int nf = 16;
	short num =0;
	[theData getTdxBytes:&num range:NSMakeRange(nf, sizeof(short))];
	
	nf += sizeof(num);
	[theData getTdxBytes:_totalNum range:NSMakeRange(nf, sizeof(short))];
	nf+= sizeof(short);
	
	for (int i = 0 ; i < num; i++) {
		SinHqInfo * tempInfo = [[SinHqInfo alloc] init];
		
		short tempShort=0;
		int tempInt=0;
		float tempFloat=0.0;
		NSString * tempString;
		[theData getTdxBytes:&tempShort range:NSMakeRange(nf, sizeof(short))];
		tempInfo.setcode = tempShort;
		
		nf += sizeof(short);
		tempString = [[NSString alloc] initWithData:[theData subdataWithRange:NSMakeRange(nf, 6)] encoding:NSUTF8StringEncoding];
		
		tempInfo.gpcode =  [NSString stringWithFormat:@"%@",tempString];
		[tempString release];
		
		nf +=6 ;
		tempString = [[NSString alloc] initWithData:[theData subdataWithRange:NSMakeRange(nf, 8)] encoding:CFStringConvertEncodingToNSStringEncoding (kCFStringEncodingGB_18030_2000)];
		tempInfo.gpname = [NSString stringWithFormat:@"%@",tempString];
		[tempString release];
		
		tempInfo.zsflag = [self testZS:tempInfo.gpcode setcode:tempInfo.setcode];
		tempInfo.dataPre = [self getDataPre:tempInfo.gpcode];
		
		nf += 8;
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		tempInfo.closeP = tempFloat;
		nf += sizeof(float);
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		tempInfo.openP = tempFloat;
		nf += sizeof(float);
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		tempInfo.maxP = tempFloat;
		nf += sizeof(float);
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		tempInfo.minP = tempFloat;
		nf += sizeof(float);
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		tempInfo.nowP = tempFloat;
		nf += sizeof(float);
		[theData getTdxBytes:&tempInt range:NSMakeRange(nf, sizeof(int))];
		tempInfo.volume = tempInt;
		nf += sizeof(int);
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		tempInfo.liangbi = tempFloat;
		nf += sizeof(int);
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		tempInfo.amount = tempFloat;
		nf += sizeof(float);
		
		[theData getTdxBytes:&tempInt range:NSMakeRange(nf, sizeof(int))];
		tempInfo.inside = tempInt;
		nf += sizeof(int);
		[theData getTdxBytes:&tempInt range:NSMakeRange(nf, sizeof(int))];
		tempInfo.outside = tempInt;
		nf += sizeof(int);
		
		
		for (int i = 0; i<5; i++) {
			[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
			tempString = [[NSString alloc] initWithFormat:@"%f",tempFloat];
			[tempInfo.buyP addObject:tempString];
			[tempString release];
			nf += sizeof(float);
		}
		for (int i = 0; i<5; i++) {
			[theData getTdxBytes:&tempInt range:NSMakeRange(nf, sizeof(int))];
			tempString = [[NSString alloc] initWithFormat:@"%i",tempInt];
			[tempInfo.buyV addObject:tempString];
			[tempString release];
			nf += sizeof(int);
		}
		for (int i = 0; i<5; i++) {
			[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
			tempString = [[NSString alloc] initWithFormat:@"%f",tempFloat];
			[tempInfo.sellP addObject:tempString];
			[tempString release];
			nf += sizeof(float);
		}
		for (int i = 0; i<5; i++) {
			[theData getTdxBytes:&tempInt range:NSMakeRange(nf, sizeof(int))];
			tempString = [[NSString alloc] initWithFormat:@"%i",tempInt];
			[tempInfo.sellV addObject:tempString];
			[tempString release];
			nf += sizeof(int);
		}
		
		
		nf+= 1;
		
		//财务数据
		//总股本
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		tempInfo.J_zgb = tempFloat;
		nf += sizeof(float);
		//流通股本
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		tempInfo.ActiveCapital = tempFloat;
		nf += sizeof(float);
		//所属省份
		[theData getTdxBytes:&tempShort range:NSMakeRange(nf, sizeof(short))];
		tempInfo.J_addr = tempShort;
		nf += sizeof(short);
		//所属行业
		[theData getTdxBytes:&tempShort range:NSMakeRange(nf, sizeof(short))];
		tempInfo.J_hy = tempShort;
		nf += sizeof(short);
		//总市值
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		tempInfo.J_zsz = tempFloat;
		nf += sizeof(float);
		//市盈
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		tempInfo.J_syl = tempFloat;
		nf += sizeof(float);
		
		
		if (tempInfo.zsflag) {
			tempInfo.exchange = 0;
		}
		else  {
			if (tempInfo.ActiveCapital > 0) {
				tempInfo.exchange =  (tempInfo.volume*100*100)/(tempInfo.ActiveCapital*10000);
			}
			else {
				tempInfo.exchange =  0.0;
			}
			
			
			
		}
		
		//if(tempInfo.nowP > 0.1)
		if(tempInfo.nowP > 0.01){
			tempInfo.zad = tempInfo.nowP - tempInfo.closeP;
			tempInfo.zaf  = (tempInfo.nowP - tempInfo.closeP)*100/tempInfo.closeP;
			tempInfo.zef = (tempInfo.maxP - tempInfo.minP)*100/tempInfo.closeP;
		}
		else {
			tempInfo.zef = 0.0f;
			
            float buyPrice = 0.0;
            if([tempInfo.buyP count])
                buyPrice=[[tempInfo.buyP objectAtIndex:0] floatValue];
            float sellPrice = 0.0;
            if([tempInfo.sellP count])
                sellPrice=[[tempInfo.sellP objectAtIndex:0] floatValue];
							
			if ((buyPrice > 0.001)&&(sellPrice > 0.001)&&(ABSOLUTE_VALUE(buyPrice - sellPrice) < 0.001)) {
				tempInfo.zaf  = (buyPrice - tempInfo.closeP)*100/tempInfo.closeP;
				tempInfo.zad = buyPrice - tempInfo.closeP;
			}
			else {
				tempInfo.zaf = 0.0f;
				tempInfo.zad = 0.0f;
			}

			
		}
		[gridArray  addObject:(SinHqInfo *)tempInfo];
		
		[tempInfo release];
	}
	
	[theData release];
}

-(void) getCurrStockReq : (NSString *) gpcode setcode:(int) setcode{
	NSMutableData *newdata = [[NSMutableData alloc] init];
	short  req = GGHQ_5MMP_NREQ;
	[newdata appendBytes:(void *)&req length:sizeof(short)];
	[newdata appendBytes:(void *)&setcode length:sizeof(short)];
	[newdata appendData:[gpcode dataUsingEncoding:NSUTF8StringEncoding]];
		
	[g_pEComm sendIt:newdata length:[newdata length]];
	[newdata release];
}

-(void) getCurrStockAsn{
	NSData * theData = [[NSData alloc] initWithData:g_pEComm.readData];
	int nf = 24;
	short tempShort=0;
	int tempInt=0;
	float tempFloat=0.0;
	NSString * tempString;
	[theData getTdxBytes:&tempShort range:NSMakeRange(nf, sizeof(short))];
	currHpAns.setcode = tempShort;
	
	nf += sizeof(short);
	tempString = [[NSString alloc] initWithData:[theData subdataWithRange:NSMakeRange(nf, 6)] encoding:NSUTF8StringEncoding];
	currHpAns.gpcode = tempString;
	[tempString release];
	
	currHpAns.zsflag = [self testZS:currHpAns.gpcode setcode:currHpAns.setcode];
	currHpAns.dataPre = [self getDataPre:currHpAns.gpcode];
	
	nf +=6 ;
	
	tempString = [[NSString alloc] initWithData:[theData subdataWithRange:NSMakeRange(nf, 8)] encoding:CFStringConvertEncodingToNSStringEncoding (kCFStringEncodingGB_18030_2000)];
	currHpAns.gpname = tempString;
	[tempString release];
	nf += 8;
	[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
	currHpAns.closeP = tempFloat;
	nf += sizeof(float);
	[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
	currHpAns.openP = tempFloat;
	nf += sizeof(float);
	[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
	currHpAns.maxP = tempFloat;
	nf += sizeof(float);
	[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
	currHpAns.minP = tempFloat;
	nf += sizeof(float);
	[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
	currHpAns.nowP = tempFloat;
	
	nf += 4;
	[theData getTdxBytes:&tempInt range:NSMakeRange(nf, sizeof(int))];
	currHpAns.volume = tempInt;
	nf += sizeof(int);
	[theData getTdxBytes:&tempInt range:NSMakeRange(nf, sizeof(int))];
	currHpAns.nowVol = tempInt;
	nf += sizeof(int);
	[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
	currHpAns.amount = tempFloat;
	nf += sizeof(float);
	[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
	currHpAns.inside = tempFloat;
	nf += sizeof(float);
	[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
	currHpAns.outside = tempFloat;
	
	nf+=4;
	[currHpAns.buyP removeAllObjects];
	[currHpAns.buyV removeAllObjects];
	[currHpAns.sellP removeAllObjects];
	[currHpAns.sellV removeAllObjects];
	
	for (int i = 0; i<5; i++) {
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		[currHpAns.buyP addObject:[NSString stringWithFormat:@"%f",tempFloat]];
		nf += sizeof(float);
	}
	for (int i = 0; i<5; i++) {
		[theData getTdxBytes:&tempInt range:NSMakeRange(nf, sizeof(int))];
		[currHpAns.buyV addObject:[NSString stringWithFormat:@"%i",tempInt]];
		nf += sizeof(int);
	}
	for (int i = 0; i<5; i++) {
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		[currHpAns.sellP addObject:[NSString stringWithFormat:@"%f",tempFloat]];
		nf += sizeof(float);
	}
	for (int i = 0; i<5; i++) {
		[theData getTdxBytes:&tempInt range:NSMakeRange(nf, sizeof(int))];
		[currHpAns.sellV addObject:[NSString stringWithFormat:@"%i",tempInt]];
		nf += sizeof(int);
	}
	currHpAns.zaf  = (currHpAns.nowP - currHpAns.closeP)*100/currHpAns.closeP;
	[theData release];
}


-(BOOL) testZS:(NSString *)gpcode setcode:(int)setcode{
	const char * tempChar = [gpcode UTF8String];

	
	if(tempChar[0]=='8' && (tempChar[1]=='8' || tempChar[1]=='3')) //如果是组合宝,也当成指数来处理
		return TRUE;
    long l = atol(tempChar);
	if(setcode==1)
	{
		if(l > 999000l || l < 30l || l == 300l || (l>=900l && l<=999l)) return TRUE;
		if(tempChar[0]=='0' && tempChar[1]=='0' && tempChar[2]=='0') return TRUE;
	}
	else
	{
		if(tempChar[0]=='3' && tempChar[1]=='9') return TRUE;
	}
	return FALSE;
	
}

-(int) getDataPre:(NSString *)gpcode {
	const char * code = [gpcode UTF8String];
	if (atol(code) >= 900000 && atol(code) < 999000)
		return 3;
	if (strncmp(code,"201",3)==0) 
		return 3;
	if (strncmp(code,"202",3)==0) 
		return 3;
	if (strncmp(code,"203",3)==0) 
		return 3;
	if (strncmp(code,"204",3)==0) 
		return 3;
	if (strncmp(code,"131",3)==0) 
		return 3;
	if (strncmp(code,"42",2)==0)
		return 3;
	if (strncmp(code,"15",2)==0 || strncmp(code,"16",2)==0 || strncmp(code,"17",2)==0 || strncmp(code,"18",2)==0 || strncmp(code,"5",1)==0)
		return 3;
	if (strncmp(code,"03",2)==0 || strncmp(code,"08",2)==0 )
		return 3;
	return 2;
}

-(void) getMinuteDataReq : (NSString *) gpcode setcode:(int) setcode{
	NSMutableData *newdata = [[NSMutableData alloc] init];
	short  req = COMBFST_NREQ;
	[newdata appendBytes:(void *)&req length:sizeof(short)];
	
	[newdata appendBytes:(void *)&setcode length:sizeof(short)];
	[newdata appendData:[gpcode dataUsingEncoding:NSUTF8StringEncoding]];
	[g_pEComm sendIt:newdata length:[newdata length]];
	[newdata release];
}
-(void) getMinuteDataAsn{
	[minute_data removeAllObjects];
	NSData * theData = [[[NSData alloc] initWithData:g_pEComm.readData] autorelease];
	
	
	int nf = 16;
	short num=0 ;
	[theData getTdxBytes:&num range:NSMakeRange(nf, sizeof(short))];
	
	nf += sizeof(num);
	
	
	
	for (int i = 0 ; i < num; i++) {
		Minute_Unit * tempMin = [[Minute_Unit alloc] init];
		short minute =0;
		float now=0.0,average=0.0;
		int nowvol=0;
		
		[theData getTdxBytes:&minute range:NSMakeRange(nf, sizeof(short))];
		tempMin.minute = minute;
		
		nf += sizeof(minute);
		
		[theData getTdxBytes:&now range:NSMakeRange(nf, sizeof(float))];
		tempMin.now = now;
		tempMin.zaf = (now - currHpAns.closeP)*100/currHpAns.closeP;
		
		nf += sizeof(now);
		
		[theData getTdxBytes:&average range:NSMakeRange(nf, sizeof(float))];
		tempMin.average = average;
		
		nf += sizeof(now);
		
		[theData getTdxBytes:&nowvol range:NSMakeRange(nf, sizeof(int))];
		tempMin.nowvol = nowvol;
		
		if(currHpAns.zsflag)  tempMin.nowvol = nowvol / 100;
		
		nf +=sizeof(nowvol);
		
		
		[minute_data addObject:tempMin];
		[tempMin release];
	}
}


-(void) getAnalyseDataReq : (NSString *) gpcode setcode:(int) setcode period:(int)m_period mulNum:(int)mulnum startxh:(int)startxh recNum:(int)num {
	NSMutableData *newdata = [[NSMutableData alloc] init];
	short  req = COMBFX2_NREQ;
	[newdata appendBytes:(void *)&req length:sizeof(short)];
	[newdata appendBytes:(void *)&setcode length:sizeof(short)];
	[newdata appendData:[gpcode dataUsingEncoding:NSUTF8StringEncoding]];
	[newdata appendBytes:(void *)&m_period length:sizeof(short)];
	[newdata appendBytes:(void *)&mulnum length:sizeof(short)];
	[newdata appendBytes:(void *)&startxh length:sizeof(short)];
	[newdata appendBytes:(void *)&num length:sizeof(short)];

	[g_pEComm sendIt:newdata length:[newdata length]];
	[newdata release];
	
}
-(void) getAnalyseDataAsn {
	[analyse_data removeAllObjects];
	NSData * theData = [[NSData alloc] initWithData:g_pEComm.readData];
	
	int nf = 16;
	short num=0 ;
	[theData getTdxBytes:&num range:NSMakeRange(nf, sizeof(short))];
	
	nf += sizeof(num);

	for (int i = 0 ; i < num; i++) {
		Analyse_Unit * tempAna = [[Analyse_Unit alloc] init];
		int tempInt =0;
		float tempFloat=0.0;
		
		[theData getTdxBytes:&tempInt range:NSMakeRange(nf, sizeof(int))];
		nf+= sizeof(int);
		tempAna.date = tempInt;
		
		[theData getTdxBytes:&tempInt range:NSMakeRange(nf, sizeof(int))];
		nf+= sizeof(int);
		tempAna.time = tempInt;
		
		
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		tempAna.openp = tempFloat;
		nf+= sizeof(float);
		
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		tempAna.highp = tempFloat;
		nf+= sizeof(float);
		
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		tempAna.lowp = tempFloat;
		nf+= sizeof(float);
		
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		tempAna.closep = tempFloat;
		nf+= sizeof(float);
		
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		tempAna.amount = tempFloat;
		nf+= sizeof(float);
		
		[theData getTdxBytes:&tempInt range:NSMakeRange(nf, sizeof(int))];
		nf+= sizeof(int);
		tempAna.volumn = tempInt;
		
		[analyse_data addObject:(Analyse_Unit *)tempAna];
		[tempAna release];
	}	
	
	[theData release];
}


-(NSMutableData * ) getF10CFGReq : (NSString *) gpcode setcode:(int) setcode{
	NSMutableData *newdata = [[[NSMutableData alloc] init] autorelease];
	short  req = F10CFG_NREQ;
	short tempShort  = 0;
	[newdata appendBytes:(void *)&req length:sizeof(short)];
	[newdata appendBytes:(void *)&setcode length:sizeof(short)];
	[newdata appendData:[gpcode dataUsingEncoding:NSUTF8StringEncoding]];
	[newdata appendBytes:(void *)&tempShort length:sizeof(short)];
	[newdata appendBytes:(void *)&tempShort length:sizeof(short)];
	
	return newdata;
}
-(void) getF10CFGAsn:(HqResultData * )_hqresult{
	if ([f10title_data count] >0) {
		[f10title_data removeAllObjects];
	}
	NSData * theData = [[NSData alloc] initWithData:_hqresult.resultData];
	
	int nf = 16;
	short num =0;
	[theData getTdxBytes:&num range:NSMakeRange(nf, sizeof(short))];
	
	nf += sizeof(num);
	
	
	
	for (int i = 0 ; i < num; i++) {
		F10Title_Unit * tempTitle = [[F10Title_Unit alloc] init];
		NSString * tempString;
		int tempInt=0;
		
		tempString = [[NSString alloc] initWithData:[theData subdataWithRange:NSMakeRange(nf, 12)] encoding:CFStringConvertEncodingToNSStringEncoding (kCFStringEncodingGB_18030_2000)];
		tempTitle.sTitle = [NSString stringWithFormat:@"%@",tempString];
		[tempString release];
		nf += 12;
		
		tempString = [[NSString alloc] initWithData:[theData subdataWithRange:NSMakeRange(nf, 80)] encoding:CFStringConvertEncodingToNSStringEncoding (kCFStringEncodingGB_18030_2000)];
		tempTitle.sFilePath = [NSString stringWithFormat:@"%@",tempString];
		[tempString release];
		nf+= 80;
		
		[theData getTdxBytes:&tempInt range:NSMakeRange(nf, sizeof(int))];
		tempTitle.nOffset = tempInt;
		
		nf += sizeof(float);
		
		[theData getTdxBytes:&tempInt range:NSMakeRange(nf, sizeof(float))];
		tempTitle.nLength = tempInt;
	
		
		nf += sizeof(float);
		
		[f10title_data addObject:tempTitle];
		[tempTitle release];
	}
	[theData release];
} 

-(NSMutableData *) getF10CFGReq_ALL : (NSString *) gpcode setcode:(int) setcode{
	NSMutableData *newdata = [[[NSMutableData alloc] init] autorelease];
	short  req = F10CFG_ALL;
	short tempShort  = 0;
	[newdata appendBytes:(void *)&req length:sizeof(short)];
	[newdata appendBytes:(void *)&setcode length:sizeof(short)];
	[newdata appendData:[gpcode dataUsingEncoding:NSUTF8StringEncoding]];
	[newdata appendBytes:(void *)&tempShort length:sizeof(short)];
	[newdata appendBytes:(void *)&tempShort length:sizeof(short)];

	return newdata;
	
}
-(void) getF10CFGAsn_ALL:(HqResultData * )_hqresult DataArray:(NSMutableArray *)_dataArray{
	
	NSData * theData = [[NSData alloc] initWithData:_hqresult.resultData];
	
	int nf = 16;
	short num=0 ;
	[theData getTdxBytes:&num range:NSMakeRange(nf, sizeof(short))];
	
	nf += sizeof(num);
	
	
	
	for (int i = 0 ; i < num; i++) {
		F10Title_Unit * tempTitle = [[F10Title_Unit alloc] init];
		NSString * tempString;
		int tempInt=0,j=0;
		char tempChar=0;
		for (j = 0; j<64; j++) {
			[theData getTdxBytes:&tempChar range:NSMakeRange(nf+j, sizeof(char))];
			if (tempChar == '\0') {
				break;
			}
		}
		
		tempString = [[NSString alloc] initWithData:[theData subdataWithRange:NSMakeRange(nf, j)] encoding:CFStringConvertEncodingToNSStringEncoding (kCFStringEncodingGB_18030_2000)];
		
		tempTitle.sTitle = [NSString stringWithFormat:@"%@",tempString];
		[tempString release];
		nf += 64;
		
		for (j = 0; j<80; j++) {
			[theData getTdxBytes:&tempChar range:NSMakeRange(nf+j, sizeof(char))];
			if (tempChar == '\0') {
				break;
			}
		}
		
		tempString = [[NSString alloc] initWithData:[theData subdataWithRange:NSMakeRange(nf, j)] encoding:CFStringConvertEncodingToNSStringEncoding (kCFStringEncodingGB_18030_2000)];
		tempTitle.sFilePath = [NSString stringWithFormat:@"%@",tempString];
		[tempString release];
		nf+= 80;
		
		[theData getTdxBytes:&tempInt range:NSMakeRange(nf, sizeof(int))];
		tempTitle.nOffset = tempInt;
		
		nf += sizeof(float);
		
		[theData getTdxBytes:&tempInt range:NSMakeRange(nf, sizeof(float))];
		tempTitle.nLength = tempInt;
		
		
		nf += sizeof(float);
		
		[_dataArray addObject:tempTitle];
		[tempTitle release];
	}
	
	[theData release];
}


-(NSMutableData * ) getF10TxtReq : (NSString *) gpcode setcode:(int) setcode which:(int)which path:(NSString *)path nOffset:(int)nOffset nLength:(int)nLength{
	NSMutableData *newdata = [[[NSMutableData alloc] init] autorelease];
	short  req = F10TXT_NREQ;
	short tempShort  = which;
	[newdata appendBytes:(void *)&req length:sizeof(short)];
	[newdata appendBytes:(void *)&setcode length:sizeof(short)];
	[newdata appendData:[gpcode dataUsingEncoding:NSUTF8StringEncoding]];
	[newdata appendBytes:(void *)&tempShort length:sizeof(short)];
	[newdata appendData:[path dataUsingEncoding:NSUTF8StringEncoding]];
	[newdata appendBytes:(void *)&nOffset length:sizeof(int)];
	[newdata appendBytes:(void *)&nLength length:sizeof(int)];
	[newdata appendBytes:(void *)&tempShort length:sizeof(short)];
	[newdata appendBytes:(void *)&tempShort length:sizeof(short)];
	
	return newdata;
}
-(NSString *) getF10TxtAsn :(HqResultData * )_hqresult{
	NSData * theData = [[NSData alloc] initWithData:_hqresult.resultData];

	int nf = 26;
	short num =0;
	[theData getTdxBytes:&num range:NSMakeRange(nf, sizeof(short))];
	nf +=sizeof(short) ;
	NSString * tempString = [[NSString alloc] initWithData:[theData subdataWithRange:NSMakeRange(nf, num)] encoding:CFStringConvertEncodingToNSStringEncoding (kCFStringEncodingGB_18030_2000)];
	
	[theData release];
	if (self.f10Txt_data != nil) {
		[self.f10Txt_data release],self.f10Txt_data=nil;
	}
	self.f10Txt_data = [[NSString alloc]  initWithFormat:@"%@",tempString];
	return [tempString autorelease];
}


-(NSMutableData *) getF10TxtReqEx : (NSString *) gpcode setcode:(int) setcode which:(int)which path:(NSString *)path nOffset:(int)nOffset nLength:(int)nLength{
	NSMutableData *newdata = [[[NSMutableData alloc] init] autorelease];
	short  req = F10TXT_ALL;
	short tempShort  = which;
	char tempChar = 0;
	[newdata appendBytes:(void *)&req length:sizeof(short)];
	[newdata appendBytes:(void *)&setcode length:sizeof(short)];
	[newdata appendData:[gpcode dataUsingEncoding:NSUTF8StringEncoding]];
	[newdata appendBytes:(void *)&tempShort length:sizeof(short)];
	[newdata appendData:[path dataUsingEncoding:NSUTF8StringEncoding]];
	if ([path length] < 80) {
		for (int i =[path length]; i<80; i++) {
			[newdata appendBytes:(void *)&tempChar length:sizeof(char)];
		}
	}
	[newdata appendBytes:(void *)&nOffset length:sizeof(int)];
	[newdata appendBytes:(void *)&nLength length:sizeof(int)];
	[newdata appendBytes:(void *)&tempShort length:sizeof(short)];
	[newdata appendBytes:(void *)&tempShort length:sizeof(short)];

	return newdata;
}
-(NSString *) getF10TxtAsnEx:(HqResultData * )_hqresult DataString:(NSString *)_dataString{
	NSData * theData = [[NSData alloc] initWithData:_hqresult.resultData];
	
	int nf = 26;
	
    short num =0;
	[theData getTdxBytes:&num range:NSMakeRange(nf, sizeof(short))];
	
    nf +=sizeof(short) ;
	
	int j;
	char tempChar=0;
	for (j = 0; j<num; j++) {
		[theData getTdxBytes:&tempChar range:NSMakeRange(nf+j, sizeof(char))];
		if (tempChar == '\0') {
			break;
		}
	}
	
	
	NSString * tempString = [[NSString alloc] initWithData:[theData subdataWithRange:NSMakeRange(nf, j)] encoding:CFStringConvertEncodingToNSStringEncoding (kCFStringEncodingGB_18030_2000)];
  
	
	[theData release];
	return tempString;
}



-(void) getTickDataReq:(NSString *) gpcode setcode:(int) setcode startx:(int)startx wantnum:(int) num{
	NSMutableData *newdata = [[NSMutableData alloc] init];
	short  req = COMBTICK_NREQ;
	[newdata appendBytes:(void *)&req length:sizeof(short)];
	[newdata appendBytes:(void *)&setcode length:sizeof(short)];
	[newdata appendData:[gpcode dataUsingEncoding:NSUTF8StringEncoding]];
	[newdata appendBytes:(void *)&startx length:sizeof(short)];
	[newdata appendBytes:(void *)&num length:sizeof(short)];
	
	[g_pEComm sendIt:newdata length:[newdata length]];
	[newdata release];
}

-(NSMutableData *) getTickDataReqEx:(NSString *) gpcode setcode:(int) setcode startx:(int)startx wantnum:(int) num{
	NSMutableData *newdata = [[[NSMutableData alloc] init] autorelease];
	short  req = COMBTICK_NREQ;
	[newdata appendBytes:(void *)&req length:sizeof(short)];
	[newdata appendBytes:(void *)&setcode length:sizeof(short)];
	[newdata appendData:[gpcode dataUsingEncoding:NSUTF8StringEncoding]];
	[newdata appendBytes:(void *)&startx length:sizeof(short)];
	[newdata appendBytes:(void *)&num length:sizeof(short)];
	
	return newdata;
}


-(void) getTIckDaraAns:(NSMutableArray *) ansArray hqResult:(HqResultData * )_hqresult{
	NSData * theData = [[NSData alloc] initWithData:_hqresult.resultData];
	
	int nf = 16;
	short num =0;
	[theData getTdxBytes:&num range:NSMakeRange(nf, sizeof(short))];
	
	nf += sizeof(num);
	nf += 6;
	int tempInt=0 ;
	float tempFloat=0;
	short tempShort=0;
	for (int i = 0 ; i < num; i++) {
		[theData getTdxBytes:&tempShort range:NSMakeRange(nf, sizeof(short))];
		if(tempShort<=0)
			continue;
		TickInfo * tempTick = [[TickInfo alloc] init];
		nf+= sizeof(short);
		tempTick.minute = tempShort;
		
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		nf+= sizeof(float);
		tempTick.nowPrice = tempFloat;
		
		[theData getTdxBytes:&tempInt range:NSMakeRange(nf, sizeof(int))];
		nf+= sizeof(int);
		tempTick.nowVol = tempInt;
		
		[theData getTdxBytes:&tempShort range:NSMakeRange(nf, sizeof(short))];
		nf+= sizeof(short);
		tempTick.inOutFlag = tempShort;
		
		
				
		[ansArray addObject:(TickInfo *)tempTick];
		[tempTick release];
	}	
	
	[theData release];
	
	
}

-(unsigned long) getTIckDaraAnsEx:(NSMutableArray *) ansArray hqResult:(HqResultData * )_hqresult{
	
	NSData * theData = [[NSData alloc] initWithData:_hqresult.resultData];
	
	int nf = 16;
	short num=0 ;
	[theData getTdxBytes:&num range:NSMakeRange(nf, sizeof(short))];
	
	nf += sizeof(short);
	short xh=0;
	[theData getTdxBytes:&xh range:NSMakeRange(nf, sizeof(short))];
	nf += sizeof(short);
	unsigned long ntotalnum=0;
	[theData getTdxBytes:&ntotalnum range:NSMakeRange(nf, sizeof(unsigned long))];
	nf+=sizeof(unsigned long);
	int tempInt=0 ;
	float tempFloat=0;
	short tempShort=0;
	for (int i = 0 ; i < num; i++) {
		[theData getTdxBytes:&tempShort range:NSMakeRange(nf, sizeof(short))];
		if(tempShort<=0)
			continue;
		TickInfo * tempTick = [[TickInfo alloc] init];
		nf+= sizeof(short);
		tempTick.minute = tempShort;
		
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		nf+= sizeof(float);
		tempTick.nowPrice = tempFloat;
		
		[theData getTdxBytes:&tempInt range:NSMakeRange(nf, sizeof(int))];
		nf+= sizeof(int);
		tempTick.nowVol = tempInt;
		
		[theData getTdxBytes:&tempShort range:NSMakeRange(nf, sizeof(short))];
		nf+= sizeof(short);
		tempTick.inOutFlag = tempShort;
		
		[ansArray addObject:(TickInfo *)tempTick];
	}
	[ansArray addObject:[[NSString alloc] initWithFormat:@"%hi",xh]];
	[theData release];
	return ntotalnum;
	
}

-(NSMutableData *) getCombDataReq:(NSString *) gpcode setcode:(int) setcode flags:(int) _flags period:(int)m_period mulNum:(int)mulnum startxh:(int)startxh recNum:(int)num tickStartx:(int)tickStartx tickWantnum:(int) tickNum{
	NSMutableData *newdata = [[[NSMutableData alloc] init] autorelease];
	short  req = COMB_NREQ;
	[newdata appendBytes:(void *)&req length:sizeof(short)];
	[newdata appendBytes:(void *)&setcode length:sizeof(short)];
	[newdata appendData:[gpcode dataUsingEncoding:NSUTF8StringEncoding]];
	[newdata appendBytes:(void *)&m_period length:sizeof(short)];
	[newdata appendBytes:(void *)&mulnum length:sizeof(short)];
	[newdata appendBytes:(void *)&startxh length:sizeof(short)];
	[newdata appendBytes:(void *)&num length:sizeof(short)];
	[newdata appendBytes:(void *)&_flags length:sizeof(int)];
	[newdata appendBytes:(void *)&tickStartx length:sizeof(short)];
	[newdata appendBytes:(void *)&tickNum length:sizeof(short)];
	
	return newdata;
}
-(NSMutableData *) getCombDataReqEx:(NSString *) gpcode setcode:(int) setcode flags:(int) _flags period:(int)m_period mulNum:(int)mulnum startxh:(int)startxh recNum:(int)num tickStartx:(int)tickStartx tickWantnum:(int) tickNum wParam:(int)_wParam lParam:(int)_lParam{
	NSMutableData *newdata = [[[NSMutableData alloc] init] autorelease];
	short  req = COMB_NREQ;
	[newdata appendBytes:(void *)&req length:sizeof(short)];
	[newdata appendBytes:(void *)&setcode length:sizeof(short)];
	[newdata appendData:[gpcode dataUsingEncoding:NSUTF8StringEncoding]];
	[newdata appendBytes:(void *)&m_period length:sizeof(short)];
	[newdata appendBytes:(void *)&mulnum length:sizeof(short)];
	[newdata appendBytes:(void *)&startxh length:sizeof(short)];
	[newdata appendBytes:(void *)&num length:sizeof(short)];
	[newdata appendBytes:(void *)&_flags length:sizeof(int)];
	[newdata appendBytes:(void *)&tickStartx length:sizeof(short)];
	[newdata appendBytes:(void *)&tickNum length:sizeof(short)];
	[newdata appendBytes:(void *)&_wParam length:sizeof(int)];
	[newdata appendBytes:(void *)&_lParam length:sizeof(int)];
	
	
	return newdata;
}

-(void) getCombDataAns:(HqResultData * )_hqresult Result:(NSMutableDictionary *)_result{
	NSMutableArray * zstArray;
	NSMutableArray * fxtArray;
	NSMutableArray * tickArray;
	SinHqInfo * ansInfo;
	NSMutableArray * gbbqArray;
	
	
	NSData * theData = [[NSData alloc] initWithData:_hqresult.resultData];
	
	int nf = 16;
	int flags ;
	[theData getTdxBytes:&flags range:NSMakeRange(nf, sizeof(int))];
	nf += sizeof(int);
	[_result setObject:[NSString stringWithFormat:@"%i",_hqresult.resultStat] forKey:@"RESULTSTAT"];
	[_result setObject:[NSString stringWithFormat:@"%i",flags] forKey:@"FLAG"];
	
	if ((flags & COMBO_MASK_GGHQ) == COMBO_MASK_GGHQ) {
		ansInfo = [[SinHqInfo alloc] init]  ;
		short tempShort;
		int tempInt;
		float tempFloat;
		NSString * tempString;
		NSString * nameString;
		NSString * codeString;
		
		nf += 8;
		
		[theData getTdxBytes:&tempShort range:NSMakeRange(nf, sizeof(short))];
		ansInfo.setcode = tempShort;
		
		nf += sizeof(short);
		codeString = [[NSString alloc] initWithData:[theData subdataWithRange:NSMakeRange(nf, 6)] encoding:NSUTF8StringEncoding] ;
		ansInfo.gpcode = [NSString stringWithFormat:@"%@",codeString];
		[codeString release],codeString = nil;
		ansInfo.zsflag = [self testZS:[NSString stringWithFormat:@"%@",ansInfo.gpcode] setcode:ansInfo.setcode];
		ansInfo.dataPre = [self getDataPre:[NSString stringWithFormat:@"%@",ansInfo.gpcode]];
		
		nf +=6 ;
		nameString = [[NSString alloc] initWithData:[theData subdataWithRange:NSMakeRange(nf, 8)] encoding:CFStringConvertEncodingToNSStringEncoding (kCFStringEncodingGB_18030_2000)];
		ansInfo.gpname = [NSString stringWithFormat:@"%@",nameString];
		[nameString release],nameString=nil;
		nf += 8;
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		ansInfo.closeP = tempFloat;
		nf += sizeof(float);
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		ansInfo.openP = tempFloat;
		//max
		nf += sizeof(float);
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		ansInfo.maxP = tempFloat;
		//min
		nf += sizeof(float);
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		ansInfo.minP = tempFloat;
		//now
		nf += sizeof(float);
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		ansInfo.nowP = tempFloat;
		
		//volumn and nowvol
		nf += 4;
		[theData getTdxBytes:&tempInt range:NSMakeRange(nf, sizeof(int))];
		ansInfo.volume = tempInt;
		nf += sizeof(int);
		[theData getTdxBytes:&tempInt range:NSMakeRange(nf, sizeof(int))];
		ansInfo.nowVol = tempInt;
		
		//amout
		nf += sizeof(int);
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		ansInfo.amount = tempFloat;
		nf += sizeof(float);
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		ansInfo.inside = tempFloat;
		nf += sizeof(float);
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		ansInfo.outside = tempFloat;
		
		nf+=4;
		
		
		for (int i = 0; i<5; i++) {
			[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
			tempString = [[NSString alloc] initWithFormat:@"%f",tempFloat];
			[ansInfo.buyP addObject:tempString];
			[tempString release];
			nf += sizeof(float);
		}
		for (int i = 0; i<5; i++) {
			[theData getTdxBytes:&tempInt range:NSMakeRange(nf, sizeof(int))];
			tempString = [[NSString alloc] initWithFormat:@"%i",tempInt];
			[ansInfo.buyV addObject:tempString];
			[tempString release];
			nf += sizeof(int);
		}
		for (int i = 0; i<5; i++) {
			[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
			tempString = [[NSString alloc] initWithFormat:@"%f",tempFloat];
			[ansInfo.sellP addObject:tempString];
			[tempString release];
			nf += sizeof(float);
		}
		for (int i = 0; i<5; i++) {
			[theData getTdxBytes:&tempInt range:NSMakeRange(nf, sizeof(int))];
			tempString = [[NSString alloc] initWithFormat:@"%i",tempInt];
			[ansInfo.sellV addObject:tempString];
			[tempString release];
			nf += sizeof(int);
		}
		nf+=1;
		if(ansInfo.nowP > 0.01){
			ansInfo.zad = ansInfo.nowP - ansInfo.closeP;
			ansInfo.zaf  = (ansInfo.nowP - ansInfo.closeP)*100/ansInfo.closeP;
			ansInfo.zef = (ansInfo.maxP - ansInfo.minP)*100/ansInfo.closeP;
		}
		else {
			
			ansInfo.zef = 0.0f;
			
			float buyPrice = 0.0;
            if([ansInfo.buyP count])
                buyPrice=[[ansInfo.buyP objectAtIndex:0] floatValue];
            float sellPrice = 0.0;
            if([ansInfo.sellP count])
                sellPrice=[[ansInfo.sellP objectAtIndex:0] floatValue];
			
			if ((buyPrice > 0.001)&&(sellPrice > 0.001)&&(ABSOLUTE_VALUE(buyPrice - sellPrice) < 0.001)) {
				ansInfo.zaf  = (buyPrice - ansInfo.closeP)*100/ansInfo.closeP;
				ansInfo.zad = buyPrice - ansInfo.closeP;
			}
			else {
				ansInfo.zaf = 0.0f;
				ansInfo.zad = 0.0f;
			}
			
			
		}
		
		//总股本
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		ansInfo.J_zgb = tempFloat;
		nf += sizeof(float);
		//流通股本
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		ansInfo.ActiveCapital = tempFloat;
		nf += sizeof(float);
		//所属省份
		[theData getTdxBytes:&tempShort range:NSMakeRange(nf, sizeof(short))];
		ansInfo.J_addr = tempShort;
		nf += sizeof(short);
		//所属行业
		[theData getTdxBytes:&tempShort range:NSMakeRange(nf, sizeof(short))];
		ansInfo.J_hy = tempShort;
		nf += sizeof(short);
		//总市值
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		ansInfo.J_zsz = tempFloat;
		nf += sizeof(float);
		//市盈率
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		ansInfo.J_syl = tempFloat;
		nf += sizeof(float);
		
		
		if (ansInfo.zsflag) {
			ansInfo.exchange = 0;
		}
		else  {
			if (ansInfo.ActiveCapital > 0) {
				ansInfo.exchange =  (ansInfo.volume*100*100)/(ansInfo.ActiveCapital*10000);
			}
			else {
				ansInfo.exchange =  0.0;
			}
			
			
			
		}
		
		[_result setObject:ansInfo forKey:@"GGHQ"];

        [ansInfo release];
		
	}
	
	if ((flags & COMBO_MASK_ZST) == COMBO_MASK_ZST) {
		short num ;
		[theData getTdxBytes:&num range:NSMakeRange(nf, sizeof(short))];
		
		nf += sizeof(num);
		
		zstArray = [[NSMutableArray alloc]initWithCapacity:num+1];
		
		for (int i = 0 ; i < num; i++) {
			Minute_Unit * tempMin = [[Minute_Unit alloc] init];
			short minute ;
			float now,average;
			int nowvol;
			
			[theData getTdxBytes:&minute range:NSMakeRange(nf, sizeof(short))];
			tempMin.minute = minute;
			
			nf += sizeof(minute);
			
			[theData getTdxBytes:&now range:NSMakeRange(nf, sizeof(float))];
			tempMin.now = now;
			
			nf += sizeof(now);
			
			[theData getTdxBytes:&average range:NSMakeRange(nf, sizeof(float))];
			tempMin.average = average;
			
			nf += sizeof(now);
			
			[theData getTdxBytes:&nowvol range:NSMakeRange(nf, sizeof(int))];
			tempMin.nowvol = nowvol;
			
			
			nf +=sizeof(nowvol);
			
			
			
			[zstArray addObject:tempMin];
			[tempMin release];
		}
		
		[_result setObject:zstArray forKey:@"ZST"];
		[zstArray release];
	}
	
	if ((flags & COMBO_MASK_FXT) == COMBO_MASK_FXT) {
		short num ;
		[theData getTdxBytes:&num range:NSMakeRange(nf, sizeof(short))];
		if(num>0)
        {
            nf += sizeof(num);
            
            fxtArray = [[NSMutableArray alloc]initWithCapacity:num+1];
            
            
            short offset;
            [theData getTdxBytes:&offset range:NSMakeRange(nf, sizeof(short))];
            nf+=sizeof(short);
            [_result setObject:[NSString stringWithFormat:@"%i",offset] forKey:@"FXTOFFSET"];
            
            
            for (int i = 0 ; i < num; i++) {
                Analyse_Unit * tempAna = [[Analyse_Unit alloc] init];
                int tempInt ;
                float tempFloat;
                
                [theData getTdxBytes:&tempInt range:NSMakeRange(nf, sizeof(int))];
                nf+= sizeof(int);
                tempAna.date = tempInt;
                
                [theData getTdxBytes:&tempInt range:NSMakeRange(nf, sizeof(int))];
                nf+= sizeof(int);
                tempAna.time = tempInt;
                
                
                [theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
                tempAna.openp = tempFloat;
                nf+= sizeof(float);
                
                [theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
                tempAna.highp = tempFloat;
                nf+= sizeof(float);
                
                [theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
                tempAna.lowp = tempFloat;
                nf+= sizeof(float);
                
                [theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
                tempAna.closep = tempFloat;
                nf+= sizeof(float);
                
                [theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
                tempAna.amount = tempFloat;
                nf+= sizeof(float);
                
                [theData getTdxBytes:&tempInt range:NSMakeRange(nf, sizeof(int))];
                nf+= sizeof(int);
                tempAna.volumn = tempInt;
                
                [fxtArray addObject:(Analyse_Unit *)tempAna];
                [tempAna release];
            }	
            
            [_result setObject:fxtArray forKey:@"FXT"];
            [fxtArray release];
        }
		
		
	}
	
	
	if ((flags & COMBO_MASK_TICK) == COMBO_MASK_TICK){
		short num=0 ;
		[theData getTdxBytes:&num range:NSMakeRange(nf, sizeof(short))];
		//NSLog(@"the tick num is %i",num);
		
		nf += sizeof(num);
		tickArray = [[NSMutableArray alloc] initWithCapacity:num+1];
		nf += 6;
		
		for (int i = 0 ; i < num; i++) {
			TickInfo * tempTick = [[TickInfo alloc] init];
			int tempInt=0 ;
			float tempFloat=0.0;
			short tempShort=0;
			
			[theData getTdxBytes:&tempShort range:NSMakeRange(nf, sizeof(short))];
			nf+= sizeof(short);
			tempTick.minute = tempShort;
			
			[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
			nf+= sizeof(float);
			tempTick.nowPrice = tempFloat;
			
			[theData getTdxBytes:&tempInt range:NSMakeRange(nf, sizeof(int))];
			nf+= sizeof(int);
			tempTick.nowVol = tempInt;
			
			[theData getTdxBytes:&tempShort range:NSMakeRange(nf, sizeof(short))];
			nf+= sizeof(short);
			tempTick.inOutFlag = tempShort;
			
			
			if (tempTick.nowPrice > 0.01) {
				[tickArray addObject:(TickInfo *)tempTick];
			}
			[tempTick release];
		}	
		
		[_result setObject:tickArray forKey:@"TICK"];
		[tickArray release];
	}
	
	
	if ((flags & COMBO_MASK_GRADE) == COMBO_MASK_GRADE){
		
	}
	
	//财务数据
	if ((flags & COMBO_MASK_CW) == COMBO_MASK_CW){
		FinanceData * financeData = [[FinanceData alloc] init];
		
		//NSLog(@"have cw");
		short tempShort=0;
		int tempInt=0;
		float tempFloat=0.0;
		//流通股本
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		financeData.ActiveCapital = tempFloat;
		nf+= sizeof(float);
		//NSLog(@"ltgb is %f",tempFloat);
		//float       cdp;                // 昨日中价
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		financeData.cdp = tempFloat;
		nf+= sizeof(float);
		
		//float       nh;                 // 卖点
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		financeData.nh = tempFloat;
		nf+= sizeof(float);
		
		//float       nl;                 // 买点
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		financeData.nl = tempFloat;
		nf+= sizeof(float);
		
		//float       ah;                 // 高价突破点
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		financeData.ah = tempFloat;
		nf+= sizeof(float);
		
		//float       al;                 // 低价突破点
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		financeData.al = tempFloat;
		nf+= sizeof(float);
		
		//short       dkflag;             // 适合作多或作空
		[theData getTdxBytes:&tempShort range:NSMakeRange(nf, sizeof(short))];
		financeData.dkflag = tempShort;
		nf+= sizeof(short);
		
		//float       tbp;                // 多空平衡点
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		financeData.tbp = tempFloat;
		nf+= sizeof(float);
		
		//float       stoplost;           // 止损点
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		financeData.stoplost = tempFloat;
		nf+= sizeof(float);
		
		//float       leave;              // 了结点
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		financeData.leave = tempFloat;
		nf+= sizeof(float);
		
		//short       J_addr;				//所属省份
		[theData getTdxBytes:&tempShort range:NSMakeRange(nf, sizeof(short))];
		financeData.J_addr = tempShort;
		nf+= sizeof(short);
		
		//short       J_hy;				//所属行业
		[theData getTdxBytes:&tempShort range:NSMakeRange(nf, sizeof(short))];
		financeData.J_hy = tempShort;
		nf+= sizeof(short);
		
		//long        J_gxrq;				//更新日期
		[theData getTdxBytes:&tempInt range:NSMakeRange(nf, sizeof(long))];
		financeData.J_gxrq = tempInt;
		nf+= sizeof(long);
		
		//long		J_start;			//上市日期
		[theData getTdxBytes:&tempInt range:NSMakeRange(nf, sizeof(long))];
		financeData.J_start = tempInt;
		nf+= sizeof(long);
		
		//float       J_zgb;				//总股本
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		financeData.J_zgb = tempFloat;
		nf+= sizeof(float);
		
		//float       J_zjhhy;			//证监会行业
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		financeData.J_zjhhy = tempFloat;
		nf+= sizeof(float);
		
		//float       J_oldjly;			//上年此期净利润
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		financeData.J_oldjly = tempFloat;
		nf+= sizeof(float);
		
		//float       J_oldzysy;			//上年此期主营收入
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		financeData.J_oldzysy = tempFloat;
		nf+= sizeof(float);
		
		//float       J_bg;				//B股
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		financeData.J_bg = tempFloat;
		nf+= sizeof(float);
		
		//float       J_hg;				//H股
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		financeData.J_hg = tempFloat;
		nf+= sizeof(float);
		
		//float       J_mgsy2;			//季报每股收益 (财报中提供的每股收益,有争议的才填)
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		financeData.J_mgsy2 = tempFloat;
		nf+= sizeof(float);
		
		//float       J_zzc;				//总资产(千元)
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		financeData.J_zzc = tempFloat*1000;
		nf+= sizeof(float);
		
		//float       J_ldzc;				//流动资产
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		financeData.J_ldzc = tempFloat*1000;
		nf+= sizeof(float);
		
		//float       J_gdzc;				//固定资产
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		financeData.J_gdzc = tempFloat*1000;
		nf+= sizeof(float);
		
		//float       J_wxzc;				//无形资产
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		financeData.J_wxzc = tempFloat*1000;
		nf+= sizeof(float);
		
		//float       J_cqtz;				//长期投资
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		financeData.J_cqtz = tempFloat*1000;
		nf+= sizeof(float);
		
		//float       J_ldfz;				//流动负债
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		financeData.J_ldfz = tempFloat*1000;
		nf+= sizeof(float);
		
		//float       J_cqfz;				//长期负债
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		financeData.J_cqfz = tempFloat*1000;
		nf+= sizeof(float);
		
		//float       J_zbgjj;			//资本公积金
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		financeData.J_zbgjj = tempFloat*1000;
		nf+= sizeof(float);
		
		//float       J_jzc;				//股东权益(就是净资产)
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		financeData.J_jzc = tempFloat*1000;
		nf+= sizeof(float);
		
		//float       J_zysy;				//主营收入
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		financeData.J_zysy = tempFloat*1000;
		nf+= sizeof(float);
		
		//float       J_zyly;				//主营利益
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		financeData.J_zyly = tempFloat*1000;
		nf+= sizeof(float);
		
		//float       J_qtly;				//其它利益
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		financeData.J_qtly = tempFloat*1000;
		nf+= sizeof(float);
		
		//float       J_yyly;				//营业利益
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		financeData.J_yyly = tempFloat*1000;
		nf+= sizeof(float);
		
		//float       J_tzsy;				//投资收益
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		financeData.J_tzsy = tempFloat*1000;
		nf+= sizeof(float);
		
		//float       J_btsy;				//补贴收入
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		financeData.J_btsy = tempFloat*1000;
		nf+= sizeof(float);
		
		//float       J_yywsz;			//营业外收支
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		financeData.J_yywsz = tempFloat*1000;
		nf+= sizeof(float);
		
		//float       J_snsytz;			//上年损益调整
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		financeData.J_snsytz = tempFloat*1000;
		nf+= sizeof(float);
		
		//float       J_lyze;				//利益总额
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		financeData.J_lyze = tempFloat*1000;
		nf+= sizeof(float);
		
		//float       J_shly;				//税后利益
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		financeData.J_shly = tempFloat*1000;
		nf+= sizeof(float);
		
		//float       J_jly;				//净利益
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		financeData.J_jly = tempFloat*1000;
		nf+= sizeof(float);
		
		//float       J_wfply;			//未分配利益
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		financeData.J_wfply = tempFloat*1000;
		nf+= sizeof(float);
		
		//float       J_tzmgjz;			//调整每股净资产 物理意义:  净资产/调整后的总股本
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		financeData.J_tzmgjz = tempFloat;
		nf+= sizeof(float);
		
		//float		J_HalfYearFlag;		//报告期
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		financeData.J_HalfYearFlag = tempFloat;
		nf+= sizeof(float);
		
		[_result setObject:financeData forKey:@"CWSJ"];
		[financeData release];
		
	}
	
	if ((flags & COMBO_MASK_GBBQ) == COMBO_MASK_GBBQ) {
		//NSLog(@"gbbq");
		//int nf = 16;
		//[readData getTdxBytes:&req range:NSMakeRange(buf, sizeof(req))];
		short num =0;
		[theData getTdxBytes:&num range:NSMakeRange(nf, sizeof(short))];
		NSLog(@"the num is %i",num);
		
		nf += sizeof(num);
		
		gbbqArray = [[NSMutableArray alloc]initWithCapacity:num+1];
				
		for (int i = 0 ; i < num; i++) {
			GBBQInfo * tempGBBQ = [[GBBQInfo alloc] init];
			int tempInt=0 ;
			float tempFloat=0.0;
			char tempChar=0;
			
			[theData getTdxBytes:&tempInt range:NSMakeRange(nf, sizeof(int))];
			nf+= sizeof(int);
			tempGBBQ.theDate = tempInt;
			//NSLog([NSString stringWithFormat:@"the date is %i",tempAna.date]);
			
			[theData getTdxBytes:&tempChar range:NSMakeRange(nf, sizeof(char))];
			nf += sizeof(char);
			tempGBBQ.theType = tempChar;
			
			[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
			nf+= sizeof(float);
			tempGBBQ.B01 = tempFloat;
			
			[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
			nf+= sizeof(float);
			tempGBBQ.B02 = tempFloat;
			
			[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
			nf+= sizeof(float);
			tempGBBQ.B03 = tempFloat;
			
			[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
			nf+= sizeof(float);
			tempGBBQ.B04 = tempFloat;
			
			
			[gbbqArray addObject:(GBBQInfo *)tempGBBQ];
			[tempGBBQ release];
		}	
		
		[_result setObject:gbbqArray forKey:@"GBBQ"];
		[gbbqArray release];
		
		
	}
	
	[theData release];
}

-(NSMutableData *) getCombHQReq:(NSString *) gpcode  wantNum:(short)_num{
	NSMutableData *newdata = [[[NSMutableData alloc] init] autorelease];
	short  req = COMBHQ2_5MMP_NREQ;
	[newdata appendBytes:(void *)&req length:sizeof(short)];
	[newdata appendBytes:(void *)&_num length:sizeof(short)];
	[newdata appendData:[gpcode dataUsingEncoding:NSUTF8StringEncoding]];
	
	return newdata;
}
-(void) getCombHQAns:(NSMutableArray *) gridData hqResult:(HqResultData * )_hqresult{
	NSData * theData = [[NSData alloc] initWithData:_hqresult.resultData];
	[gridData removeAllObjects];
	int nf = 16;
	short num =0;
	[theData getTdxBytes:&num range:NSMakeRange(nf, sizeof(short))];
	
	nf += sizeof(num);
	
	for (int i = 0 ; i < num; i++) {
		SinHqInfo * tempInfo = [[SinHqInfo alloc] init];
		
		short tempShort=0;
		int tempInt=0;
		float tempFloat=0.0;
		NSString * tempString;
		[theData getTdxBytes:&tempShort range:NSMakeRange(nf, sizeof(short))];
		tempInfo.setcode = tempShort;
		
		nf += sizeof(short);
		tempString = [[NSString alloc] initWithData:[theData subdataWithRange:NSMakeRange(nf, 6)] encoding:NSUTF8StringEncoding];
		tempInfo.gpcode = [NSString stringWithFormat:@"%@",tempString];
		[tempString release];
		
		nf +=6 ;
		
		tempString = [[NSString alloc] initWithData:[theData subdataWithRange:NSMakeRange(nf, 8)] encoding:CFStringConvertEncodingToNSStringEncoding (kCFStringEncodingGB_18030_2000)];
    	tempInfo.gpname =  [NSString stringWithFormat:@"%@",tempString];
		[tempString release];
		
		tempInfo.zsflag = [self testZS:tempInfo.gpcode setcode:tempInfo.setcode];
		tempInfo.dataPre = [self getDataPre:tempInfo.gpcode];
		
		nf += 8;
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		tempInfo.closeP = tempFloat;
		//open
		nf += sizeof(float);
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		tempInfo.openP = tempFloat;
		//max
		nf += sizeof(float);
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		tempInfo.maxP = tempFloat;
		//min
		nf += sizeof(float);
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		tempInfo.minP = tempFloat;
		//now
		nf += sizeof(float);
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		tempInfo.nowP = tempFloat;
		
		//volumn and nowvol
		nf += sizeof(float);
		[theData getTdxBytes:&tempInt range:NSMakeRange(nf, sizeof(int))];
		tempInfo.volume = tempInt;
		nf += sizeof(int);
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		tempInfo.liangbi = tempFloat;
		
		//amout
		nf += sizeof(int);
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		tempInfo.amount = tempFloat;

        nf += sizeof(float);
		
		[theData getTdxBytes:&tempInt range:NSMakeRange(nf, sizeof(int))];
		tempInfo.inside = tempInt;
		nf += sizeof(int);
		[theData getTdxBytes:&tempInt range:NSMakeRange(nf, sizeof(int))];
		tempInfo.outside = tempInt;
		
		//amout
		nf += sizeof(int);
		for (int i = 0; i<5; i++) {
			[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
			tempString = [[NSString alloc] initWithFormat:@"%f",tempFloat];
			[tempInfo.buyP addObject:tempString];
			[tempString release];
			nf += sizeof(float);
		}
		for (int i = 0; i<5; i++) {
			[theData getTdxBytes:&tempInt range:NSMakeRange(nf, sizeof(int))];
			tempString = [[NSString alloc] initWithFormat:@"%i",tempInt];
			[tempInfo.buyV addObject:tempString];
			[tempString release];
			nf += sizeof(int);
		}
		for (int i = 0; i<5; i++) {
			[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
			tempString = [[NSString alloc] initWithFormat:@"%f",tempFloat];
			[tempInfo.sellP addObject:tempString];
			[tempString release];
			nf += sizeof(float);
		}
		for (int i = 0; i<5; i++) {
			[theData getTdxBytes:&tempInt range:NSMakeRange(nf, sizeof(int))];
			tempString = [[NSString alloc] initWithFormat:@"%i",tempInt];
			[tempInfo.sellV addObject:tempString];
			[tempString release];
			nf += sizeof(int);
		}
		
		
		nf+= 1;
		//财务数据
		//nf+= 20;
		//总股本
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		tempInfo.J_zgb = tempFloat;
		nf += sizeof(float);
		//流通股本
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		tempInfo.ActiveCapital = tempFloat;
		nf += sizeof(float);
		//所属省份
		[theData getTdxBytes:&tempShort range:NSMakeRange(nf, sizeof(short))];
		tempInfo.J_addr = tempShort;
		nf += sizeof(short);
		//所属行业
		[theData getTdxBytes:&tempShort range:NSMakeRange(nf, sizeof(short))];
		tempInfo.J_hy = tempShort;
		nf += sizeof(short);
		//总市值
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		tempInfo.J_zsz = tempFloat;
		nf += sizeof(float);
		//市盈
		[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
		tempInfo.J_syl = tempFloat;
		nf += sizeof(float);
		
		
		if (tempInfo.zsflag) {
			tempInfo.exchange = 0;
		}
		else  {
			if (tempInfo.ActiveCapital > 0) {
				tempInfo.exchange =  (tempInfo.volume*100*100)/(tempInfo.ActiveCapital*10000);
			}
			else {
				tempInfo.exchange =  0.0;
			}
			
			
			
		}
	
        if(tempInfo.nowP > 0.01){
			tempInfo.zad = tempInfo.nowP - tempInfo.closeP;
			tempInfo.zaf  = (tempInfo.nowP - tempInfo.closeP)*100/tempInfo.closeP;
			tempInfo.zef = (tempInfo.maxP - tempInfo.minP)*100/tempInfo.closeP;
		}
		else {
			tempInfo.zef = 0.0f;
			
            float buyPrice = 0.0;
            if([tempInfo.buyP count])
                buyPrice=[[tempInfo.buyP objectAtIndex:0] floatValue];
            float sellPrice = 0.0;
            if([tempInfo.sellP count])
                sellPrice=[[tempInfo.sellP objectAtIndex:0] floatValue];
			
			if ((buyPrice > 0.001)&&(sellPrice > 0.001)&&(ABSOLUTE_VALUE(buyPrice - sellPrice) < 0.001)) {
				tempInfo.zaf  = (buyPrice - tempInfo.closeP)*100/tempInfo.closeP;
				tempInfo.zad = buyPrice - tempInfo.closeP;
			}
			else {
				tempInfo.zaf = 0.0f;
				tempInfo.zad = 0.0f;
			}
			
		}
	
        [gridData  addObject:(SinHqInfo *)tempInfo];
		
		
		[tempInfo release];
	}
	
	[theData release];
}




-(NSMutableData *) getCombHQMaskReq:(NSString *) gpcode  flags:(int) _flags wantNum:(short)_num{
	NSMutableData *newdata = [[[NSMutableData alloc] init] autorelease];
	short  req = COMBHQ_MASK_NREQ;
	
    [newdata appendBytes:(void *)&req length:sizeof(short)];
	[newdata appendBytes:(void *)&_num length:sizeof(short)];
	[newdata appendBytes:(void *)&_flags length:sizeof(int)];
	[newdata appendData:[gpcode dataUsingEncoding:NSUTF8StringEncoding]];
	
	return newdata;
}

-(void) getCombHQMaskAns:(NSMutableArray *) gridData hqResult:(HqResultData * )_hqresult{
	
    NSData * theData = [[NSData alloc] initWithData:_hqresult.resultData];
	
	
	
	int nf = 16;
	short num ;
	[theData getTdxBytes:&num range:NSMakeRange(nf, sizeof(short))];
	
	nf += sizeof(num);
	
	int flags ;
	[theData getTdxBytes:&flags range:NSMakeRange(nf, sizeof(int))];
	
	nf += sizeof(flags);
	
	for (int i = 0 ; i < num; i++) {
		SinHqInfo * tempInfo = [[SinHqInfo alloc] init];
		
		short tempShort=0;
		char tempChar=0;
		int tempInt=0;
		float tempFloat=0;
		NSString * tempString;
		[theData getTdxBytes:&tempShort range:NSMakeRange(nf, sizeof(short))];
		tempInfo.setcode = tempShort;
		
		nf += sizeof(short);
		tempString = [[NSString alloc] initWithData:[theData subdataWithRange:NSMakeRange(nf, 6)] encoding:NSUTF8StringEncoding];
		tempInfo.gpcode = [NSString stringWithFormat:@"%@",tempString];
		[tempString release];
		
		nf +=6 ;
		
		tempString = [[NSString alloc] initWithData:[theData subdataWithRange:NSMakeRange(nf, 8)] encoding:CFStringConvertEncodingToNSStringEncoding (kCFStringEncodingGB_18030_2000)];
    	
        tempInfo.gpname = [NSString stringWithFormat:@"%@",tempString];;
		[tempString release];
		
		tempInfo.zsflag = [self testZS:tempInfo.gpcode setcode:tempInfo.setcode];
		tempInfo.dataPre = [self getDataPre:tempInfo.gpcode];
		
        
		nf += 8;
		
        if ((flags & HQINFO_MASK_CLOSE) == HQINFO_MASK_CLOSE){
			
			[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
			tempInfo.closeP = tempFloat;
			nf += sizeof(float);
		}
		
		//open
		if ((flags & HQINFO_MASK_OPEN) == HQINFO_MASK_OPEN){
			[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
			tempInfo.openP = tempFloat;
			nf += sizeof(float);
		}
		
		//max
		if ((flags & HQINFO_MASK_MAX) == HQINFO_MASK_MAX){
			[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
			tempInfo.maxP = tempFloat;
			nf += sizeof(float);
		}
		//min
		if ((flags & HQINFO_MASK_MIN) == HQINFO_MASK_MIN){
			[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
			tempInfo.minP = tempFloat;
			nf += sizeof(float);
		}
		///now
		if ((flags & HQINFO_MASK_NOW) == HQINFO_MASK_NOW){
			[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
			tempInfo.nowP = tempFloat;
			nf += sizeof(float);
			
			if(tempInfo.nowP > 0.01){
				tempInfo.zad = tempInfo.nowP - tempInfo.closeP;
				tempInfo.zaf  = (tempInfo.nowP - tempInfo.closeP)*100/tempInfo.closeP;
				tempInfo.zef = (tempInfo.maxP - tempInfo.minP)*100/tempInfo.closeP;
			}
			else {
				tempInfo.zad = 0.0f;
				tempInfo.zaf = 0.0f;
				tempInfo.zef = 0.0f;
			}
		}
		
		//volumn and 
		if ((flags & HQINFO_MASK_VOL) == HQINFO_MASK_VOL){
			[theData getTdxBytes:&tempInt range:NSMakeRange(nf, sizeof(int))];
			tempInfo.volume = tempInt;
			nf += sizeof(int);
		}
		
		//nowvol	
		if ((flags & HQINFO_MASK_NOWVOL) == HQINFO_MASK_NOWVOL){
			[theData getTdxBytes:&tempInt range:NSMakeRange(nf, sizeof(int))];
			tempInfo.nowVol = tempInt;
			nf += sizeof(int);
		}
		
		
		//amout
		if ((flags & HQINFO_MASK_AMOUNT) == HQINFO_MASK_AMOUNT){
			[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
			tempInfo.amount = tempFloat;
			nf += sizeof(float);
		}
		
		//inside
		if ((flags & HQINFO_MASK_INSIDE) == HQINFO_MASK_INSIDE){
			[theData getTdxBytes:&tempInt range:NSMakeRange(nf, sizeof(int))];
			tempInfo.inside = tempInt;
			nf += sizeof(int);
		}
		
		//outside
		if ((flags & HQINFO_MASK_OUTSIDE) == HQINFO_MASK_OUTSIDE){
			[theData getTdxBytes:&tempInt range:NSMakeRange(nf, sizeof(int))];
			tempInfo.outside = tempInt;
			nf += sizeof(int);
		}
		
		if ((flags & HQINFO_MASK_ZGB) == HQINFO_MASK_ZGB){
			[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
			tempInfo.J_zgb = tempFloat;
			nf += sizeof(float);
		}
		
		if ((flags & HQINFO_MASK_ACTIVECAPITAL) == HQINFO_MASK_ACTIVECAPITAL){
			[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
			tempInfo.ActiveCapital = tempFloat;
			nf += sizeof(float);
			
			if (tempInfo.zsflag) {
				tempInfo.exchange = 0;
			}
			else  {
				if (tempInfo.ActiveCapital > 0) {
					tempInfo.exchange =  (tempInfo.volume*100*100)/(tempInfo.ActiveCapital*10000);
				}
				else {
					tempInfo.exchange =  0.0;
				}

				
				
			}

			
		}
		
		if ((flags & HQINFO_MASK_JLY) == HQINFO_MASK_JLY){
			[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
			tempInfo.J_jly = tempFloat;
			nf += sizeof(float);
		}
		
		if ((flags & HQINFO_MASK_JZC) == HQINFO_MASK_JZC){
			[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
			tempInfo.J_jzc = tempFloat;
			nf += sizeof(float);
		}
		
		if ((flags & HQINFO_MASK_HALFYEARFLAG) == HQINFO_MASK_HALFYEARFLAG){
			[theData getTdxBytes:&tempChar range:NSMakeRange(nf, sizeof(char))];
			nf += sizeof(char);
		}
		//总市值

		if ((flags & HQINFO_MASK_ZSZ) == HQINFO_MASK_ZSZ){
			[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
			tempInfo.J_zsz = tempFloat;
			nf += sizeof(float);
		}
		//市盈
		if ((flags & HQINFO_MASK_SYL) == HQINFO_MASK_SYL){
			[theData getTdxBytes:&tempFloat range:NSMakeRange(nf, sizeof(float))];
			tempInfo.J_syl = tempFloat;
			nf += sizeof(float);
		}
		
		[gridData  addObject:(SinHqInfo *)tempInfo];
		[tempInfo release];
		
	}
	
	[theData release];
}

-(NSMutableData *) getHisMinuteDataReq : (NSString *) gpcode setcode:(int) setcode theDate:(int)_ldate{
	NSMutableData *newdata = [[[NSMutableData alloc] init] autorelease];
	short  req = HISZST_NREQ;

	[newdata appendBytes:(void *)&req length:sizeof(short)];
	[newdata appendBytes:(void *)&setcode length:sizeof(short)];
	[newdata appendData:[gpcode dataUsingEncoding:NSUTF8StringEncoding]];
	[newdata appendBytes:(void *)&_ldate length:sizeof(int)];
	
	
	return newdata;
}
-(void) getHisMinuteDataAsn :(void *)_pClose dataArray:(NSMutableArray *) ansArray hqResult:(HqResultData * )_hqresult{
	
    NSData * theData = [[NSData alloc] initWithData:_hqresult.resultData];
	
	
	
	int nf = 16;
	
    
	[theData getTdxBytes:_pClose range:NSMakeRange(nf, sizeof(float))];
	
    nf += sizeof(float);
	short num =0;
	[theData getTdxBytes:&num range:NSMakeRange(nf, sizeof(short))];
	
	nf += sizeof(num);
	
	
	
	for (int i = 0 ; i < num; i++) {
		Minute_Unit * tempMin = [[Minute_Unit alloc] init];
		short minute=0 ;
		float now=0.0,average=0.0;
		int nowvol=0;
		
		[theData getTdxBytes:&minute range:NSMakeRange(nf, sizeof(short))];
		tempMin.minute = minute;
		
		nf += sizeof(minute);
		
		[theData getTdxBytes:&now range:NSMakeRange(nf, sizeof(float))];
		tempMin.now = now;
		tempMin.zaf = (now - currHpAns.closeP)*100/currHpAns.closeP;
		
		nf += sizeof(now);
		
		[theData getTdxBytes:&average range:NSMakeRange(nf, sizeof(float))];
		tempMin.average = average;
		
		nf += sizeof(now);
		
		[theData getTdxBytes:&nowvol range:NSMakeRange(nf, sizeof(int))];
		tempMin.nowvol = nowvol;
		
		if(currHpAns.zsflag)  tempMin.nowvol = nowvol / 100;
		
		nf +=sizeof(nowvol);
		
		
		
		[ansArray addObject:tempMin];
		[tempMin release];
	}
	
	[theData release];
	
}



-(NSMutableData *) getPYXGReq:(NSString *) seachString  {
	NSMutableData *newdata = [[[NSMutableData alloc] init] autorelease];
	short  req = PYXG_NREQ;
	short  wantnum = 50;
	char tempchar = 0;
	[newdata appendBytes:(void *)&req length:sizeof(short)];
	[newdata appendBytes:(void *)&wantnum length:sizeof(short)];
	[newdata appendData:[seachString dataUsingEncoding:NSUTF8StringEncoding]];
	if ([newdata length]<12) {
		for (int i=[newdata length]; i<12; i++) {
			[newdata appendBytes:(void *)&tempchar length:sizeof(char)];
		}
	}
	
	
	return newdata;
}

-(BOOL) getPYXGAns:(HqResultData * )_hqresult Result:(NSMutableDictionary *)_result{

	NSData * theData = [[NSData alloc] initWithData:_hqresult.resultData];
	
	
	
	int nf = 16;
	short num=0 ;
	[theData getTdxBytes:&num range:NSMakeRange(nf, sizeof(short))];
	
	nf += sizeof(num);
	
	if (num > 0) {
		NSMutableArray * resultArray = [[NSMutableArray alloc]initWithCapacity:num+1];
		
		for (int i = 0 ; i < num; i++) {
			StockInfo * tempInfo = [[StockInfo alloc] init];
			
			char tempChar=0;
			NSString * tempString;
			[theData getTdxBytes:&tempChar range:NSMakeRange(nf, sizeof(char))];
			tempInfo.setcode = tempChar;
			
			nf += sizeof(char);
			tempString = [[NSString alloc] initWithData:[theData subdataWithRange:NSMakeRange(nf, 6)] encoding:NSUTF8StringEncoding];
			tempInfo.gpcode = tempString;
			[tempString release];
			
			nf +=6 ;
			
			tempString = [[NSString alloc] initWithData:[theData subdataWithRange:NSMakeRange(nf, 8)] encoding:CFStringConvertEncodingToNSStringEncoding (kCFStringEncodingGB_18030_2000)];
			tempInfo.gpname = tempString;
			[tempString release];
			
			nf += 8;
			tempString = [[NSString alloc] initWithData:[theData subdataWithRange:NSMakeRange(nf, 4)] encoding:NSUTF8StringEncoding];
			tempInfo.gpspell = tempString;
			[tempString release];
			
			nf +=4;
			[resultArray  addObject:(StockInfo *)tempInfo];
			[tempInfo release];
			
		}
		[_result setObject:[NSString stringWithFormat:@"%i",_hqresult.resultStat] forKey:@"RESULTSTAT"];
		[_result setObject:[NSString stringWithFormat:@"%i",[resultArray count]] forKey:@"NUM"];
		[_result setObject:resultArray forKey:@"STOCK"];
		[resultArray release];
		
		[theData release];
		return TRUE;
		
	}
	else {
		[_result setObject:@"0" forKey:@"NUM"];
		[theData release];
		return FALSE;
	}

}

-(void) getSCVersionReq : (int) setcode major:(int) _major minor:(int)_minor{
	NSMutableData *newdata = [[NSMutableData alloc] init];
	short  req = COMBTICK_NREQ;
	[newdata appendBytes:(void *)&req length:sizeof(short)];
	[newdata appendBytes:(void *)&setcode length:sizeof(short)];
	[newdata appendBytes:(void *)&_major length:sizeof(short)];
	[newdata appendBytes:(void *)&_minor length:sizeof(short)];
	
    [g_pEComm sendIt:newdata length:[newdata length]];
	[newdata release];
}
-(void) getSCVersionAsn{
	NSData * theData = [[NSData alloc] initWithData:g_pEComm.readData];
	
	
	int nf = 16;
	short majorVer,minorVer,theOffset,updateNum;
	[theData getTdxBytes:&majorVer range:NSMakeRange(nf, sizeof(short))];
	nf+=2;
	[theData getTdxBytes:&minorVer range:NSMakeRange(nf, sizeof(short))];
	nf+=2;
	[theData getTdxBytes:&theOffset range:NSMakeRange(nf, sizeof(short))];
	nf+=2;
	[theData getTdxBytes:&updateNum range:NSMakeRange(nf, sizeof(short))];
	
	[theData release];
} 


-(void) getStockChainReq : (int) setcode offset:(int) _offset wantnum:(int)_wantNum updatetype:(BOOL)_updateNum{
	NSMutableData *newdata = [[NSMutableData alloc] init];
	
	short  req = STKUPDATE_NREQ;
	[newdata appendBytes:(void *)&req length:sizeof(short)];
	[newdata appendBytes:(void *)&setcode length:sizeof(short)];
	[newdata appendBytes:(void *)&_offset length:sizeof(short)];
	[newdata appendBytes:(void *)&_wantNum length:sizeof(short)];
	[newdata appendBytes:(void *)&_updateNum length:sizeof(BOOL)];
	
    [g_pEComm sendIt:newdata length:[newdata length]];
	[newdata release];
}

-(int) getStockChainAsn{
	NSData * theData = [[NSData alloc] initWithData:g_pEComm.readData];
	
	
	int nf = 16;
	int num =0;
	[theData getTdxBytes:&num range:NSMakeRange(nf, sizeof(short))];
	
	nf += sizeof(short);
	
	
	
	for (int i = 0 ; i < num; i++) {
		StockInfo * tempStock = [[StockInfo alloc] init];
		short setcode =0;
		
		[theData getTdxBytes:&setcode range:NSMakeRange(nf, sizeof(short))];
		tempStock.setcode = setcode;
		
		nf += sizeof(setcode);
		
		[tempStock release];
	}
	[theData release];

	return num;
	
}


//信息地雷
-(NSMutableData *) getInfoTitleDataReq:(short)infoType startx:(int)_startx wantnum:(short) num gpcode:(NSString *) _gpcode setcode:(int) _setcode hyStr:(NSString *)_hyStr flStr:(NSString *)_flStr{
	NSMutableData *newdata = [[[NSMutableData alloc] init] autorelease];
	short  req = INFOTITLE_NREQ;
	[newdata appendBytes:(void *)&req length:sizeof(short)];
	char tempType = infoType;
	[newdata appendBytes:(void *)&tempType length:sizeof(char)];
	[newdata appendBytes:(void *)&_startx length:sizeof(int)];
	[newdata appendBytes:(void *)&num length:sizeof(short)];
	
	char tempchar = 0;
	[newdata appendBytes:(void *)&_setcode length:sizeof(short)];
	[newdata appendData:[_gpcode dataUsingEncoding:NSUTF8StringEncoding]];
	if ([newdata length]<22) {
		for (int i=[newdata length]; i<22; i++) {
			[newdata appendBytes:(void *)&tempchar length:sizeof(char)];
		}
	}
	[newdata appendData:[_hyStr dataUsingEncoding:NSUTF8StringEncoding]];
	
	if ([newdata length]<33) {
		for (int i=[newdata length]; i<33; i++) {
			[newdata appendBytes:(void *)&tempchar length:sizeof(char)];
		}
	}
	
	[newdata appendData:[_flStr dataUsingEncoding:NSUTF8StringEncoding]];
	
	
	if ([newdata length]<44) {
		for (int i=[newdata length]; i<44; i++) {
			[newdata appendBytes:(void *)&tempchar length:sizeof(char)];
		}
	}
	
	[newdata appendBytes:(void *)&tempchar length:30];
	
	return newdata;
}

-(void) getInfoTitleDataAns:(HqResultData * )_hqresult Result:(NSMutableDictionary *)_result{
	NSMutableArray * titleArray;	
	NSData * theData = [[NSData alloc] initWithData:_hqresult.resultData];
	
	
	
	int nf = 16;
	int totalNum =0;
	short titleNum=0;
	[theData getTdxBytes:&totalNum range:NSMakeRange(nf, sizeof(int))];
	nf += sizeof(int);
	//起始位置
	nf += sizeof(int);
	[theData getTdxBytes:&titleNum range:NSMakeRange(nf, sizeof(short))];
	NSLog(@"the titleNum  is %i",titleNum);
	[_result setObject:[NSString stringWithFormat:@"%i",_hqresult.resultStat] forKey:@"RESULTSTAT"];
	[_result setObject:[NSString stringWithFormat:@"%i",totalNum] forKey:@"TOTALNUM"];
	[_result setObject:[NSString stringWithFormat:@"%i",titleNum] forKey:@"TITLENUM"];
	nf += sizeof(short);
	
	if (titleNum > 0) {
		titleArray = [[NSMutableArray alloc]initWithCapacity:titleNum+1];
		
		for (int i = 0 ; i < titleNum; i++) {
			MineInfo * tempMine = [[MineInfo alloc]init];
			
			int tempInt=0;
			char tempChar=0;
			NSString * tempString;
			
			
			[theData getTdxBytes:&tempInt range:NSMakeRange(nf, sizeof(int))];
			tempMine.rec_ID = tempInt;
			nf += sizeof(int);
			
			[theData getTdxBytes:&tempInt range:NSMakeRange(nf, sizeof(int))];
			tempMine.time_ymd = tempInt;
			nf += sizeof(int);
			
			[theData getTdxBytes:&tempInt range:NSMakeRange(nf, sizeof(int))];
			tempMine.theTime = tempInt;
			nf += sizeof(int);
			
			tempString = [[NSString alloc] initWithData:[theData subdataWithRange:NSMakeRange(nf, 121)] encoding:CFStringConvertEncodingToNSStringEncoding (kCFStringEncodingGB_18030_2000)];
			tempMine.theTitle =  [NSString stringWithFormat:@"%@",tempString];
			[tempString release];
			nf += 121;
			
			[theData getTdxBytes:&tempInt range:NSMakeRange(nf, sizeof(int))];
			tempMine.type_id = tempInt;
			nf += sizeof(int);
			
			
			[theData getTdxBytes:&tempChar range:NSMakeRange(nf, sizeof(char))];
			tempMine.show_id = tempChar;
			nf += sizeof(char);
			
			[theData getTdxBytes:&tempChar range:NSMakeRange(nf, sizeof(char))];
			tempMine.proc_id = tempChar;
			nf += sizeof(char);
			
			tempString = [[NSString alloc] initWithData:[theData subdataWithRange:NSMakeRange(nf, 31)] encoding:CFStringConvertEncodingToNSStringEncoding (kCFStringEncodingGB_18030_2000)];
			tempMine.infoSrc =  [NSString stringWithFormat:@"%@",tempString];
			[tempString release];
			nf += 31;
			
			[theData getTdxBytes:&tempChar range:NSMakeRange(nf, sizeof(char))];
			tempMine.info_format = tempChar;
			nf += sizeof(char);
			
			tempString = [[NSString alloc] initWithData:[theData subdataWithRange:NSMakeRange(nf, 201)] encoding:CFStringConvertEncodingToNSStringEncoding (kCFStringEncodingGB_18030_2000)];
			tempMine.infoURL =  [NSString stringWithFormat:@"%@",[self trim:tempString]];
			[tempString release];
			nf += 201;
			;
			
			[titleArray addObject:tempMine];
			[tempMine release];
		}	
		
		[_result setObject:titleArray forKey:@"INFOTITLE"];
		[titleArray release];
		
	}
	
	[theData release];
}

-(NSMutableData *) getInfoTextDataReq:(int)flags startx:(int)_startx wantnum:(short) num fileName:(NSString *)_fileName{
	NSMutableData *newdata = [[[NSMutableData alloc] init] autorelease];
	short  req = FILE_NREQ;
	[newdata appendBytes:(void *)&req length:sizeof(short)];
	[newdata appendBytes:(void *)&flags length:sizeof(int)];
	[newdata appendBytes:(void *)&_startx length:sizeof(int)];
	[newdata appendBytes:(void *)&num length:sizeof(int)];
	
	char tempchar = 0;
	[newdata appendData:[_fileName dataUsingEncoding:NSUTF8StringEncoding]];
	if ([newdata length]<114) {
		for (int i=[newdata length]; i<114; i++) {
			[newdata appendBytes:(void *)&tempchar length:sizeof(char)];
		}
	}
	
	return newdata;
}
-(void) getInfoTextDataAns:(HqResultData * )_hqresult Result:(NSMutableDictionary *)_result{
	NSMutableData * theData = [[NSMutableData alloc] initWithData:_hqresult.resultData];
	
	
	int nf = 16;
	int totalNum =0;
	nf += sizeof(int);
	[theData getTdxBytes:&totalNum range:NSMakeRange(nf, sizeof(int))];
	[_result setObject:[NSString stringWithFormat:@"%i",_hqresult.resultStat] forKey:@"RESULTSTAT"];
	[_result setObject:[NSString stringWithFormat:@"%i",totalNum] forKey:@"TOTALNUM"];
	nf += sizeof(int);
	
	[_result setObject:[theData subdataWithRange:NSMakeRange(nf, totalNum)] forKey:@"INFODATA"];
	
	char tempEndChar = '\0';
	char tempChar=0;
	BOOL findEnd = NO;
	int j;
	for (j = nf; j<totalNum; j++) {
		[theData getTdxBytes:&tempChar range:NSMakeRange(nf+j, sizeof(char))];
		if (tempChar == '\0') {
			findEnd = YES;
			break;
		}
	}
	NSString * textString;
	if (findEnd) {
		textString = [[NSString alloc] initWithData:[theData subdataWithRange:NSMakeRange(nf, j)] encoding:CFStringConvertEncodingToNSStringEncoding (kCFStringEncodingGB_18030_2000)];
	}
	else {
		[theData appendBytes:(void *)&tempEndChar length:sizeof(char)];
		textString = [[NSString alloc] initWithData:[theData subdataWithRange:NSMakeRange(nf, totalNum+1)] encoding:CFStringConvertEncodingToNSStringEncoding (kCFStringEncodingGB_18030_2000)];
		
		if (textString == nil) {
			[textString release];
			textString = [[NSString alloc] initWithData:[theData subdataWithRange:NSMakeRange(nf, totalNum-1)] encoding:CFStringConvertEncodingToNSStringEncoding (kCFStringEncodingGB_18030_2000)];
			
		}
	}
	[_result setObject:[NSString stringWithFormat:@"%@",textString] forKey:@"INFOTEXT"];
	[textString release];
	
	[theData release];
}

#pragma mark 交易相关协议
-(void)setExtendHead:(NSMutableData *) newdata Session:(uint64_t)dwEssion transkey:(unsigned long)dtranskey{
	short reqIndex=(dtranskey & 0xFFFF);
	if(reqIndex!=TDX_CHB)
		[clientinfos jyhasoper];
	NSString * tempString;
	char tempByte = 0 ;  //m_ctag
	[newdata appendBytes:(void *)&tempByte length:sizeof(char)];
	tempByte = 1 ;  //m_ckeepalive
	[newdata appendBytes:(void *)&tempByte length:sizeof(char)];
	tempByte = m_compressType ;  //m_compressTyoe
	[newdata appendBytes:(void *)&tempByte length:sizeof(char)];
	tempByte = m_cEncrypted ;  //m_cEncrypted
	[newdata appendBytes:(void *)&tempByte length:sizeof(char)];
	tempByte = 0 ;  //m_utf8encoding
	[newdata appendBytes:(void *)&tempByte length:sizeof(char)];
	[newdata appendBytes:(void *)&dtranskey length:4];
	[newdata appendBytes:(void *)&dwEssion length:sizeof(uint64_t)];
	tempString= @"|";
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	tempString= @"\r\n";
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	
}

-(void)sendTradeQueryData:(short)nIndex pageIndex:(short)pageindex objIndex:(short)windindex Session:(uint64_t)dwEssion StartIndex:(int)startindex ReqLines:(int)reqlines TotleLine:(int)totleline positionstr:(NSString *)posstr
{
	NSMutableData * newdata = [[NSMutableData alloc] init];	
	NSMutableData *headdata=[[NSMutableData alloc] init];
	NSString * tempString;
	switch (nIndex) {
		case TDX_GDCX: { //股东查询
			ASYNC_SENDDATA_START_PAGE
			tempString = [NSString  stringWithFormat:@"FuncID=%i&F110=0&",1122];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            
			ASYNC_SENDDATA_END_PAGE
		}
			break;			
		case TDX_CDCX:
		{
			ASYNC_SENDDATA_START_PAGE
            int ngnid=506;
            if(m_bpcywflag)
                ngnid=1100;
            
			tempString = [NSString  stringWithFormat:@"FuncID=%i&",ngnid];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = @"F1207=0&";
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = @"F110=0&";
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			ASYNC_SENDDATA_PAGE
			ASYNC_SENDDATA_END_PAGE
		}
			break;
        case TDX_DBPHZCDCX:
        {
            ASYNC_SENDDATA_START_PAGE
            
            tempString = [NSString  stringWithFormat:@"FuncID=%i&",3278];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            tempString = @"F1207=P&";
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            tempString = @"F110=WSWT&";
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            ASYNC_SENDDATA_PAGE
            ASYNC_SENDDATA_END_PAGE
        }
            break;
		case TDX_GFCX:
		{
			ASYNC_SENDDATA_START_PAGE
            int ngnid=502;
            if(m_bpcywflag)
                ngnid=1114;
			tempString = [NSString  stringWithFormat:@"FuncID=%i&",ngnid];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			ASYNC_SENDDATA_START_WTFS
			ASYNC_SENDDATA_PAGE
			ASYNC_SENDDATA_END_PAGE
			
		}
			break;	
		case TDX_ZJYE: { //资金余额查询
			ASYNC_SENDDATA_START_PAGE
            int ngnid=504;
            if(m_bpcywflag)
                ngnid=104;

			tempString = [NSString  stringWithFormat:@"FuncID=%i&",ngnid];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = @"F110=0&F132=-1&";
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			ASYNC_SENDDATA_PAGE
			ASYNC_SENDDATA_END_PAGE
		}
			break;
        case TDX_DZJZHCX: { //多资金帐号查询
            ASYNC_SENDDATA_START_PAGE
            int ngnid=1176;
            
            tempString = [NSString  stringWithFormat:@"FuncID=%i&",ngnid];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];

            ASYNC_SENDDATA_PAGE
            ASYNC_SENDDATA_END_PAGE
        }
            break;
		case TDX_DRWT:
		{
			ASYNC_SENDDATA_START_PAGE
            int ngnid=508;
            if(m_bpcywflag)
                ngnid=1102;
			tempString = [NSString  stringWithFormat:@"FuncID=%i&",ngnid];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = @"F1207=0&";
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = @"F110=0&";
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			ASYNC_SENDDATA_PAGE
			ASYNC_SENDDATA_END_PAGE
		}
			break;
		case TDX_DRCJ:
		{
			ASYNC_SENDDATA_START_PAGE
			ASYNC_SENDDATA_PAGE
            
            int ngnid=510;
            if(m_bpcywflag)
                ngnid=1108;
			tempString = [NSString  stringWithFormat:@"FuncID=%i&F1207=0&F110=0&",ngnid];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			ASYNC_SENDDATA_PAGE
			ASYNC_SENDDATA_END_PAGE
		}
			break;	
		case TDX_LSWT:
		{
			ASYNC_SENDDATA_START_PAGE
            
            int ngnid=522;
            if(m_bpcywflag)
                ngnid=1104;
			tempString = [NSString  stringWithFormat:@"FuncID=%i&",ngnid];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = @"F1207=0&";
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = @"F110=0&";
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			ASYNC_SENDDATA_START_LSDATE
			ASYNC_SENDDATA_PAGE
			ASYNC_SENDDATA_END_PAGE
		}
			break;
		case TDX_LSCJ:
		{
			ASYNC_SENDDATA_START_PAGE
			ASYNC_SENDDATA_PAGE
            
            int ngnid=524;
            if(m_bpcywflag)
                ngnid=1110;
			tempString = [NSString  stringWithFormat:@"FuncID=%i&F1207=0&F110=0&",ngnid];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			ASYNC_SENDDATA_START_LSDATE
			ASYNC_SENDDATA_PAGE
			ASYNC_SENDDATA_END_PAGE
		}
			break;	
		case TDX_CJHZ:
		{
			ASYNC_SENDDATA_START_PAGE
			ASYNC_SENDDATA_PAGE
            int ngnid=1138;

			tempString = [NSString  stringWithFormat:@"FuncID=%i&F1207=0&F110=0&",ngnid];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			ASYNC_SENDDATA_START_LSDATE
			ASYNC_SENDDATA_PAGE
			ASYNC_SENDDATA_END_PAGE
		}
			break;
		case TDX_ZJLS:
		{
			ASYNC_SENDDATA_START_PAGE
			ASYNC_SENDDATA_PAGE
            int ngnid=514;
            if(m_bpcywflag)
                ngnid=1118;
			tempString = [NSString  stringWithFormat:@"FuncID=%i&F1207=0&F110=0&",ngnid];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            tempString = [NSString  stringWithFormat:@"F132=%d&",saveDate.nzjlsBZ];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			ASYNC_SENDDATA_START_LSDATE
			ASYNC_SENDDATA_PAGE
			ASYNC_SENDDATA_END_PAGE
		}
			break;
        case TDX_XGSG:
        {
            ASYNC_SENDDATA_START_PAGE
            ASYNC_SENDDATA_PAGE
            
            int ngnid=526;
            if(m_bpcywflag)
                ngnid=1116;
            tempString = [NSString  stringWithFormat:@"FuncID=%i&F1207=0&F110=0&",ngnid];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            ASYNC_SENDDATA_START_LSDATE
            ASYNC_SENDDATA_PAGE
            ASYNC_SENDDATA_END_PAGE
        }
		case TDX_PHCX:
		{
			ASYNC_SENDDATA_START_PAGE
			ASYNC_SENDDATA_PAGE
            
            int ngnid=526;
            if(m_bpcywflag)
                ngnid=1116;
			tempString = [NSString  stringWithFormat:@"FuncID=%i&F1207=0&F110=0&",ngnid];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			ASYNC_SENDDATA_START_LSDATE
			ASYNC_SENDDATA_PAGE
			ASYNC_SENDDATA_END_PAGE
		}
			break;
        case TDX_XGSGDJKCX:
        {
            ASYNC_SENDDATA_START_PAGE
            ASYNC_SENDDATA_PAGE
            
            int ngnid=1370;
            tempString = [NSString  stringWithFormat:@"FuncID=%i&F1207=0&F110=0&",ngnid];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            ASYNC_SENDDATA_START_LSDATE
            ASYNC_SENDDATA_PAGE
            ASYNC_SENDDATA_END_PAGE
        }
            break;
        case    TDX_IPOSGED:
        {
            ASYNC_SENDDATA_START_PAGE
			ASYNC_SENDDATA_PAGE
			tempString = [NSString  stringWithFormat:@"FuncID=%i&F1207=0&F110=0&",1340];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			ASYNC_SENDDATA_START_LSDATE
			ASYNC_SENDDATA_PAGE
			ASYNC_SENDDATA_END_PAGE
        }
            break;
		case TDX_ZZCX:
		{
			ASYNC_SENDDATA_START_PAGE
			ASYNC_SENDDATA_PAGE
            int ngnid=512;
            if(m_bpcywflag)
                ngnid=902;
			tempString = [NSString  stringWithFormat:@"FuncID=%i&F1207=0&F110=0&",ngnid];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			ASYNC_SENDDATA_START_LSDATE
			ASYNC_SENDDATA_START_YHDM
			ASYNC_SENDDATA_PAGE
			ASYNC_SENDDATA_END_PAGE
		}
			break;	
		case TDX_CJCX:
		{
			ASYNC_SENDDATA_START_PAGE
			tempString = [NSString stringWithFormat:@"FUNCID=%i&",536];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			ASYNC_SENDDATA_START_WTFS
			ASYNC_SENDDATA_PAGE
			ASYNC_SENDDATA_END_PAGE
			
		}
			break;
		case TDX_ZHCX:
		{
			ASYNC_SENDDATA_START_PAGE
			tempString = [NSString stringWithFormat:@"FUNCID=%i&",540];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			ASYNC_SENDDATA_START_WTFS
			ASYNC_SENDDATA_PAGE
			ASYNC_SENDDATA_END_PAGE
		}
			break;
		case TDX_GSCX:
		case TDX_LCGSCX:
		{
			ASYNC_SENDDATA_START_PAGE
			tempString = [NSString stringWithFormat:@"FUNCID=%i&",542];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			ASYNC_SENDDATA_START_WTFS
			ASYNC_SENDDATA_PAGE
			ASYNC_SENDDATA_END_PAGE
			
		}
			break;
		case TDX_FECX:
		{
			ASYNC_SENDDATA_START_PAGE
			tempString = [NSString stringWithFormat:@"FUNCID=%i&",546];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			ASYNC_SENDDATA_START_WTFS
			ASYNC_SENDDATA_PAGE
			ASYNC_SENDDATA_END_PAGE
			
		}
			break;
		case TDX_LCFECX:
		{
			ASYNC_SENDDATA_START_PAGE
			tempString = [NSString stringWithFormat:@"FUNCID=%i&",2200];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			ASYNC_SENDDATA_START_WTFS
			ASYNC_SENDDATA_PAGE
			ASYNC_SENDDATA_END_PAGE
			
		}
			break;
		case TDX_JJWT:
		{
			ASYNC_SENDDATA_START_PAGE
			tempString = [NSString stringWithFormat:@"FUNCID=%i&",532];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			ASYNC_SENDDATA_START_WTFS
			ASYNC_SENDDATA_PAGE
			ASYNC_SENDDATA_END_PAGE
		}
			break;
		case TDX_LCWTCX:
		{
			ASYNC_SENDDATA_START_PAGE
			tempString = [NSString stringWithFormat:@"FUNCID=%i&",2206];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			ASYNC_SENDDATA_START_WTFS
			ASYNC_SENDDATA_PAGE
			ASYNC_SENDDATA_END_PAGE
		}
			break;
		case TDX_LCLSWTCX:
		{
			ASYNC_SENDDATA_START_PAGE
			tempString = [NSString stringWithFormat:@"FUNCID=%i&",2202];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			ASYNC_SENDDATA_START_WTFS
			ASYNC_SENDDATA_START_LSDATE
			ASYNC_SENDDATA_PAGE
			ASYNC_SENDDATA_END_PAGE
		}
			break;
		case TDX_LCCJCX:
		{
			ASYNC_SENDDATA_START_PAGE
			tempString = [NSString stringWithFormat:@"FUNCID=%i&",2204];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			ASYNC_SENDDATA_START_WTFS
			ASYNC_SENDDATA_START_LSDATE
			ASYNC_SENDDATA_PAGE
			ASYNC_SENDDATA_END_PAGE
		}
			break;
		case TDX_WTCX_HK:
		{
			ASYNC_SENDDATA_START_PAGE
			tempString = [NSString stringWithFormat:@"FUNCID=%i&",1104];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			ASYNC_SENDDATA_START_WTFS
			ASYNC_SENDDATA_START_LSDATE
			ASYNC_SENDDATA_PAGE
			ASYNC_SENDDATA_END_PAGE
		}
			break;
		case TDX_WTCX:
		{
			ASYNC_SENDDATA_START_PAGE
			tempString = [NSString stringWithFormat:@"FUNCID=%i&",534];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			ASYNC_SENDDATA_START_WTFS
			ASYNC_SENDDATA_START_LSDATE
			ASYNC_SENDDATA_PAGE
			ASYNC_SENDDATA_END_PAGE
		}
			break;
		case TDX_JJDRWTCX:
		{
			ASYNC_SENDDATA_START_PAGE
			tempString = [NSString stringWithFormat:@"FUNCID=%i&",532];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			ASYNC_SENDDATA_START_WTFS
			ASYNC_SENDDATA_PAGE
			ASYNC_SENDDATA_END_PAGE
		}
			break;
		case TDX_JJFJYDRWTCX:
		{
			ASYNC_SENDDATA_START_PAGE
			tempString = [NSString stringWithFormat:@"FUNCID=%i&",2164];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			ASYNC_SENDDATA_START_WTFS
			ASYNC_SENDDATA_PAGE
			ASYNC_SENDDATA_END_PAGE
		}
			break;
		case TDX_JJFJYLSWTCX:
		{
			ASYNC_SENDDATA_START_PAGE
			tempString = [NSString stringWithFormat:@"FUNCID=%i&",2162];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			ASYNC_SENDDATA_START_WTFS
			ASYNC_SENDDATA_START_LSDATE
			ASYNC_SENDDATA_PAGE
			ASYNC_SENDDATA_END_PAGE
		}
			break;
		case TDX_JJLSCJCX:
		{
			ASYNC_SENDDATA_START_PAGE
			tempString = [NSString stringWithFormat:@"FUNCID=%i&",538];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			ASYNC_SENDDATA_START_WTFS
			ASYNC_SENDDATA_START_LSDATE
			ASYNC_SENDDATA_PAGE
			ASYNC_SENDDATA_END_PAGE
		}
			break;
		case TDX_CJCX_HK:
		{
			ASYNC_SENDDATA_START_PAGE
			tempString = [NSString stringWithFormat:@"FUNCID=%i&",1110];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			ASYNC_SENDDATA_START_WTFS
			ASYNC_SENDDATA_START_LSDATE
			ASYNC_SENDDATA_PAGE
			ASYNC_SENDDATA_END_PAGE
		}
			break;
		case TDX_GFBD_HK:
		{
			ASYNC_SENDDATA_START_PAGE
			tempString = [NSString stringWithFormat:@"FUNCID=%i&",1132];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			ASYNC_SENDDATA_START_WTFS
			ASYNC_SENDDATA_START_LSDATE
			ASYNC_SENDDATA_PAGE
			ASYNC_SENDDATA_END_PAGE
		}
			break;
		case TDX_ZJLS_HK:
		{
			ASYNC_SENDDATA_START_PAGE
			tempString = [NSString stringWithFormat:@"FUNCID=%i&",1118];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			ASYNC_SENDDATA_START_WTFS
			ASYNC_SENDDATA_START_LSDATE
			ASYNC_SENDDATA_PAGE
			ASYNC_SENDDATA_END_PAGE
		}
			break;
		case TDX_IPOLB_HK:
		{
			ASYNC_SENDDATA_START_PAGE
			tempString = [NSString stringWithFormat:@"FUNCID=%i&",1156];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			ASYNC_SENDDATA_START_WTFS
			ASYNC_SENDDATA_START_LSDATE
			ASYNC_SENDDATA_PAGE
			ASYNC_SENDDATA_END_PAGE
		}
			break;
		case TDX_IPOPH_HK:
		{
			ASYNC_SENDDATA_START_PAGE
			tempString = [NSString stringWithFormat:@"FUNCID=%i&",1116];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			ASYNC_SENDDATA_START_WTFS
			ASYNC_SENDDATA_START_LSDATE
			ASYNC_SENDDATA_PAGE
			ASYNC_SENDDATA_END_PAGE
			
		}
            break;
		case TDX_DMCX:
		{
			ASYNC_SENDDATA_START_PAGE
			tempString = [NSString stringWithFormat:@"FUNCID=%i&",544];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			ASYNC_SENDDATA_START_WTFS
			ASYNC_SENDDATA_PAGE			
			ASYNC_SENDDATA_END_PAGE
		}
			break;
		case TDX_LCDMCX:
		{
			ASYNC_SENDDATA_START_PAGE
			tempString = [NSString stringWithFormat:@"FUNCID=%i&",2208];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			ASYNC_SENDDATA_START_WTFS
			ASYNC_SENDDATA_PAGE			
			ASYNC_SENDDATA_END_PAGE
		}
			break;
		case TDX_LCZHCX:
		{
			ASYNC_SENDDATA_START_PAGE
			tempString = [NSString stringWithFormat:@"FUNCID=%i&",2210];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			ASYNC_SENDDATA_START_WTFS
			ASYNC_SENDDATA_PAGE
			ASYNC_SENDDATA_END_PAGE
		}
			break;
		case TDX_JJDQSGCX:
		{
			ASYNC_SENDDATA_START_PAGE
			tempString = [NSString stringWithFormat:@"FUNCID=%i&",2160];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			ASYNC_SENDDATA_START_WTFS
			ASYNC_SENDDATA_PAGE
			ASYNC_SENDDATA_END_PAGE
			
		}
			break;
		case TDX_LCDQSGCX:
		{
			ASYNC_SENDDATA_START_PAGE
			tempString = [NSString stringWithFormat:@"FUNCID=%i&",2212];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			ASYNC_SENDDATA_START_WTFS
			ASYNC_SENDDATA_PAGE
			ASYNC_SENDDATA_END_PAGE
			
		}
			break;
		case TDX_JJFXCPXX:
		{
			ASYNC_SENDDATA_START_PAGE
			tempString = [NSString stringWithFormat:@"FUNCID=%i&F234=0&",2144];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			ASYNC_SENDDATA_START_WTFS
			ASYNC_SENDDATA_PAGE
			ASYNC_SENDDATA_END_PAGE
		}
			break;
        case TDX_XYBDZQCX:
        {
#ifdef IMAC_GDZQ
            ASYNC_SENDDATA_START
            tempString = [NSString  stringWithFormat:@"FuncID=%i&F110=0&",1114];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            ASYNC_SENDDATA_END
#else
            ASYNC_SENDDATA_START_PAGE
            tempString = [NSString stringWithFormat:@"FUNCID=%i&",3216];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            ASYNC_SENDDATA_START_WTFS
            ASYNC_SENDDATA_START_LSDATE
            ASYNC_SENDDATA_PAGE
            ASYNC_SENDDATA_END_PAGE
#endif

        }
            break;
            
        case TDX_XYMCCX:
        {
            BOOL isQs = NO;
            int funid = 0;
#ifdef IMAC_GDZQ
            funid = 3226;
            isQs = YES;
#endif
            
#ifdef IMAC_PAZQ
            funid = 3202;
            isQs = YES;
#endif
            
            if(isQs)
            {
                ASYNC_SENDDATA_START_PAGE
                tempString = [NSString stringWithFormat:@"FUNCID=%i&",funid];
                [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
                ASYNC_SENDDATA_START_WTFS
                ASYNC_SENDDATA_START_LSDATE
                ASYNC_SENDDATA_PAGE
                ASYNC_SENDDATA_END_PAGE
            }
            else
            {
                ASYNC_SENDDATA_START_PAGE
                tempString = [NSString stringWithFormat:@"FUNCID=%i&",3232];
                [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
                tempString = [NSString  stringWithFormat:@"F1207=P&F110=7&"];
                [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
                tempString = [NSString  stringWithFormat:@"F130=70&"];
                [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
                tempString = [NSString  stringWithFormat:@"F5250=%@&F5260=0&F5251=1&F5265=XYJY&",inputSave.accout];
                [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
                ASYNC_SENDDATA_START_LSDATE
                ASYNC_SENDDATA_PAGE
                ASYNC_SENDDATA_END_PAGE
            }
            
            break;
        }
        case TDX_XYMQHQCX:
        case TDX_XYXQHQCX:
        {
    #ifdef IMAC_GDZQ
            ASYNC_SENDDATA_START_PAGE
            tempString = [NSString stringWithFormat:@"FUNCID=%i&",3226];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            ASYNC_SENDDATA_START_WTFS
            ASYNC_SENDDATA_START_LSDATE
            ASYNC_SENDDATA_PAGE
            ASYNC_SENDDATA_END_PAGE
    #else
            ASYNC_SENDDATA_START_PAGE
            tempString = [NSString stringWithFormat:@"FUNCID=%i&",3204];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            ASYNC_SENDDATA_START_WTFS
            ASYNC_SENDDATA_START_LSDATE
            ASYNC_SENDDATA_PAGE
            ASYNC_SENDDATA_END_PAGE
    #endif

        }
            break;
        case TDX_XYZCCX:
        {
            ASYNC_SENDDATA_START_PAGE
            tempString = [NSString stringWithFormat:@"FUNCID=%i&",3200];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            ASYNC_SENDDATA_START_WTFS
            ASYNC_SENDDATA_START_LSDATE
            ASYNC_SENDDATA_PAGE
            ASYNC_SENDDATA_END_PAGE
        }
            break;
        case TDX_XYFZCX:
        {
            ASYNC_SENDDATA_START_PAGE
            tempString = [NSString stringWithFormat:@"FUNCID=%i&",3210];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            ASYNC_SENDDATA_START_WTFS
            ASYNC_SENDDATA_START_LSDATE
            ASYNC_SENDDATA_PAGE
            ASYNC_SENDDATA_END_PAGE
        }
            break;
        case TDX_XYSXCX:
        {
            ASYNC_SENDDATA_START_PAGE
            tempString = [NSString stringWithFormat:@"FUNCID=%i&",3208];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            tempString = @"F1207=P&";
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            tempString = @"F110=WSWT&";
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            ASYNC_SENDDATA_PAGE
            ASYNC_SENDDATA_END_PAGE
        }
            break;
        case TDX_XYRZHYCX:
        {
            ASYNC_SENDDATA_START_PAGE
            tempString = [NSString stringWithFormat:@"FUNCID=%i&",3274];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            ASYNC_SENDDATA_START_WTFS
            ASYNC_SENDDATA_START_LSDATE
            ASYNC_SENDDATA_PAGE
            ASYNC_SENDDATA_END_PAGE
        }
            break;
        case TDX_XYRQHYCX:
        {
            ASYNC_SENDDATA_START_PAGE
            tempString = [NSString stringWithFormat:@"FUNCID=%i&",3276];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            ASYNC_SENDDATA_START_WTFS
            ASYNC_SENDDATA_START_LSDATE
            ASYNC_SENDDATA_PAGE
            ASYNC_SENDDATA_END_PAGE
        }
            break;
        case TDX_XYDBPZQCX:
        {
            ASYNC_SENDDATA_START_PAGE
            tempString = [NSString stringWithFormat:@"FUNCID=%i&",3220];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            ASYNC_SENDDATA_START_WTFS
            ASYNC_SENDDATA_START_LSDATE
            ASYNC_SENDDATA_PAGE
            ASYNC_SENDDATA_END_PAGE
        }
            break;
        case TDX_XGZQCX:
        {
            ASYNC_SENDDATA_START_PAGE
            tempString = [NSString stringWithFormat:@"FUNCID=%i&",1126];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            ASYNC_SENDDATA_START_WTFS
            ASYNC_SENDDATA_START_LSDATE
            ASYNC_SENDDATA_PAGE
            ASYNC_SENDDATA_END_PAGE
        }
            break;
        case TDX_DBPHZ:
        {
            ASYNC_SENDDATA_START_PAGE
            tempString = [NSString stringWithFormat:@"FUNCID=%i&",3240];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            tempString = [NSString  stringWithFormat:@"F1207=P&F110=7&"];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            tempString = [NSString  stringWithFormat:@"F5250=%@&F5260=0&F5251=1&F5251=XYJY&",inputSave.accout];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            if (HZFX==HRXY) {
                tempString = [NSString  stringWithFormat:@"F166=0&"];
                [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            }
            else{
                tempString = [NSString  stringWithFormat:@"F166=1&"];
                [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
                
            }
            ASYNC_SENDDATA_START_GDDM
            ASYNC_SENDDATA_START_WTFS
            ASYNC_SENDDATA_START_LSDATE
            ASYNC_SENDDATA_PAGE
            ASYNC_SENDDATA_END_PAGE
        }
            break;
     
        default:
			break;
	}
	[newdata release];
	[headdata release];
}
	   
-(void)sendTradeBankData:(short)nIndex objIndex:(short)windindex Session:(uint64_t)dwEssion SecPassword:(NSString *)secpass TransferType:(int)transtype BankCode:(NSString *)yhdm BankPassword:(NSString *)yhmm MoneyNum:(NSString *)money BankID:(NSString *)yhzh MoneyType:(int)moneyType
{
	NSMutableData *newdata = [[NSMutableData alloc] init];	
	NSMutableData *headdata=[[NSMutableData alloc] init];
	NSString * tempString;
	switch (nIndex) {
		case TDX_YHYE:
		{
			ASYNC_SENDDATA_START1
			tempString = [NSString  stringWithFormat:@"FuncID=%i&",904];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString stringWithFormat:@"F135=%@&",secpass];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString stringWithFormat:@"F1101=%@&",yhdm];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString stringWithFormat:@"F1104=%@&",yhmm];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString stringWithFormat:@"F1103=%@&",yhzh];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            int nczbz=1;
#ifdef IMAC_ZXJT
            nczbz=0;
#endif
#ifdef IMAC_ZSZQ
            nczbz=0;
#endif
#ifdef IMAC_HXZQ
            nczbz=0;
#endif
			tempString = [NSString stringWithFormat:@"F132=%i&F113=%i&",moneyType,nczbz];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			ASYNC_SENDDATA_END
		}
			break;
		case TDX_YZZZ:
		{
			ASYNC_SENDDATA_START
			tempString = [NSString  stringWithFormat:@"FuncID=%i&",900];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			ASYNC_SENDDATA_START_WTFS
			ASYNC_SENDDATA_START_GDDM
			tempString = [NSString stringWithFormat:@"F135=%@&",secpass];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString stringWithFormat:@"F1101=%@&",yhdm];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString stringWithFormat:@"F1104=%@&",yhmm];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString stringWithFormat:@"F1103=%@&",yhzh];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString stringWithFormat:@"F1108=%i&",transtype];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString stringWithFormat:@"F1107=%@&",money];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString stringWithFormat:@"F132=%i&F113=0&",moneyType];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			ASYNC_SENDDATA_END
		}
			break;
        case TDX_PT_DZJZJGJ:
        {
            ASYNC_SENDDATA_START
            tempString = [NSString  stringWithFormat:@"FuncID=%i&",132];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            ASYNC_SENDDATA_START_WTFS
            ASYNC_SENDDATA_START_GDDM
            tempString = [NSString stringWithFormat:@"F110=%@&",@"7"];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            tempString = [NSString stringWithFormat:@"F228=%@&",yhdm];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            tempString = [NSString stringWithFormat:@"F229=%@&",yhmm];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            tempString = [NSString stringWithFormat:@"F1108=%i&",transtype];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            tempString = [NSString stringWithFormat:@"F132=%i&",moneyType];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            ASYNC_SENDDATA_END
        }
            break;
        case TDX_PT_DZJZZ:
        {
            ASYNC_SENDDATA_START
            tempString = [NSString  stringWithFormat:@"FuncID=%i&",134];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            ASYNC_SENDDATA_START_WTFS
            ASYNC_SENDDATA_START_GDDM
            tempString = [NSString stringWithFormat:@"F110=%@&",@"7"];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            tempString = [NSString stringWithFormat:@"F228=%@&",yhdm];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            tempString = [NSString stringWithFormat:@"F229=%@&",yhmm];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            tempString = [NSString stringWithFormat:@"F1108=%i&",transtype];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            tempString = [NSString stringWithFormat:@"F1107=%@&",money];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            tempString = [NSString stringWithFormat:@"F132=%i&",moneyType];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            ASYNC_SENDDATA_END
        }
            break;
		default:
			break;
	}
	[newdata release];
	[headdata release];
}

-(void)sendTradeBankData2:(short)nIndex objIndex:(short)windindex Session:(uint64_t)dwEssion SecPassword:(NSString *)secpass TransferType:(int)transtype BankCode:(NSString *)yhdm BankPassword:(NSString *)yhmm MoneyNum:(NSString *)money BankID:(NSString *)yhzh MoneyType:(int)moneyType czbz:(int)nczbz yhlsh:(NSString *)strlsh
{
	NSMutableData *newdata = [[NSMutableData alloc] init];
	NSMutableData *headdata=[[NSMutableData alloc] init];
	NSString * tempString;
	switch (nIndex) {
		case TDX_YHYE:
        case TDX_YHYE2:
		{
			ASYNC_SENDDATA_START1
			tempString = [NSString  stringWithFormat:@"FuncID=%i&",904];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString stringWithFormat:@"F135=%@&",secpass];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString stringWithFormat:@"F1101=%@&",yhdm];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString stringWithFormat:@"F1104=%@&",yhmm];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString stringWithFormat:@"F1103=%@&",yhzh];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
         	tempString = [NSString stringWithFormat:@"F132=%i&F113=%i&F1106=%@&",moneyType,nczbz,strlsh];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			ASYNC_SENDDATA_END
		}
			break;
        case TDX_YHYE3:
        {
            ASYNC_SENDDATA_START1
            tempString = [NSString  stringWithFormat:@"FuncID=%i&",948];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            tempString = [NSString stringWithFormat:@"F135=%@&",secpass];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            tempString = [NSString stringWithFormat:@"F1101=%@&",yhdm];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            tempString = [NSString stringWithFormat:@"F132=%i&F113=%i&F1106=%@&",moneyType,nczbz,strlsh];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            ASYNC_SENDDATA_END
        }
            break;
        default:
			break;
    }
    [newdata release];
	[headdata release];
}

-(void)genReloginData:(NSMutableData*)headdata
{
	NSString * tempString;
	NSMutableData * newdata = [[NSMutableData alloc] init];
	
	[self setExtendHead:headdata Session:0 transkey:[self makedword:TDX_KHXY high:g_TradeComm.loginwindindex]];
	
	ASYNC_SENDDATA_START2
    
	tempString = [NSString  stringWithFormat:@"F123=%@&",inputSave.accout];
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
#ifdef IMAC_TPY
	tempString = [NSString  stringWithFormat:@"FuncID=%i&F1206=20&F1292=%@&",100,[self GetMachinInfo]];
#else
    tempString = [NSString  stringWithFormat:@"FuncID=%i&F1206=39&F1292=%@&F1300=%@&",100,[self GetMachinInfo],@"6.01"];
#endif
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	ASYNC_SENDDATA_START_AUTHPASS
	tempString = [NSString  stringWithFormat:@"F1248=%@&F1214=1&",[self GetReloginSessionString]];
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	ASYNC_SENDDATA_END1
	
	[newdata release];
}

-(void)sendTradePasswordData:(short)nIndex objIndex:(short)windindex Session:(uint64_t)dwEssion  OldPassword:(NSString *)_oldPassword NewPassword:(NSString *)_newPassword {
	NSMutableData * newdata = [[NSMutableData alloc] init];
	NSMutableData * headdata = [[NSMutableData alloc] init];
	NSString * tempString;
	[self setExtendHead:headdata Session:dwEssion transkey:[self makedword:nIndex high:windindex]];
    
    
	tempString = [NSString  stringWithFormat:@"FUNCTYPE=0&BranchID=%@&MAC=%@&",inputSave.branchId,g_TradeComm.m_macsstr];
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	tempString = [NSString  stringWithFormat:@"F120=%@&",inputSave.accout];
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
    
    switch (nIndex)
    {
        case TDX_XGMM: //交易密码
        {
            tempString = [NSString  stringWithFormat:@"FuncID=%i&F110=0&",106];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            
            tempString = [NSString  stringWithFormat:@"F134=%@&",_oldPassword];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            tempString = [NSString  stringWithFormat:@"F136=%@&",_newPassword];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            ASYNC_SENDDATA_END
            
            break;
        }
        case TDX_XGZJMM: //资金密码
        {
            tempString = [NSString  stringWithFormat:@"FuncID=%i&F110=0&",108];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            
            tempString = [NSString  stringWithFormat:@"F135=%@&",_oldPassword];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            tempString = [NSString  stringWithFormat:@"F137=%@&",_newPassword];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            ASYNC_SENDDATA_END
            
            break;
        }
        default:
            break;
    }
	
	[newdata release];
	[headdata release];
}

-(void)sendTradeWTData:(short)nIndex objIndex:(short)windindex Session:(uint64_t)dwEssion yzm:(NSString *)yzmstr
{
	NSMutableData * newdata = [[NSMutableData alloc] init];
	NSMutableData * headdata = [[NSMutableData alloc] init];
	NSString * tempString;
	
    
	switch (nIndex) {
	    case TDX_SSLSHAKE:
        {
            [self setExtendHead:headdata Session:dwEssion transkey:[self makedword:nIndex high:windindex]];
			tempString = [NSString  stringWithFormat:@"skey=%@&",yzmstr];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			ASYNC_SENDDATA_END
        }
            break;
    }
    [newdata release];
	[headdata release];
}


-(void)sendTradeQueryData:(short)nIndex objIndex:(short)windindex Session:(uint64_t)dwEssion
{
	NSMutableData * newdata = [[NSMutableData alloc] init];
	NSMutableData * headdata = [[NSMutableData alloc] init];
	NSString * tempString;
	
	switch (nIndex) {
		case TDX_CHB:
		{  //存活包
			ASYNC_SENDDATA_START
			tempString = [NSString  stringWithFormat:@"FuncID=%i&F110=0&",0];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			ASYNC_SENDDATA_END
		}
			break;
		case TDX_LXCX:
		{
			ASYNC_SENDDATA_START
			tempString = [NSString  stringWithFormat:@"FuncID=%i&F113=0&",2118];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			ASYNC_SENDDATA_END
		}
			break;
		case TDX_YECX:
		{
			ASYNC_SENDDATA_START
			tempString = [NSString  stringWithFormat:@"FuncID=%i&",504];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			ASYNC_SENDDATA_START_WTFS
			ASYNC_SENDDATA_END
		}
			break;
		case TDX_KHXY:{  //客户校验
			ASYNC_SENDDATA_START

        	tempString = [NSString  stringWithFormat:@"F123=%@&",inputSave.accout];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			inputSave.nreloginaccoutType=inputSave.accoutType;
#ifdef IMAC_TPY
			tempString = [NSString  stringWithFormat:@"FuncID=%i&F125=8&F1206=20&F1292=%@&",100,[self GetMachinInfo]];//12要换成39
#else
            tempString = [NSString  stringWithFormat:@"FuncID=%i&F125=8&F1206=39&F1292=%@&F1300=%@&",100,[self GetMachinInfo],@"6.01"];//12要换成39

#endif
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            
            JyConfig *pconfig=[clientinfos.qsconfigs.jyconfigs objectAtIndex:0];
            BOOL bmacver=NO;
            if(pconfig && [pconfig.fversion_mac length] && [pconfig.assversion_mac length])
                bmacver=YES;
            if(bmacver)
                tempString = [NSString  stringWithFormat:@"F1300=%@.%@&",pconfig.fversion_mac,pconfig.assversion_mac];
            else
                tempString = [NSString  stringWithFormat:@"F1300=%@.%@&",pconfig.fversion,pconfig.assversion];
            
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            
            
			ASYNC_SENDDATA_START_AUTHPASS
            ASYNC_SENDDATA_END
        }
			break;
	case TDX_SSLTOUCH:
        {
            [self setExtendHead:headdata Session:dwEssion transkey:[self makedword:nIndex high:windindex]];
         	ASYNC_SENDDATA_END
        }
            break;
    case TDX_CXGPCP:
        {
            ASYNC_SENDDATA_START
            tempString = [NSString  stringWithFormat:@"FuncID=%i&F234=%@&",140,@"6"];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            ASYNC_SENDDATA_END
        }
            break;
        case TDX_SDXJC_LOGIN:
        {
            ASYNC_SENDDATA_START
            tempString = [NSString  stringWithFormat:@"FuncID=%i&F362=%@&",322,@"PC.Page.Login"];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            tempString = [NSString  stringWithFormat:@"F1217=%@&",@"SDX.CHECK_RISK_ACCOUNT,SDX.CHECK_EFT_CERT,SDX.CHECK_RISK_PRODUCTCODE,SDX.CHECK_AUTO_EVALUATION,"];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            ASYNC_SENDDATA_END
        }
            break;
		case TDX_GDCX: { //股东查询
			ASYNC_SENDDATA_START
			tempString = [NSString  stringWithFormat:@"FuncID=%i&F110=0&",1122];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			ASYNC_SENDDATA_END
		}
			break;
		case TDX_YHXX:{
            //908不送资金账号,送了就是查你送的这个资金账号的 银行信息
			//ASYNC_SENDDATA_START
            //不送资金账号就是查所有的
            ASYNC_SENDDATA_START_DZH
            int ngnid=908;
#ifdef IMAC_GHZQ
            ngnid=922;
#endif
#ifdef IMAC_XNZQ
            ngnid=922;
#endif
#ifdef IMAC_PAZQ
            //ngnid=922;
            ngnid=908;
#endif
			tempString = [NSString  stringWithFormat:@"FuncID=%i&",ngnid];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = @"F110=0&";
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            tempString = [NSString  stringWithFormat:@"F121=%@&",[clientinfos GetZjzh]];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            
            ASYNC_SENDDATA_END
		}
			break;
		case TDX_GFCX:
		{
			ASYNC_SENDDATA_START
			tempString = [NSString  stringWithFormat:@"FuncID=%i&F110=0&",1114];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			ASYNC_SENDDATA_END
		}
			break;
		case TDX_FECX:
		{
			ASYNC_SENDDATA_START
			tempString = [NSString  stringWithFormat:@"FuncID=%i&F110=0&",2106];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			ASYNC_SENDDATA_END
			
		}
			break;
		case TDX_LCFECX:
		{
			ASYNC_SENDDATA_START
			tempString = [NSString  stringWithFormat:@"FuncID=%i&F110=0&",2200];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			ASYNC_SENDDATA_END
			
		}
			break;
        case TDX_DBPHZ:
        {
            ASYNC_SENDDATA_START
            tempString = [NSString  stringWithFormat:@"FuncID=%i&F110=0&",2200];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            ASYNC_SENDDATA_END
            
        }
            break;
		default:
			break;
	}
	
	[newdata release];
	[headdata release];
}

//基金委托请求
//-(void)sendTradeWTData:()
-(void)sendTradeWTData:(short)nIndex objIndex:(short)windindex Session:(uint64_t)dwEssion jjCode:(NSString* )jjcode jjGsdm:(NSString*)jjgsdm jjZhdm:(NSString*)jjzhdm WTValue:(NSString *)WTvalue WTNum:(int)WTnum SFFS:(int)sffs SHFS:(int)shfs FHFS:(int)fhfs WTFlag:(int)Wtflag tjr:(NSString *)strtjr
{
	NSMutableData* newdata = [[NSMutableData alloc]init];
	NSMutableData* headdata = [[NSMutableData alloc]init];
	NSString* tempString;
	
	switch (nIndex)
	{
		case TDX_FHSZ:
		{
			ASYNC_SENDDATA_START1
			tempString = [NSString  stringWithFormat:@"FuncID=%i&",2114];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString	stringWithFormat:@"F426=%@&",jjgsdm];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString	stringWithFormat:@"F417=%@&",jjzhdm];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString	stringWithFormat:@"F402=%@&",jjcode];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString	stringWithFormat:@"F408=%i&",fhfs];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			ASYNC_SENDDATA_END
			
		}
			break;
		case TDX_WTSH:
		{
			ASYNC_SENDDATA_START1
			tempString = [NSString  stringWithFormat:@"FuncID=%i&",2100];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString	stringWithFormat:@"F426=%@&",jjgsdm];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString	stringWithFormat:@"F417=%@&",jjzhdm];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString	stringWithFormat:@"F402=%@&",jjcode];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString	stringWithFormat:@"F400=%i&",Wtflag];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString	stringWithFormat:@"F404=%@&",WTvalue];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString	stringWithFormat:@"F468=%d&",shfs];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			NSDateFormatter* tempMatter = [[[NSDateFormatter alloc]init]autorelease];
			[tempMatter setDateFormat:@"yyyyMMdd"];
			NSString* strDate = [tempMatter stringFromDate:[NSDate date]];
			tempString = [NSString	stringWithFormat:@"F409=%@&",strDate];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			ASYNC_SENDDATA_END
		}
			break;
		case TDX_WTRG:
		{
			ASYNC_SENDDATA_START1
			tempString = [NSString  stringWithFormat:@"FuncID=%i&",2100];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString	stringWithFormat:@"F426=%@&",jjgsdm];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString	stringWithFormat:@"F417=%@&",jjzhdm];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString	stringWithFormat:@"F402=%@&",jjcode];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString	stringWithFormat:@"F405=%@&",WTvalue];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString	stringWithFormat:@"F485=%@&",strtjr];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString	stringWithFormat:@"F400=%i&",Wtflag];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString	stringWithFormat:@"F429=%d&",sffs];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			ASYNC_SENDDATA_END
		}
			break;
		case TDX_CYLC:
		{
			ASYNC_SENDDATA_START1
			tempString = [NSString  stringWithFormat:@"FuncID=%i&",2100];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString	stringWithFormat:@"F426=%@&",jjgsdm];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString	stringWithFormat:@"F417=%@&",jjzhdm];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString	stringWithFormat:@"F402=%@&",jjcode];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString	stringWithFormat:@"F405=%@&",WTvalue];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString	stringWithFormat:@"F485=%@&",strtjr];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString	stringWithFormat:@"F400=%i&",Wtflag];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString	stringWithFormat:@"F429=%d&F1223=0&",sffs];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			ASYNC_SENDDATA_END
		}
			break;
		default:
			break;
	}
	[newdata release];
	[headdata release];
}

-(void)sendTradeWTData:(short)nIndex objIndex:(short)windindex Session:(uint64_t)dwEssion jjCode:(NSString* )jjcode jjGsdm:(NSString*)jjgsdm jjZhdm:(NSString*)jjzhdm WTValue:(NSString *)WTvalue WTNum:(int)WTnum SFFS:(int)sffs SHFS:(int)shfs FHFS:(int)fhfs WTFlag:(int)Wtflag tjr:(NSString *)strtjr xgflag:(BOOL)bxgflag WTRQ:(NSString *)wtrq WTBH:(NSString *)wtbh LSH:(NSString *)lsh
{
	NSMutableData* newdata = [[NSMutableData alloc]init];
	NSMutableData* headdata = [[NSMutableData alloc]init];
	NSString* tempString;
	
	switch (nIndex)
	{
	case TDX_JJDQSG:
		{
			ASYNC_SENDDATA_START1
			tempString = [NSString  stringWithFormat:@"FuncID=%i&",2130];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString	stringWithFormat:@"F426=%@&",jjgsdm];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString	stringWithFormat:@"F417=%@&",jjzhdm];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString	stringWithFormat:@"F449=%i&",WTnum];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString	stringWithFormat:@"F402=%@&",jjcode];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString	stringWithFormat:@"F405=%@&",WTvalue];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString	stringWithFormat:@"F485=%@&F1223=0&",strtjr];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString	stringWithFormat:@"F113=%i&",(bxgflag?1:0)];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			if(bxgflag)
			{
				tempString = [NSString	stringWithFormat:@"F142=%@&F146=%@&F169=%@&",wtrq,wtbh,lsh];
				[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			}
			ASYNC_SENDDATA_START_LSDATE
			ASYNC_SENDDATA_END
		}
			break;
		case TDX_LCDQSG:
		{
			ASYNC_SENDDATA_START1
			tempString = [NSString  stringWithFormat:@"FuncID=%i&",2130];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString	stringWithFormat:@"F426=%@&",jjgsdm];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString	stringWithFormat:@"F417=%@&",jjzhdm];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString	stringWithFormat:@"F449=%i&",WTnum];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString	stringWithFormat:@"F402=%@&",jjcode];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString	stringWithFormat:@"F405=%@&",WTvalue];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString	stringWithFormat:@"F485=%@&F1223=0&",strtjr];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString	stringWithFormat:@"F113=%i&",(bxgflag?1:0)];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			if(bxgflag)
			{
				tempString = [NSString	stringWithFormat:@"F142=%@&F146=%@&F169=%@&",wtrq,wtbh,lsh];
				[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			}
			ASYNC_SENDDATA_START_LSDATE
			ASYNC_SENDDATA_END
		}
			break;
		default:
			break;
	}
	[newdata release];
	[headdata release];
}


//基金转换请求
-(void)sendTradeWTData:(short)nIndex objIndex:(short)windindex Session:(uint64_t)dwEssion jjGsdm:(NSString*)jjgsdm jjzhdm:(NSString*)jjzhdm OutCode:(NSString*)outcode InCode:(NSString*)incode ZhValue:(NSString *)zhValue SHFS:(int)shfs SFFS:(int)sffs
{
	NSMutableData* newdata = [[NSMutableData alloc]init];
	NSMutableData* headdata = [[NSMutableData alloc]init];
	NSString* tempString;
	
	ASYNC_SENDDATA_START
	tempString = [NSString  stringWithFormat:@"FuncID=%i&",2104];
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	tempString = [NSString	stringWithFormat:@"F426=%@&",jjgsdm];
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	tempString = [NSString	stringWithFormat:@"F417=%@&",jjzhdm];
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	tempString = [NSString	stringWithFormat:@"F402=%@&",outcode];
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	tempString = [NSString	stringWithFormat:@"F407=%@&",incode];
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	tempString = [NSString	stringWithFormat:@"F405=%@&",zhValue];
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	tempString = [NSString	stringWithFormat:@"F468=%d&",shfs];
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	tempString = [NSString	stringWithFormat:@"F429=%d&",sffs];
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	ASYNC_SENDDATA_END
	[newdata release];
	[headdata release];
}


-(void) sendTradeWTData:(short)nIndex objIndex:(short)windindex Session:(uint64_t)dwEssion wtArray:(NSMutableArray*)wtArray selectArray:(NSMutableArray*)array
{
	NSMutableData* newdata = [[NSMutableData alloc] init];
	NSMutableData *headdata=[[NSMutableData alloc]init];
	NSString* tempString=@"";
	NSUInteger wtacount=[wtArray count];
	NSUInteger aacount=[array count];
	
	ASYNC_SENDDATA_START1
	tempString = [NSString  stringWithFormat:@"FuncID=%i&",2118];
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];

	if(wtacount>0)
	{	
		tempString = [NSString  stringWithFormat:@"F426=%@&",[wtArray objectAtIndex:0]];//交易所代码
		[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	}
	if(wtacount>15)
	{	
		tempString = [NSString  stringWithFormat:@"F125=%@&F123=%@&",[wtArray objectAtIndex:14],[wtArray objectAtIndex:15]];
		[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	}
	if(wtacount>13)
	{	
		tempString = [NSString  stringWithFormat:@"F417=%@&",[wtArray objectAtIndex:13]];
		[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	}
	tempString = [NSString  stringWithFormat:@"F113=1&"];
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	if(wtacount>1)
	{
		tempString = [NSString  stringWithFormat:@"F122=%@&F464=%@&",[wtArray objectAtIndex:1],[wtArray objectAtIndex:1]];
		[newdata appendData:[tempString dataUsingEncoding:CFStringConvertEncodingToNSStringEncoding (kCFStringEncodingGB_18030_2000)]];
	}
	if(wtacount>2)
	{
		tempString = [NSString  stringWithFormat:@"F950=%@&",[wtArray objectAtIndex:2]];
		[newdata appendData:[tempString dataUsingEncoding:CFStringConvertEncodingToNSStringEncoding (kCFStringEncodingGB_18030_2000)]];
	}
	if(wtacount>3)
	{
		tempString = [NSString  stringWithFormat:@"F128=%@&",[wtArray objectAtIndex:3]];
		[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	}
	if(wtacount>4)
	{
		tempString = [NSString  stringWithFormat:@"F129=%@&",[wtArray objectAtIndex:4]];
		[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	}
	if(aacount>8)
	{
		tempString = [NSString  stringWithFormat:@"F450=%@&",[array objectAtIndex:8]];
		[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	}
	if(aacount>1)
	{
		tempString = [NSString  stringWithFormat:@"F452=%@&",[array objectAtIndex:1]];
		[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	}
	if(wtacount>6)
	{
		tempString = [NSString  stringWithFormat:@"F454=%@&",[wtArray objectAtIndex:6]];
		[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	}
	if(wtacount>7)
	{
		tempString = [NSString  stringWithFormat:@"F455=%@&",[wtArray objectAtIndex:7]];
		[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	}
	if(wtacount>8)
	{
		tempString = [NSString  stringWithFormat:@"F456=%@&",[wtArray objectAtIndex:8]];
		[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	}
	if(wtacount>9)
	{
		tempString = [NSString  stringWithFormat:@"F463=%@&",[wtArray objectAtIndex:9]];
		[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	}
	if(wtacount>10)
	{
		tempString = [NSString  stringWithFormat:@"F457=%@&",[wtArray objectAtIndex:10]];
		[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	}
	if(wtacount>3)
	{
		tempString = [NSString  stringWithFormat:@"F458=%@&",[array objectAtIndex:3]];
		[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	}
	if(wtacount>11)
	{
		tempString = [NSString  stringWithFormat:@"F459=%@&",[wtArray objectAtIndex:11]];
		[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	}
	if(aacount>4)
	{
		tempString = [NSString  stringWithFormat:@"F465=%@&",[array objectAtIndex:4]];
		[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	}
	if(aacount>5)
	{
		tempString = [NSString  stringWithFormat:@"F467=%@&",[array objectAtIndex:5]];
		[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	}
	if(aacount>0)
	{
		tempString = [NSString  stringWithFormat:@"F952=%@&",[array objectAtIndex:0]];
		[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	}
	if(wtacount>12)
	{
		tempString = [NSString  stringWithFormat:@"F953=%@&",[wtArray objectAtIndex:12]];
		[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	}
	if(aacount>6)
	{
		tempString = [NSString  stringWithFormat:@"F466=%@&",[array objectAtIndex:6]];
		[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	}
	if(aacount>7)
	{
		tempString = [NSString  stringWithFormat:@"F468=%@&",[array objectAtIndex:7]];
		[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	}
	ASYNC_SENDDATA_END
	[newdata release];
	[headdata release];
}

-(void) sendTradeWTData:(short)nIndex objIndex:(short)windindex Sessiomn:(uint64_t)dwEssion jjCode:(NSString*)jjcode jjGsdm:(NSString*)jjgsdm jjZhdm:(NSString*)jjzhdm WTDate:(NSString*)wtdate WTNumber:(NSString*) wtNumber WTValue:(NSString*)wtValue WTIndex:(NSString*)wtIndex
{
	NSMutableData* newdata = [[NSMutableData alloc] init];
	NSMutableData *headdata=[[NSMutableData alloc]init];
	NSString* tempString;
	ASYNC_SENDDATA_START
	tempString = [NSString  stringWithFormat:@"FuncID=%i&",2102];
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	ASYNC_SENDDATA_START_GDDM
	tempString = [NSString  stringWithFormat:@"F426=%@&",jjgsdm];//交易所代码
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	tempString = [NSString  stringWithFormat:@"F417=%@&",jjzhdm];
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	tempString = [NSString  stringWithFormat:@"F402=%@&",jjcode];
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	tempString = [NSString  stringWithFormat:@"F142=%@&",wtdate];
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	tempString = [NSString  stringWithFormat:@"F404=%@&",wtNumber];
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	tempString = [NSString  stringWithFormat:@"F405=%@&",wtValue];
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	tempString = [NSString  stringWithFormat:@"F146=%@&",wtIndex];
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	tempString = @"F429=&";
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	ASYNC_SENDDATA_END
	[newdata release];
	[headdata release];
	
}

-(void) sendTradeWTData:(short)nIndex objIndex:(short)windindex Sessiomn:(uint64_t)dwEssion jjCode:(NSString*)jjcode jjGsdm:(NSString*)jjgsdm jjZhdm:(NSString*)jjzhdm WTBH:(NSString*)wtbh WTLX:(NSString*)lx MYKKRQ:(NSString*)mykkrq KSRQ:(NSString*)ksrq ZZRQ:(NSString *)zzrq JYJE:(NSString *)jyje LSH:(NSString *)lsh QMTJ:(NSString *)qmtj  MODE:(NSString *)kkzqbh WTRQ:(NSString *)wtrq
{
	NSMutableData* newdata = [[NSMutableData alloc] init];
	NSMutableData *headdata=[[NSMutableData alloc]init];
	NSString* tempString;
	ASYNC_SENDDATA_START1
	tempString = [NSString  stringWithFormat:@"FuncID=%i&",2132];
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	tempString = [NSString  stringWithFormat:@"F426=%@&",jjgsdm];//交易所代码
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	tempString = [NSString  stringWithFormat:@"F417=%@&",jjzhdm];
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	tempString = [NSString  stringWithFormat:@"F402=%@&",jjcode];
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	tempString = [NSString  stringWithFormat:@"F234=%@&",lx];
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	tempString = [NSString  stringWithFormat:@"F449=%@&",mykkrq];
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	tempString = [NSString  stringWithFormat:@"F126=%@&",ksrq];
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	tempString = [NSString  stringWithFormat:@"F146=%@&",wtbh];
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	tempString = [NSString  stringWithFormat:@"F127=%@&",zzrq];
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	tempString = [NSString  stringWithFormat:@"F405=%@&",jyje];
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	tempString = [NSString  stringWithFormat:@"F169=%@&",lsh];
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	if([lx intValue]==1 || [lx intValue]==2)
	{
		tempString = [NSString  stringWithFormat:@"F1227=%@&",qmtj];
		[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	}
	tempString = [NSString  stringWithFormat:@"F1228=%@&",kkzqbh];
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	tempString = [NSString  stringWithFormat:@"F142=%@&",wtrq];
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	tempString = @"F429=&";
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	ASYNC_SENDDATA_END
	[newdata release];
	[headdata release];
	
}

//委托请求    bsflag:0-b  1-s
-(void)sendTradeWTData:(short)nIndex objIndex:(short)windindex Session:(uint64_t)dwEssion gpCode:(NSString *)gpcode gpPrice:(NSString *)gpprice gpNum:(int)gpnum bsFlag:(int)bsflag kyzj:(float)kyzj{
	NSMutableData * newdata = [[NSMutableData alloc] init];	
	NSMutableData *headdata=[[NSMutableData alloc]init];
	NSString * tempString;
	switch (nIndex) {
		case TDX_KMMS:
		{
            ASYNC_SENDDATA_START
            tempString = [NSString  stringWithFormat:@"FuncID=%i&",110];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            tempString = [NSString  stringWithFormat:@"F140=%@&",gpcode];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            tempString = [NSString  stringWithFormat:@"F130=%i&",bsflag];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            ASYNC_SENDDATA_START_GDDM
            ASYNC_SENDDATA_START_WTFS
            tempString = [NSString  stringWithFormat:@"F949=%@&",gpprice];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            tempString = [NSString  stringWithFormat:@"F301=%.3f&",kyzj];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            tempString = [NSString  stringWithFormat:@"F166=%i&",gpnum];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            tempString = @"F110=0&F213='G'&";
            if (self.clientinfos.m_bxyjyflag)
            {
//                 tempString = [NSString  stringWithFormat:@"F5250=%@&F5260=0&F5251=1&F5251=XYJY&",inputSave.accout];
//                [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
                if (tradeType == DBPBuy) {
                    tempString = @"F110=6&F213='G'&";
                }
                else if(tradeType == RZBuy || tradeType == RZSell){
                    tempString = @"F110=N&&F213='G'&";
                }
              
            }
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            ASYNC_SENDDATA_END
		}
			break;
        case TDX_DBPHZ+1:
        {
            ASYNC_SENDDATA_START
            tempString = [NSString  stringWithFormat:@"FuncID=%i&",110];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            tempString = [NSString  stringWithFormat:@"F140=%@&",gpcode];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            tempString = [NSString  stringWithFormat:@"F130=%d&",74];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            tempString = [NSString  stringWithFormat:@"F514=%i&",-1];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            ASYNC_SENDDATA_START_GDDM
            ASYNC_SENDDATA_START_WTFS
            tempString = [NSString  stringWithFormat:@"F5250=%@&F5260=0&F5251=1&F5251=XYJY&",inputSave.accout];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            tempString = [NSString  stringWithFormat:@"F166=%i&",gpnum];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            tempString = @"F110=7&";
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            ASYNC_SENDDATA_END
        }
            break;
		default:
			break;
	}
			
	[newdata release];
	[headdata release];
}

-(void)sendTradeWTData:(short)nIndex objIndex:(short)windindex Session:(uint64_t)dwEssion gpCode:(NSString *)gpcode gpPrice:(NSString *)gpprice gpNum:(int)gpnum bsFlag:(int)bsflag{
	NSMutableData * newdata = [[NSMutableData alloc] init];	
	NSMutableData * headdata = [[NSMutableData alloc] init];	
	NSString * tempString;
	
	switch (nIndex) {
		case TDX_ZQXX:
			{
				ASYNC_SENDDATA_START
				tempString = [NSString  stringWithFormat:@"FuncID=%i&",1124];
				[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
				tempString = [NSString  stringWithFormat:@"F140=%@&",gpcode];
				[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
				tempString = [NSString  stringWithFormat:@"F130=%i&",bsflag];
				[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
				ASYNC_SENDDATA_START_GDDM
                tempString = @"F110=0&F213='G'&F113=0";
                if (self.clientinfos.m_bxyjyflag)
                {
                    if (tradeType == 0) {
                        tempString = @"F110=6&F113=0&F166=-1&F1223=1";
                    }
                    else if (tradeType == 2){
                        tempString = @"F110='N'&F113=0&F166=-1&F1223=1";
                    }
                    else{
                        tempString = @"F110=6&F113=0&F166=0&F1223=1";
                    }
                 
                }
                
				[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
				ASYNC_SENDDATA_END
			}
			break;
		case TDX_CXHQ:
		case TDX_CXSC:
		{
			ASYNC_SENDDATA_START
			tempString = [NSString  stringWithFormat:@"FuncID=%i&",102];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString  stringWithFormat:@"F140=%@&F110=0&",gpcode];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			ASYNC_SENDDATA_END
		}
			break;
        case TDX_XYXJHKCX:
        {
            ASYNC_SENDDATA_START
            tempString = [NSString  stringWithFormat:@"FuncID=%i&",110];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            tempString = @"F125=0&F110=7&F130=75&F166=0";
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            ASYNC_SENDDATA_END
        }
            break;
		default:
			break;
	}
	
	[newdata release];
	[headdata release];
}

-(void)sendTradeWTData:(short)nIndex objIndex:(short)windindex Session:(uint64_t)dwEssion gpCode:(NSString *)gpcode gpPrice:(NSString *)gpprice gpNum:(int)gpnum bsFlag:(int)bsflag zqflag:(BOOL)bzqflag wtfs:(int)nwtfs{
	NSMutableData * newdata = [[NSMutableData alloc] init];	
	NSMutableData * headdata = [[NSMutableData alloc] init];	
	NSString * tempString;
	
	switch (nIndex) {
			case TDX_WTJY:{
			ASYNC_SENDDATA_START
			tempString = [NSString  stringWithFormat:@"FuncID=%i&",202];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			ASYNC_SENDDATA_START_GDDM
			tempString = [NSString  stringWithFormat:@"F1302=%i&",39];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            tempString = [NSString  stringWithFormat:@"F130=%i&",bsflag];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString  stringWithFormat:@"F140=%@&",gpcode];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString  stringWithFormat:@"F145=%@&",gpprice];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString  stringWithFormat:@"F133=%i&",(bzqflag?2:0)];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString  stringWithFormat:@"F144=%i&",gpnum];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString  stringWithFormat:@"F166=%i&",nwtfs];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
                
            if(tradeType == DBPSell) //卖出
            {
                if([saveDate.xwdm isEqualToString:@""])
                {
                    GdmxInfo *pgddm=[clientinfos.gdinfos.gddms objectAtIndex:0];
                    tempString = [NSString  stringWithFormat:@"F173=%@&",pgddm.xwdm];
                    [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
                }
                else //点击持仓带过来的席位代码
                {
                    tempString = [NSString  stringWithFormat:@"F173=%@&",saveDate.xwdm];
                    [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
                }
            }

			tempString = @"F110=0&";
                if (self.clientinfos.m_bxyjyflag)
                {
                    if (tradeType == 0) {
                        tempString = @"F110=6&";
                    }
                    else if (tradeType == 2){
                        tempString = @"F110=N&";
                    }
                    else if(tradeType == MQHK)
                    {
                        tempString = @"F110=7&";
                    }
                }
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			ASYNC_SENDDATA_END
		}
			break;
        case TDX_DBPHZ:
            ASYNC_SENDDATA_START
            tempString = [NSString  stringWithFormat:@"FuncID=%i&",202];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            tempString = [NSString  stringWithFormat:@"F1302=%i&",39];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            tempString = [NSString  stringWithFormat:@"F110=7&F130=74&"];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            tempString = [NSString  stringWithFormat:@"F140=%@&",gpcode];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            tempString = [NSString  stringWithFormat:@"F145=0.00&"];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            tempString = [NSString  stringWithFormat:@"F133=0&"];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            tempString = [NSString  stringWithFormat:@"F144=%i&",gpnum];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            tempString = [NSString  stringWithFormat:@"F166=1&"];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            tempString = [NSString  stringWithFormat:@"F5250=%@&F5260=0&F5251=1&F5251=XYJY&",inputSave.accout];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            ASYNC_SENDDATA_START_GDDM
            ASYNC_SENDDATA_END
            
            break;
        case TDX_XYXJHKCX+1:
            ASYNC_SENDDATA_START
            tempString = [NSString  stringWithFormat:@"FuncID=%i&",202];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            tempString = [NSString  stringWithFormat:@"F1302=%i&",39];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            tempString = [NSString  stringWithFormat:@"F110=7&F130=75&"];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            tempString = [NSString  stringWithFormat:@"F133=%i&",0];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            tempString = [NSString  stringWithFormat:@"F144=%@&",gpprice];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            tempString = [NSString  stringWithFormat:@"F166=0&"];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            tempString = [NSString  stringWithFormat:@"F5250=%@&F5260=0&F5251=1&F5251=XYJY&",inputSave.accout];
            [newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
            ASYNC_SENDDATA_START_GDDM
            ASYNC_SENDDATA_END
            
            break;
		default:
			break;
	}
	
	[newdata release];
	[headdata release];
}


-(void)sendTradeWTData:(short)nIndex objIndex:(short)windindex Session:(uint64_t)dwEssion gpCode:(NSString *)gpcode Wtbhs:(NSString *)wtbh scflags:(NSString *)scflag zhlbs:(NSString *)nzhlb gddms:(NSString *)gddm mmbzs:(NSString *)nmmbz
{
	NSMutableData * newdata = [[NSMutableData alloc] init];	
	NSMutableData * headdata = [[NSMutableData alloc] init];	
	NSString * tempString;
	
	ASYNC_SENDDATA_START1
	tempString = [NSString  stringWithFormat:@"FuncID=%i&",200];
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	tempString = [NSString  stringWithFormat:@"F123=%@&",gddm];
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	tempString = [NSString  stringWithFormat:@"F130=%@&",nmmbz];
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	tempString = [NSString  stringWithFormat:@"F125=%@&",nzhlb];
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	tempString = [NSString  stringWithFormat:@"F100=%@&",scflag];//交易所代码
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	tempString = [NSString  stringWithFormat:@"F140=%@&",gpcode];
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	tempString = [NSString  stringWithFormat:@"F146=%@&F110=0&",wtbh];//委托编号
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	ASYNC_SENDDATA_END
	
	[newdata release];
	[headdata release];
}
#pragma mark 存活包
-(void) initCHBThread{
	wtCHBTimer = [NSTimer scheduledTimerWithTimeInterval:30 target:self selector:@selector(startSendCHB) userInfo:nil repeats:YES];
}
-(void) startSendCHB{
	if(tradeLoginFlag==NO)
		return;
	[self sendTradeQueryData:TDX_CHB objIndex:0 Session:self.inputSave.sessionID];
}
-(void) stopSendCHB{
}


#pragma mark 密码
-(void)EncryptJymm:(NSString *)strjymm
{
	NSMutableData *tmpdata=[[NSMutableData alloc] init];
	[tmpdata appendData:[strjymm dataUsingEncoding:NSUTF8StringEncoding]];
	
	int _length = [tmpdata length];
	char * temp2char = malloc(100);
	memset(temp2char,0,100);
	memcpy(temp2char, [tmpdata bytes], _length);
	unsigned char * pbySrc = (unsigned char *)temp2char;
	int _length1 = (_length+23)/24 * 24;
	NSData *data =[[NSData alloc] initWithBytes:pbySrc length:_length1];
	[GTMBase64 encodeData:data];
	newEncrypt(pbySrc, _length1);

	[inputSave  setjyPassword:pbySrc len:_length1];
	
	[data release];
	free(temp2char);
	[tmpdata release];
}

-(NSString *)GetJymmString
{
	int _length = [inputSave.password length] ;
	unsigned char temp2char[100];
	memset(temp2char,0,100);
	memcpy(temp2char, [inputSave.password bytes], _length);
	unsigned char * pbySrc = temp2char;
	_length = (_length+23)/24 * 24;
	newDecrypt(pbySrc, _length);
	NSString * theString = [[NSString alloc] initWithCString:(char *)pbySrc encoding:CFStringConvertEncodingToNSStringEncoding(kCFStringEncodingGB_18030_2000)];
	
	NSString *tmpstr=[NSString stringWithFormat:@"%@",theString];
	[theString release];
	return tmpstr;
}

-(void)EncryptauthPass:(NSString *)strauthpass
{
	NSMutableData *tmpdata=[[NSMutableData alloc] init];
	[tmpdata appendData:[strauthpass dataUsingEncoding:NSUTF8StringEncoding]];
	
	int _length = [tmpdata length];
	char * temp2char = malloc(100);
	memset(temp2char,0,100);
	memcpy(temp2char, [tmpdata bytes], _length);
	unsigned char * pbySrc = (unsigned char *)temp2char;
	int _length1 = (_length+23)/24 * 24;
	NSData *data =[[NSData alloc] initWithBytes:pbySrc length:_length1];
	[GTMBase64 encodeData:data]; 
	newEncrypt(pbySrc, _length1);
	
	[inputSave  setauthPassword:pbySrc len:_length1];
	
	[data release];
	free(temp2char);
	[tmpdata release];
}

-(NSString *)GetauthpassString
{
	int _length = [inputSave.authpassword length] ;
	unsigned char temp2char[100];
	memset(temp2char,0,100);
	memcpy(temp2char, [inputSave.authpassword bytes], _length);
	unsigned char * pbySrc = temp2char;
	_length = (_length+23)/24 * 24;
	newDecrypt(pbySrc, _length);
	NSString * theString = [[NSString alloc] initWithCString:(char *)pbySrc encoding:CFStringConvertEncodingToNSStringEncoding(kCFStringEncodingGB_18030_2000)];
	
	NSString *tmpstr=[NSString stringWithFormat:@"%@",theString];
	[theString release];
	return tmpstr;
}

-(void)EncryptReloginSession:(NSString *)strsession
{
    if([strsession length]<=0)
    {
        [inputSave releasereloginsession];
        return;
    }
	[inputSave  setReloginSession:strsession];
}

-(NSString *)GetReloginSessionString
{
    if(inputSave.reloginsession==nil)
        return @"";
    
	return inputSave.reloginsession;
}
#pragma mark 加密解密压缩解压
-(void)getEncrypted:(NSMutableData *) theData{
	int _length = [theData length];
	unsigned char * pbySrc;
	unsigned const char * tempChar  = (unsigned const char *)[theData bytes];
	unsigned char temp2char[_length*2];
	memset(temp2char,0,_length*2);
	memcpy(temp2char, tempChar, _length);
	pbySrc = temp2char;
	

	int _length1 = (_length+23)/24 * 24;
	newEncrypt(pbySrc, _length1);
	
	
//	theData = [NSMutableData dataWithBytes:pbySrc length:_length1];

}
-(NSString * )getDecrypt:(NSMutableData *) theData BodyFlag:(int)flag {
	int _length = [theData length]-flag ;
	unsigned char temp2char[_length];
	memcpy(temp2char, [theData bytes]+flag, _length);

	unsigned char * pbySrc = temp2char;

	newDecrypt(pbySrc, _length);
	
	NSString * theString = [NSString stringWithCString:(char *)pbySrc encoding:CFStringConvertEncodingToNSStringEncoding(kCFStringEncodingGB_18030_2000)];
	return theString;
}

-(NSString *) getDepress:(NSMutableData *)theData  BodyFlag:(int)flag RawLength:(int) rawLen {
	int _length = [theData length];
	//unsigned const char * tempChar = [theData bytes];
	
	unsigned char rawChar[rawLen+1024];
	unsigned long  getLength = _length-flag;
	unsigned char  getChar[getLength];
	unsigned long  rawLength =rawLen+1024;
	
	memcpy(getChar, [theData bytes]+flag, getLength);
	httpgzdecompress(getChar, getLength, rawChar, &rawLength);
	rawChar[rawLen] = '\0';
	NSString * theString = [NSString stringWithCString:(char *)rawChar encoding:CFStringConvertEncodingToNSStringEncoding(kCFStringEncodingGB_18030_2000)];
	return theString;

}

#pragma mark 请求

#pragma mark 数据处理
//处理数据  
-(NSString *)dealTheData:(NSMutableData *)theData{
	UInt64 session=0;
	char m_encrypted=0,m_compressed=0;
	NSMutableData * tempData;
	NSString * tempString;
	
	[theData getTdxBytes:&session range:NSMakeRange(g_TradeComm.httpFlag+9, sizeof(UInt64))];
	inputSave.sessionID = session;
	
	[theData getTdxBytes:&m_compressed range:NSMakeRange(g_TradeComm.httpFlag+2, sizeof(char))];
	[theData getTdxBytes:&m_encrypted range:NSMakeRange(g_TradeComm.httpFlag+3, sizeof(char))];
	if(m_encrypted == 1)
	{
		if(m_compressed == 1){
			int flag = g_TradeComm.httpFlag +20;
			int _length = [theData length]-flag ;
			unsigned char temp2char[_length];
			memcpy(temp2char, [theData bytes]+flag, _length);
			unsigned char * pbySrc = temp2char;
			newDecrypt(pbySrc, _length);
			
			tempData = [[NSMutableData alloc] initWithBytes:pbySrc length:_length];
			tempString = [self getDepress:tempData BodyFlag:0 RawLength:g_TradeComm.rawLen];
			[tempData release];
		}else
		{
			tempString = [self getDecrypt:theData BodyFlag:g_TradeComm.httpFlag +20];
		}
		
	}
	else if((m_encrypted == 0)&&(m_compressed == 1))
	{
		tempString = [self getDepress:theData BodyFlag:g_TradeComm.httpFlag +20 RawLength:g_TradeComm.rawLen];
	}
	else 
	{	
		tempString = [[NSString alloc] initWithData:[theData subdataWithRange:NSMakeRange(g_TradeComm.httpFlag+20, [theData length]-g_TradeComm.httpFlag-20)] encoding:CFStringConvertEncodingToNSStringEncoding (kCFStringEncodingGB_18030_2000)];
		
	}
		
	return tempString;
}



//处理客户校验信息
#pragma mark 数据处理
-(BOOL) getGDCXInfo:(ParseRecv *)pParsers
{
	if(pParsers==nil)
		return NO;
	if(pParsers.bsucflag)
	{
		if(pParsers.nrownum>0)
		{
			GdmxInfo *pgdmx=nil; 
			int i=0;
			if(clientinfos.gdinfos.gddms)
				[clientinfos.gdinfos releasegdmxs];
			clientinfos.gdinfos.gddms=[[NSMutableArray alloc] initWithCapacity:pParsers.nrownum+1];
			[clientinfos.gdinfos.gddms release];
            NSString *tmpzjzh;
			for( i=0;i<pParsers.nrownum;i++)
			{
				pgdmx=[GdmxInfo new];
				pgdmx.gddm=[[NSString alloc] initWithFormat:@"%@",[pParsers getFieldData:i fieldFlag:TDX_ID_GDDM]];
				[pgdmx.gddm release];
				pgdmx.gdmc=[[NSString alloc] initWithFormat:@"%@",[pParsers getFieldData:i fieldFlag:TDX_ID_GDMC]];
				[pgdmx.gdmc release];
				pgdmx.wttype=[[pParsers getFieldData:i fieldFlag:TDX_ID_ZHLB] intValue];
                tmpzjzh=[pParsers getFieldData:i fieldFlag:TDX_ID_ZJZH];
                if([tmpzjzh length]<=0 || [tmpzjzh isEqualToString:@"0"])
                    pgdmx.zjzh=[[NSString alloc] initWithFormat:@"%@",@""];
                else
                    pgdmx.zjzh=[[NSString alloc] initWithFormat:@"%@",tmpzjzh];
				[pgdmx.zjzh release];
                NSLog(@"zjzh %@",pgdmx.zjzh);
				pgdmx.xwdm=[[NSString alloc] initWithFormat:@"%@",[pParsers getFieldData:i fieldFlag:TDX_ID_XWDM]];
				[pgdmx.xwdm release];
				pgdmx.specTrade=[[pParsers getFieldData:i fieldFlag:TDX_ID_ZDJYBZ] intValue];
				pgdmx.bxyjygd=[[pParsers getFieldData:i fieldFlag:TDX_ID_XYJYBS] intValue];
				pgdmx.memo=[[NSString alloc] initWithFormat:@"%@",[pParsers getFieldData:i fieldFlag:TDX_ID_XT_REMARK]];
				[pgdmx.memo release];
				if(clientinfos.m_nQsbs==ZXZQ_DLL && [pgdmx.memo isEqualToString:@"信用"])
					pgdmx.bxyjygd=YES;
				else 
					pgdmx.bxyjygd=NO;
                if(pgdmx.bxyjygd)
                    continue;
                int nindex=0;
                BOOL bfindflag=NO;
                for(NSString *pzjzh in clientinfos.m_realzjzh)
                {
                    if([pzjzh isEqualToString:pgdmx.zjzh])
                        break;
                    nindex++;
                }
                if(nindex>=[clientinfos.m_realzjzh count])
                    clientinfos.m_nrealIndex=0;
                else
                    clientinfos.m_nrealIndex=nindex;
                
				[clientinfos.gdinfos.gddms addObject:pgdmx];
			}
			[clientinfos.gdinfos CalcGdInfo:clientinfos.logininfos.m_loginWtType withrawzjzh:clientinfos.logininfos.m_rawzjzh];
			[self setInputSaveInfo];
		}
		/////////保存股东信息到clientinfos////////////
		
		//MyNsLog(@"123");
		return YES;
		
	}	
	else{//股东查询失败
		return NO;
	}
	
}

-(void)SetLog:(NSString *)_theLog{
	NSDateFormatter *dateFormatter = [[[NSDateFormatter alloc] init]autorelease];
	[dateFormatter setDateFormat:@"yyyyMMdd:HHmmss"];
	NSString * dateString = [dateFormatter stringFromDate:[NSDate date]];
	
	NSError *error;
	NSString * tempString = [NSString stringWithContentsOfFile:logcachefile encoding:NSUTF8StringEncoding error:&error];
	tempString = [tempString stringByAppendingFormat:@"%@---%@%@\r",dateString,@"/",_theLog];
	NSMutableData * write = [[NSMutableData alloc] init];
	[write appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];

	[write writeToFile:logcachefile atomically:YES];
	[write release];
}

-(void)SetSessionID:(UInt64)usessionid
{
	if (usessionid == 0) {
		return;
	}
	if(inputSave.sessionID!=usessionid)
	{
		inputSave.sessionID = usessionid;
		g_TradeComm.sessionID=usessionid;
	}
}

-(BOOL) getReloginInfo:(ParseRecv *)pParsers
{
	if(pParsers==nil)
		return NO;
	if(pParsers.bsucflag ==YES)
	{
		[self EncryptReloginSession:[pParsers getFieldData:0 fieldFlag:TDX_ID_XT_SESSION]];
		self.g_TradeComm.bneedreloginflag=NO;
		self.tradeLoginFlag =YES;
		self.g_TradeComm.tradeLoginFlag=YES;
		[g_TradeComm clearAllRequest];
		if(self.g_TradeComm.btipreloginflag)
		{
			self.g_TradeComm.btipreloginflag=NO;
			[self SetSessionID:pParsers.sessionID];
			NSAlert* alert = [NSAlert alertWithMessageText: @"提示"
											 defaultButton: @"确定"
										   alternateButton: nil
											   otherButton: nil
								 informativeTextWithFormat: @"交易断线重连成功,请继续操作！"];
			[alert runModal];
			
		}
		return YES;
	}
	else 
	{
		if(self.g_TradeComm.btipreloginflag)
		{
			self.g_TradeComm.btipreloginflag=NO;
			NSAlert* alert = [NSAlert alertWithMessageText: @"提示"
											 defaultButton: @"确定"
										   alternateButton: nil
											   otherButton: nil
								 informativeTextWithFormat: @"交易断线重连后登录失败!"];
			[alert runModal];
		}
		self.g_TradeComm.bneedreloginflag=YES;
		return NO;
	}
}

//处理客户校验信息
-(BOOL) getKHJYInfo:(ParseRecv *)pParsers
{
	if(pParsers==nil)
		return NO;
	if(pParsers.bsucflag)
	{
		[self SetSessionID:pParsers.sessionID];
		self.tradeLoginFlag = YES;
		g_TradeComm.tradeLoginFlag=YES;
		
		clientinfos.m_username=nil;
		clientinfos.m_username=[[NSString alloc]  initWithFormat:@"%@",[pParsers getFieldData:0 fieldFlag:TDX_ID_KHMC]];
		[clientinfos.m_username release];
		clientinfos.m_zjzh=nil;

        NSString *tmpkhh=[pParsers getFieldData:0 fieldFlag:TDX_ID_KHH];
        if([tmpkhh length]<=0)
            tmpkhh=[pParsers getFieldData:0 fieldFlag:0];
#ifdef IMAC_ZTZQ
        tmpkhh=inputSave.accout;
#endif
#ifdef IMAC_GDZQ
        tmpkhh=inputSave.accout;
#endif
		clientinfos.m_zjzh= [[NSString alloc] initWithFormat:@"%@",tmpkhh];
		[clientinfos.m_zjzh release];
		if(clientinfos.m_nQsbs==SYWG_DLL||clientinfos.m_nQsbs==GHZQ_DLL ||clientinfos.m_nQsbs==GTJA_DLL ||clientinfos.m_nQsbs==YHZQ_DLL || clientinfos.m_nQsbs==ZXJT_DLL|| clientinfos.m_nQsbs==GLZQ_DLL || clientinfos.m_nQsbs==MZZQ_DLL || clientinfos.m_nQsbs==TPYZQ_DLL || clientinfos.m_nQsbs==GDZQ_DLL || clientinfos.m_nQsbs==SXZQ_DLL || clientinfos.m_nQsbs == PAZQ_DLL)//有的券商需要处理营业部信息，如申万，有的不需要，如招商
		{
			inputSave.branchId=[NSString stringWithFormat:@"%@",[pParsers getFieldData:0 fieldFlag:TDX_ID_XT_BRANCHID]];
			clientinfos.m_TdxRealBranchID=[inputSave.branchId intValue];
			inputSave.tdxbranchid=clientinfos.m_TdxRealBranchID;
		}
		 
		inputSave.wtfs = [pParsers getFieldData:0 fieldFlag:TDX_ID_OP_WTFS];
		clientinfos.m_strTdxWtfs=nil;
		clientinfos.m_strTdxWtfs=[[NSString alloc]  initWithFormat:@"%@",inputSave.wtfs];
		[clientinfos.m_strTdxWtfs release];
		clientinfos.m_nKhqx=[[pParsers getFieldData:0 fieldFlag:TDX_ID_KHQXDM] intValue];
		clientinfos.m_strKhqxmc=nil;
		clientinfos.m_strKhqxmc=[[NSString alloc] initWithFormat:@"%@",[pParsers getFieldData:0 fieldFlag:TDX_ID_KHQXMC]];
		[clientinfos.m_strKhqxmc release];
		clientinfos.m_bgtbs=[[pParsers getFieldData:0 fieldFlag:TDX_ID_KFSJJ_GTGSBZ] intValue];
		clientinfos.m_bgpflag=YES;
		clientinfos.m_bKfsjjflag=[[pParsers getFieldData:0 fieldFlag:TDX_ID_KFSJJ_JJBS] intValue];
		if(clientinfos.m_bKfsjjflag)
			clientinfos.m_blcflag=YES;
		clientinfos.m_bqhflag=[[pParsers getFieldData:0 fieldFlag:TDX_ID_QHZHBS] intValue];
		clientinfos.m_bxyjyflag=[[pParsers getFieldData:0 fieldFlag:TDX_ID_XYJYBS] intValue];
		clientinfos.m_bggflag=[[pParsers getFieldData:0 fieldFlag:TDX_ID_GGZHBS] intValue];
		[self EncryptReloginSession:[pParsers getFieldData:0 fieldFlag:TDX_ID_XT_SESSION]];
		if(clientinfos.m_bggflag || clientinfos.m_bqhflag)
		{
			clientinfos.m_bKfsjjflag=NO;
			clientinfos.m_bgpflag=NO;
			clientinfos.m_bxyjyflag=NO;
		}
		
		clientinfos.m_jjzjzh=nil;
		clientinfos.m_jjzjzh= [[NSString alloc] initWithFormat:@"%@",[pParsers getFieldData:0 fieldFlag:TDX_ID_ZJZH]];
		[clientinfos.m_jjzjzh release];
		clientinfos.m_bGetMaxBuy=[[pParsers getFieldData:0 fieldFlag:TDX_ID_GTZDKMBS] intValue];
		clientinfos.m_nZhlb=[[pParsers getFieldData:0 fieldFlag:TDX_ID_ZHLB] intValue];
		
		
		clientinfos.m_nRealZjzhNum=0;
		clientinfos.m_realzjzh=nil;
		int nsubzhnum=pParsers.nrownum-1;
        
		if(nsubzhnum>=1)
		{
			clientinfos.m_realzjzh=[[NSMutableArray alloc] initWithCapacity:nsubzhnum+1];
			[clientinfos.m_realzjzh release];
            NSString *tmpzjzh;
			for(int i=1;i<pParsers.nrownum && pParsers.nrownum>1;i++)//////////
			{
                tmpzjzh=[pParsers getFieldData:i fieldFlag:TDX_ID_KHH];
                if([tmpzjzh length]<=0)
                    tmpzjzh=[pParsers getFieldData:i fieldFlag:0];
                if([tmpzjzh length]<=0)
                    continue;
                [clientinfos.m_realzjzh addObject:tmpzjzh];
                clientinfos.m_nRealZjzhNum++;
			}
		}
		[clientinfos initcache];
		return YES;
	}
	else //客户校验失败
	{
		MyNsLog(@"lenx76");
		self.tradeLoginFlag = NO;
		return NO;
	}
	
}

-(BOOL) getYHXXInfo:(ParseRecv *)pParsers
{
	if(pParsers==nil)
		return NO;
	if(pParsers.bsucflag)
	{
		if(pParsers.nrownum>0)
		{
			Yhxxmx *pyhmx=nil; 
			int i=0;
			if(clientinfos.yhxxs.yhmxs)
				[clientinfos.yhxxs releaseyhmxs];
			
			clientinfos.yhxxs.yhmxs=[[NSMutableArray alloc] initWithCapacity:pParsers.nrownum+1];
			[clientinfos.yhxxs.yhmxs release];
			for( i=0;i<pParsers.nrownum;i++)
			{
				pyhmx=[Yhxxmx new];
				pyhmx.yhdm=[[NSString alloc] initWithFormat:@"%@",[pParsers getFieldData:i fieldFlag:TDX_ID_YZZZ_YHDM]];
				[pyhmx.yhdm release];
				pyhmx.yhmc=[[NSString alloc] initWithFormat:@"%@",[pParsers getFieldData:i fieldFlag:TDX_ID_YZZZ_YHMC]];
				[pyhmx.yhmc release];
				pyhmx.yhzh=[[NSString alloc] initWithFormat:@"%@",[pParsers getFieldData:i fieldFlag:TDX_ID_YZZZ_YHZH]];
				[pyhmx.yhzh release];
				pyhmx.nbz=[[pParsers getFieldData:i fieldFlag:TDX_ID_BZ] intValue];
                pyhmx.zjzh=[[NSString alloc] initWithFormat:@"%@",[pParsers getFieldData:i fieldFlag:TDX_ID_ZJZH]];
				pyhmx.nzrmmflag=[[pParsers getFieldData:i fieldFlag:TDX_ID_YZZZ_ZRMM] intValue];
				pyhmx.nzcmmflag=[[pParsers getFieldData:i fieldFlag:TDX_ID_YZZZ_ZCMM] intValue];
				pyhmx.nyemmflag=[[pParsers getFieldData:i fieldFlag:TDX_ID_YZZZ_YHYEMM] intValue];
				[clientinfos.yhxxs.yhmxs addObject:pyhmx];
			}
		}
		/////////保存银行信息到clientinfos////////////
		return YES;
		
	}	
	else{//银行查询失败
		return NO;
	}
	
}


#pragma mark 	委托类
-(BOOL) getCDCXInfo:(NSMutableArray *)showData
{
	if(g_TradeComm.readData==nil)
		return NO;
	if([g_TradeComm.readData length]<=0)
		return NO;
	char m_cTag=0;
	NSString * tempString;
	NSData * theData = [[NSData alloc] initWithData:g_TradeComm.readData];
	NSMutableArray * tempArray;
	
	[theData getTdxBytes:&m_cTag range:NSMakeRange(g_TradeComm.httpFlag, sizeof(char))];
	//验证合法性
	if(m_cTag == '0')
	{
		tempString = [[NSString alloc] initWithData:[theData subdataWithRange:NSMakeRange(g_TradeComm.httpFlag+HEADER_LEN, [theData length]-g_TradeComm.httpFlag-HEADER_LEN)] encoding:CFStringConvertEncodingToNSStringEncoding (kCFStringEncodingGB_18030_2000)];
			
		[parseRecv getRecvJx:tempString];
		
		if(parseRecv.nJls > 0)
		{
			for (int i = 0; i<parseRecv.nJls; i++) {
				tempArray = [[NSMutableArray alloc] init];
				[showData addObject:[parseRecv getItemData:tempArray Index:i TDX_Choise:TDX_CDCX]];
				[tempArray release];
			}
		}	
		
		[theData release];
		[tempString release];
		return YES;
		
	}	
	else{//撤单查询失败
		tempString = [[NSString alloc] initWithData:[theData subdataWithRange:NSMakeRange(g_TradeComm.httpFlag, [theData length]-g_TradeComm.httpFlag)] encoding:CFStringConvertEncodingToNSStringEncoding (kCFStringEncodingGB_18030_2000)];
			[parseRecv getRecvJx:tempString];
		
		[theData release];
		[tempString release];
		return NO;
	}
}

-(BOOL) getLXCXInfo:(ParseRecv *)pParsers
{
	if(pParsers==nil)
		return NO;
	NSMutableArray * tempArray;
	[lxfsArray removeAllObjects];
	//验证合法性
	if(pParsers.bsucflag)
	{
		if(pParsers.nrownum > 0)
		{
			for (int i = 0; i<pParsers.nrownum; i++) {
				tempArray = [[NSMutableArray alloc] init];
				[lxfsArray addObject:[pParsers getItemData:tempArray Index:i TDX_Choise:TDX_LXCX]];
				[tempArray release];
			}
		}	
		return YES;
		
	}	
	else{//股份查询失败
		return NO;
	}
}

-(BOOL) getGFCXInfoHK:(NSMutableArray *)showData{
	if(g_TradeComm.readData==nil)
		return NO;
	if([g_TradeComm.readData length]<=0)
		return NO;
	char m_cTag=0;
	NSString * tempString;
	NSData * theData = [[NSData alloc] initWithData:g_TradeComm.readData];
	NSMutableArray * tempArray;
	
	[theData getTdxBytes:&m_cTag range:NSMakeRange(g_TradeComm.httpFlag, sizeof(char))];
	//验证合法性
	if(m_cTag == '0')
	{
		//MyNsLog(@"lenx87");
		tempString = [[NSString alloc] initWithData:[theData subdataWithRange:NSMakeRange(g_TradeComm.httpFlag+HEADER_LEN, [theData length]-g_TradeComm.httpFlag-HEADER_LEN)] encoding:CFStringConvertEncodingToNSStringEncoding (kCFStringEncodingGB_18030_2000)];
		
		[parseRecv getRecvJx:tempString];
		
		if(parseRecv.nJls > 0)
		{
			for (int i = 0; i<parseRecv.nJls; i++) {
				tempArray = [[NSMutableArray alloc] init];
				[showData addObject:[parseRecv getItemData:tempArray Index:i TDX_Choise:TDX_GFCX_HK]];
				[tempArray release];
			}
		}	
		
		[theData release];
		[tempString release];
		return YES;
		
	}	
	else{//股份查询失败
		tempString = [[NSString alloc] initWithData:[theData subdataWithRange:NSMakeRange(g_TradeComm.httpFlag, [theData length]-g_TradeComm.httpFlag)] encoding:CFStringConvertEncodingToNSStringEncoding (kCFStringEncodingGB_18030_2000)];
		[parseRecv getRecvJx:tempString];
		
		[theData release];
		[tempString release];
		return NO;
	}
}


-(NSString *) getCXInfo:(ParseRecv *)pParsers withparse2:(ParseRecv *)pParsers2 listdata:(NSMutableArray *)showData withqueryindex:(int)queryindex withrownum:(int *)ntotalline withsucflag:(BOOL *)bsucflag{
	(*ntotalline)=0;
	(*bsucflag)=NO;
	if(pParsers==nil)
		return @"";
	NSString *positionstr=@"";
	NSMutableArray * tempArray=nil,*tempdata=nil;
	int colcount=0;
	if(pParsers.bsucflag)
	{
		(*bsucflag)=YES;
		
		if(pParsers.nrownum > 0)
		{
			NSString* strTotalLines = [pParsers getFieldData:0 fieldFlag:TDX_ID_TOTALLINE];
			positionstr=[pParsers getFieldData:0 fieldFlag:TDX_ID_XT_POSITIONSTRING];
			(*ntotalline)=[strTotalLines intValue];
			RecvField *pfield=nil;
			NSString *tmpstr=nil;
			CGSize strsize;
			ZjgfInfoClass *zjgfclass=nil;
			if(queryindex==TDX_ZJYE)
			{
				zjgfclass=[ZjgfInfoClass new];
				zjgfclass.stzjgf=clientinfos.strawzjgf;
			}
			for (int i = 0,j=0; i<pParsers.nrownum && i<[pParsers.sData count]; i++) {
				tempdata=[pParsers.sData objectAtIndex:i];
				if(tempdata==nil)
					continue;
				tempArray = [[NSMutableArray alloc] init];
				if(queryindex==TDX_ZJYE)
				{
					pParsers.m_nqsid=clientinfos.m_nQsbs;
					[showData addObject:[pParsers getItemData2:tempArray Index:i TDX_Choise:queryindex withclientinfo:clientinfos withzjgf:zjgfclass]];
					if(pParsers2)
					{
						colcount=MIN([pParsers2.sFieldColstr count],[tempArray count]);
						for(j=0;j<colcount;j++)
						{
							pfield=[pParsers2.sFieldColstr objectAtIndex:j];
							if(pfield)
							{
								tmpstr=[tempArray objectAtIndex:j];
								NSDictionary * tempAttributes= [self getAttributes:MAC_CHINESEFONT fontSize:20.0f theColor:[NSColor whiteColor] theAliment:NSCenterTextAlignment];
								NSRect temprect = [tmpstr boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
								strsize = CGSizeMake(temprect.size.width, temprect.size.height);
								
								if(strsize.width>pfield.maxwidth)
									pfield.maxwidth=strsize.width;
							}
						}
					}
				}
				[tempArray release];
			}
			if(queryindex==TDX_ZJYE)
			{
				clientinfos.stzjgf=zjgfclass.stzjgf;
				[zjgfclass release];
			}
		}	
		
		return positionstr;
	}	
	else 
	{
		(*ntotalline)=-2;
		if(pParsers.btipflag)
		{
			if (!showAlertFlag) {
				NSString *errinfo=[NSString stringWithFormat:@"错误信息:%@,%@",pParsers.psErrorNum,pParsers.psErrorData];
				
				NSAlert* alert = [NSAlert alertWithMessageText: @"提示"
												 defaultButton: @"确定"
											   alternateButton: nil
												   otherButton: nil
									 informativeTextWithFormat: @"%@",errinfo];
				
				showAlertFlag = YES;
				[alert setDelegate:self];
				NSInteger result = [alert runModal];
				[self handleResult:alert withResult:result];
			}
			
			
		}
	}
	return @"";
}


-(NSString *)getCXInfo:(ParseRecv *)pParsers listdata:(NSMutableArray *)showData withqueryindex:(int)queryindex withrownum:(int *)ntotalline withsucflag:(BOOL *)bsucflag{
	(*ntotalline)=0;
	(*bsucflag)=NO;
	if(pParsers==nil)
		return @"";
	NSString *positionstr=@"";
    double allckjz = 0.0;
	NSMutableArray * tempArray=nil,*tempdata=nil;
	
	if(pParsers.bsucflag)
	{
		(*bsucflag)=YES;
		if(pParsers.nrownum > 0)
		{
			NSString* strTotalLines = [pParsers getFieldData:0 fieldFlag:TDX_ID_TOTALLINE];
#ifdef QUERY_LOOPEND
			positionstr=[pParsers getFieldData:pParsers.nrownum-1 fieldFlag:TDX_ID_XT_POSITIONSTRING];
#else
            positionstr=[pParsers getFieldData:0 fieldFlag:TDX_ID_XT_POSITIONSTRING];
#endif
			(*ntotalline)=[strTotalLines intValue];
			BOOL bjjcdflag=NO;
			CGSize strsize;
			RecvField *pfield=nil;
			NSString *tmpstr=nil,*tmpstr1=nil;
            NSString *mainzjzh=nil;
			ZjgfInfoClass *zjgfclass=nil;
            double zzall = 0.0; //人民币
            double zzallGY = 0.00;
            double zzallMY = 0.000;
			if(queryindex==TDX_ZJYE || queryindex==TDX_ZJYE2 || queryindex==TDX_ZJYE3)
			{
				zjgfclass=[ZjgfInfoClass new];
				if(queryindex==TDX_ZJYE)
					zjgfclass.stzjgf=clientinfos.strawzjgf;
				else if(queryindex==TDX_ZJYE2)
					zjgfclass.stzjgf=clientinfos.strawzjgfjj;
				else 
					zjgfclass.stzjgf=clientinfos.strawzjgflc;
			}
            int sCount = [pParsers.sData count];
			for (int i = 0,j=0; i<pParsers.nrownum && i<sCount; i++) {
				tempdata=[pParsers.sData objectAtIndex:i];
                int bzzj = [[tempdata objectAtIndex:1] intValue];
				if(tempdata==nil)
					continue;
				tempArray = [[NSMutableArray alloc] init];
				if(queryindex==TDX_JJWT)
				{
					for(j=0;j<[pParsers.sFieldColstr count] && j<[tempdata count];j++)
					{
						pfield=[pParsers.sFieldColstr objectAtIndex:j];
						if(pfield.m_bvisible)
							[tempArray addObject:[NSString stringWithFormat:@"%@",[tempdata objectAtIndex:j]]];
					}
					if(j>0)
					{
						[pParsers getItemData1:tempArray Index:i TDX_Choise:queryindex withflag:(BOOL *)&bjjcdflag];
						if(bjjcdflag==NO)
							(*ntotalline)--;
						else 
							[showData addObject:tempArray];
					}
					else 
						(*ntotalline)--;
				}
				else if(queryindex==TDX_ZJYE || queryindex==TDX_ZJYE2 || queryindex==TDX_ZJYE3 || queryindex==TDX_GDCX)
				{
#ifdef IMAC_PAZQ
//                    if(bzzj == 0)
//                    {
//                        zzall += [[tempdata objectAtIndex:8] doubleValue];
//                        if(i+1 == sCount)
//                        {
//                            ST_ZJGFINFO tmpzjgf=zjgfclass.stzjgf;
//                            tmpzjgf.zzc[bzzj]= zzall;
//                            zjgfclass.stzjgf = tmpzjgf;
//                        }
//                    }
                    
                    switch (bzzj)
                    {
                        case 0:
                        {
                            zzall += [[tempdata objectAtIndex:8] doubleValue];
                            
                            break;
                        }
                        case 1:
                        {
                            zzallMY += [[tempdata objectAtIndex:8] doubleValue];
                            break;
                        }
                        case 2:
                        {
                            zzallGY += [[tempdata objectAtIndex:8] doubleValue];
                            break;
                        }
                        default:
                            break;
                    }
                    
                    if(i+1 == sCount)
                    {
                        ST_ZJGFINFO tmpzjgf=zjgfclass.stzjgf;
                        tmpzjgf.zzc[0]= zzall;
                        tmpzjgf.zzc[1]= zzallMY;
                        tmpzjgf.zzc[2]= zzallGY;
                        zjgfclass.stzjgf = tmpzjgf;
                    }
                
                    mainzjzh = clientinfos.m_realzjzh[0];
                    if([mainzjzh isEqualToString:@""]
                       || mainzjzh.length < 2
                       || ![mainzjzh isEqualToString:tempdata[0]]) continue;
#endif
                    
                    pParsers.m_nqsid=clientinfos.m_nQsbs;
					[showData addObject:[pParsers getItemData2:tempArray Index:i TDX_Choise:queryindex withclientinfo:clientinfos withzjgf:zjgfclass]];
#ifdef IMAC_PAZQ
                    allckjz = [[tempdata objectAtIndex:7] doubleValue];
                    if(allckjz > 0.001)
                    {
                        ST_ZJGFINFO tmpzjgf=zjgfclass.stzjgf;
                        tmpzjgf.zsz[bzzj]=allckjz;
                        if(bzzj == 0)
                        {
                            tmpzjgf.zzc[bzzj]= zzall;
                        }
                        else if(bzzj == 1)
                        {
                            tmpzjgf.zzc[1]= zzallMY;
                        }
                        else
                        {
                            tmpzjgf.zzc[2]= zzallGY;
                        }
                        zjgfclass.stzjgf = tmpzjgf;
                    }
#endif
				}
				else
				{
					for(j=0;j<[pParsers.sFieldColstr count] && j<[tempdata count];j++)
					{
						pfield=[pParsers.sFieldColstr objectAtIndex:j];
                        NSLog(@"%@ %i  %@",pfield.m_sFieldName,pfield.m_dwFieldId,[tempdata objectAtIndex:j]);
						if(pfield.m_bvisible)
						{
                            if(queryindex == TDX_ZJLS)
                            {
                                if(saveDate.nzjlsBZ != 3 && saveDate.nzjlsBZ != [[tempdata objectAtIndex:4] intValue])
                                {
                                    [tempArray addObject:@""];
                                    continue;
                                }
                                
                                if(j == 4) //币种
                                {
                                    int nbz=[[tempdata objectAtIndex:4] intValue];
                                    if(nbz == 0)
                                        [tempArray addObject:@"人民币"];
                                    else if(nbz == 1)
                                        [tempArray addObject:@"美元"];
                                    else
                                        [tempArray addObject:@"港币"];
                                }
                                else
                                {
                                    [tempArray addObject:[NSString stringWithFormat:@"%@",[tempdata objectAtIndex:j]]];
                                }
                            }
                            else if(queryindex == TDX_DRCJ)
                            {
                                if([[tempdata objectAtIndex:5] isEqualToString:@"撤卖"]
                                   ||[[tempdata objectAtIndex:5] isEqualToString:@"撤买"])
                                {
                                    continue;
                                }
                                
                                [tempArray addObject:[NSString stringWithFormat:@"%@",[tempdata objectAtIndex:j]]];
                            }
							else if(pfield.m_dwFieldId==TDX_ID_BZ)
							{
								tmpstr=[tempdata objectAtIndex:j];
								tmpstr1=[self GetBzStr:[tmpstr intValue]];
								NSDictionary * tempAttributes= [self getAttributes:MAC_CHINESEFONT fontSize:20.0f theColor:[NSColor whiteColor] theAliment:NSCenterTextAlignment];
								NSRect temprect = [tmpstr1 boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
								strsize = CGSizeMake(temprect.size.width, temprect.size.height);
								
								if(strsize.width>pfield.maxwidth)
									pfield.maxwidth=strsize.width;
								[tempArray addObject:tmpstr1];
							}
                            else if(pfield.m_dwFieldId==TDX_ID_XT_REMARK)
                            {
                                NSMutableString *tmpstrs=[[NSMutableString alloc] initWithString:[tempdata objectAtIndex:j]];
                                [tmpstrs replaceOccurrencesOfString:@"\\s" withString:@" " options:NSCaseInsensitiveSearch range:NSMakeRange(0, [tmpstrs length])];
                                [tempArray addObject:tmpstrs];
                                [tmpstrs release];
                            }
							else
                            {
//                                tmpstr=[tempdata objectAtIndex:j];
//                                if(pfield.m_dwFieldId==5547 && (tmpstr == nil || [tmpstr isEqualToString:@""]))
//                                {
//                                    continue;
//                                }
                                
                                [tempArray addObject:[NSString stringWithFormat:@"%@",[tempdata objectAtIndex:j]]];
                            }
						}
					}
					if(j>0)
                    {
                        switch (queryindex)
                        {
                            case TDX_DRCJ:
                                if(tempArray.count > 10)
                                {
                                    [showData addObject:[pParsers getItemData:tempArray Index:i TDX_Choise:queryindex]];
                                }
                                break;
                                
                            default:
                                [showData addObject:[pParsers getItemData:tempArray Index:i TDX_Choise:queryindex]];
                                break;
                        }
                        
                    }
				}
                
				[tempArray release];
			}
			if(queryindex==TDX_ZJYE || queryindex==TDX_ZJYE2 || queryindex==TDX_ZJYE3)
			{
				if(queryindex==TDX_ZJYE)
					clientinfos.stzjgf=zjgfclass.stzjgf;
				else if(queryindex==TDX_ZJYE2)
					clientinfos.stzjgfjj=zjgfclass.stzjgf;
				else 
					clientinfos.stzjgflc=zjgfclass.stzjgf;
				[zjgfclass release];
			}
		}	
		
		return positionstr;
	}	
	else
	{
		(*ntotalline)=-2;
		if(pParsers.btipflag)
		{
			if (!showAlertFlag) {
				NSString *errinfo=[NSString stringWithFormat:@"错误信息:%@,%@",pParsers.psErrorNum,pParsers.psErrorData];
				NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
												 defaultButton: @"确定"
											   alternateButton: nil
												   otherButton: nil
									 informativeTextWithFormat: @"%@",errinfo];
				showAlertFlag = YES;
				[alert setDelegate:self];
				NSInteger result = [alert runModal];
				[self handleResult:alert withResult:result];
				
			}
				
			
		}
	}
	return @"";
}

-(BOOL) getDRWTInfoHK:(NSMutableArray *)showData
{
	if(g_TradeComm.readData==nil)
		return NO;
	if([g_TradeComm.readData length]<=0)
		return NO;
	char m_cTag=0;
	NSString * tempString;
	NSData * theData = [[NSData alloc] initWithData:g_TradeComm.readData];
	NSMutableArray * tempArray;
	
	[theData getTdxBytes:&m_cTag range:NSMakeRange(g_TradeComm.httpFlag, sizeof(char))];
	//验证合法性
	if(m_cTag == '0')
	{
		tempString = [[NSString alloc] initWithData:[theData subdataWithRange:NSMakeRange(g_TradeComm.httpFlag+HEADER_LEN, [theData length]-g_TradeComm.httpFlag-HEADER_LEN)] encoding:CFStringConvertEncodingToNSStringEncoding (kCFStringEncodingGB_18030_2000)];
		
		[parseRecv getRecvJx:tempString];
		
		if(parseRecv.nJls > 0)
		{
			for (int i = 0; i<parseRecv.nJls; i++) {
				tempArray = [[NSMutableArray alloc] init];
				[showData addObject:[parseRecv getItemData:tempArray Index:i TDX_Choise:TDX_DRWT_HK]];
				[tempArray release];
			}
		}	
		
		[theData release];
		[tempString release];
		return YES;
		
	}	
	else{//撤单查询失败
		tempString = [[NSString alloc] initWithData:[theData subdataWithRange:NSMakeRange(g_TradeComm.httpFlag, [theData length]-g_TradeComm.httpFlag)] encoding:CFStringConvertEncodingToNSStringEncoding (kCFStringEncodingGB_18030_2000)];
		[parseRecv getRecvJx:tempString];
		
		[theData release];
		[tempString release];
		return NO;
	}
	
}

-(BOOL) getWTCXInfoHK:(NSMutableArray*) showData
{
	if(g_TradeComm.readData==nil)
		return NO;
	if([g_TradeComm.readData length]<=0)
		return NO;
	char m_cTag=0;
	NSString * tempString;
	NSData * theData = [[NSData alloc] initWithData:g_TradeComm.readData];
	NSMutableArray * tempArray;
	
	[theData getTdxBytes:&m_cTag range:NSMakeRange(g_TradeComm.httpFlag, sizeof(char))];
	//验证合法性
	if(m_cTag == '0')
	{
		tempString = [[NSString alloc] initWithData:[theData subdataWithRange:NSMakeRange(g_TradeComm.httpFlag+HEADER_LEN, [theData length]-g_TradeComm.httpFlag-HEADER_LEN)] encoding:CFStringConvertEncodingToNSStringEncoding (kCFStringEncodingGB_18030_2000)];
		
		[parseRecv getRecvJx:tempString];
		
		if(parseRecv.nJls > 0)
		{
			for (int i = 0; i<parseRecv.nJls; i++) {
				tempArray = [[NSMutableArray alloc] init];
				[showData addObject:[parseRecv getItemData:tempArray Index:i TDX_Choise:TDX_WTCX_HK]];
				[tempArray release];
			}
		}	
		
		[theData release];
		[tempString release];
		return YES;
		
	}	
	else{//历史委托查询失败
		tempString = [[NSString alloc] initWithData:[theData subdataWithRange:NSMakeRange(g_TradeComm.httpFlag, [theData length]-g_TradeComm.httpFlag)] encoding:CFStringConvertEncodingToNSStringEncoding (kCFStringEncodingGB_18030_2000)];
		[parseRecv getRecvJx:tempString];
		
		[theData release];
		[tempString release];
		return NO;
	}
}

-(BOOL) getCJCXInfoHK:(NSMutableArray*) showData
{
	if(g_TradeComm.readData==nil)
		return NO;
	if([g_TradeComm.readData length]<=0)
		return NO;
	char m_cTag=0;
	NSString * tempString;
	NSData * theData = [[NSData alloc] initWithData:g_TradeComm.readData];
	NSMutableArray * tempArray;
	
	[theData getTdxBytes:&m_cTag range:NSMakeRange(g_TradeComm.httpFlag, sizeof(char))];
	//验证合法性
	if(m_cTag == '0')
	{
		tempString = [[NSString alloc] initWithData:[theData subdataWithRange:NSMakeRange(g_TradeComm.httpFlag+HEADER_LEN, [theData length]-g_TradeComm.httpFlag-HEADER_LEN)] encoding:CFStringConvertEncodingToNSStringEncoding (kCFStringEncodingGB_18030_2000)];
		
		[parseRecv getRecvJx:tempString];
		
		if(parseRecv.nJls > 0)
		{
			for (int i = 0; i<parseRecv.nJls; i++) {
				tempArray = [[NSMutableArray alloc] init];
				[showData addObject:[parseRecv getItemData:tempArray Index:i TDX_Choise:TDX_CJCX_HK]];
				[tempArray release];
			}
		}	
		
		[theData release];
		[tempString release];
		return YES;
		
	}	
	else{//历史成交查询失败
		tempString = [[NSString alloc] initWithData:[theData subdataWithRange:NSMakeRange(g_TradeComm.httpFlag, [theData length]-g_TradeComm.httpFlag)] encoding:CFStringConvertEncodingToNSStringEncoding (kCFStringEncodingGB_18030_2000)];
		[parseRecv getRecvJx:tempString];
		
		[theData release];
		[tempString release];
		return NO;
	}
}

-(BOOL) getGFBDInfoHK:(NSMutableArray*) showData
{
	if(g_TradeComm.readData==nil)
		return NO;
	if([g_TradeComm.readData length]<=0)
		return NO;
	char m_cTag=0;
	NSString * tempString;
	NSData * theData = [[NSData alloc] initWithData:g_TradeComm.readData];
	NSMutableArray * tempArray;
	
	[theData getTdxBytes:&m_cTag range:NSMakeRange(g_TradeComm.httpFlag, sizeof(char))];
	//验证合法性
	if(m_cTag == '0')
	{
		tempString = [[NSString alloc] initWithData:[theData subdataWithRange:NSMakeRange(g_TradeComm.httpFlag+HEADER_LEN, [theData length]-g_TradeComm.httpFlag-HEADER_LEN)] encoding:CFStringConvertEncodingToNSStringEncoding (kCFStringEncodingGB_18030_2000)];
		
		[parseRecv getRecvJx:tempString];
		
		if(parseRecv.nJls > 0)
		{
			for (int i = 0; i<parseRecv.nJls; i++) {
				tempArray = [[NSMutableArray alloc] init];
				[showData addObject:[parseRecv getItemData:tempArray Index:i TDX_Choise:TDX_GFBD_HK]];
				[tempArray release];
			}
		}	
		
		[theData release];
		[tempString release];
		return YES;
		
	}	
	else{//股份变动查询失败
		tempString = [[NSString alloc] initWithData:[theData subdataWithRange:NSMakeRange(g_TradeComm.httpFlag, [theData length]-g_TradeComm.httpFlag)] encoding:CFStringConvertEncodingToNSStringEncoding (kCFStringEncodingGB_18030_2000)];
		[parseRecv getRecvJx:tempString];
		
		[theData release];
		[tempString release];
		return NO;
	}
}

-(BOOL) getZJLSInfoHK:(NSMutableArray*) showData
{
	if(g_TradeComm.readData==nil)
		return NO;
	if([g_TradeComm.readData length]<=0)
		return NO;
	char m_cTag=0;
	NSString * tempString;
	NSData * theData = [[NSData alloc] initWithData:g_TradeComm.readData];
	NSMutableArray * tempArray;
	
	[theData getTdxBytes:&m_cTag range:NSMakeRange(g_TradeComm.httpFlag, sizeof(char))];
	//验证合法性
	if(m_cTag == '0')
	{
		tempString = [[NSString alloc] initWithData:[theData subdataWithRange:NSMakeRange(g_TradeComm.httpFlag+HEADER_LEN, [theData length]-g_TradeComm.httpFlag-HEADER_LEN)] encoding:CFStringConvertEncodingToNSStringEncoding (kCFStringEncodingGB_18030_2000)];
		
		[parseRecv getRecvJx:tempString];
		
		if(parseRecv.nJls > 0)
		{
			for (int i = 0; i<parseRecv.nJls; i++) {
				tempArray = [[NSMutableArray alloc] init];
				[showData addObject:[parseRecv getItemData:tempArray Index:i TDX_Choise:TDX_ZJLS_HK]];
				[tempArray release];
			}
		}	
		
		[theData release];
		[tempString release];
		return YES;
		
	}	
	else{//资金流水查询失败
		tempString = [[NSString alloc] initWithData:[theData subdataWithRange:NSMakeRange(g_TradeComm.httpFlag, [theData length]-g_TradeComm.httpFlag)] encoding:CFStringConvertEncodingToNSStringEncoding (kCFStringEncodingGB_18030_2000)];
		[parseRecv getRecvJx:tempString];
		
		[theData release];
		[tempString release];
		return NO;
	}
}

-(BOOL) getIPOLBInfoHK:(NSMutableArray*) showData
{
	if(g_TradeComm.readData==nil)
		return NO;
	if([g_TradeComm.readData length]<=0)
		return NO;
	char m_cTag=0;
	NSString * tempString;
	NSData * theData = [[NSData alloc] initWithData:g_TradeComm.readData];
	NSMutableArray * tempArray;
	
	[theData getTdxBytes:&m_cTag range:NSMakeRange(g_TradeComm.httpFlag, sizeof(char))];
	//验证合法性
	if(m_cTag == '0')
	{
		tempString = [[NSString alloc] initWithData:[theData subdataWithRange:NSMakeRange(g_TradeComm.httpFlag+HEADER_LEN, [theData length]-g_TradeComm.httpFlag-HEADER_LEN)] encoding:CFStringConvertEncodingToNSStringEncoding (kCFStringEncodingGB_18030_2000)];
		
		[parseRecv getRecvJx:tempString];
		
		if(parseRecv.nJls > 0)
		{
			for (int i = 0; i<parseRecv.nJls; i++) {
				tempArray = [[NSMutableArray alloc] init];
				[showData addObject:[parseRecv getItemData:tempArray Index:i TDX_Choise:TDX_IPOLB_HK]];
				[tempArray release];
			}
		}	
		
		[theData release];
		[tempString release];
		return YES;
		
	}	
	else{//IPO列表查询失败
		tempString = [[NSString alloc] initWithData:[theData subdataWithRange:NSMakeRange(g_TradeComm.httpFlag, [theData length]-g_TradeComm.httpFlag)] encoding:CFStringConvertEncodingToNSStringEncoding (kCFStringEncodingGB_18030_2000)];
		[parseRecv getRecvJx:tempString];
		
		[theData release];
		[tempString release];
		return NO;
	}
}

-(BOOL) getIPOPHInfoHK:(NSMutableArray*) showData
{
	if(g_TradeComm.readData==nil)
		return NO;
	if([g_TradeComm.readData length]<=0)
		return NO;
	char m_cTag=0;
	NSString * tempString;
	NSData * theData = [[NSData alloc] initWithData:g_TradeComm.readData];
	NSMutableArray * tempArray;
	
	[theData getTdxBytes:&m_cTag range:NSMakeRange(g_TradeComm.httpFlag, sizeof(char))];
	//验证合法性
	if(m_cTag == '0')
	{
		tempString = [[NSString alloc] initWithData:[theData subdataWithRange:NSMakeRange(g_TradeComm.httpFlag+HEADER_LEN, [theData length]-g_TradeComm.httpFlag-HEADER_LEN)] encoding:CFStringConvertEncodingToNSStringEncoding (kCFStringEncodingGB_18030_2000)];
		
		[parseRecv getRecvJx:tempString];
		
		if(parseRecv.nJls > 0)
		{
			for (int i = 0; i<parseRecv.nJls; i++) {
				tempArray = [[NSMutableArray alloc] init];
				[showData addObject:[parseRecv getItemData:tempArray Index:i TDX_Choise:TDX_IPOPH_HK]];
				[tempArray release];
			}
		}	
		
		[theData release];
		[tempString release];
		return YES;
		
	}	
	else{//IPO配号查询失败
		tempString = [[NSString alloc] initWithData:[theData subdataWithRange:NSMakeRange(g_TradeComm.httpFlag, [theData length]-g_TradeComm.httpFlag)] encoding:CFStringConvertEncodingToNSStringEncoding (kCFStringEncodingGB_18030_2000)];
		[parseRecv getRecvJx:tempString];
		
		[theData release];
		[tempString release];
		return NO;
	}
}

-(BOOL) getJjdmInfo:(ParseRecv *)pParsers
{
	if(pParsers==nil)
		return NO;

	if(pParsers.bsucflag)
	{
		if(clientinfos.jjinfos.jjsgdminfo)
		{
			[clientinfos.jjinfos.jjsgdminfo removeAllObjects];
			clientinfos.jjinfos.jjsgdminfo=nil;
		}
		if(clientinfos.jjinfos.jjrgdminfo)
		{
			[clientinfos.jjinfos.jjrgdminfo removeAllObjects];
			clientinfos.jjinfos.jjrgdminfo=nil;
		}
		if(clientinfos.jjinfos.jjdminfo)
		{
			for(JjdmInfo *pjjdm in clientinfos.jjinfos.jjdminfo)
			{
				RELEASEOBJ(pjjdm)
			}
			[clientinfos.jjinfos.jjdminfo removeAllObjects];
			clientinfos.jjinfos.jjdminfo=nil;
			clientinfos.jjinfos.nkrgjjnum=0;
			clientinfos.jjinfos.nksgjjnum=0;
			clientinfos.jjinfos.njjnum=0;
		}
		
		//MyNsLog(@"lenx117");
		if(pParsers.nrownum > 0)
		{
			clientinfos.jjinfos.jjdminfo=[[NSMutableArray alloc] initWithCapacity:pParsers.nrownum+1];
			[clientinfos.jjinfos.jjdminfo release];
			clientinfos.jjinfos.jjsgdminfo=[[NSMutableArray alloc] initWithCapacity:pParsers.nrownum+1];
			[clientinfos.jjinfos.jjsgdminfo release];
			clientinfos.jjinfos.jjrgdminfo=[[NSMutableArray alloc] initWithCapacity:pParsers.nrownum+1];
			[clientinfos.jjinfos.jjrgdminfo release];
			clientinfos.jjinfos.jjdmdict=[[NSMutableDictionary alloc] initWithCapacity:pParsers.nrownum+1];
			[clientinfos.jjinfos.jjdmdict release];
			JjdmInfo *pjjdm=nil;
			for (int i = 0;i<pParsers.nrownum; i++)
			{
				pjjdm=[JjdmInfo new];
				pjjdm.jjgsdm=[[NSString alloc]  initWithFormat:@"%@",[pParsers getFieldData:i fieldFlag:TDX_ID_KFSJJ_JJGSDM]];
				[pjjdm.jjgsdm release];
				pjjdm.jjdm=[[NSString alloc]  initWithFormat:@"%@",[pParsers getFieldData:i fieldFlag:TDX_ID_KFSJJ_JJDM]];
				[pjjdm.jjdm release];
				pjjdm.jjmc=[[NSString alloc]  initWithFormat:@"%@",[pParsers getFieldData:i fieldFlag:TDX_ID_KFSJJ_JJMC]];
				[pjjdm.jjmc release];
				pjjdm.jjjyzt=[[NSString alloc]  initWithFormat:@"%@",[pParsers getFieldData:i fieldFlag:TDX_ID_ZTSM]];
				[pjjdm.jjjyzt release];
				pjjdm.jjjz=[[pParsers getFieldData:i fieldFlag:TDX_ID_KFSJJ_JJJZ]floatValue];
				pjjdm.grzdsgje=[[pParsers getFieldData:i fieldFlag:TDX_ID_KFSJJ_GRZDRGJE]floatValue];
				pjjdm.frzdsgje=[[pParsers getFieldData:i fieldFlag:TDX_ID_KFSJJ_FRZDRGJE]floatValue];
				pjjdm.njjjyzt=[[pParsers getFieldData:i fieldFlag:TDX_ID_KFSJJ_JJZT]intValue];
				pjjdm.zdcyfe=[[pParsers getFieldData:i fieldFlag:TDX_ID_KFSJJ_ZDCYFE]floatValue];
				pjjdm.zgshfe=[[pParsers getFieldData:i fieldFlag:TDX_ID_KFSJJ_ZGSHFE]doubleValue];
				pjjdm.njjbs=[[pParsers getFieldData:i fieldFlag:TDX_ID_KFSJJ_JJBS]intValue];
				
				[clientinfos.jjinfos.jjdminfo addObject:pjjdm];
				[clientinfos.jjinfos.jjdmdict setObject:pjjdm forKey:pjjdm.jjdm];
				
				
				if(pjjdm.njjjyzt==0)
				{
					clientinfos.jjinfos.nksgjjnum++;
					[clientinfos.jjinfos.jjsgdminfo addObject:pjjdm];
				}
				else if(pjjdm.njjjyzt==1)
				{
					clientinfos.jjinfos.nkrgjjnum++;
					[clientinfos.jjinfos.jjrgdminfo addObject:pjjdm];
				}
				clientinfos.jjinfos.njjnum++;
			}
		}	
		return YES;
		
	}	
	else{//基金代码查询失败
		return NO;
	}
}

-(BOOL) getJjZhInfo:(ParseRecv *)pParsers
{
	if(pParsers==nil)
		return NO;
	if(pParsers.bsucflag)
	{
		if(clientinfos.jjinfos.jjzhinfo)
		{
			for(JjZhInfo *pjjzh in clientinfos.jjinfos.jjzhinfo)
			{
				RELEASEOBJ(pjjzh)
			}
			[clientinfos.jjinfos.jjzhinfo removeAllObjects];
			clientinfos.jjinfos.jjzhinfo=nil;
		}
		
		if(pParsers.nrownum > 0)
		{
			clientinfos.jjinfos.jjzhinfo=[[NSMutableArray alloc] initWithCapacity:pParsers.nrownum+1];
			[clientinfos.jjinfos.jjzhinfo release];
			clientinfos.jjinfos.jjzhdict=[[NSMutableDictionary alloc] initWithCapacity:pParsers.nrownum+1];
			[clientinfos.jjinfos.jjzhdict release];
			JjZhInfo *pjjzh=nil;
			for (int i = 0;i<pParsers.nrownum; i++)
			{
				pjjzh=[JjZhInfo new];
				pjjzh.jjgsdm=[[NSString alloc]  initWithFormat:@"%@",[pParsers getFieldData:i fieldFlag:TDX_ID_KFSJJ_JJGSDM]];
				[pjjzh.jjgsdm release];
				pjjzh.jjgsmc=[[NSString alloc]  initWithFormat:@"%@",[pParsers getFieldData:i fieldFlag:TDX_ID_KFSJJ_JJGSMC]];
				[pjjzh.jjgsmc release];
				pjjzh.jjzh=[[NSString alloc]  initWithFormat:@"%@",[pParsers getFieldData:i fieldFlag:TDX_ID_KFSJJ_JJZH]];
				[pjjzh.jjzh release];
				pjjzh.khmc=[[NSString alloc]  initWithFormat:@"%@",[pParsers getFieldData:i fieldFlag:TDX_ID_KHMC]];
				[pjjzh.khmc release];
				pjjzh.zjhm=[[NSString alloc]  initWithFormat:@"%@",[pParsers getFieldData:i fieldFlag:TDX_ID_ZJHM]];
				[pjjzh.zjhm release];
				[clientinfos.jjinfos.jjzhinfo addObject:pjjzh];
				[clientinfos.jjinfos.jjzhdict setObject:pjjzh forKey:pjjzh.jjgsdm];
			}
		}	
		return YES;
		
	}	
	else{//基金代码查询失败
		return NO;
	}
	
}

-(BOOL) getJjgsInfo:(ParseRecv *)pParsers
{
	if(pParsers==nil)
		return NO;
	if(pParsers.bsucflag)
	{
		if(clientinfos.jjinfos.jjgsinfo)
		{
			for(JjgsInfo *pjjgs in clientinfos.jjinfos.jjgsinfo)
			{
				RELEASEOBJ(pjjgs)
			}
			[clientinfos.jjinfos.jjgsinfo removeAllObjects];
			clientinfos.jjinfos.jjgsinfo=nil;
		}
		
		if(pParsers.nrownum> 0)
		{
			clientinfos.jjinfos.jjgsinfo=[[NSMutableArray alloc] initWithCapacity:pParsers.nrownum+1];
			[clientinfos.jjinfos.jjgsinfo release];
			JjgsInfo *pjjgs=nil;
			NSString *gsdm=nil;
			for (int i = 0;i<pParsers.nrownum; i++)
			{
				gsdm=[pParsers getFieldData:i fieldFlag:TDX_ID_KFSJJ_JJGSDM];
				if([clientinfos.tradeccf IsExceptLcgsdm:gsdm])
					continue;
				pjjgs=[JjgsInfo new];
				pjjgs.jjgsdm=[[NSString alloc]  initWithFormat:@"%@",[pParsers getFieldData:i fieldFlag:TDX_ID_KFSJJ_JJGSDM]];
				[pjjgs.jjgsdm release];
				pjjgs.jjgsmc=[[NSString alloc]  initWithFormat:@"%@",[pParsers getFieldData:i fieldFlag:TDX_ID_KFSJJ_JJGSMC]];
				[pjjgs.jjgsmc release];
				pjjgs.jjgsdesc=[[NSString alloc] initWithFormat:@"%@ %@",pjjgs.jjgsdm,pjjgs.jjgsmc];
				[pjjgs.jjgsdesc release];
				[clientinfos.jjinfos.jjgsinfo addObject:pjjgs];
			}
		}	
		return YES;
		
	}	
	else{//基金代码查询失败
		return NO;
	}
	
}

-(BOOL) getLcdmInfo:(ParseRecv *)pParsers
{
	if(pParsers==nil)
		return NO;
	
	if(pParsers.bsucflag)
	{
		if(clientinfos.lcinfos.jjsgdminfo)
		{
			[clientinfos.lcinfos.jjsgdminfo removeAllObjects];
			clientinfos.lcinfos.jjsgdminfo=nil;
		}
		if(clientinfos.lcinfos.jjrgdminfo)
		{
			[clientinfos.lcinfos.jjrgdminfo removeAllObjects];
			clientinfos.lcinfos.jjrgdminfo=nil;
		}
		if(clientinfos.lcinfos.jjdminfo)
		{
			for(JjdmInfo *pjjdm in clientinfos.lcinfos.jjdminfo)
			{
				RELEASEOBJ(pjjdm)
			}
			[clientinfos.lcinfos.jjdminfo removeAllObjects];
			clientinfos.lcinfos.jjdminfo=nil;
			clientinfos.lcinfos.nkrgjjnum=0;
			clientinfos.lcinfos.nksgjjnum=0;
			clientinfos.lcinfos.njjnum=0;
		}
		
		//MyNsLog(@"lenx117");
		if(pParsers.nrownum > 0)
		{
			clientinfos.lcinfos.jjdminfo=[[NSMutableArray alloc] initWithCapacity:pParsers.nrownum+1];
			[clientinfos.lcinfos.jjdminfo release];
			clientinfos.lcinfos.jjsgdminfo=[[NSMutableArray alloc] initWithCapacity:pParsers.nrownum+1];
			[clientinfos.lcinfos.jjsgdminfo release];
			clientinfos.lcinfos.jjrgdminfo=[[NSMutableArray alloc] initWithCapacity:pParsers.nrownum+1];
			[clientinfos.lcinfos.jjrgdminfo release];
			clientinfos.lcinfos.jjdmdict=[[NSMutableDictionary alloc] initWithCapacity:pParsers.nrownum+1];
			[clientinfos.lcinfos.jjdmdict release];
			JjdmInfo *pjjdm=nil;
			for (int i = 0;i<pParsers.nrownum; i++)
			{
				pjjdm=[JjdmInfo new];
				
				pjjdm.jjgsdm=[[NSString alloc]  initWithFormat:@"%@",[pParsers getFieldData:i fieldFlag:TDX_ID_CPGSDM]];
				[pjjdm.jjgsdm release];
				pjjdm.jjdm=[[NSString alloc]  initWithFormat:@"%@",[pParsers getFieldData:i fieldFlag:TDX_ID_CPDM]];
				[pjjdm.jjdm release];
				pjjdm.jjmc=[[NSString alloc]  initWithFormat:@"%@",[pParsers getFieldData:i fieldFlag:TDX_ID_CPMC]];
				[pjjdm.jjmc release];
				pjjdm.jjjyzt=[[NSString alloc]  initWithFormat:@"%@",[pParsers getFieldData:i fieldFlag:TDX_ID_ZTSM]];
				[pjjdm.jjjyzt release];
				pjjdm.jjjz=[[pParsers getFieldData:i fieldFlag:TDX_ID_QRJZ]floatValue];
				pjjdm.grzdsgje=[[pParsers getFieldData:i fieldFlag:TDX_ID_KFSJJ_GRZDRGJE]floatValue];
				pjjdm.frzdsgje=[[pParsers getFieldData:i fieldFlag:TDX_ID_KFSJJ_FRZDRGJE]floatValue];
				pjjdm.njjjyzt=[[pParsers getFieldData:i fieldFlag:TDX_ID_CPZT]intValue];
				pjjdm.zdcyfe=[[pParsers getFieldData:i fieldFlag:TDX_ID_KFSJJ_ZDCYFE]floatValue];
				pjjdm.zgshfe=[[pParsers getFieldData:i fieldFlag:TDX_ID_KFSJJ_ZGSHFE]doubleValue];
				pjjdm.njjbs=[[pParsers getFieldData:i fieldFlag:TDX_ID_CPBZ]intValue];
				
				[clientinfos.lcinfos.jjdminfo addObject:pjjdm];
				[clientinfos.lcinfos.jjdmdict setObject:pjjdm forKey:pjjdm.jjdm];
				
				if(pjjdm.njjjyzt==0)
				{
					clientinfos.lcinfos.nksgjjnum++;
					[clientinfos.lcinfos.jjsgdminfo addObject:pjjdm];
				}
				else if(pjjdm.njjjyzt==1)
				{
					clientinfos.lcinfos.nkrgjjnum++;
					[clientinfos.lcinfos.jjrgdminfo addObject:pjjdm];
				}
				clientinfos.lcinfos.njjnum++;
			}
		}	
		return YES;
		
	}	
	else{//基金代码查询失败
		return NO;
	}
}

-(BOOL) getLcZhInfo:(ParseRecv *)pParsers
{
	if(pParsers==nil)
		return NO;
	if(pParsers.bsucflag)
	{
		if(clientinfos.lcinfos.jjzhinfo)
		{
			for(JjZhInfo *pjjzh in clientinfos.lcinfos.jjzhinfo)
			{
				RELEASEOBJ(pjjzh)
			}
			[clientinfos.lcinfos.jjzhinfo removeAllObjects];
			clientinfos.lcinfos.jjzhinfo=nil;
		}
		
		if(pParsers.nrownum > 0)
		{
			clientinfos.lcinfos.jjzhinfo=[[NSMutableArray alloc] initWithCapacity:pParsers.nrownum+1];
			[clientinfos.lcinfos.jjzhinfo release];
			clientinfos.lcinfos.jjzhdict=[[NSMutableDictionary alloc] initWithCapacity:pParsers.nrownum+1];
			[clientinfos.lcinfos.jjzhdict release];
			JjZhInfo *pjjzh=nil;
			for (int i = 0;i<pParsers.nrownum; i++)
			{
				pjjzh=[JjZhInfo new];
				
				pjjzh.jjgsdm=[[NSString alloc]  initWithFormat:@"%@",[pParsers getFieldData:i fieldFlag:TDX_ID_CPGSDM]];
				[pjjzh.jjgsdm release];
				pjjzh.jjgsmc=[[NSString alloc]  initWithFormat:@"%@",[pParsers getFieldData:i fieldFlag:TDX_ID_CPGSMC]];
				[pjjzh.jjgsmc release];
				pjjzh.jjzh=[[NSString alloc]  initWithFormat:@"%@",[pParsers getFieldData:i fieldFlag:TDX_ID_LCZH]];
				[pjjzh.jjzh release];
				pjjzh.khmc=[[NSString alloc]  initWithFormat:@"%@",[pParsers getFieldData:i fieldFlag:TDX_ID_KHMC]];
				[pjjzh.khmc release];
				pjjzh.zjhm=[[NSString alloc]  initWithFormat:@"%@",[pParsers getFieldData:i fieldFlag:TDX_ID_ZJHM]];
				[pjjzh.zjhm release];
				
				[clientinfos.lcinfos.jjzhinfo addObject:pjjzh];
				[clientinfos.lcinfos.jjzhdict setObject:pjjzh forKey:pjjzh.jjgsdm];
			}
		}	
		return YES;
		
	}	
	else{//基金代码查询失败
		return NO;
	}
	
}


-(BOOL) getLcgsInfo:(ParseRecv *)pParsers
{
	if(pParsers==nil)
		return NO;
	if(pParsers.bsucflag)
	{
		if(clientinfos.lcinfos.jjgsinfo)
		{
			for(JjgsInfo *pjjgs in clientinfos.lcinfos.jjgsinfo)
			{
				RELEASEOBJ(pjjgs)
			}
			[clientinfos.lcinfos.jjgsinfo removeAllObjects];
			clientinfos.lcinfos.jjgsinfo=nil;
		}
		
		if(pParsers.nrownum> 0)
		{
			clientinfos.lcinfos.jjgsinfo=[[NSMutableArray alloc] initWithCapacity:pParsers.nrownum+1];
			[clientinfos.lcinfos.jjgsinfo release];
			JjgsInfo *pjjgs=nil;
			NSString *gsdm=nil;
			for (int i = 0;i<pParsers.nrownum; i++)
			{
				gsdm=[pParsers getFieldData:i fieldFlag:TDX_ID_KFSJJ_JJGSDM];
				if([clientinfos.tradeccf Islcgsdm:gsdm]==NO)
					continue;
				pjjgs=[JjgsInfo new];
				
				pjjgs.jjgsdm=[[NSString alloc]  initWithFormat:@"%@",gsdm];
				[pjjgs.jjgsdm release];
				pjjgs.jjgsmc=[[NSString alloc]  initWithFormat:@"%@",[pParsers getFieldData:i fieldFlag:TDX_ID_KFSJJ_JJGSMC]];
				[pjjgs.jjgsmc release];
				pjjgs.jjgsdesc=[[NSString alloc] initWithFormat:@"%@ %@",pjjgs.jjgsdm,pjjgs.jjgsmc];
				[pjjgs.jjgsdesc release];
				[clientinfos.lcinfos.jjgsinfo addObject:pjjgs];
			}
		}	
		return YES;
		
	}	
	else{//基金代码查询失败
		return NO;
	}
	
}

-(void)GetGfcxInfo:(ParseRecv *)pParsers
{
	if(pParsers==nil)
		return ;
	NSString *tempString=nil;
	
	//验证合法性
	double dzxsz=0,dfdyk=0;
	int nzhlb=0,ngplx=0,nbz=0;
	if(pParsers.bsucflag)
	{
		if(pParsers.nrownum > 0)
		{
			ST_ZJGFINFO tmpzjgf=clientinfos.strawzjgf;
            tmpzjgf.zzc[0]-=tmpzjgf.lastzsz[0];
            tmpzjgf.zzc[1]-=tmpzjgf.lastzsz[1];
            tmpzjgf.zzc[2]-=tmpzjgf.lastzsz[2];
            
            double  dlastzsz[3]={0.0};
			for (int i = 0; i<pParsers.nrownum; i++) {
				
				tempString = [pParsers getFieldData:i fieldFlag:TDX_ID_ZJZH];	
				if([tempString length] && [tempString isEqualToString:@"－"]==NO)
				{
					if([tempString isEqualToString:[clientinfos GetZjzh]]==NO)
                    {
#ifndef IMAC_PAZQ
						continue;
#endif
                    }
				}
				tempString = [pParsers getFieldData:i fieldFlag:TDX_ID_ZXSZ];
				dzxsz=[tempString doubleValue];
				tempString = [pParsers getFieldData:i fieldFlag:((clientinfos.m_nQsbs==SYWG_DLL)?TDX_ID_ZYK:TDX_ID_FDYK)];
				dfdyk=[tempString doubleValue];
				tempString = [pParsers getFieldData:i fieldFlag:TDX_ID_GDDM];
				nzhlb=[clientinfos.gdinfos GetZhlbFromGddm:tempString];
				tempString = [pParsers getFieldData:i fieldFlag:TDX_ID_GPLX];
				ngplx=[tempString intValue];
				nbz=[clientinfos GetBzFromZhlb:nzhlb];
				tmpzjgf.fdyk[nbz]+=dfdyk;
				tmpzjgf.zsz[nbz]+=dzxsz;
				if(ngplx==10)
					dlastzsz[nbz]-=dzxsz;
				else  
					dlastzsz[nbz]+=dzxsz;
				if(clientinfos.m_nQsbs==SYWG_DLL)
				{
					tempString = [pParsers getFieldData:i fieldFlag:TDX_ID_JRMRJE];
					dlastzsz[nbz]-=[tempString doubleValue];
					tempString = [pParsers getFieldData:i fieldFlag:TDX_ID_JRMCJE];
					dlastzsz[nbz]+=[tempString doubleValue];
				}
			}
            for(int i=0;i<3;i++)
            {
                tmpzjgf.zzc[i]+=dlastzsz[i];
                tmpzjgf.lastzsz[i]=dlastzsz[i];
            }
			clientinfos.strawzjgf=tmpzjgf;
		}	
	}

}

-(void)GetFecxInfo2:(ParseRecv *)pParsers
{
	if(pParsers==nil)
		return ;
	NSString *tempString=nil;
	
	//验证合法性
	double dzxsz=0,dfdyk=0;
	if(pParsers.bsucflag)
	{
		if(pParsers.nrownum > 0)
		{
			ST_ZJGFINFO tmpzjgf;
			memset((char *)&tmpzjgf,0,sizeof(ST_ZJGFINFO));
			for (int i = 0; i<pParsers.nrownum; i++) {
				
				tempString = [pParsers getFieldData:i fieldFlag:TDX_ID_ZJZH];	
				if([tempString length] && [tempString isEqualToString:@"－"]==NO)
				{
					if([tempString isEqualToString:clientinfos.m_zjzh]==NO)
						continue;
				}
				tempString = [pParsers getFieldData:i fieldFlag:TDX_ID_ZXSZ];
				dzxsz=[tempString doubleValue];
				tempString = [pParsers getFieldData:i fieldFlag:TDX_ID_FDYK];
				dfdyk=[tempString doubleValue];
				tmpzjgf.jjfdyk[0]+=dfdyk;
				tmpzjgf.jjzsz[0]+=dzxsz;
				tmpzjgf.jjzzc[0]+=dzxsz;
			}
			clientinfos.strawzjgfjj=tmpzjgf;
		}	
	}
	
}

-(void)GetLcFecxInfo2:(ParseRecv *)pParsers
{
	if(pParsers==nil)
		return ;
	NSString *tempString=nil;
	
	//验证合法性
	double dzxsz=0,dfdyk=0;
	if(pParsers.bsucflag)
	{
		if(pParsers.nrownum > 0)
		{
			ST_ZJGFINFO tmpzjgf;
			memset((char *)&tmpzjgf,0,sizeof(ST_ZJGFINFO));
			for (int i = 0; i<pParsers.nrownum; i++) {
				
				tempString = [pParsers getFieldData:i fieldFlag:TDX_ID_ZJZH];	
				if([tempString length] && [tempString isEqualToString:@"－"]==NO)
				{
					if([tempString isEqualToString:clientinfos.m_zjzh]==NO)
						continue;
				}
				tempString = [pParsers getFieldData:i fieldFlag:TDX_ID_ZXSZ];
				dzxsz=[tempString doubleValue];
				tempString = [pParsers getFieldData:i fieldFlag:TDX_ID_FDYK];
				dfdyk=[tempString doubleValue];
				tmpzjgf.lcfdyk[0]+=dfdyk;
				tmpzjgf.lczsz[0]+=dzxsz;
				tmpzjgf.lczzc[0]+=dzxsz;
			}
			clientinfos.strawzjgflc=tmpzjgf;
		}	
	}
	
}

-(NSString *)GetKmsl:(ParseRecv *)pParsers zqdm:(NSString *)zqdm gddm:(NSString *)gddm xwdm:(NSString *)xwdm zjzh:(NSString *)zjzh
{
	NSString *kmsl=@"0";
	if(pParsers==nil)
		return kmsl;
	NSString *tempString=nil;
	if(pParsers.bsucflag)
	{
		if(pParsers.nrownum> 0)
		{
			for (int i = 0; i<pParsers.nrownum; i++) 
			{
				tempString = [pParsers getFieldData:i fieldFlag:TDX_ID_ZQDM];
				if([tempString isEqualToString:zqdm]==NO)
					continue;
				tempString = [pParsers getFieldData:i fieldFlag:TDX_ID_GDDM];
				if([tempString isEqualToString:gddm]==NO)
					continue;
				tempString = [pParsers getFieldData:i fieldFlag:TDX_ID_ZJZH];	
				if([tempString length] && [tempString isEqualToString:@"－"]==NO && [zjzh length])
				{
					if([tempString isEqualToString:zjzh]==NO)
                    {
						continue;
                    }
				}
				tempString = [pParsers getFieldData:i fieldFlag:TDX_ID_XWDM];
				if([tempString length] && [tempString isEqualToString:@"－"]==NO && [xwdm length])
				{
					if([tempString isEqualToString:xwdm]==NO)
						continue;
				}
				tempString = [pParsers getFieldData:i fieldFlag:TDX_ID_KMSL];
				if([tempString length] && [tempString isEqualToString:@"－"]==NO)
					kmsl=tempString;
				break;
			}
		}			
	}
	return kmsl;
}

-(NSString *)GetGfGddm:(ParseRecv *)pParsers zqdm:(NSString *)zqdm
{
  	if(pParsers==nil)
		return @"";
	NSString *tempString=nil;
	if(pParsers.bsucflag)
	{
		if(pParsers.nrownum> 0)
		{
			for (int i = 0; i<pParsers.nrownum; i++)
			{
				tempString = [pParsers getFieldData:i fieldFlag:TDX_ID_ZQDM];
				if([tempString isEqualToString:zqdm]==NO)
					continue;
                tempString = [pParsers getFieldData:i fieldFlag:TDX_ID_KMSL];
				if([tempString length]==0 || [tempString isEqualToString:@"－"])
                    continue;
                if([tempString intValue]<=0)
                    continue;
				tempString = [pParsers getFieldData:i fieldFlag:TDX_ID_GDDM];
				return tempString;			}
		}
	}
	return @"";
}

-(NSString *)GetBzStr:(int)nbz
{
	switch (nbz) {
		case 0:
			return @"人民币";
		case 1:
			return  @"美元";
		case 2:
			return @"港币";
	}
	return @"人民币";
}
#pragma mark 	委托类

-(unsigned long)makedword:(short)lowvalue high:(short)highvalue
{
	unsigned long value= ((highvalue<<16)|lowvalue);
	return value;
}

#pragma mark 加密解密压缩解压
#pragma mark 银行类



#pragma mark 咨讯类
-(void)getInformationTitleData:(NSString *)urlString theData:(NSMutableArray *) infoData{
	NSURLRequest * request = [[[NSURLRequest alloc] initWithURL:[NSURL URLWithString:urlString] cachePolicy:NSURLRequestReloadIgnoringCacheData timeoutInterval:8] autorelease];
	NSURLResponse * urlResponse = nil;
	NSError * error = [[[NSError alloc] init] autorelease];
	NSData * responseData = [NSURLConnection sendSynchronousRequest:request returningResponse:&urlResponse error:&error];
	
	if (self.netStat == ReachableViaWiFi){
		self.dataRec = self.dataRec + [responseData length];
	}
	else if(self.netStat == ReachableViaWWAN) {
		self.dataRec_3G = self.dataRec_3G + [responseData length];
	}
	
	NSString * tempString = [[NSString alloc] initWithData:responseData encoding:NSUTF8StringEncoding];
	info_data = [NSString stringWithFormat:@"%@",tempString];
	[tempString release];
	
	NSString * hrefString = @"a href=";
	NSString * endString = @">";
	NSString * startString = @"</a>";
	NSString * replaceString = @"amp;";
	NSString * theHrefString ;
	NSString * theTitleString ;
	
	NSRange range = [info_data rangeOfString:hrefString];
	
	NSRange tempRange,endRange,titleRange,replaceRange,httpRange;
	
	while (range.length > 0) {
		InfoUnit  * tempUnit = [[InfoUnit alloc] init];
		
		tempRange = NSMakeRange(range.location+range.length, [info_data length] - range.location-range.length);
		endRange = [info_data rangeOfString:endString options:NSCaseInsensitiveSearch range:tempRange];
		
		theHrefString = [info_data substringWithRange:NSMakeRange(range.location+range.length+1, endRange.location-range.location-range.length -1-1)];
		replaceRange = [theHrefString rangeOfString:replaceString];
		if (replaceRange.length > 0) {
			NSString * tempString = [NSString stringWithFormat:@"http://%@/%@%@",infoHost,[theHrefString substringToIndex:replaceRange.location],[theHrefString substringFromIndex:replaceRange.location+replaceRange.length]];
			theHrefString = tempString;
		}
		else {
			
		}
		
		httpRange = [theHrefString rangeOfString:@"http://"];
		if (httpRange.length > 0) {
			;
		}else {
			NSString * tempString = [NSString stringWithFormat:@"http://%@/%@",infoHost,theHrefString];
			theHrefString = tempString;
		}

		
		
		tempRange = NSMakeRange(endRange.location+endRange.length, [info_data length] - endRange.location-endRange.length);
		titleRange = [info_data rangeOfString:startString options:NSCaseInsensitiveSearch range:tempRange];
		
		theTitleString = [info_data substringWithRange:NSMakeRange(endRange.location+endRange.length, titleRange.location-endRange.location-endRange.length)];
		
		tempUnit.href = theHrefString;
		tempUnit.title = theTitleString;
		
		[infoData addObject:tempUnit];
		[tempUnit release];
		
		info_data = [info_data substringFromIndex:titleRange.location+titleRange.length];
		range = [info_data rangeOfString:hrefString];
	}

}

-(NSString *)getInformationTextData:(NSString *)urlString{
	NSURLRequest * request = [[[NSURLRequest alloc] initWithURL:[NSURL URLWithString:urlString] cachePolicy:NSURLRequestReloadIgnoringCacheData timeoutInterval:8] autorelease];
	NSURLResponse * urlResponse = nil;
	NSError * error = [[[NSError alloc] init] autorelease];
	NSData * responseData = [NSURLConnection sendSynchronousRequest:request returningResponse:&urlResponse error:&error];
	NSString * result = [[[NSString alloc] initWithData:responseData encoding:NSUTF8StringEncoding] autorelease];
	if (self.netStat == ReachableViaWiFi){
		self.dataRec = self.dataRec + [responseData length];
	}
	else if(self.netStat == ReachableViaWWAN) {
		self.dataRec_3G = self.dataRec_3G + [responseData length];
	}
	
	
	NSString * endString = @"</p";
	NSString * startString = @"<p>";
	NSString * replaceString = @"<br/>";
	if(currentString)
	{
		[currentString release];
		currentString = nil;
	}
	if(currTitleString)
	{
		[currTitleString release];
		currTitleString = nil;
	}
	if(currTimeString)
	{
		[currTimeString release];
		currTimeString = nil;
	}
	
	
	NSRange range = [result rangeOfString:startString];
	NSString * tempString;
	if (range.length > 0) {
		NSRange tempRange = [result rangeOfString:replaceString];
		
		
		tempString = [result substringWithRange:NSMakeRange(range.location+range.length, tempRange.location-range.location-range.length)];
		currTitleString = [[NSString alloc] initWithString:tempString];
		
		
		result = [result substringFromIndex:tempRange.location+tempRange.length];
		
		range = [result rangeOfString:replaceString];
		
		tempString = [result substringWithRange:NSMakeRange(0, range.location)];
		currTimeString = [[NSString alloc] initWithString:tempString];
		
		result = [result substringFromIndex:range.location+range.length];
		
		range = [result rangeOfString:endString];
		
		
		
		tempString = [[result substringWithRange:NSMakeRange(0, range.location)] stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceCharacterSet]];
		currentString = [[NSString alloc] initWithString:tempString];
	}
	
	return currentString;

}

#pragma mark 	委托类

- (void)parser:(NSXMLParser *)parser didEndElement:(NSString *)elementName
  namespaceURI:(NSString *)namespaceURI qualifiedName:(NSString *)qName
{
}

-(void)logoutTrade
{
	tradeLoginFlag=NO;
	[wtCHBTimer invalidate];
	[g_TradeComm logout];
	[clientinfos release];
	clientinfos=nil;
    if(bexitsysflag==NO)
    {
        [self InitHqInfo];
        [self InitClientInfo];
    }
	[jjcodeArray removeAllObjects];
	[fecxArray removeAllObjects];
	[lxfsArray removeAllObjects];
	inputSave.gddm = @"";
	inputSave.branchId = @"";
	inputSave.accout = @"";
	[inputSave releasePassword];
	[inputSave releaseauthPassword];
	[inputSave releasereloginsession];
	inputSave.sessionID=0;
}

-(void)InitClientInfo
{
	if(clientinfos==nil)
	{
		clientinfos=[ClientInfo new];
		clientinfos.qsconfigs=[QsConfig new];
		[clientinfos.qsconfigs release];
		JyConfig *pconfig=[clientinfos.qsconfigs.jyconfigs objectAtIndex:0];
		if(pconfig)
		{
			g_TradeComm.njobtimeout=pconfig.network.njobtimeout;
			clientinfos.caches=[[localCache alloc]initloginInfo:pconfig.qsjc];
			clientinfos.m_nQsbs = pconfig.qsid;
		}
		else 
			clientinfos.caches=[[localCache alloc]initloginInfo:@"TDX"];
		

		
		clientinfos.logininfos=[clientinfos.caches loadLoginInfo];
		[clientinfos.logininfos release];
		[clientinfos.caches loadMultiloginInfo:clientinfos.multilogininfos];
		if(clientinfos.multilogininfos.zhinfos==nil && clientinfos.logininfos && [clientinfos.logininfos.m_rawzjzh length])
		{
			clientinfos.multilogininfos.zhinfos=[[NSMutableArray alloc] initWithCapacity:1];
			[clientinfos.multilogininfos.zhinfos release];
			[clientinfos.multilogininfos.zhinfos addObject:[clientinfos.logininfos deepcopy]];
			[clientinfos.caches SaveMultiloginInfo:clientinfos.multilogininfos];
		}
		if(clientinfos.logininfos==nil)
		{
			clientinfos.logininfos=[LoginInfo new];
			[clientinfos.logininfos release];
		}
        int nlastjysiteindex=-1;
		if([clientinfos.caches loadLocalJySite:clientinfos.localjysites])
            nlastjysiteindex=clientinfos.localjysites.nlastindex;
        
		if(pconfig.tradesite)
		{
			if(clientinfos.localjysites.tradesites)
				[clientinfos.localjysites releaseSiteinfos];
			int sitecount=[pconfig.tradesite count];
			if(sitecount)
			{
                if(nlastjysiteindex==-1 || nlastjysiteindex>sitecount)
                {
                    clientinfos.localjysites.nlastindex=rand()%sitecount;
                    LogIt2(4)
                }
                else
                {
                    clientinfos.localjysites.nlastindex=nlastjysiteindex;
                    LogIt2(5)
                }
				clientinfos.localjysites.bfindbest=pconfig.bfindbestSite;
				clientinfos.localjysites.tradesites=[[NSMutableArray alloc] initWithCapacity:sitecount+1];
				[clientinfos.localjysites.tradesites release];
				for(TradeSite *psite in pconfig.tradesite)
				{
					[clientinfos.localjysites.tradesites addObject:[psite deepcopy]];
				}
				[clientinfos.caches SaveLocalJySite:clientinfos.localjysites];
			}
		}
        int nlasthqsiteindex=-1;
        if([clientinfos.caches loadLocalHqSite:clientinfos.localhqsites])
            nlasthqsiteindex=clientinfos.localhqsites.nlastindex;
		if(pconfig.hqsite)
		{
			if(clientinfos.localhqsites.tradesites)
				[clientinfos.localhqsites releaseSiteinfos];
			int sitecount=[pconfig.hqsite count];
			if(sitecount)
			{
                if(nlasthqsiteindex==-1 || nlasthqsiteindex>sitecount)
                    clientinfos.localhqsites.nlastindex=rand()%sitecount;
                else
                    clientinfos.localhqsites.nlastindex=nlasthqsiteindex;
				clientinfos.localhqsites.bfindbest=pconfig.bfindbesthqSite;
				clientinfos.localhqsites.tradesites=[[NSMutableArray alloc] initWithCapacity:sitecount+1];
				[clientinfos.localhqsites.tradesites release];
				for(TradeSite *psite in pconfig.hqsite)
				{
					[clientinfos.localhqsites.tradesites addObject:[psite deepcopy]];
				}
				[clientinfos.caches SaveLocalHqSite:clientinfos.localhqsites];
			}
		}
	}
	else if(clientinfos.m_bonlyinithqinfo)
	{
		clientinfos.m_bonlyinithqinfo=NO;
		clientinfos.logininfos=[clientinfos.caches loadLoginInfo];
		[clientinfos.logininfos release];
		[clientinfos.caches loadMultiloginInfo:clientinfos.multilogininfos];
		if(clientinfos.multilogininfos.zhinfos==nil && clientinfos.logininfos && [clientinfos.logininfos.m_rawzjzh length])
		{
			clientinfos.multilogininfos.zhinfos=[[NSMutableArray alloc] initWithCapacity:1];
			[clientinfos.multilogininfos.zhinfos release];
			[clientinfos.multilogininfos.zhinfos addObject:[clientinfos.logininfos deepcopy]];
			[clientinfos.caches SaveMultiloginInfo:clientinfos.multilogininfos];
		}
		if(clientinfos.logininfos==nil)
		{
			clientinfos.logininfos=[LoginInfo new];
			[clientinfos.logininfos release];
		}
		JyConfig *pconfig=[clientinfos.qsconfigs.jyconfigs objectAtIndex:0];
		if(pconfig)
			g_TradeComm.njobtimeout=pconfig.network.njobtimeout;
		int nlastjysiteindex=-1;
		if([clientinfos.caches loadLocalJySite:clientinfos.localjysites])
            nlastjysiteindex=clientinfos.localjysites.nlastindex;
        
		if(pconfig.tradesite)
		{
            NSString *strlog;
			if(clientinfos.localjysites.tradesites)
            {
 //               for(TradeSite *psite1 in clientinfos.localjysites.tradesites)
                {
//                    strlog=[NSString stringWithFormat:@"old_site %@ %@ %i\r",psite1.sname,psite1.ip,psite1.nport];
//                    LogIt3(strlog)
                }
				[clientinfos.localjysites releaseSiteinfos];
            }
			int sitecount=[pconfig.tradesite count];
			if(sitecount)
			{
                if(nlastjysiteindex==-1 || nlastjysiteindex>sitecount)
                {
                    clientinfos.localjysites.nlastindex=rand()%sitecount;
                    LogIt2(6)
                }
                else
                {
                    clientinfos.localjysites.nlastindex=nlastjysiteindex;
                    LogIt2(7)
                }
                
				clientinfos.localjysites.bfindbest=pconfig.bfindbestSite;
				clientinfos.localjysites.tradesites=[[NSMutableArray alloc] initWithCapacity:sitecount+1];
				[clientinfos.localjysites.tradesites release];
				for(TradeSite *psite in pconfig.tradesite)
				{
//                    strlog=[NSString stringWithFormat:@"new_site %@ %@ %i\r",psite.sname,psite.ip,psite.nport];
//                    LogIt3(strlog)
                    
                    [clientinfos.localjysites.tradesites addObject:[psite deepcopy]];
				}
				[clientinfos.caches SaveLocalJySite:clientinfos.localjysites];
			}
		}
	}
}

-(void)InitHqInfo
{
	if(clientinfos==nil)
	{
		clientinfos=[ClientInfo new];
		clientinfos.m_bonlyinithqinfo=YES;
		clientinfos.qsconfigs=[QsConfig new];
		[clientinfos.qsconfigs release];
		
		JyConfig *pconfig=[clientinfos.qsconfigs.jyconfigs objectAtIndex:0];
		if(pconfig){
			clientinfos.caches=[[localCache alloc]initloginInfo:pconfig.qsjc];
			clientinfos.m_nQsbs = pconfig.qsid;
		}
		else 
			clientinfos.caches=[[localCache alloc]initloginInfo:@"TDX"];
		
//		NSFileManager *fm;
//		fm=[NSFileManager defaultManager];
		NSArray* pathArray = NSSearchPathForDirectoriesInDomains(NSApplicationSupportDirectory, NSUserDomainMask, YES);
		
		int pathLen = [pathArray count];
		NSString* curuserpath = nil;
		for(int i=0;i<pathLen;i++)
		{
			curuserpath = [pathArray objectAtIndex:i];
			
		}
		curuserpath = [curuserpath stringByAppendingString:MAC_PATHSTRING];
		logcachefile = [[NSString alloc] initWithFormat:@"%@%@/%@%@/log.txt",curuserpath,@"/Library/Caches/tdximac",@"ZSZQ",@"/T0002/wtdata"];
		
		
		int nlasthqsiteindex=-1;
        if([clientinfos.caches loadLocalHqSite:clientinfos.localhqsites])
            nlasthqsiteindex=clientinfos.localhqsites.nlastindex;
		if(pconfig.hqsite)
		{
			if(clientinfos.localhqsites.tradesites)
				[clientinfos.localhqsites releaseSiteinfos];
			int sitecount=[pconfig.hqsite count];
			if(sitecount)
			{
                if(nlasthqsiteindex==-1)
                    clientinfos.localhqsites.nlastindex=rand()%sitecount;
                else
                    clientinfos.localhqsites.nlastindex=nlasthqsiteindex;
				clientinfos.localhqsites.bfindbest=pconfig.bfindbesthqSite;
				clientinfos.localhqsites.tradesites=[[NSMutableArray alloc] initWithCapacity:sitecount+1];
				[clientinfos.localhqsites.tradesites release];
				for(TradeSite *psite in pconfig.hqsite)
				{
					[clientinfos.localhqsites.tradesites addObject:[psite deepcopy]];
				}
				[clientinfos.caches SaveLocalHqSite:clientinfos.localhqsites];
			}
		}
		
		int nlastjysiteindex=-1;
		if([clientinfos.caches loadLocalJySite:clientinfos.localjysites])
            nlastjysiteindex=clientinfos.localjysites.nlastindex;
        
		if(pconfig.tradesite)
		{
			if(clientinfos.localjysites.tradesites)
				[clientinfos.localjysites releaseSiteinfos];
			int sitecount=[pconfig.tradesite count];
			if(sitecount)
			{
                if(nlastjysiteindex==-1 || nlastjysiteindex>sitecount)
                {
                    clientinfos.localjysites.nlastindex=rand()%sitecount;
                    LogIt2(8)
                }
                else
                {
                    clientinfos.localjysites.nlastindex=nlastjysiteindex;
                    LogIt2(9)
                }
                
				clientinfos.localjysites.bfindbest=pconfig.bfindbestSite;
				clientinfos.localjysites.tradesites=[[NSMutableArray alloc] initWithCapacity:sitecount+1];
				[clientinfos.localjysites.tradesites release];
				for(TradeSite *psite in pconfig.tradesite)
				{
					[clientinfos.localjysites.tradesites addObject:[psite deepcopy]];
				}
				[clientinfos.caches SaveLocalJySite:clientinfos.localjysites];
			}
		}
		clientinfos.hqParams=[clientinfos.caches loadHqParamInfo];
		[clientinfos.hqParams release];
		if(clientinfos.hqParams==nil && pconfig.hqParams)
		{
			clientinfos.hqParams=[pconfig.hqParams deepcopy];
			[clientinfos.caches SaveHqParamInfo:clientinfos.hqParams];
		}
		clientinfos.dataLltjs=[clientinfos.caches loadDataLltjInfo];
		[clientinfos.dataLltjs release];
		if(clientinfos.dataLltjs==nil)
		{
			clientinfos.dataLltjs=[DataLitj new];
			[clientinfos.dataLltjs release];
		}
		
		if([clientinfos.caches loadZxLinkInfo:clientinfos.zxLinks]==NO && pconfig.zxLinks)
		{
			clientinfos.zxLinks.mainlink=[pconfig.zxLinks.mainlink deepcopy];
			int itemcount=[pconfig.zxLinks.linkItems count];
			if(itemcount)
			{
				clientinfos.zxLinks.linkItems=[[NSMutableArray alloc] initWithCapacity:itemcount+1];
				[clientinfos.zxLinks.linkItems release];
				for(ZxLinks *plink in pconfig.zxLinks.linkItems)
				{
					if(plink)
						[clientinfos.zxLinks.linkItems addObject:[plink deepcopy]];
				}
			}
			[clientinfos.caches SaveZxLinkInfo:clientinfos.zxLinks];
		}
		
		clientinfos.styleParams=[clientinfos.caches loadStyleParam];
		[clientinfos.styleParams release];
		if (clientinfos.styleParams == nil && pconfig.styleParams) {
			clientinfos.styleParams = [pconfig.styleParams deepcopy];
			[clientinfos.caches SaveStyleParam:clientinfos.styleParams];
		}
		
		
		clientinfos.httpProxyInfo=[clientinfos.caches loadHttpProxyInfo];
		[clientinfos.httpProxyInfo release];
		if (clientinfos.httpProxyInfo == nil ) {
			clientinfos.httpProxyInfo = [[HttpProxyInfo alloc]  init];
			[clientinfos.caches SaveHttpProxyInfo:clientinfos.httpProxyInfo];
		}
		
		
		if ([clientinfos.caches loadGridcCellInfo:clientinfos.gridCellCache] == NO && pconfig.gridCellInfoArray) {
			if(clientinfos.gridCellCache.gridCellInfoArray)
				[clientinfos.gridCellCache releaseSiteinfos];
			int sitecount=[pconfig.gridCellInfoArray count];
			if(sitecount)
			{
				clientinfos.gridCellCache.gridCellInfoArray=[[NSMutableArray alloc] initWithCapacity:sitecount+1];
				[clientinfos.gridCellCache.gridCellInfoArray release];
				for(GridCellInfo *psite in pconfig.gridCellInfoArray)
				{
					[clientinfos.gridCellCache.gridCellInfoArray addObject:[psite deepcopy]];
				}
				[clientinfos.caches SaveGridCellInfo:clientinfos.gridCellCache];
			}
			
		}
	}
}

//查找行情最快
-(BOOL)FindFastedHqSite
{
	if(bfindbesthq)
		return YES;
	bfindbesthq=YES;
	for(TradeSite *psite in clientinfos.localhqsites.tradesites)
	{
		psite.bfindbest=NO;
		psite.ntime=-1;
	}
	int count=[clientinfos.localhqsites.tradesites count];
	[_myHqCondition lock];
	_threadCount = (-1)*count;
	//如果有n个要等待的thread，这里置成 -n
	[_myHqCondition unlock];
	[NSThread detachNewThreadSelector:@selector(GetFastedHqResult) toTarget:self withObject:nil];
	for(int i=0;i<count;i++)
		[NSThread detachNewThreadSelector:@selector(GetHqSiteConnTime:) toTarget:self withObject:[NSString stringWithFormat:@"%i",i]];
	[NSTimer scheduledTimerWithTimeInterval: 6.0f target:self selector: @selector(signalHqlock) userInfo: nil repeats: NO];
	return YES;
}

-(void)GetFastedHqResult
{
	NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
	time_t tstart=time(NULL);
	[_myHqCondition lock];
	while (_threadCount < -1) 
	{
		if((time(NULL)-tstart)<5)
			[_myHqCondition wait];
		else 
			break;
	};
	[_myHqCondition unlock];
	
	int nindex=0,nbestindex=clientinfos.localhqsites.nlastindex;
	double nmintime=10000;
	for(TradeSite *psite in clientinfos.localhqsites.tradesites)
	{
		if(psite.bfindbest && psite.ntime>=0&& psite.stime >= 0)
		{
			if(psite.stime<nmintime)
			{
				nmintime=psite.stime;
				nbestindex=nindex;
			}
		}
		nindex++;
	}
	clientinfos.localhqsites.nlastindex=nbestindex;
	[clientinfos.caches SaveLocalHqSite:clientinfos.localhqsites];
	bfindbesthq=NO;
	
	[self performSelectorOnMainThread:@selector(DoAfterFindHqBest) withObject:nil waitUntilDone:NO];
	[pool release];
	[NSThread exit];
	return;
}
-(void)signalHqlock
{
	if(bfindbesthq)
		[_myHqCondition signal];
}
-(void)DoAfterFindHqBest
{
	[myjyasyncdelegate DoAfterFindHqBest];
}

-(void)GetHqSiteConnTime:(NSString *)indexstr
{
	NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
	if(indexstr==nil)
	{
		[_myHqCondition lock];
		_threadCount ++ ;
		[_myHqCondition signal];
		[_myHqCondition unlock];
		[pool release];
		[NSThread exit];
		return;
	}
	int index=[indexstr intValue];
	if(index<0 || index>=[clientinfos.localhqsites.tradesites count])
	{
		[_myHqCondition lock];
		_threadCount ++ ;
		[_myHqCondition signal];
		[_myHqCondition unlock];
		[pool release];
		[NSThread exit];
		return;
	}
	
    TradeSite *psite=[clientinfos.localhqsites.tradesites objectAtIndex:index];
    psite.bfindbest=YES;
    int sockfd=0;
    NSString *strip4=psite.ip;
    AsyncSocket *asyncSocket=[[AsyncSocket alloc] init];
    NSString *strip=[asyncSocket getProperIPWithAddress:strip4 port:psite.nport];
    [asyncSocket release];
    int conn=-1;
    if([strip length]<=0)
    {
        NSArray *piparr=[strip4 componentsSeparatedByString:@"."];
        strip=[NSString stringWithFormat:@"64:ff9b::%02x%02x:%02x%02x",[piparr[0] intValue],[piparr[1]  intValue],[piparr[2]  intValue],[piparr[3] intValue]];
        
        sockfd=socket(AF_INET6, SOCK_STREAM, 0);
        if(sockfd==-1)
        {
            [_myHqCondition lock];
            _threadCount ++ ;
            [_myHqCondition signal];
            [_myHqCondition unlock];
            [pool release];
            [NSThread exit];
            return;
        }
        
        struct sockaddr_in6 their_addr6;
        
        memset(&their_addr6, 0, sizeof(their_addr6));
        their_addr6.sin6_len = sizeof(their_addr6);
        their_addr6.sin6_family = AF_INET6;
        their_addr6.sin6_port = htons(psite.nport);
        inet_pton(AF_INET6, strip.UTF8String, &their_addr6.sin6_addr);
        
        
        NSTimeInterval tstart=[[NSDate date] timeIntervalSince1970];
        conn = connect(sockfd, (struct sockaddr*)&their_addr6, sizeof(struct sockaddr_in6));
        if(conn>=0)
        {
            psite.ntime=([[NSDate date] timeIntervalSince1970]-tstart);
            
        }
        else
        {
            sockfd=socket(AF_INET, SOCK_STREAM, 0);
            if(sockfd==-1)
            {
                [_myHqCondition lock];
                _threadCount ++ ;
                [_myHqCondition signal];
                [_myHqCondition unlock];
                [pool release];
                [NSThread exit];
                return;
            }
            
            
            
            struct sockaddr_in their_addr;
            
            memset(&their_addr, 0, sizeof(their_addr));
            their_addr.sin_len = sizeof(their_addr);
            their_addr.sin_family = AF_INET;
            
            their_addr.sin_port = htons(psite.nport);
            inet_pton(AF_INET, strip4.UTF8String, &their_addr.sin_addr.s_addr);
            
            NSTimeInterval tstart=[[NSDate date] timeIntervalSince1970];
            conn = connect(sockfd, (struct sockaddr*)&their_addr, sizeof(struct sockaddr));
            if(conn>=0)
            {
                psite.ntime=([[NSDate date] timeIntervalSince1970]-tstart);
            }

        }
        
    }
    else
    {
        BOOL isipv6flag=([strip isEqualToString:strip4]==NO);
        
        if(isipv6flag)
        {
            sockfd=socket(AF_INET6, SOCK_STREAM, 0);
            if(sockfd==-1)
            {
                [_myHqCondition lock];
                _threadCount ++ ;
                [_myHqCondition signal];
                [_myHqCondition unlock];
                [pool release];
                [NSThread exit];
                return;
            }
            
            struct sockaddr_in6 their_addr6;
            
            memset(&their_addr6, 0, sizeof(their_addr6));
            their_addr6.sin6_len = sizeof(their_addr6);
            their_addr6.sin6_family = AF_INET6;
            their_addr6.sin6_port = htons(psite.nport);
            inet_pton(AF_INET6, strip.UTF8String, &their_addr6.sin6_addr);
            
            
            NSTimeInterval tstart=[[NSDate date] timeIntervalSince1970];
            conn = connect(sockfd, (struct sockaddr*)&their_addr6, sizeof(struct sockaddr_in6));
            if(conn>=0)
            {
                psite.ntime=([[NSDate date] timeIntervalSince1970]-tstart);
                
            }
        }
        else
        {
            sockfd=socket(AF_INET, SOCK_STREAM, 0);
            if(sockfd==-1)
            {
                [_myHqCondition lock];
                _threadCount ++ ;
                [_myHqCondition signal];
                [_myHqCondition unlock];
                [pool release];
                [NSThread exit];
                return;
            }
            
            
            
            struct sockaddr_in their_addr;
            
            memset(&their_addr, 0, sizeof(their_addr));
            their_addr.sin_len = sizeof(their_addr);
            their_addr.sin_family = AF_INET;
            
            their_addr.sin_port = htons(psite.nport);
            inet_pton(AF_INET, strip4.UTF8String, &their_addr.sin_addr.s_addr);
            
            NSTimeInterval tstart=[[NSDate date] timeIntervalSince1970];
            conn = connect(sockfd, (struct sockaddr*)&their_addr, sizeof(struct sockaddr));
            if(conn>=0)
            {
                psite.ntime=([[NSDate date] timeIntervalSince1970]-tstart);
            }
        }
    }
    
	if(conn>=0)
	{
		NSMutableData * theData = [self getHostBaseDataReq];
		short tempLength = [theData length];
		NSTimeInterval sstart=[[NSDate date] timeIntervalSince1970];

		NSMutableData *newdata = [[NSMutableData alloc] init];
		ReqInfo reqInfo;
		reqInfo.theVersion = 0;
		reqInfo.theCompressed = 0;
		reqInfo.theEncrypted = 0;
		reqInfo.isMobile = 0;
		reqInfo.theReserved = 0;
		[newdata appendBytes:(void *)&reqInfo length:sizeof(reqInfo)];
		short main = 1;
		[newdata appendBytes:(void *)&main length:sizeof(main)];
		short assis = 1;
		[newdata appendBytes:(void *)&assis length:sizeof(assis)];
		char priority = 1;
		[newdata appendBytes:(void *)&priority length:sizeof(priority)];
		[newdata appendBytes:(void *)&tempLength length:sizeof(tempLength)];
		[newdata appendBytes:(void *)&tempLength length:sizeof(tempLength)];
		[newdata appendData:theData];
		
		fd_set fdW;
		struct timeval timeout;
		timeout.tv_sec = 10;
		timeout.tv_usec = 0;
		BOOL netError = NO;
		int nSelRet;
		
		for (; ; ) {
			FD_ZERO(&fdW);
			FD_SET(sockfd,&fdW);
			nSelRet = select(sockfd+1, NULL, &fdW, NULL, &timeout);
			
			if(nSelRet != 1 || !FD_ISSET(sockfd,&fdW)){
				netError = YES;
				break;
			}
			else{
				
				
				int nSent = 0;
				while((!netError)&&(nSent < [newdata length]))
				{
					ssize_t dataSended = send(sockfd, [newdata bytes], [newdata length], 0);
					
					
					if(dataSended <0)
					{
						netError = YES;
					}
					else{
						nSent += dataSended;
						if(nSent == [newdata length])
						{
							break;
						}
						
					}
				}
				break;
			}
		}
		[newdata release];
		
		timeout.tv_sec = 10;
		timeout.tv_usec = 0;
		
		
		for (; ; ) {
			FD_ZERO(&fdW);
			FD_SET(sockfd,&fdW);
			int nSelRet = select(sockfd+1, &fdW, NULL, NULL, &timeout);
			
			if(nSelRet != 1 || !FD_ISSET(sockfd,&fdW)){
				break;
			}
			else{
				char readBuffer[10*1024];
				
				int br = 0;
				short getLen=0;
				short recLen = 0;
				short req = 0;
				NSMutableData * recData;
				BOOL netError = NO;
				
				recData = [[NSMutableData alloc] init];
				while((br = recv(sockfd, readBuffer, sizeof(readBuffer), 0)) < sizeof(readBuffer))
				{
					
					if(recLen == 0)
					{	
						if ([recData length] < 1) {
							netError=YES;
							break;
						}
						
						
						[recData appendBytes:readBuffer length:br];
						//NSLog(@"have received data length is :%i",[recData length]);
						
						
						
						int buf = 10;
						if([recData length]<14)
                            continue;
						[recData getTdxBytes:&req range:NSMakeRange(buf, sizeof(req))];
						buf +=sizeof(req);
						[recData getTdxBytes:&getLen range:NSMakeRange(buf, sizeof(getLen))];
						buf +=sizeof(getLen);
						
						if([recData length] == (getLen + 16))
						{
							break;
						}	
					}else {
						[recData appendBytes:readBuffer length:br];
						
						if([recData length] == (getLen+16))
						{
							
							break;
						}	
						
					}
					
				}
				[recData release];
				break;
			}
		}
		if (netError) {
			psite.stime=9999999999;
			
		}
		else {
			psite.stime=([[NSDate date] timeIntervalSince1970]-sstart);
		}
        close(sockfd);
	}
        
	[_myHqCondition lock];
	_threadCount ++ ;
	[_myHqCondition signal];
	[_myHqCondition unlock];
	[pool release];
	[NSThread exit];
	
	return;
}


//查找交易最快
-(BOOL)FindFastedJySite
{
	if(bfindbestjy)
		return YES;
	bfindbestjy=YES;
	for(TradeSite *psite in clientinfos.localjysites.tradesites)
	{
		psite.bfindbest=NO;
		psite.ntime=-1;
	}
	int count=[clientinfos.localjysites.tradesites count];
	[_myCondition lock];
	_threadCount = (-1)*count;
	//如果有n个要等待的thread，这里置成 -n
	[_myCondition unlock];
	[NSThread detachNewThreadSelector:@selector(GetFastedResult) toTarget:self withObject:nil];
	for(int i=0;i<count;i++)
		[NSThread detachNewThreadSelector:@selector(GetJySiteConnTime:) toTarget:self withObject:[NSString stringWithFormat:@"%i",i]];
	[NSTimer scheduledTimerWithTimeInterval: 6.0f target:self selector: @selector(signallock) userInfo: nil repeats: NO];
	return YES;
}

-(void)signallock
{
	if(bfindbestjy)
		[_myCondition signal];
}

-(void)GetFastedResult
{
	NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
	time_t tstart=time(NULL);
	[_myCondition lock];
	while (_threadCount < -1) 
	{
		if((time(NULL)-tstart)<5)
			[_myCondition wait];
		else 
			break;
	};
	[_myCondition unlock];
	
	int nindex=0,nbestindex=clientinfos.localjysites.nlastindex;
	double nmintime=10000;
	for(TradeSite *psite in clientinfos.localjysites.tradesites)
	{
		if(psite.bfindbest && psite.ntime>=0)
		{
			if(psite.ntime<nmintime)
			{
				nmintime=psite.ntime;
				nbestindex=nindex;
			}
		}
		nindex++;
	}
	clientinfos.localjysites.nlastindex=nbestindex;
    LogIt2(10)
  	[clientinfos.caches SaveLocalJySite:clientinfos.localjysites];
	bfindbestjy=NO;
	
	[self performSelectorOnMainThread:@selector(doAfterFindBest) withObject:nil waitUntilDone:NO];
	[pool release];
	[NSThread exit];
	return;
}

-(void)doAfterFindBest
{
	[myjyasyncdelegate DoAfterFindBest];
}

-(void)GetJySiteConnTime:(NSString *)indexstr
{
	NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
	if(indexstr==nil)
	{
		[_myCondition lock];
		_threadCount ++ ;
		[_myCondition signal];
		[_myCondition unlock];
		[pool release];
		[NSThread exit];
		return;
	}
	int index=[indexstr intValue];
	if(index<0 || index>=[clientinfos.localjysites.tradesites count])
	{
		[_myCondition lock];
		_threadCount ++ ;
		[_myCondition signal];
		[_myCondition unlock];
		[pool release];
		[NSThread exit];
		return;
	}
    TradeSite *psite=[clientinfos.localjysites.tradesites objectAtIndex:index];
    psite.bfindbest=YES;
    
    NSString *strip4=psite.ip;
    AsyncSocket *asyncSocket=[[AsyncSocket alloc] init];
    NSString *strip=[asyncSocket getProperIPWithAddress:strip4 port:psite.nport];
    [asyncSocket release];
    int sockfd=0;
    int conn=-1;
    if([strip length]<=0)
    {
        NSArray *piparr=[strip4 componentsSeparatedByString:@"."];
        strip=[NSString stringWithFormat:@"64:ff9b::%02x%02x:%02x%02x",[piparr[0] intValue],[piparr[1]  intValue],[piparr[2]  intValue],[piparr[3] intValue]];
        
        sockfd=socket(AF_INET6, SOCK_STREAM, 0);
        if(sockfd==-1)
        {
            [_myCondition lock];
            _threadCount ++ ;
            [_myCondition signal];
            [_myCondition unlock];
            [pool release];
            [NSThread exit];
            return;
        }
        
        struct sockaddr_in6 their_addr6;
        
        memset(&their_addr6, 0, sizeof(their_addr6));
        their_addr6.sin6_len = sizeof(their_addr6);
        their_addr6.sin6_family = AF_INET6;
        their_addr6.sin6_port = htons(psite.nport);
        inet_pton(AF_INET6, strip.UTF8String, &their_addr6.sin6_addr);
        
        
        NSTimeInterval tstart=[[NSDate date] timeIntervalSince1970];
        conn = connect(sockfd, (struct sockaddr*)&their_addr6, sizeof(struct sockaddr_in6));
        if(conn>=0)
        {
            psite.ntime=([[NSDate date] timeIntervalSince1970]-tstart);
            close(sockfd);
            
        }
        else
        {
            sockfd=socket(AF_INET, SOCK_STREAM, 0);
            if(sockfd==-1)
            {
                [_myCondition lock];
                _threadCount ++ ;
                [_myCondition signal];
                [_myCondition unlock];
                [pool release];
                [NSThread exit];
                return;
            }
            
            
            
            struct sockaddr_in their_addr;
            
            memset(&their_addr, 0, sizeof(their_addr));
            their_addr.sin_len = sizeof(their_addr);
            their_addr.sin_family = AF_INET;
            
            their_addr.sin_port = htons(psite.nport);
            inet_pton(AF_INET, strip4.UTF8String, &their_addr.sin_addr.s_addr);
            
            NSTimeInterval tstart=[[NSDate date] timeIntervalSince1970];
            conn = connect(sockfd, (struct sockaddr*)&their_addr, sizeof(struct sockaddr));
            if(conn>=0)
            {
                psite.ntime=([[NSDate date] timeIntervalSince1970]-tstart);
                close(sockfd);
            }
            
        }
        
    }
    else
    {
        BOOL isipv6flag=([strip isEqualToString:strip4]==NO);
        
        if(isipv6flag)
        {
            int sockfd=socket(AF_INET6, SOCK_STREAM, 0);
            if(sockfd==-1)
            {
                [_myCondition lock];
                _threadCount ++ ;
                [_myCondition signal];
                [_myCondition unlock];
                [pool release];
                [NSThread exit];
                return;
            }
            
            struct sockaddr_in6 their_addr6;
            
            memset(&their_addr6, 0, sizeof(their_addr6));
            their_addr6.sin6_len = sizeof(their_addr6);
            their_addr6.sin6_family = AF_INET6;
            their_addr6.sin6_port = htons(psite.nport);
            inet_pton(AF_INET6, strip.UTF8String, &their_addr6.sin6_addr);
            
            
            NSTimeInterval tstart=[[NSDate date] timeIntervalSince1970];
            int conn = connect(sockfd, (struct sockaddr*)&their_addr6, sizeof(struct sockaddr_in6));
            if(conn>=0)
            {
                psite.ntime=([[NSDate date] timeIntervalSince1970]-tstart);
                close(sockfd);
            }
        }
        else
        {
            int sockfd=socket(AF_INET, SOCK_STREAM, 0);
            if(sockfd==-1)
            {
                [_myCondition lock];
                _threadCount ++ ;
                [_myCondition signal];
                [_myCondition unlock];
                [pool release];
                [NSThread exit];
                return;
            }
            
            
            
            struct sockaddr_in their_addr;
            
            memset(&their_addr, 0, sizeof(their_addr));
            their_addr.sin_len = sizeof(their_addr);
            their_addr.sin_family = AF_INET;
            
            their_addr.sin_port = htons(psite.nport);
            inet_pton(AF_INET, strip4.UTF8String, &their_addr.sin_addr.s_addr);
            
            NSTimeInterval tstart=[[NSDate date] timeIntervalSince1970];
            int conn = connect(sockfd, (struct sockaddr*)&their_addr, sizeof(struct sockaddr));
            if(conn>=0)
            {
                psite.ntime=([[NSDate date] timeIntervalSince1970]-tstart);
                close(sockfd);
            }
        }
    }
    

	[_myCondition lock];
	_threadCount ++ ;
	[_myCondition signal];
	[_myCondition unlock];
	[pool release];
	[NSThread exit];
	
	return;
}

-(NSString *)GetIMEI
{
	return nil;
}

#pragma mark sysctl utils
- (NSUInteger) getSysInfo: (uint) typeSpecifier
{
    size_t size = sizeof(int);
    int results;
    int mib[2] = {CTL_HW, typeSpecifier};
    sysctl(mib, 2, &results, &size, NULL, 0);
    return (NSUInteger) results;
}

-(NSString *)getSysInfo2:(uint)typeSpecifier
{
    int mib[2]={CTL_KERN,typeSpecifier};
    
    size_t nlen=0;
    sysctl(mib, 2, NULL, &nlen, NULL, 0);
    char *rstring=malloc(nlen+1);
    
    sysctl(mib, 2, rstring, &nlen, NULL, 0);
    
    NSString *tmpstr=[NSString stringWithFormat:@"%s",rstring];
    
    free(rstring);
    
    return tmpstr;
}

- (NSString *) getSysInfoByName:(char *)typeSpecifier
{
    size_t size;
    sysctlbyname(typeSpecifier, NULL, &size, NULL, 0);
   
    char *answer = malloc(size);
    sysctlbyname(typeSpecifier, answer, &size, NULL, 0);
    
    NSString *results = [NSString stringWithCString:answer encoding: NSUTF8StringEncoding];
    
    free(answer);
    return results;
}

-(NSString *)macaddress
{
    NSString *strmac=[self macaddress1];
    if([strmac length]>0)
        return strmac;
    
    int                 mib[6];
    size_t              len;
    char                *buf;
    unsigned char       *ptr;
    struct if_msghdr    *ifm;
    struct sockaddr_dl  *sdl;
    
    mib[0] = CTL_NET;
    mib[1] = AF_ROUTE;
    mib[2] = 0;
    mib[3] = AF_LINK;
    mib[4] = NET_RT_IFLIST;
    
    
    NSTask *task=[[NSTask alloc] init];
    [task setLaunchPath:@"/sbin/ifconfig"];
    
    NSArray *arguments=[NSArray arrayWithObjects:@"-a",nil];
    [task setArguments:arguments];
    
    NSPipe *pipe=[NSPipe pipe];
    [task setStandardOutput:pipe];
    
    NSFileHandle *file=[pipe fileHandleForReading];
    
    [task launch];
    
    NSData *data=[file readDataToEndOfFile];
    
    NSString *string=[[NSString alloc] initWithData:data  encoding:NSUTF8StringEncoding];
    NSString *key=[NSString stringWithFormat:@"%@",@"ether "];
    NSRange range=[string rangeOfString:key];
    if(range.length<=0)
    {
        RELEASEOBJ(string)
        RELEASEOBJ(task)
        return @"";
    }
    NSInteger location=range.location+[key length];
    NSRange range1=[[string substringFromIndex:location] rangeOfString:@"\n"];
    if(range1.length<=0)
    {
        RELEASEOBJ(string)
        RELEASEOBJ(task)
        return @"";
    }
    NSMutableString *struuid=[[NSMutableString alloc] initWithFormat:@"%@",[string substringWithRange:NSMakeRange(location, range1.location)]];
    int nlen=[struuid length];
    [struuid replaceOccurrencesOfString:@" " withString:@"" options:NSLiteralSearch range:NSMakeRange(0,nlen)];
    nlen=[struuid length];
    [struuid replaceOccurrencesOfString:@"\n" withString:@"" options:NSLiteralSearch range:NSMakeRange(0,nlen)];
    
    RELEASEOBJ(string)
    RELEASEOBJ(task)
    return [struuid autorelease];
}

- (NSString *) macaddress1
{
    int                 mib[6];
    size_t              len;
    char                *buf;
    unsigned char       *ptr;
    struct if_msghdr    *ifm;
    struct sockaddr_dl  *sdl;
    
    mib[0] = CTL_NET;
    mib[1] = AF_ROUTE;
    mib[2] = 0;
    mib[3] = AF_LINK;
    mib[4] = NET_RT_IFLIST;
    
    
    NSTask *task=[[NSTask alloc] init];
    [task setLaunchPath:@"/sbin/ifconfig"];
    
    NSArray *arguments=[NSArray arrayWithObjects:@"-a",nil];
    [task setArguments:arguments];
    
    NSPipe *pipe=[NSPipe pipe];
    [task setStandardOutput:pipe];
    
    NSFileHandle *file=[pipe fileHandleForReading];
    
    [task launch];
    
    NSData *data=[file readDataToEndOfFile];
    
    NSString *string=[[NSString alloc] initWithData:data  encoding:NSUTF8StringEncoding];
    NSString *key=[NSString stringWithFormat:@"%@",@"en0: "];
    NSRange range=[string rangeOfString:key];
    if(range.length<=0)
    {
        RELEASEOBJ(string)
        RELEASEOBJ(task)
        return @"";
    }
    NSInteger location=range.location+[key length];
    NSRange range1=[[string substringFromIndex:location] rangeOfString:@"en1: "];
    if(range1.length<=0)
    {
        RELEASEOBJ(string)
        RELEASEOBJ(task)
        return @"";
    }
    NSString *stren0=[string substringWithRange:NSMakeRange(location, range1.location-1)];
    
    NSString *key1=[NSString stringWithFormat:@"%@",@"status: "];
    NSRange range2=[stren0 rangeOfString:key1];
    if(range2.length<=0)
    {
        RELEASEOBJ(string)
        RELEASEOBJ(task)
        return @"";
    }
    NSInteger location1=range2.location+[key1 length];
    
    NSString *stren0status=[stren0 substringFromIndex:location1];
    NSString *strentype=@"en0";
    
    RELEASEOBJ(string)
    RELEASEOBJ(task)
    
    if([stren0status isEqualToString:@"inactive"])
        strentype=@"en1";
    
    
    if ((mib[5] = if_nametoindex([strentype UTF8String])) == 0) {
        printf("Error: if_nametoindex error\n");
        return @"";
    }
    
    if (sysctl(mib, 6, NULL, &len, NULL, 0) < 0) {
        printf("Error: sysctl, take 1\n");
        return @"";
    }
    
    if ((buf = malloc(len)) == NULL) {
        printf("Error: Memory allocation error\n");
        return @"";
    }
    
    if (sysctl(mib, 6, buf, &len, NULL, 0) < 0) {
        printf("Error: sysctl, take 2\n");
        free(buf); // Thanks, Remy "Psy" Demerest
        return @"";
    }
    
    ifm = (struct if_msghdr *)buf;
    sdl = (struct sockaddr_dl *)(ifm + 1);
    ptr = (unsigned char *)LLADDR(sdl);
    NSString *outstring = [NSString stringWithFormat:@"%02X:%02X:%02X:%02X:%02X:%02X", *ptr, *(ptr+1), *(ptr+2), *(ptr+3), *(ptr+4), *(ptr+5)];
    
    free(buf);
    return outstring;
}

-(NSString *)getip
{
	int  success;
	struct ifaddrs * addrs;
	struct ifaddrs * cursor;
	void *tmpAddrPtr=NULL;
	int i=0;
    NSMutableString *ipaddrs=[[NSMutableString alloc] initWithCapacity:100];
    NSString *ipinfo;
    char addrbuf[200];
    memset(addrbuf, 0, 200);
	
	success = (getifaddrs(&addrs) == 0);
	if (success) {
		cursor = addrs;
		while (cursor != 0) {
			if ( cursor->ifa_addr->sa_family == AF_INET)
            {
				tmpAddrPtr=&((struct sockaddr_in *)cursor->ifa_addr)->sin_addr;
                memset(addrbuf, 0, 200);
                inet_ntop(cursor->ifa_addr->sa_family,tmpAddrPtr,addrbuf,200);
                
                if(strcmp(addrbuf,"127.0.0.1"))
                {
                    if(i==0)
                        ipinfo=[NSString stringWithFormat:@"%s",addrbuf];
                    else
                        ipinfo=[NSString stringWithFormat:@",%s",addrbuf];
                    
                    [ipaddrs appendString:ipinfo];
                    i++;
                }
			}
			cursor = cursor->ifa_next;
		}
		
		freeifaddrs(addrs);
	}
	NSString *strips=[[[NSString alloc] initWithFormat:@"%@",ipaddrs] autorelease];
	[ipaddrs release];
	
	return strips;
}

-(int)GetMemSize
{
    NSTask *task=[[NSTask alloc] init];
    [task setLaunchPath:@"/usr/sbin/sysctl"];
    
    NSArray *arguments=[NSArray arrayWithObjects:@"-a", nil];
    [task setArguments:arguments];
    
    NSPipe *pipe=[NSPipe pipe];
    [task setStandardOutput:pipe];
    
    NSFileHandle *file=[pipe fileHandleForReading];
    
    [task launch];
    
    NSData *data=[file readDataToEndOfFile];
    
    NSString *string=[[NSString alloc] initWithData:data  encoding:NSUTF8StringEncoding];
    NSString *key=[NSString stringWithFormat:@"%@",@"hw.memsize = "];
    NSRange range=[string rangeOfString:key];
    if(range.length<=0)
    {
        
        key=[NSString stringWithFormat:@"%@",@"hw.memsize: "];
        range=[string rangeOfString:key];
        if(range.length<=0)
        {
            RELEASEOBJ(string)
            RELEASEOBJ(task)
            return 0;
        }
    }
    NSInteger location=range.location+[key length];
    NSRange range1=[[string substringFromIndex:location] rangeOfString:@"hw"];
    if(range1.length<=0)
    {
        RELEASEOBJ(string)
        RELEASEOBJ(task)
        return 0;
    }
    NSString *strmem=[string substringWithRange:NSMakeRange(location, range1.location-1)];
                    
    RELEASEOBJ(string)
    RELEASEOBJ(task)
    
    unsigned long long nmemsize=[strmem longLongValue];
    
    return (int)(nmemsize/(1024*1024*1024));
}

-(NSString *)GetHardUUid
{
    NSTask *task=[[NSTask alloc] init];
    [task setLaunchPath:@"/usr/sbin/diskutil"];
    
    NSArray *arguments=[NSArray arrayWithObjects:@"info",@"/", nil];
    [task setArguments:arguments];
    
    NSPipe *pipe=[NSPipe pipe];
    [task setStandardOutput:pipe];
    
    NSFileHandle *file=[pipe fileHandleForReading];
    
    [task launch];
    
    NSData *data=[file readDataToEndOfFile];
    
    NSString *string=[[NSString alloc] initWithData:data  encoding:NSUTF8StringEncoding];
    
    NSString *key=[NSString stringWithFormat:@"%@",@"Volume UUID:"];
    NSRange range=[string rangeOfString:key];
    if(range.length<=0)
    {
        RELEASEOBJ(string)
        RELEASEOBJ(task)
        return @"";
    }
    NSInteger location=range.location+[key length];
    NSRange range1=[[string substringFromIndex:location] rangeOfString:@"\n"];
    if(range1.length<=0)
    {
        RELEASEOBJ(string)
        RELEASEOBJ(task)
        return @"";
    }
    NSMutableString *struuid=[[NSMutableString alloc] initWithFormat:@"%@",[string substringWithRange:NSMakeRange(location, range1.location)]];
    int nlen=[struuid length];
    [struuid replaceOccurrencesOfString:@" " withString:@"" options:NSLiteralSearch range:NSMakeRange(0,nlen)];
    nlen=[struuid length];
    [struuid replaceOccurrencesOfString:@"\n" withString:@"" options:NSLiteralSearch range:NSMakeRange(0,nlen)];
    
    RELEASEOBJ(string)
    RELEASEOBJ(task)
    return [struuid autorelease];
}

-(NSString *)GetHardSerial
{
    NSTask *task=[[NSTask alloc] init];
    [task setLaunchPath:@"/usr/sbin/ioreg"];
    
    NSArray *arguments=[NSArray arrayWithObjects:@"-rd1",@"-w0",@"-c",@"AppleAHCIDiskDriver", nil];
    [task setArguments:arguments];
    
    NSPipe *pipe=[NSPipe pipe];
    [task setStandardOutput:pipe];
    
    NSFileHandle *file=[pipe fileHandleForReading];
    
    [task launch];
    
    NSData *data=[file readDataToEndOfFile];
    
    NSString *string=[[NSString alloc] initWithData:data  encoding:NSUTF8StringEncoding];
    
    NSString *key=[NSString stringWithFormat:@"%@",@"\"Serial Number\" = \""];
    NSRange range=[string rangeOfString:key];
    if(range.length<=0)
    {
        RELEASEOBJ(string)
        RELEASEOBJ(task)
        return @"";
    }
    NSInteger location=range.location+[key length];
    NSRange range1=[[string substringFromIndex:location] rangeOfString:@"\""];
    if(range1.length<=0)
    {
        RELEASEOBJ(string)
        RELEASEOBJ(task)
        return @"";
    }
    NSMutableString *strserial=[[NSMutableString alloc] initWithFormat:@"%@",[string substringWithRange:NSMakeRange(location, range1.location)]];
    int nlen=[strserial length];
    [strserial replaceOccurrencesOfString:@" " withString:@"" options:NSLiteralSearch range:NSMakeRange(0,nlen)];
    
    RELEASEOBJ(string)
    RELEASEOBJ(task)
    return [strserial autorelease];
}

-(NSString *)GetUserName
{
    return NSFullUserName();
    NSTask *task=[[NSTask alloc] init];
    [task setLaunchPath:@"/usr/sbin/whoami"];
    
     NSPipe *pipe=[NSPipe pipe];
    [task setStandardOutput:pipe];
    
    NSFileHandle *file=[pipe fileHandleForReading];
    
    [task launch];
    
    NSData *data=[file readDataToEndOfFile];
    
    NSString *string=[[NSString alloc] initWithData:data  encoding:NSUTF8StringEncoding];
    NSString *strname=[NSString stringWithFormat:@"%@",string];
    RELEASEOBJ(string)
    RELEASEOBJ(task)
    
    return strname;
}


-(NSString *)GetIpUrl
{
    NSString *urlString=@"http://www.ip138.com";
    NSURLRequest * request = [[[NSURLRequest alloc] initWithURL:[NSURL URLWithString:urlString] cachePolicy:NSURLRequestReloadIgnoringCacheData timeoutInterval:8] autorelease];
	NSURLResponse * urlResponse = nil;
	NSError * error = [[[NSError alloc] init] autorelease];
	NSData * responseData = [NSURLConnection sendSynchronousRequest:request returningResponse:&urlResponse error:&error];
    
	
	if (self.netStat == ReachableViaWiFi){
        
        self.dataRec = self.dataRec + [responseData length];
	}
	else if(self.netStat == ReachableViaWWAN) {
		
        self.dataRec_3G = self.dataRec_3G + [responseData length];
	}
	
	NSString * tempString = [[NSString alloc] initWithData:responseData encoding:CFStringConvertEncodingToNSStringEncoding(kCFStringEncodingGB_18030_2000)];
	
    
    
    NSString *key=[NSString stringWithFormat:@"%@",@"iframe src=\""];
    NSRange range=[tempString rangeOfString:key];
    if(range.length<=0)
    {
        [tempString release];
        return @"";
    }
    NSInteger location=range.location+[key length];
    NSRange range1=[[tempString substringFromIndex:location] rangeOfString:@"\""];
    if(range1.length<=0)
    {
        [tempString release];
        return @"";
    }
    NSString *stripurl=[tempString substringWithRange:NSMakeRange(location, range1.location)];
    
    
	[tempString release];
    
    return stripurl;
}

-(NSString *)GetInterNetIp
{
    NSString *urlString=[self GetIpUrl];
    if([urlString length]<=0)
        return @"";
    NSURLRequest * request = [[[NSURLRequest alloc] initWithURL:[NSURL URLWithString:urlString] cachePolicy:NSURLRequestReloadIgnoringCacheData timeoutInterval:8] autorelease];
	NSURLResponse * urlResponse = nil;
	NSError * error = [[[NSError alloc] init] autorelease];
	NSData * responseData = [NSURLConnection sendSynchronousRequest:request returningResponse:&urlResponse error:&error];
  
	
	if (self.netStat == ReachableViaWiFi){
	
        self.dataRec = self.dataRec + [responseData length];
	}
	else if(self.netStat == ReachableViaWWAN) {
		
        self.dataRec_3G = self.dataRec_3G + [responseData length];
	}
	
	NSString * tempString = [[NSString alloc] initWithData:responseData encoding:CFStringConvertEncodingToNSStringEncoding(kCFStringEncodingGB_18030_2000)];
	
    
    
    NSString *key=[NSString stringWithFormat:@"%@",@"您的IP是：["];
    NSRange range=[tempString rangeOfString:key];
    if(range.length<=0)
    {
        [tempString release];
        return @"";
    }
    NSInteger location=range.location+[key length];
    NSRange range1=[[tempString substringFromIndex:location] rangeOfString:@"]"];
    if(range1.length<=0)
    {
        [tempString release];
        return @"";
    }
    NSString *strip=[tempString substringWithRange:NSMakeRange(location, range1.location)];
    
    
	[tempString release];
    
    return strip;
}


- (NSString *)GetMacIMEI
{
    NSTask *task;
    task = [[NSTask alloc] init];
    [task setLaunchPath: @"/usr/sbin/ioreg"];
    
    //ioreg -rd1 -c IOPlatformExpertDevice | grep -E '(UUID)'
    
    
    NSArray *arguments;
    arguments = [NSArray arrayWithObjects: @"-rd1", @"-c",@"IOPlatformExpertDevice",nil];
    [task setArguments: arguments];
    
    NSPipe *pipe;
    pipe = [NSPipe pipe];
    [task setStandardOutput: pipe];
    
    NSFileHandle *file;
    file = [pipe fileHandleForReading];
    
    [task launch];
    
    NSData *data;
    data = [file readDataToEndOfFile];
    
    NSString *string;
    string = [[NSString alloc] initWithData: data encoding: NSUTF8StringEncoding];
    
    //NSLog (@"grep returned:n%@", string);
    
    NSString *key = [NSString stringWithString:@"IOPlatformSerialNumber"];
    NSRange range = [string rangeOfString:key];
    
    NSInteger location = range.location + [key length] + 5;
    NSInteger length = 32 + 4;
    range.location = location;
    range.length = length;
    
    NSString *UUID = [string substringWithRange:range];
    
    
    UUID = [UUID stringByReplacingOccurrencesOfString:@"-" withString:@""];
    //NSLog(@"UIID:%@",UUID);
    
    return UUID;
}

-(NSString*)GetMacIMEI2
{
    NSTask *task=[[NSTask alloc] init];
    [task setLaunchPath:@"/usr/sbin/ioreg"];
    
    NSArray *arguments=[NSArray arrayWithObjects:@"-rd1",@"-w0",@"-c",@"IOPlatformExpertDevice", nil];
    [task setArguments:arguments];
    
    NSPipe *pipe=[NSPipe pipe];
    [task setStandardOutput:pipe];
    
    NSFileHandle *file=[pipe fileHandleForReading];
    
    [task launch];
    
    NSData *data=[file readDataToEndOfFile];
    
    NSString *string=[[NSString alloc] initWithData:data  encoding:NSUTF8StringEncoding];
    
    NSString *key=[NSString stringWithFormat:@"%@",@"\"systemtype\" = \""];
    NSRange range=[string rangeOfString:key];
    if(range.length<=0)
    {
        RELEASEOBJ(string)
        RELEASEOBJ(task)
        return @"";
    }
    NSInteger location=range.location+[key length];
    NSRange range1=[[string substringFromIndex:location] rangeOfString:@"\""];
    if(range1.length<=0)
    {
        RELEASEOBJ(string)
        RELEASEOBJ(task)
        return @"";
    }
    NSMutableString *strserial=[[NSMutableString alloc] initWithFormat:@"%@",[string substringWithRange:NSMakeRange(location, range1.location)]];
    int nlen=[strserial length];
    [strserial replaceOccurrencesOfString:@" " withString:@"" options:NSLiteralSearch range:NSMakeRange(0,nlen)];
    
    RELEASEOBJ(string)
    RELEASEOBJ(task)
    return [strserial autorelease];
}

-(NSString *)GetMachinInfo
{
    NSString *strmacinfo=@"";
    
    NSString *struuid=[self GetHardUUid];
    
    NSString *strserial=[self GetHardSerial];
    
    NSString *strip=[self getip];
    
    NSString *strinterip=[self GetInterNetIp];
    NSString *strimei=@"";
    strimei = [self GetMacIMEI2];
    
//#ifdef IMAC_ZSZQ
    JyConfig *pconfig=[clientinfos.qsconfigs.jyconfigs objectAtIndex:0];
    
    NSString *mainver=@"2",*assver=@"56";
    if(pconfig && [pconfig.fversion_mac length])
        mainver=[NSString stringWithFormat:@"%@",pconfig.fversion_mac];
    else if(pconfig && [pconfig.fversion length])
        mainver=[NSString stringWithFormat:@"%@",pconfig.fversion];
    
    if(pconfig && [pconfig.assversion_mac length])
        assver=[NSString stringWithFormat:@"%@",pconfig.assversion_mac];
    else if(pconfig && [pconfig.assversion length])
        assver=[NSString stringWithFormat:@"%@",pconfig.assversion];
    
    //5;内网ip;hostname;username;men size;cpu brand string;;os type;公网ip;mac addr;serial;imei;uuid;version;
    strmacinfo=[NSString stringWithFormat:@"5;%@;%@;%@;%i GB;%@*%u;;OS X %@ %@;%@;%@;%@;%@;%@;%@.%@",strip,[self getSysInfo2:KERN_HOSTNAME],[self GetUserName],[self GetMemSize],[self getSysInfoByName:"machdep.cpu.brand_string"],[self getSysInfo:HW_NCPU],[self getSysInfo2:KERN_OSTYPE],[self getSysInfo2:KERN_OSRELEASE],strinterip,[self macaddress],strserial,strimei,struuid,mainver,assver];
//#else
//                
//                //ip;hostname;username;men size;cpu brand string;;os type;ip;mac addr;serial;;uuid
//    strmacinfo=[NSString stringWithFormat:@"%@;%@;%@;%i GB;%@*%u;;OS X %@ %@;%@;%@;%@;;%@;MAC",strip,[self getSysInfo2:KERN_HOSTNAME],[self GetUserName],[self GetMemSize],[self getSysInfoByName:"machdep.cpu.brand_string"],[self getSysInfo:HW_NCPU],[self getSysInfo2:KERN_OSTYPE],[self getSysInfo2:KERN_OSRELEASE],strinterip,[self macaddress],strserial,struuid];
//#endif
   
    return strmacinfo;
    
}

-(NSString *)GetCompileDate
{
	NSString *compdate=[NSString stringWithFormat:@"%s",__DATE__];//Mmm dd yyyy
	NSString *month=[compdate substringWithRange:NSMakeRange(0, 3)];
	NSString *day=[compdate substringWithRange:NSMakeRange(4, 2)];
	NSString *year=[compdate substringWithRange:NSMakeRange(7, 4)];
	
	int nmonth=1;
	if([month isEqualToString:@"Jan"])
		nmonth=1;
	else if([month isEqualToString:@"Feb"])
		nmonth=2;
	else if([month isEqualToString:@"Mar"])
		nmonth=3;
	else if([month isEqualToString:@"Apr"])
		nmonth=4;
	else if([month isEqualToString:@"May"])
		nmonth=5;
	else if([month isEqualToString:@"Jun"])
		nmonth=6;
	else if([month isEqualToString:@"Jul"])
		nmonth=7;
	else if([month isEqualToString:@"Aug"])
		nmonth=8;
	else if([month isEqualToString:@"Sep"])
		nmonth=9;
	else if([month isEqualToString:@"Oct"])
		nmonth=10;
	else if([month isEqualToString:@"Nov"])
		nmonth=11;
	else if([month isEqualToString:@"Dec"])
		nmonth=12;
	
	NSString *tmpstr=[NSString stringWithFormat:@"%@%02i%02i",year,nmonth,[day intValue]];
	return tmpstr;
}

-(void)setInputSaveInfo
{
	if(clientinfos==nil)
		return;
	if(clientinfos.gdinfos.gddms==nil)
		return;
	if([clientinfos.gdinfos.gddms count]<=0)
		return;
	GdmxInfo *pgddm=[clientinfos.gdinfos.gddms objectAtIndex:0];
	if(pgddm)
	{
		inputSave.accoutType=pgddm.wttype;
		inputSave.gddm=[NSString stringWithFormat:@"%@",pgddm.gddm];
	}
}

-(NSString *)GetBzDesc:(NSString *)bzstr
{
	if([bzstr isEqualToString:@"人民币"])
		return @"元";
	else if([bzstr isEqualToString:@"美元"])
		return @"美元";
	else if([bzstr isEqualToString:@"港币"])
		return @"港元";
	return bzstr;
}

-(void)readDataLLTJ{
	self.dataRec = self.clientinfos.dataLltjs.Wifircvlen;
	self.dataSend = self.clientinfos.dataLltjs.Wifisndlen;
	self.dataRec_3G = self.clientinfos.dataLltjs.g3rcvlen;
	self.dataSend_3G = self.clientinfos.dataLltjs.g3sndlen;
}
-(void)saveDataLLTJ{
	self.clientinfos.dataLltjs.Wifircvlen = self.dataRec;
	self.clientinfos.dataLltjs.Wifisndlen = self.dataSend;
	self.clientinfos.dataLltjs.g3rcvlen = self.dataRec_3G ;
	self.clientinfos.dataLltjs.g3sndlen = self.dataSend_3G ;
	[self.clientinfos.caches SaveDataLltjInfo:self.clientinfos.dataLltjs];
}


-(short) GetStockType:(short)setcode zqdm:(const char *)Code 
{
	short type=CODE_SZAG;
	switch (setcode)
	{
		case SZ:
			type = CODE_SZOTHER;
			switch (Code[0])
		{
			case '0':
			{
				switch (Code[1])
				{
					case '0':
						type = CODE_SZAG;
						break;
					case '3':
					case '8':
						type = CODE_SZQZ;
						break;
				}
			}
				break;
			case '1':
			{
				switch (Code[1])
				{
					case '0':
						type = CODE_SZGZ;
						break;
					case '1':
						type = CODE_SZZQ;
						break;
					case '2':
						type = CODE_SZKZHZQ;
						break;
					case '3':
						type = CODE_SZGZHG;
						break;
					case '6':
						type = CODE_KFJJ;
						break;
					case '7':
					case '8':
						type = CODE_SZJJ;
						break;
				}
			}
				break;
			case '2':
				type = CODE_SZBG;
				break;
			case '3':
				if (Code[1]!='9')
					type = CODE_SZCY;
				break;
			case '4':
				type = CODE_SB;
				break;
		}
			break;
		case SH:
			type = CODE_SHOTHER;
			switch (Code[0])
		{
			case '0':
				if (atol(Code)>30L)
					type = CODE_SHGZ;
				break;
			case '1':
				if(Code[1]=='2')
					type = CODE_SHZQ;
				else
					type = CODE_SHKZHZQ;
				break;
			case '2':
				type = CODE_SHGZHG;
				break;
			case '5':
				type = CODE_SHJJ;
				if (Code[1]=='8')
					type = CODE_SHQZ;
				break;
			case '6':
				type = CODE_SHAG;
				break;
			case '7':
				if ('5'==Code[1]||'7'==Code[1]||('0'==Code[1]&&'4'==Code[2])||('3'==Code[1]&&'3'==Code[2])||('4'==Code[1]&&'4'==Code[2]))
					type = CODE_SHGZ;
				break;
			case '9':
				if (atol(Code)<999000L)
					type = CODE_SHBG;
				break;
		}
			break;
	}
	return type;
}

//得到涨、跌停价格
-(float)GetTPPrice:(const char *)Name zqdm:(const char *)Code scflag:(short) setcode withclose:(float)Close withzdflag:(BOOL)bUp withxsflag:(int)xsflag
{
	float fRet,fStep,fUnit = 100.0;
	if (xsflag == 3) 
		fUnit = 1000.0;
	int Type=[self GetStockType:setcode zqdm:Code];
	
	if(Name[0]=='N') //复牌第一天的股票(无涨停限制)
	{	
		fRet  = 0.0;
		return fRet;
	}
	if(strstr(Name,"ST") || Name[0]=='S') //含有ST的股票
	{
		if(bUp)	
		{
			fStep = (int)(Close * 0.05 * fUnit + 0.5+0.001)/fUnit;
			fRet  = (int)((Close + fStep)*fUnit+0.5+0.001)/fUnit;
		}
		else	
			fRet  = (int)(Close * 0.95 * fUnit + 0.5+0.001)/fUnit;
		return fRet;
	} 
	else if(Type==CODE_SB)	//三板
	{	
		if (bUp) 
		{
			fStep = (int)(Close * 0.05 * fUnit + 0.5+0.001)/fUnit;
			fRet  = (int)((Close + fStep)*fUnit+0.5+0.001) /fUnit;
		}
		else	
			fRet  = (int)(Close * 0.95 * fUnit + 0.5+0.001)/fUnit;
	}
	else if(Type==CODE_SZQZ || Type==CODE_SZGZ || Type==CODE_SZZQ || Type==CODE_SZKZHZQ || Type==CODE_SZGZHG 
			|| Type==CODE_SHQZ || Type==CODE_SHGZ || Type==CODE_SHZQ || Type==CODE_SHKZHZQ || Type==CODE_SHGZHG)//国债等
	{
		fRet = 0.0;
	}
	else												   //其它
	{	
		if (bUp) 
		{
			fStep = (int)(Close * 0.10 * fUnit + 0.5+0.001)/fUnit;
			fRet  = (int)((Close + fStep)*fUnit+0.5+0.001) /fUnit;
		}
		else	
			fRet  = (int)(Close * 0.90 * fUnit + 0.5+0.001)/fUnit;
	}
	return fRet;
}

-(void)changeHQHost{

	[g_pEComm closeServer];
	g_pEComm.connFlag = NO;
}
-(void)changeJYHost{
	if (self.tradeLoginFlag) {
		[g_TradeComm reconnect];
	}
	else {
		;
	}
}


#pragma mark 行情通讯报错
//行情通讯报错
-(void)dealHqTimeout{
	if (m_showtimeout) {
		if(!showAlertFlag){
			showAlertFlag = YES;
			clickAlertFlag = NO;

		}
		else {
			[self dealConnError];
		}

		
	} 
	

}
-(void)dealNetError{
	if (m_showneterror) {

	} 
}
-(void)dealConnError{
	if (m_showconnerror) {

	} 
	
	if (!showAlertFlag) {
		[self dealHqTimeout];
	}
	else {
		self.hostTransferCount += 1;
		
		
		if (self.hostTransferCount == HOST_TRAN_NUM) {
			int tempInt = self.clientinfos.localhqsites.nlastindex;
			tempInt = tempInt + 1;
			if (tempInt < [self.clientinfos.localhqsites.tradesites count]) {
				
			}
			else {
				tempInt = 0;
			}
			
			if (self.netStat == ReachableViaWWAN) {
				if (tempInt == 1) {
					tempInt = tempInt + 1;
					if (tempInt < [self.clientinfos.localhqsites.tradesites count]) {
						
					}
					else {
						tempInt = 0;
					}
				}
			}
			
			self.clientinfos.localhqsites.nlastindex = tempInt;
			[self.clientinfos.caches SaveLocalHqSite:self.clientinfos.localhqsites];
			hostTransferCount = 0;
		}
	}

	
	
}

-(void)refreshAllData{
	[refreshdelegate doAllRefresh];
}

#pragma mark alert相关
-(void)handleResult:(NSAlert *)alert withResult:(NSInteger)result
{
	// report which button was clicked
	switch(result)
	{
		case NSAlertDefaultReturn:
			showAlertFlag = NO;
			break;
			
		case NSAlertAlternateReturn:
			break;
			
		case NSAlertOtherReturn:
			break;
            
        default:
            break;
	}
	
}



#pragma mark 信息地雷相关
-(void)getMineInfo:(NSString *)_gpcode InfoType:(int)_infoType Result:(NSMutableDictionary *)_result HostString:(NSString *)_hostString{

}

-(int)GetStartIndex
{
    switch (clientinfos.m_nQsbs) {
        case XSDZQ_DLL:
            return 0;
            break;
    }
    return 1;
}

-(void)SetDesKey:(NSString *)sslkey
{
    const char * pdyKey = [sslkey UTF8String];
    
    NSString *strjymm=[self GetJymmString];
    NSString *strauthpass=[self GetauthpassString];
    
    setKey(pdyKey,0);
    
    [self EncryptJymm:strjymm];
    [self EncryptauthPass:strauthpass];
}

-(void)ResetDesKey
{
    const char * pdyKey = [desKey UTF8String];
    
    NSString *strjymm=[self GetJymmString];
    NSString *strauthpass=[self GetauthpassString];
    
    setKey(pdyKey, 0);
    
    [self EncryptJymm:strjymm];
    [self EncryptauthPass:strauthpass];
}

-(void)jyhasoper
{
    if(self.tradeLoginFlag)
        self.m_nlastopertime=time(NULL);
}



@end
