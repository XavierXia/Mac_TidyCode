//
//  EUZst.m
//  tdxMac
//
//  Created by tdx on 11-9-5.
//  Copyright 2011 武汉. All rights reserved.
//

#define HQ_SEC_WIDTH 210
#define HQ_SEC_HEIGHT 397//440  392

#define ZST_FUNC_FLAG  1
#define FXT_FUNC_FlAG  2
#import "EUZst.h"


@implementation EUZst
@synthesize showFlag,financeShowFlag,tickShowFlag,reloadFlag;
@synthesize gpname,zxgDelegate,fxt,hq,zst;

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
		
		showFlag = 1;
		tickShowFlag = NO;// 
		reloadFlag = NO;
		financeShowFlag = NO;
		
        // Initialization code here.
		NSRect zstFrame = frame;
		zstFrame.origin.y = 0;
		zstFrame.size.width = frame.size.width - HQ_SEC_WIDTH;
		zst = [[DataZstComponent alloc] initWithFrame:zstFrame theData:_eGetData titleHeight:40.0f titleFont:15.0f btnFont:15.0f];
		zst.hyTitleArray = [NSMutableArray arrayWithObjects:@"金融行业",@"其它类一",@"钢铁行业",@"家具行业",@"石油行业",@"公路桥梁",
							@"汽车类",@"交通运输",@"医疗器械",@"酒店旅游",@"房地产",@"商业百货",
							@"物资外贸",@"食品行业",@"纺织行业",@"电力行业",@"农林牧渔",@"传媒娱乐",
							@"化工行业",@"煤炭行业",@"建筑建材",@"水泥行业",@"家电行业",@"电子信息",
							@"综合行业",@"机械行业",@"化纤行业",@"农药化肥",@"电器行业",@"摩托车",
							@"开发区", @"自行车",@"船舶制造",@"生物制药",@"电子器件",@"有色金属",
							@"酿酒行业",@"造纸行业",@"环保行业",@"陶瓷行业",@"服装鞋类",@"供水供气",
							@"发电设备",@"其它类二",@"纺织机械",@"印刷包装",@"塑料制品",@"玻璃行业",
							@"飞机制造",@"其它制造",@"仪器仪表",@"非金属品",nil];
		zst.mineDelegate = self;
		[self addSubview:zst];
		
		fxt = [[DataFxtComponent alloc] initWithFrame:zstFrame theData:_eGetData titleHeight:20.0f dateHeight:17.0f btnHeight:30.0f titleFont:15.0f btnFont:15.0f];
		fxt.myDelegate = self;
		
		hq = [[DataHqComponent alloc] initWithData:NSMakeRect(zstFrame.size.width,frame.size.height - HQ_SEC_HEIGHT, HQ_SEC_WIDTH, HQ_SEC_HEIGHT) theData:eGetData];
		hq.titleArray = [NSMutableArray arrayWithObjects:@"卖五",@"卖四",@"卖三",@"卖二",@"卖一",@"买一",@"买二",@"买三",@"买四",@"买五",nil];
