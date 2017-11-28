#ifndef __ASE__H__
#define __ASE__H__
#define WITH_ASE
#if _MSC_VER > 1000
#pragma once
#endif

// �Զ�ʶ���ⲿ���õ�Ĭ��ģʽ
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
	// ase������
	#include "aselib.h"							// ��������
	#include "asestddef.h"						// ASE��׼����

	// ase������ർ��
	#include "feature/aselibiximplbase.h"		// ASE/IX�������(����)
	#include "feature/aselibiximplv1.h"			// ASE/IX�������(��һ��)
	#include "feature/aselibiximplv2.h"			// ASE/IX�������(�ڶ���)

	// IX�ֶ������ö���
	#if defined(ASE_WITH_IX_WEAK)
		#include "prot_ix/ixstdprot.h"			// IXЭ���������
		#include "prot_ix/ixstdprot_wt.h"		// IXЭ��(���׵����)����
	#endif
	// IX�ֶ�ǿ���ö���
	#if defined(ASE_WITH_IX_STRONG)
		#include "prot_ix/ixstdstru.h"			// IXЭ����ر�׼����
	#endif
	// IX����ṹ����
	#if defined(ASE_WITH_IX_DEFINE)
		#include "prot_ix/ixstdprot_wtstru.h"	// IXЭ��(���׵����)�ṹ����
	#endif

	// ԭʼЭ������
	#include "prot_raw/asestdprot_header.h"		// ASE��׼Э��ͷ����
	#if defined(ASE_WITH_INTER_PROT)
		#include "prot_raw/asestdprot_inter.h"	// ASE�ڲ�����Э�鶨��
	#endif
	#if defined(ASE_WITH_GS_PROT)
		#include "prot_raw/asestdprot_gs.h"		// ASEͨѶ����Э�鶨��
	#endif
	#if defined(ASE_WITH_AS_PROT)
		#include "prot_raw/asestdprot_as.h"		// ASEҵ�񼯳�ƽ̨Э�鶨��
	#endif
	#if defined(ASE_WITH_SAM_PROT)
		#include "prot_raw/asestdprot_sam.h"	// ASE���Э��
	#endif
	#if defined(ASE_WITH_V5_PROT)
		#include "prot_raw/asestdprot_v5.h"		// ASE�ͻ���Э��(5.X)
	#endif
	
	// �����ģ������
	#if defined(ASE_WITH_AS_MOD_DEF)
		#include "addon/as_fhmdefine.h"			// AS�ܹ�ģ�鶨��
	#endif
	#if defined(ASE_WITH_V5_MOD_DEF)
		#include "addon/tc_common.h"			// TC�ܹ�ͨ�ö���
		#include "addon/tc_femdefine.h"			// TC�ܹ���ԭ��ģʽģ�鶨��
	#endif
	#if defined(ASE_WITH_TS_MOD_DEF)
		#include "addon/ts_define.h"			// TS�ܹ�ԭ��ģʽģ�鶨��
	#endif





#elif defined(ASE_FOR_CLIENT)
	// ase������
	#include "aselib.h"							// ��������
	#include "asestddef.h"						// ASE��׼����
	// ase������ർ��
	#include "feature/aselibiximplbase.h"		// ASE/IX�������(����)
	#include "feature/aselibiximplv1.h"			// ASE/IX�������(��һ��)
	#include "feature/aselibiximplv2.h"			// ASE/IX�������(�ڶ���)
	// IX�������
	#include "prot_ix/ixstdstru.h"				// IXЭ����ر�׼����
	#include "prot_ix/ixstdprot.h"				// IXЭ���������
	#include "prot_ix/ixstdprot_wt.h"			// IXЭ��(���׵����)����
	// ԭʼЭ������
	#include "prot_raw/asestdprot_header.h"		// ASE��׼Э��ͷ����
	#include "prot_raw/asestdprot_v5.h"			// ASE�ͻ���Э��(5.X)





#elif defined(ASE_FOR_TCFEM)
	// ase������
	#include "aselib.h"							// ��������
	#include "asestddef.h"						// ASE��׼����
	// ase������ർ��
	#include "feature/aselibiximplbase.h"		// ASE/IX�������(����)
	#include "feature/aselibiximplv1.h"			// ASE/IX�������(��һ��)
	#include "feature/aselibiximplv2.h"			// ASE/IX�������(�ڶ���)
	// IX�������
	#include "prot_ix/ixstdstru.h"				// IXЭ����ر�׼����
	#include "prot_ix/ixstdprot.h"				// IXЭ���������
	#include "prot_ix/ixstdprot_wt.h"			// IXЭ��(���׵����)����
	#include "prot_ix/ixstdprot_wtstru.h"		// IXЭ��(���׵����)�ṹ����
	// �����ģ������
	#include "addon/tc_common.h"				// TC�ܹ�ͨ�ö���
	#include "addon/tc_femdefine.h"				// TC�ܹ���ԭ��ģʽģ�鶨��
	#include "addon/tc_femdeclare.h"			// TC�ܹ���ԭ��ģʽģ�鶨��

