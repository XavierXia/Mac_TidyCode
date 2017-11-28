//
//  ETradeWTView.m
//  tdxMac
//
//  Created by tdx on 11-10-26.
//  Copyright 2011 武汉. All rights reserved.
//
#import <QuartzCore/QuartzCore.h>
#import "ETradeWTView.h"
#define GDDM_COM_FLAG 1
#define BJFS_COM_FLAG 2
#define PRICE_TEXT_FLAG 3
#define CODE_TEXT_FLAG 4
#define NUM_TEXT_FLAG 5
#define XHKE_TEXT_FLAG 6
#define PERROWHEIGHT 26
#define PERROWHEIGHT_PK 22
#define WT_WIDTH 230
#define textFieldtag 564
#define MARIN_HEIGHT 2

#define TOPMARIN_HEIGHT 5

@implementation ETradeWTView
@synthesize tag,wtPrice,gpcodeText,gppriceText,showDelegate,m_brefreshflag,m_bOnlyRunOne,maxbuysellLabel;
@synthesize bDelegates;
@synthesize wtViewFrame;

- (id)initWithFrame:(NSRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
    }
    return self;
}

- (id)initWithData:(NSRect)frame theData:(EGetData *)_eGetData showType:(int)_showType{
	self = [super initWithData:frame theData:_eGetData];
    if (self) {
		self.tradeindex = [_eGetData.g_TradeComm.areceiver SetWinobjs:self];
		viewRect = frame;
		showType = _showType;
		self.tag = -1;
		if (showType == 0) {
			leftBlankWidth = 5;
		}
		else {
			leftBlankWidth = 2;
		}
        nlastsjwtflag=-1;
        m_bOnlyRunOne = YES;
		
		m_szsjwtfsmc=[[NSArray arrayWithObjects:@"限价委托",@"对方最优价格",@"本方最优价格",@"即时成交剩余撤销",@"五档即成剩撤",@"全额成交或撤销",nil] retain];
		m_nszsjwtfsdm=[[NSArray arrayWithObjects:@"0",@"1",@"2",@"3",@"4",@"5",nil] retain];
		
		m_shsjwtfsmc=[[NSArray arrayWithObjects:@"限价委托",@"五档即成剩撤",@"五档即成转限价",nil] retain];
		m_nshsjwtfsdm=[[NSArray arrayWithObjects:@"0",@"4",@"6",nil] retain];
		
		titleLabelArray = [[NSArray arrayWithObjects:@"股东代码:",@"证券代码:",@"报价方式:",@"买入价格:",@"可用资金:",@"最大可买:",@"买入数量:",nil] retain];
		pkTitleArray = [[NSMutableArray arrayWithObjects:@"卖五",@"卖四",@"卖三",@"卖二",@"卖一",@"买一",@"买二",@"买三",@"买四",@"买五",nil] retain];
		
		int i ;
		int _length = [titleLabelArray count];
		NSTextField * tempText;
		for (i=0; i<_length; i++) {
			tempText = [[NSTextField alloc]init];
			[tempText setEditable:NO];
			[tempText setBackgroundColor:[NSColor clearColor]];
			[tempText setBordered:NO];
			[tempText setFrame:NSMakeRect(leftBlankWidth, frame.size.height  - (i+1)*PERROWHEIGHT-TOPMARIN_HEIGHT, 70, PERROWHEIGHT)];
			[[tempText cell] setFont:[NSFont systemFontOfSize:14.0f]];
			[[tempText cell] setTextColor:[NSColor blackColor]];
			[[tempText cell] setTitle:[titleLabelArray objectAtIndex:i]];
			[tempText setTag:i+textFieldtag];
			[self addSubview:tempText];
			[tempText release];
		}
        
		gddmCombobox = [[NSComboBox alloc] initWithFrame:NSMakeRect(70, frame.size.height  - PERROWHEIGHT-TOPMARIN_HEIGHT, 140, PERROWHEIGHT)];
		[gddmCombobox setBackgroundColor:[NSColor clearColor]];
		[gddmCombobox setEditable:NO];
		[gddmCombobox setTag:GDDM_COM_FLAG];
		[gddmCombobox setUsesDataSource:YES];
		[gddmCombobox setDelegate:self];
		[gddmCombobox setDataSource:self];
        [self addSubview:gddmCombobox];
		
		gpcodeText = [[CustonTextField alloc]init];
		[gpcodeText setEditable:YES];
		[gpcodeText setBackgroundColor:[NSColor whiteColor]];
		[gpcodeText setBordered:YES];
		[gpcodeText setBezeled:YES];
		[gpcodeText setTag:CODE_TEXT_FLAG];
		[gpcodeText setBezelStyle:NSTextFieldSquareBezel];
		[gpcodeText setFrame:NSMakeRect(70, frame.size.height  - 2*PERROWHEIGHT+MARIN_HEIGHT-TOPMARIN_HEIGHT, 70, PERROWHEIGHT-2*MARIN_HEIGHT)];
		[[gpcodeText cell] setTextColor:[NSColor blackColor]];
		customTextFieldFormatter * codeFormatt = [[customTextFieldFormatter alloc] init];
		[codeFormatt setMaxLength:6];
		[gpcodeText setFormatter:codeFormatt];
		[codeFormatt release];
		[gpcodeText setDelegate:self];
		gpcodeText.focusDelegate = self;
         [self addSubview:gpcodeText];
	
		
		
		gpnameLabel = [[NSTextField alloc]init];
		[gpnameLabel setEditable:NO];
		[gpnameLabel setBackgroundColor:[NSColor clearColor]];
		[gpnameLabel setBordered:NO];
		[gpnameLabel setFrame:NSMakeRect(140, frame.size.height  - 2*PERROWHEIGHT-TOPMARIN_HEIGHT, 70, PERROWHEIGHT)];
		[[gpnameLabel cell] setFont:[NSFont systemFontOfSize:15.0f]];
		[[gpnameLabel cell] setTextColor:[NSColor blackColor]];
		[[gpnameLabel cell] setTitle:@""];
		[self addSubview:gpnameLabel];
		
		bjfsCombobox = [[NSComboBox alloc] initWithFrame:NSMakeRect(70, frame.size.height  -3*PERROWHEIGHT-TOPMARIN_HEIGHT, 140, PERROWHEIGHT)];
		[bjfsCombobox setBackgroundColor:[NSColor clearColor]];
		[bjfsCombobox setEditable:NO];
		[bjfsCombobox setTag:BJFS_COM_FLAG];
		[bjfsCombobox setUsesDataSource:YES];
		[bjfsCombobox setDelegate:self];
		[bjfsCombobox setDataSource:self];
		[[bjfsCombobox cell] setTitle:@"限价委托"];
		[self addSubview:bjfsCombobox];
		
		
		gppriceText = [[CustonTextField alloc]init];
		[gppriceText setEditable:YES];
		[gppriceText setBackgroundColor:[NSColor whiteColor]];
		[gppriceText setBordered:YES];
		[gppriceText setBezeled:YES];
		[gppriceText setTag:PRICE_TEXT_FLAG];
		[gppriceText setBezelStyle:NSTextFieldSquareBezel];
		[gppriceText setFrame:NSMakeRect(70, frame.size.height  - 4*PERROWHEIGHT+MARIN_HEIGHT-TOPMARIN_HEIGHT, 120, PERROWHEIGHT-2*MARIN_HEIGHT)];
		[[gppriceText cell] setTextColor:[NSColor blackColor]];
		customTextFieldFormatter * priceFormatt = [[customTextFieldFormatter alloc] init];
		[priceFormatt setMaxLength:9];
		[priceFormatt setShowDot:YES];
		[gppriceText setFormatter:priceFormatt];
		[priceFormatt release];
		[gppriceText setDelegate:self];
		gppriceText.focusDelegate = self;
		[self addSubview:gppriceText];
		
		priceStepper = [[NSStepper alloc] init];
		[priceStepper setFrame:NSMakeRect(190, frame.size.height  - 4*PERROWHEIGHT+2-TOPMARIN_HEIGHT, 20, PERROWHEIGHT-4)];
		[priceStepper setDoubleValue:50.0f];
		priceValue = 50.0f;
		[priceStepper setIncrement:1.0f];
		[priceStepper setAction:@selector(priceChange)];
		[self addSubview:priceStepper];
		
		tempText = [[NSTextField alloc]init];
		[tempText setEditable:NO];
		[tempText setBackgroundColor:[NSColor clearColor]];
		[tempText setBordered:NO];
		[tempText setFrame:NSMakeRect(210, frame.size.height  - 4*PERROWHEIGHT-TOPMARIN_HEIGHT, 20, PERROWHEIGHT)];
		[[tempText cell] setFont:[NSFont systemFontOfSize:14.0f]];
		[[tempText cell] setTextColor:[NSColor blackColor]];
		[tempText setTag:100];
		[[tempText cell] setTitle:@"元"];
		[self addSubview:tempText];
		[tempText release];
		
		xjwtLabel = [[NSTextField alloc]init];
		[xjwtLabel setEditable:NO];
		[xjwtLabel setBackgroundColor:COLOR_TRADEBAR_BACKGROUND];
		[xjwtLabel setBordered:NO];
		[xjwtLabel setBezeled:NO];
		[xjwtLabel setBezelStyle:NSTextFieldSquareBezel];
		[xjwtLabel setFrame:NSZeroRect];
		[[xjwtLabel cell] setTitle:@"市价委托"];
		[[xjwtLabel cell] setTextColor:[NSColor blackColor]];
		[self addSubview:xjwtLabel];
		
		
		moneynumText = [[NSTextField alloc]init];
		[moneynumText setEditable:NO];
		[moneynumText setBackgroundColor:COLOR_TRADEBAR_BACKGROUND];
		[moneynumText setBordered:NO];
		[moneynumText setBezeled:NO];
		[moneynumText setBezelStyle:NSTextFieldSquareBezel];
		[moneynumText setFrame:NSMakeRect(70, frame.size.height  - 5*PERROWHEIGHT+2-TOPMARIN_HEIGHT, 140, PERROWHEIGHT-4)];
		[[moneynumText cell] setTextColor:[NSColor blackColor]];
		[self addSubview:moneynumText];
		
		
		maxbuysellLabel = [[NSTextField alloc]init];
		[maxbuysellLabel setEditable:NO];
		[maxbuysellLabel setBackgroundColor:COLOR_TRADEBAR_BACKGROUND];
		[maxbuysellLabel setBordered:NO];
		[maxbuysellLabel setBezeled:NO];
		[maxbuysellLabel setBezelStyle:NSTextFieldSquareBezel];
		[maxbuysellLabel setFrame:NSMakeRect(70, frame.size.height  - 6*PERROWHEIGHT+2-TOPMARIN_HEIGHT, 100, PERROWHEIGHT-4)];
		[[maxbuysellLabel cell] setTextColor:[NSColor blackColor]];
		[self addSubview:maxbuysellLabel];
		
		allnumButton = [[NSButton alloc] init];
		[allnumButton setFrame:NSMakeRect(170, frame.size.height  - 6*PERROWHEIGHT+2-TOPMARIN_HEIGHT, 40, PERROWHEIGHT-4)];
		[[allnumButton cell] setTitle:@"全部"];
		[allnumButton setTarget:self];
		[allnumButton setAction:@selector(allNumClick)];
		[self addSubview:allnumButton];
		
		gpnumdwLabel = [[NSTextField alloc]init];
		[gpnumdwLabel setEditable:NO];
		[gpnumdwLabel setBackgroundColor:[NSColor clearColor]];
		[gpnumdwLabel setBordered:NO];
		[gpnumdwLabel setFrame:NSMakeRect(210, frame.size.height  - 6*PERROWHEIGHT-TOPMARIN_HEIGHT, 20, PERROWHEIGHT)];
		[[gpnumdwLabel cell] setFont:[NSFont systemFontOfSize:14.0f]];
		[[gpnumdwLabel cell] setTextColor:[NSColor blackColor]];
		[[gpnumdwLabel cell] setTitle:@"股"];
		[self addSubview:gpnumdwLabel];
		
		gpnumText = [[CustonTextField alloc]init];
		[gpnumText setEditable:YES];
		[gpnumText setBackgroundColor:[NSColor whiteColor]];
		[gpnumText setBordered:YES];
		[gpnumText setTag:NUM_TEXT_FLAG];
		[gpnumText setBezeled:YES];
		[gpnumText setBezelStyle:NSTextFieldSquareBezel];
		[gpnumText setFrame:NSMakeRect(70, frame.size.height  - 7*PERROWHEIGHT-TOPMARIN_HEIGHT, 120, PERROWHEIGHT)];
		[[gpnumText cell] setTextColor:[NSColor blackColor]];
		customTextFieldFormatter * numFormatt = [[customTextFieldFormatter alloc] init];
        numFormatt.maxLength=9;
		[gpnumText setFormatter:numFormatt];
		[numFormatt release];
		gpnumText.focusDelegate = self;
        
		[self addSubview:gpnumText];
		
		numStepper = [[NSStepper alloc] init];
		[numStepper setFrame:NSMakeRect(190, frame.size.height  - 7*PERROWHEIGHT+2-TOPMARIN_HEIGHT, 20, PERROWHEIGHT-4)];
		[numStepper setDoubleValue:50.0f];
		numValue = 500.0f;
		[numStepper setIncrement:1.0f];
		[numStepper setAction:@selector(numChange)];
		[self addSubview:numStepper];
		
		
		
		gpnumdwLabel2 = [[NSTextField alloc]init];
		[gpnumdwLabel2 setEditable:NO];
		[gpnumdwLabel2 setBackgroundColor:[NSColor clearColor]];
		[gpnumdwLabel2 setBordered:NO];
		[gpnumdwLabel2 setFrame:NSMakeRect(210, frame.size.height  - 7*PERROWHEIGHT-TOPMARIN_HEIGHT, 20, PERROWHEIGHT)];
		[[gpnumdwLabel2 cell] setFont:[NSFont systemFontOfSize:14.0f]];
		[[gpnumdwLabel2 cell] setTextColor:[NSColor blackColor]];
		[[gpnumdwLabel2 cell] setTitle:@"股"];
		[self addSubview:gpnumdwLabel2];
		
		[gpcodeText setNextKeyView:gppriceText];
		[gppriceText setNextKeyView:gpnumText];
		
		
		doneButton = [[NSButton alloc] init];
		[doneButton setFrame:NSMakeRect(140, frame.size.height  - 8*PERROWHEIGHT+2-TOPMARIN_HEIGHT, 70, PERROWHEIGHT-4)];
		[[doneButton cell] setTitle:@"买入下单"];
		[doneButton setTarget:self];
        [doneButton setAction:@selector(doneButtonClick:)];
		[self addSubview:doneButton];
		
		NSRect tempRect = NSMakeRect(WT_WIDTH+2, 0, frame.size.width-WT_WIDTH-2-2, 11*PERROWHEIGHT_PK-2);

		
		scrollView=[[NSScrollView alloc] initWithFrame:tempRect];
		[scrollView setHasHorizontalScroller:NO];
		[scrollView setHorizontalScroller:nil];
		[scrollView setHasVerticalScroller:NO];
		[scrollView setVerticalScroller:nil];
		[scrollView setDrawsBackground:NO];
		
		myTableView = [[myTableView2 alloc] initWithFrame:tempRect];
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
		
		[self addColumn:@"name" withTitle:@"" withWidth:40];
		[self addColumn:@"price" withTitle:@"" withWidth:70];
		[self addColumn:@"vol" withTitle:@"" withWidth:70];
		[myTableView setDataSource:self];
		[myTableView setDelegate:self];
		
		[scrollView setDocumentView:myTableView];
		[scrollView setBackgroundColor:[NSColor clearColor]];
		[self addSubview:scrollView];
        
//		[scrollView release];
		
        /**
         *担保品划转 View
         */

        DBPHZView = [[NSView alloc] initWithFrame:NSMakeRect(0, 0,230, frame.size.height)];
        [DBPHZView setWantsLayer:YES];
        DBPHZView.layer.backgroundColor = [NSColor colorWithCalibratedRed:231.0/255.0 green:231.0/255.0 blue:231.0/255.0 alpha:1.000].CGColor;

        NSArray * DBPHZTitle=[[NSArray arrayWithObjects:@"划转方向:",@"信用股东:",@"普通股东:",@"证券代码:",@"最大可划:",@"划转数量:",nil] retain];
        HZFXArray = [[NSArray arrayWithObjects:@"划入信用帐户",@"划出信用帐户",nil] retain];
    
        for (int i=0; i<DBPHZTitle.count; i++) {
             NSTextField * tempText = [[NSTextField alloc]init];
            [tempText setEditable:NO];
            [tempText setBackgroundColor:[NSColor clearColor]];
            [tempText setBordered:NO];
            [tempText setFrame:NSMakeRect(leftBlankWidth, frame.size.height  - (i+1)*PERROWHEIGHT-TOPMARIN_HEIGHT, 70, PERROWHEIGHT)];
            [[tempText cell] setFont:[NSFont systemFontOfSize:14.0f]];
            [[tempText cell] setTextColor:[NSColor blackColor]];
            [[tempText cell] setTitle:[DBPHZTitle objectAtIndex:i]];
            [tempText setTag:i+textFieldtag];
            [DBPHZView addSubview:tempText];
            [tempText release];
        }

        HZFXCombobox = [[NSComboBox alloc] initWithFrame:NSMakeRect(70, frame.size.height  - PERROWHEIGHT-TOPMARIN_HEIGHT, 140, PERROWHEIGHT)];
        [HZFXCombobox setBackgroundColor:[NSColor clearColor]];
        [HZFXCombobox setEditable:NO];
        [HZFXCombobox setUsesDataSource:YES];
        [HZFXCombobox setDelegate:self];
        [HZFXCombobox setDataSource:self];
        [[HZFXCombobox cell]setTitle:@"划入信用帐户"];
        [DBPHZView addSubview:HZFXCombobox];
        
        PTgddmCombobox = [[NSComboBox alloc] initWithFrame:NSMakeRect(70, frame.size.height  - 3*PERROWHEIGHT-TOPMARIN_HEIGHT, 140, PERROWHEIGHT)];
        [PTgddmCombobox setBackgroundColor:[NSColor clearColor]];
        [PTgddmCombobox setEditable:NO];
        [PTgddmCombobox setUsesDataSource:YES];
        [PTgddmCombobox setDelegate:self];
        [PTgddmCombobox setDataSource:self];
        [[PTgddmCombobox cell]setTitle:@""];
        [DBPHZView addSubview:PTgddmCombobox];
        
        
        
        NSButton * doneButton1 = [[NSButton alloc] init];
        [doneButton1 setFrame:NSMakeRect(140, frame.size.height  - 7*PERROWHEIGHT+2-TOPMARIN_HEIGHT, 70, PERROWHEIGHT-4)];
        [[doneButton1 cell] setTitle:@"下  单"];
        [doneButton1 setTarget:self];
        [doneButton1 setAction:@selector(doneButtonClick:)];
        [DBPHZView addSubview:doneButton1];
       
        [self addSubview:DBPHZView];
        
        //添加 现券还券
        XQHQView = [[NSView alloc] initWithFrame:NSMakeRect(0, 0,230, frame.size.height)];
        [XQHQView setWantsLayer:YES];
        XQHQView.layer.backgroundColor = [NSColor colorWithCalibratedRed:231.0/255.0 green:231.0/255.0 blue:231.0/255.0 alpha:1.000].CGColor;
        
        NSArray * XQHQTitle=[[NSArray arrayWithObjects:@"股东代码:",@"证券代码:",@"最大可还:",@"还券数量:",nil] retain];
        for (int i=0; i<XQHQTitle.count; i++) {
            NSTextField * tempText = [[NSTextField alloc]init];
            [tempText setEditable:NO];
            [tempText setBackgroundColor:[NSColor clearColor]];
            [tempText setBordered:NO];
            [tempText setFrame:NSMakeRect(leftBlankWidth, frame.size.height  - (i+1)*PERROWHEIGHT-TOPMARIN_HEIGHT, 70, PERROWHEIGHT)];
            [[tempText cell] setFont:[NSFont systemFontOfSize:14.0f]];
            [[tempText cell] setTextColor:[NSColor blackColor]];
            [[tempText cell] setTitle:[XQHQTitle objectAtIndex:i]];
            [tempText setTag:i+textFieldtag];
            [XQHQView addSubview:tempText];
            [tempText release];
        }
        NSButton * doneButton2 = [[NSButton alloc] init];
        [doneButton2 setFrame:NSMakeRect(140, frame.size.height  - 5*PERROWHEIGHT+2-TOPMARIN_HEIGHT, 70, PERROWHEIGHT-4)];
        [[doneButton2 cell] setTitle:@"下  单"];
        [doneButton2 setTarget:self];
        [doneButton2 setAction:@selector(doneButtonClick:)];
        [XQHQView addSubview:doneButton2];
        [self addSubview:XQHQView];
        
        //添加 现金还款
        XJHKView = [[NSView alloc] initWithFrame:NSMakeRect(0, 0,230, frame.size.height)];
        [XJHKView setWantsLayer:YES];
        XJHKView.layer.backgroundColor = [NSColor colorWithCalibratedRed:231.0/255.0 green:231.0/255.0 blue:231.0/255.0 alpha:1.000].CGColor;
        
        BZArray = [[NSArray arrayWithObjects:@"人民币",nil] retain];
        NSArray * XJHKTitle=[[NSArray arrayWithObjects:@"币    种:",@"可用金额:",@"需还款额:",@"还款金额:",nil] retain];
        for (int i=0; i<XJHKTitle.count; i++) {
            NSTextField * xjtempText = [[NSTextField alloc]init];
            [xjtempText setEditable:NO];
            [xjtempText setBackgroundColor:[NSColor clearColor]];
            [xjtempText setBordered:NO];
            [xjtempText setFrame:NSMakeRect(leftBlankWidth, frame.size.height  - (i+1)*PERROWHEIGHT-TOPMARIN_HEIGHT, 70, PERROWHEIGHT)];
            [[xjtempText cell] setFont:[NSFont systemFontOfSize:14.0f]];
            [[xjtempText cell] setTextColor:[NSColor blackColor]];
            [[xjtempText cell] setTitle:[XJHKTitle objectAtIndex:i]];
            [xjtempText setTag:i+textFieldtag];
            [XJHKView addSubview:xjtempText];
            [xjtempText release];
        }
        
        BZCombobox = [[NSComboBox alloc] initWithFrame:NSMakeRect(70, frame.size.height  - PERROWHEIGHT-TOPMARIN_HEIGHT, 140, PERROWHEIGHT)];
        [BZCombobox setBackgroundColor:[NSColor clearColor]];
        [BZCombobox setEditable:NO];
        [BZCombobox setUsesDataSource:YES];
        [BZCombobox setDelegate:self];
        [BZCombobox setDataSource:self];
        [[BZCombobox cell]setTitle:@"人民币"];
        [XJHKView addSubview:BZCombobox];
        
        
        kyjeLabel = [[NSTextField alloc]init];
        [kyjeLabel setEditable:NO];
        [kyjeLabel setBackgroundColor:COLOR_TRADEBAR_BACKGROUND];
        [kyjeLabel setBordered:NO];
        [kyjeLabel setFrame:NSMakeRect(70, frame.size.height  - 2*PERROWHEIGHT-TOPMARIN_HEIGHT, 140, PERROWHEIGHT)];
        [kyjeLabel setBezeled:NO];
        [kyjeLabel setBezelStyle:NSTextFieldSquareBezel];
        [[kyjeLabel cell] setFont:[NSFont systemFontOfSize:15.0f]];
        [[kyjeLabel cell] setTextColor:[NSColor blackColor]];
        [[kyjeLabel cell] setTitle:@"0.00"];
        [XJHKView addSubview:kyjeLabel];
        
        xhkeLabel = [[NSTextField alloc]init];
        [xhkeLabel setEditable:NO];
        [xhkeLabel setBackgroundColor:COLOR_TRADEBAR_BACKGROUND];
        [xhkeLabel setBordered:NO];
        [xhkeLabel setBezeled:NO];
        [xhkeLabel setBezelStyle:NSTextFieldSquareBezel];
        [xhkeLabel setFrame:NSMakeRect(70, frame.size.height  - 3*PERROWHEIGHT+2-TOPMARIN_HEIGHT, 100, PERROWHEIGHT-4)];
        [[xhkeLabel cell] setTextColor:[NSColor blackColor]];
        [XJHKView addSubview:xhkeLabel];
        
        xhkeAllMoneyButton = [[NSButton alloc] init];
        [xhkeAllMoneyButton setFrame:NSMakeRect(170, frame.size.height  - 3*PERROWHEIGHT+2-TOPMARIN_HEIGHT, 40, PERROWHEIGHT-4)];
        [[xhkeAllMoneyButton cell] setTitle:@"全部"];
        [xhkeAllMoneyButton setTarget:self];
        [xhkeAllMoneyButton setAction:@selector(xjhkAllMoneyButton)];
        [XJHKView addSubview:xhkeAllMoneyButton];
        
        NSTextField* moneydwLabel = [[NSTextField alloc]init];
        [moneydwLabel setEditable:NO];
        [moneydwLabel setBackgroundColor:[NSColor clearColor]];
        [moneydwLabel setBordered:NO];
        [moneydwLabel setFrame:NSMakeRect(210, frame.size.height  - 3*PERROWHEIGHT-TOPMARIN_HEIGHT, 20, PERROWHEIGHT)];
        [[moneydwLabel cell] setFont:[NSFont systemFontOfSize:14.0f]];
        [[moneydwLabel cell] setTextColor:[NSColor blackColor]];
        [[moneydwLabel cell] setTitle:@"元"];
        [XJHKView addSubview:moneydwLabel];
        
        
        xjhkpriceText = [[CustonTextField alloc]init];
        [xjhkpriceText setEditable:YES];
        [xjhkpriceText setBackgroundColor:[NSColor whiteColor]];
        [xjhkpriceText setBordered:YES];
        [xjhkpriceText setBezeled:YES];
        [xjhkpriceText setTag:PRICE_TEXT_FLAG];
        [xjhkpriceText setBezelStyle:NSTextFieldSquareBezel];
        [xjhkpriceText setFrame:NSMakeRect(70, frame.size.height  - 4*PERROWHEIGHT+MARIN_HEIGHT-TOPMARIN_HEIGHT, 120, PERROWHEIGHT-2*MARIN_HEIGHT)];
        [[xjhkpriceText cell] setTextColor:[NSColor blackColor]];
        customTextFieldFormatter * priceFormattxjkh = [[customTextFieldFormatter alloc] init];
        [priceFormattxjkh setMaxLength:9];
        [priceFormattxjkh setShowDot:YES];
        [xjhkpriceText setFormatter:priceFormattxjkh];
        [priceFormattxjkh release];
        [xjhkpriceText setDelegate:self];
        xjhkpriceText.focusDelegate = self;
        [XJHKView addSubview:xjhkpriceText];
        
        xjhkpriceStepper = [[NSStepper alloc] init];
        [xjhkpriceStepper setFrame:NSMakeRect(190, frame.size.height  - 4*PERROWHEIGHT+2-TOPMARIN_HEIGHT, 20, PERROWHEIGHT-4)];
        [xjhkpriceStepper setDoubleValue:50.0f];
        xjhkpriceValue = 50.0f;
        [xjhkpriceStepper setIncrement:1.0f];
        [xjhkpriceStepper setAction:@selector(xjhkpriceChange)];
        [XJHKView addSubview:xjhkpriceStepper];
        
        NSTextField* xjhktempText = [[NSTextField alloc]init];
        [xjhktempText setEditable:NO];
        [xjhktempText setBackgroundColor:[NSColor clearColor]];
        [xjhktempText setBordered:NO];
        [xjhktempText setFrame:NSMakeRect(210, frame.size.height  - 4*PERROWHEIGHT-TOPMARIN_HEIGHT, 20, PERROWHEIGHT)];
        [[xjhktempText cell] setFont:[NSFont systemFontOfSize:14.0f]];
        [[xjhktempText cell] setTextColor:[NSColor blackColor]];
        [xjhktempText setTag:100];
        [[xjhktempText cell] setTitle:@"元"];
        [XJHKView addSubview:xjhktempText];
        [xjhktempText release];
        
        NSButton * doneButton3 = [[NSButton alloc] init];
        [doneButton3 setFrame:NSMakeRect(140, frame.size.height  - 5*PERROWHEIGHT+2-TOPMARIN_HEIGHT, 70, PERROWHEIGHT-4)];
        [[doneButton3 cell] setTitle:@"确定"];
        [doneButton3 setTarget:self];
        [doneButton3 setAction:@selector(doneButtonClick:)];
        [XJHKView addSubview:doneButton3];
        
        [self addSubview:XJHKView];
        
		baddflag=YES;
		m_bbusy = NO;
		m_bediting=NO;
		m_bButtonshowflag = NO;
		m_bmoveflag = NO;
		
		m_xsflag=2;
		self.wtPrice = 0;
		m_gdmx=nil;
		m_bfirstflag=YES;
		lastzqdm=nil;
		lastmaxzqdm=nil;
		lastprice=nil;
		lastkyzj=nil;
		lastbsflag=-1;
		ngdIndex=0;
		m_setcode=0;
		pickindex=0;
		nselectindex=0;
		bpopupflag=NO;
		btradesucflag=NO;
		m_bolzq=NO;
		bsdmmflag=NO;
		m_btouchmoved=NO;
		m_ngzdw=0;
		m_bzyrk=NO;
		m_bzyck=NO;
		m_bolhg=eGetData.clientinfos.m_bxyjyflag;
		m_bautonext=NO;
		fztjg=0.0f;
		fdtjg=0.0f;
		m_brefreshflag = NO;
	}
	
	return self;
}

