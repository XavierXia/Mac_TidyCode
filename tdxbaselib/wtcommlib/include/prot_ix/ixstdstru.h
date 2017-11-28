//////////////////////////////////////////////////////////////////////////
// ASE(Adaptive Server Environment)架构下的标准定义(使用IX协议)
#ifndef __ASE_STDDEF_IX__H__
#define __ASE_STDDEF_IX__H__
#pragma pack(1)

#ifndef STD_IX_HEADER
#define STD_IX_HEADER
	#define STD_IX_HEADER_DEFINED
	typedef struct tagFUNCHDR
	{	BYTE   m_cFuncType;								// 功能类型
		WORD   m_wFuncID;								// 功能ID
		DWORD  m_dwBranchID;							// 营业部编号(验证请求送的是入口点ID,其他请求送的是营业部ID)
		#if defined(ASE_BACKWARD_COMPATIBILITY)
			BYTE   m_szMac[6];							// 客户MAC地址信息
			DWORD  m_dwIP;								// 客户IP地址信息(主机序)
		#else
			MAC    m_Mac;								// 客户MAC地址信息
			IPV4   m_Ip;								// 客户IP地址信息(主机序)
		#endif
		DWORD  m_dwSN;									// 请求包序号
		WORD   m_wBuild;								// 字典编译号
		WORD   m_wVersion;								// 字典版本号
		BYTE   m_szReserved[1];							// 保留字节
		tagFUNCHDR() { memset(this,0,size_of(tagFUNCHDR)); }
	} FUNCHDR,*LPFUNCHDR;
	typedef struct tagFUNCBDY
	{	DWORD	m_dwSize;
		BYTE	m_szBuffer[1];
		tagFUNCBDY() { memset(this,0,size_of(tagFUNCBDY)); }
	} FUNCBDY,*LPFUNCBDY;
#endif


// 兼容处理
#define m_dwRealBranchID m_dwBranchID

#pragma pack()
#endif
