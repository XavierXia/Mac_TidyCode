//////////////////////////////////////////////////////////////////////////
// TP��TSERVERЭ��淶�����ļ�
// 1.TP��TSERVERЭ�鶨��  (Э��ŷ�Χ: 2000-3000)
#ifndef __ASE_STDPROT_T2EE__H__
#define __ASE_STDPROT_T2EE__H__
#pragma pack(1)
#if defined(_COMPILE_BY_MSC_)
	#pragma warning(push)
	#pragma warning(disable:4200)
#endif


// ����Э���Э���
STD_PROT SHORT T2EE_ALIVE	=	0;						// T2EE����
STD_PROT SHORT T2EE_FIRST	=	2000;					// T2EEЭ�����ʼ
STD_PROT SHORT T2EE_LAST	=	2999;					// T2EEЭ��Ž�ֹ



// HTTP����
STD_PROT SHORT T2EE_HTTP				= 2007;
// ִ��SQL���������
STD_PROT SHORT T2EE_COMMAND				= 2008;
// �����ļ�������
STD_PROT SHORT T2EE_FILEUPDATE			= 2009;
// ��ȡͳ����Ϣ������
STD_PROT SHORT T2EE_STAT				= 2010;
// ���ݲ���������ʼ
STD_PROT SHORT T2EE_DATAOPBEGIN			= 2011;
// ������ӻ��߸�������
STD_PROT SHORT T2EE_DATAADD				= T2EE_DATAOPBEGIN+0;
// ����ɾ������
STD_PROT SHORT T2EE_DATADELETE			= T2EE_DATAOPBEGIN+1;
// ����д������
STD_PROT SHORT T2EE_DATAFLUSH			= T2EE_DATAOPBEGIN+2;
// ��ѯ���ݱ�ռ�����
STD_PROT SHORT T2EE_DATASPACE			= T2EE_DATAOPBEGIN+3;
// ��ȡ���ʱ���
STD_PROT SHORT T2EE_DATAGETTIME			= T2EE_DATAOPBEGIN+4;
// delete���
STD_PROT SHORT T2EE_SQLDELETE			= T2EE_DATAOPBEGIN+5;
// update���
STD_PROT SHORT T2EE_SQLUPDATE			= T2EE_DATAOPBEGIN+6;
// insert���
STD_PROT SHORT T2EE_SQLINSERT			= T2EE_DATAOPBEGIN+7;
// ���ñ��ʱ���
STD_PROT SHORT T2EE_DATASETTIME			= T2EE_DATAOPBEGIN+8;
// sqlͳ��
STD_PROT SHORT T2EE_SQLSTAT				= T2EE_DATAOPBEGIN+9;
// FileMgr Reload
STD_PROT SHORT T2EE_FMRELOAD			= T2EE_DATAOPBEGIN+10;
// �ݼӱ��ʱ���
STD_PROT SHORT T2EE_DATAINCTIME			= T2EE_DATAOPBEGIN+11;
// ���ô洢����
STD_PROT SHORT T2EE_CALL_TQL			= T2EE_DATAOPBEGIN+12;
// ���¼��ش洢����
STD_PROT SHORT T2EE_RELOADTQL			= T2EE_DATAOPBEGIN+13;
// ���ݻ�ȡ
STD_PROT SHORT T2EE_DATAGET				= T2EE_DATAOPBEGIN+14;
// ���ݲ����������
STD_PROT SHORT T2EE_DATAOPEND			= T2EE_DATAOPBEGIN+14;

// ��ȡͳ����Ϣ������
STD_PROT SHORT T2EE_BALANCE				= 2200;

// ��������
STD_PROT SHORT T2EE_TOUCH				= 2201;

// ��Կ��������
STD_PROT SHORT T2EE_SESSIONKEY			= 2202;

