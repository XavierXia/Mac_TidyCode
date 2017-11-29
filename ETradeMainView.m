//
//  ETradeMainView.m
//  tdxMac
//
//  Created by tdx on 11-10-25.
//  Copyright 2011 武汉. All rights reserved.
//

#import "ETradeMainView.h"
#define FUNCLIST_WIDTH 200
#define FUNCBAR_HEIGHT 40
#define SEPARATE_WIDTH 4
#define RIGHTMARIN_WIDTH 10
#define LEFTMARIN_WIDTH 5

@implementation ETradeMainView
@synthesize funcList,bodyView,tradeDelegate,m_lockscreen,reconObject,m_DBPHZlockscreen;


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
        //信用交易添加按钮
        CGFloat xyWidth;
        if (eGetData.clientinfos.m_bxyjyflag)
        {
            xyWidth = 80;
        }
        
		reconObject  =[[NSReconnObject alloc] initWithGetData:_eGetData];
		
		funcList = [[ETradeFuncListView alloc] initWithData:NSMakeRect(0, 0, FUNCLIST_WIDTH, frame.size.height) theData:eGetData];
	
        [self addSubview:funcList];
		
		
		bodyView = [[ETradeBodyView alloc] initWithData:NSMakeRect(FUNCLIST_WIDTH, 0, frame.size.width-FUNCLIST_WIDTH, frame.size.height-FUNCBAR_HEIGHT) theData:eGetData];
		[self addSubview:bodyView];
        
        m_DBPHZlockscreen = [[DBPHZLockScreen alloc] initWithData:NSMakeRect(FUNCLIST_WIDTH, 0, frame.size.width-FUNCLIST_WIDTH, frame.size.height) theData:_eGetData];
		
		
		m_lockscreen = [[LockScreen alloc] initWithData:NSMakeRect(0, 0, frame.size.width, frame.size.height) theData:_eGetData];
	
        currIndex= -1;
		
		titleText = [[NSTextField alloc]init];
		[titleText setEditable:NO];
		[titleText setBackgroundColor:[NSColor clearColor]];
		[titleText setBordered:NO];
		[titleText setFrame:NSMakeRect(FUNCLIST_WIDTH+(frame.size.width- FUNCLIST_WIDTH)/2 -40, frame.size.height-FUNCBAR_HEIGHT, 120, FUNCBAR_HEIGHT-10)];
	
        [[titleText cell] setTextColor:[NSColor blackColor]];
		[self addSubview:titleText];
		
		
		
		buyButton = [[NSButton alloc] init];
		[buyButton setButtonType:NSPushOnPushOffButton];
		[buyButton setBezelStyle:12];
		[[buyButton cell] setTitle:@"买入"];
		[buyButton setTag:1];
		[buyButton setTarget:self];
		[buyButton setAction:@selector(buttonClick:)];
		[buyButton setFrame:NSMakeRect(FUNCLIST_WIDTH, frame.size.height-FUNCBAR_HEIGHT+10, 40, FUNCBAR_HEIGHT-20)];
		[self addSubview:buyButton];
		
		sellButton = [[NSButton alloc] init];
		[sellButton setButtonType:NSPushOnPushOffButton];
		[sellButton setBezelStyle:12];
		[[sellButton cell] setTitle:@"卖出"];
		[sellButton setTag:2];
		[sellButton setTarget:self];
		[sellButton setAction:@selector(buttonClick:)];
		[sellButton setFrame:NSMakeRect(FUNCLIST_WIDTH+1*40, frame.size.height-FUNCBAR_HEIGHT+10, 40, FUNCBAR_HEIGHT-20)];
		[self addSubview:sellButton];
        
        RZbuyButton = [[NSButton alloc] init];
        [RZbuyButton setButtonType:NSPushOnPushOffButton];
        [RZbuyButton setBezelStyle:12];
        [[RZbuyButton cell] setTitle:@"融资买入"];
        [RZbuyButton setTag:8];
        [RZbuyButton setTarget:self];
        [RZbuyButton setAction:@selector(buttonClick:)];
        [RZbuyButton setFrame:NSMakeRect(FUNCLIST_WIDTH +2*40, frame.size.height-FUNCBAR_HEIGHT+10, 40, FUNCBAR_HEIGHT-20)];
        
        
        RZsellButton = [[NSButton alloc] init];
        [RZsellButton setButtonType:NSPushOnPushOffButton];
        [RZsellButton setBezelStyle:12];
        [[RZsellButton cell] setTitle:@"融资卖出"];
        [RZsellButton setTag:9];
        [RZsellButton setTarget:self];
        [RZsellButton setAction:@selector(buttonClick:)];
        [RZsellButton setFrame:NSMakeRect(FUNCLIST_WIDTH+3*40, frame.size.height-FUNCBAR_HEIGHT+10, 40, FUNCBAR_HEIGHT-20)];
        
        if (eGetData.clientinfos.m_bxyjyflag)
        {
            [self addSubview:RZsellButton];
            [self addSubview:RZbuyButton];
            [[sellButton cell] setTitle:@"担保品卖出"];
            [[buyButton cell] setTitle:@"担保品买入"];
        }
      
		cancelButton = [[NSButton alloc] init];
		[cancelButton setButtonType:NSPushOnPushOffButton];
		[cancelButton setBezelStyle:12];
		[[cancelButton cell] setTitle:@"撤单"];
		[cancelButton setTag:3];
		[cancelButton setTarget:self];
		[cancelButton setAction:@selector(buttonClick:)];
		[cancelButton setFrame:NSMakeRect(FUNCLIST_WIDTH+2*40 +xyWidth, frame.size.height-FUNCBAR_HEIGHT+10, 40, FUNCBAR_HEIGHT-20)];
		[self addSubview:cancelButton];
		
		dealButton = [[NSButton alloc] init];
		[dealButton setButtonType:NSPushOnPushOffButton];
		[dealButton setBezelStyle:12];
		[[dealButton cell] setTitle:@"成交"];
		[dealButton setTag:4];
		[dealButton setTarget:self];
		[dealButton setAction:@selector(buttonClick:)];
		[dealButton setFrame:NSMakeRect(FUNCLIST_WIDTH+3*40 +xyWidth, frame.size.height-FUNCBAR_HEIGHT+10, 40, FUNCBAR_HEIGHT-20)];
		[self addSubview:dealButton];
		
		chicangButton = [[NSButton alloc] init];
		[chicangButton setButtonType:NSPushOnPushOffButton];
		[chicangButton setBezelStyle:12];
		[[chicangButton cell] setTitle:@"持仓"];
		[chicangButton setTag:5];
		[chicangButton setTarget:self];
		[chicangButton setAction:@selector(buttonClick:)];
		[chicangButton setFrame:NSMakeRect(FUNCLIST_WIDTH+4*40 +xyWidth, frame.size.height-FUNCBAR_HEIGHT+10, 40, FUNCBAR_HEIGHT-20)];
		[self addSubview:chicangButton];
		
		refreshButton = [[NSButton alloc] init];
	
        [refreshButton setBezelStyle:12];
		[[refreshButton cell] setTitle:@"刷新"];
		[refreshButton setTag:6];
		[refreshButton setTarget:self];
		[refreshButton setAction:@selector(refreshButtonClick)];
		[refreshButton setFrame:NSMakeRect(FUNCLIST_WIDTH+5*40 +xyWidth, frame.size.height-FUNCBAR_HEIGHT+10, 40, FUNCBAR_HEIGHT-20)];
		[self addSubview:refreshButton];
		
		transferButton = [[NSButton alloc] init];
		[transferButton setButtonType:NSPushOnPushOffButton];
		[transferButton setBezelStyle:12];
		[[transferButton cell] setTitle:@"转账"];
		[transferButton setTag:7];
		[transferButton setTarget:self];
		[transferButton setAction:@selector(buttonClick:)];
		[transferButton setFrame:NSMakeRect(FUNCLIST_WIDTH+6*40 +xyWidth, frame.size.height-FUNCBAR_HEIGHT+10, 40, FUNCBAR_HEIGHT-20)];
		[self addSubview:transferButton];
		
		
		closeButton = [[NSButton alloc] init];
		[closeButton setBezelStyle:12];
		[[closeButton cell] setTitle:@"退出"];
		[[closeButton cell] setBackgroundColor:[NSColor clearColor]];
		[closeButton setTarget:self];
		[closeButton setAction:@selector(closeButtonClick)];
		[closeButton setFrame:NSMakeRect(frame.size.width - 40, frame.size.height-FUNCBAR_HEIGHT+10, 40, FUNCBAR_HEIGHT-20)];
		[self addSubview:closeButton];
        

