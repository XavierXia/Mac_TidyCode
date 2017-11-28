#ifndef __XML__H__
#define __XML__H__
#include "../safevcrt.h"

//////////////////////////////////////////////////////////////////////////
// 应用示例
//		1.装载XML文件
//			CXML Xml("ROOT");
//			Xml.LoadXmlFile("C:\\TEST.XML");
//		2.创建根节点以及清除根目录下的全部节点
//			HXMLNODE hNodeParent=Xml.CreateXmlNode(NULL,"ROOT");
//			Xml.DeleteAllChildXmlNode(hNodeParent);
//		3.创建节点以及设置属性
//			{	HXMLNODE hNode=NULL;
//				hNode=Xml.CreateXmlNode(hNodeParent,"ITEM",XMLNODE_KEYSET,XMLCREATE_APPEND|XMLCREATE_CREATEALWAYS);
//				Xml.SetXmlAttribValue(hNode,"ID","1");
//				hNode=Xml.CreateXmlNode(hNodeParent,"ITEM",XMLNODE_KEYSET,XMLCREATE_APPEND|XMLCREATE_CREATEALWAYS);
//				Xml.SetXmlAttribValue(hNode,"ID","2");
//				hNode=Xml.CreateXmlNode(hNodeParent,"ITEM",XMLNODE_KEYSET,XMLCREATE_APPEND|XMLCREATE_CREATEALWAYS);
//				Xml.SetXmlAttribValue(hNode,"ID","3");
//				hNode=Xml.CreateXmlNode(hNodeParent,"ITEM",XMLNODE_KEYSET,XMLCREATE_APPEND|XMLCREATE_CREATEALWAYS);
//				Xml.SetXmlAttribValue(hNode,"ID","4");
//				hNode=Xml.CreateXmlNode(hNodeParent,"ITEM",XMLNODE_KEYSET,XMLCREATE_APPEND|XMLCREATE_CREATEALWAYS);
//				Xml.SetXmlAttribValue(hNode,"ID","5");
//				hNode=Xml.CreateXmlNode(hNodeParent,"ITEM",XMLNODE_KEYSET,XMLCREATE_APPEND|XMLCREATE_CREATEALWAYS);
//				Xml.SetXmlAttribValue(hNode,"ID","6");
//			}
//		4.通过遍历删除子节点
//			{	HXMLNODE hNode=Xml.GetChildXmlNode(hNodeParent);
//				while(hNode!=NULL)
//				{	HXMLNODE hXmlNodeDeleted=hNode;
//					hNode=Xml.GetNextXmlNode(hNode);
//					LPCSTR pszID=Xml.GetXmlAttribValue(hXmlNodeDeleted,"ID");
//					if(stricmp(pszID,"3")==0)
//						Xml.DeleteChildXmlNode(hXmlNodeDeleted);
//				}
//			}
//		5.通过属性删除节点
//			{	Xml.DeleteChildXmlNode(hNodeParent,"ITEM","ID","1");
//				Xml.DeleteChildXmlNode(hNodeParent,"ITEM","ID","2");
//				Xml.DeleteChildXmlNode(hNodeParent,"ITEM","ID","6");
//				Xml.DeleteChildXmlNode(hNodeParent,"ITEM","ID","5");
//				Xml.DeleteChildXmlNode(hNodeParent,"ITEM","ID","3");
//				Xml.DeleteChildXmlNode(hNodeParent,"ITEM","ID","4");
//			}
//		6.添加节点和属性
//			{	HXMLNODE hNode=Xml.CreateXmlNode(hNodeParent,"ITEM",XMLNODE_KEYSET,XMLCREATE_APPEND|XMLCREATE_CREATEALWAYS);
//				Xml.SetXmlAttribValue(hNode,"ID","11");
//				hNode=Xml.CreateXmlNode(hNodeParent,"ITEM",XMLNODE_KEYSET,XMLCREATE_APPEND|XMLCREATE_CREATEALWAYS);
//				Xml.SetXmlAttribValue(hNode,"ID","12");
//				hNode=Xml.CreateXmlNode(hNodeParent,"ITEM",XMLNODE_KEYSET,XMLCREATE_APPEND|XMLCREATE_CREATEALWAYS);
//				Xml.SetXmlAttribValue(hNode,"ID","13");
//				hNode=Xml.CreateXmlNode(hNodeParent,"ITEM",XMLNODE_KEYSET,XMLCREATE_APPEND|XMLCREATE_CREATEALWAYS);
//				Xml.SetXmlAttribValue(hNode,"ID","14");
//				hNode=Xml.CreateXmlNode(hNodeParent,"ITEM",XMLNODE_KEYSET,XMLCREATE_APPEND|XMLCREATE_CREATEALWAYS);
//				Xml.SetXmlAttribValue(hNode,"ID","15");
//				hNode=Xml.CreateXmlNode(hNodeParent,"ITEM",XMLNODE_KEYSET,XMLCREATE_APPEND|XMLCREATE_CREATEALWAYS);
//				Xml.SetXmlAttribValue(hNode,"ID","16");
//			}
//		7.设置代码页以及保存XML
//			Xml.SetCodePage(936);
//			Xml.SaveXmlFile("C:\\TEST.XML");
//////////////////////////////////////////////////////////////////////////
// 关于汉字编码和XML的解析
// 汉字以及其他亚洲区域语言均采用变长编码(以双字节为主,对于汉字只需要双字节,英文字母需要单字节),不同
// 于西方语种采用单词的组合方式可以使用单字节编码方式汉字和英文字符混合时,双字节和单字节的混合会造成
// 解析的不便,这种情况下必须判断编码空间以正确的拆分汉字.
// 简体汉字的编码规范主要包括GB2312和GBK,GB2312的编码范围为0XA1A1-0XFEFE,其中汉字范围为0XB0A1-0XF7FE
// 共收录7445个图形字符,其中汉字占6763,小于汉字字符总数,GBK扩展了GB2312的编码范围,扩充后容纳汉字字符
// 数范围可覆盖基本全部汉字,范围为0X8140-0XFEFE,可兼容UNICODE2.0规范.对于GB2312而言每个字节的范围均在
// 0XA1-0XFE之间,和标准ASCII编码空间不会出现重叠的现象,可以很容易的进行解析并能不完整的汉字字符进行识
// 别和处理,扩充到GBK后,字符低位范围为0X81-0XFE,不会和标准ASCII编码空间重叠,但高位位于0X40-0XFE范围,
// 会和标准ASCII编码范围重叠(0X00-0X7F),会影响对ASCII的识别(如典型的'宖'字会影响'|'(0X7C)的判断),不过
// GBK是强制性的,也称大字符集,包含了GB2312,CJK,BIG5,这也是简体系统显示的繁体中文和BIG存在区别的主要原
// 因其主要原因是因为GBK的BIG5区在内码上和真正意义的BIG5并不完全对等。GBK并非国家标准,仅仅为事实标准,
// GBK最终扩展为GB18030,支持蒙藏语言.
// +------------------------------------------------------+
// |              |  B0   |  B1         |   B2  |  B3     |
// |------------------------------------------------------|
// |ASCII	      | 00-7F |             |       |         |
// |GB2312-1980   | A0-FE | A0-FE       |       |         |
// |GB2312(完整)  | B0-F7 | A0-FE       |       |         |
// |GB13000(GBK)  | 81-FE | 40-7E/80-FE |       |         |
// |GB18030       | 81-FE | 30-39       | 81-FE |  30-39  |
// +------------------------------------------------------+
// 
//////////////////////////////////////////////////////////////////////////
// 关于XML的解析
// 1.当前类不支持XSD等规范,主要是对效率的考究
// 2.当前类不支持转义(_T("&lt;"),_T("&amp;"),_T("&gt;"),_T("&apos;"),_T("&quot;")),拟后期对之进行支持
// 3.鉴于GB18030以及BIG5等内码范围和特殊标记范围并不重叠,所以解析的时候转换为指定代码页的MBCS进行处理
// 4.内存使用上尽量会使用栈和内存池以进一步提高性能,不过鉴于实际的操作复杂度,不可避免的依然保留有部分
//   直接申请的部分

