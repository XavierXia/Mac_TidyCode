//
//  DataHqComponent.m
//  tdxiphone
//
//  Created by 魏 文敏 on 09-12-30.
//  Copyright 2009 武汉. All rights reserved.
//

#import "DataHqComponent.h"

#define TITLE_TAG 1
#define PRICE_TAG 2
#define VOL_TAG 3
#define ZS_TITLE_TAG 4
#define ZS_VOL_TAG 5
#define INOUT_TAG 6
#define RISE_TAG 7
#define DOWN_TAG 8
#define MAIN_FONT_SIZE 15
#define TEXT_FONT_SIZE 15
#define TOTALWIDTH 210
#define PERSECWIDTH 50
#define PERROWHEIGHT 21
#define TOPBLANKHEIGHT 40

#define LEFTMARIN 5

#define GGHQ_FlAG 100
#define ZSHQ_FLAG 101

#define GGHQDETAILFONT 13.0f

@implementation DataHqComponent

@synthesize myTableView,titleArray,currInfo;
@synthesize myDelegate,zsTitleArray,zxgDelegate,showFlag;


- (id)initWithData:(NSRect)aRect theData:(EGetData *)_eGetData{
	self = [super initWithData:aRect theData:_eGetData ];
	if(self != nil){
		viewRect = aRect;
		self.eGetData = _eGetData;
		self.showFlag = NO;
		selectIndex= -1;

		NSRect tableFrame;
		tableFrame.origin.x = 1;
		tableFrame.origin.y = PERROWHEIGHT*6;
		tableFrame.size.width = aRect.size.width-10;
		tableFrame.size.height = aRect.size.height-TOPBLANKHEIGHT-PERROWHEIGHT*6;
		
		myTableView = [[CustonTableView alloc] initWithFrame:tableFrame];
		myTableView.clickDelegate = self;
		[myTableView setHeaderView:nil];

		[myTableView setBackgroundColor:[NSColor clearColor]];
		[myTableView setGridColor:[NSColor lightGrayColor]];
		[myTableView setAutosaveTableColumns:NO];
		[myTableView setAllowsEmptySelection:YES];
		[myTableView setAllowsColumnSelection:NO];
		[myTableView setAllowsColumnReordering:NO];
		[myTableView setAllowsColumnResizing:NO];
		[myTableView setRowHeight:PERROWHEIGHT];
		[myTableView setFocusRingType:1];
		[myTableView setAction:@selector(singleClick:)];
		[myTableView setTag:GGHQ_FlAG];
		
		[self addColumn:@"name" withTitle:@"" withWidth:70];
		[self addColumn:@"price" withTitle:@"" withWidth:60];
		[self addColumn:@"vol" withTitle:@"" withWidth:75];
		[myTableView setDataSource:self];
		[myTableView setDelegate:self];
		[self addSubview:myTableView];
		
		
		tableFrame.origin.x = 1;
		tableFrame.origin.y = PERROWHEIGHT;
		tableFrame.size.width = aRect.size.width-10;
		tableFrame.size.height = aRect.size.height-TOPBLANKHEIGHT-PERROWHEIGHT;
		
		myTableViewforZS = [[NSTableView alloc] initWithFrame:tableFrame];
		[myTableViewforZS setHeaderView:nil];

        [myTableViewforZS setBackgroundColor:[NSColor blackColor]];
		[myTableViewforZS setGridColor:[NSColor lightGrayColor]];
		[myTableViewforZS setAutosaveTableColumns:NO];
		[myTableViewforZS setAllowsEmptySelection:YES];
		[myTableViewforZS setAllowsColumnSelection:NO];
		[myTableViewforZS setAllowsColumnReordering:NO];
		[myTableViewforZS setAllowsColumnResizing:NO];
		[myTableViewforZS setRowHeight:PERROWHEIGHT];
		[myTableViewforZS setFocusRingType:1];
		[myTableViewforZS setTag:ZSHQ_FLAG];
		
		[self addColumnEx:@"zsname" withTitle:@"" withWidth:90];
		[self addColumnEx:@"zsprice" withTitle:@"" withWidth:110];

		[myTableViewforZS setDataSource:self];
		[myTableViewforZS setDelegate:self];
		[self addSubview:myTableViewforZS];
		
		
		zsCellArray = [[NSMutableArray alloc] initWithCapacity:16];
		
        if (!eGetData.clientinfos.m_bxyjyflag)
        {
            hqMenu = [[NSMenu allocWithZone:[NSMenu menuZone]] initWithTitle:@""];
        }
		
		NSMenuItem * newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"闪电买入	21" action:@selector(rightMenu:) keyEquivalent:@""];
		[newItem setEnabled:YES];
		[newItem setTarget:self];
		[newItem setTag:0];
		[hqMenu addItem:newItem];
		[newItem release];
		
		newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"闪电卖出	23" action:@selector(rightMenu:) keyEquivalent:@""];
		[newItem setEnabled:YES];
		[newItem setTarget:self];
		[newItem setTag:1];
		[hqMenu addItem:newItem];
		[newItem release];
		
		newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"普通买入	221" action:@selector(rightMenu:) keyEquivalent:@""];
		[newItem setEnabled:YES];
		[newItem setTarget:self];
		[newItem setTag:2];
		[hqMenu addItem:newItem];
		[newItem release];

		
		newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"普通卖出	223" action:@selector(rightMenu:) keyEquivalent:@""];
		[newItem setEnabled:YES];
		[newItem setTarget:self];
		[newItem setTag:3];
		[hqMenu addItem:newItem];
		[newItem release];
		
		newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"撤单查询	22" action:@selector(rightMenu:) keyEquivalent:@""];
		[newItem setEnabled:YES];
		[newItem setTarget:self];
		[newItem setTag:4];
		[hqMenu addItem:newItem];
		[newItem release];
		
	}
	
	return self;
}

