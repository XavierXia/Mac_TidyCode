#ifndef __XML__H__
#define __XML__H__
#include "../safevcrt.h"

//////////////////////////////////////////////////////////////////////////
// Ӧ��ʾ��
//		1.װ��XML�ļ�
//			CXML Xml("ROOT");
//			Xml.LoadXmlFile("C:\\TEST.XML");
//		2.�������ڵ��Լ������Ŀ¼�µ�ȫ���ڵ�
//			HXMLNODE hNodeParent=Xml.CreateXmlNode(NULL,"ROOT");
//			Xml.DeleteAllChildXmlNode(hNodeParent);
//		3.�����ڵ��Լ���������
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
//		4.ͨ������ɾ���ӽڵ�
//			{	HXMLNODE hNode=Xml.GetChildXmlNode(hNodeParent);
//				while(hNode!=NULL)
//				{	HXMLNODE hXmlNodeDeleted=hNode;
//					hNode=Xml.GetNextXmlNode(hNode);
//					LPCSTR pszID=Xml.GetXmlAttribValue(hXmlNodeDeleted,"ID");
//					if(stricmp(pszID,"3")==0)
//						Xml.DeleteChildXmlNode(hXmlNodeDeleted);
//				}
//			}
//		5.ͨ������ɾ���ڵ�
//			{	Xml.DeleteChildXmlNode(hNodeParent,"ITEM","ID","1");
//				Xml.DeleteChildXmlNode(hNodeParent,"ITEM","ID","2");
//				Xml.DeleteChildXmlNode(hNodeParent,"ITEM","ID","6");
//				Xml.DeleteChildXmlNode(hNodeParent,"ITEM","ID","5");
//				Xml.DeleteChildXmlNode(hNodeParent,"ITEM","ID","3");
//				Xml.DeleteChildXmlNode(hNodeParent,"ITEM","ID","4");
//			}
//		6.���ӽڵ������
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
//		7.���ô���ҳ�Լ�����XML
//			Xml.SetCodePage(936);
//			Xml.SaveXmlFile("C:\\TEST.XML");
//////////////////////////////////////////////////////////////////////////
// ���ں��ֱ����XML�Ľ���
// �����Լ����������������Ծ����ñ䳤����(��˫�ֽ�Ϊ��,���ں���ֻ��Ҫ˫�ֽ�,Ӣ����ĸ��Ҫ���ֽ�),��ͬ
// ���������ֲ��õ��ʵ���Ϸ�ʽ����ʹ�õ��ֽڱ��뷽ʽ���ֺ�Ӣ���ַ����ʱ,˫�ֽں͵��ֽڵĻ�ϻ����
// �����Ĳ���,��������±����жϱ���ռ�����ȷ�Ĳ�ֺ���.
// ���庺�ֵı���淶��Ҫ����GB2312��GBK,GB2312�ı��뷶ΧΪ0XA1A1-0XFEFE,���к��ַ�ΧΪ0XB0A1-0XF7FE
// ����¼7445��ͼ���ַ�,���к���ռ6763,С�ں����ַ�����,GBK��չ��GB2312�ı��뷶Χ,��������ɺ����ַ�
// ����Χ�ɸ��ǻ���ȫ������,��ΧΪ0X8140-0XFEFE,�ɼ���UNICODE2.0�淶.����GB2312����ÿ���ֽڵķ�Χ����
// 0XA1-0XFE֮��,�ͱ�׼ASCII����ռ䲻������ص�������,���Ժ����׵Ľ��н������ܲ������ĺ����ַ�����ʶ
// ��ʹ���,���䵽GBK��,�ַ���λ��ΧΪ0X81-0XFE,����ͱ�׼ASCII����ռ��ص�,����λλ��0X40-0XFE��Χ,
// ��ͱ�׼ASCII���뷶Χ�ص�(0X00-0X7F),��Ӱ���ASCII��ʶ��(����͵�'�f'�ֻ�Ӱ��'|'(0X7C)���ж�),����
// GBK��ǿ���Ե�,Ҳ�ƴ��ַ���,������GB2312,CJK,BIG5,��Ҳ�Ǽ���ϵͳ��ʾ�ķ������ĺ�BIG�����������Ҫԭ
// ������Ҫԭ������ΪGBK��BIG5���������Ϻ����������BIG5������ȫ�Եȡ�GBK���ǹ��ұ�׼,����Ϊ��ʵ��׼,
// GBK������չΪGB18030,֧���ɲ�����.
// +------------------------------------------------------+
// |              |  B0   |  B1         |   B2  |  B3     |
// |------------------------------------------------------|
// |ASCII	      | 00-7F |             |       |         |
// |GB2312-1980   | A0-FE | A0-FE       |       |         |
// |GB2312(����)  | B0-F7 | A0-FE       |       |         |
// |GB13000(GBK)  | 81-FE | 40-7E/80-FE |       |         |
// |GB18030       | 81-FE | 30-39       | 81-FE |  30-39  |
// +------------------------------------------------------+
// 
//////////////////////////////////////////////////////////////////////////
// ����XML�Ľ���
// 1.��ǰ�಻֧��XSD�ȹ淶,��Ҫ�Ƕ�Ч�ʵĿ���
// 2.��ǰ�಻֧��ת��(_T("&lt;"),_T("&amp;"),_T("&gt;"),_T("&apos;"),_T("&quot;")),����ڶ�֮����֧��
// 3.����GB18030�Լ�BIG5�����뷶Χ�������Ƿ�Χ�����ص�,���Խ�����ʱ��ת��Ϊָ������ҳ��MBCS���д���
// 4.�ڴ�ʹ���Ͼ�����ʹ��ջ���ڴ���Խ�һ���������,��������ʵ�ʵĲ������Ӷ�,���ɱ������Ȼ�����в���
//   ֱ������Ĳ���

// XML������־
typedef enum enumXMLCREATEFLAG
{	XMLCREATE_NULL,					// �����д���
	XMLCREATE_FORCE=1,				// ǿ�ƴ���,����ֻ����־
	XMLCREATE_APPEND=2,				// ��β������(Ĭ��)
	XMLCREATE_INSERT=4,				// ��ͷ������
	XMLCREATE_CREATEALWAYS=8,		// �����Ƿ���ھ�����(���������ڵ�ļ��)
	XMLCREATE_RECREATE=16,			// ���½�����־(ɾ����Ӧ���µ�ȫ������)
} XMLCREATEFLAG;

// XML�ڵ��־(����)
typedef enum enumXMLNODEFLAG
{	XMLNODE_SYSKEY,					// ϵͳ�ڵ�,��?��ʼ�ͽ���,���ӽڵ�
	XMLNODE_ITEMKEY,				// �������ӽڵ�ļ�,��ʽΪ:<KEYNAME PAR='???'/>
	XMLNODE_KEYSET,					// �����ӽڵ�ļ�,��ʽΪ:<KEYNAME PAR='???'></KEYNAME>
	XMLNODE_VALUE,					// ��������һ��ֵ,�ܱ�������ָ����KEYSET��
	XMLNODE_UNKNOWN,				// δ֪����
	XMLNODE_COMMENT,				// ע������
} XMLNODEFLAG;

struct __HXMLNODE {};
typedef __HXMLNODE* HXMLNODE;		// XML�ڵ���
struct __HXMLATTRIB {};
typedef __HXMLATTRIB* HXMLATTRIB;	// XML���Ծ��

// XML������
class THeapList;
class LITEXML_IMP CXMLCore
{
public:
	CXMLCore(LPCTSTR pszRoot);
	virtual~CXMLCore();

	// �ڵ�ö��,�����Լ������޸�
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
	
	// ����ö��,�����Լ������޸�
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
	// XML�����ַ���
	typedef struct tagXMLSMALLSTR { BYTE m_szStr[16]; } XMLSMALLSTR;

