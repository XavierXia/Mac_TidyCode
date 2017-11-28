//
//  Delegate.h
//  IpadForTDX
//
//  Created by tdx on 11-2-23.
//  Copyright 2011 武汉. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "jyconfig.h"
#import "struct.h"




@protocol DataZXGDelegate;
@protocol OperZXGDelegate;

@protocol DataZXGDelegate <NSObject>

- (void)showStockDetail:(NSString *)gpcode setcode:(int)_setcode;
- (void)showStockDetailWithReload:(NSString *)gpcode setcode:(int)_setcode;
- (void)showStockDetailWithKey:(NSString *)gpcode setcode:(int)_setcode;
- (void)showInfoDetail:(NSString *)_href;
- (void)setStockInfo:(NSString *)gpcode setcode:(int)_setcode gpName:(NSString *)_gpName;
- (void)chechStockAfterDelete:(NSString *)_gpcode setcode:(int)_setcode;
- (BOOL)checkStockInHQView:(NSString *)_gpcode setcode:(int)_setcode;
@end




@protocol OperZXGDelegate <NSObject>

- (BOOL)addStock:(NSString *)gpcode setcode:(int)_setcode;
- (BOOL)stockIsIn:(NSString *)gpcode setcode:(int)_setcode;
- (BOOL)deleteStock:(NSString *)gpcode setcode:(int)_setcode;
-(NSString *)getCurrStock;
-(NSString *)getCurrStock2:(int)nstartxh num:(int)npagenum;
-(int)GetZxgNum;
-(int)GetZxgNum2;
-(void)refreshZxgData;
-(NSString *)getStockCode:(int)nstartxh num:(int)npagenum index:(int)nindex;
@end

@interface Delegate : NSObject {

}
@end


@protocol BarItemDelegate;

@protocol BarItemDelegate <NSObject>

- (void)funcItemClick:(int)_index;
@end

@protocol TradePopDelegate;

@protocol TradePopDelegate <NSObject>

-(void)cancelBtnClick;
-(void)doneBtnClick;
-(void)loginSuccess;
-(void)loginGotoTrade;
-(int)GetScreenType;
@end


@protocol TradeLoginDelegate;

@protocol TradeLoginDelegate <NSObject>

-(void)loginBtnClick;

@end


@protocol FastWTDelegate;

@protocol FastWTDelegate <NSObject>

-(void)fastWT:(int)_bsflag gpcode:(NSString *)_gpcode gpprice:(float)_gpprice;
@end

@protocol tradeCellDelegate;

@protocol tradeCellDelegate <NSObject>

- (void)showStockHq:(NSString *)_gpcode setcode:(int)_setcode;
- (void)showCell:(int)_index;
-(int)GetScreenType;
-(void)showSell:(NSString *)_gpcode;
-(void)showrmbzc;
-(void)showUserInfo1;
-(void)showWtCancel1;
@end

@protocol buttonNameModifyDelegate;

@protocol buttonNameModifyDelegate <NSObject>
-(void)setName:(NSString *)_name;
-(void)setPage:(NSString *)_page;
-(void)setStockName:(NSString *)_name;
@end


@protocol F10ViewDelegate;
@protocol F10ViewDelegate <NSObject>

- (void)f10returnViewController;
- (void)paomareturnViewController;
@end

@protocol SerivceViewDelegate;
@protocol SerivceViewDelegate <NSObject>

- (void)showService:(NSString *)_url;

@end

@protocol TradeComDelegate <NSObject>
-(void)SetCHBSessionID:(UInt64)usessionid;
@end

@protocol showDetailDelegate;
@protocol showDetailDelegate <NSObject>

- (void)showTradeDetail;

@end

@protocol gpDetailDelegate;
@protocol gpDetailDelegate <NSObject>

- (void)showGpDetail;
-(int)GetTheScreenType;
@end

@protocol showAdjacentDelegate;
@protocol showAdjacentDelegate <NSObject>

-(void)showPre:(BOOL)zxgFlag theGpCode:(NSString *)_gpcode theSetcode:(int)_setcode;
-(void)showNext:(BOOL)zxgFlag theGpCode:(NSString *)_gpcode theSetcode:(int)_setcode;
-(void)dealFullTextNav:(int)_num;

