//
//  EULogin.h
//  tdxMac
//
//  Created by tdx on 11-10-9.
//  Copyright 2011 武汉. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "EUBase.h"
#import "jyconfig.h"
#import "CustomCellBackground.h"
#import "customTextFieldFormatter.h"
#import "CustonTextField.h"
#import "CustomSecureTextField.h"
#import "CustonComboBox.h"
#import "TdxT2EEEx.h"


@interface EULogin : EUBase <NSComboBoxDelegate,NSComboBoxDataSource,asynclogindelegate,NSTextFieldDelegate,getFocusDelegate,NSAlertDelegate,jyLogindelegate,SSLDelegate>{
	NSButton * hqButton;
	NSButton *txSetButton;
	
	NSTextField * loginTypeLabel;
	NSTextField * showTips;
	
	Yybs *m_pyyb;
	LoginMode *m_ploginmode;
	SecureMode  *m_psecuremode;
	
	LoginSet *m_ploginset;
	
	id <showBodyDelegate> showDelegate;
	
	NSBox * tradeBox;
	NSView * tradeBoxView;
	
	NSComboBox * zhlx_Combobox;
	NSComboBox * yyb_Combobox;
	CustonComboBox * account_Combobox;
	NSComboBox * aqfs_Combobox;
	
	NSButton * saveAccount;
	
	CustomSecureTextField * password_Text;
	CustonTextField * yz_Text;
	CustonTextField * authpass_Text;
	CustomCellBackground  *m_yzmview;
	
	NSButton * doneButton;
	NSButton * cancelButton;
    NSButton * tradeButtonnew;
	
	BOOL m_bLoginFlag;
	BOOL  m_bbusy;
	int  m_nfirstindex;
	int  m_ncurindex;
	BOOL loginType;
	BOOL initHQFlag;
	BOOL initJYFlag;
	BOOL alertFlag;
	BOOL bshowFlag;
	customTextFieldFormatter *formatter,*formatter1;
	int  nyybindex;
	NSRect boxRect;
    
    TdxT2EEEx  *m_t2ee;
}
@property(nonatomic, assign) id <showBodyDelegate> showDelegate;
@property BOOL loginType;
@property BOOL bshowFlag;

-(void)getBaseInfo;
-(void)getSoftVerInfo;
-(void)InitLoginset;
-(void)onViewWillAppear;
-(BOOL)IsCanQueryOther;
-(void)doasynclogin;
-(BOOL)doLogin;
-(void)doAfterLoginFailed;
-(void)doasynclogin2;
-(void)doasynclogin4;
-(void)dologinsuccess;
-(void)doneButtonClick;
-(void)enableAllButton;
-(void)disableAllbutton;
-(void)handleResult:(NSAlert *)alert withResult:(NSInteger)result withTag:(int)_tag;
-(int)SetVirtualYybID;
-(void)initT2ee;
-(void)OnSaveZhClick;
@end
