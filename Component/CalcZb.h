//
//  CalcZb.h
//  tdxiphone
//
//  Created by tdx on 11-4-15.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "macro.h"
#define FCACHENUM 300
@interface Analyse_Unit1 : NSObject {
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

@end
@interface CalcZb : NSObject
{
	short m_nDataNum;
}
@property short m_nDataNum;//
-(id) init;
-(short) GetMeanlessNum:(float*)fpData DataNum:(short)nDataNum;
-(short)GetMeanlessNum1:(NSArray*)fpData DataNum:(short)nDataNum;
-(void) SUM:(NSMutableArray*)fOUT In:(NSMutableArray*)INa Parama:(short)_para;
-(void) REF:(NSMutableArray*)fOUT In:(NSMutableArray*)INa Parama:(short)_para;
-(void) HHV:(NSMutableArray*)fOUT In:(NSMutableArray*)INa Parama:(short)_para;
-(void) LLV:(NSMutableArray*)fOUT In:(NSMutableArray*)INa Parama:(short)_para;
-(void)AVEDEV:(NSMutableArray *)fOUT In:(NSMutableArray *)INa Parama:(short)_para;
-(void)COUNT:(NSMutableArray *)fOUT In:(NSMutableArray *)INa Parama:(short)_para;
-(void) SMA:(NSMutableArray*)buffer In:(short)n Parama:(short)_para;
-(void) QLMEMA:(NSMutableArray*)buffer In:(short)n Parama:(short)_para;
-(void)	EXPMA:(NSMutableArray *)fOUT In:(NSMutableArray*)INa Parama:(short)_para;
-(void) EXPMEMA:(NSMutableArray*)buffer In:(short)n Parama:(short)_para;
-(void) EMA:(NSMutableArray*)buffer In:(short)n Parama:(short)_para;
-(void) SUB:(float*)buf1 Buf:(float*)buf2 N:(short)n Result:(float*)result;
-(void)LOW_HIGH:(NSMutableArray *)indatap Current:(short)current N:(short)n theLow:(float *)theLow theHigh:(float *)theHigh;
-(void) STD:(NSMutableArray*)fOUT In:(NSMutableArray*)fIN Parama:(short)_para;
-(void) Dma:(NSMutableArray*)fOUT In:(NSMutableArray*)INa Parama:(NSMutableArray*)INb;
-(void) SET_NULL:(float *)buf From:(short)from Num:(short)num;
@end
