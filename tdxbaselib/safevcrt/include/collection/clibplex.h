//////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2007 - All Rights Reserved
//  ģ������: clibplex
//  ��������: 2007/05/26
//  �����д: zhanglijun
//  ����˵��: ��׼���������,��ǰ����֯һ������������������ڴ�鹹�ɵ�����
//            ÿ������Ԫ����һ������������ݵ�Ԫ�������ڴ�,��������ڴ��
//            ͷ�����ڱ�����һ�����ݿ��λ�á�
//  ����ʾ��: 
//  �޸ļ�¼:
//////////////////////////////////////////////////////////////////////////
#ifndef __CLIB_PLEX__H__
#define __CLIB_PLEX__H__

// ���ݿ�������
struct COLLECTION_IMP TClibPlex
{
	TClibPlex* pNext;						// ��һ�����ݿ�λ��
	void* data() { return this+1; }			// ����ͷ���������Ļ�����,��СΪ[��Ŀ��С*ÿ����������ݸ���]
	static TClibPlex* PASCAL Create(TClibPlex*& head,UINT nMax,UINT cbElement);
	void FreeDataChain();
};

#endif
