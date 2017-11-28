//
//  ETradeBankView.m
//  tdxMac
//
//  Created by tdx on 11-11-8.
//  Copyright 2011 武汉. All rights reserved.
//

#import "ETradeBankView.h"

#define ZZFS_COM_FLAG 1
#define XZYH_COM_FLAG 2
#define XZBZ_COM_FLAG 3
#define ZJMM_TEXT_FLAG 4
#define YHMM_TEXT_FLAG 5
#define ZZJE_TEXT_FLAG 6
#define ZCZH_TEXT_FLAG 7
#define ZRZH_TEXT_FLAG 8
#define ZCZH_COM_FLAG 9
#define ZRZH_COM_FLAG 10
#define ZJGJ_BTN_FLAG 11
#define DZJZZ_BTN_FLAG 12

#define PER_LABEL_WIDTH 70
#define PER_TEXT_WIDTH 300
#define PER_LABEL_HEIGHT 25
#define TOPMARIN 15
#define LEFTMARIN 30

@implementation ETradeBankView
@synthesize m_bleftarrowflag,m_bselbz,m_bselzzfx,baddflag,tag,m_bButtonshowflag;

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
		viewRect = frame;
		m_bselbz = NO;
#ifdef IMAC_ZXJT
        m_bselbz=YES;
#endif
#ifdef IMAC_GXZQ
        m_bselbz=YES;
#endif
#ifdef IMAC_HXZQ
        m_bselbz=YES;
#endif
#ifdef IMAC_PAZQ
        m_bselbz=YES;
#endif
		self.tradeindex = [_eGetData.g_TradeComm.areceiver SetWinobjs:self];
		
		moneyTypeArray = [[NSArray arrayWithObjects:@"人民币",@"美元", @"港币",nil] retain];
		zzfxArray=[[NSArray arrayWithObjects:@"银行转证券(转入)",@"证券转银行(转出)",nil] retain];
		

		zzfsLabel = [[NSTextField alloc]init];
		[zzfsLabel setEditable:NO];
		[zzfsLabel setBackgroundColor:[NSColor clearColor]];
		[zzfsLabel setBordered:NO];
		[zzfsLabel setFrame:NSZeroRect];
		[[zzfsLabel cell] setFont:[NSFont systemFontOfSize:14.0f]];
		[[zzfsLabel cell] setTextColor:[NSColor blackColor]];
		[[zzfsLabel cell] setTitle:@"转账方式:"];
		[self addSubview:zzfsLabel];
		
		xzyhLabel = [[NSTextField alloc]init];
		[xzyhLabel setEditable:NO];
		[xzyhLabel setBackgroundColor:[NSColor clearColor]];
		[xzyhLabel setBordered:NO];
		[xzyhLabel setFrame:NSZeroRect];
		[[xzyhLabel cell] setFont:[NSFont systemFontOfSize:14.0f]];
		[[xzyhLabel cell] setTextColor:[NSColor blackColor]];
		[[xzyhLabel cell] setTitle:@"选择银行:"];
		[self addSubview:xzyhLabel];
		
		zjmmLabel = [[NSTextField alloc]init];
		[zjmmLabel setEditable:NO];
		[zjmmLabel setBackgroundColor:[NSColor clearColor]];
		[zjmmLabel setBordered:NO];
		[zjmmLabel setFrame:NSZeroRect];
		[[zjmmLabel cell] setFont:[NSFont systemFontOfSize:14.0f]];
		[[zjmmLabel cell] setTextColor:[NSColor blackColor]];
		[[zjmmLabel cell] setTitle:@"资金密码:"];
		[self addSubview:zjmmLabel];
		
		yhmmLabel = [[NSTextField alloc]init];
		[yhmmLabel setEditable:NO];
		[yhmmLabel setBackgroundColor:[NSColor clearColor]];
		[yhmmLabel setBordered:NO];
		[yhmmLabel setFrame:NSZeroRect];
		[[yhmmLabel cell] setFont:[NSFont systemFontOfSize:14.0f]];
		[[yhmmLabel cell] setTextColor:[NSColor blackColor]];
		[[yhmmLabel cell] setTitle:@"银行密码:"];
		[self addSubview:yhmmLabel];
		
		zzjeLabel = [[NSTextField alloc]init];
		[zzjeLabel setEditable:NO];
		[zzjeLabel setBackgroundColor:[NSColor clearColor]];
		[zzjeLabel setBordered:NO];
		[zzjeLabel setFrame:NSZeroRect];
		[[zzjeLabel cell] setFont:[NSFont systemFontOfSize:14.0f]];
		[[zzjeLabel cell] setTextColor:[NSColor blackColor]];
		[[zzjeLabel cell] setTitle:@"转账金额:"];
		[self addSubview:zzjeLabel];
		
		xzbzLabel = [[NSTextField alloc]init];
		[xzbzLabel setEditable:NO];
		[xzbzLabel setBackgroundColor:[NSColor clearColor]];
		[xzbzLabel setBordered:NO];
		[xzbzLabel setFrame:NSZeroRect];
		[[xzbzLabel cell] setFont:[NSFont systemFontOfSize:14.0f]];
		[[xzbzLabel cell] setTextColor:[NSColor blackColor]];
		[[xzbzLabel cell] setTitle:@"选择币种:"];
		[self addSubview:xzbzLabel];
		
		yhyeLabel = [[NSTextField alloc]init];
		[yhyeLabel setEditable:NO];
		[yhyeLabel setBackgroundColor:[NSColor clearColor]];
		[yhyeLabel setBordered:NO];
		[yhyeLabel setFrame:NSZeroRect];
		[[yhyeLabel cell] setFont:[NSFont systemFontOfSize:14.0f]];
		[[yhyeLabel cell] setTextColor:[NSColor blackColor]];
		[[yhyeLabel cell] setTitle:@"银行余额:"];
		[self addSubview:yhyeLabel];
        
        zczhLabel = [[NSTextField alloc]init];
        [zczhLabel setEditable:NO];
        [zczhLabel setBackgroundColor:[NSColor clearColor]];
        [zczhLabel setBordered:NO];
        [zczhLabel setFrame:NSZeroRect];
        [[zczhLabel cell] setFont:[NSFont systemFontOfSize:14.0f]];
        [[zczhLabel cell] setTextColor:[NSColor blackColor]];
        [[zczhLabel cell] setTitle:@"转出帐号:"];
        [self addSubview:zczhLabel];
        
        zrzhLabel = [[NSTextField alloc]init];
        [zrzhLabel setEditable:NO];
        [zrzhLabel setBackgroundColor:[NSColor clearColor]];
        [zrzhLabel setBordered:NO];
        [zrzhLabel setFrame:NSZeroRect];
        [[zrzhLabel cell] setFont:[NSFont systemFontOfSize:14.0f]];
        [[zrzhLabel cell] setTextColor:[NSColor blackColor]];
        [[zrzhLabel cell] setTitle:@"转入帐号:"];
        [self addSubview:zrzhLabel];
        
        zczhComboBox = [[NSComboBox alloc] initWithFrame:NSZeroRect];
        [zczhComboBox setBackgroundColor:[NSColor clearColor]];
        [zczhComboBox setEditable:NO];
        [zczhComboBox setTag:ZCZH_COM_FLAG];
        [zczhComboBox setUsesDataSource:YES];
        [zczhComboBox setDelegate:self];
        [zczhComboBox setDataSource:self];
        [self addSubview:zczhComboBox];
        
        zrzhComboBox = [[NSComboBox alloc] initWithFrame:NSZeroRect];
        [zrzhComboBox setBackgroundColor:[NSColor clearColor]];
        [zrzhComboBox setEditable:NO];
        [zrzhComboBox setTag:ZRZH_COM_FLAG];
        [zrzhComboBox setUsesDataSource:YES];
        [zrzhComboBox setDelegate:self];
        [zrzhComboBox setDataSource:self];
        [self addSubview:zrzhComboBox];
		
		zzfsComboBox = [[NSComboBox alloc] initWithFrame:NSZeroRect];
		[zzfsComboBox setBackgroundColor:[NSColor clearColor]];
		[zzfsComboBox setEditable:NO];
		[zzfsComboBox setTag:ZZFS_COM_FLAG];
		[zzfsComboBox setUsesDataSource:YES];
		[zzfsComboBox setDelegate:self];
		[zzfsComboBox setDataSource:self];
		[self addSubview:zzfsComboBox];
		
		xzyhComboBox = [[NSComboBox alloc] initWithFrame:NSZeroRect];
		[xzyhComboBox setBackgroundColor:[NSColor clearColor]];
		[xzyhComboBox setEditable:NO];
		[xzyhComboBox setTag:XZYH_COM_FLAG];
		[xzyhComboBox setUsesDataSource:YES];
		[xzyhComboBox setDelegate:self];
		[xzyhComboBox setDataSource:self];
		[self addSubview:xzyhComboBox];
		
		xzbzComboBox = [[NSComboBox alloc] initWithFrame:NSZeroRect];
		[xzbzComboBox setBackgroundColor:[NSColor clearColor]];
		[xzbzComboBox setEditable:NO];
		[xzbzComboBox setTag:XZBZ_COM_FLAG];
		[xzbzComboBox setUsesDataSource:YES];
		[xzbzComboBox setDelegate:self];
		[xzbzComboBox setDataSource:self];
		[self addSubview:xzbzComboBox];
		
		
		zjmmText = [[CustomSecureTextField alloc]init];
		[zjmmText setEditable:YES];
		[zjmmText setBackgroundColor:[NSColor whiteColor]];
		[zjmmText setBordered:YES];
		[zjmmText setBezeled:YES];
		[zjmmText setDelegate:self];
		zjmmText.focusDelegate = self;
		[zjmmText setBezelStyle:NSTextFieldSquareBezel];
		[zjmmText setFrame:NSZeroRect];
		[zjmmText setTag:ZJMM_TEXT_FLAG];
		[[zjmmText cell] setTextColor:[NSColor blackColor]];
		[self addSubview:zjmmText];
		
		yhmmText = [[CustomSecureTextField alloc]init];
		[yhmmText setEditable:YES];
		[yhmmText setBackgroundColor:[NSColor whiteColor]];
		[yhmmText setBordered:YES];
		[yhmmText setBezeled:YES];
		[yhmmText setDelegate:self];
		yhmmText.focusDelegate = self;
		[yhmmText setBezelStyle:NSTextFieldSquareBezel];
		[yhmmText setFrame:NSZeroRect];
		[yhmmText setTag:YHMM_TEXT_FLAG];
		[[yhmmText cell] setTextColor:[NSColor blackColor]];
		[self addSubview:yhmmText];
		
		zzjeText = [[CustonTextField alloc]init];
		[zzjeText setEditable:YES];
		[zzjeText setBackgroundColor:[NSColor whiteColor]];
		[zzjeText setBordered:YES];
		[zzjeText setBezeled:YES];
		[zzjeText setBezelStyle:NSTextFieldSquareBezel];
		[zzjeText setDelegate:self];
		zzjeText.focusDelegate = self;
		[zzjeText setTag:ZZJE_TEXT_FLAG];
		[zzjeText setFrame:NSZeroRect];
		[[zzjeText cell] setTextColor:[NSColor blackColor]];
		customTextFieldFormatter * formatter = [[[customTextFieldFormatter alloc] init] autorelease];
		[formatter setShowDot:YES];
		[zzjeText setFormatter:formatter];
		[self addSubview:zzjeText];
		
		yhyeText = [[NSTextField alloc]init];
		[yhyeText setEditable:NO];
		[yhyeText setBackgroundColor:[NSColor clearColor]];
		[yhyeText setBordered:YES];
		[yhyeText setBezeled:YES];
		[yhyeText setFrame:NSZeroRect];
		[[yhyeText cell] setFont:[NSFont systemFontOfSize:15.0f]];
		[[yhyeText cell] setTextColor:[NSColor blackColor]];
		[self addSubview:yhyeText];
		
		
		doneButton = [[NSButton alloc] init];
		[doneButton setFrame:NSZeroRect];
		[[doneButton cell] setTitle:@"转账"];
		[doneButton setTarget:self];
		[doneButton setAction:@selector(doneButtonClick)];
		[self addSubview:doneButton];
        
        doneButton1 = [[NSButton alloc] init];
        [doneButton1 setFrame:NSZeroRect];
        [[doneButton1 cell] setTitle:@"资金归集"];
        [doneButton1 setTarget:self];
        [doneButton1 setAction:@selector(doneButtonClickZJGJ)];
        [self addSubview:doneButton1];
        
        doneButton2 = [[NSButton alloc] init];
        [doneButton2 setFrame:NSZeroRect];
        [[doneButton2 cell] setTitle:@"转账"];
        [doneButton2 setTarget:self];
        [doneButton2 setAction:@selector(doneButtonClickDZJZZ)];
        [self addSubview:doneButton2];
        
        stryhlsh=nil;
        nyhyecount=0;
		
	}
	return self;
}