#ifdef IMAC_GDZQ
        changeSizeButton = [[NSButton alloc] init];
        [changeSizeButton setBezelStyle:12];
        [[changeSizeButton cell] setTitle:@"放大"];
        [[changeSizeButton cell] setBackgroundColor:[NSColor clearColor]];
        [changeSizeButton setTarget:self];
        [changeSizeButton setAction:@selector(changeSizeButtonClick)];
        [changeSizeButton setFrame:NSMakeRect(frame.size.width - 40-40, frame.size.height-FUNCBAR_HEIGHT+10, 40, FUNCBAR_HEIGHT-20)];
        [self addSubview:changeSizeButton];
		
		minButton= [[NSButton alloc] init];
		[minButton setBezelStyle:12];
		[[minButton cell] setTitle:@"隐藏"];
		[[minButton cell] setBackgroundColor:[NSColor clearColor]];
		[minButton setTarget:self];
		[minButton setAction:@selector(minButtonClick)];
		[minButton setFrame:NSMakeRect(frame.size.width - 40-40-40, frame.size.height-FUNCBAR_HEIGHT+10, 40, FUNCBAR_HEIGHT-20)];
		[self addSubview:minButton];
        
		
		lockButton = [[NSButton alloc] init];
		[lockButton setBezelStyle:12];
		[[lockButton cell] setTitle:@"锁定"];
	
        [[lockButton cell] setBackgroundColor:[NSColor clearColor]];
		[lockButton setTarget:self];
		[lockButton setAction:@selector(lockButtonClick)];
		[lockButton setFrame:NSMakeRect(frame.size.width - 40-40-40-40, frame.size.height-FUNCBAR_HEIGHT+10, 40, FUNCBAR_HEIGHT-20)];
		[self addSubview:lockButton];
