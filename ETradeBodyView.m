//
//  ETradeBodyView.m
//  tdxMac
//
//  Created by tdx on 11-10-26.
//  Copyright 2011 武汉. All rights reserved.
//

#define WTWITHPK_WIDTH 400

#import "ETradeBodyView.h"


@implementation ETradeBodyView
@synthesize wtView,userInfo,wtCancel,bankView,currFunc,passwordView;

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
		self.tradeindex = [_eGetData.g_TradeComm.areceiver SetWinobjs:self];
		readYHXXFLag = NO;
        isFirstLogin = YES;
		viewRect = frame;
		wtView = [[ETradeWTView alloc] initWithData:NSMakeRect(0, 0, WTWITHPK_WIDTH, frame.size.height) theData:_eGetData showType:1];
        wtView.bDelegates=self;
		[wtView setFrame:NSZeroRect];
		[self addSubview:wtView];
        breadyhxxflag2=NO;
		
		userInfo = [[ETradeUserInfoView alloc] initWithData:NSMakeRect(WTWITHPK_WIDTH, 0, frame.size.width-WTWITHPK_WIDTH, frame.size.height) theData:_eGetData WithTag:USER_Info_STK];
		[userInfo setFrame:NSZeroRect];
		[self addSubview:userInfo];

		
		wtCancel = [[ETradeWTCancelView alloc] initWithData:NSMakeRect(WTWITHPK_WIDTH, 0, frame.size.width-WTWITHPK_WIDTH, frame.size.height) theData:_eGetData WithTag:WT_CANCEL_STK];
		[wtCancel setFrame:NSZeroRect];
		[self addSubview:wtCancel];
		
		bankView = [[ETradeBankView alloc] initWithData:NSMakeRect(WTWITHPK_WIDTH, 0, frame.size.width-WTWITHPK_WIDTH, frame.size.height) theData:_eGetData];
		[bankView setFrame:NSZeroRect];
		[self addSubview:bankView];
		
		passwordView = [[ETradePasswordView alloc] initWithData:NSMakeRect(WTWITHPK_WIDTH, 0, frame.size.width-WTWITHPK_WIDTH, frame.size.height) theData:_eGetData];
		[passwordView setFrame:NSZeroRect];
		[self addSubview:passwordView];
	}
	return self;
}

-(void) setFrame:(NSRect)frame{
    [super setFrame:frame];
    viewRect = frame;
    [self dealTradeShow];
    [self dealViewSize];
    
}

-(void)clearAllView{
    [wtView setFrame:NSZeroRect];
    [userInfo setFrame:NSZeroRect];
    [wtCancel setFrame:NSZeroRect];
    [bankView setFrame:NSZeroRect];
    [passwordView setFrame:NSZeroRect];
    [wtView removeFromSuperview];
    [userInfo removeFromSuperview];
    [wtCancel removeFromSuperview];
    [bankView removeFromSuperview];
    [passwordView removeFromSuperview];
    [userInfo cleardsdata];
    [wtCancel cleardsdata];
}

-(void)cleandata{
    [wtView cleanscreen];
    [userInfo cleardsdata];
    [wtCancel cleanscreen];
    [bankView cleardsdata];
}

-(void)dealTradeShow{
    switch (currFunc) {
        case MAC_WT_FUNC://下单
            [wtView setFrame:NSMakeRect(0, 0, WTWITHPK_WIDTH, viewRect.size.height)];
            [userInfo setFrame:NSMakeRect(WTWITHPK_WIDTH, 0, viewRect.size.width-WTWITHPK_WIDTH, viewRect.size.height)];
            break;
        case MAC_TRADE_FUNC:
            [userInfo setFrame:NSMakeRect(0, 0, viewRect.size.width, viewRect.size.height)];
            break;
        case MAC_CANCEL_FUNC:
            [wtCancel setFrame:NSMakeRect(0, 0, viewRect.size.width, viewRect.size.height)];
            break;
        case MAC_BANK_FUNC:
            [bankView setFrame:NSMakeRect(0, 0, viewRect.size.width, viewRect.size.height)];
            break;
        case MAC_PASSWORD_FUNC:
            [passwordView setFrame:NSMakeRect(0, 0, viewRect.size.width, viewRect.size.height)];
            break;
            
        default:
            break;
    }
}

