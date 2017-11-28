//
//  SinHqInfo.m
//  tdxiphone
//
//  Created by 魏 文敏 on 09-12-30.
//  Copyright 2009 武汉. All rights reserved.
//

#import "SinHqInfo.h"


@implementation SinHqInfo

@synthesize setcode,gpcode,gpname,closeP,openP,maxP,minP,volume,nowVol,amount,inside,outside,zaf,buyP,buyV,sellP,sellV,zsflag,dataPre,nowP,zad;
@synthesize J_zgb,ActiveCapital,J_jly,J_jzc,J_HalfYearFlag,J_addr,J_hy,J_zsz,J_syl,zef,exchange,liangbi;


- (id) init
{
	self = [super init];
	if (self != nil) {
		setcode = -1;
		buyP = [[NSMutableArray alloc] init];
		buyV = [[NSMutableArray alloc] init];
		sellP = [[NSMutableArray alloc] init];
		sellV = [[NSMutableArray alloc] init];
	}
	return self;
}

-(id)initWithInfo:(SinHqInfo *)hqInfo{
	self = [super init];
	if (self != nil) {
		self.setcode = hqInfo.setcode;
		self.gpcode = hqInfo.gpcode;
		self.gpname = hqInfo.gpname;
		;
		self.closeP = hqInfo.closeP;
		self.openP = hqInfo.openP;
		self.maxP = hqInfo.maxP;
		self.minP = hqInfo.minP;
		self.nowP = hqInfo.nowP;
		self.volume = hqInfo.volume;
		self.nowVol = hqInfo.nowVol;
		self.amount = hqInfo.amount;
		self.inside = hqInfo.inside;
		self.outside = hqInfo.outside;
		self.liangbi = hqInfo.liangbi;
		buyP = [[NSMutableArray alloc] initWithArray:hqInfo.buyP];
		buyV = [[NSMutableArray alloc] initWithArray:hqInfo.buyV];
		sellP = [[NSMutableArray alloc] initWithArray:hqInfo.sellP];
		sellV = [[NSMutableArray alloc] initWithArray:hqInfo.sellV];
		self.zaf = hqInfo.zaf;
		self.zsflag = hqInfo.zsflag;
		self.dataPre = hqInfo.dataPre;
	}
	return self;
}

-(SinHqInfo *)deepCopy{
	SinHqInfo * newInfo = [[SinHqInfo alloc] init];
	
	newInfo.setcode = self.setcode;
	newInfo.gpcode = [NSString stringWithFormat:@"%@",self.gpcode];
	newInfo.gpname = [NSString stringWithFormat:@"%@",self.gpname];
	newInfo.closeP = self.closeP;
	newInfo.openP = self.openP;
	newInfo.maxP = self.maxP;
	newInfo.minP = self.minP;
	newInfo.nowP = self.nowP;
	newInfo.volume = self.volume;
	newInfo.nowVol = self.nowVol;
	newInfo.amount = self.amount;
	newInfo.inside = self.inside;
	newInfo.outside = self.outside;
	newInfo.liangbi = self.liangbi;
	int i;
	if ([self.buyP count]>0) {
		for (i=0; i<[self.buyP count]; i++) {
			[newInfo.buyP  addObject:[self.buyP objectAtIndex:i]];
		}
	}
	
	if ([self.sellP count]>0) {
		for (i=0; i<[self.sellP count]; i++) {
			[newInfo.sellP  addObject:[self.sellP objectAtIndex:i]];
		}
	}
	
	if ([self.buyV count]>0) {
		for (i=0; i<[self.buyV count]; i++) {
			[newInfo.buyV  addObject:[self.buyV objectAtIndex:i]];
		}
	}
	
	if ([self.sellV count]>0) {
		for (i=0; i<[self.sellV count]; i++) {
			[newInfo.sellV  addObject:[self.sellV objectAtIndex:i]];
		}
	}
	newInfo.zad = self.zad;
	newInfo.zaf = self.zaf;
	newInfo.zef = self.zef;
	newInfo.zsflag = self.zsflag;
	newInfo.dataPre = self.dataPre;
	newInfo.exchange = self.exchange;
	newInfo.J_zgb = self.J_zgb;		//总股本
	newInfo.ActiveCapital = self.ActiveCapital;      // 流通股本	
	newInfo.J_jly= self.J_jly;		//净利益
	newInfo.J_jzc= self.J_jzc;		//股东权益(就是净资产)
	newInfo.J_HalfYearFlag= self.J_HalfYearFlag;	//报告期
	newInfo.J_addr= self.J_addr;//省份
	newInfo.J_hy= self.J_hy; //行业
	newInfo.J_zsz= self.J_zsz;//总市值
	newInfo.J_syl= self.J_syl;//市盈率
	
	return newInfo;
}

-(void)releaseAllString {
	int i;
	if ([buyP count]>0) {
		for (i=0; i<[buyP count]; i++) {
			[[buyP objectAtIndex:i] release];
		}
	}
	
	if ([sellP count]>0) {
		for (i=0; i<[sellP count]; i++) {
			[[sellP objectAtIndex:i] release];
		}
	}
	
	if ([buyV count]>0) {
		for (i=0; i<[buyV count]; i++) {
			[[buyV objectAtIndex:i] release];
		}
	}
	
	if ([sellV count]>0) {
		for (i=0; i<[sellV count]; i++) {
			[[sellV objectAtIndex:i] release];
		}
	}
}

- (void) dealloc
{
	[gpcode release],gpcode=nil;
	[gpname release],gpname = nil;
	[buyP removeAllObjects];
	[sellP removeAllObjects];
	[buyV removeAllObjects];
	[sellV removeAllObjects];
	[buyP release],buyP = nil;
	[sellP release],sellP = nil;
	[buyV release],buyV = nil;
	[sellV release],sellV = nil;
	[super dealloc];
}


@end
