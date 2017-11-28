//
//  EUBase.h
//  tdxMac
//
//  Created by tdx on 11-8-19.
//  Copyright 2011 武汉. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "EGetData.h"
#import "struct.h"
#import "Delegate.h"
#import "SinHqInfo.h"
@interface EUBase : NSView {
	EGetData * eGetData;
	int	   windindex;
	int    tradeindex;
	BOOL   drawFlag;
	NSString * gpcode;
	int setcode;
	id<OperProcessDelegate> operProcessDelegate;
	id<OperZXGDelegate> operZXGDelegate;
	float offset_X;
	float offset_Y;
}

@property (nonatomic, retain) EGetData * eGetData;
@property int windindex;
@property int    tradeindex;
@property BOOL   drawFlag;
@property(nonatomic, assign) id <OperProcessDelegate> operProcessDelegate;
@property(nonatomic, assign) id<OperZXGDelegate> operZXGDelegate;
@property (nonatomic, retain)NSString * gpcode;
@property int setcode;
@property float offset_X;
@property float offset_Y;

- (id)initWithData:(NSRect)frame theData:(EGetData *)_eGetData;
-(void)OnScreenSizeChange:(float)_width theHeight:(float)_height;
-(void)OnReceiveData:(int)reqIndex FuncID:(int)_funcID HqResult:(id)_hqResult;//onrecdata 获得数据处理函数
-(void)OnReceiveKeyBoardEvent:(NSEvent *)theEvent;
-(void)dealKeyBoardEvent:(NSEvent *)theEvent;
-(BOOL)OnReceiveData:(int)reqIndex parser:(id)pParse;
@end
