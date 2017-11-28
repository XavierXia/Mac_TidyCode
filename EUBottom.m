//
//  EUBottom.m
//  tdxMac
//
//  Created by tdx on 11-9-8.
//  Copyright 2011 武汉. All rights reserved.
//

#import "EUBottom.h"
#define COUNTNUM 300

@implementation EUBottom
@synthesize theRepeatCount,initFlag;

- (id)initWithFrame:(NSRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code here.
    }
    return self;
}

- (id)initWithData:(NSRect)frame theData:(EGetData *)_eGetData{
    self = [super initWithData:frame theData:_eGetData];
    if (self) {
		dataFlag = NO;
		initFlag = NO;
		connFlag = NO;
		
		tipField = [[NSTextField alloc]init];
		[tipField setEditable:NO];
		[tipField setBackgroundColor:[NSColor clearColor]];
		[tipField setBordered:NO];
		[tipField setFrame:NSMakeRect(820,0,300,20)];
		[[tipField cell] setTextColor:[NSColor blackColor]];
		[[tipField cell] setFont:[NSFont systemFontOfSize:12.0]];
		[[tipField cell] setTitle:@""];
		[self addSubview:tipField];
	}
	return self;
}

-(void)getDpData{
	NSString * tempString = @"19999991999998199999703990010399002039900303990050399006";
	NSMutableData * theData = [eGetData getCombHQReq:tempString wantNum:8];	
	[eGetData.g_pEComm AsyncSendData:theData length:[theData length] withobjIndex:self.windindex withreqIndex:1];
}

-(void)OnReceiveData:(int)reqIndex FuncID:(int)_funcID HqResult:(HqResultData *)_hqResult{
	if (_hqResult.resultStat < 1) {
		return;
	}
	switch (reqIndex) {
		case COMBHQ2_5MMP_NREQ:{
			if (eGetData.codeinfo_data != nil) {
				[eGetData.codeinfo_data removeAllObjects];
				[eGetData.codeinfo_data release],eGetData.codeinfo_data=nil;
			}
			eGetData.codeinfo_data = [[NSMutableArray alloc] init];
			
			[eGetData getCombHQAns:eGetData.codeinfo_data hqResult:_hqResult];
			
			dataFlag = YES;
			
			[self setNeedsDisplay:YES];
		}	
	}		
}	

