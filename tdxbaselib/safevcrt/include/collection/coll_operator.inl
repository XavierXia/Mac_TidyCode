

// 对应类型的HASH函数
CLIB_INLINE UINT CLIBAPI GenHashKey(COLL_TYPE Key,UINT nKeyOffset)  { return (UINT)(Key>>nKeyOffset); }


// 对应类型的构造和析构函数
CLIB_INLINE void CLIBAPI CollConstructElements(UNALIGNED COLL_TYPE* pElements, int nCount)
		{
			if(nCount>0) memset((void*)pElements,0,nCount*size_of(COLL_TYPE));
			#ifndef COLLECTION_FAST_MEM
				for(; nCount--; pElements++)
					::new((void*)pElements) COLL_TYPE;
			#endif
		}
CLIB_INLINE void CLIBAPI CollDestructElements(UNALIGNED COLL_TYPE* pElements,int nCount)
		{
			#ifndef COLLECTION_FAST_MEM
				for(; nCount--; pElements++)
					pElements->~COLL_TYPE();
			#endif
			if(nCount>0) memset((void*)pElements,0,nCount*size_of(COLL_TYPE));
		}
CLIB_INLINE void CLIBAPI CollCopyElements(UNALIGNED COLL_TYPE* pDest,const COLL_TYPE* pSrc, int nCount)
		{	while(nCount--)
			{	*pDest++ = *pSrc++;
			}
		}
CLIB_INLINE BOOL CLIBAPI CollCompareElements(const UNALIGNED COLL_TYPE* pElement1,const UNALIGNED COLL_TYPE* pElement2)
		{	return *pElement1==*pElement2;
		}



// 对应类型的序列化函数
#ifdef COLL_EPXFUNC
	BOOL COLLECTION_IMP CLIBAPI CollDoDataEPXElements(COLL_TYPE* pElement,CXMLProfileSection* pPX,LPCSTR pszName);
#endif

