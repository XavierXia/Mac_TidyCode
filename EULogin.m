//
//  EULogin.m
//  tdxMac
//
//  Created by tdx on 11-10-9.
//  Copyright 2011 武汉. All rights reserved.
//

#import "EULogin.h"
#import "macro.h"

#define wantNum 500
#define ZHLX_COM_FLAG 1
#define ACCOUNT_COM_FLAG 2
#define AQFS_COM_FLAG 3
#define PASSWORD_TEXT_FLAG 4
#define YZ_TEXT_FLAG 5
#define AUTHPASS_TEXT_FLAG 6
#define YYB_COM_FLAG 7

@implementation EULogin

@synthesize showDelegate,loginType,bshowFlag;
- (id)initWithFrame:(NSRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
    }
    return self;
}

- (id)initWithData:(NSRect)frame theData:(EGetData *)_eGetData{
    self = [super initWithData:frame theData:_eGetData];
    if (self) {
		m_bLoginFlag = NO;
		m_bbusy = NO;
		loginType = NO;
		initHQFlag = NO;
		initJYFlag = NO;
		alertFlag= NO;
		formatter = [[customTextFieldFormatter alloc] init];
        formatter1 = [[customTextFieldFormatter alloc] init];
        formatter1.showalpha=YES;
		_eGetData.myjyasyncdelegate=self;
		[self InitLoginset];
        [self initT2ee];
        BOOL blogbg=NO;
#ifdef IMAC_GTJA
		blogbg=YES;
#endif
#ifdef IMAC_GHZQ
		blogbg=YES;
#endif
#ifdef IMAC_XNZQ
        blogbg=YES;
#endif
		
		JyConfig *pconfig;
        NSImageView * tempImage=nil;
        if(blogbg)
        {
            tempImage = [[NSImageView alloc] initWithFrame:NSMakeRect(0, 0, frame.size.width, frame.size.height)];
            [tempImage setImage:[NSImage imageNamed:@"login_bg.png"]];
            [self addSubview:tempImage];
            [tempImage release];
        }
		else
        {
            tempImage = [[NSImageView alloc] initWithFrame:NSMakeRect(0, frame.size.height-40, frame.size.width, 40)];
            [tempImage setImage:[NSImage imageNamed:@"logo.png"]];
            [self addSubview:tempImage];
            [tempImage release];
        }
		
		
		
		tradeBox = [[NSBox alloc] initWithFrame:NSMakeRect(10, 10, frame.size.width-20, frame.size.height-50-10)];
		[tradeBox setTitle:@""];
		[self addSubview:tradeBox];
		
		boxRect = tradeBox.frame;
		
		tempImage = [[NSImageView alloc] initWithFrame:NSMakeRect(0, 0, boxRect.size.width, boxRect.size.height)];
		[tempImage setImage:[NSImage imageNamed:@"box_bg.png"]];
		[tempImage release];
        
#ifdef IMAC_ONLYHQ
        
        NSRect rc = NSMakeRect(frame.size.width/2 - 40, 180, 80, 30);
		hqButton = [[NSButton alloc]initWithFrame:rc];
		[[hqButton cell] setTitle:@"独立行情"];
		[hqButton setBordered:YES];
		[hqButton setBezelStyle:3];
		[hqButton setTarget:self];
		[hqButton setAction:@selector(initHQPara)];
		[self addSubview:hqButton];
        
        txSetButton=[[NSButton alloc] initWithFrame:NSMakeRect(frame.size.width/2-40, 130, 80, 30)];
        [[txSetButton cell] setTitle:@"系统设置"];
		[txSetButton setBordered:YES];
		[txSetButton setBezelStyle:3];
		[txSetButton setTarget:self];
		[txSetButton setAction:@selector(txSetClick)];
		[self addSubview:txSetButton];
        
        cancelButton = [[NSButton alloc] initWithFrame:NSMakeRect(frame.size.width/2 -40, 80, 80, 30)];
		[[cancelButton cell] setTitle:@"取 消"];
		[cancelButton setBordered:YES];
		[cancelButton setBezelStyle:3];
		[cancelButton setTarget:self];
		[cancelButton setAction:@selector(cancelButtonClick)];
		[self addSubview:cancelButton];
        
#else
	
        
		NSRect rc = NSMakeRect(boxRect.size.width/2 + 40, boxRect.size.height-60, 80, 30);
		hqButton = [[NSButton alloc]initWithFrame:rc];
		[[hqButton cell] setTitle:@"独立行情"];
		[hqButton setBordered:YES];
		[hqButton setBezelStyle:3];
		[hqButton setTarget:self];
		[hqButton setAction:@selector(initHQPara)];
		[tradeBox addSubview:hqButton];
        
		
		tradeButtonnew = [[NSButton alloc]initWithFrame:NSMakeRect(boxRect.size.width/2 -120, boxRect.size.height-60, 80, 30)];
		[[tradeButtonnew cell] setTitle:@"行情+交易"];
		[tradeButtonnew setBordered:YES];
		[tradeButtonnew setButtonType:1];
		[tradeButtonnew setBezelStyle:3];
		[tradeButtonnew setState:NSOnState];
		[tradeButtonnew setTarget:self];
		[tradeButtonnew setAction:@selector(initTradePara)];
		[tradeBox addSubview:tradeButtonnew];

		
		NSTextField * tempText;
		tempText = [[NSTextField alloc]init];
		[tempText setEditable:NO];
		[tempText setBackgroundColor:[NSColor clearColor]];
		[tempText setBordered:NO];
		[tempText setFrame:NSMakeRect(20, boxRect.size.height-60-40, 120, 30)];
		[[tempText cell] setFont:[NSFont systemFontOfSize:15.0f]];
		[[tempText cell] setTextColor:[NSColor blackColor]];
		[[tempText cell] setAlignment:NSRightTextAlignment];
		[[tempText cell] setTitle:@"登录方式"];
		[tradeBox addSubview:tempText];
		[tempText release];
		
		zhlx_Combobox = [[NSComboBox alloc] initWithFrame:NSMakeRect(150, boxRect.size.height-60-40+4, 200, 26)];
		[zhlx_Combobox setBackgroundColor:[NSColor clearColor]];
		[zhlx_Combobox setEditable:NO];
		[zhlx_Combobox setTag:ZHLX_COM_FLAG];
		[zhlx_Combobox setUsesDataSource:YES];
		[zhlx_Combobox setDelegate:self];
		[zhlx_Combobox setDataSource:self];
		
		
		yyb_Combobox=nil;
		
		pconfig=[eGetData.clientinfos.qsconfigs.jyconfigs objectAtIndex:0];
		if(pconfig)
		{
			if(pconfig.loginmode && [pconfig.loginmode count])
			{
				LoginMode *ploginmode=[pconfig.loginmode objectAtIndex:0];
				if(ploginmode)
				{
					
					m_ploginmode=ploginmode;
					[[zhlx_Combobox cell] setTitle:m_ploginmode.zhdesc];
				}
				
				Yybs * pyyb = [pconfig.yybs objectAtIndex:0];
				if (pyyb) {
					m_pyyb = pyyb;
                    
                    NSRect zhlxrect=zhlx_Combobox.frame;
                    zhlx_Combobox.frame=NSMakeRect(zhlxrect.origin.x, zhlxrect.origin.y, 80, zhlxrect.size.height);
                    yyb_Combobox = [[NSComboBox alloc] initWithFrame:NSMakeRect(230, boxRect.size.height-60-40+4, 150, 26)];
                    [yyb_Combobox setBackgroundColor:[NSColor clearColor]];
                    [yyb_Combobox setEditable:NO];
                    [yyb_Combobox setTag:YYB_COM_FLAG];
                    [yyb_Combobox setUsesDataSource:YES];
                    [yyb_Combobox setDelegate:self];
                    [yyb_Combobox setDataSource:self];
                    
					[[yyb_Combobox cell] setTitle:m_pyyb.yybname];
				}
			}
		}
		
		[tradeBox addSubview:zhlx_Combobox];
        if(yyb_Combobox && m_pyyb)
            [tradeBox addSubview:yyb_Combobox];
		
		loginTypeLabel = [[NSTextField alloc]init];
		[loginTypeLabel setEditable:NO];
		[loginTypeLabel setBackgroundColor:[NSColor clearColor]];
		[loginTypeLabel setBordered:NO];
		[loginTypeLabel setFrame:NSMakeRect(20, boxRect.size.height-60-2*40, 120, 30)];
		[[loginTypeLabel cell] setFont:[NSFont systemFontOfSize:15.0f]];
		[[loginTypeLabel cell] setTextColor:[NSColor blackColor]];
		[[loginTypeLabel cell] setAlignment:NSRightTextAlignment];
		if (m_ploginmode) {
			[[loginTypeLabel cell] setTitle:m_ploginmode.zhdesc];
		}
		else {
			[[loginTypeLabel cell] setTitle:@"帐    号:"];
		}

		
		[tradeBox addSubview:loginTypeLabel];
		
		
		account_Combobox = [[CustonComboBox alloc] initWithFrame:NSMakeRect(150, boxRect.size.height-60-2*40+4, 200, 26)];
		[account_Combobox setBackgroundColor:[NSColor clearColor]];
		[account_Combobox setEditable:YES];
		[account_Combobox setTag:ACCOUNT_COM_FLAG];
		[account_Combobox setUsesDataSource:YES];
		[account_Combobox setDelegate:self];
		[account_Combobox setDataSource:self];
		[account_Combobox setFormatter:formatter1];
		account_Combobox.focusDelegate = self;
		
		if(eGetData.clientinfos.logininfos.bsavezh){
			if ([eGetData.clientinfos.logininfos.m_rawzjzh length] > 0) {
				[[account_Combobox cell] setTitle:eGetData.clientinfos.logininfos.m_rawzjzh];
			}
			
		}
		[tradeBox addSubview:account_Combobox];
			
		
		saveAccount = [[NSButton alloc] initWithFrame:NSMakeRect(370, boxRect.size.height-60-2*40+4, 80, 26)];
		[saveAccount setButtonType:NSSwitchButton];
		[saveAccount setState:eGetData.clientinfos.logininfos.bsavezh?NSOnState:NSOffState];
		[[saveAccount cell] setTitle:@"记住帐号"];
		[saveAccount setTarget:self];
        [saveAccount setAction:@selector(OnSaveZhClick)];
		[tradeBox addSubview:saveAccount];
		
		tempText = [[NSTextField alloc]init];
		[tempText setEditable:NO];
		[tempText setBackgroundColor:[NSColor clearColor]];
		[tempText setBordered:NO];
		[tempText setFrame:NSMakeRect(20, boxRect.size.height-60-3*40, 120, 30)];
		[[tempText cell] setFont:[NSFont systemFontOfSize:15.0f]];
		[[tempText cell] setTextColor:[NSColor blackColor]];
		[[tempText cell] setAlignment:NSRightTextAlignment];
		[[tempText cell] setTitle:@"交易密码"];
		[tradeBox addSubview:tempText];
		[tempText release];
		
		password_Text = [[CustomSecureTextField alloc]init];
		[password_Text setEditable:YES];
		[password_Text setBackgroundColor:[NSColor whiteColor]];
		[password_Text setBordered:YES];
		[password_Text setBezeled:YES];
		[password_Text setDelegate:self];
		password_Text.focusDelegate = self;
		[password_Text setBezelStyle:NSTextFieldSquareBezel];
		[password_Text setFrame:NSMakeRect(150, boxRect.size.height-60-3*40+4, 195, 26)];
		[password_Text setTag:PASSWORD_TEXT_FLAG];
		[[password_Text cell] setTextColor:[NSColor blackColor]];
		[tradeBox addSubview:password_Text];

		
		tempText = [[NSTextField alloc]init];
		[tempText setEditable:NO];
		[tempText setBackgroundColor:[NSColor clearColor]];
		[tempText setBordered:NO];
		[tempText setFrame:NSMakeRect(20, boxRect.size.height-60-4*40, 120, 30)];
		[[tempText cell] setFont:[NSFont systemFontOfSize:15.0f]];
		[[tempText cell] setTextColor:[NSColor blackColor]];
		[[tempText cell] setAlignment:NSRightTextAlignment];
		[[tempText cell] setTitle:@"安全方式"];
		[tradeBox addSubview:tempText];
		[tempText release];
		
		aqfs_Combobox = [[NSComboBox alloc] initWithFrame:NSMakeRect(150, boxRect.size.height-60-4*40+4, 80, 26)];
		[aqfs_Combobox setBackgroundColor:[NSColor clearColor]];
		[aqfs_Combobox setEditable:NO];
		[aqfs_Combobox setTag:AQFS_COM_FLAG];
		[aqfs_Combobox setUsesDataSource:YES];
		[aqfs_Combobox setDataSource:self];
		[aqfs_Combobox setDelegate:self];
		
		

		pconfig=[eGetData.clientinfos.qsconfigs.jyconfigs objectAtIndex:0];

		
		if(pconfig)
		{
			if(pconfig.secure && [pconfig.secure count])
			{
				SecureMode *psecuremode;
				if(eGetData.clientinfos.logininfos.bsavezh){
					if ([eGetData.clientinfos.logininfos.m_rawzjzh length] > 0) {
						[[account_Combobox cell] setTitle:eGetData.clientinfos.logininfos.m_rawzjzh];
					}
					
					for (int i =0; i<[pconfig.secure count]; i++) {
						psecuremode=[pconfig.secure objectAtIndex:i];
						
						if (psecuremode.ntype == eGetData.clientinfos.logininfos.naqfs) {
							break;
						}
					}
				}
				else {
					psecuremode=[pconfig.secure objectAtIndex:0];
				}

				
				
				if(psecuremode)
				{
					m_psecuremode=psecuremode;
					[[aqfs_Combobox cell] setTitle:m_psecuremode.sname];
				}
			}
		}
		
		[tradeBox addSubview:aqfs_Combobox];
		
		yz_Text = [[CustonTextField alloc]init];
		[yz_Text setEditable:YES];
		[yz_Text setBackgroundColor:[NSColor whiteColor]];
		[yz_Text setBordered:YES];
		[yz_Text setBezeled:YES];
		[yz_Text setBezelStyle:NSTextFieldSquareBezel];
		[yz_Text setDelegate:self];
		yz_Text.focusDelegate = self;
		[yz_Text setTag:YZ_TEXT_FLAG];
		[yz_Text setFrame:NSMakeRect(230, boxRect.size.height-60-4*40+4, 115, 26)];
		[[yz_Text cell] setTextColor:[NSColor blackColor]];
		[yz_Text setFormatter:formatter];
		[tradeBox addSubview:yz_Text];
		
		authpass_Text = [[CustonTextField alloc]init];
		[authpass_Text setEditable:YES];
		[authpass_Text setBackgroundColor:[NSColor whiteColor]];
		[authpass_Text setBordered:YES];
		[authpass_Text setBezeled:YES];
		[authpass_Text setBezelStyle:NSTextFieldSquareBezel];
		[authpass_Text setDelegate:self];
		authpass_Text.focusDelegate = self;
		[authpass_Text setTag:AUTHPASS_TEXT_FLAG];
		[authpass_Text setFrame:NSMakeRect(230, boxRect.size.height-60-4*40+4, 115, 26)];
		[[authpass_Text cell] setTextColor:[NSColor blackColor]];
		[tradeBox addSubview:authpass_Text];
	

		
		
		m_yzmview = [[CustomCellBackground alloc] initWithFrame:NSMakeRect(355, boxRect.size.height-60-4*40+4, 80, 26)];
		m_yzmview.bshowyzm=YES;
		[m_yzmview GenYzm];
		[tradeBox addSubview:m_yzmview];
		
		
		if (m_psecuremode.ntype) {
			[yz_Text removeFromSuperview];
			[m_yzmview removeFromSuperview];
			[password_Text setNextKeyView:authpass_Text];
		}
		else {
			[authpass_Text removeFromSuperview];
			[password_Text setNextKeyView:yz_Text];
		}
		
        
        txSetButton=[[NSButton alloc] initWithFrame:NSMakeRect(boxRect.size.width/2-220, boxRect.size.height-60-4*40-14, 80, 30)];
        [[txSetButton cell] setTitle:@"系统设置"];
        [txSetButton setBordered:YES];
        [txSetButton setBezelStyle:3];
        [txSetButton setTarget:self];
        [txSetButton setAction:@selector(txSetClick)];
        [self addSubview:txSetButton];
        
		
		doneButton = [[NSButton alloc] initWithFrame:NSMakeRect(boxRect.size.width/2 -110, boxRect.size.height-60-4*40-30, 80, 30)];
		[[doneButton cell] setTitle:@"登 录"];
		[doneButton setBordered:YES];
		[doneButton setBezelStyle:3];
		[doneButton setTarget:self];
		[doneButton setAction:@selector(doneButtonClick)];
		[tradeBox addSubview:doneButton];
		
		cancelButton = [[NSButton alloc] initWithFrame:NSMakeRect(boxRect.size.width/2 +30, boxRect.size.height-60-4*40-30, 80, 30)];
		[[cancelButton cell] setTitle:@"取 消"];
		[cancelButton setBordered:YES];
		[cancelButton setBezelStyle:3];
		[cancelButton setTarget:self];
		[cancelButton setAction:@selector(cancelButtonClick)];
		[tradeBox addSubview:cancelButton];	
		
	#endif
		
		showTips = [[NSTextField alloc]init];
		[showTips setEditable:NO];
		[showTips setBackgroundColor:[NSColor clearColor]];
		[showTips setBordered:NO];
		[showTips setFrame:NSMakeRect(0,0,frame.size.width,20)];
		[[showTips cell] setFont:[NSFont systemFontOfSize:13.0f]];
		[[showTips cell] setAlignment:NSLeftTextAlignment];
#ifdef IMAC_GTJA
		[[showTips cell] setTextColor:[NSColor whiteColor]];
#else
        [[showTips cell] setTextColor:[NSColor blackColor]];
#endif
#ifdef IMAC_ONLYHQ
         [[showTips cell] setTitle:@"请点击 \"独立行情\" 登录行情。"];
#endif
		[self addSubview:showTips];
		
	}
	return self;
}
#pragma mark textfield Delegate相关
-(void) controlTextDidEndEditing:(NSNotification *)obj{

}

