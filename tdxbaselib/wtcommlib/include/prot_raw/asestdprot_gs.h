//////////////////////////////////////////////////////////////////////////
// ͨѶ����(��Ϣ�м�/��ȫ����)Э��淶�����ļ�
//	1.ͨѶ������ص�Э�鶨�� (Э��ŷ�Χ: 4510-4560)
//	2.ͨѶ������Ҫʵ�ְ���: ��Ϣ�м�,��ȫ����
// ��ǰ�ļ�����:
//		Part.I		Э�鶨��
//		Part.II		�ڲ��ṹ
//		Part.III	Э�鶨��
//		Part.IV		����ź�(PROTERR)
#ifndef __ASE_STDPROT_GS__H__
#define __ASE_STDPROT_GS__H__
#pragma pack(1)


//////////////////////////////////////////////////////////////////////////
// Part.I Э�鶨��
STD_PROT SHORT TC50_GS_CP_REG				= 4510;			// (�м�)�����ע��(����Э��汾>=5.12.0190)
STD_PROT SHORT TC50_GS_CI_SYN_START			= 4511;			// (�м�)׼��ͬ������״̬(����Э��汾>=5.12.0190)
STD_PROT SHORT TC50_GS_CI_SYN_RUN			= 4512;			// (�м�)ͬ������״̬(����Э��汾>=5.12.0190)
STD_PROT SHORT TC50_GS_CI_SYN_END			= 4513;			// (�м�)ȷ������״̬ͬ��(����Э��汾>=5.12.0190)
STD_PROT SHORT TC50_GS_CP_GOREADY			= 4514;			// (�м�)�����������״̬(����Э��汾>=5.12.0190)
STD_PROT SHORT TC50_GS_CI_UPLOAD			= 4540;			// (�м�)������Ϣ����(����Э��汾>=5.12.0190)
STD_PROT SHORT TC50_GS_CP_WHOONLINE			= 4541;			// (�м�)��ȡ�����û��б�(����Э��汾>=5.12.0190)
STD_PROT SHORT TC50_GS_CP_WHOHACKER			= 4542;			// (�м�)��ȡ��ȫ��ַ������Ϣ(����Э��汾>=5.12.0190)
STD_PROT SHORT TC50_GS_CD_RELAY				= 4550;			// (�м�)�м�ת��
STD_PROT SHORT TC50_GS_CD_INBOX				= 4551;			// (�м�)�յ�ת��
STD_PROT SHORT TC50_GS_CD_KICK				= 4552;			// (�м�)�߳�����


