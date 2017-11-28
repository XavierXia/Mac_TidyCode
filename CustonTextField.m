//
//  CustonTextField.m
//  tdxMac
//
//  Created by tdx on 11-11-2.
//  Copyright 2011 武汉. All rights reserved.
//

#import "CustonTextField.h"


@implementation CustonTextField
@synthesize focusDelegate;

- (id)initWithFrame:(NSRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
    }
    return self;
}

- (void)drawRect:(NSRect)dirtyRect {
	[super drawRect:dirtyRect];
}

-(BOOL) becomeFirstResponder{
	[focusDelegate getFocus:[self tag]];
	return [super becomeFirstResponder];
}

-(void) keyUp:(NSEvent *)theEvent{
	switch ([theEvent keyCode]) {
		case MAC_KEY_ENTER:
        case MAC_SKEY_ENTER:
			[focusDelegate getEnter:[self tag]];
			break;
		case MAC_KEY_ESC:
			[focusDelegate getEsc:[self tag]];
			break;
	
		default:
			break;
	}
}

@end
