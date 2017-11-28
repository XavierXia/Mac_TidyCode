#ifndef __MEM_TABLE__INL__
#define __MEM_TABLE__INL__

#ifndef __MEM_TABLE__H__
	#error memtable.h must be included
#endif


// ��¼����ص�(��������)
template<class KEY,class RECORD,int SUBINDEXNUM>
CLIB_INLINE BOOL TIndex<KEY,RECORD,SUBINDEXNUM>::OnInsertRecord(LPVOID pRecordVoid)
{	RECORD* pRecord=(RECORD*)pRecordVoid;
	KEY aKeys[SUBINDEXNUM];
	memset(aKeys,0,size_of(aKeys));
	DWORD dwKeyNum=RecordToKeys(*pRecord,(KEY*)aKeys,ARRAYSIZE(aKeys));
	BOOL bRollback=FALSE;
	DWORD dwKey=0;
	for(dwKey=0; dwKey<dwKeyNum; dwKey++)
	{	if(!InsertIndex(aKeys[dwKey],pRecord))
		{	bRollback=TRUE;
			break;
		}
	}
	// ����������ݻ���,�����Ѿ����������������ش���
	if(bRollback)
	{	while(dwKey>0)
		{	dwKey--;
			DeleteIndex(aKeys[dwKey],pRecord);
		}
		return FALSE;
	}
	return TRUE;
}

// ��¼ɾ���ص�(��������)
template<class KEY,class RECORD,int SUBINDEXNUM>
CLIB_INLINE VOID TIndex<KEY,RECORD,SUBINDEXNUM>::OnDeleteRecord(LPVOID pRecordVoid)
{	RECORD* pRecord=(RECORD*)pRecordVoid;
	KEY aKeys[SUBINDEXNUM];
	memset(aKeys,0,size_of(aKeys));
	DWORD dwKeyNum=RecordToKeys(*pRecord,(KEY*)aKeys,ARRAYSIZE(aKeys));
	for(DWORD dwKey=0; dwKey<dwKeyNum; dwKey++) DeleteIndex(aKeys[dwKey],pRecord);
}

// ��¼�����ӹ���(ͨ���б�)
template<class KEY,class RECORD,int SUBINDEXNUM>
CLIB_INLINE VOID TIndex<KEY,RECORD,SUBINDEXNUM>::OnSelectUsingIndex(LONG nTop,LPVOID pKeyVoid,LPVOID plstResultsVoid)
{
	KEY* pKey=(KEY*)pKeyVoid;
	TList<RECORD*,RECORD*&>* plstResults=(TList<RECORD*,RECORD*&>*)plstResultsVoid;
	plstResults->RemoveAll();

	// ���ҵ�ǰ����Ӧ�ļ�¼ָ������,����������򷵻�
	LPVOID pChainVoid=NULL;
	if(!m_ChainMap.Lookup(*pKey,pChainVoid)) pChainVoid=NULL;
	if(pChainVoid==NULL) return;

	// ������ѭ������
	POSITION posChain=(POSITION)pChainVoid;
	while(posChain!=NULL)
	{	CHAIN* pChain=&m_ChainList.GetAt(posChain);
		posChain=pChain->m_posNext;
		if(pChain->m_pRecord==NULL) continue;
		plstResults->AddTail(pChain->m_pRecord);
		if(nTop>0&&plstResults->GetCount()>=nTop) break;
	}
}

// ��¼�����ӹ���(����ģʽ)
template<class KEY,class RECORD,int SUBINDEXNUM>
CLIB_INLINE DWORD TIndex<KEY,RECORD,SUBINDEXNUM>::OnSelectUsingIndexEx(DWORD dwMax,LONG nTop,LPVOID pKeyVoid,LPVOID* ppResults)
{
	KEY* pKey=(KEY*)pKeyVoid;
	
	// ���ҵ�ǰ����Ӧ�ļ�¼ָ������,����������򷵻�
	LPVOID pChainVoid=NULL;
	if(!m_ChainMap.Lookup(*pKey,pChainVoid)) pChainVoid=NULL;
	if(pChainVoid==NULL) return 0;

	// ������ѭ������
	DWORD dwSelected=0;
	POSITION posChain=(POSITION)pChainVoid;
	while(posChain!=NULL)
	{	CHAIN* pChain=&m_ChainList.GetAt(posChain);
		posChain=pChain->m_posNext;
		if(pChain->m_pRecord==NULL) continue;
		if(dwSelected>=dwMax) break;
		ppResults[dwSelected]=pChain->m_pRecord;
		dwSelected++;
		if(nTop>0&&dwSelected>=(DWORD)nTop) break;
		if(dwSelected>=dwMax) break;
	}
	return dwSelected;
}

// ����ɾ��
template<class KEY,class RECORD,int SUBINDEXNUM>
CLIB_INLINE VOID TIndex<KEY,RECORD,SUBINDEXNUM>::DeleteRender()
{	delete this;
}

// ��������
template<class KEY,class RECORD,int SUBINDEXNUM>
CLIB_INLINE BOOL TIndex<KEY,RECORD,SUBINDEXNUM>::InsertIndex(const KEY& Key,RECORD* pRecord)
{
	// ���ҵ�ǰ����Ӧ�ļ�¼ָ������
	LPVOID pChainVoid=NULL;
	if(!m_ChainMap.Lookup(Key,pChainVoid)) pChainVoid=NULL;

	// ���Ψһ��
	if(m_bUnique&&pChainVoid!=NULL) return FALSE;

	// ����һ���µļ�¼ָ�뵥Ԫ�����뵽������
	CHAIN Chain;
	memset(&Chain,0,size_of(Chain));
	POSITION posChain=m_ChainList.AddTail(Chain);
	CHAIN* pChain=&m_ChainList.GetAt(posChain);
	pChain->m_pRecord=pRecord;
	pChain->m_posNext=(POSITION)pChainVoid;
	m_ChainMap.SetAt(Key,posChain);
	return TRUE;
}

