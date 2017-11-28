//
//  Node.h
//  OutlineViewSourceList
//
//  Created by Kevin Wojniak on 4/12/08.
//  Copyright 2008 Kainjow LLC. All rights reserved.
//

#import <Cocoa/Cocoa.h>


@interface Node : NSObject
{
	NSString *name;
	NSMutableArray *children;
	BOOL isGroup;
	NSString * image;
	int level;
}

@property (readwrite, retain) NSString *name;
@property (readwrite, retain) NSMutableArray *children;
@property (readwrite, retain) NSString * image;
@property (readwrite) BOOL isGroup;
@property int level;

@end
