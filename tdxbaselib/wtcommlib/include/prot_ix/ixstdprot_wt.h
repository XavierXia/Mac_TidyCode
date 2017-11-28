//////////////////////////////////////////////////////////////////////////
// ��������:2006/07/20
// ����˵��:��׼�����ֵ��ֶκ��Լ����ܺŶ���
//			���Ľṹ
//				Part.I    ������������
//				Part.II   ��������
//				Part.III  ������ʾ����
//				Part.IV   �����ֶ�ID����
//				Part.V    ����ID����
//				Part.VI   �ʺ����Ͷ����Լ������ֵ���ö���ͱ�־����
//				Part.VII  ���������ֶ�
//				Part.VIII �ͻ�������
//				Part.IX   �ͻ���֧�ֵİ�ȫ�����Լ���֤��ʽ
//				Part.X    �������Ͷ���
//				Part.XI   DLLȯ��ID����
//				Part.XII  �г���Ϣ�ṹ
//				Part.XIII ���ܵ��ýӿ�800
#ifndef  __IX_STDPROT_WT__H__
#define  __IX_STDPROT_WT__H__
#ifdef WIN32
#pragma warning (push)			// ��ֲ��VS2005
#pragma warning (disable:4819)	// ����UNICODE���
#endif


//---------------------------------------------------------------------------
// Part.I ������������
//---------------------------------------------------------------------------

#define TDX_FID_SYS_NORMAL_FIRST		    (50)	// ϵͳ�����ֶο�ʼID
#define TDX_FID_SYS_NORMAL_LAST			(5050-1)	// ϵͳ�����ֶν���ID
#define TDX_FID_CLIENT_INNER_FIRST		  (5050)	// �ͻ����ڲ��ֶο�ʼID
#define TDX_FID_CLIENT_INNER_LAST		(5250-1)	// �ͻ����ڲ��ֶν���ID
#define TDX_FID_SYS_CACHE_FIRST			  (5250)	// ϵͳ�����ֶο�ʼID
#define TDX_FID_SYS_CACHE_LAST			(5300-1)	// ϵͳ�����ֶν���ID
#define TDX_FID_ITQ_NORMAL_FIRST		  (5300)	// ITQ(����ί�в�ѯ)�����ֶο�ʼID
#define TDX_FID_ITQ_NORMAL_LAST         (5450-1)    // ITQ(����ί�в�ѯ)�����ֶν���ID
#define TDX_FID_ITQ_CACHE_FIRST			  (5450)	// ITQ(����ί�в�ѯ)�����ֶο�ʼID
#define TDX_FID_ITQ_CACHE_LAST			(5500-1)    // ITQ(����ί�в�ѯ)�����ֶν���ID
#define TDX_FID_SDK_NORMAL_FIRST		  (5500)	// SDK�����ֶο�ʼID
#define TDX_FID_SDK_NORMAL_LAST			(5950-1)	// SDK�����ֶν���ID
#define TDX_FID_SDK_CACHE_FIRST			  (5950)	// SDK�����ֶο�ʼID
#define TDX_FID_SDK_CACHE_LAST			(6000-1)	// SDK�����ֶν���ID
#define TDX_FID_MAXID					  (6000)	// ����ֶ�ID

#define TDX_ID_FUNC_SYSFIRST			   (100)	// ϵͳ���ܿ�ʼID
#define TDX_ID_FUNC_ITQFRIST			  (5300)	// ITQ(����ί�в�ѯ)���ܿ�ʼID
#define TDX_ID_FUNC_SDKFRIST			  (5500)	// SDK���ܿ�ʼID
#define TDX_ID_FUNC_MAXID				  (6000)	// �����ID


//---------------------------------------------------------------------------
// Part.II ��������
//---------------------------------------------------------------------------
#define	TDX_DT_CHAR							1		
#define TDX_DT_SHORT						2
#define TDX_DT_LONG							3
#define TDX_DT_LONGLONG						4
#define TDX_DT_FLOAT						5
#define TDX_DT_DOUBLE						6
#define TDX_DT_LONGDOUBLE					7
#define TDX_DT_DATE							8
#define	TDX_DT_TIME							9
#define	TDX_DT_STRING						10
#define TDX_DT_MEMO							11
#define TDX_DT_BINARY						12
#define TDX_DT_RECORDSET					13



//---------------------------------------------------------------------------
// Part.III ������ʾ����
//---------------------------------------------------------------------------
#define TDX_DISP_TOP						0x00
#define TDX_DISP_LEFT						0x00
#define TDX_DISP_CENTER						0x01
#define TDX_DISP_RIGHT						0x02
#define TDX_DISP_VCENTER					0x04
#define TDX_DISP_BOTTOM						0x08
#define TDX_DISP_NONE						TDX_DISP_RIGHT


//---------------------------------------------------------------------------
// Part.IV �����ֶ�ID����
//---------------------------------------------------------------------------

// ������
#define TDX_ID_PARAM_YHSXX					85			// (����)ӡ��˰����
#define TDX_ID_PARAM_SXFXX					86			// (����)����������
#define TDX_ID_PARAM_GHFXX					87			// (����)����������
#define TDX_ID_PARAM_QTJEFXX				88			// (����)������������
#define TDX_ID_PARAM_QTSLFXX				89			// (����)��������������
#define TDX_ID_ZQJYBS						90			// ֤ȯ���ױ�ʶ '1'Ϊ��֧�� ����Ϊ֧��
#define TDX_ID_PARAM_CBJE					91			// (����)�ɱ����
#define TDX_ID_PARAM_CBSL					92			// (����)�ɱ�����
#define TDX_ID_PARAM_YHSL					93			// (����)ӡ��˰��
#define TDX_ID_PARAM_SXFL					94			// (����)��������
#define TDX_ID_PARAM_GHFL					95			// (����)��������
#define TDX_ID_PARAM_QTJEFL					96			// (����)����������
#define TDX_ID_PARAM_QTSLFL					97			// (����)������������
#define TDX_ID_FQSL							98			// ��������
#define TDX_ID_MC							99			// ����

#define TDX_ID_SCFLAG						100			// ����������
#define TDX_ID_SCNAME						101			// ����������
#define TDX_ID_YYB							102			// Ӫҵ������
#define TDX_ID_YYBMC						103			// Ӫҵ������
#define TDX_ID_TDX_OEM_FLAG					104			// #define TDX_ID_TDX_OEM_FLAG				7001
#define TDX_ID_JYYDM						105			// ����Ա����
#define TDX_ID_LXRXM						106			// ��ϵ������
#define TDX_ID_LXFS							107			// ��ϵ��ʽ
#define TDX_ID_NC							108			// �ǳ�
#define TDX_ID_LMQX							109			// ��ĿȨ��
#define TDX_ID_OP_WTFS						110			// ί�з�ʽ
#define TDX_ID_OP_GYDM						111			// ��Ա����
#define TDX_ID_OP_GYMM						112			// ��Ա����
#define TDX_ID_CZBZ							113			// ������־
#define TDX_ID_CZZT							114			// ����״̬
#define TDX_ID_HZHGZT						115			// �����ع�״̬
#define TDX_ID_ZDJYBZ						116			// ָ�����ף�0��δָ�� 1:ָ����
#define TDX_ID_SQKTWZ						117			// ���뿪ͨ����ַ
#define TDX_ID_HZHGDM						118			// �����ع�����
#define TDX_ID_HZPSDM						119			// �������۴���
#define TDX_ID_KHH							120			// �ͻ���
#define TDX_ID_ZJZH							121			// �ʽ��ʺ�
#define TDX_ID_KHMC							122			// �ͻ�����
#define TDX_ID_GDDM							123			// �ɶ�����
#define TDX_ID_GDMC							124			// �ɶ�����		
#define TDX_ID_ZHLB							125			// �ʺ����
#define TDX_ID_KSRQ							126			// ��ʼ����
#define TDX_ID_ZZRQ							127			// ��ֹ����
#define TDX_ID_USERPHONE					128			// �û���ϵ��ʽ
#define TDX_ID_USEREMAIL					129			// �û�EMAIL
#define TDX_ID_MMBZ							130			// ������־  0:���� 1:���� 2:���� 3:���� 4:����
#define	TDX_ID_MMBZSM						131			// ������־˵��
#define TDX_ID_BZ							132			// ���� 0:RMB 1:MY 2:GB
#define TDX_ID_JYDW							133			// ���׵�λ	 0:�� 1:�� 2:��
#define TDX_ID_JYMM							134			// ��������
#define TDX_ID_ZJMM							135			// �ʽ�����
#define TDX_ID_XJYMM						136			// �½�������
#define TDX_ID_XZJMM						137			// ���ʽ�����
#define TDX_ID_TXMM							138			// ͨѶ����
#define TDX_ID_SECURETYPE					139			// ��ȫ��ʽ
#define TDX_ID_ZQDM							140			// ֤ȯ����
#define TDX_ID_ZQMC							141			// ֤ȯ����
#define TDX_ID_WTRQ							142			// ί������	YYYYMMDD
#define TDX_ID_WTSJ							143			// ί��ʱ�� HHMMSS
#define TDX_ID_WTSL							144			// ί������
#define TDX_ID_WTJG							145			// ί�м۸�
#define TDX_ID_WTBH							146			// ί�б��
#define TDX_ID_ZTSM							147			// ״̬˵��
#define TDX_ID_WTJE							148			// ί�н��
#define TDX_ID_RETINFO						149			// ������Ϣ,(151 �ֽ�)
#define TDX_ID_CJRQ							150			// �ɽ�����
#define TDX_ID_CJSJ							151			// �ɽ�ʱ�� 
#define TDX_ID_CJSL							152			// �ɽ�����
#define TDX_ID_CJJG							153			// �ɽ��۸�
#define TDX_ID_CJJE							154			// �ɽ����
#define TDX_ID_CJBH							155			// �ɽ����
#define TDX_ID_HZPSZT						156			// ��������״̬
#define TDX_ID_HFBZ							157			// �Ϸ���־
#define TDX_ID_DFMM							158			// �Է�����(��֤��̨�����֤ȯ�ʽ��ʺŶ�Ӧ������,Ҳ������֤ת�ʵĵط����ʽ�����)
#define TDX_ID_HFBZSM						159			// �Ϸ���־˵��
#define TDX_ID_DJSL							160			// ��������
#define TDX_ID_DJZJ							161			// �����ʽ�
#define TDX_ID_CDSL							162			// ��������
#define TDX_ID_CDBZSM						163			// ������־˵��
#define TDX_ID_LESSPRESSURE					164			// ��֤ͨ�û������̨�ʽ��ѯ����ѹ��
#define TDX_ID_FIRSTZJCX					165			// ��֤ͨ�û���һ�ε�½��ѯ�ʽ�
#define TDX_ID_WTFS							166			// (ί�з�ʽ)�м�ί�з�ʽ
#define TDX_ID_CDBZ							167			// ������־ 1����  20061108 gxzq ���ճɽ���ѯ�������صĳ�����־���ͻ���,�ÿͻ��˿���ѡ���Ƿ���˵������ѵ��ȷ������ɽ���¼
#define	TDX_ID_KCDBZ						168			// �ɳ�����־
#define	TDX_ID_LSH							169			// ��ˮ��
#define TDX_ID_PHRQ							170			// �������
#define TDX_ID_QSPH							171			// ��ʼ���
#define	TDX_ID_PHSL							172			// �������
#define TDX_ID_XWDM							173			// ϯλ����
#define TDX_ID_ZQS							174			// ��ǩ��
#define TDX_ID_PHSLPHCX						175			// �������(��ݸ�����⴦��)
#define TDX_ID_ZQRQ							176			// ��ǩ����
#define TDX_ID_QZLX							177			// Ȩ֤����
#define TDX_ID_XQFS							178			// ��Ȩ��ʽ
#define TDX_ID_XQBL							179			// ��Ȩ����
#define TDX_ID_JSFS							180			// ���㷽ʽ
#define	TDX_ID_FXBZ							181			// ���ձ�־
#define	TDX_ID_FXSM							182			// ����˵��
#define	TDX_ID_JGRQ							183			// ��������
#define	TDX_ID_KHLBSM						184			// �ͻ����˵��
#define	TDX_ID_KHXZSM						185			// �ͻ�����˵��
#define	TDX_ID_KHZTSM						186			// �ͻ�״̬˵��
#define TDX_ID_ZXJYGS						187			// ��С���׹���
#define	TDX_ID_SHGD							188			// �Ϻ��ɶ�
#define	TDX_ID_SZGD							189			// ���ڹɶ�
#define TDX_ID_QZKTBZ						190			// Ȩ֤��ͨ��־
#define TDX_ID_SGRDM						191			// �չ��˴���
#define TDX_ID_YYSL							192			// ҪԼ����
#define TDX_ID_SBSL							193			// �걨����
//#define TDX_ID_WTFS						166			// (ί�з�ʽ)�м�ί�з�ʽ
#define TDX_ID_WTFSSM						194			// �м�ί�з�ʽ˵��
#define	TDX_ID_XTXMM						195			// ��ͨѶ����
#define TDX_ID_DZDLX						196			// ���ʵ�����
#define TDX_ID_XXSL							197			// ѡ������
#define TDX_ID_DQCB							198			// ��ǰ�ɱ�
#define TDX_ID_ZTSL							199			// ��;����

#define TDX_ID_ZQSL							200			// ֤ȯ����
#define TDX_ID_KMSL							201			// ��������
#define TDX_ID_CBJ							202			// �ɱ���
#define TDX_ID_ZXJ							203			// ���¼�
#define TDX_ID_FDYK							204			// ����ӯ��
#define TDX_ID_ZXSZ							205			// ������ֵ
#define TDX_ID_YJ							206			// Ӷ��
#define TDX_ID_KHF							207			// ������
#define TDX_ID_CJF							208			// �ɽ���
#define TDX_ID_JSF							209			// �����
#define TDX_ID_YHS							210			// ӡ��˰
#define TDX_ID_ZDKM							211			// ������
#define TDX_ID_SXF							212			// ������(�ڻ�������:С����ʱΪ���׽�����ֱȣ�������ΪԪ/��)
#define TDX_ID_GPLX							213			// ��Ʊ����
#define TDX_ID_GTZDKMBS						214			// ȡ��̨�������ʶ
#define TDX_ID_DRMRSL						215			// ������������
#define TDX_ID_GPLBP						216			// ��Ʊ�������
#define TDX_ID_GPLBV						217			// ��Ʊ��������
#define TDX_ID_GPLSP						218			// ��Ʊ��������
#define TDX_ID_GPLSV						219			// ��Ʊ��������
#define TDX_ID_KHQXDM						220			// �ͻ�Ȩ�޴���
#define TDX_ID_KHQXMC						221			// �ͻ�Ȩ������
#define TDX_ID_BBJ							222			// ������
#define TDX_ID_YWTSL						223			// ԭί������
#define TDX_ID_YWTJG						224			// ԭί�м۸�
#define TDX_ID_QTF							225			// ������
#define TDX_ID_ZXMRBDJW						226			// ��С����䶯��λ
#define TDX_ID_ZXMCBDJW						227			// ��С�����䶯��λ
#define TDX_ID_ZCZJZH						228			// ת���ʽ��ʺ�
#define TDX_ID_ZRZJZH						229			// ת���ʽ��ʺ�
#define TDX_ID_YKBL							230			// ӯ������
#define	TDX_ID_ZJZHEX						231			// �㷢�����ʽ��ʺ�
#define	TDX_ID_SXYK							232			// ʵ��ӯ��
#define	TDX_ID_TBYK							233			// ̯��ӯ��
#define	TDX_ID_LX							234			// ����
#define	TDX_ID_CJDF							235			// �ɽ�����
#define	TDX_ID_WTDF							236			// ί�е���
#define TDX_ID_JJRDM						237			// �����˴���
#define TDX_ID_ZHZT							238			// �ʻ�״̬
#define TDX_ID_KGDBZ						239			// �ɸĵ���־
#define TDX_ID_MAILADDRESS					240			// �ʼĵ�ַ
#define TDX_ID_YDXH							241			// Լ�����
#define TDX_ID_DFXWDM						242			// �Է�ϯλ����
#define TDX_ID_DFZJZH						243			// �Է��ʽ��ʺ�
#define TDX_ID_DFGDDM						244			// �Է��ɶ�����
#define TDX_ID_DFZHLB						245			// �Է��ʺ����
#define TDX_ID_ZZHBZ						246			// ���ʺű�־
#define TDX_ID_SBXH							247			// �걨���
#define TDX_ID_LMDM							248			// ��Ŀ����
#define TDX_ID_LMMC							249			// ��Ŀ����
#define TDX_ID_TSXX0						250			// ��ʾ��Ϣ0
#define TDX_ID_TSXX1						251			// ��ʾ��Ϣ1
#define TDX_ID_TSXX2						252			// ��ʾ��Ϣ2
#define TDX_ID_TSXX3						253			// ��ʾ��Ϣ3
#define TDX_ID_TSXX4						254			// ��ʾ��Ϣ4
#define TDX_ID_TSXX5						255			// ��ʾ��Ϣ5
#define TDX_ID_TSXX6						256			// ��ʾ��Ϣ6
#define TDX_ID_TSXX7						257			// ��ʾ��Ϣ7
#define TDX_ID_TSXX8						258			// ��ʾ��Ϣ8
#define TDX_ID_TSXX9						259			// ��ʾ��Ϣ9

// (����)"�ʽ���ˮ"Ӧ���ֶ�[260 ~ 272]
#define TDX_ID_ZJLS_FSRQ					260			// ��������
#define TDX_ID_ZJLS_FSSJ					261			// ����ʱ��
#define TDX_ID_ZJLS_YWDM					262			// ҵ�����
#define TDX_ID_ZJLS_YWMC					263			// ҵ������
#define TDX_ID_ZJLS_HBDM					264			// ���Ҵ���
#define TDX_ID_ZJLS_FSJE					265			// �������
#define TDX_ID_ZJLS_SYJE					266			// ʣ����
#define TDX_ID_ZJLS_ZQDM					267			// ֤ȯ����
#define TDX_ID_ZJLS_ZQMC					268			// ֤ȯ����
#define TDX_ID_ZJLS_FSJG					269			// �����۸�
#define TDX_ID_ZJLS_FSSL					270			// ��������
#define TDX_ID_ZJLS_SYSL					271			// ʣ������
#define TDX_ID_ZJLS_GDDM					272			// �ɶ�����

#define	TDX_ID_OTCJYBS						276			// ֧��OTC�����û���־
#define TDX_ID_DFBZ							277			// �Է�����
#define TDX_ID_DQHL							278			// ��ǰ����
#define	TDX_ID_JYGF							279			// ���׹��
#define	TDX_ID_ZTZJ							280			// ��;�ʽ�
#define	TDX_ID_XYJYBS						281			// ֧�����ý����û���־
#define	TDX_ID_SFCGBS						282			// ������ܱ�ʶ
#define TDX_ID_ZZFS							283			// ת�ʷ�ʽ
#define TDX_ID_ZZQD							284			// ת������
#define TDX_ID_ZZBH							285			// ת�ʱ��
#define TDX_ID_FPYH							286			// ��Ʊ����
#define TDX_ID_ZPBH							287			// ֧Ʊ���
#define TDX_ID_ZJCJSL						288			// ����ɽ�����
#define TDX_ID_ZJCDSL						289			// �����������
#define TDX_ID_KHBS							290			// �ͻ���ʶ
#define TDX_ID_ZDDM							291			// �ֶδ���
#define TDX_ID_ZDQZ							292			// �ֶ�ȡֵ
#define TDX_ID_YLXX							293			// Ԥ����Ϣ
#define TDX_ID_FJZH							294			// �����˺�
#define TDX_ID_XYJYTSXX						295			// ���ý�����ʾ��Ϣ
#define TDX_ID_JZC							296			// ���ʲ�
#define TDX_ID_SGKYS						297			// �깺������
#define TDX_ID_DFKHDM						298			// �Է��ͻ�����
#define TDX_ID_DFFZDM						299			// �Է���֧����

#define TDX_ID_ZJYE							300			// �ʽ����
#define TDX_ID_KYZJ							301			// �����ʽ�
#define TDX_ID_KQZJ							302			// ��ȡ�ʽ�
#define TDX_ID_OCCURJE						303			// �������
#define TDX_ID_POSTJE						304			// ʣ����	
#define TDX_ID_ZY							305			// ժҪ
#define TDX_ID_YWMC							306			// ҵ������
#define TDX_ID_YWDM							307			// ҵ�����
#define TDX_ID_MRDJZJ						308			// ���붳���ʽ�
#define TDX_ID_YZT_YHXZTS					309			// ѡ���������б�־
#define TDX_ID_GTZZC						310			// ��̨���ʲ�
#define TDX_ID_CJLX							311			// �ɽ�����
#define	TDX_ID_JYDJZJ						312			// ���׶����ʽ�
#define	TDX_ID_YCDJZJ						313			// �쳣�����ʽ�
#define	TDX_ID_ZTKYZJ						314			// ��;�����ʽ�
#define	TDX_ID_XJKQZJ						315			// �ֽ��ȡ�ʽ�
#define	TDX_ID_ZPKQZJ						316			// ֧Ʊ��ȡ�ʽ�
#define	TDX_ID_KZZJ							317			// ��ת�ʽ�
#define	TDX_ID_LXJE							318			// ��Ϣ���
#define	TDX_ID_LXS							319			// ��Ϣ˰
#define	TDX_ID_SYSL							320			// ʣ������
#define	TDX_ID_FJF							321			// ���ӷ�
#define	TDX_ID_SXJE							322			// ������
#define	TDX_ID_MMCB							323			// �����ɱ�
#define	TDX_ID_MRCB							324			// ����ɱ�
#define TDX_ID_ZGF							325			// ֤�ܷ�
#define TDX_ID_FCJL							326			// �ֲֻ���
#define TDX_ID_ZYK							327			// ��ӯ��
#define TDX_ID_TBCBJ						328			// ̯���ɱ���
#define TDX_ID_TBBBJ						329			// ̯��������
#define TDX_ID_TBFDYK						330			// ̯������ӯ��
#define TDX_ID_FADM							331			// ��������
#define TDX_ID_FAMC							332			// ��������
#define TDX_ID_FALX							333			// ��������
#define TDX_ID_TPDM							334			// ͶƱ����
#define TDX_ID_TPJG							335			// ͶƱ���
#define TDX_ID_CFDM							336			// �ɷִ���
#define TDX_ID_CFMC							337			// �ɷ�����
#define TDX_ID_CFQZ							338			// �ɷ�Ȩ��(%)
#define TDX_ID_MRXX							339			// Ĭ��ѡ��
#define TDX_ID_XXNR0						340			// ѡ������0
#define TDX_ID_XXNR1						341			// ѡ������1
#define TDX_ID_XXNR2						342			// ѡ������2
#define TDX_ID_XXNR3						343			// ѡ������3
#define TDX_ID_XXNR4						344			// ѡ������4
#define TDX_ID_XXNR5						345			// ѡ������5
#define TDX_ID_XXNR6						346			// ѡ������6
#define TDX_ID_XXNR7						347			// ѡ������7
#define TDX_ID_XXNR8						348			// ѡ������8
#define TDX_ID_XXNR9						349			// ѡ������9
#define TDX_ID_ZZC							350			// ���ʲ�
#define TDX_ID_SYL							351			// ������
#define TDX_ID_HYZS							352			// ��Ծָ��
#define TDX_ID_RMBZZC						353			// ��������ʲ�
#define TDX_ID_MYZZC						354			// ��Ԫ���ʲ�
#define TDX_ID_GYZZC						355			// ��Ԫ���ʲ�
#define TDX_ID_SYLTJRQ						356			// ������ͳ������
#define TDX_ID_SYLTJSJ						357			// ������ͳ��ʱ��
#define TDX_ID_ZZHZYE						358			// ���˻������
#define TDX_ID_HGJE							359			// �ع����
#define TDX_ID_MOCK_ZHTYPE					360			// �˺����� 0:��Ʊ 1:�ڻ� 2:���

#define TDX_ID_RQSL							370			// ��ȯ����(һ����ȯ��λ��10000��)
#define TDX_ID_RQJG							371			// ��ȯ�۸�
#define TDX_ID_RQZQ							372			// ��ȯ����
#define TDX_ID_RQCZLX						374			// ��ȯ��������(0:��ȯ 1:��ȯ 2:չ��)
#define TDX_ID_RQRQ							375			// ��ȯ����
#define TDX_ID_RQSJ							376			// ��ȯʱ��
#define TDX_ID_HTBH							377			// ��ͬ���
#define TDX_ID_JDJSJET						378			// �������ս��(T��)
#define TDX_ID_JDJSJET1						379			// �������ս��(T+1��)
#define TDX_ID_JDJSJET2						380			// �������ս��(T+2��)
#define TDX_ID_ZPDJSJE						381			// ֧Ʊ�����ս��
#define TDX_ID_XYSZ							382			// ������ֵ
#define TDX_ID_GJBZQGML						383			// �߼���֤ȯ������
#define TDX_ID_XYGJBZQGML					384			// ���ø߼���֤ȯ������
#define TDX_ID_DJBZQGML						385			// �ͼ���֤ȯ������
#define TDX_ID_XYDJBZQGML					386			// ���õͼ���֤ȯ������

// ����ʽ������
#define TDX_ID_YXSBCS						387			// ��Чʧ�ܴ���
#define TDX_ID_SFFSSM						388			// �շѷ�ʽ˵��
#define	TDX_ID_CPJZ							389			// ��Ʒ��ֵ
#define	TDX_ID_LCZH							390			// ����˻�
#define	TDX_ID_CPDM							391			// ��Ʒ����
#define	TDX_ID_CPMC							392			// ��Ʒ����
#define	TDX_ID_CPGSDM						393			// ��Ʒ��˾����
#define	TDX_ID_CPGSMC						394			// ��Ʒ��˾����
#define	TDX_ID_CPZT							395			// ��Ʒ״̬
#define	TDX_ID_QRJZ							396			// ǰ�վ�ֵ(ǰһ�������յľ�ֵ)
#define	TDX_ID_CPBZ							397			// ��Ʒ��־(0:��ͨ�����Ʒ,1:ȯ����Ʋ�Ʒ)
#define	TDX_ID_KTBZ							398			// ��ͨ��־
#define	TDX_ID_KFSJJ_LJJZ					399			// �ۼƾ�ֵ

#define TDX_ID_KFSJJ_MMBZ					400			// 0:�Ϲ� 1���깺 2����� 3:ԤԼ�깺 4:ԤԼ���
#define TDX_ID_KFSJJ_JJGSMC					401			// ����˾����
#define TDX_ID_KFSJJ_JJDM					402			// �������
#define	TDX_ID_KFSJJ_JJMC					403			// ��������
#define TDX_ID_KFSJJ_JJFE					404			// ����ݶ�
#define TDX_ID_KFSJJ_JYJE					405			// ���׽��
#define TDX_ID_KFSJJ_JJJZ					406			// ����ֵ
#define TDX_ID_KFSJJ_ZHDM					407			// ����ת������
#define TDX_ID_KFSJJ_DIVIDENMETHOD			408			// ����ֺ췽ʽ	    ��0��-����ת�ɡ���1��//�ֽ�ֺ졢��2��-�����ֽ���ֵ��Ͷ�ʡ���3��//-��ֵ�ֽ�������
#define TDX_ID_KFSJJ_FSRQ					409			// ��������
#define TDX_ID_KFSJJ_KYFE					410			// ���÷ݶ�
#define TDX_ID_KFSJJ_JJBS					411			// ����ʽ�����ʶ 0����֧�� 1��֧��
#define TDX_ID_KFSJJ_QSSL					412			// ��ʼ����
#define TDX_ID_KFSJJ_DQSL					413			// ��ǰ����
#define TDX_ID_KFSJJ_WTFE					414			// ί�зݶ�
#define TDX_ID_KFSJJ_CJFE					415			// �ɽ��ݶ�
#define TDX_ID_KFSJJ_CJJE					416			// �ɽ����
#define TDX_ID_KFSJJ_JJZH					417			// �����ʻ�
#define TDX_ID_KFSJJ_FXJG					418			// ���м۸�
#define TDX_ID_KFSJJ_GRZDRGJE				419			// ��������Ϲ����
#define TDX_ID_KFSJJ_FRZDRGJE				420			// ��������Ϲ����
#define TDX_ID_KFSJJ_ZDCYFE					421			// ��ͳ��зݶ�
#define TDX_ID_KFSJJ_ZGSHFE					422			// �����طݶ�
#define TDX_ID_KFSJJ_GRZGCYBL				423			// ������߳��б���
#define TDX_ID_KFSJJ_FRZGCYBL				424			// ������߳��б���
#define TDX_ID_KFSJJ_JJZT					425			// ����״̬
#define TDX_ID_KFSJJ_JJGSDM					426			// ����˾����
#define TDX_ID_KFSJJ_FXZS					427			// ��������
#define TDX_ID_KFSJJ_ZDSHFE					428			// �����طݶ�
#define TDX_ID_SFFS							429			// �շѷ�ʽ
#define TDX_ID_KFSJJ_JGZGBL					430			// ������߱���
#define TDX_ID_KFSJJ_GRZGBL					431			// ������߱���
#define TDX_ID_KFSJJ_GRZGRGZJ				432			// ��������Ϲ����
#define TDX_ID_KFSJJ_FRZGRGZJ				433			// ��������Ϲ����
#define TDX_ID_KFSJJ_GRSCSGZDZJ				434			// �����״��깺����ʽ�
#define TDX_ID_KFSJJ_FRSCSGZDZJ				435			// �����״��깺����ʽ�
#define TDX_ID_KFSJJ_GRZJSGZDZJ				436			// ����׷���깺����ʽ�
#define TDX_ID_KFSJJ_FRZJSGZDZJ				437			// ����׷���깺����ʽ�
#define TDX_ID_KFSJJ_GRJJZSSHFE				438			// ���˻���������طݶ�
#define TDX_ID_KFSJJ_FRJJZSSHFE				439			// ���˻���������طݶ�
#define TDX_ID_KFSJJ_GRJJZSZHFE				440			// ���˻�������ת���ݶ�
#define TDX_ID_KFSJJ_FRJJZSZHFE				441			// ���˻�������ת���ݶ�
#define TDX_ID_KFSJJ_TADM					442			// TA ����
#define TDX_ID_KFSJJ_GTGSBZ					443			// ����ʽ�����̨��˾��־
#define TDX_ID_KFSJJ_FHFSDM					444			// �ֺ췽ʽ����
#define	TDX_ID_KFSJJ_FHFSMC					445			// �ֺ췽ʽ����
#define TDX_ID_LSDJ							446			// ��ʱ����
#define TDX_ID_MCWTSL						447			// ��������
#define TDX_ID_KFSJJ_PZDM					448			// �깺Ʒ�ִ���
#define TDX_ID_KFSJJ_MYKKRQ					449			// ÿ�¿ۿ�����
#define TDX_ID_KHTYPE						450			// ������𣬸��ˣ�����
#define TDX_ID_KFSJJ_DQSGNS					451			// �깺����
#define TDX_ID_ZJLB							452			// ֤�����
#define TDX_ID_JYZH							453			// �����ʻ�
#define TDX_ID_ZJHM							454			// ֤������
#define TDX_ID_MOBILEPHONE					455			// �ƶ��绰
#define TDX_ID_HOMEPHONE					456			// סլ�绰
#define TDX_ID_FAX							457			// ����
#define TDX_ID_EDU							458			// �����̶�
#define TDX_ID_SALARY						459			// ������
#define TDX_ID_XLYZT_DLSGFLAG				460			// �����깺��־   0��δ��ͨ��1����ͨ 
#define TDX_ID_XLYZT_DLPGFLAG				461			// ������ɱ�־   0��δ��ͨ��1����ͨ 
#define TDX_ID_XLYZT_DLPSFLAG				462			// �������۱�־   0��δ��ͨ��1����ͨ 
#define TDX_ID_WORKPHONE					463			// ��λ�绰
#define TDX_ID_NAME							464			// ����
#define TDX_ID_VOCATION						465			// ְҵ
#define TDX_ID_FHBZ							466			// �ֺ��־
#define TDX_ID_DZDBZ						467			// ���ʵ���־
#define TDX_ID_SHFS							468			// ��ط�ʽ
#define TDX_ID_FHBL							469			// �ֺ����
#define TDX_ID_FHRQ							470			// �ֺ�����
#define TDX_ID_FHJE							471			// �ֺ���
#define TDX_ID_FHSL							472			// �ֺ�����
#define TDX_ID_MGFHJE						473			// ÿ�ɷֺ���
#define TDX_ID_ZDBZ							474			// ָ����־
#define TDX_ID_FHFS							475			// �ֺ췽ʽ
#define TDX_ID_KHRQ							476			// ��������
#define TDX_ID_KHQC							477			// �ͻ�ȫ��
#define TDX_ID_BPCALL						478			// Ѱ������
#define TDX_ID_ZBDLJYXX						479			// �ܱߵ�¼У����Ϣ
#define TDX_ID_KFSJJ_JGZDTZ					480			// �������Ͷ��
#define TDX_ID_KFSJJ_GRZDTZ					481			// �������Ͷ��
#define TDX_ID_KFSJJ_JGZDZJ					482			// �������׷��
#define TDX_ID_KFSJJ_GRZDZJ					483			// �������׷��
#define TDX_ID_SPEL_GX_HZXGSGZT				484			// ���Ų�ѯ�����¹��깺״̬
#define	TDX_ID_TJRDM						485			// �Ƽ��˴���
#define	TDX_ID_PROVINCE						486			// ʡ��
#define	TDX_ID_CITY							487			// ����
#define	TDX_ID_SECTION						488			// Ͻ��
#define TDX_ID_IDADDRESS					489			// ֤����ַ
#define TDX_ID_FRDBXM						490			// ���˴�������
#define TDX_ID_FRDBZJLX						491			// ���˴���֤������
#define TDX_ID_FRDBZJHM						492			// ���˴���֤������
#define TDX_ID_LXRZJLX						493			// ��ϵ��֤������
#define TDX_ID_LXRZJHM						494			// ��ϵ��֤������
#define TDX_ID_LXRDH						495			// ��ϵ�˵绰
#define TDX_ID_DZDJSFS						496			// ���ʵ����ͷ�ʽ
#define TDX_ID_JJDTBZ						497			// ����Ͷ��־
#define TDX_ID_XSRDM						498			// �����˴���
#define TDX_ID_XSRMC						499			// ����������

// ģ���ڻ���	
#define TDX_ID_QHZHBS						500			// �ڻ��˺ű�ʶ 1:�ڻ��ʺ� 0: ���ڻ��ʺ�
#define TDX_ID_QHZH							501			// �ڻ��˺�
#define TDX_ID_HYDM1						502			// ��Լ����1
#define TDX_ID_HYDM2						503			// ��Լ����2
#define TDX_ID_HYDM3						504			// ��Լ����3
#define TDX_ID_HYDM4						505			// ��Լ����4
#define TDX_ID_HYMC1						506			// ��Լ����1
#define TDX_ID_HYMC2						507			// ��Լ����2
#define TDX_ID_HYMC3						508			// ��Լ����3
#define TDX_ID_HYMC4						509			// ��Լ����4
#define TDX_ID_HYDM							510			// ��Լ����
#define TDX_ID_HYMC							511			// ��Լ����
#define TDX_ID_PZ							512			// Ʒ��
#define TDX_ID_KPBZ							513			// ��ƽ��־ 0:���� 1:ƽ��
#define TDX_ID_TBBZ							514			// Ͷ����־ 0:Ͷ�� 1:���ڱ�ֵ
#define TDX_ID_JKCFLAG						515			// ��ֱ�־ 0:��ʷ�� 1:�񿪲�
#define TDX_ID_CJSX							516			// �ɽ�����
#define TDX_ID_CJSXSM						517			// �ɽ�����˵��
#define TDX_ID_ZHLX							518			// �������
#define TDX_ID_ZHLXSM						519			// �������˵��
#define TDX_ID_KCJG							520			// ���ּ�
#define TDX_ID_CCSL							521			// �ֲ���
#define TDX_ID_KCRQ							522			// ��������
#define TDX_ID_CJJJ							523			// �ɽ�����
#define TDX_ID_CBJJ							524			// �ɱ�����
#define TDX_ID_BZJJE						525			// ��֤����
#define TDX_ID_SXFJE						526			// �����ѽ��
#define TDX_ID_MRJJ							527			// �������
#define TDX_ID_CCJJ							528			// �ֲ־���
#define TDX_ID_ZHTS							529			// �������
#define TDX_ID_DJBZJ						530			// ���ᱣ֤��
#define TDX_ID_QCZJ							531			// �ڳ��ʽ�
#define TDX_ID_KHQYZJ						532			// �ͻ�Ȩ���ʽ�
#define	TDX_ID_KKCSL						533			// �ɿ�������
#define	TDX_ID_KPCSL						534			// ��ƽ������
#define	TDX_ID_KPJSL						535			// ��ƽ������
#define TDX_ID_ZHHYDM						536			// ��Ϻ�Լ����
#define TDX_ID_ZHHYMC						537			// ��Ϻ�Լ����
#define TDX_ID_CFJG							538			// �����۸�
#define TDX_ID_MZL							539			// ������
#define TDX_ID_JGY							540			// �����·�
#define TDX_ID_BZJ							541			// ��֤��
#define TDX_ID_QHJYDW						542			// ���׵�λ(��/��)
#define TDX_ID_QHBJDW						543			// ���۵�λ(Ԫ/��)
#define TDX_ID_ZXBDJW						544			// ��С�䶯��λ(Ԫ/��)
#define TDX_ID_JGBDFD						545			// �۸񲨶�����(С����ʱ��λΪ�ٷֱ�,������ʱ��λΪԪ)
#define TDX_ID_BZJBL						546			// ��֤�����
	
