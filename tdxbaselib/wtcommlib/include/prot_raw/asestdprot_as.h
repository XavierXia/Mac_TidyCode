//////////////////////////////////////////////////////////////////////////
// ��׼ҵ�񼯳�ƽ̨(��ȫ����,�ּ�ƽ̨)Э��淶�����ļ�
//	1.ҵ�񼯳�ƽ̨��ص�Э�鶨�� (Э��ŷ�Χ: 4506-4510)
//	2.ҵ�񼯳�ƽ̨��Ҫʵ�ְ���: ��ȫ����/�ּ�ƽ̨
//	3.ҵ�񼯳�ƽ̨����ʵ����Ϣ����Э��(IX)��ת��(���Ա�׼�ͻ���Э��)
#ifndef __ASE_STDDEF_AS__H__
#define __ASE_STDDEF_AS__H__
#pragma pack(1)

// Э��Ŷ���
STD_PROT SHORT TC50_AS_DICT_EXCHANGE	= 4506;			// (�ڲ�����)�ֵ佻��



// �ڲ������ֵ佻��(TC50_AS_DICT_EXCHANGE,����Э��汾>=5.12.0171)
// �����̻߳��ⲿ����
// �ڲ������ֵ佻��
struct tc50_as_dict_exchange_req
{	BYTE		m_cFuncType;							// ��������
	MD5BIN		m_md5Dict;								// �ֵ��MD5
	DWORD		m_cbDict;								// �ֵ�ĳ���
};
struct tc50_as_dict_exchange_ans
{	BYTE		m_bDictSupport;							// �����ֵ��Ƿ�֧��
	BYTE		m_bDictUpdated;							// �����ֵ��Ѿ�����
	MD5BIN		m_md5Dict;								// �����ֵ��MD5
	DWORD		m_cbDict;								// �����ֵ�ĳ���
	BYTE		m_szDict[1];							// �����ֵ������
};


#pragma pack()
#endif
