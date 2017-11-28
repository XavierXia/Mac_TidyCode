//////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2007 - All Rights Reserved
//  模块名称: clibplex
//  创建日期: 2007/05/26
//  代码编写: zhanglijun
//  功能说明: 标准链表管理类,当前类组织一定包含若干数据项的内存块构成的链表
//            每个链表单元均是一个包含多个数据单元的连续内存,这个连续内存的
//            头部用于保存下一个数据块的位置。
//  引用示例: 
//  修改记录:
//////////////////////////////////////////////////////////////////////////
#ifndef __CLIB_PLEX__H__
#define __CLIB_PLEX__H__

// 数据块链表类
struct COLLECTION_IMP TClibPlex
{
	TClibPlex* pNext;						// 下一个数据块位置
	void* data() { return this+1; }			// 返回头部接下来的缓冲区,大小为[项目大小*每块包含的数据个数]
	static TClibPlex* PASCAL Create(TClibPlex*& head,UINT nMax,UINT cbElement);
	void FreeDataChain();
};

#endif
