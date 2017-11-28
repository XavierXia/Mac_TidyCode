#ifndef __CLIB_TEMPL__INL__
#define __CLIB_TEMPL__INL__

#ifndef __CLIB_TEMPL__H__
	#error clibtempl.h must be included
#endif
#ifdef PLATFORM_WINDOWS
	#include <new.h>
#else
	#include "new"
#endif // PLATFORM_WINDOWS

// 数据构造和析构函数
template<class TYPE>
CLIB_INLINE void CLIBAPI CollConstructElements(UNALIGNED TYPE* pElements, int nCount)
{
	if(nCount>0) memset((void*)pElements,0,nCount*size_of(TYPE));
	for(; nCount--; pElements++)
		::new((void*)pElements) TYPE;
}

template<class TYPE>
CLIB_INLINE void CLIBAPI CollDestructElements(UNALIGNED TYPE* pElements,int nCount)
{	for(; nCount--; pElements++)
		pElements->~TYPE();
	if(nCount>0) memset((void*)pElements,0,nCount*size_of(TYPE));
}


template<class TYPE>
CLIB_INLINE void CLIBAPI CollCopyElements(UNALIGNED TYPE* pDest,const TYPE* pSrc, int nCount)
{	while(nCount--)
	{	*pDest++ = *pSrc++;
	}
}

template<class TYPE,class ARG_TYPE>
CLIB_INLINE BOOL CLIBAPI CollCompareElements(const UNALIGNED TYPE* pElement1,const UNALIGNED ARG_TYPE* pElement2)
{	return (*pElement1==*pElement2);
}

