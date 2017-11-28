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


// 映射类(通用模板类)
class COLLECTION_IMP COLL_MAP_CLASS
{
NO_ASSIGN_OPERATOR(COLL_MAP_CLASS);
public:
	COLL_MAP_CLASS(LONG nBlockSize=1,UINT nKeyOffset=0);
	~COLL_MAP_CLASS();

	// 读取映射个数和判空
	LONG GetCount() CONST;
	BOOL IsEmpty() CONST;

	// 映射的查找,返回是否存在标志
	BOOL Lookup(COLL_MAP_ARG_KEY Key,COLL_MAP_VALUE& rValue) CONST;

	// 映射查找,返回查找到的数据,如果查找不到,返回空数据(GetValueAt)或者创建空数据([])
	COLL_MAP_ARG_VALUE GetValueAt(COLL_MAP_ARG_KEY Key) CONST;
	COLL_MAP_ARG_VALUE operator[](COLL_MAP_ARG_KEY Key);

	// 映射添加
	// 返回TRUE:节点已经存在,其数据被覆盖,返回FALSE,节点不存在,其数据重新创建
	BOOL SetAt(COLL_MAP_ARG_KEY Key,COLL_MAP_ARG_VALUE newValue);

	// 删除键
	BOOL RemoveKey(COLL_MAP_ARG_KEY Key);
	VOID RemoveAll();
	
	// 数据交换函数
	BOOL DoDataEPX(CXMLProfileSection* pPX);

	// 查找开始位置和取得关联键
	POSITION GetStartPosition() CONST;
	VOID GetNextAssoc(POSITION& rNextPosition,COLL_MAP_KEY& rKey,COLL_MAP_VALUE& rValue) CONST;

	// HASH表处理
	UINT GetHashTableSize() CONST;
	VOID InitHashTable(UINT nHashSize,BOOL bAllocNow=TRUE);
protected:
	// 映射表单元
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
// COLL_MAP_CLASS内联实现
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
