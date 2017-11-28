//////////////////////////////////////////////////////////////////////////
// 标准协议规范定义文件
// 本文件定义:
//		1.协议的衍生定义,使用EXCLUDE_STD_PACKET_HEADER可全部屏蔽
// 协议号范围:
//		5.X  7.X   		协议号			错误号		说明
//       ◎   ●		0				---			7.X系统:	心跳包(特殊)
//		 NA   ●		100-300	   		---			7.X系统:	协议错误处理和系统推送
//		 --   --		300-2000		---			----------------
//		 ◎   ●		2000-3000		<-20000		T2EE:		业务功能
//		 ●   ◎		3000-4200		<-10000		交易和IM:	业务功能
//		 ●   NA		4200-4400	   	---			5.X系统:	协议错误处理和系统推送
//		 ●   ◎		4400-4450		<-11500		监控:		监控相关协议
//		 ●   NA		4450-4470		---			服务器互联: 共有互联协议段
//	 	 ●   NA		4470-4490		---			服务器互联: 外部互联协议段
//		 ●   NA		4490-4506		---			服务器互联: 内部互联协议段
//		 ●   NA		4506-4510		<-10500			业务集成平台协议段
//		 ●   NA		4510-4560		<-11000			通讯网关协议段
//       ◎   ●		4560-4600		---			RPC调用相关协议
//       ◎   ●		4600-4650		---			RPC桥协议
//		 --   --		4650-9800		---			----------------
//       ◎   ●		9800-9900		---			测试服务
//       ◎   ●		9900-10000		---			基本公网服务(兼容协议部分:3000-4200和桌面端协议号冲突)
//		 ◎   ●		10000-10100		<-12000		移动终端
//		 --   --		10100-inf		---			----------------
#ifndef __ASE_STDPROT_HEADER__INL__
#define __ASE_STDPROT_HEADER__INL__
#pragma pack(1)
#if defined(_COMPILE_BY_MSC_)
	#pragma warning(push)
	#pragma warning(disable:4200)
#endif








#if defined(STD_PACKET_HEADER_5X)

	//////////////////////////////////////////////////////////////////////////
	// 服务器代回协议(对最终用户或服务器)
	//      服务器代回协议主要用于异常处理,即在服务器无法正常响应客户端应答时做出的应急处理
	//      这种应急处理,对于客户端而言是可恢复的,至少可以在适当的情况下大大提高客户端对错误
	//      进行处理的可能性,例如存在DELAY_CLOSE机制,可保障服务器的安全性,同时保障服务器能正
	//      常的讲服务器的错误信息返回给客户端,存在业务超时机制,可避免客户端在业务逻辑发生错
	//      误的情况下依然能够进行恢复到无错误状态,而避免断开网络重新登录连接
	STD_PROT SHORT X5_PROTOCOL_ERROR				= 4200;			// 协议处理发生错误

	//////////////////////////////////////////////////////////////////////////
	// 客户端通知协议(对最终用户)
	//		客户端通知协议为无请求协议,由服务器主动通知,客户端应该在通讯处理底层HOOK相关协议
	//		协议通知总由相关的条件触发,例如服务器无法完成客户端的应答,服务器检测到客户端存在
	//		通知信息等,客户端应该优先处理该信息,以避免对现有业务造成干扰.
	STD_PROT SHORT X5_SERVER_NOTIFY					= 4300;			// 服务器通知(限制协议版本>=5.12.0145)
	STD_PROT SHORT X5_ERROR_NOTIFY					= 4301;			// 错误通知
	STD_PROT SHORT X5_IX_NOTIFY						= 4302;			// 业务通知
	STD_PROT SHORT X5_CALLBOARD_NOTIFY				= 4303;			// 服务器系统通知
	STD_PROT SHORT X5_URGENT_NOTIFY					= 4304;			// 服务器营业部公告通知
	STD_PROT SHORT X5_KICK_NOTIFY					= 4305;			// 踢出通知





	//////////////////////////////////////////////////////////////////////////
	// 协议处理发生非致命错误(X5_PROTOCOL_ERROR)
	struct x5_protocol_error_ans
	{	BYTE		m_cReserved;									// 保留(原协议头,已废弃)
		DWORD		m_dwTransKey;									// 唯一标识(原协议头,保留)
		BYTE		m_acReserved[5];								// 保留(原协议头,已废弃)
		WORD		m_wReqID;										// 协议号(原协议头,保留)
		DWORD		m_dwReserved;									// 保留字节,全空
		LONG		m_nErrorCode;									// 错误代码(尽量避免使用,会增加耦合性)
		WORD		m_wErrorSize;									// 错误信息大小
		CHAR		m_szError[1];									// 错误信息内容
	};

	//////////////////////////////////////////////////////////////////////////
	// 服务器通知(X5_SERVER_NOTIFY,限制协议版本>=5.12.0145)
	struct x5_server_notify
	{	DWORD		m_dwType;										// 类型
		DWORD		m_dwParam;										// 参数数据
		DWORD		m_dwReserved;									// 保留字节,全空
		DWORD		m_dwExtSize;									// 扩展数据项
		BYTE		m_szExtData[1];									// 扩展数据区
	};
	#define X5_SVRNTF_MESSAGE				0						// 服务器消息通知
		#define X5_MSG_MESSAGECONTEXT		0						// 服务器消息通知
	#define MAX_SIZE_SERVERMESSAGE		(4096)						// 最大支持服务器消息长度


	//////////////////////////////////////////////////////////////////////////
	// 服务器错误通知(X5_ERROR_NOTIFY)
	struct x5_error_notify
	{	LONG		m_nErrorCode;									// 错误代码(尽量避免使用,会增加耦合性)
		WORD		m_wErrorSize;									// 错误信息大小
		DWORD		m_dwReserved;									// 保留字节,全空
		CHAR		m_szError[1];									// 错误信息内容
	};



	//////////////////////////////////////////////////////////////////////////
	// 交易事务通知(X5_IX_NOTIFY,限制协议版本>=5.12.0146)
	#ifdef STD_IX_HEADER_DEFINED
		struct x5_ix_notify
		{	FUNCHDR		m_hdr;											// 功能调用头信息
			FUNCBDY		m_bdy;											// 请求数据体
		};
	#endif

	//////////////////////////////////////////////////////////////////////////
	// 公告通知(X5_CALLBOARD_NOTIFY,限制协议版本>=5.12.0150)
	struct x5_callboard_notify {};

	//////////////////////////////////////////////////////////////////////////
	// 公告通知(X5_URGENT_NOTIFY,限制协议版本>=5.12.0150)
	struct x5_urgent_notify {};


	//////////////////////////////////////////////////////////////////////////
	// 踢出通知(X5_KICK_NOTIFY,限制协议版本>=5.12.0191)
	struct x5_kick_notify
	{	BYTE		m_cServId;										// 当前服务器ID
		DWORD		m_idSession;									// 当前会话ID
		systm_t		m_tCreated;										// 当前会话创建时间
		IPV4		m_SourceIp;										// 当前会话来源IP
		WORD		m_wClientType;									// 客户端类型
		DWORD		m_dwClientVer;									// 客户端版本
		IPV4		m_InternetIp;									// IP地址
		MAC			m_Mac;											// MAC地址
		WORD		m_wUOrgID;										// 机构
		CHAR		m_szUID[UID_GSIZE];								// 用户
	};