//////////////////////////////////////////////////////////////////////////
// Part.II �ڲ��ṹ
// �����->������Ϣ
typedef enum enumCPCONNSTAT
{	CPCONNST_NOUSED,										// δʹ��
	CPCONNST_ONLINE,										// �û�����
	CPCONNST_OFFLINE,										// �û��˳�
	CPCONNST_STATLOST1,										// ״̬��ʧ(���������)
	CPCONNST_STATLOST2,										// ״̬��ʧ(ʧ���Ͽ�,���ӱ�����)
	CPCONNST_STATLOST3,										// ״̬��ʧ(ʧ���Ͽ�)
	CPCONNST_STATLOST4,										// ״̬��ʧ(ά���Ͽ�,���ӱ�����)
	CPCONNST_UNKNOWN,										// δ֪״̬(�ȴ�ͬ��ȷ��)
} CPCONNSTAT;	
typedef struct tagCPCONNINFO	
{	CPCONNSTAT	m_eState;									// ��ǰ��¼�Ƿ���Ч(����)
	SESSIONID	m_idSession;								// ��ǰ�ỰID
	systm_t		m_tCreated;									// �Ự����ʱ��
	IPV4		m_SourceIp;									// �Ự��ԴIP
	WORD		m_wClientType;								// �ͻ�������
	DWORD		m_dwClientVer;								// �ͻ��˰汾
	IPV4		m_InternetIp;								// IP��ַ(׼����¼����)
	MAC			m_Mac;										// MAC��ַ(׼����¼����)
	WORD		m_wUOrgID;									// ����(ȫ��)
	CHAR		m_szUID[UID_GSIZE];							// �û�(ȫ��)
} CPCONNINFO;	
	
	
// �����->�¼���Ϣ
typedef enum enumCPCONNACTTYPE
{	CPCONNACT_ONLINE,										// �û�����
	CPCONNACT_OFFLINE,										// �û�����
	CPCONNACT_REFUSE,										// ���Ӿܾ�
	CPCONNACT_CRISIS,										// ����ֵ�仯
} CPCONNACTTYPE;	
typedef struct tagCPCONNACT	
{	BYTE		m_cType;	
	union	
	{	struct OfOnline	
		{	WORD		m_wSessionNo;						// �Ự��
			SESSIONID	m_idSession;						// ��ǰ�ỰID
			IPV4		m_SourceIp;							// �Ự��ԴIP
			systm_t		m_tCreated;							// �Ự����ʱ��
			WORD		m_wClientType;						// �ͻ�������
			DWORD		m_dwClientVer;						// �ͻ��˰汾
			IPV4		m_InternetIp;						// IP��ַ
			MAC			m_Mac;								// MAC��ַ
			WORD		m_wUOrgID;							// ����(ȫ��)
			CHAR		m_szUID[UID_GSIZE];					// �û�(ȫ��)
		} m_OfOnline;	
		struct OfOffline	
		{	WORD		m_wSessionNo;						// �Ự��
			SESSIONID	m_idSession;						// ��ǰ�ỰID
			UINT		m_nUnused1;							// �����ֶ�(ԭ:�˳�ԭ��)
			UINT		m_nUnused2;							// �����ֶ�(ԭ:�˳�ԭ�����)
		} m_OfOffline;	
		struct	
		{	IPV4		m_SourceIp;							// ����IP
			WORD		m_wSourcePort;						// ����˿�
			UINT		m_nCause;							// �ܾ�ԭ��
		} m_OfRefuse;	
		struct	
		{	WORD		m_wSessionNo;						// �Ự��
			SESSIONID	m_idSession;						// ��ǰ�ỰID
			WORD		m_wUOrgID;							// ����(ȫ��)
			CHAR		m_szUID[UID_GSIZE];					// �û�(ȫ��)
			IPV4		m_SourceIp;							// ����IP
			IPV4		m_InternetIp;						// IP��ַ
			MAC			m_Mac;								// MAC��ַ
			UINT		m_nCause;							// �˳�ԭ��
			UINT		m_nCauseParam;						// �˳�ԭ�����
		} m_OfCrisis;	
	} m_Data;	
} CPCONNACT;	
	
// �����<-֪ͨ��Ϣ	
typedef enum enumCPNOTIFYTYPE
{	CPNOTIFY_FREEZE,										// ��ַ����
	CPNOTIFY_LOADPOLICY,									// ����װ�ز���
	CPNOTIFY_KICKOUT,										// �û��߳�
} CPNOTIFYTYPE;	
typedef struct tagCPNOTIFY	
{	BYTE		m_cType;	
	union	
	{	struct OfFreeze	
		{	BYTE		m_cLockFlag;						// ������־
			LONG		m_tRestoreTime;						// �ָ�ʱ��(-1:������,0:������,n:Ԥ�ƻָ�ʱ��)
			IPV4		m_SourceIp;							// ����IP
			IPV4		m_InternetIp;						// �ͻ�IP
			MAC			m_Mac;								// �ͻ�MAC
		} m_OfFreeze;	
		struct OfLoadPolicy	
		{	
		} m_OfLoadPolicy;	
		struct OfKickout	
		{	WORD		m_wSessionNo;						// �Ự��
			SESSIONID	m_idSession;						// ��ǰ�ỰID
		} m_OfKickout;	
	} m_Data;	
} CPNOTIFY;	
	
	




//////////////////////////////////////////////////////////////////////////
// Part.III Э�鶨��

// �����ע��(TC50_GS_REG_CP,����Э��汾>=5.12.0188)
struct tc50_gs_cp_reg_req
{	BYTE		m_bPriConn;							// ��Ҫ����(��Ҫ����ͬ����Ϣ)
	BYTE		m_cServId;							// �����ID
	MAC			m_ServMac;							// ������MAC��ַ
	CHAR		m_szServName[64];					// ����������
	DWORD		m_dwMaxConnectNum;					// �����֧�ֵ����������
	UINT		m_nSynAnsBufSize;					// ͬ������������(Ӧ��)
	UINT		m_nExchangeAnsBufSize;				// ��������������(Ӧ��)
	systm_t		m_tCPTime;							// �����ʱ��
	LONG		m_tStartTime;						// ���������ʱ��
	DWORD		m_dwEC;								// ������������
	DWORD		m_dwFinalActIndex;					// ���һ��ͬ������ʼ����λ��
};
struct tc50_gs_cp_reg_ans
{	DWORD		m_dwPrevEC;							// ������������
	UINT		m_nSynReqBufSize;					// ͬ������������(����)
	UINT		m_nExchangeReqBufSize;				// ��������������(����)
	DWORD		m_bReset:1;							// �Ƿ�������ݱ�����
	DWORD		m_bSynch:1;							// �Ƿ���Ҫ����ͬ��
	DWORD		m_dwReserved:30;					// �����ֶ�
};


