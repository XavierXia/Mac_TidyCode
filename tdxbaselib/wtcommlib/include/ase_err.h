#ifndef __ASE_STDPROT_ERR__H__
#define __ASE_STDPROT_ERR__H__

//////////////////////////////////////////////////////////////////////////
// 有关系统错误处理,系统一共包含四个层面的错误:
//		1.连接拒绝类错误(响应方式: 拒绝连接)
//		2.连接关闭类错误(响应方式: 断开连接)
//		3.事务架构类错误(含非关闭类错误, 响应方式:关闭连接或进行报错处理)
//		4.事务应用类错误(非关闭类错误, 响应方式:进行报错处理)

//////////////////////////////////////////////////////////////////////////
//							架构级错误号								//
//////////////////////////////////////////////////////////////////////////

// 系统错误(共享)
#define SYS_ERR_NONE				(0)
#define SYS_ERR_SUCCESS				(0)
#define SYS_ERR_PENDING				(1)

#define SYS_ERR_BASENO				(-5000)						// 架构类错误
#define SYS_ERR_UNKNOWN				(SYS_ERR_BASENO-0)			// 未知错误
#define SYS_ERR_OS					(SYS_ERR_BASENO-1)			// 系统错误(OS错误)
#define SYS_ERR_NIO					(SYS_ERR_BASENO-2)			// 通讯错误(NET错误)
#define SYS_ERR_BPR					(SYS_ERR_BASENO-3)			// 底层错误(BPR错误)
#define SYS_ERR_QUEUETIMEOUT		(SYS_ERR_BASENO-4)			// 请求排队超时
#define SYS_ERR_LOWRUNLEVEL			(SYS_ERR_BASENO-5)			// 低优先级的请求被抛弃
#define SYS_ERR_QUEUEOVERFLOW		(SYS_ERR_BASENO-6)			// 队列超过最大深度
#define SYS_ERR_ASYNCIOEXCEPT		(SYS_ERR_BASENO-7)			// 异步IO异常
#define SYS_ERR_NOENTRYPOINT		(SYS_ERR_BASENO-8)			// 入口点不存在
#define SYS_ERR_NOBRANCH			(SYS_ERR_BASENO-9)			// 营业部不存在
#define SYS_ERR_INVALIDBRANCH		(SYS_ERR_BASENO-10)			// 无效营业部
#define SYS_ERR_NODEFROZEN			(SYS_ERR_BASENO-11)			// 节点已经被冻结
#define SYS_ERR_CLIENTIP_LOCKD		(SYS_ERR_BASENO-12)			// 客户IP被封锁
#define SYS_ERR_CLIENTMAC_LOCKD		(SYS_ERR_BASENO-13)			// 客户MAC被封锁
#define SYS_ERR_BADCLIENTIP			(SYS_ERR_BASENO-14)			// 请求附加的客户端IP无效
#define SYS_ERR_BADCLIENTMAC		(SYS_ERR_BASENO-15)			// 请求附加的客户端MAC无效
#define SYS_ERR_INVALIDCLITYPE		(SYS_ERR_BASENO-16)			// 请求的客户端类型不正确
#define SYS_ERR_IPORMACLOCKED		(SYS_ERR_BASENO-17)			// 用户的IP或MAC已被锁定
#define SYS_ERR_FEATURENOTSUPPORT	(SYS_ERR_BASENO-18)			// 功能不被支持
#define SYS_ERR_BADOPTBUFFER		(SYS_ERR_BASENO-19)			// 选项缓冲区错误
#define SYS_ERR_BUFFERTOOSMALL		(SYS_ERR_BASENO-20)			// 缓冲区太小
#define SYS_ERR_BADSSLKEY			(SYS_ERR_BASENO-21)			// SSL密钥不正确
#define SYS_ERR_FILENOTFOUND		(SYS_ERR_BASENO-22)			// 文件好不到
#define SYS_ERR_BADTHREADPOOL		(SYS_ERR_BASENO-23)			// 线程池错误