template<class TYPE>
CLIB_INLINE BOOL CLIBAPI CollDoDataEPXElements(UNALIGNED TYPE* pElement,CXMLProfileSection* pPX,LPCSTR pszName)
{	UNREFERENCED_PARAMETER(pElement);
	CHAR szValue[MAX_PATH]={"NotSupport"};
	EPX_NChar(pPX,(pszName==NULL)?"VALUE":pszName,szValue,size_of(szValue),"");
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
// HASH算法实现
//////////////////////////////////////////////////////////////////////////

// 常规的HASH函数
#ifdef GENERAL_HASHKEY
	template<class ARG_KEY>
	CLIB_INLINE UINT CLIBAPI GenHashKey(ARG_KEY Key,UINT nKeyOffset)
	{
		#if defined(PLATFORM_WINDOWS)
			return ((UINT)(LPVOID)(DWORD)Key)>>nKeyOffset;
		#elif defined(_ARCH_AMD64_)
			return ((UINT)((long)(LPVOID)Key))>>nKeyOffset;
		#else
			return ((UINT)(LPVOID)(DWORD)Key)>>nKeyOffset;
		#endif
	}
#endif


//////////////////////////////////////////////////////////////////////////
// TMap:标准实现
//////////////////////////////////////////////////////////////////////////

template<class KEY,class ARG_KEY,class VALUE,class ARG_VALUE>
TMap<KEY,ARG_KEY,VALUE,ARG_VALUE>::TMap(LONG nBlockSize,UINT nKeyOffset)
{	CLIBASSERT(nBlockSize>0);
	m_pHashTable=NULL;
	m_nHashTableSize=17;
	m_nKeyOffset=nKeyOffset;
	m_nCount=0;
	m_pFreeList=NULL;
	m_pBlocks=NULL;
	m_nBlockSize=nBlockSize;
}

template<class KEY,class ARG_KEY,class VALUE,class ARG_VALUE>
TMap<KEY,ARG_KEY,VALUE,ARG_VALUE>::~TMap()
{	RemoveAll();
	CLIBASSERT(m_nCount==0);
}

// 判断键值
template<class KEY,class ARG_KEY,class VALUE,class ARG_VALUE>
VALUE* TMap<KEY,ARG_KEY,VALUE,ARG_VALUE>::Exist(ARG_KEY Key)
{	UINT nHash=0;
	CAssoc* pAssoc=GetAssocAt(Key,nHash);
	if(pAssoc==NULL) return NULL;
	return &pAssoc->m_Value;
}

// 查找映射,如果不存在,则返回错误
template<class KEY,class ARG_KEY,class VALUE,class ARG_VALUE>
BOOL TMap<KEY,ARG_KEY,VALUE,ARG_VALUE>::Lookup(ARG_KEY Key,VALUE& rValue) CONST
{
	UINT nHash=0;
	CAssoc* pAssoc=GetAssocAt(Key,nHash);
	if(pAssoc==NULL) return FALSE;
	rValue=pAssoc->m_Value;
	return TRUE;
}

// 映射查找,返回查找到的数据,如果查找不到,返回空数据(GetValueAt)或者创建空数据([])
template<class KEY,class ARG_KEY,class VALUE,class ARG_VALUE>
VALUE& TMap<KEY,ARG_KEY,VALUE,ARG_VALUE>::operator[](ARG_KEY Key)
{
	UINT nHash;
	CAssoc* pAssoc=NULL;
	if((pAssoc=GetAssocAt(Key,nHash))==NULL)
	{	if(m_pHashTable==NULL)
			InitHashTable(m_nHashTableSize);
		pAssoc=NewAssoc();
		pAssoc->m_Key=Key;
		pAssoc->m_pNext=m_pHashTable[nHash];
		m_pHashTable[nHash]=pAssoc;
	}
	return pAssoc->m_Value;
}

// 添加键值
template<class KEY,class ARG_KEY,class VALUE,class ARG_VALUE>
CLIB_INLINE BOOL TMap<KEY,ARG_KEY,VALUE,ARG_VALUE>::SetAt(ARG_KEY Key,ARG_VALUE newValue)
{
	UINT nHash;
	CAssoc* pAssoc=NULL;
	BOOL bKeyExist=TRUE;
	if((pAssoc=GetAssocAt(Key,nHash))==NULL)
	{	bKeyExist=FALSE;
		if(m_pHashTable==NULL)
			InitHashTable(m_nHashTableSize);
		pAssoc=NewAssoc();
		pAssoc->m_Key=Key;
		pAssoc->m_pNext=m_pHashTable[nHash];
		m_pHashTable[nHash]=pAssoc;
	}
	pAssoc->m_Value=newValue;
	return bKeyExist;
}

// 删除键值
template<class KEY,class ARG_KEY,class VALUE,class ARG_VALUE>
BOOL TMap<KEY,ARG_KEY,VALUE,ARG_VALUE>::RemoveKey(ARG_KEY Key)
{
	if(m_pHashTable==NULL) return FALSE;
	CAssoc** ppAssocPrev;
	ppAssocPrev=&m_pHashTable[GenHashKey(Key,m_nKeyOffset)%m_nHashTableSize];
	CAssoc* pAssoc=NULL;
	for(pAssoc=*ppAssocPrev; pAssoc!=NULL; pAssoc=pAssoc->m_pNext)
	{	if(CollCompareElements(&pAssoc->m_Key,&Key))
		{	*ppAssocPrev=pAssoc->m_pNext;
			FreeAssoc(pAssoc);
			return TRUE;
		}
		ppAssocPrev=&pAssoc->m_pNext;
	}
	return FALSE;
}

// 删除全部键值
template<class KEY,class ARG_KEY,class VALUE,class ARG_VALUE>
VOID TMap<KEY,ARG_KEY,VALUE,ARG_VALUE>::RemoveAll()
{
	if(m_pHashTable!=NULL)
	{	free(m_pHashTable);
		m_pHashTable=NULL;
	}
	m_nCount=0;
	m_pFreeList=NULL;
	m_pBlocks->FreeDataChain();
	m_pBlocks=NULL;
}

// 数据交换函数
template<class KEY,class ARG_KEY,class VALUE,class ARG_VALUE>
BOOL TMap<KEY,ARG_KEY,VALUE,ARG_VALUE>::DoDataEPX(CXMLProfileSection* pPX)
{
	KEY* pTheKey=(KEY*)alloca(size_of(KEY));
	VALUE* pTheValue=(VALUE*)alloca(size_of(VALUE));
	CollConstructElements<KEY>(pTheKey,1);
	CollConstructElements<VALUE>(pTheValue,1);
	if(!pPX->IsStoring())
	{	RemoveAll();
		CXMLProfileEnumerator ItemEnumerator(pPX->GetEnumerator(_T("ITEM"),0));
		POSITION posItemInXml=ItemEnumerator.GetPosition();
		while(posItemInXml!=NULL)
		{	CXMLProfileSection ItemItemSection(ItemEnumerator.GetNext(posItemInXml));
			CollDoDataEPXElements<KEY>(pTheKey,&ItemItemSection,(LPCSTR)"KEY");
			CollDoDataEPXElements<VALUE>(pTheValue,&ItemItemSection,(LPCSTR)"VALUE");
			SetAt(*pTheKey,*pTheValue);
		}
	}
	else
	{	CXMLProfileEnumerator ItemEnumerator(pPX->GetEnumerator(_T("ITEM"),GetCount()));
		POSITION posItemInMap=GetStartPosition();
		POSITION posItemInXml=ItemEnumerator.GetPosition();
		while(posItemInMap!=NULL&&posItemInXml!=NULL)
		{	GetNextAssoc(posItemInMap,*pTheKey,*pTheValue);
			CXMLProfileSection ItemItemSection(ItemEnumerator.GetNext(posItemInXml));
			CollDoDataEPXElements<KEY>(pTheKey,&ItemItemSection,(LPCSTR)"KEY");
			CollDoDataEPXElements<VALUE>(pTheValue,&ItemItemSection,(LPCSTR)"VALUE");
		}
	}
	CollDestructElements<KEY>(pTheKey,1);
	CollDestructElements<VALUE>(pTheValue,1);
	return TRUE;
}

// 获取下一个字段
template<class KEY,class ARG_KEY,class VALUE,class ARG_VALUE>
VOID TMap<KEY,ARG_KEY,VALUE,ARG_VALUE>::GetNextAssoc(POSITION& rNextPosition,KEY& rKey,VALUE& rValue) CONST
{
	// 查找到当前位置
	CLIBASSERT(m_pHashTable!=NULL);
	CAssoc* pAssocRet=(CAssoc*)rNextPosition;
	CLIBASSERT(pAssocRet!=NULL);
	if(pAssocRet==(CAssoc*)BEFORE_START_POSITION)
	{	for(UINT nBucket=0; nBucket<m_nHashTableSize; nBucket++)
			if((pAssocRet=m_pHashTable[nBucket])!=NULL)
				break;
		CLIBASSERT(pAssocRet!=NULL);
	}

	// 继续查找下一个位置
	CLIBASSERT(clibIsValidAddress(pAssocRet,size_of(CAssoc)));
	CAssoc* pAssocNext=NULL;
	if((pAssocNext=pAssocRet->m_pNext)==NULL)
	{	for(UINT nBucket=(GenHashKey(pAssocRet->m_Key,m_nKeyOffset)%m_nHashTableSize)+1; nBucket<m_nHashTableSize; nBucket++)
			if((pAssocNext=m_pHashTable[nBucket])!=NULL)
				break;
	}
	rNextPosition=(POSITION)pAssocNext;
	rKey=pAssocRet->m_Key;
	rValue=pAssocRet->m_Value;
}

// 初始化HASH表
template<class KEY,class ARG_KEY,class VALUE,class ARG_VALUE>
VOID TMap<KEY,ARG_KEY,VALUE,ARG_VALUE>::InitHashTable(UINT nHashSize,BOOL bAllocNow)
{	
	CLIBASSERT(m_nCount==0);
	CLIBASSERT(nHashSize>0);
	if(m_pHashTable!=NULL)
	{	free(m_pHashTable);
		m_pHashTable=NULL;
	}
	if(bAllocNow)
	{	m_pHashTable=(CAssoc**)malloc(size_of(CAssoc*)*nHashSize);
		memset(m_pHashTable,0,size_of(CAssoc*)*nHashSize);
	}
	m_nHashTableSize=nHashSize;
}

// 获取下一个字段
template<class KEY,class ARG_KEY,class VALUE,class ARG_VALUE>
typename TMap<KEY,ARG_KEY,VALUE,ARG_VALUE>::CAssoc*
TMap<KEY,ARG_KEY,VALUE,ARG_VALUE>::NewAssoc()
{
	if(m_pFreeList==NULL)
	{	TBucket* newBlock=TBucket::Create(m_pBlocks,m_nBlockSize,size_of(CAssoc));
		CAssoc* pAssoc=(CAssoc*)newBlock->Data();
		pAssoc+=m_nBlockSize-1;
		for(LONG i=m_nBlockSize-1; i>=0; i--)
		{	pAssoc->m_pNext=m_pFreeList;
			m_pFreeList=pAssoc;
			if(i>0) pAssoc--;
		}
	}
	CLIBASSERT(m_pFreeList!=NULL);
	CAssoc* pAssoc=m_pFreeList;
	m_pFreeList=m_pFreeList->m_pNext;
	m_nCount++;
	CLIBASSERT(m_nCount>0);
	CollConstructElements<KEY>(&pAssoc->m_Key,1);
	CollConstructElements<VALUE>(&pAssoc->m_Value,1);
	pAssoc->m_pNext=NULL;
	return pAssoc;
}

// 释放关联键
template<class KEY,class ARG_KEY,class VALUE,class ARG_VALUE>
VOID TMap<KEY,ARG_KEY,VALUE,ARG_VALUE>::FreeAssoc(typename TMap::CAssoc* pAssoc)
{	CLIBASSERT(m_nCount>0);
	CollDestructElements<VALUE>(&pAssoc->m_Value,1);
	CollDestructElements<KEY>(&pAssoc->m_Key,1);
	pAssoc->m_pNext=m_pFreeList;
	m_pFreeList=pAssoc;
	m_nCount--;
	if(m_nCount==0) RemoveAll();
}

// 获取对应键值的数据
template<class KEY,class ARG_KEY,class VALUE,class ARG_VALUE>
typename TMap<KEY,ARG_KEY,VALUE,ARG_VALUE>::CAssoc*
TMap<KEY,ARG_KEY,VALUE,ARG_VALUE>::GetAssocAt(ARG_KEY Key,UINT& nHash) CONST
{
	nHash=GenHashKey(Key,m_nKeyOffset)%m_nHashTableSize;
	if(m_pHashTable==NULL) return NULL;
	CAssoc* pAssoc=NULL;
	for(pAssoc=m_pHashTable[nHash]; pAssoc!=NULL; pAssoc=pAssoc->m_pNext)
	{	if(CollCompareElements(&pAssoc->m_Key,&Key)) return pAssoc;
	}
	return NULL;
}



//////////////////////////////////////////////////////////////////////////
// TMap内联实现
//////////////////////////////////////////////////////////////////////////
template<class KEY,class ARG_KEY,class VALUE,class ARG_VALUE>
CLIB_INLINE LONG TMap<KEY,ARG_KEY,VALUE,ARG_VALUE>::GetCount() CONST
	{ return m_nCount; }

template<class KEY,class ARG_KEY,class VALUE,class ARG_VALUE>
CLIB_INLINE BOOL TMap<KEY,ARG_KEY,VALUE,ARG_VALUE>::IsEmpty() CONST
	{ return m_nCount==0; }

template<class KEY,class ARG_KEY,class VALUE,class ARG_VALUE>
CLIB_INLINE POSITION TMap<KEY,ARG_KEY,VALUE,ARG_VALUE>::GetStartPosition() CONST
	{ return (m_nCount==0)?NULL:BEFORE_START_POSITION; }

template<class KEY,class ARG_KEY,class VALUE,class ARG_VALUE>
CLIB_INLINE UINT TMap<KEY,ARG_KEY,VALUE,ARG_VALUE>::GetHashTableSize() CONST
	{ return m_nHashTableSize; }





//////////////////////////////////////////////////////////////////////////
// TMultiMap:标准实现
//////////////////////////////////////////////////////////////////////////
template<class KEY,class ARG_KEY,class VALUE,class ARG_VALUE>
TMultiMap<KEY,ARG_KEY,VALUE,ARG_VALUE>::TMultiMap(LONG nBlockSize,UINT nKeyOffset,UINT nValueOffset)
{	CLIBASSERT(nBlockSize>0);
	m_pKeyHashTable=NULL;
	m_pValueHashTable=NULL;
	m_nHashTableSize=17;
	m_nKeyOffset=nKeyOffset;
	m_nValueOffset=nValueOffset;
	m_nKeyCount=0;
	m_pFreeList=NULL;
	m_pBlocks=NULL;
	m_nBlockSize=nBlockSize;
}

template<class KEY,class ARG_KEY,class VALUE,class ARG_VALUE>
TMultiMap<KEY,ARG_KEY,VALUE,ARG_VALUE>::~TMultiMap()
{	RemoveAll();
	CLIBASSERT(m_nKeyCount==0);
}

// 读取映射个数和判空
template<class KEY,class ARG_KEY,class VALUE,class ARG_VALUE>
LONG TMultiMap<KEY,ARG_KEY,VALUE,ARG_VALUE>::GetKeyCount() CONST
{	return m_nKeyCount;
}

template<class KEY,class ARG_KEY,class VALUE,class ARG_VALUE>
BOOL TMultiMap<KEY,ARG_KEY,VALUE,ARG_VALUE>::IsKeyEmpty() CONST
{	return m_nKeyCount==0;
}
	
// 查找映射,如果不存在,则返回错误
template<class KEY,class ARG_KEY,class VALUE,class ARG_VALUE>
BOOL TMultiMap<KEY,ARG_KEY,VALUE,ARG_VALUE>::Lookup(ARG_KEY Key,VALUE& rValue) CONST
{	UINT nHash=0;
	CAssoc* pAssoc=GetAssocAtByKey(Key,nHash);
	if(pAssoc==NULL) return FALSE;
	rValue=pAssoc->m_Value;
	return TRUE;
}

template<class KEY,class ARG_KEY,class VALUE,class ARG_VALUE>
BOOL TMultiMap<KEY,ARG_KEY,VALUE,ARG_VALUE>::SetAt(ARG_KEY Key,ARG_VALUE newValue)
{
	// 查找键值,如果没有则创建新的
	UINT nKeyHash;
	CAssoc* pAssocKey=NULL;
	BOOL bKeyExist=TRUE;
	if((pAssocKey=GetAssocAtByKey(Key,nKeyHash))==NULL)
	{	bKeyExist=FALSE;
		if(m_pKeyHashTable==NULL) InitHashTable(m_nHashTableSize);
		pAssocKey=NewAssoc();
		pAssocKey->m_Key=Key;
		pAssocKey->m_pKeyNext=m_pKeyHashTable[nKeyHash];
		pAssocKey->m_pValueNext=NULL;
		m_pKeyHashTable[nKeyHash]=pAssocKey;
	}
	// 如果键值存在,应该首先删除其映射中查找到对应的键的列表
	// 再从键的列表中删除当前键
	else
	{	// 通过HASH表查找老的数据映射的位置(一定存在)
		CAssoc* pAssocValue=NULL;
		UINT nValueHash;
		pAssocValue=GetAssocAtByValue(pAssocKey->m_Value,nValueHash);
		CLIBVERIFY(pAssocValue!=NULL);
		// 其映射的数据本身就是一个关联的键的链表
		CAssoc* pLinkPrev=NULL;
		CAssoc* pLink=pAssocValue;
		while(pLink!=pAssocKey)
		{	pLinkPrev=pLink;
			pLink=pLink->m_pLinkNext;
		}
		CLIBVERIFY(pLink!=NULL);
		// 需要从链表中删除当前键,如果删除的为链表的第一个单元
		if(pLinkPrev!=NULL)
		{	pLinkPrev->m_pLinkNext=pLink->m_pLinkNext;
			pLink->m_pValueNext=NULL;
			pLink->m_pLinkNext=NULL;
		}
		// 否则是链表的第一个单元,这个单元被登记在HASH表中,需要处理
		// (需要从HASH表中删除或者替换)
		else
		{	CAssoc** ppAssocSeekPrev;
			ppAssocSeekPrev=&m_pValueHashTable[nValueHash];
			CAssoc* pAssocSeek=NULL;
			for(pAssocSeek=*ppAssocSeekPrev; pAssocSeek!=NULL; pAssocSeek=pAssocSeek->m_pValueNext)
			{	if(pAssocSeek==pAssocValue)
				{	// 如果删除后链表为空
					if(pLink->m_pLinkNext==NULL)
					{	(*ppAssocSeekPrev)=pAssocSeek->m_pValueNext;
						pLink->m_pValueNext=NULL;
						pLink->m_pLinkNext=NULL;
					}
					else
					{	CAssoc* pNextLink=pLink->m_pLinkNext;
						pNextLink->m_pValueNext=pAssocSeek->m_pValueNext;
						(*ppAssocSeekPrev)=pNextLink;
						pLink->m_pValueNext=NULL;
						pLink->m_pLinkNext=NULL;
					}
					break;
				}
				ppAssocSeekPrev=&pAssocSeek->m_pValueNext;
			}
		}
	}
	// 设置键值
	pAssocKey->m_Value=newValue;
	// 得到新的HASH,并添加到列表中
	CAssoc* pAssocValue=NULL;
	UINT nValueHash;
	if((pAssocValue=GetAssocAtByValue(newValue,nValueHash))==NULL)
	{	pAssocValue=pAssocKey;
		pAssocValue->m_pValueNext=m_pValueHashTable[nValueHash];
		pAssocValue->m_pLinkNext=NULL;
		m_pValueHashTable[nValueHash]=pAssocValue;
	}
	else
	{	pAssocKey->m_pLinkNext=pAssocValue->m_pLinkNext;
		pAssocValue->m_pLinkNext=pAssocKey;
	}
	return bKeyExist;
}

// 删除键值
template<class KEY,class ARG_KEY,class VALUE,class ARG_VALUE>
BOOL TMultiMap<KEY,ARG_KEY,VALUE,ARG_VALUE>::RemoveKey(ARG_KEY Key)
{	if(m_pKeyHashTable==NULL) return FALSE;
	CAssoc** ppAssocPrev;
	ppAssocPrev=&m_pKeyHashTable[GenHashKey(Key,m_nKeyOffset)%m_nHashTableSize];
	CAssoc* pAssocKey=NULL;
	for(pAssocKey=*ppAssocPrev; pAssocKey!=NULL; pAssocKey=pAssocKey->m_pKeyNext)
	{	if(CollCompareElements(&pAssocKey->m_Key,&Key))
		{	// 通过HASH表查找老的数据映射的位置(一定存在)
			CAssoc* pAssocValue=NULL;
			UINT nValueHash;
			pAssocValue=GetAssocAtByValue(pAssocKey->m_Value,nValueHash);
			CLIBVERIFY(pAssocValue!=NULL);
			// 其映射的数据本身就是一个关联的键的链表
			CAssoc* pLinkPrev=NULL;
			CAssoc* pLink=pAssocValue;
			while(pLink!=pAssocKey)
			{	pLinkPrev=pLink;
				pLink=pLink->m_pLinkNext;
			}
			CLIBVERIFY(pLink!=NULL);
			// 需要从链表中删除当前键,如果删除的为链表的第一个单元
			if(pLinkPrev!=NULL)
			{	pLinkPrev->m_pLinkNext=pLink->m_pLinkNext;
				pLink->m_pValueNext=NULL;
				pLink->m_pLinkNext=NULL;
			}
			// 否则是链表的第一个单元,这个单元被登记在HASH表中,需要处理
			// (需要从HASH表中删除或者替换)
			else
			{	CAssoc** ppAssocSeekPrev;
				ppAssocSeekPrev=&m_pValueHashTable[nValueHash];
				CAssoc* pAssocSeek=NULL;
				for(pAssocSeek=*ppAssocSeekPrev; pAssocSeek!=NULL; pAssocSeek=pAssocSeek->m_pValueNext)
				{	if(pAssocSeek==pAssocValue)
					{	// 如果删除后链表为空
						if(pLink->m_pLinkNext==NULL)
						{	(*ppAssocSeekPrev)=pAssocSeek->m_pValueNext;
							pLink->m_pValueNext=NULL;
							pLink->m_pLinkNext=NULL;
						}
						else
						{	CAssoc* pNextLink=pLink->m_pLinkNext;
							pNextLink->m_pValueNext=pAssocSeek->m_pValueNext;
							(*ppAssocSeekPrev)=pNextLink;
							pLink->m_pValueNext=NULL;
							pLink->m_pLinkNext=NULL;
						}
						break;
					}
					ppAssocSeekPrev=&pAssocSeek->m_pValueNext;
				}
			}
			// 删除键值
			*ppAssocPrev=pAssocKey->m_pKeyNext;
			FreeAssoc(pAssocKey);
			return TRUE;
		}
		ppAssocPrev=&pAssocKey->m_pKeyNext;
	}
	return FALSE;
}

// 删除全部键值
template<class KEY,class ARG_KEY,class VALUE,class ARG_VALUE>
VOID TMultiMap<KEY,ARG_KEY,VALUE,ARG_VALUE>::RemoveAll()
{
	if(m_pKeyHashTable!=NULL)
	{	free(m_pKeyHashTable);
		m_pKeyHashTable=NULL;
	}
	if(m_pValueHashTable!=NULL)
	{	free(m_pValueHashTable);
		m_pValueHashTable=NULL;
	}
	m_nKeyCount=0;
	m_pFreeList=NULL;
	m_pBlocks->FreeDataChain();
	m_pBlocks=NULL;
}

// 数据交换函数
template<class KEY,class ARG_KEY,class VALUE,class ARG_VALUE>
BOOL TMultiMap<KEY,ARG_KEY,VALUE,ARG_VALUE>::DoDataEPX(CXMLProfileSection* pPX)
{
	KEY* pTheKey=(KEY*)alloca(size_of(KEY));
	VALUE* pTheValue=(VALUE*)alloca(size_of(VALUE));
	CollConstructElements<KEY>(pTheKey,1);
	CollConstructElements<VALUE>(pTheValue,1);
	if(!pPX->IsStoring())
	{	RemoveAll();
		CXMLProfileEnumerator ItemEnumerator(pPX->GetEnumerator(_T("ITEM"),0));
		POSITION posItemInXml=ItemEnumerator.GetPosition();
		while(posItemInXml!=NULL)
		{	CXMLProfileSection ItemItemSection(ItemEnumerator.GetNext(posItemInXml));
			CollDoDataEPXElements<KEY>(pTheKey,&ItemItemSection,(LPCSTR)"KEY");
			CollDoDataEPXElements<VALUE>(pTheValue,&ItemItemSection,(LPCSTR)"VALUE");
			SetAt(*pTheKey,*pTheValue);
		}
	}
	else
	{	CXMLProfileEnumerator ItemEnumerator(pPX->GetEnumerator(_T("ITEM"),GetKeyCount()));
		POSITION posItemInMap=GetKeyStartPosition();
		POSITION posItemInXml=ItemEnumerator.GetPosition();
		while(posItemInMap!=NULL&&posItemInXml!=NULL)
		{	GetNextKeyAssoc(posItemInMap,*pTheKey,*pTheValue);
			CXMLProfileSection ItemItemSection(ItemEnumerator.GetNext(posItemInXml));
			CollDoDataEPXElements<KEY>(pTheKey,&ItemItemSection,(LPCSTR)"KEY");
			CollDoDataEPXElements<VALUE>(pTheValue,&ItemItemSection,(LPCSTR)"VALUE");
		}
	}
	CollDestructElements<KEY>(pTheKey,1);
	CollDestructElements<VALUE>(pTheValue,1);
	return TRUE;
}

// 查找开始位置和取得关联值
template<class KEY,class ARG_KEY,class VALUE,class ARG_VALUE>
CLIB_INLINE POSITION TMultiMap<KEY,ARG_KEY,VALUE,ARG_VALUE>::GetValueStartPosition(ARG_VALUE Value) CONST
{
	UINT nValueHash;
	CAssoc* pAssocValue=GetAssocAtByValue(Value,nValueHash);
	return (POSITION)pAssocValue;
}

template<class KEY,class ARG_KEY,class VALUE,class ARG_VALUE>
CLIB_INLINE VOID TMultiMap<KEY,ARG_KEY,VALUE,ARG_VALUE>::GetNextValueAssoc(POSITION& rNextPosition,KEY& rKey) CONST
{	CAssoc* pLink=(CAssoc*)rNextPosition;
	rKey=pLink->m_Key;
	rNextPosition=(POSITION)pLink->m_pLinkNext;
}

// 获取第一个字段位置
template<class KEY,class ARG_KEY,class VALUE,class ARG_VALUE>
CLIB_INLINE POSITION TMultiMap<KEY,ARG_KEY,VALUE,ARG_VALUE>::GetKeyStartPosition() CONST
{
	return (m_nKeyCount==0)?NULL:BEFORE_START_POSITION;
}

// 获取下一个字段
template<class KEY,class ARG_KEY,class VALUE,class ARG_VALUE>
CLIB_INLINE VOID TMultiMap<KEY,ARG_KEY,VALUE,ARG_VALUE>::GetNextKeyAssoc(POSITION& rNextPosition,KEY& rKey,VALUE& rValue) CONST
{
	// 查找到当前位置
	CLIBASSERT(m_pKeyHashTable!=NULL);
	CAssoc* pAssocRet=(CAssoc*)rNextPosition;
	CLIBASSERT(pAssocRet!=NULL);
	if(pAssocRet==(CAssoc*)BEFORE_START_POSITION)
	{	for(UINT nBucket=0; nBucket<m_nHashTableSize; nBucket++)
			if((pAssocRet=m_pKeyHashTable[nBucket])!=NULL)
				break;
		CLIBASSERT(pAssocRet!=NULL);
	}

	// 继续查找下一个位置
	CLIBASSERT(clibIsValidAddress(pAssocRet,size_of(CAssoc)));
	CAssoc* pAssocNext=NULL;
	if((pAssocNext=pAssocRet->m_pKeyNext)==NULL)
	{	for(UINT nBucket=(GenHashKey(pAssocRet->m_Key,m_nKeyOffset)%m_nHashTableSize)+1; nBucket<m_nHashTableSize; nBucket++)
			if((pAssocNext=m_pKeyHashTable[nBucket])!=NULL)
				break;
	}
	rNextPosition=(POSITION)pAssocNext;
	rKey=pAssocRet->m_Key;
	rValue=pAssocRet->m_Value;
}

// 得到HASH表大小
template<class KEY,class ARG_KEY,class VALUE,class ARG_VALUE>
UINT TMultiMap<KEY,ARG_KEY,VALUE,ARG_VALUE>::GetHashTableSize() CONST
{	return m_nHashTableSize;
}

// 初始化HASH表
template<class KEY,class ARG_KEY,class VALUE,class ARG_VALUE>
VOID TMultiMap<KEY,ARG_KEY,VALUE,ARG_VALUE>::InitHashTable(UINT nHashSize,BOOL bAllocNow)
{
	CLIBASSERT(m_nKeyCount==0);
	CLIBASSERT(nHashSize>0);
	if(m_pKeyHashTable!=NULL)
	{	free(m_pKeyHashTable);
		m_pKeyHashTable=NULL;
	}
	if(m_pValueHashTable!=NULL)
	{	free(m_pValueHashTable);
		m_pValueHashTable=NULL;
	}
	if(bAllocNow)
	{	m_pKeyHashTable=(CAssoc**)malloc(size_of(CAssoc*)*nHashSize);
		memset(m_pKeyHashTable,0,size_of(CAssoc*)*nHashSize);
		m_pValueHashTable=(CAssoc**)malloc(size_of(CAssoc*)*nHashSize);
		memset(m_pValueHashTable,0,size_of(CAssoc*)*nHashSize);
	}
	m_nHashTableSize=nHashSize;
}

// 获取下一个字段
template<class KEY,class ARG_KEY,class VALUE,class ARG_VALUE>
typename TMultiMap<KEY,ARG_KEY,VALUE,ARG_VALUE>::CAssoc*
TMultiMap<KEY,ARG_KEY,VALUE,ARG_VALUE>::NewAssoc()
{
	// 如果可用空间表为空,则创建可用空间表
	if(m_pFreeList==NULL)
	{	TBucket* newBlock=TBucket::Create(m_pBlocks,m_nBlockSize,size_of(TMultiMap::CAssoc));
		CAssoc* pAssoc=(CAssoc*)newBlock->Data();
		pAssoc+=m_nBlockSize-1;
		for(LONG i=m_nBlockSize-1; i>=0; i--)
		{	pAssoc->m_pKeyNext=m_pFreeList;
			pAssoc->m_pValueNext=NULL;
			pAssoc->m_pLinkNext=NULL;
			m_pFreeList=pAssoc;
			if(i>0) pAssoc--;
		}
	}
	CLIBASSERT(m_pFreeList!=NULL);
	CAssoc* pAssoc=m_pFreeList;
	m_pFreeList=m_pFreeList->m_pKeyNext;
	m_nKeyCount++;
	CLIBASSERT(m_nKeyCount>0);
	CollConstructElements<KEY>(&pAssoc->m_Key,1);
	CollConstructElements<VALUE>(&pAssoc->m_Value,1);
	pAssoc->m_pKeyNext=NULL;
	pAssoc->m_pValueNext=NULL;
	pAssoc->m_pLinkNext=NULL;
	return pAssoc;
}

// 释放关联键
template<class KEY,class ARG_KEY,class VALUE,class ARG_VALUE>
VOID TMultiMap<KEY,ARG_KEY,VALUE,ARG_VALUE>::FreeAssoc(typename TMultiMap::CAssoc* pAssoc)
{	CollDestructElements<VALUE>(&pAssoc->m_Value,1);
	CollDestructElements<KEY>(&pAssoc->m_Key,1);
	pAssoc->m_pKeyNext=m_pFreeList;
	m_pFreeList=pAssoc;
	m_nKeyCount--;
	CLIBASSERT(m_nKeyCount>=0);
	if(m_nKeyCount==0) RemoveAll();
}

// 获取对应键值的数据
template<class KEY,class ARG_KEY,class VALUE,class ARG_VALUE>
typename TMultiMap<KEY,ARG_KEY,VALUE,ARG_VALUE>::CAssoc*
TMultiMap<KEY,ARG_KEY,VALUE,ARG_VALUE>::GetAssocAtByKey(ARG_KEY Key,UINT& nHash) CONST
{
	nHash=GenHashKey(Key,m_nKeyOffset)%m_nHashTableSize;
	if(m_pKeyHashTable==NULL) return NULL;
	CAssoc* pAssoc=NULL;
	for(pAssoc=m_pKeyHashTable[nHash]; pAssoc!=NULL; pAssoc=pAssoc->m_pKeyNext)
	{	if(CollCompareElements(&pAssoc->m_Key,&Key)) return pAssoc;
	}
	return NULL;
}

// 获取对应数值的数据
template<class KEY,class ARG_KEY,class VALUE,class ARG_VALUE>
typename TMultiMap<KEY,ARG_KEY,VALUE,ARG_VALUE>::CAssoc*
TMultiMap<KEY,ARG_KEY,VALUE,ARG_VALUE>::GetAssocAtByValue(ARG_VALUE Value,UINT& nHash) CONST
{
	nHash=GenHashKey(Value,m_nValueOffset)%m_nHashTableSize;
	if(m_pValueHashTable==NULL) return NULL;
	CAssoc* pAssoc=NULL;
	for(pAssoc=m_pValueHashTable[nHash]; pAssoc!=NULL; pAssoc=pAssoc->m_pValueNext)
	{	if(CollCompareElements(&pAssoc->m_Value,&Value)) return pAssoc;
	}
	return NULL;
}







//////////////////////////////////////////////////////////////////////////
// TArray:标准实现
//////////////////////////////////////////////////////////////////////////

template<class TYPE,class ARG_TYPE>
TArray<TYPE,ARG_TYPE>::TArray(LONG nGrowBy)
{	m_bDynamic=TRUE;
	m_pData=NULL;
	m_nSize=0;
	m_nMaxSize=0;
	m_nGrowBy=nGrowBy;
}

template<class TYPE,class ARG_TYPE>
TArray<TYPE,ARG_TYPE>::TArray(LPBYTE pStack,DWORD cbStack)
{	m_bDynamic=FALSE;
	m_pData=(TYPE*)pStack;
	m_nSize=0;
	m_nMaxSize=cbStack/size_of(TYPE);
	m_nGrowBy=0;
}

template<class TYPE,class ARG_TYPE>
TArray<TYPE,ARG_TYPE>::~TArray()
{	if(m_pData!=NULL)
	{	CollDestructElements(m_pData,m_nSize);
		if(m_bDynamic) free((BYTE*)m_pData);
	}
}

template<class TYPE,class ARG_TYPE>
VOID TArray<TYPE,ARG_TYPE>::SetSize(LONG nNewSize,LONG nGrowBy)
{
	CLIBASSERT(nNewSize>=0);
	// 重新设置块增大大小
	if(nGrowBy!=-1)
		m_nGrowBy=nGrowBy;
	// 清空数组
	if(nNewSize==0)
	{	if(m_pData!=NULL)
		{	CollDestructElements(m_pData,m_nSize);
			if(m_bDynamic)
			{	free((BYTE*)m_pData);
				m_pData=NULL;
			}
		}
		if(m_bDynamic) m_nMaxSize=0;
		m_nSize=0;
	}
	// 构造数组
	else if(m_pData==NULL)
	{
		CLIBVERIFY(m_bDynamic);
		#ifdef SIZE_T_MAX
			CLIBASSERT((UINT)max_of(m_nGrowBy,nNewSize)<=(SIZE_T_MAX/size_of(TYPE)));
		#endif
		m_pData=(TYPE*)malloc(max_of(m_nGrowBy,nNewSize)*size_of(TYPE));
		CollConstructElements<TYPE>(m_pData,nNewSize);
		m_nSize=nNewSize;
		m_nMaxSize=max_of(m_nGrowBy,nNewSize);
	}
	// 收缩数组
	else if(nNewSize<=m_nMaxSize)
	{	if(nNewSize>m_nSize)
		{	CollConstructElements(&m_pData[m_nSize],nNewSize-m_nSize);
		}
		else if(m_nSize>nNewSize)
		{	CollDestructElements(&m_pData[nNewSize],m_nSize-nNewSize);
		}
		m_nSize=nNewSize;
	}
	// 扩张数组
	else
	{	CLIBVERIFY(m_bDynamic);
		LONG nGrowBy=m_nGrowBy;
		if(nGrowBy==0)
		{	nGrowBy=m_nSize/8;
			nGrowBy=(nGrowBy<4) ? 4 : ((nGrowBy>1024) ? 1024 : nGrowBy);
		}
		LONG nNewMax;
		if(nNewSize<m_nMaxSize+nGrowBy)
				nNewMax=m_nMaxSize+nGrowBy;
		else	nNewMax=nNewSize;
		CLIBASSERT(nNewMax>=m_nMaxSize);
		#ifdef SIZE_T_MAX
			CLIBASSERT((UINT)nNewMax<=(SIZE_T_MAX/size_of(TYPE)));
		#endif
		TYPE* pNewData=(TYPE*)malloc(nNewMax*size_of(TYPE));
		#if !defined(NO_CLASS_TEMPLATE)
			CollConstructElements<TYPE>(pNewData,nNewMax);
			CollCopyElements<TYPE>(pNewData,m_pData,m_nSize);
			CollDestructElements<TYPE>(m_pData,m_nSize);
		#else
			memcpy(pNewData,m_pData,m_nSize*size_of(TYPE));
			CLIBASSERT(nNewSize>m_nSize);
			CollConstructElements<TYPE>(&pNewData[m_nSize],nNewSize-m_nSize);
		#endif
		free((BYTE*)m_pData);
		m_pData=pNewData;
		m_nSize=nNewSize;
		m_nMaxSize=nNewMax;
	}
}

template<class TYPE,class ARG_TYPE>
LONG TArray<TYPE,ARG_TYPE>::Append(CONST TArray* psrc)
{
	CLIBASSERT(this!=psrc&&psrc!=NULL);
	LONG nOldSize=m_nSize;
	SetSize(m_nSize+psrc->m_nSize);
	CollCopyElements<TYPE>(m_pData+nOldSize,psrc->m_pData,psrc->m_nSize);
	return nOldSize;
}

template<class TYPE,class ARG_TYPE>
VOID TArray<TYPE,ARG_TYPE>::Copy(CONST TArray* psrc)
{	CLIBASSERT(this!=psrc&&psrc!=NULL);
	SetSize(psrc->m_nSize);
	CollCopyElements<TYPE>(m_pData,psrc->m_pData,psrc->m_nSize);
}

template<class TYPE,class ARG_TYPE>
BOOL TArray<TYPE,ARG_TYPE>::SetSizeNoAssign(LONG nNewSize,LONG nGrowBy)
{
	CLIBASSERT(nNewSize>=0);
	// 重新设置块增大大小
	if(nGrowBy!=-1)
		m_nGrowBy=nGrowBy;
	// 清空数组
	if(nNewSize==0)
	{	if(m_pData!=NULL)
		{	CollDestructElements(m_pData,m_nSize);
			if(m_bDynamic)
			{	free((BYTE*)m_pData);
				m_pData=NULL;
			}
		}
		if(m_bDynamic) m_nMaxSize=0;
		m_nSize=0;
	}
	// 构造数组
	else if(m_pData==NULL)
	{
		CLIBVERIFY(m_bDynamic);
		#ifdef SIZE_T_MAX
			CLIBASSERT((UINT)max_of(m_nGrowBy,nNewSize)<=(SIZE_T_MAX/size_of(TYPE)));
		#endif
		m_pData=(TYPE*)malloc(max_of(m_nGrowBy,nNewSize)*size_of(TYPE));
		CollConstructElements<TYPE>(m_pData,nNewSize);
		m_nSize=nNewSize;
		m_nMaxSize=max_of(m_nGrowBy,nNewSize);
	}
	// 收缩数组
	else if(nNewSize<=m_nMaxSize)
	{	if(nNewSize>m_nSize)
		{	CollConstructElements(&m_pData[m_nSize],nNewSize-m_nSize);
		}
		else if(m_nSize>nNewSize)
		{	CollDestructElements(&m_pData[nNewSize],m_nSize-nNewSize);
		}
		m_nSize=nNewSize;
	}
	// 扩张数组,没有赋值函数,所以不支持
	else
	{	return FALSE;
	}
	return TRUE;
}

template<class TYPE,class ARG_TYPE>
BOOL TArray<TYPE,ARG_TYPE>::SetAtGrowEmptyNoAssign(LONG nIndex)
{
	CLIBASSERT(nIndex>=0);
	if(m_nSize>=m_nMaxSize&&m_nMaxSize>0) return FALSE;
	if(nIndex<m_nSize) return TRUE;
	return SetSizeNoAssign(nIndex+1,-1);
}

template<class TYPE,class ARG_TYPE>
LONG TArray<TYPE,ARG_TYPE>::AddEmptyNoAssign()
{	LONG nIndex=m_nSize;
	if(!SetAtGrowEmptyNoAssign(nIndex)) return -1;
	return nIndex;
}

template<class TYPE,class ARG_TYPE>
VOID TArray<TYPE,ARG_TYPE>::FreeExtra()
{
	if(m_nSize!=m_nMaxSize&&m_bDynamic)
	{
		#ifdef SIZE_T_MAX
			CLIBASSERT((UINT)m_nSize<=(SIZE_T_MAX/size_of(TYPE)));
		#endif
		TYPE* pNewData=NULL;
		if(m_nSize!=0)
		{
			#if !defined(NO_CLASS_TEMPLATE)
				pNewData=(TYPE*)malloc(m_nSize*size_of(TYPE));
				CollConstructElements<TYPE>(pNewData,m_nSize);
				CollCopyElements<TYPE>(pNewData,m_pData,m_nSize);
				CollDestructElements<TYPE>(m_pData,m_nSize);
			#else
				pNewData=(TYPE*)malloc(m_nSize*size_of(TYPE));
				memcpy(pNewData,m_pData,m_nSize*size_of(TYPE));
			#endif
		}
		free((BYTE*)m_pData);
		m_pData=pNewData;
		m_nMaxSize=m_nSize;
	}
}

template<class TYPE,class ARG_TYPE>
VOID TArray<TYPE,ARG_TYPE>::SetAtGrow(LONG nIndex,ARG_TYPE newElement)
{
	CLIBASSERT(nIndex>=0);
	if(nIndex>=m_nSize)
		SetSize(nIndex+1,-1);
	m_pData[nIndex]=newElement;
}

template<class TYPE,class ARG_TYPE>
VOID TArray<TYPE,ARG_TYPE>::SetAtGrowEmpty(LONG nIndex)
{
	CLIBASSERT(nIndex>=0);
	if(nIndex>=m_nSize) SetSize(nIndex+1,-1);
}


// 对象插入
template<class TYPE,class ARG_TYPE>
VOID TArray<TYPE,ARG_TYPE>::InsertAt(LONG nIndex,ARG_TYPE newElement,LONG nCount)
{	CLIBASSERT(nIndex>=0);
	CLIBASSERT(nCount>0);
	if(nIndex>=m_nSize)
	{	SetSize(nIndex+nCount,-1);
	}
	else
	{	LONG nOldSize=m_nSize;
		SetSize(m_nSize+nCount,-1);
		CollDestructElements(&m_pData[nOldSize],nCount);
		memmove(&m_pData[nIndex+nCount],&m_pData[nIndex],(nOldSize-nIndex)*size_of(TYPE));
		CollConstructElements<TYPE>(&m_pData[nIndex],nCount);
	}
	CLIBASSERT(nIndex+nCount<=m_nSize);
	while(nCount--) m_pData[nIndex++]=newElement;
}

// 对象查找
template<class TYPE,class ARG_TYPE>
LONG TArray<TYPE,ARG_TYPE>::Find(ARG_TYPE searchValue,LONG startAfter) CONST
{
	LONG nIndex=max_of(startAfter+1,0);
	for(;nIndex<m_nSize; nIndex++)
		if((*this)[nIndex]==searchValue) return nIndex;
	return -1;
}

// 数据交换函数
template<class TYPE,class ARG_TYPE>
BOOL TArray<TYPE,ARG_TYPE>::DoDataEPX(CXMLProfileSection* pPX)
{
	if(!pPX->IsStoring())
	{	TYPE* pTheNullData=(TYPE*)alloca(size_of(TYPE));
		CollConstructElements<TYPE>(pTheNullData,1);
		RemoveAll();
		CXMLProfileEnumerator ItemEnumerator(pPX->GetEnumerator(_T("ITEM"),0));
		POSITION posItemInXml=ItemEnumerator.GetPosition();
		while(posItemInXml!=NULL)
		{	Add(*pTheNullData);
			TYPE* pData=&ElementAt(GetSize()-1);
			CXMLProfileSection ItemItemSection(ItemEnumerator.GetNext(posItemInXml));
			CollDoDataEPXElements(pData,&ItemItemSection,(LPCSTR)"VALUE");
		}
		CollDestructElements(pTheNullData,1);
	}
	else
	{	CXMLProfileEnumerator ItemEnumerator(pPX->GetEnumerator(_T("ITEM"),GetSize()));
		LONG nIndex=0;
		POSITION posItemInXml=ItemEnumerator.GetPosition();
		while(nIndex<GetSize()&&posItemInXml!=NULL)
		{	TYPE* pData=&ElementAt(nIndex++);
			CXMLProfileSection ItemItemSection(ItemEnumerator.GetNext(posItemInXml));
			CollDoDataEPXElements(pData,&ItemItemSection,(LPCSTR)"VALUE");
		}
	}
	return TRUE;
}

template<class TYPE,class ARG_TYPE>
VOID TArray<TYPE,ARG_TYPE>::RemoveAt(LONG nIndex,LONG nCount)
{
	CLIBASSERT(nIndex>=0);
	CLIBASSERT(nCount>=0);
	CLIBASSERT(nIndex+nCount<=m_nSize);
	LONG nMoveCount=m_nSize-(nIndex+nCount);
	CollDestructElements(&m_pData[nIndex],nCount);
	if(nMoveCount)
		memmove(&m_pData[nIndex],&m_pData[nIndex+nCount],nMoveCount*size_of(TYPE));
	m_nSize-=nCount;
}

template<class TYPE,class ARG_TYPE>
VOID TArray<TYPE,ARG_TYPE>::InsertAt(LONG nStartIndex,TArray* pNewArray)
{
	CLIBASSERT(pNewArray!=NULL);
	CLIBASSERT(nStartIndex>=0);
	if(pNewArray->GetSize()>0)
	{	InsertAt(nStartIndex,pNewArray->GetAt(0),pNewArray->GetSize());
		for(LONG i=0; i<pNewArray->GetSize(); i++)
			SetAt(nStartIndex+i,pNewArray->GetAt(i));
	}
}




//////////////////////////////////////////////////////////////////////////
// TArray:内联实现
//////////////////////////////////////////////////////////////////////////

template<class TYPE,class ARG_TYPE>
CLIB_INLINE LONG TArray<TYPE,ARG_TYPE>::GetSize() CONST
	{ return m_nSize; }
template<class TYPE,class ARG_TYPE>
CLIB_INLINE LONG TArray<TYPE,ARG_TYPE>::GetMaxSize() CONST
	{ return m_nMaxSize; }
template<class TYPE,class ARG_TYPE>
CLIB_INLINE LONG TArray<TYPE,ARG_TYPE>::GetUpperBound() CONST
	{ return m_nSize-1; }
template<class TYPE,class ARG_TYPE>
CLIB_INLINE void TArray<TYPE,ARG_TYPE>::RemoveAll()
	{ SetSize(0,-1); }
template<class TYPE,class ARG_TYPE>
CLIB_INLINE TYPE TArray<TYPE,ARG_TYPE>::GetAt(LONG nIndex) CONST
	{	CLIBASSERT(nIndex>=0 && nIndex<m_nSize);
		return m_pData[nIndex];
	}
template<class TYPE,class ARG_TYPE>
CLIB_INLINE void TArray<TYPE,ARG_TYPE>::SetAt(LONG nIndex,ARG_TYPE newElement)
	{	CLIBASSERT(nIndex>=0 && nIndex<m_nSize);
		m_pData[nIndex]=newElement;
	}
template<class TYPE,class ARG_TYPE>
CLIB_INLINE TYPE& TArray<TYPE,ARG_TYPE>::ElementAt(LONG nIndex)
	{	CLIBASSERT(nIndex>=0 && nIndex<m_nSize);
		return m_pData[nIndex];
	}
template<class TYPE,class ARG_TYPE>
CLIB_INLINE CONST TYPE* TArray<TYPE,ARG_TYPE>::GetData() CONST
	{ return (m_nSize>0)?((CONST TYPE*)m_pData):NULL; }
template<class TYPE,class ARG_TYPE>
CLIB_INLINE TYPE* TArray<TYPE,ARG_TYPE>::GetData()
	{ return (TYPE*)m_pData; }
template<class TYPE,class ARG_TYPE>
CLIB_INLINE LONG TArray<TYPE,ARG_TYPE>::Add(ARG_TYPE newElement)
	{ LONG nIndex=m_nSize; SetAtGrow(nIndex,newElement); return nIndex; }
template<class TYPE,class ARG_TYPE>
CLIB_INLINE LONG TArray<TYPE,ARG_TYPE>::AddEmpty()
	{ LONG nIndex=m_nSize; SetAtGrowEmpty(nIndex); return nIndex; }
template<class TYPE,class ARG_TYPE>
CLIB_INLINE TYPE TArray<TYPE,ARG_TYPE>::operator[](LONG nIndex) CONST
	{ return GetAt(nIndex); }
template<class TYPE,class ARG_TYPE>
CLIB_INLINE TYPE& TArray<TYPE,ARG_TYPE>::operator[](LONG nIndex)
	{ return ElementAt(nIndex); }












//////////////////////////////////////////////////////////////////////////
// TList:标准实现
//////////////////////////////////////////////////////////////////////////

template<class TYPE,class ARG_TYPE>
TList<TYPE,ARG_TYPE>::TList(LONG nBlockSize)
{
	CLIBASSERT(nBlockSize>0);
	m_nCount=0;
	m_pNodeHead=m_pNodeTail=m_pNodeFree=NULL;
	m_pBlocks=NULL;
	m_nBlockSize=nBlockSize;
}

template<class TYPE,class ARG_TYPE>
VOID TList<TYPE,ARG_TYPE>::RemoveAll()
{
	CNode* pNode;
	for(pNode=m_pNodeHead; pNode!=NULL; pNode=pNode->pNext)
		CollDestructElements(&pNode->data,1);
	m_nCount=0;
	m_pNodeHead=m_pNodeTail=m_pNodeFree=NULL;
	m_pBlocks->FreeDataChain();
	m_pBlocks=NULL;
}

template<class TYPE,class ARG_TYPE>
TList<TYPE,ARG_TYPE>::~TList()
{
	RemoveAll();
	CLIBASSERT(m_nCount==0);
}

template<class TYPE,class ARG_TYPE>
typename TList<TYPE,ARG_TYPE>::CNode*
TList<TYPE,ARG_TYPE>::NewNode(typename TList::CNode* pPrev,typename TList::CNode* pNext)
{
	// 块空,添加新块并完成链接
	if(m_pNodeFree==NULL)
	{	TBucket* pNewBlock=TBucket::Create(m_pBlocks,m_nBlockSize,size_of(CNode));
		CNode* pNode=(CNode*)pNewBlock->Data();
		pNode += m_nBlockSize-1;
		for(LONG i=m_nBlockSize-1; i>=0; i--)
		{	pNode->pNext=m_pNodeFree;
			m_pNodeFree=pNode;
			if(i>0) pNode--;
		}
	}
	// 从链接对象中分配一个可用单元
	CLIBASSERT(m_pNodeFree!=NULL);
	CNode* pNode=m_pNodeFree;
	m_pNodeFree=m_pNodeFree->pNext;
	pNode->pPrev=pPrev;
	pNode->pNext=pNext;
	m_nCount++;

	CLIBASSERT(m_nCount>0);
	CollConstructElements<TYPE>(&pNode->data,1);
	return pNode;
}


template<class TYPE,class ARG_TYPE>
VOID TList<TYPE,ARG_TYPE>::FreeNode(typename TList::CNode* pNode)
{	CLIBASSERT(m_nCount>0);
	CollDestructElements(&pNode->data,1);
	pNode->pNext=m_pNodeFree;
	m_pNodeFree=pNode;
	m_nCount--;
	if(m_nCount==0) RemoveAll();
}

template<class TYPE,class ARG_TYPE>
POSITION TList<TYPE,ARG_TYPE>::AddHeadConst(CONST TYPE& newElement)
{	CNode* pNewNode=NewNode(NULL,m_pNodeHead);
	pNewNode->data=newElement;
	if(m_pNodeHead!=NULL)
			m_pNodeHead->pPrev=pNewNode;
	else	m_pNodeTail=pNewNode;
	m_pNodeHead=pNewNode;
	return (POSITION) pNewNode;
}

template<class TYPE,class ARG_TYPE>
POSITION TList<TYPE,ARG_TYPE>::AddTailConst(CONST TYPE& newElement)
{	CNode* pNewNode=NewNode(m_pNodeTail,NULL);
	pNewNode->data=newElement;
	if(m_pNodeTail!=NULL)
			m_pNodeTail->pNext=pNewNode;
	else	m_pNodeHead=pNewNode;
	m_pNodeTail=pNewNode;
	return (POSITION)pNewNode;
}

template<class TYPE,class ARG_TYPE>
POSITION TList<TYPE,ARG_TYPE>::AddHead(ARG_TYPE newElement)
{	CNode* pNewNode=NewNode(NULL,m_pNodeHead);
	pNewNode->data=newElement;
	if(m_pNodeHead!=NULL)
			m_pNodeHead->pPrev=pNewNode;
	else	m_pNodeTail=pNewNode;
	m_pNodeHead=pNewNode;
	return (POSITION) pNewNode;
}

template<class TYPE,class ARG_TYPE>
POSITION TList<TYPE,ARG_TYPE>::AddTail(ARG_TYPE newElement)
{	CNode* pNewNode=NewNode(m_pNodeTail,NULL);
	pNewNode->data=newElement;
	if(m_pNodeTail!=NULL)
			m_pNodeTail->pNext=pNewNode;
	else	m_pNodeHead=pNewNode;
	m_pNodeTail=pNewNode;
	return (POSITION)pNewNode;
}

template<class TYPE,class ARG_TYPE>
POSITION TList<TYPE,ARG_TYPE>::AddEmptyToHead()
{	CNode* pNewNode=NewNode(NULL,m_pNodeHead);
	if(m_pNodeHead!=NULL)
			m_pNodeHead->pPrev=pNewNode;
	else	m_pNodeTail=pNewNode;
	m_pNodeHead=pNewNode;
	return (POSITION) pNewNode;
}

template<class TYPE,class ARG_TYPE>
POSITION TList<TYPE,ARG_TYPE>::AddEmptyToTail()
{	CNode* pNewNode=NewNode(m_pNodeTail,NULL);
	if(m_pNodeTail!=NULL)
			m_pNodeTail->pNext=pNewNode;
	else	m_pNodeHead=pNewNode;
	m_pNodeTail=pNewNode;
	return (POSITION)pNewNode;
}

template<class TYPE,class ARG_TYPE>
VOID TList<TYPE,ARG_TYPE>::AppendHead(CONST TList* pNewList)
{	CLIBASSERT(pNewList!=NULL);
	POSITION pos=pNewList->GetTailPosition();
	while(pos!=NULL)
		AddHeadConst(pNewList->GetPrev(pos));
}

template<class TYPE,class ARG_TYPE>
VOID TList<TYPE,ARG_TYPE>::AppendTail(CONST TList* pNewList)
{
	CLIBASSERT(pNewList!=NULL);
	POSITION pos=pNewList->GetHeadPosition();
	while(pos!=NULL)
		AddTailConst(pNewList->GetNext(pos));
}

template<class TYPE,class ARG_TYPE>
TYPE TList<TYPE,ARG_TYPE>::RemoveHead()
{
	CLIBASSERT(m_pNodeHead!=NULL);
	CLIBASSERT(clibIsValidAddress(m_pNodeHead,size_of(CNode)));
	CNode* pOldNode=m_pNodeHead;
	TYPE returnValue=pOldNode->data;
	m_pNodeHead=pOldNode->pNext;
	if(m_pNodeHead!=NULL)
			m_pNodeHead->pPrev=NULL;
	else	m_pNodeTail=NULL;
	FreeNode(pOldNode);
	return returnValue;
}

template<class TYPE,class ARG_TYPE>
TYPE TList<TYPE,ARG_TYPE>::RemoveTail()
{
	CLIBASSERT(m_pNodeTail!=NULL);
	CLIBASSERT(clibIsValidAddress(m_pNodeTail,size_of(CNode)));
	CNode* pOldNode=m_pNodeTail;
	TYPE returnValue=pOldNode->data;
	m_pNodeTail=pOldNode->pPrev;
	if(m_pNodeTail!=NULL)
			m_pNodeTail->pNext=NULL;
	else	m_pNodeHead=NULL;
	FreeNode(pOldNode);
	return returnValue;
}

template<class TYPE,class ARG_TYPE>
POSITION TList<TYPE,ARG_TYPE>::InsertBefore(POSITION position,ARG_TYPE newElement)
{
	if(position==NULL)
		return AddHead(newElement);
	CNode* pOldNode=(CNode*) position;
	CNode* pNewNode=NewNode(pOldNode->pPrev,pOldNode);
	pNewNode->data=newElement;

	if(pOldNode->pPrev!=NULL)
	{	CLIBASSERT(clibIsValidAddress(pOldNode->pPrev,size_of(CNode)));
		pOldNode->pPrev->pNext=pNewNode;
	}
	else
	{	CLIBASSERT(pOldNode==m_pNodeHead);
		m_pNodeHead=pNewNode;
	}
	pOldNode->pPrev=pNewNode;
	return (POSITION) pNewNode;
}

template<class TYPE,class ARG_TYPE>
POSITION TList<TYPE,ARG_TYPE>::InsertAfter(POSITION position,ARG_TYPE newElement)
{
	if(position==NULL)
		return AddTail(newElement);
	CNode* pOldNode=(CNode*) position;
	CLIBASSERT(clibIsValidAddress(pOldNode,size_of(CNode)));
	CNode* pNewNode=NewNode(pOldNode,pOldNode->pNext);
	pNewNode->data=newElement;
	if(pOldNode->pNext!=NULL)
	{	CLIBASSERT(clibIsValidAddress(pOldNode->pNext,size_of(CNode)));
		pOldNode->pNext->pPrev=pNewNode;
	}
	else
	{	CLIBASSERT(pOldNode==m_pNodeTail);
		m_pNodeTail=pNewNode;
	}
	pOldNode->pNext=pNewNode;
	return (POSITION)pNewNode;
}

template<class TYPE,class ARG_TYPE>
VOID TList<TYPE,ARG_TYPE>::RemoveAt(POSITION position)
{	CNode* pOldNode=(CNode*) position;
	CLIBASSERT(clibIsValidAddress(pOldNode,size_of(CNode)));
	if(pOldNode==m_pNodeHead)
	{	m_pNodeHead=pOldNode->pNext;
	}
	else
	{	CLIBASSERT(clibIsValidAddress(pOldNode->pPrev,size_of(CNode)));
		pOldNode->pPrev->pNext=pOldNode->pNext;
	}
	if(pOldNode==m_pNodeTail)
	{	m_pNodeTail=pOldNode->pPrev;
	}
	else
	{	CLIBASSERT(clibIsValidAddress(pOldNode->pNext,size_of(CNode)));
		pOldNode->pNext->pPrev=pOldNode->pPrev;
	}
	FreeNode(pOldNode);
}

template<class TYPE,class ARG_TYPE>
VOID TList<TYPE,ARG_TYPE>::RemoveByPtr(TYPE* pData)
{
	if(pData==NULL) return;
	CNode* pNode=(CNode*)((LPBYTE)((LPVOID)pData)-ex_offset_of(CNode,data));
	RemoveAt((POSITION)pNode);
}

// 数据交换函数
template<class TYPE,class ARG_TYPE>
BOOL TList<TYPE,ARG_TYPE>::DoDataEPX(CXMLProfileSection* pPX)
{
	if(!pPX->IsStoring())
	{	TYPE* pTheNullData=(TYPE*)alloca(size_of(TYPE));
		CollConstructElements<TYPE>(pTheNullData,1);
		RemoveAll();
		CXMLProfileEnumerator ItemEnumerator(pPX->GetEnumerator(_T("ITEM"),0));
		POSITION posItemInXml=ItemEnumerator.GetPosition();
		while(posItemInXml!=NULL)
		{	AddTail(*pTheNullData);
			TYPE* pData=&GetTail();
			CXMLProfileSection ItemItemSection(ItemEnumerator.GetNext(posItemInXml));
			CollDoDataEPXElements(pData,&ItemItemSection,(LPCSTR)"VALUE");
		}
		CollDestructElements(pTheNullData,1);
	}
	else
	{	CXMLProfileEnumerator ItemEnumerator(pPX->GetEnumerator(_T("ITEM"),GetCount()));
		POSITION posItemInList=GetHeadPosition();
		POSITION posItemInXml=ItemEnumerator.GetPosition();
		while(posItemInList!=NULL&&posItemInXml!=NULL)
		{	TYPE* pData=&GetNext(posItemInList);
			CXMLProfileSection ItemItemSection(ItemEnumerator.GetNext(posItemInXml));
			CollDoDataEPXElements(pData,&ItemItemSection,(LPCSTR)"VALUE");
		}
	}
	return TRUE;
}

template<class TYPE,class ARG_TYPE>
POSITION TList<TYPE,ARG_TYPE>::FindIndex(LONG nIndex) CONST
{	if(nIndex>=m_nCount || nIndex<0)
		return NULL;
	CNode* pNode=m_pNodeHead;
	while(nIndex--)
	{	CLIBASSERT(clibIsValidAddress(pNode,size_of(CNode)));
		pNode=pNode->pNext;
	}
	return (POSITION)pNode;
}

template<class TYPE,class ARG_TYPE>
CLIB_INLINE TYPE& TList<TYPE,ARG_TYPE>::GetAtIndex(LONG nIndex)
{	POSITION posNode=FindIndex(nIndex);
	return GetAt(posNode);
}

template<class TYPE,class ARG_TYPE>
CLIB_INLINE TYPE TList<TYPE,ARG_TYPE>::GetAtIndex(LONG nIndex) CONST
{	POSITION posNode=FindIndex(nIndex);
	return GetAt(posNode);
}


template<class TYPE,class ARG_TYPE>
CLIB_INLINE POSITION TList<TYPE,ARG_TYPE>::Find(ARG_TYPE searchValue,POSITION startAfter) CONST
{	CNode* pNode=(CNode*) startAfter;
	if(pNode==NULL)
	{	pNode=m_pNodeHead;
	}
	else
	{	CLIBASSERT(clibIsValidAddress(pNode,size_of(CNode)));
		pNode=pNode->pNext;
	}
	for(; pNode!=NULL; pNode=pNode->pNext)
		if(CollCompareElements<TYPE>(&pNode->data,&searchValue))
			return (POSITION)pNode;
	return NULL;
}





//////////////////////////////////////////////////////////////////////////
// TList:内联实现
//////////////////////////////////////////////////////////////////////////

template<class TYPE,class ARG_TYPE>
CLIB_INLINE LONG TList<TYPE,ARG_TYPE>::GetCount() CONST
	{ return m_nCount; }
template<class TYPE,class ARG_TYPE>
CLIB_INLINE BOOL TList<TYPE,ARG_TYPE>::IsEmpty() CONST
	{ return m_nCount==0; }
template<class TYPE,class ARG_TYPE>
CLIB_INLINE TYPE& TList<TYPE,ARG_TYPE>::GetHead()
	{	CLIBASSERT(m_pNodeHead!=NULL);
		return m_pNodeHead->data;
	}
template<class TYPE,class ARG_TYPE>
CLIB_INLINE TYPE TList<TYPE,ARG_TYPE>::GetHead() CONST
	{	CLIBASSERT(m_pNodeHead!=NULL);
		return m_pNodeHead->data;
	}
template<class TYPE,class ARG_TYPE>
CLIB_INLINE TYPE& TList<TYPE,ARG_TYPE>::GetTail()
	{	CLIBASSERT(m_pNodeTail!=NULL);
		return m_pNodeTail->data;
	}
template<class TYPE,class ARG_TYPE>
CLIB_INLINE TYPE TList<TYPE,ARG_TYPE>::GetTail() CONST
	{	CLIBASSERT(m_pNodeTail!=NULL);
		return m_pNodeTail->data;
	}
template<class TYPE,class ARG_TYPE>
CLIB_INLINE POSITION TList<TYPE,ARG_TYPE>::GetHeadPosition() CONST
	{ return (POSITION) m_pNodeHead; }
template<class TYPE,class ARG_TYPE>
CLIB_INLINE POSITION TList<TYPE,ARG_TYPE>::GetTailPosition() CONST
	{ return (POSITION) m_pNodeTail; }
template<class TYPE,class ARG_TYPE>
CLIB_INLINE TYPE& TList<TYPE,ARG_TYPE>::GetNext(POSITION& rPosition)
	{	CNode* pNode=(CNode*) rPosition;
		CLIBASSERT(clibIsValidAddress(pNode,size_of(CNode)));
		rPosition=(POSITION) pNode->pNext;
		return pNode->data;
	}
template<class TYPE,class ARG_TYPE>
CLIB_INLINE TYPE TList<TYPE,ARG_TYPE>::GetNext(POSITION& rPosition) CONST
	{	CNode* pNode=(CNode*) rPosition;
		CLIBASSERT(clibIsValidAddress(pNode,size_of(CNode)));
		rPosition=(POSITION) pNode->pNext;
		return pNode->data;
	}
template<class TYPE,class ARG_TYPE>
CLIB_INLINE TYPE& TList<TYPE,ARG_TYPE>::GetPrev(POSITION& rPosition)
	{	CNode* pNode=(CNode*) rPosition;
		CLIBASSERT(clibIsValidAddress(pNode,size_of(CNode)));
		rPosition=(POSITION) pNode->pPrev;
		return pNode->data;
	}
template<class TYPE,class ARG_TYPE>
CLIB_INLINE TYPE TList<TYPE,ARG_TYPE>::GetPrev(POSITION& rPosition) CONST
	{	CNode* pNode=(CNode*) rPosition;
		CLIBASSERT(clibIsValidAddress(pNode,size_of(CNode)));
		rPosition=(POSITION) pNode->pPrev;
		return pNode->data;
	}
template<class TYPE,class ARG_TYPE>
CLIB_INLINE TYPE& TList<TYPE,ARG_TYPE>::GetAt(POSITION position)
	{	CLIBASSERT(position!=NULL);
		CNode* pNode=(CNode*) position;
		CLIBASSERT(clibIsValidAddress(pNode,size_of(CNode)));
		return pNode->data;
	}
template<class TYPE,class ARG_TYPE>
CLIB_INLINE TYPE TList<TYPE,ARG_TYPE>::GetAt(POSITION position) CONST
	{	CLIBASSERT(position!=NULL);
		CNode* pNode=(CNode*) position;
		CLIBASSERT(clibIsValidAddress(pNode,size_of(CNode)));
		return pNode->data;
	}
template<class TYPE,class ARG_TYPE>
CLIB_INLINE VOID TList<TYPE,ARG_TYPE>::SetAt(POSITION pos,ARG_TYPE newElement)
	{	CNode* pNode=(CNode*) pos;
		CLIBASSERT(clibIsValidAddress(pNode,size_of(CNode)));
		pNode->data=newElement;
	}
template<class TYPE,class ARG_TYPE>
CLIB_INLINE POSITION TList<TYPE,ARG_TYPE>::PositionOf(TYPE* pData)
	{	CNode* pNode=(CNode*)((LPBYTE)((LPVOID)pData)-ex_offset_of(CNode,data));
		return (POSITION)pNode;
	}


//////////////////////////////////////////////////////////////////////////
// TOrdinalList:标准实现
//////////////////////////////////////////////////////////////////////////
template<class KEY,class ARG_KEY>
TOrdinalList<KEY,ARG_KEY>::TOrdinalList(LONG nBlockSize)
{	UNREFERENCED_PARAMETER(nBlockSize);
}

template<class KEY,class ARG_KEY>
TOrdinalList<KEY,ARG_KEY>::~TOrdinalList()
{
}



//////////////////////////////////////////////////////////////////////////
// THashList:标准实现
//////////////////////////////////////////////////////////////////////////
template<class KEY,class ARG_KEY>
THashList<KEY,ARG_KEY>::THashList(LONG nBlockSize,UINT nKeyOffset)
{	CLIBASSERT(nBlockSize>0);
	m_pHashTable=NULL;
	m_nHashTableSize=17;
	m_nKeyOffset=nKeyOffset;
	m_nCount=0;
	m_pFreeList=NULL;
	m_pBlocks=NULL;
	m_nBlockSize=nBlockSize;
}

template<class KEY,class ARG_KEY>
THashList<KEY,ARG_KEY>::~THashList()
{	RemoveAll();
	CLIBASSERT(m_nCount==0);
}

// 查找键值,如果不存在,则返回错误
template<class KEY,class ARG_KEY>
BOOL THashList<KEY,ARG_KEY>::Lookup(ARG_KEY Key) CONST
{
	UINT nHash=0;
	CAssoc* pAssoc=GetAssocAt(Key,nHash);
	if(pAssoc==NULL) return FALSE;
	return TRUE;
}

// 键值的查找,返回是否存在标志
template<class KEY,class ARG_KEY>
BOOL THashList<KEY,ARG_KEY>::operator[](ARG_KEY Key) CONST
{
	UINT nHash=0;
	CAssoc* pAssoc=GetAssocAt(Key,nHash);
	if(pAssoc==NULL) return FALSE;
	return TRUE;
}

template<class KEY,class ARG_KEY>
VOID THashList<KEY,ARG_KEY>::InsertKey(ARG_KEY Key)
{
	UINT nHash;
	CAssoc* pAssoc=NULL;
	if((pAssoc=GetAssocAt(Key,nHash))==NULL)
	{	if(m_pHashTable==NULL) InitHashTable(m_nHashTableSize);
		pAssoc=NewAssoc();
		pAssoc->m_Key=Key;
		pAssoc->m_pNext=m_pHashTable[nHash];
		m_pHashTable[nHash]=pAssoc;
	}
}

// 删除键值
template<class KEY,class ARG_KEY>
BOOL THashList<KEY,ARG_KEY>::RemoveKey(ARG_KEY Key)
{
	if(m_pHashTable==NULL) return FALSE;
	CAssoc** ppAssocPrev;
	ppAssocPrev=&m_pHashTable[GenHashKey(Key,m_nKeyOffset)%m_nHashTableSize];
	CAssoc* pAssoc=NULL;
	for(pAssoc=*ppAssocPrev; pAssoc!=NULL; pAssoc=pAssoc->m_pNext)
	{	if(CollCompareElements(&pAssoc->m_Key,&Key))
		{	*ppAssocPrev=pAssoc->m_pNext;
			FreeAssoc(pAssoc);
			return TRUE;
		}
		ppAssocPrev=&pAssoc->m_pNext;
	}
	return FALSE;
}

// 删除全部键值
template<class KEY,class ARG_KEY>
VOID THashList<KEY,ARG_KEY>::RemoveAll()
{
	if(m_pHashTable!=NULL)
	{	free(m_pHashTable);
		m_pHashTable=NULL;
	}
	m_nCount=0;
	m_pFreeList=NULL;
	m_pBlocks->FreeDataChain();
	m_pBlocks=NULL;
}

// 数据交换函数
template<class KEY,class ARG_KEY>
BOOL THashList<KEY,ARG_KEY>::DoDataEPX(CXMLProfileSection* pPX)
{
	KEY* pTheType=(KEY*)alloca(size_of(KEY));
	CollConstructElements<KEY>(pTheType,1);
	if(!pPX->IsStoring())
	{	RemoveAll();
		CXMLProfileEnumerator ItemEnumerator(pPX->GetEnumerator(_T("ITEM"),0));
		POSITION posItemInXml=ItemEnumerator.GetPosition();
		while(posItemInXml!=NULL)
		{	CXMLProfileSection ItemItemSection(ItemEnumerator.GetNext(posItemInXml));
			CollDoDataEPXElements<KEY>(pTheType,&ItemItemSection,(LPCSTR)"KEY");
			InsertKey(*pTheType);
		}
	}
	else
	{	CXMLProfileEnumerator ItemEnumerator(pPX->GetEnumerator(_T("ITEM"),GetCount()));
		POSITION posItemInMap=GetStartPosition();
		POSITION posItemInXml=ItemEnumerator.GetPosition();
		while(posItemInMap!=NULL&&posItemInXml!=NULL)
		{	GetNextAssoc(posItemInMap,*pTheType);
			CXMLProfileSection ItemItemSection(ItemEnumerator.GetNext(posItemInXml));
			CollDoDataEPXElements<KEY>(pTheType,&ItemItemSection,(LPCSTR)"KEY");
		}
	}
	CollDestructElements<KEY>(pTheType,1);
	return TRUE;
}

// 获取下一个字段
template<class KEY,class ARG_KEY>
VOID THashList<KEY,ARG_KEY>::GetNextAssoc(POSITION& rNextPosition,KEY& rKey) CONST
{
	// 查找到当前位置
	CLIBASSERT(m_pHashTable!=NULL);
	CAssoc* pAssocRet=(CAssoc*)rNextPosition;
	CLIBASSERT(pAssocRet!=NULL);
	if(pAssocRet==(CAssoc*)BEFORE_START_POSITION)
	{	for(UINT nBucket=0; nBucket<m_nHashTableSize; nBucket++)
			if((pAssocRet=m_pHashTable[nBucket])!=NULL)
				break;
		CLIBASSERT(pAssocRet!=NULL);
	}

	// 继续查找下一个位置
	CLIBASSERT(clibIsValidAddress(pAssocRet,size_of(CAssoc)));
	CAssoc* pAssocNext=NULL;
	if((pAssocNext=pAssocRet->m_pNext)==NULL)
	{	for(UINT nBucket=(GenHashKey(pAssocRet->m_Key,m_nKeyOffset)%m_nHashTableSize)+1; nBucket<m_nHashTableSize; nBucket++)
			if((pAssocNext=m_pHashTable[nBucket])!=NULL)
				break;
	}
	rNextPosition=(POSITION)pAssocNext;
	rKey=pAssocRet->m_Key;
}

// 初始化HASH表
template<class KEY,class ARG_KEY>
VOID THashList<KEY,ARG_KEY>::InitHashTable(UINT nHashSize,BOOL bAllocNow)
{
	CLIBASSERT(m_nCount==0);
	CLIBASSERT(nHashSize>0);
	if(m_pHashTable!=NULL)
	{	free(m_pHashTable);
		m_pHashTable=NULL;
	}
	if(bAllocNow)
	{	m_pHashTable=(CAssoc**)malloc(size_of(CAssoc*)*nHashSize);
		memset(m_pHashTable,0,size_of(CAssoc*)*nHashSize);
	}
	m_nHashTableSize=nHashSize;
}

// 获取下一个字段
template<class KEY,class ARG_KEY>
typename THashList<KEY,ARG_KEY>::CAssoc*
THashList<KEY,ARG_KEY>::NewAssoc()
{
	if(m_pFreeList==NULL)
	{	TBucket* newBlock=TBucket::Create(m_pBlocks,m_nBlockSize,size_of(CAssoc));
		CAssoc* pAssoc=(CAssoc*)newBlock->Data();
		pAssoc+=m_nBlockSize-1;
		for(LONG i=m_nBlockSize-1; i>=0; i--)
		{	pAssoc->m_pNext=m_pFreeList;
			m_pFreeList=pAssoc;
			if(i>0) pAssoc--;
		}
	}
	CLIBASSERT(m_pFreeList!=NULL);
	CAssoc* pAssoc=m_pFreeList;
	m_pFreeList=m_pFreeList->m_pNext;
	m_nCount++;
	CLIBASSERT(m_nCount>0);
	CollConstructElements<KEY>(&pAssoc->m_Key,1);
	return pAssoc;
}

// 释放关联键
template<class KEY,class ARG_KEY>
VOID THashList<KEY,ARG_KEY>::FreeAssoc(typename THashList::CAssoc* pAssoc)
{	CLIBASSERT(m_nCount>0);
	CollDestructElements<KEY>(&pAssoc->m_Key,1);
	pAssoc->m_pNext=m_pFreeList;
	m_pFreeList=pAssoc;
	m_nCount--;
	if(m_nCount==0) RemoveAll();
}

// 获取对应键值的数据
template<class KEY,class ARG_KEY>
typename THashList<KEY,ARG_KEY>::CAssoc*
THashList<KEY,ARG_KEY>::GetAssocAt(ARG_KEY Key,UINT& nHash) CONST
{
	nHash=GenHashKey(Key,m_nKeyOffset)%m_nHashTableSize;
	if(m_pHashTable==NULL) return NULL;
	CAssoc* pAssoc=NULL;
	for(pAssoc=m_pHashTable[nHash]; pAssoc!=NULL; pAssoc=pAssoc->m_pNext)
	{	if(CollCompareElements(&pAssoc->m_Key,&Key)) return pAssoc;
	}
	return NULL;
}



//////////////////////////////////////////////////////////////////////////
// THashList内联实现
//////////////////////////////////////////////////////////////////////////
template<class KEY,class ARG_KEY>
CLIB_INLINE LONG THashList<KEY,ARG_KEY>::GetCount() CONST
	{ return m_nCount; }

template<class KEY,class ARG_KEY>
CLIB_INLINE BOOL THashList<KEY,ARG_KEY>::IsEmpty() CONST
	{ return m_nCount==0; }

template<class KEY,class ARG_KEY>
CLIB_INLINE POSITION THashList<KEY,ARG_KEY>::GetStartPosition() CONST
	{ return (m_nCount==0)?NULL:BEFORE_START_POSITION; }

template<class KEY,class ARG_KEY>
CLIB_INLINE UINT THashList<KEY,ARG_KEY>::GetHashTableSize() CONST
	{ return m_nHashTableSize; }





#endif
