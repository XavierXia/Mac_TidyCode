//////////////////////////////////////////////////////////////////////////
// �ƶ��ն�Э��淶�����ļ�
// 1.�ƶ��ն�Э���������  (Э��ŷ�Χ: 10000-10100)
#ifndef __ASE_STDPROT_MOBILE__H__
#define __ASE_STDPROT_MOBILE__H__
#pragma pack(1)



//////////////////////////////////////////////////////////////////////////
// ���ܺŶ���
STD_PROT WORD MP_TOUCH				= 10000;	// ����Э��(������Կ,������,��ͨ��,�켤��,���ط�����ʱ�为�ؼ�������Ϣ)
STD_PROT WORD MP_CONFIRMBIND		= 10001;	// ȷ�ϰ�
STD_PROT WORD MP_REBIND				= 10002;	// ���°�
STD_PROT WORD MP_FINDSYMBOL			= 10003;	// ������Ʊ



//////////////////////////////////////////////////////////////////////////
// Э��ṹ����



//////////////////////////////////////////////////////////////////////////
// Ӧ�ü��쳣�����
// (�ƶ����ز���)
// (�μ�:ASE_Err.h)



//////////////////////////////////////////////////////////////////////////
// Э��ṹ����

// ����
struct mp_touch_req
{	BYTE	m_cPersistentFlag;				// 0:������ 1:������
	WORD	m_wEntryPointID;				// ��ڵ�ID
	BYTE	m_acReserved[2];				// �����ֽ�
	IPV4	m_Ip;							// �ͻ�IP��ַ��Ϣ(������)
	MAC		m_Mac;							// �ͻ�MAC��ַ��Ϣ
	CHAR	m_szBuildName[16];				// �汾��(��iPad,iPhone,iMac)
	WORD	m_wClientType;					// �ͻ������
	DWORD	m_dwClientVer;					// �ͻ��˰汾
	CHAR	m_szTouchKey[17];				// �Ự��Կ(�ԳƼ���:������Ӧ�����ݼ�����Կ)
	BYTE	m_cConfirmBind;					// ��ȷ��
	CHAR	m_szPhoneId[16];				// �绰����
	CHAR	m_szMachineId[17];				// ����Ӳ��������Ϣ
};
struct mp_touch_ans
{	BYTE	m_cFlag;						// ��־
	DWORD	m_dwMaxSession;					// ������֧�ֵ����Ự��
	DWORD	m_dwNowSession;					// ��������ǰ�ĻỰ��
	DWORD	m_dwMaxConnect;					// ������֧�ֵ����������
	DWORD	m_dwNowConnect;					// ��������ǰ��������
	LONG	m_tStartup;						// ����������ʱ��
	LONG	m_tNow;							// ��������ǰʱ��
	BYTE	m_cBindStatus;					// �ֻ���״̬(0:δ֪ 1:δ�� 2:�󶨳ɹ� 3:�󶨲�ƥ�� 4:�ظ���)
	WORD	m_wOptionalLen;					// ѡ����Ϣ����
	BYTE	m_acOptional[1];				// ѡ����Ϣ����(������Ϣ,...)
};

// ������Ϣ��ʽ
//	BYTE		�汾״̬(0:�汾������ 1:�汾̫�ͱ��ܾ� 2:�汾ǿ������ 3:�汾�������� 4:�汾�Ѿ�����ֹ 5:�汾�Ѿ������°汾)
//	DWORD		�汾��
//	STRING		����URL(��Ҫ����ʱ����Ч,�ǿ�ͨ����վ����)
//	STRING		������ʾ��Ϣ
//	IHASH		������ʶ





// ȷ�ϰ�
struct mp_confirmbind_req
{	CHAR	m_szPhoneId[16];				// �绰����
	CHAR	m_szMachineId[17];				// ����Ӳ��������Ϣ
};
struct mp_confirmbind_ans
{	BYTE	m_cBindStatus;					// �ֻ���״̬(0:δ֪ 1:δ�� 2:�󶨳ɹ� 3:�󶨲�ƥ�� 4:�ظ���)
};
	



// ���°�
struct mp_rebind_req
{	CHAR	m_szPhoneId[16];				// �绰����
};
struct mp_rebind_ans
{	BYTE	m_cStatus;						// ״̬(1:�ɹ� 0:ʧ��)
};


// ��������
struct mp_findsymbol_req
{	CHAR	m_szCode[7];					// ����(\0����)
	LONG	m_nOffset;						// ƫ��
	BYTE	m_cWantCount;					// �������
	BYTE	m_bRestrict:1;					// ��ȷƥ��
	BYTE	m_bFindByClass:1;				// �������
	BYTE	m_bFindSHSZ:1;					// ������г�
	BYTE	m_bFindHK:1;					// ���Ҹ۹��г�
	BYTE	m_bFindQH:1;					// �����ڻ��г�
	BYTE	m_cReserved:3;					// �����ֽ�
};
struct mp_findsymbol_ans
{	BYTE	m_cGotCount;					// ʵ�ʶ�ȡ���ĸ���
	BYTE	m_cReserved;					// �����ֽ�
	WORD	m_cbSymbolInfos;				// ����������
	BYTE	m_acSymbolInfos[1];				// ����������
};


#pragma pack()
#endif