// IX协议错误(共享)
#define IX_ERR_BASENO				(-5050)						// IX协议错误
#define IX_ERR_NOFUNCTYPE			(IX_ERR_BASENO-0)			// 无此功能类型
#define IX_ERR_NOFUNC				(IX_ERR_BASENO-1)			// 无此功能
#define IX_ERR_FUNCDISABLED			(IX_ERR_BASENO-2)			// 当前功能已经关闭,请稍后重试
#define IX_ERR_BOOSTLIMITED			(IX_ERR_BASENO-3)			// 服务器太忙,超过流量限制,请稍后重尝试
#define IX_ERR_FUNCTIMELIMITED		(IX_ERR_BASENO-4)			// 当前功能只在非交易时间开放,请在闭市期间使用
#define IX_ERR_FUNCBOOSTLIMITED		(IX_ERR_BASENO-5)			// 当前功能太多人调用,超过流量限制,请稍后重尝试
#define IX_ERR_FUNCPARALLELLIMITED	(IX_ERR_BASENO-6)			// 并行超过限制
#define IX_ERR_INVALIDDATA			(IX_ERR_BASENO-7)			// 数据包结构性错误
#define IX_ERR_PROCFATAL			(IX_ERR_BASENO-8)			// 事务处理返回异常
#define IX_ERR_NULLRESULT			(IX_ERR_BASENO-9)			// 事务处理返回结果集为空
#define IX_ERR_FUNCNOHANDLER		(IX_ERR_BASENO-10)			// 服务器不提供当前功能
#define IX_ERR_CREATESTRUCT			(IX_ERR_BASENO-11)			// 创建数据字典结构失败
#define IX_ERR_BADREQLENGTH			(IX_ERR_BASENO-12)			// IX请求报文长度不正确
#define IX_ERR_FUNCENTRYINVALID		(IX_ERR_BASENO-13)			// IX模块入口函数无效
#define IX_ERR_FUNCEXCEPTION		(IX_ERR_BASENO-14)			// IX模块入口函数异常
#define IX_ERR_REQOVERFLOW			(IX_ERR_BASENO-15)			// IX请求缓冲区溢出
#define IX_ERR_ANSOVERFLOW			(IX_ERR_BASENO-16)			// IX应答缓冲区溢出
#define IX_ERR_UORGIDINVALID		(IX_ERR_BASENO-17)			// IX分支机构代码错误
#define IX_ERR_FUNCIDINVALID		(IX_ERR_BASENO-18)			// IX功能号错误
#define IX_ERR_CREATEREQSTRUCT		(IX_ERR_BASENO-19)			// 创建请求字典失败
#define IX_ERR_CREATEANSSTRUCT		(IX_ERR_BASENO-20)			// 创建应答字典失败
#define IX_ERR_MODULENOTLOAD		(IX_ERR_BASENO-21)			// 模块未装载
#define IX_ERR_MODULENOTINIT		(IX_ERR_BASENO-22)			// 模块未初始化
#define IX_ERR_MODULEINSIDE			(IX_ERR_BASENO-23)			// 模块内部错误
#define IX_ERR_FRAGMENTFAIL			(IX_ERR_BASENO-24)			// 发送分片失败

// SESSION错误(共享)
#define SESSION_ERR_BASENO			(-5100)						// IX协议错误
#define SESSION_ERR_ALREADYOPEN		(SESSION_ERR_BASENO-0)		// 创建SESSION失败(已经存在)
#define SESSION_ERR_CANNOTNEW		(SESSION_ERR_BASENO-1)		// 创建SESSION失败(无法创建)
#define SESSION_ERR_CANOTOPEN		(SESSION_ERR_BASENO-2)		// 打开SESSION失败
#define SESSION_ERR_EXCHANGEKEY		(SESSION_ERR_BASENO-3)		// 交换密钥错误
#define SESSION_ERR_LOCKDATA		(SESSION_ERR_BASENO-4)		// 锁定SESSION数据失败
#define SESSION_ERR_NOTMATCH		(SESSION_ERR_BASENO-5)		// SESSION失效


