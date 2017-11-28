//////////////////////////////////////////////////////////////////////////
// 创建日期:2013/03/19
// 功能说明:数据字典处理类
// 变更记录:  
// 相关知识:
//		■ IX映射(IXMapper)原理:
//			字段映射以可插拔方式工作,即在标准字典上进行映射的工作方式,字段映射不进行字典的修改,映射后字典包括两个部分,原文部分和映射部分
//
//			1.字段别名
//			  允许重新定义新的字段,或者对原有字段进行重定义
//				旧字段重定义:
//					<Mapper ID="102" Hidden="0" Name="YYB(New!)"/>
//					在StructID范围内,重新定义原有字段(ID,必须存在)的字段
//				新字段派生(最多512个):
//					<Mapper ID="10108" Hidden="0" Name="NC(New!)" DeriveFromID="108"/>
//					<Mapper StructID="101" ID="10108" Hidden="0" Name="NC(New!!)" DeriveFromID="108"/>
//					在StructID范围内,通过原有字段(DeriveFrom,必须存在)字段派生出新的字段(ID)
//
//			2.结构重定义
//			  允许为结果集进行重新定义
//					<Mapper ID="101" Seq="102,10108" HideOther="0"/>
//					创建功能ID对应的映射序列,可以调整字段顺序,隐藏其他字段,字段优先引用其具有别名的字段
//					字段访问的优先顺序为:
//						a.经过映射的映射表中的私有字段
//						b.经过映射的映射表中的公共字段
//						c.未经过映射的字典中的私有字段
//						c.未经过映射的字典中的公共字段
//
//		■ 几种兼容的情况
//			1.老客户端---->老服务器(使用2代协议进行交互)
//			2.老客户端---->新服务器(使用2代协议进行交互)
//			3.新客户端---->老服务器(使用2代协议进行交互)
//			4.新客户端---->新服务器(使用3代协议进行交互)
//		■ 字典版本和模块版本的对应关系
//			方法					字典			客户端版本	服务器版本		客户端映射	服务器映射
//			IXHostSide				完整字典(3X)		3X			3X
//			IXNodeSide3X			精简字典(3X)		3X			3X
//			IXNodeSideNoStub		NA					3X			3X
//			IXNodeSideCompatible	旧版字典(2X)		3X			3X
//			IXNodeSideDeprecation	旧版字典(2X)		2X			3X
//			IXNodeSideCompatible	旧版字典(2X)		3X			2X
//			IXNodeSideDeprecation	旧版字典(2X)		2X			2X
//		■ 映射支持
//			方法						映射
//			CreateStructToNodeWrite		不支持映射(原理上不支持,映射导致最终字段可能不能完整映射,导致写入缺列)
//			CreateStructToHostWrite		不支持映射,必须使用字典(原理上不支持,映射导致最终字段可能不能完整映射,导致写入缺列)
//			CreateStructToNodeRead		全模式支持映射,扩展模式不支持字段派生
//			CreateStructToHostRead		全模式支持映射,扩展模式不支持字段派生,映射无实际意义
//			备注: 非扩展模式映射对数据字典存在依赖性,因为映射表中字段序号和字典相关。
//		■ 缓冲字段
//			缓冲字段提取和保存
//				从应答中提取数据保存进缓存容器中,仅适用于客户端读取应答
//				SaveCacheFields(依靠服务器返回的字段标识CACHE和COOKIES字段)
//				SaveCookiesFields(不判断字段是否CACHE和COOKIES字段,只要传回即保存)
//			缓冲字段送入
//				SetCacheAndCookiesItems(兼容模式依靠字典格式,3X模式送入全部的缓存字段)
#if !defined(__ASE_LIB_IX_IMPL_V2__H__)&&!defined(ASE_NO_IX_V2)
#define __ASE_LIB_IX_IMPL_V2__H__
#pragma pack(1)
#ifndef ASELIB_API
	#error "ASELib.h" must be included.
#endif
#define ASELIBIMPL_DEFINED
#define ASELIBIMPLV2_DEFINED

// IX字典相关属性
#define IXCOREVER_1				(0)			// IX内核版本(第1代和第2代)
#define IXCOREVER_3				(3)			// IX内核版本(第3代)

#define DICTFORMAT_DICTVER		(0X000F)	// IX字典格式
#define IXDICTVER_COMPATIBLE	(0)			// 更早的版本(包括第一代字典和第二代字典(支持附件包和COOKIES))
#define IXDICTVER_3_00_L1		(3)			// 第三代字典(基本,支持附带报文传送请求)
#define IXDICTVER_3_00_L2		(4)			// 第三代字典(深度,支持附带报文传送请求)
#define IXDICTVER_LATEST		(4)			// 最新版本

#define IXFIELD_MAX				(128)		// 最大字段个数(每个结构)




// IX数组
template<class TYPE>
class CIXArray
{
public:
	CIXArray(LONG nGrowBy=128) { m_nGrowBy=nGrowBy; m_pData=NULL; m_nAlloc=0; m_nCount=0; }
	~CIXArray() { Zero(); }
	
