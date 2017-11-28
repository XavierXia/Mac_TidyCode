//////////////////////////////////////////////////////////////////////////
// ASE(Adaptive Server Environment)�ܹ��µı�׼����(ʹ��IXЭ��)
#ifndef __ASE_STDDEF_IX__H__
#define __ASE_STDDEF_IX__H__
#pragma pack(1)

#ifndef STD_IX_HEADER
#define STD_IX_HEADER
	#define STD_IX_HEADER_DEFINED
	typedef struct tagFUNCHDR
	{	BYTE   m_cFuncType;								// ��������
		WORD   m_wFuncID;								// ����ID
		DWORD  m_dwBranchID;							// Ӫҵ�����(��֤�����͵�����ڵ�ID,���������͵���Ӫҵ��ID)
		#if defined(ASE_BACKWARD_COMPATIBILITY)
			BYTE   m_szMac[6];							// �ͻ�MAC��ַ��Ϣ
			DWORD  m_dwIP;								// �ͻ�IP��ַ��Ϣ(������)
		#else
			MAC    m_Mac;								// �ͻ�MAC��ַ��Ϣ
			IPV4   m_Ip;								// �ͻ�IP��ַ��Ϣ(������)
		#endif
		DWORD  m_dwSN;									// ��������
		WORD   m_wBuild;								// �ֵ�����
		WORD   m_wVersion;								// �ֵ�汾��
		BYTE   m_szReserved[1];							// �����ֽ�
		tagFUNCHDR() { memset(this,0,size_of(tagFUNCHDR)); }
	} FUNCHDR,*LPFUNCHDR;
	typedef struct tagFUNCBDY
	{	DWORD	m_dwSize;
		BYTE	m_szBuffer[1];
		tagFUNCBDY() { memset(this,0,size_of(tagFUNCBDY)); }
	} FUNCBDY,*LPFUNCBDY;
#endif


// ���ݴ���
#define m_dwRealBranchID m_dwBranchID

#pragma pack()
#endif
