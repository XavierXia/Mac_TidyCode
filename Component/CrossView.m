//
//  CrossView.m
//  tdxiphone
//
//  Created by 魏 文敏 on 10-1-5.
//  Copyright 2010 武汉. All rights reserved.
//

#import "CrossView.h"
#define BLANKHEIGHT 40


#define DETAILBLANKHEIGHT 20
#define RIGHTBLANKHEIGHT 60
#define LEFTBLANKHEIGHT 60
#define BOTBLANK_HEIGHT 17

#define TITLE_HIGHT 15.0f
#define DATE_HIGHT 17.0f
#define FXT_WIDTH 270.0f
#define BTN_WIDTH 30.0f

@implementation CrossView

@synthesize xPos,yPos,showFlag,typeFlag,perRowHeight,viewWidth,topRect,midRect,btmRect,titleHeight;

- (id)initWithFrame:(NSRect)frame PerRowHeight:(float) _height{
    if (self = [super initWithFrame:frame]) {
        // Initialization code
		perRowHeight = _height;
		viewWidth = frame.size.width;
		showFlag = FALSE;
    }
    return self;
}

-(void) setFrame:(NSRect)aRect{
	[super setFrame:aRect];
	viewWidth = aRect.size.width;
	[self setNeedsDisplay:YES];
}


- (void)drawRect:(NSRect)rect {
	
	if(showFlag)
	{
		if(typeFlag == 1)
		{
			CGContextRef context = [[NSGraphicsContext currentContext] graphicsPort];
			[[NSColor whiteColor] set];
			CGContextSetLineWidth(context, 1.0);
			CGContextMoveToPoint(context, xPos, BOTBLANK_HEIGHT);
			CGContextAddLineToPoint(context, xPos, rect.size.height -titleHeight);
			
			CGContextMoveToPoint(context, LEFTBLANKHEIGHT, yPos);
			CGContextAddLineToPoint(context, rect.size.width-RIGHTBLANKHEIGHT, yPos);
			
			CGContextStrokePath(context);
		}	
		else if(typeFlag  == 2)
		{
			CGContextRef context = [[NSGraphicsContext currentContext] graphicsPort];		
			[[NSColor whiteColor] set];
			CGContextSetLineWidth(context, 0.8f);
			CGContextMoveToPoint(context, xPos, topRect.origin.y);
			CGContextAddLineToPoint(context, xPos, topRect.origin.y+topRect.size.height);
			CGContextMoveToPoint(context, xPos, midRect.origin.y);
			CGContextAddLineToPoint(context, xPos, midRect.origin.y+midRect.size.height-titleHeight);
			CGContextMoveToPoint(context, xPos, btmRect.origin.y);
			CGContextAddLineToPoint(context, xPos, btmRect.origin.y+midRect.size.height-titleHeight);
			CGContextMoveToPoint(context, topRect.origin.x, yPos);
			CGContextAddLineToPoint(context, topRect.origin.x+viewWidth-50, yPos);
			CGContextStrokePath(context);	
		}	
	}
}

-(void) rightMouseDown:(NSEvent *)theEvent{
	[[self superview] rightMouseDown:theEvent];
}

-(void) refreshShow{
	[self setNeedsDisplay:YES];
}




- (void)dealloc {
    [super dealloc];
}


@end
