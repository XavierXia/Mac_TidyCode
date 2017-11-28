#ifndef __PERF_CHECK__H__
#define __PERF_CHECK__H__
#if _MSC_VER > 1000
#pragma once
#endif

class CLIBMISC_IMP CPerfCheck
{
public:
	CPerfCheck();
	virtual~CPerfCheck();
	VOID Mark(LPCSTR lpszTitle);
protected:
	DWORD m_dwLastCheck;
};

class CLIBMISC_IMP CNeckCheck
{
public:
	CNeckCheck(LPCSTR pszTitle,...);
	virtual~CNeckCheck();
	VOID BreakPoint(LONG nSeqNo);
protected:
	static systm_t m_tAppStart;
	static systm_t m_tLastCheck;
	static LONG m_nLevel;
	static LONG m_nLastSeqNo;
	CHAR	m_szTitle[MAX_PATH];
	systm_t m_tEntry;
	LONG    m_nSeqNo;
};

#endif
