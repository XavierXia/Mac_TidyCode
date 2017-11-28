//
//  ETradePasswordView.m
//  zszq_macosx
//
//  Created by tdx on 11-12-22.
//  Copyright 2011 武汉. All rights reserved.
//

#import "ETradePasswordView.h"

#define OLDPASSWORD_TEXT_FLAG 1
#define NEWPASSWORD_TEXT_FLAG 2
#define NEWPASSWORD_CONFIRM_TEXT_FLAG 3


#define PER_LABEL_WIDTH 120
#define PER_TEXT_WIDTH 120
#define PER_LABEL_HEIGHT 25
#define TOPMARIN 15
#define LEFTMARIN 30
#define SEPARATEMARIN 10
@implementation ETradePasswordView

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
		m_bbusy = NO;
		alertFlag = NO;
		
		self.tradeindex = [_eGetData.g_TradeComm.areceiver SetWinobjs:self];
        m_xgmmlxArr=[[NSArray arrayWithObjects:@"交易密码",@"资金密码",nil] retain];
        m_xgmmlxArrDM=[[NSArray arrayWithObjects:@"0",@"1",nil] retain];
        nxgmmlx = 0;
		
		showTipsLabel = [[NSTextField alloc]init];
		[showTipsLabel setEditable:NO];
		[showTipsLabel setBackgroundColor:[NSColor clearColor]];
		[showTipsLabel setBordered:NO];
		[showTipsLabel setFrame:NSZeroRect];
		[[showTipsLabel cell] setFont:[NSFont systemFontOfSize:14.0f]];
		[[showTipsLabel cell] setTextColor:[NSColor redColor]];
        int nmmlen=6;
#ifdef IMAC_MZZQ
        nmmlen=8;
