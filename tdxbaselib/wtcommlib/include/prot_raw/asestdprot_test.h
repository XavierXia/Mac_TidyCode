//////////////////////////////////////////////////////////////////////////
// 测试服务协议规范定义文件
// 1.测试服务协议基本定义  (协议号范围: 9800-9900)
#ifndef __ASE_STDPROT_TEST__H__
#define __ASE_STDPROT_TEST__H__
#pragma pack(1)
#if defined(_COMPILE_BY_MSC_)
	#pragma warning(push)
	#pragma warning(disable:4200)
#endif


//////////////////////////////////////////////////////////////////////////
// 功能号定义
STD_PROT WORD TEST_LOGIN			= 9802;		// LOGIN协议(ROSE协议)
STD_PROT WORD TEST_ECHO				= 9805;		// ECHO协议(ROSE协议)
STD_PROT WORD TEST_ENDORSEMENT		= 9806;		// ENDORSEMENT协议(ROSE协议)
STD_PROT WORD TEST_UPLOAD			= 9807;		// UPLOAD协议(ROSE协议,多包)
STD_PROT WORD TEST_DOWNLOAD			= 9808;		// DOWNLOAD协议(ROSE协议,多包)
STD_PROT WORD TEST_LONGTALK			= 9809;		// LONGTALK协议(ROSE协议,多包)


STD_PROT WORD TEST_RECHO			= 9810;		// 反向ECHO协议(ROSE协议)
STD_PROT WORD TEST_RECHOMULTI		= 9811;		// 反向ECHO协议(ROSE协议,多包)
STD_PROT WORD TEST_MQ_IN			= 9812;		// 消息输入(消息队列)
STD_PROT WORD TEST_MQ_OUT			= 9813;		// 消息输出(消息队列)


STD_PROT WORD TEST_HEY				= 9820;		// 推送报文






//////////////////////////////////////////////////////////////////////////
// 应用级异常错误号
// (测试服务协议部分)
// (参见:ASE_Err.h)



//////////////////////////////////////////////////////////////////////////
// 协议结构定义

// LOGIN调用
struct test_login_req
{	CHAR	m_szLoginID[64];				// 账号信息
	CHAR	m_szLoginPass[64];				// 密码信息
};
struct test_login_ans
{	CHAR	m_szUID[64];					// 账号信息
	BYTE	m_cReserved;
};




// ECHO调用
struct test_echo_ropt
{	BYTE	m_cReserved;					// 保留字节
};
struct test_echo_req
{	BYTE	m_cReserved;					// 保留字节
	CHAR	m_szInfo[0];					// 信息数据
};
struct test_echo_aopt
{	BYTE	m_cReserved;					// 保留字节
};
struct test_echo_ans
{	BYTE	m_cReserved;					// 保留字节
	CHAR	m_szUID[32];					// 用户ID
	CHAR	m_szInfo[0];					// 信息数据
};

// ENDORSEMENT调用
struct test_endorsement_ropt
{	BYTE	m_cReserved;					// 保留字节
};
struct test_endorsement_req
{	CHAR	m_szDevice[16];					// 设备名
	IPV6	m_EthernetIp;					// 客户IP(私网)
	IPV6	m_InternetIp;					// 客户IP(公网)
	MAC		m_Mac;							// 客户MAC
	CHAR	m_szBuildName[16];				// 版本编译名
	WORD	m_wClientType;					// 客户端类别
	DWORD	m_dwClientVer;					// 客户端版本
	TCHAR	m_szUID[32];					// 用户ID
	CHAR	m_szInfo[0];					// 信息数据
};
struct test_endorsement_aopt
{	BYTE	m_cReserved;					// 保留字节
};
struct test_endorsement_ans
{	CHAR	m_szInfo[0];					// 信息数据
};



// UPLOAD调用
struct test_upload_req
{	BYTE	m_cTestType;					// 测试类型(0:正常返回 1:异常中止 2:仅返回片段)
	CHAR	m_szAsFile[64];					// 目标文件名
	LONG	m_nLength;						// 文件大小
	LONG	m_nOffset;						// 偏移
	CHAR	m_szInfo[0];					// 数据区
};
struct test_upload_ans
{	BYTE	m_cResult;						// 完成状态
};




// DOWNLOAD调用
struct test_download_req
{	CHAR m_szFile[64];						// 文件名
	LONG m_nOffset;							// 文件偏移
	LONG m_nReadSize;						// 读取大小
};
struct test_download_ans
{	LONG m_nOffset;							// 文件偏移
	CHAR m_szInfo[0];						// 返回的文件信息
};




// LONGTALK调用
struct test_longtalk_ropt
{	BYTE	m_cReserved;					// 保留字节
};
struct test_longtalk_req
{	BYTE	m_cReserved;					// 保留字节
	CHAR	m_szInfo[0];					// 信息数据
};
struct test_longtalk_aopt
{	BYTE	m_cReserved;					// 保留字节
};
struct test_longtalk_ans
{	BYTE	m_cReserved;					// 保留字节
	CHAR	m_szInfo[0];					// 信息数据
};




// HEY调用
struct test_hey_aopt
{	BYTE	m_cReserved;					// 保留字节
};
struct test_hey_ans
{	BYTE	m_cReserved;					// 保留字节
	CHAR	m_szSentence[0];				// 信息
};

#if defined(_COMPILE_BY_MSC_)
	#pragma warning(pop)
#endif
#pragma pack()
#endif
