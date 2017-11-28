//////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2006 - All Rights Reserved
//  模块名称: coll
//  创建日期: 2006/08/03
//  代码编写: zhanglijun
//  功能说明: 数据处理类(含数组和映射等)
//  引用示例: 
//  修改记录:
//////////////////////////////////////////////////////////////////////////
#ifndef __COLL__H__
#define __COLL__H__
#if _MSC_VER > 1000
#pragma once
#endif

// 外部依赖类
class COLLECTION_IMP CXMLProfileSection;

// 基础类
struct COLLECTION_IMP TBucket;					// 数据桶(链表结构)

	class COLLECTION_IMP TMapWordToDword;		// 映射(WORD->DWORD)
	class COLLECTION_IMP TMapWordToPtr;			// 映射(WORD->LPVOID)
	class COLLECTION_IMP TMapDwordToDword;		// 映射(DWORD->DWORD)
	class COLLECTION_IMP TMapDwordToPtr;		// 映射(DWORD->LPVOID)
	class COLLECTION_IMP TMapDwordPtrToDword;	// 映射(DWORD_PTR->DWORD)
	class COLLECTION_IMP TMapDwordPtrToPtr;		// 映射(DWORD_PTR->LPVOID)
	class COLLECTION_IMP TMapPtrToPtr;			// 映射(LPVOID->LPVOID)
	class COLLECTION_IMP TMapPtrToDword;		// 映射(LPVOID->DWORD)
	class COLLECTION_IMP TMapStringToDword;		// 映射(String->DWORD)
	class COLLECTION_IMP TMapStringToPtr;		// 映射(String->LPVOID)
	class COLLECTION_IMP TMapStringToString;	// 映射(String->String)
	class COLLECTION_IMP TMapWordToStru;		// 映射(WORD->结构指针)
	class COLLECTION_IMP TMapDwordToStru;		// 映射(DWORD->结构指针)

	class COLLECTION_IMP TMultiMapDwordToDword;	// 映射(DWORD->DWORD)

	class COLLECTION_IMP TArrayByte;			// 数组(BYTE)
	class COLLECTION_IMP TArrayWord;			// 数组(WORD)
	class COLLECTION_IMP TArrayUint;			// 数组(UINT)
	class COLLECTION_IMP TArrayDword;			// 数组(DWORD)
	class COLLECTION_IMP TArrayPtr;				// 数组(LPVOID)
	class COLLECTION_IMP TArrayStr;				// 数组(LPCSTR)
	
	class COLLECTION_IMP TListWord;				// 列表(WORD)
	class COLLECTION_IMP TListUint;				// 列表(UINT)
	class COLLECTION_IMP TListDword;			// 列表(DWORD)
	class COLLECTION_IMP TListPtr;				// 列表(LPVOID)
	class COLLECTION_IMP TListStr;				// 列表(LPCSTR)

 	class COLLECTION_IMP TOrdinalListWord;		// 有序表(WORD)
 	class COLLECTION_IMP TOrdinalListDword;		// 有序表(DWORD)
 	class COLLECTION_IMP TOrdinalListPtr;		// 有序表(LPVOID)

	class COLLECTION_IMP THashListWord;			// HASH表(WORD)
	class COLLECTION_IMP THashListDword;		// HASH表(DWORD)
	class COLLECTION_IMP THashListPtr;			// HASH表(LPVOID)

	class COLLECTION_IMP THeapList;				// 堆块列表

	class COLLECTION_IMP TTree;					// 树

// 传统
#define COLLECTION_FAST_MEM

// 数据桶结构
typedef struct COLLECTION_IMP TBucket
{	TBucket* m_pNext;
	//BYTE m_Data[maxNum*elementSize];
	static TBucket* PASCAL Create(TBucket*& pHead,UINT nMax,UINT cbElement);
	LPVOID Data() { return this+1; }
	VOID FreeDataChain();
} TBUCKET;