// ��ȡͳ����Ϣ������(���ͻ����)
STD_PROT SHORT SRV_STAT_REQ				= 2010;
// �ϴ��ļ�
STD_PROT SHORT SRV_FILE_UPLOAD1_REQ		= 2500;
STD_PROT SHORT SRV_FILE_UPLOAD2_REQ		= 2501;
// �����ļ�
STD_PROT SHORT SRV_FILE_DOWNLOAD_REQ	= 2502;
// ɾ���ļ�
STD_PROT SHORT SRV_FILE_DELETE_REQ		= 2503;
// ���¼����ļ�
STD_PROT SHORT SRV_FILE_RELOAD_REQ		= 2504;
// �г��ļ�
STD_PROT SHORT SRV_FILE_LIST_REQ		= 2505;

// �ű�����
STD_PROT SHORT T2EE_CALL_TJS			= 2999;















// һ��·����Ϣͷ(֧��·�ɵ�Э��)
typedef struct tagROUTEIB
{	BYTE m_cPartition;					// ���ܷ���
	BYTE m_cReserved;					// �����ֽ�
	BYTE m_cMSFlag;						// ��־
	CHAR m_szEntry[48];					// ������
} ROUTEIB;



#define MAX_SQL_REQ_FIELDCOUNT			200
#define MAX_SQL_CONDITION_LEN			50
#define MAX_SQL_CONDITION_CNT			5
#define MAX_SQL_OPTION_SIZE				8000
#define MAX_SQL_MAGIC_SIZE				50
#define MAX_DATASPACE_PER_PAGE_COUNT	80
#define MAX_TQL_NAME_LEN				30

#define DATA_OP_OK						0
#define DATA_OP_DATA_ERR				1
#define DATA_OP_MONITOR_ERR				2
#define DATA_OP_DATABASE_FULL			3
#define DATA_OP_DATASPACE_ERR			4
#define DATA_OP_DATABASE_BUSY			5

#define MAX_DATA_OP_DEL_NUM				1000
#define MAX_DATA_OP_ADD_CONTENT_SIZE	8000

#define SQL_STAT_TYPE_COUNT				0
#define SQL_STAT_TYPE_MAX				1
#define SQL_STAT_TYPE_MIN				2
#define SQL_STAT_TYPE_AVG				3
#define SQL_STAT_TYPE_SUM				4

// ��¼��
typedef __int64 __RecIDT;

// ��֤����
struct t2ee_authenticated_req
{	short			ReqNo;								// �����
	char			MagicStr[MAX_SQL_MAGIC_SIZE];		// ����֤�ַ���
};

// ���ݲ���Ӧ��
struct t2ee_dataop_ans
{
	char			result;								// �������صĽ��
};

// SQL�������������ṹ
typedef struct tagSIGCOND
{	unsigned char	nFieldId;							// �ֶ�ID
	unsigned char	nCompareType;						// �Ƚ�����
	unsigned char	FieldType;							// �ֶ�����
	unsigned int	FieldLen;							// �ֶγ���
	unsigned int	FieldOffset;						// �ֶ�ƫ��
	char Conditions[MAX_SQL_CONDITION_LEN];				// ��������(����,����ֱ��ת��)
} SIGCOND;

















// HTTP����(T2EE_HTTP)
struct t2ee_http_req
{	short			ReqNo;
	char			sServer[32];
	unsigned short	nPort;
	int				nHttpReqLen;		// HTTP���ĳ���
	char			strHttpReq[1];		// HTTP����
};









