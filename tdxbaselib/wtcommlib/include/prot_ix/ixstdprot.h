//////////////////////////////////////////////////////////////////////////
// IX(Information eXchangeЭ���������)
// IXЭ����������ֵ�Э�鷢չ����,�����ڲ�ͬ�ĵײ�Э���Ͻ��о�����ͬ�ܹ�����Ϣ����
//	1. IXЭ��涨Ӧ�ò���Ϣ������Ӧ�����ݸ�ʽ,���Ȳ��涨�ײ�Ĵ��䷽ʽ�ͽṹ,Ҳ������
//     �����ҵ������,ֻ��ע��Ϣ��������ʽ(�����ֵ�)
//  2. IXЭ�������Ӧ��ͬ�ĵײ�Э��,Ŀǰ��Ҫ����TC5��ؼܹ��ķ������Լ�TC5ԭ��ģʽ��Э��.
//	3. IXЭ�����������֯��ͬ��Ӧ�ò�Э��,Ŀǰ��Ҫ����TC5�Լ�IMServer��Э�鼯
#ifndef __IX_STDPROT__H__
#define __IX_STDPROT__H__

// IXЭ�������ֵ�����С
#define MAX_DICT_BUF_SIZE			(1*1024*1024)		// �����ֵ�����С(����)
#define MAX_IX_BUF_SIZE				(64*1024)			// IX���ݵ�������С
#define DICTSTUFF_MAX				(MAX_IX_BUF_SIZE)	// IX���ݵ�������С


// IXЭ�鹦��������
#define FTYPE_NUM					(6)					// ����������
#define FTYPE_UNSPEC				((BYTE)-1)			// ��������δָ��
#define FTYPE_ERROR					((BYTE)-1)			// �������ʹ���
#define FTYPE_DEFAULT				((BYTE)0)			// ��׼ҵ����
#define FTYPE_TCNTR					((BYTE)0)			// ����ҵ����(TRADE CENTER)
#define FTYPE_SCNTR					((BYTE)1)			// ��ȫ���Ĺ���(SECURITY CENTER)
#define FTYPE_ICNTR					((BYTE)2)			// ��Ϣƽ̨����(INFORMATION CENTER)
#define FTYPE_CCNTR					((BYTE)3)			// �������Ĺ���(CALL CENTER)
#define FTYPE_UCNTR					((BYTE)4)			// �û��������Ĺ���(USER CENTER)
#define FTYPE_ECNTR					((BYTE)5)			// �ͻ�����ƽ̨����(SERVICE CENTER)


// IXЭ�鹦����ض���
#define NULL_FUNCNO					(0X0000)			// �޹��ܺ�
#define NULL_ENTRYPOINTID			(0X0000)			// ����ڵ�ID
#define NULL_BRANCHID				(0X00000000)		// ��Ӫҵ��ID


// IXЭ�鹦�ܳ�������
//		��Э������ַ�������ڵ�ID,��TC50�в���USHORT���,���ڸ���ϵͳ֮�������һ��
//		����,�ʽ��ʺű������ַ���(��Ҫ����Ϊ�����ʽ��ʺ��а�����ĸ)
#ifndef IX_FUNCLIMIT_DEFINED
#define IX_FUNCLIMIT_DEFINED
	#define KHH_SIZE				32					// �ͻ��ų���,���������ַ�
	#define ZJZH_SIZE				32					// �ʽ��ʺų���,���������ַ�
	#define GDDM_SIZE				32					// �ɶ����볤��,���������ַ�
	#define JBZD_SIZE				32					// �����ֶγ���,���������ַ�
	#define SMZD_SIZE				256					// ˵���ֶγ���,���������ַ�
	#define AUTHPASS_SIZE			25					// ��֤�����,���������ַ�
	#define YYBIDSTR_SIZE			9					// Ӫҵ��ID������,���������ַ�,�8λ
		
	#define	ZQDM_LEN				(ZQDM_SIZE-1)		// �����볤��
	#define	ZQMC_LEN				(ZQMC_SIZE-1)		// ��Ʒ����
	#define	HKZQDM_LEN				(HKZQDM_SIZE-1)		// (�۹�)�����볤��
	#define	HKZQMC_LEN				(HKZQMC_SIZE-1)		// (�۹�)��Ʒ����
	#define QSID_LEN				(QSID_SIZE-1)		// ȯ�̱�ʶ����
	#define KHH_LEN					(KHH_SIZE-1)		// �ͻ��ų���
	#define TDX_ZJZH_LEN			(ZJZH_SIZE-1)		// �ʽ��ʺų���
	#define AUTHPASS_LEN			(AUTHPASS_SIZE-1)	// ��֤�����
	#define YYBIDSTR_LEN			(YYBIDSTR_SIZE-1)	// Ӫҵ��ID������
		
	#define CONTENT_LEN				512					// �������ݺͻظ���Ϣ��󳤶�
	#define PTBZ_LEN				2					// ��ͨ��־����
#endif

#endif
