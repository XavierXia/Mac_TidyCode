//
//  jyconfig.m
//  tdxiphone
//
//  Created by tdx on 11-3-16.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "jyconfig.h"
#import "struct.h"

@implementation TradeSite

@synthesize sname,ip,nport,weight,tradever,hosttype,yybids,bfindbest,ntime,stime;

-(id)init
{
	self=[super init];
	if(self)
	{
		sname=nil;
		ip=nil;
		yybids=nil;
		bfindbest=NO;
		ntime=-1;
		stime= -1;
        
	}
	return self;
}

-(void) dealloc
{
	RELEASEOBJ(sname)
	RELEASEOBJ(ip)
	RELEASEOBJ(yybids)
	[super	 dealloc];
}

-(void)encodeWithCoder:(NSCoder *)encoder
{
	[encoder encodeInt:nport  forKey:@"TradeSitenport"];
	[encoder encodeInt:weight  forKey:@"TradeSiteweight"];
	[encoder encodeInt:hosttype  forKey:@"TradeSitehosttype"];
	[encoder encodeBool:tradever  forKey:@"TradeSitetradever"];	
	[encoder encodeObject:sname forKey:@"TradeSitesname"];
	[encoder encodeObject:ip	forKey:@"TradeSiteip"];
	[encoder encodeObject:yybids forKey:@"TradeSiteyybids"];
}

-(id)initWithCoder:(NSCoder *)aDecoder
{
	self=[super init];
	if(self)
	{
		nport=[aDecoder decodeIntForKey:@"TradeSitenport"];
		weight=[aDecoder decodeIntForKey:@"TradeSiteweight"];
		hosttype=[aDecoder decodeIntForKey:@"TradeSitehosttype"];
		tradever=[aDecoder decodeBoolForKey:@"TradeSitetradever"];
		sname=[[aDecoder decodeObjectForKey:@"TradeSitesname"]retain];
		ip=[[aDecoder decodeObjectForKey:@"TradeSiteip"]retain];
		yybids=[[aDecoder decodeObjectForKey:@"TradeSiteyybids"]retain];
	}
	
	return self;
}

-(TradeSite *)deepcopy
{
	TradeSite *psite=[[TradeSite alloc]init];
	
	psite.nport=nport;
	psite.weight=weight;
	psite.hosttype=hosttype;
	psite.tradever=tradever;
	psite.sname=[[NSString alloc] initWithFormat:@"%@",sname];
	[psite.sname release];
	psite.ip=[[NSString alloc] initWithFormat:@"%@",ip];
	[psite.ip release];
	psite.yybids=[[NSString alloc] initWithFormat:@"%@",yybids];
	[psite.yybids release];
	
	return psite;
}

@end

@implementation LoginMode

@synthesize zhlx,hosttype,zhdesc;

-(id)init
{
	self=[super init];
	if(self)
	{
		zhlx=8;
		hosttype=0;
		zhdesc=nil;
	}
	return self;
}

-(void)dealloc
{
	RELEASEOBJ(zhdesc)
	[super dealloc];
}

@end

@implementation Yybs

@synthesize autofill,noprefix,hosttype,yybid,yybname,yybprefix;

-(id)init
{
	self=[super init];
	if(self)
	{
		yybid=nil;
		yybname=nil;
		yybprefix=nil;
	}
	return self;
}

-(void)dealloc
{
	RELEASEOBJ(yybid)
	RELEASEOBJ(yybname)
	RELEASEOBJ(yybprefix)
	[super dealloc];
}

@end


@implementation SecureMode

@synthesize ntype,sname;

-(id)init
{
	self=[super init];
	if(self)
	{
		sname=nil;
		ntype=0;
	}
	return self;
}

-(void)dealloc
{
	RELEASEOBJ(sname)
	[super dealloc];
}
@end

@implementation Misc

@synthesize swapcombo,coloryzm,zjzhmaxlen,mustdigitpwd,mustaccountlen,maxaccountlen,aqfscombo,hascxmode;
@synthesize nyybweight,bsupportlimitmode,urlapplyAuthpass,urlmodifyAuthpass,vipxmb;

-(id)init
{
	self=[super init];
	if(self)
	{
		urlapplyAuthpass=nil;
		urlmodifyAuthpass=nil;
	}
	return self;
}

-(void)dealloc
{
	RELEASEOBJ(urlapplyAuthpass)
	RELEASEOBJ(urlmodifyAuthpass)
	[super dealloc];
}
@end

@implementation YybRange

@synthesize nRealNum,id;


-(id)init
{
	self=[super init];
	if(self)
	{
		nRealNum=0;
	}
	return self;
}

-(void)dealloc
{
	[super dealloc];
}

-(void)SetStartRange:(int)index withvalue:(int)value
{
	if(index<0 || index>=10)
		return;
	nstart[index]=value;
}

-(void)SetEndRange:(int)index withvalue:(int)value
{
	if(index<0 || index>=10)
		return;
	nend[index]=value;
}

-(int)GetStartRange:(int)index
{
	if(index<0 || index>=10)
		return 0;
	return nstart[index];
}

-(int)GetEndRange:(int)index
{
	if(index<0 || index>=10)
		return 0;
	return nend[index];
}
@end


@implementation Vyyb

@synthesize maxaccountlen,mustaccountlen,headlen,yybrange;

-(id)init
{
	self=[super init];
	if(self)
	{
		yybrange=nil;
	}
	return self;
}

-(void)dealloc
{
	if(yybrange)
	{
		for(YybRange *prange in yybrange)
		{
			RELEASEOBJ(prange)
		}
		[yybrange removeAllObjects];
	}
	RELEASEOBJ(yybrange)
	[super dealloc];
}
@end

@implementation LoginSet

@synthesize buse,pwdmaxlength,pwdtype,authmaxlength,maxzhlen,authtype;

-(id)init
{
	self=[super init];
	return self;
}

-(void)dealloc
{
	[super dealloc];
}
@end

