//
//  ETradeUserInfoView.h
//  tdxMac
//
//  Created by tdx on 11-10-28.
//  Copyright 2011 武汉. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "EUBase.h"
#import "ETradeFuncBarView.h"
#import "myTableView2.h"

@interface ETradeUserInfoView : EUBase <NSTableViewDelegate,NSTableViewDataSource,barViewDelegate>{
	int WTtag;
	int tag;
	
	int nDate;
	BOOL isOK;

	short pageIndex;
	short nmaxpage;
	long  ntotalline;
	BOOL  bdateflag;
	BOOL m_bfirstviewflag;
	NSString *m_positionstr;
	int  nsetcode;
	BOOL  m_bbusy;
	BOOL  m_bbarflag;
	BOOL  m_btoolbarstyle;//0--正常  1--半透明弹入弹出模式
	BOOL  m_popflag;
	
	Yhxxmx *m_pyhmx;
	BOOL byhflag;
	int  actionIndex;
	int nSelectyhIndex;
	BOOL m_bfirstgridtitleflag;
	
	int  m_zqdmindex;
	
	BOOL m_fullScreenFlag;
	int  npagemode;
	BOOL baddflag;
	BOOL m_bleftarrowflag;
	
	BOOL bfirstflag;
	
	NSScrollView * scrollView;
	myTableView2 * myTableView;
	NSTableHeaderView *tableHeadView;
	
	ETradeFuncBarView * barView;
	
	NSMutableArray * showDataArray;
	
	BOOL toolbarShowFlag;
	
	NSRect viewRect;
	
    signed char m_bdoubleclickflag;
	NSMenu * rightMenu;
}
@property int tag;
@property BOOL toolbarShowFlag;

- (id)initWithData:(NSRect)frame theData:(EGetData *)_eGetData WithTag:(int)_wtTag;
-(void)initRightMenu;
-(id) setFrame:(NSRect)frameRect;
- (void)onviewDidAppear:(BOOL)animated;
-(void)cleardsdata;
-(void)QueryGddm;
-(void)showGddm;
-(void)QueryJjgs;
-(void)showJjgs;
-(void)QueryJjzh;
-(void)showJjzh;
-(void)QueryJjdm;
-(void)showJjdm;
-(void)QueryLcdm;
-(void)showLcdm;
-(void)QueryLcgs;
-(void)showLcgs;
-(void)QueryLczh;
-(void)showLczh;
-(BOOL)QueryCache:(int)queryindex;
-(BOOL)showCache:(int)queryindex;
-(void)InitControl;
-(int)GetQueryindexFromTag:(int)ntag;
-(void)refreshpage;
-(void)refreshpage1;
-(void)refreshpage2;
-(void)startanimate;
-(void)stopanimate;
-(BOOL)IsCanQueryOther;
-(void)dealBarView;
-(void)resetToolbar;
-(BOOL)IsLscx;
-(BOOL)IsYhCombo;
-(void) refreshpageWithDate;
@end
