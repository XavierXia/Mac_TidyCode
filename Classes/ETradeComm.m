//
//  ETradeComm.m
//  tdxiphone
//
//  Created by 黄 股神 on 10-1-19.
//  Copyright 2010 武汉. All rights reserved.
//

#import "ETradeComm.h"
#import "ParseRecv.h"
#define DEST_IP "211.139.150.5"
#define DEST_PORT 7708


@implementation ETradeComm

@synthesize readData,myDelegate,m_KeepAlive,httpFlag,chbhttpflag,sendlock,nsendcount,tradeLoginFlag,asyncSocket,areceiver,loginwindindex,sessionID,breloginflag,njobtimeout,rawLen,bneedreloginflag;
@synthesize btipreloginflag,mygetDataDelegate,myreconDelegate,breconntipflag,m_blogout,m_macsstr,jyLoginDelegate;
@synthesize m_bconokflag;

- (id) init
{
	self = [super init];
	
	
	if (self != nil) {
		asyncSocket = nil; 
		areceiver=[AsyncRecver new];
        their_addr.sin_family = AF_INET;
        their_addr.sin_len         = sizeof(struct sockaddr_in);
        their_addr6.sin6_family=AF_INET6;
        their_addr6.sin6_len       = sizeof(struct sockaddr_in6);
		readData = [[NSMutableData alloc] init];
		sendqueue=[[NSMutableArray alloc] initWithCapacity:100];
		sendlock=[[NSCondition alloc] init];
		reconlock=[[NSCondition alloc] init];
		timeoutlock=[[NSCondition alloc] init];
		recvdatalock=[[NSCondition alloc] init];
		ntimeoutnum=0;
		nsendcount=0;
		tradeLoginFlag=NO;
		bexitflag=NO;
		sessionID=0;
		breloginflag=NO;
		brecvingflag=NO;
		njobtimeout=25;
		m_sendtime=0;
		[NSThread detachNewThreadSelector:@selector(processtimeout) toTarget:self withObject:nil];
		recvdata=nil;
		m_ntotallen=0;
		m_nlastlen=0;
		m_nobjIndex=0;
		m_nreqIndex=0;
		rawLen=0;
		bneedreloginflag=NO;
		btipreloginflag=NO;
		breconntipflag=NO;
		m_bconokflag=NO;
		m_nlastrecvtime=time(NULL);
		m_blogout=NO;
        bmustreconflag=NO;
		m_macsstr=[[NSString alloc] initWithFormat:@"%@",[self getMacAddress]];
		isHttpProxyConn = NO;
	}
	
	return self;
}

- (void) dealloc
{
	bexitflag=YES;
	[readData release];
	[sendlock release];
	if(sendqueue && [sendqueue count])
	{
		for (AsyncSendData *pdata in sendqueue) 
		{
			if(pdata)
				[pdata release];
		}
		[sendqueue removeAllObjects];
	}
	[sendqueue release];
	[asyncSocket release];
	[areceiver release];
	[recvdata release];
	recvdata=nil;
	[reconlock release];
	[timeoutlock release];
	[recvdatalock release];
	[m_macsstr release];
	[super dealloc];
}

