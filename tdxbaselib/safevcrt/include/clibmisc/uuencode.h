//////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2006 - All Rights Reserved
//  ģ������: uuencode
//  ��������: 2006/07/22
//  �����д: zhanglijun
//  ����˵��: UUENCODE����ͽ���(BASE64)
//            ע:��������Դ��WIN2K-SRC,������������������������
//            MIME�����ʽ��Ҫ����:UUENCODE,BASE64,UTF7,UTF8,BINHEX�Լ�QPencode
//            (Quoted-Printable Content-Transfer-Encoding)
//			  ��3������1�����:
//			      [01234567]
//			   -->[012345][67????][=]=]
//			  ��3������2�����:
//			      [01234567][01234567]
//			   -->[012345][670123][4567??][=]
//			  ��3���������:
//			      [01234567][01234567][01234567]
//			   -->[012345][670123][456701]234567]
//  �޸ļ�¼:
//////////////////////////////////////////////////////////////////////////
#ifndef __UU_ENCODE__H__
#define __UU_ENCODE__H__
#if _MSC_VER > 1000
#pragma once
#endif

// ����BASE64����,����Ļ��������Ȱ���'\0',�����ַ�������(������'\0')
long CLIBMISC_IMP UU_Encode(unsigned char* bufin,unsigned long nbytes,char *bufcoded,long outbufmax);
long CLIBMISC_IMP UU_Decode(char* bufcoded,unsigned char* bufplain,long outbufmax);

#endif
