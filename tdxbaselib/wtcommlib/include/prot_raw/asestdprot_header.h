//////////////////////////////////////////////////////////////////////////
// ��׼Э��淶�����ļ�
// ���ļ�����:
//		1.Э������Ҫ��־(����ѹ��)
//		2.��׼Э��ͷ(��ѡ,ʹ��EXCLUDE_STD_PACKET_HEADER������)
//			a.4.XЭ��ͷ����(������վ,��Ѷ��վ,ί���м̺�����)
//			b.CW.Э��ͷ����(������վ)
//			c.5.XЭ��ͷ����(��������,IMServer��)
//			d.7.XЭ��ͷ����
#ifndef __ASE_STDPROT_HEADER__H__
#define __ASE_STDPROT_HEADER__H__
// Э�鲿��,ʹ��1�ֽڶ���
#pragma pack(1)



// ���ܼ���(����: SafeVCRT_Types.h)
#ifndef ENCRYPTLV_DEFINED
	#define ENCRYPTLV_DEFINED
	typedef enum enumENCRYPTLV
	{	ENCRYPTLV_NONE,								// ���ܼ���: ������
		ENCRYPTLV_LL,								// ���ܼ���: �ͼ���,�ԳƼ���(������ѡ���Ƿ񽻻���Կ)
		ENCRYPTLV_SSL,								// ���ܼ���: �߼���,SSL����
	} ENCRYPTLV;
#endif

// ���ܱ�־(����: SafeVCRT_Types.h)
#ifndef ENCRYPTTYPE_DEFINED
	#define ENCRYPTTYPE_DEFINED
	typedef enum enumENCRYPTTYPE
	{	ENCRYPTTYPE_NO,								// δ����
		ENCRYPTTYPE_SESSION,						// ʹ��SESSION_KEY����
		ENCRYPTTYPE_BLOWFISH,						// ʹ��BLOWFISH����
		ENCRYPTTYPE_DES3,							// ʹ��DES3����
	} ENCRYPTTYPE;
#endif


// ѹ��ģʽ(����: SafeVCRT_Types.h)
#ifndef COMPRESSMODE_DEFINED
	#define COMPRESSMODE_DEFINED
	typedef enum enumCOMPRESSMODE
	{	COMPRESS_NONE,								// ����ѹ��
		COMPRESS_SMART,								// ����ѹ��(�����ݰ�ѹ��)
		COMPRESS_FULL,								// ��ȫѹ��(ȫ�������ѹ��)
	} COMPRESSMODE;
#endif


// ѹ�����(����: SafeVCRT_Types.h)
#ifndef COMPRESSTYPE_DEFINED
	#define COMPRESSTYPE_DEFINED
	typedef enum enumCOMPRESSTYPE
	{	COMPRESSTYPE_NONE,							// ����ѹ��
		COMPRESSTYPE_GZIP,							// ʹ��GZIPѹ��
		COMPRESSTYPE_DEFLATE,						// ʹ��DEFLATEѹ��
		COMPRESSTYPE_ZLIB,							// ʹ��ZLIBѹ��
		COMPRESSTYPE_MAX=COMPRESSTYPE_ZLIB,			// ѹ���������ֵ
	} COMPRESSTYPE;
#endif


// ��Ϣ���(����: SafeVCRT_Types.h)
#ifndef MSGTYPE_DEFINED
	#define MSGTYPE_DEFINED
	typedef enum enumMSGTYPE
	{	MSGTYPE_ROSE,								// ROSEЭ��
		MSGTYPE_RROSE,								// RROSEЭ��
		MSGTYPE_PUSHING,							// ����
		MSGTYPE_UNKNOWN,							// δ֪
	} MSGTYPE;
	#define MSGTYPE_DEFAULT MSGTYPE_ROSE
#endif




