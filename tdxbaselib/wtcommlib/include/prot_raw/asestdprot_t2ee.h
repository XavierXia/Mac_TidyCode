//////////////////////////////////////////////////////////////////////////
// TP和TSERVER协议规范定义文件
// 1.TP和TSERVER协议定义  (协议号范围: 2000-3000)
#ifndef __ASE_STDPROT_T2EE__H__
#define __ASE_STDPROT_T2EE__H__
#pragma pack(1)
#if defined(_COMPILE_BY_MSC_)
	#pragma warning(push)
	#pragma warning(disable:4200)
#endif


// 基本协议和协议段
STD_PROT SHORT T2EE_ALIVE	=	0;						// T2EE存活包
STD_PROT SHORT T2EE_FIRST	=	2000;					// T2EE协议号起始
STD_PROT SHORT T2EE_LAST	=	2999;					// T2EE协议号截止



// HTTP请求
STD_PROT SHORT T2EE_HTTP				= 2007;
// 执行SQL命令的请求
STD_PROT SHORT T2EE_COMMAND				= 2008;
// 更新文件的请求
STD_PROT SHORT T2EE_FILEUPDATE			= 2009;
// 获取统计信息的请求
STD_PROT SHORT T2EE_STAT				= 2010;
// 数据操作代码起始
STD_PROT SHORT T2EE_DATAOPBEGIN			= 2011;
// 数据添加或者更新请求
STD_PROT SHORT T2EE_DATAADD				= T2EE_DATAOPBEGIN+0;
// 数据删除请求
STD_PROT SHORT T2EE_DATADELETE			= T2EE_DATAOPBEGIN+1;
// 数据写盘请求
STD_PROT SHORT T2EE_DATAFLUSH			= T2EE_DATAOPBEGIN+2;
// 查询数据表空间请求
STD_PROT SHORT T2EE_DATASPACE			= T2EE_DATAOPBEGIN+3;
// 获取表的时间戳
STD_PROT SHORT T2EE_DATAGETTIME			= T2EE_DATAOPBEGIN+4;
// delete语句
STD_PROT SHORT T2EE_SQLDELETE			= T2EE_DATAOPBEGIN+5;
// update语句
STD_PROT SHORT T2EE_SQLUPDATE			= T2EE_DATAOPBEGIN+6;
// insert语句
STD_PROT SHORT T2EE_SQLINSERT			= T2EE_DATAOPBEGIN+7;
// 设置表的时间戳
STD_PROT SHORT T2EE_DATASETTIME			= T2EE_DATAOPBEGIN+8;
// sql统计
STD_PROT SHORT T2EE_SQLSTAT				= T2EE_DATAOPBEGIN+9;
// FileMgr Reload
STD_PROT SHORT T2EE_FMRELOAD			= T2EE_DATAOPBEGIN+10;
// 递加表的时间戳
STD_PROT SHORT T2EE_DATAINCTIME			= T2EE_DATAOPBEGIN+11;
// 调用存储过程
STD_PROT SHORT T2EE_CALL_TQL			= T2EE_DATAOPBEGIN+12;
// 重新加载存储过程
STD_PROT SHORT T2EE_RELOADTQL			= T2EE_DATAOPBEGIN+13;
// 数据获取
STD_PROT SHORT T2EE_DATAGET				= T2EE_DATAOPBEGIN+14;
// 数据操作代码结束
STD_PROT SHORT T2EE_DATAOPEND			= T2EE_DATAOPBEGIN+14;

// 获取统计信息的请求
STD_PROT SHORT T2EE_BALANCE				= 2200;

// 握手请求
STD_PROT SHORT T2EE_TOUCH				= 2201;

// 密钥交换请求
STD_PROT SHORT T2EE_SESSIONKEY			= 2202;

// 获取统计信息的请求(因冲突废弃)
STD_PROT SHORT SRV_STAT_REQ				= 2010;
// 上传文件
STD_PROT SHORT SRV_FILE_UPLOAD1_REQ		= 2500;
STD_PROT SHORT SRV_FILE_UPLOAD2_REQ		= 2501;
// 下载文件
STD_PROT SHORT SRV_FILE_DOWNLOAD_REQ	= 2502;
// 删除文件
STD_PROT SHORT SRV_FILE_DELETE_REQ		= 2503;
// 重新加载文件
STD_PROT SHORT SRV_FILE_RELOAD_REQ		= 2504;
// 列出文件
STD_PROT SHORT SRV_FILE_LIST_REQ		= 2505;

