


#include "des.h"
#include "stdlib.h"

//////////////////////////////////////////////////////////////////////////
static const unsigned long SP1[64] = {
0x01010400L,0x00000000L,0x00010000L,0x01010404L,
0x01010004L,0x00010404L,0x00000004L,0x00010000L,
0x00000400L,0x01010400L,0x01010404L,0x00000400L,
0x01000404L,0x01010004L,0x01000000L,0x00000004L,
0x00000404L,0x01000400L,0x01000400L,0x00010400L,
0x00010400L,0x01010000L,0x01010000L,0x01000404L,
0x00010004L,0x01000004L,0x01000004L,0x00010004L,
0x00000000L,0x00000404L,0x00010404L,0x01000000L,
0x00010000L,0x01010404L,0x00000004L,0x01010000L,
0x01010400L,0x01000000L,0x01000000L,0x00000400L,
0x01010004L,0x00010000L,0x00010400L,0x01000004L,
0x00000400L,0x00000004L,0x01000404L,0x00010404L,
0x01010404L,0x00010004L,0x01010000L,0x01000404L,
0x01000004L,0x00000404L,0x00010404L,0x01010400L,
0x00000404L,0x01000400L,0x01000400L,0x00000000L,
0x00010004L,0x00010400L,0x00000000L,0x01010004L };

static const unsigned long SP2[64] = {
0x80108020L,0x80008000L,0x00008000L,0x00108020L,
0x00100000L,0x00000020L,0x80100020L,0x80008020L,
0x80000020L,0x80108020L,0x80108000L,0x80000000L,
0x80008000L,0x00100000L,0x00000020L,0x80100020L,
0x00108000L,0x00100020L,0x80008020L,0x00000000L,
0x80000000L,0x00008000L,0x00108020L,0x80100000L,
0x00100020L,0x80000020L,0x00000000L,0x00108000L,
0x00008020L,0x80108000L,0x80100000L,0x00008020L,
0x00000000L,0x00108020L,0x80100020L,0x00100000L,
0x80008020L,0x80100000L,0x80108000L,0x00008000L,
0x80100000L,0x80008000L,0x00000020L,0x80108020L,
0x00108020L,0x00000020L,0x00008000L,0x80000000L,
0x00008020L,0x80108000L,0x00100000L,0x80000020L,
0x00100020L,0x80008020L,0x80000020L,0x00100020L,
0x00108000L,0x00000000L,0x80008000L,0x00008020L,
0x80000000L,0x80100020L,0x80108020L,0x00108000L };

static const unsigned long SP3[64] = {
0x00000208L,0x08020200L,0x00000000L,0x08020008L,
0x08000200L,0x00000000L,0x00020208L,0x08000200L,
0x00020008L,0x08000008L,0x08000008L,0x00020000L,
0x08020208L,0x00020008L,0x08020000L,0x00000208L,
0x08000000L,0x00000008L,0x08020200L,0x00000200L,
0x00020200L,0x08020000L,0x08020008L,0x00020208L,
0x08000208L,0x00020200L,0x00020000L,0x08000208L,
0x00000008L,0x08020208L,0x00000200L,0x08000000L,
0x08020200L,0x08000000L,0x00020008L,0x00000208L,
0x00020000L,0x08020200L,0x08000200L,0x00000000L,
0x00000200L,0x00020008L,0x08020208L,0x08000200L,
0x08000008L,0x00000200L,0x00000000L,0x08020008L,
0x08000208L,0x00020000L,0x08000000L,0x08020208L,
0x00000008L,0x00020208L,0x00020200L,0x08000008L,
0x08020000L,0x08000208L,0x00000208L,0x08020000L,
0x00020208L,0x00000008L,0x08020008L,0x00020200L };