-(int)connect:(BOOL)btipflag withlastflag:(BOOL)blastflag
{
	if (asyncSocket != nil) {
		[asyncSocket release];
		asyncSocket=nil;
	}

	if([mygetDataDelegate IsNetWorkOk]==NO)
	{
		if(btipflag	)
		{
			NSAlert* alert = [NSAlert alertWithMessageText: @"提示"
											 defaultButton: @"确定"
										   alternateButton: nil
											   otherButton: nil
								 informativeTextWithFormat: @"连接交易主站失败,请检查网络环境!"];
			[alert runModal];
		}
		
		return -1;
	}
	TradeSite *pSite=[mygetDataDelegate GetJyLoginSite:blastflag];
	if(pSite==nil)
	{
		if(btipflag	)
		{
			NSAlert* alert = [NSAlert alertWithMessageText: @"提示"
											 defaultButton: @"确定"
										   alternateButton: nil
											   otherButton: nil
								 informativeTextWithFormat: @"没有可用的交易中心,请检查交易中心设置!"];
			[alert runModal];
		}
		
		return -1;
	}
	
	asyncSocket = [[AsyncSocket alloc] initWithDelegate:self]; 
	NSError *err = nil; 
	
	if ([mygetDataDelegate IsHttpProxyWork]) {
		NSLog(@"http proxy");
		if ([[mygetDataDelegate getHttpProxyAddress] length]  == 0) {
			return -1;
		}
        
        NSString *strip4=[mygetDataDelegate getHttpProxyAddress];
        NSString *strip=[asyncSocket getProperIPWithAddress:strip4 port:[[mygetDataDelegate getHttpProxyPort] intValue]];
        
        NSData *dsa;
        if([strip length]<=0)
        {
            NSArray *piparr=[strip4 componentsSeparatedByString:@"."];
            strip=[NSString stringWithFormat:@"64:ff9b::%02x%02x:%02x%02x",[piparr[0] intValue],[piparr[1]  intValue],[piparr[2]  intValue],[piparr[3] intValue]];
            
            memset(&their_addr6, 0, sizeof(their_addr6));
            their_addr6.sin6_len = sizeof(their_addr6);
            their_addr6.sin6_family = AF_INET6;
            
            their_addr6.sin6_port = htons([[mygetDataDelegate getHttpProxyPort] intValue]);
            inet_pton(AF_INET6, strip.UTF8String, &their_addr6.sin6_addr);
            
            dsa = [NSData dataWithBytes:&their_addr6 length:sizeof(their_addr6)];
            
            if(![asyncSocket connectToAddress:dsa withTimeout:6.0f error:&err])
            {
                [asyncSocket release];
                asyncSocket=nil;
                
                asyncSocket = [[AsyncSocket alloc] initWithDelegate:self];
                
                memset(&their_addr, 0, sizeof(their_addr));
                their_addr.sin_len = sizeof(their_addr);
                their_addr.sin_family = AF_INET;
                
                their_addr.sin_port = htons([[mygetDataDelegate getHttpProxyPort] intValue]);
                inet_pton(AF_INET, strip4.UTF8String, &their_addr.sin_addr.s_addr);
                
                dsa =[NSData dataWithBytes:&their_addr length:sizeof(their_addr)];
                
                if(![asyncSocket connectToAddress:dsa withTimeout:6.0f error:&err])
                {
                    [asyncSocket release];
                    asyncSocket=nil;
                    return -1;
                }
                else
                {
                    [asyncSocket readDataWithTimeout:-1 tag:0];
                }
                
            }
            else
            {
                [asyncSocket readDataWithTimeout:-1 tag:0];
            }
        }
        else
        {
            BOOL isipv6flag=([strip isEqualToString:strip4]==NO);
            
            
            if(isipv6flag)
            {
                memset(&their_addr6, 0, sizeof(their_addr6));
                their_addr6.sin6_len = sizeof(their_addr6);
                their_addr6.sin6_family = AF_INET6;
                
                their_addr6.sin6_port = htons([[mygetDataDelegate getHttpProxyPort] intValue]);
                inet_pton(AF_INET6, strip.UTF8String, &their_addr6.sin6_addr);
                
                dsa = [NSData dataWithBytes:&their_addr6 length:sizeof(their_addr6)];
            }
            else
            {
                memset(&their_addr, 0, sizeof(their_addr));
                their_addr.sin_len = sizeof(their_addr);
                their_addr.sin_family = AF_INET;
                
                their_addr.sin_port = htons([[mygetDataDelegate getHttpProxyPort] intValue]);
                inet_pton(AF_INET, strip4.UTF8String, &their_addr.sin_addr.s_addr);
                
                dsa =[NSData dataWithBytes:&their_addr length:sizeof(their_addr)];
            }
            
            if(![asyncSocket connectToAddress:dsa withTimeout:6.0f error:&err])
            {
                [asyncSocket release];
                asyncSocket=nil;
                return -1;
            } 
            else 
            {
                [asyncSocket readDataWithTimeout:-1 tag:0];
            }
        }
        
		
		return 1;
	}
    
    NSString *strip4=pSite.ip;
    NSString *strip=[asyncSocket getProperIPWithAddress:strip4 port:pSite.nport];
    
    NSData *dsa;
    if([strip length]<=0)
    {
        NSArray *piparr=[strip4 componentsSeparatedByString:@"."];
        strip=[NSString stringWithFormat:@"64:ff9b::%02x%02x:%02x%02x",[piparr[0] intValue],[piparr[1]  intValue],[piparr[2]  intValue],[piparr[3] intValue]];
        
        memset(&their_addr6, 0, sizeof(their_addr6));
        their_addr6.sin6_len = sizeof(their_addr6);
        their_addr6.sin6_family = AF_INET6;
        
        their_addr6.sin6_port = htons(pSite.nport);
        inet_pton(AF_INET6, strip.UTF8String, &their_addr6.sin6_addr);
        
        dsa = [NSData dataWithBytes:&their_addr6 length:sizeof(their_addr6)];
        
        if(![asyncSocket connectToAddress:dsa withTimeout:6.0f error:&err])
        {
            [asyncSocket release];
            asyncSocket=nil;
            
            asyncSocket = [[AsyncSocket alloc] initWithDelegate:self];
            
            memset(&their_addr, 0, sizeof(their_addr));
            their_addr.sin_len = sizeof(their_addr);
            their_addr.sin_family = AF_INET;
            
            their_addr.sin_port = htons(pSite.nport);
            inet_pton(AF_INET, strip4.UTF8String, &their_addr.sin_addr.s_addr);
            
            dsa =[NSData dataWithBytes:&their_addr length:sizeof(their_addr)];
            
            if(![asyncSocket connectToAddress:dsa withTimeout:6.0f error:&err])
            {
                [asyncSocket release];
                asyncSocket=nil;
                
                if(btipflag	)
                {
                    NSAlert* alert = [NSAlert alertWithMessageText: @"提示"
                                                     defaultButton: @"确定"
                                                   alternateButton: nil
                                                       otherButton: nil
                                         informativeTextWithFormat: @"连接交易服务器失败,请检查网络环境!"];
                    [alert runModal];
                    
                }
                return -1;
            }
            else
            {
                m_nlastrecvtime=time(NULL);
                [asyncSocket readDataWithTimeout:-1 tag:0];
            }
            
        }
        else
        {
            m_nlastrecvtime=time(NULL);
            [asyncSocket readDataWithTimeout:-1 tag:0];
        }
    }
    else
    {
        BOOL isipv6flag=([strip isEqualToString:strip4]==NO);
        
        
        if(isipv6flag)
        {
            memset(&their_addr6, 0, sizeof(their_addr6));
            their_addr6.sin6_len = sizeof(their_addr6);
            their_addr6.sin6_family = AF_INET6;
            
            their_addr6.sin6_port = htons(pSite.nport);
            inet_pton(AF_INET6, strip.UTF8String, &their_addr6.sin6_addr);
            
            dsa = [NSData dataWithBytes:&their_addr6 length:sizeof(their_addr6)];
        }
        else
        {
            memset(&their_addr, 0, sizeof(their_addr));
            their_addr.sin_len = sizeof(their_addr);
            their_addr.sin_family = AF_INET;
            
            their_addr.sin_port = htons(pSite.nport);
            inet_pton(AF_INET, strip4.UTF8String, &their_addr.sin_addr.s_addr);
            
            dsa =[NSData dataWithBytes:&their_addr length:sizeof(their_addr)];
        }
        
        
        if(![asyncSocket connectToAddress:dsa withTimeout:6.0f error:&err])
        {
            if(btipflag	)
            {
                NSAlert* alert = [NSAlert alertWithMessageText: @"提示"
                                                 defaultButton: @"确定"
                                               alternateButton: nil
                                                   otherButton: nil
                                     informativeTextWithFormat: @"连接交易服务器失败,请检查网络环境!"];
                [alert runModal];
                
            }
            [asyncSocket release];
            asyncSocket=nil;
            return -1;
        } 
        else 
        {
            m_nlastrecvtime=time(NULL);
            [asyncSocket readDataWithTimeout:-1 tag:0];
        }
    }
    
    
	return 1;
}

