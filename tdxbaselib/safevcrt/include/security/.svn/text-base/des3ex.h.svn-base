#ifndef __DES3_EX__H__
#define __DES3_EX__H__

class CDes3Ex
{
public:
	typedef enum enumALGOMODE { ALGOMODE_DES,ALGOMODE_3DES } ALGOMODE;
	CDes3Ex(ALGOMODE eAlgoMode);
	CDes3Ex(LPCBYTE pKey,LONG nKeyLen,ALGOMODE eAlgoMode);
	CDes3Ex(LPCSTR pszKey,ALGOMODE eAlgoMode=ALGOMODE_3DES);
	~CDes3Ex();

	// 设置模式和密钥
	VOID SetKeyAndMode(LPCSTR pszKey,ALGOMODE eAlgoMode=ALGOMODE_3DES);

	// 获取数据块长度
	LONG GetBlockSize();

	// 加密数据,数据长度必须是8/16/24的整数倍
	BOOL Encrypt(LPBYTE pData,DWORD dwDataLen);

	// 解密数据,数据长度必须是8/16/24的整数倍
	BOOL Decrypt(LPBYTE pData,DWORD dwDataLen);

protected:
	// 功能:产生16个28位的key
	// 参数:源8位的字符串(key),存放key的序号0-1
	// 结果:函数将调用private CreateSubKey将结果存于char SubKeys[keyN][16][48]
	void InitializeKeys(LPCBYTE pKey,LONG nKeyLen,ALGOMODE eAlgoMode);
	void InitializeKey(char* srcBytes,unsigned int keyN);

	//功能:加密8位字符串
	//参数:8位字符串,使用Key的序号0-1
	//结果:函数将加密后结果存放于private szCiphertext[16]
	//      用户通过属性Ciphertext得到
	void EncryptBlock(unsigned char* _srcBytes,unsigned char* _dstBytes,unsigned int keyN);

	//功能:解密16位十六进制字符串
	//参数:16位十六进制字符串,使用Key的序号0-1
	//结果:函数将解密候结果存放于private m_szPlaintext[8]
	//      用户通过属性Plaintext得到
	void DecryptBlock(unsigned char* _srcBytes,unsigned char* _dstBytes,unsigned int keyN);

	//功能:Bytes到Bits的转换,
	//参数:待变换字符串,处理后结果存放缓冲区指针,Bits缓冲区大小
	void Bytes2Bits(char *srcBytes, char* dstBits, unsigned int sizeBits);

	//功能:Bits到Bytes的转换,
	//参数:待变换字符串,处理后结果存放缓冲区指针,Bits缓冲区大小
	void Bits2Bytes(char *dstBytes, char* srcBits, unsigned int sizeBits);

	//功能:Int到Bits的转换,
	//参数:待变换字符串,处理后结果存放缓冲区指针
	void Int2Bits(unsigned int srcByte, char* dstBits);

private:
	// 初始化成员变量
	void InitializeMember();

	//功能:生成子密钥
	//参数:经过PC1变换的56位二进制字符串,生成的m_szSubKeys编号0-1
	//结果:将保存于char m_szSubKeys[16][48]
	void CreateSubKey(char* sz_56key,unsigned int keyN);

	//功能:DES中的F函数,
	//参数:左32位,右32位,key序号(0-15),使用的m_szSubKeys编号0-1
	//结果:均在变换左右32位
	void FunctionF(char* sz_Li,char* sz_Ri,unsigned int iKey,unsigned int keyN);

	//功能:IP变换
	//参数:待处理字符串,处理后结果存放指针
	//结果:函数改变第二个参数的内容
	void InitialPermuteData(char* _src,char* _dst);

	//功能:将右32位进行扩展位48位,
	//参数:原32位字符串,扩展后结果存放指针
	//结果:函数改变第二个参数的内容
	void ExpansionR(char* _src,char* _dst);

	//功能:异或函数,
	//参数:待异或的操作字符串1,字符串2,操作数长度,处理后结果存放指针
	//结果: 函数改变第四个参数的内容
	void XOR(char* szParam1,char* szParam2, unsigned int uiParamLength, char* szReturnValueBuffer);

	//功能:S-BOX , 数据压缩,
	//参数:48位二进制字符串,
	//结果:返回结果:32位字符串
	void CompressFuncS(char* _src48, char* _dst32);

	//功能:IP逆变换,
	//参数:待变换字符串,处理后结果存放指针
	//结果:函数改变第二个参数的内容
	void PermutationP(char* _src,char* _dst);

private:
	ALGOMODE	m_eAlgoMode;				// 加密模式
	char		m_szSubKeys[2][16][48];		// 储存2个16组48位密钥,第2个用于3DES
};


// 字符串加密和解密
BOOL SECURITY_IMP Des3ExEncipherBy(LPCSTR pszEncoding,LPSTR pszOut,LONG cbOut,CDes3Ex* pDes3);
BOOL SECURITY_IMP Des3ExDecipherBy(LPCSTR pszEncoded,LPSTR pszOut,LONG cbOut,CDes3Ex* pDes3);
BOOL SECURITY_IMP Des3ExEncipher(LPCSTR pszEncoding,LPSTR pszOut,LONG cbOut,LPCSTR pszKey,LONG nMode=CDes3Ex::ALGOMODE_3DES);
BOOL SECURITY_IMP Des3ExDecipher(LPCSTR pszEncoded,LPSTR pszOut,LONG cbOut,LPCSTR pszKey,LONG nMode=CDes3Ex::ALGOMODE_3DES);

#endif
