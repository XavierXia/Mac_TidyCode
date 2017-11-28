//
//  EUGrid.m
//  tdxMac
//
//  Created by tdx on 11-8-16.
//  Copyright 2011 武汉. All rights reserved.
//

#import "EUGrid.h"

#define HEIGHTOFROW 25.0f
#define TITLE_HEIGHT 18.0f
#define FIXWIDTH 209.0f
#define BOTTOMBAR_HEIGHT 20
#define FENLEI_WIDTH 90
#define FIXTABLE_TAG 1
#define ORDTABLE_TAG 2

@implementation EUGrid

@synthesize gridInfo,tableView,scrollView,gridArray;



-(void) setFrame:(NSRect)frameRect{
	selectIndex = 0;
	[super setFrame:frameRect];
	viewRect = frameRect;
	[scrollView setFrame:NSMakeRect(FIXWIDTH, BOTTOMBAR_HEIGHT, frameRect.size.width-FIXWIDTH-2, frameRect.size.height-BOTTOMBAR_HEIGHT)];
	[tableView setFrame:NSMakeRect(FIXWIDTH, BOTTOMBAR_HEIGHT, frameRect.size.width-FIXWIDTH, frameRect.size.height-BOTTOMBAR_HEIGHT)];
	
	[fixScrollView setFrame:NSMakeRect(2, BOTTOMBAR_HEIGHT, FIXWIDTH, frameRect.size.height-BOTTOMBAR_HEIGHT)];
	[fixTableView setFrame:NSMakeRect(0, BOTTOMBAR_HEIGHT, FIXWIDTH, frameRect.size.height-BOTTOMBAR_HEIGHT)];
    
	int rowNum = (frameRect.size.height - TITLE_HEIGHT-BOTTOMBAR_HEIGHT)/ (HEIGHTOFROW+2);

    if (gridInfo.wantnum != rowNum) {
		gridInfo.wantnum = rowNum;
		[self getTheData:-1 theColtype:-1];
	}
	else {
		;
	}

}

