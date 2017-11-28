//
//  struct.m
//  tdxiphone
//
//  Created by 魏 文敏 on 09-12-23.
//  Copyright 2009 武汉. All rights reserved.
//

#import "struct.h"



@implementation TagReqHeader

@synthesize info;
@synthesize mainID;
@synthesize assisID;
@synthesize priority;
@synthesize packetLen;
@synthesize rawLen;

 - (id) init
{
	self = [super init];
	if (self != nil) {
		info = 12;
		mainID = 1;
		assisID =1;
		priority = 0;
		packetLen = 10;
		rawLen = 10;
	}
	return self;
}


- (void) dealloc
{
	
	[super dealloc];
}

@end

@implementation Minute_Unit

@synthesize now,minute,average,nowvol,zaf;

- (void) dealloc
{
	
	[super dealloc];
}

@end

@implementation Analyse_Unit

@synthesize date,time,openp,highp,lowp,closep,amount,volumn,maFive,maTen,maTwn,zaf,zad;


- (id) init
{
	self = [super init];
	
	return self;
}

-(Analyse_Unit *)analyseDeepCopy{
	Analyse_Unit * newInfo = [[Analyse_Unit alloc] init];
	
	newInfo.date = self.date;
	newInfo.time = self.time;			
	newInfo.openp= self.openp;
	newInfo.highp= self.highp;
	newInfo.lowp= self.lowp;
	newInfo.closep= self.closep;
	newInfo.amount= self.amount;
	newInfo.volumn= self.volumn;
	
	newInfo.maFive= self.maFive;
	newInfo.maTen= self.maTen;
	newInfo.maTwn= self.maTwn;
	
	newInfo.zaf= self.zaf;
	newInfo.zad= self.zad;
	
	return newInfo;
}

- (void) dealloc
{
	
	[super dealloc];
}

@end

@implementation zb_Unit

@synthesize vol_Five,vol_Ten,macd_Short,macd_Long,macd_DIF,macd_DEF,macd_MACD;
@synthesize kdj_RSV,kdj_K,kdj_D,kdj_J,rsi_max,rsi_abs,rsi_RSI1,rsi_RSI2,rsi_RSI3,bias_Six,bias_Twe,bias_Twf,bias_BIAS1,bias_BIAS2,bias_BIAS3;
@synthesize rsi_max6,rsi_abs6,rsi_max12,rsi_abs12,rsi_max24,rsi_abs24;
@synthesize zb_1,zb_2,zb_3,zb_4,zb_5,zb_6;
- (id) init
{
	self = [super init];
	
	return self;
}


- (void) dealloc
{
	
	[super dealloc];
}

@end

@implementation F10Title_Unit

@synthesize sTitle,sFilePath,nOffset,nLength;


- (id) init
{
	self = [super init];
	
	return self;
}


- (void) dealloc
{
	[sTitle release];
	[sFilePath release];
	[super dealloc];
}

@end

@implementation InputSave

@synthesize accoutType,gddm,branchId,password,accout,sessionID,wtfs,tdxbranchid,authpassword,authtype,yhdm,reloginsession,nreloginaccoutType;


- (id) init
{
	self = [super init];
	if(self)
	{
		nreloginaccoutType=0;
		password=nil;
		authpassword=nil;
		reloginsession=nil;
	}
	return self;
}


- (void) dealloc
{
	[reloginsession release];
	[authpassword release];
	[gddm release];
	[branchId release];
	[accout release];
	[password release];
	[wtfs release];
	[yhdm release];
	[super dealloc];
}

-(void)setjyPassword:(unsigned char *)data len:(int)nlen
{
	[self releasePassword];
	password=[[NSMutableData alloc] init];
	[password appendBytes:data length:nlen];
}

-(void)releasePassword
{
	[password release];
	password=nil;
}

-(void)setauthPassword:(unsigned char *)data len:(int)nlen
{
	[self releaseauthPassword];
	authpassword=[[NSMutableData alloc] init];
	[authpassword appendBytes:data length:nlen];
}

-(void)releaseauthPassword
{
	[authpassword release];
	authpassword=nil;
}

-(void)setReloginSession:(NSString *)strsession
{
	[self releasereloginsession];
	reloginsession=[[NSString alloc] initWithFormat:@"%@",strsession];
}

-(void)releasereloginsession
{
	[reloginsession release];
	reloginsession=nil;
}
@end

@implementation RecvField