	VOID Zero()
		{	if(m_pData!=NULL) free(m_pData);
			m_pData=NULL;
			m_nAlloc=0;
			m_nCount=0;
		}
	BOOL Expand(LONG nToHoldMore)
		{	LONG nToHold=m_nCount+nToHoldMore;
			if(m_nAlloc<=nToHold)
			{	nToHold=nToHold+m_nGrowBy;
				TYPE* pNewData=(TYPE*)malloc(nToHold*sizeof(TYPE));
				if(pNewData==NULL) return FALSE;
				if(m_nCount>0) memcpy(pNewData,m_pData,m_nCount*sizeof(TYPE));
				m_nAlloc=nToHold;
				free(m_pData);
				m_pData=pNewData;
			}
			return TRUE;
		}
	BOOL Append(TYPE& Data)
		{	if(!Expand(GetCount()+1)) return FALSE;
			(*this)[GetCount()]=Data;
			SetCount(GetCount()+1);
			return TRUE;
		}
	TYPE* AppendEmpty()
		{	if(!Expand(GetCount()+1)) return NULL;
			SetCount(GetCount()+1);
			return &(*this)[GetCount()-1];
		}
	CONST TYPE& operator[](LONG nIndex) CONST { return m_pData[nIndex]; }
	TYPE& operator[](LONG nIndex) { return m_pData[nIndex]; }
	LONG GetAllocCount() CONST { return m_nAlloc; }
	LONG GetCount() CONST { return m_nCount; }
	TYPE* GetData() CONST { return m_pData; }
	VOID SetCount(LONG nCount) { m_nCount=nCount; }
protected:
	LONG m_nGrowBy;
	TYPE* m_pData;
	LONG m_nAlloc;
	LONG m_nCount;
};



//////////////////////////////////////////////////////////////////////////
// 数据字典类(IX版本)
//////////////////////////////////////////////////////////////////////////
// 2.X重定位信息
typedef struct tagIXSTRUCTRELOC
{	LPWORD	m_pFieldIdx;						// 重定位的索引信息(字典依赖)
} IXSTRUCTRELOC,*LPIXSTRUCTRELOC;

// 3.X映射结构列表
typedef struct tagIXREMAPSTRUCT
{	WORD	m_wStructID;						// 结构号
	DWORD	m_dwSeqOffset;						// 序列偏移
	DWORD	m_dwSeqNum;							// 序列数
	DWORD	m_dwFieldOffset;					// 字段偏移
	DWORD	m_dwFieldNum;						// 字段数
	BYTE	m_cHideOther;						// 是否隐藏其他的字段
}IXREMAPSTRUCT,*LPIXREMAPSTRUCT;

// 3.X映射字段列表
typedef FIELDINFO IXREMAPFIELD,*LPIXREMAPFIELD;

#if !defined(PLATFORM_MACOSX) && !defined(PLATFORM_IOS)
	template class ASELIB_API CIXArray<FIELDINFO>;
	template class ASELIB_API CIXArray<IXSTRUCTINFO>;
	template class ASELIB_API CIXArray<WORD>;
	template class ASELIB_API CIXArray<IXSTRUCTRELOC>;
	template class ASELIB_API CIXArray<IXREMAPSTRUCT>;
#endif
class ASELIB_API CIXDict
{
public:
	CIXDict(WORD wVersion=0,WORD wBuildNo=0);
	CIXDict(LPCSTR pszBuildDate,LPCSTR pszBuildTime);
	CIXDict(LPCSTR pszTime);
	virtual~CIXDict();

	// 获取IX核心版本和IX字典格式
	WORD GetIXCoreVer() { return m_wCoreVer; }
	VOID UpdateDictFormat(WORD wDictFormat) { m_wDictFormat=wDictFormat; }
	WORD GetDictFormat() { return m_wDictFormat; }
	WORD GetIXDictVer() { return (WORD)(m_wDictFormat&DICTFORMAT_DICTVER); }

	// 获取字典版本以及编译号(字典内容版本检查)
	WORD GetVersion() { return m_wVersion; }
	WORD GetBuildNo() { return m_wBuildNo; }

	// 获取和设置扩展属性
	DWORD GetExtendAttrib() { return m_dwAttrib; }
	DWORD ModifyExtendAttrib(DWORD dwRemove,DWORD dwAdd) { m_dwAttrib=(m_dwAttrib&~dwRemove)|dwAdd; return m_dwAttrib; }

	// 代码页处理和签名处理(本地属性)
	VOID SetCodePage(UINT nDataCodePage,UINT nUserCodePage) { m_nDataCP=nDataCodePage; m_nUserCP=nUserCodePage; }
	UINT GetDataCodePage() { return m_nDataCP; }
	UINT GetUserCodePage() { return m_nUserCP; }
	BOOL GetSignature(LPTSTR pszSignature,DWORD cbSignature);

	// 删除全部数据
	VOID ResetDictContent(BOOL bResetMapper);

	// 登记字段
	BOOL RegisterFieldInfos(CONST FIELDINFO pFieldInfos[],LONG nFieldNum,BOOL bOverride);

	// 登记结构
	BOOL RegisterStructAndFields(WORD wStructID,FIELDREF* pFieldRefs,LONG nFieldNum,BOOL bOverride);

	// 重新整理和压缩数据字典
	VOID Defragment();

	// 导出字典类
	BOOL ExportToBuf(CONST LPVOID pBuff,DWORD dwSize,WORD wDictFormatAs,DWORD dwReserved,DWORD& dwUsed);

	// 导入数据字典
	BOOL ImportFromBuf(CONST LPVOID pBuff,DWORD dwSize,BOOL bDeprecation,DWORD dwReserved,DWORD& dwUsed);
	BOOL ImportFromBuf(CONST LPVOID pBuff,DWORD dwSize,BOOL bDeprecation,DWORD dwReserved);

	// 从XML导入字典
	BOOL ImportFromXML(LPCSTR pszXmlFile);

	// 装载和插入映射表
	BOOL LoadMapper(LPCSTR pszXmlFile,BOOL bMapperEnable);

