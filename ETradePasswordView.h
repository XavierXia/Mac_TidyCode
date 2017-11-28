//
//  ETradePasswordView.h
//  zszq_macosx
//
//  Created by tdx on 11-12-22.
//  Copyright 2011 武汉. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "EUBase.h"
#import "CustomSecureTextField.h"
#import "customTextFieldFormatter.h"

@interface ETradePasswordView : EUBase <NSTextFieldDelegate,NSAlertDelegate,getFocusDelegate,NSComboBoxDelegate,NSComboBoxDataSource>{
	NSRect viewRect;
	
	NSTextField * showTipsLabel;
	NSTextField * oldPasswordLabel;
	NSTextField * newPasswordLabel;
	NSTextField * newPasswordConfirmLabel;
    NSTextField * xzmmlxLabel;
	
	CustomSecureTextField * oldPasswordText;
	CustomSecureTextField * newPasswordText;
	CustomSecureTextField * newPasswordConfirmText;
	
    NSComboBox * xgmmxlComboBox;
    
	NSButton * doneButton;
    NSArray* m_xgmmlxArr;
    NSArray* m_xgmmlxArrDM;
	
	BOOL m_bbusy;
	BOOL alertFlag;
    int nxgmmlx;
}


-(void) setFrame:(NSRect)frameRect;
-(void)onviewWillAppear;
-(void)cleanscreen;
-(void) doneButtonClick;
-(void)disableAllText;
-(void)enableAllText;
-(void)dealOutLook;
-(void)startanimate;
-(void)stopanimate;
-(BOOL)IsCanQueryOther;
-(void)doXGMM;
-(void)doXGMM1;

-(void)handleResult:(NSAlert *)alert withResult:(NSInteger)result withTag:(int)_tag;
@end