-(void)clearAllRequest{
	[sendlock lock];
	AsyncSendData *pnewdata=nil;
	int count=[sendqueue count];
	for(int i=count-1;i>=0;i--)
	{
		pnewdata=[sendqueue objectAtIndex:i];
		[pnewdata release];
	}
	[sendqueue removeAllObjects];
	[sendlock unlock];
}

-(BOOL)reconnect
{
	[reconlock lock];
	if(breloginflag)
	{
		[reconlock unlock];
		return YES;
	}
	breloginflag=YES;
	[reconlock unlock];
	if(brecvingflag)
	{
		brecvingflag=NO;
		m_sendtime=time(NULL);
		ParseRecv *pParse=[ParseRecv new];
		pParse.bsucflag=NO;
		pParse.btipflag=NO;
		pParse.psErrorSign=[[NSString alloc]  initWithFormat:@"%@",@"T"];
		[pParse.psErrorSign release];
		pParse.psErrorNum=[[NSString alloc]  initWithFormat:@"%@",@"-100"];
		[pParse.psErrorNum release];
		pParse.psErrorData=[[NSString alloc]  initWithFormat:@"%@",@"接收应答超时或网络已断开"];
		[pParse.psErrorData release];
		[sendlock lock];
		AsyncSendData *pnewdata=nil;
		int count=[sendqueue count];
		for(int i=count-1;i>=0;i--)
		{
			pnewdata=[sendqueue objectAtIndex:i];
			if(pnewdata)
			{
				if(pnewdata.nreqIndex!=TDX_CHB)
					[areceiver OnReceive:pnewdata.nobjIndex reqid:pnewdata.nreqIndex parser:pParse];
			}
			[pnewdata release];
		}
		[sendqueue removeAllObjects];
		[sendlock unlock];
		[pParse release];
	}
	[recvdatalock lock];
	[recvdata release];
	recvdata=nil;
	[recvdatalock unlock];
	
	if([mygetDataDelegate IsJyLocking])
	{
        if(bmustreconflag)
        {
            bmustreconflag=NO;
        }
        else
        {
            [self relogin3];
            return NO;
        }
	}
	if([myreconDelegate AsyncReconnect]==NO)
	{
		[self relogin3];
		return NO;
	}
	return YES;
}

-(void)relogin3
{
	[myreconDelegate stopreconnect];
	bneedreloginflag=YES;
	breloginflag=NO;
}

-(void)relogin2
{
	if(tradeLoginFlag)
	{
		[self relogin];
	}
	else 
	{
		[self relogin3];
	}
}

-(int) getHttpFlag:(NSString *) theString {
	NSRange range=[theString rangeOfString:@"\r\n\r\n"];
	if(range.location==NSNotFound)
		return 0;
	return (range.location+range.length);
}

#pragma mark - UIAlertViewDelegate

-(void)logout
{
	m_blogout=YES;
	tradeLoginFlag=NO;
	sessionID=0;
	breloginflag=NO;
	brecvingflag=NO;
	bneedreloginflag=NO;
	btipreloginflag=NO;
	[sendlock lock];
	if(sendqueue && [sendqueue count])
	{
		for (AsyncSendData *pdata in sendqueue) 
		{
			if(pdata)
				[pdata release];
		}
		[sendqueue removeAllObjects];
	}
	[sendlock unlock];
	[recvdatalock lock];
	[recvdata release];
	recvdata=nil;
	[recvdatalock unlock];
	[timeoutlock lock];
	ntimeoutnum=0;
	[timeoutlock unlock];
	m_nlastrecvtime=time(NULL);
}

-(BOOL)IsLoginIndex:(int)nindex
{
    switch (nindex) {
        case TDX_KHXY:
        case TDX_SSLTOUCH:
        case TDX_SSLSHAKE:
            return YES;
            break;
            
        default:
            break;
    }
    return NO;
}