- (id)initWithData:(NSRect)frame theData:(EGetData *)_eGetData{
    self = [super initWithData:frame theData:_eGetData];
    if (self) {
		
		viewRect = frame;
        // Initialization code here.
		selectIndex = 0;
		oriColumnIndex=-1;
		desColumnIndex=-1;
		moveFlag = NO;
		
		widthArray = [NSArray arrayWithObjects:@"50",@"72",@"77",@"72",@"72",@"72",@"72",@"72",@"72",@"92",@"72",@"72",@"72",@"72",@"72",@"82",@"72",@"92",@"92",@"92",@"92",@"72",@"72",@"50",nil];
		titleArray= [NSArray arrayWithObjects:@"序号",@"代码",@"名称",@"涨幅",@"现价",@"涨跌",@"买入价",@"卖出价",@"昨收",@"总量",@"量比",@"换手",@"今开",@"最高",@"最低",@"总金额",@"振幅",@"总股本",@"流通股本",@"总市值",@"市盈(动)",@"内盘",@"外盘",@"",nil];
		identifierArray= [NSArray arrayWithObjects:@"index",@"code",@"name",@"zhangfu",@"nowprice",@"zhangdie",@"buyPrice",@"sellPrice",@"closeprice",@"totlevol",@"nowvol",@"huanshou",@"openprice",@"highprice",@"lowprice",@"amount",@"zhenfu",@"zgb",@"ltgb",@"zsz",@"syl",@"neipan",@"waipan",@"reverse",nil];
		
		int rowNum = (frame.size.height - 26)/ (HEIGHTOFROW+2);
		
		gridInfo = [[GridInfo alloc] init];
		gridInfo.extype = 0;
		gridInfo.startxh = 0;
		gridInfo.wantnum = rowNum;
		gridInfo.grid_domain =6;
		gridInfo.coltype = 14;
		gridInfo.sorttype = 1;
		
		NSRect scrollFrame = frame;
		scrollFrame.origin.x = FIXWIDTH;
		scrollFrame.origin.y =BOTTOMBAR_HEIGHT;
		scrollFrame.size.width = frame.size.width - FIXWIDTH;
		scrollFrame.size.height =frame.size.height -  BOTTOMBAR_HEIGHT;
		scrollView=[[NSScrollView alloc] initWithFrame:scrollFrame];
		[scrollView setHasHorizontalScroller:NO];
		[scrollView setHorizontalScroller:nil];
		[scrollView setHasVerticalScroller:NO];
		[scrollView setVerticalScroller:nil];
		[scrollView setDrawsBackground:NO];
		
		
		
		
		NSRect tableFrame = frame;
		tableFrame.origin.x = FIXWIDTH;
		tableFrame.origin.y =BOTTOMBAR_HEIGHT;
		tableFrame.size.width = frame.size.width - FIXWIDTH;
		tableFrame.size.height =frame.size.height -  BOTTOMBAR_HEIGHT; 
		tableView = [[EuTableView alloc] initWithFrame:tableFrame];
		[tableView setAutosaveName:@""];
        tableView.m_delegate=self;
		
		NSRect titleFrame =frame;
		titleFrame.origin.x = FIXWIDTH;
		titleFrame.size.width = frame.size.width - FIXWIDTH;
		titleFrame.origin.y=frame.size.height-TITLE_HEIGHT;
		titleFrame.size.height=TITLE_HEIGHT;

		NSTableHeaderView *tableHeadView=[[NSTableHeaderView alloc] initWithFrame:titleFrame];
		[tableView setHeaderView:tableHeadView];
		[tableHeadView release];
		[tableView setAutoresizesSubviews:FULLSIZE];
		[tableView setBackgroundColor:[NSColor clearColor]];
		[[tableView enclosingScrollView] setDrawsBackground:NO];
		[tableView setGridColor:[NSColor lightGrayColor]];
		[tableView setAutosaveTableColumns:NO];
		[tableView setAllowsEmptySelection:NO];
		[tableView setAllowsColumnSelection:NO];
		[tableView setAllowsColumnReordering:NO];
		[tableView setAllowsColumnResizing:NO];
		[tableView setFocusRingType:1];
		[tableView setTarget: self];
		[tableView setAction:@selector(singleClick:)];
		[tableView setDoubleAction:@selector(doubleClick:)];
		[tableView setTag:ORDTABLE_TAG];
		
		
		[tableView setDataSource:self];
		[tableView setDelegate:self];

		[scrollView setDocumentView:tableView];
		[scrollView setBackgroundColor:[NSColor clearColor]];
		[self addSubview:scrollView];
		[scrollView release];
		
		
		
		fixScrollView=[[NSScrollView alloc] initWithFrame:NSMakeRect(0, frame.origin.y, FIXWIDTH, frame.size.height-TITLE_HEIGHT)];
		[fixScrollView setHasHorizontalScroller:NO];
		[fixScrollView setHorizontalScroller:nil];
		[fixScrollView setHasVerticalScroller:NO];
		[fixScrollView setVerticalScroller:nil];
		[fixScrollView setDrawsBackground:NO];

		fixTableView = [[EuTableView alloc] initWithFrame:NSMakeRect(0, frame.origin.y, FIXWIDTH,  frame.size.height-TITLE_HEIGHT)];
		[fixTableView setAutosaveName:@""];
		fixTableView.m_delegate=self;
		titleFrame.origin.x = 0;
		titleFrame.size.width = FIXWIDTH;
		titleFrame.origin.y=frame.size.height-TITLE_HEIGHT;
		titleFrame.size.height=TITLE_HEIGHT;
		
		tableHeadView=[[NSTableHeaderView alloc] initWithFrame:titleFrame];
		[fixTableView setHeaderView:tableHeadView];
		[tableHeadView release];
		[fixTableView setAutoresizesSubviews:FULLSIZE];
		[fixTableView setBackgroundColor:[NSColor clearColor]];
		[[fixTableView enclosingScrollView] setDrawsBackground:NO];
		[fixTableView setGridColor:[NSColor lightGrayColor]];
		[fixTableView setAutosaveTableColumns:NO];
		[fixTableView setAllowsEmptySelection:NO];
		[fixTableView setAllowsColumnSelection:NO];
		[fixTableView setAllowsColumnReordering:NO];
		[fixTableView setAllowsColumnResizing:NO];
		[fixTableView setFocusRingType:1];
		[fixTableView setTarget:self];
		[fixTableView setAction:@selector(singleClick:)];
		[fixTableView setDoubleAction:@selector(doubleClick:)];
		[fixTableView setTag:FIXTABLE_TAG];
		
		
		[fixTableView setDataSource:self];
		[fixTableView setDelegate:self];
		
		[fixScrollView setDocumentView:fixTableView];
		[fixScrollView setBackgroundColor:[NSColor clearColor]];
		[self addSubview:fixScrollView];
		[fixScrollView release];
		
		
		for (int i = 0; i<3 && i<[titleArray count] && i<[widthArray count]; i++) {
			[self addColumnEx:[NSString stringWithFormat:@"%i",i] withTitle:[titleArray objectAtIndex:i] withWidth:[[widthArray objectAtIndex:i]intValue]];
		}
		
		
		for (int i = 3;  i<[titleArray count] && i<[widthArray count]; i++) {
			[self addColumn:[NSString stringWithFormat:@"%i",i] withTitle:[titleArray objectAtIndex:i] withWidth:[[widthArray objectAtIndex:i]intValue]];
		}
		
		gridArray = nil;
		lastColumn = nil;
		
		[self dealRightMenu];
		
		
		NSRect buttonFrame;


		buttonFrame.origin.x = 50 *0 ;
		buttonFrame.origin.y = 0;
		buttonFrame.size.width = FENLEI_WIDTH;
		buttonFrame.size.height = 20;
		sortButton = [[NSPopUpButton alloc]initWithFrame:buttonFrame pullsDown:NO];
		
		NSMenu * sortMenu = [[NSMenu allocWithZone:[NSMenu menuZone]] initWithTitle:@""];
		
		NSMenuItem *newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"上证A股" action:@selector(domainMenu:) keyEquivalent:@""];
		[newItem setEnabled:YES];
		[newItem setTarget:self];
		[newItem setTag:DOMAIN_SHAG];
		[sortMenu addItem:newItem];
		[newItem release];
		
		newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"上证B股" action:@selector(domainMenu:) keyEquivalent:@""];
		[newItem setEnabled:YES];
		[newItem setTarget:self];
		[newItem setTag:DOMAIN_SHBG];
		[sortMenu addItem:newItem];
		[newItem release];
		
		newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"深证A股" action:@selector(domainMenu:) keyEquivalent:@""];
		[newItem setEnabled:YES];
		[newItem setTarget:self];
		[newItem setTag:DOMAIN_SZAG];
		[sortMenu addItem:newItem];
		[newItem release];
		
		newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"深证B股" action:@selector(domainMenu:) keyEquivalent:@""];
		[newItem setEnabled:YES];
		[newItem setTarget:self];
		[newItem setTag:DOMAIN_SZBG];
		[sortMenu addItem:newItem];
		[newItem release];
		
		newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"上证债券" action:@selector(domainMenu:) keyEquivalent:@""];
		[newItem setEnabled:YES];
		[newItem setTarget:self];
		[newItem setTag:DOMAIN_SHZQ];
		[sortMenu addItem:newItem];
		[newItem release];
		
		newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"深证债券" action:@selector(domainMenu:) keyEquivalent:@""];
		[newItem setEnabled:YES];
		[newItem setTarget:self];
		[newItem setTag:DOMAIN_SZZQ];
		[sortMenu addItem:newItem];
		[newItem release];
		
		//
		newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"沪深A股" action:@selector(domainMenu:) keyEquivalent:@""];
		[newItem setEnabled:YES];
		[newItem setTarget:self];
		[newItem setTag:DOMAIN_ALLAG];
		[sortMenu addItem:newItem];
		[newItem release];
		
		newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"沪深B股" action:@selector(domainMenu:) keyEquivalent:@""];
		[newItem setEnabled:YES];
		[newItem setTarget:self];
		[newItem setTag:DOMAIN_ALLBG];
		[sortMenu addItem:newItem];
		[newItem release];
		
		newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"沪深债券" action:@selector(domainMenu:) keyEquivalent:@""];
		[newItem setEnabled:YES];
		[newItem setTarget:self];
		[newItem setTag:DOMAIN_ALLZQ];
		[sortMenu addItem:newItem];
		[newItem release];
		
		newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"沪深基金" action:@selector(domainMenu:) keyEquivalent:@""];
		[newItem setEnabled:YES];
		[newItem setTarget:self];
		[newItem setTag:DOMAIN_ALLJJ];
		[sortMenu addItem:newItem];
		[newItem release];
		
		newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"所有股票" action:@selector(domainMenu:) keyEquivalent:@""];
		[newItem setEnabled:YES];
		[newItem setTarget:self];
		[newItem setTag:DOMAIN_ALLGP];
		[sortMenu addItem:newItem];
		[newItem release];
		
		newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"所有指数" action:@selector(domainMenu:) keyEquivalent:@""];
		[newItem setEnabled:YES];
		[newItem setTarget:self];
		[newItem setTag:DOMAIN_ALLZS];
		[sortMenu addItem:newItem];
		[newItem release];
		
		newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"中小企业" action:@selector(domainMenu:) keyEquivalent:@""];
		[newItem setEnabled:YES];
		[newItem setTarget:self];
		[newItem setTag:DOMAIN_CYZQ];
		[sortMenu addItem:newItem];
		[newItem release];
		
		newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"沪深权证" action:@selector(domainMenu:) keyEquivalent:@""];
		[newItem setEnabled:YES];
		[newItem setTarget:self];
		[newItem setTag:DOMAIN_SHQZ];
		[sortMenu addItem:newItem];
		[newItem release];
		
		newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"创业板" action:@selector(domainMenu:) keyEquivalent:@""];
		[newItem setEnabled:YES];
		[newItem setTarget:self];
		[newItem setTag:DOMAIN_CYB];
		[sortMenu addItem:newItem];
		[newItem release];
		
		newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"自选股" action:@selector(domainMenu:) keyEquivalent:@""];
		[newItem setEnabled:YES];
		[newItem setTarget:self];
		[newItem setTag:DOMAIN_SELF];
		[sortMenu addItem:newItem];
		[newItem release];
		
		[sortButton setMenu:sortMenu];
		[self addSubview:sortButton];
		[sortButton release];
		
		
		[sortButton selectItemAtIndex:6];
		
		buttonFrame.origin.x = FENLEI_WIDTH+50 *0 ;
		buttonFrame.origin.y = 0;
		buttonFrame.size.width = 50;
		buttonFrame.size.height = 20;
		AGButton = [[NSButton alloc]initWithFrame:buttonFrame];
		[AGButton setButtonType:NSPushOnPushOffButton];
		[AGButton setBezelStyle:6];
		[AGButton setTitle:@"A股"];
		[AGButton setTarget:self];
		[AGButton setAction:@selector(domainMenu:)];
		[AGButton setTag:DOMAIN_ALLAG];
		[self addSubview:AGButton];
		[AGButton release];
		
		buttonFrame.origin.x = FENLEI_WIDTH+50 *1 ;
		buttonFrame.origin.y = 0;
		buttonFrame.size.width = 50;
		buttonFrame.size.height = 20;
		ZXButton = [[NSButton alloc]initWithFrame:buttonFrame];
		[ZXButton setButtonType:NSPushOnPushOffButton];
		[ZXButton setBezelStyle:6];
		[ZXButton setTitle:@"中小"];
		[ZXButton setTarget:self];
		[ZXButton setAction:@selector(domainMenu:)];
		[ZXButton setTag:DOMAIN_CYZQ];
		[self addSubview:ZXButton];
		[ZXButton release];
		
		buttonFrame.origin.x = FENLEI_WIDTH+50 *2 ;
		buttonFrame.origin.y = 0;
		buttonFrame.size.width = 50;
		buttonFrame.size.height = 20;
		CYButton = [[NSButton alloc]initWithFrame:buttonFrame];
		[CYButton setButtonType:NSPushOnPushOffButton];
		[CYButton setBezelStyle:6];
		[CYButton setTitle:@"创业"];
		[CYButton setTarget:self];
		[CYButton setAction:@selector(domainMenu:)];
		[CYButton setTag:DOMAIN_CYB];
		[self addSubview:CYButton];
		[CYButton release];
		
		buttonFrame.origin.x = FENLEI_WIDTH+50 *3 ;
		buttonFrame.origin.y = 0;
		buttonFrame.size.width = 50;
		buttonFrame.size.height = 20;
		BGButton = [[NSButton alloc]initWithFrame:buttonFrame];
		[BGButton setButtonType:NSPushOnPushOffButton];
		[BGButton setBezelStyle:6];
		[BGButton setTitle:@"B股"];
		[BGButton setTarget:self];
		[BGButton setAction:@selector(domainMenu:)];
		[BGButton setTag:DOMAIN_ALLBG];
		[self addSubview:BGButton];
		[BGButton release];
		
		
		buttonFrame.origin.x =FENLEI_WIDTH+50 *4 ;
		buttonFrame.origin.y = 0;
		buttonFrame.size.width = 50;
		buttonFrame.size.height = 20;
		ZXGButton = [[NSButton alloc]initWithFrame:buttonFrame];
		[ZXGButton setButtonType:NSPushOnPushOffButton];
		[ZXGButton setBezelStyle:6];
		[ZXGButton setTitle:@"自选"];
		[ZXGButton setTarget:self];
		[ZXGButton setAction:@selector(domainMenu:)];
		[ZXGButton setTag:DOMAIN_SELF];
		[self addSubview:ZXGButton];
		[ZXGButton release];
	}
    return self;
}

-(void)dealRightMenu{
	NSMenu * gridMenu = [[NSMenu allocWithZone:[NSMenu menuZone]] initWithTitle:@""];
	NSMenuItem * newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"打开		F5" action:@selector(rightMenu:) keyEquivalent:@""];
	[newItem setEnabled:YES];
	[newItem setTarget:self];
	[newItem setTag:1];
	[gridMenu addItem:newItem];
	[newItem release];
	
	newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"基本资料" action:@selector(rightMenu:) keyEquivalent:@""];
	[newItem setEnabled:YES];
	[newItem setTarget:self];
	[newItem setTag:2];
	[gridMenu addItem:newItem];
	[newItem release];
	
	[gridMenu addItem:[NSMenuItem separatorItem]];
	
	newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"上一页		[" action:@selector(rightMenu:) keyEquivalent:@""];
	[newItem setEnabled:YES];
	[newItem setTarget:self];
	[newItem setTag:3];
	[gridMenu addItem:newItem];
	[newItem release];
	
	newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"下一页		]" action:@selector(rightMenu:) keyEquivalent:@""];
	[newItem setEnabled:YES];
	[newItem setTarget:self];
	[newItem setTag:4];
	[gridMenu addItem:newItem];
	[newItem release];
	
	if (gridInfo.grid_domain != DOMAIN_SELF) {
		[gridMenu addItem:[NSMenuItem separatorItem]];
		
		newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"加入自选	Ctrl+Z" action:@selector(rightMenu:) keyEquivalent:@""];
		[newItem setEnabled:YES];
		[newItem setTarget:self];
		[newItem setTag:5];
		[gridMenu addItem:newItem];
		[newItem release];
	}
	else {
		[gridMenu addItem:[NSMenuItem separatorItem]];
		
		newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"删除自选	Del" action:@selector(rightMenu:) keyEquivalent:@""];
		[newItem setEnabled:YES];
		[newItem setTarget:self];
		[newItem setTag:6];
		[gridMenu addItem:newItem];
		[newItem release];
		
	}
	[tableView setMenu:gridMenu];
	[fixTableView setMenu:gridMenu];
	[gridMenu release];
}

