//
//  EuTableView.h
//  国海证券网上交易
//
//  Created by szk on 13-11-8.
//
//

#import <Cocoa/Cocoa.h>
#import "Delegate.h"
@interface EuTableView : NSTableView
{
    id<MouseDelegate> m_delegate;
    BOOL m_bbusy;
}
@property(nonatomic,assign) id<MouseDelegate> m_delegate;
@end
