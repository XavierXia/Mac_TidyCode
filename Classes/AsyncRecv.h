//
//  AsyncRecv.h
//  ;
//
//  Created by tdx on 11-3-28.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ParseRecv.h"

@interface AsyncRecver : NSObject {
	NSMutableDictionary	*winobjs;//窗口
	NSLock	*winlock;
	int		objIndex;//窗口索引
}


-(int)SetWinobjs:(id)pwind;
-(BOOL)OnReceive:(int)nobjIndex reqid:(int)reqIndex parser:(ParseRecv *)pParse;
-(BOOL)OnReceive:(int)nobjIndex reqid:(int)reqIndex assID:(int)_assID hqResult:(HqResultData *)_hqResult;
@end