//异步发送
-(BOOL)AsyncSendData:(NSData *) lBuf length:(int)lBufLength withobjIndex:(short)nobjIndex withreqIndex:(short)nreqIndex
{
	if([mygetDataDelegate IsNetWorkOk]==NO || m_blogout)
	{
		if(nreqIndex!=TDX_CHB)
		{
			ParseRecv *pParse=[ParseRecv new];
			pParse.bsucflag=NO;
			pParse.btipflag=((breloginflag || m_blogout)?NO:YES);
			pParse.psErrorSign=[[NSString alloc]  initWithFormat:@"%@",@"R"];
			[pParse.psErrorSign release];
			pParse.psErrorNum=[[NSString alloc]  initWithFormat:@"%@",@"-102"];
			[pParse.psErrorNum release];
			pParse.psErrorData=[[NSString alloc]  initWithFormat:@"%@",(m_blogout?@"已经退出了交易系统":@"网络已断开,请检查网络环境!")];
			[pParse.psErrorData release];
			[areceiver OnReceive:nobjIndex reqid:nreqIndex parser:pParse];
			[pParse release];
		}
		return YES;
	}
	if( tradeLoginFlag==NO && ![self IsLoginIndex:nreqIndex])
	{
		if(nreqIndex!=TDX_CHB )
		{
			ParseRecv *pParse=[ParseRecv new];
			pParse.bsucflag=NO;
			pParse.btipflag=YES;
			pParse.psErrorSign=[[NSString alloc]  initWithFormat:@"%@",@"R"];
			[pParse.psErrorSign release];
			pParse.psErrorNum=[[NSString alloc]  initWithFormat:@"%@",@"-103"];
			[pParse.psErrorNum release];
			pParse.psErrorData=[[NSString alloc]  initWithFormat:@"%@",@"您还没有登录交易系统,请登录后再操作!"];
			[pParse.psErrorData release];
			[areceiver OnReceive:nobjIndex reqid:nreqIndex parser:pParse];
			[pParse release];
		}
		return YES;
	}
	BOOL  breconflag1=(!breloginflag && !m_bconokflag && tradeLoginFlag);
	BOOL  breconflag2=(!breloginflag && tradeLoginFlag==YES && ![self IsLoginIndex:nreqIndex] && bneedreloginflag);
	BOOL  breconflag3=(!breloginflag && tradeLoginFlag==YES && !bneedreloginflag && (ntimeoutnum>=2 || (time(NULL)-m_nlastrecvtime>=90)));
	if((breconflag1 || breloginflag || breconflag2 || breconflag3) && (nreqIndex!=TDX_SSLTOUCH && nreqIndex!=TDX_SSLSHAKE))
	{
		if(breconflag3)
		{
			if(ntimeoutnum>0)
			{
				[timeoutlock lock];
				ntimeoutnum=0;
				[timeoutlock unlock];
			}
			m_nlastrecvtime=time(NULL);
		}
		NSString *status=[NSString stringWithFormat:@"%i_%i%i%i%i_%i_%i%li",m_bconokflag,breloginflag,brecvingflag,tradeLoginFlag,bneedreloginflag,nreqIndex,ntimeoutnum,(time(NULL)-m_nlastrecvtime)];
		BOOL breconnect=NO;
		if(breconflag1 ||  breconflag2 || breconflag3)
		{
			if(nreqIndex==TDX_CHB)
				btipreloginflag=NO;
			else 
				btipreloginflag=YES;
			breconnect=YES;
			[NSTimer scheduledTimerWithTimeInterval: 0.0f target:self selector:@selector(reconnect) userInfo: nil repeats: NO];
		}
		if(nreqIndex==TDX_CHB)
			return YES;
		ParseRecv *pParse=[ParseRecv new];
		pParse.bsucflag=NO;
		pParse.btipflag=((breloginflag && !breconnect)?YES:NO);
		pParse.psErrorSign=[[NSString alloc]  initWithFormat:@"%@",@"R"];
		[pParse.psErrorSign release];
		pParse.psErrorNum=[[NSString alloc]  initWithFormat:@"%@",@"-101"];
		[pParse.psErrorNum release];
		int ntimeout=njobtimeout;
		if(breloginflag && [self IsLoginIndex:m_nreqIndex] && m_nobjIndex==loginwindindex)
			ntimeout=6;
		if(brecvingflag)
			pParse.psErrorData=[[NSString alloc] initWithFormat:@"正在等待交易服务器登录应答,请稍候重试!\r\r状态码: %@\r%li秒后登录超时",status,(ntimeout-(time(NULL)-m_sendtime))];
		else 
			pParse.psErrorData=[[NSString alloc] initWithFormat:@"正在断线重连,请稍候重试!状态码: %@",status];
		[pParse.psErrorData release];
		[areceiver OnReceive:nobjIndex reqid:nreqIndex parser:pParse];
		[pParse release];
		return YES;
	}
	BOOL bflag=(brecvingflag || [sendqueue count] );
	if(bflag && (nreqIndex==TDX_CHB || nreqIndex==TDX_SSLSHAKE || nreqIndex==TDX_SSLTOUCH))
		return YES;
	NSMutableData *newdata = [[NSMutableData alloc] init];
	NSString * tempString = @"";
    if(nreqIndex==TDX_SSLTOUCH)
    {
        tempString = @"POST /Session.dll?CMD=ssltouch HTTP/1.1\r\n";
    }
    else if(nreqIndex==TDX_SSLSHAKE)
    {
        tempString = @"POST /Session.dll?CMD=sslshake HTTP/1.1\r\n";
    }
    else
    {
        tempString = @"POST /trade.dll HTTP/1.1\r\n";
        
    }
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	tempString  = [NSString stringWithFormat:@"Host:%@\r\n",@"test" ];
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	tempString = [NSString stringWithFormat:@"Referer:%i\r\n",500 ];
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	tempString = @"Accpet: */*\r\n";
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	tempString = @"Accpet-Language: zh-cn\r\n";
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	tempString = @"Accpet-Encoding: zip\r\n";
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	tempString = @"User-Agent: NT 5.1\r\n"; 
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	tempString = [NSString stringWithFormat:@"Connection:%@\r\n",@"Keep-Alive"];
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	tempString = [NSString stringWithFormat:@"Content-Length:%i\r\n",lBufLength];
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	tempString =  @"\r\n";
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	[newdata appendData:lBuf];
	
	
	
	
	[sendlock lock];
	
	AsyncSendData *pdata=[[AsyncSendData alloc] initWithData:nobjIndex reqIndex:nreqIndex data:newdata];
		
	
	if ([mygetDataDelegate IsHttpProxyWork]) {
		if(!bflag)
		{
			if (isHttpProxyConn) {
				[sendqueue addObject:pdata];
				pdata.bsended=YES;
				m_sendtime=time(NULL);
				brecvingflag=YES;
				m_nobjIndex=nobjIndex;
				m_nreqIndex=nreqIndex;
				[asyncSocket writeData:newdata withTimeout:-1 tag:0];
			}
			else {
				[sendqueue addObject:pdata];
			}
		}
		else 
		{
			if(nreqIndex>=PAGE_FIRSTINDEX)
			{
				int count=[sendqueue count];
				AsyncSendData *pdata1=nil;
				for(int i=count-1;i>=1;i--)
				{
					pdata1=[sendqueue objectAtIndex:i];
					if(pdata1 && pdata1.nreqIndex>=PAGE_FIRSTINDEX)
					{
						[pdata1 release];
						[sendqueue removeObjectAtIndex:i];
					}
					
				}
			}
			[sendqueue insertObject:pdata atIndex:1];//最新请求的最快响应
		}
	}
	else {
		if(!bflag)
		{
			//[mygetDataDelegate writeLog:@"didsendData"];
			[sendqueue addObject:pdata];
			pdata.bsended=YES;
			m_sendtime=time(NULL);
			brecvingflag=YES;
			m_nobjIndex=nobjIndex;
			m_nreqIndex=nreqIndex;
			[asyncSocket writeData:newdata withTimeout:-1 tag:0];
		}
		else 
		{
			if(nreqIndex>=PAGE_FIRSTINDEX)
			{
				int count=[sendqueue count];
				AsyncSendData *pdata1=nil;
				for(int i=count-1;i>=1;i--)
				{
					pdata1=[sendqueue objectAtIndex:i];
					if(pdata1 && pdata1.nreqIndex>=PAGE_FIRSTINDEX)
					{
						[pdata1 release];
						[sendqueue removeObjectAtIndex:i];
					}
					
				}
			}
			[sendqueue insertObject:pdata atIndex:1];//最新请求的最快响应
		}
	}

	

	[sendlock unlock];
	
	if(!bflag)
	{
		[asyncSocket readDataWithTimeout:-1 tag:0];
	}
	return YES;
}

