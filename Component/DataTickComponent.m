//
//  DataTickComponent.m
//  tdxIpad
//
//  Created by tdx on 10-12-31.
//  Copyright 2010 武汉. All rights reserved.
//

#import "DataTickComponent.h"

#define MINUTE_TAG 1
#define PRICE_TAG 2
#define VOL_TAG 3
#define INOUT_TAG 4
#define MAIN_FONT_SIZE 15
#define PERROWHEIGHT 20
#define TOTALWIDTH 200

@implementation DataTickComponent

@synthesize myTableView,zsFlag,showFlag,m_tickData,dataPre,closep,myDelegate,showNum;


- (id)initWithData:(NSRect)aRect theData:(EGetData *)_eGetData{
    if ((self = [super initWithData:aRect theData:_eGetData])) {
        // Initialization code
		self.eGetData = _eGetData;
		tapCount = 0;
		self.zsFlag = FALSE;
		self.showFlag = FALSE;
		
		NSRect tableFrame;
		tableFrame.origin.x = 1;
		tableFrame.origin.y = 1;
		tableFrame.size.width = aRect.size.width;
		tableFrame.size.height = aRect.size.height;
		
		
		
		myTableView = [[NSTableView alloc] initWithFrame:tableFrame];
		[myTableView setHeaderView:nil];
		
		[myTableView setBackgroundColor:[NSColor clearColor]];
		[myTableView setGridColor:[NSColor lightGrayColor]];
		[myTableView setAutosaveTableColumns:NO];
		[myTableView setAllowsEmptySelection:YES];
		[myTableView setAllowsColumnSelection:NO];
		[myTableView setAllowsColumnReordering:NO];
		[myTableView setAllowsColumnResizing:NO];
		[myTableView setRowHeight:PERROWHEIGHT];
		[myTableView enclosingScrollView];
		[myTableView setFocusRingType:1];
		[myTableView setAction:@selector(singleClick:)];
		
		[self addColumn:@"time" withTitle:@"" withWidth:40];
		[self addColumn:@"price" withTitle:@"" withWidth:80];
		[self addColumn:@"vol" withTitle:@"" withWidth:60];
		[self addColumn:@"flag" withTitle:@"" withWidth:30];
		[myTableView setDataSource:self];
		[myTableView setDelegate:self];
		
		[self addSubview:myTableView];
	

    }
    return self;
}