-(void)rightMenu:(id)sender{
	int tempInt = [myTableView clickedRow];
	if (tempInt == -1) {
		tempInt = selectIndex;
	}
    
 
    
	float tempFloat ;
	NSString * tempString;
	if (eGetData.tradeLoginFlag) {
		switch ([sender tag]) {
			case 0://闪电买入
				if (tempInt <5) {
					int i = tempInt-4;
					i = ABSOLUTE_VALUE(i);
                    if(i<[currInfo.sellP count])
                        tempFloat = [[currInfo.sellP objectAtIndex:i] floatValue];
                    else
                        tempFloat=0.0f;
				}
				else {
                    if((tempInt-5)<[currInfo.buyP count])
                        tempFloat = [[currInfo.buyP objectAtIndex:tempInt-5] floatValue];
                    else
                        tempFloat=0.0f;
				}
				
				if ( (tempFloat > 0.01) ){
					if(currInfo.dataPre == 2)
						tempString = [NSString stringWithFormat:@"%.2f",tempFloat];
					else
						tempString = [NSString stringWithFormat:@"%.3f",tempFloat];
				}
				else {
					tempString = @"";
				}
				[operProcessDelegate getTradeProcess:currInfo.gpcode gpSetcode:currInfo.setcode typeID:MAC_FASTWT_FUNC pareOne:0 paraTwo:-1 pareThree:tempString];
				
				
				;
				break;
			case 1://闪电卖出
				if (tempInt <5) {
					int i = tempInt-4;
					i = ABSOLUTE_VALUE(i);
                    if(i<[currInfo.sellP count])
                        tempFloat = [[currInfo.sellP objectAtIndex:i] floatValue];
                    else
                        tempFloat=0.0f;
				}
				else {
                    if((tempInt-5)<[currInfo.buyP count])
                        tempFloat = [[currInfo.buyP objectAtIndex:tempInt-5] floatValue];
                    else
                        tempFloat=0.0f;
				}
				
				if ( (tempFloat > 0.01) ){
					if(currInfo.dataPre == 2)
						tempString = [NSString stringWithFormat:@"%.2f",tempFloat];
					else
						tempString = [NSString stringWithFormat:@"%.3f",tempFloat];
				}
				else {
					tempString = @"";
				}
				
				[operProcessDelegate getTradeProcess:currInfo.gpcode gpSetcode:currInfo.setcode typeID:MAC_FASTWT_FUNC pareOne:1 paraTwo:-1 pareThree:tempString];
				
				;
				break;
			case 2://普通买入
				if (tempInt <5) {
					int i = tempInt-4;
					i = ABSOLUTE_VALUE(i);
                    if(i<[currInfo.sellP count])
                        tempFloat = [[currInfo.sellP objectAtIndex:i] floatValue];
                    else
                        tempFloat=0.0f;
				}
				else {
                    if((tempInt-5)<[currInfo.buyP count])
                        tempFloat = [[currInfo.buyP objectAtIndex:tempInt-5] floatValue];
                    else
                        tempFloat=0.0f;
				}

				if ( (tempFloat > 0.01) ){
					if(currInfo.dataPre == 2)
						tempString = [NSString stringWithFormat:@"%.2f",tempFloat];
					else
						tempString = [NSString stringWithFormat:@"%.3f",tempFloat];
				}
				else {
					tempString = @"";
				}

				[operProcessDelegate getTradeProcess:currInfo.gpcode gpSetcode:currInfo.setcode typeID:MAC_WT_FUNC pareOne:0 paraTwo:-1 pareThree:tempString];
					
				break;
			case 3://普通卖出
				if (tempInt <5) {
					int i = tempInt-4;
					i = ABSOLUTE_VALUE(i);
                    if(i<[currInfo.sellP count])
                        tempFloat = [[currInfo.sellP objectAtIndex:i] floatValue];
                    else
                        tempFloat=0.0f;
				}
				else {
                    if(tempInt-5<[currInfo.buyP count])
                        tempFloat = [[currInfo.buyP objectAtIndex:tempInt-5] floatValue];
                    else
                        tempFloat=0.0f;
				}
				
				if ( (tempFloat > 0.01) ){
					if(currInfo.dataPre == 2)
						tempString = [NSString stringWithFormat:@"%.2f",tempFloat];
					else
						tempString = [NSString stringWithFormat:@"%.3f",tempFloat];
				}
				else {
					tempString = @"";
				}
				
				[operProcessDelegate getTradeProcess:currInfo.gpcode gpSetcode:currInfo.setcode typeID:MAC_WT_FUNC pareOne:1 paraTwo:-1 pareThree:tempString];
				
				;
				break;
			case 4://委托撤单
				[operProcessDelegate getTradeProcess:@"" gpSetcode:-1 typeID:MAC_CANCEL_FUNC pareOne:TDX_CDCX paraTwo:-1 pareThree:@""];
				
				break;
			default:
				break;
		}
	}
	else{
		NSAlert* alert = [NSAlert alertWithMessageText: @"提示"
										 defaultButton: @"确定"
									   alternateButton: nil
										   otherButton: nil
							 informativeTextWithFormat: @"交易系统尚未登录!不能使用此功能"];
		[alert runModal];
	}
}

- (void)addColumn:(NSString*)newid withTitle:(NSString*)title withWidth:(int)_width
{
	NSTableColumn *column=[[NSTableColumn alloc] initWithIdentifier:newid];
	
	iTableColumnHeaderCell * tempCell = [[iTableColumnHeaderCell alloc] 
										 initTextCell:title];
	
	[column setHeaderCell:tempCell];
	[tempCell release];
	[column setWidth:_width];
	[column setEditable:NO];
	[myTableView addTableColumn:column];
	[column release];
	
	
}

- (void)addColumnEx:(NSString*)newid withTitle:(NSString*)title withWidth:(int)_width
{
	NSTableColumn *column=[[NSTableColumn alloc] initWithIdentifier:newid];
	
	iTableColumnHeaderCell * tempCell = [[iTableColumnHeaderCell alloc] 
										 initTextCell:title];
	
	[column setHeaderCell:tempCell];
	[tempCell release];
	[column setWidth:_width];
	[column setEditable:NO];
	[myTableViewforZS addTableColumn:column];
	[column release];
	
	
}

-(void) setFrame:(NSRect)aRect{
	[super setFrame:aRect];
	
}

