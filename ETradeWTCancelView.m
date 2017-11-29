//
//  ETradeWTCancelView.m
//  tdxMac
//
//  Created by tdx on 11-10-29.
//  Copyright 2011 武汉. All rights reserved.
//

#import "ETradeWTCancelView.h"
#define PERROWHEIGHT 20
#define TITLE_HEIGHT 16
#define BARVIEW_HEIGHT 25


@implementation ETradeWTCancelView
@synthesize WTtag,toolbarShowFlag,m_bdrwtcx,m_ncdType;


- (id)initWithFrame:(NSRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
    }
    return self;
}

- (id)initWithData:(NSRect)frame theData:(EGetData *)_eGetData WithTag:(int)_wtTag{
    self = [super initWithData:frame theData:_eGetData];
    if (self) {
		self.tradeindex = [_eGetData.g_TradeComm.areceiver SetWinobjs:self];
		
		
		showDataArray = [[NSMutableArray alloc]init];
		WTtag = _wtTag;
		
		m_bfirstviewflag=NO;
		
		pageIndex=0;
		nmaxpage=0;
		ntotalline=0;
		m_positionstr=nil;
		m_ncdflag=0;
		m_bbusy=NO;
		windindex=0;
		m_ntotal=m_nsuc=m_nfail=0;
		m_ncurindex=0;
		m_errinfo=nil;
		m_btoolbarstyle=TOOLBARSTYLE_POPUP;
		m_bbarflag=NO;
		m_popflag=NO;
	
		m_bfirstgridtitleflag=NO;
		m_gpcodeindex=0;
		m_bsflagindex=0;
		m_scflagindex=0;
		m_jjcodeindex=0;
		m_jjgsdmindex=0;
		m_jjzhdmindex=0;
		m_wtdateindex=0;
		m_wtnumindex=0;
		m_wtvalueindex=0;
		m_wtbhindex=0;
		m_nzhlbindex=0;
		m_ngddmindex=0;
		m_ntjrindex=0;
		npagemode=PAGE_REFRESHINDEX;
		m_nrightoffset=0.0f;
		m_bjjzndtcx=NO;
		m_blczndtcx=NO;
		m_nnameindex=0;
		m_nkkzqbhindex=0;
		m_njyjeindex=0;
		m_noccurjeindex=0;
		m_nmykkrqindex=0;
		m_nlxindex=0;
		m_nlshindex=0;
		m_nwtrqindex=0;
		
		m_bfirstalertflag=NO;
		baddflag=NO;
		
		m_kkzqarr=[[NSArray arrayWithObjects:@"每月",@"每季",@"每天",@"每周",nil] retain];
		m_kkweekarr=[[NSArray arrayWithObjects:@"星期一",@"星期二",@"星期三",@"星期四",@"星期五",nil]retain];
		m_qmtjarr=[[NSArray arrayWithObjects:@"日期区间",@"申请次数",@"申请金额",nil]retain];
		m_ncancelIndex=-1;
		m_bdrwtcx=NO;
        m_ncdType = 0;//0表示为 撤单,1表示为担保品划转撤单
		
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
		[myTableView setGridColor:[NSColor lightGrayColor]];
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
		
		
		barView = [[ETradeFuncBarView alloc] initWithData:NSZeroRect theData:eGetData parentView:self];
		barView.barViewDelegate = self;
		[self addSubview:barView];
	}
	
	return self;
}

- (void)drawRect:(NSRect)dirtyRect {
    // Drawing code here.
}
-(void) setFrame:(NSRect)frameRect{
	[super setFrame:frameRect];
	viewRect = frameRect;
	[self dealBarView];
	//return nil;
}

-(void)dealBarView{
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
	
	[barView setShowType:[self GetQueryindexFromTag]];
}


-(void)resetToolbar{
	if (self.tag == TDX_GFCX) {
		
	}
	else {
		barView.nmaxpage = nmaxpage;
		barView.ntotalline = ntotalline;
		barView.pageIndex = pageIndex;		
		[barView resetbarView];
	}
	
}

- (void)addColumn:(NSString*)newid withTitle:(NSString*)title withWidth:(int)_width
{
	NSTableColumn *column=[[NSTableColumn alloc] initWithIdentifier:newid];
	NSTableHeaderCell * tempCell = [[NSTableHeaderCell alloc] 
									initTextCell:title];
	[column setHeaderCell:tempCell];
	[tempCell release];
	[column setWidth:_width];
	[column setEditable:NO];
	[myTableView addTableColumn:column];
	[column release];
	
	
}
#pragma mark barViewDelegate
-(void)getButtonClick:(int)_tag{
	switch (_tag) {
		case 5: //刷新
			[self onviewDidAppear:NO];
			break;
		case 6://撤单
			[self myWtCancel];
			break;
	
		default:
			break;
	}
}


#pragma mark 数据相关
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

- (void)onviewWillAppear:(BOOL)animated
{
	pageIndex=0;
	nmaxpage=0;
	ntotalline=0;
	m_bfirstgridtitleflag=YES;
    [m_positionstr release];
    m_positionstr=nil;
	[self initGridFrame:nil];
}