	// XML�ַ���
	typedef struct tagXMLSTR
	{	char*		m_pStr;			// �ַ�������
		BOOL		m_bSmallStr;	// �Ƿ���С�ַ���(С�ַ���λ�ڿ��ÿռ����)
	} XMLSTR,*LPXMLSTR;

	// XML�ڵ�ṹ
	typedef struct tagXMLNODE
	{	HXMLNODE	m_hParent;		// ���ڵ���
		HXMLNODE	m_hNext;		// �ֵܽڵ���
		HXMLNODE	m_hChild;		// �ӽڵ���
		XMLSTR		m_Key;			// ��ֵ
		HXMLATTRIB	m_hAttrib;		// ����ָ��
		DWORD		m_dwFlag;		// �ڵ��ʶ
	} XMLNODE,*LPXMLNODE;

	// XML���Խṹ
	typedef struct tagXMLATTRIB
	{	HXMLATTRIB	m_hNext;		// ��һ������
		XMLSTR		m_Name;			// ��������
		XMLSTR		m_Value;		// ��������
	} XMLATTRIB,*LPXMLATTRIB;

private:
	// ���ÿռ��������ͷ�
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
	THeapList* m_pheapXmlNodes;		// XML�ڵ���ÿռ��
	THeapList* m_pheapXmlAttribs;	// XML���Կ��ÿռ��
	THeapList* m_pheapXmlSmallStrs;	// XMLС�ַ�����
	LPXMLNODE m_pNodeLinks;			// XML�ڵ�����
	TCHAR m_szRootDef[256];			// XML���ڵ�
};


// XML������
class LITEXML_IMP CXML : public CXMLCore
{
public:
	CXML(LPCTSTR pszRoot,UINT nLANGCodePage=CP_GB2312);
	virtual~CXML();

	// ��XML��������װ��
	// 1.XML�������������������ֽ���,���������Կ��ַ�����
	// 2.XML������֧��BOM���,��UTF8,UNICODE֧��
	// 3.XML����������Ҳ������������ַ��ĳ���
	BOOL LoadXmlFile(LPCTSTR lpszXmlFile,LPCSTR pszSecKey=NULL,UINT nFileLANGCodePage=CP_GB2312);
	BOOL LoadXmlMem(const unsigned char* lpXmlBuf,LONG nXmlLen,UINT nFileLANGCodePage=CP_GB2312);

	// ����XML�ı����ļ��򻺳���
	BOOL SaveXmlFile(LPCTSTR lpszXmlFile,LPCSTR pszSecKey=NULL,UINT nFileLANGCodePage=CP_GB2312,UINT nFileCONVCodePage=CP_UTF8);
	BOOL SaveXmlMem(unsigned char* lpXmlBuf,LONG nXmlBufLen,LONG* pnUsedOrNeeded,UINT nFileLANGCodePage=CP_GB2312,UINT nFileCONVCodePage=CP_UTF8);

	// �ͷ�XML�ļ�����
	VOID FreeXml();
	VOID FreeXmlButRoot();

	// �õ���ǰ����ҳ�Ͱ汾
	UINT GetLANGCodePage();
	UINT GetFileLANGCodePage();
	UINT GetFileCONVCodePage();
	FLOAT GetVersion();
	VOID SetLANGCodePage(UINT nLANGCodePage);
	VOID SetFileLANGCodePage(UINT nFileLANGCodePage);
	VOID SetFileCONVCodePage(UINT nFileCONVCodePage);

