#ifndef __ASE__H__
#define __ASE__H__
#define WITH_ASE
#if _MSC_VER > 1000
#pragma once
#endif

// 自动识别外部引用的默认模式
#if !defined(ASELIB_DYNAMIC) && !defined(ASELIB_STATIC)
	#if defined(PLATFORM_WINDOWS)
		#define ASELIB_DYNAMIC
	#else
		#define ASELIB_STATIC
	#endif
#endif

#include "ase_deprecation.h"
#include "ase_err.h"



#if defined(ASE_FOR_SERVER)
	// ase库引用
	#include "aselib.h"							// 基本声明
	#include "asestddef.h"						// ASE标准定义

	// ase库相关类导出
	#include "feature/aselibiximplbase.h"		// ASE/IX类库声明(基础)
	#include "feature/aselibiximplv1.h"			// ASE/IX类库声明(第一代)
	#include "feature/aselibiximplv2.h"			// ASE/IX类库声明(第二代)

	// IX字段弱引用定义
	#if defined(ASE_WITH_IX_WEAK)
		#include "prot_ix/ixstdprot.h"			// IX协议基本定义
		#include "prot_ix/ixstdprot_wt.h"		// IX协议(交易等相关)定义
	#endif
	// IX字段强引用定义
	#if defined(ASE_WITH_IX_STRONG)
		#include "prot_ix/ixstdstru.h"			// IX协议相关标准定义
	#endif
	// IX定义结构引用
	#if defined(ASE_WITH_IX_DEFINE)
		#include "prot_ix/ixstdprot_wtstru.h"	// IX协议(交易等相关)结构定义
	#endif

	// 原始协议引用
	#include "prot_raw/asestdprot_header.h"		// ASE标准协议头定义
	#if defined(ASE_WITH_INTER_PROT)
		#include "prot_raw/asestdprot_inter.h"	// ASE内部互联协议定义
	#endif
	#if defined(ASE_WITH_GS_PROT)
		#include "prot_raw/asestdprot_gs.h"		// ASE通讯网关协议定义
	#endif
	#if defined(ASE_WITH_AS_PROT)
		#include "prot_raw/asestdprot_as.h"		// ASE业务集成平台协议定义
	#endif
	#if defined(ASE_WITH_SAM_PROT)
		#include "prot_raw/asestdprot_sam.h"	// ASE监控协议
	#endif
	#if defined(ASE_WITH_V5_PROT)
		#include "prot_raw/asestdprot_v5.h"		// ASE客户端协议(5.X)
	#endif
	
	// 服务和模块引用
	#if defined(ASE_WITH_AS_MOD_DEF)
		#include "addon/as_fhmdefine.h"			// AS架构模块定义
	#endif
	#if defined(ASE_WITH_V5_MOD_DEF)
		#include "addon/tc_common.h"			// TC架构通用定义
		#include "addon/tc_femdefine.h"			// TC架构非原生模式模块定义
	#endif
	#if defined(ASE_WITH_TS_MOD_DEF)
		#include "addon/ts_define.h"			// TS架构原生模式模块定义
	#endif





#elif defined(ASE_FOR_CLIENT)
	// ase库引用
	#include "aselib.h"							// 基本声明
	#include "asestddef.h"						// ASE标准定义
	// ase库相关类导出
	#include "feature/aselibiximplbase.h"		// ASE/IX类库声明(基础)
	#include "feature/aselibiximplv1.h"			// ASE/IX类库声明(第一代)
	#include "feature/aselibiximplv2.h"			// ASE/IX类库声明(第二代)
	// IX相关引用
	#include "prot_ix/ixstdstru.h"				// IX协议相关标准定义
	#include "prot_ix/ixstdprot.h"				// IX协议基本定义
	#include "prot_ix/ixstdprot_wt.h"			// IX协议(交易等相关)定义
	// 原始协议引用
	#include "prot_raw/asestdprot_header.h"		// ASE标准协议头定义
	#include "prot_raw/asestdprot_v5.h"			// ASE客户端协议(5.X)





#elif defined(ASE_FOR_TCFEM)
	// ase库引用
	#include "aselib.h"							// 基本声明
	#include "asestddef.h"						// ASE标准定义
	// ase库相关类导出
	#include "feature/aselibiximplbase.h"		// ASE/IX类库声明(基础)
	#include "feature/aselibiximplv1.h"			// ASE/IX类库声明(第一代)
	#include "feature/aselibiximplv2.h"			// ASE/IX类库声明(第二代)
	// IX相关引用
	#include "prot_ix/ixstdstru.h"				// IX协议相关标准定义
	#include "prot_ix/ixstdprot.h"				// IX协议基本定义
	#include "prot_ix/ixstdprot_wt.h"			// IX协议(交易等相关)定义
	#include "prot_ix/ixstdprot_wtstru.h"		// IX协议(交易等相关)结构定义
	// 服务和模块引用
	#include "addon/tc_common.h"				// TC架构通用定义
	#include "addon/tc_femdefine.h"				// TC架构非原生模式模块定义
	#include "addon/tc_femdeclare.h"			// TC架构非原生模式模块定义

#elif defined(ASE_FOR_ASFHM)
	// ase库引用
	#include "aselib.h"							// 基本声明
	#include "asestddef.h"						// ASE标准定义
	// ase库相关类导出
	#include "feature/aselibiximplbase.h"		// ASE/IX类库声明(基础)
	#include "feature/aselibiximplv1.h"			// ASE/IX类库声明(第一代)
	#include "feature/aselibiximplv2.h"			// ASE/IX类库声明(第二代)
	// IX相关引用
	#include "prot_ix/ixstdstru.h"				// IX协议相关标准定义
	#include "prot_ix/ixstdprot.h"				// IX协议基本定义
	#include "prot_ix/ixstdprot_wt.h"			// IX协议(交易等相关)定义
	#include "prot_ix/ixstdprot_wtstru.h"		// IX协议(交易等相关)结构定义
	// 服务和模块引用
	#include "addon/as_fhmdefine.h"				// AS架构模块定义
	#include "addon/as_fhmdeclare.h"			// AS架构模块定义

