//////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2006 - All Rights Reserved
//  ģ������: clibtempl
//  ��������: 2006/08/03
//  �����д: zhanglijun
//  ����˵��: ���ݴ�����(�������ӳ���)
//  ����ʾ��: 
//  �޸ļ�¼:
//////////////////////////////////////////////////////////////////////////
#ifndef __CLIB_TEMPL__H__
#define __CLIB_TEMPL__H__
#if _MSC_VER > 1000
#pragma once
#endif

// ����������
template<class KEY,class ARG_KEY,class VALUE,class ARG_VALUE> class TMap;		// ӳ����
template<class KEY,class ARG_KEY,class VALUE,class ARG_VALUE> class TMultiMap;	// ��ӳ����
template<class TYPE,class ARG_TYPE> class TArray;								// ������(������)
template<class TYPE,class ARG_TYPE> class TList;								// ������(����,��ջ�ȵ�)
template<class TYPE,class ARG_TYPE> class TOrdinalList;							// �������
template<class KEY,class VALUE> class TListMap;									// ����ӳ��
template<class KEY,class ARG_KEY> class THashList;								// HASH����

// ӳ����(ͨ��ģ����)
template<class KEY,class ARG_KEY,class VALUE,class ARG_VALUE>
class TMap
{
NO_ASSIGN_OPERATOR(TMap);
public:
	TMap(LONG nBlockSize=1,UINT nKeyOffset=0);
	~TMap();

	// ��ȡӳ��������п�
	LONG GetCount() CONST;
	BOOL IsEmpty() CONST;

	// �жϼ�ֵ
	VALUE* Exist(ARG_KEY Key);

	// ӳ��Ĳ���,�����Ƿ���ڱ�־
	BOOL Lookup(ARG_KEY Key,VALUE& rValue) CONST;

	// ӳ�����,���ز��ҵ�������,������Ҳ���,����������([])
	VALUE& operator[](ARG_KEY Key);

	// ӳ�����
	// ����TRUE:�ڵ��Ѿ�����,�����ݱ�����,����FALSE,�ڵ㲻����,���������´���
	BOOL SetAt(ARG_KEY Key,ARG_VALUE newValue);

	// ɾ����
	BOOL RemoveKey(ARG_KEY Key);
	VOID RemoveAll();

	// ���ݽ�������
	BOOL DoDataEPX(CXMLProfileSection* pPX);

	// ���ҿ�ʼλ�ú�ȡ�ù�����
	POSITION GetStartPosition() CONST;
	VOID GetNextAssoc(POSITION& rNextPosition,KEY& rKey,VALUE& rValue) CONST;

	// HASH����
	UINT GetHashTableSize() CONST;
	VOID InitHashTable(UINT nHashSize,BOOL bAllocNow=TRUE);
protected:
	// ӳ���Ԫ
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



// ��ӳ����(ͨ��ģ����)
template<class KEY,class ARG_KEY,class VALUE,class ARG_VALUE>
class TMultiMap
{
NO_ASSIGN_OPERATOR(TMultiMap);
public:
	TMultiMap(LONG nBlockSize=1,UINT nKeyOffset=0,UINT nValueOffset=0);
	~TMultiMap();

	// ��ȡӳ��������п�
	LONG GetKeyCount() CONST;
	BOOL IsKeyEmpty() CONST;

	// ӳ��Ĳ���,�����Ƿ���ڱ�־
	BOOL Lookup(ARG_KEY Key,VALUE& rValue) CONST;

	// ӳ�����
	// ����TRUE:�ڵ��Ѿ�����,�����ݱ�����,����FALSE,�ڵ㲻����,���������´���
	BOOL SetAt(ARG_KEY Key,ARG_VALUE newValue);

	// ɾ����
	BOOL RemoveKey(ARG_KEY Key);
	VOID RemoveAll();

	// ���ݽ�������
	BOOL DoDataEPX(CXMLProfileSection* pPX);