@implementation NetWorkConfig

@synthesize njobtimeout,nconnecttimeout;

-(id)init
{
	self=[super init];
	if(self)
	{
		
	}
	return self;
}

-(void)dealloc
{
	[super dealloc];
}

@end

@implementation HqParamInfo

@synthesize bautorefreshhq,nhqrefreshspan,nfontsize,bautocheckfast,nsortrefreshspan,njylockspan;

-(id)init
{
	self=[super init];
	if(self)
	{
		bautorefreshhq=YES;
		nhqrefreshspan=10;
		nfontsize=16;
		nsortrefreshspan=10;
		bautocheckfast=YES;
        njylockspan=30;
	}
	return self;
}


-(void)dealloc
{
	
	[super dealloc];
}

-(void)encodeWithCoder:(NSCoder *)encoder
{
	[encoder encodeBool:bautocheckfast  forKey:@"HqParamInfobautocheckfast"];
	[encoder encodeBool:bautorefreshhq  forKey:@"HqParamInfobautorefreshhq"];
	[encoder encodeInt:nhqrefreshspan  forKey:@"HqParamInfonhqrefreshspan"];
	[encoder encodeInt:nsortrefreshspan  forKey:@"HqParamInfonsortrefreshspan"];
	[encoder encodeInt:nfontsize  forKey:@"HqParamInfonfontsize"];
    [encoder encodeInt:njylockspan  forKey:@"HqParamInfonjylockspan"];
}

-(id)initWithCoder:(NSCoder *)aDecoder
{
	self=[super init];
	if(self)
	{
		bautocheckfast=[aDecoder decodeBoolForKey:@"HqParamInfobautocheckfast"];
		bautorefreshhq=[aDecoder decodeBoolForKey:@"HqParamInfobautorefreshhq"];
		nhqrefreshspan=[aDecoder decodeIntForKey:@"HqParamInfonhqrefreshspan"];
		nsortrefreshspan=[aDecoder decodeIntForKey:@"HqParamInfonsortrefreshspan"];
		nfontsize=[aDecoder decodeIntForKey:@"HqParamInfonfontsize"];
        njylockspan=[aDecoder decodeIntForKey:@"HqParamInfonjylockspan"];
        if(njylockspan<1)
            njylockspan=1;
	}
	
	return self;
}

-(HqParamInfo *)deepcopy
{
	HqParamInfo *pHqParam=[[HqParamInfo alloc]init];
	
	pHqParam.bautocheckfast=bautocheckfast;
	pHqParam.bautorefreshhq=bautorefreshhq;
	pHqParam.nhqrefreshspan=nhqrefreshspan;
	pHqParam.nsortrefreshspan=nsortrefreshspan;
	pHqParam.nfontsize=nfontsize;
    pHqParam.njylockspan=njylockspan;
	if(pHqParam.njylockspan<1)
        pHqParam.njylockspan=1;
	return pHqParam;
}
@end

@implementation ZxLinks

@synthesize zxname,url;

-(id)init 
{
	self=[super init];
	if(self)
	{
		zxname=nil;
		url=nil;
	}
	return self;
}

-(void)dealloc
{
	RELEASEOBJ(zxname)
	RELEASEOBJ(url)
	[super dealloc];
}


-(void)encodeWithCoder:(NSCoder *)encoder
{
	[encoder encodeObject:zxname  forKey:@"ZxLinksname"];
	[encoder encodeObject:url  forKey:@"ZxLinksurl"];
}

-(id)initWithCoder:(NSCoder *)aDecoder
{
	self=[super init];
	if(self)
	{
		zxname=[[aDecoder decodeObjectForKey:@"ZxLinksname"] retain];
		url=[[aDecoder decodeObjectForKey:@"ZxLinksname"] retain];
	}
	
	
	return self;
}

-(ZxLinks *)deepcopy
{
	ZxLinks *pLink=[[ZxLinks alloc]init];
	
	pLink.zxname=[[NSString alloc] initWithFormat:@"%@",zxname];
	[pLink.zxname release];
	pLink.url=[[NSString alloc] initWithFormat:@"%@",url];
	[pLink.url release];
	return pLink;
}
@end

@implementation ZxLinkInfo

@synthesize mainlink,linkItems;

-(id)init 
{
	self=[super init];
	if(self)
	{
		mainlink=nil;
		linkItems=nil;
	}
	return self;
}

-(void)dealloc
{
	[self releaselinks];
	[super dealloc];
}

-(void)releaselinks
{
	RELEASEOBJ(mainlink)
	if(linkItems)
	{
		for(ZxLinks *plink in linkItems)
		{
			RELEASEOBJ(plink)
		}
		[linkItems removeAllObjects];
	}
	RELEASEOBJ(linkItems)
}

-(void)encodeWithCoder:(NSCoder *)encoder
{
	[encoder encodeObject:mainlink  forKey:@"ZxLinkInfomainlink"];
	[encoder encodeObject:linkItems  forKey:@"ZxLinkInfolinkItems"];
}

-(id)initWithCoder:(NSCoder *)aDecoder
{
	self=[super init];
	if(self)
	{
		mainlink=[[aDecoder decodeObjectForKey:@"ZxLinkInfomainlink"] retain];
		linkItems=[[aDecoder decodeObjectForKey:@"ZxLinkInfolinkItems"] retain];
	}
	
	return self;
}

@end

@implementation JyParamInfo

@synthesize nlockscreenspan;

-(id)init
{
	self=[super init];
	if(self)
	{
		nlockscreenspan=30;
	}
	return self;
}


-(void)dealloc
{
	
	[super dealloc];
}

-(void)encodeWithCoder:(NSCoder *)encoder
{
	[encoder encodeInt:nlockscreenspan  forKey:@"JyParamInfonhqrefreshspan"];
}

-(id)initWithCoder:(NSCoder *)aDecoder
{
	self=[super init];
	if(self)
	{
		nlockscreenspan=[aDecoder decodeIntForKey:@"JyParamInfonhqrefreshspan"];
	}
	
	return self;
}