// ����ɾ��
template<class KEY,class RECORD,int SUBINDEXNUM>
CLIB_INLINE VOID TIndex<KEY,RECORD,SUBINDEXNUM>::DeleteIndex(const KEY& Key,RECORD* pRecord)
{
	// ���ҵ�ǰ����Ӧ�ļ�¼ָ������,����������򷵻�
	LPVOID pChainVoid=NULL;
	if(!m_ChainMap.Lookup(Key,pChainVoid)) pChainVoid=NULL;
	if(pChainVoid==NULL) return;

	// ������������ɾ����¼
	CHAIN* pChainPrev=NULL;
	POSITION posChain=(POSITION)pChainVoid;
	while(posChain!=NULL)
	{
		// ���Ҷ�Ӧ�ļ�¼
		CHAIN* pChain=&m_ChainList.GetAt(posChain);
		if(pChain->m_pRecord!=pRecord)
		{	pChainPrev=pChain;
			posChain=pChain->m_posNext;
			continue;
		}
		// ɾ�����Ǻ���ļ�¼
		if(pChainPrev!=NULL)
		{	pChainPrev->m_posNext=pChain->m_posNext;
			m_ChainList.RemoveAt(posChain);
		}
		// ɾ������ͷ����¼
		else
		{	POSITION posNext=pChain->m_posNext;
			m_ChainList.RemoveAt(posChain);
			if(posNext==NULL)
					m_ChainMap.RemoveKey(Key);
			else	m_ChainMap.SetAt(Key,posNext);
		}
		return;
	}
}




























// ��������
template<class PKEY,class RECORD,INT INDEXNUM>
CLIB_INLINE VOID TMemTable<PKEY,RECORD,INDEXNUM>::BindIndex(LONG nIndex,IIndexRender* pIIndexRender)
{	CLIBVERIFY(nIndex>=0&&nIndex<INDEXNUM);
	CLIBVERIFY(m_apIndexRender[nIndex]==NULL);
	m_apIndexRender[nIndex]=pIIndexRender;
}

// ��ȡ��¼��Ŀ
template<class PKEY,class RECORD,INT INDEXNUM>
CLIB_INLINE LONG TMemTable<PKEY,RECORD,INDEXNUM>::GetRecordNum()
{	return m_RecordMap.GetCount();
}

// �г�����
template<class PKEY,class RECORD,INT INDEXNUM>
CLIB_INLINE VOID TMemTable<PKEY,RECORD,INDEXNUM>::List(LONG nTop,VIEWER pfnView)
{	
	LONG nCount=0;
	POSITION posRecord=m_RecordList.GetHeadPosition();
	while(posRecord!=NULL&&(nTop<=0||nCount<nTop))
	{	RECORD* pRecord=&m_RecordList.GetNext(posRecord);
		if(pRecord->__Krnl.m_bDeleted||pRecord->__Krnl.m_pCopyFrom!=NULL) continue;
		if(pfnView!=NULL) (*pfnView)(pRecord);
		nCount++;
	}
}

// �����¼
template<class PKEY,class RECORD,INT INDEXNUM>
CLIB_INLINE BOOL TMemTable<PKEY,RECORD,INDEXNUM>::Insert(RECORD& Record)
{
	// ͨ����¼�õ�����
	PKEY PKey;
	memset(&PKey,0,size_of(PKey));
	RecordToKeys(Record,&PKey,1);

	CAutoLock AutoLock(&m_CsTable);

	// ʵ�ʲ����¼
	return InsertRecord(NULL,PKey,Record);
}






// ��������ѡȡ��¼
template<class PKEY,class RECORD,INT INDEXNUM>
CLIB_INLINE BOOL TMemTable<PKEY,RECORD,INDEXNUM>::Select(RECORD& Record,const PKEY& PKey)
{
	CAutoLock AutoLock(&m_CsTable);

	// ��������
	LPVOID pRecordVoid=NULL;
	if(!m_RecordMap.Lookup(PKey,pRecordVoid)) return FALSE;
	POSITION posRecord=(POSITION)pRecordVoid;
	RECORD* pRecord=&m_RecordList.GetAt(posRecord);
	if(pRecord->__Krnl.m_bDeleted) return FALSE;

	// ��ȡ��¼
	Record=(*pRecord);

	return TRUE;
}


// �������ݲ���
template<class PKEY,class RECORD,INT INDEXNUM>
CLIB_INLINE LONG TMemTable<PKEY,RECORD,INDEXNUM>::SelectWhere(RECORDLIST* plstResult,LONG nTop,WHERE pfnWhere,...)
{
	// ������
	CLIBVERIFY(plstResult!=NULL);
	plstResult->RemoveAll();
	CAutoLock AutoLock(&m_CsTable);

	// ������¼
	va_list argsWhere;
	va_start(argsWhere,pfnWhere);
	RECORDPTRLIST lstPreliminary;
	SelectRecord(nTop,pfnWhere,argsWhere,lstPreliminary);
	va_end(argsWhere);

	// ��������
	while(!lstPreliminary.IsEmpty())
	{	RECORD* pRecord=lstPreliminary.RemoveHead();
		plstResult->AddTail(*pRecord);
	}
	return plstResult->GetCount();
}

// ������������
template<class PKEY,class RECORD,INT INDEXNUM>
CLIB_INLINE LONG TMemTable<PKEY,RECORD,INDEXNUM>::SelectByIndex(RECORDLIST* plstResult,LONG nTop,LONG nIndex,LPVOID pKey,WHERE pfnWhere,...)
{
	// ������
	CLIBVERIFY(plstResult!=NULL);
	plstResult->RemoveAll();
	if(nIndex<0||nIndex>=INDEXNUM) return 0;
	IIndexRender* pIIndexRender=m_apIndexRender[nIndex];
	CLIBVERIFY(pIIndexRender!=NULL);
	CAutoLock AutoLock(&m_CsTable);

	// ��������
	va_list argsWhere;
	va_start(argsWhere,pfnWhere);
	RECORDPTRLIST lstPreliminary;
	SelectRecord(nTop,pIIndexRender,pKey,pfnWhere,argsWhere,lstPreliminary);
	va_end(argsWhere);

	// ��������
	while(!lstPreliminary.IsEmpty())
	{	RECORD* pRecord=lstPreliminary.RemoveHead();
		plstResult->AddTail(*pRecord);
	}
	return plstResult->GetCount();
}





// �����������Ҳ�����
template<class PKEY,class RECORD,INT INDEXNUM>
CLIB_INLINE RECORD* TMemTable<PKEY,RECORD,INDEXNUM>::SelectForUpdate(const PKEY& PKey)
{
	CAutoLock AutoLock(&m_CsTable);

	// ��������
	LPVOID pRecordVoid=NULL;
	if(!m_RecordMap.Lookup(PKey,pRecordVoid)) return NULL;
	POSITION posRecord=(POSITION)pRecordVoid;
	RECORD* pRecord=&m_RecordList.GetAt(posRecord);

	// ���ɼ�¼����
	return CreateCopyRecord(pRecord);
}

