//
//  ETradeComm.h
//  tdxiphone
//
//  Created by 魏 文敏 on 10-1-19.
//  Copyright 2010 武汉. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <stdio.h>
#import <stdlib.h>
#import <unistd.h>
#import <sys/types.h>
#import <arpa/inet.h>
#import <zlib.h>
#import "macro.h"
#import <netdb.h>
#import "AsyncSocket.h"
#import "AsyncRecv.h"
#import "struct.h"
#import "Delegate.h"
#import <ifaddrs.h>
#import <net/if_dl.h>
#import "GTMBase64.h"


@interface ETradeComm : NSObject {
	AsyncSocket *asyncSocket;
	struct sockaddr_in their_addr;
    struct sockaddr_in6 their_addr6;
	NSMutableData * readData ;
	BOOL m_KeepAlive;
	int httpFlag;
	int chbhttpflag;
	int  nsendcount;
	NSCondition *sendlock;
	BOOL tradeLoginFlag;
	AsyncRecver  *areceiver;
	BOOL  bexitflag;
	int    loginwindindex;
	UInt64 sessionID;
	int rawLen;
	BOOL breloginflag;//是否正在登录 
	BOOL  brecvingflag;//是否正在接收数据
	NSMutableArray *sendqueue;//发送队列,应答成功从队列移除 ，否则接着发送
	int   njobtimeout;
	time_t  m_sendtime;
	NSMutableData *recvdata;
	int  m_ntotallen;
	int  m_nlastlen;
	short  m_nobjIndex;
	short  m_nreqIndex;
	id <TradeComDelegate> myDelegate;
	id<getdataDelegate> mygetDataDelegate;
	BOOL bneedreloginflag;
	BOOL btipreloginflag;
	id<reconnectDelegate> myreconDelegate;
	id<jyLogindelegate> jyLoginDelegate;
	BOOL breconntipflag;
	NSCondition *reconlock;
	BOOL  m_bconokflag;
	NSCondition *timeoutlock; 
	NSCondition *recvdatalock;
	int   ntimeoutnum;
	time_t m_nlastrecvtime;
	BOOL m_blogout;
	NSString *m_macsstr;
	
	BOOL  isHttpProxyConn;
    BOOL bmustreconflag;
}
@property(nonatomic,retain) NSString *m_macsstr;
@property(nonatomic) BOOL m_blogout;
@property(nonatomic) BOOL breconntipflag;
@property(nonatomic,assign) id<reconnectDelegate> myreconDelegate;
@property(nonatomic) BOOL btipreloginflag;
@property(nonatomic) BOOL bneedreloginflag;
@property(nonatomic) int rawLen;
@property(nonatomic) int njobtimeout;
@property(nonatomic) BOOL breloginflag;
@property(nonatomic)UInt64 sessionID;
@property(nonatomic) int loginwindindex;
@property(nonatomic) BOOL tradeLoginFlag;
@property BOOL m_KeepAlive;
@property (nonatomic , retain) NSMutableData * readData;
@property int nsendcount;
@property (retain) NSCondition *sendlock;
@property int httpFlag,chbhttpflag;
@property(nonatomic,retain) AsyncSocket *asyncSocket;
@property(nonatomic,retain) AsyncRecver  *areceiver;
@property(nonatomic,assign) id <TradeComDelegate> myDelegate;
@property(nonatomic,assign) id<getdataDelegate> mygetDataDelegate;
@property(nonatomic,assign) id<jyLogindelegate> jyLoginDelegate;
@property BOOL m_bconokflag;

- (int)connect:(BOOL)btipflag withlastflag:(BOOL)blastflag;
-(int) getHttpFlag:(NSString *) theData;
-(BOOL)reconnect;//断线重连
-(void) onSocket:(AsyncSocket *)sock didReadData:(NSData *)data withTag:(long)tag;//接收数据
- (void)onSocketDidDisconnect:(AsyncSocket *)sock;
-(BOOL)AsyncSendData:(NSData *) lBuf length:(int)lBufLength  withobjIndex:(short)nobjIndex withreqIndex:(short)nreqIndex;
-(BOOL)relogin;
-(BOOL)sendnextreq;
-(void)processtimeout;
-(void)onRecvTimeOut:(NSString *)indexstr;
-(void)logout;
-(void)relogin2;
-(void)relogin3;
-(NSString *)getMacAddress;
-(void)clearAllRequest;
-(BOOL)IsLoginIndex:(int)nindex;
@end