-(void) controlTextDidBeginEditing:(NSNotification *)obj{

}

-(void) controlTextDidEndEditing:(NSNotification *)obj{
	NSTextField * tempText = [obj object];
	
	if ([tempText tag] == PRICE_TEXT_FLAG) {
		[self OnGpMaxBuySell];
	}
}

-(void) controlTextDidChange:(NSNotification *)obj{
	NSTextField * tempText = [obj object];
	if ([tempText tag] == CODE_TEXT_FLAG) {
		if ([[[tempText cell] title] length] == 6) {
			[[gppriceText cell] setTitle:@""];
			m_brefreshflag = NO;
			[self QueryGpInfo];
		}
	}
    else if([tempText tag]==PRICE_TEXT_FLAG)
    {
        NSString *strprice=[[gppriceText cell] title];
        NSRange range=[strprice rangeOfString:@"."];
        if(range.length==1)
        {
            NSString *substr=[strprice substringFromIndex:range.location+range.length];
            if([substr length]>m_xsflag)
            {
                [[gppriceText cell] setTitle:[NSString stringWithFormat:@"%@",[strprice substringToIndex:range.location+range.length+m_xsflag]]];
            }
        }
    }
}

-(id) setFrame:(NSRect)frameRect{
    [super setFrame:frameRect];
    viewRect = frameRect;
    [self dealBarView];
    [self setNeedsDisplay:YES];
    [myTableView reloadData];
    return nil;
}

