//////////////////////////////////////////////////////////////////////////
// 创建日期:2006/07/20
// 功能说明:数据字典处理类
// 变更记录:  
//            2006/07/23 增加转义字处理,在原有结构中,各字段使用|字符进行分割,但是某些情况下返回内容中会出现|字符
//                       如此会影响解析等全部过程,也造成系统不稳定.这里增加转义字定义
//                             \\    字符\     |
//                             \0    字符0     |
//                             \s    字符|     |
//                             \r    字符\r    |
//                             \n    字符\n    |
//                             \t    字符\t    |
//            2006/07/23 支持多行请求集(可用于类似资金查询等多行查询情况)
//            2007/04/20 支持COOKIES以解决静态缓存造成的问题
//            2007/07/13 支持扩充翻页(定位串方式)支持
//                       扩充后返回结构为: 错误号|返回信息|总行数|COOKIES|翻页定位串|
//            2008/03/05 支持字段映射
//            2008/03/11 移植到linux
//            2010/03/16 由原WTCOMMLIB库扩充为ASE库,支持更广泛的事务
#if !defined(__ASE_LIB_IX_IMPL_V1__H__)&&!defined(ASE_NO_IX_V1)
#define __ASE_LIB_IX_IMPL_V1__H__
#pragma pack(1)
#ifndef ASELIB_API
	#error "ASELib.h" must be included.
#endif
#define ASELIBIMPL_DEFINED
#define ASELIBIMPLV1_DEFINED



// 本模块导出类
class CWtDict;		// 基本字典
class CWtDict2;		// 扩展字典(支持XML,支持字典版本号,支持数据重置)
class CWtCommon;	// 基本字典处理类

//////////////////////////////////////////////////////////////////////////
//	处理数据字典的类,字典的构建,导入和导出.字典的相关操作
//////////////////////////////////////////////////////////////////////////
// 从当前版本开始,CWtDict.V1彻底封闭
class ASELIB_API CWtDict
{
protected:
	CWtDict(DWORD dwReserved);
	virtual ~CWtDict();
public:

	// 登记标准字段(注意,不允许重载,会删除已经存在的数据)
	BOOL RegisterFieldInfo(CONST FIELDINFO pFieldInfo[],WORD wFieldNum);
	// 登记标准功能ID列表(注意,不允许重载,会删除已经存在的数据)
	BOOL RegisterStruct(CONST WORD pStructID[],WORD wStructNum);
	// 登记标准功能字段(注意,不允许重载,会删除已经存在的数据)
	BOOL RegisterStructField(WORD wStructID,CONST WORD pFieldID[],WORD wFieldNum);
	// 增加CACHE字段
	BOOL RegisterCacheFields(CONST FIELDINFO pFieldInfo[],WORD wFieldNum);


	// 重载标准字段(仅应答,严格禁止重载请求字段)
	BOOL OverrideFieldInfo(CONST FIELDINFO pFieldInfo[],WORD wFieldNum);
	// 重载请求结构中的缓存字段
	BOOL OverrideRequestStructField(WORD wStructID,CONST WORD pCacheFieldID[],WORD wCacheFieldNum,BOOL bAppend);
	// 重载应答结构中的字段
	BOOL OverrideAnswerStructField(WORD wStructID,CONST WORD pFieldID[],WORD wFieldNum);


	// 登记非标准字段
	// 注册用户自定义的字段信息
	BOOL RegisterFieldInfoNonStd(CONST FIELDINFO pFieldInfo[],WORD wFieldNum);
	// 登记非标准功能ID列表
	// 注册用户自定义的结构声明
	BOOL RegisterStructNonStd(CONST WORD pStructID[],WORD wStructNum);
	// 登记非标准功能ID对应的字段描述(在以后的升级版本中将取代标准功能)
	BOOL RegisterStructFieldNonStd(WORD wStructID,CONST WORD pFieldID[],WORD wFieldNum);


	// 导出数据字典
	// 入参:
	//		pBuff	输出缓冲区地址
	//		dwSize	最大缓冲区大小
	// 出参:
	//		pBuff	字典数据
	//		dwSize	当前字典大小
	// 返回:
	//		TRUE	取得字典成功
	//		FALSE	取得字典失败
	BOOL ExportCommonSafe(LPVOID pBuff,DWORD dwSize,DWORD& dwUsed);
	// 导入数据字典
	BOOL ImportCommonSafe(CONST LPVOID pBuff,DWORD dwSize,DWORD& dwUsed);