	// 内建字典操作
	LONG GetBuildinStructNum() { return m_aStructInfos.GetCount(); }
	WORD GetBuildinStructID(LONG nIndex) { return (WORD)((nIndex<0||nIndex>=m_aStructInfos.GetCount())?0:m_aStructInfos[nIndex].m_wStructID); }
	LONG FindAnalogousBuildinFieldIndex(LPFIELDINFO pFieldInfo) CONST;
	LONG FindBuildinStructIndex(WORD wStructID) CONST;
	LONG FindBuildinFieldIndex(WORD wStructID,WORD wFieldID) CONST;
	CONST LPIXSTRUCTINFO FindBuildinStructInfo(WORD wStructID) CONST;
	CONST LPFIELDINFO FindBuildinFieldInfo(WORD wStructID,WORD wFieldID) CONST;
	CONST LPFIELDINFO FindBuildinFieldInfo(WORD wFieldID) CONST;
	CONST LPFIELDINFO FindBuildinFieldInfoByIndex(LONG nIndex) CONST { return m_aFieldInfos.GetData()+nIndex; }

	// 映射字典操作
	LPFIELDINFO GetFieldInfoWithMap(WORD wStructID,WORD wFieldID,BOOL bUseMapper=TRUE);
	BOOL GetStructInfoWithMap(WORD wStructID,LONG nMaxCount,FIELDREF* pFieldRefs,WORD* pwFieldIdxs,WORD& wFieldNum,BOOL bUseMapper=TRUE);
	BOOL RemapStructInfo(WORD wStructID,LONG nMaxCount,FIELDREF* pFieldRefs,WORD* pwFieldIdxs,LPFIELDINFO pFieldInfos,WORD& wFieldNum);

protected:
	// 映射表装载和保存
	BOOL LoadMapperFromFile(LPCSTR pszXmlFile,BOOL bMapperEnable);
	// 映射表导入和导入
	BOOL ExportMapperAndGetUsed(LPVOID pBuff,DWORD dwSize,WORD wDictFormatAs,DWORD& dwUsed);
	BOOL ImportMapperAndGetUsed(CONST LPVOID pBuff,DWORD dwSize,WORD wDictFormat,DWORD& dwUsed);
	// 字段映射处理(返回映射后的结果信息或者字段信息,返回NULL标识未映射)
	CONST LPFIELDINFO GetMappedFieldInfo(WORD wStructID,WORD wFieldID);
	CONST BOOL MapMappedStructInfo(WORD wStructID,LONG nMaxCount,FIELDREF* pFieldRefs,WORD* pwFieldIdxs,WORD& wFieldNum);
	CONST BOOL RemapMappedStructInfo(WORD wStructID,LONG nMaxCount,FIELDREF* pFieldRefs,WORD* pwFieldIdxs,LPFIELDINFO pFieldInfos,WORD& wFieldNum);
	// 重置数据内容
	VOID ResetMapperContent();
	VOID AppendMappedFieldInfo(LPFIELDINFO pFieldInfo);
	VOID AppendMappedStructInfo(WORD wStructID,LPWORD pFieldIDs,LPWORD pFieldIdxs,WORD wFieldNum);
private:
	// 字典定义数据
	CIXArray<FIELDINFO>		m_aFieldInfos;			// 字段定义
	CIXArray<IXSTRUCTINFO>	m_aStructInfos;			// 结构定义
	WORD					m_wCoreVer;				// IX核心版本
	WORD					m_wDictFormat;			// IX字典格式
	WORD					m_wVersion;				// 版本定义(主版本)
	WORD					m_wBuildNo;				// 版本定义(编译号)
	DWORD					m_dwAttrib;				// 扩充属性
	BYTE					m_acExtAttribs[32];		// 扩充属性
	UINT					m_nDataCP;				// 数据代码页
	UINT					m_nUserCP;				// 用户代码页
	// 字段映射数据
	BOOL					m_bMapperEnable;		// 是否开启字段映射
	CIXArray<FIELDINFO>		m_aMappedFieldInfos;	// 映射后的字段信息(2X)
	CIXArray<IXSTRUCTINFO>	m_aMappedStructInfos;	// 映射后的结构信息(2X)
	CIXArray<IXSTRUCTRELOC>	m_aMappedStructRelocs;	// 映射后的重定位信息(2X)
	CIXArray<IXREMAPSTRUCT>	m_aRemapStructs;		// 重映射的结构信息(3X)
	CIXArray<WORD>			m_aRemapSeqs;			// 重映射的字段序列(3X)
	CIXArray<IXREMAPFIELD>	m_aRemapFields;			// 重映射的字段信息(3X)
	BYTE					m_acReserved[64];		// 保留数据
};














//////////////////////////////////////////////////////////////////////////
// 字典解析类
#define IXTODO_MODE				0X0000000F				// 模式				
#define IXTODO_NAKEREAD			0X00000000				//		裸读模式
#define IXTODO_READ				0X00000001				//		读标识				
#define IXTODO_WRITE			0X00000002				//		写模式
#define IXTODO_AUTOBUFFER		0X00000010				// 自动伸缩缓冲区				

