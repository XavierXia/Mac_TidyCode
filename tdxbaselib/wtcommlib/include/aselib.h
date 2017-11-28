//////////////////////////////////////////////////////////////////////////
// ��������:2006/07/20
// ����˵��:ί��ͨ�ô�����
//          TC50�����ֵ��ʽ�����ϰ汾�����ֵ��ʽ
//			ͨ���Ŷ��ο��������ԭ��
//				I.���չ������ݿɻ���Ϊ: a.ҵ���͹��� b.�����Թ���
//				II.���տͻ��˽���ģʽ�ɻ���Ϊ:
//					a.��׼����STM(��ڲ����̶�,���ز��̶�)
//					b.���ܲ�ѯITQ(��ڲ���ͨ������ָ��,���ز��̶�)
//					c.�������TPM(��ڲ������̶�,���ز��̶�)
//				III.���շ�������ʵ��
//					a.����ִ��ģ��<FEM>(����������������������), Ӧ��:��������
//					b.����ִ����ģ��<FEB>(����������������������), Ӧ��:��������(�ݲ�֧��)
//					c.���ܴ���ģ��<FHM>(����������������������), Ӧ��:��ȫ����,�û�����,��Ϣ����,��������
//					d.���ܴ�����ģ��<FHB>(����������������������), Ӧ��:��ȫ����,�û�����,��Ϣ����,��������(�ݲ�֧��)
//			ҵ��ģ����Ƶ�׼��
//				I.  ��׼����,��ͬ�������ֵ����һ��,�ϸ��ֹ�����ֵ�仯������
//				II. ��׼����,Ӧ���ֵ������,�����ֶβ���������,��������뻺���ֶ�
//				III.���ܲ�ѯ����,�������ģ��ʹ��(�������д�������,��������Ҫ�����ֵ����)
//				IV. �������,�������ģ��ʹ��(�������д�������,��������Ҫ���ղ������)
//				V.  ���⹦��,���ĳЩ��̨�ӿ���Ҫ�����������,��ô���뵥�����ٹ���ID,�ϸ��ֹ���ù���ID
//				VI. ���ĳЩ��̨�ӿ���Ҫ���������ֶ�,��ô���Բ��ø��ù���ID�ķ�ʽ,Ҳ���Ե������ٹ���ID
//					������ÿ��ٵ����Ĺ���ID,�������ٿ��Ա�֤���ܵ�Ψһ��

// �����¼:
//            2006/07/25 �Է������˼���ͷ�ļ�����
//            2008/08/12 ���Ӱ�ȫ����,�û�����,��Ϣ����,�������ĵĴ���ģ��
//            2010/03/16 ��ԭWTCOMMLIB������ΪASE��,֧�ָ��㷺������
#ifndef __ASE_LIB__H__
#define __ASE_LIB__H__
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#if defined(WIN32)
	#define PLATFORM_WINDOWS
	#if defined(_WIN64)
		#define _ARCH_AMD64_
	#else
		#define _ARCH_IA32_
	#endif
	#define _COMPILE_BY_MSC_
#endif
#if defined(LINUX)
	#define PLATFORM_LINUX
	#if defined(LINUX64)
		#define _ARCH_AMD64_
	#else
		#define _ARCH_IA32_
	#endif
	#define _COMPILE_BY_GCC_
#endif
#if defined(UNIX)
	#define PLATFORM_UNIX
	#if defined(UNIX64)
		#define _ARCH_AMD64_
	#else
		#define _ARCH_IA32_
	#endif
	#define _COMPILE_BY_GCC_
#endif
#if defined(MACOSX)
	#define PLATFORM_MACOSX
	#if defined(MACOSX64)
		#define _ARCH_AMD64_
	#else
		#define _ARCH_IA32_
	#endif
	#define _COMPILE_BY_GCC_
#endif

#if defined(IOS)
	#define PLATFORM_IOS
	#if defined(USE_SIMULATOR)
		#define _ARCH_IA32_
	#else
		#define _ARCH_ARM_
	#endif
	#define _COMPILE_BY_GCC_
#endif
#if defined(ANDROID)
	#define PLATFORM_ANDROID
	#define _ARCH_ARM_
	#define _COMPILE_BY_GCC_
#endif

// �ӿڵ���
#if !defined(DLLEXPORT)
	#ifdef PLATFORM_WINDOWS
		#define DLLEXPORT __declspec(dllexport)
		#define DLLIMPORT __declspec(dllimport)
		#define LIBEXPORT
		#define LIBIMPORT
	#else
		#define DLLEXPORT
		#define DLLIMPORT
		#define LIBEXPORT
		#define LIBIMPORT
	#endif
#endif

// �ӿڵ���
#ifndef ASELIB_DYNAMIC
	#ifdef ASELIB_LIB
		#define ASELIB_API LIBEXPORT
	#else
		#define ASELIB_API LIBIMPORT
	#endif
#else
	#ifdef ASELIB_LIB
		#define ASELIB_API DLLEXPORT
	#else
		#define ASELIB_API DLLIMPORT
	#endif
#endif

// ��ֲ��VS2005(W4ѡ���½�ֹʹ�þɵ�CRT��)
#ifdef WIN32
#pragma warning(disable:4996)
#endif

#endif
