//////////////////////////////////////////////////////////////////////////
// ��������:2013/03/19
// ����˵��:�����ֵ䴦����
// �����¼:  
// ���֪ʶ:
//		�� IXӳ��(IXMapper)ԭ��:
//			�ֶ�ӳ���Կɲ�η�ʽ����,���ڱ�׼�ֵ��Ͻ���ӳ��Ĺ�����ʽ,�ֶ�ӳ�䲻�����ֵ���޸�,ӳ����ֵ������������,ԭ�Ĳ��ֺ�ӳ�䲿��
//
//			1.�ֶα���
//			  �������¶����µ��ֶ�,���߶�ԭ���ֶν����ض���
//				���ֶ��ض���:
//					<Mapper ID="102" Hidden="0" Name="YYB(New!)"/>
//					��StructID��Χ��,���¶���ԭ���ֶ�(ID,�������)���ֶ�
//				���ֶ�����(���512��):
//					<Mapper ID="10108" Hidden="0" Name="NC(New!)" DeriveFromID="108"/>
//					<Mapper StructID="101" ID="10108" Hidden="0" Name="NC(New!!)" DeriveFromID="108"/>
//					��StructID��Χ��,ͨ��ԭ���ֶ�(DeriveFrom,�������)�ֶ��������µ��ֶ�(ID)
//
//			2.�ṹ�ض���
//			  ����Ϊ������������¶���
//					<Mapper ID="101" Seq="102,10108" HideOther="0"/>
//					��������ID��Ӧ��ӳ������,���Ե����ֶ�˳��,���������ֶ�,�ֶ�������������б������ֶ�
//					�ֶη��ʵ�����˳��Ϊ:
//						a.����ӳ���ӳ����е�˽���ֶ�
//						b.����ӳ���ӳ����еĹ����ֶ�
//						c.δ����ӳ����ֵ��е�˽���ֶ�
//						c.δ����ӳ����ֵ��еĹ����ֶ�
//
//		�� ���ּ��ݵ����
//			1.�Ͽͻ���---->�Ϸ�����(ʹ��2��Э����н���)
//			2.�Ͽͻ���---->�·�����(ʹ��2��Э����н���)
//			3.�¿ͻ���---->�Ϸ�����(ʹ��2��Э����н���)
//			4.�¿ͻ���---->�·�����(ʹ��3��Э����н���)
//		�� �ֵ�汾��ģ��汾�Ķ�Ӧ��ϵ
//			����					�ֵ�			�ͻ��˰汾	�������汾		�ͻ���ӳ��	������ӳ��
//			IXHostSide				�����ֵ�(3X)		3X			3X
//			IXNodeSide3X			�����ֵ�(3X)		3X			3X
//			IXNodeSideNoStub		NA					3X			3X
//			IXNodeSideCompatible	�ɰ��ֵ�(2X)		3X			3X
//			IXNodeSideDeprecation	�ɰ��ֵ�(2X)		2X			3X
//			IXNodeSideCompatible	�ɰ��ֵ�(2X)		3X			2X
//			IXNodeSideDeprecation	�ɰ��ֵ�(2X)		2X			2X
//		�� ӳ��֧��
//			����						ӳ��
//			CreateStructToNodeWrite		��֧��ӳ��(ԭ���ϲ�֧��,ӳ�䵼�������ֶο��ܲ�������ӳ��,����д��ȱ��)
//			CreateStructToHostWrite		��֧��ӳ��,����ʹ���ֵ�(ԭ���ϲ�֧��,ӳ�䵼�������ֶο��ܲ�������ӳ��,����д��ȱ��)
//			CreateStructToNodeRead		ȫģʽ֧��ӳ��,��չģʽ��֧���ֶ�����
//			CreateStructToHostRead		ȫģʽ֧��ӳ��,��չģʽ��֧���ֶ�����,ӳ����ʵ������
//			��ע: ����չģʽӳ��������ֵ����������,��Ϊӳ������ֶ���ź��ֵ���ء�
//		�� �����ֶ�
//			�����ֶ���ȡ�ͱ���
//				��Ӧ������ȡ���ݱ��������������,�������ڿͻ��˶�ȡӦ��
//				SaveCacheFields(�������������ص��ֶα�ʶCACHE��COOKIES�ֶ�)
//				SaveCookiesFields(���ж��ֶ��Ƿ�CACHE��COOKIES�ֶ�,ֻҪ���ؼ�����)
//			�����ֶ�����
//				SetCacheAndCookiesItems(����ģʽ�����ֵ��ʽ,3Xģʽ����ȫ���Ļ����ֶ�)
#if !defined(__ASE_LIB_IX_IMPL_V2__H__)&&!defined(ASE_NO_IX_V2)
#define __ASE_LIB_IX_IMPL_V2__H__
#pragma pack(1)
#ifndef ASELIB_API
	#error "ASELib.h" must be included.
