//
//  macro.h
//  tdxiphone
//
//  Created by 魏 文敏 on 09-12-23.
//  Copyright 2009 武汉. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "qsbs.h"

//////////////////////////////////////////////////////////
//
//		EGp公共模块使用的常量和宏定义
//
//////////////////////////////////////////////////////////

//#define TDEL(a) {if (a) {delete a;a=NULL;}}
//#define TDELA(a) {if (a) {delete [] a;a=NULL;}}

//#define TRUE			1
//#define FALSE			0

#define TRADESEPERATE  @"\x01"


//#define IMAC_LOG
/*
 招商证券   IMAC_SSL_JY    IMAC_ZSZQ
 民族证券    IMAC_MZZQ
 中信建投     IMAC_ZXJT
 国海证券     IMAC_GHZQ
 通达信     IMAC_TDX
 中信证券   IMAC_ZXZQ
 西南证券    IMAC_XNZQ
 国联证券    IMAC_GLZQ
 中泰证券    IMAC_ZTZQ
 国信证券    IMAC_GXZQ
 华西证券    IMAC_HXZQ
 光大证券    IMAC_GDZQ
 */

#define IMAC_SSL_JY         //安全加固，205以后的交易中心都要安全加固，不然交易登录会提示424，创建请求结构失败
//#define IMAC_ONLYHQ
//#define JY_SDXJC            //适当性检查
#define IMAC_ALLOWXYJY //在普通交易的基础上,允许信用交易

//#define IMAC_ZXJT
//#define IMAC_ZSZQ
//#define IMAC_GTJA
//#define IMAC_MZZQ
//#define IMAC_TDX
//#define IMAC_GHZQ
//#define IMAC_ZXZQ
//#define IMAC_XNZQ
//#define IMAC_GLZQ
//#define IMAC_ZTZQ
//#define IMAC_GDZQ
//#define IMAC_GXZQ
//#define IMAC_GFZQ
//#define IMAC_WLZQ
//#define IMAC_TPY
//#define IMAC_HXZQ
//#define IMAC_SXZQ
#define IMAC_PAZQ

#define QUERY_LOOPEND

#ifdef IMAC_HXZQ
#define ZSZQ_TITLETIP  @"华西证券网上交易"
#define MAC_TITLETIP  @"华西证券网上交易"
#define MAC_PATHSTRING @"/hxzq_macosx"
#endif

#ifdef IMAC_TPY
#define ZSZQ_TITLETIP  @"太平洋证券网上交易"
#define MAC_TITLETIP  @"太平洋证券网上交易"
#define MAC_PATHSTRING @"/tpy_macosx"
#endif

#ifdef IMAC_WLZQ
#define ZSZQ_TITLETIP  @"万联证券网上交易"
#define MAC_TITLETIP  @"万联证券网上交易"
#define MAC_PATHSTRING @"/wlzq_macosx"
#endif

#ifdef IMAC_GFZQ
#define ZSZQ_TITLETIP  @"广发证券网上交易"
#define MAC_TITLETIP  @"广发证券网上交易"
#define MAC_PATHSTRING @"/gfzq_macosx"
#endif

#ifdef IMAC_GDZQ
#define ZSZQ_TITLETIP  @"光大证券网上交易"
#define MAC_TITLETIP  @"光大证券网上交易"
#define MAC_PATHSTRING @"/gdzq_macosx"
#endif

#ifdef IMAC_PAZQ
#define ZSZQ_TITLETIP  @"平安证券网上交易"
#define MAC_TITLETIP  @"平安证券网上交易"
#define MAC_PATHSTRING @"/pazq_macosx"
#endif

#ifdef IMAC_ZTZQ
#define ZSZQ_TITLETIP  @"中泰证券网上交易"
#define MAC_TITLETIP  @"中泰证券网上交易"
#define MAC_PATHSTRING @"/ztzq_macosx"
#endif

#ifdef IMAC_GXZQ
#define ZSZQ_TITLETIP  @"国信证券网上交易"
#define MAC_TITLETIP  @"国信证券网上交易"
#define MAC_PATHSTRING @"/gxzq_macosx"
#endif

#ifdef IMAC_ZXZQ
#define ZSZQ_TITLETIP  @"中信证券网上交易"
#define MAC_TITLETIP  @"中信证券网上交易"
#define MAC_PATHSTRING @"/zxzq_macosx"
#endif

#ifdef IMAC_GLZQ
#define ZSZQ_TITLETIP  @"国联证券网上交易"
#define MAC_TITLETIP  @"国联证券网上交易"
#define MAC_PATHSTRING @"/glzq_macosx"
#endif

#ifdef IMAC_XNZQ
#define ZSZQ_TITLETIP  @"西南证券金点子财富管理终端"
#define MAC_TITLETIP  @"西南证券金点子财富管理终端"
#define MAC_PATHSTRING @"/xnzq_macosx"
#endif

#ifdef IMAC_GHZQ
#define ZSZQ_TITLETIP  @"国海证券网上交易"
#define MAC_TITLETIP  @"国海证券网上交易"
#define MAC_PATHSTRING @"/ghzq_macosx"
#endif

#ifdef IMAC_ZXJT
#define ZSZQ_TITLETIP  @"中信建投网上交易MAC版"
#define MAC_TITLETIP  @"中信建投网上交易MAC版"
#define MAC_PATHSTRING @"/zxjt_macosx"

#define JY_FXCP
#endif


#ifdef IMAC_ZSZQ
#define ZSZQ_TITLETIP  @"招商证券全能版"
#define MAC_TITLETIP  @"招商证券全能版"
#define MAC_PATHSTRING @"/zszq_macosx"
#endif

#ifdef IMAC_GTJA
#define ZSZQ_TITLETIP  @"国泰君安证券锐智版"
#define MAC_TITLETIP  @"国泰君安证券锐智版"
#define MAC_PATHSTRING @"/gtja_macosx"
#endif

#ifdef IMAC_MZZQ
#define ZSZQ_TITLETIP  @"民族证券网上交易"
#define MAC_TITLETIP  @"民族证券网上交易"
#define MAC_PATHSTRING @"/mzzq_macosx"
#endif


#ifdef IMAC_TDX
#define ZSZQ_TITLETIP  @"通达信iMac"
#define MAC_TITLETIP  @"通达信iMac"
#define MAC_PATHSTRING @"/tdx_macosx"
#define IMAC_ONLYHQ
#endif

#define RELEASEOBJ(nobj) {if(nobj) {[nobj release];nobj=nil;}}
//////////////////////////////////////////////////////////////////////////
// 交易

// 基础定义
#define TDXIN		// 标志入参
#define TDXOUT		// 标记出参
#define TDXINOUT	// 标志入/出参


//mac版功能


#define MAC_CHINESEFONT @"Arial"
#define MAC_ENGLISHFONT @"Arial"
//#define MAC_CHINESEFONT @"Times"
//#define MAC_ENGLISHFONT @"Times"

//#define MAC_WEB_FUNC      6000  //网页
#define MAC_ZST_FUNC       6001   // 走势图
#define MAC_FXT_FUNC      6002   //  分析图
#define MAC_BJ_FUNC       6003   // 报价
#define MAC_ZFPM_FUNC       6004   // 涨幅排名
#define MAC_ZIXUAN_FUNC     6005   // 自选
#define MAC_F10_FUNC       6006   // 基本资料
#define MAC_WEB_FUNC       6007   // 
#define MAC_CANCEL_WEB_FUNC       6008   // 
#define MAC_XGZX_FUNC       6009   //相关资讯 
#define MAC_SWITCH_FUNC       6010   //切换
#define MAC_MINE_FUNC    6011 //信息地雷

#define MAC_FASTWT_FUNC  6100
#define MAC_WT_FUNC 6101
#define MAC_TRADE_FUNC 6102
#define MAC_BANK_FUNC 6103
#define MAC_CANCEL_FUNC 6104
#define MAC_REFRESH_FUNC 6105
#define MAC_NORMALWT_FUNC 6106
#define MAC_PASSWORD_FUNC 6107
#define MAC_SHOWHIDETRADE_FUNC 6108

#define FULLSIZE (NSViewMinXMargin | NSViewWidthSizable | NSViewMaxXMargin | NSViewMinYMargin | NSViewHeightSizable | NSViewMaxYMargin)

//mac版菜单编号
#define MAC_MENU_FUNC_GRID  7000
#define MAC_MENU_FUNC_ZST   7001
#define MAC_MENU_FUNC_FXT   7002
#define MAC_MENU_FUNC_F10   7003
#define MAC_MENU_FUNC_NEWS  7004
#define MAC_MENU_FUNC_TRADE 7005
#define MAC_MENU_FUNC_F1	7006
#define MAC_MENU_FUNC_ZXJR  7007

#define MAC_MENU_GRID_ZIXUAN 7010
#define MAC_MENU_GRID_SHAG	 7011	
#define MAC_MENU_GRID_SHBG	 7012
#define MAC_MENU_GRID_SZAG	 7013
#define MAC_MENU_GRID_SZBG	 7014
#define MAC_MENU_GRID_SHZQ	 7015
#define MAC_MENU_GRID_SZZQ	 7016
#define MAC_MENU_GRID_HSAG	 7017
#define MAC_MENU_GRID_HSBG	 7018
#define MAC_MENU_GRID_ALLGP	 7019	
#define MAC_MENU_GRID_ALLZS	 7020
#define MAC_MENU_GRID_ZXQY	 7021
#define MAC_MENU_GRID_HSQZ	 7022
#define MAC_MENU_GRID_CYB	 7023
#define MAC_MENU_GRID_BKZS	 7024
#define MAC_MENU_GRID_HSZQ	 7025
#define MAC_MENU_GRID_HSJJ	 7026

#define MAC_MENU_ZST_SH180	 7030
#define MAC_MENU_ZST_SHZZ	 7031
#define MAC_MENU_ZST_SHAG	 7032
#define MAC_MENU_ZST_SHBG	 7033
#define MAC_MENU_ZST_SZ100	 7034
#define MAC_MENU_ZST_SZCZ	 7035
#define MAC_MENU_ZST_SZAG	 7036
#define MAC_MENU_ZST_SZBG	 7037
#define MAC_MENU_ZST_CYB	 7038
#define MAC_MENU_ZST_ZXQY	 7039
#define MAC_MENU_ZST_HS300	 7040

#define MAC_MENU_SORT_ZAF    7061
#define MAC_MENU_SORT_ZJCJ	 7062
#define MAC_MENU_SORT_QRSD   7063
#define MAC_MENU_SORT_ZRSP	 7064
#define MAC_MENU_SORT_CJL	 7065
#define MAC_MENU_SORT_XS	 7066
#define MAC_MENU_SORT_HSL	 7067
#define MAC_MENU_SORT_JRKP	 7068
#define MAC_MENU_SORT_ZGCJ	 7069
#define MAC_MENU_SORT_ZDCJ   7070
#define MAC_MENU_SORT_CJJE   7071
#define MAC_MENU_SORT_ZEF	 7072
#define MAC_MENU_SORT_LTGB   7073
#define MAC_MENU_SORT_ZSZ	 7074
#define MAC_MENU_SORT_SYL	 7075
#define MAC_MENU_SORT_NP	 7076
#define MAC_MENU_SORT_WP	 7077
#define MAC_MENU_SORT_NORMAL	 7078

#define MAC_MENU_TRADE_LOGIN 7100
#define MAC_MENU_TRADE_QUIT 7101
#define MAC_MENU_TRADE_SWITCH 7102
#define MAC_MENU_TRADE_LOCK 7103
#define MAC_MENU_HIDEANDSHOW_LOCK 7104
#define MAC_MENU_ALLSCREEN  7105
#define MAC_MENU_OPERATIONHELP  7106
#define MAC_MENU_MZSM  7107
#define MAC_MENU_FFFFWZ  7108
#define MAC_MENU_MMTS  7109

#define MAC_KEY_1   18
#define MAC_KEY_2   19
#define MAC_KEY_3   20
#define MAC_KEY_4   21
#define MAC_KEY_5   23
#define MAC_KEY_6   22
#define MAC_KEY_7   26
#define MAC_KEY_8   28
#define MAC_KEY_9   25
#define MAC_KEY_0   29