#else
        minButton= [[NSButton alloc] init];
        [minButton setBezelStyle:12];
        [[minButton cell] setTitle:@"隐藏"];
        [[minButton cell] setBackgroundColor:[NSColor clearColor]];
        [minButton setTarget:self];
        [minButton setAction:@selector(minButtonClick)];
        [minButton setFrame:NSMakeRect(frame.size.width -40-40, frame.size.height-FUNCBAR_HEIGHT+10, 40, FUNCBAR_HEIGHT-20)];
        [self addSubview:minButton];
        
        
        lockButton = [[NSButton alloc] init];
        [lockButton setBezelStyle:12];
        [[lockButton cell] setTitle:@"锁定"];
        
        [[lockButton cell] setBackgroundColor:[NSColor clearColor]];
        [lockButton setTarget:self];
        [lockButton setAction:@selector(lockButtonClick)];
        [lockButton setFrame:NSMakeRect(frame.size.width -40-40-40, frame.size.height-FUNCBAR_HEIGHT+10, 40, FUNCBAR_HEIGHT-20)];
        [self addSubview:lockButton];
        
#endif
		
	}
	return self;
}


-(void) setFrame:(NSRect)frame{
	[super setFrame:frame];
	viewRect = frame;
	   CGFloat xyWidth;
       CGFloat margin;
    if (eGetData.clientinfos.m_bxyjyflag)
    {
        xyWidth = 80;
        margin = 10;
    }
    
	[funcList setFrame:NSMakeRect(0, 0, FUNCLIST_WIDTH, frame.size.height)];
	[bodyView setFrame:NSMakeRect(FUNCLIST_WIDTH+3, 0, frame.size.width-FUNCLIST_WIDTH-3, frame.size.height-FUNCBAR_HEIGHT-2)];
    [m_DBPHZlockscreen setFrame:NSMakeRect(FUNCLIST_WIDTH+3, 0, frame.size.width-FUNCLIST_WIDTH-3, frame.size.height-FUNCBAR_HEIGHT-2)];
    
	[m_lockscreen setFrame:NSMakeRect(0, 0, frame.size.width, frame.size.height)];
	
	[titleText setFrame:NSMakeRect(LEFTMARIN_WIDTH+FUNCLIST_WIDTH+(frame.size.width- FUNCLIST_WIDTH)/2 -40, frame.size.height-FUNCBAR_HEIGHT, 120, FUNCBAR_HEIGHT-10)];
	[buyButton setFrame:NSMakeRect(LEFTMARIN_WIDTH+FUNCLIST_WIDTH, frame.size.height-FUNCBAR_HEIGHT+10, 40 + xyWidth/2, FUNCBAR_HEIGHT-20)];
	[sellButton setFrame:NSMakeRect(LEFTMARIN_WIDTH+FUNCLIST_WIDTH+1*(40+SEPARATE_WIDTH)+xyWidth/2, frame.size.height-FUNCBAR_HEIGHT+10, 40+xyWidth/2, FUNCBAR_HEIGHT-20)];
    [RZbuyButton setFrame:NSMakeRect(LEFTMARIN_WIDTH+FUNCLIST_WIDTH+2*(40+SEPARATE_WIDTH)+xyWidth, frame.size.height-FUNCBAR_HEIGHT+10, xyWidth, FUNCBAR_HEIGHT-20)];
    [RZsellButton setFrame:NSMakeRect(LEFTMARIN_WIDTH+FUNCLIST_WIDTH+3*(40+SEPARATE_WIDTH)+xyWidth/2*3, frame.size.height-FUNCBAR_HEIGHT+10, xyWidth, FUNCBAR_HEIGHT-20)];
	[cancelButton setFrame:NSMakeRect(LEFTMARIN_WIDTH+FUNCLIST_WIDTH+2*(40+SEPARATE_WIDTH) + xyWidth+xyWidth*2 +margin, frame.size.height-FUNCBAR_HEIGHT+10, 40, FUNCBAR_HEIGHT-20)];
	[dealButton setFrame:NSMakeRect(LEFTMARIN_WIDTH+FUNCLIST_WIDTH+3*(40+SEPARATE_WIDTH)+ xyWidth+xyWidth*2 +margin, frame.size.height-FUNCBAR_HEIGHT+10, 40, FUNCBAR_HEIGHT-20)];
	[chicangButton setFrame:NSMakeRect(LEFTMARIN_WIDTH+FUNCLIST_WIDTH+4*(40+SEPARATE_WIDTH)+ xyWidth+xyWidth*2 +margin, frame.size.height-FUNCBAR_HEIGHT+10, 40, FUNCBAR_HEIGHT-20)];
	[refreshButton setFrame:NSMakeRect(LEFTMARIN_WIDTH+FUNCLIST_WIDTH+5*(40+SEPARATE_WIDTH)+ xyWidth+xyWidth*2 +margin, frame.size.height-FUNCBAR_HEIGHT+10, 40, FUNCBAR_HEIGHT-20)];
	[transferButton setFrame:NSMakeRect(LEFTMARIN_WIDTH+FUNCLIST_WIDTH+6*(40+SEPARATE_WIDTH)+ xyWidth+xyWidth*2 +margin, frame.size.height-FUNCBAR_HEIGHT+10, 40, FUNCBAR_HEIGHT-20)];
	[closeButton setFrame:NSMakeRect(frame.size.width-RIGHTMARIN_WIDTH - (40+SEPARATE_WIDTH), frame.size.height-FUNCBAR_HEIGHT+10, 40, FUNCBAR_HEIGHT-20)];
    
#ifdef IMAC_GDZQ
    [changeSizeButton setFrame:NSMakeRect(frame.size.width-RIGHTMARIN_WIDTH - 2*(40+SEPARATE_WIDTH), frame.size.height-FUNCBAR_HEIGHT+10, 40, FUNCBAR_HEIGHT-20)];
    [minButton setFrame:NSMakeRect(frame.size.width -RIGHTMARIN_WIDTH- 3*(40+SEPARATE_WIDTH), frame.size.height-FUNCBAR_HEIGHT+10, 40, FUNCBAR_HEIGHT-20)];
    [lockButton setFrame:NSMakeRect(frame.size.width-RIGHTMARIN_WIDTH - 4*(40+SEPARATE_WIDTH), frame.size.height-FUNCBAR_HEIGHT+10, 40, FUNCBAR_HEIGHT-20)];
#else
    [minButton setFrame:NSMakeRect(frame.size.width -RIGHTMARIN_WIDTH- 2*(40+SEPARATE_WIDTH), frame.size.height-FUNCBAR_HEIGHT+10, 40, FUNCBAR_HEIGHT-20)];
    [lockButton setFrame:NSMakeRect(frame.size.width-RIGHTMARIN_WIDTH - 3*(40+SEPARATE_WIDTH), frame.size.height-FUNCBAR_HEIGHT+10, 40, FUNCBAR_HEIGHT-20)];
#endif
    
    float fright=transferButton.frame.origin.x+transferButton.frame.size.width+10;
    
    float fleft=LEFTMARIN_WIDTH+FUNCLIST_WIDTH+(frame.size.width- FUNCLIST_WIDTH)/2 -40;
    if(fleft>fright )
        [titleText setFrame:NSMakeRect(fleft, frame.size.height-FUNCBAR_HEIGHT, 120, FUNCBAR_HEIGHT-10)];
    else
        [titleText setFrame:NSMakeRect(0.0, 0.0, 0.0, 0.0)];
    
    fleft=frame.size.width-RIGHTMARIN_WIDTH - (40+SEPARATE_WIDTH);
    if(fleft>fright)
        [closeButton setFrame:NSMakeRect(fleft, frame.size.height-FUNCBAR_HEIGHT+10, 40, FUNCBAR_HEIGHT-20)];
    else
        [closeButton setFrame:NSMakeRect(0.0, 0.0, 0.0, 0.0)];
    
#ifdef GDZQ
    fleft=frame.size.width-RIGHTMARIN_WIDTH - 2*(40+SEPARATE_WIDTH);
    if(fleft>fright)
        [changeSizeButton setFrame:NSMakeRect(fleft, frame.size.height-FUNCBAR_HEIGHT+10, 40, FUNCBAR_HEIGHT-20)];
    else
        [changeSizeButton setFrame:NSMakeRect(0.0, 0.0, 0.0, 0.0)];
    
    fleft=frame.size.width -RIGHTMARIN_WIDTH- 3*(40+SEPARATE_WIDTH);
    if(fleft>fright)
        [minButton setFrame:NSMakeRect(fleft, frame.size.height-FUNCBAR_HEIGHT+10, 40, FUNCBAR_HEIGHT-20)];
    else
        [minButton setFrame:NSMakeRect(0.0, 0.0, 0.0, 0.0)];
    
    fleft=frame.size.width-RIGHTMARIN_WIDTH - 4*(40+SEPARATE_WIDTH);
    if(fleft>fright)
        [lockButton setFrame:NSMakeRect(fleft, frame.size.height-FUNCBAR_HEIGHT+10, 40, FUNCBAR_HEIGHT-20)];
    else
        [lockButton setFrame:NSMakeRect(0.0, 0.0, 0.0, 0.0)];
#else
    fleft=frame.size.width -RIGHTMARIN_WIDTH- 2*(40+SEPARATE_WIDTH);
    if(fleft>fright)
        [minButton setFrame:NSMakeRect(fleft, frame.size.height-FUNCBAR_HEIGHT+10, 40, FUNCBAR_HEIGHT-20)];
    else
        [minButton setFrame:NSMakeRect(0.0, 0.0, 0.0, 0.0)];
    
    fleft=frame.size.width-RIGHTMARIN_WIDTH - 3*(40+SEPARATE_WIDTH);
    if(fleft>fright)
        [lockButton setFrame:NSMakeRect(fleft, frame.size.height-FUNCBAR_HEIGHT+10, 40, FUNCBAR_HEIGHT-20)];
    else
        [lockButton setFrame:NSMakeRect(0.0, 0.0, 0.0, 0.0)];
#endif
}

