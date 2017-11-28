//
//  iTableColumnHeaderCell.h
//  iTableColumnHeader
//
//  Created by Matt Gemmell on Thu Feb 05 2004.
//  <http://iratescotsman.com/>
//

#import <Cocoa/Cocoa.h>


@interface iTableColumnHeaderCell : NSTableHeaderCell {
    NSImage *metalBg;
	NSImage *sortTip;
    NSMutableDictionary *attrs;
}

@end
