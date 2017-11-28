//////////////////////////////////////////////////////////////////////////
// ��ֵ������
#ifndef __SAMPLING__H__
#define __SAMPLING__H__
#if _MSC_VER > 1000
#pragma once
#endif



// ѭ��������(�������һ����Ŀ�Ĳ���������)
class COLLECTION_IMP CSampling
{
public:
	CSampling(LONG nSamplingNum);
	virtual~CSampling();
	VOID AddSampling(DWORD dwSampling);
	VOID NextPeriod();
	BOOL GetNowValue(DWORD& dwSampling,DWORD& dwHit);
	BOOL GetLastValue(DWORD& dwSampling,DWORD& dwHit);
	BOOL GetNearValue(DWORD& dwSampling,DWORD& dwHit);
	LONG GetValidNum() { return m_nValidNum; }
protected:
	LONG		m_nSamplingNum;		// ��������
	LONG		m_nCurrNo;			// ��ǰͳ��λ��
	LONG		m_nValidNum;		// ��Ч���ݸ���
	TArrayDword	m_aSamplings;		// ��������ֵ
	TArrayDword	m_aHits;			// �ۼ�ֵ�ϲ���
};








// ��������ָʾ��
template<INT RECENTMAX,class TYPE>
class CMAIndicator
{
public:
	CMAIndicator()
		{	memset(m_aRecents,0,size_of(m_aRecents));
			m_RecentsSum=0;
			m_dwRecentNum=0;
		}
	~CMAIndicator()
		{
		}
	// ׷�Ӳ�������
	VOID Hit(DWORD dwValue)
		{	// ������������
			if(m_dwRecentNum<RECENTMAX)
			{	m_RecentsSum+=dwValue;
				m_aRecents[m_dwRecentNum]=dwValue;
				m_dwRecentNum++;
			}
			// ����������
			else
			{	m_RecentsSum-=m_aRecents[m_dwRecentNum%RECENTMAX];
				m_RecentsSum+=dwValue;
				m_aRecents[m_dwRecentNum%RECENTMAX]=dwValue;
				m_dwRecentNum=(m_dwRecentNum+1)%RECENTMAX+RECENTMAX;
			}
		}
	// �������ֵ
	LONG CalcAvgl() { return (m_dwRecentNum==0)?0:(LONG)m_RecentsSum/min_of(RECENTMAX,m_dwRecentNum); }
	FLOAT CalcAvgf() { return (m_dwRecentNum==0)?0:(FLOAT)m_RecentsSum/min_of(RECENTMAX,m_dwRecentNum); }
	DOUBLE CalcAvgd() { return (m_dwRecentNum==0)?0:(DOUBLE)m_RecentsSum/min_of(RECENTMAX,m_dwRecentNum); }
protected:
	TYPE m_aRecents[RECENTMAX];
	TYPE m_RecentsSum;
	DWORD m_dwRecentNum;
};





// ָʾ������
typedef enum enumINDICTYPE
{	INDIC_LV,
	INDIC_FLOW,
	INDIC_STAT,
} INDICTYPE;




