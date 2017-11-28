//////////////////////////////////////////////////////////////////////////
// 标准协议规范定义文件
// 本文件定义:
//		1.协议封包重要标志(加密压缩)
//		2.标准协议头(可选,使用EXCLUDE_STD_PACKET_HEADER可屏蔽)
//			a.4.X协议头定义(行情主站,资讯主站,委托中继和网关)
//			b.CW.协议头定义(财务主站)
//			c.5.X协议头定义(交易中心,IMServer等)
//			d.7.X协议头定义
#ifndef __ASE_STDPROT_HEADER__H__
#define __ASE_STDPROT_HEADER__H__
// 协议部分,使用1字节对齐
#pragma pack(1)



// 加密级别(参阅: SafeVCRT_Types.h)
#ifndef ENCRYPTLV_DEFINED
	#define ENCRYPTLV_DEFINED
	typedef enum enumENCRYPTLV
	{	ENCRYPTLV_NONE,								// 加密级别: 不加密
		ENCRYPTLV_LL,								// 加密级别: 低级别,对称加密(服务器选择是否交换密钥)
		ENCRYPTLV_SSL,								// 加密级别: 高级别,SSL加密
	} ENCRYPTLV;
#endif

// 加密标志(参阅: SafeVCRT_Types.h)
#ifndef ENCRYPTTYPE_DEFINED
	#define ENCRYPTTYPE_DEFINED
	typedef enum enumENCRYPTTYPE
	{	ENCRYPTTYPE_NO,								// 未加密
		ENCRYPTTYPE_SESSION,						// 使用SESSION_KEY加密
		ENCRYPTTYPE_BLOWFISH,						// 使用BLOWFISH加密
		ENCRYPTTYPE_DES3,							// 使用DES3加密
	} ENCRYPTTYPE;
#endif


// 压缩模式(参阅: SafeVCRT_Types.h)
#ifndef COMPRESSMODE_DEFINED
	#define COMPRESSMODE_DEFINED
	typedef enum enumCOMPRESSMODE
	{	COMPRESS_NONE,								// 不做压缩
		COMPRESS_SMART,								// 智能压缩(大数据包压缩)
		COMPRESS_FULL,								// 完全压缩(全部事务均压缩)
	} COMPRESSMODE;
#endif


// 压缩类别(参阅: SafeVCRT_Types.h)
#ifndef COMPRESSTYPE_DEFINED
	#define COMPRESSTYPE_DEFINED
	typedef enum enumCOMPRESSTYPE
	{	COMPRESSTYPE_NONE,							// 不做压缩
		COMPRESSTYPE_GZIP,							// 使用GZIP压缩
		COMPRESSTYPE_DEFLATE,						// 使用DEFLATE压缩
		COMPRESSTYPE_ZLIB,							// 使用ZLIB压缩
		COMPRESSTYPE_MAX=COMPRESSTYPE_ZLIB,			// 压缩类型最大值
	} COMPRESSTYPE;
#endif


// 消息类别(参阅: SafeVCRT_Types.h)
#ifndef MSGTYPE_DEFINED
	#define MSGTYPE_DEFINED
	typedef enum enumMSGTYPE
	{	MSGTYPE_ROSE,								// ROSE协议
		MSGTYPE_RROSE,								// RROSE协议
		MSGTYPE_PUSHING,							// 推送
		MSGTYPE_UNKNOWN,							// 未知
	} MSGTYPE;
	#define MSGTYPE_DEFAULT MSGTYPE_ROSE
#endif




