//////////////////////////////////////////////////////////////////////////
// ��׼����Э��淶�����ļ�
// ���ļ�����:
//		1.���Э��(Surveillance and Monitoring)���� (Э��ŷ�Χ: 4400-4450)
// Э������:
//		Part.I   ��ع��ܺŶ���
//		Part.II  �����ؽṹ����
//		Part.III ���Э�鶨��
//		Part.IV  ��ش���Ŷ���(PROTERR)
#ifndef __ASE_STDPROT_SAM__H__
#define __ASE_STDPROT_SAM__H__
// Э�鲿��,ʹ��1�ֽڶ���
#pragma pack(1)

// �����Э��
//		����ͻ���Э��,�ӱ��汾��ʼ,ȫ���������˼�ؾ�ʹ�ð�ȫ��֤,�ͻ��˱��뾭��
//		��֤��������ʷ����������Ϣ,������ǰ����������
STD_PROT SHORT SAM_ADMIN_ALIVE					= 4400;			// �����û�������Ϣ(���Э��)(����Э��汾>=5.12.0156)
STD_PROT SHORT SAM_ADMIN_GET_SERVER_INFO		= 4401;			// �����û���ȡ��������Ϣ(���Э��)(����Э��汾>=5.12.0156)
STD_PROT SHORT SAM_ADMIN_LOGIN					= 4402;			// �����û���¼Э��(���Э��)(����Э��汾>=5.12.0156)
STD_PROT SHORT SAM_ADMIN_CHGINFO				= 4403;			// �����û��޸��û���Ϣ(����Э��汾>=5.12.0156)
STD_PROT SHORT SAM_ADMIN_RUNCMD					= 4404;			// ��������(����Э��汾>=5.12.0156)

STD_PROT SHORT SAM_GET_SIMP_STATUS				= 4405;			// �õ��򵥷�����״̬(����Э��汾>=5.12.0156)
STD_PROT SHORT SAM_GET_FULL_STATUS				= 4406;			// �õ���ϸ������״̬

STD_PROT SHORT SAM_LIST_ENTRYPOINTS				= 4407;			// �г�ȫ����ڵ���Ϣ(����Э��汾>=5.12.0156)
STD_PROT SHORT SAM_LIST_BRANCHS					= 4408;			// �г�ȫ��Ӫҵ����Ϣ(����Э��汾>=5.12.0156)
STD_PROT SHORT SAM_GET_ENTRYPOINT_STATUS		= 4409;			// �õ���ڵ�״̬
STD_PROT SHORT SAM_GET_BRANCH_STATUS			= 4410;			// �õ�Ӫҵ��״̬

STD_PROT SHORT SAM_PUT_CALLBOARD				= 4411;			// ����������ϵͳ֪ͨ(����Э��汾>=5.12.0156)
STD_PROT SHORT SAM_PUT_URGENT					= 4412;			// ����������Ӫҵ������(����Э��汾>=5.12.0156)

STD_PROT SHORT SAM_LIST_NETWORK					= 4413;			// �г����׼ܹ�(�ڵ㼯)

STD_PROT SHORT SAM_LIST_DIR						= 4414;			// �г�Ŀ¼ȫ������(����Э��汾>=5.12.0156)
STD_PROT SHORT SAM_MAKE_DIR						= 4415;			// ����Ŀ¼(����Э��汾>=5.12.0156)
STD_PROT SHORT SAM_GET_FILELEN					= 4416;			// �õ��ļ�����(����Э��汾>=5.12.0156)
STD_PROT SHORT SAM_GET_FILE						= 4417;			// ��ȡ�ļ�Ƭ��(����Э��汾>=5.12.0156)
STD_PROT SHORT SAM_PUT_FILE						= 4418;			// �ϴ��ļ�Ƭ��(����Э��汾>=5.12.0156)

STD_PROT SHORT SAM_REBOOT						= 4419;			// ������������(����Э��汾>=5.12.0156)

STD_PROT SHORT SAM_LIST_COUNTERS				= 4420;			// �г���̨��Ϣ
STD_PROT SHORT SAM_GET_COUNTER_STATUS			= 4421;			// �õ���̨״̬

STD_PROT SHORT SAM_CLIENT_LIST					= 4422;			// �г�ȫ���ͻ�(����Э��汾>=5.12.0156)
STD_PROT SHORT SAM_CLIENT_DROP					= 4423;			// �Ͽ�ָ���ͻ�����(����Э��汾>=5.12.0156)
STD_PROT SHORT SAM_CLIENT_MESSAGE				= 4424;			// ��ָ���ͻ�������Ϣ(����Э��汾>=5.12.0156)

STD_PROT SHORT SAM_RAWIP_LIST					= 4425;			// �г���������ڵ�(����Э��汾>=5.12.0156)
STD_PROT SHORT SAM_RAWIP_DROP					= 4426;			// �˳���ǰ����(����Э��汾>=5.12.0156)
STD_PROT SHORT SAM_RAWIP_FREEZE					= 4427;			// ��������ַ(����Э��汾>=5.12.0156)
STD_PROT SHORT SAM_RAWIP_UNFREEZE				= 4428;			// �ⶳ�����ַ(����Э��汾>=5.12.0156)
STD_PROT SHORT SAM_RAWIP_CREDIT					= 4429;			// ����IP���û�ȡ���޸�(����Э��汾>=5.12.0156)

STD_PROT SHORT SAM_IP_LIST						= 4430;			// IP��ַ�б�(����Э��汾>=5.12.0156)
STD_PROT SHORT SAM_IP_FREEZE					= 4431;			// IP��ַ����(ע*,��ȫ���Ķ�����Ҫͨ��SAM_FUNC_CALLʵ��)(����Э��汾>=5.12.0156)
STD_PROT SHORT SAM_IP_UNFREEZE					= 4432;			// IP��ַ�ⶳ(����Э��汾>=5.12.0156)
STD_PROT SHORT SAM_IP_CREDIT					= 4433;			// IP���û�ȡ���޸�(����Э��汾>=5.12.0156)

STD_PROT SHORT SAM_MAC_LIST						= 4434;			// MAC��ַ�б�(����Э��汾>=5.12.0156)
STD_PROT SHORT SAM_MAC_FREEZE					= 4435;			// MAC��ַ����(ע*,��ȫ���Ķ�����Ҫͨ��SAM_FUNC_CALLʵ��)(����Э��汾>=5.12.0156)
STD_PROT SHORT SAM_MAC_UNFREEZE					= 4436;			// MAC��ַ�ⶳ(����Э��汾>=5.12.0156)
STD_PROT SHORT SAM_MAC_CREDIT					= 4437;			// MAC���û�ȡ���޸�(����Э��汾>=5.12.0156)

STD_PROT SHORT SAM_THREAD_LIST					= 4438;			// �߳��б�(����Э��汾>=5.12.0156)
STD_PROT SHORT SAM_THREAD_STATE					= 4439;			// �߳�״̬��ȡ���޸�(����Э��汾>=5.12.0156)

STD_PROT SHORT SAM_FUNCS_LIST					= 4440;			// �����б�(����Э��汾>=5.12.0156)
STD_PROT SHORT SAM_FUNCS_ENABLE					= 4441;			// ��ֹ������ָ������(����Э��汾>=5.12.0156)

STD_PROT SHORT SAM_ROUTES_LIST					= 4442;			// �г�·����(����Э��汾>=5.12.0156)
STD_PROT SHORT SAM_ROUTES_RESET					= 4443;			// �������Ӷ�Ӧ��·����(����Э��汾>=5.12.0156)

STD_PROT SHORT SAM_BLACKLIST_LIST				= 4444;			// �������б�(ע*,��������Ϊ��̬�Ͷ�̬)(����Э��汾>=5.12.0156)
STD_PROT SHORT SAM_BLACKLIST_ADD				= 4445;			// ����������(ע*,��������Ϊ��̬�Ͷ�̬)(����Э��汾>=5.12.0156)
STD_PROT SHORT SAM_BLACKLIST_DEL				= 4446;			// ������ɾ��(����Э��汾>=5.12.0156)