// ����ָʾ��(ˮƽ)
class COLLECTION_IMP CLvIndicator
{
public:
	CLvIndicator()
		{	m_dwCurrent=0;
			m_dwTop=0;
			m_dwGrandTotal=0;
			m_dwGrandTotalInPreSec=0;
			m_dwFlowInPreSec=0;
			m_dwTopFlowInPreSec=0;
		}
	CLvIndicator(const CLvIndicator& Indicator)
		{	m_dwCurrent=Indicator.m_dwCurrent;
			m_dwTop=Indicator.m_dwTop;
			m_dwGrandTotal=Indicator.m_dwGrandTotal;
			m_dwGrandTotalInPreSec=Indicator.m_dwGrandTotalInPreSec;
			m_dwFlowInPreSec=Indicator.m_dwFlowInPreSec;
			m_dwTopFlowInPreSec=Indicator.m_dwTopFlowInPreSec;
		}
	~CLvIndicator()
		{
		}
	const CLvIndicator& operator=(const CLvIndicator& Indicator)
		{	m_dwCurrent=Indicator.m_dwCurrent;
			m_dwTop=Indicator.m_dwTop;
			m_dwGrandTotal=Indicator.m_dwGrandTotal;
			m_dwGrandTotalInPreSec=Indicator.m_dwGrandTotalInPreSec;
			m_dwFlowInPreSec=Indicator.m_dwFlowInPreSec;
			m_dwTopFlowInPreSec=Indicator.m_dwTopFlowInPreSec;
			return (*this);
		}
	LONG Count()
		{	return InterlockedExchangeAdd((LPLONG)&m_dwCurrent,0);
		}
	VOID Increment()
		{	DWORD dwCurrent=InterlockedIncrement((LPLONG)&m_dwCurrent);
			InterlockedIncrement((LPLONG)&m_dwGrandTotal);
			if(dwCurrent>m_dwTop) InterlockedExchange((LPLONG)&m_dwTop,dwCurrent);
		}
	VOID Decrement()
		{	InterlockedDecrement((LPLONG)&m_dwCurrent);
		}
	VOID CheckPoint()
		{	m_dwFlowInPreSec=max_of(m_dwGrandTotal,m_dwGrandTotalInPreSec)-m_dwGrandTotalInPreSec;
			m_dwTopFlowInPreSec=max_of(m_dwTopFlowInPreSec,m_dwFlowInPreSec);
			m_dwGrandTotalInPreSec=m_dwGrandTotal;
		}
public:
	DWORD	m_dwCurrent;			// ��ǰ����
	DWORD	m_dwTop;				// ��ֵ����(=max_of(��ǰ����))
	DWORD	m_dwGrandTotal;			// �ۼ�����(=sum(��ǰ����))
	DWORD	m_dwGrandTotalInPreSec;	// ǰ���ۼ�(=prev(�ۼ�����))
	DWORD	m_dwFlowInPreSec;		// ǰ������(=deta(�ۼ�����))
	DWORD	m_dwTopFlowInPreSec;	// ǰ���������(=max_of(ǰ������))
};


// ����ָʾ��(����)
class COLLECTION_IMP CFlowIndicator
{
public:
	CFlowIndicator()
		{	m_dwTotalFlow=0;
			m_dwTotalFlowInPreSec=0;
			m_dwFlowInPreSec=0;
			m_dwTopFlowInPreSec=0;
		}
	CFlowIndicator(const CFlowIndicator& Indicator)
		{	m_dwTotalFlow=Indicator.m_dwTotalFlow;
			m_dwTotalFlowInPreSec=Indicator.m_dwTotalFlowInPreSec;
			m_dwFlowInPreSec=Indicator.m_dwFlowInPreSec;
			m_dwTopFlowInPreSec=Indicator.m_dwTopFlowInPreSec;
		}
	~CFlowIndicator()
		{
		}
	const CFlowIndicator& operator=(const CFlowIndicator& Indicator)
		{	m_dwTotalFlow=Indicator.m_dwTotalFlow;
			m_dwTotalFlowInPreSec=Indicator.m_dwTotalFlowInPreSec;
			m_dwFlowInPreSec=Indicator.m_dwFlowInPreSec;
			m_dwTopFlowInPreSec=Indicator.m_dwTopFlowInPreSec;
			return (*this);
		}
	VOID Increment()
		{	InterlockedIncrement((LPLONG)&m_dwTotalFlow);
		}
	VOID Increment(DWORD dwValue)
		{	InterlockedExchangeAdd((LPLONG)&m_dwTotalFlow,dwValue);
		}
	VOID CheckPoint()
		{	m_dwFlowInPreSec=max_of(m_dwTotalFlow,m_dwTotalFlowInPreSec)-m_dwTotalFlowInPreSec;
			m_dwTopFlowInPreSec=max_of(m_dwTopFlowInPreSec,m_dwFlowInPreSec);
			m_dwTotalFlowInPreSec=m_dwTotalFlow;
		}
public:
	DWORD	m_dwTotalFlow;			// ������
	DWORD	m_dwTotalFlowInPreSec;	// ǰ��������(=prev(������))
	DWORD	m_dwFlowInPreSec;		// ǰ������(=deta(������))
	DWORD	m_dwTopFlowInPreSec;	// �������(=max_of(ǰ������))
};


// ״ָ̬ʾ��
class COLLECTION_IMP CStatIndicator
{
public:
	CStatIndicator()
		{	m_tLastOK=0;
			m_bStatOK=FALSE;
		}
	CStatIndicator(const CStatIndicator& Indicator)
		{	m_tLastOK=Indicator.m_tLastOK;
			m_bStatOK=Indicator.m_bStatOK;
		}
	~CStatIndicator()
		{
		}
	const CStatIndicator& operator=(const CStatIndicator& Indicator)
		{	m_tLastOK=Indicator.m_tLastOK;
			m_bStatOK=Indicator.m_bStatOK;
			return (*this);
		}
public:
	systm_t	m_tLastOK;
	BOOL	m_bStatOK;
};

#endif

