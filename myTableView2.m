//
//  CustonTableView.m
//  tdxMac
//
//  Created by tdx on 11-12-5.
//  Copyright 2011 武汉. All rights reserved.
//

#import "myTableView2.h"

#define WT_WIDTH 230
#define PERROWHEIGHT_PK 22

@implementation myTableView2


- (id)initWithFrame:(NSRect)frame {
    self = [super initWithFrame:frame];
    if (self) {

    }
    return self;
}

- (id)_highlightColorForCell:(id)cell
{
    if([self selectionHighlightStyle] == 1)
    {
        return nil;
    }
    else
    {
        return [NSColor colorWithCalibratedRed:187/255.0f green:187/255.0f blue:187/255.0f alpha:1.0f];
    }
}

- (void)drawRect:(NSRect)dirtyRect {
    // Drawing code here.
    [super drawRect:dirtyRect];
}
@end
