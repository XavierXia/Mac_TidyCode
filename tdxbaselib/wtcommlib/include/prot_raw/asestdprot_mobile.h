//////////////////////////////////////////////////////////////////////////
// 移动终端协议规范定义文件
// 1.移动终端协议基本定义  (协议号范围: 10000-10100)
#ifndef __ASE_STDPROT_MOBILE__H__
#define __ASE_STDPROT_MOBILE__H__
#pragma pack(1)



//////////////////////////////////////////////////////////////////////////
// 功能号定义
STD_PROT WORD MP_TOUCH				= 10000;	// 握手协议(交换密钥,检升级,检通告,检激活,返回服务器时间负载及其他信息)
STD_PROT WORD MP_CONFIRMBIND		= 10001;	// 确认绑定
STD_PROT WORD MP_REBIND				= 10002;	// 重新绑定
STD_PROT WORD MP_FINDSYMBOL			= 10003;	// 搜索股票



//////////////////////////////////////////////////////////////////////////
// 协议结构定义



//////////////////////////////////////////////////////////////////////////
// 应用级异常错误号
// (移动网关部分)
// (参见:ASE_Err.h)



//////////////////////////////////////////////////////////////////////////
// 协议结构定义

// 握手
struct mp_touch_req
{	BYTE	m_cPersistentFlag;				// 0:短连接 1:长连接
	WORD	m_wEntryPointID;				// 入口点ID
	BYTE	m_acReserved[2];				// 保留字节
	IPV4	m_Ip;							// 客户IP地址信息(主机序)
	MAC		m_Mac;							// 客户MAC地址信息
	CHAR	m_szBuildName[16];				// 版本名(如iPad,iPhone,iMac)
	WORD	m_wClientType;					// 客户端类别
	DWORD	m_dwClientVer;					// 客户端版本
	CHAR	m_szTouchKey[17];				// 会话密钥(对称加密:服务器应答数据加密密钥)
	BYTE	m_cConfirmBind;					// 绑定确认
	CHAR	m_szPhoneId[16];				// 电话号码
	CHAR	m_szMachineId[17];				// 机器硬件特征信息
};
struct mp_touch_ans
{	BYTE	m_cFlag;						// 标志
	DWORD	m_dwMaxSession;					// 服务器支持的最大会话数
	DWORD	m_dwNowSession;					// 服务器当前的会话数
	DWORD	m_dwMaxConnect;					// 服务器支持的最大连接数
	DWORD	m_dwNowConnect;					// 服务器当前的连接数
	LONG	m_tStartup;						// 服务器启动时间
	LONG	m_tNow;							// 服务器当前时间
	BYTE	m_cBindStatus;					// 手机绑定状态(0:未知 1:未绑定 2:绑定成功 3:绑定不匹配 4:重复绑定)
	WORD	m_wOptionalLen;					// 选项信息长度
	BYTE	m_acOptional[1];				// 选项信息内容(升级信息,...)
};

// 升级信息格式
//	BYTE		版本状态(0:版本不存在 1:版本太低被拒绝 2:版本强制升级 3:版本建议升级 4:版本已经被禁止 5:版本已经是最新版本)
//	DWORD		版本号
//	STRING		升级URL(需要升级时候有效,非空通过网站升级)
//	STRING		身体提示信息
//	IHASH		补丁标识





// 确认绑定
struct mp_confirmbind_req
{	CHAR	m_szPhoneId[16];				// 电话号码
	CHAR	m_szMachineId[17];				// 机器硬件特征信息
};
struct mp_confirmbind_ans
{	BYTE	m_cBindStatus;					// 手机绑定状态(0:未知 1:未绑定 2:绑定成功 3:绑定不匹配 4:重复绑定)
};
	



// 重新绑定
struct mp_rebind_req
{	CHAR	m_szPhoneId[16];				// 电话号码
};
struct mp_rebind_ans
{	BYTE	m_cStatus;						// 状态(1:成功 0:失败)
};


// 搜索代码
struct mp_findsymbol_req
{	CHAR	m_szCode[7];					// 代码(\0结束)
	LONG	m_nOffset;						// 偏移
	BYTE	m_cWantCount;					// 请求个数
	BYTE	m_bRestrict:1;					// 精确匹配
	BYTE	m_bFindByClass:1;				// 分类查找
	BYTE	m_bFindSHSZ:1;					// 查找深沪市场
	BYTE	m_bFindHK:1;					// 查找港股市场
	BYTE	m_bFindQH:1;					// 查找期货市场
	BYTE	m_cReserved:3;					// 保留字节
};
struct mp_findsymbol_ans
{	BYTE	m_cGotCount;					// 实际读取到的个数
	BYTE	m_cReserved;					// 保留字节
	WORD	m_cbSymbolInfos;				// 符号区长度
	BYTE	m_acSymbolInfos[1];				// 符号区内容
};


#pragma pack()
#endif
