//
//  DataZstComponent.m
//  tdxiphone
//
//  Created by 魏 文敏 on 09-12-30.
//  Copyright 2009 武汉. All rights reserved.
//

#import "DataZstComponent.h"

#define SecWidthNum 8
#define SecHeightNum 15
#define BLANKHEIGHT 40
#define BOTBLANK_HEIGHT 17
#define LEFTBLANK_HEIGHT 60
#define RIGHTBLANK_HEIGHT 60
#define TEXTWIDTH 50

#define VOL_TITLE_TAG 1
#define TIME1_TITLE_TAG 2
#define TIME2_TITLE_TAG 3
#define TIME3_TITLE_TAG 4
#define TIME4_TITLE_TAG 7
#define TIME5_TITLE_TAG 8


#define AVE_TITLE_TAG 5
#define ZAF_TITLE_TAG 6
#define TIME_TITLE_TAG 9
#define NOW_TITLE_TAG 11


#define MAIN_FONT_SIZE 15

@implementation DataZstComponent
@synthesize viewWidth,viewHeight,perSecHeight,perSecWidth;;
@synthesize dataFlag,moveFlag,m_dMaxVol,m_dMinPrice,m_dMaxPrice,m_dPriceStep,currInfo,m_MinuteData,zstCross;
@synthesize hyTitleArray,detailDelegate,myslideDelegate,slideFlag,haveMineFlag,mineDelegate;

- (id)initWithFrame:(NSRect)aRect theData:(EGetData *)_eGetData titleHeight:(float)_titleHeight  titleFont:(float)_titleFont btnFont:(float)_btnFont{
	self = [super initWithData:aRect theData:_eGetData ];
	if(self != nil){
		self.dataFlag = NO;
		self.haveMineFlag = NO;
		slideFlag = NO;
		detailShowFlag = NO;
		
		titleHeight= _titleHeight;
		dateHeight = 17.0f;
		titleFont = _titleFont;
		btnFont = _btnFont;
		
		viewWidth = aRect.size.width;
		viewHeight = aRect.size.height;
		perSecHeight = (viewHeight - titleHeight-BOTBLANK_HEIGHT) / SecHeightNum;
		perSecWidth = (viewWidth - LEFTBLANK_HEIGHT-RIGHTBLANK_HEIGHT) / SecWidthNum;
		
		
		zstCross = [[CrossView alloc] initWithFrame:NSMakeRect(0, 0, aRect.size.width, aRect.size.height) PerRowHeight:perSecHeight];
		zstCross.typeFlag  = 1;
		zstCross.titleHeight = titleHeight;
		[self addSubview:zstCross];
		
		detailComponent = [[DataDetailComponent alloc]initWithFrame:NSMakeRect(0, viewHeight-280, LEFTBLANK_HEIGHT, 280)];
		
		[self layoutLabel];
		
		
		timeTitleArray = [[NSMutableArray alloc] initWithObjects:@"9:30",@"10:30",@"13:00",@"14:00",nil] ;
		
	}	
	
	return self;
}


- (void) dealloc
{
	[zstCross release];
	[currInfo release];
	[m_MinuteData release];
	[hyTitleArray release];
	[timeTitleArray release];
	[super dealloc];
}

-(void) setFrame:(NSRect)aRect{
	[super setFrame:aRect];
	
	viewWidth = aRect.size.width;
	viewHeight = aRect.size.height;
	perSecHeight = (viewHeight - titleHeight-BOTBLANK_HEIGHT) / SecHeightNum;
	perSecWidth = (viewWidth - LEFTBLANK_HEIGHT-RIGHTBLANK_HEIGHT) / SecWidthNum;
	
	[detailComponent setFrame:NSMakeRect(0, viewHeight-280, LEFTBLANK_HEIGHT, 280)];
	
	zstCross.perRowHeight = perSecHeight;
	zstCross.titleHeight = titleHeight;
	[zstCross setFrame:NSMakeRect(0, 0, aRect.size.width, aRect.size.height)];
	
	[[self viewWithTag:VOL_TITLE_TAG] setFrame:NSMakeRect(LEFTBLANK_HEIGHT, titleHeight+4*perSecHeight +1,TEXTWIDTH, titleHeight-2)];
	[[self viewWithTag:TIME1_TITLE_TAG] setFrame:NSMakeRect(LEFTBLANK_HEIGHT-20, titleHeight*2+perSecHeight*6+2 ,TEXTWIDTH, BOTBLANK_HEIGHT )];
	[[self viewWithTag:TIME2_TITLE_TAG] setFrame:NSMakeRect(LEFTBLANK_HEIGHT+perSecWidth*3.0f-30, titleHeight*2+perSecHeight*6+2 ,TEXTWIDTH, BOTBLANK_HEIGHT  )];
	[[self viewWithTag:TIME3_TITLE_TAG] setFrame:NSMakeRect(LEFTBLANK_HEIGHT+perSecWidth*6.0f-50, titleHeight*2+perSecHeight*6+2 ,TEXTWIDTH, BOTBLANK_HEIGHT  )];
	[[self viewWithTag:TIME4_TITLE_TAG] setFrame:NSMakeRect(LEFTBLANK_HEIGHT+perSecWidth*1.5f-30, titleHeight*2+perSecHeight*6+2 ,TEXTWIDTH, BOTBLANK_HEIGHT  )];
	[[self viewWithTag:TIME5_TITLE_TAG] setFrame:NSMakeRect(LEFTBLANK_HEIGHT+perSecWidth*4.5f-35, titleHeight*2+perSecHeight*6+2 ,TEXTWIDTH, BOTBLANK_HEIGHT  )];
	[self setNeedsDisplay:YES];
}

