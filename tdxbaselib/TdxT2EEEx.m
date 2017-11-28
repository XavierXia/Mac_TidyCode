//
//  TdxT2EEEx.m
//  IpadForTDX
//
//  Created by szk on 13-9-12.
//
//

#import "TdxT2EEEx.h"

@implementation TdxT2EEEx
@synthesize m_t2ee,eGetData,windindex,mydelegate,m_breloginflag;


-(id)InitWithParam:(EGetData *)_data
{
    self=[super init];
    if(self)
    {
        m_breloginflag=NO;
        m_t2ee=[[TdxT2EE alloc] init];
        eGetData=_data;
        windindex=[eGetData.g_TradeComm.areceiver SetWinobjs:self];
    }
    return self;
}

-(void)dealloc
{
    [super dealloc];
    RELEASEOBJ(m_t2ee)
}

-(void)StartSSLShake
{
    [eGetData ResetDesKey];
    [eGetData sendTradeQueryData:TDX_SSLTOUCH objIndex:windindex Session:0];
}

-(BOOL)OnReceiveData:(int)reqIndex parser:(id)pParse
{
    ParseRecv *pParsers=(ParseRecv *)pParse;
    if(!pParsers)
        return YES;
    if([pParsers IsTimeOut]==NO)
    		[eGetData SetSessionID:pParsers.sessionID];
	switch (reqIndex)
    {
    case TDX_SSLTOUCH:
        {
            if([pParsers.psErrorSign isEqualToString:@"I"]==NO)
            {
                BOOL binnererror=([pParsers.psErrorNum isEqualToString:@"-100"] || [pParsers.psErrorNum isEqualToString:@"-101"]);
                if((!binnererror && m_breloginflag) || !m_breloginflag)
                {
                    NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
                                                     defaultButton: @"确定"
                                                   alternateButton: nil
                                                       otherButton: nil
                                         informativeTextWithFormat: @"%@",@"连接交易中心超时或网络已断开"];
                   [alert runModal];
                }
                
                [mydelegate StartLogin:NO];
            }
            else
            {
                NSRange trange,rsarange;
                
                trange=[pParsers.psErrorData rangeOfString:@"type="];
                rsarange=[pParsers.psErrorData rangeOfString:@"&pkey="];
                
                int ntype=[[pParsers.psErrorData substringWithRange:NSMakeRange(trange.location+trange.length, rsarange.location-trange.length)] intValue];
                
                NSString *rsakey=[pParsers.psErrorData substringFromIndex:rsarange.location+rsarange.length];
                
                NSString *szpubkey=[m_t2ee GetSecrityKey:ntype pubkey:rsakey];
                
                [eGetData sendTradeWTData:TDX_SSLSHAKE objIndex:windindex Session:0 yzm:szpubkey];
            }
        }
        break;
    case TDX_SSLSHAKE:
        {
            if([pParsers.psErrorSign isEqualToString:@"I"]==NO)
            {
                BOOL binnererror=([pParsers.psErrorNum isEqualToString:@"-100"] || [pParsers.psErrorNum isEqualToString:@"-101"]);
                if((!binnererror && m_breloginflag) || !m_breloginflag)
                {
                    NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
                                                     defaultButton: @"确定"
                                                   alternateButton: nil
                                                       otherButton: nil
                                         informativeTextWithFormat: @"%@",@"连接交易中心超时或网络已断开"];
                    [alert runModal];
                }
                [mydelegate StartLogin:NO];
            }
            else
            {
                NSRange trange;
                
                trange=[pParsers.psErrorData rangeOfString:@"Key="];
            
                NSString *encdeskey=[pParsers.psErrorData substringFromIndex:trange.location+trange.length];
                
                NSString *perkey=[m_t2ee GetDeskey:encdeskey];
                
                [eGetData SetDesKey:perkey];
                [mydelegate StartLogin:YES];
            }
        }
            break;
    }
    return TRUE;
}
@end
