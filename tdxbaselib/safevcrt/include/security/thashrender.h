//////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2006 - All Rights Reserved
//  模块名称: thash
//  创建日期: 2006/08/14
//  代码编写: zhanglijun
//  功能说明: HASH算法抽象类
//            目前已支持的HASH算法包括:MD2,MD5,SHA
//            目前尚未支持,将支持的算法包括SHA-1,RIPEMD,MDC2
//  引用示例: 
//  修改记录:
//////////////////////////////////////////////////////////////////////////
#ifndef __THASH_RENDER__H__
#define __THASH_RENDER__H__
#include "talgobase.h"

//////////////////////////////////////////////////////////////////////////
// 数字签名(HASH)算法
//  HASH算法:
//	1.MD2算法:			MD2 HASH算法
//	2.MD5算法:			MD5 HASH算法
//	3.SHA算法:			SHA HASH算法
//	4.SHA1算法:			SHA1(SHA-160) HASH算法
//	5.MD4算法:			MD4 HASH算法
//	6.MDC2算法:			MDC2 HASH算法
//	7.SHA224算法:		SHA-224 HASH算法
//	8.SHA256算法:		SHA-256 HASH算法
//	9.SHA384算法:		SHA-384 HASH算法
//	10.SHA512算法:		SHA-512 HASH算法
//	11.GOST算法:		GOST HASH算法
//	12.TIGER算法:		TIGER HASH算法
//	13.DSS算法:			TIGER HASH算法
//	14.DSS1算法:		TIGER HASH算法
//	15.RIPEMD160算法:	RIPEMD-160 HASH算法
//	16.HAVAL128算法:	HAVAL-128 HASH算法
//	17.HAVAL160算法:	HAVAL-160 HASH算法
//	18.HAVAL192算法:	HAVAL-192 HASH算法
//	19.HAVAL256算法:	HAVAL-256 HASH算法

//////////////////////////////////////////////////////////////////////////
#define HASH_ALGO_MD2		0		// MD2 HASH算法
#define HASH_ALGO_MD5		1		// MD5 HASH算法
#define HASH_ALGO_SHA		2		// SHA HASH算法
#define HASH_ALGO_SHA1		3		// SHA1(SHA-160) HASH算法
#define HASH_ALGO_MD4		4		// MD4 HASH算法(未支持)
#define HASH_ALGO_MDC2		5		// MDC2 HASH算法(未支持)
#define HASH_ALGO_SHA224	6		// SHA-224 HASH算法
#define HASH_ALGO_SHA256	7		// SHA-256 HASH算法
#define HASH_ALGO_SHA384	8		// SHA-384 HASH算法
#define HASH_ALGO_SHA512	9		// SHA-512 HASH算法
#define HASH_ALGO_GOST		10		// GOST HASH算法(未支持)
#define HASH_ALGO_TIGER		11		// TIGER HASH算法(未支持)
#define HASH_ALGO_DSS		12		// TIGER HASH算法(未支持)
#define HASH_ALGO_DSS1		13		// TIGER HASH算法(未支持)
#define HASH_ALGO_RIPEMD160	14		// RIPEMD-160 HASH算法(未支持)
#define HASH_ALGO_HAVAL128	15		// HAVAL-128 HASH算法(未支持)
#define HASH_ALGO_HAVAL160	16		// HAVAL-160 HASH算法(未支持)
#define HASH_ALGO_HAVAL192	17		// HAVAL-192 HASH算法(未支持)
#define HASH_ALGO_HAVAL256	18		// HAVAL-256 HASH算法(未支持)


class SECURITY_IMP THashRender
{
public:
	THashRender();
	virtual ~THashRender();
	BOOL  SelectAlgo(int nAlgoType);
	int   GetAlgo();
	const char* GetAlgoStr();
	BOOL Update(const BYTE *input,unsigned int length);
	BOOL Final(BYTE* hash);
	unsigned int DigestSize();
private:
	int			m_nType;
	TAlgoBase*	m_pAlgo;
};

// 典型HASH算法提示串
// static const char* HASH_STR[4]     = {_ANSI("MD2算法"),_ANSI("MD5算法"),_ANSI("SHA算法"),_ANSI("SHA1算法")};
// static const int   HASH_INT[4]     = {HASH_ALGO_MD2,HASH_ALGO_MD5,HASH_ALGO_SHA,HASH_ALGO_SHA1};

#endif
