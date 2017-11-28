//
//  DataFxtDetailComponent.m
//  tdxMac
//
//  Created by tdx on 11-12-2.
//  Copyright 2011 武汉. All rights reserved.
//

#import "DataFxtDetailComponent.h"
#define PERROWHEIGHT 20
#define TITLEWIDTH 50

@implementation DataFxtDetailComponent
@synthesize analyseInfo;;
- (id)initWithFrame:(NSRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code here.
		titleArray = [[NSMutableArray alloc] initWithObjects:@"时间",@"开盘价",@"最高价",@"最低价",@"收盘价",@"成交量",@"成交额",@"涨跌",@"振幅",@"换手率",@"流通股",nil] ;
    }
    return self;
}

- (void)drawRect:(NSRect)dirtyRect {
  	[DETAILBACKCOLOR_GRAY set];
	NSRectFill(dirtyRect);
	if (analyseInfo == nil) {
		return;
	}
	
	NSString * tempString;
	float tempFloat;
	NSRect tempRect;
	NSMutableDictionary * tempAttributes;
	int i;
	//标题
	tempAttributes = [self getAttributes:@"Arial" fontSize:12.0f theColor:[NSColor whiteColor] theAliment:NSLeftTextAlignment];
	
	for (i = 0 ; i<[titleArray count]; i++) {
		tempString = [titleArray objectAtIndex:i];
		
		tempRect.origin.x = 1;
		tempRect.origin.y = dirtyRect.size.height - PERROWHEIGHT-i*PERROWHEIGHT;
		tempRect.size.width = TITLEWIDTH;
		tempRect.size.height = PERROWHEIGHT;
		
		[tempString drawInRect:tempRect withAttributes:tempAttributes];
	}
	
	int tempInt = 0;
	//时间
	tempAttributes = [self getAttributes:@"Arial" fontSize:12.0f theColor:[NSColor whiteColor] theAliment:NSRightTextAlignment];
	
	if (showType > 3) {
		tempString = [NSString stringWithFormat:@"%@",[self getDateFromMinute:analyseInfo.date theType:1]];
	}
	else {
		tempString =[NSString stringWithFormat:@"%@/%@",[self getDateFromMinute:analyseInfo.date theType:0],[self getTimeFromMinute:analyseInfo.time]];
	}
	
	tempRect.origin.x = TITLEWIDTH;
	tempRect.origin.y = dirtyRect.size.height - PERROWHEIGHT-tempInt*PERROWHEIGHT;
	tempRect.size.width = dirtyRect.size.width-TITLEWIDTH;
	tempRect.size.height = PERROWHEIGHT;
	
	[tempString drawInRect:tempRect withAttributes:tempAttributes];
	tempInt = tempInt +1;

	//@"开盘价",
	if (analyseInfo.openp > analyseInfoEx.closep) {
		tempAttributes = [self getAttributes:@"Arial" fontSize:12.0f theColor:[NSColor redColor] theAliment:NSRightTextAlignment];
	}
	else if (analyseInfo.openp < analyseInfoEx.closep) {
		tempAttributes = [self getAttributes:@"Arial" fontSize:12.0f theColor:HQCOLOR_DOWN theAliment:NSRightTextAlignment];
	}
	else {
		tempAttributes = [self getAttributes:@"Arial" fontSize:12.0f theColor:[NSColor whiteColor] theAliment:NSRightTextAlignment];
	}
	
	if(currInfo.dataPre == 2)
		tempString = [NSString stringWithFormat:@"%.2f",analyseInfo.openp];
	else
		tempString = [NSString stringWithFormat:@"%.3f",analyseInfo.openp];
	
	tempRect.origin.x = TITLEWIDTH;
	tempRect.origin.y = dirtyRect.size.height - PERROWHEIGHT-tempInt*PERROWHEIGHT;
	tempRect.size.width = dirtyRect.size.width-TITLEWIDTH;
	tempRect.size.height = PERROWHEIGHT;
	
	[tempString drawInRect:tempRect withAttributes:tempAttributes];
	tempInt = tempInt +1;
	
	//@"最高价",
	if (analyseInfo.highp > analyseInfoEx.closep) {
		tempAttributes = [self getAttributes:@"Arial" fontSize:12.0f theColor:[NSColor redColor] theAliment:NSRightTextAlignment];
	}
	else if (analyseInfo.highp < analyseInfoEx.closep) {
		tempAttributes = [self getAttributes:@"Arial" fontSize:12.0f theColor:HQCOLOR_DOWN theAliment:NSRightTextAlignment];
	}
	else {
		tempAttributes = [self getAttributes:@"Arial" fontSize:12.0f theColor:[NSColor whiteColor] theAliment:NSRightTextAlignment];
	}
	
	if(currInfo.dataPre == 2)
		tempString = [NSString stringWithFormat:@"%.2f",analyseInfo.highp];
	else
		tempString = [NSString stringWithFormat:@"%.3f",analyseInfo.highp];
	
	tempRect.origin.x = TITLEWIDTH;
	tempRect.origin.y = dirtyRect.size.height - PERROWHEIGHT-tempInt*PERROWHEIGHT;
	tempRect.size.width = dirtyRect.size.width-TITLEWIDTH;
	tempRect.size.height = PERROWHEIGHT;
	
	[tempString drawInRect:tempRect withAttributes:tempAttributes];
	tempInt = tempInt +1;
	//@"最低价",
	if (analyseInfo.lowp > analyseInfoEx.closep) {
		tempAttributes = [self getAttributes:@"Arial" fontSize:12.0f theColor:[NSColor redColor] theAliment:NSRightTextAlignment];
	}
	else if (analyseInfo.lowp < analyseInfoEx.closep) {
		tempAttributes = [self getAttributes:@"Arial" fontSize:12.0f theColor:HQCOLOR_DOWN theAliment:NSRightTextAlignment];
	}
	else {
		tempAttributes = [self getAttributes:@"Arial" fontSize:12.0f theColor:[NSColor whiteColor] theAliment:NSRightTextAlignment];
	}
	
	if(currInfo.dataPre == 2)
		tempString = [NSString stringWithFormat:@"%.2f",analyseInfo.lowp];
	else
		tempString = [NSString stringWithFormat:@"%.3f",analyseInfo.lowp];
	
	tempRect.origin.x = TITLEWIDTH;
	tempRect.origin.y = dirtyRect.size.height - PERROWHEIGHT-tempInt*PERROWHEIGHT;
	tempRect.size.width = dirtyRect.size.width-TITLEWIDTH;
	tempRect.size.height = PERROWHEIGHT;
	
	[tempString drawInRect:tempRect withAttributes:tempAttributes];
	tempInt = tempInt +1;
	//@"收盘价",
	if (analyseInfo.closep > analyseInfoEx.closep) {
		tempAttributes = [self getAttributes:@"Arial" fontSize:12.0f theColor:[NSColor redColor] theAliment:NSRightTextAlignment];
	}
	else if (analyseInfo.closep < analyseInfoEx.closep) {
		tempAttributes = [self getAttributes:@"Arial" fontSize:12.0f theColor:HQCOLOR_DOWN theAliment:NSRightTextAlignment];
	}
	else {
		tempAttributes = [self getAttributes:@"Arial" fontSize:12.0f theColor:[NSColor whiteColor] theAliment:NSRightTextAlignment];
	}
	
	if(currInfo.dataPre == 2)
		tempString = [NSString stringWithFormat:@"%.2f",analyseInfo.closep];
	else
		tempString = [NSString stringWithFormat:@"%.3f",analyseInfo.closep];
	
	tempRect.origin.x = TITLEWIDTH;
	tempRect.origin.y = dirtyRect.size.height - PERROWHEIGHT-tempInt*PERROWHEIGHT;
	tempRect.size.width = dirtyRect.size.width-TITLEWIDTH;
	tempRect.size.height = PERROWHEIGHT;
	
	[tempString drawInRect:tempRect withAttributes:tempAttributes];
	tempInt = tempInt +1;
	//@"成交量",
	tempAttributes = [self getAttributes:@"Arial" fontSize:12.0f theColor:[NSColor yellowColor] theAliment:NSRightTextAlignment];
	
	if (currInfo.zsflag) {
		tempFloat = analyseInfo.volumn;
	}
	else {
		tempFloat = analyseInfo.volumn / 100;
	}
	
	if(tempFloat > 100000){
		tempString = [NSString stringWithFormat:@"%.1f",tempFloat/10000];
		tempString = [tempString stringByAppendingString:@"万"];
	}	
	else {
		tempString = [NSString stringWithFormat:@"%.0f",tempFloat];
	}
	
	
	tempRect.origin.x = TITLEWIDTH;
	tempRect.origin.y = dirtyRect.size.height - PERROWHEIGHT-tempInt*PERROWHEIGHT;
	tempRect.size.width = dirtyRect.size.width-TITLEWIDTH;
	tempRect.size.height = PERROWHEIGHT;
	
	[tempString drawInRect:tempRect withAttributes:tempAttributes];
	tempInt = tempInt +1;
	
	//@"成交额",
	tempAttributes = [self getAttributes:@"Arial" fontSize:12.0f theColor:[NSColor whiteColor] theAliment:NSRightTextAlignment];
	
	
	if(analyseInfo.amount < 10000000){
		tempString = [NSString stringWithFormat:@"%.2f",analyseInfo.amount/100000000];
		tempString = [tempString stringByAppendingString:@"亿"];
	}	
	else {
		tempString = [NSString stringWithFormat:@"%.0f",analyseInfo.amount/10000];
		tempString = [tempString stringByAppendingString:@"万"];
	}
	
	tempRect.origin.x = TITLEWIDTH;
	tempRect.origin.y = dirtyRect.size.height - PERROWHEIGHT-tempInt*PERROWHEIGHT;
	tempRect.size.width = dirtyRect.size.width-TITLEWIDTH;
	tempRect.size.height = PERROWHEIGHT;
	
	[tempString drawInRect:tempRect withAttributes:tempAttributes];
	tempInt = tempInt +1;
	//@"涨跌",
	if (analyseInfo.closep > analyseInfoEx.closep) {
		tempAttributes = [self getAttributes:@"Arial" fontSize:12.0f theColor:[NSColor redColor] theAliment:NSRightTextAlignment];
	}
	else if(analyseInfo.closep < analyseInfoEx.closep) {
		tempAttributes = [self getAttributes:@"Arial" fontSize:12.0f theColor:HQCOLOR_DOWN theAliment:NSRightTextAlignment];
	}
	else {
		tempAttributes = [self getAttributes:@"Arial" fontSize:12.0f theColor:COLOR_GRID_COMMONCOLOR theAliment:NSRightTextAlignment];
	}
	NSString * tempStringEx;
	
	tempFloat = (analyseInfo.closep - analyseInfoEx.closep) *100 / analyseInfoEx.closep;
	
	if(currInfo.dataPre == 2)
		tempString = [NSString stringWithFormat:@"%.2f",tempFloat];
	else
		tempString = [NSString stringWithFormat:@"%.3f",tempFloat];
	
	tempString = [tempString stringByAppendingString:@"%"];
	
	
	
	if(currInfo.dataPre == 2)
		tempStringEx = [NSString stringWithFormat:@"%.2f",analyseInfo.closep - analyseInfoEx.closep];
	else
		tempStringEx = [NSString stringWithFormat:@"%.3f",analyseInfo.closep - analyseInfoEx.closep];
	
	
	
	tempRect.origin.x = TITLEWIDTH;
	tempRect.origin.y = dirtyRect.size.height - PERROWHEIGHT-tempInt*PERROWHEIGHT;
	tempRect.size.width = dirtyRect.size.width-TITLEWIDTH;
	tempRect.size.height = PERROWHEIGHT;
	
	[[NSString stringWithFormat:@"%@(%@)",tempStringEx,tempString] drawInRect:tempRect withAttributes:tempAttributes];
	tempInt = tempInt +1;
	
	//@"振幅",
	tempAttributes = [self getAttributes:@"Arial" fontSize:12.0f theColor:[NSColor whiteColor] theAliment:NSRightTextAlignment];
	
	tempFloat = (analyseInfo.highp - analyseInfo.lowp) *100 / analyseInfoEx.closep;
	
	if(currInfo.dataPre == 2)
		tempString = [NSString stringWithFormat:@"%.2f",tempFloat];
	else
		tempString = [NSString stringWithFormat:@"%.3f",tempFloat];
	
	tempString = [tempString stringByAppendingString:@"%"];
	
	
	
	if(currInfo.dataPre == 2)
		tempStringEx = [NSString stringWithFormat:@"%.2f",analyseInfo.highp - analyseInfo.lowp];
	else
		tempStringEx = [NSString stringWithFormat:@"%.3f",analyseInfo.highp - analyseInfo.lowp];
	
	tempRect.origin.x = TITLEWIDTH;
	tempRect.origin.y = dirtyRect.size.height - PERROWHEIGHT-tempInt*PERROWHEIGHT;
	tempRect.size.width = dirtyRect.size.width-TITLEWIDTH;
	tempRect.size.height = PERROWHEIGHT;
	
	[[NSString stringWithFormat:@"%@(%@)",tempStringEx,tempString] drawInRect:tempRect withAttributes:tempAttributes];
	tempInt = tempInt +1;
	if (currInfo.zsflag) {
		return;
	}
	//@"换手率",
	tempAttributes = [self getAttributes:@"Arial" fontSize:12.0f theColor:[NSColor whiteColor] theAliment:NSRightTextAlignment];
	
	tempFloat = analyseInfo.volumn *100.0f / (currInfo.ActiveCapital* 10000.0f);
	tempString = [NSString stringWithFormat:@"%.2f",tempFloat];
	tempString = [tempString stringByAppendingString:@"%"];
	
	tempRect.origin.x = TITLEWIDTH;
	tempRect.origin.y = dirtyRect.size.height - PERROWHEIGHT-tempInt*PERROWHEIGHT;
	tempRect.size.width = dirtyRect.size.width-TITLEWIDTH;
	tempRect.size.height = PERROWHEIGHT;
	
	[tempString drawInRect:tempRect withAttributes:tempAttributes];
	tempInt = tempInt +1;
	
	//@"流通股"
	tempAttributes = [self getAttributes:@"Arial" fontSize:12.0f theColor:[NSColor whiteColor] theAliment:NSRightTextAlignment];
	
	if (currInfo.ActiveCapital > 1000000) {
		tempString = [NSString stringWithFormat:@"%.0f亿",currInfo.ActiveCapital/10000];
	}
	else if ((currInfo.ActiveCapital < 1000000)&&(currInfo.ActiveCapital > 100000)){
		tempString = [NSString stringWithFormat:@"%.1f亿",currInfo.ActiveCapital/10000];
	}
	else if ((currInfo.ActiveCapital < 100000)&&(currInfo.ActiveCapital > 10000)){
		tempString = [NSString stringWithFormat:@"%.2f亿",currInfo.ActiveCapital/10000];
	}
	else {
		tempString = [NSString stringWithFormat:@"%.0f万",currInfo.ActiveCapital];
	}
	
	tempRect.origin.x = TITLEWIDTH;
	tempRect.origin.y = dirtyRect.size.height - PERROWHEIGHT-tempInt*PERROWHEIGHT;
	tempRect.size.width = dirtyRect.size.width-TITLEWIDTH;
	tempRect.size.height = PERROWHEIGHT;
	
	[tempString drawInRect:tempRect withAttributes:tempAttributes];
	tempInt = tempInt +1;
}