#define TDX_ID_QHHQ_KCL						550			// ������(����)
#define TDX_ID_QHHQ_CCL						551			// �ֲ���
#define TDX_ID_QHHQ_QJS						552			// ǰ����
#define TDX_ID_QHHQ_ZS						553			// ����
	
//�۹�
#define TDX_ID_GGZHBS						580			// �۹��˺ű�ʶ 1:�۹��ʺ� 0: �Ǹ۹��ʺ�

// ����������	
#define	TDX_ID_ETFBS						600			// ETF��ʶ 0��ʾ��֧�֣� 1��ʾ֧��
#define TDX_ID_ETFDM						601			// ETF����
#define	TDX_ID_ETFMC						602			// ETF����
#define	TDX_ID_ETFMMBS						603			// 0:�깺 1:��� 2:��Ʊ�Ϲ� 3���ֽ��Ϲ�
#define TDX_ID_ETFRGSL						604			// �Ϲ�����
#define TDX_ID_ETFRGJE						605			// �Ϲ����
#define TDX_ID_PCH							606			// ���κ�
#define TDX_ID_ETFXJTDMZ					607			// �ֽ������־ /'0'������'1'����'2'���� 
#define TDX_ID_ETFYJBL						608			// ��۱���
#define TDX_ID_ETFXJTDJE					609			// �ֽ�������
#define TDX_ID_QSRQ							610			// ��������
#define TDX_ID_CLDM							611			// ���Դ���
#define TDX_ID_CLMC							612			// ��������
#define TDX_ID_ZSDM							613			// ָ������
#define TDX_ID_ZSMC							614			// ָ������
#define TDX_ID_CDDDSJ						615			// �����ȴ�ʱ��
#define TDX_ID_WTDDSJ						616			// ί�еȴ�ʱ��
#define TDX_ID_WTCS							617			// ί�д���
#define TDX_ID_JGBZ							618			// �۸��־
#define TDX_ID_ZDCD							619			// �Զ�����
#define TDX_ID_CFSL							620			// �ɷ�����
#define TDX_ID_KCSL							621			// �������
#define TDX_ID_BLSL							622			// ��������
#define TDX_ID_XJBZ							623			// �ֽ��־
#define TDX_ID_JSBZ							624			// ������־
#define TDX_ID_CJZT							625			// �ɽ�״̬
#define TDX_ID_XJTDSM						626			// �ֽ������־˵��
#define TDX_ID_QKSL							627			// ȱ������
#define TDX_ID_XYZJ							628			// ��Ҫ�ʽ�
#define TDX_ID_ZRKC							629			// ���տ��
#define TDX_ID_JRMRJE						630			// ����������
#define TDX_ID_JRMCSL						631			// ������������
#define TDX_ID_JRMCJE						632			// �����������
#define TDX_ID_MBFE							633			// Ŀ��ݶ�
#define TDX_ID_KSSJ							634			// ��ʼʱ��
#define TDX_ID_ZZSJ							635			// ��ֹʱ��
#define TDX_ID_CSWTSL						636			// ��ʼί������
#define TDX_ID_ZWTCS						637			// ��ί�д���
#define TDX_ID_ZHDM							638			// ��ϴ���
#define TDX_ID_ZHMC							639			// �������
#define TDX_ID_KZYHZHBM						640			// ��չ�����˻�����
#define TDX_ID_KZYHZHBM1					641			// ��չ�����˻�����1
#define TDX_ID_KZYHZHBM2					642			// ��չ�����˻�����2
#define TDX_ID_KZYHZHBM3					643			// ��չ�����˻�����3
#define TDX_ID_KZYHZHBM4					644			// ��չ�����˻�����4
#define TDX_ID_KZYHZHMC						645			// ��չ�����˻�����
#define TDX_ID_KZYHZHMC1					646			// ��չ�����˻�����1
#define TDX_ID_KZYHZHMC2					647			// ��չ�����˻�����2
#define TDX_ID_KZYHZHMC3					648			// ��չ�����˻�����3
#define TDX_ID_KZYHZHMC4					649			// ��չ�����˻�����4
#define TDX_ID_DJGSDM						650			// �Ǽǹ�˾����
#define TDX_ID_DJGSJC						651			// �Ǽǹ�˾���
#define TDX_ID_DJGSQC						652			// �Ǽǹ�˾ȫ��
#define TDX_ID_QZFS							653			// Ȩ�ط�ʽ
#define TDX_ID_DWSZ							654			// ��λ��ֵ
#define TDX_ID_XHZH							655			// �ֻ��˺�
#define TDX_ID_XHZHLX						656			// �ֻ��˺�����
#define TDX_ID_PCHLX						657			// ���κ�����
#define TDX_ID_DKBZ							658			// ��ձ�־
#define TDX_ID_TZSL							659			// Ͷ������
#define TDX_ID_BJFS							660			// ���۷�ʽ
#define TDX_ID_DFBJFS						661			// �Է����۷�ʽ
#define TDX_ID_SYKCBJ						662			// ʹ�ÿ����
#define TDX_ID_SYFZXHBJ						663			// ʹ�ø����ֻ����
#define TDX_ID_MCYGBJ						664			// ������ɱ��
#define TDX_ID_ZDWTBJ						665			// �Զ�ί�б��
#define TDX_ID_ZDWTCS						666			// �Զ�ί�д���
#define TDX_ID_PCHRQ						667			// ���κ�����
#define TDX_ID_JC							668			// ����
#define TDX_ID_MRJEJSJZ						669			// ����������׼
#define TDX_ID_MRJE							670			// ������
#define TDX_ID_FZXHDM						671			// �����ֻ�����
#define TDX_ID_FZXHMC						672			// �����ֻ�����
#define TDX_ID_PDDM1						673			// ��Դ���1
#define TDX_ID_PDMC1						674			// �������1
#define TDX_ID_PDDM2						675			// ��Դ���2
#define TDX_ID_PDMC2						676			// �������2
#define TDX_ID_PDBL							677			// ��Ա���
#define TDX_ID_JCRQ							678			// ��������
#define TDX_ID_JCJG1						679			// ���ּ۸�1
#define TDX_ID_JCSL1						680			// ��������1
#define TDX_ID_JCBH1						681			// ���ֱ��1
#define TDX_ID_JCJG2						682			// ���ּ۸�2
#define TDX_ID_JCSL2						683			// ��������2
#define TDX_ID_JCBH2						684			// ���ֱ��2

// �ڻ���
#define	TDX_ID_FXD							700			// ���ն�
#define	TDX_ID_KHAQLB						701			// �ͻ���ȫ���
#define	TDX_ID_KHAQLBSM						702			// �ͻ���ȫ���˵��
#define	TDX_ID_ZJBZJ						703			// ׷�ӱ�֤��
#define	TDX_ID_ZRJSJ						704			// ���ս����
#define	TDX_ID_SBMRJ						705			// �걨�����
#define	TDX_ID_SBMCJ						706			// �걨������
#define	TDX_ID_SBMRL						707			// �걨������
#define	TDX_ID_SBMCL						708			// �걨������
#define	TDX_ID_MCDJZJ						709			// ���������ʽ�
#define	TDX_ID_MRBZJ						710			// ���뱣֤��
#define	TDX_ID_MCBZJ						711			// ������֤��
#define	TDX_ID_YLJE							712			// ӯ�����
#define	TDX_ID_KSJE							713			// ������
#define	TDX_ID_DTQY							714			// ��̬Ȩ��
#define	TDX_ID_DTFX							715			// ��̬����
#define	TDX_ID_PCYK							716			// ƽ��ӯ��
#define	TDX_ID_DRCRJ						717			// ���ճ����
#define	TDX_ID_XTZXH						718			// ϵͳ���ĺ�
#define	TDX_ID_KPBZSM						719			// ��ƽ��־˵��
#define	TDX_ID_TBBZSM						720			// Ͷ����־˵��
#define	TDX_ID_MRCC							721			// ����ֲ�
#define	TDX_ID_MRFDYK						722			// ���븡��ӯ��
#define	TDX_ID_MCCC							723			// �����ֲ�
#define	TDX_ID_MCJJ							724			// ��������
#define	TDX_ID_MCFDYK						725			// ��������ӯ��
#define	TDX_ID_JF							726			// �跽
#define	TDX_ID_DF							727			// ����
#define	TDX_ID_QHTJ							728			// �ڻ�Ͷ��
#define	TDX_ID_QHBZ							729			// �ڻ���ֵ
#define	TDX_ID_ZDSS							730			// �������
#define	TDX_ID_ZDCC							731			// ���ֲ�
#define	TDX_ID_WCJSL						732			// δ�ɽ�����
#define	TDX_ID_SBSJ							733			// �걨ʱ��
#define	TDX_ID_CDSJ							734			// ����ʱ��
#define	TDX_ID_FSZ							735			// ������
#define	TDX_ID_XXLX							736			// ��Ϣ����
#define	TDX_ID_XXLXSM						737			// ��Ϣ����˵��
#define TDX_ID_ZYZJ							738			// ��Ѻ�ʽ�
#define TDX_ID_ZJFXL						739			// �ʽ������
#define TDX_ID_JYSFXL						740			// ������������
#define TDX_ID_QCQY							741			// �ڳ�Ȩ��
#define TDX_ID_DPPCYK						742			// ����ƽ��ӯ��
#define TDX_ID_FDPCYK						743			// ����ƽ��ӯ��
#define TDX_ID_DPCCYK						744			// ���ֲ̳�ӯ��
#define TDX_ID_FDCCYK						745			// �����ֲ�ӯ��
#define TDX_ID_DPZYK						746			// ������ӯ��
#define TDX_ID_FDZYK						747			// ������ӯ��
#define TDX_ID_QHJYTSXX						748			// �ڻ�������ʾ��Ϣ
#define TDX_ID_KMRKCSL						749			// �����뿪������
#define TDX_ID_KMCKCSL						750			// ��������������
#define TDX_ID_KMRPCSL						751			// ������ƽ������
#define TDX_ID_KMCPCSL						752			// ������ƽ������
#define TDX_ID_KMRPJSL						753			// ������ƽ������
#define TDX_ID_KMCPJSL						754			// ������ƽ������
#define TDX_ID_JKKY							755			// �񿪿���
#define TDX_ID_LSKKY						756			// ��ʷ������
#define TDX_ID_DSYK							757			// ����ӯ��
#define TDX_ID_YKDS							758			// ӯ������
#define TDX_ID_HYBH							759			// ��Լ���


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��ȫ������(800~899)
#define TDX_ID_CA_KHH						800			// �ͻ���							
#define TDX_ID_CA_KHMC						801			// �ͻ�����
#define TDX_ID_CA_SQBZ						802			// �����־
#define TDX_ID_CA_TXMM						803			// ��֤����
#define TDX_ID_CA_XTXMM						804			// ����֤����
#define TDX_ID_CA_ZSXH						805			// ֤�����
#define TDX_ID_CA_AQJB						806			// ��ȫ����
#define TDX_ID_CA_YHFJ						807			// �û��ּ�
#define TDX_ID_CA_YHJBMS					808			// �û���������
#define TDX_ID_CA_YHQX						809			// �û�Ȩ��
#define TDX_ID_CA_KJYBZ						810			// �ɽ��ױ�־
#define TDX_ID_CA_ZSSHBZ					811			// ֤����˱�־
#define TDX_ID_CA_ZSXZBZ					812			// ֤�����ر�־
#define TDX_ID_CA_ZSQSID					813			// ֤��ȯ��ID
#define TDX_ID_CA_ZSBFJG					814			// ֤��䷢����
#define TDX_ID_CA_ZSBFYH					815			// ֤��䷢�û�
#define TDX_ID_CA_ZSQSRQ					816			// ֤����������
#define TDX_ID_CA_ZSJZRQ					817			// ֤���ֹ����
#define TDX_ID_CA_ZSWS						818			// ֤��λ��
#define TDX_ID_CA_ZSGY						819			// ֤�鹫Կ��
#define TDX_ID_CA_CZJG						820			// ��������
#define TDX_ID_CA_CZY						821			// ����Ա
#define TDX_ID_CA_CZMM						822			// ��������
#define TDX_ID_CA_CZSX						823			// ��������
#define TDX_ID_CA_CZBZ						824			// ������־
#define TDX_ID_CA_RESV						825			// �����ֶ�
#define IDX_ID_CA_ZSKGXBZ					826			// ֤��ɸ��±�־
#define TDX_ID_CA_ZSJYGXBZ					827			// ֤�齨����±�־
#define TDX_ID_CA_ZSSYYXTS					828			// ֤��ʣ����Ч����
#define TDX_ID_CA_ZHLB						829			// CA�˺����(0:�ͻ��� 1:TQ�� 2:TQ�ʼ�)
#define TDX_ID_CA_TQID						830			// �û�TQ��
#define TDX_ID_CA_TQMAIL					831			// �û�TQ�ʼ�
#define TDX_ID_CA_XGTXMMBZ					832			// �޸�ͨѶ�����ʶ(0:�������� 1:��������޸�)
#define TDX_ID_CA_L2USER					833			// LEVEL2���˺�
#define TDX_ID_CA_L2PASS					834			// LEVEL2������
#define TDX_ID_CA_YHJBZT					835			// �û�����״̬(-1:δ���� 0:���������� 1:�Ѿ����)
#define TDX_ID_CA_YHJBBZ					836			// �û�����ע
#define TDX_ID_CA_ISVIPHOST					837			// VIP��վ��ʶ
// �ҵ���������ֶ�
#define TDX_ID_CA_KHJL						838			// �ͻ�������
#define TDX_ID_CA_TOPICID					839			// �ҵ�����:����ID
#define TDX_ID_CA_TOPICTITLE				840			// �ҵ�����:�������
#define TDX_ID_CA_CONTENT					841			// �ҵ�����:�������ݻ��߻ظ�����
#define TDX_ID_CA_QUERYDATE					842			// �ҵ�����:��ѯ�����ں����������
#define TDX_ID_CA_REQDATE					843			// �ҵ�����:��������
#define TDX_ID_CA_REQTIME					844			// �ҵ�����:��������
#define TDX_ID_CA_VALDATE					845			// �ҵ�����:��������Ч����
#define TDX_ID_CA_CLOSEFLAG					846			// �ҵ�����:����رձ�־
#define TDX_ID_CA_BRANCHMSGID				847			// �ҵ�����:Ӫҵ����ϢID
#define TDX_ID_CA_SATISFAC					848			// �ҵ�����:�����
#define TDX_ID_CA_REMINDFLAG				849			// �ҵ�����:�Ƿ���ʾ�ر�����
#define TDX_ID_CA_NEWANSFLAG				850			// �ҵ�����:�Ƿ������»ظ�
#define TDX_ID_CA_ANSWERID					851			// �ҵ�����:�ظ�ID
#define TDX_ID_CA_WHOANS					852			// �ҵ�����:������
#define TDX_ID_CA_QUERYALL					853			// �ҵ�����:Ϊ0��ѯ������״̬������,-1Ϊ��ѯ����δ�ر�����
#define TDX_ID_CA_NEWMSGNUM					854			// �ҵ�����:����Ϣ����
#define TDX_ID_CA_NOREADMSGNUM				855			// �ҵ�����:δ����Ϣ����
#define TDX_ID_CA_RESETFLAG					856			// ���ñ�־

// �����
#define TDX_ID_CA_SJH						860			// �ͻ��ֻ���
#define TDX_ID_CA_ZJHM						861			// �ͻ�֤������
#define TDX_ID_CA_KHXB						862			// �ͻ��Ա�
#define TDX_ID_CA_EMAIL						863			// �ͻ������ʼ�
#define TDX_ID_CA_JHM						865			// ������
#define TDX_ID_CA_DRZB						866			// ����ָ��
#define TDX_ID_CA_LEVELNAME					867			// �ȼ�����
#define	TDX_ID_CA_ZBMAX						868			// ָ������
#define	TDX_ID_CA_ZBMIN						869			// ָ������
#define	TDX_ID_CA_PROTOC					870			// ָ������Э��
#define	TDX_ID_CA_COMMISION					871			// Ӷ��
#define TDX_ID_CA_BIRTHTITIP				872			// �Ƿ���Ҫ��������
#define TDX_ID_CA_NOTICETITLE				873			// �������
#define TDX_ID_CA_NOTICECONTENT				875			// ������������
#define	TDX_ID_CA_TSUPDATE					878			// ��ʾ����
#define TDX_ID_CA_NOWLEVELNO				879			// ��ǰ�ȼ����
#define TDX_ID_CA_NOWLEVELNAME				880			// ��ǰ�ȼ�����
#define TDX_ID_CA_CANLEVELNO				881			// ������ȼ����
#define TDX_ID_CA_CANLEVELNAME				882			// ������ȼ�����
#define TDX_ID_CA_MENU						883			// �ɼ���Ŀ

#define TDX_ID_CA_LASTIP					890			// �ϴε�½IP
#define TDX_ID_CA_NEWIP						891			// ���ε�½IP
#define TDX_ID_CA_LASPROV					892			// �ϴε�½ʡ��
#define TDX_ID_CA_NEWPROV					893			// ���ε�½ʡ��
#define TDX_ID_CA_LASSITE					894			// �ϴε�½����
#define TDX_ID_CA_NEWSITE					895			// ���ε�½���� 
#define TDX_ID_CA_QSRQ						896			// ��ʼ��ѯʱ��
#define TDX_ID_CA_ZZRQ						897			// ��ֹ��ѯʱ��
#define TDX_ID_CA_DLSJ						898			// ��½ʱ��
#define TDX_ID_CA_DLRQ						899			// ��½����



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// �������ֶ�	
#define TDX_ID_HQ_MRSL1						900			// ��һ��
#define TDX_ID_HQ_MRSL2						901			// �����
#define TDX_ID_HQ_MRSL3						902			// ������
#define TDX_ID_HQ_MRSL4						903			// ������
#define TDX_ID_HQ_MRSL5						904			// ������
#define TDX_ID_HQ_MRSL6						905			// ������
#define TDX_ID_HQ_MRSL7						906			// ������
#define TDX_ID_HQ_MRSL8						907			// �����
#define TDX_ID_HQ_MRSL9						908			// �����
#define TDX_ID_HQ_MRSL0						909			// ��ʮ��

#define TDX_ID_HQ_MRLG1						910			// ��һ��
#define TDX_ID_HQ_MRLG2						911			// �����
#define TDX_ID_HQ_MRLG3						912			// ������
#define TDX_ID_HQ_MRLG4						913			// ���ļ�
#define TDX_ID_HQ_MRLG5						914			// �����
#define TDX_ID_HQ_MRLG6						915			// ������
#define TDX_ID_HQ_MRLG7						916			// ���߼�
#define TDX_ID_HQ_MRLG8						917			// ��˼�
#define TDX_ID_HQ_MRLG9						918			// ��ż�
#define TDX_ID_HQ_MRLG0						919			// ��ʮ��

#define TDX_ID_HQ_MCSL1						920			// ��һ��
#define TDX_ID_HQ_MCSL2						921			// ������
#define TDX_ID_HQ_MCSL3						922			// ������
#define TDX_ID_HQ_MCSL4						923			// ������
#define TDX_ID_HQ_MCSL5						924			// ������
#define TDX_ID_HQ_MCSL6						925			// ������
#define TDX_ID_HQ_MCSL7						926			// ������
#define TDX_ID_HQ_MCSL8						927			// ������
#define TDX_ID_HQ_MCSL9						928			// ������
#define TDX_ID_HQ_MCSL0						929			// ��ʮ��

#define TDX_ID_HQ_MCJS1						930			// ��һ��
#define TDX_ID_HQ_MCJS2						931			// ������
#define TDX_ID_HQ_MCJS3						932			// ������
#define TDX_ID_HQ_MCJS4						933			// ���ļ�
#define TDX_ID_HQ_MCJS5						934			// �����
#define TDX_ID_HQ_MCJS6						935			// ������
#define TDX_ID_HQ_MCJS7						936			// ���߼�
#define TDX_ID_HQ_MCJS8						937			// ���˼�
#define TDX_ID_HQ_MCJS9						938			// ���ż�
#define TDX_ID_HQ_MCJS0						939			// ��ʮ��

#define TDX_ID_HQ_ZTJG						940			// ��ͣ�۸�
#define TDX_ID_HQ_DTJG						941			// ��ͣ�۸�
#define TDX_ID_HQ_ZGJG						942			// ��߼�
#define TDX_ID_HQ_ZDJG						943			// ��ͼ�
#define TDX_ID_HQ_GZQJ						944			// ��ծȫ��
#define TDX_ID_HQ_OPEN						945			// �񿪼�
#define TDX_ID_HQ_CLOSE						946			// ���ռ�
#define TDX_ID_HQ_TPBZ						947			// ͣ�Ʊ�־	1:ͣ��
#define TDX_ID_GZLX							948			// ��ծ��Ϣ
#define	TDX_ID_NOW							949			// ��ǰ��
#define TDX_ID_USERADDRESS					950			// �û�ͨѶ��ַ
#define TDX_ID_IDENTITYCARD					951			// ���֤
#define TDX_ID_SEX							952			// �Ա�
#define TDX_ID_POSTALCODE					953			// ��������
#define TDX_ID_HQ_ZDF						954			// �ǵ���
#define TDX_ID_HQ_ZDZ						955			// �ǵ�ֵ
#define TDX_ID_GETGTHQ						956			// ȡ��̨����  ��Ҫ����ͳ���ǵ�ͣ���ǵ�����
#define TDX_ID_MBYLX						957			// ÿ��Ԫ��Ϣ
#define TDX_ID_GZBS							958			// ��ծ��ʶ(0--��ծ�ֻ�,1--ծȯ,2--��ת��ծȯ,3--��ծ�ع�,255(-1)--��ծȯ)
#define TDX_ID_ZQXXYXBZ						959			// ֤ȯ��Ϣ��Ч��־
#define TDX_ID_ZQLB							960			// ֤ȯ���(0--ͨ��״̬,1--��������,2--�����ɷ�����,3--�������۷���,4--�������۷���,5--��ծ���Ʒ���)
#define TDX_ID_ZGSL							961			// �������
#define TDX_ID_ZDSL							962			// �������


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��־�鿴���ֶ�(1000~1099)
#define TDX_ID_RZ_STARTTIME					1000		// ��ѯ��ʼʱ��
#define TDX_ID_RZ_ENDTIME					1001		// ��ѯ����ʱ��
#define TDX_ID_RZ_TCTIME					1002		// ��ѯ��������ʱ��
#define TDX_ID_RZ_APITIME					1003		// ��ѯAPIʱ��
#define TDX_ID_RZ_QUEUETIME					1004		// ��ѯ�Ŷ�ʱ��
#define TDX_ID_RZ_FUNCID					1005		// �������ܺ�
#define TDX_ID_RZ_FLAGRESULT				1006		// ��������־
#define TDX_ID_RZ_LOGID						1007		// ��־���
#define TDX_ID_RZ_TCIP						1008		// ��������IP
#define TDX_ID_RZ_LOGTIME					1009		// ��־ʱ��
#define TDX_ID_RZ_LEVER						1010		// �û�����
#define TDX_ID_RZ_PAGEINDEX					1011		// ҳ�����
#define TDX_ID_RZ_FUNCNUM					1012		// ������Ŀ
#define TDX_ID_RZ_FUNCBL					1013		// ��������
#define	TDX_ID_RZ_FUNCOKNUM					1014		// ���ù��ܳɹ���Ŀ
#define	TDX_ID_RZ_FUNCFAILNUM				1015		// ���ù���ʧ����Ŀ
#define TDX_ID_RZ_ITEMNUM					1016		// ��¼����
#define TDX_ID_RZ_AVGTCTIME					1017		// ��ѯ��������ƽ��ʱ��
#define TDX_ID_RZ_AVGAPITIME				1018		// ��ѯAPIƽ��ʱ��
#define TDX_ID_RZ_AVGQUEUETIME				1019		// ��ѯ�Ŷ�ƽ��ʱ��
#define TDX_ID_RZ_CXFLAG					1020		// ��ѯ��־
#define TDX_ID_RZ_DAY						1021		// ����ʱ��


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	
// ��֤ҵ����	
#define TDX_ID_YZZZ_YHDM					1101		// ���д���
#define TDX_ID_YZZZ_YHMC					1102		// ��������
#define TDX_ID_YZZZ_YHZH					1103		// �����ʺ�
#define TDX_ID_YZZZ_YHMM					1104		// ��������
#define TDX_ID_YZZZ_XYHMM					1105		// ����������
#define TDX_ID_YZZZ_YHLSH					1106		// ������ˮ��
#define TDX_ID_YZZZ_ZZJE					1107		// ת�ʽ��
#define TDX_ID_YZZZ_ZZFX					1108		// ת�ʷ���
#define TDX_ID_YZZZ_YHYE					1109		// �������
#define TDX_ID_YZZZ_ZZRQ					1110		// ת������
#define TDX_ID_YZZZ_ZZSJ					1111		// ת��ʱ��
#define TDX_ID_YZZZ_ZZFXSM					1112		// ת��˵��
#define TDX_ID_YZTYH						1113		// ��֤ͨ�û� 0:�� 1:��
#define	TDX_ID_YZZZ_NEEDZJMM				1114		// ��Ҫ�ʽ�����
#define TDX_ID_YZZZ_NEEDYHMM				1115		// ��Ҫ��������
#define	TDX_ID_YZZZ_SUPPORTYHYE				1116		// ֧�ֲ��������
#define TDX_ID_BANKCODE						1117		// ���д���
#define TDX_ID_BANKYYB						1118		// ����Ӫҵ�� (����֤ȯ)
#define TDX_ID_BANKGDTYPE					1119		// ���йɶ������½���г� (����֤ȯ)
//0����Ҫ���� 1 ��Ҫȡ������(�ʽ�����) 2 ��Ҫ�������� 3 ��Ҫȡ��/��������
#define	TDX_ID_YZZZ_ZRMM					1120		// ��֤ת���������
#define TDX_ID_YZZZ_ZCMM					1121		// ��֤ת���������
#define	TDX_ID_YZZZ_SHOWYHYE				1122		// ��ʾ���������
#define	TDX_ID_YZZZ_YHYEMM					1123		// ����������������  20060328 ��Ϲ���linux �ͻ���
#define TDX_ID_ZRYHDM						1124		// ת�����д���
#define TDX_ID_ZCYHDM						1125		// ת�����д���
#define TDX_ID_ZRYHZH						1126		// ת�������ʺ�
#define TDX_ID_ZCYHZH						1127		// ת�������ʺ�
#define TDX_ID_ZJYHDM						1128		// �м����д���
#define TDX_ID_ZJYHMC						1129		// �м���������
#define TDX_ID_ZJYHZH						1130		// �м������ʺ�
#define TDX_ID_ZJYHZHMC						1131		// �м������ʺ�����
#define TDX_ID_YHKH							1132		// ���п���
#define TDX_ID_YHQC							1133		// ����ȫ��
#define TDX_ID_ZKBZ							1134		// ������־
#define TDX_ID_JQBZ							1135		// ��Ȩ��־
#define TDX_ID_YHCPDM						1136		// ���в�Ʒ����
#define TDX_ID_YHCPMC						1137		// ���в�Ʒ����
#define TDX_ID_XTCPDM						1138		// ���в�Ʒ����
#define TDX_ID_XTCPMC						1139		// ���в�Ʒ����
#define TDX_ID_YHZHBM						1140		// �����˻�����
#define TDX_ID_YHZHBM1						1141		// �����˻�����1
#define TDX_ID_YHZHBM2						1142		// �����˻�����2
#define TDX_ID_YHZHBM3						1143		// �����˻�����3
#define TDX_ID_YHZHBM4						1144		// �����˻�����4
#define TDX_ID_YHZHMC						1145		// �����˻�����
#define TDX_ID_YHZHMC1						1146		// �����˻�����1
#define TDX_ID_YHZHMC2						1147		// �����˻�����2
#define TDX_ID_YHZHMC3						1148		// �����˻�����3
#define TDX_ID_YHZHMC4						1149		// �����˻�����4
//������ȯ
#define	TDX_ID_RZLX							1150		// �˻�������Ϣ
#define	TDX_ID_XYZ							1151		// �˻�����ֵ
#define	TDX_ID_ZHWBXY						1152		// �˻��ⲿ����
#define	TDX_ID_XYSX							1153		// �˻���������
#define	TDX_ID_RZSX							1154		// ������������
#define	TDX_ID_RQSX							1155		// ��ȯ��������
#define	TDX_ID_XYCPBS						1156		// ���ò�Ʒ��ʾ(mmbz)
#define	TDX_ID_DYZC							1157		// ��Ѻ�ʲ�
#define	TDX_ID_PCBZ							1158		// ƽ�ֱ�־
#define	TDX_ID_RZSXF						1159		// ���ʹ����
#define	TDX_ID_RQMCZJ						1160		// ��ȯ�����ʽ�
#define	TDX_ID_RZFX							1161		// ���ʷ���
#define	TDX_ID_GHSL							1162		// �黹����
#define	TDX_ID_RZFZ							1163		// ���ʸ�ծ
#define	TDX_ID_RQSZ							1164		// ��ȯ��ֵ
#define	TDX_ID_QSJE							1165		// ������
#define	TDX_ID_KYXYED						1166		// �������ö��
#define	TDX_ID_YYXYED						1167		// �������ö��
#define	TDX_ID_RZJE							1168		// ���ʽ��
#define	TDX_ID_RQJE							1169		// ��ȯ���
#define	TDX_ID_RQLX							1170		// ��ȯ��Ϣ
#define	TDX_ID_RQSXF						1171		// ��ȯ�����
#define	TDX_ID_DBBL							1172		// ��������
#define	TDX_ID_KYBZJ						1173		// ���ñ�֤��
#define	TDX_ID_YYBZJ						1174		// ���ñ�֤��
#define	TDX_ID_RQSYSL						1175		// ��ȯʹ������
#define	TDX_ID_PCRQ							1176		// ƽ������
#define	TDX_ID_XYHYLX						1177		// ��Լ����
#define	TDX_ID_CHSL							1178		// ��������
#define	TDX_ID_CHJE							1179		// �������
#define	TDX_ID_SSCHSL						1180		// ʵʱ��������
#define	TDX_ID_SSCHJE						1181		// ʵʱ�������
#define	TDX_ID_CHLX							1182		// ������Ϣ
#define	TDX_ID_HYSXF						1183		// ��Լ����
#define	TDX_ID_HYLL							1184		// ��Լ����
#define	TDX_ID_HYLXJE						1185		// ��Լ��Ϣ
#define	TDX_ID_RZBL							1186		// ���ʱ���
#define TDX_ID_GPZSL						1187		// ��Ʊ������
#define TDX_ID_XYJB							1188		// ���ü���
#define TDX_ID_FXZT							1189		// ����״̬
#define TDX_ID_RZBZJBL						1190		// ���ʱ�֤�����
#define TDX_ID_RQBZJBL						1191		// ��ȯ��֤�����
#define TDX_ID_RZRQLXFY						1192		// ������ȯ��Ϣ����
#define TDX_ID_ZFZ							1193		// �ܸ�ծ
#define TDX_ID_FZBL							1194		// ��ծ����
#define TDX_ID_HYQX							1195		// ��Լ����
#define	TDX_ID_SYRZED						1196		// ʣ�����ʶ��
#define	TDX_ID_SYRQED						1197		// ʣ����ȯ���
#define TDX_ID_TQZZLL						1198		// ��ǰ��ֹ����
#define TDX_ID_DQR							1199		// ������

// ϵͳ��	
#define TDX_ID_XT_ERRCODE					1200		// ����� 0:�ɹ� ����Ϊ����ʧ��,���������Ϣ��ERRMSG�з���
#define TDX_ID_XT_ERRMSG					1201		// ������Ϣ
#define	TDX_ID_XT_FUNCNO					1202		// ���ܱ��
#define	TDX_ID_XT_CLIVER					1203		// �ͻ��˰汾
#define	TDX_ID_XT_MACADDR					1204		// MAC��ַ
#define TDX_ID_XT_IPADDR					1205		// IP��ַ
#define	TDX_ID_XT_CLITYPE					1206		// �ͻ����	�μ�:CLITYPE_XXX�궨��
#define TDX_ID_XT_STARTPOS					1207		// ��ʼ���
#define TDX_ID_XT_AUTH_NEWINFO				1208		// ��ȫ������֤����Ϣ(����/��Կ��)
#define TDX_ID_XT_OEM_FLAG					1209		// OEM��־
#define TDX_ID_XT_AUTH_MODE					1210		// ��ȫ������֤��ʽ(ȡֵ��"��ȫ������")
#define TDX_ID_XT_AUTH_INFO					1211		// ��ȫ������֤��Ϣ(����/��Կ��)
#define TDX_ID_XT_BRANCHID					1212		// ����Ӫҵ��ID
#define TDX_ID_XT_RESERVED					1213		// ϵͳ����
#define	TDX_ID_XT_RECONNECTFLAG				1214		// ����������־(0-�ͻ���¼,1-��������)
#define	TDX_ID_XT_COUNTERSTATUS				1215		// (ȯ��)��̨״̬
#define	TDX_ID_XT_VIPFLAG					1216		// VIP��־
#define	TDX_ID_XT_REMARK					1217		// ��ע
#define	TDX_ID_XT_CLIENTRIGHTS				1218		// �ͻ�Ȩ��
#define TDX_ID_XT_LAST_LOGIN_DATE			1219		// �ϴε�¼����
#define TDX_ID_XT_LAST_LOGIN_TIME			1220		// �ϴε�¼ʱ��
#define TDX_ID_XT_AHTHCHAR1					1221		// ��֤�ַ�1
#define TDX_ID_XT_AHTHCHAR2					1222		// ��֤�ַ�2
#define	TDX_ID_XT_CHECKRISKFLAG				1223		// �����ձ�־
#define	TDX_ID_XT_FJYZHBZ					1224		// �ǽ����ʺű�־
#define	TDX_ID_XT_JZJJKHBZ					1225		// ��ֹ���𿪻���־
#define TDX_ID_XT_INCREMENTMODE				1226		// ����ģʽ����
#define TDX_ID_XT_PARAM						1227		// ����
#define TDX_ID_XT_MODE						1228		// ģʽ
#define TDX_ID_XT_DESCRIPTION				1229		// ����
#define TDX_ID_XT_QUERYMODE					1230		// ��ѯģʽ
#define TDX_ID_XT_DISPLAYCOLOR				1231		// ��ʾ��ɫ(RGBֵ,���ͻ�����ʾ�ο�)
#define TDX_ID_XT_PASSWORDFLAG				1232		// �����־
#define TDX_ID_XT_HANDLE					1233		// ���
#define TDX_ID_XT_GTLB						1234		// ��̨���(0:Ĭ�� 1:���ý��� 2:��Ʊ 3:���� 4:��Ʒ�ڻ� 5:�����ڻ� 6:�۹�)
#define TDX_ID_XT_MACHINEINFO				1235		// ������Ϣ(��ʽ[����ֺŷָ�,����ŷָ�]: ����IP;������;�û���;�ڴ�;CPU��Ϣ;CPUID;ϵͳ�汾;IP�б�;MAC��ַ�б�;Ӳ�����к��б�;BIOS�汾; )
														// ���Ż���������=[��־*4][CPUID*8][DISKSN*20][MAC*12][BIOSDATE*10]
#define TDX_ID_XT_LOGINTYPE					1236		// [ֻ�����ڵ�¼�ֵ���]��¼����(��¼����)
#define TDX_ID_XT_LOGINID					1237		// [ֻ�����ڵ�¼�ֵ���]��¼�ʺ�(��¼����)
#define TDX_ID_XT_LOGINPASSWD				1238		// [ֻ�����ڵ�¼�ֵ���]��¼����(��¼����)
#define TDX_ID_XT_COMMPASSWD				1239		// [ֻ�����ڵ�¼�ֵ���]ͨѶ����(��¼����)
#define TDX_ID_XT_FUNCID					1240		// [ֻ�����ڵ�¼�ֵ���]���ܺ�
#define TDX_ID_XT_FUNCDICTTAG				1241		// [ֻ�����ڵ�¼�ֵ���]�����ֵ��ʶ
#define TDX_ID_XT_FUNCCONTENT				1242		// [ֻ�����ڵ�¼�ֵ���]��������
#define TDX_ID_XT_LIMITMODE					1243		// ����ģʽ
#define TDX_ID_XT_MACHINECODE				1244		// ����������(��Բ�ͬȯ�̸�ʽ������ַ���)
#define TDX_ID_XT_MOBILECHECKCODE			1245		// �ֻ�У����
#define TDX_ID_XT_BRANCHMODIFY				1246		// Ӫҵ���ı�
#define TDX_ID_XT_NEEDEDAUTHMODE			1247		// ������֤��ʽ(ʹ��"��ȫ������",��λ��ʾ)
#define TDX_ID_XT_SESSION					1248		// �Ự��Ϣ
#define TDX_ID_XT_URL						1249		// URL
#define TDX_ID_XT_INFOCOLUMN				1250		// ��Ѷ��Ŀ
#define TDX_ID_XT_REALCLIENTVERSION			1251		// �ڲ��ͻ��˰汾
#define TDX_ID_XT_CN						1252		// CN
#define TDX_ID_XT_SN						1253		// SN
#define TDX_ID_XT_DN						1254		// DN
#define TDX_ID_XT_NEEDCONFIRMFLAGS			1255		// ��ȷ�ϵı�ʶ��(���ŷָ�,��������170���ܵ�CZBZ��Ӧ)
														// (1--ȷ���˵�,����--δ��)