#define MAC_SKEY_1  83
#define MAC_SKEY_2  84
#define MAC_SKEY_3  85
#define MAC_SKEY_4  86
#define MAC_SKEY_5  87
#define MAC_SKEY_6  88
#define MAC_SKEY_7  89
#define MAC_SKEY_8  91
#define MAC_SKEY_9  92
#define MAC_SKEY_0  82

#define MAC_KEY_ESC   53
#define MAC_KEY_ENTER  36
#define MAC_SKEY_ENTER  76
#define MAC_KEY_TAB   48
#define MAC_KEY_DEL   51
#define MAC_KEY_SPACE   49

#define MAC_KEY_ARROWUP  126
#define MAC_KEY_ARROWDOWN   125
#define MAC_KEY_ARROWLEFT   123
#define MAC_KEY_ARROWRIGHT   124

#define MAC_KEY_F1 122
#define MAC_KEY_F2 120
#define MAC_KEY_F3 99
#define MAC_KEY_F4 118
#define MAC_KEY_F5 96
#define MAC_KEY_F6 97
#define MAC_KEY_F7 98
#define MAC_KEY_F8 100
#define MAC_KEY_F10 109


#define MAC_KEY_CHAR_A 0
#define MAC_KEY_CHAR_B 11
#define MAC_KEY_CHAR_C 8
#define MAC_KEY_CHAR_D 2
#define MAC_KEY_CHAR_E 14
#define MAC_KEY_CHAR_F 3
#define MAC_KEY_CHAR_G 5
#define MAC_KEY_CHAR_H 4
#define MAC_KEY_CHAR_I 34
#define MAC_KEY_CHAR_J 38
#define MAC_KEY_CHAR_K 40
#define MAC_KEY_CHAR_L 37
#define MAC_KEY_CHAR_M 46
#define MAC_KEY_CHAR_N 45
#define MAC_KEY_CHAR_O 31
#define MAC_KEY_CHAR_P 35
#define MAC_KEY_CHAR_Q 12
#define MAC_KEY_CHAR_R 15
#define MAC_KEY_CHAR_S 1
#define MAC_KEY_CHAR_T 17
#define MAC_KEY_CHAR_U 32
#define MAC_KEY_CHAR_V 9
#define MAC_KEY_CHAR_W 13
#define MAC_KEY_CHAR_X 7 
#define MAC_KEY_CHAR_Y 16
#define MAC_KEY_CHAR_Z 6

#define MAC_KEY_CHAR_LEFT 33
#define MAC_KEY_CHAR_RIGHT 30
#define MAC_KEY_PAGEDOWN 121
#define MAC_KEY_PAGEUP 116
#define MAC_KEY_DELETE_WIN 117
// 主界面中按钮的id
// #define MENU_ZXG_ID      1000   // 主界面-自选股
//const UINT MENU_ZXG_ID = 1000;  // 主界面-自选股  // c++建议这样做
#define MENU_DP_ID       1001   // 主界面-大盘
#define MENU_GGU_ID      1002   // 主界面-个股
#define MENU_PM_ID       1003   // 主界面-排名
#define MENU_ZX_ID       1004   // 主界面-咨讯
#define MENU_GGAO_ID     1005   // 主界面-公告
#define MENU_JY_ID       1006   // 主界面-交易
#define MENU_SZ_ID       1007   // 主界面-设置
#define MENU_BZ_ID       1008   // 主界面-帮助

// 此文件定义control中所需要的消息标志.
// EM_代表EDIT类中的消息；LM_代表LABEL类中的消息；LC_代表LISTCTRL中消息;CB_代表CHECKBOX中消息
#define CONTROLHIGH         18       // 控件的高度
#define CONTROLWIDTH_NORMAL 80       // 控件的正常宽度
#define CONTROLWIDTH_BIG    120      // 控件的大宽度(银证转账界面中控件...) 
#define ANSBUFFER_LEN       6*1024   // 接受协议返回值new的栈的大小
#define ONEKB_SIZE          1024
#define MIN_SIZE            50

#define EM_SETFOCUS         2000
#define EM_KILLFOCUS        2001

#define LM_SETFOCUS         2010
#define LM_KILLFOCUS        2011

#define LC_CORMOVE          1     // 左右移动的列数,最大设置为2列.
#define LC_COLNUM           20    // 允许的最大列数
#define LC_SHOW             2020  // SW_SHOW
#define LC_HIDE             2021  // SW_HIDE
#define LC_ROWNUM           200   // 允许的最大行数
#define LC_ONPAINT          2022  // LISTCTRL创建后发生给父窗口处理的onpaint消息

#define CB_SHOW      2030   // 弹出LIST控件
#define CB_HIDE      2031   // 隐藏LIST控件

// DLG_代表控件,LABEL_代表控件类型,GPMC代表控件的作用
#define DLG_LABEL_GPMC   1010   // 委托界面-股票名称
#define DLG_LABEL_KMSL   1011   // 委托界面-可买数量
#define DLG_LABEL_MR1    1017   // 委托界面-买一
#define DLG_LABEL_MR2    1018   // 委托界面-买二
#define DLG_LABEL_MR3    1019   // 委托界面-买三
#define DLG_LABEL_MR4    1020   // 委托界面-买四
#define DLG_LABEL_MR5    1021   // 委托界面-买五
#define DLG_LABEL_MC1    1027   // 委托界面-卖一
#define DLG_LABEL_MC2    1028   // 委托界面-卖二
#define DLG_LABEL_MC3    1029   // 委托界面-卖三
#define DLG_LABEL_MC4    1030   // 委托界面-卖四
#define DLG_LABEL_MC5    1031   // 委托界面-卖五
#define DLG_LABEL_YHYE   1065   // 银行余额界面-银行余额

#define DLG_BUTTON_MRGP  1100   // 交易界面-买入股票按钮
#define DLG_BUTTON_MCGP  1101   // 交易界面-卖出股票按钮
#define DLG_BUTTON_WTCD  1102   // 交易界面-委托撤单按钮
#define DLG_BUTTON_CX    1103   // 交易界面-查询按钮
#define DLG_BUTTON_YZYW  1104   // 交易界面-银证业务按钮
#define DLG_BUTTON_XGMM  1105   // 交易界面-修改密码按钮
#define DLG_BUTTON_TCJY  1106   // 交易界面-退出交易按钮

#define DLG_BUTTON_GFCX  1110   // 委托撤单界面-股份查询按钮
#define DLG_BUTTON_ZJYE  1111   // 委托撤单界面-资金余额按钮
#define DLG_BUTTON_DRCJ  1112   // 委托撤单界面-当日成交按钮
#define DLG_BUTTON_DRWT  1113   // 委托撤单界面-当日委托按钮
#define DLG_BUTTON_YZZZ  1120   // 银证业务界面-银证转账
#define DLG_BUTTON_ZZCX  1121   // 银证业务界面-转账余额
#define DLG_BUTTON_YHYE  1122   // 银证业务界面-银行余额

#define DLG_EDIT_ZH      1200   // 交易登录界面-帐号
#define DLG_EDIT_MM      1201   // 交易登录界面-密码
#define DLG_EDIT_GPDM    1202   // 委托委托界面-股票代码
#define DLG_EDIT_WTJG    1203   // 委托委托界面-委托价格
#define DLG_EDIT_WTSL    1204   // 委托委托界面-委托数量
#define DLG_EDIT_DQJYMM  1240   // 修改密码界面-当前交易密码
#define DLG_EDIT_XJYMM   1241   // 修改密码界面-新交易密码
#define DLG_EDIT_QRXJYMM 1242   // 修改密码界面-确认新交易密码
#define DLG_EDIT_YHMM    1250   // 银证转账界面-银行密码
#define DLG_EDIT_ZJMM    1251   // 银证转账界面-资金密码
#define DLG_EDIT_ZZJE    1252   // 银证转账界面-转账金额
#define DLG_EDIT_QSRQ    1255   // 转账查询界面-起始日期
#define DLG_EDIT_ZZRQ    1256   // 转账查询界面-终止日期
#define DLG_EDIT_YHYE_YHMM    1260   // 银行余额界面-银行密码
#define DLG_EDIT_YHYE_ZJMM    1261   // 银行余额界面-资金密码

#define DLG_LIST_WTCD    1350   // 委托撤单界面
#define DLG_LIST_GFCX    1351   // 查询-股东查询界面
#define DLG_LIST_ZJYE    1352   // 查询-资金余额界面
#define DLG_LIST_DRZJ    1353   // 查询-当日成交界面
#define DLG_LIST_DRWT    1354   // 查询-当日委托界面
#define DLG_LIST_ZZCX    1355   // 银证业务-转账查询界面
#define DLG_LIST_LSWT	  1356	//查询－历史委托界面
#define DLG_LIST_LSCJ	  1357	//查询－历史成交界面
#define DLG_LIST_CJHZ	  1358	//查询－成交汇总界面
#define DLG_LIST_ZJLS	  1359	//查询－资金流水界面
#define DLG_LIST_PHCX	  1360	//查询－配号查询界面

#define DLG_BOX_ZHLB     1400   // 交易登录界面-帐号类别
#define DLG_BOX_YYB      1401   // 交易登录界面-营业部
#define DLG_BOX_GDDM     1402   // 委托委托界面-股东代码
#define DLG_BOX_MMLX     1440   // 修改密码界面-密码类别
#define DLG_BOX_ZZFS     1450   // 银证转账界面-转账方式
#define DLG_BOX_XZYH     1451   // 银证转账界面-选择银行
#define DLG_BOX_XZBZ     1452   // 银证转账界面-选择币种
#define DLG_BOX_ZZCX_YH  1455   // 转账查询界面-银 行
#define DLG_BOX_ZZCX_BZ  1456   // 转账查询界面-币 种
#define DLG_BOX_YH       1460   // 银行余额界面-银 行
#define DLG_BOX_BZ       1461   // 银行余额界面-币 种

//撤单类型
#define WT_CANCEL_STK		0		//股票撤单
#define WT_CANCEL_FUND	1		//基金撤单
#define USER_Info_STK		2		//股票信息
#define USER_Info_FUND		3		//基金信息
#define USER_Info_GG		4		//港股信息
#define WT_CANCEL_GG		5		//港股撤单
#define WT_CANCEL_LC		6		//理财撤单
#define USER_Info_LC		7		//理财信息
/************************************************************************/
/*                               行 情                                  */
/************************************************************************/

#define MEANLESS_DATA   7654321.00
#define MAX_ZXG_NUM		50
#define MAZ_DP_NUM      9

#define SZ	0
#define SH	1
#define QH	2
#define SZ_SH 3

#define NOXS          0			//没有小数
#define ZS            1			//指数
#define XS1			  4			//1位小数	
#define XS2           2			//2位小数
#define XS3           3			//3位小数

#define	QHLB  0	//期货类别
#define	GPLB  1	//股标类别
#define	ZSLB  2	//指数
#define	HKLB  3

#define GPHQMAXCOL    9		    // 行情栏目个数

//股票栏目代码
#define ZQDM  0			//代码
#define ZQJC  1			//证券名
#define ZRSP 2		//昨收
#define JRKP 3			//今开
#define ZGCJ 4			//最高
#define ZDCJ 5			//最低
#define ZJCJ 6			//现价
#define ZGJM 7			//叫买价
#define ZDJM 8		//叫卖价
#define CJL  9			//总手
#define CJJE 10			//总金额
#define XS    11			//现手
#define QRSD  12			//日升跌
#define QBSD  13			//笔升跌
#define ZAF   14			//涨幅
#define ZEF   15			//振幅
#define JUNJ  16			//均价
#define WTB   17			//委比
#define NP   18			//内盘
#define WP    19			//外盘
#define LWB   20			//内外比
#define WLC   21			//委量差

#define BJL1  22			//买手一
#define SJL1  23			//卖手一
#define BJ1   24			//买价一,昨持仓,
#define SJ1   25			//卖价一,昨结算

