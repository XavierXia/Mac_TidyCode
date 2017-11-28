//
//  tdxMacAppDelegate.m
//  tdxMac
//
//  Created by tdx on 11-8-16.
//  Copyright 2011 武汉. All rights reserved.
//

#import "tdxMacAppDelegate.h"
#import "macro.h"

@implementation tdxMacAppDelegate

@synthesize window;
-(void) applicationWillFinishLaunching:(NSNotification *)notification{
	NSArray * a =[[NSFontManager sharedFontManager] availableFonts];
	
	NSStringEncoding simpChinese = CFStringConvertEncodingToNSStringEncoding(kCFStringEncodingGB_18030_2000);

	for(NSString *name in a){
		NSFont * font = [NSFont systemFontOfSize:12.0];
		NSStringEncoding e = [font mostCompatibleStringEncoding];
		if (e == simpChinese) {
			NSLog(@"dispaly name is :%@ ",[font displayName]);
		}
	}
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
	modalSession = nil;
	modalFastWTSession = nil;
    myWindowsController=nil;
	
	sortButton = [[NSPopUpButton alloc]initWithFrame:NSZeroRect pullsDown:NO];
	coltButton = [[NSPopUpButton alloc]initWithFrame:NSZeroRect pullsDown:NO];

	
	  
	g_pEComm = [[EComm alloc] init];
	g_TradeComm = [[ETradeComm alloc]init];
	mainGetdata = [[EGetData alloc] initWithComm:g_pEComm tradeComm:g_TradeComm];
	
	NSDictionary * funcInfoDict = [NSDictionary dictionaryWithContentsOfFile:[[NSBundle mainBundle] pathForResource:@"tradeFuncInfo" ofType: @"dict"]];
	serviceInfoArray = [[NSMutableArray alloc] initWithArray:[funcInfoDict objectForKey:@"service"]];
	
	[mainGetdata InitHqInfo];
	[mainGetdata InitClientInfo];
	
	mainGetdata.clientinfos.localhqsites.bfindbest = mainGetdata.clientinfos.hqParams.bautocheckfast;
	mainGetdata.clientinfos.localjysites.bfindbest = mainGetdata.clientinfos.hqParams.bautocheckfast;
	
	//初始化更项配置
	mainGetdata.refreshTime = mainGetdata.clientinfos.hqParams.nhqrefreshspan;
    mainGetdata.njylockspan=mainGetdata.clientinfos.hqParams.njylockspan;
    if(mainGetdata.njylockspan<1)
        mainGetdata.njylockspan=1;
	mainGetdata.sortRefreshTime = mainGetdata.clientinfos.hqParams.nsortrefreshspan;
	
	NSRect screenRect = [[NSScreen mainScreen] frame];
	NSRect rc = NSMakeRect(screenRect.size.width/2.0f - 250.0f, screenRect.size.height/2.0f - 160.0f, 500, 320);
	NSUInteger uiStyle = NSBorderlessWindowMask| NSTitledWindowMask  | NSClosableWindowMask;
	NSBackingStoreType backingStoreStyle = NSBackingStoreBuffered;
	loginWin = [[NSWindow alloc] initWithContentRect:rc styleMask:uiStyle backing:backingStoreStyle defer:NO];	
	
	loginWindowsController = [[LoginWindowController alloc]initWithMyWindow:loginWin eGetData:mainGetdata];
	loginWindowsController.showDelegate =self;
	loginWindowsController.mainView.showDelegate = self;
	mainGetdata.g_TradeComm.jyLoginDelegate = loginWindowsController.mainView;
	
	
	rc = NSMakeRect(0, 0, 300, 150);
	uiStyle = NSBorderlessWindowMask| NSTitledWindowMask  | NSClosableWindowMask;
	backingStoreStyle = NSBackingStoreBuffered;
	sysStatWin= [[NSWindow alloc] initWithContentRect:rc styleMask:uiStyle backing:backingStoreStyle defer:NO];	
	
	sysStatWindowsController = [[SysStatWindowController alloc]initWithMyWindow:sysStatWin eGetData:mainGetdata];
	sysStatWindowsController.showDelegate =self;
	sysStatWindowsController.mainView.showDelegate = self;
	
	rc = NSMakeRect(0, 0, 500, 320);
	uiStyle = NSBorderlessWindowMask| NSTitledWindowMask  | NSClosableWindowMask;
	backingStoreStyle = NSBackingStoreBuffered;
	sysConfigWin= [[NSWindow alloc] initWithContentRect:rc styleMask:uiStyle backing:backingStoreStyle defer:NO];	
	
	sysConfigWindowsController = [[SysConfigWindowController alloc]initWithMyWindow:sysConfigWin eGetData:mainGetdata];
	sysConfigWindowsController.showDelegate =self;
	sysConfigWindowsController.mainView.showDelegate = self;
	
	
	[[loginWindowsController window] setTitle:MAC_TITLETIP];
    [[loginWindowsController window]  makeKeyAndOrderFront:[loginWindowsController window]];
    [[loginWindowsController window]  makeMainWindow];
	loginWindowsController.mainView.bshowFlag = YES;
	[loginWindowsController.mainView onViewWillAppear];
	
	
	//	//网络监控相关
	[[NSNotificationCenter defaultCenter] addObserver:self
											 selector:@selector(reachabilityChanged:)
												 name: kReachabilityChangedNotification
											   object: nil];
	hostReach = [[Reachability reachabilityWithHostName:@"www.baidu.com"] retain];
	[hostReach startNotifier];
	
}

// 通知网络状态
- (void)reachabilityChanged:(NSNotification *)note {
	Reachability* curReach = [note object];
	NSParameterAssert([curReach isKindOfClass: [Reachability class]]);
	NetworkStatus status = [curReach currentReachabilityStatus];
	
	
	if ((status == NotReachable)&&(nowStatus!=NotReachable)) {
	}
	else if ((status == ReachableViaWiFi) && (nowStatus == NotReachable)){
	}
	
	else if ((status == ReachableViaWWAN) && (nowStatus == NotReachable)){
		
		NSURLRequest * request = [[[NSURLRequest alloc] initWithURL:[NSURL URLWithString:@"www.baidu.com"] cachePolicy:NSURLRequestReloadIgnoringCacheData timeoutInterval:8] autorelease];
		
		NSURLResponse * urlResponse = nil;
		NSError * error = [[[NSError alloc] init] autorelease];
		[NSURLConnection sendSynchronousRequest:request returningResponse:&urlResponse error:&error];
		
	}
	
	nowStatus = status;
	mainGetdata.netStat = nowStatus;
}


