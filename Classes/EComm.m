//
//  EComm.m
//  tdxiphone
//
//  Created by 魏 文敏 on 09-12-24.
//  Copyright 2009 武汉. All rights reserved.
//

#import "EComm.h"

#define DEST_IP "183.62.98.26"
#define DEST_PORT 7709

@implementation EComm

@synthesize readData,dataCondition,myDelegate,mygetDataDelegate,errorFlag,bconnflag;
@synthesize asyncSocket,areceiver,connFlag,ntimeoutnum,menuDelegate,initFlag;

- (id) init
{
	self = [super init];
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	their_addr.sin_family = AF_INET;
    their_addr.sin_len         = sizeof(struct sockaddr_in);
    their_addr6.sin6_family=AF_INET6;
    their_addr6.sin6_len       = sizeof(struct sockaddr_in6);
	signal(SIGPIPE, SIG_IGN);
	dataCondition=  [[NSCondition alloc] init];
	
    if (self != nil) {
//		if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
//		{
//			perror("socket");
//			exit(1);
//		}
//		else{
//			their_addr.sin_port = htons(DEST_PORT);
//			their_addr.sin_addr.s_addr = inet_addr(DEST_IP);
//			bzero(&(their_addr.sin_zero), 8);
//		}
	
		
		reqInfo.theVersion = 0;
		reqInfo.theCompressed = 0;
		reqInfo.theEncrypted = 0;
		reqInfo.isMobile = 0;
		reqInfo.theReserved = 0;
		
		errorFlag = YES;
		
		sendqueue=[[NSMutableArray alloc] initWithCapacity:100];
		areceiver=[[AsyncRecver alloc] init];
		brecvingflag=NO;
		bexitflag=NO;
		bconnflag=NO;
		bfirstConnflag = YES;
		balertflag = NO;
		reconnFlag = NO;
		initFlag = NO;
		isHttpProxyConn= NO;
		
		sendlock=[[NSCondition alloc] init];
		timeoutlock=[[NSCondition alloc] init];
		recvdatalock=[[NSCondition alloc] init];
		
		
		
		m_nobjIndex=0;
		m_nreqIndex=0;
		ntimeoutnum=0;
		
		recvdata=nil;
		m_ntotallen=0;
		m_nlastlen=0;
		
		njobtimeout=8;
		m_sendtime=time(NULL);
		[NSThread detachNewThreadSelector:@selector(processtimeout) toTarget:self withObject:nil];
		
	}
	return self;
}


- (void) dealloc
{
	bexitflag = YES;
	[sendqueue release];
	[asyncSocket release];
	[areceiver release];
	
	[readData release];
	[dataCondition release];
	close(sockfd);
	[super dealloc];
}

-(void)processtimeout{
	NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
	while(!bexitflag)
	{
			if(brecvingflag || bconnflag)
			{
				int ntimeout=njobtimeout;
				if(time(NULL)-m_sendtime>ntimeout || ([mygetDataDelegate IsNetWorkOk]==NO))
				{
					[sendlock lock];
					if(bconnflag==NO)
					{
						if ([sendqueue count] >0) {
							AsyncSendData *pnewdata=[sendqueue objectAtIndex:0];
							if(pnewdata)
							{
								if(pnewdata.bsended)
									[pnewdata release];
								[sendqueue removeObjectAtIndex:0];
							}
						}
						else {
							;
						}

						
					}
					NSString *tmpstr=[NSString stringWithFormat:@"%i:%i",m_nobjIndex,m_nreqIndex];
					brecvingflag=NO;
					[recvdata release];
					recvdata=nil;
					m_nlastlen =0;
					m_ntotallen = 0;
					if (bconnflag) {
						bconnflag = NO;
					}
					m_sendtime=time(NULL);
					[sendlock unlock];
					[self performSelectorOnMainThread:@selector(onRecvTimeOut:) withObject:tmpstr waitUntilDone:NO];
				}
			}
			else {
			}
	
		sleep(1);
	};
	[pool release];
}

