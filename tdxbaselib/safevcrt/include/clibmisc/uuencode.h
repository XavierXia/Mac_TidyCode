//////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2006 - All Rights Reserved
//  模块名称: uuencode
//  创建日期: 2006/07/22
//  代码编写: zhanglijun
//  功能说明: UUENCODE编码和解码(BASE64)
//            注:本代码来源于WIN2K-SRC,修正其中输出缓冲区溢出问题
//            MIME编码格式主要包括:UUENCODE,BASE64,UTF7,UTF8,BINHEX以及QPencode
//            (Quoted-Printable Content-Transfer-Encoding)
//			  被3整除余1的情况:
//			      [01234567]
//			   -->[012345][67????][=]=]
//			  被3整除余2的情况:
//			      [01234567][01234567]
//			   -->[012345][670123][4567??][=]
//			  被3整除的情况:
//			      [01234567][01234567][01234567]
//			   -->[012345][670123][456701]234567]
//  修改记录:
//////////////////////////////////////////////////////////////////////////
#ifndef __UU_ENCODE__H__
#define __UU_ENCODE__H__
#if _MSC_VER > 1000
#pragma once
#endif

// 进行BASE64编码,输入的缓冲区长度包括'\0',返回字符串长度(不包括'\0')
long CLIBMISC_IMP UU_Encode(unsigned char* bufin,unsigned long nbytes,char *bufcoded,long outbufmax);
long CLIBMISC_IMP UU_Decode(char* bufcoded,unsigned char* bufplain,long outbufmax);

#endif