// ACL错误(共享)
#define ACL_ERR_BASENO				(-5150)						// ACL相关错误
#define ACL_ERR_HOSTNOTLOGIN		(ACL_ERR_BASENO-0)			// ACL控制,主机未登录
#define ACL_ERR_HOSTDENY			(ACL_ERR_BASENO-1)			// ACL控制,主机拒绝
#define ACL_ERR_USERDENY			(ACL_ERR_BASENO-2)			// ACL控制,用户拒绝


// SEQUEUE错误(共享)
#define SEQUEUE_ERR_BASENO			(-5200)						// SEQUEUE错误
#define SEQUEUE_ERR_READ			(SEQUEUE_ERR_BASENO-1)		// SEQUEUE读取错误
#define SEQUEUE_ERR_WRITE			(SEQUEUE_ERR_BASENO-2)		// SEQUEUE写入错误
#define SEQUEUE_ERR_OVERFLOW		(SEQUEUE_ERR_BASENO-3)		// SEQUEUE溢出









//////////////////////////////////////////////////////////////////////////
//							模块级错误号								//
//////////////////////////////////////////////////////////////////////////

// MEMREPLY错误
#define MEMREPLY_ERR_BASENO			(-7050)						// MEMREPLY错误
#define MEMREPLY_ERR_OVERFLOW		(MEMREPLY_ERR_BASENO-0)		// 内存REPLY缓冲区溢出
#define MEMREPLY_ERR_NOBUF			(MEMREPLY_ERR_BASENO-1)		// 内存REPLY缓冲区不足
#define MEMREPLY_ERR_NOMEM			(MEMREPLY_ERR_BASENO-2)		// 内存REPLY内存不足


// ASYNCREPLY错误
#define ASYNCREPLY_ERR_BASENO		(-7100)						// ASYNCREPLY错误
#define ASYNCREPLY_ERR_FRAGMENTNO	(ASYNCREPLY_ERR_BASENO-0)	// 事务分片号错误
#define ASYNCREPLY_ERR_FRAGMENTSIZE	(ASYNCREPLY_ERR_BASENO-1)	// 事务分片大小错误
#define ASYNCREPLY_ERR_BADHANDLER	(ASYNCREPLY_ERR_BASENO-2)	// 事务处理对象不支持异步接口
#define ASYNCREPLY_ERR_INITBUFFER	(ASYNCREPLY_ERR_BASENO-3)	// 异步事务应答缓冲区初始化错误
#define ASYNCREPLY_ERR_GETBUFFER	(ASYNCREPLY_ERR_BASENO-4)	// 异步事务应答缓冲区获取错误
#define ASYNCREPLY_ERR_SETDATAREADY	(ASYNCREPLY_ERR_BASENO-5)	// 异步事务处理过程设置完成状态错误
#define ASYNCREPLY_ERR_SENDSEGMENT	(ASYNCREPLY_ERR_BASENO-6)	// 异步事务处理过程中处理分片错误


// DTE错误
#define DTE_ERR_BASENO				(-7150)
#define DTE_ERR_ENCRYPTNOTSUPPORT	(DTE_ERR_BASENO-1)			// 加密不被支持
#define DTE_ERR_UNCOMPRESS			(DTE_ERR_BASENO-2)			// 解压失败
#define DTE_ERR_NETWORKFAIL			(DTE_ERR_BASENO-3)			// 通讯异常


// LPC错误
#define LPC_ERR_BASENO				(-7200)						// LPC错误
#define LPC_ERR_EXECUTE				(LPC_ERR_BASENO-0)			// LPC调用错误(抽象错误)
#define LPC_ERR_MODULENOTFOUND		(LPC_ERR_BASENO-1)			// 模块不存在


