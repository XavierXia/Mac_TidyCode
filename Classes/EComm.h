//
//  EComm.h
//  tdxiphone
//
//  Created by 魏 文敏 on 09-12-24.
//  Copyright 2009 武汉. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <zlib.h>
#import <stdio.h>
#import <stdlib.h>
#import <unistd.h>
#import <arpa/inet.h>
#import <sys/types.h>
#import <sys/socket.h>
#import <sys/fcntl.h>
#import <sys/ioctl.h>
#import <netdb.h>
#import "macro.h"
#import "struct.h"
#import "Delegate.h"
#import "AsyncSocket.h"
#import "AsyncRecv.h"
#import "GTMBase64.h"

@protocol DataSaveDelegate;

@interface EComm : NSObject<NSAlertDelegate>{
	AsyncSocket *asyncSocket;
	AsyncRecver  *areceiver;
	NSMutableArray *sendqueue;//发送队列,应答成功从队列移除 ，否则接着发送
	BOOL  brecvingflag;//是否正在接收数据
	BOOL connFlag;
	BOOL initFlag;
	BOOL bconnflag;//是否正在连接
	BOOL bfirstConnflag;//是否第一次连接
	BOOL balertflag;//是否弹出alert
	BOOL reconnFlag;//是否在自动重连
	
	NSCondition *sendlock;
	NSCondition *timeoutlock; 
	NSCondition *recvdatalock;
	
	time_t  m_sendtime;
	short  m_nobjIndex;
	short  m_nreqIndex;
	int   njobtimeout;
	
	NSMutableData *recvdata;
	int  m_ntotallen;
	int  m_nlastlen;
	
	int sockfd;
	struct sockaddr_in their_addr;
    struct sockaddr_in6 their_addr6;
	NSMutableData * readData ;
	NSCondition* dataCondition;
	ReqInfo reqInfo;
	ReqInfo ansInfo;
	id <DataSaveDelegate> myDelegate;
	BOOL errorFlag;
	id<getdataDelegate> mygetDataDelegate;
	id<SystemMenuDelegate> menuDelegate;
	
	BOOL  bexitflag;
	int   ntimeoutnum;
	BOOL  isHttpProxyConn;
}

@property (nonatomic,retain) NSMutableData * readData;
@property (nonatomic,retain) NSCondition* dataCondition;
@property BOOL errorFlag;
@property BOOL connFlag;
@property BOOL bconnflag;
@property BOOL initFlag;
@property(nonatomic, assign) id <DataSaveDelegate> myDelegate;
@property(nonatomic,assign) id<getdataDelegate> mygetDataDelegate;
@property(nonatomic,assign) id<SystemMenuDelegate> menuDelegate;
@property(nonatomic,retain) AsyncSocket *asyncSocket;
@property(nonatomic,retain) AsyncRecver  *areceiver;
@property int   ntimeoutnum;

- (int)connectToServer;
- (HqResultData * )sendIt:(NSData *) lBuf length:(short) lBufLength;
-(NSData *)getAnsData;


-(void)closeServer;
-(void)clearAllRequest;
-(BOOL)sendnextreq;
-(void) onSocket:(AsyncSocket *)sock didReadData:(NSData *)data withTag:(long)tag;//接收数据
- (void)onSocketDidDisconnect:(AsyncSocket *)sock;
-(BOOL)AsyncSendData:(NSData *) lBuf length:(short)lBufLength  withobjIndex:(short)nobjIndex withreqIndex:(short)nreqIndex;
-(void)handleResult:(NSAlert *)alert withResult:(NSInteger)result;
-(void)handleResultEx:(NSAlert *)alert withResult:(NSInteger)result;
@end