- (void)onviewDidAppear:(BOOL)animated
{
	[self startanimate];
	m_bfirstviewflag=YES;
	[self dealBarView];
    [m_positionstr release];
    m_positionstr=nil;
	[NSTimer scheduledTimerWithTimeInterval: 0.0f target:self selector: @selector(refreshpage1) userInfo: nil repeats: NO];
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

-(void) initGridFrame:(ParseRecv *)pParsers
{
	NSArray * tempArray = [myTableView tableColumns];
	int j = 0;
	for (int i =0; i< [tempArray count]; j++) {
		NSTableColumn * tempColumn =[myTableView tableColumnWithIdentifier:[NSString stringWithFormat:@"%i",j]];
		[myTableView removeTableColumn:tempColumn];
		
	}
	m_zqdmindex=[pParsers getTdxIdIndex:TDX_ID_ZQDM];
	int index=0;
	if(pParsers && pParsers.sFieldColstr)
	{
		
		for(RecvField *pfield in pParsers.sFieldColstr)
		{
			if(pfield)
			{
				if(pfield.m_bvisible==NO)
					continue;
				[self addColumn:[NSString stringWithFormat:@"%i",index] withTitle:[NSString stringWithFormat:@"%@",pfield.m_sFieldName] withWidth:pfield.maxwidth];
				index++;
			}
		}
		if(WTtag==WT_CANCEL_STK)
		{
			m_gpcodeindex=[pParsers getTdxIdIndex:TDX_ID_ZQDM];
			m_wtbhindex=[pParsers getTdxIdIndex:TDX_ID_WTBH];
			m_scflagindex=index;
			m_bsflagindex=index+1;
			m_nzhlbindex=[pParsers getTdxIdIndex:TDX_ID_ZHLB];
			m_ngddmindex=[pParsers getTdxIdIndex:TDX_ID_GDDM];
			m_nnameindex=[pParsers getTdxIdIndex:TDX_ID_ZQMC];
#ifdef IMAC_ZXZQ
            m_nywmcindex=[pParsers getTdxIdIndex:5503];
#else
			m_nywmcindex=[pParsers getTdxIdIndex:TDX_ID_MMBZSM];
#endif
		}
		else if(WTtag==WT_CANCEL_FUND)
		{
			m_jjgsdmindex=[pParsers getTdxIdIndex:TDX_ID_KFSJJ_JJGSDM];
			m_jjzhdmindex=[pParsers getTdxIdIndex:TDX_ID_KFSJJ_JJZH];
			m_jjcodeindex=[pParsers getTdxIdIndex:TDX_ID_KFSJJ_JJDM];
			m_wtbhindex=[pParsers getTdxIdIndex:TDX_ID_WTBH];
			m_nnameindex=[pParsers getTdxIdIndex:TDX_ID_KFSJJ_JJMC];
			if(m_bjjzndtcx)
			{
				m_nkkzqbhindex=[pParsers getTdxIdIndex:TDX_ID_XT_MODE];
				m_njyjeindex=[pParsers getTdxIdIndex:TDX_ID_KFSJJ_JYJE];
				m_noccurjeindex=[pParsers getTdxIdIndex:TDX_ID_OCCURJE];
				m_nmykkrqindex=[pParsers getTdxIdIndex:TDX_ID_KFSJJ_MYKKRQ];
				m_nlxindex=[pParsers getTdxIdIndex:TDX_ID_LX];
				m_nlshindex=[pParsers getTdxIdIndex:TDX_ID_LSH];
				m_nwtrqindex=[pParsers getTdxIdIndex:TDX_ID_WTRQ];
				m_ndqtjindex=[pParsers getTdxIdIndex:TDX_ID_XT_PARAM];
				m_nksrqindex=[pParsers getTdxIdIndex:TDX_ID_KSRQ];
				m_nzzrqindex=[pParsers getTdxIdIndex:TDX_ID_ZZRQ];
				m_ntjrindex=[pParsers getTdxIdIndex:TDX_ID_TJRDM];
			}
			else 
			{
				m_wtdateindex=[pParsers getTdxIdIndex:TDX_ID_WTRQ];
				m_wtnumindex=[pParsers getTdxIdIndex:TDX_ID_KFSJJ_WTFE];
				m_wtvalueindex=[pParsers getTdxIdIndex:TDX_ID_KFSJJ_JYJE];
				m_nywmcindex=[pParsers getTdxIdIndex:TDX_ID_YWMC];
			}
		}
		else if(WTtag==WT_CANCEL_LC)
		{
			m_jjcodeindex=[pParsers getTdxIdIndex:TDX_ID_CPDM];
			m_jjgsdmindex=[pParsers getTdxIdIndex:TDX_ID_CPGSDM];
			m_jjzhdmindex=[pParsers getTdxIdIndex:TDX_ID_LCZH];
			m_wtbhindex=[pParsers getTdxIdIndex:TDX_ID_WTBH];
			m_nnameindex=[pParsers getTdxIdIndex:TDX_ID_CPMC];
			if(m_blczndtcx)
			{
				m_nkkzqbhindex=[pParsers getTdxIdIndex:TDX_ID_XT_MODE];
				m_njyjeindex=[pParsers getTdxIdIndex:TDX_ID_KFSJJ_JYJE];
				m_noccurjeindex=[pParsers getTdxIdIndex:TDX_ID_OCCURJE];
				m_nmykkrqindex=[pParsers getTdxIdIndex:TDX_ID_KFSJJ_MYKKRQ];
				m_nlxindex=[pParsers getTdxIdIndex:TDX_ID_LX];
				m_nlshindex=[pParsers getTdxIdIndex:TDX_ID_LSH];
				m_nwtrqindex=[pParsers getTdxIdIndex:TDX_ID_WTRQ];
				m_ndqtjindex=[pParsers getTdxIdIndex:TDX_ID_XT_PARAM];
				m_nksrqindex=[pParsers getTdxIdIndex:TDX_ID_KSRQ];
				m_nzzrqindex=[pParsers getTdxIdIndex:TDX_ID_ZZRQ];
				m_ntjrindex=[pParsers getTdxIdIndex:TDX_ID_TJRDM];
			}
			else 
			{
				m_wtdateindex=[pParsers getTdxIdIndex:TDX_ID_WTRQ];
				m_wtnumindex=[pParsers getTdxIdIndex:TDX_ID_KFSJJ_WTFE];
				m_wtvalueindex=[pParsers getTdxIdIndex:TDX_ID_KFSJJ_JYJE];
				m_nywmcindex=[pParsers getTdxIdIndex:TDX_ID_YWMC];
			}
			
		}
	}
}

-(NSString *)GetCdTitlestr
{
	if (WTtag == WT_CANCEL_STK)
		return @"证券";
	else if(WTtag==WT_CANCEL_FUND)
		return @"基金";
	else if(WTtag==WT_CANCEL_LC)
		return @"产品";
	return @"";
}

-(int)GetQueryindexFromTag
{
	int queryindex=0;
	if (WTtag == WT_CANCEL_STK)
	{
		if(m_bdrwtcx)
			queryindex=TDX_DRWT;
		else
        {
            if(m_ncdType == 0)
            {
                queryindex=TDX_CDCX;
            }
            else
            {
                queryindex=TDX_DBPHZCD;
            }
        }
	}
	else if(WTtag==WT_CANCEL_FUND)
	{
		if(m_bjjzndtcx)
			queryindex=TDX_JJDQSGCX;
		else 
		{
			if(m_bdrwtcx)
				queryindex=TDX_JJDRWTCX;
			else 
				queryindex=TDX_JJWT;
		}
	}
	else if(WTtag==WT_CANCEL_LC)
	{
		if(m_blczndtcx)
			queryindex=TDX_LCDQSGCX;
		else
			queryindex=TDX_LCWTCX;
	}
	return queryindex;
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
	return [rowData objectAtIndex:i];
}
-(void)tableView:(NSTableView *)tableView willDisplayCell:(id)cell forTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row{
	if (row >= [showDataArray count]) {
		return ;
	}
	
	NSArray *rowData = [showDataArray objectAtIndex:row];
	
	[cell setTextColor:[rowData lastObject]];
}


#pragma mark - 撤单
-(void)singleClick:(id)sender{
    int nindex=[myTableView selectedRow];
    if(nindex<0 || nindex>=[showDataArray count])
        return;
	NSArray *rowData = [showDataArray objectAtIndex:nindex];
	if(m_zqdmindex<[rowData count])
        [operProcessDelegate getHQProcess:[rowData objectAtIndex:m_zqdmindex] gpSetcode:-1 typeID:MAC_ZST_FUNC pareOne:-1 paraTwo:1];
	
}
-(void)doubleClick:(id)sender{
	[self myWtCancel];
}

-(void)DoWtCancel
{
	int ntmpcdflag=m_ncdflag;
	NSArray * tempArray=nil;
	m_ntotal=m_nsuc=m_nfail=0;
	NSString *errinfo=@"未找到对应类型的委托单!",*tempString=nil;
	int bsflag=0,gridnum=0;
	if(WTtag == WT_CANCEL_STK)
	{
		if(ntmpcdflag==1 || ntmpcdflag==3 || ntmpcdflag==4)
		{
			gridnum=[showDataArray count];
			for(int i=0;i<gridnum && i<[showDataArray count];i++)
			{
				tempArray = [showDataArray objectAtIndex:i];
				if(tempArray && [tempArray count]>m_bsflagindex && m_bsflagindex>=0)
				{
					if(ntmpcdflag==3 || ntmpcdflag==4)
					{
						bsflag=[[tempArray objectAtIndex:m_bsflagindex]intValue];
						if(ntmpcdflag==3 && bsflag!=0)
							continue;
						if(ntmpcdflag==4 && bsflag!=1)
							continue;
					}
					m_ntotal++;
					m_ncurindex=i;
					[eGetData sendTradeWTData:TDX_WTCDS objIndex:self.tradeindex Session:eGetData.inputSave.sessionID gpCode:(CHECKINDEX(m_gpcodeindex)?[tempArray objectAtIndex:m_gpcodeindex]:@"") Wtbhs:(CHECKINDEX(m_wtbhindex)?[tempArray objectAtIndex:m_wtbhindex]:@"") scflags:(CHECKINDEX(m_scflagindex)?[tempArray objectAtIndex:m_scflagindex]:@"")  zhlbs:(CHECKINDEX(m_nzhlbindex)?[tempArray objectAtIndex:m_nzhlbindex]:@"")   gddms:(CHECKINDEX(m_ngddmindex)?[tempArray objectAtIndex:m_ngddmindex]:@"")   mmbzs:(CHECKINDEX(m_bsflagindex)?[tempArray objectAtIndex:m_bsflagindex]:@"")];
					return;
				}
			}
			if(m_ntotal==m_nsuc+m_nfail)
			{
				m_ncdflag=0;
				m_ncancelIndex=0;
				if(m_ntotal==0)
					tempString=[NSString stringWithFormat:@"%@",errinfo];
				else 
				{
					if(m_nfail==0)
						tempString=[NSString stringWithFormat:@"撤单完成,共撤了%i笔 ",m_ntotal];
					else 
						tempString=[NSString stringWithFormat:@"撤单完成,共撤了%i笔,成功%i笔,失败%i笔.\r证券系统返回的原因是:%@",m_ntotal,m_nsuc,m_nfail,errinfo];
				}
				NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
												 defaultButton: @"确定"
											   alternateButton: nil
												   otherButton: nil
									 informativeTextWithFormat: @"%@",tempString];
				[alert runModal];
				[self stopanimate];
				if(m_nsuc)
					[self refreshpage];
				return ;
			}
			
		}
		else if(ntmpcdflag==5){//选中多选测单
			NSIndexSet * tempSet = [myTableView selectedRowIndexes];
			
			int i = [tempSet firstIndex];
			
			if (i<[showDataArray count]) {
				tempArray = [showDataArray objectAtIndex:i];
				m_ntotal++;
				m_ncurindex=i;
				[eGetData sendTradeWTData:TDX_WTCDSBYSELECT objIndex:self.tradeindex Session:eGetData.inputSave.sessionID gpCode:(CHECKINDEX(m_gpcodeindex)?[tempArray objectAtIndex:m_gpcodeindex]:@"") Wtbhs:(CHECKINDEX(m_wtbhindex)?[tempArray objectAtIndex:m_wtbhindex]:@"") scflags:(CHECKINDEX(m_scflagindex)?[tempArray objectAtIndex:m_scflagindex]:@"")  zhlbs:(CHECKINDEX(m_nzhlbindex)?[tempArray objectAtIndex:m_nzhlbindex]:@"")   gddms:(CHECKINDEX(m_ngddmindex)?[tempArray objectAtIndex:m_ngddmindex]:@"")   mmbzs:(CHECKINDEX(m_bsflagindex)?[tempArray objectAtIndex:m_bsflagindex]:@"")];
				return;
			}
			else {
				;
			}

		}
		else if(ntmpcdflag==2)
		{
            int ncindex=[myTableView selectedRow];
            if(ncindex<0 || ncindex>=[showDataArray count])
                return;
			tempArray = [showDataArray objectAtIndex:ncindex];
			[eGetData sendTradeWTData:TDX_WTCD objIndex:self.tradeindex Session:eGetData.inputSave.sessionID gpCode:(CHECKINDEX(m_gpcodeindex)?[tempArray objectAtIndex:m_gpcodeindex]:@"") Wtbhs:(CHECKINDEX(m_wtbhindex)?[tempArray objectAtIndex:m_wtbhindex]:@"") scflags:(CHECKINDEX(m_scflagindex)?[tempArray objectAtIndex:m_scflagindex]:@"")  zhlbs:(CHECKINDEX(m_nzhlbindex)?[tempArray objectAtIndex:m_nzhlbindex]:@"")   gddms:(CHECKINDEX(m_ngddmindex)?[tempArray objectAtIndex:m_ngddmindex]:@"")   mmbzs:(CHECKINDEX(m_bsflagindex)?[tempArray objectAtIndex:m_bsflagindex]:@"")];
		}
	}
	else if(WTtag == WT_CANCEL_FUND || WTtag==WT_CANCEL_LC)
	{
		if(ntmpcdflag==1)
		{
			for(int i=0;i<gridnum;i++)
			{
				m_ncurindex=i;
				m_ntotal++;
				if(m_bjjzndtcx || m_blczndtcx)
				{
					NSString *jyje=(CHECKINDEX(m_njyjeindex)?[tempArray objectAtIndex:m_njyjeindex]:@"");
					if([jyje length]==0)
						jyje=(CHECKINDEX(m_noccurjeindex)?[tempArray objectAtIndex:m_noccurjeindex]:@"");
					
					NSString *strqmtj=@"";
					int nlx=(CHECKINDEX(m_nlxindex)?[[tempArray objectAtIndex:m_nlxindex] intValue]:0); 
					switch (nlx) {
						case 0:
						{
							NSString *ksrq=(CHECKINDEX(m_nksrqindex)?[tempArray objectAtIndex:m_nksrqindex]:@"");
							NSString *zzrq=(CHECKINDEX(m_nzzrqindex)?[tempArray objectAtIndex:m_nzzrqindex]:@"");
							NSString *syear=[ksrq substringWithRange:NSMakeRange(0, 4)];
							NSString *smonth=[ksrq substringWithRange:NSMakeRange(4, 2)];
							NSString *sday=[ksrq substringWithRange:NSMakeRange(6, 2)];
							NSString *eyear=[zzrq substringWithRange:NSMakeRange(0, 4)];
							NSString *emonth=[zzrq substringWithRange:NSMakeRange(4, 2)];
							NSString *eday=[zzrq substringWithRange:NSMakeRange(6, 2)];
							if(eGetData.clientinfos.m_nQsbs==XDZQ_DLL)
								strqmtj=[NSString stringWithFormat:@"下一扣款日: %@年%@月%@日\r协议期限: %@年%@月%@日\r",syear,smonth,sday,eyear,emonth,eday];
							else 
								strqmtj=[NSString stringWithFormat:@"开始日期: %@年%@月%@日\r结束日期: %@年%@月%@日\r",syear,smonth,sday,eyear,emonth,eday];
						}
							break;
						case 1:
						{
							strqmtj=[NSString stringWithFormat:@"到期次数: %@次\r",(CHECKINDEX(m_ndqtjindex)?[tempArray objectAtIndex:m_ndqtjindex]:@"")];
						}
							break;
						case 2:
						{
							strqmtj=[NSString stringWithFormat:@"到期金额: %@元\r",(CHECKINDEX(m_ndqtjindex)?[tempArray objectAtIndex:m_ndqtjindex]:@"")];
						}
							break;
						default:
							break;
					}
					
					[eGetData sendTradeWTData:TDX_JJZNDTCDS objIndex:self.tradeindex Sessiomn:eGetData.inputSave.sessionID 
									   jjCode:(CHECKINDEX(m_jjcodeindex)?[tempArray objectAtIndex:m_jjcodeindex]:@"") 
									   jjGsdm:(CHECKINDEX(m_jjgsdmindex)?[tempArray objectAtIndex:m_jjgsdmindex]:@"")  
									   jjZhdm:(CHECKINDEX(m_jjzhdmindex)?[tempArray objectAtIndex:m_jjzhdmindex]:@"")  
										 WTBH:(CHECKINDEX(m_wtbhindex)?[tempArray objectAtIndex:m_wtbhindex]:@"") 
										 WTLX:(CHECKINDEX(m_nlxindex)?[tempArray objectAtIndex:m_nlxindex]:@"") 
									   MYKKRQ:(CHECKINDEX(m_nmykkrqindex)?[tempArray objectAtIndex:m_nmykkrqindex]:@"") 
										 KSRQ:(CHECKINDEX(m_nksrqindex)?[tempArray objectAtIndex:m_nksrqindex]:@"") 
										 ZZRQ:(CHECKINDEX(m_nzzrqindex)?[tempArray objectAtIndex:m_nzzrqindex]:@"") 
										 JYJE:jyje 
										  LSH:(CHECKINDEX(m_nlshindex)?[tempArray objectAtIndex:m_nlshindex]:@"") 
										 QMTJ:strqmtj  
										 MODE:(CHECKINDEX(m_nkkzqbhindex)?[tempArray objectAtIndex:m_nkkzqbhindex]:@"") 
										 WTRQ:(CHECKINDEX(m_nwtrqindex)?[tempArray objectAtIndex:m_nwtrqindex]:@"")];
				}
				else 
				{
					[eGetData sendTradeWTData:TDX_JJCDS objIndex:self.tradeindex Sessiomn:eGetData.inputSave.sessionID 
									   jjCode:(CHECKINDEX(m_jjcodeindex)?[tempArray objectAtIndex:m_jjcodeindex]:@"") 
									   jjGsdm:(CHECKINDEX(m_jjgsdmindex)?[tempArray objectAtIndex:m_jjgsdmindex]:@"")  
									   jjZhdm:(CHECKINDEX(m_jjzhdmindex)?[tempArray objectAtIndex:m_jjzhdmindex]:@"")  
									   WTDate:(CHECKINDEX(m_wtdateindex)?[tempArray objectAtIndex:m_wtdateindex]:@"")  
									 WTNumber:(CHECKINDEX(m_wtnumindex)?[tempArray objectAtIndex:m_wtnumindex]:@"")  
									  WTValue:(CHECKINDEX(m_wtvalueindex)?[tempArray objectAtIndex:m_wtvalueindex]:@"") 
									  WTIndex:(CHECKINDEX(m_wtbhindex)?[tempArray objectAtIndex:m_wtbhindex]:@"") ];
				}
				return;
			}
			if(m_ntotal==m_nsuc+m_nfail)
			{
				m_ncdflag=0;
				m_ncancelIndex=0;
				if(m_nfail==0)
					tempString=[NSString stringWithFormat:@"撤单完成,共撤了%i笔",m_ntotal];
				else 
					tempString=[NSString stringWithFormat:@"撤单完成,共撤了%i笔,成功%i笔,失败%i笔.\r证券系统返回的原因是:%@",m_ntotal,m_nsuc,m_nfail,errinfo];
				
				NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
												 defaultButton: @"确定"
											   alternateButton: nil
												   otherButton: nil
									 informativeTextWithFormat: @"%@",tempString];
				[alert runModal];
				[self stopanimate];
				if(m_nsuc>0)
					[self refreshpage];
				return;
			}
			
		}			
		else if(ntmpcdflag==2)
		{
			//tempArray = [grid getSelectedInfo:grid.selectedIndex];
			if(m_bjjzndtcx || m_blczndtcx)
			{
				NSString *jyje=(CHECKINDEX(m_njyjeindex)?[tempArray objectAtIndex:m_njyjeindex]:@"");
				if([jyje length]==0)
					jyje=(CHECKINDEX(m_noccurjeindex)?[tempArray objectAtIndex:m_noccurjeindex]:@"");
				
				NSString *strqmtj=@"";
				int nlx=(CHECKINDEX(m_nlxindex)?[[tempArray objectAtIndex:m_nlxindex] intValue]:0); 
				switch (nlx) {
					case 0:
					{
						NSString *ksrq=(CHECKINDEX(m_nksrqindex)?[tempArray objectAtIndex:m_nksrqindex]:@"");
						NSString *zzrq=(CHECKINDEX(m_nzzrqindex)?[tempArray objectAtIndex:m_nzzrqindex]:@"");
						NSString *syear=[ksrq substringWithRange:NSMakeRange(0, 4)];
						NSString *smonth=[ksrq substringWithRange:NSMakeRange(4, 2)];
						NSString *sday=[ksrq substringWithRange:NSMakeRange(6, 2)];
						NSString *eyear=[zzrq substringWithRange:NSMakeRange(0, 4)];
						NSString *emonth=[zzrq substringWithRange:NSMakeRange(4, 2)];
						NSString *eday=[zzrq substringWithRange:NSMakeRange(6, 2)];
						if(eGetData.clientinfos.m_nQsbs==XDZQ_DLL)
							strqmtj=[NSString stringWithFormat:@"下一扣款日: %@年%@月%@日\r协议期限: %@年%@月%@日\r",syear,smonth,sday,eyear,emonth,eday];
						else 
							strqmtj=[NSString stringWithFormat:@"开始日期: %@年%@月%@日\r结束日期: %@年%@月%@日\r",syear,smonth,sday,eyear,emonth,eday];
					}
						break;
					case 1:
					{
						strqmtj=[NSString stringWithFormat:@"到期次数: %@次\r",(CHECKINDEX(m_ndqtjindex)?[tempArray objectAtIndex:m_ndqtjindex]:@"")];
					}
						break;
					case 2:
					{
						strqmtj=[NSString stringWithFormat:@"到期金额: %@元\r",(CHECKINDEX(m_ndqtjindex)?[tempArray objectAtIndex:m_ndqtjindex]:@"")];
					}
						break;
					default:
						break;
				}
				
				[eGetData sendTradeWTData:TDX_JJZNDTCD objIndex:self.tradeindex Sessiomn:eGetData.inputSave.sessionID 
								   jjCode:(CHECKINDEX(m_jjcodeindex)?[tempArray objectAtIndex:m_jjcodeindex]:@"") 
								   jjGsdm:(CHECKINDEX(m_jjgsdmindex)?[tempArray objectAtIndex:m_jjgsdmindex]:@"")  
								   jjZhdm:(CHECKINDEX(m_jjzhdmindex)?[tempArray objectAtIndex:m_jjzhdmindex]:@"")  
									 WTBH:(CHECKINDEX(m_wtbhindex)?[tempArray objectAtIndex:m_wtbhindex]:@"") 
									 WTLX:(CHECKINDEX(m_nlxindex)?[tempArray objectAtIndex:m_nlxindex]:@"") 
								   MYKKRQ:(CHECKINDEX(m_nmykkrqindex)?[tempArray objectAtIndex:m_nmykkrqindex]:@"") 
									 KSRQ:(CHECKINDEX(m_nksrqindex)?[tempArray objectAtIndex:m_nksrqindex]:@"") 
									 ZZRQ:(CHECKINDEX(m_nzzrqindex)?[tempArray objectAtIndex:m_nzzrqindex]:@"") 
									 JYJE:jyje 
									  LSH:(CHECKINDEX(m_nlshindex)?[tempArray objectAtIndex:m_nlshindex]:@"") 
									 QMTJ:strqmtj  
									 MODE:(CHECKINDEX(m_nkkzqbhindex)?[tempArray objectAtIndex:m_nkkzqbhindex]:@"") 
									 WTRQ:(CHECKINDEX(m_nwtrqindex)?[tempArray objectAtIndex:m_nwtrqindex]:@"")];
			}
			else
			{
				[eGetData sendTradeWTData:TDX_JJCD objIndex:self.tradeindex Sessiomn:eGetData.inputSave.sessionID 
								   jjCode:(CHECKINDEX(m_jjcodeindex)?[tempArray objectAtIndex:m_jjcodeindex]:@"") 
								   jjGsdm:(CHECKINDEX(m_jjgsdmindex)?[tempArray objectAtIndex:m_jjgsdmindex]:@"")  
								   jjZhdm:(CHECKINDEX(m_jjzhdmindex)?[tempArray objectAtIndex:m_jjzhdmindex]:@"")  
								   WTDate:(CHECKINDEX(m_wtdateindex)?[tempArray objectAtIndex:m_wtdateindex]:@"")  
								 WTNumber:(CHECKINDEX(m_wtnumindex)?[tempArray objectAtIndex:m_wtnumindex]:@"")  
								  WTValue:(CHECKINDEX(m_wtvalueindex)?[tempArray objectAtIndex:m_wtvalueindex]:@"") 
								  WTIndex:(CHECKINDEX(m_wtbhindex)?[tempArray objectAtIndex:m_wtbhindex]:@"") ];
			}
		}
		
	}
	
	
}