//////////////////////////////////////////////////////////////////////////
// 映射实现
#define COLL_MAP_CLASS				TMapWordToDword
#define COLL_MAP_KEY				WORD
#define COLL_MAP_ARG_KEY			WORD
#define COLL_MAP_VALUE				DWORD
#define COLL_MAP_ARG_VALUE			DWORD
#include "coll_map.h"
#define COLL_MAP_CLASS				TMapWordToPtr
#define COLL_MAP_KEY				WORD
#define COLL_MAP_ARG_KEY			WORD
#define COLL_MAP_VALUE				LPVOID
#define COLL_MAP_ARG_VALUE			LPVOID
#include "coll_map.h"
#define COLL_MAP_CLASS				TMapDwordToDword
#define COLL_MAP_KEY				DWORD
#define COLL_MAP_ARG_KEY			DWORD
#define COLL_MAP_VALUE				DWORD
#define COLL_MAP_ARG_VALUE			DWORD
#include "coll_map.h"
#define COLL_MAP_CLASS				TMapDwordToPtr
#define COLL_MAP_KEY				DWORD
#define COLL_MAP_ARG_KEY			DWORD
#define COLL_MAP_VALUE				LPVOID
#define COLL_MAP_ARG_VALUE			LPVOID
#include "coll_map.h"
#define COLL_MAP_CLASS				TMapDwordPtrToDword
#define COLL_MAP_KEY				DWORD_PTR
#define COLL_MAP_ARG_KEY			DWORD_PTR
#define COLL_MAP_VALUE				DWORD
#define COLL_MAP_ARG_VALUE			DWORD
#include "coll_map.h"
#define COLL_MAP_CLASS				TMapDwordPtrToPtr
#define COLL_MAP_KEY				DWORD_PTR
#define COLL_MAP_ARG_KEY			DWORD_PTR
#define COLL_MAP_VALUE				LPVOID
#define COLL_MAP_ARG_VALUE			LPVOID
#include "coll_map.h"
#define COLL_MAP_CLASS				TMapPtrToPtr
#define COLL_MAP_KEY				LPVOID
#define COLL_MAP_ARG_KEY			LPVOID
#define COLL_MAP_VALUE				LPVOID
#define COLL_MAP_ARG_VALUE			LPVOID
#include "coll_map.h"
#define COLL_MAP_CLASS				TMapPtrToDword
#define COLL_MAP_KEY				LPVOID
#define COLL_MAP_ARG_KEY			LPVOID
#define COLL_MAP_VALUE				DWORD
#define COLL_MAP_ARG_VALUE			DWORD
#include "coll_map.h"
#ifdef __CLIB_STR__H__
	#define COLL_MAP_CLASS			TMapStringToDword
	#define COLL_MAP_KEY			TClibStr
	#define COLL_MAP_ARG_KEY		LPCSTR
	#define COLL_MAP_VALUE			DWORD
	#define COLL_MAP_ARG_VALUE		DWORD
	#include "coll_map.h"
	#define COLL_MAP_CLASS			TMapStringToPtr
	#define COLL_MAP_KEY			TClibStr
	#define COLL_MAP_ARG_KEY		LPCSTR
	#define COLL_MAP_VALUE			LPVOID
	#define COLL_MAP_ARG_VALUE		LPVOID
	#include "coll_map.h"
	#define COLL_MAP_CLASS			TMapStringToString
	#define COLL_MAP_KEY			TClibStr
	#define COLL_MAP_ARG_KEY		LPCSTR
	#define COLL_MAP_VALUE			TClibStr
	#define COLL_MAP_ARG_VALUE		LPCSTR
	#include "coll_map.h"
#endif

class COLLECTION_IMP TMapWordToStru : public TMapWordToPtr
{
public:
	TMapWordToStru(LONG nBlockSize=1,UINT nKeyOffset=0)
		: TMapWordToPtr(nBlockSize,nKeyOffset)
	{
	}
	TMapWordToStru(LPBYTE pElems,DWORD dwElemNum,DWORD cbElem,LONG nBlockSize=1,UINT nKeyOffset=0)
		: TMapWordToPtr(nBlockSize,nKeyOffset)
	{	FillStru(pElems,dwElemNum,cbElem);
	}
	VOID FillStru(LPBYTE pElems,DWORD dwElemNum,DWORD cbElem)
	{	for(DWORD i=0; i<dwElemNum; i++)
		{	LPBYTE pTheElems=pElems+i*cbElem;
			LPWORD pwKey=(LPWORD)pTheElems;
			SetAt((*pwKey),pTheElems);
		}
	}
};