-(void)dealBarView{
    
    int i ;
    int _length = [titleLabelArray count];
    NSTextField * tempText;
    for (i=0; i<_length; i++)
    {
        tempText = (NSTextField *)[self viewWithTag:i+textFieldtag];
        [tempText setFrame:NSMakeRect(leftBlankWidth, viewRect.size.height  - (i+1)*PERROWHEIGHT-TOPMARIN_HEIGHT, 70, PERROWHEIGHT)];

    }
    
    [gddmCombobox setFrame:NSMakeRect(70, viewRect.size.height  - PERROWHEIGHT-TOPMARIN_HEIGHT, 140, PERROWHEIGHT)];
        [gpcodeText setFrame:NSMakeRect(70, viewRect.size.height  - 2*PERROWHEIGHT+MARIN_HEIGHT-TOPMARIN_HEIGHT, 70, PERROWHEIGHT-2*MARIN_HEIGHT)];
        [gpnameLabel setFrame:NSMakeRect(140, viewRect.size.height  - 2*PERROWHEIGHT-TOPMARIN_HEIGHT, 70, PERROWHEIGHT)];
        [bjfsCombobox setFrame:NSMakeRect(70, viewRect.size.height  -3*PERROWHEIGHT-TOPMARIN_HEIGHT, 140, PERROWHEIGHT)];
        [gppriceText setFrame:NSMakeRect(70, viewRect.size.height  - 4*PERROWHEIGHT+MARIN_HEIGHT-TOPMARIN_HEIGHT, 120, PERROWHEIGHT-2*MARIN_HEIGHT)];
		[priceStepper setFrame:NSMakeRect(190, viewRect.size.height  - 4*PERROWHEIGHT+2-TOPMARIN_HEIGHT, 20, PERROWHEIGHT-4)];
        tempText = (NSTextField *)[self viewWithTag:100];
		[tempText setFrame:NSMakeRect(210, viewRect.size.height  - 4*PERROWHEIGHT-TOPMARIN_HEIGHT, 20, PERROWHEIGHT)];
        [moneynumText setFrame:NSMakeRect(70, viewRect.size.height  - 5*PERROWHEIGHT+2-TOPMARIN_HEIGHT, 140, PERROWHEIGHT-4)];
        [maxbuysellLabel setFrame:NSMakeRect(70, viewRect.size.height  - 6*PERROWHEIGHT+2-TOPMARIN_HEIGHT, 100, PERROWHEIGHT-4)];
        [allnumButton setFrame:NSMakeRect(170, viewRect.size.height  - 6*PERROWHEIGHT+2-TOPMARIN_HEIGHT, 40, PERROWHEIGHT-4)];
        [gpnumdwLabel setFrame:NSMakeRect(210, viewRect.size.height  - 6*PERROWHEIGHT-TOPMARIN_HEIGHT, 20, PERROWHEIGHT)];
        [gpnumText setFrame:NSMakeRect(70, viewRect.size.height  - 7*PERROWHEIGHT-TOPMARIN_HEIGHT, 120, PERROWHEIGHT)];
        [numStepper setFrame:NSMakeRect(190, viewRect.size.height  - 7*PERROWHEIGHT+2-TOPMARIN_HEIGHT, 20, PERROWHEIGHT-4)];
        [gpnumdwLabel2 setFrame:NSMakeRect(210, viewRect.size.height  - 7*PERROWHEIGHT-TOPMARIN_HEIGHT, 20, PERROWHEIGHT)];
        [doneButton setFrame:NSMakeRect(140, viewRect.size.height  - 8*PERROWHEIGHT+2-TOPMARIN_HEIGHT, 70, PERROWHEIGHT-4)];
    
        [myTableView setFrame:NSMakeRect(WT_WIDTH+2, viewRect.size.height - 245, viewRect.size.width-WT_WIDTH-2-2, 11*PERROWHEIGHT_PK-2)];
    
        [scrollView setFrame:NSMakeRect(WT_WIDTH+2, viewRect.size.height - 245, viewRect.size.width-WT_WIDTH-2-2, 11*PERROWHEIGHT_PK-2)];
    
}

-(void)priceChange{
	float tempFloat = [priceStepper doubleValue];
	BOOL addFlag = NO;
	if (tempFloat > priceValue) {
		addFlag = YES;
	}
	else {
		addFlag = NO;
	}

	priceValue = tempFloat;
	float tempPrice = [[[gppriceText cell] title] floatValue];
	if (m_xsflag == 2) {
		if (addFlag) {
			tempPrice = tempPrice + 0.01f;
		}
		else {
			tempPrice = tempPrice - 0.01f;
		}
		if (tempPrice < 0) {
			tempPrice = 0;
		}
		[[gppriceText cell] setTitle:[NSString stringWithFormat:@"%.2f",tempPrice]];
	}
	else {
		if (addFlag) {
			tempPrice = tempPrice + 0.001f;
		}
		else {
			tempPrice = tempPrice - 0.001f;
		}
		if (tempPrice < 0) {
			tempPrice = 0;
		}
		[[gppriceText cell] setTitle:[NSString stringWithFormat:@"%.3f",tempPrice]];
	}
	
}

-(void)xjhkpriceChange{
    float tempFloat = [xjhkpriceText doubleValue];
    BOOL addFlag = NO;
    if (tempFloat > xjhkpriceValue) {
        addFlag = YES;
    }
    else {
        addFlag = NO;
    }
    
    xjhkpriceValue = tempFloat;
    float tempPrice = [[[xjhkpriceText cell] title] floatValue];
    if (addFlag) {
        tempPrice = tempPrice + 0.01f;
    }
    else {
        tempPrice = tempPrice - 0.01f;
    }
    if (tempPrice < 0) {
        tempPrice = 0;
    }
    [[xjhkpriceText cell] setTitle:[NSString stringWithFormat:@"%.2f",tempPrice]];
}

-(void)numChange{
	int  tempInt = [numStepper doubleValue];
	BOOL addFlag = NO;
	if (tempInt > numValue) {
		addFlag = YES;
	}
	else {
		addFlag = NO;
	}
	
	numValue = tempInt;
	int  tempVol = [[[gpnumText cell] title] floatValue];
	if (addFlag) {
        if (m_ngzdw==0) {
            tempVol = tempVol + 100;
        }
		else if(m_ngzdw==1)
        {
            tempVol = tempVol + 1;
        }
        else
        {
            tempVol = tempVol + 10;
        }
	}
	else {
		if (m_ngzdw==0) {
            tempVol = tempVol -100;
        }
		else if(m_ngzdw==1)
        {
            tempVol = tempVol - 1;
        }
        else
        {
            tempVol = tempVol - 10;
        }
	}
	if (tempVol < 0) {
		tempVol = 0;
	}
	
	if ((tempVol > [[[maxbuysellLabel cell] title] intValue]) && ([[[maxbuysellLabel cell] title] intValue] > 0)){
		tempVol = [[[maxbuysellLabel cell] title] intValue];
	}
	[[gpnumText cell] setTitle:[NSString stringWithFormat:@"%i",tempVol]];
}


-(void)allNumClick{
	if ([[[maxbuysellLabel cell] title] intValue] >0) {
		[[gpnumText cell] setTitle:[NSString stringWithFormat:@"%i",[[[maxbuysellLabel cell] title] intValue]]];
	}
}

-(void)xjhkAllMoneyButton{
    if ([[[kyjeLabel cell] title] floatValue] >= 0)
    {
        [[xjhkpriceText cell] setTitle:[[xhkeLabel cell] title]];
    }
}

-(void) doneButtonClick:(NSButton*)sender{
	[eGetData.clientinfos jyhasoper];
	if([self IsCanQueryOther]==NO)
		return;
	[self AutoCheckWtsl];
    if(eGetData.tradeType == XJHK)
    {
        [self xjhkdoBuySell];
    }
    else
    {
        [self doBuySell];
    }

}


-(void)AutoCheckWtsl
{
	long long gpvol=[[[gpnumText cell]title] longLongValue];
	long long maxvol=[[[maxbuysellLabel cell]title] longLongValue];
	if((self.tag==1||self.tag ==3) && gpvol==maxvol)
		;
	else 
	{
	}
	

	if(gpvol<=0)
		[[gpnumText cell] setTitle:@""];
	else 
		[[gpnumText cell] setTitle:[NSString stringWithFormat:@"%lli",gpvol]];
}

#pragma mark  focusDelegate相关
-(void)getFocus:(int)_tag{
	switch (_tag) {
		case PRICE_TEXT_FLAG:
			break;
		case NUM_TEXT_FLAG:
			break;
			
		default:
			break;
	}
}


-(void)getEnter:(int)_tag{
	switch (_tag) {
		case CODE_TEXT_FLAG:
			[[self window] makeFirstResponder:gppriceText];
			break;

		case PRICE_TEXT_FLAG:
			[[self window] makeFirstResponder:gpnumText];
			break;
		case NUM_TEXT_FLAG:
			[[self window] makeFirstResponder:doneButton];
            [self doneButtonClick:doneButton];
			break;
		default:
			break;
	}
}

-(void)getEsc:(int)_tag{
	if (showType == 0) {
		[showDelegate closeFastWT];
	}
}

-(void)getKeyUp:(NSEvent *)theEvent{
}

#pragma mark  tableview相关
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
-(void)singleClick:(id)sender{
    int nindex=[myTableView selectedRow];
    if(nindex<0 || nindex>=[pkShowArray count])
        return;
	NSDictionary * tempDict = [pkShowArray objectAtIndex:nindex];
    NSString *strprice=[tempDict objectForKey:@"price"];
    if([strprice length])
        [[gppriceText cell] setTitle:strprice];
	
	[[self window] makeFirstResponder:gppriceText];
}

- (NSInteger)numberOfRowsInTableView:(NSTableView *)tableView;
{
	return [pkShowArray count];
}

-(CGFloat) tableView:(NSTableView *)tableView heightOfRow:(NSInteger)row{
	return PERROWHEIGHT_PK;
}

