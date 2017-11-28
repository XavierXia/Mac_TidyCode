//
//  EUKey.h
//  tdxMac
//
//  Created by tdx on 11-9-15.
//  Copyright 2011 武汉. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "EUBase.h"
#import "iTableColumnHeaderCell.h"

@interface EUKey : EUBase <NSTableViewDelegate,NSTableViewDataSource>{
	NSTableView * myTableView;
	NSMutableArray  * m_keyData;
	NSTextField * myTextField;
	
	int selectIndex;
}

@property (nonatomic,retain) NSMutableArray  * m_keyData;
@property (nonatomic,retain) NSTableView * myTableView;
@property (nonatomic,retain) NSTextField * myTextField;
@property int selectIndex;

- (void)addColumn:(NSString*)newid withTitle:(NSString*)title withWidth:(int)_width;
-(void)searchTheStock;

@end
