#if !defined(__COLL__H__)
	#error coll.h must be included
#endif
#if !defined(COLL_LIST_CLASS)
	#error COLL_LIST_CLASS must be defined
#endif
#if !defined(COLL_LIST_TYPE)
	#error COLL_LIST_TYPE must be defined
#endif
#if !defined(COLL_LIST_ARG_TYPE)
	#error COLL_LIST_ARG_TYPE must be defined
#endif



// ������(ͨ��ģ����)
class COLLECTION_IMP COLL_LIST_CLASS
{
public:
	COLL_LIST_CLASS(LONG nBlockSize=10);
	~COLL_LIST_CLASS();
	CONST COLL_LIST_CLASS& operator=(CONST COLL_LIST_CLASS& Src) { Copy(&Src); return (*this); }

	// ������ȡ���п�
	LONG GetCount() CONST;
	BOOL IsEmpty() CONST;

	// ͷ����β����ȡ
	COLL_LIST_TYPE& GetHead();
	COLL_LIST_TYPE  GetHead() CONST;
	COLL_LIST_TYPE& GetTail();
	COLL_LIST_TYPE  GetTail() CONST;

	// ɾ��ͷ�������β������
	COLL_LIST_TYPE RemoveHead();
	COLL_LIST_TYPE RemoveTail();

	// �б������
	POSITION AddHeadConst(CONST COLL_LIST_TYPE& newElement);
	POSITION AddTailConst(CONST COLL_LIST_TYPE& newElement);
	POSITION AddHead(COLL_LIST_ARG_TYPE newElement);
	POSITION AddTail(COLL_LIST_ARG_TYPE newElement);

	// �б�ϲ�
	VOID AppendHead(CONST COLL_LIST_CLASS* pNewList);
	VOID AppendTail(CONST COLL_LIST_CLASS* pNewList);
	VOID Copy(CONST COLL_LIST_CLASS* pNewList) { RemoveAll(); AppendTail(pNewList); }


	// �б������
	VOID RemoveAll();

	// ���ݽ�������
	BOOL DoDataEPX(CXMLProfileSection* pPX);

	// �б������
	POSITION GetHeadPosition() CONST;
	POSITION GetTailPosition() CONST;
	COLL_LIST_TYPE& GetNext(POSITION& rPosition);
	COLL_LIST_TYPE  GetNext(POSITION& rPosition) CONST;
	COLL_LIST_TYPE& GetPrev(POSITION& rPosition);
	COLL_LIST_TYPE  GetPrev(POSITION& rPosition) CONST;

	// �б����ȡ������
	COLL_LIST_TYPE& GetAt(POSITION position);
	COLL_LIST_TYPE  GetAt(POSITION position) CONST;
	VOID SetAt(POSITION pos,COLL_LIST_ARG_TYPE newElement);
	POSITION PositionOf(COLL_LIST_TYPE* pData);

	// �б�ɾ��
	VOID RemoveAt(POSITION position);
	VOID RemoveByPtr(COLL_LIST_TYPE* pData);

	// �б����
	POSITION InsertBefore(POSITION position,COLL_LIST_ARG_TYPE newElement);
	POSITION InsertAfter(POSITION position,COLL_LIST_ARG_TYPE newElement);

	// �������
	POSITION Find(COLL_LIST_ARG_TYPE searchValue,POSITION startAfter=NULL) CONST;
	POSITION FindIndex(LONG nIndex) CONST;
	BOOL RemoveValue(COLL_LIST_ARG_TYPE searchValue);
protected:
	struct CNode
	{	CNode*	pNext;
		CNode*	pPrev;
		COLL_LIST_TYPE data;
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


//////////////////////////////////////////////////////////////////////////
// COLL_LIST_CLASS:����ʵ��
//////////////////////////////////////////////////////////////////////////
inline LONG COLL_LIST_CLASS::GetCount() CONST
	{ return m_nCount; }

inline BOOL COLL_LIST_CLASS::IsEmpty() CONST
	{ return m_nCount==0; }

inline COLL_LIST_TYPE& COLL_LIST_CLASS::GetHead()
	{	CLIBASSERT(m_pNodeHead!=NULL);
		return m_pNodeHead->data;
	}

inline COLL_LIST_TYPE COLL_LIST_CLASS::GetHead() CONST
	{	CLIBASSERT(m_pNodeHead!=NULL);
		return m_pNodeHead->data;
	}

inline COLL_LIST_TYPE& COLL_LIST_CLASS::GetTail()
	{	CLIBASSERT(m_pNodeTail!=NULL);
		return m_pNodeTail->data;
	}

inline COLL_LIST_TYPE COLL_LIST_CLASS::GetTail() CONST
	{	CLIBASSERT(m_pNodeTail!=NULL);
		return m_pNodeTail->data;
	}

inline POSITION COLL_LIST_CLASS::GetHeadPosition() CONST
	{ return (POSITION) m_pNodeHead; }

inline POSITION COLL_LIST_CLASS::GetTailPosition() CONST
	{ return (POSITION) m_pNodeTail; }

inline COLL_LIST_TYPE& COLL_LIST_CLASS::GetNext(POSITION& rPosition)
	{	CNode* pNode=(CNode*) rPosition;
		CLIBASSERT(clibIsValidAddress(pNode,size_of(CNode)));
		rPosition=(POSITION) pNode->pNext;
		return pNode->data;
	}

inline COLL_LIST_TYPE COLL_LIST_CLASS::GetNext(POSITION& rPosition) CONST
	{	CNode* pNode=(CNode*) rPosition;
		CLIBASSERT(clibIsValidAddress(pNode,size_of(CNode)));
		rPosition=(POSITION) pNode->pNext;
		return pNode->data;
	}

inline COLL_LIST_TYPE& COLL_LIST_CLASS::GetPrev(POSITION& rPosition)
	{	CNode* pNode=(CNode*) rPosition;
		CLIBASSERT(clibIsValidAddress(pNode,size_of(CNode)));
		rPosition=(POSITION) pNode->pPrev;
		return pNode->data;
	}

inline COLL_LIST_TYPE COLL_LIST_CLASS::GetPrev(POSITION& rPosition) CONST
	{	CNode* pNode=(CNode*) rPosition;
		CLIBASSERT(clibIsValidAddress(pNode,size_of(CNode)));
		rPosition=(POSITION) pNode->pPrev;
		return pNode->data;
	}

inline COLL_LIST_TYPE& COLL_LIST_CLASS::GetAt(POSITION position)
	{	CNode* pNode=(CNode*) position;
		CLIBASSERT(clibIsValidAddress(pNode,size_of(CNode)));
		return pNode->data;
	}

inline COLL_LIST_TYPE COLL_LIST_CLASS::GetAt(POSITION position) CONST
	{	CNode* pNode=(CNode*) position;
		CLIBASSERT(clibIsValidAddress(pNode,size_of(CNode)));
		return pNode->data;
	}

inline VOID COLL_LIST_CLASS::SetAt(POSITION pos,COLL_LIST_ARG_TYPE newElement)
	{	CNode* pNode=(CNode*) pos;
		CLIBASSERT(clibIsValidAddress(pNode,size_of(CNode)));
		pNode->data=newElement;
	}

inline POSITION COLL_LIST_CLASS::PositionOf(COLL_LIST_TYPE* pData)
	{	CNode* pNode=(CNode*)((LPBYTE)((LPVOID)pData)-ex_offset_of(struct CNode,data));
		return (POSITION)pNode;
	}

#undef COLL_LIST_CLASS
#undef COLL_LIST_TYPE
#undef COLL_LIST_ARG_TYPE
