//
//  ETradeFuncListView.m
//  tdxMac
//
//  Created by tdx on 11-10-25.
//  Copyright 2011 武汉. All rights reserved.
//

#import "ETradeFuncListView.h"
#define PERROWHEIGHT 20

@implementation ETradeFuncListView
@synthesize funcList;
@synthesize scrollView;


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
		clickFlag = NO;
		viewRect = frame;
		segment = [[NSSegmentedControl alloc] initWithFrame:NSMakeRect(0, frame.size.height-30, frame.size.width, 26)];
#ifdef IMAC_ZSZQ
		[segment setSegmentCount:2];
		[segment setLabel:@"    股  票    " forSegment:0];
		[segment setLabel:@"    服  务    " forSegment:1];
#else

		[segment setSegmentCount:1];
        if (eGetData.clientinfos.m_bxyjyflag) //信用
        {
            [segment setLabel:@"    信  用    " forSegment:0];
        }
        else
        {
            [segment setLabel:@"    股  票    " forSegment:0];
        }
        [segment setWidth:frame.size.width-5 forSegment:0];
#endif
		[segment setSelectedSegment:0];
		[segment setTarget:self];
		[segment setAction:@selector(segmentClick:)];
		
		[self addSubview:segment];
		NSDictionary * funcInfoDict = [NSDictionary dictionaryWithContentsOfFile:[[NSBundle mainBundle] pathForResource:@"tradeFuncInfo" ofType: @"dict"]];
		if (eGetData.clientinfos.m_bxyjyflag)
        {
            funcInfoArray = [funcInfoDict objectForKey:@"xy"];
        }
        else
        {
            funcInfoArray = [funcInfoDict objectForKey:@"gp"];
        }
		rootNode = [[Node alloc] init];
		Node *newNode1 = nil, *newNode2 = nil;
		
		for (NSDictionary *tempDict in funcInfoArray)
		{
			newNode1 = [[Node alloc] init];
			newNode1.name = [tempDict objectForKey:@"Name"];
			newNode1.image = [tempDict objectForKey:@"Image"];
			newNode1.level = 1;
			NSArray * tempArray = [tempDict objectForKey:@"Children"];
			if ([tempArray count] > 0) {
				newNode1.isGroup = YES;
			}
			else {
				newNode1.isGroup = NO;
			}

			[rootNode.children addObject:newNode1];
			
			if ([tempArray count] > 0) {
				for (NSDictionary *tempDict2 in tempArray)
				{
					newNode2 = [[Node alloc] init];
					newNode2.name = [tempDict2 objectForKey:@"Name"];
					newNode2.image = [tempDict2 objectForKey:@"Image"];
					newNode2.level = 2;
					newNode2.isGroup = NO;
					[newNode1.children addObject:newNode2];
					[newNode2 release];
				}
			}	
			
			[newNode1 release];
		}
		
		
		serviceInfoArray = [funcInfoDict objectForKey:@"service"];
		serviceNode = [[Node alloc] init];
		
		for (NSDictionary *tempDict in serviceInfoArray)
		{
			newNode1 = [[Node alloc] init];
			newNode1.name = [tempDict objectForKey:@"Name"];
			newNode1.image = [tempDict objectForKey:@"Image"];
			newNode1.level = 1;
			NSArray * tempArray = [tempDict objectForKey:@"Children"];
			if ([tempArray count] > 0) {
				newNode1.isGroup = YES;
			}
			else {
				newNode1.isGroup = NO;
			}
			
			if ([newNode1.name length] >0) {
				[serviceNode.children addObject:newNode1];
			}
			

			[newNode1 release];
		}
		
		
		funcList = [[NSOutlineView alloc] initWithFrame:NSMakeRect(0, 0, frame.size.width, frame.size.height-30)];
		
		[funcList setHeaderView:nil];
		NSTableColumn *column=[[NSTableColumn alloc] init];
		[column setWidth:100];
		[column setEditable:NO];
		[funcList addTableColumn:column];
		
		[funcList setAutosaveTableColumns:NO];
		[funcList setAllowsEmptySelection:YES];
		[funcList setAllowsColumnSelection:NO];
		[funcList setAllowsColumnReordering:NO];
		[funcList setAllowsColumnResizing:NO];
		[funcList setRowHeight:PERROWHEIGHT];
		[funcList setIndentationPerLevel:5.0];
		[funcList enclosingScrollView];
		[funcList setFocusRingType:1];
		[funcList setSelectionHighlightStyle:NSTableViewSelectionHighlightStyleRegular];

		
		[funcList setDataSource:self];
		[funcList setDelegate:self];
		[funcList reloadData];
		[funcList setNeedsDisplay:YES];
		[funcList setTarget:self];
		[funcList setAction:@selector(singleClick:)];
		[funcList setDoubleAction:@selector(doubleClick:)];
		
		scrollView=[[NSScrollView alloc] initWithFrame:NSMakeRect(0, 0, frame.size.width, frame.size.height-30)];
		[scrollView setHasHorizontalScroller:NO];
		[scrollView setHorizontalScroller:nil];
		[scrollView setHasVerticalScroller:YES];
		[scrollView setDrawsBackground:NO];
		
		[scrollView setDocumentView:funcList];
		[scrollView setBackgroundColor:[NSColor clearColor]];
		[self addSubview:scrollView];
	}
	return self;
}