-(void)clearAllButton{
	[AGButton setState:NSOffState];
	[BGButton setState:NSOffState];
	[ZXButton setState:NSOffState];
	[CYButton setState:NSOffState];
	[ZXGButton setState:NSOffState];
}

-(void)domainMenu:(id)sender{
	[self clearAllButton];
	NSButton* tempbutton = sender;
	[tempbutton setState:NSOnState];
	if ([sender tag] != DOMAIN_SELF) {
		[operProcessDelegate getHQProcess:@"" gpSetcode:1 typeID:MAC_ZFPM_FUNC pareOne:[sender tag] paraTwo:-1];
	}
	else {
		[operProcessDelegate getHQProcess:@"" gpSetcode:1 typeID:MAC_ZFPM_FUNC pareOne:[sender tag] paraTwo:0];
	}

}

-(void)rightMenu:(id)sender{
	if ([tableView clickedRow]  < 0 && [fixTableView clickedRow]<0) {
		return;
	}
    if([tableView clickedRow]>=0)
        selectIndex = [tableView clickedRow];
    else if([fixTableView clickedRow]>=0)
        selectIndex = [fixTableView clickedRow];
	[self setNeedsDisplay:YES];
	
	SinHqInfo * tempInfo;
	
	switch ([sender tag]) {
		case 1:
			if (([gridArray count] < 1) || ([gridArray count]-1 < selectIndex ) || selectIndex<0){
				return;
			}
			if (gridInfo.grid_domain != DOMAIN_SELF) {
				 tempInfo = [gridArray objectAtIndex:selectIndex];
			}
			else {
				 tempInfo = [gridArray objectAtIndex:selectIndex];
			}

			[operProcessDelegate getHQProcess:tempInfo.gpcode gpSetcode:tempInfo.setcode typeID:MAC_ZST_FUNC pareOne:-1 paraTwo:-1];
			break;
		case 2://基本资料
			[operProcessDelegate getHQProcess:self.gpcode gpSetcode:self.setcode typeID:MAC_F10_FUNC pareOne:-1 paraTwo:-1];
			;
			break;
		case 3://上一页
			[self showPrePage];
			break;
		case 4://下一页
			[self showNextPage];
			
			break;	
		case 5://加入自选
			[self addZixuan];
			
			break;
		case 6://加入自选
			[self delZixuan];
			
			break;	
		default:
			break;
	}
}



-(void) OnScreenSizeChange:(float)_width theHeight:(float)_height{
}

