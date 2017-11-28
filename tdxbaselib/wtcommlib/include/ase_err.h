#ifndef __ASE_STDPROT_ERR__H__
#define __ASE_STDPROT_ERR__H__

//////////////////////////////////////////////////////////////////////////
// �й�ϵͳ������,ϵͳһ�������ĸ�����Ĵ���:
//		1.���Ӿܾ������(��Ӧ��ʽ: �ܾ�����)
//		2.���ӹر������(��Ӧ��ʽ: �Ͽ�����)
//		3.����ܹ������(���ǹر������, ��Ӧ��ʽ:�ر����ӻ���б�����)
//		4.����Ӧ�������(�ǹر������, ��Ӧ��ʽ:���б�����)

//////////////////////////////////////////////////////////////////////////
//							�ܹ��������								//
//////////////////////////////////////////////////////////////////////////

// ϵͳ����(����)
#define SYS_ERR_NONE				(0)
#define SYS_ERR_SUCCESS				(0)
#define SYS_ERR_PENDING				(1)

#define SYS_ERR_BASENO				(-5000)						// �ܹ������
#define SYS_ERR_UNKNOWN				(SYS_ERR_BASENO-0)			// δ֪����
#define SYS_ERR_OS					(SYS_ERR_BASENO-1)			// ϵͳ����(OS����)
#define SYS_ERR_NIO					(SYS_ERR_BASENO-2)			// ͨѶ����(NET����)
#define SYS_ERR_BPR					(SYS_ERR_BASENO-3)			// �ײ����(BPR����)
#define SYS_ERR_QUEUETIMEOUT		(SYS_ERR_BASENO-4)			// �����Ŷӳ�ʱ
#define SYS_ERR_LOWRUNLEVEL			(SYS_ERR_BASENO-5)			// �����ȼ�����������
#define SYS_ERR_QUEUEOVERFLOW		(SYS_ERR_BASENO-6)			// ���г���������
#define SYS_ERR_ASYNCIOEXCEPT		(SYS_ERR_BASENO-7)			// �첽IO�쳣
#define SYS_ERR_NOENTRYPOINT		(SYS_ERR_BASENO-8)			// ��ڵ㲻����
#define SYS_ERR_NOBRANCH			(SYS_ERR_BASENO-9)			// Ӫҵ��������
#define SYS_ERR_INVALIDBRANCH		(SYS_ERR_BASENO-10)			// ��ЧӪҵ��
#define SYS_ERR_NODEFROZEN			(SYS_ERR_BASENO-11)			// �ڵ��Ѿ�������
#define SYS_ERR_CLIENTIP_LOCKD		(SYS_ERR_BASENO-12)			// �ͻ�IP������
#define SYS_ERR_CLIENTMAC_LOCKD		(SYS_ERR_BASENO-13)			// �ͻ�MAC������
#define SYS_ERR_BADCLIENTIP			(SYS_ERR_BASENO-14)			// ���󸽼ӵĿͻ���IP��Ч
#define SYS_ERR_BADCLIENTMAC		(SYS_ERR_BASENO-15)			// ���󸽼ӵĿͻ���MAC��Ч
#define SYS_ERR_INVALIDCLITYPE		(SYS_ERR_BASENO-16)			// ����Ŀͻ������Ͳ���ȷ
#define SYS_ERR_IPORMACLOCKED		(SYS_ERR_BASENO-17)			// �û���IP��MAC�ѱ�����
#define SYS_ERR_FEATURENOTSUPPORT	(SYS_ERR_BASENO-18)			// ���ܲ���֧��
#define SYS_ERR_BADOPTBUFFER		(SYS_ERR_BASENO-19)			// ѡ���������
#define SYS_ERR_BUFFERTOOSMALL		(SYS_ERR_BASENO-20)			// ������̫С
#define SYS_ERR_BADSSLKEY			(SYS_ERR_BASENO-21)			// SSL��Կ����ȷ
#define SYS_ERR_FILENOTFOUND		(SYS_ERR_BASENO-22)			// �ļ��ò���
#define SYS_ERR_BADTHREADPOOL		(SYS_ERR_BASENO-23)			// �̳߳ش���

// IXЭ�����(����)
#define IX_ERR_BASENO				(-5050)						// IXЭ�����
#define IX_ERR_NOFUNCTYPE			(IX_ERR_BASENO-0)			// �޴˹�������
#define IX_ERR_NOFUNC				(IX_ERR_BASENO-1)			// �޴˹���
#define IX_ERR_FUNCDISABLED			(IX_ERR_BASENO-2)			// ��ǰ�����Ѿ��ر�,���Ժ�����
#define IX_ERR_BOOSTLIMITED			(IX_ERR_BASENO-3)			// ������̫æ,������������,���Ժ��س���
#define IX_ERR_FUNCTIMELIMITED		(IX_ERR_BASENO-4)			// ��ǰ����ֻ�ڷǽ���ʱ�俪��,���ڱ����ڼ�ʹ��
#define IX_ERR_FUNCBOOSTLIMITED		(IX_ERR_BASENO-5)			// ��ǰ����̫���˵���,������������,���Ժ��س���
#define IX_ERR_FUNCPARALLELLIMITED	(IX_ERR_BASENO-6)			// ���г�������
#define IX_ERR_INVALIDDATA			(IX_ERR_BASENO-7)			// ���ݰ��ṹ�Դ���
#define IX_ERR_PROCFATAL			(IX_ERR_BASENO-8)			// ���������쳣
#define IX_ERR_NULLRESULT			(IX_ERR_BASENO-9)			// �������ؽ����Ϊ��
#define IX_ERR_FUNCNOHANDLER		(IX_ERR_BASENO-10)			// ���������ṩ��ǰ����
#define IX_ERR_CREATESTRUCT			(IX_ERR_BASENO-11)			// ���������ֵ�ṹʧ��
#define IX_ERR_BADREQLENGTH			(IX_ERR_BASENO-12)			// IX�����ĳ��Ȳ���ȷ
#define IX_ERR_FUNCENTRYINVALID		(IX_ERR_BASENO-13)			// IXģ����ں�����Ч
#define IX_ERR_FUNCEXCEPTION		(IX_ERR_BASENO-14)			// IXģ����ں����쳣
#define IX_ERR_REQOVERFLOW			(IX_ERR_BASENO-15)			// IX���󻺳������
#define IX_ERR_ANSOVERFLOW			(IX_ERR_BASENO-16)			// IXӦ�𻺳������
#define IX_ERR_UORGIDINVALID		(IX_ERR_BASENO-17)			// IX��֧�����������
#define IX_ERR_FUNCIDINVALID		(IX_ERR_BASENO-18)			// IX���ܺŴ���
#define IX_ERR_CREATEREQSTRUCT		(IX_ERR_BASENO-19)			// ���������ֵ�ʧ��
#define IX_ERR_CREATEANSSTRUCT		(IX_ERR_BASENO-20)			// ����Ӧ���ֵ�ʧ��
#define IX_ERR_MODULENOTLOAD		(IX_ERR_BASENO-21)			// ģ��δװ��
#define IX_ERR_MODULENOTINIT		(IX_ERR_BASENO-22)			// ģ��δ��ʼ��
#define IX_ERR_MODULEINSIDE			(IX_ERR_BASENO-23)			// ģ���ڲ�����
#define IX_ERR_FRAGMENTFAIL			(IX_ERR_BASENO-24)			// ���ͷ�Ƭʧ��

// SESSION����(����)
#define SESSION_ERR_BASENO			(-5100)						// IXЭ�����
#define SESSION_ERR_ALREADYOPEN		(SESSION_ERR_BASENO-0)		// ����SESSIONʧ��(�Ѿ�����)
#define SESSION_ERR_CANNOTNEW		(SESSION_ERR_BASENO-1)		// ����SESSIONʧ��(�޷�����)
#define SESSION_ERR_CANOTOPEN		(SESSION_ERR_BASENO-2)		// ��SESSIONʧ��
#define SESSION_ERR_EXCHANGEKEY		(SESSION_ERR_BASENO-3)		// ������Կ����
#define SESSION_ERR_LOCKDATA		(SESSION_ERR_BASENO-4)		// ����SESSION����ʧ��
#define SESSION_ERR_NOTMATCH		(SESSION_ERR_BASENO-5)		// SESSIONʧЧ