-(void)segmentClick:(id)sender{
	if ([segment selectedSegment] == 1) {
		[funcList selectRowIndexes:[NSIndexSet indexSetWithIndex:6] byExtendingSelection:NO];
	}
	
	[funcList reloadData];
	if ([segment selectedSegment] == 0) {
		Node * node = (Node *)[rootNode.children objectAtIndex:3];
		if (node.level == 1) {
			if (node.isGroup) {
				if ([funcList isItemExpanded:node]) {
				}
				else {
				[funcList expandItem:node];
				}
			}
		}
		node = (Node *)[rootNode.children objectAtIndex:4];
		if (node.level == 1) {
			if (node.isGroup) {
				if ([funcList isItemExpanded:node]) {
					;
				}
				else {
				[funcList expandItem:node];
				}
			}
		}
	}
}


-(void)dealSelect:(int)_type ParaOne:(int)_para{
	if ([segment selectedSegment] != 0 ) {
		[segment selectSegmentWithTag:0];
		[funcList reloadData];
	}
    
    //信用交易添加
    int xyjy = 0;
    int xyjyZK = 0; //展开
    if (eGetData.clientinfos.m_bxyjyflag)
    {
        xyjy = 7;
        xyjyZK = 2;
    }
    
	switch (_type) {
        case MAC_WT_FUNC://下单
            eGetData.tradeType = _para;
            [funcList selectRowIndexes:[NSIndexSet indexSetWithIndex:_para] byExtendingSelection:NO];
            
        break;
		case MAC_TRADE_FUNC:{
			if (_para == TDX_GDCX){
				int tempInt = 0;
				Node * node = (Node *)[rootNode.children objectAtIndex:3+xyjy];
				
				if (node.level == 1) {
					if (node.isGroup) {
						if ([funcList isItemExpanded:node]) {
							tempInt = tempInt+8+xyjyZK;
						}
						else {
						}
					}
				}
				node = (Node *)[rootNode.children objectAtIndex:4+xyjy];
				if (node.level == 1) {
					if (node.isGroup) {
						if ([funcList isItemExpanded:node]) {
							tempInt = tempInt+3;
						}
						else {
						}
					}
				}
				
				[funcList selectRowIndexes:[NSIndexSet indexSetWithIndex:5+tempInt] byExtendingSelection:NO];
				return;
			}
			
			Node * node = (Node *)[rootNode.children objectAtIndex:3+xyjy];
			if (node.level == 1) {
				if (node.isGroup) {
					if ([funcList isItemExpanded:node]) {
						;
					}
					else {
						//[funcList expandItem:node];
					}
				}
			}
            
           
            
			if (_para == TDX_GFCX) {
				[funcList selectRowIndexes:[NSIndexSet indexSetWithIndex:4+xyjy] byExtendingSelection:NO];
			}
			else if (_para == TDX_DRCJ){
				[funcList selectRowIndexes:[NSIndexSet indexSetWithIndex:6+xyjy] byExtendingSelection:NO];
			}
			else if (_para == TDX_LSWT){
				[funcList selectRowIndexes:[NSIndexSet indexSetWithIndex:7+xyjy] byExtendingSelection:NO];
			}
			else if (_para == TDX_LSCJ){
				[funcList selectRowIndexes:[NSIndexSet indexSetWithIndex:8+xyjy] byExtendingSelection:NO];
			}
			else if (_para == TDX_CJHZ){
				[funcList selectRowIndexes:[NSIndexSet indexSetWithIndex:9+xyjy] byExtendingSelection:NO];
			}
			else if (_para == TDX_ZJLS){
				[funcList selectRowIndexes:[NSIndexSet indexSetWithIndex:10+xyjy] byExtendingSelection:NO];
			}	
			else if (_para == TDX_PHCX){
				[funcList selectRowIndexes:[NSIndexSet indexSetWithIndex:11+xyjy] byExtendingSelection:NO];
			}
			else if (_para == TDX_IPOSGED){
				[funcList selectRowIndexes:[NSIndexSet indexSetWithIndex:12+xyjy] byExtendingSelection:NO];
			}
            else if(_para == TDX_KSGXGCX)
            {
                [funcList selectRowIndexes:[NSIndexSet indexSetWithIndex:15+xyjy] byExtendingSelection:NO];
            }
            else if (_para == TDX_XYSXCX){
                [funcList selectRowIndexes:[NSIndexSet indexSetWithIndex:12+xyjy] byExtendingSelection:NO];
            }
            else if (_para == TDX_DBPHZCD){
                [funcList selectRowIndexes:[NSIndexSet indexSetWithIndex:13+xyjy] byExtendingSelection:NO];
            }
            else if (_para == TDX_DBPHZCX){
                [funcList selectRowIndexes:[NSIndexSet indexSetWithIndex:14+xyjy] byExtendingSelection:NO];
            }
		}
			break;
		case MAC_CANCEL_FUNC:
			if (_para == TDX_CDCX) {
				[funcList selectRowIndexes:[NSIndexSet indexSetWithIndex:2+xyjy] byExtendingSelection:NO];
			}
            else if(_para == TDX_DBPHZCD)
            {
                [funcList selectRowIndexes:[NSIndexSet indexSetWithIndex:3+xyjy] byExtendingSelection:NO];
            }
			else if (_para == TDX_DRWT){
				Node * node = (Node *)[rootNode.children objectAtIndex:3];
				if (node.level == 1) {
					if (node.isGroup) {
						if ([funcList isItemExpanded:node]) {
						}
						else {
							[funcList expandItem:node];
						}
					}
				}
				
				[funcList selectRowIndexes:[NSIndexSet indexSetWithIndex:5+xyjy] byExtendingSelection:NO];
				
			}
			break;
		case MAC_BANK_FUNC:{
			Node * node = (Node *)[rootNode.children objectAtIndex:3+xyjy];
			int tempInt=0 ;
			if (node.level == 1) {
				if (node.isGroup) {
					if ([funcList isItemExpanded:node]) {
						tempInt= 8+xyjyZK;
					}
					else {
						tempInt=0+xyjyZK;
					}
				}
			}
			node = (Node *)[rootNode.children objectAtIndex:4+xyjy];
			if (node.level == 1) {
				if (node.isGroup) {
					if ([funcList isItemExpanded:node]) {
					}
					else {
						[funcList expandItem:node];
					}
				}
			}
			
			if (_para == TDX_YZZZ) {
				[funcList selectRowIndexes:[NSIndexSet indexSetWithIndex:5+tempInt+xyjy] byExtendingSelection:NO];
			}
			else if (_para == TDX_YECX){
				[funcList selectRowIndexes:[NSIndexSet indexSetWithIndex:6+tempInt] byExtendingSelection:NO];
				
			}
			else if (_para == TDX_ZZCX){
				[funcList selectRowIndexes:[NSIndexSet indexSetWithIndex:7+tempInt] byExtendingSelection:NO];
				
			}
			else if (_para == TDX_PT_ZJZZ){
                [funcList selectRowIndexes:[NSIndexSet indexSetWithIndex:8+tempInt] byExtendingSelection:NO];
            }
		}
			break;
		case MAC_PASSWORD_FUNC:{
			int tempInt = 0;
			Node * node = (Node *)[rootNode.children objectAtIndex:3+xyjy];
			
			if (node.level == 1) {
				if (node.isGroup) {
					if ([funcList isItemExpanded:node]) {
							tempInt = tempInt+8+xyjyZK;
					}
					else {
					}
				}
			}
			node = (Node *)[rootNode.children objectAtIndex:4+xyjy];
			if (node.level == 1) {
				if (node.isGroup) {
					if ([funcList isItemExpanded:node]) {
						tempInt = tempInt+3;
					}
					else {
					}
				}
			}
			
			[funcList selectRowIndexes:[NSIndexSet indexSetWithIndex:6+tempInt] byExtendingSelection:NO];
		}	
			break;
        case MAC_REFRESH_FUNC:
        {
            
        }
            break;
		default:
			break;
	}
	
}