- (void)drawRect:(NSRect)dirtyRect {
    [BGCOLOR_GRAY set];
	NSRectFill(dirtyRect);
	
	
	[[NSColor whiteColor] set];
	
	NSString * tempString;
	NSRect tempRect;
	NSMutableDictionary * attributes;

	attributes = [eGetData getAttributes:@"Arial" fontSize:12.0f theColor:[NSColor blackColor] theAliment:NSLeftTextAlignment];
	
	
	tempString = @"上证";
	
	tempRect.origin.x = 0;
	tempRect.origin.y = 0;
	tempRect.size.width = 30;
	tempRect.size.height = 20;
	
	[tempString drawInRect:tempRect withAttributes:attributes];
	
	tempString = @"深证";
	
	tempRect.origin.x = 200*1;
	tempRect.origin.y = 0;
	tempRect.size.width = 30;
	tempRect.size.height = 20;
	
	[tempString drawInRect:tempRect withAttributes:attributes];
	
	tempString = @"中小";
	
	tempRect.origin.x = 200*2;
	tempRect.origin.y = 0;
	tempRect.size.width = 30;
	tempRect.size.height = 20;
	
	[tempString drawInRect:tempRect withAttributes:attributes];
	
	tempString = @"创业";
	
	tempRect.origin.x = 200*3;
	tempRect.origin.y = 0;
	tempRect.size.width = 30;
	tempRect.size.height = 20;
	
	[tempString drawInRect:tempRect withAttributes:attributes];
	
	if (dataFlag) {
		if ([eGetData.codeinfo_data count] < 1) {
			return;
		}
		SinHqInfo *rowData = [eGetData.codeinfo_data objectAtIndex:0];
		if(rowData.nowP > rowData.closeP){
			attributes = [eGetData getAttributes:@"Arial" fontSize:12.0f theColor:[NSColor redColor] theAliment:NSLeftTextAlignment];
		}
		else if(rowData.nowP < rowData.closeP){
			attributes = [eGetData getAttributes:@"Arial" fontSize:12.0f theColor:HQCOLOR_DOWN theAliment:NSLeftTextAlignment];
			
		}
		else {
			attributes = [eGetData getAttributes:@"Arial" fontSize:12.0f theColor:COLOR_GRID_NORMALCOLOR theAliment:NSLeftTextAlignment];
			
		}
		
		tempString = [NSString stringWithFormat:@"%.2f   %.2f   %.2f",rowData.nowP,rowData.zad,rowData.zaf];
		tempString = [tempString stringByAppendingString:@"%"];
		tempRect.origin.x = 30;
		tempRect.origin.y = 0;
		tempRect.size.width = 170;
		tempRect.size.height = 20;
		
		[tempString drawInRect:tempRect withAttributes:attributes];
		
		if ([eGetData.codeinfo_data count] < 4) {
			return;
		}
		
		rowData = [eGetData.codeinfo_data objectAtIndex:3];
		if(rowData.nowP > rowData.closeP){
			attributes = [eGetData getAttributes:@"Arial" fontSize:12.0f theColor:[NSColor redColor] theAliment:NSLeftTextAlignment];
		}
		else if(rowData.nowP < rowData.closeP){
			attributes = [eGetData getAttributes:@"Arial" fontSize:12.0f theColor:HQCOLOR_DOWN theAliment:NSLeftTextAlignment];
			
		}
		else {
			attributes = [eGetData getAttributes:@"Arial" fontSize:12.0f theColor:COLOR_GRID_NORMALCOLOR theAliment:NSLeftTextAlignment];
			
		}
		
		
		tempString = [NSString stringWithFormat:@"%.2f   %.2f   %.2f",rowData.nowP,rowData.zad,rowData.zaf];
		tempString = [tempString stringByAppendingString:@"%"];
		tempRect.origin.x = 230;
		tempRect.origin.y = 0;
		tempRect.size.width = 170;
		tempRect.size.height = 20;
		
		[tempString drawInRect:tempRect withAttributes:attributes];
		
		
		if ([eGetData.codeinfo_data count] < 7) {
			return;
		}
		
		rowData = [eGetData.codeinfo_data objectAtIndex:6];
		

		if(rowData.nowP > rowData.closeP){
			attributes = [eGetData getAttributes:@"Arial" fontSize:12.0f theColor:[NSColor redColor] theAliment:NSLeftTextAlignment];
		}
		else if(rowData.nowP < rowData.closeP){
			attributes = [eGetData getAttributes:@"Arial" fontSize:12.0f theColor:HQCOLOR_DOWN theAliment:NSLeftTextAlignment];
			
		}
		else {
			attributes = [eGetData getAttributes:@"Arial" fontSize:12.0f theColor:COLOR_GRID_NORMALCOLOR theAliment:NSLeftTextAlignment];
			
		}
		
		
		tempString = [NSString stringWithFormat:@"%.2f   %.2f   %.2f",rowData.nowP,rowData.zad,rowData.zaf];
		tempString = [tempString stringByAppendingString:@"%"];
		tempRect.origin.x = 430;
		tempRect.origin.y = 0;
		tempRect.size.width = 170;
		tempRect.size.height = 20;
		
		[tempString drawInRect:tempRect withAttributes:attributes];
		
		if ([eGetData.codeinfo_data count] < 8) {
			return;
		}
		
		rowData = [eGetData.codeinfo_data objectAtIndex:7];
		
		
		if(rowData.nowP > rowData.closeP){
			attributes = [eGetData getAttributes:@"Arial" fontSize:12.0f theColor:[NSColor redColor] theAliment:NSLeftTextAlignment];
		}
		else if(rowData.nowP < rowData.closeP){
			attributes = [eGetData getAttributes:@"Arial" fontSize:12.0f theColor:HQCOLOR_DOWN theAliment:NSLeftTextAlignment];
			
		}
		else {
			attributes = [eGetData getAttributes:@"Arial" fontSize:12.0f theColor:COLOR_GRID_NORMALCOLOR theAliment:NSLeftTextAlignment];
			
		}
		
		tempString = [NSString stringWithFormat:@"%.2f   %.2f   %.2f",rowData.nowP,rowData.zad,rowData.zaf];
		tempString = [tempString stringByAppendingString:@"%"];
		tempRect.origin.x = 630;
		tempRect.origin.y = 0;
		tempRect.size.width = 170;
		tempRect.size.height = 20;
		
		[tempString drawInRect:tempRect withAttributes:attributes];
	}
}

