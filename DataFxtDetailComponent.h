//
//  DataFxtDetailComponent.h
//  tdxMac
//
//  Created by tdx on 11-12-2.
//  Copyright 2011 武汉. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "EUBase.h"

@interface DataFxtDetailComponent : NSView {
	Analyse_Unit * analyseInfo;
	Analyse_Unit * analyseInfoEx;
	NSMutableArray * titleArray;
	
	SinHqInfo * currInfo;
	int showType;
}

@property(nonatomic,retain) Analyse_Unit * analyseInfo;

-(NSMutableDictionary *)getAttributes:(NSString *)_fontName fontSize:(CGFloat)_fontSize theColor:(NSColor *)_theColor theAliment:(int)_theAliment;
-(void)setCurrInfo:(SinHqInfo *)_currInfo;
-(void)setShowType:(int)_showType;
-(void)showDetail:(Analyse_Unit *)_analyseInfo preInfo:(Analyse_Unit *)_analyseInfoEx;
-(NSString *)getTimeFromMinute:(int)min;
-(NSString *)getDateFromMinute:(int)date theType:(int)_type;
@end