-(void)test:(NSString * )_para{
	int tempInt = [_para intValue];
	if (tempInt == TDX_YZZZ) {
		[funcList selectRowIndexes:[NSIndexSet indexSetWithIndex:5+tempInt] byExtendingSelection:NO];
	}
	else if (tempInt == TDX_YECX){
		[funcList selectRowIndexes:[NSIndexSet indexSetWithIndex:6+tempInt] byExtendingSelection:NO];
		
	}
	else if (tempInt == TDX_ZZCX){
		[funcList selectRowIndexes:[NSIndexSet indexSetWithIndex:7+tempInt] byExtendingSelection:NO];
	}	
}

-(void)doubleClick:(id)sender{
	//NSLog(@"doubleClick");
}

-(void)singleClick:(id)sender{
	
	if (clickFlag) {
		clickFlag = NO;
		return;
	}
	else {
		[[self window] makeFirstResponder:[self superview]];
		Node *node ;
		node = (Node *)[funcList itemAtRow:[funcList selectedRow]];
		if (node.level == 1) {
			if (node.isGroup) {
				if ([funcList isItemExpanded:node]) {
					[funcList collapseItem:node];
				}
				else {
					[funcList expandItem:node];
				}
			}
		}
	}

	
}

-(id) setFrame:(NSRect)frameRect{
    [super setFrame:frameRect];
    viewRect = frameRect;
    [self dealBarView];
    return nil;
}

