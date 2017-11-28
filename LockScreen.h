//
//  LockScreen.h
//  tdxMac
//
//  Created by tdx on 11-11-8.
//  Copyright 2011 武汉. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "EUBase.h"
#import "CustomSecureTextField.h"
#import "Delegate.h"

@interface LockScreen : EUBase <getFocusDelegate,NSAlertDelegate>{
	BOOL m_bfirstflag;
	CGFloat m_width,m_height;
	id <TradeDelegate> tradeDelegate;
	
	NSTextField * tipsLabel;
	CustomSecureTextField * passwordText;
	
	NSButton * doneButton;
	NSButton * cancelButton;
	NSButton * closeButton;
    int nerrornum;
}

@property(nonatomic, assign) id <TradeDelegate> tradeDelegate;

-(void) setFrame:(NSRect)frame;
-(void)unlock;
-(void)quitjy;
-(void)onCancel;
-(void)SetPassFocus;
-(void)handleResult:(NSAlert *)alert withResult:(NSInteger)result withTag:(int)_tag;
-(void) doneButtonClick;
- (void)onviewWillAppear;
@end