@end

@protocol DetailTickDelegate;
@protocol DetailTickDelegate<NSObject>
-(NSString *)getgpcode;
-(int)getgpsetcode;
-(BOOL)IsCurrinfoclosep;
-(BOOL)IsCurrinfogpcodenil;
-(BOOL)IsSameGpcode;
-(void)SetTickDetailInfo;
-(int)GetScreenType;
-(NSString *)getgpname;
-(void)dismissFullTick;
@end

@protocol tradeMenuDelegate;
@protocol tradeMenuDelegate <NSObject>

-(void)showTradeFunc:(int)_funcIndex theSecIndex:(int)_secIndex theRowIndex:(int)_rowIndex;
-(void)cancelButtonClick;

@end

@protocol tradeSlideDelegate;
@protocol tradeSlideDelegate <NSObject>

-(void)dealTheDirection:(int)_direction;

@end

@protocol SystemMenuDelegate;
@protocol SystemMenuDelegate <NSObject>

-(void)showSystemFunc:(int)_funcIndex ;
-(void)changeSortRefreshTimer;
-(void)lockScreen;
-(void)afterReconnRefresh;
-(void)showConnTips;
-(void)showInitConnTips;
@end

@protocol  getdataDelegate;
@protocol  getdataDelegate<NSObject>
@optional
-(TradeSite *)GetJyLoginSite:(BOOL)blastflag;
-(TradeSite *)GetHqLoginSite:(BOOL)blastflag;
-(BOOL)IsNetWorkOk;
-(BOOL)IsJyLocking;
-(void)genReloginData:(NSMutableData*)relogindata;
-(TradeSite *)getNextHqLoginSite;
-(void)dealChangeNextHqSite;
-(void)writeLog:(NSString *)_log;
-(int)getHourDiff;
-(int)getMinuteDiff;
-(int)getSecondDiff;
-(BOOL)IsHttpProxyWork;
-(NSString *)getHttpProxyAddress;
-(NSString *)getHttpProxyPort;
-(NSString *)getHttpProxyUsername;
-(NSString *)getHttpProxyPassword;
@end

@protocol jyLogindelegate;
@protocol  jyLogindelegate<NSObject>
-(void)tradeLoginTimeOut;
@end

@protocol asynclogindelegate;
@protocol  asynclogindelegate<NSObject>
-(void)DoAfterFindBest;
-(void)DoAfterFindHqBest;
@end

@protocol wreathWebDelegate;
@protocol  wreathWebDelegate<NSObject>
-(void)gotoTheWeb:(NSString *)_url;
-(void)gotoLogin;
@end


@protocol openningdelegate;
@protocol  openningdelegate<NSObject>
-(BOOL)doVersionCheck;
-(BOOL)doNetCheck;
-(BOOL)doInitPara;
-(BOOL)doHqHostFastCheck;
-(BOOL)gotoMainView;
-(BOOL)getCheckFastFlag;
-(BOOL)doHqConn;
-(NSString *)getCheckResult;
@end

@protocol RefreshDelegate;
@protocol  RefreshDelegate<NSObject>
-(BOOL)doAllRefresh;
@end

@protocol jjkhxyDelegate;
@protocol jjkhxyDelegate<NSObject>
-(void)popkhxywindow:(int)flag;
-(void)cancelkhxyBtnClick:(int)flag;
-(void)donekhxyBtnClick:(int)flag;

@end

@protocol zndtxgDelegate;
@protocol zndtxgDelegate<NSObject>

-(void)dozndtxg:(BOOL)bjjzndt jjdm:(NSString *)jjcode jjmc:(NSString *)jjname KSRQ:(NSString *)ksrq ZZRQ:(NSString *)zzrq DQRQ:(NSString *)dqrq SGJE:(NSString *)sgje TJR:(NSString *)tjr WTRQ:(NSString *)jjdtwtrq WTBH:(NSString *)jjdtwtbh LSH:(NSString *)jjdtlsh;

@end

@protocol reconnectDelegate;

@protocol reconnectDelegate<NSObject>
-(BOOL)AsyncReconnect;
-(void)stopreconnect;
@end

@protocol lockscreenDelegate;
@protocol lockscreenDelegate<NSObject>
-(void)unlockscreen;
-(void)listdismiss;
@end