STD_PROT SHORT SAM_INFO_MORE					= 4447;			// ��ȡ������վ��Ϣ
STD_PROT SHORT SAM_INFO_VERSIONS				= 4448;			// ��ȡ�汾ͳ����Ϣ					



// ���ܼ����ļ�(��������)
typedef struct tagTCPERFSNAPSHOT
{	DWORD			m_cbPerfMonItem;					// ��ǰ�ṹ��С
	DWORD			m_cbData;							// ���ݼ�¼��С(�����߳����ݺ͹�������)
	LONG			m_tUpdate;							// ��¼����ʱ��
	LONG			m_tStartup;							// ϵͳ��������
	WORD			m_wCpuUsage;						// CPU������
	WORD			m_wMemUsage;						// �ڴ�������
	DWORD			m_dwTotalPhys;						// �����ڴ�����
    DWORD			m_dwAvailPhys;						// �����ڴ������
    DWORD			m_dwTotalPageFile;					// �ڴ�ҳ������
    DWORD			m_dwAvailPageFile;					// �ڴ�ҳ�����
    DWORD			m_dwTotalVirtual;					// �����ڴ�����
    DWORD			m_dwAvailVirtual;					// �����ڴ����
	DWORD			m_dwUsedConnectNum;					// �ܼ�������(ͳ������)
	DWORD			m_dwTopConnectNum;					// ��ʷ���������(ͳ������)
	DWORD			m_dwNowConnectNum;					// ��ǰ������
	DWORD			m_dwMaxConnectNum;					// ���������
	DWORD			m_dwHisRecvd;						// ��ʷ�����ֽ���(ͳ������)
	DWORD			m_dwHisSent;						// ��ʷ�����ֽ���(ͳ������)
	LONG			m_nBroadcastBusinessNum;			// �㲥������
	LONG			m_nMulticastBusinessNum;			// �鲥������
	LONG			m_nUnicastBusinessNum;				// ����������
	LONG			m_nIncomeBusinessNum;				// ��վ������(���ӱ��Ͽ�ʱ����쳣�������)
	LONG			m_nTopIncomeBusinessNum;			// ��ʷ�����վ������
	LONG			m_nHisIncomeBusinessNum;			// �ۼƵ���վ������
	LONG			m_nHisFailBusinessNum;				// �ۼ�ʧ��������
	LONG			m_nHisSuccessBusinessNum;			// �ۼƳɹ�������
	DWORD			m_dwActiveThreadsNum;				// ��ǰ��߳���(=�����е�������,ͳ������)
	DWORD			m_dwTopActiveThreadsNum;			// ��ֵ����߳���(=�����е�������,ͳ������)
	DWORD			m_dwActiveCoreThreadNum;			// ��ǰ��߳���(=�����е�������,ͳ������)
	DWORD			m_dwTopActiveCoreThreadNum;			// ��ֵ����߳���(=�����е�������,ͳ������)
	DWORD			m_dwActiveCommThreadNum;			// ��ǰ��߳���(=�����е�������,ͳ������)
	DWORD			m_dwTopActiveCommThreadNum;			// ��ֵ����߳���(=�����е�������,ͳ������)
	DWORD			m_dwHisRecvdLast;					// ��ʷ�����ֽ���(����,ͳ������)
	DWORD			m_dwRecvdInSec;						// �����ֽ���(ÿ��,ͳ������)
	DWORD			m_dwTopRecvdInSec;					// ��ֵ�����ֽ���(ÿ��,ͳ������)
	DWORD			m_dwHisSentLast;					// ��ʷ�����ֽ���(����,ͳ������)
	DWORD			m_dwSentInSec;						// �����ֽ���(ÿ��,ͳ������)
	DWORD			m_dwTopSentInSec;					// ��ֵ�����ֽ���(ÿ��,ͳ������)
	LONG			m_nBroadcastBusinessNumLast;		// ��ʷ�㲥������(����,ͳ������)
	LONG			m_nBroadcastBusinessNumInSec;		// �㲥������(ÿ��,ͳ������)
	LONG			m_nTopBroadcastBusinessNumInSec;	// ��ֵ�㲥������(ÿ��,ͳ������)
	LONG			m_nMulticastBusinessNumLast;		// ��ʷ�鲥������(����,ͳ������)
	LONG			m_nMulticastBusinessNumInSec;		// �鲥������(ÿ��,ͳ������)
	LONG			m_nTopMulticastBusinessNumInSec;	// ��ֵ�鲥������(ÿ��,ͳ������)
	LONG			m_nUnicastBusinessNumLast;			// ��ʷ����������(����,ͳ������)
	LONG			m_nUnicastBusinessNumInSec;			// ����������(ÿ��,ͳ������)
	LONG			m_nTopUnicastBusinessNumInSec;		// ��ֵ����������(ÿ��,ͳ������)
	LONG			m_nHisIncomeBusinessNumLast;		// ��ʷ��վ������(����,ͳ������)
	LONG			m_nIncomeBusinessNumInSec;			// ����������(ÿ��,ͳ������)
	LONG			m_nTopIncomeBusinessNumInSec;		// ��ֵ����������(ÿ��,ͳ������)
	DWORD			m_dwHisFuncCallNumLast;				// ��ʷ��ɵĹ�����
	DWORD			m_dwFuncCallNumInSec;				// ����������(ÿ��,ͳ������)
	DWORD			m_dwTopFuncCallNumInSec;			// ��ֵ����������(ÿ��,ͳ������)
	DWORD			m_cbThreadItem;						// �̼߳�¼���С
	DWORD			m_dwThreadNum;						// �߳���(�߳̿��յ��߳���)
	DWORD			m_cbFuncItem;						// ���ܼ�¼���С
	DWORD			m_dwFuncNum;						// ������
} TCPERFSNAPSHOT,*LPTCPERFSNAPSHOT;
typedef struct tagTCTHREADSNAPSHOT
{	DWORD			m_dwType;							// �߳�����
	DWORD			m_dwThreadNo;						// �̺߳�
	systm_t			m_tLastIdle;						// �ϴο���ʱ��(�߳�)
	UINT			m_nId;								// �߳�ID
	LBOOL			m_bBusy;							// �Ƿ�æ(�߳�)
	systm_t			m_tLastActive;						// �ϴμ���ʱ��(�߳�)
	systm_t			m_tBusinessCreated;					// ���񴴽�ʱ��(���ǰ)
	systm_t			m_tBusinessEntry;					// ������봦��ʱ��(�����)
	WORD			m_wReqNo;							// ��ǰ����������
	CHAR			m_szCmdDesc[64];					// ��ǰ���������
	DWORD			m_dwInWaitTime;						// �ڴ��������ĵ�ʱ��(����)
	DWORD			m_dwInProcTime;						// �ڴ��������ĵ�ʱ��(����)
	DWORD			m_dwInApiTime;						// ��API�����ĵ�ʱ��(����)
	DWORD			m_dwHisBusinessNum;					// �ۼƴ���������
	CHAR			m_szComment[64];					// �̱߳�ע��Ϣ
} TCTHREADSNAPSHOT,*LPTCTHREADSNAPSHOT;
typedef struct tagTCFUNCSNAPSHOT
{	BYTE			m_cFuncType;						// ��������
	WORD			m_wFuncID;							// ����ID
	CHAR			m_szDescription[41];				// ��������
	LBOOL			m_bNeedLog;							// �����Ƿ���Ҫ��־(��������)
	LBOOL			m_bTimeLimit;						// �����Ƿ���ʱ����(��������)
	LBOOL			m_bBoostLimit;						// �����Ƿ������������(���봦������/��,��������)
	LBOOL			m_bMassBoostLimit;					// ������������
	LONG			m_nBoostLimit;						// ������������(���봦������/��,��������)
	LBOOL			m_bParallelLimit;					// �����Ƿ����������(��������)
	LBOOL			m_bMassParallelLimit;				// ���鲢�п���
	LONG			m_nParallelLimit;					// �������Ʋ���(��������)
	LBOOL			m_bDisabled;						// �����Ƿ���ʱ����(��̬����)
	LONG			m_nBoostCount;						// ��������(���봦��/ÿ��)����(��̬����)
	LONG			m_nOutFlowCount;					// ��������(�˳�����/ÿ��)����(��̬����)
	LONG			m_nParallelCount;					// ���ܲ��ж�(���ڴ���)����(��̬����)
	LONG			m_nHitCount;						// ���ܵ��ô���(��̬����)
	FLOAT			m_fAverageTime;						// ����ƽ����ʱ(�˳����м���)
	LONG			m_nBoostHitCount;					// ������������(��̬����,��������)
	LONG			m_nParallelHitCount;				// ���鲢�п���(��̬����,��������)
} TCFUNCSNAPSHOT,*LPTCFUNCSNAPSHOT;