// ACL����(����)
#define ACL_ERR_BASENO				(-5150)						// ACL��ش���
#define ACL_ERR_HOSTNOTLOGIN		(ACL_ERR_BASENO-0)			// ACL����,����δ��¼
#define ACL_ERR_HOSTDENY			(ACL_ERR_BASENO-1)			// ACL����,�����ܾ�
#define ACL_ERR_USERDENY			(ACL_ERR_BASENO-2)			// ACL����,�û��ܾ�


// SEQUEUE����(����)
#define SEQUEUE_ERR_BASENO			(-5200)						// SEQUEUE����
#define SEQUEUE_ERR_READ			(SEQUEUE_ERR_BASENO-1)		// SEQUEUE��ȡ����
#define SEQUEUE_ERR_WRITE			(SEQUEUE_ERR_BASENO-2)		// SEQUEUEд�����
#define SEQUEUE_ERR_OVERFLOW		(SEQUEUE_ERR_BASENO-3)		// SEQUEUE���









//////////////////////////////////////////////////////////////////////////
//							ģ�鼶�����								//
//////////////////////////////////////////////////////////////////////////

// MEMREPLY����
#define MEMREPLY_ERR_BASENO			(-7050)						// MEMREPLY����
#define MEMREPLY_ERR_OVERFLOW		(MEMREPLY_ERR_BASENO-0)		// �ڴ�REPLY���������
#define MEMREPLY_ERR_NOBUF			(MEMREPLY_ERR_BASENO-1)		// �ڴ�REPLY����������
#define MEMREPLY_ERR_NOMEM			(MEMREPLY_ERR_BASENO-2)		// �ڴ�REPLY�ڴ治��


// ASYNCREPLY����
#define ASYNCREPLY_ERR_BASENO		(-7100)						// ASYNCREPLY����
#define ASYNCREPLY_ERR_FRAGMENTNO	(ASYNCREPLY_ERR_BASENO-0)	// �����Ƭ�Ŵ���
#define ASYNCREPLY_ERR_FRAGMENTSIZE	(ASYNCREPLY_ERR_BASENO-1)	// �����Ƭ��С����
#define ASYNCREPLY_ERR_BADHANDLER	(ASYNCREPLY_ERR_BASENO-2)	// ���������֧���첽�ӿ�
#define ASYNCREPLY_ERR_INITBUFFER	(ASYNCREPLY_ERR_BASENO-3)	// �첽����Ӧ�𻺳�����ʼ������
#define ASYNCREPLY_ERR_GETBUFFER	(ASYNCREPLY_ERR_BASENO-4)	// �첽����Ӧ�𻺳�����ȡ����
#define ASYNCREPLY_ERR_SETDATAREADY	(ASYNCREPLY_ERR_BASENO-5)	// �첽����������������״̬����
#define ASYNCREPLY_ERR_SENDSEGMENT	(ASYNCREPLY_ERR_BASENO-6)	// �첽����������д����Ƭ����


// DTE����
#define DTE_ERR_BASENO				(-7150)
#define DTE_ERR_ENCRYPTNOTSUPPORT	(DTE_ERR_BASENO-1)			// ���ܲ���֧��
#define DTE_ERR_UNCOMPRESS			(DTE_ERR_BASENO-2)			// ��ѹʧ��
#define DTE_ERR_NETWORKFAIL			(DTE_ERR_BASENO-3)			// ͨѶ�쳣


// LPC����
#define LPC_ERR_BASENO				(-7200)						// LPC����
#define LPC_ERR_EXECUTE				(LPC_ERR_BASENO-0)			// LPC���ô���(�������)
#define LPC_ERR_MODULENOTFOUND		(LPC_ERR_BASENO-1)			// ģ�鲻����


// PY����
#define PY_ERR_BASENO				(-7250)						// PY����
#define PY_ERR_INTERNAL				(PY_ERR_BASENO-0)			// PYִ���ڲ�����
#define PY_ERR_OPTION				(PY_ERR_BASENO-1)			// PYִ�в�������
#define PY_ERR_MEMORY				(PY_ERR_BASENO-2)			// PYִ���ڴ����
#define PY_ERR_SCRIPT				(PY_ERR_BASENO-3)			// PY�ű�����
#define PY_ERR_METHOD				(PY_ERR_BASENO-4)			// PY��������
#define PY_ERR_PYEXCEPTION			(PY_ERR_BASENO-5)			// PY���ýű��쳣
#define PY_ERR_RETURN				(PY_ERR_BASENO-6)			// PY���÷���ֵ����
#define PY_ERR_RESULT				(PY_ERR_BASENO-7)			// PY���ý������
#define PY_ERR_CEXCEPTION			(PY_ERR_BASENO-8)			// PY���÷���C++�쳣
#define PY_ERR_RPCSVCNOTVALID		(PY_ERR_BASENO-9)			// PY���÷���RPC����״̬�쳣
#define PY_ERR_RPCUSERNULL			(PY_ERR_BASENO-10)			// PY���÷����û����쳣
#define PY_ERR_RPCEXCEPTION			(PY_ERR_BASENO-11)			// PY���÷���RPC�쳣


// LUA����
#define LUA_ERR_BASENO				(-7300)						// LUA����


// MM����
#define MM_ERR_BASENO				(-7350)						// MM����
#define MM_ERR_INTERNAL				(MM_ERR_BASENO-0)			// MMִ���ڲ�����
#define MM_ERR_MODULENOTLOAD		(MM_ERR_BASENO-1)			// MMģ��δװ��
#define MM_ERR_MODULENOTINIT		(MM_ERR_BASENO-2)			// MMģ��δ��ʼ��
#define MM_ERR_MODULEINSIDE			(MM_ERR_BASENO-3)			// MMģ���ڲ�����

// RPC����
#define RPC_ERR_BASENO				(-7400)						// RPC����
#define RPC_ERR_EXECUTE				(RPC_ERR_BASENO-0)			// RPC���ô���(�������)
#define RPC_ERR_NOCLUSTER			(RPC_ERR_BASENO-1)			// RPC�ز�����
#define RPC_ERR_NODTESVC			(RPC_ERR_BASENO-2)			// RPC��������DTE������
#define RPC_ERR_NOMEM				(RPC_ERR_BASENO-3)			// RPC�ڴ治��
#define RPC_ERR_NIOREQUEST			(RPC_ERR_BASENO-4)			// RPC��������ʧ��
#define RPC_ERR_LOWLEVEL			(RPC_ERR_BASENO-5)			// RPC��������
#define RPC_ERR_NOREPLYOBJECT		(RPC_ERR_BASENO-6)			// RPCӦ�������ȷ
#define RPC_ERR_INITASYNCBUF		(RPC_ERR_BASENO-7)			// RPC��ʼ���첽������ʧ��
#define RPC_ERR_REMOTEPROCESS		(RPC_ERR_BASENO-8)			// RPC����ʱԶ����������ʧ��
#define RPC_ERR_PAGETOOSMALL		(RPC_ERR_BASENO-9)			// RPCӦ��̫��
#define RPC_ERR_PAGEMISTAKE			(RPC_ERR_BASENO-10)			// RPCҳ�����
#define RPC_ERR_PUSHANDREWIND		(RPC_ERR_BASENO-11)			// RPC���ͺͻ��˴���
#define RPC_ERR_TIMEOUT				(RPC_ERR_BASENO-12)			// RPC��ʱ
#define RPC_ERR_HUGERECURSIVE		(RPC_ERR_BASENO-13)			// RPC·�ɲ��̫��
#define RPC_ERR_NODOMAIN			(RPC_ERR_BASENO-14)			// RPC�򲻴���
#define RPC_ERR_NOROUTE				(RPC_ERR_BASENO-15)			// RPC���в�����ƥ���·��
#define RPC_ERR_NOLPCHOST			(RPC_ERR_BASENO-16)			// RPC����(��)ָ�򱾵ص���,�����ص��÷��񲻿���
#define RPC_ERR_NOBUFFER			(RPC_ERR_BASENO-17)			// RPC��������������
#define RPC_ERR_BADCALLTYPE			(RPC_ERR_BASENO-18)			// RPC�������Ͳ���Ŀ����վ֧��
#define RPC_ERR_BADHOSTTYPE			(RPC_ERR_BASENO-19)			// RPC�������Ͳ���Ŀ����վ֧��
#define RPC_ERR_UNSUPPORT			(RPC_ERR_BASENO-20)			// RPC��֧��ָ����վ���͵ĵ���
#define RPC_ERR_BADUSERDESC			(RPC_ERR_BASENO-21)			// RPC�����û���������
#define RPC_ERR_BADREQUEST			(RPC_ERR_BASENO-22)			// RPC�������ݴ���
#define RPC_ERR_NOROUTEINFO			(RPC_ERR_BASENO-23)			// RPC��������·����Ϣʧ��
#define RPC_ERR_BADSERVID			(RPC_ERR_BASENO-24)			// RPC������ID����ȷ
#define RPC_ERR_NOPRIVATEBRIDGE		(RPC_ERR_BASENO-25)			// RPC˽���Ų�����
#define RPC_ERR_REGARPC				(RPC_ERR_BASENO-26)			// ARPCע��ʧ��
#define RPC_ERR_NOARPCSERV			(RPC_ERR_BASENO-27)			// ARPC�����������û�æ
#define RPC_ERR_NOARPCSLOT			(RPC_ERR_BASENO-28)			// ARPC����۲����û�æ









