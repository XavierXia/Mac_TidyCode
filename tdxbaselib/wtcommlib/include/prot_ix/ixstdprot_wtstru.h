//////////////////////////////////////////////////////////////////////////
// ��������:2006/07/20
// ����˵��:��׼�����ֵ���ֶζ���
// �����¼:
//            2007/04/29 Ϊ�淶ȫ�������ʽ
// �ر�ע��:
//            1.��������֤ȯ���п��ŷ�ʽ,ÿ�������Ҫ����һ���ɶ��������ͺ͹ɶ�����,������������ݱ���
//              ����Լ��:
//                a.�ͻ���ÿ�ξ�����ɶ����������Լ��ɶ�����
//                b.���ֶα�����Ϊ�����ֶ�,������ɶ������б�����һ��ѡ�еĹɶ��������ͺ͹ɶ�����
//                c.���ֶα�����ʹ�����������,����Ҫ������ԭ�к���
//                d.��Լ����ֻ������֤ȯ���п��ŷ�ʽ��Ч,�������б�Ǳ������ֶξ���һ���̶���������
//                  ����Դ����ռ����,Ҳ��һ�ֶԳ��������ϰ�
//              �Ժ����������Ҫ���þ�̬���洦��,����ʹ��Ӱ��ϵͳ�ܹ��ķ���.
//            2.���ڱ����ֶ�,�ͻ��˳����������Ӧ�������κ���Ϣ,��Щ�ֶ���ʱ������������.
//            3.���ڿ�ѡ�ֶ��䱾��������⺬�岢��ʾһ�����⹦��,��̨���Զ���Щ�ֶ��ṩ�Ĺ���ѡ����֧��
//              ����Щ����δ�ؿͻ�����Ҫʹ�û����Ѿ�ʹ�õ�,Ҳ����˵�ǷǱ�Ҫ��(���ڵ���ί�в�ѯ�ֶδ˴���
//              ��һЩ���⴦��)
//            4.���ڳ�����Ҫ�����������ķ������������Զ����ķ���
//              ��������������������пɳ�����ѯ���ص��ֶ�,Ӧ������ͨ���ɳ�����ѯ���صĽ�������Щ�ֶ�
//            5.ϵͳ�ӵ�ǰ�汾��֧�ֶ�̬���潻��(Cookies),��ҪCWtCache2,CWtCommon2��CWtDict3֧��
//              ����Ľ�������Ϊ:
//                    CACHE����-->COOKIES
//                    REQ|COOKIES-->������
//                    �ͻ���<--ANS|COOKIES
//                    CACHE����<--COOKIES
//            6.���ڰ�ȫ������صĴ����߼�
//              a.������δ���ð�ȫ����·��
//                a).�ͻ��˰���EMBWT.CFG���ƿͻ��˵�¼��ʾ����
//                b).�ͻ����Զ����԰�ȫ�����Э��(��¼ʱ)
//                c).�ͻ��˲���ʾ��ȫ��صķ������(���簲ȫ����)
//              b.�����������а�ȫ����·��
//                a).�ͻ��˰���EMBWT.CFG���ƿͻ��˵�¼��ʾ����
//                b).�ͻ����κΰ�ȫҵ����ص�Э��ʱ�������͵�������(��¼ʱ)
//                c).�ͻ��˸��ݷ�����֧�ֵİ�ȫ��ʽ���ư�ȫ����ؽ���
//                   ����������֧����֤���������֤��,(����ʾ��ȫ��ؽ���)
//              c.��¼ʱ,�쳣���ݴ���
//                a).��ȫ���������ֵ�Ϊ��,��ͬ�ڿͻ���δ���ð�ȫ����(����ʾ��ȫ��ؽ���)
//                b).�ͻ��˵�¼ʱ�򷵻�·�ɷ�æ,��ͬ�ڿͻ���δ���ð�ȫ����
//                c).�ͻ��˵�¼ʱ�򷵻����ݿⷱæ,��ͬ�ڿͻ���δ���ð�ȫ����
#ifndef __IX_STDPROT_WT_STRU__H__
#define __IX_STDPROT_WT_STRU__H__
#pragma pack(1)
#ifndef ASELIB_API
	#error "ASELib.h" must be included.
#endif
#ifndef ASELIBIMPL_DEFINED
	#error "ASELibIXImpl.h" must be included.
#endif


//---------------------------------------------------------------------------
// Part.I ������
//---------------------------------------------------------------------------

	// �ṹ-�ֶζ���
	typedef struct tagSTRUCTFIELD
	{	WORD			m_wStruID;
		LPWORD			m_pwFields;
		WORD			m_wFieldNum;
	} STRUCTFIELD;

	// ��ʼ�ṹ�ֶζ���
	#define BEGIN_STRUCT_FIELD_DEF(NAME)		\
		const STRUCTFIELD NAME[]={

	// ����ṹ�ֶ�
	#define DECLARE_STRUCT_FIELD(STRU_ID,STRU_DEF)	\
		{STRU_ID,(LPWORD)STRU_DEF,size_of(STRU_DEF)/size_of(STRU_DEF[0])},

	// �����ṹ�ֶζ���
	#define END_STRUCT_FIELD_DEF(NAME)			\
		};

	// �ֶγ�ʼ������
	inline BOOL InitDict(CWtDict *pDict,
					const FIELDINFO* pFieldInfo,WORD wFieldNum,
					const WORD* pwStructInfo,WORD wStructNum,
					const STRUCTFIELD* pStructFieldInfo,WORD wStructFieldNum)
	{	if(!pDict->RegisterFieldInfo(pFieldInfo,wFieldNum)) return FALSE;
		if(!pDict->RegisterStruct(pwStructInfo,wStructNum)) return FALSE;
		for(WORD i=0; i<wStructFieldNum; i++)
		{	if(!pDict->RegisterStructField(pStructFieldInfo[i].m_wStruID,pStructFieldInfo[i].m_pwFields,pStructFieldInfo[i].m_wFieldNum))
				return FALSE;
		}
		return TRUE;
	}


	#define INIT_SIMPLE_DICT(pDict)																						\
			InitDict(pDict,tdxSimpleFieldInfo,size_of(tdxSimpleFieldInfo)/size_of(tdxSimpleFieldInfo[0]),				\
					tdxSimpleStructInfo,size_of(tdxSimpleStructInfo)/size_of(tdxSimpleStructInfo[0]),					\
					tdxSimpleStructFieldInfo,size_of(tdxSimpleStructFieldInfo)/size_of(tdxSimpleStructFieldInfo[0]))

	#define INIT_COMMON_DICT(pDict)																						\
			InitDict(pDict,tdxCommonFieldInfo,size_of(tdxCommonFieldInfo)/size_of(tdxCommonFieldInfo[0]),				\
					tdxCommonStructInfo,size_of(tdxCommonStructInfo)/size_of(tdxCommonStructInfo[0]),					\
					tdxCommonStructFieldInfo,size_of(tdxCommonStructFieldInfo)/size_of(tdxCommonStructFieldInfo[0]))

	#define INIT_SCNTR_DICT(pDict)																						\
			InitDict(pDict,tdxScntrFieldInfo,size_of(tdxScntrFieldInfo)/size_of(tdxScntrFieldInfo[0]),					\
					tdxScntrStructInfo,size_of(tdxScntrStructInfo)/size_of(tdxScntrStructInfo[0]),						\
					tdxScntrStructFieldInfo,size_of(tdxScntrStructFieldInfo)/size_of(tdxScntrStructFieldInfo[0]))
	
	#define INIT_RZ_DICT(pDict)																							\
			InitDict(pDict,tdxRZFieldInfo,size_of(tdxRZFieldInfo)/size_of(tdxRZFieldInfo[0]),							\
					tdxRZStructInfo,size_of(tdxRZStructInfo)/size_of(tdxRZStructInfo[0]),								\
					tdxRZStructFieldInfo,size_of(tdxRZStructFieldInfo)/size_of(tdxRZStructFieldInfo[0]))


//---------------------------------------------------------------------------
// Part.II ��׼�ֶζ���
//---------------------------------------------------------------------------

// ���ֵ��ֶζ���
const FIELDINFO tdxSimpleFieldInfo[]=
{
//	{	�ֶ�����,					��������,		��ʾ(����)����,���,	�ֶ�˵��,				�������,	},

	{	TDX_ID_ZQJYBS,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"֤ȯ���ױ�ʶ",			1,0,0,0,0,	},
	{	TDX_ID_YYB,					TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"Ӫҵ������",			0,0,0,0,0,	},
	{	TDX_ID_OP_WTFS,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"ί�з�ʽ",				0,0,0,0,0,	},
	{	TDX_ID_CZBZ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"������־",				1,0,0,0,0,	},
	{	TDX_ID_KHH,					TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"�ͻ���",				0,0,0,0,0,	},
	{	TDX_ID_ZJZH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"�ʽ��ʺ�",				0,0,0,0,0,	},
	{	TDX_ID_KHMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"�ͻ�����",				0,0,0,0,0,	},
	{	TDX_ID_GDDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"�ɶ�����",				0,0,0,0,0,	},
	{	TDX_ID_ZHLB,				TDX_DT_STRING,	TDX_DISP_RIGHT,   2,	"�ʺ����",				1,0,0,0,0,	},
	{	TDX_ID_JYMM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"��������",				1,0,0,0,0,	},
	{	TDX_ID_TXMM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"ͨѶ����",				1,0,0,0,0,	},
	{	TDX_ID_WTFS,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"ί�з�ʽ",				1,0,0,0,0,	},
	{	TDX_ID_QZKTBZ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"Ȩ֤��ͨ��־",			1,0,0,0,0,	},
	{	TDX_ID_GTZDKMBS,			TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"ȡ��̨��������",		1,0,0,0,0,	},
	{	TDX_ID_KHQXDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"�ͻ�Ȩ�޴���",			0,0,0,0,0,	},
	{	TDX_ID_KHQXMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"�ͻ�Ȩ������",			0,0,0,0,0,	},
	{	TDX_ID_OTCJYBS,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"OTC���ױ�־",			1,0,0,0,0,	},
	{	TDX_ID_XYJYBS,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"������ȯ��ʶ",			1,0,0,0,0,	},
	{	TDX_ID_SFCGBS,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"������ܱ�ʶ",			1,0,0,0,0,	},
	{	TDX_ID_DFKHDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"�Է��ͻ�����",			0,0,0,0,0,	},
	{	TDX_ID_DFFZDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"�Է���֧����",			0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_JJBS,			TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"����ʽ�����ʶ",		0,0,0,0,0,	},
	{	TDX_ID_ZDJYBZ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"ָ�����ױ�ʶ",			1,0,0,0,0,	},
	{	TDX_ID_ETFBS,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"ETF��ʶ",				1,0,0,0,0,	},
                                                                        	
	{	TDX_ID_BANKCODE,			TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"���д���",				0,0,0,0,0,	},
	{	TDX_ID_BANKYYB,				TDX_DT_STRING,	TDX_DISP_RIGHT,  40,	"����Ӫҵ��",			0,0,0,0,0,	},
	{	TDX_ID_BANKGDTYPE,			TDX_DT_STRING,	TDX_DISP_RIGHT,   2,	"���йɶ������¼�г�",	0,0,0,0,0,	},
                                                                        	
	{	TDX_ID_ZJHM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"֤������",				0,0,0,0,0,	},
	{	TDX_ID_MOBILEPHONE,			TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"�ƶ��绰",				0,0,0,0,0,	},
	{	TDX_ID_USERPHONE,			TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"סլ�绰",				0,0,0,0,0,	},
	{	TDX_ID_USEREMAIL,			TDX_DT_STRING,	TDX_DISP_RIGHT,  40,	"�û�EMAIL",			0,0,0,0,0,	},
	{	TDX_ID_SHGD,				TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"�Ϻ��ɶ�",				0,0,0,0,0,	},
	{	TDX_ID_SZGD,				TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"���ڹɶ�",				0,0,0,0,0,	},
	{	TDX_ID_KHTYPE,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"�������",				0,0,0,0,0,	},

	{	TDX_ID_TSXX0,				TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"��ʾ��Ϣ0",			0,0,0,0,0,	},
	{	TDX_ID_TSXX1,				TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"��ʾ��Ϣ1",			0,0,0,0,0,	},
	{	TDX_ID_TSXX2,				TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"��ʾ��Ϣ2",			0,0,0,0,0,	},
	{	TDX_ID_TSXX3,				TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"��ʾ��Ϣ3",			0,0,0,0,0,	},
	{	TDX_ID_TSXX4,				TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"��ʾ��Ϣ4",			0,0,0,0,0,	},
	{	TDX_ID_TSXX5,				TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"��ʾ��Ϣ5",			0,0,0,0,0,	},
	{	TDX_ID_TSXX6,				TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"��ʾ��Ϣ6",			0,0,0,0,0,	},
	{	TDX_ID_TSXX7,				TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"��ʾ��Ϣ7",			0,0,0,0,0,	},
	{	TDX_ID_TSXX8,				TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"��ʾ��Ϣ8",			0,0,0,0,0,	},
	{	TDX_ID_TSXX9,				TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"��ʾ��Ϣ9",			0,0,0,0,0,	},

	{	TDX_ID_FJZH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"�����˺�",				0,0,0,0,0,	},
	{	TDX_ID_XYJYTSXX,			TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"���ý�����ʾ��Ϣ",	    0,0,0,0,0,	},

	{	TDX_ID_QHJYTSXX,			TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"�ڻ�������ʾ��Ϣ",		0,0,0,0,0,	},

	{	TDX_ID_XT_ERRCODE,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"�����",				0,0,0,0,0,	},
	{	TDX_ID_XT_ERRMSG,			TDX_DT_STRING,	TDX_DISP_RIGHT,  80,	"������Ϣ",				0,0,0,0,0,	},                       	
	{	TDX_ID_XT_MACADDR,			TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"MAC��ַ",				0,0,0,0,0,	},
	{	TDX_ID_XT_CLITYPE,			TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"�ͻ����",				0,0,0,0,0,	},
	{	TDX_ID_XT_OEM_FLAG,			TDX_DT_CHAR,	TDX_DISP_RIGHT,  16,	"OEM��ʶ",				0,0,0,0,0,	},
	{	TDX_ID_XT_AUTH_MODE,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"��֤��ʽ",				0,0,0,0,0,	},
	{	TDX_ID_XT_AUTH_INFO,		TDX_DT_CHAR,	TDX_DISP_RIGHT, 512,	"��֤��Ϣ",				0,0,0,0,0,	},
	{	TDX_ID_XT_AUTH_NEWINFO,		TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"��֤����Ϣ",			0,0,0,0,0,	},
	{	TDX_ID_XT_BRANCHID,			TDX_DT_CHAR,	TDX_DISP_RIGHT,  10,	"Ӫҵ��ID",				0,0,0,0,0,	},
	{	TDX_ID_XT_RESERVED,			TDX_DT_STRING,	TDX_DISP_RIGHT,  80,	"������Ϣ",				1,0,0,0,0,	},
	{	TDX_ID_RETINFO,				TDX_DT_STRING,	TDX_DISP_RIGHT,  80,	"������Ϣ",				0,0,0,0,0,	},
	{	TDX_ID_XT_RECONNECTFLAG,	TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"����������־",			1,0,0,0,0,	},
	{	TDX_ID_XT_COUNTERSTATUS,	TDX_DT_STRING,	TDX_DISP_RIGHT,  80,	"��̨״̬",				0,0,0,0,0,	},
	{	TDX_ID_XT_VIPFLAG,			TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"VIP��־",				1,0,0,0,0,	},
	{	TDX_ID_XT_CLIENTRIGHTS,		TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"�ͻ�Ȩ��",				1,0,0,0,0,	},
	{	TDX_ID_XT_LAST_LOGIN_DATE,	TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"�ϴε�¼����",			1,0,0,0,0,	},
	{	TDX_ID_XT_LAST_LOGIN_TIME,	TDX_DT_TIME,	TDX_DISP_RIGHT,   8,	"�ϴε�¼ʱ��",			1,0,0,0,0,	},
	{	TDX_ID_XT_AHTHCHAR1,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"��֤�ַ�1",			1,0,0,0,0,	},
	{	TDX_ID_XT_AHTHCHAR2,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"��֤�ַ�2",			1,0,0,0,0,	},
	{	TDX_ID_XT_CHECKRISKFLAG,	TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"�����ձ�־",			1,0,0,0,0,	},
	{	TDX_ID_XT_FJYZHBZ,			TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"�ǽ����ʺű�־",		1,0,0,0,0,	},
	{	TDX_ID_XT_JZJJKHBZ,			TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"��ֹ���𿪻���־",		1,0,0,0,0,	},
	{	TDX_ID_RZ_LEVER,			TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"�û�����",				0,0,0,0,0,	},
	{	TDX_ID_XT_INCREMENTMODE,	TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"����ģʽ����",			0,0,0,0,0,	},
	{	TDX_ID_XT_PARAM,			TDX_DT_STRING,	TDX_DISP_RIGHT,  80,	"����",					0,0,0,0,0,	},
	{	TDX_ID_XT_MODE,				TDX_DT_STRING,	TDX_DISP_RIGHT,  80,	"ģʽ",					0,0,0,0,0,	},
	{	TDX_ID_XT_DESCRIPTION,		TDX_DT_STRING,	TDX_DISP_RIGHT,  80,	"����",					0,0,0,0,0,	},
	{	TDX_ID_XT_QUERYMODE,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"��ѯģʽ",				0,0,0,0,0,	},
	{	TDX_ID_XT_PASSWORDFLAG,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"�����־",				0,0,0,0,0,	},
	{	TDX_ID_XT_HANDLE,			TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"���",					1,0,0,0,0,	},
	{	TDX_ID_XT_GTLB,				TDX_DT_STRING,	TDX_DISP_RIGHT,   1,	"��̨���",				1,0,0,0,0,	},
	{	TDX_ID_XT_MACHINEINFO,		TDX_DT_STRING,	TDX_DISP_RIGHT, 800,	"������Ϣ",				0,0,0,0,0,	},
	{	TDX_ID_XT_CLIVER,			TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"�ͻ��˰汾",			0,0,0,0,0,	},
	{	TDX_ID_XT_LOGINTYPE,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"��¼�ʺ����",			0,0,0,0,0,	},
	{	TDX_ID_XT_LOGINID,			TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"��¼ID",				0,0,0,0,0,	},
	{	TDX_ID_XT_LOGINPASSWD,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"��¼����",				0,0,0,0,0,	},
	{	TDX_ID_XT_COMMPASSWD,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"ͨѶ����",				0,0,0,0,0,	},
	{	TDX_ID_XT_FUNCID,			TDX_DT_CHAR,	TDX_DISP_RIGHT,   3,	"����ID",				0,0,0,0,0,	},
	{	TDX_ID_XT_FUNCDICTTAG,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   3,	"�����ֵ��ʶ",			0,0,0,0,0,	},
	{	TDX_ID_XT_FUNCCONTENT,		TDX_DT_CHAR,	TDX_DISP_RIGHT, 800,	"��������",				0,0,0,0,0,	},
	{	TDX_ID_XT_LIMITMODE,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"����ģʽ",				0,0,0,0,0,	},
	{	TDX_ID_XT_MACHINECODE,		TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"����������",			0,0,0,0,0,	},
	{	TDX_ID_XT_MOBILECHECKCODE,	TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"�ֻ�У����",			0,0,0,0,0,	},
	{	TDX_ID_XT_BRANCHMODIFY,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"Ӫҵ���ı�",			0,0,0,0,0,	},
	{	TDX_ID_XT_NEEDEDAUTHMODE,	TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"������֤��ʽ",			0,0,0,0,0,	},
	{	TDX_ID_XT_SESSION,			TDX_DT_STRING,	TDX_DISP_RIGHT, 128,	"SESSION��Ϣ",			0,0,0,0,0,	},
	{	TDX_ID_XT_URL,				TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"URL",					0,0,0,0,0,	},
	{	TDX_ID_XT_INFOCOLUMN,		TDX_DT_STRING,	TDX_DISP_RIGHT, 128,	"��Ѷ��Ŀ",				0,0,0,0,0,	},
	{	TDX_ID_XT_REALCLIENTVERSION,TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"�ڲ��ͻ��˰汾",		0,0,0,0,0,	},
	{	TDX_ID_XT_NEEDCONFIRMFLAGS,	TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"��ȷ�ϵı�ʶ��",		0,0,0,0,0,	},
	{	TDX_ID_XT_URL2,				TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"URL2",					0,0,0,0,0,	},
	{	TDX_ID_XT_REDIRECTFLAG,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"�ض����־",			0,0,0,0,0,	},
	{	TDX_ID_XT_REDIRECTINFO,		TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"�ض�����Ϣ",			0,0,0,0,0,	},
	{	TDX_ID_XT_LAST_LOGIN_LOCATION,TDX_DT_STRING,TDX_DISP_RIGHT, 128,	"�ϴε�¼λ��",			1,0,0,0,0,	},
	{	TDX_ID_XT_TOKEN,			TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"����",					0,0,0,0,0,	},
	{	TDX_ID_XT_PREPASSWORD0,		TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"Ԥ��������0",			0,0,0,0,0,	},
	{	TDX_ID_XT_PREPASSWORD1,		TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"Ԥ��������1",			0,0,0,0,0,	},
	{	TDX_ID_XT_PREPASSWORD2,		TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"Ԥ��������2",			0,0,0,0,0,	},
	{	TDX_ID_XT_PREPASSWORD3,		TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"Ԥ��������3",			0,0,0,0,0,	},
	{	TDX_ID_XT_PREPASSWORD4,		TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"Ԥ��������4",			0,0,0,0,0,	},
	{	TDX_ID_XT_PREPARAM0,		TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"Ԥ�������0",			0,0,0,0,0,	},
	{	TDX_ID_XT_PREPARAM1,		TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"Ԥ�������1",			0,0,0,0,0,	},
	{	TDX_ID_XT_PREPARAM2,		TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"Ԥ�������2",			0,0,0,0,0,	},
	{	TDX_ID_XT_PREPARAM3,		TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"Ԥ�������3",			0,0,0,0,0,	},
	{	TDX_ID_XT_PREPARAM4,		TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"Ԥ�������4",			0,0,0,0,0,	},
	{	TDX_ID_XT_PREPARAM5,		TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"Ԥ�������5",			0,0,0,0,0,	},
	{	TDX_ID_XT_PREPARAM6,		TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"Ԥ�������6",			0,0,0,0,0,	},
	{	TDX_ID_XT_PREPARAM7,		TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"Ԥ�������7",			0,0,0,0,0,	},
	{	TDX_ID_XT_PREPARAM8,		TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"Ԥ�������8",			0,0,0,0,0,	},
	{	TDX_ID_XT_PREPARAM9,		TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"Ԥ�������9",			0,0,0,0,0,	},
	{	TDX_ID_XT_LOGINEMAIL,		TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"��¼Email",			0,0,0,0,0,	},
	{	TDX_ID_XT_TRADEEMAIL,		TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"����Email",			0,0,0,0,0,	},
	{	TDX_ID_XT_MULTINITICE,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"����ʾ��Ϣ",			1,0,0,0,0,	},
	{	TDX_ID_XT_RISKPARAM,		TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"���ղ���",				1,0,0,0,0,	},
	{	TDX_ID_XT_LOGINRETURNPARAM,	TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"��¼���ز���",			1,0,0,0,0,	},
	{	TDX_ID_XT_MOBILEMACHINEINFO,TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"�ֻ�������Ϣ",			1,0,0,0,0,	},
	{	TDX_ID_XT_PACKAGELIST,		TDX_DT_STRING,	TDX_DISP_RIGHT,1024,	"�ײ��б�",				1,0,0,0,0,	},
	{	TDX_ID_XT_PRODUCTLIST,		TDX_DT_STRING,	TDX_DISP_RIGHT,1024,	"��Ʒ�б�",				1,0,0,0,0,	},
	{	TDX_ID_XT_FEATURELIST,		TDX_DT_STRING,	TDX_DISP_RIGHT,1024,	"�����б�",				1,0,0,0,0,	},
	{	TDX_ID_XT_CONFIGLIST,		TDX_DT_STRING,	TDX_DISP_RIGHT,1024,	"�����б�",				1,0,0,0,0,	},
	{	TDX_ID_XT_LOGINENTERPARAM,	TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"��¼�������",			1,0,0,0,0,	},
	{	TDX_ID_XT_ALGORIGHTLIST,	TDX_DT_STRING,	TDX_DISP_RIGHT,1024,	"�㷨Ȩ���б�",			1,0,0,0,0,	},
	{	TDX_ID_XT_FUNCTIONVERSION,	TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"���ܰ汾",				1,0,0,0,0,	},
	{	TDX_ID_XT_CLIENTINVERSION,	TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"�ͻ����ڲ��汾",		1,0,0,0,0,	},
	{	TDX_ID_XT_VERSIONSTRING,	TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"�汾�ַ���",			1,0,0,0,0,	},
};

// ��׼�ֵ��ֶζ���
const FIELDINFO tdxCommonFieldInfo[]=
{
//	{	�ֶ�����,					��������,		��ʾ(����)����,���,	�ֶ�˵��,				�������,	},

	{	TDX_ID_PARAM_YHSXX,			TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"(����)ӡ��˰����",		1,0,0,0,0,	},
	{	TDX_ID_PARAM_SXFXX,			TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"(����)����������",		1,0,0,0,0,	},
	{	TDX_ID_PARAM_GHFXX,			TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"(����)����������",		1,0,0,0,0,	},
	{	TDX_ID_PARAM_QTJEFXX,		TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"(����)������������",	1,0,0,0,0,	},
	{	TDX_ID_PARAM_QTSLFXX,		TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"(����)��������������",	1,0,0,0,0,	},
	{	TDX_ID_ZQJYBS,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"֤ȯ���ױ�ʶ",			1,0,0,0,0,	},
	{	TDX_ID_PARAM_CBJE,			TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"(����)�ɱ����",		1,0,0,0,0,	},
	{	TDX_ID_PARAM_CBSL,			TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"(����)�ɱ�����",		1,0,0,0,0,	},
	{	TDX_ID_PARAM_YHSL,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"(����)ӡ��˰��",		1,0,0,0,0,	},
	{	TDX_ID_PARAM_SXFL,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"(����)��������",		1,0,0,0,0,	},
	{	TDX_ID_PARAM_GHFL,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"(����)��������",		1,0,0,0,0,	},
	{	TDX_ID_PARAM_QTJEFL,		TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"(����)����������",	1,0,0,0,0,	},
	{	TDX_ID_PARAM_QTSLFL,		TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"(����)������������",	1,0,0,0,0,	},
	{	TDX_ID_FQSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"��������",				0,0,0,0,0,	},
	{	TDX_ID_MC,					TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"����",					0,0,0,0,0,	},

	{	TDX_ID_SCFLAG,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"����������",			1,0,0,0,0,	},
	{	TDX_ID_SCNAME,				TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"����������",			0,0,0,0,0,	},
	{	TDX_ID_YYB,					TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"Ӫҵ������",			0,0,0,0,0,	},
	{	TDX_ID_YYBMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,  40,	"Ӫҵ������",			0,0,0,0,0,	},
	{	TDX_ID_TDX_OEM_FLAG,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"OEM��־",				1,0,0,0,0,	},
	{	TDX_ID_JYYDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"����Ա����",			0,0,0,0,0,	},
	{	TDX_ID_LXRXM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"��ϵ������",			0,0,0,0,0,	},
	{	TDX_ID_LXFS,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"��ϵ��ʽ",				0,0,0,0,0,	},
	{	TDX_ID_NC,					TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"�ǳ�",					0,0,0,0,0,	},
	{	TDX_ID_LMQX,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"��ĿȨ��",				0,0,0,0,0,	},
	{	TDX_ID_OP_WTFS,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"ί�з�ʽ",				0,0,0,0,0,	},
	{	TDX_ID_OP_GYDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"��Ա����",				0,0,0,0,0,	},
	{	TDX_ID_OP_GYMM,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"��Ա����",				0,0,0,0,0,	},
	{	TDX_ID_CZBZ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"������־",				1,0,0,0,0,	},
	{	TDX_ID_CZZT,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"����״̬",				1,0,0,0,0,	},
	{	TDX_ID_HZHGZT,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"�����ع�״̬",			0,0,0,0,0,	},
	{	TDX_ID_ZDJYBZ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"ָ������",				0,0,0,0,0,	},
	{	TDX_ID_SQKTWZ,				TDX_DT_STRING,	TDX_DISP_RIGHT,  40,	"���뿪ͨ����ַ",		0,0,0,0,0,	},
	{	TDX_ID_HZHGDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"�����ع�����",			0,0,0,0,0,	},
	{	TDX_ID_HZPSDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"�������۴���",			0,0,0,0,0,	},
	{	TDX_ID_KHH,					TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"�ͻ���",				0,0,0,0,0,	},
	{	TDX_ID_ZJZH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"�ʽ��ʺ�",				0,0,0,0,0,	},
	{	TDX_ID_KHMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"�ͻ�����",				0,0,0,0,0,	},
	{	TDX_ID_GDDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"�ɶ�����",				0,0,0,0,0,	},
	{	TDX_ID_GDMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"�ɶ�����",				0,0,0,0,0,	},
	{	TDX_ID_ZHLB,				TDX_DT_STRING,	TDX_DISP_RIGHT,   2,	"�ʺ����",				1,0,0,0,0,	},
	{	TDX_ID_KSRQ,				TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"��ʼ����",				0,0,0,0,0,	},
	{	TDX_ID_ZZRQ,				TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"��ֹ����",				0,0,0,0,0,	},
	{	TDX_ID_USERPHONE,			TDX_DT_STRING,	TDX_DISP_RIGHT,  40,	"�û���ϵ��ʽ",			0,0,0,0,0,	},
	{	TDX_ID_USEREMAIL,			TDX_DT_STRING,	TDX_DISP_RIGHT,  40,	"�û�EMAIL",			0,0,0,0,0,	},
	{	TDX_ID_MMBZ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"������־",				1,0,0,0,0,	},
	{	TDX_ID_MMBZSM,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   8,	"������־",				0,0,0,0,0,	},
	{	TDX_ID_BZ,					TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"����",					0,0,0,0,0,	},
	{	TDX_ID_JYDW,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"���׵�λ",				0,0,0,0,0,	},
	{	TDX_ID_JYMM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"��������",				1,0,0,0,0,	},
	{	TDX_ID_ZJMM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"�ʽ�����",				1,0,0,0,0,	},
	{	TDX_ID_XJYMM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"�½�������",			1,0,0,0,0,	},
	{	TDX_ID_XZJMM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"���ʽ�����",			1,0,0,0,0,	},
	{	TDX_ID_TXMM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"ͨѶ����",				1,0,0,0,0,	},
	{	TDX_ID_SECURETYPE,			TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"��ȫ��ʽ",				0,0,0,0,0,	},
	{	TDX_ID_ZQDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"֤ȯ����",				0,0,0,0,0,	},
	{	TDX_ID_ZQMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"֤ȯ����",				0,0,0,0,0,	},
	{	TDX_ID_WTRQ,				TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"ί������",				0,0,0,0,0,	},
	{	TDX_ID_WTSJ,				TDX_DT_TIME,	TDX_DISP_RIGHT,   8,	"ί��ʱ��",				0,0,0,0,0,	},
	{	TDX_ID_WTSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"ί������",				0,0,0,0,0,	},
	{	TDX_ID_WTJG,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"ί�м۸�",				0,0,0,0,0,	},
	{	TDX_ID_WTBH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"ί�б��",				0,0,0,0,0,	},
	{	TDX_ID_ZTSM,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"״̬˵��",				0,0,0,0,0,	},
	{	TDX_ID_WTJE,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"ί�н��",				0,0,0,0,0,	},
	{	TDX_ID_RETINFO,				TDX_DT_STRING,	TDX_DISP_RIGHT,  80,	"������Ϣ",				0,0,0,0,0,	},
	{	TDX_ID_CJRQ,				TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"�ɽ�����",				0,0,0,0,0,	},
	{	TDX_ID_CJSJ,				TDX_DT_TIME,	TDX_DISP_RIGHT,   8,	"�ɽ�ʱ��",				0,0,0,0,0,	}, 
	{	TDX_ID_CJSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"�ɽ�����",				0,0,0,0,0,	},
	{	TDX_ID_CJJG,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"�ɽ��۸�",				0,0,0,0,0,	},
	{	TDX_ID_CJJE,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"�ɽ����",				0,0,0,0,0,	},
	{	TDX_ID_CJBH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"�ɽ����",				0,0,0,0,0,	},
	{	TDX_ID_HZPSZT,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"��������״̬",			1,0,0,0,0,	},
	{	TDX_ID_HFBZ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"�Ϸ���־",				1,0,0,0,0,	},
	{	TDX_ID_DFMM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"�Է�����",				1,0,0,0,0,	},
	{	TDX_ID_HFBZSM,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"�Ϸ���־",				0,0,0,0,0,	},
	{	TDX_ID_CDBZ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"������־",				1,0,0,0,0,	},
	{	TDX_ID_KCDBZ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"�ɳ�����־",			1,0,0,0,0,	},
	{	TDX_ID_LSH,					TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"��ˮ��",				0,0,0,0,0,	},
	{	TDX_ID_DJSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"��������",				0,0,0,0,0,	},
	{	TDX_ID_DJZJ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"�����ʽ�",				0,0,0,0,0,	},
	{	TDX_ID_CDSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"��������",				0,0,0,0,0,	},
	{	TDX_ID_CDBZSM,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"������־",				0,0,0,0,0,	},
	{	TDX_ID_LESSPRESSURE,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"�����̨ѹ��",			1,0,0,0,0,	},
	{	TDX_ID_FIRSTZJCX,			TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"��һ�β�ѯ�ʽ�",		1,0,0,0,0,	},
	{	TDX_ID_WTFS,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"ί�з�ʽ",				1,0,0,0,0,	},
	{	TDX_ID_PHRQ,				TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"�������",				0,0,0,0,0,	},
	{	TDX_ID_QSPH,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"��ʼ���",				0,0,0,0,0,	},
	{	TDX_ID_PHSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"�������",				0,0,0,0,0,	},
	{	TDX_ID_XWDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"ϯλ����",				0,0,0,0,0,	},
	{	TDX_ID_ZQS,					TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"��ǩ��",				0,0,0,0,0,	},
	{	TDX_ID_PHSLPHCX,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"�������",				0,0,0,0,0,	},
	{	TDX_ID_ZQRQ,				TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"��ǩ����",				0,0,0,0,0,	},
	{	TDX_ID_QZLX,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"Ȩ֤����",				0,0,0,0,0,	},
	{	TDX_ID_XQFS,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"��Ȩ��ʽ",				0,0,0,0,0,	},
	{	TDX_ID_XQBL,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"��Ȩ����",				0,0,0,0,0,	},
	{	TDX_ID_JSFS,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"���㷽ʽ",				0,0,0,0,0,	},
	{	TDX_ID_FXBZ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"���ձ�־",				0,0,0,0,0,	},
	{	TDX_ID_FXSM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  80,	"����˵��",				0,0,0,0,0,	},
	{	TDX_ID_JGRQ,				TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"��������",				0,0,0,0,0,	},
	{	TDX_ID_KHLBSM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  80,	"�ͻ����˵��",			0,0,0,0,0,	},
	{	TDX_ID_KHXZSM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  80,	"�ͻ�����˵��",			0,0,0,0,0,	},
	{	TDX_ID_KHZTSM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  80,	"�ͻ�״̬˵��",			0,0,0,0,0,	},
	{	TDX_ID_ZXJYGS,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"��С���׹���",			0,0,0,0,0,	},
	{	TDX_ID_SHGD,				TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"�Ϻ��ɶ�",				0,0,0,0,0,	},
	{	TDX_ID_SZGD,				TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"���ڹɶ�",				0,0,0,0,0,	},
	{	TDX_ID_QZKTBZ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"Ȩ֤��ͨ��־",			1,0,0,0,0,	},
	{	TDX_ID_SGRDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"�չ��˴���",			0,0,0,0,0,	},
	{	TDX_ID_YYSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"ҪԼ����",				0,0,0,0,0,	},
	{	TDX_ID_SBSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"�걨����",				0,0,0,0,0,	},
	{	TDX_ID_WTFSSM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  40,	"���۷�ʽ",				0,0,0,0,0,	},
	{	TDX_ID_XTXMM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"��ͨѶ����",			1,0,0,0,0,	},
	{	TDX_ID_DZDLX,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"���ʵ�����",			0,0,0,0,0,	},
	{	TDX_ID_XXSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"ѡ������",				0,0,0,0,0,	},
	{	TDX_ID_ZTSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"��;����",				0,0,0,0,0,	},

	{	TDX_ID_ZQSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"֤ȯ����",				0,0,0,0,0,	},
	{	TDX_ID_KMSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"��������",				0,0,0,0,0,	},
	{	TDX_ID_CBJ,					TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"�ɱ���",				0,0,0,0,0,	},
	{	TDX_ID_DQCB,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"��ǰ�ɱ�",				0,0,0,0,0,	},
	{	TDX_ID_ZXJ,					TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"���¼�",				0,0,0,0,0,	},
	{	TDX_ID_FDYK,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"����ӯ��",				0,0,0,0,0,	},
	{	TDX_ID_ZXSZ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"������ֵ",				0,0,0,0,0,	},
	{	TDX_ID_YJ,					TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"Ӷ��",					0,0,0,0,0,	},
	{	TDX_ID_KHF,					TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"������",				0,0,0,0,0,	},
	{	TDX_ID_CJF,					TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"�ɽ���",				0,0,0,0,0,	},
	{	TDX_ID_JSF,					TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"�����",				0,0,0,0,0,	},
	{	TDX_ID_YHS,					TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"ӡ��˰",				0,0,0,0,0,	},
	{	TDX_ID_ZDKM,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"������",				0,0,0,0,0,	},
	{	TDX_ID_SXF,					TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"������",				0,0,0,0,0,	},
	{	TDX_ID_GPLX,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"��Ʊ����",				0,0,0,0,0,	},
	{	TDX_ID_GTZDKMBS,			TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"ȡ��̨��������",		1,0,0,0,0,	},
	{	TDX_ID_DRMRSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"��������",				0,0,0,0,0,	},
	{	TDX_ID_GPLBP,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"��Ʊ�������",			0,0,0,0,0,	},
	{	TDX_ID_GPLBV,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"��Ʊ��������",			0,0,0,0,0,	},
	{	TDX_ID_GPLSP,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"��Ʊ��������",			0,0,0,0,0,	},
	{	TDX_ID_GPLSV,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"��Ʊ��������",			0,0,0,0,0,	},
	{	TDX_ID_KHQXDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"�ͻ�Ȩ�޴���",			0,0,0,0,0,	},
	{	TDX_ID_KHQXMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"�ͻ�Ȩ������",			0,0,0,0,0,	},
	{	TDX_ID_BBJ,					TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"������",				0,0,0,0,0,	},
	{	TDX_ID_YWTSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"ԭί������",			0,0,0,0,0,	},
	{	TDX_ID_YWTJG,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"ԭί�м۸�",			0,0,0,0,0,	},
	{	TDX_ID_QTF,					TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"������",				0,0,0,0,0,	},
	{	TDX_ID_ZXMRBDJW,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"��С����䶯��λ",		0,0,0,0,0,	},
	{	TDX_ID_ZXMCBDJW,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"��С�����䶯��λ",		0,0,0,0,0,	},
	{	TDX_ID_ZCZJZH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"ת���ʽ��ʺ�",			0,0,0,0,0,	},
	{	TDX_ID_ZRZJZH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"ת���ʽ��ʺ�",			0,0,0,0,0,	},
	{	TDX_ID_YKBL,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"ӯ������(%)",			0,0,0,0,0,	},
	{	TDX_ID_ZJZHEX,				TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"�ʽ��ʺ�",				0,0,0,0,0,	},
	{	TDX_ID_SXYK,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"ʵ��ӯ��",				0,0,0,0,0,	},
	{	TDX_ID_TBYK,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"̯��ӯ��",				0,0,0,0,0,	},
	{	TDX_ID_LX,					TDX_DT_DOUBLE,	TDX_DISP_RIGHT,   1,	"����",					0,0,0,0,0,	},
	{	TDX_ID_CJDF,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"�ɽ�����",				0,0,0,0,0,	},
	{	TDX_ID_WTDF,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"ί�е���",				0,0,0,0,0,	},
	{	TDX_ID_JJRDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"�����˴���",			0,0,0,0,0,	},
	{	TDX_ID_ZHZT,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"�ʻ�״̬",				0,0,0,0,0,	},
	{	TDX_ID_KGDBZ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"�ɸĵ���־",			1,0,0,0,0,	},
	{	TDX_ID_MAILADDRESS,			TDX_DT_STRING,	TDX_DISP_RIGHT,  80,	"�ʼĵ�ַ",				0,0,0,0,0,	},
	{	TDX_ID_YDXH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"Լ�����",				0,0,0,0,0,	},
	{	TDX_ID_DFXWDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"�Է�ϯλ����",			0,0,0,0,0,	},
	{	TDX_ID_DFZJZH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"�Է��ʽ��ʺ�",			0,0,0,0,0,	},
	{	TDX_ID_DFGDDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"�Է��ɶ�����",			0,0,0,0,0,	},
	{	TDX_ID_DFZHLB,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"�Է��ʺ����",			1,0,0,0,0,	},
	{	TDX_ID_ZZHBZ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"���ʺű�־",			1,0,0,0,0,	},
	{	TDX_ID_SBXH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"�걨���",				0,0,0,0,0,	},
	{	TDX_ID_LMDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"��Ŀ����",				0,0,0,0,0,	},
	{	TDX_ID_LMMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"��Ŀ����",				0,0,0,0,0,	},
	{	TDX_ID_TSXX0,				TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"��ʾ��Ϣ0",			0,0,0,0,0,	},
	{	TDX_ID_TSXX1,				TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"��ʾ��Ϣ1",			0,0,0,0,0,	},
	{	TDX_ID_TSXX2,				TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"��ʾ��Ϣ2",			0,0,0,0,0,	},
	{	TDX_ID_TSXX3,				TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"��ʾ��Ϣ3",			0,0,0,0,0,	},
	{	TDX_ID_TSXX4,				TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"��ʾ��Ϣ4",			0,0,0,0,0,	},
	{	TDX_ID_TSXX5,				TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"��ʾ��Ϣ5",			0,0,0,0,0,	},
	{	TDX_ID_TSXX6,				TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"��ʾ��Ϣ6",			0,0,0,0,0,	},
	{	TDX_ID_TSXX7,				TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"��ʾ��Ϣ7",			0,0,0,0,0,	},
	{	TDX_ID_TSXX8,				TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"��ʾ��Ϣ8",			0,0,0,0,0,	},
	{	TDX_ID_TSXX9,				TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"��ʾ��Ϣ9",			0,0,0,0,0,	},

	{	TDX_ID_ZJLS_FSRQ,			TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"��������",				0,0,0,0,0,	},
	{	TDX_ID_ZJLS_FSSJ,			TDX_DT_TIME,	TDX_DISP_RIGHT,   8,	"����ʱ��",				0,0,0,0,0,	},
	{	TDX_ID_ZJLS_YWDM,			TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"ҵ�����",				0,0,0,0,0,	},
	{	TDX_ID_ZJLS_YWMC,			TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"ҵ������",				0,0,0,0,0,	},
	{	TDX_ID_ZJLS_HBDM,			TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"���Ҵ���",				0,0,0,0,0,	},
	{	TDX_ID_ZJLS_FSJE,			TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"�������",				0,0,0,0,0,	},
	{	TDX_ID_ZJLS_SYJE,			TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"ʣ����",				0,0,0,0,0,	},
	{	TDX_ID_ZJLS_ZQDM,			TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"֤ȯ����",				0,0,0,0,0,	},
	{	TDX_ID_ZJLS_ZQMC,			TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"֤ȯ����",				0,0,0,0,0,	},
	{	TDX_ID_ZJLS_FSJG,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"�����۸�",				0,0,0,0,0,	},
	{	TDX_ID_ZJLS_FSSL,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"��������",				0,0,0,0,0,	},
	{	TDX_ID_ZJLS_SYSL,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"ʣ������",				0,0,0,0,0,	},
	{	TDX_ID_ZJLS_GDDM,			TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"�ɶ�����",				0,0,0,0,0,	},

	{	TDX_ID_DFBZ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"�Է�����",				0,0,0,0,0,	},
	{	TDX_ID_DQHL,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"��ǰ����",				0,0,0,0,0,	},
	{	TDX_ID_JYGF,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"���׹��",				0,0,0,0,0,	},
	{	TDX_ID_ZTZJ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"��;�ʽ�",				0,0,0,0,0,	},
	{	TDX_ID_OTCJYBS,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"OTC���ױ�־",			1,0,0,0,0,	},
	{	TDX_ID_XYJYBS,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"������ȯ��ʶ",			1,0,0,0,0,	},
	{	TDX_ID_SFCGBS,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"������ܱ�ʶ",			1,0,0,0,0,	},
	{	TDX_ID_ZZFS,				TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"ת�ʷ�ʽ",				0,0,0,0,0,	},
	{	TDX_ID_ZZQD,				TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"ת������",				0,0,0,0,0,	},
	{	TDX_ID_ZZBH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"ת�ʱ��",				0,0,0,0,0,	},
	{	TDX_ID_FPYH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"��Ʊ����",				0,0,0,0,0,	},
	{	TDX_ID_ZPBH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"֧Ʊ���",				0,0,0,0,0,	},
	{	TDX_ID_ZJCJSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"����ɽ�����",			0,0,0,0,0,	},
	{	TDX_ID_ZJCDSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"�����������",			0,0,0,0,0,	},
	{	TDX_ID_KHBS,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"�ͻ���ʶ",				0,0,0,0,0,	},
	{	TDX_ID_ZDDM,				TDX_DT_SHORT,	TDX_DISP_RIGHT,   4,	"�ֶδ���",				0,0,0,0,0,	},
	{	TDX_ID_ZDQZ,				TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"�ֶ�ȡֵ",				0,0,0,0,0,	},
	{	TDX_ID_YLXX,				TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"Ԥ����Ϣ",				0,0,0,0,0,	},
	{	TDX_ID_FJZH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"�����˺�",				0,0,0,0,0,	},
	{	TDX_ID_XYJYTSXX,			TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"���ý�����ʾ��Ϣ",		0,0,0,0,0,	},
	{	TDX_ID_JZC,					TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"���ʲ�",				0,0,0,0,0,	},
	{	TDX_ID_SGKYS,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"�깺������",			0,0,0,0,0,	},
	{	TDX_ID_DFKHDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"�Է��ͻ�����",			0,0,0,0,0,	},
	{	TDX_ID_DFFZDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"�Է���֧����",			0,0,0,0,0,	},

	{	TDX_ID_ZJYE,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"�ʽ����",				0,0,0,0,0,	},
	{	TDX_ID_KYZJ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"�����ʽ�",				0,0,0,0,0,	},
	{	TDX_ID_KQZJ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"��ȡ�ʽ�",				0,0,0,0,0,	},
	{	TDX_ID_OCCURJE,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"�������",				0,0,0,0,0,	},
	{	TDX_ID_POSTJE,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"ʣ����",				0,0,0,0,0,	},
	{	TDX_ID_ZY,					TDX_DT_STRING,	TDX_DISP_RIGHT,  40,	"ժҪ",					0,0,0,0,0,	},
	{	TDX_ID_YWMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"ҵ������",				0,0,0,0,0,	},
	{	TDX_ID_YWDM,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"ҵ�����",				1,0,0,0,0,	},
	{	TDX_ID_MRDJZJ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"���붳���ʽ�",			0,0,0,0,0,	},
	{	TDX_ID_YZT_YHXZTS,			TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"��ʾѡ�����б�־",		1,0,0,0,0,	},
	{	TDX_ID_GTZZC,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"���ʲ�",				0,0,0,0,0,	},
	{	TDX_ID_CJLX,				TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"�ɽ�����",				0,0,0,0,0,	},
	{	TDX_ID_JYDJZJ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"���׶���",				0,0,0,0,0,	},
	{	TDX_ID_YCDJZJ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"�쳣����",				0,0,0,0,0,	},
	{	TDX_ID_ZTKYZJ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"��;����",				0,0,0,0,0,	},
	{	TDX_ID_XJKQZJ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"��ȡ�ֽ�",				0,0,0,0,0,	},
	{	TDX_ID_ZPKQZJ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"��ȡ֧Ʊ",				0,0,0,0,0,	},
	{	TDX_ID_KZZJ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"��ת�ʽ�",				0,0,0,0,0,	},
	{	TDX_ID_LXJE,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"��Ϣ",					0,0,0,0,0,	},
	{	TDX_ID_LXS,					TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"��Ϣ˰",				0,0,0,0,0,	},
	{	TDX_ID_SYSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"ʣ������",				0,0,0,0,0,	},
	{	TDX_ID_FJF,					TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"���ӷ�",				0,0,0,0,0,	},
	{	TDX_ID_SXJE,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"������",				0,0,0,0,0,	},
	{	TDX_ID_MMCB,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"�����ɱ�",				0,0,0,0,0,	},
	{	TDX_ID_MRCB,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"����ɱ�",				0,0,0,0,0,	},
	{	TDX_ID_ZGF,					TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"֤�ܷ�",				0,0,0,0,0,	},
	{	TDX_ID_FCJL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"�ֲֻ���",				0,0,0,0,0,	},
	{	TDX_ID_ZYK,					TDX_DT_FLOAT,	TDX_DISP_RIGHT,   6,	"��ӯ��",				0,0,0,0,0,	},
	{	TDX_ID_TBCBJ,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   6,	"̯���ɱ���",			0,0,0,0,0,	},
	{	TDX_ID_TBBBJ,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   6,	"̯��������",			0,0,0,0,0,	},
	{	TDX_ID_TBFDYK,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   6,	"̯������ӯ��",			0,0,0,0,0,	},
	{	TDX_ID_FADM,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"��������",				0,0,0,0,0,	},
	{	TDX_ID_FAMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"��������",				0,0,0,0,0,	},
	{	TDX_ID_FALX,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"��������",				0,0,0,0,0,	},
	{	TDX_ID_TPDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"ͶƱ����",				0,0,0,0,0,	},
	{	TDX_ID_TPJG,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"ͶƱ���",				0,0,0,0,0,	},
	{	TDX_ID_CFDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"�ɷִ���",				0,0,0,0,0,	},
	{	TDX_ID_CFMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"�ɷ�����",				0,0,0,0,0,	},
	{	TDX_ID_CFQZ,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"�ɷ�Ȩ��(%)",			0,0,0,0,0,	},
	{	TDX_ID_MRXX,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"Ĭ��ѡ��",				0,0,0,0,0,	},
	{	TDX_ID_XXNR0,				TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"ѡ������0",			0,0,0,0,0,	},
	{	TDX_ID_XXNR1,				TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"ѡ������1",			0,0,0,0,0,	},
	{	TDX_ID_XXNR2,				TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"ѡ������2",			0,0,0,0,0,	},
	{	TDX_ID_XXNR3,				TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"ѡ������3",			0,0,0,0,0,	},
	{	TDX_ID_XXNR4,				TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"ѡ������4",			0,0,0,0,0,	},
	{	TDX_ID_XXNR5,				TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"ѡ������5",			0,0,0,0,0,	},
	{	TDX_ID_XXNR6,				TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"ѡ������6",			0,0,0,0,0,	},
	{	TDX_ID_XXNR7,				TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"ѡ������7",			0,0,0,0,0,	},
	{	TDX_ID_XXNR8,				TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"ѡ������8",			0,0,0,0,0,	},
	{	TDX_ID_XXNR9,				TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"ѡ������9",			0,0,0,0,0,	},
	{	TDX_ID_ZZC,					TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"���ʲ�",				0,0,0,0,0,	},
	{	TDX_ID_SYL,					TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"������",				0,0,0,0,0,	},
	{	TDX_ID_HYZS,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"��Ծָ��",				0,0,0,0,0,	},
	{	TDX_ID_RMBZZC,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"��������ʲ�",			0,0,0,0,0,	},
	{	TDX_ID_MYZZC,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"��Ԫ���ʲ�",			0,0,0,0,0,	},
	{	TDX_ID_GYZZC,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"��Ԫ���ʲ�",			0,0,0,0,0,	},
	{	TDX_ID_SYLTJRQ,				TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"������ͳ������",		0,0,0,0,0,	},
	{	TDX_ID_SYLTJSJ,				TDX_DT_TIME,	TDX_DISP_RIGHT,   8,	"������ͳ��ʱ��",		0,0,0,0,0,	},
	{	TDX_ID_ZZHZYE,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"���˺������",			0,0,0,0,0,	},
	{	TDX_ID_HGJE,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"�ع����",				0,0,0,0,0,	},
	{	TDX_ID_MOCK_ZHTYPE,			TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"�˺�����",				0,0,0,0,0,	},

	{	TDX_ID_RQSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"��ȯ����",				0,0,0,0,0,	},
	{	TDX_ID_RQJG,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"��ȯ�۸�",				0,0,0,0,0,	},
	{	TDX_ID_RQZQ,				TDX_DT_SHORT,	TDX_DISP_RIGHT,   4,	"��ȯ����",				0,0,0,0,0,	},
	{	TDX_ID_RQCZLX,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"��ȯ��������",			0,0,0,0,0,	},
	{	TDX_ID_RQRQ,				TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"��ȯ����",				0,0,0,0,0,	},
	{	TDX_ID_RQSJ,				TDX_DT_TIME,	TDX_DISP_RIGHT,   8,	"��ȯʱ��",				0,0,0,0,0,	},
	{	TDX_ID_HTBH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"��ͬ���",				0,0,0,0,0,	},
	{	TDX_ID_JDJSJET,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"�������ս��(T��)",	0,0,0,0,0,	},
	{	TDX_ID_JDJSJET1,			TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"�������ս��(T+1��)",	0,0,0,0,0,	},
	{	TDX_ID_JDJSJET2,			TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"�������ս��(T+2��)",	0,0,0,0,0,	},
	{	TDX_ID_ZPDJSJE,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"֧Ʊ�����ս��",		0,0,0,0,0,	},
	{	TDX_ID_XYSZ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"������ֵ",				0,0,0,0,0,	},
	{	TDX_ID_GJBZQGML,			TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"�߼���֤ȯ������",		0,0,0,0,0,	},
	{	TDX_ID_XYGJBZQGML,			TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"���ø߼���֤ȯ������",	0,0,0,0,0,	},
	{	TDX_ID_DJBZQGML,			TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"�ͼ���֤ȯ������",		0,0,0,0,0,	},
	{	TDX_ID_XYDJBZQGML,			TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"���õͼ���֤ȯ������",	0,0,0,0,0,	},
	{	TDX_ID_YXSBCS,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"��Чʧ�ܴ���",			0,0,0,0,0,	},
	{	TDX_ID_SFFSSM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"�շѷ�ʽ",				0,0,0,0,0,	},
	{	TDX_ID_CPJZ,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"��Ʒ��ֵ",				0,0,0,0,0,	},
	{	TDX_ID_LCZH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"����˻�",				0,0,0,0,0,	},
	{	TDX_ID_CPDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"��Ʒ����",				0,0,0,0,0,	},
	{	TDX_ID_CPMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"��Ʒ����",				0,0,0,0,0,	},
	{	TDX_ID_CPGSDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"��Ʒ��˾����",			0,0,0,0,0,	},
	{	TDX_ID_CPGSMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"��Ʒ��˾����",			0,0,0,0,0,	},
	{	TDX_ID_CPZT,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"��Ʒ״̬",				1,0,0,0,0,	},
	{	TDX_ID_QRJZ,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"ǰ�վ�ֵ",				0,0,0,0,0,	},
	{	TDX_ID_CPBZ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"��Ʒ��־",				1,0,0,0,0,	},	
	{	TDX_ID_KTBZ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"��ͨ��־",				1,0,0,0,0,	},
	{	TDX_ID_KFSJJ_LJJZ,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"�ۼƾ�ֵ",				0,0,0,0,0,	},

	{	TDX_ID_KFSJJ_MMBZ,			TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"���ױ�־",				1,0,0,0,0,	},
	{	TDX_ID_KFSJJ_JJGSMC,		TDX_DT_STRING,	TDX_DISP_RIGHT,   1,	"����˾����",			0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_JJDM,			TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"�������",				0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_JJMC,			TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"��������",				0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_JJFE,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"����ݶ�",				0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_JYJE,			TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"���׽��",				0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_JJJZ,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"����ֵ",				0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_ZHDM,			TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"����ת������",			0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_DIVIDENMETHOD,	TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"����ֺ췽ʽ",			0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_FSRQ,			TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"��������",				0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_KYFE,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"���÷ݶ�",				0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_JJBS,			TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"����ʽ�����ʶ",		1,0,0,0,0,	},
	{	TDX_ID_KFSJJ_QSSL,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"��ʼ����",				0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_DQSL,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"��ǰ����",				0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_WTFE,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"ί�зݶ�",				0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_CJFE,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"�ɽ��ݶ�",				0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_CJJE,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"�ɽ����",				0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_JJZH,			TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"�����ʻ�",				0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_FXJG,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"���м۸�",				0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_GRZDRGJE,		TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"��������Ϲ����",		0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_FRZDRGJE,		TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"��������Ϲ����",		0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_ZDCYFE,		TDX_DT_LONG,	TDX_DISP_RIGHT,  12,	"��ͳ��зݶ�",			0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_ZGSHFE,		TDX_DT_LONG,	TDX_DISP_RIGHT,  12,	"�����طݶ�",			0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_GRZGCYBL,		TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"������߳��б���",		0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_FRZGCYBL,		TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"������߳��б���",		0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_JJZT,			TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"����״̬",				1,0,0,0,0,	},
	{	TDX_ID_KFSJJ_JJGSDM,		TDX_DT_SHORT,	TDX_DISP_RIGHT,   4,	"����˾����",			0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_FXZS,			TDX_DT_LONG,	TDX_DISP_RIGHT,  12,	"��������",				0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_ZDSHFE,		TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"�����طݶ�",			0,0,0,0,0,	},
	{	TDX_ID_SFFS,				TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"�շѷ�ʽ",				1,0,0,0,0,	},
	{	TDX_ID_KFSJJ_JGZGBL,		TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"������߱���",			0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_GRZGBL,		TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"������߱���",			0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_GRZGRGZJ,		TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"��������Ϲ����",		0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_FRZGRGZJ,		TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"��������Ϲ����",		0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_GRSCSGZDZJ,	TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"�����״��깺����ʽ�",	0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_FRSCSGZDZJ,	TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"�����״��깺����ʽ�",	0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_GRZJSGZDZJ,	TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"����׷���깺����ʽ�",	0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_FRZJSGZDZJ,	TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"����׷���깺����ʽ�",	0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_GRJJZSSHFE,	TDX_DT_LONG,	TDX_DISP_RIGHT,  12,	"���˻���������طݶ�",	0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_FRJJZSSHFE,	TDX_DT_LONG,	TDX_DISP_RIGHT,  12,	"���˻���������طݶ�",	0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_GRJJZSZHFE,	TDX_DT_LONG,	TDX_DISP_RIGHT,  12,	"���˻�������ת���ݶ�",	0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_FRJJZSZHFE,	TDX_DT_LONG,	TDX_DISP_RIGHT,  12,	"���˻�������ת���ݶ�",	0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_TADM,			TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"TA ����",				0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_GTGSBZ,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"�����̨��˾��־",		1,0,0,0,0,	},
	{	TDX_ID_KFSJJ_FHFSDM,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"�ֺ췽ʽ����",			1,0,0,0,0,	},
	{	TDX_ID_KFSJJ_FHFSMC,		TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"�ֺ췽ʽ����",			0,0,0,0,0,	},
	{	TDX_ID_LSDJ,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"��ʱ����",				0,0,0,0,0,	},
	{	TDX_ID_MCWTSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"��������",				0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_PZDM,			TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"Ʒ�ִ���",				0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_MYKKRQ,		TDX_DT_SHORT,	TDX_DISP_RIGHT,   2,	"ÿ�¿ۿ�����",			0,0,0,0,0,	},
	{	TDX_ID_KHTYPE,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"�������",				0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_DQSGNS,		TDX_DT_SHORT,	TDX_DISP_RIGHT,   4,	"�깺����",				0,0,0,0,0,	},
	{	TDX_ID_ZJLB,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"֤�����",				0,0,0,0,0,	},
	{	TDX_ID_JYZH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"�����ʻ�",				0,0,0,0,0,	},
	{	TDX_ID_ZJHM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"֤������",				0,0,0,0,0,	},
	{	TDX_ID_MOBILEPHONE,			TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"�ƶ��绰",				0,0,0,0,0,	},
	{	TDX_ID_HOMEPHONE,			TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"סլ�绰",				0,0,0,0,0,	},
	{	TDX_ID_FAX,					TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"����",					0,0,0,0,0,	},
	{	TDX_ID_EDU,					TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"�����̶�",				0,0,0,0,0,	},
	{	TDX_ID_SALARY,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"������",				0,0,0,0,0,	},
	{	TDX_ID_XLYZT_DLSGFLAG,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"�����깺��־",			0,0,0,0,0,	},
	{	TDX_ID_XLYZT_DLPGFLAG,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"������ɱ�־",			0,0,0,0,0,	},
	{	TDX_ID_XLYZT_DLPSFLAG,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"�������۱�־",			0,0,0,0,0,	},
	{	TDX_ID_WORKPHONE,			TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"��λ�绰",				0,0,0,0,0,	},
	{	TDX_ID_NAME,				TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"����",					0,0,0,0,0,	},
	{	TDX_ID_VOCATION,			TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"ְҵ",					0,0,0,0,0,	},
	{	TDX_ID_FHBZ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"�ֺ��־",				0,0,0,0,0,	},
	{	TDX_ID_DZDBZ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"���ʵ���־",			0,0,0,0,0,	},
	{	TDX_ID_SHFS,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"��ط�ʽ",				0,0,0,0,0,	},
	{	TDX_ID_FHBL,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"�ֺ����",				0,0,0,0,0,	},
	{	TDX_ID_FHRQ,				TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"�ֺ�����",				0,0,0,0,0,	},
	{	TDX_ID_FHJE,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"�ֺ���",				0,0,0,0,0,	},
	{	TDX_ID_FHSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"�ֺ�����",				0,0,0,0,0,	},
	{	TDX_ID_MGFHJE,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"ÿ�ɷֺ���",			0,0,0,0,0,	},
	{	TDX_ID_ZDBZ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"ָ����־",				0,0,0,0,0,	},
	{	TDX_ID_FHFS,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"�ֺ췽ʽ",				0,0,0,0,0,	},
	{	TDX_ID_KHRQ,				TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"��������",				0,0,0,0,0,	},
	{	TDX_ID_KHQC,				TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"�ͻ�ȫ��",				0,0,0,0,0,	},
	{	TDX_ID_BPCALL,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"Ѱ������",				0,0,0,0,0,	},
	{	TDX_ID_ZBDLJYXX,			TDX_DT_STRING,	TDX_DISP_RIGHT,1024,	"�ܱߵ�¼У����Ϣ",		0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_JGZDTZ,		TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"�������Ͷ��",			0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_GRZDTZ,		TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"�������Ͷ��",			0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_JGZDZJ,		TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"�������׷��",			0,0,0,0,0,	},
	{	TDX_ID_KFSJJ_GRZDZJ,		TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"�������׷��",			0,0,0,0,0,	},
	{	TDX_ID_SPEL_GX_HZXGSGZT,	TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"�����¹��깺",			0,0,0,0,0,	},
	{	TDX_ID_TJRDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"�Ƽ��˴���",			0,0,0,0,0,	},
	{	TDX_ID_PROVINCE,			TDX_DT_STRING,	TDX_DISP_RIGHT,  10,	"ʡ��",					0,0,0,0,0,	},
	{	TDX_ID_CITY,				TDX_DT_STRING,	TDX_DISP_RIGHT,  20,	"����",					0,0,0,0,0,	},
	{	TDX_ID_SECTION,				TDX_DT_STRING,	TDX_DISP_RIGHT,  20,	"Ͻ��",					0,0,0,0,0,	},
	{	TDX_ID_IDADDRESS,			TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"֤����ַ",				0,0,0,0,0,	},
	{	TDX_ID_FRDBXM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"���˴�������",			0,0,0,0,0,	},
	{	TDX_ID_FRDBZJLX,			TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"���˴���֤������",		0,0,0,0,0,	},
	{	TDX_ID_FRDBZJHM,			TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"���˴���֤������",		0,0,0,0,0,	},
	{	TDX_ID_LXRZJLX,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"��ϵ��֤������",		0,0,0,0,0,	},
	{	TDX_ID_LXRZJHM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"��ϵ��֤������",		0,0,0,0,0,	},
	{	TDX_ID_LXRDH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"��ϵ�˵绰",			0,0,0,0,0,	},
	{	TDX_ID_DZDJSFS,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"���ʵ����ͷ�ʽ",		0,0,0,0,0,	},
	{	TDX_ID_JJDTBZ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"����Ͷ��־",			0,0,0,0,0,	},
	{	TDX_ID_XSRDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"�����˴���",			0,0,0,0,0,	},
	{	TDX_ID_XSRMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"����������",			0,0,0,0,0,	},

	{	TDX_ID_QHZHBS,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"�ڻ��˺ű�ʶ",			0,0,0,0,0,	},
	{	TDX_ID_QHZH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"�ڻ��˺�",				0,0,0,0,0,	},
	{	TDX_ID_HYDM1,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32 ,	"��Լ����1",			0,0,0,0,0,	},
	{	TDX_ID_HYDM2,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32 ,	"��Լ����2",			0,0,0,0,0,	},
	{	TDX_ID_HYDM3,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32 ,	"��Լ����3",			0,0,0,0,0,	},
	{	TDX_ID_HYDM4,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32 ,	"��Լ����4",			0,0,0,0,0,	},
	{	TDX_ID_HYMC1,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32 ,	"��Լ����1",			0,0,0,0,0,	},
	{	TDX_ID_HYMC2,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32 ,	"��Լ����2",			0,0,0,0,0,	},
	{	TDX_ID_HYMC3,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32 ,	"��Լ����3",			0,0,0,0,0,	},
	{	TDX_ID_HYMC4,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32 ,	"��Լ����4",			0,0,0,0,0,	},
	{	TDX_ID_HYDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"��Լ����",				0,0,0,0,0,	},
	{	TDX_ID_HYMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"��Լ����",				0,0,0,0,0,	},
	{	TDX_ID_PZ,					TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"Ʒ��",					0,0,0,0,0,	},
	{	TDX_ID_KPBZ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"��ƽ��־",				1,0,0,0,0,	},
	{	TDX_ID_TBBZ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"Ͷ����־",				1,0,0,0,0,	},
	{	TDX_ID_JKCFLAG,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"��ֱ�־",				0,0,0,0,0,	},
	{	TDX_ID_CJSX,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"�ɽ�����",				1,0,0,0,0,	},
	{	TDX_ID_CJSXSM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"�ɽ�����˵��",			0,0,0,0,0,	},
	{	TDX_ID_ZHLX,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"�������",				0,0,0,0,0,	},
	{	TDX_ID_ZHLXSM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"�������˵��",			0,0,0,0,0,	},
	{	TDX_ID_KCJG,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"���ּ�",				0,0,0,0,0,	},
	{	TDX_ID_CCSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"�ֲ���",				0,0,0,0,0,	},
	{	TDX_ID_KCRQ,				TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"��������",				0,0,0,0,0,	},
	{	TDX_ID_CJJJ,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"�ɽ�����",				0,0,0,0,0,	},
	{	TDX_ID_CBJJ,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"�ɱ�����",				0,0,0,0,0,	},
	{	TDX_ID_BZJJE,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"��֤��",				0,0,0,0,0,	},
	{	TDX_ID_SXFJE,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"������",				0,0,0,0,0,	},
	{	TDX_ID_MRJJ,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"�����",				0,0,0,0,0,	},
	{	TDX_ID_CCJJ,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"�ֲ־���",				0,0,0,0,0,	},
	{	TDX_ID_ZHTS,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"�������",				0,0,0,0,0,	},
	{	TDX_ID_DJBZJ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"���ᱣ֤��",			0,0,0,0,0,	},
	{	TDX_ID_QCZJ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"�ڳ��ʽ�",				0,0,0,0,0,	},
	{	TDX_ID_KHQYZJ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"�ͻ�Ȩ���ʽ�",			0,0,0,0,0,	},
	{	TDX_ID_KKCSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"�ɿ�������",			0,0,0,0,0,	},
	{	TDX_ID_KPCSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"��ƽ������",			0,0,0,0,0,	},
	{	TDX_ID_KPJSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"��ƽ������",			0,0,0,0,0,	},
	{	TDX_ID_ZHHYDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"��Ϻ�Լ����",			0,0,0,0,0,	},
	{	TDX_ID_ZHHYMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"��Ϻ�Լ����",			0,0,0,0,0,	},
	{	TDX_ID_CFJG,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"�����۸�",				0,0,0,0,0,	},
	{	TDX_ID_MZL,					TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"������",				0,0,0,0,0,	},
	{	TDX_ID_JGY,					TDX_DT_SHORT,	TDX_DISP_RIGHT,   4,	"�����·�",				0,0,0,0,0,	},
	{	TDX_ID_BZJ,					TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"��֤��",				0,0,0,0,0,	},
	{	TDX_ID_QHJYDW,				TDX_DT_SHORT,	TDX_DISP_RIGHT,   4,	"���׵�λ",				0,0,0,0,0,	},
	{	TDX_ID_QHBJDW,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"���۵�λ",				0,0,0,0,0,	},
	{	TDX_ID_ZXBDJW,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"��С�䶯��λ",			0,0,0,0,0,	},
	{	TDX_ID_JGBDFD,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"�۸񲨶�����",			0,0,0,0,0,	},
	{	TDX_ID_BZJBL,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"��֤�����",			0,0,0,0,0,	},

	{	TDX_ID_QHHQ_KCL,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"������",				0,0,0,0,0,	},
	{	TDX_ID_QHHQ_CCL,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"�ֲ���",				0,0,0,0,0,	},
	{	TDX_ID_QHHQ_QJS,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"ǰ����",				0,0,0,0,0,	},
	{	TDX_ID_QHHQ_ZS,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"����",					0,0,0,0,0,	},

	{	TDX_ID_GGZHBS,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"�۹��˺ű�ʶ",			1,0,0,0,0,	},

	{	TDX_ID_ETFBS,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"ETF��ʶ",				0,0,0,0,0,	},
	{	TDX_ID_ETFDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"ETF����",				0,0,0,0,0,	},
	{	TDX_ID_ETFMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"ETF����",				0,0,0,0,0,	},
	{	TDX_ID_ETFMMBS,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"��������",				0,0,0,0,0,	},
	{	TDX_ID_ETFRGSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"�Ϲ�����",				0,0,0,0,0,	},
	{	TDX_ID_ETFRGJE,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"�Ϲ����",				0,0,0,0,0,	},
	{	TDX_ID_PCH,					TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"���κ�",				0,0,0,0,0,	},
	{	TDX_ID_ETFXJTDMZ,			TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"�����־",				0,0,0,0,0,	},
	{	TDX_ID_ETFYJBL,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"��۱���",				0,0,0,0,0,	},
	{	TDX_ID_ETFXJTDJE,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"�ֽ�������",			0,0,0,0,0,	},
	{	TDX_ID_QSRQ,				TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"��������",				0,0,0,0,0,	},
	{	TDX_ID_CLDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"���Դ���",				0,0,0,0,0,	},
	{	TDX_ID_CLMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"��������",				0,0,0,0,0,	},
	{	TDX_ID_ZSDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"ָ������",				0,0,0,0,0,	},
	{	TDX_ID_ZSMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"ָ������",				0,0,0,0,0,	},
	{	TDX_ID_CDDDSJ,				TDX_DT_SHORT,	TDX_DISP_RIGHT,   4,	"�����ȴ�ʱ��",			0,0,0,0,0,	},
	{	TDX_ID_WTDDSJ,				TDX_DT_SHORT,	TDX_DISP_RIGHT,   4,	"ί�еȴ�ʱ��",			0,0,0,0,0,	},
	{	TDX_ID_WTCS,				TDX_DT_SHORT,	TDX_DISP_RIGHT,   4,	"ί�д���",				0,0,0,0,0,	},
	{	TDX_ID_JGBZ,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"�۸��־",				0,0,0,0,0,	},
	{	TDX_ID_ZDCD,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"�Զ�����",				0,0,0,0,0,	},
	{	TDX_ID_CFSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"�ɷ�����",				0,0,0,0,0,	},
	{	TDX_ID_KCSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"�������",				0,0,0,0,0,	},
	{	TDX_ID_BLSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"��������",				0,0,0,0,0,	},
	{	TDX_ID_XJBZ,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"�ֽ��־",				0,0,0,0,0,	},
	{	TDX_ID_JSBZ,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"������־",				0,0,0,0,0,	},
	{	TDX_ID_CJZT,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"�ɽ�״̬",				0,0,0,0,0,	},
	{	TDX_ID_XJTDSM,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"�ֽ����",				0,0,0,0,0,	},
	{	TDX_ID_QKSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"ȱ������",				0,0,0,0,0,	},
	{	TDX_ID_XYZJ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"��Ҫ�ʽ�",				0,0,0,0,0,	},
	{	TDX_ID_ZRKC,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"���տ��",				0,0,0,0,0,	},
	{	TDX_ID_JRMRJE,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"������",				0,0,0,0,0,	},
	{	TDX_ID_JRMCSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"��������",				0,0,0,0,0,	},
	{	TDX_ID_JRMCJE,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"�������",				0,0,0,0,0,	},
	{	TDX_ID_MBFE,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"Ŀ��ݶ�",				0,0,0,0,0,	},
	{	TDX_ID_KSSJ,				TDX_DT_TIME,	TDX_DISP_RIGHT,   8,	"��ʼʱ��",				0,0,0,0,0,	},
	{	TDX_ID_ZZSJ,				TDX_DT_TIME,	TDX_DISP_RIGHT,   8,	"��ֹʱ��",				0,0,0,0,0,	},
	{	TDX_ID_CSWTSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"��ʼί������",			0,0,0,0,0,	},
	{	TDX_ID_ZWTCS,				TDX_DT_SHORT,	TDX_DISP_RIGHT,   4,	"��ί�д���",			0,0,0,0,0,	},
	{	TDX_ID_ZHDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"��ϴ���",				0,0,0,0,0,	},
	{	TDX_ID_ZHMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"�������",				0,0,0,0,0,	},
	{	TDX_ID_KZYHZHBM,			TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"��չ�����˻�����",		0,0,0,0,0,	},
	{	TDX_ID_KZYHZHBM1,			TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"��չ�����˻�����1",	0,0,0,0,0,	},
	{	TDX_ID_KZYHZHBM2,			TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"��չ�����˻�����2",	0,0,0,0,0,	},
	{	TDX_ID_KZYHZHBM3,			TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"��չ�����˻�����3",	0,0,0,0,0,	},
	{	TDX_ID_KZYHZHBM4,			TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"��չ�����˻�����4",	0,0,0,0,0,	},
	{	TDX_ID_KZYHZHMC,			TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"��չ�����˻�����",		0,0,0,0,0,	},
	{	TDX_ID_KZYHZHMC1,			TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"��չ�����˻�����1",	0,0,0,0,0,	},
	{	TDX_ID_KZYHZHMC2,			TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"��չ�����˻�����2",	0,0,0,0,0,	},
	{	TDX_ID_KZYHZHMC3,			TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"��չ�����˻�����3",	0,0,0,0,0,	},
	{	TDX_ID_KZYHZHMC4,			TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"��չ�����˻�����4",	0,0,0,0,0,	},
	{	TDX_ID_DJGSDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"�Ǽǹ�˾����",			0,0,0,0,0,	},
	{	TDX_ID_DJGSJC,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"�Ǽǹ�˾���",			0,0,0,0,0,	},
	{	TDX_ID_DJGSQC,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"�Ǽǹ�˾ȫ��",			0,0,0,0,0,	},
	{	TDX_ID_QZFS,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"Ȩ�ط�ʽ",				1,0,0,0,0,	},
	{	TDX_ID_DWSZ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"��λ��ֵ",				0,0,0,0,0,	},
	{	TDX_ID_XHZH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"�ֻ��˺�",				0,0,0,0,0,	},
	{	TDX_ID_XHZHLX,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"�ֻ��˺�����",			1,0,0,0,0,	},
	{	TDX_ID_PCHLX,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"���κ�����",			1,0,0,0,0,	},
	{	TDX_ID_DKBZ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"��ձ�־",				1,0,0,0,0,	},
	{	TDX_ID_TZSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"Ͷ������",				0,0,0,0,0,	},
	{	TDX_ID_BJFS,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"���۷�ʽ",				1,0,0,0,0,	},
	{	TDX_ID_DFBJFS,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"�Է����۷�ʽ",			1,0,0,0,0,	},
	{	TDX_ID_SYKCBJ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"ʹ�ÿ����",			1,0,0,0,0,	},
	{	TDX_ID_SYFZXHBJ,			TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"ʹ�ø����ֻ����",		1,0,0,0,0,	},
	{	TDX_ID_MCYGBJ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"������ɱ��",			1,0,0,0,0,	},
	{	TDX_ID_ZDWTBJ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"�Զ�ί�б��",			1,0,0,0,0,	},
	{	TDX_ID_ZDWTCS,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"�Զ�ί�д���",			0,0,0,0,0,	},
	{	TDX_ID_PCHRQ,				TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"���κ�����",			0,0,0,0,0,	},
	{	TDX_ID_JC,					TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"����",					0,0,0,0,0,	},
	{	TDX_ID_MRJEJSJZ,			TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"����������׼",		1,0,0,0,0,	},
	{	TDX_ID_MRJE,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"������",				1,0,0,0,0,	},
	{	TDX_ID_FZXHDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"�����ֻ�����",			0,0,0,0,0,	},
	{	TDX_ID_FZXHMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"�����ֻ�����",			0,0,0,0,0,	},
	{	TDX_ID_PDDM1,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"��Դ���1",			0,0,0,0,0,	},
	{	TDX_ID_PDMC1,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"�������1",			0,0,0,0,0,	},
	{	TDX_ID_PDDM2,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"��Դ���2",			0,0,0,0,0,	},
	{	TDX_ID_PDMC2,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"�������2",			0,0,0,0,0,	},
	{	TDX_ID_PDBL,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"��Ա���",				0,0,0,0,0,	},
	{	TDX_ID_JCRQ,				TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"��������",				0,0,0,0,0,	},
	{	TDX_ID_JCJG1,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"���ּ۸�1",			0,0,0,0,0,	},
	{	TDX_ID_JCSL1,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"��������1",			0,0,0,0,0,	},
	{	TDX_ID_JCBH1,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"���ֱ��1",			0,0,0,0,0,	},
	{	TDX_ID_JCJG2,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"���ּ۸�2",			0,0,0,0,0,	},
	{	TDX_ID_JCSL2,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"��������2",			0,0,0,0,0,	},
	{	TDX_ID_JCBH2,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"���ֱ��2",			0,0,0,0,0,	},

	{	TDX_ID_FXD,					TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"���ն�",				0,0,0,0,0,	},
	{	TDX_ID_KHAQLB,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"�ͻ���ȫ���",			0,0,0,0,0,	},
	{	TDX_ID_KHAQLBSM,			TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"�ͻ���ȫ���˵��",		0,0,0,0,0,	},
	{	TDX_ID_ZJBZJ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"׷�ӱ�֤��",			0,0,0,0,0,	},
	{	TDX_ID_ZRJSJ,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"���ս����",			0,0,0,0,0,	},
	{	TDX_ID_SBMRJ,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"�����",				0,0,0,0,0,	},
	{	TDX_ID_SBMCJ,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"������",				0,0,0,0,0,	},
	{	TDX_ID_SBMRL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"������",				0,0,0,0,0,	},
	{	TDX_ID_SBMCL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"������",				0,0,0,0,0,	},
	{	TDX_ID_MCDJZJ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"���������ʽ�",			0,0,0,0,0,	},
	{	TDX_ID_MRBZJ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"���뱣֤��",			0,0,0,0,0,	},
	{	TDX_ID_MCBZJ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"������֤��",			0,0,0,0,0,	},
	{	TDX_ID_YLJE,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"ӯ�����",				0,0,0,0,0,	},
	{	TDX_ID_KSJE,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"������",				0,0,0,0,0,	},
	{	TDX_ID_DTQY,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"��̬Ȩ��",				0,0,0,0,0,	},
	{	TDX_ID_DTFX,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"��̬����",				0,0,0,0,0,	},
	{	TDX_ID_PCYK,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"ƽ��ӯ��",				0,0,0,0,0,	},
	{	TDX_ID_DRCRJ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"���ճ����",			0,0,0,0,0,	},
	{	TDX_ID_XTZXH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"ϵͳ���ĺ�",			0,0,0,0,0,	},
	{	TDX_ID_KPBZSM,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"��ƽ��־",				0,0,0,0,0,	},
	{	TDX_ID_TBBZSM,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"Ͷ����־",				0,0,0,0,0,	},
	{	TDX_ID_MRCC,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"��ֲ�",				0,0,0,0,0,	},
	{	TDX_ID_MRFDYK,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"��ӯ��",				0,0,0,0,0,	},
	{	TDX_ID_MCCC,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"���ֲ�",				0,0,0,0,0,	},
	{	TDX_ID_MCJJ,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"������",				0,0,0,0,0,	},
	{	TDX_ID_MCFDYK,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"��ӯ��",				0,0,0,0,0,	},
	{	TDX_ID_LSH,					TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"��ˮ��",				0,0,0,0,0,	},
	{	TDX_ID_JF,					TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"����",					0,0,0,0,0,	},
	{	TDX_ID_DF,					TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"���",					0,0,0,0,0,	},
	{	TDX_ID_QHTJ,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"Ͷ��",					0,0,0,0,0,	},
	{	TDX_ID_QHBZ,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"��ֵ",					0,0,0,0,0,	},
	{	TDX_ID_ZDSS,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"�������",				0,0,0,0,0,	},
	{	TDX_ID_ZDCC,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"���ֲ�",				0,0,0,0,0,	},
	{	TDX_ID_WCJSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"δ�ɽ�����",			0,0,0,0,0,	},
	{	TDX_ID_SBSJ,				TDX_DT_TIME,	TDX_DISP_RIGHT,   8,	"�걨ʱ��",				0,0,0,0,0,	},
	{	TDX_ID_CDSJ,				TDX_DT_TIME,	TDX_DISP_RIGHT,   8,	"����ʱ��",				0,0,0,0,0,	},
	{	TDX_ID_FSZ,					TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"������",				0,0,0,0,0,	},
	{	TDX_ID_XXLX,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"��Ϣ����",				0,0,0,0,0,	},
	{	TDX_ID_XXLXSM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"��Ϣ����",				0,0,0,0,0,	},
	{	TDX_ID_ZYZJ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"��Ѻ�ʽ�",				0,0,0,0,0,	},
	{	TDX_ID_ZJFXL,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"�ʽ������",			0,0,0,0,0,	},
	{	TDX_ID_JYSFXL,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"������������",			0,0,0,0,0,	},
	{	TDX_ID_QCQY,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"�ڳ�Ȩ��",				0,0,0,0,0,	},
	{	TDX_ID_DPPCYK,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"����ƽ��ӯ��",			0,0,0,0,0,	},
	{	TDX_ID_FDPCYK,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"����ƽ��ӯ��",			0,0,0,0,0,	},
	{	TDX_ID_DPCCYK,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"���ֲ̳�ӯ��",			0,0,0,0,0,	},
	{	TDX_ID_FDCCYK,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"�����ֲ�ӯ��",			0,0,0,0,0,	},
	{	TDX_ID_DPZYK,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"������ӯ��",			0,0,0,0,0,	},
	{	TDX_ID_FDZYK,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"������ӯ��",			0,0,0,0,0,	},
	{	TDX_ID_QHJYTSXX,			TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"�ڻ�������ʾ��Ϣ",		0,0,0,0,0,	},
	{	TDX_ID_KMRKCSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"�����뿪������",		0,0,0,0,0,	},
	{	TDX_ID_KMCKCSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"��������������",		0,0,0,0,0,	},
	{	TDX_ID_KMRPCSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"������ƽ������",		0,0,0,0,0,	},
	{	TDX_ID_KMCPCSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"������ƽ������",		0,0,0,0,0,	},
	{	TDX_ID_KMRPJSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"������ƽ������",		0,0,0,0,0,	},
	{	TDX_ID_KMCPJSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"������ƽ������",		0,0,0,0,0,	},
	{	TDX_ID_JKKY,				TDX_DT_LONG,	TDX_DISP_RIGHT,	  8,	"�񿪿���",				0,0,0,0,0,	},
	{	TDX_ID_LSKKY,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"��ʷ������",			0,0,0,0,0,	},
	{	TDX_ID_DSYK,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"����ӯ��",				0,0,0,0,0,	},
	{	TDX_ID_YKDS,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"ӯ������",				0,0,0,0,0,	},
	{	TDX_ID_HYBH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"��Լ���",				0,0,0,0,0,	},


	{	TDX_ID_HQ_MRSL1,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"��һ��",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MRSL2,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"�����",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MRSL3,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"������",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MRSL4,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"������",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MRSL5,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"������",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MRSL6,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"������",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MRSL7,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"������",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MRSL8,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"�����",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MRSL9,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"�����",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MRSL0,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"��ʮ��",				0,0,0,0,0,	},

	{	TDX_ID_HQ_MRLG1,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"��һ��",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MRLG2,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"�����",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MRLG3,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"������",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MRLG4,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"���ļ�",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MRLG5,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"�����",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MRLG6,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"������",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MRLG7,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"���߼�",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MRLG8,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"��˼�",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MRLG9,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"��ż�",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MRLG0,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"��ʮ��",				0,0,0,0,0,	},

	{	TDX_ID_HQ_MCSL1,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"��һ��",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MCSL2,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"������",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MCSL3,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"������",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MCSL4,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"������",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MCSL5,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"������",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MCSL6,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"������",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MCSL7,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"������",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MCSL8,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"������",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MCSL9,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"������",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MCSL0,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"��ʮ��",				0,0,0,0,0,	},

	{	TDX_ID_HQ_MCJS1,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"��һ��",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MCJS2,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"������",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MCJS3,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"������",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MCJS4,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"���ļ�",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MCJS5,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"�����",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MCJS6,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"������",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MCJS7,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"���߼�",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MCJS8,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"���˼�",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MCJS9,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"���ż�",				0,0,0,0,0,	},
	{	TDX_ID_HQ_MCJS0,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"��ʮ��",				0,0,0,0,0,	},

	{	TDX_ID_HQ_ZTJG,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"��ͣ�۸�",				0,0,0,0,0,	},
	{	TDX_ID_HQ_DTJG,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"��ͣ�۸�",				0,0,0,0,0,	},
	{	TDX_ID_HQ_ZGJG,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"��߼�",				0,0,0,0,0,	},
	{	TDX_ID_HQ_ZDJG,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"��ͼ�",				0,0,0,0,0,	},
	{	TDX_ID_HQ_GZQJ,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"��ծȫ��",				0,0,0,0,0,	},
	{	TDX_ID_HQ_OPEN,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"�񿪼�",				0,0,0,0,0,	},
	{	TDX_ID_HQ_CLOSE,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"���ռ�",				0,0,0,0,0,	},
	{	TDX_ID_HQ_TPBZ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"ͣ�Ʊ�־",				0,0,0,0,0,	},
	{	TDX_ID_GZLX,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"��ծ��Ϣ",				0,0,0,0,0,	},
	{	TDX_ID_NOW,					TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"��ǰ��",				0,0,0,0,0,	},
	{	TDX_ID_USERADDRESS,			TDX_DT_STRING,	TDX_DISP_RIGHT,  80,	"�û�ͨѶ��ַ",			0,0,0,0,0,	},
	{	TDX_ID_IDENTITYCARD,		TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"���֤",				0,0,0,0,0,	},
	{	TDX_ID_SEX,					TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"�Ա�",					0,0,0,0,0,	},
	{	TDX_ID_POSTALCODE,			TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"��������",				0,0,0,0,0,	},
	{	TDX_ID_HQ_ZDF,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"�ǵ���",				0,0,0,0,0,	},
	{	TDX_ID_HQ_ZDZ,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"�ǵ�ֵ",				0,0,0,0,0,	},
	{	TDX_ID_GETGTHQ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"ȡ��̨����",			0,0,0,0,0,	},
	{	TDX_ID_MBYLX,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"ÿ��Ԫ��Ϣ",			0,0,0,0,0,	},
	{	TDX_ID_GZBS,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"��ծ��ʶ",				1,0,0,0,0,	},
	{	TDX_ID_ZQXXYXBZ,			TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"֤ȯ��Ϣ��Ч��־",		0,0,0,0,0,	},
	{	TDX_ID_ZQLB,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"֤ȯ���",				0,0,0,0,0,	},
	{	TDX_ID_ZGSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"�������",				0,0,0,0,0,	},
	{	TDX_ID_ZDSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"�������",				0,0,0,0,0,	},

	{	TDX_ID_YZZZ_YHDM,			TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"���д���",				0,0,0,0,0,	},
	{	TDX_ID_YZZZ_YHMC,			TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"��������",				0,0,0,0,0,	},
	{	TDX_ID_YZZZ_YHZH,			TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"�����ʺ�",				0,0,0,0,0,	},
	{	TDX_ID_YZZZ_YHMM,			TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"��������",				0,0,0,0,0,	},
	{	TDX_ID_YZZZ_XYHMM,			TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"����������",			0,0,0,0,0,	},
	{	TDX_ID_YZZZ_YHLSH,			TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"������ˮ��",			0,0,0,0,0,	},
	{	TDX_ID_YZZZ_ZZJE,			TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"ת�ʽ��",				0,0,0,0,0,	},
	{	TDX_ID_YZZZ_ZZFX,			TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"ת�ʷ���",				0,0,0,0,0,	},
	{	TDX_ID_YZZZ_YHYE,			TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"�������",				0,0,0,0,0,	},
	{	TDX_ID_YZZZ_ZZRQ,			TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"ת������",				0,0,0,0,0,	},
	{	TDX_ID_YZZZ_ZZSJ,			TDX_DT_TIME,	TDX_DISP_RIGHT,   8,	"ת��ʱ��",				0,0,0,0,0,	},
	{	TDX_ID_YZZZ_ZZFXSM,			TDX_DT_STRING,	TDX_DISP_RIGHT, 40,		"ת��˵��",				0,0,0,0,0,	},
	{	TDX_ID_YZTYH,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"��֤ͨ�û�",			0,0,0,0,0,	},
	{	TDX_ID_YZZZ_NEEDZJMM,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"��Ҫ�ʽ�����",			0,0,0,0,0,	},
	{	TDX_ID_YZZZ_NEEDYHMM,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"��Ҫ��������",			0,0,0,0,0,	},
	{	TDX_ID_YZZZ_SUPPORTYHYE,	TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"֧�ֲ��������",		0,0,0,0,0,	},
	{	TDX_ID_BANKCODE,			TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"���д���",				0,0,0,0,0,	},
	{	TDX_ID_BANKYYB,				TDX_DT_STRING,	TDX_DISP_RIGHT,  40,	"����Ӫҵ��",			0,0,0,0,0,	},
	{	TDX_ID_BANKGDTYPE,			TDX_DT_STRING,	TDX_DISP_RIGHT,   2,	"���йɶ������¼�г�",	0,0,0,0,0,	},
	{	TDX_ID_YZZZ_ZRMM,			TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"��֤ת���������",		0,0,0,0,0,	},
	{	TDX_ID_YZZZ_ZCMM,			TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"��֤ת���������",		0,0,0,0,0,	},
	{	TDX_ID_YZZZ_SHOWYHYE,		TDX_DT_CHAR,	TDX_DISP_RIGHT,  1,		"��ʾ���������",		0,0,0,0,0,	},
	{	TDX_ID_YZZZ_YHYEMM,			TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"����������������",	0,0,0,0,0,	},
	{	TDX_ID_ZRYHDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"ת�����д���",			0,0,0,0,0,	},
	{	TDX_ID_ZCYHDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"ת�����д���",			0,0,0,0,0,	},
	{	TDX_ID_ZRYHZH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"ת�������ʺ�",			0,0,0,0,0,	},
	{	TDX_ID_ZCYHZH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"ת�������ʺ�",			0,0,0,0,0,	},
	{	TDX_ID_ZJYHDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"��ת���д���",			0,0,0,0,0,	},
	{	TDX_ID_ZJYHMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"��ת��������",			0,0,0,0,0,	},
	{	TDX_ID_ZJYHZH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"��ת�����ʺ�",			0,0,0,0,0,	},
	{	TDX_ID_ZJYHZHMC,			TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"��ת�����ʺ�����",		0,0,0,0,0,	},
	{	TDX_ID_YHKH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"���п���",				0,0,0,0,0,	},
	{	TDX_ID_YHQC,				TDX_DT_STRING,	TDX_DISP_RIGHT, 128,	"����ȫ��",				0,0,0,0,0,	},
	{	TDX_ID_ZKBZ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"������־",				0,0,0,0,0,	},
	{	TDX_ID_JQBZ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"��Ȩ��־",				0,0,0,0,0,	},

	{	TDX_ID_YHZHBM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"�����˻�����",			0,0,0,0,0,	},
	{	TDX_ID_YHZHBM1,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"�����˻�����1",		0,0,0,0,0,	},
	{	TDX_ID_YHZHBM2,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"�����˻�����2",		0,0,0,0,0,	},
	{	TDX_ID_YHZHBM3,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"�����˻�����3",		0,0,0,0,0,	},
	{	TDX_ID_YHZHBM4,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"�����˻�����4",		0,0,0,0,0,	},
	{	TDX_ID_YHZHMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"�����˻�����",			0,0,0,0,0,	},
	{	TDX_ID_YHZHMC1,				TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"�����˻�����1",		0,0,0,0,0,	},
	{	TDX_ID_YHZHMC2,				TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"�����˻�����2",		0,0,0,0,0,	},
	{	TDX_ID_YHZHMC3,				TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"�����˻�����3",		0,0,0,0,0,	},
	{	TDX_ID_YHZHMC4,				TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"�����˻�����4",		0,0,0,0,0,	},
	
	{	TDX_ID_YHCPDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"���в�Ʒ����",			0,0,0,0,0,	},
	{	TDX_ID_YHCPMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"���в�Ʒ����",			0,0,0,0,0,	},		
	{	TDX_ID_XTCPDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"���в�Ʒ����",			0,0,0,0,0,	},
	{	TDX_ID_XTCPMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"���в�Ʒ����",			0,0,0,0,0,	},	

	{	TDX_ID_RZLX,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"������Ϣ",				0,0,0,0,0,	},
	{	TDX_ID_XYZ,					TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"�˻�����ֵ",			0,0,0,0,0,	},
	{	TDX_ID_ZHWBXY,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"�˻��ⲿ����",			0,0,0,0,0,	},
	{	TDX_ID_XYSX,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"��������",				0,0,0,0,0,	},
	{	TDX_ID_RZSX,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"������������",			0,0,0,0,0,	},
	{	TDX_ID_RQSX,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"��ȯ��������",			0,0,0,0,0,	},
	{	TDX_ID_XYCPBS,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"���ò�Ʒ��ʾ",			0,0,0,0,0,	},
	{	TDX_ID_DYZC,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"��Ѻ�ʲ�",				0,0,0,0,0,	},
	{	TDX_ID_PCBZ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"ƽ�ֱ�־",				0,0,0,0,0,	},
	{	TDX_ID_RZSXF,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"���ʹ����",			0,0,0,0,0,	},
	{	TDX_ID_RQMCZJ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"��ȯ�����ʽ�",			0,0,0,0,0,	},
	{	TDX_ID_RZFX,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"���ʷ���",				0,0,0,0,0,	},
	{	TDX_ID_GHSL,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"�黹����",				0,0,0,0,0,	},
	{	TDX_ID_RZFZ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"���ʸ�ծ",				0,0,0,0,0,	},
	{	TDX_ID_RQSZ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"��ȯ��ֵ",				0,0,0,0,0,	},
	{	TDX_ID_QSJE,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"������",				0,0,0,0,0,	},
	{	TDX_ID_KYXYED,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"�������ö��",			0,0,0,0,0,	},
	{	TDX_ID_YYXYED,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"�������ö��",			0,0,0,0,0,	},
	{	TDX_ID_RZJE,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"���ʽ��",				0,0,0,0,0,	},
	{	TDX_ID_RQJE,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"��ȯ���",				0,0,0,0,0,	},
	{	TDX_ID_RQLX,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"��ȯ��Ϣ",				0,0,0,0,0,	},
	{	TDX_ID_RQSXF,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"��ȯ�����",			0,0,0,0,0,	},
	{	TDX_ID_DBBL,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"��������",				0,0,0,0,0,	},
	{	TDX_ID_KYBZJ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"���ñ�֤��",			0,0,0,0,0,	},
	{	TDX_ID_YYBZJ,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"���ñ�֤��",			0,0,0,0,0,	},
	{	TDX_ID_RQSYSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,  12,	"��ȯʹ������",			0,0,0,0,0,	},
	{	TDX_ID_PCRQ,				TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"ƽ������",				0,0,0,0,0,	},
	{	TDX_ID_XYHYLX,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"��Լ����",				0,0,0,0,0,	},
	{	TDX_ID_CHSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,  12,	"��������",				0,0,0,0,0,	},
	{	TDX_ID_CHJE,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"�������",				0,0,0,0,0,	},
	{	TDX_ID_SSCHSL,				TDX_DT_LONG,	TDX_DISP_RIGHT,  12,	"ʵʱ��������",			0,0,0,0,0,	},
	{	TDX_ID_SSCHJE,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"ʵʱ�������",			0,0,0,0,0,	},
	{	TDX_ID_CHLX,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"������Ϣ",				0,0,0,0,0,	},
	{	TDX_ID_HYSXF,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"��Լ����",				0,0,0,0,0,	},
	{	TDX_ID_HYLL,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"��Լ����",				0,0,0,0,0,	},
	{	TDX_ID_HYLXJE,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"��Լ��Ϣ",				0,0,0,0,0,	},
	{	TDX_ID_RZBL,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"���ʱ���",				0,0,0,0,0,	},
	{	TDX_ID_GPZSL,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"��Ʊ������",			0,0,0,0,0,	},
	{	TDX_ID_XYJB,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"���ü���",				0,0,0,0,0,	},
	{	TDX_ID_FXZT,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"����״̬",				0,0,0,0,0,	},
	{	TDX_ID_RZBZJBL,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"���ʱ�֤�����",		0,0,0,0,0,	},
	{	TDX_ID_RQBZJBL,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"��ȯ��֤�����",		0,0,0,0,0,	},
	{	TDX_ID_RZRQLXFY,			TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"������ȯ��Ϣ����",		0,0,0,0,0,	},
	{	TDX_ID_ZFZ,					TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"�ܸ�ծ",				0,0,0,0,0,	},
	{	TDX_ID_FZBL,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"��ծ����",				0,0,0,0,0,	},
	{	TDX_ID_HYQX,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"��Լ����",				0,0,0,0,0,	},
	{	TDX_ID_SYRZED,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"ʣ�����ʶ��",			0,0,0,0,0,	},
	{	TDX_ID_SYRQED,				TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"ʣ����ȯ���",			0,0,0,0,0,	},
	{	TDX_ID_TQZZLL,				TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"��ǰ��ֹ����",			0,0,0,0,0,	},
	{	TDX_ID_DQR,					TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"������",				0,0,0,0,0,	},

	{	TDX_ID_XT_ERRCODE,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"�����",				0,0,0,0,0,	},
	{	TDX_ID_XT_ERRMSG,			TDX_DT_STRING,	TDX_DISP_RIGHT,  80,	"������Ϣ",				0,0,0,0,0,	},
	{	TDX_ID_XT_FUNCNO,			TDX_DT_SHORT,	TDX_DISP_RIGHT,   4,	"���ܱ��",				0,0,0,0,0,	},
	{	TDX_ID_XT_CLIVER,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"�ͻ��˰汾",			0,0,0,0,0,	},
	{	TDX_ID_XT_MACADDR,			TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"MAC��ַ",				0,0,0,0,0,	},
	{	TDX_ID_XT_IPADDR,			TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"IP��ַ",				0,0,0,0,0,	},
	{	TDX_ID_XT_CLITYPE,			TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"�ͻ����",				0,0,0,0,0,	},
	{	TDX_ID_XT_STARTPOS,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"��ʼ���",				0,0,0,0,0,	},
	{	TDX_ID_XT_AUTH_NEWINFO,		TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"��֤����Ϣ",			0,0,0,0,0,	},
	{	TDX_ID_XT_OEM_FLAG,			TDX_DT_CHAR,	TDX_DISP_RIGHT,  16,	"OEM��ʶ",				0,0,0,0,0,	},
	{	TDX_ID_XT_AUTH_MODE,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"��֤��ʽ",				0,0,0,0,0,	},
	{	TDX_ID_XT_AUTH_INFO,		TDX_DT_CHAR,	TDX_DISP_RIGHT, 512,	"��֤��Ϣ",				0,0,0,0,0,	},
	{	TDX_ID_XT_BRANCHID,			TDX_DT_CHAR,	TDX_DISP_RIGHT,  10,	"Ӫҵ��ID",				0,0,0,0,0,	},
	{	TDX_ID_XT_RESERVED,			TDX_DT_STRING,	TDX_DISP_RIGHT,  80,	"������Ϣ",				1,0,0,0,0,	},
	{	TDX_ID_XT_RECONNECTFLAG,	TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"����������־",			1,0,0,0,0,	},
	{	TDX_ID_XT_COUNTERSTATUS,	TDX_DT_STRING,	TDX_DISP_RIGHT,  80,	"��̨״̬",				0,0,0,0,0,	},
	{	TDX_ID_XT_VIPFLAG,			TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"VIP��־",				1,0,0,0,0,	},
	{	TDX_ID_XT_REMARK,			TDX_DT_STRING,	TDX_DISP_RIGHT,  80,	"��ע",					0,0,0,0,0,	},
	{	TDX_ID_XT_CLIENTRIGHTS,		TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"�ͻ�Ȩ��",				1,0,0,0,0,	},
	{	TDX_ID_XT_LAST_LOGIN_DATE,	TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"�ϴε�¼����",			1,0,0,0,0,	},
	{	TDX_ID_XT_LAST_LOGIN_TIME,	TDX_DT_TIME,	TDX_DISP_RIGHT,   8,	"�ϴε�¼ʱ��",			1,0,0,0,0,	},
	{	TDX_ID_XT_AHTHCHAR1,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"��֤�ַ�1",			1,0,0,0,0,	},
	{	TDX_ID_XT_AHTHCHAR2,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"��֤�ַ�2",			1,0,0,0,0,	},
	{	TDX_ID_XT_CHECKRISKFLAG,	TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"�����ձ�־",			1,0,0,0,0,	},
	{	TDX_ID_XT_FJYZHBZ,			TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"�ǽ����ʺű�־",		1,0,0,0,0,	},
	{	TDX_ID_XT_JZJJKHBZ,			TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"��ֹ���𿪻���־",		1,0,0,0,0,	},
	{	TDX_ID_XT_INCREMENTMODE,	TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"����ģʽ����",			0,0,0,0,0,	},
	{	TDX_ID_XT_PARAM,			TDX_DT_STRING,	TDX_DISP_RIGHT,  80,	"����",					0,0,0,0,0,	},
	{	TDX_ID_XT_MODE,				TDX_DT_STRING,	TDX_DISP_RIGHT,  80,	"ģʽ",					0,0,0,0,0,	},
	{	TDX_ID_XT_DESCRIPTION,		TDX_DT_STRING,	TDX_DISP_RIGHT,  80,	"����",					0,0,0,0,0,	},
	{	TDX_ID_XT_QUERYMODE,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"��ѯģʽ",				0,0,0,0,0,	},
	{	TDX_ID_XT_DISPLAYCOLOR,		TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"��ʾ��ɫ",				1,0,0,0,0,	},
	{	TDX_ID_XT_PASSWORDFLAG,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"�����־",				0,0,0,0,0,	},
	{	TDX_ID_XT_HANDLE,			TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"���",					1,0,0,0,0,	},
	{	TDX_ID_XT_GTLB,				TDX_DT_STRING,	TDX_DISP_RIGHT,   1,	"��̨���",				1,0,0,0,0,	},
	{	TDX_ID_XT_MACHINEINFO,		TDX_DT_STRING,	TDX_DISP_RIGHT, 800,	"������Ϣ",				0,0,0,0,0,	},
	{	TDX_ID_XT_LIMITMODE,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"����ģʽ",				0,0,0,0,0,	},
	{	TDX_ID_XT_MACHINECODE,		TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"����������",			0,0,0,0,0,	},
	{	TDX_ID_XT_MOBILECHECKCODE,	TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"�ֻ�У����",			0,0,0,0,0,	},
	{	TDX_ID_XT_BRANCHMODIFY,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"Ӫҵ���ı�",			0,0,0,0,0,	},
	{	TDX_ID_XT_NEEDEDAUTHMODE,	TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"������֤��ʽ",			0,0,0,0,0,	},
	{	TDX_ID_XT_SESSION,			TDX_DT_STRING,	TDX_DISP_RIGHT, 128,	"SESSION��Ϣ",			0,0,0,0,0,	},
	{	TDX_ID_XT_URL,				TDX_DT_STRING,	TDX_DISP_RIGHT, 128,	"URL",					0,0,0,0,0,	},
	{	TDX_ID_XT_INFOCOLUMN,		TDX_DT_STRING,	TDX_DISP_RIGHT, 128,	"��Ѷ��Ŀ",				0,0,0,0,0,	},
	{	TDX_ID_XT_REALCLIENTVERSION,TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"�ڲ��ͻ��˰汾",		0,0,0,0,0,	},
	{	TDX_ID_XT_CN,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"CN",					0,0,0,0,0,	},
	{	TDX_ID_XT_SN,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"SN",					0,0,0,0,0,	},
	{	TDX_ID_XT_DN,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"DN",					0,0,0,0,0,	},
	{	TDX_ID_XT_NEEDCONFIRMFLAGS,	TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"��ȷ�ϵı�ʶ��",		0,0,0,0,0,	},
	{	TDX_ID_XT_URL2,				TDX_DT_STRING,	TDX_DISP_RIGHT, 128,	"URL2",					0,0,0,0,0,	},
	{	TDX_ID_XT_REDIRECTFLAG,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"�ض����־",			0,0,0,0,0,	},
	{	TDX_ID_XT_REDIRECTINFO,		TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"�ض�����Ϣ",			0,0,0,0,0,	},
	{	TDX_ID_XT_LAST_LOGIN_LOCATION,TDX_DT_STRING,TDX_DISP_RIGHT, 128,	"�ϴε�¼λ��",			1,0,0,0,0,	},
	{	TDX_ID_XT_SLOTID,			TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"֤������ID",			0,0,0,0,0,	},
	{	TDX_ID_XT_CID,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"֤�鳧��ID",			0,0,0,0,0,	},
	{	TDX_ID_XT_INPUTPARAM,		TDX_DT_STRING,	TDX_DISP_RIGHT,1024,	"�������",				0,0,0,0,0,	},
	{	TDX_ID_XT_OUTPUTPARAM,		TDX_DT_STRING,	TDX_DISP_RIGHT,8192,	"�������",				0,0,0,0,0,	},
	{	TDX_ID_XT_TOKEN,			TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"����",					0,0,0,0,0,	},
	{	TDX_ID_XT_LOGINEMAIL,		TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"��¼Email",			0,0,0,0,0,	},
	{	TDX_ID_XT_TRADEEMAIL,		TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"����Email",			0,0,0,0,0,	},
	{	TDX_ID_XT_MESSAGEID,		TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"��Ϣ���",				0,0,0,0,0,	},
	{	TDX_ID_XT_MESSAGETITLE,		TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"��Ϣ����",				0,0,0,0,0,	},
	{	TDX_ID_XT_MESSAGECONTENT,	TDX_DT_STRING,	TDX_DISP_RIGHT,8192,	"��Ϣ����",				0,0,0,0,0,	},
	{	TDX_ID_XT_POSITIONSTRING,	TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"��λ�ִ�",				1,0,0,0,0,	},
	{	TDX_ID_XT_BEGINLINE,		TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"��ʼ�к�",				1,0,0,0,0,	},
	{	TDX_ID_XT_REQUESTLINE,		TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"��������",				1,0,0,0,0,	},
	{	TDX_ID_XT_TOTALLINE,		TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"�ܹ�����",				1,0,0,0,0,	},
	{	TDX_ID_XT_RISKPARAM,		TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"���ղ���",				1,0,0,0,0,	},
	{	TDX_ID_XT_LOGINRETURNPARAM,	TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"��¼���ز���",			1,0,0,0,0,	},
	{	TDX_ID_XT_MOBILEMACHINEINFO,TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"�ֻ�������Ϣ",			1,0,0,0,0,	},
	{	TDX_ID_XT_PACKAGELIST,		TDX_DT_STRING,	TDX_DISP_RIGHT,1024,	"�ײ��б�",				1,0,0,0,0,	},
	{	TDX_ID_XT_PRODUCTLIST,		TDX_DT_STRING,	TDX_DISP_RIGHT,1024,	"��Ʒ�б�",				1,0,0,0,0,	},
	{	TDX_ID_XT_FEATURELIST,		TDX_DT_STRING,	TDX_DISP_RIGHT,1024,	"�����б�",				1,0,0,0,0,	},
	{	TDX_ID_XT_CONFIGLIST,		TDX_DT_STRING,	TDX_DISP_RIGHT,1024,	"�����б�",				1,0,0,0,0,	},
	{	TDX_ID_XT_LOGINENTERPARAM,	TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"��¼�������",			1,0,0,0,0,	},
	{	TDX_ID_XT_ALGORIGHTLIST,	TDX_DT_STRING,	TDX_DISP_RIGHT,1024,	"�㷨Ȩ���б�",			1,0,0,0,0,	},
	{	TDX_ID_XT_FUNCTIONVERSION,	TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"���ܰ汾",				1,0,0,0,0,	},
	{	TDX_ID_XT_CLIENTINVERSION,	TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"�ͻ����ڲ��汾",		1,0,0,0,0,	},
	{	TDX_ID_XT_VERSIONSTRING,	TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"�汾�ַ���",			1,0,0,0,0,	},

	{	TDX_ID_XLYZT_XGKT_FLAG,		TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"�޸Ŀ�ͨ���",			0,0,0,0,0,	},

	{	TDX_ID_XLYZT_START_DATE,	TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"��Ч����",				0,0,0,0,0,	},
	{	TDX_ID_XLYZT_END_DATE,		TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"ʧЧ����",				0,0,0,0,0,	},
	{	TDX_ID_XLYZT_DEBT_KIND,		TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"�ع�Ʒ��",				0,0,0,0,0,	},
	{	TDX_ID_XLYZT_JE_MIN,		TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"�ʽ�����",				0,0,0,0,0,	},
	{	TDX_ID_XLYZT_JE_MAX,		TDX_DT_DOUBLE,	TDX_DISP_RIGHT,  12,	"�ʽ�����",				0,0,0,0,0,	},
};

const FIELDINFO tdxScntrFieldInfo[]=
{
//	{	�ֶ�����,					��������,		��ʾ(����)����,���,	�ֶ�˵��,				�������,	},

	{	TDX_ID_CA_KHH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"�ͻ���",				0,0,0,0,0,	},
	{	TDX_ID_ZHLB,				TDX_DT_STRING,	TDX_DISP_RIGHT,   2,	"�ʺ����",				1,0,0,0,0,	},
	{	TDX_ID_XT_GTLB,				TDX_DT_STRING,	TDX_DISP_RIGHT,   1,	"��̨���",				1,0,0,0,0,	},
	{	TDX_ID_CA_KHMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"�ͻ�����",				0,0,0,0,0,	},
	{	TDX_ID_CA_SQBZ,				TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"�����־",				0,0,0,0,0,	},
	{	TDX_ID_CA_TXMM,				TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"��֤����",				0,0,0,0,0,	},
	{	TDX_ID_CA_XTXMM,			TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"����֤����",			0,0,0,0,0,	},
	{	TDX_ID_CA_ZSXH,				TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"֤�����",				0,0,0,0,0,	},
	{	TDX_ID_CA_AQJB,				TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"��ȫ����",				0,0,0,0,0,	},
	{	TDX_ID_CA_YHFJ,				TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"�û��ּ�",				0,0,0,0,0,	},
	{	TDX_ID_CA_YHJBMS,			TDX_DT_STRING,	TDX_DISP_LEFT,    4,	"�û���������",			0,0,0,0,0,	},
	{	TDX_ID_CA_YHQX,				TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"�û�Ȩ��",				0,0,0,0,0,	},
	{	TDX_ID_CA_KJYBZ,			TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"�ɽ��ױ�־",			0,0,0,0,0,	},
	{	TDX_ID_CA_ZSSHBZ,			TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"֤����˱�־",			0,0,0,0,0,	},
	{	TDX_ID_CA_ZSXZBZ,			TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"֤�����ر�־",			0,0,0,0,0,	},
	{	TDX_ID_CA_ZSQSID,			TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"֤��ȯ��ID",			0,0,0,0,0,	},
	{	TDX_ID_CA_ZSBFJG,			TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"֤��䷢����",			0,0,0,0,0,	},
	{	TDX_ID_CA_ZSBFYH,			TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"֤��䷢�û�",			0,0,0,0,0,	},
	{	TDX_ID_CA_ZSQSRQ,			TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"֤����������",			0,0,0,0,0,	},
	{	TDX_ID_CA_ZSJZRQ,			TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"֤���ֹ����",			0,0,0,0,0,	},
	{	TDX_ID_CA_ZSWS,				TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"֤��λ��",				0,0,0,0,0,	},
	{	TDX_ID_CA_ZSGY,				TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"֤�鹫Կ",				0,0,0,0,0,	},
	{	TDX_ID_CA_CZJG,				TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"��������",				0,0,0,0,0,	},
	{	TDX_ID_CA_CZY,				TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"����Ա",				0,0,0,0,0,	},
	{	TDX_ID_CA_CZMM,				TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"��������",				0,0,0,0,0,	},
	{	TDX_ID_CA_CZSX,				TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"��������",				0,0,0,0,0,	},
	{	TDX_ID_CA_CZBZ,				TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"������־",				0,0,0,0,0,	},
	{	TDX_ID_CA_RESV, 			TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"�����ֶ�",				0,0,0,0,0,	},
	{	IDX_ID_CA_ZSKGXBZ,			TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"֤��ɸ��±�־",		0,0,0,0,0,	},
	{	TDX_ID_CA_ZSJYGXBZ,			TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"֤�齨����±�־",		0,0,0,0,0,	},
	{	TDX_ID_CA_ZSSYYXTS,			TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"֤��ʣ����Ч����",		0,0,0,0,0,	},
	{	TDX_ID_CA_ZHLB,				TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"�˺����",				0,0,0,0,0,	},
	{	TDX_ID_CA_TQID,				TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"TQ��",					0,0,0,0,0,	},
	{	TDX_ID_CA_TQMAIL,			TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"TQ�ʼ�",				0,0,0,0,0,	},
	{	TDX_ID_CA_XGTXMMBZ,			TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"��֤�����޸ı��",		0,0,0,0,0,	},
	{	TDX_ID_CA_L2USER,			TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"LEVEL2�˺�",			0,0,0,0,0,	},
	{	TDX_ID_CA_L2PASS,			TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"LEVEL2����",			0,0,0,0,0,	},
	{	TDX_ID_CA_YHJBZT,			TDX_DT_STRING,	TDX_DISP_LEFT,    4,	"�û�����״̬",			0,0,0,0,0,	},
	{	TDX_ID_CA_YHJBBZ,			TDX_DT_STRING,	TDX_DISP_LEFT,  256,	"�û�����ע",			0,0,0,0,0,	},
	{	TDX_ID_CA_ISVIPHOST,		TDX_DT_STRING,	TDX_DISP_RIGHT,   1,	"VIP��վ��ʶ",			0,0,0,0,0,	},
	{	TDX_ID_CA_KHJL,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"�ͻ�������",			0,0,0,0,0,	},
	{	TDX_ID_CA_TOPICID,			TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"������",				0,0,0,0,0,	},
	{	TDX_ID_CA_TOPICTITLE,		TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"�������",				0,0,0,0,0,	},
	{	TDX_ID_CA_CONTENT,			TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"��������",				0,0,0,0,0,	},
	{	TDX_ID_CA_QUERYDATE,		TDX_DT_STRING,	TDX_DISP_RIGHT,   9,	"��ѯ����",				0,0,0,0,0,	},
	{	TDX_ID_CA_REQDATE,			TDX_DT_STRING,	TDX_DISP_RIGHT,   9,	"���ⷢ������",			0,0,0,0,0,	},
	{	TDX_ID_CA_REQTIME,			TDX_DT_STRING,	TDX_DISP_RIGHT,   9,	"���ⷢ��ʱ��",			0,0,0,0,0,	},
	{	TDX_ID_CA_VALDATE,			TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"������Ч����",			0,0,0,0,0,	},
	{	TDX_ID_CA_CLOSEFLAG,		TDX_DT_STRING,	TDX_DISP_RIGHT,   2,	"�رձ�־",				0,0,0,0,0,	},
	{	TDX_ID_CA_SATISFAC,			TDX_DT_STRING,	TDX_DISP_RIGHT,  10,	"�����",				0,0,0,0,0,	},
	{	TDX_ID_CA_REMINDFLAG,		TDX_DT_STRING,	TDX_DISP_RIGHT,   2,	"��ʾ�ر�־��",			0,0,0,0,0,	},
	{	TDX_ID_CA_NEWANSFLAG,		TDX_DT_STRING,	TDX_DISP_RIGHT,   2,	"���»ظ���ʾ",			0,0,0,0,0,	},
	{	TDX_ID_CA_ANSWERID,			TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"�ظ����",				0,0,0,0,0,	},
	{	TDX_ID_CA_WHOANS,			TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"�ظ���",				0,0,0,0,0,	},
	{	TDX_ID_CA_QUERYALL,			TDX_DT_STRING,	TDX_DISP_RIGHT,   2,	"�Ƿ��ѯ����",			0,0,0,0,0,	},
	{	TDX_ID_CA_BRANCHMSGID,		TDX_DT_STRING,	TDX_DISP_RIGHT,   2,	"Ӫҵ����ϢID",			0,0,0,0,0,	},
	{	TDX_ID_CA_NEWMSGNUM,		TDX_DT_STRING,	TDX_DISP_RIGHT,   2,	"����Ϣ����",			0,0,0,0,0,	},
	{	TDX_ID_CA_NOREADMSGNUM,		TDX_DT_STRING,	TDX_DISP_RIGHT,   2,	"δ����Ϣ����",			0,0,0,0,0,	},
	{	TDX_ID_CA_RESETFLAG,		TDX_DT_STRING,	TDX_DISP_RIGHT,   2,	"���ñ�־",				0,0,0,0,0,	},
                                                                                                	
	{	TDX_ID_CA_SJH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"�ֻ���",				0,0,0,0,0,	},
	{	TDX_ID_CA_ZJHM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  20,	"֤������",				0,0,0,0,0,	},
	{	TDX_ID_CA_KHXB,				TDX_DT_STRING,	TDX_DISP_RIGHT,   5,	"�ͻ��Ա�",				0,0,0,0,0,	},
	{	TDX_ID_CA_EMAIL,			TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"�����ʼ�",				0,0,0,0,0,	},
	{	TDX_ID_CA_JHM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  20,	"������",				0,0,0,0,0,	},
	{	TDX_ID_CA_DRZB,				TDX_DT_STRING,	TDX_DISP_RIGHT,  20,	"����ָ��",				0,0,0,0,0,	},
	{	TDX_ID_CA_LEVELNAME,		TDX_DT_STRING,	TDX_DISP_RIGHT,  20,	"�ȼ�����",				0,0,0,0,0,	},
	{	TDX_ID_CA_ZBMAX,			TDX_DT_STRING,	TDX_DISP_RIGHT,  20,	"ָ������",				0,0,0,0,0,	},
	{	TDX_ID_CA_ZBMIN,			TDX_DT_STRING,	TDX_DISP_RIGHT,  20,	"ָ������",				0,0,0,0,0,	},
	{	TDX_ID_CA_PROTOC,			TDX_DT_STRING,	TDX_DISP_RIGHT,1024,	"����Э��",				0,0,0,0,0,	},
	{	TDX_ID_CA_COMMISION,		TDX_DT_STRING,	TDX_DISP_RIGHT,  20,	"Ӷ��",					0,0,0,0,0,	},
	{	TDX_ID_CA_BIRTHTITIP,		TDX_DT_STRING,	TDX_DISP_RIGHT,   2,	"�Ƿ���Ҫ��������",		0,0,0,0,0,	},
	{	TDX_ID_CA_NOTICETITLE,		TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"�������",				0,0,0,0,0,	},
	{	TDX_ID_CA_NOTICECONTENT,	TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"������������",			0,0,0,0,0,	},
	{	TDX_ID_CA_TSUPDATE,			TDX_DT_STRING,	TDX_DISP_RIGHT,   5,	"��ʾ����",				0,0,0,0,0,	},
	{	TDX_ID_CA_NOWLEVELNO,		TDX_DT_STRING,	TDX_DISP_RIGHT,   5,	"��ǰ�ȼ����",			0,0,0,0,0,	},
	{	TDX_ID_CA_NOWLEVELNAME,		TDX_DT_STRING,	TDX_DISP_RIGHT,  20,	"��ǰ�ȼ�����",			0,0,0,0,0,	},
	{	TDX_ID_CA_CANLEVELNO,		TDX_DT_STRING,	TDX_DISP_RIGHT,  20,	"������ȼ����",		0,0,0,0,0,	},
	{	TDX_ID_CA_CANLEVELNAME,		TDX_DT_STRING,	TDX_DISP_RIGHT,  20,	"������ȼ�����",		0,0,0,0,0,	},
	{	TDX_ID_CA_MENU,				TDX_DT_STRING,	TDX_DISP_RIGHT,  20,	"�ɼ���Ŀ",				0,0,0,0,0,	},

	{	TDX_ID_CA_LASTIP,			TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"�ϴε�¼IP",			0,0,0,0,0,	},
	{	TDX_ID_CA_NEWIP,			TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"�ϴε�¼IP",			0,0,0,0,0,	},
	{	TDX_ID_CA_LASPROV,			TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"�ϴε�¼ʡ��",			0,0,0,0,0,	},
	{	TDX_ID_CA_NEWPROV,			TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"���ε�¼ʡ��",			0,0,0,0,0,	},
	{	TDX_ID_CA_LASSITE,			TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"�ϴε�¼λ��",			0,0,0,0,0,	},
	{	TDX_ID_CA_NEWSITE,			TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"���ε�¼λ��",			0,0,0,0,0,	},
	{	TDX_ID_CA_QSRQ,				TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"��ʼ��ѯʱ��",			0,0,0,0,0,	},
	{	TDX_ID_CA_ZZRQ,				TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"��ֹ��ѯʱ��",			0,0,0,0,0,	},
	{	TDX_ID_CA_DLSJ,				TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"��¼ʱ��",				0,0,0,0,0,	},
	{	TDX_ID_CA_DLRQ,				TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"��¼����",				0,0,0,0,0,	},
	{	TDX_ID_CA_MMBHWT,			TDX_DT_STRING,	TDX_DISP_RIGHT,1024,	"���뱣������",			0,0,0,0,0,	},
	{	TDX_ID_CA_MMBHWT1,			TDX_DT_STRING,	TDX_DISP_RIGHT,1024,	"���뱣������1",		0,0,0,0,0,	},
	{	TDX_ID_CA_MMBHWT2,			TDX_DT_STRING,	TDX_DISP_RIGHT,1024,	"���뱣������2",		0,0,0,0,0,	},
	{	TDX_ID_CA_MMBHWT3,			TDX_DT_STRING,	TDX_DISP_RIGHT,1024,	"���뱣������3",		0,0,0,0,0,	},
	{	TDX_ID_CA_MMBHWT4,			TDX_DT_STRING,	TDX_DISP_RIGHT,1024,	"���뱣������4",		0,0,0,0,0,	},
	{	TDX_ID_CA_JQTZM,			TDX_DT_STRING,	TDX_DISP_RIGHT, 256,	"����������",			0,0,0,0,0,	},
	{	TDX_ID_CA_TZZB,				TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"��ս����",				0,0,0,0,0,	},
	{	TDX_ID_CA_CSCS,				TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"���Դ���",				0,0,0,0,0,	},
	{	TDX_ID_CA_ISDLWZTS,			TDX_DT_STRING,	TDX_DISP_RIGHT,   2,	"�Ƿ�֧�ֵ�¼λ����ʾ",	0,0,0,0,0,	},
	{	TDX_ID_CA_ISMMBHWT,			TDX_DT_STRING,	TDX_DISP_RIGHT,   2,	"�Ƿ�֧�����뱣������",	0,0,0,0,0,	},
	{	TDX_ID_CA_ISJQTZMBD,		TDX_DT_STRING,	TDX_DISP_RIGHT,   2,	"�Ƿ�֧���������",	0,0,0,0,0,	},
	{	TDX_ID_CA_MAC,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"����MAC��ַ",			0,0,0,0,0,	},
	{	TDX_ID_CA_YLWT,				TDX_DT_STRING,	TDX_DISP_RIGHT,1024,	"Ԥ������",				0,0,0,0,0,	},
	{	TDX_ID_CA_ISYLWT,			TDX_DT_STRING,	TDX_DISP_RIGHT,   2,	"�Ƿ�֧��Ԥ������",		0,0,0,0,0,	},
	{	TDX_ID_CA_CERTREQ,			TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"��������",				0,0,0,0,0,	},
	{	TDX_ID_CA_USERCERDN,		TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"֤��DN��Ϣ",			0,0,0,0,0,	},
	{	TDX_ID_CA_CERTTOKEN,		TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"֤��ҵ���",			0,0,0,0,0,	},
	{	TDX_ID_CA_CERTINFO,			TDX_DT_STRING,	TDX_DISP_RIGHT,8192,	"֤������",				0,0,0,0,0,	},
	{	TDX_ID_CA_SLOTSN,			TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"װ��֤������SN",		0,0,0,0,0,	},
	{	TDX_ID_CA_CERTSN,			TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"֤��SN��",				0,0,0,0,0,	},
	{	TDX_ID_CA_CID,				TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"��������ID",			0,0,0,0,0,	},
	{	TDX_ID_CA_SEEDINFO,			TDX_DT_STRING,	TDX_DISP_RIGHT, 512,	"OTP������Ϣ",			0,0,0,0,0,	},
	{	TDX_ID_CA_OTPSN,			TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"OTPSN",				0,0,0,0,0,	},
	{	TDX_ID_CA_BINDNUM,			TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"�Ѱ󶨵Ļ���̨��",		0,0,0,0,0,	},
	{	TDX_ID_CA_IDCARD,			TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"���֤����",			0,0,0,0,0,	},
	{	TDX_ID_CA_YZM,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"��֤��",				0,0,0,0,0,	},
	{	TDX_ID_XT_STARTPOS,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"��ʼ���",				0,0,0,0,0,	},
	{	TDX_ID_XT_STARTPOS,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"��ʼ���",				0,0,0,0,0,	},
	{	TDX_ID_CA_VER,				TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"�ܱ�����汾",			0,0,0,0,0,	},
	{	TDX_ID_CA_PWDPROQUESTION,	TDX_DT_STRING,	TDX_DISP_RIGHT, 128,	"�ܱ�����",				0,0,0,0,0,	},
	{	TDX_ID_CA_PWDQACZBZ,		TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"�ܱ����������־",		0,0,0,0,0,	},
	{	TDX_ID_CA_CONNID,			TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"�û�����ID",			0,0,0,0,0,	},
	{	TDX_ID_UM_BROKERCODE,		TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"�����˴���",			0,0,0,0,0,	},
	{	TDX_ID_UM_BROKERBRANCH,		TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"������Ӫҵ��",			0,0,0,0,0,	},
	{	TDX_ID_UM_BROKERNAME,		TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"����������",			0,0,0,0,0,	},
	{	TDX_ID_UM_BROKERSTATUS,		TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"������״̬",			0,0,0,0,0,	},
	{	TDX_ID_UM_BROKERLEVEL,		TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"�����˼���",			0,0,0,0,0,	},
	{	TDX_ID_UM_UPBROKER,			TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"�ϼ�������",			0,0,0,0,0,	},
	{	TDX_ID_UM_BROKERNATIONALITY,TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"�����˹���",			0,0,0,0,0,	},
	{	TDX_ID_UM_BROKERPHONECODE,	TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"�����˵绰",			0,0,0,0,0,	},
	{	TDX_ID_UM_BROKERMOPHONE,	TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"�������ƶ��绰",		0,0,0,0,0,	},
	{	TDX_ID_UM_BROKEREMAIL,		TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"�����˵����ʼ�",		0,0,0,0,0,	},
	{	TDX_ID_UM_BROKERMSN,		TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"������MSN",			0,0,0,0,0,	},
	{	TDX_ID_UM_BROKERQQ,			TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"������QQ",				0,0,0,0,0,	},
	{	TDX_ID_UM_BROKERSEX,		TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"�������Ա�",			0,0,0,0,0,	},
	{	TDX_ID_UM_BROKERAGE,		TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"����������",			0,0,0,0,0,	},
	{	TDX_ID_UM_BROKERDEGREE,		TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"������ѧ��",			0,0,0,0,0,	},
	{	TDX_ID_UM_BROKERFAVOR,		TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"�����˲���ϰ��",		0,0,0,0,0,	},
	{	TDX_ID_UM_BROKERNATIVEPLACE,TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"�����˸�������",		0,0,0,0,0,	},
	{	TDX_ID_UM_BROKERQUAL,		TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"�����˴�ҵ�ʸ�",		0,0,0,0,0,	},
	{	TDX_ID_UM_BROKERSATISLEV,	TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"����������ȼ���",		0,0,0,0,0,	},
	{	TDX_ID_UM_BROKERPHOTOS,		TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"��������Ƭ",			0,0,0,0,0,	},
	{	TDX_ID_UM_BROKERNOTES,		TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"�����˱�ע",			0,0,0,0,0,	},
	{	TDX_ID_UM_BRANCHNAME,		TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"Ӫҵ������",			0,0,0,0,0,	},
	{	TDX_ID_UM_COMHOTLINE,		TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"��˾�ͻ�����",			0,0,0,0,0,	},
	{	TDX_ID_UM_BRANCHTRADEASK,	TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"Ӫҵ��������ѯ�绰",	0,0,0,0,0,	},
	{	TDX_ID_UM_BRANCHINVESTASK,	TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"Ӫҵ��Ͷ����ѯ�绰",	0,0,0,0,0,	},
	{	TDX_ID_UM_PASSEXAM,			TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"�Ƿ�ͨ������",			0,0,0,0,0,	},
	{	TDX_ID_UM_PRACTISETIME,		TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"��ҵʱ��",				0,0,0,0,0,	},
	{	TDX_ID_CA_MACHINENAME,		TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"�����ǳ�",				0,0,0,0,0,	},
	{	TDX_ID_CA_PROVISIONAL,		TDX_DT_STRING,	TDX_DISP_RIGHT,	  4,	"��ʱ��־",				0,0,0,0,0,	},
	{	TDX_ID_CA_MACHINEBINDTIME,	TDX_DT_DATE,	TDX_DISP_RIGHT,  12,	"��ʱ��",				0,0,0,0,0,	},
	{	TDX_ID_CA_USERNICK,			TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"�û��ǳ�",				0,0,0,0,0,	},
	{	TDX_ID_CA_CARDTYPE,			TDX_DT_STRING,	TDX_DISP_RIGHT,  4,		"֤������",				0,0,0,0,0,	},
	{	TDX_ID_CA_BIRTH,			TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"��������",				0,0,0,0,0,	},
	{	TDX_ID_CA_POSTCODE,			TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"��������",				0,0,0,0,0,	},
	{	TDX_ID_CA_ADDRESS,			TDX_DT_STRING,	TDX_DISP_RIGHT,  128,	"��ϵ��ַ",				0,0,0,0,0,	},
	{	TDX_ID_CA_OFFPHONE,			TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"�칫�绰",				0,0,0,0,0,	},
	{	TDX_ID_CA_HOMEPHONE,		TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"��ͥ�绰",				0,0,0,0,0,	},
	{	TDX_ID_CA_FAXPHONE,			TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"����绰",				0,0,0,0,0,	},
	{	TDX_ID_CA_EDUCATION,		TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"ѧ��",					0,0,0,0,0,	},
	{	TDX_ID_CA_TOKEN,			TDX_DT_STRING,	TDX_DISP_RIGHT,  512,	"����",					0,0,0,0,0,	},
	{	TDX_ID_JYMM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"��������",				0,0,0,0,0,	},
	{	TDX_ID_CA_YYBID,			TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"Ӫҵ��ID",				0,0,0,0,0,	},
	{	TDX_ID_CA_GD_XH,			TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"���",					0,0,0,0,0,	},
	{	TDX_ID_CA_GD_DATE,			TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"����",					0,0,0,0,0,	},
	{	TDX_ID_CA_GD_TIME,			TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"ʱ��",					0,0,0,0,0,	},
	{	TDX_ID_CA_GD_HARDINFO,		TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"�������������Ϣ",		0,0,0,0,0,	},
	{	TDX_ID_CA_GD_MOREINFO,		TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"������ǳ�",			0,0,0,0,0,	},
	{	TDX_ID_CA_GD_TERMINALTYPE,	TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"�ն�����",				0,0,0,0,0,	},
	{	TDX_ID_CA_USERSTOCK,		TDX_DT_STRING,	TDX_DISP_RIGHT,  1024,	"�û���ѡ��",			0,0,0,0,0,	},
	{	TDX_ID_XT_PARAM,			TDX_DT_STRING,	TDX_DISP_RIGHT,  80,	"����",					0,0,0,0,0,	},
	{	TDX_ID_XT_MODE,				TDX_DT_STRING,	TDX_DISP_RIGHT,  80,	"ģʽ",					0,0,0,0,0,	},
	{	TDX_ID_XT_DESCRIPTION,		TDX_DT_STRING,	TDX_DISP_RIGHT,  80,	"����",					0,0,0,0,0,	},
	{	TDX_ID_XT_REMARK,			TDX_DT_STRING,	TDX_DISP_RIGHT,  80,	"��ע",					0,0,0,0,0,	},
	{	TDX_ID_CA_TRADETIME,		TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"����ʱ��",				0,0,0,0,0,	},
	{	TDX_ID_CA_TRADETYPE,		TDX_DT_STRING,	TDX_DISP_RIGHT,  64,	"��������",				0,0,0,0,0,	},
	{	TDX_ID_CA_SCORE,			TDX_DT_LONG,	TDX_DISP_RIGHT,  8,		"����ֵ",				0,0,0,0,0,	},
	{	TDX_ID_CA_SID,				TDX_DT_LONG,	TDX_DISP_RIGHT,  8,		"���",					0,0,0,0,0,	},
	{	TDX_ID_CA_BINDTINE,			TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"��ʱ��",				0,0,0,0,0,	},
	{	TDX_ID_CA_UMAC,				TDX_DT_STRING,	TDX_DISP_RIGHT,  32,	"MAC��ַ",				0,0,0,0,0,	},
	{	TDX_ID_CA_REMARK,			TDX_DT_STRING,	TDX_DISP_RIGHT,  128,	"�������ע",			0,0,0,0,0,	},
	{	TDX_ID_CA_HARDINFO,			TDX_DT_STRING,	TDX_DISP_RIGHT,  128,	"����Ӳ����Ϣ",			1,0,0,0,0,	},
};

const FIELDINFO tdxRZFieldInfo[]=
{
//	{	�ֶ�����,					��������,		��ʾ(����)����,���,	�ֶ�˵��,				�������,	},

	{	TDX_ID_RZ_STARTTIME,		TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"��ʼʱ��",				0,0,0,0,0,	},
	{	TDX_ID_RZ_ENDTIME,			TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"����ʱ��",				0,0,0,0,0,	},
	{	TDX_ID_RZ_TCTIME,			TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"�������ĺ�ʱ",			0,0,0,0,0,	},
	{	TDX_ID_RZ_APITIME,			TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"API��ʱ",				0,0,0,0,0,	},
	{	TDX_ID_RZ_QUEUETIME,		TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"�ŶӺ�ʱ",				0,0,0,0,0,	},
	{	TDX_ID_RZ_AVGTCTIME,		TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"��������ƽ����ʱ",		0,0,0,0,0,	},
	{	TDX_ID_RZ_AVGAPITIME,		TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"APIƽ����ʱ",			0,0,0,0,0,	},
	{	TDX_ID_RZ_AVGQUEUETIME,		TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"�Ŷ�ƽ����ʱ",			0,0,0,0,0,	},
	{	TDX_ID_RZ_FUNCID,			TDX_DT_STRING,	TDX_DISP_RIGHT,  50,	"���ù���ID",			0,0,0,0,0,	},
	{	TDX_ID_RZ_FLAGRESULT,		TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"��������־",			0,0,0,0,0,	},
	{	TDX_ID_RZ_LOGID,			TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"��־��¼���",			0,0,0,0,0,	},
	{	TDX_ID_RZ_TCIP,				TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"��������IP",			0,0,0,0,0,	},
	{	TDX_ID_RZ_LOGTIME,			TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"��־��¼ʱ��",			0,0,0,0,0,	},
	{	TDX_ID_KHH,					TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"�ͻ���",				0,0,0,0,0,	},
	{	TDX_ID_KHMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"�ͻ�����",				0,0,0,0,0,	},
	{	TDX_ID_XT_BRANCHID,			TDX_DT_CHAR,	TDX_DISP_RIGHT,  10,	"Ӫҵ��ID",				0,0,0,0,0,	},
	{	TDX_ID_XT_IPADDR,			TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"IP��ַ",				0,0,0,0,0,	},
	{	TDX_ID_XT_MACADDR,			TDX_DT_STRING,	TDX_DISP_RIGHT,  24,	"MAC��ַ",				0,0,0,0,0,	},
	{	TDX_ID_ZJZH,				TDX_DT_STRING,	TDX_DISP_RIGHT,  16,	"�ʽ��ʺ�",				0,0,0,0,0,	},
	{	TDX_ID_RETINFO,				TDX_DT_STRING,	TDX_DISP_RIGHT,  80,	"������Ϣ",				0,0,0,0,0,	},
	{	TDX_ID_JYMM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"��������",				1,0,0,0,0,	},
	{	TDX_ID_XJYMM,				TDX_DT_STRING,	TDX_DISP_RIGHT,  12,	"�½�������",			1,0,0,0,0,	},
	{	TDX_ID_RZ_LEVER,			TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"�û�����",				0,0,0,0,0,	},
	{	TDX_ID_XT_STARTPOS,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"��ʼ���",				0,0,0,0,0,	},
	{	TDX_ID_KHQXDM,				TDX_DT_STRING,	TDX_DISP_RIGHT,   4,	"�ͻ�Ȩ�޴���",			0,0,0,0,0,	},
	{	TDX_ID_KHQXMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"�ͻ�Ȩ������",			0,0,0,0,0,	},
	{	TDX_ID_RZ_PAGEINDEX,		TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"ҳ�����",				1,0,0,0,0,	},
	{	TDX_ID_CZBZ,				TDX_DT_CHAR,	TDX_DISP_RIGHT,   1,	"������־",				1,0,0,0,0,	},
	{	TDX_ID_RZ_FUNCNUM,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"������Ŀ",				0,0,0,0,0,	},
	{	TDX_ID_RZ_FUNCBL,			TDX_DT_FLOAT,	TDX_DISP_RIGHT,   8,	"���ñ���",				0,0,0,0,0,	},
	{	TDX_ID_YWMC,				TDX_DT_STRING,	TDX_DISP_RIGHT,   8,	"��������",				0,0,0,0,0,	},
	{	TDX_ID_RZ_FUNCOKNUM,		TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"�ɹ���Ŀ",				0,0,0,0,0,	},
	{	TDX_ID_RZ_FUNCFAILNUM,		TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"ʧ����Ŀ",				0,0,0,0,0,	},
	{	TDX_ID_RZ_ITEMNUM,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"��¼����",				1,0,0,0,0,	},
	{	TDX_ID_RZ_CXFLAG,			TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"��ѯ���",				1,0,0,0,0,	},
	{	TDX_ID_RZ_DAY,				TDX_DT_LONG,	TDX_DISP_RIGHT,   8,	"����ʱ��",				0,0,0,0,0,	},
};


//---------------------------------------------------------------------------
// Part.III ��׼�ṹ����
//---------------------------------------------------------------------------

// ���ֵ�
const WORD tdxSimpleStructInfo[]=
{	// ��¼Э��
	TDX_ID_FUNC_REQ_ZHYCL,			// �˺�Ԥ���� 94
	TDX_ID_FUNC_ANS_ZHYCL,
	TDX_ID_FUNC_REQ_DLYCL,			// ��¼Ԥ���� 96
	TDX_ID_FUNC_ANS_DLYCL,
	TDX_ID_FUNC_REQ_JCKHJY,			// ���ɿͻ�У�� 98
	TDX_ID_FUNC_ANS_JCKHJY,
	TDX_ID_FUNC_REQ_KHJY,			// �ͻ�У�� 100
	TDX_ID_FUNC_ANS_KHJY,
};

// �����ֵ�
const WORD tdxCommonStructInfo[]=
{
	// ί�й��ܲ���
	TDX_ID_FUNC_REQ_KHJY,			// �ͻ�У�� 100
	TDX_ID_FUNC_ANS_KHJY,
	TDX_ID_FUNC_REQ_CXHQ,			// ��ѯ���� 102
	TDX_ID_FUNC_ANS_CXHQ,
	TDX_ID_FUNC_REQ_ZJYE,			// �ʽ���� 104
	TDX_ID_FUNC_ANS_ZJYE,
	TDX_ID_FUNC_REQ_XGMM,			// �޸����� 106
	TDX_ID_FUNC_ANS_XGMM,
	TDX_ID_FUNC_REQ_XGZJMM,			// �޸��ʽ����� 108
	TDX_ID_FUNC_ANS_XGZJMM,
	TDX_ID_FUNC_REQ_JSKMS,			// �������(��)�� 110
	TDX_ID_FUNC_ANS_JSKMS,
	TDX_ID_FUNC_REQ_CACHE,			// ȡ������Ϣ 112
	TDX_ID_FUNC_ANS_CACHE,
	TDX_ID_FUNC_REQ_XGGLZJZH,		// �޸Ĺ����ʽ��ʺ� 114
	TDX_ID_FUNC_ANS_XGGLZJZH,
	TDX_ID_FUNC_REQ_KHZX,			// �ͻ�ע�� 116
	TDX_ID_FUNC_ANS_KHZX,
	TDX_ID_FUNC_REQ_DYQXDZD,		// ����ȡ�����ʵ�(�ʼ�) 118
	TDX_ID_FUNC_ANS_DYQXDZD,
	TDX_ID_FUNC_REQ_WTDJZJ,			// ί�ж����ʽ� 120
	TDX_ID_FUNC_ANS_WTDJZJ,
	TDX_ID_FUNC_REQ_PRINTDZD,		// ��ӡ���ʵ� 122
	TDX_ID_FUNC_ANS_PRINTDZD,
	TDX_ID_FUNC_REQ_PRINTHZDZD,		// ��ӡ���ܶ��ʵ� 124
	TDX_ID_FUNC_ANS_PRINTHZDZD,
	TDX_ID_FUNC_REQ_PRINTJGD,		// ��ӡ���(Ӫҵ�������������ʹ��) 126
	TDX_ID_FUNC_ANS_PRINTJGD,
	TDX_ID_FUNC_REQ_XGTXMM,			// �޸�ͨѶ���� 128
	TDX_ID_FUNC_ANS_XGTXMM,
	TDX_ID_FUNC_REQ_ZHJD,			// �ʺŽⶳ 130
	TDX_ID_FUNC_ANS_ZHJD,
	TDX_ID_FUNC_REQ_ZJGJ,			// �ʽ�鼯 132
	TDX_ID_FUNC_ANS_ZJGJ,
	TDX_ID_FUNC_REQ_ZJZHJZZ,		// �ʽ��ʺż�ת�� 134
	TDX_ID_FUNC_ANS_ZJZHJZZ,
	TDX_ID_FUNC_REQ_TJWJJG,			// �ύ�ʾ��� 136
	TDX_ID_FUNC_ANS_TJWJJG,
	TDX_ID_FUNC_REQ_HQWJNR,			// ��ȡ�ʾ����� 138
	TDX_ID_FUNC_ANS_HQWJNR,
	TDX_ID_FUNC_REQ_HQZHZTBZ,		// ��ȡ�ʺ�״̬��־ 140
	TDX_ID_FUNC_ANS_HQZHZTBZ,
	TDX_ID_FUNC_REQ_CLCXMM,			// �����ѯ���� 142
	TDX_ID_FUNC_ANS_CLCXMM,
	TDX_ID_FUNC_REQ_TSZC,			// ����ע�� 144
	TDX_ID_FUNC_ANS_TSZC,
	TDX_ID_FUNC_REQ_TSZX,			// ����ע�� 146
	TDX_ID_FUNC_ANS_TSZX,
	TDX_ID_FUNC_REQ_ZZHCX,			// ���ʺŲ�ѯ 148
	TDX_ID_FUNC_ANS_ZZHCX,
	TDX_ID_FUNC_REQ_CLRZXX,			// ������֤��Ϣ 150
	TDX_ID_FUNC_ANS_CLRZXX,
	TDX_ID_FUNC_REQ_RZXXCX,			// ��֤��Ϣ��ѯ 152
	TDX_ID_FUNC_ANS_RZXXCX,
	TDX_ID_FUNC_REQ_KHJBXXCX,		// �ͻ�������Ϣ��ѯ 154
	TDX_ID_FUNC_ANS_KHJBXXCX,
	TDX_ID_FUNC_REQ_DZHTQY,			// ���Ӻ�ͬǩԼ 156
	TDX_ID_FUNC_ANS_DZHTQY,
	TDX_ID_FUNC_REQ_DZHTQYCX,		// ���Ӻ�ͬǩԼ��ѯ 158
	TDX_ID_FUNC_ANS_DZHTQYCX,
	TDX_ID_FUNC_REQ_DZHTLBCX,		// ���Ӻ�ͬ�б��ѯ 160
	TDX_ID_FUNC_ANS_DZHTLBCX,
	TDX_ID_FUNC_REQ_DZHTXXCX,		// ���Ӻ�ͬ��Ϣ��ѯ 162
	TDX_ID_FUNC_ANS_DZHTXXCX,
	TDX_ID_FUNC_REQ_RZLSCX,			// ��֤��ˮ��ѯ 164
	TDX_ID_FUNC_ANS_RZLSCX,
	TDX_ID_FUNC_REQ_KHYLXXCX,		// �ͻ�Ԥ����Ϣ��ѯ 166
	TDX_ID_FUNC_ANS_KHYLXXCX,
	TDX_ID_FUNC_REQ_KHYLXXXG,		// �ͻ�Ԥ����Ϣ�޸� 168
	TDX_ID_FUNC_ANS_KHYLXXXG,
	TDX_ID_FUNC_REQ_KHCZQR,			// �ͻ�����ȷ�� 170
	TDX_ID_FUNC_ANS_KHCZQR,
	TDX_ID_FUNC_REQ_FYZDCX,			// �����ֵ��ѯ 172
	TDX_ID_FUNC_ANS_FYZDCX,
	TDX_ID_FUNC_REQ_UPDATESESSION,	// ���»Ự��Ϣ 174
	TDX_ID_FUNC_ANS_UPDATESESSION,
	TDX_ID_FUNC_REQ_WJLSCX,			// �ʾ���ˮ��ѯ 176
	TDX_ID_FUNC_ANS_WJLSCX,
	TDX_ID_FUNC_REQ_SCINFO,			// ��ȡ�г���Ϣ 178
	TDX_ID_FUNC_ANS_SCINFO,

	// ί��������                                   
	TDX_ID_FUNC_REQ_WTCD,			// ί�г��� 200
	TDX_ID_FUNC_ANS_WTCD,
	TDX_ID_FUNC_REQ_PTGPWT,			// ��ͨ��Ʊί�� 202
	TDX_ID_FUNC_ANS_PTGPWT,
	TDX_ID_FUNC_REQ_ZQZGHS,			// ծȯת�ɻ��� 204
	TDX_ID_FUNC_ANS_ZQZGHS,
	TDX_ID_FUNC_REQ_XGDD,			// �޸Ķ��� 206
	TDX_ID_FUNC_ANS_XGDD,
	TDX_ID_FUNC_REQ_SGXG,			// �깺�¹� 208
	TDX_ID_FUNC_ANS_SGXG,
	TDX_ID_FUNC_REQ_XGSGXG,			// �¹��깺�޸� 210
	TDX_ID_FUNC_ANS_XGSGXG,
	TDX_ID_FUNC_REQ_XGSGCD,			// �¹��깺���� 212
	TDX_ID_FUNC_ANS_XGSGCD,
	TDX_ID_FUNC_REQ_PLWT,			// ����ί�� 214
	TDX_ID_FUNC_ANS_PLWT,
	TDX_ID_FUNC_REQ_PLCD,			// �������� 216
	TDX_ID_FUNC_ANS_PLCD,
	TDX_ID_FUNC_REQ_XZDDJC,			// ����������� 218
	TDX_ID_FUNC_ANS_XZDDJC,
	TDX_ID_FUNC_REQ_XGDDJC,			// �޸Ķ������ 220
	TDX_ID_FUNC_ANS_XGDDJC,

	// ������
	TDX_ID_FUNC_REQ_SDSZJCX,		// �������ʽ��ѯ 250
	TDX_ID_FUNC_ANS_SDSZJCX,
	TDX_ID_FUNC_REQ_SDSGFCX,		// �����ֹɷݲ�ѯ 252
	TDX_ID_FUNC_ANS_SDSGFCX,
	TDX_ID_FUNC_REQ_SDSWTCX,		// ������ί�в�ѯ 254
	TDX_ID_FUNC_ANS_SDSWTCX,
	TDX_ID_FUNC_REQ_SDSCJCX,		// �����ֳɽ���ѯ 256
	TDX_ID_FUNC_ANS_SDSCJCX,
	TDX_ID_FUNC_REQ_SDSLSCX,		// ��������ˮ��ѯ 258
	TDX_ID_FUNC_ANS_SDSLSCX,
	TDX_ID_FUNC_REQ_SDSXYZCCX,		// �����������ʲ���ѯ 260
	TDX_ID_FUNC_ANS_SDSXYZCCX,
	TDX_ID_FUNC_REQ_SDSZQXXCX,		// ������֤ȯ��Ϣ��ѯ 262
	TDX_ID_FUNC_ANS_SDSZQXXCX,
	TDX_ID_FUNC_REQ_SDSKMSLCX,		// �����ֿ���(��)������ѯ 264
	TDX_ID_FUNC_ANS_SDSKMSLCX,

	// ί��������չ(�Լ���������)
	TDX_ID_FUNC_REQ_FQZQ,			// ������ǩ 300
	TDX_ID_FUNC_ANS_FQZQ,
	TDX_ID_FUNC_REQ_FW_KHZLCX,		// (����)�ͻ����ϲ�ѯ 302
	TDX_ID_FUNC_ANS_FW_KHZLCX,
	TDX_ID_FUNC_REQ_FW_HQDTKL,		// (����)��ȡ��̬���� 304
	TDX_ID_FUNC_ANS_FW_HQDTKL,
	TDX_ID_FUNC_REQ_FW_CPDGPZ,		// (����)��Ʒ����Ʒ�� 306
	TDX_ID_FUNC_ANS_FW_CPDGPZ,
	TDX_ID_FUNC_REQ_FW_CPDGCX,		// (����)��Ʒ������ѯ 308
	TDX_ID_FUNC_ANS_FW_CPDGCX,
	TDX_ID_FUNC_REQ_FW_CPDGSZ,		// (����)��Ʒ�������� 310
	TDX_ID_FUNC_ANS_FW_CPDGSZ,
	TDX_ID_FUNC_REQ_FW_CPDGXG,		// (����)��Ʒ�����޸� 312
	TDX_ID_FUNC_ANS_FW_CPDGXG,
	TDX_ID_FUNC_REQ_FW_CPDGQX,		// (����)��Ʒ����ȡ�� 314
	TDX_ID_FUNC_ANS_FW_CPDGQX,
	TDX_ID_FUNC_REQ_FW_ZJLS,		// (����)�ʽ���ˮ 316
	TDX_ID_FUNC_ANS_FW_ZJLS,
	TDX_ID_FUNC_REQ_FW_PLHQCX,		// (����)���������ѯ 318
	TDX_ID_FUNC_ANS_FW_PLHQCX,
	TDX_ID_FUNC_REQ_FW_ZXLMCX,		// (����)��Ѷ��Ŀ��ѯ 320
	TDX_ID_FUNC_ANS_FW_ZXLMCX,
	TDX_ID_FUNC_REQ_FW_HQTSXX,		// (����)��ȡ��ʾ��Ϣ 322
	TDX_ID_FUNC_ANS_FW_HQTSXX,
	TDX_ID_FUNC_REQ_FW_TPFACX,		// (����)ͶƱ������ѯ 324
	TDX_ID_FUNC_ANS_FW_TPFACX,
	TDX_ID_FUNC_REQ_FW_TPXXCX,		// (����)ͶƱ��Ϣ��ѯ 326
	TDX_ID_FUNC_ANS_FW_TPXXCX,
	TDX_ID_FUNC_REQ_FW_TPJGTJ,		// (����)ͶƱ����ύ 328
	TDX_ID_FUNC_ANS_FW_TPJGTJ,
	TDX_ID_FUNC_REQ_FW_TPJGCX,		// (����)ͶƱ�����ѯ 330
	TDX_ID_FUNC_ANS_FW_TPJGCX,
	TDX_ID_FUNC_REQ_FW_TPTJCX,		// (����)ͶƱͳ�Ʋ�ѯ 332
	TDX_ID_FUNC_ANS_FW_TPTJCX,
	TDX_ID_FUNC_REQ_FW_TLZHDMCX,	// (����)������ϴ����ѯ 334
	TDX_ID_FUNC_ANS_FW_TLZHDMCX,
	TDX_ID_FUNC_REQ_FW_TLZHCFCX,	// (����)������ϳɷֲ�ѯ 336
	TDX_ID_FUNC_ANS_FW_TLZHCFCX,
	TDX_ID_FUNC_REQ_FW_DDDLCZ,		// (����)�����¼���� 338
	TDX_ID_FUNC_ANS_FW_DDDLCZ,
	TDX_ID_FUNC_REQ_FW_PLXJCX,		// (����)�����ּ۲�ѯ 340
	TDX_ID_FUNC_ANS_FW_PLXJCX,
	TDX_ID_FUNC_REQ_FW_XXDY,		// (����)��Ϣ���� 342
	TDX_ID_FUNC_ANS_FW_XXDY,
	TDX_ID_FUNC_REQ_FW_KHKCL,		// (����)�ͻ������� 344
	TDX_ID_FUNC_ANS_FW_KHKCL,
	TDX_ID_FUNC_REQ_FW_SCPZXX,		// (����)�ϴ�������Ϣ 346
	TDX_ID_FUNC_ANS_FW_SCPZXX,
	TDX_ID_FUNC_REQ_FW_XZPZXX,		// (����)����������Ϣ 348
	TDX_ID_FUNC_ANS_FW_XZPZXX,
	TDX_ID_FUNC_REQ_FW_PZXXZYCX,	// (����)������ϢժҪ��ѯ 350
	TDX_ID_FUNC_ANS_FW_PZXXZYCX,
	TDX_ID_FUNC_REQ_FW_CLKHCS,		// (����)����ͻ����� 352
	TDX_ID_FUNC_ANS_FW_CLKHCS,
	TDX_ID_FUNC_REQ_FW_PDLBCX,		// (����)����б��ѯ 354
	TDX_ID_FUNC_ANS_FW_PDLBCX,
	TDX_ID_FUNC_REQ_FW_PDLSLR,		// (����)�����ˮ¼�� 356
	TDX_ID_FUNC_ANS_FW_PDLSLR,
	TDX_ID_FUNC_REQ_FW_PDLSCX,		// (����)�����ˮ��ѯ 358
	TDX_ID_FUNC_ANS_FW_PDLSCX,
	TDX_ID_FUNC_REQ_FW_ZZYWSF,		// (����)��ֵҵ���շ� 360
	TDX_ID_FUNC_ANS_FW_ZZYWSF,

	// ���͹���(ֻ��Ӧ����Ч)
	TDX_ID_FUNC_REQ_PUSH_QZTC,		// (����)ǿ���˳� 400 [���͹���,����ʹ��]
	TDX_ID_FUNC_ANS_PUSH_QZTC,		// (����)ǿ���˳� 401
	TDX_ID_FUNC_REQ_PUSH_XXTZ,		// (����)��Ϣ֪ͨ 402 [���͹���,����ʹ��]
	TDX_ID_FUNC_ANS_PUSH_XXTZ,		// (����)��Ϣ֪ͨ 403
	TDX_ID_FUNC_REQ_PUSH_GGXX,		// (����)������Ϣ 404 [���͹���,����ʹ��]
	TDX_ID_FUNC_ANS_PUSH_GGXX,		// (����)������Ϣ 405

	// �ֻ�����
	TDX_ID_FUNC_REQ_MOBILE_ZQCX,	// (�ֻ�)֤ȯ��ѯ 500
	TDX_ID_FUNC_ANS_MOBILE_ZQCX,
	TDX_ID_FUNC_REQ_MOBILE_GFCX,	// (�ֻ�)�ɷݲ�ѯ 502
	TDX_ID_FUNC_ANS_MOBILE_GFCX,
	TDX_ID_FUNC_REQ_MOBILE_ZJCX,	// (�ֻ�)�ʽ��ѯ 504
	TDX_ID_FUNC_ANS_MOBILE_ZJCX,
	TDX_ID_FUNC_REQ_MOBILE_CDCX,	// (�ֻ�)������ѯ 506
	TDX_ID_FUNC_ANS_MOBILE_CDCX,
	TDX_ID_FUNC_REQ_MOBILE_WTCX,	// (�ֻ�)ί�в�ѯ 508
	TDX_ID_FUNC_ANS_MOBILE_WTCX,
	TDX_ID_FUNC_REQ_MOBILE_CJCX,	// (�ֻ�)�ɽ���ѯ 510
	TDX_ID_FUNC_ANS_MOBILE_CJCX,
	TDX_ID_FUNC_REQ_MOBILE_ZZCX,	// (�ֻ�)ת�˲�ѯ 512
	TDX_ID_FUNC_ANS_MOBILE_ZZCX,
	TDX_ID_FUNC_REQ_MOBILE_LSCX,	// (�ֻ�)��ˮ��ѯ 514
	TDX_ID_FUNC_ANS_MOBILE_LSCX,
	TDX_ID_FUNC_REQ_MOBILE_JGCX,	// (�ֻ�)�����ѯ 516
	TDX_ID_FUNC_ANS_MOBILE_JGCX,
	TDX_ID_FUNC_REQ_MOBILE_DZCX,	// (�ֻ�)���˲�ѯ 518
	TDX_ID_FUNC_ANS_MOBILE_DZCX,
	TDX_ID_FUNC_REQ_MOBILE_YXSBHQCX,// (�ֻ�)�����걨�����ѯ 520
	TDX_ID_FUNC_ANS_MOBILE_YXSBHQCX,
	TDX_ID_FUNC_REQ_MOBILE_LSWTCX,	// (�ֻ�)��ʷί�в�ѯ 522
	TDX_ID_FUNC_ANS_MOBILE_LSWTCX,
	TDX_ID_FUNC_REQ_MOBILE_LSCJCX,	// (�ֻ�)��ʷ�ɽ���ѯ 524
	TDX_ID_FUNC_ANS_MOBILE_LSCJCX,
	TDX_ID_FUNC_REQ_MOBILE_PHZQCX,	// (�ֻ�)�����ǩ��ѯ 526
	TDX_ID_FUNC_ANS_MOBILE_PHZQCX,
	TDX_ID_FUNC_REQ_MOBILE_RZLSCX,	// (�ֻ�)��֤��ˮ��ѯ 528
	TDX_ID_FUNC_ANS_MOBILE_RZLSCX,
	TDX_ID_FUNC_REQ_MOBILE_JJCDCX,	// (�ֻ�)���𳷵���ѯ 530
	TDX_ID_FUNC_ANS_MOBILE_JJCDCX,
	TDX_ID_FUNC_REQ_MOBILE_JJDRWTCX,// (�ֻ�)������ί�в�ѯ 532
	TDX_ID_FUNC_ANS_MOBILE_JJDRWTCX,
	TDX_ID_FUNC_REQ_MOBILE_JJLSWTCX,// (�ֻ�)������ʷί�в�ѯ 534
	TDX_ID_FUNC_ANS_MOBILE_JJLSWTCX,
	TDX_ID_FUNC_REQ_MOBILE_JJDRCJCX,// (�ֻ�)�����ճɽ���ѯ 536
	TDX_ID_FUNC_ANS_MOBILE_JJDRCJCX,
	TDX_ID_FUNC_REQ_MOBILE_JJLSCJCX,// (�ֻ�)������ʷ�ɽ���ѯ 538
	TDX_ID_FUNC_ANS_MOBILE_JJLSCJCX,
	TDX_ID_FUNC_REQ_MOBILE_JJZHCX,	// (�ֻ�)�����˺Ų�ѯ 540
	TDX_ID_FUNC_ANS_MOBILE_JJZHCX,
	TDX_ID_FUNC_REQ_MOBILE_JJGSCX,	// (�ֻ�)����˾��ѯ 542
	TDX_ID_FUNC_ANS_MOBILE_JJGSCX,
	TDX_ID_FUNC_REQ_MOBILE_JJDMCX,	// (�ֻ�)��������ѯ 544
	TDX_ID_FUNC_ANS_MOBILE_JJDMCX,
	TDX_ID_FUNC_REQ_MOBILE_JJFECX,	// (�ֻ�)����ݶ��ѯ 546
	TDX_ID_FUNC_ANS_MOBILE_JJFECX,
	TDX_ID_FUNC_REQ_MOBILE_JJDZCX,	// (�ֻ�)������˲�ѯ 548
	TDX_ID_FUNC_ANS_MOBILE_JJDZCX,
	TDX_ID_FUNC_REQ_MOBILE_JJJGCX,	// (�ֻ�)���𽻸��ѯ 550
	TDX_ID_FUNC_ANS_MOBILE_JJJGCX,
	TDX_ID_FUNC_REQ_MOBILE_JJFJYWTCX,// (�ֻ�)����ǽ���ί�в�ѯ 552
	TDX_ID_FUNC_ANS_MOBILE_JJFJYWTCX,

	TDX_ID_FUNC_REQ_MOBILE_QHHYCX,	// (�ֻ�)�ڻ���Լ��ѯ 560
	TDX_ID_FUNC_ANS_MOBILE_QHHYCX,
	TDX_ID_FUNC_REQ_MOBILE_QHZHHYCX,// (�ֻ�)�ڻ���Ϻ�Լ��ѯ 562
	TDX_ID_FUNC_ANS_MOBILE_QHZHHYCX,
	TDX_ID_FUNC_REQ_MOBILE_QHZHCCCX,// (�ֻ�)�ڻ���ϳֲֲ�ѯ 564
	TDX_ID_FUNC_ANS_MOBILE_QHZHCCCX,
	TDX_ID_FUNC_REQ_MOBILE_QHZHWTCX,// (�ֻ�)�ڻ����ί�в�ѯ 566
	TDX_ID_FUNC_ANS_MOBILE_QHZHWTCX,
	TDX_ID_FUNC_REQ_MOBILE_QHZHCLCX,// (�ֻ�)�ڻ���ϲ��Բ�ѯ 568
	TDX_ID_FUNC_ANS_MOBILE_QHZHCLCX,
	TDX_ID_FUNC_REQ_MOBILE_GFHZCX,	// (�ֻ�)�ɷݻ��ܲ�ѯ 570
	TDX_ID_FUNC_ANS_MOBILE_GFHZCX,
	TDX_ID_FUNC_REQ_MOBILE_WTHZCX,	// (�ֻ�)ί�л��ܲ�ѯ 572
	TDX_ID_FUNC_ANS_MOBILE_WTHZCX,
	TDX_ID_FUNC_REQ_MOBILE_CJHZCX,	// (�ֻ�)�ɽ����ܲ�ѯ 574
	TDX_ID_FUNC_ANS_MOBILE_CJHZCX,
	TDX_ID_FUNC_REQ_MOBILE_CJMXCX,	// (�ֻ�)�ɽ���ϸ��ѯ 576
	TDX_ID_FUNC_ANS_MOBILE_CJMXCX,

	TDX_ID_FUNC_REQ_MOBILE_XYRZMRPTCX,	// (�ֻ�)���������������ײ�ѯ 600
	TDX_ID_FUNC_ANS_MOBILE_XYRZMRPTCX,
	TDX_ID_FUNC_REQ_MOBILE_XYRQMCPTCX,	// (�ֻ�)������ȯ�������ײ�ѯ 602
	TDX_ID_FUNC_ANS_MOBILE_XYRQMCPTCX,
	TDX_ID_FUNC_REQ_MOBILE_XYMCHKPTCX,	// (�ֻ�)���������������ײ�ѯ 604
	TDX_ID_FUNC_ANS_MOBILE_XYMCHKPTCX,
	TDX_ID_FUNC_REQ_MOBILE_XYMRHQPTCX,	// (�ֻ�)�������뻹ȯ���ײ�ѯ 606
	TDX_ID_FUNC_ANS_MOBILE_XYMRHQPTCX,
	TDX_ID_FUNC_REQ_MOBILE_XYXJHKPTCX,	// (�ֻ�)�����ֽ𻹿����ײ�ѯ 608
	TDX_ID_FUNC_ANS_MOBILE_XYXJHKPTCX,
	TDX_ID_FUNC_REQ_MOBILE_XYXQHQPTCX,	// (�ֻ�)������ȯ��ȯ���ײ�ѯ 610
	TDX_ID_FUNC_ANS_MOBILE_XYXQHQPTCX,
	TDX_ID_FUNC_REQ_MOBILE_XYYQHZPTCX,	// (�ֻ�)������ȯ��ת���ײ�ѯ 612
	TDX_ID_FUNC_ANS_MOBILE_XYYQHZPTCX,
	TDX_ID_FUNC_REQ_MOBILE_XYDBHZPTCX,	// (�ֻ�)���õ�����ת���ײ�ѯ 614
	TDX_ID_FUNC_ANS_MOBILE_XYDBHZPTCX,
	TDX_ID_FUNC_REQ_MOBILE_XYDBZRPTCX,	// (�ֻ�)���õ���ת�����ײ�ѯ 616
	TDX_ID_FUNC_ANS_MOBILE_XYDBZRPTCX,
	TDX_ID_FUNC_REQ_MOBILE_XYDBZCPTCX,	// (�ֻ�)���õ���ת�����ײ�ѯ 618
	TDX_ID_FUNC_ANS_MOBILE_XYDBZCPTCX,
	TDX_ID_FUNC_REQ_MOBILE_XYZCXXCX,	// (�ֻ�)�����ʲ���Ϣ��ѯ 620
	TDX_ID_FUNC_ANS_MOBILE_XYZCXXCX,
	TDX_ID_FUNC_REQ_MOBILE_XYGFXXCX,	// (�ֻ�)���ùɷ���Ϣ��ѯ 622
	TDX_ID_FUNC_ANS_MOBILE_XYGFXXCX,
	TDX_ID_FUNC_REQ_MOBILE_XYBDZQCX,	// (�ֻ�)���ñ��֤ȯ��ѯ 624
	TDX_ID_FUNC_ANS_MOBILE_XYBDZQCX,
	TDX_ID_FUNC_REQ_MOBILE_XYZJHZCX,	// (�ֻ�)����ֱ�ӻ�ת��ѯ 626
	TDX_ID_FUNC_ANS_MOBILE_XYZJHZCX,
	TDX_ID_FUNC_REQ_MOBILE_XYLXFYCX,	// (�ֻ�)������Ϣ���ò�ѯ 628
	TDX_ID_FUNC_ANS_MOBILE_XYLXFYCX,
	TDX_ID_FUNC_REQ_MOBILE_XYWPHYCX,	// (�ֻ�)����δƽ��Լ��ѯ 630
	TDX_ID_FUNC_ANS_MOBILE_XYWPHYCX,
	TDX_ID_FUNC_REQ_MOBILE_XYYPHYCX,	// (�ֻ�)������ƽ��Լ��ѯ 632
	TDX_ID_FUNC_ANS_MOBILE_XYYPHYCX,
	TDX_ID_FUNC_REQ_MOBILE_XYDRHYCX,	// (�ֻ�)���õ��պ�Լ��ѯ 634
	TDX_ID_FUNC_ANS_MOBILE_XYDRHYCX,
	TDX_ID_FUNC_REQ_MOBILE_XYRZHYCX,	// (�ֻ�)�������ʺ�Լ��ѯ 636
	TDX_ID_FUNC_ANS_MOBILE_XYRZHYCX,
	TDX_ID_FUNC_REQ_MOBILE_XYRQHYCX,	// (�ֻ�)������ȯ��Լ��ѯ 638
	TDX_ID_FUNC_ANS_MOBILE_XYRQHYCX,
	TDX_ID_FUNC_REQ_MOBILE_XYZJFZCX,	// (�ֻ�)�����ʽ�ծ��ѯ 640
	TDX_ID_FUNC_ANS_MOBILE_XYZJFZCX,
	TDX_ID_FUNC_REQ_MOBILE_XYGFFZCX,	// (�ֻ�)���ùɷݸ�ծ��ѯ 642
	TDX_ID_FUNC_ANS_MOBILE_XYGFFZCX,
	TDX_ID_FUNC_REQ_MOBILE_XYJYDBPZQCX,	// (�ֻ�)���ý��׵���Ʒ֤ȯ��ѯ 644
	TDX_ID_FUNC_ANS_MOBILE_XYJYDBPZQCX,
	TDX_ID_FUNC_REQ_MOBILE_XYJYFJYHZCX,	// (�ֻ�)���ý��׷ǽ��׻�ת��ѯ 646
	TDX_ID_FUNC_ANS_MOBILE_XYJYFJYHZCX,	
	TDX_ID_FUNC_REQ_MOBILE_XYJYFZLSCX,	// (�ֻ�)���ý��׸�ծ��ˮ��ѯ 648
	TDX_ID_FUNC_ANS_MOBILE_XYJYFZLSCX,

	TDX_ID_FUNC_REQ_MOBILE_ETFWTCX,		// (�ֻ�)ETFί�в�ѯ 700
	TDX_ID_FUNC_ANS_MOBILE_ETFWTCX,
	TDX_ID_FUNC_REQ_MOBILE_ETFCJCX,		// (�ֻ�)ETF�ɽ���ѯ 702
	TDX_ID_FUNC_ANS_MOBILE_ETFCJCX,

	TDX_ID_FUNC_REQ_MOBILE_LCCPFECX,	// (�ֻ�)��Ʋ�Ʒ�ݶ��ѯ 750
	TDX_ID_FUNC_ANS_MOBILE_LCCPFECX,
	TDX_ID_FUNC_REQ_MOBILE_LCCPWTCX,	// (�ֻ�)��Ʋ�Ʒί�в�ѯ 752
	TDX_ID_FUNC_ANS_MOBILE_LCCPWTCX,
	TDX_ID_FUNC_REQ_MOBILE_LCCPCJCX,	// (�ֻ�)��Ʋ�Ʒ�ɽ���ѯ 754
	TDX_ID_FUNC_ANS_MOBILE_LCCPCJCX,
	TDX_ID_FUNC_REQ_MOBILE_LCCPDMCX,	// (�ֻ�)��Ʋ�Ʒ�����ѯ 756
	TDX_ID_FUNC_ANS_MOBILE_LCCPDMCX,
	TDX_ID_FUNC_REQ_MOBILE_LCCPDQDESGCX,// (�ֻ�)��Ʋ�Ʒ���ڶ����깺��ѯ 758
	TDX_ID_FUNC_ANS_MOBILE_LCCPDQDESGCX,

	TDX_ID_FUNC_REQ_MOBILE_YHLCCPDMCX,	// (�ֻ�)������Ʋ�Ʒ�����ѯ 790
	TDX_ID_FUNC_ANS_MOBILE_YHLCCPDMCX,	
	TDX_ID_FUNC_REQ_MOBILE_YHLCCPFECX,	// (�ֻ�)������Ʋ�Ʒ�ݶ��ѯ 792
	TDX_ID_FUNC_ANS_MOBILE_YHLCCPFECX,	
	TDX_ID_FUNC_REQ_MOBILE_YHLCCPWTCX,	// (�ֻ�)������Ʋ�Ʒί�в�ѯ 794
	TDX_ID_FUNC_ANS_MOBILE_YHLCCPWTCX,	
	TDX_ID_FUNC_REQ_MOBILE_YHLCCPCJCX,	// (�ֻ�)������Ʋ�Ʒ�ɽ���ѯ 796
	TDX_ID_FUNC_ANS_MOBILE_YHLCCPCJCX,

	// ��֤ת����
	TDX_ID_FUNC_REQ_YZZZ,			// ��֤ת�� 900
	TDX_ID_FUNC_ANS_YZZZ,
	TDX_ID_FUNC_REQ_YHLS,			// ������ˮ 902
	TDX_ID_FUNC_ANS_YHLS,
	TDX_ID_FUNC_REQ_YHYE,			// ������� 904
	TDX_ID_FUNC_ANS_YHYE,
	TDX_ID_FUNC_REQ_XGYHMM,			// �޸��������� 906
	TDX_ID_FUNC_ANS_XGYHMM,
	TDX_ID_FUNC_REQ_YHXX,			// ��ѯ������Ϣ 908
	TDX_ID_FUNC_ANS_YHXX,
	// �������
	TDX_ID_FUNC_REQ_SFCGZZ,			// �������ת�� 910
	TDX_ID_FUNC_ANS_SFCGZZ,
	TDX_ID_FUNC_REQ_SFZZCX,			// ����ת�ʲ�ѯ 912
	TDX_ID_FUNC_ANS_SFZZCX,
	TDX_ID_FUNC_REQ_SFYECX,			// ��������ѯ 914
	TDX_ID_FUNC_ANS_SFYECX,
	// ת����չ(�����۹ɵ������г�����չҵ��)
	TDX_ID_FUNC_REQ_ZZXG,			// ת���޸� 916
	TDX_ID_FUNC_ANS_ZZXG,
	TDX_ID_FUNC_REQ_ZZQX,			// ת��ȡ�� 918
	TDX_ID_FUNC_ANS_ZZQX,
	TDX_ID_FUNC_REQ_KQZJCX,			// ��ȡ�ʽ��ѯ 920
	TDX_ID_FUNC_ANS_KQZJCX,
	TDX_ID_FUNC_REQ_ZZYHCX,			// ת�����в�ѯ 922
	TDX_ID_FUNC_ANS_ZZYHCX,
	TDX_ID_FUNC_REQ_YHZHJZZ,		// �����˻���ת�� 924
	TDX_ID_FUNC_ANS_YHZHJZZ,
	TDX_ID_FUNC_REQ_YDZJZZ,			// Զ���ʽ�ת�� 926
	TDX_ID_FUNC_ANS_YDZJZZ,
	TDX_ID_FUNC_REQ_YDZZCX,			// Զ��ת�˲�ѯ 928
	TDX_ID_FUNC_ANS_YDZZCX,
	TDX_ID_FUNC_REQ_YDZJCX,			// Զ���ʽ��ѯ 930
	TDX_ID_FUNC_ANS_YDZJCX,
	TDX_ID_FUNC_REQ_YDKZCX,			// Զ�˿�ת��ѯ 932
	TDX_ID_FUNC_ANS_YDKZCX,
	TDX_ID_FUNC_REQ_YHKLBCX,		// ���п��б��ѯ 934
	TDX_ID_FUNC_ANS_YHKLBCX,
	TDX_ID_FUNC_REQ_YHKXXCX,		// ���п���Ϣ��ѯ 936
	TDX_ID_FUNC_ANS_YHKXXCX,
	TDX_ID_FUNC_REQ_YHKXXXG,		// ���п���Ϣ�޸� 938
	TDX_ID_FUNC_ANS_YHKXXXG,
	TDX_ID_FUNC_REQ_YHKBGCZ,		// ���п�������� 940
	TDX_ID_FUNC_ANS_YHKBGCZ,
	TDX_ID_FUNC_REQ_YHKFLCX,		// ���п����ʲ�ѯ 942
	TDX_ID_FUNC_ANS_YHKFLCX,
	TDX_ID_FUNC_REQ_ZHJZZLSCX,		// �˺ż�ת����ˮ��ѯ 944
	TDX_ID_FUNC_ANS_ZHJZZLSCX,
	TDX_ID_FUNC_REQ_ZHJZZDRLSCX,	// �˺ż�ת�˵�����ˮ��ѯ 946
	TDX_ID_FUNC_ANS_ZHJZZDRLSCX,
	TDX_ID_FUNC_REQ_YHYELSCX,		// ���������ˮ��ѯ 948
	TDX_ID_FUNC_ANS_YHYELSCX,
	TDX_ID_FUNC_REQ_JHZZLSCX,		// �ƻ�ת����ˮ��ѯ 950
	TDX_ID_FUNC_ANS_JHZZLSCX,
	TDX_ID_FUNC_REQ_DCGYHLSCX,		// ����������ˮ��ѯ 952
	TDX_ID_FUNC_ANS_DCGYHLSCX,
	TDX_ID_FUNC_REQ_DCGZHTB,		// �����˺�ͬ�� 954
	TDX_ID_FUNC_ANS_DCGZHTB,
	TDX_ID_FUNC_REQ_HHYWCZ,			// ����ҵ����� 990
	TDX_ID_FUNC_ANS_HHYWCZ,
	TDX_ID_FUNC_REQ_HHYHCX,			// �������в�ѯ 992
	TDX_ID_FUNC_ANS_HHYHCX,
	TDX_ID_FUNC_REQ_HHHLCX,			// ������ʲ�ѯ 994
	TDX_ID_FUNC_ANS_HHHLCX,
	TDX_ID_FUNC_REQ_HHWTCX,			// ����ί�в�ѯ 996
	TDX_ID_FUNC_ANS_HHWTCX,

	// ��ѯ��
	TDX_ID_FUNC_REQ_CDCX,			// �ɳ�����ѯ 1100
	TDX_ID_FUNC_ANS_CDCX,
	TDX_ID_FUNC_REQ_DRWTCX,			// ����ί�в�ѯ 1102
	TDX_ID_FUNC_ANS_DRWTCX,
	TDX_ID_FUNC_REQ_LSWTCX,			// ��ʷί�в�ѯ 1104
	TDX_ID_FUNC_ANS_LSWTCX,
	TDX_ID_FUNC_REQ_WTCX,			// ί�в�ѯ(�����պ���ʷί��) 1106
	TDX_ID_FUNC_ANS_WTCX,
	TDX_ID_FUNC_REQ_DRCJCX,			// ���ճɽ���ѯ 1108
	TDX_ID_FUNC_ANS_DRCJCX,
	TDX_ID_FUNC_REQ_LSCJCX,			// ��ʷ�ɽ���ѯ 1110
	TDX_ID_FUNC_ANS_LSCJCX,
	TDX_ID_FUNC_REQ_CJCX,			// �ɽ���ѯ(�����պ���ʷ�ɽ�) 1112
	TDX_ID_FUNC_ANS_CJCX,
	TDX_ID_FUNC_REQ_GFCX,			// �ɷݲ�ѯ 1114
	TDX_ID_FUNC_ANS_GFCX,
	TDX_ID_FUNC_REQ_XGPH,			// �¹���� 1116
	TDX_ID_FUNC_ANS_XGPH,
	TDX_ID_FUNC_REQ_ZJLS,			// �ʽ���ˮ 1118
	TDX_ID_FUNC_ANS_ZJLS,
	TDX_ID_FUNC_REQ_JGD,			// ��� 1120
	TDX_ID_FUNC_ANS_JGD,
	TDX_ID_FUNC_REQ_GDCX,			// �ɶ���ѯ 1122
	TDX_ID_FUNC_ANS_GDCX,
	TDX_ID_FUNC_REQ_ZQXX,			// ȡ֤ȯ��Ϣ 1124
	TDX_ID_FUNC_ANS_ZQXX,
	TDX_ID_FUNC_REQ_ZQCX,			// ��ǩ��ѯ 1126
	TDX_ID_FUNC_ANS_ZQCX,
	TDX_ID_FUNC_REQ_XGCBJ,			// �޸ĳɱ��� 1128
	TDX_ID_FUNC_ANS_XGCBJ,
	TDX_ID_FUNC_REQ_XGLXFS,			// (��ѯ)�޸���ϵ��ʽ 1130
	TDX_ID_FUNC_ANS_XGLXFS,
	TDX_ID_FUNC_REQ_DZD,			// ���ʵ� 1132
	TDX_ID_FUNC_ANS_DZD,
	TDX_ID_FUNC_REQ_PSQYCX,			// ����Ȩ���ѯ 1134
	TDX_ID_FUNC_ANS_PSQYCX,
	TDX_ID_FUNC_REQ_QZXXCX,			// Ȩ֤��Ϣ��ѯ 1136
	TDX_ID_FUNC_ANS_QZXXCX,
	TDX_ID_FUNC_REQ_CJHZCX,			// �ɽ����ܲ�ѯ 1138
	TDX_ID_FUNC_ANS_CJHZCX,
	TDX_ID_FUNC_REQ_GFHZCX,			// �ɷݻ��ܲ�ѯ 1140
	TDX_ID_FUNC_ANS_GFHZCX,
	TDX_ID_FUNC_REQ_KTXY,			// Ȩ֤��ͨȡ�� 1142
	TDX_ID_FUNC_ANS_KTXY,
	TDX_ID_FUNC_REQ_YWTCX,			// ��ί�в�ѯ 1144
	TDX_ID_FUNC_ANS_YWTCX,
	TDX_ID_FUNC_REQ_QDXY,			// ǩ��Э�� 1146
	TDX_ID_FUNC_ANS_QDXY,
	TDX_ID_FUNC_REQ_ZTZJCX,			// ��;�ʽ��ѯ(ƽ��֤ȯ) 1148
	TDX_ID_FUNC_ANS_ZTZJCX,
	TDX_ID_FUNC_REQ_JGXZZ,			// �����ת�� 1150
	TDX_ID_FUNC_ANS_JGXZZ,
	TDX_ID_FUNC_REQ_FZDM,			// ��ݸ��ȡ������� 1152
	TDX_ID_FUNC_ANS_FZDM,
	TDX_ID_FUNC_REQ_HQXYNR,			// ��ȡЭ������ 1154
	TDX_ID_FUNC_ANS_HQXYNR,
	TDX_ID_FUNC_REQ_HQIPOLB,		// ��ȡIPO�б� 1156
	TDX_ID_FUNC_ANS_HQIPOLB,
	TDX_ID_FUNC_REQ_IPOXXCX,		// IPO��Ϣ��ѯ 1158
	TDX_ID_FUNC_ANS_IPOXXCX,
	TDX_ID_FUNC_REQ_YYCX,			// Ԥ��ҪԼ��ѯ 1160
	TDX_ID_FUNC_ANS_YYCX,
	TDX_ID_FUNC_REQ_YYCD,			// Ԥ��ҪԼ���� 1162
	TDX_ID_FUNC_ANS_YYCD,
	TDX_ID_FUNC_REQ_YYSB,			// Ԥ��ҪԼ�걨 1164
	TDX_ID_FUNC_ANS_YYSB,
	TDX_ID_FUNC_REQ_ZYHG,			// ��Ѻ�ع� 1166
	TDX_ID_FUNC_ANS_ZYHG,
	TDX_ID_FUNC_REQ_WJSCJMXCX,		// δ���ճɽ���ϸ��ѯ 1168
	TDX_ID_FUNC_ANS_WJSCJMXCX,
	TDX_ID_FUNC_REQ_CGYYCQ,			// ���ԤԼ��ȡҵ�� 1170
	TDX_ID_FUNC_ANS_CGYYCQ,
	TDX_ID_FUNC_REQ_CGYYCQCX,		// ���ԤԼ��ȡҵ���ѯ 1172
	TDX_ID_FUNC_ANS_CGYYCQCX,
	TDX_ID_FUNC_REQ_WTHZCX,			// ί�л��ܲ�ѯ 1174
	TDX_ID_FUNC_ANS_WTHZCX,
	TDX_ID_FUNC_REQ_ZJMXCX,			// �ʽ���ϸ��ѯ 1176
	TDX_ID_FUNC_ANS_ZJMXCX,
	TDX_ID_FUNC_REQ_CXXZCGYH,		// ��ѯѡ�������� 1178
	TDX_ID_FUNC_ANS_CXXZCGYH,
	TDX_ID_FUNC_REQ_XZCGYH,			// ѡ�������� 1180
	TDX_ID_FUNC_ANS_XZCGYH,
	TDX_ID_FUNC_REQ_CXXYXX,			// ��ѯЭ����Ϣ 1182
	TDX_ID_FUNC_ANS_CXXYXX,
	TDX_ID_FUNC_REQ_LSCJHZCX,		// ��ʷ�ɽ����ܲ�ѯ 1184
	TDX_ID_FUNC_ANS_LSCJHZCX,
	TDX_ID_FUNC_REQ_CJMXCX,			// �ɽ���ϸ��ѯ 1186
	TDX_ID_FUNC_ANS_CJMXCX,
	TDX_ID_FUNC_REQ_WTCXMX,			// ί�в�ѯ��ϸ 1188
	TDX_ID_FUNC_ANS_WTCXMX,
	TDX_ID_FUNC_REQ_CJCXMX,			// �ɽ���ѯ��ϸ 1190
	TDX_ID_FUNC_ANS_CJCXMX,
	TDX_ID_FUNC_REQ_YXSBHQCX,		// �����걨�����ѯ 1192
	TDX_ID_FUNC_ANS_YXSBHQCX,
	TDX_ID_FUNC_REQ_PLWTCX,			// ����ί�в�ѯ 1194
	TDX_ID_FUNC_ANS_PLWTCX,
	TDX_ID_FUNC_REQ_LOFHBXGDMCX,	// LOF�ϲ���ش����ѯ 1196
	TDX_ID_FUNC_ANS_LOFHBXGDMCX,
	TDX_ID_FUNC_REQ_LOFFCXGDMCX,	// LOF�ֲ���ش����ѯ 1198
	TDX_ID_FUNC_ANS_LOFFCXGDMCX,
	TDX_ID_FUNC_REQ_LOFPHYWDRWTCX,	// LOF�̺�ҵ����ί�в�ѯ 1200
	TDX_ID_FUNC_ANS_LOFPHYWDRWTCX,
	TDX_ID_FUNC_REQ_LOFPHYWLSWTCX,	// LOF�̺�ҵ����ʷί�в�ѯ 1202
	TDX_ID_FUNC_ANS_LOFPHYWLSWTCX,
	TDX_ID_FUNC_REQ_LOFPHYWDRCJCX,	// LOF�̺�ҵ���ճɽ���ѯ 1204
	TDX_ID_FUNC_ANS_LOFPHYWDRCJCX,
	TDX_ID_FUNC_REQ_LOFPHYWLSCJCX,	// LOF�̺�ҵ����ʷ�ɽ���ѯ 1206
	TDX_ID_FUNC_ANS_LOFPHYWLSCJCX,
	TDX_ID_FUNC_REQ_LOFPHYWCDCX,	// LOF�̺�ҵ�񳷵���ѯ 1208
	TDX_ID_FUNC_ANS_LOFPHYWCDCX,
	TDX_ID_FUNC_REQ_FSGFCX,			// �����ɷݲ�ѯ 1210
	TDX_ID_FUNC_ANS_FSGFCX,
	TDX_ID_FUNC_REQ_ZQFSXXCX,		// ֤ȯ������Ϣ��ѯ 1212
	TDX_ID_FUNC_ANS_ZQFSXXCX,
	TDX_ID_FUNC_REQ_BJZRCDCX,		// ����ת�ó�����ѯ 1214
	TDX_ID_FUNC_ANS_BJZRCDCX,
	TDX_ID_FUNC_REQ_BJZRWTCX,		// ����ת��ί�в�ѯ 1216
	TDX_ID_FUNC_ANS_BJZRWTCX,
	TDX_ID_FUNC_REQ_BJZRCJCX,		// ����ת�óɽ���ѯ 1218
	TDX_ID_FUNC_ANS_BJZRCJCX,
	TDX_ID_FUNC_REQ_DTGFCX,			// ��̬�ɷݲ�ѯ 1220
	TDX_ID_FUNC_ANS_DTGFCX,
	TDX_ID_FUNC_REQ_ZQZYKCX,		// ծȯ��Ѻ���ѯ 1222
	TDX_ID_FUNC_ANS_ZQZYKCX,
	TDX_ID_FUNC_REQ_DCGZJMXCX,		// �����ʽ���ϸ��ѯ 1224
	TDX_ID_FUNC_ANS_DCGZJMXCX,
	TDX_ID_FUNC_REQ_LSCCCX,			// ��ʷ�ֲֲ�ѯ 1226
	TDX_ID_FUNC_ANS_LSCCCX,
	TDX_ID_FUNC_REQ_GFMXCX,			// �ɷ���ϸ��ѯ 1228
	TDX_ID_FUNC_ANS_GFMXCX,
	TDX_ID_FUNC_REQ_GFCX_SECOND,	// �ɷݲ�ѯ(2nd��) 1230
	TDX_ID_FUNC_ANS_GFCX_SECOND,
	TDX_ID_FUNC_REQ_GFCX_THIRD,		// �ɷݲ�ѯ(3rd��) 1232
	TDX_ID_FUNC_ANS_GFCX_THIRD,
	TDX_ID_FUNC_REQ_ZQHGHYCX,		// ծȯ�ع���Լ��ѯ 1234
	TDX_ID_FUNC_ANS_ZQHGHYCX,
	TDX_ID_FUNC_REQ_KHDZXXCX,		// �ͻ�������Ϣ��ѯ 1236
	TDX_ID_FUNC_ANS_KHDZXXCX,
	TDX_ID_FUNC_REQ_ZHXYHQCX,		// �ۺ�Э�������ѯ 1238
	TDX_ID_FUNC_ANS_ZHXYHQCX,
	TDX_ID_FUNC_REQ_BZQHZCX,		// ��׼ȯ���ܲ�ѯ 1240
	TDX_ID_FUNC_ANS_BZQHZCX,
	TDX_ID_FUNC_REQ_GTZQHQCX,		// ��̨ծȯ�����ѯ 1242
	TDX_ID_FUNC_ANS_GTZQHQCX,
	TDX_ID_FUNC_REQ_RZXQHYCX,		// ������Ȩ��Լ��ѯ 1244
	TDX_ID_FUNC_ANS_RZXQHYCX,
	TDX_ID_FUNC_REQ_RZXQKHXXCX,		// ������Ȩ�ͻ���Ϣ��ѯ 1246
	TDX_ID_FUNC_ANS_RZXQKHXXCX,
	TDX_ID_FUNC_REQ_ZQHGLSCX,		// ծȯ�ع���ʷ��ѯ 1248
	TDX_ID_FUNC_ANS_ZQHGLSCX,
	TDX_ID_FUNC_REQ_QQDMCX,			// ��Ȩ�����ѯ 1250
	TDX_ID_FUNC_ANS_QQDMCX,
	TDX_ID_FUNC_REQ_QQCCCX,			// ��Ȩ�ֲֲ�ѯ 1252
	TDX_ID_FUNC_ANS_QQCCCX,
	TDX_ID_FUNC_REQ_QQSDSCX,		// ��Ȩ����˰��ѯ 1254
	TDX_ID_FUNC_ANS_QQSDSCX,
	TDX_ID_FUNC_REQ_QQDRWTCX,		// ��Ȩ����ί�в�ѯ 1256
	TDX_ID_FUNC_ANS_QQDRWTCX,
	TDX_ID_FUNC_REQ_QQLSWTCX,		// ��Ȩ��ʷί�в�ѯ 1258
	TDX_ID_FUNC_ANS_QQLSWTCX,

	// �ڻ�������
	TDX_ID_FUNC_REQ_QHWT,			// �ڻ�ί�� 1500
	TDX_ID_FUNC_ANS_QHWT,
	TDX_ID_FUNC_REQ_CXQHCC,			// ��ѯ�ڻ��ֲ� 1502
	TDX_ID_FUNC_ANS_CXQHCC,
	TDX_ID_FUNC_REQ_CXHYXX,			// ��ѯ�ڻ���Լ��Ϣ 1504
	TDX_ID_FUNC_ANS_CXHYXX,
	TDX_ID_FUNC_REQ_CXKJYHY,		// ��ѯ�ɽ��׺�Լ 1506
	TDX_ID_FUNC_ANS_CXKJYHY,
	TDX_ID_FUNC_REQ_DRZJLS,			// �����ʽ���ˮ 1508
	TDX_ID_FUNC_ANS_DRZJLS,
	TDX_ID_FUNC_REQ_QHWTZTCX,		// �ڻ�ί��״̬��ѯ 1510
	TDX_ID_FUNC_ANS_QHWTZTCX,
	TDX_ID_FUNC_REQ_QHWTHB,			// �ڻ�ί�лر� 1512 [���͹���,����ʹ��]
	TDX_ID_FUNC_ANS_QHWTHB,			// �ڻ�ί�лر� 1513
	TDX_ID_FUNC_REQ_QHCDHB,			// �ڻ������ر� 1514 [���͹���,����ʹ��]
	TDX_ID_FUNC_ANS_QHCDHB,			// �ڻ������ر� 1515
	TDX_ID_FUNC_REQ_QHCJHB,			// �ڻ��ɽ��ر� 1516 [���͹���,����ʹ��]
	TDX_ID_FUNC_ANS_QHCJHB,			// �ڻ��ɽ��ر� 1517
	TDX_ID_FUNC_REQ_QHXXFB,			// �ڻ���Ϣ���� 1518 [���͹���,����ʹ��]
	TDX_ID_FUNC_ANS_QHXXFB,			// �ڻ���Ϣ���� 1519
	TDX_ID_FUNC_REQ_QHJYSZTGB,		// �ڻ�������״̬�ı� 1520 [���͹���,����ʹ��]
	TDX_ID_FUNC_ANS_QHJYSZTGB,		// �ڻ�������״̬�ı� 1521
	TDX_ID_FUNC_REQ_QHZHHYBG,		// �ڻ���Ϻ�Լ��� 1522 [���͹���,����ʹ��]
	TDX_ID_FUNC_ANS_QHZHHYBG,		// �ڻ���Ϻ�Լ��� 1523
	TDX_ID_FUNC_REQ_QHZHWTHB,		// �ڻ����ί�лر� 1524 [���͹���,����ʹ��]
	TDX_ID_FUNC_ANS_QHZHWTHB,		// �ڻ����ί�лر� 1525
	TDX_ID_FUNC_REQ_QHZHCDHB,		// �ڻ���ϳ����ر� 1526 [���͹���,����ʹ��]
	TDX_ID_FUNC_ANS_QHZHCDHB,		// �ڻ���ϳ����ر� 1527
	TDX_ID_FUNC_REQ_QHDDLXCX,		// �ڻ��������Ͳ�ѯ 1528
	TDX_ID_FUNC_ANS_QHDDLXCX,
	TDX_ID_FUNC_REQ_QHZHWT,			// �ڻ����ί�� 1530
	TDX_ID_FUNC_ANS_QHZHWT,
	TDX_ID_FUNC_REQ_QHZHCD,			// �ڻ���ϳ��� 1532
	TDX_ID_FUNC_ANS_QHZHCD,
	TDX_ID_FUNC_REQ_QHZHHYCX,		// �ڻ���Ϻ�Լ��ѯ 1534
	TDX_ID_FUNC_ANS_QHZHHYCX,
	TDX_ID_FUNC_REQ_QHZHCCCX,		// �ڻ���ϳֲֲ�ѯ 1536
	TDX_ID_FUNC_ANS_QHZHCCCX,
	TDX_ID_FUNC_REQ_QHZHWTCX,		// �ڻ����ί�в�ѯ 1538
	TDX_ID_FUNC_ANS_QHZHWTCX,
	TDX_ID_FUNC_REQ_QHZHJSKWTS,		// �ڻ���ϼ����ί���� 1540
	TDX_ID_FUNC_ANS_QHZHJSKWTS,
	TDX_ID_FUNC_REQ_QHZHCLCX,		// �ڻ���ϲ��Բ�ѯ 1542
	TDX_ID_FUNC_ANS_QHZHCLCX,

	// �ع���
	TDX_ID_FUNC_REQ_GPZYHG,			// ��Ʊ��Ѻ�ع� 1800
	TDX_ID_FUNC_ANS_GPZYHG,
	TDX_ID_FUNC_REQ_GPZYHG_SQCX,	// ��Ʊ��Ѻ�ع������ѯ 1802
	TDX_ID_FUNC_ANS_GPZYHG_SQCX,
	TDX_ID_FUNC_REQ_GPZYHG_HTCX,	// ��Ʊ��Ѻ�ع���ͬ��ѯ 1804
	TDX_ID_FUNC_ANS_GPZYHG_HTCX,
	TDX_ID_FUNC_REQ_GPZYHG_QYCX,	// ��Ʊ��Ѻ�ع�Ȩ���ѯ 1806
	TDX_ID_FUNC_ANS_GPZYHG_QYCX,
	TDX_ID_FUNC_REQ_GPZYHG_QXLLCX,	// ��Ʊ��Ѻ�ع��������ʲ�ѯ 1808
	TDX_ID_FUNC_ANS_GPZYHG_QXLLCX,
	TDX_ID_FUNC_REQ_GPZYHG_LSCX,	// ��Ʊ��Ѻ�ع���ˮ��ѯ 1810
	TDX_ID_FUNC_ANS_GPZYHG_LSCX,
	TDX_ID_FUNC_REQ_GPZYHG_RCFCX,	// ��Ʊ��Ѻ�ع��ڳ�����ѯ 1812
	TDX_ID_FUNC_ANS_GPZYHG_RCFCX,
	TDX_ID_FUNC_REQ_GPZYHG_LXCX,	// ��Ʊ��Ѻ�ع���Ϣ��ѯ 1814
	TDX_ID_FUNC_ANS_GPZYHG_LXCX,
	TDX_ID_FUNC_REQ_GPZYHG_LSHTCX,	// ��Ʊ��Ѻ�ع���ʷ��ͬ��ѯ 1816
	TDX_ID_FUNC_ANS_GPZYHG_LSHTCX,
	TDX_ID_FUNC_REQ_GPZYHG_BDZQCX,	// ��Ʊ��Ѻ�ع����֤ȯ��ѯ 1818
	TDX_ID_FUNC_ANS_GPZYHG_BDZQCX,
	TDX_ID_FUNC_REQ_TSHG,			// ��ɫ�ع� 1830
	TDX_ID_FUNC_ANS_TSHG,
	TDX_ID_FUNC_REQ_TSHG_XXCX,		// ��ɫ�ع���Ϣ��ѯ 1832
	TDX_ID_FUNC_ANS_TSHG_XXCX,
	TDX_ID_FUNC_REQ_TSHG_SQCX,		// ��ɫ�ع������ѯ 1834
	TDX_ID_FUNC_ANS_TSHG_SQCX,
	TDX_ID_FUNC_REQ_TSHG_DMCX,		// ��ɫ�ع������ѯ 1836
	TDX_ID_FUNC_ANS_TSHG_DMCX,
	TDX_ID_FUNC_REQ_TSHG_YZT,		// ��ɫ�ع���֤ͨ 1838
	TDX_ID_FUNC_ANS_TSHG_YZT,
	TDX_ID_FUNC_REQ_TSHG_ZZJHCX,	// ��ɫ�ع�ת�˼ƻ���ѯ 1840
	TDX_ID_FUNC_ANS_TSHG_ZZJHCX,
	TDX_ID_FUNC_REQ_TSHG_LSCX,		// ��ɫ�ع���ˮ��ѯ 1842
	TDX_ID_FUNC_ANS_TSHG_LSCX,

	TDX_ID_FUNC_REQ_PSZTSZ,			// ����״̬����(��ѯ) 2000
	TDX_ID_FUNC_ANS_PSZTSZ,
	TDX_ID_FUNC_REQ_HZHG,			// �����ع� 2002
	TDX_ID_FUNC_ANS_HZHG,
	TDX_ID_FUNC_REQ_HZHGZT,			// �����ع�״̬(��ѯ) 2004
	TDX_ID_FUNC_ANS_HZHGZT,
	TDX_ID_FUNC_REQ_HZSGZT,			// �����깺״̬(��ѯ) 2006
	TDX_ID_FUNC_ANS_HZSGZT,
	TDX_ID_FUNC_REQ_HZHGCPDMCX,		// �����ع���Ʒ�����ѯ 2008
	TDX_ID_FUNC_ANS_HZHGCPDMCX,
	TDX_ID_FUNC_REQ_HZHGCPXXCX,		// �����ع���Ʒ��Ϣ��ѯ 2010
	TDX_ID_FUNC_ANS_HZHGCPXXCX,
	TDX_ID_FUNC_REQ_HZHGTQZZCX,		// �����ع���ǰ��ֹ��ѯ 2012
	TDX_ID_FUNC_ANS_HZHGTQZZCX,
	TDX_ID_FUNC_REQ_HZHGDRWTCX,		// �����ع�����ί�в�ѯ 2014
	TDX_ID_FUNC_ANS_HZHGDRWTCX,
	TDX_ID_FUNC_REQ_HZHGDRCJCX,		// �����ع����ճɽ���ѯ 2016
	TDX_ID_FUNC_ANS_HZHGDRCJCX,
	TDX_ID_FUNC_REQ_HZHGLSWTCX,		// �����ع���ʷί�в�ѯ 2018
	TDX_ID_FUNC_ANS_HZHGLSWTCX,
	TDX_ID_FUNC_REQ_HZHGLSCJCX,		// �����ع���ʷ�ɽ���ѯ 2020
	TDX_ID_FUNC_ANS_HZHGLSCJCX,
	TDX_ID_FUNC_REQ_HZHGQNHYCX,		// �����ع����ں�Լ��ѯ 2022
	TDX_ID_FUNC_ANS_HZHGQNHYCX,
	TDX_ID_FUNC_REQ_HZHGCDCX,		// �����ع�������ѯ 2024
	TDX_ID_FUNC_ANS_HZHGCDCX,
	TDX_ID_FUNC_REQ_HZHGXYCX,		// �����ع���Լ��ѯ 2026
	TDX_ID_FUNC_ANS_HZHGXYCX,
	TDX_ID_FUNC_REQ_HZHGXYZZCX,		// �����ع���Լ��ֹ��ѯ 2028
	TDX_ID_FUNC_ANS_HZHGXYZZCX,
	TDX_ID_FUNC_REQ_HZHGTQZZYYCX,	// �����ع���ǰ��ֹԤԼ��ѯ 2030
	TDX_ID_FUNC_ANS_HZHGTQZZYYCX,
	TDX_ID_FUNC_REQ_HZHGTQZZYYCXCX,	// �����ع���ǰ��ֹԤԼ������ѯ 2032
	TDX_ID_FUNC_ANS_HZHGTQZZYYCXCX,
	TDX_ID_FUNC_REQ_HZHGDYZYWCX,	// �����ع���Ӧ��Ѻ���ѯ 2034
	TDX_ID_FUNC_ANS_HZHGDYZYWCX,
	TDX_ID_FUNC_REQ_HZHGXYCDCX,		// �����ع���Լ������ѯ 2036
	TDX_ID_FUNC_ANS_HZHGXYCDCX,
	TDX_ID_FUNC_REQ_HZHGDRDQCX,		// �����ع����յ��ڲ�ѯ 2038
	TDX_ID_FUNC_ANS_HZHGDRDQCX,
	TDX_ID_FUNC_REQ_HZHGLSDQCX,		// �����ع���ʷ���ڲ�ѯ 2040
	TDX_ID_FUNC_ANS_HZHGLSDQCX,
	TDX_ID_FUNC_REQ_HZHGXZZZYYCX,	// �����ع�������ֹԤԼ��ѯ 2042
	TDX_ID_FUNC_ANS_HZHGXZZZYYCX,
	TDX_ID_FUNC_REQ_HZHGXZZZYYCXCX,	// �����ع�������ֹԤԼ������ѯ 2044
	TDX_ID_FUNC_ANS_HZHGXZZZYYCXCX,
	TDX_ID_FUNC_REQ_HZHGXYBGCX,		// �����ع���Լ�����ѯ 2046
	TDX_ID_FUNC_ANS_HZHGXYBGCX,
	TDX_ID_FUNC_REQ_HZHGHYSYCX,		// �����ع���Լ�����ѯ 2048
	TDX_ID_FUNC_ANS_HZHGHYSYCX,
	TDX_ID_FUNC_REQ_SZBJHGCPDMCX,	// ���ڱ��ۻع���Ʒ�����ѯ 2050
	TDX_ID_FUNC_ANS_SZBJHGCPDMCX,	
	TDX_ID_FUNC_REQ_SZBJHGQNHYCX,	// ���ڱ��ۻع����ں�Լ��ѯ 2052
	TDX_ID_FUNC_ANS_SZBJHGQNHYCX,
	TDX_ID_FUNC_REQ_HZHGXYSZPTCX,	// �����ع�Э���������ײ�ѯ 2054
	TDX_ID_FUNC_ANS_HZHGXYSZPTCX,


	TDX_ID_FUNC_REQ_YDHGCSJYPTCX,	// Լ���ع���ʼ�������ײ�ѯ 2070
	TDX_ID_FUNC_ANS_YDHGCSJYPTCX,
	TDX_ID_FUNC_REQ_YDHGLYBZPTCX,	// Լ���ع���Լ�������ײ�ѯ 2072
	TDX_ID_FUNC_ANS_YDHGLYBZPTCX,
	TDX_ID_FUNC_REQ_YDHGTQGHPTCX,	// Լ���ع���ǰ�������ײ�ѯ 2074
	TDX_ID_FUNC_ANS_YDHGTQGHPTCX,
	TDX_ID_FUNC_REQ_YDHGYQSQPTCX,	// Լ���ع������������ײ�ѯ 2076
	TDX_ID_FUNC_ANS_YDHGYQSQPTCX,
	TDX_ID_FUNC_REQ_YDHGJYCDPTCX,	// Լ���ع����׳������ײ�ѯ 2078
	TDX_ID_FUNC_ANS_YDHGJYCDPTCX,
	TDX_ID_FUNC_REQ_YDHGDQHYCX,		// Լ���ع���ǰ��Լ��ѯ 2080
	TDX_ID_FUNC_ANS_YDHGDQHYCX,
	TDX_ID_FUNC_REQ_YDHGLSHYCX,		// Լ���ع���ʷ��Լ��ѯ 2082
	TDX_ID_FUNC_ANS_YDHGLSHYCX,
	TDX_ID_FUNC_REQ_YDHGJXHYCX,		// Լ���ع����к�Լ��ѯ 2084
	TDX_ID_FUNC_ANS_YDHGJXHYCX,
	TDX_ID_FUNC_REQ_YDHGZZHYCX,		// Լ���ع���ֹ��Լ��ѯ 2086
	TDX_ID_FUNC_ANS_YDHGZZHYCX,
	TDX_ID_FUNC_REQ_YDHGBDZQCX,		// Լ���ع����֤ȯ��ѯ 2088
	TDX_ID_FUNC_ANS_YDHGBDZQCX,
	TDX_ID_FUNC_REQ_YDHGCPXXCX,		// Լ���ع���Ʒ��Ϣ��ѯ 2090
	TDX_ID_FUNC_ANS_YDHGCPXXCX,
	TDX_ID_FUNC_REQ_YDHGZHXXCX,		// Լ���ع��ۺ���Ϣ��ѯ 2092
	TDX_ID_FUNC_ANS_YDHGZHXXCX,
	TDX_ID_FUNC_REQ_YDHGYWCZ,		// Լ���ع�ҵ�����(��Ϣ��ѯ) 2098
	TDX_ID_FUNC_ANS_YDHGYWCZ,

	// ����ʽ������
	TDX_ID_FUNC_REQ_KFSJJWT,		// ����ʽ����ί�� 2100
	TDX_ID_FUNC_ANS_KFSJJWT,
	TDX_ID_FUNC_REQ_KFSJJWTCD,		// ����ί�г��� 2102
	TDX_ID_FUNC_ANS_KFSJJWTCD,
	TDX_ID_FUNC_REQ_KFSJJZH,		// ת�� 2104
	TDX_ID_FUNC_ANS_KFSJJZH,
	TDX_ID_FUNC_REQ_KFSJJFECX,		// �ݶ��ѯ 2106
	TDX_ID_FUNC_ANS_KFSJJFECX,
	TDX_ID_FUNC_REQ_KFSJJWTCX,		// ����ί�в�ѯ 2108
	TDX_ID_FUNC_ANS_KFSJJWTCX,
	TDX_ID_FUNC_REQ_KFSJJXXCX,		// ���������Ϣ��ѯ 2110
	TDX_ID_FUNC_ANS_KFSJJXXCX,
	TDX_ID_FUNC_REQ_KFSJJCJCX,		// �ɽ���ѯ 2112
	TDX_ID_FUNC_ANS_KFSJJCJCX,
	TDX_ID_FUNC_REQ_KFSJJFH,		// ����ֺ� 2114
	TDX_ID_FUNC_ANS_KFSJJFH,
	TDX_ID_FUNC_REQ_KFSJJDMCX,		// �������� 2116
	TDX_ID_FUNC_ANS_KFSJJDMCX,
	TDX_ID_FUNC_REQ_KFSJJZJZHKH,	// �����ʽ��ʺſ��� 2118
	TDX_ID_FUNC_ANS_KFSJJZJZHKH,
	TDX_ID_FUNC_REQ_KFSJJZJZHZC,	// �����ʽ��ʺ�ע�� 2120
	TDX_ID_FUNC_ANS_KFSJJZJZHZC,
	TDX_ID_FUNC_REQ_KFSJJKHZLXG,	// �ͻ������޸� 2122
	TDX_ID_FUNC_ANS_KFSJJKHZLXG,
	TDX_ID_FUNC_REQ_KFSJJCXGSDM,	// ��ѯ����˾���� 2124
	TDX_ID_FUNC_ANS_KFSJJCXGSDM,
	TDX_ID_FUNC_REQ_KFSJJZHCX,		// ��ѯ�����ʺ� 2126
	TDX_ID_FUNC_ANS_KFSJJZHCX,
	TDX_ID_FUNC_REQ_KFSJJLSWTCX,	// ������ʷί�в�ѯ 2128
	TDX_ID_FUNC_ANS_KFSJJLSWTCX,
	TDX_ID_FUNC_REQ_KFSJJDSDESGSZ,	// ��ʱ�����깺���� 2130
	TDX_ID_FUNC_ANS_KFSJJDSDESGSZ,
	TDX_ID_FUNC_REQ_KFSJJDSDESGQX,	// ��ʱ�����깺ȡ�� 2132
	TDX_ID_FUNC_ANS_KFSJJDSDESGQX,
	TDX_ID_FUNC_REQ_KFSJJCXDQDESGPZ,// ��ѯ���ڶ����깺Ʒ�� 2134
	TDX_ID_FUNC_ANS_KFSJJCXDQDESGPZ,
	TDX_ID_FUNC_REQ_KFSJJDRWTCX,	// ����ʽ������ί�в�ѯ 2136
	TDX_ID_FUNC_ANS_KFSJJDRWTCX,
	TDX_ID_FUNC_REQ_KFSJJFHCX,		// ����ֺ��ѯ 2138
	TDX_ID_FUNC_ANS_KFSJJFHCX,
	TDX_ID_FUNC_REQ_LOFJJFHCX,		// LOF����ֺ��ѯ 2140
	TDX_ID_FUNC_ANS_LOFJJFHCX,
	TDX_ID_FUNC_REQ_LOFJJFH,		// LOF����ֺ����� 2142
	TDX_ID_FUNC_ANS_LOFJJFH,
	TDX_ID_FUNC_REQ_KFSJJFXXXCX,	// ����ʽ������������Ϣ��ѯ 2144
	TDX_ID_FUNC_ANS_KFSJJFXXXCX,
	TDX_ID_FUNC_REQ_KFSJJZZKH,		// ����ת�ʿ��� 2146
	TDX_ID_FUNC_ANS_KFSJJZZKH,
	TDX_ID_FUNC_REQ_KFSJJJYKH,		// �����׿��� 2148
	TDX_ID_FUNC_ANS_KFSJJJYKH,
	TDX_ID_FUNC_REQ_KFSJJDRCJCX,	// �����ճɽ���ѯ 2150
	TDX_ID_FUNC_ANS_KFSJJDRCJCX,
	TDX_ID_FUNC_REQ_KFSJJLSCJCX,	// ������ʷ�ɽ���ѯ 2152
	TDX_ID_FUNC_ANS_KFSJJLSCJCX,
	TDX_ID_FUNC_REQ_KFSJJJZCX,		// ����ֵ��ѯ 2154
	TDX_ID_FUNC_ANS_KFSJJJZCX,
	TDX_ID_FUNC_REQ_KFSJJXYCXKT,	// ����Э���ѯ��ͨ 2156
	TDX_ID_FUNC_ANS_KFSJJXYCXKT,
	TDX_ID_FUNC_REQ_KFSJJFHMXCX,	// ����ֺ���ϸ��ѯ 2158
	TDX_ID_FUNC_ANS_KFSJJFHMXCX,
	TDX_ID_FUNC_REQ_DQDESZCX,		// ���ڶ������ò�ѯ 2160
	TDX_ID_FUNC_ANS_DQDESZCX,
	TDX_ID_FUNC_REQ_KFSJJFJYWTCX,	// ����ʽ����ǽ���ί�в�ѯ 2162
	TDX_ID_FUNC_ANS_KFSJJFJYWTCX,
	TDX_ID_FUNC_REQ_KFSJJFJYDRWTCX,	// ����ʽ����ǽ��׵���ί�в�ѯ 2164
	TDX_ID_FUNC_ANS_KFSJJFJYDRWTCX,
	TDX_ID_FUNC_REQ_KFSJJFXKCSDMCX,	// ����ʽ������տɳ��ܴ����ѯ 2166
	TDX_ID_FUNC_ANS_KFSJJFXKCSDMCX,
	TDX_ID_FUNC_REQ_KFSJJFLCX,		// ����ʽ������ʲ�ѯ 2168
	TDX_ID_FUNC_ANS_KFSJJFLCX,
	TDX_ID_FUNC_REQ_KFSJJDQDESHSZ,	// ����ʽ�����ڶ���������� 2170
	TDX_ID_FUNC_ANS_KFSJJDQDESHSZ,
	TDX_ID_FUNC_REQ_KFSJJDQDESHQX,	// ����ʽ�����ڶ������ȡ�� 2172
	TDX_ID_FUNC_ANS_KFSJJDQDESHQX,
	TDX_ID_FUNC_REQ_KFSJJDQDESHCX,	// ����ʽ�����ڶ�����ز�ѯ 2174
	TDX_ID_FUNC_ANS_KFSJJDQDESHCX,
	TDX_ID_FUNC_REQ_KFSJJDQDESHPZ,	// ����ʽ�����ڶ������Ʒ�� 2176
	TDX_ID_FUNC_ANS_KFSJJDQDESHPZ,
	TDX_ID_FUNC_REQ_KFSJJDMXGXXCX,	// ����ʽ������������Ϣ��ѯ 2178
	TDX_ID_FUNC_ANS_KFSJJDMXGXXCX,
	TDX_ID_FUNC_REQ_KFSJJGSXGXXCX,	// ����ʽ����˾�����Ϣ��ѯ 2180
	TDX_ID_FUNC_ANS_KFSJJGSXGXXCX,
	TDX_ID_FUNC_REQ_KFSJJDZDCX,		// ����ʽ������˵���ѯ 2182
	TDX_ID_FUNC_ANS_KFSJJDZDCX,
	TDX_ID_FUNC_REQ_KFSJJJGDCX,		// ����ʽ���𽻸��ѯ 2184
	TDX_ID_FUNC_ANS_KFSJJJGDCX,

	// ��Ʋ�Ʒ
	TDX_ID_FUNC_REQ_LCCPFECX,		// ��Ʋ�Ʒ�ݶ��ѯ 2200
	TDX_ID_FUNC_ANS_LCCPFECX,
	TDX_ID_FUNC_REQ_LCCPWTCX,		// ��Ʋ�Ʒί�в�ѯ 2202
	TDX_ID_FUNC_ANS_LCCPWTCX,
	TDX_ID_FUNC_REQ_LCCPCJCX,		// ��Ʋ�Ʒ�ɽ���ѯ 2204
	TDX_ID_FUNC_ANS_LCCPCJCX,
	TDX_ID_FUNC_REQ_LCCPDRWTCX,		// ��Ʋ�Ʒ����ί�в�ѯ 2206
	TDX_ID_FUNC_ANS_LCCPDRWTCX,
	TDX_ID_FUNC_REQ_LCCPDMCX,		// ��Ʋ�Ʒ�����ѯ 2208
	TDX_ID_FUNC_ANS_LCCPDMCX,
	TDX_ID_FUNC_REQ_LCCPZHCX,		// ��Ʋ�Ʒ�ʺŲ�ѯ 2210
	TDX_ID_FUNC_ANS_LCCPZHCX,
	TDX_ID_FUNC_REQ_LCCPDQDESGCX,	// ��Ʋ�Ʒ���ڶ����깺��ѯ 2212
	TDX_ID_FUNC_ANS_LCCPDQDESGCX,
	TDX_ID_FUNC_REQ_LCCPDQDESGPZ,	// ��Ʋ�Ʒ���ڶ����깺Ʒ�� 2214
	TDX_ID_FUNC_ANS_LCCPDQDESGPZ,
	TDX_ID_FUNC_REQ_LCCPZZJHLBCX,	// ��Ʋ�Ʒ��ֵ�ƻ��б��ѯ 2216
	TDX_ID_FUNC_ANS_LCCPZZJHLBCX,
	TDX_ID_FUNC_REQ_LCCPZZJHXXCX,	// ��Ʋ�Ʒ��ֵ�ƻ���Ϣ��ѯ 2218
	TDX_ID_FUNC_ANS_LCCPZZJHXXCX,
	TDX_ID_FUNC_REQ_LCCPZZJHJESZ,	// ��Ʋ�Ʒ��ֵ�ƻ�������� 2220
	TDX_ID_FUNC_ANS_LCCPZZJHJESZ,
	TDX_ID_FUNC_REQ_LCCPZZJHZTSZ,	// ��Ʋ�Ʒ��ֵ�ƻ�״̬���� 2222
	TDX_ID_FUNC_ANS_LCCPZZJHZTSZ,
	TDX_ID_FUNC_REQ_LCCPZZJHJCXY,	// ��Ʋ�Ʒ��ֵ�ƻ����Э�� 2224
	TDX_ID_FUNC_ANS_LCCPZZJHJCXY,
	TDX_ID_FUNC_REQ_LCCPZZJHFECX,	// ��Ʋ�Ʒ��ֵ�ƻ��ݶ��ѯ 2226
	TDX_ID_FUNC_ANS_LCCPZZJHFECX,
	TDX_ID_FUNC_REQ_LCCPZZJHCDCX,	// ��Ʋ�Ʒ��ֵ�ƻ�������ѯ 2228
	TDX_ID_FUNC_ANS_LCCPZZJHCDCX,
	TDX_ID_FUNC_REQ_LCCPZZJHXXXG,	// ��Ʋ�Ʒ��ֵ�ƻ���Ϣ�޸� 2230
	TDX_ID_FUNC_ANS_LCCPZZJHXXXG,
	TDX_ID_FUNC_REQ_LCCPZZJHFESH,	// ��Ʋ�Ʒ��ֵ�ƻ��ݶ���� 2232
	TDX_ID_FUNC_ANS_LCCPZZJHFESH,
	TDX_ID_FUNC_REQ_LCCPZZJHWTCD,	// ��Ʋ�Ʒ��ֵ�ƻ�ί�г��� 2234
	TDX_ID_FUNC_ANS_LCCPZZJHWTCD,
	TDX_ID_FUNC_REQ_LCCPZZJHYYQKCZ,	// ��Ʋ�Ʒ��ֵ�ƻ�ԤԼȡ����� 2236
	TDX_ID_FUNC_ANS_LCCPZZJHYYQKCZ,
	TDX_ID_FUNC_REQ_LCCPZZJHYYQKCX,	// ��Ʋ�Ʒ��ֵ�ƻ�ԤԼȡ���ѯ 2238
	TDX_ID_FUNC_ANS_LCCPZZJHYYQKCX,
	TDX_ID_FUNC_REQ_LCCPZZJHLSSYCX,	// ��Ʋ�Ʒ��ֵ�ƻ���ʷ�����ѯ 2240
	TDX_ID_FUNC_ANS_LCCPZZJHLSSYCX,
	TDX_ID_FUNC_REQ_DQLCCPSHXXCX,	// ������Ʋ�Ʒ�����Ϣ��ѯ 2242
	TDX_ID_FUNC_ANS_DQLCCPSHXXCX,
	TDX_ID_FUNC_REQ_LCCPZRDMCX,		// ��Ʋ�Ʒת�ô����ѯ 2244
	TDX_ID_FUNC_ANS_LCCPZRDMCX,
	TDX_ID_FUNC_REQ_LCCPZRHQCX,		// ��Ʋ�Ʒת�������ѯ 2246
	TDX_ID_FUNC_ANS_LCCPZRHQCX,
	TDX_ID_FUNC_REQ_LCCPZRCDCX,		// ��Ʋ�Ʒת�ó�����ѯ 2248
	TDX_ID_FUNC_ANS_LCCPZRCDCX,
	TDX_ID_FUNC_REQ_LCCPZRWTCX,		// ��Ʋ�Ʒת��ί�в�ѯ 2250
	TDX_ID_FUNC_ANS_LCCPZRWTCX,
	TDX_ID_FUNC_REQ_LCCPZRCJCX,		// ��Ʋ�Ʒת�óɽ���ѯ 2252
	TDX_ID_FUNC_ANS_LCCPZRCJCX,
	TDX_ID_FUNC_REQ_LCCPQYJYCX,		// ��Ʋ�ƷǩԼ��Լ��ѯ 2254
	TDX_ID_FUNC_ANS_LCCPQYJYCX,
	TDX_ID_FUNC_REQ_YHLCCPDMCX,		// ������Ʋ�Ʒ�����ѯ 2256
	TDX_ID_FUNC_ANS_YHLCCPDMCX,
	TDX_ID_FUNC_REQ_YHLCCPFECX,		// ������Ʋ�Ʒ�ݶ��ѯ 2258
	TDX_ID_FUNC_ANS_YHLCCPFECX,
	TDX_ID_FUNC_REQ_YHLCCPWTCX,		// ���в���Ʋ�Ʒί�в�ѯ 2260
	TDX_ID_FUNC_ANS_YHLCCPWTCX,
	TDX_ID_FUNC_REQ_YHLCCPZHCX,		// ������Ʋ�Ʒ�ʺŲ�ѯ 2262
	TDX_ID_FUNC_ANS_YHLCCPZHCX,
	TDX_ID_FUNC_REQ_YHLCCPCJCX,		// ������Ʋ�Ʒ�ɽ���ѯ 2264
	TDX_ID_FUNC_ANS_YHLCCPCJCX,
	TDX_ID_FUNC_REQ_OTCFECX,		// OTC�ݶ��ѯ 2266
	TDX_ID_FUNC_ANS_OTCFECX,
	TDX_ID_FUNC_REQ_OTCRSSCX,		// OTC�������ѯ 2268
	TDX_ID_FUNC_ANS_OTCRSSCX,
	TDX_ID_FUNC_REQ_OTCYXSBCX,		// OTC�����걨��ѯ 2270
	TDX_ID_FUNC_ANS_OTCYXSBCX,
	TDX_ID_FUNC_REQ_OTCCJSBCX,		// OTC�ɽ��걨��ѯ 2272
	TDX_ID_FUNC_ANS_OTCCJSBCX,
	TDX_ID_FUNC_REQ_OTCCPHYCX,		// OTC��Ʒ��Լ��ѯ 2274
	TDX_ID_FUNC_ANS_OTCCPHYCX,
	TDX_ID_FUNC_REQ_OTCBJXXCX,		// OTC������Ϣ��ѯ 2276
	TDX_ID_FUNC_ANS_OTCBJXXCX,
	TDX_ID_FUNC_REQ_OTCHQXXCX,		// OTC������Ϣ��ѯ 2278
	TDX_ID_FUNC_ANS_OTCHQXXCX,
	TDX_ID_FUNC_REQ_OTCDZHTLBCX,	// OTC���Ӻ�ͬ�б��ѯ 2280
	TDX_ID_FUNC_ANS_OTCDZHTLBCX,
	TDX_ID_FUNC_REQ_OTCDZHTCX,		// OTC���Ӻ�ͬ��ѯ 2282
	TDX_ID_FUNC_ANS_OTCDZHTCX,
	TDX_ID_FUNC_REQ_XTCPDMCX,		// ���в�Ʒ�����ѯ 2300
	TDX_ID_FUNC_ANS_XTCPDMCX,
	TDX_ID_FUNC_REQ_XTCPFECX,		// ���в�Ʒ�ݶ��ѯ 2302
	TDX_ID_FUNC_ANS_XTCPFECX,
	TDX_ID_FUNC_REQ_XTCPZHCX,		// ���в�Ʒ�ʺŲ�ѯ 2304
	TDX_ID_FUNC_ANS_XTCPZHCX,
	TDX_ID_FUNC_REQ_XTCPWTCX,		// ���в�Ʒί�в�ѯ 2306
	TDX_ID_FUNC_ANS_XTCPWTCX,
	TDX_ID_FUNC_REQ_XTCPCJCX,		// ���в�Ʒ�ɽ���ѯ 2308
	TDX_ID_FUNC_ANS_XTCPCJCX,
	TDX_ID_FUNC_REQ_XTCPLSWTCX,		// ���в�Ʒ��ʷί�в�ѯ 2310
	TDX_ID_FUNC_ANS_XTCPLSWTCX,
		
	// ����ֱ��
	TDX_ID_FUNC_REQ_JJZXRG,			// ����ֱ���Ϲ� 2500
	TDX_ID_FUNC_ANS_JJZXRG,
	TDX_ID_FUNC_REQ_JJZXSG,			// ����ֱ���깺 2502
	TDX_ID_FUNC_ANS_JJZXSG,
	TDX_ID_FUNC_REQ_JJZXSH,			// ����ֱ����� 2504
	TDX_ID_FUNC_ANS_JJZXSH,
	TDX_ID_FUNC_REQ_JJZXFH,			// ����ֱ���ֺ� 2506
	TDX_ID_FUNC_ANS_JJZXFH,
	TDX_ID_FUNC_REQ_JJZXZH,			// ����ֱ��ת�� 2508
	TDX_ID_FUNC_ANS_JJZXZH,
	TDX_ID_FUNC_REQ_JJZXZTG,		// ����ֱ��ת�й� 2510
	TDX_ID_FUNC_ANS_JJZXZTG,
	TDX_ID_FUNC_REQ_JJZXCD,			// ����ֱ������ 2512
	TDX_ID_FUNC_ANS_JJZXCD,
	TDX_ID_FUNC_REQ_JJZXFLCX,		// ����ֱ�����ʲ�ѯ 2514
	TDX_ID_FUNC_ANS_JJZXFLCX,
	TDX_ID_FUNC_REQ_JJZXYHZF,		// ����ֱ������֧�� 2516
	TDX_ID_FUNC_ANS_JJZXYHZF,
	TDX_ID_FUNC_REQ_JJZXXSRDMCX,	// ����ֱ�������˴����ѯ 2518
	TDX_ID_FUNC_ANS_JJZXXSRDMCX,
	TDX_ID_FUNC_REQ_JJZXXXJC,		// ����ֱ����Ϣ��� 2520
	TDX_ID_FUNC_ANS_JJZXXXJC,

	// ���������ڻ���
	TDX_ID_FUNC_REQ_JYSCNJJDMCX,	// ���������ڻ�������ѯ 2850
	TDX_ID_FUNC_ANS_JYSCNJJDMCX,
	TDX_ID_FUNC_REQ_JYSCNJJCFGCX,	// ���������ڻ���ɷֹɲ�ѯ 2852
	TDX_ID_FUNC_ANS_JYSCNJJCFGCX,

	// ETF
	TDX_ID_FUNC_REQ_ETFSHKJSGPTCX,	// ETF�Ϻ��羳�깺���ײ�ѯ 2950
	TDX_ID_FUNC_ANS_ETFSHKJSGPTCX,
	TDX_ID_FUNC_REQ_ETFSZKJSGPTCX,	// ETF���ڿ羳�깺���ײ�ѯ 2952
	TDX_ID_FUNC_ANS_ETFSZKJSGPTCX,
	TDX_ID_FUNC_REQ_ETFSHKJSHPTCX,	// ETF�Ϻ��羳������ײ�ѯ 2954
	TDX_ID_FUNC_ANS_ETFSHKJSHPTCX,
	TDX_ID_FUNC_REQ_ETFSZKJSHPTCX,	// ETF���ڿ羳������ײ�ѯ 2956
	TDX_ID_FUNC_ANS_ETFSZKJSHPTCX,
	TDX_ID_FUNC_REQ_ETFSHKJWTCDCX,	// ETF�Ϻ��羳ί�г�����ѯ 2958
	TDX_ID_FUNC_ANS_ETFSHKJWTCDCX,
	TDX_ID_FUNC_REQ_ETFSZKJWTCDCX,	// ETF���ڿ羳ί�г�����ѯ 2960
	TDX_ID_FUNC_ANS_ETFSZKJWTCDCX,
	TDX_ID_FUNC_REQ_ETFSHKJDRWTCX,	// ETF�Ϻ��羳����ί�в�ѯ 2962
	TDX_ID_FUNC_ANS_ETFSHKJDRWTCX,
	TDX_ID_FUNC_REQ_ETFSZKJDRWTCX,	// ETF���ڿ羳����ί�в�ѯ 2964
	TDX_ID_FUNC_ANS_ETFSZKJDRWTCX,
	TDX_ID_FUNC_REQ_ETFSHKJDRCJCX,	// ETF�Ϻ��羳���ճɽ���ѯ 2966
	TDX_ID_FUNC_ANS_ETFSHKJDRCJCX,
	TDX_ID_FUNC_REQ_ETFSZKJDRCJCX,	// ETF���ڿ羳���ճɽ���ѯ 2968
	TDX_ID_FUNC_ANS_ETFSZKJDRCJCX,
	TDX_ID_FUNC_REQ_ETFSHKJLSWTCX,	// ETF�Ϻ��羳��ʷί�в�ѯ 2970
	TDX_ID_FUNC_ANS_ETFSHKJLSWTCX,
	TDX_ID_FUNC_REQ_ETFSZKJLSWTCX,	// ETF���ڿ羳��ʷί�в�ѯ 2972
	TDX_ID_FUNC_ANS_ETFSZKJLSWTCX,
	TDX_ID_FUNC_REQ_ETFSHKJLSCJCX,	// ETF�Ϻ��羳��ʷ�ɽ���ѯ 2974
	TDX_ID_FUNC_ANS_ETFSHKJLSCJCX,
	TDX_ID_FUNC_REQ_ETFSZKJLSCJCX,	// ETF���ڿ羳��ʷ�ɽ���ѯ 2976
	TDX_ID_FUNC_ANS_ETFSZKJLSCJCX,
	TDX_ID_FUNC_REQ_ETFWXXJRGPTCX,	// ETF�����ֽ��Ϲ����ײ�ѯ 2980
	TDX_ID_FUNC_ANS_ETFWXXJRGPTCX,
	TDX_ID_FUNC_REQ_ETFWXGFRGPTCX,	// ETF���¹ɷ��Ϲ����ײ�ѯ 2982
	TDX_ID_FUNC_ANS_ETFWXGFRGPTCX,
	TDX_ID_FUNC_REQ_ETFWXXJRGCDCX,	// ETF�����ֽ��Ϲ�������ѯ 2984
	TDX_ID_FUNC_ANS_ETFWXXJRGCDCX,
	TDX_ID_FUNC_REQ_ETFWXGFRGCDCX,	// ETF���¹ɷ��Ϲ�������ѯ 2986
	TDX_ID_FUNC_ANS_ETFWXGFRGCDCX,
	TDX_ID_FUNC_REQ_ETFWXXJRGXXCX,	// ETF�����ֽ��Ϲ���Ϣ��ѯ 2988
	TDX_ID_FUNC_ANS_ETFWXXJRGXXCX,
	TDX_ID_FUNC_REQ_ETFWXGFRGXXCX,	// ETF���¹ɷ��Ϲ���Ϣ��ѯ 2990
	TDX_ID_FUNC_ANS_ETFWXGFRGXXCX,
	TDX_ID_FUNC_REQ_ETFWXXJRGLSCX,	// ETF�����ֽ��Ϲ���ˮ��ѯ 2992
	TDX_ID_FUNC_ANS_ETFWXXJRGLSCX,
	TDX_ID_FUNC_REQ_ETFWXGFRGLSCX,	// ETF���¹ɷ��Ϲ���ˮ��ѯ 2994
	TDX_ID_FUNC_ANS_ETFWXGFRGLSCX,
	TDX_ID_FUNC_REQ_ETFMM,			// ETF���� 3000
	TDX_ID_FUNC_ANS_ETFMM,
	TDX_ID_FUNC_REQ_ETFXXCX,		// ETF��Ϣ��ѯ 3002
	TDX_ID_FUNC_ANS_ETFXXCX,
	TDX_ID_FUNC_REQ_ETFRGCX,		// ETF�Ϲ���ѯ 3004
	TDX_ID_FUNC_ANS_ETFRGCX,
	TDX_ID_FUNC_REQ_ETFRGCD,		// ETF�Ϲ����� 3006
	TDX_ID_FUNC_ANS_ETFRGCD,
	TDX_ID_FUNC_REQ_ETFPCH,			// ETFȡ���κ� 3008
	TDX_ID_FUNC_ANS_ETFPCH,
	TDX_ID_FUNC_REQ_ETFGPLMM,		// ETF��Ʊ������ 3010
	TDX_ID_FUNC_ANS_ETFGPLMM,
	TDX_ID_FUNC_REQ_ETFGPLCX,		// ETF��Ʊ����ѯ 3012
	TDX_ID_FUNC_ANS_ETFGPLCX,
	TDX_ID_FUNC_REQ_ETFYGCX,		// ETF��֤50ӵ�ɲ�ѯ 3014
	TDX_ID_FUNC_ANS_ETFYGCX,
	TDX_ID_FUNC_REQ_ETFWTCX,		// ETFί�в�ѯ 3016
	TDX_ID_FUNC_ANS_ETFWTCX,
	TDX_ID_FUNC_REQ_ETFCJCX,		// ETF�ɽ���ѯ 3018
	TDX_ID_FUNC_ANS_ETFCJCX,
	TDX_ID_FUNC_REQ_ETFCLCX,		// ETF���Բ�ѯ 3020
	TDX_ID_FUNC_ANS_ETFCLCX,
	TDX_ID_FUNC_REQ_ETFZSDMCX,		// ETFָ�������ѯ 3022
	TDX_ID_FUNC_ANS_ETFZSDMCX,
	TDX_ID_FUNC_REQ_ETFQR,			// ETF(ί��)ȷ�� 3024
	TDX_ID_FUNC_ANS_ETFQR,
	TDX_ID_FUNC_REQ_ETFWTCXMX,		// ETFί�в�ѯ��ϸ 3026
	TDX_ID_FUNC_ANS_ETFWTCXMX,
	TDX_ID_FUNC_REQ_ETFRGCDCX,		// ETF�Ϲ�������ѯ 3028
	TDX_ID_FUNC_ANS_ETFRGCDCX,
	TDX_ID_FUNC_REQ_ETFZSCFCX,		// ETFָ���ɷֲ�ѯ 3030
	TDX_ID_FUNC_ANS_ETFZSCFCX,
	TDX_ID_FUNC_REQ_ETFGFCX,		// ETF�ɷݲ�ѯ 3032
	TDX_ID_FUNC_ANS_ETFGFCX,
	TDX_ID_FUNC_REQ_ETFKSGCFGCX,	// ETF���깺�ɷֹɲ�ѯ 3034
	TDX_ID_FUNC_ANS_ETFKSGCFGCX,
	TDX_ID_FUNC_REQ_ETFGPLCD,		// ETF��Ʊ������ 3036
	TDX_ID_FUNC_ANS_ETFGPLCD,
	TDX_ID_FUNC_REQ_ETFGPLCDCX,		// ETF��Ʊ��������ѯ 3038
	TDX_ID_FUNC_ANS_ETFGPLCDCX,
	TDX_ID_FUNC_REQ_ETFKSCDPCX,		// ETF���г����̲�ѯ
	TDX_ID_FUNC_ANS_ETFKSCDPCX,

	// ���ͨҵ��
	TDX_ID_FUNC_REQ_ZHTPCH,			// ���ͨ���κ� 3050
	TDX_ID_FUNC_ANS_ZHTPCH,
	TDX_ID_FUNC_REQ_ZHTGPLMM,		// ���ͨ��Ʊ������ 3052
	TDX_ID_FUNC_ANS_ZHTGPLMM,
	TDX_ID_FUNC_REQ_ZHTGPLCX,		// ���ͨ��Ʊ����ѯ 3054
	TDX_ID_FUNC_ANS_ZHTGPLCX,
	TDX_ID_FUNC_REQ_ZHTYGCX,		// ���ͨӵ�ɲ�ѯ 3056
	TDX_ID_FUNC_ANS_ZHTYGCX,
	TDX_ID_FUNC_REQ_ZHTWTCX,		// ���ͨί�в�ѯ 3058
	TDX_ID_FUNC_ANS_ZHTWTCX,
	TDX_ID_FUNC_REQ_ZHTCJCX,		// ���ͨ�ɽ���ѯ 3060
	TDX_ID_FUNC_ANS_ZHTCJCX,
	TDX_ID_FUNC_REQ_ZHTCLCX,		// ���ͨ���Բ�ѯ 3062
	TDX_ID_FUNC_ANS_ZHTCLCX,
	TDX_ID_FUNC_REQ_ZHTZSDMCX,		// ���ָͨ�������ѯ 3064
	TDX_ID_FUNC_ANS_ZHTZSDMCX,
	TDX_ID_FUNC_REQ_ZHTQR,			// ���ͨȷ�� 3066
	TDX_ID_FUNC_ANS_ZHTQR,
	TDX_ID_FUNC_REQ_ZHTLSCX,		// ���ͨ��ʷ��ѯ 3068
	TDX_ID_FUNC_ANS_ZHTLSCX,
	TDX_ID_FUNC_REQ_ZHTLSCXMX,		// ���ͨ��ʷ��ѯ��ϸ 3070
	TDX_ID_FUNC_ANS_ZHTLSCXMX,
	TDX_ID_FUNC_REQ_ZHTWTCXMX,		// ���ͨί�в�ѯ��ϸ 3072
	TDX_ID_FUNC_ANS_ZHTWTCXMX,
	TDX_ID_FUNC_REQ_ZHTCJCXMX,		// ���ͨ�ɽ���ѯ��ϸ 3074
	TDX_ID_FUNC_ANS_ZHTCJCXMX,
	TDX_ID_FUNC_REQ_ZHTZSCFCX,		// ���ָͨ���ɷֲ�ѯ 3076
	TDX_ID_FUNC_ANS_ZHTZSCFCX,

	// ��������
	TDX_ID_FUNC_REQ_TL_HQHHH,		// (����)��ȡ�Ự�� 3100
	TDX_ID_FUNC_ANS_TL_HQHHH,
	TDX_ID_FUNC_REQ_TL_ZHDMCX,		// (����)��ϴ����ѯ 3102
	TDX_ID_FUNC_ANS_TL_ZHDMCX,
	TDX_ID_FUNC_REQ_TL_ZHCFCX,		// (����)��ϳɷֲ�ѯ 3104
	TDX_ID_FUNC_ANS_TL_ZHCFCX,
	TDX_ID_FUNC_REQ_TL_ZHDMCZ,		// (����)��ϴ������ 3106
	TDX_ID_FUNC_ANS_TL_ZHDMCZ,
	TDX_ID_FUNC_REQ_TL_ZHCFCZ,		// (����)��ϳɷֲ��� 3108
	TDX_ID_FUNC_ANS_TL_ZHCFCZ,
	TDX_ID_FUNC_REQ_TL_CLDMCX,		// (����)���Դ����ѯ 3110
	TDX_ID_FUNC_ANS_TL_CLDMCX,
	TDX_ID_FUNC_REQ_TL_CLCFCX,		// (����)���Գɷֲ�ѯ 3112
	TDX_ID_FUNC_ANS_TL_CLCFCX,
	TDX_ID_FUNC_REQ_TL_CLDMCZ,		// (����)���Դ������ 3114
	TDX_ID_FUNC_ANS_TL_CLDMCZ,
	TDX_ID_FUNC_REQ_TL_CLCFCZ,		// (����)���Գɷֲ��� 3116
	TDX_ID_FUNC_ANS_TL_CLCFCZ,
	TDX_ID_FUNC_REQ_TL_PHCZ,		// (����)���Ų��� 3118
	TDX_ID_FUNC_ANS_TL_PHCZ,
	TDX_ID_FUNC_REQ_TL_PHCX,		// (����)���Ų�ѯ 3120
	TDX_ID_FUNC_ANS_TL_PHCX,
	TDX_ID_FUNC_REQ_TL_PHWTLB,		// (����)����ί���б� 3122
	TDX_ID_FUNC_ANS_TL_PHWTLB,
	TDX_ID_FUNC_REQ_TL_PHWTZX,		// (����)����ί��ִ�� 3124
	TDX_ID_FUNC_ANS_TL_PHWTZX,
	TDX_ID_FUNC_REQ_TL_PHWTCX,		// (����)����ί�в�ѯ 3126
	TDX_ID_FUNC_ANS_TL_PHWTCX,
	TDX_ID_FUNC_REQ_TL_PHCCCX,		// (����)���ųֲֲ�ѯ 3128
	TDX_ID_FUNC_ANS_TL_PHCCCX,

	// �㷨����
	TDX_ID_FUNC_REQ_SFJY_DDCZ,		// (�㷨����)�������� 3190
	TDX_ID_FUNC_ANS_SFJY_DDCZ,
	TDX_ID_FUNC_REQ_SFJY_DDLBCX,	// (�㷨����)�����б��ѯ 3192
	TDX_ID_FUNC_ANS_SFJY_DDLBCX,
	TDX_ID_FUNC_REQ_SFJY_DDJGCX,	// (�㷨����)���������ѯ 3194
	TDX_ID_FUNC_ANS_SFJY_DDJGCX,

	//���ý���
	TDX_ID_FUNC_REQ_XYZCCX,			// �����ʲ���ѯ 3200
	TDX_ID_FUNC_ANS_XYZCCX,
	TDX_ID_FUNC_REQ_XYGFCX,			// ���ùɷݲ�ѯ 3202
	TDX_ID_FUNC_ANS_XYGFCX,
	TDX_ID_FUNC_REQ_XYHYCX,			// Ĭ��δƽ�ֺ�Լ��ѯ��ѯ 3204
	TDX_ID_FUNC_ANS_XYHYCX,
	TDX_ID_FUNC_REQ_XYHYYPCCX,		// ��ƽ�ֺ�Լ��ѯ 3206
	TDX_ID_FUNC_ANS_XYHYYPCCX,
	TDX_ID_FUNC_REQ_XYSXCX,			// �������޲�ѯ 3208
	TDX_ID_FUNC_ANS_XYSXCX,
	TDX_ID_FUNC_REQ_XYFZCX,			// ���ø�ծ��ѯ 3210
	TDX_ID_FUNC_ANS_XYFZCX,
	TDX_ID_FUNC_REQ_FXYZCCX,		// �������ʲ���ѯ 3212
	TDX_ID_FUNC_ANS_FXYZCCX,
	TDX_ID_FUNC_REQ_XYHYDRCX,		// ���ú�Լ���ղ�ѯ 3214
	TDX_ID_FUNC_ANS_XYHYDRCX,
	TDX_ID_FUNC_REQ_XYJYBDZQCX,		// ���ý��ױ��֤ȯ��ѯ 3216
	TDX_ID_FUNC_ANS_XYJYBDZQCX,
	TDX_ID_FUNC_REQ_XYJYZHXXCX,		// ���ý����ۺ���Ϣ��ѯ 3218
	TDX_ID_FUNC_ANS_XYJYZHXXCX,
	TDX_ID_FUNC_REQ_XYJYDBPZQCX,	// ���ý��׵���Ʒ֤ȯ��ѯ 3220
	TDX_ID_FUNC_ANS_XYJYDBPZQCX,
	TDX_ID_FUNC_REQ_XYJYRZMRZQCX,	// ���ý�����������֤ȯ��ѯ 3222
	TDX_ID_FUNC_ANS_XYJYRZMRZQCX,
	TDX_ID_FUNC_REQ_XYJYRQMCZQCX,	// ���ý�����ȯ����֤ȯ��ѯ 3224
	TDX_ID_FUNC_ANS_XYJYRQMCZQCX,
	TDX_ID_FUNC_REQ_XYJYDMTSXXCX,	// ���ý��״�����ʾ��Ϣ��ѯ 3226
	TDX_ID_FUNC_ANS_XYJYDMTSXXCX,
	TDX_ID_FUNC_REQ_XYJYHYHZCX,		// ���ý��׺�Լ���ܲ�ѯ 3228
	TDX_ID_FUNC_ANS_XYJYHYHZCX,
	TDX_ID_FUNC_REQ_XYJYRZMRPTCX,	// ���ý��������������ײ�ѯ 3230
	TDX_ID_FUNC_ANS_XYJYRZMRPTCX,
	TDX_ID_FUNC_REQ_XYJYRQMCPTCX,	// ���ý�����ȯ�������ײ�ѯ 3232
	TDX_ID_FUNC_ANS_XYJYRQMCPTCX,
	TDX_ID_FUNC_REQ_XYJYMQHQPTCX,	// ���ý�����ȯ��ȯ���ײ�ѯ 3234
	TDX_ID_FUNC_ANS_XYJYMQHQPTCX,
	TDX_ID_FUNC_REQ_XYJYYQHZPTCX,	// ���ý�����ȯ��ת���ײ�ѯ 3236
	TDX_ID_FUNC_ANS_XYJYYQHZPTCX,
	TDX_ID_FUNC_REQ_XYJYXQHQPTCX,	// ���ý�����ȯ��ȯ���ײ�ѯ 3238
	TDX_ID_FUNC_ANS_XYJYXQHQPTCX,
	TDX_ID_FUNC_REQ_XYJYDBPHZPTCX,	// ���ý��׵���Ʒ��ת���ײ�ѯ 3240
	TDX_ID_FUNC_ANS_XYJYDBPHZPTCX,
	TDX_ID_FUNC_REQ_XYJYDBPHRPTCX,	// ���ý��׵���Ʒ�������ײ�ѯ 3242
	TDX_ID_FUNC_ANS_XYJYDBPHRPTCX,
	TDX_ID_FUNC_REQ_XYJYDBPHCPTCX,	// ���ý��׵���Ʒ�������ײ�ѯ 3244
	TDX_ID_FUNC_ANS_XYJYDBPHCPTCX,
	TDX_ID_FUNC_REQ_XYJYXJHKPTCX,	// ���ý����ֽ𻹿����ײ�ѯ 3246
	TDX_ID_FUNC_ANS_XYJYXJHKPTCX,
	TDX_ID_FUNC_REQ_XYJYMQHKPTCX,	// ���ý�����ȯ�������ײ�ѯ 3248
	TDX_ID_FUNC_ANS_XYJYMQHKPTCX,
	TDX_ID_FUNC_REQ_XYJYRZPCMCPTCX,	// ���ý�������ƽ���������ײ�ѯ 3250
	TDX_ID_FUNC_ANS_XYJYRZPCMCPTCX,
	TDX_ID_FUNC_REQ_XYJYRQPCMRPTCX,	// ���ý�����ȯƽ���������ײ�ѯ 3252
	TDX_ID_FUNC_ANS_XYJYRQPCMRPTCX,
	TDX_ID_FUNC_REQ_XYJYLLXXCX,		// ���ý���������Ϣ��ѯ 3254
	TDX_ID_FUNC_ANS_XYJYLLXXCX,
	TDX_ID_FUNC_REQ_XYJYRQYECX,		// ���ý�����ȯ����ѯ 3256
	TDX_ID_FUNC_ANS_XYJYRQYECX,
	TDX_ID_FUNC_REQ_XYJYRZYECX,		// ���ý�����������ѯ 3258
	TDX_ID_FUNC_ANS_XYJYRZYECX,
	TDX_ID_FUNC_REQ_XYJYFJYHZCX,	// ���ý��׷ǽ��׻�ת��ѯ 3260
	TDX_ID_FUNC_ANS_XYJYFJYHZCX,
	TDX_ID_FUNC_REQ_XYJYLXFYCX,		// ���ý�����Ϣ���ò�ѯ 3262
	TDX_ID_FUNC_ANS_XYJYLXFYCX,
	TDX_ID_FUNC_REQ_XYJYZJFZCX,		// ���ý����ʽ�ծ��ѯ 3264
	TDX_ID_FUNC_ANS_XYJYZJFZCX,
	TDX_ID_FUNC_REQ_XYJYZQFZCX,		// ���ý���֤ȯ��ծ��ѯ 3266
	TDX_ID_FUNC_ANS_XYJYZQFZCX,
	TDX_ID_FUNC_REQ_XYJYKHQYCX,		// ���ý��׿ͻ�ǩԼ��ѯ 3268
	TDX_ID_FUNC_ANS_XYJYKHQYCX,
	TDX_ID_FUNC_REQ_XYJYKHXYCL,		// ���ý��׿ͻ�Э�鴦�� 3270
	TDX_ID_FUNC_ANS_XYJYKHXYCL,
	TDX_ID_FUNC_REQ_XYJYCHMXCX,		// ���ý��׳�����ϸ��ѯ 3272
	TDX_ID_FUNC_ANS_XYJYCHMXCX,
	TDX_ID_FUNC_REQ_XYJYRZHYCX,		// ���ý������ʺ�Լ��ѯ 3274
	TDX_ID_FUNC_ANS_XYJYRZHYCX,
	TDX_ID_FUNC_REQ_XYJYRQHYCX,		// ���ý�����ȯ��Լ��ѯ 3276
	TDX_ID_FUNC_ANS_XYJYRQHYCX,
	TDX_ID_FUNC_REQ_XYJYDBPHZCX,	// ���ý��׵���Ʒ��ת��ѯ 3278
	TDX_ID_FUNC_ANS_XYJYDBPHZCX,
	TDX_ID_FUNC_REQ_XYJYMRDBPPTCX,	// ���ý������뵣��Ʒ���ײ�ѯ 3280
	TDX_ID_FUNC_ANS_XYJYMRDBPPTCX,
	TDX_ID_FUNC_REQ_XYJYMCDBPPTCX,	// ���ý�����������Ʒ���ײ�ѯ 3282
	TDX_ID_FUNC_ANS_XYJYMCDBPPTCX,
	TDX_ID_FUNC_REQ_XYJYGHRQFYPTCX,	// ���ý��׹黹��ȯ�������ײ�ѯ 3284
	TDX_ID_FUNC_ANS_XYJYGHRQFYPTCX,
	TDX_ID_FUNC_REQ_XYJYFZLSCX,		// ���ý��׸�ծ��ˮ��ѯ 3286
	TDX_ID_FUNC_ANS_XYJYFZLSCX,
	TDX_ID_FUNC_REQ_XYJYXJTDHQPTCX, // ���ý����ֽ������ȯ���ײ�ѯ 3288
	TDX_ID_FUNC_ANS_XYJYXJTDHQPTCX,
	TDX_ID_FUNC_REQ_XYJYWCDBBLCX,	// ���ý���ά�ֵ������ʲ�ѯ 3290
	TDX_ID_FUNC_ANS_XYJYWCDBBLCX,
	TDX_ID_FUNC_REQ_XYJYEDGL,		// ���ý��׶�ȹ��� 3292
	TDX_ID_FUNC_ANS_XYJYEDGL,
	TDX_ID_FUNC_REQ_XYJYEDBGCX,		// ���ý��׶�ȱ����ѯ 3294
	TDX_ID_FUNC_ANS_XYJYEDBGCX,
	TDX_ID_FUNC_REQ_XYJYPCRZHYCX,	// ���ý���ƽ�����ʺ�Լ��ѯ 3296
	TDX_ID_FUNC_ANS_XYJYPCRZHYCX,
	TDX_ID_FUNC_REQ_XYJYPCRQHYCX,	// ���ý���ƽ����ȯ��Լ��ѯ 3298
	TDX_ID_FUNC_ANS_XYJYPCRQHYCX,

	// ת��ͨ
	TDX_ID_FUNC_REQ_ZRTYWCZ,		// ת��ͨҵ����� 3400
	TDX_ID_FUNC_ANS_ZRTYWCZ,
	TDX_ID_FUNC_REQ_ZRTBDZQCX,		// ת��ͨ���֤ȯ��ѯ 3402
	TDX_ID_FUNC_ANS_ZRTBDZQCX,
	TDX_ID_FUNC_REQ_ZRTZJXXCX,		// ת��ͨ�ʽ���Ϣ��ѯ 3404
	TDX_ID_FUNC_ANS_ZRTZJXXCX,
	TDX_ID_FUNC_REQ_ZRTGFXXCX,		// ת��ͨ�ɷ���Ϣ��ѯ 3406
	TDX_ID_FUNC_ANS_ZRTGFXXCX,
	TDX_ID_FUNC_REQ_ZRTRZMRPTCX,	// ת��ͨ�����������ײ�ѯ 3408
	TDX_ID_FUNC_ANS_ZRTRZMRPTCX,
	TDX_ID_FUNC_REQ_ZRTRQMCPTCX,	// ת��ͨ��ȯ�������ײ�ѯ 3410
	TDX_ID_FUNC_ANS_ZRTRQMCPTCX,
	TDX_ID_FUNC_REQ_ZRTZJJRSQPTCX,	// ת��ͨ�ʽ�����������ײ�ѯ 3412
	TDX_ID_FUNC_ANS_ZRTZJJRSQPTCX,
	TDX_ID_FUNC_REQ_ZRTGFJRSQPTCX,	// ת��ͨ�ɷݽ����������ײ�ѯ 3414
	TDX_ID_FUNC_ANS_ZRTGFJRSQPTCX,
	TDX_ID_FUNC_REQ_ZRTJRZQSQPTCX,	// ת��ͨ����չ���������ײ�ѯ 3416
	TDX_ID_FUNC_ANS_ZRTJRZQSQPTCX,
	TDX_ID_FUNC_REQ_ZRTTQGHSQPTCX,	// ת��ͨ��ǰ�黹�������ײ�ѯ 3418
	TDX_ID_FUNC_ANS_ZRTTQGHSQPTCX,
	TDX_ID_FUNC_REQ_ZRTJRYWCDCX,	// ת��ͨ����ҵ�񳷵���ѯ 3420
	TDX_ID_FUNC_ANS_ZRTJRYWCDCX,
	TDX_ID_FUNC_REQ_ZRTJRYWDRCX,	// ת��ͨ����ҵ���ղ�ѯ 3422
	TDX_ID_FUNC_ANS_ZRTJRYWDRCX,
	TDX_ID_FUNC_REQ_ZRTJRYWLSCX,	// ת��ͨ����ҵ����ʷ��ѯ 3424
	TDX_ID_FUNC_ANS_ZRTJRYWLSCX,
	TDX_ID_FUNC_REQ_ZRTDRJRHYCX,	// ת��ͨ���ս����Լ��ѯ 3426
	TDX_ID_FUNC_ANS_ZRTDRJRHYCX,
	TDX_ID_FUNC_REQ_ZRTWLJRHYCX,	// ת��ͨδ�˽����Լ��ѯ 3428
	TDX_ID_FUNC_ANS_ZRTWLJRHYCX,
	TDX_ID_FUNC_REQ_ZRTYLJRHYCX,	// ת��ͨ���˽����Լ��ѯ 3430
	TDX_ID_FUNC_ANS_ZRTYLJRHYCX,
	TDX_ID_FUNC_REQ_ZRTZJCJSQPTCX,	// ת��ͨ�ʽ�����������ײ�ѯ 3432
	TDX_ID_FUNC_ANS_ZRTZJCJSQPTCX,
	TDX_ID_FUNC_REQ_ZRTGFCJSQPTCX,	// ת��ͨ�ɷݳ����������ײ�ѯ 3434
	TDX_ID_FUNC_ANS_ZRTGFCJSQPTCX,
	TDX_ID_FUNC_REQ_ZRTZJCJQDPTCX,	// ת��ͨ�ʽ����ȷ�����ײ�ѯ 3436
	TDX_ID_FUNC_ANS_ZRTZJCJQDPTCX,
	TDX_ID_FUNC_REQ_ZRTGFCJQDPTCX,	// ת��ͨ�ɷݳ���ȷ�����ײ�ѯ 3438
	TDX_ID_FUNC_ANS_ZRTGFCJQDPTCX,
	TDX_ID_FUNC_REQ_ZRTCJYWCDCX,	// ת��ͨ����ҵ�񳷵���ѯ 3440
	TDX_ID_FUNC_ANS_ZRTCJYWCDCX,
	TDX_ID_FUNC_REQ_ZRTCJYWDRCX,	// ת��ͨ����ҵ���ղ�ѯ 3442
	TDX_ID_FUNC_ANS_ZRTCJYWDRCX,
	TDX_ID_FUNC_REQ_ZRTCJYWLSCX,	// ת��ͨ����ҵ����ʷ��ѯ 3444
	TDX_ID_FUNC_ANS_ZRTCJYWLSCX,
	TDX_ID_FUNC_REQ_ZRTCJTQSHPTCX,	// ת��ͨ������ǰ�������ײ�ѯ 3446
	TDX_ID_FUNC_ANS_ZRTCJTQSHPTCX,
	TDX_ID_FUNC_REQ_ZRTCJTYZQPTCX,	// ת��ͨ����ͬ��չ�����ײ�ѯ 3448
	TDX_ID_FUNC_ANS_ZRTCJTYZQPTCX,
	TDX_ID_FUNC_REQ_ZRTQXFLCX,		// ת��ͨ���޷��ʲ�ѯ 3450
	TDX_ID_FUNC_ANS_ZRTQXFLCX,
	TDX_ID_FUNC_REQ_ZRTCJHYCX,		// ת��ͨ�����Լ��ѯ 3452
	TDX_ID_FUNC_ANS_ZRTCJHYCX,
	TDX_ID_FUNC_REQ_ZRTCJLSHYCX,	// ת��ͨ������ʷ��Լ��ѯ 3454
	TDX_ID_FUNC_ANS_ZRTCJLSHYCX,
	TDX_ID_FUNC_REQ_ZRTMCHKPTCX,	// ת��ͨ�����������ײ�ѯ 3456
	TDX_ID_FUNC_ANS_ZRTMCHKPTCX,
	TDX_ID_FUNC_REQ_ZRTMRHQPTCX,	// ת��ͨ���뻹ȯ���ײ�ѯ 3458
	TDX_ID_FUNC_ANS_ZRTMRHQPTCX,
	TDX_ID_FUNC_REQ_ZRTXJHKPTCX,	// ת��ͨ�ֽ𻹿����ײ�ѯ 3460
	TDX_ID_FUNC_ANS_ZRTXJHKPTCX,
	TDX_ID_FUNC_REQ_ZRTXQHQPTCX,	// ת��ͨ��ȯ��ȯ���ײ�ѯ 3462
	TDX_ID_FUNC_ANS_ZRTXQHQPTCX,
	TDX_ID_FUNC_REQ_ZRTKCJXXCX,		// ת��ͨ�ɳ�����Ϣ��ѯ 3464
	TDX_ID_FUNC_ANS_ZRTKCJXXCX,
	TDX_ID_FUNC_REQ_ZRTJRTYSHPTCX,	// ת��ͨ����ͬ���������ײ�ѯ 3466
	TDX_ID_FUNC_ANS_ZRTJRTYSHPTCX,
	TDX_ID_FUNC_REQ_ZRTCJZHXXCX,	// ת��ͨ�����˻���Ϣ��ѯ 3468
	TDX_ID_FUNC_ANS_ZRTCJZHXXCX,

	// ����
	TDX_ID_FUNC_REQ_XLYZT_KTQXZDDL,	// (����)��ͨ/ȡ���Զ���������/�깺/��� 4100
	TDX_ID_FUNC_ANS_XLYZT_KTQXZDDL,
	TDX_ID_FUNC_REQ_XLYZT_KTHZPS,	// (����)��ͨ�������� 4102
	TDX_ID_FUNC_ANS_XLYZT_KTHZPS,
	TDX_ID_FUNC_REQ_XLYZT_QXHZPS,	// (����)ȡ���������� 4104
	TDX_ID_FUNC_ANS_XLYZT_QXHZPS,
	TDX_ID_FUNC_REQ_XLYZT_KTHZHG,	// (����)��ͨ�����ع� 4106
	TDX_ID_FUNC_ANS_XLYZT_KTHZHG,
	TDX_ID_FUNC_REQ_XLYZT_QXHZHG,	// (����)ȡ�������ع� 4108
	TDX_ID_FUNC_ANS_XLYZT_QXHZHG,
	TDX_ID_FUNC_REQ_XLYZT_KTHZSG,	// (����)��ͨ�����깺 4110
	TDX_ID_FUNC_ANS_XLYZT_KTHZSG,
	TDX_ID_FUNC_REQ_XLYZT_QXHZSG,	// (����)ȡ�������깺 4112
	TDX_ID_FUNC_ANS_XLYZT_QXHZSG,
	TDX_ID_FUNC_REQ_XLYZT_DLGNCX,	// ��ѯ����ͨ��Ϣ 4114
	TDX_ID_FUNC_ANS_XLYZT_DLGNCX,
	TDX_ID_FUNC_REQ_SYLPM,			// ���������� 5000
	TDX_ID_FUNC_ANS_SYLPM,
	TDX_ID_FUNC_REQ_ZHRQ,			// �ʻ���ȯ 5002
	TDX_ID_FUNC_ANS_ZHRQ,
	TDX_ID_FUNC_REQ_RQCX,			// ��ȯ��ѯ 5004
	TDX_ID_FUNC_ANS_RQCX,
	TDX_ID_FUNC_REQ_ZHHQZQ,			// �ʻ���ȯչ�� 5006
	TDX_ID_FUNC_ANS_ZHHQZQ,
	TDX_ID_FUNC_REQ_TCMONITOR,		// �������ļ�� 5008
	TDX_ID_FUNC_ANS_TCMONITOR,
	TDX_ID_FUNC_REQ_TSROUTING,		// TS·�� 5010
	TDX_ID_FUNC_ANS_TSROUTING,
};

// ��ȫ�����ֵ�
const WORD tdxScntrStructInfo[]=
{
	// ��ȫ����Э��
	TDX_ID_FUNC_REQ_CA_ZHSQ,		// CA�˻����� 800
	TDX_ID_FUNC_ANS_CA_ZHSQ,
	TDX_ID_FUNC_REQ_CA_ZHCX,		// CA�ʺŲ�ѯ 802
	TDX_ID_FUNC_ANS_CA_ZHCX,
	TDX_ID_FUNC_REQ_CA_ZHJY,		// CA�˻�У�� 804
	TDX_ID_FUNC_ANS_CA_ZHJY,
	TDX_ID_FUNC_REQ_CA_TXMMXG,		// CA��֤�����޸� 806
	TDX_ID_FUNC_ANS_CA_TXMMXG,
	TDX_ID_FUNC_REQ_CA_TXMMCX,		// CA��֤�����ѯ 808
	TDX_ID_FUNC_ANS_CA_TXMMCX,
	TDX_ID_FUNC_REQ_CA_ZSXZ,		// CA֤������ 810
	TDX_ID_FUNC_ANS_CA_ZSXZ,
	TDX_ID_FUNC_REQ_CA_ZSXZQR,		// CA֤������ȷ�� 812
	TDX_ID_FUNC_ANS_CA_ZSXZQR,
	TDX_ID_FUNC_REQ_CA_ZTXM,		// CA״̬�޸� 814
	TDX_ID_FUNC_ANS_CA_ZTXM,
	TDX_ID_FUNC_REQ_CA_ZSGX,		// CA֤����� 816
	TDX_ID_FUNC_ANS_CA_ZSGX,
	TDX_ID_FUNC_REQ_CA_YHFJCX,		// �û��ּ���ѯ 818
	TDX_ID_FUNC_ANS_CA_YHFJCX,
	TDX_ID_FUNC_REQ_CA_YHFJSQ,		// �û��ּ����� 820
	TDX_ID_FUNC_ANS_CA_YHFJSQ,
	TDX_ID_FUNC_REQ_CA_HTTPYHFJCX,	// HTTP�û��ּ���ѯ 822
	TDX_ID_FUNC_ANS_CA_HTTPYHFJCX,
	TDX_ID_FUNC_REQ_CA_ANONUSER,	// (ע��)�����û� 824
	TDX_ID_FUNC_ANS_CA_ANONUSER,

	TDX_ID_FUNC_REQ_CA_XJZT,			// �½����� 826
	TDX_ID_FUNC_ANS_CA_XJZT,
	TDX_ID_FUNC_REQ_CA_CXZT,			// ��ѯ���� 828
	TDX_ID_FUNC_ANS_CA_CXZT,
	TDX_ID_FUNC_REQ_CA_CXHF,			// ��ѯ�ظ� 830
	TDX_ID_FUNC_ANS_CA_CXHF,
	TDX_ID_FUNC_REQ_CA_HFZT,			// �ظ����� 832
	TDX_ID_FUNC_ANS_CA_HFZT,
	TDX_ID_FUNC_REQ_CA_GBZT,			// (������)�ر����� 834
	TDX_ID_FUNC_ANS_CA_GBZT,
	TDX_ID_FUNC_REQ_CA_USERMESSAGE,		// �û�(����)��Ϣ 836
	TDX_ID_FUNC_ANS_CA_USERMESSAGE,
	TDX_ID_FUNC_REQ_CA_USERACTION,		// �����û����� 838
	TDX_ID_FUNC_ANS_CA_USERACTION,
	TDX_ID_FUNC_REQ_CA_ANONYLOGIN,		// �����û���¼ 840
	TDX_ID_FUNC_ANS_CA_ANONYLOGIN,
	TDX_ID_FUNC_REQ_CA_QUERYMSG,		// ��ѯ�Ƿ����������� 842
	TDX_ID_FUNC_ANS_CA_QUERYMSG,
	TDX_ID_FUNC_REQ_CA_READED,			// ���Ķ����� 844
	TDX_ID_FUNC_ANS_CA_READED,
	TDX_ID_FUNC_REQ_CA_NOTICEINFO,		// �û����漰����������Ϣ 846
	TDX_ID_FUNC_ANS_CA_NOTICEINFO,
	TDX_ID_FUNC_REQ_CA_INFOFEEDBACK,	// �û���Ѷ��Ϣ���� 848
	TDX_ID_FUNC_ANS_CA_INFOFEEDBACK,

	TDX_ID_FUNC_REQ_TQ_KHJY,			// TQУ�� 860
	TDX_ID_FUNC_ANS_TQ_KHJY,
	TDX_ID_FUNC_REQ_UM_UBROKER,			// ����֤ȯ�û�Ͷ�ʹ�����Ϣ 862
	TDX_ID_FUNC_ANS_UM_UBROKER,

	TDX_ID_FUNC_REQ_CA_SYZC_GD,			// ����(�û�)ע�� 880
	TDX_ID_FUNC_ANS_CA_SYZC_GD,		
	TDX_ID_FUNC_REQ_CA_XXLR_GD,			// (��ϸ)��Ϣ¼�� 882
	TDX_ID_FUNC_ANS_CA_XXLR_GD,		
	TDX_ID_FUNC_REQ_CA_SYJH_GD,			// ����(�û�)���� 884
	TDX_ID_FUNC_ANS_CA_SYJH_GD,		
	TDX_ID_FUNC_REQ_CA_ZHJY_GD,			// �˻�У�� 886
	TDX_ID_FUNC_ANS_CA_ZHJY_GD,		
	TDX_ID_FUNC_REQ_CA_DJCX_GD,			// �ȼ���ѯ 888
	TDX_ID_FUNC_ANS_CA_DJCX_GD,		
	TDX_ID_FUNC_REQ_CA_KSJCX_GD,		// ����(��)��(��)��ѯ 890
	TDX_ID_FUNC_ANS_CA_KSJCX_GD,	
	TDX_ID_FUNC_REQ_CA_KHSQ_GD,			// �ͻ�����(����) 892
	TDX_ID_FUNC_ANS_CA_KHSQ_GD,
	TDX_ID_FUNC_REQ_CA_YHZXQX_GD,		// �û���ѶȨ�� 894
	TDX_ID_FUNC_ANS_CA_YHZXQX_GD,
	TDX_ID_FUNC_REQ_CA_YHQXZX,			// �û�Ȩ��ע�� 896
	TDX_ID_FUNC_ANS_CA_YHQXZX,
	TDX_ID_FUNC_REQ_CA_CXDLLS,			// ��ѯ��¼��ʷ 898
	TDX_ID_FUNC_ANS_CA_CXDLLS,

	TDX_ID_FUNC_REQ_CA_AQGNSQ,			// ��ȫ�������� 4200
	TDX_ID_FUNC_ANS_CA_AQGNSQ,
	TDX_ID_FUNC_REQ_CA_AQGNCX,			// ��ȫ���ܳ��� 4202
	TDX_ID_FUNC_ANS_CA_AQGNCX,
	TDX_ID_FUNC_REQ_CA_MMBHWTJY,		// ���뱣������У�� 4204
	TDX_ID_FUNC_ANS_CA_MMBHWTJY,
	TDX_ID_FUNC_REQ_CA_GETTZZB,			// ��ȡ��ս���� 4206
	TDX_ID_FUNC_ANS_CA_GETTZZB,
	TDX_ID_FUNC_REQ_CA_ZXJZK,			// ע������ 4208
	TDX_ID_FUNC_ANS_CA_ZXJZK,
	TDX_ID_FUNC_REQ_CA_YLWT,			// Ԥ������ 4210
	TDX_ID_FUNC_ANS_CA_YLWT,
	TDX_ID_FUNC_REQ_CA_CERRAREQ,		// ֤������ 4212
	TDX_ID_FUNC_ANS_CA_CERRAREQ,
	TDX_ID_FUNC_REQ_CA_CERAUDIT,		// ֤����� 4214
	TDX_ID_FUNC_ANS_CA_CERAUDIT,
	TDX_ID_FUNC_REQ_CA_CERDOWNLOAD,		// ֤������ 4216
	TDX_ID_FUNC_ANS_CA_CERDOWNLOAD,
	TDX_ID_FUNC_REQ_CA_CERDLCONFIRM,	// ֤������ȷ�� 4218
	TDX_ID_FUNC_ANS_CA_CERDLCONFIRM,
	TDX_ID_FUNC_REQ_CA_ADDYHXX,			// ����û���Ϣ 4220
	TDX_ID_FUNC_ANS_CA_ADDYHXX,
	TDX_ID_FUNC_REQ_CA_XGYHXX,			// �޸��û���Ϣ 4222
	TDX_ID_FUNC_ANS_CA_XGYHXX,
	TDX_ID_FUNC_REQ_CA_CXYHXX,			// ��ѯ�û���Ϣ 4224
	TDX_ID_FUNC_ANS_CA_CXYHXX,
	TDX_ID_FUNC_REQ_CA_GETYZM,			// ��ȡ�ֻ���֤�� 4226
	TDX_ID_FUNC_ANS_CA_GETYZM,
	TDX_ID_FUNC_REQ_CA_YZMJY,			// ��֤��У�� 4228
	TDX_ID_FUNC_ANS_CA_YZMJY,
	TDX_ID_FUNC_REQ_OTHERCA_BASEFUN,	// ������ȫ��֤У�� 4230
	TDX_ID_FUNC_ANS_OTHERCA_BASEFUN,
	TDX_ID_FUNC_REQ_CA_MMBHWTCX,		// ��ѯ���뱣������ 4232
	TDX_ID_FUNC_ANS_CA_MMBHWTCX,
	TDX_ID_FUNC_REQ_CA_XGMMBHWT,		// �޸����뱣������ 4234
	TDX_ID_FUNC_ANS_CA_XGMMBHWT,
	TDX_ID_FUNC_REQ_CA_XGYLWT,			// �޸�Ԥ������ 4236
	TDX_ID_FUNC_ANS_CA_XGYLWT,
	TDX_ID_FUNC_REQ_CA_PWDPROTQUEQU,	// ���뱣�������б��ѯ 4238
	TDX_ID_FUNC_ANS_CA_PWDPROTQUEQU,
	TDX_ID_FUNC_REQ_CA_APPLYPWDQA,		// �������뱣������ 4240
	TDX_ID_FUNC_ANS_CA_APPLYPWDQA,
	TDX_ID_FUNC_REQ_CA_BINDMACHINE,		// �������������� 4242
	TDX_ID_FUNC_ANS_CA_BINDMACHINE,
	TDX_ID_FUNC_REQ_CA_QUEBINDINFO,		// ��ѯ����Ϣ 4244
	TDX_ID_FUNC_ANS_CA_QUEBINDINFO,
	TDX_ID_FUNC_REQ_CA_CANCELBIND,		// ȡ������Ϣ 4246
	TDX_ID_FUNC_ANS_CA_CANCELBIND,
	TDX_ID_FUNC_REQ_CA_SAFEMODQUE,		// ��ȫ����״̬��ѯ 4248
	TDX_ID_FUNC_ANS_CA_SAFEMODQUE,
	TDX_ID_FUNC_REQ_CA_ABUSERLV,		// �����û���ȫ���� 4248
	TDX_ID_FUNC_ANS_CA_ABUSERLV,
	TDX_ID_FUNC_REQ_CA_USERLOGOUT,		// �û����� 4252
	TDX_ID_FUNC_ANS_CA_USERLOGOUT,
	TDX_ID_FUNC_REQ_CA_USERALIVE,		// �û��������� 4254
	TDX_ID_FUNC_ANS_CA_USERALIVE,
	TDX_ID_FUNC_REQ_CA_CANCELLV,		// ȡ���û����� 4256
	TDX_ID_FUNC_ANS_CA_CANCELLV,
	TDX_ID_FUNC_REQ_CA_GETPROINFO,		// ��ȡ��Ʒ���� 4258
	TDX_ID_FUNC_ANS_CA_GETPROINFO,
	TDX_ID_FUNC_REQ_CA_REGUSER,			// ע���û� 4280
	TDX_ID_FUNC_ANS_CA_REGUSER,
	TDX_ID_FUNC_REQ_CA_ALTERREGPWD,		// �޸�ע������ 4283
	TDX_ID_FUNC_ANS_CA_ALTERREGPWD,
	TDX_ID_FUNC_REQ_CA_SSO,				// �����½���Ʋ��� 4284
	TDX_ID_FUNC_ANS_CA_SSO,
	TDX_ID_FUNC_REQ_CA_SSOYHXX,			// �����½��������ȡ�û���Ϣ 4286
	TDX_ID_FUNC_ANS_CA_SSOYHXX,
	TDX_ID_FUNC_REQ_CA_CERDEL,			// ֤�����
	TDX_ID_FUNC_ANS_CA_CERDEL,
	TDX_ID_FUNC_REQ_CA_OTPSYN,			//	OTPͬ��
	TDX_ID_FUNC_ANS_CA_OTPSYN,
	TDX_ID_FUNC_REQ_CA_CHECKRECORD,		// �������һ����
	TDX_ID_FUNC_ANS_CA_CHECKRECORD,
	TDX_ID_FUNC_REQ_CA_PAAUTH,			// �û���֤ 4284
	TDX_ID_FUNC_ANS_CA_PAAUTH,
	TDX_ID_FUNC_REQ_CA_ACCREPORT,		// Ͷ����ϱ���
	TDX_ID_FUNC_ANS_CA_ACCREPORT,
	TDX_ID_FUNC_REQ_CA_OTPTEMP,			// OTP����
	TDX_ID_FUNC_ANS_CA_OTPTEMP,
	TDX_ID_FUNC_REQ_OTHERCA_GETYZM,		// ��ȡ�����ֻ���֤�� 4300
	TDX_ID_FUNC_ANS_OTHERCA_GETYZM,
	TDX_ID_FUNC_REQ_OPMYSTOCK,			// ��ѡ���ϴ����� 4302
	TDX_ID_FUNC_ANS_OPMYSTOCK,
	TDX_ID_FUNC_REQ_FETCHPWD,			// �һ��û����� 4304
	TDX_ID_FUNC_ANS_FETCHPWD,			
	TDX_ID_FUNC_REQ_FETCHUSERACCOUNT,	// �һ��û��ʺ� 4306
	TDX_ID_FUNC_ANS_FETCHUSERACCOUNT,
	TDX_ID_FUNC_REQ_QUERYSCORE,			// ���ֲ�ѯ 4308
	TDX_ID_FUNC_ANS_QUERYSCORE,	
	TDX_ID_FUNC_REQ_QUERYREGUDATA,		// ע���û���Ϣ��ѯ 4310
	TDX_ID_FUNC_ANS_QUERYREGUDATA,
	TDX_ID_FUNC_REQ_GETACTIVECODE,		// ��ȡ������ 4312
	TDX_ID_FUNC_ANS_GETACTIVECODE,
	TDX_ID_FUNC_REQ_QRYSCFUNC,			// ��ȫ���ܲ�ѯ	4500
	TDX_ID_FUNC_ANS_QRYSCFUNC,
	TDX_ID_FUNC_REQ_SWITCHSCFUNC,		// ����/�رհ�ȫ���� 4502
	TDX_ID_FUNC_ANS_SWITCHSCFUNC,
	TDX_ID_FUNC_REQ_UNIAUTH,			// ͳһ��֤ 4504
	TDX_ID_FUNC_ANS_UNIAUTH,
	TDX_ID_FUNC_REQ_REQAPWD,			// ������֤���� 4506
	TDX_ID_FUNC_ANS_REQAPWD,
	TDX_ID_FUNC_REQ_MODAPWD,			// �޸���֤���� 4508
	TDX_ID_FUNC_ANS_MODAPWD,
	TDX_ID_FUNC_REQ_RESETAPWD,			// ������֤���� 4510
	TDX_ID_FUNC_ANS_RESETAPWD,
	TDX_ID_FUNC_REQ_SYNOTP,				// ͬ��OTP 4512
	TDX_ID_FUNC_ANS_SYNOTP,
	TDX_ID_FUNC_REQ_GETCSIGNKEY,		// ��ȡ֤��ǩ���� 4514
	TDX_ID_FUNC_ANS_GETCSIGNKEY,
	TDX_ID_FUNC_REQ_UPDCERT,			// ����֤�� 4516
	TDX_ID_FUNC_ANS_UPDCERT,
	TDX_ID_FUNC_REQ_GETCCODE,			// ��ȡ�ֻ���̬�� 4518
	TDX_ID_FUNC_ANS_GETCCODE,
	TDX_ID_FUNC_REQ_PERMITMACHINE,		// ��Ȩ����� 4520
	TDX_ID_FUNC_ANS_PERMITMACHINE,
	TDX_ID_FUNC_REQ_FREEMACHINE,		// ����������Ȩ 4522
	TDX_ID_FUNC_ANS_FREEMACHINE,
	TDX_ID_FUNC_REQ_QRYPERMITION,		// ��ѯ��Ȩ 4524
	TDX_ID_FUNC_ANS_QRYPERMITION,
	TDX_ID_FUNC_REQ_UPDSELFINFO,		// ����Ԥ����Ϣ 4526
	TDX_ID_FUNC_ANS_UPDSELFINFO,
	TDX_ID_FUNC_REQ_QRYUSERCOMMON,		// ��ѯ�û�������Ϣ 4528
	TDX_ID_FUNC_ANS_QRYUSERCOMMON,
	TDX_ID_FUNC_REQ_QRYUDATA,			// �û����ϲ�ѯ 4530
	TDX_ID_FUNC_ANS_QRYUDATA,
	TDX_ID_FUNC_REQ_UPDUDATA,			// �����û����� 4532
	TDX_ID_FUNC_ANS_UPDUDATA,
	TDX_ID_FUNC_REQ_QRYIMPOTOP,			// �ؼ�������ѯ 4534
	TDX_ID_FUNC_ANS_QRYIMPOTOP,
	TDX_ID_FUNC_REQ_RCDIMPOTOP,			// �ؼ�������¼ 4536
	TDX_ID_FUNC_ANS_RCDIMPOTOP,
	TDX_ID_FUNC_REQ_QRYAUTHHIS,			// ��֤��ʷ��ѯ 4538
	TDX_ID_FUNC_ANS_QRYAUTHHIS,
	TDX_ID_FUNC_REQ_REQQAPROT,			// ���뱣���������� 4540
	TDX_ID_FUNC_ANS_REQQAPROT,
	TDX_ID_FUNC_REQ_MODQAPROT,			// ���뱣�������޸� 4542
	TDX_ID_FUNC_ANS_MODQAPROT,
	TDX_ID_FUNC_REQ_AUTHQAPROT,			// ���뱣��У�� 4544
	TDX_ID_FUNC_ANS_AUTHQAPROT,
	TDX_ID_FUNC_REQ_RESVPWD,			// Ӧ������ 4546
	TDX_ID_FUNC_ANS_RESVPWD,
	TDX_ID_FUNC_REQ_CONSIS,				// ���������ǩ����Ϣ
	TDX_ID_FUNC_ANS_CONSIS,
};


// ��־�鿴�ֵ�
const WORD tdxRZStructInfo[]=
{	
	TDX_ID_FUNC_REQ_KHJY,			// �ͻ�У�� 100
	TDX_ID_FUNC_ANS_KHJY,	
	TDX_ID_FUNC_REQ_CACHE,			// ȡ������Ϣ 112
	TDX_ID_FUNC_ANS_CACHE,
	TDX_ID_FUNC_REQ_GDCX,			// �ɶ���ѯ 1122
	TDX_ID_FUNC_ANS_GDCX,
	TDX_ID_FUNC_REQ_YHXX,			// ������Ϣ 908
	TDX_ID_FUNC_ANS_YHXX,
	TDX_ID_FUNC_REQ_XGMM,			// �޸����� 106
	TDX_ID_FUNC_ANS_XGMM,

	TDX_ID_FUNC_REQ_RZ_KHCZJLCX,	// �ͻ�������¼��ѯ 1002
	TDX_ID_FUNC_ANS_RZ_KHCZJLCX,
	TDX_ID_FUNC_REQ_RZ_ZHSQ,		// �˺����� 1004
	TDX_ID_FUNC_ANS_RZ_ZHSQ,
	TDX_ID_FUNC_REQ_RZ_ZHDJJD,		// �˺Ŷ���ⶳ 1006
	TDX_ID_FUNC_ANS_RZ_ZHDJJD,
	TDX_ID_FUNC_REQ_RZ_CXTJFX,		// ��ѯͳ�Ʒ��� 1008
	TDX_ID_FUNC_ANS_RZ_CXTJFX,
	TDX_ID_FUNC_REQ_RZ_QDYGBCX,		// ������رղ�ѯ 1010
	TDX_ID_FUNC_ANS_RZ_QDYGBCX,
	TDX_ID_FUNC_REQ_RZ_HTFMCD,		// ��̨��æ�̶� 1012
	TDX_ID_FUNC_ANS_RZ_HTFMCD,
	TDX_ID_FUNC_REQ_RZ_HTCFHCX,		// ��̨�����ɲ�ѯ 1014
	TDX_ID_FUNC_ANS_RZ_HTCFHCX,
	TDX_ID_FUNC_REQ_RZ_FXIPPM,		// ����IP���� 1016
	TDX_ID_FUNC_ANS_RZ_FXIPPM,
	TDX_ID_FUNC_REQ_RZ_FXZH,		// �����˺� 1018
	TDX_ID_FUNC_ANS_RZ_FXZH,
	TDX_ID_FUNC_REQ_RZ_FXXXXX,		// �����˺� 1020
	TDX_ID_FUNC_ANS_RZ_FXXXXX,
	TDX_ID_FUNC_REQ_RZ_HTFMCDXX,	// ��̨��æ�̶���ϸ 1022
	TDX_ID_FUNC_ANS_RZ_HTFMCDXX,
	TDX_ID_FUNC_REQ_RZ_TCIP,		// ��������IP 1024
	TDX_ID_FUNC_ANS_RZ_TCIP,
};


//---------------------------------------------------------------------------
// Part.IV �ṹ��Ӧ���ֶζ���
//---------------------------------------------------------------------------


// ʾ��(��ͨ)
const WORD tdxFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�
	TDX_ID_ZHLB,				// �ʺ����
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ
};

// ʾ��(����ʽ����)
const WORD tdxKFSJJFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�
	TDX_ID_ZHLB,				// �ʺ����
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// ����˾����
	TDX_ID_KFSJJ_JJZH,			// �����ʺ�
	TDX_ID_KFSJJ_JJDM,			// �������
};

// �˺�Ԥ���� 94
const WORD tdxZHYCLFieldReq[]=
{
	TDX_ID_XT_LOGINID,			// ��¼�ʺ�(�ɶ������ʽ��ʺŵ�У���ʺ�)
	TDX_ID_XT_LOGINPASSWD,		// ��¼����(�����ֶ�)
	TDX_ID_XT_COMMPASSWD,		// ͨѶ����(��̨��¼��ͨѶ����)
	TDX_ID_XT_LOGINTYPE,		// ��¼�ʺ����
	TDX_ID_XT_AUTH_MODE,		// (��̨,����)��֤ģʽ(ȡֵ��"��ȫ������")
	TDX_ID_XT_AUTH_INFO,		// (��̨,����)��֤��Ϣ
	TDX_ID_XT_CLITYPE,			// �ͻ�����
	TDX_ID_XT_CLIVER,			// �ͻ��˰汾

	TDX_ID_CZBZ,				// ������־
	TDX_ID_XT_PREPASSWORD0,		// Ԥ��������0
	TDX_ID_XT_PREPASSWORD1,		// Ԥ��������1
	TDX_ID_XT_PREPASSWORD2,		// Ԥ��������2
	TDX_ID_XT_PREPASSWORD3,		// Ԥ��������3
	TDX_ID_XT_PREPASSWORD4,		// Ԥ��������4
	TDX_ID_XT_PREPARAM0,		// Ԥ�������0
	TDX_ID_XT_PREPARAM1,		// Ԥ�������1
	TDX_ID_XT_PREPARAM2,		// Ԥ�������2
	TDX_ID_XT_PREPARAM3,		// Ԥ�������3
	TDX_ID_XT_PREPARAM4,		// Ԥ�������4
	TDX_ID_XT_PREPARAM5,		// Ԥ�������5
	TDX_ID_XT_PREPARAM6,		// Ԥ�������6
	TDX_ID_XT_PREPARAM7,		// Ԥ�������7
	TDX_ID_XT_PREPARAM8,		// Ԥ�������8
	TDX_ID_XT_PREPARAM9,		// Ԥ�������9
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
};

// ��¼Ԥ���� 96
const WORD tdxDLYCLFieldReq[]=
{
	TDX_ID_XT_LOGINID,			// ��¼�ʺ�(�ɶ������ʽ��ʺŵ�У���ʺ�)
	TDX_ID_XT_LOGINPASSWD,		// ��¼����(�����ֶ�)
	TDX_ID_XT_COMMPASSWD,		// ͨѶ����(��̨��¼��ͨѶ����)
	TDX_ID_XT_LOGINTYPE,		// ��¼�ʺ����
	TDX_ID_XT_AUTH_MODE,		// (��̨,����)��֤ģʽ(ȡֵ��"��ȫ������")
	TDX_ID_XT_AUTH_INFO,		// (��̨,����)��֤��Ϣ
	TDX_ID_XT_CLITYPE,			// �ͻ�����
	TDX_ID_XT_CLIVER,			// �ͻ��˰汾

	TDX_ID_CZBZ,				// ������־(0/(-1)--��������,1--��ȡ�����)
	TDX_ID_XT_MACHINEINFO,		// ������Ϣ(��ʽͬ"���ɿͻ�У�� 98"/"�ͻ�У�� 100")
	TDX_ID_XT_MACHINECODE,		// ����������(��Բ�ͬȯ�̸�ʽ������ַ���)
	TDX_ID_XT_CLIENTINVERSION,	// �ͻ����ڲ��汾
	TDX_ID_XT_VERSIONSTRING,	// �汾�ַ���
};

// ���ɿͻ�У�� 98
const WORD tdxJCKHJYFieldReq[]=
{
	TDX_ID_XT_LOGINID,			// ��¼�ʺ�(�ɶ������ʽ��ʺŵ�У���ʺ�)
	TDX_ID_XT_LOGINPASSWD,		// ��¼����(�����ֶ�)
	TDX_ID_XT_COMMPASSWD,		// ͨѶ����(��̨��¼��ͨѶ����)
	TDX_ID_XT_LOGINTYPE,		// ��¼�ʺ����
	TDX_ID_XT_AUTH_MODE,		// (��̨,����)��֤ģʽ(ȡֵ��"��ȫ������")
	TDX_ID_XT_AUTH_INFO,		// (��̨,����)��֤��Ϣ
	TDX_ID_XT_CLITYPE,			// �ͻ�����
	TDX_ID_XT_CLIVER,			// �ͻ��˰汾
                            	
	TDX_ID_KHMC,				// (���Ͻ��׿�ͨ)�ͻ�����
	TDX_ID_ZJZH,				// (���Ͻ��׿�ͨ)�ʽ��ʺ�
	TDX_ID_ZJHM,				// (���Ͻ��׿�ͨ)֤������
	TDX_ID_MOBILEPHONE,			// (���Ͻ��׿�ͨ)�ƶ��绰
	TDX_ID_USERPHONE,			// (���Ͻ��׿�ͨ)�̶��绰
	TDX_ID_USEREMAIL,			// (���Ͻ��׿�ͨ)�����ʼ�
	TDX_ID_SHGD,				// (���Ͻ��׿�ͨ)�Ϻ��ɶ�����
	TDX_ID_SZGD,				// (���Ͻ��׿�ͨ)���ڹɶ�����
                            	
	TDX_ID_XT_GTLB,				// ��̨���(0:Ĭ�� 1:���ý��� 2:��Ʊ 3:���� 4:��Ʒ�ڻ� 5:�����ڻ� 6:�۹�),ԭ���ý��ױ�ʶ�ֶ�
	TDX_ID_XT_RECONNECTFLAG,	// ����������־
	TDX_ID_XT_QUERYMODE,		// ��ѯģʽ��־
	TDX_ID_XT_VIPFLAG,			// VIP��־
	TDX_ID_XT_MACHINEINFO,		// ������Ϣ(��ʽ[����ֺŷָ�,����ŷָ�]: ����IP;������;�û���;�ڴ�;CPU��Ϣ;CPUID;ϵͳ�汾;IP�б�;MAC��ַ�б�;Ӳ�����к��б�;BIOS�汾...)
	TDX_ID_XT_LIMITMODE,		// ����ģʽ(1--֧������ģʽ,0/����--��֧������ģʽ)
	TDX_ID_XT_SESSION,			// �Ự��Ϣ
	TDX_ID_YYB,					// (����)Ӫҵ��
	TDX_ID_CZBZ,				// ������־(0/(-1)--������½,1--��ȡ������֤��)
	TDX_ID_XT_REALCLIENTVERSION,// �ڲ��ͻ��˰汾
	TDX_ID_XT_REDIRECTFLAG,		// �ض����־(1--�ض����¼,����--����)
	TDX_ID_XT_REDIRECTINFO,		// �ض�����Ϣ(�ض����־=1ʱ��Ч)
	TDX_ID_XT_MULTINITICE,		// ����ʾ��Ϣ
	TDX_ID_XT_LOGINENTERPARAM,	// ��¼�������
	TDX_ID_XT_MACHINECODE,		// ����������(��Բ�ͬȯ�̸�ʽ������ַ���)
	TDX_ID_XT_CLIENTINVERSION,	// �ͻ����ڲ��汾
	TDX_ID_XT_VERSIONSTRING,	// �汾�ַ���
};

// ���ɿͻ�У�� 99
const WORD tdxJCKHJYFieldAns[]=
{
	TDX_ID_XT_FUNCID,			// Ӧ������Ĺ���ID
	TDX_ID_XT_FUNCDICTTAG,		// Ӧ������Ĺ����ֵ��ʶ
	TDX_ID_XT_FUNCCONTENT,		// Ӧ������Ĺ�������
	TDX_ID_XT_RESERVED,			// ������Ϣ
};

// �ͻ�У�� 100
const WORD tdxKHJYFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���(�ɶ������ʽ��ʺŵ�У���ʺ�)
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// (���Ͻ��׿�ͨ)�ʽ��ʺ�
	TDX_ID_ZHLB,				// �ʺ����(��¼�ʺ����)
	TDX_ID_GDDM,				// �ɶ�����(����TDX_ID_KHH����)
	TDX_ID_XT_CLITYPE,			// �ͻ�������
	TDX_ID_XT_AUTH_MODE,		// (��̨,����)��֤ģʽ(ȡֵ��"��ȫ������")
	TDX_ID_XT_AUTH_INFO,		// (��̨,����)��֤��Ϣ
                            	
	TDX_ID_KHMC,				// (���Ͻ��׿�ͨ)�ͻ�����
	TDX_ID_ZJHM,				// (���Ͻ��׿�ͨ)֤������
	TDX_ID_MOBILEPHONE,			// (���Ͻ��׿�ͨ)�ƶ��绰
	TDX_ID_USERPHONE,			// (���Ͻ��׿�ͨ)�̶��绰
	TDX_ID_USEREMAIL,			// (���Ͻ��׿�ͨ)�����ʼ�
	TDX_ID_SHGD,				// (���Ͻ��׿�ͨ)�Ϻ��ɶ�����
	TDX_ID_SZGD,				// (���Ͻ��׿�ͨ)���ڹɶ�����
	TDX_ID_TXMM,				// (��¼)ͨѶ����
                            	
	TDX_ID_BANKCODE,			// (���п���,����)���д���
	TDX_ID_BANKYYB,				// (���п���,����)����Ӫҵ������(ʵ��Ӫҵ������)
	TDX_ID_BANKGDTYPE,			// (���п���,����)���йɶ����
                            	
	TDX_ID_XT_GTLB,				// �ͻ����(0:Ĭ�� 1:���ý��� 2:��Ʊ 3:���� 4:��Ʒ�ڻ� 5:�����ڻ� 6:�۹�),ԭ���ý��ױ�ʶ�ֶ�
	TDX_ID_XT_RECONNECTFLAG,	// ����������־
	TDX_ID_XT_QUERYMODE,		// ��ѯģʽ
	TDX_ID_XT_VIPFLAG,			// VIP��־
	TDX_ID_XT_MACHINEINFO,		// ������Ϣ(��ʽ[����ֺŷָ�,����ŷָ�]: ����IP;������;�û���;�ڴ�;CPU��Ϣ;CPUID;ϵͳ�汾;IP�б�;MAC��ַ�б�;Ӳ�����к��б�;BIOS�汾;...)
	TDX_ID_XT_LIMITMODE,		// ����ģʽ(1--֧������ģʽ,0/����--��֧������ģʽ)
	TDX_ID_XT_SESSION,			// �Ự��Ϣ
	TDX_ID_XT_REDIRECTFLAG,		// �ض����־(1--�ض����¼,����--����)
	TDX_ID_XT_REDIRECTINFO,		// �ض�����Ϣ(�ض����־=1ʱ��Ч)
	TDX_ID_XT_MOBILEMACHINEINFO,// �ֻ�������Ϣ
	TDX_ID_XT_LOGINENTERPARAM,	// ��¼�������
	TDX_ID_XT_MACHINECODE,		// ����������(��Բ�ͬȯ�̸�ʽ������ַ���)
	TDX_ID_XT_CLIENTINVERSION,	// �ͻ����ڲ��汾
	TDX_ID_XT_VERSIONSTRING,	// �汾�ַ���
};                          	

// ��ѯ���� 102
const WORD tdxCXHQFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���(�ɶ������ʽ��ʺŵ�У���ʺ�)
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (�ڻ�)�ʺ����
	TDX_ID_GDDM,				// (�ڻ�)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_SCFLAG,				// (����)�г�����
	TDX_ID_ZQDM,				// ֤ȯ����
	TDX_ID_HYDM,				// (����,�ڻ�)��Լ����(�ڻ�ʹ��)
	TDX_ID_CZBZ,				// ������־(1--����֤ȯ���������ʾ��Ϣ[TDX_ID_RETINFO],Ĭ��--0)
};

// �ʽ���� 104
const WORD tdxZJYEFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
	TDX_ID_BZ,					// (��ѡ)����(CZBZ=1ʱ��Ч)
	TDX_ID_CZBZ,				// (��ѡ)������־(1--[����֤ȯ]��ȡ�ʽ��ѯ,0/...--�����ʽ��ѯ)
	TDX_ID_XT_MODE,				// ģʽ(��λ�ñ�־)
};

// �޸�(����)���� 106
const WORD tdxXGMMFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
	
	TDX_ID_XJYMM,				// �½�������
	TDX_ID_ZJMM,				// �ʽ�����(�۹�ʹ��)
	TDX_ID_XZJMM,				// ���ʽ�����(�۹�ʹ��)
	TDX_ID_XT_SESSION,			// �Ự��Ϣ
};

// �޸��ʽ����� 108
const WORD tdxXGZJMMFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_ZJMM,				// �ʽ�����
	TDX_ID_XZJMM,				// ���ʽ�����
	TDX_ID_XT_PARAM,			// ����
};

// �������(��)�� 110
const WORD tdxJSKMSFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_ZQDM,				// ֤ȯ����
	TDX_ID_MMBZ,				// ������־(0-�޼����� 1-�޼����� 'C'-�м����� ...)
	TDX_ID_NOW,					// ί�м۸�
	TDX_ID_KYZJ,				// �����ʽ�
	TDX_ID_WTFS,				// ί������(�м�����)

	TDX_ID_HYDM,				// (����,�ڻ�)��Լ����
	TDX_ID_KPBZ,				// (�ڻ�)��ƽ��־
	TDX_ID_TBBZ,				// (�ڻ�)Ͷ����־
	TDX_ID_XWDM,				// (�ڻ�)ϯλ����

	TDX_ID_DFXWDM,				// �Է�ϯλ����
	TDX_ID_DFZJZH,				// �Է��ʽ��ʺ�
	TDX_ID_DFGDDM,				// �Է��ɶ�����
	TDX_ID_DFZHLB,				// �Է��ʺ����

	TDX_ID_CZBZ,				// ������־(0--��ͨ����,1--��������,2--����������־,3--ֻ���ط�����Ϣ,4--ת��ͨ��������,5--ת��ͨƽ������,6--ת��ͨת��,����--δ��)
	TDX_ID_DFFZDM,				// �Է���֧����
	TDX_ID_DFKHDM,				// �Է��ͻ�����
	TDX_ID_DFMM,				// �Է�����

	TDX_ID_SBMRJ,				// �걨�����(CZBZ=2ʱ��Ч)
	TDX_ID_SBMCJ,				// �걨������(CZBZ=2ʱ��Ч)
	TDX_ID_XT_CHECKRISKFLAG,	// �����ձ�־
	TDX_ID_WTBH,				// ί�б��
	TDX_ID_XT_FUNCTIONVERSION,	// ���ܰ汾
	TDX_ID_WTRQ,				// ί������
};

// ȡ������Ϣ 112
const WORD tdxCACHEFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���(�ɶ������ʽ��ʺŵ�У���ʺ�)
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(��¼�ʺ����)
	TDX_ID_GDDM,				// �ɶ�����(����TDX_ID_KHH����)
	TDX_ID_OP_WTFS,				// ������ʽ
	
	TDX_ID_BANKCODE,			// (���п���,����)���д���
	TDX_ID_BANKYYB,				// (���п���,����)����Ӫҵ������(ʵ��Ӫҵ������)
	TDX_ID_BANKGDTYPE,			// (���п���,����)���йɶ����
	
	TDX_ID_XT_GTLB,				// �ͻ����(0:Ĭ�� 1:���ý��� 2:��Ʊ 3:���� 4:��Ʒ�ڻ� 5:�����ڻ� 6:�۹�),ԭ���ý��ױ�ʶ�ֶ�
	TDX_ID_TXMM,				// ͨ������
	TDX_ID_XT_QUERYMODE,		// ��ѯģʽ
	TDX_ID_YYB,					// Ӫҵ��(����ʹ��,�ͷ���Ӫҵ��)
	TDX_ID_XT_MACHINEINFO,		// ������Ϣ(��ʽ[����ֺŷָ�,����ŷָ�]: ����IP;������;�û���;�ڴ�;CPU��Ϣ;CPUID;ϵͳ�汾;IP�б�;MAC��ַ�б�;Ӳ�����к��б�;BIOS�汾;...)
	TDX_ID_XT_MACHINECODE,		// ����������(��Բ�ͬȯ�̸�ʽ������ַ���)
};

// �޸Ĺ����ʽ��ʺ� 114
const WORD tdxXGGLZJZHFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
};

// �ͻ�ע�� 116
const WORD tdxKHZXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ
};

// ����ȡ�����ʵ�(�ʼ�) 118
const WORD tdxDYQXDZDFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(����)
	TDX_ID_GDDM,				// �ɶ�����(����)
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_CZBZ,				// ������־(0:��ͨ,1:ȡ��,2:��ѯ)
	TDX_ID_DZDLX,				// ���ʵ�����(0:�¶��ʵ�)
	TDX_ID_POSTALCODE,			// ��������
	TDX_ID_USERADDRESS,			// ͨѶ��ַ
};


// ί�ж����ʽ� 120
const WORD tdxWTDJZJFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
};

// ��ӡ���ʵ� 122
const WORD tdxPRINTDZDFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
	
	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_CZBZ,				// ������־(0:�������ʵ�,1:���ܶ��ʵ�,2 �ڻ����㵥,3 ��ʽ���ʵ�[ֻ����һ����¼--���ʵ���ʽ�����ļ�])
	TDX_ID_BZ,					// ����(һ�㲻��)
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����(�ڻ��������)
	
	TDX_ID_LX,					// (�ڻ�)(�ʵ�)����(0:�ս��㵥,1:�½��㵥)
};

// ��ӡ���ܶ��ʵ� 124 (����)
const WORD tdxPRINTHZDZDFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
	
	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_BZ,					// ����(һ�㲻��)
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

// ��ӡ��� 126 (Ӫҵ����)
const WORD tdxPRINTJGDFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_BZ,					// (����)����
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// �޸���֤���� 128
const WORD tdxXGTXMMFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_TXMM,				// ͨѶ����
	TDX_ID_XTXMM,				// ��ͨѶ����
};

// �ʺŽⶳ 130
const WORD tdxZHJDFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
};

// �ʽ�鼯 132
const WORD tdxZJGJFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_BZ,					// ����

	TDX_ID_CZBZ,				// ������־(1--�ƻ�ת��,����--ʵʱת��)
	TDX_ID_WTRQ,				// ί������(�ƻ�ת������,CZBZ=1ʱ��Ч)
	TDX_ID_WTSJ,				// ί��ʱ��(�ƻ�ת��ʱ��,CZBZ=1ʱ��Ч)
	TDX_ID_ZJMM,				// �ʽ�����
	TDX_ID_ZCZJZH,				// ת���ʽ��ʺ�(���ŷָ����˺��б�,�ձ�ʾ�����˺���ָ���˺Ź鼯)
	TDX_ID_ZRZJZH,				// ת���ʽ��ʺ�(ת����˺�,�ձ�ʾת�����˺�)
};

// �ʽ��ʺż�ת�� 134
const WORD tdxZJZHJZZFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_ZCZJZH,				// ת���ʽ��ʺ�
	TDX_ID_ZRZJZH,				// ת���ʽ��ʺ�
	TDX_ID_BZ,					// ����
	TDX_ID_YZZZ_ZZJE,			// ת�ʽ��
	TDX_ID_ZJMM,				// �ʽ�����(ת���ʽ��ʺ�)

	TDX_ID_CZBZ,				// ������־(1--�ƻ�ת��,����--ʵʱת��)
	TDX_ID_WTRQ,				// ί������(�ƻ�ת������,CZBZ=1ʱ��Ч)
	TDX_ID_WTSJ,				// ί��ʱ��(�ƻ�ת��ʱ��,CZBZ=1ʱ��Ч)
};

// �ύ�ʾ��� 136
const WORD tdxTJWJJGFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_LX,					// ����(0--�����������)
	TDX_ID_RETINFO,				// ������Ϣ(�����ύ�ͻ��ʾ���,����֮���Էֺ�";"�ָ�)
	TDX_ID_CZBZ,				// ������־(0--�����ύ,1--ȡ���ύ�ʾ�[��̨����Ĭ�ϴ���])
	TDX_ID_XT_FUNCTIONVERSION,	// ���ܰ汾	
};

// ��ȡ�ʾ����� 138
const WORD tdxHQWJNRFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_LX,					// ����(0--�����������)
	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_XT_FUNCTIONVERSION,	// ���ܰ汾
};

// ��ȡ�ʺ�״̬��־ 140
const WORD tdxHQZHZTBZFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_LX,					// ����(0--�����������)
	TDX_ID_CZBZ,				// ������־(����)
	TDX_ID_XXLX,				// ��Ϣ����
};

// �����ѯ���� 142
const WORD tdxCLCXMMFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_CZBZ,				// ������־(0--ͣ��,1--����,2--�޸�)
	TDX_ID_ZJMM,				// �ʽ�����(��ѯ����,CZBZ=2��Ч)
	TDX_ID_XZJMM,				// ���ʽ�����(�²�ѯ����,CZBZ=1/2��Ч)
};

// ����ע�� 144
const WORD tdxTSZCFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// (����)�ʽ��ʺ�
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
};

// ����ע�� 146
const WORD tdxTSZXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// (����)�ʽ��ʺ�
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
};

// ���ʺŲ�ѯ 148
const WORD tdxZZHCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// (����)�ʽ��ʺ�
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
};

// ������֤��Ϣ 150
const WORD tdxCLRZXXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_CZBZ,				// ������־(0--ͣ��,1--����,2--�޸�,3--������,4--������,5--��ʱ���,6--����)
	TDX_ID_XT_AUTH_MODE,		// ��֤ģʽ(ȡֵ��"��ȫ������")
	TDX_ID_XT_AUTH_INFO,		// ��֤��Ϣ
	TDX_ID_XT_AUTH_NEWINFO,		// ��֤����Ϣ
	TDX_ID_XT_MACHINEINFO,		// ������Ϣ
	TDX_ID_XT_PARAM,			// ����(����������,���ӿ�����Լ��)
	TDX_ID_XT_MOBILECHECKCODE,	// �ֻ�У����
	TDX_ID_XT_CN,				// CN
	TDX_ID_XT_SN,				// SN
	TDX_ID_XT_DN,				// DN
	TDX_ID_XT_SLOTID,			// ֤������ID
	TDX_ID_XT_CID,				// ֤�鳧��ID
};

// ��֤��Ϣ��ѯ 152
const WORD tdxRZXXCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_AUTH_MODE,		// ��ȫ������֤��ʽ
	TDX_ID_MOBILEPHONE,			// �ֻ�����
};

// �ͻ�������Ϣ��ѯ 154
const WORD tdxKHJBXXCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_ZJLB,				// ֤�����
	TDX_ID_ZJHM,				// ֤������
};

// ���Ӻ�ͬǩԼ 156
const WORD tdxDZHTQYFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_LX,					// ����(���Ӻ�ͬ����,���ӿ�/ȯ�����ж���)
	TDX_ID_CZBZ,				// ������־(0--ǩԼ,1--ȡ��,����--����)
	TDX_ID_ZQDM,				// ֤ȯ����
	TDX_ID_XT_PARAM,			// ����(���ӿ��Զ���)
	TDX_ID_XT_CHECKRISKFLAG,	// �����ձ�־
	TDX_ID_KFSJJ_JYJE,			// ���׽��(�ʽ������)
	TDX_ID_DZDJSFS,				// ���ʵ����ͷ�ʽ( 1--����,2--�ʼ�,3--��������)
};

// ���Ӻ�ͬǩԼ��ѯ 158
const WORD tdxDZHTQYCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_LX,					// ����(-1/255--ȫ��,����--ָ������)
	TDX_ID_ZQDM,				// ֤ȯ����(��--ȫ��,����--ָ��֤ȯ����)
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

// ���Ӻ�ͬ�б��ѯ 160
const WORD tdxDZHTLBCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_ZQDM,				// ֤ȯ����(��--ȫ��,����--ָ��֤ȯ����)
	TDX_ID_CZBZ,				// ������־(0--ȫ��,����--��ȯ���Զ���)
};

// ���Ӻ�ͬ��Ϣ��ѯ 162
const WORD tdxDZHTXXCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_LX,					// ����(����ָ������)
	TDX_ID_ZQDM,				// ֤ȯ����
};

// ��֤��ˮ��ѯ 164
const WORD tdxRZLSCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_AUTH_MODE,		// ��ȫ������֤��ʽ((-1)--ȫ��)
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// �ͻ�Ԥ����Ϣ��ѯ 166
const WORD tdxKHYLXXCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
};

// �ͻ�Ԥ����Ϣ�޸� 168
const WORD tdxKHYLXXXGFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_CZBZ,				// ������־(0/(-1)--ֱ��ִ��,����--δ����)
	TDX_ID_ZDDM,				// �ֶδ���
	TDX_ID_ZDQZ,				// �ֶ�ȡֵ
};

// �ͻ�����ȷ�� 170
const WORD tdxKHCZQRFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_CZBZ,				// ������־(��TDX_ID_XT_NEEDCONFIRMFLAGS�ֶζ������,1--�˵�ȷ��,����--δ����)
	TDX_ID_XT_MESSAGETITLE,		// ��Ϣ����
	TDX_ID_XT_MESSAGECONTENT,	// ��Ϣ����
	TDX_ID_XXLX,				// ��Ϣ����
	TDX_ID_KHMC,				// �ͻ�����
	TDX_ID_XT_CHECKRISKFLAG,	// �����ձ�־
};

// �����ֵ��ѯ 172
const WORD tdxFYZDCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_XT_MODE,				// ģʽ(�ֵ�����)
	TDX_ID_XT_PARAM,			// ����(�ֵ��־)
};

const WORD tdxFYZDCXFieldAns[]=
{
	TDX_ID_XT_MODE,				// ģʽ(�ֵ�����)
	TDX_ID_XT_PARAM,			// ����(�ֵ��־)
	TDX_ID_XT_DESCRIPTION,		// ����(�ֵ�����)
	TDX_ID_XT_REMARK,			// ��ע(�ֵ䱸ע)
	TDX_ID_XT_DISPLAYCOLOR,		// ��ʾ��ɫ

	TDX_ID_XT_RESERVED,			// ������Ϣ
};

// ���»Ự��Ϣ 174
const WORD tdxUPDATESESSIONFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_SESSION,			// �Ự��Ϣ
	TDX_ID_XT_MODE,				// ģʽ
	TDX_ID_XT_PARAM,			// ����
	TDX_ID_XT_DESCRIPTION,		// ����
};

const WORD tdxUPDATESESSIONFieldAns[]=
{
	TDX_ID_XT_SESSION,			// �Ự��Ϣ
	TDX_ID_XT_MODE,				// ģʽ
	TDX_ID_XT_PARAM,			// ����
	TDX_ID_XT_DESCRIPTION,		// ����
	TDX_ID_RETINFO,				// ������Ϣ

	TDX_ID_XT_RESERVED,			// ������Ϣ
};

// �ʾ���ˮ��ѯ 176
const WORD tdxWJLSCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_LX,					// ����
};

// ��ȡ�г���Ϣ 178
const WORD tdxSCINFOFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_ZQDM,				// ֤ȯ����
};

//////////////////////////////////////////////////////////////////////////
//	ί��������
//////////////////////////////////////////////////////////////////////////

// ί�г��� 200
const WORD tdxWTCDFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_SCFLAG,				// �г�����(����,��Ҫ��TDX_ID_ZHLB)
	TDX_ID_ZQDM,				// ֤ȯ����
	TDX_ID_CZBZ,				// (����)������־
	TDX_ID_WTBH,				// ί�б��(Ϊ�ճ�ȫ��ί��)

	TDX_ID_HYDM,				// (����,�ڻ�)��Լ����
	TDX_ID_CDSL,				// (�ڻ�)��������
	TDX_ID_XWDM,				// ϯλ����
	TDX_ID_XTZXH,				// (�ڻ�)ϵͳ���ĺ�

	TDX_ID_WTRQ,				// ί������

	TDX_ID_MMBZ,				// ������־(0-�޼����� 1-�޼����� 'C'-�м����� ...)
	TDX_ID_TBBZ,				// (�ڻ�)Ͷ����־
	TDX_ID_KPBZ,				// (�ڻ�)��ƽ��־
	TDX_ID_WTSL,				// (�ڻ�)ί������
	TDX_ID_WTJG,				// (�ڻ�)ί�м۸�

	TDX_ID_HTBH,				// ��ͬ���
	TDX_ID_ZJMM,				// �ʽ�����(�۹�--���������µ�����)
	TDX_ID_WTSJ,				// ί��ʱ��
	TDX_ID_CJSJ,				// �ɽ�ʱ��
	TDX_ID_XT_PARAM,			// ����(�ӿ�Լ��,�ͻ��˴�"������ѯ"/"����ί�в�ѯ"ȡ��,ԭ���ͻ�)
	TDX_ID_CJSX,				// �ɽ�����(�ͻ��˴�"������ѯ"/"����ί�в�ѯ"ȡ��,ԭ���ͻ�)
};

// ��ͨ��Ʊί�� 202
const WORD tdxPTGPWTFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_MMBZ,				// ������־(0-�޼����� 1-�޼����� 'C'-�м����� ...)
	TDX_ID_TXMM,				// (����)ͨѶ����
	TDX_ID_SCFLAG,				// (����)�г���־
	TDX_ID_ZQDM,				// ֤ȯ����
	TDX_ID_WTJG,				// ί�м۸�
	TDX_ID_JYDW,				// ���׵�λ
	TDX_ID_WTSL,				// ί������
	TDX_ID_WTFS,				// ί�з�ʽ(��������־���)

	TDX_ID_BZ,					// (��ѡ,Ԥί��)����
	TDX_ID_WTJE,				// (��ѡ,Ԥί��)ί�н��
	TDX_ID_WTRQ,				// (��ѡ,Ԥί��)ί������(YYYYMMDD)
	TDX_ID_WTSJ,				// (��ѡ,Ԥί��)ί��ʱ��(HHMMSS)
	TDX_ID_WTBH,				// (����)ί�б��
	TDX_ID_PCH,					// ���κ�(֧��ʱ��)
	TDX_ID_XWDM,				// ϯλ����(֧��ʱ��)

	TDX_ID_HYDM,				// (����,�ڻ�)��Լ����
	TDX_ID_KPBZ,				// (�ڻ�)��ƽ��־
	TDX_ID_TBBZ,				// (�ڻ�)Ͷ����־

	TDX_ID_XT_CHECKRISKFLAG,	// �����ձ�־

	TDX_ID_FCJL,				// �ֲֻ���
	TDX_ID_ZJMM,				// �ʽ�����(�۹�--���������µ�����)

	TDX_ID_YDXH,				// Լ�����
	TDX_ID_DFXWDM,				// �Է�ϯλ����
	TDX_ID_DFZJZH,				// �Է��ʽ��ʺ�
	TDX_ID_DFGDDM,				// �Է��ɶ�����
	TDX_ID_DFZHLB,				// �Է��ʺ����

	TDX_ID_CJSX,				// (�ڻ�)�ɽ�����
	TDX_ID_CFJG,				// (�ڻ�)�����۸�
	TDX_ID_DFFZDM,				// �Է���֧����
	TDX_ID_DFKHDM,				// �Է��ͻ�����
	TDX_ID_DFMM,				// �Է�����
	TDX_ID_TJRDM,				// �Ƽ��˴���
	TDX_ID_XT_TOKEN,			// ����
	TDX_ID_LXRXM,				// ��ϵ������
	TDX_ID_LXFS,				// ��ϵ��ʽ
};

// ծȯת�ɻ��� 204
const WORD tdxZQZGHSFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_MMBZ,				// ������־(0-ת�� 1-����)
	TDX_ID_ZQDM,				// ֤ȯ����
	TDX_ID_WTSL,				// ί������
	TDX_ID_WTJG,				// ί�м۸�
};

// �޸Ķ��� 206
const WORD tdxXGDDFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_WTBH,				// ί�б��(ԭ�������)
	TDX_ID_MMBZ,				// ������־(0-���� 1-���� ...)
	TDX_ID_ZQDM,				// ֤ȯ����
	TDX_ID_WTJG,				// ί�м۸�
	TDX_ID_JYDW,				// ���׵�λ
	TDX_ID_WTSL,				// ί������
	TDX_ID_WTFS,				// ί�з�ʽ(��������־���)

	TDX_ID_BZ,					// (��ѡ,Ԥί��)����
	TDX_ID_WTJE,				// (��ѡ,Ԥί��)ί�н��
	TDX_ID_WTRQ,				// (��ѡ,Ԥί��)ί������(YYYYMMDD)
	TDX_ID_WTSJ,				// (��ѡ,Ԥί��)ί��ʱ��(HHMMSS)
	TDX_ID_PCH,					// ���κ�(֧��ʱ��)
	TDX_ID_XWDM,				// ϯλ����(֧��ʱ��)

	TDX_ID_KPBZ,				// (�ڻ�)��ƽ��־
	TDX_ID_TBBZ,				// (�ڻ�)Ͷ����־

	TDX_ID_YWTSL,				// ԭί������
	TDX_ID_YWTJG,				// ԭί�м۸�
	TDX_ID_HTBH,				// ��ͬ���
	TDX_ID_ZJMM,				// �ʽ�����(�۹�--���������µ�����)
	TDX_ID_WCJSL,				// δ�ɽ�����
	TDX_ID_XT_PARAM,			// ����(�ӿ�Լ��,�ͻ��˴�"������ѯ"/"����ί�в�ѯ"ȡ��,ԭ���ͻ�)
	TDX_ID_CJSX,				// �ɽ�����
	TDX_ID_XT_TOKEN,			// ����
};

// �깺�¹� 208
const WORD tdxSGXGFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_MMBZ,				// ������־(�깺����)
	TDX_ID_ZQDM,				// ֤ȯ����
	TDX_ID_WTSL,				// ί������(�깺����)
	TDX_ID_RZJE,				// ���ʽ��
	TDX_ID_RZBL,				// ���ʱ���
	TDX_ID_SXF,					// ������(�깺����)
	TDX_ID_LX,					// ����(��������)
};

// �¹��깺�޸� 210
const WORD tdxXGSGXGFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_MMBZ,				// ������־(�깺����)
	TDX_ID_ZQDM,				// ֤ȯ����
	TDX_ID_WTSL,				// ί������(�깺����)
	TDX_ID_RZJE,				// ���ʽ��
	TDX_ID_RZBL,				// ���ʱ���
	TDX_ID_SXF,					// ������(�깺����)
	TDX_ID_LX,					// ����(��������)
	TDX_ID_WTBH,				// ί�б��
};

// �¹��깺���� 212
const WORD tdxXGSGCDFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_MMBZ,				// ������־(�깺����)
	TDX_ID_ZQDM,				// ֤ȯ����
	TDX_ID_WTSL,				// ί������(�깺����)
	TDX_ID_RZJE,				// ���ʽ��
	TDX_ID_RZBL,				// ���ʱ���
	TDX_ID_SXF,					// ������(�깺����)
	TDX_ID_LX,					// ����(��������)
	TDX_ID_WTBH,				// ί�б��
};

// ����ί�� 214
const WORD tdxPLWTFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_MMBZ,				// ������־
	TDX_ID_WTFS,				// ί�����
	TDX_ID_ZQDM,				// ֤ȯ����
	TDX_ID_WTJG,				// ί�м۸�
	TDX_ID_WTSL,				// ί������
	TDX_ID_WTCS,				// ί�д���
	TDX_ID_XWDM,				// ϯλ����(֧��ʱ��)
	TDX_ID_XT_CHECKRISKFLAG,	// �����ձ�־
};

// �������� 216
const WORD tdxPLCDFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_ZQDM,				// ֤ȯ����
	TDX_ID_PCH,					// ���κ�
	TDX_ID_XWDM,				// ϯλ����
	TDX_ID_WTRQ,				// ί������
};

// ����������� 218
const WORD tdxXZDDJCFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_MMBZ,				// ������־(0-�޼����� 1-�޼����� 'C'-�м����� ...)
	TDX_ID_TXMM,				// (����)ͨѶ����
	TDX_ID_SCFLAG,				// (����)�г���־
	TDX_ID_ZQDM,				// ֤ȯ����
	TDX_ID_WTJG,				// ί�м۸�
	TDX_ID_JYDW,				// ���׵�λ
	TDX_ID_WTSL,				// ί������
	TDX_ID_WTFS,				// ί�з�ʽ(��������־���)

	TDX_ID_BZ,					// (��ѡ,Ԥί��)����
	TDX_ID_WTJE,				// (��ѡ,Ԥί��)ί�н��
	TDX_ID_WTRQ,				// (��ѡ,Ԥί��)ί������(YYYYMMDD)
	TDX_ID_WTSJ,				// (��ѡ,Ԥί��)ί��ʱ��(HHMMSS)
	TDX_ID_WTBH,				// (����)ί�б��
	TDX_ID_PCH,					// ���κ�(֧��ʱ��)
	TDX_ID_XWDM,				// ϯλ����(֧��ʱ��)

	TDX_ID_HYDM,				// (����,�ڻ�)��Լ����
	TDX_ID_KPBZ,				// (�ڻ�)��ƽ��־
	TDX_ID_TBBZ,				// (�ڻ�)Ͷ����־

	TDX_ID_XT_CHECKRISKFLAG,	// �����ձ�־

	TDX_ID_FCJL,				// �ֲֻ���
	TDX_ID_ZJMM,				// �ʽ�����(�۹�--���������µ�����)

	TDX_ID_YDXH,				// Լ�����
	TDX_ID_DFXWDM,				// �Է�ϯλ����
	TDX_ID_DFZJZH,				// �Է��ʽ��ʺ�
	TDX_ID_DFGDDM,				// �Է��ɶ�����
	TDX_ID_DFZHLB,				// �Է��ʺ����

	TDX_ID_CJSX,				// (�ڻ�)�ɽ�����
	TDX_ID_CFJG,				// (�ڻ�)�����۸�
	TDX_ID_DFFZDM,				// �Է���֧����
	TDX_ID_DFKHDM,				// �Է��ͻ�����
	TDX_ID_DFMM,				// �Է�����
};

// �޸Ķ������ 220
const WORD tdxXGDDJCFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_WTBH,				// ί�б��(ԭ�������)
	TDX_ID_MMBZ,				// ������־(0-���� 1-���� ...)
	TDX_ID_ZQDM,				// ֤ȯ����
	TDX_ID_WTJG,				// ί�м۸�
	TDX_ID_JYDW,				// ���׵�λ
	TDX_ID_WTSL,				// ί������
	TDX_ID_WTFS,				// ί�з�ʽ(��������־���)

	TDX_ID_BZ,					// (��ѡ,Ԥί��)����
	TDX_ID_WTJE,				// (��ѡ,Ԥί��)ί�н��
	TDX_ID_WTRQ,				// (��ѡ,Ԥί��)ί������(YYYYMMDD)
	TDX_ID_WTSJ,				// (��ѡ,Ԥί��)ί��ʱ��(HHMMSS)
	TDX_ID_PCH,					// ���κ�(֧��ʱ��)
	TDX_ID_XWDM,				// ϯλ����(֧��ʱ��)

	TDX_ID_KPBZ,				// (�ڻ�)��ƽ��־
	TDX_ID_TBBZ,				// (�ڻ�)Ͷ����־

	TDX_ID_YWTSL,				// ԭί������
	TDX_ID_YWTJG,				// ԭί�м۸�
	TDX_ID_HTBH,				// ��ͬ���
	TDX_ID_ZJMM,				// �ʽ�����(�۹�--���������µ�����)
	TDX_ID_WCJSL,				// δ�ɽ�����
	TDX_ID_XT_PARAM,			// ����(�ӿ�Լ��,�ͻ��˴�"������ѯ"/"����ί�в�ѯ"ȡ��,ԭ���ͻ�)
	TDX_ID_CJSX,				// �ɽ�����
};

// �������ʽ��ѯ 250
const WORD tdxSDSZJCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
	
	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_CZBZ,				// ������־
};

// �����ֹɷݲ�ѯ 252
const WORD tdxSDSGFCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
	
	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ������ί�в�ѯ 254
const WORD tdxSDSWTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
	
	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// �����ֳɽ���ѯ 256
const WORD tdxSDSCJCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
	
	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_LSH,					// ��ˮ��(����������ѯ)
	TDX_ID_CZBZ,				// ������־
};

// ��������ˮ��ѯ 258
const WORD tdxSDSLSCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
	
	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_LSH,					// ��ˮ��(����������ѯ)
	TDX_ID_CZBZ,				// ������־
	TDX_ID_BZ,					// ����
};

// �����������ʲ���ѯ 260
const WORD tdxSDSXYZCCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ������֤ȯ��Ϣ��ѯ 262
const WORD tdxSDSZQXXCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_ZQDM,				// ֤ȯ����
	TDX_ID_MMBZ,				// ������־
	TDX_ID_WTFS,				// ί�����
	TDX_ID_CZBZ,				// ������־
};

// �����ֿ���(��)������ѯ 264
const WORD tdxSDSKMSLCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_ZQDM,				// ֤ȯ����
	TDX_ID_MMBZ,				// ������־
	TDX_ID_WTFS,				// ί�����
	TDX_ID_WTJG,				// ί�м۸�
	TDX_ID_CZBZ,				// ������־
};

// ������ǩ 300 (����)
const WORD tdxFQZQFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
	
	TDX_ID_SCFLAG,				// �г�����
	TDX_ID_ZQDM,				// ֤ȯ����
	TDX_ID_ZQSL,				// ֤ȯ����
};

// (����)�ͻ����ϲ�ѯ 302
const WORD tdxFWKHZLCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���(�����ʺ�)
	TDX_ID_JYMM,				// ��������(����)
	TDX_ID_ZJZH,				// �ʽ��ʺ�(����)
	TDX_ID_ZHLB,				// �ʺ����("�ͻ���"���ʺŵ�����)
	TDX_ID_GDDM,				// �ɶ�����(����)
	TDX_ID_OP_WTFS,				// ������ʽ(Ϊ�յ�ʱ��ʹ��"�ͻ�������"��ֵ����)

	TDX_ID_XT_CLITYPE,			// �ͻ�������("������ʽ"Ϊ�յ�ʱ��ʹ��)
};

// (����)��ȡ��̬���� 304
const WORD tdxFWHQDTKLFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_LX,					// ����(0--Ĭ��,1--��ȡ��̬����,2--��ȡ�ͻ�Ȩ��,3--��ȡ�ֻ���֤��)
	TDX_ID_CZBZ,				// ������־(�������ֲ�ͬ����)
	TDX_ID_XT_PARAM,			// ����(����Я����ز���)
	TDX_ID_XT_AUTH_MODE,		// ��֤ģʽ(�������ֲ�ͬ����)
};

// (����)��Ʒ����Ʒ�� 306
const WORD tdxFWCPDGPZFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_CPDM,				// ��Ʒ����
};

// (����)��Ʒ������ѯ 308
const WORD tdxFWCPDGCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_CPDM,				// ��Ʒ����
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

// (����)��Ʒ�������� 310
const WORD tdxFWCPDGSZFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_CPDM,				// ��Ʒ����
	TDX_ID_XT_PARAM,			// ����(����Я����ز���)
	TDX_ID_KHMC,				// �ͻ�����
	TDX_ID_ZJHM,				// ֤������
	TDX_ID_USEREMAIL,			// �û�Email
	TDX_ID_USERPHONE,			// ��ϵ�绰
	TDX_ID_MOBILEPHONE,			// �ƶ��绰
	TDX_ID_FAX,					// ����绰
	TDX_ID_USERADDRESS,			// ͨѶ��ַ
	TDX_ID_POSTALCODE,			// ��������
	TDX_ID_PROVINCE,			// ʡ��
	TDX_ID_CITY,				// ����
	TDX_ID_SECTION,				// Ͻ��
	TDX_ID_ZJLB,				// ֤�����
	TDX_ID_XT_AUTH_MODE,		// ��֤ģʽ
	TDX_ID_XT_AUTH_INFO,		// ��֤��Ϣ
};

// (����)��Ʒ�����޸� 312
const WORD tdxFWCPDGXGFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_CPDM,				// ��Ʒ����
	TDX_ID_XT_PARAM,			// ����(����Я����ز���)
	TDX_ID_LSH,					// ��ˮ��
	TDX_ID_KHMC,				// �ͻ�����
	TDX_ID_ZJHM,				// ֤������
	TDX_ID_USEREMAIL,			// �û�Email
	TDX_ID_USERPHONE,			// ��ϵ�绰
	TDX_ID_MOBILEPHONE,			// �ƶ��绰
	TDX_ID_FAX,					// ����绰
	TDX_ID_USERADDRESS,			// ͨѶ��ַ
	TDX_ID_POSTALCODE,			// ��������
	TDX_ID_PROVINCE,			// ʡ��
	TDX_ID_CITY,				// ����
	TDX_ID_SECTION,				// Ͻ��
	TDX_ID_ZJLB,				// ֤�����
	TDX_ID_XT_AUTH_MODE,		// ��֤ģʽ
	TDX_ID_XT_AUTH_INFO,		// ��֤��Ϣ
};

// (����)��Ʒ����ȡ�� 314
const WORD tdxFWCPDGQXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_CPDM,				// ��Ʒ����
	TDX_ID_LSH,					// ��ˮ��
	TDX_ID_CZBZ,				// ������־(0--��ͨ,1--չ��,Ĭ��--0)
};

// (����)�ʽ���ˮ 316
const WORD tdxFWZJLSFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

const WORD tdxFWZJLSFieldAns[]=
{
	TDX_ID_ZJLS_FSRQ,			// ��������
	TDX_ID_ZJLS_FSSJ,			// ����ʱ��
	TDX_ID_ZJLS_YWDM,			// ҵ�����
	TDX_ID_ZJLS_YWMC,			// ҵ������
	TDX_ID_ZJLS_HBDM,			// ���Ҵ���
	TDX_ID_ZJLS_FSJE,			// �������
	TDX_ID_ZJLS_SYJE,			// ʣ����
	TDX_ID_ZJLS_ZQDM,			// ֤ȯ����
	TDX_ID_ZJLS_ZQMC,			// ֤ȯ����
	TDX_ID_ZJLS_FSJG,			// �����۸�
	TDX_ID_ZJLS_FSSL,			// ��������
	TDX_ID_ZJLS_SYSL,			// ʣ������
	TDX_ID_ZJLS_GDDM,			// �ɶ�����
};

// (����)���������ѯ 318
const WORD tdxFWPLHQCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_SCFLAG,				// ����������
	TDX_ID_ZQDM,				// ֤ȯ����(���֤ȯ����,Ĭ���ɶ���","�ָ�)
	TDX_ID_XT_PARAM,			// ����(ָ���ָ���,�ǿ�ʱ��һ���ֽ���Ч,�������Ĭ�Ϸָ���)
	TDX_ID_XT_MODE,				// ģʽ(ָ���������,"֤ȯ����"Ϊ��ʱ��Ч)
};

// (����)��Ѷ��Ŀ��ѯ 320
const WORD tdxFWZXLMCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// (����)��ȡ��ʾ��Ϣ 322
const WORD tdxFWHQTSXXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_XXLX,				// ��Ϣ����(���ŷָ��Ķ����Ҫ���ص���Ϣ����)
	TDX_ID_XT_PARAM,			// ����(�ͻ��˺ͽӿ�Լ������ز���)
};

// (����)ͶƱ������ѯ 324
const WORD tdxFWTPFACXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_TPDM,				// ͶƱ����(��--��ȫ��)
	TDX_ID_FADM,				// ��������(��--��ȫ��)
	TDX_ID_ZQDM,				// ֤ȯ����(��--��ȫ��)
};

// (����)ͶƱ��Ϣ��ѯ 326
const WORD tdxFWTPXXCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_TPDM,				// ͶƱ����(����)
	TDX_ID_FADM,				// ��������(����)

};

// (����)ͶƱ����ύ 328
const WORD tdxFWTPJGTJFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_TPDM,				// ͶƱ����
	TDX_ID_FADM,				// ��������
	TDX_ID_TPJG,				// ͶƱ���(1--ͬ��,2--����,3--��Ȩ)
	TDX_ID_XT_PARAM,			// ����(�Ƿ���ڹ�ϵ,0--���ڹ�ϵ,2--�����ڹ�ϵ)
	TDX_ID_FALX,				// ��������(0--ͶƱ,1--ѡ��)
	TDX_ID_WTSL,				// ͶƱ����
};

// (����)ͶƱ�����ѯ 330
const WORD tdxFWTPJGCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_TPDM,				// ͶƱ����(��--��ȫ��)
	TDX_ID_FADM,				// ��������(��--��ȫ��)
	TDX_ID_ZQDM,				// ֤ȯ����(��--��ȫ��)
};

// (����)ͶƱͳ�Ʋ�ѯ 332
const WORD tdxFWTPTJCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_TPDM,				// ͶƱ����(��--��ȫ��)
	TDX_ID_FADM,				// ��������(��--��ȫ��)
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_XT_PARAM,			// ����(�Ƿ���ڹ�ϵ,0--���ڹ�ϵ,2--�����ڹ�ϵ)
	TDX_ID_ZQDM,				// ֤ȯ����(��--��ȫ��)
};

// (����)������ϴ����ѯ 334
const WORD tdxFWTLZHDMCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// (����)������ϳɷֲ�ѯ 336
const WORD tdxFWTLZHCFCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_ZSDM,				// ָ������
};

// (����)�����¼���� 338
const WORD tdxFWDDDLCZFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_CZBZ,				// ������־(0--��ȡ����,1--У������)
	TDX_ID_XT_TOKEN,			// ����
};

// (����)�����ּ۲�ѯ 340
const WORD tdxFWPLXJCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_SCFLAG,				// ����������
	TDX_ID_ZQDM,				// ֤ȯ����(���֤ȯ����,Ĭ���ɶ���","�ָ�)
	TDX_ID_XT_PARAM,			// ����(ָ���ָ���,�ǿ�ʱ��һ���ֽ���Ч,�������Ĭ�Ϸָ���)
	TDX_ID_XT_MODE,				// ģʽ(ָ���������,"֤ȯ����"Ϊ��ʱ��Ч)
};

// (����)��Ϣ���� 342
const WORD tdxFWXXDYFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_CZBZ,				// ������־(Ĭ��--0)
	TDX_ID_LX,					// ����(Ĭ��--0)
	TDX_ID_XT_PARAM,			// ����(Ĭ��--��)
};

// (����)�ͻ������� 344
const WORD tdxFWKHKCLFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_CZBZ,				// ������־(0--��ѯ,1--��ʧ)
	TDX_ID_XT_PARAM,			// ����(Ĭ��--��)
};

// (����)�ϴ�������Ϣ 346
const WORD tdxFWSCPZXXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_MODE,				// ģʽ(��������)
	TDX_ID_XT_PARAM,			// ����(������Ϣ)
	TDX_ID_XT_DESCRIPTION,		// ����(��������)
	TDX_ID_XT_REMARK,			// ��ע(���÷���)
	TDX_ID_XT_INPUTPARAM,		// �������
};

// (����)����������Ϣ 348
const WORD tdxFWXZPZXXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_XT_MODE,				// ģʽ(��������,�ձ�ʾȫ��)
	TDX_ID_XT_REMARK,			// ��ע(���÷���)
	TDX_ID_XT_INPUTPARAM,		// �������
};

// (����)������ϢժҪ��ѯ 350
const WORD tdxFWPZXXZYCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_MODE,				// ģʽ(��������,�ձ�ʾȫ��)
	TDX_ID_XT_REMARK,			// ��ע(���÷���)
	TDX_ID_XT_INPUTPARAM,		// �������
};

// (����)����ͻ����� 352
const WORD tdxFWCLKHCSFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_LX,					// ����(1--�ɱ�������;...)
	TDX_ID_CZBZ,				// ������־(0--��ѯ;1--Ԥ�ύ;2--�ύ)
	TDX_ID_RETINFO,				// �ύ��ѡ��(�ж���ʱ,���ŷָ�)
};

// (����)����б��ѯ 354
const WORD tdxFWPDLBCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// (����)�����ˮ¼�� 356
const WORD tdxFWPDLSLRFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_JCRQ,				// ��������
	TDX_ID_PDDM1,				// ��Դ���1
	TDX_ID_PDMC1,				// �������1
	TDX_ID_JCJG1,				// ���ּ۸�1
	TDX_ID_JCSL1,				// ��������1
	TDX_ID_JCBH1,				// ���ֱ��1
	TDX_ID_PDDM2,				// ��Դ���2
	TDX_ID_PDMC2,				// �������2
	TDX_ID_JCJG2,				// ���ּ۸�2
	TDX_ID_JCSL2,				// ��������2
	TDX_ID_JCBH2,				// ���ֱ��2
};

// (����)�����ˮ��ѯ 358
const WORD tdxFWPDLSCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

// (����)��ֵҵ���շ� 360
const WORD tdxFWZZYWSFFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_CZBZ,				// ������־(1--�µ�,2--�ĵ�,3--����)
	TDX_ID_WTBH,				// ί�б��(�ĵ�/����ʹ��)
	TDX_ID_YWDM,				// ҵ�����(�ͻ���/�ӿ�--����Լ���շ�����)
	TDX_ID_BZ,					// ����
	TDX_ID_JYDW,				// ���׵�λ
	TDX_ID_WTSL,				// ί������
	TDX_ID_WTJG,				// ί�м۸�
	TDX_ID_WTJE,				// ί�н��
	TDX_ID_YZZZ_YHDM,			// ���д���
	TDX_ID_YZZZ_YHZH,			// �����˺�
	TDX_ID_YZZZ_YHMM,			// ��������
	TDX_ID_XT_REMARK,			// ��ע
};

//////////////////////////////////////////////////////////////////////////

// (����)ǿ���˳� 400 [���͹���,����ʹ��]
const WORD tdxQZTCFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
};

// (����)ǿ���˳� 401

// (����)��Ϣ֪ͨ 402 [���͹���,����ʹ��]
const WORD tdxXXTZFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
};

// (����)��Ϣ֪ͨ 403

// (����)������Ϣ 404 [���͹���,����ʹ��]
const WORD tdxGGXXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
};

// (����)������Ϣ 405

// (�ֻ�)֤ȯ��ѯ 500
const WORD tdxMOBILEZQCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_ZQDM,				// ֤ȯ����
	TDX_ID_WTJG,				// ί�м۸�
	TDX_ID_MMBZ,				// ������־
	TDX_ID_WTFS,				// ί�����
	TDX_ID_CZBZ,				// ������־
	TDX_ID_XT_CHECKRISKFLAG,	// �����ձ�־
	TDX_ID_SBMRJ,				// �걨�����(CZBZ=2ʱ��Ч)
	TDX_ID_SBMCJ,				// �걨������(CZBZ=2ʱ��Ч)
	TDX_ID_TBBZ,				// Ͷ����־

	TDX_ID_DFFZDM,				// �Է���֧����
	TDX_ID_DFKHDM,				// �Է��ͻ�����
	TDX_ID_DFMM,				// �Է�����
	TDX_ID_DFXWDM,				// �Է�ϯλ����
	TDX_ID_DFZJZH,				// �Է��ʽ��ʺ�
	TDX_ID_DFGDDM,				// �Է��ɶ�����
	TDX_ID_DFZHLB,				// �Է��ʺ����
	TDX_ID_XT_FUNCTIONVERSION,	// ���ܰ汾
};

// (�ֻ�)�ɷݲ�ѯ 502
const WORD tdxMOBILEGFCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����
};

// (�ֻ�)�ʽ��ѯ 504
const WORD tdxMOBILEZJCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����
};

// (�ֻ�)������ѯ 506
const WORD tdxMOBILECDCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����
};

// (�ֻ�)ί�в�ѯ 508
const WORD tdxMOBILEWTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����
};

// (�ֻ�)�ɽ���ѯ 510
const WORD tdxMOBILECJCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����
};

// (�ֻ�)ת�˲�ѯ 512
const WORD tdxMOBILEZZCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_YZZZ_YHDM,			// ���д���
};

// (�ֻ�)��ˮ��ѯ 514
const WORD tdxMOBILELSCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

// (�ֻ�)�����ѯ 516
const WORD tdxMOBILEJGCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

// (�ֻ�)���˲�ѯ 518
const WORD tdxMOBILEDZCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

// (�ֻ�)�����걨�����ѯ 520
const WORD tdxMOBILEYXSBHQCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����

	TDX_ID_MMBZ,				// ������־
	TDX_ID_WTFS,				// ί�����
	TDX_ID_ZQDM,				// ֤ȯ����
};

// (�ֻ�)��ʷί�в�ѯ 522
const WORD tdxMOBILELSWTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

// (�ֻ�)��ʷ�ɽ���ѯ 524
const WORD tdxMOBILELSCJCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_CZBZ,				// ������־
};

// (�ֻ�)�����ǩ��ѯ 526
const WORD tdxMOBILEPHZQCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

// (�ֻ�)��֤��ˮ��ѯ 528
const WORD tdxMOBILERZLSCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_XT_AUTH_MODE,		// ��ȫ������֤��ʽ((-1)--ȫ��)
};

// (�ֻ�)���𳷵���ѯ 530
const WORD tdxMOBILEJJCDCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����
};

// (�ֻ�)������ί�в�ѯ 532
const WORD tdxMOBILEJJDRWTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����
};

// (�ֻ�)������ʷί�в�ѯ 534
const WORD tdxMOBILEJJLSWTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����

	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

// (�ֻ�)�����ճɽ���ѯ 536
const WORD tdxMOBILEJJDRCJCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����
};

// (�ֻ�)������ʷ�ɽ���ѯ 538
const WORD tdxMOBILEJJLSCJCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����

	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

// (�ֻ�)�����˺Ų�ѯ 540
const WORD tdxMOBILEJJZHCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����
};

// (�ֻ�)����˾��ѯ 542
const WORD tdxMOBILEJJGSCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����
};

// (�ֻ�)��������ѯ 544
const WORD tdxMOBILEJJDMCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����
};

// (�ֻ�)����ݶ��ѯ 546
const WORD tdxMOBILEJJFECXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����
};

// (�ֻ�)������˲�ѯ 548
const WORD tdxMOBILEJJDZCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����

	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

// (�ֻ�)���𽻸��ѯ 550
const WORD tdxMOBILEJJJGCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����

	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

// (�ֻ�)����ǽ���ί�в�ѯ 552
const WORD tdxMOBILEJJFJYWTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����

	TDX_ID_KSRQ,				// ��ѯ��ʼ����
	TDX_ID_ZZRQ,				// ��ѯ��������
	TDX_ID_LX,					// (0������ 1����ʷ)
};

// (�ֻ�)�ڻ���Լ��ѯ 560
const WORD tdxMOBILEQHHYCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����

	TDX_ID_CZBZ,				// ������־(0--��ѯȫ����Լ,1--��ѯָ���г��Ŀ��ú�Լ,Ĭ��--0)
	TDX_ID_SCFLAG,				// �г�����(CZBZ=1ʱ��Ч)
};

// (�ֻ�)�ڻ���Ϻ�Լ��ѯ 562
const WORD tdxMOBILEQHZHHYCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����
};

// (�ֻ�)�ڻ���ϳֲֲ�ѯ 564
const WORD tdxMOBILEQHZHCCCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����
};

// (�ֻ�)�ڻ����ί�в�ѯ 566
const WORD tdxMOBILEQHZHWTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����
};

// (�ֻ�)�ڻ���ϲ��Բ�ѯ 568
const WORD tdxMOBILEQHZHCLCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����

	TDX_ID_CLDM,				// ���Դ���
	TDX_ID_ZHLX,				// �������
};

// (�ֻ�)�ɷݻ��ܲ�ѯ 570
const WORD tdxMOBILEGFHZCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����
};

// (�ֻ�)ί�л��ܲ�ѯ 572
const WORD tdxMOBILEWTHZCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����
};

// (�ֻ�)�ɽ����ܲ�ѯ 574
const WORD tdxMOBILECJHZCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����
};

// (�ֻ�)�ɽ���ϸ��ѯ 576
const WORD tdxMOBILECJMXCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����
};

// (�ֻ�)���������������ײ�ѯ 600
const WORD tdxMOBILEXYRZMRPTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����
};

// (�ֻ�)������ȯ�������ײ�ѯ 602
const WORD tdxMOBILEXYRQMCPTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����
};

// (�ֻ�)���������������ײ�ѯ 604
const WORD tdxMOBILEXYMCHKPTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����
};

// (�ֻ�)�������뻹ȯ���ײ�ѯ 606
const WORD tdxMOBILEXYMRHQPTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����
};

// (�ֻ�)�����ֽ𻹿����ײ�ѯ 608
const WORD tdxMOBILEXYXJHKPTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����
};

// (�ֻ�)������ȯ��ȯ���ײ�ѯ 610
const WORD tdxMOBILEXYXQHQPTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����
};

// (�ֻ�)������ȯ��ת���ײ�ѯ 612
const WORD tdxMOBILEXYYQHZPTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����
};

// (�ֻ�)���õ�����ת���ײ�ѯ 614
const WORD tdxMOBILEXYDBHZPTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����

	TDX_ID_WTFS,				// ί�����(����/����)
	TDX_ID_DFFZDM,				// �Է���֧����
	TDX_ID_DFKHDM,				// �Է��ͻ�����
	TDX_ID_DFMM,				// �Է�����
};

// (�ֻ�)���õ���ת�����ײ�ѯ 616
const WORD tdxMOBILEXYDBZRPTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����

	TDX_ID_DFFZDM,				// �Է���֧����
	TDX_ID_DFKHDM,				// �Է��ͻ�����
	TDX_ID_DFMM,				// �Է�����
};

// (�ֻ�)���õ���ת�����ײ�ѯ 618
const WORD tdxMOBILEXYDBZCPTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����
};

// (�ֻ�)�����ʲ���Ϣ��ѯ 620
const WORD tdxMOBILEXYZCXXCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����
};

// (�ֻ�)���ùɷ���Ϣ��ѯ 622
const WORD tdxMOBILEXYGFXXCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����
};

// (�ֻ�)���ñ��֤ȯ��ѯ 624
const WORD tdxMOBILEXYBDZQCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����

	TDX_ID_MMBZ,				// ������־
	TDX_ID_WTFS,				// ί�����
	TDX_ID_ZQDM,				// ֤ȯ����
};

// (�ֻ�)����ֱ�ӻ�ת��ѯ 626
const WORD tdxMOBILEXYZJHZCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����

	TDX_ID_KSRQ,				// ��ѯ��ʼ����
	TDX_ID_ZZRQ,				// ��ѯ��ֹ����
};

// (�ֻ�)������Ϣ���ò�ѯ 628
const WORD tdxMOBILEXYLXFYCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����
};

// (�ֻ�)����δƽ��Լ��ѯ 630
const WORD tdxMOBILEXYWPHYCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����

	TDX_ID_KSRQ,				// ��ѯ��ʼ����
	TDX_ID_ZZRQ,				// ��ѯ��ֹ����
	TDX_ID_CZBZ,				// ������־(0--ȫ��,1--����,2--��ȯ,Ĭ��--0)
};

// (�ֻ�)������ƽ��Լ��ѯ 632
const WORD tdxMOBILEXYYPHYCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����

	TDX_ID_KSRQ,				// ��ѯ��ʼ����
	TDX_ID_ZZRQ,				// ��ѯ��ֹ����
	TDX_ID_CZBZ,				// ������־(0--ȫ��,1--����,2--��ȯ,Ĭ��--0)
};

// (�ֻ�)���õ��պ�Լ��ѯ 634
const WORD tdxMOBILEXYDRHYCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����
};

// (�ֻ�)�������ʺ�Լ��ѯ 636
const WORD tdxMOBILEXYRZHYCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����

	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_CZBZ,				// ������־(0--ȫ��,1--δ�˽�,2--���˽�,Ĭ��--0)
};

// (�ֻ�)������ȯ��Լ��ѯ 638
const WORD tdxMOBILEXYRQHYCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����

	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_CZBZ,				// ������־(0--ȫ��,1--δ�˽�,2--���˽�,Ĭ��--0)
};

// (�ֻ�)�����ʽ�ծ��ѯ 640
const WORD tdxMOBILEXYZJFZCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����

	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

// (�ֻ�)���ùɷݸ�ծ��ѯ 642
const WORD tdxMOBILEXYGFFZCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����

	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

// (�ֻ�)���ý��׵���Ʒ֤ȯ��ѯ 644
const WORD tdxMOBILEXYJYDBPZQCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����
	
	TDX_ID_ZQDM,				// ֤ȯ����
};

// (�ֻ�)���ý��׷ǽ��׻�ת��ѯ 646
const WORD tdxMOBILEXYJYFJYHZCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����

	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

// (�ֻ�)���ý��׸�ծ��ˮ��ѯ 648
const WORD tdxMOBILEXYJYFZLSCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����

	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};
//////////////////////////////////////////////////////////////////////////

// (�ֻ�)ETFί�в�ѯ 700
const WORD tdxMOBILEETFWTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����

	TDX_ID_CZBZ,				// ������־(0--������ί��,1--��ɳ���ί��,Ĭ��--0)
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_ZSDM,				// ָ������
	TDX_ID_PCH,					// ���κ�(0--�����м�¼,����--���Ӧ��¼)
};

// (�ֻ�)ETF�ɽ���ѯ 702
const WORD tdxMOBILEETFCJCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����

	TDX_ID_WTRQ,				// ί������
	TDX_ID_ZSDM,				// ָ������
	TDX_ID_PCH,					// ���κ�
};

//////////////////////////////////////////////////////////////////////////

// (�ֻ�)��Ʋ�Ʒ�ݶ��ѯ 750
const WORD tdxMOBILELCCPFECXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����

	TDX_ID_CZBZ,				// ������־
};

// (�ֻ�)��Ʋ�Ʒί�в�ѯ 752
const WORD tdxMOBILELCCPWTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����

	TDX_ID_CZBZ,				// ������־
	TDX_ID_LX,					// (0������ 1����ʷ)
};

// (�ֻ�)��Ʋ�Ʒ�ɽ���ѯ 754
const WORD tdxMOBILELCCPCJCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����

	TDX_ID_CZBZ,				// ������־
};

// (�ֻ�)��Ʋ�Ʒ�����ѯ 756
const WORD tdxMOBILELCCPDMCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����

	TDX_ID_CZBZ,				// ������־
};

// (�ֻ�)��Ʋ�Ʒ���ڶ����깺��ѯ 758
const WORD tdxMOBILELCCPDQDESGCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����
};

// (�ֻ�)������Ʋ�Ʒ�����ѯ 790
const WORD tdxMOBILEYHLCCPDMCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����

	TDX_ID_CZBZ,				// ������־
};

// (�ֻ�)������Ʋ�Ʒ�ݶ��ѯ 792
const WORD tdxMOBILEYHLCCPFECXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����

	TDX_ID_CZBZ,				// ������־
};

// (�ֻ�)������Ʋ�Ʒί�в�ѯ 794
const WORD tdxMOBILEYHLCCPWTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����

	TDX_ID_CZBZ,				// ������־
};

// (�ֻ�)������Ʋ�Ʒ�ɽ���ѯ 796
const WORD tdxMOBILEYHLCCPCJCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����

	TDX_ID_XT_POSITIONSTRING,	// ��λ�ִ�
	TDX_ID_XT_BEGINLINE,		// ��ʼ�к�
	TDX_ID_XT_REQUESTLINE,		// ��������
	TDX_ID_XT_TOTALLINE,		// �ܹ�����

	TDX_ID_CZBZ,				// ������־
};

//////////////////////////////////////////////////////////////////////////
//	��ȫ������
//////////////////////////////////////////////////////////////////////////

// CA�˻����� 800
const WORD tdxCAZHSQFieldReq[]=
{
	TDX_ID_CA_KHH,				// 800 �����ͻ���
	TDX_ID_CA_KHMC,				// 801 �ͻ�����
	TDX_ID_CA_TXMM,				// 803 ��֤����
	TDX_ID_CA_ZSXH,				// 805 ֤�����(�ͻ�������)
	TDX_ID_CA_AQJB,				// 806 ����İ�ȫ����(���: 1,SLL 2,��֤���� 4,����֤��,8Ӳ��OTP,64 �ֻ�OTP)
	TDX_ID_CA_SEEDINFO,			// 4221 ������Ϣ
	TDX_ID_CA_OTPSN,			// 4222 OTPSN���
	TDX_ID_CA_CID,				// 4220 ������ȫ����ID(�䷢/��֤)
};
const WORD tdxCAZHSQFieldAns[]=
{
	TDX_ID_CA_TXMM,				// 803 ��֤����
	TDX_ID_CA_ZSXH,				// 805 ֤�����
	TDX_ID_CA_AQJB,				// 806 ��ȫ����
	TDX_ID_CA_YHFJ,				// 807 �û��ּ�
	TDX_ID_CA_YHJBMS,			// 808 �û���������
	TDX_ID_CA_YHQX,				// 809 �û�Ȩ��(ASCII�ַ���)
	TDX_ID_CA_ZSSHBZ,			// 811 ֤����˱�־(0,�Ѿ�ͨ����� 1,���ڵȴ����)
	TDX_ID_CA_ZSXZBZ,			// 812 ֤�����ر�־(0,��ǰ����δЯ������ 1,��ǰ����Я����֤������)
	TDX_ID_CA_ZSQSID,			// 813 ֤���ȯ��ID
	TDX_ID_CA_ZSBFJG,			// 814 ֤��䷢����
	TDX_ID_CA_ZSBFYH,			// 815 ֤��䷢�û�
	TDX_ID_CA_ZSQSRQ,			// 816 ֤����ʼ����
	TDX_ID_CA_ZSJZRQ,			// 817 ֤���ֹ����
	TDX_ID_CA_ZSWS,				// 818 ֤��λ��
	TDX_ID_CA_ZSGY,				// 819 ֤�鹫Կ
};

// CA�ʺŲ�ѯ 802
const WORD tdxCAZHCXFieldReq[]=
{
	TDX_ID_CA_KHH,				// �����ͻ���
};
const WORD tdxCAZHCXFieldAns[]=
{
	TDX_ID_CA_AQJB,				// ��ǰ����İ�ȫ����
	TDX_ID_CA_ZSSHBZ,			// ֤����˱�־
};

// CA�˻�У�� 804
const WORD tdxCAZHJYFieldReq[]=
{
	TDX_ID_CA_KHH,				// �����ͻ���
	TDX_ID_CA_KHMC,				// �ͻ�����
	TDX_ID_CA_AQJB,				// ��¼��ȫ����
	TDX_ID_CA_TXMM,				// ��֤����(���ʹ����֤���ʽ)
	TDX_ID_CA_ZSGY,				// ֤�鹫Կ(���ʹ������֤�鷽ʽ)
	TDX_ID_CA_ISVIPHOST,		// VIP��վ��ʶ
	TDX_ID_CA_NEWIP,			// ���ε�½IP
	TDX_ID_CA_JQTZM,			// ����������
	TDX_ID_CA_SJH,				// �ͻ��ֻ���
};
const WORD tdxCAZHJYFieldAns[]=
{
	TDX_ID_CA_SQBZ,				// �����־(0:�Ѿ����� 1:δ����,������������)
	TDX_ID_CA_AQJB,				// ��ȫ����(�������־Ϊ0,Ϊ�û���ǰ��ȫ���� �������־Ϊ1:Ϊ������֧�ֵ���Ͱ�ȫ����)
	TDX_ID_CA_YHFJ,				// �û��ּ�
	TDX_ID_CA_YHJBMS,			// �û���������
	TDX_ID_CA_YHQX,				// �û�Ȩ��
	TDX_ID_CA_ZSSHBZ,			// ֤����˱�־
	TDX_ID_CA_KJYBZ,			// �ɽ��ױ�־(0:���ɽ���,ֻ�ɽ��а�ȫ���� 1:����������)
	TDX_ID_CA_ZSXZBZ,			// ֤�����ر�־(0:��֤�����ݸ��� 1:����֤�鸽��,��Ҫ����ȷ��)
	TDX_ID_CA_ZSQSID,			// ֤���ȯ��ID
	TDX_ID_CA_ZSBFJG,			// ֤��䷢����
	TDX_ID_CA_ZSBFYH,			// ֤��䷢�û�
	TDX_ID_CA_ZSQSRQ,			// ֤����ʼ����(YYYYMMDD)
	TDX_ID_CA_ZSJZRQ,			// ֤���ֹ����(YYYYMMDD)
	TDX_ID_CA_ZSWS,				// ֤��λ��
	TDX_ID_CA_ZSGY,				// ֤�鹫Կ
	IDX_ID_CA_ZSKGXBZ,			// ֤��ɸ��±�־(0:���ɸ��� 1:֤��ɸ���)
	TDX_ID_CA_ZSJYGXBZ,			// ֤�齨����±�־(0:����Ҫ�����û����� 1:�����û���������)
	TDX_ID_CA_ZSSYYXTS,			// ֤��ʣ����Ч����(>=0)
	TDX_ID_CA_XGTXMMBZ,			// ��֤����ǿ���޸ı�־
	TDX_ID_CA_L2USER,			// LEVEL2�˺�
	TDX_ID_CA_L2PASS,			// LEVEL2����
	TDX_ID_CA_ISDLWZTS,			// �Ƿ�֧�ֵ�½λ����ʾ
	TDX_ID_CA_ISMMBHWT,			// �Ƿ�֧�����뱣������
	TDX_ID_CA_ISJQTZMBD,		// �Ƿ�֧�ֻ����������
	TDX_ID_CA_ISYLWT,			// �Ƿ�֧��Ԥ������
	TDX_ID_CA_YLWT,				// Ԥ������
	TDX_ID_CA_LASTIP,			// �ϴε�½IP

	TDX_ID_CA_LASPROV,			// �ϴε�½ʡ��
	TDX_ID_CA_NEWPROV,			// ���ε�½ʡ��
	TDX_ID_CA_LASSITE,			// �ϴε�½λ��
	TDX_ID_CA_NEWSITE,			// ���ε�½λ��
	TDX_ID_CA_DLSJ,				// ��½ʱ��
	
	TDX_ID_CA_BINDNUM,			// �Ѱ󶨻��������������̨��
	TDX_ID_CA_MAC,				// ����MAC��ַ
	TDX_ID_CA_MACHINENAME,		// �ϴε�½�����ǳ�
};

// CA��֤�����޸� 806
const WORD tdxCATXMMXGFieldReq[]=
{
	TDX_ID_CA_KHH,				// �����ͻ���
	TDX_ID_CA_TXMM,				// ��֤����
	TDX_ID_CA_XTXMM,			// ����֤����
	TDX_ID_CA_RESETFLAG,		// ���ñ�־
};
const WORD tdxCATXMMXGFieldAns[]=
{
	TDX_ID_CA_RESV,				// (����)�����ֶ�
};

// CA��֤�����ѯ 808
const WORD tdxCATXMMCXFieldReq[]=
{
	TDX_ID_CA_KHH,				// �����ͻ���
};
const WORD tdxCATXMMCXFieldAns[]=
{
	TDX_ID_CA_TXMM,				// ��֤����
	TDX_ID_CA_RESV,				// (����)�����ֶ�
};

// CA֤������ 810
const WORD tdxCAZSXZFieldReq[]=
{
	TDX_ID_CA_KHH,				// �����ͻ���
	TDX_ID_CA_ZSXH,				// ֤�����
};
const WORD tdxCAZSXZFieldAns[]=
{
	TDX_ID_CA_AQJB,				// ��ȫ����
	TDX_ID_CA_ZSSHBZ,			// ֤����˱�־(0:�Ѿ���� 1:���ڵȴ����)
	TDX_ID_CA_ZSXZBZ,			// ֤�����ر�־(0:������֤������ 1:����֤������)
	TDX_ID_CA_ZSQSID,			// ֤���ȯ��ID
	TDX_ID_CA_ZSBFJG,			// ֤��䷢����
	TDX_ID_CA_ZSBFYH,			// ֤��䷢�û�
	TDX_ID_CA_ZSQSRQ,			// ֤����ʼ����(YYYYMMDD)
	TDX_ID_CA_ZSJZRQ,			// ֤���ֹ����(YYYYMMDD)
	TDX_ID_CA_ZSWS,				// ֤��λ��
	TDX_ID_CA_ZSGY,				// ֤�鹫Կ
};

// CA֤������ȷ�� 812
const WORD tdxCAZSXZQRFieldReq[]=
{
	TDX_ID_CA_KHH,				// �����ͻ���
};
const WORD tdxCAZSXZQRFieldAns[]=
{
	TDX_ID_CA_RESV,				// (����)�����ֶ�
};

// CA�˻�״̬�޸� 814
const WORD tdxCAZTXGFieldReq[]=
{	TDX_ID_CA_KHH,				// �����ͻ���
	TDX_ID_CA_CZJG,				// �����ṹ
	TDX_ID_CA_CZY,				// ����Ա
	TDX_ID_CA_CZMM,				// ��������
	TDX_ID_CA_CZSX,				// ��������
	TDX_ID_CA_CZBZ,				// ������־
};
const WORD tdxCAZTXGFieldAns[]=
{	TDX_ID_CA_RESV,				// (����)�����ֶ�
};

// CA֤����� 816
const WORD tdxCAZSGXFieldReq[]=
{
	TDX_ID_CA_KHH,				// �����ͻ���
};
const WORD tdxCAZSGXFieldAns[]=
{
	TDX_ID_CA_AQJB,				// ��ǰ�û���ȫ����
	TDX_ID_CA_ZSSHBZ,			// ֤����˱�־(0,ͨ����� 1,���ڵȴ����)
	TDX_ID_CA_ZSXZBZ,			// ֤�����ر�־(0,δ����֤�� 1,������֤��)
	TDX_ID_CA_ZSQSID,			// ֤��ȯ��ID
	TDX_ID_CA_ZSBFJG,			// ֤�鷢������
	TDX_ID_CA_ZSBFYH,			// ֤��䷢�û�
	TDX_ID_CA_ZSQSRQ,			// ֤����ʼ����
	TDX_ID_CA_ZSJZRQ,			// ֤���������
	TDX_ID_CA_ZSWS,				// ֤��λ��
	TDX_ID_CA_ZSGY,				// ֤�鹫Կ
};


// �û��ּ���ѯ 818
const WORD tdxCAYHFJCXFieldReq[]=
{
	TDX_ID_CA_KHH,				// �����ͻ���
};
const WORD tdxCAYHFJCXFieldAns[]=
{
	TDX_ID_CA_YHFJ,				// �û��ּ�
	TDX_ID_CA_YHJBMS,			// �û���������
	TDX_ID_CA_YHJBZT,			// �û�����״̬
	TDX_ID_CA_YHJBBZ,			// �û�����ע
};

// �û��ּ����� 820
const WORD tdxCAYHFJSQFieldReq[]=
{
	TDX_ID_CA_KHH,				// �����ͻ���
	TDX_ID_CA_YHFJ,				// �û��ּ�
};
const WORD tdxCAYHFJSQFieldAns[]=
{	TDX_ID_CA_YHFJ,				// �û��ּ�
	TDX_ID_CA_YHJBMS,			// �û���������
	TDX_ID_CA_YHQX,				// �û�Ȩ��
};

// HTTP�û��ּ���ѯ 822
const WORD tdxCAHTTPYHFJCXFieldReq[]=
{
	TDX_ID_CA_KHH,				// �����ͻ���
};
const WORD tdxCAHTTPYHFJCXFieldAns[]=
{
	TDX_ID_CA_YHFJ,				// �û��ּ�
	TDX_ID_CA_YHJBMS,			// �û���������
	TDX_ID_CA_YHQX,				// �û�Ȩ��
};

// �����û����� 824
const WORD tdxCANMZCFieldReq[]=
{
	TDX_ID_CA_SJH,				// �ͻ���,�û��ֻ���
	TDX_ID_CA_EMAIL,			// �û�email
	TDX_ID_CA_KHMC,				// �û�����
};
const WORD tdxCANMZCFieldAns[]=
{
	TDX_ID_CA_RESV,				// �����ֶ�
};

// �½����� 826
const WORD tdxCAXJZTFieldReq[]=
{
	TDX_ID_CA_KHH,
	TDX_ID_CA_KHJL,
	TDX_ID_CA_TOPICTITLE,
	TDX_ID_CA_CONTENT,
};
const WORD tdxCAXJZTFieldAns[]=
{
	TDX_ID_CA_TOPICID,
};

// ��ѯ���� 828
const WORD tdxCACXZTFieldReq[]=
{
	TDX_ID_CA_KHH,
	TDX_ID_CA_QUERYDATE,
	TDX_ID_CA_QUERYALL,
	TDX_ID_CA_CLOSEFLAG,
};
const WORD tdxCACXZTFieldAns[]=
{
	TDX_ID_CA_TOPICID,
	TDX_ID_CA_TOPICTITLE,
	TDX_ID_CA_REMINDFLAG,
	TDX_ID_CA_NEWANSFLAG,
	TDX_ID_CA_CLOSEFLAG,
	TDX_ID_CA_KHJL,
	TDX_ID_CA_REQDATE,
	TDX_ID_CA_VALDATE,
};

// ��ѯ�ظ� 830
const WORD tdxCACXHFFieldReq[]=
{
	TDX_ID_CA_TOPICID,
};
const WORD tdxCACXHFFieldAns[]=
{
	TDX_ID_CA_ANSWERID,
	TDX_ID_CA_REQDATE,
	TDX_ID_CA_REQTIME,
	TDX_ID_CA_VALDATE,
	TDX_ID_CA_WHOANS,
	TDX_ID_CA_CONTENT,
	TDX_ID_CA_SATISFAC,
};

// �ظ����� 832
const WORD tdxCAHFZTFieldReq[]=
{
	TDX_ID_CA_TOPICID,
	TDX_ID_CA_CONTENT,
};
const WORD tdxCAHFZTFieldAns[]=
{
	TDX_ID_CA_ANSWERID,
};

// (������)�ر����� 834
const WORD tdxCAGBZTFieldReq[]=
{
	TDX_ID_CA_TOPICID,
	TDX_ID_CA_SATISFAC,
};
const WORD tdxCAGBZTFieldAns[]=
{
	TDX_ID_CA_TOPICID,
};

// �û�(����)��Ϣ 836
const WORD tdxCAYHLYFieldReq[]=
{
	TDX_ID_CA_KHH,
	TDX_ID_CA_BRANCHMSGID,
};
const WORD tdxCAYHLYFieldAns[]=
{
	TDX_ID_CA_TOPICID,
	TDX_ID_CA_TOPICTITLE,
	TDX_ID_CA_CONTENT,
	TDX_ID_CA_REQDATE,
	TDX_ID_CA_CLOSEFLAG,
};

// �����û����� 838
const WORD tdxCANMJHFieldReq[]=
{
	TDX_ID_CA_KHH,
	TDX_ID_CA_JHM,
};
const WORD tdxCANMJHFieldAns[]=
{
	TDX_ID_CA_RESV,				// �����ֶ�
};

// �����û���¼ 840
const WORD tdxCANMDLFieldReq[]=
{
	TDX_ID_CA_KHH,
	TDX_ID_CA_TXMM,
};
const WORD tdxCANMDLFieldAns[]=
{
	TDX_ID_CA_RESV,				// �����ֶ�
};

// ��ѯ�Ƿ����������� 842
const WORD tdxCANEWMSGFieldReq[]=
{
	TDX_ID_CA_KHH,
	TDX_ID_CA_BRANCHMSGID,
};
const WORD tdxCANEWMSGFieldAns[]=
{
	TDX_ID_CA_NEWMSGNUM,		// �ҵ�����:����Ϣ����
	TDX_ID_CA_NOREADMSGNUM,		// �ҵ�����:δ����Ϣ����
	TDX_ID_CA_RESV,				// �����ֶ�
};

// ���Ķ����� 844
const WORD tdxCAREADMSGFieldReq[]=
{
	TDX_ID_CA_TOPICID,			// �ҵ�����:����ID
};
const WORD tdxCAREADMSGFieldAns[]=
{
	TDX_ID_CA_RESV,				// �����ֶ�
};

// �û����漰����������Ϣ 846
const WORD tdxNOTICEINFOFieldReq[]=
{
	TDX_ID_CA_KHH,				// �ͻ���
	TDX_ID_XT_STARTPOS,			// ��ʼ���
};
const WORD tdxNOTICEINFOFieldAns[]=
{
	TDX_ID_CA_BIRTHTITIP,
	TDX_ID_CA_NOTICETITLE,
	TDX_ID_CA_NOTICECONTENT,
	TDX_ID_CA_RESV,
};

// �û���Ѷ��Ϣ���� 848
const WORD tdxINFOFEEDBACKFieldReq[]=
{
	TDX_ID_CA_KHH,				// �ͻ���
	TDX_ID_CA_MENU,				// ��Ŀ
	TDX_ID_CA_SJH,				// �ֻ���
	TDX_ID_CA_EMAIL,			// �����ʼ�
	TDX_ID_CA_CONTENT,			// ��������
	TDX_ID_CA_CZBZ,				// ������־
};
const WORD tdxINFOFEEDBACKFieldAns[]=
{
	TDX_ID_CA_RESV,
};

// TQ�ͻ�У�� 860
const WORD tdxTQKHJYFieldReq[]=
{	TDX_ID_CA_ZHLB,				// �˺����(0:�ͻ��� 1:TQ�� 2:TQ�ʼ�)
	TDX_ID_CA_KHH,				// �˺���Ϣ
};
const WORD tdxTQKHJYFieldAns[]=
{	TDX_ID_CA_ZHLB,				// �˺����
	TDX_ID_CA_KHH,				// �˺���Ϣ
	TDX_ID_CA_KHMC,				// �ͻ�����
	TDX_ID_CA_AQJB,				// ��ǰ�û���ȫ����(1:SSL�ͻ� 2:ͨѶ����ͻ� 4:֤��ͻ�)
	TDX_ID_CA_YHFJ,				// �û��ּ�
	TDX_ID_CA_YHJBMS,			// �û���������
	TDX_ID_CA_YHQX,				// �û�Ȩ��
	TDX_ID_CA_TQID,				// �û�TQ��
	TDX_ID_CA_TQMAIL,			// �û�TQ�ʼ�
};

// ����֤ȯ�û�Ͷ�ʹ�����Ϣ 862
const WORD  tdxUMUBROKERFieldReq[]=
{
	TDX_ID_CA_KHH,				// �ͻ���
	TDX_ID_CA_VER,				// Ͷ�ʹ������ϰ汾
};
const WORD   tdxUMUBROKERFieldAns[]=
{
	TDX_ID_UM_BROKERCODE,		// �����˴���
	TDX_ID_UM_BROKERBRANCH,		// ������Ӫҵ��
	TDX_ID_UM_BROKERNAME,		// ����������
	TDX_ID_UM_BROKERSTATUS,		// ������״̬
	TDX_ID_UM_BROKERLEVEL,		// �����˼���
	TDX_ID_UM_UPBROKER,			// �ϼ�������
	TDX_ID_UM_BROKERNATIONALITY,// �����˹���
	TDX_ID_UM_BROKERPHONECODE,	// �����˵绰
	TDX_ID_UM_BROKERMOPHONE,	// �������ƶ��绰
	TDX_ID_UM_BROKEREMAIL,		// �����˵����ʼ�
	TDX_ID_UM_BROKERMSN,		// ������MSN
	TDX_ID_UM_BROKERQQ,			// ������QQ
	TDX_ID_UM_BROKERSEX,		// �������Ա�
	TDX_ID_UM_BROKERAGE,		// ����������
	TDX_ID_UM_BROKERDEGREE,		// ������ѧ��	
	TDX_ID_UM_PASSEXAM,			// �Ƿ�ͨ������
	TDX_ID_UM_PRACTISETIME,		// ��ҵʱ��
	TDX_ID_UM_BROKERFAVOR,		// �����˲���ϰ��
	TDX_ID_UM_BROKERNATIVEPLACE,// �����˸�������
	TDX_ID_UM_BROKERQUAL,		// �����˴�ҵ�ʸ�
	TDX_ID_UM_BROKERSATISLEV,	// ������Ͷ�ʹ�������ȼ���
	TDX_ID_UM_BROKERPHOTOS,		// ��������Ƭ
	TDX_ID_UM_BROKERNOTES,		// �����˱�ע
	TDX_ID_UM_BRANCHNAME,		// Ӫҵ������
	TDX_ID_UM_COMHOTLINE,		// ��˾�ͻ�����
	TDX_ID_UM_BRANCHTRADEASK,	// Ӫҵ��������ѯ�绰
	TDX_ID_UM_BRANCHINVESTASK,	// Ӫҵ��Ͷ����ѯ�绰
	TDX_ID_CA_VER,				// Ͷ�ʹ������ϰ汾
	TDX_ID_CA_RESV,				// Ԥ��
};

// ����(�û�)ע�� 880
const WORD tdxCASYZCGDFieldReq[]=
{
	TDX_ID_CA_KHH,
};
const WORD tdxCASYZCGDFieldAns[]=
{
	TDX_ID_CA_RESV,
};

// (��ϸ)��Ϣ¼�� 882
const WORD tdxCAXXLRGDFieldReq[]=
{
	TDX_ID_CA_KHH,
	TDX_ID_CA_KHMC,
	TDX_ID_CA_KHXB,
	TDX_ID_CA_ZJHM,
	TDX_ID_CA_EMAIL,
};
const WORD tdxCAXXLRGDFieldAns[]=
{
	TDX_ID_CA_JHM,
};

// ����(�û�)���� 884
const WORD tdxCASYJHGDFieldReq[]=
{
	TDX_ID_CA_KHH,
	TDX_ID_CA_JHM,
};
const WORD tdxCASYJHGDFieldAns[]=
{
	TDX_ID_CA_RESV,
};

// �˻�У�� 886
const WORD tdxCAZHJYGDFieldReq[]=
{
	TDX_ID_CA_KHH,
	TDX_ID_CA_TXMM,
	TDX_ID_CA_AQJB,				// ��¼��ȫ����
	TDX_ID_CA_ZSGY,
	TDX_ID_CA_CERTSN,
	TDX_ID_CA_CZBZ,
	TDX_ID_CA_RESV,				// ����Ԥ����Ϣ
};
const WORD tdxCAZHJYGDFieldAns[]=
{
	TDX_ID_CA_KHMC,
	TDX_ID_CA_RESV,
	TDX_ID_CA_NOWLEVELNO,
	TDX_ID_CA_NOWLEVELNAME,
	TDX_ID_CA_CANLEVELNO,
	TDX_ID_CA_CANLEVELNAME,
};

// �ȼ���ѯ 888
const WORD tdxCADJCXGDFieldReq[]=
{
	TDX_ID_CA_KHH,
};
const WORD tdxCADJCXGDFieldAns[]=
{
	TDX_ID_CA_YHFJ,
	TDX_ID_CA_LEVELNAME,
	TDX_ID_CA_ZBMAX,
	TDX_ID_CA_ZBMIN,
	TDX_ID_CA_TSUPDATE,
	TDX_ID_CA_PROTOC,
	TDX_ID_CA_COMMISION,
};

// ����(��)��(��)��ѯ 890
const WORD tdxCAKSJCXGDFieldReq[]=
{
	TDX_ID_CA_KHH,
	TDX_ID_CA_DRZB,
};
const WORD tdxCAKSJCXGDFieldAns[]=
{
	TDX_ID_CA_RESV,
};

// �ͻ�����(����) 892
const WORD tdxCAKHSQGDFieldReq[]=
{
	TDX_ID_CA_KHH,
	TDX_ID_CA_AQJB,
};
const WORD tdxCAKHSQGDFieldAns[]=
{
	TDX_ID_CA_RESV,
};

// �û���ѶȨ�� 894
const WORD tdxCAYHZXQXFieldReq[]=
{
	TDX_ID_CA_KHH,
};
const WORD tdxCAYHZXQXFieldAns[]=
{
	TDX_ID_CA_MENU,			// �ɼ���Ŀ
	TDX_ID_CA_RESV,			// �����ֶ�,�����Ŀ��ʾ��ʽ
};

// �û�Ȩ��ע�� 896
const WORD tdxCAYHQXZXFieldReq[]=
{
	TDX_ID_CA_KHH,			// �����ͻ���
};
const WORD tdxCAYHQXZXFieldAns[]=
{
	TDX_ID_CA_AQJB,			// ��ǰ����İ�ȫ����
	TDX_ID_CA_ZSSHBZ,		// ֤����˱�־
};

// ��ѯ��½��ʷ 898
const WORD tdxCACXDLLSFieldReq[]=
{
	TDX_ID_CA_KHH,			// 800 �����ͻ���
 	TDX_ID_CA_QSRQ,			// 896 ��ʼ��ѯʱ��
 	TDX_ID_CA_ZZRQ,			// 897 ��ֹ��ѯʱ��
};
const WORD tdxCACXDLLSFieldAns[]=
{
	TDX_ID_CA_DLRQ,			// 899 ��½����
	TDX_ID_CA_DLSJ,			// 898 ��½ʱ��
	TDX_ID_CA_LASPROV,		// 892 ��½ʡ��
	TDX_ID_CA_LASSITE,		// 894 ��½�ص�
	TDX_ID_CA_LASTIP,		// 890 ��½IP
	TDX_ID_CA_MAC,			// 4211 ����MAC��ַ
	TDX_ID_CA_JQTZM,		// 4201 ����������
};

//////////////////////////////////////////////////////////////////////////
//	��֤ת����
//////////////////////////////////////////////////////////////////////////

// ��֤ת�� 900
const WORD tdxYZZZFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
	
	TDX_ID_ZJMM,				// �ʽ�����
	TDX_ID_YZZZ_ZZFX,			// ת�ʷ���(0-ת��,1-ת��)
	TDX_ID_YZZZ_YHDM,			// ���д���
	TDX_ID_YZZZ_YHMM,			// ��������
	TDX_ID_YZZZ_ZZJE,			// ת�ʽ��

	TDX_ID_YZZZ_YHZH,			// (��ѡ)�����ʺ�(���"������Ϣ"���ܷ����˾���)
	TDX_ID_BZ,					// (��ѡ)����(���"������Ϣ"���ܷ����˾���)

	TDX_ID_ZZFS,				// ת�ʷ�ʽ(�۹�ת��)
	TDX_ID_ZZQD,				// ת������(�۹�ת��)
	TDX_ID_ZZBH,				// ת�ʱ��(�۹�ת��)
	TDX_ID_FPYH,				// ��Ʊ����(�۹�ת��)
	TDX_ID_ZPBH,				// ֧Ʊ���(�۹�ת��)

	TDX_ID_CZBZ,				// ������־(0--ʵʱת��,1--�ƻ�ת��,2--����ת���ж�����,3--����ת��ִ������)
	TDX_ID_WTRQ,				// ί������(�ƻ�ת������,CZBZ=1ʱ��Ч)
	TDX_ID_WTSJ,				// ί��ʱ��(�ƻ�ת��ʱ��,CZBZ=1ʱ��Ч)

	TDX_ID_ZJYHDM,				// �м����д���(�۹�ת��)
	TDX_ID_ZJYHMC,				// �м���������(�۹�ת��)
	TDX_ID_ZJYHZH,				// �м������ʺ�(�۹�ת��)
	TDX_ID_ZJYHZHMC,			// �м������ʺ�����(�۹�ת��)
	TDX_ID_XT_PARAM,			// ����(����ת����ز���,CZBZ=3ʱ��Ч)

	TDX_ID_ZRZJZH,				// ת���ʽ��ʺ�
	TDX_ID_ZRYHDM,				// ת�����д���
	TDX_ID_ZRYHZH,				// ת�������ʺ�
	TDX_ID_ZCZJZH,				// ת���ʽ��ʺ�
	TDX_ID_ZCYHDM,				// ת�����д���
	TDX_ID_ZCYHZH,				// ת�������ʺ�
};

// ������ˮ 902
const WORD tdxYHLSFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
	
	TDX_ID_YZZZ_YHDM,			// ���д���
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_BZ,					// (��ѡ)����,�Ϳղ�ȫ������
	TDX_ID_YZZZ_YHZH,			// (��ѡ)�����ʺ�(���"������Ϣ"���ܷ����˾���)
};

// ������� 904
const WORD tdxYHYEFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
	
	TDX_ID_ZJMM,				// �ʽ�����
	TDX_ID_YZZZ_YHDM,			// ���д���
	TDX_ID_YZZZ_YHMM,			// ��������

	TDX_ID_YZZZ_YHZH,			// (��ѡ)�����ʺ�(���"������Ϣ"���ܷ����˾���)
	TDX_ID_BZ,					// ����
	TDX_ID_CZBZ,				// ������־(0-������,1-ȡ���)
	TDX_ID_YZZZ_YHLSH,			// ������ˮ��(TDX_ID_CZBZ==1ʱ,���ڲ�ѯ���)
};

// �޸��������� 906
const WORD tdxXGYHMMFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
	
	TDX_ID_YZZZ_YHDM,			// ���д���
	TDX_ID_YZZZ_YHMM,			// ��������
	TDX_ID_YZZZ_XYHMM,			// ����������

	TDX_ID_BZ,					// (����)����
	TDX_ID_YZZZ_YHZH,			// �����ʺ�(���"������Ϣ"���ܷ����˾���)
};

// ������Ϣ 908
const WORD tdxYHXXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
};

// �������ת�� 910
const WORD tdxSFCGZZFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
	
	TDX_ID_ZJMM,				// �ʽ�����
	TDX_ID_YZZZ_ZZFX,			// ת�ʷ���(0-ת��,1-ת��)
	TDX_ID_YZZZ_YHMM,			// ��������
	TDX_ID_YZZZ_ZZJE,			// ת�ʽ��
};

// ����ת�ʲ�ѯ 912
const WORD tdxSFZZCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
	
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ��������ѯ 914
const WORD tdxSFYECXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
	
	TDX_ID_ZJMM,				// �ʽ�����
	TDX_ID_YZZZ_YHMM,			// ��������
	TDX_ID_BZ,					// ����
};

// ת���޸� 916
const WORD tdxZZXGFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
	
	TDX_ID_ZJMM,				// �ʽ�����
	TDX_ID_YZZZ_ZZFX,			// ת�ʷ���(0-ת��,1-ת��)
	TDX_ID_YZZZ_YHDM,			// ���д���
	TDX_ID_YZZZ_YHMM,			// ��������
	TDX_ID_YZZZ_ZZJE,			// ת�ʽ��

	TDX_ID_YZZZ_YHZH,			// (��ѡ)�����ʺ�(���"������Ϣ"���ܷ����˾���)
	TDX_ID_BZ,					// (��ѡ)����(���"������Ϣ"���ܷ����˾���)

	TDX_ID_ZZFS,				// ת�ʷ�ʽ(�۹�ת��)
	TDX_ID_ZZQD,				// ת������(�۹�ת��)
	TDX_ID_ZZBH,				// ת�ʱ��(�۹�ת��)
	TDX_ID_FPYH,				// ��Ʊ����(�۹�ת��)
	TDX_ID_ZPBH,				// ֧Ʊ���(�۹�ת��)

	TDX_ID_YZZZ_YHLSH,			// ������ˮ��

	TDX_ID_ZJYHDM,				// �м����д���(�۹�ת��)
	TDX_ID_ZJYHMC,				// �м���������(�۹�ת��)
	TDX_ID_ZJYHZH,				// �м������ʺ�(�۹�ת��)
	TDX_ID_ZJYHZHMC,			// �м������ʺ�����(�۹�ת��)
	TDX_ID_WTRQ,				// ί������
	TDX_ID_WTSJ,				// ί��ʱ��

	TDX_ID_CZBZ,				// ������־(��"��֤ת�� 900"������ͬ)
	TDX_ID_ZRZJZH,				// ת���ʽ��ʺ�
	TDX_ID_ZRYHDM,				// ת�����д���
	TDX_ID_ZRYHZH,				// ת�������ʺ�
	TDX_ID_ZCZJZH,				// ת���ʽ��ʺ�
	TDX_ID_ZCYHDM,				// ת�����д���
	TDX_ID_ZCYHZH,				// ת�������ʺ�
};

// ת��ȡ�� 918
const WORD tdxZZQXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_YZZZ_YHLSH,			// ������ˮ��
	TDX_ID_CZBZ,				// ������־(��"��֤ת�� 900"������ͬ)
	TDX_ID_YZZZ_YHDM,			// ���д���
	TDX_ID_YZZZ_YHZH,			// �����˺�
	TDX_ID_YZZZ_ZZFX,			// ת�˷���
	TDX_ID_YZZZ_ZZJE,			// ת�˽��
	TDX_ID_BZ,					// ����
	TDX_ID_WTRQ,				// ί������
	TDX_ID_WTSJ,				// ί�н��
};

// ��ȡ�ʽ��ѯ 920
const WORD tdxKQZJCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_BZ,					// ����
};

// ת�����в�ѯ 922
const WORD tdxZZYHCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�������Ҫʱ��,�����Ϳ�,��--ȫ��)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_BZ,					// ����(��ѯָ������,�ӿ�ʵ�ֿ��ܺ���,255(-1)--ȫ��)
	TDX_ID_YZZZ_YHDM,			// ���д���(��ѯָ��������Ϣ,��--ȫ��)
	TDX_ID_YZZZ_ZZFX,			// ת�ʷ���(0--ת��,1--ת��,255(-1)--ȫ��)
	TDX_ID_ZZFS,				// ת�ʷ�ʽ(�۹�ת��,�ӿ�ʵ�ֿ��ܺ���,��--ȫ��)
	TDX_ID_ZZQD,				// ת������(�۹�ת��,�ӿ�ʵ�ֿ��ܺ���,��--ȫ��)
	TDX_ID_CZBZ,				// ������־

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// �����˻���ת�� 924
const WORD tdxYHZHJZZFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�������Ҫʱ��,�����Ϳ�,��--ȫ��)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_CZBZ,				// ������־(1--�ƻ�ת��,����--ʵʱת��)
	TDX_ID_WTRQ,				// ί������(�ƻ�ת������,CZBZ=1ʱ��Ч)
	TDX_ID_WTSJ,				// ί��ʱ��(�ƻ�ת��ʱ��,CZBZ=1ʱ��Ч)
	TDX_ID_BZ,					// ����
	TDX_ID_YZZZ_ZZJE,			// ת�ʽ��
	TDX_ID_ZRYHDM,				// ת�����д���
	TDX_ID_ZCYHDM,				// ת�����д���
	TDX_ID_ZRYHZH,				// ת�������ʺ�
	TDX_ID_ZCYHZH,				// ת�������ʺ�
};

// Զ���ʽ�ת�� 926
const WORD tdxYDZJZZFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_BZ,					// ����
	TDX_ID_YZZZ_ZZFX,			// ת�ʷ���(0-ת��,1-ת��)
	TDX_ID_YZZZ_ZZJE,			// ת�ʽ��
};

// Զ��ת�ʲ�ѯ 928
const WORD tdxYDZZCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// Զ���ʽ��ѯ 930
const WORD tdxYDZJCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// Զ�˿�ת��ѯ 932
const WORD tdxYDKZCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_BZ,					// ����
	TDX_ID_YZZZ_ZZFX,			// ת�˷���
};

// ���п��б��ѯ 934
const WORD tdxYHKLBCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_ZJLB,				// ֤�����
	TDX_ID_ZJHM,				// ֤������
	TDX_ID_KHMC,				// �ͻ�����
};

// ���п���Ϣ��ѯ 936
const WORD tdxYHKXXCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_YZZZ_YHDM,			// ���д���
	TDX_ID_YZZZ_YHMC,			// ��������
	TDX_ID_YHQC,				// ����ȫ��
	TDX_ID_YHKH,				// ���п���
	TDX_ID_ZJLB,				// ֤�����
	TDX_ID_ZJHM,				// ֤������
	TDX_ID_KHMC,				// �ͻ�����
};

// ���п���Ϣ�޸� 938
const WORD tdxYHKXXXGFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_YZZZ_YHDM,			// ���д���
	TDX_ID_YZZZ_YHMC,			// ��������
	TDX_ID_YHQC,				// ����ȫ��
	TDX_ID_YHKH,				// ���п���
	TDX_ID_ZJLB,				// ֤�����
	TDX_ID_ZJHM,				// ֤������
	TDX_ID_KHMC,				// �ͻ�����
	TDX_ID_PROVINCE,			// ʡ��
	TDX_ID_CITY,				// ����
};

// ���п�������� 940
const WORD tdxYHKBGCZFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_CZBZ,				// ������־(0--��Ȩ,1--����,2--ɾ��,3--����,����--δ����)
	TDX_ID_YZZZ_YHDM,			// ���д���
	TDX_ID_YZZZ_YHMC,			// ��������
	TDX_ID_YHQC,				// ����ȫ��
	TDX_ID_YHKH,				// ���п���
	TDX_ID_ZJLB,				// ֤�����
	TDX_ID_ZJHM,				// ֤������
	TDX_ID_KHMC,				// �ͻ�����
	TDX_ID_PROVINCE,			// ʡ��
	TDX_ID_CITY,				// ����
	TDX_ID_SECTION,				// Ͻ��
	TDX_ID_DZDBZ,				// ���˵���־
	TDX_ID_DZDJSFS				// ���ʵ����ͷ�ʽ
};

// ���п����ʲ�ѯ 942
const WORD tdxYHKFLCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_YZZZ_YHDM,			// ���д���
	TDX_ID_YZZZ_YHMC,			// ��������
	TDX_ID_YHQC,				// ����ȫ��
	TDX_ID_YHKH,				// ���п���
	TDX_ID_ZJLB,				// ֤�����
	TDX_ID_ZJHM,				// ֤������
	TDX_ID_KHMC,				// �ͻ�����
};

// �˺ż�ת����ˮ��ѯ 944
const WORD tdxZHJZZLSCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

// �˺ż�ת�˵�����ˮ��ѯ 946
const WORD tdxZHJZZDRLSCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ���������ˮ��ѯ 948
const WORD tdxYHYELSCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_YZZZ_YHDM,			// ���д���
	TDX_ID_BZ,					// ����
};

// �ƻ�ת����ˮ��ѯ 950
const WORD tdxJHZZLSCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_YZZZ_YHDM,			// ���д���
	TDX_ID_BZ,					// ����
};

// ����������ˮ��ѯ 952
const WORD tdxDCGYHLSCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
	
	TDX_ID_YZZZ_YHDM,			// ���д���
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_BZ,					// (��ѡ)����,�Ϳղ�ȫ������
	TDX_ID_YZZZ_YHZH,			// (��ѡ)�����ʺ�(���"������Ϣ"���ܷ����˾���)
};

// �����˺�ͬ�� 954
const WORD tdxDCGZHTBFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_CZBZ,				// ������־(1--ͬ���ʽ�����,2--ͬ���˺���Ϣ)
};

// ����ҵ����� 990
const WORD tdxHHYWCZFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_CZBZ,				// ������־(ż��--��Ϣ��ѯ,����--ҵ�����,���"��ʶ�ֶ�ͳ��")
	TDX_ID_XT_PARAM,			// ����(���ڴ�������ѯ���ݲ�����"ҵ�����")
	TDX_ID_ZJMM,				// �ʽ�����
	TDX_ID_YZZZ_YHDM,			// ���д���
	TDX_ID_YZZZ_YHMM,			// ��������
	TDX_ID_YZZZ_ZZJE,			// ת�˽��(������)
	TDX_ID_BZ,					// ����(��������)
	TDX_ID_DFBZ,				// �Է�����(�������)
	TDX_ID_DQHL,				// ��ǰ����
};

// �������в�ѯ 992
const WORD tdxHHYHCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_YZZZ_YHDM,			// ���д���
};

// ������ʲ�ѯ 994
const WORD tdxHHHLCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_YZZZ_YHDM,			// ���д���
	TDX_ID_BZ,					// ����(��������)
	TDX_ID_DFBZ,				// �Է�����(�������)
};

// ����ί�в�ѯ 996
const WORD tdxHHWTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

////////////////////////////////////////////////////////////////////////////
//��־�鿴��
////////////////////////////////////////////////////////////////////////////

// (��־)�ͻ�У�� 100
const WORD tdxRZKHJYFieldReq[]=
{
	TDX_ID_KHH,				// �ͻ���
	TDX_ID_JYMM,			// �ͻ�����	
};

// (��־)ȡ������Ϣ 112
const WORD tdxRZCACHEFieldReq[]=
{
	TDX_ID_KHH,				// �ͻ���
	TDX_ID_JYMM,			// �ͻ�����	
};

// (��־)�ɶ���ѯ 1122
const WORD tdxRZGDCXFieldReq[]=
{
	TDX_ID_KHH,				// �ͻ���
	TDX_ID_JYMM,			// �ͻ�����	
};

// (��־)������Ϣ 908
const WORD tdxRZYHXXFieldReq[]=
{
	TDX_ID_KHH,				// �ͻ���
	TDX_ID_JYMM,			// �ͻ�����	
};

// (��־)�޸����� 106
const WORD tdxRZXGMMFieldReq[]=
{
	TDX_ID_KHH,						// �����˺�
	TDX_ID_JYMM,					// �˺�����
	TDX_ID_XJYMM,					// ���˺�����
};

// �ͻ�������¼��ѯ 1002
const WORD tdxRZKHCZJLCXFieldReq[]=
{
	TDX_ID_RZ_STARTTIME,			// ��ѯ��ʼʱ��
	TDX_ID_RZ_ENDTIME,				// ��ѯ����ʱ��
	TDX_ID_RZ_TCTIME,				// ��ѯ��������ʱ��
	TDX_ID_RZ_APITIME,				// ��ѯAPIʱ��
	TDX_ID_RZ_QUEUETIME,			// ��ѯ�Ŷ�ʱ��
	TDX_ID_RZ_FUNCID,				// �������ܺ�
	TDX_ID_KHH,						// �ͻ���
	TDX_ID_XT_BRANCHID,				// ��ʵӪҵ��
	TDX_ID_XT_STARTPOS,				// ��ʼ���
	TDX_ID_ZJZH,					// �ʽ��˺�
	TDX_ID_RETINFO,					// ������Ϣ
	TDX_ID_RZ_PAGEINDEX,			// ҳ�����
	TDX_ID_RZ_CXFLAG,				// ��ѯ���
	TDX_ID_RZ_DAY,					// ��ѯ����
};
const WORD tdxRZKHCZJLCXFieldAns[]=
{
	TDX_ID_RZ_LOGID,				// ��־��¼���
	TDX_ID_RZ_TCIP,					// ��������IP
	TDX_ID_RZ_LOGTIME,				// ��־��¼ʱ��
	TDX_ID_XT_IPADDR,				// �ͻ���IP
	TDX_ID_XT_MACADDR,				// �ͻ���MAC
	TDX_ID_KHH,						// �ͻ���
	TDX_ID_XT_BRANCHID,				// ʵ��Ӫҵ��ID
	TDX_ID_ZJZH,					// �ʽ��˺�
	TDX_ID_RZ_FUNCID,				// ��������ID
	TDX_ID_RZ_FLAGRESULT,			// ��������־
	TDX_ID_RZ_TCTIME,				// �������ĺ�ʱ
	TDX_ID_RZ_APITIME,				// API��ʱ
	TDX_ID_RZ_QUEUETIME,			// �ŶӺ�ʱ
	TDX_ID_RETINFO,					// ������Ϣ
	TDX_ID_RZ_PAGEINDEX,			// ҳ�����
};

// �ʺ����� 1004
const WORD tdxRZZHSQFieldReq[]=
{
	TDX_ID_ZJZH,					// �����˺�
	TDX_ID_JYMM,					// �˺�����
	TDX_ID_KHMC,					// �˺�����
	TDX_ID_XT_BRANCHID,				// Ӫҵ��
	TDX_ID_RZ_LEVER,				// �û��ȼ�
};

// �ʺŶ���ⶳ 1006
const WORD tdxRZZHDJJDFieldReq[]=
{
	TDX_ID_CZBZ,					// ������־������1���ⶳ2��
	TDX_ID_ZJZH,					// ���ᡢ�ⶳ�˺�
	TDX_ID_RZ_LEVER,				// �������û��ȼ�
};

// ��ѯͳ�Ʒ��� 1008
const WORD tdxRZCXTJFXFieldReq[]=
{
	TDX_ID_RZ_STARTTIME,			// ��ѯ��ʼʱ��
	TDX_ID_RZ_ENDTIME,				// ��ѯ����ʱ��
	TDX_ID_RZ_FUNCID,				// ��������ID
	TDX_ID_XT_STARTPOS,				// ��ʼ���
	TDX_ID_RZ_PAGEINDEX,			// ҳ�����
};

// ������رղ�ѯ 1010
const WORD tdxRZQDYGBCXFieldReq[]=
{
	TDX_ID_RZ_STARTTIME,			// ��ѯ��ʼʱ��
	TDX_ID_RZ_ENDTIME,				// ��ѯ����ʱ��
	TDX_ID_XT_STARTPOS,				// ��ʼ���
	TDX_ID_RZ_PAGEINDEX,			// ҳ�����
};

// ��̨��æ�̶�1012
const WORD tdxRZHTFMCDFieldReq[]=
{
	TDX_ID_RZ_STARTTIME,			// ��ѯ��ʼʱ��
	TDX_ID_RZ_ENDTIME,				// ��ѯ����ʱ��
	TDX_ID_RZ_ITEMNUM,				// ��¼����
	TDX_ID_XT_STARTPOS,				// ��ʼ���
	TDX_ID_RZ_PAGEINDEX,			// ҳ�����
};

// ��̨�����ɲ�ѯ 1014
const WORD tdxRZHTCFHCXFieldReq[]=
{
	TDX_ID_RZ_STARTTIME,			// ��ѯ��ʼʱ��
	TDX_ID_RZ_ENDTIME,				// ��ѯ����ʱ��
	TDX_ID_XT_STARTPOS,				// ��ʼ���
	TDX_ID_RZ_PAGEINDEX,			// ҳ�����
};

// ����IP���� 1016
const WORD tdxRZFXIPPMFieldReq[]=
{
	TDX_ID_RZ_STARTTIME,			// ��ѯ��ʼʱ��
	TDX_ID_RZ_ENDTIME,				// ��ѯ����ʱ��
	TDX_ID_RZ_ITEMNUM,				// ��¼����
	TDX_ID_XT_STARTPOS,				// ��ʼ���
	TDX_ID_RZ_PAGEINDEX,			// ҳ�����
};

// �����˺� 1018
const WORD tdxRZFXZHFieldReq[]=
{
	TDX_ID_RZ_STARTTIME,			// ��ѯ��ʼʱ��
	TDX_ID_RZ_ENDTIME,				// ��ѯ����ʱ��
	TDX_ID_RZ_ITEMNUM,				// ��¼����
	TDX_ID_XT_STARTPOS,				// ��ʼ���
	TDX_ID_RZ_PAGEINDEX,			// ҳ�����
};

// ������ϸ��Ϣ 1020
const WORD tdxRZFXXXXXFieldReq[]=
{
	TDX_ID_RZ_STARTTIME,			// ��ѯ��ʼʱ��
	TDX_ID_RZ_ENDTIME,				// ��ѯ����ʱ��
	TDX_ID_ZJZH,					// �ʽ��˺�
	TDX_ID_XT_IPADDR,				// �ͻ�IP
	TDX_ID_XT_STARTPOS,				// ��ʼ���
	TDX_ID_RZ_PAGEINDEX,			// ҳ�����
};

// ��̨��æ�̶���ϸ 1022
const WORD tdxRZHTFMCDXXFieldReq[]=
{
	TDX_ID_RZ_STARTTIME,			// ��ѯ��ʼʱ��
	TDX_ID_RZ_ENDTIME,				// ��ѯ����ʱ��
	TDX_ID_RZ_TCIP,					// ��������IP
	TDX_ID_XT_STARTPOS,				// ��ʼ���
};

// ��������IP 1024
const WORD tdxRZTCIPFieldReq[] =
{
	TDX_ID_KHH,				// �ͻ���
	TDX_ID_JYMM,			// �ͻ�����	
};

//////////////////////////////////////////////////////////////////////////
//	��ѯ��
//////////////////////////////////////////////////////////////////////////

// ������ѯ 1100
const WORD tdxCDCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���

	TDX_ID_KSRQ,				// (����,�ڻ�)��ʼ����
	TDX_ID_ZZRQ,				// (����,�ڻ�)��ֹ����
};

// ����ί�в�ѯ 1102
const WORD tdxDRWTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_XT_PARAM,			// ����
};

// ��ʷί�в�ѯ 1104 (��ѡ)
const WORD tdxLSWTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_ZQDM,				// (��ѡ)֤ȯ����,�Ϳղ�ȫ����Ʊ
};

// ί�в�ѯ 1106��(��ѡ)
const WORD tdxWTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ���ճɽ���ѯ 1108
const WORD tdxDRCJCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_CJBH,				// �ɽ����
};

// ��ʷ�ɽ���ѯ 1110
const WORD tdxLSCJCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_ZQDM,				// (��ѡ)֤ȯ����,�Ϳղ�ȫ����Ʊ
};

// �ɽ���ѯ 1112
const WORD tdxCJCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// �ɷݲ�ѯ 1114
const WORD tdxGFCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
	
	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_ZQDM,				// ֤ȯ����
	TDX_ID_CZBZ,				// ������־(1--���ý���ʱ����ͨ�˺Źɷ�)
	TDX_ID_XT_MODE,				// ģʽ(�ͻ��˿�ѡ���ֶ����ݿ���,��λ����,0x00000001--����ӯ������������)
	TDX_ID_XT_FUNCTIONVERSION,	// ���ܰ汾
};

// �¹���� 1116
const WORD tdxXGPHFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// �ʽ���ˮ 1118
const WORD tdxZJLSFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
	
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_BZ,					// (��ѡ)����(һ�㲻��)
	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ��� 1120
const WORD tdxJGDFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_ZQDM,				// (��ѡ)֤ȯ����,�Ϳղ�ȫ����Ʊ
};

// �ɶ���ѯ 1122
const WORD tdxGDCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_CZBZ,				// ������־(1--���ý���ʱ����ͨ�˺Źɶ�)
	TDX_ID_DFFZDM,				// �Է���֧����
	TDX_ID_DFKHDM,				// �Է��ͻ�����
	TDX_ID_DFZJZH,				// �Է��ʽ��˺�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_DFMM,				// �Է�����
};

// ֤ȯ��Ϣ 1124
const WORD tdxZQXXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_MMBZ,				// ������־(0-�޼����� 1-�޼����� 'C'-�м����� ...)
	TDX_ID_ZQDM,				// ֤ȯ����
	TDX_ID_HYDM,				// (����,�ڻ�)��Լ����
	TDX_ID_ZQXXYXBZ,			// ֤ȯ��Ϣ��Ч��־(1--��Ҫ��ѯ�����֤ȯ��Ϣ)
	TDX_ID_XT_CHECKRISKFLAG,	// �����ձ�־
	TDX_ID_XT_FUNCTIONVERSION,	// ���ܰ汾
};

// ��ǩ��ѯ 1126
const WORD tdxZQCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
	
	TDX_ID_SCFLAG,				// (����)�г�����
	TDX_ID_ZQDM,				// ֤ȯ����
	TDX_ID_XT_STARTPOS,			// ��ʼ���
	
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

// �޸ĳɱ��� 1128
const WORD tdxXGCBJFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_SCFLAG,				// �г�����(����,��Ҫ��TDX_ID_ZHLB)
	TDX_ID_ZQDM,				// ֤ȯ����
	TDX_ID_CBJ,					// �³ɱ���
	TDX_ID_XWDM,				// ϯλ����("�ɷݲ�ѯ"�����˾���)
	TDX_ID_MRJJ,				// �������
	TDX_ID_CCJJ,				// �ֲ־���
	TDX_ID_SXYK,				// ʵ��ӯ��
};

// (��ѯ)�޸���ϵ��ʽ 1130
const WORD tdxXGLXFSFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
	
	TDX_ID_CZBZ,				// ������־(0-��ѯ,1-�޸�)
	TDX_ID_USERPHONE,			// �û���ϵ�绰
	TDX_ID_USEREMAIL,			// �û�EMAIL
	TDX_ID_USERADDRESS,			// �û�ͨѶ��ַ

    TDX_ID_KHMC,				// (��ѡ)�ͻ�����
    TDX_ID_ZJHM,				// (��ѡ)֤������
    TDX_ID_POSTALCODE,			// ��������
    TDX_ID_MOBILEPHONE,			// �ƶ��绰
	TDX_ID_WORKPHONE,			// ��λ�绰
	TDX_ID_HOMEPHONE,			// סլ�绰
	TDX_ID_MAILADDRESS,			// �ʼĵ�ַ
	TDX_ID_XT_PARAM,			// ����
	TDX_ID_FAX,					// ����
	TDX_ID_EDU,					// �����̶�
	TDX_ID_VOCATION,			// ְҵ
	TDX_ID_PROVINCE,			// ʡ��
	TDX_ID_CITY,				// ����
	TDX_ID_SECTION,				// Ͻ������
	TDX_ID_BPCALL,				// Ѱ������
	TDX_ID_ZBDLJYXX,			// �ܱߵ�¼У����Ϣ
	TDX_ID_XT_LOGINEMAIL,		// ��¼Email
	TDX_ID_XT_TRADEEMAIL,		// ����Email
	TDX_ID_XT_MOBILECHECKCODE,	// �ֻ���֤��
	TDX_ID_SALARY,				// ����
};

// ���ʵ� 1132
const WORD tdxDZDFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
	
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_BZ,					// (��ѡ)����(һ�㲻��)
	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ����Ȩ���ѯ 1134
const WORD tdxPSQYCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// Ȩ֤��Ϣ��ѯ 1136
const WORD tdxQZXXCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_ZQDM,				// ֤ȯ����
	TDX_ID_MMBZ,				// ������־
	TDX_ID_CZBZ,				// �������(0--Ȩ֤��Ϣ 1--��Ȩ��Ϣ)
};

// �ɽ����ܲ�ѯ 1138
const WORD tdxCJHZCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// �ɷݻ��ܲ�ѯ 1140
const WORD tdxGFHZCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// Ȩ֤��ͨȡ�� 1142
const WORD tdxQZKTQXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
	
	TDX_ID_CZBZ,				// ������־(0-��ͨ,1-ȡ��)
	TDX_ID_LX,					// (Э��)����(����dll�Լ�����,������������)
};

// Ԥί�в�ѯ 1144
const WORD tdxYWTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ǩ��Э�� 1146
const WORD tdxQDXYFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_LX,					// ����(0--����Լ����,1--ծȯ�ع�,)
	TDX_ID_CZBZ,				// ������־(1--��ͨ,2--ȡ��,)
};


// ��;�ʽ��ѯ 1148 (����)
const WORD tdxZTZJCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
};

// �����ת�� 1150 (����)
const WORD tdxJGXZZFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
	
	TDX_ID_WTJE,				// ί�н��
};

// ��֧���� 1152(����)
const WORD tdxFZDMFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
};

// ��ȡЭ������ 1154
const WORD tdxHQXYNRFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_LX,					// (Э��)����(����dll�Լ�ȷ��,������������)
};

// ��ȡIPO�б� 1156
const WORD tdxHQIPOLBFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
	
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// IPO��Ϣ��ѯ 1158
const WORD tdxIPOXXCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_ZQDM,				// ֤ȯ����
};

// Ԥ��ҪԼ��ѯ 1160
const WORD tdxYYCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

// Ԥ��ҪԼ���� 1162
const WORD tdxYYCDFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
	
	TDX_ID_ZQDM,				// ֤ȯ����
	TDX_ID_YYSL,				// ҪԼ����
	TDX_ID_SGRDM,				// �깺�˴���
};

// Ԥ��ҪԼ�걨 1164
const WORD tdxYYSBFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
	
	TDX_ID_MMBZ,				// (����)������־(0-�޼����� 1-�޼����� 'C'-�м����� ...)
	TDX_ID_SGRDM,				// �깺�˴���
	TDX_ID_TXMM,				// (����)ͨѶ����
	TDX_ID_SCFLAG,				// (����)�г�����
	TDX_ID_ZQDM,				// ֤ȯ����
	TDX_ID_WTJG,				// (����)ί�м۸�
	TDX_ID_JYDW,				// (����)���׵�λ
	TDX_ID_WTSL,				// ί������*
};

// ��Ѻ�ع� 1166
const WORD tdxZYHGFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
	TDX_ID_MMBZ,				// ������־(0-��Ѻ 1-�ع�)
	TDX_ID_TXMM,				// (����)ͨѶ����
	TDX_ID_SCFLAG,				// (����)�г�����
	TDX_ID_ZQDM,				// ֤ȯ����
	TDX_ID_WTJG,				// ί�м۸�(�ͻ�����1)
	TDX_ID_JYDW,				// (����)���׵�λ
	TDX_ID_WTSL,				// ί������
	TDX_ID_WTFS,				// (����)ί�з�ʽ
};

// δ���ճɽ���ϸ��ѯ 1168
const WORD tdxWJSCJMXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ���ԤԼ��ȡҵ�� 1170
const WORD tdxCGYYCQFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_BZ,					// ����
	TDX_ID_YZZZ_ZZJE,			// ȡ����
	TDX_ID_KSRQ,				// ��������
	TDX_ID_ZY,					// ժҪ
	TDX_ID_YZZZ_YHDM,			// ���д���
};

// ���ԤԼ��ȡҵ���ѯ 1172
const WORD tdxCGYYCQCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_CZBZ,				// ��־	 (0:"��ѯȫ��",1:"������",2:"��ͨ��",3:"�����")
	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ί�л��ܲ�ѯ 1174
const WORD tdxWTHZCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// �ʽ���ϸ��ѯ 1176
const WORD tdxZJMXCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ��ѯѡ�������� 1178
const WORD tdxCXXZCGYHFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
};

// ѡ�������� 1180
const WORD tdxXZCGYHFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_YZZZ_YHDM,			// ���д���
	TDX_ID_YZZZ_YHZH,			// �����ʺ�
};

// ��ѯЭ����Ϣ 1182
const WORD tdxCXXYXXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
};

// ��ʷ�ɽ����ܲ�ѯ 1184
const WORD tdxLSCJHZCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// �ɽ���ϸ��ѯ 1186
const WORD tdxCJMXCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ί�в�ѯ��ϸ 1188
const WORD tdxWTCXMXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_WTRQ,				// ί������
	TDX_ID_WTBH,				// ί�б��
	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_ZQDM,				// ֤ȯ����
	TDX_ID_ZQMC,				// ֤ȯ����
	TDX_ID_MMBZ,				// ������־
	TDX_ID_MMBZSM,				// ������־˵��
	TDX_ID_WTFS,				// ί�����
	TDX_ID_WTFSSM,				// ί�����˵��
	TDX_ID_CJSX,				// �ɽ�����
};

// �ɽ���ѯ��ϸ 1190
const WORD tdxCJCXMXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_WTRQ,				// ί������
	TDX_ID_WTBH,				// ί�б��
	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_ZQDM,				// ֤ȯ����
	TDX_ID_ZQMC,				// ֤ȯ����
	TDX_ID_MMBZ,				// ������־
	TDX_ID_MMBZSM,				// ������־˵��
	TDX_ID_WTFS,				// ί�����
	TDX_ID_WTFSSM,				// ί�����˵��
	TDX_ID_CJSX,				// �ɽ�����
};

// �����걨�����ѯ 1192
const WORD tdxYXSBHQCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_MMBZ,				// ������־
	TDX_ID_WTFS,				// (������־���)ί�з�ʽ
	TDX_ID_ZQDM,				// ֤ȯ����
	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ����ί�в�ѯ 1194
const WORD tdxPLWTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_ZQDM,				// ֤ȯ����
	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// LOF�ϲ���ش����ѯ 1196
const WORD tdxLOFHBXGDMCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_ZQDM,				// ֤ȯ����
};

// LOF�ֲ���ش����ѯ 1198
const WORD tdxLOFFCXGDMCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_ZQDM,				// ֤ȯ����
};

// LOF�̺�ҵ����ί�в�ѯ 1200
const WORD tdxLOFPHYWDRWTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// LOF�̺�ҵ����ʷί�в�ѯ 1202
const WORD tdxLOFPHYWLSWTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

// LOF�̺�ҵ���ճɽ���ѯ 1204
const WORD tdxLOFPHYWDRCJCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// LOF�̺�ҵ����ʷ�ɽ���ѯ 1206
const WORD tdxLOFPHYWLSCJCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

// LOF�̺�ҵ�񳷵���ѯ 1208
const WORD tdxLOFPHYWCDCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// �����ɷݲ�ѯ 1210
const WORD tdxFSGFCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ֤ȯ������Ϣ��ѯ 1212
const WORD tdxZQFSXXCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_ZQDM,				// ֤ȯ����
};

// ����ת�ó�����ѯ 1214
const WORD tdxBJZRCDCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ����ת��ί�в�ѯ 1216
const WORD tdxBJZRWTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ����ת�óɽ���ѯ 1218
const WORD tdxBJZRCJCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ��̬�ɷݲ�ѯ 1220
const WORD tdxDTGFCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_XT_MODE,				// ģʽ
	TDX_ID_XT_FUNCTIONVERSION,	// ���ܰ汾
	TDX_ID_CZBZ,				// ������־
};

// ծȯ��Ѻ���ѯ 1222
const WORD tdxZQZYKCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_MMBZ,				// ������־
	TDX_ID_ZQDM,				// ֤ȯ����
	TDX_ID_CZBZ,				// ������־
};

// �����ʽ���ϸ��ѯ 1224
const WORD tdxDCGZJMXCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ��ʷ�ֲֲ�ѯ 1226
const WORD tdxLSCCCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

// �ɷ���ϸ��ѯ 1228
const WORD tdxGFMXCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// �ɷݲ�ѯ(2nd��) 1230
const WORD tdxGFCXSECONDFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
	
	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_ZQDM,				// ֤ȯ����
	TDX_ID_CZBZ,				// ������־(1--���ý���ʱ����ͨ�˺Źɷ�)
	TDX_ID_XT_MODE,				// ģʽ(�ͻ��˿�ѡ���ֶ����ݿ���,��λ����,0x00000001--����ӯ������������)
};

// �ɷݲ�ѯ(3rd��) 1232
const WORD tdxGFCXTHIRDFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_ZQDM,				// ֤ȯ����
	TDX_ID_CZBZ,				// ������־(1--���ý���ʱ����ͨ�˺Źɷ�)
	TDX_ID_XT_MODE,				// ģʽ(�ͻ��˿�ѡ���ֶ����ݿ���,��λ����,0x00000001--����ӯ������������)
};

// ծȯ�ع���Լ��ѯ 1234
const WORD tdxZQHGHYCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

// �ͻ�������Ϣ��ѯ 1236
const WORD tdxKHDZXXCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

// �ۺ�Э�������ѯ 1238
const WORD tdxZHXYHQCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_MMBZ,				// ������־
	TDX_ID_WTFS,				// (������־���)ί�з�ʽ
	TDX_ID_ZQDM,				// ֤ȯ����
	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ��׼ȯ���ܲ�ѯ 1240
const WORD tdxBZQHZCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ��̨ծȯ�����ѯ 1242
const WORD tdxGTZQHQCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_MMBZ,				// ������־
	TDX_ID_WTFS,				// (������־���)ί�з�ʽ
	TDX_ID_ZQDM,				// ֤ȯ����
};

// ������Ȩ��Լ��ѯ 1244
const WORD tdxRZXQHYCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_CZZT,				// ����״̬(-1/0--ȫ��;���ఴλ����:0x1--�ɻ���Լ,0x2--������,0x4--����ʧ��,0x8--���˽�)
};

// ������Ȩ�ͻ���Ϣ��ѯ 1246
const WORD tdxRZXQKHXXCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ծȯ�ع���ʷ��ѯ 1248
const WORD tdxZQHGLSCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

// ��Ȩ�����ѯ 1250
const WORD tdxQQDMCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ��Ȩ�ֲֲ�ѯ 1252
const WORD tdxQQCCCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ��Ȩ����˰��ѯ 1254
const WORD tdxQQSDSCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

// ��Ȩ����ί�в�ѯ 1256
const WORD tdxQQDRWTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_CZBZ,				// ������־(0--��ѯȫ��ί��,1--��ѯ�ɳ���ί��)
};

// ��Ȩ��ʷί�в�ѯ 1258
const WORD tdxQQLSWTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

//////////////////////////////////////////////////////////////////////////
//	�ڻ�������(ԭ����ģ�⻷��,�ֲ���������������)
//////////////////////////////////////////////////////////////////////////

// �ڻ�ί�� 1500 (����)
const WORD tdxQHWTFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
	
	TDX_ID_MMBZ,				// ������־(0-�޼����� 1-�޼����� 'C'-�м����� ...)
	TDX_ID_KPBZ,				// ��ƽ��־
	TDX_ID_QHZH,				// �ڻ��ʺ�
	TDX_ID_TXMM,				// (����)ͨѶ����
	TDX_ID_SCFLAG,				// (����)�г�����
	TDX_ID_HYDM,				// ��Լ����
	TDX_ID_WTJG,				// ί�м۸�
	TDX_ID_JYDW,				// ���׵�λ
	TDX_ID_WTSL,				// ί������
};

// ��ѯ�ڻ��ֲ� 1502 (����)
const WORD tdxCXQHCCFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
	
	TDX_ID_QHZH,				// �ڻ��ʺ�
};

// ��ѯ��Լ��Ϣ 1504 (����)
const WORD tdxCXHYXXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ����)
	TDX_ID_GDDM,				// �ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
	
	TDX_ID_QHZH,				// �ڻ��ʺ�
	TDX_ID_HYDM,				// ��Լ����
};

// ��ѯ�ɽ��׺�Լ 1506
const WORD tdxCXKJYHYFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
	
	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_CZBZ,				// ������־(0--��ѯȫ����Լ,1--��ѯָ���г��Ŀ��ú�Լ,Ĭ��--0)
	TDX_ID_SCFLAG,				// �г�����(CZBZ=1ʱ��Ч)
};

// �����ʽ���ˮ 1508
const WORD tdxDRZJLSFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
	
	TDX_ID_BZ,					// (��ѡ)����(һ�㲻��)
	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// �ڻ�ί��״̬��ѯ 1510
const WORD tdxQHWTZTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
	
	TDX_ID_WTBH,				// ί�б��
};

// �ڻ�ί�лر� 1512 [���͹���,����ʹ��]
const WORD tdxQHWTHBFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
};

// �ڻ�ί�лر� 1513

// �ڻ������ر� 1514 [���͹���,����ʹ��]
const WORD tdxQHCDHBFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
};

// �ڻ������ر� 1515

// �ڻ��ɽ��ر� 1516 [���͹���,����ʹ��]
const WORD tdxQHCJHBFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
};

// �ڻ��ɽ��ر� 1517

// �ڻ���Ϣ���� 1518 [���͹���,����ʹ��]
const WORD tdxQHXXFBFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
};

// �ڻ���Ϣ���� 1519

// �ڻ�������״̬�ı� 1520 [���͹���,����ʹ��]
const WORD tdxQHJYSZTGBFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
};

// �ڻ�������״̬�ı� 1521

// �ڻ���Ϻ�Լ��� 1522 [���͹���,����ʹ��]
const WORD tdxQHZHHYBGFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
};

// �ڻ���Ϻ�Լ��� 1523

// �ڻ����ί�лر� 1524 [���͹���,����ʹ��]
const WORD tdxQHZHWTHBFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
};

// �ڻ����ί�лر� 1525

// �ڻ���ϳ����ر� 1526 [���͹���,����ʹ��]
const WORD tdxQHZHCDHBFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ
};

// �ڻ���ϳ����ر� 1527

// �ڻ��������Ͳ�ѯ 1528
const WORD tdxQHDDLXCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_MODE,				// ģʽ(0--�����,1--���,��--ȫ��)
	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// �ڻ����ί�� 1530
const WORD tdxQHZHWTFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XWDM,				// ϯλ����
	TDX_ID_WTSL,				// ί������
	TDX_ID_WTJG,				// ί�м۸�
	TDX_ID_CLDM,				// ���Դ���
	TDX_ID_WTFS,				// ί������
	TDX_ID_CJSX,				// �ɽ�����
	TDX_ID_ZHLX,				// �������
	TDX_ID_MMBZ,				// ������־
	TDX_ID_KPBZ,				// ��ƽ��־
	TDX_ID_TBBZ,				// Ͷ����־
	TDX_ID_HYDM1,				// ��Լ����1
	TDX_ID_HYDM2,				// ��Լ����2
	TDX_ID_HYDM3,				// ��Լ����3
	TDX_ID_HYDM4,				// ��Լ����4
	TDX_ID_XT_TOKEN,			// ����
};

// �ڻ���ϳ��� 1532
const WORD tdxQHZHCDFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XWDM,				// ϯλ����
	TDX_ID_WTBH,				// ί�б��
	TDX_ID_XT_PARAM,			// ����
};

// �ڻ���Ϻ�Լ��ѯ 1534
const WORD tdxQHZHHYCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// �ڻ���ϳֲֲ�ѯ 1536
const WORD tdxQHZHCCCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// �ڻ����ί�в�ѯ 1538
const WORD tdxQHZHWTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// �ڻ���ϼ����ί���� 1540
const WORD tdxQHZHJSKWTSFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_XWDM,				// ϯλ����
	TDX_ID_CLDM,				// ���Դ���
	TDX_ID_MMBZ,				// ������־
	TDX_ID_TBBZ,				// Ͷ����־
	TDX_ID_HYDM1,				// ��Լ����1
	TDX_ID_HYDM2,				// ��Լ����2
	TDX_ID_HYDM3,				// ��Լ����3
	TDX_ID_HYDM4,				// ��Լ����4
	TDX_ID_ZHLX,				// �������
};

// �ڻ���ϲ��Բ�ѯ 1542
const WORD tdxQHZHCLCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ������ʽ

	TDX_ID_CLDM,				// ���Դ���
	TDX_ID_ZHLX,				// �������
	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

//////////////////////////////////////////////////////////////////////////
//	�ع���
//////////////////////////////////////////////////////////////////////////
// ��Ʊ��Ѻ�ع� 1800
const WORD tdxGPZYHGFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_HZHGZT,				// �ع�״̬(1--��ʼ��������,2--������Ѻ����,3--���ֽ����Ѻ����,4--��������,5--�걨����)
	TDX_ID_LX,					// ����(1--���ڹ���,2--��ǰ����,3--���ڹ���)
	TDX_ID_CPDM,				// ��Ʒ����
	TDX_ID_WTSL,				// ί������
	TDX_ID_WTJE,				// ί�н��
	TDX_ID_WTRQ,				// ί������
	TDX_ID_WTBH,				// ί�б��
	TDX_ID_CJRQ,				// �ɽ�����
	TDX_ID_CJBH,				// �ɽ����
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_SCFLAG,				// �г�����
	
	TDX_ID_XWDM,				// ϯλ����
	TDX_ID_DFXWDM,				// �Է�ϯλ����
	TDX_ID_DFGDDM,				// �Է��ɶ�����
};

// ��Ʊ��Ѻ�ع������ѯ 1802
const WORD tdxGPZYHGSQCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ��Ʊ��Ѻ�ع���ͬ��ѯ 1804
const WORD tdxGPZYHGHTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ��Ʊ��Ѻ�ع�Ȩ���ѯ 1806
const WORD tdxGPZYHGQYCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ��Ʊ��Ѻ�ع��������ʲ�ѯ 1808
const WORD tdxGPZYHGQXLLCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ��Ʊ��Ѻ�ع���ˮ��ѯ 1810
const WORD tdxGPZYHGLSCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ��Ʊ��Ѻ�ع��ڳ�����ѯ 1812
const WORD tdxGPZYHGRCFCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ��Ʊ��Ѻ�ع���Ϣ��ѯ 1814
const WORD tdxGPZYHGLXCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ��Ʊ��Ѻ�ع���ʷ��ͬ��ѯ 1816
const WORD tdxGPZYHGLSHTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ��Ʊ��Ѻ�ع����֤ȯ��ѯ 1818
const WORD tdxGPZYHGBDZQCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ��ɫ�ع� 1830
const WORD tdxTSHGFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_HZHGZT,				// �ع�״̬(1--�Ǽ�,2--�޸�,3--ȡ��)
	TDX_ID_CPDM,				// ��Ʒ����
	TDX_ID_WTSL,				// ί������
	TDX_ID_WTJE,				// ί�н��
	TDX_ID_WTRQ,				// ί������
	TDX_ID_WTBH,				// ί�б��
	TDX_ID_CJRQ,				// �ɽ�����
	TDX_ID_CJBH,				// �ɽ����
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_SCFLAG,				// �г�����
	
	TDX_ID_XWDM,				// ϯλ����
	TDX_ID_DFXWDM,				// �Է�ϯλ����
	TDX_ID_DFGDDM,				// �Է��ɶ�����
};

// ��ɫ�ع���Ϣ��ѯ 1832
const WORD tdxTSHGXXCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_CPDM,				// ��Ʒ����
	TDX_ID_LX,					// ����(0--Ȫ��ͨ 1-Ȫ��ͨ)
};

// ��ɫ�ع������ѯ 1834
const WORD tdxTSHGSQCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ��ɫ�ع������ѯ 1836
const WORD tdxTSHGDMCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ��ɫ�ع���֤ͨ 1838
const WORD tdxTSHGYZTFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_ZJMM,				// �ʽ�����
	TDX_ID_YZZZ_ZZFX,			// ת�ʷ���
	TDX_ID_YZZZ_YHDM,			// ���д���
	TDX_ID_YZZZ_YHMM,			// ��������
	TDX_ID_YZZZ_ZZJE,			// ת�ʽ��

	TDX_ID_CZBZ,				// ������־(1--�Ǽ�,2--�޸�,3--ȡ��)
	TDX_ID_WTRQ,				// ί������
	TDX_ID_WTSJ,				// ί��ʱ��
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_CZZT,				// ����״̬(0--���� 1--��ͣ)
};

// ��ɫ�ع�ת�˼ƻ���ѯ 1840
const WORD tdxTSHGZZJHCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ��ɫ�ع���ˮ��ѯ 1842
const WORD tdxTSHGLSCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ����״̬����(��ѯ) 2000
const WORD tdxPSZTSZFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_CZZT,				// ������־
	TDX_ID_WTSL,				// ί������
	TDX_ID_WTJG,				// ί�м۸�
	TDX_ID_WTJE,				// ί�н��
	TDX_ID_WTRQ,				// ί������
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_XT_REMARK,			// ��ע
	TDX_ID_XT_PARAM,			// ����
};

// �����ع� 2002
const WORD tdxHZHGFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ
	
	TDX_ID_HZHGZT,				// �����ع�״̬(0--��������,1--��ǰ��ֹ,2--����.3--��Լ,4--��Լ��ֹ,5--��ǰ��ֹԤԼ,6--��ǰ��ֹԤԼ����)
	TDX_ID_CPDM,				// ��Ʒ����
	TDX_ID_WTSL,				// ί������
	TDX_ID_CJRQ,				// �ɽ�����
	TDX_ID_CJBH,				// �ɽ����
	TDX_ID_WTRQ,				// ί������
	TDX_ID_WTBH,				// ί�б��
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_ZDWTBJ,				// �Զ�ί�б��(0--���Զ�չ��,1--�Զ�չ��,Ĭ��--0)
	TDX_ID_CJJG,				// �ɽ��۸�
	TDX_ID_CJSL,				// �ɽ�����
	TDX_ID_XT_PARAM,			// ����(�ӿڲ�ѯ���ܸ���,�ͻ���ԭ�ⷵ��)
	TDX_ID_XT_CHECKRISKFLAG,	// �����ձ�־(1--����Ƿ�ӵ��ǩ�𱨼ۻع�Ȩ��)
	TDX_ID_CZBZ,				// ������־(0--�Ϻ����ۻع�,1--���ڱ��ۻع�,Ĭ��--0,���͵�ͬ0)
};

// �����ع�״̬(��ѯ) 2004
const WORD tdxHZHGZTFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

// �����깺״̬(��ѯ) 2006
const WORD tdxHZSGZTFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

// �����ع���Ʒ�����ѯ 2008
const WORD tdxHZHGCPDMCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_CZBZ,				// ������־(0--�Ϻ����ۻع�,1--���ڱ��ۻع�,Ĭ��--0,���͵�ͬ0)
};

// �����ع���Ʒ��Ϣ��ѯ 2010
const WORD tdxHZHGCPXXCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_CPDM,				// ��Ʒ����
	TDX_ID_CZBZ,				// ������־(0--�Ϻ����ۻع�,1--���ڱ��ۻع�,Ĭ��--0,���͵�ͬ0)
};

// �����ع���ǰ��ֹ��ѯ 2012
const WORD tdxHZHGTQZZCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_CZBZ,				// ������־(0--�Ϻ����ۻع�,1--���ڱ��ۻع�,Ĭ��--0,���͵�ͬ0)
};

// �����ع�����ί�в�ѯ 2014
const WORD tdxHZHGDRWTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_CZBZ,				// ������־(0--�Ϻ����ۻع�,1--���ڱ��ۻع�,Ĭ��--0,���͵�ͬ0)
	TDX_ID_XT_FUNCTIONVERSION,	// ���ܰ汾
};

// �����ع����ճɽ���ѯ 2016
const WORD tdxHZHGDRCJCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// �����ع���ʷί�в�ѯ 2018
const WORD tdxHZHGLSWTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_CZBZ,				// ������־(0--�Ϻ����ۻع�,1--���ڱ��ۻع�,Ĭ��--0,���͵�ͬ0)
};

// �����ع���ʷ�ɽ���ѯ 2020
const WORD tdxHZHGLSCJCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

// �����ع����ں�Լ��ѯ 2022
const WORD tdxHZHGQNHYCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_CZBZ,				// ������־(0--�Ϻ����ۻع�,1--���ڱ��ۻع�,Ĭ��--0,���͵�ͬ0)
	TDX_ID_XT_FUNCTIONVERSION,	// ���ܰ汾
};

// �����ع�������ѯ 2024
const WORD tdxHZHGCDCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_CZBZ,				// ������־(0--�Ϻ����ۻع�,1--���ڱ��ۻع�,Ĭ��--0,���͵�ͬ0)
};

// �����ع���Լ��ѯ 2026
const WORD tdxHZHGXYCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_CZBZ,				// ������־(0--�Ϻ����ۻع�,1--���ڱ��ۻع�,Ĭ��--0,���͵�ͬ0)
};

// �����ع���Լ��ֹ��ѯ 2028
const WORD tdxHZHGXYZZCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_CZBZ,				// ������־(0--�Ϻ����ۻع�,1--���ڱ��ۻع�,Ĭ��--0,���͵�ͬ0)
};

// �����ع���ǰ��ֹԤԼ��ѯ 2030
const WORD tdxHZHGTQZZYYCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_CZBZ,				// ������־(0--�Ϻ����ۻع�,1--���ڱ��ۻع�,Ĭ��--0,���͵�ͬ0)
};

// �����ع���ǰ��ֹԤԼ������ѯ 2032
const WORD tdxHZHGTQZZYYCXCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_CZBZ,				// ������־(0--��Ϊ���ײ�ѯ,1--��Ϊ������ѯ,Ĭ��--0)
	TDX_ID_LX,					// ����(0--��ǰ���� 1-�Զ�����)
	TDX_ID_CZBZ,				// ������־(0--�Ϻ����ۻع�,1--���ڱ��ۻع�,Ĭ��--0,���͵�ͬ0)
};

// �����ع���Ӧ��Ѻ���ѯ 2034
const WORD tdxHZHGDYZYWCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_CJRQ,				// �ɽ�����
	TDX_ID_CJBH,				// �ɽ����
};

// �����ع���Լ������ѯ 2036
const WORD tdxHZHGXYCDCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_CZBZ,				// ������־(0--�Ϻ����ۻع�,1--���ڱ��ۻع�,Ĭ��--0,���͵�ͬ0)
};

// �����ع����յ��ڲ�ѯ 2038
const WORD tdxHZHGDRDQCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// �����ع���ʷ���ڲ�ѯ 2040
const WORD tdxHZHGLSDQCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

// �����ع�������ֹԤԼ��ѯ 2042
const WORD tdxHZHGXZZZYYCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// �����ع�������ֹԤԼ������ѯ 2044
const WORD tdxHZHGXZZZYYCXCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// �����ع���Լ�����ѯ 2046
const WORD tdxHZHGXYBGCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// �����ع���Լ�����ѯ 2048
const WORD tdxHZHGHYSYCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

// ���ڱ��ۻع���Ʒ�����ѯ 2050
const WORD tdxSZBJHGCPDMCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_CZBZ,				// ������־(0--����,1--��ʷ,Ĭ��--0,���͵�ͬ0)

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

//  ���ڱ��ۻع����ں�Լ��ѯ 2052
const WORD tdxSZBJHGQNHYCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_CZBZ,				// ������־
	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// �����ع�Э���������ײ�ѯ 2054
const WORD tdxHZHGXYSZPTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_CZBZ,				// ������־(0--���ۻع�Э������,1--�Զ�ɨ��Э������ Ĭ��--0 ���͵�ͬ0)
	TDX_ID_XT_STARTPOS,			// ��ʼ���
};


//////////////////////////////////////////////////////////////////////////

// Լ���ع���ʼ�������ײ�ѯ 2070
const WORD tdxYDHGCSJYPTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// Լ���ع���Լ�������ײ�ѯ 2072
const WORD tdxYDHGLYBZPTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// Լ���ع���ǰ�������ײ�ѯ 2074
const WORD tdxYDHGTQGHPTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// Լ���ع������������ײ�ѯ 2076
const WORD tdxYDHGYQSQPTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// Լ���ع����׳������ײ�ѯ 2078
const WORD tdxYDHGJYCDPTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// Լ���ع���ǰ��Լ��ѯ 2080
const WORD tdxYDHGDQHYCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_TSXX1,				// ��ʾ��Ϣ1(��Լ״̬,��̨ԭ���ֶ�)
};

// Լ���ع���ʷ��Լ��ѯ 2082
const WORD tdxYDHGLSHYCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

// Լ���ع����к�Լ��ѯ 2084
const WORD tdxYDHGJXHYCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

// Լ���ع���ֹ��Լ��ѯ 2086
const WORD tdxYDHGZZHYCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

// Լ���ع����֤ȯ��ѯ 2088
const WORD tdxYDHGBDZQCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_ZQDM,				// ֤ȯ����
	TDX_ID_TSXX1,				// ��ʾ��Ϣ1(֤ȯ���,��̨ԭ���ֶ�)
	TDX_ID_SCFLAG,				// �г�����
};

// Լ���ع���Ʒ��Ϣ��ѯ 2090
const WORD tdxYDHGCPXXCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_HYQX,				// ��Լ����
};

// Լ���ع��ۺ���Ϣ��ѯ 2092
const WORD tdxYDHGZHXXCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_CZBZ,				// ������־
};

// Լ���ع�ҵ�����(��Ϣ��ѯ) 2098
const WORD tdxYDHGYWCZFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����(�ɶ����)
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_CZBZ,				// ������־
	TDX_ID_XT_PARAM,			// ����
	TDX_ID_ZQDM,				// ֤ȯ����
	TDX_ID_WTSL,				// ί������
	TDX_ID_WTJE,				// ί�н��
	TDX_ID_WTRQ,				// ί������
	TDX_ID_WTBH,				// ί�б��
	TDX_ID_DQR,					// ������
	TDX_ID_YDXH,				// Լ�����
	TDX_ID_XT_REMARK,			// ��ע
};

//////////////////////////////////////////////////////////////////////////
//	����ʽ������
//////////////////////////////////////////////////////////////////////////

// ����ʽ����ί�� 2100
const WORD tdxKFSJJWTFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// ����˾����
	TDX_ID_KFSJJ_JJZH,			// �����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// �������
	
	TDX_ID_KFSJJ_MMBZ,			// ����ʽ����������־(0,�Ϲ� 1,�깺 2,��� 3,ԤԼ�깺 4,ԤԼ��� 5,�����깺 6 ԤԼ�Ϲ�)
	TDX_ID_KFSJJ_JYJE,			// �Ϲ�/�깺���
	TDX_ID_KFSJJ_JJFE,			// ��طݶ�
	TDX_ID_KFSJJ_FSRQ,			// (Ԥ�깺���/ԤԼ�Ϲ�)��������

	TDX_ID_SHFS,				// (���/ԤԼ���)�޶���ط�ʽ
	TDX_ID_TJRDM,				// (��ѡ)(�깺/�Ϲ�)�Ƽ��˴���
	TDX_ID_IDENTITYCARD,		// ���֤
	TDX_ID_SFFS,				// �շѷ�ʽ
	TDX_ID_XT_CHECKRISKFLAG,	// �����ձ�־
	TDX_ID_CPBZ,				// ��Ʒ��־

	TDX_ID_WTSL,				// ί������
	TDX_ID_WTJG,				// ί�м۸�
	TDX_ID_LXFS,				// ��ϵ��ʽ
	TDX_ID_LXRXM,				// ��ϵ������
	TDX_ID_DFXWDM,				// �Է�ϯλ����
	TDX_ID_YDXH,				// Լ�����
	TDX_ID_CZBZ,				// ������־
};

// ����ʽ����ί�г��� 2102
const WORD tdxKFSJJWTCDFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// ����˾����
	TDX_ID_KFSJJ_JJZH,			// �����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// �������
	
	TDX_ID_WTRQ,				// ί���ύ����
	TDX_ID_KFSJJ_JJFE,			// ί���ύ�ݶ�
	TDX_ID_KFSJJ_JYJE,			// ί���ύ���
	TDX_ID_WTBH,				// ί�б��
	TDX_ID_SFFS,				// �շѷ�ʽ
	TDX_ID_KFSJJ_MMBZ,			// ����ʽ����������־
	TDX_ID_CZBZ,				// ������־
	TDX_ID_CPBZ,				// ��Ʒ��־
};

// ����ʽ����ת�� 2104
const WORD tdxKFSJJZHFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// ����˾����
	TDX_ID_KFSJJ_JJZH,			// �����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// �������(ת������)

	TDX_ID_KFSJJ_ZHDM,			// ת������(ת�����)
	TDX_ID_KFSJJ_JYJE,			// ���׽��(ת���ݶ�)

	TDX_ID_SHFS,				// �޶���ط�ʽ: 0,���ȡ�� 1,���˳��
	TDX_ID_SFFS,				// �շѷ�ʽ(ת������)
	TDX_ID_XT_CHECKRISKFLAG,	// �����ձ�־
	TDX_ID_CPBZ,				// ��Ʒ��־
};

// ����ʽ����ݶ��ѯ 2106
const WORD tdxKFSJJFECXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
	TDX_ID_CPBZ,				// ��Ʒ��־
};

// ����ʽ����ί�в�ѯ 2108
const WORD tdxKFSJJWTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_KSRQ,				// ��ѯ��ʼ����
	TDX_ID_ZZRQ,				// ��ѯ��������
	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
	TDX_ID_CPBZ,				// ��Ʒ��־
};

// ����ʽ������Ϣ��ѯ 2110
const WORD tdxKFSJJXXCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// ����˾����
	TDX_ID_KFSJJ_JJZH,			// �����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// �������

	TDX_ID_KFSJJ_MMBZ,			// 0,�Ϲ� 1,�깺 2,��� 3,ԤԼ�깺 4,ԤԼ��� 5,�����깺 6,ԤԼ�Ϲ�
	TDX_ID_XT_CHECKRISKFLAG,	// �����ձ�־
	TDX_ID_CPBZ,				// ��Ʒ��־
	TDX_ID_WTJG,				// ί�м۸�
	TDX_ID_XT_PARAM,			// ����
};

// ����ʽ����ɽ���ѯ 2112
const WORD tdxKFSJJCJCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_KSRQ,				// ��ѯ��ʼ����
	TDX_ID_ZZRQ,				// ��ѯ��������
	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
	TDX_ID_CPBZ,				// ��Ʒ��־
};

// ����ʽ����ֺ��趨 2114
const WORD tdxKFSJJFHFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// ����˾����
	TDX_ID_KFSJJ_JJZH,			// �����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// �������
	
	TDX_ID_KFSJJ_DIVIDENMETHOD,	// �·ֺ췽ʽ 0,����ת�� 1,�ֽ�ֺ� 2,-�����ֽ���ֵ��Ͷ�� 3,��ֵ�ֽ�������
	TDX_ID_SFFS,				// �շѷ�ʽ
	TDX_ID_CPBZ,				// ��Ʒ��־
};

// ����ʽ��������ѯ 2116
const WORD tdxKFSJJDMCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
	TDX_ID_CPBZ,				// ��Ʒ��־
};

// ����ʽ�����ʽ��ʻ����� 2118
const WORD tdxKFSJJZJZHKHFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// �ʺ����(�ɶ��������,�󶨵Ĺɶ��������)
	TDX_ID_GDDM,				// �ɶ�����(�󶨵Ĺɶ�����,Ϊ�ղ���)
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// ����˾����
	TDX_ID_KFSJJ_JJZH,			// �����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������
	
	TDX_ID_CZBZ,				// ������־ 0,�׿� 1,��ͨ������������ͨ
	TDX_ID_KHMC,				// �ͻ�����
	TDX_ID_USERADDRESS,			// �ͻ���ַ
	TDX_ID_USERPHONE,			// ��ϵ�绰
	TDX_ID_USEREMAIL,			// �ͻ��ʼ�
	TDX_ID_KHTYPE,				// ������� 0,���� 1,����
	TDX_ID_ZJHM,				// ֤������
	TDX_ID_MOBILEPHONE,			// �ƶ��绰
	TDX_ID_HOMEPHONE,			// סլ�绰
	TDX_ID_WORKPHONE,			// �����绰
	TDX_ID_FAX,					// �������
	TDX_ID_EDU,					// �����̶�
	TDX_ID_SALARY,				// ������
	TDX_ID_VOCATION,			// ְҵ
	TDX_ID_DZDBZ,				// ���ʵ����ͷ�ʽ 0,������ 1,���� 2,���� 3,���� 4,һ��
	TDX_ID_SEX,					// �Ա�
	TDX_ID_POSTALCODE,			// ��������

	TDX_ID_ZJLB,				// ֤�����
	TDX_ID_FHBZ,				// �ֺ��־
	TDX_ID_NAME,				// �û���
	TDX_ID_SHFS,				// �շѷ�ʽ
	TDX_ID_FHBL,				// �ֺ����

	TDX_ID_FRDBXM,				// ���˴�������
	TDX_ID_FRDBZJLX,			// ���˴���֤������
	TDX_ID_FRDBZJHM,			// ���˴���֤������
	TDX_ID_LXRXM,				// ��ϵ������
	TDX_ID_LXRZJLX,				// ��ϵ��֤������
	TDX_ID_LXRZJHM,				// ��ϵ��֤������
	TDX_ID_LXRDH,				// ��ϵ�˵绰
	TDX_ID_CPBZ,				// ��Ʒ��־
};

// ����ʽ�����ʽ��ʻ�ע�� 2120 (����)
const WORD tdxKFSJJZJZHZCFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// ����˾����
	TDX_ID_KFSJJ_JJZH,			// �����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������
	
	TDX_ID_KHMC,				// �ͻ�����
	TDX_ID_ZJMM,				// �ʽ�����
	TDX_ID_USERADDRESS,			// �û�ͨѶ��ַ
	TDX_ID_ZJHM,				// ���֤
	TDX_ID_SEX,					// �Ա�
	TDX_ID_POSTALCODE,			// ��������
};

// ����ʽ����ͻ������޸� 2122
const WORD tdxKFSJJKHZLXGFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// ����˾����
	TDX_ID_KFSJJ_JJZH,			// �����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������
	
	TDX_ID_CZBZ,				// ������־(0-��ѯ,1-�޸�)
	TDX_ID_USERADDRESS,			// ��ϵ��ַ
	TDX_ID_USERPHONE,			// �绰����
	TDX_ID_USEREMAIL,			// �����ʼ�
	TDX_ID_MOBILEPHONE,			// �ֻ�����
	TDX_ID_POSTALCODE,			// ��������
	TDX_ID_HOMEPHONE,			// סլ�绰
	TDX_ID_WORKPHONE,			// ��λ�绰����
	TDX_ID_FAX,					// ����

	TDX_ID_KHMC,				// �ͻ�����
	TDX_ID_ZJHM,				// ֤������
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_XT_PARAM,			// ����
};

// ����ʽ�����ѯ��˾���� 2124
const WORD tdxKFSJJCXGSDMFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_CZZT,				// 0,������ 1,���Ѿ��ǼǵĻ���˾  2����ѯ������Ƶ�����
	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
	TDX_ID_CPBZ,				// ��Ʒ��־
};

// ����ʽ�����ʺŲ�ѯ 2126
const WORD tdxKFSJJZHCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
	TDX_ID_CPBZ,				// ��Ʒ��־
};

// ����ʽ������ʷί�в�ѯ 2128
const WORD tdxKFSJJLSWTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������
	
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
	TDX_ID_CPBZ,				// ��Ʒ��־
};

// ����ʽ����ʱ�����깺���� 2130
const WORD tdxKFSJJDSDESGSZFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// ����˾����
	TDX_ID_KFSJJ_JJZH,			// �����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// �������

	TDX_ID_KFSJJ_JYJE,			// ���׽��(ί�н��)
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_KFSJJ_MYKKRQ,		// ÿ�¿ۿ�����
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_CZBZ,				// ������־(0--���,1--�޸�)
	TDX_ID_SFFS,				// �շѷ�ʽ
	TDX_ID_LX,					// ����(��������:0--��������,1--�ɹ�����,2--�ɹ����)
	TDX_ID_XT_PARAM,			// ����(��������:TDX_ID_LX=1--��ʾ�ɹ����������ֵ,TDX_ID_LX=2--��ʾ�ɹ���������ֵ)
	TDX_ID_XT_MODE,				// ģʽ(�ۿ�����:0--ÿ��,1--ÿ��,2--ÿ��,3--ÿ��)
	TDX_ID_XT_DESCRIPTION,		// ����
	TDX_ID_WTRQ,				// ί������(�޸�ʱ��Ч)
	TDX_ID_WTBH,				// ί�б��(�޸�ʱ��Ч)
	TDX_ID_LSH,					// ��ˮ��(�޸�ʱ��Ч)
	TDX_ID_XT_REMARK,			// ��ע
	TDX_ID_XT_CHECKRISKFLAG,	// �����ձ�־
	TDX_ID_TJRDM,				// �Ƽ��˴���
	TDX_ID_KFSJJ_PZDM,			// Ʒ�ִ���
	TDX_ID_YXSBCS,				// ��Чʧ�ܴ���
};

// ����ʽ����ʱ�����깺ȡ�� 2132
const WORD tdxKFSJJDSDESGQXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// ����˾����
	TDX_ID_KFSJJ_JJZH,			// �����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// �������

	TDX_ID_WTBH,				// ί�б��
	TDX_ID_WTRQ,				// ί������
	TDX_ID_LSH,					// ��ˮ��
	TDX_ID_KFSJJ_JYJE,			// ���׽��(ί�н��)
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_KFSJJ_MYKKRQ,		// ÿ�¿ۿ�����
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_SFFS,				// �շѷ�ʽ
	TDX_ID_LX,					// ����(��������:0--��������,1--�ɹ�����,2--�ɹ����)
	TDX_ID_XT_PARAM,			// ����(��������:TDX_ID_LX=1--��ʾ�ɹ����������ֵ,TDX_ID_LX=2--��ʾ�ɹ���������ֵ)
	TDX_ID_XT_MODE,				// ģʽ(�ۿ�����:0--ÿ��,1--ÿ��,2--ÿ��,3--ÿ��)
	TDX_ID_XT_DESCRIPTION,		// ����
	TDX_ID_XT_REMARK,			// ��ע
};

// ����ʽ�����ѯ���ڶ����깺Ʒ�� 2134
const WORD tdxKFSJJCXDQDESGPZFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ
	
	TDX_ID_KFSJJ_JJGSDM,		// ����˾����
	TDX_ID_KFSJJ_JJZH,			// �����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// �������

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

// ����ʽ�����ѯ���ڶ����깺���ò�ѯ 2160
const WORD tdxKFSJJDSDESZCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ
	
	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_CPBZ,				// ��Ʒ��־
};

// ����ʽ������ί�в�ѯ 2136
const WORD tdxKFSJJDRWTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ
	
	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������
		
	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

// ����ʽ����ֺ��ѯ 2138
const WORD tdxKFSJJFHCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ
	
	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// �������
};

// LOF����ֺ��ѯ 2140 
const WORD tdxLOFJJFHCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ
};

// LOF����ֺ� 2142 
const WORD tdxLOFJJFHFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ
	TDX_ID_KFSJJ_JJDM,			// ������� 
	TDX_ID_KFSJJ_DIVIDENMETHOD,	// �·ֺ췽ʽ 0,����ת�� 1,�ֽ�ֺ� 2,-�����ֽ���ֵ��Ͷ�� 3,��ֵ�ֽ�������
	TDX_ID_XWDM,				// ϯλ����
};

// ����ʽ���������Ϣ��ѯ 2144
const WORD tdxKFSJJFXXXCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ
	
	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_LX,					// ����(0--���������Ϣ,4--��ҵ�������Ϣ,����--Ĭ�Ϸ��ػ��������Ϣ)
};

// ����ʽ����ת�ʿ��� 2146 (����)
const WORD tdxKFSJJZZKHFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ
	
	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������
};

// ����ʽ�����׿��� 2148 (����)
const WORD tdxKFSJJJYKHFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ
	
	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������
};

// ����ʽ�����ճɽ���ѯ 2150
const WORD tdxKFSJJDRCJCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ
	
	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

// ����ʽ������ʷ�ɽ���ѯ 2152
const WORD tdxKFSJJLSCJCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ
	
	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

// ����ʽ����ֵ��ѯ 2154
const WORD tdxKFSJJJZCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ
	
	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

// ����Э���ѯ��ͨ 2156
const WORD tdxKFSJJXYCXKTFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ
	
	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_CZBZ,				// ������־(0:��ѯ,1:��ͨ)
	TDX_ID_KHMC,				// �ͻ�����
	TDX_ID_USERPHONE,			// �û���ϵ��ʽ
	TDX_ID_MOBILEPHONE,			// �ƶ��绰
	TDX_ID_USEREMAIL,			// �û�EMAIL
	TDX_ID_USERADDRESS,			// �û�ͨѶ��ַ
};

// ����ֺ���ϸ��ѯ 2158
const WORD tdxKFSJJFHMXCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ
	
	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

// ����ʽ����ǽ���ί�в�ѯ 2162
const WORD tdxKFSJJFJYWTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_KSRQ,				// ��ѯ��ʼ����
	TDX_ID_ZZRQ,				// ��ѯ��������
	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

// ����ʽ����ǽ��׵���ί�в�ѯ 2164
const WORD tdxKFSJJFJYDRWTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

// ����ʽ������տɳ��ܴ����ѯ 2166
const WORD tdxKFSJJFXKCSDMCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_FXBZ,				// ���ձ�־(�ͻ����յȼ�,�ǿղ�ѯָ���ͻ����յȼ���Ӧ�Ļ������)
	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
	TDX_ID_CPBZ,				// ��Ʒ��־
};

// ����ʽ������ʲ�ѯ 2168
const WORD tdxKFSJJFLCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

// ����ʽ�����ڶ���������� 2170
const WORD tdxKFSJJDQDESHSZFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// ����˾����
	TDX_ID_KFSJJ_JJZH,			// �����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// �������

	TDX_ID_KFSJJ_JJFE,			// ����ݶ�(��طݶ�)
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_KFSJJ_MYKKRQ,		// ÿ�¿ۿ�����
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_CZBZ,				// ������־(0--���,1--�޸�)
	TDX_ID_SFFS,				// �շѷ�ʽ
	TDX_ID_XT_MODE,				// ģʽ(�ۿ�����:0--ÿ��,1--ÿ��)
	TDX_ID_WTRQ,				// ί������(�޸�ʱ��Ч)
	TDX_ID_WTBH,				// ί�б��(�޸�ʱ��Ч)
	TDX_ID_LSH,					// ��ˮ��(�޸�ʱ��Ч)
	TDX_ID_XT_REMARK,			// ��ע
	TDX_ID_XT_CHECKRISKFLAG,	// �����ձ�־
	TDX_ID_SHFS,				// ��ط�ʽ
};

// ����ʽ�����ڶ������ȡ�� 2172
const WORD tdxKFSJJDQDESHQXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// ����˾����
	TDX_ID_KFSJJ_JJZH,			// �����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// �������

	TDX_ID_WTBH,				// ί�б��
	TDX_ID_WTRQ,				// ί������
	TDX_ID_LSH,					// ��ˮ��
	TDX_ID_KFSJJ_JJFE,			// ����ݶ�(��طݶ�)
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_KFSJJ_MYKKRQ,		// ÿ�¿ۿ�����
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_SFFS,				// �շѷ�ʽ
	TDX_ID_XT_MODE,				// ģʽ(�ۿ�����:0--ÿ��,1--ÿ��)
	TDX_ID_XT_REMARK,			// ��ע
	TDX_ID_SHFS,				// ��ط�ʽ
};

// ����ʽ�����ڶ�����ز�ѯ 2174
const WORD tdxKFSJJDQDESHCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// ����˾����
	TDX_ID_KFSJJ_JJZH,			// �����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// �������

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

// ����ʽ�����ڶ������Ʒ�� 2176
const WORD tdxKFSJJDQDESHPZFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// ����˾����
	TDX_ID_KFSJJ_JJZH,			// �����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// �������

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

// ����ʽ������������Ϣ��ѯ 2178
const WORD tdxKFSJJDMXGXXCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// ����˾����
	TDX_ID_KFSJJ_JJZH,			// �����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// �������

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

// ����ʽ����˾�����Ϣ��ѯ 2180
const WORD tdxKFSJJGSXGXXCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// ����˾����
	TDX_ID_KFSJJ_JJZH,			// �����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// �������

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

// ����ʽ������˵���ѯ 2182
const WORD tdxKFSJJDZDCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// ����˾����
	TDX_ID_KFSJJ_JJZH,			// �����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// �������

	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

// ����ʽ���𽻸��ѯ 2184
const WORD tdxKFSJJJGDCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// ����˾����
	TDX_ID_KFSJJ_JJZH,			// �����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// �������

	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

//////////////////////////////////////////////////////////////////////////
//	��Ʋ�Ʒ��
//////////////////////////////////////////////////////////////////////////

// ��Ʋ�Ʒ�ݶ��ѯ 2200
const WORD tdxLCCPFECXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ
	
	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������
		
	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
	TDX_ID_CZBZ,				// ������־
	TDX_ID_CPBZ,				// ��Ʒ��־
};

// ��Ʋ�Ʒί�в�ѯ 2202
const WORD tdxLCCPWTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ
	
	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
	TDX_ID_CZBZ,				// ������־
};

// ��Ʋ�Ʒ�ɽ���ѯ 2204
const WORD tdxLCCPCJCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ
	
	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
	TDX_ID_CZBZ,				// ������־

};

// ��Ʋ�Ʒ����ί�в�ѯ 2206
const WORD tdxLCCPDRWTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ
	
	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
	TDX_ID_CZBZ,				// ������־
	TDX_ID_LX,					// (0����ȫ�� 1����ɳ���)
};

// ��Ʋ�Ʒ�����ѯ 2208
const WORD tdxLCCPDMCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ
	
	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
	TDX_ID_CZBZ,				// ������־
};

// ��Ʋ�Ʒ�ʺŲ�ѯ 2210
const WORD tdxLCCPZHCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ
	
	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
	TDX_ID_CZBZ,				// ������־
};

// ��Ʋ�Ʒ���ڶ����깺��ѯ 2212
const WORD tdxLCCPDQDESGCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ
	
	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

// ��Ʋ�Ʒ���ڶ����깺Ʒ�� 2214
const WORD tdxLCCPDQDESGPZFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ
	
	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
	TDX_ID_CZBZ,				// ������־
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

// ��Ʋ�Ʒ��ֵ�ƻ��б��ѯ 2216
const WORD tdxLCCPZZJHLBCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ
	
	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
	TDX_ID_CZZT,				// ����״̬(���ڹ���,��--ȫ��)
};

// ��Ʋ�Ʒ��ֵ�ƻ���Ϣ��ѯ 2218
const WORD tdxLCCPZZJHXXCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
	TDX_ID_XT_CHECKRISKFLAG,	// �����ձ�־(1--����Ƿ�ǩ����Ӻ�ͬ)
	TDX_ID_XT_PARAM,			// ����
};

// ��Ʋ�Ʒ��ֵ�ƻ�������� 2220
const WORD tdxLCCPZZJHJESZFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ
	
	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// �������

	TDX_ID_KFSJJ_JYJE,			// ���׽��
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_XT_PARAM,			// ����
	TDX_ID_XT_REMARK,			// ��ע
	TDX_ID_CZBZ,				// ������־ 0:���� 1:��ͣ
};

// ��Ʋ�Ʒ��ֵ�ƻ�״̬���� 2222
const WORD tdxLCCPZZJHZTSZFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ
	
	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_CZBZ,				// ������־(0--����,1--��ͣ)
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_XT_PARAM,			// ����
	TDX_ID_XT_REMARK,			// ��ע
};

// ��Ʋ�Ʒ��ֵ�ƻ����Э�� 2224
const WORD tdxLCCPZZJHJCXYFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ
	
	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_XT_PARAM,			// ����
	TDX_ID_XT_REMARK,			// ��ע
};

// ��Ʋ�Ʒ��ֵ�ƻ��ݶ��ѯ 2226
const WORD tdxLCCPZZJHFECXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ
	
	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

// ��Ʋ�Ʒ��ֵ�ƻ�������ѯ 2228
const WORD tdxLCCPZZJHCDCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ
	
	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

// ��Ʋ�Ʒ��ֵ�ƻ���Ϣ�޸� 2230
const WORD tdxLCCPZZJHXXXGFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ
	
	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_CZBZ,				// ������־(0--�Ǽǲ�Ʒ;����Ϊ��λ��ʶ[�޸Ķ�Ӧ�ֶ�]:0x1--Э��״̬,0x2--�ʽ������,0x4--��ͣ��Ч�ڽ�ֹ��,0x8--�����Ч�ڽ�ֹ��;0xffffffff[-1]--ȫ���޸�[�ӿ�����ѡ����])
	TDX_ID_CZZT,				// ����״̬(Э��״̬,0--����,1--��ͣ)
	TDX_ID_KFSJJ_JYJE,			// ���׽��(�ʽ������)
	TDX_ID_ZZRQ,				// ��ֹ����(��ͣ��Ч�ڽ�ֹ��)
	TDX_ID_PCRQ,				// ƽ������(�����Ч�ڽ�ֹ��)
	TDX_ID_XT_PARAM,			// ����
	TDX_ID_XT_REMARK,			// ��ע
	TDX_ID_TJRDM,				// �Ƽ��˴���
	TDX_ID_XT_CHECKRISKFLAG,	// �����ձ�־
};

// ��Ʋ�Ʒ��ֵ�ƻ��ݶ���� 2232
const WORD tdxLCCPZZJHFESHFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ
	
	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_KFSJJ_JJFE,			// ��طݶ�
	TDX_ID_SHFS,				// ��ط�ʽ
};

// ��Ʋ�Ʒ��ֵ�ƻ�ί�г��� 2234
const WORD tdxLCCPZZJHWTCDFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ
	
	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_WTRQ,				// ί������
	TDX_ID_WTBH,				// ί�б��
	TDX_ID_XT_PARAM,			// ����
};

// ��Ʋ�Ʒ��ֵ�ƻ�ԤԼȡ����� 2236
const WORD tdxLCCPZZJHYYQKCZFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ
	
	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_CZBZ,				// ������־(0--��ѯ������Ϣ,1--������¼,2--��ѯ�޸���Ϣ,3--�޸ļ�¼,4--��ѯɾ����Ϣ,5--ɾ����¼)
	TDX_ID_XT_PARAM,			// ����(��"��Ʋ�Ʒ��ֵ�ƻ�ԤԼȡ���ѯ 2238"��ͬ��Ӧ���ֶ����Ӧ)
	TDX_ID_WTRQ,				// ί������
	TDX_ID_WTJE,				// ί�н��
};

// ��Ʋ�Ʒ��ֵ�ƻ�ԤԼȡ���ѯ 2238
const WORD tdxLCCPZZJHYYQKCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ
	
	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

// ��Ʋ�Ʒ��ֵ�ƻ���ʷ�����ѯ 2240
const WORD tdxLCCPZZJHLSSYCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ
	
	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

// ������Ʋ�Ʒ�����Ϣ��ѯ 2242
const WORD tdxDQLCCPSHXXCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
	TDX_ID_KFSJJ_FSRQ,			// ��������
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_CZBZ,				// ������־
};

// ��Ʋ�Ʒת�ô����ѯ 2244
const WORD tdxLCCPZRDMCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
	TDX_ID_CZBZ,				// ������־
};

// ��Ʋ�Ʒת�������ѯ 2246
const WORD tdxLCCPZRHQCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
	TDX_ID_CZBZ,				// ������־
};

// ��Ʋ�Ʒת�ó�����ѯ 2248
const WORD tdxLCCPZRCDCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
	TDX_ID_CZBZ,				// ������־
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

// ��Ʋ�Ʒת��ί�в�ѯ 2250
const WORD tdxLCCPZRWTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
	TDX_ID_CZBZ,				// ������־
};

// ��Ʋ�Ʒת�óɽ���ѯ 2252
const WORD tdxLCCPZRCJCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
	TDX_ID_CZBZ,				// ������־
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

// ��Ʋ�ƷǩԼ��Լ��ѯ 2254
const WORD tdxLCCPQYJYCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_CZBZ,				// ������־
};

// ������Ʋ�Ʒ�����ѯ 2256
const WORD tdxYHLCCPDMCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
	TDX_ID_CZBZ,				// ������־
};

// ������Ʋ�Ʒ�ݶ��ѯ 2258
const WORD tdxYHLCCPFECXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
	TDX_ID_CZBZ,				// ������־
};

// ������Ʋ�Ʒί�в�ѯ 2260
const WORD tdxYHLCCPWTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
	TDX_ID_CZBZ,				// ������־
};

// ������Ʋ�Ʒ�ʺŲ�ѯ 2262
const WORD tdxYHLCCPZHCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
	TDX_ID_CZBZ,				// ������־
};

// ������Ʋ�Ʒ�ɽ���ѯ 2264
const WORD tdxYHLCCPCJCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
	TDX_ID_CZBZ,				// ������־
};

// OTC�ݶ��ѯ 2266
const WORD tdxOTCFECXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

// OTC�������ѯ 2268
const WORD tdxOTCRSSCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����

	TDX_ID_CZBZ,				// �������
	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

// OTC�����걨��ѯ 2270
const WORD tdxOTCYXSBCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����

	TDX_ID_CZBZ,				// �������
	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

// OTC�ɽ��걨��ѯ 2272
const WORD tdxOTCCJSBCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ
	
	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
	
	TDX_ID_CZBZ,				// �������
	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

// OTC��Ʒ��Լ��ѯ 2274
const WORD tdxOTCCPHYCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

// OTC������Ϣ��ѯ 2276
const WORD tdxOTCBJXXCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

// OTC������Ϣ��ѯ 2278
const WORD tdxOTCHQXXCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����	
	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

// OTC���Ӻ�ͬ�б��ѯ 2280
const WORD tdxOTCDZHTLBCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

// OTC���Ӻ�ͬ��ѯ 2282
const WORD tdxOTCDZHTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// (����)�������

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

// ���в�Ʒ�����ѯ 2300
const WORD tdxXTCPDMCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_XTCPDM,				// (����)���в�Ʒ����

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

// ���в�Ʒ�ݶ��ѯ 2302
const WORD tdxXTCPFECXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_XTCPDM,				// (����)���в�Ʒ����

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

// ���в�Ʒ�ʺŲ�ѯ 2304
const WORD tdxXTCPZHCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_XTCPDM,				// (����)���в�Ʒ����

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

// ���в�Ʒί�в�ѯ 2306
const WORD tdxXTCPWTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_XTCPDM,				// (����)���в�Ʒ����

	TDX_ID_KSRQ,				// ��ѯ��ʼ����
	TDX_ID_ZZRQ,				// ��ѯ��������
	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

// ���в�Ʒ�ɽ���ѯ 2308
const WORD tdxXTCPCJCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_XTCPDM,				// (����)���в�Ʒ����

	TDX_ID_KSRQ,				// ��ѯ��ʼ����
	TDX_ID_ZZRQ,				// ��ѯ��������
	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

// ���в�Ʒ��ʷί�в�ѯ 2310
const WORD tdxXTCPLSWTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// (����)����˾����
	TDX_ID_KFSJJ_JJZH,			// (����)�����ʺŴ���
	TDX_ID_XTCPDM,				// (����)���в�Ʒ����
	
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

//////////////////////////////////////////////////////////////////////////
//	����ֱ��
//////////////////////////////////////////////////////////////////////////

// ����ֱ���Ϲ�	2500
const WORD tdxJJZXRGFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// ����˾����
	TDX_ID_KFSJJ_JJZH,			// �����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// �������

	TDX_ID_KFSJJ_JYJE,			// �Ϲ�/�깺���
	TDX_ID_KFSJJ_JJFE,			// ��طݶ�
	TDX_ID_KFSJJ_FSRQ,			// (Ԥ�깺���/ԤԼ�Ϲ�)��������

	TDX_ID_SHFS,				// (���/ԤԼ���)�޶���ط�ʽ
	TDX_ID_TJRDM,				// (��ѡ)(�깺/�Ϲ�)�Ƽ��˴���
	TDX_ID_BANKCODE,			// ���д���	
	TDX_ID_IDENTITYCARD,		// ���֤
	TDX_ID_SFFS,				// �շѷ�ʽ
	TDX_ID_XT_CHECKRISKFLAG,	// �����ձ�־
};

// ����ֱ���깺	2502
const WORD tdxJJZXSGFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// ����˾����
	TDX_ID_KFSJJ_JJZH,			// �����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// �������

	TDX_ID_KFSJJ_JYJE,			// �Ϲ�/�깺���
	TDX_ID_KFSJJ_JJFE,			// ��طݶ�
	TDX_ID_KFSJJ_FSRQ,			// (Ԥ�깺���/ԤԼ�Ϲ�)��������

	TDX_ID_SHFS,				// (���/ԤԼ���)�޶���ط�ʽ
	TDX_ID_TJRDM,				// (��ѡ)(�깺/�Ϲ�)�Ƽ��˴���
	TDX_ID_IDENTITYCARD,		// ���֤
	TDX_ID_SFFS,				// �շѷ�ʽ
	TDX_ID_XT_CHECKRISKFLAG,	// �����ձ�־
};

// ����ֱ�����	2504
const WORD tdxJJZXSHFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// ����˾����
	TDX_ID_KFSJJ_JJZH,			// �����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// �������

	TDX_ID_KFSJJ_JYJE,			// �Ϲ�/�깺���
	TDX_ID_KFSJJ_JJFE,			// ��طݶ�
	TDX_ID_KFSJJ_FSRQ,			// (Ԥ�깺���/ԤԼ�Ϲ�)��������

	TDX_ID_SHFS,				// (���/ԤԼ���)�޶���ط�ʽ
	TDX_ID_TJRDM,				// (��ѡ)(�깺/�Ϲ�)�Ƽ��˴���
	TDX_ID_IDENTITYCARD,		// ���֤
	TDX_ID_SFFS,				// �շѷ�ʽ
	TDX_ID_XT_CHECKRISKFLAG,	// �����ձ�־
};

// ����ֱ���ֺ�	2506
const WORD tdxJJZXFHFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// ����˾����
	TDX_ID_KFSJJ_JJZH,			// �����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// �������
	
	TDX_ID_KFSJJ_DIVIDENMETHOD,	// �·ֺ췽ʽ 0,����ת�� 1,�ֽ�ֺ�
	TDX_ID_SFFS,				// �շѷ�ʽ
};

// ����ֱ��ת��	2508
const WORD tdxJJZXZHFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// ����˾����
	TDX_ID_KFSJJ_JJZH,			// �����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// �������(ת������)

	TDX_ID_KFSJJ_ZHDM,			// ת������(ת�����)
	TDX_ID_KFSJJ_JYJE,			// ���׽��(ת���ݶ�)

	TDX_ID_SHFS,				// �޶���ط�ʽ: 0,���ȡ�� 1,���˳��
	TDX_ID_SFFS,				// �շѷ�ʽ(ת������)
	TDX_ID_XT_CHECKRISKFLAG,	// �����ձ�־
};

// ����ֱ��ת�й� 2510
const WORD tdxJJZXZTGFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// ����˾����
	TDX_ID_KFSJJ_JJZH,			// �����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// �������(ת������)

	TDX_ID_KFSJJ_ZHDM,			// ת������(ת�����)
	TDX_ID_KFSJJ_JYJE,			// ���׽��(ת���ݶ�)

	TDX_ID_SHFS,				// �޶���ط�ʽ: 0,���ȡ�� 1,���˳��
	TDX_ID_SFFS,				// �շѷ�ʽ(ת������)
	TDX_ID_XT_CHECKRISKFLAG,	// �����ձ�־
};

// ����ֱ������ 2512
const WORD tdxJJZXCDFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// ����˾����
	TDX_ID_KFSJJ_JJZH,			// �����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// �������
	
	TDX_ID_WTRQ,				// ί���ύ����
	TDX_ID_KFSJJ_JJFE,			// ί���ύ�ݶ�
	TDX_ID_KFSJJ_JYJE,			// ί���ύ���
	TDX_ID_WTBH,				// ί�б��
	TDX_ID_SFFS,				// �շѷ�ʽ
};

// ����ֱ�����ʲ�ѯ 2514
const WORD tdxJJZXFLCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// ����˾����
	TDX_ID_KFSJJ_JJZH,			// �����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// �������

	TDX_ID_YZZZ_YHDM,			// ���д���(�������)
	TDX_ID_JYZH,				// �����˺�
	TDX_ID_KFSJJ_ZHDM,			// ת������
	TDX_ID_KFSJJ_JJFE,			// ί���ύ�ݶ�
	TDX_ID_KFSJJ_JYJE,			// ί���ύ���
	TDX_ID_KFSJJ_MMBZ,			// ����������־
	TDX_ID_SFFS,				// �շѷ�ʽ
	TDX_ID_LX,					// ����(�������,0--ȫ��,1--������,2--ӡ��˰,3--������,5--����ۿ���,9--Ĭ���ۿ���,����--δ����)
};

// ����ֱ������֧�� 2516
const WORD tdxJJZXYHZFFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// ����˾����
	TDX_ID_KFSJJ_JJZH,			// �����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// �������

	TDX_ID_YZZZ_YHDM,			// ���д���(�������)
	TDX_ID_JYZH,				// �����˺�
	TDX_ID_KFSJJ_JJFE,			// ί���ύ�ݶ�
	TDX_ID_KFSJJ_JYJE,			// ί���ύ���
	TDX_ID_KFSJJ_MMBZ,			// ����������־
	TDX_ID_ZJLB,				// ֤�����
	TDX_ID_ZJHM,				// ֤������
	TDX_ID_WTBH,				// ί�б��
	TDX_ID_YZZZ_YHZH,			// �����˺�(Ͷ�����˻�)
	TDX_ID_KHMC,				// �ͻ�����(Ͷ��������)
	TDX_ID_KFSJJ_JJMC,			// ��������
	TDX_ID_XT_PARAM,			// ����
};

// ����ֱ�������˴����ѯ 2518
const WORD tdxJJZXXSRDMCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// ����˾����
	TDX_ID_KFSJJ_JJZH,			// �����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// �������

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

// ����ֱ����Ϣ��� 2520
const WORD tdxJJZXXXJCFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// ����˾����
	TDX_ID_KFSJJ_JJZH,			// �����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// �������

	TDX_ID_CZBZ,				// ������־(0--��������ǳ�,1--�޸����ϼ���ǳ�)
	TDX_ID_XT_PARAM,			// ����
	TDX_ID_NC,					// �ǳ�
};

// ���������ڻ�������ѯ 2850
const WORD tdxJYSCNJJDMCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// ����˾����
	TDX_ID_KFSJJ_JJZH,			// �����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// �������

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
	TDX_ID_CZBZ,				// ������־
	TDX_ID_XT_PARAM,			// ����
};

// ���������ڻ���ɷֹɲ�ѯ 2852
const WORD tdxJYSCNJJCFGCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KFSJJ_JJGSDM,		// ����˾����
	TDX_ID_KFSJJ_JJZH,			// �����ʺŴ���
	TDX_ID_KFSJJ_JJDM,			// �������

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
	TDX_ID_CZBZ,				// ������־
	TDX_ID_XT_PARAM,			// ����
};

//////////////////////////////////////////////////////////////////////////
//	ETF
//////////////////////////////////////////////////////////////////////////

// ETF�Ϻ��羳�깺���ײ�ѯ 2950
const WORD tdxETFSHKJSGPTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

// ETF���ڿ羳�깺���ײ�ѯ 2952
const WORD tdxETFSZKJSGPTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

// ETF�Ϻ��羳������ײ�ѯ 2954
const WORD tdxETFSHKJSHPTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

// ETF���ڿ羳������ײ�ѯ 2956
const WORD tdxETFSZKJSHPTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

// ETF�Ϻ��羳ί�г�����ѯ 2958
const WORD tdxETFSHKJWTCDCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

// ETF���ڿ羳ί�г�����ѯ 2960
const WORD tdxETFSZKJWTCDCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

// ETF�Ϻ��羳����ί�в�ѯ 2962
const WORD tdxETFSHKJDRWTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

// ETF���ڿ羳����ί�в�ѯ 2964
const WORD tdxETFSZKJDRWTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

// ETF�Ϻ��羳���ճɽ���ѯ 2966
const WORD tdxETFSHKJDRCJCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

// ETF���ڿ羳���ճɽ���ѯ 2968
const WORD tdxETFSZKJDRCJCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

// ETF�Ϻ��羳��ʷί�в�ѯ 2970
const WORD tdxETFSHKJLSWTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

// ETF���ڿ羳��ʷί�в�ѯ 2972
const WORD tdxETFSZKJLSWTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

// ETF�Ϻ��羳��ʷ�ɽ���ѯ 2974
const WORD tdxETFSHKJLSCJCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

// ETF���ڿ羳��ʷ�ɽ���ѯ 2976
const WORD tdxETFSZKJLSCJCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

// ETF�����ֽ��Ϲ����ײ�ѯ 2980
const WORD tdxETFWXXJRGPTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

// ETF���¹ɷ��Ϲ����ײ�ѯ 2982
const WORD tdxETFWXGFRGPTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
	TDX_ID_ETFDM,				// ETF����
};

// ETF�����ֽ��Ϲ�������ѯ 2984
const WORD tdxETFWXXJRGCDCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

// ETF���¹ɷ��Ϲ�������ѯ 2986
const WORD tdxETFWXGFRGCDCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

// ETF�����ֽ��Ϲ���Ϣ��ѯ 2988
const WORD tdxETFWXXJRGXXCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

// ETF���¹ɷ��Ϲ���Ϣ��ѯ 2990
const WORD tdxETFWXGFRGXXCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

// ETF�����ֽ��Ϲ���ˮ��ѯ 2992
const WORD tdxETFWXXJRGLSCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

// ETF���¹ɷ��Ϲ���ˮ��ѯ 2994
const WORD tdxETFWXGFRGLSCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

// ETF���� 3000
const WORD tdxETFMMFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_ETFMMBS,				// 0,�깺,1,���,2,��Ʊ�Ϲ�,3,�ֽ��Ϲ�
	TDX_ID_ETFDM,				// ETF����(ע:���ﲻ����֤ȯ����)
	TDX_ID_ZQDM,				// ��Ʊ����(��Ʊ�Ϲ�ʱ,���ֶ���Ч)
	TDX_ID_WTJG,				// (����)ί�м۸�
	TDX_ID_ETFRGSL,				// ����
	TDX_ID_DFZHLB,				// �Է��ʺ����
	TDX_ID_DFGDDM,				// �Է��ɶ�����
	TDX_ID_TJRDM,				// �Ƽ��˴���
};

// ETF��Ϣ��ѯ 3002
const WORD tdxETFXXCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ
	
	TDX_ID_ETFMMBS,				// 0,�깺,1,���,2,��Ʊ�Ϲ�,3,�ֽ��Ϲ�
	TDX_ID_ETFDM,				// ETF����(ע:���ﲻ����֤ȯ����)
	TDX_ID_ZQDM,				// ��Ʊ����(��Ʊ�Ϲ�ʱ,���ֶ���Ч)
	TDX_ID_WTJG,				// (����)ί�м۸�
	TDX_ID_DFZHLB,				// �Է��ʺ����
	TDX_ID_DFGDDM,				// �Է��ɶ�����
	TDX_ID_KFSJJ_JJDM,			// �������(����ͬʱ����"�Ϲ�����"/"�������"ʱ,����"�������")
};

// ETF�Ϲ���ѯ 3004
const WORD tdxETFRGCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
	TDX_ID_QSRQ,				// ��������
};

// ETF�Ϲ����� 3006
const WORD tdxETFRGCDFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_ZSDM,				// ָ������
	TDX_ID_PCH,					// ���κ�
	TDX_ID_QSRQ,				// ��������
	TDX_ID_WTBH,				// ί�б��
	TDX_ID_ETFMMBS,				// ETF������ʶ
	TDX_ID_ZQDM,				// ֤ȯ����(�ɷֹɴ���)
	TDX_ID_CDSL,				// ��������
};

// ETF���κ� 3008
const WORD tdxETFPCHFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

// ETF��Ʊ������ 3010
const WORD tdxETFGPLMMFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ
	
	TDX_ID_MMBZ,				// 0,����,1,����
	TDX_ID_ETFDM,				// ETF����
	TDX_ID_PCH,					// ���κ�
	TDX_ID_QSRQ,				// ��������
	TDX_ID_CLDM,				// ���Դ���
	TDX_ID_ZSDM,				// ָ������
	TDX_ID_ZQDM,				// ֤ȯ����
	TDX_ID_WTJG,				// ί�м۸�
	TDX_ID_WTSL,				// ί������
	TDX_ID_BLSL,				// ��������
	TDX_ID_CZBZ,				// (����)������־
};

// ETF��Ʊ����ѯ 3012
const WORD tdxETFGPLCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ
	
	TDX_ID_ETFDM,				// ETF����
	TDX_ID_ZSDM,				// ָ������
	TDX_ID_MMBZ,				// ������־
	TDX_ID_PCH,					// ���κ�
	TDX_ID_QSRQ,				// ��������
	TDX_ID_WTSL,				// ί������
	TDX_ID_WTJG,				// ί�м۸�
	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
	
	TDX_ID_CZBZ,				// ������־(�Ƿ�ʹ�ÿ��:1--��,2--��)
};

// ETFӵ�ɲ�ѯ 3014
const WORD tdxETFYGCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ
	
	TDX_ID_ETFDM,				// ETF����
	TDX_ID_ZSDM,				// ָ������(ͬETF����)
	TDX_ID_PCH,					// ���κ�
	TDX_ID_QSRQ,				// ��������
	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
	TDX_ID_WTSL,				// ί������
};

// ETFί�в�ѯ 3016
const WORD tdxETFWTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_PCH,					// 0:������ ������Ӧ
	TDX_ID_ZSDM,				// ָ������(ͬETF����)
	TDX_ID_ETFDM,				// ETF����
	TDX_ID_KSRQ,				// ��ѯ��ʼ����
	TDX_ID_ZZRQ,				// ��ѯ��ֹ����
	TDX_ID_CZBZ,				// 0,������ 1,��ɳ���ί��
	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

// ETF�ɽ���ѯ 3018
const WORD tdxETFCJCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_WTRQ,				// ί������
	TDX_ID_ZSDM,				// ָ������
	TDX_ID_PCH,					// ���κ�
	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

// ETF���Բ�ѯ 3020
const WORD tdxETFCLCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ
};

// ETFָ�������ѯ 3022
const WORD tdxETFZSDMCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_ZSDM,				// ָ������
	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

// ETF(ί��)ȷ�� 3024
const WORD tdxETFQRFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_PCH,					// ���κ�
	TDX_ID_CLDM,				// ���Դ���
	TDX_ID_ZSDM,				// ָ������
	TDX_ID_CZBZ,				// ������־(0--�����κŴ���(������ָ�����봦��),1--����,2--ƽ��,3--����,4--���,Ĭ��--0)
	TDX_ID_WTSL,				// ί������(��������)
	TDX_ID_JGBZ,				// �۸��־
	TDX_ID_MZL,					// ������
};

// ETFί�в�ѯ��ϸ 3026
const WORD tdxETFWTCXMXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_ZSDM,				// ָ������
	TDX_ID_PCH,					// ���κ�
	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

// ETF�Ϲ�������ѯ 3028
const WORD tdxETFRGCDCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
	TDX_ID_QSRQ,				// ��������
};

// ETFָ���ɷֲ�ѯ 3030
const WORD tdxETFZSCFCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_ZSDM,				// ָ������
	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

// ETF�ɷݲ�ѯ 3032
const WORD tdxETFGFCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_ZQDM,				// ֤ȯ����(�ǿղ�ָ������)
	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

// ETF���깺�ɷֹɲ�ѯ 3034
const WORD tdxETFKSGCFGCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_ZSDM,				// ָ������
	TDX_ID_WTSL,				// ί������(��������)
	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
};

// ETF��Ʊ������ 3036
const WORD tdxETFGPLCDFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_ZSDM,				// ָ������
	TDX_ID_PCH,					// ���κ�
	TDX_ID_WTRQ,				// ί������
};

// ETF��Ʊ��������ѯ 3038
const WORD tdxETFGPLCDCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
	TDX_ID_ZSDM,				// ָ������
};

// ETF���г����̲�ѯ 3040
const WORD tdxETFKSCDPCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼ���
	TDX_ID_ZSDM,				// ָ������
	TDX_ID_CJRQ,				// �ɽ�����
};

//////////////////////////////////////////////////////////////////////////
//	���ͨ
//////////////////////////////////////////////////////////////////////////

// ���ͨ���κ� 3050
const WORD tdxZHTPCHFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ
};

// ���ͨ��Ʊ������ 3052
const WORD tdxZHTGPLMMFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ
	
	TDX_ID_PCH,					// ���κ�
	TDX_ID_QSRQ,				// ��������
	TDX_ID_CLDM,				// ���Դ���
	TDX_ID_ZSDM,				// ָ������
	TDX_ID_ZQDM,				// ֤ȯ����
	TDX_ID_WTJG,				// ί�м۸�
	TDX_ID_WTSL,				// ί������
	TDX_ID_BLSL,				// ��������

	TDX_ID_XT_PARAM,			// ����
};

// ���ͨ��Ʊ����ѯ 3054
const WORD tdxZHTGPLCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_ZSDM,				// ָ������
	TDX_ID_PCH,					// ���κ�
	TDX_ID_QSRQ,				// ��������
	TDX_ID_MMBZ,				// ������־
	TDX_ID_WTSL,				// ί������
	TDX_ID_WTJG,				// ί�м۸�
	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��

	TDX_ID_ZHDM,				// ��ϴ���
};

// ���ͨӵ�ɲ�ѯ 3056
const WORD tdxZHTYGCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_ZSDM,				// ָ������
	TDX_ID_PCH,					// ���κ�
	TDX_ID_CZBZ,				// ������־(0����ѯȫ�� 1���ɳ��� 2����ת��)

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��
};

// ���ͨί�в�ѯ 3058
const WORD tdxZHTWTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_ZSDM,				// ָ������
	TDX_ID_PCH,					// ���κ�

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��
};

// ���ͨ�ɽ���ѯ 3060
const WORD tdxZHTCJCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_ZQDM,				// ָ������
	TDX_ID_PCH,					// ���κ�
	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��
};

// ���ͨ���Բ�ѯ 3062
const WORD tdxZHTCLCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��
};

// ���ָͨ�������ѯ 3064
const WORD tdxZHTZSDMCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_ZSDM,				// ָ������

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��
};

// ���ͨȷ�� 3066
const WORD tdxZHTQRFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_PCH,					// ���κ�
	TDX_ID_CLDM,				// ���Դ���
};

// ���ͨ��ʷ��ѯ 3068
const WORD tdxZHTLSCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_KSRQ,				// ��ѯ��ʼ����
	TDX_ID_ZZRQ,				// ��ѯ��ֹ����
	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��
};

// ���ͨ��ʷ��ѯ��ϸ 3070
const WORD tdxZHTLSCXMXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_ZSDM,				// ָ������
	TDX_ID_PCH,					// ���κ�
	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��
	
	TDX_ID_QSRQ,				// ��������
	TDX_ID_KSRQ,				// ��ѯ��ʼ����
	TDX_ID_ZZRQ,				// ��ѯ��ֹ����
};

// ���ͨί�в�ѯ��ϸ 3072
const WORD tdxZHTWTCXMXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_ZSDM,				// ָ������
	TDX_ID_PCH,					// ���κ�

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��
};

// ���ͨ�ɽ���ѯ��ϸ 3074
const WORD tdxZHTCJCXMXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_ZSDM,				// ָ������
	TDX_ID_PCH,					// ���κ�
	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��

	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

// ���ָͨ���ɷֲ�ѯ 3076
const WORD tdxZHTZSCFCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_ZSDM,				// ָ������
	TDX_ID_PCH,					// ���κ�
	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��
};

// (����)��ȡ�Ự�� 3100
const WORD tdxTLHQHHHFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_DFKHDM,				// �Է��ͻ�����
	TDX_ID_DFMM,				// �Է�����
	TDX_ID_DFZJZH,				// �Է��ʽ��˺�
	TDX_ID_DFZHLB,				// �Է��˺����
	TDX_ID_DFGDDM,				// �Է��ɶ�����
	TDX_ID_XHZHLX,				// �ֻ��˺�����
};

// (����)��ϴ����ѯ 3102
const WORD tdxTLZHDMCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_DFKHDM,				// �Է��ͻ�����
	TDX_ID_DFMM,				// �Է�����
	TDX_ID_DFZJZH,				// �Է��ʽ��˺�
	TDX_ID_DFZHLB,				// �Է��˺����
	TDX_ID_DFGDDM,				// �Է��ɶ�����
	TDX_ID_XHZHLX,				// �ֻ��˺�����

	TDX_ID_XT_TOKEN,			// ����
	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��
	TDX_ID_ZHDM,				// ��ϴ���
};

// (����)��ϳɷֲ�ѯ 3104
const WORD tdxTLZHCFCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_DFKHDM,				// �Է��ͻ�����
	TDX_ID_DFMM,				// �Է�����
	TDX_ID_DFZJZH,				// �Է��ʽ��˺�
	TDX_ID_DFZHLB,				// �Է��˺����
	TDX_ID_DFGDDM,				// �Է��ɶ�����
	TDX_ID_XHZHLX,				// �ֻ��˺�����

	TDX_ID_XT_TOKEN,			// ����
	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��
	TDX_ID_ZHDM,				// ��ϴ���
	TDX_ID_ZQDM,				// ֤ȯ����
};

// (����)��ϴ������ 3106
const WORD tdxTLZHDMCZFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_DFKHDM,				// �Է��ͻ�����
	TDX_ID_DFMM,				// �Է�����
	TDX_ID_DFZJZH,				// �Է��ʽ��˺�
	TDX_ID_DFZHLB,				// �Է��˺����
	TDX_ID_DFGDDM,				// �Է��ɶ�����
	TDX_ID_XHZHLX,				// �ֻ��˺�����

	TDX_ID_XT_TOKEN,			// ����
	TDX_ID_CZBZ,				// ������־(0--����,1--ɾ��)
	TDX_ID_ZHDM,				// ��ϴ���
	TDX_ID_ZHMC,				// �������
	TDX_ID_ZHLX,				// �������
	TDX_ID_QZFS,				// Ȩ�ط�ʽ
	TDX_ID_DWSZ,				// ��λ��ֵ
	TDX_ID_XYJYBS,				// ���ý��ױ�ʶ
};

// (����)��ϳɷֲ��� 3108
const WORD tdxTLZHCFCZFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_DFKHDM,				// �Է��ͻ�����
	TDX_ID_DFMM,				// �Է�����
	TDX_ID_DFZJZH,				// �Է��ʽ��˺�
	TDX_ID_DFZHLB,				// �Է��˺����
	TDX_ID_DFGDDM,				// �Է��ɶ�����
	TDX_ID_XHZHLX,				// �ֻ��˺�����

	TDX_ID_XT_TOKEN,			// ����
	TDX_ID_CZBZ,				// ������־(0--����,1--ɾ��)
	TDX_ID_ZHDM,				// ��ϴ���
	TDX_ID_ZQDM,				// ֤ȯ����
	TDX_ID_ZQMC,				// ֤ȯ����
	TDX_ID_CFQZ,				// �ɷ�Ȩ��
	TDX_ID_CFSL,				// �ɷ�����
	TDX_ID_XYJYBS,				// ���ý��ױ�ʶ
};

// (����)���Դ����ѯ 3110
const WORD tdxTLCLDMCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_DFKHDM,				// �Է��ͻ�����
	TDX_ID_DFMM,				// �Է�����
	TDX_ID_DFZJZH,				// �Է��ʽ��˺�
	TDX_ID_DFZHLB,				// �Է��˺����
	TDX_ID_DFGDDM,				// �Է��ɶ�����
	TDX_ID_XHZHLX,				// �ֻ��˺�����

	TDX_ID_XT_TOKEN,			// ����
	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��
	TDX_ID_CLDM,				// ���Դ���
};

// (����)���Գɷֲ�ѯ 3112
const WORD tdxTLCLCFCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_DFKHDM,				// �Է��ͻ�����
	TDX_ID_DFMM,				// �Է�����
	TDX_ID_DFZJZH,				// �Է��ʽ��˺�
	TDX_ID_DFZHLB,				// �Է��˺����
	TDX_ID_DFGDDM,				// �Է��ɶ�����
	TDX_ID_XHZHLX,				// �ֻ��˺�����

	TDX_ID_XT_TOKEN,			// ����
	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��
	TDX_ID_CLDM,				// ���Դ���
	TDX_ID_ZQDM,				// ֤ȯ����
};

// (����)���Դ������ 3114
const WORD tdxTLCLDMCZFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_DFKHDM,				// �Է��ͻ�����
	TDX_ID_DFMM,				// �Է�����
	TDX_ID_DFZJZH,				// �Է��ʽ��˺�
	TDX_ID_DFZHLB,				// �Է��˺����
	TDX_ID_DFGDDM,				// �Է��ɶ�����
	TDX_ID_XHZHLX,				// �ֻ��˺�����

	TDX_ID_XT_TOKEN,			// ����
	TDX_ID_CZBZ,				// ������־
	TDX_ID_CLDM,				// ���Դ���
	TDX_ID_CLMC,				// ��������
	TDX_ID_HYDM,				// ��Լ����
	TDX_ID_QZFS,				// ȯ�ַ�ʽ
	TDX_ID_ZHDM,				// ��ϴ���
	TDX_ID_WTJE,				// ί�н��
	TDX_ID_MRJEJSJZ,			// ����������׼
};

// (����)���Գɷֲ��� 3116
const WORD tdxTLCLCFCZFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_DFKHDM,				// �Է��ͻ�����
	TDX_ID_DFMM,				// �Է�����
	TDX_ID_DFZJZH,				// �Է��ʽ��˺�
	TDX_ID_DFZHLB,				// �Է��˺����
	TDX_ID_DFGDDM,				// �Է��ɶ�����
	TDX_ID_XHZHLX,				// �ֻ��˺�����

	TDX_ID_XT_TOKEN,			// ����
	TDX_ID_CZBZ,				// ������־
	TDX_ID_CLDM,				// ���Դ���
	TDX_ID_ZQDM,				// ֤ȯ����
	TDX_ID_ZQMC,				// ֤ȯ����
	TDX_ID_CFQZ,				// �ɷ�Ȩ��
	TDX_ID_CFSL,				// �ɷ�����
	TDX_ID_XYJYBS,				// ���ý��ױ�ʶ
};

// (����)���Ų��� 3118
const WORD tdxTLPHCZFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_DFKHDM,				// �Է��ͻ�����
	TDX_ID_DFMM,				// �Է�����
	TDX_ID_DFZJZH,				// �Է��ʽ��˺�
	TDX_ID_DFZHLB,				// �Է��˺����
	TDX_ID_DFGDDM,				// �Է��ɶ�����
	TDX_ID_XHZHLX,				// �ֻ��˺�����

	TDX_ID_XT_TOKEN,			// ����
	TDX_ID_CZBZ,				// ������־(0--����,1--����,2--��ͣ���׹�Ʊ,3--�ָ����׹�Ʊ)
	TDX_ID_ZQDM,				// ֤ȯ����
	TDX_ID_PCH,					// ���κ�
	TDX_ID_PCHLX,				// ���κ�����
	TDX_ID_ZHDM,				// ��ϴ���
	TDX_ID_CLDM,				// ���Դ���
	TDX_ID_DKBZ,				// ��ձ�־
	TDX_ID_TZSL,				// Ͷ������
	TDX_ID_BJFS,				// ���۷�ʽ
	TDX_ID_DFBJFS,				// �Է����۷�ʽ
	TDX_ID_MCYGBJ,				// ������ɱ��
	TDX_ID_SYKCBJ,				// ʹ�ÿ����
	TDX_ID_SYFZXHBJ,			// ʹ�ø����ֻ����
	TDX_ID_ZDWTBJ,				// �Զ�ί�б��
	TDX_ID_ZDWTCS,				// �Զ�ί�д���
	TDX_ID_ZQMC,				// ֤ȯ����
};

// (����)���Ų�ѯ 3120
const WORD tdxTLPHCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_DFKHDM,				// �Է��ͻ�����
	TDX_ID_DFMM,				// �Է�����
	TDX_ID_DFZJZH,				// �Է��ʽ��˺�
	TDX_ID_DFZHLB,				// �Է��˺����
	TDX_ID_DFGDDM,				// �Է��ɶ�����
	TDX_ID_XHZHLX,				// �ֻ��˺�����

	TDX_ID_XT_TOKEN,			// ����
	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��
	TDX_ID_PCH,					// ���κ�
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_CZZT,				// ����״̬
};

// (����)����ί���б� 3122
const WORD tdxTLPHWTLBFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_DFKHDM,				// �Է��ͻ�����
	TDX_ID_DFMM,				// �Է�����
	TDX_ID_DFZJZH,				// �Է��ʽ��˺�
	TDX_ID_DFZHLB,				// �Է��˺����
	TDX_ID_DFGDDM,				// �Է��ɶ�����
	TDX_ID_XHZHLX,				// �ֻ��˺�����

	TDX_ID_XT_TOKEN,			// ����
	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��
	TDX_ID_PCH,					// ���κ�
	TDX_ID_PCHRQ,				// ���κ�����
	TDX_ID_CZBZ,				// ������־(0--Ĭ��,1--����,2--ƽ��,3--����,4--����)
	TDX_ID_ZHDM,				// ��ϴ���
	TDX_ID_BJFS,				// ���۷�ʽ
	TDX_ID_DFBJFS,				// �Է����۷�ʽ
	TDX_ID_MCYGBJ,				// ������ɱ��
};

// (����)����ί��ִ�� 3124
const WORD tdxTLPHWTZXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_DFKHDM,				// �Է��ͻ�����
	TDX_ID_DFMM,				// �Է�����
	TDX_ID_DFZJZH,				// �Է��ʽ��˺�
	TDX_ID_DFZHLB,				// �Է��˺����
	TDX_ID_DFGDDM,				// �Է��ɶ�����
	TDX_ID_XHZHLX,				// �ֻ��˺�����

	TDX_ID_XT_TOKEN,			// ����
	TDX_ID_PCH,					// ���κ�
	TDX_ID_PCHRQ,				// ���κ�����
	TDX_ID_CZBZ,				// ������־
	TDX_ID_ZHDM,				// ��ϴ���
	TDX_ID_JC,					// ����
	TDX_ID_LX,					// ����
	TDX_ID_BJFS,				// ���۷�ʽ
	TDX_ID_DFBJFS,				// �Է����۷�ʽ
	TDX_ID_MCYGBJ,				// ������ɱ��
};

// (����)����ί�в�ѯ 3126
const WORD tdxTLPHWTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_DFKHDM,				// �Է��ͻ�����
	TDX_ID_DFMM,				// �Է�����
	TDX_ID_DFZJZH,				// �Է��ʽ��˺�
	TDX_ID_DFZHLB,				// �Է��˺����
	TDX_ID_DFGDDM,				// �Է��ɶ�����
	TDX_ID_XHZHLX,				// �ֻ��˺�����

	TDX_ID_XT_TOKEN,			// ����
	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��
	TDX_ID_PCH,					// ���κ�
};

// (����)���ųֲֲ�ѯ 3128
const WORD tdxTLPHCCCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_DFKHDM,				// �Է��ͻ�����
	TDX_ID_DFMM,				// �Է�����
	TDX_ID_DFZJZH,				// �Է��ʽ��˺�
	TDX_ID_DFZHLB,				// �Է��˺����
	TDX_ID_DFGDDM,				// �Է��ɶ�����
	TDX_ID_XHZHLX,				// �ֻ��˺�����

	TDX_ID_XT_TOKEN,			// ����
	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��
	TDX_ID_PCH,					// ���κ�
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

// (�㷨����)�������� 3190
const WORD tdxSFJYDDCZFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_CZBZ,				// ������־(0--����,1--�޸�,3--����,����--��֧��)
	TDX_ID_ZQDM,				// ֤ȯ����
	TDX_ID_XT_MODE,				// ģʽ(�㷨����)
	TDX_ID_XT_PARAM,			// ����(�㷨������)
	TDX_ID_LSH,					// ��ˮ��(�㷨�������)
};

// (�㷨����)�����б��ѯ 3192
const WORD tdxSFJYDDLBCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��
	TDX_ID_LSH,					// ��ˮ��(�㷨�������,��--ȫ��)
	TDX_ID_KGDBZ,				// �ɸĵ���־(0--ȫ��,1--ֻ���ؿɸĵ�,Ĭ��--0)
	TDX_ID_KCDBZ,				// �ɳ�����־(0--ȫ��,1--ֻ���ؿɳ���,Ĭ��--0)
	TDX_ID_CDBZ,				// ������־(0--ȫ��,1--ֻ����δ����,Ĭ��--0)
	TDX_ID_XT_MODE,				// ģʽ(�㷨����)
	TDX_ID_CZBZ,				// ������־
};

// (�㷨����)���������ѯ 3194
const WORD tdxSFJYDDJGCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��
	TDX_ID_LSH,					// ��ˮ��(�㷨�������,��--ȫ��)
	TDX_ID_XT_MODE,				// ģʽ(�㷨����)
	TDX_ID_CZBZ,				// ������־
};

//////////////////////////////////////////////////////////////////////////
//	���ý���
//////////////////////////////////////////////////////////////////////////

// �����ʲ���ѯ 3200
const WORD tdxXYZCCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��
	TDX_ID_ZQDM,				// ֤ȯ����
	TDX_ID_MMBZ,				// ������־
	TDX_ID_WTFS,				// ί�з�ʽ(��������־���)
};

// ���ùɷݲ�ѯ 3202
const WORD tdxXYGFCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��
	TDX_ID_MMBZ,				// ������־(ֻ�������ý��׵�������־,������Ĭ�Ϸ���"����ȯ�ɷ�")
	TDX_ID_WTFS,				// ί�з�ʽ(��������־���)
	TDX_ID_ZQDM,				// ֤ȯ����
};

// ���ú�Լ��ѯ(Ĭ��δƽ��) 3204
const WORD tdxXYHYCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��
	TDX_ID_KSRQ,				// ��ѯ��ʼ����
	TDX_ID_ZZRQ,				// ��ѯ��ֹ����
	TDX_ID_MMBZ,				// ������־
	TDX_ID_WTFS,				// ί�з�ʽ(��������־���)
	TDX_ID_CZBZ,				// ������־(0--ȫ��,1--����,2--��ȯ,Ĭ��--0)
};

// ���ú�Լ��ƽ�ֲ�ѯ 3206
const WORD tdxXYHYYPCCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��

	TDX_ID_KSRQ,				// ��ѯ��ʼ����
	TDX_ID_ZZRQ,				// ��ѯ��ֹ����
	TDX_ID_CZBZ,				// ������־(0--ȫ��,1--����,2--��ȯ,Ĭ��--0)
};

// �������޲�ѯ 3208
const WORD tdxXYSXCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��
	TDX_ID_ZQDM,				// ֤ȯ����
	TDX_ID_MMBZ,				// ������־
	TDX_ID_WTFS,				// ί�з�ʽ(��������־���)
};

// ���ø�ծ��ѯ 3210
const WORD tdxXYFZCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��
	TDX_ID_BZ,					// (����)���ֱ�ʶ
};

// �������ʲ���ѯ 3212
const WORD tdxFXYZCCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��
	TDX_ID_BZ,					// (����)���ֱ�ʶ
};

// ���ú�Լ���ղ�ѯ 3214
const WORD tdxXYHYDRCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��
};

// ���ý��ױ��֤ȯ��ѯ 3216
const WORD tdxXYJYBDZQCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��
	TDX_ID_MMBZ,				// ������־
	TDX_ID_WTFS,				// ί�з�ʽ
	TDX_ID_ZQDM,				// ֤ȯ����
};

// ���ý����ۺ���Ϣ��ѯ 3218
const WORD tdxXYJYZHXXCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��
};

// ���ý��׵���Ʒ֤ȯ��ѯ 3220
const WORD tdxXYJYDBPZQCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��
	TDX_ID_ZQDM,				// ֤ȯ����
};

// ���ý�����������֤ȯ��ѯ 3222
const WORD tdxXYJYRZMRZQCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��
};

// ���ý�����ȯ����֤ȯ��ѯ 3224
const WORD tdxXYJYRQMCZQCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��
};

// ���ý��״�����ʾ��Ϣ��ѯ 3226
const WORD tdxXYJYDMTSXXCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��
	TDX_ID_MMBZ,				// ������־
	TDX_ID_WTFS,				// ί������
	TDX_ID_ZQDM,				// ֤ȯ����
};

// ���ý��׺�Լ���ܲ�ѯ 3228
const WORD tdxXYJYHYHZCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��
	TDX_ID_KSRQ,				// ��ѯ��ʼ����
	TDX_ID_ZZRQ,				// ��ѯ��ֹ����
	TDX_ID_MMBZ,				// ������־
	TDX_ID_WTFS,				// ί�з�ʽ(��������־���)
};

// ���ý��������������ײ�ѯ 3230
const WORD tdxXYJYRZMRPTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��
};

// ���ý�����ȯ�������ײ�ѯ 3232
const WORD tdxXYJYRQMCPTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��
};

// ���ý�����ȯ��ȯ���ײ�ѯ 3234
const WORD tdxXYJYMQHQPTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��
};

// ���ý�����ȯ��ת���ײ�ѯ 3236
const WORD tdxXYJYYQHZPTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��
};

// ���ý�����ȯ��ȯ���ײ�ѯ 3238
const WORD tdxXYJYXQHQPTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��
};

// ���ý��׵���Ʒ��ת���ײ�ѯ 3240
const WORD tdxXYJYDBPHZPTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��
	TDX_ID_WTFS,				// ί�����(����/����)
	TDX_ID_DFFZDM,				// �Է���֧����
	TDX_ID_DFKHDM,				// �Է��ͻ�����
	TDX_ID_DFMM,				// �Է�����
};

// ���ý��׵���Ʒ�������ײ�ѯ 3242
const WORD tdxXYJYDBPHRPTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��
	TDX_ID_DFFZDM,				// �Է���֧����
	TDX_ID_DFKHDM,				// �Է��ͻ�����
	TDX_ID_DFMM,				// �Է�����
};

// ���ý��׵���Ʒ�������ײ�ѯ 3244
const WORD tdxXYJYDBPHCPTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��
	TDX_ID_DFFZDM,				// �Է���֧����
	TDX_ID_DFKHDM,				// �Է��ͻ�����
	TDX_ID_DFMM,				// �Է�����
};

// ���ý����ֽ𻹿����ײ�ѯ 3246
const WORD tdxXYJYXJHKPTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��
};

// ���ý�����ȯ�������ײ�ѯ 3248
const WORD tdxXYJYMQHKPTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��
};

// ���ý�������ƽ���������ײ�ѯ 3250
const WORD tdxXYJYRZPCMCPTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��
};

// ���ý�����ȯƽ���������ײ�ѯ 3252
const WORD tdxXYJYRQPCMRPTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��
};

// ���ý���������Ϣ��ѯ 3254
const WORD tdxXYJYLLXXCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��
};

// ���ý�����ȯ����ѯ 3256
const WORD tdxXYJYRQYECXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��
};

// ���ý�����������ѯ 3258
const WORD tdxXYJYRZYECXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��
};

// ���ý��׷ǽ��׻�ת��ѯ 3260
const WORD tdxXYJYFJYHZCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ
	
	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��
	TDX_ID_KSRQ,				// ��ѯ��ʼ����
	TDX_ID_ZZRQ,				// ��ѯ��ֹ����
};

// ���ý�����Ϣ���ò�ѯ 3262
const WORD tdxXYJYLXFYCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��
};

// ���ý����ʽ�ծ��ѯ 3264
const WORD tdxXYJYZJFZCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��
	TDX_ID_KSRQ,				// ��ѯ��ʼ����
	TDX_ID_ZZRQ,				// ��ѯ��ֹ����
};

// ���ý���֤ȯ��ծ��ѯ 3266
const WORD tdxXYJYZQFZCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��
	TDX_ID_KSRQ,				// ��ѯ��ʼ����
	TDX_ID_ZZRQ,				// ��ѯ��ֹ����
};

// ���ý��׿ͻ�ǩԼ��ѯ 3268
const WORD tdxXYJYKHQYCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��
};

// ���ý��׿ͻ�Э�鴦�� 3270
const WORD tdxXYJYKHXYCLFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_LX,					// ����(0--�Զ�����)
	TDX_ID_CZBZ,				// ������־(0--��ѯ,1--��ͨ,2--ȡ��,Ĭ��--0)
};

// ���ý��׳�����ϸ��ѯ 3272
const WORD tdxXYJYCHMXCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��
};

// ���ý������ʺ�Լ��ѯ 3274
const WORD tdxXYJYRZHYCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_CZBZ,				// ������־(0--ȫ��,1--δ�˽�,2--���˽�,Ĭ��--0)
};

// ���ý�����ȯ��Լ��ѯ 3276
const WORD tdxXYJYRQHYCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
	TDX_ID_CZBZ,				// ������־(0--ȫ��,1--δ�˽�,2--���˽�,Ĭ��--0)
};

// ���ý��׵���Ʒ��ת��ѯ 3278
const WORD tdxXYJYDBPHZCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

// ���ý������뵣��Ʒ���ײ�ѯ 3280
const WORD tdxXYJYMRDBPPTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ���ý�����������Ʒ���ײ�ѯ 3282
const WORD tdxXYJYMCDBPPTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ���ý��׹黹��ȯ�������ײ�ѯ 3284
const WORD tdxXYJYGHRQFYPTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ���ý��׸�ծ��ˮ��ѯ 3286
const WORD tdxXYJYFZLSCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

// ���ý����ֽ������ȯ���ײ�ѯ 3288
const WORD tdxXYJYXJTDHQPTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ���ý���ά�ֵ������ʲ�ѯ 3290
const WORD tdxXYJYWCDBBLCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ���ý��׶�ȹ��� 3292
const WORD tdxXYJYEDGLFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_CZBZ,				// ������־(0--��ѯ,1--���� 2--����)
	TDX_ID_RZSX,				// ������������
	TDX_ID_RQSX,				// ��ȯ��������
	TDX_ID_BZ,					// ����
	TDX_ID_XT_REMARK,			// ��ע
};

// ���ý��׶�ȱ����ѯ 3294
const WORD tdxXYJYEDBGCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

// ���ý���ƽ�����ʺ�Լ��ѯ 3296
const WORD tdxXYJYPCRZHYCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

// ���ý���ƽ����ȯ��Լ��ѯ 3298
const WORD tdxXYJYPCRQHYCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

//////////////////////////////////////////////////////////////////////////
//	ת��ͨ
//////////////////////////////////////////////////////////////////////////

// ת��ͨҵ����� 3400
const WORD tdxZRTYWCZFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_CZBZ,				// ������־(ż��--��Ϣ,����--����,�����"��ʶ�ֶ�ͳ��"�ĵ�)
	TDX_ID_XT_PARAM,			// ����(����"ת��ͨ"����Լ����ͬ����,��'\1'�ָ�,��������ͻ��˶���ȡ�����ֶ�)
	TDX_ID_BZ,					// ����
	TDX_ID_ZQDM,				// ֤ȯ����
	TDX_ID_HYQX,				// ��Լ����(Լ������������)
	TDX_ID_HYLL,				// ��Լ����(Լ��������)
	TDX_ID_TQZZLL,				// ��ǰ��ֹ����(��ǰ�黹����)
	TDX_ID_WTJE,				// ί�н��
	TDX_ID_WTSL,				// ί������
	TDX_ID_WTRQ,				// ί������(��ʼʹ������)
	TDX_ID_WTBH,				// ί�б��
	TDX_ID_PCH,					// ���κ�
	TDX_ID_DFXWDM,				// �Է�ϯλ����
	TDX_ID_DFGDDM,				// �Է��ɶ�����
	TDX_ID_YDXH,				// Լ�����
	TDX_ID_TSXX1,				// ��ʾ��Ϣ1(��ѡ��������)
	TDX_ID_XWDM,				// ϯλ����
};

// ת��ͨ���֤ȯ��ѯ 3402
const WORD tdxZRTBDZQCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_ZQDM,				// ֤ȯ����
	TDX_ID_HYQX,				// ��Լ����
};

// ת��ͨ�ʽ���Ϣ��ѯ 3404
const WORD tdxZRTZJXXCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ת��ͨ�ɷ���Ϣ��ѯ 3406
const WORD tdxZRTGFXXCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ת��ͨ�����������ײ�ѯ 3408
const WORD tdxZRTRZMRPTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ת��ͨ��ȯ�������ײ�ѯ 3410
const WORD tdxZRTRQMCPTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ת��ͨ�ʽ�����������ײ�ѯ 3412
const WORD tdxZRTZJJRSQPTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ת��ͨ�ɷݽ����������ײ�ѯ 3414
const WORD tdxZRTGFJRSQPTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ת��ͨ����չ���������ײ�ѯ 3416
const WORD tdxZRTJRZQSQPTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ת��ͨ��ǰ�黹�������ײ�ѯ 3418
const WORD tdxZRTTQGHSQPTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ת��ͨ����ҵ�񳷵���ѯ 3420
const WORD tdxZRTJRYWCDCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ת��ͨ����ҵ���ղ�ѯ 3422
const WORD tdxZRTJRYWDRCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ת��ͨ����ҵ����ʷ��ѯ 3424
const WORD tdxZRTJRYWLSCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

// ת��ͨ���ս����Լ��ѯ 3426
const WORD tdxZRTDRJRHYCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ת��ͨδ�˽����Լ��ѯ 3428
const WORD tdxZRTWLJRHYCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

// ת��ͨ���˽����Լ��ѯ 3430
const WORD tdxZRTYLJRHYCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

// ת��ͨ�ʽ�����������ײ�ѯ 3432
const WORD tdxZRTZJCJSQPTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ת��ͨ�ɷݳ����������ײ�ѯ 3434
const WORD tdxZRTGFCJSQPTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ת��ͨ�ʽ����ȷ�����ײ�ѯ 3436
const WORD tdxZRTZJCJQDPTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ת��ͨ�ɷݳ���ȷ�����ײ�ѯ 3438
const WORD tdxZRTGFCJQDPTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ת��ͨ����ҵ�񳷵���ѯ 3440
const WORD tdxZRTCJYWCDCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ת��ͨ����ҵ���ղ�ѯ 3442
const WORD tdxZRTCJYWDRCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ת��ͨ����ҵ����ʷ��ѯ 3444
const WORD tdxZRTCJYWLSCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

// ת��ͨ������ǰ�������ײ�ѯ 3446
const WORD tdxZRTCJTQSHPTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ת��ͨ����ͬ��չ�����ײ�ѯ 3448
const WORD tdxZRTCJTYZQPTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ת��ͨ���޷��ʲ�ѯ 3450
const WORD tdxZRTQXFLCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_CZBZ,				// ������־(��"ת��ͨҵ����� 3400"������ͬ)
	TDX_ID_ZQDM,				// ֤ȯ����
};

// ת��ͨ�����Լ��ѯ 3452
const WORD tdxZRTCJHYCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

// ת��ͨ������ʷ��Լ��ѯ 3454
const WORD tdxZRTCJLSHYCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
	TDX_ID_KSRQ,				// ��ʼ����
	TDX_ID_ZZRQ,				// ��ֹ����
};

// ת��ͨ�����������ײ�ѯ 3456
const WORD tdxZRTMCHKPTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ת��ͨ���뻹ȯ���ײ�ѯ 3458
const WORD tdxZRTMRHQPTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ת��ͨ�ֽ𻹿����ײ�ѯ 3460
const WORD tdxZRTXJHKPTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ת��ͨ��ȯ��ȯ���ײ�ѯ 3462
const WORD tdxZRTXQHQPTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ת��ͨ�ɳ�����Ϣ��ѯ 3464
const WORD tdxZRTKCJXXCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ת��ͨ����ͬ���������ײ�ѯ 3466
const WORD tdxZRTJRTYSHPTCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

// ת��ͨ�����˻���Ϣ��ѯ 3468
const WORD tdxZRTCJZHXXCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ʼ���
};

//////////////////////////////////////////////////////////////////////////
//	����
//////////////////////////////////////////////////////////////////////////

// ������ͨȡ���Զ����� 4100
const WORD tdxXLKTQXZDDLFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XLYZT_XGKT_FLAG,		// ��ͨ���
};

// ������ͨ�������� 4102
const WORD tdxXLKTHZPSFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XLYZT_START_DATE,	// ����������Ч����
	TDX_ID_XLYZT_END_DATE,		// ����������ֹ����
};

// ����ȡ���������� 4104
const WORD tdxXLQXHZPSFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ
};

// ������ͨ�����ع� 4106
const WORD tdxXLKTHZHGFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XLYZT_DEBT_KIND,		// �ع�Ʒ��
	TDX_ID_XLYZT_JE_MIN,		// �ʽ�����
	TDX_ID_XLYZT_JE_MAX,		// �ʽ�����
	TDX_ID_XLYZT_START_DATE,	// ����������Ч����
	TDX_ID_XLYZT_END_DATE,		// ����������ֹ����
};

// ����ȡ�������ع� 4108
const WORD tdxXLQXHZHGFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ
};

// ������ͨ�����깺 4110
const WORD tdxXLKTHZSGFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XLYZT_JE_MIN,		// �ʽ�����
	TDX_ID_XLYZT_JE_MAX,		// �ʽ�����
	TDX_ID_XLYZT_START_DATE,	// ����������Ч����
	TDX_ID_XLYZT_END_DATE,		// ����������ֹ����
};

// ����ȡ�������깺 4112
const WORD tdxXLQXHZSGFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ
};

// ���������ܲ�ѯ 4114
const WORD tdxXLDLGNCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ
};

//////////////////////////////////////////////////////////////////////////
//  ��ȫ������չ
//////////////////////////////////////////////////////////////////////////

//��ȫ�������� 4200
const WORD tdxCAAQGNSQFieldReq[]=
{
	TDX_ID_CA_KHH,			// �����ͻ���
	TDX_ID_CA_AQJB,			// ��ȫ����
	TDX_ID_CA_NEWIP,		// IP��Ϣ
	TDX_ID_CA_MMBHWT,		// ���뱣������
	TDX_ID_CA_JQTZM,		// ����������
};
const WORD tdxCAAQGNSQFieldAns[]=
{
	TDX_ID_CA_RESV,				// (����)�����ֶ�
};

// ��ȫ���ܳ��� 4202
const WORD tdxCAAQGNCXFieldReq[]=
{
	TDX_ID_CA_KHH,			// �����ͻ���
	TDX_ID_CA_AQJB,			// ��ȫ����
	TDX_ID_CA_JQTZM,		// ����������
};
const WORD tdxCAAQGNCXFieldAns[]=
{
	TDX_ID_CA_RESV,				// (����)�����ֶ�
};

//���뱣������У�� 4204
const WORD tdxCAMMBHWTJYFieldReq[]=
{
	TDX_ID_CA_KHH,			// 800 �����ͻ���
	TDX_ID_CA_MMBHWT1,		// 4231 ���뱣������1
	TDX_ID_CA_MMBHWT2,		// 4232 ���뱣������2
	TDX_ID_CA_MMBHWT3,		// 4233 ���뱣������3
	TDX_ID_CA_MMBHWT4,		// 4234 ���뱣������4
};
const WORD tdxCAMMBHWTJYFieldAns[]=
{
	TDX_ID_CA_MMBHWT1,		// 4231 ���뱣������1
	TDX_ID_CA_MMBHWT2,		// 4232 ���뱣������2
	TDX_ID_CA_MMBHWT3,		// 4233 ���뱣������3
	TDX_ID_CA_MMBHWT4,		// 4234 ���뱣������4
	TDX_ID_CA_RESV,			// 825 (����)�����ֶ�
};

// ��ȡ��ս���� 4206
const WORD tdxCAGETTZZBFieldReq[]=
{
	TDX_ID_CA_KHH,			// �����ͻ���
};
const WORD tdxCAGETTZZBFieldAns[]=
{
	TDX_ID_CA_TZZB,				// ��ս����
	TDX_ID_CA_CSCS,				// ���Դ���
	TDX_ID_CA_RESV,				// (����)�����ֶ�
};

// ע������ 4208
const WORD tdxCAZXJZKFieldReq[]=
{
	TDX_ID_CA_KHH,			// �����ͻ���
};
const WORD tdxCAZXJZKFieldAns[]=
{
	TDX_ID_CA_RESV,				// (����)�����ֶ�
};

// Ԥ������ 4210
const WORD tdxCAYLWTFieldReq[]=
{
	TDX_ID_CA_KHH,			// 800 �����ͻ���
	TDX_ID_CA_YLWT,			// 4212 Ԥ������
};
const WORD tdxCAYLWTFieldAns[]=
{
	TDX_ID_CA_RESV,				// 825 (����)�����ֶ�
};

// ֤������ 4212
const WORD tdxCACERRAREQFieldReq[]=
{
	TDX_ID_CA_KHH,			// �ͻ���
	TDX_ID_CA_SLOTSN,		// װ��֤������SN
	TDX_ID_CA_CID,			// ������ȫ����ID(�䷢/��֤)
	TDX_ID_CA_CERTREQ,		// ֤����������
	TDX_ID_CA_USERCERDN,	// ֤��DN
};
const WORD tdxCACERRAREQFieldAns[]=
{
	TDX_ID_CA_CERTTOKEN,	// ֤��ҵ����ˮ��
	TDX_ID_CA_CERTSN,		// ֤����(ֻ�е������Զ���˲�����������ȡ֤��ʱ)
	TDX_ID_CA_CERTINFO,		// ֤������
};

// ֤����� 4214
const WORD tdxCACERAUDITFieldReq[]=
{
	TDX_ID_CA_KHH,			// �����ͻ���
};
const WORD tdxCACERAUDITFieldAns[]=
{
	TDX_ID_CA_RESV,			// �����ֶ�
};

// ֤������ 4216
const WORD tdxCACERDOWNLOADFieldReq[]=
{
	TDX_ID_CA_KHH,			// �����ͻ���
	TDX_ID_CA_SLOTSN,		// װ��֤������SN
};
const WORD tdxCACERDOWNLOADFieldAns[]=
{
	TDX_ID_CA_CERTTOKEN,	// ֤��ҵ���
	TDX_ID_CA_CERTSN,		// ֤����
	TDX_ID_CA_CERTINFO,		// ֤������
	TDX_ID_CA_RESV,			// �����ֶ�
};

// ֤������ȷ�� 4218
const WORD tdxCACERDLCONFIRMFieldReq[]=
{
	TDX_ID_CA_KHH,			// �����ͻ���
};
const WORD tdxCACERDLCONFIRMFieldAns[]=
{
	TDX_ID_CA_RESV,			// �����ֶ�
};

// ����û���Ϣ 4220
const WORD tdxCAADDYHXXFieldReq[]=
{
	TDX_ID_CA_KHH,			// �����ͻ���
	TDX_ID_CA_IDCARD,		// ���֤��
	TDX_ID_CA_SJH,			// �ֻ���
};
const WORD tdxCAADDYHXXFieldAns[]=
{
	TDX_ID_CA_SJH,			// �ֻ���
	TDX_ID_CA_RESV,			// (����)�����ֶ�
};

// �޸��û���Ϣ 4222
const WORD tdxCAXGYHXXFieldReq[]=
{
	TDX_ID_CA_KHH,			// �����ͻ���
	TDX_ID_CA_SJH,			// �ֻ���
};
const WORD tdxCAXGYHXXFieldAns[]=
{
	TDX_ID_CA_SJH,				// �ֻ���
	TDX_ID_CA_RESV,				// (����)�����ֶ�
};

// ��ѯ�û���Ϣ 4224
const WORD tdxCACXYHXXFieldReq[]=
{
	TDX_ID_CA_KHH,			// �����ͻ���
};
const WORD tdxCACXYHXXFieldAns[]=
{
	TDX_ID_CA_SJH,				// �ֻ���
	TDX_ID_CA_RESV,				// (����)�����ֶ�
};

// ��ȡ�ֻ���֤�� 4226
const WORD tdxCAGETYZMFieldReq[]=
{
	TDX_ID_CA_KHH,			// �����ͻ���
	TDX_ID_CA_USERNICK,		// �û��ǳ�
	TDX_ID_CA_SJH,			// �ͻ��ֻ���
	TDX_ID_CA_YZM,			// ��֤��
};
const WORD tdxCAGETYZMFieldAns[]=
{
	TDX_ID_CA_YZM,				// ��֤��
	TDX_ID_CA_RESV,				// (����)�����ֶ�
};

// У����֤�� 4228
const WORD tdxCAYZMJYFieldReq[]=
{
	TDX_ID_CA_KHH,			// �����ͻ���
	TDX_ID_CA_YZM,			// ��֤��
};
const WORD tdxCAYZMJYFieldAns[]=
{	
	TDX_ID_CA_RESV,				// (����)�����ֶ�
};

// ������ȫ��֤У�� 4230
const WORD tdxOTHCABASEFUNFieldReq[]=
{
	TDX_ID_CA_KHH,			// �����ͻ���
	TDX_ID_JYMM,			// ��������
	TDX_ID_CA_SQBZ,			// �����־
	TDX_ID_CA_AQJB,			// ��ȫ����
	TDX_ID_CA_KHMC,			// �ͻ�����
	TDX_ID_CA_TXMM,			// ��֤����
	TDX_ID_CA_XTXMM,		// ����֤����
	TDX_ID_CA_ZSGY,			// ֤�鹫Կ��
	TDX_ID_CA_SJH,			// �ͻ��ֻ���
	TDX_ID_CA_ZJHM,			// �ͻ�֤������
	TDX_ID_CA_KHXB,			// �ͻ��Ա�
	TDX_ID_CA_EMAIL,		// �ͻ������ʼ�
	TDX_ID_CA_JHM,			// ������
	TDX_ID_CA_DRZB,			// ����ָ��(���ݺ��ָ���ͻ�ָ������,�ͻ�����Ҫ����,����,���ճֲ�,����Ӷ��)
	TDX_ID_CA_NEWIP,		// ���ε�½IP
	TDX_ID_CA_QSRQ,			// ��ʼ��ѯʱ��(��¼��ʷ��Ϣ��ѯ)
	TDX_ID_CA_ZZRQ,			// ��ֹ��ѯʱ��(��¼��ʷ��Ϣ��ѯ)
	TDX_ID_CA_JQTZM,		// ����������
	TDX_ID_CA_MMBHWT1,		// ���뱣������1
	TDX_ID_CA_MMBHWT2,		// ���뱣������2
	TDX_ID_CA_MMBHWT3,		// ���뱣������3
	TDX_ID_CA_MMBHWT4,		// ���뱣������4
	TDX_ID_CA_MAC,			// �û�MAC��ַ
	TDX_ID_CA_YLWT,			// Ԥ������
	TDX_ID_CA_CERTREQ,		// ֤����������(P10)
	TDX_ID_CA_USERCERDN,	// ֤��DN��Ϣ
	TDX_ID_CA_SEEDINFO,		// ������Ϣ
	TDX_ID_CA_OTPSN,		// OTPSN���
	TDX_ID_CA_IDCARD,		// �û����֤����
	TDX_ID_CA_YZM,			// ��֤��
	TDX_ID_CA_MACHINENAME,	// �����ǳ�
};
const WORD tdxOTHCABASEFUNFieldAns[]=
{
	TDX_ID_CA_YHFJ,			// �û��ּ�
	TDX_ID_CA_YHJBMS,		// �û���������
	TDX_ID_CA_YHQX,			// �û�Ȩ��
	TDX_ID_CA_LASTIP,		// �ϴε�½IP
	TDX_ID_CA_NEWIP,		// ���ε�½IP
	TDX_ID_CA_LASPROV,		// �ϴε�¼ʡ��
	TDX_ID_CA_NEWPROV,		// ���ε�¼ʡ��
	TDX_ID_CA_LASSITE,		// �ϴε�½����
	TDX_ID_CA_NEWSITE,		// ���ε�½���� 
	TDX_ID_CA_DLSJ,			// ��½ʱ��
	TDX_ID_CA_DLRQ,			// ��½����
	TDX_ID_CA_TZZB,			// ��ս����
	TDX_ID_CA_CSCS,			// ���Դ���
	TDX_ID_CA_MAC,			// �û�MAC��ַ
	TDX_ID_CA_RESV,			// (����)�����ֶ�
	TDX_ID_CA_YLWT,			// Ԥ����Ϣ
	TDX_ID_CA_BINDNUM,		// �󶨻���̨��
	TDX_ID_CA_KJYBZ,		// �ɽ��ױ�־ �˴����������жϱ�־
	TDX_ID_CA_MACHINENAME,		// 4204 �����ǳ�
	TDX_ID_CA_JQTZM,			// 4201 ����������	
	TDX_ID_CA_MACHINEBINDTIME,	// 4228 ������ʱ��
	TDX_ID_CA_GD_XH,			// 4241	���
	TDX_ID_CA_GD_DATE,			// 4242	����
	TDX_ID_CA_GD_TIME,			// 4243	ʱ��
	TDX_ID_CA_GD_HARDINFO,		// 4244 �������������Ϣ
	TDX_ID_CA_GD_MOREINFO,		// 4245	������ǳ�
	TDX_ID_CA_GD_TERMINALTYPE,	// 4246 �ն�����
};

// ��ѯ���뱣������ 4232
const WORD tdxCAMMBHWTCXFieldReq[]=
{
	TDX_ID_CA_KHH,			// �����ͻ���
};
const WORD tdxCAMMBHWTCXFieldAns[]=
{	
	TDX_ID_CA_MMBHWT,			// ���뱣������
	TDX_ID_CA_RESV,				// (����)�����ֶ�
};

// �޸����뱣������ 4234
const WORD tdxCAXGMMBHWTFieldReq[]=
{
	TDX_ID_CA_KHH,				// �����ͻ���
	TDX_ID_CA_MMBHWT,			// ���뱣������
};
const WORD tdxCAXGMMBHWTFieldAns[]=
{	
	TDX_ID_CA_RESV,				// (����)�����ֶ�
};

// �޸�Ԥ������ 4236
const WORD tdxCAXGYLWTFieldReq[]=
{
	TDX_ID_CA_KHH,				// �����ͻ���
	TDX_ID_CA_YLWT,				// ���뱣������
};
const WORD tdxCAXGYLWTFieldAns[]=
{
	TDX_ID_CA_RESV,				// (����)�����ֶ�
};

// ���뱣�������б��ѯ 4238
const WORD tdxPWDPROTQUEQUFieldReq[]=
{
	TDX_ID_CA_KHH,					// 800 �����ͻ���
	TDX_ID_CA_VER,					// 4226 ���뱣�������б�汾
};
const WORD tdxPWDPROTQUEQUFieldAns[]=
{
	TDX_ID_CA_VER,					// 4226 ���뱣�������б�ǰ�汾
	TDX_ID_CA_PWDPROQUESTION,		// 4227 ���뱣������
	TDX_ID_CA_RESV,					// 825 (����)�����ֶ�
};

// �������뱣������ 4240
const WORD tdxAPPLYPWDQAFieldReq[]=
{
	TDX_ID_CA_KHH,					// 800 �����ͻ���
	TDX_ID_CA_PWDQACZBZ,			// 4202 ���뱣�����������־ ( 0-����,1-�޸� )
	TDX_ID_CA_MMBHWT1,				// 4231 ���뱣������1
	TDX_ID_CA_MMBHWT2,				// 4232 ���뱣������2
	TDX_ID_CA_MMBHWT3,				// 4233 ���뱣������3
	TDX_ID_CA_MMBHWT4,				// 4234 ���뱣������4
};
const WORD tdxAPPLYPWDQAFieldAns[]=
{
	TDX_ID_CA_RESV,					// (����)�����ֶ�
};

// �������������� 4242
const WORD tdxBINDINFOFieldReq[]=
{
	TDX_ID_CA_KHH,				// 800 �ͻ���							
	TDX_ID_CA_JQTZM,			// 4201 ����������
	TDX_ID_CA_MACHINENAME,		// 4204 �����ǳ�
};
const WORD tdxBINDINFOFieldAns[]=
{
	TDX_ID_CA_RESV,				// 825 �����ֶ�
};

// ��ѯ����Ϣ 4244
const WORD tdxQUEBINDINFOFieldReq[]=
{
	TDX_ID_CA_KHH,				// 800 �ͻ���							
};
const WORD tdxQUEBINDINFOFieldAns[]=
{
	TDX_ID_CA_MACHINENAME,		// 4204 �����ǳ�
	TDX_ID_CA_JQTZM,			// 4201 ����������
	TDX_ID_CA_MACHINEBINDTIME,	// 4228 ������ʱ��
};

// ȡ���� 4246
const WORD tdxCANCELBINDFieldReq[]=
{
	TDX_ID_CA_KHH,				// 800 �ͻ���
	TDX_ID_CA_PROVISIONAL,		// 4205 ��ʱ��־
	TDX_ID_CA_MACHINENAME,		// 4204 �����ǳ�
};
const WORD tdxCANCELBINDFieldAns[]=
{
	TDX_ID_CA_RESV,				// 825 �����ֶ�
};

// ��ȫ����״̬��ѯ 4248
const WORD tdxSAFEMODQUEFieldReq[]=
{
	TDX_ID_CA_KHH,				// 800 �ͻ���
	TDX_ID_CA_CZBZ,				// 824 ������־
};
const WORD tdxSAFEMODQUEFieldAns[]=
{
	TDX_ID_CA_SQBZ,				// 802 �����־
	TDX_ID_CA_RESV,				// 825 �����ֶ�
};

// �����û���ȫ���� 4250
const WORD tdxABUSERLVFieldReq[]=
{
	TDX_ID_CA_KHH,				// 800 �ͻ���
};
const WORD tdxABUSERLVFieldAns[]=
{
	TDX_ID_CA_RESV,				// 825 �����ֶ�
};

// �û����� 4252
const WORD tdxUSERLOGOUTFieldReq[]=
{
	TDX_ID_CA_KHH,				// 800 �ͻ���
	TDX_ID_CA_CONNID,			// 4203 ������ID
};
const WORD tdxUSERLOGOUTFieldAns[]=
{
	TDX_ID_CA_RESV,				// 825 �����ֶ�
};

// �û��������� 4254
const WORD tdxUSERALIVEFieldReq[]=
{
	TDX_ID_CA_KHH,				// 800 �ͻ���
	TDX_ID_CA_CONNID,			// 4203 ������ID
};
const WORD tdxUSERALIVEFieldAns[]=
{
	TDX_ID_CA_RESV,				// 825 �����ֶ�
};

// ȡ���û����� 4256
const WORD tdxCANCELLVFieldReq[]=
{
	TDX_ID_CA_KHH,				// 800 �ͻ���
	TDX_ID_CA_CZBZ,				// 824 ������־
	TDX_ID_CA_AQJB,				// 806 ��ȫ����
	TDX_ID_CA_OTPSN,			// 4222 OTPsn
};
const WORD tdxCANCELLVFieldAns[]=
{
	TDX_ID_CA_RESV,				// 825 �����ֶ�
};

// ��ȡ��Ʒ���� 4258
const WORD tdxGETPROINFOFieldReq[]=
{
	TDX_ID_CA_KHH,				// 800 �ͻ���
};
const WORD tdxGETPROINFOFieldAns[]=
{
	TDX_ID_CA_QSRQ ,			// 896 ��ʼʱ��
	TDX_ID_CA_ZZRQ ,			// 897 ��ֹʱ��
	TDX_ID_CA_RESETFLAG ,		// 856 ��Ч��־
	TDX_ID_CA_YHQX ,			// 809 �û�Ȩ��
	TDX_ID_CA_YHJBBZ ,			// 836 �û�����ע
};


// ע���û� 4280
const WORD tdxREGUSERFieldReq[]= 
{
	TDX_ID_CA_KHMC,				// 801 �ͻ�����
	TDX_ID_CA_USERNICK,			// 4229 �û��ǳ�
	TDX_ID_CA_TXMM,				// 803 ��֤����
	TDX_ID_CA_CARDTYPE,			// 4231	֤������
	TDX_ID_CA_IDCARD,			// 4224 �û����֤����
	TDX_ID_CA_KHXB,				// 862 �ͻ��Ա�
	TDX_ID_CA_BIRTH,			// 4232 ��������
	TDX_ID_CA_POSTCODE,			// 4233 ��������
	TDX_ID_CA_ADDRESS,			// 4234 ��ϵ��ַ
	TDX_ID_CA_OFFPHONE,			// 4235 �칫�绰
	TDX_ID_CA_HOMEPHONE,		// 4236 ��ͥ�绰
	TDX_ID_CA_FAXPHONE,			// 4237 ����绰
	TDX_ID_CA_SJH,				// 860 �ͻ��ֻ���
	TDX_ID_CA_EMAIL,			// 863 �ͻ������ʼ�
	TDX_ID_CA_EDUCATION,		// 4238 ѧ��
	TDX_ID_CA_YZM,				// 4225 ������֤��
	TDX_ID_CA_CZSX,				// 823 ��������
	TDX_ID_CA_ISVIPHOST,		// 837 �Ƿ�VIP, ����У���ֻ���̬��
};
const WORD tdxREGUSERFieldAns[]=
{
	TDX_ID_CA_KHH,				// 800 �ͻ���
	TDX_ID_CA_RESV,				// 825 �����ֶ�
};

// �޸�ע������ 4282
const WORD tdxALTERREGPWDFieldReq[]=
{
	TDX_ID_CA_KHH,				// 800 �ͻ���
	TDX_ID_CA_TXMM,				// 803 ��֤����
	TDX_ID_CA_XTXMM,			// 804 ����֤����
};
const WORD tdxALTERREGPWDFieldAns[]=
{
	TDX_ID_CA_RESV,				// 825 �����ֶ�
};

// �����½���Ʋ��� 4284
const WORD tdxSSOFieldReq[]=
{
	TDX_ID_CA_KHH,				// 800 �ͻ���
	TDX_ID_CA_CZBZ,				// 824 ������ʾ(0 �������� 1 У������)
	TDX_ID_CA_TOKEN,			// 4239 ����
	TDX_ID_CA_RESV,				// 825 �����ֶ�
};
const WORD tdxSSOFieldAns[]=
{
	TDX_ID_CA_TOKEN,			// 4239 ����
	TDX_ID_CA_RESV,				// 825 �����ֶ�
};
// �����½��������ȡ�û���Ϣ 4286
const WORD tdxSSOYHXXFieldReq[]=
{
	TDX_ID_CA_TOKEN,			// 4239 ����
};
const WORD tdxSSOYHXXFieldAns[]=
{
	TDX_ID_CA_KHH,				// 800 �ͻ���
};
// ֤�����
const WORD tdxCERDELFieldReq[]=
{
	TDX_ID_CA_KHH,			// 800 �ͻ���	
	TDX_ID_CA_SLOTSN,		// װ��֤������SN
	TDX_ID_CA_CERTSN,		// ֤����
};
const WORD tdxCERDELFieldAns[]=
{
	TDX_ID_CA_RESV,				// 825 �����ֶ�
};
// OTPͬ��
const WORD tdxOTPSYNFieldReq[]=
{
	TDX_ID_CA_KHH,			// 800 �ͻ���
	TDX_ID_CA_YYBID,		// Ӫҵ��ID
	TDX_ID_CA_TXMM,			// ��һ�ζ�̬����
	TDX_ID_CA_XTXMM,		// �ڶ��ζ�̬����
	TDX_ID_CA_CZBZ,			// 824 ������ʾ(0-�ͻ������� 1-HTTP����)
	TDX_ID_CA_RESV,			// 825 �����ֶ�(0-OTPͬ��,1-OTP��֤)
};
const WORD tdxOTPSYNFieldAns[]=
{
	TDX_ID_CA_RESV,				// 825 �����ֶ�
};
// �������һ����
const WORD tdxCHECKRECORDFieldReq[]=
{
	TDX_ID_CA_KHH,			// 800 �ͻ���
};
const WORD tdxCHECKRECORDFieldAns[]=
{
	TDX_ID_CA_RESV,				// 825 �����ֶ�
};
// �û���֤ 4294
const WORD tdxPAAUTHFieldReq[]=
{
	TDX_ID_CA_KHH,				// 800 �ͻ���
	TDX_ID_CA_TXMM,				// 803 ��֤����
	TDX_ID_CA_CZY,				// 821 ����Ա
};
const WORD tdxPAAUTHFieldAns[]=
{
	TDX_ID_CA_YHFJ,				// �û��ּ�
	TDX_ID_CA_RESV,				// 825 �����ֶ�
};
const WORD tdxPAACCREPORTFieldReq[]=
{
	TDX_ID_CA_KHH,				// 800 �ͻ���
};
const WORD tdxPAACCREPORTFieldAns[]=
{
	TDX_ID_CA_RESV,				// 825 �����ֶ�
};
// OTP����
const WORD tdxOTPTEMPFieldReq[]=
{
	TDX_ID_CA_KHH,				// 800 �ͻ���
	TDX_ID_CA_CZBZ,				// 824 ������ʾ
};
const WORD tdxOTPTEMPFieldAns[]=
{
	TDX_ID_CA_RESV,				// 825 �����ֶ�
};
// ������ȫ��֤��ȡ��֤�� 4300
const WORD tdxOTHCAGETYZMFUNFieldReq[]=
{
	TDX_ID_CA_KHH,			// �����ͻ���
	TDX_ID_CA_SQBZ,			// �����־
	TDX_ID_CA_AQJB,			// ��ȫ����
	TDX_ID_CA_KHMC,			// �ͻ�����
	TDX_ID_CA_TXMM,			// ��֤����
	TDX_ID_CA_XTXMM,		// ����֤����
	TDX_ID_CA_ZSGY,			// ֤�鹫Կ��
	TDX_ID_CA_SJH,			// �ͻ��ֻ���
	TDX_ID_CA_ZJHM,			// �ͻ�֤������
	TDX_ID_CA_KHXB,			// �ͻ��Ա�
	TDX_ID_CA_EMAIL,		// �ͻ������ʼ�
	TDX_ID_CA_JHM,			// ������
	TDX_ID_CA_DRZB,			// ����ָ��(���ݺ��ָ���ͻ�ָ������,�ͻ�����Ҫ����,����,���ճֲ�,����Ӷ��)
	TDX_ID_CA_NEWIP,		// ���ε�½IP
	TDX_ID_CA_QSRQ,			// ��ʼ��ѯʱ��(��¼��ʷ��Ϣ��ѯ)
	TDX_ID_CA_ZZRQ,			// ��ֹ��ѯʱ��(��¼��ʷ��Ϣ��ѯ)
	TDX_ID_CA_JQTZM,		// ����������
	TDX_ID_CA_MMBHWT1,		// ���뱣������1
	TDX_ID_CA_MMBHWT2,		// ���뱣������2
	TDX_ID_CA_MMBHWT3,		// ���뱣������3
	TDX_ID_CA_MMBHWT4,		// ���뱣������4
	TDX_ID_CA_MAC,			// �û�MAC��ַ
	TDX_ID_CA_YLWT,			// Ԥ������
	TDX_ID_CA_CERTREQ,		// ֤����������(P10)
	TDX_ID_CA_USERCERDN,	// ֤��DN��Ϣ
	TDX_ID_CA_SEEDINFO,		// ������Ϣ
	TDX_ID_CA_OTPSN,		// OTPSN���
	TDX_ID_CA_IDCARD,		// �û����֤����
	TDX_ID_CA_YZM,			// ��֤��
	TDX_ID_CA_MACHINENAME,	// �����ǳ�
};
const WORD tdxOTHCAGETYZMFUNFieldAns[]=
{
	TDX_ID_CA_YHFJ,			// �û��ּ�
	TDX_ID_CA_YHJBMS,		// �û���������
	TDX_ID_CA_YHQX,			// �û�Ȩ��
	TDX_ID_CA_LASTIP,		// �ϴε�½IP
	TDX_ID_CA_NEWIP,		// ���ε�½IP
	TDX_ID_CA_LASPROV,		// �ϴε�¼ʡ��
	TDX_ID_CA_NEWPROV,		// ���ε�¼ʡ��
	TDX_ID_CA_DLSJ,			// ��½ʱ��
	TDX_ID_CA_DLRQ,			// ��½����
	TDX_ID_CA_TZZB,			// ��ս����
	TDX_ID_CA_CSCS,			// ���Դ���
	TDX_ID_CA_MAC,			// �û�MAC��ַ
	TDX_ID_CA_YLWT,			// Ԥ����Ϣ
	TDX_ID_CA_BINDNUM,		// �󶨻���̨��
	TDX_ID_CA_KJYBZ,		// �ɽ��ױ�־ �˴����������жϱ�־
	TDX_ID_CA_MACHINENAME,	// �����ǳ�
	TDX_ID_CA_JQTZM,		// ����������
	TDX_ID_CA_RESV,			// (����)�����ֶ�
};

// ��ѡ���ϴ�����
const WORD tdxOPMYSTOCKFUNFieldReq[]=
{
	TDX_ID_CA_KHH,			// (800) �����ͻ���
	TDX_ID_CA_CZBZ,			// (824) ������־ 0- ����, 1�ϴ�
	TDX_ID_CA_USERSTOCK,	// (4241) ��ѡ����Ϣ
	TDX_ID_XT_MODE,			// ģʽ(��������)
	TDX_ID_XT_PARAM,		// ����(������Ϣ)
	TDX_ID_XT_DESCRIPTION,	// ����(��������)
	TDX_ID_XT_REMARK,		// ��ע(���÷���)
};
const WORD tdxOPMYSTOCKFUNFieldAns[]=
{
	TDX_ID_CA_CZBZ,			// (824) ������־ 0- ����, 1�ϴ�
	TDX_ID_CA_USERSTOCK,	// (4241) ��ѡ����Ϣ
	TDX_ID_XT_MODE,			// ģʽ(��������)
	TDX_ID_XT_PARAM,		// ����(������Ϣ)
	TDX_ID_XT_DESCRIPTION,	// ����(��������)
	TDX_ID_CA_RESV,			// (825) Ԥ����Ϣ
};

// �һ��û����� 4304
const WORD tdxFETCHPWDFUNFieldReq[]=
{
	TDX_ID_CA_KHH,			// (800) �����ͻ���
	TDX_ID_CA_TXMM,			// ���û�����
	TDX_ID_CA_USERNICK,		// 4229 �û��ǳ�
	TDX_ID_CA_YZM,			// 4225 ��֤��
};
const WORD tdxFETCHPWDFUNFieldAns[]=
{
	TDX_ID_CA_RESV,			// (825) Ԥ����Ϣ
};

// ע���û���Ϣ��ѯ
const WORD tdxQUERYREGUDATAFUNFieldReq[]=
{
	TDX_ID_CA_KHH,			// (800) �����ͻ���
	TDX_ID_CA_TXMM,			// 803 ��֤����
};
const WORD tdxQUERYREGUDATAFUNFieldAns[]=
{
	TDX_ID_CA_KHMC,				// 801 �ͻ�����
	TDX_ID_CA_USERNICK,			// 4229 �û��ǳ�
	TDX_ID_CA_CARDTYPE,			// 4231	֤������
	TDX_ID_CA_IDCARD,			// 4224 �û����֤����
	TDX_ID_CA_KHXB,				// 862 �ͻ��Ա�
	TDX_ID_CA_BIRTH,			// 4232 ��������
	TDX_ID_CA_POSTCODE,			// 4233 ��������
	TDX_ID_CA_ADDRESS,			// 4234 ��ϵ��ַ
	TDX_ID_CA_OFFPHONE,			// 4235 �칫�绰
	TDX_ID_CA_HOMEPHONE,		// 4236 ��ͥ�绰
	TDX_ID_CA_FAXPHONE,			// 4237 ����绰
	TDX_ID_CA_SJH,				// 860 �ͻ��ֻ���
	TDX_ID_CA_EMAIL,			// 863 �ͻ������ʼ�
	TDX_ID_CA_EDUCATION,		// 4238 ѧ��
};


// �һ��û��ʺ� 4306
const WORD tdxFETCHUSERACCOUNTFUNFieldReq[]=
{
	TDX_ID_CA_KHH,			// (800) �����ͻ���
	TDX_ID_CA_TXMM,			// ���û�����
	TDX_ID_CA_SJH,			// �ֻ���
	TDX_ID_CA_YZM,			// �ֻ���̬��
};
const WORD tdxFETCHUSERACCOUNTFUNFieldAns[]=
{
	TDX_ID_CA_RESV,			// (825) Ԥ����Ϣ
};

// ���ֲ�ѯ
const WORD tdxQUERYSCOREFUNFieldReq[]=
{
	TDX_ID_CA_KHH,			// (800) �����ͻ���
	TDX_ID_CA_QSRQ,			// (896) ��ʼ��ѯʱ��
	TDX_ID_CA_ZZRQ,			// (897) ��ֹ��ѯʱ��
	TDX_ID_CA_TRADETYPE,	// (4249)��������
};
const WORD tdxQUERYSCOREFUNFieldAns[]=
{
	TDX_ID_CA_TRADETIME,	// ����ʱ��
	TDX_ID_CA_TRADETYPE,	// ��������
	TDX_ID_CA_SCORE,		// ����ֵ
	TDX_ID_XT_REMARK,		// ��ע
};

// ��ȡ������ 4312
const WORD tdxGETACTIVECODEFUNFieldReq[]=
{
	TDX_ID_CA_SJH,			// �ֻ���
	TDX_ID_CA_TXMM,			// ������Ϣ
	TDX_ID_CA_XTXMM,		// �ֻ�OTPID
	TDX_ID_CA_RESV,			// ������Ϣ
};
const WORD tdxGETACTIVECODEFUNFieldAns[]=
{
	TDX_ID_CA_TOKEN,	// ������
	TDX_ID_CA_RESV,		// ��ע
};

// �°汾��ȫ����( 4500 - 4600)

// ��ȫ���ܲ�ѯ 4500
const WORD tdxQRYSCFUNCFUNFieldReq[]=
{
	TDX_ID_CA_KHH,				// (800) �����ͻ���
	TDX_ID_CA_VER,				// (4226) �汾��Ϣ( ��ʽ: ��˾����(ͨ����/����/����);�ͻ�������(�ͻ���/web/�ֻ�);�汾��(V1.0);...��չ�ֶ�)
};
const WORD tdxQRYSCFUNCFUNFieldAns[]=
{// ���ն��¼������
	TDX_ID_CA_AQJB,				// (806) ��¼��ȫ����
	TDX_ID_CA_OTPSN,			// (4222) OTPSN��� ( ����ȫ�������OTPʱ��Ч)
	TDX_ID_CA_CERTSN,			// (4219) ֤����( ����ȫ�����а���֤�鼶��ʱ��Ч)
	TDX_ID_CA_ZSQSRQ,			// (816) ������Ч����
	TDX_ID_CA_ZSJZRQ,			// (817) ����ʧЧ����( ������Чʱ��0)
	TDX_ID_CA_RESV,				// (825) �����ֶ�
};

// ����/�رհ�ȫ���� 4502
const WORD tdxSWITCHSCFUNCFUNFieldReq[]=
{
	TDX_ID_CA_KHH,				// (800) �����ͻ���
	TDX_ID_JYMM,				// (134) ��������
	TDX_ID_CA_AQJB,				// (806) ��¼��ȫ����
	TDX_ID_CA_TXMM,				// (803) ��֤��Ϣ( ���ݰ�ȫ����, Ϊ��֤����, OTP����, ֤��ǩ��, ������֤���)(��׼֤��ǩ�����ø�ʽ: ֤��SN;ǩ��ԭ��;֤����Ϣ;ǩ����Ϣ;��չ, ����Ҫʱ�ֶ����)
	TDX_ID_CA_CZBZ,				// (824) ������־( 0-ȡ��, 1-��ͨ, 2-��ʱȡ��)
	TDX_ID_CA_ZSJZRQ,			// (817) ��ʱȡ������ʱ��( ����ʱȡ��ʱ��Ч �Ե�����00:00����)
	TDX_ID_CA_VER,				// (4226) �汾��Ϣ( ��ʽ: ��˾����(ͨ����/����/����);�ͻ�������(�ͻ���/web/�ֻ�);�汾��(V1.0);...��չ�ֶ�)
};
const WORD tdxSWITCHSCFUNCFUNFieldAns[]=
{
	TDX_ID_CA_RESV,				// (825) �����ֶ�
};

// ͳһ��֤ 4504
const WORD tdxUNIAUTHFUNFieldReq[]=
{
	TDX_ID_CA_KHH,				// (800) �����ͻ���
	TDX_ID_ZHLB,				// (125) �ʺ����
	TDX_ID_XT_GTLB,				// (1234) ��̨���(0:Ĭ�� 1:���ý��� 2:��Ʊ 3:���� 4:��Ʒ�ڻ� 5:�����ڻ� 6:�۹�),ԭ���ý��ױ�ʶ�ֶ�
	TDX_ID_JYMM,				// (134) ��������
	TDX_ID_CA_VER,				// (4226) �汾��Ϣ( ��ʽ: ��˾����(ͨ����/����/����);�ͻ�������(�ͻ���/web/�ֻ�);�汾��(V1.0);...��չ�ֶ�)

	TDX_ID_CA_KHMC,				// (801) �ͻ�����
	TDX_ID_CA_AQJB,				// (806) ��¼��ȫ����
	TDX_ID_CA_TXMM,				// (803) ��֤��Ϣ( ���ݰ�ȫ����, Ϊ��֤����, OTP����, ֤��ǩ��, ������֤���)(��׼֤��ǩ�����ø�ʽ: ֤��SN;ǩ��ԭ��;֤����Ϣ;ǩ����Ϣ;��չ, ����Ҫʱ�ֶ����)
	TDX_ID_CA_ISVIPHOST,		// (837) VIP��վ��ʶ
	TDX_ID_CA_JQTZM,			// (4201) ����������
};
const WORD tdxUNIAUTHFUNFieldAns[]=
{
	TDX_ID_CA_KJYBZ,			// (810) �ɽ��ױ�־(0:���ɽ���,ֻ�ɽ��а�ȫ����() 1:����������)
	TDX_ID_CA_RESV,				// (825) ������Ϣ
};

// ������֤���� 4506
const WORD tdxREQAPWDFUNFieldReq[]=
{
	TDX_ID_CA_KHH,				// (800) �����ͻ���
	TDX_ID_JYMM,				// (134) ��������
	TDX_ID_CA_TXMM,				// (803) ��֤����
	TDX_ID_CA_VER,				// (4226) �汾��Ϣ( ��ʽ: ��˾����(ͨ����/����/����);�ͻ�������(�ͻ���/web/�ֻ�);�汾��(V1.0);...��չ�ֶ�)
};
const WORD tdxREQAPWDFUNFieldAns[]=
{
	TDX_ID_CA_RESV,				// (825) �����ֶ�
};

// �޸���֤���� 4508
const WORD tdxMODAPWDFUNFieldReq[]=
{
	TDX_ID_CA_KHH,				// (800) �����ͻ���
	TDX_ID_JYMM,				// (134) ��������
	TDX_ID_CA_TXMM,				// (803) ��֤��Ϣ
	TDX_ID_CA_VER,				// (4226) �汾��Ϣ( ��ʽ: ��˾����(ͨ����/����/����);�ͻ�������(�ͻ���/web/�ֻ�);�汾��(V1.0);...��չ�ֶ�)
	
	TDX_ID_CA_XTXMM,			// (804) ����֤����
};
const WORD tdxMODAPWDFUNFieldAns[]=
{
	TDX_ID_CA_RESV,				// (825) �����ֶ�
};

// ������֤���� 4510
const WORD tdxRESETAPWDFUNFieldReq[]=
{
	TDX_ID_CA_KHH,				// (800) �����ͻ���
	TDX_ID_JYMM,				// (134) ��������
	TDX_ID_CA_TXMM,				// (803) ��֤��Ϣ( ������֤��ʽ, ������ſ���)
	TDX_ID_CA_VER,				// (4226) �汾��Ϣ( ��ʽ: ��˾����(ͨ����/����/����);�ͻ�������(�ͻ���/web/�ֻ�);�汾��(V1.0);...��չ�ֶ�)

	TDX_ID_CA_XTXMM,			// (804) ����֤����
};
const WORD tdxRESETAPWDFUNFieldAns[]=
{
	TDX_ID_CA_RESV,				// (825) �����ֶ�
};

// ͬ��OTP 4512
const WORD tdxSYNOTPFUNFieldReq[]=
{
	TDX_ID_CA_KHH,				// (800) �����ͻ���
	TDX_ID_JYMM,				// (134) ��������
	TDX_ID_CA_TXMM,				// (803) У׼��Ϣ( ��ʽ:��һ����̬����;�ڶ�����̬����)
	TDX_ID_CA_VER,				// (4226) �汾��Ϣ( ��ʽ: ��˾����(ͨ����/����/����);�ͻ�������(�ͻ���/web/�ֻ�);�汾��(V1.0);...��չ�ֶ�)
};
const WORD tdxSYNOTPFUNFieldAns[]=
{
	TDX_ID_CA_RESV,				// (825) �����ֶ�
};

// ��ȡ֤��ǩ���� 4514
const WORD tdxGETCSIGNKEYFUNFieldReq[]=
{
	TDX_ID_CA_KHH,				// (800) �����ͻ���
	TDX_ID_JYMM,				// (134) ��������
	TDX_ID_CA_VER,				// (4226) �汾��Ϣ( ��ʽ: ��˾����(ͨ����/����/����);�ͻ�������(�ͻ���/web/�ֻ�);�汾��(V1.0);...��չ�ֶ�)
};
const WORD tdxGETCSIGNKEYFUNFieldAns[]=
{
	TDX_ID_CA_YZM,				// (4225) ֤��ǩ��ԭ��
	TDX_ID_CA_RESV,				// (825) �����ֶ�
};

// ����֤�� 4516
const WORD tdxUPDCERTFUNFieldReq[]=
{
	TDX_ID_CA_KHH,				// (800) �����ͻ���
	TDX_ID_JYMM,				// (134) ��������
	TDX_ID_CA_VER,				// (4226) �汾��Ϣ( ��ʽ: ��˾����(ͨ����/����/����);�ͻ�������(�ͻ���/web/�ֻ�);�汾��(V1.0);...��չ�ֶ�)

	TDX_ID_CA_SLOTSN,			// (4218) װ��֤������SN
	TDX_ID_CA_CID,				// (4220) ������ȫ����ID(�䷢/��֤)
	TDX_ID_CA_CERTREQ,			// (4214) ֤���������
	TDX_ID_CA_USERCERDN,		// (4215) ֤��DN
	TDX_ID_CA_ZSQSRQ,			// (816) ֤����������
	TDX_ID_CA_ZSJZRQ,			// (817) ֤�鵽������
};
const WORD tdxUPDCERTFUNFieldAns[]=
{
	TDX_ID_CA_CERTSN,			// (4219) ֤����
	TDX_ID_CA_CERTINFO,			// (4217) ֤������
	TDX_ID_CA_RESV,				// (825) �����ֶ�
};

// ��ȡ�ֻ���̬�� 4518
const WORD tdxGETCCODEFUNFieldReq[]=
{
	TDX_ID_CA_KHH,				// (800) �����ͻ���
	TDX_ID_JYMM,				// (134) ��������
	TDX_ID_CA_VER,				// (4226) �汾��Ϣ( ��ʽ: ��˾����(ͨ����/����/����);�ͻ�������(�ͻ���/web/�ֻ�);�汾��(V1.0);...��չ�ֶ�)
};
const WORD tdxGETCCODEFUNFieldAns[]=
{
	TDX_ID_CA_RESV,				// (825) �����ֶ�
};

// ��Ȩ����� 4520
const WORD tdxPERMITMACHINEFUNFieldReq[]=
{
	TDX_ID_CA_KHH,				// (800) �����ͻ���
	TDX_ID_JYMM,				// (134) ��������
	TDX_ID_CA_TXMM,				// (803) ��֤��Ϣ( ���ݰ�ȫ����, Ϊ��֤����, OTP����, ֤��ǩ��, ������֤���)(��׼֤��ǩ�����ø�ʽ: ֤��SN;ǩ��ԭ��;֤����Ϣ;ǩ����Ϣ;��չ, ����Ҫʱ�ֶ����)
	TDX_ID_CA_VER,				// (4226) �汾��Ϣ( ��ʽ: ��˾����(ͨ����/����/����);�ͻ�������(�ͻ���/web/�ֻ�);�汾��(V1.0);...��չ�ֶ�)
	
	TDX_ID_CA_MACHINENAME,		// (4204) �����ǳ�
	TDX_ID_CA_JQTZM,			// (4201) ����������
};
const WORD tdxPERMITMACHINEFUNFieldAns[]=
{
	TDX_ID_CA_RESV,				// (825) �����ֶ�
};

// ����������Ȩ 4522
const WORD tdxFREEMACHINEFUNFieldReq[]=
{
	TDX_ID_CA_KHH,				// (800) �����ͻ���
	TDX_ID_JYMM,				// (134) ��������
	TDX_ID_CA_TXMM,				// (803) ��֤��Ϣ( ���ݰ�ȫ����, Ϊ��֤����, OTP����, ֤��ǩ��, ������֤���)(��׼֤��ǩ�����ø�ʽ: ֤��SN;ǩ��ԭ��;֤����Ϣ;ǩ����Ϣ;��չ, ����Ҫʱ�ֶ����)
	TDX_ID_CA_VER,				// (4226) �汾��Ϣ( ��ʽ: ��˾����(ͨ����/����/����);�ͻ�������(�ͻ���/web/�ֻ�);�汾��(V1.0);...��չ�ֶ�)
	
	TDX_ID_CA_MACHINENAME,		// (4204) �����ǳ�
	TDX_ID_CA_CZBZ,				// (824) ������־( 0-���, 1-�ָ���ʱ���, 2-��ʱȡ��)
	TDX_ID_CA_ZSJZRQ,			// (817) ��ʱȡ������ʱ��( ����ʱȡ��ʱ��Ч �Ե�����00:00����)
};
const WORD tdxFREEMACHINEFUNFieldAns[]=
{
	TDX_ID_CA_RESV,				// (825) �����ֶ�
};

// ��ѯ��Ȩ
const WORD tdxQRYPERMITIONFUNFieldReq[]=
{
	TDX_ID_CA_KHH,				// (800) �����ͻ���
	TDX_ID_JYMM,				// (134) ��������
	TDX_ID_CA_TXMM,				// (803) ��֤��Ϣ( ���ݰ�ȫ����, Ϊ��֤����, OTP����, ֤��ǩ��, ������֤���)(��׼֤��ǩ�����ø�ʽ: ֤��SN;ǩ��ԭ��;֤����Ϣ;ǩ����Ϣ;��չ, ����Ҫʱ�ֶ����)
	TDX_ID_CA_VER,				// (4226) �汾��Ϣ( ��ʽ: ��˾����(ͨ����/����/����);�ͻ�������(�ͻ���/web/�ֻ�);�汾��(V1.0);...��չ�ֶ�)
};
const WORD tdxQRYPERMITIONFUNFieldAns[]=
{
	TDX_ID_CA_SID,			// (4501) ���
	TDX_ID_CA_BINDTINE,		// (4502) ��ʱ��
	TDX_ID_CA_UMAC,			// (4503) MAC��ַ
	TDX_ID_CA_REMARK,		// (4504) �������ע
	TDX_ID_CA_HARDINFO,		// (4505) ����������Ϣ
};
// const WORD tdxQRYPERMITIONFUNFieldAns[]=
// {
// 	TDX_ID_CA_MACHINENAME,		// (4204) �����ǳ�
// 	TDX_ID_CA_JQTZM,			// (4201) ����������
// 	TDX_ID_CA_ZSQSRQ,			// (816) ��ʱ��
// 	TDX_ID_CA_ZSJZRQ,			// (817) ��ʱȡ������ʱ��( ����ʱȡ��ʱ��Ч �Ե�����00:00����)
// 	TDX_ID_CA_VER,				// (4226) �汾��Ϣ( ��ʽ: ��˾����(ͨ����/����/����)�ͻ�������(�ͻ���/web/�ֻ�)�汾��(V1.0) ����:ͨ���ſͻ���V6.01)
// 	TDX_ID_CA_RESV,				// (825) �����ֶ�
// };

// ����Ԥ����Ϣ 4526
const WORD tdxUPDSELFINFOFUNFieldReq[]=
{
	TDX_ID_CA_KHH,				// (800) �����ͻ���
	TDX_ID_JYMM,				// (134) ��������
	TDX_ID_CA_TXMM,				// (803) ��֤��Ϣ( ���ݰ�ȫ����, Ϊ��֤����, OTP����, ֤��ǩ��, ������֤���)(��׼֤��ǩ�����ø�ʽ: ֤��SN;ǩ��ԭ��;֤����Ϣ;ǩ����Ϣ;��չ, ����Ҫʱ�ֶ����)
	TDX_ID_CA_VER,				// (4226) �汾��Ϣ( ��ʽ: ��˾����(ͨ����/����/����);�ͻ�������(�ͻ���/web/�ֻ�);�汾��(V1.0);...��չ�ֶ�)
	
	TDX_ID_CA_RESV,				// (825) Ԥ����Ϣ
};
const WORD tdxUPDSELFINFOFUNFieldAns[]=
{
	TDX_ID_CA_RESV,				// (825) �����ֶ�
};

// ��ѯ�û�������Ϣ 4528
const WORD tdxQRYUSERCOMMONFUNFieldReq[]=
{
	TDX_ID_CA_KHH,				// (800) �����ͻ���
	TDX_ID_JYMM,				// (134) ��������
	TDX_ID_CA_TXMM,				// (803) ��֤��Ϣ( ���ݰ�ȫ����, Ϊ��֤����, OTP����, ֤��ǩ��, ������֤���)(��׼֤��ǩ�����ø�ʽ: ֤��SN;ǩ��ԭ��;֤����Ϣ;ǩ����Ϣ;��չ, ����Ҫʱ�ֶ����)
	TDX_ID_CA_VER,				// (4226) �汾��Ϣ( ��ʽ: ��˾����(ͨ����/����/����);�ͻ�������(�ͻ���/web/�ֻ�);�汾��(V1.0);...��չ�ֶ�)
};
const WORD tdxQRYUSERCOMMONFUNFieldAns[]=
{
	TDX_ID_CA_DLSJ,				// (898) �ϴε�½ʱ�� (��ʽ:(YYYY/MM/DD HH:MI:SS))
	TDX_ID_CA_LASTIP,			// (890) �ϴε�¼��ַ
	TDX_ID_CA_MAC,				// (4211) �ϴε�¼MAC��ַ
	TDX_ID_CA_VER,				// (4226) �ϴε�¼�汾��Ϣ( ��ʽ: ��˾����(ͨ����/����/����)�ͻ�������(�ͻ���/web/�ֻ�)�汾��(V1.0) ����:ͨ���ſͻ���V6.01)
	TDX_ID_CA_CSCS,				// (4207) �ܵ�½����
	TDX_ID_CA_RESV,				// (825) Ԥ����Ϣ
};

// �û����ϲ�ѯ 4530
const WORD tdxQRYUDATAFUNFieldReq[]=
{
	TDX_ID_CA_KHH,				// (800) �����ͻ���
	TDX_ID_JYMM,				// (134) ��������
	TDX_ID_CA_TXMM,				// (803) ��֤��Ϣ( ���ݰ�ȫ����, Ϊ��֤����, OTP����, ֤��ǩ��, ������֤���)(��׼֤��ǩ�����ø�ʽ: ֤��SN;ǩ��ԭ��;֤����Ϣ;ǩ����Ϣ;��չ, ����Ҫʱ�ֶ����)
	TDX_ID_CA_VER,				// (4226) �汾��Ϣ( ��ʽ: ��˾����(ͨ����/����/����);�ͻ�������(�ͻ���/web/�ֻ�);�汾��(V1.0);...��չ�ֶ�)
};
const WORD tdxQRYUDATAFUNFieldAns[]=
{
	TDX_ID_CA_SJH,				// (860) �ͻ��ֻ���
	TDX_ID_CA_ZJHM,				// (861) �ͻ�֤������
	TDX_ID_CA_RESV,				// (825) �����ֶ�
};

// �����û����� 4532
const WORD tdxUPDUDATAFUNFieldReq[]=
{
	TDX_ID_CA_KHH,				// (800) �����ͻ���
	TDX_ID_JYMM,				// (134) ��������
	TDX_ID_CA_TXMM,				// (803) ��֤��Ϣ( ���ݰ�ȫ����, Ϊ��֤����, OTP����, ֤��ǩ��, ������֤���)(��׼֤��ǩ�����ø�ʽ: ֤��SN;ǩ��ԭ��;֤����Ϣ;ǩ����Ϣ;��չ, ����Ҫʱ�ֶ����)
	TDX_ID_CA_VER,				// (4226) �汾��Ϣ( ��ʽ: ��˾����(ͨ����/����/����);�ͻ�������(�ͻ���/web/�ֻ�);�汾��(V1.0);...��չ�ֶ�)

	TDX_ID_CA_SJH,				// (860) �ͻ��ֻ���
	TDX_ID_CA_ZJHM				// (861) �ͻ�֤������
};
const WORD tdxUPDUDATAFUNFieldAns[]=
{
	TDX_ID_CA_RESV,				// (825) �����ֶ�
};

// �ؼ�������ѯ 4534
const WORD tdxQRYIMPOTOPFUNFieldReq[]=
{
	TDX_ID_CA_KHH,				// (800) �����ͻ���
	TDX_ID_JYMM,				// (134) ��������
	TDX_ID_CA_TXMM,				// (803) ��֤��Ϣ( ���ݰ�ȫ����, Ϊ��֤����, OTP����, ֤��ǩ��, ������֤���)(��׼֤��ǩ�����ø�ʽ: ֤��SN;ǩ��ԭ��;֤����Ϣ;ǩ����Ϣ;��չ, ����Ҫʱ�ֶ����)
	TDX_ID_CA_VER,				// (4226) �汾��Ϣ( ��ʽ: ��˾����(ͨ����/����/����);�ͻ�������(�ͻ���/web/�ֻ�);�汾��(V1.0);...��չ�ֶ�)
};
const WORD tdxQRYIMPOTOPFUNFieldAns[]=
{
	TDX_ID_CA_CZBZ,				// (824) ������־(Ϊ���ܺŻ�������)
	TDX_ID_CA_RESV,				// (825) ����˵��
};

// �ؼ�������¼ 4536
const WORD tdxRCDIMPOTOPFUNFieldReq[]=
{
	TDX_ID_CA_KHH,				// (800) �����ͻ���
	TDX_ID_JYMM,				// (134) ��������
	TDX_ID_CA_TXMM,				// (803) ��֤��Ϣ( ���ݰ�ȫ����, Ϊ��֤����, OTP����, ֤��ǩ��, ������֤���)(��׼֤��ǩ�����ø�ʽ: ֤��SN;ǩ��ԭ��;֤����Ϣ;ǩ����Ϣ;��չ, ����Ҫʱ�ֶ����)
	TDX_ID_CA_VER,				// (4226) �汾��Ϣ( ��ʽ: ��˾����(ͨ����/����/����);�ͻ�������(�ͻ���/web/�ֻ�);�汾��(V1.0);...��չ�ֶ�)

	TDX_ID_CA_CZBZ,				// (824) ������־(����Ϊ���ܺ�, ��������)
	TDX_ID_CA_RESV,				// (825) ����˵��
};
const WORD tdxRCDIMPOTOPFUNFieldAns[]=
{
	TDX_ID_CA_RESV,				// (825) �����ֶ�
};

// ��֤��ʷ��ѯ 4538
const WORD tdxQRYAUTHHISFUNFieldReq[]=
{
	TDX_ID_CA_KHH,				// (800) �����ͻ���
	TDX_ID_JYMM,				// (134) ��������
	TDX_ID_CA_TXMM,				// (803) ��֤��Ϣ( ���ݰ�ȫ����, Ϊ��֤����, OTP����, ֤��ǩ��, ������֤���)(��׼֤��ǩ�����ø�ʽ: ֤��SN;ǩ��ԭ��;֤����Ϣ;ǩ����Ϣ;��չ, ����Ҫʱ�ֶ����)
	TDX_ID_CA_VER,				// (4226) �汾��Ϣ( ��ʽ: ��˾����(ͨ����/����/����);�ͻ�������(�ͻ���/web/�ֻ�);�汾��(V1.0);...��չ�ֶ�)

	TDX_ID_CA_QSRQ,				// (896) ��ʼ��ѯʱ��
 	TDX_ID_CA_ZZRQ,				// (897) ��ֹ��ѯʱ��
};
const WORD tdxQRYAUTHHISFUNFieldAns[]=
{
	TDX_ID_CA_DLSJ,				// (898) �ϴε�½ʱ�� (��ʽ:(YYYY/MM/DD HH:MI:SS))
	TDX_ID_CA_AQJB,				// (806) ��ȫ����
	TDX_ID_CA_LASTIP,			// (890) ��½IP
	TDX_ID_CA_MAC,				// (4211) ����MAC��ַ
	TDX_ID_CA_JQTZM,			// (4201) ����������
	TDX_ID_CA_VER,				// (4226) �汾��Ϣ( ��ʽ: ��˾����(ͨ����/����/����);�ͻ�������(�ͻ���/web/�ֻ�);�汾��(V1.0);...��չ�ֶ�)
	TDX_ID_CA_RESV,				// (825) ��֤���
};

// ���뱣���������� 4540
const WORD tdxREQQAPROTFUNFieldReq[]=
{
	TDX_ID_CA_KHH,				// (800) �����ͻ���
	TDX_ID_JYMM,				// (134) ��������
	TDX_ID_CA_TXMM,				// (803) ��֤��Ϣ( ���ݰ�ȫ����, Ϊ��֤����, OTP����, ֤��ǩ��, ������֤���)(��׼֤��ǩ�����ø�ʽ: ֤��SN;ǩ��ԭ��;֤����Ϣ;ǩ����Ϣ;��չ, ����Ҫʱ�ֶ����)
	TDX_ID_CA_VER,				// (4226) �汾��Ϣ( ��ʽ: ��˾����(ͨ����/����/����);�ͻ�������(�ͻ���/web/�ֻ�);�汾��(V1.0);...��չ�ֶ�)
	// �ݲ�֧��
};
const WORD tdxREQQAPROTFUNFieldAns[]=
{
	TDX_ID_CA_RESV,				// (825) �����ֶ�
};

// ���뱣�������޸� 4542
const WORD tdxMODQAPROTFUNFieldReq[]=
{
	TDX_ID_CA_KHH,				// (800) �����ͻ���
	TDX_ID_JYMM,				// (134) ��������
	TDX_ID_CA_TXMM,				// (803) ��֤��Ϣ( ���ݰ�ȫ����, Ϊ��֤����, OTP����, ֤��ǩ��, ������֤���)(��׼֤��ǩ�����ø�ʽ: ֤��SN;ǩ��ԭ��;֤����Ϣ;ǩ����Ϣ;��չ, ����Ҫʱ�ֶ����)
	TDX_ID_CA_VER,				// (4226) �汾��Ϣ( ��ʽ: ��˾����(ͨ����/����/����);�ͻ�������(�ͻ���/web/�ֻ�);�汾��(V1.0);...��չ�ֶ�)
	// �ݲ�֧��
};
const WORD tdxMODQAPROTFUNFieldAns[]=
{
	TDX_ID_CA_RESV,				// (825) �����ֶ�
};

// ���뱣��У�� 4544
const WORD tdxAUTHQAPROTFUNFieldReq[]=
{
	TDX_ID_CA_KHH,				// (800) �����ͻ���
	TDX_ID_JYMM,				// (134) ��������
	TDX_ID_CA_TXMM,				// (803) ��֤��Ϣ( ���ݰ�ȫ����, Ϊ��֤����, OTP����, ֤��ǩ��, ������֤���)(��׼֤��ǩ�����ø�ʽ: ֤��SN;ǩ��ԭ��;֤����Ϣ;ǩ����Ϣ;��չ, ����Ҫʱ�ֶ����)
	TDX_ID_CA_VER,				// (4226) �汾��Ϣ( ��ʽ: ��˾����(ͨ����/����/����);�ͻ�������(�ͻ���/web/�ֻ�);�汾��(V1.0);...��չ�ֶ�)
	// �ݲ�֧��
};
const WORD tdxAUTHQAPROTFUNFieldAns[]=
{
	TDX_ID_CA_RESV,				// (825) �����ֶ�
};

// Ӧ������ 4546
const WORD tdxRESVPWDFUNFieldReq[]=
{
	TDX_ID_CA_KHH,				// (800) �����ͻ���
	TDX_ID_JYMM,				// (134) ��������
	TDX_ID_CA_TXMM,				// (803) ��֤��Ϣ( ���ݰ�ȫ����, Ϊ��֤����, OTP����, ֤��ǩ��, ������֤���)(��׼֤��ǩ�����ø�ʽ: ֤��SN;ǩ��ԭ��;֤����Ϣ;ǩ����Ϣ;��չ, ����Ҫʱ�ֶ����)
	TDX_ID_CA_VER,				// (4226) �汾��Ϣ( ��ʽ: ��˾����(ͨ����/����/����);�ͻ�������(�ͻ���/web/�ֻ�);�汾��(V1.0);...��չ�ֶ�)
	// �ݲ�֧��
};
const WORD tdxRESVPWDFUNFieldAns[]=
{
	TDX_ID_CA_RESV,				// (825) �����ֶ�
};

const WORD tdxCONSISFUNFieldReq[]=
{
	TDX_ID_CA_KHH,				// (800) �����ͻ���
	TDX_ID_JYMM,				// (134) ��������
	TDX_ID_CA_GD_HARDINFO,		// (4244) �������������Ϣ
};
const WORD tdxCONSISFUNFieldAns[]=
{
	TDX_ID_CA_REMARK,			// (4504) �����ǩ����Ϣ
	TDX_ID_CA_RESV,				// (825) �����ֶ�
};


// �°汾��ȫ����( 4500 - 4600)

//////////////////////////////////////////////////////////////////////////
//	ģ�⽻�����
//////////////////////////////////////////////////////////////////////////

// ���������� 5000
const WORD tdxSYLPMFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_STARTPOS,			// ��ѯ��ʼλ��
};

// �ʻ���ȯ 5002 (N/A)
const WORD tdxZHRQFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ
};

// ��ȯ��ѯ 5004 (N/A)
const WORD tdxRQCXFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ
};

// �ʻ���ȯչ�� 5006 (N/A)
const WORD tdxZHHQZQFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ
};

// �������ļ�� 5008
const WORD tdxTCMONITORFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_INPUTPARAM,		// �������
};

// TS·�� 5010
const WORD tdxTSROUTINGFieldReq[]=
{
	TDX_ID_KHH,					// �ͻ���
	TDX_ID_JYMM,				// ��������
	TDX_ID_ZJZH,				// �ʽ��ʺ�(֧�ֶ��ʽ��ʺ�ʱ��,�����Ϳ�)
	TDX_ID_ZHLB,				// (����)�ʺ����
	TDX_ID_GDDM,				// (����)�ɶ�����
	TDX_ID_OP_WTFS,				// ί�з�ʽ

	TDX_ID_XT_FUNCNO,			// ���ܱ��(��������)
	TDX_ID_XT_MODE,				// ģʽ(��θ�ʽ����)
	TDX_ID_XT_PARAM,			// ����(�������)
	TDX_ID_XT_REMARK,			// ��ע(·����Ϣ)
	TDX_ID_XT_DESCRIPTION,		// ����(����˵��,����ʹ��)
};

const WORD tdxTSROUTINGFieldAns[]=
{
	TDX_ID_XT_FUNCNO,			// ���ܱ��(��������)
	TDX_ID_XT_MODE,				// ģʽ(���θ�ʽ����)
	TDX_ID_XT_PARAM,			// ����(��������)
	TDX_ID_XT_REMARK,			// ��ע(·����Ϣ)
	TDX_ID_XT_DESCRIPTION,		// ����(Ӧ��˵��,����ʹ��)
	TDX_ID_XT_ERRCODE,			// �������(ҵ��������)
	TDX_ID_XT_ERRMSG,			// ������Ϣ(ҵ�������Ϣ)

	TDX_ID_XT_RESERVED,			// ������Ϣ
};


//---------------------------------------------------------------------------
// Part.V �ṹ-�ֶζ���
//---------------------------------------------------------------------------

// ���ֵ䶨��
BEGIN_STRUCT_FIELD_DEF(tdxSimpleStructFieldInfo)
	// �˺�Ԥ���� 94
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZHYCL,tdxZHYCLFieldReq)
	// ��¼Ԥ���� 96
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_DLYCL,tdxDLYCLFieldReq)
	// ���ɿͻ�У�� 98|99
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_JCKHJY,tdxJCKHJYFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_JCKHJY,tdxJCKHJYFieldAns)
	// �ͻ�У�� 100
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KHJY,tdxKHJYFieldReq)
END_STRUCT_FIELD_DEF(tdxSimpleStructFieldInfo)

// �����ֵ䶨��
BEGIN_STRUCT_FIELD_DEF(tdxCommonStructFieldInfo)
	// �ͻ�У�� 100
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KHJY,tdxKHJYFieldReq)
	// �����ѯ 102
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CXHQ,tdxCXHQFieldReq)
	// �ʽ���� 104
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZJYE,tdxZJYEFieldReq)
	// �޸����� 106
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XGMM,tdxXGMMFieldReq)
	// �޸��ʽ����� 108
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XGZJMM,tdxXGZJMMFieldReq)
	// �������(��)�� 110
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_JSKMS,tdxJSKMSFieldReq)
	// ȡ������Ϣ 112
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CACHE,tdxCACHEFieldReq)
	// �޸Ĺ����ʽ��ʺ� 114
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XGGLZJZH,tdxXGGLZJZHFieldReq)
	// �ͻ�ע�� 116
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KHZX,tdxKHZXFieldReq)
	// ����ȡ�����ʵ�(�ʼ�) 118
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_DYQXDZD,tdxDYQXDZDFieldReq)
	// ί�ж����ʽ� 120
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_WTDJZJ,tdxWTDJZJFieldReq)
	// ��ӡ���ʵ� 122
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_PRINTDZD,tdxPRINTDZDFieldReq)
	// ��ӡ���ܶ��ʵ� 124
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_PRINTHZDZD,tdxPRINTHZDZDFieldReq)
	// ��ӡ��� 126
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_PRINTJGD,tdxPRINTJGDFieldReq)
	// �޸���֤���� 128
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XGTXMM,tdxXGTXMMFieldReq)
	// �ʺŽⶳ 130
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZHJD,tdxZHJDFieldReq)
	// �ʽ�鼯 132
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZJGJ,tdxZJGJFieldReq)
	// �ʽ��ʺż�ת�� 134
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZJZHJZZ,tdxZJZHJZZFieldReq)
	// �ύ�ʾ��� 136
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_TJWJJG,tdxTJWJJGFieldReq)
	// ��ȡ�ʾ����� 138
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HQWJNR,tdxHQWJNRFieldReq)
	// ��ȡ�ʺ�״̬��־ 140
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HQZHZTBZ,tdxHQZHZTBZFieldReq)
	// �����ѯ���� 142
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CLCXMM,tdxCLCXMMFieldReq)
	// ����ע�� 144
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_TSZC,tdxTSZCFieldReq)
	// ����ע�� 146
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_TSZX,tdxTSZXFieldReq)
	// ���ʺŲ�ѯ 148
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZZHCX,tdxZZHCXFieldReq)
	// ������֤��Ϣ 150
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CLRZXX,tdxCLRZXXFieldReq)
	// ��֤��Ϣ��ѯ 152
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_RZXXCX,tdxRZXXCXFieldReq)
	// �ͻ�������Ϣ��ѯ 154
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KHJBXXCX,tdxKHJBXXCXFieldReq)
	// ���Ӻ�ͬǩԼ 156
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_DZHTQY,tdxDZHTQYFieldReq)
	// ���Ӻ�ͬǩԼ��ѯ 158
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_DZHTQYCX,tdxDZHTQYCXFieldReq)
	// ���Ӻ�ͬ�б��ѯ 160
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_DZHTLBCX,tdxDZHTLBCXFieldReq)
	// ���Ӻ�ͬ��Ϣ��ѯ 162
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_DZHTXXCX,tdxDZHTXXCXFieldReq)
	// ��֤��ˮ��ѯ 164
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_RZLSCX,tdxRZLSCXFieldReq)
	// �ͻ�Ԥ����Ϣ��ѯ 166
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KHYLXXCX,tdxKHYLXXCXFieldReq)
	// �ͻ�Ԥ����Ϣ�޸� 168
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KHYLXXXG,tdxKHYLXXXGFieldReq)
	// �ͻ�����ȷ�� 170
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KHCZQR,tdxKHCZQRFieldReq)
	// �����ֵ��ѯ 172
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FYZDCX,tdxFYZDCXFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_FYZDCX,tdxFYZDCXFieldAns)
	// ���»Ự��Ϣ 174
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_UPDATESESSION,tdxUPDATESESSIONFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_UPDATESESSION,tdxUPDATESESSIONFieldAns)
	// �ʾ���ˮ��ѯ 176
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_WJLSCX,tdxWJLSCXFieldReq)
	// ��ȡ�г���Ϣ 178
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_SCINFO,tdxSCINFOFieldReq)

	// ί�г��� 200
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_WTCD,tdxWTCDFieldReq)
	// ��ͨ��Ʊί�� 202
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_PTGPWT,tdxPTGPWTFieldReq)
	// ծȯת�ɻ��� 204
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZQZGHS,tdxZQZGHSFieldReq)
	// �޸Ķ��� 206
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XGDD,tdxXGDDFieldReq)
	// �깺�¹� 208
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_SGXG,tdxSGXGFieldReq)
	// �¹��깺�޸� 210
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XGSGXG,tdxXGSGXGFieldReq)
	// �¹��깺���� 212
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XGSGCD,tdxXGSGCDFieldReq)
	// ����ί�� 214
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_PLWT,tdxPLWTFieldReq)
	// �������� 216
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_PLCD,tdxPLCDFieldReq)
	// ����������� 218
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XZDDJC,tdxXZDDJCFieldReq)
	// �޸Ķ������ 220
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XGDDJC,tdxXGDDJCFieldReq)

	// �������ʽ��ѯ 250
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_SDSZJCX,tdxSDSZJCXFieldReq)
	// �����ֹɷݲ�ѯ 252
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_SDSGFCX,tdxSDSGFCXFieldReq)
	// ������ί�в�ѯ 254
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_SDSWTCX,tdxSDSWTCXFieldReq)
	// �����ֳɽ���ѯ 256
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_SDSCJCX,tdxSDSCJCXFieldReq)
	// ��������ˮ��ѯ 258
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_SDSLSCX,tdxSDSLSCXFieldReq)
	// �����������ʲ���ѯ 260
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_SDSXYZCCX,tdxSDSXYZCCXFieldReq)
	// ������֤ȯ��Ϣ��ѯ 262
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_SDSZQXXCX,tdxSDSZQXXCXFieldReq)
	// �����ֿ���(��)������ѯ 264
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_SDSKMSLCX,tdxSDSKMSLCXFieldReq)

	// ������ǩ 300
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FQZQ,tdxFQZQFieldReq)
	// (����)�ͻ����ϲ�ѯ 302
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_KHZLCX,tdxFWKHZLCXFieldReq)
	// (����)��ȡ��̬���� 304
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_HQDTKL,tdxFWHQDTKLFieldReq)
	// (����)��Ʒ����Ʒ�� 306
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_CPDGPZ,tdxFWCPDGPZFieldReq)
	// (����)��Ʒ������ѯ 308
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_CPDGCX,tdxFWCPDGCXFieldReq)
	// (����)��Ʒ�������� 310
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_CPDGSZ,tdxFWCPDGSZFieldReq)
	// (����)��Ʒ�����޸� 312
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_CPDGXG,tdxFWCPDGXGFieldReq)
	// (����)��Ʒ����ȡ�� 314
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_CPDGQX,tdxFWCPDGQXFieldReq)
	// (����)�ʽ���ˮ 316
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_ZJLS,tdxFWZJLSFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_FW_ZJLS,tdxFWZJLSFieldAns)
	// (����)���������ѯ 318
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_PLHQCX,tdxFWPLHQCXFieldReq)
	// (����)��Ѷ��Ŀ��ѯ 320
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_ZXLMCX,tdxFWZXLMCXFieldReq)
	// (����)��ȡ��ʾ��Ϣ 322
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_HQTSXX,tdxFWHQTSXXFieldReq)
	// (����)ͶƱ������ѯ 324
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_TPFACX,tdxFWTPFACXFieldReq)
	// (����)ͶƱ��Ϣ��ѯ 326
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_TPXXCX,tdxFWTPXXCXFieldReq)
	// (����)ͶƱ����ύ 328
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_TPJGTJ,tdxFWTPJGTJFieldReq)
	// (����)ͶƱ�����ѯ 330
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_TPJGCX,tdxFWTPJGCXFieldReq)
	// (����)ͶƱͳ�Ʋ�ѯ 332
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_TPTJCX,tdxFWTPTJCXFieldReq)
	// (����)������ϴ����ѯ 334
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_TLZHDMCX,tdxFWTLZHDMCXFieldReq)
	// (����)������ϳɷֲ�ѯ 336
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_TLZHCFCX,tdxFWTLZHCFCXFieldReq)
	// (����)�����¼���� 338
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_DDDLCZ,tdxFWDDDLCZFieldReq)
	// (����)�����ּ۲�ѯ 340
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_PLXJCX,tdxFWPLXJCXFieldReq)
	// (����)��Ϣ���� 342
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_XXDY,tdxFWXXDYFieldReq)
	// (����)�ͻ������� 344
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_KHKCL,tdxFWKHKCLFieldReq)
	// (����)�ϴ�������Ϣ 346
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_SCPZXX,tdxFWSCPZXXFieldReq)
	// (����)����������Ϣ 348
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_XZPZXX,tdxFWXZPZXXFieldReq)
	// (����)������ϢժҪ��ѯ 350
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_PZXXZYCX,tdxFWPZXXZYCXFieldReq)
	// (����)����ͻ����� 352
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_CLKHCS,tdxFWCLKHCSFieldReq)
	// (����)����б��ѯ 354
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_PDLBCX,tdxFWPDLBCXFieldReq)
	// (����)�����ˮ¼�� 356
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_PDLSLR,tdxFWPDLSLRFieldReq)
	// (����)�����ˮ��ѯ 358
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_PDLSCX,tdxFWPDLSCXFieldReq)
	// (����)��ֵҵ���շ� 360
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FW_ZZYWSF,tdxFWZZYWSFFieldReq)

	// (����)ǿ���˳� 400 [���͹���,����ʹ��]
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_PUSH_QZTC,tdxQZTCFieldReq)
	// (����)��Ϣ֪ͨ 402 [���͹���,����ʹ��]
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_PUSH_XXTZ,tdxXXTZFieldReq)
	// (����)������Ϣ 404 [���͹���,����ʹ��]
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_PUSH_GGXX,tdxGGXXFieldReq)

	// (�ֻ�)֤ȯ��ѯ 500
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_ZQCX,tdxMOBILEZQCXFieldReq)
	// (�ֻ�)�ɷݲ�ѯ 502
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_GFCX,tdxMOBILEGFCXFieldReq)
	// (�ֻ�)�ʽ��ѯ 504
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_ZJCX,tdxMOBILEZJCXFieldReq)
	// (�ֻ�)������ѯ 506
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_CDCX,tdxMOBILECDCXFieldReq)
	// (�ֻ�)ί�в�ѯ 508
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_WTCX,tdxMOBILEWTCXFieldReq)
	// (�ֻ�)�ɽ���ѯ 510
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_CJCX,tdxMOBILECJCXFieldReq)
	// (�ֻ�)ת�˲�ѯ 512
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_ZZCX,tdxMOBILEZZCXFieldReq)
	// (�ֻ�)��ˮ��ѯ 514
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_LSCX,tdxMOBILELSCXFieldReq)
	// (�ֻ�)�����ѯ 516
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_JGCX,tdxMOBILEJGCXFieldReq)
	// (�ֻ�)���˲�ѯ 518
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_DZCX,tdxMOBILEDZCXFieldReq)
	// (�ֻ�)�����걨�����ѯ 520
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_YXSBHQCX,tdxMOBILEYXSBHQCXFieldReq)
	// (�ֻ�)��ʷί�в�ѯ 522
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_LSWTCX,tdxMOBILELSWTCXFieldReq)
	// (�ֻ�)��ʷ�ɽ���ѯ 524
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_LSCJCX,tdxMOBILELSCJCXFieldReq)
	// (�ֻ�)�����ǩ��ѯ 526
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_PHZQCX,tdxMOBILEPHZQCXFieldReq)
	// (�ֻ�)��֤��ˮ��ѯ 528
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_RZLSCX,tdxMOBILERZLSCXFieldReq)
	// (�ֻ�)���𳷵���ѯ 530
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_JJCDCX,tdxMOBILEJJCDCXFieldReq)
	// (�ֻ�)������ί�в�ѯ 532
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_JJDRWTCX,tdxMOBILEJJDRWTCXFieldReq)
	// (�ֻ�)������ʷί�в�ѯ 534
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_JJLSWTCX,tdxMOBILEJJLSWTCXFieldReq)
	// (�ֻ�)�����ճɽ���ѯ 536
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_JJDRCJCX,tdxMOBILEJJDRCJCXFieldReq)
	// (�ֻ�)������ʷ�ɽ���ѯ 538
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_JJLSCJCX,tdxMOBILEJJLSCJCXFieldReq)
	// (�ֻ�)�����˺Ų�ѯ 540
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_JJZHCX,tdxMOBILEJJZHCXFieldReq)
	// (�ֻ�)����˾��ѯ 542
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_JJGSCX,tdxMOBILEJJGSCXFieldReq)
	// (�ֻ�)��������ѯ 544
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_JJDMCX,tdxMOBILEJJDMCXFieldReq)
	// (�ֻ�)����ݶ��ѯ 546
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_JJFECX,tdxMOBILEJJFECXFieldReq)
	// (�ֻ�)������˲�ѯ 548
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_JJDZCX,tdxMOBILEJJDZCXFieldReq)
	// (�ֻ�)���𽻸��ѯ 550
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_JJJGCX,tdxMOBILEJJJGCXFieldReq)
	// (�ֻ�)����ǽ���ί�в�ѯ 552
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_JJFJYWTCX,tdxMOBILEJJFJYWTCXFieldReq)
	// (�ֻ�)�ڻ���Լ��ѯ 560
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_QHHYCX,tdxMOBILEQHHYCXFieldReq)
	// (�ֻ�)�ڻ���Ϻ�Լ��ѯ 562
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_QHZHHYCX,tdxMOBILEQHZHHYCXFieldReq)
	// (�ֻ�)�ڻ���ϳֲֲ�ѯ 564
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_QHZHCCCX,tdxMOBILEQHZHCCCXFieldReq)
	// (�ֻ�)�ڻ����ί�в�ѯ 566
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_QHZHWTCX,tdxMOBILEQHZHWTCXFieldReq)
	// (�ֻ�)�ڻ���ϲ��Բ�ѯ 568
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_QHZHCLCX,tdxMOBILEQHZHCLCXFieldReq)
	// (�ֻ�)�ɷݻ��ܲ�ѯ 570
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_GFHZCX,tdxMOBILEGFHZCXFieldReq)
	// (�ֻ�)ί�л��ܲ�ѯ 572
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_WTHZCX,tdxMOBILEWTHZCXFieldReq)
	// (�ֻ�)�ɽ����ܲ�ѯ 574
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_CJHZCX,tdxMOBILECJHZCXFieldReq)
	// (�ֻ�)�ɽ���ϸ��ѯ 576
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_CJMXCX,tdxMOBILECJMXCXFieldReq)

	// (�ֻ�)���������������ײ�ѯ 600
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_XYRZMRPTCX,tdxMOBILEXYRZMRPTCXFieldReq)
	// (�ֻ�)������ȯ�������ײ�ѯ 602
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_XYRQMCPTCX,tdxMOBILEXYRQMCPTCXFieldReq)
	// (�ֻ�)���������������ײ�ѯ 604
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_XYMCHKPTCX,tdxMOBILEXYMCHKPTCXFieldReq)
	// (�ֻ�)�������뻹ȯ���ײ�ѯ 606
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_XYMRHQPTCX,tdxMOBILEXYMRHQPTCXFieldReq)
	// (�ֻ�)�����ֽ𻹿����ײ�ѯ 608
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_XYXJHKPTCX,tdxMOBILEXYXJHKPTCXFieldReq)
	// (�ֻ�)������ȯ��ȯ���ײ�ѯ 610
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_XYXQHQPTCX,tdxMOBILEXYXQHQPTCXFieldReq)
	// (�ֻ�)������ȯ��ת���ײ�ѯ 612
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_XYYQHZPTCX,tdxMOBILEXYYQHZPTCXFieldReq)
	// (�ֻ�)���õ�����ת���ײ�ѯ 614
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_XYDBHZPTCX,tdxMOBILEXYDBHZPTCXFieldReq)
	// (�ֻ�)���õ���ת�����ײ�ѯ 616
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_XYDBZRPTCX,tdxMOBILEXYDBZRPTCXFieldReq)
	// (�ֻ�)���õ���ת�����ײ�ѯ 618
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_XYDBZCPTCX,tdxMOBILEXYDBZCPTCXFieldReq)
	// (�ֻ�)�����ʲ���Ϣ��ѯ 620
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_XYZCXXCX,tdxMOBILEXYZCXXCXFieldReq)
	// (�ֻ�)���ùɷ���Ϣ��ѯ 622
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_XYGFXXCX,tdxMOBILEXYGFXXCXFieldReq)
	// (�ֻ�)���ñ��֤ȯ��ѯ 624
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_XYBDZQCX,tdxMOBILEXYBDZQCXFieldReq)
	// (�ֻ�)����ֱ�ӻ�ת��ѯ 626
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_XYZJHZCX,tdxMOBILEXYZJHZCXFieldReq)
	// (�ֻ�)������Ϣ���ò�ѯ 628
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_XYLXFYCX,tdxMOBILEXYLXFYCXFieldReq)
	// (�ֻ�)����δƽ��Լ��ѯ 630
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_XYWPHYCX,tdxMOBILEXYWPHYCXFieldReq)
	// (�ֻ�)������ƽ��Լ��ѯ 632
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_XYYPHYCX,tdxMOBILEXYYPHYCXFieldReq)
	// (�ֻ�)���õ��պ�Լ��ѯ 634
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_XYDRHYCX,tdxMOBILEXYDRHYCXFieldReq)
	// (�ֻ�)�������ʺ�Լ��ѯ 636
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_XYRZHYCX,tdxMOBILEXYRZHYCXFieldReq)
	// (�ֻ�)������ȯ��Լ��ѯ 638
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_XYRQHYCX,tdxMOBILEXYRQHYCXFieldReq)
	// (�ֻ�)�����ʽ�ծ��ѯ 640
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_XYZJFZCX,tdxMOBILEXYZJFZCXFieldReq)
	// (�ֻ�)���ùɷݸ�ծ��ѯ 642
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_XYGFFZCX,tdxMOBILEXYGFFZCXFieldReq)
	// (�ֻ�)���ý��׵���Ʒ֤ȯ��ѯ 644
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_XYJYDBPZQCX,tdxMOBILEXYJYDBPZQCXFieldReq)
	// (�ֻ�)���ý��׷ǽ��׻�ת��ѯ 646
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_XYJYFJYHZCX,tdxMOBILEXYJYFJYHZCXFieldReq)
	// (�ֻ�)���ý��׸�ծ��ˮ��ѯ 648
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_XYJYFZLSCX,tdxMOBILEXYJYFZLSCXFieldReq)
	
	// (�ֻ�)ETFί�в�ѯ 700
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_ETFWTCX,tdxMOBILEETFWTCXFieldReq)
	// (�ֻ�)ETF�ɽ���ѯ 702
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_ETFCJCX,tdxMOBILEETFCJCXFieldReq)

	// (�ֻ�)��Ʋ�Ʒ�ݶ��ѯ 750
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_LCCPFECX,tdxMOBILELCCPFECXFieldReq)
	// (�ֻ�)��Ʋ�Ʒί�в�ѯ 752
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_LCCPWTCX,tdxMOBILELCCPWTCXFieldReq)
	// (�ֻ�)��Ʋ�Ʒ�ɽ���ѯ 754
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_LCCPCJCX,tdxMOBILELCCPCJCXFieldReq)
	// (�ֻ�)��Ʋ�Ʒ�����ѯ 756
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_LCCPDMCX,tdxMOBILELCCPDMCXFieldReq)
	// (�ֻ�)��Ʋ�Ʒ���ڶ����깺��ѯ 758
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_LCCPDQDESGCX,tdxMOBILELCCPDQDESGCXFieldReq)
	// (�ֻ�)������Ʋ�Ʒ�����ѯ 790
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_YHLCCPDMCX,tdxMOBILEYHLCCPDMCXFieldReq)
	// (�ֻ�)������Ʋ�Ʒ�ݶ��ѯ 792
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_YHLCCPFECX,tdxMOBILEYHLCCPFECXFieldReq)
	// (�ֻ�)������Ʋ�Ʒί�в�ѯ 794
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_YHLCCPWTCX,tdxMOBILEYHLCCPWTCXFieldReq)
	// (�ֻ�)������Ʋ�Ʒ�ɽ���ѯ 796
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_MOBILE_YHLCCPCJCX,tdxMOBILEYHLCCPCJCXFieldReq)

	// ��֤ת�� 900
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YZZZ,tdxYZZZFieldReq)
	// ������ˮ 902
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YHLS,tdxYHLSFieldReq)
	// ������� 904
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YHYE,tdxYHYEFieldReq)
	// �޸��������� 906
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XGYHMM,tdxXGYHMMFieldReq)
	// ������Ϣ 908
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YHXX,tdxYHXXFieldReq)
	
	// �������ת�� 910
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_SFCGZZ,tdxSFCGZZFieldReq)
	// ����ת�ʲ�ѯ 912
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_SFZZCX,tdxSFZZCXFieldReq)
	// ��������ѯ 914
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_SFYECX,tdxSFYECXFieldReq)

	// ת���޸� 916
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZZXG,tdxZZXGFieldReq)
	// ת��ȡ�� 918
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZZQX,tdxZZQXFieldReq)
	// ��ȡ�ʽ��ѯ 920
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KQZJCX,tdxKQZJCXFieldReq)
	// ת�����в�ѯ 922
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZZYHCX,tdxZZYHCXFieldReq)
	// �����˻���ת�� 924
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YHZHJZZ,tdxYHZHJZZFieldReq)
	// Զ���ʽ�ת�� 926
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YDZJZZ,tdxYDZJZZFieldReq)
	// Զ��ת�˲�ѯ 928
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YDZZCX,tdxYDZZCXFieldReq)
	// Զ���ʽ��ѯ 930
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YDZJCX,tdxYDZJCXFieldReq)
	// Զ�˿�ת��ѯ 932
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YDKZCX,tdxYDKZCXFieldReq)
	// ���п��б��ѯ 934
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YHKLBCX,tdxYHKLBCXFieldReq)
	// ���п���Ϣ��ѯ 936
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YHKXXCX,tdxYHKXXCXFieldReq)
	// ���п���Ϣ�޸� 938
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YHKXXXG,tdxYHKXXXGFieldReq)
	// ���п�������� 940
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YHKBGCZ,tdxYHKBGCZFieldReq)
	// ���п����ʲ�ѯ 942
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YHKFLCX,tdxYHKFLCXFieldReq)
	// �˺ż�ת����ˮ��ѯ 944
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZHJZZLSCX,tdxZHJZZLSCXFieldReq)
	// �˺ż�ת�˵�����ˮ��ѯ 946
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZHJZZDRLSCX,tdxZHJZZDRLSCXFieldReq)
	// ���������ˮ��ѯ 948
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YHYELSCX,tdxYHYELSCXFieldReq)
	// �ƻ�ת����ˮ��ѯ 950
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_JHZZLSCX,tdxJHZZLSCXFieldReq)
	// ����������ˮ��ѯ 952
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_DCGYHLSCX,tdxDCGYHLSCXFieldReq)
	// �����˺�ͬ�� 954
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_DCGZHTB,tdxDCGZHTBFieldReq)
	// ����ҵ����� 990
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HHYWCZ,tdxHHYWCZFieldReq)
	// �������в�ѯ 992
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HHYHCX,tdxHHYHCXFieldReq)
	// ������ʲ�ѯ 994
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HHHLCX,tdxHHHLCXFieldReq)
	// ����ί�в�ѯ 996
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HHWTCX,tdxHHWTCXFieldReq)

	// ������ѯ 1100
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CDCX,tdxCDCXFieldReq)
	// ����ί�в�ѯ 1102
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_DRWTCX,tdxDRWTCXFieldReq)
	// ��ʷί�в�ѯ 1104
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LSWTCX,tdxLSWTCXFieldReq)
	// ί�в�ѯ 1106
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_WTCX,tdxWTCXFieldReq)
	// ���ճɽ���ѯ 1108
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_DRCJCX,tdxDRCJCXFieldReq)
	// ��ʷ�ɽ���ѯ 1110
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LSCJCX,tdxLSCJCXFieldReq)
	// �ɽ���ѯ 1112
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CJCX,tdxCJCXFieldReq)
	// �ɷݲ�ѯ 1114
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_GFCX,tdxGFCXFieldReq)
	// �¹���� 1116
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XGPH,tdxXGPHFieldReq)
	// �ʽ���ˮ 1118
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZJLS,tdxZJLSFieldReq)
	// ��� 1120
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_JGD,tdxJGDFieldReq)
	// �ɶ���ѯ 1122
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_GDCX,tdxGDCXFieldReq)
	// ֤ȯ��Ϣ 1124
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZQXX,tdxZQXXFieldReq)
	// ��ǩ��ѯ 1126
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZQCX,tdxZQCXFieldReq)
	// �޸ĳɱ��� 1128
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XGCBJ,tdxXGCBJFieldReq)
	// (��ѯ)�޸���ϵ��ʽ 1130
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XGLXFS,tdxXGLXFSFieldReq)
	// ���ʵ� 1132
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_DZD,tdxDZDFieldReq)
	// ����Ȩ���ѯ 1134
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_PSQYCX,tdxPSQYCXFieldReq)
	// Ȩ֤��Ϣ��ѯ 1136
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_QZXXCX,tdxQZXXCXFieldReq)
	// �ɽ����ܲ�ѯ 1138
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CJHZCX,tdxCJHZCXFieldReq)
	// �ɷݻ��ܲ�ѯ 1140
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_GFHZCX,tdxGFHZCXFieldReq)
	// Ȩ֤��ͨȡ�� 1142
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KTXY,tdxQZKTQXFieldReq)
	// Ԥί�в�ѯ 1144
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YWTCX,tdxYWTCXFieldReq)
	// ǩ��Э�� 1146
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_QDXY,tdxQDXYFieldReq)
	// ��;�ʽ��ѯ 1148
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZTZJCX,tdxZTZJCXFieldReq)
	// �����ת�� 1150
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_JGXZZ,tdxJGXZZFieldReq)
	// ��֧���� 1152
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FZDM,tdxFZDMFieldReq)
	// ��ȡЭ������ 1154
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HQXYNR,tdxHQXYNRFieldReq)
	// ��ȡIPO�б� 1156
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HQIPOLB,tdxHQIPOLBFieldReq)
	// IPO��Ϣ��ѯ 1158
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_IPOXXCX,tdxIPOXXCXFieldReq)
	// Ԥ��ҪԼ��ѯ 1160
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YYCX,tdxYYCXFieldReq)
	// Ԥ��ҪԼ���� 1162
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YYCD,tdxYYCDFieldReq)
	// Ԥ��ҪԼ�걨 1164
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YYSB,tdxYYSBFieldReq)
	// ��ѹ�ع� 1166
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZYHG,tdxZYHGFieldReq)
	// δ���ճɽ���ϸ��ѯ 1168
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_WJSCJMXCX,tdxWJSCJMXFieldReq)
	// ���ԤԼ��ȡҵ�� 1170
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CGYYCQ,tdxCGYYCQFieldReq)
	// ���ԤԼ��ȡҵ���ѯ 1172
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CGYYCQCX,tdxCGYYCQCXFieldReq)
	// ί�л��ܲ�ѯ 1174
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_WTHZCX,tdxWTHZCXFieldReq)
	// �ʽ���ϸ��ѯ 1176
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZJMXCX,tdxZJMXCXFieldReq)
	// ��ѯѡ�������� 1178
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CXXZCGYH,tdxCXXZCGYHFieldReq)
	// ѡ�������� 1180
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XZCGYH,tdxXZCGYHFieldReq)
	// ��ѯЭ����Ϣ 1182
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CXXYXX,tdxCXXYXXFieldReq)
	// ��ʷ�ɽ����ܲ�ѯ 1184
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LSCJHZCX,tdxLSCJHZCXFieldReq)
	// �ɽ���ϸ��ѯ 1186
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CJMXCX,tdxCJMXCXFieldReq)
	// ί�в�ѯ��ϸ 1188
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_WTCXMX,tdxWTCXMXFieldReq)
	// �ɽ���ѯ��ϸ 1190
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CJCXMX,tdxCJCXMXFieldReq)
	// �����걨�����ѯ 1192
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YXSBHQCX,tdxYXSBHQCXFieldReq)
	// ����ί�в�ѯ 1194
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_PLWTCX,tdxPLWTCXFieldReq)
	// LOF�ϲ���ش����ѯ 1196
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LOFHBXGDMCX,tdxLOFHBXGDMCXFieldReq)
	// LOF�ֲ���ش����ѯ 1198
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LOFFCXGDMCX,tdxLOFFCXGDMCXFieldReq)
	// LOF�̺�ҵ����ί�в�ѯ 1200
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LOFPHYWDRWTCX,tdxLOFPHYWDRWTCXFieldReq)
	// LOF�̺�ҵ����ʷί�в�ѯ 1202
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LOFPHYWLSWTCX,tdxLOFPHYWLSWTCXFieldReq)
	// LOF�̺�ҵ���ճɽ���ѯ 1204
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LOFPHYWDRCJCX,tdxLOFPHYWDRCJCXFieldReq)
	// LOF�̺�ҵ����ʷ�ɽ���ѯ 1206
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LOFPHYWLSCJCX,tdxLOFPHYWLSCJCXFieldReq)
	// LOF�̺�ҵ�񳷵���ѯ 1208
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LOFPHYWCDCX,tdxLOFPHYWCDCXFieldReq)
	// �����ɷݲ�ѯ 1210
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FSGFCX,tdxFSGFCXFieldReq)
	// ֤ȯ������Ϣ��ѯ 1212
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZQFSXXCX,tdxZQFSXXCXFieldReq)
	// ����ת�ó�����ѯ 1214
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_BJZRCDCX,tdxBJZRCDCXFieldReq)
	// ����ת��ί�в�ѯ 1216
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_BJZRWTCX,tdxBJZRWTCXFieldReq)
	// ����ת�óɽ���ѯ 1218
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_BJZRCJCX,tdxBJZRCJCXFieldReq)
	// ��̬�ɷݲ�ѯ 1220
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_DTGFCX,tdxDTGFCXFieldReq)
	// ծȯ��Ѻ���ѯ 1222
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZQZYKCX,tdxZQZYKCXFieldReq)
	// �����ʽ���ϸ��ѯ 1224
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_DCGZJMXCX,tdxDCGZJMXCXFieldReq)
	// ��ʷ�ֲֲ�ѯ 1226
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LSCCCX,tdxLSCCCXFieldReq)
	// �ɷ���ϸ��ѯ 1228
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_GFMXCX,tdxGFMXCXFieldReq)
	// �ɷݲ�ѯ(2nd��) 1230
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_GFCX_SECOND,tdxGFCXSECONDFieldReq)
	// �ɷݲ�ѯ(3rd��) 1232
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_GFCX_THIRD,tdxGFCXTHIRDFieldReq)
	// ծȯ�ع���Լ��ѯ 1234
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZQHGHYCX,tdxZQHGHYCXFieldReq)
	// �ͻ�������Ϣ��ѯ 1236
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KHDZXXCX,tdxKHDZXXCXFieldReq)
	// �ۺ�Э�������ѯ 1238
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZHXYHQCX,tdxZHXYHQCXFieldReq)
	// ��׼ȯ���ܲ�ѯ 1240
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_BZQHZCX,tdxBZQHZCXFieldReq)
	// ��̨ծȯ�����ѯ 1242
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_GTZQHQCX,tdxGTZQHQCXFieldReq)
	// ������Ȩ��Լ��ѯ 1244
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_RZXQHYCX,tdxRZXQHYCXFieldReq)
	// ������Ȩ�ͻ���Ϣ��ѯ 1246
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_RZXQKHXXCX,tdxRZXQKHXXCXFieldReq)
	// ծȯ�ع���ʷ��ѯ 1248
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZQHGLSCX,tdxZQHGLSCXFieldReq)
	// ��Ȩ�����ѯ 1250
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_QQDMCX,tdxQQDMCXFieldReq)
	// ��Ȩ�ֲֲ�ѯ 1252
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_QQCCCX,tdxQQCCCXFieldReq)
	// ��Ȩ����˰��ѯ 1254
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_QQSDSCX,tdxQQSDSCXFieldReq)
	// ��Ȩ����ί�в�ѯ 1256
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_QQDRWTCX,tdxQQDRWTCXFieldReq)
	// ��Ȩ��ʷί�в�ѯ 1258
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_QQLSWTCX,tdxQQLSWTCXFieldReq)

	// �ڻ�ί�� 1500
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_QHWT,tdxQHWTFieldReq)
	// ��ѯ�ڻ��ֲ� 1502
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CXQHCC,tdxCXQHCCFieldReq)
	// ��ѯ��Լ��Ϣ 1504
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CXHYXX,tdxCXHYXXFieldReq)
	// ��ѯ�ɽ��׺�ͬ 1506
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CXKJYHY,tdxCXKJYHYFieldReq)
	// �����ʽ���ˮ 1508
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_DRZJLS,tdxDRZJLSFieldReq)
	// �ڻ�ί��״̬��ѯ 1510
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_QHWTZTCX,tdxQHWTZTCXFieldReq)
	// �ڻ�ί�лر� 1512 [���͹���,����ʹ��]
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_QHWTHB,tdxQHWTHBFieldReq)
	// �ڻ�ί�лر� 1513
	// �ڻ������ر� 1514 [���͹���,����ʹ��]
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_QHCDHB,tdxQHCDHBFieldReq)
	// �ڻ������ر� 1515
	// �ڻ��ɽ��ر� 1516 [���͹���,����ʹ��]
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_QHCJHB,tdxQHCJHBFieldReq)
	// �ڻ��ɽ��ر� 1517
	// �ڻ���Ϣ���� 1518 [���͹���,����ʹ��]
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_QHXXFB,tdxQHXXFBFieldReq)
	// �ڻ���Ϣ���� 1519
	// �ڻ�������״̬�ı� 1520 [���͹���,����ʹ��]
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_QHJYSZTGB,tdxQHJYSZTGBFieldReq)
	// �ڻ�������״̬�ı� 1521
	// �ڻ���Ϻ�Լ��� 1522 [���͹���,����ʹ��]
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_QHZHHYBG,tdxQHZHHYBGFieldReq)
	// �ڻ���Ϻ�Լ��� 1523
	// �ڻ����ί�лر� 1524 [���͹���,����ʹ��]
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_QHZHWTHB,tdxQHZHWTHBFieldReq)
	// �ڻ����ί�лر� 1525
	// �ڻ���ϳ����ر� 1526 [���͹���,����ʹ��]
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_QHZHCDHB,tdxQHZHCDHBFieldReq)
	// �ڻ���ϳ����ر� 1527
	// �ڻ��������Ͳ�ѯ 1528
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_QHDDLXCX,tdxQHDDLXCXFieldReq)
	// �ڻ����ί�� 1530
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_QHZHWT,tdxQHZHWTFieldReq)
	// �ڻ���ϳ��� 1532
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_QHZHCD,tdxQHZHCDFieldReq)
	// �ڻ���Ϻ�Լ��ѯ 1534
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_QHZHHYCX,tdxQHZHHYCXFieldReq)
	// �ڻ���ϳֲֲ�ѯ 1536
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_QHZHCCCX,tdxQHZHCCCXFieldReq)
	// �ڻ����ί�в�ѯ 1538
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_QHZHWTCX,tdxQHZHWTCXFieldReq)
	// �ڻ���ϼ����ί���� 1540
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_QHZHJSKWTS,tdxQHZHJSKWTSFieldReq)
	// �ڻ���ϲ��Բ�ѯ 1542
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_QHZHCLCX,tdxQHZHCLCXFieldReq)

	// ��Ʊ��Ѻ�ع� 1800
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_GPZYHG,tdxGPZYHGFieldReq)
	// ��Ʊ��Ѻ�ع������ѯ 1802
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_GPZYHG_SQCX,tdxGPZYHGSQCXFieldReq)
	// ��Ʊ��Ѻ�ع���ͬ��ѯ 1804
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_GPZYHG_HTCX,tdxGPZYHGHTCXFieldReq)
	// ��Ʊ��Ѻ�ع�Ȩ���ѯ 1806
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_GPZYHG_QYCX,tdxGPZYHGQYCXFieldReq)
	// ��Ʊ��Ѻ�ع��������ʲ�ѯ 1808
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_GPZYHG_QXLLCX,tdxGPZYHGQXLLCXFieldReq)
	// ��Ʊ��Ѻ�ع���ˮ��ѯ 1810
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_GPZYHG_LSCX,tdxGPZYHGLSCXFieldReq)
	// ��Ʊ��Ѻ�ع��ڳ�����ѯ 1812
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_GPZYHG_RCFCX,tdxGPZYHGRCFCXFieldReq)
	// ��Ʊ��Ѻ�ع���Ϣ��ѯ 1814
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_GPZYHG_LXCX,tdxGPZYHGLXCXFieldReq)
	// ��Ʊ��Ѻ�ع���ʷ��ͬ��ѯ 1816
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_GPZYHG_LSHTCX,tdxGPZYHGLSHTCXFieldReq)
	// ��Ʊ��Ѻ�ع����֤ȯ��ѯ 1818
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_GPZYHG_BDZQCX,tdxGPZYHGBDZQCXFieldReq)
	// ��ɫ�ع� 1830
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_TSHG,tdxTSHGFieldReq)
	// ��ɫ�ع���Ϣ��ѯ 1832
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_TSHG_XXCX,tdxTSHGXXCXFieldReq)
	// ��ɫ�ع������ѯ 1834
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_TSHG_SQCX,tdxTSHGSQCXFieldReq)
	// ��ɫ�ع������ѯ 1836
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_TSHG_DMCX,tdxTSHGDMCXFieldReq)
	// ��ɫ�ع���֤ͨ 1838
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_TSHG_YZT,tdxTSHGYZTFieldReq)
	// ��ɫ�ع�ת�˼ƻ���ѯ 1840
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_TSHG_ZZJHCX,tdxTSHGZZJHCXFieldReq)
	// ��ɫ�ع���ˮ��ѯ 1842
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_TSHG_LSCX,tdxTSHGLSCXFieldReq)							
	// ����״̬����(��ѯ) 2000
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_PSZTSZ,tdxPSZTSZFieldReq)
	// �����ع� 2002
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HZHG,tdxHZHGFieldReq)
	// �����ع�״̬(��ѯ) 2004
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HZHGZT,tdxHZHGZTFieldReq)
	// �����깺״̬(��ѯ) 2006
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HZSGZT,tdxHZSGZTFieldReq)
	// �����ع���Ʒ�����ѯ 2008
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HZHGCPDMCX,tdxHZHGCPDMCXFieldReq)
	// �����ع���Ʒ��Ϣ��ѯ 2010
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HZHGCPXXCX,tdxHZHGCPXXCXFieldReq)
	// �����ع���ǰ��ֹ��ѯ 2012
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HZHGTQZZCX,tdxHZHGTQZZCXFieldReq)
	// �����ع�����ί�в�ѯ 2014
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HZHGDRWTCX,tdxHZHGDRWTCXFieldReq)
	// �����ع����ճɽ���ѯ 2016
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HZHGDRCJCX,tdxHZHGDRCJCXFieldReq)
	// �����ع���ʷί�в�ѯ 2018
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HZHGLSWTCX,tdxHZHGLSWTCXFieldReq)
	// �����ع���ʷ�ɽ���ѯ 2020
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HZHGLSCJCX,tdxHZHGLSCJCXFieldReq)
	// �����ع����ں�Լ��ѯ 2022
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HZHGQNHYCX,tdxHZHGQNHYCXFieldReq)
	// �����ع�������ѯ 2024
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HZHGCDCX,tdxHZHGCDCXFieldReq)
	// �����ع���Լ��ѯ 2026
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HZHGXYCX,tdxHZHGXYCXFieldReq)
	// �����ع���Լ��ֹ��ѯ 2028
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HZHGXYZZCX,tdxHZHGXYZZCXFieldReq)
	// �����ع���ǰ��ֹԤԼ��ѯ 2030
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HZHGTQZZYYCX,tdxHZHGTQZZYYCXFieldReq)
	// �����ع���ǰ��ֹԤԼ������ѯ 2032
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HZHGTQZZYYCXCX,tdxHZHGTQZZYYCXCXFieldReq)
	// �����ع���Ӧ��Ѻ���ѯ 2034
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HZHGDYZYWCX,tdxHZHGDYZYWCXFieldReq)
	// �����ع���Լ������ѯ 2036
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HZHGXYCDCX,tdxHZHGXYCDCXFieldReq)
	// �����ع����յ��ڲ�ѯ 2038
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HZHGDRDQCX,tdxHZHGDRDQCXFieldReq)
	// �����ع���ʷ���ڲ�ѯ 2040
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HZHGLSDQCX,tdxHZHGLSDQCXFieldReq)
	// �����ع�������ֹԤԼ��ѯ 2042
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HZHGXZZZYYCX,tdxHZHGXZZZYYCXFieldReq)
	// �����ع�������ֹԤԼ������ѯ 2044
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HZHGXZZZYYCXCX,tdxHZHGXZZZYYCXCXFieldReq)
	// �����ع���Լ�����ѯ 2046
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HZHGXYBGCX,tdxHZHGXYBGCXFieldReq)
	// �����ع���Լ�����ѯ 2048
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HZHGHYSYCX,tdxHZHGHYSYCXFieldReq)
	// ���ڱ��ۻع���Ʒ�����ѯ 2050
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_SZBJHGCPDMCX,tdxSZBJHGCPDMCXFieldReq)
	// ���ڱ��ۻع����ں�Լ��ѯ 2052
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_SZBJHGQNHYCX,tdxSZBJHGQNHYCXFieldReq)
	// �����ع�Э���������ײ�ѯ 2054
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_HZHGXYSZPTCX,tdxHZHGXYSZPTCXFieldReq)


	// Լ���ع���ʼ�������ײ�ѯ 2070
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YDHGCSJYPTCX,tdxYDHGCSJYPTCXFieldReq)
	// Լ���ع���Լ�������ײ�ѯ 2072
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YDHGLYBZPTCX,tdxYDHGLYBZPTCXFieldReq)
	// Լ���ع���ǰ�������ײ�ѯ 2074
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YDHGTQGHPTCX,tdxYDHGTQGHPTCXFieldReq)
	// Լ���ع������������ײ�ѯ 2076
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YDHGYQSQPTCX,tdxYDHGYQSQPTCXFieldReq)
	// Լ���ع����׳������ײ�ѯ 2078
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YDHGJYCDPTCX,tdxYDHGJYCDPTCXFieldReq)
	// Լ���ع���ǰ��Լ��ѯ 2080
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YDHGDQHYCX,tdxYDHGDQHYCXFieldReq)
	// Լ���ع���ʷ��Լ��ѯ 2082
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YDHGLSHYCX,tdxYDHGLSHYCXFieldReq)
	// Լ���ع����к�Լ��ѯ 2084
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YDHGJXHYCX,tdxYDHGJXHYCXFieldReq)
	// Լ���ع���ֹ��Լ��ѯ 2086
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YDHGZZHYCX,tdxYDHGZZHYCXFieldReq)
	// Լ���ع����֤ȯ��ѯ 2088
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YDHGBDZQCX,tdxYDHGBDZQCXFieldReq)
	// Լ���ع���Ʒ��Ϣ��ѯ 2090
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YDHGCPXXCX,tdxYDHGCPXXCXFieldReq)
	// Լ���ع��ۺ���Ϣ��ѯ 2092
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YDHGZHXXCX,tdxYDHGZHXXCXFieldReq)
	// Լ���ع�ҵ�����(��Ϣ��ѯ) 2098
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YDHGYWCZ,tdxYDHGYWCZFieldReq)

	// ����ʽ����ί�� 2100
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJWT,tdxKFSJJWTFieldReq)
	// ����ʽ����ί�г��� 2102
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJWTCD,tdxKFSJJWTCDFieldReq)
	// ����ʽ����ת�� 2104
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJZH,tdxKFSJJZHFieldReq)
	// ����ʽ����ݶ��ѯ 2106
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJFECX,tdxKFSJJFECXFieldReq)
	// ����ʽ����ί�в�ѯ 2108
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJWTCX,tdxKFSJJWTCXFieldReq)
	// ����ʽ������Ϣ��ѯ 2110
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJXXCX,tdxKFSJJXXCXFieldReq)
	// ����ʽ����ɽ���ѯ 2112
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJCJCX,tdxKFSJJCJCXFieldReq)
	// ����ʽ����ֺ��趨 2114
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJFH,tdxKFSJJFHFieldReq)
	// ����ʽ��������ѯ 2116
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJDMCX,tdxKFSJJDMCXFieldReq)
	// ����ʽ�����ʽ��ʻ����� 2118
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJZJZHKH,tdxKFSJJZJZHKHFieldReq)
	// ����ʽ�����ʽ��ʻ�ע�� 2120
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJZJZHZC,tdxKFSJJZJZHZCFieldReq)
	// ����ʽ����ͻ������޸� 2122
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJKHZLXG,tdxKFSJJKHZLXGFieldReq)
	// ����ʽ�����ѯ��˾���� 2124
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJCXGSDM,tdxKFSJJCXGSDMFieldReq)
	// ����ʽ�����ʻ���ѯ 2126
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJZHCX,tdxKFSJJZHCXFieldReq)
	// ����ʽ����ί�в�ѯ 2128
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJLSWTCX,tdxKFSJJLSWTCXFieldReq)
	// ����ʽ����ʱ�����깺���� 2130
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJDSDESGSZ,tdxKFSJJDSDESGSZFieldReq)
	// ����ʽ����ʱ�����깺ȡ�� 2132
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJDSDESGQX,tdxKFSJJDSDESGQXFieldReq)
	//����ʽ����ʱ�����깺���ò�ѯ
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_DQDESZCX,tdxKFSJJDSDESZCXFieldReq)
	// ����ʽ�����ڶ����깺Ʒ�� 2134
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJCXDQDESGPZ,tdxKFSJJCXDQDESGPZFieldReq)
	// ����ʽ������ί�в�ѯ 2136
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJDRWTCX,tdxKFSJJDRWTCXFieldReq)
	// ����ʽ����ֺ��ѯ 2138
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJFHCX,tdxKFSJJFHCXFieldReq)
	// LOF����ֺ��ѯ 2140
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LOFJJFHCX,tdxLOFJJFHCXFieldReq)
	// LOF����ֺ��趨 2142
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LOFJJFH,tdxLOFJJFHFieldReq)
	// ����ʽ���������Ϣ��ѯ 2144
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJFXXXCX,tdxKFSJJFXXXCXFieldReq)
	// ����ʽ����ת�ʿ��� 2146
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJZZKH,tdxKFSJJZZKHFieldReq)
	// ����ʽ�����׿��� 2148
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJJYKH,tdxKFSJJJYKHFieldReq)
	// ���ճɽ���ѯ 2150
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJDRCJCX,tdxKFSJJDRCJCXFieldReq)
	// ��ʷ�ɽ���ѯ 2152
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJLSCJCX,tdxKFSJJLSCJCXFieldReq)
	// ����ʽ����ֵ��ѯ 2154
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJJZCX,tdxKFSJJJZCXFieldReq)
	// ����ʽ����Э���ѯ��ͨ 2156
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJXYCXKT,tdxKFSJJXYCXKTFieldReq)
	// ����ʽ����ֺ���ϸ��ѯ 2158
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJFHMXCX,tdxKFSJJFHMXCXFieldReq)
	// ����ʽ����ǽ���ί�в�ѯ 2162
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJFJYWTCX,tdxKFSJJFJYWTCXFieldReq)
	// ����ʽ����ǽ��׵���ί�в�ѯ 2164
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJFJYDRWTCX,tdxKFSJJFJYDRWTCXFieldReq)
	// ����ʽ������տɳ��ܴ����ѯ 2166
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJFXKCSDMCX,tdxKFSJJFXKCSDMCXFieldReq)
	// ����ʽ������ʲ�ѯ 2168
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJFLCX,tdxKFSJJFLCXFieldReq)
	// ����ʽ�����ڶ���������� 2170
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJDQDESHSZ,tdxKFSJJDQDESHSZFieldReq)
	// ����ʽ�����ڶ������ȡ�� 2172
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJDQDESHQX,tdxKFSJJDQDESHQXFieldReq)
	// ����ʽ�����ڶ�����ز�ѯ 2174
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJDQDESHCX,tdxKFSJJDQDESHCXFieldReq)
	// ����ʽ�����ڶ������Ʒ�� 2176
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJDQDESHPZ,tdxKFSJJDQDESHPZFieldReq)
	// ����ʽ������������Ϣ��ѯ 2178
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJDMXGXXCX,tdxKFSJJDMXGXXCXFieldReq)
	// ����ʽ����˾�����Ϣ��ѯ 2180
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJGSXGXXCX,tdxKFSJJGSXGXXCXFieldReq)
	// ����ʽ������˵���ѯ 2182
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJDZDCX,tdxKFSJJDZDCXFieldReq)
	// ����ʽ���𽻸��ѯ 2184
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KFSJJJGDCX,tdxKFSJJJGDCXFieldReq)

	// ��Ʋ�Ʒ�ݶ��ѯ 2200
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LCCPFECX,tdxLCCPFECXFieldReq)
	// ��Ʋ�Ʒί�в�ѯ 2202
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LCCPWTCX,tdxLCCPWTCXFieldReq)
	// ��Ʋ�Ʒ�ɽ���ѯ 2204
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LCCPCJCX,tdxLCCPCJCXFieldReq)
	// ��Ʋ�Ʒ����ί�в�ѯ 2206
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LCCPDRWTCX,tdxLCCPDRWTCXFieldReq)
	// ��Ʋ�Ʒ�����ѯ 2208
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LCCPDMCX,tdxLCCPDMCXFieldReq)
	// ��Ʋ�Ʒ�ʺŲ�ѯ 2210
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LCCPZHCX,tdxLCCPZHCXFieldReq)
	// ��Ʋ�Ʒ���ڶ����깺��ѯ 2212
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LCCPDQDESGCX,tdxLCCPDQDESGCXFieldReq)
	// ��Ʋ�Ʒ���ڶ����깺Ʒ�� 2214
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LCCPDQDESGPZ,tdxLCCPDQDESGPZFieldReq)
	// ��Ʋ�Ʒ��ֵ�ƻ��б��ѯ 2216
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LCCPZZJHLBCX,tdxLCCPZZJHLBCXFieldReq)
	// ��Ʋ�Ʒ��ֵ�ƻ���Ϣ��ѯ 2218
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LCCPZZJHXXCX,tdxLCCPZZJHXXCXFieldReq)
	// ��Ʋ�Ʒ��ֵ�ƻ�������� 2220
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LCCPZZJHJESZ,tdxLCCPZZJHJESZFieldReq)
	// ��Ʋ�Ʒ��ֵ�ƻ�״̬���� 2222
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LCCPZZJHZTSZ,tdxLCCPZZJHZTSZFieldReq)
	// ��Ʋ�Ʒ��ֵ�ƻ����Э�� 2224
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LCCPZZJHJCXY,tdxLCCPZZJHJCXYFieldReq)
	// ��Ʋ�Ʒ��ֵ�ƻ��ݶ��ѯ 2226
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LCCPZZJHFECX,tdxLCCPZZJHFECXFieldReq)
	// ��Ʋ�Ʒ��ֵ�ƻ�������ѯ 2228
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LCCPZZJHCDCX,tdxLCCPZZJHCDCXFieldReq)
	// ��Ʋ�Ʒ��ֵ�ƻ���Ϣ�޸� 2230
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LCCPZZJHXXXG,tdxLCCPZZJHXXXGFieldReq)
	// ��Ʋ�Ʒ��ֵ�ƻ��ݶ���� 2232
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LCCPZZJHFESH,tdxLCCPZZJHFESHFieldReq)
	// ��Ʋ�Ʒ��ֵ�ƻ�ί�г��� 2234
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LCCPZZJHWTCD,tdxLCCPZZJHWTCDFieldReq)
	// ��Ʋ�Ʒ��ֵ�ƻ�ԤԼȡ����� 2236
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LCCPZZJHYYQKCZ,tdxLCCPZZJHYYQKCZFieldReq)
	// ��Ʋ�Ʒ��ֵ�ƻ�ԤԼȡ���ѯ 2238
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LCCPZZJHYYQKCX,tdxLCCPZZJHYYQKCXFieldReq)
	// ��Ʋ�Ʒ��ֵ�ƻ���ʷ�����ѯ 2240
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LCCPZZJHLSSYCX,tdxLCCPZZJHLSSYCXFieldReq)
	// ������Ʋ�Ʒ�����Ϣ��ѯ 2242
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_DQLCCPSHXXCX,tdxDQLCCPSHXXCXFieldReq)
	// ��Ʋ�Ʒת�ô����ѯ 2244
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LCCPZRDMCX,tdxLCCPZRDMCXFieldReq)
	// ��Ʋ�Ʒת�������ѯ 2246
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LCCPZRHQCX,tdxLCCPZRHQCXFieldReq)
	// ��Ʋ�Ʒת�ó�����ѯ 2248
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LCCPZRCDCX,tdxLCCPZRCDCXFieldReq)
	// ��Ʋ�Ʒת��ί�в�ѯ 2250
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LCCPZRWTCX,tdxLCCPZRWTCXFieldReq)
	// ��Ʋ�Ʒת�óɽ���ѯ 2252
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LCCPZRCJCX,tdxLCCPZRCJCXFieldReq)
	// ��Ʋ�ƷǩԼ��Լ��ѯ 2254
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_LCCPQYJYCX,tdxLCCPQYJYCXFieldReq)
	// ������Ʋ�Ʒ�����ѯ 2256
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YHLCCPDMCX,tdxYHLCCPDMCXFieldReq)
	// ������Ʋ�Ʒ�ݶ��ѯ 2258
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YHLCCPFECX,tdxYHLCCPFECXFieldReq)
	// ������Ʋ�Ʒί�в�ѯ 2260
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YHLCCPWTCX,tdxYHLCCPWTCXFieldReq)
	// ������Ʋ�Ʒ�ʺŲ�ѯ 2262
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YHLCCPZHCX,tdxYHLCCPZHCXFieldReq)
	// ������Ʋ�Ʒ�ɽ���ѯ 2264
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YHLCCPCJCX,tdxYHLCCPCJCXFieldReq)
	// OTC�ݶ��ѯ 2266
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_OTCFECX,tdxOTCFECXFieldReq)
	// OTC�������ѯ 2268
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_OTCRSSCX,tdxOTCRSSCXFieldReq)
	// OTC�����걨��ѯ 2270
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_OTCYXSBCX,tdxOTCYXSBCXFieldReq)
	// OTC�ɽ��걨��ѯ 2272
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_OTCCJSBCX,tdxOTCCJSBCXFieldReq)
	// OTC��Ʒ��Լ��ѯ 2274
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_OTCCPHYCX,tdxOTCCPHYCXFieldReq)
	// OTC������Ϣ��ѯ 2276
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_OTCBJXXCX,tdxOTCBJXXCXFieldReq)
	// OTC������Ϣ��ѯ 2278
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_OTCHQXXCX,tdxOTCHQXXCXFieldReq)
	// OTC���Ӻ�ͬ�б��ѯ 2280
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_OTCDZHTLBCX,tdxOTCDZHTLBCXFieldReq)
	// OTC���Ӻ�ͬ��ѯ 2282
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_OTCDZHTCX,tdxOTCDZHTCXFieldReq)	
	// ���в�Ʒ�����ѯ 2300
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XTCPDMCX,tdxXTCPDMCXFieldReq)
	// ���в�Ʒ�ݶ��ѯ 2302
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XTCPFECX,tdxXTCPFECXFieldReq)
	// ���в�Ʒ�ʺŲ�ѯ 2304
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XTCPZHCX,tdxXTCPZHCXFieldReq)
	// ���в�Ʒί�в�ѯ 2306
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XTCPWTCX,tdxXTCPWTCXFieldReq)		
	// ���в�Ʒ�ɽ���ѯ 2308
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XTCPCJCX,tdxXTCPCJCXFieldReq)
	// ���в�Ʒ��ʷί�в�ѯ 2310
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XTCPLSWTCX,tdxXTCPLSWTCXFieldReq)

	// ����ֱ���Ϲ� 2500
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_JJZXRG,tdxJJZXRGFieldReq)
	// ����ֱ���깺 2502
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_JJZXSG,tdxJJZXSGFieldReq)
	// ����ֱ����� 2504
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_JJZXSH,tdxJJZXSHFieldReq)
	// ����ֱ���ֺ� 2506
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_JJZXFH,tdxJJZXFHFieldReq)
	// ����ֱ��ת�� 2508
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_JJZXZH,tdxJJZXZHFieldReq)
	// ����ֱ��ת�й� 2510
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_JJZXZTG,tdxJJZXZTGFieldReq)
	// ����ֱ������ 2512
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_JJZXCD,tdxJJZXCDFieldReq)
	// ����ֱ�����ʲ�ѯ 2514
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_JJZXFLCX,tdxJJZXFLCXFieldReq)
	// ����ֱ������֧�� 2516
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_JJZXYHZF,tdxJJZXYHZFFieldReq)
	// ����ֱ�������˴����ѯ 2518
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_JJZXXSRDMCX,tdxJJZXXSRDMCXFieldReq)
	// ����ֱ����Ϣ��� 2520
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_JJZXXXJC,tdxJJZXXXJCFieldReq)
	
	// ���������ڻ�������ѯ 2850
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_JYSCNJJDMCX,tdxJYSCNJJDMCXFieldReq)
	// ���������ڻ���ɷֹɲ�ѯ 2852
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_JYSCNJJCFGCX,tdxJYSCNJJCFGCXFieldReq)

	// ETF�Ϻ��羳�깺���ײ�ѯ 2950
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFSHKJSGPTCX,tdxETFSHKJSGPTCXFieldReq)
	// ETF���ڿ羳�깺���ײ�ѯ 2952
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFSZKJSGPTCX,tdxETFSZKJSGPTCXFieldReq)
	// ETF�Ϻ��羳������ײ�ѯ 2954
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFSHKJSHPTCX,tdxETFSHKJSHPTCXFieldReq)
	// ETF���ڿ羳������ײ�ѯ 2956
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFSZKJSHPTCX,tdxETFSZKJSHPTCXFieldReq)
	// ETF�Ϻ��羳ί�г�����ѯ 2958
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFSHKJWTCDCX,tdxETFSHKJWTCDCXFieldReq)
	// ETF���ڿ羳ί�г�����ѯ 2960
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFSZKJWTCDCX,tdxETFSZKJWTCDCXFieldReq)
	// ETF�Ϻ��羳����ί�в�ѯ 2962
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFSHKJDRWTCX,tdxETFSHKJDRWTCXFieldReq)
	// ETF���ڿ羳����ί�в�ѯ 2964
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFSZKJDRWTCX,tdxETFSZKJDRWTCXFieldReq)
	// ETF�Ϻ��羳���ճɽ���ѯ 2966
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFSHKJDRCJCX,tdxETFSHKJDRCJCXFieldReq)
	// ETF���ڿ羳���ճɽ���ѯ 2968
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFSZKJDRCJCX,tdxETFSZKJDRCJCXFieldReq)
	// ETF�Ϻ��羳��ʷί�в�ѯ 2970
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFSHKJLSWTCX,tdxETFSHKJLSWTCXFieldReq)
	// ETF���ڿ羳��ʷί�в�ѯ 2972
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFSZKJLSWTCX,tdxETFSZKJLSWTCXFieldReq)
	// ETF�Ϻ��羳��ʷ�ɽ���ѯ 2974
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFSHKJLSCJCX,tdxETFSHKJLSCJCXFieldReq)
	// ETF���ڿ羳��ʷ�ɽ���ѯ 2976
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFSZKJLSCJCX,tdxETFSZKJLSCJCXFieldReq)
	// ETF�����ֽ��Ϲ����ײ�ѯ 2980
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFWXXJRGPTCX,tdxETFWXXJRGPTCXFieldReq)
	// ETF���¹ɷ��Ϲ����ײ�ѯ 2982
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFWXGFRGPTCX,tdxETFWXGFRGPTCXFieldReq)
	// ETF�����ֽ��Ϲ�������ѯ 2984
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFWXXJRGCDCX,tdxETFWXXJRGCDCXFieldReq)
	// ETF���¹ɷ��Ϲ�������ѯ 2986
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFWXGFRGCDCX,tdxETFWXGFRGCDCXFieldReq)
	// ETF�����ֽ��Ϲ���Ϣ��ѯ 2988
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFWXXJRGXXCX,tdxETFWXXJRGXXCXFieldReq)
	// ETF���¹ɷ��Ϲ���Ϣ��ѯ 2990
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFWXGFRGXXCX,tdxETFWXGFRGXXCXFieldReq)
	// ETF�����ֽ��Ϲ���ˮ��ѯ 2992
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFWXXJRGLSCX,tdxETFWXXJRGLSCXFieldReq)
	// ETF���¹ɷ��Ϲ���ˮ��ѯ 2994
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFWXGFRGLSCX,tdxETFWXGFRGLSCXFieldReq)
	// ETF���� 3000
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFMM,tdxETFMMFieldReq)
	// ETF��Ϣ��ѯ 3002
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFXXCX,tdxETFXXCXFieldReq)
	// ETF�Ϲ���ѯ 3004
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFRGCX,tdxETFRGCXFieldReq)
	// ETF�Ϲ����� 3006
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFRGCD,tdxETFRGCDFieldReq)
	// ETF���κ� 3008
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFPCH,tdxETFPCHFieldReq)
	// ETF��Ʊ������ 3010
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFGPLMM,tdxETFGPLMMFieldReq)
	// ETF��Ʊ����ѯ 3012
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFGPLCX,tdxETFGPLCXFieldReq)
	// ETFԤ����ѯ 3014
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFYGCX,tdxETFYGCXFieldReq)
	// ETFί�г��� 3016
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFWTCX,tdxETFWTCXFieldReq)
	// ETF�ɽ���ѯ 3018
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFCJCX,tdxETFCJCXFieldReq)
	// ETF���Բ�ѯ 3020
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFCLCX,tdxETFCLCXFieldReq)
	// ETFָ�������ѯ 3022
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFZSDMCX,tdxETFZSDMCXFieldReq)
	// ETF(ί��)ȷ�� 3024
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFQR,tdxETFQRFieldReq)
	// ETFί�в�ѯ��ϸ 3026
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFWTCXMX,tdxETFWTCXMXFieldReq)
	// ETF�Ϲ�������ѯ 3028
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFRGCDCX,tdxETFRGCDCXFieldReq)
	// ETFָ���ɷֲ�ѯ 3030
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFZSCFCX,tdxETFZSCFCXFieldReq)
	// ETF�ɷݲ�ѯ 3032
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFGFCX,tdxETFGFCXFieldReq)
	// ETF���깺�ɷֹɲ�ѯ 3034
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFKSGCFGCX,tdxETFKSGCFGCXFieldReq)
	// ETF��Ʊ������ 3036
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFGPLCD,tdxETFGPLCDFieldReq)
	// ETF��Ʊ��������ѯ 3038
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFGPLCDCX,tdxETFGPLCDCXFieldReq)
	// ETF���г����̲�ѯ 3040
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ETFKSCDPCX,tdxETFKSCDPCXFieldReq)

	// ���ͨ���κ� 3050
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZHTPCH,tdxZHTPCHFieldReq)
	// ���ͨ��Ʊ������ 3052
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZHTGPLMM,tdxZHTGPLMMFieldReq)
	// ���ͨ��Ʊ����ѯ 3054
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZHTGPLCX,tdxZHTGPLCXFieldReq)
	// ���ͨӵ�ɲ�ѯ 3056
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZHTYGCX,tdxZHTYGCXFieldReq)
	// ���ͨί�в�ѯ 3058
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZHTWTCX,tdxZHTWTCXFieldReq)
	// ���ͨ�ɽ���ѯ 3060
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZHTCJCX,tdxZHTCJCXFieldReq)
	// ���ͨ���Բ�ѯ 3062
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZHTCLCX,tdxZHTCLCXFieldReq)
	// ���ָͨ�������ѯ 3064
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZHTZSDMCX,tdxZHTZSDMCXFieldReq)
	// ���ͨȷ�� 3066
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZHTQR,tdxZHTQRFieldReq)
	// ���ͨ��ʷ��ѯ 3068
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZHTLSCX,tdxZHTLSCXFieldReq)
	// ���ͨ��ʷ��ѯ��ϸ 3070
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZHTLSCXMX,tdxZHTLSCXMXFieldReq)
	// ���ͨί�в�ѯ��ϸ 3072
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZHTWTCXMX,tdxZHTWTCXMXFieldReq)
	// ���ͨ�ɽ���ѯ��ϸ 3074
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZHTCJCXMX,tdxZHTCJCXMXFieldReq)
	// ���ָͨ���ɷֲ�ѯ 3076
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZHTZSCFCX,tdxZHTZSCFCXFieldReq)

	// (����)��ȡ�Ự�� 3100
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_TL_HQHHH,tdxTLHQHHHFieldReq)
	// (����)��ϴ����ѯ 3102
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_TL_ZHDMCX,tdxTLZHDMCXFieldReq)
	// (����)��ϳɷֲ�ѯ 3104
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_TL_ZHCFCX,tdxTLZHCFCXFieldReq)
	// (����)��ϴ������ 3106
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_TL_ZHDMCZ,tdxTLZHDMCZFieldReq)
	// (����)��ϳɷֲ��� 3108
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_TL_ZHCFCZ,tdxTLZHCFCZFieldReq)
	// (����)���Դ����ѯ 3110
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_TL_CLDMCX,tdxTLCLDMCXFieldReq)
	// (����)���Գɷֲ�ѯ 3112
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_TL_CLCFCX,tdxTLCLCFCXFieldReq)
	// (����)���Դ������ 3114
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_TL_CLDMCZ,tdxTLCLDMCZFieldReq)
	// (����)���Գɷֲ��� 3116
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_TL_CLCFCZ,tdxTLCLCFCZFieldReq)
	// (����)���Ų��� 3118
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_TL_PHCZ,tdxTLPHCZFieldReq)
	// (����)���Ų�ѯ 3120
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_TL_PHCX,tdxTLPHCXFieldReq)
	// (����)����ί���б� 3122
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_TL_PHWTLB,tdxTLPHWTLBFieldReq)
	// (����)����ί��ִ�� 3124
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_TL_PHWTZX,tdxTLPHWTZXFieldReq)
	// (����)����ί�в�ѯ 3126
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_TL_PHWTCX,tdxTLPHWTCXFieldReq)
	// (����)���ųֲֲ�ѯ 3128
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_TL_PHCCCX,tdxTLPHCCCXFieldReq)

	// (�㷨����)�������� 3190
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_SFJY_DDCZ,tdxSFJYDDCZFieldReq)
	// (�㷨����)�����б��ѯ 3192
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_SFJY_DDLBCX,tdxSFJYDDLBCXFieldReq)
	// (�㷨����)���������ѯ 3194
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_SFJY_DDJGCX,tdxSFJYDDJGCXFieldReq)

	// �����ʲ���ѯ 3200
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYZCCX,tdxXYZCCXFieldReq)
	// ���ùɷݲ�ѯ 3202
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYGFCX,tdxXYGFCXFieldReq)
	// ���ú�Լ��ѯ(Ĭ��δƽ��) 3204
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYHYCX,tdxXYHYCXFieldReq)
	// ���ú�Լ��ƽ�ֲ�ѯ 3206
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYHYYPCCX,tdxXYHYCXFieldReq)
	// �������޲�ѯ 3208
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYSXCX,tdxXYSXCXFieldReq)
	// ���ø�ծ��ѯ 3210
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYFZCX,tdxXYFZCXFieldReq)
	// �������ʲ���ѯ 3212
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_FXYZCCX,tdxFXYZCCXFieldReq)
	// ���ú�Լ���ղ�ѯ 3214
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYHYDRCX,tdxXYHYDRCXFieldReq)
	// ���ý��ױ��֤ȯ��ѯ 3216
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYBDZQCX,tdxXYJYBDZQCXFieldReq)
	// ���ý����ۺ���Ϣ��ѯ 3218
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYZHXXCX,tdxXYJYZHXXCXFieldReq)
	// ���ý��׵���Ʒ֤ȯ��ѯ 3220
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYDBPZQCX,tdxXYJYDBPZQCXFieldReq)
	// ���ý�����������֤ȯ��ѯ 3222
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYRZMRZQCX,tdxXYJYRZMRZQCXFieldReq)
	// ���ý�����ȯ����֤ȯ��ѯ 3224
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYRQMCZQCX,tdxXYJYRQMCZQCXFieldReq)
	// ���ý��״�����ʾ��Ϣ��ѯ 3226
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYDMTSXXCX,tdxXYJYDMTSXXCXFieldReq)
	// ���ý��׺�Լ���ܲ�ѯ 3228
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYHYHZCX,tdxXYJYHYHZCXFieldReq)
	// ���ý��������������ײ�ѯ 3230
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYRZMRPTCX,tdxXYJYRZMRPTCXFieldReq)
	// ���ý�����ȯ�������ײ�ѯ 3232
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYRQMCPTCX,tdxXYJYRQMCPTCXFieldReq)
	// ���ý�����ȯ��ȯ���ײ�ѯ 3234
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYMQHQPTCX,tdxXYJYMQHQPTCXFieldReq)
	// ���ý�����ȯ��ת���ײ�ѯ 3236
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYYQHZPTCX,tdxXYJYYQHZPTCXFieldReq)
	// ���ý�����ȯ��ȯ���ײ�ѯ 3238
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYXQHQPTCX,tdxXYJYXQHQPTCXFieldReq)
	// ���ý��׵���Ʒ��ת���ײ�ѯ 3240
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYDBPHZPTCX,tdxXYJYDBPHZPTCXFieldReq)
	// ���ý��׵���Ʒ�������ײ�ѯ 3242
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYDBPHRPTCX,tdxXYJYDBPHRPTCXFieldReq)
	// ���ý��׵���Ʒ�������ײ�ѯ 3244
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYDBPHCPTCX,tdxXYJYDBPHCPTCXFieldReq)
	// ���ý����ֽ𻹿����ײ�ѯ 3246
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYXJHKPTCX,tdxXYJYXJHKPTCXFieldReq)
	// ���ý�����ȯ�������ײ�ѯ 3248
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYMQHKPTCX,tdxXYJYMQHKPTCXFieldReq)
	// ���ý�������ƽ���������ײ�ѯ 3250
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYRZPCMCPTCX,tdxXYJYRZPCMCPTCXFieldReq)
	// ���ý�����ȯƽ���������ײ�ѯ 3252
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYRQPCMRPTCX,tdxXYJYRQPCMRPTCXFieldReq)
	// ���ý���������Ϣ��ѯ 3254
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYLLXXCX,tdxXYJYLLXXCXFieldReq)
	// ���ý�����ȯ����ѯ 3256
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYRQYECX,tdxXYJYRQYECXFieldReq)
	// ���ý�����������ѯ 3258
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYRZYECX,tdxXYJYRZYECXFieldReq)
	// ���ý��׷ǽ��׻�ת��ѯ 3260
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYFJYHZCX,tdxXYJYFJYHZCXFieldReq)
	// ���ý�����Ϣ���ò�ѯ 3262
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYLXFYCX,tdxXYJYLXFYCXFieldReq)
	// ���ý����ʽ�ծ��ѯ 3264
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYZJFZCX,tdxXYJYZJFZCXFieldReq)
	// ���ý���֤ȯ��ծ��ѯ 3266
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYZQFZCX,tdxXYJYZQFZCXFieldReq)
	// ���ý��׿ͻ�ǩԼ��ѯ 3268
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYKHQYCX,tdxXYJYKHQYCXFieldReq)
	// ���ý��׿ͻ�Э�鴦�� 3270
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYKHXYCL,tdxXYJYKHXYCLFieldReq)
	// ���ý��׳�����ϸ��ѯ 3272
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYCHMXCX,tdxXYJYCHMXCXFieldReq)
	// ���ý������ʺ�Լ��ѯ 3274
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYRZHYCX,tdxXYJYRZHYCXFieldReq)
	// ���ý�����ȯ��Լ��ѯ 3276
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYRQHYCX,tdxXYJYRQHYCXFieldReq)
	// ���ý��׵���Ʒ��ת��ѯ 3278
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYDBPHZCX,tdxXYJYDBPHZCXFieldReq)
	// ���ý������뵣��Ʒ���ײ�ѯ 3280
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYMRDBPPTCX,tdxXYJYMRDBPPTCXFieldReq)
	// ���ý�����������Ʒ���ײ�ѯ 3282
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYMCDBPPTCX,tdxXYJYMCDBPPTCXFieldReq)
	// ���ý��׹黹��ȯ�������ײ�ѯ 3284
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYGHRQFYPTCX,tdxXYJYGHRQFYPTCXFieldReq)
	// ���ý��׸�ծ��ˮ��ѯ 3286
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYFZLSCX,tdxXYJYFZLSCXFieldReq)
	// ���ý����ֽ������ȯ���ײ�ѯ 3288
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYXJTDHQPTCX,tdxXYJYXJTDHQPTCXFieldReq)
	// ���ý���ά�ֵ������ʲ�ѯ 3290
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYWCDBBLCX,tdxXYJYWCDBBLCXFieldReq)
	// ���ý��׶�ȹ��� 3292
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYEDGL,tdxXYJYEDGLFieldReq)
	// ���ý��׶�ȱ����ѯ 3294
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYEDBGCX,tdxXYJYEDBGCXFieldReq)
	// ���ý���ƽ�����ʺ�Լ��ѯ 3296
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYPCRZHYCX,tdxXYJYPCRZHYCXFieldReq)
	// ���ý���ƽ����ȯ��Լ��ѯ 3298
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XYJYPCRQHYCX,tdxXYJYPCRQHYCXFieldReq)

	// ת��ͨҵ����� 3400
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTYWCZ,tdxZRTYWCZFieldReq)
	// ת��ͨ���֤ȯ��ѯ 3402
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTBDZQCX,tdxZRTBDZQCXFieldReq)
	// ת��ͨ�ʽ���Ϣ��ѯ 3404
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTZJXXCX,tdxZRTZJXXCXFieldReq)
	// ת��ͨ�ɷ���Ϣ��ѯ 3406
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTGFXXCX,tdxZRTGFXXCXFieldReq)
	// ת��ͨ�����������ײ�ѯ 3408
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTRZMRPTCX,tdxZRTRZMRPTCXFieldReq)
	// ת��ͨ��ȯ�������ײ�ѯ 3410
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTRQMCPTCX,tdxZRTRQMCPTCXFieldReq)
	// ת��ͨ�ʽ�����������ײ�ѯ 3412
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTZJJRSQPTCX,tdxZRTZJJRSQPTCXFieldReq)
	// ת��ͨ�ɷݽ����������ײ�ѯ 3414
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTGFJRSQPTCX,tdxZRTGFJRSQPTCXFieldReq)
	// ת��ͨ����չ���������ײ�ѯ 3416
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTJRZQSQPTCX,tdxZRTJRZQSQPTCXFieldReq)
	// ת��ͨ��ǰ�黹�������ײ�ѯ 3418
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTTQGHSQPTCX,tdxZRTTQGHSQPTCXFieldReq)
	// ת��ͨ����ҵ�񳷵���ѯ 3420
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTJRYWCDCX,tdxZRTJRYWCDCXFieldReq)
	// ת��ͨ����ҵ���ղ�ѯ 3422
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTJRYWDRCX,tdxZRTJRYWDRCXFieldReq)
	// ת��ͨ����ҵ����ʷ��ѯ 3424
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTJRYWLSCX,tdxZRTJRYWLSCXFieldReq)
	// ת��ͨ���ս����Լ��ѯ 3426
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTDRJRHYCX,tdxZRTDRJRHYCXFieldReq)
	// ת��ͨδ�˽����Լ��ѯ 3428
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTWLJRHYCX,tdxZRTWLJRHYCXFieldReq)
	// ת��ͨ���˽����Լ��ѯ 3430
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTYLJRHYCX,tdxZRTYLJRHYCXFieldReq)
	// ת��ͨ�ʽ�����������ײ�ѯ 3432
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTZJCJSQPTCX,tdxZRTZJCJSQPTCXFieldReq)
	// ת��ͨ�ɷݳ����������ײ�ѯ 3434
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTGFCJSQPTCX,tdxZRTGFCJSQPTCXFieldReq)
	// ת��ͨ�ʽ����ȷ�����ײ�ѯ 3436
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTZJCJQDPTCX,tdxZRTZJCJQDPTCXFieldReq)
	// ת��ͨ�ɷݳ���ȷ�����ײ�ѯ 3438
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTGFCJQDPTCX,tdxZRTGFCJQDPTCXFieldReq)
	// ת��ͨ����ҵ�񳷵���ѯ 3440
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTCJYWCDCX,tdxZRTCJYWCDCXFieldReq)
	// ת��ͨ����ҵ���ղ�ѯ 3442
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTCJYWDRCX,tdxZRTCJYWDRCXFieldReq)
	// ת��ͨ����ҵ����ʷ��ѯ 3444
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTCJYWLSCX,tdxZRTCJYWLSCXFieldReq)
	// ת��ͨ������ǰ�������ײ�ѯ 3446
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTCJTQSHPTCX,tdxZRTCJTQSHPTCXFieldReq)
	// ת��ͨ����ͬ��չ�����ײ�ѯ 3448
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTCJTYZQPTCX,tdxZRTCJTYZQPTCXFieldReq)
	// ת��ͨ���޷��ʲ�ѯ 3450
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTQXFLCX,tdxZRTQXFLCXFieldReq)
	// ת��ͨ�����Լ��ѯ 3452
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTCJHYCX,tdxZRTCJHYCXFieldReq)
	// ת��ͨ������ʷ��Լ��ѯ 3454
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTCJLSHYCX,tdxZRTCJLSHYCXFieldReq)
	// ת��ͨ�����������ײ�ѯ 3456
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTMCHKPTCX,tdxZRTMCHKPTCXFieldReq)
	// ת��ͨ���뻹ȯ���ײ�ѯ 3458
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTMRHQPTCX,tdxZRTMRHQPTCXFieldReq)
	// ת��ͨ�ֽ𻹿����ײ�ѯ 3460
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTXJHKPTCX,tdxZRTXJHKPTCXFieldReq)
	// ת��ͨ��ȯ��ȯ���ײ�ѯ 3462
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTXQHQPTCX,tdxZRTXQHQPTCXFieldReq)
	// ת��ͨ�ɳ�����Ϣ��ѯ 3464
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTKCJXXCX,tdxZRTKCJXXCXFieldReq)
	// ת��ͨ����ͬ���������ײ�ѯ 3466
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTJRTYSHPTCX,tdxZRTJRTYSHPTCXFieldReq)
	// ת��ͨ�����˻���Ϣ��ѯ 3468
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZRTCJZHXXCX,tdxZRTCJZHXXCXFieldReq)

	// (����)��ͨȡ���Զ����� 4100
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XLYZT_KTQXZDDL,tdxXLKTQXZDDLFieldReq)
	// (����)��ͨ�������� 4102
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XLYZT_KTHZPS,tdxXLKTHZPSFieldReq)
	// (����)ȡ���������� 4104
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XLYZT_QXHZPS,tdxXLQXHZPSFieldReq)
	// (����)��ͨ�����ع� 4106
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XLYZT_KTHZHG,tdxXLKTHZHGFieldReq)
	// (����)ȡ�������ع� 4108
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XLYZT_QXHZHG,tdxXLQXHZHGFieldReq)
	// (����)��ͨ�����깺 4110
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XLYZT_KTHZSG,tdxXLKTHZSGFieldReq)
	// (����)ȡ�������깺 4112
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XLYZT_QXHZSG,tdxXLQXHZSGFieldReq)
	// (����)�����ܲ�ѯ 4114
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XLYZT_DLGNCX,tdxXLDLGNCXFieldReq)
	// ���������� 5000
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_SYLPM,tdxSYLPMFieldReq)
	// �ʻ���ȯ 5002
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZHRQ,tdxZHRQFieldReq)
	// ��ȯ��ѯ 5004
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_RQCX,tdxRQCXFieldReq)
	// �ʻ���ȯչ�� 5006
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_ZHHQZQ,tdxZHHQZQFieldReq)
	// �������ļ�� 5008
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_TCMONITOR,tdxTCMONITORFieldReq)
	// TS·�� 5010
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_TSROUTING,tdxTSROUTINGFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_TSROUTING,tdxTSROUTINGFieldAns)
END_STRUCT_FIELD_DEF(tdxCommonStructFieldInfo)

// ��ȫ�����ֵ䶨��
BEGIN_STRUCT_FIELD_DEF(tdxScntrStructFieldInfo)
	// ��ȫ����Э��

	// CA�˻����� 800
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_ZHSQ,tdxCAZHSQFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_ZHSQ,tdxCAZHSQFieldAns)

	// CA�ʺŲ�ѯ 802
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_ZHCX,tdxCAZHCXFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_ZHCX,tdxCAZHCXFieldAns)

	// CA�˻�У�� 804
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_ZHJY,tdxCAZHJYFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_ZHJY,tdxCAZHJYFieldAns)

	// CA��֤�����޸� 806
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_TXMMXG,tdxCATXMMXGFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_TXMMXG,tdxCATXMMXGFieldAns)

	// CA��֤�����ѯ 808
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_TXMMCX,tdxCATXMMCXFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_TXMMCX,tdxCATXMMCXFieldAns)

	// CA֤������ 810
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_ZSXZ,tdxCAZSXZFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_ZSXZ,tdxCAZSXZFieldAns)

	// CA֤������ȷ�� 812
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_ZSXZQR,tdxCAZSXZQRFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_ZSXZQR,tdxCAZSXZQRFieldAns)

	// �ʺ�״̬�޸� 814
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_ZTXM,tdxCAZTXGFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_ZTXM,tdxCAZTXGFieldAns)

	// CA֤����� 816
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_ZSGX,tdxCAZSGXFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_ZSGX,tdxCAZSGXFieldAns)

	// �û��ּ���ѯ 818
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_YHFJCX,tdxCAYHFJCXFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_YHFJCX,tdxCAYHFJCXFieldAns)

	// �û��ּ����� 820
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_YHFJSQ,tdxCAYHFJSQFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_YHFJSQ,tdxCAYHFJSQFieldAns)

	// HTTP�û��ּ���ѯ 822
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_HTTPYHFJCX,tdxCAHTTPYHFJCXFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_HTTPYHFJCX,tdxCAHTTPYHFJCXFieldAns)

	// (ע��)�����û� 824
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_ANONUSER,tdxCANMZCFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_ANONUSER,tdxCANMZCFieldAns)
	
	// �½����� 826
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_XJZT,tdxCAXJZTFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_XJZT,tdxCAXJZTFieldAns)
	
	// ��ѯ���� 828
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_CXZT,tdxCACXZTFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_CXZT,tdxCACXZTFieldAns)
	
	// ��ѯ�ظ� 830
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_CXHF,tdxCACXHFFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_CXHF,tdxCACXHFFieldAns)
	
	// �ظ����� 832
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_HFZT,tdxCAHFZTFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_HFZT,tdxCAHFZTFieldAns)
	
	// (������)�ر����� 834
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_GBZT,tdxCAGBZTFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_GBZT,tdxCAGBZTFieldAns)
	
	// �û�(����)��Ϣ 836
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_USERMESSAGE,tdxCAYHLYFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_USERMESSAGE,tdxCAYHLYFieldAns)

	// �����û����� 838
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_USERACTION,tdxCANMJHFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_USERACTION,tdxCANMJHFieldAns)

	// �����û���¼ 840
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_ANONYLOGIN,tdxCANMDLFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_ANONYLOGIN,tdxCANMDLFieldAns)

	// ��ѯ�Ƿ����������� 842
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_QUERYMSG,tdxCANEWMSGFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_QUERYMSG,tdxCANEWMSGFieldAns)

	// ���Ķ����� 844
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_READED,tdxCAREADMSGFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_READED,tdxCAREADMSGFieldAns)

	// �û����漰����������Ϣ 846
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_NOTICEINFO,tdxNOTICEINFOFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_NOTICEINFO,tdxNOTICEINFOFieldAns)

	// �û���Ѷ��Ϣ���� 848
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_INFOFEEDBACK,tdxINFOFEEDBACKFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_INFOFEEDBACK,tdxINFOFEEDBACKFieldAns)

	// TQУ�� 860
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_TQ_KHJY,tdxTQKHJYFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_TQ_KHJY,tdxTQKHJYFieldAns)

	// ����֤ȯ�û�Ͷ�ʹ�����Ϣ 862
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_UM_UBROKER,tdxUMUBROKERFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_UM_UBROKER,tdxUMUBROKERFieldAns)

	// ����(�û�)ע�� 880
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_SYZC_GD,tdxCASYZCGDFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_SYZC_GD,tdxCASYZCGDFieldAns)

	// (��ϸ)��Ϣ¼�� 882
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_XXLR_GD,tdxCAXXLRGDFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_XXLR_GD,tdxCAXXLRGDFieldAns)

	// ����(�û�)���� 884
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_SYJH_GD,tdxCASYJHGDFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_SYJH_GD,tdxCASYJHGDFieldAns)
	
	// �˻�У�� 886
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_ZHJY_GD,tdxCAZHJYGDFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_ZHJY_GD,tdxCAZHJYGDFieldAns)
	
	// �ȼ���ѯ 888
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_DJCX_GD,tdxCADJCXGDFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_DJCX_GD,tdxCADJCXGDFieldAns)

	// ����(��)��(��)��ѯ 890
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_KSJCX_GD,tdxCAKSJCXGDFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_KSJCX_GD,tdxCAKSJCXGDFieldAns)

	// �ͻ�����(����) 892
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_KHSQ_GD,tdxCAKHSQGDFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_KHSQ_GD,tdxCAKHSQGDFieldAns)

	// �û���ѶȨ�� 894
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_YHZXQX_GD,tdxCAYHZXQXFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_YHZXQX_GD,tdxCAYHZXQXFieldAns)

	// �û�Ȩ��ע�� 896
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_YHQXZX,tdxCAYHQXZXFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_YHQXZX,tdxCAYHQXZXFieldAns)

	// ��ѯ��½��ʷ 898
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_CXDLLS,tdxCACXDLLSFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_CXDLLS,tdxCACXDLLSFieldAns)

 	// ��ȫ�������� 4200
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_AQGNSQ,tdxCAAQGNSQFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_AQGNSQ,tdxCAAQGNSQFieldAns)

	//��ȫ���ܳ��� 4202
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_AQGNCX,tdxCAAQGNCXFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_AQGNCX,tdxCAAQGNCXFieldAns)

	// ���뱣������У�� 4204
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_MMBHWTJY,tdxCAMMBHWTJYFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_MMBHWTJY,tdxCAMMBHWTJYFieldAns)

	// ��ȡ��ս���� 4206
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_GETTZZB,tdxCAGETTZZBFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_GETTZZB,tdxCAGETTZZBFieldAns)

	// ע������ 4208
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_ZXJZK,tdxCAZXJZKFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_ZXJZK,tdxCAZXJZKFieldAns)

	// Ԥ������ 4210
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_YLWT,tdxCAYLWTFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_YLWT,tdxCAYLWTFieldAns)

	// ֤������ 4212
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_CERRAREQ,tdxCACERRAREQFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_CERRAREQ,tdxCACERRAREQFieldAns)

	// ֤����� 4214
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_CERAUDIT,tdxCACERAUDITFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_CERAUDIT,tdxCACERAUDITFieldAns)

	// ֤������ 4216
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_CERDOWNLOAD,tdxCACERDOWNLOADFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_CERDOWNLOAD,tdxCACERDOWNLOADFieldAns)

	// ֤������ȷ�� 4218
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_CERDLCONFIRM,tdxCACERDLCONFIRMFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_CERDLCONFIRM,tdxCACERDLCONFIRMFieldAns)
	
	// ����û���Ϣ 4220
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_ADDYHXX,tdxCAADDYHXXFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_ADDYHXX,tdxCAADDYHXXFieldAns)

	// �޸��û���Ϣ 4222
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_XGYHXX,tdxCAXGYHXXFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_XGYHXX,tdxCAXGYHXXFieldAns)

	// ��ѯ�û���Ϣ 4224
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_CXYHXX,tdxCACXYHXXFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_CXYHXX,tdxCACXYHXXFieldAns)

	// ��ȡ�ֻ���֤�� 4226
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_GETYZM,tdxCAGETYZMFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_GETYZM,tdxCAGETYZMFieldAns)

	// ��֤��У�� 4228
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_YZMJY,tdxCAYZMJYFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_YZMJY,tdxCAYZMJYFieldAns)

	// ������ȫ��֤У�� 4230
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_OTHERCA_BASEFUN,tdxOTHCABASEFUNFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_OTHERCA_BASEFUN,tdxOTHCABASEFUNFieldAns)

	// ��ѯ���뱣������ 4232
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_MMBHWTCX,tdxCAMMBHWTCXFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_MMBHWTCX,tdxCAMMBHWTCXFieldAns)

	// �޸����뱣������ 4234
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_XGMMBHWT,tdxCAXGMMBHWTFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_XGMMBHWT,tdxCAXGMMBHWTFieldAns)

	// �޸�Ԥ������ 4236
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_XGYLWT,tdxCAXGYLWTFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_XGYLWT,tdxCAXGYLWTFieldAns)

	// ���뱣�������б��ѯ 4238
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_PWDPROTQUEQU,tdxPWDPROTQUEQUFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_PWDPROTQUEQU,tdxPWDPROTQUEQUFieldAns)

	// �������뱣������ 4240
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_APPLYPWDQA,tdxAPPLYPWDQAFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_APPLYPWDQA,tdxAPPLYPWDQAFieldAns)

	// �������������� 4242
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_BINDMACHINE,tdxBINDINFOFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_BINDMACHINE,tdxBINDINFOFieldAns)

	// ��ѯ����Ϣ 4244
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_QUEBINDINFO,tdxQUEBINDINFOFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_QUEBINDINFO,tdxQUEBINDINFOFieldAns)

	// ȡ������Ϣ 4246
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_CANCELBIND,tdxCANCELBINDFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_CANCELBIND,tdxCANCELBINDFieldAns)

	// ��ȫ����״̬��ѯ 4248
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_SAFEMODQUE,tdxSAFEMODQUEFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_SAFEMODQUE,tdxSAFEMODQUEFieldAns)

	// �����û���ȫ���� 4250
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CA_ABUSERLV,tdxABUSERLVFieldReq)
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_ANS_CA_ABUSERLV,tdxABUSERLVFieldAns)

	// �û����� 4252
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_CA_USERLOGOUT, tdxUSERLOGOUTFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_CA_USERLOGOUT, tdxUSERLOGOUTFieldAns)

	// �û��������� 4254
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_CA_USERALIVE, tdxUSERALIVEFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_CA_USERALIVE, tdxUSERALIVEFieldAns)

	// ȡ���û����� 4256
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_CA_CANCELLV, tdxCANCELLVFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_CA_CANCELLV, tdxCANCELLVFieldAns)

	// ��ȡ��Ʒ���� 4258
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_CA_GETPROINFO, tdxGETPROINFOFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_CA_GETPROINFO, tdxGETPROINFOFieldAns)

	// ע���û� 4280
 	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_CA_REGUSER, tdxREGUSERFieldReq)
 	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_CA_REGUSER, tdxREGUSERFieldAns)
	
	// �޸�ע������ 4282
 	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_CA_ALTERREGPWD, tdxALTERREGPWDFieldReq)
 	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_CA_ALTERREGPWD, tdxALTERREGPWDFieldAns)
	// �����½���Ʋ��� 4284
 	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_CA_SSO, tdxSSOFieldReq)
 	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_CA_SSO, tdxSSOFieldAns)
	// �����½��������ȡ�û���Ϣ 4286
 	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_CA_SSOYHXX, tdxSSOYHXXFieldReq)
 	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_CA_SSOYHXX, tdxSSOYHXXFieldAns)
	// ֤�����
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_CA_CERDEL, tdxCERDELFieldReq)
 	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_CA_CERDEL, tdxCERDELFieldAns)
	// ��̬����ͬ��
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_CA_OTPSYN, tdxOTPSYNFieldReq)
 	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_CA_OTPSYN, tdxOTPSYNFieldAns)
	// �������һ����
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_CA_CHECKRECORD, tdxCHECKRECORDFieldReq)
 	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_CA_CHECKRECORD, tdxCHECKRECORDFieldAns)
	// �û���֤ 4294
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_CA_PAAUTH, tdxPAAUTHFieldReq)
 	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_CA_PAAUTH, tdxPAAUTHFieldAns)
	// Ͷ����ϱ��� 4296
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_CA_ACCREPORT, tdxPAACCREPORTFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_CA_ACCREPORT, tdxPAACCREPORTFieldAns)
	// OTP����		4298
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_CA_OTPTEMP, tdxOTPTEMPFieldReq)
 	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_CA_OTPTEMP, tdxOTPTEMPFieldAns)
	// ��ȡ�����ֻ���֤�� 4300
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_OTHERCA_GETYZM, tdxOTHCAGETYZMFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_OTHERCA_GETYZM, tdxOTHCAGETYZMFUNFieldAns)
	// ��ѡ���ϴ�����
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_OPMYSTOCK, tdxOPMYSTOCKFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_OPMYSTOCK, tdxOPMYSTOCKFUNFieldAns)

	// �һ��û����� 4304
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_FETCHPWD, tdxFETCHPWDFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_FETCHPWD, tdxFETCHPWDFUNFieldAns)

	// ע���û���Ϣ��ѯ 4310
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_QUERYREGUDATA, tdxQUERYREGUDATAFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_QUERYREGUDATA, tdxQUERYREGUDATAFUNFieldAns)

	// �һ��û��ʺ� 4306
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_FETCHUSERACCOUNT, tdxFETCHUSERACCOUNTFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_FETCHUSERACCOUNT, tdxFETCHUSERACCOUNTFUNFieldAns)

	// ���ֲ�ѯ
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_QUERYSCORE, tdxQUERYSCOREFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_QUERYSCORE, tdxQUERYSCOREFUNFieldAns)

	// ��ȡ������ 4312
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_GETACTIVECODE, tdxGETACTIVECODEFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_GETACTIVECODE, tdxGETACTIVECODEFUNFieldAns)

	// ��ȫ���ܲ�ѯ 4500
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_QRYSCFUNC, tdxQRYSCFUNCFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_QRYSCFUNC, tdxQRYSCFUNCFUNFieldAns)

	// ����/�رհ�ȫ���� 4502
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_SWITCHSCFUNC, tdxSWITCHSCFUNCFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_SWITCHSCFUNC, tdxSWITCHSCFUNCFUNFieldAns)

	// ͳһ��֤ 4504
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_UNIAUTH, tdxUNIAUTHFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_UNIAUTH, tdxUNIAUTHFUNFieldAns)

	// ������֤���� 4506
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_REQAPWD, tdxREQAPWDFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_REQAPWD, tdxREQAPWDFUNFieldAns)

	// �޸���֤���� 4508
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_MODAPWD, tdxMODAPWDFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_MODAPWD, tdxMODAPWDFUNFieldAns)

	// ������֤���� 4510
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_RESETAPWD, tdxRESETAPWDFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_RESETAPWD, tdxRESETAPWDFUNFieldAns)

	// ͬ��OTP 4512
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_SYNOTP, tdxSYNOTPFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_SYNOTP, tdxSYNOTPFUNFieldAns)
	
	// ��ȡ֤��ǩ���� 4514
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_GETCSIGNKEY, tdxGETCSIGNKEYFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_GETCSIGNKEY, tdxGETCSIGNKEYFUNFieldAns)

	// ����֤�� 4516
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_UPDCERT, tdxUPDCERTFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_UPDCERT, tdxUPDCERTFUNFieldAns)

	// ��ȡ�ֻ���̬�� 4518
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_GETCCODE, tdxGETCCODEFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_GETCCODE, tdxGETCCODEFUNFieldAns)

	// ��Ȩ����� 4520
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_PERMITMACHINE, tdxPERMITMACHINEFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_PERMITMACHINE, tdxPERMITMACHINEFUNFieldAns)

	// ����������Ȩ 4522
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_FREEMACHINE, tdxFREEMACHINEFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_FREEMACHINE, tdxFREEMACHINEFUNFieldAns)

	// ��ѯ��Ȩ 4524
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_QRYPERMITION, tdxQRYPERMITIONFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_QRYPERMITION, tdxQRYPERMITIONFUNFieldAns)

	// ����Ԥ����Ϣ 4526
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_UPDSELFINFO, tdxUPDSELFINFOFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_UPDSELFINFO, tdxUPDSELFINFOFUNFieldAns)
		
	// ��ѯ�û�������Ϣ 4528
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_QRYUSERCOMMON, tdxQRYUSERCOMMONFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_QRYUSERCOMMON, tdxQRYUSERCOMMONFUNFieldAns)
		
	// �û����ϲ�ѯ 4530
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_QRYUDATA, tdxQRYUDATAFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_QRYUDATA, tdxQRYUDATAFUNFieldAns)
		
	// �����û����� 4532
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_UPDUDATA, tdxUPDUDATAFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_UPDUDATA, tdxUPDUDATAFUNFieldAns)
		
	// �ؼ�������ѯ 4534
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_QRYIMPOTOP, tdxQRYIMPOTOPFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_QRYIMPOTOP, tdxQRYIMPOTOPFUNFieldAns)
		
	// �ؼ�������¼ 4536
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_RCDIMPOTOP, tdxRCDIMPOTOPFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_RCDIMPOTOP, tdxRCDIMPOTOPFUNFieldAns)
		
	// ��֤��ʷ��ѯ 4538
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_QRYAUTHHIS, tdxQRYAUTHHISFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_QRYAUTHHIS, tdxQRYAUTHHISFUNFieldAns)
		
	// ���뱣���������� 4540
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_REQQAPROT, tdxREQQAPROTFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_REQQAPROT, tdxREQQAPROTFUNFieldAns)
		
	// ���뱣�������޸� 4542
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_MODQAPROT, tdxMODQAPROTFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_MODQAPROT, tdxMODQAPROTFUNFieldAns)
		
	// ���뱣��У�� 4544
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_AUTHQAPROT, tdxAUTHQAPROTFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_AUTHQAPROT, tdxAUTHQAPROTFUNFieldAns)
	
	// Ӧ������ 4546
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_RESVPWD, tdxRESVPWDFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_RESVPWD, tdxRESVPWDFUNFieldAns)

	// ���������ǩ����Ϣ 4548
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_REQ_CONSIS, tdxCONSISFUNFieldReq)
	DECLARE_STRUCT_FIELD( TDX_ID_FUNC_ANS_CONSIS, tdxCONSISFUNFieldAns)
	
END_STRUCT_FIELD_DEF(tdxCommonStructFieldInfo)


// ��־�鿴�ֵ䶨��
BEGIN_STRUCT_FIELD_DEF(tdxRZStructFieldInfo)

	// (��־)�ͻ�У�� 100
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_KHJY,tdxRZKHJYFieldReq)

	// (��־)ȡ������Ϣ 112
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_CACHE,tdxRZCACHEFieldReq)

	// (��־)�ɶ���ѯ 1122
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_GDCX,tdxRZGDCXFieldReq)

	// (��־)������Ϣ 908
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_YHXX,tdxRZYHXXFieldReq)

	// (��־)�޸����� 106
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_XGMM,tdxRZXGMMFieldReq)

	// �ͻ�������¼��ѯ 1002
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_RZ_KHCZJLCX,tdxRZKHCZJLCXFieldReq)

	// �˺����� 1004
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_RZ_ZHSQ,tdxRZZHSQFieldReq)

	// �˺Ŷ���ⶳ 1006
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_RZ_ZHDJJD,tdxRZZHDJJDFieldReq)

	// ��ѯͳ�Ʒ��� 1008
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_RZ_CXTJFX,tdxRZCXTJFXFieldReq)

	// ������رղ�ѯ 1010
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_RZ_QDYGBCX,tdxRZQDYGBCXFieldReq)

	// ��̨��æ�̶� 1012
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_RZ_HTFMCD,tdxRZHTFMCDFieldReq)

	// ��̨�����ɲ�ѯ 1014
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_RZ_HTCFHCX,tdxRZHTCFHCXFieldReq)

	// ����IP���� 1016
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_RZ_FXIPPM,tdxRZFXIPPMFieldReq)

	// �����˺� 1018
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_RZ_FXZH,tdxRZFXZHFieldReq)

	// ������ϸ��Ϣ 1020
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_RZ_FXXXXX,tdxRZFXXXXXFieldReq)

	// ��̨��æ�̶���ϸ 1022
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_RZ_HTFMCDXX,tdxRZHTFMCDXXFieldReq)

	// ��������IP 1024
	DECLARE_STRUCT_FIELD(TDX_ID_FUNC_REQ_RZ_TCIP,tdxRZTCIPFieldReq)
	
END_STRUCT_FIELD_DEF(tdxCommonStructFieldInfo)

#pragma pack()
#endif
