//
//  ETradeUserInfoView.m
//  tdxMac
//
//  Created by tdx on 11-10-28.
//  Copyright 2011 武汉. All rights reserved.
//

#import "ETradeUserInfoView.h"

#define TITLE_HEIGHT 16
#define PERROWHEIGHT 20
#define BARVIEW_HEIGHT 25
#define itemTag 1405
#define titleTag 1905
@implementation ETradeUserInfoView
@synthesize tag,toolbarShowFlag;

- (id)initWithFrame:(NSRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code here.
    }
    return self;
}

- (void)drawRect:(NSRect)dirtyRect {
   
}

-(id) setFrame:(NSRect)frameRect{
	[super setFrame:frameRect];
	viewRect = frameRect;
	[self dealBarView];
	[self resetToolbar];
	return nil;
}

- (id)initWithData:(NSRect)frame theData:(EGetData *)_eGetData WithTag:(int)_wtTag{
    self = [super initWithData:frame theData:_eGetData];
    if (self) {
		self.tradeindex = [_eGetData.g_TradeComm.areceiver SetWinobjs:self];
		viewRect = frame;
		showDataArray = [[NSMutableArray alloc] init];
		
		WTtag = _wtTag;
		
		isOK = NO;
		
		bdateflag=NO;
		pageIndex=0;
		nmaxpage=0;
		ntotalline=0;
		m_positionstr=nil;
		m_bbusy=NO;
        m_bdoubleclickflag=NO;
		m_bbarflag=NO;
		m_popflag=NO;
		bfirstflag = YES;
		
		m_pyhmx=nil;
		actionIndex=0;
		byhflag=NO;
		nSelectyhIndex=0;
		m_bfirstgridtitleflag=NO;
		m_zqdmindex=0;
		m_bfirstviewflag=NO;
		npagemode=PAGE_REFRESHINDEX;
		gpcode=nil;
		baddflag=NO;
		m_bleftarrowflag=YES;
		nsetcode=0;
	
		barView = [[ETradeFuncBarView alloc] initWithData:NSZeroRect theData:eGetData parentView:self];
		barView.barViewDelegate = self;
		[self addSubview:barView];
	
		scrollView = [[NSScrollView alloc] initWithFrame:NSMakeRect(0, 0, frame.size.width, frame.size.height)];
		[scrollView setHasHorizontalScroller:YES];
		[scrollView setHasVerticalScroller:YES];
		[scrollView setDrawsBackground:NO];
		
		myTableView = [[myTableView2 alloc] initWithFrame:NSMakeRect(0, 0, frame.size.width, frame.size.height)];
		
		tableHeadView=[[NSTableHeaderView alloc] initWithFrame:NSMakeRect(0, frame.size.height-TITLE_HEIGHT, frame.size.width, TITLE_HEIGHT)];
		[myTableView setHeaderView:tableHeadView];
		[tableHeadView release];
		
		[myTableView setAutoresizesSubviews:FULLSIZE];
		[myTableView setBackgroundColor:[NSColor clearColor]];
		[[myTableView enclosingScrollView] setDrawsBackground:NO];
		[myTableView setGridColor:[NSColor whiteColor]];
		[myTableView setAutosaveTableColumns:NO];
		[myTableView setAllowsEmptySelection:NO];
		[myTableView setAllowsColumnSelection:NO];
		[myTableView setAllowsColumnReordering:NO];
		[myTableView setAllowsColumnResizing:NO];
		[myTableView setFocusRingType:1];
		[myTableView setTarget:self];
		[myTableView setAction:@selector(singleClick:)];
		[myTableView setDoubleAction:@selector(doubleClick:)];
		
		[myTableView setDataSource:self];
		[myTableView setDelegate:self];
		
		[scrollView setDocumentView:myTableView];
		[scrollView setBackgroundColor:[NSColor clearColor]];
		[self addSubview:scrollView];
		
		[self initRightMenu];
		
	}
	return self;
}

-(void)initRightMenu{
	rightMenu = [[NSMenu allocWithZone:[NSMenu menuZone]] initWithTitle:@""];
	
	NSMenuItem * newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"买入" action:@selector(rightMenu:) keyEquivalent:@""];
	[newItem setEnabled:YES];
	[newItem setTarget:self];
	[newItem setTag:0+itemTag];
	[rightMenu addItem:newItem];
	[newItem release];
	
	newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"卖出" action:@selector(rightMenu:) keyEquivalent:@""];
	[newItem setEnabled:YES];
	[newItem setTarget:self];
	[newItem setTag:1+itemTag];
	[rightMenu addItem:newItem];
	[newItem release];
    
    
    newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"融资买入" action:@selector(rightMenu:) keyEquivalent:@""];
    [newItem setEnabled:YES];
    [newItem setTarget:self];
    [newItem setTag:10+itemTag];
    if (eGetData.clientinfos.m_bxyjyflag){
    [rightMenu addItem:newItem];
    }
    [newItem release];
    
    newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"融券卖出" action:@selector(rightMenu:) keyEquivalent:@""];
    [newItem setEnabled:YES];
    [newItem setTarget:self];
    [newItem setTag:11+itemTag];
    if (eGetData.clientinfos.m_bxyjyflag){
        [rightMenu addItem:newItem];
    }
    [newItem release];
    
    

	
	[rightMenu addItem:[NSMenuItem separatorItem]];
#ifdef IMAC_ZSZQ
	newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"相关资讯" action:@selector(rightMenu:) keyEquivalent:@""];
	[newItem setEnabled:YES];
	[newItem setTarget:self];
	[newItem setTag:3+itemTag];
	[rightMenu addItem:newItem];
	[newItem release];
#endif
}

-(void)rightMenu:(id)sender{
	[myTableView selectRowIndexes:[NSIndexSet indexSetWithIndex:[myTableView clickedRow]] byExtendingSelection:NO];

	NSMenuItem * tempItem = (NSMenuItem *)sender;
	int tempInt = [tempItem tag];
 
    if (eGetData.tradeType == 3)
    {
        m_zqdmindex = 1;
    }
    
    
	switch (tempInt) {
		case 0+itemTag:{//买入
            int nindex=[myTableView selectedRow];
            if(nindex>=0 && nindex<[showDataArray count])
            {
                NSArray *rowData = [showDataArray objectAtIndex:nindex];
                if(m_zqdmindex<[rowData count])
                    [operProcessDelegate getTradeProcess:[rowData objectAtIndex:m_zqdmindex] gpSetcode:-1 typeID:MAC_WT_FUNC pareOne:0 paraTwo:-1 pareThree:@""];
            }
		}
			break;
		case 1+itemTag:{//卖出
            int nindex=[myTableView selectedRow];
            if(nindex>=0 && nindex<[showDataArray count])
            {
                NSArray *rowData = [showDataArray objectAtIndex:nindex];
                if(m_zqdmindex<[rowData count])
                    [operProcessDelegate getTradeProcess:[rowData objectAtIndex:m_zqdmindex] gpSetcode:-1 typeID:MAC_WT_FUNC pareOne:1 paraTwo:-1 pareThree:@""];
            }
		}
			break;
        case 10+itemTag:{//融资买入
            int nindex=[myTableView selectedRow];
            if(nindex>=0 && nindex<[showDataArray count])
            {
                NSArray *rowData = [showDataArray objectAtIndex:nindex];
                if(m_zqdmindex<[rowData count])
                    [operProcessDelegate getTradeProcess:[rowData objectAtIndex:m_zqdmindex] gpSetcode:-1 typeID:MAC_WT_FUNC pareOne:2 paraTwo:-1 pareThree:@""];
            }
        }
            break;
        case 11+itemTag:{//融券卖出
            int nindex=[myTableView selectedRow];
            if(nindex>=0 && nindex<[showDataArray count])
            {
                NSArray *rowData = [showDataArray objectAtIndex:nindex];
                if(m_zqdmindex<[rowData count])
                    [operProcessDelegate getTradeProcess:[rowData objectAtIndex:m_zqdmindex] gpSetcode:-1 typeID:MAC_WT_FUNC pareOne:3 paraTwo:-1 pareThree:@""];
            }
        }
            break;
		case 2+itemTag://加入自选
			;
			break;
		case 3+itemTag:{//相关资讯
            int nindex=[myTableView selectedRow];
            if(nindex>=0 && nindex<[showDataArray count])
            {
                NSArray *rowData = [showDataArray objectAtIndex:nindex];
                if(m_zqdmindex<[rowData count])
                    [operProcessDelegate getHQProcess:[rowData objectAtIndex:m_zqdmindex] gpSetcode:-1 typeID:MAC_XGZX_FUNC pareOne:-1 paraTwo:-1];
            }
			
			
		}
			break;	
		default:
			break;
	}
}