#define TDX_ID_XT_URL2						1256		// URL2
#define TDX_ID_XT_REDIRECTFLAG				1257		// �ض����־
#define TDX_ID_XT_REDIRECTINFO				1258		// �ض�����Ϣ
#define TDX_ID_XT_LAST_LOGIN_LOCATION		1259		// �ϴε�¼λ��
#define TDX_ID_XT_SLOTID					1260		// ֤������ID
#define TDX_ID_XT_CID						1261		// ֤�鳧��ID
#define TDX_ID_XT_INPUTPARAM				1262		// �������
#define TDX_ID_XT_OUTPUTPARAM				1263		// �������
#define TDX_ID_XT_TOKEN						1264		// ����
#define TDX_ID_XT_PREPASSWORD0				1265		// [ֻ�����ڵ�¼�ֵ���]Ԥ��������0
#define TDX_ID_XT_PREPASSWORD1				1266		// [ֻ�����ڵ�¼�ֵ���]Ԥ��������1
#define TDX_ID_XT_PREPASSWORD2				1267		// [ֻ�����ڵ�¼�ֵ���]Ԥ��������2
#define TDX_ID_XT_PREPASSWORD3				1268		// [ֻ�����ڵ�¼�ֵ���]Ԥ��������3
#define TDX_ID_XT_PREPASSWORD4				1269		// [ֻ�����ڵ�¼�ֵ���]Ԥ��������4
#define TDX_ID_XT_PREPARAM0					1270		// [ֻ�����ڵ�¼�ֵ���]Ԥ�������0
#define TDX_ID_XT_PREPARAM1					1271		// [ֻ�����ڵ�¼�ֵ���]Ԥ�������1
#define TDX_ID_XT_PREPARAM2					1272		// [ֻ�����ڵ�¼�ֵ���]Ԥ�������2
#define TDX_ID_XT_PREPARAM3					1273		// [ֻ�����ڵ�¼�ֵ���]Ԥ�������3
#define TDX_ID_XT_PREPARAM4					1274		// [ֻ�����ڵ�¼�ֵ���]Ԥ�������4
#define TDX_ID_XT_PREPARAM5					1275		// [ֻ�����ڵ�¼�ֵ���]Ԥ�������5
#define TDX_ID_XT_PREPARAM6					1276		// [ֻ�����ڵ�¼�ֵ���]Ԥ�������6
#define TDX_ID_XT_PREPARAM7					1277		// [ֻ�����ڵ�¼�ֵ���]Ԥ�������7
#define TDX_ID_XT_PREPARAM8					1278		// [ֻ�����ڵ�¼�ֵ���]Ԥ�������8
#define TDX_ID_XT_PREPARAM9					1279		// [ֻ�����ڵ�¼�ֵ���]Ԥ�������9
#define TDX_ID_XT_LOGINEMAIL				1280		// ��¼Email
#define TDX_ID_XT_TRADEEMAIL				1281		// ����Email
#define TDX_ID_XT_MULTINITICE				1282		// [ֻ�����ڵ�¼�ֵ���]����ʾ��Ϣ
#define TDX_ID_XT_MESSAGEID					1283		// ��Ϣ���
#define TDX_ID_XT_MESSAGETITLE				1284		// ��Ϣ����
#define TDX_ID_XT_MESSAGECONTENT			1285		// ��Ϣ����
#define TDX_ID_XT_POSITIONSTRING			1286		// ��λ�ִ�
#define TDX_ID_XT_BEGINLINE					1287		// ��ʼ�к�
#define TDX_ID_XT_REQUESTLINE				1288		// ��������
#define TDX_ID_XT_TOTALLINE					1289		// �ܹ�����
#define TDX_ID_XT_RISKPARAM					1290		// ���ղ���
#define TDX_ID_XT_LOGINRETURNPARAM			1291		// ��¼���ز���
#define TDX_ID_XT_MOBILEMACHINEINFO			1292		// �ֻ�������Ϣ
#define TDX_ID_XT_PACKAGELIST				1293		// �ײ��б�
#define TDX_ID_XT_PRODUCTLIST				1294		// ��Ʒ�б�
#define TDX_ID_XT_FEATURELIST				1295		// �����б�
#define TDX_ID_XT_CONFIGLIST				1296		// �����б�
#define TDX_ID_XT_LOGINENTERPARAM			1297		// ��¼�������
#define TDX_ID_XT_ALGORIGHTLIST				1298		// �㷨Ȩ���б�
#define TDX_ID_XT_FUNCTIONVERSION			1299		// ���ܰ汾
#define TDX_ID_XT_CLIENTINVERSION			1300		// �ͻ����ڲ��汾
#define TDX_ID_XT_VERSIONSTRING				1301		// �汾�ַ���

// ����	
#define TDX_ID_XLYZT_XGKT_FLAG				3101		// �޸Ŀ�ͨ��� 

//	1 ������ɿ�ͨ
//	2 �������ȡ��
//	3 �����깺��ͨ
//	4 �����깺ȡ��
//	5 �������ۿ�ͨ
//	6 ��������ȡ��
	
#define TDX_ID_XLYZT_START_DATE				3104		// ��Чʱ��
#define TDX_ID_XLYZT_END_DATE				3105		// ʧЧʱ��
#define TDX_ID_XLYZT_DEBT_KIND				3106		// �ع�Ʒ�� '3''7''14''28''63''91''182''273
#define TDX_ID_XLYZT_JE_MIN					3107		// �ʽ����ޣ���λ��Ԫ
#define TDX_ID_XLYZT_JE_MAX					3108		// �ʽ����ޣ���λ��Ԫ

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CA��չ�ֶ�

#define TDX_ID_CA_JQTZM						4201		// ����������
#define TDX_ID_CA_PWDQACZBZ					4202		// ���뱣�����������־ ( 0-����,1-�޸� )
#define TDX_ID_CA_CONNID					4203		// �û�����ID
#define TDX_ID_CA_MACHINENAME				4204		// �����ǳ�
#define TDX_ID_CA_PROVISIONAL				4205		// ��ʱ��־
#define TDX_ID_CA_TZZB						4206		// ��ս����
#define TDX_ID_CA_CSCS						4207		// ���Դ���
#define TDX_ID_CA_ISDLWZTS					4208		// �Ƿ�֧�ֵ�½λ����ʾ
#define TDX_ID_CA_ISMMBHWT					4209		// �Ƿ�֧�����뱣������
#define TDX_ID_CA_ISJQTZMBD					4210		// �Ƿ�֧�ֻ����������
#define TDX_ID_CA_MAC						4211		// �û�MAC��ַ
#define TDX_ID_CA_YLWT						4212		// Ԥ������
#define TDX_ID_CA_ISYLWT					4213		// �Ƿ�֧��Ԥ������

#define TDX_ID_CA_CERTREQ					4214		// ֤����������(P10)
#define TDX_ID_CA_USERCERDN					4215		// ֤��DN��Ϣ
#define TDX_ID_CA_CERTTOKEN					4216		// ֤��ҵ���
#define TDX_ID_CA_CERTINFO					4217		// ֤������
#define TDX_ID_CA_SLOTSN					4218		// װ��֤������SN
#define TDX_ID_CA_CERTSN					4219		// ֤����
#define	TDX_ID_CA_CID						4220		// ������ȫ����ID(�䷢/��֤)
#define	TDX_ID_CA_SEEDINFO					4221		// ������Ϣ
#define	TDX_ID_CA_OTPSN						4222		// OTPSN���

#define TDX_ID_CA_BINDNUM					4223		// �Ѱ󶨻������������̨��
#define TDX_ID_CA_IDCARD					4224		// �û����֤����
#define TDX_ID_CA_YZM						4225		// ��֤��

#define	TDX_ID_CA_VER						4226		// �汾��Ϣ
#define	TDX_ID_CA_PWDPROQUESTION			4227		// ���뱣������(�����ʽ: ���:��������)
#define	TDX_ID_CA_MACHINEBINDTIME			4228		// ������ʱ��

// �޸����뱣������궨��,ԭ�����ֵ�ı�,Ԥ����ռ�(4230-4250)
#define TDX_ID_CA_MMBHWT					4230		// ���뱣������
#define TDX_ID_CA_MMBHWT1	(TDX_ID_CA_MMBHWT+1)		// ���뱣������1
#define TDX_ID_CA_MMBHWT2	(TDX_ID_CA_MMBHWT+2)		// ���뱣������2
#define TDX_ID_CA_MMBHWT3	(TDX_ID_CA_MMBHWT+3)		// ���뱣������3
#define TDX_ID_CA_MMBHWT4	(TDX_ID_CA_MMBHWT+4)		// ���뱣������4
#define TDX_ID_CA_MMBHWT_LAST				4250		// Ԥ���ռ�

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define TDX_ID_UM_BROKERCODE				4251		// �����˴���
#define TDX_ID_UM_BROKERBRANCH				4252		// ������Ӫҵ��
#define TDX_ID_UM_BROKERNAME				4253		// ����������
#define TDX_ID_UM_BROKERSTATUS				4254		// ������״̬
#define TDX_ID_UM_BROKERLEVEL				4255		// �����˼���
#define TDX_ID_UM_UPBROKER					4256		// �ϼ�������
#define TDX_ID_UM_BROKERNATIONALITY			4257		// �����˹���
#define TDX_ID_UM_BROKERPHONECODE			4258		// �����˵绰
#define TDX_ID_UM_BROKERMOPHONE				4259		// �������ƶ��绰
#define TDX_ID_UM_BROKEREMAIL				4260		// �����˵����ʼ�
#define TDX_ID_UM_BROKERMSN					4261		// ������MSN
#define TDX_ID_UM_BROKERQQ					4262		// ������QQ
#define TDX_ID_UM_BROKERSEX					4263		// �������Ա�
#define TDX_ID_UM_BROKERAGE					4264		// ����������
#define TDX_ID_UM_BROKERDEGREE				4265		// ������ѧ��
#define TDX_ID_UM_BROKERFAVOR				4266		// �����˲���ϰ��
#define TDX_ID_UM_BROKERNATIVEPLACE			4267		// �����˸�������
#define TDX_ID_UM_BROKERQUAL				4268		// �����˴�ҵ�ʸ�
#define TDX_ID_UM_BROKERSATISLEV			4269		// ������Ͷ�ʹ�������ȼ���
#define TDX_ID_UM_BROKERPHOTOS				4270		// ��������Ƭ
#define TDX_ID_UM_BROKERNOTES				4271		// �����˱�ע
#define TDX_ID_UM_BRANCHNAME				4272		// Ӫҵ������
#define TDX_ID_UM_COMHOTLINE				4273		// ��˾�ͻ�����
#define TDX_ID_UM_BRANCHTRADEASK			4274		// Ӫҵ��������ѯ�绰
#define TDX_ID_UM_BRANCHINVESTASK			4275		// Ӫҵ��Ͷ����ѯ�绰
#define TDX_ID_UM_PASSEXAM					4276		// �Ƿ�ͨ������
#define TDX_ID_UM_PRACTISETIME				4277		// ��ҵʱ��

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define	TDX_ID_CA_USERNICK					4230		// �û��ǳ�
#define	TDX_ID_CA_CARDTYPE					4231		// ֤������
#define	TDX_ID_CA_BIRTH						4232		// ��������
#define	TDX_ID_CA_POSTCODE					4233		// ��������
#define	TDX_ID_CA_ADDRESS					4234		// ��ϵ��ַ
#define	TDX_ID_CA_OFFPHONE					4235		// �칫�绰
#define	TDX_ID_CA_HOMEPHONE					4236		// ��ͥ�绰
#define	TDX_ID_CA_FAXPHONE					4237		// ����绰
#define	TDX_ID_CA_EDUCATION					4238		// ѧ��
#define	TDX_ID_CA_TOKEN						4239		// ����
#define TDX_ID_CA_YYBID						4240		// Ӫҵ��ID
#define TDX_ID_CA_USERSTOCK					4241		// �û���ѡ��
#define TDX_ID_CA_GD_DATE					4242		// ����
#define TDX_ID_CA_GD_TIME					4243		// ʱ��
#define TDX_ID_CA_GD_HARDINFO				4244		// �������������Ϣ
#define TDX_ID_CA_GD_MOREINFO				4245		// ������ǳ�
#define TDX_ID_CA_GD_TERMINALTYPE			4246		// �ն�����
#define TDX_ID_CA_GD_XH						4247		// ���
#define TDX_ID_CA_TRADETIME					4248		// ����ʱ��
#define TDX_ID_CA_TRADETYPE					4249		// ��������
#define TDX_ID_CA_SCORE						4250		// ����ֵ

#define TDX_ID_CA_SID						4501		// ���
#define TDX_ID_CA_BINDTINE					4502		// ��ʱ��
#define TDX_ID_CA_UMAC						4503		// MAC��ַ
#define TDX_ID_CA_REMARK					4504		// �������ע
#define TDX_ID_CA_HARDINFO					4505		// ����Ӳ����Ϣ


	
// ����ֶ�ID	
#define TDX_ID_FIELD_MAXID					6000		// ����ֶ�ID



//---------------------------------------------------------------------------
// Part.V ����ID����
//---------------------------------------------------------------------------
	
	
// ϵͳ����
#define TDX_ID_FUNC_REQ_GETDICT				1		// ȡ�����ֵ�
#define TDX_ID_FUNC_ANS_GETDICT				2

// ί�й��ܲ���
#define TDX_ID_FUNC_REQ_ZHYCL				94		// �˺�Ԥ���� 94
#define TDX_ID_FUNC_ANS_ZHYCL				95

#define TDX_ID_FUNC_REQ_DLYCL				96		// ��¼Ԥ���� 96
#define TDX_ID_FUNC_ANS_DLYCL				97

#define TDX_ID_FUNC_REQ_JCKHJY				98		// ���ɿͻ�У�� 98
#define TDX_ID_FUNC_ANS_JCKHJY				99

#define TDX_ID_FUNC_REQ_KHJY				100		// �ͻ�У�� 100
#define TDX_ID_FUNC_ANS_KHJY				101

#define TDX_ID_FUNC_REQ_SIMPDICTMAX			100		// ���ֵ��ڵ�����ܺ�
	
#define TDX_ID_FUNC_REQ_CXHQ				102		// ��ѯ���� 102
#define TDX_ID_FUNC_ANS_CXHQ				103		
	
#define TDX_ID_FUNC_REQ_ZJYE				104		// �ʽ���� 104
#define TDX_ID_FUNC_ANS_ZJYE				105
	
#define TDX_ID_FUNC_REQ_XGMM				106		// �޸����� 106
#define TDX_ID_FUNC_ANS_XGMM				107
	
#define TDX_ID_FUNC_REQ_XGZJMM				108		// �޸��ʽ����� 108
#define TDX_ID_FUNC_ANS_XGZJMM				109
	
#define TDX_ID_FUNC_REQ_JSKMS				110		// �������(��)�� 110
#define TDX_ID_FUNC_ANS_JSKMS				111
	
#define	TDX_ID_FUNC_REQ_CACHE				112		// ȡ������Ϣ 112
#define	TDX_ID_FUNC_ANS_CACHE				113

#define	TDX_ID_FUNC_REQ_XGGLZJZH			114		// �޸Ĺ����ʽ��ʺ� 114
#define	TDX_ID_FUNC_ANS_XGGLZJZH			115

#define TDX_ID_FUNC_REQ_KHZX				116		// �ͻ�ע�� 116
#define TDX_ID_FUNC_ANS_KHZX				117

#define	TDX_ID_FUNC_REQ_DYQXDZD				118		// ����ȡ�����ʵ�(�ʼ�) 118
#define	TDX_ID_FUNC_ANS_DYQXDZD				119
	
#define TDX_ID_FUNC_REQ_WTDJZJ				120		// ί�ж����ʽ� 120
#define TDX_ID_FUNC_ANS_WTDJZJ				121

#define TDX_ID_FUNC_REQ_PRINTDZD			122		// ��ӡ���ʵ� 122
#define TDX_ID_FUNC_ANS_PRINTDZD			123
	
#define TDX_ID_FUNC_REQ_PRINTHZDZD			124		// ��ӡ���ܶ��ʵ� 124
#define TDX_ID_FUNC_ANS_PRINTHZDZD			125
	
#define TDX_ID_FUNC_REQ_PRINTJGD			126		// ��ӡ��� 126
#define TDX_ID_FUNC_ANS_PRINTJGD			127

#define	TDX_ID_FUNC_REQ_XGTXMM				128		// �޸�ͨѶ���� 128
#define	TDX_ID_FUNC_ANS_XGTXMM				129

#define TDX_ID_FUNC_REQ_ZHJD				130		// �ʺŽⶳ 130
#define TDX_ID_FUNC_ANS_ZHJD				131

#define TDX_ID_FUNC_REQ_ZJGJ				132		// �ʽ�鼯 132
#define TDX_ID_FUNC_ANS_ZJGJ				133

#define TDX_ID_FUNC_REQ_ZJZHJZZ				134		// �ʽ��ʺż�ת�� 134
#define TDX_ID_FUNC_ANS_ZJZHJZZ				135

#define	TDX_ID_FUNC_REQ_TJWJJG				136		// �ύ�ʾ��� 136
#define	TDX_ID_FUNC_ANS_TJWJJG				137

#define	TDX_ID_FUNC_REQ_HQWJNR				138		// ��ȡ�ʾ����� 138
#define	TDX_ID_FUNC_ANS_HQWJNR				139

#define	TDX_ID_FUNC_REQ_HQZHZTBZ			140		// ��ȡ�ʺ�״̬��־ 140
#define	TDX_ID_FUNC_ANS_HQZHZTBZ			141

#define	TDX_ID_FUNC_REQ_CLCXMM				142		// �����ѯ���� 142
#define	TDX_ID_FUNC_ANS_CLCXMM				143

#define	TDX_ID_FUNC_REQ_TSZC				144		// ����ע�� 144
#define	TDX_ID_FUNC_ANS_TSZC				145

#define	TDX_ID_FUNC_REQ_TSZX				146		// ����ע�� 146
#define	TDX_ID_FUNC_ANS_TSZX				147

#define TDX_ID_FUNC_REQ_ZZHCX				148		// ���ʺŲ�ѯ 148
#define TDX_ID_FUNC_ANS_ZZHCX				149

#define TDX_ID_FUNC_REQ_CLRZXX				150		// ������֤��Ϣ 150
#define TDX_ID_FUNC_ANS_CLRZXX				151

#define TDX_ID_FUNC_REQ_RZXXCX				152		// ��֤��Ϣ��ѯ 152
#define TDX_ID_FUNC_ANS_RZXXCX				153

#define TDX_ID_FUNC_REQ_KHJBXXCX			154		// �ͻ�������Ϣ��ѯ 154
#define TDX_ID_FUNC_ANS_KHJBXXCX			155

#define TDX_ID_FUNC_REQ_DZHTQY				156		// ���Ӻ�ͬǩԼ 156
#define TDX_ID_FUNC_ANS_DZHTQY				157

#define TDX_ID_FUNC_REQ_DZHTQYCX			158		// ���Ӻ�ͬǩԼ��ѯ 158
#define TDX_ID_FUNC_ANS_DZHTQYCX			159

#define TDX_ID_FUNC_REQ_DZHTLBCX			160		// ���Ӻ�ͬ�б��ѯ 160
#define TDX_ID_FUNC_ANS_DZHTLBCX			161

#define TDX_ID_FUNC_REQ_DZHTXXCX			162		// ���Ӻ�ͬ��Ϣ��ѯ 162
#define TDX_ID_FUNC_ANS_DZHTXXCX			163

#define TDX_ID_FUNC_REQ_RZLSCX				164		// ��֤��ˮ��ѯ 164
#define TDX_ID_FUNC_ANS_RZLSCX				165

#define TDX_ID_FUNC_REQ_KHYLXXCX			166		// �ͻ�Ԥ����Ϣ��ѯ 166
#define TDX_ID_FUNC_ANS_KHYLXXCX			167

#define TDX_ID_FUNC_REQ_KHYLXXXG			168		// �ͻ�Ԥ����Ϣ�޸� 168
#define TDX_ID_FUNC_ANS_KHYLXXXG			169

#define TDX_ID_FUNC_REQ_KHCZQR				170		// �ͻ�����ȷ�� 170
#define TDX_ID_FUNC_ANS_KHCZQR				171

#define TDX_ID_FUNC_REQ_FYZDCX				172		// �����ֵ��ѯ 172
#define TDX_ID_FUNC_ANS_FYZDCX				173

#define TDX_ID_FUNC_REQ_UPDATESESSION		174		// ���»Ự��Ϣ 174
#define TDX_ID_FUNC_ANS_UPDATESESSION		175

#define TDX_ID_FUNC_REQ_WJLSCX				176		// �ʾ���ˮ��ѯ 176
#define TDX_ID_FUNC_ANS_WJLSCX				177

#define TDX_ID_FUNC_REQ_SCINFO				178		// ��ȡ�г���Ϣ 178
#define TDX_ID_FUNC_ANS_SCINFO				179

// ί��������
#define TDX_ID_FUNC_REQ_WTCD				200		// ί�г��� 200
#define TDX_ID_FUNC_ANS_WTCD				201	
	
#define TDX_ID_FUNC_REQ_PTGPWT				202		// ��ͨ��Ʊί�� 202
#define TDX_ID_FUNC_ANS_PTGPWT				203

#define TDX_ID_FUNC_REQ_ZQZGHS				204		// ծȯת�ɻ��� 204
#define TDX_ID_FUNC_ANS_ZQZGHS				205

#define TDX_ID_FUNC_REQ_XGDD				206		// �޸Ķ��� 206
#define TDX_ID_FUNC_ANS_XGDD				207

#define TDX_ID_FUNC_REQ_SGXG				208		// �깺�¹� 208
#define TDX_ID_FUNC_ANS_SGXG				209

#define TDX_ID_FUNC_REQ_XGSGXG				210		// �¹��깺�޸� 210
#define TDX_ID_FUNC_ANS_XGSGXG				211

#define TDX_ID_FUNC_REQ_XGSGCD				212		// �¹��깺���� 212
#define TDX_ID_FUNC_ANS_XGSGCD				213

#define TDX_ID_FUNC_REQ_PLWT				214		// ����ί�� 214
#define TDX_ID_FUNC_ANS_PLWT				215

#define TDX_ID_FUNC_REQ_PLCD				216		// �������� 216
#define TDX_ID_FUNC_ANS_PLCD				217

#define TDX_ID_FUNC_REQ_XZDDJC				218		// ����������� 218
#define TDX_ID_FUNC_ANS_XZDDJC				219

#define TDX_ID_FUNC_REQ_XGDDJC				220		// �޸Ķ������ 220
#define TDX_ID_FUNC_ANS_XGDDJC				221

// ������
#define TDX_ID_FUNC_REQ_SDSZJCX				250		// �������ʽ��ѯ 250
#define TDX_ID_FUNC_ANS_SDSZJCX				251

#define TDX_ID_FUNC_REQ_SDSGFCX				252		// �����ֹɷݲ�ѯ 252
#define TDX_ID_FUNC_ANS_SDSGFCX				253

#define TDX_ID_FUNC_REQ_SDSWTCX				254		// ������ί�в�ѯ 254
#define TDX_ID_FUNC_ANS_SDSWTCX				255

#define TDX_ID_FUNC_REQ_SDSCJCX				256		// �����ֳɽ���ѯ 256
#define TDX_ID_FUNC_ANS_SDSCJCX				257

#define TDX_ID_FUNC_REQ_SDSLSCX				258		// ��������ˮ��ѯ 258
#define TDX_ID_FUNC_ANS_SDSLSCX				259

#define TDX_ID_FUNC_REQ_SDSXYZCCX			260		// �����������ʲ���ѯ 260
#define TDX_ID_FUNC_ANS_SDSXYZCCX			261

#define TDX_ID_FUNC_REQ_SDSZQXXCX			262		// ������֤ȯ��Ϣ��ѯ 262
#define TDX_ID_FUNC_ANS_SDSZQXXCX			263

#define TDX_ID_FUNC_REQ_SDSKMSLCX			264		// �����ֿ���(��)������ѯ 264
#define TDX_ID_FUNC_ANS_SDSKMSLCX			265

// ί��������չ(�Լ���������)
#define TDX_ID_FUNC_REQ_FQZQ				300		// ������ǩ 300
#define TDX_ID_FUNC_ANS_FQZQ				301

#define TDX_ID_FUNC_REQ_FW_KHZLCX			302		// (����)�ͻ����ϲ�ѯ 302
#define TDX_ID_FUNC_ANS_FW_KHZLCX			303

#define TDX_ID_FUNC_REQ_FW_HQDTKL			304		// (����)��ȡ��̬���� 304
#define TDX_ID_FUNC_ANS_FW_HQDTKL			305

#define TDX_ID_FUNC_REQ_FW_CPDGPZ			306		// (����)��Ʒ����Ʒ�� 306
#define TDX_ID_FUNC_ANS_FW_CPDGPZ			307

#define TDX_ID_FUNC_REQ_FW_CPDGCX			308		// (����)��Ʒ������ѯ 308
#define TDX_ID_FUNC_ANS_FW_CPDGCX			309

#define TDX_ID_FUNC_REQ_FW_CPDGSZ			310		// (����)��Ʒ�������� 310
#define TDX_ID_FUNC_ANS_FW_CPDGSZ			311

#define TDX_ID_FUNC_REQ_FW_CPDGXG			312		// (����)��Ʒ�����޸� 312
#define TDX_ID_FUNC_ANS_FW_CPDGXG			313

#define TDX_ID_FUNC_REQ_FW_CPDGQX			314		// (����)��Ʒ����ȡ�� 314
#define TDX_ID_FUNC_ANS_FW_CPDGQX			315

#define TDX_ID_FUNC_REQ_FW_ZJLS				316		// (����)�ʽ���ˮ 316
#define TDX_ID_FUNC_ANS_FW_ZJLS				317

#define TDX_ID_FUNC_REQ_FW_PLHQCX			318		// (����)���������ѯ 318
#define TDX_ID_FUNC_ANS_FW_PLHQCX			319

#define TDX_ID_FUNC_REQ_FW_ZXLMCX			320		// (����)��Ѷ��Ŀ��ѯ 320
#define TDX_ID_FUNC_ANS_FW_ZXLMCX			321

#define TDX_ID_FUNC_REQ_FW_HQTSXX			322		// (����)��ȡ��ʾ��Ϣ 322
#define TDX_ID_FUNC_ANS_FW_HQTSXX			323

#define TDX_ID_FUNC_REQ_FW_TPFACX			324		// (����)ͶƱ������ѯ 324
#define TDX_ID_FUNC_ANS_FW_TPFACX			325

#define TDX_ID_FUNC_REQ_FW_TPXXCX			326		// (����)ͶƱ��Ϣ��ѯ 326
#define TDX_ID_FUNC_ANS_FW_TPXXCX			327

#define TDX_ID_FUNC_REQ_FW_TPJGTJ			328		// (����)ͶƱ����ύ 328
#define TDX_ID_FUNC_ANS_FW_TPJGTJ			329

#define TDX_ID_FUNC_REQ_FW_TPJGCX			330		// (����)ͶƱ�����ѯ 330
#define TDX_ID_FUNC_ANS_FW_TPJGCX			331

#define TDX_ID_FUNC_REQ_FW_TPTJCX			332		// (����)ͶƱͳ�Ʋ�ѯ 332
#define TDX_ID_FUNC_ANS_FW_TPTJCX			333

#define TDX_ID_FUNC_REQ_FW_TLZHDMCX			334		// (����)������ϴ����ѯ 334
#define TDX_ID_FUNC_ANS_FW_TLZHDMCX			335

#define TDX_ID_FUNC_REQ_FW_TLZHCFCX			336		// (����)������ϳɷֲ�ѯ 336
#define TDX_ID_FUNC_ANS_FW_TLZHCFCX			337

#define TDX_ID_FUNC_REQ_FW_DDDLCZ			338		// (����)�����¼���� 338
#define TDX_ID_FUNC_ANS_FW_DDDLCZ			339

#define TDX_ID_FUNC_REQ_FW_PLXJCX			340		// (����)�����ּ۲�ѯ 340
#define TDX_ID_FUNC_ANS_FW_PLXJCX			341

#define TDX_ID_FUNC_REQ_FW_XXDY				342		// (����)��Ϣ���� 342
#define TDX_ID_FUNC_ANS_FW_XXDY				343

#define TDX_ID_FUNC_REQ_FW_KHKCL			344		// (����)�ͻ������� 344
#define TDX_ID_FUNC_ANS_FW_KHKCL			345

#define TDX_ID_FUNC_REQ_FW_SCPZXX			346		// (����)�ϴ�������Ϣ 346
#define TDX_ID_FUNC_ANS_FW_SCPZXX			347

#define TDX_ID_FUNC_REQ_FW_XZPZXX			348		// (����)����������Ϣ 348
#define TDX_ID_FUNC_ANS_FW_XZPZXX			349

#define TDX_ID_FUNC_REQ_FW_PZXXZYCX			350		// (����)������ϢժҪ��ѯ 350
#define TDX_ID_FUNC_ANS_FW_PZXXZYCX			351

#define TDX_ID_FUNC_REQ_FW_CLKHCS			352		// (����)����ͻ����� 352
#define TDX_ID_FUNC_ANS_FW_CLKHCS			353

#define TDX_ID_FUNC_REQ_FW_PDLBCX			354		// (����)����б��ѯ 354
#define TDX_ID_FUNC_ANS_FW_PDLBCX			355

#define TDX_ID_FUNC_REQ_FW_PDLSLR			356		// (����)�����ˮ¼�� 356
#define TDX_ID_FUNC_ANS_FW_PDLSLR			357

#define TDX_ID_FUNC_REQ_FW_PDLSCX			358		// (����)�����ˮ��ѯ 358
#define TDX_ID_FUNC_ANS_FW_PDLSCX			359

#define TDX_ID_FUNC_REQ_FW_ZZYWSF			360		// (����)��ֵҵ���շ� 360
#define TDX_ID_FUNC_ANS_FW_ZZYWSF			361

// ���͹���(ֻ��Ӧ����Ч)
#define TDX_ID_FUNC_REQ_PUSH_QZTC			400		// (����)ǿ���˳� 400 [���͹���,����ʹ��]
#define TDX_ID_FUNC_ANS_PUSH_QZTC			401		// (����)ǿ���˳� 401

#define TDX_ID_FUNC_REQ_PUSH_XXTZ			402		// (����)��Ϣ֪ͨ 402 [���͹���,����ʹ��]
#define TDX_ID_FUNC_ANS_PUSH_XXTZ			403		// (����)��Ϣ֪ͨ 403

#define TDX_ID_FUNC_REQ_PUSH_GGXX			404		// (����)������Ϣ 404 [���͹���,����ʹ��]
#define TDX_ID_FUNC_ANS_PUSH_GGXX			405		// (����)������Ϣ 405

// �ֻ�����
#define TDX_ID_FUNC_REQ_MOBILE_ZQCX			500		// (�ֻ�)֤ȯ��ѯ 500
#define TDX_ID_FUNC_ANS_MOBILE_ZQCX			501

#define TDX_ID_FUNC_REQ_MOBILE_GFCX			502		// (�ֻ�)�ɷݲ�ѯ 502
#define TDX_ID_FUNC_ANS_MOBILE_GFCX			503

#define TDX_ID_FUNC_REQ_MOBILE_ZJCX			504		// (�ֻ�)�ʽ��ѯ 504
#define TDX_ID_FUNC_ANS_MOBILE_ZJCX			505

#define TDX_ID_FUNC_REQ_MOBILE_CDCX			506		// (�ֻ�)������ѯ 506
#define TDX_ID_FUNC_ANS_MOBILE_CDCX			507

#define TDX_ID_FUNC_REQ_MOBILE_WTCX			508		// (�ֻ�)ί�в�ѯ 508
#define TDX_ID_FUNC_ANS_MOBILE_WTCX			509

#define TDX_ID_FUNC_REQ_MOBILE_CJCX			510		// (�ֻ�)�ɽ���ѯ 510
#define TDX_ID_FUNC_ANS_MOBILE_CJCX			511

#define TDX_ID_FUNC_REQ_MOBILE_ZZCX			512		// (�ֻ�)ת�˲�ѯ 512
#define TDX_ID_FUNC_ANS_MOBILE_ZZCX			513

#define TDX_ID_FUNC_REQ_MOBILE_LSCX			514		// (�ֻ�)��ˮ��ѯ 514
#define TDX_ID_FUNC_ANS_MOBILE_LSCX			515

#define TDX_ID_FUNC_REQ_MOBILE_JGCX			516		// (�ֻ�)�����ѯ 516
#define TDX_ID_FUNC_ANS_MOBILE_JGCX			517

#define TDX_ID_FUNC_REQ_MOBILE_DZCX			518		// (�ֻ�)���˲�ѯ 518
#define TDX_ID_FUNC_ANS_MOBILE_DZCX			519

#define TDX_ID_FUNC_REQ_MOBILE_YXSBHQCX		520		// (�ֻ�)�����걨�����ѯ 520
#define TDX_ID_FUNC_ANS_MOBILE_YXSBHQCX		521

#define TDX_ID_FUNC_REQ_MOBILE_LSWTCX		522		// (�ֻ�)��ʷί�в�ѯ 522
#define TDX_ID_FUNC_ANS_MOBILE_LSWTCX		523

#define TDX_ID_FUNC_REQ_MOBILE_LSCJCX		524		// (�ֻ�)��ʷ�ɽ���ѯ 524
#define TDX_ID_FUNC_ANS_MOBILE_LSCJCX		525

#define TDX_ID_FUNC_REQ_MOBILE_PHZQCX		526		// (�ֻ�)�����ǩ��ѯ 526
#define TDX_ID_FUNC_ANS_MOBILE_PHZQCX		527

#define TDX_ID_FUNC_REQ_MOBILE_RZLSCX		528		// (�ֻ�)��֤��ˮ��ѯ 528
#define TDX_ID_FUNC_ANS_MOBILE_RZLSCX		529

#define TDX_ID_FUNC_REQ_MOBILE_JJCDCX		530		// (�ֻ�)���𳷵���ѯ 530
#define TDX_ID_FUNC_ANS_MOBILE_JJCDCX		531

#define TDX_ID_FUNC_REQ_MOBILE_JJDRWTCX		532		// (�ֻ�)������ί�в�ѯ 532
#define TDX_ID_FUNC_ANS_MOBILE_JJDRWTCX		533

#define TDX_ID_FUNC_REQ_MOBILE_JJLSWTCX		534		// (�ֻ�)������ʷί�в�ѯ 534
#define TDX_ID_FUNC_ANS_MOBILE_JJLSWTCX		535

#define TDX_ID_FUNC_REQ_MOBILE_JJDRCJCX		536		// (�ֻ�)�����ճɽ���ѯ 536
#define TDX_ID_FUNC_ANS_MOBILE_JJDRCJCX		537

#define TDX_ID_FUNC_REQ_MOBILE_JJLSCJCX		538		// (�ֻ�)������ʷ�ɽ���ѯ 538
#define TDX_ID_FUNC_ANS_MOBILE_JJLSCJCX		539

#define TDX_ID_FUNC_REQ_MOBILE_JJZHCX		540		// (�ֻ�)�����˺Ų�ѯ 540
#define TDX_ID_FUNC_ANS_MOBILE_JJZHCX		541

#define TDX_ID_FUNC_REQ_MOBILE_JJGSCX		542		// (�ֻ�)����˾��ѯ 542
#define TDX_ID_FUNC_ANS_MOBILE_JJGSCX		543

#define TDX_ID_FUNC_REQ_MOBILE_JJDMCX		544		// (�ֻ�)��������ѯ 544
#define TDX_ID_FUNC_ANS_MOBILE_JJDMCX		545

#define TDX_ID_FUNC_REQ_MOBILE_JJFECX		546		// (�ֻ�)����ݶ��ѯ 546
#define TDX_ID_FUNC_ANS_MOBILE_JJFECX		547

#define TDX_ID_FUNC_REQ_MOBILE_JJDZCX		548		// (�ֻ�)������˲�ѯ 548
#define TDX_ID_FUNC_ANS_MOBILE_JJDZCX		549

#define TDX_ID_FUNC_REQ_MOBILE_JJJGCX		550		// (�ֻ�)���𽻸��ѯ 550
#define TDX_ID_FUNC_ANS_MOBILE_JJJGCX		551

#define TDX_ID_FUNC_REQ_MOBILE_JJFJYWTCX	552		// (�ֻ�)����ǽ���ί�в�ѯ 552
#define TDX_ID_FUNC_ANS_MOBILE_JJFJYWTCX	553

#define TDX_ID_FUNC_REQ_MOBILE_QHHYCX		560		// (�ֻ�)�ڻ���Լ��ѯ 560
#define TDX_ID_FUNC_ANS_MOBILE_QHHYCX		561

#define TDX_ID_FUNC_REQ_MOBILE_QHZHHYCX		562		// (�ֻ�)�ڻ���Ϻ�Լ��ѯ 562
#define TDX_ID_FUNC_ANS_MOBILE_QHZHHYCX		563

#define TDX_ID_FUNC_REQ_MOBILE_QHZHCCCX		564		// (�ֻ�)�ڻ���ϳֲֲ�ѯ 564
#define TDX_ID_FUNC_ANS_MOBILE_QHZHCCCX		565