// Э��ͷ����(��ʹ��EXCLUDE_STD_PACKET_HEADER��������)
#ifndef EXCLUDE_STD_PACKET_HEADER

	//////////////////////////////////////////////////////////////////////////
	// 4.XЭ��ͷ������(������վ,�����м�,��������ʹ�õ�Э��)
	#if !defined(STD_PACKET_HEADER_4X) && (!defined(SELECT_PROT_SPEC)||defined(SELECT_PROT_4X))
		#define STD_PACKET_HEADER_4X
		// ����ṹ����
		typedef struct tagREQHEADER4X
		{	struct
			{	BYTE Version:4;								// Э��汾
				BYTE Compressed:1;							// ѹ����־
				BYTE Encrypted:1;							// SESSION���ܱ�־
				BYTE IsMobile:1;							// �ֻ����ɱ�־
				BYTE Reserved:1;							// ����λ
			} Info;
			SHORT MainID;
			SHORT AssisID;
			char Priority;
			WORD PacketLen;
			WORD RawLen;
		} REQHEADER4X;
		typedef REQHEADER4X* LPREQHEADER4X;
		// Ӧ��ṹ����
		typedef struct tagANSHEADER4X
		{	DWORD Separator;								// �ָ�����,���ڲ��Ӧ�������,������ͷ������SEPARATOR_NUM
			struct tagINFO
			{	BYTE Version:4;								// Э��汾
				BYTE Compressed:1;							// �Ƿ�ѹ��
				BYTE Encrypted:1;							// SESSION���ܱ�־
				BYTE Reserved:2;							// ����λ
			} Info;
			SHORT MainID;									// ������ID
			SHORT AssisID;									// ����ID
			char  Reserved;									// �����ֽ�(��Ϊ0,ԭ���ȼ��ֶ�)
			SHORT req;										// �����
			WORD PacketLen;									// ������(������,��������ͷ�Ϳ���չ��ͷ)
			WORD RawLen;									// ԭʼ������(������,��������ͷ�Ϳ���չ��ͷ)
		} ANSHEADER4X;
		typedef ANSHEADER4X* LPANSHEADER4X;
	#endif


	//////////////////////////////////////////////////////////////////////////
	// ������վЭ��
	#if !defined(STD_PACKET_HEADER_CW) && (!defined(SELECT_PROT_SPEC)||defined(SELECT_PROT_CW))
		#define STD_PACKET_HEADER_CW
		// ����ṹ����
		typedef struct tagREQHEADERCW
		{	struct
			{	BYTE Version:4;								// Э��汾
				BYTE Compressed:1;							// ѹ����־
				BYTE Encrypted:1;							// SESSION���ܱ�־
				BYTE Encrypted2:1;							// ���ܱ�־
				BYTE Reserved:1;							// ����λ
			} Info;
			SHORT MainID;
			SHORT AssisID;
			BYTE Priority;
			UINT PacketLen;
			UINT RawLen;
		} REQHEADERCW;
		typedef REQHEADERCW* LPREQHEADERCW;
		// Ӧ��ṹ����
		typedef struct tagANSHEADERCW
		{	DWORD Separator;								// �ָ�����,���ڲ��Ӧ�������,������ͷ������SEPARATOR_NUM
			struct tagINFO
			{	BYTE Version:4;								// Э��汾
				BYTE Compressed:1;							// �Ƿ�ѹ��
				BYTE Encrypted:1;							// SESSION���ܱ�־
				BYTE Encrypted2:1;							// ���ܱ�־
				BYTE Reserved:1;							// ����λ
			} Info;
			SHORT MainID;									// ������ID
			SHORT AssisID;									// ����ID
			CHAR  Reserved;									// �����ֽ�(��Ϊ0,ԭ���ȼ��ֶ�)
			SHORT req;										// �����
			UINT PacketLen;									// ������(������,��������ͷ�Ϳ���չ��ͷ)
			UINT RawLen;									// ԭʼ������(������,��������ͷ�Ϳ���չ��ͷ)
			UINT Process;									// ������Ϣ
		} ANSHEADERCW;
		typedef ANSHEADERCW* LPANSHEADERCW;
	#endif


	//////////////////////////////////////////////////////////////////////////
	// 5.XЭ��ͷ������(��������,IMServer��ʹ�õ�Э��)
	#if !defined(STD_PACKET_HEADER_5X) && (!defined(SELECT_PROT_SPEC)||defined(SELECT_PROT_5X))
		#define STD_PACKET_HEADER_5X
		// ����ͷ��Ϣ,�ӵ�ǰ�汾��ʼЭ��ͷ���߱�������
		// ����ͨ��OptionLen�����չ��ͷ����,�������256�ֽ�
		// ��Щ��ͷ��Ϣ����ϵͳ������չ,�ɼ���ԭ�в���������Ϣ���Э��
		// ����ͷ�������չ�����㷨����
		typedef struct tagREQHEADER5X
		{	struct tagINFO
			{	BYTE Version:4;							// Э��汾
				BYTE Compressed:1;						// �Ƿ�ѹ��
				BYTE EncryptType:3;						// ��������		
			} Info;
			DWORD TransKey;								// ����Ψһ��ʶ
			BYTE OptionLen;								// ѡ��������(��Э��Ϊ���ȼ��ֶ�,��Ϊ0)
			WORD PacketLen;								// ������(������,��������ͷ�Ϳ���չ��ͷ)
			WORD RawLen;								// ����ԭʼ����(������,��������ͷ�Ϳ���չ��ͷ)
			WORD ReqNo;									// �������
		} REQHEADER5X;
		typedef REQHEADER5X* LPREQHEADER5X;
		// Ӧ��ͷ��Ϣ,��׼Ӧ����Ϣ
		typedef struct tagANSHEADER5X
		{	DWORD Separator;							// ���ָ����(SEPARATOR_NUM)
			struct tagINFO
			{	BYTE Version:4;							// Э��汾
				BYTE Compressed:1;						// �Ƿ�ѹ��
				BYTE EncryptType:3;						// ��������
			} Info;
			DWORD TransKey;								// ����Ψһ��ʶ
			BYTE Reserved;								// ����λ,ȫ��
			WORD ReqNo;									// �����
			WORD PacketLen;								// ������(������,��������ͷ�Ϳ���չ��ͷ)
			WORD RawLen;								// ԭʼ������(������,��������ͷ�Ϳ���չ��ͷ)
		} ANSHEADER5X;
		typedef ANSHEADER5X* LPANSHEADER5X;
		// ���Э������ͷ(���ܱ���ʹ��)
		typedef struct tagREQHEADERHT5X
		{	BYTE Padding;								// ������(0:HTTPX,1:TUNNEL)
			struct tagINFO
			{	BYTE Version:4;							// Э��汾
				BYTE CompressType:2;					// ѹ������
				BYTE EncryptType:2;						// ��������
			} Info;
			UINT64 AspSessionID;						// ASPSESSIONID
			DWORD TransKey;								// ����Ψһ��ʶ
			BYTE OptionLen;								// ѡ��������
			WORD RawLen;								// ����ԭʼ����(������,��������ͷ,������HTTP��ͷ,ѡ����)
			WORD ReqNo;									// �������
		} REQHEADERHT5X,*LPREQHEADERHT5X;
		// ���Э��Ӧ��ͷ
		typedef struct tagANSHEADERHT5X
		{	struct tagINFO
			{	BYTE Version:4;							// Э��汾
				BYTE CompressType:2;					// ѹ������
				BYTE EncryptType:2;						// ��������
			} Info;
			UINT64 AspSessionID;						// ASPSESSIONID
			DWORD TransKey;								// ����Ψһ��ʶ
			WORD RawLen;								// ����ԭʼ����(������,��������ͷ,������HTTP��ͷ)
			WORD ReqNo;									// �������
			BYTE FragmentNo;							// ��Ƭ��
		} ANSHEADERHT5X,*LPANSHEADERHT5X;
		// BUGBUG: HTTPEXTHDR��Ҫ����
	#endif


	//////////////////////////////////////////////////////////////////////////
	// 7.X BETAЭ��ͷ������
	#if !defined(STD_PACKET_HEADER_7BETA) && (!defined(SELECT_PROT_SPEC)||defined(SELECT_PROT_7BETA))
		#define STD_PACKET_HEADER_7BETA
		// ��׼������ṹ
		typedef struct tagREQHEADER7BX
		{	struct tagINFO
			{	BYTE Version:4;							// Э��汾
				BYTE CompressType:2;					// ѹ������
				BYTE EncryptType:2;						// ��������		
			} Info;
			DWORD TransKey;								// ����Ψһ��ʶ
			BYTE OptionLen;								// ѡ��������
			WORD PacketLen;								// ������(������,��������ͷ,ѡ����)
			WORD RawLen;								// ����ԭʼ����(������,��������ͷ,ѡ����)
			WORD ReqNo;									// �������
		} REQHEADER7BX;
		typedef REQHEADER7BX* LPREQHEADER7BX;

		// ��׼Ӧ����ṹ
		typedef struct tagANSHEADER7BX
		{	struct tagINFO
			{	BYTE Version:4;							// Э��汾
				BYTE CompressType:2;					// ѹ������
				BYTE EncryptType:2;						// ��������
			} Info;
			DWORD TransKey;								// ����Ψһ��ʶ
			WORD ReqNo;									// �����
			WORD PacketLen;								// ������(������,��������ͷ,ѡ����)
			WORD RawLen;								// ԭʼ������(������,��������ͷ,ѡ����)
			BYTE FragmentNo;							// ��Ƭ��
		} ANSHEADER7BX;
		typedef ANSHEADER7BX* LPANSHEADER7BX;

		// ���Э������ͷ(���ܱ���ʹ��)
		typedef struct tagREQHEADERHT7BX
		{	BYTE Padding;								// ������(������1,����HTTPЭ������Э��)
			struct tagINFO
			{	BYTE Version:4;							// Э��汾
				BYTE CompressType:2;					// ѹ������
				BYTE EncryptType:2;						// ��������
			} Info;
			UINT64 AspSessionID;						// ASPSESSIONID
			DWORD TransKey;								// ����Ψһ��ʶ
			BYTE OptionLen;								// ѡ��������
			WORD RawLen;								// ����ԭʼ����(������,��������ͷ,������HTTP��ͷ,ѡ����)
			WORD ReqNo;									// �������
		} REQHEADERHT7BX,*LPREQHEADERHT7BX;

		// ���Э��Ӧ��ͷ
		typedef struct tagANSHEADERHT7BX
		{	struct tagINFO
			{	BYTE Version:4;							// Э��汾
				BYTE CompressType:2;					// ѹ������
				BYTE EncryptType:2;						// ��������
			} Info;
			UINT64 AspSessionID;						// ASPSESSIONID
			DWORD TransKey;								// ����Ψһ��ʶ
			WORD RawLen;								// ����ԭʼ����(������,��������ͷ,������HTTP��ͷ)
			WORD ReqNo;									// �������
			BYTE FragmentNo;							// ��Ƭ��
		} ANSHEADERHT7BX,*LPANSHEADERHT7BX;
	#endif


	//////////////////////////////////////////////////////////////////////////
	// 7.X Э��ͷ������
	#if !defined(STD_PACKET_HEADER_7X) && (!defined(SELECT_PROT_SPEC)||defined(SELECT_PROT_7X))
		#define STD_PACKET_HEADER_7X
		
		// ��׼����ͷ
		typedef struct tagMSGHEADER7X
		{	struct tagINFO
			{	BYTE Version:4;							// Э��汾
				BYTE CompressType:2;					// ѹ������
				BYTE EncryptType:2;						// ��������
			} Info;
			DWORD TransKey;								// Ψһ��ʶ
			BYTE OptionLen;								// ѡ��������
			WORD PacketLen;								// ������(������,��������ͷ,ѡ����)
			WORD RawLen;								// ����ԭʼ����(������,��������ͷ,ѡ����)
			WORD ReqNo;									// �������
			BYTE MsgType;								// ��Ϣ����
			BYTE FragmentNo;							// ��Ƭ��
		} MSGHEADER7X;
		typedef MSGHEADER7X* LPMSGHEADER7X;

		// ���Э�鱨��ͷ(���ܱ���ʹ��)
		typedef struct tagMSGHEADERHT7X
		{	BYTE Padding;								// ������(������1,����HTTPЭ������Э��)
			struct tagINFO
			{	BYTE Version:4;							// Э��汾
				BYTE CompressType:2;					// ѹ������
				BYTE EncryptType:2;						// ��������
			} Info;
			UINT64 AspSessionID;						// ASPSESSIONID
			DWORD TransKey;								// ����Ψһ��ʶ
			BYTE OptionLen;								// ѡ��������
			WORD RawLen;								// ����ԭʼ����(������,��������ͷ,������HTTP��ͷ,ѡ����)
			WORD ReqNo;									// �������
			BYTE MsgType;								// ��Ϣ����
			BYTE FragmentNo;							// ��Ƭ��
		} MSGHEADERHT7X,*LPMSGHEADERHT7X;
	#endif


	//////////////////////////////////////////////////////////////////////////
	// ���ݶ���
	#ifdef STD_PACKET_HEADER_5X
		typedef REQHEADER5X REQHEADER;
		typedef LPREQHEADER5X LPREQHEADER;
		typedef ANSHEADER5X ANSHEADER;
		typedef LPANSHEADER5X LPANSHEADER;
	#endif

