//
//  iTableColumnHeaderCell.m
//  iTableColumnHeader
//
//  Created by Matt Gemmell on Thu Feb 05 2004.
//  <http://iratescotsman.com/>
//

#import "iTableColumnHeaderCell.h"


@implementation iTableColumnHeaderCell


- (id)initTextCell:(NSString *)text
{
    if (self = [super initTextCell:text]) {
		
        metalBg = [[NSImage imageNamed:@"titleBg.png"] retain];
        if (text == nil || [text isEqualToString:@""]) {
            [self setTitle:@" "];
        }
        [metalBg setFlipped:YES];
		
		sortTip = [[NSImage imageNamed:@"sortDown.png"] retain];
		[sortTip setFlipped:YES];
		
        attrs = [[NSMutableDictionary dictionaryWithDictionary:
                                        [[self attributedStringValue] 
                                                    attributesAtIndex:0 
                                                    effectiveRange:NULL]] 
                                                        mutableCopy];
        return self;
    }
    return nil;
}


- (void)dealloc
{
    [metalBg release];
	[sortTip release];
    [attrs release];
    [super dealloc];
}


- (void)drawWithFrame:(NSRect)inFrame inView:(NSView*)inView
{
    NSRect tempSrc = NSZeroRect;
    tempSrc.size = [metalBg size];
    tempSrc.origin.y = tempSrc.size.height - 1.0;
    tempSrc.size.height = 1.0;
    
    NSRect tempDst = inFrame;
    tempDst.origin.y = inFrame.size.height - 1.0;
    tempDst.size.height = 1.0;
    
    [metalBg drawInRect:tempDst 
               fromRect:tempSrc 
              operation:NSCompositeSourceOver 
               fraction:1.0];
    
    tempSrc.origin.y = 0.0;
    tempSrc.size.height = [metalBg size].height - 1.0;
    
    tempDst.origin.y = 1.0;
    tempDst.size.height = inFrame.size.height - 2.0;
    
    [metalBg drawInRect:tempDst 
               fromRect:tempSrc 
              operation:NSCompositeSourceOver 
               fraction:1.0];
    
	tempSrc.origin.x = inFrame.size.width - 5.0;
	tempSrc.origin.y = 0.0;
	tempSrc.size.width  = 5.0;
	tempSrc.size.height = inFrame.size.height;
	
	tempDst.origin.x = inFrame.size.width - 10.0;
	tempDst.origin.y = 0.0;
	tempDst.size.width  = 10.0;
	tempDst.size.height = inFrame.size.height;
	
	[sortTip drawInRect:tempDst 
               fromRect:tempSrc 
              operation:NSCompositeSourceOver 
               fraction:1.0];
	
    float offset = 0.5;
    [attrs setValue:[NSColor colorWithCalibratedWhite:1.0 alpha:0.7] 
             forKey:@"NSColor"];
    
    NSRect centeredRect = inFrame;
    centeredRect.size = [[self stringValue] sizeWithAttributes:attrs];
    centeredRect.origin.x += 
        ((inFrame.size.width - centeredRect.size.width) / 2.0) - offset;
    centeredRect.origin.y = 
        ((inFrame.size.height - centeredRect.size.height) / 2.0) + offset;
    [[self stringValue] drawInRect:centeredRect withAttributes:attrs];
    
 
}


- (id)copyWithZone:(NSZone *)zone
{
    id newCopy = [super copyWithZone:zone];
    [metalBg retain];
	[sortTip retain];
    [attrs retain];
    return newCopy;
}


@end