//////////////////////////////////////////////////////////////////////////
// ����������
// �����û�������Ϣ(SAM_ADMIN_ALIVE,����Э��汾>=5.12.0156)
struct sam_admin_alive_req
{	BYTE		m_cReserved;
};
struct sam_admin_alive_ans
{	BYTE		m_cReserved;
};

// �����û���ȡ��¼����(SAM_ADMIN_GET_SERVER_INFO,����Э��汾>=5.12.0156)
struct sam_admin_get_server_info_req
{	BYTE		m_cReserved;
};
struct sam_admin_get_server_info_ans
{	IPV4		m_InetIp;						// �ͻ��˹���IP
	CHAR		m_szQsid[QSID_SIZE];			// ȯ�̱�ʶ
	CHAR		m_szDesc[41];					// ����������
	DWORD		m_dwReserved;					// �����ֶ�
};
struct sam_admin_get_server_info_ans2 : public sam_admin_get_server_info_ans
{	WORD		m_wServType;					// ����������
	DWORD		m_dwServVer;					// �������汾
	LONG		m_nLicenseType;					// ��Ȩ����
	CHAR		m_szLicenseFile[MAX_PATH];		// ��Ȩ�ļ�
	LONG		m_nLicenseStatus;				// ��Ȩ״̬
	DWORD		m_dwServID;						// ������ID
	CHAR		m_szServName[32];				// ����������
};


// �����û���¼Э��(SAM_ADMIN_LOGIN,����Э��汾>=5.12.0156)
struct sam_admin_login_req
{	IPV4		m_InetIp;						// �ͻ��˹���IP
	MAC			m_Mac;							// �ͻ���MAC��ַ(��¼��Ϣ)
	WORD		m_wClientType;					// �ͻ�������
	WORD		m_wClientVer;					// �ͻ��˰汾
	WORD		m_wReleaseVer;					// ���а汾
	CHAR		m_szUserName[41];				// �û�����
	CHAR		m_szPassword[41];				// �û�����
	DWORD		m_dwReserved;					// �����ֶ�
};
struct sam_admin_login_ans
{	LBOOL		m_bLocalLogin:1;				// Ȩ��:���ص�¼(ֻ��ʹ��˽����ַ��¼)
	LBOOL		m_bNetLogin:1;					// Ȩ��:�������(����ʹ�����������ַ��¼)
	LBOOL		m_bReboot:1;					// Ȩ��:��������(�Լ�ϵͳ�����������,����Ŀ¼�鿴ɾ����)
	LBOOL		m_bNotice:1;					// Ȩ��:ͨ�淢��(һ��������Ӫҵ����,���Է���ϵͳ�����Ӫҵ������,����ֻ�ܷ�Ӫҵ������)
	LBOOL		m_bMonitor:1;					// Ȩ��:���Ȩ��(ȡ��������/��Ӫҵ��״̬)
	LBOOL		m_bMoreAdmin:1;					// Ȩ��:�������
	LBOOL		m_bLogView:1;					// Ȩ��:��־�鿴
	LBOOL		m_bUserAdmin:1;					// Ȩ��:�ʺŹ���
	LBOOL		m_bPassChange:1;				// Ȩ��:�����޸�(�����޸�����)
	LBOOL		m_bUnused:23;					// ����λ
	DWORD		m_dwReserved;					// �����ֶ�
};

// �����û��޸��û���Ϣ(SAM_ADMIN_CHGINFO,����Э��汾>=5.12.0156)
struct sam_admin_chginfo_req
{	CHAR		m_szUserName[41];				// �û�����
	CHAR		m_szPassword[41];				// �û�����
	CHAR		m_szNewPassword[41];			// ���û�����
	DWORD		m_dwReserved;					// �����ֶ�
};
struct sam_admin_chginfo_ans
{	BYTE		m_cReserved;					// �����ֶ�
};

// �����û�SHELL����(SAM_ADMIN_RUNCMD,����Э��汾>=5.12.0156 NOT_IMPL)
struct sam_admin_runcmd_req
{	CHAR		m_szUserName[41];				// �û�����
	CHAR		m_szPassword[41];				// �û�����
	CHAR		m_szCmd[512];					// ����������
	DWORD		m_dwReserved;					// �����ֶ�
};
struct sam_admin_runcmd_ans
{	BYTE		m_cReserved;					// �����ֶ�
};


// �õ��򵥷�����״̬(SAM_GET_SIMP_STATUS,����Э��汾>=5.12.0156)
struct sam_get_simp_status_req
{	CHAR		m_szUserName[41];				// �û�����
	CHAR		m_szPassword[41];				// �û�����
	DWORD		m_dwReserved;					// �����ֶ�
};
struct sam_get_simp_status_ans
{	FLOAT		m_fVersion;						// �������汾
	CHAR		m_szBuild[32];					// �����������
	LONG		m_tStartupTime;					// ����������ʱ��
	LONG		m_bLogOn;						// �������Ƿ񿪷���־
	
	DWORD		m_dwMaxConnectNum;				// ������������������
	DWORD		m_dwNowConnectNum;				// ��ǰ����
	DWORD		m_dwTopConnectNum;				// ������ֵ
	DWORD		m_dwUsedConnectNum;				// �ۼ�ʹ�ù�������

	DWORD		m_dwHisRecvd;					// ��ʷ�����ֽ���(ͳ������)
	DWORD		m_dwHisSent;					// ��ʷ�����ֽ���(ͳ������)

	LONG		m_nIncomeBusinessNum;			// ��վ������(���ӱ��Ͽ�ʱ����쳣�������)
	LONG		m_nTopIncomeBusinessNum;		// ��ʷ�����վ������

	LONG		m_nHisIncomeBusinessNum;		// �ۼƵ���վ������
	LONG		m_nHisFailBusinessNum;			// �ۼ�ʧ��������
	LONG		m_nHisSuccessBusinessNum;		// �ۼƳɹ�������

	DWORD		m_dwActiveThreadsNum;			// ��ǰ��߳���(=�����е�������,ͳ������)
	DWORD		m_dwTopActiveThreadsNum;		// ��ֵ����߳���(=�����е�������,ͳ������)
	DWORD		m_dwActiveCoreThreadNum;		// ��ǰ��߳���(=�����е�������,ͳ������)
	DWORD		m_dwTopActiveCoreThreadNum;		// ��ֵ����߳���(=�����е�������,ͳ������)
	DWORD		m_dwActiveCommThreadNum;		// ��ǰ��߳���(=�����е�������,ͳ������)
	DWORD		m_dwTopActiveCommThreadNum;		// ��ֵ����߳���(=�����е�������,ͳ������)
	