-(BOOL)relogin
{
	NSMutableData *newdata = [[NSMutableData alloc] init];
	NSString * tempString = @"POST /trade.dll HTTP/1.1\r\n";
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	tempString  = [NSString stringWithFormat:@"Host:%@\r\n",@"test" ];
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	tempString = [NSString stringWithFormat:@"Referer:%i\r\n",500 ];
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	tempString = @"Accpet: */*\r\n";
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	tempString = @"Accpet-Language: zh-cn\r\n";
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	tempString = @"Accpet-Encoding: zip\r\n";
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	tempString = @"User-Agent: NT 5.1\r\n"; 
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	tempString = [NSString stringWithFormat:@"Connection:%@\r\n",@"Keep-Alive"];
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
	
	NSMutableData *relogindata=[[NSMutableData alloc] init];
	[mygetDataDelegate genReloginData:relogindata];
	tempString = [NSString stringWithFormat:@"Content-Length:%i\r\n\r\n",[relogindata length]];	
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];	
	
	[newdata appendData:relogindata];
	
	[sendlock lock];
	m_sendtime=time(NULL);
	brecvingflag=YES;
	m_nobjIndex=loginwindindex;
	m_nreqIndex=TDX_KHXY;
	[asyncSocket writeData:newdata withTimeout:-1 tag:0];
	[sendlock unlock];
	
	[newdata release];
	[relogindata release];
	[asyncSocket readDataWithTimeout:-1 tag:0];
	return YES;
}

