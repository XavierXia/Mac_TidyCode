//////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2006 - All Rights Reserved
//  模块名称: tsession
//  创建日期: 2006/08/14
//  代码编写: zhanglijun
//  功能说明: SESSION算法外壳类
//            目前已支持的SESSION算法包括:RC2,RC4,RC5,RC6,IDEA
//            目前尚不支持将支持的算法包括:
//  引用示例: 
//  修改记录:
//////////////////////////////////////////////////////////////////////////
#ifndef __TSESSION_RENDER__H__
#define __TSESSION_RENDER__H__
#include "talgobase.h"

//////////////////////////////////////////////////////////////////////////
// 块加密(SESSION)算法
//
//	1.RC2算法:	最大Key长128字节 Block长为8字节
//				加密时的输出缓冲区长度应大于输入长度(8+4)字节长
//	2.RC4算法:  最大Key长128字节
//				支持分块大小,但未实现
//	3.RC5算法:	ROUNDS = 12 Block长为8字节
//				加密时的输出缓冲区长度应大于输入长度(8+4)字节长
//	4.RC6算法:	ROUNDS = 20 Block长为16字节
//				加密时的输出缓冲区长度应大于输入长度(16+4)字节长
//	5.IDEA算法: Key长固定为16字节 Block长为8字节
//				加密时的输出缓冲区长度应大于输入长度(8+4)字节长
//	6.D3DES算法:    Key长无限制 Block长为24字节
//	7.D2DES算法:    Key长无限制 Block长为16字节
//	8.DDES算法:     Key长无限制 Block长为8字节
//	9.DES算法:      Key长无限制 Block长为8字节
//	10.BLOWFIS算法: Key长无限制 Block长为8字节

// 未支持的算法将支持的算法
// CAST,UFC1,UFC2,AES,TWOFISH
//	以上算法均适合于大块内存区加密
//////////////////////////////////////////////////////////////////////////

#define SESSION_ALGO_RC2		0		// RC2算法
#define SESSION_ALGO_RC4		1		// RC4算法(暂不支持)
#define SESSION_ALGO_RC5		2		// RC5算法
#define SESSION_ALGO_RC6		3		// RC6算法
#define SESSION_ALGO_IDEA		4		// IDEA算法
#define SESSION_ALGO_D3DES		5		// D3DES算法
#define SESSION_ALGO_D2DES		6		// D2DES算法
#define SESSION_ALGO_DDES		7		// DDES算法
#define SESSION_ALGO_DES		8		// DES算法
#define SESSION_ALGO_BLOWFIS	9		// BLOWFISH算法
#define SESSION_ALGO_INVALID	(-1)	// 未支持的算法

class SECURITY_IMP TSessionRender
{
public:
	TSessionRender();
	virtual ~TSessionRender();
	BOOL SelectAlgo(int nAlgoType);
	BOOL UpdateSessionKey(BYTE* lpSessionKey,int nKeyLength);
	int GetAlgo();
	const char* GetAlgoStr();
	const char* PeekSessionKey();
	int EncryptBuf(const BYTE* inBuf,unsigned int inLen,BYTE* outBuf=NULL,unsigned int outLen=UINT_MAX);
	int DecryptBuf(const BYTE* inBuf,unsigned int inLen,BYTE* outBuf=NULL,unsigned int outLen=UINT_MAX);
private:
	int m_nType;
	CHAR m_szSessionKey[128+1];
	TAlgoBase* m_pAlgo;
};

// 典型SESSION提示串以及提示
// static const char* SESSION_STR[4]  = {_ANSI("RC2算法"),_ANSI("RC5算法"),_ANSI("RC6算法"),_ANSI("IDEA算法")};
//static const int   SESSION_TYPE[4] = {SESSION_ALGO_RC2,SESSION_ALGO_RC5,SESSION_ALGO_RC6,SESSION_ALGO_IDEA};
// 典型SESSION位数提示串以及位数
// static const char* SESSION_KEYLEN_STR[5] =  {_ANSI("64位"),_ANSI("128位"),_ANSI("256位"),_ANSI("512位"),_ANSI("1024位")};
// static const short SESSION_KEYLEN_INT[5] =  {8,16,32,64,128};

#endif
