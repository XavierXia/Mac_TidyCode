//
//  DataDetailComponent.m
//  tdxMac
//
//  Created by tdx on 11-9-17.
//  Copyright 2011 武汉. All rights reserved.
//

#import "DataDetailComponent.h"
#define PERROWHEIGHT 20

@implementation DataDetailComponent

- (id)initWithFrame:(NSRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
      	titleArray = [[NSMutableArray alloc] initWithObjects:@"时间",@"价位",@"均价",@"涨跌",@"涨幅",nil] ;
		
    }
    return self;
}

-(NSMutableDictionary *)getAttributes:(NSString *)_fontName fontSize:(CGFloat)_fontSize theColor:(NSColor *)_theColor theAliment:(int)_theAliment{
	NSMutableDictionary * attributes = [[NSMutableDictionary alloc] init] ;
	
	NSMutableParagraphStyle * tempStyle = [[NSMutableParagraphStyle alloc]init] ;
	[tempStyle setLineBreakMode:NSLineBreakByTruncatingTail];
	[tempStyle setAlignment:_theAliment];
	
	[attributes setObject:[NSFont systemFontOfSize:_fontSize] forKey:NSFontAttributeName];
	[attributes setObject:_theColor forKey:NSForegroundColorAttributeName];
	[attributes setObject:tempStyle forKey:NSParagraphStyleAttributeName];
	[tempStyle release];
	return [attributes autorelease];
}

