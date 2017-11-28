//
//  LoginWindowController.m
//  tdxMac
//
//  Created by tdx on 11-10-8.
//  Copyright 2011 武汉. All rights reserved.
//

#import "LoginWindowController.h"


@implementation LoginWindowController
@synthesize mainView,showDelegate;
-(id)initWithMyWindow:(NSWindow *)window eGetData:(EGetData *)_eGetData{
	if ((self = [super initWithWindow:window])) {
		[[self window] setDelegate:self];
		mainGetdata = _eGetData;
		[self initPara];
	}
	
	return self;
}

-(void)initPara{
	NSRect winFrame = [[self window] frame];
	winFrame.size.height = 320;
	mainView = [[EULogin alloc] initWithData:winFrame theData:mainGetdata];
	mainView.drawFlag  = NO;
	mainView.tradeindex=[mainGetdata.g_TradeComm.areceiver SetWinobjs:(id)mainView];

	[mainView setNeedsDisplay:YES];
	[[self window] setContentView:mainView];
	
	[[self window] setAcceptsMouseMovedEvents:YES];
	
	
	
	
}

-(void) windowWillClose:(NSNotification *)notification{
	NSLog(@"windowWillClose");
	mainView.bshowFlag = NO;
	
	[showDelegate closeSession];
}

@end