#endif
        
        [[showTipsLabel cell] setTitle:[NSString stringWithFormat:@"您最多可以设置%i位新密码,建议使用6位新密码，只允许输入0－9",nmmlen]];
		[self addSubview:showTipsLabel];
		
		
        xzmmlxLabel  = [[NSTextField alloc]init];
        [xzmmlxLabel setEditable:NO];
        [xzmmlxLabel setBackgroundColor:[NSColor clearColor]];
        [xzmmlxLabel setBordered:NO];
        [xzmmlxLabel setFrame:NSZeroRect];
        [[xzmmlxLabel cell] setTextColor:[NSColor blackColor]];
        [[xzmmlxLabel cell] setFont:[NSFont systemFontOfSize:14.0f]];
        [[xzmmlxLabel cell] setTitle:@"选择密码类型:"];
        [self addSubview:xzmmlxLabel];
		
		oldPasswordLabel = [[NSTextField alloc]init];
		[oldPasswordLabel setEditable:NO];
		[oldPasswordLabel setBackgroundColor:[NSColor clearColor]];
		[oldPasswordLabel setBordered:NO];
		[oldPasswordLabel setFrame:NSZeroRect];
		[[oldPasswordLabel cell] setFont:[NSFont systemFontOfSize:14.0f]];
		[[oldPasswordLabel cell] setTextColor:[NSColor blackColor]];
		[[oldPasswordLabel cell] setTitle:@"当前交易密码:"];
		[self addSubview:oldPasswordLabel];
		
		newPasswordLabel = [[NSTextField alloc]init];
		[newPasswordLabel setEditable:NO];
		[newPasswordLabel setBackgroundColor:[NSColor clearColor]];
		[newPasswordLabel setBordered:NO];
		[newPasswordLabel setFrame:NSZeroRect];
		[[newPasswordLabel cell] setFont:[NSFont systemFontOfSize:14.0f]];
		[[newPasswordLabel cell] setTextColor:[NSColor blackColor]];
		[[newPasswordLabel cell] setTitle:@"新交易密码:"];
		[self addSubview:newPasswordLabel];
		
		newPasswordConfirmLabel = [[NSTextField alloc]init];
		[newPasswordConfirmLabel setEditable:NO];
		[newPasswordConfirmLabel setBackgroundColor:[NSColor clearColor]];
		[newPasswordConfirmLabel setBordered:NO];
		[newPasswordConfirmLabel setFrame:NSZeroRect];
		[[newPasswordConfirmLabel cell] setFont:[NSFont systemFontOfSize:14.0f]];
		[[newPasswordConfirmLabel cell] setTextColor:[NSColor blackColor]];
		[[newPasswordConfirmLabel cell] setTitle:@"确认新交易密码:"];
		[self addSubview:newPasswordConfirmLabel];
		
        
        
        xgmmxlComboBox = [[NSComboBox alloc] initWithFrame:NSZeroRect];
        [xgmmxlComboBox setBackgroundColor:[NSColor clearColor]];
        [xgmmxlComboBox setEditable:NO];
        [xgmmxlComboBox setUsesDataSource:YES];
        [xgmmxlComboBox setDelegate:self];
        [xgmmxlComboBox setDataSource:self];
        [[xgmmxlComboBox cell] setTitle:@"交易密码"];
        [self addSubview:xgmmxlComboBox];
        
		customTextFieldFormatter * passwordFormatt = [[customTextFieldFormatter alloc] init];
		[passwordFormatt setMaxLength:nmmlen];
		
		
		oldPasswordText = [[CustomSecureTextField alloc]init];
		[oldPasswordText setEditable:YES];
		[oldPasswordText setBackgroundColor:[NSColor whiteColor]];
		[oldPasswordText setBordered:YES];
		[oldPasswordText setBezeled:YES];
		[oldPasswordText setDelegate:self];
		oldPasswordText.focusDelegate = self;
		[oldPasswordText setBezelStyle:NSTextFieldSquareBezel];
		[oldPasswordText setFrame:NSZeroRect];
		[oldPasswordText setFormatter:passwordFormatt];
		[oldPasswordText setTag:OLDPASSWORD_TEXT_FLAG];
		[[oldPasswordText cell] setTextColor:[NSColor blackColor]];
		[self addSubview:oldPasswordText];
		
		newPasswordText = [[CustomSecureTextField alloc]init];
		[newPasswordText setEditable:YES];
		[newPasswordText setBackgroundColor:[NSColor whiteColor]];
		[newPasswordText setBordered:YES];
		[newPasswordText setBezeled:YES];
		[newPasswordText setDelegate:self];
		newPasswordText.focusDelegate = self;
		[newPasswordText setBezelStyle:NSTextFieldSquareBezel];
		[newPasswordText setFrame:NSZeroRect];
		[newPasswordText setFormatter:passwordFormatt];
		[newPasswordText setTag:NEWPASSWORD_TEXT_FLAG];
		[[newPasswordText cell] setTextColor:[NSColor blackColor]];
		[self addSubview:newPasswordText];

		newPasswordConfirmText = [[CustomSecureTextField alloc]init];
		[newPasswordConfirmText setEditable:YES];
		[newPasswordConfirmText setBackgroundColor:[NSColor whiteColor]];
		[newPasswordConfirmText setBordered:YES];
		[newPasswordConfirmText setBezeled:YES];
		[newPasswordConfirmText setDelegate:self];
		newPasswordConfirmText.focusDelegate = self;
		[newPasswordConfirmText setBezelStyle:NSTextFieldSquareBezel];
		[newPasswordConfirmText setFrame:NSZeroRect];
		[newPasswordConfirmText setFormatter:passwordFormatt];
		[newPasswordConfirmText setTag:NEWPASSWORD_CONFIRM_TEXT_FLAG];
		[[newPasswordConfirmText cell] setTextColor:[NSColor blackColor]];
		[self addSubview:newPasswordConfirmText];
		
		
		
		
		[passwordFormatt release];
		
		
		[oldPasswordText setNextKeyView:newPasswordText];
		[newPasswordText setNextKeyView:newPasswordConfirmText];
		
		
		doneButton = [[NSButton alloc] init];
		[doneButton setFrame:NSZeroRect];
		[[doneButton cell] setTitle:@"确定更改"];
		[doneButton setTarget:self];
		[doneButton setAction:@selector(doneButtonClick)];
		[self addSubview:doneButton];
		
		
		
		[self dealOutLook];
		
	}
	return self;
}

