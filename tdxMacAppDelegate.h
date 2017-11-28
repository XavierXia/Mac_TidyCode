//
//  tdxMacAppDelegate.h
//  tdxMac
//
//  Created by tdx on 11-8-16.
//  Copyright 2011 武汉. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "MyWindowController.h"
#import "LoginWindowController.h"
#import "FastTradeWTWindowController.h"
#import "SysStatWindowController.h"
#import "SysConfigWindowController.h"
#import "EGetData.h"
#import "EComm.h"
#import "ETradeComm.h"
#import "Reachability.h"

@interface tdxMacAppDelegate : NSObject <NSApplicationDelegate,showBodyDelegate,NSAlertDelegate> {
	Reachability  *hostReach;
	NetworkStatus nowStatus;
	
	MyWindowController * myWindowsController;
	LoginWindowController * loginWindowsController;
	FastTradeWTWindowController * fastWTWindowsController;
	SysStatWindowController * sysStatWindowsController;
	SysConfigWindowController * sysConfigWindowsController;
    NSWindow *window;
	NSWindow *loginWin;
	NSWindow *fastWTWin;
	NSWindow *sysStatWin;
	NSWindow *sysConfigWin;
	
	EGetData * mainGetdata;
	EComm * g_pEComm;
	ETradeComm * g_TradeComm;
	
	NSModalSession modalSession;
	NSModalSession modalFastWTSession;
	
	NSPopUpButton * coltButton;
	NSMenu * coltMenu;
	NSPopUpButton * sortButton;
	NSMenu * sortMenu;
	
	NSMutableArray * serviceInfoArray;
}

@property (assign) IBOutlet NSWindow *window;

-(IBAction)sysConfig:(id)sender;
-(IBAction)sysPara:(id)sender;
-(void)initFuncMenu;
-(void)handleResult:(NSAlert *)alert withResult:(NSInteger)result;
@end