-(void)onViewWillAppear{
    
#ifdef IMAC_ONLYHQ
    return;
#endif
	if (self.loginType) {
		[hqButton setFrame:NSZeroRect];
		[tradeButtonnew setFrame:NSZeroRect];
	}else {
		[hqButton setFrame:NSMakeRect(boxRect.size.width/2 + 40, boxRect.size.height-60, 80, 30)];
		[tradeButtonnew setFrame:NSMakeRect(boxRect.size.width/2 - 120, boxRect.size.height-60, 80, 30)];
	}

	
	
	if ([[[account_Combobox cell] title] length]>0) {
		[[self window] makeFirstResponder:password_Text];
	}
	else {
		[[self window] makeFirstResponder:account_Combobox];
	}
	
	if (m_psecuremode) {
		JyConfig * pconfig=[eGetData.clientinfos.qsconfigs.jyconfigs objectAtIndex:0];
		if(pconfig)
		{
			if(pconfig.secure && [pconfig.secure count])
			{
				SecureMode *psecuremode;
				if(eGetData.clientinfos.logininfos.bsavezh){
					if ([eGetData.clientinfos.logininfos.m_rawzjzh length] > 0) {
						[[account_Combobox cell] setTitle:eGetData.clientinfos.logininfos.m_rawzjzh];
					}
					
					for (int i =0; i<[pconfig.secure count]; i++) {
						psecuremode=[pconfig.secure objectAtIndex:i];
						
						if (psecuremode.ntype == eGetData.clientinfos.logininfos.naqfs) {
							break;
						}
					}
				}
				else {
					psecuremode=[pconfig.secure objectAtIndex:0];
				}
				
				if(psecuremode)
				{
					m_psecuremode=psecuremode;
					[[aqfs_Combobox cell] setTitle:m_psecuremode.sname];
				}
				
				[yz_Text removeFromSuperview];
				[m_yzmview removeFromSuperview];
				[authpass_Text removeFromSuperview];
				if (m_psecuremode.ntype) {
					[tradeBox addSubview:authpass_Text];
					[password_Text setNextKeyView:authpass_Text];
				}
				else {
					[tradeBox addSubview:yz_Text];
					[tradeBox addSubview:m_yzmview];
					[password_Text setNextKeyView:yz_Text];
				}
			}
			
			
			if(pconfig.yybs && [pconfig.yybs count])
			{
				int i=0;
				NSString *tmpstr=@"";
				for(Yybs *pyyb in pconfig.yybs)
				{
					tmpstr=[NSString stringWithFormat:@"%@%@",pyyb.yybid,pyyb.yybname];
					if([tmpstr isEqualToString:eGetData.clientinfos.logininfos.m_rawbranchid])
					{
						m_pyyb=pyyb;
						nyybindex=i;
						[[yyb_Combobox cell] setTitle:m_pyyb.yybname];
						NSLog(@"%@",m_pyyb.yybname);
						
					}
					i++;
				}
			}
			
			if(pconfig.loginmode && [pconfig.loginmode count])
			{
				LoginMode *ploginmode=[pconfig.loginmode objectAtIndex:0];
				if(ploginmode)
				{
					
					m_ploginmode=ploginmode;
					[[zhlx_Combobox cell] setTitle:m_ploginmode.zhdesc];
				}
			}
		}
	}
	


}