//		hq.zsTitleArray=[NSMutableArray arrayWithObjects:@"A股成交",@"B股成交",@"国债成交",@"基金成交",@"权证成交",@"最新指数",@"今日开盘",@"昨日收盘",@"指数涨跌",@"指数涨幅",@"指数振幅",@"总成交量",@"总成交额",@"最高指数",@"最低指数",@"涨家数",nil];
        
        hq.zsTitleArray=[NSMutableArray arrayWithObjects:@"A股成交",@"B股成交",@"国债成交",@"基金成交",@"最新指数",@"今日开盘",@"昨日收盘",@"指数涨跌",@"指数涨幅",@"指数振幅",@"总成交量",@"总成交额",@"最高指数",@"最低指数",nil];
        
		[self addSubview:hq];
		
		tick = [[DataTickComponent alloc] initWithData:NSMakeRect(zstFrame.size.width, 0, HQ_SEC_WIDTH,frame.size.height - HQ_SEC_HEIGHT) theData:eGetData];
		[self addSubview:tick];
		
		
		
		NSMenu * gridMenu = [[NSMenu allocWithZone:[NSMenu menuZone]] initWithTitle:@""];
		
		NSMenuItem * newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"返回		ESC" action:@selector(rightMenu:) keyEquivalent:@""];
		[newItem setEnabled:YES];
		[newItem setTarget:self];
		[newItem setTag:0];
		[gridMenu addItem:newItem];
		[newItem release];
		
		newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"切换		F5" action:@selector(rightMenu:) keyEquivalent:@""];
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
		
		newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"上一支股票" action:@selector(rightMenu:) keyEquivalent:@""];
		[newItem setEnabled:YES];
		[newItem setTarget:self];
		[newItem setTag:3];
		[gridMenu addItem:newItem];
		[newItem release];
		
		newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"下一支股票" action:@selector(rightMenu:) keyEquivalent:@""];
		[newItem setEnabled:YES];
		[newItem setTarget:self];
		[newItem setTag:4];
		[gridMenu addItem:newItem];
		[newItem release];
		
		[gridMenu addItem:[NSMenuItem separatorItem]];
		
		newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"加入自选	Ctrl+Z" action:@selector(rightMenu:) keyEquivalent:@""];
		[newItem setEnabled:YES];
		[newItem setTarget:self];
		[newItem setTag:5];
		[gridMenu addItem:newItem];
		[newItem release];
		
		[self setMenu:gridMenu];
		[zst setMenu:gridMenu];
		[zst.zstCross setMenu:gridMenu];
		[gridMenu release];
	}
    return self;
	
}

-(void) setFrame:(NSRect)frameRect{
	[super setFrame:frameRect];
	viewRect = frameRect;
	
	zst.offset_X = frameRect.origin.x;
	zst.offset_Y = frameRect.origin.y;
	
	fxt.offset_X = frameRect.origin.x;
	fxt.offset_Y = frameRect.origin.y;
	
	[zst setFrame:NSMakeRect(0, 0, viewRect.size.width - HQ_SEC_WIDTH, MAX(viewRect.size.height,HQ_SEC_HEIGHT))];
	[fxt setFrame:NSMakeRect(0, 0, viewRect.size.width - HQ_SEC_WIDTH, MAX(viewRect.size.height,HQ_SEC_HEIGHT))];
	[hq setFrame:NSMakeRect(viewRect.size.width - HQ_SEC_WIDTH,viewRect.size.height - HQ_SEC_HEIGHT, HQ_SEC_WIDTH, HQ_SEC_HEIGHT)];
	[tick setFrame:NSMakeRect(viewRect.size.width - HQ_SEC_WIDTH, 0, HQ_SEC_WIDTH,viewRect.size.height - HQ_SEC_HEIGHT)];
}

-(void)rightMenu:(id)sender{
	StockInfo * tempInfo;
	
	switch ([sender tag]) {
		case 0:
			if (zst.zstCross.showFlag) {
				zst.zstCross.showFlag = NO;
				[zst.zstCross refreshShow];
				[zst dismissDetailComponent];
			}
			
			[operProcessDelegate getHQProcess:@"" gpSetcode:-1 typeID:MAC_ZFPM_FUNC pareOne:-1 paraTwo:-1];
			
			break;

		case 1:
			if (zst.zstCross.showFlag) {
				zst.zstCross.showFlag = NO;
				[zst.zstCross refreshShow];
				[zst dismissDetailComponent];
			}
			if (self.showFlag == ZST_FUNC_FLAG) {
				[self showSwitchInfo:FXT_FUNC_FlAG];
			}
			else if(self.showFlag == FXT_FUNC_FlAG)
			{
				[self showSwitchInfo:ZST_FUNC_FLAG];
			}
			break;
		case 2://基本资料
			[operProcessDelegate getHQProcess:self.gpcode gpSetcode:self.setcode typeID:MAC_F10_FUNC pareOne:-1 paraTwo:-1];
			break;
		case 3://上一只股票
			tempInfo = [operProcessDelegate getPreStockInfo:self.gpcode gpSetcode:self.setcode];
			[self getHqData:tempInfo.gpcode setcode:tempInfo.setcode reloadFlag:YES];
			break;
		case 4://下一只股票
			tempInfo = [operProcessDelegate getNextStockInfo:self.gpcode gpSetcode:self.setcode];
			[self getHqData:tempInfo.gpcode setcode:tempInfo.setcode reloadFlag:YES];

			break;

		case 5://加入自选
			[self addZixuan];
			break;
			
		default:
			break;
	}
}