-(void)dealViewSize{
    [wtView setFrame:NSMakeRect(0, viewRect.origin.y, WTWITHPK_WIDTH, viewRect.size.height)];
    //[wtView setNeedsDisplay:YES];
}

-(void)dealTradeProcess:(NSString *)_gpcode gpSetcode:(int)_setcode typeID:(int)_typeID pareOne:(int)_paraone paraTwo:(int)_paraTwo pareThree:(NSString *)_paraThree{
    

    
    [NSObject cancelPreviousPerformRequestsWithTarget:self selector:@selector(getRefreshTradeData) object:nil];
    [[self window] makeFirstResponder:self];
    
    if(_typeID==MAC_REFRESH_FUNC && currFunc==MAC_BANK_FUNC && bankView.tag==IPHONE_WT_YHYE)
    {
        [bankView cleanscreen];
        return;
    }
    
    if (_typeID != MAC_REFRESH_FUNC) {
        currFunc = _typeID;
    }
    switch (_typeID) {
        case MAC_WT_FUNC://下单
            [self clearAllView];
            
            [wtView setFrame:NSMakeRect(0, 0, WTWITHPK_WIDTH, viewRect.size.height)];
            [self addSubview:wtView];
            [wtView cleanscreen];
            
            if (_paraone > -1) {
                [wtView setTag:_paraone];//设置买入还是卖出
            }
            else {
                if (wtView.tag == 1) {
                    [wtView setTag:1];
                }
            }
            
            
            if ([_gpcode length] > 0) {
                [[wtView.gpcodeText cell] setTitle:_gpcode];
            }
            if ([_paraThree length] > 0) {
                [[wtView.gppriceText cell] setTitle:_paraThree];
            }
            
            wtView.m_brefreshflag = NO;
            [wtView onviewWillAppear];
            
            if(eGetData.tradeType != XJHK)
            {
                [userInfo setFrame:NSMakeRect(WTWITHPK_WIDTH, 0, viewRect.size.width-WTWITHPK_WIDTH, viewRect.size.height)];
                [userInfo setToolbarShowFlag:NO];
                
                switch (_paraone)
                {
                        //买券还券，查询到的数据
                    case MQHQ:
                        [userInfo setTag:TDX_XYMQHQCX];
                        break;
                    case XJHK:
                        [userInfo setTag:TDX_XYXJHKCX];
                        break;
                    case XQHQ:
                        [userInfo setTag:TDX_XYXQHQCX];
                        break;
                    default:
                        [userInfo setTag:TDX_GFCX];
                        break;
                }
                
                [userInfo onviewDidAppear:NO];
                [self addSubview:userInfo];
            }

            
            if(eGetData.tradeType == XJHK)
            {
                [self getXJHKDataFromServer];
            }
            else
            {
                [self performSelector:@selector(getRefreshTradeData) withObject:nil afterDelay:10];
            }
            
            
            if(eGetData.tradeType == DBPSell && ![eGetData.saveDate.xwdm isEqualToString:@""])
            {
                [[wtView.maxbuysellLabel cell] setTitle:[NSString stringWithFormat:@"%d",_paraTwo]];
            }
            
            break;
        case MAC_TRADE_FUNC:
            [self clearAllView];
            userInfo.tag=_paraone;
            [userInfo setFrame:NSMakeRect(0, 0, viewRect.size.width, viewRect.size.height)];
            [self addSubview:userInfo];
            [userInfo setToolbarShowFlag:YES];
            [userInfo onviewDidAppear:NO];
            
            break;
        case MAC_CANCEL_FUNC:
            [self clearAllView];
            [wtCancel setFrame:NSMakeRect(0, 0, viewRect.size.width, viewRect.size.height)];
            [self addSubview:wtCancel];
            [wtCancel setToolbarShowFlag:YES];
            if (_paraone == TDX_DRWT) {
                wtCancel.m_bdrwtcx = YES;
            }
            else if(_paraone == TDX_CDCX){
                wtCancel.m_bdrwtcx = NO;
                wtCancel.m_ncdType = 0;
            }
            else if(_paraone == TDX_DBPHZCDCX)
            {
                wtCancel.m_bdrwtcx = NO;
                wtCancel.m_ncdType = 1;
            }
            [wtCancel onviewDidAppear:NO];
            break;
        case MAC_BANK_FUNC:
            if(_paraone == TDX_YECX)
                [bankView cleanscreen];
			if ([self IsNeedQueryYhInfo] && breadyhxxflag2==NO) {
				readYHXXFLag = YES;
				bakFunc = _paraone;
				[eGetData sendTradeQueryData:TDX_YHXX objIndex:self.tradeindex Session:eGetData.inputSave.sessionID];
				
			}
			else {
				if (readYHXXFLag) {
					return;
				}
				
				if (_paraone == TDX_YZZZ) {
					[self clearAllView];
					[bankView setFrame:NSMakeRect(0, 0, viewRect.size.width, viewRect.size.height)];
					[self addSubview:bankView];
					[bankView setTag:IPHONE_WT_BANKTOSEC];	
					[bankView onviewWillAppear];
				}
				else if(_paraone == TDX_YECX) {
					[self clearAllView];
					[bankView setFrame:NSMakeRect(0, 0, viewRect.size.width, viewRect.size.height)];
					[self addSubview:bankView];
					[bankView setTag:IPHONE_WT_YHYE];	
					[bankView onviewWillAppear];
				}
				else if(_paraone == TDX_ZZCX){
					[self dealTradeProcess:@"" gpSetcode:-1 typeID:MAC_TRADE_FUNC pareOne:TDX_ZZCX paraTwo:-1 pareThree:@""];
				}
				else if(_paraone == TDX_PT_ZJZZ){
                    [self clearAllView];
                    [bankView setFrame:NSMakeRect(0, 0, WTWITHPK_WIDTH, viewRect.size.height)];
                    [self addSubview:bankView];
                    [bankView setTag:IPHONE_WT_ZJZZ];
                    [bankView onviewWillAppear];
                    
                    [userInfo setFrame:NSMakeRect(WTWITHPK_WIDTH, 0, viewRect.size.width-WTWITHPK_WIDTH, viewRect.size.height)];
                    [userInfo setTag:TDX_DZJZHCX];
                    [self addSubview:userInfo];
                    [userInfo setToolbarShowFlag:NO];
                    [userInfo onviewDidAppear:NO];
                }
                breadyhxxflag2=NO;
            }
            
            break;
            
        case MAC_REFRESH_FUNC:
            if (currFunc == MAC_WT_FUNC) {
                [wtView refreshHqData];
                [userInfo onviewDidAppear:NO];
            }
            else if(currFunc == MAC_TRADE_FUNC){
                [userInfo refreshpage2];
            }
            else if(currFunc == MAC_CANCEL_FUNC){
                [wtCancel onviewDidAppear:NO];
            }
            break;
        case MAC_PASSWORD_FUNC:
			[self clearAllView];
			[passwordView setFrame:NSMakeRect(0, 0, viewRect.size.width, viewRect.size.height)];
			[self addSubview:passwordView];
			[passwordView onviewWillAppear];
			break;

		default:
			break;
	}
    
#ifdef JY_SDXJC
    if(eGetData.saveDate.b_isFirstUsed)
    {
        [self performSelector:@selector(popAlertInfo) withObject:nil afterDelay:1.5];
    }
#endif
    
#ifdef IMAC_ZSZQ
    if (isFirstLogin == YES) {
        isFirstLogin = NO;
        WelComeView = [[NSView alloc] initWithFrame:NSMakeRect(0, 0, viewRect.size.width-WTWITHPK_WIDTH, viewRect.size.height)];
        [WelComeView setWantsLayer:YES];
        WelComeView.layer.backgroundColor = [NSColor colorWithCalibratedRed:231.0/255.0 green:231.0/255.0 blue:231.0/255.0 alpha:1.000].CGColor;
        [self configWelComeView];
        [self addSubview:WelComeView];
        [userInfo removeFromSuperview];
        
    }else{
        [self addSubview:userInfo];
        [WelComeView removeFromSuperview];
    }
#endif
}