static const unsigned long SP4[64] = {
0x00802001L,0x00002081L,0x00002081L,0x00000080L,
0x00802080L,0x00800081L,0x00800001L,0x00002001L,
0x00000000L,0x00802000L,0x00802000L,0x00802081L,
0x00000081L,0x00000000L,0x00800080L,0x00800001L,
0x00000001L,0x00002000L,0x00800000L,0x00802001L,
0x00000080L,0x00800000L,0x00002001L,0x00002080L,
0x00800081L,0x00000001L,0x00002080L,0x00800080L,
0x00002000L,0x00802080L,0x00802081L,0x00000081L,
0x00800080L,0x00800001L,0x00802000L,0x00802081L,
0x00000081L,0x00000000L,0x00000000L,0x00802000L,
0x00002080L,0x00800080L,0x00800081L,0x00000001L,
0x00802001L,0x00002081L,0x00002081L,0x00000080L,
0x00802081L,0x00000081L,0x00000001L,0x00002000L,
0x00800001L,0x00002001L,0x00802080L,0x00800081L,
0x00002001L,0x00002080L,0x00800000L,0x00802001L,
0x00000080L,0x00800000L,0x00002000L,0x00802080L };

static const unsigned long SP5[64] = {
0x00000100L,0x02080100L,0x02080000L,0x42000100L,
0x00080000L,0x00000100L,0x40000000L,0x02080000L,
0x40080100L,0x00080000L,0x02000100L,0x40080100L,
0x42000100L,0x42080000L,0x00080100L,0x40000000L,
0x02000000L,0x40080000L,0x40080000L,0x00000000L,
0x40000100L,0x42080100L,0x42080100L,0x02000100L,
0x42080000L,0x40000100L,0x00000000L,0x42000000L,
0x02080100L,0x02000000L,0x42000000L,0x00080100L,
0x00080000L,0x42000100L,0x00000100L,0x02000000L,
0x40000000L,0x02080000L,0x42000100L,0x40080100L,
0x02000100L,0x40000000L,0x42080000L,0x02080100L,
0x40080100L,0x00000100L,0x02000000L,0x42080000L,
0x42080100L,0x00080100L,0x42000000L,0x42080100L,
0x02080000L,0x00000000L,0x40080000L,0x42000000L,
0x00080100L,0x02000100L,0x40000100L,0x00080000L,
0x00000000L,0x40080000L,0x02080100L,0x40000100L };

static const unsigned long SP6[64] = {
0x20000010L,0x20400000L,0x00004000L,0x20404010L,
0x20400000L,0x00000010L,0x20404010L,0x00400000L,
0x20004000L,0x00404010L,0x00400000L,0x20000010L,
0x00400010L,0x20004000L,0x20000000L,0x00004010L,
0x00000000L,0x00400010L,0x20004010L,0x00004000L,
0x00404000L,0x20004010L,0x00000010L,0x20400010L,
0x20400010L,0x00000000L,0x00404010L,0x20404000L,
0x00004010L,0x00404000L,0x20404000L,0x20000000L,
0x20004000L,0x00000010L,0x20400010L,0x00404000L,
0x20404010L,0x00400000L,0x00004010L,0x20000010L,
0x00400000L,0x20004000L,0x20000000L,0x00004010L,
0x20000010L,0x20404010L,0x00404000L,0x20400000L,
0x00404010L,0x20404000L,0x00000000L,0x20400010L,
0x00000010L,0x00004000L,0x20400000L,0x00404010L,
0x00004000L,0x00400010L,0x20004010L,0x00000000L,
0x20404000L,0x20000000L,0x00400010L,0x20004010L };

static const unsigned long SP7[64] = {
0x00200000L,0x04200002L,0x04000802L,0x00000000L,
0x00000800L,0x04000802L,0x00200802L,0x04200800L,
0x04200802L,0x00200000L,0x00000000L,0x04000002L,
0x00000002L,0x04000000L,0x04200002L,0x00000802L,
0x04000800L,0x00200802L,0x00200002L,0x04000800L,
0x04000002L,0x04200000L,0x04200800L,0x00200002L,
0x04200000L,0x00000800L,0x00000802L,0x04200802L,
0x00200800L,0x00000002L,0x04000000L,0x00200800L,
0x04000000L,0x00200800L,0x00200000L,0x04000802L,
0x04000802L,0x04200002L,0x04200002L,0x00000002L,
0x00200002L,0x04000000L,0x04000800L,0x00200000L,
0x04200800L,0x00000802L,0x00200802L,0x04200800L,
0x00000802L,0x04000002L,0x04200802L,0x04200000L,
0x00200800L,0x00000000L,0x00000002L,0x04200802L,
0x00000000L,0x00200802L,0x04200000L,0x00000800L,
0x04000002L,0x04000800L,0x00000800L,0x00200002L };