-(void) setFrame:(NSRect)frameRect{
	[super setFrame:frameRect];
	viewRect = frameRect;
    [self dealOutLook];
}

-(void) doneButtonClick{
	[eGetData.clientinfos jyhasoper];
	if([self IsCanQueryOther]==NO)
		return;
	[self doYzzz];
}

-(void) doneButtonClickZJGJ{
    nZJZZ = ZJGJ_BTN_FLAG;
    [eGetData.clientinfos jyhasoper];
    if([self IsCanQueryOther]==NO)
        return;
    [self doYzzz3];
}

-(void) doneButtonClickDZJZZ{
    nZJZZ = DZJZZ_BTN_FLAG;
    [eGetData.clientinfos jyhasoper];
    if([self IsCanQueryOther]==NO)
        return;
    [self doYzzz3];
}

- (void)onviewWillAppear{
	if(self.tag==IPHONE_WT_YHYE)
		m_bfirstyhyeflag=YES;
	else 
		m_bfirstyhyeflag=NO;

	if(m_pyhmx==nil)
    {
		if(eGetData.clientinfos.yhxxs.yhmxs && [eGetData.clientinfos.yhxxs.yhmxs count])
		{
			Yhxxmx *pyhmx=[eGetData.clientinfos.yhxxs.yhmxs objectAtIndex:0];
			if(pyhmx)
				m_pyhmx=pyhmx;
		}
	}
	
	if (m_pyhmx != nil) {
		[self dealOutLook];
	}
	else {
		NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
										 defaultButton: @"确定"
									   alternateButton: nil
										   otherButton: nil
							 informativeTextWithFormat: @"未查到可用银行信息"];
		[alert runModal];
	}

}

