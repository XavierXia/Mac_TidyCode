#ifndef __MD5__H__
#define __MD5__H__
#include "../safevcrt.h"

// 基本实现
#pragma pack(1)

typedef struct tagMD5CONTEXT
{	uint32 buf[4];
	uint32 bits[2];
	unsigned char in[64];
} MD5CONTEXT;

void LITEMD5_IMP MD5_Init(MD5CONTEXT *);
void LITEMD5_IMP MD5_Update(MD5CONTEXT *,unsigned const char*,unsigned);
void LITEMD5_IMP MD5_Final(unsigned char digest[16],MD5CONTEXT*);
typedef MD5CONTEXT MD5_CTX;

// 生成指定缓冲区/字符串的MD5串(大小必须是33字节,包括MD5结束字)
void LITEMD5_IMP MD5_Buffer(unsigned char* lpszBuf,unsigned long nLen,char* pMD5String);
void LITEMD5_IMP MD5_String(const char* lpszStr,char* pMD5String);

// 生成指定缓冲区/字符串的MD5值(全长16字节)
void LITEMD5_IMP MD5Bin_Buffer(unsigned char* lpszBuf,unsigned long nLen,LPMD5BIN lpMD5Bin);
void LITEMD5_IMP MD5Bin_String(char* lpszStr,LPMD5BIN lpMD5Bin);

// 检查判断MD5数据是否一致(检查空指针)
BOOL LITEMD5_IMP IsMD5BinMatch(LPCMD5BIN lpMD5Bin1,LPCMD5BIN lpMD5Bin2);

#pragma pack()

#endif