-(JyParamInfo *)deepcopy
{
	JyParamInfo *pJyParam=[[JyParamInfo alloc]init];
	
	pJyParam.nlockscreenspan=nlockscreenspan;
	
	return pJyParam;
}


@end

@implementation VersionParam

@synthesize versionID,hostUpdate,riskUpdate,serviceUpdate,zxUpdate,blzdone,blzdtwo;

- (id)init
{
	if (self = [super init])
	{
		versionID =0 ;
		hostUpdate=0;
		riskUpdate=0;
		serviceUpdate=0;
		zxUpdate=0;
		blzdone=0;
		blzdtwo=0;
	}
	
	return self;
}

-(void)encodeWithCoder:(NSCoder *)encoder
{
	[encoder encodeInt:versionID  forKey:@"VersionParamversionID"];
	[encoder encodeInt:hostUpdate  forKey:@"VersionParamhostUpdate"];
	[encoder encodeInt:riskUpdate  forKey:@"VersionParamriskUpdate"];
	[encoder encodeInt:serviceUpdate  forKey:@"VersionParamserviceUpdate"];
	[encoder encodeInt:zxUpdate  forKey:@"VersionParamzxUpdate"];
	[encoder encodeInt:blzdone  forKey:@"VersionParamblzdone"];
	[encoder encodeInt:blzdtwo  forKey:@"VersionParamblzdtwo"];
	
}

-(id)initWithCoder:(NSCoder *)aDecoder
{
	self=[super init];
	if(self)
	{
		versionID=[aDecoder decodeIntForKey:@"VersionParamversionID"];
		hostUpdate=[aDecoder decodeIntForKey:@"VersionParamhostUpdate"];
		riskUpdate=[aDecoder decodeIntForKey:@"VersionParamriskUpdate"];
		serviceUpdate=[aDecoder decodeIntForKey:@"VersionParamserviceUpdate"];
		zxUpdate=[aDecoder decodeIntForKey:@"VersionParamzxUpdate"];
		blzdone=[aDecoder decodeIntForKey:@"VersionParamblzdone"];
		blzdtwo=[aDecoder decodeIntForKey:@"VersionParamblzdtwo"];
	}
	
	return self;
}

-(VersionParam *)deepcopy
{
	VersionParam *pVersionParam=[[VersionParam alloc]init] ;
	
	pVersionParam.versionID=versionID;
	pVersionParam.hostUpdate=hostUpdate;
	pVersionParam.riskUpdate=riskUpdate;
	pVersionParam.serviceUpdate=serviceUpdate;
	pVersionParam.zxUpdate=zxUpdate;
	pVersionParam.blzdone=blzdone;
	pVersionParam.blzdtwo=blzdtwo;
	
	return pVersionParam;
}

- (void)dealloc
{
	[super dealloc];
}



@end

@implementation StyleParams

@synthesize colorStyle,paomaStyle,lanStyle,backStyle,blzdone,blzdtwo;

- (id)init
{
	if (self = [super init])
	{
		colorStyle =0 ;
		paomaStyle=0;
		lanStyle=0;
		backStyle=0;
		blzdone=0;
		blzdtwo=0;
	}
	
	return self;
}

-(void)encodeWithCoder:(NSCoder *)encoder
{
	[encoder encodeInt:colorStyle  forKey:@"StyleParamcolorStyle"];
	[encoder encodeInt:paomaStyle  forKey:@"StyleParampaomaStyle"];
	[encoder encodeInt:lanStyle  forKey:@"StyleParamlanStyle"];
	[encoder encodeInt:backStyle  forKey:@"StyleParambackStyle"];
	[encoder encodeInt:blzdone  forKey:@"StyleParamblzdone"];
	[encoder encodeInt:blzdtwo  forKey:@"StyleParamblzdtwo"];
	
}

-(id)initWithCoder:(NSCoder *)aDecoder
{
	self=[super init];
	if(self)
	{
		colorStyle=[aDecoder decodeIntForKey:@"StyleParamcolorStyle"];
		paomaStyle=[aDecoder decodeIntForKey:@"StyleParampaomaStyle"];
		lanStyle=[aDecoder decodeIntForKey:@"StyleParamlanStyle"];
		backStyle=[aDecoder decodeIntForKey:@"StyleParambackStyle"];
		blzdone=[aDecoder decodeIntForKey:@"StyleParamblzdone"];
		blzdtwo=[aDecoder decodeIntForKey:@"StyleParamblzdtwo"];
	}
	
	return self;
}

-(StyleParams *)deepcopy
{
	StyleParams *pStyleParam=[[StyleParams alloc]init] ;
	
	pStyleParam.colorStyle=colorStyle;
	pStyleParam.paomaStyle=paomaStyle;
	pStyleParam.lanStyle=lanStyle;
	pStyleParam.backStyle=backStyle;
	pStyleParam.blzdone=blzdone;
	pStyleParam.blzdtwo=blzdtwo;
	
	return pStyleParam;
}

- (void)dealloc
{
	[super dealloc];
}



@end



@implementation JyConfig

@synthesize qsid,qsmc,classfication,qsjc,tradesite,loginmode,viptradesite,yybs,secure,pmisc,vyybs,loginsets,network,bfindbestSite,bfindbestVipSite,bfindbesthqSite,hqsite,fversion,updatetag;
@synthesize hqParams,zxLinks,jyParams,assversion,versionParams,styleParams,gridCellInfoArray;
@synthesize fversion_mac,assversion_mac;