- (void)drawRect:(NSRect)rect {

	CGContextRef context = [[NSGraphicsContext currentContext] graphicsPort];
	CGContextSetAllowsAntialiasing(context, FALSE);
	[[NSColor colorWithCalibratedRed:190/255.0f green:0.0f blue:0.0f alpha:1.0f] set];
	CGContextSetLineWidth(context, 2.0f);
	CGContextMoveToPoint(context, LEFTBLANK_HEIGHT, BOTBLANK_HEIGHT+perSecHeight*SecHeightNum/3);
	CGContextAddLineToPoint(context, viewWidth- RIGHTBLANK_HEIGHT, BOTBLANK_HEIGHT+perSecHeight*SecHeightNum/3);
	CGContextStrokePath(context);
	
	CGContextSetLineWidth(context, 0.6f);
	
	CGContextAddRect(context, CGRectMake(LEFTBLANK_HEIGHT, BOTBLANK_HEIGHT, viewWidth-LEFTBLANK_HEIGHT-RIGHTBLANK_HEIGHT, viewHeight-BOTBLANK_HEIGHT-titleHeight));
	CGContextAddRect(context, CGRectMake(0, 0, viewWidth-1, viewHeight-1));
	CGContextMoveToPoint(context, 0, BOTBLANK_HEIGHT);
	CGContextAddLineToPoint(context, viewWidth-1, BOTBLANK_HEIGHT);
	int i ,j;

	for (i =1; i<SecWidthNum; i++) {
		CGContextMoveToPoint(context, LEFTBLANK_HEIGHT+i*perSecWidth, BOTBLANK_HEIGHT);
		CGContextAddLineToPoint(context, LEFTBLANK_HEIGHT+i*perSecWidth, viewHeight-titleHeight);
		CGContextStrokePath(context);
	}
	
	for (j =1; j<SecHeightNum; j++) {
		CGContextMoveToPoint(context, LEFTBLANK_HEIGHT, BOTBLANK_HEIGHT+perSecHeight*j);
		CGContextAddLineToPoint(context, viewWidth- RIGHTBLANK_HEIGHT, BOTBLANK_HEIGHT+perSecHeight*j);
		CGContextStrokePath(context);
	}

	
	CGContextStrokePath(context);
	if ([m_MinuteData count] < 1) {
		return;
	}
	CGContextSetAllowsAntialiasing(context, TRUE);
	if((dataFlag)&&([m_MinuteData count]>0))
	{
		
		//画现价
		[[NSColor whiteColor] set];
		CGContextSetLineWidth(context, 1.0);
		Minute_Unit * tempUnit ;
		float x0,y0,x1,y1;
		float pos;
		float tempFLoat = 240;
		pos = (self.viewWidth-LEFTBLANK_HEIGHT-RIGHTBLANK_HEIGHT)/tempFLoat;
		tempUnit = [m_MinuteData objectAtIndex:0];
		x0 = LEFTBLANK_HEIGHT + pos;
		y0 = [self getYFromValue:tempUnit.now pOrv:1];
		
		for (int i = 1; i < [m_MinuteData count]; i++) {
			tempUnit = [m_MinuteData objectAtIndex:i];
			x1 = LEFTBLANK_HEIGHT+pos*i;
			y1 = [self getYFromValue:tempUnit.now pOrv:1];
			
            if(isnan(x1) || isnan(y1))
                break;
			CGContextMoveToPoint(context, x0, y0);
			CGContextAddLineToPoint(context, x1, y1);
			CGContextStrokePath(context);
			
			x0 = x1;
			y0= y1;
		}
		
		//画均线
		[[NSColor yellowColor] set];
		CGContextSetLineWidth(context, 1.0);
		tempUnit = [m_MinuteData objectAtIndex:0];
		x0 = LEFTBLANK_HEIGHT + pos;
		y0 = [self getYFromValue:tempUnit.average pOrv:1];
		
		for (int i = 1; i < [m_MinuteData count]; i++) {
			tempUnit = [m_MinuteData objectAtIndex:i];
			x1 = LEFTBLANK_HEIGHT+pos*i;
			y1 = [self getYFromValue:tempUnit.average pOrv:1];
			if(isnan(x1) || isnan(y1))
                break;
			CGContextMoveToPoint(context, x0, y0);
            
			CGContextAddLineToPoint(context, x1, y1);
			CGContextStrokePath(context);
			
			x0 = x1;
			y0= y1;
		}
		
		//画成交量
	
		
		for (int i = 0; i < [m_MinuteData count]; i++) {
			tempUnit = [m_MinuteData objectAtIndex:i];
			x0 = LEFTBLANK_HEIGHT + pos*i;
			y0 = BOTBLANK_HEIGHT;
			x1 = LEFTBLANK_HEIGHT+pos*i;
			y1 = [self getYFromValue:tempUnit.nowvol pOrv:0];
			if(isnan(x1) || isnan(y1))
                break;
			CGContextMoveToPoint(context, x0, y0);
			CGContextAddLineToPoint(context, x1, y1);
			CGContextStrokePath(context);
		}
		
	}	
	
	NSString * tempString;
	NSRect tempRect;
	NSMutableDictionary * tempAttributes;
	tempAttributes = [eGetData getAttributes:@"Arial" fontSize:12.0f theColor:[NSColor redColor] theAliment:NSLeftTextAlignment];
	//画时间轴
	for (i = 0; i<[timeTitleArray count]; i++) {
		tempString = [timeTitleArray objectAtIndex:i];
		
		tempRect.origin.x = LEFTBLANK_HEIGHT+i*perSecWidth*2 - 20;
		tempRect.origin.y = 0;
		tempRect.size.width = 50;
		tempRect.size.height = BOTBLANK_HEIGHT;
		
		[tempString drawInRect:tempRect withAttributes:tempAttributes];
	}
	
	//画坐标轴
	//成交量坐标
	tempAttributes = [eGetData getAttributes:@"Arial" fontSize:12.0f theColor:[NSColor yellowColor] theAliment:NSRightTextAlignment];

    for (i = 1; i<SecHeightNum/3+1; i++) {
		int tempInt = m_lVolStep*i; 

		if(tempInt > 100000){
			tempString = [NSString stringWithFormat:@"%i",tempInt/10000];
			tempString = [tempString stringByAppendingString:@"万"];
		}	
		else
			tempString = [NSString stringWithFormat:@"%i",tempInt];
		
		
		tempRect.origin.x = 0;
		tempRect.origin.y = BOTBLANK_HEIGHT + i*perSecHeight-15;
		tempRect.size.width = LEFTBLANK_HEIGHT-2;
		tempRect.size.height = 25;
		
		[tempString drawInRect:tempRect withAttributes:tempAttributes];
		
	}
	
	tempAttributes = [eGetData getAttributes:@"Arial" fontSize:12.0f theColor:[NSColor yellowColor] theAliment:NSLeftTextAlignment];

    for (i = 1; i<SecHeightNum/3+1; i++) {
		int tempInt = m_lVolStep*i; 
		
		if(tempInt > 100000){
			tempString = [NSString stringWithFormat:@"%i",tempInt/10000];
			tempString = [tempString stringByAppendingString:@"万"];
		}	
		else
			tempString = [NSString stringWithFormat:@"%i",tempInt];
		
		
		tempRect.origin.x = viewWidth - RIGHTBLANK_HEIGHT+5;
		tempRect.origin.y = BOTBLANK_HEIGHT + i*perSecHeight-15;
		tempRect.size.width = RIGHTBLANK_HEIGHT;
		tempRect.size.height = 25;
		
		[tempString drawInRect:tempRect withAttributes:tempAttributes];
		
	}
	
	//价格坐标
	tempAttributes = [eGetData getAttributes:@"Arial" fontSize:12.0f theColor:[NSColor whiteColor] theAliment:NSRightTextAlignment];

    int closeNum = SecHeightNum /3 *2;

    if (currInfo.zsflag) {
		tempString = [NSString stringWithFormat:@"%.0f",currInfo.closeP];
	}else {
		
		if(currInfo.dataPre == 2)
			tempString = [NSString stringWithFormat:@"%.2f",currInfo.closeP];
		else
			tempString = [NSString stringWithFormat:@"%.3f",currInfo.closeP];
	}
	
	tempRect.origin.x = 0;
	tempRect.origin.y = BOTBLANK_HEIGHT + closeNum*perSecHeight-15;
	tempRect.size.width = LEFTBLANK_HEIGHT-2;
	tempRect.size.height = 25;
	
	[tempString drawInRect:tempRect withAttributes:tempAttributes];
	
	tempAttributes = [eGetData getAttributes:@"Arial" fontSize:12.0f theColor:HQCOLOR_DOWN theAliment:NSRightTextAlignment];

    for (i = 1; i<SecHeightNum /3; i++) {
		if(currInfo.zsflag){
			tempString = [NSString stringWithFormat:@"%.0f",currInfo.closeP - (m_dMaxPrice - currInfo.closeP)/SecHeightNum*3*i];
		}else {
			if(currInfo.dataPre == 2)
				tempString = [NSString stringWithFormat:@"%.2f",currInfo.closeP - (m_dMaxPrice - currInfo.closeP)/SecHeightNum*3*i];
			else
				tempString = [NSString stringWithFormat:@"%.3f",currInfo.closeP - (m_dMaxPrice - currInfo.closeP)/SecHeightNum*3*i];
		}
		
		tempRect.origin.x = 0;
		tempRect.origin.y = BOTBLANK_HEIGHT + closeNum*perSecHeight-15 - i*perSecHeight;
		tempRect.size.width = LEFTBLANK_HEIGHT-2;
		tempRect.size.height = 25;
		
		[tempString drawInRect:tempRect withAttributes:tempAttributes];
	}
	
	tempAttributes = [eGetData getAttributes:@"Arial" fontSize:12.0f theColor:[NSColor redColor] theAliment:NSRightTextAlignment];
	
	for (i = 1; i<SecHeightNum /3+1; i++) {
		if(currInfo.zsflag){
			tempString = [NSString stringWithFormat:@"%.0f",currInfo.closeP + (m_dMaxPrice - currInfo.closeP)/SecHeightNum*3*i];
		}else {
			if(currInfo.dataPre == 2)
				tempString = [NSString stringWithFormat:@"%.2f",currInfo.closeP +(m_dMaxPrice - currInfo.closeP)/SecHeightNum*3*i];
			else
				tempString = [NSString stringWithFormat:@"%.3f",currInfo.closeP + (m_dMaxPrice - currInfo.closeP)/SecHeightNum*3*i];
		}
		
		tempRect.origin.x = 0;
		tempRect.origin.y = BOTBLANK_HEIGHT + closeNum*perSecHeight-15 + i*perSecHeight;
		tempRect.size.width = LEFTBLANK_HEIGHT-2;
		tempRect.size.height = 25;
		
		[tempString drawInRect:tempRect withAttributes:tempAttributes];
	}
	
	
	
	//涨幅坐标
	tempAttributes = [eGetData getAttributes:@"Arial" fontSize:12.0f theColor:[NSColor whiteColor] theAliment:NSLeftTextAlignment];
	if (currInfo.zsflag) {
		tempString = @"0.00%";
	}else {
		
		if(currInfo.dataPre == 2)
			tempString = @"0.00%";
		else
			tempString = @"0.000%";
	}
	
	tempRect.origin.x = viewWidth - RIGHTBLANK_HEIGHT+5;
	tempRect.origin.y = BOTBLANK_HEIGHT + closeNum*perSecHeight-15;
	tempRect.size.width = RIGHTBLANK_HEIGHT;
	tempRect.size.height = 25;
	
	[tempString drawInRect:tempRect withAttributes:tempAttributes];
	
	
	tempAttributes = [eGetData getAttributes:@"Arial" fontSize:12.0f theColor:HQCOLOR_DOWN theAliment:NSLeftTextAlignment];


	for (i = 1; i<SecHeightNum /3; i++) {
		if(currInfo.zsflag){
			tempString = [NSString stringWithFormat:@"%.2f",(m_dMaxPrice - currInfo.closeP)/SecHeightNum*3*i*100/currInfo.closeP ];
		}else {
			if(currInfo.dataPre == 2)
				tempString = [NSString stringWithFormat:@"%.2f", (m_dMaxPrice - currInfo.closeP)/SecHeightNum*3*i*100/currInfo.closeP];
			else
				tempString = [NSString stringWithFormat:@"%.3f", (m_dMaxPrice - currInfo.closeP)/SecHeightNum*3*i*100/currInfo.closeP];
		}
		tempString = [tempString stringByAppendingString:@"%"];
		tempRect.origin.x = viewWidth - RIGHTBLANK_HEIGHT+5;
		tempRect.origin.y = BOTBLANK_HEIGHT + closeNum*perSecHeight-15 - i*perSecHeight;
		tempRect.size.width = RIGHTBLANK_HEIGHT;
		tempRect.size.height = 25;
		
		[tempString drawInRect:tempRect withAttributes:tempAttributes];
	}
	
	tempAttributes = [eGetData getAttributes:@"Arial" fontSize:12.0f theColor:[NSColor redColor] theAliment:NSLeftTextAlignment];

	for (i = 1; i<SecHeightNum /3+1; i++) {
		if(currInfo.zsflag){
			tempString = [NSString stringWithFormat:@"%.2f",(m_dMaxPrice - currInfo.closeP)/SecHeightNum*3*i*100/currInfo.closeP ];
		}else {
			if(currInfo.dataPre == 2)
				tempString = [NSString stringWithFormat:@"%.2f",(m_dMaxPrice - currInfo.closeP)/SecHeightNum*3*i*100/currInfo.closeP ];
			else
				tempString = [NSString stringWithFormat:@"%.3f",(m_dMaxPrice - currInfo.closeP)/SecHeightNum*3*i*100/currInfo.closeP ];
		}
		tempString = [tempString stringByAppendingString:@"%"];

		tempRect.origin.x =viewWidth - RIGHTBLANK_HEIGHT+5;
		tempRect.origin.y = BOTBLANK_HEIGHT + closeNum*perSecHeight-15 + i*perSecHeight;
		tempRect.size.width = RIGHTBLANK_HEIGHT;
		tempRect.size.height = 25;
		
		[tempString drawInRect:tempRect withAttributes:tempAttributes];
	}
	
	
	//画名称等
	tempAttributes = [eGetData getAttributes:@"Arial" fontSize:14.0f theColor:[NSColor whiteColor] theAliment:NSLeftTextAlignment];
	//名称
	tempString = currInfo.gpname;
	tempRect.origin.x = LEFTBLANK_HEIGHT;
	tempRect.origin.y = viewHeight - titleHeight;
	tempRect.size.width = 80;
	tempRect.size.height = titleHeight;
	
	[tempString drawInRect:tempRect withAttributes:tempAttributes];
	
	if (!currInfo.zsflag) {
		
		if ((currInfo.J_hy - 1 >0) &&(currInfo.J_hy - 1 < [hyTitleArray count]-1)){
			tempString = [NSString stringWithFormat:@"%@",[hyTitleArray objectAtIndex:currInfo.J_hy-1]];
			tempRect.origin.x = LEFTBLANK_HEIGHT+80;
			tempRect.origin.y = viewHeight - titleHeight;
			tempRect.size.width = 80;
			tempRect.size.height = titleHeight;
			
			[tempString drawInRect:tempRect withAttributes:tempAttributes];
			
		}
	}
}