#elif defined(ASE_FOR_TSMOD)

	// ase库引用
	#include "aselib.h"							// 基本声明
	#include "asestddef.h"						// ASE标准定义

	// IX库相关类导出
	#if defined(ASE_WITH_IX_CLASS)
		#include "feature/aselibiximplbase.h"	// IX类库声明(基础)
		#include "feature/aselibiximplv1.h"		// IX类库声明(第一代)
		#include "feature/aselibiximplv2.h"		// IX类库声明(第二代)
	#endif

	// IX字段弱引用定义
	#if defined(ASE_WITH_IX_WEAK)
		#include "prot_ix/ixstdprot.h"			// IX协议基本定义
		#include "prot_ix/ixstdprot_wt.h"		// IX协议(交易等相关)定义
	#endif

	// IX字段强引用定义
	#if defined(ASE_WITH_IX_STRONG)
		#include "prot_ix/ixstdstru.h"			// IX协议相关标准定义
	#endif

	// IX定义结构引用
	#if defined(ASE_WITH_IX_CLASS) && defined(ASE_WITH_IX_DEFINE)
		#include "prot_ix/ixstdprot_wtstru.h"	// IX协议(交易等相关)结构定义
	#endif

	// 协议结构定义
	#if defined(ASE_WITH_PF_DECL)
		#include "prot_raw/asestdprot_header.h"	// ASE标准协议头定义
	#endif

	// 服务和模块引用
	#include "addon/ts_define.h"				// TS架构原生模式模块定义







#elif defined(ASE_FOR_V6MAIN)
	// 基础引用
	#include "asestddef.h"						// ASE标准定义
	// ix协议引用
	#include "prot_ix/ixstdprot.h"				// IX协议基本定义
	#include "prot_ix/ixstdprot_wt.h"			// IX协议(交易等相关)定义


#elif defined(ASE_FOR_V6ADDIN)
	// ix协议引用
	#include "prot_ix/ixstdprot.h"				// IX协议基本定义
	#include "prot_ix/ixstdprot_wt.h"			// IX协议(交易等相关)定义





#elif defined(ASE_FOR_SELF)
	// ase库引用
	#include "aselib.h"							// IX库相关定义
	#include "asestddef.h"						// ASE标准定义
	// ase库相关类导出
	#include "feature/aselibiximplbase.h"		// ASE/IX类库声明(基础)
	#include "feature/aselibiximplv1.h"			// ASE/IX类库声明(第一代)
	#include "feature/aselibiximplv2.h"			// ASE/IX类库声明(第二代)
	// IX相关引用
	#include "prot_ix/ixstdstru.h"				// IX协议相关标准定义
	#include "prot_ix/ixstdprot.h"				// IX协议基本定义
	#include "prot_ix/ixstdprot_wt.h"			// IX协议(交易等相关)定义
	#include "prot_ix/ixstdprot_wtstru.h"		// IX协议(交易等相关)结构定义
	// 服务和模块引用
	#include "addon/tc_common.h"				// TC架构通用定义
	#include "addon/tc_femdefine.h"				// TC架构非原生模式模块定义
	#include "addon/as_fhmdefine.h"				// AS架构模块定义
#else
	#error ASE_FOR_XXX must be defined.
#endif


#if defined(PLATFORM_WINDOWS) && !defined(ASELIB_LIB) && (defined(__ASE_LIB_IX_IMPL_V1__H__)||defined(__ASE_LIB_IX_IMPL_V2__H__))
	#ifndef WTCOMMLIB_NOAUTOLINK
		#if defined(_ARCH_AMD64_)
			// 动态模式
			#if defined(ASELIB_DYNAMIC)
				#ifdef _DEBUG
					#pragma message("Automatically linking with WTCommLibx64d.dll....")
					#pragma comment(lib,"WTCommLibx64d.lib")
				#else
					#pragma message("Automatically linking with WTCommLibx64.dll....")
					#pragma comment(lib,"WTCommLibx64.lib")
				#endif
			// 静态模式
			#else
				#ifdef _DEBUG
					#pragma message("Automatically linking with WTCommLibSx64d.lib....")
					#pragma comment(lib,"WTCommLibSx64d.lib")
				#else
					#pragma message("Automatically linking with WTCommLibSx64.lib....")
					#pragma comment(lib,"WTCommLibSx64.lib")
				#endif
			#endif
		#else
			// 动态模式
			#if defined(ASELIB_DYNAMIC)
				#ifdef _DEBUG
					#pragma message("Automatically linking with WTCommLibd.dll....")
					#pragma comment(lib,"WTCommLibd.lib")
				#else
					#pragma message("Automatically linking with WTCommLib.dll....")
					#pragma comment(lib,"WTCommLib.lib")
				#endif
			// 静态模式
			#else
				#ifdef _DEBUG
					#pragma message("Automatically linking with WTCommLibSd.lib....")
					#pragma comment(lib,"WTCommLibSd.lib")
				#else
					#pragma message("Automatically linking with WTCommLibS.lib....")
					#pragma comment(lib,"WTCommLibS.lib")
				#endif
			#endif
		#endif
	#endif
#endif


#endif