// 协议头定义(可使用EXCLUDE_STD_PACKET_HEADER进行屏蔽)
#ifndef EXCLUDE_STD_PACKET_HEADER

	//////////////////////////////////////////////////////////////////////////
	// 4.X协议头部定义(行情主站,交易中继,交易网关使用的协议)
	#if !defined(STD_PACKET_HEADER_4X) && (!defined(SELECT_PROT_SPEC)||defined(SELECT_PROT_4X))
		#define STD_PACKET_HEADER_4X
		// 请求结构定义
		typedef struct tagREQHEADER4X
		{	struct
			{	BYTE Version:4;								// 协议版本
				BYTE Compressed:1;							// 压缩标志
				BYTE Encrypted:1;							// SESSION加密标志
				BYTE IsMobile:1;							// 手机炒股标志
				BYTE Reserved:1;							// 保留位
			} Info;
			SHORT MainID;
			SHORT AssisID;
			char Priority;
			WORD PacketLen;
			WORD RawLen;
		} REQHEADER4X;
		typedef REQHEADER4X* LPREQHEADER4X;
		// 应答结构定义
		typedef struct tagANSHEADER4X
		{	DWORD Separator;								// 分割数字,用于拆分应答包处理,正常包头必须是SEPARATOR_NUM
			struct tagINFO
			{	BYTE Version:4;								// 协议版本
				BYTE Compressed:1;							// 是否压缩
				BYTE Encrypted:1;							// SESSION加密标志
				BYTE Reserved:2;							// 保留位
			} Info;
			SHORT MainID;									// 请求主ID
			SHORT AssisID;									// 请求辅ID
			char  Reserved;									// 保留字节(恒为0,原优先级字段)
			SHORT req;										// 请求号
			WORD PacketLen;									// 包长度(数据体,不包含包头和可扩展包头)
			WORD RawLen;									// 原始包长度(数据体,不包含包头和可扩展包头)
		} ANSHEADER4X;
		typedef ANSHEADER4X* LPANSHEADER4X;
	#endif


	//////////////////////////////////////////////////////////////////////////
	// 财务主站协议
	#if !defined(STD_PACKET_HEADER_CW) && (!defined(SELECT_PROT_SPEC)||defined(SELECT_PROT_CW))
		#define STD_PACKET_HEADER_CW
		// 请求结构定义
		typedef struct tagREQHEADERCW
		{	struct
			{	BYTE Version:4;								// 协议版本
				BYTE Compressed:1;							// 压缩标志
				BYTE Encrypted:1;							// SESSION加密标志
				BYTE Encrypted2:1;							// 加密标志
				BYTE Reserved:1;							// 保留位
			} Info;
			SHORT MainID;
			SHORT AssisID;
			BYTE Priority;
			UINT PacketLen;
			UINT RawLen;
		} REQHEADERCW;
		typedef REQHEADERCW* LPREQHEADERCW;
		// 应答结构定义
		typedef struct tagANSHEADERCW
		{	DWORD Separator;								// 分割数字,用于拆分应答包处理,正常包头必须是SEPARATOR_NUM
			struct tagINFO
			{	BYTE Version:4;								// 协议版本
				BYTE Compressed:1;							// 是否压缩
				BYTE Encrypted:1;							// SESSION加密标志
				BYTE Encrypted2:1;							// 加密标志
				BYTE Reserved:1;							// 保留位
			} Info;
			SHORT MainID;									// 请求主ID
			SHORT AssisID;									// 请求辅ID
			CHAR  Reserved;									// 保留字节(恒为0,原优先级字段)
			SHORT req;										// 请求号
			UINT PacketLen;									// 包长度(数据体,不包含包头和可扩展包头)
			UINT RawLen;									// 原始包长度(数据体,不包含包头和可扩展包头)
			UINT Process;									// 进度信息
		} ANSHEADERCW;
		typedef ANSHEADERCW* LPANSHEADERCW;
	#endif


	//////////////////////////////////////////////////////////////////////////
	// 5.X协议头部定义(交易中心,IMServer等使用的协议)
	#if !defined(STD_PACKET_HEADER_5X) && (!defined(SELECT_PROT_SPEC)||defined(SELECT_PROT_5X))
		#define STD_PACKET_HEADER_5X
		// 请求头信息,从当前版本开始协议头将具备伸缩性
		// 请求通过OptionLen检查扩展包头长度,最长不超过256字节
		// 这些包头信息用于系统级别扩展,可兼容原有部分升级信息相关协议
		// 报文头另外可扩展加密算法报文
		typedef struct tagREQHEADER5X
		{	struct tagINFO
			{	BYTE Version:4;							// 协议版本
				BYTE Compressed:1;						// 是否压缩
				BYTE EncryptType:3;						// 加密类型		
			} Info;
			DWORD TransKey;								// 请求唯一标识
			BYTE OptionLen;								// 选项区长度(老协议为优先级字段,恒为0)
			WORD PacketLen;								// 包长度(数据体,不包含包头和可扩展包头)
			WORD RawLen;								// 包的原始长度(数据体,不包含包头和可扩展包头)
			WORD ReqNo;									// 请求序号
		} REQHEADER5X;
		typedef REQHEADER5X* LPREQHEADER5X;
		// 应答头信息,标准应答信息
		typedef struct tagANSHEADER5X
		{	DWORD Separator;							// 包分割序号(SEPARATOR_NUM)
			struct tagINFO
			{	BYTE Version:4;							// 协议版本
				BYTE Compressed:1;						// 是否压缩
				BYTE EncryptType:3;						// 加密类型
			} Info;
			DWORD TransKey;								// 请求唯一标识
			BYTE Reserved;								// 保留位,全空
			WORD ReqNo;									// 请求号
			WORD PacketLen;								// 包长度(数据体,不包含包头和可扩展包头)
			WORD RawLen;								// 原始包长度(数据体,不包含包头和可扩展包头)
		} ANSHEADER5X;
		typedef ANSHEADER5X* LPANSHEADER5X;
		// 隧道协议请求头(加密必须使用)
		typedef struct tagREQHEADERHT5X
		{	BYTE Padding;								// 空数据(0:HTTPX,1:TUNNEL)
			struct tagINFO
			{	BYTE Version:4;							// 协议版本
				BYTE CompressType:2;					// 压缩类型
				BYTE EncryptType:2;						// 加密类型
			} Info;
			UINT64 AspSessionID;						// ASPSESSIONID
			DWORD TransKey;								// 请求唯一标识
			BYTE OptionLen;								// 选项区长度
			WORD RawLen;								// 包的原始长度(数据体,不包含包头,不包含HTTP包头,选项区)
			WORD ReqNo;									// 请求序号
		} REQHEADERHT5X,*LPREQHEADERHT5X;
		// 隧道协议应答头
		typedef struct tagANSHEADERHT5X
		{	struct tagINFO
			{	BYTE Version:4;							// 协议版本
				BYTE CompressType:2;					// 压缩类型
				BYTE EncryptType:2;						// 加密类型
			} Info;
			UINT64 AspSessionID;						// ASPSESSIONID
			DWORD TransKey;								// 请求唯一标识
			WORD RawLen;								// 包的原始长度(数据体,不包含包头,不包含HTTP包头)
			WORD ReqNo;									// 请求序号
			BYTE FragmentNo;							// 分片号
		} ANSHEADERHT5X,*LPANSHEADERHT5X;
		// BUGBUG: HTTPEXTHDR需要处理
	#endif


	//////////////////////////////////////////////////////////////////////////
	// 7.X BETA协议头部定义
	#if !defined(STD_PACKET_HEADER_7BETA) && (!defined(SELECT_PROT_SPEC)||defined(SELECT_PROT_7BETA))
		#define STD_PACKET_HEADER_7BETA
		// 标准请求包结构
		typedef struct tagREQHEADER7BX
		{	struct tagINFO
			{	BYTE Version:4;							// 协议版本
				BYTE CompressType:2;					// 压缩类型
				BYTE EncryptType:2;						// 加密类型		
			} Info;
			DWORD TransKey;								// 请求唯一标识
			BYTE OptionLen;								// 选项区长度
			WORD PacketLen;								// 包长度(数据体,不包含包头,选项区)
			WORD RawLen;								// 包的原始长度(数据体,不包含包头,选项区)
			WORD ReqNo;									// 请求序号
		} REQHEADER7BX;
		typedef REQHEADER7BX* LPREQHEADER7BX;

		// 标准应答包结构
		typedef struct tagANSHEADER7BX
		{	struct tagINFO
			{	BYTE Version:4;							// 协议版本
				BYTE CompressType:2;					// 压缩类型
				BYTE EncryptType:2;						// 加密类型
			} Info;
			DWORD TransKey;								// 请求唯一标识
			WORD ReqNo;									// 请求号
			WORD PacketLen;								// 包长度(数据体,不包含包头,选项区)
			WORD RawLen;								// 原始包长度(数据体,不包含包头,选项区)
			BYTE FragmentNo;							// 分片号
		} ANSHEADER7BX;
		typedef ANSHEADER7BX* LPANSHEADER7BX;

		// 隧道协议请求头(加密必须使用)
		typedef struct tagREQHEADERHT7BX
		{	BYTE Padding;								// 空数据(必须填1,区分HTTP协议和隧道协议)
			struct tagINFO
			{	BYTE Version:4;							// 协议版本
				BYTE CompressType:2;					// 压缩类型
				BYTE EncryptType:2;						// 加密类型
			} Info;
			UINT64 AspSessionID;						// ASPSESSIONID
			DWORD TransKey;								// 请求唯一标识
			BYTE OptionLen;								// 选项区长度
			WORD RawLen;								// 包的原始长度(数据体,不包含包头,不包含HTTP包头,选项区)
			WORD ReqNo;									// 请求序号
		} REQHEADERHT7BX,*LPREQHEADERHT7BX;

		// 隧道协议应答头
		typedef struct tagANSHEADERHT7BX
		{	struct tagINFO
			{	BYTE Version:4;							// 协议版本
				BYTE CompressType:2;					// 压缩类型
				BYTE EncryptType:2;						// 加密类型
			} Info;
			UINT64 AspSessionID;						// ASPSESSIONID
			DWORD TransKey;								// 请求唯一标识
			WORD RawLen;								// 包的原始长度(数据体,不包含包头,不包含HTTP包头)
			WORD ReqNo;									// 请求序号
			BYTE FragmentNo;							// 分片号
		} ANSHEADERHT7BX,*LPANSHEADERHT7BX;
	#endif


	//////////////////////////////////////////////////////////////////////////
	// 7.X 协议头部定义
	#if !defined(STD_PACKET_HEADER_7X) && (!defined(SELECT_PROT_SPEC)||defined(SELECT_PROT_7X))
		#define STD_PACKET_HEADER_7X
		
		// 标准报文头
		typedef struct tagMSGHEADER7X
		{	struct tagINFO
			{	BYTE Version:4;							// 协议版本
				BYTE CompressType:2;					// 压缩类型
				BYTE EncryptType:2;						// 加密类型
			} Info;
			DWORD TransKey;								// 唯一标识
			BYTE OptionLen;								// 选项区长度
			WORD PacketLen;								// 包长度(数据体,不包含包头,选项区)
			WORD RawLen;								// 包的原始长度(数据体,不包含包头,选项区)
			WORD ReqNo;									// 请求序号
			BYTE MsgType;								// 消息类型
			BYTE FragmentNo;							// 分片号
		} MSGHEADER7X;
		typedef MSGHEADER7X* LPMSGHEADER7X;

		// 隧道协议报文头(加密必须使用)
		typedef struct tagMSGHEADERHT7X
		{	BYTE Padding;								// 空数据(必须填1,区分HTTP协议和隧道协议)
			struct tagINFO
			{	BYTE Version:4;							// 协议版本
				BYTE CompressType:2;					// 压缩类型
				BYTE EncryptType:2;						// 加密类型
			} Info;
			UINT64 AspSessionID;						// ASPSESSIONID
			DWORD TransKey;								// 请求唯一标识
			BYTE OptionLen;								// 选项区长度
			WORD RawLen;								// 包的原始长度(数据体,不包含包头,不包含HTTP包头,选项区)
			WORD ReqNo;									// 请求序号
			BYTE MsgType;								// 消息类型
			BYTE FragmentNo;							// 分片号
		} MSGHEADERHT7X,*LPMSGHEADERHT7X;
	#endif


	//////////////////////////////////////////////////////////////////////////
	// 兼容定义
	#ifdef STD_PACKET_HEADER_5X
		typedef REQHEADER5X REQHEADER;
		typedef LPREQHEADER5X LPREQHEADER;
		typedef ANSHEADER5X ANSHEADER;
		typedef LPANSHEADER5X LPANSHEADER;
	#endif

#endif


// 协议版本定义(0,7,8不可用,会存在冲突,这些主要是隧道协议(GET,POST,FIX)
#define PROT_VERSION_SPEC		0						// 特殊协议版本(内部互通,不可用于交换)
#define PROT_VERSION_EXTEND		1						// 扩充主站协议版本
#define PROT_VERSION_5BETA		9						// 标准协议版本(5.X,早期)
#define PROT_VERSION_HSHQ		12						// 沪深行情主站协议版本
#define PROT_VERSION_CW			13						// 财务主站协议版本
#define PROT_VERSION_5X			14						// 标准协议版本(5.X)
#define PROT_VERSION_7BETA1		13						// 标准协议版本(7.X Beta1,兼容旧版TP/TS架构客户端,TCP直连)
#define PROT_VERSION_7BETA2		15						// 标准协议版本(7.X Beta2,兼容旧版MP/MUM架构客户端,TCP直连)
#define PROT_VERSION_7X			11						// 标准协议版本(7.X 标准T架构,TAAPI)
#define PROT_VERSION_UNSPEC		65535					// 无效版本号(不可能出现在传输协议中)

#include "asestdprot_header.inl"


// 恢复原有对齐方式
#pragma pack()

#endif