- (void)drawRect:(NSRect)rect {
	//NSLog(@"draw hq frame");
	
	CGContextRef context = [[NSGraphicsContext currentContext] graphicsPort];
	CGContextSetAllowsAntialiasing(context, FALSE);
	[[NSColor redColor] set];
	CGContextSetLineWidth(context, 0.6f);
	CGContextMoveToPoint(context, 2, viewRect.size.height-1  );
	CGContextAddLineToPoint(context, viewRect.size.width-3, viewRect.size.height-1);
	
	CGContextMoveToPoint(context, 2, 0);
	CGContextAddLineToPoint(context, viewRect.size.width-3,0);
	
	
	if (!currInfo.zsflag) {
		CGContextMoveToPoint(context, 2, viewRect.size.height -TOPBLANKHEIGHT );
		CGContextAddLineToPoint(context, viewRect.size.width-3, viewRect.size.height -TOPBLANKHEIGHT);
		
		CGContextMoveToPoint(context, 2, PERROWHEIGHT*6-1);
		CGContextAddLineToPoint(context, viewRect.size.width-3, PERROWHEIGHT*6-1);
		
        CGContextMoveToPoint(context, 2, PERROWHEIGHT*11.5-1);
        CGContextAddLineToPoint(context, viewRect.size.width-3, PERROWHEIGHT*11.5-1);
	}
	
	CGContextStrokePath(context);
	
	CGContextSetAllowsAntialiasing(context, TRUE);
	
	if (selectIndex > -1) {
		if (!currInfo.zsflag) {
			[[NSColor blueColor] set];	
			NSRectFill(NSMakeRect(0, 6*PERROWHEIGHT+ABSOLUTE_VALUE(selectIndex -9)*(PERROWHEIGHT+2), viewRect.size.width, (PERROWHEIGHT+2)));

		}
	}
	

	if (self.showFlag) {
		NSString * tempString;
		NSRect tempRect;
		NSMutableDictionary * tempAttributes;
		
		if ([operZXGDelegate stockIsIn:currInfo.gpcode setcode:currInfo.setcode]) {
			tempAttributes = [eGetData getAttributes:@"Arial" fontSize:20.0f theColor:HQCOLOR_ZIXUAN theAliment:2];
		}
		else {
			tempAttributes = [eGetData getAttributes:@"Arial" fontSize:20.0f theColor:[NSColor yellowColor] theAliment:2];
		}
		
		
		if (currInfo.gpcode != nil) {
			tempString = [NSString stringWithFormat:@"%@  %@",currInfo.gpcode,currInfo.gpname];
			
			tempRect.origin.x = 0;
			tempRect.origin.y = viewRect.size.height-TOPBLANKHEIGHT-10;
			tempRect.size.width = viewRect.size.width;
			tempRect.size.height = TOPBLANKHEIGHT;
			[tempString drawInRect:tempRect withAttributes:tempAttributes];
			
		}
		
		//个股
		if (!currInfo.zsflag) {
			tempAttributes = [eGetData getAttributes:@"Arial" fontSize:GGHQDETAILFONT theColor:[NSColor whiteColor] theAliment:NSLeftTextAlignment];
			
			//现价
			tempRect.origin.x = LEFTMARIN;
			tempRect.origin.y = PERROWHEIGHT * 5 ;
			tempRect.size.width = 50-LEFTMARIN;
			tempRect.size.height = PERROWHEIGHT;
			
			tempString =@"现价";
			[tempString drawInRect:tempRect withAttributes:tempAttributes];
			
			//今开
			tempRect.origin.x = LEFTMARIN+TOTALWIDTH/2;
			tempRect.origin.y = PERROWHEIGHT * 5 ;
			tempRect.size.width = 50-LEFTMARIN;
			tempRect.size.height = PERROWHEIGHT;
			
			tempString =@"今开";
			[tempString drawInRect:tempRect withAttributes:tempAttributes];
			
			//涨跌
			tempRect.origin.x = LEFTMARIN;
			tempRect.origin.y = PERROWHEIGHT * 4 ;
			tempRect.size.width = 50-LEFTMARIN;
			tempRect.size.height = PERROWHEIGHT;
			
			tempString =@"涨跌";
			[tempString drawInRect:tempRect withAttributes:tempAttributes];
			
			//最高
			tempRect.origin.x = LEFTMARIN+TOTALWIDTH/2;
			tempRect.origin.y = PERROWHEIGHT * 4 ;
			tempRect.size.width = 50-LEFTMARIN;
			tempRect.size.height = PERROWHEIGHT;
			
			tempString =@"最高";
			[tempString drawInRect:tempRect withAttributes:tempAttributes];
			
			//涨幅
			tempRect.origin.x = LEFTMARIN;
			tempRect.origin.y = PERROWHEIGHT * 3 ;
			tempRect.size.width = 50-LEFTMARIN;
			tempRect.size.height = PERROWHEIGHT;
			
			tempString =@"涨幅";
			[tempString drawInRect:tempRect withAttributes:tempAttributes];
			
			//最低
			tempRect.origin.x = LEFTMARIN+TOTALWIDTH/2;
			tempRect.origin.y = PERROWHEIGHT * 3 ;
			tempRect.size.width = 50-LEFTMARIN;
			tempRect.size.height = PERROWHEIGHT;
			
			tempString =@"最低";
			[tempString drawInRect:tempRect withAttributes:tempAttributes];
			
			//总量
			tempRect.origin.x = LEFTMARIN;
			tempRect.origin.y = PERROWHEIGHT * 2 ;
			tempRect.size.width = 50-LEFTMARIN;
			tempRect.size.height = PERROWHEIGHT;
			
			tempString =@"总量";
			[tempString drawInRect:tempRect withAttributes:tempAttributes];
			
			//总额
			tempRect.origin.x = LEFTMARIN+TOTALWIDTH/2;
			tempRect.origin.y = PERROWHEIGHT * 2 ;
			tempRect.size.width = 50-LEFTMARIN;
			tempRect.size.height = PERROWHEIGHT;
			
			tempString =@"总额";
			[tempString drawInRect:tempRect withAttributes:tempAttributes];
			
			//换手
			tempRect.origin.x = LEFTMARIN;
			tempRect.origin.y = PERROWHEIGHT * 1 ;
			tempRect.size.width = 50-LEFTMARIN;
			tempRect.size.height = PERROWHEIGHT;
			
			tempString =@"换手";
			[tempString drawInRect:tempRect withAttributes:tempAttributes];
			
			//股本
			tempRect.origin.x = LEFTMARIN+TOTALWIDTH/2;
			tempRect.origin.y = PERROWHEIGHT * 1 ;
			tempRect.size.width = 50-LEFTMARIN;
			tempRect.size.height = PERROWHEIGHT;
			
			tempString =@"股本";
			[tempString drawInRect:tempRect withAttributes:tempAttributes];
			
			//pe
			tempRect.origin.x = LEFTMARIN;
			tempRect.origin.y = 0 ;
			tempRect.size.width = 50-LEFTMARIN;
			tempRect.size.height = PERROWHEIGHT;
			
			tempString =@"PE(动)";
			[tempString drawInRect:tempRect withAttributes:tempAttributes];
			
			//流通
			tempRect.origin.x = LEFTMARIN+TOTALWIDTH/2;
			tempRect.origin.y = 0;
			tempRect.size.width = 50-LEFTMARIN;
			tempRect.size.height = PERROWHEIGHT;
			
			tempString =@"流通";
			[tempString drawInRect:tempRect withAttributes:tempAttributes];
			
			
			//值
			//现价
			if (currInfo.nowP > currInfo.closeP) {
				tempAttributes = [eGetData getAttributes:@"Arial" fontSize:GGHQDETAILFONT theColor:[NSColor redColor] theAliment:NSRightTextAlignment];
			}
			else if(currInfo.nowP < currInfo.closeP) {
				tempAttributes = [eGetData getAttributes:@"Arial" fontSize:GGHQDETAILFONT theColor:HQCOLOR_DOWN theAliment:NSRightTextAlignment];
			}
			else {
				tempAttributes = [eGetData getAttributes:@"Arial" fontSize:GGHQDETAILFONT theColor:COLOR_GRID_COMMONCOLOR theAliment:NSRightTextAlignment];
			}
			
			if (currInfo.nowP > 0.01) {
				if(currInfo.dataPre == 2)
					tempString = [NSString stringWithFormat:@"%.2f",currInfo.nowP];
				else
					tempString = [NSString stringWithFormat:@"%.3f",currInfo.nowP];
			}
			else {
				tempString = @"";
			}


			tempRect.origin.x = LEFTMARIN+TOTALWIDTH/4;
			tempRect.origin.y = PERROWHEIGHT * 5 ;
			tempRect.size.width = 50-LEFTMARIN;
			tempRect.size.height = PERROWHEIGHT;
			
			[tempString drawInRect:tempRect withAttributes:tempAttributes];
			
			//今开
			if (currInfo.openP > currInfo.closeP) {
				tempAttributes = [eGetData getAttributes:@"Arial" fontSize:GGHQDETAILFONT theColor:[NSColor redColor] theAliment:NSRightTextAlignment];
			}
			else if(currInfo.openP < currInfo.closeP) {
				tempAttributes = [eGetData getAttributes:@"Arial" fontSize:GGHQDETAILFONT theColor:HQCOLOR_DOWN theAliment:NSRightTextAlignment];
			}
			else {
				tempAttributes = [eGetData getAttributes:@"Arial" fontSize:GGHQDETAILFONT theColor:COLOR_GRID_COMMONCOLOR theAliment:NSRightTextAlignment];
			}
			
			if (currInfo.nowP > 0.01) {
				if(currInfo.dataPre == 2)
					tempString = [NSString stringWithFormat:@"%.2f",currInfo.openP];
				else
					tempString = [NSString stringWithFormat:@"%.3f",currInfo.openP];
			}
			else {
				tempString = @"";
			}
			
			tempRect.origin.x = LEFTMARIN+TOTALWIDTH/2+TOTALWIDTH/4;
			tempRect.origin.y = PERROWHEIGHT * 5 ;
			tempRect.size.width = 50-LEFTMARIN;
			tempRect.size.height = PERROWHEIGHT;
			
			[tempString drawInRect:tempRect withAttributes:tempAttributes];
			
						
			if ((currInfo.zaf == 0) &&(currInfo.nowP < 0.001) && ([currInfo.buyP count]<=0 || [[currInfo.buyP objectAtIndex:0]floatValue] < 0.001)) {
				tempString = @"";
			}
			else {
				if (currInfo.zaf > 0) {
					tempAttributes = [eGetData getAttributes:@"Arial" fontSize:GGHQDETAILFONT theColor:[NSColor redColor] theAliment:NSRightTextAlignment];
				}
				else if(currInfo.zaf < 0) {
					tempAttributes = [eGetData getAttributes:@"Arial" fontSize:GGHQDETAILFONT theColor:HQCOLOR_DOWN theAliment:NSRightTextAlignment];
				}
				else {
					tempAttributes = [eGetData getAttributes:@"Arial" fontSize:GGHQDETAILFONT theColor:COLOR_GRID_COMMONCOLOR theAliment:NSRightTextAlignment];
				}
				if(currInfo.dataPre == 2)
					tempString = [NSString stringWithFormat:@"%.2f",currInfo.zad];
				else
					tempString = [NSString stringWithFormat:@"%.3f",currInfo.zad];
			}

			
			
			tempRect.origin.x = LEFTMARIN+TOTALWIDTH/4;
			tempRect.origin.y = PERROWHEIGHT * 4 ;
			tempRect.size.width = 50-LEFTMARIN;
			tempRect.size.height = PERROWHEIGHT;
			
			[tempString drawInRect:tempRect withAttributes:tempAttributes];
			
			//最高
			if (currInfo.maxP > currInfo.closeP) {
				tempAttributes = [eGetData getAttributes:@"Arial" fontSize:GGHQDETAILFONT theColor:[NSColor redColor] theAliment:NSRightTextAlignment];
			}
			else if(currInfo.maxP < currInfo.closeP) {
				tempAttributes = [eGetData getAttributes:@"Arial" fontSize:GGHQDETAILFONT theColor:HQCOLOR_DOWN theAliment:NSRightTextAlignment];
			}
			else {
				tempAttributes = [eGetData getAttributes:@"Arial" fontSize:GGHQDETAILFONT theColor:COLOR_GRID_COMMONCOLOR theAliment:NSRightTextAlignment];
			}
			
			if (currInfo.nowP > 0.01) {
				if(currInfo.dataPre == 2)
					tempString = [NSString stringWithFormat:@"%.2f",currInfo.maxP];
				else
					tempString = [NSString stringWithFormat:@"%.3f",currInfo.maxP];
			}
			else {
				tempString = @"";
			}
			
			tempRect.origin.x = LEFTMARIN+TOTALWIDTH/2+TOTALWIDTH/4;
			tempRect.origin.y = PERROWHEIGHT * 4 ;
			tempRect.size.width = 50-LEFTMARIN;
			tempRect.size.height = PERROWHEIGHT;
			
			[tempString drawInRect:tempRect withAttributes:tempAttributes];
			
			if ((currInfo.zaf == 0) &&(currInfo.nowP < 0.001) && ([currInfo.buyP count]<=0 || [[currInfo.buyP objectAtIndex:0]floatValue] < 0.001)) {
				tempString = @"";
			}
			else {
				if (currInfo.zaf > 0) {
					tempAttributes = [eGetData getAttributes:@"Arial" fontSize:GGHQDETAILFONT theColor:[NSColor redColor] theAliment:NSRightTextAlignment];
				}
				else if(currInfo.zaf < 0) {
					tempAttributes = [eGetData getAttributes:@"Arial" fontSize:GGHQDETAILFONT theColor:HQCOLOR_DOWN theAliment:NSRightTextAlignment];
				}
				else {
					tempAttributes = [eGetData getAttributes:@"Arial" fontSize:GGHQDETAILFONT theColor:COLOR_GRID_COMMONCOLOR theAliment:NSRightTextAlignment];
				}
				
				if(currInfo.dataPre == 2)
					tempString = [NSString stringWithFormat:@"%.2f",currInfo.zaf];
				else
					tempString = [NSString stringWithFormat:@"%.3f",currInfo.zaf];
				
				tempString = [tempString stringByAppendingString:@"%"];
			}

			
			
			tempRect.origin.x = LEFTMARIN+TOTALWIDTH/4;
			tempRect.origin.y = PERROWHEIGHT * 3 ;
			tempRect.size.width = 50-LEFTMARIN;
			tempRect.size.height = PERROWHEIGHT;
			
			[tempString drawInRect:tempRect withAttributes:tempAttributes];
			
			//最低
			if (currInfo.minP > currInfo.closeP) {
				tempAttributes = [eGetData getAttributes:@"Arial" fontSize:GGHQDETAILFONT theColor:[NSColor redColor] theAliment:NSRightTextAlignment];
			}
			else if(currInfo.minP < currInfo.closeP) {
				tempAttributes = [eGetData getAttributes:@"Arial" fontSize:GGHQDETAILFONT theColor:HQCOLOR_DOWN theAliment:NSRightTextAlignment];
			}
			else {
				tempAttributes = [eGetData getAttributes:@"Arial" fontSize:GGHQDETAILFONT theColor:COLOR_GRID_COMMONCOLOR theAliment:NSRightTextAlignment];
			}
			
			if (currInfo.nowP > 0.01) {
				if(currInfo.dataPre == 2)
					tempString = [NSString stringWithFormat:@"%.2f",currInfo.minP];
				else
					tempString = [NSString stringWithFormat:@"%.3f",currInfo.minP];
			}
			else {
				tempString = @"";
			}
			
			tempRect.origin.x = LEFTMARIN+TOTALWIDTH/2+TOTALWIDTH/4;
			tempRect.origin.y = PERROWHEIGHT * 3 ;
			tempRect.size.width = 50-LEFTMARIN;
			tempRect.size.height = PERROWHEIGHT;
			
			[tempString drawInRect:tempRect withAttributes:tempAttributes];
			
			//总量
			tempAttributes = [eGetData getAttributes:@"Arial" fontSize:GGHQDETAILFONT theColor:[NSColor yellowColor] theAliment:NSRightTextAlignment];
			
			if (currInfo.nowP > 0.01) {
				if(currInfo.volume > 100000){
					tempString = [NSString stringWithFormat:@"%.1f",currInfo.volume/10000];
					tempString = [tempString stringByAppendingString:@"万"];
				}	
				else {
					tempString = [NSString stringWithFormat:@"%.0f",currInfo.volume];
				}
			}
			else {
				tempString = @"";
			}
			tempRect.origin.x = LEFTMARIN+TOTALWIDTH/4;
			tempRect.origin.y = PERROWHEIGHT * 2 ;
			tempRect.size.width = 50-LEFTMARIN;
			tempRect.size.height = PERROWHEIGHT;
			
			[tempString drawInRect:tempRect withAttributes:tempAttributes];
			
			//总额
			tempAttributes = [eGetData getAttributes:@"Arial" fontSize:GGHQDETAILFONT theColor:[NSColor whiteColor] theAliment:NSRightTextAlignment];
			
			
			if (currInfo.nowP > 0.01) {
				if(currInfo.amount > 100000000){
					tempString = [NSString stringWithFormat:@"%.2f",currInfo.amount/100000000];
					tempString = [tempString stringByAppendingString:@"亿"];
				}	
				else {
					tempString = [NSString stringWithFormat:@"%.0f",currInfo.amount/10000];
					tempString = [tempString stringByAppendingString:@"万"];
				}
			}
			else {
				tempString = @"";
			}
			
			tempRect.origin.x = LEFTMARIN+TOTALWIDTH/2+TOTALWIDTH/4;
			tempRect.origin.y = PERROWHEIGHT * 2 ;
			tempRect.size.width = 50-LEFTMARIN;
			tempRect.size.height = PERROWHEIGHT;
			
			[tempString drawInRect:tempRect withAttributes:tempAttributes];
			
			//换手
			if (currInfo.ActiveCapital > 0) {
				tempString = [NSString stringWithFormat:@"%.2f",currInfo.exchange];
				tempString = [tempString stringByAppendingString:@"%"];
			}
			else {
				tempString = @"－";
			}
			
			tempRect.origin.x = LEFTMARIN+TOTALWIDTH/4;
			tempRect.origin.y = PERROWHEIGHT * 1 ;
			tempRect.size.width = 50-LEFTMARIN;
			tempRect.size.height = PERROWHEIGHT;
			
			[tempString drawInRect:tempRect withAttributes:tempAttributes];
			
			//股本
			if (currInfo.J_zgb > 1000000) {
				tempString = [NSString stringWithFormat:@"%.0f亿",currInfo.J_zgb/10000];
			}
			else if ((currInfo.J_zgb < 1000000)&&(currInfo.J_zgb > 100000)){
				tempString = [NSString stringWithFormat:@"%.1f亿",currInfo.J_zgb/10000];
			}
			else if ((currInfo.J_zgb < 100000)&&(currInfo.J_zgb > 10000)){
				tempString = [NSString stringWithFormat:@"%.2f亿",currInfo.J_zgb/10000];
			}
			else {
				tempString = [NSString stringWithFormat:@"%.0f万",currInfo.J_zgb];
			}
			
			tempRect.origin.x = LEFTMARIN+TOTALWIDTH/2+TOTALWIDTH/4;
			tempRect.origin.y = PERROWHEIGHT * 1 ;
			tempRect.size.width = 50-LEFTMARIN;
			tempRect.size.height = PERROWHEIGHT;
			
			[tempString drawInRect:tempRect withAttributes:tempAttributes];
			
			//pe
			if (currInfo.J_syl <= 0) {
				tempString = @"-";
			}
			else {
				tempString = [NSString stringWithFormat:@"%.1f",currInfo.J_syl];
				
			}

			
			tempRect.origin.x = LEFTMARIN+TOTALWIDTH/4;
			tempRect.origin.y = 0 ;
			tempRect.size.width = 50-LEFTMARIN;
			tempRect.size.height = PERROWHEIGHT;
			
			
			[tempString drawInRect:tempRect withAttributes:tempAttributes];
			
			//流通
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
			
			tempRect.origin.x = LEFTMARIN+TOTALWIDTH/2+TOTALWIDTH/4;
			tempRect.origin.y = 0;
			tempRect.size.width = 50-LEFTMARIN;
			tempRect.size.height = PERROWHEIGHT;
			
			[tempString drawInRect:tempRect withAttributes:tempAttributes];
			
			
		}
		//指数
		else {
			tempAttributes = [eGetData getAttributes:@"Arial" fontSize:GGHQDETAILFONT theColor:[NSColor whiteColor] theAliment:NSLeftTextAlignment];
			
			//
			tempRect.origin.x = LEFTMARIN;
			tempRect.origin.y = 0;
			tempRect.size.width = 50-LEFTMARIN;
			tempRect.size.height = PERROWHEIGHT;
			
			tempString =@"涨家数";
			[tempString drawInRect:tempRect withAttributes:tempAttributes];
			
			//今开
			tempRect.origin.x = LEFTMARIN+TOTALWIDTH/2;
			tempRect.origin.y = 0 ;
			tempRect.size.width = 50-LEFTMARIN;
			tempRect.size.height = PERROWHEIGHT;
			
			tempString =@"跌家数";
			[tempString drawInRect:tempRect withAttributes:tempAttributes];
			
			
			
			//现价
			
			tempAttributes = [eGetData getAttributes:@"Arial" fontSize:GGHQDETAILFONT theColor:[NSColor redColor] theAliment:NSRightTextAlignment];
			
            if([currInfo.buyV count])
                tempString = [currInfo.buyV objectAtIndex:0];
            else
                tempString=@"";
			if ([tempString intValue] == 0) {
				tempString =@"";
			}
			
			
			tempRect.origin.x = LEFTMARIN+TOTALWIDTH/4;
			tempRect.origin.y = 0 ;
			tempRect.size.width = 50-LEFTMARIN;
			tempRect.size.height = PERROWHEIGHT;
			
			[tempString drawInRect:tempRect withAttributes:tempAttributes];
			
			//今开
			tempAttributes = [eGetData getAttributes:@"Arial" fontSize:GGHQDETAILFONT theColor:HQCOLOR_DOWN theAliment:NSRightTextAlignment];
            if([currInfo.sellV count])
                tempString = [currInfo.sellV objectAtIndex:0];
            else
                tempString=@"0";
			if ([tempString intValue] == 0) {
				tempString = @"";
			}
			
			tempRect.origin.x = LEFTMARIN+TOTALWIDTH/2+TOTALWIDTH/4;
			tempRect.origin.y = 0 ;
			tempRect.size.width = 50-LEFTMARIN;
			tempRect.size.height = PERROWHEIGHT;
			
			[tempString drawInRect:tempRect withAttributes:tempAttributes];
			
		}

	}
}