#define BJ2  26			//买价二
#define BJL2 27			//买手二
#define SJ2   28			//卖价二,持仓增减
#define SJL2  29			//卖手二

#define BJ3   30			//买价三
#define BJL3  31			//买手三
#define SJ3   32			//卖价三
#define SJL3  33			//卖手三

#define BJ4   34			//买价四
#define BJL4  35			//买手四
#define SJ4  36			//卖价四
#define SJL4  37			//卖手四

#define BJ5   38			//买价五
#define BJL5  39			//买手五
#define SJ5   40			//卖价五
#define SJL5  41			//卖手五

#define LIANGB 35			//量比

#define DKPH    43		//多空平衡
#define DTHL   44		//多头获利
#define DTZS    45		//多头止损
#define KTHB   46		//空头回补
#define KTZS    47		//空头止损
#define QRD     48		//强弱度

#define ZANGSU  49		//涨速

#define HYD		50		//活路度
#define MBZL	51		//每笔均量

#define HSL		36			//换手率
#define LTGB	37			//流通股本
#define LTSZ	38		//流通市值
#define ZSZ		39		//总市值
#define  SYL   17

////////////////////////////////////////////////////////////
#define FIXED_BARHEIGHT	    25     // 控件栏高度
#define FIXED_INPUTWIDE	    48     // 输入框宽度
#define FIXED_HEIGHT        18     // 单行高度(行情)

#define ADDED_FXT	240

//几种版面类型,从1开始,0表示状态栏
#define PAD_INIT		 0   // 状态栏,由于没有状态栏,此选项代表空白界面（自选股进入的选择界面等）
#define PAD_TICK		 1   // 分笔栏
#define PAD_FJB			 2
#define PAD_ZST			 3
#define PAD_FXT			 4
#define PAD_HQ	         5
#define PAD_GRID		 6
#define PAD_F10			 7
#define PAD_XXM			 8
#define PAD_DP	    	 9   // 大盘界面
// #define PAD_WT			= 10;

//Unit类型及其风格
#define SHOW_UNIT			0
#define GRID_UNIT			1
#define ZST_UNIT			2
#define FXT_UNIT			3
#define HQ_UNIT				4
#define TICK_UNIT			5
#define F10_UNIT			6
#define XXM_UNIT			7
#define WT_UNIT				8
#define FJB_UNIT			9
#define DP_UNIT		       10

//控制图的风格

#define UM_GETDATA_ACK	WM_USER+3021
#define ASYN_HQ_MESSAGE	WM_USER+3022

#define UM_SET_STOCK	WM_USER+4060
#define UM_GET_STOCK	WM_USER+4061
#define UM_READDATA		WM_USER+4062
//#define UM_CREATE       WM_USER+4063   // 大盘主界面的创建
//#define UM_COMMAND      WM_USER+4064   // 大盘主界面选择
#define UM_SETRECT		WM_USER+4073

#define UM_START		WM_USER+4083   // 节目开始了

//其它自定义消息
#define UM_SETPERIOD	WM_USER+5001
#define PER_MIN5     0
#define PER_MIN15    1
#define PER_MIN30    2
#define PER_HOUR     3 
#define PER_DAY      4
#define PER_WEEK     5
#define PER_MONTH    6 

#define UM_DPZST		WM_USER+5018   // 设置大盘走势

#define UM_SETDOMAIN	WM_USER+5020   // 设置市场
#define DOMAIN_SHAG		0
#define DOMAIN_SHBG		1
#define DOMAIN_SZAG		2
#define DOMAIN_SZBG		3
#define DOMAIN_SHZQ		4
#define DOMAIN_SZZQ		5
#define DOMAIN_ALLAG	6    // 沪深A股
#define DOMAIN_ALLBG	7
#define DOMAIN_ALLZQ	8    // 深证债券
#define DOMAIN_ALLJJ	9
#define DOMAIN_ALLGP	10   // 所有商品
#define DOMAIN_ALLZS	11   // 所有指数
#define DOMAIN_CYZQ		12   // 中小
#define DOMAIN_SHQZ		13   // 沪深权证
#define DOMAIN_SELF		100   // 自选股
#define DOMAIN_CYB      14   //创业板

#define TDX_ID_HQ_MRSL1						900			// 买一量
#define TDX_ID_HQ_MRSL2						901			// 买二量
#define TDX_ID_HQ_MRSL3						902			// 买三量
#define TDX_ID_HQ_MRSL4						903			// 买四量
#define TDX_ID_HQ_MRSL5						904			// 买五量

#define TDX_ID_HQ_MRLG1						910			// 买一价
#define TDX_ID_HQ_MRLG2						911			// 买二价
#define TDX_ID_HQ_MRLG3						912			// 买三价
#define TDX_ID_HQ_MRLG4						913			// 买四价
#define TDX_ID_HQ_MRLG5						914			// 买五价

#define TDX_ID_HQ_MCSL1						920			// 卖一量
#define TDX_ID_HQ_MCSL2						921			// 卖二量
#define TDX_ID_HQ_MCSL3						922			// 卖三量
#define TDX_ID_HQ_MCSL4						923			// 卖四量
#define TDX_ID_HQ_MCSL5						924			// 卖五量

#define TDX_ID_HQ_MCJS1						930			// 卖一价
#define TDX_ID_HQ_MCJS2						931			// 卖二价
#define TDX_ID_HQ_MCJS3						932			// 卖三价
#define TDX_ID_HQ_MCJS4						933			// 卖四价
#define TDX_ID_HQ_MCJS5						934			// 卖五价

#define TDX_ID_HQ_ZTJG						940			// 涨停价格
#define TDX_ID_HQ_DTJG						941			// 跌停价格

#define TDX_ID_HQ_CLOSE						946			//昨收价
#define TDX_ID_GZLX							947			//国债利息

#define	UM_GPSORT		WM_USER+5021
#define	UM_CHANGEZB		WM_USER+5022

#define UM_CREATEMENU	WM_USER+5030   // 创建菜单框
#define UM_EXITMENU		WM_USER+5031   // 关闭菜单框

#define UM_CONSTRUCTPAD	WM_USER+5040   // 面板PAD
#define UM_ADDSELFSOCKET  WM_USER+5041 // 添加自选股
#define UM_DELSELFSOCKET  WM_USER+5042 // 删除自选股

#define UM_LASTPAGE		WM_USER+5058
#define UM_NEXTPAGE		WM_USER+5059

#define	UM_SETUNIT_IDLE WM_USER+6013

#define UM_INITGRID		WM_USER+6022
#define UM_DRAWFRAME	WM_USER+6023

#define ELAPSE_TIMER	0x1001	//1分钟,分时,5分钟线的刷新更新时间  // 未用？？？
#define HQREFRESH_TIMER	0x1002	//单股行情刷新
#define GRID_TIMER		0x1003	//Grid行情刷新
#define	LOGIN_TIMER		0x1004	//连接超时               // 未用？？？
#define	LOGOK_TIMER		0x1005	//登陆超时               // 未用？？？

//嵌入式界面的几种菜单
#define MENU_GPDOMAIN	 0  // 集合（市场）
#define MENU_GPSORT		 1  // 排序
#define MENU_PERIOD		 2  // 周期（K线图）
#define MENU_ZB			 3  // 指标（分析图）


#define MAX_UNIT_NUM    93

#define AUTOCONNECTNUM	3	//设定自动重连的次数为3次

//行情协议
#define  COMBFST_NREQ         4606       // 组合分时走势图(可包括行情和/或每笔成交明细)
#define  GGHQ_5MMP_NREQ       4605		  // 支持5档买卖盘的个股行情协议
#define  COMBHQ_5MMP_NREQ     1313		  // 支持5档买卖盘( 刷新请求 )
#define  MULTIHQ2_5MMP_NREQ   4604	     // 支持5档买卖盘( Grid行情 )  4231
#define  COMBHQ2_5MMP_NREQ    4603		  // 支持5档买卖盘( Grid行情-自选股)
#define  COMBFX2_NREQ         4607       // 分析图协议号
#define  COMBTICK_NREQ        4608       // TICK协议号
#define  F10CFG_NREQ          4611       // f10标题协议号
#define  F10TXT_NREQ          4612       // f10内容协议号
#define  HISZST_NREQ          4613       // 历史分时
#define  STKVERSION_NREQ      4601       //查询服务器码表版本
#define  STKUPDATE_NREQ       4602		 //更新码表
#define  COMB_NREQ			  4617		 //组合数据
#define  COMBHQ_MASK_NREQ      4618      //支持掩码的组合行情
#define  COMBMULTIHQ_MASK_NREQ 4619     //支持掩码的多行情
#define  PYXG_NREQ			    4616     //拼音选股
#define  HOSTINFO_NREQ		    4600     //服务器信息
#define  SOFTVER_NREQ		    4622     //软件版本信息
#define  INFOTITLE_NREQ         4630     //取资讯工场的标题
#define  FILE_NREQ              4631     //取文件

#define HOSTINFO_ORI    4200  //服务器信息（42头协议）
#define STOCKCHAIN_ORI  4210  //取码表信息（42头协议）
#define  F10CFG_ALL          4211       // f10标题协议号
#define  F10TXT_ALL         4212       // f10内容协议号

#define STOCKCHAIN_ANSNUM 100

#define  ZST_ID					0       
#define  FXT_ID					1		  
#define  TICK_ID				2		  
#define  F10_TITLE_ID			3	
#define  F10_TEXT_ID			4	
#define  GIRD_ALL_ID			5		
#define  GIRD_BASE_ID			6
#define  ZIXUAN_ID				7       
#define  SEARCH_ID				8		
#define  PYXG_ID				9
#define  FXT_ONLY_ID            10
#define	 HIS_ZST_ID				11
#define	 ZIXUAN_ALL_ID			12
#define	 TICK_FIRSTPAGE	 13	//第一页
#define	 TICK_NEXTPAGE	 14	//下一页
#define	 TICK_PREVIOUSPAGE	15	//上一页
#define	 TICK_ENDPAGE	 16	//最后一页
#define  HOST_BASE_ID    17
#define  SOFT_VER_ID    18
//#define  F10CFG_NREQ          4611      
//#define  F10TXT_NREQ          4612       
//#define  STKVERSION_NREQ      4601      
//#define  STKUPDATE_NREQ       4602

//infotitle类别
#define INFOTITLE_TYPE_ALL 0 
#define INFOTITLE_TYPE_HY 1 
#define INFOTITLE_TYPE_ID 2 
#define INFOTITLE_TYPE_SS 3
#define INFOTITLE_TYPE_LS 4

#define COMBO_MASK_GGHQ		0x00000001		//行情
#define COMBO_MASK_ZST		0x00000002		//走势图
#define COMBO_MASK_FXT		0x00000004		//分析图
#define COMBO_MASK_TICK		0x00000008		//分笔
#define COMBO_MASK_GRADE	0x00000010		//评级(暂不支持)
#define COMBO_MASK_CW		0x00000020		//财务
#define COMBO_MASK_GBBQ		0x00000040		//股本变迁


//动画时间
#define kTransitionDuration 0.8

#define  MAX_VALUE(a,b)  ((a) > (b) ?  (a) : (b))
#define  MIN_VALUE(a,b)  ((a) < (b) ?  (a) : (b))
#define  ABSOLUTE_VALUE(x)  ((x) < 0 ? -(x) : (x))

//交易

