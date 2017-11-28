//
//  TdxT2EE.m
//  IpadForTDX
//
//  Created by szk on 13-9-11.
//
//

#import "TdxT2EE.h"


#define SAFEVCRT_FULLMODE
#define PLATFORM_IOS
#define _COMPILE_BY_GCC_
#import "safevcrt.h"
#import "security/tpki.h"

R_RSA_PUBLIC_KEY  m_cpubkey,m_spubkey;
R_RSA_PRIVATE_KEY m_cprikey;

@implementation TdxT2EE

-(id)init
{
    self=[super init];
    if(self)
    {
        
    }
    return self;
}

-(void)dealloc
{
    [super dealloc];
}

-(NSString *)GetSecrityKey:(int)ntype pubkey:(NSString *)szUCKey
{
    char szBase64Key[1024]={0},szUCKey2[1024]={0};
    long cbBase64key=UrlDecode([szUCKey UTF8String],szBase64Key,sizeof(szBase64Key));
    szBase64Key[cbBase64key]=0;
    Base64DecodeBinary(szBase64Key,(Byte *)&m_spubkey,sizeof(m_spubkey));
  
    TPKI pki;
    pki.GenerateKeys((LPPUBLICKEY)&m_cpubkey,(LPPRIVATEKEY)&m_cprikey,PKI_RSA1,ntype,FALSE);
  
  
    long cbTemp=0;
    BYTE szPubKeyEncrypted[1024]={0};
    memset(szBase64Key,0,1024);
    cbTemp=Base64Encode((LPBYTE)&m_cpubkey, sizeof(m_cpubkey), szBase64Key, sizeof(szBase64Key));
    memcpy(szPubKeyEncrypted,szBase64Key,strlen(szBase64Key)+1);
    cbTemp=pki.PublicBuf(PKI_RSA1,(LPBYTE)szPubKeyEncrypted,strlen((LPCSTR)szPubKeyEncrypted),sizeof(szPubKeyEncrypted),(LPPUBLICKEY)&m_spubkey);
    
    memset(szBase64Key,0,1024);
    cbTemp=Base64Encode((LPBYTE)szPubKeyEncrypted, cbTemp, szBase64Key, sizeof(szBase64Key));
    cbTemp=UrlEncode(szBase64Key, szUCKey2, sizeof(szUCKey2));
    return [NSString stringWithFormat:@"%s",szUCKey2];
    
}

-(NSString *)GetDeskey:(NSString *)encdeskey
{
    char szBase64Key[1024]={0},szUCKey2[1024]={0};
    long cbBase64key=UrlDecode([encdeskey UTF8String],szBase64Key,sizeof(szBase64Key));
    szBase64Key[cbBase64key]=0;
    long cbdeslen=Base64DecodeBinary(szBase64Key,(Byte *)szUCKey2,sizeof(szUCKey2));
    
    TPKI pki;
    int ncbTemp=pki.PrivateBuf(PKI_RSA1, (unsigned char* )szUCKey2,  cbdeslen,sizeof(szUCKey2), (LPPRIVATEKEY)&m_cprikey);
    szUCKey2[ncbTemp]=0;
    return [NSString stringWithFormat:@"%s",szUCKey2];
}
@end
