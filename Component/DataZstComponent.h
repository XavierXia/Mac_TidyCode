//
//  DataZstComponent.h
//  tdxiphone
//
//  Created by 魏 文敏 on 09-12-30.
//  Copyright 2009 武汉. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SinHqInfo.h"
#import "struct.h"
#import "macro.h"
#import "CrossView.h"
#import "EGetData.h"
#import "Delegate.h"
#import "EUBase.h"
#import "DataDetailComponent.h"
#define PRICEAXISNUM 4;

@interface DataZstComponent : EUBase {
	BOOL  dataFlag;
	BOOL  moveFlag;
	float m_dMaxPrice,m_dMinPrice,m_dPriceStep;
	int m_dMaxVol;
	int m_lVolStep;
	int viewWidth;
	int viewHeight;
	float perSecHeight;
	float perSecWidth;
	SinHqInfo * currInfo;
	NSMutableArray  * m_MinuteData;
	NSMutableArray * hyTitleArray;
	NSMutableArray * timeTitleArray;
	CrossView  * zstCross;
	DataDetailComponent * detailComponent;
	id <gpDetailDelegate> detailDelegate;
	
	
	float titleHeight;
	float dateHeight;
	float titleFont;
	float btnFont;
	
	BOOL slideFlag;
	float m_nStartPosX;
	id<tradeSlideDelegate> myslideDelegate;
	id<MineDelegate> mineDelegate;
	
	
	BOOL haveMineFlag;
	BOOL detailShowFlag;
	int cursor;
	
}

@property(nonatomic, assign) id <gpDetailDelegate> detailDelegate;
@property(nonatomic,assign) id<tradeSlideDelegate> myslideDelegate;
@property(nonatomic,assign) id<MineDelegate> mineDelegate;
@property BOOL slideFlag;
@property BOOL  dataFlag;
@property BOOL  moveFlag;
@property float m_dMaxPrice;
@property float m_dMinPrice;
@property float m_dPriceStep;
@property int m_dMaxVol;
@property BOOL haveMineFlag;

@property(nonatomic,retain) SinHqInfo * currInfo;
@property(nonatomic,retain) NSMutableArray  * m_MinuteData;
@property(nonatomic,retain) NSMutableArray * hyTitleArray;
@property(nonatomic,retain) CrossView * zstCross;
@property int viewWidth;
@property int viewHeight;
@property float perSecHeight;
@property float perSecWidth;

- (id)initWithFrame:(NSRect)aRect theData:(EGetData *)_eGetData titleHeight:(float)_titleHeight  titleFont:(float)_titleFont btnFont:(float)_btnFont;
-(void) setFrame:(NSRect)aRect;
-(void)layoutLabel;
-(void)dismissDetailComponent;
-(void)showBase:(SinHqInfo *) hqInfo;
-(void)showCrossInfo:(float)xPos;
-(void)showCrossInfoWithCursor:(int)_cursor;
-(void)showzstDetail:(int)cursor;
-(void)showMinute:(NSMutableArray *) m_MinuteData currInfo:(SinHqInfo *) currInfo;
-(BOOL)refreshMinute:(SinHqInfo *) _currInfo nowHour:(int)_nowHour nowMinute:(int)_nowMinute ;
-(void) calIt;
-(float)getYFromValue:(float) value  pOrv:(int) pOrv;
-(NSString *)getTimeFromMinute:(int)min;

@end
