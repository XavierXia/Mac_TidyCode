//
//  DataDetailComponent.h
//  tdxMac
//
//  Created by tdx on 11-9-17.
//  Copyright 2011 武汉. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "EUBase.h"

@interface DataDetailComponent : NSView {
	Minute_Unit * minuteInfo;
	NSMutableArray * titleArray;
	
	BOOL zsflag;
	int dataPre;
	float closep;
}

-(void)showDetail:(Minute_Unit *)_minuteInfo zsFlag:(BOOL)_zsflag dataPre:(int)_datapre closeP:(float)_closep;
-(NSMutableDictionary *)getAttributes:(NSString *)_fontName fontSize:(CGFloat)_fontSize theColor:(NSColor *)_theColor theAliment:(int)_theAliment;
-(NSString *)getTimeFromMinute:(int)min;
@end