-(void)layoutLabel{
}
#pragma mark 键盘事件相关
-(void) dealKeyBoardEvent:(NSEvent *)theEvent{
	switch ([theEvent keyCode]) {
		
		case MAC_KEY_ARROWDOWN:{
			//NSLog(@"方向键下");
		}
			break;
		case MAC_KEY_ARROWUP:{
			//NSLog(@"方向键上");
		}
			break;	
		case MAC_KEY_ARROWLEFT:{
			float tempFloat = 240.0f;
			float pos = (self.viewWidth-LEFTBLANK_HEIGHT-RIGHTBLANK_HEIGHT)/tempFloat;
			
			
			if (zstCross.showFlag) {
				cursor = cursor - 1;
				if (cursor < 0) {
					cursor = [m_MinuteData count]-1;
				}
				
				zstCross.xPos = LEFTBLANK_HEIGHT + pos*cursor;
				
				Minute_Unit * tempUnit;
				tempUnit = [m_MinuteData objectAtIndex:cursor];
				zstCross.yPos = [self getYFromValue:tempUnit.now pOrv:1];
				
				
				[zstCross refreshShow];
			}
			else {
				zstCross.showFlag = TRUE;
				

				cursor = [m_MinuteData count]-1;
				zstCross.xPos = LEFTBLANK_HEIGHT + pos*cursor;
				
				Minute_Unit * tempUnit;
				tempUnit = [m_MinuteData objectAtIndex:cursor];
				zstCross.yPos = [self getYFromValue:tempUnit.now pOrv:1];
				
				
				[zstCross refreshShow];
			}
			[self showCrossInfoWithCursor:cursor];
			
		}
			break;
		case MAC_KEY_ARROWRIGHT:{
			float tempFloat = 240.0f;
			float pos = (self.viewWidth-LEFTBLANK_HEIGHT-RIGHTBLANK_HEIGHT)/tempFloat;
			
			
			if (zstCross.showFlag) {
				cursor = cursor + 1;
				if (cursor >[m_MinuteData count]-1) {
					cursor = 0;
				}
				
				zstCross.xPos = LEFTBLANK_HEIGHT + pos*cursor;
				
				Minute_Unit * tempUnit;
				tempUnit = [m_MinuteData objectAtIndex:cursor];
				zstCross.yPos = [self getYFromValue:tempUnit.now pOrv:1];
				
				
				[zstCross refreshShow];
				
			}
			else {
				zstCross.showFlag = TRUE;
				
				
				cursor = 0;
				zstCross.xPos = LEFTBLANK_HEIGHT + pos*cursor;
				
				Minute_Unit * tempUnit;
                if([m_MinuteData count])
                {
                    tempUnit = [m_MinuteData objectAtIndex:cursor];
                    zstCross.yPos = [self getYFromValue:tempUnit.now pOrv:1];
                    [zstCross refreshShow];
                }
				
				
				
				
			}
			[self showCrossInfoWithCursor:cursor];
			
		}
			
			
			break;
			
		
		default:
			break;
	}
}