#elif defined(ASE_FOR_ASFHM)
	// ase������
	#include "aselib.h"							// ��������
	#include "asestddef.h"						// ASE��׼����
	// ase������ർ��
	#include "feature/aselibiximplbase.h"		// ASE/IX�������(����)
	#include "feature/aselibiximplv1.h"			// ASE/IX�������(��һ��)
	#include "feature/aselibiximplv2.h"			// ASE/IX�������(�ڶ���)
	// IX�������
	#include "prot_ix/ixstdstru.h"				// IXЭ����ر�׼����
	#include "prot_ix/ixstdprot.h"				// IXЭ���������
	#include "prot_ix/ixstdprot_wt.h"			// IXЭ��(���׵����)����
	#include "prot_ix/ixstdprot_wtstru.h"		// IXЭ��(���׵����)�ṹ����
	// �����ģ������
	#include "addon/as_fhmdefine.h"				// AS�ܹ�ģ�鶨��
	#include "addon/as_fhmdeclare.h"			// AS�ܹ�ģ�鶨��

#elif defined(ASE_FOR_TSMOD)

	// ase������
	#include "aselib.h"							// ��������
	#include "asestddef.h"						// ASE��׼����

	// IX������ർ��
	#if defined(ASE_WITH_IX_CLASS)
		#include "feature/aselibiximplbase.h"	// IX�������(����)
		#include "feature/aselibiximplv1.h"		// IX�������(��һ��)
		#include "feature/aselibiximplv2.h"		// IX�������(�ڶ���)
	#endif

	// IX�ֶ������ö���
	#if defined(ASE_WITH_IX_WEAK)
		#include "prot_ix/ixstdprot.h"			// IXЭ���������
		#include "prot_ix/ixstdprot_wt.h"		// IXЭ��(���׵����)����
	#endif

	// IX�ֶ�ǿ���ö���
	#if defined(ASE_WITH_IX_STRONG)
		#include "prot_ix/ixstdstru.h"			// IXЭ����ر�׼����
	#endif

	// IX����ṹ����
	#if defined(ASE_WITH_IX_CLASS) && defined(ASE_WITH_IX_DEFINE)
		#include "prot_ix/ixstdprot_wtstru.h"	// IXЭ��(���׵����)�ṹ����
	#endif

	// Э��ṹ����
	#if defined(ASE_WITH_PF_DECL)
		#include "prot_raw/asestdprot_header.h"	// ASE��׼Э��ͷ����
	#endif

	// �����ģ������
	#include "addon/ts_define.h"				// TS�ܹ�ԭ��ģʽģ�鶨��







#elif defined(ASE_FOR_V6MAIN)
	// ��������
	#include "asestddef.h"						// ASE��׼����
	// ixЭ������
	#include "prot_ix/ixstdprot.h"				// IXЭ���������
	#include "prot_ix/ixstdprot_wt.h"			// IXЭ��(���׵����)����


#elif defined(ASE_FOR_V6ADDIN)
	// ixЭ������
	#include "prot_ix/ixstdprot.h"				// IXЭ���������
	#include "prot_ix/ixstdprot_wt.h"			// IXЭ��(���׵����)����





#elif defined(ASE_FOR_SELF)
	// ase������
	#include "aselib.h"							// IX����ض���
	#include "asestddef.h"						// ASE��׼����
	// ase������ർ��
	#include "feature/aselibiximplbase.h"		// ASE/IX�������(����)
	#include "feature/aselibiximplv1.h"			// ASE/IX�������(��һ��)
	#include "feature/aselibiximplv2.h"			// ASE/IX�������(�ڶ���)
	// IX�������
	#include "prot_ix/ixstdstru.h"				// IXЭ����ر�׼����
	#include "prot_ix/ixstdprot.h"				// IXЭ���������
	#include "prot_ix/ixstdprot_wt.h"			// IXЭ��(���׵����)����
	#include "prot_ix/ixstdprot_wtstru.h"		// IXЭ��(���׵����)�ṹ����
	// �����ģ������
	#include "addon/tc_common.h"				// TC�ܹ�ͨ�ö���
	#include "addon/tc_femdefine.h"				// TC�ܹ���ԭ��ģʽģ�鶨��
	#include "addon/as_fhmdefine.h"				// AS�ܹ�ģ�鶨��
#else
	#error ASE_FOR_XXX must be defined.
#endif


#if defined(PLATFORM_WINDOWS) && !defined(ASELIB_LIB) && (defined(__ASE_LIB_IX_IMPL_V1__H__)||defined(__ASE_LIB_IX_IMPL_V2__H__))
	#ifndef WTCOMMLIB_NOAUTOLINK
		#if defined(_ARCH_AMD64_)
			// ��̬ģʽ
			#if defined(ASELIB_DYNAMIC)
				#ifdef _DEBUG
					#pragma message("Automatically linking with WTCommLibx64d.dll....")
					#pragma comment(lib,"WTCommLibx64d.lib")
				#else
					#pragma message("Automatically linking with WTCommLibx64.dll....")
					#pragma comment(lib,"WTCommLibx64.lib")
				#endif
			// ��̬ģʽ
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
			// ��̬ģʽ
			#if defined(ASELIB_DYNAMIC)
				#ifdef _DEBUG
					#pragma message("Automatically linking with WTCommLibd.dll....")
					#pragma comment(lib,"WTCommLibd.lib")
				#else
					#pragma message("Automatically linking with WTCommLib.dll....")
					#pragma comment(lib,"WTCommLib.lib")
				#endif
			// ��̬ģʽ
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
