//
//  EUMainView.m
//  tdxMac
//
//  Created by tdx on 11-8-31.
//  Copyright 2011 武汉. All rights reserved.
//


#define BOTTOM_DP_HEIHGT 20
#define EUKEY_WIDTH 180
#define EUKEY_HEIGHT 220
#define TRADEVIEW_HEIGHT 285
#define CHAINWANTNUM 500

#import "EUMainView.h"
#import "MyWindowController.h"


@implementation EUMainView
@synthesize euGrid,stockArray,euZst,euFxt,tradeShowFlag,showDelegate,fastWTShowFlag,tradeView,controllerDelegate,tradeChangeSizeShowFlag;
@synthesize webView;

- (id)initWithFrame:(NSRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code here.
    }
    return self;
}

-(id) initWithData:(NSRect)frame theData:(EGetData *)_eGetData{
	self = [super initWithData:frame theData:_eGetData];
    if (self) {
		viewRect = frame;
		
       
        // Initialization code here.
		NSRect tempframe;
		tempframe.origin.x = 0;
		tempframe.origin.y=BOTTOM_DP_HEIHGT;
		tempframe.size.width = frame.size.width;
		tempframe.size.height = frame.size.height-BOTTOM_DP_HEIHGT;
		
		stockArray = [[StockArray alloc] init];
		[stockArray readData];
        
		NSRect bottomframe;
		bottomframe.origin.x = 0;
		bottomframe.origin.y=0;
		bottomframe.size.width = frame.size.width;
		bottomframe.size.height = BOTTOM_DP_HEIHGT;
		
		euBottom = [[EUBottom alloc] initWithData:bottomframe theData:eGetData];
		euBottom.operProcessDelegate = self;
		[self addSubview:euBottom];
		[euBottom getDpData];
		[euBottom showTips];
        
        
		
		euGrid = [[EUGrid alloc] initWithData:tempframe theData:eGetData];
		euGrid.operProcessDelegate = self;
		euGrid.operZXGDelegate = self;
        
        
		
		euZst = [[EUZst alloc] initWithData:tempframe theData:eGetData];
		euZst.operProcessDelegate = self;
		euZst.operZXGDelegate = self;
		euZst.hq.operProcessDelegate=self;
		euZst.hq.operZXGDelegate = self;
		euZst.zst.operProcessDelegate = self;
		euZst.fxt.operProcessDelegate = self;
        
        
		
		euFxt = [[EUFxt alloc] initWithData:tempframe theData:eGetData];
		euFxt.operProcessDelegate = self;
        
        
		
		self.webView = [[EUWebView alloc] initWithData:tempframe theData:eGetData];
		self.webView.operProcessDelegate = self;
        
        
		
		euF10 = [[EUF10 alloc] initWithData:tempframe theData:eGetData];
		euF10.operProcessDelegate = self;
        
        
		
		NSRect keyframe;
		keyframe.origin.x = frame.size.width - EUKEY_WIDTH-210;
		keyframe.origin.y=BOTTOM_DP_HEIHGT;
		keyframe.size.width = EUKEY_WIDTH;
		keyframe.size.height = EUKEY_HEIGHT;
		euKey = [[EUKey alloc] initWithData:keyframe theData:eGetData];
		euKey.operProcessDelegate = self;

        
        tradeView=nil;
		
		
		euMine = [[EUMine alloc] initWithData:NSMakeRect(0, euBottom.frame.size.height, frame.size.width, TRADEVIEW_HEIGHT) theData:eGetData];
		euMine.operProcessDelegate = self;
		
		currFunc = -1;
		currView = nil;
		searchString= nil;
		tradeShowFlag = NO;
		reloadFlag = NO;
		fastWTShowFlag = NO;
		mineShowFlag = NO;
		
        
        
		
		eGetData.g_pEComm.menuDelegate = self;
        
        [self performSelector:@selector(OnAutoLockScreen) withObject:nil afterDelay:1];
    }
    return self;
}


-(void)OnAutoLockScreen
{
    if(eGetData.tradeLoginFlag && !eGetData.clientinfos.m_blocking)
    {
        if((time(NULL)-eGetData.m_nlastopertime)>=eGetData.njylockspan*60)
        {
            eGetData.clientinfos.m_blocking=YES;
            [tradeView showlockscreen];
        }
    }
    [self performSelector:@selector(OnAutoLockScreen) withObject:nil afterDelay:1];
}

-(void)clearAllView{
	[euGrid removeFromSuperview];
	[euZst removeFromSuperview];
	[euFxt removeFromSuperview];
	[euF10 removeFromSuperview];
	[self.webView removeFromSuperview];
	[euMine removeFromSuperview];
}

#pragma mark  system delegate相关
-(void)changeSortRefreshTimer{
}

-(void)lockScreen{
	[tradeView showlockscreen];
}

-(void)showSystemFunc:(int)_funcIndex {
	if (_funcIndex == 0) {  //交易登录
	
	}
	else if(_funcIndex ==1){  //切换用户
		[self closeButtonClick];
		[showDelegate showLogin];
	}
	else if(_funcIndex ==2){  //退出交易
		[self closeButtonClick];
		
	}
	else if(_funcIndex ==3){
	
	}
	else if(_funcIndex ==4){
	
	}
	else if(_funcIndex ==5){  
		
	}
}


-(void)afterReconnRefresh{
	[NSObject cancelPreviousPerformRequestsWithTarget:self selector:@selector(getTheRefreshData) object:nil];
	reloadFlag = YES;
	[self getTheRefreshData];
}

-(void)showConnTips{
	[euBottom showTips];
}

-(void)showInitConnTips{
	eGetData.initStockChainFlag = YES; //
	[NSObject cancelPreviousPerformRequestsWithTarget:self selector:@selector(getTheRefreshData) object:nil];
	[euZst clearScreenInInit];
	[euBottom showInitTips];
	initRefreshTimer = [[NSTimer scheduledTimerWithTimeInterval: 1.0f target:self selector: @selector(checkTheInitRefresh)  userInfo: nil   repeats: YES] retain];
}