class COLLECTION_IMP TMapDwordToStru : public TMapDwordToPtr
{
public:
	TMapDwordToStru(LONG nBlockSize=1,UINT nKeyOffset=0)
		: TMapDwordToPtr(nBlockSize,nKeyOffset)
	{
	}
	TMapDwordToStru(LPBYTE pElems,DWORD dwElemNum,DWORD cbElem,LONG nBlockSize=1,UINT nKeyOffset=0)
		: TMapDwordToPtr(nBlockSize,nKeyOffset)
	{	FillStru(pElems,dwElemNum,cbElem);
	}
	VOID FillStru(LPBYTE pElems,DWORD dwElemNum,DWORD cbElem)
	{	for(DWORD i=0; i<dwElemNum; i++)
		{	LPBYTE pTheElems=pElems+i*cbElem;
			LPDWORD pdwKey=(LPDWORD)pTheElems;
			SetAt((*pdwKey),pTheElems);
		}
	}
};

//////////////////////////////////////////////////////////////////////////
// 多映射实现
#define COLL_MULTIMAP_CLASS				TMultiMapDwordToDword
#define COLL_MULTIMAP_KEY				DWORD
#define COLL_MULTIMAP_ARG_KEY			DWORD
#define COLL_MULTIMAP_VALUE				DWORD
#define COLL_MULTIMAP_ARG_VALUE			DWORD
#include "coll_multimap.h"

//////////////////////////////////////////////////////////////////////////
// 数组实现
#define COLL_ARRAY_CLASS			TArrayByte
#define COLL_ARRAY_TYPE				BYTE
#define COLL_ARRAY_ARG_TYPE			BYTE
#include "coll_array.h"
#define COLL_ARRAY_CLASS			TArrayWord
#define COLL_ARRAY_TYPE				WORD
#define COLL_ARRAY_ARG_TYPE			WORD
#include "coll_array.h"
#define COLL_ARRAY_CLASS			TArrayUint
#define COLL_ARRAY_TYPE				UINT
#define COLL_ARRAY_ARG_TYPE			UINT
#include "coll_array.h"
#define COLL_ARRAY_CLASS			TArrayDword
#define COLL_ARRAY_TYPE				DWORD
#define COLL_ARRAY_ARG_TYPE			DWORD
#include "coll_array.h"
#define COLL_ARRAY_CLASS			TArrayPtr
#define COLL_ARRAY_TYPE				LPVOID
#define COLL_ARRAY_ARG_TYPE			LPVOID
#include "coll_array.h"
#define COLL_ARRAY_CLASS			TArrayStr
#define COLL_ARRAY_TYPE				TClibStr
#define COLL_ARRAY_ARG_TYPE			LPCSTR
#define COLL_IS_CLASS
#include "coll_array.h"

//////////////////////////////////////////////////////////////////////////
// 列表实现
#define COLL_LIST_CLASS				TListWord
#define COLL_LIST_TYPE				WORD
#define COLL_LIST_ARG_TYPE			WORD
#include "coll_list.h"
#define COLL_LIST_CLASS				TListUint
#define COLL_LIST_TYPE				UINT
#define COLL_LIST_ARG_TYPE			UINT
#include "coll_list.h"
#define COLL_LIST_CLASS				TListDword
#define COLL_LIST_TYPE				DWORD
#define COLL_LIST_ARG_TYPE			DWORD
#include "coll_list.h"
#define COLL_LIST_CLASS				TListPtr
#define COLL_LIST_TYPE				LPVOID
#define COLL_LIST_ARG_TYPE			LPVOID
#include "coll_list.h"
#define COLL_LIST_CLASS				TListStr
#define COLL_LIST_TYPE				TClibStr
#define COLL_LIST_ARG_TYPE			LPCSTR
#include "coll_list.h"

//////////////////////////////////////////////////////////////////////////
// 有序表实现
#define COLL_ORDINALLIST_CLASS		TOrdinalListWord
#define COLL_ORDINALLIST_KEY		WORD
#define COLL_ORDINALLIST_ARG_KEY	WORD
#include "coll_ordinallist.h"
#define COLL_ORDINALLIST_CLASS		TOrdinalListDword
#define COLL_ORDINALLIST_KEY		DWORD
#define COLL_ORDINALLIST_ARG_KEY	DWORD
#include "coll_ordinallist.h"
#define COLL_ORDINALLIST_CLASS		TOrdinalListPtr
#define COLL_ORDINALLIST_KEY		LPVOID
#define COLL_ORDINALLIST_ARG_KEY	LPVOID
#include "coll_ordinallist.h"

