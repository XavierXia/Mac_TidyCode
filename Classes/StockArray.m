//
//  StockArray.m
//  stockSave
//
//  Created by tdx on 11-2-14.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "StockArray.h"

@implementation StockArray
@synthesize bIsEmpty,nCount,stockArray;

-(id)init
{
	self = [super init];
	if(self != nil)
	{
		stockCodeArray = [[NSMutableArray alloc] init];
		stockArray = [[NSMutableArray alloc]init];
		stockExtArray = [[NSMutableArray alloc]init];
		nCount = 0;
		bIsEmpty = YES;
		
		NSArray* pathArray = NSSearchPathForDirectoriesInDomains(NSApplicationSupportDirectory, NSUserDomainMask, YES);
		
		int pathLen = [pathArray count];
		
		NSString* filePath = nil;
		for(int i=0;i<pathLen;i++)
		{
			filePath = [pathArray objectAtIndex:i];
			
		}
		filePath = [filePath stringByAppendingString:MAC_PATHSTRING];
		
		theFilePath = [filePath retain];
		NSError * error;
		
		@try {
			[[NSFileManager defaultManager] createDirectoryAtPath:filePath withIntermediateDirectories:YES attributes:nil error:&error];
		}
		@catch (NSException * e) {
			NSLog(@"%@",[e name]);
		}
		@finally {
			;
		}
		
	}
	return self;
}

void getStockCodeAndMarketID(NSString* stockCode,NSString** code,int* nMarketID)
{
	BOOL b = YES;
	int nIndex = 0;
	for(int i=0;i<[stockCode length];i++)
	{
		unichar sz = [stockCode characterAtIndex:i];
		if(sz == '#')
		{
			nIndex = i;
			b = NO;
			break;
		}
	}
	if(b)
	{
		*nMarketID = [[stockCode substringToIndex:1] intValue];
		*code = [NSString stringWithString:[stockCode substringFromIndex:1]];
	}
	else
	{
		*nMarketID = [[stockCode substringToIndex:nIndex]intValue];
		*code = [NSString stringWithString:[stockCode substringFromIndex:nIndex + 1]];
	}
}

-(BOOL)	addStockCode:(NSString*)stockCode
{
	int nMarketID = 0;
	NSString* code = [[[NSString alloc] init]autorelease];
	getStockCodeAndMarketID(stockCode,&code,&nMarketID);
    if(code==nil || [code isEqualToString:@"null"])
        return FALSE;
	return [self addStockCode:code MarketID:nMarketID];
}

-(BOOL)addStockCode:(NSString*)stockCode MarketID:(int)marketID
{
	NSString* tempString = nil;
	if(marketID < 0)
		return NO;
	else if(marketID >=0 && marketID <=2)
	{
		tempString = [[[NSString stringWithFormat:@"%d%@",marketID,stockCode]retain]autorelease];
		[stockArray addObject:tempString];
	}
	else if(marketID >=3)
	{
		tempString = [[[NSString stringWithFormat:@"%d#%@",marketID,stockCode]retain]autorelease];
		[stockExtArray addObject:tempString];
	}
	BOOL b = YES;
	for(int i=0;i<[stockCodeArray count];i++)
	{
		if([tempString isEqualToString:[stockCodeArray objectAtIndex:i]])
			b = NO;
	}
	if(b)
	{
		[stockCodeArray addObject:tempString];
		bIsEmpty = NO;
		return YES;
	}
	return NO;
}

-(void)dealloc
{
	[stockCodeArray release];
	[stockArray release];
	[stockExtArray release];
	[super dealloc];
}

-(BOOL) isEmpty
{
	return [stockCodeArray count] > 0;
}

-(BOOL) setObjectFrom:(int)IndexR To:(int)IndexD
{
	
	if(IndexR < [stockCodeArray count] && IndexD < [stockCodeArray count] && IndexD >=0 && IndexR >= 0 && IndexD != IndexR)
	{
		NSString* tempString = [[stockCodeArray objectAtIndex:IndexR]retain];
		[stockCodeArray removeObjectAtIndex:IndexR];
		[stockCodeArray insertObject:tempString atIndex:IndexD];
		[tempString release];
		tempString = nil;
		return YES;
	}
	else
		return NO;
}

-(BOOL) deleteObjectWithIndex:(int)Index
{
	if(Index >=0 && Index < [stockCodeArray count])
	{
		[stockCodeArray removeObjectAtIndex:Index];
		nCount = [stockCodeArray count];
		if([stockCodeArray count] > 0)
			bIsEmpty = NO;
		else
			bIsEmpty = YES;
		return YES;
	}
	else
		return NO;
		
}

-(BOOL) deleteObject:(NSString*)stockCode
{
	for(int i=0;i<[stockCodeArray count];i++)
	{
		if([stockCode isEqualToString:[stockCodeArray objectAtIndex:i]])
		{
			[stockCodeArray removeObjectAtIndex:i];
			nCount = [stockCodeArray count];
			if([stockCodeArray count] > 0)
				bIsEmpty = NO;
			else
				bIsEmpty = YES;
			return YES;			
		}
	}
	return NO;
}

