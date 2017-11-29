//
//  struct.h
//  tdxiphone
//
//  Created by 魏 文敏 on 09-12-23.
//  Copyright 2009 武汉. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "macro.h"
#import "wtstruct.h"

/************************************************************************/
/*                                                                      */
/*                             行情                                     */
/*                                                                      */
/************************************************************************/

#define   SH_CODE_LEN      6
#define   NAME_LEN         8

typedef struct {	
	unsigned char theVersion:4;
	unsigned char theCompressed:1;
	unsigned char theEncrypted:1;
	unsigned char isMobile:1;
	unsigned char theReserved:1;
} ReqInfo;

#pragma mark 行情协议请求包结构

//请求头
@interface TagReqHeader : NSObject {
	char info;
	int mainID;
	int assisID;
	char  priority;
	int packetLen;
	int rawLen;
}

@property char  info;
@property int mainID;
@property int assisID;
@property char  priority;
@property int packetLen;
@property int rawLen;

@end


//grid行情

@interface Minute_Unit : NSObject {
	short minute;
	float now;			
	float average;
	int nowvol;
	float zaf;
}

@property short minute;
@property float now;	
@property float average;
@property int nowvol;
@property float zaf;

@end
//k线
@interface Analyse_Unit : NSObject {
	int date;
	int time;			
	float openp;
	float highp;
	float lowp;
	float closep;
	float amount;
	int volumn;
	
	float maFive;
	float maTen;
	float maTwn;
	
	float zaf;
	float zad;
}

@property int date;
@property int time;		
@property float openp;
@property float highp;
@property float lowp;
@property float closep;
@property float amount;
@property int volumn;
@property float maFive;
@property float maTen;
@property float maTwn;
@property float zaf;
@property float zad;

-(Analyse_Unit *)analyseDeepCopy;

@end

//指标
@interface zb_Unit : NSObject {
	float  vol_Five;
	float  vol_Ten;			
	float  macd_Short;
	float  macd_Long;
	float  macd_DIF;
	float  macd_DEF;
	float  macd_MACD;
	
	float kdj_RSV;
	float kdj_K;
	float kdj_D;
	float kdj_J;
	
	float rsi_max;
	float rsi_abs;
	float rsi_max6;
	float rsi_abs6;
	float rsi_max12;
	float rsi_abs12;
	float rsi_max24;
	float rsi_abs24;
	float rsi_RSI1;
	float rsi_RSI2;
	float rsi_RSI3;
	
	float bias_Six;
	float bias_Twe;
	float bias_Twf;
	float bias_BIAS1;
	float bias_BIAS2;
	float bias_BIAS3;
	
	float zb_1;
	float zb_2;
	float zb_3;
	float zb_4;
	float zb_5;
	float zb_6;
}

@property float  vol_Five;
@property float  vol_Ten;		

@property float  macd_Short;
@property float  macd_Long;
@property float  macd_DIF;
@property float  macd_DEF;
@property float  macd_MACD;

@property float kdj_RSV;
@property float kdj_K;
@property float kdj_D;
@property float kdj_J;

@property float rsi_max;
@property float rsi_abs;
@property float rsi_max6;
@property float rsi_abs6;
@property float rsi_max12;
@property float rsi_abs12;
@property float rsi_max24;
@property float rsi_abs24;
@property float rsi_RSI1;
@property float rsi_RSI2;
@property float rsi_RSI3;

@property float bias_Six;
@property float bias_Twe;
@property float bias_Twf;
@property float bias_BIAS1;
@property float bias_BIAS2;
@property float bias_BIAS3;

@property float zb_1;
@property float zb_2;
@property float zb_3;
@property float zb_4;
@property float zb_5;
@property float zb_6;

@end


@interface F10Title_Unit : NSObject {
	NSString * sTitle;
	NSString *  sFilePath;			
	int nOffset;
	int nLength;
}

@property (nonatomic , retain) NSString * sTitle;
@property (nonatomic , retain) NSString * sFilePath;
@property int nOffset;
@property int nLength;

