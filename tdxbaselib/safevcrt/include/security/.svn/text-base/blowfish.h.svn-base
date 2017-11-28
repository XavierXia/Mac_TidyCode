#ifndef __BLOWFISH__H__
#define __BLOWFISH__H__

class SECURITY_IMP CBlowfish
{
public:
	CBlowfish();
	CBlowfish(BYTE* pKey,short nKeyBytes);
	~CBlowfish(){};

	// 初始化BLOWFISH
	void InitializeBlowfish(BYTE* pKey,short nKeyBytes);

	// 加密数据,数据长度必须是8的整数倍
	BOOL Encrypt(BYTE* pData,DWORD dwDataLen);

	// 解密数据,数据长度必须是8的整数倍
	BOOL Decrypt(BYTE *pData, DWORD dwDataLen);

protected:
	void Blowfish_encipher(DWORD* xl,DWORD* xr);
	void Blowfish_decipher(DWORD* xl,DWORD* xr);
protected:
	BOOL	m_bInited;
	DWORD	F(DWORD x);
	DWORD	bf_P[18];
	DWORD	bf_S[4][256];
};

// 字符串加密和解密
BOOL SECURITY_IMP BlowfishEncipherBy(LPCSTR pszEncoding,LPSTR pszOut,LONG cbOut,CBlowfish* pFish);
BOOL SECURITY_IMP BlowfishDecipherBy(LPCSTR pszEncoded,LPSTR pszOut,LONG cbOut,CBlowfish* pFish);
BOOL SECURITY_IMP BlowfishEncipher(LPCSTR pszEncoding,LPSTR pszOut,LONG cbOut,LPCSTR pszKey);
BOOL SECURITY_IMP BlowfishDecipher(LPCSTR pszEncoded,LPSTR pszOut,LONG cbOut,LPCSTR pszKey);

#endif
