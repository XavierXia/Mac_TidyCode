//
//  GetDataOperation.h
//  tdxIpad
//
//  Created by tdx on 11-1-24.
//  Copyright 2011 武汉. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "EGetData.h"
#import "macro.h"
#import "struct.h"
#import "SinHqInfo.h"
#import "Reachability.h"

@interface GetDataOperation : NSOperation {
	EGetData * eGetData;
	NSMutableData * newData;
	//NSMutableArray * ansArray;
	short myID;
	id myTarget;
	SEL myAction;
	
	NSString * newString;
	int newNum;
	int newFlags;
}

@property (nonatomic,retain) EGetData * eGetData;
@property (nonatomic,retain) NSMutableData * newData;
@property (nonatomic,retain) NSString * newString;
@property int newNum;
@property int newFlags;
//@property (nonatomic,retain) NSMutableArray * ansArray;
@property short myID;
@property(nonatomic, assign) id myTarget;
@property(nonatomic, assign) SEL myAction;

-(id) initWithData:(EGetData *)_eGetData reqID:(short)_ID  reqData:(NSMutableData *)_newData target:(id)_target action:(SEL)_action;
-(id) initWithDataEx:(EGetData *)_eGetData reqID:(short)_ID reqFlags:(int)_newFlags reqString:(NSString*)_newString reqNum:(int)_newNum  reqData:(NSMutableData *)_newData target:(id)_target action:(SEL)_action;


@end