-(void)showDetail:(Analyse_Unit *)_analyseInfo  preInfo:(Analyse_Unit *)_analyseInfoEx{
	if (analyseInfo != nil) {
		[analyseInfo release],analyseInfo = nil;
	}
	
	if (analyseInfoEx != nil) {
		[analyseInfoEx release],analyseInfoEx = nil;
	}
	
	analyseInfo = [_analyseInfo analyseDeepCopy];
	analyseInfoEx = [_analyseInfoEx analyseDeepCopy];
	[self setNeedsDisplay:YES];
	
}

-(NSMutableDictionary *)getAttributes:(NSString *)_fontName fontSize:(CGFloat)_fontSize theColor:(NSColor *)_theColor theAliment:(int)_theAliment{
	NSMutableDictionary * attributes = [[NSMutableDictionary alloc] init] ;
	
	NSMutableParagraphStyle * tempStyle = [[[NSMutableParagraphStyle alloc]init] autorelease];
	[tempStyle setLineBreakMode:NSLineBreakByTruncatingTail];
	[tempStyle setAlignment:_theAliment];
	
	[attributes setObject:[NSFont systemFontOfSize:_fontSize] forKey:NSFontAttributeName];
	[attributes setObject:_theColor forKey:NSForegroundColorAttributeName];
	[attributes setObject:tempStyle forKey:NSParagraphStyleAttributeName];
	return [attributes autorelease];
}

-(void)setCurrInfo:(SinHqInfo *)_currInfo{
	if (currInfo != nil) {
		[currInfo release],currInfo=nil;
	}
	
	currInfo = [_currInfo deepCopy];
}
-(void)setShowType:(int)_showType{
	showType = _showType;
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

-(NSString *)getDateFromMinute:(int)date theType:(int)_type{
	if (date < 999999) {
		return @"-";
	}
	
	int tempInt;
	int yeah,month,day;
	
	yeah = date / 10000;
	
	tempInt = date % 10000;
	
	month = tempInt / 100;
	
	tempInt = tempInt % 100;
	
	day = tempInt;
	
	if (_type >0) {
		return [NSString stringWithFormat:@"%i/%i/%i",yeah,month,day];
	}
	else {
		return [NSString stringWithFormat:@"%i/%i",month,day];
	}

	
}


@end
