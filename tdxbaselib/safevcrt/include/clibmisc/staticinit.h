//////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2006 - All Rights Reserved
//  ģ������: staticinit
//  ��������: 2006/07/22
//  �����д: zhanglijun
//  ����˵��: ��̬��ʼ��������
//  ����ʾ��: 
//            ��̬������ʼ��
//					static char s_anArray[100];
//					static BEGIN_STATIC_INIT(s_anArray)
//					...(YOUR CODE)
//					END_STATIC_INIT(s_anArray)
//            ��̬������ʼ����������
//					char* s_Buffer=NULL;
//					IMPLAMENT_STATIC_CONSTRUCTION(s_Buffer)
//					...(YOUR INIT CODE)
//					END_STATIC_INITINST(s_Buffer)
//					...(YOUR EXIT CODE)
//					END_STATIC_EXITINST(s_Buffer)
//  �޸ļ�¼:
//////////////////////////////////////////////////////////////////////////


// ��ʼ(��̬)������̬��ʼ��
#define BEGIN_STATIC_INIT(VAR_NAME)											\
	static BOOL s_StaticInit_Of_##VAR_NAME()								\
	{																		\


// ���(��̬)������̬��ʼ��
#define END_STATIC_INIT(VAR_NAME)											\
		return TRUE;														\
	}																		\
	static BOOL s_StaticInited_Of_##VAR_NAME=s_StaticInit_Of_##VAR_NAME();	\






// ��ʼ(��̬)������������ʼ��
#define IMPLAMENT_STATIC_CONSTRUCTION(NAME)									\
	class CStaticInit_Of_##NAME												\
	{																		\
	public:																	\
		CStaticInit_Of_##NAME();											\
		~CStaticInit_Of_##NAME();											\
	};																		\
	CStaticInit_Of_##NAME::CStaticInit_Of_##NAME()							\
	{																		\

// ���(��̬)������������ʼ��
#define END_STATIC_INITINST(NAME)											\
	}																		\
	CStaticInit_Of_##NAME::~CStaticInit_Of_##NAME()							\
	{																		\

// ���(��̬)������������ʼ��
#define END_STATIC_EXITINST(NAME)											\
	}																		\
	static CStaticInit_Of_##NAME s_StaticInit_Of_##NAME;					\

