#if !defined(__COLL__H__)
	#error coll.h must be included
#endif
#if !defined(COLL_MULTIMAP_CLASS)
	#error COLL_MULTIMAP_CLASS must be defined
#endif
#if !defined(COLL_MULTIMAP_KEY)
	#error COLL_MULTIMAP_KEY must be defined
#endif
#if !defined(COLL_MULTIMAP_ARG_KEY)
	#error COLL_MULTIMAP_ARG_KEY must be defined
#endif
#if !defined(COLL_MULTIMAP_VALUE)
	#error COLL_MULTIMAP_VALUE must be defined
#endif
#if !defined(COLL_MULTIMAP_ARG_VALUE)
	#error COLL_MULTIMAP_ARG_VALUE must be defined
#endif


// ��ӳ����(ͨ��ģ����)
class COLLECTION_IMP COLL_MULTIMAP_CLASS
{
NO_ASSIGN_OPERATOR(COLL_MULTIMAP_CLASS);
public:
	COLL_MULTIMAP_CLASS(LONG nBlockSize=1,UINT nKeyOffset=0,UINT nValueOffset=0);
	~COLL_MULTIMAP_CLASS();

	// ��ȡӳ��������п�
	LONG GetKeyCount() CONST;
	BOOL IsKeyEmpty() CONST;

	// ӳ��Ĳ���,�����Ƿ���ڱ�־
	BOOL Lookup(COLL_MULTIMAP_ARG_KEY Key,COLL_MULTIMAP_VALUE& rValue) CONST;

	// ӳ�����
	// ����TRUE:�ڵ��Ѿ�����,�����ݱ�����,����FALSE,�ڵ㲻����,���������´���
	BOOL SetAt(COLL_MULTIMAP_ARG_KEY Key,COLL_MULTIMAP_ARG_VALUE newValue);

	// ɾ����
	BOOL RemoveKey(COLL_MULTIMAP_ARG_KEY Key);
	VOID RemoveAll();
	
	// ���ݽ�������
	BOOL DoDataEPX(CXMLProfileSection* pPX);

	// ���ҿ�ʼλ�ú�ȡ�ù�����
	POSITION GetKeyStartPosition() CONST;
	VOID GetNextKeyAssoc(POSITION& rNextPosition,COLL_MULTIMAP_KEY& rKey,COLL_MULTIMAP_VALUE& rValue) CONST;

	// ���ҿ�ʼλ�ú�ȡ�ù���ֵ
	POSITION GetValueStartPosition(COLL_MULTIMAP_ARG_VALUE Value) CONST;
	VOID GetNextValueAssoc(POSITION& rNextPosition,COLL_MULTIMAP_KEY& rKey) CONST;

	// HASH����
	UINT GetHashTableSize() CONST;
	VOID InitHashTable(UINT nHashSize,BOOL bAllocNow=TRUE);
protected:
	// ӳ���Ԫ
	struct CAssoc
	{	CAssoc* m_pKeyNext;
		CAssoc* m_pValueNext;
		CAssoc* m_pLinkNext;
		COLL_MULTIMAP_KEY m_Key;
		COLL_MULTIMAP_VALUE m_Value;
	};
protected:
	CAssoc* NewAssoc();
	VOID FreeAssoc(CAssoc* pAssoc);
	CAssoc* GetAssocAtByKey(COLL_MULTIMAP_ARG_KEY Key,UINT& nHash) CONST;
	CAssoc* GetAssocAtByValue(COLL_MULTIMAP_ARG_VALUE Value,UINT& nHash) CONST;
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


//////////////////////////////////////////////////////////////////////////
// COLL_MULTIMAP_CLASS����ʵ��
//////////////////////////////////////////////////////////////////////////

inline LONG COLL_MULTIMAP_CLASS::GetKeyCount() CONST
	{ return m_nKeyCount; }

inline BOOL COLL_MULTIMAP_CLASS::IsKeyEmpty() CONST
	{ return m_nKeyCount==0; }

inline UINT COLL_MULTIMAP_CLASS::GetHashTableSize() CONST
	{ return m_nHashTableSize; }


#undef COLL_MULTIMAP_CLASS
#undef COLL_MULTIMAP_KEY
#undef COLL_MULTIMAP_ARG_KEY
#undef COLL_MULTIMAP_VALUE
#undef COLL_MULTIMAP_ARG_VALUE
