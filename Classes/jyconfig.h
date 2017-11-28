//
//  jyconfig.h
//  tdxiphone
//
//  Created by tdx on 11-3-16.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "GDataDefines.h"
#import "macro.h"


@interface TradeSite : NSObject<NSCoding>  //交易中心
{
	int   nport;//端口
	int   weight;//权重
	int hosttype;// 站点类型
	BOOL  tradever;//交易版本
	NSString *sname;//站点名称
	NSString *ip;//ip
	NSString *yybids;//附近营业部id
	BOOL  bfindbest;//是否已查找过最快
	double      ntime;//最快时间
	double      stime;//响应时间
}
@property(nonatomic) BOOL bfindbest;
@property(nonatomic) double ntime;
@property(nonatomic) double stime;
@property(nonatomic) int nport;
@property(nonatomic) int weight;
@property(nonatomic) int hosttype;
@property(nonatomic,retain) NSString *sname;
@property(nonatomic,retain) NSString *ip;
@property(nonatomic) BOOL tradever;
@property(nonatomic,retain) NSString *yybids;

-(TradeSite *)deepcopy;
@end

@interface LoginMode : NSObject
{
	int  zhlx;//账户类型
	int  hosttype;//站点类型
	NSString *zhdesc;//账户类型描述
}

@property(nonatomic) int zhlx;
@property(nonatomic) int hosttype;
@property(nonatomic,retain) NSString *zhdesc;

@end

@interface Yybs : NSObject
{
	int   autofill;
	int   noprefix;
	int   hosttype;
	NSString *yybid;
	NSString *yybname;
	NSString *yybprefix;
}

@property(nonatomic) int autofill;
@property(nonatomic) int noprefix;
@property(nonatomic) int hosttype;
@property(nonatomic,retain) NSString *yybid;
@property(nonatomic,retain) NSString *yybname;
@property(nonatomic,retain) NSString *yybprefix;

@end

@interface SecureMode : NSObject
{
	int ntype;
	NSString *sname;
}
@property(nonatomic) int ntype;
@property(nonatomic,retain) NSString *sname;
@end

@interface Misc : NSObject
{
	int swapcombo;
	int  coloryzm;
	int zjzhmaxlen;
	int mustdigitpwd;
	int  mustaccountlen;
	int  maxaccountlen;
	int  aqfscombo;
	int  hascxmode;
	int nyybweight;
	int  vipxmb;
	BOOL bsupportlimitmode;
	NSString *urlapplyAuthpass;
	NSString *urlmodifyAuthpass;
}
@property (nonatomic) int swapcombo;
@property(nonatomic) int coloryzm;
@property(nonatomic) int zjzhmaxlen;
@property(nonatomic) int mustdigitpwd;
@property(nonatomic) int mustaccountlen;
@property(nonatomic) int maxaccountlen;
@property(nonatomic) int aqfscombo;
@property(nonatomic) int hascxmode;
@property(nonatomic) int nyybweight;
@property(nonatomic) int vipxmb;
@property(nonatomic) BOOL bsupportlimitmode;
@property(nonatomic,retain) NSString *urlapplyAuthpass;
@property(nonatomic,retain) NSString *urlmodifyAuthpass;
@end

@interface YybRange : NSObject
{
	int id;
	int nRealNum;
	int  nstart[10];
	int  nend[10];
}
@property(nonatomic) int id;
@property(nonatomic) int nRealNum;

-(void)SetStartRange:(int)index withvalue:(int)value;
-(void)SetEndRange:(int)index withvalue:(int)value;
-(int)GetStartRange:(int)index;
-(int)GetEndRange:(int)index;
@end


@interface Vyyb : NSObject //虚拟营业部
{
	int maxaccountlen;
	int mustaccountlen;
	int headlen;
	NSMutableArray *yybrange;//YybRange
}

@property(nonatomic) int maxaccountlen;
@property(nonatomic) int mustaccountlen;
@property(nonatomic) int headlen;
@property(nonatomic,retain) NSMutableArray *yybrange;

@end

@interface LoginSet : NSObject
{
	int buse;
	int pwdmaxlength;
	int pwdtype;
	int authmaxlength;
	int authtype;
	int maxzhlen;
}

@property(nonatomic) int buse;
@property(nonatomic) int pwdmaxlength;
@property(nonatomic) int pwdtype;
@property(nonatomic) int authmaxlength;
@property(nonatomic) int authtype;
@property(nonatomic) int maxzhlen;

@end

@interface NetWorkConfig : NSObject
{
	int  njobtimeout;//job超时时间
	int  nconnecttimeout;//连接超时时间
}

@property(nonatomic) int njobtimeout;
@property(nonatomic) int nconnecttimeout;

@end

@interface HqParamInfo : NSObject<NSCoding>
{
	BOOL bautocheckfast;//是否自动查找最快
	BOOL bautorefreshhq;//自动刷新行情
	int    nhqrefreshspan;//行情刷新间隔
	int    nsortrefreshspan;//排序刷新间隔
	int	 nfontsize;//字体大小
    int  njylockspan;
}
@property(nonatomic) int njylockspan;
@property(nonatomic) BOOL bautocheckfast;
@property(nonatomic) BOOL bautorefreshhq;
@property(nonatomic) int nhqrefreshspan;
@property(nonatomic) int nfontsize;
@property(nonatomic) int nsortrefreshspan;

