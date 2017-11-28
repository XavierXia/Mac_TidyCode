//////////////////////////////////////////////////////////////////////////
// ˵��: ��ǰ������ʵ��ȫ����Դ����,�ڸ��Ϸ�������,�ڴ������̹߳�����Ҫͳһ����
//		 �Ա���ϵͳʹ���϶���ģ��ʹ�ø�����ڴ�
// 
#ifndef __RS_MANAGER__H__
#define __RS_MANAGER__H__


// 1.�߳�������Ϊϵͳ������Դ������һ��
// 2.��IOCPģʽ�ķ�������(����,TCP),ҲӦ�����������ӹ�����(��ʽ,TCP),��������(UDP)��,�����ڴ���Դ��


// 1.�̹߳�����,ͨ�����������߳�,�������߳�
// 2.�ڴ������,ͨ�����������ڴ�,�������ڴ�
// 3.�̺߳��ڴ���Щ��ԴҲ��Ҫ�ɹ�������
// 4.��־����(���̶���)Ҳ��Ҫͳһ

// ��Щ������Ҫ���ڷ���������ʱ������,��֧�ֶ��߳̿ɼ�ؿɹ�������
// ���ʹ���̳߳ص�


// ϵͳ��Դ����(���̺�����,SOCKET��Դ)
class CLIBMISC_IMP CSysRSManager
{
public:
	CSysRSManager();
	virtual~CSysRSManager();
};





// �ڴ�ع���ģ��
class CLIBMISC_IMP CHeapPoolManager
{
public:
	CHeapPoolManager();
	virtual~CHeapPoolManager();
};



// �����߳�����
typedef struct tagTHDINF
{	HTHREAD			m_hHandle;						// �߳̾��
	BOOL			m_bQueueAborted;				// �߳��˳��ź�
	systm_t			m_tLastIdle;					// �ϴο���ʱ��(�߳�)
	THREADID		m_nId;							// �߳�ID
	BOOL			m_bBusy;						// �Ƿ�æ(�߳�)
	systm_t			m_tLastActive;					// �ϴμ���ʱ��(�߳�)
	systm_t			m_tBusinessCreated;				// ���񴴽�ʱ��(���ǰ)
	systm_t			m_tBusinessEntry;				// ������봦��ʱ��(�����)
	WORD			m_wCmdNo;						// ��ǰ�����Э���
	CHAR			m_szCmdDesc[64];				// ��ǰ���������
	DWORD			m_dwInWaitTime;					// �ڴ��������ĵ�ʱ��(����)
	DWORD			m_dwInProcTime;					// �ڴ��������ĵ�ʱ��(����)
	DWORD			m_dwInApiTime;					// ��API�����ĵ�ʱ��(����)
	DWORD			m_dwHisBusinessNum;				// �ۼƴ���������
	CHAR			m_szComment[64];				// �̱߳�ע��Ϣ
} THDINF,*LPTHDINF;


// �̳߳ع���
class CLIBMISC_IMP CThreadPoolManager
{
public:
	CThreadPoolManager();
	virtual~CThreadPoolManager();
};


#endif