-(void)lockButtonClick{
	[tradeDelegate lockButtonClick];
}

-(void)closeButtonClick{
	NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
									 defaultButton: @"确定"
								   alternateButton:@"取消"
									   otherButton: nil
						 informativeTextWithFormat: @"你确定要退出交易系统吗？"];
	[alert setDelegate:self];
	NSInteger result = [alert runModal];
	[self handleResult:alert withResult:result];	
}
-(void)minButtonClick{
	[tradeDelegate minButtonClick];
}

-(void)changeSizeButtonClick
{
    int flag = 0;
    if([[[changeSizeButton cell] title] isEqualToString:@"放大"])
    {
        [[changeSizeButton cell] setTitle:@"缩小"];
        flag = 0;
    }
    else
    {
        [[changeSizeButton cell] setTitle:@"放大"];
        flag = 1;
    }
    
    [tradeDelegate changeSizeButtonClick:flag];
}

-(void)refreshButtonClick{
	
    [NSTimer scheduledTimerWithTimeInterval: 1.0f target:self selector: @selector(refreshDelayed) userInfo: nil repeats: NO];
}

-(void)refreshDelayed
{
    [operProcessDelegate getTradeProcess:@"" gpSetcode:-1 typeID:MAC_REFRESH_FUNC pareOne:-1 paraTwo:-1 pareThree:@""];
}