-(BOOL) saveData
{

	NSString* myFileName = [theFilePath stringByAppendingPathComponent:@"ZXG.rtf"];
	
	[NSKeyedArchiver archiveRootObject:stockCodeArray toFile:myFileName];
	
	return YES;
}

-(NSArray*) readData
{	
	NSString* myFileName = [theFilePath stringByAppendingPathComponent:@"ZXG.rtf"];
	NSArray* tempArray = [NSKeyedUnarchiver unarchiveObjectWithFile:myFileName];
	nCount = [tempArray count];
    [stockCodeArray removeAllObjects];
    [stockArray removeAllObjects];
    [stockExtArray removeAllObjects];
	if(nCount >0){
		for(int i=0;i<[tempArray count];i++)
			[self addStockCode:[tempArray objectAtIndex:i]];
	}
	else {
		[self saveData];
		nCount= 0;
	}
	return tempArray;
}

-(NSDictionary*) getStockCodeString
{
	NSString* tempString;
	NSMutableData* newData = [[NSMutableData alloc]init];
	for(int i=0;i<[stockArray count];i++)
	{
		tempString = [NSString stringWithString:[stockArray objectAtIndex:i]];
		[newData appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	}
	NSString* tempString1 = [[[NSString alloc] initWithData:newData encoding:NSUTF8StringEncoding]autorelease];
	[newData release];
	newData = nil;
	newData = [[NSMutableData alloc]init];
	for(int i=0;i<[stockExtArray count];i++)
	{
		tempString = [NSString stringWithString:[stockExtArray objectAtIndex:i]];
		[newData appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	}
	NSString* tempString2 = [[[NSString alloc] initWithData:newData encoding:NSUTF8StringEncoding]autorelease];
	[newData release];
	newData = nil;
	NSDictionary* stockdic = [[[NSDictionary dictionaryWithObjectsAndKeys:tempString1,@"0",tempString2,@"1",nil]retain]autorelease];
	return stockdic;
}

-(NSDictionary*) getStockCodeString2:(int)nstartxh num:(int)nwantnum
{
	NSString* tempString;
	NSMutableData* newData = [[NSMutableData alloc]init];
	for(int i=nstartxh,j=0;i<[stockArray count] && j<nwantnum;i++,j++)
	{
		tempString = [NSString stringWithString:[stockArray objectAtIndex:i]];
		[newData appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	}
	NSString* tempString1 = [[[NSString alloc] initWithData:newData encoding:NSUTF8StringEncoding]autorelease];
	[newData release];
	newData = nil;
	newData = [[NSMutableData alloc]init];
	for(int i=0;i<[stockExtArray count];i++)
	{
		tempString = [NSString stringWithString:[stockExtArray objectAtIndex:i]];
		[newData appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	}
	NSString* tempString2 = [[[NSString alloc] initWithData:newData encoding:NSUTF8StringEncoding]autorelease];
	[newData release];
	newData = nil;
	NSDictionary* stockdic = [[[NSDictionary dictionaryWithObjectsAndKeys:tempString1,@"0",tempString2,@"1",nil]retain]autorelease];
	return stockdic;
}

-(NSString *)getStockCode:(int)nstartxh num:(int)nwantnum index:(int)nindex
{
    int ntmpnum=0;
    NSString* tempString;
	for(int i=nstartxh,j=0;i<[stockArray count] && j<nwantnum;i++,j++)
	{
        if(ntmpnum==nindex)
        {
            tempString = [NSString stringWithString:[stockArray objectAtIndex:i]];
            return tempString;
        }
		ntmpnum++;
	}
	for(int i=0;i<[stockExtArray count];i++)
	{
        if(ntmpnum==nindex)
        {
            tempString = [NSString stringWithString:[stockExtArray objectAtIndex:i]];
            return tempString;
        }
		ntmpnum++;
    }
	return @"";
}

-(BOOL) initWithTheArray:(NSArray*)array
{
	[stockArray removeAllObjects];
	[stockExtArray removeAllObjects];
	[stockCodeArray removeAllObjects];
	for(int i=0;i<[array count];i++)
		[self addStockCode:[array objectAtIndex:i]];
	return YES;
}

-(BOOL) stockInArray:(int)marketID StockCode:(NSString*)stockCode
{
	BOOL b = NO;
	if([stockCodeArray count] == 0)
		[self readData];
	NSString* tempCode = nil;
	if(marketID <= 1)
		tempCode = [[[NSString alloc] initWithFormat:@"%i%@",marketID,stockCode]autorelease];
	else
		tempCode = [[[NSString alloc] initWithFormat:@"%i#%@",marketID,stockCode]autorelease];
	for(int i=0;i<[stockCodeArray count];i++)
	{
		if([tempCode isEqualToString:[stockCodeArray objectAtIndex:i]])
		{
			b = YES;
			break;
		}
	}
	
	return b;
}

@end
