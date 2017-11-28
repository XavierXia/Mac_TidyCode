#ifndef __SHARE_CONF__H__
#define __SHARE_CONF__H__
#ifdef __cplusplus
extern "C"
{
#endif

typedef void* HINICONF;
LITEINI_IMP HINICONF LoadIniConfAnyFile(CAnyFile* pIniConfFile,BOOL bForceOpen);
LITEINI_IMP HINICONF LoadIniConf(char* lpszIniConf,BOOL bForceOpen);
LITEINI_IMP void  StoreIniConfAnyFile(HINICONF hIniConf,CAnyFile* pIniConfFile,BOOL bUnixFormat);
LITEINI_IMP void  StoreIniConf(HINICONF hIniConf,char* lpszIniConf,BOOL bUnixFormat);


LITEINI_IMP void  CloseIniConf(HINICONF hIniConf);
// 查找INI的组标记,从头开始查找,nIndex=-1,返回当前组的文本行序号
//	int nIndex=-1;
//	char* lpszGroupName=FindIniConfGroup(hIniConf,nIndex);
//	while(nIndex!=-1)
//	{	TRACE("%s\n",lpszGroupName);
//		lpszGroupName=FindIniConfGroup(hIniConf,nIndex);
//	}
LITEINI_IMP char* FindIniConfGroup(HINICONF hIniConf,int& nFrom);
// 查找INI的字段标记,从头开始查找,nIndex=-1,返回当前组的文本行序号
//	int nIndex=-1;
//	char* lpszKeyName=FindIniConfKey(hIniConf,"[AAAA]",nIndex);
//	while(nIndex!=-1)
//	{	TRACE("%s\n",lpszKeyName);
//		lpszKeyName=FindIniConfKey(hIniConf,"[AAAA]",nIndex);
//	}
LITEINI_IMP char* FindIniConfKey(HINICONF hIniConf,char* lpszGroup,int& nIndex);
LITEINI_IMP int   ReadIniConfString(HINICONF hIniConf,char* lpszGroup,char* lpKey,char* lpValue,int nMaxLen);
LITEINI_IMP int   WriteIniConfString(HINICONF hIniConf,const char* lpszGroup,const char* lpKey,const char* lpValue);
LITEINI_IMP void  RemoveIniConfGroup(HINICONF hIniConf,int nIndex);
LITEINI_IMP void  RemoveIniConfGroupByName(HINICONF hIniConf,char* lpszGroupName);



//////////////////////////////////////////////////////////////////////////
// 经过封装的API
LITEINI_IMP VOID GetIniConfString(HINICONF hIniConf,char* lpszGroup,char* lpKey,char* lpValue,int nMaxLen,const char* lpszDef);
LITEINI_IMP LONG GetIniConfLong(HINICONF hIniConf,char* lpszGroup,char* lpKey,LONG nDef);
LITEINI_IMP BOOL GetIniConfBool(HINICONF hIniConf,char* lpszGroup,char* lpKey,BOOL bDef);
LITEINI_IMP BYTE GetIniConfByte(HINICONF hIniConf,char* lpszGroup,char* lpKey,BYTE ucDef);
LITEINI_IMP FLAG GetIniConfFlag(HINICONF hIniConf,char* lpszGroup,char* lpKey,FLAG cDef);
LITEINI_IMP WORD GetIniConfWord(HINICONF hIniConf,char* lpszGroup,char* lpKey,WORD wDef);

LITEINI_IMP VOID SetIniConfString(HINICONF hIniConf,char* lpszGroup,char* lpKey,char* lpValue);
LITEINI_IMP VOID SetIniConfLong(HINICONF hIniConf,char* lpszGroup,char* lpKey,LONG nValue);
LITEINI_IMP VOID SetIniConfBool(HINICONF hIniConf,char* lpszGroup,char* lpKey,BOOL bValue);
LITEINI_IMP VOID SetIniConfByte(HINICONF hIniConf,char* lpszGroup,char* lpKey,BYTE ucValue);
LITEINI_IMP VOID SetIniConfFlag(HINICONF hIniConf,char* lpszGroup,char* lpKey,FLAG cValue);
LITEINI_IMP VOID SetIniConfWord(HINICONF hIniConf,char* lpszGroup,char* lpKey,WORD wValue);




typedef void* HTXTCONF;
LITEINI_IMP HTXTCONF LoadTxtConfAnyFile(CAnyFile* pTxtConfFile,BOOL bForceOpen);
LITEINI_IMP HTXTCONF LoadTxtConf(char* lpszTxtConf,BOOL bForceOpen);
LITEINI_IMP void  StoreTxtConfAnyFile(HTXTCONF hTxtConf,CAnyFile* pTxtConfFile,BOOL bUnixFormat);
LITEINI_IMP void  StoreTxtConf(HTXTCONF hTxtConf,char* lpszTxtConf,BOOL bUnixFormat);
LITEINI_IMP void  CloseTxtConf(HTXTCONF hTxtConf);
LITEINI_IMP int   ReadTxtConfString(HTXTCONF hTxtConf,char* lpKey,char* lpValue,int nMaxLen);
LITEINI_IMP int   WriteTxtConfString(HTXTCONF hTxtConf,char* lpKey,char* lpValue);
LITEINI_IMP int   RemoveTxtConfString(HTXTCONF hTxtConf,char* lpKey);


LITEINI_IMP int   IsSubKey(char* lpKey,char* lpKeys,char cSplitter);



#ifdef __cplusplus
}
#endif

#endif
