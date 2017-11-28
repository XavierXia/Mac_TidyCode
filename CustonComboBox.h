//
//  CustonComboBox.h
//  tdxMac
//
//  Created by tdx on 11-11-2.
//  Copyright 2011 武汉. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "Delegate.h"

@interface CustonComboBox : NSComboBox {
	id <getFocusDelegate> focusDelegate;
}
@property(nonatomic, assign) id <getFocusDelegate> focusDelegate;
@end