// �����������Ҳ�����
template<class PKEY,class RECORD,INT INDEXNUM>
CLIB_INLINE LONG TMemTable<PKEY,RECORD,INDEXNUM>::SelectForUpdateWhere(RECORDPTRLIST* plstForUpdate,LONG nTop,WHERE pfnWhere,...)
{
	// ������
	CLIBVERIFY(plstForUpdate!=NULL);
	plstForUpdate->RemoveAll();
	CAutoLock AutoLock(&m_CsTable);

	// ������¼
	va_list argsWhere;
	va_start(argsWhere,pfnWhere);
	RECORDPTRLIST lstPreliminary;
	SelectRecord(nTop,pfnWhere,argsWhere,lstPreliminary);
	va_end(argsWhere);

	// ���ɸ�������
	while(!lstPreliminary.IsEmpty())
	{	RECORD* pRecord=lstPreliminary.RemoveHead();
		RECORD* pRecordCopy=CreateCopyRecord(pRecord);
		plstForUpdate->AddTail(pRecordCopy);
	}
	return plstForUpdate->GetCount();
}

// �����������Ҳ�����
template<class PKEY,class RECORD,INT INDEXNUM>
CLIB_INLINE LONG TMemTable<PKEY,RECORD,INDEXNUM>::SelectForUpdateByIndex(RECORDPTRLIST* plstForUpdate,LONG nTop,LONG nIndex,LPVOID pKey,WHERE pfnWhere,...)
{
	// ������
	CLIBVERIFY(plstForUpdate!=NULL);
	plstForUpdate->RemoveAll();
	if(nIndex<0||nIndex>=INDEXNUM) return 0;
	IIndexRender* pIIndexRender=m_apIndexRender[nIndex];
	CLIBVERIFY(pIIndexRender!=NULL);
	CAutoLock AutoLock(&m_CsTable);

	// ��������
	va_list argsWhere;
	va_start(argsWhere,pfnWhere);
	RECORDPTRLIST lstPreliminary;
	SelectRecord(nTop,pIIndexRender,pKey,pfnWhere,argsWhere,lstPreliminary);
	va_end(argsWhere);

	// ���ɸ�������
	while(!lstPreliminary.IsEmpty())
	{	RECORD* pRecord=lstPreliminary.RemoveHead();
		RECORD* pRecordCopy=CreateCopyRecord(pRecord);
		plstForUpdate->AddTail(pRecordCopy);
	}
	return plstForUpdate->GetCount();
}

// �ύ�����޸�
template<class PKEY,class RECORD,INT INDEXNUM>
CLIB_INLINE BOOL TMemTable<PKEY,RECORD,INDEXNUM>::CommitUpdate(RECORD* pRecord,BOOL bCancel)
{
	// ����Ƿ��Ƴ����ļ�¼
	CLIBVERIFY(pRecord->__Krnl.m_bDeleted==FALSE);
	CLIBVERIFY(pRecord->__Krnl.m_nRecordRef==-1);
	CLIBVERIFY(pRecord->__Krnl.m_pCopyFrom!=NULL);

	// �����������ύ����
	BOOL bCommitSuccess=TRUE;
	RECORD* pCopyFrom=(RECORD*)pRecord->__Krnl.m_pCopyFrom;
	CAutoLock AutoLock(&m_CsTable);
	if(!bCancel)
	{	bCommitSuccess=(pRecord->__Krnl.m_nRecordVer==pCopyFrom->__Krnl.m_nRecordVer);
		if(bCommitSuccess)
		{	pRecord->__Krnl=pCopyFrom->__Krnl;
			(*pCopyFrom)=(*pRecord);
			pCopyFrom->__Krnl.m_nRecordVer++;
		}
	}
	// ɾ����ʱ��¼
	m_RecordList.RemoveByPtr(pRecord);
	pCopyFrom->__Krnl.m_nRecordRef--;
	if(pCopyFrom->__Krnl.m_nRecordRef<=0) m_RecordList.RemoveByPtr(pCopyFrom);
	return bCommitSuccess;
}

// �����ύ�����޸�
template<class PKEY,class RECORD,INT INDEXNUM>
CLIB_INLINE BOOL TMemTable<PKEY,RECORD,INDEXNUM>::BatchCommitUpdate(RECORDPTRLIST* plstForUpdate,BOOL bCancel)
{
	CLIBVERIFY(plstForUpdate!=NULL);
	CAutoLock AutoLock(&m_CsTable);
	BOOL bOneOrMoreFail=FALSE;
	while(!plstForUpdate->IsEmpty())
	{	RECORD* pRecord=plstForUpdate->RemoveHead();
		if(!CommitUpdate(pRecord,bCancel)) bOneOrMoreFail=TRUE;
	}
	return !bOneOrMoreFail;
}


// ���¼�¼(����)
template<class PKEY,class RECORD,INT INDEXNUM>
CLIB_INLINE BOOL TMemTable<PKEY,RECORD,INDEXNUM>::Update(RECORD* pAffect,const PKEY& PKey,UPDATE_ROUTINE pfnUpdateRoutine,...)
{
	// ������
	if(pfnUpdateRoutine==NULL) return FALSE;

	CAutoLock AutoLock(&m_CsTable);

	// ��������
	LPVOID pRecordVoid=NULL;
	if(!m_RecordMap.Lookup(PKey,pRecordVoid)) return FALSE;
	POSITION posRecord=(POSITION)pRecordVoid;
	RECORD* pRecord=&m_RecordList.GetAt(posRecord);
	if(pRecord->__Krnl.m_bDeleted) return FALSE;

	va_list args;
	va_start(args,pfnUpdateRoutine);
	(*pfnUpdateRoutine)(pRecord,args);
	pRecord->__Krnl.m_nRecordVer++;
	if(pAffect!=NULL) (*pAffect)=(*pRecord);
	va_end(args);
	return TRUE;
}

// ���¼�¼(����ƥ��)
template<class PKEY,class RECORD,INT INDEXNUM>
CLIB_INLINE LONG TMemTable<PKEY,RECORD,INDEXNUM>::UpdateWhere(RECORDLIST* plstAffect,LONG nTop,WHERE pfnWhere,ARGS_SHIFTER pfnWhereShifer,UPDATE_ROUTINE pfnUpdateRoutine,...)
{
	// ������
	if(pfnUpdateRoutine==NULL) return 0;
	va_list argsWhere,argsUpdate;
	va_start(argsWhere,pfnUpdateRoutine);
	va_start(argsUpdate,pfnUpdateRoutine);
	if(pfnWhere!=NULL&&pfnWhereShifer!=NULL) (*pfnWhereShifer)(argsUpdate);
	CAutoLock AutoLock(&m_CsTable);

	// ������¼
	RECORDPTRLIST lstPreliminary;
	SelectRecord(nTop,pfnWhere,argsWhere,lstPreliminary);

	// ���ø���
	LONG nAffectRecords=0;
	while(!lstPreliminary.IsEmpty())
	{	RECORD* pRecord=lstPreliminary.RemoveHead();
		(*pfnUpdateRoutine)(pRecord,argsUpdate);
		pRecord->__Krnl.m_nRecordVer++;
		nAffectRecords++;
		if(plstAffect!=NULL) plstAffect->AddTail(*pRecord);
		if(nTop>0&&nAffectRecords>=nTop) break;
	}
	return nAffectRecords;
}