// PY错误
#define PY_ERR_BASENO				(-7250)						// PY错误
#define PY_ERR_INTERNAL				(PY_ERR_BASENO-0)			// PY执行内部错误
#define PY_ERR_OPTION				(PY_ERR_BASENO-1)			// PY执行参数错误
#define PY_ERR_MEMORY				(PY_ERR_BASENO-2)			// PY执行内存错误
#define PY_ERR_SCRIPT				(PY_ERR_BASENO-3)			// PY脚本错误
#define PY_ERR_METHOD				(PY_ERR_BASENO-4)			// PY方法错误
#define PY_ERR_PYEXCEPTION			(PY_ERR_BASENO-5)			// PY调用脚本异常
#define PY_ERR_RETURN				(PY_ERR_BASENO-6)			// PY调用返回值错误
#define PY_ERR_RESULT				(PY_ERR_BASENO-7)			// PY调用结果错误
#define PY_ERR_CEXCEPTION			(PY_ERR_BASENO-8)			// PY调用发生C++异常
#define PY_ERR_RPCSVCNOTVALID		(PY_ERR_BASENO-9)			// PY调用发生RPC服务状态异常
#define PY_ERR_RPCUSERNULL			(PY_ERR_BASENO-10)			// PY调用发生用户空异常
#define PY_ERR_RPCEXCEPTION			(PY_ERR_BASENO-11)			// PY调用发生RPC异常


// LUA错误
#define LUA_ERR_BASENO				(-7300)						// LUA错误


// MM错误
#define MM_ERR_BASENO				(-7350)						// MM错误
#define MM_ERR_INTERNAL				(MM_ERR_BASENO-0)			// MM执行内部错误
#define MM_ERR_MODULENOTLOAD		(MM_ERR_BASENO-1)			// MM模块未装载
#define MM_ERR_MODULENOTINIT		(MM_ERR_BASENO-2)			// MM模块未初始化
#define MM_ERR_MODULEINSIDE			(MM_ERR_BASENO-3)			// MM模块内部错误