#define IXPKGFORMAT_PKGVER		0X0000000F				// 数据包版本
#define IXPKGVER_2X				0X00000001				//		2X数据包(需要字典)
#define IXPKGVER_3X				0X00000002				//		3X数据包(不需要字典,或传送附带精简字典)
#define IXPKGFORMAT_PKGTYPE		0X000000F0				// 数据包类型
#define IXPKGTYPE_REQ			0X00000010				//		请求数据
#define IXPKGTYPE_ACK			0X00000020				//		应答数据
#define IXPKGTYPE_RS			0X00000030				//		数据集
#define IXPKGFORMAT_PKGOPT		0X0000FF00				// 包选项
#define IXPKGOPT_FIELDIDS		0X00000100				//		包含字段ID信息
#define IXPKGOPT_FIELDKEYS		0X00000200				//		包含字段名信息
#define IXPKGOPT_FIELDINFOS		0X00000400				//		包含字段详细信息
#define IXPKGOPT_NOFROMDICT		0X00000800				//		忽略字典进行创建


class ASELIB_API CIXCommon
{
public:
	CIXCommon(CIXDict* pDict=NULL,CIXCache* pCacheInst=NULL,BOOL bCaptureFatalError=FALSE);
	CIXCommon(CIXDict* pDict,LPBYTE pCacheBuf,DWORD cbCacheBuf,DWORD cbCacheUsed,BOOL bCaptureFatalError=FALSE);
	virtual ~CIXCommon();
public:
	// 设置和获取数据字典
	VOID		SetDict(CIXDict* pDict);		// 设置数据字典类实例
	CIXDict*	GetDict();						// 获取数据字典类实例
	// 设置字段缓存对象和获取
	VOID		SetCache(CIXCache* pCacheInst);
	VOID		SetCache(LPBYTE pCacheBuf,DWORD cbCacheBuf,DWORD cbCacheUsed);
	CIXCache*	GetCacheInst() { return m_pCacheInst; }
	LPBYTE		GetCacheBuf() { return m_pCacheBuf; }
	DWORD		GetCacheBufMax() { return m_cbCacheBuf; }
	DWORD		GetCacheUsed() { return m_cbCacheUsed; }
	BOOL		HasCacheFeature() { return m_pCacheInst!=NULL||m_pCacheBuf!=NULL; }
	// 创建结构,FALSE返回失败,TRUE返回成功
	BOOL		CreateStructAs(WORD wStructID,LPBYTE pBuffer,DWORD cbUsedLen,DWORD dwBuffLen,DWORD dwToDo,DWORD dwPkgFormat);
	BOOL		CreateStructToNodeWrite(WORD wStructID,LPBYTE pBuffer,DWORD dwBuffLen);
	BOOL		CreateStructToHostRead(WORD wStructID,LPBYTE pBuffer,DWORD dwBuffLen);
	BOOL		CreateStructToHostWrite(WORD wStructID,LPBYTE pBuffer,DWORD dwBuffLen,DWORD dwPkgFormatOfReq,BOOL bForceUsingDict=TRUE);
	BOOL		CreateStructToNodeRead(WORD wStructID,LPBYTE pBuffer,DWORD dwBuffLen);
	BOOL		CreateStructToRSWrite(WORD wStructID,LPBYTE pBuffer,DWORD dwBuffLen,BOOL bInherit,CIXCommon* pOwner);
	BOOL		CreateStructToRSRead(WORD wStructID,LPBYTE pBuffer,DWORD dwBuffLen,BOOL bInherit,CIXCommon* pOwner);
	BOOL		CreateStructAs(LPCSTR pszStructID,LPBYTE pBuffer,DWORD cbUsedLen,DWORD dwBuffLen,DWORD dwToDo,DWORD dwPkgFormat);
	BOOL		CreateStructToNodeWrite(LPCSTR pszStructID,LPBYTE pBuffer,DWORD dwBuffLen);
	BOOL		CreateStructToHostRead(LPCSTR pszStructID,LPBYTE pBuffer,DWORD dwBuffLen);
	BOOL		CreateStructToHostWrite(LPCSTR pszStructID,LPBYTE pBuffer,DWORD dwBuffLen,DWORD dwPkgFormatOfReq,BOOL bForceUsingDict=TRUE);
	BOOL		CreateStructToNodeRead(LPCSTR pszStructID,LPBYTE pBuffer,DWORD dwBuffLen);
	BOOL		CreateStructToRSWrite(LPCSTR pszStructID,LPBYTE pBuffer,DWORD dwBuffLen,BOOL bInherit,CIXCommon* pOwner);
	BOOL		CreateStructToRSRead(LPCSTR pszStructID,LPBYTE pBuffer,DWORD dwBuffLen,BOOL bInherit,CIXCommon* pOwner);
	BOOL		CreateStructNaked(LPBYTE pBuffer,DWORD dwBuffLen);
	BOOL		ModifyToDo(DWORD dwAdd,DWORD dwRemove);
	BOOL		ModifyPkgOpt(DWORD dwAdd,DWORD dwRemove);