@end

@interface InputSave : NSObject {
	short accoutType;
	short nreloginaccoutType;
	NSString *  gddm;			
	NSString *  branchId;
	NSString *  accout;
	NSMutableData *  password;
	NSString *	wtfs;
	uint64_t sessionID;
	int    tdxbranchid;
	int   authtype;
	NSMutableData	 *authpassword;
	NSString	 *reloginsession;
	NSString *yhdm;
    NSString* dbphz_gddm;
    NSString* dbphz_mm;
}
@property short nreloginaccoutType;
@property short accoutType;
@property (nonatomic , retain) NSString * gddm;
@property (nonatomic , retain) NSString * branchId;
@property (nonatomic , retain) NSString * accout;
@property (nonatomic , retain) NSMutableData*  password;
@property (nonatomic , retain) NSString *	wtfs;
@property  uint64_t sessionID;
@property(nonatomic) int tdxbranchid;
@property(nonatomic) int authtype;
@property(nonatomic,retain) NSMutableData *authpassword;
@property(nonatomic,retain) NSString *reloginsession;
@property(nonatomic,retain) NSString *yhdm;
@property(nonatomic,retain) NSString *dbphz_gddm;
@property(nonatomic,retain) NSString *dbphz_mm;

-(void)setjyPassword:(unsigned char *)data len:(int)nlen;
-(void)releasePassword;

-(void)setauthPassword:(unsigned char *)data len:(int)nlen;
-(void)releaseauthPassword;

-(void)setReloginSession:(NSString *)strsession;
-(void)releasereloginsession;
@end

@interface RecvField : NSObject {
	int  index;
	int m_dwFieldId;
	int   m_cFieldType;
	BOOL m_bvisible;
	int   nvisibleindex;
	NSString *  m_sFieldName;
	int maxwidth;
}
@property(nonatomic) int   nvisibleindex;
@property(nonatomic) int index;
@property (nonatomic)	int m_dwFieldId;
@property (nonatomic , retain) NSString * m_sFieldName;
@property (nonatomic) int  m_cFieldType;
@property(nonatomic) BOOL m_bvisible;
@property(nonatomic) int maxwidth;
@end


@interface StockInfo : NSObject<NSCoding>
{
	int setcode;
	NSString *  gpcode;			
	NSString * gpname;
	NSString * gpspell;
}

@property int setcode;
@property (nonatomic , retain) NSString * gpcode;
@property (nonatomic , retain) NSString * gpname;
@property (nonatomic , retain) NSString * gpspell;


@end

@interface GridCellInfo : NSObject<NSCoding>
{
	int cellID;
	NSString * cellName;
	int cellWidth;
	int cellSortID;
	BOOL cellShowFlag;
	BOOL cellFixFlag;
	int cellMarktet;
}

@property int cellID;
@property (nonatomic , retain)NSString * cellName;
@property int cellWidth;
@property int cellSortID;
@property BOOL cellShowFlag;
@property BOOL cellFixFlag;
@property int cellMarktet;

-(GridCellInfo *)deepcopy;

@end



@interface ProcessInfo : NSObject
{
	int setcode;
	NSString *  gpcode;	
	NSString *  showcode;	
	NSString *  gpname;	
	int typeID;
	int paraOne;
	int paraTwo;
}

@property int setcode;
@property (nonatomic , retain) NSString * showcode;	
@property (nonatomic , retain) NSString * gpcode;
@property (nonatomic , retain) NSString * gpname;
@property int typeID;
@property int paraOne;
@property int paraTwo;


@end

@interface TickInfo : NSObject
{
	int minute;
	float nowPrice;
	int nowVol;
	int inOutFlag;
}

@property int minute;
@property float nowPrice;
@property int nowVol;
@property int inOutFlag;



@end

@interface InfoUnit : NSObject
{
	int theIndex;
	int unitID;
	NSString *  href;			
	NSString * title;
}

@property int theIndex;
@property int unitID;
@property (nonatomic , retain) NSString * href;
@property (nonatomic , retain) NSString * title;