-(void)onRecvTimeOut:(NSString *)indexstr
{

	if(indexstr && [indexstr length])
	{
		NSRange range=[indexstr rangeOfString:@":"];
		if(range.location!=NSNotFound && range.location < [indexstr length])
		{
			HqResultData * hqResult = [[HqResultData alloc] init];
	
			hqResult.receiveLen = 0;
			hqResult.resultStat = DATARESULT_TIMEOUT;
			[areceiver OnReceive:m_nobjIndex reqid:m_nreqIndex assID:0 hqResult:hqResult];
			[hqResult release];

			
			if (!balertflag) {
				[self clearAllRequest];
				[timeoutlock lock];
				ntimeoutnum++;
				[timeoutlock unlock];
				
				NSDateFormatter *dateFormatter=[[[NSDateFormatter alloc] init]autorelease]; 
				[dateFormatter setDateFormat:@"HH-mm-ss"];
				NSString * localTime = [dateFormatter stringFromDate:[NSDate date]];
				NSArray * tempArray = [localTime componentsSeparatedByString:@"-"];	
				int nowHour,nowMinute,nowSec;
                if([tempArray count]<3)
                {
                    nowHour=0;
                    nowMinute=0;
                    nowSec=0;
                }
                else
                {
                    nowHour = [[tempArray objectAtIndex:0]intValue]+[mygetDataDelegate getHourDiff];
                    nowMinute = [[tempArray objectAtIndex:1]intValue]+[mygetDataDelegate getMinuteDiff];
                    nowSec = [[tempArray objectAtIndex:2]intValue]+[mygetDataDelegate getSecondDiff];
                }
				
				if (nowSec > 59) {
					nowMinute = nowMinute + 1;
				}
				if (nowMinute > 59) {
					nowMinute = nowMinute -60;
					nowHour = nowHour+1;
				}
				
				int checkInt = nowHour * 60+nowMinute;
				
				if (ntimeoutnum == 1) {
					if ((checkInt > 510) && (checkInt <540)) {
						if (!initFlag) {
							if ([menuDelegate respondsToSelector:@selector(afterReconnRefresh)]) {
								[menuDelegate afterReconnRefresh];
							}
						}
						else {
                            balertflag = NO;
                            if ([menuDelegate respondsToSelector:@selector(afterReconnRefresh)]) {
                                [menuDelegate afterReconnRefresh];
                            }
						}

					}
					else {
                        balertflag = NO;
                        if ([menuDelegate respondsToSelector:@selector(afterReconnRefresh)]) {
                            [menuDelegate afterReconnRefresh];
                        }
					}
				}
				else if (ntimeoutnum >= 2){
					if ([mygetDataDelegate IsNetWorkOk]==NO) {
						NSAlert* alert = [NSAlert alertWithMessageText: @"提示"
														 defaultButton: @"确定"
													   alternateButton: nil
														   otherButton: nil
											 informativeTextWithFormat: @"未检测到可用网络,请检查网络设置"];
						balertflag = YES;
						[alert setDelegate:self];
						NSInteger result = [alert runModal];
						[self handleResult:alert withResult:result];	
					}
					else {
						if ((checkInt > 510) && (checkInt <540)){
							if (!initFlag) {
								initFlag= YES;
								[menuDelegate showInitConnTips];
							}
							else {
								TradeSite *pSite = [mygetDataDelegate getNextHqLoginSite];
								if (pSite == nil) {
									;
								}
								else {
								}
							}

							
						}else {
							TradeSite *pSite = [mygetDataDelegate getNextHqLoginSite];
							if (pSite == nil || [mygetDataDelegate IsHttpProxyWork]) {
								;
							}
							else {
                                
                                //自动连接下一个行情服务器
                                [mygetDataDelegate dealChangeNextHqSite];
                                if ([menuDelegate respondsToSelector:@selector(afterReconnRefresh)]) {
                                    [menuDelegate afterReconnRefresh];
                                }
							}
						}

						
						
					}

					
					

					
					
				}
			}
			

		}
	}
	
	if(brecvingflag==NO)
		[self sendnextreq];
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
	connFlag = NO;
	[sendlock unlock];
	
}

