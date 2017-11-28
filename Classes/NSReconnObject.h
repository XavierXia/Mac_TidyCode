//
//  NSReconnObject.h
//  IpadForTDX
//
//  Created by tdx on 11-5-19.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Delegate.h"
#import "EGetData.h"
#import "TdxT2EEEx.h"

@interface NSReconnObject : NSObject<reconnectDelegate,NSAlertDelegate,SSLDelegate> {
	EGetData * eGetData;
	BOOL  m_breconning;
	int	   windindex;
	BOOL  m_bfirstflag;
	int  m_nfirstindex;
	int  m_ncurindex;
	id <SystemMenuDelegate> systemDelegate;
	id <showBodyDelegate> showDelegate;
	TdxT2EEEx  *m_t2ee;
}

@property(nonatomic,assign) id <SystemMenuDelegate> systemDelegate;
@property (nonatomic,retain) EGetData * eGetData;
@property(nonatomic) int windindex;
@property(nonatomic, assign) id <showBodyDelegate> showDelegate;

-(id)initWithGetData:(EGetData *)_eGetData;

-(void)startReconn;
-(void)stopReconn;
-(BOOL)IsReconning;
-(void)relogin2;
-(void)initT2ee;
-(void)doasyncReconn;
-(void)doAfterReconnFailed;
-(void)autochangeuser;
-(void)handleResult:(NSAlert *)alert withResult:(NSInteger)result withTag:(int)_tag;
@end
