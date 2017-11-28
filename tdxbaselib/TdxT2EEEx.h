//
//  TdxT2EEEx.h
//  IpadForTDX
//
//  Created by szk on 13-9-12.
//
//

#import <Foundation/Foundation.h>
#import "TdxT2EE.h"
#import "EGetData.h"
#import "Delegate.h"

@interface TdxT2EEEx : NSObject
{
    int windindex;
    TdxT2EE  *m_t2ee;
    EGetData * eGetData;
    id<SSLDelegate> mydelegate;
    BOOL  m_breloginflag;
}
@property(nonatomic) BOOL m_breloginflag;
@property(nonatomic) int windindex;
@property(nonatomic,retain) EGetData * eGetData;
@property(nonatomic,retain) TdxT2EE  *m_t2ee;
@property(nonatomic,assign) id<SSLDelegate> mydelegate;

-(id)InitWithParam:(EGetData *)_data;
-(void)StartSSLShake;
@end
