//
//  ParseRecv.h
//  tdxiphone
//
//  Created by 魏 文敏 on 10-1-21.
//  Copyright 2010 武汉. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "struct.h"
#import "macro.h"
#import <string.h>
#import "des.h"

@interface ParseRecv : NSObject {
	BOOL bsucflag;//应答成功，失败标志
	short nrownum ;//记录行数
	short ncolnum;//字段个数
	short  nvisiblecolnum;//可视字段个数
	NSMutableArray *sData;//NSMutableArray---NSString
	NSMutableArray *sFieldColstr;//RecvField
	NSString * psErrorSign;
	NSString * psErrorNum;//NSString
	NSString * psErrorData;//NSString
	NSMutableDictionary *coldict;//储存字段索引
	UInt64 sessionID;
	int nJls;
	int  rawlen;
	int  compresslen;
	char bencrypted,bcompressed;
	BOOL  btipflag;
	int   m_nqsid;
    int   nreqindex;
}
@property(nonatomic) int nreqindex;
@property(nonatomic) int m_nqsid;
@property(nonatomic) BOOL btipflag;
@property(nonatomic) char bencrypted;
@property(nonatomic) char bcompressed;
@property(nonatomic) int rawlen;
@property(nonatomic) int compresslen;
@property(nonatomic) int nJls;
@property(nonatomic) UInt64 sessionID;
@property (nonatomic,retain) NSMutableArray *sData;
@property (nonatomic,retain) NSMutableArray *sFieldColstr;
@property (nonatomic) BOOL bsucflag;
@property (nonatomic) short nrownum;
@property (nonatomic) short ncolnum;
@property(nonatomic) short nvisiblecolnum;
@property (nonatomic,retain) NSString *psErrorNum;
@property (nonatomic,retain) NSString *psErrorData;
@property(nonatomic,retain) NSMutableDictionary *coldict;
@property(nonatomic,retain) NSString *psErrorSign;

-(int)parseit:(NSData *)recvdata;
-(int)getRecvJx:(NSString *)theString;
-(int)setField;
-(NSString *)getFieldData:(int)nrow fieldFlag:(int)nFlag;
-(NSMutableArray * )getItemData:(NSMutableArray *)theData Index:(int)nRow TDX_Choise:(int)nChoise;
-(NSMutableArray * )getItemData1:(NSMutableArray *)theData Index:(int)nRow TDX_Choise:(int)nChoise withflag:(BOOL *)bflag;
-(NSMutableArray * )getItemData2:(NSMutableArray *)theData Index:(int)nRow TDX_Choise:(int)nChoise withclientinfo:(ClientInfo *)pclientinfo withzjgf:(ZjgfInfoClass *)zjgfclass;
-(char *)GetSFieldColStr:(int)index;
-(NSColor *)GetUIColorFromMmbz:(NSString *)mmbz;
-(NSColor *)GetUIColorFromfdyk:(float )fdyk;
-(NSColor *)GetUIColorFromJjbs:(int )jjbs;
-(NSColor *)GetUIColorFromBZ:(int)nbz;
-(NSString *)GetBzStr:(int)nbz;
//解密，解压
-(NSString *)getDecrypt:(NSMutableData *) theData BodyFlag:(int)flag ;
-(NSString *)getDepress:(NSMutableData *) theData  BodyFlag:(int)flag RawLength:(int) rawLen;

-(int)getTdxIdIndex:(int)ntdxid;
-(BOOL)IsTimeOut;
-(BOOL)IsTimeOut2;
-(void)generror;
-(BOOL) cleanHalfCharacter:(unsigned char*) sz len:(long) nlenth;
-(NSMutableDictionary *)getAttributes:(NSString *)_fontName fontSize:(CGFloat)_fontSize theColor:(NSColor *)_theColor theAliment:(int)_theAliment;

@end