-(void)dealOutLook{
	float tempFloat = viewRect.size.height - TOPMARIN - PER_LABEL_HEIGHT;
	
	[showTipsLabel setFrame:NSMakeRect(LEFTMARIN, tempFloat, 500, PER_LABEL_HEIGHT)];
    
    tempFloat = tempFloat - PER_LABEL_HEIGHT;
    [xzmmlxLabel setFrame:NSMakeRect(LEFTMARIN, tempFloat-15, PER_LABEL_WIDTH, PER_LABEL_HEIGHT)];
    [xgmmxlComboBox setFrame:NSMakeRect(LEFTMARIN+PER_LABEL_WIDTH, tempFloat-15, PER_TEXT_WIDTH, PER_LABEL_HEIGHT)];
	
	tempFloat = tempFloat - PER_LABEL_HEIGHT*2;
	[oldPasswordLabel setFrame:NSMakeRect(LEFTMARIN, tempFloat, PER_LABEL_WIDTH, PER_LABEL_HEIGHT)];
	[oldPasswordText setFrame:NSMakeRect(LEFTMARIN+PER_LABEL_WIDTH, tempFloat, PER_TEXT_WIDTH, PER_LABEL_HEIGHT)];
	
	tempFloat = tempFloat - PER_LABEL_HEIGHT-SEPARATEMARIN;
	[newPasswordLabel setFrame:NSMakeRect(LEFTMARIN, tempFloat, PER_LABEL_WIDTH, PER_LABEL_HEIGHT)];
	[newPasswordText setFrame:NSMakeRect(LEFTMARIN+PER_LABEL_WIDTH, tempFloat, PER_TEXT_WIDTH, PER_LABEL_HEIGHT)];
	
	
	tempFloat = tempFloat - PER_LABEL_HEIGHT-SEPARATEMARIN;
	[newPasswordConfirmLabel setFrame:NSMakeRect(LEFTMARIN, tempFloat, PER_LABEL_WIDTH, PER_LABEL_HEIGHT)];
	[newPasswordConfirmText setFrame:NSMakeRect(LEFTMARIN+PER_LABEL_WIDTH, tempFloat, PER_TEXT_WIDTH, PER_LABEL_HEIGHT)];
	
	tempFloat = tempFloat - PER_LABEL_HEIGHT - 20;
	[doneButton setFrame:NSMakeRect(LEFTMARIN+PER_TEXT_WIDTH, tempFloat-5, PER_LABEL_WIDTH, PER_LABEL_HEIGHT)];
}

- (void)drawRect:(NSRect)dirtyRect {

}

-(void) setFrame:(NSRect)frameRect{
	[super setFrame:frameRect];
	viewRect = frameRect;
	[self dealOutLook];
}

#pragma mark  focusDelegate相关
-(void)getFocus:(int)_tag{
	switch (_tag) {
		case OLDPASSWORD_TEXT_FLAG:
			break;
		case NEWPASSWORD_TEXT_FLAG:
			break;
		case NEWPASSWORD_CONFIRM_TEXT_FLAG:
			break;
		default:
			break;
	}
}


-(void)getEnter:(int)_tag{
	switch (_tag) {
		case OLDPASSWORD_TEXT_FLAG:
			[[self window] makeFirstResponder:newPasswordText];
			break;
		case NEWPASSWORD_TEXT_FLAG:
			[[self window] makeFirstResponder:newPasswordConfirmText];
			break;
		case NEWPASSWORD_CONFIRM_TEXT_FLAG:
			[[self window] makeFirstResponder:doneButton];
			[self doneButtonClick];
			break;	
		default:
			break;
	}
}

-(void)getEsc:(int)_tag{
}

-(void)getKeyUp:(NSEvent *)theEvent{
}



#pragma mark 页面显示相关
-(void)onviewWillAppear{
	[[oldPasswordText cell] setTitle:@""];
	[[newPasswordText cell] setTitle:@""];
	[[newPasswordConfirmText cell] setTitle:@""];
	
	[[self window] makeFirstResponder:oldPasswordText];
}


-(void)disableAllText{
	[oldPasswordText setEnabled:NO];
	[newPasswordText setEnabled:NO];
	[newPasswordConfirmText setEnabled:NO];
}
-(void)enableAllText{
	[oldPasswordText setEnabled:YES];
	[newPasswordText setEnabled:YES];
	[newPasswordConfirmText setEnabled:YES];
}

-(void) doneButtonClick{
	[eGetData.clientinfos jyhasoper];
	if([self IsCanQueryOther]==NO)
		return;
	[self doXGMM];
}

#pragma mark 数据相关

-(void)startanimate
{
	m_bbusy=YES;
	[self disableAllText];
}

-(void)stopanimate
{
	if(m_bbusy)
	{
		m_bbusy=NO;
		[self enableAllText];
	}
}

-(BOOL)IsCanQueryOther
{
	return !m_bbusy;
}

-(void)cleanscreen{
	[[oldPasswordText cell] setTitle:@""];
	[[newPasswordText cell] setTitle:@""];
	[[newPasswordConfirmText cell] setTitle:@""];
}

