//////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2007 - All Rights Reserved
//  模块名称: clibfixedalloc
//  创建日期: 2003/05/26
//  代码编写: zhanglijun
//  功能说明: 可用空间表支持类
//            可用空间表的支持可以避免小片内存的重复分配从而最大程度
//            的提高程序运行的性能以及减少由于频繁申请和释放带来的大量
//            的内存碎片。
//  引用示例: 
//  修改记录:
//////////////////////////////////////////////////////////////////////////
#ifndef __CLIB_FIXEDALLOC__H__
#define __CLIB_FIXEDALLOC__H__
#if _MSC_VER > 1000
#pragma once
#endif

class COLLECTION_IMP TClibFixedAlloc
{
public:
	TClibFixedAlloc(UINT cbElement,UINT nMaxInPlex=64);
	virtual~TClibFixedAlloc();
	UINT GetAllocSize() { return m_cbElement; }
public:
	void* Alloc();					// 从可用空间表中分配出一个大小为cbElement的单元
	void Free(void* p);				// 释放从可用空间表中申请的单元(目前申请的内存并不释放)
	void FreeAll();					// 释放全部可用空间表中的单元并释放内存
protected:
	struct CNode
	{	CNode* pNext;				// 可用空间表的下一个位置
	};
	UINT m_cbElement;				// 数据单元大小
	UINT m_nMaxInPlex;				// 每次分配的数据单元个数
	struct TClibPlex* m_pBlocks;	// 数据块列表
	CNode* m_pNodeFree;				// 可用空间表(若为NULL则表明无可用单元可用)
	CRITICAL_SECTION m_protect;		// 链表互斥对象
};

#endif
