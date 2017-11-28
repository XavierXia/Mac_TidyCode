
// 	// AP节点
// 	typedef struct tagAPNODE
// 	{	TCHAR m_szAPNode[16];		// AP节点
// 	} APNODE;
// 	// 用户
// 	typedef struct tagUSER
// 	{	DWORD m_dwUOrgID;			// 用户分支机构
// 		CHAR m_szUID[UID_SIZE];		// 用户ID
// 	} USER;
// 	// 别名
// 	typedef struct tagALIAS
// 	{	TCHAR m_szAlias[16];		// 别名ID
// 	} ALIAS;
// 	// 行记录
// 	typedef struct tagREADER
// 	{	RECKRNL __Krnl;				// 记录核心字段
// 		TCHAR m_szAPNode[16];		// AP节点
// 		DWORD m_dwUOrgID;			// 用户分支机构
// 		CHAR  m_szUID[UID_SIZE];	// 用户ID
// 		TCHAR m_szAliases[256];		// 别名
// 		TCHAR m_szAP[AP_SIZE];		// AP信息
// 		TCHAR m_szName[32];			// 我的名字
// 	} READER;
// 
// 	inline DWORD RecordToKeys(const READER& Reader,APNODE* pKey,DWORD dwMaxNum)
// 	{	UNREFERENCED_PARAMETER(dwMaxNum);
// 		CLIBASSERT(pKey!=NULL);
// 		CLIBASSERT(dwMaxNum>0);
// 		COPYSTRARRAY(pKey->m_szAPNode,Reader.m_szAPNode);
// 		return 1;
// 	}
// 	inline DWORD RecordToKeys(const READER& Reader,USER* pKey,DWORD dwMaxNum)
// 	{	UNREFERENCED_PARAMETER(dwMaxNum);
// 		CLIBASSERT(pKey!=NULL);
// 		CLIBASSERT(dwMaxNum>0);
// 		pKey->m_dwUOrgID=Reader.m_dwUOrgID;
// 		COPYSTRARRAY(pKey->m_szUID,Reader.m_szUID);
// 		return 1;
// 	}
// 	inline DWORD RecordToKeys(const READER& Reader,ALIAS* pKey,DWORD dwMaxNum)
// 	{	UNREFERENCED_PARAMETER(dwMaxNum);
// 		CLIBASSERT(pKey!=NULL);
// 		if(Reader.m_szAliases[0]=='\0') return 0;
// 		DWORD dwAliasesNum=0;
// 		LPCSTR pszRest=Reader.m_szAliases;
// 		while(pszRest!=NULL)
// 		{	LPSTR pszNext=strchr(pszRest,',');
// 			LONG nLength=(pszNext==NULL)?strlen(pszRest):(pszNext-pszRest);
// 			if(nLength>0)
// 			{	if(dwAliasesNum>=dwMaxNum) return FALSE;
// 				ALIAS* pAlias=&pKey[dwAliasesNum];
// 				if(nLength>=size_of(pAlias->m_szAlias)) return FALSE;
// 				memcpy(pAlias->m_szAlias,pszRest,nLength);
// 				pAlias->m_szAlias[nLength]='\0';
// 				dwAliasesNum++;
// 			}
// 			pszRest=(pszNext==NULL)?pszNext:(pszNext+1);
// 		}
// 		return dwAliasesNum;
// 	}
// 
// 	// 几种索引的HASH
// 	inline UINT static WINAPI GenHashKey(APNODE Key,UINT nKeyOffset) { UNREFERENCED_PARAMETER(nKeyOffset); return HashOfHexString(Key.m_szAPNode,4,8); }
// 	inline UINT static WINAPI GenHashKey(USER Key,UINT nKeyOffset) { UNREFERENCED_PARAMETER(nKeyOffset); return HashOfNumberString(Key.m_szUID,6); }
// 	inline UINT static WINAPI GenHashKey(ALIAS Key,UINT nKeyOffset) { UNREFERENCED_PARAMETER(nKeyOffset); return HashOfNumberString(Key.m_szAlias,6); }
// 
// 	// 几种索引的比较
// 	inline bool static operator==(const APNODE s1,const APNODE s2)
// 	{	if(stricmp(s1.m_szAPNode,s2.m_szAPNode)!=0) return false;
// 		return true;
// 	}
// 	inline bool static operator==(const USER s1,const USER s2)
// 	{	if(s1.m_dwUOrgID!=s2.m_dwUOrgID) return false;
// 		if(stricmp(s1.m_szUID,s2.m_szUID)!=0) return false;
// 		return true;
// 	}
// 	inline bool static operator==(const ALIAS s1,const ALIAS s2)
// 	{	if(stricmp(s1.m_szAlias,s2.m_szAlias)!=0) return false;
// 		return true;
// 	}
// 
// 
// 
// 	static VOID ViewAll(READER* pRecord)
// 	{	CLIBTRACE("%12s | %2d | %12s | %40s | %24s | %25s |\r\n",pRecord->m_szAPNode,pRecord->m_dwUOrgID,pRecord->m_szUID,pRecord->m_szAliases,pRecord->m_szName,pRecord->m_szAP);
// 	}
// 
// 	static BOOL WhereNameEq(READER* pRecord,va_list args)
// 	{	LPCSTR pszName=va_arg(args,LPCSTR);
// 		if(pszName==NULL) return FALSE;
// 		return stricmp(pRecord->m_szName,pszName)==0;
// 	}
// 
// 	static VOID WhereNameEq_Shifter(va_list& args)
// 	{	va_arg(args,LPCSTR);
// 	}
// 
// 
// 
// 
// 
// 	static VOID UpdateName(READER* pRecord,va_list args)
// 	{	LPCSTR pszName=va_arg(args,LPCSTR);
// 		CLIBVERIFY(pszName);
// 		strcpy(pRecord->m_szName,pszName);
// 	}
// 
// 	static VOID InsertOrUpdateName(READER* pRecord,const APNODE* pKey,BOOL bInsert,va_list args)
// 	{
// 		// 键值和索引相关数据(只能在插入的时候处理)
// 		if(bInsert)
// 		{	COPYSTRARRAY(pRecord->m_szAPNode,pKey->m_szAPNode);
// 			pRecord->m_dwUOrgID=1;
// 			COPYSTRARRAY(pRecord->m_szUID,"UID00001234");
// 			COPYSTRARRAY(pRecord->m_szAliases,"MyAlias");
// 		}
// 
// 		// 更新内容
// 		LPCSTR pszAP=va_arg(args,LPCSTR);
// 		LPCSTR pszName=va_arg(args,LPCSTR);
// 		COPYSTRARRAY(pRecord->m_szName,pszName);
// 		COPYSTRARRAY(pRecord->m_szAP,pszAP);
// 	}
// 
// 
// 
// 
// 	LONG TestTable()
// 	{
// 		// 内存表
// 		typedef TMemTable<APNODE,READER,2> READERS;
// 		typedef TIndex<USER,READER,1> IX_USER;
// 		typedef TIndex<ALIAS,READER,64> IX_ALIAS;
// 		const LONG INDEX_IX_USER=0;
// 		const LONG INDEX_IX_ALIAS=1;
// 		READERS tblReaders(1024,65535);
// 		tblReaders.BindIndex(INDEX_IX_USER,IX_USER::Create(1024,65535,TRUE));
// 		tblReaders.BindIndex(INDEX_IX_ALIAS,IX_ALIAS::Create(1024,65535,FALSE));
// 
// 		// 测试插入
// 		{
// 			READER Reader={0};
// 			
// 			COPYSTRARRAY(Reader.m_szAPNode,"00000000000A");
// 			Reader.m_dwUOrgID=1;
// 			COPYSTRARRAY(Reader.m_szUID,"11111111");
// 			COPYSTRARRAY(Reader.m_szAliases,",,1-00123456,,,2-00123456,3-00123456,");
// 			COPYSTRARRAY(Reader.m_szAP,"00000000000A:0000000003E9");
// 			COPYSTRARRAY(Reader.m_szName,"Record1");
// 			CLIBVERIFY(tblReaders.Insert(Reader));
// 
// 			COPYSTRARRAY(Reader.m_szAPNode,"00000000000B");
// 			Reader.m_dwUOrgID=1;
// 			COPYSTRARRAY(Reader.m_szUID,"22222222");
// 			COPYSTRARRAY(Reader.m_szAliases,",,,2-00123456,3-00123456,");
// 			COPYSTRARRAY(Reader.m_szAP,"00000000000B:0000000003E9");
// 			COPYSTRARRAY(Reader.m_szName,"Record2");
// 			CLIBVERIFY(tblReaders.Insert(Reader));
// 		}
// 
// 		// 测试SELECT
// 		{	APNODE APNode={0}; COPYSTRARRAY(APNode.m_szAPNode,"00000000000B");
// 			ALIAS Alias={0}; COPYSTRARRAY(Alias.m_szAlias,"2-00123456");
// 			READER Selected={0};
// 			LONG nSelected=0;
// 			
// 			TList<READER,READER&> lstSelected;
// 			CLIBVERIFY(tblReaders.Select(Selected,APNode));
// 
// 			nSelected=tblReaders.SelectWhere(&lstSelected,32,&WhereNameEq,"Record2");
// 			CLIBVERIFY(nSelected==1);
// 			CLIBVERIFY(lstSelected.GetCount()==1);
// 			lstSelected.RemoveAll();
// 
// 			nSelected=tblReaders.SelectByIndex(&lstSelected,32,INDEX_IX_ALIAS,&Alias,NULL);
// 			CLIBVERIFY(nSelected==2);
// 			CLIBVERIFY(lstSelected.GetCount()==2);
// 			lstSelected.RemoveAll();
// 		}
// 
// 		// 测试SELECTFORUPDATE和COMMITUPDATE
// 		{
// 			APNODE APNode={0}; COPYSTRARRAY(APNode.m_szAPNode,"00000000000B");
// 			ALIAS Alias={0}; COPYSTRARRAY(Alias.m_szAlias,"2-00123456");
// 			READER ReaderVerify={0};
// 			LONG nAffectRecords=0;
// 			TList<READER*,READER*&> lstForUpdate;
// 
// 			READER* pForUpdate=tblReaders.SelectForUpdate(APNode);
// 			CLIBVERIFY(pForUpdate!=NULL);
// 			strcpy(pForUpdate->m_szName,"SelectForUpdate");
// 			CLIBVERIFY(tblReaders.CommitUpdate(pForUpdate));
// 			CLIBVERIFY(tblReaders.Select(ReaderVerify,APNode));
// 			CLIBVERIFY(stricmp(ReaderVerify.m_szName,"SelectForUpdate")==0);
// 
// 			nAffectRecords=tblReaders.SelectForUpdateWhere(&lstForUpdate,32,&WhereNameEq,"SelectForUpdate");
// 			CLIBVERIFY(nAffectRecords==1);
// 			while(!lstForUpdate.IsEmpty())
// 			{	READER* pForUpdate=lstForUpdate.RemoveHead();
// 				strcpy(pForUpdate->m_szName,"SelectForUpdateWhere");
// 				CLIBVERIFY(tblReaders.CommitUpdate(pForUpdate));
// 			}
// 			CLIBVERIFY(tblReaders.Select(ReaderVerify,APNode));
// 			CLIBVERIFY(stricmp(ReaderVerify.m_szName,"SelectForUpdateWhere")==0);
// 
// 			nAffectRecords=tblReaders.SelectForUpdateByIndex(&lstForUpdate,32,INDEX_IX_ALIAS,&Alias,NULL);
// 			CLIBVERIFY(nAffectRecords==2);
// 			POSITION posForUpdate=lstForUpdate.GetHeadPosition();
// 			while(posForUpdate!=NULL)
// 			{	READER* pForUpdate=lstForUpdate.GetNext(posForUpdate);
// 				strcpy(pForUpdate->m_szName,"SelectForUpdateByIndex");
// 			}
// 			CLIBVERIFY(tblReaders.BatchCommitUpdate(&lstForUpdate));
// 			CLIBVERIFY(tblReaders.Select(ReaderVerify,APNode));
// 			CLIBVERIFY(stricmp(ReaderVerify.m_szName,"SelectForUpdateByIndex")==0);
// 		}
// 
// 		// 测试直接更新
// 		{
// 			APNODE APNode={0}; COPYSTRARRAY(APNode.m_szAPNode,"00000000000B");
// 			ALIAS Alias={0}; COPYSTRARRAY(Alias.m_szAlias,"2-00123456");
// 			READER ReaderVerify={0};
// 			LONG nAffectRecords=0;
// 			TList<READER,READER&> lstAffect;
// 
// 			CLIBVERIFY(tblReaders.Update(NULL,APNode,UpdateName,"Update"));
// 			CLIBVERIFY(tblReaders.Select(ReaderVerify,APNode));
// 			CLIBVERIFY(stricmp(ReaderVerify.m_szName,"Update")==0);
// 
// 			nAffectRecords=tblReaders.UpdateWhere(&lstAffect,32,&WhereNameEq,&WhereNameEq_Shifter,&UpdateName,"Update","UpdateWhere");
// 			CLIBVERIFY(nAffectRecords==1);
// 			tblReaders.Select(ReaderVerify,APNode);
// 			CLIBVERIFY(stricmp(ReaderVerify.m_szName,"UpdateWhere")==0);
// 
// 			nAffectRecords=tblReaders.UpdateByIndex(&lstAffect,32,INDEX_IX_ALIAS,&Alias,&WhereNameEq,&WhereNameEq_Shifter,&UpdateName,"UpdateWhere","UpdateByIndex");
// 			CLIBVERIFY(nAffectRecords==1);
// 			tblReaders.Select(ReaderVerify,APNode);
// 			CLIBVERIFY(stricmp(ReaderVerify.m_szName,"UpdateByIndex")==0);
// 		}
// 
// 		// 测试插入或更新
// 		{
// 			APNODE APNode={0}; COPYSTRARRAY(APNode.m_szAPNode,"00000000000C");
// 			READER AffectRecord={0};
// 
// 			// 插入一条新记录
// 			CLIBVERIFY(tblReaders.InsertOrUpdate(&AffectRecord,APNode,InsertOrUpdateName,"AP.1","InsertOrUpdate.1"));
// 
// 			// 更新其数据
// 			READER* pForUpdate=tblReaders.SelectForUpdate(APNode);
// 			CLIBVERIFY(pForUpdate!=NULL);
// 			strcpy(pForUpdate->m_szAP,"SelectForUpdate");
// 			strcpy(pForUpdate->m_szName,"SelectForUpdate");
// 			CLIBVERIFY(tblReaders.CommitUpdate(pForUpdate));
// 
// 			// 更新这条记录
// 			CLIBVERIFY(tblReaders.InsertOrUpdate(&AffectRecord,APNode,InsertOrUpdateName,"AP.2","InsertOrUpdate.2"));
// 
// 			// 更新记录通过
// 			CLIBVERIFY(tblReaders.InsertOrUpdateWhere(&AffectRecord,WhereNameEq,WhereNameEq_Shifter,InsertOrUpdateName,"InsertOrUpdate.2","NewAP","InsertOrUpdate.3"));
// 		}
// 
// 		
// 		// 性能测试和多版本控制
// 		{
// 			READER Reader={0};
// 			COPYSTRARRAY(Reader.m_szAPNode,"00000000000D");
// 			Reader.m_dwUOrgID=1;
// 			COPYSTRARRAY(Reader.m_szUID,"33333333");
// 			COPYSTRARRAY(Reader.m_szAliases,",,1-00123456,,,2-00123456,3-00123456,");
// 			COPYSTRARRAY(Reader.m_szAP,"00000000000A:0000000003E9");
// 			COPYSTRARRAY(Reader.m_szName,"Record4");
// 			CLIBVERIFY(tblReaders.Insert(Reader));
// 
// 			systm_t tBegin=systm();
// 			APNODE APNode={0}; COPYSTRARRAY(APNode.m_szAPNode,"00000000000D");
// 			ALIAS Alias={0}; COPYSTRARRAY(Alias.m_szAlias,"2-00123456");
// 			READER ReaderVerify={0};
// 			CLIBVERIFY(tblReaders.Select(ReaderVerify,APNode));
// 			CLIBVERIFY(stricmp(ReaderVerify.m_szName,"Record4")==0);
// 			for(LONG i=0; i<32*10000; i++)
// 			{
// 				READER* pReader1=tblReaders.SelectForUpdate(APNode);
// 				CLIBVERIFY(pReader1!=NULL);
// 				strcpy(pReader1->m_szName,"RECORD-UPDATE-1");
// 
// 				READER* pReader2=tblReaders.SelectForUpdate(APNode);
// 				CLIBVERIFY(pReader2!=NULL);
// 				strcpy(pReader2->m_szName,"RECORD-UPDATE-2");
// 
// 				CLIBVERIFY(tblReaders.CommitUpdate(pReader2,FALSE));
// 				CLIBVERIFY(tblReaders.Select(ReaderVerify,APNode));
// 				CLIBVERIFY(stricmp(ReaderVerify.m_szName,"RECORD-UPDATE-2")==0);
// 
// 				CLIBVERIFY(!tblReaders.CommitUpdate(pReader1,FALSE));
// 				CLIBVERIFY(tblReaders.Select(ReaderVerify,APNode));
// 				CLIBVERIFY(stricmp(ReaderVerify.m_szName,"RECORD-UPDATE-2")==0);
// 			}
// 			systm_t tDelay=systm()-tBegin;
// 			TRACE("DELAY:%I64d,PERSECOND=%I64dW/S\r\n",tDelay,(INT64)(32*10000/tDelay)*1000/10000);
// 		}
// 
// 		tblReaders.List(-1,ViewAll);
// 
// 		// 测试删除
// 		{	APNODE APNode={0}; COPYSTRARRAY(APNode.m_szAPNode,"00000000000B");
// 			ALIAS Alias={0}; COPYSTRARRAY(Alias.m_szAlias,"2-00123456");
// 			READER ReaderVerify={0};
// 			LONG nAffectRecords=0;
// 			TList<READER,READER&> lstAffect;
// 
// 			CLIBVERIFY(tblReaders.Delete(NULL,APNode));
// 			CLIBVERIFY(!tblReaders.Select(ReaderVerify,APNode));
// 
// 			nAffectRecords=tblReaders.DeleteWhere(&lstAffect,32,&WhereNameEq,"UpdateByIndex");
// 			CLIBVERIFY(nAffectRecords==0||nAffectRecords==2);
// 			CLIBVERIFY(!tblReaders.Select(ReaderVerify,APNode));
// 
// 			nAffectRecords=tblReaders.DeleteByIndex(&lstAffect,32,INDEX_IX_ALIAS,&Alias,NULL);
// 			CLIBVERIFY(nAffectRecords==0||nAffectRecords==2);
// 			CLIBVERIFY(!tblReaders.Select(ReaderVerify,APNode));
// 		}
// 
// 		return 0;
// 	}
// 
// 	LONG TestTableNoList()
// 	{
// 		// 内存表
// 		typedef TMemTable<APNODE,READER,2> READERS;
// 		typedef TIndex<USER,READER,1> IX_USER;
// 		typedef TIndex<ALIAS,READER,64> IX_ALIAS;
// 		const LONG INDEX_IX_USER=0;
// 		const LONG INDEX_IX_ALIAS=1;
// 		READERS tblReaders(1024,65535);
// 		tblReaders.BindIndex(INDEX_IX_USER,IX_USER::Create(1024,65535,TRUE));
// 		tblReaders.BindIndex(INDEX_IX_ALIAS,IX_ALIAS::Create(1024,65535,FALSE));
// 
// 		// 测试插入
// 		{
// 			READER Reader={0};
// 			
// 			COPYSTRARRAY(Reader.m_szAPNode,"00000000000A");
// 			Reader.m_dwUOrgID=1;
// 			COPYSTRARRAY(Reader.m_szUID,"11111111");
// 			COPYSTRARRAY(Reader.m_szAliases,",,1-00123456,,,2-00123456,3-00123456,");
// 			COPYSTRARRAY(Reader.m_szAP,"00000000000A:0000000003E9");
// 			COPYSTRARRAY(Reader.m_szName,"Record1");
// 			CLIBVERIFY(tblReaders.Insert(Reader));
// 
// 			COPYSTRARRAY(Reader.m_szAPNode,"00000000000B");
// 			Reader.m_dwUOrgID=1;
// 			COPYSTRARRAY(Reader.m_szUID,"22222222");
// 			COPYSTRARRAY(Reader.m_szAliases,",,,2-00123456,3-00123456,");
// 			COPYSTRARRAY(Reader.m_szAP,"00000000000B:0000000003E9");
// 			COPYSTRARRAY(Reader.m_szName,"Record2");
// 			CLIBVERIFY(tblReaders.Insert(Reader));
// 		}
// 
// 		// 测试SELECT
// 		{	APNODE APNode={0}; COPYSTRARRAY(APNode.m_szAPNode,"00000000000B");
// 			ALIAS Alias={0}; COPYSTRARRAY(Alias.m_szAlias,"2-00123456");
// 			READER Selected={0};
// 			LONG nSelected=0;
// 			
// 			READER aSelected[32]={0};
// 			CLIBVERIFY(tblReaders.Select(Selected,APNode));
// 
// 			nSelected=tblReaders.SelectWhereEx(aSelected,ARRAYSIZE(aSelected),32,&WhereNameEq,"Record2");
// 			CLIBVERIFY(nSelected==1);
// 
// 			nSelected=tblReaders.SelectByIndexEx(aSelected,ARRAYSIZE(aSelected),32,INDEX_IX_ALIAS,&Alias,NULL);
// 			CLIBVERIFY(nSelected==2);
// 		}
// 
// 		// 测试SELECTFORUPDATE和COMMITUPDATE
// 		{
// 			APNODE APNode={0}; COPYSTRARRAY(APNode.m_szAPNode,"00000000000B");
// 			ALIAS Alias={0}; COPYSTRARRAY(Alias.m_szAlias,"2-00123456");
// 			READER ReaderVerify={0};
// 			LONG nAffectRecords=0,nEnum=0;
// 			READER* apForUpdates[256]={0};
// 
// 			READER* pForUpdate=tblReaders.SelectForUpdate(APNode);
// 			CLIBVERIFY(pForUpdate!=NULL);
// 			strcpy(pForUpdate->m_szName,"SelectForUpdate");
// 			CLIBVERIFY(tblReaders.CommitUpdate(pForUpdate));
// 			CLIBVERIFY(tblReaders.Select(ReaderVerify,APNode));
// 			CLIBVERIFY(stricmp(ReaderVerify.m_szName,"SelectForUpdate")==0);
// 
// 			nAffectRecords=tblReaders.SelectForUpdateWhereEx(apForUpdates,ARRAYSIZE(apForUpdates),32,&WhereNameEq,"SelectForUpdate");
// 			CLIBVERIFY(nAffectRecords==1);
// 			for(nEnum=0; nEnum<nAffectRecords; nEnum++)
// 			{	READER* pForUpdate=apForUpdates[nEnum];
// 				strcpy(pForUpdate->m_szName,"SelectForUpdateWhere");
// 				CLIBVERIFY(tblReaders.CommitUpdate(pForUpdate));
// 			}
// 			CLIBVERIFY(tblReaders.Select(ReaderVerify,APNode));
// 			CLIBVERIFY(stricmp(ReaderVerify.m_szName,"SelectForUpdateWhere")==0);
// 
// 			nAffectRecords=tblReaders.SelectForUpdateByIndexEx(apForUpdates,ARRAYSIZE(apForUpdates),32,INDEX_IX_ALIAS,&Alias,NULL);
// 			CLIBVERIFY(nAffectRecords==2);
// 			for(nEnum=0; nEnum<nAffectRecords; nEnum++)
// 			{	READER* pForUpdate=apForUpdates[nEnum];
// 				strcpy(pForUpdate->m_szName,"SelectForUpdateByIndex");
// 			}
// 			CLIBVERIFY(tblReaders.BatchCommitUpdateEx(apForUpdates,nAffectRecords));
// 			CLIBVERIFY(tblReaders.Select(ReaderVerify,APNode));
// 			CLIBVERIFY(stricmp(ReaderVerify.m_szName,"SelectForUpdateByIndex")==0);
// 		}
// 
// 		// 测试直接更新
// 		{
// 			APNODE APNode={0}; COPYSTRARRAY(APNode.m_szAPNode,"00000000000B");
// 			ALIAS Alias={0}; COPYSTRARRAY(Alias.m_szAlias,"2-00123456");
// 			READER ReaderVerify={0};
// 			LONG nAffectRecords=0;
// 			READER aAffect[256]={0};
// 
// 			CLIBVERIFY(tblReaders.Update(NULL,APNode,UpdateName,"Update"));
// 			CLIBVERIFY(tblReaders.Select(ReaderVerify,APNode));
// 			CLIBVERIFY(stricmp(ReaderVerify.m_szName,"Update")==0);
// 
// 			nAffectRecords=tblReaders.UpdateWhereEx(aAffect,ARRAYSIZE(aAffect),32,&WhereNameEq,&WhereNameEq_Shifter,&UpdateName,"Update","UpdateWhere");
// 			CLIBVERIFY(nAffectRecords==1);
// 			tblReaders.Select(ReaderVerify,APNode);
// 			CLIBVERIFY(stricmp(ReaderVerify.m_szName,"UpdateWhere")==0);
// 
// 			nAffectRecords=tblReaders.UpdateByIndexEx(aAffect,ARRAYSIZE(aAffect),32,INDEX_IX_ALIAS,&Alias,&WhereNameEq,&WhereNameEq_Shifter,&UpdateName,"UpdateWhere","UpdateByIndex");
// 			CLIBVERIFY(nAffectRecords==1);
// 			tblReaders.Select(ReaderVerify,APNode);
// 			CLIBVERIFY(stricmp(ReaderVerify.m_szName,"UpdateByIndex")==0);
// 		}
// 
// 		// 测试插入或更新
// 		{
// 			APNODE APNode={0}; COPYSTRARRAY(APNode.m_szAPNode,"00000000000C");
// 			READER AffectRecord={0};
// 
// 			// 插入一条新记录
// 			CLIBVERIFY(tblReaders.InsertOrUpdate(&AffectRecord,APNode,InsertOrUpdateName,"AP.1","InsertOrUpdate.1"));
// 
// 			// 更新其数据
// 			READER* pForUpdate=tblReaders.SelectForUpdate(APNode);
// 			CLIBVERIFY(pForUpdate!=NULL);
// 			strcpy(pForUpdate->m_szAP,"SelectForUpdate");
// 			strcpy(pForUpdate->m_szName,"SelectForUpdate");
// 			CLIBVERIFY(tblReaders.CommitUpdate(pForUpdate));
// 
// 			// 更新这条记录
// 			CLIBVERIFY(tblReaders.InsertOrUpdate(&AffectRecord,APNode,InsertOrUpdateName,"AP.2","InsertOrUpdate.2"));
// 
// 			// 更新记录通过
// 			CLIBVERIFY(tblReaders.InsertOrUpdateWhere(&AffectRecord,WhereNameEq,WhereNameEq_Shifter,InsertOrUpdateName,"InsertOrUpdate.2","NewAP","InsertOrUpdate.3"));
// 		}
// 
// 		
// 		// 性能测试和多版本控制
// 		{
// 			READER Reader={0};
// 			COPYSTRARRAY(Reader.m_szAPNode,"00000000000D");
// 			Reader.m_dwUOrgID=1;
// 			COPYSTRARRAY(Reader.m_szUID,"33333333");
// 			COPYSTRARRAY(Reader.m_szAliases,",,1-00123456,,,2-00123456,3-00123456,");
// 			COPYSTRARRAY(Reader.m_szAP,"00000000000A:0000000003E9");
// 			COPYSTRARRAY(Reader.m_szName,"Record4");
// 			CLIBVERIFY(tblReaders.Insert(Reader));
// 
// 			systm_t tBegin=systm();
// 			APNODE APNode={0}; COPYSTRARRAY(APNode.m_szAPNode,"00000000000D");
// 			ALIAS Alias={0}; COPYSTRARRAY(Alias.m_szAlias,"2-00123456");
// 			READER ReaderVerify={0};
// 			CLIBVERIFY(tblReaders.Select(ReaderVerify,APNode));
// 			CLIBVERIFY(stricmp(ReaderVerify.m_szName,"Record4")==0);
// 			for(LONG i=0; i<32*10000; i++)
// 			{
// 				READER* pReader1=tblReaders.SelectForUpdate(APNode);
// 				CLIBVERIFY(pReader1!=NULL);
// 				strcpy(pReader1->m_szName,"RECORD-UPDATE-1");
// 
// 				READER* pReader2=tblReaders.SelectForUpdate(APNode);
// 				CLIBVERIFY(pReader2!=NULL);
// 				strcpy(pReader2->m_szName,"RECORD-UPDATE-2");
// 
// 				CLIBVERIFY(tblReaders.CommitUpdate(pReader2,FALSE));
// 				CLIBVERIFY(tblReaders.Select(ReaderVerify,APNode));
// 				CLIBVERIFY(stricmp(ReaderVerify.m_szName,"RECORD-UPDATE-2")==0);
// 
// 				CLIBVERIFY(!tblReaders.CommitUpdate(pReader1,FALSE));
// 				CLIBVERIFY(tblReaders.Select(ReaderVerify,APNode));
// 				CLIBVERIFY(stricmp(ReaderVerify.m_szName,"RECORD-UPDATE-2")==0);
// 			}
// 			systm_t tDelay=systm()-tBegin;
// 			TRACE("DELAY:%I64d,PERSECOND=%I64dW/S\r\n",tDelay,(INT64)(32*10000/tDelay)*1000/10000);
// 		}
// 
// 		tblReaders.List(-1,ViewAll);
// 
// 		// 测试删除
// 		{	APNODE APNode={0}; COPYSTRARRAY(APNode.m_szAPNode,"00000000000B");
// 			ALIAS Alias={0}; COPYSTRARRAY(Alias.m_szAlias,"2-00123456");
// 			READER ReaderVerify={0};
// 			LONG nAffectRecords=0;
// 			READER aAffect[256]={0};
// 
// 			CLIBVERIFY(tblReaders.Delete(NULL,APNode));
// 			CLIBVERIFY(!tblReaders.Select(ReaderVerify,APNode));
// 
// 			nAffectRecords=tblReaders.DeleteWhereEx(aAffect,ARRAYSIZE(aAffect),32,&WhereNameEq,"UpdateByIndex");
// 			CLIBVERIFY(nAffectRecords==0||nAffectRecords==2);
// 			CLIBVERIFY(!tblReaders.Select(ReaderVerify,APNode));
// 
// 			nAffectRecords=tblReaders.DeleteByIndexEx(aAffect,ARRAYSIZE(aAffect),32,INDEX_IX_ALIAS,&Alias,NULL);
// 			CLIBVERIFY(nAffectRecords==0||nAffectRecords==2);
// 			CLIBVERIFY(!tblReaders.Select(ReaderVerify,APNode));
// 		}
// 
// 		return 0;
// 	}
// 
// 	LONG nResult=TestTable();
// 	LONG nResultNoList=TestTableNoList();