// 脚本调用
STD_PROT SHORT T2EE_CALL_TJS			= 2999;















// 一级路由信息头(支持路由的协议)
typedef struct tagROUTEIB
{	BYTE m_cPartition;					// 功能分区
	BYTE m_cReserved;					// 保留字节
	BYTE m_cMSFlag;						// 标志
	CHAR m_szEntry[48];					// 功能名
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

// 记录号
typedef __int64 __RecIDT;

// 验证请求
struct t2ee_authenticated_req
{	short			ReqNo;								// 请求号
	char			MagicStr[MAX_SQL_MAGIC_SIZE];		// 待验证字符串
};

// 数据操作应答
struct t2ee_dataop_ans
{
	char			result;								// 操作返回的结果
};

// SQL条件单个条件结构
typedef struct tagSIGCOND
{	unsigned char	nFieldId;							// 字段ID
	unsigned char	nCompareType;						// 比较类型
	unsigned char	FieldType;							// 字段类型
	unsigned int	FieldLen;							// 字段长度
	unsigned int	FieldOffset;						// 字段偏移
	char Conditions[MAX_SQL_CONDITION_LEN];				// 具体条件(整形,浮点直接转换)
} SIGCOND;

















// HTTP请求(T2EE_HTTP)
struct t2ee_http_req
{	short			ReqNo;
	char			sServer[32];
	unsigned short	nPort;
	int				nHttpReqLen;		// HTTP报文长度
	char			strHttpReq[1];		// HTTP报文
};









// 具体查询请求结构(T2EE_COMMAND)
// nOptionSize索引的options字段可以包含多个表字段的或条件
// 格式如下:FieldID(unsigned char)+len(short)+内容+'\0'
// 内容为这个FieldId对应的多条查询条件 以逗号分隔
// 例如 gzsh9000458,gzsh9000459,gzsh9000460,gzsh9000461,gzsh9000462,gzsh9000463
// 多字段示例 nOptionSize如下
// 1个字段:FieldID(unsigned char)+len(short)+内容+'\0'
// 2个字段:FieldID(unsigned char)+len(short)+内容+'\0'
// 3个字段:FieldID(unsigned char)+len(short)+内容+'\0'
struct t2ee_command_req : public t2ee_authenticated_req
{
	short			MagicNum;							// 魔数
	short			nOptionSize;						// 后跟Option 或条件
	unsigned int	nPage;								// 页序号
	unsigned short	nPageFrame;							// 页框大小取值范围[0,MAX_SEND_LINE],等于0 查询全部nPage不起作用.
	unsigned char	nSortFieldID;						// 排序字段ID 字段ID为0 不参与排序
	unsigned char	nSortWay;							// 排序方向 ASC=0(升序) DESC=1(降序)
	unsigned char	nDistinctFieldID;					// 等于0 不排除重复
	int				TableId;
	unsigned char	FieldIds[MAX_SQL_REQ_FIELDCOUNT];
	unsigned char	nFieldNum;
	SIGCOND			pCond[MAX_SQL_CONDITION_CNT];
	unsigned char	nCondNum;
};




// 文件更新(T2EE_FILEUPDATE)
// 如果不需要更新,那么返回长度0
struct t2ee_fileupdata_req
{
	short			ReqNo;				// 请求号
	char			strMD5[32];			// 文件的MD5
	int				nFileNameLen;		// 文件名长度
	char			strFilename[1];		// 文件名称
};

struct t2ee_fileupdata_ans
{
	char			pBuf[1];			// 具体文件数据
};



// 查询服务器状态(T2EE_STAT)
struct t2ee_stat_req : public t2ee_authenticated_req
{
};

struct t2ee_stat_ans
{
	char			OpenTime[14];		// 服务器开启时间 格式YYYYMMDDHHMMSS
	unsigned int	CurConnects;		// 当前连接数量
	unsigned int	TotalConnects;		// 总计连接数量
	double			TotalSendbyte;		// 总计发包BYTE
	double			TotalRecvbyte;		// 总计收包BYTE
	char			BeginStat[14];		// 单位时间起始 格式YYYYMMDDHHMMSS
	char			EndStat[14];		// 单位时间结束 格式YYYYMMDDHHMMSS
	unsigned int	Connects;			// 单位时间内的连接数量
	double			Sendbyte;			// 单位时间内的发送BYTE
	double			Recvbyte;			// 单位时间内的接受BYTE
	unsigned int	index;				// 引用计数
};


// 插入数据(T2EE_DATAADD)
// 包后面包含了需要更新或者添加的一条数据内容和tat内容 添加还是更新要看RecID是否能再表中找到
struct t2ee_dataadd_req : public t2ee_authenticated_req
{
	int				TableID;			// 表ID
	unsigned int	RowNum;				// 插入的绝对行号,服务器不解析,用于旁路模块
	__RecIDT		RecID;				// 需要更新或者添加的RecID
	char			bBack;				// 是否末尾插入
	unsigned int	ContentSize;		// 更新信息内容的长度
};



// 数据删除(T2EE_DATADELETE)
// 包后面结构如下 DelNum个的recID sizeof(recID)==sizeof(__RecIDT)
struct t2ee_datadel_req : public t2ee_authenticated_req
{
	int				TableID;			// 表ID
	unsigned int	DelNum;				// 需要删除表ID的个数
};



// 数据写盘(T2EE_DATAFLUSH)
struct t2ee_dataflush_req : public t2ee_authenticated_req
{
	int				TableID;			// 表ID
};



// 磁盘空间查询(T2EE_DATASPACE)
struct t2ee_dataspace_req : public t2ee_authenticated_req
{
	unsigned int	page;				// 请求的页码
};

// 应答头部是t2ee_dataop_ans 后面跟着result+int(t2ee_dataspace_ans count)+t2ee_dataspace_ans*count
struct t2ee_dataspace_ans
{
	char			TableName[48];		// 表名称
	unsigned int	TableSize;			// 表大小   单位字节
	unsigned int	RemainSize;			// 空闲大小 单位字节
};




// 请求数据时间(T2EE_DATAGETTIME)
// 请求的返回信息 t2ee_dataop_ans+__int64(Timestamp)
struct t2ee_datagettime_req
{
	short			ReqNo;				//请求号
	int				TableID;			//表ID
};


// 数据删除(T2EE_SQLDELETE)
// T2EE_SQLDELETE请求的返回信息 t2ee_dataop_ans+t2ee_sqlnoselect_ans
struct t2ee_sqldelete_req : public t2ee_authenticated_req
{
	int				TableId;							// 表ID
	SIGCOND			pCond[MAX_SQL_CONDITION_CNT];
	unsigned char	nCondNum;
};



// 数据更新(T2EE_SQLUPDATE)
// 请求后面还跟着ContentSize个字节的内容
// 请求的返回信息 t2ee_dataop_ans+t2ee_sqlnoselect_ans
struct t2ee_sqlupdate_req : public t2ee_authenticated_req
{
	int				TableId;							// 表ID
	unsigned char	FieldIds[MAX_SQL_REQ_FIELDCOUNT];
	unsigned char	nFieldNum;
	SIGCOND			pCond[MAX_SQL_CONDITION_CNT];
	unsigned char	nCondNum;
	unsigned int	ContentSize;						// 更新信息内容的长度
};





// 数据插入(T2EE_SQLINSERT)
// 请求后面还跟着ContentSize个字节的内容
// 请求的返回信息 t2ee_dataop_ans+t2ee_sqlnoselect_ans
struct t2ee_sqlinsert_req : public t2ee_authenticated_req
{
	int				TableId;							// 表ID
	unsigned char	FieldIds[MAX_SQL_REQ_FIELDCOUNT];
	unsigned char	nFieldNum;
	char			bBack;								// 是否末尾插入
	unsigned int	ContentSize;						// 插入信息内容的长度
};


struct t2ee_sqlnoselect_ans
{
	// 1.delete 为删除条数的数量
	// 2.update 为更新条数的数量
	// 3.insert 为添加条数的数量(因为一个insert语句只能添加一条,所以插入成功后返回1失败为0)
	// 4.select count 为给定相对条件对应数据库中的条数
	unsigned int	nCount;
};


// 数据时间修订(T2EE_DATASETTIME)
// 请求的返回信息t2ee_dataop_ans
struct t2ee_datasettime_req : public t2ee_authenticated_req
{
	int				TableId;							// 表ID
	__int64			Timestamp;							// 设置的时间戳
};




// SQL统计(T2EE_SQLSTAT)
// 请求的返回信息 t2ee_dataop_ans[+字段类型(short)+字段长度(int)+内容]
struct t2ee_sqlstat_req
{
	short			ReqNo;								// 请求号
	int				TableId;							// 表ID
	unsigned char	StatType;							// 请求的类型 SQL_STAT_TYPE_XXX
	unsigned char	FieldId;							// 请求的字段
	SIGCOND			pCond[MAX_SQL_CONDITION_CNT];
	unsigned char	nCondNum;
	unsigned char	bDistinctField;						// 是否排除重复 0为不排除
	short			nOptionSize;						// 后跟Option 或条件
};


// 文件管理重新装载(T2EE_FMRELOAD)
struct t2ee_fmreload_req
{
	short			ReqNo;				// 请求号
	char			strMD5[32];			// 文件的MD5
};







// 递加表的时间戳(T2EE_DATAINCTIME)
// 请求的返回信息 t2ee_dataop_ans+sizeof(__int64)
struct t2ee_datainctime_req : public t2ee_authenticated_req
{
	int				TableId;							// 表ID
};




// 调用存储过程(调用存储过程)
// 请求返回的信息t2ee_dataop_ans[+具体内容]
struct t2ee_calltql_req
{
	short			m_wReqNoVerify;						// 请求号
	char			tqlname[MAX_TQL_NAME_LEN+1];		// TQL名称
	short			nOptionSize;						// 后跟Option
};


// 重新装载脚本(T2EE_RELOADTQL)
// 请求返回的信息t2ee_dataop_ans
struct t2ee_reloadtql_req : public t2ee_authenticated_req
{
	char			tqlname[MAX_TQL_NAME_LEN+1];		// TQL名称
};


// 数据获取(T2EE_DATAGET)
// 如果能够得到数据,返回一个t2ee_dataadd_req结构,否则只返回一个包头
struct t2ee_dataget_req : public t2ee_authenticated_req
{
	int				TableID;							// 表ID
	__RecIDT		RecID;
};




// 均衡请求(T2EE_BALANCE)
struct t2ee_balance_req
{
};
struct t2ee_balance_ans
{
	unsigned int CurConnects; //当前连接数量
	unsigned int LicenseConnects; //许可连接数量
};


// 握手请求(T2EE_TOUCH)
struct t2ee_touch_req
{	IPV4	m_EthernetIp;			// 客户端私网IP
	MAC		m_Mac;					// 客户端MAC
	WORD	m_wClientType;			// 客户端类型
	DWORD	m_dwClientVer;			// 客户端版本
	BYTE	m_cEncryptLv:2;			// 加密级别(0:不加密 1:BLOWFIS加密 2:DES3加密 3: SSL加密)	// TP版本>2.10.147
	BYTE	m_cReserved:6;			// 保留字节
};
struct t2ee_touch_ans
{	IPV4	m_InternetIp;			// 客户端公网IP
	BYTE	m_cEncryptLv:2;			// 加密级别(0:不加密 1:BLOWFIS加密 2:DES3加密 3: SSL加密)	// TP版本>=2.10.147
	BYTE	m_cReserved:6;			// 保留字节(为增扩SSL预留)
};
struct t2ee_touch_v2_ans : public t2ee_touch_ans
{	BYTE	m_acSeq[0];				// 数据缓冲区(密钥<STRING>|ETC)								// TP版本>=2.10.147
};

// 密钥交换(T2EE_SESSIONKEY)
struct t2ee_sessionkey_req
{	IPV4	m_InetIp;				// 客户端公网IP
	BYTE	m_cReserved;			// 保留字节(为增扩SSL预留)
};
struct t2ee_sessionkey_ans
{	BYTE	m_cReserved;			// 保留字节(为增扩SSL预留)
};


// 脚本调用(T2EE_CALL_TJS)
struct t2ee_calltjs_req
{	WORD	m_wReqNoVerify;			// 请求号
	DWORD	m_dwOptionSize;			// 选项长度
};

struct t2ee_calltjs_ans
{
};















//////////////////////////////////////////////////////////////////////////
// Part.III 应用级异常错误号
// (T2EE架构部分)
// (参见:ASEStd_Prot.Err.h)
#if defined(_COMPILE_BY_MSC_)
	#pragma warning(pop)
#endif
#pragma pack()
#endif