// ���¼�¼(����ƥ��)
template<class PKEY,class RECORD,INT INDEXNUM>
CLIB_INLINE LONG TMemTable<PKEY,RECORD,INDEXNUM>::UpdateByIndex(RECORDLIST* plstAffect,LONG nTop,LONG nIndex,LPVOID pKey,WHERE pfnWhere,ARGS_SHIFTER pfnWhereShifer,UPDATE_ROUTINE pfnUpdateRoutine,...)
{
	// ������
	if(nIndex<0||nIndex>=INDEXNUM) return 0;
	if(pfnUpdateRoutine==NULL) return 0;
	va_list argsWhere,argsUpdate;
	va_start(argsWhere,pfnUpdateRoutine);
	va_start(argsUpdate,pfnUpdateRoutine);
	if(pfnWhere!=NULL&&pfnWhereShifer!=NULL) (*pfnWhereShifer)(argsUpdate);
	IIndexRender* pIIndexRender=m_apIndexRender[nIndex];
	CLIBVERIFY(pIIndexRender!=NULL);
	CAutoLock AutoLock(&m_CsTable);

	// ��������
	RECORDPTRLIST lstPreliminary;
	SelectRecord(nTop,pIIndexRender,pKey,pfnWhere,argsWhere,lstPreliminary);

	// ���ø���
	LONG nAffectRecords=0;
	while(!lstPreliminary.IsEmpty())
	{	RECORD* pRecord=lstPreliminary.RemoveHead();
		(*pfnUpdateRoutine)(pRecord,argsUpdate);
		pRecord->__Krnl.m_nRecordVer++;
		nAffectRecords++;
		if(plstAffect!=NULL) plstAffect->AddTail(*pRecord);
		if(nTop>0&&nAffectRecords>=nTop) break;
	}
	return nAffectRecords;
}




// ��������
template<class PKEY,class RECORD,INT INDEXNUM>
CLIB_INLINE BOOL TMemTable<PKEY,RECORD,INDEXNUM>::InsertOrUpdate(RECORD* pAffect,const PKEY& PKey,INSERTUPDATE_ROUTINE pfnInsertUpdateRoutine,...)
{
	// ������
	if(pfnInsertUpdateRoutine==NULL) return FALSE;

	CAutoLock AutoLock(&m_CsTable);

	// ���Ҽ�¼�Ƿ����,����������������
	LPVOID pRecordVoid=NULL;
	if(m_RecordMap.Lookup(PKey,pRecordVoid))
	{	POSITION posRecord=(POSITION)pRecordVoid;
		RECORD* pRecord=&m_RecordList.GetAt(posRecord);
		va_list args;
		va_start(args,pfnInsertUpdateRoutine);
		(*pfnInsertUpdateRoutine)(pRecord,&PKey,FALSE,args);
		va_end(args);
		pRecord->__Krnl.m_nRecordVer++;
		if(pAffect!=NULL) (*pAffect)=(*pRecord);
		return TRUE;
	}

	// ���Բ����¼
	RECORD Record;
	memset(&Record,0,size_of(Record));
	va_list args;
	va_start(args,pfnInsertUpdateRoutine);
	(*pfnInsertUpdateRoutine)(&Record,&PKey,TRUE,args);
	va_end(args);
	return InsertRecord(pAffect,PKey,Record);
}

// ��������
template<class PKEY,class RECORD,INT INDEXNUM>
CLIB_INLINE BOOL TMemTable<PKEY,RECORD,INDEXNUM>::InsertOrUpdateWhere(RECORD* pAffect,WHERE pfnWhere,ARGS_SHIFTER pfnWhereShifer,INSERTUPDATE_ROUTINE pfnInsertUpdateRoutine,...)
{
	// ������
	if(pfnInsertUpdateRoutine==NULL) return FALSE;
	va_list argsWhere,argsInsertUpdate;
	va_start(argsWhere,pfnInsertUpdateRoutine);
	va_start(argsInsertUpdate,pfnInsertUpdateRoutine);
	if(pfnWhere!=NULL&&pfnWhereShifer!=NULL) (*pfnWhereShifer)(argsInsertUpdate);
	CAutoLock AutoLock(&m_CsTable);

	// ������¼
	RECORD* apPreliminary[2]={0,0};
	DWORD dwSelected=SelectRecordEx(ARRAYSIZE(apPreliminary),2,pfnWhere,argsWhere,apPreliminary);
	
	// ���в�������
	BOOL bSuccess=TRUE;
	do 
	{	// ��¼����һ��(��֪��������һ��)
		if(dwSelected>1)
		{	bSuccess=FALSE;
			break;
		}
		// �����ҽ���һ����¼(���и���)
		else if(dwSelected>0)
		{	RECORD* pRecord=apPreliminary[0];
			(*pfnInsertUpdateRoutine)(pRecord,NULL,FALSE,argsInsertUpdate);
			pRecord->__Krnl.m_nRecordVer++;
			if(pAffect!=NULL) (*pAffect)=(*pRecord);
			break;
		}
		// ��¼������,���Բ����¼
		RECORD Record;
		memset(&Record,0,size_of(Record));
		(*pfnInsertUpdateRoutine)(&Record,NULL,TRUE,argsInsertUpdate);
		PKEY PKey;
		memset(&PKey,0,size_of(PKey));
		RecordToKeys(Record,&PKey,1);
		bSuccess=InsertRecord(pAffect,PKey,Record);
		break;
	} while(FALSE);
	va_end(argsWhere);
	va_end(argsInsertUpdate);
	return bSuccess;
}