#pragma mark alert相关
-(void)handleResult:(NSAlert *)alert withResult:(NSInteger)result
{
	switch(result)
	{
			
		case NSAlertDefaultReturn:{
			[eGetData.clientinfos jyhasoper];
			if(NO)
			{
				;
			}
			else 
			{

				[self startanimate];
				[NSTimer scheduledTimerWithTimeInterval: 0.0f target:self selector:@selector(DoWtCancel) userInfo: nil repeats: NO];
			}
		}
			break;
			
		case NSAlertAlternateReturn:
			break;
			
		case NSAlertOtherReturn:
			break;
            
        default:
            break;
	}
	
}


#pragma mark 其它相关
-(void)myWtCancel
{
	if([myTableView selectedRow]<0 || [myTableView selectedRow]>=[showDataArray count]){
		NSAlert* alert = [NSAlert alertWithMessageText:@"撤单确认"
										 defaultButton: @"确定"
									   alternateButton: nil
										   otherButton: nil
							 informativeTextWithFormat: @"请选择您要撤销的交易单,用Command或者Shift键可以选中多条一起撤销！\r您可以在此页面双击记录进行撤单，也可以在当日委托查询界面双击记录进行撤单!"];
		[alert runModal];
		return;
		
	}
		
	
	m_ncdflag=2;
    int ncindex=[myTableView selectedRow];
    if(ncindex<0 || ncindex>=[showDataArray count])
        return;
	NSArray * tempArray = [showDataArray objectAtIndex:ncindex];
	NSString * tempString=@"" ;
	int queryindex=[self GetQueryindexFromTag];
	if(queryindex==TDX_CDCX || queryindex==TDX_DRWT || queryindex == TDX_DBPHZCD){
		if ([[myTableView selectedRowIndexes] count] > 1) {
			m_ncdflag=5;
			multiSelectCount = [[myTableView selectedRowIndexes] count];
			tempString = [NSString stringWithFormat:@"共有%i笔委托需要撤单,请确认",[[myTableView selectedRowIndexes] count]];
		}
		else {
			tempString = [NSString stringWithFormat:@"请确认以下信息:\r\r操作类别:   股票撤单\r买卖方向:   %@\r%@代码:   %@\r%@名称:   %@\r合同编号:   %@\r",(CHECKINDEX(m_nywmcindex)?[tempArray objectAtIndex:m_nywmcindex]:@""),[self GetCdTitlestr],(CHECKINDEX(m_gpcodeindex)?[tempArray objectAtIndex:m_gpcodeindex]:@""),[self GetCdTitlestr],(CHECKINDEX(m_nnameindex)?[tempArray objectAtIndex:m_nnameindex]:@""),(CHECKINDEX(m_wtbhindex)?[tempArray objectAtIndex:m_wtbhindex]:@"")];
		}

	}
	else if(queryindex==TDX_JJWT || queryindex==TDX_JJDRWTCX)
	{
		tempString = [NSString stringWithFormat:@"请确认以下信息:\r\r操作类别: 基金撤单\r买卖方向: %@\r%@代码: %@\r%@名称: %@\r合同编号: %@\r",(CHECKINDEX(m_nywmcindex)?[tempArray objectAtIndex:m_nywmcindex]:@""),[self GetCdTitlestr],(CHECKINDEX(m_jjcodeindex)?[tempArray objectAtIndex:m_jjcodeindex]:@""),[self GetCdTitlestr],(CHECKINDEX(m_nnameindex)?[tempArray objectAtIndex:m_nnameindex]:@""),(CHECKINDEX(m_wtbhindex)?[tempArray objectAtIndex:m_wtbhindex]:@"")];
	}
	else if(queryindex==TDX_JJDQSGCX)
	{
		int kkzqindex=(CHECKINDEX(m_nkkzqbhindex)?[[tempArray objectAtIndex:m_nkkzqbhindex] intValue]:0);
		NSString *strkkrq=@"";
		int mykkrq=(CHECKINDEX(m_nmykkrqindex)?[[tempArray objectAtIndex:m_nmykkrqindex] intValue]:0);
		if(kkzqindex==0)
			strkkrq=[NSString stringWithFormat:@"%i号",mykkrq];
		else if(kkzqindex==3 && mykkrq>=1 && mykkrq<=5)
			strkkrq=[NSString stringWithFormat:@"%@",[m_kkweekarr objectAtIndex:mykkrq-1]];
		if(eGetData.clientinfos.tradeccf.m_bjjzndtex)
			tempString = [NSString stringWithFormat:@"请确认以下信息:\r\r操作类别: 新版定时定额撤销\r合  同  号: %@\r基金代码: %@\r基金名称: %@\r基金账号: %@\r扣款周期: %@\r周期发送日: %@\r\r\r\r\r\r",(CHECKINDEX(m_wtbhindex)?[tempArray objectAtIndex:m_wtbhindex]:@""),(CHECKINDEX(m_jjcodeindex)?[tempArray objectAtIndex:m_jjcodeindex]:@""),(CHECKINDEX(m_nnameindex)?[tempArray objectAtIndex:m_nnameindex]:@""),(CHECKINDEX(m_jjzhdmindex)?[tempArray objectAtIndex:m_jjzhdmindex]:@""),((kkzqindex>=0 && kkzqindex<[m_kkzqarr count])?[m_kkzqarr objectAtIndex:kkzqindex]:@""),strkkrq];
		else 
		{
			NSString *strqmtj=@"";
			int nlx=(CHECKINDEX(m_nlxindex)?[[tempArray objectAtIndex:m_nlxindex] intValue]:0); 
			switch (nlx) {
				case 0:
				{
					NSString *ksrq=(CHECKINDEX(m_nksrqindex)?[tempArray objectAtIndex:m_nksrqindex]:@"");
					NSString *zzrq=(CHECKINDEX(m_nzzrqindex)?[tempArray objectAtIndex:m_nzzrqindex]:@"");
					NSString *syear=[ksrq substringWithRange:NSMakeRange(0, 4)];
					NSString *smonth=[ksrq substringWithRange:NSMakeRange(4, 2)];
					NSString *sday=[ksrq substringWithRange:NSMakeRange(6, 2)];
					NSString *eyear=[zzrq substringWithRange:NSMakeRange(0, 4)];
					NSString *emonth=[zzrq substringWithRange:NSMakeRange(4, 2)];
					NSString *eday=[zzrq substringWithRange:NSMakeRange(6, 2)];
					if(eGetData.clientinfos.m_nQsbs==XDZQ_DLL)
						strqmtj=[NSString stringWithFormat:@"下一扣款日: %@年%@月%@日\r协议期限: %@年%@月%@日\r",syear,smonth,sday,eyear,emonth,eday];
					else 
						strqmtj=[NSString stringWithFormat:@"开始日期: %@年%@月%@日\r结束日期: %@年%@月%@日\r",syear,smonth,sday,eyear,emonth,eday];
				}
					break;
				case 1:
				{
					strqmtj=[NSString stringWithFormat:@"到期次数: %@次\r",(CHECKINDEX(m_ndqtjindex)?[tempArray objectAtIndex:m_ndqtjindex]:@"")];
				}
					break;
				case 2:
				{
					strqmtj=[NSString stringWithFormat:@"到期金额: %@元\r",(CHECKINDEX(m_ndqtjindex)?[tempArray objectAtIndex:m_ndqtjindex]:@"")];
				}
					break;
				default:
					break;
			}
			NSString *strtitle=@"";
			if(eGetData.clientinfos.m_nQsbs==ZXJT_DLL || eGetData.clientinfos.m_nQsbs==BHZQ_DLL)
				strtitle=@"新版定时定额撤销";
			else if(eGetData.clientinfos.m_nQsbs==QLZQ_DLL)
				strtitle=@"新版定时定投撤销";
			else if(eGetData.clientinfos.m_nQsbs==GHZQ_DLL)
				strtitle=@"撤销定时定额";
			else if(eGetData.clientinfos.m_nQsbs==XDZQ_DLL)
				strtitle=@"撤销基金定投";
			else 
				strtitle=@"撤销智能定投";
			NSString *mqtjze=(CHECKINDEX(m_njyjeindex)?[tempArray objectAtIndex:m_njyjeindex]:@"");
			if([mqtjze length]==0)
				mqtjze=(CHECKINDEX(m_noccurjeindex)?[tempArray objectAtIndex:m_noccurjeindex]:@"");
			tempString=[NSString stringWithFormat:@"请确认以下信息:\r\r操作类别: %@\r合同号: %@\r基金代码: %@\r基金名称: %@\r基金账号: %@\r扣款周期: %@\r周期发送日: %@\r每期投资金额: %@元\r期满条件: %@\r%@\r\r\r\r\r\r\r\r",strtitle,(CHECKINDEX(m_wtbhindex)?[tempArray objectAtIndex:m_wtbhindex]:@""),(CHECKINDEX(m_jjcodeindex)?[tempArray objectAtIndex:m_jjcodeindex]:@""),(CHECKINDEX(m_nnameindex)?[tempArray objectAtIndex:m_nnameindex]:@""),(CHECKINDEX(m_jjzhdmindex)?[tempArray objectAtIndex:m_jjzhdmindex]:@""),[m_kkzqarr objectAtIndex:kkzqindex],strkkrq,mqtjze,[m_qmtjarr objectAtIndex:nlx],strqmtj];
		}
		m_bfirstalertflag=YES;
		
	}
	else if(queryindex==TDX_LCDQSGCX)
	{
		int kkzqindex=(CHECKINDEX(m_nkkzqbhindex)?[[tempArray objectAtIndex:m_nkkzqbhindex] intValue]:0);
		NSString *strkkrq=@"";
		int mykkrq=(CHECKINDEX(m_nmykkrqindex)?[[tempArray objectAtIndex:m_nmykkrqindex] intValue]:0);
		if(kkzqindex==0)
			strkkrq=[NSString stringWithFormat:@"%i号",mykkrq];
		else if(kkzqindex==3 && mykkrq>=1 && mykkrq<=5)
			strkkrq=[NSString stringWithFormat:@"%@",[m_kkweekarr objectAtIndex:mykkrq-1]];
		if(eGetData.clientinfos.tradeccf.m_bjjzndtex)
			tempString = [NSString stringWithFormat:@"请确认以下信息:\r\r操作类别: 新版定时定额撤销\r合  同  号: %@\r产品代码: %@\r产品名称: %@\r理财账号: %@\r扣款周期: %@\r周期发送日: %@\r\r\r\r\r\r",(CHECKINDEX(m_wtbhindex)?[tempArray objectAtIndex:m_wtbhindex]:@""),(CHECKINDEX(m_jjcodeindex)?[tempArray objectAtIndex:m_jjcodeindex]:@""),(CHECKINDEX(m_nnameindex)?[tempArray objectAtIndex:m_nnameindex]:@""),(CHECKINDEX(m_jjzhdmindex)?[tempArray objectAtIndex:m_jjzhdmindex]:@""),((kkzqindex>=0 && kkzqindex<[m_kkzqarr count])?[m_kkzqarr objectAtIndex:kkzqindex]:@""),strkkrq];
		else 
		{
			NSString *strqmtj=@"";
			int nlx=(CHECKINDEX(m_nlxindex)?[[tempArray objectAtIndex:m_nlxindex] intValue]:0); 
			switch (nlx) {
				case 0:
				{
					NSString *ksrq=(CHECKINDEX(m_nksrqindex)?[tempArray objectAtIndex:m_nksrqindex]:@"");
					NSString *zzrq=(CHECKINDEX(m_nzzrqindex)?[tempArray objectAtIndex:m_nzzrqindex]:@"");
					NSString *syear=[ksrq substringWithRange:NSMakeRange(0, 4)];
					NSString *smonth=[ksrq substringWithRange:NSMakeRange(4, 2)];
					NSString *sday=[ksrq substringWithRange:NSMakeRange(6, 2)];
					NSString *eyear=[zzrq substringWithRange:NSMakeRange(0, 4)];
					NSString *emonth=[zzrq substringWithRange:NSMakeRange(4, 2)];
					NSString *eday=[zzrq substringWithRange:NSMakeRange(6, 2)];
					if(eGetData.clientinfos.m_nQsbs==XDZQ_DLL)
						strqmtj=[NSString stringWithFormat:@"下一扣款日: %@年%@月%@日\r协议期限: %@年%@月%@日\r",syear,smonth,sday,eyear,emonth,eday];
					else 
						strqmtj=[NSString stringWithFormat:@"开始日期: %@年%@月%@日\r结束日期: %@年%@月%@日\r",syear,smonth,sday,eyear,emonth,eday];
				}
					break;
				case 1:
				{
					strqmtj=[NSString stringWithFormat:@"到期次数: %@次\r",(CHECKINDEX(m_ndqtjindex)?[tempArray objectAtIndex:m_ndqtjindex]:@"")];
				}
					break;
				case 2:
				{
					strqmtj=[NSString stringWithFormat:@"到期金额: %@元\r",(CHECKINDEX(m_ndqtjindex)?[tempArray objectAtIndex:m_ndqtjindex]:@"")];
				}
					break;
				default:
					break;
			}
			NSString *strtitle=@"";
			if(eGetData.clientinfos.m_nQsbs==ZXJT_DLL || eGetData.clientinfos.m_nQsbs==BHZQ_DLL)
				strtitle=@"新版定时定额撤销";
			else if(eGetData.clientinfos.m_nQsbs==QLZQ_DLL)
				strtitle=@"新版定时定投撤销";
			else if(eGetData.clientinfos.m_nQsbs==GHZQ_DLL)
				strtitle=@"撤销定时定额";
			else if(eGetData.clientinfos.m_nQsbs==XDZQ_DLL)
				strtitle=@"撤销李柴定投";
			else 
				strtitle=@"撤销智能定投";
			NSString *mqtjze=(CHECKINDEX(m_njyjeindex)?[tempArray objectAtIndex:m_njyjeindex]:@"");
			if([mqtjze length]==0)
				mqtjze=(CHECKINDEX(m_noccurjeindex)?[tempArray objectAtIndex:m_noccurjeindex]:@"");
			tempString=[NSString stringWithFormat:@"请确认以下信息:\r\r操作类别: %@\r合同号: %@\r产品代码: %@\r产品名称: %@\r理财账号: %@\r扣款周期: %@\r周期发送日: %@\r每期投资金额: %@元\r期满条件: %@\r%@\r\r\r\r\r\r\r\r",strtitle,(CHECKINDEX(m_wtbhindex)?[tempArray objectAtIndex:m_wtbhindex]:@""),(CHECKINDEX(m_jjcodeindex)?[tempArray objectAtIndex:m_jjcodeindex]:@""),(CHECKINDEX(m_nnameindex)?[tempArray objectAtIndex:m_nnameindex]:@""),(CHECKINDEX(m_jjzhdmindex)?[tempArray objectAtIndex:m_jjzhdmindex]:@""),[m_kkzqarr objectAtIndex:kkzqindex],strkkrq,mqtjze,[m_qmtjarr objectAtIndex:nlx],strqmtj];
		}
		m_bfirstalertflag=YES;
	}
	else if(queryindex==TDX_LCWTCX)
	{
		tempString = [NSString stringWithFormat:@"请确认以下信息:\r\r操作类别: 理财撤单\r买卖方向: %@\r%@代码: %@\r%@名称: %@\r合同编号: %@\r\r\r\r\r\r\r\r\r",(CHECKINDEX(m_nywmcindex)?[tempArray objectAtIndex:m_nywmcindex]:@""),[self GetCdTitlestr],(CHECKINDEX(m_jjcodeindex)?[tempArray objectAtIndex:m_jjcodeindex]:@""),[self GetCdTitlestr],(CHECKINDEX(m_nnameindex)?[tempArray objectAtIndex:m_nnameindex]:@""),(CHECKINDEX(m_wtbhindex)?[tempArray objectAtIndex:m_wtbhindex]:@"")];
	}
	m_ncancelIndex=1;

	NSAlert* alert = [NSAlert alertWithMessageText:@"撤单确认"
									 defaultButton: @"确定"
								   alternateButton: @"取消"
									   otherButton: nil
						 informativeTextWithFormat: @"%@",tempString];
	[alert setDelegate:self];
	NSInteger result = [alert runModal];
	[self handleResult:alert withResult:result];		
	
}