-(void)checkTheInitRefresh{
	euBottom.theRepeatCount = euBottom.theRepeatCount - 1;
	[euBottom showRefreshTips];
	
	if (euBottom.theRepeatCount <= 0) {
		[euBottom showAfterInitTips];
		[initRefreshTimer invalidate];
		[initRefreshTimer release],initRefreshTimer = nil;
		
		
		reloadFlag = YES;
		NSMutableData * theData = [eGetData getHostBaseDataReqEx];	
		[eGetData.g_pEComm AsyncSendData:theData length:[theData length] withobjIndex:self.windindex withreqIndex:1];
	}
}

#pragma mark processDelegate
-(void)getTheTitleName:(NSString *)_titleName{
	[showDelegate dealTitleName:_titleName];
}

-(void)getTheGridType{
	[showDelegate dealSortSelect:euGrid.gridInfo.grid_domain sortType:euGrid.gridInfo.coltype];
}

-(int)getHQCurrFunc{
	return currFunc;
}
-(int)getTradeCurrFunc{
	return tradeView.bodyView.currFunc;
}

-(void)getHQProcess:(NSString *)_gpcode gpSetcode:(int)_setcode typeID:(int)_typeID pareOne:(int)_paraone paraTwo:(int)_paraTwo{
	if (eGetData.initStockChainFlag) {
		return;
	}
	
	if (keyShowFlag) {
		[self dismissKeyboard];
	}

	eGetData.bakFunc = currFunc;
	[NSObject cancelPreviousPerformRequestsWithTarget:self selector:@selector(getTheRefreshData) object:nil];
	
	switch (_typeID) {
		case MAC_ZFPM_FUNC:{
			if (currFunc != MAC_ZFPM_FUNC) {
				[self clearAllView];
				[self addSubview:euGrid];

                
				currFunc = MAC_ZFPM_FUNC;
				currView=euGrid;
				[[self window] makeFirstResponder:euGrid];

			}
			else {
				
			}
			[euGrid getTheData:_paraone theColtype:_paraTwo];
		}
			break;
		case MAC_ZST_FUNC:{
			if (currFunc != MAC_ZST_FUNC) {
				[self clearAllView];
				[self addSubview:euZst];
				
				if ([_gpcode isEqualToString:@""]) {
					self.gpcode = [NSString stringWithFormat:@"%@",currView.gpcode];
					self.setcode = currView.setcode;
					
				}
				
				currFunc = MAC_ZST_FUNC;
				currView=euZst;
				[[self window] makeFirstResponder:euZst];
			}
			else {
				if ([_gpcode isEqualToString:@""]) {
					self.gpcode = [NSString stringWithFormat:@"%@",euZst.gpcode];
					self.setcode = euZst.setcode;					
				}
			}
			
			if (_paraone == 1) {
				[euZst setSwitchInfo:1];
			}
			
			if (_paraone == 2) {
				[euZst setSwitchInfo:2];
			}
			
			if (_paraTwo == 1) {
				if ([euZst.gpcode isEqualToString:_gpcode]) {
					//return;
				}
				else {
					if ([_gpcode isEqualToString:@""]) {
						[euZst getHqData:self.gpcode setcode:self.setcode reloadFlag:YES];
						
					}
					else {
						[euZst getHqData:_gpcode setcode:_setcode reloadFlag:YES];
						
					}
				}

			}
			else {
				if (_paraTwo == 2) {
					if ([_gpcode isEqualToString:@""]) {
						[euZst getHqData:self.gpcode setcode:self.setcode reloadFlag:NO];
						
					}
					else {
						[euZst getHqData:_gpcode setcode:_setcode reloadFlag:NO];
						
					}
				}
				else {
					if ([_gpcode isEqualToString:@""]) {
						[euZst getHqData:self.gpcode setcode:self.setcode reloadFlag:YES];
						
					}
					else {
						[euZst getHqData:_gpcode setcode:_setcode reloadFlag:YES];
						
					}
				}
			}

		}
			break;
		case MAC_SWITCH_FUNC:
			if ([_gpcode isEqualToString:@""]) {
				self.gpcode = [NSString stringWithFormat:@"%@",currView.gpcode];
				self.setcode = currView.setcode;
			}
			else {
				self.gpcode = [NSString stringWithFormat:@"%@",_gpcode];
				self.setcode = _setcode;
			}

			
			if ((currFunc == MAC_ZFPM_FUNC)|| (currFunc == MAC_F10_FUNC)){
				[self getHQProcess:self.gpcode gpSetcode:self.setcode typeID:MAC_ZST_FUNC pareOne:1 paraTwo:-1];
			}
			else if(currFunc == MAC_ZST_FUNC) {
				if (euZst.showFlag == 1) {
					[self getHQProcess:self.gpcode gpSetcode:self.setcode typeID:MAC_ZST_FUNC pareOne:2 paraTwo:-1];
				}
				else if(euZst.showFlag == 2){
					[self getHQProcess:self.gpcode gpSetcode:self.setcode typeID:MAC_ZST_FUNC pareOne:1 paraTwo:-1];
				}
			}

			break;
	
		case MAC_FXT_FUNC:{
			[euZst setFxtInfo:_paraone ZBIndex:_paraTwo];
			
			
			if ([_gpcode isEqualToString:@""]) {
				self.gpcode = [NSString stringWithFormat:@"%@",currView.gpcode];
				self.setcode = currView.setcode;
			}
			else {
				self.gpcode = [NSString stringWithFormat:@"%@",_gpcode];
				self.setcode = _setcode;
			}
			
			if (currFunc == MAC_ZST_FUNC  && euZst.showFlag == 2) {
				if (_paraone>-1) {
					[self getHQProcess:self.gpcode gpSetcode:self.setcode typeID:MAC_ZST_FUNC pareOne:2 paraTwo:2];
				}
				else {
					[euZst.fxt setNeedsDisplay:YES];
				}
			}
			else {
				[self getHQProcess:self.gpcode gpSetcode:self.setcode typeID:MAC_ZST_FUNC pareOne:2 paraTwo:2];
			}

		}
		break;
		case MAC_F10_FUNC:
			if (currFunc != MAC_F10_FUNC) {
				[self clearAllView];
				[self addSubview:euF10];
				currFunc = MAC_F10_FUNC;
				
				if ([_gpcode isEqualToString:@""]) {
					self.gpcode = [NSString stringWithFormat:@"%@",currView.gpcode];
					self.setcode = currView.setcode;
				}
				
				currView=euF10;
				[[self window] makeFirstResponder:euF10];
				
				
			}
			else {
			}
			
			if ([_gpcode isEqualToString:@""]) {
				[euF10 getF10Data:gpcode setcode:setcode reloadFlag:YES];
			}
			else {
				[euF10 getF10Data:_gpcode setcode:_setcode reloadFlag:YES];
			}

			
			break;
		case MAC_WEB_FUNC:
			if (currFunc != MAC_WEB_FUNC) {
				[self clearAllView];
				[self addSubview:self.webView];
				bakFunc = currFunc;
				currFunc = MAC_WEB_FUNC;
			}
			
			[showDelegate dealTitleName:@""];;
			[self.webView showWeb:[NSString stringWithFormat:@"%@",_gpcode]];
			break;
		case MAC_CANCEL_WEB_FUNC:
			[self clearAllView];
			[self addSubview:currView];
			currFunc= bakFunc;
			break;
		case MAC_XGZX_FUNC:
			if (currFunc != MAC_XGZX_FUNC) {
				[self clearAllView];
				[self addSubview:self.webView];
				bakFunc = currFunc;
				currFunc = MAC_XGZX_FUNC;
			}
			NSString * tempString = [NSString stringWithFormat:@"http://www.newone.com.cn/newone/articlereport/xgzx.jsp?zqdm=%@",_gpcode];
			[self.webView showWeb:tempString];
			break;

		default:
			break;
	}
	
	if (eGetData.clientinfos.hqParams.bautorefreshhq) {
		[self performSelector:@selector(getTheRefreshData) withObject:nil afterDelay:eGetData.refreshTime];
	}
}



