//////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2006 - All Rights Reserved
//  ģ������: escapencode
//  ��������: 2006/07/22
//  �����д: zhanglijun
//  ����˵��: ESCAPE����ͽ���
//			  �ڴ���ʹ���ַ���������Э����,���������Ŀ�ǳ���(���ֳ���),ֻ��Ҫ��������
//			  �ؼ�����ķָ��ּ���,����ʱ��ʹ��ת�崦�����ܿ������Ŀ����ַ�
//					\\		[\]
//					\s		[|]
//					\0		0X00
//					\1		0X01
//					\2		0X02
//					\3		0X03
//					\4		0X04
//					\5		0X05
//					\6		0X06
//					\7		0X07
//					\8		0X08
//					\t		0X09, TABLE, [\t]
//					\n		0X0A, NEWLINE, [\n]
//					\b		0X0B
//					\c		0X0C
//					\r		0X0D, RETURN, [\r]
//					\e		0X0E
//					\f		0X0F
//  ����ʾ��: 
//  �޸ļ�¼:
//////////////////////////////////////////////////////////////////////////
#ifndef __ESCAPE_ENCODE__H__
#define __ESCAPE_ENCODE__H__
#if _MSC_VER > 1000
#pragma once
#endif

// ����ESCAPE����,����Ļ��������Ȱ���'\0',�����ַ�������(������'\0')
LONG CLIBMISC_IMP ESCAPE_Encode(LPBYTE bufin,ULONG nbytes,LPSTR bufcoded,LONG outbufmax);
LONG CLIBMISC_IMP ESCAPE_Decode(LPCSTR bufcoded,LPBYTE bufplain,LONG outbufsize);


#endif