// ��������
template<class PKEY,class RECORD,INT INDEXNUM>
CLIB_INLINE BOOL TMemTable<PKEY,RECORD,INDEXNUM>::InsertOrUpdateByIndex(RECORD* pAffect,LONG nIndex,LPVOID pKey,WHERE pfnWhere,ARGS_SHIFTER pfnWhereShifer,INSERTUPDATE_ROUTINE pfnInsertUpdateRoutine,...)
{
	// ������
	if(pfnInsertUpdateRoutine==NULL) return FALSE;
	if(nIndex<0||nIndex>=INDEXNUM) return FALSE;
	IIndexRender* pIIndexRender=m_apIndexRender[nIndex];
	CLIBVERIFY(pIIndexRender!=NULL);
	va_list argsWhere,argsInsertUpdate;
	va_start(argsWhere,pfnInsertUpdateRoutine);
	va_start(argsInsertUpdate,pfnInsertUpdateRoutine);
	if(pfnWhere!=NULL&&pfnWhereShifer!=NULL) (*pfnWhereShifer)(argsInsertUpdate);
	CAutoLock AutoLock(&m_CsTable);

	// ������¼
	RECORD* apPreliminary[2]={0,0};
	DWORD dwSelected=SelectRecordEx(ARRAYSIZE(apPreliminary),2,pIIndexRender,pKey,pfnWhere,argsWhere,apPreliminary);

	// ���в�������
	BOOL bSuccess=TRUE;
	do 
	{	// ��¼����һ��(��֪��������һ��)
		if(dwSelected>1)
		{	bSuccess=FALSE;
			break;
		}
		// �����ҽ���һ����¼(���и���)
		else if(dwSelected>0)
		{	RECORD* pRecord=apPreliminary[0];
			(*pfnInsertUpdateRoutine)(pRecord,NULL,FALSE,argsInsertUpdate);
			pRecord->m_nRecordVer++;
			if(pAffect!=NULL) (*pAffect)=(*pRecord);
			break;
		}
		// ��¼������,���Բ����¼
		RECORD Record;
		memset(&Record,0,size_of(Record));
		(*pfnInsertUpdateRoutine)(&Record,NULL,TRUE,argsInsertUpdate);
		PKEY PKey;
		memset(&PKey,0,size_of(PKey));
		RecordToKeys(Record,&PKey,1);
		bSuccess=InsertRecord(pAffect,PKey,Record);
		break;
	} while(FALSE);
	va_end(argsWhere);
	va_end(argsInsertUpdate);
	return bSuccess;
}



// ��������ɾ����¼
template<class PKEY,class RECORD,INT INDEXNUM>
CLIB_INLINE BOOL TMemTable<PKEY,RECORD,INDEXNUM>::Delete(RECORD* pAffect,const PKEY& PKey)
{
	CAutoLock AutoLock(&m_CsTable);

	// ��������
	LPVOID pRecordVoid=NULL;
	if(!m_RecordMap.Lookup(PKey,pRecordVoid)) return FALSE;
	POSITION posRecord=(POSITION)pRecordVoid;
	RECORD* pRecord=&m_RecordList.GetAt(posRecord);

	// ɾ������,�����ͼ�¼
	DeleteRecord(pAffect,pRecord);

	return TRUE;
}

// ��������ɾ����¼
template<class PKEY,class RECORD,INT INDEXNUM>
CLIB_INLINE LONG TMemTable<PKEY,RECORD,INDEXNUM>::DeleteWhere(RECORDLIST* plstAffect,LONG nTop,WHERE pfnWhere,...)
{
	// ������
	CAutoLock AutoLock(&m_CsTable);
	
	// ������¼
	va_list argsWhere;
	va_start(argsWhere,pfnWhere);
	RECORDPTRLIST lstPreliminary;
	SelectRecord(nTop,pfnWhere,argsWhere,lstPreliminary);
	va_end(argsWhere);

	// ɾ����¼
	LONG nAffectRecords=0;
	while(!lstPreliminary.IsEmpty())
	{	RECORD* pRecord=lstPreliminary.RemoveHead();
		nAffectRecords++;
		RECORD RecordAffect;
		memset(&RecordAffect,0,size_of(RecordAffect));
		DeleteRecord(&RecordAffect,pRecord);
		if(plstAffect!=NULL) plstAffect->AddTail(RecordAffect);
		if(nTop>0&&nAffectRecords>=nTop) break;
	}
	return nAffectRecords;
}

// ��������ɾ����¼
template<class PKEY,class RECORD,INT INDEXNUM>
CLIB_INLINE LONG TMemTable<PKEY,RECORD,INDEXNUM>::DeleteByIndex(RECORDLIST* plstAffect,LONG nTop,LONG nIndex,LPVOID pKey,WHERE pfnWhere,...)
{
	// ������
	if(nIndex<0||nIndex>=INDEXNUM) return 0;
	IIndexRender* pIIndexRender=m_apIndexRender[nIndex];
	CLIBVERIFY(pIIndexRender!=NULL);
	CAutoLock AutoLock(&m_CsTable);

	// ��������
	va_list argsWhere;
	va_start(argsWhere,pfnWhere);
	RECORDPTRLIST lstPreliminary;
	SelectRecord(nTop,pIIndexRender,pKey,pfnWhere,argsWhere,lstPreliminary);
	va_end(argsWhere);

	// ɾ����¼
	LONG nAffectRecords=0;
	while(!lstPreliminary.IsEmpty())
	{	RECORD* pRecord=lstPreliminary.RemoveHead();
		nAffectRecords++;
		RECORD RecordAffect;
		memset(&RecordAffect,0,size_of(RecordAffect));
		DeleteRecord(&RecordAffect,pRecord);
		if(plstAffect!=NULL) plstAffect->AddTail(RecordAffect);
		if(nTop>0&&nAffectRecords>=nTop) break;
	}
	return nAffectRecords;
}













// �������ݲ���(����ģʽ)
template<class PKEY,class RECORD,INT INDEXNUM>
CLIB_INLINE LONG TMemTable<PKEY,RECORD,INDEXNUM>::SelectWhereEx(RECORD* pResult,DWORD dwMax,LONG nTop,WHERE pfnWhere,...)
{
	// ������
	CLIBVERIFY(pResult!=NULL);
	dwMax=max_of(dwMax,1);
	CAutoLock AutoLock(&m_CsTable);

	// ������¼
	va_list argsWhere;
	va_start(argsWhere,pfnWhere);
	RECORD** ppPreliminary=(RECORD**)alloca(dwMax*size_of(RECORD*));
	DWORD dwSelected=SelectRecordEx(dwMax,nTop,pfnWhere,argsWhere,ppPreliminary);
	va_end(argsWhere);

	// ��������
	for(DWORD dwItem=0; dwItem<dwSelected; dwItem++)
	{	RECORD* pRecord=ppPreliminary[dwItem];
		pResult[dwItem]=(*pRecord);
	}
	return dwSelected;
}

