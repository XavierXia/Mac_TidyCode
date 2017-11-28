#ifndef __MLANG__H__
#define __MLANG__H__

// 语言包管理器
class MLANG_IMP CMLangMngr
{
public:
	CMLangMngr();
	virtual~CMLangMngr();
	VOID Initialize(HINSTANCE hInst,LPCSTR pszResName,LONG nBufSize);
	VOID SetLangPackInst(HINSTANCE hLangPackInst);
	VOID SetLangPackFile(LPCTSTR pszLangPackFile);
	HINSTANCE GetLangPackInst();
	LPCSTR LoadString(WORD wID);
	LPCSTR LoadText(WORD wID,LPSTR pszBuf,LONG cbBuf);
protected:
	HINSTANCE	m_hInst;
	TCHAR		m_szResName[MAX_PATH];
	HINSTANCE	m_hLangPackInst;
	TCHAR		m_szLangPackModule[MAX_PATH];
	HMODULE		m_hLangPackModule;
	LPVOID		m_pMap;
	LPSTR		m_pBuf;
	LONG		m_nBufSize;
	LONG		m_nBufUsed;
};

// 语言包管理相关函数
#ifdef PLATFORM_WINDOWS
	#pragma comment(lib,"version.lib")
#endif



// 语言包管理函数
MLANG_IMP VOID _mlangInitializeStatic(CMLangMngr* pMngr,HINSTANCE hInst,LPCSTR pszResName,LONG nBufSize=10*1024);
MLANG_IMP VOID _mlangInitializeDynamic(CMLangMngr* pPrevMngr,CMLangMngr* pMngr,HINSTANCE hInst,LPCSTR pszResName,LONG nBufSize=10*1024);
MLANG_IMP VOID _mlangSetLangPackInst(CMLangMngr* pMngr,HINSTANCE hLangPackInst);
MLANG_IMP VOID _mlangSetLangPackFile(CMLangMngr* pMngr,LPCTSTR pszLangPackFile);
MLANG_IMP HINSTANCE _mlangGetLangPackInst(CMLangMngr* pMngr);
MLANG_IMP LPCSTR _mlangSTR(CMLangMngr* pMngr,WORD wID);
MLANG_IMP LPCSTR _mlangTXT(CMLangMngr* pMngr,WORD wID,LPSTR pszBuf,LONG cbBuf);

#if !defined(SAFEVCRT_DYNAMIC)
	#define mlangSetMngr(pMngr,hInst)							_mlangInitializeStatic(pMngr,hInst,"noname")
	#define mlangSetMngrEx(pMngr,hInst,pszResName)				_mlangInitializeStatic(pMngr,hInst,pszResName)
	#define mlangSetLangPackInst(hLangPackInst)					_mlangSetLangPackInst(NULL,hLangPackInst)
	#define mlangSetLangPackFile(pszLangPackFile)				_mlangSetLangPackFile(NULL,pszLangPackFile)
	#define mlangGetLangPackInst()								_mlangGetLangPackInst(NULL)
	#define MLANGSTR(wID)										_mlangSTR(NULL,wID)
	#define MLANGTXT(wID,pszBuf,cbBuf)							_mlangTXT(NULL,wID,pszBuf,cbBuf)
	#define DECLARE_MLANG_MNGR()								
#else
	extern CMLangMngr* g_pMngr;
	#define mlangSetMngrEx(pMngr,hInst,pszResName)				_mlangInitializeDynamic(g_pMngr,pMngr,hInst,pszResName); g_pMngr=pMngr;
	#define mlangSetLangPackInst(hLangPackInst)					_mlangSetLangPackInst(g_pMngr,hLangPackInst)
	#define mlangSetLangPackFile(pszLangPackFile)				_mlangSetLangPackFile(g_pMngr,pszLangPackFile)
	#define mlangGetLangPackInst()								_mlangGetLangPackInst(g_pMngr)
	#define MLANGSTR(wID)										_mlangSTR(g_pMngr,wID)
	#define MLANGTXT(wID,pszBuf,cbBuf)							_mlangTXT(g_pMngr,wID,pszBuf,cbBuf)
	#define DECLARE_MLANG_MNGR()								CMLangMngr* g_pMngr=NULL;
#endif


// 目前支持的语言定义
#ifndef LANG_ENGLISH
	#define LANG_ENGLISH                     0x09
	#define LANG_CHINESE                     0x04
	#define SUBLANG_ENGLISH_US               0x01    // English (USA)
	#define SUBLANG_CHINESE_SIMPLIFIED       0x02    // Chinese (PR China)
	#define SUBLANG_CHINESE_TRADITIONAL      0x01    // Chinese (Taiwan)
#endif

// 语言和代码页的转换处理
MLANG_IMP LPCSTR LangId2ShortName(WORD wLangId,LPSTR pszPostfix,LONG cbPostfix);
MLANG_IMP UINT LangId2CodePage(WORD wLangId);
MLANG_IMP WORD LangId2CompatibleLangId(WORD wLangId);
	


#endif // THIS_FILE