- (void)addColumn:(NSString*)newid withTitle:(NSString*)title withWidth:(int)_width
{
	NSTableColumn *column=[[NSTableColumn alloc] initWithIdentifier:newid];
	NSTableHeaderCell * tempCell = [[NSTableHeaderCell alloc] 
										 initTextCell:title];
	
	[column setHeaderCell:tempCell];
	[tempCell release];
    
    int wide = _width;
    if([title isEqualToString:@"币种"])
    {
        wide += 10;
    }
    
	[column setWidth:wide];
	[column setEditable:NO];
	[myTableView addTableColumn:column];
	[column release];
	
	
}


-(void)dealBarView{
    
    if (eGetData.tradeType ==2||eGetData.tradeType ==3)
    {
        toolbarShowFlag = NO;
    }
	if (toolbarShowFlag) {
		[barView setFrame:NSMakeRect(0, viewRect.size.height-BARVIEW_HEIGHT, viewRect.size.width, BARVIEW_HEIGHT)];
		[scrollView setFrame:NSMakeRect(0, 0, viewRect.size.width, viewRect.size.height-BARVIEW_HEIGHT)];
		[myTableView setFrame:NSMakeRect(0, 0, viewRect.size.width, viewRect.size.height-BARVIEW_HEIGHT)];
	}
	else {
		[barView setFrame:NSZeroRect];
		[scrollView setFrame:NSMakeRect(0, 0, viewRect.size.width, viewRect.size.height)];
		[myTableView setFrame:NSMakeRect(0, 0, viewRect.size.width, viewRect.size.height)];
	}
	
	[barView setShowType:[self GetQueryindexFromTag:self.tag]];
	
}


#pragma mark data相关
-(BOOL)IsLscx
{
	if(WTtag==USER_Info_STK)
	{
		switch (self.tag) {
			case TDX_LSWT:
			case TDX_LSCJ:	
			case TDX_ZJLS:
			case TDX_PHCX:
			case TDX_ZZCX:
            case TDX_XGZQCX:
            case TDX_DBPHZCD:
            case TDX_KSGXGCX:
            {
#ifdef IMAC_GXZQ
                if(self.tag==TDX_ZZCX)
                    return NO;
#endif
				return YES;
            }
				break;
			default:
				break;
		}
	}
	if(WTtag==USER_Info_FUND)
	{
		switch (self.tag) {
			case TDX_WTCX:
			case TDX_JJLSCJCX:
			case TDX_JJFJYLSWTCX:
				return YES;
				break;
			default:
				break;
		}
	}
	if(WTtag==USER_Info_LC)
	{
		switch (self.tag) {
			case TDX_LCLSWTCX:
			case TDX_LCCJCX:
				return YES;
				break;
			default:
				break;
		}
	}
	if(WTtag==USER_Info_GG)
	{
		switch (self.tag) {
			case TDX_CJCX_HK:
			case TDX_GFBD_HK:
			case TDX_ZJLS_HK:
			case TDX_IPOLB_HK:
			case TDX_IPOPH_HK:
				return YES;
				break;
			default:
				break;
		}
	}
	return NO;
}

-(BOOL)IsYhCombo
{
	if(WTtag==USER_Info_STK && self.tag==TDX_ZZCX)
		return YES;
	return NO;
}

-(void)cleardsdata
{
	if (showDataArray) {
		if ([showDataArray count]>0) {
			[showDataArray removeAllObjects];
			[myTableView reloadData];
		}
		
	}
    ntotalline=0;
}


-(void) initGridFrame:(ParseRecv *)pParsers
{
	NSArray * tempArray = [myTableView tableColumns];
	int j = 0;
	for (int i =0; i< [tempArray count]; j++) {
		NSTableColumn * tempColumn =[myTableView tableColumnWithIdentifier:[NSString stringWithFormat:@"%i",j]];
		[myTableView removeTableColumn:tempColumn];

	}
	m_zqdmindex=[pParsers getTdxIdIndex:TDX_ID_ZQDM];
    if (eGetData.tradeType ==0
        ||eGetData.tradeType ==1
        || eGetData.tradeType == MQHQ
        || eGetData.tradeType == MQHK
        || eGetData.tradeType == XQHQ
        || eGetData.tradeType == XGSG
        || eGetData.tradeType == ZQCX
        )
    {
        if(pParsers && pParsers.sFieldColstr)
        {
            int i = 0;
            for(RecvField *pfield in pParsers.sFieldColstr)
            {
                if(pfield)
                {
                    if(pfield.m_bvisible==NO)
                        continue;
                    [self addColumn:[NSString stringWithFormat:@"%i",i] withTitle:[NSString stringWithFormat:@"%@",pfield.m_sFieldName] withWidth:pfield.maxwidth];
                    i++;
                }
            }
        }
    }
    else if (eGetData.tradeType >=RZBuy && eGetData.tradeType < 20)
    {
        [self XYCXTitle];
    }
}