static const unsigned long SP8[64] = {
0x10001040L,0x00001000L,0x00040000L,0x10041040L,
0x10000000L,0x10001040L,0x00000040L,0x10000000L,
0x00040040L,0x10040000L,0x10041040L,0x00041000L,
0x10041000L,0x00041040L,0x00001000L,0x00000040L,
0x10040000L,0x10000040L,0x10001000L,0x00001040L,
0x00041000L,0x00040040L,0x10040040L,0x10041000L,
0x00001040L,0x00000000L,0x00000000L,0x10040040L,
0x10000040L,0x10001000L,0x00041040L,0x00040000L,
0x00041040L,0x00040000L,0x10041000L,0x00001000L,
0x00000040L,0x10040040L,0x00001000L,0x00041040L,
0x10001000L,0x00000040L,0x10000040L,0x10040000L,
0x10040040L,0x10000000L,0x00040000L,0x10001040L,
0x00000000L,0x10041040L,0x00040040L,0x10000040L,
0x10040000L,0x10001000L,0x10001040L,0x00000000L,
0x10041040L,0x00041000L,0x00041000L,0x00001040L,
0x00001040L,0x00040040L,0x10000000L,0x10041000L };

static const unsigned short bytebit[8] = {
0200,0100,040,020,010,04,02,01 };

static const unsigned long bigbyte[24] = {
0x800000L,	0x400000L,	0x200000L,	0x100000L,
0x80000L,	0x40000L,	0x20000L,	0x10000L,
0x8000L,	0x4000L,	0x2000L,	0x1000L,
0x800L,	0x400L,	0x200L,	0x100L,
0x80L,		0x40L,		0x20L,		0x10L,
0x8L,		0x4L,		0x2L,		0x1L	};

// Use the key schedule specified in the Standard (ANSI X3.92-1981).
static const unsigned char pc1[56] = {
56,48,40,32,24,16, 8,	 0,57,49,41,33,25,17,
9, 1,58,50,42,34,26,	18,10, 2,59,51,43,35,
62,54,46,38,30,22,14,	 6,61,53,45,37,29,21,
13, 5,60,52,44,36,28,	20,12, 4,27,19,11, 3 };

static const unsigned char totrot[16] = {
1,2,4,6,8,10,12,14,15,17,19,21,23,25,27,28 };

static const unsigned char pc2[48] = {
13,16,10,23, 0, 4, 2,27,14, 5,20, 9,
22,18,11, 3,25, 7,15, 6,26,19,12, 1,
40,51,30,36,46,54,29,39,50,44,32,47,
43,48,38,55,33,52,45,41,49,35,28,31 };

static const unsigned char Df_Key[24] = {	
0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,
0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10,
0x89,0xab,0xcd,0xef,0x01,0x23,0x45,0x67 };

void setKey(const char * pszKey,short flag){
	m_nKeyMode = 0;
    int nlen=strlen(pszKey);
	char *szTempKey=(char *)malloc(nlen+1);
    memset(szTempKey,0,nlen+1);
	strcpy(szTempKey, pszKey);
	make3key(szTempKey,m_DesKey.new_Key24);
	free(szTempKey);
}

