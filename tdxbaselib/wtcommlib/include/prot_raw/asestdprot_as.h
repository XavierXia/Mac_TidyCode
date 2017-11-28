//////////////////////////////////////////////////////////////////////////
// 标准业务集成平台(安全中心,分级平台)协议规范定义文件
//	1.业务集成平台相关的协议定义 (协议号范围: 4506-4510)
//	2.业务集成平台主要实现包括: 安全中心/分级平台
//	3.业务集成平台必须实现信息交换协议(IX)的转发(来自标准客户端协议)
#ifndef __ASE_STDDEF_AS__H__
#define __ASE_STDDEF_AS__H__
#pragma pack(1)

// 协议号定义
STD_PROT SHORT TC50_AS_DICT_EXCHANGE	= 4506;			// (内部互联)字典交换



// 内部数据字典交换(TC50_AS_DICT_EXCHANGE,限制协议版本>=5.12.0171)
// 事务线程或外部处理
// 内部数据字典交换
struct tc50_as_dict_exchange_req
{	BYTE		m_cFuncType;							// 功能类型
	MD5BIN		m_md5Dict;								// 字典的MD5
	DWORD		m_cbDict;								// 字典的长度
};
struct tc50_as_dict_exchange_ans
{	BYTE		m_bDictSupport;							// 数据字典是否支持
	BYTE		m_bDictUpdated;							// 数据字典已经更新
	MD5BIN		m_md5Dict;								// 数据字典的MD5
	DWORD		m_cbDict;								// 数据字典的长度
	BYTE		m_szDict[1];							// 数据字典的内容
};


#pragma pack()
#endif
