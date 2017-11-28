#if !defined(__COLL__H__)
	#error coll.h must be included
#endif
#if !defined(COLL_ARRAY_CLASS)
	#error COLL_ARRAY_CLASS must be defined
#endif
#if !defined(COLL_ARRAY_TYPE)
	#error COLL_ARRAY_TYPE must be defined
#endif
#if !defined(COLL_ARRAY_ARG_TYPE)
	#error COLL_ARRAY_ARG_TYPE must be defined
#endif

// 数组类(通用类)
class COLLECTION_IMP COLL_ARRAY_CLASS
{
public:
	COLL_ARRAY_CLASS(LONG nGrowBy=0);
	~COLL_ARRAY_CLASS();
	CONST COLL_ARRAY_CLASS& operator=(CONST COLL_ARRAY_CLASS& Src) { Copy(&Src); return (*this); }

	// 属性获取
	LONG GetSize() CONST;
	LONG GetUpperBound() CONST;
	VOID SetSize(LONG nNewSize,LONG nGrowBy=-1);

	// 操作
	VOID FreeExtra();
	VOID RemoveAll();

	// 单元访问
	COLL_ARRAY_TYPE GetAt(LONG nIndex) CONST;
	VOID SetAt(LONG nIndex,COLL_ARRAY_ARG_TYPE newElement);
	COLL_ARRAY_TYPE& ElementAt(LONG nIndex);

	// 直接单元访问
	CONST COLL_ARRAY_TYPE* GetData() CONST;
	COLL_ARRAY_TYPE* GetData();

	// 单元添加
	VOID SetAtGrow(LONG nIndex,COLL_ARRAY_ARG_TYPE newElement);
	LONG Add(COLL_ARRAY_ARG_TYPE newElement);
	LONG Append(CONST COLL_ARRAY_CLASS* psrc);
	VOID Copy(CONST COLL_ARRAY_CLASS* psrc);
	VOID Copy(CONST COLL_ARRAY_TYPE* pDatas,LONG nCount);

	// 操作重载
	COLL_ARRAY_TYPE operator[](LONG nIndex) CONST;
	COLL_ARRAY_TYPE& operator[](LONG nIndex);

	// 单元插入和删除(需要单元移动)
	VOID InsertAt(LONG nIndex,COLL_ARRAY_ARG_TYPE newElement,LONG nCount=1);
	VOID RemoveAt(LONG nIndex,LONG nCount=1);
	VOID InsertAt(LONG nStartIndex,COLL_ARRAY_CLASS* pNewArray);
	// 对象查找
	LONG Find(COLL_ARRAY_ARG_TYPE searchValue,LONG startAfter=-1) CONST;
	// 数据交换函数
	BOOL DoDataEPX(CXMLProfileSection* pPX);
protected:
	COLL_ARRAY_TYPE*	m_pData;	 // 数组指针
	LONG	m_nSize;     // 数组大小
	LONG	m_nMaxSize;  // 数组被分配的大小
	LONG	m_nGrowBy;   // 数组每次增大的大小
};


//////////////////////////////////////////////////////////////////////////
// COLL_ARRAY_CLASS:内联实现
//////////////////////////////////////////////////////////////////////////
inline LONG COLL_ARRAY_CLASS::GetSize() CONST
	{ return m_nSize; }

inline LONG COLL_ARRAY_CLASS::GetUpperBound() CONST
	{ return m_nSize-1; }

inline void COLL_ARRAY_CLASS::RemoveAll()
	{ SetSize(0,-1); }

inline COLL_ARRAY_TYPE COLL_ARRAY_CLASS::GetAt(LONG nIndex) CONST
	{	CLIBASSERT(nIndex>=0 && nIndex<m_nSize);
		return m_pData[nIndex];
	}

inline void COLL_ARRAY_CLASS::SetAt(LONG nIndex,COLL_ARRAY_ARG_TYPE newElement)
	{	CLIBASSERT(nIndex>=0 && nIndex<m_nSize);
		m_pData[nIndex]=newElement;
	}

inline COLL_ARRAY_TYPE& COLL_ARRAY_CLASS::ElementAt(LONG nIndex)
	{	CLIBASSERT(nIndex>=0 && nIndex<m_nSize);
		return m_pData[nIndex];
	}

inline CONST COLL_ARRAY_TYPE* COLL_ARRAY_CLASS::GetData() CONST
	{ return (CONST COLL_ARRAY_TYPE*)m_pData; }

inline COLL_ARRAY_TYPE* COLL_ARRAY_CLASS::GetData()
	{ return (COLL_ARRAY_TYPE*)m_pData; }

inline LONG COLL_ARRAY_CLASS::Add(COLL_ARRAY_ARG_TYPE newElement)
	{ LONG nIndex=m_nSize; SetAtGrow(nIndex,newElement); return nIndex; }

inline COLL_ARRAY_TYPE COLL_ARRAY_CLASS::operator[](LONG nIndex) CONST
	{ return GetAt(nIndex); }

inline COLL_ARRAY_TYPE& COLL_ARRAY_CLASS::operator[](LONG nIndex)
	{ return ElementAt(nIndex); }


#undef COLL_ARRAY_CLASS
#undef COLL_ARRAY_TYPE
#undef COLL_ARRAY_ARG_TYPE
#undef COLL_IS_CLASS