-(void)getTradeProcess:(NSString *)_gpcode gpSetcode:(int)_setcode typeID:(int)_typeID pareOne:(int)_paraone paraTwo:(int)_paraTwo pareThree:(NSString *)_paraThree{
	if (keyShowFlag) {
		[self dismissKeyboard];
	}
	
	if(_typeID == MAC_SHOWHIDETRADE_FUNC){
		if (eGetData.tradeLoginFlag) {
			if (tradeShowFlag) {
				tradeShowFlag = NO;
			}else {
				tradeShowFlag = YES;
			}
			[self dealTradeViewShow];
			
		}
		else {
			[showDelegate showLogin];
		}
		return;
	}
	
	if (eGetData.tradeLoginFlag) {
		if (_typeID == MAC_FASTWT_FUNC) {  //闪电下单
			fastWTShowFlag = YES;
			if ([_gpcode isEqualToString:@""]) {
				self.gpcode = [NSString stringWithFormat:@"%@",currView.gpcode];
				self.setcode = currView.setcode;
				
				if ([eGetData testZS:self.gpcode setcode:self.setcode]) {
					NSAlert* alert = [NSAlert alertWithMessageText: @"提示"
													 defaultButton: @"确定"
												   alternateButton: nil
													   otherButton: nil
										 informativeTextWithFormat: @"该品种不能进行此操作"];
					[alert runModal];
				}
				else {
					[showDelegate showFastWT:[NSString stringWithFormat:@"%@",gpcode] bsFlag:_paraone gpPrice:_paraThree];
					
				}

			}
			else {
				if ([eGetData testZS:_gpcode setcode:_setcode]) {
					NSAlert* alert = [NSAlert alertWithMessageText: @"提示"
													 defaultButton: @"确定"
												   alternateButton: nil
													   otherButton: nil
										 informativeTextWithFormat: @"该品种不能进行此操作"];
					[alert runModal];
				}
				else {
					[showDelegate showFastWT:_gpcode bsFlag:_paraone%2 gpPrice:_paraThree];
				}

				
			}

			
		}
		else if(_typeID == MAC_NORMALWT_FUNC){//普通下单
			
			[tradeView.funcList dealSelect:MAC_WT_FUNC ParaOne:_paraone];
			[tradeView dealTitleAndButton:MAC_WT_FUNC ParaOne:_paraone];
			
			if ([_gpcode isEqualToString:@""]) {
				self.gpcode = [NSString stringWithFormat:@"%@",currView.gpcode];
				self.setcode = currView.setcode;
				if ([eGetData testZS:self.gpcode setcode:self.setcode]) {
					NSAlert* alert = [NSAlert alertWithMessageText: @"提示"
													 defaultButton: @"确定"
												   alternateButton: nil
													   otherButton: nil
										 informativeTextWithFormat: @"该品种不能进行此操作"];
					[alert runModal];
				}
				else {
					[tradeView.bodyView dealTradeProcess:[NSString stringWithString:self.gpcode] gpSetcode:self.setcode typeID:MAC_WT_FUNC pareOne:_paraone%2 paraTwo:_paraTwo pareThree:[NSString stringWithString:_paraThree]];
				}
			}
			
		}

		else {//传给交易主体处理
			//处理标题
			if (_typeID == MAC_WT_FUNC && _paraone == -1) {
				if (tradeView.bodyView.wtView.tag == -1) {
					[tradeView.funcList dealSelect:_typeID ParaOne:1];
					[tradeView dealTitleAndButton:_typeID ParaOne:1];
				}
				else {
                    [tradeView.funcList dealSelect:_typeID ParaOne:tradeView.bodyView.wtView.tag];
                    [tradeView dealTitleAndButton:_typeID ParaOne:tradeView.bodyView.wtView.tag];
				}

			}
			else {
				[tradeView.funcList dealSelect:_typeID ParaOne:_paraone];
				[tradeView dealTitleAndButton:_typeID ParaOne:_paraone];
			}

			
			//处理列表
			[tradeView.bodyView dealTradeProcess:[NSString stringWithString:_gpcode] gpSetcode:_setcode typeID:_typeID pareOne:_paraone paraTwo:_paraTwo pareThree:[NSString stringWithString:_paraThree]];
            
            //担保品划转密码输入界面
            if(_paraone == DBPHZ)
            {
                if([tradeView DBPHZshowlockscreen]) return;
            }
            else
            {
                if(eGetData.clientinfos.m_DBPHZblocking==YES)
                {
                    [tradeView DBPHZunlockscreen];
                }
            }

		}
		
	}
	else {
		NSAlert* alert = [NSAlert alertWithMessageText: @"提示"
										 defaultButton: @"确定"
									   alternateButton: nil
										   otherButton: nil
							 informativeTextWithFormat: @"交易系统尚未登录!不能使用此功能"];
		[alert runModal];
	}
}