-(void) setFrame:(NSRect)aRect{
	[super setFrame:aRect];
	NSRect tableFrame;
	tableFrame.origin.x = 1;
	tableFrame.origin.y = 1;
	tableFrame.size.width = aRect.size.width;
	tableFrame.size.height = aRect.size.height;
	

    [myTableView setFrame:tableFrame];
	
	
	showNum = (aRect.size.height-22) / PERROWHEIGHT;
	if (showNum <= 0) {
		showNum = 1;
	}
	[self setNeedsDisplay:YES];

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



-(void)singleClick:(id)sender{
	[[self window] makeFirstResponder:[self superview]];
}

-(void)segmentAction:(id)sender{
}

-(void)showTable:(NSMutableArray *)ansArray{
	self.m_tickData = ansArray;
	self.showFlag = TRUE;
	[self.myTableView reloadData];
	
	
	if ([m_tickData count]<1) 
		return;
}


- (void)drawRect:(NSRect)rect {
	CGContextRef context = [[NSGraphicsContext currentContext] graphicsPort];
	CGContextSetAllowsAntialiasing(context, FALSE);
	[[NSColor redColor] set];
	CGContextSetLineWidth(context, 0.6f);
	CGContextMoveToPoint(context, 0, 0);
	CGContextAddLineToPoint(context, rect.size.width-1, 0);
	
	CGContextStrokePath(context);
	CGContextSetAllowsAntialiasing(context, TRUE);
}

#pragma mark tableview 相关
-(void)singleTap{
	tapCount = 0;
}

-(void)doubleTap{
	[myDelegate showFullTick];
	tapCount = 0;
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
#pragma mark NSTableViewDelegate
-(BOOL) selectionShouldChangeInTableView:(NSTableView *)tableView{
	return NO;
}


#pragma mark NSTableViewDataSource Delegate

- (NSInteger)numberOfRowsInTableView:(NSTableView *)tableView;
{
	return [m_tickData count];
}

-(CGFloat) tableView:(NSTableView *)tableView heightOfRow:(NSInteger)row{
	return PERROWHEIGHT;
}


-(void)doubleClick:(id)sender{
}

- (id)tableView:(NSTableView *)tableView objectValueForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row;

{
	if (!self.showFlag) {
		return @"";
	}
	
	if (row >=[m_tickData count]) {
		return @"";
	}
	
	NSString * tempString;
	TickInfo * tickInfo = [m_tickData objectAtIndex:row];
	
	if ([[tableColumn identifier] isEqual:@"time"]) {
		return [self getTimeFromMinute:tickInfo.minute];
	}
	else if([[tableColumn identifier] isEqual:@"price"]){
		if(dataPre == 2)
			tempString = [NSString stringWithFormat:@"%.2f",tickInfo.nowPrice];
		else
			tempString = [NSString stringWithFormat:@"%.3f",tickInfo.nowPrice];
		
		return tempString;
	}
	else if([[tableColumn identifier] isEqual:@"vol"]){
		if(zsFlag){
			if (tickInfo.nowVol*100 > 100000000) {
				tempString = [NSString stringWithFormat:@"%.1f亿",tickInfo.nowVol*100.0f/100000000];
			}
			else if((tickInfo.nowVol*100 < 100000000)&&(tickInfo.nowVol*100 > 10000)) {
				tempString = [NSString stringWithFormat:@"%i万",tickInfo.nowVol*100/10000];
			}
			else {
				tempString = [NSString stringWithFormat:@"%i",tickInfo.nowVol*100];
			}
			
		}
		else{
			tempString = [NSString stringWithFormat:@"%i",tickInfo.nowVol];
		}
		
		return tempString;
	}
	else if([[tableColumn identifier] isEqual:@"flag"]){
		if(!zsFlag){
			if(tickInfo.inOutFlag == 1){
				tempString = @"S";
			}
			else if(tickInfo.inOutFlag == 0){
				tempString = @"B";
			}
			else {
				tempString = @"";
			}
		}
		else {
			tempString =@"";
		}

		return tempString;
	}
	return @"";
}

-(void)tableView:(NSTableView *)tableView willDisplayCell:(id)cell forTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row{
	if (!self.showFlag) {
		return;
	}
    if(row>=[m_tickData count])
        return;
	TickInfo * tickInfo = [m_tickData objectAtIndex:row];
	if ([[tableColumn identifier] isEqual:@"time"]) {
		[cell setTextColor:COLOR_GRID_COMMONCOLOR];
	}	
	else if ([[tableColumn identifier] isEqual:@"price"]) {
		[cell setTextColor:COLOR_GRID_COMMONCOLOR];
		[cell setAlignment:NSCenterTextAlignment];
		if(tickInfo.nowPrice > closep)
			[cell setTextColor:[NSColor redColor]];
		else if (tickInfo.nowPrice < closep)
			[cell setTextColor:HQCOLOR_DOWN];
		else 
			[cell setTextColor:COLOR_GRID_COMMONCOLOR];		
	}
	else if([[tableColumn identifier] isEqual:@"vol"]){
		[cell setAlignment:NSRightTextAlignment];
		[cell setTextColor:[NSColor yellowColor]];
	}
	else if([[tableColumn identifier] isEqual:@"flag"]){
		if(!zsFlag){
			if(tickInfo.inOutFlag == 1){
				[cell setTextColor:HQCOLOR_DOWN];
			}
			else if(tickInfo.inOutFlag == 0){
				[cell setTextColor:[NSColor redColor]];
			}
			else {
				[cell setTextColor:COLOR_GRID_COMMONCOLOR];
			}
		}
	}
}


- (void)dealloc {
	[myTableView release];
	[m_tickData release];
	
	[super dealloc];
}


@end