void make3key(char * password,unsigned char  hexkey[24]){
	unsigned char * store;
	long first,i;
	unsigned long savek[96];
	
	cp3key(savek);
	unsigned char  Df_Key_Temp[24];
	//	memcpy(Df_Key_Temp,Df_Key,sizeof(Df_Key_Temp));
	memcpy(Df_Key_Temp,Df_Key,sizeof(Df_Key_Temp));
	////for (i=0; i<24; i++) {
	//	fprintf(stderr, "Df_Key_Temp is %i\n",Df_Key_Temp[i]);
	//}
	
	newdes3key(Df_Key_Temp,0);
	for( i = 0; i < 24; i++ ) hexkey[i] = Df_Key_Temp[i];
	first = 1;
	while( (*password != '\0') || first )
	{	store = hexkey;
		for( i = 0; i < 24 && (*password != '\0'); i++ )
		{	*store++ ^= *password & 0x7f;
			*password++ = '\0';
		}
		////for (i=0; i<24; i++) {
		//	fprintf(stderr, "ori hexkey is %i\n",hexkey[i]);
		//}
	
		
		
		d3des(hexkey,hexkey);
		
///for (i=0; i<24; i++) {
		//	fprintf(stderr, "after hexkey is %i\n",hexkey[i]);
		//}
		first = 0;
	}
	use3key(savek);
	//return;
}

void d3des(unsigned char  from[24],unsigned char  into[24]){
	unsigned long swap,leftt[2],middl[2],right[2];
	scrunch(from,leftt);
	scrunch(&from[8],middl);
	scrunch(&from[16],right);
	desfunc(leftt,m_anKnL);
	desfunc(middl,m_anKnL);
	desfunc(right,m_anKnL);
	swap=leftt[1];
	leftt[1]=middl[0];
	middl[0]=swap;
	swap=middl[1];
	middl[1]=right[0];
	right[0]=swap;
	desfunc(leftt,m_anKnR);
	desfunc(middl,m_anKnR);
	desfunc(right,m_anKnR);
	swap=leftt[1];
	leftt[1]=middl[0];
	middl[0]=swap;
	swap=middl[1];
	middl[1]=right[0];
	right[0]=swap;
	desfunc(leftt,m_anKn3);
	desfunc(middl,m_anKn3);
	desfunc(right,m_anKn3);
	unscrun(leftt,into);
	unscrun(middl,&into[8]);
	unscrun(right,&into[16]);
	//return;
}