-(void)getFocus:(int)_tag{
	switch (_tag) {
		case ACCOUNT_COM_FLAG:
			[[showTips cell] setTitle:[NSString stringWithFormat:@"请输入%@信息",[[loginTypeLabel cell]title]]];
			break;
		case PASSWORD_TEXT_FLAG:
			[[showTips cell] setTitle:@"请输入密码信息"];
			break;
		case YZ_TEXT_FLAG:
			[[showTips cell] setTitle:@"请输入图片中的4个数字"];
			break;
        case AUTHPASS_TEXT_FLAG:
			[[showTips cell] setTitle:@"请输入动态令牌口令"];
			break;

		default:
			break;
	}
}


-(void)getEnter:(int)_tag{
	if (alertFlag) {
		[[self window] makeFirstResponder:self];
		return;
	}
	switch (_tag) {
		case ACCOUNT_COM_FLAG:
			[[self window] makeFirstResponder:password_Text];
			break;
		case PASSWORD_TEXT_FLAG:
			if (m_psecuremode.ntype) {
				[[self window] makeFirstResponder:authpass_Text];
			}
			else {
				[[self window] makeFirstResponder:yz_Text];
			}
			break;
		case YZ_TEXT_FLAG:
			[[self window] makeFirstResponder:password_Text];
			[self doneButtonClick];
			break;
		case AUTHPASS_TEXT_FLAG:
			[[self window] makeFirstResponder:password_Text];
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

#pragma mark 键盘输入相关
-(void) keyDown:(NSEvent *)theEvent{
}

#pragma mark combobox Delegate相关
-(NSInteger) numberOfItemsInComboBox:(NSComboBox *)aComboBox{
    if (aComboBox.tag == ZHLX_COM_FLAG) {
		JyConfig *pconfig=[eGetData.clientinfos.qsconfigs.jyconfigs objectAtIndex:0];
		if(pconfig)
		{
			return [pconfig.loginmode count];
		}
		else {
			return  0 ;
		}

		
	}
	
	else if(aComboBox.tag == ACCOUNT_COM_FLAG){

		return [eGetData.clientinfos.multilogininfos.zhinfos count];
	}
	
	else if(aComboBox.tag == AQFS_COM_FLAG){
		JyConfig *pconfig=[eGetData.clientinfos.qsconfigs.jyconfigs objectAtIndex:0];
		if(pconfig)
		{
			return [pconfig.secure count];
		}
		else {
			return  0 ;
		}
	}
	else if(aComboBox.tag == YYB_COM_FLAG){
		JyConfig *pconfig=[eGetData.clientinfos.qsconfigs.jyconfigs objectAtIndex:0];
		if(pconfig)
		{
			return [pconfig.yybs count];
		}
		else {
			return  0 ;
		}
		
	}
	
	return 0;
}

-(id) comboBox:(NSComboBox *)aComboBox objectValueForItemAtIndex:(NSInteger)index{
     if (aComboBox.tag == ZHLX_COM_FLAG) {
         JyConfig *pconfig=[eGetData.clientinfos.qsconfigs.jyconfigs objectAtIndex:0];
         LoginMode *ploginmode=[pconfig.loginmode objectAtIndex:index];
         return ploginmode.zhdesc;
     }
	else if (aComboBox.tag == ACCOUNT_COM_FLAG){
		LoginInfo *pInfo = [eGetData.clientinfos.multilogininfos.zhinfos objectAtIndex:index];
        return [NSString stringWithFormat:@"%@(%@)",pInfo.m_rawzjzh,pInfo.m_strzhlx];
	}
	else if(aComboBox.tag == AQFS_COM_FLAG){
		JyConfig *pconfig=[eGetData.clientinfos.qsconfigs.jyconfigs objectAtIndex:0];
		SecureMode *psecuremode=[pconfig.secure objectAtIndex:index];
		return psecuremode.sname;
	}
	else if(aComboBox.tag == YYB_COM_FLAG){
		JyConfig *pconfig=[eGetData.clientinfos.qsconfigs.jyconfigs objectAtIndex:0];
		Yybs *pyyb=[pconfig.yybs objectAtIndex:index];
		return pyyb.yybname;
	}

	return nil;
}

-(void)OnProcessAccount
{
    LoginInfo *pInfo = [eGetData.clientinfos.multilogininfos.zhinfos objectAtIndex:[account_Combobox indexOfSelectedItem]];
    [account_Combobox cell].title=pInfo.m_rawzjzh;
    
    JyConfig *pconfig=[eGetData.clientinfos.qsconfigs.jyconfigs objectAtIndex:0];
    if(pconfig)
    {
        int ncount=[pconfig.loginmode count];
        int nindex=0;
        for(LoginMode *pmode in pconfig.loginmode)
        {
            if(pmode.zhlx==pInfo.m_loginWtType)
            {
                [zhlx_Combobox selectItemAtIndex:nindex];
                break;
            }
            nindex++;
        }
    }
}

-(void) comboBoxSelectionDidChange:(NSNotification *)notification{
	NSComboBox * tempCombobox = [notification object];
	
	if ([tempCombobox tag] == ZHLX_COM_FLAG) {
		JyConfig *pconfig=[eGetData.clientinfos.qsconfigs.jyconfigs objectAtIndex:0];
		LoginMode *ploginmode=[pconfig.loginmode objectAtIndex:[zhlx_Combobox indexOfSelectedItem]];
		m_ploginmode=ploginmode;
		[[loginTypeLabel cell] setTitle:m_ploginmode.zhdesc];
	}
	else if([tempCombobox tag] == YYB_COM_FLAG){
		JyConfig *pconfig=[eGetData.clientinfos.qsconfigs.jyconfigs objectAtIndex:0];
		nyybindex = [tempCombobox indexOfSelectedItem];
		m_pyyb=[pconfig.yybs objectAtIndex:nyybindex];
		NSLog(@"%i",nyybindex);
	}
	else if([tempCombobox tag] == ACCOUNT_COM_FLAG){
		JyConfig *pconfig=[eGetData.clientinfos.qsconfigs.jyconfigs objectAtIndex:0];
		LoginInfo *pInfo = [eGetData.clientinfos.multilogininfos.zhinfos objectAtIndex:[account_Combobox indexOfSelectedItem]];
        [NSTimer scheduledTimerWithTimeInterval: 0.0f target:self selector: @selector(OnProcessAccount) userInfo: nil repeats: NO];
        if(pconfig.secure && [pconfig.secure count])
		{
			SecureMode *psecuremode;
			for (int i =0; i<[pconfig.secure count]; i++) {
				psecuremode=[pconfig.secure objectAtIndex:i];
			
				if (psecuremode.ntype == pInfo.naqfs) {
					break;
				}
			}
			
			if(psecuremode)
			{
				m_psecuremode=psecuremode;
				[[aqfs_Combobox cell] setTitle:m_psecuremode.sname];
			}
			
			[yz_Text removeFromSuperview];
			[m_yzmview removeFromSuperview];
			[authpass_Text removeFromSuperview];
			if (m_psecuremode.ntype) {
				[tradeBox addSubview:authpass_Text];
				[password_Text setNextKeyView:authpass_Text];
			}
			else {
				[tradeBox addSubview:yz_Text];
				[tradeBox addSubview:m_yzmview];
				[password_Text setNextKeyView:yz_Text];
			}
			
		}
	}
	else if([tempCombobox tag] == AQFS_COM_FLAG){
		int tempInt = [aqfs_Combobox indexOfSelectedItem];
		
		
		JyConfig *pconfig=[eGetData.clientinfos.qsconfigs.jyconfigs objectAtIndex:0];
		if(pconfig)
		{
			if(pconfig.secure && [pconfig.secure count]>tempInt)
			{
				SecureMode *psecuremode=[pconfig.secure objectAtIndex:tempInt];
				if(psecuremode)
				{
					m_psecuremode=psecuremode;
					
					[authpass_Text removeFromSuperview];
					[yz_Text removeFromSuperview];
					[m_yzmview removeFromSuperview];
					if(m_psecuremode.ntype==0)
					{
						[tradeBox addSubview:yz_Text];
						[tradeBox addSubview:m_yzmview];
						[[yz_Text cell] setTitle:@""];
						[password_Text setNextKeyView:yz_Text];
						[[self window] makeFirstResponder:yz_Text];
					}
					else 
					{
						[tradeBox addSubview:authpass_Text];
						[[authpass_Text cell] setTitle:@""];
						[password_Text setNextKeyView:authpass_Text];
						[[self window] makeFirstResponder:authpass_Text];
					}
				}
			}
		
		}
	}
	
	
}
#pragma mark 用户点击相关
-(void)initTradePara{
	[tradeButtonnew setState:NSOnState];
	[hqButton setState:NSOffState];
	[self enableAllButton];
}

-(void)initHQPara{
	if (initHQFlag) {
		return;
	}
	[tradeButtonnew setState:NSOffState];
	[hqButton setState:NSOnState];
	
	[self disableAllbutton];
	BOOL bfastflag=NO;
	if (eGetData.clientinfos.localhqsites.bfindbest && [eGetData.clientinfos.localhqsites.tradesites count]>1) {
		[[showTips cell] setTitle:@"正在查找最快行情主站......"];
		
		
		bfastflag=[eGetData FindFastedHqSite];
		
		if(bfastflag==NO)
		{
			[self getBaseInfo];
		}
	}
	else {
		[self getBaseInfo];
	}
}
-(void)getBaseInfo{
	NSMutableData * theData = [eGetData getHostBaseDataReqEx];	
	if (![eGetData.g_pEComm AsyncSendData:theData length:[theData length] withobjIndex:self.windindex withreqIndex:1]) {
		[self enableAllButton];
		[tradeButtonnew setState:NSOnState];
		[hqButton setState:NSOffState];
		[[showTips cell] setTitle:@"连接主情主站失败......"];
		
	}
	else {
		[[showTips cell] setTitle:@"正在获取服务器信息......"];
	}
	
}

-(void)DoAfterFindHqBest{
	[self getBaseInfo];
}


-(void)enableAllButton{
#ifdef IMAC_ONLYHQ
     [txSetButton setEnabled:YES];
#else
	[zhlx_Combobox setEnabled:YES];
	[yyb_Combobox setEnabled:YES];
	[account_Combobox setEnabled:YES];
	[aqfs_Combobox setEnabled:YES];
	[password_Text setEnabled:YES];
	[yz_Text setEnabled:YES];
	[doneButton setEnabled:YES];
	[cancelButton setEnabled:YES];
	[hqButton setEnabled: YES];
	[tradeButtonnew setEnabled:YES];
	[authpass_Text setEnabled:YES];
	[saveAccount setEnabled:YES];
#endif
	m_bLoginFlag = NO;
}

-(void)disableAllbutton{
#ifdef IMAC_ONLYHQ
    [txSetButton setEnabled:NO];
#else
	[zhlx_Combobox setEnabled:NO];
	[yyb_Combobox setEnabled:NO];
	[account_Combobox setEnabled:NO];
	[aqfs_Combobox setEnabled:NO];
	[password_Text setEnabled:NO];
	[yz_Text setEnabled:NO];
	[doneButton setEnabled:NO];
	[cancelButton setEnabled:NO];
	[hqButton setEnabled: NO];
	[tradeButtonnew setEnabled:NO];
	[authpass_Text setEnabled:NO];
	[saveAccount setEnabled:NO];
#endif
	m_bLoginFlag= YES;
}

-(void)getSoftVerInfo{
	NSMutableData * theData = [eGetData getSoftVerReq];	
	[eGetData.g_pEComm AsyncSendData:theData length:[theData length] withobjIndex:self.windindex withreqIndex:1];
	[[showTips cell] setTitle:@"正在检查版本信息......"];
}


-(void)OnReceiveData:(int)reqIndex FuncID:(int)_funcID HqResult:(HqResultData *)_hqResult{
	if (_hqResult.resultStat < 1) {
		[tradeButtonnew setState:NSOnState];
		[hqButton setState:NSOffState];
		[self enableAllButton];
		
		
		NSDateFormatter *dateFormatter=[[[NSDateFormatter alloc] init]autorelease]; 
		[dateFormatter setDateFormat:@"HH-mm-ss"];
		NSString * localTime = [dateFormatter stringFromDate:[NSDate date]];
		NSArray * tempArray = [localTime componentsSeparatedByString:@"-"];	
		int nowHour,nowMinute,nowSec;
        if([tempArray count]<2)
        {
            nowHour = 0;
            nowMinute = 0;
            nowSec = 0;
        }
        else
        {
            nowHour = [[tempArray objectAtIndex:0]intValue]+eGetData.hourDiff;
            nowMinute = [[tempArray objectAtIndex:1]intValue]+eGetData.minuteDiff;
            nowSec = [[tempArray objectAtIndex:2]intValue]+eGetData.secondDiff;
        }
		
		if (nowSec > 59) {
			nowMinute = nowMinute + 1;
		}
		if (nowMinute > 59) {
			nowMinute = nowMinute -60;
			nowHour = nowHour+1;
		}
		
		int checkInt = nowHour * 60+nowMinute;
		if ((checkInt > 510) && (checkInt <540)) {
			[[showTips cell] setTitle:@"行情主站正在进行初始化,请稍后再连接!"];
		}
		else {
			[[showTips cell] setTitle:@"未知错误"];
		}

		
		
		
		if (eGetData.tradeLoginFlag) {
			[eGetData logoutTrade];
			[eGetData InitHqInfo];
			[eGetData InitClientInfo];
			[self onViewWillAppear];
		}
		return;
	}
	
	switch (reqIndex) {
		case HOSTINFO_ORI:
			if (!m_bLoginFlag) {
				return;
			}
			
			//取服务器信息
			[eGetData getHostBaseDataAnsEx:_hqResult];
			NSLog(@"获取码表");
			[[showTips cell] setTitle:@"正在获取股票信息......"];
			
			if([eGetData.clientinfos.caches loadGpdml:eGetData.gpdmlInfo]==NO)
			{
				NSMutableData * theData = [eGetData getAllStockChainReq:SZ offset:eGetData.szStockRec wantnum:wantNum];	
				[eGetData.g_pEComm AsyncSendData:theData length:[theData length] withobjIndex:self.windindex withreqIndex:1];
			}
			else {
				eGetData.szStockArray = [[NSMutableArray alloc] initWithArray:eGetData.gpdmlInfo.szGPArray];
				eGetData.shStockArray = [[NSMutableArray alloc] initWithArray:eGetData.gpdmlInfo.shGPArray];
				
				if( ([eGetData.szStockArray count] == eGetData.szStockNum) && ([eGetData.shStockArray count] == eGetData.shStockNum) ){
					[self getSoftVerInfo];
            	}
				else {
					[eGetData.szStockArray removeAllObjects];
					[eGetData.shStockArray removeAllObjects];
					NSMutableData * theData = [eGetData getAllStockChainReq:SZ offset:eGetData.szStockRec wantnum:wantNum];	
					[eGetData.g_pEComm AsyncSendData:theData length:[theData length] withobjIndex:self.windindex withreqIndex:1];
				}

				
				
			}

			
						
			break;
		case STOCKCHAIN_ORI:
			if (!m_bLoginFlag) {
				return;
			}
			
			
			//取码表信息
			if (eGetData.szStockRec < eGetData.szStockNum) {
				eGetData.szStockRec += [eGetData getAllStockChainAsn:_hqResult];
				
				float tempFloat = (eGetData.szStockRec +eGetData.shStockRec) *100 / (eGetData.szStockNum+eGetData.shStockNum);
				[[showTips cell] setTitle:[NSString stringWithFormat:@"正在获取深市股票信息%.0f％",tempFloat]];
				
				
				if (eGetData.szStockRec < eGetData.szStockNum) {
					NSMutableData * theData = [eGetData getAllStockChainReq:SZ offset:eGetData.szStockRec wantnum:wantNum];	
					[eGetData.g_pEComm AsyncSendData:theData length:[theData length] withobjIndex:self.windindex withreqIndex:1];
					
					
				}
				else {
					NSMutableData * theData = [eGetData getAllStockChainReq:SH offset:eGetData.shStockRec wantnum:wantNum];	
					[eGetData.g_pEComm AsyncSendData:theData length:[theData length] withobjIndex:self.windindex withreqIndex:1];
					
					
				}
				
				

			}
			else if(eGetData.shStockRec < eGetData.shStockNum) {
				eGetData.shStockRec += [eGetData getAllStockChainAsn:_hqResult];
				
				float tempFloat = (eGetData.szStockRec +eGetData.shStockRec) *100/ (eGetData.szStockNum+eGetData.shStockNum);
				[[showTips cell] setTitle:[NSString stringWithFormat:@"正在获取沪市股票信息%.0f％",tempFloat]];
				
				if (eGetData.shStockRec < eGetData.shStockNum) {
					NSMutableData * theData = [eGetData getAllStockChainReq:SH offset:eGetData.shStockRec wantnum:wantNum];	
					[eGetData.g_pEComm AsyncSendData:theData length:[theData length] withobjIndex:self.windindex withreqIndex:1];
					
				}
				else {
					eGetData.gpdmlInfo.szGPArray = [[NSMutableArray alloc] initWithArray:eGetData.szStockArray];
					eGetData.gpdmlInfo.shGPArray = [[NSMutableArray alloc] initWithArray:eGetData.shStockArray];
					[eGetData.clientinfos.caches SaveGpdml:eGetData.gpdmlInfo];
					[self getSoftVerInfo];
                }
			}

			
			break;
		case SOFTVER_NREQ:{
			if (!m_bLoginFlag) {
				return;
			}
			NSLog(@"版本信息");
			NSMutableDictionary * result = [[[NSMutableDictionary alloc]init] autorelease];
			[eGetData getSoftVerAns:_hqResult Result:result];
			
			int majorVer,minorVer,quitflag;
			majorVer = [[result objectForKey:@"MAJORVER"]intValue];
			minorVer = [[result objectForKey:@"MINORVER"]intValue];
			quitflag = [[result objectForKey:@"QUITFLAG"]intValue];
			
			JyConfig *pconfig=[eGetData.clientinfos.qsconfigs.jyconfigs objectAtIndex:0];
			
			if (majorVer >[pconfig.fversion intValue] || (majorVer =[pconfig.fversion intValue] && minorVer > [pconfig.assversion intValue])) {
				
                NSString *strtip=@"";
				if (quitflag > 0) {
#ifdef IMAC_ZTZQ
                    strtip= @"您的版本需要更新,请到中泰证券官网（http://www.zts.com.cn/）下载新版本,谢谢";
#endif
#ifdef IMAC_ZXJT    
                    strtip= @"您的版本需要更新,请到中信建投证券108网（www.csc108.com）下载新版本,谢谢";
#endif
#ifdef IMAC_ZSZQ
                    strtip= @"您的版本需要更新,请到招商证券牛网（www.newone.com.cn）下载新版本,谢谢";
#endif
#ifdef IMAC_GTJA
                    strtip= @"您的版本需要更新,请到国泰君安官网（www.gtja.com）下载新版本,谢谢";
#endif
#ifdef IMAC_TDX
                    strtip= @"您的版本需要更新,请到通达信官网（www.tdx.com.cn）下载新版本,谢谢";
#endif
#ifdef IMAC_GHZQ
                    strtip= @"您的版本需要更新,请到国海证券官网（www.ghzq.com.cn）下载新版本,谢谢";
#endif
#ifdef IMAC_GDZQ
                    strtip= @"您的版本需要更新,请到光大证券官网（www.ebscn.com/）下载新版本,谢谢";
#endif
			if([strtip length]<=0)
                        strtip=@"您的版本需要更新,请到券商官网下载新版本,谢谢!";
					NSAlert* alert = [NSAlert alertWithMessageText: @"提示"
													 defaultButton: @"确定"
												   alternateButton: nil
													   otherButton: nil
										 informativeTextWithFormat:@"%@",strtip];
					[alert setDelegate:self];
					alertFlag = YES;
					NSInteger result = [alert runModal];
					[self handleResult:alert withResult:result withTag:10];	
				}else {
                    
#ifdef IMAC_ZTZQ
                    strtip= @"检测到新版本,请到中泰证券官网（http://www.zts.com.cn/）下载新版本,谢谢";
#endif
#ifdef IMAC_ZXJT
                    strtip= @"检测到新版本,请到中信建投证券108网（www.csc108.com）下载更新,谢谢";
#endif
#ifdef IMAC_ZSZQ
                    strtip= @"检测到新版本,请到招商证券牛网（www.newone.com.cn）下载更新,谢谢";
#endif
#ifdef IMAC_GTJA
                    strtip= @"检测到新版本,请到国泰君安官网（www.gtja.com）下载新版本,谢谢";
#endif
#ifdef IMAC_TDX
                    strtip= @"检测到新版本,请到通达信官网（www.tdx.com.cn）下载新版本,谢谢";
#endif
#ifdef IMAC_GHZQ
                    strtip= @"检测到新版本,请到国海证券官网（www.ghzq.com.cn）下载新版本,谢谢";
#endif
                    if([strtip length]<=0)
                        strtip=@"检测到新版本,请到券商官网下载新版本,谢谢!";
					NSAlert* alert = [NSAlert alertWithMessageText: @"提示"
													 defaultButton: @"确定"
												   alternateButton: nil
													   otherButton: nil
										 informativeTextWithFormat:@"%@",strtip ];
					[alert setDelegate:self];
					alertFlag = YES;
					NSInteger result = [alert runModal];
					[self handleResult:alert withResult:result withTag:11];	
				}
				
				
				
				
			}
			else {
				initHQFlag = YES;
				[showDelegate afterInit];
			}

			
			
		}
			break;

		default:
			break;
	}
}

#pragma mark  登录相关
-(void)InitLoginset
{
	m_ploginset=nil;
	JyConfig *pconfig=[eGetData.clientinfos.qsconfigs.jyconfigs objectAtIndex:0];
	if(pconfig)
		eGetData.clientinfos.m_nQsbs=pconfig.qsid;
	if(pconfig && pconfig.loginsets)
		m_ploginset=pconfig.loginsets;
	if(m_ploginset && m_ploginset.buse)
	{

	}
	if(pconfig && pconfig.pmisc)
		m_yzmview.bcoloryzm=pconfig.pmisc.coloryzm;	
	else 
		m_yzmview.bcoloryzm=NO;
	
}


-(BOOL)IsCanQueryOther
{
	return !m_bbusy;
}

-(void)startanimate
{
	m_bbusy=YES;
	[[showTips cell] setTitle:@"正在验证用户信息......"];
}

-(void)stopanimate
{
	m_bbusy=NO;
	[[showTips cell] setTitle:@""];
}

-(BOOL)doLogin
{
	NSString * tempString ;
	if([[[account_Combobox cell] title] length] == 0)
	{
		NSAlert* alert = [NSAlert alertWithMessageText: @"提示"
										 defaultButton: @"确定"
									   alternateButton: nil
										   otherButton: nil
							 informativeTextWithFormat: @"请输入帐号"];
		[alert setDelegate:self];
		alertFlag = YES;
		NSInteger result = [alert runModal];
		[self handleResult:alert withResult:result withTag:0];	
		return NO;
	}
	if(eGetData.clientinfos.m_nQsbs==YHZQ_DLL && [[[account_Combobox cell] title] length]<11)
	{
		NSAlert* alert = [NSAlert alertWithMessageText: @"提示"
										 defaultButton: @"确定"
									   alternateButton: nil
										   otherButton: nil
							 informativeTextWithFormat: @"帐号不能少于11位"];
		[alert setDelegate:self];
		alertFlag = YES;
		NSInteger result = [alert runModal];
		[self handleResult:alert withResult:result withTag:1];	
		return NO;
	}
	Vyyb *pvyyb=nil;
	JyConfig *pconfig=[eGetData.clientinfos.qsconfigs.jyconfigs objectAtIndex:0];
	if(pconfig)
		pvyyb=pconfig.vyybs;
	if(pvyyb)
	{
		int wttype=9;
		if(m_ploginmode)
			wttype=m_ploginmode.zhlx;
		if((wttype==SHHY || wttype==KHWT) && pvyyb.mustaccountlen>0 && [[[account_Combobox cell] title] length]!=pvyyb.mustaccountlen)
		{
			tempString=[NSString stringWithFormat:@"必须输入%i位帐号!",pvyyb.mustaccountlen];
			NSAlert* alert = [NSAlert alertWithMessageText: @"提示"
											 defaultButton: @"确定"
										   alternateButton: nil
											   otherButton: nil
								 informativeTextWithFormat: @"%@",tempString];
			[alert setDelegate:self];
			alertFlag = YES;
			NSInteger result = [alert runModal];
			[self handleResult:alert withResult:result withTag:1];	
			return NO;
		}
	}
	if([[[password_Text cell] title] length] == 0)
	{
		NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
										 defaultButton: @"确定"
									   alternateButton: nil
										   otherButton: nil
							 informativeTextWithFormat: @"请输入密码"];
		[alert setDelegate:self];
		alertFlag = YES;
		NSInteger result = [alert runModal];
		[self handleResult:alert withResult:result withTag:2];	
		return NO;
	}
	if(m_psecuremode.ntype==0)
	{
		if([[[yz_Text cell] title] length]==0)
		{
			NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
											 defaultButton: @"确定"
										   alternateButton: nil
											   otherButton: nil
								 informativeTextWithFormat: @"请输入验证码"];
			[alert setDelegate:self];
			alertFlag = YES;
			NSInteger result = [alert runModal];
			[self handleResult:alert withResult:result withTag:3];	
			[[yz_Text cell] setTitle:@""];
			return NO;
		}
		if([m_yzmview IsValidYzm:[[yz_Text cell] title]]==NO)
		{
			NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
											 defaultButton: @"确定"
										   alternateButton: nil
											   otherButton: nil
								 informativeTextWithFormat: @"验证码校验错误，请重新输入验证码"];
			[alert setDelegate:self];
			alertFlag = YES;
			NSInteger result = [alert runModal];
			[self handleResult:alert withResult:result withTag:4];	
			[[yz_Text cell] setTitle:@""];
			[m_yzmview GenYzm];
			return NO;
			
		}
	}
	else if(m_psecuremode.ntype)
	{
		if ([[[authpass_Text cell] title] length]==0) {
			tempString=[NSString stringWithFormat:@"请输入%@",m_psecuremode.sname];
			NSAlert* alert = [NSAlert alertWithMessageText: @"提示"
											 defaultButton: @"确定"
										   alternateButton: nil
											   otherButton: nil
								 informativeTextWithFormat: @"%@",tempString];
			[alert setDelegate:self];
			alertFlag = YES;
			NSInteger result = [alert runModal];
			[self handleResult:alert withResult:result withTag:5];	
			return NO;
		}
	}
	InputSave * tempSave = eGetData.inputSave;
	if(m_ploginmode)
    {
		tempSave.accoutType=m_ploginmode.zhlx;
    }
    else{
		tempSave.accoutType=9;
    }
	
	if(m_psecuremode)
	{
		tempSave.authtype=m_psecuremode.ntype;
		if(m_psecuremode.ntype!=0)
			[eGetData EncryptauthPass: [[authpass_Text cell] title]];
	}
	else 
		tempSave.authtype=0;
    if (eGetData.clientinfos.m_nQsbs == GTJA_DLL) {
		if (m_pyyb) {
			tempSave.tdxbranchid = [m_pyyb.yybid intValue];
		}
	}
	else {
		tempSave.tdxbranchid=[self SetVirtualYybID];
        if(tempSave.tdxbranchid==0)
            tempSave.tdxbranchid=1;
	}
    int nindex=[account_Combobox indexOfSelectedItem];
    if(nindex>=0)
    {
        LoginInfo *pInfo = [eGetData.clientinfos.multilogininfos.zhinfos objectAtIndex:nindex];
        if(pInfo)
            tempSave.accout=pInfo.m_rawzjzh;
        else
            tempSave.accout = [[account_Combobox cell] title];
    }
    else
        tempSave.accout = [[account_Combobox cell] title];
    [eGetData EncryptJymm: [[password_Text cell] title]];
	
    eGetData.clientinfos.m_TdxRealBranchID=tempSave.tdxbranchid;
	tempSave.branchId=[NSString stringWithFormat:@"%i",tempSave.tdxbranchid];
	
	if (eGetData.netStat == NotReachable) {
		NSAlert* alert = [NSAlert alertWithMessageText: @"提示"
										 defaultButton: @"确定"
									   alternateButton: nil
										   otherButton: nil
							 informativeTextWithFormat: @"网络不可用,请检查网络!"];
		[alert setDelegate:self];
		alertFlag = YES;
		NSInteger result = [alert runModal];
		[self handleResult:alert withResult:result withTag:6];	
		return NO;		
	}
	return YES;
}