// ������������(����ģʽ)
template<class PKEY,class RECORD,INT INDEXNUM>
CLIB_INLINE LONG TMemTable<PKEY,RECORD,INDEXNUM>::SelectByIndexEx(RECORD* pResult,DWORD dwMax,LONG nTop,LONG nIndex,LPVOID pKey,WHERE pfnWhere,...)
{
	// ������
	CLIBVERIFY(pResult!=NULL);
	dwMax=max_of(dwMax,1);
	if(nIndex<0||nIndex>=INDEXNUM) return 0;
	IIndexRender* pIIndexRender=m_apIndexRender[nIndex];
	CLIBVERIFY(pIIndexRender!=NULL);
	CAutoLock AutoLock(&m_CsTable);

	// ��������
	va_list argsWhere;
	va_start(argsWhere,pfnWhere);
	RECORD** ppPreliminary=(RECORD**)alloca(dwMax*size_of(RECORD*));
	DWORD dwSelected=SelectRecordEx(dwMax,nTop,pIIndexRender,pKey,pfnWhere,argsWhere,ppPreliminary);
	va_end(argsWhere);

	// ��������
	for(DWORD dwItem=0; dwItem<dwSelected; dwItem++)
	{	RECORD* pRecord=ppPreliminary[dwItem];
		pResult[dwItem]=(*pRecord);
	}
	return dwSelected;
}


// �����������Ҳ�����(����ģʽ)
template<class PKEY,class RECORD,INT INDEXNUM>
CLIB_INLINE LONG TMemTable<PKEY,RECORD,INDEXNUM>::SelectForUpdateWhereEx(RECORD** ppForUpdate,DWORD dwMax,LONG nTop,WHERE pfnWhere,...)
{
	// ������
	CLIBVERIFY(ppForUpdate!=NULL);
	dwMax=max_of(dwMax,1);
	CAutoLock AutoLock(&m_CsTable);

	// ������¼
	va_list argsWhere;
	va_start(argsWhere,pfnWhere);
	RECORD** ppPreliminary=(RECORD**)alloca(dwMax*size_of(RECORD*));
	DWORD dwSelected=SelectRecordEx(dwMax,nTop,pfnWhere,argsWhere,ppPreliminary);
	va_end(argsWhere);

	// ���ɸ�������
	for(DWORD dwSelect=0; dwSelect<dwSelected; dwSelect++)
	{	RECORD* pRecord=ppPreliminary[dwSelect];
		RECORD* pRecordCopy=CreateCopyRecord(pRecord);
		ppForUpdate[dwSelect]=pRecordCopy;
	}
	return dwSelected;
}

// �����������Ҳ�����(����ģʽ)
template<class PKEY,class RECORD,INT INDEXNUM>
CLIB_INLINE LONG TMemTable<PKEY,RECORD,INDEXNUM>::SelectForUpdateByIndexEx(RECORD** ppForUpdate,DWORD dwMax,LONG nTop,LONG nIndex,LPVOID pKey,WHERE pfnWhere,...)
{
	// ������
	CLIBVERIFY(ppForUpdate!=NULL);
	dwMax=max_of(dwMax,1);
	if(nIndex<0||nIndex>=INDEXNUM) return 0;
	IIndexRender* pIIndexRender=m_apIndexRender[nIndex];
	CLIBVERIFY(pIIndexRender!=NULL);
	CAutoLock AutoLock(&m_CsTable);

	// ��������
	va_list argsWhere;
	va_start(argsWhere,pfnWhere);
	RECORD** ppPreliminary=(RECORD**)alloca(dwMax*size_of(RECORD*));
	DWORD dwSelected=SelectRecordEx(dwMax,nTop,pIIndexRender,pKey,pfnWhere,argsWhere,ppPreliminary);
	va_end(argsWhere);

	// ���ɸ�������
	for(DWORD dwSelect=0; dwSelect<dwSelected; dwSelect++)
	{	RECORD* pRecord=ppPreliminary[dwSelect];
		RECORD* pRecordCopy=CreateCopyRecord(pRecord);
		ppForUpdate[dwSelect]=pRecordCopy;
	}
	return dwSelected;
}

// �����ύ�����޸�(����ģʽ)
template<class PKEY,class RECORD,INT INDEXNUM>
CLIB_INLINE BOOL TMemTable<PKEY,RECORD,INDEXNUM>::BatchCommitUpdateEx(RECORD** ppForUpdate,DWORD dwCount,BOOL bCancel)
{
	CLIBVERIFY(ppForUpdate!=NULL);
	CAutoLock AutoLock(&m_CsTable);
	BOOL bOneOrMoreFail=FALSE;
	for(DWORD dwRecord=0; dwRecord<dwCount; dwRecord++)
	{	RECORD* pRecord=ppForUpdate[dwRecord];
		if(!CommitUpdate(pRecord,bCancel)) bOneOrMoreFail=TRUE;
	}
	return !bOneOrMoreFail;
}

// ���¼�¼(����ƥ��,����ģʽ)
template<class PKEY,class RECORD,INT INDEXNUM>
CLIB_INLINE LONG TMemTable<PKEY,RECORD,INDEXNUM>::UpdateWhereEx(RECORD* pAffect,DWORD dwMax,LONG nTop,WHERE pfnWhere,ARGS_SHIFTER pfnWhereShifer,UPDATE_ROUTINE pfnUpdateRoutine,...)
{
	// ������
	dwMax=max_of(dwMax,1);
	if(pfnUpdateRoutine==NULL) return 0;
	va_list argsWhere,argsUpdate;
	va_start(argsWhere,pfnUpdateRoutine);
	va_start(argsUpdate,pfnUpdateRoutine);
	if(pfnWhere!=NULL&&pfnWhereShifer!=NULL) (*pfnWhereShifer)(argsUpdate);
	CAutoLock AutoLock(&m_CsTable);

	// ������¼
	RECORD** ppPreliminary=(RECORD**)alloca(dwMax*size_of(RECORD*));
	DWORD dwSelected=SelectRecordEx(dwMax,nTop,pfnWhere,argsWhere,ppPreliminary);

	// ���ø���
	for(DWORD dwSelect=0; dwSelect<dwSelected; dwSelect++)
	{	RECORD* pRecord=ppPreliminary[dwSelect];
		(*pfnUpdateRoutine)(pRecord,argsUpdate);
		pRecord->__Krnl.m_nRecordVer++;
		if(pAffect!=NULL) pAffect[dwSelect]=(*pRecord);
	}
	return dwSelected;
}

