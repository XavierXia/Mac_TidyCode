//
//  SysConfigWindowController.h
//  tdxMac
//
//  Created by tdx on 11-12-17.
//  Copyright 2011 武汉. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "EGetData.h"
#import "EUSysConfig.h"

@interface SysConfigWindowController : NSWindowController<NSWindowDelegate> {
	EGetData * mainGetdata;
	
	EUSysConfig * mainView;
	
	id <showBodyDelegate> showDelegate;
	
}


@property (nonatomic,retain) EUSysConfig * mainView;
@property(nonatomic, assign) id <showBodyDelegate> showDelegate;


-(id)initWithMyWindow:(NSWindow *)window  eGetData:(EGetData *)_eGetData;
-(void)initPara;

@end