#endif
	

	
#if defined(STD_PACKET_HEADER_7BETA) || defined(STD_PACKET_HEADER_7X)

	//////////////////////////////////////////////////////////////////////////
	// 服务器代回协议(对最终用户或服务器)
	//      服务器代回协议主要用于异常处理,即在服务器无法正常响应客户端应答时做出的应急处理
	//      这种应急处理,对于客户端而言是可恢复的,至少可以在适当的情况下大大提高客户端对错误
	//      进行处理的可能性,例如存在DELAY_CLOSE机制,可保障服务器的安全性,同时保障服务器能正
	//      常的讲服务器的错误信息返回给客户端,存在业务超时机制,可避免客户端在业务逻辑发生错
	//      误的情况下依然能够进行恢复到无错误状态,而避免断开网络重新登录连接
	STD_PROT SHORT X7_PROTOCOL_ERROR				= 100;			// 协议处理发生错误


	//////////////////////////////////////////////////////////////////////////
	// 客户端通知协议
	//		客户端通知协议为无请求协议,由服务器主动通知,客户端应该在通讯处理底层HOOK相关协议
	//		协议通知总由相关的条件触发,例如服务器无法完成客户端的应答,服务器检测到客户端存在
	//		通知信息等,客户端应该优先处理该信息,以避免对现有业务造成干扰.
	STD_PROT SHORT X7_PUSHING_BYROUTE				= 200;			// 推送信息(路由推送)
	STD_PROT SHORT X7_PUSHING_BYROAM				= 201;			// 推送信息(漫游推送)
	STD_PROT SHORT X7_PUSHING_BYCHAIN				= 202;			// 推送信息(链式推送)

	// 协议异常包定义(X7_PROTOCOL_ERROR)
	struct x7_protocol_error_ans
	{	WORD		m_wCmdNo;										// 请求的协议号
		DWORD		m_dwReserved;									// 保留字节,全空
		LONG		m_nErrorCode;									// 错误代码(尽量避免使用,会增加耦合性)
		WORD		m_wErrorSize;									// 错误信息大小
		CHAR		m_szError[1];									// 错误信息内容
	};

	// 推送数据包(X7_PUSHING_BYROUTE)
	struct x7_pushing_byroute
	{	DWORD		m_idPushingType;								// 推送类型
		DWORD		m_dwPushingOption;								// 推送选项
		BYTE		m_acSequence[0];								// 推送序列
	};

	// 推送数据包(X7_PUSHING_BYROAM)
	struct x7_pushing_byroam
	{	DWORD		m_idPushingType;								// 推送类型
		DWORD		m_dwPushingOption;								// 推送选项
		BYTE		m_acSequence[0];								// 推送序列
	};

	// 推送数据包(X7_PUSHING_BYCHAIN)
	struct x7_pushing_bychain
	{	DWORD		m_dwLinkAsyncID;								// 关联发送ID(通过TransKey传输)
		DWORD		m_idPushingType;								// 推送类型
		DWORD		m_dwPushingOption;								// 推送选项
		BYTE		m_acSequence[0];								// 推送序列
	};

#endif

#if defined(_COMPILE_BY_MSC_)
	#pragma warning(pop)
#endif
#pragma pack()
#endif
