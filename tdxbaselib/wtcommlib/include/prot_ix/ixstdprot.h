//////////////////////////////////////////////////////////////////////////
// IX(Information eXchange协议基本定义)
// IX协议基于数据字典协议发展而来,用于在不同的底层协议上进行具有相同架构的信息交换
//	1. IX协议规定应用层信息交换的应用数据格式,但既不规定底层的传输方式和结构,也不关心
//     具体的业务内容,只关注信息交换的形式(数据字典)
//  2. IX协议可以适应不同的底层协议,目前主要包括TC5相关架构的服务器以及TC5原生模式的协议.
//	3. IX协议可以用于组织不同的应用层协议,目前主要包括TC5以及IMServer等协议集
#ifndef __IX_STDPROT__H__
#define __IX_STDPROT__H__

// IX协议数据字典最大大小
#define MAX_DICT_BUF_SIZE			(1*1024*1024)		// 数据字典最大大小(交换)
#define MAX_IX_BUF_SIZE				(64*1024)			// IX数据单包最大大小
#define DICTSTUFF_MAX				(MAX_IX_BUF_SIZE)	// IX数据单包最大大小


// IX协议功能子类型
#define FTYPE_NUM					(6)					// 功能类型数
#define FTYPE_UNSPEC				((BYTE)-1)			// 功能类型未指定
#define FTYPE_ERROR					((BYTE)-1)			// 功能类型错误
#define FTYPE_DEFAULT				((BYTE)0)			// 标准业务功能
#define FTYPE_TCNTR					((BYTE)0)			// 交易业务功能(TRADE CENTER)
#define FTYPE_SCNTR					((BYTE)1)			// 安全中心功能(SECURITY CENTER)
#define FTYPE_ICNTR					((BYTE)2)			// 消息平台功能(INFORMATION CENTER)
#define FTYPE_CCNTR					((BYTE)3)			// 呼叫中心功能(CALL CENTER)
#define FTYPE_UCNTR					((BYTE)4)			// 用户管理中心功能(USER CENTER)
#define FTYPE_ECNTR					((BYTE)5)			// 客户服务平台功能(SERVICE CENTER)


// IX协议功能相关定义
#define NULL_FUNCNO					(0X0000)			// 无功能号
#define NULL_ENTRYPOINTID			(0X0000)			// 无入口点ID
#define NULL_BRANCHID				(0X00000000)		// 无营业部ID


// IX协议功能常用限制
//		老协议采用字符串的入口点ID,在TC50中采用USHORT表达,利于各子系统之间的数据一致
//		处理,资金帐号必须是字符串(主要是因为部分资金帐号中包含字母)
#ifndef IX_FUNCLIMIT_DEFINED
#define IX_FUNCLIMIT_DEFINED
	#define KHH_SIZE				32					// 客户号长度,包含结束字符
	#define ZJZH_SIZE				32					// 资金帐号长度,包含结束字符
	#define GDDM_SIZE				32					// 股东代码长度,包含结束字符
	#define JBZD_SIZE				32					// 基本字段长度,包含结束字符
	#define SMZD_SIZE				256					// 说明字段长度,包含结束字符
	#define AUTHPASS_SIZE			25					// 认证口令长度,包含结束字符
	#define YYBIDSTR_SIZE			9					// 营业部ID串长度,包含结束字符,最长8位
		
	#define	ZQDM_LEN				(ZQDM_SIZE-1)		// 最大代码长度
	#define	ZQMC_LEN				(ZQMC_SIZE-1)		// 商品名称
	#define	HKZQDM_LEN				(HKZQDM_SIZE-1)		// (港股)最大代码长度
	#define	HKZQMC_LEN				(HKZQMC_SIZE-1)		// (港股)商品名称
	#define QSID_LEN				(QSID_SIZE-1)		// 券商标识长度
	#define KHH_LEN					(KHH_SIZE-1)		// 客户号长度
	#define TDX_ZJZH_LEN			(ZJZH_SIZE-1)		// 资金帐号长度
	#define AUTHPASS_LEN			(AUTHPASS_SIZE-1)	// 认证口令长度
	#define YYBIDSTR_LEN			(YYBIDSTR_SIZE-1)	// 营业部ID串长度
		
	#define CONTENT_LEN				512					// 主题内容和回复信息最大长度
	#define PTBZ_LEN				2					// 普通标志长度
#endif

#endif
