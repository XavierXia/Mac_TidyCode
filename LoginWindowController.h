//
//  LoginWindowController.h
//  tdxMac
//
//  Created by tdx on 11-10-8.
//  Copyright 2011 武汉. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "EGetData.h"
#import "EULogin.h"
#import "Delegate.h"

@interface LoginWindowController : NSWindowController<NSWindowDelegate> {
	EGetData * mainGetdata;
	
	EULogin * mainView;
	
	id <showBodyDelegate> showDelegate;
}
@property(nonatomic, assign) id <showBodyDelegate> showDelegate;
@property(nonatomic,retain) EULogin * mainView;

-(id)initWithMyWindow:(NSWindow *)window  eGetData:(EGetData *)_eGetData;
-(void)initPara;

@end