//////////////////////////////////////////////////////////////////////////
//							�ܹ��������								//
//////////////////////////////////////////////////////////////////////////

// ��������
#define SAM_ERR_BASENO				(-9000)						// ��������
#define SAM_ERR_USERMISSING			(SAM_ERR_BASENO-0)			// �����û�������
#define SAM_ERR_INVALIDUSER			(SAM_ERR_BASENO-1)			// �����û�����Ч
#define SAM_ERR_INVALIDPASSWORD		(SAM_ERR_BASENO-2)			// �����û�������Ч
#define SAM_ERR_REQUESTDENIED		(SAM_ERR_BASENO-3)			// �û����߱���ӦȨ��
#define SAM_ERR_DIRPATHINVALID		(SAM_ERR_BASENO-4)			// Ŀ¼·����Ч
#define SAM_ERR_CANNOTMKDIR			(SAM_ERR_BASENO-5)			// ���ܴ���Ŀ¼
#define SAM_ERR_CANNOTRMDIR			(SAM_ERR_BASENO-6)			// ����ɾ��Ŀ¼
#define SAM_ERR_FILEPATHINVALID		(SAM_ERR_BASENO-7)			// �ļ�·����Ч
#define SAM_ERR_FILEOPENFAILED		(SAM_ERR_BASENO-8)			// �ļ���ʧ��
#define SAM_ERR_FILESEEKFAILED		(SAM_ERR_BASENO-9)			// �ƶ��ļ�ָ��ʧ��

// T2EE����������(���Ӽܹ�)
#define T2EE_ERR_BASENO				(-9050)						// T2EE����������
#define T2EE_ERR_NOROUTEINFO		(T2EE_ERR_BASENO-0)			// ��������·����Ϣʧ��
#define T2EE_ERR_BADREQUEST			(T2EE_ERR_BASENO-1)			// ����ṹ����
#define T2EE_ERR_NOROUTING			(T2EE_ERR_BASENO-2)			// �Ҳ���·��


// ��������(���Ӽܹ�)�����
#define TC_ERR_BASENO				(-10000)					// ��������(���Ӽܹ�)����
#define TC_ERR_REDIRECTFAIL			(TC_ERR_BASENO-0)			// ������ת��������ʧ��
#define TC_ERR_VERSIONDISCARD		(TC_ERR_BASENO-1)			// �ͻ���ʹ�õİ汾����,�Ѿ����ܾ���¼,��ͨ����վ����
#define TC_ERR_USERNOTLOGIN			(TC_ERR_BASENO-2)			// �ͻ�δ��¼
#define TC_ERR_DICTINVALID			(TC_ERR_BASENO-3)			// �������ֵ䲻����
#define TC_ERR_INVALIDQSID			(TC_ERR_BASENO-4)			// ȯ�̱�ʶ����ȷ
#define TC_ERR_INVALIDPID			(TC_ERR_BASENO-5)			// ��Ʒ��ʶ����ȷ
#define TC_ERR_DICTNOTEXIST			(TC_ERR_BASENO-6)			// �����ֵ䲻����
#define TC_ERR_NULLPID				(TC_ERR_BASENO-7)			// ��ƷID����ȯ��IDΪ��
#define TC_ERR_NOSIGNATURE			(TC_ERR_BASENO-8)			// �ͻ���δ����֤��ǩ��
#define TC_ERR_BADSIGNATURE			(TC_ERR_BASENO-9)			// ֤��ǩ������ȷ
#define TC_ERR_BUFNOTENOUGH			(TC_ERR_BASENO-10)			// ����������(Ӧ���̫��)
#define TC_ERR_KICKOUTBYOTHER		(TC_ERR_BASENO-11)			// �û������Ѿ����߳�
#define TC_ERR_NOROUTE				(TC_ERR_BASENO-12)			// û�п���·��
#define TC_ERR_BUSYROUTE			(TC_ERR_BASENO-13)			// ·�ɷ�æ����·�ɶϿ�
#define TC_ERR_TRADECCFTOOLARGE		(TC_ERR_BASENO-14)			// TRADECCF̫��

// ҵ�񼯳�ƽ̨(���Ӽܹ�)�����
#define AS_ERR_BASENO				(-10500)					// ҵ�񼯳�ƽ̨(���Ӽܹ�)���Э��
#define AS_ERR_NOSTORAGEAREA		(AS_ERR_BASENO-0)			// �洢���򲻴���
#define AS_ERR_NOMODULE				(AS_ERR_BASENO-1)			// ������ָ�����͵Ĺ���ģ��
#define AS_ERR_BADMODULE			(AS_ERR_BASENO-2)			// ����ģ����Ч


// �ƶ�����(���Ӽܹ�)�����
#define MP_ERR_BASENO				(-12000)					// �����ƶ��������ش���
#define MP_ERR_NORPCHOST			(MP_ERR_BASENO-0)			// ��������վת������ʧ��
#define MP_ERR_ASYNCANSTOOLARGE		(MP_ERR_BASENO-1)			// �첽Ӧ�𻺳�̫��
#define MP_ERR_DATATOOLARGE			(MP_ERR_BASENO-2)			// Ӧ������̫��
#define MP_ERR_CANNOTREAD			(MP_ERR_BASENO-3)			// ��ȡ�ļ�ʧ��
#define MP_ERR_EXECUTESQL			(MP_ERR_BASENO-4)			// ִ��SQL���ô���
#define MP_ERR_MMNOTSUPPORT			(MP_ERR_BASENO-5)			// ���ò�֧��MM����
#define MP_ERR_NOROUTEINFO			(MP_ERR_BASENO-6)			// ��������·����Ϣʧ��

// ��̨�����
#define GT_ERR_BASENO				(-100000)					// ��̨�����
//#include "ASE_Err_GT.h"




















//////////////////////////////////////////////////////////////////////////
// ���ݴ����(��Щ������Ѿ�����,�������ѷ������)
#define ERR_NOTDXBRANCH				SYS_ERR_NOENTRYPOINT
#define ERR_NOREALBRANCH			SYS_ERR_NOBRANCH
#define ERR_BUSYROUTE				TC_ERR_BUSYROUTE

#endif