	DWORD		m_dwHisRecvdLast;				// ��ʷ�����ֽ���(����,ͳ������)
	DWORD		m_dwRecvdInSec;					// �����ֽ���(ÿ��,ͳ������)
	DWORD		m_dwTopRecvdInSec;				// ��ֵ�����ֽ���(ÿ��,ͳ������)

	DWORD		m_dwHisSentLast;				// ��ʷ�����ֽ���(����,ͳ������)
	DWORD		m_dwSentInSec;					// �����ֽ���(ÿ��,ͳ������)
	DWORD		m_dwTopSentInSec;				// ��ֵ�����ֽ���(ÿ��,ͳ������)

	LONG		m_nBroadcastBusinessNumLast;	// ��ʷ�㲥������(����,ͳ������)
	LONG		m_nBroadcastBusinessNumInSec;	// �㲥������(ÿ��,ͳ������)
	LONG		m_nTopBroadcastBusinessNumInSec;// ��ֵ�㲥������(ÿ��,ͳ������)

	LONG		m_nMulticastBusinessNumLast;	// ��ʷ�鲥������(����,ͳ������)
	LONG		m_nMulticastBusinessNumInSec;	// �鲥������(ÿ��,ͳ������)
	LONG		m_nTopMulticastBusinessNumInSec;// ��ֵ�鲥������(ÿ��,ͳ������)

	LONG		m_nUnicastBusinessNumLast;		// ��ʷ����������(����,ͳ������)
	LONG		m_nUnicastBusinessNumInSec;		// ����������(ÿ��,ͳ������)
	LONG		m_nTopUnicastBusinessNumInSec;	// ��ֵ����������(ÿ��,ͳ������)

	LONG		m_nHisIncomeBusinessNumLast;	// ��ʷ��վ������(����,ͳ������)
	LONG		m_nIncomeBusinessNumInSec;		// ����������(ÿ��,ͳ������)
	LONG		m_nTopIncomeBusinessNumInSec;	// ��ֵ����������(ÿ��,ͳ������)

	WORD		m_wLastCpuUsage;				// ��һ��CPU������
	WORD		m_wLastMemUsage;				// ��һ��MEM������

	CHAR		m_szHomePath[MAX_PATH];			// ����·��
	DWORD		m_dwReserved;					// �����ֽ�
};
struct sam_get_simp_status_ans2 : public sam_get_simp_status_ans
{	UINT64		m_nMemTotal;					// �ڴ�����
	UINT64		m_nMemUsed;						// �ڴ�����
	UINT64		m_nDiskTotal;					// ��������
	UINT64		m_nDiskUsed;					// ��������
};


// �õ���ϸ������״̬(SAM_GET_FULL_STATUS,����Э��汾>=5.12.0150)
struct sam_get_full_status_req
{	CHAR		m_szUserName[41];				// �û�����
	CHAR		m_szPassword[41];				// �û�����
	BYTE		m_cReserved;					// �����ֶ�
};
struct sam_get_full_status_ans
{	BYTE		m_cReserved;
};


// �г�ȫ����ڵ���Ϣ(SAM_LIST_ENTRYPOINTS,����Э��汾>=5.12.0150)
struct sam_list_entrypoints_req
{	CHAR		m_szUserName[41];				// �û�����
	CHAR		m_szPassword[41];				// �û�����
	DWORD		m_dwReserved;					// �����ֶ�
};
struct sam_list_entrypoints
{	WORD		m_wEntryPointID;				// ��ڵ�ID
	CHAR		m_szName[41];					// ��ڵ�����
};
struct sam_list_entrypoints_ans
{	WORD		m_wCount;						// ��ڵ����
	DWORD		m_dwReserved;					// �����ֶ�
	sam_list_entrypoints m_Data[1];			// ��ڵ�����
};

// �г�ȫ��Ӫҵ����Ϣ(SAM_LIST_BRANCHS,����Э��汾>=5.12.0150)
struct sam_list_branchs_req
{	CHAR		m_szUserName[41];				// �û�����
	CHAR		m_szPassword[41];				// �û�����
	DWORD		m_dwReserved;					// �����ֶ�
};
struct sam_list_branchs
{	DWORD		m_dwBranchID;					// Ӫҵ��ID
	CHAR		m_szName[41];					// Ӫҵ������
};
struct sam_list_branchs_ans
{	WORD		m_wCount;						// Ӫҵ������
	DWORD		m_dwReserved;					// �����ֶ�
	sam_list_branchs m_Data[1];				// Ӫҵ������
};

// �õ���ڵ�״̬(SAM_GET_ENTRYPOINT_STATUS,����Э��汾>=5.12.0150)
struct sam_get_entrypoint_status_req
{	CHAR		m_szUserName[41];				// �û�����
	CHAR		m_szPassword[41];				// �û�����
	BYTE		m_cReserved;					// �����ֶ�
};
struct sam_get_entrypoint_status_ans
{	BYTE		m_cReserved;
};

// �õ�Ӫҵ��״̬(SAM_GET_BRANCH_STATUS,����Э��汾>=5.12.0150)
struct sam_get_branch_status_req
{	CHAR		m_szUserName[41];				// �û�����
	CHAR		m_szPassword[41];				// �û�����
	BYTE		m_cReserved;					// �����ֶ�
};
struct sam_get_branch_status_ans
{	BYTE		m_cReserved;
};

// ����������ϵͳ֪ͨ(SAM_PUT_CALLBOARD,����Э��汾>=5.12.0150)
struct sam_put_callboard_req
{	CHAR		m_szUserName[41];				// �û�����
	CHAR		m_szPassword[41];				// �û�����
	WORD		m_wCallboardLen;				// �����ı�����
	DWORD		m_dwReserved;					// �����ֶ�
	CHAR		m_szCallboard[1];				// �����ı�
};
struct sam_put_callboard_ans
{	BYTE		m_cReserved;					// �����ֶ�
};

// ����������Ӫҵ������(SAM_PUT_URGENT,����Э��汾>=5.12.0150)
struct sam_put_urgent_req
{	CHAR		m_szUserName[41];				// �û�����
	CHAR		m_szPassword[41];				// �û�����
	DWORD		m_dwBranchID;					// Ӫҵ��ID
	WORD		m_wUrgentLen;					// �����ı�����
	DWORD		m_dwReserved;					// �����ֶ�
	CHAR		m_szUrgent[1];					// �����ı�
};
struct sam_put_urgent_ans
{	BYTE		m_cReserved;					// �����ֶ�
};

// �г�Ŀ¼ȫ������(SAM_LIST_DIR,����Э��汾>=5.12.0156)
struct sam_list_dir_req
{	CHAR		m_szUserName[41];				// �û�����
	CHAR		m_szPassword[41];				// �û�����
	CHAR		m_szDir[256];					// �鿴��Ŀ¼
	LONG		m_nOffset;						// ��ʼ���
	WORD		m_wWantNum;						// ���ӻ�ȡ�ü�¼����
	DWORD		m_dwReserved;					// �����ֶ�
};
struct sam_list_dir
{	CHAR		m_szName[41];					// �ļ������ļ�����
	LBOOL		m_bDir:1;						// �Ƿ���Ŀ¼��
	LBOOL		m_bUnused:31;					// ����λ
	DWORD		m_dwLength;						// �ļ���С
	LONG		m_tModified;					// �ļ��޸�ʱ��
};
struct sam_list_dir_ans
{	WORD		m_wCount;						// Ŀ¼���ļ�����
	DWORD		m_dwReserved;					// �����ֶ�
	sam_list_dir m_Data[1];					// Ŀ¼���ļ������б�
};