#pragma mark menu相关
-(void)initFuncMenu{
	NSMenuItem * newItem;
	NSMenuItem * newSubItem;
	NSMenuItem * leafItem;
	NSMenu * newMenu;
	NSMenu * newSubMenu;
	
	int menuIndex = 1;
	//功能菜单
	newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"功能" action:nil keyEquivalent:@""];
	[newItem setEnabled:YES];
	[newItem setTarget:self];
	newMenu = [[NSMenu allocWithZone:[NSMenu menuZone]] initWithTitle:@"功能"];
	
	newSubItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"报价分析" action:@selector(menuClick:) keyEquivalent:@""];
	[newSubItem setTag:MAC_MENU_FUNC_GRID];
	[newSubItem setTarget:self];
	[newMenu addItem:newSubItem];
	[newSubItem release];
	newSubItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"即时分析" action:@selector(menuClick:) keyEquivalent:@""];
	[newSubItem setTag:MAC_MENU_FUNC_ZST];
	[newSubItem setTarget:self];
	[newMenu addItem:newSubItem];
	[newSubItem release];
	
	newSubItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"技术分析" action:@selector(menuClick:) keyEquivalent:@""];
	[newSubItem setTag:MAC_MENU_FUNC_FXT];
	[newSubItem setTarget:self];
	[newMenu addItem:newSubItem];
	[newSubItem release];
	
	newSubItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"基本资料" action:@selector(menuClick:) keyEquivalent:@""];
	[newSubItem setTag:MAC_MENU_FUNC_F10];
	[newSubItem setTarget:self];
	[newMenu addItem:newSubItem];
	[newSubItem release];
	
	[newItem setSubmenu:newMenu];
	[newMenu release];
	
	[[NSApp mainMenu] insertItem:newItem atIndex:menuIndex];
	[newItem release];
	
	menuIndex++;
	
	newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"报价" action:nil keyEquivalent:@""];
	[newItem setEnabled:YES];
	[newItem setTarget:self];
	
	newMenu = [[NSMenu allocWithZone:[NSMenu menuZone]] initWithTitle:@"报价"];

	newSubItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"自选股		 F6" action:@selector(menuClick:) keyEquivalent:@""];
	[newSubItem setTag:MAC_MENU_GRID_ZIXUAN];
	[newSubItem setTarget:self];
	[newMenu addItem:newSubItem];
	[newSubItem release];
	
	
	//沪深分类菜单
	newSubItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"沪深分类" action:nil keyEquivalent:@""];
	[newSubItem setTarget:self];
	//二级菜单
	coltMenu=[[NSMenu allocWithZone:[NSMenu menuZone]] initWithTitle:@"沪深分类"];
	leafItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"上证A股		1" action:@selector(menuClick:) keyEquivalent:@""];
	[leafItem setTag:MAC_MENU_GRID_SHAG];
	[leafItem setTarget:self];
	[coltMenu addItem:leafItem];
	[leafItem release];
	
	leafItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"上证B股		2" action:@selector(menuClick:) keyEquivalent:@""];
	[leafItem setTag:MAC_MENU_GRID_SHBG];
	[leafItem setTarget:self];
	[coltMenu addItem:leafItem];
	[leafItem release];
	
	leafItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"深证A股		3" action:@selector(menuClick:) keyEquivalent:@""];
	[leafItem setTag:MAC_MENU_GRID_SZAG];
	[leafItem setTarget:self];
	[coltMenu addItem:leafItem];
	[leafItem release];
	
	leafItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"深证B股		4" action:@selector(menuClick:) keyEquivalent:@""];
	[leafItem setTag:MAC_MENU_GRID_SZBG];
	[leafItem setTarget:self];
	[coltMenu addItem:leafItem];
	[leafItem release];
	
	leafItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"上证债券	5" action:@selector(menuClick:) keyEquivalent:@""];
	[leafItem setTag:MAC_MENU_GRID_SHZQ];
	[leafItem setTarget:self];
	[coltMenu addItem:leafItem];
	[leafItem release];
	
	leafItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"深证债券	6" action:@selector(menuClick:) keyEquivalent:@""];
	[leafItem setTag:MAC_MENU_GRID_SZZQ];
	[leafItem setTarget:self];
	[coltMenu addItem:leafItem];
	[leafItem release];
	
	leafItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"沪深A股		7" action:@selector(menuClick:) keyEquivalent:@""];
	[leafItem setTag:MAC_MENU_GRID_HSAG];
	[leafItem setTarget:self];
	[coltMenu addItem:leafItem];
	[leafItem release];
	
	leafItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"沪深B股		8" action:@selector(menuClick:) keyEquivalent:@""];
	[leafItem setTag:MAC_MENU_GRID_HSBG];
	[leafItem setTarget:self];
	[coltMenu addItem:leafItem];
	[leafItem release];
	
	leafItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"沪深债券" action:@selector(menuClick:) keyEquivalent:@""];
	[leafItem setTag:MAC_MENU_GRID_HSZQ];
	[leafItem setTarget:self];
	[coltMenu addItem:leafItem];
	[leafItem release];
	
	leafItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"沪深基金" action:@selector(menuClick:) keyEquivalent:@""];
	[leafItem setTag:MAC_MENU_GRID_HSJJ];
	[leafItem setTarget:self];
	[coltMenu addItem:leafItem];
	[leafItem release];
	
	leafItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"所有股票" action:@selector(menuClick:) keyEquivalent:@""];
	[leafItem setTag:MAC_MENU_GRID_ALLGP];
	[leafItem setTarget:self];
	[coltMenu addItem:leafItem];
	[leafItem release];
	
	leafItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"所有指数" action:@selector(menuClick:) keyEquivalent:@""];
	[leafItem setTag:MAC_MENU_GRID_ALLZS];
	[leafItem setTarget:self];
	[coltMenu addItem:leafItem];
	[leafItem release];
	
	leafItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"中小企业	9" action:@selector(menuClick:) keyEquivalent:@""];
	[leafItem setTag:MAC_MENU_GRID_ZXQY];
	[leafItem setTarget:self];
	[coltMenu addItem:leafItem];
	[leafItem release];
	
	leafItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"沪深权证	11" action:@selector(menuClick:) keyEquivalent:@""];
	[leafItem setTag:MAC_MENU_GRID_HSQZ];
	[leafItem setTarget:self];
	[coltMenu addItem:leafItem];
	[leafItem release];
	
	leafItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"创业板		12" action:@selector(menuClick:) keyEquivalent:@""];
	[leafItem setTag:MAC_MENU_GRID_CYB];
	[leafItem setTarget:self];
	[coltMenu addItem:leafItem];
	[leafItem release];
	
	[coltButton setMenu:coltMenu];
	[newSubItem setSubmenu:coltMenu];
	
	[newMenu addItem:newSubItem];
	[newSubItem release];
	//沪深分类菜单结束
	
	
	//栏目排名菜单
	newSubItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"栏目排名" action:nil keyEquivalent:@""];
	[newSubItem setTarget:self];
	
	//二级菜单
	sortMenu=[[NSMenu allocWithZone:[NSMenu menuZone]] initWithTitle:@"栏目排名"];
	leafItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"分类行情显示" action:@selector(menuClick:) keyEquivalent:@""];
	[leafItem setTag:MAC_MENU_SORT_NORMAL];
	[leafItem setTarget:self];
	[sortMenu addItem:leafItem];
	[leafItem release];
	
	leafItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"涨幅排名" action:@selector(menuClick:) keyEquivalent:@""];
	[leafItem setTag:MAC_MENU_SORT_ZAF];
	[leafItem setTarget:self];
	[sortMenu addItem:leafItem];
	[leafItem release];
	
	leafItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"现价排名" action:@selector(menuClick:) keyEquivalent:@""];
	[leafItem setTag:MAC_MENU_SORT_ZJCJ];
	[leafItem setTarget:self];
	[sortMenu addItem:leafItem];
	[leafItem release];
	
	leafItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"成交量排名" action:@selector(menuClick:) keyEquivalent:@""];
	[leafItem setTag:MAC_MENU_SORT_CJL];
	[leafItem setTarget:self];
	[sortMenu addItem:leafItem];
	[leafItem release];
	
	leafItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"换手率排名" action:@selector(menuClick:) keyEquivalent:@""];
	[leafItem setTag:MAC_MENU_SORT_HSL];
	[leafItem setTarget:self];
	[sortMenu addItem:leafItem];
	[leafItem release];
	
	leafItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"成交金额排名" action:@selector(menuClick:) keyEquivalent:@""];
	[leafItem setTag:MAC_MENU_SORT_CJJE];
	[leafItem setTarget:self];
	[sortMenu addItem:leafItem];
	[leafItem release];
	
	leafItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"振幅排名" action:@selector(menuClick:) keyEquivalent:@""];
	[leafItem setTag:MAC_MENU_SORT_ZEF];
	[leafItem setTarget:self];
	[sortMenu addItem:leafItem];
	[leafItem release];
	
	leafItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"流通股本排名" action:@selector(menuClick:) keyEquivalent:@""];
	[leafItem setTag:MAC_MENU_SORT_LTGB];
	[leafItem setTarget:self];
	[sortMenu addItem:leafItem];
	[leafItem release];
	
	leafItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"总市值排名" action:@selector(menuClick:) keyEquivalent:@""];
	[leafItem setTag:MAC_MENU_SORT_ZSZ];
	[leafItem setTarget:self];
	[sortMenu addItem:leafItem];
	[leafItem release];
	
	leafItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"市盈率排名" action:@selector(menuClick:) keyEquivalent:@""];
	[leafItem setTag:MAC_MENU_SORT_SYL];
	[leafItem setTarget:self];
	[sortMenu addItem:leafItem];
	[leafItem release];
	
	[sortButton setMenu:sortMenu];
	[newSubItem setSubmenu:sortMenu];
	
	[newMenu addItem:newSubItem];
	[newSubItem release];
	//栏目排名菜单结束
	
	
	
	[newItem setSubmenu:newMenu];
	[newMenu release];

	
	[[NSApp mainMenu] insertItem:newItem atIndex:menuIndex];
	[newItem release];
	
	menuIndex++;
	
	
	newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"分析" action:nil keyEquivalent:@""];
	[newItem setEnabled:YES];
	[newItem setTarget:self];
	newMenu = [[NSMenu allocWithZone:[NSMenu menuZone]] initWithTitle:@"分析"];
	
	//大盘走势菜单
	newSubItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"大盘走势" action:@selector(menuClick:) keyEquivalent:@""];
	[newSubItem setTarget:self];
	//二级菜单
	newSubMenu=[[NSMenu allocWithZone:[NSMenu menuZone]] initWithTitle:@"大盘走势"];
	leafItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"上证180走势" action:@selector(menuClick:) keyEquivalent:@""];
	[leafItem setTag:MAC_MENU_ZST_SH180];
	[leafItem setTarget:self];
	[newSubMenu addItem:leafItem];
	[leafItem release];
	
	leafItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"上证综指走势	F3" action:@selector(menuClick:) keyEquivalent:@""];
	[leafItem setTag:MAC_MENU_ZST_SHZZ];
	[leafItem setTarget:self];
	[newSubMenu addItem:leafItem];
	[leafItem release];
	
	leafItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"上证A股走势" action:@selector(menuClick:) keyEquivalent:@""];
	[leafItem setTag:MAC_MENU_ZST_SHAG];
	[leafItem setTarget:self];
	[newSubMenu addItem:leafItem];
	[leafItem release];
	
	leafItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"上证B股走势" action:@selector(menuClick:) keyEquivalent:@""];
	[leafItem setTag:MAC_MENU_ZST_SHBG];
	[leafItem setTarget:self];
	[newSubMenu addItem:leafItem];
	[leafItem release];
	
	[newSubMenu addItem:[NSMenuItem separatorItem]];

	
	leafItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"深证100走势" action:@selector(menuClick:) keyEquivalent:@""];
	[leafItem setTag:MAC_MENU_ZST_SZ100];
	[leafItem setTarget:self];
	[newSubMenu addItem:leafItem];
	[leafItem release];
	
	leafItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"深证成份走势	F4" action:@selector(menuClick:) keyEquivalent:@""];
	[leafItem setTag:MAC_MENU_ZST_SZCZ];
	[leafItem setTarget:self];
	[newSubMenu addItem:leafItem];
	[leafItem release];
	
	leafItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"深证A股走势" action:@selector(menuClick:) keyEquivalent:@""];
	[leafItem setTag:MAC_MENU_ZST_SZAG];
	[leafItem setTarget:self];
	[newSubMenu addItem:leafItem];
	[leafItem release];
	
	leafItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"深证B股走势" action:@selector(menuClick:) keyEquivalent:@""];
	[leafItem setTag:MAC_MENU_ZST_SZBG];
	[leafItem setTarget:self];
	[newSubMenu addItem:leafItem];
	[leafItem release];
	
	[newSubMenu addItem:[NSMenuItem separatorItem]];

	
	leafItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"创业板指数" action:@selector(menuClick:) keyEquivalent:@""];
	[leafItem setTag:MAC_MENU_ZST_CYB];
	[leafItem setTarget:self];
	[newSubMenu addItem:leafItem];
	[leafItem release];
	
	leafItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"中小企业指数" action:@selector(menuClick:) keyEquivalent:@""];
	[leafItem setTag:MAC_MENU_ZST_ZXQY];
	[leafItem setTarget:self];
	[newSubMenu addItem:leafItem];
	[leafItem release];
	
	leafItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"沪深300指数" action:@selector(menuClick:) keyEquivalent:@""];
	[leafItem setTag:MAC_MENU_ZST_HS300];
	[leafItem setTarget:self];
	[newSubMenu addItem:leafItem];
	[leafItem release];
	
	
	
	[newSubItem setSubmenu:newSubMenu];
	[newSubMenu release];
	
	[newMenu addItem:newSubItem];
	[newSubItem release];
	//大盘走势菜单结束
	
	newSubItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"分时走势图" action:@selector(menuClick:) keyEquivalent:@""];
	[newSubItem setTag:MAC_MENU_FUNC_ZST];
	[newSubItem setTarget:self];
	[newMenu addItem:newSubItem];
	[newSubItem release];
	
	
	newSubItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"分析图" action:@selector(menuClick:) keyEquivalent:@""];
	[newSubItem setTag:MAC_MENU_FUNC_FXT];
	[newSubItem setTarget:self];
	[newMenu addItem:newSubItem];
	[newSubItem release];
	
	
	[newItem setSubmenu:newMenu];
	[newMenu release];
	
	[[NSApp mainMenu] insertItem:newItem atIndex:menuIndex];
	[newItem release];
	
	menuIndex++;
	