- (id)tableView:(NSTableView *)tableView objectValueForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row;
{
	if (row > [pkShowArray count]-1) {
		return @"";
	}
	NSDictionary * tempDict = [pkShowArray objectAtIndex:row];
	NSString * tempString;
	if ([[tableColumn identifier] isEqual:@"name"]) {
		tempString = [tempDict objectForKey:@"name"];
		return tempString;
	}
	
	else if([[tableColumn identifier] isEqual:@"price"]) {
		tempString = [tempDict objectForKey:@"price"];
		return tempString;
	}
	else if([[tableColumn identifier] isEqual:@"vol"]){
		return [tempDict objectForKey:@"vol"];
	}

	
	return @"";
}

-(void)tableView:(NSTableView *)tableView willDisplayCell:(id)cell forTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row{
	if (row > [pkShowArray count]-1) {
	}
	NSDictionary * tempDict = [pkShowArray objectAtIndex:row];

	if ([[tableColumn identifier] isEqual:@"name"]) {
		
	}
	
	else if([[tableColumn identifier] isEqual:@"price"]) {
		 if ([[tempDict objectForKey:@"price"] floatValue]> currClose) {
			 [cell setTextColor:[NSColor redColor]];
		 }
		 else if ([[tempDict objectForKey:@"price"] floatValue]< currClose) {
			 [cell setTextColor:HQCOLOR_DOWN];
		 }
		 else {
			 [cell setTextColor:[NSColor blackColor]];
		 }


	}
	else if([[tableColumn identifier] isEqual:@"vol"]){
		if (row < 5) {
			[cell setTextColor:[NSColor blueColor]];
		}
		else {
			[cell setTextColor:[NSColor redColor]];
		}

		
	}
}



#pragma mark 页面显示相关
- (void)clearLabel{

}

- (void)onviewWillAppear{
	baddflag=YES;
	
	[lastzqdm release];
	lastzqdm=nil;
	[lastmaxzqdm release];
	lastmaxzqdm=nil;
	[lastprice release];
	lastprice=nil;
	[lastkyzj release];
	lastkyzj=nil;
	
	[self dealBorS];
	
	if(eGetData.clientinfos.gdinfos.m_gdcount)
	{
		if(ngdIndex<0 || ngdIndex>=eGetData.clientinfos.gdinfos.m_gdcount)
			ngdIndex=0;
		GdmxInfo *tmpgdmx=[eGetData.clientinfos.gdinfos.gddms objectAtIndex:ngdIndex];
		if(tmpgdmx)
			m_gdmx=tmpgdmx;
		else 
			m_gdmx=nil;
	}
	NSString * tempString = [m_gdmx GetGdDescribe];
	if ([tempString length]>0) {
		[[gddmCombobox cell] setTitle:tempString];
	}
	
	eGetData.inputSave.gddm=[NSString stringWithFormat:@"%@",m_gdmx.gddm];
	eGetData.inputSave.accoutType=m_gdmx.wttype;

	
	int tempInt = 0;
	m_nsjfsindex=tempInt;
	
	if(tempInt>0)
		m_bsjwtflag=YES;
	else 
		m_bsjwtflag=NO;
	
	NSTextField * tempTextField;
	tempTextField = [self viewWithTag:100];
	if (tempInt == 0) {
		[gppriceText setFrame:NSMakeRect(70, viewRect.size.height  - 4*PERROWHEIGHT+2, 120, PERROWHEIGHT-4)];
		[priceStepper setFrame:NSMakeRect(190, viewRect.size.height  - 4*PERROWHEIGHT+2, 20, PERROWHEIGHT-4)];
		[[tempTextField cell] setTitle:@"元"];
		[xjwtLabel setFrame:NSZeroRect];
	}
	else {
		[gppriceText setFrame:NSZeroRect];
		[priceStepper setFrame:NSZeroRect];
		[[tempTextField cell] setTitle:@""];
		[xjwtLabel setFrame:NSMakeRect(70, viewRect.size.height  - 4*PERROWHEIGHT+2, 140, PERROWHEIGHT-4)];
	}
	
	[[self window] makeFirstResponder:gpcodeText];
	if ([[[gpcodeText cell] title] length]==6) {
		[self QueryGpInfo];
	}
}

-(void)dealBorS{ //处理买入卖出的页面差别

    [[gpnumdwLabel cell] setTitle:@"股"];
    
    [gddmCombobox removeFromSuperview];
    [gpcodeText removeFromSuperview];
    [numStepper removeFromSuperview];
    [moneynumText removeFromSuperview];
    [maxbuysellLabel removeFromSuperview];
    [allnumButton removeFromSuperview];
    [gpnumdwLabel removeFromSuperview];
    [gpnumText removeFromSuperview];
    [gpnumdwLabel2 removeFromSuperview];
    [gpnameLabel removeFromSuperview];
   
    [gpcodeText setFrame:NSMakeRect(70, viewRect.size.height  - 2*PERROWHEIGHT+MARIN_HEIGHT-TOPMARIN_HEIGHT, 70, PERROWHEIGHT-2*MARIN_HEIGHT)];
    [gddmCombobox setFrame:NSMakeRect(70,viewRect.size.height  - PERROWHEIGHT-TOPMARIN_HEIGHT, 140, PERROWHEIGHT)];
    
    if (eGetData.tradeType == DBPHZ) {
        DBPHZView.hidden = NO;
        XQHQView.hidden = YES;
        XJHKView.hidden = YES;
        [DBPHZView addSubview:gddmCombobox];
        [DBPHZView addSubview:gpcodeText];
        [DBPHZView addSubview:numStepper];
        [DBPHZView addSubview:moneynumText];
        [DBPHZView addSubview:maxbuysellLabel];
        [DBPHZView addSubview:allnumButton];
        [DBPHZView addSubview:gpnumdwLabel];
        [DBPHZView addSubview:gpnumText];
        [DBPHZView addSubview:gpnumdwLabel2];
        [DBPHZView addSubview:gpnameLabel];
        
        [gpcodeText setFrame:NSMakeRect(70, viewRect.size.height  - 4*PERROWHEIGHT+MARIN_HEIGHT-TOPMARIN_HEIGHT, 70, PERROWHEIGHT-2*MARIN_HEIGHT)];
        [gddmCombobox setFrame:NSMakeRect(70,viewRect.size.height  - 2*PERROWHEIGHT-TOPMARIN_HEIGHT, 140, PERROWHEIGHT)];
        [gpnameLabel setFrame:NSMakeRect(140, viewRect.size.height  - 4*PERROWHEIGHT-TOPMARIN_HEIGHT, 70, PERROWHEIGHT)];

    }
    else if(eGetData.tradeType == XQHQ)
    {
        //删除原来不用的控件
        [bjfsCombobox removeFromSuperview];
        [gppriceText removeFromSuperview];
        [priceStepper removeFromSuperview];
        [xjwtLabel removeFromSuperview];
        
        //添加新控件
        XQHQView.hidden = NO;
        DBPHZView.hidden = YES;
        XJHKView.hidden = YES;
        
        [XQHQView addSubview:gddmCombobox];
        [XQHQView addSubview:gpcodeText];
        [XQHQView addSubview:gpnameLabel];
        [XQHQView addSubview:maxbuysellLabel];
        [XQHQView addSubview:allnumButton];
        [XQHQView addSubview:gpnumdwLabel];
        [XQHQView addSubview:gpnumText];
        [XQHQView addSubview:numStepper];
        [XQHQView addSubview:gpnumdwLabel2];
        
        [maxbuysellLabel setFrame:NSMakeRect(70, viewRect.size.height  - 3*PERROWHEIGHT+2-TOPMARIN_HEIGHT, 100, PERROWHEIGHT-4)];
        [allnumButton setFrame:NSMakeRect(170, viewRect.size.height  - 3*PERROWHEIGHT+2-TOPMARIN_HEIGHT, 40, PERROWHEIGHT-4)];
        [gpnumdwLabel setFrame:NSMakeRect(210, viewRect.size.height  - 3*PERROWHEIGHT-TOPMARIN_HEIGHT, 20, PERROWHEIGHT)];
        [gpnumText setFrame:NSMakeRect(70, viewRect.size.height  - 4*PERROWHEIGHT-TOPMARIN_HEIGHT, 120, PERROWHEIGHT)];
        [numStepper setFrame:NSMakeRect(190, viewRect.size.height  - 4*PERROWHEIGHT+2-TOPMARIN_HEIGHT, 20, PERROWHEIGHT-4)];
        [gpnumdwLabel2 setFrame:NSMakeRect(210, viewRect.size.height  - 4*PERROWHEIGHT-TOPMARIN_HEIGHT, 20, PERROWHEIGHT)];
        
        return;
    }
    else if(eGetData.tradeType == XJHK)
    {
        XJHKView.hidden = NO;
        DBPHZView.hidden = YES;
        XQHQView.hidden = YES;
        myTableView.hidden = YES;
        scrollView.hidden = YES;
        [scrollView removeFromSuperview];
        return;
    }
    else
    {
        
        [self addSubview:gddmCombobox];
        [self addSubview:gpcodeText];
        [self addSubview:numStepper];
        [self addSubview:moneynumText];
        [self addSubview:maxbuysellLabel];
        [self addSubview:allnumButton];
        [self addSubview:gpnumdwLabel];
        [self addSubview:gpnumText];
        [self addSubview:gpnumdwLabel2];
        [self addSubview:gpnameLabel];
        [self addSubview:bjfsCombobox];
        [self addSubview:gppriceText];
        [self addSubview:priceStepper];
        [self addSubview:xjwtLabel];
        
        DBPHZView.hidden = YES;
        XQHQView.hidden = YES;
        XJHKView.hidden = YES;
        
        if (eGetData.tradeType == DBPHZ)
        {
            [gpcodeText setFrame:NSMakeRect(70, viewRect.size.height  - 2*PERROWHEIGHT+MARIN_HEIGHT-TOPMARIN_HEIGHT, 70, PERROWHEIGHT-2*MARIN_HEIGHT)];
            [gddmCombobox setFrame:NSMakeRect(70,viewRect.size.height  - PERROWHEIGHT-TOPMARIN_HEIGHT, 140, PERROWHEIGHT)];
            [gpnameLabel setFrame:NSMakeRect(140, viewRect.size.height  - 2*PERROWHEIGHT-TOPMARIN_HEIGHT, 70, PERROWHEIGHT)];
        }
        else if(eGetData.tradeType == XQHQ)
        {
            [maxbuysellLabel setFrame:NSMakeRect(70, viewRect.size.height  - 5*PERROWHEIGHT+2-TOPMARIN_HEIGHT, 100, PERROWHEIGHT-4)];
            [allnumButton setFrame:NSMakeRect(170, viewRect.size.height  - 5*PERROWHEIGHT+2-TOPMARIN_HEIGHT, 40, PERROWHEIGHT-4)];
            [gpnumdwLabel setFrame:NSMakeRect(210, viewRect.size.height  - 5*PERROWHEIGHT-TOPMARIN_HEIGHT, 20, PERROWHEIGHT)];
            [gpnumText setFrame:NSMakeRect(70, viewRect.size.height  - 6*PERROWHEIGHT-TOPMARIN_HEIGHT, 120, PERROWHEIGHT)];
            [numStepper setFrame:NSMakeRect(190, viewRect.size.height  - 6*PERROWHEIGHT+2-TOPMARIN_HEIGHT, 20, PERROWHEIGHT-4)];
            [gpnumdwLabel2 setFrame:NSMakeRect(210, viewRect.size.height  - 6*PERROWHEIGHT-TOPMARIN_HEIGHT, 20, PERROWHEIGHT)];
            
            return;
        }
        else if(eGetData.tradeType == XJHK)
        {

            return;
        }
    }
    
	if (self.tag == 0
        || self.tag == 2
        || self.tag == MQHQ //买券还券
        || eGetData.tradeType == MQHQ
        )
    { //买入
        NSTextField * tempText;
		tempText = (NSTextField *)[self viewWithTag:3+textFieldtag];
		[[tempText cell] setTextColor:[NSColor redColor]];
		[[tempText cell] setTitle:@"买入价格:"];
		
        //可用资金
        tempText = (NSTextField *)[self viewWithTag:4+textFieldtag];
        [tempText setFrame:NSMakeRect(leftBlankWidth, viewRect.size.height  - (4+1)*PERROWHEIGHT-TOPMARIN_HEIGHT, 70, PERROWHEIGHT)];
        [moneynumText setFrame:NSMakeRect(70, viewRect.size.height  - 5*PERROWHEIGHT+MARIN_HEIGHT-TOPMARIN_HEIGHT, 140, PERROWHEIGHT-2*MARIN_HEIGHT)];
	
		//最大可买
		tempText = (NSTextField *)[self viewWithTag:5+textFieldtag];
		[[tempText cell] setTitle:@"最大可买:"];
		[tempText setFrame:NSMakeRect(leftBlankWidth, viewRect.size.height  - (5+1)*PERROWHEIGHT-TOPMARIN_HEIGHT, 70, PERROWHEIGHT)];
		[maxbuysellLabel setFrame:NSMakeRect(70, viewRect.size.height  - 6*PERROWHEIGHT+2-TOPMARIN_HEIGHT, 100, PERROWHEIGHT-4)];
		[allnumButton setFrame:NSMakeRect(170, viewRect.size.height  - 6*PERROWHEIGHT+2-TOPMARIN_HEIGHT, 40, PERROWHEIGHT-4)];
		[gpnumdwLabel setFrame:NSMakeRect(210, viewRect.size.height  - 6*PERROWHEIGHT-TOPMARIN_HEIGHT, 20, PERROWHEIGHT)];
		
		//买入数量
		tempText = (NSTextField *)[self viewWithTag:6+textFieldtag];
		[tempText setFrame:NSMakeRect(leftBlankWidth, viewRect.size.height  - (6+1)*PERROWHEIGHT-TOPMARIN_HEIGHT, 70, PERROWHEIGHT)];
		[[tempText cell] setTextColor:[NSColor redColor]];
		[[tempText cell] setTitle:@"买入数量:"];
		[gpnumText setFrame:NSMakeRect(70, viewRect.size.height  - 7*PERROWHEIGHT+2-TOPMARIN_HEIGHT, 120, PERROWHEIGHT-4)];
		[numStepper setFrame:NSMakeRect(190, viewRect.size.height  - 7*PERROWHEIGHT+2-TOPMARIN_HEIGHT, 20, PERROWHEIGHT-4)];
		[gpnumdwLabel2 setFrame:NSMakeRect(210, viewRect.size.height  - 7*PERROWHEIGHT-TOPMARIN_HEIGHT, 20, PERROWHEIGHT)];
		
		
		//按钮
		NSMutableParagraphStyle * tempStyle = [[NSMutableParagraphStyle alloc]init] ;
		[tempStyle setAlignment:NSCenterTextAlignment];
		
		NSDictionary * attrsDictionary = [NSDictionary dictionaryWithObjectsAndKeys:[NSColor redColor],NSForegroundColorAttributeName,tempStyle,NSParagraphStyleAttributeName,nil];
		NSAttributedString * attrString = [[NSAttributedString alloc] initWithString:@"买入下单" attributes:attrsDictionary];
		[tempStyle release];
		
		[doneButton setAttributedTitle:attrString];
		[attrString release];
		if (showType == 0) {
			[doneButton setFrame:NSMakeRect(140, viewRect.size.height  - 8*PERROWHEIGHT-TOPMARIN_HEIGHT, 70, PERROWHEIGHT-4)];
			
		}
		else {
			[doneButton setFrame:NSMakeRect(140, viewRect.size.height  - 8*PERROWHEIGHT-2-TOPMARIN_HEIGHT, 70, PERROWHEIGHT-4)];
		}

	}
	else { //self.tag == 4(卖券还款)
       
        NSTextField * tempText1 = [[NSTextField alloc]init];
        tempText1 = (NSTextField *)[self viewWithTag:3+textFieldtag];
		[[tempText1 cell] setTextColor:[NSColor greenColor]];
		[[tempText1 cell] setTitle:@"卖出价格:"];
		
		
		//可用资金
		NSTextField *tempText2 = (NSTextField *)[self viewWithTag:4+textFieldtag];
		[tempText2 setFrame:NSZeroRect];
		[moneynumText setFrame:NSZeroRect];
		
		//最大可买
		NSTextField *tempText3 = (NSTextField *)[self viewWithTag:5+textFieldtag];
		[[tempText3 cell] setTitle:@"最大可卖:"];
		[tempText3 setFrame:NSMakeRect(leftBlankWidth, viewRect.size.height  - (4+1)*PERROWHEIGHT-TOPMARIN_HEIGHT, 70, PERROWHEIGHT)];
		[maxbuysellLabel setFrame:NSMakeRect(70, viewRect.size.height  - 5*PERROWHEIGHT+2-TOPMARIN_HEIGHT, 100, PERROWHEIGHT-4)];
		[allnumButton setFrame:NSMakeRect(170, viewRect.size.height  - 5*PERROWHEIGHT+2-TOPMARIN_HEIGHT, 40, PERROWHEIGHT-4)];
		[gpnumdwLabel setFrame:NSMakeRect(210, viewRect.size.height  - 5*PERROWHEIGHT-TOPMARIN_HEIGHT, 20, PERROWHEIGHT)];
		
		//卖出数量
		NSTextField *tempText4 = (NSTextField *)[self viewWithTag:6+textFieldtag];
		[tempText4 setFrame:NSMakeRect(leftBlankWidth, viewRect.size.height  - (5+1)*PERROWHEIGHT-TOPMARIN_HEIGHT, 70, PERROWHEIGHT)];
		[[tempText4 cell] setTextColor:[NSColor greenColor]];
		[[tempText4 cell] setTitle:@"卖出数量:"];
		[gpnumText setFrame:NSMakeRect(70, viewRect.size.height  - 6*PERROWHEIGHT+2-TOPMARIN_HEIGHT, 120, PERROWHEIGHT-4)];
		[numStepper setFrame:NSMakeRect(190, viewRect.size.height  - 6*PERROWHEIGHT+2-TOPMARIN_HEIGHT, 20, PERROWHEIGHT-4)];
		[gpnumdwLabel2 setFrame:NSMakeRect(210, viewRect.size.height  - 6*PERROWHEIGHT-TOPMARIN_HEIGHT, 20, PERROWHEIGHT)];
		
		//按钮
		
		NSMutableParagraphStyle * tempStyle = [[NSMutableParagraphStyle alloc]init] ;
		[tempStyle setAlignment:NSCenterTextAlignment];
		
		NSDictionary * attrsDictionary = [NSDictionary dictionaryWithObjectsAndKeys:[NSColor greenColor],NSForegroundColorAttributeName,tempStyle,NSParagraphStyleAttributeName,nil];
		NSAttributedString * attrString = [[NSAttributedString alloc] initWithString:@"卖出下单" attributes:attrsDictionary];
		[tempStyle release];
		
		[doneButton setAttributedTitle:attrString];
		[attrString release];
		[doneButton setFrame:NSMakeRect(140, viewRect.size.height  - 7*PERROWHEIGHT-2-TOPMARIN_HEIGHT, 70, PERROWHEIGHT-4)];
	}

}

