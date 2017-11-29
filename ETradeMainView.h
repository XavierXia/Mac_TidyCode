//
//  ETradeMainView.h
//  tdxMac
//
//  Created by tdx on 11-10-25.
//  Copyright 2011 武汉. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "EUBase.h"
#import "ETradeFuncListView.h"
#import "ETradeFuncBarView.h"
#import "ETradeBodyView.h"
#import "Delegate.h"
#import "LockScreen.h"
#import "NSReconnObject.h"
#import "DBPHZLockScreen.h"

@interface ETradeMainView : EUBase <NSAlertDelegate> {
	ETradeFuncListView * funcList;
	ETradeBodyView * bodyView;
	NSRect viewRect;
	
	NSTextField * titleText;
	
	NSButton * buyButton;
	NSButton * sellButton;
    NSButton * RZbuyButton;
    NSButton * RZsellButton;
	NSButton * cancelButton;
	NSButton * dealButton;
	NSButton * chicangButton;
	NSButton * refreshButton;
	NSButton * transferButton;
	NSButton * lockButton;
	NSButton * closeButton;
	NSButton * minButton;
    NSButton * changeSizeButton;
	int currIndex;
	
	id<TradeDelegate> tradeDelegate;
	
	LockScreen * m_lockscreen;
    DBPHZLockScreen * m_DBPHZlockscreen;
	//断线重连
	NSReconnObject *reconObject;
}

@property(nonatomic, assign) id<TradeDelegate> tradeDelegate;
@property (readwrite, retain) ETradeFuncListView * funcList;
@property (readwrite, retain) ETradeBodyView * bodyView;
@property (readwrite, retain) LockScreen * m_lockscreen;
@property (readwrite, retain) DBPHZLockScreen * m_DBPHZlockscreen;
@property (readwrite, retain) NSReconnObject *reconObject;

-(void) setFrame:(NSRect)frameRect;
-(void)dealTitleAndButton:(int)_type ParaOne:(int)_para;
-(void)resetAllButton;
-(void)handleResult:(NSAlert *)alert withResult:(NSInteger)result;
-(void)showlockscreen;
-(void)unlockscreen;
-(BOOL)DBPHZshowlockscreen;
-(void)DBPHZunlockscreen;
@end
