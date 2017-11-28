//
//  ETradeWTCancelView.h
//  tdxMac
//
//  Created by tdx on 11-10-29.
//  Copyright 2011 武汉. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "EUBase.h"
#import "ETradeFuncBarView.h"
#import "myTableView2.h"

@interface ETradeWTCancelView : EUBase <NSTableViewDelegate,NSTableViewDataSource,NSAlertDelegate,barViewDelegate>{
	int WTtag;
	
	BOOL m_bfirstviewflag;
	short pageIndex;
	short nmaxpage;
	long  ntotalline;
	
	NSString *m_positionstr;
	int     m_ncdflag;
	BOOL  m_bbusy;
	int    m_ntotal,m_nsuc,m_nfail,m_ncurindex;
	NSString *m_errinfo;
	
	BOOL  m_bbarflag;
	BOOL  m_btoolbarstyle;//0--正常  1--半透明弹入弹出模式
	BOOL  m_popflag;
	BOOL m_bfirstgridtitleflag;
	int  m_gpcodeindex;
	int  m_scflagindex;
	int  m_bsflagindex;
	int  m_nzhlbindex;
	int  m_ngddmindex;
	
	int  m_jjcodeindex;
	int  m_jjgsdmindex;
	int  m_jjzhdmindex;
	int  m_wtdateindex;
	int  m_wtnumindex;
	int  m_wtvalueindex;
	int  m_wtbhindex;
	int  m_nnameindex;
	int  m_nywmcindex;
	int  m_nkkzqbhindex;
	int  m_njyjeindex;
	int  m_noccurjeindex;
	int  m_nmykkrqindex;
	int  m_nlxindex;
	int  m_nlshindex;
	int  m_nwtrqindex;
	int  m_nksrqindex;
	int  m_nzzrqindex;
	int  m_ndqtjindex;
	int  m_ntjrindex;

	BOOL m_fullScreenFlag;
	int npagemode;
	CGFloat m_nrightoffset;
	BOOL   m_bjjzndtcx;
	BOOL   m_blczndtcx;
	NSArray *m_kkzqarr;
	NSArray *m_kkweekarr;
	NSArray *m_qmtjarr;
	BOOL  m_bfirstalertflag;
	BOOL baddflag;
	int  m_ncancelIndex;
	BOOL   m_bdrwtcx;
    int m_ncdType;
	
	NSScrollView * scrollView;
	myTableView2   * myTableView;
	NSTableHeaderView *tableHeadView;
	
	NSMutableArray * showDataArray;
	
	ETradeFuncBarView * barView;
	BOOL toolbarShowFlag;
	
	NSRect viewRect;
	
	int m_zqdmindex;
	
	NSIndexSet * multiSelectSet;
	int multiSelectCount;
}

@property(nonatomic) int WTtag;
@property BOOL toolbarShowFlag;
@property BOOL m_bdrwtcx;
@property(nonatomic) int m_ncdType;

- (id)initWithData:(NSRect)frame theData:(EGetData *)_eGetData WithTag:(int)_wtTag;
-(void) cleanscreen;
-(void) initGridFrame:(ParseRecv *)pParsers;
- (void)onviewWillAppear:(BOOL)animated;
- (void)onviewDidAppear:(BOOL)animated;
-(void)cleardsdata;
-(void)refreshpage;
-(void)previouspage;
-(void)nextpage;
-(void)refreshpage1;
-(void)previouspage1;
-(void)nextpage1;
-(void)startanimate;
-(void)stopanimate;
-(BOOL)IsCanQueryOther;
-(int)GetQueryindexFromTag;
-(void)handleResult:(NSAlert *)alert withResult:(NSInteger)result;
-(void) setFrame:(NSRect)frameRect;
-(void)dealBarView;
-(void)myWtCancel;
@end