-(StockInfo *)getNextStockInfo:(NSString *)_gpcode gpSetcode:(int)_setcode{
	if ([euGrid isInGridArray:_gpcode gpSetcode:_setcode]) {
		SinHqInfo * tempInfo = [euGrid nextInGridArray:_gpcode gpSetcode:_setcode];
		
		StockInfo * tempStock = [[StockInfo alloc] init];
		tempStock.gpcode = [NSString stringWithFormat:@"%@",tempInfo.gpcode];
		tempStock.setcode = tempInfo.setcode;
		
		return [tempStock autorelease];
	}
	else {
		return [eGetData searchNextStockInfo:_gpcode gpSetcode:_setcode];
	}

	
}
-(StockInfo *)getPreStockInfo:(NSString *)_gpcode gpSetcode:(int)_setcode{
	if ([euGrid isInGridArray:_gpcode gpSetcode:_setcode]) {
		SinHqInfo * tempInfo = [euGrid preInGridArray:_gpcode gpSetcode:_setcode];
		
		StockInfo * tempStock = [[StockInfo alloc] init];
		tempStock.gpcode = [NSString stringWithFormat:@"%@",tempInfo.gpcode];
		tempStock.setcode = tempInfo.setcode;
		
		return [tempStock autorelease];
	}
	else {
		return [eGetData searchPreStockInfo:_gpcode gpSetcode:_setcode];
	}
	
}

-(void)closeKeyBoard{
	[self dismissKeyboard];
}


-(void)startReconnect{
	reloadFlag = YES;
	[self getTheRefreshData];

}
#pragma mark  数据相关
-(void)OnReceiveData:(int)reqIndex FuncID:(int)_funcID HqResult:(HqResultData *)_hqResult{
	if (_hqResult.resultStat < 1) {
		if (eGetData.initStockChainFlag) {
			eGetData.initStockChainFlag = NO;
		}
		
		if (eGetData.g_pEComm.initFlag) {
			eGetData.g_pEComm.initFlag = NO;
			[euBottom setTips:@"重连失败！"];
			[self getTheRefreshData];
		}
		else {
			[NSObject cancelPreviousPerformRequestsWithTarget:self selector:@selector(getTheRefreshData) object:nil];
			[self performSelector:@selector(getTheRefreshData) withObject:nil afterDelay:eGetData.refreshTime];
		}

		
		
	}
	
	switch (reqIndex) {
		case HOSTINFO_ORI:
			[eGetData getHostBaseDataAnsEx:_hqResult];
			
			if (eGetData.g_pEComm.initFlag) {
				if( ([eGetData.szStockArray count] == eGetData.szStockNum) && ([eGetData.shStockArray count] == eGetData.shStockNum) ){
					//码表没有变化
					eGetData.initStockChainFlag = NO;
					eGetData.g_pEComm.initFlag = NO;
					[self getTheRefreshData];
				}
				else {
					//码表需要更新
					eGetData.initStockChainFlag = YES;
					eGetData.szStockRec =0;
					eGetData.shStockRec =0;
					[NSObject cancelPreviousPerformRequestsWithTarget:self selector:@selector(getTheRefreshData) object:nil];
					[euBottom setTips:@"正在更新股票信息......"];
					[eGetData.szStockArray removeAllObjects];
					[eGetData.shStockArray removeAllObjects];
					NSMutableData * theData = [eGetData getAllStockChainReq:SZ offset:eGetData.szStockRec wantnum:CHAINWANTNUM];	
					[eGetData.g_pEComm AsyncSendData:theData length:[theData length] withobjIndex:self.windindex withreqIndex:1];
					
				}

			}else {
				if( ([eGetData.szStockArray count] == eGetData.szStockNum) && ([eGetData.shStockArray count] == eGetData.shStockNum) ){
					//码表没有变化
					eGetData.initStockChainFlag = NO;
					[self getTheRefreshData];
				}
				else {
					//码表需要更新
					eGetData.initStockChainFlag = YES;
					eGetData.szStockRec =0;
					eGetData.shStockRec =0;
					[NSObject cancelPreviousPerformRequestsWithTarget:self selector:@selector(getTheRefreshData) object:nil];
					[euBottom setTips:@"正在更新股票信息......"];
					[eGetData.szStockArray removeAllObjects];
					[eGetData.shStockArray removeAllObjects];
					NSMutableData * theData = [eGetData getAllStockChainReq:SZ offset:eGetData.szStockRec wantnum:CHAINWANTNUM];	
					[eGetData.g_pEComm AsyncSendData:theData length:[theData length] withobjIndex:self.windindex withreqIndex:1];
					
				}
			}

			
			break;
			
		case STOCKCHAIN_ORI:
			//取码表信息
			if (eGetData.szStockRec < eGetData.szStockNum) {
				eGetData.szStockRec += [eGetData getAllStockChainAsn:_hqResult];
				if (eGetData.szStockRec < eGetData.szStockNum) {
					NSMutableData * theData = [eGetData getAllStockChainReq:SZ offset:eGetData.szStockRec wantnum:CHAINWANTNUM];	
					[eGetData.g_pEComm AsyncSendData:theData length:[theData length] withobjIndex:self.windindex withreqIndex:1];
					
				}
				else {
					NSMutableData * theData = [eGetData getAllStockChainReq:SH offset:eGetData.shStockRec wantnum:CHAINWANTNUM];	
					[eGetData.g_pEComm AsyncSendData:theData length:[theData length] withobjIndex:self.windindex withreqIndex:1];
					
					
				}
				
			}
			else if(eGetData.shStockRec < eGetData.shStockNum) {
				eGetData.shStockRec += [eGetData getAllStockChainAsn:_hqResult];
				if (eGetData.shStockRec < eGetData.shStockNum) {
					NSMutableData * theData = [eGetData getAllStockChainReq:SH offset:eGetData.shStockRec wantnum:CHAINWANTNUM];	
					[eGetData.g_pEComm AsyncSendData:theData length:[theData length] withobjIndex:self.windindex withreqIndex:1];
					
				}
				else {
					
					eGetData.gpdmlInfo.szGPArray = [[NSMutableArray alloc] initWithArray:eGetData.szStockArray];
					eGetData.gpdmlInfo.shGPArray = [[NSMutableArray alloc] initWithArray:eGetData.shStockArray];
					[eGetData.clientinfos.caches SaveGpdml:eGetData.gpdmlInfo];
					
					
					eGetData.initStockChainFlag = NO;
					eGetData.g_pEComm.initFlag = NO;
					[euBottom setTips:@""];
					[euBottom showTips];
					[self getTheRefreshData];
					
				}
			}
			
			
			break;	
		default:
			break;	
	}	
}