-(void)dealTitleS{ //处理买入卖出的页面差别
	NSTextField * tempText;
	if (self.tag == 0 || self.tag==2) { //买入
		tempText = (NSTextField *)[self viewWithTag:3+textFieldtag];
		[[tempText cell] setTextColor:[NSColor redColor]];
		[[tempText cell] setTitle: (m_bolhg?(m_bzyck?@"出库价格:":@"融资价格:"):@"买入价格:")];
       
		//最大可买
		tempText = (NSTextField *)[self viewWithTag:5+textFieldtag];
		[[tempText cell] setTitle: (m_bolhg?(m_bzyck?@"最大可出:":@"最大可融:"):@"最大可买:")];
		
        if (eGetData.tradeType == RZBuy)
        {
            [[tempText cell] setTitle:@"最大可融:"];
        }
        
		//买入数量
		tempText = (NSTextField *)[self viewWithTag:6+textFieldtag];
		[[tempText cell] setTextColor:[NSColor redColor]];
		[[tempText cell] setTitle:(m_bolhg?(m_bzyck?@"出库数量:":@"融资数量:"):@"买入数量:")];
		
		
		//按钮
		NSMutableParagraphStyle * tempStyle = [[NSMutableParagraphStyle alloc]init] ;
		[tempStyle setAlignment:NSCenterTextAlignment];
		
		NSDictionary * attrsDictionary = [NSDictionary dictionaryWithObjectsAndKeys:[NSColor redColor],NSForegroundColorAttributeName,tempStyle,NSParagraphStyleAttributeName,nil];
		NSAttributedString * attrString = [[NSAttributedString alloc] initWithString:(m_bolhg?(m_bzyck?@"出库下单":@"融资下单"):@"买入下单") attributes:attrsDictionary];
		[tempStyle release];
		
		[doneButton setAttributedTitle:attrString];
		[attrString release];
	}
	else {
		tempText = (NSTextField *)[self viewWithTag:3+textFieldtag];
		[[tempText cell] setTextColor:[NSColor greenColor]];
		[[tempText cell] setTitle: (m_bolhg?(m_bzyrk?@"入库价格:":@"融券价格:"):@"卖出价格:")];
		
		
		//最大可买
		tempText = (NSTextField *)[self viewWithTag:5+textFieldtag];
		[[tempText cell] setTitle:(m_bolhg?(m_bzyrk?@"最大可入:":@"最大可融:"):@"最大可卖:")];
		
		//卖出数量
		tempText = (NSTextField *)[self viewWithTag:6+textFieldtag];
		[[tempText cell] setTextColor:[NSColor greenColor]];
		[[tempText cell] setTitle: (m_bolhg?(m_bzyrk?@"入库数量:":@"融券数量:"):@"卖出数量:")];
		
		NSMutableParagraphStyle * tempStyle = [[NSMutableParagraphStyle alloc]init] ;
		[tempStyle setAlignment:NSCenterTextAlignment];
		
		NSDictionary * attrsDictionary = [NSDictionary dictionaryWithObjectsAndKeys:[NSColor greenColor],NSForegroundColorAttributeName,tempStyle,NSParagraphStyleAttributeName,nil];
		NSAttributedString * attrString = [[NSAttributedString alloc] initWithString:(m_bolhg?(m_bzyrk?@"入库下单":@"融券下单"):@"卖出下单") attributes:attrsDictionary];
		[tempStyle release];
		
		[doneButton setAttributedTitle:attrString];
		[attrString release];
	}
    
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

#pragma mark   交易相关

-(void)cleanscreen
{
	m_nsjfsindex = 0;
    if(m_bsjwtflag)
    {
        [gppriceText setFrame:NSMakeRect(70, viewRect.size.height  - 4*PERROWHEIGHT-TOPMARIN_HEIGHT, 120, PERROWHEIGHT)];
        [priceStepper setFrame:NSMakeRect(190, viewRect.size.height  - 4*PERROWHEIGHT+2-TOPMARIN_HEIGHT, 20, PERROWHEIGHT-4)];
        NSTextField * tempTextField;
        tempTextField = [self viewWithTag:100];
        [[tempTextField cell] setTitle:@"元"];
        [xjwtLabel setFrame:NSZeroRect];
    }
	m_bsjwtflag = NO;
	[[bjfsCombobox cell]setTitle:@"限价委托"];
	[[gpcodeText cell] setTitle:@""];
	[[gpnameLabel cell] setTitle:@""];
	[[gppriceText cell] setTitle:@""];
	[[gpnumText cell] setTitle:@""];
	[[moneynumText cell] setTitle:@""];
	[[maxbuysellLabel cell] setTitle:@""];
	
	[lastzqdm release];
	lastzqdm=nil;
	[lastmaxzqdm release];
	lastmaxzqdm=nil;
	[lastprice release];
	lastprice=nil;
	[lastkyzj release];
	lastkyzj=nil;
	m_bolzq=NO;
	fztjg=0.0f;
	fdtjg=0.0f;
    
    
	
	if (pkShowArray != nil) {
		[pkShowArray removeAllObjects];
	}
	[myTableView reloadData];
}

-(void)QueryGpInfo
{
	if([[[gpcodeText cell] title] length]  == 6)
	{
		if(lastzqdm!=nil)
		{
			if([lastzqdm isEqualToString:[[gpcodeText cell] title]] )
				;//return;
		}
		[lastzqdm release];
		lastzqdm=[[NSString alloc]  initWithFormat:@"%@",[[gpcodeText cell] title]];
		[operProcessDelegate getHQProcess:lastzqdm gpSetcode:-1 typeID:MAC_ZST_FUNC pareOne:1 paraTwo:1];
		[eGetData sendTradeWTData:TDX_CXSC objIndex:self.tradeindex Session:eGetData.inputSave.sessionID gpCode:[[gpcodeText cell] title] gpPrice:0 gpNum:0 bsFlag:0];
	}
}

-(void)OnGpMaxBuySell
{
	if([[[gpcodeText cell] title] length]!=6)
 		return;
    int bsFlag=0;
    if(tag == 0)
    {
        bsFlag = 0;
        if(m_bsjwtflag==1)
            bsFlag='C';
    }
    else
    {
        bsFlag = 1;
        if(m_bsjwtflag==1)
            bsFlag='D';
    }

    
    int nwtfs=0;
    if(m_bsjwtflag)
    {
        if(m_setcode==SZ)
        {
            nwtfs=[[m_nszsjwtfsdm objectAtIndex:m_nsjfsindex] intValue];
        }
        else if(m_setcode==SH)
        {
            nwtfs=[[m_nshsjwtfsdm objectAtIndex:m_nsjfsindex] intValue];
        }
    }
	if(tag==0 || m_bolhg)//买入
	{
#ifdef IMAC_HXZQ
        if(m_bolhg)
        {
            if(tag==0)
                bsFlag=1;
            else
                bsFlag=0;
        }
        
        
#endif
        if(!m_bsjwtflag)
        {
            if([[[gppriceText cell] title] floatValue]<((m_xsflag==2)?0.008:0.0008))
            {
                [[maxbuysellLabel cell] setTitle:@"0"];
                return;
            }
        }
		
		if(lastmaxzqdm!=nil && lastprice!=nil && lastkyzj!=nil)
		{
			if([lastmaxzqdm isEqualToString:[[gpcodeText cell] title]] && [lastkyzj isEqualToString:[[moneynumText cell] title]] && [lastprice isEqualToString:[[gppriceText cell] title]] && lastbsflag==tag && nlastsjwtflag==m_bsjwtflag)
				return;
		}
        if (eGetData.clientinfos.m_bxyjyflag) {
            [self getMRMCFlag];
         
            [eGetData sendTradeWTData:TDX_KMMS objIndex:self.tradeindex Session:eGetData.inputSave.sessionID gpCode:[[gpcodeText cell] title] gpPrice:(m_bsjwtflag?@"1.000":[[gppriceText cell] title]) gpNum:nwtfs bsFlag:m_strMRMCFlag kyzj:[[[moneynumText cell] title] floatValue]];
            
        }
        else
        {
            [eGetData sendTradeWTData:TDX_KMMS objIndex:self.tradeindex Session:eGetData.inputSave.sessionID gpCode:[[gpcodeText cell] title] gpPrice:(m_bsjwtflag?@"1.000":[[gppriceText cell] title]) gpNum:nwtfs bsFlag:bsFlag kyzj:[[[moneynumText cell] title] floatValue]];
        }
	}
	else if(m_gdmx)//卖出
	{
		if(lastmaxzqdm!=nil)
		{
			if([lastmaxzqdm isEqualToString:[[gpcodeText cell] title]] && lastbsflag==tag)
				return;
		}
		[eGetData sendTradeQueryData:TDX_GFCX objIndex:self.tradeindex Session:eGetData.inputSave.sessionID];
	}
    else if(eGetData.tradeType == DBPHZ){//担保品划转查最大可划
    
            eGetData.inputSave.wtfs=@"7";
            m_strMRMCFlag = @"74";
          [eGetData sendTradeWTData:TDX_DBPHZ+1 objIndex:self.tradeindex Session:eGetData.inputSave.sessionID gpCode:[[gpcodeText cell] title] gpPrice:(m_bsjwtflag?@"1.000":[[gppriceText cell] title]) gpNum:1 bsFlag:m_strMRMCFlag kyzj:[[[moneynumText cell] title] floatValue]];
    }
	else
		[[maxbuysellLabel cell] setTitle:@"0"];
	
    nlastsjwtflag=m_bsjwtflag;
	[lastmaxzqdm release];
	lastmaxzqdm=[[NSString alloc]  initWithFormat:@"%@",[[gpcodeText cell] title]];
	
	[lastprice release];
	lastprice=[[NSString alloc]  initWithFormat:@"%@",[[gppriceText cell] title]];
	
	[lastkyzj release];
	lastkyzj=[[NSString alloc]  initWithFormat:@"%@",[[moneynumText cell] title]];
	
	lastbsflag=tag;
	
	if (showType == 0) {
		[[self window] makeFirstResponder:gpnumText];
	}
}

-(void) getMRMCFlag
{
    
    if (eGetData.tradeType ==0) {
         m_strMRMCFlag = 0;
    }
    else if (eGetData.tradeType ==1){
         m_strMRMCFlag = 1;
    }
    else if (eGetData.tradeType ==2){
        m_strMRMCFlag = 69;
    }
    else if (eGetData.tradeType ==3){
         m_strMRMCFlag = 70;
    }
    else if (eGetData.tradeType == MQHK){
        m_strMRMCFlag = 76;
    }
}




-(void)doBuySell
{
	//NSLog(@"lenx14");
	if([[[gpcodeText cell] title] length] == 0)
	{
		NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
										 defaultButton: @"确定"
									   alternateButton: nil
										   otherButton: nil
							 informativeTextWithFormat: @"请输入股票代码"];
		[alert setDelegate:self];
		NSInteger result = [alert runModal];
		[self handleResult:alert withResult:result withTag:1];	
		return;
	}
	else if(([[[gpcodeText cell] title] length] > 0) &&([[[gpcodeText cell] title] length] < 5))
	{
		NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
										 defaultButton: @"确定"
									   alternateButton: nil
										   otherButton: nil
							 informativeTextWithFormat: @"输入完整的股票代码"];
		[alert setDelegate:self];
		NSInteger result = [alert runModal];
		[self handleResult:alert withResult:result withTag:1];	
		return;
	}
	else if(m_nsjfsindex<0 || (m_setcode==SZ && m_nsjfsindex>=[m_szsjwtfsmc count]) || (m_setcode==SH && m_nsjfsindex>=[m_shsjwtfsmc count]))
	{
		NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
										 defaultButton: @"确定"
									   alternateButton: nil
										   otherButton: nil
							 informativeTextWithFormat: @"请选择报价方式"];
		[alert setDelegate:self];
		NSInteger result = [alert runModal];
		[self handleResult:alert withResult:result withTag:1];	
		
		return;
	}
	else if(!m_bsjwtflag && ([[[gppriceText cell] title] length] == 0 || [[[gppriceText cell] title] floatValue]<=0.0001f)){
		NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
										 defaultButton: @"确定"
									   alternateButton: nil
										   otherButton: nil
							 informativeTextWithFormat: @"请输入委托价格"];
		[alert setDelegate:self];
		NSInteger result = [alert runModal];
		[self handleResult:alert withResult:result withTag:2];	
		return;
	}
	else if([[[gpnumText cell] title] length] == 0 || [[[gpnumText cell] title] longLongValue]==0){
		NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
										 defaultButton: @"确定"
									   alternateButton: nil
										   otherButton: nil
							 informativeTextWithFormat: @"请输入委托数量"];
		[alert setDelegate:self];
		NSInteger result = [alert runModal];
		[self handleResult:alert withResult:result withTag:3];			
		return;
	}
	else{
		NSString * tempString;
        if (!m_gdmx){
            NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
                                             defaultButton: @"确定"
                                           alternateButton: nil
                                               otherButton: nil
                                 informativeTextWithFormat: @"请选择对应的股东!"];
            [alert setDelegate:self];
            NSInteger result = [alert runModal];
            [self handleResult:alert withResult:result withTag:1];
        }
        else{
            [[gddmCombobox cell] setTitle:[m_gdmx GetGdDescribe]];
			NSString *errtip=@"",*errtip1=@"",*errtip2=@"",*tmpokstr=@"买入确认",*tmptitlestr=@"买入交易确认",*stroper=@"买入";
			float fprice=[[[gppriceText cell] title] floatValue];
			long long  jyvol=[[[gpnumText cell] title] longLongValue];
			long long maxvol=[[[maxbuysellLabel cell] title] longLongValue];
			if(tag == 0)
			{
				if(m_bolhg)
				{
					if(m_bzyck)
					{
						stroper=@"出库";
						tmptitlestr=@"出库交易确认";
						tmpokstr=@"出库确认";
						
						if(jyvol>maxvol)
							errtip1=@"出库数量大于最大可出,";
					}
					else 
					{
						stroper=@"融资";
						tmptitlestr=@"融资交易确认";
						tmpokstr=@"融资确认";
						
						if(!m_bsjwtflag)
						{
							if(fprice>fztjg)
								errtip=@"融资价格高于涨停价,";
							else if(fprice<fdtjg)
								errtip=@"融资价格低于跌停价,";
						}
						
						if(jyvol>maxvol)
							errtip1=@"融资数量大于最大可融,";
					}
				}
				else 
				{
					if(!m_bsjwtflag)
					{
						if(fprice>fztjg)
							errtip=@"买入价格高于涨停价,";
						else if(fprice<fdtjg)
							errtip=@"买入价格低于跌停价,";
					}
					
					if(jyvol>maxvol)
						errtip1=@"买入数量大于最大可买,";
				}
			}
			else
			{
				if(m_bolhg)
				{
					if(m_bzyrk)
					{
						stroper=@"入库";
						tmptitlestr=@"入库交易确认";
						tmpokstr=@"入库确认";
						if(jyvol>maxvol)
							errtip1=@"入库数量大于最大可入,";
					}
					else 
					{
						stroper=@"融券";
						tmptitlestr=@"融券交易确认";
						tmpokstr=@"融券确认";
						
						if(!m_bsjwtflag)
						{
							if(fprice>fztjg)
								errtip=@"融券价格高于涨停价,";
							else if(fprice<fdtjg)
								errtip=@"融券价格低于跌停价,";
						}
						if(jyvol>maxvol)
							errtip1=@"融券数量大于最大可融,";
					}
				}
				else 
				{
					stroper=@"卖出";
					tmptitlestr=@"卖出交易确认";
					tmpokstr=@"卖出确认";
					
					if(!m_bsjwtflag)
					{
						if(fprice>fztjg)
							errtip=@"卖出价格高于涨停价,";
						else if(fprice<fdtjg)
							errtip=@"卖出价格低于跌停价,";
					}
					
					if(jyvol>maxvol)
						errtip1=@"卖出数量大于最大可卖,";
				}
			}
            if (eGetData.clientinfos.m_bxyjyflag)
            {
                switch (eGetData.tradeType) {
                    case DBPBuy:
                        stroper=@"担保品买入";
                        break;
                    case DBPSell:
                        stroper=@"担保品卖出";
                        break;
                    case RZBuy:
                        stroper=@"融资买入";
                        break;
                    case MQHK:
                        stroper=@"卖券还款";
                        break;
                    case MQHQ:
                        stroper=@"买券还券";
                        break;
                    case XJHK:
                        stroper=@"现金还款";
                        break;
                    case XQHQ:
                        stroper=@"现券还券";
                        break;
                    case RZSell:
                        stroper=@"融券卖出";
                        break;
                    case DBPHZ:
                        stroper=@"担保品划转";
                        break;
                    default:
                        break;
                }
            }
            
			m_bfirstalertflag=YES;
			if([errtip length] || [errtip1 length])
				errtip2=[NSString stringWithFormat:@"%@%@交易可能不会成功!",errtip,errtip1];
			if(m_bsjwtflag)
			{
				NSString *strsjfs=@"";
				if(m_setcode==SZ)
					strsjfs=[NSString stringWithFormat:@"%@",[m_szsjwtfsmc objectAtIndex:m_nsjfsindex]];
				else if(m_setcode==SH)
					strsjfs=[NSString stringWithFormat:@"%@",[m_shsjwtfsmc objectAtIndex:m_nsjfsindex]];
				tempString = [NSString stringWithFormat:@"请确认以下信息:\r\r操作类别:   %@\r股票代码:   %@ %@\r报价方式:   %@\r委托数量:   %@%@\r股东代码:   %@\r\r(如果股东代码有误，请选择正确的股东代码.)\r\r%@\r\r\r\r",stroper,[[gpcodeText cell] title],[[gpnameLabel cell] title],strsjfs,[[gpnumText cell] title],(m_bolzq?((m_ngzdw==2)?@"张":@"手"):@"股"),[m_gdmx GetGdDescribe],errtip2];
			}
            else if (eGetData.tradeType == DBPHZ)
            {
                tempString = [NSString stringWithFormat:@"请确认以下信息:\r\r操作类别:   %@\r股票代码:   %@ %@\r委托数量:   %@%@\r股东代码:   %@\r\r(如果股东代码有误，请选择正确的股东代码.)\r\r%@\r\r\r\r",stroper,[[gpcodeText cell] title],[[gpnameLabel cell] title],[[gpnumText cell] title],(m_bolzq?((m_ngzdw==2)?@"张":@"手"):@"股"),eGetData.inputSave.gddm,errtip2];
            }
			else
				tempString = [NSString stringWithFormat:@"请确认以下信息:\r\r操作类别:   %@\r股票代码:   %@ %@\r报价方式:   限价委托\r委托价格:   %@\r委托数量:   %@%@\r股东代码:   %@\r\r(如果股东代码有误，请选择正确的股东代码.)\r\r%@\r\r\r\r",stroper,[[gpcodeText cell] title],[[gpnameLabel cell] title],[[gppriceText cell] title],[[gpnumText cell] title],(m_bolzq?((m_ngzdw==2)?@"张":@"手"):@"股"),[m_gdmx GetGdDescribe],errtip2];
			
			NSAlert* alert = [NSAlert alertWithMessageText:@"交易确认"
											 defaultButton: @"确定"
										   alternateButton: @"取消"
											   otherButton: nil
								 informativeTextWithFormat: @"%@",tempString];
			[alert setDelegate:self];
			NSInteger result = [alert runModal];
			[self handleResult:alert withResult:result withTag:0];	
			return;
		}
    }
}