#define TDX_ID_FUNC_REQ_MOBILE_QHZHWTCX		566		// (�ֻ�)�ڻ����ί�в�ѯ 566
#define TDX_ID_FUNC_ANS_MOBILE_QHZHWTCX		567

#define TDX_ID_FUNC_REQ_MOBILE_QHZHCLCX		568		// (�ֻ�)�ڻ���ϲ��Բ�ѯ 568
#define TDX_ID_FUNC_ANS_MOBILE_QHZHCLCX		569

#define TDX_ID_FUNC_REQ_MOBILE_GFHZCX		570		// (�ֻ�)�ɷݻ��ܲ�ѯ 570
#define TDX_ID_FUNC_ANS_MOBILE_GFHZCX		571

#define TDX_ID_FUNC_REQ_MOBILE_WTHZCX		572		// (�ֻ�)ί�л��ܲ�ѯ 572
#define TDX_ID_FUNC_ANS_MOBILE_WTHZCX		573

#define TDX_ID_FUNC_REQ_MOBILE_CJHZCX		574		// (�ֻ�)�ɽ����ܲ�ѯ 574
#define TDX_ID_FUNC_ANS_MOBILE_CJHZCX		575

#define TDX_ID_FUNC_REQ_MOBILE_CJMXCX		576		// (�ֻ�)�ɽ���ϸ��ѯ 576
#define TDX_ID_FUNC_ANS_MOBILE_CJMXCX		577


#define TDX_ID_FUNC_REQ_MOBILE_XYRZMRPTCX	600		// (�ֻ�)���������������ײ�ѯ 600
#define TDX_ID_FUNC_ANS_MOBILE_XYRZMRPTCX	601

#define TDX_ID_FUNC_REQ_MOBILE_XYRQMCPTCX	602		// (�ֻ�)������ȯ�������ײ�ѯ 602
#define TDX_ID_FUNC_ANS_MOBILE_XYRQMCPTCX	603

#define TDX_ID_FUNC_REQ_MOBILE_XYMCHKPTCX	604		// (�ֻ�)���������������ײ�ѯ 604
#define TDX_ID_FUNC_ANS_MOBILE_XYMCHKPTCX	605

#define TDX_ID_FUNC_REQ_MOBILE_XYMRHQPTCX	606		// (�ֻ�)�������뻹ȯ���ײ�ѯ 606
#define TDX_ID_FUNC_ANS_MOBILE_XYMRHQPTCX	607

#define TDX_ID_FUNC_REQ_MOBILE_XYXJHKPTCX	608		// (�ֻ�)�����ֽ𻹿����ײ�ѯ 608
#define TDX_ID_FUNC_ANS_MOBILE_XYXJHKPTCX	609

#define TDX_ID_FUNC_REQ_MOBILE_XYXQHQPTCX	610		// (�ֻ�)������ȯ��ȯ���ײ�ѯ 610
#define TDX_ID_FUNC_ANS_MOBILE_XYXQHQPTCX	611

#define TDX_ID_FUNC_REQ_MOBILE_XYYQHZPTCX	612		// (�ֻ�)������ȯ��ת���ײ�ѯ 612
#define TDX_ID_FUNC_ANS_MOBILE_XYYQHZPTCX	613

#define TDX_ID_FUNC_REQ_MOBILE_XYDBHZPTCX	614		// (�ֻ�)���õ�����ת���ײ�ѯ 614
#define TDX_ID_FUNC_ANS_MOBILE_XYDBHZPTCX	615

#define TDX_ID_FUNC_REQ_MOBILE_XYDBZRPTCX	616		// (�ֻ�)���õ���ת�����ײ�ѯ 616
#define TDX_ID_FUNC_ANS_MOBILE_XYDBZRPTCX	617

#define TDX_ID_FUNC_REQ_MOBILE_XYDBZCPTCX	618		// (�ֻ�)���õ���ת�����ײ�ѯ 618
#define TDX_ID_FUNC_ANS_MOBILE_XYDBZCPTCX	619

#define TDX_ID_FUNC_REQ_MOBILE_XYZCXXCX		620		// (�ֻ�)�����ʲ���Ϣ��ѯ 620
#define TDX_ID_FUNC_ANS_MOBILE_XYZCXXCX		621

#define TDX_ID_FUNC_REQ_MOBILE_XYGFXXCX		622		// (�ֻ�)���ùɷ���Ϣ��ѯ 622
#define TDX_ID_FUNC_ANS_MOBILE_XYGFXXCX		623

#define TDX_ID_FUNC_REQ_MOBILE_XYBDZQCX		624		// (�ֻ�)���ñ��֤ȯ��ѯ 624
#define TDX_ID_FUNC_ANS_MOBILE_XYBDZQCX		625

#define TDX_ID_FUNC_REQ_MOBILE_XYZJHZCX		626		// (�ֻ�)����ֱ�ӻ�ת��ѯ 626
#define TDX_ID_FUNC_ANS_MOBILE_XYZJHZCX		627

#define TDX_ID_FUNC_REQ_MOBILE_XYLXFYCX		628		// (�ֻ�)������Ϣ���ò�ѯ 628
#define TDX_ID_FUNC_ANS_MOBILE_XYLXFYCX		629

#define TDX_ID_FUNC_REQ_MOBILE_XYWPHYCX		630		// (�ֻ�)����δƽ��Լ��ѯ 630
#define TDX_ID_FUNC_ANS_MOBILE_XYWPHYCX		631

#define TDX_ID_FUNC_REQ_MOBILE_XYYPHYCX		632		// (�ֻ�)������ƽ��Լ��ѯ 632
#define TDX_ID_FUNC_ANS_MOBILE_XYYPHYCX		633

#define TDX_ID_FUNC_REQ_MOBILE_XYDRHYCX		634		// (�ֻ�)���õ��պ�Լ��ѯ 634
#define TDX_ID_FUNC_ANS_MOBILE_XYDRHYCX		635

#define TDX_ID_FUNC_REQ_MOBILE_XYRZHYCX		636		// (�ֻ�)�������ʺ�Լ��ѯ 636
#define TDX_ID_FUNC_ANS_MOBILE_XYRZHYCX		637

#define TDX_ID_FUNC_REQ_MOBILE_XYRQHYCX		638		// (�ֻ�)������ȯ��Լ��ѯ 638
#define TDX_ID_FUNC_ANS_MOBILE_XYRQHYCX		639

#define TDX_ID_FUNC_REQ_MOBILE_XYZJFZCX		640		// (�ֻ�)�����ʽ�ծ��ѯ 640
#define TDX_ID_FUNC_ANS_MOBILE_XYZJFZCX		641

#define TDX_ID_FUNC_REQ_MOBILE_XYGFFZCX		642		// (�ֻ�)���ùɷݸ�ծ��ѯ 642
#define TDX_ID_FUNC_ANS_MOBILE_XYGFFZCX		643

#define TDX_ID_FUNC_REQ_MOBILE_XYJYDBPZQCX	644		// (�ֻ�)���ý��׵���Ʒ֤ȯ��ѯ 644
#define TDX_ID_FUNC_ANS_MOBILE_XYJYDBPZQCX	645

#define TDX_ID_FUNC_REQ_MOBILE_XYJYFJYHZCX	646		// (�ֻ�)���ý��׷ǽ��׻�ת��ѯ 646
#define TDX_ID_FUNC_ANS_MOBILE_XYJYFJYHZCX	647

#define TDX_ID_FUNC_REQ_MOBILE_XYJYFZLSCX	648		// (�ֻ�)���ý��׸�ծ��ˮ��ѯ 648
#define TDX_ID_FUNC_ANS_MOBILE_XYJYFZLSCX	649	

#define TDX_ID_FUNC_REQ_MOBILE_ETFWTCX		700		// (�ֻ�)ETFί�в�ѯ 700
#define TDX_ID_FUNC_ANS_MOBILE_ETFWTCX		701

#define TDX_ID_FUNC_REQ_MOBILE_ETFCJCX		702		// (�ֻ�)ETF�ɽ���ѯ 702
#define TDX_ID_FUNC_ANS_MOBILE_ETFCJCX		703


#define	TDX_ID_FUNC_REQ_MOBILE_LCCPFECX		750		// (�ֻ�)��Ʋ�Ʒ�ݶ��ѯ 750
#define	TDX_ID_FUNC_ANS_MOBILE_LCCPFECX		751

#define	TDX_ID_FUNC_REQ_MOBILE_LCCPWTCX		752		// (�ֻ�)��Ʋ�Ʒί�в�ѯ 752
#define	TDX_ID_FUNC_ANS_MOBILE_LCCPWTCX		753

#define	TDX_ID_FUNC_REQ_MOBILE_LCCPCJCX		754		// (�ֻ�)��Ʋ�Ʒ�ɽ���ѯ 754
#define	TDX_ID_FUNC_ANS_MOBILE_LCCPCJCX		755

#define	TDX_ID_FUNC_REQ_MOBILE_LCCPDMCX		756		// (�ֻ�)��Ʋ�Ʒ�����ѯ 756
#define	TDX_ID_FUNC_ANS_MOBILE_LCCPDMCX		757

#define	TDX_ID_FUNC_REQ_MOBILE_LCCPDQDESGCX	758		// (�ֻ�)��Ʋ�Ʒ���ڶ����깺��ѯ 758
#define	TDX_ID_FUNC_ANS_MOBILE_LCCPDQDESGCX	759

#define	TDX_ID_FUNC_REQ_MOBILE_YHLCCPDMCX	790		// (�ֻ�)������Ʋ�Ʒ�����ѯ 790
#define	TDX_ID_FUNC_ANS_MOBILE_YHLCCPDMCX	791

#define	TDX_ID_FUNC_REQ_MOBILE_YHLCCPFECX	792		// (�ֻ�)������Ʋ�Ʒ�ݶ��ѯ 792
#define	TDX_ID_FUNC_ANS_MOBILE_YHLCCPFECX	793

#define	TDX_ID_FUNC_REQ_MOBILE_YHLCCPWTCX	794		// (�ֻ�)������Ʋ�Ʒί�в�ѯ 794
#define	TDX_ID_FUNC_ANS_MOBILE_YHLCCPWTCX	795

#define	TDX_ID_FUNC_REQ_MOBILE_YHLCCPCJCX	796		// (�ֻ�)������Ʋ�Ʒ�ɽ���ѯ 796
#define	TDX_ID_FUNC_ANS_MOBILE_YHLCCPCJCX	797

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��ȫ����Э�鼰����������Э��(800~899)
#define TDX_ID_FUNC_REQ_CA_ZHSQ				800		// CA�˻����� 800
#define TDX_ID_FUNC_ANS_CA_ZHSQ				801

#define TDX_ID_FUNC_REQ_CA_ZHCX				802		// CA�ʺŲ�ѯ 802
#define TDX_ID_FUNC_ANS_CA_ZHCX				803

#define TDX_ID_FUNC_REQ_CA_ZHJY				804		// CA�˻�У�� 804
#define TDX_ID_FUNC_ANS_CA_ZHJY				805

#define TDX_ID_FUNC_REQ_CA_TXMMXG			806		// CA��֤�����޸� 806
#define TDX_ID_FUNC_ANS_CA_TXMMXG			807

#define TDX_ID_FUNC_REQ_CA_TXMMCX			808		// CA��֤�����ѯ 808
#define TDX_ID_FUNC_ANS_CA_TXMMCX			809

#define TDX_ID_FUNC_REQ_CA_ZSXZ				810		// CA֤������ 810
#define TDX_ID_FUNC_ANS_CA_ZSXZ				811

#define TDX_ID_FUNC_REQ_CA_ZSXZQR			812		// CA֤������ȷ�� 812
#define TDX_ID_FUNC_ANS_CA_ZSXZQR			813

#define TDX_ID_FUNC_REQ_CA_ZTXM				814		// CA״̬�޸� 814
#define TDX_ID_FUNC_ANS_CA_ZTXM				815

#define TDX_ID_FUNC_REQ_CA_ZSGX				816		// CA֤����� 816
#define TDX_ID_FUNC_ANS_CA_ZSGX				817

#define TDX_ID_FUNC_REQ_CA_YHFJCX			818		// �û��ּ���ѯ 818
#define TDX_ID_FUNC_ANS_CA_YHFJCX			819

#define TDX_ID_FUNC_REQ_CA_YHFJSQ			820		// �û��ּ����� 820
#define TDX_ID_FUNC_ANS_CA_YHFJSQ			821

#define TDX_ID_FUNC_REQ_CA_HTTPYHFJCX		822		// HTTP�û��ּ���ѯ 822
#define TDX_ID_FUNC_ANS_CA_HTTPYHFJCX		823

#define TDX_ID_FUNC_REQ_CA_ANONUSER			824		// ע�������û� 824
#define TDX_ID_FUNC_ANS_CA_ANONUSER			825

#define TDX_ID_FUNC_REQ_CA_XJZT				826		// �½����� 826
#define TDX_ID_FUNC_ANS_CA_XJZT				827

#define TDX_ID_FUNC_REQ_CA_CXZT				828		// ��ѯ���� 828
#define TDX_ID_FUNC_ANS_CA_CXZT				829

#define TDX_ID_FUNC_REQ_CA_CXHF				830		// ��ѯ�ظ� 830
#define TDX_ID_FUNC_ANS_CA_CXHF				831

#define TDX_ID_FUNC_REQ_CA_HFZT				832		// �ظ����� 832
#define TDX_ID_FUNC_ANS_CA_HFZT				833

#define TDX_ID_FUNC_REQ_CA_GBZT				834		// �������ر����� 834
#define TDX_ID_FUNC_ANS_CA_GBZT				835

#define TDX_ID_FUNC_REQ_CA_USERMESSAGE		836		// �û���Ϣ 836
#define TDX_ID_FUNC_ANS_CA_USERMESSAGE		837

#define TDX_ID_FUNC_REQ_CA_USERACTION		838		// �����û����� 838
#define TDX_ID_FUNC_ANS_CA_USERACTION		839

#define TDX_ID_FUNC_REQ_CA_ANONYLOGIN		840		// �����û���¼ 840
#define TDX_ID_FUNC_ANS_CA_ANONYLOGIN		841

#define TDX_ID_FUNC_REQ_CA_QUERYMSG			842		// ��ѯ�Ƿ����������� 842
#define TDX_ID_FUNC_ANS_CA_QUERYMSG			843

#define TDX_ID_FUNC_REQ_CA_READED			844		// ���Ķ����� 844
#define TDX_ID_FUNC_ANS_CA_READED			845

#define TDX_ID_FUNC_REQ_CA_NOTICEINFO		846		// �û����漰����������Ϣ 846
#define TDX_ID_FUNC_ANS_CA_NOTICEINFO		847

#define TDX_ID_FUNC_REQ_CA_INFOFEEDBACK		848		// �û���Ѷ��Ϣ���� 848
#define TDX_ID_FUNC_ANS_CA_INFOFEEDBACK		849
// �û�������Э��
#define TDX_ID_FUNC_REQ_TQ_KHJY				860		// TQ�ͻ���У�� 860
#define TDX_ID_FUNC_ANS_TQ_KHJY				861

#define TDX_ID_FUNC_REQ_UM_UBROKER			862		// ����֤ȯ�û�Ͷ�ʹ�����Ϣ 862
#define TDX_ID_FUNC_ANS_UM_UBROKER			863

#define TDX_ID_FUNC_REQ_UC_QXCX				876		// Ȩ�޲�ѯ 876
#define TDX_ID_FUNC_ANS_UC_QXCX				876

#define TDX_ID_FUNC_REQ_UC_QXSQ				878		// Ȩ������ 878
#define TDX_ID_FUNC_ANS_UC_QXSQ				879

// �����
#define TDX_ID_FUNC_REQ_CA_SYZC_GD			880		// �����û�ע�� 880
#define TDX_ID_FUNC_ANS_CA_SYZC_GD			881

#define TDX_ID_FUNC_REQ_CA_XXLR_GD			882		// ��ϸ��Ϣ¼�� 882
#define TDX_ID_FUNC_ANS_CA_XXLR_GD			883

#define TDX_ID_FUNC_REQ_CA_SYJH_GD			884		// �����û����� 884
#define TDX_ID_FUNC_ANS_CA_SYJH_GD			885

#define TDX_ID_FUNC_REQ_CA_ZHJY_GD			886		// �˻�У�� 886
#define TDX_ID_FUNC_ANS_CA_ZHJY_GD			887

#define TDX_ID_FUNC_REQ_CA_DJCX_GD			888		// �ȼ���ѯ 888
#define TDX_ID_FUNC_ANS_CA_DJCX_GD			889

#define TDX_ID_FUNC_REQ_CA_KSJCX_GD			890		// �����뼶���ѯ 890
#define TDX_ID_FUNC_ANS_CA_KSJCX_GD			891

#define TDX_ID_FUNC_REQ_CA_KHSQ_GD			892		// �ͻ����뼶�� 892
#define TDX_ID_FUNC_ANS_CA_KHSQ_GD			893

#define TDX_ID_FUNC_REQ_CA_YHZXQX_GD		894		// �û���ѶȨ�� 894
#define TDX_ID_FUNC_ANS_CA_YHZXQX_GD		895

#define TDX_ID_FUNC_REQ_CA_YHQXZX			896		// �û�Ȩ��ע�� 896
#define TDX_ID_FUNC_ANS_CA_YHQXZX			897

#define TDX_ID_FUNC_REQ_CA_CXDLLS			898		// ��ѯ��½��ʷ 898
#define TDX_ID_FUNC_ANS_CA_CXDLLS			899	


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// ��֤ת����	
#define TDX_ID_FUNC_REQ_YZZZ				900		// ��֤ת�� 900
#define TDX_ID_FUNC_ANS_YZZZ				901
	
#define TDX_ID_FUNC_REQ_YHLS				902		// ������ˮ 902
#define TDX_ID_FUNC_ANS_YHLS				903
	
#define TDX_ID_FUNC_REQ_YHYE				904		// ������� 904
#define TDX_ID_FUNC_ANS_YHYE				905
	
#define	TDX_ID_FUNC_REQ_XGYHMM				906		// �޸��������� 906
#define	TDX_ID_FUNC_ANS_XGYHMM				907

#define TDX_ID_FUNC_REQ_YHXX				908		// ��ѯ������Ϣ 908
#define TDX_ID_FUNC_ANS_YHXX				909

#define	TDX_ID_FUNC_REQ_SFCGZZ				910		// �������ת�� 910
#define	TDX_ID_FUNC_ANS_SFCGZZ				911

#define	TDX_ID_FUNC_REQ_SFZZCX				912		// ����ת�ʲ�ѯ 912
#define	TDX_ID_FUNC_ANS_SFZZCX				913

#define	TDX_ID_FUNC_REQ_SFYECX				914		// ��������ѯ 914
#define	TDX_ID_FUNC_ANS_SFYECX				915

#define	TDX_ID_FUNC_REQ_ZZXG				916		// ת���޸� 916
#define	TDX_ID_FUNC_ANS_ZZXG				917

#define	TDX_ID_FUNC_REQ_ZZQX				918		// ת��ȡ�� 918
#define	TDX_ID_FUNC_ANS_ZZQX				919

#define	TDX_ID_FUNC_REQ_KQZJCX				920		// ��ȡ�ʽ��ѯ 920
#define	TDX_ID_FUNC_ANS_KQZJCX				921

#define	TDX_ID_FUNC_REQ_ZZYHCX				922		// ת�����в�ѯ 922
#define	TDX_ID_FUNC_ANS_ZZYHCX				923

#define	TDX_ID_FUNC_REQ_YHZHJZZ				924		// �����˻���ת�� 924
#define	TDX_ID_FUNC_ANS_YHZHJZZ				925

#define	TDX_ID_FUNC_REQ_YDZJZZ				926		// Զ���ʽ�ת�� 926
#define	TDX_ID_FUNC_ANS_YDZJZZ				927

#define	TDX_ID_FUNC_REQ_YDZZCX				928		// Զ��ת�˲�ѯ 928
#define	TDX_ID_FUNC_ANS_YDZZCX				929

#define	TDX_ID_FUNC_REQ_YDZJCX				930		// Զ���ʽ��ѯ 930
#define	TDX_ID_FUNC_ANS_YDZJCX				931

#define	TDX_ID_FUNC_REQ_YDKZCX				932		// Զ�˿�ת��ѯ 932
#define	TDX_ID_FUNC_ANS_YDKZCX				933

#define	TDX_ID_FUNC_REQ_YHKLBCX				934		// ���п��б��ѯ 934
#define	TDX_ID_FUNC_ANS_YHKLBCX				935

#define	TDX_ID_FUNC_REQ_YHKXXCX				936		// ���п���Ϣ��ѯ 936
#define	TDX_ID_FUNC_ANS_YHKXXCX				937

#define	TDX_ID_FUNC_REQ_YHKXXXG				938		// ���п���Ϣ�޸� 938
#define	TDX_ID_FUNC_ANS_YHKXXXG				939

#define	TDX_ID_FUNC_REQ_YHKBGCZ				940		// ���п�������� 940
#define	TDX_ID_FUNC_ANS_YHKBGCZ				941

#define	TDX_ID_FUNC_REQ_YHKFLCX				942		// ���п����ʲ�ѯ 942
#define	TDX_ID_FUNC_ANS_YHKFLCX				943

#define	TDX_ID_FUNC_REQ_ZHJZZLSCX			944		// �˺ż�ת����ˮ��ѯ 944
#define	TDX_ID_FUNC_ANS_ZHJZZLSCX			945

#define	TDX_ID_FUNC_REQ_ZHJZZDRLSCX			946		// �˺ż�ת�˵�����ˮ��ѯ 946
#define	TDX_ID_FUNC_ANS_ZHJZZDRLSCX			947

#define	TDX_ID_FUNC_REQ_YHYELSCX			948		// ���������ˮ��ѯ 948
#define	TDX_ID_FUNC_ANS_YHYELSCX			949

#define	TDX_ID_FUNC_REQ_JHZZLSCX			950		// �ƻ�ת����ˮ��ѯ 950
#define	TDX_ID_FUNC_ANS_JHZZLSCX			951

#define	TDX_ID_FUNC_REQ_DCGYHLSCX			952		// ����������ˮ��ѯ 952
#define	TDX_ID_FUNC_ANS_DCGYHLSCX			953

#define	TDX_ID_FUNC_REQ_DCGZHTB				954		// �����˺�ͬ�� 954
#define	TDX_ID_FUNC_ANS_DCGZHTB				955

#define	TDX_ID_FUNC_REQ_HHYWCZ				990		// ����ҵ����� 990
#define	TDX_ID_FUNC_ANS_HHYWCZ				991

#define	TDX_ID_FUNC_REQ_HHYHCX				992		// �������в�ѯ 992
#define	TDX_ID_FUNC_ANS_HHYHCX				993

#define	TDX_ID_FUNC_REQ_HHHLCX				994		// ������ʲ�ѯ 994
#define	TDX_ID_FUNC_ANS_HHHLCX				995

#define	TDX_ID_FUNC_REQ_HHWTCX				996		// ����ί�в�ѯ 996
#define	TDX_ID_FUNC_ANS_HHWTCX				997


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��־�鿴��(1000~1099)
#define TDX_ID_FUNC_REQ_RZ_KHJY				1000	// ��־�ͻ�У�� 1000
#define TDX_ID_FUNC_ANS_RZ_KHJY				1001

#define TDX_ID_FUNC_REQ_RZ_KHCZJLCX			1002	// �ͻ�������¼��ѯ 1002
#define TDX_ID_FUNC_ANS_RZ_KHCZJLCX			1003

#define TDX_ID_FUNC_REQ_RZ_ZHSQ				1004	// �ʺ����� 1004
#define TDX_ID_FUNC_ANS_RZ_ZHSQ				1005

#define TDX_ID_FUNC_REQ_RZ_ZHDJJD			1006	// �ʺŶ���ⶳ 1006
#define TDX_ID_FUNC_ANS_RZ_ZHDJJD			1007

#define TDX_ID_FUNC_REQ_RZ_CXTJFX			1008	// ��ѯͳ�Ʒ��� 1008
#define TDX_ID_FUNC_ANS_RZ_CXTJFX			1009

#define TDX_ID_FUNC_REQ_RZ_QDYGBCX			1010	// ������رղ�ѯ 1010
#define TDX_ID_FUNC_ANS_RZ_QDYGBCX			1011

#define TDX_ID_FUNC_REQ_RZ_HTFMCD			1012	// ��̨��æ�̶� 1012
#define TDX_ID_FUNC_ANS_RZ_HTFMCD			1013

#define TDX_ID_FUNC_REQ_RZ_HTCFHCX			1014	// ��̨�����ɲ�ѯ 1014
#define TDX_ID_FUNC_ANS_RZ_HTCFHCX			1015

#define TDX_ID_FUNC_REQ_RZ_FXIPPM			1016	// ����IP���� 1016
#define TDX_ID_FUNC_ANS_RZ_FXIPPM			1017

#define TDX_ID_FUNC_REQ_RZ_FXZH				1018	// �����˺� 1018
#define TDX_ID_FUNC_ANS_RZ_FXZH				1019

#define TDX_ID_FUNC_REQ_RZ_FXXXXX			1020	// ������ϸ��Ϣ 1020
#define TDX_ID_FUNC_ANS_RZ_FXXXXX			1021

#define TDX_ID_FUNC_REQ_RZ_HTFMCDXX			1022	// ��̨��æ�̶���ϸ 1022
#define TDX_ID_FUNC_ANS_RZ_HTFMCDXX			1023

#define TDX_ID_FUNC_REQ_RZ_TCIP				1024	// ��������IP 1024
#define TDX_ID_FUNC_ANS_RZ_TCIP				1025


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// ��ѯ��	
#define TDX_ID_FUNC_REQ_CDCX				1100	// �ɳ�����ѯ 1100
#define TDX_ID_FUNC_ANS_CDCX				1101
	
#define TDX_ID_FUNC_REQ_DRWTCX				1102	// ����ί�в�ѯ 1102
#define TDX_ID_FUNC_ANS_DRWTCX				1103

#define TDX_ID_FUNC_REQ_LSWTCX				1104	// ��ʷί�в�ѯ 1104
#define TDX_ID_FUNC_ANS_LSWTCX				1105

#define TDX_ID_FUNC_REQ_WTCX				1106	// ί�в�ѯ 1106
#define TDX_ID_FUNC_ANS_WTCX				1107

#define TDX_ID_FUNC_REQ_DRCJCX				1108	// ���ճɽ���ѯ 1108
#define TDX_ID_FUNC_ANS_DRCJCX				1109

#define TDX_ID_FUNC_REQ_LSCJCX				1110	// ��ʷ�ɽ���ѯ 1110
#define TDX_ID_FUNC_ANS_LSCJCX				1111

#define TDX_ID_FUNC_REQ_CJCX				1112	// �ɽ���ѯ 1112
#define TDX_ID_FUNC_ANS_CJCX				1113

#define	TDX_ID_FUNC_REQ_GFCX				1114	// �ɷݲ�ѯ 1114
#define	TDX_ID_FUNC_ANS_GFCX				1115

#define	TDX_ID_FUNC_REQ_XGPH				1116	// �¹���� 1116
#define	TDX_ID_FUNC_ANS_XGPH				1117

#define TDX_ID_FUNC_REQ_ZJLS				1118	// �ʽ���ˮ 1118
#define TDX_ID_FUNC_ANS_ZJLS				1119

#define TDX_ID_FUNC_REQ_JGD					1120	// ��� 1120
#define TDX_ID_FUNC_ANS_JGD					1121

#define TDX_ID_FUNC_REQ_GDCX				1122	// �ɶ���ѯ 1122
#define TDX_ID_FUNC_ANS_GDCX				1123

#define TDX_ID_FUNC_REQ_ZQXX				1124	// ȡ֤ȯ��Ϣ 1124
#define TDX_ID_FUNC_ANS_ZQXX				1125

#define TDX_ID_FUNC_REQ_ZQCX				1126	// ��ǩ��ѯ 1126
#define TDX_ID_FUNC_ANS_ZQCX				1127

#define TDX_ID_FUNC_REQ_XGCBJ				1128	// �޸ĳɱ��� 1128
#define TDX_ID_FUNC_ANS_XGCBJ				1129	

#define TDX_ID_FUNC_REQ_XGLXFS				1130	// (��ѯ)�޸���ϵ��ʽ 1130
#define TDX_ID_FUNC_ANS_XGLXFS				1131

#define TDX_ID_FUNC_REQ_DZD					1132	// ���ʵ� 1132
#define TDX_ID_FUNC_ANS_DZD					1133

#define TDX_ID_FUNC_REQ_PSQYCX				1134	// ����Ȩ���ѯ 1134
#define TDX_ID_FUNC_ANS_PSQYCX				1135

#define TDX_ID_FUNC_REQ_QZXXCX				1136	// Ȩ֤��Ϣ��ѯ 1136
#define TDX_ID_FUNC_ANS_QZXXCX				1137

#define TDX_ID_FUNC_REQ_CJHZCX				1138	// �ɽ����ܲ�ѯ 1138
#define TDX_ID_FUNC_ANS_CJHZCX				1139

#define TDX_ID_FUNC_REQ_GFHZCX				1140	// �ɷݻ��ܲ�ѯ 1140
#define TDX_ID_FUNC_ANS_GFHZCX				1141

#define TDX_ID_FUNC_REQ_KTXY				1142	// ��ͨȡ��Э�� 1142
#define TDX_ID_FUNC_ANS_KTXY				1143

#define TDX_ID_FUNC_REQ_YWTCX				1144	// ��ί�в�ѯ 1144
#define TDX_ID_FUNC_ANS_YWTCX				1145

#define TDX_ID_FUNC_REQ_QDXY				1146	// ǩ��Э�� 1146
#define TDX_ID_FUNC_ANS_QDXY				1147

#define TDX_ID_FUNC_REQ_ZTZJCX				1148	// ��;�ʽ��ѯ 1148
#define TDX_ID_FUNC_ANS_ZTZJCX				1149

#define TDX_ID_FUNC_REQ_JGXZZ				1150	// �����ת�� 1150
#define TDX_ID_FUNC_ANS_JGXZZ				1151

#define TDX_ID_FUNC_REQ_FZDM				1152	// ��ݸ��ȡ������� 1152
#define TDX_ID_FUNC_ANS_FZDM				1153

#define TDX_ID_FUNC_REQ_HQXYNR				1154	// ��ȡЭ������ 1154
#define TDX_ID_FUNC_ANS_HQXYNR				1155

#define TDX_ID_FUNC_REQ_HQIPOLB				1156	// ��ȡIPO�б� 1156
#define TDX_ID_FUNC_ANS_HQIPOLB				1157

#define TDX_ID_FUNC_REQ_IPOXXCX				1158	// IPO��Ϣ��ѯ 1158
#define TDX_ID_FUNC_ANS_IPOXXCX				1159

#define TDX_ID_FUNC_REQ_YYCX				1160	// Ԥ��ҪԼ��ѯ 1160
#define TDX_ID_FUNC_ANS_YYCX				1161

#define TDX_ID_FUNC_REQ_YYCD				1162	// Ԥ��ҪԼ���� 1162
#define TDX_ID_FUNC_ANS_YYCD				1163

#define TDX_ID_FUNC_REQ_YYSB				1164	// Ԥ��ҪԼ�걨 1164
#define TDX_ID_FUNC_ANS_YYSB				1165

#define TDX_ID_FUNC_REQ_ZYHG				1166	// ��Ѻ�ع� 1166
#define TDX_ID_FUNC_ANS_ZYHG				1167

#define TDX_ID_FUNC_REQ_WJSCJMXCX			1168	// δ���ճɽ���ϸ��ѯ 1168
#define TDX_ID_FUNC_ANS_WJSCJMXCX			1169

#define TDX_ID_FUNC_REQ_CGYYCQ				1170	// ���ԤԼ��ȡҵ�� 1170
#define TDX_ID_FUNC_ANS_CGYYCQ				1171

#define TDX_ID_FUNC_REQ_CGYYCQCX			1172	// ���ԤԼ��ȡҵ���ѯ 1172
#define TDX_ID_FUNC_ANS_CGYYCQCX			1173

#define	TDX_ID_FUNC_REQ_WTHZCX				1174	// ί�л��ܲ�ѯ 1174
#define	TDX_ID_FUNC_ANS_WTHZCX				1175

#define	TDX_ID_FUNC_REQ_ZJMXCX				1176	// �ʽ���ϸ��ѯ 1176
#define	TDX_ID_FUNC_ANS_ZJMXCX				1177

#define	TDX_ID_FUNC_REQ_CXXZCGYH			1178	// ��ѯѡ�������� 1178
#define	TDX_ID_FUNC_ANS_CXXZCGYH			1179

#define	TDX_ID_FUNC_REQ_XZCGYH				1180	// ѡ�������� 1180
#define	TDX_ID_FUNC_ANS_XZCGYH				1181

#define	TDX_ID_FUNC_REQ_CXXYXX				1182	// ��ѯЭ����Ϣ 1182
#define	TDX_ID_FUNC_ANS_CXXYXX				1183

#define	TDX_ID_FUNC_REQ_LSCJHZCX			1184	// ��ʷ�ɽ����ܲ�ѯ 1184
#define	TDX_ID_FUNC_ANS_LSCJHZCX			1185

#define	TDX_ID_FUNC_REQ_CJMXCX				1186	// �ɽ���ϸ��ѯ 1186
#define	TDX_ID_FUNC_ANS_CJMXCX				1187

#define	TDX_ID_FUNC_REQ_WTCXMX				1188	// ί�в�ѯ��ϸ 1188
#define	TDX_ID_FUNC_ANS_WTCXMX				1189

#define	TDX_ID_FUNC_REQ_CJCXMX				1190	// �ɽ���ѯ��ϸ 1190
#define	TDX_ID_FUNC_ANS_CJCXMX				1191

#define	TDX_ID_FUNC_REQ_YXSBHQCX			1192	// �����걨�����ѯ 1192
#define	TDX_ID_FUNC_ANS_YXSBHQCX			1193

#define	TDX_ID_FUNC_REQ_PLWTCX				1194	// ����ί�в�ѯ 1194
#define	TDX_ID_FUNC_ANS_PLWTCX				1195

#define	TDX_ID_FUNC_REQ_LOFHBXGDMCX			1196	// LOF�ϲ���ش����ѯ 1196
#define	TDX_ID_FUNC_ANS_LOFHBXGDMCX			1197

#define	TDX_ID_FUNC_REQ_LOFFCXGDMCX			1198	// LOF�ֲ���ش����ѯ 1198
#define	TDX_ID_FUNC_ANS_LOFFCXGDMCX			1199

#define	TDX_ID_FUNC_REQ_LOFPHYWDRWTCX		1200	// LOF�̺�ҵ����ί�в�ѯ 1200
#define	TDX_ID_FUNC_ANS_LOFPHYWDRWTCX		1201

#define	TDX_ID_FUNC_REQ_LOFPHYWLSWTCX		1202	// LOF�̺�ҵ����ʷί�в�ѯ 1202
#define	TDX_ID_FUNC_ANS_LOFPHYWLSWTCX		1203

#define	TDX_ID_FUNC_REQ_LOFPHYWDRCJCX		1204	// LOF�̺�ҵ���ճɽ���ѯ 1204
#define	TDX_ID_FUNC_ANS_LOFPHYWDRCJCX		1205

#define	TDX_ID_FUNC_REQ_LOFPHYWLSCJCX		1206	// LOF�̺�ҵ����ʷ�ɽ���ѯ 1206
#define	TDX_ID_FUNC_ANS_LOFPHYWLSCJCX		1207

#define	TDX_ID_FUNC_REQ_LOFPHYWCDCX			1208	// LOF�̺�ҵ�񳷵���ѯ 1208
#define	TDX_ID_FUNC_ANS_LOFPHYWCDCX			1209

#define	TDX_ID_FUNC_REQ_FSGFCX				1210	// �����ɷݲ�ѯ 1210
#define	TDX_ID_FUNC_ANS_FSGFCX				1211

#define	TDX_ID_FUNC_REQ_ZQFSXXCX			1212	// ֤ȯ������Ϣ��ѯ 1212
#define	TDX_ID_FUNC_ANS_ZQFSXXCX			1213

#define	TDX_ID_FUNC_REQ_BJZRCDCX			1214	// ����ת�ó�����ѯ 1214
#define	TDX_ID_FUNC_ANS_BJZRCDCX			1215

#define	TDX_ID_FUNC_REQ_BJZRWTCX			1216	// ����ת��ί�в�ѯ 1216
#define	TDX_ID_FUNC_ANS_BJZRWTCX			1217

#define	TDX_ID_FUNC_REQ_BJZRCJCX			1218	// ����ת�óɽ���ѯ 1218
#define	TDX_ID_FUNC_ANS_BJZRCJCX			1219

#define	TDX_ID_FUNC_REQ_DTGFCX				1220	// ��̬�ɷݲ�ѯ 1220
#define	TDX_ID_FUNC_ANS_DTGFCX				1221

#define	TDX_ID_FUNC_REQ_ZQZYKCX				1222	// ծȯ��Ѻ���ѯ 1222
#define	TDX_ID_FUNC_ANS_ZQZYKCX				1223

#define	TDX_ID_FUNC_REQ_DCGZJMXCX			1224	// �����ʽ���ϸ��ѯ 1224
#define	TDX_ID_FUNC_ANS_DCGZJMXCX			1225

#define	TDX_ID_FUNC_REQ_LSCCCX				1226	// ��ʷ�ֲֲ�ѯ 1226
#define	TDX_ID_FUNC_ANS_LSCCCX				1227