@synthesize m_dwFieldId,m_sFieldName,m_cFieldType,m_bvisible,index,nvisibleindex,maxwidth;


- (id) init
{
	self = [super init];
	if(self)
	{
		m_sFieldName=nil;
		m_bvisible=YES;
		m_dwFieldId=0;
		m_cFieldType=0;
		index=0;
		nvisibleindex=0;
		maxwidth=0;
	}
	return self;
}


- (void) dealloc
{
	[m_sFieldName release];
	[super dealloc];
}

@end

@implementation DateSave

@synthesize nStartDate,nEndDate,nzjlsBZ,xwdm,jysdxjc_login,b_isFirstUsed;
-(id) init
{
	self = [super init];
    xwdm = [NSString stringWithFormat:@"%@",@""];
    jysdxjc_login = [NSString stringWithFormat:@"%@",@""];
    b_isFirstUsed = NO;
	return self;
}

-(void) dealloc
{
	[super dealloc];
}

@end

@implementation StockInfo

@synthesize setcode,gpcode,gpname,gpspell;

- (id) init
{
	self = [super init];

	
	return self;
}
-(void)encodeWithCoder:(NSCoder *)encoder
{
	[encoder encodeInt:setcode forKey:@"StockInfoSetcode"];
	[encoder encodeObject:gpcode forKey:@"StockInfoGpcode"];
	[encoder encodeObject:gpname forKey:@"StockInfoGpname"];
	[encoder encodeObject:gpspell forKey:@"StockInfoGpspell"];
}

-(id)initWithCoder:(NSCoder *)aDecoder
{
	self=[super init];
	if(self)
	{
		setcode=[aDecoder decodeIntForKey:@"StockInfoSetcode"];
		gpcode=[[aDecoder decodeObjectForKey:@"StockInfoGpcode"] retain];
		gpname=[[aDecoder decodeObjectForKey:@"StockInfoGpname"] retain];
		gpspell=[[aDecoder decodeObjectForKey:@"StockInfoGpspell"] retain];
	}
	
	return self;
}

- (void) dealloc
{
	[gpcode release];
	[gpname release];
	[gpspell release];
	[super dealloc];
}

@end


@implementation GridCellInfo

@synthesize cellID,cellName,cellWidth,cellSortID,cellShowFlag,cellFixFlag,cellMarktet;

- (id) init
{
	self = [super init];
	
	return self;
}
-(void)encodeWithCoder:(NSCoder *)encoder
{
	[encoder encodeInt:cellID forKey:@"GridCellInfoCellID"];
	[encoder encodeObject:cellName forKey:@"GridCellInfoCellName"];
	[encoder encodeInt:cellWidth forKey:@"GridCellInfoCellWidth"];
	[encoder encodeInt:cellSortID forKey:@"GridCellInfoCellSortID"];
	[encoder encodeBool:cellShowFlag forKey:@"GridCellInfoCellShowFlag"];
	[encoder encodeBool:cellFixFlag forKey:@"GridCellInfoCellFixFlag"];
	[encoder encodeInt:cellMarktet forKey:@"GridCellInfoCellMarket"];
}

-(id)initWithCoder:(NSCoder *)aDecoder
{
	self=[super init];
	if(self)
	{
		cellID=[aDecoder decodeIntForKey:@"GridCellInfoCellID"];
		cellName=[[aDecoder decodeObjectForKey:@"GridCellInfoCellName"] retain];
		cellWidth=[aDecoder decodeIntForKey:@"GridCellInfoCellWidth"];
		cellSortID=[aDecoder decodeIntForKey:@"GridCellInfoCellSortID"];
		cellShowFlag = [aDecoder decodeBoolForKey:@"GridCellInfoCellShowFlag"];
		cellFixFlag = [aDecoder decodeBoolForKey:@"GridCellInfoCellFixFlag"];
		cellMarktet= [aDecoder decodeIntForKey:@"GridCellInfoCellMarket"];
	}
	
	return self;
}

-(GridCellInfo *)deepcopy
{
	GridCellInfo *pstockinfo=[[GridCellInfo alloc]init];
	
	pstockinfo.cellID=self.cellID;
	pstockinfo.cellName=[[NSString alloc] initWithFormat:@"%@",cellName];
	[pstockinfo.cellName release];
	pstockinfo.cellWidth = self.cellWidth;
	pstockinfo.cellSortID = self.cellSortID;
	pstockinfo.cellShowFlag = self.cellShowFlag;
	pstockinfo.cellFixFlag = self.cellFixFlag;
	pstockinfo.cellMarktet = self.cellMarktet;
	return pstockinfo;
}