#pragma mark alert相关
-(void)handleResult:(NSAlert *)alert withResult:(NSInteger)result
{
	switch(result)
	{
		case NSAlertDefaultReturn:
			balertflag = NO;
			if ([menuDelegate respondsToSelector:@selector(afterReconnRefresh)]) {
				[menuDelegate afterReconnRefresh];
			}
			break;
			
		case NSAlertAlternateReturn:
			break;
			
		case NSAlertOtherReturn:
			break;
            
        default:
            break;
	}
	
}

-(void)handleResultEx:(NSAlert *)alert withResult:(NSInteger)result
{
	switch(result)
	{
		
		case NSAlertDefaultReturn:
			balertflag = NO;

			
			[mygetDataDelegate dealChangeNextHqSite];
			if ([menuDelegate respondsToSelector:@selector(afterReconnRefresh)]) {
				[menuDelegate afterReconnRefresh];
			}
			break;
			
		case NSAlertAlternateReturn:
			balertflag = NO;
			if ([menuDelegate respondsToSelector:@selector(afterReconnRefresh)]) {
				[menuDelegate afterReconnRefresh];
			}
			break;
			
		case NSAlertOtherReturn:
			break;
            
        default:
            break;
	}
	
}

-(void)closeServer{
	if (asyncSocket != nil) {
		[asyncSocket disconnectAfterReadingAndWriting];
		[asyncSocket release];
		asyncSocket=nil;
	}
}

-(int)connectToServer
{
	if (bconnflag) {
		return -1;
	}
	if (asyncSocket != nil) {
		[asyncSocket disconnectAfterReadingAndWriting];
		[asyncSocket release];
		asyncSocket=nil;
	}
	bconnflag=YES;
	
	asyncSocket = [[AsyncSocket alloc] initWithDelegate:self]; 
	NSError *err = nil; 
	
	
	
	if ([mygetDataDelegate IsHttpProxyWork]) {
		NSLog(@"http proxy");
		
		
		
		if ([[mygetDataDelegate getHttpProxyAddress] length]  == 0) {
			bconnflag = NO;
			return -2;
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
                    connFlag = NO;
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
                connFlag = NO;
                return -1;
            } 
            else 
            {
                [asyncSocket readDataWithTimeout:-1 tag:0];
            }
        }
		return -3;
	}
	
	TradeSite *pSite=[mygetDataDelegate GetHqLoginSite:YES];
	if(pSite==nil)
	{
		return -1;
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
                connFlag = NO;
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
        
        NSLog(@"fast result is %@  ,%@ ",pSite.ip,strip);
        
        
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

            [asyncSocket release];
            asyncSocket=nil;
            connFlag = NO;
            return -1;
        } 
        else 
        {
            [asyncSocket readDataWithTimeout:-1 tag:0];
        }
    }
	return 1;
}

