//
//  ETradeWTView.h
//  tdxMac
//
//  Created by tdx on 11-10-26.
//  Copyright 2011 武汉. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "EUBase.h"
#import "customTextFieldFormatter.h"
#import "iTableColumnHeaderCell.h"
#import "CustonTextField.h"
#import "Delegate.h"
#import "myTableView2.h"

@interface ETradeWTView : EUBase <NSComboBoxDelegate,NSComboBoxDataSource,NSTextFieldDelegate,NSAlertDelegate,NSTableViewDelegate,NSTableViewDataSource,getFocusDelegate>{
	int showType;//是否显示盘口信息
	int textIndex;
	int wtType ; //0 普通  1闪电下单

	float leftBlankWidth;
	
	int   m_xsflag;
	BOOL  m_bfirstflag;
	int tag; //0 买入 1 卖出
	float wtPrice;
	BOOL m_bButtonshowflag;
	BOOL m_bmoveflag;
	
	int lastbsflag;
	int  ngdIndex;
	int  m_setcode;//市场
	int pickindex;
	int nselectindex;
	BOOL bpopupflag;
	BOOL btradesucflag;
	int  nlasttag;
	int   m_ngzdw;
	BOOL m_bolzq;//是否债券
	BOOL m_bzyck;//是否质押出库
	BOOL m_bzyrk;//是否质押入库
	BOOL bsdmmflag;//是否闪电买卖
	BOOL baddflag;//是否已被加载addsubview
	
	float m_nStartPosX;
	BOOL m_btouchmoved;
	BOOL  m_btitleflag;
	BOOL  m_bolhg;
	float  fztjg,fdtjg;
	int ntotalrow;
	BOOL m_bautonext;
	BOOL  m_bfirstalertflag;
	BOOL m_brefreshflag;
	int m_strMRMCFlag; //在不同的报价方式下的买入卖出标志；
	int  m_nsjfsindex;
	BOOL m_bsjwtflag,nlastsjwtflag;
	BOOL  m_bleftarrowflag;
    BOOL m_bOnlyRunOne;
	
	NSArray *m_szsjwtfsmc;
	NSArray *m_nszsjwtfsdm;
	NSArray *m_shsjwtfsmc;
	NSArray *m_nshsjwtfsdm;
	NSArray *titleLabelArray;
	
	NSComboBox * gddmCombobox;
	NSComboBox * bjfsCombobox;
	CustonTextField * gpcodeText;
	NSTextField * gpnameLabel;
	CustonTextField * gppriceText;
	NSTextField * moneynumText;
	CustonTextField * gpnumText;
	NSTextField * maxbuysellLabel;
	NSTextField * sjwtfsLabel;
	NSTextField * gpnumdwLabel;
	NSTextField * gpnumdwLabel2;
	NSTextField * xjwtLabel;
    
    CustonTextField* xjhkpriceText;
    NSTextField * kyjeLabel;
    NSTextField * xhkeLabel;
    NSTextField * sgjgLabel;
    NSTextField * sgsxLabel;
    NSTextField * sgxxLabel;
    NSTextField * kyzjLabel;
    NSButton * xhkeAllMoneyButton;
    NSButton * xgsgAllMoneyButton;
    NSStepper * xjhkpriceStepper;
	
	NSStepper * priceStepper;
	NSStepper * numStepper;
	GdmxInfo   *m_gdmx;
	
	NSButton * allnumButton;
	
	
	NSString *lastzqdm;
	NSString *lastmaxzqdm;
	NSString *lastprice;
	NSString *lastkyzj;
	
	float priceValue;
	float numValue;
    float xjhkpriceValue;
	BOOL   m_bediting;
	BOOL  m_bbusy;
	
	NSButton * doneButton;
	
	myTableView2 * myTableView;
    NSScrollView * scrollView;
	
	float currClose;
	NSMutableArray * pkTitleArray;
	NSMutableArray * pkShowArray;
    NSMutableArray * DBPHZTitleArray;
    NSMutableArray * DBPHZGDDMArray;
	
	NSRect viewRect;
    NSRect tableViewRect;
    NSView * DBPHZView; //担保品划转 View
    NSComboBox * HZFXCombobox; //划转方向
    NSArray *HZFXArray; //划转方向title
    NSComboBox * PTgddmCombobox; //普通股东
    NSComboBox * BZCombobox; //币种
    NSArray *BZArray; //币种数组
    
    NSView *XQHQView; //现券还券
    NSView *XJHKView; //现金还款
    NSView *XGSGView; //新股申购
    NSView* wtViewFrame;
	id <showBodyDelegate> showDelegate;
    id<BodyDelegate> bDelegates;
    
    int xgsgMSGS;

}

@property(nonatomic) int tag;
@property float wtPrice;
@property BOOL m_brefreshflag;
@property BOOL m_bOnlyRunOne;
@property (readwrite, retain) NSTextField * gpcodeText;
@property (readwrite, retain) NSTextField * gppriceText;
@property (readwrite, retain) NSTextField * maxbuysellLabel;
@property(nonatomic, assign) id <showBodyDelegate> showDelegate;
@property(nonatomic,assign)id<BodyDelegate> bDelegates;
@property(nonatomic,retain) NSView * DBPHZView;
@property(nonatomic,retain) NSView* XQHQView;
@property(nonatomic,retain) NSView* XJHKView;
@property(nonatomic,retain) NSView* wtViewFrame;
@property(nonatomic) int xgsgMSGS;
@property(nonatomic, retain)NSMutableArray* DBPHZGDDMArray;

- (id)initWithData:(NSRect)frame theData:(EGetData *)_eGetData showType:(int)_showType;
- (void)clearLabel;
- (void)onviewWillAppear;
-(void)QueryGpInfo;
-(void)OnGpMaxBuySell;
-(void)cleanscreen;
-(void)doBuySell;
-(void)doBuySell2;
-(void)SetGpnum:(float)frate;
-(void)AutoCheckWtsl;
-(void)startanimate;
-(void)stopanimate;
-(BOOL)IsCanQueryOther;
-(void)handleResult:(NSAlert *)alert withResult:(NSInteger)result withTag:(int)_tag;
- (void)addColumn:(NSString*)newid withTitle:(NSString*)title withWidth:(int)_width;
-(void)dealPKArray:(ParseRecv*)pParse;
-(void)dealBorS;
-(void) doneButtonClick;
-(void)refreshHqData;
-(void)dealTitleS;
-(void)getXJHKData;
-(void)getDBPHZGDDMData;

@end