	// ��XML�ļ��л��߻�������װ��ָ���Ľڵ㵽ָ���ڵ���
	// �����·��ΪNULL,Ŀ��XML�ĸ��µ�ȫ���ڵ㽫������,����ָ��·���µĽڵ㽫������
	BOOL LoadFeatureFromXmlFile(HXMLNODE hNode,LPCTSTR lpszXmlFile,LPCSTR pszSecKey,UINT nFileLANGCodePage,LPCTSTR pszRoot,BOOL bCopyRoot=FALSE);
	BOOL LoadFeatureFromXmlMem(HXMLNODE hNode,const unsigned char* lpXmlBuf,LONG nXmlLen,UINT nFileLANGCodePage,LPCTSTR pszRoot,BOOL bCopyRoot=FALSE);
	BOOL LoadFeatureFromXml(HXMLNODE hNode,CXML* pXml,LPCTSTR pszRoot,BOOL bCopyRoot);

	// ��INI�ļ��л���װ�ؽڵ㵽ָ���Ľڵ���
	BOOL LoadFeatureFromIniFile(HXMLNODE hNode,LPCTSTR lpszIniFile,UINT nFileLANGCodePage);
	BOOL LoadFeatureFromIniMem(HXMLNODE hNode,LPCBYTE pszIniBuf,LONG nIniLen,UINT nFileLANGCodePage);

	// ��JSON�ļ������ڴ���װ�ؽڵ㵽ָ���Ľڵ���
	BOOL LoadFeatureFromJsonMem(HXMLNODE hNode,LPCBYTE pszJsonBuf,LONG nJsonLen);

	// ��ȡ���ڵ�
	HXMLNODE GetRoot();

	// ���ö�ȡ������д��(����)
	//		���÷���:	GetXmlProfileString("root/somevalue",...);
	//		XML����:	<root>
	//						<somevalue>VALUE</somevalue>
	//					</root>
	INT GetProfileInt(LPCSTR lpszKeyPath,INT nDefault);
	DWORD GetProfileString(LPCSTR lpszKeyPath,LPCSTR lpDefault,LPSTR lpReturnedString,DWORD nSize);
	LPCSTR GetProfileString(LPCSTR lpszKeyPath,LPCSTR lpDefault);
	time_t GetProfileDateTime(LPCSTR lpszKeyPath);
	BOOL SetProfileInt(LPCSTR lpszKeyPath,INT nValue);
	BOOL SetProfileString(LPCSTR lpszKeyPath,LPCSTR pszValue);
	BOOL SetProfileDateTime(LPCSTR lpszKeyPath,time_t tValue);

	// ���ö�ȡ������д��(��չ)
	//		���÷���:	GetXmlProfileString("root/somevalue","DATA",...);
	//		XML����:	<root>
	//						<somevalue DATA="VALUE"/>
	//					</root>
	INT GetProfileIntEx(LPCSTR lpszKeyPath,LPCSTR lpszAttrib,INT nDefault);
	DWORD GetProfileStringEx(LPCSTR lpszKeyPath,LPCSTR lpszAttrib,LPCSTR lpDefault,LPSTR lpReturnedString,DWORD nSize);
	LPCSTR GetProfileStringEx(LPCSTR lpszKeyPath,LPCSTR lpszAttrib,LPCSTR lpDefault);
	time_t GetProfileDateTimeEx(LPCSTR lpszKeyPath,LPCSTR lpszAttrib);
	BOOL SetProfileIntEx(LPCSTR lpszKeyPath,LPCSTR lpszAttrib,INT nValue);
	BOOL SetProfileStringEx(LPCSTR lpszKeyPath,LPCSTR lpszAttrib,LPCSTR pszValue);
	BOOL SetProfileDateTimeEx(LPCSTR lpszKeyPath,LPCSTR lpszAttrib,time_t tValue);

	// ·�����Һʹ���(֧����չ)
	HXMLNODE CreateXmlNodeEx(HXMLNODE hParentNode,LPCTSTR lpszXmlPath,DWORD dwFlag=XMLNODE_KEYSET,DWORD dwCreateFlag=XMLCREATE_APPEND);
	HXMLNODE FindXmlNodeEx(HXMLNODE hParentNode,LPCTSTR lpszXmlPath);