-(void)dealOutLook{
	float tempFloat = viewRect.size.height - TOPMARIN - PER_LABEL_HEIGHT;
    
    [zczhLabel setFrame:NSZeroRect];
    [zczhComboBox setFrame:NSZeroRect];
    [zrzhLabel setFrame:NSZeroRect];
    [zrzhComboBox setFrame:NSZeroRect];
    [doneButton1 setFrame:NSZeroRect];
    [doneButton2 setFrame:NSZeroRect];
    
	if (self.tag == IPHONE_WT_BANKTOSEC) { //转入
		[zzfsLabel setFrame:NSMakeRect(LEFTMARIN, tempFloat, PER_LABEL_WIDTH, PER_LABEL_HEIGHT)];
		[zzfsComboBox setFrame:NSMakeRect(LEFTMARIN+PER_LABEL_WIDTH, tempFloat, PER_TEXT_WIDTH, PER_LABEL_HEIGHT)];
		[[zzfsComboBox cell] setTitle:@"银行转证券(转入)"];
		tempFloat = tempFloat - PER_LABEL_HEIGHT;
		
		[xzyhLabel setFrame:NSMakeRect(LEFTMARIN, tempFloat, PER_LABEL_WIDTH, PER_LABEL_HEIGHT)];
		[xzyhComboBox setFrame:NSMakeRect(LEFTMARIN+PER_LABEL_WIDTH, tempFloat, PER_TEXT_WIDTH, PER_LABEL_HEIGHT)];
		if (m_pyhmx.yhdm != nil && m_pyhmx.yhmc != nil) {
			[[xzyhComboBox cell] setTitle:[NSString stringWithFormat:@"%@  %@",m_pyhmx.yhdm,m_pyhmx.yhmc]];
		}
		tempFloat = tempFloat - PER_LABEL_HEIGHT;
		
		
		[[zjmmText cell] setTitle:@""];
		[[yhmmText cell] setTitle:@""];
		[[zzjeText cell] setTitle:@""];
		if (m_pyhmx.nzrmmflag == 0) {
			[zjmmLabel setFrame:NSZeroRect];
			[zjmmText setFrame:NSZeroRect];
			[yhmmLabel setFrame:NSZeroRect];
			[yhmmText setFrame:NSZeroRect];
			
			[[self window] makeFirstResponder:zzjeText];
		}
		else if(m_pyhmx.nzrmmflag == 1) {
			[yhmmLabel setFrame:NSZeroRect];
			[yhmmText setFrame:NSZeroRect];
			
			[zjmmLabel setFrame:NSMakeRect(LEFTMARIN, tempFloat, PER_LABEL_WIDTH, PER_LABEL_HEIGHT)];
			[zjmmText setFrame:NSMakeRect(LEFTMARIN+PER_LABEL_WIDTH, tempFloat, PER_TEXT_WIDTH, PER_LABEL_HEIGHT)];
			tempFloat = tempFloat - PER_LABEL_HEIGHT;
			
			[zjmmText setNextKeyView:zzjeText];
			[[self window] makeFirstResponder:zjmmText];
		}
		else if(m_pyhmx.nzrmmflag == 2) {
			[zjmmLabel setFrame:NSZeroRect];
			[zjmmText setFrame:NSZeroRect];
			
			[yhmmLabel setFrame:NSMakeRect(LEFTMARIN, tempFloat, PER_LABEL_WIDTH, PER_LABEL_HEIGHT)];
			[yhmmText setFrame:NSMakeRect(LEFTMARIN+PER_LABEL_WIDTH, tempFloat, PER_TEXT_WIDTH, PER_LABEL_HEIGHT)];
			tempFloat = tempFloat - PER_LABEL_HEIGHT;
			
//			[yhmmLabel setNextKeyView:zzjeText];
            [yhmmText setNextKeyView:zzjeText];
			[[self window] makeFirstResponder:yhmmText];

		}
		else {
			[zjmmLabel setFrame:NSMakeRect(LEFTMARIN, tempFloat, PER_LABEL_WIDTH, PER_LABEL_HEIGHT)];
			[zjmmText setFrame:NSMakeRect(LEFTMARIN+PER_LABEL_WIDTH, tempFloat, PER_TEXT_WIDTH, PER_LABEL_HEIGHT)];
			tempFloat = tempFloat - PER_LABEL_HEIGHT;
			
			[zjmmText setNextKeyView:yhmmText];
			[[self window] makeFirstResponder:zjmmText];
			
			[yhmmLabel setFrame:NSMakeRect(LEFTMARIN, tempFloat, PER_LABEL_WIDTH, PER_LABEL_HEIGHT)];
			[yhmmText setFrame:NSMakeRect(LEFTMARIN+PER_LABEL_WIDTH, tempFloat, PER_TEXT_WIDTH, PER_LABEL_HEIGHT)];
			tempFloat = tempFloat - PER_LABEL_HEIGHT;	
			
			[yhmmText setNextKeyView:zzjeText];
		}
		
		if (m_bselbz) {
			[xzbzLabel setFrame:NSMakeRect(LEFTMARIN, tempFloat, PER_LABEL_WIDTH, PER_LABEL_HEIGHT)];
			[xzbzComboBox setFrame:NSMakeRect(LEFTMARIN+PER_LABEL_WIDTH, tempFloat, PER_TEXT_WIDTH, PER_LABEL_HEIGHT)];
			[[xzbzComboBox cell] setTitle:((m_pyhmx && m_pyhmx.nbz>=0 && m_pyhmx.nbz<[moneyTypeArray count])?[moneyTypeArray objectAtIndex:m_pyhmx.nbz]:@"人民币")];
			tempFloat = tempFloat - PER_LABEL_HEIGHT;
		}
		else {
			[xzbzLabel setFrame:NSZeroRect];
			[xzbzComboBox setFrame:NSZeroRect];
		}
		
		[yhyeLabel setFrame:NSZeroRect];
		[yhyeText setFrame:NSZeroRect];
		
		[zzjeLabel setFrame:NSMakeRect(LEFTMARIN, tempFloat, PER_LABEL_WIDTH, PER_LABEL_HEIGHT)];
		[zzjeText setFrame:NSMakeRect(LEFTMARIN+PER_LABEL_WIDTH, tempFloat, PER_TEXT_WIDTH, PER_LABEL_HEIGHT)];
		tempFloat = tempFloat - PER_LABEL_HEIGHT;
		
		[[doneButton cell] setTitle:@"转 账"];
		[doneButton setFrame:NSMakeRect(LEFTMARIN+PER_TEXT_WIDTH, tempFloat-5, PER_LABEL_WIDTH, PER_LABEL_HEIGHT)];
	}
	else if(self.tag == IPHONE_WT_SECTOBANK) { //转出
		[zzfsLabel setFrame:NSMakeRect(LEFTMARIN, tempFloat, PER_LABEL_WIDTH, PER_LABEL_HEIGHT)];
		[zzfsComboBox setFrame:NSMakeRect(LEFTMARIN+PER_LABEL_WIDTH, tempFloat, PER_TEXT_WIDTH, PER_LABEL_HEIGHT)];
		[[zzfsComboBox cell] setTitle:@"证券转银行(转出)"];
		tempFloat = tempFloat - PER_LABEL_HEIGHT;
		
		[xzyhLabel setFrame:NSMakeRect(LEFTMARIN, tempFloat, PER_LABEL_WIDTH, PER_LABEL_HEIGHT)];
		[xzyhComboBox setFrame:NSMakeRect(LEFTMARIN+PER_LABEL_WIDTH, tempFloat, PER_TEXT_WIDTH, PER_LABEL_HEIGHT)];
		if (m_pyhmx.yhdm != nil && m_pyhmx.yhmc != nil) {
			[[xzyhComboBox cell] setTitle:[NSString stringWithFormat:@"%@  %@",m_pyhmx.yhdm,m_pyhmx.yhmc]];
		}
		tempFloat = tempFloat - PER_LABEL_HEIGHT;
		
		
		[[zjmmText cell] setTitle:@""];
		[[yhmmText cell] setTitle:@""];
		[[zzjeText cell] setTitle:@""];
		if (m_pyhmx.nzcmmflag == 0) {
			[zjmmLabel setFrame:NSZeroRect];
			[zjmmText setFrame:NSZeroRect];
			[yhmmLabel setFrame:NSZeroRect];
			[yhmmText setFrame:NSZeroRect];
			
			[[self window] makeFirstResponder:zzjeText];
		}
		else if(m_pyhmx.nzcmmflag == 1) {
			[yhmmLabel setFrame:NSZeroRect];
			[yhmmText setFrame:NSZeroRect];
			
			[zjmmLabel setFrame:NSMakeRect(LEFTMARIN, tempFloat, PER_LABEL_WIDTH, PER_LABEL_HEIGHT)];
			[zjmmText setFrame:NSMakeRect(LEFTMARIN+PER_LABEL_WIDTH, tempFloat, PER_TEXT_WIDTH, PER_LABEL_HEIGHT)];
			tempFloat = tempFloat - PER_LABEL_HEIGHT;
			
			[zjmmText setNextKeyView:zzjeText];
			[[self window] makeFirstResponder:zjmmText];

		}
		else if(m_pyhmx.nzcmmflag == 2) {
			[zjmmLabel setFrame:NSZeroRect];
			[zjmmText setFrame:NSZeroRect];
			
			[yhmmLabel setFrame:NSMakeRect(LEFTMARIN, tempFloat, PER_LABEL_WIDTH, PER_LABEL_HEIGHT)];
			[yhmmText setFrame:NSMakeRect(LEFTMARIN+PER_LABEL_WIDTH, tempFloat, PER_TEXT_WIDTH, PER_LABEL_HEIGHT)];
			tempFloat = tempFloat - PER_LABEL_HEIGHT;
			
			[yhmmLabel setNextKeyView:zzjeText];
			[[self window] makeFirstResponder:yhmmLabel];
		}
		else {
			[zjmmLabel setFrame:NSMakeRect(LEFTMARIN, tempFloat, PER_LABEL_WIDTH, PER_LABEL_HEIGHT)];
			[zjmmText setFrame:NSMakeRect(LEFTMARIN+PER_LABEL_WIDTH, tempFloat, PER_TEXT_WIDTH, PER_LABEL_HEIGHT)];
			tempFloat = tempFloat - PER_LABEL_HEIGHT;
			
			[zjmmText setNextKeyView:yhmmText];
			[[self window] makeFirstResponder:zjmmText];
			
			[yhmmLabel setFrame:NSMakeRect(LEFTMARIN, tempFloat, PER_LABEL_WIDTH, PER_LABEL_HEIGHT)];
			[yhmmText setFrame:NSMakeRect(LEFTMARIN+PER_LABEL_WIDTH, tempFloat, PER_TEXT_WIDTH, PER_LABEL_HEIGHT)];
			tempFloat = tempFloat - PER_LABEL_HEIGHT;		
			
			[yhmmText setNextKeyView:zzjeText];
		}
		
		if (m_bselbz) {
			[xzbzLabel setFrame:NSMakeRect(LEFTMARIN, tempFloat, PER_LABEL_WIDTH, PER_LABEL_HEIGHT)];
			[xzbzComboBox setFrame:NSMakeRect(LEFTMARIN+PER_LABEL_WIDTH, tempFloat, PER_TEXT_WIDTH, PER_LABEL_HEIGHT)];
			[[xzbzComboBox cell] setTitle:((m_pyhmx && m_pyhmx.nbz>=0 && m_pyhmx.nbz<[moneyTypeArray count])?[moneyTypeArray objectAtIndex:m_pyhmx.nbz]:@"人民币")];
			tempFloat = tempFloat - PER_LABEL_HEIGHT;
		}
		else {
			[xzbzLabel setFrame:NSZeroRect];
			[xzbzComboBox setFrame:NSZeroRect];
		}
		
		[zzjeLabel setFrame:NSMakeRect(LEFTMARIN, tempFloat, PER_LABEL_WIDTH, PER_LABEL_HEIGHT)];
		[zzjeText setFrame:NSMakeRect(LEFTMARIN+PER_LABEL_WIDTH, tempFloat, PER_TEXT_WIDTH, PER_LABEL_HEIGHT)];
		tempFloat = tempFloat - PER_LABEL_HEIGHT;
		
		[yhyeLabel setFrame:NSZeroRect];
		[yhyeText setFrame:NSZeroRect];
		
		[[doneButton cell] setTitle:@"转 账"];
		[doneButton setFrame:NSMakeRect(LEFTMARIN+PER_TEXT_WIDTH, tempFloat-5, PER_LABEL_WIDTH, PER_LABEL_HEIGHT)];
		
	}
	else if(self.tag == IPHONE_WT_YHYE) { //余额查询
        
        [zzfsLabel setFrame:NSZeroRect];
        [zzfsComboBox setFrame:NSZeroRect];
        [doneButton1 setFrame:NSZeroRect];
        [doneButton2 setFrame:NSZeroRect];
		
		[xzyhLabel setFrame:NSMakeRect(LEFTMARIN, tempFloat, PER_LABEL_WIDTH, PER_LABEL_HEIGHT)];
		[xzyhComboBox setFrame:NSMakeRect(LEFTMARIN+PER_LABEL_WIDTH, tempFloat, PER_TEXT_WIDTH, PER_LABEL_HEIGHT)];
		if (m_pyhmx.yhdm != nil && m_pyhmx.yhmc != nil) {
			[[xzyhComboBox cell] setTitle:[NSString stringWithFormat:@"%@  %@",m_pyhmx.yhdm,m_pyhmx.yhmc]];
		}
		tempFloat = tempFloat - PER_LABEL_HEIGHT;
		
		
		[[zjmmText cell] setTitle:@""];
		[[yhmmText cell] setTitle:@""];
		[[zzjeText cell] setTitle:@""];
		if (m_pyhmx.nyemmflag == 0) {
			[zjmmLabel setFrame:NSZeroRect];
			[zjmmText setFrame:NSZeroRect];
			[yhmmLabel setFrame:NSZeroRect];
			[yhmmText setFrame:NSZeroRect];
			
			[[self window] makeFirstResponder:doneButton];
		}
		else if(m_pyhmx.nyemmflag == 1) {
			[yhmmLabel setFrame:NSZeroRect];
			[yhmmText setFrame:NSZeroRect];
			
			[zjmmLabel setFrame:NSMakeRect(LEFTMARIN, tempFloat, PER_LABEL_WIDTH, PER_LABEL_HEIGHT)];
			[zjmmText setFrame:NSMakeRect(LEFTMARIN+PER_LABEL_WIDTH, tempFloat, PER_TEXT_WIDTH, PER_LABEL_HEIGHT)];
			tempFloat = tempFloat - PER_LABEL_HEIGHT;
			
			[zjmmText setNextKeyView:doneButton];
			[[self window] makeFirstResponder:zjmmText];
		}
		else if(m_pyhmx.nyemmflag == 2) {
			[zjmmLabel setFrame:NSZeroRect];
			[zjmmText setFrame:NSZeroRect];
			
			[yhmmLabel setFrame:NSMakeRect(LEFTMARIN, tempFloat, PER_LABEL_WIDTH, PER_LABEL_HEIGHT)];
			[yhmmText setFrame:NSMakeRect(LEFTMARIN+PER_LABEL_WIDTH, tempFloat, PER_TEXT_WIDTH, PER_LABEL_HEIGHT)];
			tempFloat = tempFloat - PER_LABEL_HEIGHT;
			
			[yhmmLabel setNextKeyView:doneButton];
			[[self window] makeFirstResponder:yhmmLabel];
		}
		else {
			[zjmmLabel setFrame:NSMakeRect(LEFTMARIN, tempFloat, PER_LABEL_WIDTH, PER_LABEL_HEIGHT)];
			[zjmmText setFrame:NSMakeRect(LEFTMARIN+PER_LABEL_WIDTH, tempFloat, PER_TEXT_WIDTH, PER_LABEL_HEIGHT)];
			tempFloat = tempFloat - PER_LABEL_HEIGHT;
			
			[zjmmText setNextKeyView:yhmmText];
			[[self window] makeFirstResponder:zjmmText];
			
			
			[yhmmLabel setFrame:NSMakeRect(LEFTMARIN, tempFloat, PER_LABEL_WIDTH, PER_LABEL_HEIGHT)];
			[yhmmText setFrame:NSMakeRect(LEFTMARIN+PER_LABEL_WIDTH, tempFloat, PER_TEXT_WIDTH, PER_LABEL_HEIGHT)];
			tempFloat = tempFloat - PER_LABEL_HEIGHT;	
			
			[yhmmText setNextKeyView:doneButton];
		}
		
		if (m_bselbz) {
			[xzbzLabel setFrame:NSMakeRect(LEFTMARIN, tempFloat, PER_LABEL_WIDTH, PER_LABEL_HEIGHT)];
			[xzbzComboBox setFrame:NSMakeRect(LEFTMARIN+PER_LABEL_WIDTH, tempFloat, PER_TEXT_WIDTH, PER_LABEL_HEIGHT)];
			[[xzbzComboBox cell] setTitle:((m_pyhmx && m_pyhmx.nbz>=0 && m_pyhmx.nbz<[moneyTypeArray count])?[moneyTypeArray objectAtIndex:m_pyhmx.nbz]:@"人民币")];
			tempFloat = tempFloat - PER_LABEL_HEIGHT;
		}
		else {
			[xzbzLabel setFrame:NSZeroRect];
			[xzbzComboBox setFrame:NSZeroRect];
		}
		
		[zzjeLabel setFrame:NSZeroRect];
		[zzjeText setFrame:NSZeroRect];
		
		[yhyeLabel setFrame:NSMakeRect(LEFTMARIN, tempFloat, PER_LABEL_WIDTH, PER_LABEL_HEIGHT)];
		[yhyeText setFrame:NSMakeRect(LEFTMARIN+PER_LABEL_WIDTH, tempFloat, PER_TEXT_WIDTH, PER_LABEL_HEIGHT)];
		tempFloat = tempFloat - PER_LABEL_HEIGHT;
		
		[[doneButton cell] setTitle:@"查 询"];
		[doneButton setFrame:NSMakeRect(LEFTMARIN+PER_TEXT_WIDTH, tempFloat-5, PER_LABEL_WIDTH, PER_LABEL_HEIGHT)];
		
	}
    else if(self.tag == IPHONE_WT_ZJZZ) { //资金转账
        
        [zzfsLabel setFrame:NSZeroRect];
        [zzfsComboBox setFrame:NSZeroRect];
        [xzyhLabel setFrame:NSZeroRect];
        [xzyhComboBox setFrame:NSZeroRect];
        [zjmmLabel setFrame:NSZeroRect];
        [zjmmText setFrame:NSZeroRect];
        [yhmmLabel setFrame:NSZeroRect];
        [yhmmText setFrame:NSZeroRect];
        [doneButton setFrame:NSZeroRect];
        
        [zczhLabel setFrame:NSMakeRect(LEFTMARIN, tempFloat, PER_LABEL_WIDTH, PER_LABEL_HEIGHT)];
        [zczhComboBox setFrame:NSMakeRect(LEFTMARIN+PER_LABEL_WIDTH, tempFloat, PER_TEXT_WIDTH, PER_LABEL_HEIGHT)];
        if (m_pyhmx.yhdm != nil && m_pyhmx.yhmc != nil) {
            [[zczhComboBox cell] setTitle:m_pyhmx.zjzh];
        }
        tempFloat = tempFloat - PER_LABEL_HEIGHT;
        
        [zrzhLabel setFrame:NSMakeRect(LEFTMARIN, tempFloat, PER_LABEL_WIDTH, PER_LABEL_HEIGHT)];
        [zrzhComboBox setFrame:NSMakeRect(LEFTMARIN+PER_LABEL_WIDTH, tempFloat, PER_TEXT_WIDTH, PER_LABEL_HEIGHT)];
        if (m_pyhmx.yhdm != nil && m_pyhmx.yhmc != nil) {
            [[zrzhComboBox cell] setTitle:m_pyhmx.zjzh];
        }
        tempFloat = tempFloat - PER_LABEL_HEIGHT;
        
        [[zjmmText cell] setTitle:@""];
        [[yhmmText cell] setTitle:@""];
        [[zzjeText cell] setTitle:@""];
        if (m_pyhmx.nzrmmflag == 0)
        {
            [zjmmLabel setFrame:NSZeroRect];
            [zjmmText setFrame:NSZeroRect];
            [yhmmLabel setFrame:NSZeroRect];
            [yhmmText setFrame:NSZeroRect];
            
            [[self window] makeFirstResponder:zzjeText];
        }
        
        [xzbzLabel setFrame:NSMakeRect(LEFTMARIN, tempFloat, PER_LABEL_WIDTH, PER_LABEL_HEIGHT)];
        [xzbzComboBox setFrame:NSMakeRect(LEFTMARIN+PER_LABEL_WIDTH, tempFloat, PER_TEXT_WIDTH, PER_LABEL_HEIGHT)];
        [[xzbzComboBox cell] setTitle:((m_pyhmx && m_pyhmx.nbz>=0 && m_pyhmx.nbz<[moneyTypeArray count])?[moneyTypeArray objectAtIndex:m_pyhmx.nbz]:@"人民币")];
        tempFloat = tempFloat - PER_LABEL_HEIGHT;
        
        [yhyeLabel setFrame:NSZeroRect];
        [yhyeText setFrame:NSZeroRect];
        
        [zzjeLabel setFrame:NSMakeRect(LEFTMARIN, tempFloat, PER_LABEL_WIDTH, PER_LABEL_HEIGHT)];
        [zzjeText setFrame:NSMakeRect(LEFTMARIN+PER_LABEL_WIDTH, tempFloat, PER_TEXT_WIDTH, PER_LABEL_HEIGHT)];
        tempFloat = tempFloat - PER_LABEL_HEIGHT;
        
        [[doneButton1 cell] setTitle:@"资金归集"];
        [doneButton1 setFrame:NSMakeRect(LEFTMARIN+PER_LABEL_HEIGHT, tempFloat-5, PER_LABEL_WIDTH, PER_LABEL_HEIGHT)];
        
        [[doneButton2 cell] setTitle:@"转  账"];
        [doneButton2 setFrame:NSMakeRect(LEFTMARIN+PER_TEXT_WIDTH, tempFloat-5, PER_LABEL_WIDTH, PER_LABEL_HEIGHT)];
    }
}