#endif
#define ASELIBIMPL_DEFINED
#define ASELIBIMPLV2_DEFINED

// IX�ֵ��������
#define IXCOREVER_1				(0)			// IX�ں˰汾(��1���͵�2��)
#define IXCOREVER_3				(3)			// IX�ں˰汾(��3��)

#define DICTFORMAT_DICTVER		(0X000F)	// IX�ֵ��ʽ
#define IXDICTVER_COMPATIBLE	(0)			// ����İ汾(������һ���ֵ�͵ڶ����ֵ�(֧�ָ�������COOKIES))
#define IXDICTVER_3_00_L1		(3)			// �������ֵ�(����,֧�ָ������Ĵ�������)
#define IXDICTVER_3_00_L2		(4)			// �������ֵ�(���,֧�ָ������Ĵ�������)
#define IXDICTVER_LATEST		(4)			// ���°汾

#define IXFIELD_MAX				(128)		// ����ֶθ���(ÿ���ṹ)




// IX����
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
// �����ֵ���(IX�汾)
//////////////////////////////////////////////////////////////////////////
// 2.X�ض�λ��Ϣ
typedef struct tagIXSTRUCTRELOC
{	LPWORD	m_pFieldIdx;						// �ض�λ��������Ϣ(�ֵ�����)
} IXSTRUCTRELOC,*LPIXSTRUCTRELOC;

// 3.Xӳ��ṹ�б�
typedef struct tagIXREMAPSTRUCT
{	WORD	m_wStructID;						// �ṹ��
	DWORD	m_dwSeqOffset;						// ����ƫ��
	DWORD	m_dwSeqNum;							// ������
	DWORD	m_dwFieldOffset;					// �ֶ�ƫ��
	DWORD	m_dwFieldNum;						// �ֶ���
	BYTE	m_cHideOther;						// �Ƿ������������ֶ�
}IXREMAPSTRUCT,*LPIXREMAPSTRUCT;

// 3.Xӳ���ֶ��б�
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

	// ��ȡIX���İ汾��IX�ֵ��ʽ
	WORD GetIXCoreVer() { return m_wCoreVer; }
	VOID UpdateDictFormat(WORD wDictFormat) { m_wDictFormat=wDictFormat; }
	WORD GetDictFormat() { return m_wDictFormat; }
	WORD GetIXDictVer() { return (WORD)(m_wDictFormat&DICTFORMAT_DICTVER); }

	// ��ȡ�ֵ�汾�Լ������(�ֵ����ݰ汾���)
	WORD GetVersion() { return m_wVersion; }
	WORD GetBuildNo() { return m_wBuildNo; }

	// ��ȡ��������չ����
	DWORD GetExtendAttrib() { return m_dwAttrib; }
	DWORD ModifyExtendAttrib(DWORD dwRemove,DWORD dwAdd) { m_dwAttrib=(m_dwAttrib&~dwRemove)|dwAdd; return m_dwAttrib; }

	// ����ҳ�����ǩ������(��������)
	VOID SetCodePage(UINT nDataCodePage,UINT nUserCodePage) { m_nDataCP=nDataCodePage; m_nUserCP=nUserCodePage; }
	UINT GetDataCodePage() { return m_nDataCP; }
	UINT GetUserCodePage() { return m_nUserCP; }
	BOOL GetSignature(LPTSTR pszSignature,DWORD cbSignature);

	// ɾ��ȫ������
	VOID ResetDictContent(BOOL bResetMapper);

	// �Ǽ��ֶ�
	BOOL RegisterFieldInfos(CONST FIELDINFO pFieldInfos[],LONG nFieldNum,BOOL bOverride);

	// �Ǽǽṹ
	BOOL RegisterStructAndFields(WORD wStructID,FIELDREF* pFieldRefs,LONG nFieldNum,BOOL bOverride);

	// ���������ѹ�������ֵ�
	VOID Defragment();

	// �����ֵ���
	BOOL ExportToBuf(CONST LPVOID pBuff,DWORD dwSize,WORD wDictFormatAs,DWORD dwReserved,DWORD& dwUsed);

	// ���������ֵ�
	BOOL ImportFromBuf(CONST LPVOID pBuff,DWORD dwSize,BOOL bDeprecation,DWORD dwReserved,DWORD& dwUsed);
	BOOL ImportFromBuf(CONST LPVOID pBuff,DWORD dwSize,BOOL bDeprecation,DWORD dwReserved);

	// ��XML�����ֵ�
	BOOL ImportFromXML(LPCSTR pszXmlFile);

	// װ�غͲ���ӳ���
	BOOL LoadMapper(LPCSTR pszXmlFile,BOOL bMapperEnable);

	// �ڽ��ֵ����
	LONG GetBuildinStructNum() { return m_aStructInfos.GetCount(); }
	WORD GetBuildinStructID(LONG nIndex) { return (WORD)((nIndex<0||nIndex>=m_aStructInfos.GetCount())?0:m_aStructInfos[nIndex].m_wStructID); }
	LONG FindAnalogousBuildinFieldIndex(LPFIELDINFO pFieldInfo) CONST;
	LONG FindBuildinStructIndex(WORD wStructID) CONST;
	LONG FindBuildinFieldIndex(WORD wStructID,WORD wFieldID) CONST;
	CONST LPIXSTRUCTINFO FindBuildinStructInfo(WORD wStructID) CONST;
	CONST LPFIELDINFO FindBuildinFieldInfo(WORD wStructID,WORD wFieldID) CONST;
	CONST LPFIELDINFO FindBuildinFieldInfo(WORD wFieldID) CONST;
	CONST LPFIELDINFO FindBuildinFieldInfoByIndex(LONG nIndex) CONST { return m_aFieldInfos.GetData()+nIndex; }

	// ӳ���ֵ����
	LPFIELDINFO GetFieldInfoWithMap(WORD wStructID,WORD wFieldID,BOOL bUseMapper=TRUE);
	BOOL GetStructInfoWithMap(WORD wStructID,LONG nMaxCount,FIELDREF* pFieldRefs,WORD* pwFieldIdxs,WORD& wFieldNum,BOOL bUseMapper=TRUE);
	BOOL RemapStructInfo(WORD wStructID,LONG nMaxCount,FIELDREF* pFieldRefs,WORD* pwFieldIdxs,LPFIELDINFO pFieldInfos,WORD& wFieldNum);