// ���¼�¼(����ƥ��,����ģʽ)
template<class PKEY,class RECORD,INT INDEXNUM>
CLIB_INLINE LONG TMemTable<PKEY,RECORD,INDEXNUM>::UpdateByIndexEx(RECORD* pAffect,DWORD dwMax,LONG nTop,LONG nIndex,LPVOID pKey,WHERE pfnWhere,ARGS_SHIFTER pfnWhereShifer,UPDATE_ROUTINE pfnUpdateRoutine,...)
{
	// ������
	dwMax=max_of(dwMax,1);
	if(nIndex<0||nIndex>=INDEXNUM) return 0;
	if(pfnUpdateRoutine==NULL) return 0;
	va_list argsWhere,argsUpdate;
	va_start(argsWhere,pfnUpdateRoutine);
	va_start(argsUpdate,pfnUpdateRoutine);
	if(pfnWhere!=NULL&&pfnWhereShifer!=NULL) (*pfnWhereShifer)(argsUpdate);
	IIndexRender* pIIndexRender=m_apIndexRender[nIndex];
	CLIBVERIFY(pIIndexRender!=NULL);
	CAutoLock AutoLock(&m_CsTable);

	// ��������
	RECORD** ppPreliminary=(RECORD**)alloca(dwMax*size_of(RECORD*));
	DWORD dwSelected=SelectRecordEx(dwMax,nTop,pIIndexRender,pKey,pfnWhere,argsWhere,ppPreliminary);

	// ���ø���
	for(DWORD dwSelect=0; dwSelect<dwSelected; dwSelect++)
	{	RECORD* pRecord=ppPreliminary[dwSelect];
		(*pfnUpdateRoutine)(pRecord,argsUpdate);
		pRecord->__Krnl.m_nRecordVer++;
		if(pAffect!=NULL) pAffect[dwSelect]=(*pRecord);
	}
	return dwSelected;
}


// ��������ɾ����¼(����ģʽ)
template<class PKEY,class RECORD,INT INDEXNUM>
CLIB_INLINE LONG TMemTable<PKEY,RECORD,INDEXNUM>::DeleteWhereEx(RECORD* pAffect,DWORD dwMax,LONG nTop,WHERE pfnWhere,...)
{
	// ������
	dwMax=max_of(dwMax,1);
	CAutoLock AutoLock(&m_CsTable);
	
	// ������¼
	va_list argsWhere;
	va_start(argsWhere,pfnWhere);
	RECORD** ppPreliminary=(RECORD**)alloca(dwMax*size_of(RECORD*));
	DWORD dwSelected=SelectRecordEx(dwMax,nTop,pfnWhere,argsWhere,ppPreliminary);
	va_end(argsWhere);

	// ɾ����¼
	for(DWORD dwSelect=0; dwSelect<dwSelected; dwSelect++)
	{	RECORD* pRecord=ppPreliminary[dwSelect];
		RECORD RecordAffect;
		memset(&RecordAffect,0,size_of(RecordAffect));
		DeleteRecord(&RecordAffect,pRecord);
		if(pAffect!=NULL) pAffect[dwSelect]=RecordAffect;
	}
	return dwSelected;
}

// ��������ɾ����¼(����ģʽ)
template<class PKEY,class RECORD,INT INDEXNUM>
CLIB_INLINE LONG TMemTable<PKEY,RECORD,INDEXNUM>::DeleteByIndexEx(RECORD* pAffect,DWORD dwMax,LONG nTop,LONG nIndex,LPVOID pKey,WHERE pfnWhere,...)
{
	// ������
	dwMax=max_of(dwMax,1);
	if(nIndex<0||nIndex>=INDEXNUM) return 0;
	IIndexRender* pIIndexRender=m_apIndexRender[nIndex];
	CLIBVERIFY(pIIndexRender!=NULL);
	CAutoLock AutoLock(&m_CsTable);

	// ��������
	va_list argsWhere;
	va_start(argsWhere,pfnWhere);
	RECORD** ppPreliminary=(RECORD**)alloca(dwMax*size_of(RECORD*));
	DWORD dwSelected=SelectRecordEx(dwMax,nTop,pIIndexRender,pKey,pfnWhere,argsWhere,ppPreliminary);
	va_end(argsWhere);

	// ɾ����¼
	for(DWORD dwSelect=0; dwSelect<dwSelected; dwSelect++)
	{	RECORD* pRecord=ppPreliminary[dwSelect];
		RECORD RecordAffect;
		memset(&RecordAffect,0,size_of(RecordAffect));
		DeleteRecord(&RecordAffect,pRecord);
		if(pAffect!=NULL) pAffect[dwSelect]=RecordAffect;
	}
	return dwSelected;
}













// ���Ҽ�¼(ͨ������)
template<class PKEY,class RECORD,INT INDEXNUM>
CLIB_INLINE VOID TMemTable<PKEY,RECORD,INDEXNUM>::SelectRecord(LONG nTop,WHERE pfnWhere,va_list argsWhere,RECORDPTRLIST& lstPreliminary)
{	POSITION posRecord=m_RecordList.GetHeadPosition();
	while(posRecord!=NULL)
	{	RECORD* pRecord=&m_RecordList.GetNext(posRecord);
		if(pRecord->__Krnl.m_bDeleted||pRecord->__Krnl.m_pCopyFrom!=NULL) continue;
		if(pfnWhere!=NULL&&!(*pfnWhere)(pRecord,argsWhere)) continue;
		lstPreliminary.AddTail(pRecord);
		if(nTop>0&&lstPreliminary.GetCount()>=nTop) break;
	}
}

// ���Ҽ�¼(ͨ������)
template<class PKEY,class RECORD,INT INDEXNUM>
CLIB_INLINE VOID TMemTable<PKEY,RECORD,INDEXNUM>::SelectRecord(LONG nTop,IIndexRender* pIIndexRender,LPVOID pKey,WHERE pfnWhere,va_list argsWhere,RECORDPTRLIST& lstPreliminary)
{	RECORDPTRLIST lstPreliminaryIX;
	pIIndexRender->OnSelectUsingIndex((pfnWhere==NULL)?nTop:(-1),pKey,&lstPreliminaryIX);
	if(lstPreliminaryIX.IsEmpty())
	{	lstPreliminary.RemoveAll();
		return;
	}
	while(!lstPreliminaryIX.IsEmpty())
	{	RECORD* pRecord=lstPreliminaryIX.RemoveHead();
		if(pfnWhere!=NULL&&!(*pfnWhere)(pRecord,argsWhere)) continue;
		lstPreliminary.AddTail(pRecord);
		if(nTop>0&&lstPreliminary.GetCount()>=nTop) break;
	}
}