// �����ѯ����ṹ(T2EE_COMMAND)
// nOptionSize������options�ֶο��԰���������ֶεĻ�����
// ��ʽ����:FieldID(unsigned char)+len(short)+����+'\0'
// ����Ϊ���FieldId��Ӧ�Ķ�����ѯ���� �Զ��ŷָ�
// ���� gzsh9000458,gzsh9000459,gzsh9000460,gzsh9000461,gzsh9000462,gzsh9000463
// ���ֶ�ʾ�� nOptionSize����
// 1���ֶ�:FieldID(unsigned char)+len(short)+����+'\0'
// 2���ֶ�:FieldID(unsigned char)+len(short)+����+'\0'
// 3���ֶ�:FieldID(unsigned char)+len(short)+����+'\0'
struct t2ee_command_req : public t2ee_authenticated_req
{
	short			MagicNum;							// ħ��
	short			nOptionSize;						// ���Option ������
	unsigned int	nPage;								// ҳ���
	unsigned short	nPageFrame;							// ҳ���Сȡֵ��Χ[0,MAX_SEND_LINE],����0 ��ѯȫ��nPage��������.
	unsigned char	nSortFieldID;						// �����ֶ�ID �ֶ�IDΪ0 ����������
	unsigned char	nSortWay;							// ������ ASC=0(����) DESC=1(����)
	unsigned char	nDistinctFieldID;					// ����0 ���ų��ظ�
	int				TableId;
	unsigned char	FieldIds[MAX_SQL_REQ_FIELDCOUNT];
	unsigned char	nFieldNum;
	SIGCOND			pCond[MAX_SQL_CONDITION_CNT];
	unsigned char	nCondNum;
};




// �ļ�����(T2EE_FILEUPDATE)
// �������Ҫ����,��ô���س���0
struct t2ee_fileupdata_req
{
	short			ReqNo;				// �����
	char			strMD5[32];			// �ļ���MD5
	int				nFileNameLen;		// �ļ�������
	char			strFilename[1];		// �ļ�����
};

struct t2ee_fileupdata_ans
{
	char			pBuf[1];			// �����ļ�����
};



// ��ѯ������״̬(T2EE_STAT)
struct t2ee_stat_req : public t2ee_authenticated_req
{
};

struct t2ee_stat_ans
{
	char			OpenTime[14];		// ����������ʱ�� ��ʽYYYYMMDDHHMMSS
	unsigned int	CurConnects;		// ��ǰ��������
	unsigned int	TotalConnects;		// �ܼ���������
	double			TotalSendbyte;		// �ܼƷ���BYTE
	double			TotalRecvbyte;		// �ܼ��հ�BYTE
	char			BeginStat[14];		// ��λʱ����ʼ ��ʽYYYYMMDDHHMMSS
	char			EndStat[14];		// ��λʱ����� ��ʽYYYYMMDDHHMMSS
	unsigned int	Connects;			// ��λʱ���ڵ���������
	double			Sendbyte;			// ��λʱ���ڵķ���BYTE
	double			Recvbyte;			// ��λʱ���ڵĽ���BYTE
	unsigned int	index;				// ���ü���
};


// ��������(T2EE_DATAADD)
// �������������Ҫ���»�����ӵ�һ���������ݺ�tat���� ��ӻ��Ǹ���Ҫ��RecID�Ƿ����ٱ����ҵ�
struct t2ee_dataadd_req : public t2ee_authenticated_req
{
	int				TableID;			// ��ID
	unsigned int	RowNum;				// ����ľ����к�,������������,������·ģ��
	__RecIDT		RecID;				// ��Ҫ���»�����ӵ�RecID
	char			bBack;				// �Ƿ�ĩβ����
	unsigned int	ContentSize;		// ������Ϣ���ݵĳ���
};



// ����ɾ��(T2EE_DATADELETE)
// ������ṹ���� DelNum����recID sizeof(recID)==sizeof(__RecIDT)
struct t2ee_datadel_req : public t2ee_authenticated_req
{
	int				TableID;			// ��ID
	unsigned int	DelNum;				// ��Ҫɾ����ID�ĸ���
};



// ����д��(T2EE_DATAFLUSH)
struct t2ee_dataflush_req : public t2ee_authenticated_req
{
	int				TableID;			// ��ID
};