	// 获取数据字典类实例,结构ID获取/长度获取(包括结束字符,创建字典读取会重置)
	DWORD		GetToDoMode() { return (m_dwToDo&IXTODO_MODE); }					// 获取用途
	DWORD		GetPkgFormat() { return m_dwPkgFormat; }							// 获取包格式
	DWORD		GetPkgVer() { return m_dwPkgFormat&IXPKGFORMAT_PKGVER; }			// 获取包版本
	DWORD		GetPkgType() { return m_dwPkgFormat&IXPKGFORMAT_PKGTYPE; }			// 获取包类型
	DWORD		GetPkgOpt() { return m_dwPkgFormat&IXPKGFORMAT_PKGOPT; }			// 获取包选项
	WORD		GetStructID() { return (WORD)atol(m_szStructID); }					// 获取当前结构ID
	LPCSTR		GetStructStrID() { return m_szStructID; }							// 获取当前结构ID(字符串)
	LPBYTE		GetBuffer();														// 得到数据区地址
	DWORD		GetUsedBufferLen();													// 得到已使用缓冲区长度(包括结束字符,若为读取,本函数无效)
	DWORD		GetUsedBufferLenNoNil();											// 得到已使用缓冲区长度(不包括结束字符,若为读取,本函数无效)
	DWORD		GetMaxBufferLen();													// 得到全部缓冲区长度(包括结束字符)
	DWORD		GetFatalError();													// 获取最后的致命错误
	DWORD		GetCommonError();													// 获取最后的常规错误
	LONG		GetFieldNum();														// 返回当前字段个数
	WORD		GetFieldIDAt(WORD wExtIndex);										// 获取字段ID(映射后)
	LPCSTR		GetFieldKeyAt(WORD wExtIndex);										// 获取字段KEY(映射后)
	BOOL		AddField(LPCSTR pszKey);											// 增加字段ID(映射后)
	BOOL		AddFieldAsKey(WORD wFieldID);										// 添加字段ID(映射后)
	BOOL		AddField(WORD wFieldID,LPCSTR pszKey=NULL,WORD wNickID=0);			// 增加字段ID(映射后)
	BOOL		AddField(FIELDINFO* pFieldInfo,LPCSTR pszKey=NULL,WORD wNickID=0);	// 增加字段ID(映射后)



	//////////////////////////////////////////////////////////////////////////
	// 写入公用接口
	BOOL		InitBuffer();																						// 初始化写缓冲区
	BOOL		AddEOL();																							// 添加行结束标志
	BOOL		IXEncode(CONST LPBYTE pIn,WORD wInLen,BOOL bSecure,BOOL bBase64,BOOL bConvCP,LPSTR pszBuf,DWORD nMaxBufLen,DWORD& cbFinal);
	BOOL		IXTryEncode(CONST LPBYTE pIn,WORD wInLen,BOOL bSecure,BOOL bBase64,BOOL bConvCP,LPSTR pszBuf,DWORD nMaxBufLen,DWORD& cbFinal,DWORD& cbNeed,DWORD& dwError);
	BOOL		IXDecode(LPCSTR pszIn,DWORD cbIn,BOOL bSecure,BOOL bBase64,BOOL bConvCP,LPBYTE pValue,WORD wMaxSize,WORD& wFinal);


	//////////////////////////////////////////////////////////////////////////
	// 请求集写入接口(IXPKGTYPE_REQ)

	// 直接填写字段
	BOOL		SetItemValue4X(WORD wFieldID,LPCSTR lpszValue,BOOL bSecure=FALSE);
	BOOL		SetItemFlagValue(WORD wFieldID,BYTE cFlag);
	BOOL		SetItemLongValue(WORD wFieldID,LONG nValue);
	BOOL		SetItemValue(WORD wFieldID,LPCSTR lpszValue,BOOL bSecure=FALSE);
	BOOL		SetItemBinaryValue(WORD wFieldID,CONST LPBYTE lpValue,WORD wSize,BOOL bSecure=FALSE,BOOL bBase64=TRUE);
	BOOL		SetItemIXCommonValue(WORD wFieldID,CIXCommon* pIXCommon);
	
	BOOL		SetItemValue4X(LPCSTR pszKey,LPCSTR lpszValue,BOOL bSecure=FALSE);
	BOOL		SetItemFlagValue(LPCSTR pszKey,BYTE cFlag);
	BOOL		SetItemLongValue(LPCSTR pszKey,LONG nValue);
	BOOL		SetItemValue(LPCSTR pszKey,LPCSTR lpszValue,BOOL bSecure=FALSE);
	BOOL		SetItemBinaryValue(LPCSTR pszKey,CONST LPBYTE lpValue,WORD wSize,BOOL bSecure=FALSE,BOOL bBase64=TRUE);
	BOOL		SetItemIXCommonValue(LPCSTR pszKey,CIXCommon* pIXCommon);

	// 缓存和COOKIES字段自动完成,如果返回无错误,则
	// 1.从缓存类中提取缓存字段放入当前数据行
	// 2.从缓存类中提取COOKIES字段放入当前数据行
	// (除客户校验/集成客户校验/获取缓存信息需要调用)
	BOOL		SetCacheAndCookiesItems();

	// 增加请求结束符
	BOOL		SetEOR();
	BOOL		SetAttachAndEOR(const BYTE* pAttach,DWORD cbAttach);



	//////////////////////////////////////////////////////////////////////////
	// 结果集写入接口(IXPKGTYPE_ACK,IXPKGTYPE_RS)

	// 为提高服务器端的效率,数据项必须按顺序填充
	BOOL		IsMemRealloced() { return m_bRealloced; }
	BOOL		IsDueToOverflow();
	DWORD		GetRestorePoint();
	BOOL		CommitOrRestore(DWORD dwRestorePoint);
	WORD		GetAliasIDOrFieldID(WORD wExtIndex);
	BOOL		AddItemValue4X(LPCSTR lpszValue,BOOL bSecure=FALSE);
	BOOL		AddItemFlagValue(BYTE cFlag);
	BOOL		AddItemLongValue(LONG nValue);
	BOOL		AddItemValue(LPCSTR lpszValue,BOOL bSecure=FALSE);
	BOOL		AddItemBinaryValue(CONST LPBYTE lpValue,WORD wSize,BOOL bSecure=FALSE,BOOL bBase64=TRUE);
	BOOL		AddItemIXCommonValue(CIXCommon* pIXCommon,BOOL bFashionable);

