//////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2006 - All Rights Reserved
//  模块名称: clibtempl
//  创建日期: 2006/08/03
//  代码编写: zhanglijun
//  功能说明: 数据处理类(含数组和映射等)
//  引用示例: 
//  修改记录:
//////////////////////////////////////////////////////////////////////////
#ifndef __CLIB_TEMPL__H__
#define __CLIB_TEMPL__H__
#if _MSC_VER > 1000
#pragma once
#endif

// 基本处理类
template<class KEY,class ARG_KEY,class VALUE,class ARG_VALUE> class TMap;		// 映射类
template<class KEY,class ARG_KEY,class VALUE,class ARG_VALUE> class TMultiMap;	// 多映射类
template<class TYPE,class ARG_TYPE> class TArray;								// 数组类(向量表)
template<class TYPE,class ARG_TYPE> class TList;								// 链表类(队列,堆栈等等)
template<class TYPE,class ARG_TYPE> class TOrdinalList;							// 有序表类
template<class KEY,class VALUE> class TListMap;									// 有序映射
template<class KEY,class ARG_KEY> class THashList;								// HASH表类

// 映射类(通用模板类)
template<class KEY,class ARG_KEY,class VALUE,class ARG_VALUE>
class TMap
{
NO_ASSIGN_OPERATOR(TMap);
public:
	TMap(LONG nBlockSize=1,UINT nKeyOffset=0);
	~TMap();

	// 读取映射个数和判空
	LONG GetCount() CONST;
	BOOL IsEmpty() CONST;

	// 判断键值
	VALUE* Exist(ARG_KEY Key);

	// 映射的查找,返回是否存在标志
	BOOL Lookup(ARG_KEY Key,VALUE& rValue) CONST;

	// 映射查找,返回查找到的数据,如果查找不到,创建空数据([])
	VALUE& operator[](ARG_KEY Key);

	// 映射添加
	// 返回TRUE:节点已经存在,其数据被覆盖,返回FALSE,节点不存在,其数据重新创建
	BOOL SetAt(ARG_KEY Key,ARG_VALUE newValue);

	// 删除键
	BOOL RemoveKey(ARG_KEY Key);
	VOID RemoveAll();

	// 数据交换函数
	BOOL DoDataEPX(CXMLProfileSection* pPX);

	// 查找开始位置和取得关联键
	POSITION GetStartPosition() CONST;
	VOID GetNextAssoc(POSITION& rNextPosition,KEY& rKey,VALUE& rValue) CONST;

	// HASH表处理
	UINT GetHashTableSize() CONST;
	VOID InitHashTable(UINT nHashSize,BOOL bAllocNow=TRUE);
protected:
	// 映射表单元
	struct CAssoc
	{	CAssoc* m_pNext;
		KEY		m_Key;
		VALUE	m_Value;
	};
protected:
	CAssoc* NewAssoc();
	VOID FreeAssoc(CAssoc* pAssoc);
	CAssoc* GetAssocAt(ARG_KEY Key,UINT& nHash) CONST;
protected:
	CAssoc**	m_pHashTable;
	UINT		m_nHashTableSize;
	UINT		m_nKeyOffset;
	LONG		m_nCount;
	CAssoc*		m_pFreeList;
	TBUCKET*	m_pBlocks;
	LONG		m_nBlockSize;
};



// 多映射类(通用模板类)
template<class KEY,class ARG_KEY,class VALUE,class ARG_VALUE>
class TMultiMap
{
NO_ASSIGN_OPERATOR(TMultiMap);
public:
	TMultiMap(LONG nBlockSize=1,UINT nKeyOffset=0,UINT nValueOffset=0);
	~TMultiMap();

	// 读取映射个数和判空
	LONG GetKeyCount() CONST;
	BOOL IsKeyEmpty() CONST;

	// 映射的查找,返回是否存在标志
	BOOL Lookup(ARG_KEY Key,VALUE& rValue) CONST;

	// 映射添加
	// 返回TRUE:节点已经存在,其数据被覆盖,返回FALSE,节点不存在,其数据重新创建
	BOOL SetAt(ARG_KEY Key,ARG_VALUE newValue);