#define	TDX_ID_FUNC_REQ_GFMXCX				1228	// �ɷ���ϸ��ѯ 1228
#define	TDX_ID_FUNC_ANS_GFMXCX				1229

#define	TDX_ID_FUNC_REQ_GFCX_SECOND			1230	// �ɷݲ�ѯ(2nd��) 1230
#define	TDX_ID_FUNC_ANS_GFCX_SECOND			1231

#define	TDX_ID_FUNC_REQ_GFCX_THIRD			1232	// �ɷݲ�ѯ(3rd��) 1232
#define	TDX_ID_FUNC_ANS_GFCX_THIRD			1233

#define	TDX_ID_FUNC_REQ_ZQHGHYCX			1234	// ծȯ�ع���Լ��ѯ 1234
#define	TDX_ID_FUNC_ANS_ZQHGHYCX			1235

#define	TDX_ID_FUNC_REQ_KHDZXXCX			1236	// �ͻ�������Ϣ��ѯ 1236
#define	TDX_ID_FUNC_ANS_KHDZXXCX			1237

#define	TDX_ID_FUNC_REQ_ZHXYHQCX			1238	// �ۺ�Э�������ѯ 1238
#define	TDX_ID_FUNC_ANS_ZHXYHQCX			1239

#define	TDX_ID_FUNC_REQ_BZQHZCX				1240	// ��׼ȯ���ܲ�ѯ 1240
#define	TDX_ID_FUNC_ANS_BZQHZCX				1241

#define	TDX_ID_FUNC_REQ_GTZQHQCX			1242	// ��̨ծȯ�����ѯ 1242
#define	TDX_ID_FUNC_ANS_GTZQHQCX			1243

#define	TDX_ID_FUNC_REQ_RZXQHYCX			1244	// ������Ȩ��Լ��ѯ 1244
#define	TDX_ID_FUNC_ANS_RZXQHYCX			1245

#define	TDX_ID_FUNC_REQ_RZXQKHXXCX			1246	// ������Ȩ�ͻ���Ϣ��ѯ 1246
#define	TDX_ID_FUNC_ANS_RZXQKHXXCX			1247

#define	TDX_ID_FUNC_REQ_ZQHGLSCX			1248	// ծȯ�ع���ʷ��ѯ 1248
#define	TDX_ID_FUNC_ANS_ZQHGLSCX			1249

#define	TDX_ID_FUNC_REQ_QQDMCX				1250	// ��Ȩ�����ѯ 1250
#define	TDX_ID_FUNC_ANS_QQDMCX				1251

#define	TDX_ID_FUNC_REQ_QQCCCX				1252	// ��Ȩ�ֲֲ�ѯ 1252
#define	TDX_ID_FUNC_ANS_QQCCCX				1253

#define	TDX_ID_FUNC_REQ_QQSDSCX				1254	// ��Ȩ����˰��ѯ 1254
#define	TDX_ID_FUNC_ANS_QQSDSCX				1255

#define	TDX_ID_FUNC_REQ_QQDRWTCX			1256	// ��Ȩ����ί�в�ѯ 1256
#define	TDX_ID_FUNC_ANS_QQDRWTCX			1257

#define	TDX_ID_FUNC_REQ_QQLSWTCX			1258	// ��Ȩ��ʷί�в�ѯ 1258
#define	TDX_ID_FUNC_ANS_QQLSWTCX			1259


// �ڻ�������
#define TDX_ID_FUNC_REQ_QHWT				1500	// �ڻ�ί�� 1500
#define TDX_ID_FUNC_ANS_QHWT				1501

#define TDX_ID_FUNC_REQ_CXQHCC				1502	// ��ѯ�ڻ��ֲ� 1502
#define TDX_ID_FUNC_ANS_CXQHCC				1503

#define TDX_ID_FUNC_REQ_CXHYXX				1504	// ��ѯ�ڻ���Լ��Ϣ 1504
#define TDX_ID_FUNC_ANS_CXHYXX				1505

#define TDX_ID_FUNC_REQ_CXKJYHY				1506	// ��ѯ�ɽ��׺�Լ 1506
#define TDX_ID_FUNC_ANS_CXKJYHY				1507

#define TDX_ID_FUNC_REQ_DRZJLS				1508	// �����ʽ���ˮ 1508
#define TDX_ID_FUNC_ANS_DRZJLS				1509

#define	TDX_ID_FUNC_REQ_QHWTZTCX			1510	// �ڻ�ί��״̬��ѯ 1510
#define	TDX_ID_FUNC_ANS_QHWTZTCX			1511

#define	TDX_ID_FUNC_REQ_QHWTHB				1512	// �ڻ�ί�лر� 1512 [���͹���,����ʹ��]
#define	TDX_ID_FUNC_ANS_QHWTHB				1513	// �ڻ�ί�лر� 1513

#define	TDX_ID_FUNC_REQ_QHCDHB				1514	// �ڻ������ر� 1514 [���͹���,����ʹ��]
#define	TDX_ID_FUNC_ANS_QHCDHB				1515	// �ڻ������ر� 1515

#define	TDX_ID_FUNC_REQ_QHCJHB				1516	// �ڻ��ɽ��ر� 1516 [���͹���,����ʹ��]
#define	TDX_ID_FUNC_ANS_QHCJHB				1517	// �ڻ��ɽ��ر� 1517

#define	TDX_ID_FUNC_REQ_QHXXFB				1518	// �ڻ���Ϣ���� 1518 [���͹���,����ʹ��]
#define	TDX_ID_FUNC_ANS_QHXXFB				1519	// �ڻ���Ϣ���� 1519

#define	TDX_ID_FUNC_REQ_QHJYSZTGB			1520	// �ڻ�������״̬�ı� 1520 [���͹���,����ʹ��]
#define TDX_ID_FUNC_ANS_QHJYSZTGB			1521	// �ڻ�������״̬�ı� 1521

#define	TDX_ID_FUNC_REQ_QHZHHYBG			1522	// �ڻ���Ϻ�Լ��� 1522 [���͹���,����ʹ��]
#define TDX_ID_FUNC_ANS_QHZHHYBG			1523	// �ڻ���Ϻ�Լ��� 1523

#define	TDX_ID_FUNC_REQ_QHZHWTHB			1524	// �ڻ����ί�лر� 1524 [���͹���,����ʹ��]
#define TDX_ID_FUNC_ANS_QHZHWTHB			1525	// �ڻ����ί�лر� 1525

#define	TDX_ID_FUNC_REQ_QHZHCDHB			1526	// �ڻ���ϳ����ر� 1526 [���͹���,����ʹ��]
#define TDX_ID_FUNC_ANS_QHZHCDHB			1527	// �ڻ���ϳ����ر� 1527

#define	TDX_ID_FUNC_REQ_QHDDLXCX			1528	// �ڻ��������Ͳ�ѯ 1528
#define	TDX_ID_FUNC_ANS_QHDDLXCX			1529

#define	TDX_ID_FUNC_REQ_QHZHWT				1530	// �ڻ����ί�� 1530
#define	TDX_ID_FUNC_ANS_QHZHWT				1531

#define	TDX_ID_FUNC_REQ_QHZHCD				1532	// �ڻ���ϳ��� 1532
#define	TDX_ID_FUNC_ANS_QHZHCD				1533

#define	TDX_ID_FUNC_REQ_QHZHHYCX			1534	// �ڻ���Ϻ�Լ��ѯ 1534
#define	TDX_ID_FUNC_ANS_QHZHHYCX			1535

#define	TDX_ID_FUNC_REQ_QHZHCCCX			1536	// �ڻ���ϳֲֲ�ѯ 1536
#define	TDX_ID_FUNC_ANS_QHZHCCCX			1537

#define	TDX_ID_FUNC_REQ_QHZHWTCX			1538	// �ڻ����ί�в�ѯ 1538
#define	TDX_ID_FUNC_ANS_QHZHWTCX			1539

#define	TDX_ID_FUNC_REQ_QHZHJSKWTS			1540	// �ڻ���ϼ����ί���� 1540
#define	TDX_ID_FUNC_ANS_QHZHJSKWTS			1541

#define	TDX_ID_FUNC_REQ_QHZHCLCX			1542	// �ڻ���ϲ��Բ�ѯ 1542
#define	TDX_ID_FUNC_ANS_QHZHCLCX			1543

// �ع���
#define TDX_ID_FUNC_REQ_GPZYHG				1800	// ��Ʊ��Ѻ�ع� 1800
#define TDX_ID_FUNC_ANS_GPZYHG				1801

#define TDX_ID_FUNC_REQ_GPZYHG_SQCX			1802	// ��Ʊ��Ѻ�ع������ѯ 1802
#define TDX_ID_FUNC_ANS_GPZYHG_SQCX			1803

#define TDX_ID_FUNC_REQ_GPZYHG_HTCX			1804	// ��Ʊ��Ѻ�ع���ͬ��ѯ 1804
#define TDX_ID_FUNC_ANS_GPZYHG_HTCX			1805

#define TDX_ID_FUNC_REQ_GPZYHG_QYCX			1806	// ��Ʊ��Ѻ�ع�Ȩ���ѯ 1806
#define TDX_ID_FUNC_ANS_GPZYHG_QYCX			1807

#define TDX_ID_FUNC_REQ_GPZYHG_QXLLCX		1808	// ��Ʊ��Ѻ�ع��������ʲ�ѯ 1808
#define TDX_ID_FUNC_ANS_GPZYHG_QXLLCX		1809

#define TDX_ID_FUNC_REQ_GPZYHG_LSCX			1810	// ��Ʊ��Ѻ�ع���ˮ��ѯ 1810
#define TDX_ID_FUNC_ANS_GPZYHG_LSCX			1811

#define TDX_ID_FUNC_REQ_GPZYHG_RCFCX		1812	// ��Ʊ��Ѻ�ع��ڳ�����ѯ 1812
#define TDX_ID_FUNC_ANS_GPZYHG_RCFCX		1813

#define TDX_ID_FUNC_REQ_GPZYHG_LXCX			1814	// ��Ʊ��Ѻ�ع���Ϣ��ѯ 1814
#define TDX_ID_FUNC_ANS_GPZYHG_LXCX			1815

#define TDX_ID_FUNC_REQ_GPZYHG_LSHTCX		1816	// ��Ʊ��Ѻ�ع���ʷ��ͬ��ѯ 1816
#define TDX_ID_FUNC_ANS_GPZYHG_LSHTCX		1817

#define TDX_ID_FUNC_REQ_GPZYHG_BDZQCX		1818	// ��Ʊ��Ѻ�ع����֤ȯ��ѯ 1818
#define TDX_ID_FUNC_ANS_GPZYHG_BDZQCX		1819

#define TDX_ID_FUNC_REQ_TSHG				1830	// ��ɫ�ع� 1830
#define TDX_ID_FUNC_ANS_TSHG				1831

#define TDX_ID_FUNC_REQ_TSHG_XXCX			1832	// ��ɫ�ع���Ϣ��ѯ 1832
#define TDX_ID_FUNC_ANS_TSHG_XXCX			1833

#define TDX_ID_FUNC_REQ_TSHG_SQCX			1834	// ��ɫ�ع������ѯ 1834
#define TDX_ID_FUNC_ANS_TSHG_SQCX			1835

#define TDX_ID_FUNC_REQ_TSHG_DMCX			1836	// ��ɫ�ع������ѯ 1836
#define TDX_ID_FUNC_ANS_TSHG_DMCX			1837

#define TDX_ID_FUNC_REQ_TSHG_YZT			1838	// ��ɫ�ع���֤ͨ 1838
#define TDX_ID_FUNC_ANS_TSHG_YZT			1839

#define TDX_ID_FUNC_REQ_TSHG_ZZJHCX			1840	// ��ɫ�ع�ת�˼ƻ���ѯ 1840
#define TDX_ID_FUNC_ANS_TSHG_ZZJHCX			1841

#define TDX_ID_FUNC_REQ_TSHG_LSCX			1842	// ��ɫ�ع���ˮ��ѯ 1842
#define TDX_ID_FUNC_ANS_TSHG_LSCX			1843


#define TDX_ID_FUNC_REQ_PSZTSZ				2000	// ����״̬����(��ѯ) 2000
#define TDX_ID_FUNC_ANS_PSZTSZ				2001

#define TDX_ID_FUNC_REQ_HZHG				2002	// �����ع� 2002
#define TDX_ID_FUNC_ANS_HZHG				2003

#define TDX_ID_FUNC_REQ_HZHGZT				2004	// �����ع�״̬(��ѯ) 2004
#define TDX_ID_FUNC_ANS_HZHGZT				2005

#define TDX_ID_FUNC_REQ_HZSGZT				2006	// �����깺״̬(��ѯ) 2006
#define TDX_ID_FUNC_ANS_HZSGZT				2007

#define TDX_ID_FUNC_REQ_HZHGCPDMCX			2008	// �����ع���Ʒ�����ѯ 2008
#define TDX_ID_FUNC_ANS_HZHGCPDMCX			2009

#define TDX_ID_FUNC_REQ_HZHGCPXXCX			2010	// �����ع���Ʒ��Ϣ��ѯ 2010
#define TDX_ID_FUNC_ANS_HZHGCPXXCX			2011

#define TDX_ID_FUNC_REQ_HZHGTQZZCX			2012	// �����ع���ǰ��ֹ��ѯ 2012
#define TDX_ID_FUNC_ANS_HZHGTQZZCX			2013

#define TDX_ID_FUNC_REQ_HZHGDRWTCX			2014	// �����ع�����ί�в�ѯ 2014
#define TDX_ID_FUNC_ANS_HZHGDRWTCX			2015

#define TDX_ID_FUNC_REQ_HZHGDRCJCX			2016	// �����ع����ճɽ���ѯ 2016
#define TDX_ID_FUNC_ANS_HZHGDRCJCX			2017

#define TDX_ID_FUNC_REQ_HZHGLSWTCX			2018	// �����ع���ʷί�в�ѯ 2018
#define TDX_ID_FUNC_ANS_HZHGLSWTCX			2019

#define TDX_ID_FUNC_REQ_HZHGLSCJCX			2020	// �����ع���ʷ�ɽ���ѯ 2020
#define TDX_ID_FUNC_ANS_HZHGLSCJCX			2021

#define TDX_ID_FUNC_REQ_HZHGQNHYCX			2022	// �����ع����ں�Լ��ѯ 2022
#define TDX_ID_FUNC_ANS_HZHGQNHYCX			2023

#define TDX_ID_FUNC_REQ_HZHGCDCX			2024	// �����ع�������ѯ 2024
#define TDX_ID_FUNC_ANS_HZHGCDCX			2025

#define TDX_ID_FUNC_REQ_HZHGXYCX			2026	// �����ع���Լ��ѯ 2026
#define TDX_ID_FUNC_ANS_HZHGXYCX			2027

#define TDX_ID_FUNC_REQ_HZHGXYZZCX			2028	// �����ع���Լ��ֹ��ѯ 2028
#define TDX_ID_FUNC_ANS_HZHGXYZZCX			2029

#define TDX_ID_FUNC_REQ_HZHGTQZZYYCX		2030	// �����ع���ǰ��ֹԤԼ��ѯ 2030
#define TDX_ID_FUNC_ANS_HZHGTQZZYYCX		2031

#define TDX_ID_FUNC_REQ_HZHGTQZZYYCXCX		2032	// �����ع���ǰ��ֹԤԼ������ѯ 2032
#define TDX_ID_FUNC_ANS_HZHGTQZZYYCXCX		2033

#define TDX_ID_FUNC_REQ_HZHGDYZYWCX			2034	// �����ع���Ӧ��Ѻ���ѯ 2034
#define TDX_ID_FUNC_ANS_HZHGDYZYWCX			2035

#define TDX_ID_FUNC_REQ_HZHGXYCDCX			2036	// �����ع���Լ������ѯ 2036
#define TDX_ID_FUNC_ANS_HZHGXYCDCX			2037

#define TDX_ID_FUNC_REQ_HZHGDRDQCX			2038	// �����ع����յ��ڲ�ѯ 2038
#define TDX_ID_FUNC_ANS_HZHGDRDQCX			2039

#define TDX_ID_FUNC_REQ_HZHGLSDQCX			2040	// �����ع���ʷ���ڲ�ѯ 2040
#define TDX_ID_FUNC_ANS_HZHGLSDQCX			2041

#define TDX_ID_FUNC_REQ_HZHGXZZZYYCX		2042	// �����ع�������ֹԤԼ��ѯ 2042
#define TDX_ID_FUNC_ANS_HZHGXZZZYYCX		2043

#define TDX_ID_FUNC_REQ_HZHGXZZZYYCXCX		2044	// �����ع�������ֹԤԼ������ѯ 2044
#define TDX_ID_FUNC_ANS_HZHGXZZZYYCXCX		2045

#define TDX_ID_FUNC_REQ_HZHGXYBGCX			2046	// �����ع���Լ�����ѯ 2046
#define TDX_ID_FUNC_ANS_HZHGXYBGCX			2047

#define TDX_ID_FUNC_REQ_HZHGHYSYCX			2048	// �����ع���Լ�����ѯ 2048
#define TDX_ID_FUNC_ANS_HZHGHYSYCX			2049

#define TDX_ID_FUNC_REQ_SZBJHGCPDMCX		2050	// ���ڱ��ۻع���Ʒ�����ѯ 2050
#define TDX_ID_FUNC_ANS_SZBJHGCPDMCX		2051

#define TDX_ID_FUNC_REQ_SZBJHGQNHYCX		2052	// ���ڱ��ۻع����ں�Լ��ѯ 2052
#define TDX_ID_FUNC_ANS_SZBJHGQNHYCX		2053

#define TDX_ID_FUNC_REQ_HZHGXYSZPTCX		2054	// �����ع�Э���������ײ�ѯ 2054
#define TDX_ID_FUNC_ANS_HZHGXYSZPTCX		2055

#define TDX_ID_FUNC_REQ_YDHGCSJYPTCX		2070	// Լ���ع���ʼ�������ײ�ѯ 2070
#define TDX_ID_FUNC_ANS_YDHGCSJYPTCX		2071

#define TDX_ID_FUNC_REQ_YDHGLYBZPTCX		2072	// Լ���ع���Լ�������ײ�ѯ 2072
#define TDX_ID_FUNC_ANS_YDHGLYBZPTCX		2073

#define TDX_ID_FUNC_REQ_YDHGTQGHPTCX		2074	// Լ���ع���ǰ�������ײ�ѯ 2074
#define TDX_ID_FUNC_ANS_YDHGTQGHPTCX		2075

#define TDX_ID_FUNC_REQ_YDHGYQSQPTCX		2076	// Լ���ع������������ײ�ѯ 2076
#define TDX_ID_FUNC_ANS_YDHGYQSQPTCX		2077

#define TDX_ID_FUNC_REQ_YDHGJYCDPTCX		2078	// Լ���ع����׳������ײ�ѯ 2078
#define TDX_ID_FUNC_ANS_YDHGJYCDPTCX		2079

#define TDX_ID_FUNC_REQ_YDHGDQHYCX			2080	// Լ���ع���ǰ��Լ��ѯ 2080
#define TDX_ID_FUNC_ANS_YDHGDQHYCX			2081

#define TDX_ID_FUNC_REQ_YDHGLSHYCX			2082	// Լ���ع���ʷ��Լ��ѯ 2082
#define TDX_ID_FUNC_ANS_YDHGLSHYCX			2083

#define TDX_ID_FUNC_REQ_YDHGJXHYCX			2084	// Լ���ع����к�Լ��ѯ 2084
#define TDX_ID_FUNC_ANS_YDHGJXHYCX			2085

#define TDX_ID_FUNC_REQ_YDHGZZHYCX			2086	// Լ���ع���ֹ��Լ��ѯ 2086
#define TDX_ID_FUNC_ANS_YDHGZZHYCX			2087

#define TDX_ID_FUNC_REQ_YDHGBDZQCX			2088	// Լ���ع����֤ȯ��ѯ 2088
#define TDX_ID_FUNC_ANS_YDHGBDZQCX			2089

#define TDX_ID_FUNC_REQ_YDHGCPXXCX			2090	// Լ���ع���Ʒ��Ϣ��ѯ 2090
#define TDX_ID_FUNC_ANS_YDHGCPXXCX			2091

#define TDX_ID_FUNC_REQ_YDHGZHXXCX			2092	// Լ���ع��ۺ���Ϣ��ѯ 2092
#define TDX_ID_FUNC_ANS_YDHGZHXXCX			2093

#define TDX_ID_FUNC_REQ_YDHGYWCZ			2098	// Լ���ع�ҵ�����(��Ϣ��ѯ) 2098
#define TDX_ID_FUNC_ANS_YDHGYWCZ			2099

// ����ʽ������
#define TDX_ID_FUNC_REQ_KFSJJWT				2100	// ����ʽ����ί�� 2100
#define TDX_ID_FUNC_ANS_KFSJJWT				2101

#define TDX_ID_FUNC_REQ_KFSJJWTCD			2102	// ����ί�г��� 2102
#define TDX_ID_FUNC_ANS_KFSJJWTCD			2103

#define TDX_ID_FUNC_REQ_KFSJJZH				2104	// ת�� 2104
#define TDX_ID_FUNC_ANS_KFSJJZH				2105

#define TDX_ID_FUNC_REQ_KFSJJFECX			2106	// �ݶ��ѯ 2106
#define TDX_ID_FUNC_ANS_KFSJJFECX			2107

#define TDX_ID_FUNC_REQ_KFSJJWTCX			2108	// ����ί�в�ѯ 2108
#define TDX_ID_FUNC_ANS_KFSJJWTCX			2109

#define TDX_ID_FUNC_REQ_KFSJJXXCX			2110	// ���������Ϣ��ѯ 2110
#define TDX_ID_FUNC_ANS_KFSJJXXCX			2111

#define TDX_ID_FUNC_REQ_KFSJJCJCX			2112	// �ɽ���ѯ 2112
#define TDX_ID_FUNC_ANS_KFSJJCJCX			2113

#define TDX_ID_FUNC_REQ_KFSJJFH				2114	// ����ֺ� 2114
#define TDX_ID_FUNC_ANS_KFSJJFH				2115

#define TDX_ID_FUNC_REQ_KFSJJDMCX			2116	// �������� 2116
#define TDX_ID_FUNC_ANS_KFSJJDMCX			2117

#define TDX_ID_FUNC_REQ_KFSJJZJZHKH			2118	// �����ʽ��ʺſ��� 2118
#define TDX_ID_FUNC_ANS_KFSJJZJZHKH			2119

#define TDX_ID_FUNC_REQ_KFSJJZJZHZC			2120	// �����ʽ��ʺ�ע�� 2120
#define TDX_ID_FUNC_ANS_KFSJJZJZHZC			2121

#define TDX_ID_FUNC_REQ_KFSJJKHZLXG			2122	// �ͻ������޸� 2122
#define TDX_ID_FUNC_ANS_KFSJJKHZLXG			2123

#define TDX_ID_FUNC_REQ_KFSJJCXGSDM			2124	// ��ѯ����˾���� 2124
#define TDX_ID_FUNC_ANS_KFSJJCXGSDM			2125

#define TDX_ID_FUNC_REQ_KFSJJZHCX			2126	// ��ѯ�����ʺ� 2126
#define TDX_ID_FUNC_ANS_KFSJJZHCX			2127

#define TDX_ID_FUNC_REQ_KFSJJLSWTCX			2128	// ������ʷί�в�ѯ 2128
#define TDX_ID_FUNC_ANS_KFSJJLSWTCX			2129

#define TDX_ID_FUNC_REQ_KFSJJDSDESGSZ		2130	// ��ʱ�����깺���� 2130
#define TDX_ID_FUNC_ANS_KFSJJDSDESGSZ		2131 

#define TDX_ID_FUNC_REQ_KFSJJDSDESGQX		2132	// ��ʱ�����깺ȡ�� 2132
#define TDX_ID_FUNC_ANS_KFSJJDSDESGQX		2133 

#define TDX_ID_FUNC_REQ_KFSJJCXDQDESGPZ		2134	// ��ѯ���ڶ����깺Ʒ�� 2134
#define TDX_ID_FUNC_ANS_KFSJJCXDQDESGPZ		2135 

#define TDX_ID_FUNC_REQ_KFSJJDRWTCX			2136	// ����ʽ������ί�в�ѯ 2136
#define TDX_ID_FUNC_ANS_KFSJJDRWTCX			2137
	
#define TDX_ID_FUNC_REQ_KFSJJFHCX			2138	// ����ֺ��ѯ 2138
#define TDX_ID_FUNC_ANS_KFSJJFHCX			2139

#define TDX_ID_FUNC_REQ_LOFJJFHCX			2140	// LOF����ֺ��ѯ 2140
#define TDX_ID_FUNC_ANS_LOFJJFHCX			2141

#define TDX_ID_FUNC_REQ_LOFJJFH				2142	// LOF����ֺ����� 2142
#define TDX_ID_FUNC_ANS_LOFJJFH				2143

#define TDX_ID_FUNC_REQ_KFSJJFXXXCX			2144	// ����ʽ������������Ϣ��ѯ 2144
#define TDX_ID_FUNC_ANS_KFSJJFXXXCX			2145

#define TDX_ID_FUNC_REQ_KFSJJZZKH			2146	// ����ת�ʿ��� 2146
#define TDX_ID_FUNC_ANS_KFSJJZZKH			2147

#define TDX_ID_FUNC_REQ_KFSJJJYKH			2148	// �����׿��� 2148
#define TDX_ID_FUNC_ANS_KFSJJJYKH			2149

#define TDX_ID_FUNC_REQ_KFSJJDRCJCX			2150	// �����ճɽ���ѯ 2150
#define TDX_ID_FUNC_ANS_KFSJJDRCJCX			2151

#define TDX_ID_FUNC_REQ_KFSJJLSCJCX			2152	// ������ʷ�ɽ���ѯ 2152
#define TDX_ID_FUNC_ANS_KFSJJLSCJCX			2153

#define TDX_ID_FUNC_REQ_KFSJJJZCX			2154	// ����ֵ��ѯ 2154
#define TDX_ID_FUNC_ANS_KFSJJJZCX			2155

#define TDX_ID_FUNC_REQ_KFSJJXYCXKT			2156	// ����Э���ѯ��ͨ 2156
#define TDX_ID_FUNC_ANS_KFSJJXYCXKT			2157

#define TDX_ID_FUNC_REQ_KFSJJFHMXCX			2158	// ����ֺ���ϸ��ѯ 2158
#define TDX_ID_FUNC_ANS_KFSJJFHMXCX			2159

#define TDX_ID_FUNC_REQ_DQDESZCX			2160	// ���ڶ����깺���ò�ѯ 2160
#define TDX_ID_FUNC_ANS_DQDESZCX			2161

#define TDX_ID_FUNC_REQ_KFSJJFJYWTCX		2162	// ����ʽ����ǽ���ί�в�ѯ 2162
#define TDX_ID_FUNC_ANS_KFSJJFJYWTCX		2163

#define TDX_ID_FUNC_REQ_KFSJJFJYDRWTCX		2164	// ����ʽ����ǽ��׵���ί�в�ѯ 2164
#define TDX_ID_FUNC_ANS_KFSJJFJYDRWTCX		2165

#define TDX_ID_FUNC_REQ_KFSJJFXKCSDMCX		2166	// ����ʽ������տɳ��ܴ����ѯ 2166
#define TDX_ID_FUNC_ANS_KFSJJFXKCSDMCX		2167

#define TDX_ID_FUNC_REQ_KFSJJFLCX			2168	// ����ʽ������ʲ�ѯ 2168
#define TDX_ID_FUNC_ANS_KFSJJFLCX			2169

#define TDX_ID_FUNC_REQ_KFSJJDQDESHSZ		2170	// ����ʽ�����ڶ���������� 2170
#define TDX_ID_FUNC_ANS_KFSJJDQDESHSZ		2171

#define TDX_ID_FUNC_REQ_KFSJJDQDESHQX		2172	// ����ʽ�����ڶ������ȡ�� 2172
#define TDX_ID_FUNC_ANS_KFSJJDQDESHQX		2173

#define TDX_ID_FUNC_REQ_KFSJJDQDESHCX		2174	// ����ʽ�����ڶ�����ز�ѯ 2174
#define TDX_ID_FUNC_ANS_KFSJJDQDESHCX		2175

#define TDX_ID_FUNC_REQ_KFSJJDQDESHPZ		2176	// ����ʽ�����ڶ������Ʒ�� 2176
#define TDX_ID_FUNC_ANS_KFSJJDQDESHPZ		2177

#define TDX_ID_FUNC_REQ_KFSJJDMXGXXCX		2178	// ����ʽ������������Ϣ��ѯ 2178
#define TDX_ID_FUNC_ANS_KFSJJDMXGXXCX		2179

#define TDX_ID_FUNC_REQ_KFSJJGSXGXXCX		2180	// ����ʽ����˾�����Ϣ��ѯ 2180
#define TDX_ID_FUNC_ANS_KFSJJGSXGXXCX		2181

#define TDX_ID_FUNC_REQ_KFSJJDZDCX			2182	// ����ʽ������˵���ѯ 2182
#define TDX_ID_FUNC_ANS_KFSJJDZDCX			2183

#define TDX_ID_FUNC_REQ_KFSJJJGDCX			2184	// ����ʽ���𽻸��ѯ 2184
#define TDX_ID_FUNC_ANS_KFSJJJGDCX			2185

// ��Ʋ�Ʒ
#define	TDX_ID_FUNC_REQ_LCCPFECX			2200	// ��Ʋ�Ʒ�ݶ��ѯ 2200
#define	TDX_ID_FUNC_ANS_LCCPFECX			2201

#define	TDX_ID_FUNC_REQ_LCCPWTCX			2202	// ��Ʋ�Ʒί�в�ѯ 2202
#define	TDX_ID_FUNC_ANS_LCCPWTCX			2203

#define	TDX_ID_FUNC_REQ_LCCPCJCX			2204	// ��Ʋ�Ʒ�ɽ���ѯ 2204
#define	TDX_ID_FUNC_ANS_LCCPCJCX			2205

#define	TDX_ID_FUNC_REQ_LCCPDRWTCX			2206	// ��Ʋ�Ʒ����ί�в�ѯ 2206
#define	TDX_ID_FUNC_ANS_LCCPDRWTCX			2207

#define	TDX_ID_FUNC_REQ_LCCPDMCX			2208	// ��Ʋ�Ʒ�����ѯ 2208
#define	TDX_ID_FUNC_ANS_LCCPDMCX			2209

#define	TDX_ID_FUNC_REQ_LCCPZHCX			2210	// ��Ʋ�Ʒ�ʺŲ�ѯ 2210
#define	TDX_ID_FUNC_ANS_LCCPZHCX			2211

#define	TDX_ID_FUNC_REQ_LCCPDQDESGCX		2212	// ��Ʋ�Ʒ���ڶ����깺��ѯ 2212
#define	TDX_ID_FUNC_ANS_LCCPDQDESGCX		2213

#define	TDX_ID_FUNC_REQ_LCCPDQDESGPZ		2214	// ��Ʋ�Ʒ���ڶ����깺Ʒ�� 2214
#define	TDX_ID_FUNC_ANS_LCCPDQDESGPZ		2215

#define	TDX_ID_FUNC_REQ_LCCPZZJHLBCX		2216	// ��Ʋ�Ʒ��ֵ�ƻ��б��ѯ 2216
#define	TDX_ID_FUNC_ANS_LCCPZZJHLBCX		2217

#define	TDX_ID_FUNC_REQ_LCCPZZJHXXCX		2218	// ��Ʋ�Ʒ��ֵ�ƻ���Ϣ��ѯ 2218
#define	TDX_ID_FUNC_ANS_LCCPZZJHXXCX		2219

#define	TDX_ID_FUNC_REQ_LCCPZZJHJESZ		2220	// ��Ʋ�Ʒ��ֵ�ƻ�������� 2220
#define	TDX_ID_FUNC_ANS_LCCPZZJHJESZ		2221

#define	TDX_ID_FUNC_REQ_LCCPZZJHZTSZ		2222	// ��Ʋ�Ʒ��ֵ�ƻ�״̬���� 2222
#define	TDX_ID_FUNC_ANS_LCCPZZJHZTSZ		2223

#define	TDX_ID_FUNC_REQ_LCCPZZJHJCXY		2224	// ��Ʋ�Ʒ��ֵ�ƻ����Э�� 2224
#define	TDX_ID_FUNC_ANS_LCCPZZJHJCXY		2225

#define	TDX_ID_FUNC_REQ_LCCPZZJHFECX		2226	// ��Ʋ�Ʒ��ֵ�ƻ��ݶ��ѯ 2226
#define	TDX_ID_FUNC_ANS_LCCPZZJHFECX		2227

#define	TDX_ID_FUNC_REQ_LCCPZZJHCDCX		2228	// ��Ʋ�Ʒ��ֵ�ƻ�������ѯ 2228
#define	TDX_ID_FUNC_ANS_LCCPZZJHCDCX		2229

#define	TDX_ID_FUNC_REQ_LCCPZZJHXXXG		2230	// ��Ʋ�Ʒ��ֵ�ƻ���Ϣ�޸� 2230
#define	TDX_ID_FUNC_ANS_LCCPZZJHXXXG		2231

#define	TDX_ID_FUNC_REQ_LCCPZZJHFESH		2232	// ��Ʋ�Ʒ��ֵ�ƻ��ݶ���� 2232
#define	TDX_ID_FUNC_ANS_LCCPZZJHFESH		2233

#define	TDX_ID_FUNC_REQ_LCCPZZJHWTCD		2234	// ��Ʋ�Ʒ��ֵ�ƻ�ί�г��� 2234
#define	TDX_ID_FUNC_ANS_LCCPZZJHWTCD		2235

#define	TDX_ID_FUNC_REQ_LCCPZZJHYYQKCZ		2236	// ��Ʋ�Ʒ��ֵ�ƻ�ԤԼȡ����� 2236
#define	TDX_ID_FUNC_ANS_LCCPZZJHYYQKCZ		2237

#define	TDX_ID_FUNC_REQ_LCCPZZJHYYQKCX		2238	// ��Ʋ�Ʒ��ֵ�ƻ�ԤԼȡ���ѯ 2238
#define	TDX_ID_FUNC_ANS_LCCPZZJHYYQKCX		2239

#define	TDX_ID_FUNC_REQ_LCCPZZJHLSSYCX		2240	// ��Ʋ�Ʒ��ֵ�ƻ���ʷ�����ѯ 2240
#define	TDX_ID_FUNC_ANS_LCCPZZJHLSSYCX		2241

#define	TDX_ID_FUNC_REQ_DQLCCPSHXXCX		2242	// ������Ʋ�Ʒ�����Ϣ��ѯ 2242
#define	TDX_ID_FUNC_ANS_DQLCCPSHXXCX		2243

#define	TDX_ID_FUNC_REQ_LCCPZRDMCX			2244	// ��Ʋ�Ʒת�ô����ѯ 2244
#define	TDX_ID_FUNC_ANS_LCCPZRDMCX			2245

#define	TDX_ID_FUNC_REQ_LCCPZRHQCX			2246	// ��Ʋ�Ʒת�������ѯ 2246
#define	TDX_ID_FUNC_ANS_LCCPZRHQCX			2247

#define	TDX_ID_FUNC_REQ_LCCPZRCDCX			2248	// ��Ʋ�Ʒת�ó�����ѯ 2248
#define	TDX_ID_FUNC_ANS_LCCPZRCDCX			2249

#define	TDX_ID_FUNC_REQ_LCCPZRWTCX			2250	// ��Ʋ�Ʒת��ί�в�ѯ 2250
#define	TDX_ID_FUNC_ANS_LCCPZRWTCX			2251

#define	TDX_ID_FUNC_REQ_LCCPZRCJCX			2252	// ��Ʋ�Ʒת�óɽ���ѯ 2252
#define	TDX_ID_FUNC_ANS_LCCPZRCJCX			2253

#define TDX_ID_FUNC_REQ_LCCPQYJYCX			2254	// ��Ʋ�ƷǩԼ��Լ��ѯ 2254
#define TDX_ID_FUNC_ANS_LCCPQYJYCX			2255

#define	TDX_ID_FUNC_REQ_YHLCCPDMCX			2256	// ������Ʋ�Ʒ�����ѯ 2256
#define	TDX_ID_FUNC_ANS_YHLCCPDMCX			2257

#define	TDX_ID_FUNC_REQ_YHLCCPFECX			2258	// ������Ʋ�Ʒ�ݶ��ѯ 2258
#define	TDX_ID_FUNC_ANS_YHLCCPFECX			2259

#define	TDX_ID_FUNC_REQ_YHLCCPWTCX			2260	// ������Ʋ�Ʒί�в�ѯ 2260
#define	TDX_ID_FUNC_ANS_YHLCCPWTCX			2261

#define	TDX_ID_FUNC_REQ_YHLCCPZHCX			2262	// ������Ʋ�Ʒ�ʺŲ�ѯ 2262
#define	TDX_ID_FUNC_ANS_YHLCCPZHCX			2263

#define	TDX_ID_FUNC_REQ_YHLCCPCJCX			2264	// ������Ʋ�Ʒ�ɽ���ѯ 2264
#define	TDX_ID_FUNC_ANS_YHLCCPCJCX			2265

#define	TDX_ID_FUNC_REQ_OTCFECX				2266	// OTC�ݶ��ѯ 2266
#define	TDX_ID_FUNC_ANS_OTCFECX				2267

#define	TDX_ID_FUNC_REQ_OTCRSSCX			2268	// OTC�������ѯ 2268
#define	TDX_ID_FUNC_ANS_OTCRSSCX			2269