- (void)drawRect:(NSRect)dirtyRect {
	[[NSColor blackColor] set];
	NSRectFill(dirtyRect);
	CGContextRef context = [[NSGraphicsContext currentContext] graphicsPort];
	CGContextSetAllowsAntialiasing(context, FALSE);
	[[NSColor redColor] set];
	CGContextSetLineWidth(context, 1.0f);
	
	if (zsflag) {
		CGContextAddRect(context, CGRectMake(dirtyRect.origin.x, dirtyRect.origin.y+2*PERROWHEIGHT,dirtyRect.size.width-1,dirtyRect.size.height-2*PERROWHEIGHT-1));
	}
	else {
		CGContextAddRect(context, CGRectMake(dirtyRect.origin.x, dirtyRect.origin.y,dirtyRect.size.width-1,dirtyRect.size.height-1));
	}

	CGContextStrokePath(context);
	
	CGContextSetAllowsAntialiasing(context, TRUE);
	
	
	NSString * tempString;
	NSRect tempRect;
	NSMutableDictionary * tempAttributes;
	int i;
	//标题
	tempAttributes = [self getAttributes:@"Arial" fontSize:12.0f theColor:[NSColor whiteColor] theAliment:NSLeftTextAlignment];
	
	for (i = 0 ; i<[titleArray count]; i++) {
		tempString = [titleArray objectAtIndex:i];
		
		tempRect.origin.x = 1;
		tempRect.origin.y = dirtyRect.size.height - PERROWHEIGHT-i*2*PERROWHEIGHT;
		tempRect.size.width = dirtyRect.size.width;
		tempRect.size.height = PERROWHEIGHT;
		
		[tempString drawInRect:tempRect withAttributes:tempAttributes];
	}
	
	if (zsflag) {
		tempString = @"成交额";
		
		tempRect.origin.x = 1;
		tempRect.origin.y = dirtyRect.size.height - PERROWHEIGHT-5*2*PERROWHEIGHT;
		tempRect.size.width = dirtyRect.size.width;
		tempRect.size.height = PERROWHEIGHT;
		
		[tempString drawInRect:tempRect withAttributes:tempAttributes];
	}
	else {
		tempString = @"成交量";
		
		tempRect.origin.x = 1;
		tempRect.origin.y = dirtyRect.size.height - PERROWHEIGHT-5*2*PERROWHEIGHT;
		tempRect.size.width = dirtyRect.size.width;
		tempRect.size.height = PERROWHEIGHT;
		
		[tempString drawInRect:tempRect withAttributes:tempAttributes];
		
		tempString = @"成交额";
		
		tempRect.origin.x = 1;
		tempRect.origin.y = dirtyRect.size.height - PERROWHEIGHT-6*2*PERROWHEIGHT;
		tempRect.size.width = dirtyRect.size.width;
		tempRect.size.height = PERROWHEIGHT;
		
		[tempString drawInRect:tempRect withAttributes:tempAttributes];
	}
	
	if (minuteInfo != nil) {
		tempAttributes = [self getAttributes:@"Arial" fontSize:12.0f theColor:[NSColor whiteColor] theAliment:NSRightTextAlignment];
		
		tempString = [self getTimeFromMinute:minuteInfo.minute];
		
		tempRect.origin.x = 1;
		tempRect.origin.y = dirtyRect.size.height - 2*PERROWHEIGHT-0*2*PERROWHEIGHT;
		tempRect.size.width = dirtyRect.size.width-3;
		tempRect.size.height = PERROWHEIGHT;
		
		[tempString drawInRect:tempRect withAttributes:tempAttributes];
		//均价
		if (minuteInfo.average > closep) {
			tempAttributes = [self getAttributes:@"Arial" fontSize:12.0f theColor:[NSColor redColor] theAliment:NSRightTextAlignment];
		}
		else if (minuteInfo.average < closep) {
			tempAttributes = [self getAttributes:@"Arial" fontSize:12.0f theColor:HQCOLOR_DOWN theAliment:NSRightTextAlignment];
		}
		else {
			tempAttributes = [self getAttributes:@"Arial" fontSize:12.0f theColor:[NSColor whiteColor] theAliment:NSRightTextAlignment];
		}
		
		if(dataPre== 2)
			tempString = [NSString stringWithFormat:@"%.2f",minuteInfo.average];
		else
			tempString = [NSString stringWithFormat:@"%.3f",minuteInfo.average];
		
		tempRect.origin.x = 1;
		tempRect.origin.y = dirtyRect.size.height - 2*PERROWHEIGHT-2*2*PERROWHEIGHT;
		tempRect.size.width = dirtyRect.size.width-3;
		tempRect.size.height = PERROWHEIGHT;
		
		[tempString drawInRect:tempRect withAttributes:tempAttributes];
		
		
		//价位
		if (minuteInfo.now > closep) {
			tempAttributes = [self getAttributes:@"Arial" fontSize:12.0f theColor:[NSColor redColor] theAliment:NSRightTextAlignment];
		}
		else if (minuteInfo.now < closep) {
			tempAttributes = [self getAttributes:@"Arial" fontSize:12.0f theColor:HQCOLOR_DOWN theAliment:NSRightTextAlignment];
		}
		else {
			tempAttributes = [self getAttributes:@"Arial" fontSize:12.0f theColor:[NSColor whiteColor] theAliment:NSRightTextAlignment];
		}

		if(dataPre == 2)
			tempString = [NSString stringWithFormat:@"%.2f",minuteInfo.now];
		else
			tempString = [NSString stringWithFormat:@"%.3f",minuteInfo.now];

		tempRect.origin.x = 1;
		tempRect.origin.y = dirtyRect.size.height - 2*PERROWHEIGHT-1*2*PERROWHEIGHT;
		tempRect.size.width = dirtyRect.size.width-3;
		tempRect.size.height = PERROWHEIGHT;
		
		[tempString drawInRect:tempRect withAttributes:tempAttributes];
		//涨跌
		if(dataPre == 2)
			tempString = [NSString stringWithFormat:@"%.2f",minuteInfo.now - closep];
		else
			tempString = [NSString stringWithFormat:@"%.3f",minuteInfo.now - closep];
		
		tempRect.origin.x = 1;
		tempRect.origin.y = dirtyRect.size.height - 2*PERROWHEIGHT-3*2*PERROWHEIGHT;
		tempRect.size.width = dirtyRect.size.width-3;
		tempRect.size.height = PERROWHEIGHT;
		
		[tempString drawInRect:tempRect withAttributes:tempAttributes];
		
		//涨幅
		if(dataPre == 2)
			tempString = [NSString stringWithFormat:@"%.2f",(minuteInfo.now - closep)*100/closep];
		else
			tempString = [NSString stringWithFormat:@"%.3f",(minuteInfo.now - closep)*100/closep];
		tempString = [tempString stringByAppendingString:@"%"];

		
		tempRect.origin.x = 1;
		tempRect.origin.y = dirtyRect.size.height - 2*PERROWHEIGHT-4*2*PERROWHEIGHT;
		tempRect.size.width = dirtyRect.size.width-3;
		tempRect.size.height = PERROWHEIGHT;
		
		[tempString drawInRect:tempRect withAttributes:tempAttributes];
		//成交量 成交额
		tempAttributes = [self getAttributes:@"Arial" fontSize:12.0f theColor:[NSColor yellowColor] theAliment:NSRightTextAlignment];
		
		if (zsflag) {
			tempString = [NSString stringWithFormat:@"%i万",minuteInfo.nowvol/100];
			
			
			tempRect.origin.x = 1;
			tempRect.origin.y = dirtyRect.size.height - 2*PERROWHEIGHT-5*2*PERROWHEIGHT;
			tempRect.size.width = dirtyRect.size.width-3;
			tempRect.size.height = PERROWHEIGHT;
			
			[tempString drawInRect:tempRect withAttributes:tempAttributes];
		}
		else {
			tempString = [NSString stringWithFormat:@"%i",minuteInfo.nowvol];
			
			
			tempRect.origin.x = 1;
			tempRect.origin.y = dirtyRect.size.height - 2*PERROWHEIGHT-5*2*PERROWHEIGHT;
			tempRect.size.width = dirtyRect.size.width-3;
			tempRect.size.height = PERROWHEIGHT;
			
			[tempString drawInRect:tempRect withAttributes:tempAttributes];
			
			
			float tempFloat = minuteInfo.now*minuteInfo.nowvol*100;
			if (tempFloat > 10000) {
				tempString = [NSString stringWithFormat:@"%.1f万",tempFloat/10000];
			}
			else
			{
				tempString = [NSString stringWithFormat:@"%.1f",tempFloat];
			}
			
			
			
			tempRect.origin.x = 1;
			tempRect.origin.y = dirtyRect.size.height - 2*PERROWHEIGHT-6*2*PERROWHEIGHT;
			tempRect.size.width = dirtyRect.size.width-3;
			tempRect.size.height = PERROWHEIGHT;
			
			[tempString drawInRect:tempRect withAttributes:tempAttributes];
		}

	}

}