#ifndef IMAC_ONLYHQ
	newItem = [[NSMenuItem alloc]initWithTitle:@"交易" action:nil keyEquivalent:@""];
	[newItem setEnabled:YES];
	[newItem setTarget:self];
	newMenu = [[NSMenu allocWithZone:[NSMenu menuZone]] initWithTitle:@"交易"];
	
	if (mainGetdata.tradeLoginFlag) {
		newSubItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"显示/隐藏	F2" action:@selector(menuClick:) keyEquivalent:@""];
		[newSubItem setTag:MAC_MENU_HIDEANDSHOW_LOCK];
		[newSubItem setTarget:self];
		[newMenu addItem:newSubItem];
		[newSubItem release];
		
		newSubItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"交易锁定" action:@selector(menuClick:) keyEquivalent:@""];
		[newSubItem setTag:MAC_MENU_TRADE_LOCK];
		[newSubItem setTarget:self];
		[newMenu addItem:newSubItem];
		[newSubItem release];
		
		newSubItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"切换用户" action:@selector(menuClick:) keyEquivalent:@""];
		[newSubItem setTag:MAC_MENU_TRADE_SWITCH];
		[newSubItem setTarget:self];
		[newMenu addItem:newSubItem];
		[newSubItem release];
		
		newSubItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"退出交易" action:@selector(menuClick:) keyEquivalent:@""];
		[newSubItem setTag:MAC_MENU_TRADE_QUIT];
		[newSubItem setTarget:self];
		[newMenu addItem:newSubItem];
		[newSubItem release];
	}
	else {
		newSubItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"交易登录	F2" action:@selector(menuClick:) keyEquivalent:@""];
		[newSubItem setTag:MAC_MENU_TRADE_LOGIN];
		[newSubItem setTarget:self];
		[newMenu addItem:newSubItem];
		[newSubItem release];
	}


	
	
	[newItem setSubmenu:newMenu];
	[newMenu release];
	[[NSApp mainMenu] insertItem:newItem atIndex:menuIndex];
	[newItem release];
	
	menuIndex++;
	