	// ���ҿ�ʼλ�ú�ȡ�ù�����
	POSITION GetKeyStartPosition() CONST;
	VOID GetNextKeyAssoc(POSITION& rNextPosition,KEY& rKey,VALUE& rValue) CONST;

	// ���ҿ�ʼλ�ú�ȡ�ù���ֵ
	POSITION GetValueStartPosition(ARG_VALUE Value) CONST;
	VOID GetNextValueAssoc(POSITION& rNextPosition,KEY& rKey) CONST;

	// HASH����
	UINT GetHashTableSize() CONST;
	VOID InitHashTable(UINT nHashSize,BOOL bAllocNow=TRUE);
protected:
	// ӳ���Ԫ
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
	CAssoc**		m_pKeyHashTable;		// ����HASH��
	CAssoc**		m_pValueHashTable;		// ֵ��HASH��
	UINT			m_nHashTableSize;		// HASH���С
	UINT			m_nKeyOffset;			// ����HASHƫ��
	UINT			m_nValueOffset;			// ֵ��HASHƫ��
	LONG			m_nKeyCount;			// ���ĸ���
	CAssoc*			m_pFreeList;			// ���ÿռ��
	TBUCKET*		m_pBlocks;				// �ֿ�
	LONG			m_nBlockSize;			// �ֿ��С
};


// ������(ͨ����)
template<class TYPE,class ARG_TYPE>
class TArray
{
public:
	TArray(LONG nGrowBy=0);
	TArray(LPBYTE pStack,DWORD cbStack);
	~TArray();
	CONST TArray& operator=(CONST TArray& Src) { Copy(&Src); return (*this); }

	// ���Ի�ȡ
	LONG GetSize() CONST;
	LONG GetUpperBound() CONST;
	LONG GetMaxSize() CONST;
	VOID SetSize(LONG nNewSize,LONG nGrowBy=-1);

	// ����
	VOID FreeExtra();
	VOID RemoveAll();

	// ��Ԫ����
	TYPE GetAt(LONG nIndex) CONST;
	VOID SetAt(LONG nIndex,ARG_TYPE newElement);
	TYPE& ElementAt(LONG nIndex);

	// ֱ�ӵ�Ԫ����
	CONST TYPE* GetData() CONST;
	TYPE* GetData();

	// ��Ԫ���
	VOID SetAtGrow(LONG nIndex,ARG_TYPE newElement);
	VOID SetAtGrowEmpty(LONG nIndex);
	LONG Add(ARG_TYPE newElement);
	LONG AddEmpty();
	LONG Append(CONST TArray* psrc);
	VOID Copy(CONST TArray* psrc);

	// ��Ԫ���(�޸�ֵ����)
	BOOL SetSizeNoAssign(LONG nNewSize,LONG nGrowBy=-1);
	BOOL SetAtGrowEmptyNoAssign(LONG nIndex);
	LONG AddEmptyNoAssign();

	// ��������
	TYPE operator[](LONG nIndex) CONST;
	TYPE& operator[](LONG nIndex);

	// ��Ԫ�����ɾ��(��Ҫ��Ԫ�ƶ�)
	VOID InsertAt(LONG nIndex,ARG_TYPE newElement,LONG nCount=1);
	VOID RemoveAt(LONG nIndex,LONG nCount=1);
	VOID InsertAt(LONG nStartIndex,TArray* pNewArray);
	// �������
	LONG Find(ARG_TYPE searchValue,LONG startAfter=-1) CONST;

	// ���ݽ�������
	BOOL DoDataEPX(CXMLProfileSection* pPX);
protected:
	BOOL	m_bDynamic;	// �Ƿ�ʹ�öѷ���
	TYPE*	m_pData;	 // ����ָ��
	LONG	m_nSize;     // �����С
	LONG	m_nMaxSize;  // ���鱻����Ĵ�С
	LONG	m_nGrowBy;   // ����ÿ������Ĵ�С
};


// ������(ͨ��ģ����)
template<class TYPE,class ARG_TYPE>
class TList
{
public:
	TList(LONG nBlockSize=10);
	~TList();
	CONST TList& operator=(CONST TList& Src) { Copy(&Src); return (*this); }