#define	TDX_ID_FUNC_REQ_OTCYXSBCX			2270	// OTC�����걨��ѯ 2270
#define	TDX_ID_FUNC_ANS_OTCYXSBCX			2271

#define	TDX_ID_FUNC_REQ_OTCCJSBCX			2272	// OTC�ɽ��걨��ѯ 2272
#define	TDX_ID_FUNC_ANS_OTCCJSBCX			2273

#define	TDX_ID_FUNC_REQ_OTCCPHYCX			2274	// OTC��Ʒ��Լ��ѯ 2274
#define	TDX_ID_FUNC_ANS_OTCCPHYCX			2275

#define	TDX_ID_FUNC_REQ_OTCBJXXCX			2276	// OTC������Ϣ��ѯ 2276
#define	TDX_ID_FUNC_ANS_OTCBJXXCX			2277

#define	TDX_ID_FUNC_REQ_OTCHQXXCX			2278	// OTC������Ϣ��ѯ 2278
#define	TDX_ID_FUNC_ANS_OTCHQXXCX			2279

#define	TDX_ID_FUNC_REQ_OTCDZHTLBCX			2280	// OTC���Ӻ�ͬ�б��ѯ 2280
#define	TDX_ID_FUNC_ANS_OTCDZHTLBCX			2281

#define	TDX_ID_FUNC_REQ_OTCDZHTCX			2282	// OTC���Ӻ�ͬ��ѯ 2282
#define	TDX_ID_FUNC_ANS_OTCDZHTCX			2283

#define	TDX_ID_FUNC_REQ_XTCPDMCX			2300	// ���в�Ʒ�����ѯ 2300
#define	TDX_ID_FUNC_ANS_XTCPDMCX			2301	

#define	TDX_ID_FUNC_REQ_XTCPFECX			2302	// ���в�Ʒ�ݶ��ѯ 2302
#define	TDX_ID_FUNC_ANS_XTCPFECX			2303	

#define	TDX_ID_FUNC_REQ_XTCPZHCX			2304	// ���в�Ʒ�ʺŲ�ѯ 2304
#define	TDX_ID_FUNC_ANS_XTCPZHCX			2305
	
#define	TDX_ID_FUNC_REQ_XTCPWTCX			2306	// ���в�Ʒί�в�ѯ 2306
#define	TDX_ID_FUNC_ANS_XTCPWTCX			2307

#define	TDX_ID_FUNC_REQ_XTCPCJCX			2308	// ���в�Ʒ�ɽ���ѯ 2308
#define	TDX_ID_FUNC_ANS_XTCPCJCX			2309
	
#define	TDX_ID_FUNC_REQ_XTCPLSWTCX			2310	// ���в�Ʒ��ʷί�в�ѯ 2310
#define	TDX_ID_FUNC_ANS_XTCPLSWTCX			2311	

// ����ֱ��
#define	TDX_ID_FUNC_REQ_JJZXRG				2500	// ����ֱ���Ϲ� 2500
#define	TDX_ID_FUNC_ANS_JJZXRG				2501	

#define	TDX_ID_FUNC_REQ_JJZXSG				2502	// ����ֱ���깺 2502
#define	TDX_ID_FUNC_ANS_JJZXSG				2503

#define	TDX_ID_FUNC_REQ_JJZXSH				2504	// ����ֱ����� 2504
#define	TDX_ID_FUNC_ANS_JJZXSH				2505	 

#define	TDX_ID_FUNC_REQ_JJZXFH				2506	// ����ֱ���ֺ� 2506
#define	TDX_ID_FUNC_ANS_JJZXFH				2507

#define	TDX_ID_FUNC_REQ_JJZXZH				2508	// ����ֱ��ת�� 2508
#define	TDX_ID_FUNC_ANS_JJZXZH				2509

#define	TDX_ID_FUNC_REQ_JJZXZTG				2510	// ����ֱ��ת�й� 2510
#define	TDX_ID_FUNC_ANS_JJZXZTG				2511

#define	TDX_ID_FUNC_REQ_JJZXCD				2512	// ����ֱ������ 2512
#define	TDX_ID_FUNC_ANS_JJZXCD				2513

#define	TDX_ID_FUNC_REQ_JJZXFLCX			2514	// ����ֱ�����ʲ�ѯ 2514
#define	TDX_ID_FUNC_ANS_JJZXFLCX			2515

#define	TDX_ID_FUNC_REQ_JJZXYHZF			2516	// ����ֱ������֧�� 2516
#define	TDX_ID_FUNC_ANS_JJZXYHZF			2517

#define	TDX_ID_FUNC_REQ_JJZXXSRDMCX			2518	// ����ֱ�������˴����ѯ 2518
#define	TDX_ID_FUNC_ANS_JJZXXSRDMCX			2519

#define	TDX_ID_FUNC_REQ_JJZXXXJC			2520	// ����ֱ����Ϣ��� 2520
#define	TDX_ID_FUNC_ANS_JJZXXXJC			2521

// ���ڻ���
#define	TDX_ID_FUNC_REQ_JYSCNJJDMCX			2850	// ���������ڻ�������ѯ 2850
#define	TDX_ID_FUNC_ANS_JYSCNJJDMCX			2851

#define	TDX_ID_FUNC_REQ_JYSCNJJCFGCX		2852	// ���������ڻ���ɷֹɲ�ѯ 2852
#define	TDX_ID_FUNC_ANS_JYSCNJJCFGCX		2853

// ETF
#define TDX_ID_FUNC_REQ_ETFSHKJSGPTCX		2950	// ETF�Ϻ��羳�깺���ײ�ѯ 2950
#define TDX_ID_FUNC_ANS_ETFSHKJSGPTCX		2951

#define TDX_ID_FUNC_REQ_ETFSZKJSGPTCX		2952	// ETF���ڿ羳�깺���ײ�ѯ 2952
#define TDX_ID_FUNC_ANS_ETFSZKJSGPTCX		2953

#define TDX_ID_FUNC_REQ_ETFSHKJSHPTCX		2954	// ETF�Ϻ��羳������ײ�ѯ 2954
#define TDX_ID_FUNC_ANS_ETFSHKJSHPTCX		2955

#define TDX_ID_FUNC_REQ_ETFSZKJSHPTCX		2956	// ETF���ڿ羳������ײ�ѯ 2956
#define TDX_ID_FUNC_ANS_ETFSZKJSHPTCX		2957

#define TDX_ID_FUNC_REQ_ETFSHKJWTCDCX		2958	// ETF�Ϻ��羳ί�г�����ѯ 2958
#define TDX_ID_FUNC_ANS_ETFSHKJWTCDCX		2959

#define TDX_ID_FUNC_REQ_ETFSZKJWTCDCX		2960	// ETF���ڿ羳ί�г�����ѯ 2960
#define TDX_ID_FUNC_ANS_ETFSZKJWTCDCX		2961

#define TDX_ID_FUNC_REQ_ETFSHKJDRWTCX		2962	// ETF�Ϻ��羳����ί�в�ѯ 2962
#define TDX_ID_FUNC_ANS_ETFSHKJDRWTCX		2963

#define TDX_ID_FUNC_REQ_ETFSZKJDRWTCX		2964	// ETF���ڿ羳����ί�в�ѯ 2964
#define TDX_ID_FUNC_ANS_ETFSZKJDRWTCX		2965

#define TDX_ID_FUNC_REQ_ETFSHKJDRCJCX		2966	// ETF�Ϻ��羳���ճɽ���ѯ 2966
#define TDX_ID_FUNC_ANS_ETFSHKJDRCJCX		2967

#define TDX_ID_FUNC_REQ_ETFSZKJDRCJCX		2968	// ETF���ڿ羳���ճɽ���ѯ 2968
#define TDX_ID_FUNC_ANS_ETFSZKJDRCJCX		2969

#define TDX_ID_FUNC_REQ_ETFSHKJLSWTCX		2970	// ETF�Ϻ��羳��ʷί�в�ѯ 2970
#define TDX_ID_FUNC_ANS_ETFSHKJLSWTCX		2971

#define TDX_ID_FUNC_REQ_ETFSZKJLSWTCX		2972	// ETF���ڿ羳��ʷί�в�ѯ 2972
#define TDX_ID_FUNC_ANS_ETFSZKJLSWTCX		2973

#define TDX_ID_FUNC_REQ_ETFSHKJLSCJCX		2974	// ETF�Ϻ��羳��ʷ�ɽ���ѯ 2974
#define TDX_ID_FUNC_ANS_ETFSHKJLSCJCX		2975

#define TDX_ID_FUNC_REQ_ETFSZKJLSCJCX		2976	// ETF���ڿ羳��ʷ�ɽ���ѯ 2976
#define TDX_ID_FUNC_ANS_ETFSZKJLSCJCX		2977

#define TDX_ID_FUNC_REQ_ETFWXXJRGPTCX		2980	// ETF�����ֽ��Ϲ����ײ�ѯ 2980
#define TDX_ID_FUNC_ANS_ETFWXXJRGPTCX		2981

#define TDX_ID_FUNC_REQ_ETFWXGFRGPTCX		2982	// ETF���¹ɷ��Ϲ����ײ�ѯ 2982
#define TDX_ID_FUNC_ANS_ETFWXGFRGPTCX		2983

#define TDX_ID_FUNC_REQ_ETFWXXJRGCDCX		2984	// ETF�����ֽ��Ϲ�������ѯ 2984
#define TDX_ID_FUNC_ANS_ETFWXXJRGCDCX		2985

#define TDX_ID_FUNC_REQ_ETFWXGFRGCDCX		2986	// ETF���¹ɷ��Ϲ�������ѯ 2986
#define TDX_ID_FUNC_ANS_ETFWXGFRGCDCX		2987

#define TDX_ID_FUNC_REQ_ETFWXXJRGXXCX		2988	// ETF�����ֽ��Ϲ���Ϣ��ѯ 2988
#define TDX_ID_FUNC_ANS_ETFWXXJRGXXCX		2989

#define TDX_ID_FUNC_REQ_ETFWXGFRGXXCX		2990	// ETF���¹ɷ��Ϲ���Ϣ��ѯ 2990
#define TDX_ID_FUNC_ANS_ETFWXGFRGXXCX		2991

#define TDX_ID_FUNC_REQ_ETFWXXJRGLSCX		2992	// ETF�����ֽ��Ϲ���ˮ��ѯ 2992
#define TDX_ID_FUNC_ANS_ETFWXXJRGLSCX		2993

#define TDX_ID_FUNC_REQ_ETFWXGFRGLSCX		2994	// ETF���¹ɷ��Ϲ���ˮ��ѯ 2994
#define TDX_ID_FUNC_ANS_ETFWXGFRGLSCX		2995

#define TDX_ID_FUNC_REQ_ETFMM				3000	// ETF���� 3000
#define TDX_ID_FUNC_ANS_ETFMM				3001

#define TDX_ID_FUNC_REQ_ETFXXCX				3002	// ETF��Ϣ��ѯ 3002
#define TDX_ID_FUNC_ANS_ETFXXCX				3003

#define TDX_ID_FUNC_REQ_ETFRGCX				3004	// ETF�Ϲ���ѯ 3004
#define TDX_ID_FUNC_ANS_ETFRGCX				3005

#define TDX_ID_FUNC_REQ_ETFRGCD				3006	// ETF�Ϲ����� 3006
#define TDX_ID_FUNC_ANS_ETFRGCD				3007

#define TDX_ID_FUNC_REQ_ETFPCH				3008	// ETFȡ���κ� 3008
#define TDX_ID_FUNC_ANS_ETFPCH				3009

#define TDX_ID_FUNC_REQ_ETFGPLMM			3010	// ETF��Ʊ������ 3010
#define TDX_ID_FUNC_ANS_ETFGPLMM			3011

#define TDX_ID_FUNC_REQ_ETFGPLCX			3012	// ETF��Ʊ����ѯ 3012
#define TDX_ID_FUNC_ANS_ETFGPLCX			3013

#define TDX_ID_FUNC_REQ_ETFYGCX				3014	// ETF��֤50ӵ�ɲ�ѯ 3014
#define TDX_ID_FUNC_ANS_ETFYGCX				3015

#define TDX_ID_FUNC_REQ_ETFWTCX				3016	// ETFί�в�ѯ 3016
#define TDX_ID_FUNC_ANS_ETFWTCX				3017

#define TDX_ID_FUNC_REQ_ETFCJCX				3018	// ETF�ɽ���ѯ 3018
#define TDX_ID_FUNC_ANS_ETFCJCX				3019
                                        	
#define TDX_ID_FUNC_REQ_ETFCLCX				3020	// ETF���Բ�ѯ 3020
#define TDX_ID_FUNC_ANS_ETFCLCX				3021    
                                        	
#define TDX_ID_FUNC_REQ_ETFZSDMCX			3022	// ETFָ�������ѯ 3022
#define TDX_ID_FUNC_ANS_ETFZSDMCX			3023
                                        	
#define TDX_ID_FUNC_REQ_ETFQR				3024	// ETF(ί��)ȷ�� 3024
#define TDX_ID_FUNC_ANS_ETFQR				3025
                                        	
#define TDX_ID_FUNC_REQ_ETFWTCXMX			3026	// ETFί�в�ѯ��ϸ 3026
#define TDX_ID_FUNC_ANS_ETFWTCXMX			3027

#define TDX_ID_FUNC_REQ_ETFRGCDCX			3028	// ETF�Ϲ�������ѯ 3028
#define TDX_ID_FUNC_ANS_ETFRGCDCX			3029

#define TDX_ID_FUNC_REQ_ETFZSCFCX			3030	// ETFָ���ɷֲ�ѯ 3030
#define TDX_ID_FUNC_ANS_ETFZSCFCX			3031

#define TDX_ID_FUNC_REQ_ETFGFCX				3032	// ETF�ɷݲ�ѯ 3032
#define TDX_ID_FUNC_ANS_ETFGFCX				3033

#define TDX_ID_FUNC_REQ_ETFKSGCFGCX			3034	// ETF���깺�ɷֹɲ�ѯ 3034
#define TDX_ID_FUNC_ANS_ETFKSGCFGCX			3035

#define TDX_ID_FUNC_REQ_ETFGPLCD			3036	// ETF��Ʊ������ 3036
#define TDX_ID_FUNC_ANS_ETFGPLCD			3037

#define TDX_ID_FUNC_REQ_ETFGPLCDCX			3038	// ETF��Ʊ��������ѯ 3038
#define TDX_ID_FUNC_ANS_ETFGPLCDCX			3039

#define TDX_ID_FUNC_REQ_ETFKSCDPCX			3040	// ETF���г����̲�ѯ 3040
#define TDX_ID_FUNC_ANS_ETFKSCDPCX			3041

// ���ͨҵ��
#define TDX_ID_FUNC_REQ_ZHTPCH				3050	// ���ͨ���κ� 3050
#define TDX_ID_FUNC_ANS_ZHTPCH				3051
                                        	
#define TDX_ID_FUNC_REQ_ZHTGPLMM			3052	// ���ͨ��Ʊ������ 3052
#define TDX_ID_FUNC_ANS_ZHTGPLMM			3053
                                        	
#define TDX_ID_FUNC_REQ_ZHTGPLCX			3054	// ���ͨ��Ʊ����ѯ 3054
#define TDX_ID_FUNC_ANS_ZHTGPLCX			3055
                                        	
#define TDX_ID_FUNC_REQ_ZHTYGCX				3056	// ���ͨӵ�ɲ�ѯ 3056
#define TDX_ID_FUNC_ANS_ZHTYGCX				3057
                                        	
#define TDX_ID_FUNC_REQ_ZHTWTCX				3058	// ���ͨί�в�ѯ 3058
#define TDX_ID_FUNC_ANS_ZHTWTCX				3059
                                        	
#define TDX_ID_FUNC_REQ_ZHTCJCX				3060	// ���ͨ�ɽ���ѯ 3060
#define TDX_ID_FUNC_ANS_ZHTCJCX				3061
                                        	
#define TDX_ID_FUNC_REQ_ZHTCLCX				3062	// ���ͨ���Բ�ѯ 3062
#define TDX_ID_FUNC_ANS_ZHTCLCX				3063    
                                        	
#define TDX_ID_FUNC_REQ_ZHTZSDMCX			3064	// ���ָͨ�������ѯ 3064
#define TDX_ID_FUNC_ANS_ZHTZSDMCX			3065
                                        	
#define TDX_ID_FUNC_REQ_ZHTQR				3066	// ���ͨȷ�� 3066
#define TDX_ID_FUNC_ANS_ZHTQR				3067
                                        	
#define TDX_ID_FUNC_REQ_ZHTLSCX				3068	// ���ͨ��ʷ��ѯ 3068
#define TDX_ID_FUNC_ANS_ZHTLSCX				3069
                                        	
#define TDX_ID_FUNC_REQ_ZHTLSCXMX			3070	// ���ͨ��ʷ��ѯ��ϸ 3070
#define TDX_ID_FUNC_ANS_ZHTLSCXMX			3071
                                        	
#define TDX_ID_FUNC_REQ_ZHTWTCXMX			3072	// ���ͨί�в�ѯ��ϸ 3072
#define TDX_ID_FUNC_ANS_ZHTWTCXMX			3073
                                        	
#define TDX_ID_FUNC_REQ_ZHTCJCXMX			3074	// ���ͨ�ɽ���ѯ��ϸ 3074
#define TDX_ID_FUNC_ANS_ZHTCJCXMX			3075

#define TDX_ID_FUNC_REQ_ZHTZSCFCX			3076	// ���ָͨ���ɷֲ�ѯ 3076
#define TDX_ID_FUNC_ANS_ZHTZSCFCX			3077

// ��������
#define TDX_ID_FUNC_REQ_TL_HQHHH			3100	// (����)��ȡ�Ự�� 3100
#define TDX_ID_FUNC_ANS_TL_HQHHH			3101

#define TDX_ID_FUNC_REQ_TL_ZHDMCX			3102	// (����)��ϴ����ѯ 3102
#define TDX_ID_FUNC_ANS_TL_ZHDMCX			3103

#define TDX_ID_FUNC_REQ_TL_ZHCFCX			3104	// (����)��ϳɷֲ�ѯ 3104
#define TDX_ID_FUNC_ANS_TL_ZHCFCX			3105

#define TDX_ID_FUNC_REQ_TL_ZHDMCZ			3106	// (����)��ϴ������ 3106
#define TDX_ID_FUNC_ANS_TL_ZHDMCZ			3107

#define TDX_ID_FUNC_REQ_TL_ZHCFCZ			3108	// (����)��ϳɷֲ��� 3108
#define TDX_ID_FUNC_ANS_TL_ZHCFCZ			3109

#define TDX_ID_FUNC_REQ_TL_CLDMCX			3110	// (����)���Դ����ѯ 3110
#define TDX_ID_FUNC_ANS_TL_CLDMCX			3111

#define TDX_ID_FUNC_REQ_TL_CLCFCX			3112	// (����)���Գɷֲ�ѯ 3112
#define TDX_ID_FUNC_ANS_TL_CLCFCX			3113

#define TDX_ID_FUNC_REQ_TL_CLDMCZ			3114	// (����)���Դ������ 3114
#define TDX_ID_FUNC_ANS_TL_CLDMCZ			3115

#define TDX_ID_FUNC_REQ_TL_CLCFCZ			3116	// (����)���Գɷֲ��� 3116
#define TDX_ID_FUNC_ANS_TL_CLCFCZ			3117

#define TDX_ID_FUNC_REQ_TL_PHCZ				3118	// (����)���Ų��� 3118
#define TDX_ID_FUNC_ANS_TL_PHCZ				3119

#define TDX_ID_FUNC_REQ_TL_PHCX				3120	// (����)���Ų�ѯ 3120
#define TDX_ID_FUNC_ANS_TL_PHCX				3121

#define TDX_ID_FUNC_REQ_TL_PHWTLB			3122	// (����)����ί���б� 3122
#define TDX_ID_FUNC_ANS_TL_PHWTLB			3123

#define TDX_ID_FUNC_REQ_TL_PHWTZX			3124	// (����)����ί��ִ�� 3124
#define TDX_ID_FUNC_ANS_TL_PHWTZX			3125

#define TDX_ID_FUNC_REQ_TL_PHWTCX			3126	// (����)����ί�в�ѯ 3126
#define TDX_ID_FUNC_ANS_TL_PHWTCX			3127

#define TDX_ID_FUNC_REQ_TL_PHCCCX			3128	// (����)���ųֲֲ�ѯ 3128
#define TDX_ID_FUNC_ANS_TL_PHCCCX			3129

// �㷨����
#define TDX_ID_FUNC_REQ_SFJY_DDCZ			3190	// (�㷨����)�������� 3190
#define TDX_ID_FUNC_ANS_SFJY_DDCZ			3191

#define TDX_ID_FUNC_REQ_SFJY_DDLBCX			3192	// (�㷨����)�����б��ѯ 3192
#define TDX_ID_FUNC_ANS_SFJY_DDLBCX			3193

#define TDX_ID_FUNC_REQ_SFJY_DDJGCX			3194	// (�㷨����)���������ѯ 3194
#define TDX_ID_FUNC_ANS_SFJY_DDJGCX			3195

// ���ý���
#define TDX_ID_FUNC_REQ_XYZCCX				3200	// �����ʲ���ѯ 3200
#define TDX_ID_FUNC_ANS_XYZCCX				3201

#define TDX_ID_FUNC_REQ_XYGFCX				3202	// ���ùɷݲ�ѯ 3202
#define TDX_ID_FUNC_ANS_XYGFCX				3203

#define TDX_ID_FUNC_REQ_XYHYCX				3204	// Ĭ��δƽ�ֺ�Լ��ѯ��ѯ 3204
#define TDX_ID_FUNC_ANS_XYHYCX				3205

#define TDX_ID_FUNC_REQ_XYHYYPCCX			3206	// ��ƽ�ֺ�Լ��ѯ 3206
#define TDX_ID_FUNC_ANS_XYHYYPCCX			3207

#define TDX_ID_FUNC_REQ_XYSXCX				3208	// �������޲�ѯ 3208
#define TDX_ID_FUNC_ANS_XYSXCX				3209

#define TDX_ID_FUNC_REQ_XYFZCX				3210	// ���ø�ծ��ѯ 3210
#define TDX_ID_FUNC_ANS_XYFZCX				3211

#define TDX_ID_FUNC_REQ_FXYZCCX				3212	// �������ʲ���ѯ 3212
#define TDX_ID_FUNC_ANS_FXYZCCX				3213

#define	TDX_ID_FUNC_REQ_XYHYDRCX			3214	// ���ú�Լ���ղ�ѯ 3214
#define	TDX_ID_FUNC_ANS_XYHYDRCX			3215

#define	TDX_ID_FUNC_REQ_XYJYBDZQCX			3216	// ���ý��ױ��֤ȯ��ѯ 3216
#define	TDX_ID_FUNC_ANS_XYJYBDZQCX			3217

#define	TDX_ID_FUNC_REQ_XYJYZHXXCX			3218	// ���ý����ۺ���Ϣ��ѯ 3218
#define	TDX_ID_FUNC_ANS_XYJYZHXXCX			3219

#define	TDX_ID_FUNC_REQ_XYJYDBPZQCX			3220	// ���ý��׵���Ʒ֤ȯ��ѯ 3220
#define	TDX_ID_FUNC_ANS_XYJYDBPZQCX			3221

#define	TDX_ID_FUNC_REQ_XYJYRZMRZQCX		3222	// ���ý�����������֤ȯ��ѯ 3222
#define	TDX_ID_FUNC_ANS_XYJYRZMRZQCX		3223

#define	TDX_ID_FUNC_REQ_XYJYRQMCZQCX		3224	// ���ý�����ȯ����֤ȯ��ѯ 3224
#define	TDX_ID_FUNC_ANS_XYJYRQMCZQCX		3225

#define	TDX_ID_FUNC_REQ_XYJYDMTSXXCX		3226	// ���ý��״�����ʾ��Ϣ��ѯ 3226
#define	TDX_ID_FUNC_ANS_XYJYDMTSXXCX		3227

#define	TDX_ID_FUNC_REQ_XYJYHYHZCX			3228	// ���ý��׺�Լ���ܲ�ѯ 3228
#define	TDX_ID_FUNC_ANS_XYJYHYHZCX			3229

#define	TDX_ID_FUNC_REQ_XYJYRZMRPTCX		3230	// ���ý��������������ײ�ѯ 3230
#define	TDX_ID_FUNC_ANS_XYJYRZMRPTCX		3231

#define	TDX_ID_FUNC_REQ_XYJYRQMCPTCX		3232	// ���ý�����ȯ�������ײ�ѯ 3232
#define	TDX_ID_FUNC_ANS_XYJYRQMCPTCX		3233

#define	TDX_ID_FUNC_REQ_XYJYMQHQPTCX		3234	// ���ý�����ȯ��ȯ���ײ�ѯ 3234
#define	TDX_ID_FUNC_ANS_XYJYMQHQPTCX		3235

#define	TDX_ID_FUNC_REQ_XYJYYQHZPTCX		3236	// ���ý�����ȯ��ת���ײ�ѯ 3236
#define	TDX_ID_FUNC_ANS_XYJYYQHZPTCX		3237

#define	TDX_ID_FUNC_REQ_XYJYXQHQPTCX		3238	// ���ý�����ȯ��ȯ���ײ�ѯ 3238
#define	TDX_ID_FUNC_ANS_XYJYXQHQPTCX		3239

#define	TDX_ID_FUNC_REQ_XYJYDBPHZPTCX		3240	// ���ý��׵���Ʒ��ת���ײ�ѯ 3240
#define	TDX_ID_FUNC_ANS_XYJYDBPHZPTCX		3241

#define	TDX_ID_FUNC_REQ_XYJYDBPHRPTCX		3242	// ���ý��׵���Ʒ�������ײ�ѯ 3242
#define	TDX_ID_FUNC_ANS_XYJYDBPHRPTCX		3243

#define	TDX_ID_FUNC_REQ_XYJYDBPHCPTCX		3244	// ���ý��׵���Ʒ�������ײ�ѯ 3244
#define	TDX_ID_FUNC_ANS_XYJYDBPHCPTCX		3245

#define	TDX_ID_FUNC_REQ_XYJYXJHKPTCX		3246	// ���ý����ֽ𻹿����ײ�ѯ 3246
#define	TDX_ID_FUNC_ANS_XYJYXJHKPTCX		3247

#define	TDX_ID_FUNC_REQ_XYJYMQHKPTCX		3248	// ���ý�����ȯ�������ײ�ѯ 3248
#define	TDX_ID_FUNC_ANS_XYJYMQHKPTCX		3249

#define	TDX_ID_FUNC_REQ_XYJYRZPCMCPTCX		3250	// ���ý�������ƽ���������ײ�ѯ 3250
#define	TDX_ID_FUNC_ANS_XYJYRZPCMCPTCX		3251

#define	TDX_ID_FUNC_REQ_XYJYRQPCMRPTCX		3252	// ���ý�����ȯƽ���������ײ�ѯ 3252
#define	TDX_ID_FUNC_ANS_XYJYRQPCMRPTCX		3253

#define	TDX_ID_FUNC_REQ_XYJYLLXXCX			3254	// ���ý���������Ϣ��ѯ 3254
#define	TDX_ID_FUNC_ANS_XYJYLLXXCX			3255

#define	TDX_ID_FUNC_REQ_XYJYRQYECX			3256	// ���ý�����ȯ����ѯ 3256
#define	TDX_ID_FUNC_ANS_XYJYRQYECX			3257

#define	TDX_ID_FUNC_REQ_XYJYRZYECX			3258	// ���ý�����������ѯ 3258
#define	TDX_ID_FUNC_ANS_XYJYRZYECX			3259

#define	TDX_ID_FUNC_REQ_XYJYFJYHZCX			3260	// ���ý��׷ǽ��׻�ת��ѯ 3260
#define	TDX_ID_FUNC_ANS_XYJYFJYHZCX			3261

#define	TDX_ID_FUNC_REQ_XYJYLXFYCX			3262	// ���ý�����Ϣ���ò�ѯ 3262
#define	TDX_ID_FUNC_ANS_XYJYLXFYCX			3263

#define	TDX_ID_FUNC_REQ_XYJYZJFZCX			3264	// ���ý����ʽ�ծ��ѯ 3264
#define	TDX_ID_FUNC_ANS_XYJYZJFZCX			3265

#define	TDX_ID_FUNC_REQ_XYJYZQFZCX			3266	// ���ý���֤ȯ��ծ��ѯ 3266
#define	TDX_ID_FUNC_ANS_XYJYZQFZCX			3267

#define	TDX_ID_FUNC_REQ_XYJYKHQYCX			3268	// ���ý��׿ͻ�ǩԼ��ѯ 3268
#define	TDX_ID_FUNC_ANS_XYJYKHQYCX			3269

#define	TDX_ID_FUNC_REQ_XYJYKHXYCL			3270	// ���ý��׿ͻ�Э�鴦�� 3270
#define	TDX_ID_FUNC_ANS_XYJYKHXYCL			3271

#define	TDX_ID_FUNC_REQ_XYJYCHMXCX			3272	// ���ý��׳�����ϸ��ѯ 3272
#define	TDX_ID_FUNC_ANS_XYJYCHMXCX			3273

#define	TDX_ID_FUNC_REQ_XYJYRZHYCX			3274	// ���ý������ʺ�Լ��ѯ 3274
#define	TDX_ID_FUNC_ANS_XYJYRZHYCX			3275

#define	TDX_ID_FUNC_REQ_XYJYRQHYCX			3276	// ���ý�����ȯ��Լ��ѯ 3276
#define	TDX_ID_FUNC_ANS_XYJYRQHYCX			3277

#define	TDX_ID_FUNC_REQ_XYJYDBPHZCX			3278	// ���ý��׵���Ʒ��ת��ѯ 3278
#define	TDX_ID_FUNC_ANS_XYJYDBPHZCX			3279

#define	TDX_ID_FUNC_REQ_XYJYMRDBPPTCX		3280	// ���ý������뵣��Ʒ���ײ�ѯ 3280
#define	TDX_ID_FUNC_ANS_XYJYMRDBPPTCX		3281

#define	TDX_ID_FUNC_REQ_XYJYMCDBPPTCX		3282	// ���ý�����������Ʒ���ײ�ѯ 3282
#define	TDX_ID_FUNC_ANS_XYJYMCDBPPTCX		3283

#define	TDX_ID_FUNC_REQ_XYJYGHRQFYPTCX		3284	// ���ý��׹黹��ȯ�������ײ�ѯ 3284
#define	TDX_ID_FUNC_ANS_XYJYGHRQFYPTCX		3285

#define	TDX_ID_FUNC_REQ_XYJYFZLSCX			3286	// ���ý��׸�ծ��ˮ��ѯ 3286
#define	TDX_ID_FUNC_ANS_XYJYFZLSCX			3287

#define	TDX_ID_FUNC_REQ_XYJYXJTDHQPTCX		3288	// ���ý����ֽ������ȯ���ײ�ѯ 3288
#define	TDX_ID_FUNC_ANS_XYJYXJTDHQPTCX		3289

#define	TDX_ID_FUNC_REQ_XYJYWCDBBLCX		3290	// ���ý���ά�ֵ������ʲ�ѯ 3290
#define	TDX_ID_FUNC_ANS_XYJYWCDBBLCX		3291

#define	TDX_ID_FUNC_REQ_XYJYEDGL			3292	// ���ý��׶�ȹ��� 3292
#define	TDX_ID_FUNC_ANS_XYJYEDGL			3293

#define	TDX_ID_FUNC_REQ_XYJYEDBGCX			3294	// ���ý��׶�ȱ����ѯ 3294
#define	TDX_ID_FUNC_ANS_XYJYEDBGCX			3295

#define	TDX_ID_FUNC_REQ_XYJYPCRZHYCX		3296	// ���ý���ƽ�����ʺ�Լ��ѯ 3296
#define	TDX_ID_FUNC_ANS_XYJYPCRZHYCX		3297

#define	TDX_ID_FUNC_REQ_XYJYPCRQHYCX		3298	// ���ý���ƽ����ȯ��Լ��ѯ 3298
#define	TDX_ID_FUNC_ANS_XYJYPCRQHYCX		3299

// ת��ͨ
#define	TDX_ID_FUNC_REQ_ZRTYWCZ				3400	// ת��ͨҵ����� 3400
#define	TDX_ID_FUNC_ANS_ZRTYWCZ				3401

#define	TDX_ID_FUNC_REQ_ZRTBDZQCX			3402	// ת��ͨ���֤ȯ��ѯ 3402
#define	TDX_ID_FUNC_ANS_ZRTBDZQCX			3403

#define	TDX_ID_FUNC_REQ_ZRTZJXXCX			3404	// ת��ͨ�ʽ���Ϣ��ѯ 3404
#define	TDX_ID_FUNC_ANS_ZRTZJXXCX			3405

#define	TDX_ID_FUNC_REQ_ZRTGFXXCX			3406	// ת��ͨ�ɷ���Ϣ��ѯ 3406
#define	TDX_ID_FUNC_ANS_ZRTGFXXCX			3407

#define	TDX_ID_FUNC_REQ_ZRTRZMRPTCX			3408	// ת��ͨ�����������ײ�ѯ 3408
#define	TDX_ID_FUNC_ANS_ZRTRZMRPTCX			3409

#define	TDX_ID_FUNC_REQ_ZRTRQMCPTCX			3410	// ת��ͨ��ȯ�������ײ�ѯ 3410
#define	TDX_ID_FUNC_ANS_ZRTRQMCPTCX			3411

#define	TDX_ID_FUNC_REQ_ZRTZJJRSQPTCX		3412	// ת��ͨ�ʽ�����������ײ�ѯ 3412
#define	TDX_ID_FUNC_ANS_ZRTZJJRSQPTCX		3413

#define	TDX_ID_FUNC_REQ_ZRTGFJRSQPTCX		3414	// ת��ͨ�ɷݽ����������ײ�ѯ 3414
#define	TDX_ID_FUNC_ANS_ZRTGFJRSQPTCX		3415

#define	TDX_ID_FUNC_REQ_ZRTJRZQSQPTCX		3416	// ת��ͨ����չ���������ײ�ѯ 3416
#define	TDX_ID_FUNC_ANS_ZRTJRZQSQPTCX		3417

#define	TDX_ID_FUNC_REQ_ZRTTQGHSQPTCX		3418	// ת��ͨ��ǰ�黹�������ײ�ѯ 3418
#define	TDX_ID_FUNC_ANS_ZRTTQGHSQPTCX		3419

#define	TDX_ID_FUNC_REQ_ZRTJRYWCDCX			3420	// ת��ͨ����ҵ�񳷵���ѯ 3420
#define	TDX_ID_FUNC_ANS_ZRTJRYWCDCX			3421

#define	TDX_ID_FUNC_REQ_ZRTJRYWDRCX			3422	// ת��ͨ����ҵ���ղ�ѯ 3422
#define	TDX_ID_FUNC_ANS_ZRTJRYWDRCX			3423

#define	TDX_ID_FUNC_REQ_ZRTJRYWLSCX			3424	// ת��ͨ����ҵ����ʷ��ѯ 3424
#define	TDX_ID_FUNC_ANS_ZRTJRYWLSCX			3425

#define	TDX_ID_FUNC_REQ_ZRTDRJRHYCX			3426	// ת��ͨ���ս����Լ��ѯ 3426
#define	TDX_ID_FUNC_ANS_ZRTDRJRHYCX			3427

#define	TDX_ID_FUNC_REQ_ZRTWLJRHYCX			3428	// ת��ͨδ�˽����Լ��ѯ 3428
#define	TDX_ID_FUNC_ANS_ZRTWLJRHYCX			3429

#define	TDX_ID_FUNC_REQ_ZRTYLJRHYCX			3430	// ת��ͨ���˽����Լ��ѯ 3430
#define	TDX_ID_FUNC_ANS_ZRTYLJRHYCX			3431

#define	TDX_ID_FUNC_REQ_ZRTZJCJSQPTCX		3432	// ת��ͨ�ʽ�����������ײ�ѯ 3432
#define	TDX_ID_FUNC_ANS_ZRTZJCJSQPTCX		3433

#define	TDX_ID_FUNC_REQ_ZRTGFCJSQPTCX		3434	// ת��ͨ�ɷݳ����������ײ�ѯ 3434
#define	TDX_ID_FUNC_ANS_ZRTGFCJSQPTCX		3435

#define	TDX_ID_FUNC_REQ_ZRTZJCJQDPTCX		3436	// ת��ͨ�ʽ����ȷ�����ײ�ѯ 3436
#define	TDX_ID_FUNC_ANS_ZRTZJCJQDPTCX		3437

#define	TDX_ID_FUNC_REQ_ZRTGFCJQDPTCX		3438	// ת��ͨ�ɷݳ���ȷ�����ײ�ѯ 3438
#define	TDX_ID_FUNC_ANS_ZRTGFCJQDPTCX		3439

#define	TDX_ID_FUNC_REQ_ZRTCJYWCDCX			3440	// ת��ͨ����ҵ�񳷵���ѯ 3440
#define	TDX_ID_FUNC_ANS_ZRTCJYWCDCX			3441

#define	TDX_ID_FUNC_REQ_ZRTCJYWDRCX			3442	// ת��ͨ����ҵ���ղ�ѯ 3442
#define	TDX_ID_FUNC_ANS_ZRTCJYWDRCX			3443

#define	TDX_ID_FUNC_REQ_ZRTCJYWLSCX			3444	// ת��ͨ����ҵ����ʷ��ѯ 3444
#define	TDX_ID_FUNC_ANS_ZRTCJYWLSCX			3445

