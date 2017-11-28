//////////////////////////////////////////////////////////////////////////
// 创建日期:2006/07/20
// 功能说明:委托通用处理类
//          TC50数据字典格式兼容老版本数据字典格式
//			通达信二次开发的设计原理
//				I.按照功能内容可划分为: a.业务型功能 b.辅助性功能
//				II.按照客户端交互模式可划分为:
//					a.标准功能STM(入口参数固定,返回不固定)
//					b.智能查询ITQ(入口参数通过配置指定,返回不固定)
//					c.插件功能TPM(入口参数不固定,返回不固定)
//				III.按照服务器端实现
//					a.功能执行模块<FEM>(可重载任意请求并新增请求), 应用:交易中心
//					b.功能执行桥模块<FEB>(可重载任意请求并新增请求), 应用:交易中心(暂不支持)
//					c.功能处理模块<FHM>(可重载任意请求并新增请求), 应用:安全中心,用户中心,消息中心,服务中心
//					d.功能处理桥模块<FHB>(可重载任意请求并新增请求), 应用:安全中心,用户中心,消息中心,服务中心(暂不支持)
//			业务模块设计的准则
//				I.  标准功能,相同的请求字典必须一致,严格禁止请求字典变化和重载
//				II. 标准功能,应答字典可重载,请求字段不允许重载,但允许加入缓存字段
//				III.智能查询功能,不允许跨模块使用(机构版中存在问题,功能树需要根据字典调整)
//				IV. 插件功能,不允许跨模块使用(机构版中存在问题,功能树需要按照插件调整)
//				V.  任意功能,如果某些柜台接口需要送入特殊参数,那么必须单独开辟功能ID,严格禁止复用功能ID
//				VI. 如果某些柜台接口需要返回特殊字段,那么可以采用复用功能ID的方式,也可以单独开辟功能ID
//					建议采用开辟单独的功能ID,这样最少可以保证功能的唯一性

// 变更记录:
//            2006/07/25 对服务器端加入头文件引用
//            2008/08/12 增加安全中心,用户中心,消息中心,服务中心的处理模块
//            2010/03/16 由原WTCOMMLIB库扩充为ASE库,支持更广泛的事务
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

// 接口导出
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

// 接口导出
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

// 移植到VS2005(W4选项下禁止使用旧的CRT库)
#ifdef WIN32
#pragma warning(disable:4996)
#endif

#endif