-(void)popAlertInfo
{
    if(eGetData.saveDate.b_isFirstUsed)
    {
        NSAlert* alert = [NSAlert alertWithMessageText: @"提示"
                                         defaultButton: @"确定"
                                       alternateButton: nil
                                           otherButton: nil
                             informativeTextWithFormat: @"%@", eGetData.saveDate.jysdxjc_login];
        [alert runModal];
        eGetData.saveDate.b_isFirstUsed = NO;
    }
}

- (NSString *)getloginLXBy:(NSString *)num
{
    NSString *LXTitle;
    if([num isEqualToString:@"0"]){
        LXTitle = @"自助委托";
    }else if([num isEqualToString:@"1"]){
        LXTitle = @"电话交易";
    }else if([num isEqualToString:@"2"]){
        LXTitle = @"可视委托";
    }else if([num isEqualToString:@"3"]){
        LXTitle = @"柜台委托";
    }else if([num isEqualToString:@"4"]){
        LXTitle = @"柜台委托";
    }else if([num isEqualToString:@"5"]){
        LXTitle = @"网上交易";
    }else if([num isEqualToString:@"6"]){
        LXTitle = @"集中电话";
    }else if([num isEqualToString:@"7"]){
        LXTitle = @"套利委托";
    }else if([num isEqualToString:@"8"]){
        LXTitle = @"手机交易";
    }else if([num isEqualToString:@"9"]){
        LXTitle = @"自营委托";
    }else if([num isEqualToString:@"a"]){
        LXTitle = @"资产管理委托";
    }else if([num isEqualToString:@"b"]){
        LXTitle = @"算法交易委托";
    }else if([num isEqualToString:@"c"]){
        LXTitle = @"电话销售";
    }else if([num isEqualToString:@"d"]){
        LXTitle = @"电话代填";
    }else if([num isEqualToString:@"e"]){
        LXTitle = @"高级算法";
    }else if([num isEqualToString:@"f"]){
        LXTitle = @"快速交易";
    }else if([num isEqualToString:@"m"]){
        LXTitle = @"银行委托";
    }
    return LXTitle;
}