@protocol TickDelegate;
@protocol TickDelegate<NSObject>
-(void)showFullTick;
@end

@protocol MineDelegate;
@protocol MineDelegate<NSObject>
-(void)showMineInfo;

@end

@protocol SwitchDelegate;
@protocol SwitchDelegate<NSObject>
-(void)showSwitchInfo:(int)_index TheTag:(int)_tag;

@end

@protocol actionDelegate;

@protocol actionDelegate<NSObject>
-(void)popupActionSheet:(CGFloat)nwidth height:(CGFloat)nheight view:(id)pobjview arrowview:(id)destview title:(NSString *)strtitle selrow:(int)nselrow tag:(int)ntag type:(int)ntype date:(NSDate *)nowdate arrowflag:(int)nflag;
-(void)dismissActionSheet:(BOOL)banimated;
@end

@protocol actionDelegate1;
@protocol actionDelegate1<NSObject>
-(void)OnActionOk:(int)ntag;
-(void)OnActionDateOk:(int)ntag date:(NSDate *)seldate;

@end


@protocol OperProcessDelegate;
@protocol OperProcessDelegate <NSObject>
-(int)getHQCurrFunc;
-(int)getTradeCurrFunc;
-(void)getHQProcess:(NSString *)_gpcode gpSetcode:(int)_setcode typeID:(int)_typeID pareOne:(int)_paraone paraTwo:(int)_paraTwo;
-(void)getKeyBoardEvent:(NSEvent *)theEvent;
-(void)getTradeProcess:(NSString *)_gpcode gpSetcode:(int)_setcode typeID:(int)_typeID pareOne:(int)_paraone paraTwo:(int)_paraTwo pareThree:(NSString *)_paraThree;
-(void)getTheTitleName:(NSString *)_titleName;
-(void)getTheGridType;

-(StockInfo *) getNextStockInfo:(NSString *)_gpcode gpSetcode:(int)_setcode;
-(StockInfo *)getPreStockInfo:(NSString *)_gpcode gpSetcode:(int)_setcode;

-(void)closeKeyBoard;
-(void)startReconnect;
@end


@protocol showBodyDelegate;
@protocol showBodyDelegate <NSObject>

-(void)dealTitleName:(NSString *)_titleName;
-(void)afterInit;
-(void)closeLogin;
-(void)closeApp;
-(void)showLogin;
-(void)afterLogin;
-(void)closeFastWTSession;
-(void)closeSession;
-(void)closeFastWT;
-(void)showFastWT:(NSString *)_gpcode bsFlag:(int)_bsFlag gpPrice:(NSString *)_gpPrice;
-(void)dealTradeMenu;
-(void)dealSortSelect:(int)_coltType sortType:(int)_sortType;
-(void)closeSysStat;
-(void)closeSysConfig;
-(void)logoutTrade;
-(void)onTeleSet;
@end

@protocol getFocusDelegate;
@protocol getFocusDelegate <NSObject>
-(void)getFocus:(int)_tag;
-(void)getEnter:(int)_tag;
-(void)getEsc:(int)_tag;
-(void)getKeyUp:(NSEvent *)theEvent;
@end

@protocol getTableClickDelegate;
@protocol getTableClickDelegate <NSObject>
-(void)getClick:(NSEvent *)theEvent;
@end


@protocol barViewDelegate;
@protocol barViewDelegate <NSObject>
-(void)getButtonClick:(int)_tag;
-(signed char)IsLscxFlag;
@end


@protocol TradeDelegate;
@protocol TradeDelegate <NSObject>
-(void)minButtonClick;
-(void)closeButtonClick;
-(void)lockButtonClick;
-(void)unlockButtonClick;
-(void)changeSizeButtonClick:(int)flag; 
@end

@protocol MouseDelegate;
@protocol MouseDelegate <NSObject>

-(void)OnMouseWheel:(BOOL)bupdownflag;

@end

@protocol SSLDelegate;
@protocol SSLDelegate <NSObject>

-(void)StartLogin:(BOOL)bsucflag;

@end

@protocol BodyDelegate;
@protocol BodyDelegate <NSObject>

-(void)OnWtSuccess;

@end