-(void)previouspage
{
    if([self IsCanQueryOther]==NO)
        return;
	[self startanimate];
	[NSTimer scheduledTimerWithTimeInterval: 0.0f target:self selector: @selector(previouspage1) userInfo: nil repeats: NO];
}

-(void)previouspage1
{
	if(pageIndex > 0 && nmaxpage>1)
	{
		pageIndex--;
		int queryindex=[self GetQueryindexFromTag];
		npagemode=PAGE_PREVIOUSINDEX;
      	[eGetData sendTradeQueryData:queryindex pageIndex:(queryindex+PAGE_PREVIOUSINDEX) objIndex:self.tradeindex Session:eGetData.inputSave.sessionID StartIndex:(pageIndex*PAGE_ROWNUM+[eGetData GetStartIndex]) ReqLines:PAGE_ROWNUM TotleLine:ntotalline positionstr:m_positionstr];
		return;
	}
	else
		pageIndex = 0;
	
	[self stopanimate];
}

-(void)nextpage
{
    if([self IsCanQueryOther]==NO)
        return;
	[self startanimate];
	[NSTimer scheduledTimerWithTimeInterval: 0.0f target:self selector: @selector(nextpage1) userInfo: nil repeats: NO];
}

-(void)nextpage1
{
	if(pageIndex<(nmaxpage-1) && pageIndex>=0)
	{
		pageIndex++;
		int queryindex=[self GetQueryindexFromTag];
		npagemode=PAGE_NEXTINDEX;
      
		[eGetData sendTradeQueryData:queryindex pageIndex:(queryindex+PAGE_NEXTINDEX) objIndex:self.tradeindex Session:eGetData.inputSave.sessionID StartIndex:pageIndex*PAGE_ROWNUM+[eGetData GetStartIndex] ReqLines:PAGE_ROWNUM TotleLine:ntotalline positionstr:m_positionstr];
		return;
	}
	else 
		pageIndex=MAX(nmaxpage-1,0);
	[self stopanimate];
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
	int queryindex=[self GetQueryindexFromTag];
	if (queryindex == TDX_CDCX || queryindex == TDX_DBPHZCD) {
		[myTableView setAllowsMultipleSelection:YES];
	}
	else if(queryindex == TDX_DRWT) {
		[myTableView setAllowsMultipleSelection:NO];		
	}
    [self cleardsdata];
	npagemode=PAGE_REFRESHINDEX;
	[eGetData sendTradeQueryData:queryindex pageIndex:(queryindex+PAGE_REFRESHINDEX) objIndex:self.tradeindex Session:eGetData.inputSave.sessionID StartIndex:(pageIndex*PAGE_ROWNUM+[eGetData GetStartIndex]) ReqLines:PAGE_ROWNUM TotleLine:(PAGE_ROWNUM*MAX_PAGENUM) positionstr:@""];
}

