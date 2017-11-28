//
//  DataTickComponent.h
//  tdxIpad
//
//  Created by tdx on 10-12-31.
//  Copyright 2010 武汉. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "EUBase.h"
#import "iTableColumnHeaderCell.h"

@interface DataTickComponent : EUBase<NSTableViewDelegate,NSTableViewDataSource>{
	NSTableView * myTableView;
    NSScrollView * tableContainer;
	NSView * scrollView;
	NSMutableArray  * m_tickData;
	BOOL zsFlag;
	int dataPre;
	float closep;
	BOOL showFlag;
	int tapCount;
	id<TickDelegate> myDelegate;
	
	int showNum;
	int startNum;
}

@property BOOL zsFlag;
@property BOOL showFlag;
@property int dataPre;
@property float closep;
@property int showNum;
@property (nonatomic,retain) NSMutableArray  * m_tickData;
@property (nonatomic,retain) NSTableView * myTableView;
@property(nonatomic,assign) id<TickDelegate> myDelegate;

- (id)initWithData:(NSRect)aRect theData:(EGetData *)_eGetData;
-(void)showTable:(NSMutableArray *)ansArray;
-(void) setFrame:(NSRect)aRect;
-(NSString *)getTimeFromMinute:(int)min;
-(void) setFrame:(NSRect)aRect;
- (void)addColumn:(NSString*)newid withTitle:(NSString*)title withWidth:(int)_width;
@end
