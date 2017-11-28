//
//  CustonTableView.h
//  tdxMac
//
//  Created by tdx on 11-12-5.
//  Copyright 2011 武汉. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "Delegate.h"

@interface CustonTableView : NSTableView {
	id <getTableClickDelegate> clickDelegate;
}
@property(nonatomic, assign) id <getTableClickDelegate> clickDelegate;
@end