-(void)doXGMM{
    
    NSString *info1;
    NSString *info2;
    NSString *info3;
    NSString *info4;
    NSString *info5;
    
    if(nxgmmlx == 0) //交易密码
    {
        info1 = @"请输入当前交易密码";
        info2 = @"当前交易密码输入错误,请重新输入!";
        info3 = @"请输入新交易密码";
        info4 = @"请确认新交易密码";
        info5 = @"两次输入的交易密码不一致，请重新输入!";
    }
    else
    {
        info1 = @"请输入当前资金密码";
        info2 = @"当前资金密码输入错误,请重新输入!";
        info3 = @"请输入新资金密码";
        info4 = @"请确认新资金密码";
        info5 = @"两次输入的资金密码不一致，请重新输入!";
    }
    
	if([[[oldPasswordText cell] title] length] == 0)
	{
		NSAlert* alert = [NSAlert alertWithMessageText: @"提示"
										 defaultButton: @"确定"
									   alternateButton: nil
										   otherButton: nil
							 informativeTextWithFormat: @"%@", info1];
		[alert setDelegate:self];
		alertFlag = YES;
		NSInteger result = [alert runModal];
		[self handleResult:alert withResult:result withTag:0];	
		return;
	}
	if([[[oldPasswordText cell] title] isEqualToString:[eGetData GetJymmString]]==NO)
    {
        NSAlert* alert = [NSAlert alertWithMessageText: @"提示"
                                         defaultButton: @"确定"
                                       alternateButton: nil
                                           otherButton: nil
                             informativeTextWithFormat: @"%@", info2];
        [alert setDelegate:self];
        alertFlag = YES;
        NSInteger result = [alert runModal];
        [self handleResult:alert withResult:result withTag:0];
        [[oldPasswordText cell] setTitle:@""];
        return;
    }
	if([[[newPasswordText cell] title] length] == 0)
	{
		NSAlert* alert = [NSAlert alertWithMessageText: @"提示"
										 defaultButton: @"确定"
									   alternateButton: nil
										   otherButton: nil
							 informativeTextWithFormat: @"%@", info3];
		[alert setDelegate:self];
		alertFlag = YES;
		NSInteger result = [alert runModal];
		[self handleResult:alert withResult:result withTag:1];	
		return ;
	}
	
	if([[[newPasswordConfirmText cell] title] length] == 0)
	{
		NSAlert* alert = [NSAlert alertWithMessageText: @"提示"
										 defaultButton: @"确定"
									   alternateButton: nil
										   otherButton: nil
							 informativeTextWithFormat: @"%@", info4];
		[alert setDelegate:self];
		alertFlag = YES;
		NSInteger result = [alert runModal];
		[self handleResult:alert withResult:result withTag:2];	
		return ;
	}
	
	if ([[[newPasswordConfirmText cell] title] compare:[[newPasswordText cell] title]]!=NSOrderedSame){
		NSAlert* alert = [NSAlert alertWithMessageText: @"提示"
										 defaultButton: @"确定"
									   alternateButton: nil
										   otherButton: nil
							 informativeTextWithFormat: @"%@", info5];
		[alert setDelegate:self];
		alertFlag = YES;
		NSInteger result = [alert runModal];
		[self handleResult:alert withResult:result withTag:3];	
		return ;
		
	}
    
    [info1 release];
	[info2 release];
    [info3 release];
    [info4 release];
    [info5 release];
    
	[self doXGMM1];
}