#define TDX_CHB   0    // 存活包
#define TDX_KHXY  1	// 客户校验
#define TDX_GDCX  2	// 股东查询
#define TDX_YHXX  3   // 查询银行信息
#define TDX_CXHQ  4	// 查询行情
#define TDX_KMMS  5	// 可买卖数
#define TDX_GFCX  6	// 股份查询
#define TDX_CDCX  7	// 撤单查询
#define TDX_WTCD  8	// 委托撤单
#define TDX_WTJY  9	// 委托买卖
#define TDX_ZJYE  10	// 资金余额
#define TDX_DRCJ  11	// 当日成交
#define TDX_DRWT  12	// 当日委托
#define TDX_XGMM  13   // 修改密码
#define TDX_YZZZ  14   // 银证转账
#define TDX_ZZCX  15   // 转账查询
#define TDX_YHYE  16  // 银行余额
#define TDX_FECX  17	//基金份额查询
#define TDX_WTCX  18	//基金历史委托查询
#define TDX_GSCX  19	//基金公司查询
#define TDX_ZHCX  20	//基金帐号查询
#define TDX_DMCX  21	//基金代码查询
#define TDX_CJCX  23	//基金当日成交查询
#define TDX_WTRG  24	//基金委托认购
#define TDX_WTSH  25	//基金委托赎回
#define TDX_FHSZ  26	//基金分红设置
#define TDX_JJWT  27	//基金当日委托
#define TDX_LXCX  28	//联系方式查询
#define TDX_JJ_CDCX 29	//基金撤单查询
#define TDX_GFCX_HK 30	//港股股份查询
#define TDX_DRWT_HK 31	//港股委托查询
#define TDX_DRCJ_HK 32	//港股当日成交
#define TDX_WTCX_HK 33	//港股历史委托
#define TDX_CJCX_HK 34	//港股历史成交
#define TDX_GFBD_HK 35	//港股股份变动
#define TDX_ZJLS_HK 36	//港股资金流水
#define TDX_IPOLB_HK 37	//港股IPO列表
#define TDX_IPOPH_HK 38	//港股IPO配号
#define TDX_YECX  50	//账户余额查询
#define TDX_ZQXX	51	//证券信息查询
#define TDX_JJZH	52	//基金转换
#define TDX_JJKH	53	//基金开户
#define TDX_JJCD	54	//基金撤单
#define TDX_WTCDS  55		// 批量委托撤单
#define TDX_JJCDS	56	//批量基金撤单
#define TDX_LSWT	57	//历史委托
#define TDX_LSCJ	58	//历史成交
#define TDX_CJHZ	59	//成交汇总
#define TDX_ZJLS    60	//资金流水
#define TDX_PHCX	61    //配号查询
#define TDX_CXSC	62	//查市场
#define TDX_JJRG	63	//基金认购
#define TDX_GPWT  64	//股票买卖
#define TDX_JJSG	65	//基金申购
#define TDX_JJSH	66	//基金赎回
#define TDX_JJFH	68	//基金分红
#define TDX_ZJYE2  69	// 资金余额
#define TDX_LCGSCX  70		//理财公司查询
#define TDX_LCZHCX  71	//理财帐号查询
#define TDX_LCDMCX  72	//理财代码查询
#define TDX_LCFECX  73	//理财份额查询
#define TDX_LCLSWTCX  74	//理财历史委托查询
#define TDX_LCCJCX  75	//理财成交查询
#define TDX_LCWTCX  76	//理财当日委托查询
#define TDX_LCDEKTCX  77	//理财定额开通查询
#define TDX_CYLC  78	//参与理财
#define TDX_TCLC  79	//退出理财
#define TDX_LCDEKT  80	//理财定额开通
#define TDX_ZJYE3  81	// 资金余额
#define TDX_JJDQSG  82	//基金定期申购
#define TDX_LCDQSG  83	//理财定期申购
#define TDX_JJDQSGCX  84	//基金定期申购查询
#define TDX_LCDQSGCX  85	//理财定期申购查询
#define TDX_JJFXCPXX  86	//基金风险测评信息查询
#define TDX_JJDRWTCX	87	//基金当日委托查询
#define TDX_JJLSCJCX	90	//基金历史成交查询
#define TDX_JJFJYDRWTCX	91	//基金非交易当日委托
#define  TDX_JJFJYLSWTCX	92	//基金非交易历史委托
#define TDX_JJZNDTCD		93	//基金智能定投撤单
#define TDX_JJZNDTCDS		94	//基金智能定投批量撤单
#define TDX_WTCDSBYSELECT  95		// 多选中批量委托撤单
#define TDX_DLYCL          96   //登录预处理
#define TDX_YHYE2           97
#define TDX_SSLTOUCH        98
#define TDX_SSLSHAKE        99
#define TDX_IPOSGED         100
#define TDX_CXGPCP          101
#define TDX_XYZCCX          102 //信用资产查询 
#define TDX_XYRZHYCX        103 //信用融资合约查询
#define TDX_XYRQHYCX        104 //信用融券合约查询
#define TDX_XYFZCX          105 //信用负债查询
#define TDX_XYBDZQCX        106 //标的证券查询 3216
#define TDX_XYDBPZQCX       107 //信用担保品证券查询
#define TDX_XGZQCX          108 //中签查询
#define TDX_XYMCCX          109 //信用卖出查询
#define TDX_XYMQHKCX        110 //信用卖券还款查询
#define TDX_DBPHZ           111 //担保品划转
#define TDX_XYMQHQCX        112 //信用买券还券查询
#define TDX_XYXJHKCX        113 //信用现金还款查询
#define TDX_XYXQHQCX        114 //信用现券还券查询
#define TDX_PT_ZJZZ  115   // 资金转账(包括资金归集和内部划转)
#define TDX_DZJZHCX  116	// 多资金帐号信息查询
#define TDX_PT_DZJZJGJ  117	// 多资金帐号-资金归集
#define TDX_PT_DZJZZ  118	// 多资金帐号-转账
#define TDX_DBPHZCD       119 //担保品划转撤单
#define TDX_DBPHZCX       120 //担保品划转查询
#define TDX_XYSXCX          121 //信用上限查询
#define TDX_XGSGDJKCX       122 //新股申购待缴款查询
#define TDX_XGSG            123 //新股申购
#define TDX_KSGXGCX         124 //可申购新股查询
#define TDX_GDCX_DBPHZ      125	// 担保品划转股东查询
#define TDX_YHYE3           126 //通过948来查询余额
#define TDX_XGZJMM          127 //修改资金密码
#define TDX_SDXJC_LOGIN     128 //登录时，客户端发送322请求,适当性检查
#define TDX_SDXJC_CLICKMENU 129 //点击菜单，发送198功能

#define TDX_ID_ZQJYBS						90			// 证券交易标识 '1'为不支持 其他为支持
#define TDX_ID_FQSL							98
#define TDX_ID_MC							99			// 名次
#define TDX_ID_SCFLAG						100			// 交易所代码
#define TDX_ID_SCNAME						101			// 交易所名称
#define TDX_ID_YYB							102			// 营业部代码
#define TDX_ID_YYBMC						103			// 营业部名称
#define TDX_ID_TDX_OEM_FLAG					104			// #define TDX_ID_TDX_OEM_FLAG				7001


#define TDX_ID_OP_WTFS						110			// 委托方式
#define TDX_ID_OP_GYDM						111			// 柜员代码
#define TDX_ID_OP_GYMM						112			// 柜员密码

#define TDX_ID_CZBZ							113			// 操作标志
#define TDX_ID_CZZT							114			// 操作状态
#define TDX_ID_HZHGZT						115			// 合作回购状态
#define TDX_ID_ZDJYBZ						116			// 指定交易（0：未指定 1:指定）
#define TDX_ID_SQKTWZ						117			// 申请开通的网址
#define TDX_ID_HZHGDM						118			// 合作回购代码
#define TDX_ID_HZPSDM						119			// 合作配售代码
#define TDX_ID_KHH							120			// 客户号
#define TDX_ID_ZJZH							121			// 资金帐号
#define TDX_ID_KHMC							122			// 客户名称
#define TDX_ID_GDDM							123			// 股东代码
#define TDX_ID_GDMC							124			// 股东名称		
#define TDX_ID_ZHLB							125			// 帐号类别
#define TDX_ID_KSRQ							126			// 开始日期
#define TDX_ID_ZZRQ							127			// 终止日期
#define TDX_ID_USERPHONE					128			// 用户联系方式
#define TDX_ID_USEREMAIL					129			// 用户EMAIL

#define TDX_ID_MMBZ							130			// 买卖标志  0:买入 1:卖出 2:撤单 3:撤买 4:撤卖
#define	TDX_ID_MMBZSM						131			// 买卖标志说明
#define TDX_ID_BZ							132			// 币种 0:RMB 1:MY 2:GB
#define TDX_ID_JYDW							133			// 交易单位	 0:股 1:手 2:张
#define TDX_ID_JYMM							134			// 交易密码
#define TDX_ID_ZJMM							135			// 资金密码
#define TDX_ID_XJYMM						136			// 新交易密码
#define TDX_ID_XZJMM						137			// 新资金密码
#define TDX_ID_TXMM							138			// 通讯密码
#define TDX_ID_SECURETYPE					139			// 安全方式

#define TDX_ID_ZQDM							140			// 证券代码
#define TDX_ID_ZQMC							141			// 证券名称

#define TDX_ID_WTRQ							142			// 委托日期	YYYYMMDD
#define TDX_ID_WTSJ							143			// 委托时间 HHMMSS
#define TDX_ID_WTSL							144			// 委托数量
#define TDX_ID_WTJG							145			// 委托价格
#define TDX_ID_WTBH							146			// 委托编号
#define TDX_ID_ZTSM							147			// 状态说明
#define TDX_ID_WTJE							148			// 委托金额
#define TDX_ID_RETINFO						149			// 返回信息,(151 字节)
#define TDX_ID_CJRQ							150			// 成交日期
#define TDX_ID_CJSJ							151			// 成交时间 
#define TDX_ID_CJSL							152			// 成交数量
#define TDX_ID_CJJG							153			// 成交价格
#define TDX_ID_CJJE							154			// 成交金额
#define TDX_ID_CJBH							155			// 成交编号
#define TDX_ID_HZPSZT						156			// 合作配售状态
#define TDX_ID_HFBZ							157			// 合法标志
#define TDX_ID_DFMM							158			// 对方密码(金证柜台里面的证券资金帐号对应的密码,也就是银证转帐的地方的资金密码)
#define TDX_ID_HFBZSM						159			// 合法标志说明

#define TDX_ID_DJSL							160			// 冻结数量
#define TDX_ID_DJZJ							161			// 冻结资金
#define TDX_ID_CDSL							162			// 撤单数量
#define TDX_ID_CDBZSM						163			// 撤单标志说明
#define TDX_ID_LESSPRESSURE					164			// 银证通用户减轻柜台资金查询请求压力
#define TDX_ID_FIRSTZJCX					165			// 银证通用户第一次登陆查询资金
#define TDX_ID_WTFS							166			// (委托方式)市价委托方式
#define TDX_ID_CDBZ							167			// 撤单标志 1撤单  20061108 gxzq 当日成交查询返回隐藏的撤单标志给客户端,让客户端可以选择是否过滤掉撤单费单等非正常成交记录
#define	TDX_ID_KCDBZ						168			// 可撤单标志
#define	TDX_ID_LSH							169			// 流水号

#define TDX_ID_PHRQ							170			// 配号日期
#define TDX_ID_QSPH							171			// 起始配号
#define	TDX_ID_PHSL							172			// 配号数量
#define TDX_ID_XWDM							173			// 席位代码
#define TDX_ID_ZQS							174			// 中签数
#define TDX_ID_PHSLPHCX						175			// 配号数量(东莞的特殊处理)
#define TDX_ID_ZQRQ							176			// 中签日期
#define TDX_ID_QZLX							177			// 权证类型
#define TDX_ID_XQFS							178			// 行权方式
#define TDX_ID_XQBL							179			// 行权比例
#define TDX_ID_JSFS							180			// 结算方式


#define	TDX_ID_FXBZ							181			// 风险标志
#define	TDX_ID_FXSM							182			// 风险说明

#define	TDX_ID_JGRQ							183			// 交割日期

#define	TDX_ID_KHLBSM						184			// 客户类别说明
#define	TDX_ID_KHXZSM						185			// 客户性质说明
#define	TDX_ID_KHZTSM						186			// 客户状态说明

#define TDX_ID_ZXJYGS						187			// 最小交易股数