- (void)drawRect:(NSRect)dirtyRect {
    // Drawing code here.
}
#pragma mark combobox Delegate相关
-(NSInteger) numberOfItemsInComboBox:(NSComboBox *)aComboBox{
    if (aComboBox.tag == ZZFS_COM_FLAG) {
		return 2;
	}
	
	else if(aComboBox.tag == XZYH_COM_FLAG
            || aComboBox.tag == ZCZH_COM_FLAG
            || aComboBox.tag == ZRZH_COM_FLAG){
		
		return [eGetData.clientinfos.yhxxs.yhmxs count];
	}
	
	else if(aComboBox.tag == XZBZ_COM_FLAG){
		return 3;
	}
	
	return 0;
}

-(id) comboBox:(NSComboBox *)aComboBox objectValueForItemAtIndex:(NSInteger)index{
	if (aComboBox.tag == ZZFS_COM_FLAG) {


		return [zzfxArray objectAtIndex:index];
	}
	else if (aComboBox.tag == XZYH_COM_FLAG){
		Yhxxmx *pyhmx=[eGetData.clientinfos.yhxxs.yhmxs objectAtIndex:index];
		NSString *tmpstr=[NSString stringWithFormat:@"%@  %@",pyhmx.yhdm,pyhmx.yhmc];
		return tmpstr;
	}
    else if(aComboBox.tag == ZCZH_COM_FLAG
            || aComboBox.tag == ZRZH_COM_FLAG)
    {
        Yhxxmx *pyhmx=[eGetData.clientinfos.yhxxs.yhmxs objectAtIndex:index];
        NSString *tmpstr=pyhmx.zjzh;
        return tmpstr;
    }
	else if(aComboBox.tag == XZBZ_COM_FLAG){
		return [moneyTypeArray objectAtIndex:index];
	}
	
	return nil;
}