	// 压缩数据字典
	// 入参:
	//		(无)
	// 出参:
	//		(无)
	VOID CompressDict();
public:
	WORD GetStructNum();
	WORD GetStructID(WORD wIndex);
	WORD GetFieldNum(WORD wStructID);
	WORD GetFieldID(WORD wStructID,WORD wIndex);
	CONST LPFIELDINFO GetFieldInfo(WORD wFieldID);
	CONST LPWTSTRUCT_INFO GetStructInfo(WORD wStructID);
protected:
	VOID Cleanup();
	LONG FindFieldInfo(WORD wFieldID) CONST;
	LONG FindStructInfo(WORD wStructID) CONST;
	BOOL SetFieldInfo(CONST FIELDINFO pFieldInfo[],WORD wFieldNum,BOOL bOverwrite);
	BOOL SetStruct(CONST WORD pStructID[],WORD wStructNum,BOOL bOverwrite);
	BOOL SetStructField(WORD wStructID,CONST WORD pFieldID[],WORD wFieldNum,BOOL bOverwrite);

protected:
	LPFIELDINFO		m_pFieldInfo;
	WORD			m_wFieldNum;
	LPWTSTRUCT_INFO	m_pStructInfo;
	WORD			m_wStructNum;
};







//////////////////////////////////////////////////////////////////////////
// 数据字典扩展类(支持编译号和其他处理)
//////////////////////////////////////////////////////////////////////////
// 保留字段[0]: 字段映射表指针
class ASELIB_API CWtDict2 : public CWtDict
{
public:
	CWtDict2(WORD wVersion=0,WORD wBuildNo=0);
	CWtDict2(LPCSTR pszBuildDate,LPCSTR pszBuildTime);
	CWtDict2(LPCSTR pszTime);
	virtual~CWtDict2();
	VOID SetCodePage(UINT nDataCodePage,UINT nUserCodePage);
	UINT GetDataCodePage();
	UINT GetUserCodePage();
public:
	// 获取字典版本以及编译号(版本检查)
	WORD GetVersion();
	WORD GetBuildNo();
	// 导出字典类
	BOOL ExportCommonAndGetUsed(CONST LPVOID pBuff,DWORD dwSize,DWORD& dwUsed);
	virtual BOOL ExportCommon(LPVOID pBuff,DWORD& dwSize);
	// 导入数据字典
	virtual BOOL ImportCommonAndGetUsed(CONST LPVOID pBuff,DWORD dwSize,DWORD& dwUsed);
	virtual BOOL ImportCommon(CONST LPVOID pBuff,DWORD dwSize);
	// 从XML导入字典
	virtual BOOL ImportFromXML(LPCSTR pszXmlFile);
	// 获取扩展属性
	virtual LPCSTR GetExtendAttrib(LPCSTR pszName);
	// 字段信息枚举
	WORD GetFieldNumNoMapping(WORD wStructID);
	WORD GetFieldIDNoMapping(WORD wStructID,WORD wIndex);
	CONST LPFIELDINFO GetFieldInfoNoMapping(WORD wFieldID);
	CONST LPWTSTRUCT_INFO GetStructInfoNoMapping(WORD wStructID);
	// 映射字段的枚举
	WORD GetMappedFieldNum(WORD wStructID);
	WORD GetMappedFieldID(WORD wStructID,WORD wIndex);
	CONST LPFIELDINFO GetMappedFieldInfo(WORD wFieldID);
	CONST LPWTSTRUCT_INFO GetMappedStructInfo(WORD wStructID);
	BOOL MappingFieldIndex(WORD wStructID,WORD& wFieldIndex);
	// 装载和插入映射表
	BOOL LoadFieldsMapper(LPCSTR pszXmlFile,BOOL bMapperEnable);
	// 增加重置字典的功能
	VOID ResetContent();
protected:
	enum enumREVDNO
	{	REV_FIELDSMAPPER,	// 系统字段映射
		REV_DATA_CODEPAGE,	// 数据代码页
		REV_USER_CODEPAGE,	// 用户代码页
	};
protected:
	WORD		m_wVersion;
	WORD		m_wBuildNo;
	DWORD		m_dwAttrib;
	DWORD_PTR	m_adwReserved[10];
};











