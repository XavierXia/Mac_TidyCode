//
//  EuTableView.m
//  国海证券网上交易
//
//  Created by szk on 13-11-8.
//
//

#import "EuTableView.h"

@implementation EuTableView

@synthesize m_delegate;

- (id)initWithFrame:(NSRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        m_bbusy=NO;
    }
    return self;
}

- (void)drawRect:(NSRect)dirtyRect
{
	[super drawRect:dirtyRect];
}

-(void) scrollWheel:(NSEvent *)theEvent{
	
    if(m_bbusy)
        return;
    m_bbusy=YES;
    CGFloat ndelta=theEvent.deltaY;
    if(ndelta>0.5)
        [m_delegate OnMouseWheel:NO];
    else if(ndelta<-0.5)
        [m_delegate OnMouseWheel:YES];
    m_bbusy=NO;
}
@end