-(void)xjhkdoBuySell
{
    if([[[xjhkpriceText cell] title] floatValue] <= 0.001)
    {
        NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
                                         defaultButton: @"确定"
                                       alternateButton: nil
                                           otherButton: nil
                             informativeTextWithFormat: @"请输入正确的还款金额"];
        [alert setDelegate:self];
        NSInteger result = [alert runModal];
        [self handleResult:alert withResult:result withTag:1];	
        return;
    }
    
    NSString* tempString = [NSString stringWithFormat:@"请确认以下信息:\r\r操作类别:   %@\r还款金额:   %@ %@",@"现金还款",[[xjhkpriceText cell] title], @"元"];
    
    NSAlert* alert = [NSAlert alertWithMessageText:@"交易确认"
                                     defaultButton: @"确定"
                                   alternateButton: @"取消"
                                       otherButton: nil
                         informativeTextWithFormat: @"%@",tempString];
    [alert setDelegate:self];
    NSInteger result = [alert runModal];
    [self handleResult:alert withResult:result withTag:0];	
    return;
}

-(void)doBuySell2
{
	int bsFlag=0;
	if(tag == 0)
	{
		bsFlag = 0;
		if(m_bsjwtflag==1)
			bsFlag='C';
	}
	else
	{
		bsFlag = 1;
		if(m_bsjwtflag==1)
			bsFlag='D';
	}
	int nwtfs=0;
	if(m_bsjwtflag)
	{
		if(m_setcode==SZ)
		{
			nwtfs=[[m_nszsjwtfsdm objectAtIndex:m_nsjfsindex] intValue];
		}
		else if(m_setcode==SH)
		{
			nwtfs=[[m_nshsjwtfsdm objectAtIndex:m_nsjfsindex] intValue];
		}
	}
	eGetData.inputSave.gddm=[NSString stringWithFormat:@"%@",m_gdmx.gddm];
	eGetData.inputSave.accoutType=m_gdmx.wttype;
	
	[operZXGDelegate addStock:[[gpcodeText cell] title] setcode:m_setcode];
    if (eGetData.clientinfos.m_bxyjyflag) {
        
        if (eGetData.tradeType==DBPHZ) {
             [eGetData sendTradeWTData:TDX_DBPHZ objIndex:self.tradeindex Session:eGetData.inputSave.sessionID gpCode:[[gpcodeText cell] title] gpPrice:((m_bzyck || m_bzyrk || m_bsjwtflag)?@"1.000":[[gppriceText cell] title] ) gpNum:([[[gpnumText cell] title] intValue]*((m_ngzdw==1)?10:1)) bsFlag:m_strMRMCFlag zqflag:(m_bolzq || m_bolhg) wtfs:m_nsjfsindex];
        }else{
            [self getMRMCFlag];
            [eGetData sendTradeWTData:TDX_WTJY objIndex:self.tradeindex Session:eGetData.inputSave.sessionID gpCode:[[gpcodeText cell] title] gpPrice:((m_bzyck || m_bzyrk || m_bsjwtflag)?@"1.000":[[gppriceText cell] title] ) gpNum:([[[gpnumText cell] title] intValue]*((m_ngzdw==1)?10:1)) bsFlag:m_strMRMCFlag zqflag:(m_bolzq || m_bolhg) wtfs:m_nsjfsindex];
        }
    }
    else
    {
        [eGetData sendTradeWTData:TDX_WTJY objIndex:self.tradeindex Session:eGetData.inputSave.sessionID gpCode:[[gpcodeText cell] title] gpPrice:((m_bzyck || m_bzyrk || m_bsjwtflag)?@"1.000":[[gppriceText cell] title] ) gpNum:([[[gpnumText cell] title] intValue]*((m_ngzdw==1)?10:1)) bsFlag:bsFlag zqflag:(m_bolzq || m_bolhg) wtfs:nwtfs];
    }
 
}