#pragma mark 显示相关
-(void)layoutLabel{
}

-(void)showTable{
	//NSLog(@"hq reloaddata");
	self.showFlag = TRUE;
	selectIndex = -1;
	[self setNeedsDisplay:YES];
	if (currInfo.zsflag) {
		[myTableViewforZS reloadData];
	}else {
		[self.myTableView reloadData];
	}

	
}


-(void)checkIsInZXG{
	if([zxgDelegate stockIsIn:currInfo.gpcode setcode:currInfo.setcode]){
		addFlag = NO;
	}
	else {
		addFlag = YES;
	}
}

-(void)checkIsInZXGAfterDelete:(NSString *)_gpcode theSetcode:(int)_setcode{
	if(([currInfo.gpcode compare:_gpcode] == 0) && (currInfo.setcode == _setcode)){
		[self checkIsInZXG];
	}
}

-(void)showBase:(SinHqInfo *) hqInfo{
	if (currInfo != nil) {
		[currInfo release],currInfo = nil;
		;
	}
	currInfo = [hqInfo deepCopy];
	
	
	if (currInfo.zsflag) {
		[myTableView removeFromSuperview];
		[myTableViewforZS removeFromSuperview];
		[self addSubview:myTableViewforZS];
	}
	else {
		[myTableView removeFromSuperview];
		[myTableViewforZS removeFromSuperview];
		[self addSubview:myTableView];
	}
	self.showFlag = YES;
	[self setNeedsDisplay:YES];
	
	[self showTable];
	if(currInfo.zsflag)
	{
	}
	else {
		if(currInfo.nowP > currInfo.closeP)
		{	
		}
		else if(currInfo.nowP < currInfo.closeP)
		{	
		}
		else	
		{	
		}
		
	}

}