-(void)buttonClick:(id)sender{
	NSButton * tempButton;
	tempButton = (NSButton*)sender;
	
	[self resetAllButton];
	
	
	if (currIndex != tempButton.tag) {
		[tempButton setState:NSOnState];
		currIndex = tempButton.tag;
        eGetData.saveDate.xwdm = @"";
		
		
		switch (tempButton.tag) {
			case 1:
				[operProcessDelegate getTradeProcess:@"" gpSetcode:-1 typeID:MAC_WT_FUNC pareOne:0 paraTwo:-1 pareThree:@""];
				break;
			case 2:
				[operProcessDelegate getTradeProcess:@"" gpSetcode:-1 typeID:MAC_WT_FUNC pareOne:1 paraTwo:-1 pareThree:@""];
				break;
			case 4:
				[operProcessDelegate getTradeProcess:@"" gpSetcode:-1 typeID:MAC_TRADE_FUNC pareOne:TDX_DRCJ paraTwo:-1 pareThree:@""];
				break;
			case 3:
				[operProcessDelegate getTradeProcess:@"" gpSetcode:-1 typeID:MAC_CANCEL_FUNC pareOne:TDX_CDCX paraTwo:-1 pareThree:@""];
				break;
			case 5:
                eGetData.tradeType = DBPBuy;
				[operProcessDelegate getTradeProcess:@"" gpSetcode:-1 typeID:MAC_TRADE_FUNC pareOne:TDX_GFCX paraTwo:-1 pareThree:@""];
				break;
			case 7:
				[operProcessDelegate getTradeProcess:@"" gpSetcode:-1 typeID:MAC_BANK_FUNC pareOne:TDX_YZZZ paraTwo:-1 pareThree:@""];
				break;
            case 8:
                eGetData.tradeType = RZBuy;
                [operProcessDelegate getTradeProcess:@"" gpSetcode:-1 typeID:MAC_WT_FUNC pareOne:2 paraTwo:-1 pareThree:@""];
                break;
            case 9:
                eGetData.tradeType = RZSell;
                [operProcessDelegate getTradeProcess:@"" gpSetcode:-1 typeID:MAC_WT_FUNC pareOne:3 paraTwo:-1 pareThree:@""];
                break;

			default:
				break;
		}
	}
	else {
		[tempButton setState:NSOnState];
	}

	
	
}