#endif
    
#ifdef IMAC_ZXZQ
    
    newItem = [[NSMenuItem alloc]initWithTitle:@"金融商城" action:nil keyEquivalent:@""];
    [newItem setEnabled:YES];
    [newItem setTarget:self];
    newMenu = [[NSMenu allocWithZone:[NSMenu menuZone]] initWithTitle:@"金融商城"];
    
    
    {
        newSubItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"OTC理财" action:@selector(menuClick:) keyEquivalent:@""];
        [newSubItem setTag:MAC_MENU_FUNC_ZXJR];
        [newSubItem setTarget:self];
        [newMenu addItem:newSubItem];
        [newSubItem release];
    }
    
    
    
    
    [newItem setSubmenu:newMenu];
    [newMenu release];
    [[NSApp mainMenu] insertItem:newItem atIndex:menuIndex];
    [newItem release];
    
    menuIndex++;

#endif
	if (mainGetdata.clientinfos.m_nQsbs == GTJA_DLL) {
		
		
		newItem = [[NSMenuItem alloc]initWithTitle:@"国泰君安服务" action:nil keyEquivalent:@""];
		[newItem setEnabled:YES];
		[newItem setTarget:self];
		newMenu = [[NSMenu allocWithZone:[NSMenu menuZone]] initWithTitle:@"国泰君安服务"];
		
		for (int i=0; i<[serviceInfoArray count]; i++) {
			NSDictionary *tempDict = [serviceInfoArray objectAtIndex:i];
			
			if ([[tempDict objectForKey:@"Name"] length] >0) {
				newSubItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:[tempDict objectForKey:@"Name"]  action:@selector(serviceClick:) keyEquivalent:@""];
				[newSubItem setTag:i];
				[newSubItem setTarget:self];
				[newMenu addItem:newSubItem];
				[newSubItem release];
			}
			else {
				[newMenu addItem:[NSMenuItem separatorItem]];

			}

		}
		

		
		
		
		
		[newItem setSubmenu:newMenu];
		[newMenu release];
		[[NSApp mainMenu] insertItem:newItem atIndex:menuIndex];
		[newItem release];
		
		menuIndex++;
	}
	

	
	
	
	if (mainGetdata.clientinfos.m_nQsbs == ZSZQ_DLL) {
		newItem = [[NSMenuItem alloc]initWithTitle:@"帮助" action:nil keyEquivalent:@""];
		[newItem setEnabled:YES];
		[newItem setTarget:self];
		newMenu = [[NSMenu allocWithZone:[NSMenu menuZone]] initWithTitle:@"帮助"];
		
#ifdef IMAC_ZSZQ
        newSubItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"免责申明" action:@selector(menuClick:) keyEquivalent:@""];
        [newSubItem setTag:MAC_MENU_MZSM];
        [newSubItem setTarget:self];
        [newMenu addItem:newSubItem];
        [newSubItem release];
        
        newSubItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"防范非法网站" action:@selector(menuClick:) keyEquivalent:@""];
        [newSubItem setTag:MAC_MENU_FFFFWZ];
        [newSubItem setTarget:self];
        [newMenu addItem:newSubItem];
        [newSubItem release];
        
        newSubItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"密码安全提示" action:@selector(menuClick:) keyEquivalent:@""];
        [newSubItem setTag:MAC_MENU_MMTS];
        [newSubItem setTarget:self];
        [newMenu addItem:newSubItem];
        [newSubItem release];
        
#endif
        
		newSubItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"软件操作向导" action:@selector(menuClick:) keyEquivalent:@""];
		[newSubItem setTag:MAC_MENU_OPERATIONHELP];
		[newSubItem setTarget:self];
		[newMenu addItem:newSubItem];
		[newSubItem release];
		
		
		[newItem setSubmenu:newMenu];
		[newMenu release];
		[[NSApp mainMenu] insertItem:newItem atIndex:menuIndex];
		[newItem release];
		menuIndex++;
	}
	
}