// ���̿ռ��ѯ(T2EE_DATASPACE)
struct t2ee_dataspace_req : public t2ee_authenticated_req
{
	unsigned int	page;				// �����ҳ��
};

// Ӧ��ͷ����t2ee_dataop_ans �������result+int(t2ee_dataspace_ans count)+t2ee_dataspace_ans*count
struct t2ee_dataspace_ans
{
	char			TableName[48];		// ������
	unsigned int	TableSize;			// ���С   ��λ�ֽ�
	unsigned int	RemainSize;			// ���д�С ��λ�ֽ�
};




// ��������ʱ��(T2EE_DATAGETTIME)
// ����ķ�����Ϣ t2ee_dataop_ans+__int64(Timestamp)
struct t2ee_datagettime_req
{
	short			ReqNo;				//�����
	int				TableID;			//��ID
};


// ����ɾ��(T2EE_SQLDELETE)
// T2EE_SQLDELETE����ķ�����Ϣ t2ee_dataop_ans+t2ee_sqlnoselect_ans
struct t2ee_sqldelete_req : public t2ee_authenticated_req
{
	int				TableId;							// ��ID
	SIGCOND			pCond[MAX_SQL_CONDITION_CNT];
	unsigned char	nCondNum;
};



// ���ݸ���(T2EE_SQLUPDATE)
// ������滹����ContentSize���ֽڵ�����
// ����ķ�����Ϣ t2ee_dataop_ans+t2ee_sqlnoselect_ans
struct t2ee_sqlupdate_req : public t2ee_authenticated_req
{
	int				TableId;							// ��ID
	unsigned char	FieldIds[MAX_SQL_REQ_FIELDCOUNT];
	unsigned char	nFieldNum;
	SIGCOND			pCond[MAX_SQL_CONDITION_CNT];
	unsigned char	nCondNum;
	unsigned int	ContentSize;						// ������Ϣ���ݵĳ���
};





// ���ݲ���(T2EE_SQLINSERT)
// ������滹����ContentSize���ֽڵ�����
// ����ķ�����Ϣ t2ee_dataop_ans+t2ee_sqlnoselect_ans
struct t2ee_sqlinsert_req : public t2ee_authenticated_req
{
	int				TableId;							// ��ID
	unsigned char	FieldIds[MAX_SQL_REQ_FIELDCOUNT];
	unsigned char	nFieldNum;
	char			bBack;								// �Ƿ�ĩβ����
	unsigned int	ContentSize;						// ������Ϣ���ݵĳ���
};


struct t2ee_sqlnoselect_ans
{
	// 1.delete Ϊɾ������������
	// 2.update Ϊ��������������
	// 3.insert Ϊ�������������(��Ϊһ��insert���ֻ�����һ��,���Բ���ɹ��󷵻�1ʧ��Ϊ0)
	// 4.select count Ϊ�������������Ӧ���ݿ��е�����
	unsigned int	nCount;
};


// ����ʱ���޶�(T2EE_DATASETTIME)
// ����ķ�����Ϣt2ee_dataop_ans
struct t2ee_datasettime_req : public t2ee_authenticated_req
{
	int				TableId;							// ��ID
	__int64			Timestamp;							// ���õ�ʱ���
};




// SQLͳ��(T2EE_SQLSTAT)
// ����ķ�����Ϣ t2ee_dataop_ans[+�ֶ�����(short)+�ֶγ���(int)+����]
struct t2ee_sqlstat_req
{
	short			ReqNo;								// �����
	int				TableId;							// ��ID
	unsigned char	StatType;							// ��������� SQL_STAT_TYPE_XXX
	unsigned char	FieldId;							// ������ֶ�
	SIGCOND			pCond[MAX_SQL_CONDITION_CNT];
	unsigned char	nCondNum;
	unsigned char	bDistinctField;						// �Ƿ��ų��ظ� 0Ϊ���ų�
	short			nOptionSize;						// ���Option ������
};