	// 删除键
	BOOL RemoveKey(ARG_KEY Key);
	VOID RemoveAll();

	// 数据交换函数
	BOOL DoDataEPX(CXMLProfileSection* pPX);

	// 查找开始位置和取得关联键
	POSITION GetKeyStartPosition() CONST;
	VOID GetNextKeyAssoc(POSITION& rNextPosition,KEY& rKey,VALUE& rValue) CONST;

	// 查找开始位置和取得关联值
	POSITION GetValueStartPosition(ARG_VALUE Value) CONST;
	VOID GetNextValueAssoc(POSITION& rNextPosition,KEY& rKey) CONST;

	// HASH表处理
	UINT GetHashTableSize() CONST;
	VOID InitHashTable(UINT nHashSize,BOOL bAllocNow=TRUE);
protected:
	// 映射表单元
	struct CAssoc
	{	CAssoc* m_pKeyNext;
		CAssoc* m_pValueNext;
		CAssoc* m_pLinkNext;
		KEY m_Key;
		VALUE m_Value;
	};
protected:
	CAssoc* NewAssoc();
	VOID FreeAssoc(CAssoc* pAssoc);
	CAssoc* GetAssocAtByKey(ARG_KEY Key,UINT& nHash) CONST;
	CAssoc* GetAssocAtByValue(ARG_VALUE Value,UINT& nHash) CONST;
protected:
	CAssoc**		m_pKeyHashTable;		// 键的HASH表
	CAssoc**		m_pValueHashTable;		// 值的HASH表
	UINT			m_nHashTableSize;		// HASH表大小
	UINT			m_nKeyOffset;			// 键的HASH偏移
	UINT			m_nValueOffset;			// 值的HASH偏移
	LONG			m_nKeyCount;			// 键的个数
	CAssoc*			m_pFreeList;			// 可用空间表
	TBUCKET*		m_pBlocks;				// 分块
	LONG			m_nBlockSize;			// 分块大小
};


// 数组类(通用类)
template<class TYPE,class ARG_TYPE>
class TArray
{
public:
	TArray(LONG nGrowBy=0);
	TArray(LPBYTE pStack,DWORD cbStack);
	~TArray();
	CONST TArray& operator=(CONST TArray& Src) { Copy(&Src); return (*this); }

	// 属性获取
	LONG GetSize() CONST;
	LONG GetUpperBound() CONST;
	LONG GetMaxSize() CONST;
	VOID SetSize(LONG nNewSize,LONG nGrowBy=-1);

	// 操作
	VOID FreeExtra();
	VOID RemoveAll();

	// 单元访问
	TYPE GetAt(LONG nIndex) CONST;
	VOID SetAt(LONG nIndex,ARG_TYPE newElement);
	TYPE& ElementAt(LONG nIndex);

	// 直接单元访问
	CONST TYPE* GetData() CONST;
	TYPE* GetData();

	// 单元添加
	VOID SetAtGrow(LONG nIndex,ARG_TYPE newElement);
	VOID SetAtGrowEmpty(LONG nIndex);
	LONG Add(ARG_TYPE newElement);
	LONG AddEmpty();
	LONG Append(CONST TArray* psrc);
	VOID Copy(CONST TArray* psrc);

	// 单元添加(无赋值操作)
	BOOL SetSizeNoAssign(LONG nNewSize,LONG nGrowBy=-1);
	BOOL SetAtGrowEmptyNoAssign(LONG nIndex);
	LONG AddEmptyNoAssign();

	// 操作重载
	TYPE operator[](LONG nIndex) CONST;
	TYPE& operator[](LONG nIndex);

	// 单元插入和删除(需要单元移动)
	VOID InsertAt(LONG nIndex,ARG_TYPE newElement,LONG nCount=1);
	VOID RemoveAt(LONG nIndex,LONG nCount=1);
	VOID InsertAt(LONG nStartIndex,TArray* pNewArray);
	// 对象查找
	LONG Find(ARG_TYPE searchValue,LONG startAfter=-1) CONST;