- (void)XYCXTitle
{
    NSArray * tempArray = [myTableView tableColumns];
    int j = 0;
    for (int i =0; i< [tempArray count]; j++) {
        NSTableColumn * tempColumn =[myTableView tableColumnWithIdentifier:[NSString stringWithFormat:@"%i",j]];
        [myTableView removeTableColumn:tempColumn];
        
    }
    NSArray * itemArray = [[NSArray alloc]init];
    if (eGetData.tradeType ==RZBuy){
        
        itemArray = [NSArray arrayWithObjects:@"交易所名称",@"证券代码",@"证券名称",@"证券数量",@"可卖数量",nil];
        
#ifdef IMAC_GDZQ
        itemArray = [NSArray arrayWithObjects:@"序号",@"证券名称",@"证券代码",@"最新市值",@"证券数量",@"可卖数量",@"成本价",@"当前价",@"浮动盈亏",@"盈亏比例(%)",@"证券市场",@"股东代码",nil];
#endif
        
#ifdef IMAC_SXZQ
        itemArray = [NSArray arrayWithObjects:@"证券代码",@"证券名称",@"交易所名称",nil];
#endif

#ifdef IMAC_PAZQ
        itemArray = [NSArray arrayWithObjects:@"证券代码",@"证券名称",@"股票折算率",@"融资保证金比例",@"融券保证金比例",@"备注",@"交易所名称",nil];
#endif

           [eGetData sendTradeQueryData:TDX_XYBDZQCX pageIndex:(TDX_XYBDZQCX+PAGE_REFRESHINDEX) objIndex:self.tradeindex Session:eGetData.inputSave.sessionID StartIndex:(pageIndex*PAGE_ROWNUM+[eGetData GetStartIndex]) ReqLines:PAGE_ROWNUM TotleLine:(PAGE_ROWNUM*MAX_PAGENUM) positionstr:@""];
    }
    else if(eGetData.tradeType ==RZSell){
        
        itemArray = [NSArray arrayWithObjects:@"交易所名称",@"证券代码",@"证券名称",@"证券数量",@"可卖数量",nil];
#ifdef IMAC_GDZQ
        itemArray = [NSArray arrayWithObjects:@"序号",@"证券名称",@"证券代码",@"融券市值",@"实时融券负债数量",@"成本价",@"当前价",@"浮动盈亏",@"盈亏比例(%)",@"今买数量",@"今卖数量",@"今买金额",@"今卖金额",@"证券市场",@"股东代码",nil];
#endif
#ifdef IMAC_SXZQ
        itemArray = [NSArray arrayWithObjects:@"证券代码",@"证券名称",@"交易所名称",nil];
#endif

#ifdef IMAC_PAZQ
        itemArray = [NSArray arrayWithObjects:@"证券代码",@"证券名称",@"可用股份",@"保证金比例",nil];
#endif
        
        [eGetData sendTradeQueryData:TDX_XYMCCX pageIndex:(TDX_XYMCCX+PAGE_REFRESHINDEX) objIndex:self.tradeindex Session:eGetData.inputSave.sessionID StartIndex:(pageIndex*PAGE_ROWNUM+[eGetData GetStartIndex]) ReqLines:PAGE_ROWNUM TotleLine:(PAGE_ROWNUM*MAX_PAGENUM) positionstr:@""];
    }
    else if(eGetData.tradeType ==XYZCCX){
#ifdef IMAC_GDZQ
        itemArray = [NSArray arrayWithObjects:@"序号",@"币种",@"总资产",@"资金金额",@"可用资金",@"最新市值",@"浮动盈亏",@"持仓比率",@"净资产",@"负债总额",@"资金负债",@"应还金额",@"融券市值",@"融券盈利",@"担保比例",@"可用保证金",@"信用上限",@"可融资金额",@"可融券额度",nil];
        [eGetData sendTradeQueryData:TDX_XYZCCX pageIndex:(TDX_XYZCCX+PAGE_REFRESHINDEX) objIndex:self.tradeindex Session:eGetData.inputSave.sessionID StartIndex:(pageIndex*PAGE_ROWNUM+[eGetData GetStartIndex]) ReqLines:PAGE_ROWNUM TotleLine:(PAGE_ROWNUM*MAX_PAGENUM) positionstr:@""];
#else
        itemArray = [NSArray arrayWithObjects:@"信用资产信息",@"数值",@"--",@"融资信息",@"数值",@"--",@"融券信息",@"数值",nil];
        [eGetData sendTradeQueryData:TDX_XYZCCX pageIndex:(TDX_XYZCCX+PAGE_REFRESHINDEX) objIndex:self.tradeindex Session:eGetData.inputSave.sessionID StartIndex:(pageIndex*PAGE_ROWNUM+[eGetData GetStartIndex]) ReqLines:PAGE_ROWNUM TotleLine:(PAGE_ROWNUM*MAX_PAGENUM) positionstr:@""];
#endif

    }
    else if(eGetData.tradeType ==XYFZCX){
        itemArray = [NSArray arrayWithObjects:@"资金帐号",@"币种",@"总资产",@"总负债",@"融资负债",@"融券市值",@"可用资金",@"负债比例",nil];
        [eGetData sendTradeQueryData:TDX_XYFZCX pageIndex:(TDX_XYFZCX+PAGE_REFRESHINDEX) objIndex:self.tradeindex Session:eGetData.inputSave.sessionID StartIndex:(pageIndex*PAGE_ROWNUM+[eGetData GetStartIndex]) ReqLines:PAGE_ROWNUM TotleLine:(PAGE_ROWNUM*MAX_PAGENUM) positionstr:@""];
    }
    else if(eGetData.tradeType ==XYSXCX){
        itemArray = [NSArray arrayWithObjects:@"序号",@"信用上限",@"融资保证金比例",@"融券保证金比例",@"担保比例",nil];
        [eGetData sendTradeQueryData:TDX_XYSXCX pageIndex:(TDX_XYSXCX+PAGE_REFRESHINDEX) objIndex:self.tradeindex Session:eGetData.inputSave.sessionID StartIndex:(pageIndex*PAGE_ROWNUM+[eGetData GetStartIndex]) ReqLines:PAGE_ROWNUM TotleLine:(PAGE_ROWNUM*MAX_PAGENUM) positionstr:@""];
    }
    else if(eGetData.tradeType ==XYRZHYCX){
        itemArray = [NSArray arrayWithObjects:@"资金帐号",@"币种",@"委托编号",@"证券代码",@"证券名称",@"委托日期",@"交易所名称",@"委托数量",@"成交数量",@"委托金额",@"委托冻结金额",@"成交金额",@"清算金额",@"合约状态",@"负载截止日期",@"原始的负债截止日期",@"融资本金",@"融资其它费合计",@"融资负载本金",nil];
#ifdef IMAC_SXZQ
        itemArray = [NSArray arrayWithObjects:@"开仓日期",@"归还截止日",@"证券代码",@"证券名称",@"合约类型",@"未还数量",@"未还本金",@"未还数量",@"未还利息",@"合约状态",@"合约性质",@"合约年利率",@"合约编号",@"展期次数",@"展期状态",nil];
#endif
        [eGetData sendTradeQueryData:TDX_XYRZHYCX pageIndex:(TDX_XYRZHYCX+PAGE_REFRESHINDEX) objIndex:self.tradeindex Session:eGetData.inputSave.sessionID StartIndex:(pageIndex*PAGE_ROWNUM+[eGetData GetStartIndex]) ReqLines:PAGE_ROWNUM TotleLine:(PAGE_ROWNUM*MAX_PAGENUM) positionstr:@""];
    }
    else if(eGetData.tradeType ==XYRQHYCX){
        itemArray = [NSArray arrayWithObjects:@"资金帐号",@"币种",@"委托编号",@"证券代码",@"证券名称",@"委托日期",@"交易所名称",@"委托数量",@"成交数量",@"委托金额",@"委托冻结金额",@"成交金额",@"清算金额",@"合约状态",@"负载截止日期",@"原始的负债截止日期",@"应偿还数量",@"融券负债",@"融券本金",@"融券其它费合计",nil];
        [eGetData sendTradeQueryData:TDX_XYRQHYCX pageIndex:(TDX_XYRQHYCX+PAGE_REFRESHINDEX) objIndex:self.tradeindex Session:eGetData.inputSave.sessionID StartIndex:(pageIndex*PAGE_ROWNUM+[eGetData GetStartIndex]) ReqLines:PAGE_ROWNUM TotleLine:(PAGE_ROWNUM*MAX_PAGENUM) positionstr:@""];
    }
    else if(eGetData.tradeType ==DBPZQCX){
        itemArray = [NSArray arrayWithObjects:@"交易所名称",@"证券代码",@"证券名称",@"担保品折算率",nil];
        [eGetData sendTradeQueryData:TDX_XYDBPZQCX pageIndex:(TDX_XYDBPZQCX+PAGE_REFRESHINDEX) objIndex:self.tradeindex Session:eGetData.inputSave.sessionID StartIndex:(pageIndex*PAGE_ROWNUM+[eGetData GetStartIndex]) ReqLines:PAGE_ROWNUM TotleLine:(PAGE_ROWNUM*MAX_PAGENUM) positionstr:@""];
    }
    else if(eGetData.tradeType ==ZQCX){
        itemArray = [NSArray arrayWithObjects:@"中签日期",@"证券代码",@"证券名称",@"成交价格",@"成交数量",@"股东代码",@"状态说明",nil];
        [eGetData sendTradeQueryData:TDX_XGZQCX pageIndex:(TDX_XGZQCX+PAGE_REFRESHINDEX) objIndex:self.tradeindex Session:eGetData.inputSave.sessionID StartIndex:(pageIndex*PAGE_ROWNUM+[eGetData GetStartIndex]) ReqLines:PAGE_ROWNUM TotleLine:(PAGE_ROWNUM*MAX_PAGENUM) positionstr:@""];
    }
    else if(eGetData.tradeType ==DBPHZ){
        itemArray = [NSArray arrayWithObjects:@"证券代码",@"证券名称",@"当前价",@"证券数量",@"可卖数量",@"股东代码",@"成本价",@"交易所名称",nil];
        eGetData.inputSave.wtfs=@"7";
        [eGetData sendTradeQueryData:TDX_DBPHZ pageIndex:(TDX_DBPHZ+PAGE_REFRESHINDEX) objIndex:self.tradeindex Session:eGetData.inputSave.sessionID StartIndex:(pageIndex*PAGE_ROWNUM+[eGetData GetStartIndex]) ReqLines:PAGE_ROWNUM TotleLine:(PAGE_ROWNUM*MAX_PAGENUM) positionstr:@""];
    }
    for (int i =0; i<itemArray.count; i++) {
        NSTableColumn *column=[[NSTableColumn alloc] initWithIdentifier:[NSString stringWithFormat:@"%d",i]];
        NSTableHeaderCell * tempCell = [[NSTableHeaderCell alloc] initTextCell:itemArray[i]];
        [column setHeaderCell:tempCell];
        [tempCell release];
        [column setWidth:100];
        if (i == itemArray.count-1)
              [column setWidth:150];
        [column setEditable:NO];
        [myTableView addTableColumn:column];
        [column release];
    }
 
}