#pragma mark touche事件相关

-(void) mouseDown:(NSEvent *)theEvent{
	moveFlag = NO;
	
	NSPoint  p = [theEvent locationInWindow];
	m_nStartPosX = p.x;
	
	[[self window] makeFirstResponder:[self superview]];
}
-(void) mouseEntered:(NSEvent *)theEvent{
	//NSLog(@"mouseEntered");
}

-(void) mouseMoved:(NSEvent *)theEvent{
	//NSLog(@"mouseMoved");
	if(zstCross.showFlag)
	{
		float tempX  = [theEvent locationInWindow].x;
		if(tempX < LEFTBLANK_HEIGHT)  tempX = LEFTBLANK_HEIGHT;
		if (tempX > viewWidth - RIGHTBLANK_HEIGHT) tempX = viewWidth - RIGHTBLANK_HEIGHT;
		
		zstCross.xPos = tempX;
		
		cursor = (tempX - LEFTBLANK_HEIGHT)*240 / ((viewWidth - LEFTBLANK_HEIGHT-RIGHTBLANK_HEIGHT))  ;
		if (cursor < 0) cursor = 0;
		if(cursor > [m_MinuteData count]-1)
			cursor =  [m_MinuteData count]-1 ;
		
		Minute_Unit * tempUnit;
		tempUnit = [m_MinuteData objectAtIndex:cursor];
		zstCross.yPos = [self getYFromValue:tempUnit.now pOrv:1];
		
		
		[zstCross refreshShow];
		[self showCrossInfo:tempX];
	}
}