	// ������ȡ���п�
	LONG GetCount() CONST;
	BOOL IsEmpty() CONST;

	// ͷ����β����ȡ
	TYPE& GetHead();
	TYPE  GetHead() CONST;
	TYPE& GetTail();
	TYPE  GetTail() CONST;

	// ɾ��ͷ�������β������
	TYPE RemoveHead();
	TYPE RemoveTail();

	// �б������
	POSITION AddHeadConst(const TYPE& newElement);
	POSITION AddTailConst(const TYPE& newElement);
	POSITION AddHead(ARG_TYPE newElement);
	POSITION AddTail(ARG_TYPE newElement);
	POSITION AddEmptyToHead();
	POSITION AddEmptyToTail();

	// �б�ϲ�
	VOID AppendHead(CONST TList* pNewList);
	VOID AppendTail(CONST TList* pNewList);
	VOID Copy(CONST TList* pNewList) { RemoveAll(); AppendTail(pNewList); }

	// �б������
	VOID RemoveAll();

	// �б������
	POSITION GetHeadPosition() CONST;
	POSITION GetTailPosition() CONST;
	TYPE& GetNext(POSITION& rPosition);
	TYPE  GetNext(POSITION& rPosition) CONST;
	TYPE& GetPrev(POSITION& rPosition);
	TYPE  GetPrev(POSITION& rPosition) CONST;

	// �б����ȡ������
	TYPE& GetAt(POSITION position);
	TYPE  GetAt(POSITION position) CONST;
	VOID  SetAt(POSITION pos,ARG_TYPE newElement);
	POSITION PositionOf(TYPE* pData);

	// �б�ɾ��
	VOID RemoveAt(POSITION position);
	VOID RemoveByPtr(TYPE* pData);

	// ���ݽ�������
	BOOL DoDataEPX(CXMLProfileSection* pPX);

	// �б����
	POSITION InsertBefore(POSITION position,ARG_TYPE newElement);
	POSITION InsertAfter(POSITION position,ARG_TYPE newElement);

	// �������
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


// �������
template<class KEY,class ARG_KEY>
class TOrdinalList
{
NO_ASSIGN_OPERATOR(TOrdinalList);
public:
	TOrdinalList(LONG nBlockSize=10);
	~TOrdinalList();
};

// ����ӳ��
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


// HASH����(ͨ��ģ����)
template<class KEY,class ARG_KEY>
class THashList
{
public:
	THashList(LONG nBlockSize=10,UINT nKeyOffset=0);
	~THashList();

	// ��ȡHASH���ݸ������п�
	LONG GetCount() CONST;
	BOOL IsEmpty() CONST;

	// ӳ��Ĳ���,�����Ƿ���ڱ�־
	BOOL Lookup(ARG_KEY Key) CONST;
	BOOL operator[](ARG_KEY Key) CONST;

	// ӳ�����
	VOID InsertKey(ARG_KEY Key);
	BOOL RemoveKey(ARG_KEY Key);
	VOID RemoveAll();

	// ���ݽ�������
	BOOL DoDataEPX(CXMLProfileSection* pPX);

	// ���ҿ�ʼλ�ú�ȡ�ù�����
	POSITION GetStartPosition() CONST;
	VOID GetNextAssoc(POSITION& rNextPosition,KEY& rKey) CONST;

	// HASH����
	UINT GetHashTableSize() CONST;
	VOID InitHashTable(UINT nHashSize,BOOL bAllocNow=TRUE);
protected:
	// ӳ���Ԫ
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


// ģ����
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

// ��������ʵ��
#include "clibtempl.inl"

// ��������
typedef TArray<TClibStr,LPCSTR> TStringArray;
typedef TList<TClibStr,LPCSTR> TStringList;


#endif
