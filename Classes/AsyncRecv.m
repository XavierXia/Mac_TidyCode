//
//  AsyncRecv.m
//  tdxiphone
//
//  Created by tdx on 11-3-28.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "AsyncRecv.h"
#import "EUBase.h"

@implementation AsyncRecver

-(id)init
{
	self=[super init];
	if (self) 
	{
		winobjs=[[NSMutableDictionary alloc] initWithCapacity:100];
		winlock=[NSLock new];
		objIndex=1;
	}
	return self;
}

-(void)dealloc
{
	[winlock lock];
	[winobjs	removeAllObjects];
	[winobjs release];
	[winlock unlock];
	[winlock release];
	[super dealloc];
}

-(int)SetWinobjs:(id)pwind
{
	[winlock lock];
	int nindex=objIndex;
	[winobjs setObject:pwind forKey:[NSString stringWithFormat:@"%i",nindex]];
	objIndex++;
	[winlock unlock];
	
	return nindex;
}

-(BOOL)OnReceive:(int)nobjIndex reqid:(int)reqIndex parser:(ParseRecv *)pParse
{
	[winlock lock];
	id pwind=[winobjs objectForKey:[NSString stringWithFormat:@"%i",nobjIndex]];
	[winlock unlock];
	if(pwind)
	{
		[(NSObject *)pwind OnReceiveData:reqIndex parser:pParse];
	}
	return YES;
}

-(BOOL)OnReceive:(int)nobjIndex reqid:(int)reqIndex assID:(int)_assID hqResult:(HqResultData *)_hqResult
{
	[winlock lock];
	id pwind=[winobjs objectForKey:[NSString stringWithFormat:@"%i",nobjIndex]];
	[winlock unlock];
	if(pwind)
	{
		[(EUBase *)pwind OnReceiveData:reqIndex FuncID:_assID HqResult:_hqResult];
	}
	return YES;
}
@end
