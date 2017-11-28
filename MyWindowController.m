//
//  MyWindowController.m
//  tdxMac
//
//  Created by tdx on 11-8-16.
//  Copyright 2011 武汉. All rights reserved.
//

#import "MyWindowController.h"


@implementation MyWindowController
@synthesize mainGetdata,mainView,showDelegate;


-(id)initWithMyWindow:(NSWindow *)window eGetData:(EGetData *)_eGetData{
	if ((self = [super initWithWindow:window])) {
		[[self window] setDelegate:self];
		mainGetdata = _eGetData;
		fullScreenFlag = NO;
        
		[self initPara];
        
	}
		
	return self;
}

-(void)initPara{
	
	NSRect winFrame = [[self window] frame];
	winFrame.origin.x=0;
	winFrame.origin.y=0;
	winFrame.size.width = 1024;
	winFrame.size.height = 680;
    
	mainView = [[EUMainView alloc] initWithData:winFrame theData:mainGetdata];
	mainView.controllerDelegate = self;
    
	[[self window] setContentView:mainView];
	
	[[self window] setAcceptsMouseMovedEvents:YES];
    
}

-(void) windowDidResize:(NSNotification *)notification{
		[mainView OnScreenSizeChange:[[self window] frame].size.width theHeight:[[self window] frame].size.height-20.0f];
}

-(void) windowDidEndLiveResize:(NSNotification *)notification{
}

-(void) windowWillClose:(NSNotification *)notification{
	if (mainGetdata.tradeLoginFlag) {
		[mainView closeButtonClick];
	}
	[showDelegate closeApp];
}

-(void)dealFullScreen{
	if (fullScreenFlag) {
		fullScreenFlag = NO;
		[mainView exitFullScreenModeWithOptions:nil];
		[mainView OnScreenSizeChange:[[self window] frame].size.width theHeight:[[self window] frame].size.height-20.0f];

	}
	else {
		fullScreenFlag = YES;
		[mainView enterFullScreenMode:[NSScreen mainScreen] withOptions:nil];
		[mainView OnScreenSizeChange:[[NSScreen mainScreen] frame].size.width theHeight:[[NSScreen mainScreen] frame].size.height];
	}

	[[self window] makeFirstResponder:mainView];
	

}

-(BOOL)getFullScreenFlag{
	return fullScreenFlag;
}

-(void) dealloc{
	[super dealloc];
	[mainView release];
	[mainGetdata release];
}

-(void) mouseDown:(NSEvent *)theEvent{
    
}

- (void)mouseMoved:(NSEvent *)theEvent
{
    [mainGetdata jyhasoper];
}
@end