-(void)showTips{
	NSString * tempString;
	if (eGetData.g_pEComm.connFlag) {
		connFlag = YES;
		TradeSite *pSite=[eGetData GetHqLoginSite:YES];
		if(pSite!=nil)
		{
			tempString = [NSString stringWithFormat:@"行情主站_%@",pSite.sname];
			[[tipField cell] setTitle:tempString];
		}
	}
	else {
		connFlag = NO;
		if (!initFlag) {
			[[tipField cell] setTitle:@"未连接到行情主站"];
		}
		
	}

}

-(void)showInitTips{
	initFlag = YES;
	theRepeatCount = COUNTNUM;
	NSString * tempString;
	tempString = [NSString stringWithFormat:@"行情主站正在初始化，请耐心等待%i秒......",theRepeatCount];
	[[tipField cell] setTitle:tempString];
}
-(void)showRefreshTips{
	NSString * tempString;
	tempString = [NSString stringWithFormat:@"行情主站正在初始化，请耐心等待%i秒......",theRepeatCount];
	[[tipField cell] setTitle:tempString];
}

-(void)showAfterInitTips{
	initFlag = NO;
	[[tipField cell] setTitle:@"正在尝试重新连接....."];
}

-(void)setTips:(NSString *)_tips{
	[[tipField cell] setTitle:_tips];
}

-(void) mouseUp:(NSEvent *)theEvent{
	float tempX  = [theEvent locationInWindow].x;
	
	if (tempX > 800 && tempX < 1100) {
    if (!connFlag) {
			if( (!eGetData.g_pEComm.bconnflag) && (!initFlag)){
				[[tipField cell] setTitle:@"正在尝试重新连接......"];
				eGetData.g_pEComm.ntimeoutnum = 1;
				[operProcessDelegate startReconnect];
			}
			
		}
	}

	
	if ([theEvent clickCount] != 2) {
		return;
	}
	
	if (tempX <= 800) {
		int tempInt = tempX / 200;
		
		switch (tempInt) {
			case 0:
				[operProcessDelegate getHQProcess:@"999999" gpSetcode:1 typeID:MAC_ZST_FUNC pareOne:1 paraTwo:-1];
				break;
			case 1:
				[operProcessDelegate getHQProcess:@"399001" gpSetcode:0 typeID:MAC_ZST_FUNC pareOne:1 paraTwo:-1];
				break;
			case 2:
				[operProcessDelegate getHQProcess:@"399005" gpSetcode:0 typeID:MAC_ZST_FUNC pareOne:1 paraTwo:-1];
				break;
			case 3:
				[operProcessDelegate getHQProcess:@"399006" gpSetcode:0 typeID:MAC_ZST_FUNC pareOne:1 paraTwo:-1];
				break;
			default:
				break;
		}
	}
	else {
		
	}


	
	
}

@end