// XML创建标志
typedef enum enumXMLCREATEFLAG
{	XMLCREATE_NULL,					// 不进行创建
	XMLCREATE_FORCE=1,				// 强制创建,忽略只读标志
	XMLCREATE_APPEND=2,				// 在尾部创建(默认)
	XMLCREATE_INSERT=4,				// 在头部创建
	XMLCREATE_CREATEALWAYS=8,		// 不论是否存在均创建(跳过重名节点的检查)
	XMLCREATE_RECREATE=16,			// 重新建立标志(删除对应节下的全部数据)
} XMLCREATEFLAG;

// XML节点标志(类型)
typedef enum enumXMLNODEFLAG
{	XMLNODE_SYSKEY,					// 系统节点,以?开始和结束,无子节点
	XMLNODE_ITEMKEY,				// 不包含子节点的键,格式为:<KEYNAME PAR='???'/>
	XMLNODE_KEYSET,					// 包含子节点的键,格式为:<KEYNAME PAR='???'></KEYNAME>
	XMLNODE_VALUE,					// 包含的是一个值,总被包含在指定的KEYSET中
	XMLNODE_UNKNOWN,				// 未知类型
	XMLNODE_COMMENT,				// 注释类型
} XMLNODEFLAG;

struct __HXMLNODE {};
typedef __HXMLNODE* HXMLNODE;		// XML节点句柄
struct __HXMLATTRIB {};
typedef __HXMLATTRIB* HXMLATTRIB;	// XML属性句柄