@end

@interface GridInfo : NSObject
{
	int extype;
	int startxh;
	int wantnum;
	int grid_domain;
	int coltype;
	int sorttype;
}

@property int extype;
@property int startxh;
@property int wantnum;
@property int grid_domain;
@property int coltype;
@property int sorttype;

@end

@interface GBBQInfo : NSObject
{
	int theDate;
	char theType;
	float B01;
	float B02;
	float B03;
	float B04;
}

@property int theDate;
@property char theType;
@property float B01;
@property float B02;
@property float B03;
@property float B04;

@end

@interface MineInfo : NSObject
{
	int rec_ID;
	int time_ymd;
	int theTime;
	NSString * theTitle;
	int type_id;//分类id
	char show_id;
	char proc_id;
	NSString * infoSrc;
	char info_format;
	NSString * infoURL;
	NSString * theContent;
}

@property int theTime;
@property int rec_ID;
@property int time_ymd;
@property int type_id;//分类id
@property char show_id;
@property char proc_id;
@property (nonatomic , retain) NSString * infoSrc;
@property char info_format;
@property (nonatomic , retain) NSString * theTitle;
@property (nonatomic , retain) NSString * theContent;
@property (nonatomic , retain) NSString * infoURL;
@end



@interface RecDataUnit : NSObject
{
	int threadName;
	NSMutableData * recData;
	int httpFlag;
}

@property int threadName;
@property (nonatomic , retain) NSMutableData * recData;
@property int httpFlag;
//@property (nonatomic , retain) NSString * title;
- (id) initWithData:(NSMutableData *)_recData;
@end


@interface DateSave : NSObject
{
	int nStartDate;
	int nEndDate;
    NSArray* arrayData;
    NSString* DBPHZ_xw;
    NSString* DBPHZ_ptgddm;
    NSString* DBPHZ_zhlb;
    NSString* DBPHZ_dfkhh; //资金帐号
    NSString* DBPHZ_dfmm;
    int nzjlsBZ;
    NSString* xwdm;
    NSString* jysdxjc_login;
    BOOL b_isFirstUsed;
}
@property int nStartDate;
@property int nEndDate;
@property (nonatomic , retain) NSArray * arrayData;
@property (nonatomic , retain) NSString * DBPHZ_xw;
@property (nonatomic , retain) NSString * DBPHZ_ptgddm;
@property (nonatomic , retain) NSString * DBPHZ_zhlb;
@property (nonatomic , retain) NSString * DBPHZ_dfkhh;
@property (nonatomic , retain) NSString * DBPHZ_dfmm;
@property int nzjlsBZ;
@property (nonatomic,copy) NSString* xwdm;
@property (nonatomic,copy) NSString* jysdxjc_login;
@property BOOL b_isFirstUsed;
@end


@interface NSObject(asyncrecv)

-(BOOL)OnReceiveData:(int)reqIndex parser:(id)pParse;

@end

@interface HqResultData : NSObject
{
	NSMutableData * resultData;
	int receiveLen;
	int resultStat;
}

@property (nonatomic , retain) NSMutableData * resultData;
@property int receiveLen;
@property int resultStat;

@end


@interface AsyncSendData : NSObject
{
	short nobjIndex;
	short nreqIndex;
	BOOL bsended;
	NSMutableData *senddata;
}
@property(nonatomic) BOOL bsended;
@property(nonatomic) short nobjIndex;
@property(nonatomic) short nreqIndex;
@property(nonatomic,retain) NSMutableData *senddata;

-(id)initWithData:(int)nobjIndex1 reqIndex:(int)nreqIndex1 data:(NSMutableData *)nsenddata;
@end


