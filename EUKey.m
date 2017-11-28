//
//  EUKey.m
//  tdxMac
//
//  Created by tdx on 11-9-15.
//  Copyright 2011 武汉. All rights reserved.
//

#define TEXTFIELD_HEIGHT 20
#define PERROWHEIGHT 18
#import "EUKey.h"


@implementation EUKey

@synthesize myTableView,m_keyData,myTextField,selectIndex;
 
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
        
        
		myTextField = [[NSTextField alloc]initWithFrame:NSMakeRect(0, frame.size.height -TEXTFIELD_HEIGHT ,frame.size.width, TEXTFIELD_HEIGHT)];
		[myTextField setEditable:NO];
		[[myTextField cell] setTitle:@""];
        
		
		[self addSubview:myTextField];
		
		
		NSScrollView * scrollView=[[NSScrollView alloc] initWithFrame:NSMakeRect(0,0,frame.size.width,frame.size.height - TEXTFIELD_HEIGHT)];
		[scrollView setHasHorizontalScroller:NO];
		[scrollView setHorizontalScroller:nil];
		[scrollView setHasVerticalScroller:NO];
		[scrollView setVerticalScroller:nil];
		[scrollView setDrawsBackground:NO];
		
		
		
		myTableView = [[NSTableView alloc] initWithFrame:NSMakeRect(0,0,frame.size.width,frame.size.height - TEXTFIELD_HEIGHT)];
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
		[myTableView setDoubleAction:@selector(doubleClick:)];
		[self addColumn:@"code" withTitle:@"" withWidth:70];
		[self addColumn:@"name" withTitle:@"" withWidth:100];
		[myTableView setDataSource:self];
		[myTableView setDelegate:self];
		
		
		[scrollView setDocumentView:myTableView];
		[scrollView setBackgroundColor:[NSColor blackColor]];
		[self addSubview:scrollView];
        scrollView.alphaValue=1.0f;
        
		[scrollView release];
		
        self.alphaValue=1.0f;
		selectIndex = -1;
	}
    return self;
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

- (void)drawRect:(NSRect)dirtyRect {
    [[NSColor whiteColor] set];
	NSRectFill(dirtyRect);

	if (selectIndex > -1) {
		[[NSColor blueColor] set];	
		NSRectFill(NSMakeRect(0, ABSOLUTE_VALUE(selectIndex -9)*(PERROWHEIGHT+2), dirtyRect.size.width, (PERROWHEIGHT+2)));
	}
}



#pragma mark NSTableViewDelegate
-(BOOL) selectionShouldChangeInTableView:(NSTableView *)tableView{
	return NO;
}


#pragma mark NSTableViewDataSource Delegate

- (NSInteger)numberOfRowsInTableView:(NSTableView *)tableView;
{
	return [m_keyData count];
}

-(CGFloat) tableView:(NSTableView *)tableView heightOfRow:(NSInteger)row{
	return PERROWHEIGHT;
}

-(void)singleClick:(id)sender{
	if ([myTableView clickedRow]  < 0) {
		return;
	}
	selectIndex = [myTableView clickedRow];
	[self setNeedsDisplay:YES];
	[[self window] makeFirstResponder:self];
}


-(void)doubleClick:(id)sender{
	if (([m_keyData count] < 1) || ([m_keyData count] < [myTableView clickedRow])){
		return;
	}
	ProcessInfo * tempInfo = [m_keyData objectAtIndex:[myTableView clickedRow]];
	if (tempInfo.typeID < 6100) {
		[operProcessDelegate getHQProcess:[NSString stringWithFormat:@"%@",tempInfo.gpcode] gpSetcode:tempInfo.setcode typeID:tempInfo.typeID pareOne:tempInfo.paraOne paraTwo:tempInfo.paraTwo];
	}
	else {
		[operProcessDelegate getTradeProcess:[NSString stringWithFormat:@"%@",tempInfo.gpcode] gpSetcode:tempInfo.setcode typeID:tempInfo.typeID pareOne:tempInfo.paraOne paraTwo:tempInfo.paraTwo pareThree:@""];
	}

	
}