-(void)resetAllButton{
    [buyButton setState:NSOffState];
    [sellButton setState:NSOffState];
    [cancelButton setState:NSOffState];
    [dealButton setState:NSOffState];
    [chicangButton setState:NSOffState];
    [transferButton setState:NSOffState];
    
	NSMutableParagraphStyle * tempStyle = [[NSMutableParagraphStyle alloc]init] ;
	[tempStyle setAlignment:NSCenterTextAlignment];
	
	NSDictionary * attrsDictionary = [NSDictionary dictionaryWithObjectsAndKeys:[NSColor blackColor],NSForegroundColorAttributeName,tempStyle,NSParagraphStyleAttributeName,nil];
	[tempStyle release];
	
	NSAttributedString * attrString = [[NSAttributedString alloc] initWithString:@"买入" attributes:attrsDictionary];
	[buyButton setAttributedTitle:attrString];
	[attrString release];
	
	attrString = [[NSAttributedString alloc] initWithString:@"卖出" attributes:attrsDictionary];
	[sellButton setAttributedTitle:attrString];
	[attrString release];
	
	attrString = [[NSAttributedString alloc] initWithString:@"撤单" attributes:attrsDictionary];
	[cancelButton setAttributedTitle:attrString];
	[attrString release];
	
	attrString = [[NSAttributedString alloc] initWithString:@"成交" attributes:attrsDictionary];
	[dealButton setAttributedTitle:attrString];
	[attrString release];
	
	attrString = [[NSAttributedString alloc] initWithString:@"持仓" attributes:attrsDictionary];
	[chicangButton setAttributedTitle:attrString];
	[attrString release];
	
	attrString = [[NSAttributedString alloc] initWithString:@"转账" attributes:attrsDictionary];
	[transferButton setAttributedTitle:attrString];
	[attrString release];
    
    if (eGetData.clientinfos.m_bxyjyflag)
    {
        NSAttributedString * attrString = [[NSAttributedString alloc] initWithString:@"担保品买入" attributes:attrsDictionary];
        [buyButton setAttributedTitle:attrString];
        [attrString release];
        
        attrString = [[NSAttributedString alloc] initWithString:@"担保品卖出" attributes:attrsDictionary];
        [sellButton setAttributedTitle:attrString];
        [attrString release];
    
         attrString = [[NSAttributedString alloc] initWithString:@"融资买入" attributes:attrsDictionary];
        [RZbuyButton setAttributedTitle:attrString];
        [attrString release];
        
        attrString = [[NSAttributedString alloc] initWithString:@"融资卖出" attributes:attrsDictionary];
        [RZsellButton setAttributedTitle:attrString];
        [attrString release];
        
        [RZbuyButton setState:NSOffState];
        [RZsellButton setState:NSOffState];
    }
  
    
}

