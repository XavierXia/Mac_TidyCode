//
//  CustonTableView.m
//  tdxMac
//
//  Created by tdx on 11-12-5.
//  Copyright 2011 武汉. All rights reserved.
//

#import "CustonTableView.h"


@implementation CustonTableView
@synthesize clickDelegate;

- (id)initWithFrame:(NSRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code here.
    }
    return self;
}

- (void)drawRect:(NSRect)dirtyRect {
    // Drawing code here.
	[super drawRect:dirtyRect];
}

-(void) mouseDown:(NSEvent *)theEvent{
	//NSLog(@"table mousedown");
	[super mouseDown:theEvent];
	[self performSelector:@selector(test:) withObject:theEvent afterDelay:0.1f];
}
-(void) mouseUp:(NSEvent *)theEvent{
	[super mouseUp:theEvent];
}

-(void)test:(NSEvent *)theEvent{
	[clickDelegate getClick:theEvent];
}


@end