- (void)drawRect:(NSRect)dirtyRect {
    // Drawing code here.
    [[NSColor blackColor] set];
    NSRectFill(dirtyRect);
}

-(void)clearScreenInInit{
	zst.dataFlag = NO;
	[zst setNeedsDisplay:YES];
	fxt.dataFlag =NO;
	[fxt setNeedsDisplay:YES];
	hq.showFlag = NO;
	[hq setNeedsDisplay:YES];
	[hq.myTableView reloadData];
	tick.showFlag = NO;
	[tick.myTableView reloadData];
}


-(void)setFxtInfo:(int)_periodIndex ZBIndex:(int)_zbIndex{
	if (_periodIndex > -1) {
		fxt.periodIndex = _periodIndex;
	}
	if (_zbIndex > -1) {
		fxt.zbIndex = _zbIndex;
	}
	
}

-(void)setSwitchInfo:(int)_index{
	if (_index == ZST_FUNC_FLAG) {
		[zst removeFromSuperview];
		[fxt removeFromSuperview];
		[self addSubview:zst];
		self.showFlag = ZST_FUNC_FLAG;
	}
	else if(_index == FXT_FUNC_FlAG){
		[zst removeFromSuperview];
		[fxt removeFromSuperview];
		[self addSubview:fxt];
		self.showFlag = FXT_FUNC_FlAG;
	}
}

-(void)showSwitchInfo:(int)_index{
	if (_index == ZST_FUNC_FLAG) {
		[zst removeFromSuperview];
		[fxt removeFromSuperview];
		[self addSubview:zst];
		self.showFlag = ZST_FUNC_FLAG;
	}
	else if(_index == FXT_FUNC_FlAG){
		[zst removeFromSuperview];
		[fxt removeFromSuperview];
		[self addSubview:fxt];
		self.showFlag = FXT_FUNC_FlAG;
	}
	[self getHqData:[NSString stringWithFormat:@"%@",self.gpcode] setcode:self.setcode reloadFlag:YES];
}


-(void)getRefreshData{
	if (reloadFlag) {
		reloadFlag = NO;
		[self getHqData:[NSString stringWithFormat:@"%@",self.gpcode] setcode:self.setcode reloadFlag:YES];
	}else {

		
		int flags;
		flags = COMBO_MASK_GGHQ | COMBO_MASK_TICK;
		
		NSMutableData * theData = [eGetData getCombDataReq:self.gpcode setcode:self.setcode flags:flags period:fxt.periodIndex mulNum:1 startxh:fxt.m_ReadNum recNum:fxt.m_PerReadNum tickStartx:-1 tickWantnum:tick.showNum];	
		[eGetData.g_pEComm AsyncSendData:theData length:[theData length] withobjIndex:self.windindex withreqIndex:4];
		
	}

	
	
}

