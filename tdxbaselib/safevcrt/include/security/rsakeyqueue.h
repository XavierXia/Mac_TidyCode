#ifndef __RSA_KEY_QUEUE__H__
#define __RSA_KEY_QUEUE__H__
#if _MSC_VER > 1000
#pragma once
#endif
#include "tpki.h"

// RSA√‹‘ø∂”¡–
class SECURITY_IMP CRsaKeyQueue  
{
public:
	CRsaKeyQueue();
	virtual~CRsaKeyQueue();
	BOOL DequeueIntelligent(R_RSA_PUBLIC_KEY& PubKey,R_RSA_PRIVATE_KEY& PriKey,BYTE cRsaBitIdx);
	BOOL GenerateAndEnqueue(BYTE cRsaBitIdx);
	LONG GetTotalNum();
protected:
	BOOL Enqueue(R_RSA_PUBLIC_KEY* pPubKey,R_RSA_PRIVATE_KEY* pPriKey);
	BOOL Dequeue(R_RSA_PUBLIC_KEY& PubKey,R_RSA_PRIVATE_KEY& PriKey);
protected:
	typedef struct tagKEYLISTITEM
	{	R_RSA_PUBLIC_KEY m_PubKey;
		R_RSA_PRIVATE_KEY m_PriKey;
		struct tagKEYLISTITEM* m_pNextNode;
	} KEYLISTITEM,*LPKEYLISTITEM;
protected:
	LPKEYLISTITEM m_pHeadNode;
	CRITICAL_SECTION m_Lock;
	LONG m_nTotalNum;
};

#endif
