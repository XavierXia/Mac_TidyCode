//////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2006 - All Rights Reserved
//  ģ������: SESSION�Ự����
//  ��������: 2006/08/14
//  �����д: SESSION�㷨����
//  ����˵��: 
//  ����ʾ��: 
//  �޸ļ�¼:
//////////////////////////////////////////////////////////////////////////
#ifndef __TSESSION_BASE__H__
#define __TSESSION_BASE__H__
#include "talgobase.h"

//////////////////////////////////////////////////////////////////////////
// SESSION�㷨����
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