// ������Ϣͬ��(TC50_GS_CI_SYN_START,����Э��汾>=5.12.0188)
struct tc50_gs_ci_syn_start_req
{	BYTE		m_cServId;							// �����ID
	DWORD		m_bForceSync:1;						// ǿ��ͬ����־
	DWORD		m_dwReserved:31;					// �����ֶ�
};
struct tc50_gs_ci_syn_start_ans
{	DWORD		m_dwReserved;						// �����ֶ�
};


// ������Ϣͬ��(TC50_GS_CI_SYN_RUN,����Э��汾>=5.12.0188)
struct tc50_gs_ci_syn_run_req
{	BYTE		m_cServId;							// �����ID
	WORD		m_wSessionFrom;						// ��ʼ�Ự��
	WORD		m_wSessionEnd;						// �����Ự��
	WORD		m_wSessionCount;					// �Ự��
	DWORD		m_dwReserved;						// �����ֶ�
	WORD		m_cbBuffer;							// ����������
	BYTE		m_acBuffer[1];						// ������
};
struct tc50_gs_ci_syn_run_ans
{	WORD		m_wNextSessionNo;					// �´�ͬ���ĻỰ��
};

// ������Ϣͬ�����(TC50_GS_CI_SYN_END,����Э��汾>=5.12.0188)
struct tc50_gs_ci_syn_end_req
{	BYTE		m_cServId;							// �����ID
	DWORD		m_dwEC;								// ������������
};
struct tc50_gs_ci_syn_end_ans
{	DWORD		m_dwPrevEC;							// ������������
	DWORD		m_dwNewActIndex;					// ͬ�����µ���ʼ����λ��
	DWORD		m_dwReserved;						// �����ֶ�
};




// ��ȡ����״̬�б�(TC50_GS_CP_WHOONLINE,����Э��汾>=5.12.0188)
struct tc50_gs_cp_whoonline_req
{	BYTE		m_cServId;							// �����ID
	systm_t		m_tDataStamp;						// �б�ʱ���(GW��������������,����Խ�������)
	systm_t		m_tSnapStamp;						// ����ʱ���(GW��������������,����Խ�������)
	LONG		m_nOffset;							// ����ƫ��(-1:�������ղ���ȡ��һ����,>=0:�Ѿ���ɵĸ���)
	LONG		m_nAfterVersion;					// ������¼����߰汾
	BYTE		m_cReserved;						// �����ֶ�
};
#define WOF_ONLINE		0X01						// �û�����
#define WOF_OFFLINE		0X02						// �û�����
struct tc50_gs_cp_whoonline_ans
{	systm_t		m_tDataStamp;						// �б�ʱ���(GW��������������,����Խ�������)
	systm_t		m_tSnapStamp;						// ����ʱ���(GW��������������,����Խ�������)
	LONG		m_nCount;							// ���ݸ���
	BYTE		m_bOverwriteAll:1;					// ��Ҫ��ȫ���Ǳ�������
	BYTE		m_bReSnapshot:1;					// ��Ҫ�ؽ�ͬ������
	BYTE		m_cReserved:6;						// �����ֶ�
	WORD		m_cbBuffer;							// ����������
	BYTE		m_acBuffer[1];						// ������
};