-(void)dealBarView{
    [scrollView setFrame:NSMakeRect(0, viewRect.origin.y-40, viewRect.size.width, viewRect.size.height)];
//    [segment setFrame:NSMakeRect(0, viewRect.origin.y-30, viewRect.size.width, 26)];
}

#pragma mark  OutLineView Data Source methods

- (NSInteger)outlineView:(NSOutlineView *)outlineView numberOfChildrenOfItem:(id)item
{
	Node *node;
	if ([segment selectedSegment] == 0) {
		node = (item == nil ? rootNode : (Node *)item);
	}
	else if ([segment selectedSegment] == 1){
		node = (item == nil ? serviceNode : (Node *)item);
	}

	
	return [node.children count];
}

- (id)outlineView:(NSOutlineView *)outlineView child:(NSInteger)index ofItem:(id)item
{
	Node *node;
	if ([segment selectedSegment] == 0) {
		node = (item == nil ? rootNode : (Node *)item);
	}
	else if ([segment selectedSegment] == 1){
		node = (item == nil ? serviceNode : (Node *)item);
	}
	return [node.children objectAtIndex:index];
}

- (BOOL)outlineView:(NSOutlineView *)outlineView isItemExpandable:(id)item
{
	if (item == nil) {
		return YES;
	}
	else {
		Node *node = (Node *)item;
		
		return node.isGroup;
	}

	
}

- (id)outlineView:(NSOutlineView *)outlineView objectValueForTableColumn:(NSTableColumn *)tableColumn byItem:(id)item
{
    tableColumn.width = funcList.frame.size.width;
	Node *node = (Node *)item;
	return node.name;
}

- (BOOL)outlineView:(NSOutlineView *)outlineView shouldEditTableColumn:(NSTableColumn *)tableColumn item:(id)item {
    return YES;
}

-(BOOL) outlineView:(NSOutlineView *)outlineView shouldExpandItem:(id)item{
	return YES;
}

-(void) outlineViewSelectionDidChange:(NSNotification *)notification{
}

