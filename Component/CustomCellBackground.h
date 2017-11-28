//
//  CustomCellBackground.h
//  CoolTable
//
//  Created by Ray Wenderlich on 9/29/10.
//  Copyright 2010 Ray Wenderlich. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <QuartzCore/QuartzCore.h>

@interface CustomCellBackground : NSView {

	BOOL  bcoloryzm;
	BOOL  bshowyzm;
	NSString	 *m_yzmstr;
}
@property(nonatomic) BOOL bcoloryzm;
@property(nonatomic) BOOL bshowyzm;

-(void)GenYzm;
-(void)DrawYzm:(CGContextRef)context withrect:(CGRect)rect;
-(void)DrawNumber:(CGContextRef)context withrect:(CGRect)rect withnumber:(int)flag;
-(void) GetYzmOffset:(int *)nRetX :(int*)nRetY :(int)nX :(int)nY;
-(BOOL)IsValidYzm:(NSString *)inputyzm;
-(void)drawMhdot:(CGContextRef)context withrect:(CGRect)rect;
@end
