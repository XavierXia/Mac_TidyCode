//
//  ETradeFuncListView.h
//  tdxMac
//
//  Created by tdx on 11-10-25.
//  Copyright 2011 武汉. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "EUBase.h"
#import "Node.h"
#import "ImageAndTextCell.h"

@interface ETradeFuncListView : EUBase <NSOutlineViewDataSource,NSOutlineViewDelegate>{
	NSSegmentedControl * segment;
	
	NSArray * funcInfoArray;
	NSArray * serviceInfoArray;
	NSOutlineView * funcList;
	
	Node *rootNode;
	Node *serviceNode;
	BOOL clickFlag;
    NSRect viewRect;
    NSScrollView * scrollView;

}

@property (readwrite, retain) NSOutlineView * funcList;
@property (readwrite, retain) NSScrollView * scrollView;

-(void)dealSelect:(int)_type ParaOne:(int)_para;
@end
