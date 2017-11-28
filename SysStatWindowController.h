//
//  SysStatWindowController.h
//  tdxMac
//
//  Created by tdx on 11-12-13.
//  Copyright 2011 武汉. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "EGetData.h"
#import "EUSysStat.h"

@interface SysStatWindowController : NSWindowController<NSWindowDelegate> {
	EGetData * mainGetdata;
	
	EUSysStat * mainView;
	
	id <showBodyDelegate> showDelegate;
	
}


@property (nonatomic,retain) EUSysStat * mainView;
@property(nonatomic, assign) id <showBodyDelegate> showDelegate;


-(id)initWithMyWindow:(NSWindow *)window  eGetData:(EGetData *)_eGetData;
-(void)initPara;
@end