-(void)dealTradeMenu{
	NSMenuItem * newItem = [[NSApp mainMenu] itemAtIndex:4];

	NSMenu * newMenu = [[NSMenu allocWithZone:[NSMenu menuZone]] initWithTitle:@"交易"];
	NSMenuItem * newSubItem;
	if (mainGetdata.tradeLoginFlag) {
		newSubItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"显示/隐藏	F2" action:@selector(menuClick:) keyEquivalent:@""];
		[newSubItem setTag:MAC_MENU_HIDEANDSHOW_LOCK];
		[newSubItem setTarget:self];
		[newMenu addItem:newSubItem];
		[newSubItem release];
		
		newSubItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"交易锁定" action:@selector(menuClick:) keyEquivalent:@""];
		[newSubItem setTag:MAC_MENU_TRADE_LOCK];
		[newSubItem setTarget:self];
		[newMenu addItem:newSubItem];
		[newSubItem release];
		
		newSubItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"切换用户" action:@selector(menuClick:) keyEquivalent:@""];
		[newSubItem setTag:MAC_MENU_TRADE_SWITCH];
		[newSubItem setTarget:self];
		[newMenu addItem:newSubItem];
		[newSubItem release];
		
		newSubItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"退出交易" action:@selector(menuClick:) keyEquivalent:@""];
		[newSubItem setTag:MAC_MENU_TRADE_QUIT];
		[newSubItem setTarget:self];
		[newMenu addItem:newSubItem];
		[newSubItem release];
	}
	else {
		newSubItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]]initWithTitle:@"交易登录	F2" action:@selector(menuClick:) keyEquivalent:@""];
		[newSubItem setTag:MAC_MENU_TRADE_LOGIN];
		[newSubItem setTarget:self];
		[newMenu addItem:newSubItem];
		[newSubItem release];
	}
	
	
	
	
	[newItem setSubmenu:newMenu];
	[newMenu release];
	
}


-(void)serviceClick:(id)sender{
	NSMenuItem * tempItem = (NSMenuItem *)sender;
	if([tempItem tag]>=[serviceInfoArray count])
        return;
	NSDictionary * tempDic = [serviceInfoArray objectAtIndex:[tempItem tag]];
	[myWindowsController.mainView getHQProcess:[tempDic objectForKey:@"Image"] gpSetcode:-1 typeID:MAC_WEB_FUNC pareOne:-1 paraTwo:-1];
	
}

-(void)OnZxjr
{
    NSURL *url = [[NSURL alloc] initWithString:@"https://weixin.citicsinfo.com/tztpc/jy/otc_new/otc_index.html"];
    [[NSWorkspace sharedWorkspace] openURL:url];
}

