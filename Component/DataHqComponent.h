//
//  DataHqComponent.h
//  tdxiphone
//
//  Created by 魏 文敏 on 09-12-30.
//  Copyright 2009 武汉. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "EUBase.h"
#import "iTableColumnHeaderCell.h"
#import "CustonTableView.h"
@interface DataHqComponent : EUBase <NSTableViewDelegate,NSTableViewDataSource,getTableClickDelegate>{
	CustonTableView * myTableView;
	NSTableView * myTableViewforZS;
	NSMutableArray * titleArray;
	NSMutableArray * zsTitleArray;
	NSMutableArray * zsCellArray;
	BOOL showFlag;
	BOOL addFlag;
	SinHqInfo * currInfo;
	NSRect viewRect;
	int selectIndex;
	
	id <FastWTDelegate> myDelegate;
	id <OperZXGDelegate> zxgDelegate;
	NSMenu * hqMenu;
}

@property BOOL showFlag;
@property (nonatomic,retain) NSTableView * myTableView;
@property (nonatomic,retain) NSMutableArray * titleArray;
@property (nonatomic,retain) NSMutableArray * zsTitleArray;
@property (nonatomic,retain) SinHqInfo * currInfo;
@property(nonatomic, assign) id <FastWTDelegate> myDelegate;
@property(nonatomic, assign) id <OperZXGDelegate> zxgDelegate;
- (id)initWithData:(NSRect)aRect theData:(EGetData *)_eGetData;
-(void)layoutLabel;
-(void)showBase:(SinHqInfo *) hqInfo;
-(void)showTable;
-(void)dealTheZS;

-(void)checkIsInZXG;
-(void)checkIsInZXGAfterDelete:(NSString *)_gpcode theSetcode:(int)_setcode;
- (void)addColumn:(NSString*)newid withTitle:(NSString*)title withWidth:(int)_width;
- (void)addColumnEx:(NSString*)newid withTitle:(NSString*)title withWidth:(int)_width;

@end
