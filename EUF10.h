//
//  EUF10.h
//  tdxMac
//
//  Created by tdx on 11-10-22.
//  Copyright 2011 武汉. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "EUBase.h"
#import "CustonTextView.h"

@interface EUF10 : EUBase <getFocusDelegate>{
	NSRect viewRect;
	
	NSMutableArray * titleValue;
	NSMutableArray * titleArray;
	CustonTextView * textView;
	NSScrollView *scrollView;
	NSString * textValue;
	int selectIndex;
	

}

-(void)getF10Data:(NSString *)_gpcode setcode:(int)_setcode  reloadFlag:(BOOL)_reloadFlag;
-(void)layoutTitle;
-(void)dealSelectedTitleChange:(int)_index;
-(void) setFrame:(NSRect)frameRect;
@end