-(void)doasynclogin{
	if([self doLogin]==NO)
		return;
	eGetData.g_TradeComm.m_blogout=NO;
	int sitecount=[eGetData.clientinfos.localjysites.tradesites count];
	if(sitecount<=0)
	{
		NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
										 defaultButton: @"确定"
									   alternateButton: nil
										   otherButton: nil
							 informativeTextWithFormat: @"没有可用的交易中心,请检查交易中心设置!"];
		[alert setDelegate:self];
		alertFlag = YES;
		NSInteger result = [alert runModal];
		[self handleResult:alert withResult:result withTag:6];	
		
		return;
	}
	[self startanimate];
	if(eGetData.clientinfos.localjysites.bfindbest && [eGetData.clientinfos.localjysites.tradesites count]>1)
		[NSTimer scheduledTimerWithTimeInterval: 0.0f target:self selector: @selector(doasynclogin4) userInfo: nil repeats: NO];
	else 
	{
		m_nfirstindex=-1;
		m_ncurindex=-1;
		[NSTimer scheduledTimerWithTimeInterval: 0.0f target:self selector: @selector(doasynclogin2) userInfo: nil repeats: NO];
	}
}

-(void)doasynclogin4
{
	BOOL bfastflag=NO;
	if(eGetData.clientinfos.localjysites.bfindbest && [eGetData.clientinfos.localjysites.tradesites count]>1)
	{
		eGetData.myjyasyncdelegate=self;
		[self disableAllbutton];
		[[showTips cell] setTitle:@"正在查找最快交易主站......"];
		bfastflag=[eGetData FindFastedJySite];
	}
	if(bfastflag==NO)
	{
		m_nfirstindex=-1;
		m_ncurindex=-1;
		[self doasynclogin2];
	}
}