-(void) mouseDragged:(NSEvent *)theEvent{
	
	if(zstCross.showFlag)
	{
		float tempX  = [theEvent locationInWindow].x;
		if(tempX < LEFTBLANK_HEIGHT)  tempX = LEFTBLANK_HEIGHT;
		if (tempX > viewWidth - RIGHTBLANK_HEIGHT) tempX = viewWidth - RIGHTBLANK_HEIGHT;
		
		zstCross.xPos = tempX;
		
		cursor = (tempX - LEFTBLANK_HEIGHT)*240 / ((viewWidth - LEFTBLANK_HEIGHT-RIGHTBLANK_HEIGHT))  ;
		if (cursor < 0) cursor = 0;
		if(cursor > [m_MinuteData count]-1)
			cursor =  [m_MinuteData count]-1 ;
		
		Minute_Unit * tempUnit;
		tempUnit = [m_MinuteData objectAtIndex:cursor];
		zstCross.yPos = [self getYFromValue:tempUnit.now pOrv:1];
		
		
		[zstCross refreshShow];
		[self showCrossInfo:tempX];
	}
	else{
		//切换下只股票
	}
}

-(void) rightMouseDown:(NSEvent *)theEvent{
	[[self superview] rightMouseDown:theEvent];
}

-(void) mouseUp:(NSEvent *)theEvent{
	float tempX,tempY;
	if ([theEvent clickCount] != 2) {
		return;
	}
	tempX  = [theEvent locationInWindow].x;
	tempY  = [theEvent locationInWindow].y;
	if ((tempX > viewWidth - RIGHTBLANK_HEIGHT)&&(tempX < viewWidth)){
		[operProcessDelegate getHQProcess:@"" gpSetcode:-1 typeID:MAC_SWITCH_FUNC pareOne:-1 paraTwo:-1];
		return;
	}
	
	if(zstCross.showFlag)
	{
		if(!moveFlag){
			zstCross.showFlag = NO;
		}
		[zstCross refreshShow];
		[self dismissDetailComponent];
	}else{
		
		
		if(!moveFlag)
		{
			tempX  = [theEvent locationInWindow].x;
			if(tempX < 50)  tempX = 50;
			if (tempX > viewWidth - RIGHTBLANK_HEIGHT) tempX = viewWidth - RIGHTBLANK_HEIGHT;
			
			
			zstCross.xPos = tempX;
			
			
			cursor = (tempX - LEFTBLANK_HEIGHT)*240 / ((viewWidth - LEFTBLANK_HEIGHT-RIGHTBLANK_HEIGHT))  ;
			if (cursor < 0) cursor = 0;
			//NSLog([NSString stringWithFormat:@"cursor is %i",cursor]);
			if(cursor > [m_MinuteData count]-1)
				cursor =  [m_MinuteData count]-1 ;
			
			
			Minute_Unit * tempUnit;
			tempUnit = [m_MinuteData objectAtIndex:cursor];
			zstCross.yPos = [self getYFromValue:tempUnit.now pOrv:1];
			
			[zstCross refreshShow];
			
			zstCross.showFlag = TRUE;
			[self showCrossInfo:tempX];
		}	
	}
}

