//
//  FastTradeWTWindowController.h
//  tdxMac
//
//  Created by tdx on 11-11-26.
//  Copyright 2011 武汉. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "EGetData.h"
#import "ETradeWTView.h"

@interface FastTradeWTWindowController : NSWindowController<NSWindowDelegate> {
	EGetData * mainGetdata;
	ETradeWTView * fastWTView;
	
	id <showBodyDelegate> showDelegate;
}

@property(nonatomic,retain) ETradeWTView * fastWTView;
@property(nonatomic, assign) id <showBodyDelegate> showDelegate;

-(id)initWithMyWindow:(NSWindow *)window  eGetData:(EGetData *)_eGetData;
@end