-(void)doasynclogin2
{
	int sitecount=[eGetData.clientinfos.localjysites.tradesites count];
	if(m_nfirstindex==-1 && m_ncurindex==-1)
	{
		if(eGetData.clientinfos.localjysites.nlastindex>=0 && eGetData.clientinfos.localjysites.nlastindex<sitecount)
			m_ncurindex=eGetData.clientinfos.localjysites.nlastindex;
		else 
			m_ncurindex=0;
		m_nfirstindex=m_ncurindex;
	}
	else
	{
		m_ncurindex++;
		if(m_ncurindex>=sitecount)
			m_ncurindex=0;
	}
	if([eGetData.g_TradeComm connect:((sitecount==1)?YES:NO) withlastflag:YES]>=0)
	{
		[self disableAllbutton];
#ifdef IMAC_SSL_JY
		[m_t2ee StartSSLShake];
#else
		[eGetData sendTradeQueryData:TDX_KHXY objIndex:tradeindex Session:0];
#endif		
		return;
	}
}

-(void)tradeLoginTimeOut{
}


-(void)DoAfterFindBest
{
	m_nfirstindex=-1;
	m_ncurindex=-1;
	[NSTimer scheduledTimerWithTimeInterval: 0.0f target:self selector: @selector(doasynclogin2) userInfo: nil repeats: NO];
}