void desfunc(unsigned long block[2],unsigned long keys[32]){
	unsigned long fval,work,right,leftt;
	long round;
	
	leftt = block[0];
	right = block[1];
	work = ((leftt >> 4) ^ right) & 0x0f0f0f0fL;
	right ^= work;
	leftt ^= (work << 4);
	work = ((leftt >> 16) ^ right) & 0x0000ffffL;
	right ^= work;
	leftt ^= (work << 16);
	work = ((right >> 2) ^ leftt) & 0x33333333L;
	leftt ^= work;
	right ^= (work << 2);
	work = ((right >> 8) ^ leftt) & 0x00ff00ffL;
	leftt ^= work;
	right ^= (work << 8);
	right = ((right << 1) | ((right >> 31) & 1L)) & 0xffffffffL;
	work = (leftt ^ right) & 0xaaaaaaaaL;
	leftt ^= work;
	right ^= work;
	leftt = ((leftt << 1) | ((leftt >> 31) & 1L)) & 0xffffffffL;
	
	for( round = 0; round < 8; round++ )
	{	work  = (right << 28) | (right >> 4);
		work ^= *keys++;
		fval  = SP7[ work		 & 0x3fL];
		fval |= SP5[(work >>  8) & 0x3fL];
		fval |= SP3[(work >> 16) & 0x3fL];
		fval |= SP1[(work >> 24) & 0x3fL];
		work  = right ^ *keys++;
		fval |= SP8[ work		 & 0x3fL];
		fval |= SP6[(work >>  8) & 0x3fL];
		fval |= SP4[(work >> 16) & 0x3fL];
		fval |= SP2[(work >> 24) & 0x3fL];
		leftt ^= fval;
		work  = (leftt << 28) | (leftt >> 4);
		work ^= *keys++;
		fval  = SP7[ work		 & 0x3fL];
		fval |= SP5[(work >>  8) & 0x3fL];
		fval |= SP3[(work >> 16) & 0x3fL];
		fval |= SP1[(work >> 24) & 0x3fL];
		work  = leftt ^ *keys++;
		fval |= SP8[ work		 & 0x3fL];
		fval |= SP6[(work >>  8) & 0x3fL];
		fval |= SP4[(work >> 16) & 0x3fL];
		fval |= SP2[(work >> 24) & 0x3fL];
		right ^= fval;
	}
	
	right = (right << 31) | (right >> 1);
	work = (leftt ^ right) & 0xaaaaaaaaL;
	leftt ^= work;
	right ^= work;
	leftt = (leftt << 31) | (leftt >> 1);
	work = ((leftt >> 8) ^ right) & 0x00ff00ffL;
	right ^= work;
	leftt ^= (work << 8);
	work = ((leftt >> 2) ^ right) & 0x33333333L;
	right ^= work;
	leftt ^= (work << 2);
	work = ((right >> 16) ^ leftt) & 0x0000ffffL;
	leftt ^= work;
	right ^= (work << 16);
	work = ((right >> 4) ^ leftt) & 0x0f0f0f0fL;
	leftt ^= work;
	right ^= (work << 4);
	*block++ = right;
	*block = leftt;
//	return;
}
void scrunch(unsigned char * outof,unsigned long * into){
	*into	 = (*outof++ & 0xffL) << 24;
	*into	|= (*outof++ & 0xffL) << 16;
	*into	|= (*outof++ & 0xffL) << 8;
	*into++ |= (*outof++ & 0xffL);
	*into	 = (*outof++ & 0xffL) << 24;
	*into	|= (*outof++ & 0xffL) << 16;
	*into	|= (*outof++ & 0xffL) << 8;
	*into	|= (*outof   & 0xffL);
}
void unscrun(unsigned long * outof,unsigned char * into){
	*into++ = (unsigned char )((*outof >> 24) & 0xffL);
	*into++ = (unsigned char )((*outof >> 16) & 0xffL);
	*into++ = (unsigned char )((*outof >>  8) & 0xffL);
	*into++ = (unsigned char )((*outof++	& 0xffL));
	*into++ = (unsigned char )((*outof >> 24) & 0xffL);
	*into++ = (unsigned char )((*outof >> 16) & 0xffL);
	*into++ = (unsigned char )((*outof >>  8) & 0xffL);
	*into	= (unsigned char )((*outof & 0xffL));

}

void newdes3key(unsigned char  hexkey[24],short nKeyMode){
	unsigned char * first,* third;
	short nRevMod=0;
	if(nKeyMode==0)
	{	
		nRevMod=1;
		first=hexkey;
		third=&hexkey[16];
	}
	else
	{	
		nRevMod=0;
		first=&hexkey[16];
		third=hexkey;
	}
	newdeskey(&hexkey[8],nRevMod);
	cpkey(m_anKnR);
	newdeskey(third,nKeyMode);
	cpkey(m_anKn3);
	newdeskey(first,nKeyMode);
	
	//for (int i=0; i<32; i++) {
	///	fprintf(stderr, "m_anKnL is %i\n",m_anKnL[i]);
	//}
	//for (int i=0; i<32; i++) {
	//	fprintf(stderr, "m_anKnR is %i\n",m_anKnR[i]);
	//}
	//for (int i=0; i<32; i++) {
	//	fprintf(stderr, "m_anKn3 is %i\n",m_anKn3[i]);
	//}
	
	//return;
}

void cpkey(unsigned long cookedkey[32]){
	unsigned long * from =m_anKnL;
	unsigned long * endp =&m_anKnL[32];
	while(from<endp) *cookedkey++ = *from++;
	//return;
}