protected:
	// ӳ���װ�غͱ���
	BOOL LoadMapperFromFile(LPCSTR pszXmlFile,BOOL bMapperEnable);
	// ӳ�����͵���
	BOOL ExportMapperAndGetUsed(LPVOID pBuff,DWORD dwSize,WORD wDictFormatAs,DWORD& dwUsed);
	BOOL ImportMapperAndGetUsed(CONST LPVOID pBuff,DWORD dwSize,WORD wDictFormat,DWORD& dwUsed);
	// �ֶ�ӳ�䴦��(����ӳ���Ľ����Ϣ�����ֶ���Ϣ,����NULL��ʶδӳ��)
	CONST LPFIELDINFO GetMappedFieldInfo(WORD wStructID,WORD wFieldID);
	CONST BOOL MapMappedStructInfo(WORD wStructID,LONG nMaxCount,FIELDREF* pFieldRefs,WORD* pwFieldIdxs,WORD& wFieldNum);
	CONST BOOL RemapMappedStructInfo(WORD wStructID,LONG nMaxCount,FIELDREF* pFieldRefs,WORD* pwFieldIdxs,LPFIELDINFO pFieldInfos,WORD& wFieldNum);
	// ������������
	VOID ResetMapperContent();
	VOID AppendMappedFieldInfo(LPFIELDINFO pFieldInfo);
	VOID AppendMappedStructInfo(WORD wStructID,LPWORD pFieldIDs,LPWORD pFieldIdxs,WORD wFieldNum);
private:
	// �ֵ䶨������
	CIXArray<FIELDINFO>		m_aFieldInfos;			// �ֶζ���
	CIXArray<IXSTRUCTINFO>	m_aStructInfos;			// �ṹ����
	WORD					m_wCoreVer;				// IX���İ汾
	WORD					m_wDictFormat;			// IX�ֵ��ʽ
	WORD					m_wVersion;				// �汾����(���汾)
	WORD					m_wBuildNo;				// �汾����(�����)
	DWORD					m_dwAttrib;				// ��������
	BYTE					m_acExtAttribs[32];		// ��������
	UINT					m_nDataCP;				// ���ݴ���ҳ
	UINT					m_nUserCP;				// �û�����ҳ
	// �ֶ�ӳ������
	BOOL					m_bMapperEnable;		// �Ƿ����ֶ�ӳ��
	CIXArray<FIELDINFO>		m_aMappedFieldInfos;	// ӳ�����ֶ���Ϣ(2X)
	CIXArray<IXSTRUCTINFO>	m_aMappedStructInfos;	// ӳ���Ľṹ��Ϣ(2X)
	CIXArray<IXSTRUCTRELOC>	m_aMappedStructRelocs;	// ӳ�����ض�λ��Ϣ(2X)
	CIXArray<IXREMAPSTRUCT>	m_aRemapStructs;		// ��ӳ��Ľṹ��Ϣ(3X)
	CIXArray<WORD>			m_aRemapSeqs;			// ��ӳ����ֶ�����(3X)
	CIXArray<IXREMAPFIELD>	m_aRemapFields;			// ��ӳ����ֶ���Ϣ(3X)
	BYTE					m_acReserved[64];		// ��������
};