-(id)init
{
	self=[super init];
	if(self)
	{
		bfindbestSite=YES;
		bfindbestVipSite=YES;
		bfindbesthqSite=YES;
		qsmc=nil;
		fversion=nil;
		assversion = nil;
        fversion_mac=nil;
        assversion_mac = nil;
		updatetag=nil;
		classfication=nil;
		qsjc=nil;
		tradesite=nil;
		viptradesite=nil;
		loginmode=nil;
		yybs=nil;
		secure=nil;
		gridCellInfoArray = nil;
		pmisc=nil;
		vyybs=nil;
		loginsets=nil;
		network=nil;
		hqsite=nil;
		hqParams=nil;
		zxLinks=nil;
		jyParams=nil;
		versionParams= nil;
		styleParams = nil;
	}
	return self;
}

-(void)dealloc
{
	if(hqsite)
	{
		for(TradeSite *psite in hqsite)
		{
			RELEASEOBJ(psite)
		}
		[hqsite removeAllObjects];
	}
	RELEASEOBJ(hqsite)
	if(tradesite)
	{
		for(TradeSite *psite in tradesite)
		{
			RELEASEOBJ(psite)
		}
		[tradesite removeAllObjects];
	}
	RELEASEOBJ(tradesite)
	if(viptradesite)
	{
		for(TradeSite *psite in viptradesite)
		{
			RELEASEOBJ(psite)
		}
		[viptradesite removeAllObjects];
	}
	RELEASEOBJ(viptradesite)
	if(loginmode)
	{
		for(LoginMode *ploginmode in loginmode)
		{
			RELEASEOBJ(ploginmode)
		}
		[loginmode removeAllObjects];
	}
	RELEASEOBJ(loginmode)
	if(yybs)
	{
		for(Yybs *pyyb in yybs)
		{
			RELEASEOBJ(pyyb)
		}
		[yybs removeAllObjects];
	}
	RELEASEOBJ(yybs)
	if(secure)
	{
		for(SecureMode *psecure in secure)
		{
			RELEASEOBJ(psecure)
		}
		[secure removeAllObjects];
	}
	if (gridCellInfoArray) {
		for(GridCellInfo * pgrid in gridCellInfoArray) {
			RELEASEOBJ(pgrid)
		}
		[gridCellInfoArray removeAllObjects];
	}
	RELEASEOBJ(secure)
	RELEASEOBJ(gridCellInfoArray)
	RELEASEOBJ(pmisc)
	RELEASEOBJ(vyybs)
	RELEASEOBJ(loginsets)
	RELEASEOBJ(qsmc)
	RELEASEOBJ(fversion)
	RELEASEOBJ(assversion)
    RELEASEOBJ(fversion_mac)
    RELEASEOBJ(assversion_mac)
	RELEASEOBJ(updatetag)
	RELEASEOBJ(classfication)
	RELEASEOBJ(qsjc)
	RELEASEOBJ(network)
	RELEASEOBJ(hqParams)
	RELEASEOBJ(zxLinks)
	RELEASEOBJ(jyParams)
	RELEASEOBJ(versionParams)
	RELEASEOBJ(styleParams)
	[super dealloc];
}
@end

@implementation QsConfig

@synthesize jyconfigs;


-(id)init
{
	self=[super init];
	if(self)
	{
		jyconfigs=nil;
        
        NSFileManager *fm;
        fm=[NSFileManager defaultManager];
        NSArray* pathArray = NSSearchPathForDirectoriesInDomains(NSApplicationSupportDirectory, NSUserDomainMask, YES);
        
        int pathLen = [pathArray count];
        NSString* curuserpath = nil;
        for(int i=0;i<pathLen;i++)
        {
            curuserpath = [pathArray objectAtIndex:i];
            
        }
        curuserpath = [curuserpath stringByAppendingString:MAC_PATHSTRING];
        logcachefile = [[NSString alloc] initWithFormat:@"%@%@/%@%@/log.txt",curuserpath,@"/Library/Caches/tdximac",@"ZSZQ",@"/T0002/wtdata"];
        

        
		[self loadjyconfig];
	}
	return self;
}

-(void)dealloc
{
	if(jyconfigs)
	{
		for(JyConfig *pconfig in jyconfigs)
		{
			RELEASEOBJ(pconfig)
		}
		[jyconfigs removeAllObjects];
	}
	RELEASEOBJ(jyconfigs)
	[super dealloc];
}