void cookey(unsigned long * raw1){
	unsigned long * cook;
	unsigned long * raw0;
	unsigned long dough[32];
	long i=0;
	cook = dough;
	for( i = 0; i < 16; i++,raw1++ )
	{	raw0 = raw1++;
		*cook	 = (*raw0 & 0x00fc0000L) << 6;
		*cook	|= (*raw0 & 0x00000fc0L) << 10;
		*cook	|= (*raw1 & 0x00fc0000L) >> 10;
		*cook++ |= (*raw1 & 0x00000fc0L) >> 6;
		*cook	 = (*raw0 & 0x0003f000L) << 12;
		*cook	|= (*raw0 & 0x0000003fL) << 16;
		*cook	|= (*raw1 & 0x0003f000L) >> 4;
		*cook++ |= (*raw1 & 0x0000003fL);
	}
	usekey(dough);
	return;
}

void cp3key(unsigned long cookedkey[96]){
	cpkey(cookedkey);
	cookedkey=&cookedkey[32];
	unsigned long * from=m_anKnR;
	unsigned long * endp=&m_anKnR[32];
	while(from<endp) *cookedkey++=*from++;
	from=m_anKn3,endp=&m_anKn3[32];
	while(from<endp ) *cookedkey++=*from++;
	//return;
}
void use3key(unsigned long cookedkey[96]){
	unsigned long *to,*endp;
	usekey(cookedkey);
	cookedkey = &cookedkey[32];
	to = m_anKnR,endp = &m_anKnR[32];
	while( to < endp ) *to++ = *cookedkey++;
	to = m_anKn3,endp = &m_anKn3[32];
	while( to < endp ) *to++ = *cookedkey++;
}

void usekey(unsigned long cookedkey[32]){
	unsigned long * to=m_anKnL;
	unsigned long * endp=&m_anKnL[32];
	while(to<endp) *to++ = *cookedkey++;
}

void newdeskey(unsigned char  hexkey[8],short nKeyMode){
	
	long i,j,l,m,n;
	unsigned char  pc1m[56],pcr[56];
	unsigned long kn[32];
	
	for(j=0; j<56; j++)
	{	l=pc1[j];
		m=l&07;
		pc1m[j]=((hexkey[l>>3]&bytebit[m])?1:0);
		//fprintf(stderr, "pc1m%i is %i\n",j,pc1m[j]);
	}
	for(i=0; i<16; i++)
	{	if(nKeyMode==1)
			m=(15-i)<<1;
		else	
			m=i<<1;
		n=m+1;
		kn[m]=kn[n]=0L;
		for(j=0; j<28; j++)
		{	l=j+totrot[i];
			if(l<28)
				pcr[j]=pc1m[l];
			else	pcr[j]=pc1m[l-28];
		}
		for(j=28; j<56; j++)
		{	l=j+totrot[i];
		    if(l<56)
				pcr[j] = pc1m[l];
		    else	pcr[j] = pc1m[l-28];
		}
		for(j=0; j<24; j++)
		{	if(pcr[pc2[j]]) kn[m]|=bigbyte[j];
			if(pcr[pc2[j+24]]) kn[n]|=bigbyte[j];
		}
	}
	
	//for (i=0; i<32; i++) {
	//	fprintf(stderr, "kn%i is %i\n",i,kn[i]);
	//}
	
	cookey(kn);
	
	
	//return;
}

void XXdesAll(short nKeyMode,unsigned char * pData,unsigned long dwDataLen){
	newdes3key(m_DesKey.new_Key24,nKeyMode);
	for(int i=0; i<dwDataLen; i+=24)
		//fprintf(stderr, "the i is ");
		d3des(pData+i,pData+i);
	
	
}

void newEncrypt(unsigned char * pData,long dwDataLen){
	XXdesAll(0, pData, dwDataLen);
}
void newDecrypt(unsigned char * pData,long dwDataLen){
	XXdesAll(1, pData, dwDataLen);
}