- (id)tableView:(NSTableView *)tableView objectValueForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row;
{
    if(row>=[m_keyData count])
        return nil;
	ProcessInfo * stockInfo = [m_keyData objectAtIndex:row];
	
	if ([[tableColumn identifier] isEqual:@"code"]) {
		return stockInfo.showcode;
	}
	else if([[tableColumn identifier] isEqual:@"name"]){
		return stockInfo.gpname;
	}
	return nil;
}

-(void)tableView:(NSTableView *)tableView willDisplayCell:(id)cell forTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row{
	if (row >[m_keyData count]-1) {
		return;
	}
	[cell setTextColor:[NSColor redColor]];
	if ([[tableColumn identifier] isEqual:@"code"]) {
		[cell setAlignment:NSLeftTextAlignment];
	}
	else if([[tableColumn identifier] isEqual:@"name"]){
		[cell setAlignment:NSRightTextAlignment];
	}
}

#pragma mark 键盘事件相关
-(void) dealKeyBoardEvent:(NSEvent *)theEvent{
	switch ([theEvent keyCode]) {
		case MAC_KEY_ARROWDOWN:{
			selectIndex = selectIndex+1;
			if (selectIndex > [m_keyData count]-1) {
				selectIndex = 0;
			}
			
			[self setNeedsDisplay:YES];
		}
			break;
		case MAC_KEY_ARROWUP:{
			selectIndex = selectIndex-1;
			if (selectIndex < 0) {
				selectIndex = [m_keyData count]-1;
			}
			
			[self setNeedsDisplay:YES];
		}
			break;	
		case MAC_KEY_ENTER://回车
        case MAC_SKEY_ENTER://回车
		{
			if ([m_keyData count] <1) {
				[operProcessDelegate closeKeyBoard];
				return;
			}
			
			if (([m_keyData count] < 1) || ([m_keyData count] < selectIndex) || selectIndex <0){
				return;
			}
			ProcessInfo * tempInfo = [m_keyData objectAtIndex:selectIndex];
			if (tempInfo.typeID < 6100) {
				[operProcessDelegate getHQProcess:[NSString stringWithFormat:@"%@",tempInfo.gpcode] gpSetcode:tempInfo.setcode typeID:tempInfo.typeID pareOne:tempInfo.paraOne paraTwo:tempInfo.paraTwo];
			}
			else {
				[operProcessDelegate getTradeProcess:[NSString stringWithFormat:@"%@",tempInfo.gpcode] gpSetcode:tempInfo.setcode typeID:tempInfo.typeID pareOne:tempInfo.paraOne paraTwo:tempInfo.paraTwo pareThree:@""];
			}
		}
			break;
			
		default:
			break;
	}
}



#pragma mark  数据处理相关
-(void)searchTheStock{
	NSString * tempString = [[myTextField cell] title];
	if ([tempString length]<1) {
		return;
	}
	
	if (m_keyData != nil) {
		[m_keyData removeAllObjects];
		[m_keyData release],m_keyData = nil;
	}
	
	m_keyData = [[NSMutableArray alloc] init];
	[eGetData getSearchResult:tempString KeyArray:m_keyData];
	
	[myTableView reloadData];
	
	selectIndex = 0;
	[self setNeedsDisplay:YES];
}

-(void)OnReceiveData:(int)reqIndex FuncID:(int)_funcID HqResult:(HqResultData *)_hqResult{
	if (_hqResult.resultStat < 1) {
		return;
	}
	switch (reqIndex) {
		case PYXG_NREQ:{
			NSMutableDictionary * result = [[[NSMutableDictionary alloc]init] autorelease];
			[eGetData getPYXGAns:_hqResult Result:result];
			if (m_keyData != nil) {
				[m_keyData removeAllObjects];
				[m_keyData release],m_keyData = nil;
			}
			
			m_keyData = [[NSMutableArray alloc] initWithArray:[result objectForKey:@"STOCK"]];
			[myTableView reloadData];
		}	
			break;

		default:
			break;
	}
}

-(void) dealloc{
	[super dealloc];
	[myTableView release];
	[m_keyData release];
}

@end
