//////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2006 - All Rights Reserved
//  ģ������: coll_hashlist
//  ��������: 2006/09/28
//  �����д: HASH��ʵ����
//  ����˵��: 
//  ����ʾ��: 
//  �޸ļ�¼:
//////////////////////////////////////////////////////////////////////////
#if !defined(__COLL__H__)
	#error coll.h must be included
#endif
#if !defined(COLL_HASHLIST_CLASS)
	#error COLL_HASHLIST_CLASS must be defined
#endif
#if !defined(COLL_HASHLIST_KEY)
	#error COLL_HASHLIST_KEY must be defined
#endif
#if !defined(COLL_HASHLIST_ARG_KEY)
	#error COLL_HASHLIST_ARG_KEY must be defined
#endif



// HASH����
class COLLECTION_IMP COLL_HASHLIST_CLASS
{
NO_ASSIGN_OPERATOR(COLL_HASHLIST_CLASS);
public:
	COLL_HASHLIST_CLASS(LONG nBlockSize=10,UINT nKeyOffset=0);
	~COLL_HASHLIST_CLASS();

	// ��ȡHASH���ݸ������п�
	LONG GetCount() CONST;
	BOOL IsEmpty() CONST;

	// ӳ��Ĳ���,�����Ƿ���ڱ�־
	BOOL Lookup(COLL_HASHLIST_ARG_KEY Key) CONST;
	BOOL operator[](COLL_HASHLIST_ARG_KEY Key) CONST;

	// ӳ������
	VOID InsertKey(COLL_HASHLIST_ARG_KEY Key);
	BOOL RemoveKey(COLL_HASHLIST_ARG_KEY Key);
	VOID RemoveAll();

	// ���ݽ�������
	BOOL DoDataEPX(CXMLProfileSection* pPX);

	// ���ҿ�ʼλ�ú�ȡ�ù�����
	POSITION GetStartPosition() CONST;
	VOID GetNextAssoc(POSITION& rNextPosition,COLL_HASHLIST_KEY& rKey) CONST;

	// HASH������
	UINT GetHashTableSize() CONST;
	VOID InitHashTable(UINT nHashSize,BOOL bAllocNow=TRUE);
protected:
	// ӳ�����Ԫ
	struct CAssoc
	{	CAssoc* m_pNext;
		COLL_HASHLIST_KEY m_Key;
	};
protected:
	CAssoc* NewAssoc();
	VOID FreeAssoc(CAssoc* pAssoc);
	CAssoc* GetAssocAt(COLL_HASHLIST_ARG_KEY Key,UINT& nHash) CONST;
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
// COLL_HASHLIST_CLASS����ʵ��
//////////////////////////////////////////////////////////////////////////

inline LONG COLL_HASHLIST_CLASS::GetCount() CONST
	{ return m_nCount; }


inline BOOL COLL_HASHLIST_CLASS::IsEmpty() CONST
	{ return m_nCount==0; }


inline POSITION COLL_HASHLIST_CLASS::GetStartPosition() CONST
	{ return (m_nCount==0)?NULL:BEFORE_START_POSITION; }


inline UINT COLL_HASHLIST_CLASS::GetHashTableSize() CONST
	{ return m_nHashTableSize; }



#undef COLL_HASHLIST_CLASS
#undef COLL_HASHLIST_KEY
#undef COLL_HASHLIST_ARG_KEY