// XML核心类
class THeapList;
class LITEXML_IMP CXMLCore
{
public:
	CXMLCore(LPCTSTR pszRoot);
	virtual~CXMLCore();

	// 节点枚举,查找以及创建修改
	virtual DWORD GetXmlNodeFlag(HXMLNODE hNode) { return ((LPXMLNODE)hNode)->m_dwFlag; }
	virtual LPCTSTR GetXmlNodeKey(HXMLNODE hNode) { return ((LPXMLNODE)hNode)->m_Key.m_pStr; }
	virtual LPCTSTR GetXmlNodeValue(HXMLNODE hNode);
	virtual HXMLNODE GetParentXmlNode(HXMLNODE hNode) { return (hNode==NULL)?NULL:((LPXMLNODE)hNode)->m_hParent; }
	virtual HXMLNODE GetChildXmlNode(HXMLNODE hParentNode) { return (hParentNode==NULL)?(HXMLNODE)m_pNodeLinks:((LPXMLNODE)hParentNode)->m_hChild; }
	virtual HXMLNODE GetNextXmlNode(HXMLNODE hNode) { return (hNode==NULL)?NULL:((LPXMLNODE)hNode)->m_hNext; }
	virtual HXMLNODE FindXmlNode(HXMLNODE hParentNode,LPCTSTR pszKey);
	virtual HXMLNODE CreateXmlNode(HXMLNODE hParentNode,LPCTSTR pszKey,DWORD dwFlag=XMLNODE_KEYSET,DWORD dwCreateFlag=XMLCREATE_APPEND);
	virtual HXMLNODE CreateXmlNode(HXMLNODE hParentNode,HXMLNODE hPreviousNode,LPCTSTR pszStr,LONG nSize,DWORD dwFlag);
	virtual HXMLNODE CreateXmlWithPath(LPCTSTR lpszXmlPath,DWORD dwFlag=XMLNODE_KEYSET,DWORD dwCreateFlag=XMLCREATE_APPEND);
	virtual HXMLNODE FindXmlWithPath(LPCTSTR lpszXmlPath);
	virtual BOOL DeleteChildXmlNode(HXMLNODE hNode);
	virtual BOOL DeleteChildXmlNode(HXMLNODE hParentNode,LPCTSTR pszKey);
	virtual BOOL DeleteChildXmlNode(HXMLNODE hParentNode,LPCTSTR pszKey,LPCTSTR pszName,LPCTSTR pszValue);
	virtual BOOL SetXmlNodeValue(HXMLNODE hNode,LPCTSTR pszValue);
	virtual BOOL SetXmlNodeFlag(HXMLNODE hNode,DWORD dwAdd) { ((LPXMLNODE)hNode)->m_dwFlag=dwAdd; return TRUE; }
	
