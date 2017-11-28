//
//  Common.m
//  CoolTable
//
//  Created by Ray Wenderlich on 9/29/10.
//  Copyright 2010 Ray Wenderlich. All rights reserved.
//

#import "Commondraw.h"

CGRect rectFor1PxStroke(CGRect rect) {
    return CGRectMake(rect.origin.x + 0.5, rect.origin.y + 0.5, rect.size.width - 1, rect.size.height - 1);
}
CGColorRef CGColorCreateDeviceRGBFromNSColor (NSColor * color){
	NSColor * deviceColor = [color colorUsingColorSpaceName:NSDeviceRGBColorSpace];
	CGFloat componenets[4];
	[deviceColor getRed:&componenets[0] green:&componenets[1] blue:&componenets[2] alpha:&componenets[3]];
	
	return CGColorCreate(CGColorSpaceCreateDeviceRGB(),componenets);
	
}


void drawLinearGradient(CGContextRef context, CGRect rect, CGColorRef startColor, CGColorRef  endColor) {
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    CGFloat locations[] = { 0.0, 1.0 };
    
    NSArray *colors = [NSArray arrayWithObjects:(id)startColor, (id)endColor, nil];
    
    CGGradientRef gradient = CGGradientCreateWithColors(colorSpace, (CFArrayRef) colors, locations);
    
    CGPoint startPoint = CGPointMake(CGRectGetMidX(rect), CGRectGetMinY(rect));
    CGPoint endPoint = CGPointMake(CGRectGetMidX(rect), CGRectGetMaxY(rect));
    
    CGContextSaveGState(context);
    CGContextAddRect(context, rect);
    CGContextClip(context);
    CGContextDrawLinearGradient(context, gradient, startPoint, endPoint, 0);
    CGContextRestoreGState(context);
    
    CGGradientRelease(gradient);
    CGColorSpaceRelease(colorSpace);
}

void draw1PxStroke(CGContextRef context, CGPoint startPoint, CGPoint endPoint, CGColorRef color) {
    
    CGContextSaveGState(context);
    CGContextSetLineCap(context, kCGLineCapSquare);
    CGContextSetStrokeColorWithColor(context, color);
    CGContextSetLineWidth(context, 1.0);
    CGContextMoveToPoint(context, startPoint.x + 0.5, startPoint.y + 0.5);
    CGContextAddLineToPoint(context, endPoint.x + 0.5, endPoint.y + 0.5);
    CGContextStrokePath(context);
    CGContextRestoreGState(context);        
    
}

// MyCreateBitmapContext: Source based on Apple Sample Code
CGContextRef MyCreateBitmapContext (int pixelsWide, int pixelsHigh)
{
    CGContextRef    context = NULL;
    CGColorSpaceRef colorSpace;
    void *          bitmapData;
    int             bitmapByteCount;
    int             bitmapBytesPerRow;
	
    bitmapBytesPerRow   = (pixelsWide * 4);
    bitmapByteCount     = (bitmapBytesPerRow * pixelsHigh);
	
    colorSpace = CGColorSpaceCreateDeviceRGB();
    bitmapData = malloc( bitmapByteCount );
    if (bitmapData == NULL)
    {
        fprintf (stderr, "Memory not allocated!");
        return NULL;
    }
    context = CGBitmapContextCreate (bitmapData,
									 pixelsWide,
									 pixelsHigh,
									 8,
									 bitmapBytesPerRow,
									 colorSpace,
									 kCGImageAlphaPremultipliedLast);
    if (context== NULL)
    {
        free (bitmapData);
        fprintf (stderr, "Context not created!");
        return NULL;
    }
    CGColorSpaceRelease( colorSpace );
	
    return context;
}

id createImage(float percentage,BOOL bsflag)
{
	CGRect aRect = CGRectMake(0.0f, 0.0f, 36.0f, 36.0f);
	CGContextRef context = MyCreateBitmapContext(36, 36);
	CGContextClearRect(context, aRect);
	
	CGContextSetFillColorWithColor(context, CGColorCreateDeviceRGBFromNSColor([NSColor lightGrayColor]) );
	CGContextFillEllipseInRect(context, aRect);
	
	CGContextSetFillColorWithColor(context, CGColorCreateDeviceRGBFromNSColor([NSColor colorWithDeviceRed:(bsflag?percentage:0.0f) green:(bsflag?0.0f:percentage) blue:0.5F alpha:0.5f] ));
	CGContextFillEllipseInRect(context, CGRectInset(aRect, 4.0f, 4.0f));
	
	CGContextSetFillColorWithColor(context, CGColorCreateDeviceRGBFromNSColor([NSColor whiteColor]));
	CGContextSelectFont(context, "Georgia", ((percentage==1.0f)?11.0f:14.0f), kCGEncodingMacRoman);
	CGContextSetTextDrawingMode(context, kCGTextFill);
	CGContextSetShouldAntialias(context, true);
	NSString *outString = [NSString stringWithFormat:@"%2.0f%%", percentage*100];
	CGContextShowTextAtPoint(context, 5, 15, [outString UTF8String], [outString length]);
	
	CGImageRef myRef = CGBitmapContextCreateImage (context);
	free(CGBitmapContextGetData(context));
	CGContextRelease(context);
	
	return [[NSImage alloc] initWithCGImage:myRef size:NSMakeSize(36.0f, 36.0f)];

}