@interface FinanceData : NSObject
{
	float       ActiveCapital;      // 流通股本	
	float       cdp;                // 昨日中价
	float       nh;                 // 卖点
	float       nl;                 // 买点
	float       ah;                 // 高价突破点
	float       al;                 // 低价突破点
	short       dkflag;             // 适合作多或作空
	float       tbp;                // 多空平衡点
	float       stoplost;           // 止损点
	float       leave;              // 了结点
	short       J_addr;				//所属省份
	short       J_hy;				//所属行业
    long        J_gxrq;				//更新日期
	long		J_start;			//上市日期
    float       J_zgb;				//总股本
    float       J_zjhhy;			//证监会行业
    float       J_oldjly;			//上年此期净利润
    float       J_oldzysy;			//上年此期主营收入
    float       J_bg;				//B股
    float       J_hg;				//H股
    float       J_mgsy2;			//季报每股收益 (财报中提供的每股收益,有争议的才填)
    float       J_zzc;				//总资产(千元)
    float       J_ldzc;				//流动资产
    float       J_gdzc;				//固定资产
    float       J_wxzc;				//无形资产
    float       J_cqtz;				//长期投资
    float       J_ldfz;				//流动负债
    float       J_cqfz;				//长期负债
    float       J_zbgjj;			//资本公积金
    float       J_jzc;				//股东权益(就是净资产)
    float       J_zysy;				//主营收入
    float       J_zyly;				//主营利益
    float       J_qtly;				//其它利益
    float       J_yyly;				//营业利益
    float       J_tzsy;				//投资收益
    float       J_btsy;				//补贴收入
    float       J_yywsz;			//营业外收支
    float       J_snsytz;			//上年损益调整
    float       J_lyze;				//利益总额
    float       J_shly;				//税后利益
    float       J_jly;				//净利益
    float       J_wfply;			//未分配利益
    float       J_tzmgjz;			//调整每股净资产 物理意义:  净资产/调整后的总股本
	float		J_HalfYearFlag;		//报告期
}
@property float   ActiveCapital;      // 流通股本	
@property float     cdp;                // 昨日中价
@property float       nh;                 // 卖点
@property float       nl;                 // 买点
@property float       ah;                 // 高价突破点
@property float       al;                 // 低价突破点
@property short       dkflag;             // 适合作多或作空
@property float       tbp;                // 多空平衡点
@property float       stoplost;           // 止损点
@property float       leave;              // 了结点
@property short       J_addr;				//所属省份
@property short       J_hy;				//所属行业
@property long        J_gxrq;				//更新日期
@property long		J_start;			//上市日期
@property float       J_zgb;				//总股本
@property float       J_zjhhy;			//证监会行业
@property float       J_oldjly;			//上年此期净利润
@property float       J_oldzysy;			//上年此期主营收入
@property float       J_bg;				//B股
@property float       J_hg;				//H股
@property float       J_mgsy2;			//季报每股收益 (财报中提供的每股收益,有争议的才填)
@property float       J_zzc;				//总资产(千元)
@property float       J_ldzc;				//流动资产
@property float       J_gdzc;				//固定资产
@property float       J_wxzc;				//无形资产
@property float       J_cqtz;				//长期投资
@property float       J_ldfz;				//流动负债
@property float       J_cqfz;				//长期负债
@property float       J_zbgjj;			//资本公积金
@property float       J_jzc;				//股东权益(就是净资产)
@property float       J_zysy;				//主营收入
@property float       J_zyly;				//主营利益
@property float       J_qtly;				//其它利益
@property float       J_yyly;				//营业利益
@property float       J_tzsy;				//投资收益
@property float       J_btsy;				//补贴收入
@property float       J_yywsz;			//营业外收支
@property float       J_snsytz;			//上年损益调整
@property float       J_lyze;				//利益总额
@property float       J_shly;				//税后利益
@property float       J_jly;				//净利益
@property float       J_wfply;			//未分配利益
@property float       J_tzmgjz;			//调整每股净资产 物理意义:  净资产/调整后的总股本
@property float		J_HalfYearFlag;		//报告期


@end



@interface ImageRect : NSObject
{
	CGPoint origin;
	CGSize size;
}
@property CGPoint origin;
@property CGSize size;

-(id)initWithRect:(CGRect)_rect;
-(CGRect)frame; 
@end
