//
//  DataFxtComponent.h
//  tdxiphone
//
//  Created by 魏 文敏 on 09-12-30.
//  Copyright 2009 武汉. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <QuartzCore/QuartzCore.h>
#import "SinHqInfo.h"
#import "struct.h"
#import "macro.h"
#import "EGetData.h"
#import "CrossView.h"
#import "Delegate.h"
#import "CalcZb.h"
#import "DataFxtDrawView.h"
#import "EUBase.h"
#import "DataFxtDetailComponent.h"

#define FXT_LEFT 0
#define FXT_RIGHT 1
#define RELEASE(object) if(object != nil) {[object release];object=nil;}
#define MAXPRICE_TAG 23
#define MINPRICE_TAG 24
@protocol DataFXTDelegate;

@interface DataFxtComponent : EUBase 
{
	DataFxtDrawView * drawView;
	BOOL  dataFlag;
	BOOL  moveFlag;
	BOOL  freshFlag;
	BOOL  changeZb;
	
	id <gpDetailDelegate> detailDelegate;
	
	short m_nShowStyle;
	short m_nOffset;
	short m_nDirection;
	short m_nStartPosX;
	short m_nStartPosY;
	short m_nLeftPos;
	short isZoom;
	short m_originPos;
	short nIndeZb;
	short m_nZoomfreshConunt;
	
	float viewWidth;
	float viewHeight;
	float perSecHeight;
	float perSecWidth;
	float drawWidth;
	
	CrossView  * fxtCross;
	DataFxtDetailComponent * detailView;

    
	SinHqInfo * currInfo;
	NSMutableArray  * m_AnalyseData;
	NSMutableArray  * m_ZbData;
	NSMutableArray * periodArray ;
	NSMutableArray * zbArray;
	NSMutableArray * drawNumArray;
	NSMutableArray * axisArray;
	NSMutableArray * positionArray;
	int periodIndex;
	int zbIndex;
	int drawIndex;
	int m_DrawNum;
	int m_LeftNum;
	int m_ReadNum;
	int m_PerReadNum;
	int cursor;
	
	float dPer;
	float m_dWidth;
	float m_dDistance;
	
	float m_MaxPrice;
	float m_MinPrice;
	int m_MaxVol;
	float m_MaxZb;
	float m_MinZb;
	float m_PricePerUnit;
	float m_PricePerUnitZB;
	float m_fPerUnitHeight;

    
	int m_MaxIndex;
	int m_MinIndex;
	
	float fVolUnit;
	NSTextField * nameField;

    
	NSMutableArray * titleArray;

    
	NSTextField * pMA5;
	NSTextField * pMA10;
	NSTextField * pMA20;

    
	NSTextField * zb1;
	NSTextField * zb2;
	NSTextField * zb3;
	NSTextField * zb4;
	NSTextField * vol1;
	NSTextField * vol2;
	NSTextField * vol3;

    
	CGContextRef m_context;
	
	CGRect kLineRect;
	CGRect volRect;
	CGRect zbRect;
	CGRect InfoRect;
	
	NSRect leftDetailRect;
	NSRect rightDetailRect;
	short pickIndex;
	short nSelectIndex;
	CalcZb* myCalcZb;
	
	id <DataFXTDelegate> myDelegate;

	
	float titleHeight;
	float dateHeight;
	float btnHeight;
	float titleFont;
	float btnFont;
	
	float oriAmount;
	float oriVol;
	float originalDistance;
	
	CGAffineTransform originalTransform;
	BOOL aniFlag;
	
	int theOffset;
	
	BOOL isAllData;
	
	id<actionDelegate> myActionDelegate;
	
	
	NSPopUpButton * zqButton;
	NSPopUpButton * zbButton;
	NSPopUpButton * fqButton;
	