-(void)dealTheZS{
}

-(void)addZXGClick:(id)sender{
	if (addFlag) {
		if([self.zxgDelegate addStock:currInfo.gpcode setcode:currInfo.setcode]){
		}
		else {
		}
	}
	else {

	}

	
	
}

#pragma mark NSTableViewDelegate
-(BOOL) selectionShouldChangeInTableView:(NSTableView *)tableView{
	return NO;
}


#pragma mark NSTableViewDataSource Delegate

- (NSInteger)numberOfRowsInTableView:(NSTableView *)tableView;
{
	NSUInteger tempInt;
	if (tableView.tag == GGHQ_FlAG) {
			if (currInfo.zsflag) {
				tempInt =  (NSUInteger)[zsTitleArray count];
				return tempInt;
			}
			else {
				tempInt = (NSUInteger)[titleArray count];
				return tempInt;
			}
			
	}
	else if(tableView.tag == ZSHQ_FLAG){
		tempInt = 14;
		return tempInt;
	}

	tempInt = 0;
	return tempInt ;
}

-(CGFloat) tableView:(NSTableView *)tableView heightOfRow:(NSInteger)row{
	return PERROWHEIGHT;
}

-(void)getClick:(NSEvent *)theEvent{
	[NSMenu popUpContextMenu:hqMenu withEvent:theEvent forView:myTableView];
}

