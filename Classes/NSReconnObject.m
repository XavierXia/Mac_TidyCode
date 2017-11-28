//
//  NSReconnObject.m
//  IpadForTDX
//
//  Created by tdx on 11-5-19.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "NSReconnObject.h"


@implementation NSReconnObject

@synthesize systemDelegate,eGetData,windindex,showDelegate;

-(id)initWithGetData:(EGetData *)_eGetData
{
	self=[super init];
	if(self)
	{
		eGetData=_eGetData;
		m_breconning=NO;
		m_nfirstindex=-1;
		m_ncurindex=-1;
		windindex=[_eGetData.g_TradeComm.areceiver SetWinobjs:(id)self];
		_eGetData.g_TradeComm.loginwindindex=windindex;
		_eGetData.g_TradeComm.myreconDelegate=self;
		m_bfirstflag=NO;
        [self initT2ee];
	}
	return self;
}

-(void)initT2ee
{
    m_t2ee=[[TdxT2EEEx alloc] InitWithParam:eGetData];
    m_t2ee.mydelegate=self;
    m_t2ee.m_breloginflag=YES;
}

-(void)dealloc
{
	[eGetData release];
    [m_t2ee release];
	[super dealloc];
}

-(void)startReconn
{
	m_breconning=YES;
}
-(void)stopReconn
{
	m_breconning=NO;
}

-(BOOL)IsReconning
{
	return m_breconning;
}

-(void)doasyncReconn
{
	if(eGetData.netStat==NotReachable)
	{
		[eGetData.g_TradeComm relogin3];
		return;
	}
	int sitecount=[eGetData.clientinfos.localjysites.tradesites count];
	if(m_nfirstindex==-1 && m_ncurindex==-1)
	{
		if(eGetData.clientinfos.localjysites.nlastindex>=0 && eGetData.clientinfos.localjysites.nlastindex<sitecount)
			m_ncurindex=eGetData.clientinfos.localjysites.nlastindex;
		else 
			m_ncurindex=0;
		m_nfirstindex=m_ncurindex;
	}
	else 
	{
		m_ncurindex++;
		if(m_ncurindex>=sitecount)
			m_ncurindex=0;
	}
	if([eGetData.g_TradeComm connect:NO withlastflag:YES]>=0)
	{
	//
#ifdef IMAC_SSL_JY
        [m_t2ee StartSSLShake];
#else
        [eGetData.g_TradeComm relogin2];
#endif
        
		return;
	}
	m_bfirstflag=NO;
	[self doAfterReconnFailed];
}

#pragma mark SSLDelegate

-(void)StartLogin:(BOOL)bsucflag
{
    if(bsucflag)
        [eGetData.g_TradeComm relogin2];
    else
    {
        m_bfirstflag=NO;
        [self doAfterReconnFailed];
    }
}

-(void)relogin2
{
	if([eGetData.g_TradeComm connect:NO withlastflag:YES]>=0)
	{
		[eGetData.g_TradeComm relogin2];
		return;
	}
	[self doAfterReconnFailed];
}

-(void)doAfterReconnFailed
{
	if(eGetData.netStat==NotReachable)
	{
		[eGetData.g_TradeComm relogin3];
		return;
	}
	int sitecount=[eGetData.clientinfos.localjysites.tradesites count];
	if(sitecount<=1)
	{
		[eGetData.g_TradeComm relogin3];
		return;
	}
	int nextindex=m_ncurindex+1;
	if(nextindex>=[eGetData.clientinfos.localjysites.tradesites count])
		nextindex=0;
	if(nextindex==m_nfirstindex)
	{
		[eGetData.g_TradeComm relogin3];
		return;
	}
    if(nextindex>=[eGetData.clientinfos.localjysites.tradesites count])
    {
        [eGetData.g_TradeComm relogin3];
        return;
    }
	TradeSite *pSite=[eGetData.clientinfos.localjysites.tradesites objectAtIndex:nextindex];
	NSString *tmpstr=[NSString stringWithFormat:@"连接交易服务器失败,是否连接下一个交易服务器:%@(%@:%i)?",pSite.sname,pSite.ip,pSite.nport];
	
	NSAlert* alert = [NSAlert alertWithMessageText:@"连接确认"
									 defaultButton: @"是"
								   alternateButton: @"否"
									   otherButton: @"退出交易"
						 informativeTextWithFormat: @"%@",tmpstr];
	[alert setDelegate:self];
	NSInteger result = [alert runModal];
	[self handleResult:alert withResult:result withTag:0];	
	
}

