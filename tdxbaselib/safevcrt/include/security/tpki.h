//////////////////////////////////////////////////////////////////////////
// ͨѶ����Ҫ����ԭ����㷨
//      1.���ѹ��
//      2.PKI��˽Կ��ϵ����
//      3.PKI��˽Կ��ϵǩ��
//      4.����������㷨(BLOWFISH,DES,3DES)
//      5.��̬������֤(��֤�ֵ�,MD5,DES)
// ���ѹ���㷨
//      ���ѹ���㷨��Ҫ����ZIP��ʽ
// PKI��˽Կ��ϵ����Ҫ����
//      RSA�㷨(֧��128-1024λ),RSA�㷨(֧��128-4096λ),ECC�㷨(֧��224-256λ)
//      SESSION�㷨(RC2,RC4,RC5,RC6,IDEA�㷨)
//      ����ǩ��HASH�㷨(MD2,MD5,SHA)
// ���������
//      �ṩ������ݱ���,ǿ�ƻ���Э�����
// ��̬������֤
//      ͨ�����������ͳ�������+�ͻ����ڴ�����(���������ֵ��EXE�ռ����)�ϲ�����
//      ��̬����,�Զ�̬�������MD5�Լ�DES����,���͵���������
//      �ɷ����������������֤,�жϿͻ��˵ĺϷ���
//      ��Ч��ֹ�ͻ��˱��۸�
#ifndef __TPKI__H__
#define __TPKI__H__


#pragma pack(1)

//////////////////////////////////////////////////////////////////////////
// �ڲ����Լ��ṹ����(RSA1)
#define NN_DIGIT_BITS		 32
#define NN_HALF_DIGIT_BITS	 16
#define NN_DIGIT_LEN		 (NN_DIGIT_BITS / 8)
#define MAX_NN_DIGIT		 0xffffffff
#define MAX_NN_HALF_DIGIT	 0xffff

#define MAX_NN_DIGITS		 ((MAX_RSA_MODULUS_LEN + NN_DIGIT_LEN - 1) / NN_DIGIT_LEN + 1)

#define MIN_RSA_MODULUS_BITS 1
#define MAX_RSA_MODULUS_BITS 1024
#define MAX_RSA_MODULUS_LEN  ((MAX_RSA_MODULUS_BITS + 7) / 8)
#define MAX_RSA_PRIME_BITS   ((MAX_RSA_MODULUS_BITS + 1) / 2)
#define MAX_RSA_PRIME_LEN    ((MAX_RSA_PRIME_BITS + 7) / 8)

#pragma pack(1)

typedef struct 
{	unsigned int bits;									// length in bits of modulus
	unsigned char modulus[MAX_RSA_MODULUS_LEN];   		// modulus
	unsigned char exponent[MAX_RSA_MODULUS_LEN];  		// public exponent
} R_RSA_PUBLIC_KEY;

typedef struct 
{	unsigned int bits;									// length in bits of modulus
	unsigned char modulus[MAX_RSA_MODULUS_LEN];			// modulus
	unsigned char publicExponent[MAX_RSA_MODULUS_LEN];  // public exponent
	unsigned char exponent[MAX_RSA_MODULUS_LEN];        // private exponent
	unsigned char prime[2][MAX_RSA_PRIME_LEN];          // prime factors
	unsigned char primeExponent[2][MAX_RSA_PRIME_LEN];	// exponents for CRT
	unsigned char coefficient[MAX_RSA_PRIME_LEN];       // CRT coefficient
} R_RSA_PRIVATE_KEY;

#pragma pack()





//////////////////////////////////////////////////////////////////////////
//	RSA�㷨�ඨ��(���������ܣ�Ҳ������ǩ��)
//	����һ����Կ: GenerateKeys()
//	�ù�Կ����: PublicBuf
//	��˽Կ����: PrivateBuf
//	ע��:���ܿ鳤��Ӧ��(m_nBits+7)/8��������(!!!)
//	����ʱ���������������Ӧ�������볤��(8+4)�ֽڳ�
//////////////////////////////////////////////////////////////////////////
#if defined(SAFEVCRT_FULLMODE)

