//////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2006 - All Rights Reserved
//  模块名称: clibMisc
//  创建日期: 2006/07/28
//  代码编写: zhanglijun
//  功能说明: CLIB的扩展函数集(仅支持ANSI_CHAR版本)
//  引用示例: 
//  修改记录:
//////////////////////////////////////////////////////////////////////////
#ifndef __CLIB_MISC__H__
#define __CLIB_MISC__H__


//////////////////////////////////////////////////////////////////////////
// 缓冲区处理
LPVOID CLIBMISC_IMP DupBuffer(LPVOID lpBuffer,LONG nSize);						// 复制缓冲区(内部内存分配)
LPSTR CLIBMISC_IMP DupString(LPCSTR lpszString);								// 复制字符串(内部内存分配)
LPVOID CLIBMISC_IMP clibMalloc(LONG nSize);										// 释放内部分分配的缓冲区
LPVOID CLIBMISC_IMP clibInternalFree(LPVOID lpBuffer);							// 释放内部分配的缓冲区
#ifndef TFREECLIBINTERNAL
	#define TFREECLIBINTERNAL(a)	\
		if((a)!=NULL)				\
		{	clibInternalFree(a);	\
			(a)=NULL;				\
		}
#endif





#endif