-(void)doAfterLoginFailed
{
	int sitecount=[eGetData.clientinfos.localjysites.tradesites count];
	if(sitecount<=1)
	{
		[self stopanimate];
		if(m_psecuremode.ntype==0)
		{
			[[yz_Text cell] setTitle:@""];
			[m_yzmview GenYzm];
		}
		return;
	}
	int nextindex=m_ncurindex+1;
	if(nextindex>=[eGetData.clientinfos.localjysites.tradesites count])
		nextindex=0;
	if(nextindex==m_nfirstindex)
	{
		NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
										 defaultButton: @"确定"
									   alternateButton: nil
										   otherButton: nil
							 informativeTextWithFormat: @"连接交易服务器失败,请检查网络环境!"];
		[alert setDelegate:self];
		alertFlag = YES;
		NSInteger result = [alert runModal];
		[self handleResult:alert withResult:result withTag:7];	
		
		[self stopanimate];
		if(m_psecuremode.ntype==0)
		{
			[[yz_Text cell] setTitle:@""];
			[m_yzmview GenYzm];
		}
		return;
	}
}

-(BOOL)OnReceiveData:(int)reqIndex parser:(id)pParse
{
	
	ParseRecv *pParsers=(ParseRecv *)pParse;
	if(!pParsers)
		return YES;
	if([pParsers IsTimeOut]==NO){
		if (!m_bLoginFlag) {
			return YES;
		}
		[eGetData SetSessionID:pParsers.sessionID];
	}
	switch (reqIndex) {
		case TDX_KHXY:
		{
            #ifdef IMAC_ZSZQ
            eGetData.clientinfos.dldzxy = [pParsers getFieldData:0 fieldFlag:293];
            #endif
			if(pParsers.bsucflag)
            {
                if(m_ncurindex!=eGetData.clientinfos.localjysites.nlastindex)
                {
                    eGetData.clientinfos.localjysites.nlastindex=m_ncurindex;
                    LogIt(11)
                    [eGetData.clientinfos.caches SaveLocalJySite:eGetData.clientinfos.localjysites];
                }
		    }
			eGetData.g_TradeComm.breloginflag=NO;
			if([eGetData getKHJYInfo:pParsers])
			{
                if( eGetData.clientinfos.m_bqhflag || eGetData.clientinfos.m_bggflag)
                {
                    [self enableAllButton];
                    [tradeButtonnew setState:NSOffState];
                    [hqButton setState:NSOnState];
                    [self stopanimate];
                    [[self window] makeFirstResponder:password_Text];
                    NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
                                                     defaultButton: @"确定"
                                                   alternateButton: nil
                                                       otherButton: nil
                                         informativeTextWithFormat: @"本系统只支持普通股票交易!"];
                    [alert setDelegate:self];
                    alertFlag = YES;
                    NSInteger result = [alert runModal];
                    [self handleResult:alert withResult:result withTag:0];
                    break;
                }
                
				[[password_Text cell] setTitle:@""];
				[eGetData.clientinfos.logininfos releasecontent];
				eGetData.clientinfos.logininfos.bsavezh=[saveAccount state];
				if(eGetData.clientinfos.logininfos.bsavezh)
					eGetData.clientinfos.logininfos.m_rawzjzh=[[NSString alloc]  initWithFormat:@"%@",[[account_Combobox cell] title]];
				else 
					eGetData.clientinfos.logininfos.m_rawzjzh=[[NSString alloc]  initWithFormat:@"%@",@""];
				[eGetData.clientinfos.logininfos.m_rawzjzh release];
				if(m_ploginmode)
					eGetData.clientinfos.logininfos.m_loginWtType=m_ploginmode.zhlx;
				else 
					eGetData.clientinfos.logininfos.m_loginWtType=9;
				if(m_pyyb)
					eGetData.clientinfos.logininfos.m_rawbranchid=[[NSString alloc] initWithFormat:@"%@%@",m_pyyb.yybid,m_pyyb.yybname];
				else 
					eGetData.clientinfos.logininfos.m_rawbranchid=[[NSString alloc]  initWithFormat:@"%@",@""];
				[eGetData.clientinfos.logininfos.m_rawbranchid release];
				eGetData.clientinfos.logininfos.m_strzhlx=[[NSString alloc]  initWithFormat:@"%@",[[zhlx_Combobox cell] title]];
				[eGetData.clientinfos.logininfos.m_strzhlx release];
				if(m_psecuremode){
					eGetData.clientinfos.logininfos.naqfs=m_psecuremode.ntype;
				}
				else
					eGetData.clientinfos.logininfos.naqfs=0;
				
				[eGetData.clientinfos.caches SaveLoginInfo:eGetData.clientinfos.logininfos];
				if(eGetData.clientinfos.logininfos.bsavezh)
				{
					BOOL bzhexist=NO;
					for(LoginInfo *ploginInfo in eGetData.clientinfos.multilogininfos.zhinfos)
					{
						if(ploginInfo.m_loginWtType==eGetData.clientinfos.logininfos.m_loginWtType && [ploginInfo.m_rawzjzh isEqualToString:eGetData.clientinfos.logininfos.m_rawzjzh]==YES)
						{
							bzhexist=YES;
							break;
						}
					}
					if(bzhexist==NO)
					{
						if(eGetData.clientinfos.multilogininfos.zhinfos==nil)
						{
							eGetData.clientinfos.multilogininfos.zhinfos=[[NSMutableArray alloc] initWithCapacity:1];
							[eGetData.clientinfos.multilogininfos.zhinfos release];
						}
						[eGetData.clientinfos.multilogininfos.zhinfos addObject:[eGetData.clientinfos.logininfos deepcopy]];
						[eGetData.clientinfos.caches SaveMultiloginInfo:eGetData.clientinfos.multilogininfos];
					}
				}
                else if(eGetData.clientinfos.multilogininfos.zhinfos && [eGetData.clientinfos.multilogininfos.zhinfos count])
                {
                    [eGetData.clientinfos.multilogininfos releasezhinfos2];
                    [eGetData.clientinfos.caches SaveMultiloginInfo:eGetData.clientinfos.multilogininfos];
                }
				//trade.ccf
				[eGetData.clientinfos.tradeccf loadTradeccf];
				eGetData.clientinfos.jyParams=[eGetData.clientinfos.caches loadJyParamInfo];
				[eGetData.clientinfos.jyParams release];
				JyConfig *pconfig=[eGetData.clientinfos.qsconfigs.jyconfigs objectAtIndex:0];
				if(eGetData.clientinfos.jyParams==nil && pconfig && pconfig.jyParams)
				{
					eGetData.clientinfos.jyParams=[pconfig.jyParams deepcopy];
					[eGetData.clientinfos.caches SaveJyParamInfo:eGetData.clientinfos.jyParams];
				}
				if(eGetData.clientinfos.m_bgpflag)
				{
					if([eGetData.clientinfos.caches loadGddm:eGetData.clientinfos.gdinfos]==NO)
					{
						[eGetData sendTradeQueryData:TDX_GDCX objIndex:tradeindex Session:eGetData.inputSave.sessionID];
						break;
					}
					else 
					{
						[eGetData.clientinfos.gdinfos CalcGdInfo:eGetData.clientinfos.logininfos.m_loginWtType withrawzjzh:eGetData.clientinfos.logininfos.m_rawzjzh];
						[eGetData setInputSaveInfo];
#ifdef JY_FXCP
                        [eGetData sendTradeQueryData:TDX_CXGPCP objIndex:tradeindex Session:eGetData.inputSave.sessionID];
                        break;
#endif
					}
				}
				[self dologinsuccess];
                
			}
			else
			{
				[self enableAllButton];		
				[tradeButtonnew setState:NSOffState];
				[hqButton setState:NSOnState];
				[self stopanimate];
				[[self window] makeFirstResponder:password_Text];
				if([pParsers IsTimeOut2]){
					[self doAfterLoginFailed];
					if (!bshowFlag) {
						return YES;
					}
					NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
													 defaultButton: @"确定"
												   alternateButton: nil
													   otherButton: nil
										 informativeTextWithFormat: pParsers.psErrorData];
					[alert setDelegate:self];
					alertFlag = YES;
					NSInteger result = [alert runModal];
					[self handleResult:alert withResult:result withTag:7];	
					
				}	
				else 
				{
					if(pParsers.btipflag)
					{
						NSString *tempString = [NSString stringWithFormat:@"错误信息:%@%@",pParsers.psErrorNum,pParsers.psErrorData];
						//NSLog(@"%@",tempString);
						NSAlert* alert = [NSAlert alertWithMessageText: @"提示"
														 defaultButton: @"确定"
													   alternateButton: nil
														   otherButton: nil
											 informativeTextWithFormat: @"%@",tempString];
						[alert setDelegate:self];
						alertFlag = YES;
						NSInteger result = [alert runModal];
						[self handleResult:alert withResult:result withTag:8];	
						
					}
					[self stopanimate];
					if(m_psecuremode.ntype==0)
					{
						[[yz_Text cell] setTitle:@""];
						[m_yzmview GenYzm];
					}
				}
			}
		}
			break;
		case TDX_GDCX:
		{
			if([eGetData getGDCXInfo:pParsers]){
                
                [eGetData.clientinfos.caches SaveGddm:eGetData.clientinfos.gdinfos];
#ifdef JY_FXCP
                [eGetData sendTradeQueryData:TDX_CXGPCP objIndex:tradeindex Session:eGetData.inputSave.sessionID];
                break;
#else
				[self dologinsuccess];
#endif
                
#ifdef JY_SDXJC
                [eGetData sendTradeQueryData:TDX_SDXJC_LOGIN objIndex:tradeindex Session:eGetData.inputSave.sessionID];
                break;
#endif
			}
			else {
				[self enableAllButton];
				[tradeButtonnew setState:NSOffState];
				[hqButton setState:NSOnState];
				[self stopanimate];
				
				if([pParsers IsTimeOut2]){
					[self doAfterLoginFailed];
					if (!bshowFlag) {
						return YES;
					}
					NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
													 defaultButton: @"确定"
												   alternateButton: nil
													   otherButton: nil
										 informativeTextWithFormat: @"获取股东代码超时!"];
					[alert setDelegate:self];
					alertFlag = YES;
					NSInteger result = [alert runModal];
					[self handleResult:alert withResult:result withTag:7];	
					
				}	
				else 
				{
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
						[self handleResult:alert withResult:result withTag:8];	
						
					}
					[self stopanimate];
					if(m_psecuremode.ntype==0)
					{
						[[yz_Text cell] setTitle:@""];
						[m_yzmview GenYzm];
					}
				}
			}

		}
			break;
        case TDX_CXGPCP:
        {
            if(pParsers.bsucflag)
            {
                int nriskflag=[[pParsers getFieldData:0 fieldFlag:TDX_ID_XT_CHECKRISKFLAG] intValue];
#ifdef IMAC_ZXJT //中信在风险标志等于0或者等于3时强制测评禁止登录
                {
                    if (nriskflag==0 || nriskflag==3) {
                        [self enableAllButton];
                        [tradeButtonnew setState:NSOffState];
                        [hqButton setState:NSOnState];
                        [self stopanimate];
                        eGetData.clientinfos.m_zjzh=nil;
                        NSString *strtsxx=@"未做测评的用户提示：尊敬的客户：根据中国证监会的有关规定，投资者在进行投资前，应完成初次及后续风险承受能力评估，请跳转至http://www.csc108.com/newsite/businesshall/fastTrade.jsp进行风险承受能力评估";
                        if([strtsxx length])
                        {
                            NSAlert* alert = [NSAlert alertWithMessageText: @"提示"
                                                             defaultButton: @"确定"
                                                           alternateButton: @"前往"
                                                               otherButton: nil
                                                 informativeTextWithFormat: @"%@",strtsxx];
                            [alert setDelegate:self];
                            alertFlag = YES;
                            NSInteger result = [alert runModal];
                            [self handleResult:alert withResult:result withTag:8];
                            
                        }
                        break;
                    }
                }
#endif
                if(nriskflag==3)
                {
                    [self enableAllButton];
                    [tradeButtonnew setState:NSOffState];
                    [hqButton setState:NSOnState];
                    [self stopanimate];
                    
                    NSString *strtsxx=[pParsers getFieldData:0 fieldFlag:TDX_ID_RETINFO];
                    if([strtsxx length])
                    {
                        NSAlert* alert = [NSAlert alertWithMessageText: @"提示"
                                                         defaultButton: @"确定"
                                                       alternateButton: nil
                                                           otherButton: nil
                                             informativeTextWithFormat: @"%@",strtsxx];
                        [alert setDelegate:self];
                        alertFlag = YES;
                        NSInteger result = [alert runModal];
                        [self handleResult:alert withResult:result withTag:8];
                        
                    }
                    break;
                }
                [self dologinsuccess];
            }
            else
            {
                
                [self enableAllButton];
                [tradeButtonnew setState:NSOffState];
                [hqButton setState:NSOnState];
                [self stopanimate];
                
                if([pParsers IsTimeOut2]){
                    [self doAfterLoginFailed];
                    if (!bshowFlag) {
                        return YES;
                    }
                    NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
                                                     defaultButton: @"确定"
                                                   alternateButton: nil
                                                       otherButton: nil
                                         informativeTextWithFormat: @"获取股东代码超时!"];
                    [alert setDelegate:self];
                    alertFlag = YES;
                    NSInteger result = [alert runModal];
                    [self handleResult:alert withResult:result withTag:7];	
                    
                }	
                else if(pParsers.btipflag)
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
                    [self handleResult:alert withResult:result withTag:8];	
                    
                }
                if(m_psecuremode.ntype==0)
                {
                    [[yz_Text cell] setTitle:@""];
                    [m_yzmview GenYzm];
                }
            }
                
            
        }
            break;
        case TDX_SDXJC_LOGIN:
        {
            if(pParsers.bsucflag)
            {
                int nriskflag=[[pParsers getFieldData:0 fieldFlag:TDX_ID_XT_CHECKRISKFLAG] intValue];
                if(nriskflag==1 || nriskflag == 0)
                {
//                    [self enableAllButton];
//                    [tradeButtonnew setState:NSOffState];
//                    [hqButton setState:NSOnState];
//                    [self stopanimate];
                    
                    NSString *strtsxx=[pParsers getFieldData:0 fieldFlag:TDX_ID_RETINFO];
                    if(strtsxx != nil && strtsxx.length > 30)
                    {
                        NSString *tmpStr = [strtsxx substringFromIndex:9];
                        tmpStr = [tmpStr substringToIndex:tmpStr.length - 16];
                        tmpStr = [tmpStr stringByReplacingOccurrencesOfString:@"\\r\\n" withString:@""];
                        eGetData.saveDate.jysdxjc_login = tmpStr;
                        eGetData.saveDate.b_isFirstUsed = YES;
                    }
//                    if([strtsxx length])
//                    {
//                        NSAlert* alert = [NSAlert alertWithMessageText: @"提示"
//                                                         defaultButton: @"确定"
//                                                       alternateButton: nil
//                                                           otherButton: nil
//                                             informativeTextWithFormat: @"%@",strtsxx];
//                        [alert setDelegate:self];
//                        alertFlag = YES;
//                        NSInteger result = [alert runModal];
//                        [self handleResult:alert withResult:result withTag:8];
//                        
//                    }
                    break;
                }
            }
        }
            break;
		default:
			break;
	}	
	return YES;
}