#define	TDX_ID_SHGD							188			// 上海股东
#define	TDX_ID_SZGD							189			// 深圳股东
#define TDX_ID_QZKTBZ						190			// 权证开通标志
#define TDX_ID_SGRDM						191			// 收购人代码
#define TDX_ID_YYSL							192			// 要约数量
#define TDX_ID_SBSL							193			// 申报数量
//#define TDX_ID_WTFS						166			// (委托方式)市价委托方式
#define TDX_ID_WTFSSM						194			// 市价委托方式说明
#define	TDX_ID_XTXMM						195			// 新通讯密码
#define TDX_ID_DZDLX						196			// 对帐单类型

#define TDX_ID_XXSL							197			// 选项数量`

#define TDX_ID_DQCB							198			// 当前成本
#define TDX_ID_ZTSL							199			// 在途数量
#define TDX_ID_ZQSL							200			// 证券数量
#define TDX_ID_KMSL							201			// 可卖数量
#define TDX_ID_CBJ							202			// 成本价
#define TDX_ID_ZXJ							203			// 最新价
#define TDX_ID_FDYK							204			// 浮动盈亏
#define TDX_ID_ZXSZ							205			// 最新市值
#define TDX_ID_YJ							206			// 佣金
#define TDX_ID_KHF							207			// 过户费
#define TDX_ID_CJF							208			// 成交费
#define TDX_ID_JSF							209			// 结算费
#define TDX_ID_YHS							210			// 印花税
#define TDX_ID_ZDKM							211			// 最大可买
#define TDX_ID_SXF							212			// 手续费(期货手续费:小于零时为交易金额的万分比，大于零为元/手)
#define TDX_ID_GPLX							213			// 股票类型
#define TDX_ID_GTZDKMBS						214			// 取柜台最大可买标识
#define TDX_ID_DRMRSL						215			// 当日买入数量
#define TDX_ID_GPLBP						216			// 股票篮买入价
#define TDX_ID_GPLBV						217			// 股票篮买入量
#define TDX_ID_GPLSP						218			// 股票篮卖出价
#define TDX_ID_GPLSV						219			// 股票篮卖出量
#define TDX_ID_KHQXDM						220			// 客户权限代码
#define TDX_ID_KHQXMC						221			// 客户权限名称
#define TDX_ID_BBJ							222			// 保本价
#define TDX_ID_YWTSL						223			// 原委托数量
#define TDX_ID_YWTJG						224			// 原委托价格

#define TDX_ID_QTF							225			// 其他费
#define TDX_ID_ZXMRBDJW						226			// 最小买入变动价位
#define TDX_ID_ZXMCBDJW						227			// 最小卖出变动价位

#define TDX_ID_ZCZJZH						228			// 转出资金帐号
#define TDX_ID_ZRZJZH						229			// 转入资金帐号

#define TDX_ID_YKBL							230			// 盈亏比例
#define	TDX_ID_ZJZHEX						231			// 广发附属资金帐号
#define	TDX_ID_SXYK							232			// 实现盈亏
#define	TDX_ID_TBYK							233			// 摊薄盈亏
#define	TDX_ID_LX							234			// 类型
#define	TDX_ID_CJDF							235			// 成交单费
#define	TDX_ID_WTDF							236			// 委托单费

#define TDX_ID_JJRDM						237			// 经纪人代码
#define TDX_ID_ZHZT							238			// 帐户状态
#define TDX_ID_KGDBZ						239			// 可改单标志
#define TDX_ID_MAILADDRESS					240			// 邮寄地址

#define TDX_ID_ZJLS_FSJE					265
#define TDX_ID_ZJLS_SYJE					266
#define TDX_ID_ZJLS_YWMC					263
#define TDX_ID_QSJE						1165

#define	TDX_ID_ZTZJ							280			// 在途资金
#define	TDX_ID_XYJYBS						281			// 支持信用交易用户标志
#define	TDX_ID_SFCGBS						282			// 三方存管标识
#define TDX_ID_ZZFS							283			// 转帐方式
#define TDX_ID_ZZQD							284			// 转帐渠道
#define TDX_ID_ZZBH							285			// 转帐编号
#define TDX_ID_FPYH							286			// 发票银行
#define TDX_ID_ZPBH							287			// 支票编号

#define TDX_ID_ZJCJSL						288			// 最近成交数量
#define TDX_ID_ZJCDSL						289			// 最近撤单数量
#define TDX_ID_KHBS							290			// 客户标识

#define TDX_ID_ZJYE							300			// 资金余额
#define TDX_ID_KYZJ							301			// 可用资金
#define TDX_ID_KQZJ							302			// 可取资金
#define TDX_ID_OCCURJE						303			// 发生金额
#define TDX_ID_POSTJE						304			// 剩余金额	
#define TDX_ID_ZY							305			// 摘要
#define TDX_ID_YWMC							306			// 业务名称
#define TDX_ID_YWDM							307			// 业务代码
#define TDX_ID_MRDJZJ						308			// 买入冻结资金
#define TDX_ID_YZT_YHXZTS					309			// 选择银行提市标志
#define TDX_ID_GTZZC						310			// 柜台总资产
#define TDX_ID_CJLX							311			// 成交类型
#define	TDX_ID_JYDJZJ						312			// 交易冻结资金
#define	TDX_ID_YCDJZJ						313			// 异常冻结资金
#define	TDX_ID_ZTKYZJ						314			// 在途可用资金
#define	TDX_ID_XJKQZJ						315			// 现金可取资金
#define	TDX_ID_ZPKQZJ						316			// 支票可取资金
#define	TDX_ID_KZZJ							317			// 可转资金
#define	TDX_ID_LXJE							318			// 利息金额
#define	TDX_ID_LXS							319			// 利息税
#define	TDX_ID_SYSL							320			// 剩余数量
#define	TDX_ID_FJF							321			// 附加费
#define	TDX_ID_SXJE							322			// 所需金额
#define	TDX_ID_MMCB							323			// 买卖成本
#define	TDX_ID_MRCB							324			// 买入成本
#define TDX_ID_ZGF							325			// 证管费
#define TDX_ID_FCJL							326			// 分仓基量

#define TDX_ID_ZYK							327			// 总盈亏
#define TDX_ID_TBCBJ						328			// 摊薄成本价
#define TDX_ID_TBBBJ						329			// 摊薄保本价
#define TDX_ID_TBFDYK						330			// 摊薄浮动盈亏


#define TDX_ID_XXNR0						340			// 选项内容0
#define TDX_ID_XXNR1						341			// 选项内容1
#define TDX_ID_XXNR2						342			// 选项内容2
#define TDX_ID_XXNR3						343			// 选项内容3
#define TDX_ID_XXNR4						344			// 选项内容4
#define TDX_ID_XXNR5						345			// 选项内容5
#define TDX_ID_XXNR6						346			// 选项内容6
#define TDX_ID_XXNR7						347			// 选项内容7
#define TDX_ID_XXNR8						348			// 选项内容8
#define TDX_ID_XXNR9						349			// 选项内容9

// 模拟股票类
#define TDX_ID_ZZC							350			// 总资产
#define TDX_ID_SYL							351			// 收益率
#define TDX_ID_HYZS							352			// 活跃指数
#define TDX_ID_RMBZZC						353			// 人民币总资产
#define TDX_ID_MYZZC						354			// 美元总资产
#define TDX_ID_GYZZC						355			// 港元总资产
#define TDX_ID_SYLTJRQ						356			// 收益率统计日期
#define TDX_ID_SYLTJSJ						357			// 收益率统计时间
#define TDX_ID_MOCK_ZHTYPE					360			// 账号类型 0:股票 1:期货 2:外汇

#define TDX_ID_RQSL							370			// 融券数量(一个融券单位：10000股)
#define TDX_ID_RQJG							371			// 融券价格
#define TDX_ID_RQZQ							372			// 融券周期
#define TDX_ID_RQCZLX						374			// 融券操作类型(0:融券 1:还券 2:展期)
#define TDX_ID_RQRQ							375			// 融券日期
#define TDX_ID_RQSJ							376			// 融券时间
#define TDX_ID_HTBH							377			// 合同编号

// 开放式基金类
#define TDX_ID_SFFSSM						388			// 收费方式说明
#define	TDX_ID_CPJZ							389			// 产品净值
#define	TDX_ID_LCZH							390			// 理财账户
#define	TDX_ID_CPDM							391			// 产品代码
#define	TDX_ID_CPMC							392			// 产品名称
#define	TDX_ID_CPGSDM						393			// 产品公司代码
#define	TDX_ID_CPGSMC						394			// 产品公司名称
#define	TDX_ID_CPZT							395			// 产品状态
#define	TDX_ID_QRJZ							396			// 前日净值(前一个交易日的净值)
#define	TDX_ID_CPBZ							397			// 产品标志(0:普通基金产品,1:券商理财产品)
#define	TDX_ID_KTBZ							398			// 开通标志
#define	TDX_ID_KFSJJ_LJJZ					399			// 累计净值
#define TDX_ID_KFSJJ_MMBZ					400			// 0:认购 1：申购 2：赎回 3:预约申购 4:预约赎回
#define TDX_ID_KFSJJ_JJGSMC					401			// 基金公司名称
#define TDX_ID_KFSJJ_JJDM					402			// 基金代码
#define	TDX_ID_KFSJJ_JJMC					403			// 基金名称
#define TDX_ID_KFSJJ_JJFE					404			// 基金份额
#define TDX_ID_KFSJJ_JYJE					405			// 交易金额
#define TDX_ID_KFSJJ_JJJZ					406			// 基金净值
#define TDX_ID_KFSJJ_ZHDM					407			// 基金转换代码
#define TDX_ID_KFSJJ_DIVIDENMETHOD			408			// 基金分红方式	    ‘0’-红利转股、‘1’//现金分红、‘2’-利得现金增值再投资、‘3’//-增值现金利得再
#define TDX_ID_KFSJJ_FSRQ					409			// 发生日期
#define TDX_ID_KFSJJ_KYFE					410			// 可用份额
#define TDX_ID_KFSJJ_JJBS					411			// 开放式基金标识 0：不支持 1：支持
#define TDX_ID_KFSJJ_QSSL					412			// 起始数量
#define TDX_ID_KFSJJ_DQSL					413			// 当前数量
#define TDX_ID_KFSJJ_WTFE					414			// 委托份额
#define TDX_ID_KFSJJ_CJFE					415			// 成交份额
#define TDX_ID_KFSJJ_CJJE					416			// 成交金额
#define TDX_ID_KFSJJ_JJZH					417			// 基金帐户
#define TDX_ID_KFSJJ_FXJG					418			// 发行价格

#define TDX_ID_KFSJJ_GRZDRGJE				419			// 个人最低认购金额
#define TDX_ID_KFSJJ_FRZDRGJE				420			// 法人最低认购金额
#define TDX_ID_KFSJJ_ZDCYFE					421			// 最低持有份额
#define TDX_ID_KFSJJ_ZGSHFE					422			// 最高赎回份额
#define TDX_ID_KFSJJ_GRZGCYBL				423			// 个人最高持有比例
#define TDX_ID_KFSJJ_FRZGCYBL				424			// 法人最高持有比例
#define TDX_ID_KFSJJ_JJZT					425			// 基金状态
#define TDX_ID_KFSJJ_JJGSDM					426			// 基金公司代码
#define TDX_ID_KFSJJ_FXZS					427			// 发行总数
#define TDX_ID_KFSJJ_ZDSHFE					428			// 最低赎回份额
#define TDX_ID_SFFS							429			// 收费方式

