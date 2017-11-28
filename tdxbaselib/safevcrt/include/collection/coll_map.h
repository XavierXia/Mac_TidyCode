#if !defined(__COLL__H__)
	#error coll.h must be included
#endif
#if !defined(COLL_MAP_CLASS)
	#error COLL_MAP_CLASS must be defined
#endif
#if !defined(COLL_MAP_KEY)
	#error COLL_MAP_KEY must be defined
#endif
#if !defined(COLL_MAP_ARG_KEY)
	#error COLL_MAP_ARG_KEY must be defined
#endif
#if !defined(COLL_MAP_VALUE)
	#error COLL_MAP_VALUE must be defined
#endif
#if !defined(COLL_MAP_ARG_VALUE)
	#error COLL_MAP_ARG_VALUE must be defined
#endif


// ӳ����(ͨ��ģ����)
class COLLECTION_IMP COLL_MAP_CLASS
{
NO_ASSIGN_OPERATOR(COLL_MAP_CLASS);
public:
	COLL_MAP_CLASS(LONG nBlockSize=1,UINT nKeyOffset=0);
	~COLL_MAP_CLASS();

	// ��ȡӳ��������п�
	LONG GetCount() CONST;
	BOOL IsEmpty() CONST;

	// ӳ��Ĳ���,�����Ƿ���ڱ�־
	BOOL Lookup(COLL_MAP_ARG_KEY Key,COLL_MAP_VALUE& rValue) CONST;

	// ӳ�����,���ز��ҵ�������,������Ҳ���,���ؿ�����(GetValueAt)���ߴ���������([])
	COLL_MAP_ARG_VALUE GetValueAt(COLL_MAP_ARG_KEY Key) CONST;
	COLL_MAP_ARG_VALUE operator[](COLL_MAP_ARG_KEY Key);

	// ӳ�����
	// ����TRUE:�ڵ��Ѿ�����,�����ݱ�����,����FALSE,�ڵ㲻����,���������´���
	BOOL SetAt(COLL_MAP_ARG_KEY Key,COLL_MAP_ARG_VALUE newValue);

	// ɾ����
	BOOL RemoveKey(COLL_MAP_ARG_KEY Key);
	VOID RemoveAll();
	
	// ���ݽ�������
	BOOL DoDataEPX(CXMLProfileSection* pPX);

	// ���ҿ�ʼλ�ú�ȡ�ù�����
	POSITION GetStartPosition() CONST;
	VOID GetNextAssoc(POSITION& rNextPosition,COLL_MAP_KEY& rKey,COLL_MAP_VALUE& rValue) CONST;

	// HASH����
	UINT GetHashTableSize() CONST;
	VOID InitHashTable(UINT nHashSize,BOOL bAllocNow=TRUE);
protected:
	// ӳ���Ԫ
	struct CAssoc
	{	CAssoc* m_pNext;
		COLL_MAP_KEY m_Key;
		COLL_MAP_VALUE m_Value;
	};
protected:
	CAssoc* NewAssoc();
	VOID FreeAssoc(CAssoc* pAssoc);
	CAssoc* GetAssocAt(COLL_MAP_ARG_KEY Key,UINT& nHash) CONST;
protected:
	CAssoc**	m_pHashTable;
	UINT		m_nHashTableSize;
	UINT		m_nKeyOffset;
	LONG		m_nCount;
	CAssoc*		m_pFreeList;
	TBUCKET*	m_pBlocks;
	LONG		m_nBlockSize;
};


//////////////////////////////////////////////////////////////////////////
// COLL_MAP_CLASS����ʵ��
//////////////////////////////////////////////////////////////////////////

inline LONG COLL_MAP_CLASS::GetCount() CONST
	{ return m_nCount; }

inline BOOL COLL_MAP_CLASS::IsEmpty() CONST
	{ return m_nCount==0; }

inline POSITION COLL_MAP_CLASS::GetStartPosition() CONST
	{ return (m_nCount==0)?NULL:BEFORE_START_POSITION; }

inline UINT COLL_MAP_CLASS::GetHashTableSize() CONST
	{ return m_nHashTableSize; }


#undef COLL_MAP_CLASS
#undef COLL_MAP_KEY
#undef COLL_MAP_ARG_KEY
#undef COLL_MAP_VALUE
#undef COLL_MAP_ARG_VALUE