-(BOOL) outlineView:(NSOutlineView *)outlineView shouldSelectItem:(id)item{
	
	clickFlag = YES;
	Node *node = (Node *)item;
	if (node.level == 1) {
		if (node.isGroup) {
			if ([funcList isItemExpanded:node]) {
				[funcList collapseItem:node];
			}
			else {
				[funcList expandItem:node];
			}
		}
	}
	else {
		;
	}

	
	if ([node.name isEqualToString:@"买入"]) {
         eGetData.tradeType = DBPBuy;
		[operProcessDelegate getTradeProcess:@"" gpSetcode:-1 typeID:MAC_WT_FUNC pareOne:0 paraTwo:01 pareThree:@""];
	}
	else if ([node.name isEqualToString:@"卖出"]) {
        eGetData.tradeType = DBPSell;
		[operProcessDelegate getTradeProcess:@"" gpSetcode:-1 typeID:MAC_WT_FUNC pareOne:1 paraTwo:01 pareThree:@""];
	}
    else if ([node.name isEqualToString:@"担保品买入"]) {
        
        eGetData.tradeType = DBPBuy;
       [operProcessDelegate getTradeProcess:@"" gpSetcode:-1 typeID:MAC_WT_FUNC pareOne:DBPBuy paraTwo:01 pareThree:@""];
    }
    else if ([node.name isEqualToString:@"担保品卖出"]) {
        
        eGetData.tradeType = DBPSell;
        [operProcessDelegate getTradeProcess:@"" gpSetcode:-1 typeID:MAC_WT_FUNC pareOne:DBPSell paraTwo:01 pareThree:@""];
    }
    else if ([node.name isEqualToString:@"融资买入"]) {
        
        eGetData.tradeType = RZBuy;
        [operProcessDelegate getTradeProcess:@"" gpSetcode:-1 typeID:MAC_WT_FUNC pareOne:RZBuy paraTwo:01 pareThree:@""];
    }
    else if ([node.name isEqualToString:@"融券卖出"]) {
        
        eGetData.tradeType = RZSell;
        [operProcessDelegate getTradeProcess:@"" gpSetcode:-1 typeID:MAC_WT_FUNC pareOne:RZSell paraTwo:01 pareThree:@""];
    }
    else if ([node.name isEqualToString:@"担保品划转"]){
        eGetData.tradeType = DBPHZ;
        [operProcessDelegate getTradeProcess:@"" gpSetcode:-1 typeID:MAC_WT_FUNC pareOne:DBPHZ paraTwo:01 pareThree:@""];
    }
    else if ([node.name isEqualToString:@"担保品划转撤单"]){
        
        eGetData.tradeType = DBPBuy;
        [operProcessDelegate getTradeProcess:@"" gpSetcode:-1 typeID:MAC_TRADE_FUNC pareOne:TDX_DBPHZCD paraTwo:01 pareThree:@""];
        
        
    }
    else if ([node.name isEqualToString:@"担保品划转查询"]){
        eGetData.tradeType = DBPBuy;
        [operProcessDelegate getTradeProcess:@"" gpSetcode:-1 typeID:MAC_TRADE_FUNC pareOne:TDX_DBPHZCX paraTwo:01 pareThree:@""];
    }
    else if ([node.name isEqualToString:@"卖券还款"]) {
        
        eGetData.tradeType = MQHK;
        [operProcessDelegate getTradeProcess:@"" gpSetcode:-1 typeID:MAC_WT_FUNC pareOne:MQHK paraTwo:01 pareThree:@""];
    }
    else if ([node.name isEqualToString:@"买券还券"]) {
        
        eGetData.tradeType = MQHQ;
        [operProcessDelegate getTradeProcess:@"" gpSetcode:-1 typeID:MAC_WT_FUNC pareOne:MQHQ paraTwo:TDX_XYMQHQCX pareThree:@""];
    }
    else if ([node.name isEqualToString:@"现金还款"]) {
        
        eGetData.tradeType = XJHK;
        [operProcessDelegate getTradeProcess:@"" gpSetcode:-1 typeID:MAC_WT_FUNC pareOne:XJHK paraTwo:TDX_XYXJHKCX pareThree:@""];
    }
    else if ([node.name isEqualToString:@"现券还券"]) {
        
        eGetData.tradeType = XQHQ;
        [operProcessDelegate getTradeProcess:@"" gpSetcode:-1 typeID:MAC_WT_FUNC pareOne:XQHQ paraTwo:TDX_XYXQHQCX pareThree:@""];
    }
	else if ([node.name isEqualToString:@"撤单"]){
		[operProcessDelegate getTradeProcess:@"" gpSetcode:-1 typeID:MAC_CANCEL_FUNC pareOne:TDX_CDCX paraTwo:01 pareThree:@""];
	}
	else if ([node.name isEqualToString:@"资金股份"]){
        eGetData.tradeType = DBPBuy;
		[operProcessDelegate getTradeProcess:@"" gpSetcode:-1 typeID:MAC_TRADE_FUNC pareOne:TDX_GFCX paraTwo:01 pareThree:@""];
	}
	else if ([node.name isEqualToString:@"当日委托"]){
        eGetData.tradeType = DBPBuy;
		[operProcessDelegate getTradeProcess:@"" gpSetcode:-1 typeID:MAC_CANCEL_FUNC pareOne:TDX_DRWT paraTwo:01 pareThree:@""];
	}
	else if ([node.name isEqualToString:@"当日成交"]){
        eGetData.tradeType = DBPBuy;
		[operProcessDelegate getTradeProcess:@"" gpSetcode:-1 typeID:MAC_TRADE_FUNC pareOne:TDX_DRCJ paraTwo:01 pareThree:@""];
	}
	else if ([node.name isEqualToString:@"历史委托"]){
        eGetData.tradeType = DBPBuy;
		[operProcessDelegate getTradeProcess:@"" gpSetcode:-1 typeID:MAC_TRADE_FUNC pareOne:TDX_LSWT paraTwo:01 pareThree:@""];
	}
	else if ([node.name isEqualToString:@"历史成交"]){
        eGetData.tradeType = DBPBuy;
		[operProcessDelegate getTradeProcess:@"" gpSetcode:-1 typeID:MAC_TRADE_FUNC pareOne:TDX_LSCJ paraTwo:01 pareThree:@""];
	}
	else if ([node.name isEqualToString:@"成交汇总"]){
        eGetData.tradeType = DBPBuy;
		[operProcessDelegate getTradeProcess:@"" gpSetcode:-1 typeID:MAC_TRADE_FUNC pareOne:TDX_CJHZ paraTwo:01 pareThree:@""];
	}
	else if ([node.name isEqualToString:@"资金流水"]){
        eGetData.tradeType = DBPBuy;
		[operProcessDelegate getTradeProcess:@"" gpSetcode:-1 typeID:MAC_TRADE_FUNC pareOne:TDX_ZJLS paraTwo:01 pareThree:@""];
	}
    else if ([node.name isEqualToString:@"新股申购"]){ //新加
        eGetData.tradeType = DBPBuy;
        [operProcessDelegate getTradeProcess:@"" gpSetcode:-1 typeID:MAC_WT_FUNC pareOne:XGSG paraTwo:TDX_XGSG pareThree:@""];
    }
    else if ([node.name isEqualToString:@"    可申购新股查询"]){
        eGetData.tradeType = DBPBuy;
        [operProcessDelegate getTradeProcess:@"" gpSetcode:-1 typeID:MAC_TRADE_FUNC pareOne:TDX_KSGXGCX paraTwo:01 pareThree:@""];
    }
	else if ([node.name isEqualToString:@"配号查询"]){
        eGetData.tradeType = DBPBuy;
		[operProcessDelegate getTradeProcess:@"" gpSetcode:-1 typeID:MAC_TRADE_FUNC pareOne:TDX_PHCX paraTwo:01 pareThree:@""];
	}
    else if ([node.name isEqualToString:@"中签查询"]){
        eGetData.tradeType = ZQCX;
        [operProcessDelegate getTradeProcess:@"" gpSetcode:-1 typeID:MAC_TRADE_FUNC pareOne:ZQCX paraTwo:TDX_XGZQCX pareThree:@""];
    }
    else if ([node.name isEqualToString:@"    新股申购额度查询"]){
        eGetData.tradeType = DBPBuy;
		[operProcessDelegate getTradeProcess:@"" gpSetcode:-1 typeID:MAC_TRADE_FUNC pareOne:TDX_IPOSGED paraTwo:01 pareThree:@""];
	}
	else if ([node.name isEqualToString:@"股东查询"]){
        eGetData.tradeType = DBPBuy;
		[operProcessDelegate getTradeProcess:@"" gpSetcode:-1 typeID:MAC_TRADE_FUNC pareOne:TDX_GDCX paraTwo:01 pareThree:@""];
	}
    else if ([node.name isEqualToString:@"    信用资产查询"]){
        eGetData.tradeType = XYZCCX;
        [operProcessDelegate getTradeProcess:@"" gpSetcode:-1 typeID:MAC_TRADE_FUNC pareOne:TDX_XYZCCX paraTwo:01 pareThree:@""];
    }
    else if ([node.name isEqualToString:@"    信用融资合约查询"]){
        eGetData.tradeType = XYRZHYCX;
        [operProcessDelegate getTradeProcess:@"" gpSetcode:-1 typeID:MAC_TRADE_FUNC pareOne:TDX_XYRZHYCX paraTwo:01 pareThree:@""];
    }
    else if ([node.name isEqualToString:@"    信用合约查询"]){
        eGetData.tradeType = XYRZHYCX;
        [operProcessDelegate getTradeProcess:@"" gpSetcode:-1 typeID:MAC_TRADE_FUNC pareOne:TDX_XYRZHYCX paraTwo:01 pareThree:@""];
    }
    else if ([node.name isEqualToString:@"    信用融券合约查询"]){
        eGetData.tradeType = XYRQHYCX;
        [operProcessDelegate getTradeProcess:@"" gpSetcode:-1 typeID:MAC_TRADE_FUNC pareOne:TDX_XYRQHYCX paraTwo:01 pareThree:@""];
    }
    else if ([node.name isEqualToString:@"    信用负债查询"]){
        eGetData.tradeType = XYFZCX;
        [operProcessDelegate getTradeProcess:@"" gpSetcode:-1 typeID:MAC_TRADE_FUNC pareOne:TDX_XYFZCX paraTwo:01 pareThree:@""];
    }
    else if ([node.name isEqualToString:@"    信用上限查询"]){
        eGetData.tradeType = XYSXCX;
        [operProcessDelegate getTradeProcess:@"" gpSetcode:-1 typeID:MAC_TRADE_FUNC pareOne:TDX_XYSXCX paraTwo:01 pareThree:@""];
    }
    else if ([node.name isEqualToString:@"    标的证券查询"]){
        eGetData.tradeType = RZBuy;
        [operProcessDelegate getTradeProcess:@"" gpSetcode:-1 typeID:MAC_TRADE_FUNC pareOne:TDX_XYBDZQCX paraTwo:01 pareThree:@""];
    }
    else if ([node.name isEqualToString:@"    担保品证券查询"]){
        eGetData.tradeType = DBPZQCX;
        [operProcessDelegate getTradeProcess:@"" gpSetcode:-1 typeID:MAC_TRADE_FUNC pareOne:TDX_XYDBPZQCX paraTwo:01 pareThree:@""];
    }
	else if ([node.name isEqualToString:@"银证转账"]){
        eGetData.tradeType = DBPBuy;
		[operProcessDelegate getTradeProcess:@"" gpSetcode:-1 typeID:MAC_BANK_FUNC pareOne:TDX_YZZZ paraTwo:01 pareThree:@""];
	}
	else if ([node.name isEqualToString:@"银行余额"]){
        eGetData.tradeType = DBPBuy;
		[operProcessDelegate getTradeProcess:@"" gpSetcode:-1 typeID:MAC_BANK_FUNC pareOne:TDX_YECX paraTwo:01 pareThree:@""];
	}
    else if ([node.name isEqualToString:@"资金转账"]){
        eGetData.tradeType = DBPBuy;
        [operProcessDelegate getTradeProcess:@"" gpSetcode:-1 typeID:MAC_BANK_FUNC pareOne:TDX_PT_ZJZZ paraTwo:01 pareThree:@""];
    }
	else if ([node.name isEqualToString:@"转账查询"]){
        eGetData.tradeType = DBPBuy;
		[operProcessDelegate getTradeProcess:@"" gpSetcode:-1 typeID:MAC_BANK_FUNC pareOne:TDX_ZZCX paraTwo:01 pareThree:@""];
	}
	else if ([node.name isEqualToString:@"股东列表"]){
        eGetData.tradeType = DBPBuy;
		[operProcessDelegate getTradeProcess:@"" gpSetcode:-1 typeID:MAC_TRADE_FUNC pareOne:TDX_GDCX paraTwo:01 pareThree:@""];
	}
	else if ([node.name isEqualToString:@"修改密码"]){
		[operProcessDelegate getTradeProcess:@"" gpSetcode:-1 typeID:MAC_PASSWORD_FUNC pareOne:TDX_GDCX paraTwo:01 pareThree:@""];
	}
	else if ([node.name isEqualToString:@"智远理财"]){
		[operProcessDelegate getHQProcess:@"http://news.newone.com.cn/newone/service/zhuoyue/index.htm" gpSetcode:-1 typeID:MAC_WEB_FUNC pareOne:-1 paraTwo:-1];
	}
	else if ([node.name isEqualToString:@"专家在线"]){
		[operProcessDelegate getHQProcess:[NSString stringWithFormat:@"http://www.newone.com.cn/newone/expert/nodelist_showa_zyb.jsp?khh=%@",eGetData.inputSave.accout] gpSetcode:-1 typeID:MAC_WEB_FUNC pareOne:-1 paraTwo:-1];
	}
	else if ([node.name isEqualToString:@"我的投资顾问"]){
		[operProcessDelegate getHQProcess:[NSString stringWithFormat:@"http://www.newone.com.cn/mytzgw?khh=%@",eGetData.inputSave.accout] gpSetcode:-1 typeID:MAC_WEB_FUNC pareOne:-1 paraTwo:-1];
	}
	else if ([node.name isEqualToString:@"短信理财通"]){
		[operProcessDelegate getHQProcess:@"http://www.newone.com.cn/sms" gpSetcode:-1 typeID:MAC_WEB_FUNC pareOne:-1 paraTwo:-1];
	}
	else if ([node.name isEqualToString:@"E号通"]){
		[operProcessDelegate getHQProcess:@"http://www.newone.com.cn/ws/html?arg=2personal/95565/index" gpSetcode:-1 typeID:MAC_WEB_FUNC pareOne:-1 paraTwo:-1];
	}
	else if ([node.name isEqualToString:@"软件操作向导"]){
		[operProcessDelegate getHQProcess:@"http://news.newone.com.cn/newone/zhuanyeban/mac/index.html" gpSetcode:-1 typeID:MAC_WEB_FUNC pareOne:-1 paraTwo:-1];
	}
	
	return YES;
}