// ���Ҽ�¼(ͨ������)
template<class PKEY,class RECORD,INT INDEXNUM>
CLIB_INLINE DWORD TMemTable<PKEY,RECORD,INDEXNUM>::SelectRecordEx(DWORD dwMax,LONG nTop,WHERE pfnWhere,va_list argsWhere,RECORD** ppPreliminarys)
{	DWORD dwSelectedNum=0;
	POSITION posRecord=m_RecordList.GetHeadPosition();
	while(posRecord!=NULL)
	{	RECORD* pRecord=&m_RecordList.GetNext(posRecord);
		if(pRecord->__Krnl.m_bDeleted||pRecord->__Krnl.m_pCopyFrom!=NULL) continue;
		if(pfnWhere!=NULL&&!(*pfnWhere)(pRecord,argsWhere)) continue;
		if(dwSelectedNum>=dwMax) break;
		ppPreliminarys[dwSelectedNum]=pRecord;
		dwSelectedNum++;
		if(nTop>0&&dwSelectedNum>=(DWORD)nTop) break;
		if(dwSelectedNum>=dwMax) break;
	}
	return dwSelectedNum;
}

// ���Ҽ�¼(ͨ������)
template<class PKEY,class RECORD,INT INDEXNUM>
CLIB_INLINE DWORD TMemTable<PKEY,RECORD,INDEXNUM>::SelectRecordEx(DWORD dwMax,LONG nTop,IIndexRender* pIIndexRender,LPVOID pKey,WHERE pfnWhere,va_list argsWhere,RECORD** ppPreliminarys)
{
	DWORD dwMaxPreliminaryIX=min_of(2*dwMax,1024);
	RECORD** ppPreliminaryIX=(RECORD**)alloca(dwMaxPreliminaryIX*size_of(LPVOID));
	DWORD dwSelectedIX=pIIndexRender->OnSelectUsingIndexEx(dwMaxPreliminaryIX,(pfnWhere==NULL)?nTop:(-1),pKey,(LPVOID*)ppPreliminaryIX);
	if(dwSelectedIX<=0) return 0;
	DWORD dwSelected=0;
	for(DWORD dwSelectIX=0; dwSelectIX<dwSelectedIX; dwSelectIX++)
	{	RECORD* pRecord=ppPreliminaryIX[dwSelectIX];
		if(pfnWhere!=NULL&&!(*pfnWhere)(pRecord,argsWhere)) continue;
		if(dwSelected>=dwMax) break;
		ppPreliminarys[dwSelected]=pRecord;
		dwSelected++;
		if(nTop>0&&dwSelected>=(DWORD)nTop) break;
		if(dwSelected>=dwMax) break;
	}
	return dwSelected;
}



// �����¼
template<class PKEY,class RECORD,INT INDEXNUM>
CLIB_INLINE BOOL TMemTable<PKEY,RECORD,INDEXNUM>::InsertRecord(RECORD* pAffect,const PKEY& PKey,RECORD& Record)
{
	// ���������ͻ,����ʧ��
	LPVOID pRecordVoid=NULL;
	if(m_RecordMap.Lookup(PKey,pRecordVoid)) return FALSE;

	// ���Ӽ�¼
	POSITION posRecord=m_RecordList.AddTail(Record);
	CLIBVERIFY(posRecord!=NULL);

	// ����ȫ������
	RECORD* pRecord=&m_RecordList.GetAt(posRecord);
	pRecord->__Krnl.m_bDeleted=FALSE;
	pRecord->__Krnl.m_nRecordVer=0;
	pRecord->__Krnl.m_nRecordRef=1;
	pRecord->__Krnl.m_pCopyFrom=NULL;
	BOOL bRollback=FALSE;
	LONG nIndex=0;
	for(nIndex=0; nIndex<INDEXNUM; nIndex++)
	{	IIndexRender* pIIndexRender=m_apIndexRender[nIndex];
		CLIBVERIFY(pIIndexRender!=NULL);
		if(!pIIndexRender->OnInsertRecord(pRecord))
		{	bRollback=TRUE;
			break;
		}
	}
	// ����������ݻ���,�����Ѿ�������������ɾ����ʱ������
	if(bRollback)
	{	while(nIndex>0)
		{	nIndex--;
			IIndexRender* pIIndexRender=m_apIndexRender[nIndex];
			CLIBVERIFY(pIIndexRender!=NULL);
			pIIndexRender->OnDeleteRecord(pRecord);
		}
		m_RecordList.RemoveAt(posRecord);
		return FALSE;
	}

	// ��������
	m_RecordMap.SetAt(PKey,posRecord);

	// ������Ӱ����ֶ�
	if(pAffect!=NULL) (*pAffect)=(*pRecord);

	return TRUE;
}

// ɾ����¼
template<class PKEY,class RECORD,INT INDEXNUM>
CLIB_INLINE VOID TMemTable<PKEY,RECORD,INDEXNUM>::DeleteRecord(RECORD* pAffect,RECORD* pRecord)
{
	// ɾ������,�����ͼ�¼
	if(!pRecord->__Krnl.m_bDeleted)
	{	
		// ͨ����¼�õ�����
		PKEY PKey;
		memset(&PKey,0,size_of(PKey));
		RecordToKeys(*pRecord,&PKey,1);
		// ɾ������
		m_RecordMap.RemoveKey(PKey);
		// ����ȫ������
		for(LONG nIndex=0; nIndex<INDEXNUM; nIndex++)
		{	IIndexRender* pIIndexRender=m_apIndexRender[nIndex];
			CLIBVERIFY(pIIndexRender!=NULL);
			pIIndexRender->OnDeleteRecord(pRecord);
		}
		// ɾ����¼
		pRecord->__Krnl.m_bDeleted=TRUE;
		pRecord->__Krnl.m_nRecordVer++;
		pRecord->__Krnl.m_nRecordRef--;
		if(pAffect!=NULL) (*pAffect)=(*pRecord);
		if(pRecord->__Krnl.m_nRecordRef<=0) m_RecordList.RemoveByPtr(pRecord);
	}
}

// ������¼����
template<class PKEY,class RECORD,INT INDEXNUM>
CLIB_INLINE RECORD* TMemTable<PKEY,RECORD,INDEXNUM>::CreateCopyRecord(RECORD* pRecord)
{	POSITION posCopy=m_RecordList.AddTail(*pRecord);
	RECORD* pCopy=&m_RecordList.GetAt(posCopy);
	pCopy->__Krnl.m_bDeleted=FALSE;
	pCopy->__Krnl.m_nRecordVer=pRecord->__Krnl.m_nRecordVer;
	pCopy->__Krnl.m_nRecordRef=-1;
	pCopy->__Krnl.m_pCopyFrom=pRecord;
	pRecord->__Krnl.m_nRecordRef++;
	return pCopy;
}




#endif