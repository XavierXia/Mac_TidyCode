//////////////////////////////////////////////////////////////////////////
// ��������:2006/07/20
// ����˵��:�����ֵ䴦����
// �����¼:  
//            2006/07/23 ����ת���ִ���,��ԭ�нṹ��,���ֶ�ʹ��|�ַ����зָ�,����ĳЩ����·��������л����|�ַ�
//                       ��˻�Ӱ�������ȫ������,Ҳ���ϵͳ���ȶ�.��������ת���ֶ���
//                             \\    �ַ�\     |
//                             \0    �ַ�0     |
//                             \s    �ַ�|     |
//                             \r    �ַ�\r    |
//                             \n    �ַ�\n    |
//                             \t    �ַ�\t    |
//            2006/07/23 ֧�ֶ�������(�����������ʽ��ѯ�ȶ��в�ѯ���)
//            2007/04/20 ֧��COOKIES�Խ����̬������ɵ�����
//            2007/07/13 ֧�����䷭ҳ(��λ����ʽ)֧��
//                       ����󷵻ؽṹΪ: �����|������Ϣ|������|COOKIES|��ҳ��λ��|
//            2008/03/05 ֧���ֶ�ӳ��
//            2008/03/11 ��ֲ��linux
//            2010/03/16 ��ԭWTCOMMLIB������ΪASE��,֧�ָ��㷺������
#if !defined(__ASE_LIB_IX_IMPL_V1__H__)&&!defined(ASE_NO_IX_V1)
#define __ASE_LIB_IX_IMPL_V1__H__
#pragma pack(1)
#ifndef ASELIB_API
	#error "ASELib.h" must be included.
#endif
#define ASELIBIMPL_DEFINED
#define ASELIBIMPLV1_DEFINED



// ��ģ�鵼����
class CWtDict;		// �����ֵ�
class CWtDict2;		// ��չ�ֵ�(֧��XML,֧���ֵ�汾��,֧����������)
class CWtCommon;	// �����ֵ䴦����

//////////////////////////////////////////////////////////////////////////
//	���������ֵ����,�ֵ�Ĺ���,����͵���.�ֵ����ز���
//////////////////////////////////////////////////////////////////////////
// �ӵ�ǰ�汾��ʼ,CWtDict.V1���׷��
class ASELIB_API CWtDict
{
protected:
	CWtDict(DWORD dwReserved);
	virtual ~CWtDict();
public:

	// �ǼǱ�׼�ֶ�(ע��,����������,��ɾ���Ѿ����ڵ�����)
	BOOL RegisterFieldInfo(CONST FIELDINFO pFieldInfo[],WORD wFieldNum);
	// �ǼǱ�׼����ID�б�(ע��,����������,��ɾ���Ѿ����ڵ�����)
	BOOL RegisterStruct(CONST WORD pStructID[],WORD wStructNum);
	// �ǼǱ�׼�����ֶ�(ע��,����������,��ɾ���Ѿ����ڵ�����)
	BOOL RegisterStructField(WORD wStructID,CONST WORD pFieldID[],WORD wFieldNum);
	// ����CACHE�ֶ�
	BOOL RegisterCacheFields(CONST FIELDINFO pFieldInfo[],WORD wFieldNum);


	// ���ر�׼�ֶ�(��Ӧ��,�ϸ��ֹ���������ֶ�)
	BOOL OverrideFieldInfo(CONST FIELDINFO pFieldInfo[],WORD wFieldNum);
	// ��������ṹ�еĻ����ֶ�
	BOOL OverrideRequestStructField(WORD wStructID,CONST WORD pCacheFieldID[],WORD wCacheFieldNum,BOOL bAppend);
	// ����Ӧ��ṹ�е��ֶ�
	BOOL OverrideAnswerStructField(WORD wStructID,CONST WORD pFieldID[],WORD wFieldNum);


	// �ǼǷǱ�׼�ֶ�
	// ע���û��Զ�����ֶ���Ϣ
	BOOL RegisterFieldInfoNonStd(CONST FIELDINFO pFieldInfo[],WORD wFieldNum);
	// �ǼǷǱ�׼����ID�б�
	// ע���û��Զ���Ľṹ����
	BOOL RegisterStructNonStd(CONST WORD pStructID[],WORD wStructNum);
	// �ǼǷǱ�׼����ID��Ӧ���ֶ�����(���Ժ�������汾�н�ȡ����׼����)
	BOOL RegisterStructFieldNonStd(WORD wStructID,CONST WORD pFieldID[],WORD wFieldNum);