- (void)configWelComeView
{
    NSRect WFrame =  WelComeView.frame;
    NSTextField * tempText = [[NSTextField alloc]init];
    [tempText setEditable:NO];
    [tempText setBackgroundColor:[NSColor clearColor]];
    [tempText setBordered:NO];
    [tempText setFrame:NSMakeRect(WFrame.size.width/2-250, WFrame.size.height-40, WFrame.size.width/2, 25)];
    [[tempText cell] setFont:[NSFont systemFontOfSize:20.0f]];
    [[tempText cell] setTextColor:[NSColor redColor]];
    [[tempText cell] setTitle:@"您好,欢迎使用招商证券全能版"];
    [WelComeView addSubview:tempText];
    
    NSArray * title = [eGetData.clientinfos.dldzxy componentsSeparatedByString:@"\\r\\n\\r\\n"];
    if([title count]<=1)
        return;
    
    NSArray * ftitle =[title[0] componentsSeparatedByString:@","];
    if([ftitle count]<=3)
        return;
    NSString *XyStr=ftitle[0];
    

    NSString *XYStr = [NSString stringWithFormat:@"您最近是使用%@方式登录",[self getloginLXBy:XyStr]];
    
    int year = [ftitle[1] intValue]/10000;
    int month = ([ftitle[1] intValue] -year*10000)/100;
    int day =[ftitle[1] intValue] -year*10000 -month*100;
    NSString *timeStr = [NSString stringWithFormat:@"登录时间:%i年%i月%i日%@",year,month,day,ftitle[2]];
    NSString *ipStr=[NSString stringWithFormat:@"登录ip:%@",ftitle[3]];
    NSString *drxy =  title[1];
    NSArray * titleArray=[[NSArray arrayWithObjects:XYStr,timeStr,ipStr,drxy,nil] retain];
    
    CGFloat titleHeight = 25;
    for (int i = 0; i<titleArray.count; i++) {
        NSTextField * tempText = [[NSTextField alloc]init];
        [tempText setEditable:NO];
        [tempText setBackgroundColor:[NSColor clearColor]];
        [tempText setBordered:NO];
        [tempText setFrame:NSMakeRect(WFrame.size.width/2-250, WFrame.size.height-65-titleHeight*i, WFrame.size.width/2, 20)];
        [[tempText cell] setFont:[NSFont systemFontOfSize:14.0f]];
        [[tempText cell] setTextColor:[NSColor blackColor]];
        [[tempText cell] setTitle:titleArray[i]];
        [WelComeView addSubview:tempText];
    }
}