-(void)xjhkdoBuySell2
{
    [eGetData sendTradeWTData:TDX_XYXJHKCX+1 objIndex:self.tradeindex Session:eGetData.inputSave.sessionID gpCode:@"" gpPrice:[[xjhkpriceText cell] title] gpNum:0 bsFlag:0 zqflag:0 wtfs:0];
}

-(void)dealPKArray:(ParseRecv*)pParsers{
	if (pkShowArray != nil) {
		[pkShowArray removeAllObjects];
		[pkShowArray release],pkShowArray=nil;
	}
	pkShowArray = [[NSMutableArray alloc] init];
	NSDictionary * tempDict;
	tempDict = [NSDictionary dictionaryWithObjectsAndKeys:[pkTitleArray objectAtIndex:0],@"name",[pParsers getFieldData:0 fieldFlag:TDX_ID_HQ_MCJS5],@"price",[pParsers getFieldData:0 fieldFlag:TDX_ID_HQ_MCSL5],@"vol",nil];
	[pkShowArray addObject:tempDict];
	tempDict = [NSDictionary dictionaryWithObjectsAndKeys:[pkTitleArray objectAtIndex:1],@"name",[pParsers getFieldData:0 fieldFlag:TDX_ID_HQ_MCJS4],@"price",[pParsers getFieldData:0 fieldFlag:TDX_ID_HQ_MCSL4],@"vol",nil];
	[pkShowArray addObject:tempDict];
	tempDict = [NSDictionary dictionaryWithObjectsAndKeys:[pkTitleArray objectAtIndex:2],@"name",[pParsers getFieldData:0 fieldFlag:TDX_ID_HQ_MCJS3],@"price",[pParsers getFieldData:0 fieldFlag:TDX_ID_HQ_MCSL3],@"vol",nil];
	[pkShowArray addObject:tempDict];
	tempDict = [NSDictionary dictionaryWithObjectsAndKeys:[pkTitleArray objectAtIndex:3],@"name",[pParsers getFieldData:0 fieldFlag:TDX_ID_HQ_MCJS2],@"price",[pParsers getFieldData:0 fieldFlag:TDX_ID_HQ_MCSL2],@"vol",nil];
	[pkShowArray addObject:tempDict];
	tempDict = [NSDictionary dictionaryWithObjectsAndKeys:[pkTitleArray objectAtIndex:4],@"name",[pParsers getFieldData:0 fieldFlag:TDX_ID_HQ_MCJS1],@"price",[pParsers getFieldData:0 fieldFlag:TDX_ID_HQ_MCSL1],@"vol",nil];
	[pkShowArray addObject:tempDict];

	
	tempDict = [NSDictionary dictionaryWithObjectsAndKeys:[pkTitleArray objectAtIndex:5],@"name",[pParsers getFieldData:0 fieldFlag:TDX_ID_HQ_MRLG1],@"price",[pParsers getFieldData:0 fieldFlag:TDX_ID_HQ_MRSL1],@"vol",nil];
	[pkShowArray addObject:tempDict];
	tempDict = [NSDictionary dictionaryWithObjectsAndKeys:[pkTitleArray objectAtIndex:6],@"name",[pParsers getFieldData:0 fieldFlag:TDX_ID_HQ_MRLG2],@"price",[pParsers getFieldData:0 fieldFlag:TDX_ID_HQ_MRSL2],@"vol",nil];
	[pkShowArray addObject:tempDict];
	tempDict = [NSDictionary dictionaryWithObjectsAndKeys:[pkTitleArray objectAtIndex:7],@"name",[pParsers getFieldData:0 fieldFlag:TDX_ID_HQ_MRLG3],@"price",[pParsers getFieldData:0 fieldFlag:TDX_ID_HQ_MRSL3],@"vol",nil];
	[pkShowArray addObject:tempDict];
	tempDict = [NSDictionary dictionaryWithObjectsAndKeys:[pkTitleArray objectAtIndex:8],@"name",[pParsers getFieldData:0 fieldFlag:TDX_ID_HQ_MRLG4],@"price",[pParsers getFieldData:0 fieldFlag:TDX_ID_HQ_MRSL4],@"vol",nil];
	[pkShowArray addObject:tempDict];
	tempDict = [NSDictionary dictionaryWithObjectsAndKeys:[pkTitleArray objectAtIndex:9],@"name",[pParsers getFieldData:0 fieldFlag:TDX_ID_HQ_MRLG5],@"price",[pParsers getFieldData:0 fieldFlag:TDX_ID_HQ_MRSL5],@"vol",nil];
	[pkShowArray addObject:tempDict];
	
}


-(void)refreshHqData{
	m_brefreshflag = YES;
	if ([[[gpcodeText cell] title] length] == 6) {
		if (!eGetData.g_TradeComm.breloginflag) {
			[eGetData sendTradeWTData:TDX_CXHQ objIndex:self.tradeindex Session:eGetData.inputSave.sessionID gpCode:[[gpcodeText cell] title] gpPrice:0 gpNum:0 bsFlag:0];
		}
	}
}

-(void)getXJHKData
{
    if (!eGetData.g_TradeComm.breloginflag)
    {
        [eGetData sendTradeWTData:TDX_XYXJHKCX objIndex:self.tradeindex Session:eGetData.inputSave.sessionID gpCode:@"" gpPrice:0 gpNum:0 bsFlag:0];
    }
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
		case TDX_ZQXX:
		{
			if(!baddflag)
				break;
			if([pParsers IsTimeOut])
				break;
			if(pParsers.bsucflag)
			{
                m_bOnlyRunOne = YES;
				[[gpnameLabel cell] setTitle:[pParsers getFieldData:0 fieldFlag:TDX_ID_ZQMC]];
				NSString *strkyzj=[pParsers getFieldData:0 fieldFlag:TDX_ID_KYZJ];
                if([strkyzj length])
                    [[moneynumText cell] setTitle:strkyzj];
                else
                    [[moneynumText cell] setTitle:@"0.00"];
			}
			if(bsdmmflag || m_bzyck || m_bzyrk)
			{
				bsdmmflag=NO;
				if(m_bzyck || m_bzyrk)
					[[gppriceText cell] setTitle:@"1.000"];
				else if(m_xsflag==2)
					[[gppriceText cell] setTitle:[NSString stringWithFormat:@"%.2f",wtPrice]];
				else 
					[[gppriceText cell] setTitle:[NSString stringWithFormat:@"%.3f",wtPrice]];
				[[self window] makeFirstResponder:gppriceText];

				
				[self OnGpMaxBuySell];
				break;
			}
			[eGetData sendTradeWTData:TDX_CXHQ objIndex:self.tradeindex Session:eGetData.inputSave.sessionID gpCode:[[gpcodeText cell] title] gpPrice:0 gpNum:0 bsFlag:0];
		}
			break;
		case TDX_CXHQ:
		{
			if(!baddflag)
				break;
			if(pParsers.bsucflag)
			{
				if ([[[gppriceText cell] title] length] > 0) {
					;
				}
				else {
					if(tag == 0)
						[[gppriceText cell] setTitle:[pParsers getFieldData:0 fieldFlag:TDX_ID_HQ_MCJS1]];
					else
						[[gppriceText cell] setTitle:[pParsers getFieldData:0 fieldFlag:TDX_ID_HQ_MRLG1]];
					
                    if([[[gppriceText cell] title] floatValue]<0.01)
                    {
                        if(tag == 0)
                            [[gppriceText cell] setTitle:[pParsers getFieldData:0 fieldFlag:TDX_ID_HQ_MRLG1]];
                        else
                            [[gppriceText cell] setTitle:[pParsers getFieldData:0 fieldFlag:TDX_ID_HQ_MCJS1]];
                    }
                    if([[[gppriceText cell] title] floatValue]<0.01)
                        [[gppriceText cell] setTitle:[pParsers getFieldData:0 fieldFlag:TDX_ID_NOW]];
                    if([[[gppriceText cell] title] floatValue]<0.01)
                        [[gppriceText cell] setTitle:[pParsers getFieldData:0 fieldFlag:TDX_ID_HQ_CLOSE]];
				}
				

				float fclose=[[pParsers getFieldData:0 fieldFlag:TDX_ID_HQ_CLOSE] floatValue];
				if (showType > 0) {
					currClose =fclose;
					[self dealPKArray:pParsers];
					[self setNeedsDisplay:YES];
					[myTableView reloadData];
				}
				
				fztjg= [eGetData GetTPPrice:[[[gpnameLabel cell] title] UTF8String] zqdm:[[[gpcodeText cell] title] UTF8String] scflag:m_setcode withclose:fclose withzdflag:YES withxsflag:m_xsflag];
				fdtjg=[eGetData GetTPPrice:[[[gpnameLabel cell] title] UTF8String] zqdm:[[[gpcodeText cell] title] UTF8String] scflag:m_setcode withclose:fclose withzdflag:NO withxsflag:m_xsflag];
				
				if (!m_brefreshflag) {
					[[self window] makeFirstResponder:gppriceText];
					[self OnGpMaxBuySell];
				}
				else {
//                    if(eGetData.tradeType == DBPBuy)
//                    {
//                        [self OnGpMaxBuySell];
//                    }
				}
                
                if(m_bOnlyRunOne)
                {
                    if(eGetData.tradeType == DBPBuy)
                    {
                        [self OnGpMaxBuySell];
                    }
                    m_bOnlyRunOne = NO;
                }

				
			}
		}
			break;
		case TDX_CXSC:
		{
			if(!baddflag)
				break;
			if([pParsers IsTimeOut])
				break;
			int _setcode=m_setcode;
			if(pParsers.bsucflag)
				m_setcode=[[pParsers getFieldData:0 fieldFlag:TDX_ID_SCFLAG] intValue];
			else 
				m_setcode=-1;
			ScStrucInfo *pscinfo=[eGetData.clientinfos GetScStructInfo:[[[gpcodeText cell] title] UTF8String] setcode:m_setcode];
			m_bolhg=NO;
			if(pscinfo)
			{
				m_xsflag=pscinfo.nxsflag;
				m_setcode=pscinfo.setcode;
				m_bolzq=(pscinfo.ngzbz>=0);
				if(pscinfo.ngzbz==3)
					m_bolhg=YES;
				else 
					m_bolhg=NO;
			}
			if(m_bsjwtflag && _setcode!=m_setcode)
			{
				m_nsjfsindex=1;
				if(m_setcode==SZ)
					[[bjfsCombobox cell] setTitle:[NSString stringWithFormat:@"%@",[m_szsjwtfsmc objectAtIndex:1]]];
				else if(m_setcode==SH)
					[[bjfsCombobox cell] setTitle:[NSString stringWithFormat:@"%@",[m_shsjwtfsmc objectAtIndex:1]]];
				[bjfsCombobox reloadData];
			}
			if(m_setcode==SH && [eGetData.clientinfos.tradeccf IsZyckgpdm:[[gpcodeText cell]title]])
			{
				if(self.tag ==0 ||self.tag ==2)
				{
					m_bzyck=YES;
					m_bzyrk=NO;
				}
				else 
				{
					m_bzyrk=YES;
					m_bzyck=NO;
				}
			}
			else 
			{
				m_bzyck=NO;
				m_bzyrk=NO;
			}
			if(m_bzyck || m_bzyrk)
				m_bolhg=YES;
			m_ngzdw=0;
			if(m_bolzq || m_bzyck || m_bzyrk)
			{
				if(m_setcode==SZ)
				{
					if(eGetData.clientinfos.tradeccf.nszgzdw==0)
						m_ngzdw=2;
					else 
						m_ngzdw=1;
				}
				if(m_setcode==SH)
				{
					if(eGetData.clientinfos.tradeccf.nshgzdw==0)
						m_ngzdw=2;
					else 
						m_ngzdw=1;
				}
			}
            [self dealTitleS];
			if(m_ngzdw==0)
			{
                [[gpnumdwLabel cell] setTitle:@"股"];
                [[gpnumdwLabel2 cell] setTitle:@"股"];
            }
			else if(m_ngzdw==1)
			{
                [[gpnumdwLabel cell] setTitle:@"手"];
                [[gpnumdwLabel2 cell] setTitle:@"手"];
            }
			else
            {
                [[gpnumdwLabel cell] setTitle:@"张"];
                [[gpnumdwLabel2 cell] setTitle:@"张"];
            }
            if (eGetData.clientinfos.m_bxyjyflag&&eGetData.tradeType!=DBPHZ) {
                m_gdmx=[eGetData.clientinfos  AutoChangeGddm:m_gdmx withzqdm:[[[gpcodeText cell]title] UTF8String] withxyflag:NO withsetcode:m_setcode];
            }else{
                m_gdmx=[eGetData.clientinfos  AutoChangeGddm:m_gdmx withzqdm:[[[gpcodeText cell]title] UTF8String] withxyflag:NO withsetcode:m_setcode];
            }
		
			NSString * tempString = [m_gdmx GetGdDescribe];
			if ([tempString length] > 0) {
				[[gddmCombobox cell] setTitle:tempString];
			}
			
			eGetData.inputSave.accoutType=m_gdmx.wttype;
			eGetData.inputSave.gddm=[NSString stringWithFormat:@"%@",m_gdmx.gddm];
    
            [eGetData sendTradeWTData:TDX_ZQXX objIndex:self.tradeindex Session:eGetData.inputSave.sessionID gpCode:[[gpcodeText cell] title] gpPrice:0 gpNum:0 bsFlag:tag];
         
		}
			break;
		case TDX_KMMS:
		{
			if(!baddflag)
				break;
			if([pParsers IsTimeOut])
				break;
            if(pParsers.bsucflag){
            
				[[maxbuysellLabel cell] setTitle:[pParsers getFieldData:0 fieldFlag:TDX_ID_KMSL]];
            }
			if([[[maxbuysellLabel cell] title] length]==0)
				[[maxbuysellLabel cell] setTitle:@"0"];
            
            if(eGetData.tradeType == DBPBuy)
            {
                [[maxbuysellLabel cell] setTitle:[pParsers getFieldData:0 fieldFlag:TDX_ID_KMSL]];
            }
		}
			break;
		case TDX_GFCX:
		{
			if(!baddflag)
				break;
			if([pParsers IsTimeOut])
				break;
			NSString *strgfgddm=[eGetData GetGfGddm:pParsers zqdm:[[gpcodeText cell]title]] ;
            if([strgfgddm length] && [m_gdmx.gddm isEqualToString:strgfgddm]==NO)
            {
                GdmxInfo *ptmpgd=[eGetData.clientinfos.gdinfos GetGddm:strgfgddm];
                if(ptmpgd)
                {
                    m_gdmx=ptmpgd;
                    NSString * tempString = [m_gdmx GetGdDescribe];
                    if ([tempString length] > 0) {
                        [[gddmCombobox cell] setTitle:tempString];
                    }
                }
            }
            
            NSString *maxNum = [[maxbuysellLabel cell] title];
            if([maxNum isEqualToString:@""]
               || [maxNum intValue] == 0)
            {
                [[maxbuysellLabel cell] setTitle:[eGetData GetKmsl:pParsers zqdm:[[gpcodeText cell]title] gddm:m_gdmx.gddm xwdm:m_gdmx.xwdm zjzh:m_gdmx.zjzh]];
            }
		}
			break;
        case TDX_DBPHZ:
		case TDX_WTJY:
		{
			if(pParsers.bsucflag){
				NSString * tempString =[pParsers getFieldData:0 fieldFlag:TDX_ID_RETINFO];
				if([tempString length]==0)
				{
					if(eGetData.clientinfos.m_nQsbs==ZSZQ_DLL)
						tempString=[NSString stringWithFormat:@"您的申请已提交,合同号是%@",[pParsers getFieldData:0 fieldFlag:TDX_ID_WTBH]];
					else 
						tempString=[NSString stringWithFormat:@"委托已提交,合同号是%@",[pParsers getFieldData:0 fieldFlag:TDX_ID_WTBH]];
				}
				m_bfirstalertflag=YES;
				
				NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
												 defaultButton: @"确定"
											   alternateButton: nil
												   otherButton: nil
									 informativeTextWithFormat: @"%@",tempString];
				[alert setDelegate:self];
				NSInteger result = [alert runModal];
				[self handleResult:alert withResult:result withTag:4];
				[self cleanscreen];
                if(tag==1)
                    [self.bDelegates OnWtSuccess];
				if(bpopupflag)
					btradesucflag=YES;
				
			}else  if(pParsers.btipflag){//处理委托失败的报错
				NSString *  tempString = @"";
				if(eGetData.clientinfos.m_nQsbs==ZSZQ_DLL)
					tempString=[NSString stringWithFormat:@"您的申请处理失败,原因是:\r%@",pParsers.psErrorData];
				else if(eGetData.clientinfos.m_nQsbs==GJZQ_DLL)
					tempString=[NSString stringWithFormat:@"委托失败,证券系统返回的原因:\r%@",pParsers.psErrorData];
				else 
					tempString=[NSString stringWithFormat:@"委托已提交,证券系统返回的原因:\r%@",pParsers.psErrorData];
				m_bfirstalertflag=YES;

				NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
												 defaultButton: @"确定"
											   alternateButton: nil
												   otherButton: nil
									 informativeTextWithFormat: @"%@",tempString];
				[alert setDelegate:self];
				NSInteger result = [alert runModal];
				[self handleResult:alert withResult:result withTag:4];	
				
			}
			[self stopanimate];
		}
			break;
               case TDX_DBPHZ+1:
            if(pParsers.bsucflag)
             [[maxbuysellLabel cell] setTitle:[pParsers getFieldData:0 fieldFlag:TDX_ID_KMSL]];
            break;
        case TDX_XYXJHKCX:
        {
            if(!baddflag)
                break;
            if([pParsers IsTimeOut])
                break;
            if(pParsers.bsucflag)
            {
                [[kyjeLabel cell] setTitle:[pParsers getFieldData:0 fieldFlag:TDX_ID_KYZJ]];
                [[xhkeLabel cell] setTitle:[pParsers getFieldData:0 fieldFlag:TDX_ID_KMSL]];
            }
            break;
        }
        case TDX_XYXJHKCX+1:
        {
            if(pParsers.bsucflag){
                NSString * tempString =[pParsers getFieldData:0 fieldFlag:TDX_ID_RETINFO];
                if([tempString length]==0)
                {
                    tempString=[NSString stringWithFormat:@"委托已提交,合同号是%@",[pParsers getFieldData:0 fieldFlag:TDX_ID_WTBH]];
                }
                
                NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
                                                 defaultButton: @"确定"
                                               alternateButton: nil
                                                   otherButton: nil
                                     informativeTextWithFormat: @"%@",tempString];
                [alert setDelegate:self];
                NSInteger result = [alert runModal];
                [self handleResult:alert withResult:result withTag:4];
            }else  if(pParsers.btipflag){//处理委托失败的报错
                NSString *  tempString = @"";
                if(eGetData.clientinfos.m_nQsbs==ZSZQ_DLL)
                    tempString=[NSString stringWithFormat:@"您的申请处理失败,原因是:\r%@",pParsers.psErrorData];
                else if(eGetData.clientinfos.m_nQsbs==GJZQ_DLL)
                    tempString=[NSString stringWithFormat:@"委托失败,证券系统返回的原因:\r%@",pParsers.psErrorData];
                else
                    tempString=[NSString stringWithFormat:@"委托已提交,证券系统返回的原因:\r%@",pParsers.psErrorData];
                
                NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
                                                 defaultButton: @"确定"
                                               alternateButton: nil
                                                   otherButton: nil
                                     informativeTextWithFormat: @"%@",tempString];
                [alert setDelegate:self];
                NSInteger result = [alert runModal];
                [self handleResult:alert withResult:result withTag:4];	
                
            }
            [self stopanimate];
            break;
        }
		default:
			break;
	}
	return YES;
}