#pragma mark 中信建投禁止登录
- (void)ZXJTLogin:(int)type
{
    NSString *tempString;
    if (type == 0) {
      tempString = [NSString stringWithFormat:@"您所使用的客户端版本过低已经停用，敬请通过官方网站下载安装最新版本"];
    }else if (type ==1){
      tempString = [NSString stringWithFormat:@"未做测评的用户提示：尊敬的客户：根据中国证监会的有关规定，投资者在进行投资前，应完成初次及后续风险承受能力评估，请跳转至http://www.csc108.com/newsite/businesshall/fastTrade.jsp进行风险承受能力评估."];
    }
    
    NSAlert* alert = [NSAlert alertWithMessageText: @"提示"
                                     defaultButton: @"确定"
                                   alternateButton: nil
                                       otherButton: nil
                         informativeTextWithFormat: @"%@",tempString];
    [alert setDelegate:self];
    alertFlag = YES;
    NSInteger result = [alert runModal];
    [self handleResult:alert withResult:result withTag:8];
    [self stopanimate];
    if(m_psecuremode.ntype==0)
    {
        [[yz_Text cell] setTitle:@""];
        [m_yzmview GenYzm];
    }
    [self enableAllButton];

}

-(void)dologinsuccess
{
	{
        eGetData.m_nlastopertime=time(NULL);
        eGetData.tradeLoginFlag=YES;
        
		[eGetData.clientinfos.scinfos loadScInfos];
	}
	[eGetData initCHBThread];
	
	[self stopanimate];
	if(m_psecuremode.ntype==0)
	{
		[[yz_Text cell] setTitle:@""];
		[m_yzmview GenYzm];
	}
	
	//登录完成
	if (!self.loginType) {
		if (eGetData.clientinfos.localhqsites.bfindbest && [eGetData.clientinfos.localhqsites.tradesites count]>1) {
			[[showTips cell] setTitle:@"正在查找最快行情主站......"];
			
			
			int bfastflag=[eGetData FindFastedHqSite];
			
			if(bfastflag==NO)
			{
				[self getBaseInfo];
			}
		}
		else {
			[self getBaseInfo];
		}
		
	}
	else {
		[showDelegate afterLogin];
	}
}