//////////////////////////////////////////////////////////////////////////
// �ֵ������
#define IXTODO_MODE				0X0000000F				// ģʽ				
#define IXTODO_NAKEREAD			0X00000000				//		���ģʽ
#define IXTODO_READ				0X00000001				//		����ʶ				
#define IXTODO_WRITE			0X00000002				//		дģʽ
#define IXTODO_AUTOBUFFER		0X00000010				// �Զ�����������				

#define IXPKGFORMAT_PKGVER		0X0000000F				// ���ݰ��汾
#define IXPKGVER_2X				0X00000001				//		2X���ݰ�(��Ҫ�ֵ�)
#define IXPKGVER_3X				0X00000002				//		3X���ݰ�(����Ҫ�ֵ�,���͸��������ֵ�)
#define IXPKGFORMAT_PKGTYPE		0X000000F0				// ���ݰ�����
#define IXPKGTYPE_REQ			0X00000010				//		��������
#define IXPKGTYPE_ACK			0X00000020				//		Ӧ������
#define IXPKGTYPE_RS			0X00000030				//		���ݼ�
#define IXPKGFORMAT_PKGOPT		0X0000FF00				// ��ѡ��
#define IXPKGOPT_FIELDIDS		0X00000100				//		�����ֶ�ID��Ϣ
#define IXPKGOPT_FIELDKEYS		0X00000200				//		�����ֶ�����Ϣ
#define IXPKGOPT_FIELDINFOS		0X00000400				//		�����ֶ���ϸ��Ϣ
#define IXPKGOPT_NOFROMDICT		0X00000800				//		�����ֵ���д���


class ASELIB_API CIXCommon
{
public:
	CIXCommon(CIXDict* pDict=NULL,CIXCache* pCacheInst=NULL,BOOL bCaptureFatalError=FALSE);
	CIXCommon(CIXDict* pDict,LPBYTE pCacheBuf,DWORD cbCacheBuf,DWORD cbCacheUsed,BOOL bCaptureFatalError=FALSE);
	virtual ~CIXCommon();
public:
	// ���úͻ�ȡ�����ֵ�
	VOID		SetDict(CIXDict* pDict);		// ���������ֵ���ʵ��
	CIXDict*	GetDict();						// ��ȡ�����ֵ���ʵ��
	// �����ֶλ������ͻ�ȡ
	VOID		SetCache(CIXCache* pCacheInst);
	VOID		SetCache(LPBYTE pCacheBuf,DWORD cbCacheBuf,DWORD cbCacheUsed);
	CIXCache*	GetCacheInst() { return m_pCacheInst; }
	LPBYTE		GetCacheBuf() { return m_pCacheBuf; }
	DWORD		GetCacheBufMax() { return m_cbCacheBuf; }
	DWORD		GetCacheUsed() { return m_cbCacheUsed; }
	BOOL		HasCacheFeature() { return m_pCacheInst!=NULL||m_pCacheBuf!=NULL; }
	// �����ṹ,FALSE����ʧ��,TRUE���سɹ�
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