-(void)dealTitleAndButton:(int)_type ParaOne:(int)_para{
	if (_type == MAC_REFRESH_FUNC) {
		return;
	}
	
	NSMutableParagraphStyle * tempStyle = [[NSMutableParagraphStyle alloc]init] ;
	[tempStyle setAlignment:NSCenterTextAlignment];
	
	currIndex = _type;
	[self resetAllButton];
	switch (_type) {
		case MAC_WT_FUNC://下单
			if (_para == DBPBuy) {
				[self resetAllButton];
				[buyButton setState:NSOnState];
                NSDictionary * attrsDictionary = [NSDictionary dictionaryWithObjectsAndKeys:[NSColor redColor],NSForegroundColorAttributeName,tempStyle,NSParagraphStyleAttributeName,nil];
                NSAttributedString * attrString = [[NSAttributedString alloc] initWithString:buyButton.cell.title attributes:attrsDictionary];
                [buyButton setAttributedTitle:attrString];
                [attrString release];
                [[titleText cell] setTitle:buyButton.cell.title];

			}
			else if (_para == DBPSell){
				[self resetAllButton];
				[sellButton setState:NSOnState];
                NSDictionary * attrsDictionary = [NSDictionary dictionaryWithObjectsAndKeys:[NSColor greenColor],NSForegroundColorAttributeName,tempStyle,NSParagraphStyleAttributeName,nil];
                NSAttributedString * attrString = [[NSAttributedString alloc] initWithString:sellButton.cell.title attributes:attrsDictionary];
                [sellButton setAttributedTitle:attrString];
                [attrString release];
				[[titleText cell] setTitle:sellButton.cell.title];
			}
            else if (_para == RZBuy) {
                [self resetAllButton];
                [RZbuyButton setState:NSOnState];
                NSDictionary * attrsDictionary = [NSDictionary dictionaryWithObjectsAndKeys:[NSColor redColor],NSForegroundColorAttributeName,tempStyle,NSParagraphStyleAttributeName,nil];
                NSAttributedString * attrString = [[NSAttributedString alloc] initWithString:RZbuyButton.cell.title attributes:attrsDictionary];
                [RZbuyButton setAttributedTitle:attrString];
                [attrString release];
                [[titleText cell] setTitle:RZbuyButton.cell.title];
                
            }
            else if (_para == RZSell){
                [self resetAllButton];
                [RZsellButton setState:NSOnState];
                NSDictionary * attrsDictionary = [NSDictionary dictionaryWithObjectsAndKeys:[NSColor greenColor],NSForegroundColorAttributeName,tempStyle,NSParagraphStyleAttributeName,nil];
                NSAttributedString * attrString = [[NSAttributedString alloc] initWithString:RZsellButton.cell.title attributes:attrsDictionary];
                [RZsellButton setAttributedTitle:attrString];
                [attrString release];
                [[titleText cell] setTitle:RZsellButton.cell.title];
            }

            else if (_para == DBPHZ){
                [[titleText cell] setTitle:@"担保品划转"];
            }
            else if (_para == MQHK){
                [[titleText cell] setTitle:@"卖券还款"];
            }
            else if (_para == MQHQ){
                [[titleText cell] setTitle:@"买券还券"];
            }
            else if (_para == XJHK){
                [[titleText cell] setTitle:@"现金还款"];
            }
            else if (_para == XQHQ){
                [[titleText cell] setTitle:@"现券还券"];

            }
            else if (_para == XGSG){
                [[titleText cell] setTitle:@"新股申购"];
            }

			break;
		case MAC_TRADE_FUNC:
            
			if (_para == TDX_GFCX) {
				[self resetAllButton];
				[chicangButton setState:NSOnState];
				NSDictionary * attrsDictionary = [NSDictionary dictionaryWithObjectsAndKeys:[NSColor blueColor],NSForegroundColorAttributeName,tempStyle,NSParagraphStyleAttributeName,nil];
				NSAttributedString * attrString = [[NSAttributedString alloc] initWithString:@"持仓" attributes:attrsDictionary];
				[chicangButton setAttributedTitle:attrString];
				[attrString release];
				[[titleText cell] setTitle:@"资金股份"];
			}
			else if (_para == TDX_DRCJ){
				[self resetAllButton];
				[dealButton setState:NSOnState];
				NSDictionary * attrsDictionary = [NSDictionary dictionaryWithObjectsAndKeys:[NSColor blueColor],NSForegroundColorAttributeName,tempStyle,NSParagraphStyleAttributeName,nil];
				NSAttributedString * attrString = [[NSAttributedString alloc] initWithString:@"成交" attributes:attrsDictionary];
				[dealButton setAttributedTitle:attrString];
				[attrString release];
				[[titleText cell] setTitle:@"当日成交"];
			}
			else if (_para == TDX_LSWT){
				[[titleText cell] setTitle:@"历史委托"];
			}
			else if (_para == TDX_LSCJ){
				[[titleText cell] setTitle:@"历史成交"];
			}
			else if (_para == TDX_CJHZ){
				[[titleText cell] setTitle:@"成交汇总"];
			}
			else if (_para == TDX_ZJLS){
				[[titleText cell] setTitle:@"资金流水"];
			}
            else if (_para == TDX_XGSG){
                [[titleText cell] setTitle:@"新股申购"];
            }
            else if (_para == TDX_KSGXGCX){
                [[titleText cell] setTitle:@"可申购新股查询"];
            }
            else if (_para == TDX_PHCX){
                [[titleText cell] setTitle:@"配号查询"];
            }
            else if (_para == TDX_XGZQCX){
                [[titleText cell] setTitle:@"中签查询"];
            }
            else if (_para == TDX_IPOSGED){
				[[titleText cell] setTitle:@"新股申购额度查询"];
			}
			else if (_para == TDX_GDCX){
				[[titleText cell] setTitle:@"股东查询"];
			}
            else if (_para == TDX_XYBDZQCX){
                [[titleText cell] setTitle:@"标的证券查询"];
            }

            else if (_para == TDX_XYDBPZQCX){
                [[titleText cell] setTitle:@"担保品证券查询"];
            }
            else if (_para == TDX_XYFZCX){
                [[titleText cell] setTitle:@"信用负债查询"];
            }
            else if (_para == TDX_XYSXCX){
                [[titleText cell] setTitle:@"信用上限查询"];
            }
            else if (_para == TDX_XYRQHYCX){
                [[titleText cell] setTitle:@"信用融券合约查询"];
            }
            else if (_para == TDX_XYRZHYCX){
                [[titleText cell] setTitle:@"信用合约查询"];
            }
            else if (_para == TDX_XYZCCX){
                [[titleText cell] setTitle:@"信用资产查询"];
            }
            else if(_para == TDX_DBPHZCD){
                [[titleText cell] setTitle:@"担保品划转撤单"];
            }
            else if(_para == TDX_DBPHZCX){
                [[titleText cell] setTitle:@"担保品划转查询"];
            }
//            else if(_para == TDX_DBPHZCD){
//                [[titleText cell] setTitle:@"信用资产查询"];
//            }
			break;
		case MAC_CANCEL_FUNC:
			if (_para == TDX_CDCX || _para == TDX_DBPHZCD) {
				[self resetAllButton];
				[cancelButton setState:NSOnState];
				NSDictionary * attrsDictionary = [NSDictionary dictionaryWithObjectsAndKeys:[NSColor blueColor],NSForegroundColorAttributeName,tempStyle,NSParagraphStyleAttributeName,nil];
				NSAttributedString * attrString = [[NSAttributedString alloc] initWithString:@"撤单" attributes:attrsDictionary];
				[cancelButton setAttributedTitle:attrString];
				[attrString release];
				[[titleText cell] setTitle:cancelButton.cell.title];
			}
			else if (_para == TDX_DRWT){
				[[titleText cell] setTitle:@"当日委托"];
			}
            break;
		case MAC_BANK_FUNC:
			if (_para == TDX_YZZZ) {
				[[titleText cell] setTitle:@"银证转账"];
				[self resetAllButton];
				[transferButton setState:NSOnState];
				NSDictionary * attrsDictionary = [NSDictionary dictionaryWithObjectsAndKeys:[NSColor blueColor],NSForegroundColorAttributeName,tempStyle,NSParagraphStyleAttributeName,nil];
				NSAttributedString * attrString = [[NSAttributedString alloc] initWithString:@"转账" attributes:attrsDictionary];
				[transferButton setAttributedTitle:attrString];
				[attrString release];
			}
			else if (_para == TDX_YHYE){
				[[titleText cell] setTitle:@"银行余额"];
			}
			else if (_para == TDX_ZZCX){
				[[titleText cell] setTitle:@"转账查询"];
			}
            else if (_para == TDX_PT_ZJZZ){
                [[titleText cell] setTitle:@"资金转账"];
            }
			break;
		case MAC_PASSWORD_FUNC:
			[[titleText cell] setTitle:@"修改密码"];
			break;
		default:
			break;
	}
	
	[tempStyle release];
}

