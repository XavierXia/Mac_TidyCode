//////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2006 - All Rights Reserved
//  模块名称: SESSION会话基类
//  创建日期: 2006/08/14
//  代码编写: SESSION算法基类
//  功能说明: 
//  引用示例: 
//  修改记录:
//////////////////////////////////////////////////////////////////////////
#ifndef __TSESSION_BASE__H__
#define __TSESSION_BASE__H__
#include "talgobase.h"

//////////////////////////////////////////////////////////////////////////
// SESSION算法基类
class TBlockTransformation : public TAlgoBase
{
public:
	TBlockTransformation() {}
	virtual ~TBlockTransformation() {}
	virtual void EncryptBlock(const byte *inBlock, byte *outBlock) =0;
	virtual void DecryptBlock(const byte *inBlock, byte *outBlock) =0;
	virtual unsigned int BlockSize()=0;
};

#endif