int gzcompress(Bytef *data, uLong ndata, 
			   Bytef *zdata, uLong *nzdata)
{
	z_stream c_stream;
	int err = 0;
	
	if(data && ndata > 0)
	{
		c_stream.zalloc = (alloc_func)0;
		c_stream.zfree = (free_func)0;
		c_stream.opaque = (voidpf)0;
		if(deflateInit2(&c_stream, Z_DEFAULT_COMPRESSION, Z_DEFLATED, 
						-MAX_WBITS, 8, Z_DEFAULT_STRATEGY) != Z_OK) return -1;
		c_stream.next_in  = data;
		c_stream.avail_in  = ndata;
		c_stream.next_out = zdata;
		c_stream.avail_out  = *nzdata;
		while (c_stream.avail_in != 0 && c_stream.total_out < *nzdata) 
		{
			if(deflate(&c_stream, Z_NO_FLUSH) != Z_OK) return -1;
		}
        if(c_stream.avail_in != 0) return c_stream.avail_in;
		for (;;) {
			if((err = deflate(&c_stream, Z_FINISH)) == Z_STREAM_END) break;
			if(err != Z_OK) return -1;
		}
		if(deflateEnd(&c_stream) != Z_OK) return -1;
		*nzdata = c_stream.total_out;
		return 0;
	}
	return -1;
}

/* Uncompress gzip data */
int gzdecompress(Byte *zdata, uLong nzdata,                 
				 Byte *data, uLong *ndata)
{
    int err = 0;
    z_stream d_stream = {0}; /* decompression stream */
    static char dummy_head[2] = 
    {
        0x8 + 0x7 * 0x10,
        (((0x8 + 0x7 * 0x10) * 0x100 + 30) / 31 * 31) & 0xFF,
    };
    d_stream.zalloc = (alloc_func)0;
    d_stream.zfree = (free_func)0;
    d_stream.opaque = (voidpf)0;
    d_stream.next_in  = zdata;
    d_stream.avail_in = 0;
    d_stream.next_out = data;
    if(inflateInit2(&d_stream, -MAX_WBITS) != Z_OK) return -1;
    //if(inflateInit2(&d_stream, 47) != Z_OK) return -1;
    while (d_stream.total_out < *ndata && d_stream.total_in < nzdata) {
        d_stream.avail_in = d_stream.avail_out = 1; /* force small buffers */
        if((err = inflate(&d_stream, Z_NO_FLUSH)) == Z_STREAM_END) break;
        if(err != Z_OK )
        {
            if(err == Z_DATA_ERROR)
            {
                d_stream.next_in = (Bytef*) dummy_head;
                d_stream.avail_in = sizeof(dummy_head);
                if((err = inflate(&d_stream, Z_NO_FLUSH)) != Z_OK) 
                {
                    return -1;
                }
            }
            else return -1;
        }
    }
    if(inflateEnd(&d_stream) != Z_OK) return -1;
    *ndata = d_stream.total_out;
    return 0;
}


int httpgzdecompress(Byte *zdata, uLong nzdata,                 
					 Byte *data, uLong *ndata)
{
    int err = 0;
    z_stream d_stream = {0}; /* decompression stream */
    static char dummy_head[2] = 
    {
        0x8 + 0x7 * 0x10,
        (((0x8 + 0x7 * 0x10) * 0x100 + 30) / 31 * 31) & 0xFF,
    };
    d_stream.zalloc = (alloc_func)0;
    d_stream.zfree = (free_func)0;
    d_stream.opaque = (voidpf)0;
    d_stream.next_in  = zdata;
    d_stream.avail_in = 0;
    d_stream.next_out = data;
    if(inflateInit2(&d_stream, 47) != Z_OK) return -1;
    while (d_stream.total_out < *ndata && d_stream.total_in < nzdata) {
        d_stream.avail_in = d_stream.avail_out = 1; /* force small buffers */
        if((err = inflate(&d_stream, Z_NO_FLUSH)) == Z_STREAM_END) break;
        if(err != Z_OK )
        {
            if(err == Z_DATA_ERROR)
            {
                d_stream.next_in = (Bytef*) dummy_head;
                d_stream.avail_in = sizeof(dummy_head);
                if((err = inflate(&d_stream, Z_NO_FLUSH)) != Z_OK) 
                {
                    return -1;
                }
            }
            else return -1;
        }
    }
    if(inflateEnd(&d_stream) != Z_OK) return -1;
    *ndata = d_stream.total_out;
    return 0;
}