	// ·�����Һ�������ֵ��ȡ
	HXMLNODE FindXmlNodeWithAttrib(HXMLNODE hParentNode,LPCTSTR pszKey,LPCTSTR pszName,LPCTSTR pszValue);
	LPCTSTR GetXmlValueWithPath(LPCTSTR lpszXmlPath);
	LPCTSTR GetXmlAttribValueWithPath(LPCTSTR lpszXmlPath,LPCTSTR pszName);

	// ·����������ֵ����������
	BOOL SetXmlValueWithPath(LPCTSTR lpszXmlPath,LPCTSTR lpszValue);
	BOOL SetXmlAttribValueWithPath(LPCTSTR lpszXmlPath,LPCTSTR pszName,LPCTSTR lpszValue);

	// ���ýڵ������(ɾ��ȫ�����Ժ��ӽڵ�)
	BOOL ResetXmlNode(HXMLNODE hNode);
	// ɾ��ȫ���ڵ���ӽڵ�(���������ڵ�)
	BOOL DeleteAllChildXmlNode(HXMLNODE hParentNode);

	// ˮӡ����
	BOOL GenerateWaterMark(LPCTSTR pszRoot,char* pszWaterMark,LONG nWaterMarkLen,BOOL bWithAttrib=FALSE);

protected:
	// XML�ʷ�����
	UINT GetXmlInfo(char* lpszXml,FLOAT& fVersion);
	BOOL ParsingAndLoadXml(char* lpszXml,UINT nFileLANGCodePage,UINT nFileCONVCodePage,FLOAT fVersion);
	BOOL ParsingAndLoadJson(HXMLNODE hParentNode,LONG& nNodeLevel,char*& pszParsing);
	LPCTSTR FindXmlKeyOrAttribBegin(LPCTSTR lpszXml);
	LPCTSTR FindXmlKeyOrAttribEnd(LPCTSTR lpszXmlTokenBegin);
	LPCTSTR FindXmlAttribEqual(LPCTSTR lpszXml);
	LPCTSTR FindXmlAttribValueBegin(LPCTSTR lpszXml,BOOL& bSingleComma);
	LPCTSTR FindXmlAttribValueEnd(LPCTSTR lpszXmlAttribValue,BOOL bSingleComma);

	// ���ƽڵ���ӽڵ�
	VOID CopyXmlNodes(HXMLNODE hNodeTo,CXML* pFrom,HXMLNODE hXmlNodeFrom,BOOL bCopyChilds);

	// ��������
	VOID CatXmlLine(char* lpXml,LONG nXmlBufLen,LONG* pnUsed,LPCTSTR lpszAdd,LONG nAddLen);

	// ������ص�����(�ݹ麯��)
	LPCSTR XMLDecoding(LPSTR pszTemp,DWORD cbTemp,LPCSTR pszIn,DWORD cbIn);
	LPCSTR XMLEncoding(LPSTR pszTemp,DWORD cbTemp,LPCSTR pszIn);
	VOID SaveXmlNodeAndChilds(HXMLNODE hNode,char* lpXml,LONG nXmlBufLen,LONG* pnUsed,LONG nLevel,LPSTR pszEncodedKey,DWORD cbEncodedKey,LPSTR pszEncodedVal,DWORD cbEncodedVal);

	// ˮӡ�ռ��ص�����(�ݹ麯��)
	VOID WaterMarkXmlNodeAndChilds(HXMLNODE hNode,char** lppszBuffer,LONG* pnBufferSize,LONG* pnUsed,BOOL bWithAttrib);

	// ת������
	VOID XMLConvertCodePage(LPSTR pszBuf,LONG nMaxLen,UINT nExternCodePage,BOOL bLoad);
protected:
	UINT m_nLANGCodePage;			// MBCS����ʱ�Ĵ���ҳ
	UINT m_nFileLANGCodePage;		// �ļ�����ʱMBCS����Ĵ���ҳ
	UINT m_nFileCONVCodePage;		// ���װ��ʹ�õĴ���ҳ
	FLOAT m_fVersion;				// XML�ļ��汾
};



#endif