-(void)menuClick:(id)sender{
	NSMenuItem * tempItem = (NSMenuItem *)sender;
	int tempInt = [tempItem tag];
	switch (tempInt) {
		case MAC_MENU_FUNC_GRID:
			[myWindowsController.mainView getHQProcess:@"" gpSetcode:-1 typeID:MAC_ZFPM_FUNC pareOne:-1 paraTwo:-1];
			break;
		case MAC_MENU_FUNC_ZST:
			[myWindowsController.mainView getHQProcess:@"" gpSetcode:-1 typeID:MAC_ZST_FUNC pareOne:1 paraTwo:-1];
			break;
		case MAC_MENU_FUNC_FXT:
			[myWindowsController.mainView getHQProcess:@"" gpSetcode:-1 typeID:MAC_ZST_FUNC pareOne:2 paraTwo:-1];
			break;
		case MAC_MENU_FUNC_F10:
			[myWindowsController.mainView getHQProcess:@"" gpSetcode:-1 typeID:MAC_F10_FUNC pareOne:-1 paraTwo:-1];
			break;
        case MAC_MENU_FUNC_ZXJR:
        //    [myWindowsController.mainView getHQProcess:@"https://weixin.citicsinfo.com/tztpc/jy/otc_new/otc_index.html" gpSetcode:-1 typeID:MAC_WEB_FUNC pareOne:-1 paraTwo:-1];

            [self OnZxjr];
            
            break;
		//排名
		case MAC_MENU_GRID_ZIXUAN:
			[myWindowsController.mainView getHQProcess:@"" gpSetcode:-1 typeID:MAC_ZFPM_FUNC pareOne:DOMAIN_SELF paraTwo:-1];
			break;
		case MAC_MENU_GRID_SHAG:
			[myWindowsController.mainView getHQProcess:@"" gpSetcode:-1 typeID:MAC_ZFPM_FUNC pareOne:DOMAIN_SHAG paraTwo:-1];
			break;
		case MAC_MENU_GRID_SHBG:
			[myWindowsController.mainView getHQProcess:@"" gpSetcode:-1 typeID:MAC_ZFPM_FUNC pareOne:DOMAIN_SHBG paraTwo:-1];
			break;
		case MAC_MENU_GRID_SZAG:
			[myWindowsController.mainView getHQProcess:@"" gpSetcode:-1 typeID:MAC_ZFPM_FUNC pareOne:DOMAIN_SZAG paraTwo:-1];
			break;
		case MAC_MENU_GRID_SZBG:
			[myWindowsController.mainView getHQProcess:@"" gpSetcode:-1 typeID:MAC_ZFPM_FUNC pareOne:DOMAIN_SZBG paraTwo:-1];
			break;	
		case MAC_MENU_GRID_SHZQ:
			[myWindowsController.mainView getHQProcess:@"" gpSetcode:-1 typeID:MAC_ZFPM_FUNC pareOne:DOMAIN_SHZQ paraTwo:-1];
			break;	
		case MAC_MENU_GRID_SZZQ:
			[myWindowsController.mainView getHQProcess:@"" gpSetcode:-1 typeID:MAC_ZFPM_FUNC pareOne:DOMAIN_SZZQ paraTwo:-1];
			break;	
		case MAC_MENU_GRID_HSAG:
			[myWindowsController.mainView getHQProcess:@"" gpSetcode:-1 typeID:MAC_ZFPM_FUNC pareOne:DOMAIN_ALLAG paraTwo:-1];
			break;	
		case MAC_MENU_GRID_HSBG:
			[myWindowsController.mainView getHQProcess:@"" gpSetcode:-1 typeID:MAC_ZFPM_FUNC pareOne:DOMAIN_ALLBG paraTwo:-1];
			break;	
		case MAC_MENU_GRID_HSZQ:
			[myWindowsController.mainView getHQProcess:@"" gpSetcode:-1 typeID:MAC_ZFPM_FUNC pareOne:DOMAIN_ALLZQ paraTwo:-1];
			break;
		case MAC_MENU_GRID_HSJJ:
			[myWindowsController.mainView getHQProcess:@"" gpSetcode:-1 typeID:MAC_ZFPM_FUNC pareOne:DOMAIN_ALLJJ paraTwo:-1];
			break;	
		case MAC_MENU_GRID_ALLGP:
			[myWindowsController.mainView getHQProcess:@"" gpSetcode:-1 typeID:MAC_ZFPM_FUNC pareOne:DOMAIN_ALLGP paraTwo:-1];
			break;	
		case MAC_MENU_GRID_ALLZS:
			[myWindowsController.mainView getHQProcess:@"" gpSetcode:-1 typeID:MAC_ZFPM_FUNC pareOne:DOMAIN_ALLZS paraTwo:-1];
			break;	
		case MAC_MENU_GRID_ZXQY:
			[myWindowsController.mainView getHQProcess:@"" gpSetcode:-1 typeID:MAC_ZFPM_FUNC pareOne:DOMAIN_CYZQ paraTwo:-1];
			break;
		case MAC_MENU_GRID_HSQZ:
			[myWindowsController.mainView getHQProcess:@"" gpSetcode:-1 typeID:MAC_ZFPM_FUNC pareOne:DOMAIN_SHQZ paraTwo:-1];
			break;
		case MAC_MENU_GRID_CYB:
			[myWindowsController.mainView getHQProcess:@"" gpSetcode:-1 typeID:MAC_ZFPM_FUNC pareOne:DOMAIN_CYB paraTwo:-1];
			break;	
		//排序
		case MAC_MENU_SORT_NORMAL:
			[myWindowsController.mainView getHQProcess:@"" gpSetcode:-1 typeID:MAC_ZFPM_FUNC pareOne:-1 paraTwo:ZQDM];
			break;

		case MAC_MENU_SORT_ZAF:
			[myWindowsController.mainView getHQProcess:@"" gpSetcode:-1 typeID:MAC_ZFPM_FUNC pareOne:-1 paraTwo:ZAF];
			break;
		case MAC_MENU_SORT_ZJCJ:
			[myWindowsController.mainView getHQProcess:@"" gpSetcode:-1 typeID:MAC_ZFPM_FUNC pareOne:-1 paraTwo:ZJCJ];
			break;
		case MAC_MENU_SORT_CJL:
			[myWindowsController.mainView getHQProcess:@"" gpSetcode:-1 typeID:MAC_ZFPM_FUNC pareOne:-1 paraTwo:CJL];
			break;
		case MAC_MENU_SORT_HSL:
			[myWindowsController.mainView getHQProcess:@"" gpSetcode:-1 typeID:MAC_ZFPM_FUNC pareOne:-1 paraTwo:HSL];
			break;	
		case MAC_MENU_SORT_CJJE:
			[myWindowsController.mainView getHQProcess:@"" gpSetcode:-1 typeID:MAC_ZFPM_FUNC pareOne:-1 paraTwo:CJJE];
			break;	
		case MAC_MENU_SORT_ZEF:
			[myWindowsController.mainView getHQProcess:@"" gpSetcode:-1 typeID:MAC_ZFPM_FUNC pareOne:-1 paraTwo:ZEF];
			break;	
		case MAC_MENU_SORT_LTGB:
			[myWindowsController.mainView getHQProcess:@"" gpSetcode:-1 typeID:MAC_ZFPM_FUNC pareOne:-1 paraTwo:LTGB];
			break;	
		case MAC_MENU_SORT_ZSZ:
			[myWindowsController.mainView getHQProcess:@"" gpSetcode:-1 typeID:MAC_ZFPM_FUNC pareOne:-1 paraTwo:ZSZ];
			break;	
		case MAC_MENU_SORT_SYL:
			[myWindowsController.mainView getHQProcess:@"" gpSetcode:-1 typeID:MAC_ZFPM_FUNC pareOne:-1 paraTwo:SYL];
			break;	
		case MAC_MENU_FUNC_TRADE:
		{
			if (mainGetdata.tradeLoginFlag) {
				if (myWindowsController.mainView.tradeShowFlag) {
					myWindowsController.mainView.tradeShowFlag = NO;
				}else {
					myWindowsController.mainView.tradeShowFlag = YES;
				}
				[myWindowsController.mainView dealTradeViewShow];
				
			}
			else {
				[self showLogin];
			}
		}
			break;
		case MAC_MENU_ZST_SH180:
			[myWindowsController.mainView getHQProcess:@"000010" gpSetcode:1 typeID:MAC_ZST_FUNC pareOne:1 paraTwo:-1];
			break;
		case MAC_MENU_ZST_SHZZ:
			[myWindowsController.mainView getHQProcess:@"999999" gpSetcode:1 typeID:MAC_ZST_FUNC pareOne:1 paraTwo:-1];
			break;
		case MAC_MENU_ZST_SHAG:
			[myWindowsController.mainView getHQProcess:@"999998" gpSetcode:1 typeID:MAC_ZST_FUNC pareOne:1 paraTwo:-1];
			break;
		case MAC_MENU_ZST_SHBG:
			[myWindowsController.mainView getHQProcess:@"999997" gpSetcode:1 typeID:MAC_ZST_FUNC pareOne:1 paraTwo:-1];
			break;
		case MAC_MENU_ZST_SZ100:
			[myWindowsController.mainView getHQProcess:@"399004" gpSetcode:0 typeID:MAC_ZST_FUNC pareOne:1 paraTwo:-1];
			break;
		case MAC_MENU_ZST_SZCZ:
			[myWindowsController.mainView getHQProcess:@"399001" gpSetcode:0 typeID:MAC_ZST_FUNC pareOne:1 paraTwo:-1];
			break;	
		case MAC_MENU_ZST_SZAG:
			[myWindowsController.mainView getHQProcess:@"399002" gpSetcode:0 typeID:MAC_ZST_FUNC pareOne:1 paraTwo:-1];
			break;	
		case MAC_MENU_ZST_SZBG:
			[myWindowsController.mainView getHQProcess:@"399003" gpSetcode:0 typeID:MAC_ZST_FUNC pareOne:1 paraTwo:-1];
			break;	
		case MAC_MENU_ZST_CYB:
			[myWindowsController.mainView getHQProcess:@"399006" gpSetcode:0 typeID:MAC_ZST_FUNC pareOne:1 paraTwo:-1];
			break;		
		case MAC_MENU_ZST_ZXQY:
			[myWindowsController.mainView getHQProcess:@"399005" gpSetcode:0 typeID:MAC_ZST_FUNC pareOne:1 paraTwo:-1];
			break;	
		case MAC_MENU_ZST_HS300:
			[myWindowsController.mainView getHQProcess:@"399300" gpSetcode:0 typeID:MAC_ZST_FUNC pareOne:1 paraTwo:-1];
			break;	
		case MAC_MENU_TRADE_LOGIN:
			[self showLogin];
			break;
		case MAC_MENU_TRADE_LOCK:
			[myWindowsController.mainView lockButtonClick];
			break;
		case MAC_MENU_TRADE_QUIT:{
			NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
											 defaultButton: @"确定"
										   alternateButton:@"取消"
											   otherButton: nil
								 informativeTextWithFormat: @"你确定要退出交易系统吗？"];
			[alert setDelegate:self];
			NSInteger result = [alert runModal];
			[self handleResult:alert withResult:result];	
		}
			break;
		case MAC_MENU_TRADE_SWITCH:
			[myWindowsController.mainView closeButtonClick];
			[self showLogin];
			break;
		case MAC_MENU_HIDEANDSHOW_LOCK:
			if (myWindowsController.mainView.eGetData.tradeLoginFlag) {
				if (myWindowsController.mainView.tradeShowFlag) {
					myWindowsController.mainView.tradeShowFlag = NO;
				}else {
					myWindowsController.mainView.tradeShowFlag = YES;
				}
				[myWindowsController.mainView dealTradeViewShow];
				
			}
			break;
		case MAC_MENU_ALLSCREEN:
			[myWindowsController dealFullScreen];
			break;
		case MAC_MENU_OPERATIONHELP:
			[myWindowsController.mainView getHQProcess:@"http://news.newone.com.cn/newone/zhuanyeban/mac/index.html" gpSetcode:-1 typeID:MAC_WEB_FUNC pareOne:-1 paraTwo:-1];
			break;
        case MAC_MENU_MZSM:
            [myWindowsController.mainView getHQProcess:@"http://zszx.newone.com.cn:8978/public/common/html/mzsm.html" gpSetcode:-1 typeID:MAC_WEB_FUNC pareOne:-1 paraTwo:-1];
            break;
        case MAC_MENU_FFFFWZ:
            [myWindowsController.mainView getHQProcess:@"http://zszx.newone.com.cn:8978/public/common/html/ffffwz.html" gpSetcode:-1 typeID:MAC_WEB_FUNC pareOne:-1 paraTwo:-1];
            break;
        case MAC_MENU_MMTS:
            [myWindowsController.mainView getHQProcess:@"http://zszx.newone.com.cn:8978/public/common/html/mmts.html" gpSetcode:-1 typeID:MAC_WEB_FUNC pareOne:-1 paraTwo:-1];
            break;
		default:
			break;
	}
}