	// 数据交换函数
	BOOL DoDataEPX(CXMLProfileSection* pPX);
protected:
	BOOL	m_bDynamic;	// 是否使用堆分配
	TYPE*	m_pData;	 // 数组指针
	LONG	m_nSize;     // 数组大小
	LONG	m_nMaxSize;  // 数组被分配的大小
	LONG	m_nGrowBy;   // 数组每次增大的大小
};


// 链表类(通用模板类)
template<class TYPE,class ARG_TYPE>
class TList
{
public:
	TList(LONG nBlockSize=10);
	~TList();
	CONST TList& operator=(CONST TList& Src) { Copy(&Src); return (*this); }

	// 个数获取和判空
	LONG GetCount() CONST;
	BOOL IsEmpty() CONST;

	// 头部和尾部获取
	TYPE& GetHead();
	TYPE  GetHead() CONST;
	TYPE& GetTail();
	TYPE  GetTail() CONST;

	// 删除头部对象和尾部对象
	TYPE RemoveHead();
	TYPE RemoveTail();

	// 列表项添加
	POSITION AddHeadConst(const TYPE& newElement);
	POSITION AddTailConst(const TYPE& newElement);
	POSITION AddHead(ARG_TYPE newElement);
	POSITION AddTail(ARG_TYPE newElement);
	POSITION AddEmptyToHead();
	POSITION AddEmptyToTail();

	// 列表合并
	VOID AppendHead(CONST TList* pNewList);
	VOID AppendTail(CONST TList* pNewList);
	VOID Copy(CONST TList* pNewList) { RemoveAll(); AppendTail(pNewList); }

	// 列表项清空
	VOID RemoveAll();

	// 列表项遍历
	POSITION GetHeadPosition() CONST;
	POSITION GetTailPosition() CONST;
	TYPE& GetNext(POSITION& rPosition);
	TYPE  GetNext(POSITION& rPosition) CONST;
	TYPE& GetPrev(POSITION& rPosition);
	TYPE  GetPrev(POSITION& rPosition) CONST;

	// 列表项获取和设置
	TYPE& GetAt(POSITION position);
	TYPE  GetAt(POSITION position) CONST;
	VOID  SetAt(POSITION pos,ARG_TYPE newElement);
	POSITION PositionOf(TYPE* pData);

	// 列表删除
	VOID RemoveAt(POSITION position);
	VOID RemoveByPtr(TYPE* pData);

	// 数据交换函数
	BOOL DoDataEPX(CXMLProfileSection* pPX);

	// 列表插入
	POSITION InsertBefore(POSITION position,ARG_TYPE newElement);
	POSITION InsertAfter(POSITION position,ARG_TYPE newElement);

	// 对象查找
	POSITION Find(ARG_TYPE searchValue,POSITION startAfter=NULL) CONST;
	POSITION FindIndex(LONG nIndex) CONST;
	TYPE& GetAtIndex(LONG nIndex);
	TYPE  GetAtIndex(LONG nIndex) CONST;
protected:
	struct CNode
	{	CNode*	pNext;
		CNode*	pPrev;
		TYPE	data;
	};
protected:
	CNode* NewNode(CNode*,CNode*);
	VOID FreeNode(CNode*);
protected:
	CNode*		m_pNodeHead;
	CNode*		m_pNodeTail;
	LONG		m_nCount;
	CNode*		m_pNodeFree;
	TBUCKET*	m_pBlocks;
	LONG		m_nBlockSize;
};


// 有序表类
template<class KEY,class ARG_KEY>
class TOrdinalList
{
NO_ASSIGN_OPERATOR(TOrdinalList);
public:
	TOrdinalList(LONG nBlockSize=10);
	~TOrdinalList();
};

