//////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2006 - All Rights Reserved
//  模块名称: thashbase
//  创建日期: 2006/08/14
//  代码编写: HASH算法基类
//  功能说明: 
//  引用示例: 
//  修改记录:
//////////////////////////////////////////////////////////////////////////
#ifndef __THASH_BASE__H__
#define __THASH_BASE__H__
#include "talgobase.h"

//////////////////////////////////////////////////////////////////////////
// HASH算法基类
class THashModule : public TAlgoBase
{
public:
	THashModule() {}
	virtual ~THashModule() {}
	virtual void Update(const byte *input, unsigned int length) =0;
	virtual void Final(byte *digest) =0;
	virtual unsigned int DigestSize() const =0;
	virtual void CalculateDigest(byte *digest, const byte *input, int length)
		{Update(input, length); Final(digest);}
};

template <class T> class TIteratedHash : public THashModule
{
public:
	TIteratedHash(unsigned int blockSize, unsigned int digestSize);
	~TIteratedHash();
	void Update(const byte *input, unsigned int length);

	typedef T HashWordType;

protected:
	void PadLastBlock(unsigned int lastBlockSize, byte padFirst=0x80);
	virtual void Init() =0;
	virtual void HashBlock(const T *input) =0;

	unsigned int blockSize;
	word32 countLo, countHi;	// 64-bit bit count
	TSecBlock<T> data;			// Data buffer
	TSecBlock<T> digest;			// Message digest
};


#endif
