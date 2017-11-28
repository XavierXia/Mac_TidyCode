//
//  CustonComboBox.m
//  tdxMac
//
//  Created by tdx on 11-11-2.
//  Copyright 2011 武汉. All rights reserved.
//

#import "CustonComboBox.h"


@implementation CustonComboBox
@synthesize focusDelegate;
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

-(BOOL) becomeFirstResponder{
	[focusDelegate getFocus:[self tag]];
	return [super becomeFirstResponder];
}

-(void) keyDown:(NSEvent *)theEvent{
	switch ([theEvent keyCode]) {
		case MAC_KEY_ENTER:
        case MAC_SKEY_ENTER:
			[focusDelegate getEnter:[self tag]];
			break;
		default:
			break;
	}
}

@end