#pragma mark 刷新相关
-(void)getTheRefreshData{
	if ((eGetData.b_yesterday >0)) {
		[NSObject cancelPreviousPerformRequestsWithTarget:self selector:@selector(getTheRefreshData) object:nil];
		[self performSelector:@selector(getTheRefreshData) withObject:nil afterDelay:eGetData.refreshTime];
		return;
	}
	
	if (eGetData.netStat == NotReachable) {
		NSLog(@"NotReachable");
		[euBottom showTips];
		[NSObject cancelPreviousPerformRequestsWithTarget:self selector:@selector(getTheRefreshData) object:nil];
		[self performSelector:@selector(getTheRefreshData) withObject:nil afterDelay:eGetData.refreshTime];
		return;
	}
	
	

	
	if (eGetData.clientinfos.hqParams.bautorefreshhq) {
		if (reloadFlag) {
			[euBottom getDpData];
			
			if (currFunc == MAC_ZFPM_FUNC) {
				[euGrid getTheData:-1 theColtype:-1];
			}
			else if((currFunc == MAC_ZST_FUNC)||(currFunc == MAC_FXT_FUNC)) {
				euZst.reloadFlag = YES;
				[euZst getRefreshData];;
			}
			
			reloadFlag = NO;
			[self performSelector:@selector(getTheRefreshData) withObject:nil afterDelay:eGetData.refreshTime];
			
		}else {
			NSDateFormatter *dateFormatter=[[[NSDateFormatter alloc] init]autorelease]; 
			[dateFormatter setDateFormat:@"YYYY-MM-dd-HH-mm-ss"];
			NSString * localTime = [dateFormatter stringFromDate:[NSDate date]];
			NSArray * tempArray = [localTime componentsSeparatedByString:@"-"];
			if([tempArray count]<6)
            {
                NSMutableData * theData = [eGetData getHostBaseDataReqEx];
                [eGetData.g_pEComm AsyncSendData:theData length:[theData length] withobjIndex:self.windindex withreqIndex:1];
                reloadFlag = YES;
                return;
            }
            int nowDate=0;
            if([tempArray count]>2)
            {
                nowDate = ([[tempArray objectAtIndex:0]intValue] +eGetData.yearDiff)*10000+([[tempArray objectAtIndex:1]intValue]+eGetData.monthDiff)*100+[[tempArray objectAtIndex:2]intValue]+ eGetData.dayDiff;
            }
			if (nowDate != eGetData.sysYMD) {
				NSMutableData * theData = [eGetData getHostBaseDataReqEx];	
				[eGetData.g_pEComm AsyncSendData:theData length:[theData length] withobjIndex:self.windindex withreqIndex:1];
				reloadFlag = YES;
				return;
			}
			
			
			
			
			
			int nowHour,nowMinute,nowSec;
			nowHour = [[tempArray objectAtIndex:3]intValue]+eGetData.hourDiff;
			nowMinute = [[tempArray objectAtIndex:4]intValue]+eGetData.minuteDiff;
			nowSec = [[tempArray objectAtIndex:5]intValue]+eGetData.secondDiff;
			if (nowSec > 59) {
				nowMinute = nowMinute + 1;
			}
			if (nowMinute > 59) {
				nowMinute = nowMinute -60;
				nowHour = nowHour+1;
			}
			
			int checkInt = nowHour * 60+nowMinute;
			
			if (!eGetData.g_pEComm.connFlag) {
				
                if ((checkInt > 510) && (checkInt <570)){
					;
				}
				else {
					if (eGetData.g_pEComm.ntimeoutnum <2) {
					}
					else {
						[euBottom showTips];
						[NSObject cancelPreviousPerformRequestsWithTarget:self selector:@selector(getTheRefreshData) object:nil];
						[self performSelector:@selector(getTheRefreshData) withObject:nil afterDelay:eGetData.refreshTime];
						return;
					}
				}
			}
			
			
			if ((checkInt > 905) ||(checkInt <510)){
						
			}
			else {
				[euBottom getDpData];
				
				if (currFunc == MAC_ZFPM_FUNC) {
					[euGrid refreshTheData];
				}
				else if((currFunc == MAC_ZST_FUNC)||(currFunc == MAC_FXT_FUNC)) {
					[euZst getRefreshData];;
				}
				
				
			}
			[self performSelector:@selector(getTheRefreshData) withObject:nil afterDelay:eGetData.refreshTime];
			
			
			
		}
		
	}
	else {
		[NSObject cancelPreviousPerformRequestsWithTarget:self selector:@selector(getTheRefreshData) object:nil];
		[self performSelector:@selector(getTheRefreshData) withObject:nil afterDelay:eGetData.refreshTime];
	}
}


- (void)drawRect:(NSRect)dirtyRect {
    
	
}

