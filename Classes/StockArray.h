//
//  StockArray.h
//  stockSave
//
//  Created by tdx on 11-2-14.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "macro.h"
#define MARKET_STOCK 0
#define MARKET_STOCK_EXT 1

@interface StockArray : NSObject {
	NSMutableArray* stockCodeArray;
	int nCount;
	BOOL bIsEmpty;
	NSMutableArray* stockArray;
	NSMutableArray* stockExtArray;
	
	NSString * theFilePath;
}

@property int nCount;
@property BOOL bIsEmpty;
@property(nonatomic,retain) NSMutableArray* stockArray;

-(id) init;
-(BOOL) initWithTheArray:(NSArray*)array;
-(BOOL)	addStockCode:(NSString*)stockCode;
-(BOOL)	addStockCode:(NSString*)stockCode MarketID:(int)marketID;
-(BOOL) isEmpty;
-(BOOL) setObjectFrom:(int)IndexR To:(int)IndexD;
-(BOOL) deleteObjectWithIndex:(int)Index;
-(BOOL) deleteObject:(NSString*)stockCode;
-(BOOL) saveData;
-(NSDictionary*) getStockCodeString;
-(NSArray*) readData;
-(BOOL) stockInArray:(int)marketID StockCode:(NSString*)stockCode;
-(NSDictionary*) getStockCodeString2:(int)nstartxh num:(int)nwantnum;
-(NSString *)getStockCode:(int)nstartxh num:(int)nwantnum index:(int)nindex;
@end