	// 属性枚举,查找以及创建修改
	virtual LPCTSTR GetXmlAttribName(HXMLATTRIB hAttrib) { return ((LPXMLATTRIB)hAttrib)->m_Name.m_pStr; }
	virtual LPCTSTR GetXmlAttribValue(HXMLATTRIB hAttrib) { return ((LPXMLATTRIB)hAttrib)->m_Value.m_pStr; }
	virtual LPCTSTR GetXmlAttribValue(HXMLNODE hNode,LPCTSTR pszName);
	virtual HXMLATTRIB GetFirstXmlAttrib(HXMLNODE hParentNode);
	virtual HXMLATTRIB GetNextXmlAttrib(HXMLATTRIB hAttrib);
	virtual HXMLATTRIB FindXmlAttrib(HXMLNODE hNode,LPCTSTR pszName);
	virtual HXMLATTRIB CreateXmlAttrib(HXMLNODE hNode,LPCTSTR pszName);
	virtual HXMLATTRIB CreateXmlAttrib(HXMLNODE hNode,HXMLATTRIB hPreviousAttrib) { return (HXMLATTRIB)AllocXmlAttrib((LPXMLNODE)hNode,(LPXMLATTRIB)hPreviousAttrib); }
	virtual BOOL SetXmlAttribValue(HXMLATTRIB hAttrib,LPCTSTR pszAttribName,LPCTSTR pszAttribValue);
	virtual BOOL SetXmlAttribValue(HXMLNODE hNode,LPCTSTR pszName,LPCTSTR pszValue);
	virtual BOOL DeleteXmlAttrib(HXMLNODE hNode,LPCTSTR pszName);
	virtual BOOL ResetXmlNodeAttribs(HXMLNODE hNode);

private:
	// XML快速字符串
	typedef struct tagXMLSMALLSTR { BYTE m_szStr[16]; } XMLSMALLSTR;

	// XML字符串
	typedef struct tagXMLSTR
	{	char*		m_pStr;			// 字符串内容
		BOOL		m_bSmallStr;	// 是否是小字符串(小字符串位于可用空间表中)
	} XMLSTR,*LPXMLSTR;

	// XML节点结构
	typedef struct tagXMLNODE
	{	HXMLNODE	m_hParent;		// 父节点句柄
		HXMLNODE	m_hNext;		// 兄弟节点句柄
		HXMLNODE	m_hChild;		// 子节点句柄
		XMLSTR		m_Key;			// 键值
		HXMLATTRIB	m_hAttrib;		// 属性指针
		DWORD		m_dwFlag;		// 节点标识
	} XMLNODE,*LPXMLNODE;

	// XML属性结构
	typedef struct tagXMLATTRIB
	{	HXMLATTRIB	m_hNext;		// 下一个属性
		XMLSTR		m_Name;			// 属性名称
		XMLSTR		m_Value;		// 属性数据
	} XMLATTRIB,*LPXMLATTRIB;

private:
	// 可用空间表分配和释放
	VOID AllocXmlStr(XMLSTR& XmlStr,LPCTSTR pszStr,LONG nSize);
	VOID AllocXmlStr(XMLSTR& XmlStr,LONG nSize);
	LPXMLNODE AllocXmlNodeAtHead(LPXMLNODE pParentNode);
	LPXMLNODE AllocXmlNodeAtTail(LPXMLNODE pParentNode);
	LPXMLNODE AllocXmlNodeAtSysTail(LPXMLNODE pParentNode);
	LPXMLATTRIB AllocXmlAttribAtTail(LPXMLNODE pParentNode);
	LPXMLNODE AllocXmlNode(LPXMLNODE pParentNode,LPXMLNODE pPreviousNode);
	LPXMLATTRIB AllocXmlAttrib(LPXMLNODE pParentNode,LPXMLATTRIB pPreviousAttrib);
	VOID FreeXmlStr(XMLSTR& XmlStr);
	VOID FreeXmlNode(LPXMLNODE pNode);
	VOID FreeXmlAttrib(LPXMLATTRIB pAttrib);
private:
	THeapList* m_pheapXmlNodes;		// XML节点可用空间表
	THeapList* m_pheapXmlAttribs;	// XML属性可用空间表
	THeapList* m_pheapXmlSmallStrs;	// XML小字符串表
	LPXMLNODE m_pNodeLinks;			// XML节点链表
	TCHAR m_szRootDef[256];			// XML根节点
};


// XML处理类
class LITEXML_IMP CXML : public CXMLCore
{
public:
	CXML(LPCTSTR pszRoot,UINT nLANGCodePage=CP_GB2312);
	virtual~CXML();

	// 从XML缓冲区中装载
	// 1.XML缓冲区必须是完整的字节流,但不必须以空字符结束
	// 2.XML缓冲区支持BOM标记,对UTF8,UNICODE支持
	// 3.XML缓冲区长度也不必须包含空字符的长度
	BOOL LoadXmlFile(LPCTSTR lpszXmlFile,LPCSTR pszSecKey=NULL,UINT nFileLANGCodePage=CP_GB2312);
	BOOL LoadXmlMem(const unsigned char* lpXmlBuf,LONG nXmlLen,UINT nFileLANGCodePage=CP_GB2312);

