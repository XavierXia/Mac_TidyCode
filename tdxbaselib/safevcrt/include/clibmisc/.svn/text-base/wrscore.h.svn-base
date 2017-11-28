#ifndef __WRS_CORE__H__
#define __WRS_CORE__H__
#if _MSC_VER > 1000
#pragma once
#endif

// 权重轮询调度算法(Weighted Round-Robin Scheduling)
class CLIBMISC_IMP CWRSCore
{
public:
	CWRSCore(DWORD dwMaxGroupNum,DWORD dwMaxTargetNum);
	virtual~CWRSCore();
	BOOL AddTarget(LONG nGroupID,LONG nTargetID,LONG nWeight);
	VOID PrepareWRS();
	LONG NextTarget();
	VOID MuteTarget(LONG nTargetID,BOOL bOn);
	VOID SetDamagedTarget(LONG nTargetID,BOOL bDamaged);
	CLock* GetWRSLock() { return &m_CsWRSData; }
protected:
	virtual BOOL IsTargetValid(LONG nTargetID) { UNREFERENCED_PARAMETER(nTargetID); return TRUE; }
public:
	// 分组信息
	typedef struct tagGROUPINFO
	{	LONG	m_nGroupNo;				// 分组号
		LONG	m_nGroupID;				// 分组标识
		LONG	m_nTargetNum;			// 分组中的服务器个数
		LONG	m_nHealthNum;			// 分组中的活动服务器个数
	} GROUPINFO;
	// 目标信息
	typedef struct tagTARGETINFO
	{	GROUPINFO*	m_pGroupInfo;		// 分组信息
		LONG		m_nTargetID;		// 目标标识
		LONG		m_nWeight;			// 预设权重
		LONG		m_nInitWeight;		// 初始权重(0-100)
		LONG		m_nVisiWeight;		// 访问权重(0-100)
		BOOL		m_bDamaged;			// 目标损毁
	} TARGETINFO;
protected:
	void TrySwitchGroupIfNeeded(TARGETINFO* pTargetInfo,BOOL bNowValid);
private:
	CLock			m_CsWRSData;		// 均衡数据
	DWORD			m_dwMaxGroupNum;	// 最大分组个数
	GROUPINFO*		m_pGroupInfos;		// 分组信息
	DWORD			m_dwGroupNum;		// 分组个数
	DWORD			m_dwMaxTargetNum;	// 最大目标个数
	TARGETINFO*		m_pTargetInfos;		// 目标信息
	DWORD			m_dwTargetNum;		// 目标个数
	LONG			m_nWeightMAX;		// 最大权重
	LONG			m_nWeightGCD;		// 权重的最大公约数
	LONG			m_nCurrTarget;		// 当前访问的目标
	LONG			m_nCurrWeight;		// 当前权重信息
	LONG			m_nPriGroupNo;		// 主组(-1表示没有)
	LONG			m_nNowGroupNo;		// 当前活动的组(-1表示没有)
};


#endif