-(void)getHqData:(NSString *)_gpcode setcode:(int)_setcode  reloadFlag:(BOOL)_reloadFlag{
	if (zst.zstCross.showFlag) {
		zst.zstCross.showFlag = NO;
		[zst.zstCross refreshShow];
		[zst dismissDetailComponent];
	}
	
	if (fxt.fxtCross.showFlag) {
		fxt.fxtCross.showFlag = NO;
		[fxt.fxtCross refreshShow];
		[fxt hideFxtDetail];
	}
	
	
	if (_reloadFlag) {
		if (showFlag == ZST_FUNC_FLAG) {
			zst.dataFlag = NO;
			[zst setNeedsDisplay:YES];
		}
		else if(showFlag == FXT_FUNC_FlAG){
			fxt.dataFlag=NO;
			fxt.m_ReadNum = 0;
			[fxt setNeedsDisplay:YES];
		}
	}
	else {
		if (showFlag == ZST_FUNC_FLAG) {
		}
		else if(showFlag == FXT_FUNC_FlAG){
			fxt.dataFlag=NO;
			fxt.m_ReadNum = 0;
			[fxt setNeedsDisplay:YES];
		}
	}

	
	if ([self.gpcode isEqualToString:_gpcode]) {
		
	}else {
		hq.showFlag = NO;
		[hq setNeedsDisplay:YES];
		
		tick.showFlag = NO;
		[tick.myTableView reloadData];		
	}

	
	self.gpcode = [NSString stringWithFormat:@"%@",_gpcode];
	self.setcode = _setcode;
	
	int flags;
	
	if(showFlag == ZST_FUNC_FLAG){
		flags = COMBO_MASK_GGHQ | COMBO_MASK_ZST |COMBO_MASK_TICK;
		zst.haveMineFlag = NO;
		[zst.m_MinuteData removeAllObjects];
	}
	else if(showFlag == FXT_FUNC_FlAG) {
		flags = COMBO_MASK_GGHQ | COMBO_MASK_FXT |COMBO_MASK_TICK;
		
		fxt.moreFxtFlag = NO;
	}
	else {
		;
	}
	
	if (financeShowFlag) {
		flags =flags | COMBO_MASK_CW;
	}
	
	NSMutableData * theData = [eGetData getCombDataReqEx:self.gpcode setcode:self.setcode flags:flags period:fxt.periodIndex mulNum:1 startxh:fxt.m_ReadNum recNum:fxt.m_PerReadNum tickStartx:-1 tickWantnum:tick.showNum wParam:fxt.fqFlag lParam:0];
	
	[eGetData.g_pEComm AsyncSendData:theData length:[theData length] withobjIndex:self.windindex withreqIndex:1];
}

