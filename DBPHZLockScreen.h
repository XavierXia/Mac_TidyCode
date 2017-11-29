//
//  DBPHZLockScreen.h
//  tdxMac
//
//  Created by xiawenxing on 16-09-06.
//  Copyright 2017 武汉. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "EUBase.h"
#import "CustomSecureTextField.h"
#import "Delegate.h"

@interface DBPHZLockScreen : EUBase <getFocusDelegate,NSAlertDelegate,BodyDelegate>{
	BOOL m_bfirstflag;
	CGFloat m_width,m_height;
	id <TradeDelegate> tradeDelegate;
	
    NSTextField * ptGDDMText;
    NSTextField* nameLabel1;
    NSTextField* nameLabel2;
	CustomSecureTextField * passwordText;
	
	NSButton * doneButton;
	NSButton * cancelButton;
	NSButton * closeButton;
    int nerrornum;
}

@property(nonatomic, assign) id <TradeDelegate> tradeDelegate;
@property (readwrite, retain) NSTextField * ptGDDMText;

-(void) setFrame:(NSRect)frame;
-(void)unlock;
-(void)quitjy;
-(void)onCancel;
-(void)SetPassFocus;
-(void)handleResult:(NSAlert *)alert withResult:(NSInteger)result withTag:(int)_tag;
-(void) doneButtonClick;
- (void)onviewWillAppear;
@end