-(void)loadjyconfig
{
	NSString* path = [[NSBundle mainBundle] pathForResource:@"eTrade" ofType:@"xml"];
    LogIt3(path)
	NSString* fileText = [NSString stringWithContentsOfFile:path encoding:NSUTF8StringEncoding error:nil];

    LogIt3(fileText)
	//MyNsLog(path);
	//MyNsLog(fileText);
	NSError* error;
	NSInteger tempInt = 0;
	GDataXMLDocument* document = [[GDataXMLDocument alloc] initWithXMLString:fileText options:tempInt error:&error];
	GDataXMLElement *rootNode = [document rootElement];
											
	NSArray* qsList = [rootNode nodesForXPath:@"//Classification/ITEM" error:&error];///Site/ITEM
	int num=0;
	if(qsList)
		num=[qsList count];
	if(num)
		jyconfigs=[[NSMutableArray alloc] initWithCapacity:num+1];
	for(GDataXMLNode* node in qsList) 
	{
		JyConfig *pconfig=[JyConfig new];
		pconfig.qsmc=[[NSString alloc]  initWithFormat:@"%@",[node GetAttributeStringValue:@"QsTag"]];
		[pconfig.qsmc release];
		pconfig.classfication=[[NSString alloc]  initWithFormat:@"%@",[node GetAttributeStringValue:@"ClassificationName"]];	
		[pconfig.classfication release];
		pconfig.qsid=[node GetAttrbuteIntValue:@"QsId"];
		pconfig.qsjc=[[NSString alloc]  initWithFormat:@"%@",[node GetAttributeStringValue:@"QsJc"]];
		[pconfig.qsjc release];
		
		NSArray *site=[node nodesForXPath:@"./Site" error:&error];
		if(site)
		{
			num=[site count];
			if(num)
			{
				for(GDataXMLNode *pnode in site)
				{
					pconfig.bfindbestSite=[pnode GetAttrbuteBoolValue:@"bfindbest"];
					break;
				}
			}
		}
		NSArray *sitelist=[node nodesForXPath:@"./Site/ITEM" error:&error];
		if(sitelist)
		{
			num=[sitelist count];
			if(num)
			{
				pconfig.tradesite=[[NSMutableArray alloc] initWithCapacity:num+1];
				[pconfig.tradesite release];
                NSString *strlog=@"";
				for(GDataXMLNode *pnode in sitelist)
				{
					TradeSite *psite=[TradeSite new];
					psite.sname=[[NSString alloc]  initWithFormat:@"%@",[pnode GetAttributeStringValue:@"Name"]];
					[psite.sname release];
					psite.ip=[[NSString alloc]  initWithFormat:@"%@",[pnode GetAttributeStringValue:@"Address"]];
					[psite.ip release];
					psite.tradever=[pnode GetAttrbuteBoolValue:@"TradVer"];
					psite.yybids=[[NSString alloc]  initWithFormat:@"%@",[pnode GetAttributeStringValue:@"yybids"]];
					[psite.yybids release];
					psite.nport=[pnode GetAttrbuteIntValue:@"Port"];//很大的数用这样的方式取得
					psite.weight=[pnode GetAttrbuteIntValue:@"Weight"];
					psite.hosttype=[pnode GetAttrbuteIntValue:@"HostType"];
				
                    
                    strlog=[NSString stringWithFormat:@"etrade_site %@ %@ %i\r",psite.sname,psite.ip,psite.nport];
                    LogIt3(strlog)
                    
                    
					[pconfig.tradesite addObject:psite];
				}
			}
		}
		NSArray *Vipsite=[node nodesForXPath:@"./VipSite" error:&error];
		if(Vipsite)
		{
			num=[Vipsite count];
			if(num)
			{
				for(GDataXMLNode *pnode in Vipsite)
				{
					pconfig.bfindbestVipSite=[pnode GetAttrbuteBoolValue:@"bfindbest"];
					break;
				}
			}
		}
		
		NSArray *vipsitelist=[node nodesForXPath:@"./VipSite/ITEM" error:&error];
		if(vipsitelist)
		{
			num=[vipsitelist count];
			if(num)
			{
				pconfig.viptradesite=[[NSMutableArray alloc] initWithCapacity:num+1];
				[pconfig.viptradesite release];
				for(GDataXMLNode *pnode in vipsitelist)
				{ 
					TradeSite *psite=[TradeSite new];
					psite.sname=[[NSString alloc]  initWithFormat:@"%@",[pnode GetAttributeStringValue:@"Name"]];
					[psite.sname release];
					psite.ip=[[NSString alloc]  initWithFormat:@"%@",[pnode GetAttributeStringValue:@"Address"]];
					[psite.ip release];
					psite.tradever=[pnode GetAttrbuteBoolValue:@"TradVer"];
					psite.yybids=[[NSString alloc]  initWithFormat:@"%@",[pnode GetAttributeStringValue:@"yybids"]];
					[psite.yybids release];
					psite.nport=[pnode GetAttrbuteIntValue:@"Port"];
					psite.weight=[pnode GetAttrbuteIntValue:@"Weight"];
					psite.hosttype=[pnode GetAttrbuteIntValue:@"HostType"];
					
					[pconfig.viptradesite addObject:psite];
				}
			}
		}
		NSArray *hqsite=[node nodesForXPath:@"./HQSite" error:&error];
		if(hqsite)
		{
			num=[hqsite count];
			if(num)
			{
				for(GDataXMLNode *pnode in hqsite)
				{
					pconfig.bfindbesthqSite=[pnode GetAttrbuteBoolValue:@"bfindbest"];
					break;
				}
			}
		}
		NSArray *hqsitelist=[node nodesForXPath:@"./HQSite/ITEM" error:&error];
		if(hqsitelist)
		{
			num=[hqsitelist count];
			if(num)
			{
				pconfig.hqsite=[[NSMutableArray alloc] initWithCapacity:num+1];
				[pconfig.hqsite release];
				for(GDataXMLNode *pnode in hqsitelist)
				{
					TradeSite *psite=[TradeSite new];
					psite.sname=[[NSString alloc]  initWithFormat:@"%@",[pnode GetAttributeStringValue:@"Name"]];
					[psite.sname release];
					psite.ip=[[NSString alloc]  initWithFormat:@"%@",[pnode GetAttributeStringValue:@"Address"]];
					[psite.ip release];
					psite.yybids=[[NSString alloc]  initWithFormat:@"%@",[pnode GetAttributeStringValue:@"yybids"]];
					[psite.yybids release];
					psite.nport=[pnode GetAttrbuteIntValue:@"Port"];
					psite.weight=[pnode GetAttrbuteIntValue:@"Weight"];
					psite.hosttype=[pnode GetAttrbuteIntValue:@"HostType"];
					
					[pconfig.hqsite addObject:psite];
				}
			}
		}
		NSArray *loginlist=[node nodesForXPath:@"./LoginMode/ITEM" error:&error];
		if(loginlist)
		{
			num=[loginlist count];
			if(num)
			{
				pconfig.loginmode=[[NSMutableArray alloc] initWithCapacity:num+1];
				[pconfig.loginmode release];
				for(GDataXMLNode *pnode in loginlist)
				{
					LoginMode *plogin=[LoginMode new];
					
					plogin.zhlx=[pnode GetAttrbuteIntValue:@"AccountType"];
					plogin.hosttype=[pnode GetAttrbuteIntValue:@"HostType"];
					plogin.zhdesc=[[NSString alloc]  initWithFormat:@"%@",[pnode GetAttributeStringValue:@"Prompt"]];
					[plogin.zhdesc release];
					
					[pconfig.loginmode addObject:plogin];
				}
			}
		}
		
		NSArray *yyblist=[node nodesForXPath:@"./Branch/ITEM" error:&error];
		if(yyblist)
		{
			num=[yyblist count];
			if(num)
			{
				pconfig.yybs=[[NSMutableArray alloc] initWithCapacity:num+1];
				[pconfig.yybs release];
				for(GDataXMLNode *pnode in yyblist)
				{
					Yybs *pyyb=[Yybs new];
					
					pyyb.autofill=[pnode GetAttrbuteIntValue:@"AutoFill"];
					pyyb.noprefix=[pnode GetAttrbuteIntValue:@"NoPrefix"];
					pyyb.hosttype=[pnode GetAttrbuteIntValue:@"HostType"];
					pyyb.yybid=[[NSString alloc]  initWithFormat:@"%@",[pnode GetAttributeStringValue:@"ID"]];
					[pyyb.yybid release];
					pyyb.yybname=[[NSString alloc]  initWithFormat:@"%@",[pnode GetAttributeStringValue:@"Name"]];
					[pyyb.yybname release];
					pyyb.yybprefix=[[NSString alloc]  initWithFormat:@"%@",[pnode GetAttributeStringValue:@"Prefix"]];
					[pyyb.yybprefix release];
					
					[pconfig.yybs addObject:pyyb];
				}
			}
		}
		NSArray *securelist=[node nodesForXPath:@"./SecurityMode/ITEM" error:&error];
		if(securelist)
		{
			num=[securelist count];
			if(num)
			{
				pconfig.secure=[[NSMutableArray alloc] initWithCapacity:num+1];
				[pconfig.secure release];
				for(GDataXMLNode *pnode in securelist)
				{
					SecureMode *psecure=[SecureMode new];
					
					psecure.ntype=[pnode GetAttrbuteIntValue:@"SecurityType"];
					psecure.sname=[[NSString alloc]  initWithFormat:@"%@",[pnode GetAttributeStringValue:@"Prompt"]];
					[psecure.sname release];
					
					[pconfig.secure addObject:psecure];
				}
			}
			else 
			{
				pconfig.secure=[[NSMutableArray alloc] initWithCapacity:1];
				[pconfig.secure release];
				SecureMode *psecure=[SecureMode new];
				psecure.ntype=0;
				psecure.sname=[[NSString alloc]  initWithFormat:@"%@",@"通达信加密"];
				[psecure.sname release];
				[pconfig.secure addObject:psecure];
			}
		}
		
		
		NSArray *gridcelllist=[node nodesForXPath:@"./GridParams/ITEM" error:&error];
		if(gridcelllist)
		{
			num=[gridcelllist count];
			if(num)
			{
				pconfig.gridCellInfoArray=[[NSMutableArray alloc] initWithCapacity:num+1];
				[pconfig.gridCellInfoArray release];
				for(GDataXMLNode *pnode in gridcelllist)
				{
					GridCellInfo *pgrid = [GridCellInfo new];
					
					pgrid.cellID=[pnode GetAttrbuteIntValue:@"id"];
					pgrid.cellName=[[NSString alloc]  initWithFormat:@"%@",[pnode GetAttributeStringValue:@"name"]];
					[pgrid.cellName release];
					pgrid.cellWidth = [pnode GetAttrbuteIntValue:@"width"];
					if ([[pnode GetAttributeStringValue:@"sortid"] length] > 0) {
						pgrid.cellSortID = [pnode GetAttrbuteIntValue:@"sortid"];
					}
					else {
						pgrid.cellSortID = -1;
					}
					pgrid.cellShowFlag = [pnode GetAttrbuteBoolValue:@"showFlag"];
					pgrid.cellFixFlag = [pnode GetAttrbuteBoolValue:@"fixFlag"];
					pgrid.cellMarktet=[pnode GetAttrbuteIntValue:@"marketFlag"];
					
					
					[pconfig.gridCellInfoArray addObject:pgrid];
				}
			}
		}
		
		
		NSArray *misclist=[node nodesForXPath:@"./Misc/Option" error:&error];
		if(misclist && [misclist count])
		{
			pconfig.pmisc=[Misc new];
			[pconfig.pmisc release];
			GDataXMLNode *pnode=[misclist objectAtIndex:0];
			pconfig.pmisc.swapcombo=[pnode GetAttrbuteIntValue:@"SwapCombo"];
			pconfig.pmisc.coloryzm=[pnode GetAttrbuteIntValue:@"ColorYzm"];
			pconfig.pmisc.zjzhmaxlen=[pnode GetAttrbuteIntValue:@"ZJZHMaxLen"];
			pconfig.pmisc.mustdigitpwd=[pnode GetAttrbuteIntValue:@"MustDigitPwd"];
			pconfig.pmisc.mustaccountlen=[pnode GetAttrbuteIntValue:@"MustAccountLen"];
			pconfig.pmisc.maxaccountlen=[pnode GetAttrbuteIntValue:@"MaxAccountLen"];
			pconfig.pmisc.aqfscombo=[pnode GetAttrbuteIntValue:@"AqfsCombo"];
			pconfig.pmisc.hascxmode=[pnode GetAttrbuteIntValue:@"HasCxMode"];
			pconfig.pmisc.nyybweight=[pnode GetAttrbuteIntValue:@"YybWeight"];
			pconfig.pmisc.vipxmb=[pnode GetAttrbuteIntValue:@"VipXMB"];
			pconfig.pmisc.bsupportlimitmode=[pnode GetAttrbuteBoolValue:@"SUPPORTLIMITMOD"];
			pconfig.pmisc.urlapplyAuthpass=[[NSString alloc]  initWithFormat:@"%@",[pnode GetAttributeStringValue:@"UrlApplyAuthPass"]];
			[pconfig.pmisc.urlapplyAuthpass release];
			pconfig.pmisc.urlmodifyAuthpass=[[NSString alloc]  initWithFormat:@"%@",[pnode GetAttributeStringValue:@"UrlModifyAuthPass"]];
			[pconfig.pmisc.urlmodifyAuthpass release];
		}
		NSArray *vyyblist=[node nodesForXPath:@"./BranchMap" error:&error];
		if(vyyblist && [vyyblist count])
		{
			pconfig.vyybs=[Vyyb new];
			[pconfig.vyybs release];
			GDataXMLNode *pnode=[vyyblist objectAtIndex:0];
			pconfig.vyybs.maxaccountlen=[pnode GetAttrbuteIntValue:@"MAXACCOUNTLEN"];
			pconfig.vyybs.mustaccountlen=[pnode GetAttrbuteIntValue:@"MUSTACCOUNTLEN"];
			pconfig.vyybs.headlen=[pnode GetAttrbuteIntValue:@"HEADLEN"];
			
			NSArray *vyybslist=[pnode nodesForXPath:@"./yybs/ITEM" error:&error];
			if(vyybslist)
			{
				num=[vyybslist count];
				if(num)
				{
					NSRange range;
					NSString *tmpstr,*tmpstr2,*tmpstr3;
					pconfig.vyybs.yybrange=[[NSMutableArray alloc] initWithCapacity:num+1];
					[pconfig.vyybs.yybrange release];
					for(GDataXMLNode *pnode1 in vyybslist)
					{
						YybRange *prange=[YybRange new];
						
						prange.id=[pnode1 GetAttrbuteIntValue:@"ID"];
						
						tmpstr=[pnode1 GetAttributeStringValue:@"Prefix"];  
						
						range=[tmpstr rangeOfString:@";"];
						while (range.location!=NSNotFound &&range.location<[tmpstr length] && prange.nRealNum<10)
						{
							tmpstr2=[tmpstr substringToIndex:(range.location)];
							tmpstr3=[tmpstr substringFromIndex:(range.location+range.length)];
							tmpstr=tmpstr3;
							
							range=[tmpstr2 rangeOfString:@"-"];
							[prange SetStartRange:prange.nRealNum withvalue:[[tmpstr2 substringToIndex:(range.location)] intValue]];
							[prange SetEndRange:prange.nRealNum withvalue:[[tmpstr2 substringFromIndex:(range.location+range.length)] intValue]];
							prange.nRealNum++;
							
							
							range=[tmpstr rangeOfString:@";"];
						};
						
						[pconfig.vyybs.yybrange addObject:prange];
					}
				}
			}
		}
		NSArray *loginsetlist=[node nodesForXPath:@"./LOGINSET" error:&error];
		if(loginsetlist && [loginsetlist count])
		{
			pconfig.loginsets=[LoginSet new];
			[pconfig.loginsets release];
			GDataXMLNode *pnode=[loginsetlist objectAtIndex:0];
			pconfig.loginsets.buse=[pnode GetAttrbuteIntValue:@"buse"];
			pconfig.loginsets.pwdmaxlength=[pnode GetAttrbuteIntValue:@"PwdMaxLength"];
			pconfig.loginsets.pwdtype=[pnode GetAttrbuteIntValue:@"pwdType"];
			pconfig.loginsets.authmaxlength=[pnode GetAttrbuteIntValue:@"AuthMaxLength"];
			pconfig.loginsets.authtype=[pnode GetAttrbuteIntValue:@"AuthType"];
			pconfig.loginsets.maxzhlen=[pnode GetAttrbuteIntValue:@"MAXZHLEN"];
		}
		NSArray *networklist=[node nodesForXPath:@"./Network" error:&error];
		if(networklist && [networklist count])
		{
			pconfig.network=[NetWorkConfig new];
			[pconfig.network release];
			GDataXMLNode *pnode=[networklist objectAtIndex:0];
			if(pnode)
			{
				NSArray *timeoutlist=[pnode nodesForXPath:@"./Timeout" error:&error];
				if(timeoutlist && [timeoutlist count])
				{
					GDataXMLNode *pnode1=[timeoutlist objectAtIndex:0];
					pconfig.network.njobtimeout=[pnode1 GetAttrbuteIntValue:@"JobTimeout"];
					pconfig.network.nconnecttimeout=[pnode1 GetAttrbuteIntValue:@"ConnectTimeout"];
				}
			}
		}
		NSArray *pupdateInfo=[node nodesForXPath:@"./UpdateInfo" error:&error];
		if(pupdateInfo)
		{
			num=[pupdateInfo count];
			if(num)
			{
				for(GDataXMLNode *pnode in pupdateInfo)
				{
					pconfig.fversion=[[NSString alloc]  initWithFormat:@"%@",[pnode GetAttributeStringValue:@"MainVer"]];
					[pconfig.fversion release];
					pconfig.assversion = [[NSString alloc]  initWithFormat:@"%@",[pnode GetAttributeStringValue:@"AssVer"]];
					[pconfig.assversion release];
					pconfig.updatetag=[[NSString alloc]  initWithFormat:@"%@",[pnode GetAttributeStringValue:@"UpdateTag"]];
					[pconfig.updatetag release];
					break;
				}
			}
		}
        NSArray *pmacInfo=[node nodesForXPath:@"./MachInfo" error:&error];
        if(pmacInfo)
        {
            num=[pmacInfo count];
            if(num)
            {
                for(GDataXMLNode *pnode in pmacInfo)
                {
                    pconfig.fversion_mac=[[NSString alloc]  initWithFormat:@"%@",[pnode GetAttributeStringValue:@"MainVer"]];
                    [pconfig.fversion_mac release];
                    pconfig.assversion_mac = [[NSString alloc]  initWithFormat:@"%@",[pnode GetAttributeStringValue:@"AssVer"]];
                    [pconfig.assversion_mac release];
                    break;
                }
            }
        }
		NSArray *pHqParamInfo=[node nodesForXPath:@"./HqParams" error:&error];
		if(pHqParamInfo)
		{
			num=[pHqParamInfo count];
			if(num)
			{
				pconfig.hqParams=[HqParamInfo new];
				[pconfig.hqParams release];
				for(GDataXMLNode *pnode in pHqParamInfo)
				{
					pconfig.hqParams.bautocheckfast=[pnode GetAttrbuteBoolValue:@"autocheckfast"];
					pconfig.hqParams.bautorefreshhq=[pnode GetAttrbuteBoolValue:@"autorefreshhq"];
					pconfig.hqParams.nhqrefreshspan=[pnode GetAttrbuteIntValue:@"hqrefreshspan"];
					pconfig.hqParams.nfontsize=[pnode GetAttrbuteIntValue:@"fontsize"];
					break;
				}
			}
		}
		NSArray *pzxLinkInfo=[node nodesForXPath:@"./ZxLinks" error:&error];
		if(pzxLinkInfo)
		{
			num=[pzxLinkInfo count];
			if(num)
			{
				pconfig.zxLinks=[ZxLinkInfo new];
				[pconfig.zxLinks release];
				pconfig.zxLinks.mainlink=[ZxLinks new];
				[pconfig.zxLinks.mainlink release];
				
				for(GDataXMLNode *pnode in pzxLinkInfo)
				{
					pconfig.zxLinks.mainlink.zxname=[[NSString alloc]  initWithFormat:@"%@",[pnode GetAttributeStringValue:@"mainName"]];
					[pconfig.zxLinks.mainlink.zxname release];
					pconfig.zxLinks.mainlink.url=[[NSString alloc]  initWithFormat:@"%@",[pnode GetAttributeStringValue:@"mainUrl"]];
					[pconfig.zxLinks.mainlink.url release];
					break;
				}
				
				NSArray *pzxLinkItems=[node nodesForXPath:@"./ZxLinks/ITEM" error:&error];
				if(pzxLinkItems)
				{
					num=[pzxLinkItems count];
					if(num)
					{
						pconfig.zxLinks.linkItems=[[NSMutableArray alloc] initWithCapacity:num+1];
						[pconfig.zxLinks.linkItems release];
						for(GDataXMLNode *pnode1 in pzxLinkItems)
						{
							ZxLinks *plink=[ZxLinks new];
							
							plink.zxname=[[NSString alloc]  initWithFormat:@"%@",[pnode1 GetAttributeStringValue:@"name"]];
							[plink.zxname release];
							plink.url=[[NSString alloc]  initWithFormat:@"%@",[pnode1 GetAttributeStringValue:@"url"]];
							[plink.url release];
							
							[pconfig.zxLinks.linkItems addObject:plink];
						}
					}
				}
			}
		}
		NSArray *pJyParamInfo=[node nodesForXPath:@"./JyParams" error:&error];
		if(pJyParamInfo)
		{
			num=[pJyParamInfo count];
			if(num)
			{
				pconfig.jyParams=[JyParamInfo new];
				[pconfig.jyParams release];
				for(GDataXMLNode *pnode in pJyParamInfo)
				{
					pconfig.jyParams.nlockscreenspan=[pnode GetAttrbuteIntValue:@"lockscreenspan"];
					break;
				}
			}
		}
		
		NSArray *pVersionParamInfo=[node nodesForXPath:@"./VersionParams" error:&error];
		if(pVersionParamInfo)
		{
			num=[pVersionParamInfo count];
			if(num)
			{
				pconfig.versionParams=[VersionParam new];
				[pconfig.versionParams release];
				for(GDataXMLNode *pnode in pVersionParamInfo)
				{
					pconfig.versionParams.hostUpdate=[pnode GetAttrbuteIntValue:@"hostupdate"];
					pconfig.versionParams.riskUpdate=[pnode GetAttrbuteIntValue:@"riskupdate"];
					pconfig.versionParams.serviceUpdate=[pnode GetAttrbuteIntValue:@"serviceupdate"];
					pconfig.versionParams.zxUpdate=[pnode GetAttrbuteIntValue:@"zxupdate"];
					//pconfig.versionParams.blzdone =0;
					//pconfig.versionParams.blzdtwo =0;
					
					break;
				}
			}
		}
		
		NSArray *pStyleParamInfo=[node nodesForXPath:@"./StyleParams" error:&error];
		if(pStyleParamInfo)
		{
			num=[pStyleParamInfo count];
			if(num)
			{
				pconfig.styleParams=[StyleParams new];
				[pconfig.styleParams release];
				for(GDataXMLNode *pnode in pStyleParamInfo)
				{
					pconfig.styleParams.colorStyle=[pnode GetAttrbuteIntValue:@"colorStyle"];
					pconfig.styleParams.paomaStyle=[pnode GetAttrbuteIntValue:@"paomaStyle"];
					pconfig.styleParams.lanStyle=[pnode GetAttrbuteIntValue:@"lanStyle"];
					pconfig.styleParams.backStyle=[pnode GetAttrbuteIntValue:@"backStyle"];
					pconfig.versionParams.blzdone =[pnode GetAttrbuteIntValue:@"fqStyle"];
					//pconfig.versionParams.blzdtwo =0;
					
					break;
				}
			}
		}
		
		
		
		
		[jyconfigs addObject:pconfig];
		break;//只取第一个，单券商
	}
	[document release];                          
	
}

-(void)writeLog:(NSString *)_log{
    [self SetLog:_log];
}

-(void)SetLog:(NSString *)_theLog{
    NSDateFormatter *dateFormatter = [[[NSDateFormatter alloc] init]autorelease];
    [dateFormatter setDateFormat:@"yyyyMMdd:HHmmss"];
    NSString * dateString = [dateFormatter stringFromDate:[NSDate date]];
    
    NSError *error;
    NSString * tempString = [NSString stringWithContentsOfFile:logcachefile encoding:NSUTF8StringEncoding error:&error];
    tempString = [tempString stringByAppendingFormat:@"%@---%@%@\r",dateString,@"/",_theLog];
    NSMutableData * write = [[NSMutableData alloc] init];
    [write appendData:[tempString dataUsingEncoding:NSUTF8StringEncoding]];
    //[write appendData:@"/"];
    [write writeToFile:logcachefile atomically:YES];
    [write release];
}

@end