-(void)OnReceiveData:(int)reqIndex FuncID:(int)_funcID HqResult:(HqResultData *)_hqResult{
	if (_hqResult.resultStat < 1) {
		return;
	}
	switch (reqIndex) {
		case INFOTITLE_NREQ:{
			NSMutableDictionary * theData = [[[NSMutableDictionary alloc]init] autorelease];
			[eGetData getInfoTitleDataAns:_hqResult Result:theData];
			
			int minesize = [[theData objectForKey:@"TITLENUM"] intValue];
			
			NSLog(@"minesize is %i",minesize);
			
			if (minesize > 0) {
				if (!zst.haveMineFlag) {
					zst.haveMineFlag = YES;
					[zst setNeedsDisplay:YES];
				}
				
			}
			else {
				if (zst.haveMineFlag) {
					zst.haveMineFlag = NO;
					[zst setNeedsDisplay:YES];
				}
				
			}
		}
			break;
	
		case COMB_NREQ:{
			if (_funcID == 1) {
				NSMutableDictionary * theData = [[[NSMutableDictionary alloc]init] autorelease];
				[eGetData getCombDataAns:_hqResult Result:theData];
				
				if (currInfo != nil) {
					[currInfo release],currInfo = nil;
					;
				}
				
				SinHqInfo * tempInfo = [theData objectForKey:@"GGHQ"];
				currInfo = [tempInfo deepCopy];
				self.setcode = currInfo.setcode;
				self.gpname = [NSString stringWithFormat:@"%@",currInfo.gpname];
				[operProcessDelegate getTheTitleName:currInfo.gpname];
				
				if (currInfo.closeP > 0.01) {
					
					if([self.gpcode compare:currInfo.gpcode] == 0){
						int flags = [[theData objectForKey:@"FLAG"] intValue];
						
						[hq showBase:currInfo];
						
						if ((flags & COMBO_MASK_ZST) == COMBO_MASK_ZST)
						{
							[zst showMinute:[theData objectForKey:@"ZST"] currInfo:currInfo];
							
							
						}
						if((flags & COMBO_MASK_FXT) == COMBO_MASK_FXT){
							fxt.theOffset = [[theData objectForKey:@"FXTOFFSET"] intValue];
							[fxt showAnalyse:[theData objectForKey:@"FXT"] currInfo:currInfo];
						}
						if((flags & COMBO_MASK_TICK) == COMBO_MASK_TICK){
							tick.zsFlag = currInfo.zsflag;
							tick.closep = currInfo.closeP;
							tick.dataPre = currInfo.dataPre;
							[tick showTable:[theData objectForKey:@"TICK"]];
						}
						if((flags & COMBO_MASK_CW) == COMBO_MASK_CW){
						}
					}
				}
				else {
				}
				
				
				NSMutableData * mineData = [eGetData getInfoTitleDataReq:INFOTITLE_TYPE_SS startx:0 wantnum:1 gpcode:self.gpcode setcode:self.setcode hyStr:@"" flStr:@""];
				
				[eGetData.g_pEComm AsyncSendData:mineData length:[mineData length] withobjIndex:self.windindex withreqIndex:1];
				
			}
			
			else if(_funcID == 2){
				if(self.showFlag ==1)
					;
				else if(self.showFlag ==2)
				{
					NSMutableDictionary * theData = [[[NSMutableDictionary alloc]init] autorelease];
					[eGetData getCombDataAns:_hqResult Result:theData];
					
					fxt.theOffset = [[theData objectForKey:@"FXTOFFSET"] intValue];
					[fxt showAnalyse:[theData objectForKey:@"FXT"] currInfo:currInfo];
				}
				else;
			}
			else if(_funcID == 3){
				
				NSMutableDictionary * theData = [[[NSMutableDictionary alloc]init] autorelease];
				[eGetData getCombDataAns:_hqResult Result:theData];
				int tempOffset = [[theData objectForKey:@"FXTOFFSET"] intValue];

				NSMutableArray * tempArray = [theData objectForKey:@"FXT"];
				if ((tempOffset == 0) &&([tempArray count] == 0)){
					fxt.moreFxtFlag = NO;
					fxt.isAllData = YES;
					return;
				}
				
				if ((fxt.theOffset - tempOffset) == fxt.m_PerReadNum){
					[fxt updateKLine:[theData objectForKey:@"FXT"]];
					fxt.theOffset = tempOffset;
				}
				else {
					if ((fxt.theOffset - tempOffset) == [tempArray count]){
						fxt.isAllData = YES;
						[fxt updateKLine:tempArray];
						fxt.theOffset = tempOffset;
					}
					else {
						fxt.isAllData = YES;
						fxt.moreFxtFlag = NO;
						[fxt calDataEx];
						[fxt calIt];
						[fxt setNeedsDisplay:YES];
					}
				}

			}
			else if(_funcID == 4){
				NSMutableDictionary * theData = [[[NSMutableDictionary alloc]init] autorelease];
				[eGetData getCombDataAns:_hqResult Result:theData];

				if (currInfo != nil) {
					[currInfo release],currInfo = nil;
					;
				}
				SinHqInfo * tempInfo = [theData objectForKey:@"GGHQ"];
				currInfo = [tempInfo deepCopy];

				if (currInfo.closeP > 0.01) {
					
					if([self.gpcode compare:currInfo.gpcode] == 0){
						int flags = [[theData objectForKey:@"FLAG"] intValue];
						
						if([currInfo.gpcode compare:hq.currInfo.gpcode] == 0){
							[hq showBase:currInfo];
							
							if((flags & COMBO_MASK_TICK) == COMBO_MASK_TICK){
								tick.zsFlag = currInfo.zsflag;
								tick.closep = currInfo.closeP;
								tick.dataPre = currInfo.dataPre;
								[tick showTable:[theData objectForKey:@"TICK"]];
							}
						}
						else {
							reloadFlag = YES;
						}
						
						//处理分时k线的动态维护
						NSDateFormatter *dateFormatter=[[[NSDateFormatter alloc] init]autorelease]; 
						[dateFormatter setDateFormat:@"YYYY-MM-dd-HH-mm-ss"];
						NSString * localTime = [dateFormatter stringFromDate:[NSDate date]];
						NSArray * tempArray = [localTime componentsSeparatedByString:@"-"];
                        if([tempArray count]<6)
                            return;
                        int nowDate=0;
                        if([tempArray count]>2)
                        {
                            nowDate = ([[tempArray objectAtIndex:0]intValue] +eGetData.yearDiff)*10000+([[tempArray objectAtIndex:1]intValue]+eGetData.monthDiff)*100+[[tempArray objectAtIndex:2]intValue]+ eGetData.dayDiff;
                        }
						
						
						
						if (nowDate == eGetData.sysYMD) {
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
							
							if (showFlag == 1) {
								int checkInt = nowHour * 60+nowMinute;
								if ((checkInt > 510) && (checkInt <570)){
									if ([zst.m_MinuteData count] == 240) {
									}
									else {
										if([currInfo.gpcode compare:zst.currInfo.gpcode] == 0){
											if ([zst refreshMinute:currInfo nowHour:nowHour nowMinute:nowMinute]) {
												reloadFlag = NO;
											}
											else {
												reloadFlag = YES;
											}
										}else {
											reloadFlag = YES;
										}
									}
									
								}
								else {
									if([currInfo.gpcode compare:zst.currInfo.gpcode] == 0){
										if ([zst refreshMinute:currInfo nowHour:nowHour nowMinute:nowMinute]) {
											reloadFlag = NO;
										}
										else {
											reloadFlag = YES;
										}
									}else {
										reloadFlag = YES;
									}
								}
							}
							else if(showFlag == 2) {
								if([currInfo.gpcode compare:fxt.currInfo.gpcode] == 0){
									if ([fxt refreshAnalyse:currInfo nowDate:nowDate nowHour:nowHour nowMinute:nowMinute]) {
										reloadFlag = NO;
									}
									else {
										reloadFlag = YES;
									}
								}
								else {
									reloadFlag = YES;
								}
								
								
							}
						}
					}
				}
				else {
				}
			}

		}	
			break;

		default:
			break;
	}
}
#pragma mark MineDelegate
-(void)showMineInfo{

}