- (void)drawRect:(NSRect)dirtyRect {
    CGContextRef context = [[NSGraphicsContext currentContext] graphicsPort];
	CGContextSetAllowsAntialiasing(context, FALSE);
	[[NSColor lightGrayColor] set];
	
	CGContextMoveToPoint(context, FUNCLIST_WIDTH+1, 0);
	CGContextAddLineToPoint(context, FUNCLIST_WIDTH+1, viewRect.size.height);
	
	CGContextMoveToPoint(context, FUNCLIST_WIDTH+1, viewRect.size.height-FUNCBAR_HEIGHT);
	CGContextAddLineToPoint(context, viewRect.size.width, viewRect.size.height-FUNCBAR_HEIGHT);
	
	
	CGContextStrokePath(context);
	CGContextSetAllowsAntialiasing(context, TRUE);
}



#pragma mark alert相关
-(void)handleResult:(NSAlert *)alert withResult:(NSInteger)result
{
	// report which button was clicked
	switch(result)
	{
			//删除自选股
		case NSAlertDefaultReturn:
			[tradeDelegate closeButtonClick];
			break;
			
		case NSAlertAlternateReturn:
			break;
			
		case NSAlertOtherReturn:
			break;
            
        default:
            break;
	}
	
}

#pragma mark 锁屏相关
-(void)showlockscreen
{
	if(eGetData.clientinfos.m_blocking==NO)
	{
		return;
	}
	[funcList removeFromSuperview];
	[bodyView removeFromSuperview];
	[self addSubview:m_lockscreen];
	[m_lockscreen onviewWillAppear];
}

-(void)unlockscreen
{
	[m_lockscreen removeFromSuperview];
	[self addSubview:funcList];
	[self addSubview:bodyView];
}

#pragma mark 担保品划转锁屏相关
-(BOOL)DBPHZshowlockscreen
{
    if(eGetData.clientinfos.m_DBPHZblocking==NO)
    {
        return NO;
    }
    [bodyView removeFromSuperview];
    [self addSubview:m_DBPHZlockscreen];
    [m_DBPHZlockscreen onviewWillAppear];
    
    return YES;
}

-(void)DBPHZunlockscreen
{
    [m_DBPHZlockscreen removeFromSuperview];
    [self addSubview:bodyView];
    
}

@end