#pragma mark 协议相关

-(void)showBase:(SinHqInfo *) hqInfo{
	
	if(hqInfo.nowP > hqInfo.closeP)
	{	
	}
	else if(hqInfo.nowP < hqInfo.closeP)
	{	
	}
	else	
	{	
	}
}


-(void)showCrossInfo:(float)xPos{
	cursor = (xPos - LEFTBLANK_HEIGHT)*240 / ((viewWidth - LEFTBLANK_HEIGHT-RIGHTBLANK_HEIGHT))  ;
	if (cursor < 0) cursor = 0;
	if(cursor > [m_MinuteData count]-1)
		cursor =  [m_MinuteData count]-1 ;
	[self showzstDetail:cursor];
}
-(void)showCrossInfoWithCursor:(int)_cursor{
	[self showzstDetail:_cursor];
}

-(void)dismissDetailComponent{
	detailShowFlag = NO;
	[detailComponent removeFromSuperview];
}

-(void)showzstDetail:(int)_cursor{
	if ([m_MinuteData count] <1) {
		return;
	}
	
	if (!detailShowFlag) {
		detailShowFlag = YES;
		[self addSubview:detailComponent];
	}
	if(_cursor>=0 && _cursor<[m_MinuteData count])
    {
        Minute_Unit * tempUnit = [m_MinuteData objectAtIndex:_cursor];
        [detailComponent showDetail:tempUnit zsFlag:currInfo.zsflag dataPre:currInfo.dataPre  closeP:(float)currInfo.closeP];
    }
	
}

-(void)showMinute:(NSMutableArray *) MinuteData currInfo:(SinHqInfo *) _currInfo{
	self.dataFlag = TRUE;
	zstCross.showFlag = FALSE;
	[zstCross refreshShow];
	
	if (currInfo != nil) {
		[currInfo release],currInfo = nil;
		;
	}
	currInfo = [_currInfo deepCopy];

	if (m_MinuteData != nil) {
		[m_MinuteData removeAllObjects];
		[m_MinuteData release];
	}
	m_MinuteData = [[NSMutableArray alloc] initWithArray:MinuteData];
	if ([m_MinuteData count]>0) {
		
	if (currInfo.zsflag) {
	}
	else {
		
		
		int tempInt = currInfo.J_hy-1 ;
		if (tempInt < 0) {
		}
		else {
		}

		
	}

	
		[self calIt];
		[self setNeedsDisplay:YES];
	}
	
}