-(void)OnWtCancelAll
{
	if(m_ncdflag)
		return;
	m_ncdflag=1;
	m_ncancelIndex=1;

	NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
									 defaultButton: @"确定"
								   alternateButton: @"取消"
									   otherButton: nil
						 informativeTextWithFormat: @"%@",@"你确定要撤掉本页显示的全部委托吗?"];
	[alert runModal];
	
}

-(int)GetBuyCount
{
	int nbuycount=0;

	return nbuycount;
}

-(int)GetSellCount
{
	int nsellcount=0;
	return nsellcount;
}

-(void)DoCancelBuy
{
	if(m_ncdflag)
		return;
	m_ncdflag=3;
	m_ncancelIndex=1;
	NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
									 defaultButton: @"确定"
								   alternateButton: @"取消"
									   otherButton: nil
						 informativeTextWithFormat: @"%@",@"你确定要撤掉本页显示的全部买入委托吗?"];
	[alert runModal];
	
}

-(void)DoCancelSell
{
	if(m_ncdflag)
		return;
	m_ncdflag=4;
	m_ncancelIndex=1;
	NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
									 defaultButton: @"确定"
								   alternateButton: @"取消"
									   otherButton: nil
						 informativeTextWithFormat: @"%@",@"你确定要撤掉本页显示的全部卖出委托吗?"];
	[alert runModal];
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
		case	TDX_WTCD:
		case TDX_JJCD:
		{
			m_ncdflag=0;
			NSString *tmpstr=@"";
			if(pParsers.bsucflag)
			{
				if(eGetData.clientinfos.m_nQsbs==ZSZQ_DLL && reqIndex==TDX_WTCD)
					tmpstr=@"您的申请已提交!";
				else if(eGetData.clientinfos.m_nQsbs==ZTZQ_DLL && reqIndex==TDX_WTCD)
					tmpstr=[NSString stringWithFormat:@"撤单已提交!%@",CDTIP_ZTZQ_DLL];
				else 
					tmpstr=@"撤单已提交!";
				m_ncancelIndex=0;
				NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
												 defaultButton: @"确定"
											   alternateButton: nil
												   otherButton: nil
									 informativeTextWithFormat: @"%@",tmpstr];
				[alert runModal];
			}
			else 
			{
				if(pParsers.btipflag)
				{
					if(eGetData.clientinfos.m_nQsbs==ZSZQ_DLL)
						tmpstr=[NSString stringWithFormat:@"您的申请处理失败,原因是:\r%@",pParsers.psErrorData];
					else if(eGetData.clientinfos.m_nQsbs==GJZQ_DLL)
					{
						if(reqIndex==TDX_WTCD)
							tmpstr=[NSString stringWithFormat:@"撤单失败!\r\r证券系统返回的原因:\r%@",pParsers.psErrorData];
						else if(reqIndex==TDX_JJCD)
							tmpstr=[NSString stringWithFormat:@"基金撤单请求处理失败!\r\r证券系统返回的原因是:\r%@",pParsers.psErrorData];
					}
					else if(eGetData.clientinfos.m_nQsbs==ZTZQ_DLL && reqIndex==TDX_WTCD)
						tmpstr=[NSString stringWithFormat:@"撤单已提交!\r\r证券系统返回的原因:\r%@%@",pParsers.psErrorData,CDTIP_ZTZQ_DLL];
					else if(reqIndex==TDX_WTCD)
						tmpstr=[NSString stringWithFormat:@"撤单已提交!\r\r证券系统返回的原因:\r%@",pParsers.psErrorData];
					else if(reqIndex==TDX_JJCD)
					{
						if(eGetData.clientinfos.tradeccf.bweaktip)
							tmpstr=[NSString stringWithFormat:@"撤单已提交!\r\r证券系统返回的原因:\r%@",pParsers.psErrorData];
						else 
							tmpstr=[NSString stringWithFormat:@"错误种类:%@ 错误代码:%@ 错误信息:%@",pParsers.psErrorSign,pParsers.psErrorNum,pParsers.psErrorData];
					}
					m_ncancelIndex=0;
					m_bfirstalertflag=YES;
					NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
													 defaultButton: @"确定"
												   alternateButton: nil
													   otherButton: nil
										 informativeTextWithFormat: @"%@",tmpstr];
					[alert runModal];
				}
			}
			[self stopanimate];
			if(pParsers.bsucflag)
				[self refreshpage];
		}
			break;
		case TDX_WTCDS:
		{
			if(pParsers.bsucflag)
			{
				m_nsuc++;
			}
			else 
			{
				m_nfail++;
				if(pParsers.btipflag)
				{
					[m_errinfo release];
					m_errinfo = [[NSString alloc ] initWithFormat:@"%@",pParsers.psErrorData];
				}
			}
			NSArray * tempArray=nil;
			int gridnum=[showDataArray count],bsflag=0;
			for(int i=m_ncurindex+1;i<gridnum;i++)
			{
				tempArray = [showDataArray objectAtIndex:i];
				
				if(tempArray && [tempArray count]>m_bsflagindex && m_bsflagindex>=0)
				{
					if(m_ncdflag==3 || m_ncdflag==4)
					{
						bsflag=[[tempArray objectAtIndex:m_bsflagindex]intValue];
						if(m_ncdflag==3 && bsflag!=0)
							continue;
						if(m_ncdflag==4 && bsflag!=1)
							continue;
					}
					m_ntotal++;
					m_ncurindex=i;
					[eGetData sendTradeWTData:TDX_WTCDS objIndex:self.tradeindex Session:eGetData.inputSave.sessionID gpCode:(CHECKINDEX(m_gpcodeindex)?[tempArray objectAtIndex:m_gpcodeindex]:@"") Wtbhs:(CHECKINDEX(m_wtbhindex)?[tempArray objectAtIndex:m_wtbhindex]:@"") scflags:(CHECKINDEX(m_scflagindex)?[tempArray objectAtIndex:m_scflagindex]:@"")  zhlbs:(CHECKINDEX(m_nzhlbindex)?[tempArray objectAtIndex:m_nzhlbindex]:@"")   gddms:(CHECKINDEX(m_ngddmindex)?[tempArray objectAtIndex:m_ngddmindex]:@"")   mmbzs:(CHECKINDEX(m_bsflagindex)?[tempArray objectAtIndex:m_bsflagindex]:@"")];
					return YES;
				}
				else 
				{
					if(m_errinfo==nil)
						m_errinfo=[[NSString alloc]  initWithFormat:@"%@",@"未找到委托单!"];
				}
			}
			m_ncdflag=0;
			NSString *tmpstr=@"";
			if(eGetData.clientinfos.m_nQsbs==ZSZQ_DLL)
			{
				if(m_nfail==0)
					tmpstr=@"您的申请已提交!";
				else if(m_nfail==m_ntotal)
					tmpstr=[NSString stringWithFormat:@"您的申请处理失败,原因是:\r%@",m_errinfo];
				else  
					tmpstr=[NSString stringWithFormat:@"您的申请已提交,部分申请处理失败,原因是:\r%@",m_errinfo];
			}
			else 
			{
				if(m_nfail==0)
				{
					if(eGetData.clientinfos.m_nQsbs==ZTZQ_DLL)
						tmpstr=[NSString stringWithFormat:@"撤单已提交!%@",CDTIP_ZTZQ_DLL];
					else 
						tmpstr=@"撤单已提交!";
				}
				else 
				{
					if(eGetData.clientinfos.m_nQsbs==GJZQ_DLL)
						tmpstr=[NSString stringWithFormat:@"撤单失败!\r\r证券系统返回的原因:\r%@",m_errinfo];
					else if(eGetData.clientinfos.m_nQsbs==ZTZQ_DLL)
						tmpstr=[NSString stringWithFormat:@"撤单已提交!\r\r证券系统返回的原因:\r%@%@",m_errinfo,CDTIP_ZTZQ_DLL];
					else 
						tmpstr=[NSString stringWithFormat:@"撤单已提交!\r\r证券系统返回的原因:\r%@",m_errinfo];
				}
			}
			m_ncancelIndex=0;
			NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
											 defaultButton: @"确定"
										   alternateButton: nil
											   otherButton: nil
								 informativeTextWithFormat: @"%@",tmpstr];
			[alert runModal];
			[m_errinfo release];
			m_errinfo=nil;
			[self stopanimate];
			if(m_nsuc>0)
			{
				[self refreshpage];
			}
		}
			break;
		case TDX_WTCDSBYSELECT:
		{
			
			if(pParsers.bsucflag)
			{
				m_nsuc++;
				[myTableView deselectRow:m_ncurindex];
			}
			else 
			{
				[myTableView deselectRow:m_ncurindex];
				m_nfail++;
				if(pParsers.btipflag)
				{
					[m_errinfo release];
					m_errinfo = [[NSString alloc ] initWithFormat:@"%@",pParsers.psErrorData];
				}
			}
			
			NSArray * tempArray=nil;
			NSIndexSet * tempSet = [myTableView selectedRowIndexes];
			NSLog(@"%i",m_ncurindex);
			if (m_ntotal < multiSelectCount) {
				int i = [tempSet indexGreaterThanIndex:m_ncurindex];
				if (i < [showDataArray count]) {
					tempArray = [showDataArray objectAtIndex:i];
					m_ncurindex=i;
					m_ntotal++;
					[eGetData sendTradeWTData:TDX_WTCDSBYSELECT objIndex:self.tradeindex Session:eGetData.inputSave.sessionID gpCode:(CHECKINDEX(m_gpcodeindex)?[tempArray objectAtIndex:m_gpcodeindex]:@"") Wtbhs:(CHECKINDEX(m_wtbhindex)?[tempArray objectAtIndex:m_wtbhindex]:@"") scflags:(CHECKINDEX(m_scflagindex)?[tempArray objectAtIndex:m_scflagindex]:@"")  zhlbs:(CHECKINDEX(m_nzhlbindex)?[tempArray objectAtIndex:m_nzhlbindex]:@"")   gddms:(CHECKINDEX(m_ngddmindex)?[tempArray objectAtIndex:m_ngddmindex]:@"")   mmbzs:(CHECKINDEX(m_bsflagindex)?[tempArray objectAtIndex:m_bsflagindex]:@"")];
					return YES;
				}
			}
			
			m_ncdflag=0;
			NSString *tmpstr=@"";
			if(eGetData.clientinfos.m_nQsbs==ZSZQ_DLL)
			{
				if(m_nfail==0)
					tmpstr=@"您的申请已提交!";
				else if(m_nfail==m_ntotal)
					tmpstr=[NSString stringWithFormat:@"您的申请处理失败,原因是:\r%@",m_errinfo];
				else  
					tmpstr=[NSString stringWithFormat:@"您的申请已提交,部分申请处理失败,原因是:\r%@",m_errinfo];
			}
			else 
			{
				if(m_nfail==0)
				{
					if(eGetData.clientinfos.m_nQsbs==ZTZQ_DLL)
						tmpstr=[NSString stringWithFormat:@"撤单已提交!%@",CDTIP_ZTZQ_DLL];
					else 
						tmpstr=@"撤单已提交!";
				}
				else 
				{
					if(eGetData.clientinfos.m_nQsbs==GJZQ_DLL)
						tmpstr=[NSString stringWithFormat:@"撤单失败!\r\r证券系统返回的原因:\r%@",m_errinfo];
					else if(eGetData.clientinfos.m_nQsbs==ZTZQ_DLL)
						tmpstr=[NSString stringWithFormat:@"撤单已提交!\r\r证券系统返回的原因:\r%@%@",m_errinfo,CDTIP_ZTZQ_DLL];
					else 
						tmpstr=[NSString stringWithFormat:@"撤单已提交!\r\r证券系统返回的原因:\r%@",m_errinfo];
				}
			}
			m_ncancelIndex=0;
			NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
											 defaultButton: @"确定"
										   alternateButton: nil
											   otherButton: nil
								 informativeTextWithFormat: @"%@",tmpstr];
			[alert runModal];
			[m_errinfo release];
			m_errinfo=nil;
			[self stopanimate];
			if(m_nsuc>0)
			{
				[self refreshpage];
			}
			
		}
			break;
	
		case TDX_JJCDS:
		{
			m_ncdflag=0;
			if(pParsers.bsucflag)
			{
				m_nsuc++;
			}
			else 
			{
				m_nfail++;
				if(pParsers.btipflag)
				{
					[m_errinfo release];
					if(eGetData.clientinfos.tradeccf.bweaktip && (eGetData.clientinfos.m_nQsbs!=ZSZQ_DLL && eGetData.clientinfos.m_nQsbs!=GJZQ_DLL))
						m_errinfo = [[NSString alloc ] initWithFormat:@"错误种类:%@ 错误代码:%@ 错误信息:%@",pParsers.psErrorSign,pParsers.psErrorNum,pParsers.psErrorData];
					else 
						m_errinfo = [[NSString alloc ] initWithFormat:@"%@",pParsers.psErrorData];
				}
			}
			NSArray * tempArray=nil;
			int gridnum=[showDataArray count];
			for(int i=m_ncurindex+1;i<gridnum;i++)
			{
				tempArray = [showDataArray objectAtIndex:i];
				m_ncurindex=i;
				m_ntotal++;
				[eGetData sendTradeWTData:TDX_JJCDS objIndex:self.tradeindex Sessiomn:eGetData.inputSave.sessionID 
								   jjCode:(CHECKINDEX(m_jjcodeindex)?[tempArray objectAtIndex:m_jjcodeindex]:@"") 
								   jjGsdm:(CHECKINDEX(m_jjgsdmindex)?[tempArray objectAtIndex:m_jjgsdmindex]:@"")  
								   jjZhdm:(CHECKINDEX(m_jjzhdmindex)?[tempArray objectAtIndex:m_jjzhdmindex]:@"")  
								   WTDate:(CHECKINDEX(m_wtdateindex)?[tempArray objectAtIndex:m_wtdateindex]:@"")  
								 WTNumber:(CHECKINDEX(m_wtnumindex)?[tempArray objectAtIndex:m_wtnumindex]:@"")  
								  WTValue:(CHECKINDEX(m_wtvalueindex)?[tempArray objectAtIndex:m_wtvalueindex]:@"") 
								  WTIndex:(CHECKINDEX(m_wtbhindex)?[tempArray objectAtIndex:m_wtbhindex]:@"") ];
				return YES;
			}
			NSString *tmpstr=@"";
			{
				if(m_nfail==0)
				{
					tmpstr=@"撤单已提交!";
				}
				else 
				{
					if(eGetData.clientinfos.m_nQsbs==GJZQ_DLL)
						tmpstr=[NSString stringWithFormat:@"基金撤单请求处理失败,证券系统返回的原因:\r%@",m_errinfo];
					else if(eGetData.clientinfos.m_nQsbs==ZSZQ_DLL)
						tmpstr=[NSString stringWithFormat:@"您的申请处理失败,原因是:\r%@",m_errinfo];
					else if(eGetData.clientinfos.tradeccf.bweaktip)
						tmpstr=[NSString stringWithFormat:@"%@",m_errinfo];
					else 
						tmpstr=[NSString stringWithFormat:@"撤单已提交!\r\r证券系统返回的原因:\r%@",m_errinfo];
				}
			}
			m_ncancelIndex=0;
			NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
											 defaultButton: @"确定"
										   alternateButton: nil
											   otherButton: nil
								 informativeTextWithFormat: @"%@",tmpstr];
			[alert runModal];
			[m_errinfo release];
			m_errinfo=nil;
			[self stopanimate];
			if(m_nsuc>0)
			{
				[self refreshpage];
			}
		}
			break;
		case	TDX_JJZNDTCD:
		{
			m_ncdflag=0;
			NSString *tmpstr=@"";
			if(pParsers.bsucflag)
			{
				if(eGetData.clientinfos.m_nQsbs==ZXJT_DLL || eGetData.clientinfos.m_nQsbs==BHZQ_DLL)
					tmpstr=@"新版定时定额撤销请求已提交";
				else 
				{
					NSString *wtbh=[pParsers getFieldData:0 fieldFlag:TDX_ID_WTBH];
					if(eGetData.clientinfos.m_nQsbs==DXZQ_DLL)
					{
						if([wtbh length]==0)
							tmpstr=@"撤销新版定时定额申请已提交";
						else 
							tmpstr=[NSString stringWithFormat:@"撤销新版定时定额申请已提交,委托编号为: %@",wtbh];
					}
					else if(eGetData.clientinfos.m_nQsbs==XDZQ_DLL)
					{
						if([wtbh length]==0)
							tmpstr=@"撤销基金定投已提交";
						else 
							tmpstr=[NSString stringWithFormat:@"撤销基金定投已提交,委托编号为: %@",wtbh];
					}
					else 
					{
						if([wtbh length]==0)
						{
							if(eGetData.clientinfos.m_nQsbs==GHZQ_DLL)
								tmpstr=@"撤销定时定额已提交";
							else 
								tmpstr=@"撤销智能定投已提交";
						}
						else 
							tmpstr=[NSString stringWithFormat:@"撤销智能定投已提交,委托编号为: %@",wtbh];
						
					}
				}
				m_ncancelIndex=0;
				NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
												 defaultButton: @"确定"
											   alternateButton: nil
												   otherButton: nil
									 informativeTextWithFormat: @"%@",tmpstr];
				[alert runModal];
			}
			else 
			{
				if(pParsers.btipflag)
				{
					m_ncancelIndex=0;
					if(eGetData.clientinfos.tradeccf.bweaktip)
						tmpstr=[NSString stringWithFormat:@"%@",pParsers.psErrorData];
					else 
						tmpstr=[NSString stringWithFormat:@"错误种类:%@ 错误代码:%@ 错误信息:%@",pParsers.psErrorSign,pParsers.psErrorNum,pParsers.psErrorData];
					NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
													 defaultButton: @"确定"
												   alternateButton: nil
													   otherButton: nil
										 informativeTextWithFormat: @"%@",tmpstr];
					[alert runModal];
				}
			}
			[self stopanimate];
			if(pParsers.bsucflag)
				[self refreshpage];
		}
			break;
		case TDX_JJZNDTCDS:
		{
			m_ncdflag=0;
			if(pParsers.bsucflag)
			{
				m_nsuc++;
			}
			else 
			{
				m_nfail++;
				if(pParsers.btipflag)
				{
					[m_errinfo release];
					if(eGetData.clientinfos.tradeccf.bweaktip)
						m_errinfo = [[NSString alloc ] initWithFormat:@"错误种类:%@ 错误代码:%@ 错误信息:%@",pParsers.psErrorSign,pParsers.psErrorNum,pParsers.psErrorData];
					else 
						m_errinfo = [[NSString alloc ] initWithFormat:@"%@",pParsers.psErrorData];
				}
			}
			NSArray * tempArray=nil;
			int gridnum=[showDataArray count];
			for(int i=m_ncurindex+1;i<gridnum;i++)
			{
				tempArray = [showDataArray objectAtIndex:i];
				m_ncurindex=i;
				m_ntotal++;
				NSString *jyje=(CHECKINDEX(m_njyjeindex)?[tempArray objectAtIndex:m_njyjeindex]:@"");
				if([jyje length]==0)
					jyje=(CHECKINDEX(m_noccurjeindex)?[tempArray objectAtIndex:m_noccurjeindex]:@"");
				
				NSString *strqmtj=@"";
				int nlx=(CHECKINDEX(m_nlxindex)?[[tempArray objectAtIndex:m_nlxindex] intValue]:0); 
				switch (nlx) {
					case 0:
					{
						NSString *ksrq=(CHECKINDEX(m_nksrqindex)?[tempArray objectAtIndex:m_nksrqindex]:@"");
						NSString *zzrq=(CHECKINDEX(m_nzzrqindex)?[tempArray objectAtIndex:m_nzzrqindex]:@"");
						NSString *syear=[ksrq substringWithRange:NSMakeRange(0, 4)];
						NSString *smonth=[ksrq substringWithRange:NSMakeRange(4, 2)];
						NSString *sday=[ksrq substringWithRange:NSMakeRange(6, 2)];
						NSString *eyear=[zzrq substringWithRange:NSMakeRange(0, 4)];
						NSString *emonth=[zzrq substringWithRange:NSMakeRange(4, 2)];
						NSString *eday=[zzrq substringWithRange:NSMakeRange(6, 2)];
						if(eGetData.clientinfos.m_nQsbs==XDZQ_DLL)
							strqmtj=[NSString stringWithFormat:@"下一扣款日: %@年%@月%@日\r协议期限: %@年%@月%@日\r",syear,smonth,sday,eyear,emonth,eday];
						else 
							strqmtj=[NSString stringWithFormat:@"开始日期: %@年%@月%@日\r结束日期: %@年%@月%@日\r",syear,smonth,sday,eyear,emonth,eday];
					}
						break;
					case 1:
					{
						strqmtj=[NSString stringWithFormat:@"到期次数: %@次\r",(CHECKINDEX(m_ndqtjindex)?[tempArray objectAtIndex:m_ndqtjindex]:@"")];
					}
						break;
					case 2:
					{
						strqmtj=[NSString stringWithFormat:@"到期金额: %@元\r",(CHECKINDEX(m_ndqtjindex)?[tempArray objectAtIndex:m_ndqtjindex]:@"")];
					}
						break;
					default:
						break;
				}
				
				[eGetData sendTradeWTData:TDX_JJZNDTCDS objIndex:self.tradeindex Sessiomn:eGetData.inputSave.sessionID 
								   jjCode:(CHECKINDEX(m_jjcodeindex)?[tempArray objectAtIndex:m_jjcodeindex]:@"") 
								   jjGsdm:(CHECKINDEX(m_jjgsdmindex)?[tempArray objectAtIndex:m_jjgsdmindex]:@"")  
								   jjZhdm:(CHECKINDEX(m_jjzhdmindex)?[tempArray objectAtIndex:m_jjzhdmindex]:@"")  
									 WTBH:(CHECKINDEX(m_wtbhindex)?[tempArray objectAtIndex:m_wtbhindex]:@"") 
									 WTLX:(CHECKINDEX(m_nlxindex)?[tempArray objectAtIndex:m_nlxindex]:@"") 
								   MYKKRQ:(CHECKINDEX(m_nmykkrqindex)?[tempArray objectAtIndex:m_nmykkrqindex]:@"") 
									 KSRQ:(CHECKINDEX(m_nksrqindex)?[tempArray objectAtIndex:m_nksrqindex]:@"") 
									 ZZRQ:(CHECKINDEX(m_nzzrqindex)?[tempArray objectAtIndex:m_nzzrqindex]:@"") 
									 JYJE:jyje 
									  LSH:(CHECKINDEX(m_nlshindex)?[tempArray objectAtIndex:m_nlshindex]:@"") 
									 QMTJ:strqmtj  
									 MODE:(CHECKINDEX(m_nkkzqbhindex)?[tempArray objectAtIndex:m_nkkzqbhindex]:@"") 
									 WTRQ:(CHECKINDEX(m_nwtrqindex)?[tempArray objectAtIndex:m_nwtrqindex]:@"")];
				return YES;
			}
			NSString *tmpstr=@"";
			{
				if(m_nfail==0)
				{
					if(eGetData.clientinfos.m_nQsbs==ZXJT_DLL || eGetData.clientinfos.m_nQsbs==BHZQ_DLL)
						tmpstr=@"新版定时定额撤销请求已提交";
					else 
						tmpstr=[NSString stringWithFormat:@"撤单请求发送完成,总撤单次数%i,成功次数%i",m_ntotal,m_nsuc];
				}
				else 
				{
					if(eGetData.clientinfos.m_nQsbs==ZXJT_DLL || eGetData.clientinfos.m_nQsbs==BHZQ_DLL)
						tmpstr=[NSString stringWithFormat:@"新版定时定额撤销请求已提交\r证券系统返回的原因:\r%@",m_errinfo];
					else 
						tmpstr=[NSString stringWithFormat:@"撤单请求发送完成,总撤单次数%i,成功次数%i,失败次数%i\r证券系统返回的原因:\r%@",m_ntotal,m_nsuc,m_nfail,m_errinfo];
				}
			}
			m_ncancelIndex=0;
			NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
											 defaultButton: @"确定"
										   alternateButton: nil
											   otherButton: nil
								 informativeTextWithFormat: @"%@",tmpstr];
			[alert runModal];
			[m_errinfo release];
			m_errinfo=nil;
			[self stopanimate];
			if(m_nsuc>0)
			{
				[self refreshpage];
			}
		}
			break;
		default:
		{
			int queryindex=[self GetQueryindexFromTag];
			if((reqIndex-npagemode)!=queryindex)
				break;
			int index=reqIndex-queryindex;
			switch (index) {
				case PAGE_PREVIOUSINDEX:
				case PAGE_NEXTINDEX:
				{
					[self cleardsdata];
					int tmptotalline=0;
					BOOL bsucflag=YES;
                    [m_positionstr release];
					m_positionstr=[[NSString alloc] initWithFormat:@"%@",[eGetData getCXInfo:pParsers listdata:showDataArray withqueryindex:queryindex withrownum:(int *)(&tmptotalline) withsucflag:(BOOL *)(&bsucflag)]];
					[self initGridFrame:pParsers];
					[self resetToolbar];
					[myTableView reloadData];
					[self stopanimate];
				}
					break;
				case PAGE_REFRESHINDEX:
				{
					
					
					[m_positionstr release];
					BOOL bsucflag=YES;
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
                            [eGetData sendTradeQueryData:[self GetQueryindexFromTag] pageIndex:([self GetQueryindexFromTag]+PAGE_REFRESHINDEX) objIndex:self.tradeindex Session:eGetData.inputSave.sessionID StartIndex:(pageIndex*PAGE_ROWNUM+[eGetData GetStartIndex]) ReqLines:PAGE_ROWNUM TotleLine:(PAGE_ROWNUM*MAX_PAGENUM) positionstr:m_positionstr];
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
					[self initGridFrame:pParsers];
					[self resetToolbar];
					[myTableView reloadData];
					[self stopanimate];
					if(m_bfirstviewflag)
					{
						m_bfirstviewflag=NO;
					}
				}
					break;
				default:
					break;
			}
		}
			break;
	}
	return YES;
}



-(void)changezndt
{
}

-(void) cleanscreen
{
	m_bdrwtcx=NO;
	m_bjjzndtcx=NO;
	m_blczndtcx=NO;
	[self cleardsdata];
}

-(void)buttonClick:(id)sender{
    
    if([self IsCanQueryOther]==NO)
        return;
    NSButton *pbut=(NSButton *)sender;
    if(pbut.tag==2)//下页
    {
        [self nextpage];
    }
	else if(pbut.tag==3)//上页
    {
        [self previouspage];
    }
    else if(pbut.tag==1)//首页
    {
        
    }
    else if(pbut.tag==4)//尾页
    {
        
    }
    else if(pbut.tag==5)//刷新
    {
        [self refreshpage];
    }
}

@end