-(void)showDetail:(Minute_Unit *)_minuteInfo zsFlag:(BOOL)_zsflag dataPre:(int)_datapre  closeP:(float)_closep{
	closep  = _closep;
	minuteInfo = _minuteInfo;
	zsflag = _zsflag;
	dataPre = _datapre;
	[self setNeedsDisplay:YES];
}


-(NSString *)getTimeFromMinute:(int)min{
	if (!(min%60)) {
		if (min/60 <10) {
			return [NSString stringWithFormat:@"0%i:00",min/60];
		}
		else {
			return [NSString stringWithFormat:@"%i:00",min/60];
		}
	}
	else if((min%60) > 0 && (min%60)<10){
		if (min/60 <10) {
			return [NSString stringWithFormat:@"0%i:0%i",min/60,min%60];
		}
		else {
			return [NSString stringWithFormat:@"%i:0%i",min/60,min%60];
		}
	}
	else {
		if (min/60 <10) {
			return [NSString stringWithFormat:@"0%i:%i",min/60,min%60];
		}
		else {
			return [NSString stringWithFormat:@"%i:%i",min/60,min%60];
		}
	}
}

-(void) rightMouseDown:(NSEvent *)theEvent{
}
-(void) dealloc{
	[super dealloc];
	[titleArray release];
}

@end