// ����Ŀ¼(SAM_MAKE_DIR,����Э��汾>=5.12.0156)
struct sam_make_dir_req
{	CHAR		m_szUserName[41];				// �û�����
	CHAR		m_szPassword[41];				// �û�����
	CHAR		m_szDir[256];					// ��������ɾ��Ŀ¼
	LBOOL		m_bNewOrDel:1;					// ������ɾ����־
	LBOOL		m_bUnused:31;					// ����λ
	DWORD		m_dwReserved;					// �����ֶ�
};
struct sam_make_dir_ans
{	BYTE		m_cReserved;					// �����ֶ�
};

// �õ��ļ�����(SAM_GET_FILELEN,����Э��汾>=5.12.0156)
struct sam_get_filelen_req
{	CHAR		m_szUserName[41];				// �û�����
	CHAR		m_szPassword[41];				// �û�����
	WORD		m_wPathLen;						// ·������
	DWORD		m_dwReserved;					// �����ֶ�
	CHAR		m_szPath[1];					// ·���ı�
};
struct sam_get_filelen_ans
{	DWORD		m_dwReserved;					// �����ֶ�
	DWORD		m_dwLength;						// �ļ�����
};


// ��ȡ�ļ�Ƭ��(SAM_GET_FILE,����Э��汾>=5.12.0156)
struct sam_get_file_req
{	CHAR		m_szUserName[41];				// �û�����
	CHAR		m_szPassword[41];				// �û�����
	DWORD		m_dwOffset;						// �ļ��е�ƫ��
	WORD		m_wWantLen;						// ��ȡ�ĳ���
	WORD		m_wPathLen;						// ·������
	DWORD		m_dwReserved;					// �����ֶ�
	CHAR		m_szPath[1];					// ·���ı�
};
struct sam_get_file_ans
{	WORD		m_wGotLen;						// ��ȡ�ĳ���
	BYTE		m_cReserved;					// �����ֶ�
	BYTE		m_acBuffer[1];					// ������
};

// �ϴ��ļ�Ƭ��(SAM_PUT_FILE,����Э��汾>=5.12.0156)
struct sam_put_file_req
{	CHAR		m_szUserName[41];				// �û�����
 	CHAR		m_szPassword[41];				// �û�����
	CHAR		m_szPath[128];					// �ļ�·��
	DWORD		m_dwOffset;						// �ļ�ƫ��
	WORD		m_wBufferLen;					// ����������
	DWORD		m_dwReserved;					// �����ֶ�
	BYTE		m_acBuffer[1];					// ������
};
struct sam_put_file_ans
{	WORD		m_wWroteLen;					// д�볤��
	BYTE		m_cReserved;					// �����ֶ�
};

// ������������(SAM_REBOOT,����Э��汾>=5.12.0156)
struct sam_reboot_req
{	CHAR		m_szUserName[41];				// �û�����
	CHAR		m_szPassword[41];				// �û�����
	DWORD		m_dwReserved;					// �����ֶ�
};
struct sam_reboot_ans
{	BYTE		m_cReserved;					// �����ֶ�
};

// �г���̨��Ϣ(SAM_LIST_COUNTERS)
struct sam_list_counters_req
{	CHAR		m_szUserName[41];				// �û�����
	CHAR		m_szPassword[41];				// �û�����
	BYTE		m_cReserved;					// �����ֶ�
};
struct sam_list_counters_ans
{	BYTE		m_cReserved;
};

// �õ���̨״̬(SAM_GET_COUNTER_STATUS)
struct sam_get_counter_status_req
{	CHAR		m_szUserName[41];				// �û�����
	CHAR		m_szPassword[41];				// �û�����
	BYTE		m_cReserved;					// �����ֶ�
};
struct sam_get_counter_status_ans
{	BYTE		m_cReserved;
};

// �г�ȫ���ͻ�(SAM_CLIENT_LIST,����Э��汾>=5.12.0156)
enum enumCLIENTSORTFLAG {CLIENT_SORTFLAG_NONE,CLIENT_SORTFLAG_HOT};
enum enumCLIENTFILTER {CLIENT_FILTER_NONE,CLIENT_FILTER_SOURCEIP,CLIENT_FILTER_INTERNETIP,CLIENT_FILTER_MAC,CLIENT_FILTER_OPUID};
struct sam_client_list_req
{	CHAR		m_szUserName[41];				// �û�����
	CHAR		m_szPassword[41];				// �û�����
	WORD		m_wType;						// ��ȡ��ʽ(0:��ȡȫ�� 1:����IP���� 2:�ͻ�IP���� 3:�ͻ�MAC���� 4:�ͻ��Ź���)
	WORD		m_wSortFlag;					// ����ʽ(0:������ 1:���յ��ô�������)
	CHAR		m_szFilter[41];					// ���˵������Ϣ,�ַ�������IP��Ϣ
	DWORD		m_dwOffset;						// ��ʼ���
	WORD		m_wWantNum;						// ��ȡ�ĸ���
	DWORD		m_dwReserved;					// �����ֶ�
};
struct sam_client_list
{	DWORD		m_dwSessionID;					// �ỰID
	DWORD		m_dwSessionNo;					// �Ự��
	IPV4		m_SourceIp;						// ��Դ��ַ
	systm_t		m_tCreated;						// �Ự����ʱ��
	WORD		m_wClientType;					// �ͻ�������
	DWORD		m_dwClientVer;					// �ͻ��˰汾
	IPV4		m_InternetIp;					// ����IP
	MAC			m_Mac;							// ����MAC
	CHAR		m_szUOrg[UORG_SIZE];			// ��������
	CHAR		m_szUID[UID_SIZE];				// �����ʺ�
	DWORD		m_dwHisAppCallNum;				// �ۼƹ��ܵ���
};
struct sam_client_list_ans
{	WORD		m_wCount;						// �ͻ�����
	DWORD		m_dwReserved;					// �����ֶ�
	sam_client_list m_Data[1];					// �ͻ�����
};

// �Ͽ�ָ���ͻ�����(SAM_CLIENT_DROP,����Э��汾>=5.12.0156)
struct sam_client_drop_req
{	CHAR		m_szUserName[41];				// �û�����
	CHAR		m_szPassword[41];				// �û�����
	DWORD		m_dwChannelID;					// ͨ��ID
	DWORD		m_dwReserved;					// �����ֶ�
};
struct sam_client_drop_ans
{	BYTE		m_cReserved;					// �����ֶ�
};

// ��ָ���ͻ�������Ϣ(SAM_CLIENT_MESSAGE,����Э��汾>=5.12.0156)
struct sam_client_message_req
{	CHAR		m_szUserName[41];				// �û�����
	CHAR		m_szPassword[41];				// �û�����
	DWORD		m_dwChannelID;					// ͨ��ID
	WORD		m_wMessageLen;					// ��Ϣ�ı�����
	DWORD		m_dwReserved;					// �����ֶ�
	CHAR		m_szMessage[1];					// ��Ϣ�ı�
};
struct sam_client_message_ans
{	BYTE		m_cReserved;					// �����ֶ�
};


