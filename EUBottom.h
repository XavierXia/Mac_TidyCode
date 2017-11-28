//
//  EUBottom.h
//  tdxMac
//
//  Created by tdx on 11-9-8.
//  Copyright 2011 武汉. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "EUBase.h"

@interface EUBottom : EUBase {
	BOOL dataFlag;
	BOOL initFlag;
	BOOL connFlag;
	NSTextField * tipField;
	
	int theRepeatCount;
}

@property int theRepeatCount;
@property BOOL initFlag;

-(void)getDpData;
-(void)showTips;
-(void)showInitTips;
-(void)showRefreshTips;
-(void)showAfterInitTips;
-(void)setTips:(NSString *)_tips;
@end
