//////////////////////////////////////////////////////////////////////////
// 支持DES3的加密算法
#ifndef __DES3__H__
#define __DES3__H__


class SECURITY_IMP CDes3
{
public:
	typedef enum enumALGOMODE { ALGOMODE_DES,ALGOMODE_DDES,ALGOMODE_D2DES,ALGOMODE_D3DES } ALGOMODE;
	CDes3(ALGOMODE eAlgoMode);
	CDes3(LPCBYTE pKey,LONG nKeyLen,ALGOMODE eAlgoMode);
	CDes3(LPCSTR pszKey,ALGOMODE eAlgoMode=ALGOMODE_D3DES);
	~CDes3(){};

	// 设置模式和密钥
	VOID SetKeyAndMode(LPCSTR pszKey,ALGOMODE eAlgoMode=ALGOMODE_D3DES);

	// 获取数据块长度
	LONG GetBlockSize();

	// 加密数据,数据长度必须是8/16/24的整数倍
	BOOL Encrypt(LPBYTE pData,DWORD dwDataLen);

	// 解密数据,数据长度必须是8/16/24的整数倍
	BOOL Decrypt(LPBYTE pData,DWORD dwDataLen);
	
protected:
	// Encrypts/Decrypts (according to the key currently loaded in the
	// internal key register) one block of eight bytes at address 'from'
	// into the block at address 'to'.  They can be the same.
	BOOL XXdesAll(SHORT nKeyMode,LPBYTE pData,DWORD dwDataLen);

	// Encrypts/Decrypts (according to the key currently loaded in the
	// internal key register) one block of eight bytes at address 'from'
	// into the block at address 'to'.  They can be the same.
	VOID des(BYTE from[8],BYTE into[8]);

	// Encrypts/Decrypts (according to the keyS currently loaded in the
	// internal key registerS) one block of eight bytes at address 'from'
	// into the block at address 'into'.  They can be the same.
	VOID Ddes(BYTE from[8],BYTE into[8]);

	// Encrypts/Decrypts (according to the keyS currently loaded in the
	// internal key registerS) one block of SIXTEEN bytes at address 'from'
	// into the block at address 'into'.  They can be the same.
	VOID D2des(BYTE from[16],BYTE into[16]);

	// Encrypts/Decrypts (according to the keyS currently loaded in the
	// internal key registerS) one block of SIXTEEN bytes at address 'from'
	// into the block at address 'into'.  They can be the same.
	VOID D3des(BYTE from[24],BYTE into[24]);


	// With a double-length default key, this routine hashes a NULL-terminated
	// string into an eight-byte random-looking key, suitable for use with the
	// deskey() routine.
	VOID makekey(LPSTR password,BYTE hexkey[8]);

	// With a double-length default hexkey, this routine hashes a NULL-terminated
	// string into a sixteen-byte random-looking hexkey, suitable for use with the
	// des2key() routine.
	VOID make2key(LPSTR password,BYTE hexkey[16]);

	// With a triple-length default hexkey, this routine hashes a NULL-terminated
	// string into a twenty-four-byte random-looking hexkey, suitable for use with
	// the des3key() routine.
	VOID make3key(LPSTR password,BYTE hexkey[24]);



	// Key Mode
	enum enumKEYMODE { KEYMODE_ENCRYPT,KEYMODE_DECRYPT };

	// Sets the internal key register according to the hexadecimal
	// key contained in the 8 bytes of hexkey, according to the DES,
	// for encryption or decryption according to MODE.
	VOID deskey(BYTE hexkey[8],SHORT nKeyMode);

	// Copies the contents of the internal key register into the storage
	// located at &cookedkey[0].
	VOID cpkey(DWORD cookedkey[32]);


	// Sets the internal key registerS according to the hexadecimal
	// keyS contained in the 16 bytes of hexkey, according to the DES,
	// for DOUBLE encryption or decryption according to MODE.
	// NOTE: this clobbers all three key registers!
	VOID des2key(BYTE hexkey[16],SHORT nKeyMode);


	// Sets the internal key registerS according to the hexadecimal
	// keyS contained in the 24 bytes of hexkey, according to the DES,
	// for DOUBLE encryption or decryption according to MODE.
	VOID des3key(BYTE hexkey[24],SHORT nKeyMode);

	// Copies the contents of the 3 internal key registerS into the storage
	// located at &cookedkey[0].
	VOID cp3key(DWORD cookedkey[96]);



	// Loads the internal key register with the data in cookedkey.
	VOID usekey(DWORD cookedkey[32]);

	// Loads the 3 internal key registerS with the data in cookedkey.
	VOID use3key(DWORD cookedkey[96]);

	// Loads the internal key register with the data from raw data.
	VOID cookey(LPDWORD raw1);

	// encoding/decoding func
	VOID desfunc(DWORD block[2],DWORD keys[32]);
	VOID scrunch(LPBYTE outof,LPDWORD into);
	VOID unscrun(LPDWORD outof,LPBYTE into);

	typedef union tagDESHEXKEY
	{	BYTE m_Key8[8];
		BYTE m_Key16[16];
		BYTE m_Key24[24];
	} DESHEXKEY;
protected:
	ALGOMODE	m_eAlgoMode;
	SHORT		m_nKeyMode;
	DESHEXKEY	m_DesKey;
	DWORD		m_anKnL[32];
	DWORD		m_anKnR[32];
	DWORD		m_anKn3[32];
};



// 字符串加密和解密
BOOL SECURITY_IMP Des3EncipherBy(LPCSTR pszEncoding,LPSTR pszOut,LONG cbOut,CDes3* pDes3);
BOOL SECURITY_IMP Des3DecipherBy(LPCSTR pszEncoded,LPSTR pszOut,LONG cbOut,CDes3* pDes3);
BOOL SECURITY_IMP Des3Encipher(LPCSTR pszEncoding,LPSTR pszOut,LONG cbOut,LPCSTR pszKey,LONG nMode=CDes3::ALGOMODE_D3DES);
BOOL SECURITY_IMP Des3Decipher(LPCSTR pszEncoded,LPSTR pszOut,LONG cbOut,LPCSTR pszKey,LONG nMode=CDes3::ALGOMODE_D3DES);




#endif
