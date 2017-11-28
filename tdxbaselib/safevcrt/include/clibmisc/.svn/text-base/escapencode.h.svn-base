//////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2006 - All Rights Reserved
//  模块名称: escapencode
//  创建日期: 2006/07/22
//  代码编写: zhanglijun
//  功能说明: ESCAPE编码和解码
//			  在大量使用字符串交换的协议中,其二进制数目非常少(汉字除外),只需要避免其中
//			  关键意义的分割字即可,整个时候使用转义处理来避开基本的控制字符
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
//  引用示例: 
//  修改记录:
//////////////////////////////////////////////////////////////////////////
#ifndef __ESCAPE_ENCODE__H__
#define __ESCAPE_ENCODE__H__
#if _MSC_VER > 1000
#pragma once
#endif

// 进行ESCAPE编码,输入的缓冲区长度包括'\0',返回字符串长度(不包括'\0')
LONG CLIBMISC_IMP ESCAPE_Encode(LPBYTE bufin,ULONG nbytes,LPSTR bufcoded,LONG outbufmax);
LONG CLIBMISC_IMP ESCAPE_Decode(LPCSTR bufcoded,LPBYTE bufplain,LONG outbufsize);


#endif