#pragma mark barViewDelegate
-(void)getButtonClick:(int)_tag{
	switch (_tag) {
		case 5: //刷新
			if([self IsLscx])
				[self refreshpageWithDate];
			else 
				[self refreshpage2];
			
			
			break;
		default:
			break;
	}
}

- (void)onviewWillAppear:(BOOL)animated
{
	pageIndex=0;
	nmaxpage=0;
	ntotalline=0;
    [m_positionstr release];
    m_positionstr=nil;
	[self InitControl];
}

- (void)onviewDidAppear:(BOOL)animated
{

	[self startanimate];
	int queryindex=[self GetQueryindexFromTag:self.tag];
	[m_positionstr release];
    m_positionstr=nil;
	[self dealBarView];
	
	if([self showCache:queryindex]==NO)
	{
		m_bfirstviewflag=YES;
		[NSTimer scheduledTimerWithTimeInterval: 0.0f target:self selector: @selector(refreshpage1) userInfo: nil repeats: NO];
	}
    
}




-(void)buttonClick:(id)sender{
    if([self IsCanQueryOther]==NO)
        return;
    NSButton *pbut=(NSButton *)sender;
    if(pbut.tag==2)//下页
    {
        if(pageIndex<(nmaxpage-1) && pageIndex>=0)
        {
            pageIndex++;
            int queryindex=[self GetQueryindexFromTag:self.tag];
            if([self showCache:queryindex])
                return;
            npagemode=PAGE_NEXTINDEX;
            [self startanimate];
            [eGetData sendTradeQueryData:queryindex pageIndex:(queryindex+PAGE_NEXTINDEX) objIndex:self.tradeindex Session:eGetData.inputSave.sessionID StartIndex:(pageIndex*PAGE_ROWNUM+[eGetData GetStartIndex]) ReqLines:PAGE_ROWNUM TotleLine:ntotalline positionstr:m_positionstr];
            return;
        }
        else
            pageIndex=MAX(nmaxpage-1,0);
    }
	else if(pbut.tag==3)//上页
    {
        if(pageIndex > 0 && nmaxpage>1)
        {
            pageIndex--;
            int queryindex=[self GetQueryindexFromTag:self.tag];
            if([self showCache:queryindex])
                return;
            npagemode=PAGE_PREVIOUSINDEX;
            [self startanimate];
            [eGetData sendTradeQueryData:queryindex pageIndex:(queryindex+PAGE_PREVIOUSINDEX) objIndex:self.tradeindex Session:eGetData.inputSave.sessionID StartIndex:(pageIndex*PAGE_ROWNUM+[eGetData GetStartIndex]) ReqLines:PAGE_ROWNUM TotleLine:ntotalline positionstr:m_positionstr];
            return;
        }
        else
            pageIndex = 0;
    }
    else if(pbut.tag==1)//首页
    {
        
    }
    else if(pbut.tag==4)//尾页
    {
        
    }
    else if(pbut.tag==5)
    {
        [self refreshpage];
    }
}

-(void)InitControl
{
}

-(void)startanimate
{
	m_bbusy=YES;
}

-(void)stopanimate
{
	m_bbusy=NO;
}

-(BOOL)IsCanQueryOther
{
	return !m_bbusy;
}


#pragma mark  tableView Delegate相关
- (NSInteger)numberOfRowsInTableView:(NSTableView *)aTableView
{

        return [showDataArray count];
}

-(CGFloat) tableView:(NSTableView *)tableView heightOfRow:(NSInteger)row{
	return PERROWHEIGHT;
}

-(void) tableView:(NSTableView *)tableView didClickTableColumn:(NSTableColumn *)tableColumn{
}

- (id)tableView: (NSTableView *)theTableView objectValueForTableColumn: (NSTableColumn *)theColumn row: (NSInteger)rowIndex
{
  
    if (rowIndex >= [showDataArray count]) {
        return @"";
    }
    
    
    int i =[[theColumn identifier] intValue];
    NSArray *rowData = [showDataArray objectAtIndex:rowIndex];
    
    if(i>=0 && i<[rowData count])
        return [rowData objectAtIndex:i];
    else
        return @"";
    
	
}