-(void) comboBoxSelectionDidChange:(NSNotification *)notification{
	[self cleanscreen];
	NSComboBox * tempCombobox = [notification object];
	int tempInt ;
	tempInt = [tempCombobox indexOfSelectedItem];
	if (tempCombobox.tag == ZZFS_COM_FLAG) {
		if (tempInt == 0) {
			[self setTag:IPHONE_WT_BANKTOSEC];
			[self dealOutLook];
		}
		else {
			[self setTag:IPHONE_WT_SECTOBANK];
			[self dealOutLook];
		}

	}
	else if (tempCombobox.tag == XZYH_COM_FLAG){
        Yhxxmx *pyhmx=nil;
        if(tempInt>=0 && tempInt<[eGetData.clientinfos.yhxxs.yhmxs count])
            pyhmx=[eGetData.clientinfos.yhxxs.yhmxs objectAtIndex:tempInt];
		if(pyhmx)
			m_pyhmx=pyhmx;
		if (m_pyhmx != nil) {
			[self dealOutLook];
		}
	}
	else if(tempCombobox.tag == XZBZ_COM_FLAG){
	
	}
	
}

#pragma mark focusDelegate
-(void)getFocus:(int)_tag{

}


-(void)getEnter:(int)_tag{
	switch (_tag) {
		case ZJMM_TEXT_FLAG:{
			if (self.tag == IPHONE_WT_BANKTOSEC) {
				if (m_pyhmx.nzrmmflag > 1) {
					[[self window] makeFirstResponder:yhmmText];
				}
				else {
					[[self window] makeFirstResponder:zzjeText];
				}
			}
			else if(self.tag == IPHONE_WT_SECTOBANK){
				if (m_pyhmx.nzcmmflag > 1) {
					[[self window] makeFirstResponder:yhmmText];
				}
				else {
					[[self window] makeFirstResponder:zzjeText];
				}
			}
			else if(self.tag == IPHONE_WT_YHYE){
				if (m_pyhmx.nyemmflag > 1) {
					[[self window] makeFirstResponder:yhmmText];
				}
				else {
					[[self window] makeFirstResponder:doneButton];
					[self doneButtonClick];
				}
			}
		}
			break;
		case YHMM_TEXT_FLAG:{
			if (self.tag == IPHONE_WT_BANKTOSEC) {
				[[self window] makeFirstResponder:zzjeText];
			}
			else if(self.tag == IPHONE_WT_SECTOBANK){
				[[self window] makeFirstResponder:zzjeText];
			}
			else if(self.tag == IPHONE_WT_YHYE){
				[[self window] makeFirstResponder:doneButton];
				[self doneButtonClick];
			}
		}
			break;
		case ZZJE_TEXT_FLAG:{
			[[self window] makeFirstResponder:doneButton];
			[self doneButtonClick];
		}
			break;		
		default:
			break;
	}
}


-(void)getEsc:(int)_tag{
}

-(void)getKeyUp:(NSEvent *)theEvent{
}
#pragma mark 数据相关

-(void)startanimate
{
	m_bbusy=YES;
	[doneButton setEnabled:NO];
	[zjmmText setEnabled:NO];
	[yhmmText setEnabled:NO];
	[zzjeText setEnabled:NO];
	[zzfsComboBox setEnabled:NO];
	[xzyhComboBox setEnabled:NO];
	[xzbzComboBox setEnabled:NO];
}

-(void)stopanimate
{
	if(m_bbusy)
	{
		[doneButton setEnabled:YES];
		[zjmmText setEnabled:YES];
		[yhmmText setEnabled:YES];
		[zzjeText setEnabled:YES];
		[zzfsComboBox setEnabled:YES];
		[xzyhComboBox setEnabled:YES];
		[xzbzComboBox setEnabled:YES];
		
		m_bbusy=NO;
	}
}

-(BOOL)IsCanQueryOther
{
	return !m_bbusy;
}
-(void)cleanscreen
{
	[[zjmmText cell] setTitle:@""];
	[[yhmmText cell] setTitle:@""];
	[[yhyeText cell] setTitle:@""];
	[[zzjeText cell] setTitle:@""];
}

-(int)GetBzIndex:(NSString *)bzstr
{
	int i=0;
	for(NSString *pbzstr in moneyTypeArray)
	{
		if([pbzstr isEqualToString:bzstr])
			return i;
		i++;
	}
	return 0;
}

-(int)GetZzfxIndex:(NSString *)zzfxstr
{
	int i=0;
	for(NSString *pbzstr in zzfxArray)
	{
		if([pbzstr isEqualToString:zzfxstr])
			return i;
		i++;
	}
	return 0;
}	  