// RPC错误
#define RPC_ERR_BASENO				(-7400)						// RPC错误
#define RPC_ERR_EXECUTE				(RPC_ERR_BASENO-0)			// RPC调用错误(抽象错误)
#define RPC_ERR_NOCLUSTER			(RPC_ERR_BASENO-1)			// RPC簇不存在
#define RPC_ERR_NODTESVC			(RPC_ERR_BASENO-2)			// RPC依赖服务DTE不存在
#define RPC_ERR_NOMEM				(RPC_ERR_BASENO-3)			// RPC内存不足
#define RPC_ERR_NIOREQUEST			(RPC_ERR_BASENO-4)			// RPC网络请求失败
#define RPC_ERR_LOWLEVEL			(RPC_ERR_BASENO-5)			// RPC基础错误
#define RPC_ERR_NOREPLYOBJECT		(RPC_ERR_BASENO-6)			// RPC应答对象不正确
#define RPC_ERR_INITASYNCBUF		(RPC_ERR_BASENO-7)			// RPC初始化异步缓冲区失败
#define RPC_ERR_REMOTEPROCESS		(RPC_ERR_BASENO-8)			// RPC调用时远程主机返回失败
#define RPC_ERR_PAGETOOSMALL		(RPC_ERR_BASENO-9)			// RPC应答太大
#define RPC_ERR_PAGEMISTAKE			(RPC_ERR_BASENO-10)			// RPC页面错误
#define RPC_ERR_PUSHANDREWIND		(RPC_ERR_BASENO-11)			// RPC推送和回退错误
#define RPC_ERR_TIMEOUT				(RPC_ERR_BASENO-12)			// RPC超时
#define RPC_ERR_HUGERECURSIVE		(RPC_ERR_BASENO-13)			// RPC路由层次太深
#define RPC_ERR_NODOMAIN			(RPC_ERR_BASENO-14)			// RPC域不存在
#define RPC_ERR_NOROUTE				(RPC_ERR_BASENO-15)			// RPC域中不存在匹配的路由
#define RPC_ERR_NOLPCHOST			(RPC_ERR_BASENO-16)			// RPC调用(域)指向本地调用,但本地调用服务不可用
#define RPC_ERR_NOBUFFER			(RPC_ERR_BASENO-17)			// RPC调用数据区不足
#define RPC_ERR_BADCALLTYPE			(RPC_ERR_BASENO-18)			// RPC调用类型不被目标主站支持
#define RPC_ERR_BADHOSTTYPE			(RPC_ERR_BASENO-19)			// RPC调用类型不被目标主站支持
#define RPC_ERR_UNSUPPORT			(RPC_ERR_BASENO-20)			// RPC不支持指定主站类型的调用
#define RPC_ERR_BADUSERDESC			(RPC_ERR_BASENO-21)			// RPC请求用户描述错误
#define RPC_ERR_BADREQUEST			(RPC_ERR_BASENO-22)			// RPC请求数据错误
#define RPC_ERR_NOROUTEINFO			(RPC_ERR_BASENO-23)			// RPC检索功能路由信息失败
#define RPC_ERR_BADSERVID			(RPC_ERR_BASENO-24)			// RPC服务器ID不正确
#define RPC_ERR_NOPRIVATEBRIDGE		(RPC_ERR_BASENO-25)			// RPC私有桥不存在
#define RPC_ERR_REGARPC				(RPC_ERR_BASENO-26)			// ARPC注册失败
#define RPC_ERR_NOARPCSERV			(RPC_ERR_BASENO-27)			// ARPC服务器不可用或繁忙
#define RPC_ERR_NOARPCSLOT			(RPC_ERR_BASENO-28)			// ARPC服务槽不可用或繁忙









//////////////////////////////////////////////////////////////////////////
//							架构级错误号								//
//////////////////////////////////////////////////////////////////////////

// 监控类错误
#define SAM_ERR_BASENO				(-9000)						// 监控类错误
#define SAM_ERR_USERMISSING			(SAM_ERR_BASENO-0)			// 管理用户不存在
#define SAM_ERR_INVALIDUSER			(SAM_ERR_BASENO-1)			// 管理用户名无效
#define SAM_ERR_INVALIDPASSWORD		(SAM_ERR_BASENO-2)			// 管理用户密码无效
#define SAM_ERR_REQUESTDENIED		(SAM_ERR_BASENO-3)			// 用户不具备对应权限
#define SAM_ERR_DIRPATHINVALID		(SAM_ERR_BASENO-4)			// 目录路径无效
#define SAM_ERR_CANNOTMKDIR			(SAM_ERR_BASENO-5)			// 不能创建目录
#define SAM_ERR_CANNOTRMDIR			(SAM_ERR_BASENO-6)			// 不能删除目录
#define SAM_ERR_FILEPATHINVALID		(SAM_ERR_BASENO-7)			// 文件路径无效
#define SAM_ERR_FILEOPENFAILED		(SAM_ERR_BASENO-8)			// 文件打开失败
#define SAM_ERR_FILESEEKFAILED		(SAM_ERR_BASENO-9)			// 移动文件指针失败

// T2EE服务器错误(含子架构)
#define T2EE_ERR_BASENO				(-9050)						// T2EE服务器错误
#define T2EE_ERR_NOROUTEINFO		(T2EE_ERR_BASENO-0)			// 检索功能路由信息失败
#define T2EE_ERR_BADREQUEST			(T2EE_ERR_BASENO-1)			// 请求结构错误
#define T2EE_ERR_NOROUTING			(T2EE_ERR_BASENO-2)			// 找不到路由