-(BOOL)refreshMinute:(SinHqInfo *) _currInfo nowHour:(int)_nowHour nowMinute:(int)_nowMinute {	
	if (currInfo != nil) {
		[currInfo release],currInfo = nil;
		;
	}
	currInfo = [_currInfo deepCopy];

	int nowCursor = [eGetData getTdxMinute:_nowHour theMinute:_nowMinute];
	int minute = [eGetData getMinuteFromFZ:nowCursor-1 fzNum:1];
	
	float nowPrice = currInfo.nowP;
	float average = 0;
	int tempVol = 0;
	int nowVol = 0;
	int i ;
	Minute_Unit * tempUnit;
	Minute_Unit * newUnit;
	
	int tempInt = nowCursor - [m_MinuteData count];
	
	if ([m_MinuteData count] < 1) {
		return NO;
	}
	
	if (tempInt < 0) {
		return YES;
	}
	
	if ((nowCursor - [m_MinuteData count]) >1){
		return NO;
	}
	else if ((nowCursor - [m_MinuteData count]) == 1){
		if (_currInfo.zsflag) {//指数
			for (i=0; i<nowCursor-1 && i<[m_MinuteData count]; i++) {
				tempUnit = [m_MinuteData objectAtIndex:i];
				tempVol = tempVol + tempUnit.nowvol;
			}
			
			nowVol = (currInfo.amount-tempVol*100.0)/100;
			
			average = currInfo.J_zgb;
			
            if([currInfo.sellP count]>2)
            {
                if ([[currInfo.sellP objectAtIndex:2] floatValue] > 0.01) {
                    average = average * [[currInfo.sellP objectAtIndex:2] floatValue];
                }
            }
			
			if (([m_MinuteData count] > i-1)&& average < 0.01 && [m_MinuteData count] && (i-1)>=0) {
				tempUnit = [m_MinuteData objectAtIndex:i-1];
				average = tempUnit.average;
			}
		}
		else {
			for (i=0; i<nowCursor-1 && i<[m_MinuteData count]; i++) {
				tempUnit = [m_MinuteData objectAtIndex:i];
				tempVol = tempVol + tempUnit.nowvol;
			}
			nowVol = currInfo.volume-tempVol;
			average = currInfo.amount/(currInfo.volume*100);
		}
		
		newUnit = [[Minute_Unit alloc] init];
		newUnit.minute = minute-1;
		newUnit.now = nowPrice;
		newUnit.average = average;
		newUnit.nowvol = nowVol;
		if (_currInfo.zsflag) {
		}
		[m_MinuteData addObject:newUnit];
		[newUnit release];
	}
	else if (nowCursor == [m_MinuteData count]){
		if (_currInfo.zsflag) {//指数
			for (i=0; i<nowCursor-1 && i<[m_MinuteData count]; i++) {
				tempUnit = [m_MinuteData objectAtIndex:i];
				tempVol = tempVol + tempUnit.nowvol;
			}
			
			nowVol = (currInfo.amount-tempVol*100.0)/100;
			
			average = currInfo.J_zgb;
			if([currInfo.sellP count]>2)
            {
                if ([[currInfo.sellP objectAtIndex:2] floatValue] > 0.01) {
                    average = average * [[currInfo.sellP objectAtIndex:2] floatValue];
                }
            }
			if (([m_MinuteData count] > (i-1))&& average < 0.01 && [m_MinuteData count] && (i-1)>=0) {
				tempUnit = [m_MinuteData objectAtIndex:i-1];
				average = tempUnit.average;
			}
		}
		else {
			for (i=0; i<nowCursor-1 && i<[m_MinuteData count]; i++) {
				tempUnit = [m_MinuteData objectAtIndex:i];
				tempVol = tempVol + tempUnit.nowvol;
				
			}
			
			nowVol = currInfo.volume-tempVol;
			if (currInfo.volume > 0) {
				average = currInfo.amount/(currInfo.volume*100);
			}
			else {
				average = 0.00f;
			}

			
		}
		if((nowCursor-1)>=0 && (nowCursor-1)<[m_MinuteData count])
            tempUnit = [m_MinuteData objectAtIndex:nowCursor-1];
        else
            tempUnit=nil;
		
		tempUnit.now = nowPrice;
		tempUnit.average = average;
		tempUnit.nowvol = nowVol;
		if (_currInfo.zsflag) {
		}
	}


	

	
	
	if ([m_MinuteData count]>0) {
		[self calIt];
		[self setNeedsDisplay:YES];
	}
	
	return YES;
}