	BOOL moreFxtFlag;
	int fqFlag;
}
@property int fqFlag;
@property BOOL  dataFlag;
@property BOOL  moveFlag;
@property BOOL  moreFxtFlag;
@property BOOL isAllData;
@property float viewWidth;
@property float viewHeight;
@property float perSecHeight;
@property float perSecWidth;

@property (nonatomic,retain)CalcZb* myCalcZb;
@property (nonatomic , retain) CrossView  * fxtCross;
@property (nonatomic , retain) SinHqInfo * currInfo;
@property (nonatomic , retain) NSMutableArray  * m_AnalyseData;
@property (nonatomic , retain) NSMutableArray  * m_ZbData;
@property (nonatomic , retain) NSMutableArray * periodArray ;
@property (nonatomic , retain) NSMutableArray * zbArray;
@property (nonatomic , retain) NSMutableArray * drawNumArray;
@property (nonatomic , retain) NSMutableArray * axisArray;
@property (nonatomic , retain) NSMutableArray * positionArray;


@property int periodIndex;
@property int zbIndex;
@property int drawIndex;
@property int m_DrawNum;
@property int m_LeftNum;
@property int m_ReadNum;
@property int m_PerReadNum;
@property int cursor;
@property float dPer;
@property float m_dWidth;
@property float m_dDistance;
@property float m_MaxPrice;
@property float m_MinPrice;
@property int m_MaxVol;
@property float m_MaxZb;
@property float m_MinZb;
@property float m_PricePerUnit;
@property float m_fPerUnitHeight;
@property int m_MaxIndex;
@property int m_MinIndex;
@property(nonatomic, assign) id <DataFXTDelegate> myDelegate;
@property(nonatomic, assign) id <gpDetailDelegate> detailDelegate;
@property(nonatomic,assign) id<actionDelegate> myActionDelegate;

@property CGRect kLineRect;
@property CGRect volRect;
@property CGRect zbRect;
@property CGRect InfoRect;

@property float titleHeight;
@property float dateHeight;
@property float btnHeight;
@property float titleFont;
@property float btnFont;

@property int theOffset;
@property  short m_nZoomfreshConunt;

- (id)initWithFrame:(NSRect)aRect theData:(EGetData *)_eGetData titleHeight:(float)_titleHeight dateHeight:(float)_dateHeight btnHeight:(float)_btnHeight titleFont:(float)_titleFont btnFont:(float)_btnFont;
-(void) setFrame:(NSRect)aRect;
- (void)layoutLabel;

- (void)periodClickAction:(id)sender;
- (void)zbClickAction:(id)sender;

-(void) setShowStyle:(short)_showStyle;
-(void)showAnalyse:(NSMutableArray *)m_RecAnalyseData currInfo:(SinHqInfo *)_currInfo;
-(void)prepareData;
-(void)calMA;
-(void)calZB;
-(void)calIt;
-(void)calVol;
-(float)getYPos:(float)_value secNum:(int)secNum;
-(float)getZBYPos:(float)_value secNum:(int)secNum;
-(void) drawKLine:(CGContextRef)context;
-(void) drawZb:(CGContextRef)context;
-(void)drawVol:(CGContextRef)context;
-(void) drawCaption;
-(void) drawAxis;
-(void) calData;
-(void)calDataEx;
-(void) calDataZoom;
-(void)changeZb:(NSInteger)buttonIndex;
-(void) updateKLine:(NSMutableArray *)m_RecAnalyseData;
-(BOOL)refreshAnalyse:(SinHqInfo *) _currInfo nowDate:(int)_nowDate nowHour:(int)_nowHour nowMinute:(int)_nowMinute;
-(int) getTodayCursor:(int)ymd nowMinute:(int)_nowMinute;
-(CGFloat) distanceBetweenTwoPoints:(CGPoint)fromPoint toPoint:(CGPoint)toPoint ;
-(void)showFxtDetail;
-(void)hideFxtDetail;
@end

@protocol DataFXTDelegate <NSObject>

- (void)changeFXTPara;
- (void)getMoreFXTData;
@end