//////////////////////////////////////////////////////////////////////////
// 散列表实现
#define COLL_HASHLIST_CLASS			THashListWord
#define COLL_HASHLIST_KEY			WORD
#define COLL_HASHLIST_ARG_KEY		WORD
#include "coll_hashlist.h"
#define COLL_HASHLIST_CLASS			THashListDword
#define COLL_HASHLIST_KEY			DWORD
#define COLL_HASHLIST_ARG_KEY		DWORD
#include "coll_hashlist.h"
#define COLL_HASHLIST_CLASS			THashListPtr
#define COLL_HASHLIST_KEY			LPVOID
#define COLL_HASHLIST_ARG_KEY		LPVOID
#include "coll_hashlist.h"




//////////////////////////////////////////////////////////////////////////
// 堆块列表(用于快速分配内存,无锁定)
#define TRACK_MEMORY_LEAK

class COLLECTION_IMP THeapManager
{
public:
	THeapManager(LONG nLimit) { InitializeCriticalSection(&m_sect); m_nLimit=nLimit; m_nTotalAlloc=0; }
	virtual~THeapManager() { ::DeleteCriticalSection(&m_sect); }
	LPVOID AllocMemory(size_t nSize)
		{	EnterCriticalSection(&m_sect);
			if(m_nLimit>=0&&((m_nTotalAlloc+nSize)/(1024*1024))>(UINT64)m_nLimit)
			{	LeaveCriticalSection(&m_sect);
				return NULL;
			}
			LPVOID pMemory=malloc(nSize);
			if(pMemory==NULL)
			{	LeaveCriticalSection(&m_sect);
				return NULL;
			}
			m_nTotalAlloc+=nSize;
			LeaveCriticalSection(&m_sect);
			return pMemory;
		}
	VOID FreeMemory(LPVOID pMemory,size_t nSize)
		{	if(pMemory==NULL) return;
			EnterCriticalSection(&m_sect);
			m_nTotalAlloc-=nSize;
			LeaveCriticalSection(&m_sect);
			free(pMemory);
		}
	UINT64 GetAlloc() { return (m_nTotalAlloc/1024/1024); }
	UINT GetLimit() { return m_nLimit; }
protected:
	CRITICAL_SECTION m_sect;
	LONG m_nLimit;
	UINT64 m_nTotalAlloc;
};

class COLLECTION_IMP THeapList
{
public:
	static THeapList* New(DWORD dwInitBlockCount,DWORD dwUnitNumPerBlock,DWORD dwUnitSize,LONG nLimit,BOOL bPoolOn,THeapManager* pManager=NULL);
	static VOID Delete(THeapList* pHeapList);
	THeapList(DWORD dwInitBlockCount,DWORD dwUnitNumPerBlock,DWORD dwUnitSize,LONG nLimit,BOOL bPoolOn,THeapManager* pManager=NULL);
	~THeapList();
	LPBYTE AllocUnit();
	VOID FreeUnit(LPBYTE pUnit);
	VOID DumpHeap(LPCSTR pszFileName);
	DWORD GetBlockCount() const { return m_lstBlock.GetCount(); };
	DWORD GetUnitSize() const { return m_dwUnitSize; }
	DWORD GetUnitsCount() const { return m_lstBlock.GetCount()*m_dwUnitNumPerBlock; };
	DWORD GetUsedCount() const { return m_nInUsingNum; };
	DWORD GetFreeCount() const { return m_lstFree.GetCount(); };
	DWORD GetLimitCount() const { return m_nLimit; }
	#ifdef TRACK_MEMORY_LEAK
		POSITION GetFirstInUsing()
			{	return m_hashInUsing.GetStartPosition();
			}
		LPVOID GetNextInUsing(POSITION& posUsing)
			{	LPVOID pUnit=NULL;
				m_hashInUsing.GetNextAssoc(posUsing,pUnit);
				return pUnit;
			}
	#endif
protected:
	CRITICAL_SECTION m_sect;
	DWORD m_dwUnitNumPerBlock;
	DWORD m_dwUnitSize;
	LONG m_nLimit;
	BOOL m_bPoolOn;
	THeapManager* m_pManager;
	LONG m_nInUsingNum;
	TListPtr m_lstBlock;
	TListPtr m_lstFree;
	#ifdef TRACK_MEMORY_LEAK
		THashListPtr m_hashInUsing;
	#endif
};