-(void)tableView:(NSTableView *)tableView willDisplayCell:(id)cell forTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row{
	

    if (row > [showDataArray count]+1) {
        return ;
    }
    if (self.tag == TDX_GFCX) {
        [cell setMenu:rightMenu];
    }
    else {
        [cell setMenu:nil];
    }
    
    NSArray *rowData = [showDataArray objectAtIndex:row];
    if ([rowData lastObject]==[NSColor whiteColor])
        [cell setTextColor:[NSColor blackColor]];
    else
        [cell setTextColor:[rowData lastObject]];
        
        

    
}

#pragma mark 请求相关
-(void)singleClick:(id)sender{
	if ((self.tag == TDX_ZJLS)||(self.tag == TDX_PHCX)||(self.tag == TDX_GDCX)||eGetData.tradeType==XYZCCX||eGetData.tradeType==XYRZHYCX||eGetData.tradeType==XYRQHYCX||eGetData.tradeType==XYFZCX || eGetData.tradeType == XYSXCX || eGetData.tradeType == TDX_KSGXGCX){
		return;
	}
    int nindex=[myTableView selectedRow];
    if(nindex>=0 && nindex<[showDataArray count])
    {
        NSArray *rowData = [showDataArray objectAtIndex:nindex];
       
        if(m_zqdmindex>=0 && m_zqdmindex<[rowData count]){
            if (eGetData.tradeType==DBPZQCX||eGetData.tradeType==RZSell) {
            [operProcessDelegate getHQProcess:[rowData objectAtIndex:1] gpSetcode:-1 typeID:MAC_ZST_FUNC pareOne:-1 paraTwo:1];
            }
            else if (eGetData.tradeType==RZBuy) {
                [operProcessDelegate getHQProcess:[rowData objectAtIndex:0] gpSetcode:-1 typeID:MAC_ZST_FUNC pareOne:-1 paraTwo:1];
            }
            else {
            [operProcessDelegate getHQProcess:[rowData objectAtIndex:m_zqdmindex] gpSetcode:-1 typeID:MAC_ZST_FUNC pareOne:-1 paraTwo:1];
            }
        }
    }
}

-(void)doubleClick:(id)sender{
	if (self.tag == TDX_GFCX
        || eGetData.tradeType==DBPZQCX
        || eGetData.tradeType==MQHQ
        || eGetData.tradeType == XQHQ
        || eGetData.tradeType == XGSG) {
        int nindex=[myTableView selectedRow];
        if(nindex>=0 && nindex<[showDataArray count])
        {
            NSArray *rowData = [showDataArray objectAtIndex:nindex];
            m_bdoubleclickflag=YES;
            int  nflag=-1;
            
            eGetData.saveDate.arrayData = nil;
#ifdef IMAC_ZXZQ
            if(toolbarShowFlag)
                nflag=1;
#endif
            if(m_zqdmindex>=0 && m_zqdmindex<[rowData count]){
                if (eGetData.tradeType == RZSell)
                {
                    int order = 1;
#ifdef IMAC_GDZQ
                    order = 2;
#endif
#ifdef IMAC_SXZQ
                    order = 0;
#endif


#ifdef IMAC_PAZQ
                    order = 0;
#endif
                    [operProcessDelegate getTradeProcess:[rowData objectAtIndex:order] gpSetcode:-1 typeID:MAC_WT_FUNC pareOne:3 paraTwo:-1 pareThree:@""];

                }
                else if (eGetData.tradeType == RZBuy)
                {
                    int order = m_zqdmindex;
#ifdef IMAC_SXZQ
                    order = 0;
#endif
                    
                    [operProcessDelegate getTradeProcess:[rowData objectAtIndex:order] gpSetcode:-1 typeID:MAC_WT_FUNC pareOne:2 paraTwo:-1 pareThree:@""];
                }
                else if (eGetData.tradeType == DBPZQCX)
                {
                    [operProcessDelegate getTradeProcess:[rowData objectAtIndex:1] gpSetcode:-1 typeID:MAC_WT_FUNC pareOne:0 paraTwo:-1 pareThree:@""];
                }
                else if (eGetData.tradeType == MQHQ)
                {
                    int order = 3;
#ifdef IMAC_GDZQ
                    order = 2;
#endif
#ifdef IMAC_SXZQ
                    order = 2;
#endif

#ifdef IMAC_PAZQ
                    order = 2;
#endif
                    
                    [operProcessDelegate getTradeProcess:[rowData objectAtIndex:order] gpSetcode:-1 typeID:MAC_WT_FUNC pareOne:MQHQ paraTwo:TDX_XYMQHQCX pareThree:@""];
                }
                else if (eGetData.tradeType == XQHQ)
                {
                    
                    int order = 3;
#ifdef IMAC_GDZQ
                    order = 2;
#endif
#ifdef IMAC_SXZQ
                    order = 2;
#endif

#ifdef IMAC_PAZQ
                    order = 2;
#endif
                    
                    [operProcessDelegate getTradeProcess:[rowData objectAtIndex:order] gpSetcode:-1 typeID:MAC_WT_FUNC pareOne:XQHQ paraTwo:TDX_XYXQHQCX pareThree:@""];
                }
                else if(eGetData.tradeType == DBPHZ)
                {
                    if(rowData.count > 7)
                    {
                        eGetData.saveDate.DBPHZ_ptgddm = [rowData objectAtIndex:5];
                        eGetData.saveDate.DBPHZ_zhlb = [rowData objectAtIndex:7];
                    }
                    
                    [operProcessDelegate getTradeProcess:[rowData objectAtIndex:0] gpSetcode:-1 typeID:MAC_WT_FUNC pareOne:nflag paraTwo:-1 pareThree:@""];
                }
                else if(eGetData.tradeType == XGSG)
                {
                    eGetData.saveDate.arrayData = [NSArray arrayWithArray:rowData];
                    [operProcessDelegate getTradeProcess:[rowData objectAtIndex:m_zqdmindex] gpSetcode:-1 typeID:MAC_WT_FUNC pareOne:XGSG paraTwo:TDX_XGSG pareThree:@""];
                }
                else{
                    int kygf = -1;
                    if(eGetData.tradeType == DBPSell)
                    {
                        kygf = [[rowData objectAtIndex:3] intValue];
                        
                        NSString* cCode = [rowData objectAtIndex:0];
                        for(int order=0;order < [showDataArray count];order++)
                        {
                            NSString* tempCd = [[showDataArray objectAtIndex:order] objectAtIndex:0];
                            if(order != nindex && [tempCd isEqualToString:cCode])
                            {
                                kygf += [[[showDataArray objectAtIndex:order] objectAtIndex:3] intValue];
                            }
                        }
                        
                        
                        eGetData.saveDate.xwdm = [rowData objectAtIndex:17];
                    }
                     [operProcessDelegate getTradeProcess:[rowData objectAtIndex:m_zqdmindex] gpSetcode:-1 typeID:MAC_WT_FUNC pareOne:nflag paraTwo:-1 pareThree:@""];
                }
            
            }
        }
		
	}
}

-(void) refreshpageWithDate
{
    BOOL isCX = YES;
    
	if(self.tag == TDX_LSCJ || self.tag == TDX_ZJLS)
    {
        int nS = eGetData.saveDate.nStartDate;
        int nE = eGetData.saveDate.nEndDate;
        
        if(nE - nS > 100)
        {
            isCX = NO;
            NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
                                             defaultButton: @"确定"
                                           alternateButton: nil
                                               otherButton: nil
                                 informativeTextWithFormat: @"查询间隔不能大于31天"];
            [alert runModal];
        }

    }
    if(!isCX) return;
    
	if(eGetData.saveDate.nStartDate  > eGetData.saveDate.nEndDate )
	{
		NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
										 defaultButton: @"确定"
									   alternateButton: nil
										   otherButton: nil
							 informativeTextWithFormat: @"时间设置错误"];
		[alert runModal];		
	}
	else
	{
		[self refreshpage2];
	}
	
	
}