-(void) calIt{
	Minute_Unit * tempUnit;
	Minute_Unit * tempUnitEx ;
	BOOL m_bZs,m_bBGp;
	float dmax ,dTmp,fTmp;
	float dmin ;
	int vmax = 0;
	dmax = (currInfo.maxP > 0.001) ? currInfo.maxP :currInfo.closeP;
	dmin = (currInfo.minP > 0.001) ? currInfo.minP : currInfo.closeP;
	m_bZs = (currInfo.zsflag) ? TRUE:FALSE;
	m_bBGp = (currInfo.dataPre == 3) ? TRUE:FALSE;

	for (int i = 0; i < [m_MinuteData count]; i++) {
		tempUnit = [m_MinuteData objectAtIndex:i];
		if(tempUnit.now > dmax)
			dmax = tempUnit.now;
		if(tempUnit.now < dmin)
			dmin = tempUnit.now;
		if(tempUnit.nowvol > vmax)
			vmax = tempUnit.nowvol;
	}
	
	
		
	dTmp=MAX_VALUE(ABSOLUTE_VALUE(dmax-currInfo.closeP),ABSOLUTE_VALUE(dmin-currInfo.closeP));
	dTmp=MAX_VALUE(dTmp,currInfo.closeP*(m_bZs?0.01:0.002));

	
	//由于远程传来的数据可能不准，因此有必要先将数据进行平滑处理
	if([m_MinuteData count] > 0)
	{	
		tempUnit = [m_MinuteData objectAtIndex:0];
		if(tempUnit.now < 0.001)
		{
			tempUnit.now = currInfo.closeP;
			tempUnit.average = currInfo.closeP;
		}
		
		//平滑均价
		if(tempUnit.average < 0.001 || ABSOLUTE_VALUE(tempUnit.average-currInfo.closeP) > dTmp+ 0.15*currInfo.closeP)
			tempUnit.average = currInfo.closeP;
		
	
		for(int i = 1;i < [m_MinuteData count];i++)
		{
			tempUnit = [m_MinuteData objectAtIndex:i];
			if(tempUnit.average < 0.001 || ABSOLUTE_VALUE(tempUnit.average-currInfo.closeP) > dTmp+ 0.15*currInfo.closeP){
				Minute_Unit * tempUnitEx = [m_MinuteData objectAtIndex:i-1];
				tempUnit.average =tempUnitEx.average;
			}
		}
		
		tempUnit = [m_MinuteData objectAtIndex:0];
		dmax = MAX_VALUE(tempUnit.average,tempUnit.now);
		dmin = MIN_VALUE(tempUnit.average,tempUnit.now);
		for (int i= 1; i < [m_MinuteData count]; i++)
		{
			tempUnit = [m_MinuteData objectAtIndex:i];

			if (tempUnit.now< 0.0001){
				tempUnitEx = [m_MinuteData objectAtIndex:i-1];
				tempUnit.now = tempUnitEx.now;
			}	
			
			
			fTmp = MAX_VALUE(tempUnit.average,tempUnit.now);
			if (dmax < fTmp) dmax = fTmp;
			fTmp = MIN_VALUE(tempUnit.average,tempUnit.now);
			if (dmin > fTmp) dmin = fTmp;
			
		}
	}
	
	
		//昨收必须在dMax和dMin之间
	if (dmax < currInfo.closeP) dmax =  currInfo.closeP;
	if (dmin > currInfo.closeP || dmin <= 0) dmin = currInfo.closeP;
	if(dmax < currInfo.maxP) dmax = currInfo.maxP;
	if(dmin > currInfo.minP) dmin = currInfo.minP;
	
	dTmp = (dmax + dmin) / 2;
	if (dTmp - currInfo.closeP > 0.001)//昨收偏向较低的价位,最小值要更小以使其到中间位置(昨收)的距离变大
		dmin = currInfo.closeP * 2 - dmax;
	else
		if (dTmp - currInfo.closeP < -0.001)
			dmax = currInfo.closeP * 2 - dmin;
	

	m_dPriceStep = (dmax-dmin)/PRICEAXISNUM;
	BOOL bUpdateMinMax = TRUE;
	if (m_bZs && m_dPriceStep < 1.0)
		m_dPriceStep = 1.0;
	else if (m_dPriceStep < 0.01 && !m_bBGp)
		m_dPriceStep = 0.01;
	else if (m_dPriceStep < 0.001 && m_bBGp)
		m_dPriceStep = 0.001;
	else 
		bUpdateMinMax = FALSE;
	if (bUpdateMinMax)
	{
		dmax = currInfo.closeP + m_dPriceStep   * 2;
		dmin = currInfo.closeP - m_dPriceStep  * 2;
		
			
		dTmp = (dmax + dmin) / 2;
		if (dTmp - currInfo.closeP > 0.01)//昨收偏向较低的价位,最小值要更小以使其到中间位置(昨收)的距离变大
			dmin = currInfo.closeP * 2 - dmax;
		else
			if (dTmp - currInfo.closeP < -0.01)
				dmax = currInfo.closeP * 2 - dmin;
	}
	m_dMaxPrice = dmax;
	m_dMinPrice = dmin;
	
	
	if (currInfo.zsflag) {
		m_dMaxVol= vmax * 1.10;
		m_dMaxVol = m_dMaxVol /100;
	}
	else {
		m_dMaxVol= vmax * 1.10;
	}

	
	m_lVolStep = m_dMaxVol / SecHeightNum*3;
	 

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

-(float)getYFromValue:(float) value  pOrv:(int) pOrv{
	float temp=0 ;
	if (pOrv)
    {
        if((m_dMaxPrice-m_dMinPrice)==0)
            temp=perSecHeight*SecHeightNum/3*2;
        else
            temp = ((m_dMaxPrice - value)/(m_dMaxPrice-m_dMinPrice))* perSecHeight*SecHeightNum/3*2;
		return viewHeight -  titleHeight - temp;
	}
    else
    {
		if(m_dMaxVol==0)
            temp=0;
		else if (currInfo.zsflag) {
			temp = ((value/100)/ m_dMaxVol)* self.perSecHeight*SecHeightNum/3;
		}
		else {
			temp = ((value)/ m_dMaxVol)* self.perSecHeight*SecHeightNum/3;
		}
		return BOTBLANK_HEIGHT+temp ;
	}
} 

@end