// PKI����
typedef enum enumPKITYPE
{	PKI_RSA1,										// RSA1,֧��RSA128-1024
	PKI_RSA2,										// RSA2,֧��RSA128-2048
	PKI_ECC,										// ECC
	PKI_MAX,										// �������֧��
} PKITYPE;
// ��Կ��˽Կ��С
#define MAX_PUBKEY	1024							// �ڴ��С(���������ڴ����ʵ�ʴ���,�ṹ��С��������)
#define MAX_PRIKEY	3072							// �ڴ��С(���������ڴ����ʵ�ʴ���,�ṹ��С��������)

typedef struct tagPUBLICKEY { BYTE m_acKey[MAX_PUBKEY]; } PUBLICKEY,*LPPUBLICKEY;
typedef struct tagPRIVATEKEY { BYTE m_acKey[MAX_PRIKEY]; } PRIVATEKEY,*LPPRIVATEKEY;





class SECURITY_IMP TPKI
{
public:
	TPKI(){}
	virtual~TPKI(){}
public:
	int KeyIndex2Bits(PKITYPE ePKIType,int nIndex);
	int ValidKeyBits(PKITYPE ePKIType,int nBits);
	int CalcKeyLen(PKITYPE ePKIType,int nIndex,BOOL bPubKey);
	int CalcOpMaxNeedLen(PKITYPE ePKIType,LPBYTE pKey,BOOL bPubOp,int nOrgLen);
	int GenerateKeys(LPPUBLICKEY pPubKey,LPPRIVATEKEY pPriKey,PKITYPE ePKIType,int nBits,int bUseFermat4=FALSE);
	int GenerateStrongKeys(LPPUBLICKEY pPubKey,LPPRIVATEKEY pPriKey,PKITYPE ePKIType,int nBits,int bUseFermat4=FALSE);
	int PublicBuf(PKITYPE ePKIType,unsigned char* lpBuffer,LONG nLength,int cbBuffer,LPPUBLICKEY pPubKey);		// ʹ�ù�Կ��������
	int PrivateBuf(PKITYPE ePKIType,unsigned char* lpBuffer,LONG nLength,int cbBuffer,LPPRIVATEKEY pPriKey);	// ʹ��˽Կ��������
	int PrivateBuf2(PKITYPE ePKIType,unsigned char* lpBuffer,LONG nLength,int cbBuffer,LPPRIVATEKEY pPriKey);	// ʹ��˽Կ����(ǩ��)����
	int PublicBuf2(PKITYPE ePKIType,unsigned char* lpBuffer,LONG nLength,int cbBuffer,LPPUBLICKEY pPubKey);		// ʹ�ù�Կ����(ǩ��)����
	BOOL VerifyKeyPair(PKITYPE ePKIType,LPPUBLICKEY pPubKey,LPPRIVATEKEY pPriKey);
private:
	int CalcRSA1BlockLen(LPBYTE pKey,BOOL bPubOp);
};


// ǩ������
DWORD SECURITY_IMP PKI_GenerateSignature(LPCBYTE lpData,DWORD cbData,LPBYTE lpSignature,DWORD cbSignature,PKITYPE ePKIType,LPPRIVATEKEY pPriKey,LONG nHashAlgoType,BOOL bConvert);
BOOL SECURITY_IMP  PKI_VerifySignature(LPCBYTE lpData,DWORD cbData,LPCBYTE lpSignature,DWORD cbSignature,PKITYPE ePKIType,LPPUBLICKEY pPubKey,LONG nHashAlgoType,BOOL bConvert);
DWORD SECURITY_IMP PKI_GenerateSignature2(LPCBYTE lpData,DWORD cbData,LPBYTE lpSignature,DWORD cbSignature,PKITYPE ePKIType,LPPUBLICKEY pPubKey,LONG nHashAlgoType,BOOL bConvert);
BOOL SECURITY_IMP  PKI_VerifySignature2(LPCBYTE lpData,DWORD cbData,LPCBYTE lpSignature,DWORD cbSignature,PKITYPE ePKIType,LPPRIVATEKEY pPriKey,LONG nHashAlgoType,BOOL bConvert);


#endif
#pragma pack()


// ����PKIλ��
static const int RSA1BITS_INT[5] = {128,256,512,768,1024};
static const int RSA2BITS_INT[7] = {128,256,512,768,1024,2048,4096};
static const int ECCBITS_INT[5] = {192,224,256,384,521};
#endif
