//
//  MyWindowController.h
//  tdxMac
//
//  Created by tdx on 11-8-16.
//  Copyright 2011 武汉. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "EUMainView.h"
#import "EGetData.h"


@interface MyWindowController : NSWindowController<NSWindowDelegate> {

	
	EGetData * mainGetdata;

	
	EUMainView * mainView;
	id <showBodyDelegate> showDelegate;
	
	BOOL fullScreenFlag;
}

@property (nonatomic,retain) EGetData * mainGetdata;
@property (nonatomic,retain) EUMainView * mainView;
@property(nonatomic, assign) id <showBodyDelegate> showDelegate;


-(id)initWithMyWindow:(NSWindow *)window  eGetData:(EGetData *)_eGetData;
-(void)initPara;
-(void)dealFullScreen;
-(BOOL)getFullScreenFlag;

@end