-(HqParamInfo *)deepcopy;
@end

@interface ZxLinks : NSObject<NSCoding>
{
	NSString *zxname;
	NSString *url;
}

@property(nonatomic,retain) NSString *zxname;
@property(nonatomic,retain) NSString *url;

-(ZxLinks *)deepcopy;
@end

@interface ZxLinkInfo : NSObject<NSCoding>
{
	ZxLinks *mainlink;
	NSMutableArray *linkItems;//ZxLinks
}

@property(nonatomic,retain) ZxLinks *mainlink;
@property(nonatomic,retain) NSMutableArray *linkItems;

-(void)releaselinks;
@end

@interface JyParamInfo : NSObject<NSCoding>
{
	int  nlockscreenspan;//交易闲置x分钟后锁定
}

@property(nonatomic) int nlockscreenspan;

-(JyParamInfo *)deepcopy;
@end


@interface VersionParam: NSObject<NSCoding>
{
	int versionID;
	int hostUpdate;
	int riskUpdate;
	int serviceUpdate;
	int zxUpdate;
	int blzdone;
	int blzdtwo;
}

@property int versionID;
@property int hostUpdate;
@property int riskUpdate;
@property int serviceUpdate;
@property int zxUpdate;
@property int blzdone;
@property int blzdtwo;

-(VersionParam *)deepcopy;

@end

@interface StyleParams: NSObject<NSCoding>
{
	int colorStyle;
	int paomaStyle;
	int lanStyle;
	int backStyle;
	int blzdone;
	int blzdtwo;
}

@property int colorStyle;
@property int paomaStyle;
@property int lanStyle;
@property int backStyle;
@property int blzdone;
@property int blzdtwo;

-(StyleParams *)deepcopy;

@end

@interface JyConfig : NSObject {

	int		qsid;
	BOOL       bfindbesthqSite;//是否查找最快行情站点
	BOOL       bfindbestSite;//是否查找最快站点
	BOOL       bfindbestVipSite;//是否查找最快站点
	NSString   *fversion;
	NSString   *assversion;
    NSString   *fversion_mac;
    NSString   *assversion_mac;
	NSString   *updatetag;
	NSString	 *qsmc;
	NSString	 *classfication;
	NSString	 *qsjc;
	NSMutableArray  *hqsite;//TradeSite
	NSMutableArray  *tradesite;//TradeSite
	NSMutableArray  *viptradesite;//TradeSite
	NSMutableArray  *loginmode;//LoginMode
	NSMutableArray  *yybs;//Yybs
	NSMutableArray  *secure;//SecureMode
	NSMutableArray *gridCellInfoArray;
	Misc  *pmisc;
	Vyyb *vyybs;
	LoginSet   *loginsets;//登录设置
	NetWorkConfig *network;//网络设置
	HqParamInfo  *hqParams;//行情参数设置
	ZxLinkInfo  *zxLinks;//资讯链接
	JyParamInfo *jyParams;//交易参数设置
	VersionParam * versionParams;//版本更新参数
	StyleParams * styleParams;//风格参数
}
@property(nonatomic) int qsid;
@property(nonatomic) BOOL bfindbesthqSite;
@property(nonatomic) BOOL bfindbestSite;
@property(nonatomic) BOOL bfindbestVipSite;
@property(nonatomic,retain) NSString *fversion;
@property(nonatomic,retain) NSString *assversion;
@property(nonatomic,retain) NSString *fversion_mac;
@property(nonatomic,retain) NSString *assversion_mac;
@property(nonatomic,retain) NSString *updatetag;
@property(nonatomic,retain) NSString *qsmc;
@property(nonatomic,retain) NSString *classfication;
@property(nonatomic,retain) NSString *qsjc;
@property(nonatomic,retain) NSMutableArray *hqsite;
@property(nonatomic,retain) NSMutableArray *tradesite;
@property(nonatomic,retain) NSMutableArray *loginmode;
@property(nonatomic,retain) NSMutableArray *viptradesite;
@property(nonatomic,retain) NSMutableArray *yybs;
@property(nonatomic,retain) NSMutableArray *secure;
@property(nonatomic,retain) NSMutableArray *gridCellInfoArray;
@property(nonatomic,retain) Misc *pmisc;
@property(nonatomic,retain) Vyyb *vyybs;
@property(nonatomic,retain) LoginSet *loginsets;
@property(nonatomic,retain) NetWorkConfig *network;
@property(nonatomic,retain) HqParamInfo  *hqParams;
@property(nonatomic,retain) ZxLinkInfo  *zxLinks;
@property(nonatomic,retain) JyParamInfo *jyParams;
@property(nonatomic,retain) VersionParam * versionParams;
@property(nonatomic,retain)StyleParams * styleParams;
@end

@interface QsConfig : NSObject
{
	NSMutableArray *jyconfigs;//JyConfig
    NSString *logcachefile;
}

@property(nonatomic,retain) NSMutableArray *jyconfigs;
-(void)loadjyconfig;

@end