#pragma mark  自选股相关
-(void)addZixuan{
	
	if([operZXGDelegate addStock:self.gpcode setcode:self.setcode]){
		
        NSAlert* alert = [NSAlert alertWithMessageText: [NSString stringWithFormat:@"%@(%@)已成功加入自选股",currInfo.gpname,currInfo.gpcode]
										 defaultButton: @"确定"
									   alternateButton: nil
										   otherButton: nil
							 informativeTextWithFormat: @""];
		[alert setDelegate:self];
		NSInteger result = [alert runModal];
		[self handleResult:alert withResult:result];
	}	
	else {
		NSAlert* alert = [NSAlert alertWithMessageText: [NSString stringWithFormat:@"%@(%@)已存在自选股中",currInfo.gpname,currInfo.gpcode]
										 defaultButton: @"确定"
									   alternateButton: nil
										   otherButton: nil
							 informativeTextWithFormat: @""];
		[alert runModal];
	}
	
}

-(void)handleResult:(NSAlert *)alert withResult:(NSInteger)result
{
	switch(result)
	{
		case NSAlertDefaultReturn:
			[hq setNeedsDisplay:YES];
			break;
			
		case NSAlertAlternateReturn:
			break;
			
		case NSAlertOtherReturn:
			break;
            
        default:
            break;
	}

}