	// ��ȡ�����ֵ���ʵ��,�ṹID��ȡ/���Ȼ�ȡ(���������ַ�,�����ֵ��ȡ������)
	DWORD		GetToDoMode() { return (m_dwToDo&IXTODO_MODE); }					// ��ȡ��;
	DWORD		GetPkgFormat() { return m_dwPkgFormat; }							// ��ȡ����ʽ
	DWORD		GetPkgVer() { return m_dwPkgFormat&IXPKGFORMAT_PKGVER; }			// ��ȡ���汾
	DWORD		GetPkgType() { return m_dwPkgFormat&IXPKGFORMAT_PKGTYPE; }			// ��ȡ������
	DWORD		GetPkgOpt() { return m_dwPkgFormat&IXPKGFORMAT_PKGOPT; }			// ��ȡ��ѡ��
	WORD		GetStructID() { return (WORD)atol(m_szStructID); }					// ��ȡ��ǰ�ṹID
	LPCSTR		GetStructStrID() { return m_szStructID; }							// ��ȡ��ǰ�ṹID(�ַ���)
	LPBYTE		GetBuffer();														// �õ���������ַ
	DWORD		GetUsedBufferLen();													// �õ���ʹ�û���������(���������ַ�,��Ϊ��ȡ,��������Ч)
	DWORD		GetUsedBufferLenNoNil();											// �õ���ʹ�û���������(�����������ַ�,��Ϊ��ȡ,��������Ч)
	DWORD		GetMaxBufferLen();													// �õ�ȫ������������(���������ַ�)
	DWORD		GetFatalError();													// ��ȡ������������
	DWORD		GetCommonError();													// ��ȡ���ĳ������
	LONG		GetFieldNum();														// ���ص�ǰ�ֶθ���
	WORD		GetFieldIDAt(WORD wExtIndex);										// ��ȡ�ֶ�ID(ӳ���)
	LPCSTR		GetFieldKeyAt(WORD wExtIndex);										// ��ȡ�ֶ�KEY(ӳ���)
	BOOL		AddField(LPCSTR pszKey);											// �����ֶ�ID(ӳ���)
	BOOL		AddFieldAsKey(WORD wFieldID);										// ����ֶ�ID(ӳ���)
	BOOL		AddField(WORD wFieldID,LPCSTR pszKey=NULL,WORD wNickID=0);			// �����ֶ�ID(ӳ���)
	BOOL		AddField(FIELDINFO* pFieldInfo,LPCSTR pszKey=NULL,WORD wNickID=0);	// �����ֶ�ID(ӳ���)



	//////////////////////////////////////////////////////////////////////////
	// д�빫�ýӿ�
	BOOL		InitBuffer();																						// ��ʼ��д������
	BOOL		AddEOL();																							// ����н�����־
	BOOL		IXEncode(CONST LPBYTE pIn,WORD wInLen,BOOL bSecure,BOOL bBase64,BOOL bConvCP,LPSTR pszBuf,DWORD nMaxBufLen,DWORD& cbFinal);
	BOOL		IXTryEncode(CONST LPBYTE pIn,WORD wInLen,BOOL bSecure,BOOL bBase64,BOOL bConvCP,LPSTR pszBuf,DWORD nMaxBufLen,DWORD& cbFinal,DWORD& cbNeed,DWORD& dwError);
	BOOL		IXDecode(LPCSTR pszIn,DWORD cbIn,BOOL bSecure,BOOL bBase64,BOOL bConvCP,LPBYTE pValue,WORD wMaxSize,WORD& wFinal);


	//////////////////////////////////////////////////////////////////////////
	// ����д��ӿ�(IXPKGTYPE_REQ)

	// ֱ����д�ֶ�
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

	// �����COOKIES�ֶ��Զ����,��������޴���,��
	// 1.�ӻ���������ȡ�����ֶη��뵱ǰ������
	// 2.�ӻ���������ȡCOOKIES�ֶη��뵱ǰ������
	// (���ͻ�У��/���ɿͻ�У��/��ȡ������Ϣ��Ҫ����)
	BOOL		SetCacheAndCookiesItems();

	// �������������
	BOOL		SetEOR();
	BOOL		SetAttachAndEOR(const BYTE* pAttach,DWORD cbAttach);



	//////////////////////////////////////////////////////////////////////////
	// �����д��ӿ�(IXPKGTYPE_ACK,IXPKGTYPE_RS)

	// Ϊ��߷������˵�Ч��,��������밴˳�����
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

	// ����ʱ��������䷵��ֵ��ϢnRetcode=0Ϊ����ɹ�,����Ϊʧ��
	// ע:���������ȫ���ֶ���д�����(ֻ�ܵ���һ��)
	BOOL		SetReturn(LONG nRetCode,LPCSTR lpszMessage,LONG nRecordNum);
	BOOL		SetReturn2(LONG nRetCode,LPCSTR lpszMessage,LONG nRecordNum,CIXCookies* pCookies,LPCSTR lpszNextPageId);
	BOOL		SetReturn3(LONG nRetCode,LPCSTR lpszMessage,LONG nRecordNum,LPCSTR pszCookies,LONG nCookiesLen,LPCSTR lpszNextPageId);
	BOOL		SetAttachAndReturn(LONG nRetCode,LPCSTR lpszMessage,LONG nRecordNum,LPCSTR pszCookies,LONG nCookiesLen,LPCSTR lpszNextPageId,LPBYTE pAttach,WORD cbAttach);








	//////////////////////////////////////////////////////////////////////////
	// ��ȡ���ýӿ�

	// ��ȡ������ָ��,���Ⱥ�����
	LPBYTE		GetContentPtr();		// ��ȡ�����ֵ�ַ
	DWORD		GetContentLen();		// ��ȡ���ĳ���(���������ַ�)
	DWORD		GetContentLineNum();	// ��ȡ��������(�����²���,ע�⻺��)

	// ��ȡ����������
	LPBYTE		GetAttachPtr();			// ��ȡ����ָ��
	ATTACHSIZE	GetAttachLen();			// ��ȡ������С

	// �ж��Ƿ���ڸ��������
	// ����:	(BOOL)		�Ƿ������һ��
	BOOL		More();

	// �ƶ���ָ�뵽ָ����/����(�ͻ��˶�ȡ�ͷ�������ȡ)
	// ����:	dwLine		�к�,0��ʱ���ƶ���ͷ��(����״̬��Ϣ��)
	// ����:	(BOOL)		ָ�����Ƿ����
	BOOL		MoveToLine(DWORD dwLine);

	// �ƶ���ָ�뵽��һ��
	// ����:	(BOOL)		ָ�����Ƿ����
	BOOL		MoveNext();

	// ȡ��4.X���ݵ��ֶ�
	LPCSTR		GetItemValue4X(WORD wExtIndex,LPSTR lpszValue,WORD wSize,BOOL bSecure=FALSE);
	LPCSTR		GetItemValueFromID4X(WORD wFieldID,LPSTR lpszValue,WORD wSize,BOOL bSecure=FALSE);
	LPCSTR		GetItemValueFromKey4X(LPCSTR pszKey,LPSTR lpszValue,WORD wSize,BOOL bSecure=FALSE);

	// �����ֶ���Ż�ȡ�ֶ�����/�����ֶ�ID��ȡ�ֶ�����
	// ����0XFF������ȡʧ��
	BYTE		GetItemFlagValue(WORD wExtIndex,DWORD dwLineOffset=(DWORD)(-1));
	BYTE		GetItemFlagValueFromID(WORD wFieldID,DWORD dwLineOffset=(DWORD)(-1));
	BYTE		GetItemFlagValueFromKey(LPCSTR pszKey,DWORD dwLineOffset=(DWORD)(-1));

	// �����ֶ���Ż�ȡ�ֶ�����/�����ֶ�ID��ȡ�ֶ�����
	// ����0XFFFFFFFF������ȡʧ��
	LONG		GetItemLongValue(WORD wExtIndex,DWORD dwLineOffset=(DWORD)(-1));
	LONG		GetItemLongValueFromID(WORD wFieldID,DWORD dwLineOffset=(DWORD)(-1));
	LONG		GetItemLongValueFromKey(LPCSTR pszKey,DWORD dwLineOffset=(DWORD)(-1));

	// �����ֶ���Ż�ȡ�ֶ�����/�����ֶ�ID��ȡ�ֶ�����
	// ����NULL������ȡʧ��,������뻺������Ч,�������ڲ������
	LPCSTR		GetItemValue(WORD wExtIndex,LPSTR lpszValue,WORD wSize,BOOL bSecure=FALSE,DWORD dwLineOffset=(DWORD)(-1));
	LPCSTR		GetItemValueFromID(WORD wFieldID,LPSTR lpszValue,WORD wSize,BOOL bSecure=FALSE,DWORD dwLineOffset=(DWORD)(-1));
	LPCSTR		GetItemValueFromKey(LPCSTR pszKey,LPSTR lpszValue,WORD wSize,BOOL bSecure=FALSE,DWORD dwLineOffset=(DWORD)(-1));

	// �����ֶ���Ż�ȡ�ֶ�����/�����ֶ�ID��ȡ�ֶ�����
	// ����FALSE������ȡʧ��,������뻺������Ч,�������ڲ����ᱻ���
	BOOL		GetItemBinaryValue(WORD wExtIndex,WORD wMaxSize,LPBYTE lpValue,WORD* pwSize,BOOL bSecure=FALSE,BOOL bBase64=TRUE,DWORD dwLineOffset=(DWORD)(-1));
	BOOL		GetItemBinaryValueFromID(WORD wFieldID,WORD wMaxSize,LPBYTE lpValue,WORD* pwSize,BOOL bSecure=FALSE,BOOL bBase64=TRUE,DWORD dwLineOffset=(DWORD)(-1));
	BOOL		GetItemBinaryValueFromKey(LPCSTR pszKey,WORD wMaxSize,LPBYTE lpValue,WORD* pwSize,BOOL bSecure=FALSE,BOOL bBase64=TRUE,DWORD dwLineOffset=(DWORD)(-1));