//窗口大小改变
-(void) OnScreenSizeChange:(float)_width theHeight:(float)_height{
	[super OnScreenSizeChange:_width theHeight:_height];
	NSLog(@"OnScreenSizeChange  and height is %f",_height);
	viewRect = NSMakeRect(0, 0, _width, _height);
	[self dealResizeViewShow];
}
#pragma mark 交易界面处理相关
-(void)dealTradeViewShow{
	NSRect tempframe;
	if(tradeView==nil && eGetData.tradeLoginFlag)
    {
        tradeView = [[ETradeMainView alloc] initWithData:NSMakeRect(0, euBottom.frame.size.height, viewRect.size.width, TRADEVIEW_HEIGHT) theData:eGetData];
        tradeView.tradeindex=[eGetData.g_TradeComm.areceiver SetWinobjs:(id)tradeView];
        tradeView.tradeDelegate = self;
        tradeView.reconObject.systemDelegate = self;
        tradeView.m_lockscreen.tradeDelegate = self;
        tradeView.m_DBPHZlockscreen.tradeDelegate = self;
        tradeView.operProcessDelegate = self;
        tradeView.funcList.operProcessDelegate=self;
        tradeView.bodyView.operProcessDelegate=self;
        tradeView.bodyView.wtView.operProcessDelegate = self;
        tradeView.bodyView.wtCancel.operProcessDelegate =self;
        tradeView.bodyView.userInfo.operProcessDelegate = self;
    }
	if (eGetData.tradeLoginFlag && tradeShowFlag) {
		[self addSubview:tradeView];
		
		tempframe.origin.x = 0;
		tempframe.origin.y=BOTTOM_DP_HEIHGT+TRADEVIEW_HEIGHT;
		tempframe.size.width = viewRect.size.width;
		tempframe.size.height = viewRect.size.height-BOTTOM_DP_HEIHGT-TRADEVIEW_HEIGHT;
		
		[euGrid setFrame:tempframe];
		[euZst setFrame:tempframe];
		[euF10 setFrame:tempframe];
		[self.webView setFrame:tempframe];
	
		[euKey setFrame:NSMakeRect(viewRect.size.width - EUKEY_WIDTH-210, BOTTOM_DP_HEIHGT+TRADEVIEW_HEIGHT, EUKEY_WIDTH, EUKEY_HEIGHT)];
	
		[tradeView setFrame:NSMakeRect(0, euBottom.frame.size.height, viewRect.size.width, TRADEVIEW_HEIGHT)];
		
		[euBottom setFrame:NSMakeRect(0, 0, viewRect.size.width, BOTTOM_DP_HEIHGT)];
	}
	else {
		[tradeView removeFromSuperview];
		
		tempframe.origin.x = 0;
		tempframe.origin.y=BOTTOM_DP_HEIHGT;
		tempframe.size.width = viewRect.size.width;
		tempframe.size.height = viewRect.size.height-BOTTOM_DP_HEIHGT;
		
		[euGrid setFrame:tempframe];
		[euZst setFrame:tempframe];
		[euF10 setFrame:tempframe];
		[self.webView setFrame:tempframe];
		[euKey setFrame:NSMakeRect(viewRect.size.width - EUKEY_WIDTH-210, BOTTOM_DP_HEIHGT, EUKEY_WIDTH, EUKEY_HEIGHT)];
		[tradeView setFrame:NSMakeRect(0, euBottom.frame.size.height, viewRect.size.width, TRADEVIEW_HEIGHT)];
		[euBottom setFrame:NSMakeRect(0, 0, viewRect.size.width, BOTTOM_DP_HEIHGT)];
	}
	
	
	if ((currFunc == MAC_ZST_FUNC)||(currFunc == MAC_FXT_FUNC) ){
		[euZst getHqData:euZst.gpcode setcode:euZst.setcode reloadFlag:NO];
	}
}

-(void)dealResizeViewShow{
	NSRect tempframe;
	
	if (eGetData.tradeLoginFlag && tradeShowFlag) {
		[self addSubview:tradeView];
		
		tempframe.origin.x = 0;
		tempframe.origin.y=BOTTOM_DP_HEIHGT+TRADEVIEW_HEIGHT;
		tempframe.size.width = viewRect.size.width;
		tempframe.size.height = viewRect.size.height-BOTTOM_DP_HEIHGT-TRADEVIEW_HEIGHT;
		
		[euGrid setFrame:tempframe];
		[euZst setFrame:tempframe];
		[euF10 setFrame:tempframe];
		[self.webView setFrame:tempframe];
		
		[euKey setFrame:NSMakeRect(viewRect.size.width - EUKEY_WIDTH-210, BOTTOM_DP_HEIHGT+TRADEVIEW_HEIGHT, EUKEY_WIDTH, EUKEY_HEIGHT)];
		
		[tradeView setFrame:NSMakeRect(0, euBottom.frame.size.height, viewRect.size.width, TRADEVIEW_HEIGHT)];
		
		[euBottom setFrame:NSMakeRect(0, 0, viewRect.size.width, BOTTOM_DP_HEIHGT)];
	}
	else {
		[tradeView removeFromSuperview];
		
		tempframe.origin.x = 0;
		tempframe.origin.y=BOTTOM_DP_HEIHGT;
		tempframe.size.width = viewRect.size.width;
		tempframe.size.height = viewRect.size.height-BOTTOM_DP_HEIHGT;
		
		[euGrid setFrame:tempframe];
		[euZst setFrame:tempframe];
		[euF10 setFrame:tempframe];
		[self.webView setFrame:tempframe];
		[euKey setFrame:NSMakeRect(viewRect.size.width - EUKEY_WIDTH-210, BOTTOM_DP_HEIHGT, EUKEY_WIDTH, EUKEY_HEIGHT)];
		[tradeView setFrame:NSMakeRect(0, euBottom.frame.size.height, viewRect.size.width, TRADEVIEW_HEIGHT)];
		[euBottom setFrame:NSMakeRect(0, 0, viewRect.size.width, BOTTOM_DP_HEIHGT)];
	}
}

