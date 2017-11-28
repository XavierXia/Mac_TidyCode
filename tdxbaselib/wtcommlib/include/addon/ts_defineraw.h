interface IRawHandler;				// Э�鴦����(PROTOCOLTYPE_TUNNEL,PROTOCOLTYPE_BINARY)


// ԭʼ������Ϣ
typedef struct tagRAWREQCNTX
{	LPBYTE m_pOption;					// ѡ����ָ��
	DWORD m_cbOption;					// ѡ������С
	LPBYTE m_pBody;						// ��Ϣ������ָ��
	DWORD m_cbBody;						// ��Ϣ��С
	DWORD m_cbPackage;					// ��Ϣ��������С(���ǰ)
	BYTE m_cCompressType;				// ѹ��ģʽ
	BYTE m_cEncryptType;				// ��������
} RAWREQCNTX;

// ԭʼӦ����Ϣ
typedef struct tagRAWANSCNTX
{	LPBYTE m_pOption;					// ѡ����ָ��
	DWORD m_cbOption;					// ѡ������С
	LPBYTE m_pBody;						// ��Ϣ������ָ��
	DWORD m_cbBodyMax;					// ��Ϣ��������󳤶�
	DWORD m_cbBody;						// ��Ϣ��С
	BOOL m_bExternPacker;				// �ⲿ�����
	BYTE m_cCompressType;				// ѹ��ģʽ(ԭʼ��С,�ⲿ���)
	BYTE m_cEncryptType;				// ��������(ԭʼ��С,�ⲿ���)
	WORD m_wRawLen;						// Ӧ�𳤶�(ԭʼ��С,�ⲿ���)
} RAWANSCNTX;

// �����Ӧ�������Ļ�ȡ
#define USING_RAW_REQCNTX()																			\
	RAWREQCNTX* pRawReqCntx=(RAWREQCNTX*)pIBusiness->FindCntxObj(BCNTX_RAWREQ);						\
	CLIBVERIFY(pRawReqCntx!=NULL);																	\

#define USING_RAW_ANSCNTX()																			\
	BPR nBPR=m_pIServer->PrepareWriteBufAndEncoder(pIConnect,pIBusiness);							\
	if(nBPR!=BPR_SUCCESS) return nBPR;																\
	RAWANSCNTX* pRawAnsCntx=(RAWANSCNTX*)pIBusiness->FindCntxObj(BCNTX_RAWANS);						\
	CLIBVERIFY(pRawAnsCntx!=NULL&&pRawAnsCntx->m_pBody!=NULL);										\

#define USING_RAW_REQANSCNTX()																		\
	USING_RAW_REQCNTX()																				\
	USING_RAW_ANSCNTX()																				\



// RAWЭ�鶨��
typedef struct tagRAWPROTDEF
{	WORD		m_wCmdNoMin;			// Э���(��ʼ)
	WORD		m_wCmdNoMax;			// Э���(����)
	LPCSTR		m_pszCmdDesc;			// Э������
	DWORD		m_dwProtFlag;			// Э���ʶ(���建�������,���ܵ��߳����,�Ƿ�IXЭ��,�Ƿ���Ҫ��־�͸��ٵ�)
	WORD		m_wOptionLen;			// ��ͷ��Ϣ�鳤��
	WORD		m_wMinReqLen;			// ��С���󳤶�
	WORD		m_wMinAnsBuf;			// ��СӦ�𳤶�
} RAWPROTDEF;
typedef RAWPROTDEF* LPRAWPROTDEF;



// RAWЭ�鴦����
// {BA74AD15-6531-4a7a-8D3A-9D5ADCA549BB}
static const IID IID_IRawHandler = { 0xba74ad15, 0x6531, 0x4a7a, { 0x8d, 0x3a, 0x9d, 0x5a, 0xdc, 0xa5, 0x49, 0xbb } };
interface IRawHandler : public IHandler
{	virtual BPR ParseInfo(IConnect* pIConnect,IBusiness* pIBusiness,LPRAWPROTDEF pProtDef,LPPROTINFO pProtInfo) PURE;
	virtual BPR PreExecute(ISession* pISession,IConnect* pIConnect,IBusiness* pIBusiness) PURE;
	virtual BPR Execute(ISession* pISession,IConnect* pIConnect,IBusiness* pIBusiness) PURE;
};



