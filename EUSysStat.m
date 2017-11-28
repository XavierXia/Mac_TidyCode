//
//  EUSysStat.m
//  tdxMac
//
//  Created by tdx on 11-12-13.
//  Copyright 2011 武汉. All rights reserved.
//

#import "EUSysStat.h"

#define PERROWHEIGHT 20

@implementation EUSysStat
@synthesize showDelegate,myTableView;

- (id)initWithData:(NSRect)aRect theData:(EGetData *)_eGetData{
    if ((self = [super initWithData:aRect theData:_eGetData])) {
        // Initialization code
		self.eGetData = _eGetData;
#ifdef IMAC_TDX
        titleArray = [[NSMutableArray alloc] initWithObjects:@"程序名",@"行情主站",nil] ;
#else
		titleArray = [[NSMutableArray alloc] initWithObjects:@"程序名",@"行情主站",@"行情地址",@"交易主站",@"交易地址",nil] ;
#endif
		
		cancelButton = [[NSButton alloc] initWithFrame:NSMakeRect(aRect.size.width-70, 0, 60, 30)];
		[[cancelButton cell] setTitle:@"关 闭"];
		[cancelButton setBordered:YES];
		[cancelButton setBezelStyle:3];
		[cancelButton setTarget:self];
		[cancelButton setAction:@selector(cancelButtonClick)];
		[self addSubview:cancelButton];
		
		NSRect tableFrame;
		tableFrame.origin.x = 1;
		tableFrame.origin.y = 30;
		tableFrame.size.width = aRect.size.width;
		tableFrame.size.height = aRect.size.height-30;
		
		scrollView=[[NSScrollView alloc] initWithFrame:tableFrame];
		[scrollView setHasHorizontalScroller:NO];
		[scrollView setHorizontalScroller:nil];
		[scrollView setHasVerticalScroller:NO];
		[scrollView setVerticalScroller:nil];
		[scrollView setDrawsBackground:NO];
		
		
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
		
		[self addColumn:@"name" withTitle:@"" withWidth:70];
		[self addColumn:@"value" withTitle:@"" withWidth:220];
		[myTableView setDataSource:self];
		[myTableView setDelegate:self];
		
		[scrollView setDocumentView:myTableView];
		[scrollView setBackgroundColor:[NSColor clearColor]];
		[self addSubview:scrollView];
		[scrollView release];
		
    }
    return self;
}

-(void)cancelButtonClick
{
	[showDelegate closeSysStat];
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
#pragma mark NSTableViewDataSource Delegate
- (NSInteger)numberOfRowsInTableView:(NSTableView *)aTableView
{
	return [titleArray count];
}

-(CGFloat) tableView:(NSTableView *)tableView heightOfRow:(NSInteger)row{
	return PERROWHEIGHT;
}


- (id)tableView: (NSTableView *)theTableView objectValueForTableColumn: (NSTableColumn *)theColumn row: (NSInteger)rowIndex
{
	TradeSite *pSite;

	if ([[theColumn identifier] isEqual:@"name"]) {
        if(rowIndex<[titleArray count])
            return [titleArray objectAtIndex:rowIndex];
        else
            return @"";
	}
	else if([[theColumn identifier] isEqual:@"value"]){
		if (rowIndex  == 0) {
			return MAC_TITLETIP;
		}
		else if(rowIndex == 1){
			pSite  = [eGetData GetHqLoginSite:YES];
			if (eGetData.g_pEComm.connFlag) {
				return pSite.sname;
			}
			else {
				return @"未连接行情主站";
			}

		}
		else if(rowIndex == 2){
#ifdef IMAC_TDX
            return @"(通达信)深圳市财富趋势科技股份有限公司";
#else
			pSite  = [eGetData GetHqLoginSite:YES];
			if (eGetData.g_pEComm.connFlag) {
				return [NSString stringWithFormat:@"%@(%i)",pSite.ip,pSite.nport];
			}
			else {
				return @"";
			}
#endif
		}
		else if(rowIndex == 3){
			pSite  = [eGetData GetJyLoginSite:YES];
			if (eGetData.g_TradeComm.m_bconokflag) {
				return pSite.sname;
			}
			else {
				return @"未连接交易主站";
			}
			
		}
		else if(rowIndex == 4){
			pSite  = [eGetData GetJyLoginSite:YES];
			if (eGetData.g_TradeComm.m_bconokflag) {
				return [NSString stringWithFormat:@"%@(%i)",pSite.ip,pSite.nport];
			}
			else {
				return @"";
			}
			
		}
	}
	return @"";
}

-(void)tableView:(NSTableView *)tableView willDisplayCell:(id)cell forTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row{

	if ([[tableColumn identifier] isEqual:@"name"]) {
		[cell setAlignment:NSLeftTextAlignment];
	}
	else if([[tableColumn identifier] isEqual:@"value"]){
		[cell setAlignment:NSRightTextAlignment];
	}
}


-(void) keyUp:(NSEvent *)theEvent{
	switch ([theEvent keyCode]) {
		case MAC_KEY_ENTER:
        case MAC_SKEY_ENTER:
		case MAC_KEY_ESC:
			[showDelegate closeSysStat];
		default:
			break;

	}
}

- (void)dealloc {
	[myTableView release];
	[scrollView release];
	[titleArray release];
    [super dealloc];
}

- (void)drawRect:(NSRect)dirtyRect {
}

@end