-(void)singleClick:(id)sender{
	
	selectIndex = [myTableView clickedRow];
	[self setNeedsDisplay:YES];
	
	
	[[self window] makeFirstResponder:[self superview]];
	
	
}

-(void)doubleClick:(id)sender{
}

- (id)tableView:(NSTableView *)tableView objectValueForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row
{
	if (!self.showFlag) {
		return nil;
	}
	
	NSString * tempString;
	int i;
	float tempfloat ;
	
	if (tableView.tag == GGHQ_FlAG) {
		if (currInfo.zsflag) {
			return nil;
		}
		else { //个股
			if ([[tableColumn identifier] isEqual:@"name"]) {
                if(row>=[titleArray count])
                    return @"";
				return [titleArray objectAtIndex:row];
			}
			
			else if([[tableColumn identifier] isEqual:@"price"]) {
				if (row < 5) {
					i = row-4;
					i = ABSOLUTE_VALUE(i);
                    if(i>=[currInfo.sellP count])
                        tempfloat=0.0f;
                    else
                        tempfloat = [[currInfo.sellP objectAtIndex:i] floatValue];
					
					if ( (tempfloat > 0.01) ){
						if(currInfo.dataPre == 2)
							tempString = [NSString stringWithFormat:@"%.2f",tempfloat];
						else
							tempString = [NSString stringWithFormat:@"%.3f",tempfloat];
					}
					else {
						tempString = @"";
					}
				}
				else {
					i = row-5;
					i = ABSOLUTE_VALUE(i);
                    if(i>=[currInfo.buyP count])
                        tempfloat=0.0f;
                    else
                        tempfloat = [[currInfo.buyP objectAtIndex:i] floatValue];
					
					if ( (tempfloat > 0.01)){
						if(currInfo.dataPre == 2)
							tempString = [NSString stringWithFormat:@"%.2f",tempfloat];
						else
							tempString = [NSString stringWithFormat:@"%.3f",tempfloat];
					}
					else {
						tempString = @"";
					}
				}
				
				
				return tempString;
			}
			
			else if([[tableColumn identifier] isEqual:@"vol"]){
				if (row < 5) {
					i = row-4;
					i = ABSOLUTE_VALUE(i);
                    if(i>=[currInfo.sellV count])
                        tempString = @"";
                    else
                    {
                        if ([[currInfo.sellV objectAtIndex:i] intValue]> 0.01){
                            tempString = [NSString stringWithFormat:@"%@",[currInfo.sellV objectAtIndex:i]];
                        }else{
                            tempString = @"";
                        }
                    }
				}
				else {
					i = row-5;
					i = ABSOLUTE_VALUE(i);
					if(i>=[currInfo.buyV count])
                        tempString = @"";
                    else
                    {
                        if (([[currInfo.buyV objectAtIndex:i]intValue] > 0.01)){
                            tempString = [NSString stringWithFormat:@"%@",[currInfo.buyV objectAtIndex:i]];
                        }
                        else {
                            tempString = @"";
                        }
                    }
					
				}
				
				
				return tempString;
			}
		}
	}
	else if(tableView.tag == ZSHQ_FLAG){
		if ([[tableColumn identifier] isEqual:@"zsname"]) {
            if(row>=[zsTitleArray count])
                return @"";
			return [zsTitleArray objectAtIndex:row];
		}
		else if([[tableColumn identifier] isEqual:@"zsprice"]) {
			SinHqInfo *rowData;
			switch (row) {
				case 0:{ //A股成交
                    if(currInfo.setcode == 1)
                    {
                        if([eGetData.codeinfo_data count]>1)
                            rowData = [eGetData.codeinfo_data objectAtIndex:1];
                        else
                            rowData=nil;
                    }
                    else
                    {
                        if([eGetData.codeinfo_data count]>4)
                            rowData = [eGetData.codeinfo_data objectAtIndex:4];
                        else
                            rowData=nil;
                    }
                    if(rowData)
                    {
                        if(rowData.amount>=10000*10000.0)
                            tempString = [NSString stringWithFormat:@"%.4f亿",rowData.amount/(10000*10000.0)];
                        else if(rowData.amount>=10000.0)
                            tempString = [NSString stringWithFormat:@"%.4f万",rowData.amount/(10000.0)];
                        else
                            tempString = [NSString stringWithFormat:@"%.0f",rowData.amount];
                    }
				}
					break;
				case 1:{//b股成交
                    if(currInfo.setcode == 1)
                    {
                        if([eGetData.codeinfo_data count]>2)
                            rowData = [eGetData.codeinfo_data objectAtIndex:2];
                        else
                            rowData=nil;
                    }
                    else
                    {
                        if([eGetData.codeinfo_data count]>5)
                            rowData = [eGetData.codeinfo_data objectAtIndex:5];
                        else
                            rowData=nil;
                    }
                    if(rowData)
                    {
                        if(rowData.amount>=10000*10000.0)
                            tempString = [NSString stringWithFormat:@"%.4f亿",rowData.amount/(10000*10000.0)];
                        else if(rowData.amount>=10000.0)
                            tempString = [NSString stringWithFormat:@"%.4f万",rowData.amount/(10000.0)];
                        else
                            tempString = [NSString stringWithFormat:@"%.0f",rowData.amount];
                    }
				}
					break;
				case 2:{//国债成交
                    if(currInfo.setcode == 1)
                    {
                        if([eGetData.codeinfo_data count])
                            rowData = [eGetData.codeinfo_data objectAtIndex:0];
                        else
                            rowData=nil;
                    }
                    else
                    {
                        if([eGetData.codeinfo_data count]>3)
                            rowData = [eGetData.codeinfo_data objectAtIndex:3];
                        else
                            rowData=nil;
                    }
                    if(rowData && [rowData.buyP count]>0)
                    {
                        tempfloat = [[rowData.buyP objectAtIndex:2] floatValue];
                        if(tempfloat>=10000*10000.0)
                            tempString = [NSString stringWithFormat:@"%.4f亿",tempfloat/(10000*10000.0)];
                        else if(tempfloat>=10000.0)
                            tempString = [NSString stringWithFormat:@"%.4f万",tempfloat/(10000.0)];
                        else
                            tempString = [NSString stringWithFormat:@"%.0f",tempfloat];
                    }
              
				}
					break;	
				case 3:{//基金成交
                    if(currInfo.setcode == 1)
                    {
                        if([eGetData.codeinfo_data count])
                            rowData = [eGetData.codeinfo_data objectAtIndex:0];
                        else
                            rowData=nil;
                    }
                    else
                    {
                        if([eGetData.codeinfo_data count]>3)
                            rowData = [eGetData.codeinfo_data objectAtIndex:3];
                        else
                            rowData=nil;
                    }
                    if(rowData && [rowData.buyP count])
                    {
                        tempfloat = [[rowData.buyP objectAtIndex:0] floatValue];
                        if(tempfloat>=10000*10000.0)
                            tempString = [NSString stringWithFormat:@"%.4f亿",tempfloat/(10000*10000.0)];
                        else if(tempfloat>=10000.0)
                            tempString = [NSString stringWithFormat:@"%.4f万",tempfloat/(10000.0)];
                        else
                            tempString = [NSString stringWithFormat:@"%.0f",tempfloat];
                    }
				}
					break;	
//				case 4:{//权证成交
//					if(currInfo.setcode == 1)
//                    {
//                        if([eGetData.codeinfo_data count])
//                            rowData = [eGetData.codeinfo_data objectAtIndex:0];
//                        else
//                            rowData=nil;
//                    }
//					else
//                    {
//                        if([eGetData.codeinfo_data count]>3)
//                            rowData = [eGetData.codeinfo_data objectAtIndex:3];
//                        else
//                            rowData=nil;
//                    }
//                    if(rowData && [rowData.sellP count])
//                    {
//                        tempfloat = [[rowData.sellP objectAtIndex:0] floatValue];
//                        tempString= [NSString stringWithFormat:@"%.0f万",tempfloat/10000];
//                    }
//				}
//					break;	
				case 4:{//最新指数
					tempString= [NSString stringWithFormat:@"%.2f",currInfo.nowP];
				}
					break;	
				case 5:{//今日开盘
					tempString = [NSString stringWithFormat:@"%.2f",currInfo.openP];
				}
					break;	
				case 6:{//昨日收盘
					tempString = [NSString stringWithFormat:@"%.2f",currInfo.closeP];
				}
					break;	
				case 7:{//指数涨跌
					tempString = [NSString stringWithFormat:@"%.2f",currInfo.nowP-currInfo.closeP];
				}
					break;	
				case 8:{//指数涨幅
					tempString = [NSString stringWithFormat:@"%.2f",currInfo.zaf];
					tempString = [tempString stringByAppendingString:@"%"];
				}
					break;	
				case 9:{//指数振幅
					tempString = [NSString stringWithFormat:@"%.2f",(currInfo.maxP- currInfo.minP)*100/currInfo.closeP];
					tempString = [tempString stringByAppendingString:@"%"];
				}
					break;	
				case 10:{//总成交量
					if(currInfo.volume>=10000*10000)
                        tempString = [NSString stringWithFormat:@"%.4f亿",currInfo.volume/(10000*10000.0)];
                    else if(currInfo.volume>=10000)
                        tempString = [NSString stringWithFormat:@"%.4f万",currInfo.volume/(10000.0)];
                    else
                        tempString = [NSString stringWithFormat:@"%.0f",currInfo.volume*1.0];
				}
					break;	
				case 11:{//总成交额
                    if(currInfo.amount>=10000*10000.0)
                        tempString = [NSString stringWithFormat:@"%.4f亿",currInfo.amount/(10000*10000.0)];
                    else if(currInfo.amount>=10000.0)
                        tempString = [NSString stringWithFormat:@"%.4f万",currInfo.amount/(10000.0)];
                    else
                        tempString = [NSString stringWithFormat:@"%.0f",currInfo.amount];
                    
				}
					break;	
				case 12:{//最高指数
					tempString = [NSString stringWithFormat:@"%.2f",currInfo.maxP];
				}
					break;	
				case 13:{//最低指数
					tempString = [NSString stringWithFormat:@"%.2f",currInfo.minP];
				}
					break;

				default:
					break;
			}
			return tempString;
		}
	}
	

	return nil;
}