#pragma mark alert相关
-(void)handleResult:(NSAlert *)alert withResult:(NSInteger)result
{
	switch(result)
	{
			//删除自选股
		case NSAlertDefaultReturn:
			[myWindowsController.mainView closeButtonClick2];
			break;
			
		case NSAlertAlternateReturn:
			break;
			
		case NSAlertOtherReturn:
			break;
            
        default:
            break;
	}
	
}

#pragma mark 事件相关
-(void)onTeleSet
{
    [NSApp beginSheet:[sysConfigWindowsController window] modalForWindow:[loginWindowsController window] modalDelegate:self didEndSelector:@selector(saveSheetDidEnd:returnCode:contextInfo:) contextInfo:NULL];
    
    [sysConfigWindowsController.mainView showInfo];
}

-(void)dealTitleName:(NSString *)_titleName{
	if (myWindowsController != nil) {
		[[myWindowsController window] setTitle:[NSString stringWithFormat:@"%@ %@",MAC_TITLETIP,_titleName]];
		
	}
}

-(void)dealSortSelect:(int)_coltType sortType:(int)_sortType{
	switch (_sortType) {
		case ZQDM:
			[sortButton selectItemAtIndex:0];
			break;
		case ZAF:
			[sortButton selectItemAtIndex:1];
			break;
		case ZJCJ:
			[sortButton selectItemAtIndex:2];
			break;
		case CJL:
			[sortButton selectItemAtIndex:3];
			break;	
		case HSL:
			[sortButton selectItemAtIndex:4];
			break;
		case CJJE:
			[sortButton selectItemAtIndex:5];
			break;
		case ZEF:
			[sortButton selectItemAtIndex:6];
			break;
		case LTGB:
			[sortButton selectItemAtIndex:7];
			break;
		case ZSZ:
			[sortButton selectItemAtIndex:8];
			break;
		case SYL:
			[sortButton selectItemAtIndex:9];
			break;
		default:
			break;	
			
	}
	
	switch (_coltType) {
		case DOMAIN_SHAG:
			[coltButton selectItemAtIndex:0];
			break;
		case DOMAIN_SHBG:
			[coltButton selectItemAtIndex:1];
			break;
		case DOMAIN_SZAG:
			[coltButton selectItemAtIndex:2];
			break;
		case DOMAIN_SZBG:
			[coltButton selectItemAtIndex:3];
			break;	
		case DOMAIN_SHZQ:
			[coltButton selectItemAtIndex:4];
			break;
		case DOMAIN_SZZQ:
			[coltButton selectItemAtIndex:5];
			break;
		case DOMAIN_ALLAG:
			[coltButton selectItemAtIndex:6];
			break;
		case DOMAIN_ALLBG:
			[coltButton selectItemAtIndex:7];
			break;		
		case DOMAIN_ALLZQ:
			[coltButton selectItemAtIndex:8];
			break;
		case DOMAIN_ALLJJ:
			[coltButton selectItemAtIndex:9];
			break;	
		case DOMAIN_ALLGP:
			[coltButton selectItemAtIndex:10];
			break;
		case DOMAIN_ALLZS:
			[coltButton selectItemAtIndex:11];
			break;	
		case DOMAIN_CYZQ:
			[coltButton selectItemAtIndex:12];
			break;
		case DOMAIN_SHQZ:
			[coltButton selectItemAtIndex:13];
			break;
		case DOMAIN_CYB:
			[coltButton selectItemAtIndex:14];
			break;
		case DOMAIN_SELF:
			[coltButton selectItemAtIndex:15];
			break;	
		default:
			break;
	}
	
}

