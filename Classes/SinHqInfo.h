//
//  SinHqInfo.h
//  tdxiphone
//
//  Created by 魏 文敏 on 09-12-30.
//  Copyright 2009 武汉. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface SinHqInfo : NSObject{
	int setcode;
	NSString * gpcode;
	NSString * gpname;
	float closeP;
	float openP;
	float maxP;
	float minP;
	float nowP;
	float volume;
	int nowVol;
	float amount;
	float inside;
	float outside;
	NSMutableArray * buyP;
	NSMutableArray * buyV;
	NSMutableArray * sellP;
	NSMutableArray * sellV;
	float zad;
	float zaf;
	float zef;
	BOOL zsflag;
	int  dataPre;
	
	float exchange;
	
	float	J_zgb;		//总股本
	float   ActiveCapital;      // 流通股本	
	float       J_jly;		//净利益
	float       J_jzc;		//股东权益(就是净资产)
	char	    J_HalfYearFlag;	//报告期
	short J_addr;//省份
	short J_hy; //行业
	float J_zsz;//总市值
	float J_syl;//市盈率
	float liangbi;//量比
}

@property int setcode;
@property (nonatomic , retain) NSString * gpcode;
@property (nonatomic , retain) NSString * gpname;
@property float exchange;
@property float closeP;
@property float openP;
@property float maxP;
@property float minP;
@property float nowP;
@property float volume;
@property int nowVol;
@property float amount;
@property float inside;
@property float outside;
@property float zad;
@property float zaf;
@property float zef;
@property BOOL zsflag;
@property int  dataPre;

@property  float	J_zgb;		//总股本
@property float   ActiveCapital;      // 流通股本	
@property float       J_jly;		//净利益
@property float       J_jzc;		//股东权益(就是净资产)
@property char	    J_HalfYearFlag;	//报告期
@property short J_addr;//省份
@property short J_hy; //行业
@property float J_zsz;//总市值
@property float J_syl;//市盈率
@property float liangbi;


@property (nonatomic , retain) NSMutableArray * buyP;
@property (nonatomic , retain) NSMutableArray * buyV;
@property (nonatomic , retain) NSMutableArray * sellP;
@property (nonatomic , retain) NSMutableArray * sellV;

-(id)initWithInfo:(SinHqInfo *)hqInfo;
-(SinHqInfo *)deepCopy;

@end