//异步发送
-(BOOL)AsyncSendData:(NSData *) lBuf length:(short)lBufLength withobjIndex:(short)nobjIndex withreqIndex:(short)nreqIndex
{
	
	BOOL bflag=(brecvingflag || [sendqueue count] );

	NSMutableData *newdata = [[NSMutableData alloc] init];
	
	
	[newdata appendBytes:(void *)&reqInfo length:sizeof(reqInfo)];
	[newdata appendBytes:(void *)&nobjIndex length:sizeof(short)];
	[newdata appendBytes:(void *)&nreqIndex length:sizeof(short)];
	char priority = 1;
	[newdata appendBytes:(void *)&priority length:sizeof(priority)];
	[newdata appendBytes:(void *)&lBufLength length:sizeof(lBufLength)];
	[newdata appendBytes:(void *)&lBufLength length:sizeof(lBufLength)];
	[newdata appendData:lBuf];
	
	
	
	
	
	AsyncSendData *pdata=[[AsyncSendData alloc] initWithData:nobjIndex reqIndex:nreqIndex data:newdata];
	
	if ([mygetDataDelegate IsHttpProxyWork]) {
		if(!bflag)
		{
			errorFlag = NO;
			if (connFlag) {
				
			}
			else {
				int tempInt = [self connectToServer];
				if(tempInt == -2){
					NSAlert* alert = [NSAlert alertWithMessageText: @"提示"
													 defaultButton: @"确定"
												   alternateButton: nil
													   otherButton: nil
										 informativeTextWithFormat: @"请设置代理服务器地址!"];
					[alert runModal];
				}
				else if(tempInt == -3){
				}
				
				m_nobjIndex=nobjIndex;
				m_nreqIndex=nreqIndex;
			}

			
			if (isHttpProxyConn) {
				[sendlock lock];
				[sendqueue addObject:pdata];
				pdata.bsended=YES;
				m_sendtime=time(NULL);
				brecvingflag=YES;
				m_nobjIndex=nobjIndex;
				m_nreqIndex=nreqIndex;
				[asyncSocket writeData:newdata withTimeout:-1 tag:0];
				[sendlock unlock];
			}
			else {
				[sendlock lock];
				[sendqueue addObject:pdata];
				[sendlock unlock];
			}

			
			
		}
		else {
			[sendlock lock];
			int count=[sendqueue count];
			AsyncSendData *pdata1=nil;
			int tempInt;
			if(brecvingflag)
				tempInt = 1;
			else 
				tempInt = 0;
			
			for(int i=count-1;i>=tempInt;i--)
			{
				pdata1=[sendqueue objectAtIndex:i];
				[pdata1 release];
				[sendqueue removeObjectAtIndex:i];
			}
			[sendqueue addObject:pdata];
			[sendlock unlock];
		}

	}
	else {
		if(!bflag)
		{
			errorFlag = NO;
			if (connFlag) {
				
			}
			else {
				if ([self connectToServer] == -1) {
					errorFlag = YES;
				}
				
			}
			
			
			
			[sendlock lock];
			[sendqueue addObject:pdata];
			pdata.bsended=YES;
			m_sendtime=time(NULL);
			brecvingflag=YES;
			m_nobjIndex=nobjIndex;
			m_nreqIndex=nreqIndex;
			[asyncSocket writeData:newdata withTimeout:-1 tag:0];
			
			[sendlock unlock];
		}
		else 
		{
			[sendlock lock];
			int count=[sendqueue count];
			AsyncSendData *pdata1=nil;
			int tempInt;
			if(brecvingflag)
				tempInt = 1;
			else 
				tempInt = 0;
			
			for(int i=count-1;i>=tempInt;i--)
			{
				pdata1=[sendqueue objectAtIndex:i];
				[pdata1 release];
				[sendqueue removeObjectAtIndex:i];
			}
			[sendqueue addObject:pdata];
			[sendlock unlock];
		}
	}

	

	
	
	if(!bflag)
	{
		[asyncSocket readDataWithTimeout:-1 tag:0];
	}
	if (errorFlag) {
		return NO;
	}
	return YES;
}

