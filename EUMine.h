//
//  EUMine.h
//  ghzq_macosx
//
//  Created by tdx on 12-5-15.
//  Copyright 2012 武汉. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "EUBase.h"
#import "CustonTextView.h"


@interface EUMine : EUBase<getFocusDelegate> {
	NSRect viewRect;
	NSMutableArray * titleInfoArray;
	
	CustonTextView * textView;
	NSString * textValue;
	int selectIndex;
}

@end
