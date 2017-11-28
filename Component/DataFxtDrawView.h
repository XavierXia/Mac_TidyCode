//
//  DataFxtDrawView.h
//  IpadForTDX
//
//  Created by tdx on 11-5-11.
//  Copyright 2011 武汉. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "struct.h"

@interface DataFxtDrawView : NSView {
	CGContextRef m_context;
	id m_pparent;
	BOOL dataFlag;
}

@property(nonatomic,assign) id m_pparent;
@property BOOL dataFlag;

-(CGContextRef)getTheViewContext;
-(void)drawTheView;
-(void) drawKLine:(CGContextRef)context;
-(void) drawZb:(CGContextRef)context;
-(void)drawVol:(CGContextRef)context;
-(float)getYPos:(float)_value secNum:(int)secNum;
-(float)getZBYPos:(float)_value secNum:(int)secNum;
-(void) drawBARLine:(CGContextRef)context;
@end
