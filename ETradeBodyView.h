//
//  ETradeBodyView.h
//  tdxMac
//
//  Created by tdx on 11-10-26.
//  Copyright 2011 武汉. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "Delegate.h"
#import "EUBase.h"
#import "ETradeWTView.h"
#import "ETradeUserInfoView.h"
#import "ETradeWTCancelView.h"
#import "ETradeBankView.h"
#import "ETradePasswordView.h"
@interface ETradeBodyView : EUBase<BodyDelegate> {
	ETradeWTView * wtView;
	ETradeUserInfoView * userInfo;
	ETradeWTCancelView * wtCancel;
	ETradeBankView * bankView;
	ETradePasswordView * passwordView;
	
	NSRect viewRect;
	int currFunc;
	BOOL  breadyhxxflag2;
	BOOL readYHXXFLag;
	
	int bakFunc;
	BOOL isFirstLogin;
    NSView *WelComeView;
}
@property int currFunc;
@property(nonatomic,retain) ETradeWTView * wtView;
@property(nonatomic,retain) ETradeUserInfoView * userInfo;
@property(nonatomic,retain) ETradeWTCancelView * wtCancel;
@property(nonatomic,retain) ETradeBankView * bankView;
@property(nonatomic,retain) ETradePasswordView * passwordView;

-(void) setFrame:(NSRect)frameRect;
-(void)dealTradeShow;
-(void)dealTradeProcess:(NSString *)_gpcode gpSetcode:(int)_setcode typeID:(int)_typeID pareOne:(int)_paraone paraTwo:(int)_paraTwo pareThree:(NSString *)_paraThree;
-(void)clearAllView;
-(BOOL)IsNeedQueryYhInfo;

-(void)doasyncsuc;
-(void)doasyncfail;
-(void)cleandata;
-(void)doyzzz;
-(void)getDBPHZ_GDDM;
@end