// ��ȡ��ȫ��ַ������Ϣ(TC50_GS_CP_WHOHACKER,����Э��汾>=5.12.0188)
struct tc50_gs_cp_whohacker_req
{	BYTE		m_cServId;							// �����ID
	systm_t		m_tDataStamp;						// �б�ʱ���(GW��������������,����Խ�������)
	systm_t		m_tSnapStamp;						// ����ʱ���(GW��������������,����Խ�������)
	LONG		m_nOffset;							// ����ƫ��(-1:�������ղ���ȡ��һ����,>=0:�Ѿ���ɵĸ���)
	LONG		m_nAfterVersion;					// ������¼����߰汾
	BYTE		m_cReserved;						// �����ֶ�
};
struct tc50_gs_cp_whohacker_ans
{	systm_t		m_tDataStamp;						// �б�ʱ���(GW��������������,����Խ�������)
	systm_t		m_tSnapStamp;						// ����ʱ���(GW��������������,����Խ�������)
	LONG		m_nCount;							// ���ݸ���
	BYTE		m_bOverwriteAll:1;					// ��Ҫ��ȫ���Ǳ�������
	BYTE		m_bReSnapshot:1;					// ��Ҫ�ؽ�ͬ������
	BYTE		m_cReserved:6;						// �����ֶ�
	WORD		m_cbBuffer;							// ����������
	BYTE		m_acBuffer[1];						// ������
};


// �����֪ͨ����(TC50_GS_CP_GOREADY,����Э��汾>=5.12.0188)
struct tc50_gs_cp_goready_req
{	BYTE		m_cServId;							// �����ID
	DWORD		m_dwReserved;						// �����ֶ�
};
struct tc50_gs_cp_goready_ans
{	DWORD		m_dwReserved;						// �����ֶ�
};


// ������Ϣ����(TC50_GS_CI_UPLOAD,����Э��汾>=5.12.0188)
struct tc50_gs_ci_upload_req
{	BYTE		m_cServId;							// �����ID
	DWORD		m_dwEC;								// ������������
	DWORD		m_dwActIndex;						// ��ʼ����λ��
	DWORD		m_dwActCount;						// ���µ�������
	WORD		m_cbBuffer;							// ����������
	BYTE		m_acBuffer[1];						// ������
};
struct tc50_gs_ci_upload_ans
{	DWORD		m_dwPrevEC;							// ������������
	DWORD		m_dwNewActIndex;					// �µ���ʼ����λ��
	DWORD		m_dwDropActCount;					// ��Ҫɾ����������
	DWORD		m_dwReserved;						// �����ֶ�
};


// ����ת��(TC50_GS_CD_RELAY,����Э��汾>=5.12.0191)
struct tc50_gs_cd_relay
{	WORD		m_wUOrgID;							// ����(ȫ��)
	CHAR		m_szUID[UID_GSIZE];					// �û�(ȫ��)
	BYTE		m_cFuncType;						// ��������
	WORD		m_wFuncID;							// ���ܺ�
	BYTE		m_cFlags;							// ��־λ(RELAYF_XXXXX)
	DWORD		m_dwReserved;						// ����
	WORD		m_cbBuffer;							// ����������
	BYTE		m_acBuffer[1];						// ������
};
// �м̱�ʶ(����: ASEStdProt_GS.h)
#ifndef RELAY_FLAGS
	#define RELAY_FLAGS
	#define RELAYF_USECOUNTER	0X01				// ʹ���м̼�����
	#define RELAYF_ADDCOUNTER	0X02				// �м̼���������(����:���ӽ����߼��� ȷ��:�������߼���)
	#define RELAYF_COMPRESS		0X04				// ǿ��ʹ��ѹ��ģʽ
	#define RELAYF_ENCRYPTED	0X08				// ǿ��ʹ�ü���ģʽ
#endif


// �յ�ת��(TC50_GS_CD_INBOX,����Э��汾>=5.12.0191)
struct tc50_gs_cd_inbox
{	WORD		m_wUOrgID;							// ����(ȫ��)
	CHAR		m_szUID[UID_GSIZE];					// �û�(ȫ��)
	BYTE		m_cFuncType;						// ��������
	WORD		m_wFuncID;							// ���ܺ�
	BYTE		m_cFlags;							// ��־λ(RELAYF_XXXXX)
	DWORD		m_dwReserved;						// ����
	WORD		m_cbBuffer;							// ����������
	BYTE		m_acBuffer[1];						// ������
};

// �߳�����(TC50_GS_CD_KICK,����Э��汾>=5.12.0191)
struct tc50_gs_cd_kick
{	BYTE		m_cServId;							// �·�����ID
	CPCONNINFO	m_CI;								// ��������Ϣ
	BYTE		m_cServIdToKick;					// �߳��ķ�����ID
	SESSIONID	m_idSessionToKick;					// �߳��ĻỰID
	DWORD		m_dwReserved;						// ����
};



//////////////////////////////////////////////////////////////////////////
// Part.IV �������ź�(PROTERR)
// (��ȫ���ز���)
// (�μ�:ASE_Err.h)

#pragma pack()
#endif