// 交易中心(含子架构)错误号
#define TC_ERR_BASENO				(-10000)					// 交易中心(含子架构)错误
#define TC_ERR_REDIRECTFAIL			(TC_ERR_BASENO-0)			// 数据在转发过程中失败
#define TC_ERR_VERSIONDISCARD		(TC_ERR_BASENO-1)			// 客户端使用的版本过低,已经被拒绝登录,请通过网站升级
#define TC_ERR_USERNOTLOGIN			(TC_ERR_BASENO-2)			// 客户未登录
#define TC_ERR_DICTINVALID			(TC_ERR_BASENO-3)			// 服务器字典不可用
#define TC_ERR_INVALIDQSID			(TC_ERR_BASENO-4)			// 券商标识不正确
#define TC_ERR_INVALIDPID			(TC_ERR_BASENO-5)			// 产品标识不正确
#define TC_ERR_DICTNOTEXIST			(TC_ERR_BASENO-6)			// 数据字典不存在
#define TC_ERR_NULLPID				(TC_ERR_BASENO-7)			// 产品ID或者券商ID为空
#define TC_ERR_NOSIGNATURE			(TC_ERR_BASENO-8)			// 客户端未送入证书签名
#define TC_ERR_BADSIGNATURE			(TC_ERR_BASENO-9)			// 证书签名不正确
#define TC_ERR_BUFNOTENOUGH			(TC_ERR_BASENO-10)			// 缓冲区不足(应答包太大)
#define TC_ERR_KICKOUTBYOTHER		(TC_ERR_BASENO-11)			// 用户连接已经被踢出
#define TC_ERR_NOROUTE				(TC_ERR_BASENO-12)			// 没有可用路由
#define TC_ERR_BUSYROUTE			(TC_ERR_BASENO-13)			// 路由繁忙或者路由断开
#define TC_ERR_TRADECCFTOOLARGE		(TC_ERR_BASENO-14)			// TRADECCF太大

// 业务集成平台(含子架构)错误号
#define AS_ERR_BASENO				(-10500)					// 业务集成平台(含子架构)相关协议
#define AS_ERR_NOSTORAGEAREA		(AS_ERR_BASENO-0)			// 存储区域不存在
#define AS_ERR_NOMODULE				(AS_ERR_BASENO-1)			// 不存在指定类型的功能模块
#define AS_ERR_BADMODULE			(AS_ERR_BASENO-2)			// 功能模块无效


// 移动网关(含子架构)错误号
#define MP_ERR_BASENO				(-12000)					// 基本移动接入网关错误
#define MP_ERR_NORPCHOST			(MP_ERR_BASENO-0)			// 向三方主站转发数据失败
#define MP_ERR_ASYNCANSTOOLARGE		(MP_ERR_BASENO-1)			// 异步应答缓冲太大
#define MP_ERR_DATATOOLARGE			(MP_ERR_BASENO-2)			// 应答数据太大
#define MP_ERR_CANNOTREAD			(MP_ERR_BASENO-3)			// 读取文件失败
#define MP_ERR_EXECUTESQL			(MP_ERR_BASENO-4)			// 执行SQL调用错误
#define MP_ERR_MMNOTSUPPORT			(MP_ERR_BASENO-5)			// 调用不支持MM功能
#define MP_ERR_NOROUTEINFO			(MP_ERR_BASENO-6)			// 检索功能路由信息失败

// 柜台错误号
#define GT_ERR_BASENO				(-100000)					// 柜台错误号
//#include "ASE_Err_GT.h"




















//////////////////////////////////////////////////////////////////////////
// 兼容错误号(这些错误号已经改名,物理含义已发生变更)
#define ERR_NOTDXBRANCH				SYS_ERR_NOENTRYPOINT
#define ERR_NOREALBRANCH			SYS_ERR_NOBRANCH
#define ERR_BUSYROUTE				TC_ERR_BUSYROUTE

#endif