#define TDX_ID_KFSJJ_JGZGBL					430			// 机构最高比例
#define TDX_ID_KFSJJ_GRZGBL					431			// 个人最高比例
#define TDX_ID_KFSJJ_GRZGRGZJ				432			// 个人最高认购金额
#define TDX_ID_KFSJJ_FRZGRGZJ				433			// 法人最高认购金额
#define TDX_ID_KFSJJ_GRSCSGZDZJ				434			// 个人首次申购最低资金
#define TDX_ID_KFSJJ_FRSCSGZDZJ				435			// 法人首次申购最低资金
#define TDX_ID_KFSJJ_GRZJSGZDZJ				436			// 个人追加申购最低资金
#define TDX_ID_KFSJJ_FRZJSGZDZJ				437			// 法人追加申购最低资金
#define TDX_ID_KFSJJ_GRJJZSSHFE				438			// 个人基金最少赎回份额
#define TDX_ID_KFSJJ_FRJJZSSHFE				439			// 法人基金最少赎回份额
#define TDX_ID_KFSJJ_GRJJZSZHFE				440			// 个人基金最少转换份额
#define TDX_ID_KFSJJ_FRJJZSZHFE				441			// 法人基金最少转换份额
#define TDX_ID_KFSJJ_TADM					442			// TA 代码
#define TDX_ID_KFSJJ_GTGSBZ					443			// 开放式基金柜台公司标志

#define TDX_ID_KFSJJ_FHFSDM					444			// 分红方式代码
#define	TDX_ID_KFSJJ_FHFSMC					445			// 分红方式名称
#define TDX_ID_LSDJ							446			// 临时冻结
#define TDX_ID_MCWTSL						447			// 卖出冻结
#define TDX_ID_KFSJJ_PZDM					448			// 申购品种代码
#define TDX_ID_KFSJJ_MYKKRQ					449			// 每月扣款日期

#define TDX_ID_KHTYPE						450			// 开户类别，个人，机构
#define TDX_ID_KFSJJ_DQSGNS					451			// 申购年数

#define TDX_ID_ZJLB							452			// 证件类别
#define TDX_ID_JYZH							453			// 交易帐户
#define TDX_ID_ZJHM							454			// 证件号码
#define TDX_ID_MOBILEPHONE					455			// 移动电话
#define TDX_ID_HOMEPHONE					456			// 住宅电话
#define TDX_ID_FAX							457			// 传真
#define TDX_ID_EDU							458			// 教育程度
#define TDX_ID_SALARY						459			// 年收入
#define TDX_ID_XLYZT_DLSGFLAG				460			// 代理申购标志   0：未开通，1：开通 
#define TDX_ID_XLYZT_DLPGFLAG				461			// 代理配股标志   0：未开通，1：开通 
#define TDX_ID_XLYZT_DLPSFLAG				462			// 代理配售标志   0：未开通，1：开通 
#define TDX_ID_WORKPHONE					463			// 单位电话

#define TDX_ID_NAME							464			// 姓名
#define TDX_ID_VOCATION						465			// 职业
#define TDX_ID_FHBZ							466			// 分红标志
#define TDX_ID_DZDBZ						467			// 对帐单标志
#define TDX_ID_SHFS							468			// 赎回方式
#define TDX_ID_FHBL							469			// 分红比例

#define TDX_ID_FHRQ							470			// 分红日期
#define TDX_ID_FHJE							471			// 分红金额
#define TDX_ID_FHSL							472			// 分红数量
#define TDX_ID_MGFHJE						473			// 每股分红金额

#define TDX_ID_ZDBZ							474			// 指定标志
#define TDX_ID_FHFS							475			// 分红方式
#define TDX_ID_KHRQ							476			// 开户日期

#define TDX_ID_KFSJJ_JGZDTZ					480			// 机构最低投资
#define TDX_ID_KFSJJ_GRZDTZ					481			// 个人最低投资
#define TDX_ID_KFSJJ_JGZDZJ					482			// 机构最低追加
#define TDX_ID_KFSJJ_GRZDZJ					483			// 个人最低追加

#define TDX_ID_SPEL_GX_HZXGSGZT				484			// 国信查询合作新股申购状态
// 调整到定义范围内
#define	TDX_ID_TJRDM						485			// 推荐人代码
#define	TDX_ID_QHZHBS					500			//期货账户标识
#define TDX_ID_XDLY							517			// 下单来源
#define TDX_ID_CJJJ							523			// 成交均价
#define	TDX_ID_GGZHBS					580			//港股账户标识
#define TDX_ID_WCJSL						732			// 为成交数量
#define TDX_ID_XXLXSM						737			// 信息类型说明

#define TDX_ID_JRMRJE						630
#define TDX_ID_JRMCJE						632

#define TDX_ID_NOW							949			// 当前价
#define TDX_ID_USERADDRESS					950			// 联系地址
#define TDX_ID_IDENTITYCARD					951			// 身份证
#define TDX_ID_SEX							952			// 性别
#define TDX_ID_POSTALCODE					953			// 邮政编码
#define TDX_ID_YZZZ_YHDM					1101		// 银行代码
#define TDX_ID_YZZZ_YHMC					1102		// 银行名称
#define TDX_ID_YZZZ_YHZH					1103		// 银行帐号
#define TDX_ID_YZZZ_YHMM					1104		// 银行密码
#define TDX_ID_YZZZ_XYHMM					1105		// 新银行密码
#define TDX_ID_YZZZ_YHLSH					1106		// 银行流水号
#define TDX_ID_YZZZ_ZZJE					1107		// 转帐金额
#define TDX_ID_YZZZ_ZZFX					1108		// 转帐方向
#define TDX_ID_YZZZ_YHYE					1109		// 银行余额
#define TDX_ID_YZZZ_ZZRQ					1110		// 转帐日期
#define TDX_ID_YZZZ_ZZSJ					1111		// 转帐时间
#define TDX_ID_YZZZ_ZZFXSM					1112		// 转帐说明
#define TDX_ID_YZTYH						1113		// 银证通用户 0:否 1:是
#define	TDX_ID_YZZZ_NEEDZJMM				1114		// 需要资金密码
#define TDX_ID_YZZZ_NEEDYHMM				1115		// 需要银行密码
#define	TDX_ID_YZZZ_SUPPORTYHYE				1116		// 支持查银行余额
#define TDX_ID_BANKCODE						1117		// 银行代码
#define TDX_ID_BANKYYB						1118		// 银行营业部 (招商证券)
#define TDX_ID_BANKGDTYPE					1119		// 银行股东代码登陆的市场 (招商证券)
//0不需要密码 1 需要取款密码(资金密码) 2 需要银行密码 3 需要取款/银行密码
#define	TDX_ID_YZZZ_ZRMM					1120		// 银证转入密码情况
#define TDX_ID_YZZZ_ZCMM					1121		// 银证转出密码情况
#define	TDX_ID_YZZZ_SHOWYHYE				1122		// 显示查银行余额
#define	TDX_ID_YZZZ_YHYEMM					1123		// 查银行余额密码情况  20060328 配合国信linux 客户端
#define TDX_ID_ZRYHDM						1124		// 转入银行代码
#define TDX_ID_ZCYHDM						1125		// 转出银行代码
#define TDX_ID_ZRYHZH						1126		// 转入银行帐号
#define TDX_ID_ZCYHZH						1127		// 转出银行帐号
#define TDX_ID_ZJYHDM						1128		// 中继银行代码
#define TDX_ID_ZJYHMC						1129		// 中继银行名称
#define TDX_ID_ZJYHZH						1130		// 中继银行帐号
#define TDX_ID_ZJYHZHMC						1131		// 中继银行帐号名称
#define TDX_ID_XT_REMARK                    1217        // 备注
#define TDX_ID_XT_PARAM					1227		//参数
#define TDX_ID_XT_MODE					1228		//模式
#define TDX_ID_XT_DISPLAYCOLOR			1231		//显示颜色
#define	TDX_ID_XT_SESSION					1248		//会话信息
#define TDX_ID_XT_CHECKRISKFLAG             1223    //检查风险标志


#define IPHONE_WT_BUY						0    //买入委托
#define IPHONE_WT_SELL						1	//卖出委托
#define IPHONE_WT_CANCEL					2	//委托撤单
#define IPHONE_WT_GFCX						3	//股份查询
#define IPHONE_WT_ZJCX						4	//资金查询
#define IPHONE_WT_DRWT						5	//当日委托
#define IPHONE_WT_DRCJ						6	//当日成交
#define IPHONE_WT_BANK					    7	//银证业务
#define IPHONE_WT_OTHER						8	//其他业务
#define IPHONE_WT_QUIT					    9	//退出交易
#define IPHONE_WT_BANKTOSEC					10	//银行转证券
#define IPHONE_WT_SECTOBANK					11	//证券转银行
#define IPHONE_WT_ZZCX						12	//转账查询
#define IPHONE_WT_YHYE					    13	//银行余额
#define IPHONE_WT_ZJZZ					    14	//资金转账


#define MAX_GDDM_NUM		200

#ifdef QUERY_LOOPEND

    #define PAGE_ROWNUM			300		//每页显示21条
#else

    #define PAGE_ROWNUM			600		//每页显示21条

#endif
#define MAX_PAGENUM			3000       //最多翻1000页

#define	TDX_ID_XT_REMARK					1217		// 备注
#define TDX_ID_XT_BRANCHID				1212		//所在营业部id
#define TDX_ID_XT_HANDLE                    1233        // 句柄
#define TDX_ID_XT_POSITIONSTRING			1286		//定位串
#define TDX_ID_TOTALLINE					1289		// 总共行数
#define TDX_ID_XT_MOBILEMACHINEINFO		1292		//手机机器信息
#define TDX_ID_YQCY							5503		// 预期持有
#define TDX_ID_GPCY							5506		// 股票持有
#define TDX_ID_SCJ							5539		// 市场价
#define TDX_ID_QSSJ							5505		// 前收市价
#define TDX_ID_CQ							5507		// 存／取
#define TDX_ID_JSRQ							5508		// 交收日期
#define TDX_ID_SQZK							5517		// 中签数量
#define TDX_ID_JYRQ							5527		// 交易日期
#define TDX_ID_JE							5528		// 金额
#define TDX_ID_SCMG							5535		// 首次公开募股
#define TDX_ID_NBMG							5536		// 内部募股截止日期
#define TDX_ID_JZRQ							5537		// 申请截止日期
#define TDX_ID_SSRQ							5538		// 上市日期
#define TDX_ID_SQRQ							5541		// 申请日期


#define MAX_GDDM_NUM		200
#define MAX_PAGENUM	3000       //最多翻1000页

#define CODE_SZAG       0					//深圳A股
#define CODE_SZQZ       1					//深圳权证
#define CODE_SZGZ       2					//深圳国债
#define CODE_SZZQ       3					//深圳企债
#define CODE_SZKZHZQ    4					//深圳可转债
#define CODE_SZGZHG     5					//深圳国债回购
#define CODE_SZJJ       6					//深圳基金
#define CODE_SZBG       7					//深圳B股
#define CODE_SZCY       8					//深圳创业
#define CODE_SZOTHER    9					//深圳其它
#define CODE_SHAG      10					//上海A股
#define CODE_SHQZ      11					//上海权证
#define CODE_SHGZ      12					//上海国债
#define CODE_SHZQ      13					//上海企债
#define CODE_SHKZHZQ   14					//上海转债
#define CODE_SHGZHG    15					//上海回购
#define CODE_SHJJ      16					//上海基金
#define CODE_SHBG      17					//上海B股
#define CODE_SHOTHER   18					//上海其它
#define CODE_KFJJ	   19					//开放式基金
#define CODE_SB		   20					//三板

// 调整到定义范围内
#define	TDX_ID_TJRDM						485			// 推荐人代码
#define TDX_ID_XDLY							517			// 下单来源
#define TDX_ID_CJJJ							523			// 成交均价
#define TDX_ID_WCJSL						732			// 为成交数量
#define TDX_ID_XXLXSM						737			// 信息类型说明