-(void)refreshpage
{
    if([self IsCanQueryOther]==NO)
        return;
	[self startanimate];
	[NSTimer scheduledTimerWithTimeInterval: 0.0f target:self selector: @selector(refreshpage1) userInfo: nil repeats: NO];
}

-(void)refreshpage1
{
	pageIndex=0;
	int queryindex=[self GetQueryindexFromTag:self.tag];
	if([self QueryCache:queryindex])
    {
        [self stopanimate];
        return;
    }
    signed char blszzcx=[self IsLscx];
	
	npagemode=PAGE_REFRESHINDEX;
    [self cleardsdata];
	if((queryindex==TDX_GFCX)&&toolbarShowFlag)//先查股份 ，得到参考市值，浮动盈亏 
	{
        ST_ZJGFINFO tmpzjgf;
        memset((char *)&tmpzjgf,0,sizeof(ST_ZJGFINFO));
        eGetData.clientinfos.strawzjgf=tmpzjgf;
	}
    if (eGetData.tradeType >=RZBuy && eGetData.tradeType < 20){
        [self startanimate];
        [self XYCXTitle];
    }
    else{
    	[eGetData sendTradeQueryData:queryindex pageIndex:(queryindex+PAGE_REFRESHINDEX) objIndex:self.tradeindex Session:eGetData.inputSave.sessionID StartIndex:(pageIndex*PAGE_ROWNUM+[eGetData GetStartIndex]) ReqLines:PAGE_ROWNUM TotleLine:(PAGE_ROWNUM*MAX_PAGENUM) positionstr:@""];
    }
  
    
}

-(void)refreshpage2{

    if([self IsCanQueryOther]==NO)
        return;
	[self startanimate];
	
	pageIndex=0;
	int queryindex=[self GetQueryindexFromTag:self.tag];
	if([self QueryCache:queryindex])
    {
        [self stopanimate];
        return;
    }
		
    [self cleardsdata];
	npagemode=PAGE_REFRESHINDEX;
	if((queryindex==TDX_GFCX)&&toolbarShowFlag)//先查股份 ，得到参考市值，浮动盈亏 
	{
        ST_ZJGFINFO tmpzjgf;
        memset((char *)&tmpzjgf,0,sizeof(ST_ZJGFINFO));
        eGetData.clientinfos.strawzjgf=tmpzjgf;
  	}
	[eGetData sendTradeQueryData:queryindex pageIndex:(queryindex+PAGE_REFRESHINDEX) objIndex:self.tradeindex Session:eGetData.inputSave.sessionID StartIndex:(pageIndex*PAGE_ROWNUM+[eGetData GetStartIndex]) ReqLines:PAGE_ROWNUM TotleLine:(PAGE_ROWNUM*MAX_PAGENUM) positionstr:@""];
	
}

