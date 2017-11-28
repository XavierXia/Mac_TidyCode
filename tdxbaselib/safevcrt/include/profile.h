#ifndef __PROFILE__H__
#define __PROFILE__H__

#if defined(_COMPILE_BY_GCC_)

INT WINAPI clibGetPrivateProfileString(LPCSTR pszSection,LPCSTR pszEntry,LPCSTR pDefDal,LPSTR pszBuffer,UINT nLength,LPCSTR pszFileName);
UINT WINAPI clibGetPrivateProfileInt(LPCSTR pszSection,LPCSTR pszEntry,INT nDefVal,LPCSTR pszFileName);
INT WINAPI clibGetPrivateProfileSection(LPCSTR pszSection,LPSTR pszBuffer,DWORD nLength,LPCSTR pszFileName);
DWORD WINAPI clibGetPrivateProfileSectionNames(LPSTR pszBuffer,DWORD cbSize,LPCSTR pszFileName);
BOOL WINAPI clibGetPrivateProfileStruct(LPCSTR pszSection,LPCSTR pszKey,LPVOID pBuf,UINT nLength,LPCSTR pszFileName);

BOOL WINAPI clibWritePrivateProfileString(LPCSTR pszSection,LPCSTR pszEntry,LPCSTR pszString,LPCSTR pszFileName);
BOOL WINAPI clibWritePrivateProfileSection(LPCSTR pszSection,LPCSTR pszString,LPCSTR pszFileName);
BOOL WINAPI clibWritePrivateProfileStruct(LPCSTR pszSection,LPCSTR pszKey,LPVOID pBuf,UINT cbBuf,LPCSTR pszFileName);

UINT WINAPI clibGetProfileInt(LPCSTR pszSection,LPCSTR pszEntry,INT nDefVal);
INT WINAPI clibGetProfileString(LPCSTR pszSection,LPCSTR pszEntry,LPCSTR pszDefVal,LPSTR pszBuffer,UINT nLength);
BOOL WINAPI clibWriteProfileString(LPCSTR pszSection,LPCSTR pszEntry,LPCSTR pszString);
INT WINAPI clibGetProfileSection(LPCSTR pszSection,LPSTR pszBuffer,DWORD nLength);
BOOL WINAPI clibWriteProfileSection(LPCSTR pszSection,LPCSTR pszKeyAndValues);




#define GetPrivateProfileString			clibGetPrivateProfileString
#define GetPrivateProfileInt			clibGetPrivateProfileInt
#define GetPrivateProfileSection		clibGetPrivateProfileSection
#define GetPrivateProfileSectionNames	clibGetPrivateProfileSectionNames
#define GetPrivateProfileStruct			clibGetPrivateProfileStruct

#define WritePrivateProfileString		clibWritePrivateProfileString
#define WritePrivateProfileSection		clibWritePrivateProfileSection
#define WritePrivateProfileStruct		clibWritePrivateProfileStruct

#define GetProfileInt					clibGetProfileInt
#define GetProfileString				clibGetProfileString
#define WriteProfileString				clibWriteProfileString
#define GetProfileSection				clibGetProfileSection
#define WriteProfileSection				clibWriteProfileSection



#endif

#endif