#define TRADECOLOR_BUY	[NSColor colorWithCalibratedRed:1.0f green:0.0f blue:0.0f alpha:1.0f]
#define TRADECOLOR_SELL	[NSColor colorWithCalibratedRed:0.0f green:192.0/255.0f blue:0.0f alpha:1.0f]
#define HQCOLOR_DOWN	[NSColor colorWithCalibratedRed:0.0f green:192.0/255.0f blue:0.0f alpha:1.0f]
#define HQCOLOR_VOL	[NSColor colorWithCalibratedRed:192.0/255.0f green:192.0/255.0f blue:0.0f alpha:1.0f]
#define TRADECOLOR_COMMON	 [NSColor whiteColor]
#define HQCOLOR_ZIXUAN	[NSColor colorWithCalibratedRed:2.0/255.0f green:226.0/255.0f blue:244.0f/255.0f alpha:1.0f]
#define HQCOLOR_F10TITLE	[NSColor colorWithCalibratedRed:34.0/255.0f green:255.0/255.0f blue:255.0f/255.0f alpha:1.0f]
#define HQCOLOR_F10TITLE_SEL	[NSColor colorWithCalibratedRed:255.0/255.0f green:80.0/255.0f blue:80.0f/255.0f alpha:1.0f]
#define HQCOLOR_F10TEXT	[NSColor colorWithCalibratedRed:192.0/255.0f green:192.0/255.0f blue:0.0f/255.0f alpha:1.0f]
#define BGCOLOR_GRAY	[NSColor colorWithCalibratedRed:210.0/255.0f green:210.0/255.0f blue:210.0/255.0f alpha:1.0f]
#define DETAILBACKCOLOR_GRAY	[NSColor colorWithCalibratedRed:49.0/255.0f green:49.0/255.0f blue:49.0/255.0f alpha:1.0f]


#define TOOLBARSTYLE_NORMAL	0
#define TOOLBARSTYLE_POPUP	1

#define COLOR_GRID_TITLE [NSColor colorWithCalibratedRed:228/255.0f green:231/255.0f blue:236/255.0f alpha:1.0f]
#define COLOR_GRID_GRIDLINE	[NSColor colorWithCalibratedRed:200/255.0f green:203/255.0f blue:208/255.0f alpha:1.0f]
#define COLOR_GRID_LINE1		[NSColor colorWithCalibratedRed:230/255.0f green:233/255.0f blue:238/255.0f alpha:1.0f]
#define COLOR_GRID_LINE2		[NSColor colorWithCalibratedRed:211/255.0f green:214/255.0f blue:219/255.0f alpha:1.0f]
#define COLOR_GRID_BACKGROUND	 [NSColor colorWithCalibratedRed:202/255.0f green:205/255.0f blue:210/255.0f alpha:1.0f]
#define COLOR_GRID_COMMONCOLOR	[NSColor whiteColor]
#define COLOR_GRID_NORMALCOLOR	[NSColor blackColor]
#define COLOR_TRADE_SELLCOLOR	[NSColor blueColor]
#define COLOR_TRADEBAR_BACKGROUND	 [NSColor colorWithCalibratedRed:218/255.0f green:218/255.0f blue:218/255.0f alpha:1.0f]


#define OFFSETBLANK 1
#define TOPOFFSETBLANK 0.8f
#define TOOLBAR_HEIGHT  44

#define isPad (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) //判断环境是否ipad

#ifdef DEBUG_MODE
#define  MyNsLog(s) //NSLog(s)
#define  MyNsLog2(s,...)  //NSLog(@"%@",[NSString stringWithFormat:(s), ##__VA_ARGS__]);
#else
#define  MyNsLog(s) 
#define  MyNsLog2(s,...) 
#endif

//招商的标志
#define TDX_ID_CMB 
@interface macro : NSObject {
	
}


#define DATARESULT_NORMAL  1
#define DATARESULT_NETERROR  -1
#define DATARESULT_CONNERROR  -2
#define DATARESULT_TIMEOUT  0

#define HQINFO_MASK_CLOSE			0x00000001			// 前收盘价,指数
#define HQINFO_MASK_OPEN			0x00000002			// 今开盘价,指数
#define HQINFO_MASK_MAX				0x00000004			// 最高价,指数
#define HQINFO_MASK_MIN				0x00000008			// 最低价,指数
#define HQINFO_MASK_NOW				0x00000010			// 现价,最近指数
#define HQINFO_MASK_VOL				0x00000020			// 总手
#define HQINFO_MASK_NOWVOL			0x00000040			// 现手(总手差)
#define HQINFO_MASK_AMOUNT			0x00000080			// 总成交金额
#define HQINFO_MASK_INSIDE			0x00000100			// 内盘
#define HQINFO_MASK_OUTSIDE			0x00000200			// 外盘
#define HQINFO_MASK_ZGB				0x00000400			// 总股本
#define HQINFO_MASK_ACTIVECAPITAL	0x00000800			// 流通股本
#define HQINFO_MASK_JLY				0x00001000			// 净利益
#define HQINFO_MASK_JZC				0x00002000			// 净资产
#define HQINFO_MASK_HALFYEARFLAG	0x00004000			// 报告期
#define HQINFO_MASK_ZSZ				0x00008000			// 总市值
#define HQINFO_MASK_SYL				0x00010000			// 市盈率
/*
 新包头
 BYTE m_cTag; // POST标识
 BYTE m_cKeepAlive; // 存活包标志
 BYTE m_cCompressType; // 压缩模式
 BYTE m_cEncrypted; // 加密标志
 BYTE m_cUTF8Encoding; // 代码页
 DWORD m_dwTransKey; // 当前事务的传输键
 UINT64 m_i64AspSessionId; // ASPSESSIONID
 BYTE m_cSeparator; // 分割字符
 BYTE m_cNil[2]; // 保留字节(\r\n)
 
 老包头
 BYTE m_cTag; // POST标识
 BYTE m_cKeepAlive; // 存活包标志
 BYTE m_cCompressType; // 压缩模式
 BYTE m_cEncrypted; // 加密标志
 BYTE m_cUTF8Encoding; // 代码页
 int SessionId;
 BYTE m_cSeparator; // 分割字符
 BYTE m_cNil[2]; // 保留字节(\r\n)
 
 */
#define HEADER_LEN  20
#define SESSION_INDEX	9
#define PAGE_FIRSTINDEX	1000
#define PAGE_PREVIOUSINDEX	 1001
#define PAGE_NEXTINDEX	1002
#define PAGE_ENDINDEX		1003
#define PAGE_REFRESHINDEX	1004

#define ASYNC_SENDDATA_START	\
[self setExtendHead:headdata Session:dwEssion transkey:[self makedword:nIndex high:windindex]];\
tempString = [NSString  stringWithFormat:@"FUNCTYPE=0&BranchID=%@&MAC=%@&",inputSave.branchId,g_TradeComm.m_macsstr];\
[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];\
tempString = [NSString  stringWithFormat:@"F120=%@&",inputSave.accout];\
[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];\
tempString = [NSString  stringWithFormat:@"F134=%@&",[self GetJymmString]];\
[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];\
tempString = [NSString  stringWithFormat:@"F125=%i&",inputSave.accoutType];\
[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];\
tempString = [NSString  stringWithFormat:@"F121=%@&",[clientinfos GetZjzh]];\
[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];\

#define ASYNC_SENDDATA_START_DBPHZ	\
[self setExtendHead:headdata Session:dwEssion transkey:[self makedword:nIndex high:windindex]];\
tempString = [NSString  stringWithFormat:@"FUNCTYPE=0&BranchID=%@&MAC=%@&",inputSave.branchId,g_TradeComm.m_macsstr];\
[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];\
tempString = [NSString  stringWithFormat:@"F120=%@&",inputSave.accout];\
[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];\
tempString = [NSString  stringWithFormat:@"F134=%@&",[self GetJymmString]];\
[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];\
tempString = [NSString  stringWithFormat:@"F121=%@&",[clientinfos GetZjzh]];\
[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];\

#define ASYNC_SENDDATA_START_DZH	\
[self setExtendHead:headdata Session:dwEssion transkey:[self makedword:nIndex high:windindex]];\
tempString = [NSString  stringWithFormat:@"FUNCTYPE=0&BranchID=%@&MAC=%@&",inputSave.branchId,g_TradeComm.m_macsstr];\
[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];\
tempString = [NSString  stringWithFormat:@"F120=%@&",inputSave.accout];\
[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];\
tempString = [NSString  stringWithFormat:@"F134=%@&",[self GetJymmString]];\
[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];\
tempString = [NSString  stringWithFormat:@"F125=%i&",inputSave.accoutType];\
[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];\


#define ASYNC_SENDDATA_START1	\
[self setExtendHead:headdata Session:dwEssion transkey:[self makedword:nIndex high:windindex]];\
tempString = [NSString  stringWithFormat:@"FUNCTYPE=0&BranchID=%@&MAC=%@&",inputSave.branchId,g_TradeComm.m_macsstr];\
[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];\
tempString = [NSString  stringWithFormat:@"F120=%@&",inputSave.accout];\
[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];\
tempString = [NSString  stringWithFormat:@"F134=%@&",[self GetJymmString]];\
[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];\
tempString = [NSString  stringWithFormat:@"F121=%@&",[clientinfos GetZjzh]];\
[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];\

#define ASYNC_SENDDATA_START2	\
tempString = [NSString  stringWithFormat:@"FUNCTYPE=0&BranchID=1&F120=%@&MAC=%@&",inputSave.accout,g_TradeComm.m_macsstr];\
[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];\
tempString = [NSString  stringWithFormat:@"F134=%@&",[self GetJymmString]];\
[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];\
tempString = [NSString  stringWithFormat:@"F125=%i&",inputSave.nreloginaccoutType];\
[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];\
tempString = [NSString  stringWithFormat:@"F121=%@&",[clientinfos GetZjzh]];\
[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];\

#define ASYNC_SENDDATA_START_AUTHPASS	\
if(inputSave.authtype>0)\
{\
	tempString = [NSString  stringWithFormat:@"F1210=%i&",inputSave.authtype];\
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];\
	tempString = [NSString  stringWithFormat:@"F1211=%@&",[self GetauthpassString]];\
	[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];\
}\

#define ASYNC_SENDDATA_START_GDDM	\
tempString = [NSString  stringWithFormat:@"F123=%@&",inputSave.gddm];\
[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];\

#define ASYNC_SENDDATA_START_YHDM	\
tempString = [NSString  stringWithFormat:@"F1101=%@&",inputSave.yhdm];\
[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];\


#define ASYNC_SENDDATA_START_WTFS	\
tempString = [NSString  stringWithFormat:@"F110=%@&",inputSave.wtfs];\
[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];\

#define ASYNC_SENDDATA_START_LSDATE	\
tempString = [NSString stringWithFormat:@"F126=%i&",saveDate.nStartDate];\
[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];\
tempString = [NSString stringWithFormat:@"F127=%i&",saveDate.nEndDate];\
[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];\

#define ASYNC_SENDDATA_START_PAGE	\
[self setExtendHead:headdata Session:dwEssion transkey:[self makedword:pageindex high:windindex]];\
tempString = [NSString  stringWithFormat:@"FUNCTYPE=%d&MAC=%@&",0,g_TradeComm.m_macsstr];\
[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];\
tempString = [NSString  stringWithFormat:@"BranchID=%@&",inputSave.branchId];\
[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];\
tempString = [NSString  stringWithFormat:@"F120=%@&",inputSave.accout];\
[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];\
tempString = [NSString  stringWithFormat:@"F134=%@&",[self GetJymmString]];\
[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];\
tempString = [NSString  stringWithFormat:@"F125=%i&",inputSave.accoutType];\
[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];\
tempString = [NSString  stringWithFormat:@"F121=%@&",[clientinfos GetZjzh]];\
[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];\

#define ASYNC_SENDDATA_PAGE	\
[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];\
tempString = [NSString stringWithFormat:@"F1286=%@&",posstr];\
[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];\
tempString = [NSString stringWithFormat:@"F1287=%i&",startindex];\
[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];\
tempString = [NSString stringWithFormat:@"F1288=%i&",reqlines];\
[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];\
tempString = [NSString stringWithFormat:@"F1289=%i&",totleline];\
[newdata appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];\





#ifdef IMAC_LOG

#define LogIt(xxindex) \
NSString *logstr=[NSString stringWithFormat:@" %i  siteindex=%i",xxindex,eGetData.clientinfos.localjysites.nlastindex];\
[eGetData writeLog:logstr];\

#define LogIt2(xxindex) \
NSString *logstr=[NSString stringWithFormat:@" %i  siteindex=%i",xxindex,clientinfos.localjysites.nlastindex];\
[self writeLog:logstr];\