//异步接收
-(void) onSocket:(AsyncSocket *)sock didReadData:(NSData *)data withTag:(long)tag
{
	if(m_blogout)
		return;
	NSData *strData =nil;
	[recvdatalock lock];
	BOOL brecvdataflag=(recvdata!=nil);
	if(brecvdataflag)
		[recvdata appendData:data];
	else 
		recvdata=[[NSMutableData alloc] initWithData:data];
	
	
	if ([mygetDataDelegate IsHttpProxyWork]) {
		if (!isHttpProxyConn) {
			NSString *tempStringEx = [[NSString alloc] initWithData:recvdata encoding:CFStringConvertEncodingToNSStringEncoding (kCFStringEncodingGB_18030_2000)];
			NSLog(@"%@",tempStringEx);
			
			
			NSRange range=[tempStringEx rangeOfString:@"200"];
			if(range.location!=NSNotFound && range.location<[tempStringEx length])
			{
				[recvdata release];
				recvdata=nil;
				isHttpProxyConn = YES;
				[self sendnextreq];
			}
			else {
				NSAlert* alert = [NSAlert alertWithMessageText: @"提示"
												 defaultButton: @"确定"
											   alternateButton: nil
												   otherButton: nil
									 informativeTextWithFormat: @"连接代理服务器失败!"];
				[alert runModal];
				HqResultData * hqResult = [[HqResultData alloc]  init];
				hqResult.receiveLen = 0;
				hqResult.resultStat = DATARESULT_TIMEOUT;
				[areceiver OnReceive:m_nobjIndex reqid:m_nreqIndex assID:0 hqResult:hqResult];
				[hqResult release];
			}
			
			
			[recvdatalock unlock];
			return;
		}
	}
	
	int nrtotallen=[recvdata length];
	[recvdatalock unlock];
	if(brecvdataflag)
	{
		if(m_ntotallen>m_nlastlen)
		{
			int noffset=m_ntotallen-m_nlastlen;
			if(noffset>[data length])
			{
				m_nlastlen+=[data length];
				[asyncSocket readDataWithTimeout:-1 tag:0];//结尾调用
				return;
			}
			else if(noffset==[data length])
			{
				strData=recvdata;
				m_nlastlen=m_ntotallen;
			}
			else 
			{
				strData=recvdata;
				m_nlastlen=m_ntotallen;
			}
		}
		else 
		{
			strData=recvdata;
			m_ntotallen=nrtotallen;
			m_nlastlen=0;
		}
	}
	else
	{
		strData=recvdata;
		m_ntotallen=nrtotallen;
		m_nlastlen=0;
	}
	NSString *tempString2 = [[NSString alloc] initWithData:strData encoding:NSASCIIStringEncoding];
	NSRange range,range2;
	range=[tempString2 rangeOfString:@"HTTP/1.1"];
	if(range.location==NSNotFound)
	{
		[tempString2 release];
		[asyncSocket readDataWithTimeout:-1 tag:0];//结尾调用
		return;
	}
	NSString *tempString1=[tempString2 substringFromIndex:range.location];
	int nhttpFlag = [self getHttpFlag:tempString1];
	if(nhttpFlag<=0)
	{
		[tempString2 release];
		[asyncSocket readDataWithTimeout:-1 tag:0];//结尾调用
		return;
	}
	nhttpFlag+=range.location;
	int ntotallen=0;
	////判断是否收完//////
	range=[tempString2 rangeOfString:@"Content-Length:"];
	if(range.location!=NSNotFound && range.location<[tempString2 length])
	{
		range2= [[tempString2 substringFromIndex:(range.length+range.location)] rangeOfString:@"\r\n"];
		if(range2.location!=NSNotFound && range2.location < [tempString2 length])
		{
			ntotallen=[[tempString2 substringWithRange:NSMakeRange((range.length+range.location), range2.location)] intValue];
			if((ntotallen+nhttpFlag)>[tempString2 length])//说明没有收完
			{
				m_nlastlen=[tempString2 length];
				m_ntotallen=(ntotallen+nhttpFlag);
				[tempString2 release];
				[asyncSocket readDataWithTimeout:-1 tag:0];//结尾调用
				return;
			}
		}
	}
	brecvingflag=NO;
	if(ntimeoutnum>0)
	{
		[timeoutlock lock];
		ntimeoutnum=0;
		[timeoutlock unlock];
	}
	m_nlastrecvtime=time(NULL);
	////判断是否收完//////
	unsigned long transkey=0;
	[strData getTdxBytes:&transkey range:NSMakeRange(nhttpFlag+5, 4)];
	
	
	short reqIndex=(transkey & 0xFFFF);
	
	short objIndex=(transkey>>16);
	NSData *recvdata1=[strData subdataWithRange:NSMakeRange(nhttpFlag,ntotallen)];
	ParseRecv *pParse=[ParseRecv new];
	char bcompressed=0,bencrypted=0;
	[recvdata1 getTdxBytes:&bcompressed range:NSMakeRange(2, sizeof(char))];
	[recvdata1 getTdxBytes:&bencrypted range:NSMakeRange(3, sizeof(char))];
	pParse.bcompressed=bcompressed;
	pParse.bencrypted=bencrypted;
	range=[tempString2 rangeOfString:@"Raw-Length:"];
	if(range.location!=NSNotFound && range.location<[tempString2 length])
	{
		range2= [[tempString2 substringFromIndex:(range.length+range.location)] rangeOfString:@"\r\n"];
		if(range2.location!=NSNotFound && range2.location < [tempString2 length])
		{
			pParse.rawlen=[[tempString2 substringWithRange:NSMakeRange((range.length+range.location), range2.location)] intValue];
		}
	}
	range=[tempString2 rangeOfString:@"Compress-Length:"];
	if((range.location!=NSNotFound)&&(range.location < [tempString2 length]))
	{
		range2= [[tempString2 substringFromIndex:(range.length+range.location)] rangeOfString:@"\r\n"];
		if(range2.location!=NSNotFound && range2.location < [tempString2 length])
		{
			pParse.compresslen=[[tempString2 substringWithRange:NSMakeRange((range.length+range.location), range2.location)] intValue];
		}
	}
	@try {
        pParse.nreqindex=reqIndex;
		[pParse parseit:recvdata1];
	}
	@catch (NSException * e) {
		NSLog(@"%@",[e name]);
		[pParse generror];
	}
	@finally {
		;
	}
	//NSLog(@"onSocket data rec4");
	if([pParse.psErrorNum isEqualToString:@"423"] && [pParse.psErrorData compare:@"SESSION无效"]>=0)
	{
		[pParse release];
		[tempString2 release];
		m_ntotallen=0;
		m_nlastlen=0;
		[recvdatalock lock];
		[recvdata release];
		recvdata=nil;
		[recvdatalock unlock];
		
        if([sendqueue count])
        {
            [sendlock lock];
            AsyncSendData *pnewdata=[sendqueue objectAtIndex:0];
            if(pnewdata)
            {
                if(pnewdata.bsended)
                {
                    if(reqIndex==TDX_KHXY && !breloginflag)
                    {
                        [pnewdata release];
                        [sendqueue removeObjectAtIndex:0];
                    }
                    else
                        pnewdata.bsended=NO;
                }
            }
            [sendlock unlock];
        }
		
		
		if(reqIndex!=TDX_CHB)
		{
			pParse=[ParseRecv new];
			pParse.bsucflag=NO;
			pParse.btipflag=((reqIndex==TDX_KHXY && !breloginflag)?YES:NO);
			pParse.psErrorSign=[[NSString alloc]  initWithFormat:@"%@",@"F"];
			[pParse.psErrorSign release];
			pParse.psErrorNum=[[NSString alloc]  initWithFormat:@"%@",@"423"];
			[pParse.psErrorNum release];
			pParse.psErrorData=[[NSString alloc]  initWithFormat:@"%@",@"SESSION无效"];
			[pParse.psErrorData release];
			[areceiver OnReceive:((breloginflag && reqIndex==TDX_KHXY)?loginwindindex:objIndex) reqid:reqIndex parser:pParse];
			[pParse release];
		}
		[NSTimer scheduledTimerWithTimeInterval: 0.0f target:self selector: @selector(reconnect) userInfo: nil repeats: NO];
		return;
	}
	else 
	{
		if([sendqueue count])
		{
			[sendlock lock];
			AsyncSendData *pnewdata=[sendqueue objectAtIndex:0];
			if(pnewdata && pnewdata.bsended)
			{
				[pnewdata release];
				[sendqueue removeObjectAtIndex:0];
			}
			[sendlock unlock];
		}
	}
	//NSLog(@"onSocket data rec5");
	if(reqIndex==TDX_CHB)
		[myDelegate SetCHBSessionID:pParse.sessionID];
	else if(breloginflag && reqIndex==TDX_KHXY)
		[areceiver OnReceive:loginwindindex reqid:reqIndex parser:pParse];
	else 
		[areceiver OnReceive:objIndex reqid:reqIndex parser:pParse];
	[pParse release];
	[tempString2 release];
	[recvdatalock lock];
	if(recvdata)
	{
		int recvlen=[recvdata length];
		if(recvlen >(ntotallen+nhttpFlag))
		{
			m_nlastlen=recvlen-ntotallen-nhttpFlag;
			m_ntotallen=0;
			NSData *pdata=[[NSData alloc] initWithData: [recvdata subdataWithRange:NSMakeRange((ntotallen+nhttpFlag), m_nlastlen)]];
			[recvdata release];
			recvdata=nil;
			recvdata=[[NSMutableData alloc]initWithData: pdata];
			[pdata release];
            [recvdatalock unlock];
			[asyncSocket readDataWithTimeout:-1 tag:0];//结尾调用
			return;
		}
		else 
		{
			m_ntotallen=0;
			m_nlastlen=0;
			[recvdata release];
			recvdata=nil;
		}
	}
	else 
	{
		m_ntotallen=0;
		m_nlastlen=0;
		recvdata=nil;
	}
	[recvdatalock unlock];
	[self sendnextreq];

}