-(BOOL)OnReceiveData:(int)reqIndex parser:(id)pParse
{
	ParseRecv *pParsers=(ParseRecv *)pParse;
	if(!pParsers)
		return YES;
	if([pParsers IsTimeOut]==NO){
		[eGetData SetSessionID:pParsers.sessionID];
	}
    
	switch (reqIndex) {

		case TDX_GDCX:
		{
			if([eGetData getGDCXInfo:pParsers])
				[eGetData.clientinfos.caches SaveGddm:eGetData.clientinfos.gdinfos];
              [self showGddm];
            if(eGetData.tradeType == DBPHZ){
                
                
            }else{
                
                [self showGddm];
            }
		
		}
			break;
		case TDX_ZJYE:{
			if([pParsers IsTimeOut])
			{
				if(pParsers.btipflag)
				{
					NSString *errinfo=[NSString stringWithFormat:@"错误信息:%@,%@",pParsers.psErrorNum,pParsers.psErrorData];
					
					
					NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
													 defaultButton: @"确定"
												   alternateButton: nil
													   otherButton: nil
										 informativeTextWithFormat: @"%@",errinfo];
					[alert runModal];		
				}
				return YES;
			}
			
			NSMutableArray * data=[[NSMutableArray alloc] initWithCapacity:3];
			BOOL bsucflag=YES;
            int ntmptotalline=0;
            [eGetData getCXInfo:pParsers listdata:data withqueryindex:TDX_ZJYE withrownum:(int *)(&ntmptotalline) withsucflag:(BOOL *)(&bsucflag)];
			[data release];
            [self resetToolbar];
            [self stopanimate];
            [myTableView reloadData];
            if(m_bfirstviewflag)
            {
                m_bfirstviewflag=NO;
            }
		}
			break;

		case TDX_ZHCX:
		{
			if([eGetData getJjZhInfo:pParsers])
				[eGetData.clientinfos.caches SaveJjxx:eGetData.clientinfos.jjinfos];
			[self showJjzh];
		}
			break;
		case TDX_DMCX:
		{
			if([eGetData getJjdmInfo:pParsers])
				[eGetData.clientinfos.caches SaveJjxx:eGetData.clientinfos.jjinfos];
			[self showJjdm];
		}
			break;
		case TDX_GSCX:
		{
			if([eGetData getJjgsInfo:pParsers])
				[eGetData.clientinfos.caches SaveJjxx:eGetData.clientinfos.jjinfos];
			[self showJjgs];
		}
			break;
		case TDX_LCZHCX:
		{
			if([eGetData getLcZhInfo:pParsers])
				[eGetData.clientinfos.caches SaveLcxx:eGetData.clientinfos.lcinfos];
			[self showLczh];
		}
			break;
		case TDX_LCDMCX:
		{
			if([eGetData getLcdmInfo:pParsers])
				[eGetData.clientinfos.caches SaveLcxx:eGetData.clientinfos.lcinfos];
			[self showLcdm];
		}
			break;
		case TDX_LCGSCX:
		{
			if([eGetData getLcgsInfo:pParsers])
				[eGetData.clientinfos.caches SaveLcxx:eGetData.clientinfos.lcinfos];
			[self showLcgs];
		}
			break;
            
        case 1113: //标的证券查询
        case 1110: //信用卖出查询
        case 1106: //信用资产查询
        case 1109: //信用负债查询
        case 1107: //信用融资合约查询
        case 1108: //信用融券合约查询
        case 1111: //担保品证券查询
        case 1112: //中签查询
        case 1115: //担保品划转查询
        case TDX_XYBDZQCX:
        {
            BOOL bsucflag=YES;
             int ntmptotalline=0;
            int queryindex=[self GetQueryindexFromTag:self.tag];
            [eGetData getCXInfo:pParsers listdata:showDataArray withqueryindex:queryindex withrownum:(int *)(&ntmptotalline) withsucflag:(BOOL *)(&bsucflag)];
            [barView resetbarView];
            [myTableView reloadData];
        }
            break;
        case TDX_XYMQHQCX: //买券还券查询
        case TDX_XYXQHQCX: //买券还券查询
        {

            [self initGridFrame:pParsers];
            break;
        }
		default:
		{
			int queryindex=[self GetQueryindexFromTag:self.tag];
			if((reqIndex-npagemode)!=queryindex)
				break;
			int index=reqIndex-queryindex;
			switch (index)
			{
				case PAGE_FIRSTINDEX:
				case PAGE_PREVIOUSINDEX:
				case PAGE_NEXTINDEX:
				case PAGE_ENDINDEX:
				{
					[self cleardsdata];
					BOOL bsucflag=YES;
					[m_positionstr release];
                    int ntmptotalline=0;
                    m_positionstr=[[NSString alloc] initWithFormat:@"%@",[eGetData getCXInfo:pParsers listdata:showDataArray withqueryindex:queryindex withrownum:(int *)(&ntmptotalline) withsucflag:(BOOL *)(&bsucflag)]];
              		[self initGridFrame:pParsers];
					[myTableView reloadData];
                    [self resetToolbar];
					[self stopanimate];
				}
					break;
				case PAGE_REFRESHINDEX:
				{
					if ((queryindex == TDX_GFCX)&&toolbarShowFlag) {
						[eGetData GetGfcxInfo:pParsers];
					}
					
					ParseRecv *pParsers2=nil;
					if(queryindex==TDX_ZJYE)
					{
						CGSize strsize;
						NSArray *colarray=[NSArray arrayWithObjects:@"币种",@"余额",@"可用",@"参考市值",@"资产",@"盈亏",nil];
						int colnum=[colarray count];
						pParsers2=[ParseRecv new];
						pParsers2.sFieldColstr=[[NSMutableArray alloc] initWithCapacity:colnum+1];
						[pParsers2.sFieldColstr release];
						NSString *tmpstr=nil;
						for(int i=0;i<colnum;i++)
						{
							tmpstr=[colarray objectAtIndex:i];
							RecvField *pfield=[RecvField new];
							pfield.m_sFieldName=[[NSString alloc] initWithFormat:@"%@",tmpstr];
							[pfield.m_sFieldName release];
							pfield.m_bvisible=YES;
							NSDictionary * tempAttributes= [eGetData getAttributes:MAC_CHINESEFONT fontSize:20.0f theColor:[NSColor whiteColor] theAliment:NSCenterTextAlignment];
							NSRect temprect = [tmpstr boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
							strsize = CGSizeMake(temprect.size.width, temprect.size.height);
							if(strsize.width>pfield.maxwidth)
								pfield.maxwidth=strsize.width;
							pfield.m_cFieldType=0;
							pfield.m_dwFieldId=0;
							pfield.nvisibleindex=i;
							pfield.index=i;
							[pParsers2.sFieldColstr addObject:pfield];
						}
					}
					[m_positionstr release];
					BOOL bsucflag=YES;
                    
					if(queryindex==TDX_ZJYE)
                    {
						m_positionstr=[[NSString alloc] initWithFormat:@"%@",[eGetData getCXInfo:pParsers withparse2:pParsers2 listdata:showDataArray withqueryindex:queryindex withrownum:(int *)(&ntotalline) withsucflag:(BOOL *)(&bsucflag)]];
                    }
					else
                    {
#ifdef QUERY_LOOPEND
                        int ntmptotalline=0;
						m_positionstr=[[NSString alloc] initWithFormat:@"%@",[eGetData getCXInfo:pParsers listdata:showDataArray withqueryindex:queryindex withrownum:(int *)(&ntmptotalline) withsucflag:(BOOL *)(&bsucflag)]];
#else
                        m_positionstr=[[NSString alloc] initWithFormat:@"%@",[eGetData getCXInfo:pParsers listdata:showDataArray withqueryindex:queryindex withrownum:(int *)(&ntotalline) withsucflag:(BOOL *)(&bsucflag)]];
#endif
                    }
					if(bsucflag)
					{
#ifdef QUERY_LOOPEND
                        ntotalline+=pParsers.nrownum;
                        if(pParsers.nrownum>=PAGE_ROWNUM)
                        {//继续查询
                            pageIndex++;
                            [eGetData sendTradeQueryData:[self GetQueryindexFromTag:self.tag] pageIndex:([self GetQueryindexFromTag:self.tag]+PAGE_REFRESHINDEX) objIndex:self.tradeindex Session:eGetData.inputSave.sessionID StartIndex:(pageIndex*PAGE_ROWNUM+[eGetData GetStartIndex]) ReqLines:PAGE_ROWNUM TotleLine:(PAGE_ROWNUM*MAX_PAGENUM) positionstr:m_positionstr];
                            break;
                        }
                        nmaxpage=1;
#else
                        if(ntotalline<=0 && pParsers.nrownum>=0)
                            ntotalline=pParsers.nrownum;
                        nmaxpage=ntotalline/PAGE_ROWNUM;
                        if(ntotalline%PAGE_ROWNUM)
                            nmaxpage++;
#endif
						
					}
					else 
					{
#ifdef QUERY_LOOPEND
                        if(ntotalline>0)
                            nmaxpage=1;
                        else
                            nmaxpage=0;
#else
						ntotalline=0;
						nmaxpage=0;
#endif
					}
					if(queryindex==TDX_ZJYE)
					{
						[self initGridFrame:pParsers2];
						[pParsers2 release];
					}
					else 
						[self initGridFrame:pParsers];
					
                    if(queryindex==TDX_GFCX && toolbarShowFlag)
                    {
                        [eGetData sendTradeQueryData:TDX_ZJYE pageIndex:TDX_ZJYE objIndex:self.tradeindex Session:eGetData.inputSave.sessionID StartIndex:1 ReqLines:PAGE_ROWNUM TotleLine:(PAGE_ROWNUM*MAX_PAGENUM) positionstr:@""];
                        break;
                    }
                    [self resetToolbar];
                    [myTableView reloadData];
                    [self stopanimate];
                    if(m_bfirstviewflag)
                    {
                        m_bfirstviewflag=NO;
                    }
				}
					break;
			}
		}
			break;
	}
	return YES;
}



-(void)resetToolbar{
	if (self.tag == TDX_GFCX) {
		if (toolbarShowFlag) {
			ST_ZJGFINFO tmpzjgf=eGetData.clientinfos.stzjgf;
			int rowNum=0;
			if(tmpzjgf.zzc[0]>0.00001) rowNum= 1;
			if(tmpzjgf.zzc[1]>0.00001) rowNum= rowNum+1;
			if(tmpzjgf.zzc[2]>0.00001) rowNum= rowNum+1;
            if(rowNum==0) rowNum=1;
			
			[barView setFrame:NSMakeRect(0, viewRect.size.height-rowNum*BARVIEW_HEIGHT, viewRect.size.width,rowNum*BARVIEW_HEIGHT)];
			[scrollView setFrame:NSMakeRect(0, 0, viewRect.size.width, viewRect.size.height-rowNum*BARVIEW_HEIGHT)];
            int wShowData = 0;
            if(showDataArray.count > 0)
            {
                wShowData = [[showDataArray objectAtIndex:0] count];
            }
            //wShowData = 0;
			[myTableView setFrame:NSMakeRect(0, 0, viewRect.size.width+wShowData*30, viewRect.size.height-rowNum*BARVIEW_HEIGHT+ (showDataArray.count - 10)*22)];
		
            barView.nmaxpage = nmaxpage;
            barView.ntotalline = ntotalline;
            barView.pageIndex = pageIndex;
			[barView resetbarView];
		} 
        else
        {
            [myTableView setFrame:NSMakeRect(0, 0, viewRect.size.width, viewRect.size.height-BARVIEW_HEIGHT+(showDataArray.count - 10)*22)];
        }
	
	}
	else {
		[barView setFrame:NSMakeRect(0, viewRect.size.height-BARVIEW_HEIGHT, viewRect.size.width, BARVIEW_HEIGHT)];
		[scrollView setFrame:NSMakeRect(0, 0, viewRect.size.width, viewRect.size.height-BARVIEW_HEIGHT)];
		[myTableView setFrame:NSMakeRect(0, 0, viewRect.size.width+400, viewRect.size.height-BARVIEW_HEIGHT)];
        
		barView.nmaxpage = nmaxpage;
		barView.ntotalline = ntotalline;
		barView.pageIndex = pageIndex;		
		[barView resetbarView];
	}

}