	// 返回时必须先填充返回值信息nRetcode=0为处理成功,其他为失败
	// 注:必须在完成全部字段填写后添加(只能调用一次)
	BOOL		SetReturn(LONG nRetCode,LPCSTR lpszMessage,LONG nRecordNum);
	BOOL		SetReturn2(LONG nRetCode,LPCSTR lpszMessage,LONG nRecordNum,CIXCookies* pCookies,LPCSTR lpszNextPageId);
	BOOL		SetReturn3(LONG nRetCode,LPCSTR lpszMessage,LONG nRecordNum,LPCSTR pszCookies,LONG nCookiesLen,LPCSTR lpszNextPageId);
	BOOL		SetAttachAndReturn(LONG nRetCode,LPCSTR lpszMessage,LONG nRecordNum,LPCSTR pszCookies,LONG nCookiesLen,LPCSTR lpszNextPageId,LPBYTE pAttach,WORD cbAttach);








	//////////////////////////////////////////////////////////////////////////
	// 读取公用接口

	// 获取数据区指针,长度和行数
	LPBYTE		GetContentPtr();		// 获取正文字地址
	DWORD		GetContentLen();		// 获取正文长度(包含结束字符)
	DWORD		GetContentLineNum();	// 获取正文行数(会重新查找,注意缓冲)

	// 获取附件缓冲区
	LPBYTE		GetAttachPtr();			// 获取附件指针
	ATTACHSIZE	GetAttachLen();			// 获取附件大小

	// 判定是否存在更多的数据
	// 返回:	(BOOL)		是否存在下一行
	BOOL		More();

	// 移动行指针到指定行/首行(客户端读取和服务器读取)
	// 参数:	dwLine		行号,0的时候移动到头部(返回状态信息行)
	// 返回:	(BOOL)		指定行是否存在
	BOOL		MoveToLine(DWORD dwLine);

	// 移动行指针到下一行
	// 返回:	(BOOL)		指定行是否存在
	BOOL		MoveNext();

	// 取得4.X兼容的字段
	LPCSTR		GetItemValue4X(WORD wExtIndex,LPSTR lpszValue,WORD wSize,BOOL bSecure=FALSE);
	LPCSTR		GetItemValueFromID4X(WORD wFieldID,LPSTR lpszValue,WORD wSize,BOOL bSecure=FALSE);
	LPCSTR		GetItemValueFromKey4X(LPCSTR pszKey,LPSTR lpszValue,WORD wSize,BOOL bSecure=FALSE);

	// 根据字段序号获取字段内容/根据字段ID获取字段内容
	// 返回0XFF表明获取失败
	BYTE		GetItemFlagValue(WORD wExtIndex,DWORD dwLineOffset=(DWORD)(-1));
	BYTE		GetItemFlagValueFromID(WORD wFieldID,DWORD dwLineOffset=(DWORD)(-1));
	BYTE		GetItemFlagValueFromKey(LPCSTR pszKey,DWORD dwLineOffset=(DWORD)(-1));

	// 根据字段序号获取字段内容/根据字段ID获取字段内容
	// 返回0XFFFFFFFF表明获取失败
	LONG		GetItemLongValue(WORD wExtIndex,DWORD dwLineOffset=(DWORD)(-1));
	LONG		GetItemLongValueFromID(WORD wFieldID,DWORD dwLineOffset=(DWORD)(-1));
	LONG		GetItemLongValueFromKey(LPCSTR pszKey,DWORD dwLineOffset=(DWORD)(-1));

	// 根据字段序号获取字段内容/根据字段ID获取字段内容
	// 返回NULL表明获取失败,如果输入缓冲区有效,缓冲区内部被清空
	LPCSTR		GetItemValue(WORD wExtIndex,LPSTR lpszValue,WORD wSize,BOOL bSecure=FALSE,DWORD dwLineOffset=(DWORD)(-1));
	LPCSTR		GetItemValueFromID(WORD wFieldID,LPSTR lpszValue,WORD wSize,BOOL bSecure=FALSE,DWORD dwLineOffset=(DWORD)(-1));
	LPCSTR		GetItemValueFromKey(LPCSTR pszKey,LPSTR lpszValue,WORD wSize,BOOL bSecure=FALSE,DWORD dwLineOffset=(DWORD)(-1));

	// 根据字段序号获取字段内容/根据字段ID获取字段内容
	// 返回FALSE表明获取失败,如果输入缓冲区有效,缓冲区内部不会被清空
	BOOL		GetItemBinaryValue(WORD wExtIndex,WORD wMaxSize,LPBYTE lpValue,WORD* pwSize,BOOL bSecure=FALSE,BOOL bBase64=TRUE,DWORD dwLineOffset=(DWORD)(-1));
	BOOL		GetItemBinaryValueFromID(WORD wFieldID,WORD wMaxSize,LPBYTE lpValue,WORD* pwSize,BOOL bSecure=FALSE,BOOL bBase64=TRUE,DWORD dwLineOffset=(DWORD)(-1));
	BOOL		GetItemBinaryValueFromKey(LPCSTR pszKey,WORD wMaxSize,LPBYTE lpValue,WORD* pwSize,BOOL bSecure=FALSE,BOOL bBase64=TRUE,DWORD dwLineOffset=(DWORD)(-1));