class COLLECTION_IMP THeapUnit
{
public:
	THeapUnit(THeapList* pHeapList)
	{	m_pHeapList=pHeapList;
		m_pBlock=(m_pHeapList!=NULL)?m_pHeapList->AllocUnit():NULL;
		m_cbBlock=(m_pHeapList!=NULL)?m_pHeapList->GetUnitSize():0;
	}
	virtual~THeapUnit()
	{	if(m_pBlock!=NULL)
		{	m_pHeapList->FreeUnit(m_pBlock);
			m_pBlock=NULL;
		}
	}
	operator LPBYTE () const
	{	return m_pBlock;
	}
	DWORD GetSize() const
	{	return m_cbBlock;
	}
protected:
	THeapList* m_pHeapList;
	LPBYTE m_pBlock;
	DWORD m_cbBlock;
};





// 树节点ID(内存有效)
typedef DWORD_PTR			TREEITEMID;

// 树节点查找宏
#define TGN_ROOT			(0x0000)
#define TGN_NEXT			(0x0001)
#define TGN_PREVIOUS		(0x0002)
#define TGN_PARENT			(0x0003)
#define TGN_CHILD			(0x0004)
#define TGN_NEXT_NEAR		(0x0005)
#define TGN_PREVIOUS_NEAR	(0x0006)

// 特殊树节点ID
#define TID_NULL		((TREEITEMID)0x00000000)
#define TID_ROOT		((TREEITEMID)0xFFFF0000)
#define TID_FIRST		((TREEITEMID)0xFFFF0001)
#define TID_LAST		((TREEITEMID)0xFFFF0002)

// 树定义
class COLLECTION_IMP TTree
{
public:
	TTree();
	virtual~TTree();
public:
	UINT GetCount() const;
	TREEITEMID GetNextItem(TREEITEMID idItem,UINT nCode) const;
	TREEITEMID GetChildItem(TREEITEMID idItem) const;
	TREEITEMID GetNextItem(TREEITEMID idItem) const;
	TREEITEMID GetPrevItem(TREEITEMID idItem) const;
	TREEITEMID GetParentItem(TREEITEMID idItem) const;
	TREEITEMID GetRootItem(TREEITEMID idItem) const;	
	LPCSTR GetItemText(TREEITEMID idItem) const;
	DWORD_PTR GetItemData(TREEITEMID idItem) const;
	DWORD_PTR GetItemExData(TREEITEMID idItem) const;
	BOOL SetItemText(TREEITEMID idItem,LPCSTR lpszItem);
	BOOL SetItemData(TREEITEMID idItem,DWORD dwData);
	BOOL ItemHasChild(TREEITEMID idItem) const;
	LONG GetChildCount(TREEITEMID idItem) const;
	// 节点添加和删除
	TREEITEMID InsertItem(LPCSTR lpszItem,DWORD dwData,TREEITEMID idParent=TID_ROOT,TREEITEMID idInsertAfter=TID_LAST);
	virtual BOOL DeleteItem(TREEITEMID idItem);
	virtual BOOL DeleteChildItems(TREEITEMID idItem);
	virtual VOID DeleteAllItems();
	// 数据交换函数
	virtual BOOL DoDataEPX(TREEITEMID idItem,CXMLProfileSection* pPX);
	// 树节点遍历回调
	// 树遍历
	// 参数说明:
	//		pfnTreeWalkThrough	遍历回调函数
	//		dwParam				遍历回调参数
	//		idItem				起始树节点
	//		dwStack				堆栈值
	// 返回说明:
	//		TREEWALK_COMPLETED	遍历成功
	//		TREEWALK_SKIPPED	遍历被忽略
	//		TREEWALK_CANCELLED	遍历被取消
	typedef LONG (CALLBACK * PFNTREEWALKTHROUGH)(TTree* pTree,TREEITEMID idItem,DWORD_PTR dwParam,LPDWORD lpdwStack);
	typedef enum enumTREEWALKSTATE
	{	TREEWALK_COMPLETED=1,	// 遍历子树全部完成
		TREEWALK_SKIPPED=2,		// 遍历子树被忽略
		TREEWALK_CANCELLED=3,	// 遍历子树被取消
	} TREEWALKSTATE;
	LONG WalkThrough(PFNTREEWALKTHROUGH pfnTreeWalkThrough,DWORD_PTR dwParam,TREEITEMID idItem,DWORD dwStack);
	LONG WalkThroughWithRoot(PFNTREEWALKTHROUGH pfnTreeWalkThrough,DWORD_PTR dwParam,TREEITEMID idItem,DWORD dwStack);
public:
	// 树节点定义
	typedef struct tagTREEITEM
	{	TREEITEMID	m_idKids;		// 第一个子节点
		TREEITEMID	m_idParent;		// 父节点
		TREEITEMID	m_idNext;		// 下一个兄弟节点
		LPSTR		m_lpText;		// 树节点文本
		DWORD_PTR	m_dwExData;		// 树节点关联数据
		DWORD_PTR	m_dwData;		// 树节点关联数据
	} TREEITEM,*LPTREEITEM;
	typedef const TREEITEM* LPCTREEITEM;
protected:
	virtual VOID OnItemCreated(TREEITEMID idItem,LPTREEITEM pTreeItem) { UNREFERENCED_PARAMETER(idItem); UNREFERENCED_PARAMETER(pTreeItem); }
	virtual VOID OnItemDestoryed(TREEITEMID idItem,LPTREEITEM pTreeItem) { UNREFERENCED_PARAMETER(idItem); UNREFERENCED_PARAMETER(pTreeItem); }
	virtual VOID OnItemEPX(TREEITEMID idItem,CXMLProfileSection* pPX) { UNREFERENCED_PARAMETER(idItem); UNREFERENCED_PARAMETER(pPX); }
	LPCTREEITEM LookupItemByIdConst(const TREEITEMID idItem) const;
	LPTREEITEM LookupItemById(const TREEITEMID idItem);
protected:
	TREEITEMID					m_idKids;
	LPVOID						m_plistItems;
};