-(void)ChangeTradeViewSizeShow:(int)flag
{
    NSRect tempframe;
    
    if (eGetData.tradeLoginFlag && flag == 0) { //放大
        [self addSubview:tradeView];
        
        tempframe.origin.x = 0;
        tempframe.origin.y= viewRect.size.height;
        tempframe.size.width = viewRect.size.width;
        tempframe.size.height = BOTTOM_DP_HEIHGT;
        
        [euGrid setFrame:tempframe];
        [euZst setFrame:tempframe];
        [euF10 setFrame:tempframe];
        [webView setFrame:tempframe];
        
        [euKey setFrame:NSMakeRect(viewRect.size.width - EUKEY_WIDTH-210, BOTTOM_DP_HEIHGT+TRADEVIEW_HEIGHT, EUKEY_WIDTH, EUKEY_HEIGHT)];
        
        [tradeView setFrame:NSMakeRect(0, euBottom.frame.size.height, viewRect.size.width, viewRect.size.height-BOTTOM_DP_HEIHGT)];
        
        [euBottom setFrame:NSMakeRect(0, 0, viewRect.size.width, BOTTOM_DP_HEIHGT)];
    }
    else if(eGetData.tradeLoginFlag && flag == 1) //缩小,正常大小
    {
        [self addSubview:tradeView];
        
        tempframe.origin.x = 0;
        tempframe.origin.y=BOTTOM_DP_HEIHGT+TRADEVIEW_HEIGHT;
        tempframe.size.width = viewRect.size.width;
        tempframe.size.height = viewRect.size.height-BOTTOM_DP_HEIHGT-TRADEVIEW_HEIGHT;
        
        [euGrid setFrame:tempframe];
        [euZst setFrame:tempframe];
        [euF10 setFrame:tempframe];
        [webView setFrame:tempframe];
        
        [euKey setFrame:NSMakeRect(viewRect.size.width - EUKEY_WIDTH-210, BOTTOM_DP_HEIHGT+TRADEVIEW_HEIGHT, EUKEY_WIDTH, EUKEY_HEIGHT)];
        
        [tradeView setFrame:NSMakeRect(0, euBottom.frame.size.height, viewRect.size.width, TRADEVIEW_HEIGHT)];
        
        [euBottom setFrame:NSMakeRect(0, 0, viewRect.size.width, BOTTOM_DP_HEIHGT)];
    }
}

-(void)minButtonClick{
	tradeShowFlag = NO;
	[[self window] makeFirstResponder:currView];
	[self dealTradeViewShow];
}

-(void)changeSizeButtonClick:(int)flag
{
    tradeShowFlag = YES;
    [[self window] makeFirstResponder:currView];
    [self ChangeTradeViewSizeShow:flag];
}

-(void)closeButtonClick{
	[tradeView.bodyView cleandata];
	
	if(eGetData.clientinfos.m_blocking)
	{
		[self unlockButtonClick];
	}
    eGetData.bexitsysflag=YES;
	[eGetData logoutTrade];
	[self dealTradeViewShow];
	[showDelegate dealTradeMenu];
    [tradeView release];
    tradeView=nil;
}
-(void)closeButtonClick2{
	[tradeView.bodyView cleandata];
	
	if(eGetData.clientinfos.m_blocking)
	{
		[self unlockButtonClick];
	}
 	[eGetData logoutTrade];
	[self dealTradeViewShow];
	[showDelegate dealTradeMenu];
    
    [tradeView release];
    tradeView=nil;
}
-(void)lockButtonClick{
	if (eGetData.tradeLoginFlag) {
		eGetData.clientinfos.m_blocking=YES;
		
		[tradeView showlockscreen];
	}
}

-(void)unlockButtonClick{
	[tradeView unlockscreen];
}

-(void)tradeDBPHZunlockscreen
{
    [tradeView DBPHZunlockscreen];
}

-(void)tradeDBPHZinputGDDM
{
    [tradeView.bodyView getDBPHZ_GDDM];
}

#pragma mark 按键精灵相关
-(void)appendKey:(NSString *)_keyString{
	NSString * tempString;
	tempString = [[euKey.myTextField cell] title];
	if ([tempString length]<1) {
		[self showKeyBoard];
	}
	else if([tempString length]>5){
		return;
	}
	tempString = [tempString stringByAppendingString:_keyString];
	[[euKey.myTextField cell] setTitle:tempString];
	
	[self checkTheSearch];
}
-(void)delKey{
	
	NSString * tempString;
	tempString = [[euKey.myTextField cell] title];

	if ([tempString length]<2) {
		[self dismissKeyboard];
	}
	
	tempString = [tempString substringToIndex:[tempString length]-1];
	[[euKey.myTextField cell] setTitle:tempString];
	
	[self checkTheSearch];
}
-(void)showKeyBoard{
    [self addSubview:euKey positioned:NSWindowAbove relativeTo:currView];
	keyShowFlag = YES;
	[[self window] makeFirstResponder:euKey];
}
-(void)dismissKeyboard{
	[euKey removeFromSuperview];
	[[euKey.myTextField cell] setTitle:@""];
	[euKey.m_keyData removeAllObjects];
	[searchString release],searchString=nil;
	euKey.selectIndex = -1;
	keyShowFlag = NO;
	
	[self setNeedsDisplay:YES];
	[[self window] makeFirstResponder:currView];

}

-(void)checkTheSearch{
	
	NSString * tempString = [[euKey.myTextField cell] title];
	if ([tempString length] ==  0){
	}
	else if ([tempString compare:searchString]==NSOrderedSame){
	}
	else if (([tempString length] > 0)&&([tempString compare:searchString]!=NSOrderedSame)){
		if (searchString != nil) {
			[searchString release],searchString = nil;
		}
		
		searchString = [[NSString alloc]  initWithFormat:@"%@",tempString];
		[euKey searchTheStock];
		
	}
	
}


#pragma mark  自选股Delegate
- (BOOL)addStock:(NSString *)_gpcode setcode:(int)_setcode{
	if ([stockArray addStockCode:_gpcode MarketID:_setcode]) {
		[stockArray saveData];
		[stockArray readData];
		return TRUE;
	}
	else {
		return FALSE;
	}
}
- (BOOL)stockIsIn:(NSString *)_gpcode setcode:(int)_setcode{
	return [stockArray stockInArray:_setcode StockCode:_gpcode];
}
- (BOOL)deleteStock:(NSString *)_gpcode setcode:(int)_setcode{
	
	NSString * tempString = [NSString stringWithFormat:@"%i%@",_setcode,_gpcode];
	if ([stockArray deleteObject:tempString]) {
		[stockArray saveData];
		return TRUE;
		
		
	}
	else {
		return FALSE;
	}
}