#endif


// Э��汾����(0,7,8������,����ڳ�ͻ,��Щ��Ҫ�����Э��(GET,POST,FIX)
#define PROT_VERSION_SPEC		0						// ����Э��汾(�ڲ���ͨ,�������ڽ���)
#define PROT_VERSION_EXTEND		1						// ������վЭ��汾
#define PROT_VERSION_5BETA		9						// ��׼Э��汾(5.X,����)
#define PROT_VERSION_HSHQ		12						// ����������վЭ��汾
#define PROT_VERSION_CW			13						// ������վЭ��汾
#define PROT_VERSION_5X			14						// ��׼Э��汾(5.X)
#define PROT_VERSION_7BETA1		13						// ��׼Э��汾(7.X Beta1,���ݾɰ�TP/TS�ܹ��ͻ���,TCPֱ��)
#define PROT_VERSION_7BETA2		15						// ��׼Э��汾(7.X Beta2,���ݾɰ�MP/MUM�ܹ��ͻ���,TCPֱ��)
#define PROT_VERSION_7X			11						// ��׼Э��汾(7.X ��׼T�ܹ�,TAAPI)
#define PROT_VERSION_UNSPEC		65535					// ��Ч�汾��(�����ܳ����ڴ���Э����)

#include "asestdprot_header.inl"


// �ָ�ԭ�ж��뷽ʽ
#pragma pack()

#endif