-(void)doXGMM1{
	[self startanimate];
    int orderID;
    if(nxgmmlx == 0)
    {
        orderID = TDX_XGMM;
    }
    else
    {
        orderID = TDX_XGZJMM;
    }
    
	[eGetData sendTradePasswordData:orderID objIndex:self.tradeindex Session:eGetData.inputSave.sessionID OldPassword:[[oldPasswordText cell] title] NewPassword:[[newPasswordText cell] title] ];
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
		case TDX_XGMM:
		{
			NSString *tmpstr=@"";
			if(pParsers.bsucflag){
				[eGetData EncryptJymm:[[newPasswordText cell] title]];
                [self cleanscreen];
				tmpstr=[NSString stringWithFormat:@"交易密码已经更改,请记住新交易密码!"];
	
				NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
												 defaultButton: @"确定"
											   alternateButton: nil
												   otherButton: nil
									 informativeTextWithFormat: @"%@",tmpstr];
				[alert setDelegate:self];
				NSInteger result = [alert runModal];
				[self handleResult:alert withResult:result withTag:4];	
			}else  if(pParsers.btipflag){//处理委托失败的报错
				if(pParsers.btipflag)
				{
					NSString *tempString = [NSString stringWithFormat:@"错误信息:%@%@",pParsers.psErrorNum,pParsers.psErrorData];
					
					NSAlert* alert = [NSAlert alertWithMessageText: @"提示"
													 defaultButton: @"确定"
												   alternateButton: nil
													   otherButton: nil
										 informativeTextWithFormat: @"%@",tempString];
					[alert setDelegate:self];
					alertFlag = YES;
					NSInteger result = [alert runModal];
					[self handleResult:alert withResult:result withTag:5];	
					
				}
				
			}
		}
			break;
        case TDX_XGZJMM:
        {
            NSString *tmpstr=@"";
            if(pParsers.bsucflag){
                tmpstr=[NSString stringWithFormat:@"资金密码已经更改,请记住新资金密码!"];
                
                NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
                                                 defaultButton: @"确定"
                                               alternateButton: nil
                                                   otherButton: nil
                                     informativeTextWithFormat: @"%@",tmpstr];
                [alert setDelegate:self];
                NSInteger result = [alert runModal];
                [self handleResult:alert withResult:result withTag:4];
            }else  if(pParsers.btipflag){//处理委托失败的报错
                if(pParsers.btipflag)
                {
                    NSString *tempString = [NSString stringWithFormat:@"错误信息:%@%@",pParsers.psErrorNum,pParsers.psErrorData];
                    
                    NSAlert* alert = [NSAlert alertWithMessageText: @"提示"
                                                     defaultButton: @"确定"
                                                   alternateButton: nil
                                                       otherButton: nil
                                         informativeTextWithFormat: @"%@",tempString];
                    [alert setDelegate:self];
                    alertFlag = YES;
                    NSInteger result = [alert runModal];
                    [self handleResult:alert withResult:result withTag:5];	
                    
                }
                
            }
        }
            break;
	}
	return YES;
}


#pragma mark alertdelegate相关
-(void)handleResult:(NSAlert *)alert withResult:(NSInteger)result  withTag:(int)_tag{
	
	switch(result)
	{
		case NSAlertDefaultReturn:{
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
	alertFlag = NO;
}

-(void)dealErrorFocus:(NSString *)_tag{
	switch ([_tag intValue]) {
		case 0:
			[[self window] makeFirstResponder:oldPasswordText];
			break;
		case 1:	
			[[self window] makeFirstResponder:newPasswordText];
			break;
		case 2:
			[[self window] makeFirstResponder:newPasswordConfirmText];
			break;
		case 3:
			[[newPasswordText cell] setTitle:@""];
			[[newPasswordConfirmText cell] setTitle:@""];
			[[self window] makeFirstResponder:newPasswordText];
			break;
		case 4:
			[self cleanscreen];
			[self stopanimate];
			[[self window] makeFirstResponder:oldPasswordText];
			break;			
		case 5:	
			[self stopanimate];
			[[self window] makeFirstResponder:oldPasswordText];
			break;

		default:
			break;
	}
}

#pragma mark combobox Delegate相关
-(NSInteger) numberOfItemsInComboBox:(NSComboBox *)aComboBox{
    return [m_xgmmlxArr count];
}

-(id) comboBox:(NSComboBox *)aComboBox objectValueForItemAtIndex:(NSInteger)index{
    return [m_xgmmlxArr objectAtIndex:index];
}

-(void) comboBoxSelectionDidChange:(NSNotification *)notification{
    NSComboBox * tempCombobox = [notification object];
    int tempInt = [tempCombobox indexOfSelectedItem];
    if(index >= 0)
    {
        nxgmmlx = [[m_xgmmlxArrDM objectAtIndex:tempInt] intValue];
        
        [[oldPasswordText cell] setTitle:@""];
        [[newPasswordText cell] setTitle:@""];
        [[newPasswordConfirmText cell] setTitle:@""];
        
        [[self window] makeFirstResponder:oldPasswordText];
    }
    
    switch (tempInt)
    {
        case 0:
        {
            [[oldPasswordLabel cell] setTitle:@"当前交易密码:"];
            [[newPasswordLabel cell] setTitle:@"新交易密码:"];
            [[newPasswordConfirmLabel cell] setTitle:@"确认新交易密码:"];
            break;
        }
        case 1:
        {
            [[oldPasswordLabel cell] setTitle:@"当前资金密码:"];
            [[newPasswordLabel cell] setTitle:@"新资金密码:"];
            [[newPasswordConfirmLabel cell] setTitle:@"确认新资金密码:"];
            break;
        }
        default:
            break;
    }
}


@end