#pragma mark 从后台获取显示数据
-(void)getXJHKDataFromServer
{
    if (currFunc == MAC_WT_FUNC)
    {
        [wtView getXJHKData];
    }
}

#pragma mark 刷新相关
-(void)getRefreshTradeData{
    //NSLog(@"456");
    if (currFunc == MAC_WT_FUNC) {
        
        [wtView refreshHqData];
        [self performSelector:@selector(getRefreshTradeData) withObject:nil afterDelay:10];
    }
}


-(BOOL)IsNeedQueryYhInfo
{
    //查询银行信息
    if(eGetData.clientinfos.yhxxs.bqueryyhflag==NO)
    {
        if([eGetData.clientinfos.caches loadYhxx:eGetData.clientinfos.yhxxs]==NO)
        {
            return YES;
        }
        eGetData.clientinfos.yhxxs.bqueryyhflag=YES;
    }
    return NO;
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
        case TDX_YHXX:
        {
            if([pParsers IsTimeOut])
            {
                NSString *errinfo=[NSString stringWithFormat:@"错误信息:%@,%@",pParsers.psErrorNum,pParsers.psErrorData];
                
                NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
                                                 defaultButton: @"确定"
                                               alternateButton: nil
                                                   otherButton: nil
                                     informativeTextWithFormat: @"%@",errinfo];
                [alert runModal];	
                [NSTimer scheduledTimerWithTimeInterval: 0.0f target:self selector: @selector(doasyncfail) userInfo: nil repeats: NO];
                return YES;
            }
            if([eGetData getYHXXInfo:pParsers])
            {
                [eGetData.clientinfos.caches SaveYhxx:eGetData.clientinfos.yhxxs];
                eGetData.clientinfos.yhxxs.bqueryyhflag=YES;
                [NSTimer scheduledTimerWithTimeInterval: 0.0f target:self selector: @selector(doasyncsuc) userInfo: nil repeats: NO];
            }
            else 
                [NSTimer scheduledTimerWithTimeInterval: 0.0f target:self selector: @selector(doasyncfail) userInfo: nil repeats: NO];
        }
            break;
    }
    return YES;
}
-(void)doasyncsuc
{
    breadyhxxflag2=YES;
    readYHXXFLag = NO;
    [self doyzzz];
}

-(void)doyzzz
{
    if (bakFunc == TDX_YZZZ) {
		[self dealTradeProcess:@"" gpSetcode:-1 typeID:MAC_BANK_FUNC pareOne:TDX_YZZZ paraTwo:-1 pareThree:@""];
	}
	else if(bakFunc == TDX_YECX) {
		[self dealTradeProcess:@"" gpSetcode:-1 typeID:MAC_BANK_FUNC pareOne:TDX_YECX paraTwo:-1 pareThree:@""];
	}
	else if(bakFunc == TDX_ZZCX){
		[self dealTradeProcess:@"" gpSetcode:-1 typeID:MAC_TRADE_FUNC pareOne:TDX_ZZCX paraTwo:-1 pareThree:@""];
	}
	else if(bakFunc == TDX_PT_ZJZZ){
        [self dealTradeProcess:@"" gpSetcode:-1 typeID:MAC_BANK_FUNC pareOne:TDX_PT_ZJZZ paraTwo:-1 pareThree:@""];
    }
}

-(void)doasyncfail
{
    breadyhxxflag2=YES;
    readYHXXFLag = NO;
    [self doyzzz];
}


- (void)drawRect:(NSRect)dirtyRect {
}

-(void)OnWtSuccess
{
    [userInfo refreshpage];
}
@end