// 有序映射
template<class KEY,class VALUE>
class TListMap
{
NO_ASSIGN_OPERATOR(TListMap);
public:
	TListMap(LONG nBlockSize,LONG nHashSize)
		: m_lstValue(nBlockSize)
		{	m_mapKeys.InitHashTable(nHashSize,TRUE);
		}
	VALUE* SetAt(KEY& Key,VALUE& newValue,POSITION* pposValue=NULL)
		{	POSITION posValue=NULL;
			if(!m_mapKeys.Lookup(Key,posValue))
				posValue=m_lstValue.AddTail(newValue);
			VALUE* pValue=&m_lstValue.GetAt(posValue);
			if(pposValue!=NULL) (*pposValue)=posValue;
			m_mapKeys.SetAt(Key,posValue);
			return pValue;
		}
	BOOL RemoveAt(KEY& Key)
		{	POSITION posValue=NULL;
			if(!m_mapKeys.Lookup(Key,posValue)) return FALSE;
			m_mapKeys.RemoveKey(Key);
			m_lstValue.RemoveAt(posValue);
			return TRUE;
		}
	VALUE* Lookup(KEY& Key,POSITION* pposValue)
		{	POSITION posValue=NULL;
			if(!m_mapKeys.Lookup(Key,posValue)||posValue==NULL) return NULL;
			if(pposValue!=NULL) (*pposValue)=posValue;
			return &m_lstValue.GetAt(posValue);
		}
	POSITION GetHeadPosition()
		{	return m_lstValue.GetHeadPosition();
		}
	VALUE* GetNext(POSITION& posValue)
		{	return &m_lstValue.GetNext(posValue);
		}
	VALUE* GetByPosition(POSITION posValue)
		{	return &m_lstValue.GetAt(posValue);
		}
protected:
	TMap<KEY,KEY&,POSITION,POSITION&> m_mapKeys;
	TList<VALUE,VALUE&> m_lstValue;
};


// HASH表类(通用模板类)
template<class KEY,class ARG_KEY>
class THashList
{
public:
	THashList(LONG nBlockSize=10,UINT nKeyOffset=0);
	~THashList();

	// 读取HASH数据个数和判空
	LONG GetCount() CONST;
	BOOL IsEmpty() CONST;

	// 映射的查找,返回是否存在标志
	BOOL Lookup(ARG_KEY Key) CONST;
	BOOL operator[](ARG_KEY Key) CONST;

	// 映射添加
	VOID InsertKey(ARG_KEY Key);
	BOOL RemoveKey(ARG_KEY Key);
	VOID RemoveAll();

	// 数据交换函数
	BOOL DoDataEPX(CXMLProfileSection* pPX);

	// 查找开始位置和取得关联键
	POSITION GetStartPosition() CONST;
	VOID GetNextAssoc(POSITION& rNextPosition,KEY& rKey) CONST;

	// HASH表处理
	UINT GetHashTableSize() CONST;
	VOID InitHashTable(UINT nHashSize,BOOL bAllocNow=TRUE);
protected:
	// 映射表单元
	struct CAssoc
	{	CAssoc* m_pNext;
		KEY		m_Key;
	};
protected:
	CAssoc* NewAssoc();
	VOID FreeAssoc(CAssoc* pAssoc);
	CAssoc* GetAssocAt(ARG_KEY Key,UINT& nHash) CONST;
protected:
	CAssoc**	m_pHashTable;
	UINT		m_nHashTableSize;
	UINT		m_nKeyOffset;
	LONG		m_nCount;
	CAssoc*		m_pFreeList;
	TBUCKET*	m_pBlocks;
	LONG		m_nBlockSize;
};