// �г���������ڵ�(SAM_RAWIP_LIST,����Э��汾>=5.12.0156)
enum enumRAWIPSORTFLAG {RAWIP_SORTFLAG_NONE,RAWIP_SORTFLAG_REFNUM,RAWIP_SORTFLAG_HISREFNUM,RAWIP_SORTFLAG_CREDIT,RAWIP_SORTFLAG_HISDENY};
enum enumRAWIPFILTER {RAWIP_FILTER_NONE,RAWIP_FILTER_DANGER,RAWIP_FILTER_FROZEN,RAWIP_FILTER_ACTIVE};
struct sam_rawip_list_req
{	CHAR		m_szUserName[41];				// �û�����
	CHAR		m_szPassword[41];				// �û�����
	DWORD		m_dwType;						// ��ȡ��ʽ(0:��ȡȫ�� 1:��ȡΣ�յ�ַ 2:��ȡ�����ַ 3:��ȡ������ַ)
	WORD		m_wSortFlag;					// ����ʽ(0:������ 1:���ջ���� 2:�����ۼ����� 3.���տ��Ŷ� 4.�����ۼƾܾ�)
	DWORD		m_dwOffset;						// ��ʼ���
	WORD		m_wWantNum;						// ��ȡ�ĸ���
	DWORD		m_dwReserved;					// �����ֶ�
};
struct sam_rawip_list
{	IPV4		m_RawIp;						// �����ַ
	LONG		m_nAddrState;					// ��ǰ״̬
	DWORD		m_dwHisRefNum;					// �ۼ�������
	DWORD		m_dwRefNum;						// ���ü���
	systm_t		m_tLastRef;						// ������ʱ��(�����Ƿ񱻾ܾ�)
	DWORD		m_dwCredit;						// ����ֵ
	systm_t		m_tLastDanger;					// ������Σ��״̬ʱ��
	systm_t		m_tLastFrozen;					// �����붳��״̬ʱ��
	CHAR		m_szByUOrg[UORG_SIZE];			// �������
	CHAR		m_szByUID[UID_SIZE];			// �����û�
	systm_t		m_tLastDeny;					// ���ܾ�ʱ��
	DWORD		m_dwHisDenyNum;					// �ۼ����ܹ�������
};
struct sam_rawip_list_ans
{	WORD		m_wCount;						// �����ַ����
	DWORD		m_dwReserved;					// �����ֶ�
	sam_rawip_list m_Data[1];					// �����ַ����
};


// �˳���ǰ����(SAM_RAWIP_DROP,����Э��汾>=5.12.0156)
struct sam_rawip_drop_req
{	CHAR		m_szUserName[41];				// �û�����
	CHAR		m_szPassword[41];				// �û�����
	IPV4		m_RawIp;						// �����ַ
	DWORD		m_dwReserved;					// �����ֶ�
};
struct sam_rawip_drop_ans
{	BYTE		m_cReserved;					// �����ֶ�
};


// ��������ַ(SAM_RAWIP_FREEZE,����Э��汾>=5.12.0156)
struct sam_rawip_freeze_req
{	CHAR		m_szUserName[41];				// �û�����
	CHAR		m_szPassword[41];				// �û�����
	IPV4		m_RawIp;						// �����ַ
	DWORD		m_dwReserved;					// �����ֶ�
};
struct sam_rawip_freeze_ans
{	BYTE		m_cReserved;					// �����ֶ�
};


// �ⶳ�����ַ(SAM_RAWIP_UNFREEZE,����Э��汾>=5.12.0156)
struct sam_rawip_unfreeze_req
{	CHAR		m_szUserName[41];				// �û�����
	CHAR		m_szPassword[41];				// �û�����
	IPV4		m_RawIp;						// �����ַ
	DWORD		m_dwReserved;					// �����ֶ�
};
struct sam_rawip_unfreeze_ans
{	BYTE		m_cReserved;					// �����ֶ�
};

// ����IP���û�ȡ���޸�(SAM_RAWIP_CREDIT,����Э��汾>=5.12.0156)
struct sam_rawip_credit_req
{	CHAR		m_szUserName[41];				// �û�����
	CHAR		m_szPassword[41];				// �û�����
	IPV4		m_RawIp;						// �����ַ
	DWORD		m_dwCredit;						// �޸�����ֵ
	DWORD		m_dwReserved;					// �����ֶ�
};
struct sam_rawip_credit_ans
{	BYTE		m_cReserved;					// �����ֶ�
};


// IP��ַ�б�(SAM_IP_LIST,����Э��汾>=5.12.0156)
enum enumIPSORTFLAG {IP_SORTFLAG_NONE,IP_SORTFLAG_CREDIT,IP_SORTFLAG_HISDENY};
enum enumIPFILTER {IP_FILTER_NONE,IP_FILTER_DANGER,IP_FILTER_FROZEN,IP_FILTER_ACTIVE};
struct sam_ip_list_req
{	CHAR		m_szUserName[41];				// �û�����
	CHAR		m_szPassword[41];				// �û�����
	DWORD		m_dwType;						// ��ȡ��ʽ(0:��ȡȫ�� 1:��ȡΣ�յ�ַ 2:��ȡ�����ַ)
	WORD		m_wSortFlag;					// ����ʽ(0:������ 1.���տ��Ŷ� 2.�����ۼƾܾ�)
	DWORD		m_dwOffset;						// ��ʼ���
	WORD		m_wWantNum;						// ��ȡ�ĸ���
	DWORD		m_dwReserved;					// �����ֶ�
};
struct sam_ip_list
{	IPV4		m_ClientIp;						// �ͻ���ַ
	LONG		m_nAddrState;					// ��ǰ״̬
	systm_t		m_tLastRegister;				// ���Ǽ�ʱ��
	DWORD		m_dwCredit;						// ����ֵ
	systm_t		m_tLastDanger;					// ������Σ��״̬ʱ��
	systm_t		m_tLastFrozen;					// �����붳��״̬ʱ��
	CHAR		m_szByClientUOrg[UORG_SIZE];	// �������
	CHAR		m_szByClientUID[UID_SIZE];		// �����û�
	systm_t		m_tLastDeny;					// ���ܾ�ʱ��
	DWORD		m_dwHisDenyNum;					// �ۼ����ܹ�������
};
struct sam_ip_list_ans
{	WORD		m_wCount;						// �ͻ���ַ����
	DWORD		m_dwReserved;					// �����ֶ�
	sam_ip_list m_Data[1];						// �ͻ���ַ����
};


// IP��ַ����(ע*,��ȫ���Ķ�����Ҫͨ��SAM_FUNC_CALLʵ��)(SAM_IP_FREEZE,����Э��汾>=5.12.0156)
struct sam_ip_freeze_req
{	CHAR		m_szUserName[41];				// �û�����
	CHAR		m_szPassword[41];				// �û�����
	IPV4		m_ClientIp;						// �ͻ���ַ
	DWORD		m_dwReserved;					// �����ֶ�
};
struct sam_ip_freeze_ans
{	BYTE		m_cReserved;					// �����ֶ�
};


// IP��ַ�ⶳ(SAM_IP_UNFREEZE,����Э��汾>=5.12.0156)
struct sam_ip_unfreeze_req
{	CHAR		m_szUserName[41];				// �û�����
	CHAR		m_szPassword[41];				// �û�����
	IPV4		m_ClientIp;						// �ͻ���ַ
	DWORD		m_dwReserved;					// �����ֶ�
};
struct sam_ip_unfreeze_ans
{	BYTE		m_cReserved;					// �����ֶ�
};


// IP���û�ȡ���޸�(SAM_IP_CREDIT,����Э��汾>=5.12.0156)
struct sam_ip_credit_req
{	CHAR		m_szUserName[41];				// �û�����
	CHAR		m_szPassword[41];				// �û�����
	IPV4		m_ClientIp;						// �ͻ���ַ
	DWORD		m_dwCredit;						// �޸�����ֵ
	DWORD		m_dwReserved;					// �����ֶ�
};
struct sam_ip_credit_ans
{	BYTE		m_cReserved;					// �����ֶ�
};