#pragma mark K线处理相关
- (void)changeFXTPara{
	if (fxt.fxtCross.showFlag) {
		fxt.fxtCross.showFlag = NO;
		[fxt.fxtCross refreshShow];
		[fxt hideFxtDetail];
	}
	
	int flags = COMBO_MASK_FXT;
	fxt.moreFxtFlag = NO;
	
    NSMutableData * theData = [eGetData getCombDataReqEx:self.gpcode setcode:self.setcode flags:flags period:fxt.periodIndex mulNum:1 startxh:fxt.m_ReadNum recNum:fxt.m_PerReadNum tickStartx:-1 tickWantnum:tick.showNum wParam:fxt.fqFlag lParam:0];
	
	[eGetData.g_pEComm AsyncSendData:theData length:[theData length] withobjIndex:self.windindex withreqIndex:2];

	
}
- (void)getMoreFXTData{
	int flags = COMBO_MASK_FXT;
	
	fxt.moreFxtFlag = YES;
	
	NSMutableData * theData = [eGetData getCombDataReqEx:self.gpcode setcode:self.setcode flags:flags period:fxt.periodIndex mulNum:1 startxh:fxt.m_ReadNum recNum:fxt.m_PerReadNum tickStartx:-1 tickWantnum:tick.showNum wParam:fxt.fqFlag lParam:0];
	[eGetData.g_pEComm AsyncSendData:theData length:[theData length] withobjIndex:self.windindex withreqIndex:3];
	
	
}

#pragma mark 鼠标响应相关

-(void) mouseMoved:(NSEvent *)theEvent{
	if(showFlag == ZST_FUNC_FLAG){
		[zst mouseMoved:theEvent];
	}
	else if(showFlag == FXT_FUNC_FlAG)
	{
		[fxt mouseMoved:theEvent];
	}
}

-(void) rightMouseDown:(NSEvent *)theEvent{

    [NSMenu popUpContextMenu:[self menu] withEvent:theEvent forView:self];
}