#define	TDX_ID_FUNC_REQ_ZRTCJTQSHPTCX		3446	// ת��ͨ������ǰ�������ײ�ѯ 3446
#define	TDX_ID_FUNC_ANS_ZRTCJTQSHPTCX		3447

#define	TDX_ID_FUNC_REQ_ZRTCJTYZQPTCX		3448	// ת��ͨ����ͬ��չ�����ײ�ѯ 3448
#define	TDX_ID_FUNC_ANS_ZRTCJTYZQPTCX		3449

#define	TDX_ID_FUNC_REQ_ZRTQXFLCX			3450	// ת��ͨ���޷��ʲ�ѯ 3450
#define	TDX_ID_FUNC_ANS_ZRTQXFLCX			3451

#define	TDX_ID_FUNC_REQ_ZRTCJHYCX			3452	// ת��ͨ�����Լ��ѯ 3452
#define	TDX_ID_FUNC_ANS_ZRTCJHYCX			3453

#define	TDX_ID_FUNC_REQ_ZRTCJLSHYCX			3454	// ת��ͨ������ʷ��Լ��ѯ 3454
#define	TDX_ID_FUNC_ANS_ZRTCJLSHYCX			3455

#define	TDX_ID_FUNC_REQ_ZRTMCHKPTCX			3456	// ת��ͨ�����������ײ�ѯ 3456
#define	TDX_ID_FUNC_ANS_ZRTMCHKPTCX			3457

#define	TDX_ID_FUNC_REQ_ZRTMRHQPTCX			3458	// ת��ͨ���뻹ȯ���ײ�ѯ 3458
#define	TDX_ID_FUNC_ANS_ZRTMRHQPTCX			3459

#define	TDX_ID_FUNC_REQ_ZRTXJHKPTCX			3460	// ת��ͨ�ֽ𻹿����ײ�ѯ 3460
#define	TDX_ID_FUNC_ANS_ZRTXJHKPTCX			3461

#define	TDX_ID_FUNC_REQ_ZRTXQHQPTCX			3462	// ת��ͨ��ȯ��ȯ���ײ�ѯ 3462
#define	TDX_ID_FUNC_ANS_ZRTXQHQPTCX			3463

#define	TDX_ID_FUNC_REQ_ZRTKCJXXCX			3464	// ת��ͨ�ɳ�����Ϣ��ѯ 3464
#define	TDX_ID_FUNC_ANS_ZRTKCJXXCX			3465

#define	TDX_ID_FUNC_REQ_ZRTJRTYSHPTCX		3466	// ת��ͨ����ͬ���������ײ�ѯ 3466
#define	TDX_ID_FUNC_ANS_ZRTJRTYSHPTCX		3467

#define	TDX_ID_FUNC_REQ_ZRTCJZHXXCX			3468	// ת��ͨ�����˻���Ϣ��ѯ 3468
#define	TDX_ID_FUNC_ANS_ZRTCJZHXXCX			3469

// ����
#define TDX_ID_FUNC_REQ_XLYZT_BEGIN			4100

#define TDX_ID_FUNC_REQ_XLYZT_KTQXZDDL		4100	// ���� ��ͨ/ȡ���Զ��������ۡ��깺����� 4100
#define TDX_ID_FUNC_ANS_XLYZT_KTQXZDDL		4101

#define TDX_ID_FUNC_REQ_XLYZT_KTHZPS		4102	// ���� ��ͨ�������� 4102
#define TDX_ID_FUNC_ANS_XLYZT_KTHZPS		4103

#define TDX_ID_FUNC_REQ_XLYZT_QXHZPS		4104	// ���� ȡ���������� 4104
#define TDX_ID_FUNC_ANS_XLYZT_QXHZPS		4105

#define TDX_ID_FUNC_REQ_XLYZT_KTHZHG		4106	// ���� ��ͨ�����ع� 4106
#define TDX_ID_FUNC_ANS_XLYZT_KTHZHG		4107	

#define TDX_ID_FUNC_REQ_XLYZT_QXHZHG		4108	// ���� ȡ�������ع� 4108
#define TDX_ID_FUNC_ANS_XLYZT_QXHZHG		4109

#define TDX_ID_FUNC_REQ_XLYZT_KTHZSG		4110	// ���� ��ͨ�����깺 4110
#define TDX_ID_FUNC_ANS_XLYZT_KTHZSG		4111

#define TDX_ID_FUNC_REQ_XLYZT_QXHZSG		4112	// ���� ȡ�������깺 4112
#define TDX_ID_FUNC_ANS_XLYZT_QXHZSG		4113

#define TDX_ID_FUNC_REQ_XLYZT_DLGNCX		4114	// ��ѯ����ͨ��Ϣ 4114
#define TDX_ID_FUNC_ANS_XLYZT_DLGNCX		4115		

#define TDX_ID_FUNC_REQ_XLYZT_END			4200


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��ȫ������չ����

#define TDX_ID_FUNC_REQ_CA_AQGNSQ			4200	// ��ȫ�������� 4200
#define TDX_ID_FUNC_ANS_CA_AQGNSQ			4201

#define TDX_ID_FUNC_REQ_CA_AQGNCX			4202	// ��ȫ���ܳ��� 4202
#define TDX_ID_FUNC_ANS_CA_AQGNCX			4203

#define TDX_ID_FUNC_REQ_CA_MMBHWTJY			4204	// ���뱣������У�� 4204
#define TDX_ID_FUNC_ANS_CA_MMBHWTJY			4205

// �㷢֤ȯ����
#define TDX_ID_FUNC_REQ_CA_GETTZZB			4206	// ��ȡ��ս���� 4206
#define TDX_ID_FUNC_ANS_CA_GETTZZB			4207

#define TDX_ID_FUNC_REQ_CA_ZXJZK			4208	// ע������ 4208
#define TDX_ID_FUNC_ANS_CA_ZXJZK			4209

// Ԥ������
#define TDX_ID_FUNC_REQ_CA_YLWT				4210	// Ԥ������ 4210	
#define TDX_ID_FUNC_ANS_CA_YLWT				4211

// ��������֤
#define TDX_ID_FUNC_REQ_CA_CERRAREQ			4212	// ֤������ 4212
#define TDX_ID_FUNC_ANS_CA_CERRAREQ			4213

#define TDX_ID_FUNC_REQ_CA_CERAUDIT			4214	// ֤����� 4214
#define TDX_ID_FUNC_ANS_CA_CERAUDIT			4215

#define TDX_ID_FUNC_REQ_CA_CERDOWNLOAD		4216	// ֤������ 4216
#define TDX_ID_FUNC_ANS_CA_CERDOWNLOAD		4217

#define TDX_ID_FUNC_REQ_CA_CERDLCONFIRM		4218	// ֤������ȷ�� 4218
#define TDX_ID_FUNC_ANS_CA_CERDLCONFIRM		4219

// �������������
#define TDX_ID_FUNC_REQ_CA_ADDYHXX			4220	// ����û���Ϣ 4220
#define TDX_ID_FUNC_ANS_CA_ADDYHXX			4221

#define TDX_ID_FUNC_REQ_CA_XGYHXX			4222	// �޸��û���Ϣ 4222
#define TDX_ID_FUNC_ANS_CA_XGYHXX			4223

#define TDX_ID_FUNC_REQ_CA_CXYHXX			4224	// ��ѯ�û���Ϣ 4224
#define TDX_ID_FUNC_ANS_CA_CXYHXX			4225	

#define TDX_ID_FUNC_REQ_CA_GETYZM			4226	// ��ȡ�ֻ���֤�� 4226
#define TDX_ID_FUNC_ANS_CA_GETYZM			4227

#define TDX_ID_FUNC_REQ_CA_YZMJY			4228	// ��֤��У�� 4228
#define TDX_ID_FUNC_ANS_CA_YZMJY			4229	

// ����������֤У��
#define	TDX_ID_FUNC_REQ_OTHERCA_BASEFUN		4230	// ������ȫ��֤У�� 4230
#define	TDX_ID_FUNC_ANS_OTHERCA_BASEFUN		4231

// ��ѯ���뱣������
#define TDX_ID_FUNC_REQ_CA_MMBHWTCX			4232	// ���뱣�������ѯ 4232
#define TDX_ID_FUNC_ANS_CA_MMBHWTCX			4233	 

// �޸����뱣������
#define TDX_ID_FUNC_REQ_CA_XGMMBHWT			4234	// �޸����뱣������ 4234
#define TDX_ID_FUNC_ANS_CA_XGMMBHWT			4235

//	�޸�Ԥ������
#define TDX_ID_FUNC_REQ_CA_XGYLWT			4236	// �޸�Ԥ������ 4236
#define TDX_ID_FUNC_ANS_CA_XGYLWT			4237

// ���뱣�������б��ѯ
#define TDX_ID_FUNC_REQ_CA_PWDPROTQUEQU		4238	// ���뱣�������б��ѯ 4238
#define TDX_ID_FUNC_ANS_CA_PWDPROTQUEQU		4239

// �������뱣������
#define TDX_ID_FUNC_REQ_CA_APPLYPWDQA		4240	// �������뱣������ 4240
#define TDX_ID_FUNC_ANS_CA_APPLYPWDQA		4241

// ��������������
#define TDX_ID_FUNC_REQ_CA_BINDMACHINE		4242	// �������������� 4242
#define TDX_ID_FUNC_ANS_CA_BINDMACHINE		4243

// ��ѯ����Ϣ
#define TDX_ID_FUNC_REQ_CA_QUEBINDINFO		4244	// ��ѯ����Ϣ 4244
#define TDX_ID_FUNC_ANS_CA_QUEBINDINFO		4245

// ȡ������Ϣ
#define TDX_ID_FUNC_REQ_CA_CANCELBIND		4246	// ȡ������Ϣ 4246
#define TDX_ID_FUNC_ANS_CA_CANCELBIND		4247

// ��ȫ����״̬��ѯ
#define TDX_ID_FUNC_REQ_CA_SAFEMODQUE		4248	// ��ȫ����״̬��ѯ 4248
#define TDX_ID_FUNC_ANS_CA_SAFEMODQUE		4249

// �����û���ȫ����
#define TDX_ID_FUNC_REQ_CA_ABUSERLV			4250	// �����û���ȫ���� 4250
#define TDX_ID_FUNC_ANS_CA_ABUSERLV			4251

// �û�����
#define TDX_ID_FUNC_REQ_CA_USERLOGOUT		4252	// �û����� 4252
#define TDX_ID_FUNC_ANS_CA_USERLOGOUT		4253

// �û���������
#define TDX_ID_FUNC_REQ_CA_USERALIVE		4254	// �û��������� 4254
#define TDX_ID_FUNC_ANS_CA_USERALIVE		4255

// ȡ���û�����
#define TDX_ID_FUNC_REQ_CA_CANCELLV			4256	// ȡ���û����� 4256
#define TDX_ID_FUNC_ANS_CA_CANCELLV			4257

// ��ȡ��Ʒ����
#define TDX_ID_FUNC_REQ_CA_GETPROINFO		4258	// ��ȡ��Ʒ���� 4258
#define TDX_ID_FUNC_ANS_CA_GETPROINFO		4259

// ���֤ȯ��ȫ��ع���
// �ͻ�֤���
#define TDX_ID_FUNC_REQ_CA_BINDCERT_GD		4260	// �ͻ�֤��� 4260
#define TDX_ID_FUNC_ANS_CA_BINDCERT_GD		4261

// �ͻ�Ԥ����Ϣ
#define TDX_ID_FUNC_REQ_CA_RESER_GD			4262	// �û��������� 4262
#define TDX_ID_FUNC_ANS_CA_RESER_GD			4263


// ע���û���ع���
#define TDX_ID_FUNC_REQ_CA_REGUSER			4280	// ע���û�
#define TDX_ID_FUNC_ANS_CA_REGUSER			4281

#define TDX_ID_FUNC_REQ_CA_ALTERREGPWD		4282	// �޸�ע������
#define TDX_ID_FUNC_ANS_CA_ALTERREGPWD		4283

// �����½���
#define TDX_ID_FUNC_REQ_CA_SSO				4284	// �����½���Ʋ���
#define TDX_ID_FUNC_ANS_CA_SSO				4285
#define TDX_ID_FUNC_REQ_CA_SSOYHXX			4286	// �����½��������ȡ�û���Ϣ
#define TDX_ID_FUNC_ANS_CA_SSOYHXX			4287
// �°汾֤��
#define TDX_ID_FUNC_REQ_CA_CERDEL			4288	// ֤�����
#define TDX_ID_FUNC_ANS_CA_CERDEL			4289
// OTPͬ��
#define TDX_ID_FUNC_REQ_CA_OTPSYN			4290	//	OTPͬ��
#define TDX_ID_FUNC_ANS_CA_OTPSYN			4291
// �������һ����
#define TDX_ID_FUNC_REQ_CA_CHECKRECORD		4292	//	�������һ����
#define TDX_ID_FUNC_ANS_CA_CHECKRECORD		4293	//	
#define TDX_ID_FUNC_REQ_CA_PAAUTH			4294	// �޸�ע������
#define TDX_ID_FUNC_ANS_CA_PAAUTH			4295
#define TDX_ID_FUNC_REQ_CA_ACCREPORT		4296	// Ͷ����ϱ���
#define TDX_ID_FUNC_ANS_CA_ACCREPORT		4297
// OTP����
#define TDX_ID_FUNC_REQ_CA_OTPTEMP			4298	// OTP����
#define TDX_ID_FUNC_ANS_CA_OTPTEMP			4299
// ��ȡ�����ֻ���֤��
#define	TDX_ID_FUNC_REQ_OTHERCA_GETYZM		4300	// ��ȡ�����ֻ���֤��
#define	TDX_ID_FUNC_ANS_OTHERCA_GETYZM		4301

// ��ѡ���ϴ�����
#define	TDX_ID_FUNC_REQ_OPMYSTOCK			4302	// ��ѡ���ϴ�����
#define	TDX_ID_FUNC_ANS_OPMYSTOCK			4303

// �һ�����
#define	TDX_ID_FUNC_REQ_FETCHPWD			4304	// �һ��û�����
#define	TDX_ID_FUNC_ANS_FETCHPWD			4305

// �һ��û���
#define	TDX_ID_FUNC_REQ_FETCHUSERACCOUNT	4306	// �һ��û��ʺ�
#define	TDX_ID_FUNC_ANS_FETCHUSERACCOUNT	4307

// ���ֲ�ѯ
#define	TDX_ID_FUNC_REQ_QUERYSCORE			4308	// ���ֲ�ѯ
#define	TDX_ID_FUNC_ANS_QUERYSCORE			4309

// ע���û���Ϣ��ѯ
#define	TDX_ID_FUNC_REQ_QUERYREGUDATA		4310	// ע���û���Ϣ��ѯ
#define	TDX_ID_FUNC_ANS_QUERYREGUDATA		4311

// ��ȡ������
#define TDX_ID_FUNC_REQ_GETACTIVECODE		4312	// ��ȡ������
#define TDX_ID_FUNC_ANS_GETACTIVECODE		4313


// �°汾��ȫ����( 4500 - 4600)

#define TDX_ID_FUNC_REQ_QRYSCFUNC			4500	// ��ȫ���ܲ�ѯ ( �û������İ�ȫ����, OPT���к�, ֤����Ч��)
#define TDX_ID_FUNC_ANS_QRYSCFUNC			4501

#define TDX_ID_FUNC_REQ_SWITCHSCFUNC		4502	// ����/�رհ�ȫ����
#define TDX_ID_FUNC_ANS_SWITCHSCFUNC		4503

#define TDX_ID_FUNC_REQ_UNIAUTH				4504	// ͳһ��֤
#define TDX_ID_FUNC_ANS_UNIAUTH				4505

#define TDX_ID_FUNC_REQ_REQAPWD				4506	// ������֤����
#define TDX_ID_FUNC_ANS_REQAPWD				4507

#define TDX_ID_FUNC_REQ_MODAPWD				4508	// �޸���֤����
#define TDX_ID_FUNC_ANS_MODAPWD				4509

#define TDX_ID_FUNC_REQ_RESETAPWD			4510	// ������֤����
#define TDX_ID_FUNC_ANS_RESETAPWD			4511

#define TDX_ID_FUNC_REQ_SYNOTP				4512	// ͬ��OTP
#define TDX_ID_FUNC_ANS_SYNOTP				4513

#define TDX_ID_FUNC_REQ_GETCSIGNKEY			4514	// ��ȡ֤��ǩ����
#define TDX_ID_FUNC_ANS_GETCSIGNKEY			4515

#define TDX_ID_FUNC_REQ_UPDCERT				4516	// ����֤��
#define TDX_ID_FUNC_ANS_UPDCERT				4517

#define TDX_ID_FUNC_REQ_GETCCODE			4518	// ��ȡ�ֻ���̬��
#define TDX_ID_FUNC_ANS_GETCCODE			4519

#define TDX_ID_FUNC_REQ_PERMITMACHINE		4520	// ��Ȩ����� ( CPU, MAC�б�, HDD�б�, BIOS) ( ����ѡ����֤, ʹ���ֻ���̬��������뱣������,���߰�ȫ��ʽ, ����ѡ��һ��)
#define TDX_ID_FUNC_ANS_PERMITMACHINE		4521

#define TDX_ID_FUNC_REQ_FREEMACHINE			4522	// ����������Ȩ( ����ѡ����֤, ʹ���ֻ���̬��������뱣������,���߰�ȫ��ʽ, ����ѡ��һ��)
#define TDX_ID_FUNC_ANS_FREEMACHINE			4523

#define TDX_ID_FUNC_REQ_QRYPERMITION		4524	// ��ѯ��Ȩ
#define TDX_ID_FUNC_ANS_QRYPERMITION		4525

#define TDX_ID_FUNC_REQ_UPDSELFINFO			4526	// ����Ԥ����Ϣ
#define TDX_ID_FUNC_ANS_UPDSELFINFO			4527

#define TDX_ID_FUNC_REQ_QRYUSERCOMMON		4528	// ��ѯ�û�������Ϣ( �ϴε�¼IP, �ϴε�¼MAC, �ϴ�ʹ�ð汾, �ܵ�¼����, Ԥ����Ϣ)
#define TDX_ID_FUNC_ANS_QRYUSERCOMMON		4529

#define TDX_ID_FUNC_REQ_QRYUDATA			4530	// �û����ϲ�ѯ ( �ֻ���, ���֤�ŵ�)
#define TDX_ID_FUNC_ANS_QRYUDATA			4531

#define TDX_ID_FUNC_REQ_UPDUDATA			4532	// �����û�����
#define TDX_ID_FUNC_ANS_UPDUDATA			4533

#define TDX_ID_FUNC_REQ_QRYIMPOTOP			4534	// �ؼ�������ѯ
#define TDX_ID_FUNC_ANS_QRYIMPOTOP			4535

#define TDX_ID_FUNC_REQ_RCDIMPOTOP			4536	// �ؼ�������¼( ���ܺ�, ��������, ����˵��)
#define TDX_ID_FUNC_ANS_RCDIMPOTOP			4537

#define TDX_ID_FUNC_REQ_QRYAUTHHIS			4538	// ��֤��ʷ��ѯ( ��֤ʱ��, ��ȫ��ʽ, ��֤���, IP, MAC, ������Ϣ, �ͻ��˰汾)
#define TDX_ID_FUNC_ANS_QRYAUTHHIS			4539

#define TDX_ID_FUNC_REQ_REQQAPROT			4540	// ���뱣����������
#define TDX_ID_FUNC_ANS_REQQAPROT			4541

#define TDX_ID_FUNC_REQ_MODQAPROT			4542	// ���뱣�������޸�
#define TDX_ID_FUNC_ANS_MODQAPROT			4543

#define TDX_ID_FUNC_REQ_AUTHQAPROT			4544	// ���뱣��У��
#define TDX_ID_FUNC_ANS_AUTHQAPROT			4545

#define TDX_ID_FUNC_REQ_RESVPWD				4546	// Ӧ������
#define TDX_ID_FUNC_ANS_RESVPWD				4547

#define TDX_ID_FUNC_REQ_CONSIS				4548	// ���������ǩ����Ϣ
#define TDX_ID_FUNC_ANS_CONSIS				4549

// �°汾��ȫ����( 4500 - 4600)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// ģ�⽻�����
#define TDX_ID_FUNC_REQ_SYLPM				5000	// ���������� 5000
#define TDX_ID_FUNC_ANS_SYLPM				5001

#define TDX_ID_FUNC_REQ_ZHRQ				5002	// �ʻ���ȯ 5002
#define TDX_ID_FUNC_ANS_ZHRQ				5003

#define TDX_ID_FUNC_REQ_RQCX				5004	// ��ȯ��ѯ 5004
#define TDX_ID_FUNC_ANS_RQCX				5005

#define	TDX_ID_FUNC_REQ_ZHHQZQ				5006	// �ʻ���ȯչ�� 5006
#define	TDX_ID_FUNC_ANS_ZHHQZQ				5007

#define	TDX_ID_FUNC_REQ_TCMONITOR			5008	// �������ļ�� 5008
#define	TDX_ID_FUNC_ANS_TCMONITOR			5009

#define	TDX_ID_FUNC_REQ_TSROUTING			5010	// TS·�� 5010
#define	TDX_ID_FUNC_ANS_TSROUTING			5011


//---------------------------------------------------------------------------
// Part.VI �ʺ����Ͷ����Լ������ֵ���ö���ͱ�־����
//---------------------------------------------------------------------------

// �˺����
#define SZAG				0						// ����A��
#define SHAG				1						// �Ϻ�A��
#define SZBG				2						// ����B��
#define SHBG				3						// �Ϻ�B��
#define SZGZ				4						// ���ڹ�ծ
#define SHGZ				5						// �Ϻ���ծ
#define DFGT				6						// �ط���̨
#define QHWT				7						// �ڻ�ί��
#define SHHY				8						// ���һ(�ʽ��ʺ�)
#define KHWT				9						// �ͻ���ί��
//#define SHWT				10						// �ͻ���ί��
#define SZCY				11						// ���ڴ�ҵ
#define SBAG				12						// ����A��
#define SBBG				13 						// ����B��
#define SBGB				14						// ����G��
#define KSJJ				15						// ����ʽ����
#define SZHG				16						// ��֤�ع�
#define SHHG				17						// �Ϻ��ع�
#define ZBZH				18						// �����ʻ�
#define SBZH				19						// �����ʻ�
#define QHZH				20						// �ڻ��ʺ�
#define ZZQH				21						// ֣���ڻ�
#define SHQH				22						// �Ϻ��ڻ�
#define DLQH				23						// �����ڻ�
#define KHKH				24						// �ͻ�����
#define YHWT				25						// �������з�ʽ��¼	
#define ZJQH				26						// �н��ڻ�
#define GGJYZH				27						// �۹ɽ����ʺ�
#define ZCYH				28						// ע���û�(��ʹ�������ʺ�У��,����¼����,����)
#define FWYH				29						// �����û�(����̨���з����ʺ���֤,У�鲻��¼����)
#define YHZH				30						// �����˺�
#define LMKH				31						// ��������
#define NAME				32						// �ǳ�(����̨���з����ʺ���֤,У�鲻��¼����)
#define SFZH				33						// ���֤(����̨���з����ʺ���֤,У�鲻��¼����)
#define SJH					34						// �ֻ���(����̨���з����ʺ���֤,У�鲻��¼����)
#define SVYH_NB				35						// �ڲ�Ա����(����̨���з����ʺ���֤,У�鲻��¼����
#define TYYH				36						// �����û�(���в����������̨�����)


// ������־(TDX_ID_MMBZ)
#define TDX_FLAG_MMBZ_MR		0					// ����
#define TDX_FLAG_MMBZ_MC		1					// ����
#define TDX_FLAG_MMBZ_CD		2					// ����(����ѯ����)
#define TDX_FLAG_MMBZ_MRCD		3					// ����(����ѯ����)
#define TDX_FLAG_MMBZ_MCCD		4					// ����(����ѯ����)
#define TDX_FLAG_MMBZ_KZZZG		5					// ��תծת��(����ѯ���)
#define TDX_FLAG_MMBZ_KZZHS		6					// ��תծ����(����ѯ���)
#define TDX_FLAG_MMBZ_DQDESG	5					// ���ڶ����깺(����)
#define TDX_FLAG_MMBZ_RQ		6					// ��ȯ(����)
#define TDX_FLAG_MMBZ_HQ		7					// ��ȯ(����)
#define TDX_FLAG_MMBZ_ZQ		8					// չ��(����)
#define TDX_FLAG_MMBZ_YMR		9					// Ԥ��
#define TDX_FLAG_MMBZ_YMC		10					// Ԥ��
#define TDX_FLAG_MMBZ_XGYWT		11					// �޸�Ԥί��
#define TDX_FLAG_MMBZ_LOFHB		12					// LOF�ϲ�
#define TDX_FLAG_MMBZ_LOFFC		13					// LOF�ֲ�
#define TDX_FLAG_MMBZ_LOFZH		14					// LOFת��
#define TDX_FLAG_MMBZ_MRDBP		15					// ���뵣��Ʒ
#define TDX_FLAG_MMBZ_MCDBP		16					// �������Ʒ
#define TDX_FLAG_MMBZ_YHK		17					// Ԥ����
#define TDX_FLAG_MMBZ_YHQ		18					// Ԥ��ȯ
#define TDX_FLAG_MMBZ_HGRZ		19					// �ع�����
#define TDX_FLAG_MMBZ_HGRQ		20					// �ع���ȯ
#define TDX_FLAG_MMBZ_ZDSHMR	21					// �Զ��������
#define TDX_FLAG_MMBZ_XJTDHQ	22					// (��ȯ)�ֽ������ȯ
#define TDX_FLAG_MMBZ_ZRTRZMR	23					// ת��ͨ��������
#define TDX_FLAG_MMBZ_ZRTRQMC	24					// ת��ͨ��ȯ����
#define TDX_FLAG_MMBZ_ZHXYYXMR	25					// �ۺ�Э����������
#define TDX_FLAG_MMBZ_ZHXYYXMC	26					// �ۺ�Э����������
#define TDX_FLAG_MMBZ_ZHXYDJMR	27					// �ۺ�Э�鶨������
#define TDX_FLAG_MMBZ_ZHXYDJMC	28					// �ۺ�Э�鶨������
#define TDX_FLAG_MMBZ_ZHXYCJMR	29					// �ۺ�Э��ɽ�����
#define TDX_FLAG_MMBZ_ZHXYCJMC	30					// �ۺ�Э��ɽ�����
#define TDX_FLAG_MMBZ_ZQZYCK	31					// ծȯ��Ѻ����
#define TDX_FLAG_MMBZ_ZQZYRK	32					// ծȯ��Ѻ���
#define TDX_FLAG_MMBZ_ZRTMCHK	33					// ת��ͨ��������
#define TDX_FLAG_MMBZ_ZRTMRHQ	34					// ת��ͨ���뻹ȯ
#define TDX_FLAG_MMBZ_ZRTXJHK	35					// ת��ͨ�ֽ𻹿�
#define TDX_FLAG_MMBZ_ZRTXQHQ	36					// ת��ͨ��ȯ��ȯ
#define TDX_FLAG_MMBZ_GTZQYXMR	37					// ��̨ծȯ��������
#define TDX_FLAG_MMBZ_GTZQYXMC	38					// ��̨ծȯ��������
#define TDX_FLAG_MMBZ_GTZQDEMR	39					// ��̨ծȯ�������
#define TDX_FLAG_MMBZ_GTZQDEMC	40					// ��̨ծȯ�������
#define TDX_FLAG_MMBZ_GTZQXEMR	41					// ��̨ծȯС������
#define TDX_FLAG_MMBZ_GTZQXEMC	42					// ��̨ծȯС������
#define TDX_FLAG_MMBZ_GTZQCJMR	43					// ��̨ծȯ�ɽ�����
#define TDX_FLAG_MMBZ_GTZQCJMC	44					// ��̨ծȯ�ɽ�����
#define TDX_FLAG_MMBZ_JYSHBJJSG	45					// ���������һ����깺
#define TDX_FLAG_MMBZ_JYSHBJJSH	46					// ���������һ������
#define TDX_FLAG_MMBZ_RZXQWT	47					// ������Ȩί��
#define TDX_FLAG_MMBZ_RZXQMCHK	48					// ������Ȩ��������
#define TDX_FLAG_MMBZ_RZXQXJHK	49					// ������Ȩ�ֽ𻹿�
#define TDX_FLAG_MMBZ_NBGFHZ	50					// �ڲ��ɷݻ�ת
#define TDX_FLAG_MMBZ_QQZZXQ	51					// ��Ȩ������Ȩ
#define TDX_FLAG_MMBZ_TJQQSDS	52					// �ύ��Ȩ����˰
#define TDX_FLAG_MMBZ_FQZQ		'A'					// [65]������ǩ(����,�Ѳ��õ�������)
#define TDX_FLAG_MMBZ_GHRQFY	'B'					// [66]�黹��ȯ����
#define TDX_FLAG_MMBZ_SJMR		'C'					// [67]�м�����
#define TDX_FLAG_MMBZ_SJMC		'D'					// [68]�м�����
#define TDX_FLAG_MMBZ_RZMR		'E'					// [69]��������
#define TDX_FLAG_MMBZ_RQMC		'F'					// [70]��ȯ����
#define TDX_FLAG_MMBZ_MRHQ		'G'					// [71](��ȯ)��ȯ��ȯ
#define TDX_FLAG_MMBZ_YQHZ		'H'					// [72]��ȯ��ת
#define TDX_FLAG_MMBZ_XQHQ		'I'					// [73](��ȯ)��ȯ��ȯ
#define TDX_FLAG_MMBZ_DBPHZ		'J'					// [74]����Ʒ��ת
#define TDX_FLAG_MMBZ_HK		'K'					// [75](�����ֽ�)����
#define TDX_FLAG_MMBZ_XQHK		'L'					// [76](����)��ȯ����[������ȯ����]
#define TDX_FLAG_MMBZ_RZPCMC	'M'					// [77]����ƽ������
#define TDX_FLAG_MMBZ_RQPCMR	'N'					// [78]��ȯƽ������
#define TDX_FLAG_MMBZ_LOFSG		'O'					// [79]LOF�깺
#define TDX_FLAG_MMBZ_LOFSH		'P'					// [80]LOF���
#define TDX_FLAG_MMBZ_LOFRG		'Q'					// [81]LOF�Ϲ�
#define TDX_FLAG_MMBZ_YXWTMR	'R'					// [82]����ί������
#define TDX_FLAG_MMBZ_YXWTMC	'S'					// [83]����ί������
#define TDX_FLAG_MMBZ_DJWTMR	'T'					// [84]����ί������
#define TDX_FLAG_MMBZ_DJWTMC	'U'					// [85]����ί������
#define TDX_FLAG_MMBZ_QZXQ		'V'					// [86]Ȩ֤��Ȩ
#define TDX_FLAG_MMBZ_CJQRMR	'W'					// [87]�ɽ�ȷ������
#define TDX_FLAG_MMBZ_CJQRMC	'X'					// [88]�ɽ�ȷ������
#define TDX_FLAG_MMBZ_YYSB		'Y'					// [89]ҪԼ�걨
#define TDX_FLAG_MMBZ_YYJC		'Z'					// [90]ҪԼ���

// ETF������ʶ(TDX_ID_ETFMMBS)
#define TDX_FLAG_ETF_MMBS_SG		0				// ETF�깺
#define TDX_FLAG_ETF_MMBS_SH		1				// ETF���
#define TDX_FLAG_ETF_MMBS_GPRG		2				// ETF�ɷ��Ϲ�(��������/����,�ӿڸ�����������)
#define TDX_FLAG_ETF_MMBS_XJRG		3				// ETF�ֽ��Ϲ�(��������/����,�ӿڸ�����������)
#define TDX_FLAG_ETF_MMBS_WSGPRG	4				// ETF���Ϲɷ��Ϲ�
#define TDX_FLAG_ETF_MMBS_WSXJRG	5				// ETF�����ֽ��Ϲ�
#define TDX_FLAG_ETF_MMBS_WXGPRG	6				// ETF���¹ɷ��Ϲ�
#define TDX_FLAG_ETF_MMBS_WXXJRG	7				// ETF�����ֽ��Ϲ�
#define TDX_FLAG_ETF_MMBS_SWSG		8				// ETF(���г�)ʵ���깺
#define TDX_FLAG_ETF_MMBS_SWSH		9				// ETF(���г�)ʵ�����
#define TDX_FLAG_ETF_MMBS_SWRG		10				// ETF(���г�)ʵ���Ϲ�
#define TDX_FLAG_ETF_MMBS_KJXJSG	11				// ETF�羳�ֽ��깺
#define TDX_FLAG_ETF_MMBS_KJXJSH	12				// ETF�羳�ֽ����
#define TDX_FLAG_ETF_MMBS_KJXJRG	13				// ETF�羳�ֽ��Ϲ�

// ����������־(TDX_ID_KFSJJ_MMBZ)
// ��ѯͨ��TDX_ID_MMBZ����(0-�� 1-�� 2-�������� 3-���� 4-����)
#define TDX_FLAG_JJ_MMBZ_JJRG		0				// �����Ϲ�
#define TDX_FLAG_JJ_MMBZ_JJSG		1				// �����깺
#define TDX_FLAG_JJ_MMBZ_CYLC		1				// �������
#define TDX_FLAG_JJ_MMBZ_JJSH		2				// �������
#define TDX_FLAG_JJ_MMBZ_LCTC		2				// ����˳�
#define TDX_FLAG_JJ_MMBZ_YYSG		3				// ԤԼ�깺
#define TDX_FLAG_JJ_MMBZ_YYSH		4				// ԤԼ���
#define TDX_FLAG_JJ_MMBZ_DQSG		5				// �����깺
#define TDX_FLAG_JJ_MMBZ_YYRG		6				// ԤԼ�Ϲ�
#define TDX_FLAG_JJ_MMBZ_JJZH		7				// ����ת��
#define TDX_FLAG_JJ_MMBZ_LCZRYXMR	8				// ���ת����������
#define TDX_FLAG_JJ_MMBZ_LCZRYXMC	9				// ���ת����������
#define TDX_FLAG_JJ_MMBZ_LCZRDJMR	10				// ���ת�ö�������
#define TDX_FLAG_JJ_MMBZ_LCZRDJMC	11				// ���ת�ö�������
#define TDX_FLAG_JJ_MMBZ_LCZRQDMR	12				// ���ת��ȷ������
#define TDX_FLAG_JJ_MMBZ_LCZRQDMC	13				// ���ת��ȷ������
#define TDX_FLAG_JJ_MMBZ_LCCPSG		14				// ��Ʋ�Ʒ�깺
#define TDX_FLAG_JJ_MMBZ_LCCPSH		15				// ��Ʋ�Ʒ���

#define TDX_FLAG_JJ_MMBZ_LCZRDEMR	31				// ���ת�ô��ɽ�����
#define TDX_FLAG_JJ_MMBZ_LCZRDEMC	32				// ���ת�ô��ɽ�����
#define TDX_FLAG_JJ_MMBZ_LCZRXEMR	33				// ���ת��С��ɽ�����
#define TDX_FLAG_JJ_MMBZ_LCZRXEMC	34				// ���ת��С��ɽ�����
#define TDX_FLAG_JJ_MMBZ_LCZRCJMR	35				// ���ת������ɽ�����
#define TDX_FLAG_JJ_MMBZ_LCZRCJMC	36				// ���ת������ɽ�����


// ��Ʒ��־(TDX_ID_CPBZ)
#define TDX_FLAG_CPBZ_JJCP		((BYTE)0)			// �����Ʒ
#define TDX_FLAG_CPBZ_LCCP		((BYTE)1)			// ��Ʋ�Ʒ
#define TDX_FLAG_CPBZ_XJCP		((BYTE)2)			// �ֽ��Ʒ
#define TDX_FLAG_CPBZ_YHCP		((BYTE)3)			// ���в�Ʒ
#define TDX_FLAG_CPBZ_DXCP		((BYTE)4)			// ������Ʒ
#define TDX_FLAG_CPBZ_XTCP		((BYTE)5)			// ���в�Ʒ
#define TDX_FLAG_CPBZ_ALL		((BYTE)(-1))		// ȫ��(���ڲ�ѯ)

// ��Ʒ��ѯ������־(TDX_ID_CZBZ)
// ��Ӧ��"��Ʒ��־(TDX_ID_CPBZ)"��1
#define TDX_FLAG_CPCX_CZBZ_LCCP	((BYTE)0)			// ��Ʋ�Ʒ
#define TDX_FLAG_CPCX_CZBZ_XJCP	((BYTE)1)			// �ֽ��Ʒ
#define TDX_FLAG_CPCX_CZBZ_YHCP	((BYTE)2)			// ���в�Ʒ
#define TDX_FLAG_CPCX_CZBZ_DXCP	((BYTE)3)			// ������Ʒ
#define TDX_FLAG_CPCX_CZBZ_ALL	((BYTE)(-1))		// ȫ��

// �ֺ��־(TDX_ID_KFSJJ_DIVIDENMETHOD,TDX_ID_FHBZ)
#define TDX_FLAG_FHBZ_HLZG		0					// ����ת��
#define TDX_FLAG_FHBZ_XJFH		1					// �ֽ�ֺ�
#define TDX_FLAG_FHBZ_LDXJZZZTZ	2					// �����ֽ���ֵ��Ͷ��
#define TDX_FLAG_FHBZ_ZZXJLDZTZ	3					// ��ֵ�ֽ�������Ͷ��
#define TDX_FLAG_FHBZ_CANNOTSET	99					// ��������(���ڿͻ����������)