// 典型字符串数字的HASH算法(字符串和十六进制串)
CLIB_INLINE UINT HashOfNumberString(LPCSTR pszString,DWORD dwRightWidth)
{	UINT uKey=0;
	LONG nLength=strlen32(pszString);
	for(LONG i=max_of(nLength-dwRightWidth,0); i<nLength; i++)
	{	uKey*=10;
		uKey+=pszString[i]-'0';
	}
	return uKey;
}
CLIB_INLINE UINT HashOfHexString(LPCSTR pszString,LONG nOffset,LONG nWidth)
{	UINT uKey=0;
	LONG nLength=strlen32(pszString);
	if(nOffset<nLength) uKey=HexStrToDword(pszString+nOffset,min_of(nLength-nOffset,nWidth));
	return uKey;
}



// CHAR,UCHAR,INT,UINT,INT64,UINT64类型
#define COLL_TYPE CHAR
#define COLL_EPXFUNC
#include "coll_operator.inl"
#undef COLL_TYPE
#undef COLL_EPXFUNC

#define COLL_TYPE UCHAR
#define COLL_EPXFUNC
#include "coll_operator.inl"
#undef COLL_TYPE
#undef COLL_EPXFUNC

#define COLL_TYPE INT
#define COLL_EPXFUNC
#include "coll_operator.inl"
#undef COLL_TYPE
#undef COLL_EPXFUNC

#define COLL_TYPE UINT
#define COLL_EPXFUNC
#include "coll_operator.inl"
#undef COLL_TYPE
#undef COLL_EPXFUNC

#define COLL_TYPE INT64
#define COLL_EPXFUNC
#include "coll_operator.inl"
#undef COLL_TYPE
#undef COLL_EPXFUNC

#define COLL_TYPE UINT64
#define COLL_EPXFUNC
#include "coll_operator.inl"
#undef COLL_TYPE
#undef COLL_EPXFUNC






// BYTE(UCHAR),WORD,DWORD类型
#define COLL_TYPE WORD
#define COLL_EPXFUNC
#include "coll_operator.inl"
#undef COLL_TYPE
#undef COLL_EPXFUNC

#if !defined(_COMPILE_BY_GCC_)
	#define COLL_TYPE DWORD
	#define COLL_EPXFUNC
	#include "coll_operator.inl"
	#undef COLL_TYPE
	#undef COLL_EPXFUNC
#endif





// SHORT,USHORT(WORD),LONG,ULONG(DWORD)
#define COLL_TYPE SHORT
#define COLL_EPXFUNC
#include "coll_operator.inl"
#undef COLL_TYPE
#undef COLL_EPXFUNC

#if !defined(_COMPILE_BY_GCC_)
	#define COLL_TYPE LONG
	#define COLL_EPXFUNC
	#include "coll_operator.inl"
	#undef COLL_TYPE
	#undef COLL_EPXFUNC
#endif