#pragma mark button事件相关
-(void)doneButtonClick
{
	if([self IsCanQueryOther]==NO)
		return;
	[self doasynclogin];
}

-(void)cancelButtonClick
{
	if([self IsCanQueryOther]==NO)
		return;
	[showDelegate closeLogin];
}


#pragma mark alert事件相关
-(void)handleResult:(NSAlert *)alert withResult:(NSInteger)result  withTag:(int)_tag{
	
	switch(result)
	{
		case NSAlertDefaultReturn:{
			[self performSelector:@selector(dealErrorFocus:) withObject:[NSString stringWithFormat:@"%i",_tag] afterDelay:0.1f];
		}
			break;
			
        case NSAlertAlternateReturn:{
            #ifdef IMAC_ZXJT
            NSURL *url = [[NSURL alloc] initWithString:@"http://www.csc108.com/newsite/businesshall/fastTrade.jsp"];
            [[NSWorkspace sharedWorkspace] openURL:url];
            #endif
        }
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
		case 1:	
			[[self window] makeFirstResponder:account_Combobox];
			break;
		case 2:	
		case 8:
			[[self window] makeFirstResponder:password_Text];
			break;	
		case 5:
			[[self window] makeFirstResponder:authpass_Text];
			break;
		case 3:
		case 4:
		case 6:	
			[[self window] makeFirstResponder:yz_Text];
			break;
		case 7:
			break;
		case 10:
			[showDelegate closeLogin];
			break;
		case 11:
			initHQFlag = YES;
			[showDelegate afterInit];
			break;

		default:
			break;
	}
}

- (void)drawRect:(NSRect)dirtyRect {
   
}


-(void) dealloc{
	[super dealloc];
	[hqButton release];
	[tradeButtonnew release];
	[loginTypeLabel release];
	[showTips release];
    [formatter release];
    [formatter1 release];
    [txSetButton release];
}

-(int)SetVirtualYybID
{
	int TdxBranchID = 0;
	int nyybrangenum=0,i=0;
	Vyyb *pvyyb=nil;
    
    JyConfig *pconfig=nil;
    if([eGetData.clientinfos.qsconfigs.jyconfigs count]>0)
        pconfig=[eGetData.clientinfos.qsconfigs.jyconfigs objectAtIndex:0];
	if(pconfig)
		pvyyb=pconfig.vyybs;
	if(pvyyb && pvyyb.yybrange)
		nyybrangenum=[pvyyb.yybrange count];
    BOOL bzxjtptjyflag=NO;
    if(eGetData.clientinfos.m_nQsbs==ZXJT_DLL && [m_pyyb.yybname isEqualToString:@"普通交易"])
        bzxjtptjyflag=YES;
    
//#ifdef IMAC_GXZQ
    NSString *tmpstr=[NSString stringWithString:[[account_Combobox cell] title]];
    int nzhlen=[tmpstr length];
    int wttype=9;
    if(m_ploginmode)
        wttype=m_ploginmode.zhlx;
    if(nzhlen<8 && m_pyyb && wttype==SHHY)
    {
        NSString *strformat=[NSString stringWithFormat:@"%%@%%0%ii%%@",8-nzhlen];
        NSString *tmpstr1=[NSString stringWithFormat:strformat,m_pyyb.yybid,0,tmpstr];
        
        [[account_Combobox cell] setTitle:tmpstr1];
    }
//#endif
	if((!m_pyyb || bzxjtptjyflag) && pvyyb && nyybrangenum>0)
	{
		long nHeadAccount=0;
		NSString *tmpstr=[NSString stringWithString:[[account_Combobox cell] title]];
		if(eGetData.clientinfos.m_nQsbs==ZXJT_DLL && [tmpstr length]==7)
		{
			tmpstr=[NSString stringWithFormat:@"0%@",[[account_Combobox cell] title]];
		    [[account_Combobox cell] setTitle:tmpstr];
		}
        if(pvyyb.headlen>=1 && [tmpstr length]>pvyyb.headlen)
            nHeadAccount=[[tmpstr substringToIndex:(pvyyb.headlen)] intValue] ;
		if(eGetData.clientinfos.m_nQsbs==ZXJT_DLL && [tmpstr length]<pvyyb.maxaccountlen)
		{
			TdxBranchID=nyybrangenum+1;
			return TdxBranchID;
		}
		else
		{
			for(YybRange *prange in pvyyb.yybrange)
			{
				for(i=0;i<prange.nRealNum;i++)
				{
					if(nHeadAccount>=[prange GetStartRange:i] && nHeadAccount<=[prange GetEndRange:i])
					{
						TdxBranchID=prange.id;
						return TdxBranchID;
					}
				}
			}
		}
	}
	else  if(m_pyyb)
	{
		TdxBranchID=[m_pyyb.yybid intValue];
		return TdxBranchID;
	}
	return 0;
}

-(void)initT2ee
{
    m_t2ee=[[TdxT2EEEx alloc] InitWithParam:eGetData];
    m_t2ee.mydelegate=self;
}

#pragma mark SSLDelegate

-(void)StartLogin:(BOOL)bsucflag
{
    if(bsucflag)
        [eGetData sendTradeQueryData:TDX_KHXY objIndex:tradeindex Session:0];
    else
    {
        [self stopanimate];
        if(m_psecuremode.ntype==0)
        {
            [[yz_Text cell] setTitle:@""];
            [m_yzmview GenYzm];
        }
        [self enableAllButton];
    }
}

-(void)OnSaveZhClick
{
}

-(void)txSetClick
{
    [showDelegate onTeleSet];
}
@end