-(NSString *)getCurrStock{
	[stockArray readData];
	
	return [[stockArray getStockCodeString] objectForKey:@"0"];
}

-(NSString *)getCurrStock2:(int)nstartxh num:(int)npagenum
{
    return [[stockArray getStockCodeString2:nstartxh num:npagenum] objectForKey:@"0"];
}

-(NSString *)getStockCode:(int)nstartxh num:(int)npagenum index:(int)nindex
{
    return [stockArray getStockCode:nstartxh num:npagenum index:nindex];
}

-(void)refreshZxgData
{
    [NSObject cancelPreviousPerformRequestsWithTarget:self selector:@selector(getTheRefreshData) object:nil];
	[euGrid refreshTheData];
    [self performSelector:@selector(getTheRefreshData) withObject:nil afterDelay:eGetData.refreshTime];
}

-(int)GetZxgNum2
{
    [stockArray readData];
    return stockArray.nCount;
}

-(int)GetZxgNum
{
    return stockArray.nCount;
}


#pragma mark 事件相关
-(void)getKeyBoardEvent:(NSEvent *)theEvent{
	if (eGetData.initStockChainFlag) {
		return;
	}
	
	NSString * characters;
	characters  =[theEvent characters];
	
	unichar character;
	character = [characters characterAtIndex:0];
    
    unsigned short nkeycode=[theEvent keyCode];
    
	switch ([theEvent keyCode]) {
		case MAC_KEY_F5:
			[self getHQProcess:@"" gpSetcode:-1 typeID:MAC_SWITCH_FUNC pareOne:-1 paraTwo:-1];
			return;
			break;
	
		case MAC_KEY_F6:
			[self getHQProcess:@"" gpSetcode:1 typeID:MAC_ZFPM_FUNC pareOne:100 paraTwo:0];
			return;
			break;
		case MAC_KEY_F7:
			[controllerDelegate dealFullScreen];
			return;
			break;
	
		case MAC_KEY_ESC:
			if ([controllerDelegate getFullScreenFlag]) {
				[controllerDelegate dealFullScreen];
				return;
			}
			
			if (fastWTShowFlag) {
				[showDelegate closeFastWT];
				return;
			}
			
			if (keyShowFlag) {
				[self dismissKeyboard];
				return;
			}
			break;
	
		case MAC_KEY_DEL:
			if (keyShowFlag) {
				[self delKey];
				return;
			}
			break;

		case MAC_KEY_CHAR_Z:
			if(! ([theEvent modifierFlags]& NSControlKeyMask)){
				[self appendKey:[NSString stringWithFormat:@"%c",character-32]];
				return;
			}
			break;
		case MAC_KEY_1:
		case MAC_KEY_2:
		case MAC_KEY_3:	
		case MAC_KEY_4:
		case MAC_KEY_5:
		case MAC_KEY_6:	
		case MAC_KEY_7:
		case MAC_KEY_8:
		case MAC_KEY_9:	
		case MAC_KEY_0:
        case MAC_SKEY_1:
        case MAC_SKEY_2:
        case MAC_SKEY_3:
        case MAC_SKEY_4:
        case MAC_SKEY_5:
        case MAC_SKEY_6:
        case MAC_SKEY_7:
        case MAC_SKEY_8:
        case MAC_SKEY_9:
        case MAC_SKEY_0:
            if(character==42)
                return;
			[self appendKey:[NSString stringWithFormat:@"%c",character]];
			return;
			break;
			
		case MAC_KEY_CHAR_A:
		case MAC_KEY_CHAR_B:
		case MAC_KEY_CHAR_C:
		case MAC_KEY_CHAR_D:
		case MAC_KEY_CHAR_E:
		case MAC_KEY_CHAR_F:
		case MAC_KEY_CHAR_G:
		case MAC_KEY_CHAR_H:
		case MAC_KEY_CHAR_I:
		case MAC_KEY_CHAR_J:
		case MAC_KEY_CHAR_K:
		case MAC_KEY_CHAR_L:
		case MAC_KEY_CHAR_M:
		case MAC_KEY_CHAR_N:
		case MAC_KEY_CHAR_O:
		case MAC_KEY_CHAR_P:
		case MAC_KEY_CHAR_Q:
		case MAC_KEY_CHAR_R:
		case MAC_KEY_CHAR_S:
		case MAC_KEY_CHAR_T:
		case MAC_KEY_CHAR_U:
		case MAC_KEY_CHAR_V:
		case MAC_KEY_CHAR_W:
		case MAC_KEY_CHAR_X:	
		case MAC_KEY_CHAR_Y:		
			[self appendKey:[NSString stringWithFormat:@"%c",character-32]];
			return;
			break;
		case MAC_KEY_F10:
			[self getHQProcess:@"" gpSetcode:-1 typeID:MAC_F10_FUNC pareOne:-1 paraTwo:-1];
			break;
		case MAC_KEY_F2:
			if (eGetData.tradeLoginFlag) {
				if (tradeShowFlag) {
					tradeShowFlag = NO;
				}else {
					tradeShowFlag = YES;
				}
				[self dealTradeViewShow];

			}
			else {
				[showDelegate showLogin];
			}

			
			break;
	
		case MAC_KEY_F3:
			[self getHQProcess:@"999999" gpSetcode:1 typeID:MAC_ZST_FUNC pareOne:1 paraTwo:-1];
			break;
		case MAC_KEY_F4:
			[self getHQProcess:@"399001" gpSetcode:0 typeID:MAC_ZST_FUNC pareOne:1 paraTwo:-1];
			break;

		default:
			break;
	}
	
	
	if (keyShowFlag) {
		[euKey dealKeyBoardEvent:theEvent];
	}
	else {
		[currView dealKeyBoardEvent:theEvent];
	}

	
}


-(void) dealloc{
	[super dealloc];
	[euGrid release];
	[euZst release];
	[euFxt release];
	[euBottom release];
	[euF10 release];
	[stockArray release];
}

@end