/*
// DWORD_PTR类型
#if defined(_COMPILE_BY_GCC_)
 	#define COLL_TYPE DWORD_PTR
	#define COLL_EPXFUNC
 	#include "coll_operator.inl"
 	#undef COLL_TYPE
	#undef COLL_EPXFUNC
#endif
*/

// LONGINT
#if defined(_COMPILE_BY_GCC_)
 	#define COLL_TYPE LONGINT
	#define COLL_EPXFUNC
 	#include "coll_operator.inl"
 	#undef COLL_TYPE
	#undef COLL_EPXFUNC
#endif

// ULONGINT
#if defined(_COMPILE_BY_GCC_)
 	#define COLL_TYPE ULONGINT
	#define COLL_EPXFUNC
 	#include "coll_operator.inl"
 	#undef COLL_TYPE
	#undef COLL_EPXFUNC
#endif



// LPVOID类型相关函数
CLIB_INLINE UINT CLIBAPI GenHashKey(LPVOID Key,UINT nKeyOffset)
	{	UNREFERENCED_PARAMETER(nKeyOffset);
		return (UINT)(((DWORD_PTR)Key)>>4);
	}
CLIB_INLINE void CLIBAPI CollConstructElements(UNALIGNED LPVOID* pElements, int nCount)
	{
		if(nCount>0) memset((void*)pElements,0,nCount*size_of(LPVOID));
		#ifndef COLLECTION_FAST_MEM
			for(; nCount--; pElements++)
				::new((void*)pElements) LPVOID;
		#endif
	}
CLIB_INLINE void CLIBAPI CollDestructElements(UNALIGNED LPVOID* pElements,int nCount)
	{
		#ifndef COLLECTION_FAST_MEM
			for(; nCount--; pElements++)
				pElements->~LPVOID();
		#endif
		if(nCount>0) memset((void*)pElements,0,nCount*size_of(LPVOID));
	}
CLIB_INLINE void CLIBAPI CollCopyElements(LPVOID* pDest,const LPVOID* pSrc, int nCount)
	{	while(nCount--)
		{	*pDest++ = *pSrc++;
		}
	}
CLIB_INLINE BOOL CLIBAPI CollCompareElements(const LPVOID* pElement1,const LPVOID* pElement2)
	{	return *pElement1==*pElement2;
	}
BOOL COLLECTION_IMP CLIBAPI CollDoDataEPXElements(LPVOID* pElement,CXMLProfileSection* pPX,LPCSTR pszName);



// LPSTR类型相关函数
CLIB_INLINE UINT CLIBAPI GenHashKey(LPCSTR Key,UINT nKeyOffset)
		{	LPCTSTR pszKey=Key;
			if(pszKey==NULL) pszKey="";
			UINT nHash=0;
			while(*pszKey) nHash=(nHash<<5)+nHash+*pszKey++;
			return nHash>>nKeyOffset;
		}
CLIB_INLINE void CLIBAPI CollConstructElements(UNALIGNED LPCSTR* pElements, int nCount)
		{
			if(nCount>0) memset((void*)pElements,0,nCount*size_of(LPCSTR));
			#ifndef COLLECTION_FAST_MEM
				for(; nCount--; pElements++)
					::new((void*)pElements) LPCSTR;
			#endif
		}
CLIB_INLINE void CLIBAPI CollDestructElements(UNALIGNED LPCSTR* pElements,int nCount)
		{
			#ifndef COLLECTION_FAST_MEM
				for(; nCount--; pElements++)
					pElements->~LPCSTR();
			#endif
			if(nCount>0) memset((void*)pElements,0,nCount*size_of(LPCSTR));
		}
CLIB_INLINE void CLIBAPI CollCopyElements(LPCSTR* pDest,const LPCSTR* pSrc, int nCount)
		{	while(nCount--)
			{	*pDest++ = *pSrc++;
			}
		}
CLIB_INLINE BOOL CLIBAPI CollCompareElements(const LPCSTR* pElement1,const LPCSTR* pElement2)
		{	if(pElement1==NULL&&pElement2==NULL) return TRUE;
			if(pElement1==NULL) return FALSE;
			if(pElement2==NULL) return FALSE;
			return strcmp(*pElement1,*pElement2)==0;
		}
BOOL COLLECTION_IMP CLIBAPI CollDoDataEPXElements(LPCSTR* pElement,CXMLProfileSection* pPX,LPCSTR pszName);


#endif