-(void)doYzzz
{
    if([self IsCanQueryOther]==NO)
        return;
	Yhxxmx *pyhmx=[eGetData.clientinfos.yhxxs GetYhmxFromYhmc:[[xzyhComboBox cell] title]];
	if(pyhmx==nil)
	{
		NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
										 defaultButton: @"确定"
									   alternateButton: nil
										   otherButton: nil
							 informativeTextWithFormat: @"没有对应的银行信息"];
		[alert setDelegate:self];
		NSInteger result = [alert runModal];
		[self handleResult:alert withResult:result withTag:1];	
		return;
	}
	
	if(tag == IPHONE_WT_BANKTOSEC)
	{
		if((m_pyhmx.nzrmmflag!=0 && m_pyhmx.nzrmmflag!=1 ) && [[[yhmmText cell] title] length] == 0)
		{
			NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
											 defaultButton: @"确定"
										   alternateButton: nil
											   otherButton: nil
								 informativeTextWithFormat: @"请输入银行密码"];
			[alert setDelegate:self];
			NSInteger result = [alert runModal];
			[self handleResult:alert withResult:result withTag:2];	
			return;
		}
		else if((m_pyhmx.nzrmmflag!=0 && m_pyhmx.nzrmmflag!=2 ) && [[[zjmmText cell] title] length] == 0)
		{
			NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
											 defaultButton: @"确定"
										   alternateButton: nil
											   otherButton: nil
								 informativeTextWithFormat: @"请输入资金密码"];
			[alert setDelegate:self];
			NSInteger result = [alert runModal];
			[self handleResult:alert withResult:result withTag:3];	
			return;
		}
	}
	if(tag == IPHONE_WT_SECTOBANK)
	{
		if((m_pyhmx.nzcmmflag!=0 && m_pyhmx.nzcmmflag!=1 ) && [[[yhmmText cell] title] length] == 0)
		{
			NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
											 defaultButton: @"确定"
										   alternateButton: nil
											   otherButton: nil
								 informativeTextWithFormat: @"请输入银行密码"];
			[alert setDelegate:self];
			NSInteger result = [alert runModal];
			[self handleResult:alert withResult:result withTag:2];	
			return;
		}
		else if((m_pyhmx.nzcmmflag!=0 && m_pyhmx.nzcmmflag!=2 ) && [[[zjmmText cell] title] length] == 0)
		{
			NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
											 defaultButton: @"确定"
										   alternateButton: nil
											   otherButton: nil
								 informativeTextWithFormat: @"请输入资金密码"];
			[alert setDelegate:self];
			NSInteger result = [alert runModal];
			[self handleResult:alert withResult:result withTag:3];	
			return;
		}
	}
	if(tag == IPHONE_WT_YHYE)
	{
		if((m_pyhmx.nyemmflag!=0 && m_pyhmx.nyemmflag!=1 ) &&  [[[yhmmText cell] title] length] == 0)
		{
			NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
											 defaultButton: @"确定"
										   alternateButton: nil
											   otherButton: nil
								 informativeTextWithFormat: @"请输入银行密码"];
			[alert setDelegate:self];
			NSInteger result = [alert runModal];
			[self handleResult:alert withResult:result withTag:2];	
			return;
		}
		else if((m_pyhmx.nyemmflag!=0 && m_pyhmx.nyemmflag!=2 ) && [[[zjmmText cell] title] length] == 0)
		{
			NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
											 defaultButton: @"确定"
										   alternateButton: nil
											   otherButton: nil
								 informativeTextWithFormat: @"请输入资金密码"];
			[alert setDelegate:self];
			NSInteger result = [alert runModal];
			[self handleResult:alert withResult:result withTag:3];	
			return;
		}
	}

	[NSTimer scheduledTimerWithTimeInterval: 0.0f target:self selector: @selector(doYzzz1) userInfo: nil repeats: NO];
}

-(void)doYzzz3
{
    if([self IsCanQueryOther]==NO)
        return;
    Yhxxmx *pyhmx=[eGetData.clientinfos.yhxxs GetYhmxFromzjzh:[[zczhComboBox cell] title]];
    if(pyhmx==nil)
    {
        NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
                                         defaultButton: @"确定"
                                       alternateButton: nil
                                           otherButton: nil
                             informativeTextWithFormat: @"没有对应的帐号信息"];
        [alert setDelegate:self];
        NSInteger result = [alert runModal];
        [self handleResult:alert withResult:result withTag:1];
        return;
    }
    
    if (nZJZZ == DZJZZ_BTN_FLAG)
    {
        if([[[zzjeText cell] title] length] == 0)
        {
            NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
                                             defaultButton: @"确定"
                                           alternateButton: nil
                                               otherButton: nil
                                 informativeTextWithFormat: @"请输入转账金额"];
            [alert setDelegate:self];
            NSInteger result = [alert runModal];
            [self handleResult:alert withResult:result withTag:2];
            return;
        }
    }

    [NSTimer scheduledTimerWithTimeInterval: 0.0f target:self selector: @selector(doYzzz1) userInfo: nil repeats: NO];
}

-(void)doYzzz1
{
	if(tag == IPHONE_WT_YHYE)//银行余额查询
	{
		[self startanimate];
		Yhxxmx *pyhmx=[eGetData.clientinfos.yhxxs GetYhmxFromYhmc:[[xzyhComboBox cell] title]];
        signed char bczbzflag=NO;
#ifdef IMAC_ZXJT
        bczbzflag=YES;
#endif
#ifdef IMAC_GXZQ
        bczbzflag=YES;
#endif
        if(bczbzflag)
        {
            [eGetData sendTradeBankData2:TDX_YHYE objIndex:self.tradeindex Session:eGetData.inputSave.sessionID SecPassword:[[zjmmText cell]title] TransferType:0 BankCode:pyhmx.yhdm BankPassword:[[yhmmText cell] title] MoneyNum:0 BankID:pyhmx.yhzh MoneyType:(m_bselbz?[self GetBzIndex:[[xzbzComboBox cell]title]]:pyhmx.nbz) czbz:0 yhlsh:@""];
        }
        else
        {
            [eGetData sendTradeBankData:TDX_YHYE objIndex:self.tradeindex Session:eGetData.inputSave.sessionID SecPassword:[[zjmmText cell]title] TransferType:0 BankCode:pyhmx.yhdm BankPassword:[[yhmmText cell] title] MoneyNum:0 BankID:pyhmx.yhzh MoneyType:(m_bselbz?[self GetBzIndex:[[xzbzComboBox cell]title]]:pyhmx.nbz)];
        }
		
	}
    else if(tag == IPHONE_WT_ZJZZ)
    {
        if(nZJZZ == ZJGJ_BTN_FLAG) //资金归集
        {
            NSString * tempString;
            tempString = [NSString stringWithFormat:@"请确认以下信息:\r\r您确定将所有资金账号上的资金归集到 %@ 吗？\r",[[zczhComboBox cell] title]];
            
            m_bfirstalertflag=YES;
            
            NSAlert* alert = [NSAlert alertWithMessageText:@"资金归集提示"
                                             defaultButton: @"确定"
                                           alternateButton:@"取消"
                                               otherButton: nil
                                 informativeTextWithFormat: @"%@",tempString];
            [alert setDelegate:self];
            NSInteger result = [alert runModal];
            [self handleResult:alert withResult:result withTag:100];
        }
        else //多资金帐号转账
        {
            NSString * tempString;
            tempString = [NSString stringWithFormat:@"您确定将 %@ 的资金%@元转到 %@ 吗？\r",[[zczhComboBox cell] title], [[zzjeText cell] title],[[zczhComboBox cell] title]];
            
            m_bfirstalertflag=YES;
            
            NSAlert* alert = [NSAlert alertWithMessageText:@"转帐提示"
                                             defaultButton: @"确定"
                                           alternateButton:@"取消"
                                               otherButton: nil
                                 informativeTextWithFormat: @"%@",tempString];
            [alert setDelegate:self];
            NSInteger result = [alert runModal];
            [self handleResult:alert withResult:result withTag:101];
        }
    }
    else //转账
	{
		if(([[[zzjeText cell] title] length] == 0)||([[[zzjeText cell] title] floatValue] == 0)){
			NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
											 defaultButton: @"确定"
										   alternateButton: nil
											   otherButton: nil
								 informativeTextWithFormat: @"请输入转账金额"];
			[alert setDelegate:self];
			NSInteger result = [alert runModal];
			[self handleResult:alert withResult:result withTag:4];	
		}else{
			NSString * tempString ;
			if(tag == IPHONE_WT_BANKTOSEC)
				tempString = [NSString stringWithFormat:@"请确认以下信息:\r\r操作类别:   银行转证券(转入)\r银      行:   %@\r转入金额:   %@ %@\r",m_pyhmx.yhmc,[[zzjeText cell] title],(m_pyhmx?[eGetData GetBzDesc:[m_pyhmx GetBzStr]]:@"")];
			else                                                                
				tempString = [NSString stringWithFormat:@"请确认以下信息:\r\r操作类别:   证券转银行(转出)\r银      行:   %@\r转出金额:   %@ %@\r",m_pyhmx.yhmc,[[zzjeText cell] title],(m_pyhmx?[eGetData GetBzDesc:[m_pyhmx GetBzStr]]:@"")];
			m_bfirstalertflag=YES;
			
			NSAlert* alert = [NSAlert alertWithMessageText:@"转帐提示"
											 defaultButton: @"确定"
										   alternateButton:@"取消"
											   otherButton: nil
								 informativeTextWithFormat: @"%@",tempString];
			[alert setDelegate:self];
			NSInteger result = [alert runModal];
			[self handleResult:alert withResult:result withTag:0];	
		}	
	}	
}