	// 保存XML文本到文件或缓冲区
	BOOL SaveXmlFile(LPCTSTR lpszXmlFile,LPCSTR pszSecKey=NULL,UINT nFileLANGCodePage=CP_GB2312,UINT nFileCONVCodePage=CP_UTF8);
	BOOL SaveXmlMem(unsigned char* lpXmlBuf,LONG nXmlBufLen,LONG* pnUsedOrNeeded,UINT nFileLANGCodePage=CP_GB2312,UINT nFileCONVCodePage=CP_UTF8);

	// 释放XML文件内容
	VOID FreeXml();
	VOID FreeXmlButRoot();

	// 得到当前代码页和版本
	UINT GetLANGCodePage();
	UINT GetFileLANGCodePage();
	UINT GetFileCONVCodePage();
	FLOAT GetVersion();
	VOID SetLANGCodePage(UINT nLANGCodePage);
	VOID SetFileLANGCodePage(UINT nFileLANGCodePage);
	VOID SetFileCONVCodePage(UINT nFileCONVCodePage);

	// 从XML文件中或者缓冲区中装载指定的节点到指定节点下
	// 如果根路径为NULL,目标XML的根下的全部节点将被复制,否则指定路径下的节点将被复制
	BOOL LoadFeatureFromXmlFile(HXMLNODE hNode,LPCTSTR lpszXmlFile,LPCSTR pszSecKey,UINT nFileLANGCodePage,LPCTSTR pszRoot,BOOL bCopyRoot=FALSE);
	BOOL LoadFeatureFromXmlMem(HXMLNODE hNode,const unsigned char* lpXmlBuf,LONG nXmlLen,UINT nFileLANGCodePage,LPCTSTR pszRoot,BOOL bCopyRoot=FALSE);
	BOOL LoadFeatureFromXml(HXMLNODE hNode,CXML* pXml,LPCTSTR pszRoot,BOOL bCopyRoot);

	// 从INI文件中或者装载节点到指定的节点下
	BOOL LoadFeatureFromIniFile(HXMLNODE hNode,LPCTSTR lpszIniFile,UINT nFileLANGCodePage);
	BOOL LoadFeatureFromIniMem(HXMLNODE hNode,LPCBYTE pszIniBuf,LONG nIniLen,UINT nFileLANGCodePage);

	// 从JSON文件或者内存中装载节点到指定的节点下
	BOOL LoadFeatureFromJsonMem(HXMLNODE hNode,LPCBYTE pszJsonBuf,LONG nJsonLen);

	// 获取根节点
	HXMLNODE GetRoot();

	// 配置读取和配置写入(基本)
	//		调用方法:	GetXmlProfileString("root/somevalue",...);
	//		XML样例:	<root>
	//						<somevalue>VALUE</somevalue>
	//					</root>
	INT GetProfileInt(LPCSTR lpszKeyPath,INT nDefault);
	DWORD GetProfileString(LPCSTR lpszKeyPath,LPCSTR lpDefault,LPSTR lpReturnedString,DWORD nSize);
	LPCSTR GetProfileString(LPCSTR lpszKeyPath,LPCSTR lpDefault);
	time_t GetProfileDateTime(LPCSTR lpszKeyPath);
	BOOL SetProfileInt(LPCSTR lpszKeyPath,INT nValue);
	BOOL SetProfileString(LPCSTR lpszKeyPath,LPCSTR pszValue);
	BOOL SetProfileDateTime(LPCSTR lpszKeyPath,time_t tValue);

	// 配置读取和配置写入(扩展)
	//		调用方法:	GetXmlProfileString("root/somevalue","DATA",...);
	//		XML样例:	<root>
	//						<somevalue DATA="VALUE"/>
	//					</root>
	INT GetProfileIntEx(LPCSTR lpszKeyPath,LPCSTR lpszAttrib,INT nDefault);
	DWORD GetProfileStringEx(LPCSTR lpszKeyPath,LPCSTR lpszAttrib,LPCSTR lpDefault,LPSTR lpReturnedString,DWORD nSize);
	LPCSTR GetProfileStringEx(LPCSTR lpszKeyPath,LPCSTR lpszAttrib,LPCSTR lpDefault);
	time_t GetProfileDateTimeEx(LPCSTR lpszKeyPath,LPCSTR lpszAttrib);
	BOOL SetProfileIntEx(LPCSTR lpszKeyPath,LPCSTR lpszAttrib,INT nValue);
	BOOL SetProfileStringEx(LPCSTR lpszKeyPath,LPCSTR lpszAttrib,LPCSTR pszValue);
	BOOL SetProfileDateTimeEx(LPCSTR lpszKeyPath,LPCSTR lpszAttrib,time_t tValue);