	// �����ֶ�ID��ȡ�ֶ�����(�ֵ��ʽ)
	BOOL		GetItemIXCommonValue(WORD wExtIndex,WORD wAsStructID,BOOL bInherit,CIXCommon* pIXCommon);
	BOOL		GetItemIXCommonValueFromID(WORD wFieldID,WORD wAsStructID,BOOL bInherit,CIXCommon* pIXCommon);
	BOOL		GetItemIXCommonValueFromKey(LPCSTR pszKey,WORD wAsStructID,BOOL bInherit,CIXCommon* pIXCommon);
	VOID		FreeIXCommonValue(CIXCommon* pIXCommon);

	// ���󻯶�ȡ(���󻯺��ܰ���������ʽ��ȡ)
	BOOL		ConvertMatrix();
	DWORD		GetMatrixRowNum() { return m_dwMatrixRow; }
	DWORD		GetMatrixColNum() { return m_dwMatrixCol; }
	LPCSTR*		operator[](LONG nRow) { return &m_ppszMatrixs[nRow*m_dwMatrixCol]; }





	//////////////////////////////////////////////////////////////////////////
	// �ͻ��˶�ȡ�����ӿ�(IXPKGTYPE_ACK,IXPKGTYPE_RS)

	// ��ȡ�ֶ���Ϣ
	FIELDINFO*	GetFieldInfoAt(WORD wExtIndex);
	FIELDINFO*	GetFieldInfoByID(WORD wFieldID);

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
	
	// ��ȡ�����ֶε����滺����,��������޴���,��ӵ�ǰ���صĽ��������ȡ���Ա�ʶΪCACHE���ֶ�,���뻺��������
	BOOL		SaveCacheFields();

	// ��ȡCOOKIES�ֶε����滺����,��������޴���,��ӵ�ǰ���صĽ��������ȡ���Ա�ʶΪCACHE���ֶ�,���뻺��������
	BOOL		SaveCookiesFields();



	//////////////////////////////////////////////////////////////////////////
	// ���ݼ��ϲ�
	DWORD CalcLengthToMerge(DWORD dwOriginSize);
	BOOL MergeTo(LPBYTE pTarget,DWORD cbTargetMax,DWORD& cbUsed);

protected:
	// ȷ��������
	BOOL		EnsureBuffer(DWORD cbNeed);

	// ��ʼ������(�����������ֶ���Ϣ)
	BOOL		InitReverseIdxs();
	BOOL		InitFieldInfosFromDict();

	// ��־�ж�
	BOOL		IsDictFullySupport() { return m_pDict!=NULL&&(m_pDict->GetIXDictVer()>=IXDICTVER_3_00_L2||m_pDict->GetIXDictVer()<=IXDICTVER_COMPATIBLE); }
	BOOL		IsToRead() { return GetToDoMode()==IXTODO_NAKEREAD||GetToDoMode()==IXTODO_READ; }
	BOOL		IsToWrite() { return GetToDoMode()==IXTODO_WRITE; }
	BOOL		IsToWriteReq() { return IsToWrite()&&GetPkgType()==IXPKGTYPE_REQ; }
	BOOL		IsToReadAck() { return IsToRead()&&GetPkgType()==IXPKGTYPE_ACK; }
	BOOL		IsCanMapper() { return IsToRead(); } 

	// ����ֶ���Ϣ(д��)
	BOOL		AddFieldDynamic(WORD wFieldID,FIELDINFO* pFieldInfo,LPCSTR pszKey,WORD wNickID);
	// �����н�������־(д��)
	BOOL		AddEOLTag();
	// ��Ӱ汾��Ϣ(д��)
	BOOL		AddVerTag();
	// ����ֶ�������(д��)
	BOOL		AddFieldTag(DWORD dwOffset);
	// ��Ӹ����ֶ�(д��)
	BOOL		AddAttach(const BYTE* pAttach,DWORD cbAttach);

	// ����ժҪ/�ֶζ���/���������,������β��ƫ��,����������,�������ݳ���(��ȡ��д��)
	DWORD		HardLineNoOfSummary();
	DWORD		HardLineNoOfFieldTag();
	DWORD		HardLineNoOfContent();
	DWORD		OffsetOfEndOfContent();
	DWORD		AttachAreaLen();
	DWORD		AttachDataLen();

	// �ƶ���ָ���к��ƶ�����һ��(��ȡ��д��)
	BOOL		HardSeekTo(DWORD dwLine);
	BOOL		HardSeekToNext();