-(BOOL)sendnextreq
{
	if([sendqueue count])
	{
		if (!connFlag) {
			[self connectToServer];
			return NO;
		}
		[sendlock lock];
        AsyncSendData *pnewdata=nil;
        if([sendqueue count])
            pnewdata=[sendqueue objectAtIndex:0];
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
	else {
	}

	[asyncSocket readDataWithTimeout:-1 tag:0];//结尾调用
	return YES;
}




//异步接收
-(void) onSocket:(AsyncSocket *)sock didReadData:(NSData *)data withTag:(long)tag
{
	BOOL netError = NO;
	BOOL timeoutFlag = NO;
	short mainID;
	short assisID;
	short getLen=0;
	short recLen = 0;
	short req = 0;
	NSLog(@"rec Data");
	NSMutableData *recData =nil;
	[recvdatalock lock];
	BOOL brecvdataflag=(recvdata!=nil);
	if(brecvdataflag)
		[recvdata appendData:data];
	else {
		recvdata=[[NSMutableData alloc] initWithData:data];
	}
	
	if ([mygetDataDelegate IsHttpProxyWork]) {
		if (!isHttpProxyConn) {
			NSString *tempStringEx = [[NSString alloc] initWithData:recvdata encoding:CFStringConvertEncodingToNSStringEncoding (kCFStringEncodingGB_18030_2000)];
			
			
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
				recData=recvdata;
				m_nlastlen=m_ntotallen;
			}
			else 
			{
				recData=recvdata;
				m_nlastlen=m_ntotallen;
			}
		}
		else 
		{
			recData=recvdata;
			m_ntotallen=nrtotallen;
			m_nlastlen=0;
		}
	}
	else
	{
		recData=recvdata;
		m_ntotallen=nrtotallen;
		m_nlastlen=0;
	}
	
	if ([recData length] >0 ) 
	{
		if ([recData length] < 10) {
			[asyncSocket readDataWithTimeout:-1 tag:0];//结尾调用
			return;
		}
		
		
		[recData getTdxBytes:&ansInfo range:NSMakeRange(4, sizeof(ansInfo))];
		
		int buf = 5;
		
		
		
		[recData getTdxBytes:&mainID range:NSMakeRange(buf, sizeof(mainID))];
		buf +=sizeof(mainID);
		[recData getTdxBytes:&assisID range:NSMakeRange(buf, sizeof(assisID))];
		buf = 10;
		
		[recData getTdxBytes:&req range:NSMakeRange(buf, sizeof(req))];
		buf +=sizeof(req);
		[recData getTdxBytes:&getLen range:NSMakeRange(buf, sizeof(getLen))];
		buf +=sizeof(getLen);
		[recData getTdxBytes:&recLen range:NSMakeRange(buf, sizeof(recLen))];
		
		
		////判断是否收完//////
		if ([recData length] == getLen + 16 ) {
			NSLog(@"rec done");
			//recLen = 0;
			if (readData != nil) {
				readData = nil;
			}
			if(ansInfo.theCompressed)
			{
				unsigned const char * tempChar = [recData bytes];
				unsigned char rawChar[recLen];
				unsigned long  getLength = getLen;
				unsigned long  rawLength = recLen;
				uncompress(rawChar, &rawLength, tempChar+16, getLength);
				readData = [NSMutableData dataWithBytes:tempChar length:16];
				[readData appendBytes:rawChar length:recLen];
			}
			else	
				readData = [NSMutableData dataWithData:recData];
		}
		else {
			m_nlastlen=[recData length];
			m_ntotallen=getLen+16;
			if (m_nlastlen > m_ntotallen) {
				[recvdata release];
				recvdata=nil;
				m_nlastlen =0;
				m_ntotallen = 0;
			}
			[asyncSocket readDataWithTimeout:-1 tag:0];//结尾调用
			return;
		}
	}
	else {
		netError  = YES;
	}
	
	if(ntimeoutnum>0)
	{
		[timeoutlock lock];
		ntimeoutnum=0;
		[timeoutlock unlock];
	}

	brecvingflag= NO;
	HqResultData * hqResult;
	if (netError) {
		//NSLog(@"nSelRet is %i",nSelRet);
		hqResult = [[HqResultData alloc] init];
		if (timeoutFlag) {
			hqResult.resultStat = DATARESULT_TIMEOUT;
		}
		else {
			hqResult.resultStat = DATARESULT_NETERROR;
		}
		errorFlag = YES;
		
	}
	else {
		hqResult = [[HqResultData alloc] init];
		if (readData != nil) {
			hqResult.receiveLen = [readData length];
			
			
			hqResult.resultStat = DATARESULT_NORMAL;
			hqResult.resultData = readData;
		}
		else {
			hqResult.receiveLen = 0;
			hqResult.resultStat = DATARESULT_TIMEOUT;
			errorFlag = YES;
		}
		
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
	[areceiver OnReceive:mainID reqid:req assID:assisID hqResult:hqResult];
	[hqResult release];
	[recvdata release];
	recvdata=nil;
	[self sendnextreq];
}

//断线
- (void)onSocketDidDisconnect:(AsyncSocket *)sock{
	NSLog(@"onSocketDidDisconnect");
	connFlag= NO;
	
	if (asyncSocket != nil) {
		[asyncSocket release];
		asyncSocket=nil;
	}
	
	if ([mygetDataDelegate IsHttpProxyWork]) {
		isHttpProxyConn = NO;
	}
	
	[sendlock lock];
	int count=[sendqueue count];
	AsyncSendData *pdata1=nil;
	int tempInt =0;
	if(brecvingflag)
		tempInt = 1;
	else 
		tempInt = 0;
	
	for(int i=count-1;i>=tempInt;i--)
	{
		pdata1=[sendqueue objectAtIndex:i];
		[pdata1 release];
		[sendqueue removeObjectAtIndex:i];
	}
	[sendlock unlock];
	
	if ([menuDelegate respondsToSelector:@selector(showConnTips)]) {
		sleep(3);
		[menuDelegate showConnTips];
	}
}

-(void) onSocket:(AsyncSocket *)sock didConnectToHost:(NSString *)host port:(UInt16)port{
	NSLog(@"didConnectToHost");
	NSLog(@"Host is %@ and port is %hu",host,port);
	connFlag=YES;
	bconnflag = NO;
	bfirstConnflag = NO;
	
	if ([mygetDataDelegate IsHttpProxyWork]) {
		if (!isHttpProxyConn) {
			
			TradeSite *pSite=[mygetDataDelegate GetHqLoginSite:YES];
			NSMutableData *newdata = [[NSMutableData alloc] init];
			
			NSString * tempString = [NSString stringWithFormat:@"CONNECT %@:%i HTTP/1.1\r\n",pSite.ip,pSite.nport];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString  = [NSString stringWithFormat:@"User-Agent: Mozilla/4.0\r\n"];
			[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
			tempString = [NSString stringWithFormat:@"Connection: Keep-Alive\r\n" ];
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
	else {
		if ([menuDelegate respondsToSelector:@selector(showConnTips)]) {
			[menuDelegate showConnTips];
		}
		
		if (!brecvingflag) {
			[self sendnextreq];
		}
	}

	
}

-(void)sendData:(NSData *)sendData Length:(int)_length{
	int nSent = 0;
	while(nSent < _length)
	{
		ssize_t dataSended = send(sockfd, [sendData bytes], [sendData length], 0);
		if(dataSended > -1){
			
			//NSLog([NSString stringWithFormat:@"dataSended is %i",dataSended]);
			nSent += dataSended;
			if(nSent == _length)
			{
				NSLog(@"Datas have been sended over!");
			}
			
		}
	}	
}


-(HqResultData *)sendIt:(NSData *) lBuf length:(short) lBufLength
{
		[dataCondition lock];
	
	
	NSMutableData *newdata = [[NSMutableData alloc] init];
	 
	
	[newdata appendBytes:(void *)&reqInfo length:sizeof(reqInfo)];
	short main = 1;
	[newdata appendBytes:(void *)&main length:sizeof(main)];
	short assis = 1;
	[newdata appendBytes:(void *)&assis length:sizeof(assis)];
	char priority = 1;
	[newdata appendBytes:(void *)&priority length:sizeof(priority)];
	[newdata appendBytes:(void *)&lBufLength length:sizeof(lBufLength)];
	[newdata appendBytes:(void *)&lBufLength length:sizeof(lBufLength)];
	[newdata appendData:lBuf];
	
	NSLog(@"sending data length is %i",[newdata length]);
	
	if (!errorFlag) {
		
	}
	else{//出现错误重新连接
		close(sockfd);
		sockfd = socket(AF_INET, SOCK_STREAM, 0);
		int i = [self connectToServer];
		
		if(i == 0)
		{
			errorFlag = NO;
		}
		else{
			[newdata release];
			HqResultData * hqResult = [[HqResultData alloc] init];
			hqResult.resultStat = DATARESULT_CONNERROR;
			errorFlag = YES;
			[dataCondition unlock];
			return [hqResult autorelease];
		}
	}
	
	
	
	
	
	fd_set fdW;
	struct timeval timeout;
	timeout.tv_sec = 10;
	timeout.tv_usec = 0;
	BOOL netError = NO;
	BOOL timeoutFlag = NO;
	int nSelRet;
	
	for (; ; ) {
		FD_ZERO(&fdW);
		FD_SET(sockfd,&fdW);
		nSelRet = select(sockfd+1, NULL, &fdW, NULL, &timeout);
		
		if(nSelRet != 1 || !FD_ISSET(sockfd,&fdW)){
			NSLog(@"network is bad");
			netError = YES;
			break;
		}
		else{
			NSLog(@"network is alive send");

			
			int nSent = 0;
			while((!netError)&&(nSent < [newdata length]))
			{
				ssize_t dataSended = send(sockfd, [newdata bytes], [newdata length], 0);
				
				
				if(dataSended <0)
				{
					netError = YES;
				}
				else{
					nSent += dataSended;
					if(nSent == [newdata length])
					{
						break;
					}
					
				}
			}
			break;
		}
	}
	[newdata release];
	if (netError) {
		errorFlag = YES;
		HqResultData * hqResult = [[HqResultData alloc] init];
		hqResult.resultStat = DATARESULT_NETERROR;
		
		[dataCondition unlock];
		return [hqResult autorelease];
	}
		
	
	
	
	timeout.tv_sec = 10;
	timeout.tv_usec = 0;

	
	for (; ; ) {
		FD_ZERO(&fdW);
		FD_SET(sockfd,&fdW);
		int nSelRet = select(sockfd+1, &fdW, NULL, NULL, &timeout);
		
		if(nSelRet != 1 || !FD_ISSET(sockfd,&fdW)){
			if (nSelRet == 0) {
				timeoutFlag = YES;
			}
			netError = YES;
			break;
		}
		else{
			char readBuffer[20*1024];
			
			if (readData != nil) {
				readData = nil;
			}
			
			int br = 0;
			short getLen=0;
			short recLen = 0;
			short req = 0;
			NSMutableData * recData;
			
			recData = [[NSMutableData alloc] init];
			while((br = recv(sockfd, readBuffer, sizeof(readBuffer), 0)) < sizeof(readBuffer))
			{
				if(recLen == 0)
				{	
					[recData appendBytes:readBuffer length:br];
					
					[recData getTdxBytes:&ansInfo range:NSMakeRange(4, sizeof(ansInfo))];
					
					
					int buf = 10;
					
					[recData getTdxBytes:&req range:NSMakeRange(buf, sizeof(req))];
					buf +=sizeof(req);
					[recData getTdxBytes:&getLen range:NSMakeRange(buf, sizeof(getLen))];
					buf +=sizeof(getLen);
					
					[recData getTdxBytes:&recLen range:NSMakeRange(buf, sizeof(recLen))];
					
					if([recData length] == (getLen + 16))
					{
						NSLog(@"rec done");
						if (readData != nil) {
							readData = nil;
						}
						if(ansInfo.theCompressed)
						{
							unsigned const char * tempChar = [recData bytes];
							unsigned char rawChar[recLen];
							unsigned long  getLength = getLen;
							unsigned long  rawLength = recLen;
							uncompress(rawChar, &rawLength, tempChar+16, getLength);
							readData = [NSMutableData dataWithBytes:tempChar length:16];
							[readData appendBytes:rawChar length:recLen];
						}
						else	
							readData = [NSMutableData dataWithData:recData];
						break;
					}	
				}else {
					[recData appendBytes:readBuffer length:br];
					
					if([recData length] == (getLen+16))
					{
						if(ansInfo.theCompressed)
						{
							unsigned const char * tempChar = [recData bytes];
							unsigned char rawChar[recLen];
							unsigned long  getLength = getLen;
							unsigned long  rawLength = recLen;
							uncompress(rawChar, &rawLength, tempChar+16, getLength);
							readData = [NSMutableData dataWithBytes:tempChar length:16];
							[readData appendBytes:rawChar length:recLen];
						}
						else	
							readData = [NSMutableData dataWithData:recData];
						break;
					}	
					
				}
				
			}
			[recData release];
			break;
		}
	}
		if (netError) {
		HqResultData * hqResult = [[HqResultData alloc] init];
		if (timeoutFlag) {
			hqResult.resultStat = DATARESULT_TIMEOUT;
		}
		else {
			hqResult.resultStat = DATARESULT_NETERROR;
		}
		errorFlag = YES;
		[dataCondition unlock];
		return [hqResult autorelease];
	}
	else {
		HqResultData * hqResult = [[HqResultData alloc] init];
		if (readData != nil) {
			hqResult.receiveLen = [readData length];

			
			hqResult.resultStat = DATARESULT_NORMAL;
			hqResult.resultData = readData;
		}
		else {
			hqResult.receiveLen = 0;
			hqResult.resultStat = DATARESULT_TIMEOUT;
			errorFlag = YES;
		}
		
		[dataCondition unlock];
		return [hqResult autorelease];
	}
}

-(void) dealTheData{
}

-(NSData *)getAnsData{
	return readData;
}


@end
