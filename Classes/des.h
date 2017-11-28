#include <stdio.h>
#include <string.h>
#include <zlib.h>
//#include "GTMBase64.h"



typedef unsigned long DES_KS[16][2];	/* Single-key DES key schedule */
typedef unsigned long DES3_KS[48][2];	/* Triple-DES key schedule */

/* In deskey.c: */
void deskey(DES_KS,unsigned char *,int);
void des3key(DES3_KS,unsigned char *,int);

/* In desport.c, desborl.cas or desgnu.s: */
void des(DES_KS,unsigned char *);
/* In des3port.c, des3borl.cas or des3gnu.s: */
void des3(DES3_KS,unsigned char *);

void gethex(char *result,char *cp,int cnt);
void memxor( char *,char *,int);
int doencrypt(DES3_KS,int cbc,char iv[8],char *in,char *out,int _length);
int dodecrypt(DES3_KS,int cbc,char iv[8],FILE *in,FILE *out);

extern int Asmversion;	/* 1 if we're linked with an asm version, 0 if C */


void setKey(const char * pszKey,short flag);
void d3des(unsigned char  from[24],unsigned char  into[24]);
void make3key(char * password,unsigned char  hexkey[24]);
void newdeskey(unsigned char  hexkey[8],short nKeyMode);
//void newdes2key(unsigned char * hexkey,short nKeyMode);
void newdes3key(unsigned char  hexkey[24],short nKeyMode);
void cpkey(unsigned long cookedkey[32]);
void cp3key(unsigned long cookedkey[96]);
void cookey(unsigned long * raw1);
void usekey(unsigned long cookedkey[32]);
void use3key(unsigned long cookedkey[96]);

// 加密数据,数据长度必须是8/16/24的整数倍
void newEncrypt(unsigned char * pData,long dwDataLen);

// 解密数据,数据长度必须是8/16/24的整数倍
void newDecrypt(unsigned char * pData,long dwDataLen);


// encoding/decoding func
void desfunc(unsigned long block[2],unsigned long keys[32]);
void scrunch(unsigned char * outof,unsigned long * into);
void unscrun(unsigned long * outof,unsigned char * into);

void XXdesAll(short nKeyMode,unsigned char * pData,unsigned long dwDataLen);

typedef struct {	
		unsigned char new_Key8[8];
		unsigned char new_Key16[16];
		unsigned char new_Key24[24];
	} DESHEXKEY;

DESHEXKEY	m_DesKey;
unsigned long m_anKnL[32];
unsigned long m_anKnR[32];
unsigned long m_anKn3[32];
short m_nKeyMode;


int gzcompress(Bytef *data, uLong ndata, Bytef *zdata, uLong *nzdata);
int gzdecompress(Byte *zdata, uLong nzdata,Byte *data, uLong *ndata);
int httpgzdecompress(Byte *zdata, uLong nzdata,Byte *data, uLong *ndata);
