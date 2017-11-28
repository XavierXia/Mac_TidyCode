//
//  MyTableView.m
//  tdxMac
//
//  Created by tdx on 11-9-6.
//  Copyright 2011 武汉. All rights reserved.
//

#import "MyTableView.h"


@implementation MyTableView

- (id)initWithFrame:(NSRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code here.
    }
    return self;
}

- (void)drawRect:(NSRect)dirtyRect {
    // Drawing code here.
}

-(BOOL) resignFirstResponder{
	return NO;
}

@end