#define LogIt3(strinfo) \
[self writeLog:strinfo];\

#define LogIt4(strinfo) \
[eGetData writeLog:strinfo];\

#define ASYNC_SENDDATA_END	\
if(m_cEncrypted == YES)\
{\
int _length = [newdata length];\
char * temp2char = malloc(_length*2);\
memset(temp2char,0,_length*2);\
memcpy(temp2char, [newdata bytes], _length);\
unsigned char * pbySrc = (unsigned char *)temp2char;\
int _length1 = (_length+23)/24 * 24;\
NSData *data =[[NSData alloc] initWithBytes:pbySrc length:_length1];\
[GTMBase64 encodeData:data]; \
newEncrypt(pbySrc, _length1);\
[headdata appendBytes:pbySrc length:_length1];\
[data release];\
free(temp2char);\
}\
else\
[headdata appendBytes:[newdata bytes] length:[newdata length]];\
[g_TradeComm AsyncSendData:headdata length:[headdata length] withobjIndex:windindex withreqIndex:nIndex];\


#define ASYNC_SENDDATA_END_PAGE	\
if(m_cEncrypted == YES)\
{\
int _length = [newdata length];\
char * temp2char = malloc(_length*2);\
memset(temp2char,0,_length*2);\
memcpy(temp2char, [newdata bytes], _length);\
unsigned char * pbySrc = (unsigned char *)temp2char;\
int _length1 = (_length+23)/24 * 24;\
NSData *data =[[NSData alloc] initWithBytes:pbySrc length:_length1];\
[GTMBase64 encodeData:data]; \
newEncrypt(pbySrc, _length1);\
[headdata appendBytes:pbySrc length:_length1];\
[data release];\
free(temp2char);\
}\
else\
[headdata appendBytes:[newdata bytes] length:[newdata length]];\
[g_TradeComm AsyncSendData:headdata length:[headdata length] withobjIndex:windindex withreqIndex:pageindex];\


#define ASYNC_SENDDATA_END1	\
if(m_cEncrypted == YES)\
{\
int _length = [newdata length];\
char * temp2char = malloc(_length*2);\
memset(temp2char,0,_length*2);\
memcpy(temp2char, [newdata bytes], _length);\
unsigned char * pbySrc = (unsigned char *)temp2char;\
int _length1 = (_length+23)/24 * 24;\
NSData *data =[[NSData alloc] initWithBytes:pbySrc length:_length1];\
[GTMBase64 encodeData:data]; \
newEncrypt(pbySrc, _length1);\
[headdata appendBytes:pbySrc length:_length1];\
[data release];\
free(temp2char);\
}\
else\
[headdata appendBytes:[newdata bytes] length:[newdata length]];\

#else

#define LogIt(xxindex) \

#define LogIt2(xxindex) \

#define LogIt3(strinfo) \

#define LogIt4(strinfo) \

#define ASYNC_SENDDATA_END	\
if(m_cEncrypted == YES)\
{\
int _length = [newdata length];\
char * temp2char = malloc(_length*2);\
memset(temp2char,0,_length*2);\
memcpy(temp2char, [newdata bytes], _length);\
unsigned char * pbySrc = (unsigned char *)temp2char;\
int _length1 = (_length+23)/24 * 24;\
NSData *data =[[NSData alloc] initWithBytes:pbySrc length:_length1];\
[GTMBase64 encodeData:data]; \
newEncrypt(pbySrc, _length1);\
[headdata appendBytes:pbySrc length:_length1];\
[data release];\
free(temp2char);\
}\
else\
[headdata appendBytes:[newdata bytes] length:[newdata length]];\
[g_TradeComm AsyncSendData:headdata length:[headdata length] withobjIndex:windindex withreqIndex:nIndex];\


#define ASYNC_SENDDATA_END1	\
if(m_cEncrypted == YES)\
{\
int _length = [newdata length];\
char * temp2char = malloc(_length*2);\
memset(temp2char,0,_length*2);\
memcpy(temp2char, [newdata bytes], _length);\
unsigned char * pbySrc = (unsigned char *)temp2char;\
int _length1 = (_length+23)/24 * 24;\
NSData *data =[[NSData alloc] initWithBytes:pbySrc length:_length1];\
[GTMBase64 encodeData:data]; \
newEncrypt(pbySrc, _length1);\
[headdata appendBytes:pbySrc length:_length1];\
[data release];\
free(temp2char);\
}\
else\
[headdata appendBytes:[newdata bytes] length:[newdata length]];\

#define ASYNC_SENDDATA_END_PAGE	\
if(m_cEncrypted == YES)\
{\
int _length = [newdata length];\
char * temp2char = malloc(_length*2);\
memset(temp2char,0,_length*2);\
memcpy(temp2char, [newdata bytes], _length);\
unsigned char * pbySrc = (unsigned char *)temp2char;\
int _length1 = (_length+23)/24 * 24;\
NSData *data =[[NSData alloc] initWithBytes:pbySrc length:_length1];\
[GTMBase64 encodeData:data]; \
newEncrypt(pbySrc, _length1);\
[headdata appendBytes:pbySrc length:_length1];\
[data release];\
free(temp2char);\
}\
else\
[headdata appendBytes:[newdata bytes] length:[newdata length]];\
[g_TradeComm AsyncSendData:headdata length:[headdata length] withobjIndex:windindex withreqIndex:pageindex];\


#endif



#define View_Animation_Out	\
CATransition *animation = [CATransition animation];\
animation.duration = 0.3f;\
animation.timingFunction = UIViewAnimationCurveEaseInOut;\
animation.fillMode = kCAFillModeForwards;\
animation.type = kCATransitionPush;\
animation.subtype = kCATransitionFromBottom;\

#define View_Animation_In \
CATransition *animation = [CATransition animation];\
animation.duration = 0.3f;\
animation.timingFunction = UIViewAnimationCurveEaseInOut;\
animation.fillMode = kCAFillModeForwards;\
animation.type = kCATransitionMoveIn;\
animation.subtype = kCATransitionFromTop;\


#define MAX_ANSBUFFER (64*1024)
#define KeyBoard_DONE_KEY	 @"Return-Key"
#define KeyBoard_DONE_Title	 @"确定"

#define TEXT_FONT2 20.0f
#define TEXT_FONT 18.0f
#define TEXT_FONT3 16.0f
#define TITLE_FONT2 16.0f
#define TITLE_FONT 18.0f
#define LABEL_FONT	17.0F

#define tableRedColor [NSColor colorWithCalibratedRed::0.6f green:0.0f blue:0.0f alpha:1.0f]
#define infoTextDataColor [NSColor colorWithCalibratedRed::0.701f green:0.701f blue:0.701f alpha:1.0f]
#define f10TextDataColor [NSColor colorWithCalibratedRed::0.243f green:0.243f blue:0.243f alpha:1.0f]

#define SPAN_GRID  0.5f

#define ADDBUT_OKCANCEL	\
if (m_bButtonshowflag && m_bfirstflag) {\
UIButton * lastbut=(UIButton * )[cell viewWithTag:300];\
if(lastbut)\
	[lastbut removeFromSuperview];\
lastbut=(UIButton * )[cell viewWithTag:301];\
if(lastbut)\
	[lastbut removeFromSuperview];\
UIButton * tempButton = [UIButton buttonWithType:UIButtonTypeCustom];\
[tempButton setTitle:@"确 定" forState:UIControlStateNormal];\
[tempButton setTitleColor:[UIColor blackColor]  forState:UIControlStateNormal];\
[tempButton setBackgroundImage:[UIImage imageNamed:@"queding3.png"]  forState:UIControlStateNormal];\
[tempButton setBackgroundImage:[UIImage imageNamed:@"queding4.png"]  forState:UIControlStateHighlighted];\
[tempButton addTarget:self action:@selector(doneButtonClick) forControlEvents:UIControlEventTouchUpInside];\
tempButton.frame = CGRectMake(self.center.x-100-20, 4, 100, 39);\
tempButton.tag=300;\
[cell.contentView addSubview:tempButton];\
tempButton = [UIButton buttonWithType:UIButtonTypeCustom];\
[tempButton setTitle:@"取 消" forState:UIControlStateNormal];\
[tempButton setTitleColor:[UIColor blackColor]  forState:UIControlStateNormal];\
[tempButton setBackgroundImage:[UIImage imageNamed:@"queding3.png"]  forState:UIControlStateNormal];\
[tempButton setBackgroundImage:[UIImage imageNamed:@"queding4.png"]  forState:UIControlStateHighlighted];\
[tempButton addTarget:self action:@selector(cancelButtonClick) forControlEvents:UIControlEventTouchUpInside];\
tempButton.frame = CGRectMake(self.center.x+20, 4, 100, 38);\
tempButton.tag=301;\
[cell.contentView addSubview:tempButton];\
}\

#define ANIMATE_PAGE_DOWN	\
[UIView beginAnimations:@"animationID" context:nil];\
[UIView setAnimationDuration:0.5f];\
[UIView setAnimationCurve:UIViewAnimationCurveEaseInOut];\
[UIView setAnimationTransition:UIViewAnimationTransitionCurlUp forView:self cache:YES];\
[UIView commitAnimations];\

#define ANIMATE_PAGE_UP	\
[UIView beginAnimations:@"animationID" context:nil];\
[UIView setAnimationDuration:0.5f];\
[UIView setAnimationCurve:UIViewAnimationCurveEaseInOut];\
[UIView setAnimationTransition:UIViewAnimationTransitionCurlDown forView:self cache:YES];\
[UIView commitAnimations];\


#define ANIMATE_RIGHTTOLEFT_IN		\
CATransition *animation = [CATransition animation];\
animation.duration = 0.3f;\
animation.timingFunction = UIViewAnimationCurveEaseInOut;\
animation.fillMode = kCAFillModeForwards;\
animation.type = kCATransitionPush;\
animation.subtype = kCATransitionFromRight;\

#define ANIMATE_LEFTTORIGHT_OUT	\
CATransition *animation = [CATransition animation];\
animation.duration = 0.3f;\
animation.timingFunction = UIViewAnimationCurveEaseInOut;\
animation.fillMode = kCAFillModeForwards;\
animation.type = kCATransitionPush;\
animation.subtype = kCATransitionFromLeft;\

#define ANIMATE_LEFTTORIGHT_IN		\
CATransition *animation = [CATransition animation];\
animation.duration = 0.5f;\
animation.timingFunction = UIViewAnimationCurveEaseInOut;\
animation.fillMode = kCAFillModeForwards;\
animation.type = kCATransitionMoveIn;\
animation.subtype = kCATransitionFromLeft;\


#define DROPDOWN_SELMORJJ	\
CGRect jjdmrect=[jjdmText frame];\
UIButton *wysj = [UIButton buttonWithType:UIButtonTypeCustom];\
[wysj setFrame:CGRectMake(jjdmrect.origin.x+jjdmrect.size.width+5, 5, 43, 32)];\
[wysj setBackgroundImage:[UIImage imageNamed:@"dropdown.png"]  forState:UIControlStateNormal];\
[wysj setBackgroundImage:[UIImage imageNamed:@"dropdown2.png"]  forState:UIControlStateHighlighted];\
[wysj addTarget:self action:@selector(selmorejj) forControlEvents:UIControlEventTouchUpInside];\
[wysj setTitle:@"" forState:UIControlStateNormal];\
[cell.contentView addSubview:wysj];\

#define JJNAME_AUTORESIZE	\
CGSize strsize;\
CGFloat nfontsize=LABEL_FONT;\
while(nfontsize>10)\
{\
	strsize=[jjnameLable.text sizeWithFont:[UIFont systemFontOfSize:nfontsize]];\
	if(strsize.width>m_nnamewidth)\
		nfontsize--;\
	else \
		break;\
};\
jjnameLable.font=[UIFont systemFontOfSize:nfontsize];\


#define CDTIP_ZTZQ_DLL @"\r\r温馨提示：如属于集合竞价时段或委托已成交，\r交易所将不允许撤单"

#define CHECKINDEX(A) (A>=0 && A<[tempArray count])
@end
