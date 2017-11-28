//
//  CustonTextView.m
//  tdxMac
//
//  Created by tdx on 11-12-16.
//  Copyright 2011 武汉. All rights reserved.
//

#import "CustonTextView.h"


@implementation CustonTextView

@synthesize focusDelegate;

- (id)initWithFrame:(NSRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
 
    }
    return self;
}

- (void)drawRect:(NSRect)dirtyRect {
    // Drawing code here.
	[super drawRect:dirtyRect];
}

-(void) keyUp:(NSEvent *)theEvent{
	//NSLog(@"keyUp");
	[focusDelegate getKeyUp:theEvent];
}

-(void) setSelectedRanges:(NSArray *)ranges affinity:(NSSelectionAffinity)affinity stillSelecting:(BOOL)stillSelectingFlag{
	NSArray * oldRanges = [self selectedRanges];

	for(NSValue *v in oldRanges){
		NSRange oldRange = [v rangeValue];
		
		if (oldRange.length >0) {
			[[self layoutManager] removeTemporaryAttribute:NSForegroundColorAttributeName forCharacterRange:oldRange];
			[[self layoutManager] addTemporaryAttributes:[NSDictionary dictionaryWithObject:HQCOLOR_F10TEXT forKey:NSForegroundColorAttributeName] forCharacterRange:oldRange];
			
		}
	}
	
	for(NSValue *v in ranges){
		NSRange oldRange = [v rangeValue];
		
		if (oldRange.length >0) {
			[[self layoutManager] removeTemporaryAttribute:NSForegroundColorAttributeName forCharacterRange:oldRange];
			[[self layoutManager] addTemporaryAttributes:[NSDictionary dictionaryWithObject:[NSColor blueColor] forKey:NSForegroundColorAttributeName] forCharacterRange:oldRange];
		}
	}
	
	[super setSelectedRanges:ranges affinity:affinity stillSelecting:stillSelectingFlag];
}

@end