-(void)SetGpnum:(float)frate
{

}
#pragma mark combobox Delegate相关
-(NSInteger) numberOfItemsInComboBox:(NSComboBox *)aComboBox{
    if (aComboBox.tag == GDDM_COM_FLAG) {
		return [eGetData.clientinfos.gdinfos.gddms count];

	}
	
	else if(aComboBox.tag == BJFS_COM_FLAG){
		
		if(m_setcode==SZ)
			return [m_szsjwtfsmc count];
		else if(m_setcode==SH)
			return [m_shsjwtfsmc count];
	}
    else if (aComboBox == HZFXCombobox){
        return 2;
    }
	
	return 0;
}

-(id) comboBox:(NSComboBox *)aComboBox objectValueForItemAtIndex:(NSInteger)index{
	if (aComboBox.tag == GDDM_COM_FLAG) {
		GdmxInfo *tmpgdmx=[eGetData.clientinfos.gdinfos.gddms objectAtIndex:index];
		return [tmpgdmx GetGdDescribe];
	}
	else if (aComboBox.tag == BJFS_COM_FLAG){
		if(m_setcode==SZ)
			return [m_szsjwtfsmc objectAtIndex:index];
		else if(m_setcode==SH)
			return [m_shsjwtfsmc objectAtIndex:index];
	}
    else if (aComboBox == HZFXCombobox){
        return [HZFXArray objectAtIndex:index];
    }
    else if(aComboBox == BZCombobox)
    {
        return [BZArray objectAtIndex:index];
    }
	return nil;
}

-(void) comboBoxSelectionDidChange:(NSNotification *)notification{
	NSComboBox * tempCombobox = [notification object];
	//NSLog(@"%@",[[tempText cell] title]);
	
	if ([tempCombobox tag] == GDDM_COM_FLAG) {
		//NSLog(@"123");indexOfSelectedItem
		int tempInt = [tempCombobox indexOfSelectedItem];
		if(tempInt>=0 && eGetData.clientinfos.gdinfos.m_gdcount>tempInt)
		{
			GdmxInfo *pgdmx=[eGetData.clientinfos.gdinfos.gddms objectAtIndex:tempInt];
			if(pgdmx)
			{
				ngdIndex=tempInt;
				m_gdmx=pgdmx;
				eGetData.inputSave.gddm=[NSString stringWithFormat:@"%@",m_gdmx.gddm];
				eGetData.inputSave.accoutType=m_gdmx.wttype;
			}
			else 
				[[gddmCombobox cell] setTitle:@""];
		}
		else 
			[[gddmCombobox cell] setTitle:@""];
	}
	else if([tempCombobox tag] == BJFS_COM_FLAG) {
		
		
		int tempInt = [tempCombobox indexOfSelectedItem];
		m_nsjfsindex=tempInt;
		
		if(tempInt>0)
			m_bsjwtflag=YES;
		else 
			m_bsjwtflag=NO;
		
		NSTextField * tempTextField;
		tempTextField = [self viewWithTag:100];
		if (tempInt == 0) {
			[gppriceText setFrame:NSMakeRect(70, viewRect.size.height  - 4*PERROWHEIGHT-TOPMARIN_HEIGHT, 120, PERROWHEIGHT)];
			[priceStepper setFrame:NSMakeRect(190, viewRect.size.height  - 4*PERROWHEIGHT+2-TOPMARIN_HEIGHT, 20, PERROWHEIGHT-4)];
			[[tempTextField cell] setTitle:@"元"];
			[xjwtLabel setFrame:NSZeroRect];
		}
		else {
			[gppriceText setFrame:NSZeroRect];
			[priceStepper setFrame:NSZeroRect];
			[[tempTextField cell] setTitle:@""];
			[xjwtLabel setFrame:NSMakeRect(70, viewRect.size.height  - 4*PERROWHEIGHT+2-TOPMARIN_HEIGHT, 140, PERROWHEIGHT-4)];
		}
        [self OnGpMaxBuySell];
	}
    else if (tempCombobox == HZFXCombobox){
        int tempInt = [tempCombobox indexOfSelectedItem];
        eGetData.HZFX = tempInt;
        [self cleanscreen];
        [self HZFXChange];
    
    }
	
}
#pragma 划转方向改变
- (void)HZFXChange
{
     [operProcessDelegate getTradeProcess:@"" gpSetcode:-1 typeID:MAC_WT_FUNC pareOne:DBPHZ paraTwo:01 pareThree:@""];
}

#pragma mark alert相关
-(void)handleResult:(NSAlert *)alert withResult:(NSInteger)result withTag:(int)_tag
{
	switch(result)
	{
			//删除自选股
		case NSAlertDefaultReturn:
			if (_tag == 0) {
				[self startanimate];
                if(eGetData.tradeType == XJHK)
                {
                    [NSTimer scheduledTimerWithTimeInterval: 0.0f target:self selector: @selector(xjhkdoBuySell2) userInfo: nil repeats: NO];
                }
                else
                {
                    [NSTimer scheduledTimerWithTimeInterval: 0.0f target:self selector: @selector(doBuySell2) userInfo: nil repeats: NO];
                }
			}
			else {
				[self performSelector:@selector(dealErrorFocus:) withObject:[NSString stringWithFormat:@"%i",_tag] afterDelay:0.1f];
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

-(void)dealErrorFocus:(NSString *)_tag{
	switch ([_tag intValue]) {
		case 1:
		case 4:{
			[[self window] makeFirstResponder:gpcodeText];
			
			if (showType == 0){
				[showDelegate closeFastWT];
				[operProcessDelegate getTradeProcess:@"" gpSetcode:-1 typeID:MAC_CANCEL_FUNC pareOne:TDX_DRWT paraTwo:01 pareThree:@""];
			}
		}
			break;
		case 2:	
			[[self window] makeFirstResponder:gppriceText];
			break;	
		case 3:
			[[self window] makeFirstResponder:gpnumText];
			
		default:
			break;
	}
}
- (void)drawRect:(NSRect)dirtyRect {
   
	if (showType > 0) {
		CGContextRef context = [[NSGraphicsContext currentContext] graphicsPort];
		CGContextSetAllowsAntialiasing(context, FALSE);
		[[NSColor grayColor] set];
		CGContextAddRect(context, CGRectMake(gddmCombobox.frame.origin.x+gddmCombobox.frame.size.width+18, gddmCombobox.frame.origin.y+TOPMARIN_HEIGHT-213, dirtyRect.size.width-WT_WIDTH-2, 11*PERROWHEIGHT_PK-2*TOPMARIN_HEIGHT));
		
		CGContextStrokePath(context);
		CGContextSetAllowsAntialiasing(context, TRUE);
	}
}

@end