	// ���������ֵ�
	// ���:
	//		pBuff	�����������ַ
	//		dwSize	��󻺳�����С
	// ����:
	//		pBuff	�ֵ�����
	//		dwSize	��ǰ�ֵ��С
	// ����:
	//		TRUE	ȡ���ֵ�ɹ�
	//		FALSE	ȡ���ֵ�ʧ��
	BOOL ExportCommonSafe(LPVOID pBuff,DWORD dwSize,DWORD& dwUsed);
	// ���������ֵ�
	BOOL ImportCommonSafe(CONST LPVOID pBuff,DWORD dwSize,DWORD& dwUsed);

	// ѹ�������ֵ�
	// ���:
	//		(��)
	// ����:
	//		(��)
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
// �����ֵ���չ��(֧�ֱ���ź���������)
//////////////////////////////////////////////////////////////////////////
// �����ֶ�[0]: �ֶ�ӳ���ָ��
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
	// ��ȡ�ֵ�汾�Լ������(�汾���)
	WORD GetVersion();
	WORD GetBuildNo();
	// �����ֵ���
	BOOL ExportCommonAndGetUsed(CONST LPVOID pBuff,DWORD dwSize,DWORD& dwUsed);
	virtual BOOL ExportCommon(LPVOID pBuff,DWORD& dwSize);
	// ���������ֵ�
	virtual BOOL ImportCommonAndGetUsed(CONST LPVOID pBuff,DWORD dwSize,DWORD& dwUsed);
	virtual BOOL ImportCommon(CONST LPVOID pBuff,DWORD dwSize);
	// ��XML�����ֵ�
	virtual BOOL ImportFromXML(LPCSTR pszXmlFile);
	// ��ȡ��չ����
	virtual LPCSTR GetExtendAttrib(LPCSTR pszName);
	// �ֶ���Ϣö��
	WORD GetFieldNumNoMapping(WORD wStructID);
	WORD GetFieldIDNoMapping(WORD wStructID,WORD wIndex);
	CONST LPFIELDINFO GetFieldInfoNoMapping(WORD wFieldID);
	CONST LPWTSTRUCT_INFO GetStructInfoNoMapping(WORD wStructID);
	// ӳ���ֶε�ö��
	WORD GetMappedFieldNum(WORD wStructID);
	WORD GetMappedFieldID(WORD wStructID,WORD wIndex);
	CONST LPFIELDINFO GetMappedFieldInfo(WORD wFieldID);
	CONST LPWTSTRUCT_INFO GetMappedStructInfo(WORD wStructID);
	BOOL MappingFieldIndex(WORD wStructID,WORD& wFieldIndex);
	// װ�غͲ���ӳ���
	BOOL LoadFieldsMapper(LPCSTR pszXmlFile,BOOL bMapperEnable);
	// ���������ֵ�Ĺ���
	VOID ResetContent();
protected:
	enum enumREVDNO
	{	REV_FIELDSMAPPER,	// ϵͳ�ֶ�ӳ��
		REV_DATA_CODEPAGE,	// ���ݴ���ҳ
		REV_USER_CODEPAGE,	// �û�����ҳ
	};
protected:
	WORD		m_wVersion;
	WORD		m_wBuildNo;
	DWORD		m_dwAttrib;
	DWORD_PTR	m_adwReserved[10];
};