-(void) dealKeyBoardEvent:(NSEvent *)theEvent{
	StockInfo * tempInfo;
	switch ([theEvent keyCode]) {
		case MAC_KEY_ARROWDOWN:{
			NSLog(@"方向键下");
			if (self.showFlag == ZST_FUNC_FLAG) {
				[zst dealKeyBoardEvent:theEvent];
			}
			else {
				[fxt dealKeyBoardEvent:theEvent];
			}
		}
			break;
		case MAC_KEY_ARROWUP:{
			NSLog(@"方向键上");
			if (self.showFlag == ZST_FUNC_FLAG) {
				[zst dealKeyBoardEvent:theEvent];
			}
			else {
				[fxt dealKeyBoardEvent:theEvent];
			}
		}
			break;	
		case MAC_KEY_ARROWLEFT:
			if (self.showFlag == ZST_FUNC_FLAG) {
				[zst dealKeyBoardEvent:theEvent];
			}
			else {
				[fxt dealKeyBoardEvent:theEvent];
			}

			break;
		case MAC_KEY_ARROWRIGHT:
			if (self.showFlag == ZST_FUNC_FLAG) {
				[zst dealKeyBoardEvent:theEvent];
			}
			else {
				[fxt dealKeyBoardEvent:theEvent];
			}
			break;

		case MAC_KEY_ESC://ESC
		{
			if (self.showFlag == ZST_FUNC_FLAG) {
				if (zst.zstCross.showFlag) {
					zst.zstCross.showFlag = NO;
					[zst.zstCross refreshShow];
					[zst dismissDetailComponent];
					return;
				}
				
			}
			else {
				if (fxt.fxtCross.showFlag) {
					fxt.fxtCross.showFlag = NO;
					[fxt hideFxtDetail];
					[fxt.fxtCross refreshShow];
					
					return;
				}
				
			}
						
			[operProcessDelegate getHQProcess:@"" gpSetcode:-1 typeID:MAC_ZFPM_FUNC pareOne:-1 paraTwo:-1];
		}
			break;
		case MAC_KEY_CHAR_Z:{
			if ([theEvent modifierFlags]& NSControlKeyMask){
				
                if([operZXGDelegate addStock:self.gpcode setcode:self.setcode]){
					
					NSAlert* alert = [NSAlert alertWithMessageText: [NSString stringWithFormat:@"%@(%@)已成功加入自选股",currInfo.gpname,currInfo.gpcode]
													 defaultButton: @"确定"
												   alternateButton: nil
													   otherButton: nil
										 informativeTextWithFormat: @""];
					[alert runModal];
					[hq setNeedsDisplay:YES];
				}	
				else {
					NSAlert* alert = [NSAlert alertWithMessageText: [NSString stringWithFormat:@"%@(%@)已存在自选股中",currInfo.gpname,currInfo.gpcode]
													 defaultButton: @"确定"
												   alternateButton: nil
													   otherButton: nil
										 informativeTextWithFormat: @""];
					[alert runModal];
				}
			}
		}	
			break;	
		case MAC_KEY_ENTER:
        case MAC_SKEY_ENTER:
		case MAC_KEY_F5:
		{
			if (zst.zstCross.showFlag) {
				zst.zstCross.showFlag = NO;
				[zst.zstCross refreshShow];
				[zst dismissDetailComponent];
			}
			if (fxt.fxtCross.showFlag) {
				fxt.fxtCross.showFlag = NO;
				[fxt.fxtCross refreshShow];
				[fxt hideFxtDetail];
			}
			if (self.showFlag == ZST_FUNC_FLAG) {
				[self showSwitchInfo:FXT_FUNC_FlAG];
			}
			else if(self.showFlag == FXT_FUNC_FlAG)
			{
				[self showSwitchInfo:ZST_FUNC_FLAG];
			}
			
		}	
			break;
		case MAC_KEY_F8:
		case MAC_KEY_CHAR_RIGHT:
			if (self.showFlag == ZST_FUNC_FLAG) {
				tempInfo = [operProcessDelegate getNextStockInfo:self.gpcode gpSetcode:self.setcode];
				[self getHqData:tempInfo.gpcode setcode:tempInfo.setcode reloadFlag:YES];
			}
			else {
				[fxt dealKeyBoardEvent:theEvent];
			}
			break;
		case MAC_KEY_CHAR_LEFT:	
			if (self.showFlag == ZST_FUNC_FLAG) {
				tempInfo = [operProcessDelegate getPreStockInfo:self.gpcode gpSetcode:self.setcode];
				[self getHqData:tempInfo.gpcode setcode:tempInfo.setcode reloadFlag:YES];
			}
			else {
				[fxt dealKeyBoardEvent:theEvent];
			}
			
			break;
		case MAC_KEY_PAGEUP:
			tempInfo = [operProcessDelegate getPreStockInfo:self.gpcode gpSetcode:self.setcode];
			[self getHqData:tempInfo.gpcode setcode:tempInfo.setcode reloadFlag:YES];
			break;
		case MAC_KEY_PAGEDOWN:
			tempInfo = [operProcessDelegate getNextStockInfo:self.gpcode gpSetcode:self.setcode];
			[self getHqData:tempInfo.gpcode setcode:tempInfo.setcode reloadFlag:YES];
			break;
			
		default:
			break;
	}
}


-(void) dealloc{
	[super dealloc];
	[zst release];
	[fxt release];
	[currInfo release];
}

@end