#pragma mark 缓存相关




-(BOOL)QueryCache:(int)queryindex
{
	if(queryindex==TDX_GDCX)
	{
		[self QueryGddm];
		return YES;
	}
	else if(queryindex==TDX_GSCX)
	{
		[self QueryJjgs];
		return YES;
	}
	else if(queryindex==TDX_DMCX)
	{
		[self QueryJjdm];
		return YES;
	}
	
	else if(queryindex==TDX_ZHCX)
	{
		[self QueryJjzh];
		return YES;
	}
	else if(queryindex==TDX_LCGSCX)
	{
		[self QueryLcgs];
		return YES;
	}
	else if(queryindex==TDX_LCDMCX)
	{
		[self QueryLcdm];
		return YES;
	}
	
	else if(queryindex==TDX_LCZHCX)
	{
		[self QueryLczh];
		return YES;
	}
	return NO;
}

-(BOOL)showCache:(int)queryindex
{
	if(queryindex==TDX_GDCX)
	{
		[self showGddm];
		return YES;
	}
	else if(queryindex==TDX_GSCX)
	{
		[self showJjgs];
		return YES;
	}
	else if(queryindex==TDX_DMCX)
	{
		[self showJjdm];
		return YES;
	}
	else if(queryindex==TDX_ZHCX)
	{
		[self showJjzh];
		return YES;
	}
	else if(queryindex==TDX_LCGSCX)
	{
		[self showLcgs];
		return YES;
	}
	else if(queryindex==TDX_LCDMCX)
	{
		[self showLcdm];
		return YES;
	}
	else if(queryindex==TDX_LCZHCX)
	{
		[self showLczh];
		return YES;
	}
	return NO;
}

-(void)QueryGddm
{
	[eGetData sendTradeQueryData:TDX_GDCX objIndex:self.tradeindex Session:eGetData.inputSave.sessionID];
}

-(void)showGddm
{
	[self cleardsdata];
	BOOL bsucflag=YES;
	ParseRecv *pParsers=nil;
	CGSize strsize;
	NSArray *colarray=[NSArray arrayWithObjects:@"股东代码",@"股东姓名",@"市场类别",@"资金帐号",nil];
	int colnum=[colarray count];
	pParsers=[ParseRecv new];
	pParsers.sFieldColstr=[[NSMutableArray alloc] initWithCapacity:colnum+1];
	[pParsers.sFieldColstr release];
	NSString *tmpstr=nil;
	for(int i=0;i<colnum;i++)
	{
		tmpstr=[colarray objectAtIndex:i];
		RecvField *pfield=[RecvField new];
		pfield.m_sFieldName=[[NSString alloc] initWithFormat:@"%@",tmpstr];
		[pfield.m_sFieldName release];
		pfield.m_bvisible=YES;
		NSDictionary * tempAttributes= [eGetData getAttributes:MAC_CHINESEFONT fontSize:20.0f theColor:[NSColor whiteColor] theAliment:NSCenterTextAlignment];
		NSRect temprect = [tmpstr boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
		strsize = CGSizeMake(temprect.size.width, temprect.size.height);
		if(strsize.width>pfield.maxwidth)
			pfield.maxwidth=strsize.width;
		pfield.m_cFieldType=0;
		pfield.m_dwFieldId=0;
		pfield.nvisibleindex=i;
		pfield.index=i;
		[pParsers.sFieldColstr addObject:pfield];
	}
	[m_positionstr release];
	m_positionstr=[[NSString alloc] initWithFormat:@"%@",[eGetData.clientinfos GetGdCacheInfo:showDataArray withparse:(id)pParsers StartIndex:(pageIndex*PAGE_ROWNUM+1) ReqLines:PAGE_ROWNUM withrownum:(int *)(&ntotalline) withsucflag:(BOOL *)(&bsucflag)]];
	if(ntotalline)
	{
		nmaxpage=ntotalline/PAGE_ROWNUM;
		if(ntotalline%PAGE_ROWNUM)
			nmaxpage++;
	}
	else 
		nmaxpage=0;

	[self initGridFrame:pParsers];
	[pParsers release];
	[myTableView reloadData];
	[self stopanimate];
}

-(void)QueryJjgs
{
	[eGetData sendTradeQueryData:TDX_GSCX pageIndex:TDX_GSCX objIndex:self.tradeindex Session:eGetData.inputSave.sessionID StartIndex:1 ReqLines:10000 TotleLine:10000 positionstr:@""];
}

-(void)showJjgs
{
}

-(void)QueryJjzh
{
	[eGetData sendTradeQueryData:TDX_ZHCX pageIndex:TDX_ZHCX objIndex:self.tradeindex Session:eGetData.inputSave.sessionID StartIndex:1 ReqLines:10000 TotleLine:10000 positionstr:@""];
}

-(void)showJjzh
{

}

-(void)QueryJjdm
{
	[eGetData sendTradeQueryData:TDX_DMCX pageIndex:TDX_DMCX objIndex:self.tradeindex Session:eGetData.inputSave.sessionID StartIndex:1 ReqLines:10000 TotleLine:10000 positionstr:@""];
}

-(void)showJjdm
{
}

/////
-(void)QueryLcgs
{
	[eGetData sendTradeQueryData:TDX_LCGSCX pageIndex:TDX_LCGSCX objIndex:self.tradeindex Session:eGetData.inputSave.sessionID StartIndex:1 ReqLines:10000 TotleLine:10000 positionstr:@""];
}

-(void)showLcgs
{
}

-(void)QueryLczh
{
	[eGetData sendTradeQueryData:TDX_LCZHCX pageIndex:TDX_LCZHCX objIndex:self.tradeindex Session:eGetData.inputSave.sessionID StartIndex:1 ReqLines:10000 TotleLine:10000 positionstr:@""];
}

-(void)showLczh
{

}

-(void)QueryLcdm
{
	[eGetData sendTradeQueryData:TDX_LCDMCX pageIndex:TDX_LCDMCX objIndex:self.tradeindex Session:eGetData.inputSave.sessionID StartIndex:1 ReqLines:10000 TotleLine:10000 positionstr:@""];
}

-(void)showLcdm
{

}

-(int)GetQueryindexFromTag:(int)ntag
{
	return ntag;
}

-(signed char)IsLscxFlag
{
    return [self IsLscx];
}
@end