//////////////////////////////////////////////////////////////////////////
//	使用数据字典类进行业务处理的类
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// 字典解析类
class ASELIB_API CWtCommon
{
public:
	CWtCommon(CWtDict* pDict=NULL,CWtCache* pCache=NULL,BOOL bCaptureFatalError=FALSE);
	virtual ~CWtCommon();
public:
	// 设置数据字典
	VOID		SetDict(CWtDict* pDict);
	// 设置字段缓存
	VOID		SetCache(CWtCache* pCache);
	// 接受数据,-1返回失败,0返回成功
	LONG		CreateStruct(WORD wStructID,LPVOID pBuffer,DWORD dwBuffLen);
	LONG		CreateStructToRead(WORD wStructID,LPVOID pBuffer,DWORD dwBuffLen);
	LONG		CreateNoDict(LPVOID pBuffer,DWORD dwBuffLen);
	// 缓冲区置空/结构ID获取/长度获取(包括结束字符,创建字典读取会重置)
	VOID		InitBuffer();			// 初始化缓冲区
	WORD		GetStructID();			// 获取当前结构ID
	LPBYTE		GetBufferAddress();		// 得到数据区地址
	DWORD		GetUsedBufferLen();		// 得到已使用缓冲区长度(包括结束字符,若为读取,本函数无效)
	DWORD		GetMaxBufferLen();		// 得到全部缓冲区长度(包括结束字符)
	LPBYTE		GetContentAddress();	// 获取正文字地址
	DWORD		GetContentLen();		// 获取正文长度(包含结束字符)
	// 为提高服务器端的效率,数据项必须按顺序填充,客户端禁止使用
	BOOL		AddItemValue4X(LPCSTR lpszValue,BOOL bEncrypt=FALSE);
	BOOL		AddItemFlagValue(BYTE cFlag);
	BOOL		AddItemLongValue(LONG nValue);
	BOOL		AddItemValue(LPCSTR lpszValue,BOOL bEncrypt=FALSE);
	BOOL		AddItemBinaryValue(CONST LPBYTE lpValue,WORD wSize,BOOL bEncrypt=FALSE,BOOL bEncode=TRUE);
	BOOL		AddItemWtCommonValue(CWtCommon* pWtCommon);
	// 用于客户端填写请求时调用,服务器禁止调用,仅适用于单结果集
	BOOL		SetItemValue4X(WORD wFieldID,LPCSTR lpszValue,BOOL bEncrypt=FALSE);
	BOOL		SetItemFlagValue(WORD wFieldID,BYTE cFlag);
	BOOL		SetItemLongValue(WORD wFieldID,LONG nValue);
	BOOL		SetItemValue(WORD wFieldID,LPCSTR lpszValue,BOOL bEncrypt=FALSE);
	BOOL		SetItemBinaryValue(WORD wFieldID,CONST LPBYTE lpValue,WORD wSize,BOOL bEncrypt=FALSE,BOOL bEncode=TRUE);
	// 增加行结束符(服务器版)
	BOOL		AddLine();
	// 增加请求结束符(客户端版)
	BOOL		AddAttachAndEOR(const BYTE* pAttach,DWORD cbAttach);
	// 增加缓存字段并添加行结束字符(客户端调用,已废弃,客户端会根据功能号判断)
	BOOL		FillCacheAndAddLine();
	BOOL		FillCacheAndAddLineEx(LPBYTE pszCacheBuf,DWORD cbCacheUsed);
	// 返回时必须先填充返回值信息nRetcode=0为处理成功,其他为失败
	// 注:必须在完成全部字段填写后添加(只能调用一次)
	BOOL		SetReturn(LONG nRetCode,LPCSTR lpszMessage,LONG nRecordNum);
	BOOL		SetReturn2(LONG nRetCode,LPCSTR lpszMessage,LONG nRecordNum,CWtCookies* pCookies,LPCSTR lpszNextPageId);
	BOOL		SetReturn3(LONG nRetCode,LPCSTR lpszMessage,LONG nRecordNum,LPCSTR pszCookies,LONG nCookiesLen,LPCSTR lpszNextPageId);
	BOOL		SetReturn4(LONG nRetCode,LPCSTR lpszMessage,LONG nRecordNum,LPCSTR pszCookies,LONG nCookiesLen,LPCSTR lpszNextPageId,LPBYTE pAttach,WORD cbAttach);
	// 得到返回错误号(客户端必须判断返回错误号)
	LONG		GetReturnNo();
	// 得到返回错误信息(客户端在存在错误的情况下建议提示错误信息)
	LPCSTR		GetErrmsg(LPSTR lpszErrMsg,WORD wMaxSize);
	// 柜台实际返回的查询数,在多结果集用到,客户端必须判断结果返回值
	LONG		GetTotalReturn();
	// 得到COOKIES信息
	LPCSTR		GetCookies(LPSTR lpszCookies,WORD wMaxSize);
	// 获取定位串信息
	LPCSTR		GetNextPageId(LPSTR lpszNextPageId,WORD wMaxSize);
	// 获取附件缓冲区
	LPBYTE		GetAttachPtr();
	ATTACHSIZE	GetAttachSize();
	// 返回当前字段个数
	LONG		GetFieldNum();
	WORD		GetFieldIDAt(WORD wIndex);
	CONST LPFIELDINFO GetFieldInfoAt(WORD wIndex);
	// 获取字段信息
	CONST LPFIELDINFO GetFieldInfoByID(WORD wFieldID);
	// 获取返回行数(多结果集功能返回,单结果集返回行数为0)
	WORD		GetLineCount();
	// 得到第N行的偏移
	// 参数:	wLine		行号,<=0的时候移动到头部(返回状态信息行)
	// 返回:	(DWORD)		位置偏移,(DWORD)(-1)表明行不存在
	DWORD		GetLineOffset(WORD wLine);
	// 得到第N行的缓冲区
	// 参数:	wLine		行号,<=0的时候移动到头部(返回状态信息行)
	// 返回:	(LPCSTR)	缓冲区起始位置
	LPCSTR		GetLineAddress(WORD wLine);
	// 移动行指针到指定行/首行
	// 参数:	wLine		行号,<=0的时候移动到头部(返回状态信息行)
	// 返回:	(BOOL)		指定行是否存在
	BOOL		MoveToLine(WORD wLine);
	// 移动行指针到下一行
	// 返回:	(BOOL)		指定行是否存在
	BOOL		MoveNext();
	// 取得4.X兼容的字段
	LPCSTR		GetItemValue4X(WORD wIndex,LPSTR lpszValue,WORD wSize,BOOL bDecrypt=FALSE);
	LPCSTR		GetItemValueFromID4X(WORD wFieldID,LPSTR lpszValue,WORD wSize,BOOL bDecrypt=FALSE);
	// 根据字段序号获取字段内容/根据字段ID获取字段内容
	// 返回0XFF表明获取失败
	BYTE		GetItemFlagValue(WORD wIndex,DWORD dwLineOffset=(DWORD)(-1));
	BYTE		GetItemFlagValueFromID(WORD wFieldID,DWORD dwLineOffset=(DWORD)(-1));
	// 根据字段序号获取字段内容/根据字段ID获取字段内容
	// 返回0XFFFFFFFF表明获取失败
	LONG		GetItemLongValue(WORD wIndex,DWORD dwLineOffset=(DWORD)(-1));
	LONG		GetItemLongValueFromID(WORD wFieldID,DWORD dwLineOffset=(DWORD)(-1));
	// 根据字段序号获取字段内容/根据字段ID获取字段内容
	// 返回NULL表明获取失败,如果输入缓冲区有效,缓冲区内部被清空
	LPCSTR		GetItemValue(WORD wIndex,LPSTR lpszValue,WORD wSize,BOOL bDecrypt=FALSE,DWORD dwLineOffset=(DWORD)(-1));
	LPCSTR		GetItemValueFromID(WORD wFieldID,LPSTR lpszValue,WORD wSize,BOOL bDecrypt=FALSE,DWORD dwLineOffset=(DWORD)(-1));
	// 根据字段序号获取字段内容/根据字段ID获取字段内容
	// 返回NULL表明获取失败,如果输入缓冲区有效,缓冲区内部不会[!!!]被清空
	BOOL		GetItemBinaryValue(WORD wIndex,WORD wMaxSize,LPBYTE lpValue,WORD* pwSize,BOOL bDecrypt=FALSE,BOOL bDecode=TRUE,DWORD dwLineOffset=(DWORD)(-1));
	BOOL		GetItemBinaryValueFromID(WORD wFieldID,WORD wMaxSize,LPBYTE lpValue,WORD* pwSize,BOOL bDecrypt=FALSE,BOOL bDecode=TRUE,DWORD dwLineOffset=(DWORD)(-1));
	// 根据字段ID获取字段内容(字典格式)
	BOOL		GetItemWtCommonValue(CWtCommon* pWtCommon);
	VOID		FreeWtCommonValue(CWtCommon* pWtCommon);
	// 提取缓存字段到缓存缓冲区,如果返回无错误,则从当前返回的结果集中提取属性标识为CACHE的字段,放入CWtCache中
	BOOL		ExtractCacheField();
	// 提取COOKIES字段到缓存缓冲区,如果返回无错误,则从当前返回的结果集中提取属性标识为CACHE的字段,放入CWtCache中
	BOOL		ExtractCookiesField();
	// 提取缓存字段到缓存缓冲区,如果返回无错误,则从当前返回的结果集中提取属性标识为CACHE的字段,放入CWtCache中
	BOOL		ExtractCacheFieldEx(LPBYTE pCacheBuf,DWORD cbCacheBuf,DWORD& cbCacheUsed);
	// 提取COOKIES字段到缓存缓冲区,如果返回无错误,则从当前返回的结果集中提取属性标识为CACHE的字段,放入CWtCache中
	BOOL		ExtractCookiesFieldEx(LPBYTE pCacheBuf,DWORD cbCacheBuf,DWORD& cbCacheUsed);
	// 缓存和COOKIES字段自动完成,如果返回无错误,则
	// 1.从缓存类中提取缓存字段放入当前数据行
	// 2.从缓存类中提取COOKIES字段放入当前数据行
	// (除客户校验/集成客户校验/获取缓存信息需要调用)
	BOOL		AutoFillCacheAndCookiesToReq();
	BOOL		AutoFillCacheAndCookiesToReqEx(LPBYTE pCacheBuf,DWORD cbCacheUsed);
	// 取得最后的致命错误和非致命错误代码
	DWORD		GetLastFatalError();
	DWORD		GetLastCommonError();
	// 获取数据字典类实例
	CWtDict*	GetDict();
	// 读取当前字典结构
	LPWTSTRUCT_INFO GetStructInfo() { return m_StrcBuf.m_pStructInfo; }
	// 数据集合并
	DWORD CalcLengthToMerge(DWORD dwOriginSize);
	BOOL MergeTo(LPBYTE pTarget,DWORD cbTargetMax,DWORD& cbUsed);
protected:
	// 查找当前行中字段的起止位置(终止字符为下一个字段的开始字符)
	BOOL		FindFieldByIndex(WORD wFieldIndex,LPDWORD lpdwFieldBegin,LPDWORD lpdwFieldEnd,DWORD dwLineOffset,BOOL bMapper);
	// 代码页转换
	LONG		ConvertWtCommonCodePage(LPSTR pszBuf,LONG nLen,LONG nMaxSize,BOOL bToUser);
	// 内部函数
	BOOL		AddItemRawBinaryValue(CONST LPBYTE lpValue,WORD wSize,BOOL bEncrypt,BOOL bEncode,BOOL bConvertCodePage);
	BOOL		SetItemRawBinaryValue(WORD wFieldID,CONST LPBYTE lpValue,WORD wSize,BOOL bEncrypt,BOOL bEncode,BOOL bMapper,BOOL bConvertCodePage);
	BOOL		GetItemRawBinaryValue(WORD wIndex,WORD wMaxSize,LPBYTE lpValue,WORD* pwSize,BOOL bDecrypt,BOOL bDecode,DWORD dwLineOffset,BOOL bMapper,BOOL bConvertCodePage);
	LPCSTR		GetItemRawTextValue(WORD wIndex,LPSTR lpszValue,WORD wSize,BOOL bDecrypt,DWORD dwLineOffset,BOOL bMapper,BOOL bConvertCodePage);
	BOOL		GetItemRawBinaryValueFromID(WORD wFieldID,WORD wMaxSize,LPBYTE lpValue,WORD* pwSize,BOOL bDecrypt,BOOL bDecode,DWORD dwLineOffset,BOOL bMapper,BOOL bConvertCodePage);
	LPCSTR		GetItemRawTextValueFromID(WORD wFieldID,LPSTR lpszValue,WORD wSize,BOOL bDecrypt,DWORD dwLineOffset,BOOL bMapper,BOOL bConvertCodePage);
protected:
	friend class CWtCache;
private:
	CWtDict*		m_pDict;				// 数据字典类指针
	CWtCache*		m_pCache;				// 数据缓存类指针
	BOOL			m_bCaptureFatalError;	// 是否捕获致命错误
	WTCOMMON_STRC	m_StrcBuf;				// 当前结构描述缓冲区
	DWORD			m_dwLineOffset;			// 当前行偏移
	DWORD			m_dwMaxBufLen;			// 缓冲区长度
	DWORD			m_dwUsedLen;			// 当前缓冲区已经使用的
	BOOL			m_bLineStruInit;		// 当前行结构是否已经初始化(逐字段添加时在添加第一个字段的时候添加全部的记录分割字)
	DWORD			m_dwLastFatalError;		// 最后致命错误
	DWORD			m_dwLastCommonError;	// 最后非致命错误
};

#pragma pack()
#endif
