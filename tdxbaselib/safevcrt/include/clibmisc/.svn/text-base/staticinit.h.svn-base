//////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2006 - All Rights Reserved
//  模块名称: staticinit
//  创建日期: 2006/07/22
//  代码编写: zhanglijun
//  功能说明: 静态初始化辅助宏
//  引用示例: 
//            静态变量初始化
//					static char s_anArray[100];
//					static BEGIN_STATIC_INIT(s_anArray)
//					...(YOUR CODE)
//					END_STATIC_INIT(s_anArray)
//            静态变量初始化及析构器
//					char* s_Buffer=NULL;
//					IMPLAMENT_STATIC_CONSTRUCTION(s_Buffer)
//					...(YOUR INIT CODE)
//					END_STATIC_INITINST(s_Buffer)
//					...(YOUR EXIT CODE)
//					END_STATIC_EXITINST(s_Buffer)
//  修改记录:
//////////////////////////////////////////////////////////////////////////


// 开始(静态)变量静态初始化
#define BEGIN_STATIC_INIT(VAR_NAME)											\
	static BOOL s_StaticInit_Of_##VAR_NAME()								\
	{																		\


// 完成(静态)变量静态初始化
#define END_STATIC_INIT(VAR_NAME)											\
		return TRUE;														\
	}																		\
	static BOOL s_StaticInited_Of_##VAR_NAME=s_StaticInit_Of_##VAR_NAME();	\






// 开始(静态)环境构造器初始化
#define IMPLAMENT_STATIC_CONSTRUCTION(NAME)									\
	class CStaticInit_Of_##NAME												\
	{																		\
	public:																	\
		CStaticInit_Of_##NAME();											\
		~CStaticInit_Of_##NAME();											\
	};																		\
	CStaticInit_Of_##NAME::CStaticInit_Of_##NAME()							\
	{																		\

// 完成(静态)环境构造器初始化
#define END_STATIC_INITINST(NAME)											\
	}																		\
	CStaticInit_Of_##NAME::~CStaticInit_Of_##NAME()							\
	{																		\

// 完成(静态)环境析造器初始化
#define END_STATIC_EXITINST(NAME)											\
	}																		\
	static CStaticInit_Of_##NAME s_StaticInit_Of_##NAME;					\

