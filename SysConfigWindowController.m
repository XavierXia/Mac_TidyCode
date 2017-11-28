//
//  SysConfigWindowController.m
//  tdxMac
//
//  Created by tdx on 11-12-17.
//  Copyright 2011 武汉. All rights reserved.
//

#import "SysConfigWindowController.h"


@implementation SysConfigWindowController

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
	winFrame.origin.x = 0;
	winFrame.origin.y=0;
	winFrame.size.height = winFrame.size.height -22;
	mainView = [[EUSysConfig alloc]initWithNibName:@"SystemConfig" bundle:nil eGetData:mainGetdata];
	
	[[self window] setContentView:[mainView view]];
	
}
@end
