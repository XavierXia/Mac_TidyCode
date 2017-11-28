//////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2007 - All Rights Reserved
//  模块名称: cachedfile
//  创建日期: 2003/05/26
//  代码编写: zhanglijun
//  功能说明: 带缓冲的文件读取类
//            用于大量文件的操作,减少磁盘IO的次数,以提高文件缓冲处理的速度。
//            系统每次读取一个块大小,在块使用了一半后继续下次读取,对调用者透明。
//            适用大小小于2G的文件高速批量操作,例如文件检索等等。
//  引用示例: 
//  修改记录:
//////////////////////////////////////////////////////////////////////////
#ifndef __CACHED_FILE__H__
#define __CACHED_FILE__H__
#if _MSC_VER > 1000
#pragma once
#endif
#include "../safevcrt.h"

class LITEFILEIO_IMP CCachedFile
{
public:
	CCachedFile(LPCTSTR pszFile,LONG nBlockSize=128*1024*64);
	virtual~CCachedFile();
	LONG GetAbsOffset();
	BOOL ReadLine(LPSTR pszBuffer,LONG nBufferSize,LPLONG pnOffset,LPLONG pnLineLen);
	BOOL ReadBlock(LPSTR pszBuffer,LONG nBufferSize,LPLONG pnOffset,LPLONG pnRead);
protected:
	TCHAR	m_szLog[MAX_PATH];
	LONG	m_nBlockSize;
	LONG	m_nFileOffset;
	LONG	m_nOffset;
	LONG	m_nUsed;
	FILE*	m_fpLog;
	CHAR*	m_lpBlock;
};


#endif