#pragma mark alert事件相关
-(void)handleResult:(NSAlert *)alert withResult:(NSInteger)result  withTag:(int)_tag{
	
	switch(result)
	{
		case NSAlertDefaultReturn:{
			[NSTimer scheduledTimerWithTimeInterval: 0.0f target:self selector: @selector(doasyncReconn) userInfo: nil repeats: NO];
			
		}
			break;
			
		case NSAlertAlternateReturn:
			[eGetData.g_TradeComm relogin3];
			break;
			
		case NSAlertOtherReturn:
			[self stopReconn];
			[showDelegate logoutTrade];
			break;
            
        default:
            break;
	}
}


#pragma mark reconnectDelegate

-(BOOL)AsyncReconnect
{
	if([self IsReconning])
		return YES;
	if(eGetData.netStat==NotReachable)
	{
		
		return NO;
	}
	m_nfirstindex=-1;
	m_ncurindex=-1;
	m_bfirstflag=YES;
	[self startReconn];
	[NSTimer scheduledTimerWithTimeInterval: 0.5f target:self selector: @selector(doasyncReconn) userInfo: nil repeats: NO];
	return YES;
}

-(void)stopreconnect
{
	[self stopReconn];
}

#pragma mark alert相关

-(BOOL)OnReceiveData:(int)reqIndex parser:(id)pParse
{
	ParseRecv *pParsers=(ParseRecv *)pParse;
	if(!pParsers)
		return YES;
	if([pParsers IsTimeOut]==NO){
		[eGetData SetSessionID:pParsers.sessionID];
	}
	switch (reqIndex) {
		case TDX_KHXY:
		{
			if(pParsers.bsucflag)
            {
                if(m_ncurindex!=eGetData.clientinfos.localjysites.nlastindex)
                {
                    eGetData.clientinfos.localjysites.nlastindex=m_ncurindex;
                    LogIt(12)
                    [eGetData.clientinfos.caches SaveLocalJySite:eGetData.clientinfos.localjysites];
                }
                
            }
			if([pParsers IsTimeOut2])
			{
				BOOL breloginflag=NO;
				if(m_bfirstflag)
				{
					m_bfirstflag=NO;
					breloginflag=YES;
				}
				if(eGetData.netStat!=NotReachable && breloginflag)
					[NSTimer scheduledTimerWithTimeInterval: 0.0f target:self selector: @selector(relogin2) userInfo: nil repeats: NO];
				else 
					[NSTimer scheduledTimerWithTimeInterval: 0.0f target:self selector: @selector(doAfterReconnFailed) userInfo: nil repeats: NO];
			}
			else 
			{
				m_bfirstflag=NO;
				if(pParsers.bsucflag==NO && pParsers.psErrorSign && [pParsers.psErrorSign isEqualToString:@"F"])
				{
					eGetData.g_TradeComm.bneedreloginflag=NO;
					[NSTimer scheduledTimerWithTimeInterval: 0.0f target:self selector: @selector(autochangeuser) userInfo: nil repeats: NO];
				}
				else
				{
					[eGetData getReloginInfo:pParsers];
					eGetData.g_TradeComm.breloginflag=NO;
					[self stopReconn];
				}
			}
		}
		default:
			break;
	}
	return YES;
}

-(void)autochangeuser
{
	[systemDelegate showSystemFunc:1];
}
@end