//////////////////////////////////////////////////////////////////////////
//	ʹ�������ֵ������ҵ�������
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// �ֵ������
class ASELIB_API CWtCommon
{
public:
	CWtCommon(CWtDict* pDict=NULL,CWtCache* pCache=NULL,BOOL bCaptureFatalError=FALSE);
	virtual ~CWtCommon();
public:
	// ���������ֵ�
	VOID		SetDict(CWtDict* pDict);
	// �����ֶλ���
	VOID		SetCache(CWtCache* pCache);
	// ��������,-1����ʧ��,0���سɹ�
	LONG		CreateStruct(WORD wStructID,LPVOID pBuffer,DWORD dwBuffLen);
	LONG		CreateStructToRead(WORD wStructID,LPVOID pBuffer,DWORD dwBuffLen);
	LONG		CreateNoDict(LPVOID pBuffer,DWORD dwBuffLen);
	// �������ÿ�/�ṹID��ȡ/���Ȼ�ȡ(���������ַ�,�����ֵ��ȡ������)
	VOID		InitBuffer();			// ��ʼ��������
	WORD		GetStructID();			// ��ȡ��ǰ�ṹID
	LPBYTE		GetBufferAddress();		// �õ���������ַ
	DWORD		GetUsedBufferLen();		// �õ���ʹ�û���������(���������ַ�,��Ϊ��ȡ,��������Ч)
	DWORD		GetMaxBufferLen();		// �õ�ȫ������������(���������ַ�)
	LPBYTE		GetContentAddress();	// ��ȡ�����ֵ�ַ
	DWORD		GetContentLen();		// ��ȡ���ĳ���(���������ַ�)
	// Ϊ��߷������˵�Ч��,��������밴˳�����,�ͻ��˽�ֹʹ��
	BOOL		AddItemValue4X(LPCSTR lpszValue,BOOL bEncrypt=FALSE);
	BOOL		AddItemFlagValue(BYTE cFlag);
	BOOL		AddItemLongValue(LONG nValue);
	BOOL		AddItemValue(LPCSTR lpszValue,BOOL bEncrypt=FALSE);
	BOOL		AddItemBinaryValue(CONST LPBYTE lpValue,WORD wSize,BOOL bEncrypt=FALSE,BOOL bEncode=TRUE);
	BOOL		AddItemWtCommonValue(CWtCommon* pWtCommon);
	// ���ڿͻ�����д����ʱ����,��������ֹ����,�������ڵ������
	BOOL		SetItemValue4X(WORD wFieldID,LPCSTR lpszValue,BOOL bEncrypt=FALSE);
	BOOL		SetItemFlagValue(WORD wFieldID,BYTE cFlag);
	BOOL		SetItemLongValue(WORD wFieldID,LONG nValue);
	BOOL		SetItemValue(WORD wFieldID,LPCSTR lpszValue,BOOL bEncrypt=FALSE);
	BOOL		SetItemBinaryValue(WORD wFieldID,CONST LPBYTE lpValue,WORD wSize,BOOL bEncrypt=FALSE,BOOL bEncode=TRUE);
	// �����н�����(��������)
	BOOL		AddLine();
	// �������������(�ͻ��˰�)
	BOOL		AddAttachAndEOR(const BYTE* pAttach,DWORD cbAttach);
	// ���ӻ����ֶβ�����н����ַ�(�ͻ��˵���,�ѷ���,�ͻ��˻���ݹ��ܺ��ж�)
	BOOL		FillCacheAndAddLine();
	BOOL		FillCacheAndAddLineEx(LPBYTE pszCacheBuf,DWORD cbCacheUsed);
	// ����ʱ��������䷵��ֵ��ϢnRetcode=0Ϊ����ɹ�,����Ϊʧ��
	// ע:���������ȫ���ֶ���д�����(ֻ�ܵ���һ��)
	BOOL		SetReturn(LONG nRetCode,LPCSTR lpszMessage,LONG nRecordNum);
	BOOL		SetReturn2(LONG nRetCode,LPCSTR lpszMessage,LONG nRecordNum,CWtCookies* pCookies,LPCSTR lpszNextPageId);
	BOOL		SetReturn3(LONG nRetCode,LPCSTR lpszMessage,LONG nRecordNum,LPCSTR pszCookies,LONG nCookiesLen,LPCSTR lpszNextPageId);
	BOOL		SetReturn4(LONG nRetCode,LPCSTR lpszMessage,LONG nRecordNum,LPCSTR pszCookies,LONG nCookiesLen,LPCSTR lpszNextPageId,LPBYTE pAttach,WORD cbAttach);
	// �õ����ش����(�ͻ��˱����жϷ��ش����)
	LONG		GetReturnNo();
	// �õ����ش�����Ϣ(�ͻ����ڴ��ڴ��������½�����ʾ������Ϣ)
	LPCSTR		GetErrmsg(LPSTR lpszErrMsg,WORD wMaxSize);
	// ��̨ʵ�ʷ��صĲ�ѯ��,�ڶ������õ�,�ͻ��˱����жϽ������ֵ
	LONG		GetTotalReturn();
	// �õ�COOKIES��Ϣ
	LPCSTR		GetCookies(LPSTR lpszCookies,WORD wMaxSize);
	// ��ȡ��λ����Ϣ
	LPCSTR		GetNextPageId(LPSTR lpszNextPageId,WORD wMaxSize);
	// ��ȡ����������
	LPBYTE		GetAttachPtr();
	ATTACHSIZE	GetAttachSize();
	// ���ص�ǰ�ֶθ���
	LONG		GetFieldNum();
	WORD		GetFieldIDAt(WORD wIndex);
	CONST LPFIELDINFO GetFieldInfoAt(WORD wIndex);
	// ��ȡ�ֶ���Ϣ
	CONST LPFIELDINFO GetFieldInfoByID(WORD wFieldID);
	// ��ȡ��������(���������ܷ���,���������������Ϊ0)
	WORD		GetLineCount();
	// �õ���N�е�ƫ��
	// ����:	wLine		�к�,<=0��ʱ���ƶ���ͷ��(����״̬��Ϣ��)
	// ����:	(DWORD)		λ��ƫ��,(DWORD)(-1)�����в�����
	DWORD		GetLineOffset(WORD wLine);
	// �õ���N�еĻ�����
	// ����:	wLine		�к�,<=0��ʱ���ƶ���ͷ��(����״̬��Ϣ��)
	// ����:	(LPCSTR)	��������ʼλ��
	LPCSTR		GetLineAddress(WORD wLine);
	// �ƶ���ָ�뵽ָ����/����
	// ����:	wLine		�к�,<=0��ʱ���ƶ���ͷ��(����״̬��Ϣ��)
	// ����:	(BOOL)		ָ�����Ƿ����
	BOOL		MoveToLine(WORD wLine);
	// �ƶ���ָ�뵽��һ��
	// ����:	(BOOL)		ָ�����Ƿ����
	BOOL		MoveNext();
	// ȡ��4.X���ݵ��ֶ�
	LPCSTR		GetItemValue4X(WORD wIndex,LPSTR lpszValue,WORD wSize,BOOL bDecrypt=FALSE);
	LPCSTR		GetItemValueFromID4X(WORD wFieldID,LPSTR lpszValue,WORD wSize,BOOL bDecrypt=FALSE);
	// �����ֶ���Ż�ȡ�ֶ�����/�����ֶ�ID��ȡ�ֶ�����
	// ����0XFF������ȡʧ��
	BYTE		GetItemFlagValue(WORD wIndex,DWORD dwLineOffset=(DWORD)(-1));
	BYTE		GetItemFlagValueFromID(WORD wFieldID,DWORD dwLineOffset=(DWORD)(-1));
	// �����ֶ���Ż�ȡ�ֶ�����/�����ֶ�ID��ȡ�ֶ�����
	// ����0XFFFFFFFF������ȡʧ��
	LONG		GetItemLongValue(WORD wIndex,DWORD dwLineOffset=(DWORD)(-1));
	LONG		GetItemLongValueFromID(WORD wFieldID,DWORD dwLineOffset=(DWORD)(-1));
	// �����ֶ���Ż�ȡ�ֶ�����/�����ֶ�ID��ȡ�ֶ�����
	// ����NULL������ȡʧ��,������뻺������Ч,�������ڲ������
	LPCSTR		GetItemValue(WORD wIndex,LPSTR lpszValue,WORD wSize,BOOL bDecrypt=FALSE,DWORD dwLineOffset=(DWORD)(-1));
	LPCSTR		GetItemValueFromID(WORD wFieldID,LPSTR lpszValue,WORD wSize,BOOL bDecrypt=FALSE,DWORD dwLineOffset=(DWORD)(-1));
	// �����ֶ���Ż�ȡ�ֶ�����/�����ֶ�ID��ȡ�ֶ�����
	// ����NULL������ȡʧ��,������뻺������Ч,�������ڲ�����[!!!]�����
	BOOL		GetItemBinaryValue(WORD wIndex,WORD wMaxSize,LPBYTE lpValue,WORD* pwSize,BOOL bDecrypt=FALSE,BOOL bDecode=TRUE,DWORD dwLineOffset=(DWORD)(-1));
	BOOL		GetItemBinaryValueFromID(WORD wFieldID,WORD wMaxSize,LPBYTE lpValue,WORD* pwSize,BOOL bDecrypt=FALSE,BOOL bDecode=TRUE,DWORD dwLineOffset=(DWORD)(-1));
	// �����ֶ�ID��ȡ�ֶ�����(�ֵ��ʽ)
	BOOL		GetItemWtCommonValue(CWtCommon* pWtCommon);
	VOID		FreeWtCommonValue(CWtCommon* pWtCommon);
	// ��ȡ�����ֶε����滺����,��������޴���,��ӵ�ǰ���صĽ��������ȡ���Ա�ʶΪCACHE���ֶ�,����CWtCache��
	BOOL		ExtractCacheField();
	// ��ȡCOOKIES�ֶε����滺����,��������޴���,��ӵ�ǰ���صĽ��������ȡ���Ա�ʶΪCACHE���ֶ�,����CWtCache��
	BOOL		ExtractCookiesField();
	// ��ȡ�����ֶε����滺����,��������޴���,��ӵ�ǰ���صĽ��������ȡ���Ա�ʶΪCACHE���ֶ�,����CWtCache��
	BOOL		ExtractCacheFieldEx(LPBYTE pCacheBuf,DWORD cbCacheBuf,DWORD& cbCacheUsed);
	// ��ȡCOOKIES�ֶε����滺����,��������޴���,��ӵ�ǰ���صĽ��������ȡ���Ա�ʶΪCACHE���ֶ�,����CWtCache��
	BOOL		ExtractCookiesFieldEx(LPBYTE pCacheBuf,DWORD cbCacheBuf,DWORD& cbCacheUsed);
	// �����COOKIES�ֶ��Զ����,��������޴���,��
	// 1.�ӻ���������ȡ�����ֶη��뵱ǰ������
	// 2.�ӻ���������ȡCOOKIES�ֶη��뵱ǰ������
	// (���ͻ�У��/���ɿͻ�У��/��ȡ������Ϣ��Ҫ����)
	BOOL		AutoFillCacheAndCookiesToReq();
	BOOL		AutoFillCacheAndCookiesToReqEx(LPBYTE pCacheBuf,DWORD cbCacheUsed);
	// ȡ��������������ͷ������������
	DWORD		GetLastFatalError();
	DWORD		GetLastCommonError();
	// ��ȡ�����ֵ���ʵ��
	CWtDict*	GetDict();
	// ��ȡ��ǰ�ֵ�ṹ
	LPWTSTRUCT_INFO GetStructInfo() { return m_StrcBuf.m_pStructInfo; }
	// ���ݼ��ϲ�
	DWORD CalcLengthToMerge(DWORD dwOriginSize);
	BOOL MergeTo(LPBYTE pTarget,DWORD cbTargetMax,DWORD& cbUsed);
protected:
	// ���ҵ�ǰ�����ֶε���ֹλ��(��ֹ�ַ�Ϊ��һ���ֶεĿ�ʼ�ַ�)
	BOOL		FindFieldByIndex(WORD wFieldIndex,LPDWORD lpdwFieldBegin,LPDWORD lpdwFieldEnd,DWORD dwLineOffset,BOOL bMapper);
	// ����ҳת��
	LONG		ConvertWtCommonCodePage(LPSTR pszBuf,LONG nLen,LONG nMaxSize,BOOL bToUser);
	// �ڲ�����
	BOOL		AddItemRawBinaryValue(CONST LPBYTE lpValue,WORD wSize,BOOL bEncrypt,BOOL bEncode,BOOL bConvertCodePage);
	BOOL		SetItemRawBinaryValue(WORD wFieldID,CONST LPBYTE lpValue,WORD wSize,BOOL bEncrypt,BOOL bEncode,BOOL bMapper,BOOL bConvertCodePage);
	BOOL		GetItemRawBinaryValue(WORD wIndex,WORD wMaxSize,LPBYTE lpValue,WORD* pwSize,BOOL bDecrypt,BOOL bDecode,DWORD dwLineOffset,BOOL bMapper,BOOL bConvertCodePage);
	LPCSTR		GetItemRawTextValue(WORD wIndex,LPSTR lpszValue,WORD wSize,BOOL bDecrypt,DWORD dwLineOffset,BOOL bMapper,BOOL bConvertCodePage);
	BOOL		GetItemRawBinaryValueFromID(WORD wFieldID,WORD wMaxSize,LPBYTE lpValue,WORD* pwSize,BOOL bDecrypt,BOOL bDecode,DWORD dwLineOffset,BOOL bMapper,BOOL bConvertCodePage);
	LPCSTR		GetItemRawTextValueFromID(WORD wFieldID,LPSTR lpszValue,WORD wSize,BOOL bDecrypt,DWORD dwLineOffset,BOOL bMapper,BOOL bConvertCodePage);
protected:
	friend class CWtCache;
private:
	CWtDict*		m_pDict;				// �����ֵ���ָ��
	CWtCache*		m_pCache;				// ���ݻ�����ָ��
	BOOL			m_bCaptureFatalError;	// �Ƿ񲶻���������
	WTCOMMON_STRC	m_StrcBuf;				// ��ǰ�ṹ����������
	DWORD			m_dwLineOffset;			// ��ǰ��ƫ��
	DWORD			m_dwMaxBufLen;			// ����������
	DWORD			m_dwUsedLen;			// ��ǰ�������Ѿ�ʹ�õ�
	BOOL			m_bLineStruInit;		// ��ǰ�нṹ�Ƿ��Ѿ���ʼ��(���ֶ����ʱ����ӵ�һ���ֶε�ʱ�����ȫ���ļ�¼�ָ���)
	DWORD			m_dwLastFatalError;		// �����������
	DWORD			m_dwLastCommonError;	// ������������
};

#pragma pack()
#endif