	// 根据字段ID获取字段内容(字典格式)
	BOOL		GetItemIXCommonValue(WORD wExtIndex,WORD wAsStructID,BOOL bInherit,CIXCommon* pIXCommon);
	BOOL		GetItemIXCommonValueFromID(WORD wFieldID,WORD wAsStructID,BOOL bInherit,CIXCommon* pIXCommon);
	BOOL		GetItemIXCommonValueFromKey(LPCSTR pszKey,WORD wAsStructID,BOOL bInherit,CIXCommon* pIXCommon);
	VOID		FreeIXCommonValue(CIXCommon* pIXCommon);

	// 矩阵化读取(矩阵化后不能按照正常方式读取)
	BOOL		ConvertMatrix();
	DWORD		GetMatrixRowNum() { return m_dwMatrixRow; }
	DWORD		GetMatrixColNum() { return m_dwMatrixCol; }
	LPCSTR*		operator[](LONG nRow) { return &m_ppszMatrixs[nRow*m_dwMatrixCol]; }





	//////////////////////////////////////////////////////////////////////////
	// 客户端读取操作接口(IXPKGTYPE_ACK,IXPKGTYPE_RS)

	// 获取字段信息
	FIELDINFO*	GetFieldInfoAt(WORD wExtIndex);
	FIELDINFO*	GetFieldInfoByID(WORD wFieldID);

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
	
	// 提取缓存字段到缓存缓冲区,如果返回无错误,则从当前返回的结果集中提取属性标识为CACHE的字段,放入缓存容器中
	BOOL		SaveCacheFields();

	// 提取COOKIES字段到缓存缓冲区,如果返回无错误,则从当前返回的结果集中提取属性标识为CACHE的字段,放入缓存容器中
	BOOL		SaveCookiesFields();



	//////////////////////////////////////////////////////////////////////////
	// 数据集合并
	DWORD CalcLengthToMerge(DWORD dwOriginSize);
	BOOL MergeTo(LPBYTE pTarget,DWORD cbTargetMax,DWORD& cbUsed);

protected:
	// 确保缓冲区
	BOOL		EnsureBuffer(DWORD cbNeed);

	// 初始化操作(反向索引和字段信息)
	BOOL		InitReverseIdxs();
	BOOL		InitFieldInfosFromDict();

	// 标志判定
	BOOL		IsDictFullySupport() { return m_pDict!=NULL&&(m_pDict->GetIXDictVer()>=IXDICTVER_3_00_L2||m_pDict->GetIXDictVer()<=IXDICTVER_COMPATIBLE); }
	BOOL		IsToRead() { return GetToDoMode()==IXTODO_NAKEREAD||GetToDoMode()==IXTODO_READ; }
	BOOL		IsToWrite() { return GetToDoMode()==IXTODO_WRITE; }
	BOOL		IsToWriteReq() { return IsToWrite()&&GetPkgType()==IXPKGTYPE_REQ; }
	BOOL		IsToReadAck() { return IsToRead()&&GetPkgType()==IXPKGTYPE_ACK; }
	BOOL		IsCanMapper() { return IsToRead(); } 

	// 添加字段信息(写入)
	BOOL		AddFieldDynamic(WORD wFieldID,FIELDINFO* pFieldInfo,LPCSTR pszKey,WORD wNickID);
	// 增加行结束符标志(写入)
	BOOL		AddEOLTag();
	// 添加版本信息(写入)
	BOOL		AddVerTag();
	// 添加字段描述表(写入)
	BOOL		AddFieldTag(DWORD dwOffset);
	// 添加附件字段(写入)
	BOOL		AddAttach(const BYTE* pAttach,DWORD cbAttach);

	// 计算摘要/字段定义/正文行序号,正文区尾部偏移,附件区长度,附件数据长度(读取和写入)
	DWORD		HardLineNoOfSummary();
	DWORD		HardLineNoOfFieldTag();
	DWORD		HardLineNoOfContent();
	DWORD		OffsetOfEndOfContent();
	DWORD		AttachAreaLen();
	DWORD		AttachDataLen();

	// 移动到指定行和移动到下一行(读取和写入)
	BOOL		HardSeekTo(DWORD dwLine);
	BOOL		HardSeekToNext();

	// 得到第N行的偏移
	// 参数:	dwLine		行号
	// 返回:	(DWORD)		位置偏移,ULONG_MAX表明行不存在
	DWORD		HardLineOffset(DWORD dwLine);

	// 得到第N行的宽度
	// 参数:	dwLine		行号
	// 返回:	(DWORD)		位置宽度,ULONG_MAX表明行不存在
	DWORD		HardLineLength(DWORD dwLine);

	// 得到第N行的缓冲区
	// 参数:	dwLine		行号
	// 返回:	(LPCSTR)	缓冲区起始位置
	LPCSTR		HardLineAddress(DWORD dwLine);

	// 得到物理行数
	// 返回:	(WORD)		行数
	DWORD		HardCalcLineCount();

	// 外部列转换为物理列
	BOOL		ExtIndex2PhyIndex(WORD wExtIndex,WORD& wPhyIndex);

	// 查找当前行中字段的起止位置(终止字符为下一个字段的开始字符)
	BOOL		FindFieldByPhyIndex(WORD wExtIndex,LPDWORD lpdwFieldBegin,LPDWORD lpdwFieldEnd,DWORD dwLineOffset);
	WORD		FindExtIndexByID(WORD wFieldID);
	WORD		FindExtIndexByKey(LPCSTR pszKey);