// MAC��ַ�б�(SAM_MAC_LIST,����Э��汾>=5.12.0156)
enum enumMACSORTFLAG {MAC_SORTFLAG_NONE,MAC_SORTFLAG_CREDIT,MAC_SORTFLAG_HISDENY};
enum enumMACFILTER {MAC_FILTER_NONE,MAC_FILTER_DANGER,MAC_FILTER_FROZEN,MAC_FILTER_ACTIVE};
struct sam_mac_list_req
{	CHAR		m_szUserName[41];				// �û�����
	CHAR		m_szPassword[41];				// �û�����
	DWORD		m_dwType;						// ��ȡ��ʽ(0:��ȡȫ�� 1:��ȡΣ�յ�ַ 2:��ȡ�����ַ)
	WORD		m_wSortFlag;					// ����ʽ(0:������ 1.���տ��Ŷ� 2.�����ۼƾܾ�)
	DWORD		m_dwOffset;						// ��ʼ���
	WORD		m_wWantNum;						// ��ȡ�ĸ���
	DWORD		m_dwReserved;					// �����ֶ�
};
struct sam_mac_list
{	MAC			m_ClientMac;					// �ͻ��˵�ַ
	LONG		m_nAddrState;					// ��ǰ״̬
	systm_t		m_tLastRegister;				// ���Ǽ�ʱ��
	DWORD		m_dwCredit;						// ����ֵ
	systm_t		m_tLastDanger;					// ������Σ��״̬ʱ��
	systm_t		m_tLastFrozen;					// �����붳��״̬ʱ��
	CHAR		m_szByClientUOrg[UORG_SIZE];	// �������
	CHAR		m_szByClientUID[UID_SIZE];		// �����û�
	systm_t		m_tLastDeny;					// ���ܾ�ʱ��
	DWORD		m_dwHisDenyNum;					// �ۼ����ܹ�������
};
struct sam_mac_list_ans
{	WORD		m_wCount;						// �ͻ���ַ����
	DWORD		m_dwReserved;					// �����ֶ�
	sam_mac_list m_Data[1];					// �ͻ���ַ����
};


// MAC��ַ����(ע*,��ȫ���Ķ�����Ҫͨ��SAM_FUNC_CALLʵ��)(SAM_MAC_FREEZE,����Э��汾>=5.12.0156)
struct sam_mac_freeze_req
{	CHAR		m_szUserName[41];				// �û�����
	CHAR		m_szPassword[41];				// �û�����
	MAC			m_ClientMac;					// �ͻ���ַ
	DWORD		m_dwReserved;					// �����ֶ�
};
struct sam_mac_freeze_ans
{	BYTE		m_cReserved;					// �����ֶ�
};


// MAC��ַ�ⶳ(SAM_MAC_UNFREEZE,����Э��汾>=5.12.0156)
struct sam_mac_unfreeze_req
{	CHAR		m_szUserName[41];				// �û�����
	CHAR		m_szPassword[41];				// �û�����
	MAC			m_ClientMac;					// �ͻ���ַ
	DWORD		m_dwReserved;					// �����ֶ�
};
struct sam_mac_unfreeze_ans
{	BYTE		m_cReserved;					// �����ֶ�
};


// MAC���û�ȡ���޸�(SAM_MAC_CREDIT,����Э��汾>=5.12.0156)
struct sam_mac_credit_req
{	CHAR		m_szUserName[41];				// �û�����
	CHAR		m_szPassword[41];				// �û�����
	MAC			m_ClientMac;					// �ͻ���ַ
	DWORD		m_dwCredit;						// �޸�����ֵ
	DWORD		m_dwReserved;					// �����ֶ�
};
struct sam_mac_credit_ans
{	BYTE		m_cReserved;					// �����ֶ�
};


// �߳��б�(SAM_THREAD_LIST,����Э��汾>=5.12.0156)
enum enumTHREADSORTFLAG {THREAD_SORTFLAG_NONE,THREAD_SORTFLAG_ALIVE,THREAD_SORTFLAG_LASTCALL,THREAD_SORTFLAG_LASTBUSINESS,THREAD_SORTFLAG_WAITTIME,THREAD_SORTFLAG_PROCTIME,THREAD_SORTFLAG_HISCALL};
enum enumTHREADFILTER {THREAD_FILTER_NONE};
struct sam_thread_list_req
{	CHAR		m_szUserName[41];				// �û�����
	CHAR		m_szPassword[41];				// �û�����
	DWORD		m_dwType;						// ��ȡ��ʽ(0:��ȡȫ��)
	WORD		m_wSortFlag;					// ����ʽ(0:������ 1.�ϴ�����ʱ�� 2.�ϴε���ʱ�� 3.�ϴ�����ʱ�� 4.�ȴ�ʱ�� 5.����ʱ�� 6.�ۼ�����)
	DWORD		m_dwOffset;						// ��ʼ���
	WORD		m_wWantNum;						// ��ȡ�ĸ���
	DWORD		m_dwReserved;					// �����ֶ�
};
struct sam_thread_list
{	DWORD			m_dwType;					// �߳�����
	DWORD			m_dwThreadID;				// �߳�ID
	LBOOL			m_bBusy;					// �Ƿ�æ(�߳�)
	systm_t			m_tLastIdle;				// �ϴο���ʱ��(�߳�)
	systm_t			m_tLastActive;				// �ϴμ���ʱ��(�߳�)
	systm_t			m_tBusinessCreated;			// ���񴴽�ʱ��(���ǰ)
	systm_t			m_tBusinessEntry;			// ������봦��ʱ��(�����)
	WORD			m_wReqNo;					// ��ǰ����������
	CHAR			m_szCmdDesc[64];			// ��ǰ���������
	DWORD			m_dwInWaitTime;				// �ڴ��������ĵ�ʱ��(����)
	DWORD			m_dwInProcTime;				// �ڴ��������ĵ�ʱ��(����)
	DWORD			m_dwInApiTime;				// ��API�����ĵ�ʱ��(����)
	DWORD			m_dwHisBusinessNum;			// �ۼƴ���������
};
struct sam_thread_list_ans
{	WORD		m_wCount;						// �̸߳���
	DWORD		m_dwReserved;					// �����ֶ�
	sam_thread_list m_Data[1];					// �߳��б�
};


// �߳�״̬��ȡ���޸�(SAM_THREAD_STATE,����Э��汾>=5.12.0156)
struct sam_thread_state_req
{	CHAR		m_szUserName[41];				// �û�����
	CHAR		m_szPassword[41];				// �û�����
	BYTE		m_cReserved;					// �����ֶ�
};
struct sam_thread_state_ans
{	BYTE		m_cReserved;					// �����ֶ�
};

// �����б�(SAM_FUNCS_LIST,����Э��汾>=5.12.0156)
enum enumFUNCSORTFLAG {FUNC_SORTFLAG_NONE,FUNC_SORTFLAG_BOOSTLIMIT,FUNC_SORTFLAG_NEARIN,FUNC_SORTFLAG_AVGTIME,FUNC_SORTFLAG_HISCALL};
enum enumFUNCFILTER {FUNC_FILTER_NONE,FUNC_FILTER_CALLED,FUNC_FILTER_DISABLED,FUNC_FILTER_TIMELIMITED,FUNC_FILTER_BOOSTLIMITED,FUNC_FILTER_BOOSTREACH};
struct sam_funcs_list_req
{	CHAR		m_szUserName[41];				// �û�����
	CHAR		m_szPassword[41];				// �û�����
	DWORD		m_dwType;						// ��ȡ��ʽ(0:��ȡȫ�� 1:��ȡ���ù��� 2:��ȡ������ 3:��ȡ��ʱ���� 4:�������� 5:��������)
	WORD		m_wSortFlag;					// ����ʽ(0:������ 1.�������� 2.�����վ 3.ƽ����ʱ 4.�ۼƵ���)
	DWORD		m_dwOffset;						// ��ʼ���
	WORD		m_wWantNum;						// ��ȡ�ĸ���
	DWORD		m_dwReserved;					// �����ֶ�
};
struct sam_funcs_list
{	BYTE		m_cFuncType;					// ��������
	WORD		m_wFuncID;						// ����ID
	CHAR		m_szDescription[41];			// ��������
	LBOOL		m_bNeedLog;						// �����Ƿ���Ҫ��־(��������)
	LBOOL		m_bTimeLimit;					// �����Ƿ���ʱ����(��������)
	LBOOL		m_bBoostLimit;					// �����Ƿ������������(��������)
	LONG		m_nBoostLimit;					// ��������������(��������)
	LBOOL		m_bDisabled;					// �����Ƿ���ʱ����(��̬����)
	LONG		m_nHitCount;					// ���ܵ��ô���(��̬����)
	LONG		m_nBoostCount;					// ��������(���봦��/ÿ��)����(��̬����)
	LONG		m_nOutFlowCount;				// ��������(�˳�����/ÿ��)����(��̬����)
	FLOAT		m_fAverageTime;					// ����ƽ����ʱ(�˳����м���)
};
struct sam_funcs_list_ans
{	WORD		m_wCount;						// ���ܸ���
	DWORD		m_dwReserved;					// �����ֶ�
	sam_funcs_list m_Data[1];					// �����б�
};