-(void)tableView:(NSTableView *)tableView willDisplayCell:(id)cell forTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row{
	if (!self.showFlag) {
		return;
	}
	
	
	int i;
	float tempfloat ;
	
	
	if (tableView.tag == GGHQ_FlAG) {
		[cell setFont:[NSFont systemFontOfSize:14.0f]];
		if (currInfo.zsflag) {
			
		}
		else {
			if ([[tableColumn identifier] isEqual:@"name"]) {
				[cell setTextColor:COLOR_GRID_COMMONCOLOR];
			}
			else if([[tableColumn identifier] isEqual:@"price"])
            {
				if (row<5) {
					i = row-4;
					i = ABSOLUTE_VALUE(i);
                    if(i<[currInfo.sellP count])
                        tempfloat = [[currInfo.sellP objectAtIndex:i] floatValue];
                    else
                        tempfloat=0.0f;
				}
				else {
					i = row-5;
					i = ABSOLUTE_VALUE(i);
                    if(i<[currInfo.buyP count])
                        tempfloat = [[currInfo.buyP objectAtIndex:i] floatValue];
                    else
                        tempfloat=0.0f;
				}
				if(tempfloat > currInfo.closeP)
					[cell setTextColor:[NSColor redColor]];
				else if(tempfloat < currInfo.closeP)
					[cell setTextColor:HQCOLOR_DOWN] ;
				else
					[cell setTextColor:COLOR_GRID_COMMONCOLOR];
			}
			else if([[tableColumn identifier] isEqual:@"vol"]){
				[cell setAlignment:NSRightTextAlignment];
				[cell setTextColor:[NSColor yellowColor]];
				
			}
		}
	}
	else if (tableView.tag == ZSHQ_FLAG) { 
		[cell setFont:[NSFont systemFontOfSize:13.0f]];
		if ([[tableColumn identifier] isEqual:@"zsname"]) {
			[cell setTextColor:COLOR_GRID_COMMONCOLOR];
		}
		else if([[tableColumn identifier] isEqual:@"zsprice"]) {
			[cell setAlignment:NSRightTextAlignment];
			
			
			switch (row) {
				case 0:{ //A股成交
					[cell setTextColor:[NSColor yellowColor]];				}
					break;
				case 1:{//b股成交
					[cell setTextColor:[NSColor yellowColor]];					}
					break;
				case 2:{//国债成交
					[cell setTextColor:[NSColor yellowColor]];	
				}
					break;	
				case 3:{//基金成交
					[cell setTextColor:[NSColor yellowColor]];	
				}
					break;	
//				case 4:{//权证成交
//					[cell setTextColor:[NSColor yellowColor]];	
//				}
//					break;	
				case 4:{//最新指数
					if (currInfo.nowP>currInfo.closeP) {
						[cell setTextColor:[NSColor redColor]];
					}
					else if(currInfo.nowP<currInfo.closeP){
						[cell setTextColor:HQCOLOR_DOWN] ;
					}
					else {
						[cell setTextColor:COLOR_GRID_COMMONCOLOR];
					}
				}
					break;	
				case 5:{//今日开盘
					if (currInfo.openP>currInfo.closeP) {
						[cell setTextColor:[NSColor redColor]];
					}
					else if(currInfo.openP<currInfo.closeP){
						[cell setTextColor:HQCOLOR_DOWN] ;
					}
					else {
						[cell setTextColor:COLOR_GRID_COMMONCOLOR];
					}
				}
					break;	
				case 6:{//昨日收盘
					[cell setTextColor:COLOR_GRID_COMMONCOLOR];
				}
					break;	
				case 7:{//指数涨跌
					if (currInfo.nowP>currInfo.closeP) {
						[cell setTextColor:[NSColor redColor]];
					}
					else if(currInfo.nowP<currInfo.closeP){
						[cell setTextColor:HQCOLOR_DOWN] ;
					}
					else {
						[cell setTextColor:COLOR_GRID_COMMONCOLOR];
					}
					
				}
					break;	
				case 8:{//指数涨幅
					if (currInfo.nowP>currInfo.closeP) {
						[cell setTextColor:[NSColor redColor]];
					}
					else if(currInfo.nowP<currInfo.closeP){
						[cell setTextColor:HQCOLOR_DOWN] ;
					}
					else {
						[cell setTextColor:COLOR_GRID_COMMONCOLOR];
					}
					
				}
					break;	
				case 9:{//指数振幅
					[cell setTextColor:COLOR_GRID_COMMONCOLOR];
				}
					break;	
				case 10:{//总成交量
					[cell setTextColor:[NSColor yellowColor]];
				}
					break;	
				case 11:{//总成交额
					[cell setTextColor:[NSColor yellowColor]];
                }
					break;	
				case 12:{//最高指数
					if (currInfo.maxP>currInfo.closeP) {
						[cell setTextColor:[NSColor redColor]];
					}
					else if(currInfo.maxP<currInfo.closeP){
						[cell setTextColor:HQCOLOR_DOWN] ;
					}
					else {
						[cell setTextColor:COLOR_GRID_COMMONCOLOR];
					}
					
				}
					break;	
				case 13:{//最低指数
					if (currInfo.minP>currInfo.closeP) {
						[cell setTextColor:[NSColor redColor]];
					}
					else if(currInfo.minP<currInfo.closeP){
						[cell setTextColor:HQCOLOR_DOWN] ;
					}
					else {
						[cell setTextColor:COLOR_GRID_COMMONCOLOR];
					}
                }
					break;
				
				default:
					break;
			}
			
		}

		
	}

	

}

#pragma mark 鼠标键盘事件相关
-(void) mouseDown:(NSEvent *)theEvent{
	[[self window] makeFirstResponder:[self superview]];
	if (currInfo.zsflag) {
		
	}
}


- (void)dealloc {
	[titleArray release];
	[zsTitleArray release];
	[myTableView release];
	[myTableViewforZS release];
	[currInfo release];
	[zsCellArray removeAllObjects],[zsCellArray release];
	[super dealloc];
}


@end
