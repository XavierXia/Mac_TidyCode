//
//  TdxT2EE.h
//  IpadForTDX
//
//  Created by szk on 13-9-11.
//
//

#import <Foundation/Foundation.h>


@interface TdxT2EE : NSObject
{
}


-(NSString *)GetSecrityKey:(int)ntype pubkey:(NSString *)szUCKey;
-(NSString *)GetDeskey:(NSString *)encdeskey;
@end
