//////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2006 - All Rights Reserved
//  ģ������: clibMisc
//  ��������: 2006/07/28
//  �����д: zhanglijun
//  ����˵��: CLIB����չ������(��֧��ANSI_CHAR�汾)
//  ����ʾ��: 
//  �޸ļ�¼:
//////////////////////////////////////////////////////////////////////////
#ifndef __CLIB_MISC__H__
#define __CLIB_MISC__H__


//////////////////////////////////////////////////////////////////////////
// ����������
LPVOID CLIBMISC_IMP DupBuffer(LPVOID lpBuffer,LONG nSize);						// ���ƻ�����(�ڲ��ڴ����)
LPSTR CLIBMISC_IMP DupString(LPCSTR lpszString);								// �����ַ���(�ڲ��ڴ����)
LPVOID CLIBMISC_IMP clibMalloc(LONG nSize);										// �ͷ��ڲ��ַ���Ļ�����
LPVOID CLIBMISC_IMP clibInternalFree(LPVOID lpBuffer);							// �ͷ��ڲ�����Ļ�����
#ifndef TFREECLIBINTERNAL
	#define TFREECLIBINTERNAL(a)	\
		if((a)!=NULL)				\
		{	clibInternalFree(a);	\
			(a)=NULL;				\
		}
#endif





#endif