	// 添加和获取的内部处理函数
	BOOL		AddItemRawBinaryValue(CONST LPBYTE lpValue,WORD wSize,BOOL bSecure,BOOL bBase64,BOOL bConvCP);
	BOOL		SetItemRawBinaryValueByID(WORD wFieldID,CONST LPBYTE lpValue,WORD wSize,BOOL bSecure,BOOL bBase64,BOOL bConvCP);
	BOOL		SetItemRawBinaryValueByKey(LPCSTR pszKey,CONST LPBYTE lpValue,WORD wSize,BOOL bSecure,BOOL bBase64,BOOL bConvCP);
	BOOL		SetItemRawBinaryValueByExtIndex(WORD wExtIndex,CONST LPBYTE lpValue,WORD wSize,BOOL bSecure,BOOL bBase64,BOOL bConvCP);
	BOOL		GetItemRawBinaryValueByExtIndex(WORD wExtIndex,WORD wMaxSize,LPBYTE lpValue,WORD* pwSize,BOOL bSecure,BOOL bBase64,DWORD dwLineOffset,BOOL bConvCP);
	BOOL		GetItemRawBinaryValueByPhyIndex(WORD wPhyIndex,WORD wMaxSize,LPBYTE lpValue,WORD* pwSize,BOOL bSecure,BOOL bBase64,DWORD dwLineOffset,BOOL bConvCP);
	LPCSTR		GetItemRawTextValueByExtIndex(WORD wExtIndex,LPSTR lpszValue,WORD wSize,BOOL bSecure,DWORD dwLineOffset,BOOL bConvCP);
	BOOL		GetItemRawBinaryValueFromID(WORD wFieldID,WORD wMaxSize,LPBYTE lpValue,WORD* pwSize,BOOL bSecure,BOOL bBase64,DWORD dwLineOffset,BOOL bConvCP);
	BOOL		GetItemRawBinaryValueFromKey(LPCSTR pszKey,WORD wMaxSize,LPBYTE lpValue,WORD* pwSize,BOOL bSecure,BOOL bBase64,DWORD dwLineOffset,BOOL bConvCP);
	LPCSTR		GetItemRawTextValueFromID(WORD wFieldID,LPSTR lpszValue,WORD wSize,BOOL bSecure,DWORD dwLineOffset,BOOL bConvCP);
	LPCSTR		GetItemRawTextValueFromKey(LPCSTR pszKey,LPSTR lpszValue,WORD wSize,BOOL bSecure,DWORD dwLineOffset,BOOL bConvCP);
	LPCSTR		GetItemRawTextValueByPhyIndex(WORD wPhyIndex,LPSTR lpszValue,WORD wSize,BOOL bSecure,DWORD dwLineOffset,BOOL bConvCP);

	// 插入缓冲区(写入操作)
	BOOL		InitLineStruct();
	BOOL		ReplaceToBuffer(DWORD dwFieldBegin,DWORD dwFieldEnd,LPBYTE pszField,DWORD cbField);
	BOOL		InsertToBuffer(DWORD dwOffset,LPBYTE pszField,DWORD cbField);
	VOID		TruncateOnError();

	// 代码页转换
	LONG		ConvertIXCommonCodePage(LPSTR pszBuf,LONG nLen,LONG nMaxSize,BOOL bToUser);
private:
	CIXDict*			m_pDict;						// 数据字典类指针
	CIXCache*			m_pCacheInst;					// 数据缓存类指针
	LPBYTE				m_pCacheBuf;					// 缓存区指针
	DWORD				m_cbCacheBuf;					// 缓存区大小
	DWORD				m_cbCacheUsed;					// 缓存数据大小
	BOOL				m_bCaptureFatalError;			// 是否捕获致命错误
	DWORD				m_dwToDo;						// 操作
	DWORD				m_dwPkgFormat;					// 包格式
	CHAR				m_szStructID[32];				// 功能ID
	LPBYTE				m_pBuffer;						// 缓冲区信息
	DWORD				m_cbUsedLen;					// 当前缓冲区已经使用的
	DWORD				m_cbMaxBufLen;					// 缓冲区长度

	BOOL				m_bEOIX;						// 结束标志
	BOOL				m_bStructCreated;				// 结构是否创建
	BOOL				m_bLineStructInit;				// (写入)当前行结构是否已经初始化(逐字段添加时在添加第一个字段的时候添加全部的记录分割字)
	WORD				m_wFieldNum;					// 字段数
	FIELDREF			m_aFieldRefs[IXFIELD_MAX];		// 字段引用
	LPCSTR				m_apszFieldKeys[IXFIELD_MAX];	// 字段KEY值
	TCHAR				m_szFieldKeys[256];				// KEY值缓冲区
	DWORD				m_cbFieldKeys;					// KEY值缓冲区使用长度
	WORD				m_awFieldPhyIdxs[IXFIELD_MAX];	// 字段索引(下标是逻辑列,数值指向物理列)
	WORD				m_awFieldExtIdxs[IXFIELD_MAX];	// 字段索引(下标是物理列,数值指向逻辑列)
	CIXArray<FIELDINFO>	m_aFieldInfos;					// 字段信息

	DWORD				m_dwLineOffset;					// 当前行偏移(读取方式下有效)
	LPCSTR*				m_ppszMatrixs;					// 数据矩阵(矩阵模式有效)
	DWORD				m_dwMatrixRow;					// 矩阵行数
	DWORD				m_dwMatrixCol;					// 矩阵列数
	DWORD				m_dwIXFatalError;				// 最后致命错误
	DWORD				m_dwIXCommonError;				// 最后非致命错误
	BOOL				m_bRealloced;					// 内存是否经过重新分配
	BYTE				m_aReserved[60];				// 保留字节
};

#pragma pack()
#endif
