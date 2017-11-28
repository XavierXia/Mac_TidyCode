//
//  Node.m
//  OutlineViewSourceList
//
//  Created by Kevin Wojniak on 4/12/08.
//  Copyright 2008 Kainjow LLC. All rights reserved.
//

#import "Node.h"


@implementation Node

@synthesize name, children, isGroup,image,level;

- (id)init
{
	if (self = [super init])
	{
		self.name = nil;
		self.children = [NSMutableArray array];
		self.isGroup = NO;
	}
	
	return self;
}

- (void)dealloc
{
	self.name = nil;
	self.children = nil;
	self.image = nil;
	[super dealloc];
}

@end
