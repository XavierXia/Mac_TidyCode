//
//  EUSysStat.h
//  tdxMac
//
//  Created by tdx on 11-12-13.
//  Copyright 2011 武汉. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "EUBase.h"
#import "iTableColumnHeaderCell.h"

@interface EUSysStat : EUBase <NSTableViewDelegate,NSTableViewDataSource>{
	NSTableView * myTableView;
	NSScrollView * scrollView;
	
	NSButton * cancelButton;
	
	id <showBodyDelegate> showDelegate;
	NSMutableArray * titleArray;
}

@property(nonatomic, assign) id <showBodyDelegate> showDelegate;
@property (nonatomic,retain)  NSTableView * myTableView;

- (id)initWithData:(NSRect)aRect theData:(EGetData *)_eGetData;
- (void)addColumn:(NSString*)newid withTitle:(NSString*)title withWidth:(int)_width;
@end