	// �õ���N�е�ƫ��
	// ����:	dwLine		�к�
	// ����:	(DWORD)		λ��ƫ��,ULONG_MAX�����в�����
	DWORD		HardLineOffset(DWORD dwLine);

	// �õ���N�еĿ��
	// ����:	dwLine		�к�
	// ����:	(DWORD)		λ�ÿ��,ULONG_MAX�����в�����
	DWORD		HardLineLength(DWORD dwLine);

	// �õ���N�еĻ�����
	// ����:	dwLine		�к�
	// ����:	(LPCSTR)	��������ʼλ��
	LPCSTR		HardLineAddress(DWORD dwLine);

	// �õ���������
	// ����:	(WORD)		����
	DWORD		HardCalcLineCount();

	// �ⲿ��ת��Ϊ������
	BOOL		ExtIndex2PhyIndex(WORD wExtIndex,WORD& wPhyIndex);

	// ���ҵ�ǰ�����ֶε���ֹλ��(��ֹ�ַ�Ϊ��һ���ֶεĿ�ʼ�ַ�)
	BOOL		FindFieldByPhyIndex(WORD wExtIndex,LPDWORD lpdwFieldBegin,LPDWORD lpdwFieldEnd,DWORD dwLineOffset);
	WORD		FindExtIndexByID(WORD wFieldID);
	WORD		FindExtIndexByKey(LPCSTR pszKey);

	// ��Ӻͻ�ȡ���ڲ�������
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

	// ���뻺����(д�����)
	BOOL		InitLineStruct();
	BOOL		ReplaceToBuffer(DWORD dwFieldBegin,DWORD dwFieldEnd,LPBYTE pszField,DWORD cbField);
	BOOL		InsertToBuffer(DWORD dwOffset,LPBYTE pszField,DWORD cbField);
	VOID		TruncateOnError();

	// ����ҳת��
	LONG		ConvertIXCommonCodePage(LPSTR pszBuf,LONG nLen,LONG nMaxSize,BOOL bToUser);
private:
	CIXDict*			m_pDict;						// �����ֵ���ָ��
	CIXCache*			m_pCacheInst;					// ���ݻ�����ָ��
	LPBYTE				m_pCacheBuf;					// ������ָ��
	DWORD				m_cbCacheBuf;					// ��������С
	DWORD				m_cbCacheUsed;					// �������ݴ�С
	BOOL				m_bCaptureFatalError;			// �Ƿ񲶻���������
	DWORD				m_dwToDo;						// ����
	DWORD				m_dwPkgFormat;					// ����ʽ
	CHAR				m_szStructID[32];				// ����ID
	LPBYTE				m_pBuffer;						// ��������Ϣ
	DWORD				m_cbUsedLen;					// ��ǰ�������Ѿ�ʹ�õ�
	DWORD				m_cbMaxBufLen;					// ����������

	BOOL				m_bEOIX;						// ������־
	BOOL				m_bStructCreated;				// �ṹ�Ƿ񴴽�
	BOOL				m_bLineStructInit;				// (д��)��ǰ�нṹ�Ƿ��Ѿ���ʼ��(���ֶ����ʱ����ӵ�һ���ֶε�ʱ�����ȫ���ļ�¼�ָ���)
	WORD				m_wFieldNum;					// �ֶ���
	FIELDREF			m_aFieldRefs[IXFIELD_MAX];		// �ֶ�����
	LPCSTR				m_apszFieldKeys[IXFIELD_MAX];	// �ֶ�KEYֵ
	TCHAR				m_szFieldKeys[256];				// KEYֵ������
	DWORD				m_cbFieldKeys;					// KEYֵ������ʹ�ó���
	WORD				m_awFieldPhyIdxs[IXFIELD_MAX];	// �ֶ�����(�±����߼���,��ֵָ��������)
	WORD				m_awFieldExtIdxs[IXFIELD_MAX];	// �ֶ�����(�±���������,��ֵָ���߼���)
	CIXArray<FIELDINFO>	m_aFieldInfos;					// �ֶ���Ϣ

	DWORD				m_dwLineOffset;					// ��ǰ��ƫ��(��ȡ��ʽ����Ч)
	LPCSTR*				m_ppszMatrixs;					// ���ݾ���(����ģʽ��Ч)
	DWORD				m_dwMatrixRow;					// ��������
	DWORD				m_dwMatrixCol;					// ��������
	DWORD				m_dwIXFatalError;				// �����������
	DWORD				m_dwIXCommonError;				// ������������
	BOOL				m_bRealloced;					// �ڴ��Ƿ񾭹����·���
	BYTE				m_aReserved[60];				// �����ֽ�
};

#pragma pack()
#endif