// ��ֹ������ָ������(SAM_FUNCS_ENABLE,����Э��汾>=5.12.0156)
struct sam_funcs_enable_req
{	CHAR		m_szUserName[41];				// �û�����
	CHAR		m_szPassword[41];				// �û�����
	BYTE		m_cFuncType;					// ��������
	WORD		m_wFuncID;						// ����ID
	LBOOL		m_bEnable:1;					// ʹ������͹رչ���
	LBOOL		m_bUnused:31;					// �����ֶ�
	DWORD		m_dwReserved;					// �����ֶ�
};
struct sam_funcs_enable_ans
{	BYTE		m_cReserved;					// �����ֶ�	
};


// �г�·����(SAM_ROUTES_LIST,����Э��汾>=5.12.0156)
enum enumROUTESORTFLAG {ROUTE_SORTFLAG_NONE};
enum enumROUTEFILTER {ROUTE_FILTER_NONE};
struct sam_routes_list_req
{	CHAR		m_szUserName[41];				// �û�����
	CHAR		m_szPassword[41];				// �û�����
	DWORD		m_dwType;						// ��ȡ��ʽ(0:��ȡȫ��)
	WORD		m_wSortFlag;					// ����ʽ(0:������)
	DWORD		m_dwOffset;						// ��ʼ���
	WORD		m_wWantNum;						// ��ȡ�ĸ���
	DWORD		m_dwReserved;					// �����ֶ�
};
struct sam_routes_list
{	LONG		m_nRouteNo;						// ·�ɺ�
	LONG		m_nRouteGuid;					// ·����ΨһID
	BYTE		m_cFuncType;					// ��������
	BYTE		m_cRouteType;					// ·������(Զ��/����)
	TCHAR		m_szRouteDesc[64];				// ·������
	LBOOL		m_bRouteError;					// ·��״̬
	TCHAR		m_szRouteMemo[64];				// ·�ɱ�ע
	DWORD		m_dwBalanceMode;				// ����ģʽ
	LBOOL		m_bBalanceAsWhole;				// �ԵȾ���
	LONG		m_nMaxConnect;					// ���������
};
struct sam_routes_list_ans
{	WORD		m_wCount;						// ·�ɸ���
	DWORD		m_dwReserved;					// �����ֶ�
	sam_routes_list m_Data[1];					// ·���б�
};

// �������Ӷ�Ӧ��·����(SAM_ROUTES_RESET,����Э��汾>=5.12.0156)
struct sam_routes_reset_req
{	CHAR		m_szUserName[41];				// �û�����
	CHAR		m_szPassword[41];				// �û�����
	LONG		m_nRouteGuid;					// ·����ΨһID
	DWORD		m_dwReserved;					// �����ֶ�
};
struct sam_routes_reset_ans
{	BYTE		m_cReserved;					// �����ֶ�	
};


// �������б�(ע*,��������Ϊ��̬�Ͷ�̬)(SAM_BLACKLIST_LIST,����Э��汾>=5.12.0156)
struct sam_blacklist_list_req
{	CHAR		m_szUserName[41];				// �û�����
	CHAR		m_szPassword[41];				// �û�����
	DWORD		m_dwType;						// ����
	DWORD		m_dwOffset;						// ��ʼ���
	DWORD		m_dwReserved;					// �����ֶ�
};
struct sam_blacklist_list
{	DWORD		m_dwRecNo;						// ��¼���
	DWORD		m_dwRawIp;						// �����ַ
};
struct sam_blacklist_list_ans
{	WORD		m_wCount;						// ����������
	DWORD		m_dwReserved;					// �����ֶ�
	sam_blacklist_list m_Data[1];				// �������б�
};

// ����������(ע*,��������Ϊ��̬�Ͷ�̬)(SAM_BLACKLIST_ADD,����Э��汾>=5.12.0156)
struct sam_blacklist_add_req
{	CHAR		m_szUserName[41];				// �û�����
	CHAR		m_szPassword[41];				// �û�����
	IPV4		m_IpFrom;						// ��������ַ(��ʼ)
	IPV4		m_IpEnd;						// ��������ַ(����)
	DWORD		m_dwReserved;					// �����ֶ�
};
struct sam_blacklist_add_ans
{	DWORD		m_dwRecNo;						// ��¼���
};

// ������ɾ��(SAM_BLACKLIST_DEL,����Э��汾>=5.12.0156)
struct sam_blacklist_del_req
{	CHAR		m_szUserName[41];				// �û�����
	CHAR		m_szPassword[41];				// �û�����
	DWORD		m_dwRecNo;						// ��¼���
	DWORD		m_dwReserved;					// �����ֶ�
};
struct sam_blacklist_del_ans
{	BYTE		m_cReserved;					// �����ֶ�
};


// ��ȡ������վ��Ϣ(SAM_INFO_MORE)
struct sam_info_more_req
{	CHAR		m_szUserName[41];				// �û�����
	CHAR		m_szPassword[41];				// �û�����
};
struct sam_info_more_ans
{	LONG		m_nModuleNum;					// ģ����
	struct  
	{	time_t	m_tLastLoginSucess;				// ���һ�γɹ���¼ʱ��
		LONG	m_nKeepLoginFailNum;			// ����ʧ�ܴ���
		time_t	m_tLastAccessSucess;			// ���һ�γɹ�����ʱ��
		LONG	m_nKeepAccessFailNum;			// �������ʴ���
		systm_t	m_tLast30Delays;				// ���30��
	} m_aModuleStatic[8];
	LONG		m_nQueueDepth;					// ��ǰ�������
	LONG		m_nHisIncomeBusinessNum;		// �ۼƵ���վ������
	LONG		m_nHisFailBusinessNum;			// �ۼ�ʧ��������
	LONG		m_nHisSuccessBusinessNum;		// �ۼƳɹ�������
	LONG		m_nHisTimeoutBusinessNum;		// �ۼƵĳ�ʱ������
	LONG		m_nHisOverflowBusinessNum;		// �ۼƵ����������
	LONG		m_nHisInactiveConnectNum;		// �ۼƿͻ����쳣��
	LONG		m_nHisViciousConnectNum;		// �ۼƶ���������
};

// ��ȡ�汾ͳ����Ϣ(SAM_INFO_VERSIONS)
struct sam_info_versions_req
{	CHAR		m_szUserName[41];				// �û�����
	CHAR		m_szPassword[41];				// �û�����
};
struct sam_info_veritem
{	WORD	m_wClientType;						// �ͻ�������
	DWORD	m_dwClientVer;						// �ͻ��˰汾
	LONG	m_nTotalHit;						// �ۼƵ�¼��
	LONG	m_nOnline;							// ��������
};
struct sam_info_versions_ans
{	LONG				m_nVersionNum;			// �汾��
	sam_info_veritem	m_aVersionStatic[1];	// �汾ͳ��
};


//////////////////////////////////////////////////////////////////////////
// ��׼����ź�(PROTERR)
// (��׼���Э�鲿��)
// (�μ�:ASE_Err.h)

#pragma pack()
#endif

