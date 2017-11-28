//
//  EUBase.m
//  tdxMac
//
//  Created by tdx on 11-8-19.
//  Copyright 2011 武汉. All rights reserved.
//

#import "EUBase.h"


@implementation EUBase

@synthesize eGetData,windindex,operProcessDelegate,operZXGDelegate,drawFlag,tradeindex,gpcode,setcode,offset_X,offset_Y;

- (id)initWithFrame:(NSRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code here.
    }
    return self;
}

- (id)initWithData:(NSRect)frame theData:(EGetData *)_eGetData{
	self = [super initWithFrame:frame];
    if (self) {
        // Initialization code here.
		self.eGetData = _eGetData;
		self.drawFlag = YES;
		self.windindex = [eGetData.g_pEComm.areceiver SetWinobjs:self];
	}
    return self;
}

- (void)drawRect:(NSRect)dirtyRect {
    if (drawFlag) {
		[[NSColor blackColor] set];
		NSRectFill(dirtyRect);
	}
	

}	


-(BOOL) acceptsFirstResponder{
	return YES;
}

-(BOOL)resignFirstResponder{
	return YES;
}
-(BOOL) becomeFirstResponder{
	return YES;
}

-(void)OnScreenSizeChange:(float)_width theHeight:(float)_height{
}

-(void)OnReceiveData:(int)reqIndex FuncID:(int)_funcID HqResult:(HqResultData *)_hqResult{
	
}

-(void)OnReceiveKeyBoardEvent:(NSEvent *)theEvent{
	
}

-(void) keyDown:(NSEvent *)theEvent{
	[operProcessDelegate getKeyBoardEvent:theEvent];
}

-(BOOL)OnReceiveData:(int)reqIndex parser:(id)pParse{
	return YES;
}

-(void)dealKeyBoardEvent:(NSEvent *)theEvent{
	
}

-(void) dealloc{
	[eGetData release];
	[super dealloc];
}

@end