-(BOOL)sendnextreq
{
	
	if([mygetDataDelegate IsNetWorkOk]==NO)
		return YES;
	if(breloginflag)
		return YES;
	if ([mygetDataDelegate IsHttpProxyWork]) {
		if (!isHttpProxyConn) {
			return YES;
		}
	}
	
	if(!breloginflag && tradeLoginFlag==YES && [sendqueue count]>0 && bneedreloginflag)
	{
		btipreloginflag=NO;
		[NSTimer scheduledTimerWithTimeInterval: 0.0f target:self selector: @selector(reconnect) userInfo: nil repeats: NO];
		return YES;
	}
	if([sendqueue count])
	{
		[sendlock lock];
		AsyncSendData *pnewdata=[sendqueue objectAtIndex:0];
		if(pnewdata)
		{
			if(pnewdata.bsended)
			{
				[sendlock unlock];
				return YES;
			}
			m_sendtime=time(NULL);
			m_nobjIndex=pnewdata.nobjIndex;
			m_nreqIndex=pnewdata.nreqIndex;
			brecvingflag=YES;
			pnewdata.bsended=YES;
			[asyncSocket writeData:pnewdata.senddata withTimeout:-1 tag:0];
		}
		[sendlock unlock];
	}
	[asyncSocket readDataWithTimeout:-1 tag:0];//结尾调用
	return YES;
}

//断线
- (void)onSocketDidDisconnect:(AsyncSocket *)sock
{
	NSLog(@"onSocketDidDisconnect");
	
	if ([mygetDataDelegate IsHttpProxyWork]) {
		isHttpProxyConn = NO;
	}
	
	m_bconokflag=NO;
	if(bexitflag || !tradeLoginFlag || breloginflag)
		return;
	btipreloginflag=NO;
	[NSTimer scheduledTimerWithTimeInterval: 0.0f target:self selector: @selector(reconnect) userInfo: nil repeats: NO];
}