-(void)doYzzz2
{
	Yhxxmx *pyhmx=[eGetData.clientinfos.yhxxs GetYhmxFromYhmc:[[xzyhComboBox cell] title]];
	if(pyhmx==nil)
	{
		NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
										 defaultButton: @"确定"
									   alternateButton: nil
										   otherButton: nil
							 informativeTextWithFormat: @"没有对应的银行信息"];
		[alert setDelegate:self];
		NSInteger result = [alert runModal];
		[self handleResult:alert withResult:result withTag:1];	
		[self stopanimate];
		return;
	}
	[self startanimate];
	[eGetData sendTradeBankData:TDX_YZZZ objIndex:self.tradeindex Session:eGetData.inputSave.sessionID SecPassword:[[zjmmText cell]title] TransferType:((tag==IPHONE_WT_BANKTOSEC)?0:1) BankCode:pyhmx.yhdm BankPassword:[[yhmmText cell]title] MoneyNum:[[zzjeText cell] title]  BankID:pyhmx.yhzh MoneyType:(m_bselbz?[self GetBzIndex:[[xzbzComboBox cell]title]]:pyhmx.nbz)];
    
#ifdef IMAC_GXZQ
    [[zzjeText cell] setTitle:@""];
#endif
}

-(void)doYzzz4
{
    Yhxxmx *pyhmx=[eGetData.clientinfos.yhxxs GetYhmxFromzjzh:[[zczhComboBox cell] title]];
    if(pyhmx==nil)
    {
        NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
                                         defaultButton: @"确定"
                                       alternateButton: nil
                                           otherButton: nil
                             informativeTextWithFormat: @"没有对应的帐号信息"];
        [alert setDelegate:self];
        NSInteger result = [alert runModal];
        [self handleResult:alert withResult:result withTag:1];
        [self stopanimate];
        return;
    }
    
    if(nZJZZ == ZJGJ_BTN_FLAG)
    {
        [self startanimate];
        [eGetData sendTradeBankData:TDX_PT_DZJZJGJ objIndex:self.tradeindex Session:eGetData.inputSave.sessionID SecPassword:nil TransferType:((tag==IPHONE_WT_BANKTOSEC)?0:1) BankCode:[[zczhComboBox cell] title] BankPassword:[[zrzhComboBox cell] title] MoneyNum:nil  BankID:nil MoneyType:(m_bselbz?[self GetBzIndex:[[xzbzComboBox cell]title]]:pyhmx.nbz)];
    }
    else
    {
        Yhxxmx *pyhmxzc=[eGetData.clientinfos.yhxxs GetYhmxFromzjzh:[[zrzhComboBox cell] title]];
        if(pyhmxzc==nil)
        {
            NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
                                             defaultButton: @"确定"
                                           alternateButton: nil
                                               otherButton: nil
                                 informativeTextWithFormat: @"没有对应的帐号信息"];
            [alert setDelegate:self];
            NSInteger result = [alert runModal];
            [self handleResult:alert withResult:result withTag:1];
            [self stopanimate];
            return;
        }
        
        [self startanimate];
        [eGetData sendTradeBankData:TDX_PT_DZJZZ objIndex:self.tradeindex Session:eGetData.inputSave.sessionID SecPassword:nil TransferType:((tag==IPHONE_WT_BANKTOSEC)?0:1) BankCode:[[zczhComboBox cell] title] BankPassword:[[zrzhComboBox cell] title] MoneyNum:[[zzjeText cell] title]  BankID:nil MoneyType:(m_bselbz?[self GetBzIndex:[[xzbzComboBox cell]title]]:pyhmx.nbz)];
    }
    

    
#ifdef IMAC_GXZQ
    [[zzjeText cell] setTitle:@""];
#endif
}

-(void)QueryYhye
{
    Yhxxmx *pyhmx=[eGetData.clientinfos.yhxxs GetYhmxFromYhmc:[[xzyhComboBox cell] title]];
    [eGetData sendTradeBankData2:TDX_YHYE2 objIndex:self.tradeindex Session:eGetData.inputSave.sessionID SecPassword:[[zjmmText cell]title] TransferType:0 BankCode:pyhmx.yhdm BankPassword:[[yhmmText cell] title] MoneyNum:0 BankID:pyhmx.yhzh MoneyType:(m_bselbz?[self GetBzIndex:[[xzbzComboBox cell]title]]:pyhmx.nbz) czbz:1 yhlsh:stryhlsh];
}

-(void)QueryYhye2
{
    Yhxxmx *pyhmx=[eGetData.clientinfos.yhxxs GetYhmxFromYhmc:[[xzyhComboBox cell] title]];
    [eGetData sendTradeBankData2:TDX_YHYE3 objIndex:self.tradeindex Session:eGetData.inputSave.sessionID SecPassword:[[zjmmText cell]title] TransferType:0 BankCode:pyhmx.yhdm BankPassword:[[yhmmText cell] title] MoneyNum:0 BankID:pyhmx.yhzh MoneyType:(m_bselbz?[self GetBzIndex:[[xzbzComboBox cell]title]]:pyhmx.nbz) czbz:1 yhlsh:stryhlsh];
}