-(void) dealKeyBoardEvent:(NSEvent *)theEvent{
	switch ([theEvent keyCode]) {
		case MAC_KEY_ARROWDOWN:{
			if ([gridArray count] == 0) {
				return;
			}
			
			if (([theEvent modifierFlags]& NSCommandKeyMask)) {
				[self showNextPage];
				return;
			}
			
			selectIndex = selectIndex+1;
			if (gridInfo.grid_domain != DOMAIN_SELF) {
				if (selectIndex > [gridArray count]-1) {
					selectIndex = 0;
				}
			}
			else {
				if (selectIndex > gridInfo.wantnum-1) {
					selectIndex = 0;
				}
				
				if (selectIndex  > [gridArray count]-1) {
					selectIndex = 0;
				}
			}

			
			SinHqInfo * tempInfo;
			
			if (gridInfo.grid_domain != DOMAIN_SELF) {
				tempInfo = [gridArray objectAtIndex:selectIndex];
			}
			else {
				if (selectIndex > [gridArray count]-1) {
					return;
				}
				tempInfo = [gridArray objectAtIndex:selectIndex];
			}
			self.gpcode = tempInfo.gpcode;
			self.setcode= tempInfo.setcode;
			
			[self setNeedsDisplay:YES];
		}
			break;
		case MAC_KEY_ARROWUP:{
			if ([gridArray count] == 0) {
				return;
			}
			if (([theEvent modifierFlags]& NSCommandKeyMask)) {
				[self showPrePage];
				return;
			}
			
			selectIndex = selectIndex-1;
			if (gridInfo.grid_domain != DOMAIN_SELF) {
				if (selectIndex < 0) {
					selectIndex = [gridArray count]-1;
				}
			}
			else {
				if (selectIndex < 0) {
					selectIndex = selectIndex+gridInfo.wantnum;
					
					if (selectIndex > [gridArray count]-1) {
						selectIndex = [gridArray count]-1 ;
					}
				}
			}

			
			SinHqInfo * tempInfo;
			
			if (gridInfo.grid_domain != DOMAIN_SELF) {
				tempInfo = [gridArray objectAtIndex:selectIndex];
			}
			else {
				if (selectIndex > [gridArray count]-1) {
					return;
				}
				tempInfo = [gridArray objectAtIndex:selectIndex];
			}
            self.gpcode = tempInfo.gpcode;
			self.setcode= tempInfo.setcode;
			
			
			[self setNeedsDisplay:YES];
		}
			break;	
		case MAC_KEY_ENTER://回车
        case MAC_SKEY_ENTER:
		case MAC_KEY_F5:
		{
			if (([gridArray count] < 1) || ([gridArray count] < selectIndex) || selectIndex <0){
				return;
			}
			SinHqInfo * tempInfo;
			
			if (gridInfo.grid_domain != DOMAIN_SELF) {
				tempInfo = [gridArray objectAtIndex:selectIndex];
			}
			else {
				if (selectIndex > [gridArray count]-1) {
					return;
				}
				tempInfo = [gridArray objectAtIndex:selectIndex];
			}
			[operProcessDelegate getHQProcess:tempInfo.gpcode gpSetcode:tempInfo.setcode typeID:MAC_ZST_FUNC pareOne:-1 paraTwo:-1];
			
		}
			break;
		case MAC_KEY_CHAR_Z:{
			[self addZixuan];
		}	
			break;
		case MAC_KEY_DEL:
		case MAC_KEY_DELETE_WIN:
			if (gridInfo.grid_domain == DOMAIN_SELF) {
				[self delZixuan];
			}
			
			break;
		case MAC_KEY_PAGEDOWN://下一页
			[self showNextPage];
			break;
		case MAC_KEY_PAGEUP://上一页
			[self showPrePage];
			break;
		case MAC_KEY_CHAR_RIGHT:
			[self showNextPage];
			break;
		case MAC_KEY_CHAR_LEFT:
			[self showPrePage];
			break;
		default:
			break;
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
	[tableView addTableColumn:column];
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
	[fixTableView addTableColumn:column];
	[column release];
	
	
}



- (void)drawRect:(NSRect)dirtyRect {
    [[NSColor blackColor] set];
	NSRectFill(dirtyRect);

	
	
	CGContextRef context = [[NSGraphicsContext currentContext] graphicsPort];
	CGContextSetAllowsAntialiasing(context, FALSE);
	[[NSColor redColor] set];
	CGContextSetLineWidth(context, 1.1f);
	CGContextAddRect(context, CGRectMake(viewRect.origin.x, 0,viewRect.size.width,viewRect.size.height));
	CGContextStrokePath(context);
	CGContextSetAllowsAntialiasing(context, TRUE);
	
	if (selectIndex > -1) {
		[[NSColor blueColor] set];	
		NSRectFill(NSMakeRect(2, viewRect.size.height-TITLE_HEIGHT - (selectIndex + 1)*(HEIGHTOFROW+2), viewRect.size.width-4, (HEIGHTOFROW+2)));
	}
}

- (void)refreshTheData{
	if (self.gridInfo.grid_domain == DOMAIN_SELF) {
        
        int nzxgnum=[operZXGDelegate GetZxgNum2];
        if(nzxgnum)
        {
            NSString * tempString = [operZXGDelegate getCurrStock2:gridInfo.startxh num:gridInfo.wantnum];
            NSMutableData * theData = [eGetData getCombHQReq:tempString wantNum:[tempString length]/7];
            [eGetData.g_pEComm AsyncSendData:theData length:[theData length] withobjIndex:self.windindex withreqIndex:1];
        }
	}
	else {
		NSMutableData * theData = [eGetData getMultiCurrStockDataReqEx:gridInfo.grid_domain coltType:gridInfo.coltype startXH:gridInfo.startxh wantNum:gridInfo.wantnum sortType:gridInfo.sorttype];
		[eGetData.g_pEComm AsyncSendData:theData length:[theData length] withobjIndex:self.windindex withreqIndex:1];
	}
	
}

- (void)getTheData:(int)_domain theColtype:(int)_coltype{
	[gridArray removeAllObjects];
	[tableView reloadData];
	[fixTableView reloadData];
	
	if (_domain > -1) {
		gridInfo.grid_domain = _domain;
		gridInfo.startxh = 0;
		totalNum = 0;
		selectIndex= 0;
	}
	if (_coltype > -1) {
		gridInfo.coltype = _coltype;
		if (gridInfo.coltype > 0) {
			gridInfo.sorttype = 1;
		}
		else {
			gridInfo.sorttype = 0;
		}

		
		gridInfo.startxh = 0;
		totalNum = 0;
		selectIndex = 0;
	}
	
	[operProcessDelegate getTheGridType];
	
	switch (gridInfo.grid_domain) {
		case DOMAIN_SHAG:
			[operProcessDelegate getTheTitleName:@"上证A股"];
			[sortButton selectItemAtIndex:0];
			break;
		case DOMAIN_SHBG:
			[operProcessDelegate getTheTitleName:@"上证B股"];
			[sortButton selectItemAtIndex:1];
			break;
		case DOMAIN_SZAG:
			[operProcessDelegate getTheTitleName:@"深证A股"];
			[sortButton selectItemAtIndex:2];
			break;
		case DOMAIN_SZBG:
			[operProcessDelegate getTheTitleName:@"深证B股"];
			[sortButton selectItemAtIndex:3];
			break;	
		case DOMAIN_SHZQ:
			[operProcessDelegate getTheTitleName:@"上证债券"];
			[sortButton selectItemAtIndex:4];
			break;
		case DOMAIN_SZZQ:
			[operProcessDelegate getTheTitleName:@"深证债券"];
			[sortButton selectItemAtIndex:5];
			break;
		case DOMAIN_ALLAG:
			[operProcessDelegate getTheTitleName:@"沪深A股"];
			[sortButton selectItemAtIndex:6];
			break;
		case DOMAIN_ALLBG:
			[operProcessDelegate getTheTitleName:@"沪深B股"];
			[sortButton selectItemAtIndex:7];
			break;		
		case DOMAIN_ALLZQ:
			[operProcessDelegate getTheTitleName:@"沪深债券"];
			[sortButton selectItemAtIndex:8];
			break;
		case DOMAIN_ALLJJ:
			[operProcessDelegate getTheTitleName:@"沪深基金"];
			[sortButton selectItemAtIndex:9];
			break;	
		case DOMAIN_ALLGP:
			[operProcessDelegate getTheTitleName:@"所有股票"];
			[sortButton selectItemAtIndex:10];
			break;
		case DOMAIN_ALLZS:
			[operProcessDelegate getTheTitleName:@"所有指数"];
			[sortButton selectItemAtIndex:11];
			break;	
		case DOMAIN_CYZQ:
			[operProcessDelegate getTheTitleName:@"中小企业"];
			[sortButton selectItemAtIndex:12];
			break;
		case DOMAIN_SHQZ:
			[operProcessDelegate getTheTitleName:@"沪深权证"];
			[sortButton selectItemAtIndex:13];
			break;
		case DOMAIN_CYB:
			[operProcessDelegate getTheTitleName:@"创业板"];
			[sortButton selectItemAtIndex:14];
			break;
		case DOMAIN_SELF:
			[operProcessDelegate getTheTitleName:@"自选股"];
			[sortButton selectItemAtIndex:15];
			break;	
		default:
			break;
	}
	//更新右键菜单
	[self dealRightMenu];
	if (self.gridInfo.grid_domain == DOMAIN_SELF) {
        int nzxgnum=[operZXGDelegate GetZxgNum2];
        if(nzxgnum)
        {
            NSString * tempString =[operZXGDelegate getCurrStock2:gridInfo.startxh num:gridInfo.wantnum];
            NSMutableData * theData = [eGetData getCombHQReq:tempString wantNum:[tempString length]/7];
            [eGetData.g_pEComm AsyncSendData:theData length:[theData length] withobjIndex:self.windindex withreqIndex:1];
        }
        
		

	}
	else {
		NSMutableData * theData = [eGetData getMultiCurrStockDataReqEx:gridInfo.grid_domain coltType:gridInfo.coltype startXH:gridInfo.startxh wantNum:gridInfo.wantnum sortType:gridInfo.sorttype];
		[eGetData.g_pEComm AsyncSendData:theData length:[theData length] withobjIndex:self.windindex withreqIndex:1];
	}

}

-(void)OnReceiveData:(int)reqIndex FuncID:(int)_funcID HqResult:(HqResultData *)_hqResult{
	if (_hqResult.resultStat < 1) {
		return;
	}
	[self clearAllButton];
	switch (gridInfo.grid_domain) {
		case DOMAIN_ALLAG:
			[AGButton setState:NSOnState];
			break;
		case DOMAIN_ALLBG:
			[BGButton setState:NSOnState];
			break;
		case DOMAIN_CYZQ:
			[ZXButton setState:NSOnState];
			break;
		case DOMAIN_CYB:
			[CYButton setState:NSOnState];
			break;
		case DOMAIN_SELF:
			[ZXGButton setState:NSOnState];
			break;	
		default:
			break;
	}
	switch (reqIndex) {
		case COMBHQ2_5MMP_NREQ:{
			[gridArray release],gridArray=nil;
			gridArray = [[NSMutableArray alloc] init];
			[eGetData getCombHQAns:gridArray hqResult:_hqResult];
	
            
			if ([gridArray count] < 1) {
				selectIndex = -1;
			}
			else {
				if (selectIndex > [gridArray count]-1) {
					selectIndex = 0;
				}
			}
			
			
			if (selectIndex > -1) {
				SinHqInfo * tempInfo;
				
				if (gridInfo.grid_domain != DOMAIN_SELF) {
					tempInfo = [gridArray objectAtIndex:selectIndex];
				}
				else {
					if (selectIndex > [gridArray count]-1) {
						selectIndex = 0;
					}
					tempInfo = [gridArray objectAtIndex:selectIndex];
				}
				self.gpcode = tempInfo.gpcode;
				self.setcode= tempInfo.setcode;
			}
			
			[tableView reloadData];
			[fixTableView reloadData];
			[[self window] makeFirstResponder:self];
		}
			break;
	
		case COMBHQ_MASK_NREQ:{
			[gridArray release],gridArray=nil;
			gridArray = [[NSMutableArray alloc] init];
			[eGetData getCombHQMaskAns:gridArray hqResult:_hqResult];
			
			if ([gridArray count] < 1) {
				selectIndex = -1;
			}
			else {
				if (selectIndex > [gridArray count]-1) {
					selectIndex = 0;
				}
			}

			
			if (selectIndex > -1) {
				SinHqInfo * tempInfo;
				
				if (gridInfo.grid_domain != DOMAIN_SELF) {
					tempInfo = [gridArray objectAtIndex:selectIndex];
				}
				else {
					if (selectIndex > [gridArray count]-1) {
						selectIndex = 0;
					}
					tempInfo = [gridArray objectAtIndex:selectIndex];
				}
				self.gpcode = tempInfo.gpcode;
				self.setcode= tempInfo.setcode;
			}
			
			[tableView reloadData];
			[fixTableView reloadData];
			[[self window] makeFirstResponder:self];
		}	
			break;
		case MULTIHQ2_5MMP_NREQ:{
			[gridArray release],gridArray=nil;
			gridArray = [[NSMutableArray alloc] init];
			[eGetData getMultiCurrStockDataAsn:gridArray TotalNum:&totalNum hqResult:_hqResult];
			if ([gridArray count] < 1) {
				selectIndex = -1;
			}
			else {
				if (selectIndex > [gridArray count]-1) {
					selectIndex = 0;
				}
			}
			if (selectIndex > -1) {
				SinHqInfo * tempInfo;
				
				if (gridInfo.grid_domain != DOMAIN_SELF) {
					tempInfo = [gridArray objectAtIndex:selectIndex];
				}
				else {
					if (selectIndex > [gridArray count]-1) {
						selectIndex = 0;
					}
					tempInfo = [gridArray objectAtIndex:selectIndex];
				}
				self.gpcode = tempInfo.gpcode;
				self.setcode= tempInfo.setcode;
			}	
			[tableView reloadData];
			[fixTableView reloadData];
		}
			break;
		default:
			break;
	}
}


-(void)dealTheColSort: (NSTableColumn *)theColumn{
	if (lastColumn != nil) {
		[tableView setIndicatorImage:nil inTableColumn:lastColumn];
	}
	
	NSImage * indicatorImage;
	if (gridInfo.sorttype == 1) {
		indicatorImage = [NSImage imageNamed:@"sortUp.png"];
	}
	else if(gridInfo.sorttype == 2) {
		indicatorImage = [NSImage imageNamed:@"sortDown.png"];
	}
	else {
		indicatorImage = nil;
	}

	lastColumn= theColumn;
	[tableView setIndicatorImage:indicatorImage inTableColumn:theColumn];

}


-(BOOL)isInGridArray:(NSString *)_gpcode gpSetcode:(int)_setcode{
	int tempLength = [gridArray count];
	if (tempLength == 0) {
		return NO;
	}
	
	for (int i =0; i<tempLength && i<[gridArray count]; i++) {
		SinHqInfo * tempInfo = [gridArray objectAtIndex:i];
		if ([tempInfo.gpcode isEqualToString:_gpcode] && tempInfo.setcode == _setcode) {
			return YES;
		}
	}
	
	return NO;
}

-(SinHqInfo *)nextInGridArray:(NSString *)_gpcode gpSetcode:(int)_setcode{
	int tempLength = [gridArray count];
	if (tempLength == 0) {
		return nil;
	}
	
	int j;
	for (int i =0; i<tempLength && i<[gridArray count]; i++) {
		SinHqInfo * tempInfo = [gridArray objectAtIndex:i];
		if ([tempInfo.gpcode isEqualToString:_gpcode] && tempInfo.setcode == _setcode) {
			j = i+1;
			
			if (j == tempLength) {
				j=0;
			}
			
			return [gridArray objectAtIndex:j];
		}
	}
	
	return nil;
}
-(SinHqInfo *)preInGridArray:(NSString *)_gpcode gpSetcode:(int)_setcode{
	int tempLength = [gridArray count];
	if (tempLength == 0) {
		return nil;
	}
	
	int j;
	for (int i =0; i<tempLength && i<[gridArray count]; i++) {
		SinHqInfo * tempInfo = [gridArray objectAtIndex:i];
		if ([tempInfo.gpcode isEqualToString:_gpcode] && tempInfo.setcode == _setcode) {
			j = i-1;
			
			if (j <0) {
				j=tempLength-1;
			}
			
			return [gridArray objectAtIndex:j];
		}
	}
	
	return nil;
}

#pragma mark 翻页相关
-(void)showNextPage{
	if (gridInfo.grid_domain != DOMAIN_SELF) {
		if((gridInfo.startxh + gridInfo.wantnum)>totalNum){
			gridInfo.startxh = 0;
			[self getTheData:-1 theColtype:-1];
		}
		else {
			gridInfo.startxh = gridInfo.startxh + gridInfo.wantnum;
			[self getTheData:-1 theColtype:-1];
		}	
	}
	else { //自选股翻页
		gridInfo.startxh = gridInfo.startxh + gridInfo.wantnum;
        int nzxgnum=[operZXGDelegate GetZxgNum];
		if (gridInfo.startxh >nzxgnum -1) {
			gridInfo.startxh = 0;
		}
		
		if (selectIndex + gridInfo.startxh >  nzxgnum-1) {
			selectIndex = 0;
		}
		[operZXGDelegate refreshZxgData];


	}

	
}
-(void)showPrePage{
	if (gridInfo.grid_domain != DOMAIN_SELF) {
		if((gridInfo.startxh - gridInfo.wantnum)>=0){
			gridInfo.startxh = gridInfo.startxh - gridInfo.wantnum;
			[self getTheData:-1 theColtype:-1];
		}
		else {
			if (gridInfo.startxh == 0) {
				if (totalNum > gridInfo.wantnum) {
					gridInfo.startxh = totalNum - totalNum % gridInfo.wantnum;
					
					if (gridInfo.startxh == totalNum) {
						gridInfo.startxh = totalNum - gridInfo.wantnum;
					}
					[self getTheData:-1 theColtype:-1];
				}
			}
			else {
				gridInfo.startxh = 0;
				[self getTheData:-1 theColtype:-1];
			}

		}

	}
	else {
		if(gridInfo.startxh - gridInfo.wantnum < 0) {
			if (gridInfo.startxh == 0)
				return;
			else {
				gridInfo.startxh = 0;
			}
		}	
		else {
			gridInfo.startxh = gridInfo.startxh - gridInfo.wantnum;
		}
	    [operZXGDelegate refreshZxgData];
	}

	
}
#pragma mark 自选股相关
-(void)addZixuan{
	if (([gridArray count] < 1) || ([gridArray count] < selectIndex ) || selectIndex <0){
		return;
	}
	SinHqInfo * tempInfo;
	
	if (gridInfo.grid_domain != DOMAIN_SELF) {
		tempInfo = [gridArray objectAtIndex:selectIndex];
	}
	else {
		tempInfo = [gridArray objectAtIndex:selectIndex];
	}
	
	if([operZXGDelegate addStock:tempInfo.gpcode setcode:tempInfo.setcode]){
		
		NSAlert* alert = [NSAlert alertWithMessageText: [NSString stringWithFormat:@"%@(%@)已成功加入自选股",tempInfo.gpname,tempInfo.gpcode]
										 defaultButton: @"确定"
									   alternateButton: nil
										   otherButton: nil
							 informativeTextWithFormat: @""];
		[alert runModal];
		[self.tableView reloadData];
		[fixTableView reloadData];
	}	
	else {
		NSAlert* alert = [NSAlert alertWithMessageText: [NSString stringWithFormat:@"%@(%@)已存在自选股中",tempInfo.gpname,tempInfo.gpcode]
										 defaultButton: @"确定"
									   alternateButton: nil
										   otherButton: nil
							 informativeTextWithFormat: @""];
		[alert runModal];
	}

}
-(void)delZixuan{
	if (([gridArray count] < 1) || ([gridArray count] < selectIndex ) || selectIndex <0){
		return;
	}
	SinHqInfo * tempInfo;
	
	if (gridInfo.grid_domain != DOMAIN_SELF) {
		tempInfo = [gridArray objectAtIndex:selectIndex];
	}
	else {
		tempInfo = [gridArray objectAtIndex:selectIndex];
	}
    NSString *tmpstr=@"";
    if([tempInfo.gpcode isEqualToString:@"(null)"] || [tempInfo.gpcode length]<=0 || [tempInfo.gpcode intValue]<=0)
    {
        tmpstr=[NSString stringWithFormat:@"是否删除自选股%@",[[operZXGDelegate getStockCode:gridInfo.startxh num:gridInfo.wantnum index:selectIndex] substringFromIndex:1]];
    }
    else
    {
        tmpstr=[NSString stringWithFormat:@"是否删除自选股%@(%@)",tempInfo.gpname,tempInfo.gpcode];
    }
	NSAlert* alert = [NSAlert alertWithMessageText:tmpstr
									 defaultButton: @"确定"
								   alternateButton: @"取消"
									   otherButton: nil
						 informativeTextWithFormat: @""];
	[alert setDelegate:self];
	NSInteger result = [alert runModal];
	[self handleResult:alert withResult:result];

}


#pragma mark NSTableViewDelegate
-(BOOL) selectionShouldChangeInTableView:(NSTableView *)tableView{
	return NO;
}

-(BOOL) tableView:(NSTableView *)tableView shouldReorderColumn:(NSInteger)columnIndex toColumn:(NSInteger)newColumnIndex{
	if (!moveFlag) {
		oriColumnIndex = columnIndex + 3;
		moveFlag = YES;
	}
	
	desColumnIndex  = newColumnIndex +3;
	return YES;
}

-(void) tableViewColumnDidMove:(NSNotification *)notification{
	
	moveFlag = NO;
	if(oriColumnIndex < [eGetData.clientinfos.gridCellCache.gridCellInfoArray count] && desColumnIndex < [eGetData.clientinfos.gridCellCache.gridCellInfoArray count] && oriColumnIndex >=0 && desColumnIndex >= 0 && desColumnIndex != oriColumnIndex)
	{
		GridCellInfo* tempInfo = [[eGetData.clientinfos.gridCellCache.gridCellInfoArray objectAtIndex:oriColumnIndex] retain];
		[eGetData.clientinfos.gridCellCache.gridCellInfoArray removeObjectAtIndex:oriColumnIndex];
		[eGetData.clientinfos.gridCellCache.gridCellInfoArray insertObject:tempInfo atIndex:desColumnIndex];
		[tempInfo release];
		[eGetData.clientinfos.caches SaveGridCellInfo:eGetData.clientinfos.gridCellCache];
		
	}
	else ;
	
}

#pragma mark NSTableViewDataSource Delegate
- (NSInteger)numberOfRowsInTableView:(NSTableView *)aTableView
{
	return MIN_VALUE([gridArray count],gridInfo.wantnum);
}

-(CGFloat) tableView:(NSTableView *)tableView heightOfRow:(NSInteger)row{
	return HEIGHTOFROW;
}

-(void) tableView:(NSTableView *)tableView didClickTableColumn:(NSTableColumn *)tableColumn{
	[[self window] makeFirstResponder:self];
	
	if (gridInfo.grid_domain == DOMAIN_SELF) {
		return;
	}
	
	switch ([[tableColumn identifier] intValue]) {
		case 1:  //代码
			if (gridInfo.coltype != ZQDM) {
				gridInfo.sorttype = 0;
				gridInfo.startxh = 0;
			}
			
			gridInfo.coltype = ZQDM;
			//return;
			break;
		case 2:  //名称
			if (gridInfo.coltype != ZQJC) {
				gridInfo.sorttype = 0;
				gridInfo.startxh = 0;
			}
			
			gridInfo.coltype = ZQJC;
			//return;
			break;
		case 3:  //涨幅
			if (gridInfo.coltype != ZAF) {
				gridInfo.sorttype = 0;
				gridInfo.startxh = 0;
			}
			
			gridInfo.coltype = ZAF;
			
			
			break;
		case 4:  //现价
			if (gridInfo.coltype != ZJCJ){
				gridInfo.sorttype = 0;
				gridInfo.startxh = 0;
			}
			
			gridInfo.coltype = ZJCJ;
			
			break;
		case 5:  //涨跌
			if (gridInfo.coltype != QRSD) {
				gridInfo.sorttype = 0;
				gridInfo.startxh = 0;
			}
			gridInfo.coltype = QRSD;
			break;
		case 6:  //买入价
			if (gridInfo.coltype != ZGJM){
				gridInfo.sorttype = 0;
				gridInfo.startxh = 0;
			}
			
			gridInfo.coltype = ZGJM;
			
			break;
		case 7:  //卖出价
			if (gridInfo.coltype != ZDJM) {
				gridInfo.sorttype = 0;
				gridInfo.startxh = 0;
			}
			gridInfo.coltype = ZDJM;
			break;	
		case 8:  //昨收
			if (gridInfo.coltype != ZRSP) {
				gridInfo.sorttype = 0;
				gridInfo.startxh = 0;
			}
			gridInfo.coltype = ZRSP;
			break;
		case 9:  //总量
			if (gridInfo.coltype != CJL) {
				gridInfo.sorttype = 0;
				gridInfo.startxh = 0;
			}
			gridInfo.coltype = CJL;
			break;
		case 10:  //量比
			if (gridInfo.coltype != LIANGB) {
				gridInfo.sorttype = 0;
				gridInfo.startxh = 0;
			}
			gridInfo.coltype = LIANGB;
			break;
		case 11:  //换手
			if (gridInfo.coltype != HSL) {
				gridInfo.sorttype = 0;
				gridInfo.startxh = 0;
			}
			gridInfo.coltype = HSL;
			
			break;
		case 12:  //今开
			if (gridInfo.coltype != JRKP) {
				gridInfo.sorttype = 0;
				gridInfo.startxh = 0;
			}
			gridInfo.coltype = JRKP;
			break;
		case 13:  //最高
			if (gridInfo.coltype != ZGCJ) {
				gridInfo.sorttype = 0;
				gridInfo.startxh = 0;
			}
			gridInfo.coltype = ZGCJ;
			
			break;
		case 14:  //最低
			if (gridInfo.coltype != ZDCJ) {
				gridInfo.sorttype = 0;
				gridInfo.startxh = 0;
			}
			gridInfo.coltype = ZDCJ;			
			break;
		case 15:  //总金额
			if (gridInfo.coltype != CJJE) {
				gridInfo.sorttype = 0;
				gridInfo.startxh = 0;
			}
			gridInfo.coltype = CJJE;
			break;
		case 16:  //振幅
			if (gridInfo.coltype != ZEF) {
				gridInfo.sorttype = 0;
				gridInfo.startxh = 0;
			}
			gridInfo.coltype = ZEF;
			break;
		case 17:  //总股本
			if (gridInfo.coltype != LTGB) {
				gridInfo.sorttype = 0;
				gridInfo.startxh = 0;
			}
			gridInfo.coltype = LTGB;
			
			break;
		case 18:  //流通股本
			if (gridInfo.coltype != LTGB) {
				gridInfo.sorttype = 0;
				gridInfo.startxh = 0;
			}
			gridInfo.coltype = LTGB;
			
			break;	
		case 19:  //总市值
			if (gridInfo.coltype != ZSZ) {
				gridInfo.sorttype = 0;
				gridInfo.startxh = 0;
			}
			gridInfo.coltype = ZSZ;
			break;
		case 20:  //市盈率
			if (gridInfo.coltype != SYL) {
				gridInfo.sorttype = 0;
				gridInfo.startxh = 0;
			}
			gridInfo.coltype = SYL;
			break;
		case 21:  //内盘
			if (gridInfo.coltype != NP) {
				gridInfo.sorttype = 0;
				gridInfo.startxh = 0;
			}
			gridInfo.coltype = NP;
			break;
		case 22:  //外盘
			if (gridInfo.coltype != WP) {
				gridInfo.sorttype = 0;
				gridInfo.startxh = 0;
			}
			gridInfo.coltype = WP;
			break;
		default:
			break;
	}
	
	if(gridInfo.sorttype == 2)
		gridInfo.sorttype = 1;
	else if(gridInfo.sorttype == 1)
		gridInfo.sorttype = 2;
	else 
		gridInfo.sorttype = 1;

	[self dealTheColSort:tableColumn];
	[self getTheData:-1 theColtype:-1];
}


-(void)singleClick:(id)sender{
	if ([sender tag] == ORDTABLE_TAG) {
		if ([tableView clickedRow]  < 0) {
			return;
		}
		if (gridInfo.grid_domain == DOMAIN_SELF) {
			if ([tableView clickedRow] > [gridArray count]-1) {
				return;
			}
		}
		selectIndex = [tableView clickedRow];
		[self setNeedsDisplay:YES];
		[[self window] makeFirstResponder:self];		
	}
	else if([sender tag] == FIXTABLE_TAG){
		if ([fixTableView clickedRow]  < 0) {
			return;
		}
		if (gridInfo.grid_domain == DOMAIN_SELF) {
			if ([fixTableView clickedRow] > [gridArray count]-1) {
				return;
			}
		}
		selectIndex = [fixTableView clickedRow];
		[self setNeedsDisplay:YES];
		[[self window] makeFirstResponder:self];		
	
	}
	
	SinHqInfo * tempInfo ;
	if (gridInfo.grid_domain != DOMAIN_SELF) {
		if ([sender tag] == ORDTABLE_TAG) {
			if (([gridArray count] < 1) || ([gridArray count] < [tableView clickedRow])){
				return;
			}
			tempInfo = [gridArray objectAtIndex:[tableView clickedRow]];
		}
		else if([sender tag] == FIXTABLE_TAG){
			if (([gridArray count] < 1) || ([gridArray count] < [fixTableView clickedRow])){
				return;
			}
			tempInfo = [gridArray objectAtIndex:[fixTableView clickedRow]];
		}
		
	}
	else {
		if ([tableView clickedRow] > [gridArray count]-1) {
			return;
		}
		
		if ([sender tag] == ORDTABLE_TAG) {
			if ([tableView clickedRow] > [gridArray count]-1) {
				return;
			}
			
			if (([gridArray count] < 1) || ([gridArray count] < [tableView clickedRow])){
				return;
			}
			tempInfo = [gridArray objectAtIndex:[tableView clickedRow]];
		}
		else if([sender tag] == FIXTABLE_TAG){
			if (([gridArray count] < 1) || ([gridArray count] < [fixTableView clickedRow])){
				return;
			}
			tempInfo = [gridArray objectAtIndex:[fixTableView clickedRow]];
		}
	}

	
	
	self.gpcode = tempInfo.gpcode;
	self.setcode = tempInfo.setcode;
	
}

-(void)doubleClick:(id)sender{
	SinHqInfo * tempInfo ;
	if (gridInfo.grid_domain != DOMAIN_SELF) {
		if ([sender tag] == ORDTABLE_TAG) {
			if (([gridArray count] < 1) || ([gridArray count] < [tableView clickedRow])){
				return;
			}
			tempInfo = [gridArray objectAtIndex:[tableView clickedRow]];
		}
		else if([sender tag] == FIXTABLE_TAG){
			if (([gridArray count] < 1) || ([gridArray count] < [fixTableView clickedRow])){
				return;
			}
			tempInfo = [gridArray objectAtIndex:[fixTableView clickedRow]];
		}
	}
	else {
		if ([tableView clickedRow] > [gridArray count]-1) {
			return;
		}
		
		if ([sender tag] == ORDTABLE_TAG) {
			if (([gridArray count] < 1) || ([gridArray count] < [tableView clickedRow])){
				return;
			}
			tempInfo = [gridArray objectAtIndex:[tableView clickedRow]];
		}
		else if([sender tag] == FIXTABLE_TAG){
			if (([gridArray count] < 1) || ([gridArray count] < [fixTableView clickedRow])){
				return;
			}
			tempInfo = [gridArray objectAtIndex:[fixTableView clickedRow]];
		}
	}

	

	
	
	[operProcessDelegate getHQProcess:tempInfo.gpcode gpSetcode:tempInfo.setcode typeID:MAC_ZST_FUNC pareOne:-1 paraTwo:-1];
}

- (id)tableView: (NSTableView *)theTableView objectValueForTableColumn: (NSTableColumn *)theColumn row: (NSInteger)rowIndex
{
	SinHqInfo * rowData ;
    if (rowIndex >= [gridArray count]) {
        return nil;
    }
    rowData = [gridArray objectAtIndex:rowIndex];
	
	NSString * tempString = @"";
    
    if([rowData.gpcode isEqualToString:@"(null)"] || [rowData.gpcode length]<=0 || [rowData.gpcode intValue]<=0)
    {
        if([[theColumn identifier] intValue]==0)
            tempString = [NSString stringWithFormat:@"%i",gridInfo.startxh + rowIndex +1];
        else if([[theColumn identifier] intValue]==1)
            tempString= [[operZXGDelegate getStockCode:gridInfo.startxh num:gridInfo.wantnum index:rowIndex] substringFromIndex:1];
        else
            tempString = @"－";
        return tempString;
    }
    
	float tempFloat;
	switch ([[theColumn identifier] intValue]) {
		case 0:
			tempString = [NSString stringWithFormat:@"%i",gridInfo.startxh + rowIndex +1];
			break;

		case 1:  //代码
			tempString =  rowData.gpcode;
			break;
		case 2:  //名称
			tempString = rowData.gpname;
			break;
		case 3:  //涨幅
			if ((rowData.zaf == 0) &&(rowData.nowP < 0.001) && ([rowData.buyP count]<=0 || [[rowData.buyP objectAtIndex:0]floatValue] < 0.001)) {
				tempString = @"－";
			}
			else {
				if(rowData.dataPre == 2)
					tempString = [NSString stringWithFormat:@"%.2f",rowData.zaf];
				else
					tempString = [NSString stringWithFormat:@"%.3f",rowData.zaf];
				tempString = [tempString stringByAppendingString:@"%"];
			}
			break;
		case 4:  //现价
			if (rowData.nowP > 0.001) {
				if(rowData.dataPre == 2)
					tempString = [NSString stringWithFormat:@"%.2f",rowData.nowP];
				else
					tempString = [NSString stringWithFormat:@"%.3f",rowData.nowP];
			}
			else {
				tempString = @"－";
			}
			
			break;
		case 5:  //涨跌

			if ((rowData.zad == 0) &&(rowData.nowP < 0.001) && ([rowData.buyP count]<=0 || [[rowData.buyP objectAtIndex:0]floatValue] < 0.001)) {
				tempString = @"－";
			}
			else {
				if(rowData.dataPre == 2)
					tempString = [NSString stringWithFormat:@"%.2f",rowData.zad];
				else
					tempString = [NSString stringWithFormat:@"%.3f",rowData.zad];
			}
		
			break;
		case 6:  //买入价
            if([rowData.buyP count]<=0)
                tempString = @"-";
            else
            {
                tempFloat = [[rowData.buyP objectAtIndex:0] floatValue];
                if (rowData.zsflag) {
                    tempString = @"-";
                }
                else {
                    if (tempFloat > 0.001) {
                        if(rowData.dataPre == 2)
                            tempString = [NSString stringWithFormat:@"%.2f",tempFloat];
                        else
                            tempString = [NSString stringWithFormat:@"%.3f",tempFloat];	
                    }
                    else {
                        tempString = @"－";
                    }
                }
            }
			

			break;
		case 7:  //卖出价
            if([rowData.sellP count]<=0)
                tempString = @"-";
            else
            {
                tempFloat = [[rowData.sellP objectAtIndex:0] floatValue];
                if (rowData.zsflag) {
                    tempString = @"-";
                }
                else {
                    if (tempFloat > 0.001) {
                        if(rowData.dataPre == 2)
                            tempString = [NSString stringWithFormat:@"%.2f",[[rowData.sellP objectAtIndex:0]floatValue]];
                        else
                            tempString = [NSString stringWithFormat:@"%.3f",[[rowData.sellP objectAtIndex:0]floatValue]];
                    }
                    else {
                        tempString = @"－";
                    }
                }
            }
			break;
		case 8:  //昨收
			if(rowData.dataPre == 2)
				tempString = [NSString stringWithFormat:@"%.2f",rowData.closeP];
			else
				tempString = [NSString stringWithFormat:@"%.3f",rowData.closeP];			
			break;
		case 9:  //总量
			
			if(rowData.volume > 100000){
				tempString = [NSString stringWithFormat:@"%.1f",rowData.volume/10000];
				tempString = [tempString stringByAppendingString:@"万"];
			}	
			else
				tempString = [NSString stringWithFormat:@"%.0f",rowData.volume];
			break;
		case 10:  //现量
			if (rowData.zsflag) {
				tempString = @"－";
			}
			else {
				if (rowData.liangbi < 0.01) {
					tempString = @"－";
				}
				else {
					tempString = [NSString stringWithFormat:@"%.1f",rowData.liangbi];
				}
			}
			break;
		case 11:  //换手
			if (!rowData.zsflag) {
				if (rowData.ActiveCapital > 0) {
					tempString = [NSString stringWithFormat:@"%.2f",rowData.exchange];
					tempString = [tempString stringByAppendingString:@"%"];
				}
				else {
					tempString = @"－";
				}
			}
			else {
				tempString = @"－";
			}
			
		
			break;
		case 12:  //今开
			if (rowData.nowP > 0.001) {
				if(rowData.dataPre == 2)
					tempString = [NSString stringWithFormat:@"%.2f",rowData.openP];
				else
					tempString = [NSString stringWithFormat:@"%.3f",rowData.openP];
				
			}
			else {
				tempString = @"－";
			}
		
			break;
		case 13:  //最高
			if (rowData.nowP > 0.001) {
				if(rowData.dataPre == 2)
					tempString = [NSString stringWithFormat:@"%.2f",rowData.maxP];
				else
					tempString = [NSString stringWithFormat:@"%.3f",rowData.maxP];
				
			}
			else {
				tempString = @"－";
			}
			break;
		case 14:  //最低
			if (rowData.nowP > 0.001) {
				if(rowData.dataPre == 2)
					tempString = [NSString stringWithFormat:@"%.2f",rowData.minP];
				else
					tempString = [NSString stringWithFormat:@"%.3f",rowData.minP];
				
			}
			else {
				tempString = @"－";
			}
		
			break;
		case 15:  //总金额
			if(rowData.amount > 100000000){
				tempString = [NSString stringWithFormat:@"%.2f",rowData.amount/100000000];
				tempString = [tempString stringByAppendingString:@"亿"];
			}	
			else {
				tempString = [NSString stringWithFormat:@"%.1f",rowData.amount/10000];
				tempString = [tempString stringByAppendingString:@"万"];
			}
			break;
		case 16:  //振幅
			if (rowData.nowP > 0.001) {
				tempString = [NSString stringWithFormat:@"%.2f",rowData.zef];
				tempString = [tempString stringByAppendingString:@"%"];
			}
			else {
				tempString = @"－";
			}
			break;
		case 17:  //总股本
			if (rowData.J_zgb > 1000000) {
				tempString = [NSString stringWithFormat:@"%.0f亿",rowData.J_zgb/10000];
			}
			else if ((rowData.J_zgb < 1000000)&&(rowData.J_zgb > 100000)){
				tempString = [NSString stringWithFormat:@"%.1f亿",rowData.J_zgb/10000];
			}
			else if ((rowData.J_zgb < 100000)&&(rowData.J_zgb > 10000)){
				tempString = [NSString stringWithFormat:@"%.2f亿",rowData.J_zgb/10000];
			}
			else if ((rowData.J_zgb < 10000)&&(rowData.J_zgb > 0.001)){
				tempString = [NSString stringWithFormat:@"%.0f万",rowData.J_zgb];
			}
			else {
				tempString = @"-";
			}
			
			break;
		case 18:  //流通股本
			if (rowData.ActiveCapital > 1000000) {
				tempString = [NSString stringWithFormat:@"%.0f亿",rowData.ActiveCapital/10000];
			}
			else if ((rowData.ActiveCapital < 1000000)&&(rowData.ActiveCapital > 100000)){
				tempString = [NSString stringWithFormat:@"%.1f亿",rowData.ActiveCapital/10000];
			}
			else if ((rowData.ActiveCapital < 100000)&&(rowData.ActiveCapital > 10000)){
				tempString = [NSString stringWithFormat:@"%.2f亿",rowData.ActiveCapital/10000];
			}
			else if ((rowData.J_zgb < 10000)&&(rowData.J_zgb > 0.001)){
				tempString = [NSString stringWithFormat:@"%.0f万",rowData.ActiveCapital];
			}
			else {
				tempString = @"-";
			}
			
			break;	
		case 19:  //总市值
			if (rowData.J_zsz > 1000000) {
				tempString = [NSString stringWithFormat:@"%.0f亿",rowData.J_zsz/10000];
			}
			else if ((rowData.J_zsz < 1000000)&&(rowData.J_zsz > 100000)){
				tempString = [NSString stringWithFormat:@"%.1f亿",rowData.J_zsz/10000];
			}
			else if ((rowData.J_zsz < 100000)&&(rowData.J_zsz > 10000)){
				tempString = [NSString stringWithFormat:@"%.2f亿",rowData.J_zsz/10000];
			}
			else if ((rowData.J_zsz < 10000)&&(rowData.J_zsz > 0.001)){
				tempString = [NSString stringWithFormat:@"%.0f万",rowData.J_zsz];
			}
			else {
				tempString = @"-";
			}
			break;
		case 20:  //市盈率
			if (rowData.zsflag) {
				tempString = @"－";
			}
			else {
				if (rowData.J_syl <= 0) {
					tempString = @"-";
				}
				else {
					tempString = [NSString stringWithFormat:@"%.1f",rowData.J_syl];
				}

			}
			break;
		case 21:  //内盘
			if(rowData.inside > 100000){
				tempString = [NSString stringWithFormat:@"%.1f",rowData.inside/10000];
				tempString = [tempString stringByAppendingString:@"万"];
			}	
			else
				tempString = [NSString stringWithFormat:@"%.0f",rowData.inside];
			
			break;
		case 22:  //外盘
			if(rowData.outside > 100000){
				tempString = [NSString stringWithFormat:@"%.1f",rowData.outside/10000];
				tempString = [tempString stringByAppendingString:@"万"];
			}	
			else
				tempString = [NSString stringWithFormat:@"%.0f",rowData.outside];
			
			break;
		default:
			break;
	}
	
	return tempString;
}

-(void)tableView:(NSTableView *)tableView willDisplayCell:(id)cell forTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row{
	[cell setBackgroundColor:[NSColor clearColor]];
	[cell setAlignment:NSCenterTextAlignment];
	[cell setFont:[NSFont systemFontOfSize:15]];
	
    SinHqInfo * rowData ;
	float tempFloat;
    if (row >= [gridArray count]) {
        return;
    }
    rowData = [gridArray objectAtIndex:row];
	
	switch ([[tableColumn identifier] intValue]) {
		case 0:
			[cell setTextColor:COLOR_GRID_COMMONCOLOR];
			break;

		case 1:  //代码
			[cell setTextColor:COLOR_GRID_COMMONCOLOR];
			break;
		case 2:  //名称
			if ([operZXGDelegate stockIsIn:rowData.gpcode setcode:rowData.setcode]) {
				[cell setTextColor:HQCOLOR_ZIXUAN];
			}
			else {
				[cell setTextColor:COLOR_GRID_COMMONCOLOR];
			}

			
			break;
		case 3:  //涨幅
			if ((rowData.zaf == 0) &&(rowData.nowP < 0.001) && ([rowData.buyP count]<=0 || [[rowData.buyP objectAtIndex:0]floatValue] < 0.001)) {
				[cell setTextColor:[NSColor grayColor]];
			}
			else {
				if(rowData.zaf > 0.001)
					[cell setTextColor:[NSColor redColor]];
				else if(rowData.zaf < 0)
					[cell setTextColor:HQCOLOR_DOWN] ;
				else	
					[cell setTextColor:COLOR_GRID_COMMONCOLOR];
			}
			
			break;
		case 4:  //现价
			if (rowData.nowP > 0.001) {
				if(rowData.nowP > rowData.closeP)
					[cell setTextColor:[NSColor redColor]];
				else if(rowData.nowP < rowData.closeP)
					[cell setTextColor:HQCOLOR_DOWN] ;
				else	
					[cell setTextColor:COLOR_GRID_COMMONCOLOR];
			}
			else {
				[cell setTextColor:[NSColor grayColor]];
			}
			
			break;
		case 5:  //涨跌
            
			if ((rowData.zaf == 0) &&(rowData.nowP < 0.001) && ([rowData.buyP count]<=0 || [[rowData.buyP objectAtIndex:0]floatValue] < 0.001)) {
				[cell setTextColor:[NSColor grayColor]];
			}
			else {
				if(rowData.zaf > 0)
					[cell setTextColor:[NSColor redColor]];
				else if(rowData.zaf < 0)
					[cell setTextColor:HQCOLOR_DOWN] ;
				else	
					[cell setTextColor:COLOR_GRID_COMMONCOLOR];
			}

			
			break;
		case 6:  //买入价
            if([rowData.buyP count]<=0)
                [cell setTextColor:[NSColor grayColor]];
            else
            {
                tempFloat = [[rowData.buyP objectAtIndex:0] floatValue];
                if (rowData.zsflag) {
                    [cell setTextColor:[NSColor grayColor]];
                }
                else {
                    if (tempFloat > 0.001) {
                        if(tempFloat > rowData.closeP)
                            [cell setTextColor:[NSColor redColor]];
                        else if(tempFloat < rowData.closeP)
                            [cell setTextColor:HQCOLOR_DOWN] ;
                        else	
                            [cell setTextColor:COLOR_GRID_COMMONCOLOR];
                    }
                    else {
                        [cell setTextColor:[NSColor grayColor]];
                    }
                    
                }
            }
			

		
			break;
		case 7:  //卖出价
            if([rowData.sellP count]<=0)
                [cell setTextColor:[NSColor grayColor]];
            else
            {
                tempFloat = [[rowData.sellP objectAtIndex:0] floatValue];
                if (rowData.zsflag) {
                    [cell setTextColor:[NSColor grayColor]];
                }
                else {
                    if (tempFloat > 0.001) {
                        if(tempFloat > rowData.closeP)
                            [cell setTextColor:[NSColor redColor]];
                        else if(tempFloat < rowData.closeP)
                            [cell setTextColor:HQCOLOR_DOWN] ;
                        else	
                            [cell setTextColor:COLOR_GRID_COMMONCOLOR];
                    }
                    else {
                        [cell setTextColor:[NSColor grayColor]];
                    }
                }
            }
			

			
			break;	
		case 8:  //昨收
			[cell setTextColor:COLOR_GRID_COMMONCOLOR];			
			break;
		case 9:  //总量
			[cell setTextColor:HQCOLOR_VOL];		
			break;
		case 10:  //现量
			if (rowData.liangbi < 1) {
				[cell setTextColor:HQCOLOR_DOWN];	
			}
			else {
				[cell setTextColor:[NSColor redColor]];	
			}
			break;
		case 11:  //换手
			if (!rowData.zsflag) {
				if (rowData.ActiveCapital > 0) {
					[cell setTextColor:COLOR_GRID_COMMONCOLOR];
				}
				else {
					[cell setTextColor:[NSColor grayColor]];
				}
			}
			else {
				[cell setTextColor:[NSColor grayColor]];
			}
			
			
			break;
		case 12:  //今开
			if (rowData.nowP > 0.001) {
				if(rowData.openP > rowData.closeP)
					[cell setTextColor:[NSColor redColor]];
				else if(rowData.openP < rowData.closeP)
					[cell setTextColor:HQCOLOR_DOWN] ;
				else	
					[cell setTextColor:COLOR_GRID_COMMONCOLOR];
			}
			else {
				[cell setTextColor:[NSColor grayColor]];
			}
			
			break;
		case 13:  //最高
			if (rowData.nowP > 0.001) {
				if(rowData.maxP > rowData.closeP)
					[cell setTextColor:[NSColor redColor]];
				else if(rowData.maxP < rowData.closeP)
					[cell setTextColor:HQCOLOR_DOWN] ;
				else	
					[cell setTextColor:COLOR_GRID_COMMONCOLOR];
			}
			else {
				[cell setTextColor:[NSColor grayColor]];
			}
			break;
		case 14:  //最低
			if (rowData.nowP > 0.001) {
				if(rowData.minP > rowData.closeP)
					[cell setTextColor:[NSColor redColor]];
				else if(rowData.minP < rowData.closeP)
					[cell setTextColor:HQCOLOR_DOWN] ;
				else	
					[cell setTextColor:COLOR_GRID_COMMONCOLOR];			}
			else {
				[cell setTextColor:[NSColor grayColor]];
			}
			
			break;
		case 15:  //总金额
			[cell setTextColor:HQCOLOR_VOL];	
			break;
		case 16:  //振幅
			if (rowData.nowP > 0.001) {
				[cell setTextColor:COLOR_GRID_COMMONCOLOR];	
			}
			else {
				[cell setTextColor:[NSColor grayColor]];
			}
			break;
		case 17:  //总股本
			[cell setTextColor:COLOR_GRID_COMMONCOLOR];	
			break;
		case 18:  //流通股本
			[cell setTextColor:COLOR_GRID_COMMONCOLOR];	
			break;	
		case 19:  //总市值
			[cell setTextColor:COLOR_GRID_COMMONCOLOR];	
			break;
		case 20:  //市盈率
			if (rowData.zsflag) {
				[cell setTextColor:[NSColor grayColor]];
			}
			else {
				[cell setTextColor:COLOR_GRID_COMMONCOLOR];	
			}
			break;
		case 21:  //内盘
			[cell setTextColor:HQCOLOR_DOWN];	
			break;
		case 22:  //外盘
			[cell setTextColor:[NSColor redColor]];
			break;
		default:
			break;
	}
}

#pragma mark mouseDelegate;
-(void) mouseDown:(NSEvent *)theEvent{
	//NSLog(@"mouseDown");
	if (eGetData.g_pEComm.connFlag) {

	}
}

-(void) scrollWheel:(NSEvent *)theEvent{
	
    
}

-(void)OnMouseWheel:(BOOL)bupdownflag
{
    if(bupdownflag)
        [self showPrePage];
    else
        [self showNextPage];
}
#pragma mark  alertDelegate
- (void)alertDidEnd:(NSAlert *)alert returnCode:(NSInteger)returnCode contextInfo:(void *)contextInfo
{

}


-(void)handleResult:(NSAlert *)alert withResult:(NSInteger)result
{

	switch(result)
	{
			//删除自选股
		case NSAlertDefaultReturn:
			if (([gridArray count] < 1) || ([gridArray count] < selectIndex ) || selectIndex <0){
				return;
			}
			//NSLog(@"选中的股票是 %i",selectIndex );
			SinHqInfo * tempInfo ;
			if (gridInfo.grid_domain != DOMAIN_SELF) {
				tempInfo = [gridArray objectAtIndex:selectIndex];
			}
			else {
				tempInfo = [gridArray objectAtIndex:selectIndex];
			}
            BOOL bdelflag=NO;
            NSString *tmpstr1=@"",*tmpstr2=@"";
			if([tempInfo.gpcode isEqualToString:@"(null)"] || [tempInfo.gpcode length]<=0 || [tempInfo.gpcode intValue]<=0)
            {
                NSString *gpcode1=[operZXGDelegate getStockCode:gridInfo.startxh num:gridInfo.wantnum index:selectIndex];
                NSString *zqdm=[gpcode1 substringFromIndex:1];
                bdelflag=[operZXGDelegate deleteStock:zqdm  setcode:[[gpcode1 substringToIndex:1] intValue]];
                
                tmpstr1=[NSString stringWithFormat:@"自选股%@已成功删除",zqdm];
                tmpstr2=[NSString stringWithFormat:@"%@已存在自选股中",zqdm];
            }
            else
            {
                bdelflag=[operZXGDelegate deleteStock:tempInfo.gpcode setcode:tempInfo.setcode];
                tmpstr1=[NSString stringWithFormat:@"自选股%@(%@)已成功删除",tempInfo.gpname,tempInfo.gpcode];
                tmpstr2=[NSString stringWithFormat:@"%@(%@)已存在自选股中",tempInfo.gpname,tempInfo.gpcode];
            }
			
			if(bdelflag){
				
				NSAlert* alert = [NSAlert alertWithMessageText:tmpstr1
												 defaultButton: @"确定"
											   alternateButton: nil
												   otherButton: nil
									 informativeTextWithFormat: @""];
				[alert runModal];
				[self getTheData:-1 theColtype:-1];
				
			}	
			else {
				NSAlert* alert = [NSAlert alertWithMessageText:tmpstr2
												 defaultButton: @"确定"
											   alternateButton: nil
												   otherButton: nil
									 informativeTextWithFormat: @""];
				[alert runModal];
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


-(void) dealloc{
	[super dealloc];
	[gridInfo release];
	[gridArray release];
	[titleArray release];
	[widthArray release];
	[identifierArray release];
	[scrollView release];
}
@end
