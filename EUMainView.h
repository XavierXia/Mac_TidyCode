//
//  EUMainView.h
//  tdxMac
//
//  Created by tdx on 11-8-31.
//  Copyright 2011 武汉. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "EUBase.h"
#import "EUGrid.h"
#import "EUZst.h"
#import "EUFxt.h"
#import "EUBottom.h"
#import "EUKey.h"
#import "EUF10.h"
#import "StockArray.h"
#import "ETradeMainView.h"
#import "EUWebView.h"
#import "EUMine.h"
@interface EUMainView : EUBase <OperProcessDelegate,OperZXGDelegate,TradeDelegate,SystemMenuDelegate>{
	EUGrid * euGrid;
	EUZst * euZst;
	EUFxt * euFxt;
	EUBottom * euBottom;
	EUF10 * euF10;
	StockArray* stockArray;
	EUKey * euKey;
	EUWebView * webView;
	EUMine * euMine;
	
	ETradeMainView * tradeView;
	
	int currFunc;
	int bakFunc;
	EUBase * currView;
	
	BOOL keyShowFlag;
	BOOL tradeShowFlag;
    BOOL tradeChangeSizeShowFlag;
	BOOL fastWTShowFlag;
	BOOL mineShowFlag;
	NSTimer * searchStockTimer;
	NSString * searchString;
	
	BOOL reloadFlag;
	
	NSRect viewRect;
	
	id <showBodyDelegate> showDelegate;
	
	id controllerDelegate;
	
	NSTimer * initRefreshTimer;
}

@property (nonatomic,retain) EUWebView * webView;
@property(nonatomic, assign) id <showBodyDelegate> showDelegate;
@property (nonatomic,retain) EUGrid * euGrid;
@property (nonatomic,retain) EUZst * euZst;
@property (nonatomic,retain) EUFxt * euFxt;
@property (nonatomic,retain)  StockArray* stockArray;
@property (nonatomic,retain)  ETradeMainView * tradeView;
@property BOOL tradeShowFlag;
@property BOOL tradeChangeSizeShowFlag;
@property BOOL fastWTShowFlag;
@property(nonatomic, assign) id controllerDelegate;

-(void)clearAllView;
-(void)dealTradeViewShow;
-(void)dealResizeViewShow;
-(void)appendKey:(NSString *)_keyString;
-(void)delKey;
-(void)showKeyBoard;
-(void)dismissKeyboard;
-(void)checkTheSearch;
-(void)getTheRefreshData;
-(void)closeButtonClick2;
@end
