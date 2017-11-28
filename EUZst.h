//
//  EUZst.h
//  tdxMac
//
//  Created by tdx on 11-9-5.
//  Copyright 2011 武汉. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "EUBase.h"
#import "SinHqInfo.h"
#import "DataZstComponent.h"
#import "DataFxtComponent.h"
#import "DataHqComponent.h"
#import "DataTickComponent.h"

@interface EUZst : EUBase <DataFXTDelegate,NSAlertDelegate,MineDelegate>{
	int showFlag; // 1 分时 2 k线
	BOOL financeShowFlag; // 
	BOOL tickShowFlag;// 
	BOOL reloadFlag;

	
	NSString * gpname;
	id <OperZXGDelegate> zxgDelegate;
	
	NSRect viewRect;
	
	DataZstComponent * zst;
	DataFxtComponent * fxt;
	DataHqComponent * hq;
	DataTickComponent * tick;
	
	SinHqInfo * currInfo;
	

}
@property (nonatomic,retain)  NSString * gpname;
@property int showFlag;
@property BOOL financeShowFlag;
@property BOOL tickShowFlag;
@property BOOL reloadFlag;
@property(nonatomic, assign) id <OperZXGDelegate> zxgDelegate;
@property (nonatomic,retain)  DataZstComponent * zst;
@property (nonatomic, retain) DataFxtComponent * fxt;
@property (nonatomic,retain) DataHqComponent * hq;

-(void) setFrame:(NSRect)frameRect;
-(void)setFxtInfo:(int)_periodIndex ZBIndex:(int)_zbIndex;
-(void)showSwitchInfo:(int)_index;
-(void)setSwitchInfo:(int)_index;
-(void)getHqData:(NSString *)_gpcode setcode:(int)_setcode  reloadFlag:(BOOL)_reloadFlag;
-(void)getRefreshData;
-(void)addZixuan;
-(void)handleResult:(NSAlert *)alert withResult:(NSInteger)result;
-(void)clearScreenInInit;
@end