	// 路径查找和创建(支持扩展)
	HXMLNODE CreateXmlNodeEx(HXMLNODE hParentNode,LPCTSTR lpszXmlPath,DWORD dwFlag=XMLNODE_KEYSET,DWORD dwCreateFlag=XMLCREATE_APPEND);
	HXMLNODE FindXmlNodeEx(HXMLNODE hParentNode,LPCTSTR lpszXmlPath);

	// 路径查找和属性数值读取
	HXMLNODE FindXmlNodeWithAttrib(HXMLNODE hParentNode,LPCTSTR pszKey,LPCTSTR pszName,LPCTSTR pszValue);
	LPCTSTR GetXmlValueWithPath(LPCTSTR lpszXmlPath);
	LPCTSTR GetXmlAttribValueWithPath(LPCTSTR lpszXmlPath,LPCTSTR pszName);

	// 路径创建和数值和属性设置
	BOOL SetXmlValueWithPath(LPCTSTR lpszXmlPath,LPCTSTR lpszValue);
	BOOL SetXmlAttribValueWithPath(LPCTSTR lpszXmlPath,LPCTSTR pszName,LPCTSTR lpszValue);

	// 重置节点的数据(删除全部属性和子节点)
	BOOL ResetXmlNode(HXMLNODE hNode);
	// 删除全部节点的子节点(不包括父节点)
	BOOL DeleteAllChildXmlNode(HXMLNODE hParentNode);

	// 水印生成
	BOOL GenerateWaterMark(LPCTSTR pszRoot,char* pszWaterMark,LONG nWaterMarkLen,BOOL bWithAttrib=FALSE);

protected:
	// XML词法分析
	UINT GetXmlInfo(char* lpszXml,FLOAT& fVersion);
	BOOL ParsingAndLoadXml(char* lpszXml,UINT nFileLANGCodePage,UINT nFileCONVCodePage,FLOAT fVersion);
	BOOL ParsingAndLoadJson(HXMLNODE hParentNode,LONG& nNodeLevel,char*& pszParsing);
	LPCTSTR FindXmlKeyOrAttribBegin(LPCTSTR lpszXml);
	LPCTSTR FindXmlKeyOrAttribEnd(LPCTSTR lpszXmlTokenBegin);
	LPCTSTR FindXmlAttribEqual(LPCTSTR lpszXml);
	LPCTSTR FindXmlAttribValueBegin(LPCTSTR lpszXml,BOOL& bSingleComma);
	LPCTSTR FindXmlAttribValueEnd(LPCTSTR lpszXmlAttribValue,BOOL bSingleComma);

	// 复制节点和子节点
	VOID CopyXmlNodes(HXMLNODE hNodeTo,CXML* pFrom,HXMLNODE hXmlNodeFrom,BOOL bCopyChilds);

	// 其他函数
	VOID CatXmlLine(char* lpXml,LONG nXmlBufLen,LONG* pnUsed,LPCTSTR lpszAdd,LONG nAddLen);

	// 流输出回调函数(递归函数)
	LPCSTR XMLDecoding(LPSTR pszTemp,DWORD cbTemp,LPCSTR pszIn,DWORD cbIn);
	LPCSTR XMLEncoding(LPSTR pszTemp,DWORD cbTemp,LPCSTR pszIn);
	VOID SaveXmlNodeAndChilds(HXMLNODE hNode,char* lpXml,LONG nXmlBufLen,LONG* pnUsed,LONG nLevel,LPSTR pszEncodedKey,DWORD cbEncodedKey,LPSTR pszEncodedVal,DWORD cbEncodedVal);

	// 水印收集回调函数(递归函数)
	VOID WaterMarkXmlNodeAndChilds(HXMLNODE hNode,char** lppszBuffer,LONG* pnBufferSize,LONG* pnUsed,BOOL bWithAttrib);

	// 转换内码
	VOID XMLConvertCodePage(LPSTR pszBuf,LONG nMaxLen,UINT nExternCodePage,BOOL bLoad);
protected:
	UINT m_nLANGCodePage;			// MBCS表达时的代码页
	UINT m_nFileLANGCodePage;		// 文件交互时MBCS表达的代码页
	UINT m_nFileCONVCodePage;		// 最近装载使用的代码页
	FLOAT m_fVersion;				// XML文件版本
};



#endif

