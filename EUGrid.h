//
//  EUGrid.h
//  tdxMac
//
//  Created by tdx on 11-8-16.
//  Copyright 2011 武汉. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "EUBase.h"
//#import "StockArray.h"
#import "iTableColumnHeaderCell.h"
#import "EuTableView.h"

@interface EUGrid : EUBase <NSTableViewDelegate,NSTableViewDataSource,NSAlertDelegate,MouseDelegate>{
	GridInfo * gridInfo;

	
	NSMutableArray * gridArray;
	
	NSArray * titleArray;
	NSArray * widthArray;
	NSArray * identifierArray;
	
	NSScrollView *scrollView;
	EuTableView			*tableView;
	NSTableColumn * lastColumn;
	int selectIndex;
	int totalNum;
	int drawNum;
	
	NSScrollView *fixScrollView;
	EuTableView	 *fixTableView;
	
	NSRect viewRect;
	
	NSButton * AGButton;
	NSButton * BGButton;
	NSButton * ZXButton;
	NSButton * CYButton;
	NSButton * ZXGButton;
	NSPopUpButton * sortButton;
	
	int oriColumnIndex;
	int desColumnIndex;
	
	BOOL moveFlag;
    int  m_nzxgcount;
   
}

@property (nonatomic,retain) GridInfo * gridInfo;
@property (nonatomic,retain) NSMutableArray * gridArray;
@property (nonatomic,retain) NSTableView			*tableView;
@property (nonatomic,retain) NSScrollView *scrollView;

-(void)clearAllButton;
-(void) setFrame:(NSRect)frameRect;
- (void)getTheData:(int)_domain theColtype:(int)_coltype;
- (void)addColumn:(NSString*)newid withTitle:(NSString*)title withWidth:(int)_width;
- (void)addColumnEx:(NSString*)newid withTitle:(NSString*)title withWidth:(int)_width;
-(void)dealTheColSort: (NSTableColumn *)theColumn;
-(void)addZixuan;
-(void)delZixuan;
-(void)handleResult:(NSAlert *)alert withResult:(NSInteger)result;
-(void)showNextPage;
-(void)showPrePage;
-(BOOL)isInGridArray:(NSString *)_gpcode gpSetcode:(int)_setcode;
-(SinHqInfo *)nextInGridArray:(NSString *)_gpcode gpSetcode:(int)_setcode;
-(SinHqInfo *)preInGridArray:(NSString *)_gpcode gpSetcode:(int)_setcode;
-(void)dealRightMenu;
- (void)refreshTheData;
@end
