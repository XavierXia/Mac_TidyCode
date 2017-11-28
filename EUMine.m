//
//  EUMine.m
//  ghzq_macosx
//
//  Created by tdx on 12-5-15.
//  Copyright 2012 武汉. All rights reserved.
//

#import "EUMine.h"


@implementation EUMine

- (id)initWithFrame:(NSRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code here.
    }
    return self;
}


- (id)initWithData:(NSRect)frame theData:(EGetData *)_eGetData{
	self = [super initWithData:frame theData:_eGetData];
	if (self) {
		viewRect = frame;
		
		NSRect textRect;
		textRect.origin.x  = 0;
		textRect.origin.y = 0;
		textRect.size.width = viewRect.size.width;
		textRect.size.height = viewRect.size.height ;
		textView = [[CustonTextView alloc] initWithFrame:textRect];
		[textView setEditable:NO];
		[textView setBackgroundColor:[NSColor blackColor]];
		[textView setFont:[NSFont systemFontOfSize:15.0f]];
		[textView setTextColor:HQCOLOR_F10TEXT];
		
		textView.focusDelegate = self;
		
	}
	
	return self;
}	

-(void) setFrame:(NSRect)frameRect{
	[super setFrame:frameRect];
	viewRect = frameRect;
	
	self.offset_X = frameRect.origin.x;
	self.offset_Y = frameRect.origin.y;
	
	NSRect textRect;
	textRect.origin.x  = 0;
	textRect.origin.y = 0;
	textRect.size.width = viewRect.size.width;
	textRect.size.height = viewRect.size.height;
	
	[textView setFrame:textRect];
}

-(void)getFocus:(int)_tag{}
-(void)getEnter:(int)_tag{}
-(void)getEsc:(int)_tag{}
-(void)getKeyUp:(NSEvent *)theEvent{}

- (void)drawRect:(NSRect)dirtyRect {
}

@end
