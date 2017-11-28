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


// 多映射类(通用模板类)
class COLLECTION_IMP COLL_MULTIMAP_CLASS
{
NO_ASSIGN_OPERATOR(COLL_MULTIMAP_CLASS);
public:
	COLL_MULTIMAP_CLASS(LONG nBlockSize=1,UINT nKeyOffset=0,UINT nValueOffset=0);
	~COLL_MULTIMAP_CLASS();

	// 读取映射个数和判空
	LONG GetKeyCount() CONST;
	BOOL IsKeyEmpty() CONST;

	// 映射的查找,返回是否存在标志
	BOOL Lookup(COLL_MULTIMAP_ARG_KEY Key,COLL_MULTIMAP_VALUE& rValue) CONST;

	// 映射添加
	// 返回TRUE:节点已经存在,其数据被覆盖,返回FALSE,节点不存在,其数据重新创建
	BOOL SetAt(COLL_MULTIMAP_ARG_KEY Key,COLL_MULTIMAP_ARG_VALUE newValue);

	// 删除键
	BOOL RemoveKey(COLL_MULTIMAP_ARG_KEY Key);
	VOID RemoveAll();
	
	// 数据交换函数
	BOOL DoDataEPX(CXMLProfileSection* pPX);

	// 查找开始位置和取得关联键
	POSITION GetKeyStartPosition() CONST;
	VOID GetNextKeyAssoc(POSITION& rNextPosition,COLL_MULTIMAP_KEY& rKey,COLL_MULTIMAP_VALUE& rValue) CONST;

	// 查找开始位置和取得关联值
	POSITION GetValueStartPosition(COLL_MULTIMAP_ARG_VALUE Value) CONST;
	VOID GetNextValueAssoc(POSITION& rNextPosition,COLL_MULTIMAP_KEY& rKey) CONST;

	// HASH表处理
	UINT GetHashTableSize() CONST;
	VOID InitHashTable(UINT nHashSize,BOOL bAllocNow=TRUE);
protected:
	// 映射表单元
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


//////////////////////////////////////////////////////////////////////////
// COLL_MULTIMAP_CLASS内联实现
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