// �ļ���������װ��(T2EE_FMRELOAD)
struct t2ee_fmreload_req
{
	short			ReqNo;				// �����
	char			strMD5[32];			// �ļ���MD5
};







// �ݼӱ��ʱ���(T2EE_DATAINCTIME)
// ����ķ�����Ϣ t2ee_dataop_ans+sizeof(__int64)
struct t2ee_datainctime_req : public t2ee_authenticated_req
{
	int				TableId;							// ��ID
};




// ���ô洢����(���ô洢����)
// ���󷵻ص���Ϣt2ee_dataop_ans[+��������]
struct t2ee_calltql_req
{
	short			m_wReqNoVerify;						// �����
	char			tqlname[MAX_TQL_NAME_LEN+1];		// TQL����
	short			nOptionSize;						// ���Option
};


// ����װ�ؽű�(T2EE_RELOADTQL)
// ���󷵻ص���Ϣt2ee_dataop_ans
struct t2ee_reloadtql_req : public t2ee_authenticated_req
{
	char			tqlname[MAX_TQL_NAME_LEN+1];		// TQL����
};


// ���ݻ�ȡ(T2EE_DATAGET)
// ����ܹ��õ�����,����һ��t2ee_dataadd_req�ṹ,����ֻ����һ����ͷ
struct t2ee_dataget_req : public t2ee_authenticated_req
{
	int				TableID;							// ��ID
	__RecIDT		RecID;
};




// ��������(T2EE_BALANCE)
struct t2ee_balance_req
{
};
struct t2ee_balance_ans
{
	unsigned int CurConnects; //��ǰ��������
	unsigned int LicenseConnects; //�����������
};


// ��������(T2EE_TOUCH)
struct t2ee_touch_req
{	IPV4	m_EthernetIp;			// �ͻ���˽��IP
	MAC		m_Mac;					// �ͻ���MAC
	WORD	m_wClientType;			// �ͻ�������
	DWORD	m_dwClientVer;			// �ͻ��˰汾
	BYTE	m_cEncryptLv:2;			// ���ܼ���(0:������ 1:BLOWFIS���� 2:DES3���� 3: SSL����)	// TP�汾>2.10.147
	BYTE	m_cReserved:6;			// �����ֽ�
};
struct t2ee_touch_ans
{	IPV4	m_InternetIp;			// �ͻ��˹���IP
	BYTE	m_cEncryptLv:2;			// ���ܼ���(0:������ 1:BLOWFIS���� 2:DES3���� 3: SSL����)	// TP�汾>=2.10.147
	BYTE	m_cReserved:6;			// �����ֽ�(Ϊ����SSLԤ��)
};
struct t2ee_touch_v2_ans : public t2ee_touch_ans
{	BYTE	m_acSeq[0];				// ���ݻ�����(��Կ<STRING>|ETC)								// TP�汾>=2.10.147
};

// ��Կ����(T2EE_SESSIONKEY)
struct t2ee_sessionkey_req
{	IPV4	m_InetIp;				// �ͻ��˹���IP
	BYTE	m_cReserved;			// �����ֽ�(Ϊ����SSLԤ��)
};
struct t2ee_sessionkey_ans
{	BYTE	m_cReserved;			// �����ֽ�(Ϊ����SSLԤ��)
};


// �ű�����(T2EE_CALL_TJS)
struct t2ee_calltjs_req
{	WORD	m_wReqNoVerify;			// �����
	DWORD	m_dwOptionSize;			// ѡ���
};

struct t2ee_calltjs_ans
{
};















//////////////////////////////////////////////////////////////////////////
// Part.III Ӧ�ü��쳣�����
// (T2EE�ܹ�����)
// (�μ�:ASEStd_Prot.Err.h)
#if defined(_COMPILE_BY_MSC_)
	#pragma warning(pop)
#endif
#pragma pack()
#endif