// �����շѷ�ʽ(TDX_ID_SFFS)
#define TDX_FLAG_JJ_SFFS_QD		1					// ǰ��
#define TDX_FLAG_JJ_SFFS_HD		2					// ���
#define TDX_FLAG_JJ_SFFS_CL		4					// C��

// ����޶���ط�ʽ(TDX_ID_SHFS)
#define TDX_FLAG_JJ_JESHFS_QX	0					// ȡ��
#define TDX_FLAG_JJ_JESHFS_SY	1					// ˳��

// ί�����(TDX_ID_WTFS)--���ڹ�Ʊ
#define TDX_FLAG_WTLB_XJWT		0					// [�޼�ί��]�޼�
#define TDX_FLAG_WTLB_DFZY		1					// [�Է�����]���ַ����ż۸�
#define TDX_FLAG_WTLB_BFZY		2					// [��������]�������ż۸�
#define TDX_FLAG_WTLB_JCSC		3					// [����ʣ��]��ʱ�ɽ�ʣ�೷��
#define TDX_FLAG_WTLB_WDSC		4					// [�嵵ʣ��]�����嵵��ʱ�ɽ�ʣ�೷��
#define TDX_FLAG_WTLB_QEWT		5					// [ȫ��ί��]ȫ��ɽ�����
#define TDX_FLAG_WTLB_WDSZ		6					// [�嵵ʣת]�����嵵��ʱ�ɽ�ʣ��ת�޼�

// ί�����(TDX_ID_WTFS)--�����ڻ�
#define TDX_FLAG_WTLB_QH_XJWT	0					// �޼�ί��
#define TDX_FLAG_WTLB_QH_SJWT	1					// �м�ί��
#define TDX_FLAG_WTLB_QH_SJZS	2					// �м�ֹ��
#define TDX_FLAG_WTLB_QH_SJZY	3					// �м�ֹӯ
#define TDX_FLAG_WTLB_QH_XJZS	4					// �޼�ֹ��
#define TDX_FLAG_WTLB_QH_XJZY	5					// �޼�ֹӯ
#define TDX_FLAG_WTLB_QH_ZYJ	6					// ���ż�

// ί�����(TDX_ID_WTFS)--���̽���
#define TDX_FLAG_WTLB_WP_LO		0					// �޼���(Limit Order)
#define TDX_FLAG_WTLB_WP_AO		1					// ������(Auction Order)
#define TDX_FLAG_WTLB_WP_ALO	2					// �����޼���(Auction Limit Order)
#define TDX_FLAG_WTLB_WP_ELO	3					// ��ǿ�޼���(Enhanced Limit Order)
#define TDX_FLAG_WTLB_WP_SLO	4					// �ر��޼���(Special Limit Order)
#define TDX_FLAG_WTLB_WP_MO		5					// �м���(Market Order)
#define TDX_FLAG_WTLB_WP_SELO	6					// ������ǿ�޼���(Super Enhanced Limit Order)
#define TDX_FLAG_WTLB_WP_SSLO	7					// �����ر��޼���(Super Special Limit Order)
#define TDX_FLAG_WTLB_WP_LLO	8					// (?)�޼���(? Limit Order) -- �ɸ���ʱ����Զ�ת���� LO �� AO

// �ڻ���ƽ��־(TDX_ID_KPBZ)
#define TDX_FLAG_QH_KPBZ_KC		0					// ����
#define TDX_FLAG_QH_KPBZ_PC		1					// ƽ��
#define TDX_FLAG_QH_KPBZ_PJ		2					// ƽ��
#define TDX_FLAG_QH_KPBZ_QP		3					// ǿƽ

// �ڻ�Ͷ����־(TDX_ID_TBBZ)
#define TDX_FLAG_QH_TBBZ_TJ		0					// Ͷ��
#define TDX_FLAG_QH_TBBZ_BZ		1					// ��ֵ
#define TDX_FLAG_QH_TBBZ_TL		2					// ����

// �ɽ�����(TDX_ID_CJSX)[���԰�λ����]
#define TDX_FLAG_CJSX_SDJY		(0x00000001)		// ��������(���ɳ���)

// �ڻ��ɽ�����(TDX_ID_CJSX)
#define TDX_FLAG_QH_CJSX_DRYX	0					// ������Ч[GFD]
#define TDX_FLAG_QH_CJSX_QCHC	1					// ȫ�ɻ�[FOK]
#define TDX_FLAG_QH_CJSX_SYJC	2					// ʣ�༴��[FAK]

// ���̳ɽ�����(TDX_ID_CJSX)[���԰�λ����]
#define TDX_FLAG_WP_CJSX_PF		(0x00000001)		// ����ִ��(partial fill)
#define TDX_FLAG_WP_CJSX_PM		(0x00000002)		// ��ǰ����(pre market)
#define TDX_FLAG_WP_CJSX_OL		(0x00000004)		// ��ɽ���(odd lot)
#define TDX_FLAG_WP_CJSX_SS		(0x00000008)		// ���ս���(short sell)

// �ڻ��������(TDX_ID_ZHLX)
#define TDX_FLAG_QH_ZHLX_TL		0					// ����
#define TDX_FLAG_QH_ZHLX_HH		1					// ����

// ת�˷���(TDX_ID_YZZZ_ZZFX)
#define TDX_FLAG_ZZFX_ZR		0					// ת��
#define TDX_FLAG_ZZFX_ZC		1					// ת��
#define TDX_FLAG_ZZFX_ALL		((BYTE)(-1))		// ȫ��(���ڲ�ѯ)

// �����ع�״̬(TDX_ID_HZHGZT)
#define TDX_FLAG_HZHGZT_SQMR	0					// ��������
#define TDX_FLAG_HZHGZT_TQZZ	1					// ��ǰ��ֹ

// ��¼�������(TDX_ID_XT_LOGINENTERPARAM)
#define TDX_FLAG_LEP_ZJZHDL		('1')				// ׷���˺ŵ�¼

// ��¼���ز���(TDX_ID_XT_LOGINRETURNPARAM)
#define TDX_FLAG_LRP_DZJZH		('1')				// [49]���ʽ��˺�
#define TDX_FLAG_LRP_JYDCG		('2')				// [50]���ö���
#define TDX_FLAG_LRP_YSZMB		('3')				// [51]�������ܱ�
#define TDX_FLAG_LRP_JQWBD		('4')				// [52]����δ��
#define TDX_FLAG_LRP_YXSFJY		('5')				// [53]�����㷨����
#define TDX_FLAG_LRP_JYBJHG		('6')				// [54]���ñ��ۻع�
#define TDX_FLAG_LRP_YXDZHJGJY	('7')				// [55]������˻���������
#define TDX_FLAG_LRP_YXDZHXGSG	('8')				// [56]������˻��¹��깺
#define TDX_FLAG_LRP_TSGXJYMM	('9')				// [57]��ʾ���½�������
#define TDX_FLAG_LRP_YXZRTJR	('A')				// [65]����ת��ͨ����
#define TDX_FLAG_LRP_YXZRTCJ	('B')				// [66]����ת��ͨ����
#define TDX_FLAG_LRP_YXSYZXTC	('C')				// [67]����ʹ��ר��ͷ��
#define TDX_FLAG_LRP_JZYDHG		('D')				// [68]��ֹԼ���ع�

#define TDX_FLAG_LRP_XGMMXYJY	('a')				// [97]�޸�������ҪУ��
#define TDX_FLAG_LRP_ZQZYHXYJY	('b')				// [98]֤ȯת������ҪУ��
#define TDX_FLAG_LRP_BZHTCTS	('c')				// [99]BתH������ʾ

// ���˺ű�־(TDX_ID_ZZHBZ)
#define TDX_FLAG_ZZHBZ_ASSIST	((BYTE)0)			// ��
#define TDX_FLAG_ZZHBZ_MAIN		((BYTE)1)			// ��
#define TDX_FLAG_ZZHBZ_OTHER	((BYTE)2)			// ����
#define TDX_FLAG_ZZHBZ_NOFUND	((BYTE)97)			// û���ʽ�(������ת)
#define TDX_FLAG_ZZHBZ_NOBANK	((BYTE)98)			// û�����д���
#define TDX_FLAG_ZZHBZ_CANNEL	((BYTE)99)			// ��ע��

// �ֻ��˻�����(TDX_ID_XHZHLX)
#define TDX_FLAG_XHZHLX_DEFAULT	((BYTE)0)			// Ĭ��
#define TDX_FLAG_XHZHLX_NORMAL	((BYTE)1)			// ��ͨ
#define TDX_FLAG_XHZHLX_FUTURES	((BYTE)2)			// �ڻ�
#define TDX_FLAG_XHZHLX_CREDIT	((BYTE)3)			// ����

// �������(TDX_ID_ZHLX)
#define TDX_FLAG_ZHLX_DEFAULT	((BYTE)0)			// Ĭ��
#define TDX_FLAG_ZHLX_CUSTOMER	((BYTE)1)			// �û��Զ���
#define TDX_FLAG_ZHLX_BROKER	((BYTE)2)			// ȯ���Զ���

// ���κ�����(TDX_ID_PCHLX)
#define TDX_FLAG_PCHLX_DEFAULT		((BYTE)0)		// Ĭ��
#define TDX_FLAG_PCHLX_PHASE		((BYTE)1)		// ��������
#define TDX_FLAG_PCHLX_ALPHA		((BYTE)2)		// Alpha����
#define TDX_FLAG_PCHLX_PORTFOLIO	((BYTE)3)		// ��Ʊ���ί��

// Ȩ�ط�ʽ(TDX_ID_QZFS)
#define TDX_FLAG_QZFS_DEFAULT	((BYTE)0)			// Ĭ��
#define TDX_FLAG_QZFS_RATIO		((BYTE)1)			// ����
#define TDX_FLAG_QZFS_QUANTITY	((BYTE)2)			// ����

// ����������׼(TDX_ID_MRJEJSJZ)
#define TDX_FLAG_MRJEJSJZ_DEFAULT	((BYTE)0)		// Ĭ��
#define TDX_FLAG_MRJEJSJZ_AMOUNT	((BYTE)1)		// ���
#define TDX_FLAG_MRJEJSJZ_FUTURES	((BYTE)2)		// �ڻ�
#define TDX_FLAG_MRJEJSJZ_INDEX		((BYTE)3)		// ָ��


//---------------------------------------------------------------------------
// Part.VII ���������ֶ�(����ͷ�ļ����ж���)
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
// Part.VIII �ͻ�������(�Զ�����ʹ��,��ϸ�汾����)(����ͷ�ļ����ж���)
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
// �ͻ�����(����Ӷ�����)
//---------------------------------------------------------------------------
#define CLITYPE_INVALID				0				// δ֪����
#define CLITYPE_INTERNET			12				// ���Ͻ����û�
#define CLITYPE_FLOOR				18				// ���ڽ����û�
#define CLITYPE_WEB					19				// WEB�����û�	
#define CLITYPE_MOBILE				20				// �ƶ������û�
#define CLITYPE_BROKER				21				// �������û�



//---------------------------------------------------------------------------
// Part.IX �ͻ���֧�ֵİ�ȫ�����Լ���֤��ʽ
//---------------------------------------------------------------------------
// ��ȫ������
#define SCLV_SIMPLE					1				// �ʻ���֤��ʽ(��������+��֤��)
#define SCLV_AUTHPASS				2				// �ʻ���֤+��֤���ʽ(��������+��֤����|ͨѶ����,���������밴ť)
#define SCLV_CA						4				// �ʻ���֤+��֤֤�鷽ʽ(���������ļ�֤��,��������+֤������,��֤�����)
#define SCLV_OTP					8				// �ʺ���֤+OTP(��������+��̬����,��ͬ����ť,ȡ�����Ƿ�֧��ͬ��)
#define SCLV_UKEY					16				// �ʺ���֤+UKEY(����Ӳ֤��,��������+֤������,��֤�����)
#define SCLV_RC						32				// �ʺ���֤+����(��������+��֤��)
#define SCLV_MOTP					64				// �ʺ���֤+�ֻ�OTP(��������+��̬����,��ͬ����ť,ȡ�����Ƿ�֧��ͬ��)
#define SCLV_SMSC					128				// �ʺ���֤+���ſ���(֧���κη�ʽ�µ�,��������+��̬����,�л�ȡ��ť)

// ������֧�ֵİ�ȫģʽ
#define TDXSSL_AUTHORITY			0				// ͨ����SSL����
#define AUTHPASS_AUTHORITY			1				// ��֤����
#define DIGITCERT_AUTHORITY			2				// ����֤��(���������ļ�֤��)
#define OTP_AUTHORITY				3				// OTP��֤(�������)
#define UKEY_AUTHORITY				4				// UKEY��֤(����Ӳ֤��)
#define RC_AUTHORITY				5				// ����
#define MOTP_AUTHORITY				6				// �ֻ�OTP
#define SMSC_AUTHORITY				7				// ���ſ���

#define SERVICE_AUTHORITY			64				// ��������(�����ڽ�������ʹ��)
#define QUESTION_AUTHORITY			65				// �ܱ�����(�����ڽ�������ʹ��)
#define SSO_AUTHORITY				66				// SSO��֤(�����ڽ�������ʹ��)
#define CAROLLBACK_AUTHORITY		67				// CA�ع���֤(�����ڽ�������ʹ��,һ�������ⲿ���߻ع�����ʹ��)
#define TELLEROPER_AUTHORITY		68				// ��Ա������֤(�����ڽ�������ʹ��,һ�������ⲿ���ߵ���̨��һ���Բ���)

//����������֧�ֵİ�ȫ��ʽ
#define SCLV_DLWZTS					10				// ��½λ����ʾ
#define SCLV_MMBHWT					11				// ���뱣������
#define SCLV_JQTZMBD				12				// �����������	


//---------------------------------------------------------------------------
// Part.X �������Ͷ���(����ͷ�ļ����ж���)
//---------------------------------------------------------------------------




//---------------------------------------------------------------------------
// Part.XI DLLȯ��ID����
//---------------------------------------------------------------------------
#define NORMAL_DLL						0			// ͨ��
#define	CJZQ_DLL						1			// ����֤ȯ
#define	DYCY_DLL						2			// ��һ��ҵ
#define	DGZQ_DLL						3			// ��ݸ֤ȯ
#define	GXZQ_DLL						4			// ����֤ȯ
#define	HTZQ_DLL						5			// ����֤ȯ
#define	LHZQ_DLL						6			// ����֤ȯ
#define	PAZQ_DLL						7			// ƽ��֤ȯ
#define	TQZQ_DLL						8			// ����֤ȯ
#define	MAZQ_DLL						9			// ��֤ȯ
#define	JQZQ_DLL						10			// ����֤ȯ
#define	TTZQ_DLL						11			// ��֤ͬȯ
#define	GFZQ_DLL						12			// �㷢֤ȯ
#define DTZQ_DLL						13			// ��֤ͨȯ
#define	HXZQ_DLL						14			// ����֤ȯ
#define	XYZQ_DLL						15			// ��ҵ֤ȯ
#define	ZSZQ_DLL						16			// ����֤ȯ
#define	JYZQ_DLL						17			// ��Ԫ֤ȯ
#define	ZXJT_DLL						18			// ���Ž�Ͷ
#define	YNHT_DLL						19			// ����֤ȯ
#define	CCZQ_DLL						20			// ����֤ȯ
#define	HYZQ_DLL						21			// ��Դ֤ȯ
#define	GTJA_DLL						22			// ��̩����
#define	SJZQ_DLL						23			// ����֤ȯ
#define	AXZQ_DLL						24			// ����֤ȯ
#define	CFZQ_DLL						25			// �Ƹ�֤ȯ
#define	DXZQ_DLL						26			// ����֤ȯ(����֤ȯ)
#define	YHZQ_DLL						27			// ����֤ȯ
#define	GDZQ_DLL						28			// ���֤ȯ
#define YDZQ_DLL						29			// Ӣ��֤ȯ
#define DBZQ_DLL						30			// �°�֤ȯ
#define	NJZQ_DLL						31			// �Ͼ�֤ȯ
#define ZXZQ_DLL						32			// ����֤ȯ
#define SHZQ_DLL						33			// �Ϻ�֤ȯ
#define HBZQ_DLL						34			// ����֤ȯ
#define AJZQ_DLL						35			// ����֤ȯ
#define QLZQ_DLL						36			// ��³֤ȯ
#define ZYGJ_DLL						37			// ��������
#define MZZQ_DLL						38			// ����֤ȯ
#define XCZQ_DLL						39			// ���֤ȯ
#define GJZQ_DLL						40			// ����֤ȯ
#define SCZQ_DLL						41			// �״�֤ȯ
#define GLZQ_DLL						42			// ����֤ȯ
#define HLZQ_DLL						43			// ����֤ȯ
#define HFZQ_DLL						44			// ����֤ȯ
#define GYZQ_DLL						45			// ��Ԫ֤ȯ
#define GZZQ_DLL						46			// ����֤ȯ
#define FZZQ_DLL						47			// ����֤ȯ
#define BHZQ_DLL						48			// ����֤ȯ
#define XNZQ_DLL						49			// ����֤ȯ
#define XSDZQ_DLL						50			// ��ʱ��֤ȯ
#define ZTZQ_DLL						51			// ��Ͷ֤ȯ
#define HRZQ_DLL						52			// ����֤ȯ
#define SYWG_DLL						53			// �������
#define SHHX_DLL						54			// ����֤ȯ
#define NJHT_DLL						55			// ��̩֤ȯ
#define JLDB_DLL						56			// ����֤ȯ
#define MSZQ_DLL						57			// ����֤ȯ
#define SXDT_DLL						58			// ��֤ͬȯ
#define ZCZQ_DLL						59			// �ڳ�֤ȯ
#define XMZQ_DLL						60			// ����֤ȯ
#define DFZQ_DLL						61			// ����֤ȯ
#define YTZQ_DLL						62			// ��̩֤ȯ
#define ZXGJHK_DLL						63			// ���Ź���HK
#define GDKGHK_DLL						64			// ���ع�HK
#define ZSXGHK_DLL						65			// �������HK
#define BDZQHK_DLL						66			// ����֤ȯHK
#define JNZQ_DLL						67			// ����֤ȯ
#define WHZQ_DLL						68			// ���֤ȯ
#define HKZQ_DLL						69			// ����֤ȯ
#define ZXWT_DLL						70			// ������ͨ
#define XDZQ_DLL						71			// �Ŵ�֤ȯ
#define WKZQ_DLL						72			// ���֤ȯ
#define JHZQ_DLL						73			// ����֤ȯ
#define HCZQ_DLL						74			// ����֤ȯ
#define TPYZQ_DLL						75			// ̫ƽ��֤ȯ
#define GHZQ_DLL						76			// ����֤ȯ
#define DHZQ_DLL						77			// ����֤ȯ
#define XBZQ_DLL						78			// ����֤ȯ
#define SXZQ_DLL						79			// ɽ��֤ȯ
#define KYZQ_DLL						80			// ��Դ֤ȯ
#define HAZQ_DLL						81			// ����֤ȯ
#define GXZQHK_DLL						82			// ����֤ȯHK
#define GSZQ_DLL						83			// ��ʢ֤ȯ
#define ZJZXJT_DLL						84			// ���Ž�ͨ
#define SCHX_DLL						85			// ����֤ȯ
#define XHJHK_DLL						86			// �º��HK
#define QFZQHK_DLL						87			// �ȷ�֤ȯHK
#define RFZQHK_DLL						88			// �շ�֤ȯHK
#define WLZQ_DLL						89			// ����֤ȯ
#define LNZT_DLL						90			// ����֤ȯ
#define XDGJHK_DLL						91			// �Ŵ����HK
#define NMHT_DLL						92			// ��̩֤ȯ
#define TFZQ_DLL						93			// ���֤ȯ
#define GSHL_DLL						94			// ����֤ȯ
#define RXZQ_DLL						95			// ����֤ȯ
#define ZHZQ_DLL						96			// �к�֤ȯ
#define DFXGHK_DLL						97			// �������HK
#define CTZQ_DLL						98			// ��֤ͨȯ
#define YFJHK_DLL						99			// �����HK
#define NFJJ_DLL						100			// �Ϸ�����
#define YXZQHK_DLL						101			// Խ��֤ȯHK
#define SHHT_DLL						102			// ��֤ͨȯ
#define DWZQ_DLL						103			// ����֤ȯ
#define ZJZS_DLL						104			// ����֤ȯ
#define JDTZHK_DLL						105			// ���Ͷ��HK
#define LXZQ_DLL						106			// ��Ѷ֤ȯ
#define CFLA_DLL						107			// �Ƹ��ﰺ
#define GYXGHK_DLL						108			// ��Ԫ���HK
#define XZTX_DLL						109			// ����ͬ��
#define ZYZQ_DLL						110			// ��ԭ֤ȯ
#define BJGD_DLL						111			// ����֤ȯ
#define QLGJHK_DLL						112			// ��³����HK
#define JHZQHK_DLL						113			// ���֤ȯHK
#define ZJZQ_DLL						114			// �н�֤ȯ

#define	MAX_QSID						114			// ���ȯ��ID

#if !defined(NO_QSIDS)

typedef struct tagQSIDInfo
{
	DWORD	dwQSID;
	CHAR	szQSSX[6+1];
	CHAR	szQSMC[12+1];
} QSID_INFO, *LPQSID_INFO;

const QSID_INFO tdxQSIDInfo[]=
{
//	ȯ��ID		ȯ��ƴ����д(���6�ֽ�)	ȯ�̺�������(���6����)
	{	NORMAL_DLL,	"",						"",					},
	{	CJZQ_DLL,	"CJZQ",					"����֤ȯ",			},
	{	DYCY_DLL,	"DYCY",					"��һ��ҵ",			},
	{	DGZQ_DLL,	"DGZQ",					"��ݸ֤ȯ",			},
	{	GXZQ_DLL,	"GXZQ",					"����֤ȯ",			},
	{	HTZQ_DLL,	"HTZQ",					"����֤ȯ",			},
	{	LHZQ_DLL,	"LHZQ",					"����֤ȯ",			},
	{	PAZQ_DLL,	"PAZQ",					"ƽ��֤ȯ",			},
	{	TQZQ_DLL,	"TQZQ",					"����֤ȯ",			},
	{	MAZQ_DLL,	"MAZQ",					"��֤ȯ",			},
	{	JQZQ_DLL,	"JQZQ",					"����֤ȯ",			},
	{	TTZQ_DLL,	"TTZQ",					"��֤ͬȯ",			},
	{	GFZQ_DLL,	"GFZQ",					"�㷢֤ȯ",			},
	{	DTZQ_DLL,	"DTZQ",					"��֤ͨȯ",			},
	{	HXZQ_DLL,	"HXZQ",					"����֤ȯ",			},
	{	XYZQ_DLL,	"XYZQ",					"��ҵ֤ȯ",			},
	{	ZSZQ_DLL,	"ZSZQ",					"����֤ȯ",			},
	{	JYZQ_DLL,	"JYZQ",					"��Ԫ֤ȯ",			},
	{	ZXJT_DLL,	"ZXJT",					"���Ž�Ͷ",			},
	{	YNHT_DLL,	"YNHT",					"����֤ȯ",			},
	{	CCZQ_DLL,	"CCZQ",					"����֤ȯ",			},
	{	HYZQ_DLL,	"HYZQ",					"��Դ֤ȯ",			},
	{	GTJA_DLL,	"GTJA",					"��̩����",			},
	{	SJZQ_DLL,	"SJZQ",					"����֤ȯ",			},
	{	AXZQ_DLL,	"AXZQ",					"����֤ȯ",			},
	{	CFZQ_DLL,	"CFZQ",					"�Ƹ�֤ȯ",			},
	{	DXZQ_DLL,	"DXZQ",					"����֤ȯ",			},
	{	YHZQ_DLL,	"YHZQ",					"����֤ȯ",			},
	{	GDZQ_DLL,	"GDZQ",					"���֤ȯ",			},
	{	YDZQ_DLL,	"YDZQ",					"Ӣ��֤ȯ",			},
	{	DBZQ_DLL,	"DBZQ",					"�°�֤ȯ",			},
	{	NJZQ_DLL,	"NJZQ",					"�Ͼ�֤ȯ",			},
	{	ZXZQ_DLL,	"ZXZQ",					"����֤ȯ",			},
	{	SHZQ_DLL,	"SHZQ",					"�Ϻ�֤ȯ",			},
	{	HBZQ_DLL,	"HBZQ",					"����֤ȯ",			},
	{	AJZQ_DLL,	"AJZQ",					"����֤ȯ",			},
	{	QLZQ_DLL,	"QLZQ",					"��³֤ȯ",			},
	{	ZYGJ_DLL,	"ZYGJ",					"��������",			},
	{	MZZQ_DLL,	"MZZQ",					"����֤ȯ",			},
	{	XCZQ_DLL,	"XCZQ",					"���֤ȯ",			},
	{	GJZQ_DLL,	"GJZQ",					"����֤ȯ",			},
	{	SCZQ_DLL,	"SCZQ",					"�״�֤ȯ",			},
	{	GLZQ_DLL,	"GLZQ",					"����֤ȯ",			},
	{	HLZQ_DLL,	"HLZQ",					"����֤ȯ",			},
	{	HFZQ_DLL,	"HFZQ",					"����֤ȯ",			},
	{	GYZQ_DLL,	"GYZQ",					"��Ԫ֤ȯ",			},
	{	GZZQ_DLL,	"GZZQ",					"����֤ȯ",			},
	{	FZZQ_DLL,	"FZZQ",					"����֤ȯ",			},
	{	BHZQ_DLL,	"BHZQ",					"����֤ȯ",			},
	{	XNZQ_DLL,	"XNZQ",					"����֤ȯ",			},
	{	XSDZQ_DLL,	"XSDZQ",				"��ʱ��֤ȯ",		},
	{	ZTZQ_DLL,	"ZTZQ",					"��Ͷ֤ȯ",			},
	{	HRZQ_DLL,	"HRZQ",					"����֤ȯ",			},
	{	SYWG_DLL,	"SYWG",					"�������",			},
	{	SHHX_DLL,	"SHHX",					"����֤ȯ",			},
	{	NJHT_DLL,	"NJHT",					"��̩֤ȯ",			},
	{	JLDB_DLL,	"JLDB",					"����֤ȯ",			},
	{	MSZQ_DLL,	"MSZQ",					"����֤ȯ",			},
	{	SXDT_DLL,	"SXDT",					"��֤ͬȯ",			},
	{	ZCZQ_DLL,	"ZCZQ",					"�ڳ�֤ȯ",			},
	{	XMZQ_DLL,	"XMZQ",					"����֤ȯ",			},
	{	DFZQ_DLL,	"DFZQ",					"����֤ȯ",			},
	{	YTZQ_DLL,	"YTZQ",					"��̩֤ȯ",			},
	{	ZXGJHK_DLL,	"ZXGJHK",				"���Ź���HK",		},
	{	GDKGHK_DLL,	"GDKGHK",				"���ع�HK",		},
	{	ZSXGHK_DLL,	"ZSXGHK",				"�������HK",		},
	{	BDZQHK_DLL,	"BDZQHK",				"����֤ȯHK",		},
	{	JNZQ_DLL,	"JNZQ",					"����֤ȯ",			},
	{	WHZQ_DLL,	"WHZQ",					"���֤ȯ",			},
	{	HKZQ_DLL,	"HKZQ",					"����֤ȯ",			},
	{	ZXWT_DLL,	"ZXWT",					"������ͨ",			},
	{	XDZQ_DLL,	"XDZQ",					"�Ŵ�֤ȯ",			},
	{	WKZQ_DLL,	"WKZQ",					"���֤ȯ",			},
	{	JHZQ_DLL,	"JHZQ",					"����֤ȯ",			},
	{	HCZQ_DLL,	"HCZQ",					"����֤ȯ",			},
	{	TPYZQ_DLL,	"TPYZQ",				"̫ƽ��֤ȯ",		},
	{	GHZQ_DLL,	"GHZQ",					"����֤ȯ",			},
	{	DHZQ_DLL,	"DHZQ",					"����֤ȯ",			},
	{	XBZQ_DLL,	"XBZQ",					"����֤ȯ",			},
	{	SXZQ_DLL,	"SXZQ",					"ɽ��֤ȯ",			},
	{	KYZQ_DLL,	"KYZQ",					"��Դ֤ȯ",			},
	{	HAZQ_DLL,	"HAZQ",					"����֤ȯ",			},
	{	GXZQHK_DLL,	"GXZQHK",				"����֤ȯHK",		},
	{	GSZQ_DLL,	"GSZQ",					"��ʢ֤ȯ",			},
	{	ZJZXJT_DLL,	"ZJZXJT",				"���Ž�ͨ",			},
	{	SCHX_DLL,	"SCHX",					"����֤ȯ",			},
	{	XHJHK_DLL,	"XHJHK",				"�º��HK",			},
	{	QFZQHK_DLL,	"QFZQHK",				"�ȷ�֤ȯHK",		},
	{	RFZQHK_DLL,	"RFZQHK",				"�շ�֤ȯHK",		},
	{	WLZQ_DLL,	"WLZQ",					"����֤ȯ",			},
	{	LNZT_DLL,	"LNZT",					"����֤ȯ",			},
	{	XDGJHK_DLL,	"XDGJHK",				"�Ŵ����HK",		},
	{	NMHT_DLL,	"NMHT",					"��̩֤ȯ",			},
	{	TFZQ_DLL,	"TFZQ",					"���֤ȯ",			},
	{	GSHL_DLL,	"GSHL",					"����֤ȯ",			},
	{	RXZQ_DLL,	"RXZQ",					"����֤ȯ",			},
	{	ZHZQ_DLL,	"ZHZQ",					"�к�֤ȯ",			},
	{	DFXGHK_DLL,	"DFXGHK",				"�������HK",		},
	{	CTZQ_DLL,	"CTZQ",					"��֤ͨȯ",			},
	{	YFJHK_DLL,	"YFJHK",				"�����HK",			},
	{	NFJJ_DLL,	"NFJJ",					"�Ϸ�����",			},
	{	YXZQHK_DLL,	"YXZQHK",				"Խ��֤ȯHK",		},
	{	SHHT_DLL,	"SHHT",					"��֤ͨȯ",			},
	{	DWZQ_DLL,	"DWZQ",					"����֤ȯ",			},
	{	ZJZS_DLL,	"ZJZS",					"����֤ȯ",			},
	{	JDTZHK_DLL,	"JDTZHK",				"���Ͷ��HK",		},
	{	LXZQ_DLL,	"LXZQ",					"��Ѷ֤ȯ",			},
	{	CFLA_DLL,	"CFLA",					"�Ƹ��ﰺ",			},
	{	GYXGHK_DLL,	"GYXGHK",				"��Ԫ���HK",		},
	{	XZTX_DLL,	"XZTX",					"����ͬ��",			},
	{	ZYZQ_DLL,	"ZYZQ",					"��ԭ֤ȯ",			},
	{	BJGD_DLL,	"BJGD",					"����֤ȯ",			},
	{	QLGJHK_DLL,	"QLGJHK",				"��³����HK",		},
	{	JHZQHK_DLL,	"JHZQHK",				"���֤ȯHK",		},
	{	ZJZQ_DLL,	"ZJZQ",					"�н�֤ȯ",			},
};

inline LPCSTR GetQsName( DWORD dwQSID )
{
	for ( LONG i=0; i<(LONG)(sizeof(tdxQSIDInfo)/sizeof(QSID_INFO)); i++ )
	{
		if ( dwQSID == tdxQSIDInfo[i].dwQSID ) return tdxQSIDInfo[i].szQSMC;
	}
	return "";
}

inline LPCSTR GetQssx( DWORD dwQSID )
{
	for ( LONG i=0; i<(LONG)(sizeof(tdxQSIDInfo)/sizeof(QSID_INFO)); i++ )
	{
		if ( dwQSID == tdxQSIDInfo[i].dwQSID ) return tdxQSIDInfo[i].szQSSX;
	}
	return "";
}

#endif

//---------------------------------------------------------------------------
// Part.XII �г���Ϣ�ṹ(����ͷ�ļ����ж���)
//---------------------------------------------------------------------------
#ifndef MARKETINFO_TYPE
#define MARKETINFO_TYPE
	// ��Ʒ���
	enum enumSPLB
	{	SPLB_ZS=1,			// ָ��
		SPLB_AG=2,			// A��
		SPLB_AGQZ=3,		// A��Ȩ֤
		SPLB_AGTP=4,		// A��ͶƱ
		SPLB_AGQZXQ=5,		// A��Ȩ֤��Ȩ
		SPLB_BG=6,			// B��
		SPLB_BGQZ=7,		// B��Ȩ֤
		SPLB_BGTP=8,		// B��ͶƱ
		SPLB_BGQZXQ=9,		// B��Ȩ֤��Ȩ
		SPLB_ZF=10,			// ����
		SPLB_PS=11,			// ����
		SPLB_PZ=12,			// ��ծ
		SPLB_PG=13,			// ���
		SPLB_ZXB=14,		// ��С��
		SPLB_ZXBTP=15,		// ��С��ͶƱ
		SPLB_SBRMB=16,		// ���������
		SPLB_XSBRMB=17,		// �����������
		SPLB_SBMY=18,		// ������Ԫ
		SPLB_SBGY=19,		// �����Ԫ
		SPLB_GZ=20,			// ��ծ
		SPLB_QZ=21,			// ��ծ
		SPLB_ZZ=22,			// תծ
		SPLB_FZ=23,			// ��ծ
		SPLB_ZG=24,			// ת��
		SPLB_GZZYHG=25,		// ��ծ��Ѻ�ع�
		SPLB_QZZYHG=26,		// ��ծ��Ѻ�ع�
		SPLB_GZMDSHG=27,	// ��ծ���ʽ�ع�
		SPLB_GZXZYHG=28,	// ��ծ����Ѻ�ع�
		SPLB_GZXZYHGSB=29,	// ��ծ����Ѻ�걨
		SPLB_QTHG=30,		// �����ع�
		SPLB_FBJJ=31,		// ��ջ���
		SPLB_KFSJJ=32,		// ���Ż���
		SPLB_KFSJJGN=33,	// ��������
		SPLB_ETF=34,		// ETF����
		SPLB_LOF=35,		// LOF����
		SPLB_GZFX=36,		// ��ծ��������
		SPLB_QT=37,			// ����
		SPLB_BZH=38,		// BתH
	};
	// ���ֱ�ʶ
	enum enumBZBS
	{	BZ_RMB=0,		// �����
		BZ_MY=1,		// ��Ԫ
		BZ_GY=2,		// �۱�

		BZ_CNY=BZ_RMB,	// �����
		BZ_USD=BZ_MY,	// ��Ԫ
		BZ_HKD=BZ_GY,	// ��Ԫ
		BZ_EUR=3,		// ŷԪ
		BZ_JPY=4,		// ��Ԫ
		BZ_SGD=5,		// �¼���Ԫ
		BZ_AUD=6,		// ��Ԫ
		BZ_CAD=7,		// ��Ԫ
		BZ_GBP=8,		// Ӣ��
		BZ_IDR=9,		// ӡ���
		BZ_MYR=10,		// ��Ԫ
		BZ_NOK=11,		// Ų������
		BZ_THB=12,		// ̩��
		BZ_TWD=13,		// ��̨��
		BZ_PHP=14,		// ���ɱ�����
	};
	// ��ծ��ʶ
	enum enumGZBS
	{	GZBS_NULL=-1,	// �ǹ�ծ
		GZBS_GZXH=0,	// ��ծ�ֻ�
		GZBS_QZ=1,		// ��ҵծ
		GZBS_ZZ=2,		// ��תծ
		GZBS_GZHG=3,	// ��ծ�ع�
	};
#endif
	
	
	
	//---------------------------------------------------------------------------
	// Part.XIII ���ܵ��ýӿ�(����ͷ�ļ����ж���)
	//---------------------------------------------------------------------------
	// ҵ�񷵻�
	enum enumDICTRET
	{	DICTRET_PROC_SUCCESS=0,			// ���ܵ��óɹ�
		DICTRET_PROC_FAIL=-1,			// ���ܵ��ó������
		DICTRET_FATAL_FAIL=-2,			// �����ֵ���������
		DICTRET_LOGIN_SCNTR_FAIL=-3,	// ����(��¼����)����,��ȫ��¼����(�ʺŴ�������������)
		DICTRET_LOGIN_FAIL=-4,			// ����(��¼����)����,��¼����(�ʺŴ�������������)
		DICTRET_PROC_KICKOUT=-5,		// ���ܵ���,���߳�(����ͬ�ʺŵ�¼,�ȵ�¼�߱��߳�)
		DICTRET_PROC_SQLBUSY=-6,		// ���ܵ���,���ݿⷱæ
		DICTRET_PROC_LINKBUSY=-7,		// ���ܵ���,��·����
		DICTRET_PROC_WARNING=-8,		// ���ܵ���,���ܾ���
		DICTRET_LOGIN_NOTVIP=-9,		// ����(��¼����)����,��VIP�ͻ���¼VIP��վ����
		DICTRET_LOGIN_GETSMS=-10,		// ����(��¼����)����,��ȡ�ֻ�����(�ɹ�)
	};
	
	
	// ��׼����ź�(PROTERR)
	// ������ת�����Э�鶨��ͷ�ļ�
	// �Ѱ���Э�����ͷֽ�����Э�鶨�塣
	
	// ��ֲ��VS2005
#ifdef WIN32
#pragma warning (pop)
#endif
	
#endif

