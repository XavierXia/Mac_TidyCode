//////////////////////////////////////////////////////////////////////////
// 通讯层主要加密原理和算法
//      1.封包压缩
//      2.PKI公私钥体系加密
//      3.PKI公私钥体系签名
//      4.外层封包加密算法(BLOWFISH,DES,3DES)
//      5.动态口令验证(验证字典,MD5,DES)
// 封包压缩算法
//      封包压缩算法主要采用ZIP格式
// PKI公私钥体系的主要构成
//      RSA算法(支持128-1024位),RSA算法(支持128-4096位),ECC算法(支持224-256位)
//      SESSION算法(RC2,RC4,RC5,RC6,IDEA算法)
//      数字签名HASH算法(MD2,MD5,SHA)
// 外层封包加密
//      提供外层数据保护,强制基本协议加密
// 动态口令验证
//      通过服务器端送出的种子+客户端内存数据(包括数据字典和EXE空间代码)合并生成
//      动态口令,对动态口令进行MD5以及DES加密,传送到服务器端
//      由服务器端完成数据验证,判断客户端的合法性
//      有效防止客户端被篡改
#ifndef __TPKI__H__
#define __TPKI__H__


#pragma pack(1)

//////////////////////////////////////////////////////////////////////////
// 内部宏以及结构定义(RSA1)
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
//	RSA算法类定义(可用来加密，也可用于签名)
//	生成一对密钥: GenerateKeys()
//	用公钥加密: PublicBuf
//	用私钥加密: PrivateBuf
//	注意:加密块长度应是(m_nBits+7)/8的整数倍(!!!)
//	加密时的输出缓冲区长度应大于输入长度(8+4)字节长
//////////////////////////////////////////////////////////////////////////
#if defined(SAFEVCRT_FULLMODE)

// PKI类型
typedef enum enumPKITYPE
{	PKI_RSA1,										// RSA1,支持RSA128-1024
	PKI_RSA2,										// RSA2,支持RSA128-2048
	PKI_ECC,										// ECC
	PKI_MAX,										// 最大类型支持
} PKITYPE;
// 公钥和私钥大小
#define MAX_PUBKEY	1024							// 内存大小(不可以用于传输和实际存盘,结构大小可能扩充)
#define MAX_PRIKEY	3072							// 内存大小(不可以用于传输和实际存盘,结构大小可能扩充)

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
	int PublicBuf(PKITYPE ePKIType,unsigned char* lpBuffer,LONG nLength,int cbBuffer,LPPUBLICKEY pPubKey);		// 使用公钥加密数据
	int PrivateBuf(PKITYPE ePKIType,unsigned char* lpBuffer,LONG nLength,int cbBuffer,LPPRIVATEKEY pPriKey);	// 使用私钥解密数据
	int PrivateBuf2(PKITYPE ePKIType,unsigned char* lpBuffer,LONG nLength,int cbBuffer,LPPRIVATEKEY pPriKey);	// 使用私钥加密(签名)数据
	int PublicBuf2(PKITYPE ePKIType,unsigned char* lpBuffer,LONG nLength,int cbBuffer,LPPUBLICKEY pPubKey);		// 使用公钥解密(签名)数据
	BOOL VerifyKeyPair(PKITYPE ePKIType,LPPUBLICKEY pPubKey,LPPRIVATEKEY pPriKey);
private:
	int CalcRSA1BlockLen(LPBYTE pKey,BOOL bPubOp);
};


// 签名运算
DWORD SECURITY_IMP PKI_GenerateSignature(LPCBYTE lpData,DWORD cbData,LPBYTE lpSignature,DWORD cbSignature,PKITYPE ePKIType,LPPRIVATEKEY pPriKey,LONG nHashAlgoType,BOOL bConvert);
BOOL SECURITY_IMP  PKI_VerifySignature(LPCBYTE lpData,DWORD cbData,LPCBYTE lpSignature,DWORD cbSignature,PKITYPE ePKIType,LPPUBLICKEY pPubKey,LONG nHashAlgoType,BOOL bConvert);
DWORD SECURITY_IMP PKI_GenerateSignature2(LPCBYTE lpData,DWORD cbData,LPBYTE lpSignature,DWORD cbSignature,PKITYPE ePKIType,LPPUBLICKEY pPubKey,LONG nHashAlgoType,BOOL bConvert);
BOOL SECURITY_IMP  PKI_VerifySignature2(LPCBYTE lpData,DWORD cbData,LPCBYTE lpSignature,DWORD cbSignature,PKITYPE ePKIType,LPPRIVATEKEY pPriKey,LONG nHashAlgoType,BOOL bConvert);


#endif
#pragma pack()


// 典型PKI位数
static const int RSA1BITS_INT[5] = {128,256,512,768,1024};
static const int RSA2BITS_INT[7] = {128,256,512,768,1024,2048,4096};
static const int ECCBITS_INT[5] = {192,224,256,384,521};
#endif