- (void) dealloc
{
	[cellName release];
	[super dealloc];
}

@end



@implementation ProcessInfo

@synthesize setcode,gpcode,gpname,typeID,paraOne,paraTwo,showcode;

- (id) init
{
	self = [super init];
	
	return self;
}


- (void) dealloc
{
	[gpcode release];
	[gpname release];
	[showcode release];
	[super dealloc];
}

@end

@implementation TickInfo

@synthesize minute,nowPrice,nowVol,inOutFlag;

- (id) init
{
	self = [super init];
	
	return self;
}


- (void) dealloc
{
	
	[super dealloc];
}

@end


@implementation InfoUnit

@synthesize unitID,href,title,theIndex;

- (id) init
{
	self = [super init];
	
	return self;
}


- (void) dealloc
{
	[href release];
	[title release];
	[super dealloc];
}

@end

@implementation MineInfo

@synthesize rec_ID,time_ymd,theTime,theTitle,type_id,show_id,proc_id,infoSrc,info_format,infoURL,theContent;

- (id) init
{
	self = [super init];
	
	return self;
}


- (void) dealloc
{
	[infoSrc release];
	[infoURL release];
	[theTitle release];
	[theContent release];
	[super dealloc];
}

@end


@implementation NSObject(asyncrecv)

-(BOOL)OnReceiveData:(int)reqIndex parser:(id)pParse
{
	return YES;
}

@end

@implementation GridInfo

@synthesize startxh,wantnum,grid_domain,coltype,sorttype,extype;

- (id) init
{
	self = [super init];
	
	return self;
}


- (void) dealloc
{
	
	[super dealloc];
}

@end


@implementation GBBQInfo

@synthesize theDate,theType,B01,B02,B03,B04;

- (id) init
{
	self = [super init];
	
	return self;
}


- (void) dealloc
{
	
	[super dealloc];
}

@end



@implementation RecDataUnit

@synthesize threadName,recData,httpFlag;

- (id) initWithData:(NSMutableData *)_recData
{
	self = [super init];
	
	self.recData = [_recData retain];
	
	return self;
}


- (void) dealloc
{
	[recData release];
	[super dealloc];
}

@end

@implementation HqResultData

@synthesize resultData,receiveLen,resultStat;
-(id) init
{
	self = [super init];
	return self;
}

-(void) dealloc
{
	[resultData release];
	[super dealloc];
}

@end

@implementation AsyncSendData

@synthesize nobjIndex,nreqIndex,senddata,bsended;

-(id)initWithData:(int)nobjIndex1 reqIndex:(int)nreqIndex1 data:(NSMutableData *)nsenddata
{
	self=[super init];
	if(self)
	{
		nobjIndex=nobjIndex1;
		nreqIndex=nreqIndex1;
		senddata=nsenddata;
		bsended=NO;
	}
	return self;
}

-(void)dealloc
{
	[senddata release];
	[super dealloc];
}
@end

@implementation FinanceData

@synthesize ActiveCapital,cdp,nh,nl,ah,al,dkflag,tbp,stoplost,leave,J_addr,J_hy,J_gxrq,J_start,J_zgb,J_zjhhy,J_oldjly;
@synthesize J_oldzysy,J_bg,J_hg,J_mgsy2,J_zzc,J_ldzc,J_gdzc,J_wxzc,J_cqtz,J_ldfz,J_cqfz,J_zbgjj,J_jzc,J_zysy,J_zyly;
@synthesize J_qtly,J_yyly,J_tzsy,J_btsy,J_yywsz,J_snsytz,J_lyze,J_shly,J_jly,J_wfply,J_tzmgjz,J_HalfYearFlag;

- (id) init
{
	self = [super init];
	
	return self;
}


- (void) dealloc
{
	
	[super dealloc];
}

@end

@implementation ImageRect
@synthesize origin,size;
-(id)initWithRect:(CGRect)_rect
{
	self = [super init];
	if(self != nil)
	{
		origin = _rect.origin;
		size = _rect.size;
	}
	return self;
}
-(CGRect)frame
{
	CGRect rect;
	rect.origin = self.origin;
	rect.size = self.size;
	return rect;
}
@end