-(void)afterInit{
	NSRect rc = [[NSScreen mainScreen] frame];
    NSUInteger uiStyle = NSBorderlessWindowMask|NSTitledWindowMask| NSClosableWindowMask| NSResizableWindowMask |NSMiniaturizableWindowMask;// | NSResizableWindowMask 
    NSBackingStoreType backingStoreStyle = NSBackingStoreBuffered;
    
    
  
	if (myWindowsController == nil)
    {
		window = [[NSWindow alloc] initWithContentRect:rc styleMask:uiStyle backing:backingStoreStyle defer:NO screen:[NSScreen mainScreen]];	
        
		myWindowsController = [[MyWindowController alloc] initWithMyWindow:window eGetData:mainGetdata];
        
		myWindowsController.mainView.showDelegate = self;
		myWindowsController.mainView.tradeView.reconObject.showDelegate = self;
		myWindowsController.showDelegate = self;
        
		loginWindowsController.mainView.loginType = YES;
		
		
		[[loginWindowsController window] close];
		[self initFuncMenu];
		[[myWindowsController window] setTitle:MAC_TITLETIP];
		[[myWindowsController window]  makeKeyAndOrderFront:[myWindowsController window]];
		[[myWindowsController window]  makeMainWindow];
		
       
		if (mainGetdata.tradeLoginFlag) {
			myWindowsController.mainView.tradeShowFlag = YES;
		}
		[myWindowsController.mainView dealTradeViewShow];
		[myWindowsController.mainView getHQProcess:@"" gpSetcode:1 typeID:MAC_ZFPM_FUNC pareOne:-1 paraTwo:-1];
		if (mainGetdata.tradeLoginFlag) {
			[myWindowsController.mainView getTradeProcess:@"" gpSetcode:-1 typeID:MAC_TRADE_FUNC pareOne:TDX_GFCX paraTwo:-1 pareThree:@""];
		}
       
	}
		
	
}

-(void)afterLogin{	
	[[loginWindowsController window] close];
	[self dealTradeMenu];
	if (mainGetdata.tradeLoginFlag) {
		myWindowsController.mainView.tradeShowFlag = YES;
	}
	[myWindowsController.mainView dealTradeViewShow];
	if (mainGetdata.tradeLoginFlag) {
		[myWindowsController.mainView getTradeProcess:@"" gpSetcode:-1 typeID:MAC_TRADE_FUNC pareOne:TDX_GFCX paraTwo:-1 pareThree:@""];
	}
}

-(void)closeLogin{
	loginWindowsController.mainView.bshowFlag = NO;
	[[loginWindowsController window] close];
}

-(void)closeApp{
	[NSApp terminate:self];
}

-(void)closeSession{
	if (modalSession != nil) {
		[NSApp endModalSession:modalSession];
        modalSession=nil;
	}
	
	if (loginWindowsController.mainView.loginType) {
	}
	else {
		[NSApp terminate:self];
	}

}

-(void)closeFastWTSession{
	[NSApp endModalSession:modalFastWTSession];
	modalFastWTSession = nil;
}
-(void)closeFastWT{
	[[fastWTWindowsController window] close];
	myWindowsController.mainView.fastWTShowFlag = NO;
}

-(void)showLogin{
	[mainGetdata InitHqInfo];
	[mainGetdata InitClientInfo];
	
	loginWindowsController.mainView.loginType = YES;
	loginWindowsController.mainView.bshowFlag = YES;
	[loginWindowsController.mainView enableAllButton];
	[loginWindowsController.mainView InitLoginset];
	[loginWindowsController.mainView onViewWillAppear];
	modalSession = [NSApp beginModalSessionForWindow:[loginWindowsController window]];
}

-(void)showFastWT:(NSString *)_gpcode bsFlag:(int)_bsFlag gpPrice:(NSString *)_gpPrice{
	if (fastWTWindowsController == nil) {
		NSRect rc = NSMakeRect(300, 300, 236, 210);
		NSUInteger uiStyle = NSTitledWindowMask| NSClosableWindowMask;// | NSResizableWindowMask 
		NSBackingStoreType backingStoreStyle = NSBackingStoreBuffered;	

		fastWTWin = [[NSWindow alloc] initWithContentRect:rc styleMask:uiStyle backing:backingStoreStyle defer:NO];	
		fastWTWindowsController = [[FastTradeWTWindowController alloc]initWithMyWindow:fastWTWin eGetData:mainGetdata];
		fastWTWindowsController.showDelegate =self;
		fastWTWindowsController.fastWTView.showDelegate = self;
		fastWTWindowsController.fastWTView.operProcessDelegate = myWindowsController.mainView;
	}
	
	[fastWTWindowsController.fastWTView cleanscreen];
	[fastWTWindowsController.fastWTView setTag:_bsFlag];//设置买入还是卖出
	if (_bsFlag ==0) {
		[[fastWTWindowsController window] setTitle:@"闪电买入"];
	}
	else {
		[[fastWTWindowsController window] setTitle:@"闪电卖出"];
	}

	
	if ([_gpcode length] > 0) {
		[[fastWTWindowsController.fastWTView.gpcodeText cell] setTitle:_gpcode];
	}
	if ([_gpPrice length] > 0) {
		[[fastWTWindowsController.fastWTView.gppriceText cell] setTitle:_gpPrice];
	}
	
	if (modalFastWTSession == nil) {
		modalFastWTSession = [NSApp beginModalSessionForWindow:[fastWTWindowsController window]];
	}
	[fastWTWindowsController.fastWTView onviewWillAppear];
	
}

-(void)closeSysStat{
	[NSApp endSheet:[sysStatWindowsController window] returnCode:NSOKButton];
}

-(void)closeSysConfig{
	[NSApp endSheet:[sysConfigWindowsController window] returnCode:NSOKButton];
}

-(void)logoutTrade{
	[myWindowsController.mainView closeButtonClick];
}

-(IBAction)sysConfig:(id)sender{
	if (myWindowsController == nil) {
		[NSApp beginSheet:[sysConfigWindowsController window] modalForWindow:[loginWindowsController window] modalDelegate:self didEndSelector:@selector(saveSheetDidEnd:returnCode:contextInfo:) contextInfo:NULL];
		
	}
	else {
		[NSApp beginSheet:[sysConfigWindowsController window] modalForWindow:[myWindowsController window] modalDelegate:self didEndSelector:@selector(saveSheetDidEnd:returnCode:contextInfo:) contextInfo:NULL];
		
	}
	
	[sysConfigWindowsController.mainView showInfo];
}

-(IBAction)sysPara:(id)sender{
	if (myWindowsController == nil) {
		[NSApp beginSheet:[sysStatWindowsController window] modalForWindow:[loginWindowsController window] modalDelegate:self didEndSelector:@selector(saveSheetDidEnd:returnCode:contextInfo:) contextInfo:NULL];
		
	}
	else {
		[NSApp beginSheet:[sysStatWindowsController window] modalForWindow:[myWindowsController window] modalDelegate:self didEndSelector:@selector(saveSheetDidEnd:returnCode:contextInfo:) contextInfo:NULL];

	}
	[sysStatWindowsController.mainView.myTableView reloadData];
}

- (void) saveSheetDidEnd: (NSWindow *) sheet
              returnCode: (int) returnCode
             contextInfo: (void *) contextInfo
{
    if (returnCode == NSOKButton) {
        // …
    } else if (returnCode == NSCancelButton) {
        // …
    } else {
        // …
    }
	
    [sheet close];
	
}

-(void) dealloc{
	[window release];
	[super dealloc];
}

@end