-(BOOL)OnReceiveData:(int)reqIndex parser:(id)pParse
{
	ParseRecv *pParsers=(ParseRecv *)pParse;
	if(!pParsers)
		return YES;
	if([pParsers IsTimeOut]==NO){
		[eGetData SetSessionID:pParsers.sessionID];
	}
	switch (reqIndex) 
	{
        case TDX_YHYE2:
        {
            if(pParsers.bsucflag)
            {
                int nczbz=[[pParsers getFieldData:0 fieldFlag:TDX_ID_CZBZ] intValue];
                if(nczbz!=1)
                {
                    [[zjmmText cell] setTitle:@""];
                    [[yhmmText cell] setTitle:@""];
                    [[yhyeText cell] setTitle:[pParsers getFieldData:0 fieldFlag:TDX_ID_YZZZ_YHYE]];
                    [self stopanimate];
                    [stryhlsh release];
                    stryhlsh=nil;
                    break;
                }
            }
            nyhyecount--;
            if(nyhyecount<=0)
            {
                [[zjmmText cell] setTitle:@""];
                [[yhmmText cell] setTitle:@""];
                [self stopanimate];
                [stryhlsh release];
                stryhlsh=nil;
                NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
                                                 defaultButton: @"确定"
                                               alternateButton: nil
                                                   otherButton: nil
                                     informativeTextWithFormat:  @"%@",@"银行余额查询超时"];
                [alert setDelegate:self];
                NSInteger result = [alert runModal];
                [self handleResult:alert withResult:result withTag:1];
            }
            else
            {
                [NSTimer scheduledTimerWithTimeInterval: 2.0f target:self selector: @selector(QueryYhye) userInfo: nil repeats: NO];
            }
        }
            break;
		case TDX_YHYE:
		{
			if(pParsers.bsucflag)
			{
                BOOL bflag=NO;
                signed char bczbzflag=NO;
#ifdef IMAC_ZXJT
                bczbzflag=YES;
#endif
#ifdef IMAC_GXZQ
                bczbzflag=YES;
#endif
#ifdef IMAC_GDZQ
                bczbzflag=YES;
#endif

                if(bczbzflag)
                {
                    int nczbz=[[pParsers getFieldData:0 fieldFlag:TDX_ID_CZBZ] intValue];
                    if(nczbz==1)
                    {
                        [stryhlsh release];
                        stryhlsh=[[pParsers getFieldData:0 fieldFlag:TDX_ID_YZZZ_YHLSH] retain];
                        nyhyecount=30;
                        [NSTimer scheduledTimerWithTimeInterval: 0.0f target:self selector: @selector(QueryYhye) userInfo: nil repeats: NO];
                        break;
                    }
                }
                [[zjmmText cell] setTitle:@""];
                [[yhmmText cell] setTitle:@""];
                if(!bflag)
                {
                    [[yhyeText cell] setTitle:[pParsers getFieldData:0 fieldFlag:TDX_ID_YZZZ_YHYE]];
                    NSMutableString *tmpstr=[[NSMutableString alloc] initWithString:[pParsers getFieldData:0 fieldFlag:TDX_ID_RETINFO]];
                    [tmpstr replaceOccurrencesOfString:@"\\r\\n" withString:@"\r" options:NSCaseInsensitiveSearch range:NSMakeRange(0, [tmpstr length])];
                    

                    if([tmpstr length])
                    {
                        NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
                                                         defaultButton: @"确定"
                                                       alternateButton: nil
                                                           otherButton: nil
                                             informativeTextWithFormat:  @"%@",tmpstr];
                        [alert setDelegate:self];
                        NSInteger result = [alert runModal];
                        int wTag = 1;
#ifdef IMAC_PAZQ
                        wTag = 123;
#endif
                        [self handleResult:alert withResult:result withTag:wTag];
                    }
                    [tmpstr release];
                }
            }
			else  if(pParsers.btipflag)//处理银行余额失败的报错
            {
//  				[[yhyeText cell] setTitle:[NSString stringWithFormat:@"%@",(pParsers.psErrorData?pParsers.psErrorData:@"查询失败")]];
                [[yhyeText cell] setTitle:@""];
                
                NSMutableString *tmpstr=[[NSMutableString alloc] initWithString:[NSString stringWithFormat:@"%@",(pParsers.psErrorData?pParsers.psErrorData:@"查询失败")]];
                [tmpstr replaceOccurrencesOfString:@"\\r\\n" withString:@"\r" options:NSCaseInsensitiveSearch range:NSMakeRange(0, [tmpstr length])];
                
                if([tmpstr length])
                {
                    NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
                                                     defaultButton: @"确定"
                                                   alternateButton: nil
                                                       otherButton: nil
                                         informativeTextWithFormat:  @"%@",tmpstr];
                    [alert setDelegate:self];
                    NSInteger result = [alert runModal];
                    [self handleResult:alert withResult:result withTag:1];
                }
                [tmpstr release];
            }
			[self stopanimate];
		}
			break;
        case TDX_YHYE3:
        {
            if(pParsers.bsucflag)
            {
                BOOL bflag=NO;
                [[zjmmText cell] setTitle:@""];
                [[yhmmText cell] setTitle:@""];
                if(!bflag)
                {
                   // [[yhyeText cell] setTitle:[pParsers getFieldData:0 fieldFlag:169]];
                    //[[yhyeText cell] setTitle:[pParsers getFieldData:0 fieldFlag:409]];
                    [[yhyeText cell] setTitle:[pParsers getFieldData:0 fieldFlag:5549]];
                }
            }

        }
            break;
		case TDX_YZZZ:
		{
			NSString *tmpstr=@"";
			if(pParsers.bsucflag){
				[[zjmmText cell] setTitle:@""];
				[[yhmmText cell] setTitle:@""];
				[[zzjeText cell] setTitle:@""];
				NSString *yhlsh=[pParsers getFieldData:0 fieldFlag:TDX_ID_YZZZ_YHLSH];
				if([yhlsh length])
				{
					if(eGetData.clientinfos.m_nQsbs==GDZQ_DLL)
						tmpstr=[NSString stringWithFormat:@"银行流水号%@,请在转帐查询中查看转帐结果",yhlsh];
					else 
						tmpstr=[NSString stringWithFormat:@"转帐请求已提交,请在转帐查询中查看转帐结果!流水号:%@",yhlsh];
				}
				else 
					tmpstr=[pParsers getFieldData:0 fieldFlag:TDX_ID_RETINFO];
				m_bfirstalertflag=YES;
				NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
												 defaultButton: @"确定"
											   alternateButton: nil
												   otherButton: nil
									 informativeTextWithFormat: @"%@",tmpstr];
				[alert setDelegate:self];
				NSInteger result = [alert runModal];
				[self handleResult:alert withResult:result withTag:1];	
				[self cleanscreen];
			}else  if(pParsers.btipflag){//处理委托失败的报错
				if(eGetData.clientinfos.m_nQsbs==GJZQ_DLL)
					tmpstr=[NSString stringWithFormat:@"转帐请求失败,证券系统返回的原因:\r%@",(pParsers.psErrorData?pParsers.psErrorData:@"转账失败")];
				else 
					tmpstr=[NSString stringWithFormat:@"转帐请求已提交,证券系统返回的原因:\r%@",(pParsers.psErrorData?pParsers.psErrorData:@"转账失败")];
				m_bfirstalertflag=YES;
				NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
												 defaultButton: @"确定"
											   alternateButton: nil
												   otherButton: nil
									 informativeTextWithFormat: @"%@",tmpstr];
				[alert setDelegate:self];
				NSInteger result = [alert runModal];
				[self handleResult:alert withResult:result withTag:1];	
			}
			[self stopanimate];
		}
            break;
        case TDX_PT_DZJZZ:
        {
            NSString *tmpstr=@"";
            if(pParsers.bsucflag){
                [[zjmmText cell] setTitle:@""];
                [[yhmmText cell] setTitle:@""];
                [[zzjeText cell] setTitle:@""];
                
                
                tmpstr=[pParsers getFieldData:0 fieldFlag:TDX_ID_RETINFO];
                NSArray *array = [tmpstr componentsSeparatedByString:@"\\r\\n"];
                NSString *info = @"";
                for(NSString *obj in array)
                {
                    info = [info stringByAppendingString:[obj stringByAppendingString:@"\n"]];
                }
                
                m_bfirstalertflag=YES;
                NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
                                                 defaultButton: @"确定"
                                               alternateButton: nil
                                                   otherButton: nil
                                     informativeTextWithFormat: @"%@",info];
                [alert setDelegate:self];
                NSInteger result = [alert runModal];
                [self handleResult:alert withResult:result withTag:1];
                [self cleanscreen];
                [self refreshpage2];
            }else  if(pParsers.btipflag){//处理委托失败的报错
                
                tmpstr=[NSString stringWithFormat:@"转帐请求已提交,证券系统返回的原因:\r%@",(pParsers.psErrorData?pParsers.psErrorData:@"转账失败")];
                m_bfirstalertflag=YES;
                NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
                                                 defaultButton: @"确定"
                                               alternateButton: nil
                                                   otherButton: nil
                                     informativeTextWithFormat: @"%@",tmpstr];
                [alert setDelegate:self];
                NSInteger result = [alert runModal];
                [self handleResult:alert withResult:result withTag:1];	
            }
            [self stopanimate];
        }
            break;
        case TDX_PT_DZJZJGJ:
        {
            NSString *tmpstr=@"";
            if(pParsers.bsucflag){
                [[zjmmText cell] setTitle:@""];
                [[yhmmText cell] setTitle:@""];
                [[zzjeText cell] setTitle:@""];
                
                tmpstr=[pParsers getFieldData:0 fieldFlag:TDX_ID_RETINFO];
                NSArray *array = [tmpstr componentsSeparatedByString:@"\\r\\n"];
                NSString *info = @"";
                for(NSString *obj in array)
                {
                    info = [info stringByAppendingString:[obj stringByAppendingString:@"\n"]];
                }
                
                m_bfirstalertflag=YES;
                NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
                                                 defaultButton: @"确定"
                                               alternateButton: nil
                                                   otherButton: nil
                                     informativeTextWithFormat: @"%@",info];
                [alert setDelegate:self];
                NSInteger result = [alert runModal];
                [self handleResult:alert withResult:result withTag:1];
                [self cleanscreen];
                [self refreshpage2];
            }else  if(pParsers.btipflag){//处理委托失败的报错
                
                tmpstr=[NSString stringWithFormat:@"资金归集请求已提交,证券系统返回的原因:\r%@",(pParsers.psErrorData?pParsers.psErrorData:@"资金归集失败")];
                m_bfirstalertflag=YES;
                NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
                                                 defaultButton: @"确定"
                                               alternateButton: nil
                                                   otherButton: nil
                                     informativeTextWithFormat: @"%@",tmpstr];
                [alert setDelegate:self];
                NSInteger result = [alert runModal];
                [self handleResult:alert withResult:result withTag:1];
            }
            [self stopanimate];
        }
			break;
	}
	return YES;
}

-(void)refreshpage2
{
    int pageIndex=0;
    int queryindex = TDX_DZJZHCX;

    [eGetData sendTradeQueryData:queryindex pageIndex:(queryindex+PAGE_REFRESHINDEX) objIndex:self.tradeindex Session:eGetData.inputSave.sessionID StartIndex:(pageIndex*PAGE_ROWNUM+[eGetData GetStartIndex]) ReqLines:PAGE_ROWNUM TotleLine:(PAGE_ROWNUM*MAX_PAGENUM) positionstr:@""];
}


#pragma mark alert相关
-(void)handleResult:(NSAlert *)alert withResult:(NSInteger)result withTag:(int)_tag
{
	// report which button was clicked
	switch(result)
	{
			//删除自选股
		case NSAlertDefaultReturn:
            switch (_tag)
            {
                case 0:
                {
                    [self doYzzz2];
                    break;
                }
                case 123: //通过948来获取银行余额
                {
                    [self QueryYhye2];
                    break;
                }
                case 100: //归集
                case 101: //多资金帐号划转
                {
                    [self doYzzz4];
                    break;
                }
                default:
                    [self performSelector:@selector(dealErrorFocus:) withObject:[NSString stringWithFormat:@"%i",_tag] afterDelay:0.1f];
                    break;
            }

			break;
			
		case NSAlertAlternateReturn:
			[self stopanimate];
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
			[[self window] makeFirstResponder:xzyhComboBox];
			break;
		case 2:	
			[[self window] makeFirstResponder:yhmmText];
			break;	
		case 3:
			[[self window] makeFirstResponder:zjmmText];
			break;
		case 4:
			[[self window] makeFirstResponder:zzjeText];
			break;

		default:
			break;
	}
}

-(void)cleardsdata
{
    [self cleanscreen];
    m_pyhmx=nil;
}
@end
