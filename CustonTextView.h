//
//  CustonTextView.h
//  tdxMac
//
//  Created by tdx on 11-12-16.
//  Copyright 2011 武汉. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "Delegate.h"

@interface CustonTextView : NSTextView {
	id <getFocusDelegate> focusDelegate;
}
@property(nonatomic, assign) id <getFocusDelegate> focusDelegate;
@end