// 模板树
template<class TYPE,class ARG_TYPE>
class TTypedTree : public TTree
{
NO_ASSIGN_OPERATOR(TTypedTree);
public:
	TTypedTree(LONG nBlockSize=10) : m_aExDatas(nBlockSize) {};
	virtual~TTypedTree() { DeleteAllItems(); };
public:
	TREEITEMID InsertItem(LPCSTR lpszItem,ARG_TYPE Data,TREEITEMID idParent=TID_ROOT,TREEITEMID idInsertAfter=TID_LAST)
	{	TREEITEMID idItem=TTree::InsertItem(lpszItem,0,idParent,idInsertAfter);
		if(idItem==TID_NULL) return TID_NULL;
		POSITION posExData=(POSITION)GetItemExData(idItem);
		if(posExData!=NULL) m_aExDatas.SetAt(posExData,Data);
		return idItem;
	}
	TYPE GetTypedItemData(TREEITEMID idItem)
	{	POSITION posItemData=(POSITION)GetItemExData(idItem);
		CLIBASSERT(posItemData!=NULL);
		return m_aExDatas.GetAt(posItemData);
	}
	TYPE* GetTypedItemDataPtr(TREEITEMID idItem)
	{	POSITION posItemData=(POSITION)GetItemExData(idItem);
		if(posItemData==NULL) return NULL;
		return &(m_aExDatas.GetAt(posItemData));
	}
	virtual BOOL DoDataEPX(TREEITEMID idItem,CXMLProfileSection* pPX)
	{	TYPE* pData=(TYPE*)alloca(size_of(TYPE));
		CollConstructElements(pData,1);
		if(!pPX->IsStoring())
		{	DeleteChildItems(idItem);
			CXMLProfileEnumerator ItemEnumerator(pPX->GetEnumerator(_T("ITEM"),0));
			POSITION posItemInXml=ItemEnumerator.GetPosition();
			while(posItemInXml!=NULL)
			{	CXMLProfileSection ItemItemSection(ItemEnumerator.GetNext(posItemInXml));
				LPCSTR pszText=NULL;
				CHAR szText[4096]={0};
				if(ItemItemSection.ReadNChar("TEXT",szText,size_of(szText),"")) pszText=szText;
				TREEITEMID idTheItemInTree=InsertItem(pszText,*pData,idItem,TID_LAST);
				TYPE* pData=GetTypedItemDataPtr(idTheItemInTree);
				CollDoDataEPXElements((TYPE*)pData,&ItemItemSection,(LPCSTR)"VALUE");
				OnItemEPX(idTheItemInTree,&ItemItemSection);
				DoDataEPX(idTheItemInTree,&ItemItemSection);
			}
		}
		else
		{	CXMLProfileEnumerator ItemEnumerator(pPX->GetEnumerator(_T("ITEM"),GetChildCount(idItem)));
			TREEITEMID idItemInTree=GetChildItem(idItem);
			POSITION posItemInXml=ItemEnumerator.GetPosition();
			while(idItemInTree!=TID_NULL&&posItemInXml!=NULL)
			{	TREEITEMID idTheItemInTree=idItemInTree;
				idItemInTree=GetNextItem(idItemInTree);
				CXMLProfileSection ItemItemSection(ItemEnumerator.GetNext(posItemInXml));
				LPCSTR pszText=GetItemText(idTheItemInTree);
				if(pszText!=NULL) EPX_NChar(&ItemItemSection,"TEXT",(LPSTR)pszText,strlen32(pszText),"");
				TYPE* pData=GetTypedItemDataPtr(idTheItemInTree);
				CollDoDataEPXElements((TYPE*)pData,&ItemItemSection,(LPCSTR)"VALUE");
				OnItemEPX(idTheItemInTree,&ItemItemSection);
				DoDataEPX(idTheItemInTree,&ItemItemSection);
			}
		}
		CollDestructElements(pData,1);
		return TRUE;
	}
protected:
	virtual VOID OnItemCreated(TREEITEMID idItem,LPTREEITEM pTreeItem)
	{	LPVOID pExData=alloca(size_of(TYPE));
		CollConstructElements((TYPE*)pExData,1);
		POSITION posExData=m_aExDatas.AddTail(*((TYPE*)pExData));
		pTreeItem->m_dwExData=(DWORD_PTR)posExData;
		TTree::OnItemCreated(idItem,pTreeItem);
		CollDestructElements((TYPE*)pExData,1);
	}
	virtual VOID OnItemDestoryed(TREEITEMID idItem,LPTREEITEM pTreeItem)
	{	if(pTreeItem->m_dwExData!=0) m_aExDatas.RemoveAt((POSITION)pTreeItem->m_dwExData);
		pTreeItem->m_dwExData=0;
		TTree::OnItemDestoryed(idItem,pTreeItem);
	}
protected:
	TList<TYPE,ARG_TYPE> m_aExDatas;
};

// 包含内联实现
#include "clibtempl.inl"

// 衍生类型
typedef TArray<TClibStr,LPCSTR> TStringArray;
typedef TList<TClibStr,LPCSTR> TStringList;


#endif
