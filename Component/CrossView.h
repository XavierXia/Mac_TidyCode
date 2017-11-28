//
//  CrossView.h
//  tdxiphone
//
//  Created by 魏 文敏 on 10-1-5.
//  Copyright 2010 武汉. All rights reserved.
//

#import <Cocoa/Cocoa.h>


@interface CrossView : NSView {
	float xPos;
	float yPos;
	float perRowHeight;
	float viewWidth;
	float titleHeight;
	BOOL showFlag;
	int typeFlag;
	
	CGRect topRect;
	CGRect midRect;
	CGRect btmRect;
}



@property float xPos;
@property float yPos;
@property float perRowHeight;
@property float titleHeight;
@property float viewWidth;
@property BOOL showFlag;
@property int typeFlag;
@property CGRect topRect;
@property CGRect midRect;
@property CGRect btmRect;

-(void) refreshShow;
-(id)initWithFrame:(NSRect)frame PerRowHeight:(float) _height;


@end