- (void)drawRect:(NSRect)dirtyRect {
    // Drawing code here.
	[BGCOLOR_GRAY set];
	NSRectFill(NSMakeRect(0, dirtyRect.size.height -30, dirtyRect.size.width, 30));
	
}


-(void) outlineView:(NSOutlineView *)outlineView willDisplayCell:(id)cell forTableColumn:(NSTableColumn *)tableColumn item:(id)item{
	Node *node = (Node *)item;
	
	if (node.image != nil) {
		ImageAndTextCell *imageAndTextCell = (ImageAndTextCell *)cell;
        [imageAndTextCell setImage:[NSImage imageNamed:node.image]];
		
	}
	if (node.level == 1) {
		[cell setTitle:[NSString stringWithFormat:@"    %@",node.name]];
		if ([node.name isEqualToString:@"查询"]) {
			if ([funcList isItemExpanded:node]) {
				[cell setTitle:[NSString stringWithFormat:@"－ %@",node.name]];
			}
			else {
				[cell setTitle:[NSString stringWithFormat:@"＋ %@",node.name]];
			}
		}
        if ([node.name isEqualToString:@"新股申购 "]) {
            if ([funcList isItemExpanded:node]) {
                [cell setTitle:[NSString stringWithFormat:@"－ %@",node.name]];
            }
            else {
                [cell setTitle:[NSString stringWithFormat:@"＋ %@",node.name]];
            }
        }
		
		if ([node.name isEqualToString:@"银证业务"]) {
			if ([funcList isItemExpanded:node]) {
				[cell setTitle:[NSString stringWithFormat:@"－ %@",node.name]];
			}
			else {
				[cell setTitle:[NSString stringWithFormat:@"＋ %@",node.name]];
			}
		}	
	}
	else if(node.level == 2){
        if([node.name length]==4)
            [cell setTitle:[NSString stringWithFormat:@"       %@",node.name]];
        else
            [cell setTitle:[NSString stringWithFormat:@"   %@",node.name]];
	}
	
}


-(void) dealloc{
	[rootNode release];
	[funcList release];
	[super dealloc];
}

@end
