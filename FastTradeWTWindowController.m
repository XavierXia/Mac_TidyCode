//
//  FastTradeWTWindowController.m
//  tdxMac
//
//  Created by tdx on 11-11-26.
//  Copyright 2011 武汉. All rights reserved.
//

#import "FastTradeWTWindowController.h"


@implementation FastTradeWTWindowController
@synthesize fastWTView,showDelegate;
-(id)initWithMyWindow:(NSWindow *)window eGetData:(EGetData *)_eGetData{
	if ((self = [super initWithWindow:window])) {
		[[self window] setDelegate:self];
		mainGetdata = _eGetData;
			
		fastWTView = [[ETradeWTView alloc] initWithData:NSMakeRect(0, 0, 258, 215) theData:_eGetData showType:0];
		[fastWTView setFrame:NSZeroRect];
		
		
		[fastWTView setNeedsDisplay:YES];
		[[self window] setContentView:fastWTView];
		
		[[self window] setAcceptsMouseMovedEvents:YES];
	}
	
	return self;
}

-(void) windowWillClose:(NSNotification *)notification{
	NSLog(@"windowWillClose");
	
	[showDelegate closeFastWTSession];
}

@end