-(void) onSocket:(AsyncSocket *)sock didConnectToHost:(NSString *)host port:(UInt16)port{
	NSLog(@"Host is %@ and port is %hu",host,port);

	m_bconokflag=YES;
	
	if ([mygetDataDelegate IsHttpProxyWork])
    {
		if (!isHttpProxyConn)
        {
			TradeSite *pSite=[mygetDataDelegate GetJyLoginSite:YES];
			NSMutableData *newdata = [[NSMutableData alloc] init];
			
			NSString * tempString = [NSString stringWithFormat:@"CONNECT %@:%i HTTP/1.1\r\n",pSite.ip,pSite.nport];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString  = [NSString stringWithFormat:@"User-Agent: Mozilla/4.0\r\n"];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			if ([[mygetDataDelegate getHttpProxyUsername] length] >0) {
				NSString * authString = [NSString stringWithFormat:@"%@:%@",[mygetDataDelegate getHttpProxyUsername],[mygetDataDelegate getHttpProxyPassword]];
				NSData * tempData = [authString dataUsingEncoding:NSUTF8StringEncoding allowLossyConversion:YES];
				NSString * base64String = [[NSString alloc]  initWithData:[GTMBase64 encodeData:tempData] encoding:NSUTF8StringEncoding];
				tempString = [NSString stringWithFormat:@"Proxy-Authorization:Basic %@\r\n",base64String];
				[base64String release];
				[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			}
			
			tempString = @"\r\n";
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			
			[sendlock lock];
			[asyncSocket writeData:newdata withTimeout:-1 tag:0];
			[sendlock unlock];
			[asyncSocket readDataWithTimeout:-1 tag:0];
			
			[newdata release];
		}
	}
}

-(void)processtimeout
{
	NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
	while(!bexitflag)
	{
		if(brecvingflag)
		{
			int ntimeout=njobtimeout;
			if(m_nreqIndex==TDX_KHXY)
				ntimeout=6;
			if(breloginflag && m_nreqIndex==TDX_KHXY)
				ntimeout=6;
			
			if(time(NULL)-m_sendtime>ntimeout || ([mygetDataDelegate IsNetWorkOk]==NO))
			{
				[sendlock lock];
				if(breloginflag==NO && [sendqueue count])
				{
					AsyncSendData *pnewdata=[sendqueue objectAtIndex:0];
					if(pnewdata)
					{
						if(pnewdata.bsended)
							[pnewdata release];
						[sendqueue removeObjectAtIndex:0];
					}
				}
				NSString *tmpstr=[NSString stringWithFormat:@"%i:%i",m_nobjIndex,m_nreqIndex];
				brecvingflag=NO;
				m_sendtime=time(NULL);
				[sendlock unlock];
				[self performSelectorOnMainThread:@selector(onRecvTimeOut:) withObject:tmpstr waitUntilDone:NO];
			}
		}
		sleep(1);
	};
	[pool release];
}

-(void)onRecvTimeOut:(NSString *)indexstr
{
	[timeoutlock lock];
	ntimeoutnum++;
	[timeoutlock unlock];
	if(indexstr && [indexstr length])
	{
		NSRange range=[indexstr rangeOfString:@":"];
		if(range.location!=NSNotFound && range.location < [indexstr length])
		{
			int nobjindex=[[indexstr substringToIndex:range.location] intValue];
			int nreqIndex=[[indexstr substringFromIndex:(range.location+range.length)] intValue];
			
			if(nreqIndex!=TDX_CHB)
			{
				ParseRecv *pParse=[ParseRecv new];
				pParse.bsucflag=NO;
				pParse.psErrorSign=[[NSString alloc]  initWithFormat:@"%@",@"T"];
				[pParse.psErrorSign release];
				pParse.psErrorNum=[[NSString alloc]  initWithFormat:@"%@",@"-100"];
				[pParse.psErrorNum release];
				pParse.psErrorData=[[NSString alloc]  initWithFormat:@"%@",@"接收应答超时或网络已断开"];
				[pParse.psErrorData release];
				[areceiver OnReceive:((breloginflag && nreqIndex==TDX_KHXY)?loginwindindex:nobjindex) reqid:nreqIndex parser:pParse];
				[pParse release];
			}
		}
	}
    if([sendqueue count])
    {
        AsyncSendData *pnewdata=[sendqueue objectAtIndex:0];
        if(pnewdata)
        {
            if(pnewdata.nreqIndex==TDX_SSLTOUCH || pnewdata.nreqIndex==TDX_SSLSHAKE)
                [sendqueue removeObjectAtIndex:0];
        }
    }
	
	if(brecvingflag==NO && breloginflag==NO)
		[self sendnextreq];
}

-(NSString *)getMacAddress
{
	char* macAddress= (char*)malloc(18);
	int  success;
	struct ifaddrs * addrs;
	struct ifaddrs * cursor;
	const struct sockaddr_dl * dlAddr;
	const unsigned char* base;
	int i;
	
	success = (getifaddrs(&addrs) == 0);
	if (success) {
		cursor = addrs;
		while (cursor != 0) {
			if ( (cursor->ifa_addr->sa_family == AF_LINK)
				&& (((const struct sockaddr_dl *) cursor->ifa_addr)->sdl_type == 0x6) && strcmp("en0",  cursor->ifa_name)==0 ) {
				dlAddr = (const struct sockaddr_dl *) cursor->ifa_addr;
				base = (const unsigned char*) &dlAddr->sdl_data[dlAddr->sdl_nlen];
				strcpy(macAddress, ""); 
				for (i = 0; i < dlAddr->sdl_alen; i++) {
					char partialAddr[3];
					sprintf(partialAddr, "%02X", base[i]);
					strcat(macAddress, partialAddr);
					
				}
			}
			cursor = cursor->ifa_next;
		}
		
		freeifaddrs(addrs);
	}    
	NSString *strmac=[[[NSString alloc] initWithFormat:@"%s",macAddress] autorelease];
	free(macAddress);
	
	return strmac;
}
@end
