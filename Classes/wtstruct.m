//
//  wtstruct.m
//  tdxiphone
//
//  Created by tdx on 11-2-23.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "wtstruct.h"
#import "ParseRecv.h"

@implementation GdmxInfo

@synthesize gdmc,gddm,wttype,specTrade,zjzh,xwdm,memo,bxyjygd;

-(id) init
{
	self = [super init];
	if(self)
	{
		gdmc=nil;
		gddm=nil;
		zjzh=nil;
		xwdm=nil;
		memo=nil;
		
	}
	return self;
}

-(void) dealloc
{
	RELEASEOBJ(gdmc)
	RELEASEOBJ(gddm)
	RELEASEOBJ(zjzh)
	RELEASEOBJ(xwdm)
	RELEASEOBJ(memo)
	[super dealloc];
}

-(NSString *)GetWtTypeStr
{
	switch (wttype) {
		case SZAG:
			return @"深A";
		case SZBG:
			return @"深B";
		case SHAG:
			return @"沪A";
		case SHBG:
			return @"沪B";
		case SBAG:
			return @"三板A";
			break;
		case SBBG:
			return @"三板B";
		case SBGB:
			return @"三板港";
        case 21:
            return @"郑交所";
        case 22:
            return @"上交所";
        case 23:
            return @"大交所";
        case 26:
            return @"中金所";
        case 38:
            return @"新三板A股";
        case 39:
            return @"新三板B股";
        case 40:
            return @"沪港通";
        case 41:
            return @"深港通";
		default:
			break;
	}
	return @"";
}

+(NSString *)GetWtTypeStr2:(int)nwttype
{
	switch (nwttype) {
		case SZAG:
			return @"深A股东";
		case SZBG:
			return @"深B股东";
		case SHAG:
			return @"沪A股东";
		case SHBG:
			return @"沪B股东";
		case SBAG:
			return @"三板人民币";
		case SBBG:
			return @"三板港币";
		case SBGB:
			return @"三板美元";
        case 21:
            return @"郑交所";
        case 22:
            return @"上交所";
        case 23:
            return @"大交所";
        case 26:
            return @"中金所";
        case 38:
            return @"新三板A股";
        case 39:
            return @"新三板B股";
        case 40:
            return @"沪港通";
        case 41:
            return @"深港通";
		default:
			break;
	}
	return @"";
}

-(NSString *)GetGdDescribe
{
	return [NSString  stringWithFormat:@"%@ %@",[self GetWtTypeStr],gddm];
}

-(void)encodeWithCoder:(NSCoder *)encoder
{
	[encoder encodeInt:wttype  forKey:@"GdmxInfowttype"];
	[encoder encodeInt:specTrade  forKey:@"GdmxInfospecTrade"];
	[encoder encodeBool:bxyjygd  forKey:@"GdmxInfobxyjygd"];	
	[encoder encodeObject:gdmc forKey:@"GdmxInfogdmc"];
	[encoder encodeObject:gddm	forKey:@"GdmxInfogddm"];
	[encoder encodeObject:zjzh forKey:@"GdmxInfozjzh"];
	[encoder encodeObject:xwdm	forKey:@"GdmxInfoxwdm"];
	[encoder encodeObject:memo forKey:@"GdmxInfomemo"];
}

-(id)initWithCoder:(NSCoder *)aDecoder
{
	self=[super init];
	if(self)
	{
		wttype=[aDecoder decodeIntForKey:@"GdmxInfowttype"];
		specTrade=[aDecoder decodeIntForKey:@"GdmxInfospecTrade"];
		bxyjygd=[aDecoder decodeBoolForKey:@"GdmxInfobxyjygd"];
		gdmc=[[aDecoder decodeObjectForKey:@"GdmxInfogdmc"]retain];
		gddm=[[aDecoder decodeObjectForKey:@"GdmxInfogddm"]retain];
		zjzh=[[aDecoder decodeObjectForKey:@"GdmxInfozjzh"]retain];
		xwdm=[[aDecoder decodeObjectForKey:@"GdmxInfoxwdm"]retain];
		memo=[[aDecoder decodeObjectForKey:@"GdmxInfomemo"]retain];
	}
	
	return self;
}

-(GdmxInfo *)deepcopy
{
	GdmxInfo *pgdmx=[[GdmxInfo alloc]init];

	pgdmx.wttype=wttype;
	pgdmx.specTrade=specTrade;
	pgdmx.bxyjygd=bxyjygd;
	pgdmx.gdmc=[[NSString alloc] initWithFormat:@"%@",gdmc];
	[pgdmx.gdmc release];
	pgdmx.gddm=[[NSString alloc] initWithFormat:@"%@",gddm];
	[pgdmx.gddm release];
	pgdmx.zjzh=[[NSString alloc] initWithFormat:@"%@",zjzh];
	[pgdmx.zjzh release];
	pgdmx.xwdm=[[NSString alloc] initWithFormat:@"%@",xwdm];
	[pgdmx.xwdm release];
	pgdmx.memo=[[NSString alloc] initWithFormat:@"%@",memo];
	[pgdmx.memo release];
	return pgdmx;
}
@end


@implementation GpdmlInfo
@synthesize szGPArray,shGPArray,savedate;


-(id) init
{
	self = [super init];
	if(self)
	{
		szGPArray=nil;
		shGPArray=nil;
		savedate=nil;
	}
	return self;
}

-(void)encodeWithCoder:(NSCoder *)encoder
{
	[encoder encodeObject:szGPArray forKey:@"szGpdlm"];
	[encoder encodeObject:shGPArray forKey:@"shGpdlm"];
	[encoder encodeObject:savedate forKey:@"GdInfosavedate"];
	
}

-(id)initWithCoder:(NSCoder *)aDecoder
{
	self=[super init];
	if(self)
	{
		szGPArray=[[aDecoder decodeObjectForKey:@"szGpdlm"]retain];
		shGPArray=[[aDecoder decodeObjectForKey:@"shGpdlm"]retain];
		savedate=[[aDecoder decodeObjectForKey:@"GdInfosavedate"]retain];
	}
	return self;
}

-(void)releasegpdml{
	if(szGPArray && [szGPArray count])
	{
		for(StockInfo *pgddm in szGPArray)
		{
			RELEASEOBJ(pgddm);
		}
		[szGPArray removeAllObjects];
	}
	RELEASEOBJ(szGPArray);
	
	if(shGPArray && [shGPArray count])
	{
		for(StockInfo *pgddm in shGPArray)
		{
			RELEASEOBJ(pgddm);
		}
		[shGPArray removeAllObjects];
	}
	RELEASEOBJ(shGPArray);
	
	[savedate release],savedate=nil;
	
}

@end



@implementation GdInfo

@synthesize gddms,m_SZA_MainGd,m_SZB_MainGd,m_SHA_MainGd,m_SHB_MainGd,m_SBA_MainGd,m_SBB_MainGd,m_SBG_MainGd;
@synthesize m_SZA_MainxyGd,m_SZB_MainxyGd,m_SHA_MainxyGd,m_SHB_MainxyGd,m_SBA_MainxyGd,m_SBB_MainxyGd,m_SBG_MainxyGd;
@synthesize m_SZA_MainFlag,m_SZB_MainFlag,m_SHA_MainFlag,m_SHB_MainFlag,m_SBA_MainFlag,m_SBB_MainFlag,m_SBG_MainFlag,m_SZA_MainxyFlag,m_SZB_MainxyFlag;
@synthesize m_SHA_MainxyFlag,m_SHB_MainxyFlag,m_SBA_MainxyFlag,m_SBB_MainxyFlag,m_SBG_MainxyFlag,m_SZAGDNUM,m_SZBGDNUM,m_SHAGDNUM;
@synthesize m_SHBGDNUM,m_SBAGDNUM,m_SBBGDNUM,m_SBGGDNUM,m_bsfcguser,m_gdcount,savedate;
-(id) init
{
	self = [super init];
	if(self)
	{
		[self resetflag];
	}
	return self;
}

-(void)resetflag
{
	m_gdcount=0;
	m_SZAGDNUM=0;
	m_SZBGDNUM=0;
	m_SHAGDNUM=0;
	m_SHBGDNUM=0;
	m_SBAGDNUM=0;
	m_SBBGDNUM=0;
	m_SBGGDNUM=0;
	m_bsfcguser=NO;
	
	m_SZA_MainFlag=0;
	m_SZB_MainFlag=0;
	m_SHA_MainFlag=0;
	m_SHB_MainFlag=0;
	m_SBA_MainFlag=0;
	m_SBB_MainFlag=0;
	m_SBG_MainFlag=0;
	m_SZA_MainxyFlag=0;
	m_SZB_MainxyFlag=0;
	m_SHA_MainxyFlag=0;
	m_SHB_MainxyFlag=0;
	m_SBA_MainxyFlag=0;
	m_SBB_MainxyFlag=0;
	m_SBG_MainxyFlag=0;
	m_SZA_MainGd=nil;
	m_SZB_MainGd=nil;
	m_SHA_MainGd=nil;
	m_SHB_MainGd=nil;
	m_SBA_MainGd=nil;
	m_SBB_MainGd=nil;
	m_SBG_MainGd=nil;
	m_SZA_MainxyGd=nil;
	m_SZB_MainxyGd=nil;
	m_SHA_MainxyGd=nil;
	m_SHB_MainxyGd=nil;
	m_SBA_MainxyGd=nil;
	m_SBB_MainxyGd=nil;
	m_SBG_MainxyGd=nil;
	gddms=nil;
	savedate=nil;
}

-(void) dealloc
{
	if(gddms && [gddms count])
	{
		for(GdmxInfo *pgddm in gddms)
		{
			RELEASEOBJ(pgddm);
		}
		[gddms removeAllObjects];
	}
	RELEASEOBJ(gddms);
	RELEASEOBJ(savedate);
	[super dealloc];
}

-(void)encodeWithCoder:(NSCoder *)encoder
{
	[encoder encodeObject:gddms forKey:@"GdInfogddms"];
	[encoder encodeObject:savedate forKey:@"GdInfosavedate"];
}

-(id)initWithCoder:(NSCoder *)aDecoder
{
	self=[super init];
	if(self)
	{
		gddms=[[aDecoder decodeObjectForKey:@"GdInfogddms"]retain];
		savedate=[[aDecoder decodeObjectForKey:@"GdInfosavedate"]retain];
	}
	return self;
}

-(void)releasegdmxs
{
	if(gddms && [gddms count])
	{
		for(GdmxInfo *pgddm in gddms)
		{
			RELEASEOBJ(pgddm);
		}
		[gddms removeAllObjects];
	}
	RELEASEOBJ(gddms);
	[self resetflag];
}

-(void)CalcGdInfo:(int)nloginWtType withrawzjzh:(NSString *)rawzjzh
{
	m_gdcount=0;
	if(gddms)
		m_gdcount=[gddms count];
	if(m_gdcount==0)
	{
		[self resetflag];
		return;
	}
	GdmxInfo *tmpszagd,*tmpshagd,*tmpszbgd,*tmpshbgd,*tmpsbagd,*tmpsbggd,*tmpsbbgd,*pgdmx;
	GdmxInfo *tmpszaxygd,*tmpshaxygd,*tmpszbxygd,*tmpshbxygd,*tmpsbaxygd,*tmpsbgxygd,*tmpsbbxygd;
	
	int   sza_flag=0,szb_flag=0,sha_flag=0,shb_flag=0,sba_flag=0,sbg_flag=0,sbb_flag=0;
	int   sza_xyflag=0,szb_xyflag=0,sha_xyflag=0,shb_xyflag=0,sba_xyflag=0,sbg_xyflag=0,sbb_xyflag=0;
	
	NSRange range;
	BOOL bonlybg=YES;
	for(pgdmx in gddms)
	{
		if(pgdmx==nil)
			continue;
		if(pgdmx.wttype!=SZBG && pgdmx.wttype!=SHBG)
			bonlybg=NO;
		switch (pgdmx.wttype) {
			case SZAG:
			{
				if(sza_flag!=1)
				{
					sza_flag=1;
					tmpszagd=pgdmx;
				}
				if(pgdmx.bxyjygd)
				{
					if(sza_xyflag!=1)
					{
						sza_xyflag=1;
						tmpszaxygd=pgdmx;
					}
					if (m_SZA_MainxyFlag != 1)
					{
						m_SZA_MainxyFlag = 1;
						m_SZA_MainxyGd=pgdmx;
					}
				}
				
				if(nloginWtType==SZAG)
				{
					if (m_SZA_MainFlag != 1 && rawzjzh)
					{
						range=[pgdmx.gddm rangeOfString:rawzjzh];
						if(range.location!=NSNotFound && range.location <[pgdmx.gddm length])
						{
							m_SZA_MainFlag = 1;
							m_SZA_MainGd=pgdmx;
						}
					}
				}
				else
				{
					if (m_SZA_MainFlag != 1)
					{
						m_SZA_MainFlag = 1;
						m_SZA_MainGd=pgdmx;
					}
				}
				m_SZAGDNUM++;
			}
				break;
			case SZBG:
			{
				if(szb_flag!=1)
				{
					szb_flag=1;
					tmpszbgd=pgdmx;
				}
				if(pgdmx.bxyjygd)
				{
					if(szb_xyflag!=1)
					{
						szb_xyflag=1;
						tmpszbxygd=pgdmx;
					}
					if (m_SZB_MainxyFlag != 1)
					{
						m_SZB_MainxyFlag = 1;
						m_SZB_MainxyGd=pgdmx;
					}
				}
				if(nloginWtType==SZBG)
				{
					if (m_SZB_MainFlag != 1 && rawzjzh)
					{
						range=[pgdmx.gddm rangeOfString:rawzjzh];
						if(range.location!=NSNotFound && range.location <[pgdmx.gddm length])
						{
							m_SZB_MainFlag = 1;
							m_SZB_MainGd=pgdmx;
						}
					}
				}
				else
				{
					if (m_SZB_MainFlag != 1)
					{
						m_SZB_MainFlag = 1;
						m_SZB_MainGd=pgdmx;
					}
				}
				m_SZBGDNUM++;
			}
				break;
			case SHAG:
			{
				if(sha_flag!=1)
				{
					sha_flag=1;
					tmpshagd=pgdmx;
				}
				if(pgdmx.bxyjygd)
				{
					if(sha_xyflag!=1)
					{
						sha_xyflag=1;
						tmpshaxygd=pgdmx;
					}
					if (m_SHA_MainxyFlag != 1)
					{
						m_SHA_MainxyFlag = 1;
						m_SHA_MainxyGd=pgdmx;
					}
				}
				if(nloginWtType==SHAG)
				{
					if (m_SHA_MainFlag != 1 && rawzjzh)
					{
						range=[pgdmx.gddm rangeOfString:rawzjzh];
						if(range.location!=NSNotFound && range.location <[pgdmx.gddm length])
						{
							m_SHA_MainFlag = 1;
							m_SHA_MainGd=pgdmx;
						}
					}
				}
				else
				{
					if (m_SHA_MainFlag != 1)
					{
						m_SHA_MainFlag = 1;
						m_SHA_MainGd=pgdmx;
					}
				}
				m_SHAGDNUM++;
			}
				break;
			case SHBG:
			{
				if(shb_flag!=1)
				{
					shb_flag=1;
					tmpshbgd=pgdmx;
				}
				if(pgdmx.bxyjygd)
				{
					if(shb_xyflag!=1)
					{
						shb_xyflag=1;
						tmpshbxygd=pgdmx;
					}
					if (m_SHB_MainxyFlag != 1)
					{
						m_SHB_MainxyFlag = 1;
						m_SHB_MainxyGd=pgdmx;
					}
				}
				if(nloginWtType==SHBG)
				{
					if (m_SHB_MainFlag != 1 && rawzjzh)
					{
						range=[pgdmx.gddm rangeOfString:rawzjzh];
						if(range.location!=NSNotFound && range.location <[pgdmx.gddm length])
						{
							m_SHB_MainFlag = 1;
							m_SHB_MainGd=pgdmx;
						}
					}
				}
				else
				{
					if (m_SHB_MainFlag != 1)
					{
						m_SHB_MainFlag = 1;
						m_SHB_MainGd=pgdmx;
					}
				}
				m_SHBGDNUM++;
			}
				break;	
			case SBAG:
			{
				if(sba_flag!=1)
				{
					sba_flag=1;
					tmpsbagd=pgdmx;
				}
				if(pgdmx.bxyjygd)
				{
					if(sba_xyflag!=1)
					{
						sba_xyflag=1;
						tmpsbaxygd=pgdmx;
					}
					if (m_SBA_MainxyFlag != 1)
					{
						m_SBA_MainxyFlag = 1;
						m_SBA_MainxyGd=pgdmx;
					}
				}
				
				if(nloginWtType==SBAG)
				{
					if (m_SBA_MainFlag != 1 && rawzjzh)
					{
						range=[pgdmx.gddm rangeOfString:rawzjzh];
						if(range.location!=NSNotFound && range.location <[pgdmx.gddm length])
						{
							m_SBA_MainFlag = 1;
							m_SBA_MainGd=pgdmx;
						}
					}
				}
				else
				{
					if (m_SBA_MainFlag != 1)
					{
						m_SBA_MainFlag = 1;
						m_SBA_MainGd=pgdmx;
					}
				}
				m_SBAGDNUM++;
			}
				break;
			case SBGB:
			{
				if(sbg_flag!=1)
				{
					sbg_flag=1;
					tmpsbggd=pgdmx;
				}
				if(pgdmx.bxyjygd)
				{
					if(sbg_xyflag!=1)
					{
						sbg_xyflag=1;
						tmpsbgxygd=pgdmx;
					}
					if (m_SBG_MainxyFlag != 1)
					{
						m_SBG_MainxyFlag = 1;
						m_SBG_MainxyGd=pgdmx;
					}
				}
				if(nloginWtType==SBGB)
				{
					if (m_SBG_MainFlag != 1 && rawzjzh)
					{
						range=[pgdmx.gddm rangeOfString:rawzjzh];
						if(range.location!=NSNotFound && range.location <[pgdmx.gddm length])
						{
							m_SBG_MainFlag = 1;
							m_SBG_MainGd=pgdmx;
						}
					}
				}
				else
				{
					if (m_SBG_MainFlag != 1)
					{
						m_SBG_MainFlag = 1;
						m_SBG_MainGd=pgdmx;
					}
				}
				m_SBGGDNUM++;
			}
				break;
			case SBBG:
			{
				if(sbb_flag!=1)
				{
					sbb_flag=1;
					tmpsbbgd=pgdmx;
				}
				if(pgdmx.bxyjygd)
				{
					if(sbb_xyflag!=1)
					{
						sbb_xyflag=1;
						tmpsbbxygd=pgdmx;
					}
					if (m_SBB_MainxyFlag != 1)
					{
						m_SBB_MainxyFlag = 1;
						m_SBB_MainxyGd=pgdmx;
					}
				}
				
				if(nloginWtType==SBBG)
				{
					if (m_SBB_MainFlag != 1 && rawzjzh)
					{
						range=[pgdmx.gddm rangeOfString:rawzjzh];
						if(range.location!=NSNotFound && range.location <[pgdmx.gddm length])
						{
							m_SBB_MainFlag = 1;
							m_SBB_MainGd=pgdmx;
						}
					}
				}
				else
				{
					if (m_SBB_MainFlag != 1)
					{
						m_SBB_MainFlag = 1;
						m_SBB_MainGd=pgdmx;
					}
				}
				m_SBBGDNUM++;
			}
				break;
			default:
				break;
		}
	}
	if(bonlybg)
		m_bsfcguser=YES;
	else 
		m_bsfcguser=NO;
	if(m_SZA_MainFlag != 1 && sza_flag==1)
	{
		m_SZA_MainFlag=1;
		m_SZA_MainGd=tmpszagd;
	}
	if(m_SZB_MainFlag != 1 && szb_flag==1)
	{
		m_SZB_MainFlag=1;
		m_SZB_MainGd=tmpszbgd;
	}
	if(m_SHA_MainFlag != 1 && sha_flag==1)
	{
		m_SHA_MainFlag=1;
		m_SHA_MainGd=tmpshagd;
	}
	if(m_SHB_MainFlag != 1 && shb_flag==1)
	{
		m_SHB_MainFlag=1;
		m_SHB_MainGd=tmpshbgd;
	}
	if(m_SBA_MainFlag != 1 && sba_flag==1)
	{
		m_SBA_MainFlag=1;
		m_SBA_MainGd=tmpsbagd;
	}
	if(m_SBG_MainFlag != 1 && sbg_flag==1)
	{
		m_SBG_MainFlag=1;
		m_SBG_MainGd=tmpsbggd;
	}
	if(m_SBB_MainFlag != 1 && sbb_flag==1)
	{
		m_SBB_MainFlag=1;
		m_SBB_MainGd=tmpsbbgd;
	}
	if(m_SZA_MainxyFlag != 1 && sza_xyflag==1)
	{
		m_SZA_MainxyFlag=1;
		m_SZA_MainxyGd=tmpszaxygd;
	}
	if(m_SZB_MainxyFlag != 1 && szb_xyflag==1)
	{
		m_SZB_MainxyFlag=1;
		m_SZB_MainxyGd=tmpszbxygd;
	}
	if(m_SHA_MainxyFlag != 1 && sha_xyflag==1)
	{
		m_SHA_MainxyFlag=1;
		m_SHA_MainxyGd=tmpshaxygd;
	}
	if(m_SHB_MainxyFlag != 1 && shb_xyflag==1)
	{
		m_SHB_MainxyFlag=1;
		m_SHB_MainxyGd=tmpshbxygd;
	}
	if(m_SBA_MainxyFlag != 1 && sba_xyflag==1)
	{
		m_SBA_MainxyFlag=1;
		m_SBA_MainxyGd=tmpsbaxygd;
	}
	if(m_SBG_MainxyFlag != 1 && sbg_xyflag==1)
	{
		m_SBG_MainxyFlag=1;
		m_SBG_MainxyGd=tmpsbgxygd;
	}
	if(m_SBB_MainxyFlag != 1 && sbb_xyflag==1)
	{
		m_SBB_MainxyFlag=1;
		m_SBB_MainxyGd=tmpsbbxygd;
	}
}

-(int)GetZhlbFromGddm:(NSString *)gddm
{
	int zhlb=SZAG;
	
	if(gddms && [gddms count])
	{
		for(GdmxInfo *pgdmx in gddms)
		{
			if([pgdmx.gddm isEqualToString:gddm])
			{
				zhlb=pgdmx.wttype;
				break;
			}
			
		}
	}
	return zhlb;
}

-(BOOL)IsMainGd:(NSString *)gddm
{
	if(gddm==nil)
		return NO;
	if(m_SZA_MainGd && m_SZA_MainGd.gddm && [m_SZA_MainGd.gddm isEqualToString:gddm])
		return YES;
	if(m_SZB_MainGd && m_SZB_MainGd.gddm && [m_SZB_MainGd.gddm isEqualToString:gddm])
		return YES;
	if(m_SHA_MainGd && m_SHA_MainGd.gddm && [m_SHA_MainGd.gddm isEqualToString:gddm])
		return YES;
	
	if(m_SHB_MainGd && m_SHB_MainGd.gddm && [m_SHB_MainGd.gddm isEqualToString:gddm])
		return YES;
	if(m_SBB_MainGd && m_SBB_MainGd.gddm && [m_SBB_MainGd.gddm isEqualToString:gddm])
		return YES;
	if(m_SBG_MainGd && m_SBG_MainGd.gddm && [m_SBG_MainGd.gddm isEqualToString:gddm])
		return YES;
	return NO;
}

-(GdmxInfo *)GetGddm:(NSString *)strgddm
{
    for(GdmxInfo *pgddm in gddms)
    {
        if([pgddm.gddm isEqualToString:strgddm])
            return pgddm;
    }
    return nil;
}

-(NSString *)GetMainGdStr:(NSString *)gddm
{
	if([self IsMainGd:gddm])
		return @"(主)";
	return @"";
}

-(int)GetGdCountBySc:(int)ntype
{
	int count=0;
	for(GdmxInfo *pgddm in gddms)
	{
		if(pgddm.wttype==SHAG || pgddm.wttype==SHBG)
		{
			if(ntype==SH)
				count++;
		}
		else 
		{
			if(ntype==SZ)
				count++;
		}
	}
	return count;
}

-(GdmxInfo *)GetGdMxByScIndex:(int)ntype withindex:(int)index
{
	int count=0;
	for(GdmxInfo *pgddm in gddms)
	{
		if(pgddm.wttype==SHAG || pgddm.wttype==SHBG)
		{
			if(ntype==SH)
			{
				if(count==index)
					return pgddm;
				count++;
			}
		}
		else 
		{
			if(ntype==SZ)
			{
				if(count==index)
					return pgddm;
				count++;
			}
		}
	}
	return nil;
}

-(int)GetGdIndexBySc:(int)ntype withgdmx:(GdmxInfo *)pgdmx
{
	if(pgdmx==nil)
		return -1;
	int count=0;
	for(GdmxInfo *pgddm in gddms)
	{
		if(pgddm.wttype==SHAG || pgddm.wttype==SHBG)
		{
			if(ntype==SH)
			{
				if(pgddm==pgdmx)
					return count;
				count++;
			}
		}
		else 
		{
			if(ntype==SZ)
			{
				if(pgddm==pgdmx)
					return count;
				count++;
			}
		}
	}
	return -1;
}
@end

@implementation Yhxxmx

@synthesize yhdm,yhmc,yhzh,zjzh,nzrmmflag,nzcmmflag,nyemmflag,nbz;

-(id)init
{
	self=[super init];
	if(self)
	{
		yhdm=nil;
		yhzh=nil;
		yhmc=nil;
        zjzh=nil;
		nzrmmflag=0;
		nzcmmflag=0;
		nyemmflag=0;
		nbz=0;
	}
	return self;
}


-(void)dealloc
{
	RELEASEOBJ(yhdm);
	RELEASEOBJ(yhzh);
	RELEASEOBJ(yhmc);
    RELEASEOBJ(zjzh);
	[super dealloc];
}

-(void)encodeWithCoder:(NSCoder *)encoder
{
	[encoder encodeObject:yhdm forKey:@"Yhxxmxyhdm"];
	[encoder encodeObject:yhmc forKey:@"Yhxxmxyhmc"];
	[encoder encodeObject:yhzh forKey:@"Yhxxmxyhzh"];
    [encoder encodeObject:zjzh forKey:@"Yhxxmxzjzh"];
	[encoder encodeInt:nbz forKey:@"Yhxxmxbz"];
	[encoder encodeInt:nzrmmflag forKey:@"Yhxxmxzrmm"];
	[encoder encodeInt:nzcmmflag forKey:@"Yhxxmxzcmm"];
	[encoder encodeInt:nyemmflag forKey:@"Yhxxmxyhyemm"];
}

-(id)initWithCoder:(NSCoder *)aDecoder
{
	self=[super init];
	if(self)
	{
		yhdm=[[aDecoder decodeObjectForKey:@"Yhxxmxyhdm"] retain];
		yhmc=[[aDecoder decodeObjectForKey:@"Yhxxmxyhmc"] retain];
		yhzh=[[aDecoder decodeObjectForKey:@"Yhxxmxyhzh"] retain];
        zjzh=[[aDecoder decodeObjectForKey:@"Yhxxmxzjzh"] retain];
		nbz=[aDecoder decodeIntForKey:@"Yhxxmxbz"];
		nzrmmflag=[aDecoder decodeIntForKey:@"Yhxxmxzrmm"];
		nzcmmflag=[aDecoder decodeIntForKey:@"Yhxxmxzcmm"];
		nyemmflag=[aDecoder decodeIntForKey:@"Yhxxmxyhyemm"];
	}
	
	return self;
}

-(NSString *)GetBzStr
{
	switch (nbz) {
		case 0:
			return @"人民币";
		case 1:
			return  @"美元";
		case 2:
			return @"港币";
	}
	return @"人民币";
}

-(Yhxxmx *)deepcopy
{
	Yhxxmx *pyhmx=[[Yhxxmx alloc]init];
	
	pyhmx.nbz=nbz;
	pyhmx.nzcmmflag=nzcmmflag;
	pyhmx.nzrmmflag=nzrmmflag;
	pyhmx.nyemmflag=nyemmflag;
	pyhmx.yhdm=[[NSString alloc] initWithFormat:@"%@",yhdm];
	[pyhmx.yhdm release];
	pyhmx.yhmc=[[NSString alloc] initWithFormat:@"%@",yhmc];
	[pyhmx.yhmc release];
	pyhmx.yhzh=[[NSString alloc] initWithFormat:@"%@",yhzh];
	[pyhmx.yhzh release];
    pyhmx.zjzh=[[NSString alloc] initWithFormat:@"%@",zjzh];
    [pyhmx.zjzh release];
	return pyhmx;
}
@end

@implementation YhxxInfo
	
@synthesize savedate,yhmxs,bqueryyhflag;
		
				 
-(id)init 
{
	self=[super init];
	if(self)
	{
		savedate=nil;
		yhmxs=nil;
		bqueryyhflag=NO;
	}
	return self;
}

-(void)dealloc
{
	if(yhmxs && [yhmxs count])
	{
		for(Yhxxmx *pyhxx in yhmxs)
		{
			RELEASEOBJ(pyhxx)
		}
		[yhmxs removeAllObjects];
	}
	RELEASEOBJ(yhmxs);
	RELEASEOBJ(savedate);
	[super dealloc];
}
				 
-(void)encodeWithCoder:(NSCoder *)encoder
{
	[encoder encodeObject:yhmxs forKey:@"YhxxInfoyhmxs"];
	[encoder encodeObject:savedate forKey:@"YhxxInfosavedate"];
}
				 
-(id)initWithCoder:(NSCoder *)aDecoder
{
	self=[super init];
	if(self)
	{
		yhmxs=[[aDecoder decodeObjectForKey:@"YhxxInfoyhmxs"] retain];
		savedate=[[aDecoder decodeObjectForKey:@"YhxxInfosavedate"] retain];
	}
	return self;
}
	
-(void)releaseyhmxs
{
	if(yhmxs)
	{
		for(Yhxxmx *pyhmx in yhmxs)
		{
			RELEASEOBJ(pyhmx);
		}
		[yhmxs removeAllObjects];
	}
	RELEASEOBJ(yhmxs)
	RELEASEOBJ(savedate);
}

-(Yhxxmx *)GetYhmxFromYhmc:(NSString *)yhmc
{
	if(yhmxs)
	{
		for(Yhxxmx *pyhmx in yhmxs)
		{
			if(pyhmx)
			{
				NSString *tmpstr=[NSString stringWithFormat:@"%@  %@",pyhmx.yhdm,pyhmx.yhmc];
				if([yhmc isEqualToString:tmpstr])
					return pyhmx;
			}
		}
	}
	return nil;
}

-(Yhxxmx *)GetYhmxFromzjzh:(NSString *)zjzh
{
    if(yhmxs)
    {
        for(Yhxxmx *pyhmx in yhmxs)
        {
            if(pyhmx)
            {
                if([zjzh isEqualToString:pyhmx.zjzh])
                    return pyhmx;
            }
        }
    }
    return nil;
}
@end

@implementation ScStrucInfo
@synthesize  setcode,ntype,nzhlb,nxsflag,nbz,ngzbz,jldw,nxsdw,nzsdw,nkcdw,nsbdw,nsbxx,nsbsx,fyj,fqbj,zqdm,lbname;

-(id)init
{
	self = [super init];
	if(self)
	{
		zqdm=nil;
		lbname=nil;
		jldw=nil;
	}
	return self;
}

-(void)dealloc
{
	RELEASEOBJ(jldw);
	RELEASEOBJ(zqdm);
	RELEASEOBJ(lbname);
	[super dealloc];
}

-(void)encodeWithCoder:(NSCoder *)encoder
{
	[encoder encodeInt:setcode forKey:@"ScStrucInfosetcode"];
	[encoder encodeInt:ntype forKey:@"ScStrucInfontype"];
	[encoder encodeInt:nzhlb forKey:@"ScStrucInfonzhlb"];
	[encoder encodeInt:nxsflag forKey:@"ScStrucInfonxsflag"];
	
	[encoder encodeInt:nbz forKey:@"ScStrucInfonbz"];
	[encoder encodeInt:ngzbz forKey:@"ScStrucInfongzbz"];
	[encoder encodeInt:nxsdw forKey:@"ScStrucInfonxsdw"];

	[encoder encodeInt:nzsdw forKey:@"ScStrucInfonzsdw"];
	[encoder encodeInt:nkcdw forKey:@"ScStrucInfonkcdw"];
	[encoder encodeInt:nsbdw forKey:@"ScStrucInfonsbdw"];
	[encoder encodeInt:nsbxx forKey:@"ScStrucInfonsbxx"];

	[encoder encodeInt:nsbsx forKey:@"ScStrucInfonsbsx"];
	[encoder encodeFloat:fyj forKey:@"ScStrucInfofyj"];
	[encoder encodeFloat:fqbj forKey:@"ScStrucInfofqbj"];

	[encoder encodeObject:zqdm forKey:@"ScStrucInfozqdm"];
	[encoder encodeObject:lbname forKey:@"ScStrucInfolbname"];
	[encoder encodeObject:jldw forKey:@"ScStrucInfojldw"];
}

-(id)initWithCoder:(NSCoder *)aDecoder
{
	self=[super init];
	if(self)
	{
		setcode=[aDecoder decodeIntForKey:@"ScStrucInfosetcode"];
		ntype=[aDecoder decodeIntForKey:@"ScStrucInfontype"];
		nzhlb=[aDecoder decodeIntForKey:@"ScStrucInfonzhlb"];
		nxsflag=[aDecoder decodeIntForKey:@"ScStrucInfonxsflag"];
		
		nbz=[aDecoder decodeIntForKey:@"ScStrucInfonbz"];
		ngzbz=[aDecoder decodeIntForKey:@"ScStrucInfongzbz"];
		nxsdw=[aDecoder decodeIntForKey:@"ScStrucInfonxsdw"];
		
		nzsdw=[aDecoder decodeIntForKey:@"ScStrucInfonzsdw"];
		nkcdw=[aDecoder decodeIntForKey:@"ScStrucInfonkcdw"];
		nsbdw=[aDecoder decodeIntForKey:@"ScStrucInfonsbdw"];
		nsbxx=[aDecoder decodeIntForKey:@"ScStrucInfonsbxx"];
		
		nsbsx=[aDecoder decodeIntForKey:@"ScStrucInfonsbsx"];
		fyj=[aDecoder decodeFloatForKey:@"ScStrucInfofyj"];
		fqbj=[aDecoder decodeFloatForKey:@"ScStrucInfofqbj"];
		
		zqdm=[[aDecoder decodeObjectForKey:@"ScStrucInfozqdm"] retain];
		lbname=[[aDecoder decodeObjectForKey:@"ScStrucInfolbname"] retain];
		jldw=[[aDecoder decodeObjectForKey:@"ScStrucInfojldw"] retain];
	}
	
	return self;
}

-(ScStrucInfo *)deepcopy
{
	ScStrucInfo *pscstruc=[[ScStrucInfo alloc]init];
	
	pscstruc.setcode=setcode;
	pscstruc.ntype=ntype;
	pscstruc.nzhlb=nzhlb;
	pscstruc.nxsflag=nxsflag;
	
	pscstruc.nbz=nbz;
	pscstruc.ngzbz=ngzbz;
	pscstruc.nxsdw=nxsdw;
	
	pscstruc.nzsdw=nzsdw;
	pscstruc.nkcdw=nkcdw;
	pscstruc.nsbdw=nsbdw;
	pscstruc.nsbxx=nsbxx;
	
	pscstruc.nsbsx=nsbsx;
	pscstruc.fyj=fyj;
	pscstruc.fqbj=fqbj;
	
	pscstruc.zqdm=[[NSString alloc] initWithFormat:@"%@",zqdm];
	[pscstruc.zqdm release];
	pscstruc.lbname=[[NSString alloc] initWithFormat:@"%@",lbname];
	[pscstruc.lbname release];
	pscstruc.jldw=[[NSString alloc] initWithFormat:@"%@",jldw];
	[pscstruc.jldw release];
	return pscstruc;
}
@end


@implementation ScInfo
@synthesize m_scinfos,m_bHasSCStruc,savedate;

-(id)init
{
	self = [super init];
	if(self)
	{
		m_scinfos=nil;
		m_bHasSCStruc=NO;
	}
	return self;
}

-(void) dealloc
{
	if(m_scinfos && [m_scinfos count])
	{
		for(ScStrucInfo *scinfo in m_scinfos)
		{
			RELEASEOBJ(scinfo)
		}
		[m_scinfos removeAllObjects];
	}
	RELEASEOBJ(m_scinfos)
	RELEASEOBJ(savedate)
	[super dealloc];
}

-(void)encodeWithCoder:(NSCoder *)encoder
{
	[encoder encodeObject:m_scinfos forKey:@"ScInfom_scinfos"];
	[encoder encodeObject:savedate forKey:@"ScInfosavedate"];
}

-(id)initWithCoder:(NSCoder *)aDecoder
{
	self=[super init];
	if(self)
	{
		m_scinfos=[[aDecoder decodeObjectForKey:@"ScInfom_scinfos"] retain];
		savedate=[[aDecoder decodeObjectForKey:@"ScInfosavedate"] retain];
	}
	
	return self;
}

-(void)releasescinfos
{
	if(m_scinfos)
	{
		for(ScStrucInfo *pscinfo in m_scinfos)
		{
			RELEASEOBJ(pscinfo)
		}
		[m_scinfos removeAllObjects];
	}
	RELEASEOBJ(m_scinfos)
	m_bHasSCStruc=NO;
}

-(void)loadScInfos
{
	[self releasescinfos];
	NSString* path = [[NSBundle mainBundle] pathForResource:@"scinfo2" ofType:@"ini"];
	NSString* fileText = [NSString stringWithContentsOfFile:path encoding:NSASCIIStringEncoding error:nil];
	//MyNsLog(path);
	//MyNsLog(fileText);
	
	NSRange range,range1;
	NSString *tmpstr1,*tmpstr2,*tmpstr3=fileText,*tmpstr4;
	
	range=[fileText rangeOfString:@"SC_NUM="];
	if(range.location==NSNotFound)
		return;
	range1=[fileText rangeOfString:@"SC_0001="];
	if(range1.location==NSNotFound)
		return;
	int num=[[fileText substringWithRange:NSMakeRange((range.location+range.length), (range1.location-1))] intValue];
	if(num<=0)
		return;
	m_bHasSCStruc=YES;
	m_scinfos=[[NSMutableArray alloc] initWithCapacity:num+1];
	for(int i=1,j=0;i<=num;i++)
	{
		range=[tmpstr3 rangeOfString:[NSString stringWithFormat:@"SC_%04i=",i]];
		if(range.location==NSNotFound)
			break;
		if(i==num)
			tmpstr1=[tmpstr3 substringFromIndex:(range.location+range.length)];
		else 
		{
			range1=[tmpstr3 rangeOfString:[NSString stringWithFormat:@"SC_%04i=",i+1]];
			if(range1.location==NSNotFound)
				break;
			tmpstr1=[tmpstr3 substringWithRange:NSMakeRange((range.location+range.length), range1.location)];
			tmpstr4=[tmpstr3 substringFromIndex:range1.location];
			tmpstr3=tmpstr4;
		}
		if(tmpstr1==nil)
			break;
		range.location=0;
		range.length=0;
		ScStrucInfo *pnewstru=[ScStrucInfo new];
		for(j=0;j<17;j++)
		{
			range1=[[tmpstr1 substringFromIndex:(range.location+range.length)] rangeOfString:@","];
			if(range1.location==NSNotFound)
				break;
			tmpstr2=[[tmpstr1 substringWithRange:NSMakeRange((range.location+range.length), range1.location)] stringByReplacingOccurrencesOfString:@" " withString:@""];
			switch (j) {
				case 0:
					pnewstru.setcode=[tmpstr2 intValue];//市场
					break;
				case 1:
					pnewstru.zqdm=[[NSString alloc]  initWithFormat:@"%@",tmpstr2];//代码规则
					[pnewstru.zqdm release];
					break;
				case 2:
					pnewstru.ntype=[tmpstr2 intValue];//类型
					break;
				case 3:
					pnewstru.nzhlb=[tmpstr2 intValue];//账户类别
					break;
				case 4:
					pnewstru.lbname=[[NSString alloc]  initWithFormat:@"%@",tmpstr2];//类别名称
					[pnewstru.lbname release];
					break;
				case 5:
					pnewstru.nxsflag=[tmpstr2 intValue];//小数位数
					break;
				case 6:
					pnewstru.nbz=[tmpstr2 intValue];//币种
					break;
				case 7:
					pnewstru.ngzbz=[tmpstr2 intValue];//国债标志
					break;
				case 8:
					pnewstru.jldw=[[NSString alloc]  initWithFormat:@"%@",tmpstr2];//计量单位
					[pnewstru.jldw release];
					break;
				case 9:
					pnewstru.nxsdw=[tmpstr2 intValue];//现手单位
					break;
				case 10:
					pnewstru.nzsdw=[tmpstr2 intValue];//总手单位
					break;
				case 11:
					pnewstru.nkcdw=[tmpstr2 intValue];//库存单位
					break;
				case 12:
					pnewstru.nsbdw=[tmpstr2 intValue];//申报单位
					break;
				case 13:
					pnewstru.nsbxx=[tmpstr2 intValue];//申报下限
					break;
				case 14:
					pnewstru.nsbsx=[tmpstr2 intValue];//申报上限(万)
					break;
				case 15:
					pnewstru.fyj=[tmpstr2 floatValue];//佣金
					break;
				case 16:
					pnewstru.fqbj=[tmpstr2 floatValue];//佣金起步价
					break;
				default:
					break;
			}
			range.location+=(range.length+range1.location);
			range.length=range1.length;
		}
		if(j<17)
		{
			[pnewstru release];
			continue;
		}
		[m_scinfos addObject:pnewstru];
	}
}
@end

@implementation JjZhInfo

@synthesize jjgsdm,jjgsmc,jjzh,khmc,zjhm;

-(id)init
{
	self=[super init];
	if(self)
	{
		jjgsdm=nil;
		jjgsmc=nil;
		jjzh=nil;
		khmc=nil;
		zjhm=nil;
	}
	return self;
}

-(void)dealloc
{
	RELEASEOBJ(jjgsdm)
	RELEASEOBJ(jjgsmc)
	RELEASEOBJ(jjzh)
	RELEASEOBJ(khmc)
	RELEASEOBJ(zjhm)
	[super dealloc];
}

-(void)encodeWithCoder:(NSCoder *)encoder
{
	[encoder encodeObject:jjgsdm forKey:@"JjZhInfojjgsdm"];
	[encoder encodeObject:jjgsmc forKey:@"JjZhInfojjgsmc"];
	[encoder encodeObject:jjzh forKey:@"JjZhInfojjzh"];
	[encoder encodeObject:khmc forKey:@"JjZhInfokhmc"];
	[encoder encodeObject:zjhm forKey:@"JjZhInfozjhm"];
}

-(id)initWithCoder:(NSCoder *)aDecoder
{
	self=[super init];
	if(self)
	{
		jjgsdm=[[aDecoder decodeObjectForKey:@"JjZhInfojjgsdm"]retain];
		jjgsmc=[[aDecoder decodeObjectForKey:@"JjZhInfojjgsmc"]retain];
		jjzh=[[aDecoder decodeObjectForKey:@"JjZhInfojjzh"]retain];
		khmc=[[aDecoder decodeObjectForKey:@"JjZhInfokhmc"]retain];
		zjhm=[[aDecoder decodeObjectForKey:@"JjZhInfozjhm"]retain];
	}
	
	return self;
}

-(JjZhInfo *)deepcopy
{
	JjZhInfo *pjjzh=[[JjZhInfo alloc]init];
	
	pjjzh.jjgsdm=[[NSString alloc] initWithFormat:@"%@",jjgsdm];
	[pjjzh.jjgsdm release];
	pjjzh.jjgsmc=[[NSString alloc] initWithFormat:@"%@",jjgsmc];
	[pjjzh.jjgsmc release];
	pjjzh.jjzh=[[NSString alloc] initWithFormat:@"%@",jjzh];
	[pjjzh.jjzh release];
	pjjzh.khmc=[[NSString alloc] initWithFormat:@"%@",khmc];
	[pjjzh.khmc release];
	pjjzh.zjhm=[[NSString alloc] initWithFormat:@"%@",zjhm];
	[pjjzh.zjhm release];
	return pjjzh;
}
@end

@implementation JjgsInfo

@synthesize jjgsdm,jjgsmc,jjgsdesc,njjbs;

-(id)init
{
	self=[super init];
	if(self)
	{
		jjgsdm=nil;
		jjgsmc=nil;
		jjgsdesc=nil;
		njjbs=0;
	}
	return self;
}

-(void)dealloc
{
	RELEASEOBJ(jjgsdm)
	RELEASEOBJ(jjgsmc)
	RELEASEOBJ(jjgsdesc)
	[super dealloc];
}

-(void)encodeWithCoder:(NSCoder *)encoder
{
	[encoder encodeInt:njjbs  forKey:@"JjgsInfonjjbs"];
	[encoder encodeObject:jjgsdm forKey:@"JjgsInfojjgsdm"];
	[encoder encodeObject:jjgsmc forKey:@"JjgsInfojjgsmc"];
	[encoder encodeObject:jjgsdesc forKey:@"JjgsInfojjgsdesc"];
}

-(id)initWithCoder:(NSCoder *)aDecoder
{
	self=[super init];
	if(self)
	{
		njjbs=[aDecoder decodeIntForKey:@"JjgsInfonjjbs"];
		jjgsdm=[[aDecoder decodeObjectForKey:@"JjgsInfojjgsdm"]retain];
		jjgsmc=[[aDecoder decodeObjectForKey:@"JjgsInfojjgsmc"]retain];
		jjgsdesc=[[aDecoder decodeObjectForKey:@"JjgsInfojjgsdesc"]retain];
	}
	
	return self;
}

-(JjgsInfo *)deepcopy
{
	JjgsInfo *pjjgs=[[JjgsInfo alloc]init];
	
	pjjgs.jjgsdm=[[NSString alloc] initWithFormat:@"%@",jjgsdm];
	[pjjgs.jjgsdm release];
	pjjgs.jjgsmc=[[NSString alloc] initWithFormat:@"%@",jjgsmc];
	[pjjgs.jjgsmc release];
	pjjgs.jjgsdesc=[[NSString alloc] initWithFormat:@"%@",jjgsdesc];
	[pjjgs.jjgsdesc release];
	pjjgs.njjbs=njjbs;
	return pjjgs;
}
@end


@implementation JjdmInfo

@synthesize jjjz,grzdsgje,frzdsgje,jjgsdm,jjdm,jjmc,jjjyzt,njjjyzt,njjbs,zdcyfe,zgshfe;

-(id)init
{
	self=[super init];
	if(self)
	{
		njjbs=0;
		zdcyfe=0.0f;
		zgshfe=0.0f;
		njjjyzt=0;
		jjjz=0.0f;
		grzdsgje=0.0f;
		frzdsgje=0.0f;
		jjgsdm=nil;
		jjdm=nil;
		jjmc=nil;
		jjjyzt=nil;
	}
	return self;
}

-(void)dealloc
{
	RELEASEOBJ(jjgsdm)
	RELEASEOBJ(jjdm)
	RELEASEOBJ(jjmc)
	RELEASEOBJ(jjjyzt)
	
	[super dealloc];
}

-(NSString *)GetJjDescribe
{
	return [NSString  stringWithFormat:@"%@ %@(%@)",jjdm,jjmc,jjjyzt];
}

-(NSString *)GetJjDescribe2
{
	return [NSString stringWithFormat:@"%@ %@",jjdm,jjmc];
}

-(void)encodeWithCoder:(NSCoder *)encoder
{
	[encoder encodeFloat:zdcyfe  forKey:@"JjdmInfozdcyfe"];
	[encoder encodeDouble:zgshfe  forKey:@"JjdmInfozgshfe"];
	[encoder encodeFloat:jjjz  forKey:@"JjdmInfojjjz"];
	[encoder encodeFloat:grzdsgje  forKey:@"JjdmInfogrzdsgje"];
	[encoder encodeFloat:frzdsgje  forKey:@"JjdmInfofrzdsgje"];
	[encoder encodeInt:njjjyzt  forKey:@"JjdmInfonjjjyzt"];
	[encoder encodeInt:njjbs  forKey:@"JjdmInfonjjbs"];
	[encoder encodeObject:jjgsdm forKey:@"JjdmInfojjgsdm"];
	[encoder encodeObject:jjdm forKey:@"JjdmInfojjdm"];
	[encoder encodeObject:jjmc forKey:@"JjdmInfojjmc"];
	[encoder encodeObject:jjjyzt forKey:@"JjdmInfojjjyzt"];
}

-(id)initWithCoder:(NSCoder *)aDecoder
{
	self=[super init];
	if(self)
	{
		zdcyfe=[aDecoder decodeFloatForKey:@"JjdmInfozdcyfe"];
		zgshfe=[aDecoder decodeDoubleForKey:@"JjdmInfozgshfe"];
		jjjz=[aDecoder decodeFloatForKey:@"JjdmInfojjjz"];
		grzdsgje=[aDecoder decodeFloatForKey:@"JjdmInfogrzdsgje"];
		frzdsgje=[aDecoder decodeFloatForKey:@"JjdmInfofrzdsgje"];
		njjjyzt=[aDecoder decodeIntForKey:@"JjdmInfonjjjyzt"];
		njjbs=[aDecoder decodeIntForKey:@"JjdmInfonjjbs"];
		jjgsdm=[[aDecoder decodeObjectForKey:@"JjdmInfojjgsdm"]retain];
		jjdm=[[aDecoder decodeObjectForKey:@"JjdmInfojjdm"]retain];
		jjmc=[[aDecoder decodeObjectForKey:@"JjdmInfojjmc"]retain];
		jjjyzt=[[aDecoder decodeObjectForKey:@"JjdmInfojjjyzt"]retain];
	}
	
	return self;
}

-(JjdmInfo *)deepcopy
{
	JjdmInfo *pjjdm=[[JjdmInfo alloc]init];
	
	pjjdm.jjgsdm=[[NSString alloc] initWithFormat:@"%@",jjgsdm];
	[pjjdm.jjgsdm release];
	pjjdm.jjdm=[[NSString alloc] initWithFormat:@"%@",jjdm];
	[pjjdm.jjdm release];
	pjjdm.jjmc=[[NSString alloc] initWithFormat:@"%@",jjmc];
	[pjjdm.jjmc release];
	pjjdm.jjjyzt=[[NSString alloc] initWithFormat:@"%@",jjjyzt];
	[pjjdm.jjjyzt release];
	pjjdm.njjbs=njjbs;
	pjjdm.zdcyfe=zdcyfe;
	pjjdm.zgshfe=zgshfe;
	pjjdm.jjjz=jjjz;
	pjjdm.grzdsgje=grzdsgje;
	pjjdm.frzdsgje=frzdsgje;
	pjjdm.njjjyzt=njjjyzt;
	return pjjdm;
}
@end


@implementation JjInfo

@synthesize  bqueryjjzhflag,strjjzhztbz,njjzhztbz,jjzhinfo,jjdminfo,jjzhdict,jjdmdict,nksgjjnum,nkrgjjnum,jjsgdminfo,jjrgdminfo,jjgsinfo,savedate,njjnum;

-(id)init
{
	self=[super init];
	if(self)
	{
		bqueryjjzhflag=NO;
		strjjzhztbz=nil;
		njjzhztbz=0;
		jjzhinfo=nil;
		jjdminfo=nil;
		jjzhdict=nil;
		jjdmdict=nil;
		nksgjjnum=0;
		nkrgjjnum=0;
		njjnum=0;
		jjsgdminfo=nil;
		jjrgdminfo=nil;
		jjgsinfo=nil;
	}
	return self;
}


-(void)dealloc
{
	[self releasejjinfos];
	[super dealloc];
}

-(void)encodeWithCoder:(NSCoder *)encoder
{
	[encoder encodeObject:jjgsinfo forKey:@"JjInfojjgsinfo"];
	[encoder encodeObject:jjzhinfo forKey:@"JjInfojjzhinfo"];
	[encoder encodeObject:jjdminfo forKey:@"JjInfojjdminfo"];
	[encoder encodeObject:savedate forKey:@"JjInfosavedate"];
}

-(id)initWithCoder:(NSCoder *)aDecoder
{
	self=[super init];
	if(self)
	{
		jjgsinfo=[[aDecoder decodeObjectForKey:@"JjInfojjgsinfo"] retain];
		jjzhinfo=[[aDecoder decodeObjectForKey:@"JjInfojjzhinfo"] retain];
		jjdminfo=[[aDecoder decodeObjectForKey:@"JjInfojjdminfo"] retain];
		savedate=[aDecoder decodeObjectForKey:@"JjInfosavedate"];
	}
	
	return self;
}

-(void)releasejjinfos
{
	RELEASEOBJ(strjjzhztbz)
	if(jjdmdict)
	{
		[jjdmdict removeAllObjects];
		RELEASEOBJ(jjdmdict)
	}
	if(jjzhdict)
	{
		[jjzhdict removeAllObjects];
		RELEASEOBJ(jjzhdict)
	}
	if(jjsgdminfo)
	{
		[jjsgdminfo removeAllObjects];
		RELEASEOBJ(jjsgdminfo)
	}
	if(jjrgdminfo)
	{
		[jjrgdminfo removeAllObjects];
		RELEASEOBJ(jjrgdminfo)
	}
	if(jjzhinfo)
	{
		for(JjZhInfo *pjjzh in jjzhinfo)
		{
			RELEASEOBJ(pjjzh)
		}
		[jjzhinfo removeAllObjects];
	}
	RELEASEOBJ(jjzhinfo)
	if(jjdminfo)
	{
		for(JjdmInfo *pjjdm in jjdminfo)
		{
			RELEASEOBJ(pjjdm)
		}
		[jjdminfo removeAllObjects];
	}
	RELEASEOBJ(jjdminfo)
	if(jjgsinfo)
	{
		for(JjgsInfo *pjjgs in jjgsinfo)
		{
			RELEASEOBJ(pjjgs)
		}
		[jjgsinfo removeAllObjects];
	}
	RELEASEOBJ(jjgsinfo)
	nksgjjnum=0;
	nkrgjjnum=0;
	njjnum=0;
}

-(NSString *)GetJJDescribe:(NSString *)jjdm
{
	JjdmInfo *pjjdm=[jjdmdict objectForKey:jjdm];
	if(pjjdm)
		return [pjjdm GetJjDescribe2];
	else 
		return jjdm;
}

-(JjdmInfo *)GetJjdmInfo:(NSString *)jjdm
{
	JjdmInfo *pjjdm=[jjdmdict objectForKey:jjdm];
	return pjjdm;
}
@end

@implementation LoginInfo
@synthesize m_rawzjzh,m_loginWtType,m_rawbranchid,m_strzhlx,naqfs,bsavezh;

-(id)init
{
	self=[super init];
	if(self)
	{
		m_rawzjzh=nil;
		m_loginWtType=SHHY;
		m_rawbranchid=nil;
		m_strzhlx=nil;
		bsavezh=YES;
		naqfs=0;
	}
	return self;
}

-(void)dealloc
{
	RELEASEOBJ(m_rawzjzh)
	RELEASEOBJ(m_rawbranchid)
	RELEASEOBJ(m_strzhlx)
	[super dealloc];
}

-(void)encodeWithCoder:(NSCoder *)encoder
{
	[encoder encodeBool:bsavezh  forKey:@"LoginInfobsavezh"];
	[encoder encodeInt:naqfs  forKey:@"LoginInfonaqfs"];
	[encoder encodeInt:m_loginWtType  forKey:@"LoginInfom_loginWtType"];
	[encoder encodeObject:m_rawzjzh forKey:@"LoginInfom_rawzjzh"];
	[encoder encodeObject:m_rawbranchid	forKey:@"LoginInfom_rawbranchid"];
	[encoder encodeObject:m_strzhlx	forKey:@"LoginInfom_strzhlx"];
}

-(id)initWithCoder:(NSCoder *)aDecoder
{
	self=[super init];
	if(self)
	{
		bsavezh=[aDecoder decodeBoolForKey:@"LoginInfobsavezh"];
		naqfs=[aDecoder decodeIntForKey:@"LoginInfonaqfs"];
		m_loginWtType=[aDecoder decodeIntForKey:@"LoginInfom_loginWtType"];
		m_rawzjzh=[[aDecoder decodeObjectForKey:@"LoginInfom_rawzjzh"]retain];
		m_rawbranchid=[[aDecoder decodeObjectForKey:@"LoginInfom_rawbranchid"]retain];
		m_strzhlx=[[aDecoder decodeObjectForKey:@"LoginInfom_strzhlx"]retain];
	}
	return self;
}

-(LoginInfo *)deepcopy
{
	LoginInfo *plogininfo=[[LoginInfo alloc]init];
	
	plogininfo.bsavezh=bsavezh;
	plogininfo.naqfs=naqfs;
	plogininfo.m_loginWtType=m_loginWtType;
	plogininfo.m_rawzjzh=[[NSString alloc] initWithFormat:@"%@",m_rawzjzh];
	[plogininfo.m_rawzjzh release];
	plogininfo.m_rawbranchid=[[NSString alloc] initWithFormat:@"%@",m_rawbranchid];
	[plogininfo.m_rawbranchid release];
	plogininfo.m_strzhlx=[[NSString alloc] initWithFormat:@"%@",m_strzhlx];
	[plogininfo.m_strzhlx release];
	return plogininfo;
}

-(void)releasecontent
{
	RELEASEOBJ(m_rawzjzh)
	RELEASEOBJ(m_rawbranchid)
	RELEASEOBJ(m_strzhlx)
}

-(NSString *)GetZhDescribe:(int)nqsbs
{
	NSString *tempstr=@"";
	switch (m_loginWtType) {
		case SZAG:
			tempstr=[NSString stringWithFormat:@"深A %@",m_rawzjzh];
			break;
		case SZBG:
			tempstr=[NSString stringWithFormat:@"深B %@",m_rawzjzh];
			break;
		case SHAG:
			tempstr=[NSString stringWithFormat:@"沪A %@",m_rawzjzh];
			break;
		case SHBG:
			tempstr=[NSString stringWithFormat:@"沪B %@",m_rawzjzh];
			break;
		case SBAG:
			tempstr=[NSString stringWithFormat:@"三板A %@",m_rawzjzh];
			break;
		case SBBG:
			tempstr=[NSString stringWithFormat:@"三板B %@",m_rawzjzh];
			break;
		case SBGB:
			tempstr=[NSString stringWithFormat:@"三板G %@",m_rawzjzh];
			break;
		case SHHY:
			tempstr=[NSString stringWithFormat:@"资金帐号 %@",m_rawzjzh];
			break;
		case KHWT:
			{
				if(nqsbs==ZSZQ_DLL)
					tempstr=[NSString stringWithFormat:@"牛卡号 %@",m_rawzjzh];
				else 
					tempstr=[NSString stringWithFormat:@"客户号 %@",m_rawzjzh];
			}
			break;
		default:
			tempstr=[NSString stringWithFormat:@"%@",m_rawzjzh];
			break;
	}
	return  tempstr;
}
@end

@implementation MultizhLogininfo

@synthesize zhinfos;

-(id)init
{
	self=[super init];
	if(self)
	{
		zhinfos=nil;
	}
	return self;
}

-(void)dealloc
{
	[self releasezhinfos];
	[super dealloc];
}

-(void)releasezhinfos
{
	if(zhinfos)
	{
		for(LoginInfo *pInfo in zhinfos)
		{
			RELEASEOBJ(pInfo)
		}
		[zhinfos removeAllObjects];
	}
	RELEASEOBJ(zhinfos)
}

-(void)releasezhinfos2
{
	if(zhinfos)
	{
		for(LoginInfo *pInfo in zhinfos)
		{
			RELEASEOBJ(pInfo)
		}
		[zhinfos removeAllObjects];
	}
}

-(void)encodeWithCoder:(NSCoder *)encoder
{
	[encoder encodeObject:zhinfos forKey:@"MultizhLogininfozhinfos"];
}

-(id)initWithCoder:(NSCoder *)aDecoder
{
	self=[super init];
	if(self)
	{
		zhinfos=[[aDecoder decodeObjectForKey:@"MultizhLogininfozhinfos"] retain];
	}
	return self;
}

-(int)getIndex:(LoginInfo *)prawLogin
{
	if(prawLogin==nil)
		return 0;
	if(zhinfos==nil)
		return 0;
	if([zhinfos count]<=0)
		return 0;
	int index=0;
	for(LoginInfo *plogin in zhinfos)
	{
		if(plogin.m_loginWtType==prawLogin.m_loginWtType && [plogin.m_rawzjzh isEqualToString:prawLogin.m_rawzjzh])
			return index;
		index++;
	}
	return 0;
}

-(int)getIndex:(NSString *)account withzhlx:(LoginMode *)ploginmode
{
	if(account || zhinfos==nil)
		return 0;
	if([zhinfos count]<=0)
		return 0;
	int index=0;
	for(LoginInfo *plogin in zhinfos)
	{
		if([account isEqualToString:plogin.m_rawzjzh]==YES)
		{
			if(ploginmode)
			{
				if(ploginmode.zhlx==plogin.m_loginWtType)
					return index;
			}
			else 
				return index;
		}
		index++;
	}
	return 0;
}
@end

@implementation TradeSiteInfo

@synthesize bfindbest,nlastindex,tradesites;

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
	[self releaseSiteinfos];
	[super dealloc];
}

-(void)encodeWithCoder:(NSCoder *)encoder
{
	[encoder encodeBool:bfindbest  forKey:@"TradeSiteInfobfindbest"];
	[encoder encodeInt:nlastindex  forKey:@"TradeSiteInfonlastindex"];
	[encoder encodeObject:tradesites forKey:@"TradeSiteInfotradesites"];
}

-(id)initWithCoder:(NSCoder *)aDecoder
{
	self=[super init];
	if(self)
	{
		bfindbest=[aDecoder decodeBoolForKey:@"TradeSiteInfobfindbest"];
		nlastindex=[aDecoder decodeIntForKey:@"TradeSiteInfonlastindex"];
		tradesites=[[aDecoder decodeObjectForKey:@"TradeSiteInfotradesites"] retain];
	}
	

	return self;
}

-(void)releaseSiteinfos
{
	if(tradesites)
	{
		for(TradeSite *psite in tradesites)
		{
			RELEASEOBJ(psite)
		}
		[tradesites removeAllObjects];
	}
	RELEASEOBJ(tradesites)
}
@end

@implementation DataLitj

@synthesize Wifisndlen,Wifircvlen,g3sndlen,g3rcvlen,savedate,cleandate;


-(id)init
{
	self=[super init];
	if(self)
	{
		Wifisndlen=0.0f;
		Wifircvlen=0.0f;
		g3sndlen=0.0f;
		g3rcvlen=0.0f;
		cleandate=nil;
		savedate=nil;
	}
	return self;
}


-(void)dealloc
{
	RELEASEOBJ(savedate)
	RELEASEOBJ(cleandate)
	[super dealloc];
}

-(void)encodeWithCoder:(NSCoder *)encoder
{
	[encoder encodeFloat:Wifisndlen  forKey:@"DataLitjWifisndlen"];
	[encoder encodeFloat:Wifircvlen  forKey:@"DataLitjWifircvlen"];
	[encoder encodeFloat:g3sndlen forKey:@"DataLitjg3sndlen"];
	[encoder encodeFloat:g3rcvlen forKey:@"DataLitjg3rcvlen"];
	[encoder encodeObject:savedate forKey:@"DataLitjsavedate"];
	[encoder encodeObject:cleandate forKey:@"DataLitjcleandate"];
}

-(id)initWithCoder:(NSCoder *)aDecoder
{
	self=[super init];
	if(self)
	{
		Wifisndlen=[aDecoder decodeFloatForKey:@"DataLitjWifisndlen"];
		Wifircvlen=[aDecoder decodeFloatForKey:@"DataLitjWifircvlen"];
		g3sndlen=[aDecoder decodeFloatForKey:@"DataLitjg3sndlen"];
		g3rcvlen=[aDecoder decodeFloatForKey:@"DataLitjg3rcvlen"];
		savedate=[[aDecoder decodeObjectForKey:@"DataLitjsavedate"]retain];
		cleandate=[[aDecoder decodeObjectForKey:@"DataLitjcleandate"]retain];
	}
	
	return self;
}

-(DataLitj *)deepcopy
{
	DataLitj *pDataInfo=[[DataLitj alloc]init];
	
	pDataInfo.Wifisndlen=Wifisndlen;
	pDataInfo.Wifircvlen=Wifircvlen;
	pDataInfo.g3sndlen=g3sndlen;
	pDataInfo.g3rcvlen=g3rcvlen;
	pDataInfo.savedate=[NSDate date];
	pDataInfo.cleandate=cleandate;
	return pDataInfo;
}

-(void)clean
{
	Wifisndlen=0.0f;
	Wifircvlen=0.0f;
	g3sndlen=0.0f;
	g3rcvlen=0.0f;
	cleandate=[NSDate date];
}
@end


@implementation HttpProxyInfo

@synthesize beUsedFlag,httpProxyAddress,httpProxyPort,httpProxyUsername,httpProxyPassword;

-(id)init
{
	self=[super init];
	if(self)
	{
		beUsedFlag=NO;
		httpProxyAddress=@"";
		httpProxyPort=@"";
		httpProxyUsername=@"";
		httpProxyPassword=@"";
	}
	return self;
}

-(void)dealloc
{
	RELEASEOBJ(httpProxyAddress)
	RELEASEOBJ(httpProxyPort)
	RELEASEOBJ(httpProxyUsername)
	RELEASEOBJ(httpProxyPassword)
	[super dealloc];
}

-(void)encodeWithCoder:(NSCoder *)encoder
{
	[encoder encodeBool:beUsedFlag forKey:@"HttpProxyUseFlag"];
	[encoder encodeObject:httpProxyAddress forKey:@"HttpProxyAddress"];
	[encoder encodeObject:httpProxyPort forKey:@"HttpProxyPort"];
	[encoder encodeObject:httpProxyUsername forKey:@"HttpProxyUsername"];
	[encoder encodeObject:httpProxyPassword forKey:@"HttpProxyPassword"];
}

-(id)initWithCoder:(NSCoder *)aDecoder
{
	self=[super init];
	if(self)
	{
		beUsedFlag=[aDecoder decodeBoolForKey:@"HttpProxyUseFlag"];
		httpProxyAddress=[[aDecoder decodeObjectForKey:@"HttpProxyAddress"]retain];
		httpProxyPort=[[aDecoder decodeObjectForKey:@"HttpProxyPort"]retain];
		httpProxyUsername=[[aDecoder decodeObjectForKey:@"HttpProxyUsername"]retain];
		httpProxyPassword=[[aDecoder decodeObjectForKey:@"HttpProxyPassword"]retain];
	}
	
	return self;
}

-(HttpProxyInfo *)deepcopy
{
	HttpProxyInfo *pjjzh=[[HttpProxyInfo alloc]init];
	
	pjjzh.beUsedFlag = self.beUsedFlag;
	pjjzh.httpProxyAddress=[[NSString alloc] initWithFormat:@"%@",httpProxyAddress];
	[pjjzh.httpProxyAddress release];
	pjjzh.httpProxyPort=[[NSString alloc] initWithFormat:@"%@",httpProxyPort];
	[pjjzh.httpProxyPort release];
	pjjzh.httpProxyUsername=[[NSString alloc] initWithFormat:@"%@",httpProxyUsername];
	[pjjzh.httpProxyUsername release];
	pjjzh.httpProxyPassword=[[NSString alloc] initWithFormat:@"%@",httpProxyPassword];
	[pjjzh.httpProxyPassword release];
	return pjjzh;
}
@end



@implementation gridCellInfoForCache

@synthesize gridCellInfoArray;
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
	[self releaseSiteinfos];
	[super dealloc];
}

-(void)encodeWithCoder:(NSCoder *)encoder
{
	[encoder encodeObject:gridCellInfoArray forKey:@"gridCellInfoForCacheArray"];
}

-(id)initWithCoder:(NSCoder *)aDecoder
{
	self=[super init];
	if(self)
	{
		
		gridCellInfoArray=[[aDecoder decodeObjectForKey:@"gridCellInfoForCacheArray"] retain];
	}
	return self;
}



-(void)releaseSiteinfos
{
	if(gridCellInfoArray)
	{
		for(GridCellInfo *psite in gridCellInfoArray)
		{
			RELEASEOBJ(psite)
		}
		[gridCellInfoArray removeAllObjects];
	}
	RELEASEOBJ(gridCellInfoArray)
}

@end

@implementation localCache
NSString *tdxpath=@"/Library/Caches/tdximac";
NSString *cachepath=@"/T0002";
NSString *wtdatapath=@"/T0002/wtdata";
NSString *wtcachepath=@"/T0002/wtcache";
NSString *hqdatapath=@"/T0002/hqdata";
NSString *hqcachepath=@"/T0002/hqcache";
NSString *zxdatapath=@"/T0002/zxdata";
NSString *zxcachepath=@"/T0002/zxcache";

-(id)initloginInfo:(NSString *)qsjc
{
	self=[super init];
	if(self)
	{
		m_qsjc=[[NSString alloc] initWithFormat:@"%@",qsjc];
		NSFileManager *fm;
		fm=[NSFileManager defaultManager];
		

		NSArray* pathArray = NSSearchPathForDirectoriesInDomains(NSApplicationSupportDirectory, NSUserDomainMask, YES);
		
		int pathLen = [pathArray count];
		NSString* curuserpath = nil;
		for(int i=0;i<pathLen;i++)
		{
			curuserpath = [pathArray objectAtIndex:i];
			
		}
		//NSLog(@"%@",filePath);
		curuserpath = [curuserpath stringByAppendingString:MAC_PATHSTRING];
		//NSLog(@"%@",filePath);
		
		//NSLog(@"%@",theFilePath);
		NSError * error;
		

		[[NSFileManager defaultManager] createDirectoryAtPath:curuserpath withIntermediateDirectories:YES attributes:nil error:&error];
			
		
		//NSLog(@"%@",curuserpath);

		//NSString *curuserpath=NSHomeDirectory();
		if(fm)
		{
			//NSError *error;
			NSString *tmptdxpath=[NSString stringWithFormat:@"%@%@",curuserpath,tdxpath];
			[fm createDirectoryAtPath:tmptdxpath withIntermediateDirectories:YES attributes:nil error:&error];
			NSString *tmpqspath=[NSString stringWithFormat:@"%@%@/%@",curuserpath,tdxpath,qsjc];
			[fm createDirectoryAtPath:tmpqspath withIntermediateDirectories:YES attributes:nil error:&error];
			NSString  *strcachepath=[NSString stringWithFormat:@"%@%@/%@%@",curuserpath,tdxpath,qsjc,cachepath];
			[fm createDirectoryAtPath:strcachepath withIntermediateDirectories:YES attributes:nil error:&error];
			NSString *strwtdatapath=[NSString stringWithFormat:@"%@%@/%@%@",curuserpath,tdxpath,qsjc,wtdatapath];
			[fm createDirectoryAtPath:strwtdatapath withIntermediateDirectories:YES attributes:nil error:&error];
			NSString *strhqdatapath=[NSString stringWithFormat:@"%@%@/%@%@",curuserpath,tdxpath,qsjc,hqdatapath];
			[fm createDirectoryAtPath:strhqdatapath withIntermediateDirectories:YES attributes:nil error:&error];
			NSString *strzxdatapath=[NSString stringWithFormat:@"%@%@/%@%@",curuserpath,tdxpath,qsjc,zxdatapath];
			[fm createDirectoryAtPath:strzxdatapath withIntermediateDirectories:YES attributes:nil error:&error];
			NSString *strwtcachepath=[NSString stringWithFormat:@"%@%@/%@%@",curuserpath,tdxpath,qsjc,wtcachepath];
			[fm createDirectoryAtPath:strwtcachepath withIntermediateDirectories:YES attributes:nil error:&error];
			NSString *strhqcachepath=[NSString stringWithFormat:@"%@%@/%@%@",curuserpath,tdxpath,qsjc,hqcachepath];
			[fm createDirectoryAtPath:strhqcachepath withIntermediateDirectories:YES attributes:nil error:&error];
			NSString *strzxcachepath=[NSString stringWithFormat:@"%@%@/%@%@",curuserpath,tdxpath,qsjc,zxcachepath];
			[fm createDirectoryAtPath:strzxcachepath withIntermediateDirectories:YES attributes:nil error:&error];
		}
		logincachefile=[[NSString alloc] initWithFormat:@"%@%@/%@%@/login.arch",curuserpath,tdxpath,qsjc,wtdatapath];
		multilogincachefile=[[NSString alloc] initWithFormat:@"%@%@/%@%@/multilogin.arch",curuserpath,tdxpath,qsjc,wtdatapath];
		scinfocachefile=[[NSString alloc] initWithFormat:@"%@%@/%@%@/scinfo.arch",curuserpath,tdxpath,qsjc,wtdatapath];
		localjysitecachefile=[[NSString alloc] initWithFormat:@"%@%@/%@%@/localjysite.arch",curuserpath,tdxpath,qsjc,wtdatapath];
		localhqsitecachefile=[[NSString alloc] initWithFormat:@"%@%@/%@%@/localhqsite.arch",curuserpath,tdxpath,qsjc,hqdatapath];
		localhqparamcachefile=[[NSString alloc] initWithFormat:@"%@%@/%@%@/hqparam.arch",curuserpath,tdxpath,qsjc,hqdatapath];
		locallltjcachefile=[[NSString alloc] initWithFormat:@"%@%@/%@%@/datalitj.arch",curuserpath,tdxpath,qsjc,hqdatapath];
		localzxlinkcachefile=[[NSString alloc] initWithFormat:@"%@%@/%@%@/zxlinks.arch",curuserpath,tdxpath,qsjc,zxdatapath];
		gpdmlcachefile =[[NSString alloc] initWithFormat:@"%@%@/%@%@/gpdml.arch",curuserpath,tdxpath,qsjc,hqdatapath];
		versionparamcachefile= [[NSString alloc] initWithFormat:@"%@%@/%@%@/versionparam.arch",curuserpath,tdxpath,qsjc,hqdatapath];
		styleparamcachefile = [[NSString alloc] initWithFormat:@"%@%@/%@%@/styleparam.arch",curuserpath,tdxpath,qsjc,hqdatapath];
		gridcellparamcachefile= [[NSString alloc] initWithFormat:@"%@%@/%@%@/gridcellparam.arch",curuserpath,tdxpath,qsjc,hqdatapath];
		httpproxyinfoparamcachefile= [[NSString alloc] initWithFormat:@"%@%@/%@%@/httpproxyparam.arch",curuserpath,tdxpath,qsjc,hqdatapath];
	}
	return self;
}

-(void)initWithtoken:(NSString *)strtoken
{
	NSArray* pathArray = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSAllDomainsMask, YES);
	NSString* curuserpath = nil;
	int pathLen = [pathArray count];
	for(int i=0;i<pathLen;i++)
	{
		curuserpath = [pathArray objectAtIndex:i];
	}
	//NSString *curuserpath=NSHomeDirectory();
	gddmcachefile=[[NSString alloc] initWithFormat:@"%@%@/%@%@/%@gddm.arch",curuserpath,tdxpath,m_qsjc,wtdatapath,strtoken];
	yhxxcachefile=[[NSString alloc] initWithFormat:@"%@%@/%@%@/%@yhxx.arch",curuserpath,tdxpath,m_qsjc,wtdatapath,strtoken];
	jjxxcachefile=[[NSString alloc] initWithFormat:@"%@%@/%@%@/%@jjxx.arch",curuserpath,tdxpath,m_qsjc,wtdatapath,strtoken];
	lcxxcachefile=[[NSString alloc] initWithFormat:@"%@%@/%@%@/%@lcxx.arch",curuserpath,tdxpath,m_qsjc,wtdatapath,strtoken];
	localjyparamcachefile=[[NSString alloc] initWithFormat:@"%@%@/%@%@/%@jyparam.arch",curuserpath,tdxpath,m_qsjc,wtdatapath,strtoken];
}

-(void)dealloc
{
	[m_qsjc release];
	[scinfocachefile release];
	[logincachefile release];
	[multilogincachefile release];
	[gpdmlcachefile release];
	[gddmcachefile release];
	[yhxxcachefile release];
	[jjxxcachefile release];
	[lcxxcachefile release];
	[localjysitecachefile release];
	[localhqsitecachefile release];
	[localhqparamcachefile release];
	[locallltjcachefile release];
	[localzxlinkcachefile release];
	[localjyparamcachefile release];
	[styleparamcachefile release];
	[httpproxyinfoparamcachefile release];
	[gridcellparamcachefile release];
	[versionparamcachefile release];
	[super dealloc];
}

-(void)SaveHttpProxyInfo:(HttpProxyInfo*) httpproxyinfocache{//写http代理信息
	if(httpproxyinfocache==nil)
		return;
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	
	NSMutableData *cachedata=[NSMutableData	alloc];
	NSKeyedArchiver *archiver=[[NSKeyedArchiver alloc] initForWritingWithMutableData:cachedata];
	[archiver encodeObject:httpproxyinfocache forKey:@"HttpProxyInfoCache"];
	[archiver finishEncoding];
	[cachedata writeToFile:httpproxyinfoparamcachefile atomically:YES];
	[archiver release];
	[cachedata release];
	[pool drain];
}
-(HttpProxyInfo *)loadHttpProxyInfo{//读http代理信息
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	HttpProxyInfo *styleinfo=nil;

	NSData *cachedata=[[NSData alloc]initWithContentsOfFile:httpproxyinfoparamcachefile];
	if(cachedata)
	{
		NSKeyedUnarchiver *archiver=[[NSKeyedUnarchiver alloc] initForReadingWithData:cachedata];
		HttpProxyInfo * ptimeinfo =[archiver decodeObjectForKey:@"HttpProxyInfoCache"];
		[archiver finishDecoding];
		
	
		
		if (ptimeinfo) {
			styleinfo = [ptimeinfo deepcopy];
		}
		[archiver release];
	}
	[cachedata release];
	[pool drain];
	return styleinfo;
}

-(void)SaveGridCellInfo:(gridCellInfoForCache*) gridcellinfocache{//写列表信息
	if(gridcellinfocache==nil)
		return;
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	NSMutableData *cachedata=[NSMutableData	alloc];
	NSKeyedArchiver *archiver=[[NSKeyedArchiver alloc] initForWritingWithMutableData:cachedata];
	[archiver encodeObject:gridcellinfocache forKey:@"ClientGridCellInfo"];
	[archiver finishEncoding];
	[cachedata writeToFile:gridcellparamcachefile atomically:YES];
	[archiver release];
	[cachedata release];
	[pool drain];
}
-(BOOL)loadGridcCellInfo:(gridCellInfoForCache*) gridcellinfocache{//读列表信息
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	BOOL bret=NO;
	NSData *cachedata=[[NSData alloc]initWithContentsOfFile:gridcellparamcachefile];
	if(cachedata && [cachedata length])
	{
		NSKeyedUnarchiver *archiver=[[NSKeyedUnarchiver alloc] initForReadingWithData:cachedata];
		gridCellInfoForCache *ptmpSiteInfo=[archiver decodeObjectForKey:@"ClientGridCellInfo"];
		[archiver finishDecoding];
		
		bret=YES;
		
		if(gridcellinfocache.gridCellInfoArray)
			[gridcellinfocache releaseSiteinfos];
		int sitecount=[ptmpSiteInfo.gridCellInfoArray count];
		if(sitecount)
		{
			gridcellinfocache.gridCellInfoArray=[[NSMutableArray alloc] initWithCapacity:sitecount+1];
			[gridcellinfocache.gridCellInfoArray release];
			for(GridCellInfo *psite in ptmpSiteInfo.gridCellInfoArray)
			{
				if(psite)
					[gridcellinfocache.gridCellInfoArray addObject:[psite deepcopy]];
			}
		}
		[ptmpSiteInfo.gridCellInfoArray removeAllObjects];
		[archiver release];
	}
	
	[cachedata release];
	[pool drain];
	return bret;
		
}
-(void)SaveStyleParam:(StyleParams*) styleinfo{//写风格信息
	if(styleinfo==nil)
		return;
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	
	NSMutableData *cachedata=[NSMutableData	alloc];
	NSKeyedArchiver *archiver=[[NSKeyedArchiver alloc] initForWritingWithMutableData:cachedata];
	[archiver encodeObject:styleinfo forKey:@"ClientStyleinfo"];
	[archiver finishEncoding];
	[cachedata writeToFile:styleparamcachefile atomically:YES];
	[archiver release];
	[cachedata release];
	[pool drain];
}
-(StyleParams *)loadStyleParam{//读风格信息
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	StyleParams *styleinfo=nil;
	BOOL bret=NO;
	NSData *cachedata=[[NSData alloc]initWithContentsOfFile:styleparamcachefile];
	if(cachedata)
	{
		NSKeyedUnarchiver *archiver=[[NSKeyedUnarchiver alloc] initForReadingWithData:cachedata];
		StyleParams * pstyleinfo =[archiver decodeObjectForKey:@"ClientStyleinfo"];
		[archiver finishDecoding];
		
		bret=YES;
		
		styleinfo = [pstyleinfo deepcopy];
		[archiver release];
	}
	[cachedata release];
	[pool drain];
	return styleinfo;
}
-(void)SaveVersionParam:(VersionParam*) versioninfo{//写版本信息
	if(versioninfo==nil)
		return;
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	
	NSMutableData *cachedata=[NSMutableData	alloc];
	NSKeyedArchiver *archiver=[[NSKeyedArchiver alloc] initForWritingWithMutableData:cachedata];
	[archiver encodeObject:versioninfo forKey:@"ClientVersioninfo"];
	[archiver finishEncoding];
	[cachedata writeToFile:versionparamcachefile atomically:YES];
	[archiver release];
	[cachedata release];
	[pool drain];
	
}
-(BOOL)loadVersionParam:(VersionParam*) versioninfo{//读版本信息
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	
	BOOL bret=NO;
	NSData *cachedata=[[NSData alloc]initWithContentsOfFile:versionparamcachefile];
	if(cachedata)
	{
		NSKeyedUnarchiver *archiver=[[NSKeyedUnarchiver alloc] initForReadingWithData:cachedata];
		VersionParam * ptimeinfo =[archiver decodeObjectForKey:@"ClientVersioninfo"];
		[archiver finishDecoding];
		
		bret=YES;
		
		if (ptimeinfo) {
			versioninfo.versionID = ptimeinfo.versionID;
			versioninfo.hostUpdate = ptimeinfo.hostUpdate;
			versioninfo.riskUpdate = ptimeinfo.riskUpdate;
			versioninfo.serviceUpdate = ptimeinfo.serviceUpdate;
			versioninfo.zxUpdate = ptimeinfo.serviceUpdate;
			versioninfo.blzdone = ptimeinfo.blzdone;
			versioninfo.blzdtwo = ptimeinfo.blzdtwo;
		}
		[archiver release];
	}
	[cachedata release];
	[pool drain];
	return bret;
	
}

-(void)SaveGpdml:(GpdmlInfo *)pgdmlinfo;//保存代码链
{
	if(pgdmlinfo==nil)
		return;
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	pgdmlinfo.savedate=[NSDate date];
	
	NSMutableData *cachedata=[NSMutableData	alloc];
	NSKeyedArchiver *archiver=[[NSKeyedArchiver alloc] initForWritingWithMutableData:cachedata];
	[archiver encodeObject:pgdmlinfo forKey:@"ClientGpdmlinfo"];
	[archiver finishEncoding];
	[cachedata writeToFile:gpdmlcachefile atomically:YES];
	[archiver release];
	[cachedata release];
	pgdmlinfo.savedate=nil;
	[pool drain];
}

-(BOOL)loadGpdml:(GpdmlInfo *)pgdmlinfo;//读取代码链
{
//    return NO;
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	BOOL bret=NO;
	NSData *cachedata=[[NSData alloc]initWithContentsOfFile:gpdmlcachefile];
	if(cachedata && [cachedata length])
	{
		NSKeyedUnarchiver *archiver=[[NSKeyedUnarchiver alloc] initForReadingWithData:cachedata];
		GpdmlInfo *ptmpgdinfo=[archiver decodeObjectForKey:@"ClientGpdmlinfo"];
		[archiver finishDecoding];
		
		NSDateFormatter* tempMatter = [[NSDateFormatter alloc]init];
		[tempMatter setDateFormat:@"yyyyMMdd"];
		NSString* strDate1 = [tempMatter stringFromDate:ptmpgdinfo.savedate];
		NSString* strDate2 = [tempMatter stringFromDate:[NSDate date]];
		[tempMatter release];
		if([strDate1 isEqualToString:strDate2])//每天第一次用的时候取服务器，再登录就取缓存
		{
			bret=YES;
			if((pgdmlinfo.szGPArray)||(pgdmlinfo.shGPArray))
				[pgdmlinfo releasegpdml];
			int gpcount=[ptmpgdinfo.szGPArray count];
			if(gpcount)
			{
				pgdmlinfo.szGPArray=[[NSMutableArray alloc] initWithArray:ptmpgdinfo.szGPArray];
			}
			gpcount=[ptmpgdinfo.shGPArray count];
			if(gpcount)
			{
				pgdmlinfo.shGPArray=[[NSMutableArray alloc] initWithArray:ptmpgdinfo.shGPArray];
			}
		}
		[ptmpgdinfo.shGPArray removeAllObjects];
		[ptmpgdinfo.szGPArray removeAllObjects];
		[archiver release];
	}
	
	[cachedata release];
	[pool drain];
	return bret;
}


-(void)SaveGddm:(GdInfo *)pgdinfo//保存股东代码
{
	if(pgdinfo==nil)
		return;
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	pgdinfo.savedate=[NSDate date];
	
	NSMutableData *cachedata=[NSMutableData	alloc];
	NSKeyedArchiver *archiver=[[NSKeyedArchiver alloc] initForWritingWithMutableData:cachedata];
	[archiver encodeObject:pgdinfo forKey:@"ClientGdinfo"];
	[archiver finishEncoding];
	[cachedata writeToFile:gddmcachefile atomically:YES];
	[archiver release];
	[cachedata release];
	pgdinfo.savedate=nil;
	[pool drain];
}

-(BOOL)loadGddm:(GdInfo *)pgdinfo//读取股东代码
{
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	BOOL bret=NO;
	NSData *cachedata=[[NSData alloc]initWithContentsOfFile:gddmcachefile];
	if(cachedata && [cachedata length])
	{
		NSKeyedUnarchiver *archiver=[[NSKeyedUnarchiver alloc] initForReadingWithData:cachedata];
		GdInfo *ptmpgdinfo=[archiver decodeObjectForKey:@"ClientGdinfo"];
		[archiver finishDecoding];
		
		NSDateFormatter* tempMatter = [[NSDateFormatter alloc]init];
		[tempMatter setDateFormat:@"yyyyMMdd"];
		NSString* strDate1 = [tempMatter stringFromDate:ptmpgdinfo.savedate];
		NSString* strDate2 = [tempMatter stringFromDate:[NSDate date]];
		[tempMatter release];
		if([strDate1 isEqualToString:strDate2])//每天第一次用的时候取服务器，再登录就取缓存
		{
			bret=YES;
			if(pgdinfo.gddms)
				[pgdinfo releasegdmxs];
			int gdcount=[ptmpgdinfo.gddms count];
			if(gdcount)
			{
				pgdinfo.gddms=[[NSMutableArray alloc] initWithCapacity:gdcount+1];
				[pgdinfo.gddms release];
				for(GdmxInfo *pgdmx in ptmpgdinfo.gddms)
				{
			 		if(pgdmx)
						[pgdinfo.gddms addObject:[pgdmx deepcopy]];
				}
			}
		}
		[ptmpgdinfo.gddms removeAllObjects];
		[archiver release];
	}
	
	[cachedata release];
	[pool drain];
	return bret;
}

-(void)SaveYhxx:(YhxxInfo *)pYhInfo//保存银行信息
{
	if(pYhInfo==nil)
		return;
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	pYhInfo.savedate=[NSDate date];
	
	NSMutableData *cachedata=[NSMutableData	alloc];
	NSKeyedArchiver *archiver=[[NSKeyedArchiver alloc] initForWritingWithMutableData:cachedata];
	[archiver encodeObject:pYhInfo forKey:@"ClientYhInfo"];
	[archiver finishEncoding];
	[cachedata writeToFile:yhxxcachefile atomically:YES];
	[archiver release];
	[cachedata release];
	pYhInfo.savedate=nil;
	[pool drain];
}

-(BOOL)loadYhxx:(YhxxInfo *)pYhInfo//读取银行信息
{
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	BOOL bret=NO;
	NSData *cachedata=[[NSData alloc]initWithContentsOfFile:yhxxcachefile];
	if(cachedata && [cachedata length])
	{
		NSKeyedUnarchiver *archiver=[[NSKeyedUnarchiver alloc] initForReadingWithData:cachedata];
		YhxxInfo *ptmpyhinfo=[archiver decodeObjectForKey:@"ClientYhInfo"];
		[archiver finishDecoding];
		
		NSDateFormatter* tempMatter = [[NSDateFormatter alloc]init];
		[tempMatter setDateFormat:@"yyyyMMdd"];
		NSString* strDate1 = [tempMatter stringFromDate:ptmpyhinfo.savedate];
		NSString* strDate2 = [tempMatter stringFromDate:[NSDate date]];
		[tempMatter release];
		if([strDate1 isEqualToString:strDate2])
		{
			bret=YES;
			if(pYhInfo.yhmxs)
				[pYhInfo releaseyhmxs];
			int yhcount=[ptmpyhinfo.yhmxs count];
			if(yhcount)
			{
				pYhInfo.yhmxs=[[NSMutableArray alloc] initWithCapacity:yhcount+1];
				[pYhInfo.yhmxs release];
				for(Yhxxmx *pyhmx in ptmpyhinfo.yhmxs)
				{
					if(pyhmx)
						[pYhInfo.yhmxs addObject:[pyhmx deepcopy]];
				}
			}
		}
		[ptmpyhinfo.yhmxs removeAllObjects];
		[archiver release];
	}
	
	[cachedata release];
	[pool drain];
	return bret;	
}

-(void)SaveJjxx:(JjInfo *)pJjinfos//保存基金信息
{
	if(pJjinfos==nil)
		return;
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	pJjinfos.savedate=[NSDate date];
	
	NSMutableData *cachedata=[NSMutableData	alloc];
	NSKeyedArchiver *archiver=[[NSKeyedArchiver alloc] initForWritingWithMutableData:cachedata];
	[archiver encodeObject:pJjinfos forKey:@"ClientJjInfo"];
	[archiver finishEncoding];
	[cachedata writeToFile:jjxxcachefile atomically:YES];
	[archiver release];
	[cachedata release];
	pJjinfos.savedate=nil;
	[pool drain];
}

-(BOOL)loadJjxx:(JjInfo *)pJjinfos//读取基金信息
{
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	BOOL bret=NO;
	NSData *cachedata=[[NSData alloc]initWithContentsOfFile:jjxxcachefile];
	if(cachedata && [cachedata length])
	{
		NSKeyedUnarchiver *archiver=[[NSKeyedUnarchiver alloc] initForReadingWithData:cachedata];
		JjInfo *ptmpjjinfo=[archiver decodeObjectForKey:@"ClientJjInfo"];
		[archiver finishDecoding];
		NSDateFormatter* tempMatter = [[NSDateFormatter alloc]init];
		[tempMatter setDateFormat:@"yyyyMMdd"];
		NSString* strDate1 = [tempMatter stringFromDate:ptmpjjinfo.savedate];
		NSString* strDate2 = [tempMatter stringFromDate:[NSDate date]];
		[tempMatter release];
		if([strDate1 isEqualToString:strDate2])
		{
			bret=YES;
			[pJjinfos releasejjinfos];
			int count=[ptmpjjinfo.jjgsinfo count];
			if(count)
			{
				pJjinfos.jjgsinfo=[[NSMutableArray alloc] initWithCapacity:count+1];
				[pJjinfos.jjgsinfo release];
				for(JjgsInfo *pjjgs in ptmpjjinfo.jjgsinfo)
				{
					if(pjjgs)
						[pJjinfos.jjgsinfo addObject:[pjjgs deepcopy]];
				}
			}
			count=[ptmpjjinfo.jjzhinfo count];
			if(count)
			{
				pJjinfos.jjzhinfo=[[NSMutableArray alloc] initWithCapacity:count+1];
				[pJjinfos.jjzhinfo release];
				pJjinfos.jjzhdict=[[NSMutableDictionary alloc] initWithCapacity:count+1];
				[pJjinfos.jjzhdict release];
				JjZhInfo *pnewjjzh=nil;
				for(JjZhInfo *pjjzh in ptmpjjinfo.jjzhinfo)
				{
					if(pjjzh)
					{
						pnewjjzh=[pjjzh deepcopy];
						[pJjinfos.jjzhinfo addObject:pnewjjzh];
						[pJjinfos.jjzhdict setObject:pnewjjzh forKey:pnewjjzh.jjgsdm];
					}
				}
			}
			count=[ptmpjjinfo.jjdminfo count];
			if(count)
			{
				pJjinfos.jjdminfo=[[NSMutableArray alloc] initWithCapacity:count+1];
				[pJjinfos.jjdminfo release];
				pJjinfos.jjsgdminfo=[[NSMutableArray alloc] initWithCapacity:count+1];
				[pJjinfos.jjsgdminfo release];
				pJjinfos.jjrgdminfo=[[NSMutableArray alloc] initWithCapacity:count+1];
				[pJjinfos.jjrgdminfo release];
				pJjinfos.jjdmdict=[[NSMutableDictionary alloc] initWithCapacity:count+1];
				[pJjinfos.jjdmdict release];
				JjdmInfo *pnewjjdm=nil;
				for(JjdmInfo *pjjdm in ptmpjjinfo.jjdminfo)
				{
					if(pjjdm)
					{
						pnewjjdm=[pjjdm deepcopy];
						[pJjinfos.jjdminfo addObject:pnewjjdm];
						[pJjinfos.jjdmdict setObject:pnewjjdm forKey:pnewjjdm.jjdm];
						if(pnewjjdm.njjjyzt==0)
						{
							pJjinfos.nksgjjnum++;
							[pJjinfos.jjsgdminfo addObject:pnewjjdm];
						}
						else if(pnewjjdm.njjjyzt==1)
						{
							pJjinfos.nkrgjjnum++;
							[pJjinfos.jjrgdminfo addObject:pnewjjdm];
						}
						pJjinfos.njjnum++;
					}
				}
			}
		}
		[ptmpjjinfo.jjgsinfo removeAllObjects];
		[ptmpjjinfo.jjzhinfo removeAllObjects];
		[ptmpjjinfo.jjdminfo removeAllObjects];
		[archiver release];
	}
	
	[cachedata release];
	[pool drain];
	return bret;	
	
}

-(void)SaveLcxx:(JjInfo *)pLcinfos//保存理财信息
{
	if(pLcinfos==nil)
		return;
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	pLcinfos.savedate=[NSDate date];
	
	NSMutableData *cachedata=[NSMutableData	alloc];
	NSKeyedArchiver *archiver=[[NSKeyedArchiver alloc] initForWritingWithMutableData:cachedata];
	[archiver encodeObject:pLcinfos forKey:@"ClientLcInfo"];
	[archiver finishEncoding];
	[cachedata writeToFile:lcxxcachefile atomically:YES];
	[archiver release];
	[cachedata release];
	pLcinfos.savedate=nil;
	[pool drain];
}

-(BOOL)loadLcxx:(JjInfo *)pLcinfos//读取理财信息
{
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	BOOL bret=NO;
	NSData *cachedata=[[NSData alloc]initWithContentsOfFile:lcxxcachefile];
	if(cachedata && [cachedata length])
	{
		NSKeyedUnarchiver *archiver=[[NSKeyedUnarchiver alloc] initForReadingWithData:cachedata];
		JjInfo *ptmplcinfo=[archiver decodeObjectForKey:@"ClientLcInfo"];
		[archiver finishDecoding];
		
		NSDateFormatter* tempMatter = [[NSDateFormatter alloc]init];
		[tempMatter setDateFormat:@"yyyyMMdd"];
		NSString* strDate1 = [tempMatter stringFromDate:ptmplcinfo.savedate];
		NSString* strDate2 = [tempMatter stringFromDate:[NSDate date]];
		[tempMatter release];
		if([strDate1 isEqualToString:strDate2])
		{
			bret=YES;
			[pLcinfos releasejjinfos];
			int count=[ptmplcinfo.jjgsinfo count];
			if(count)
			{
				pLcinfos.jjgsinfo=[[NSMutableArray alloc] initWithCapacity:count+1];
				[pLcinfos.jjgsinfo release];
				for(JjgsInfo *pjjgs in ptmplcinfo.jjgsinfo)
				{
					if(pjjgs)
						[pLcinfos.jjgsinfo addObject:[pjjgs deepcopy]];
				}
			}
			count=[ptmplcinfo.jjzhinfo count];
			if(count)
			{
				pLcinfos.jjzhinfo=[[NSMutableArray alloc] initWithCapacity:count+1];
				[pLcinfos.jjzhinfo release];
				pLcinfos.jjzhdict=[[NSMutableDictionary alloc] initWithCapacity:count+1];
				[pLcinfos.jjzhdict release];
				JjZhInfo *pnewjjzh=nil;
				for(JjZhInfo *pjjzh in ptmplcinfo.jjzhinfo)
				{
					if(pjjzh)
					{
						pnewjjzh=[pjjzh deepcopy];
						[pLcinfos.jjzhinfo addObject:pnewjjzh];
						[pLcinfos.jjzhdict setObject:pnewjjzh forKey:pnewjjzh.jjgsdm];
					}
				}
			}
			count=[ptmplcinfo.jjdminfo count];
			if(count)
			{
				pLcinfos.jjdminfo=[[NSMutableArray alloc] initWithCapacity:count+1];
				[pLcinfos.jjdminfo release];
				pLcinfos.jjsgdminfo=[[NSMutableArray alloc] initWithCapacity:count+1];
				[pLcinfos.jjsgdminfo release];
				pLcinfos.jjrgdminfo=[[NSMutableArray alloc] initWithCapacity:count+1];
				[pLcinfos.jjrgdminfo release];
				pLcinfos.jjdmdict=[[NSMutableDictionary alloc] initWithCapacity:count+1];
				[pLcinfos.jjdmdict release];
				JjdmInfo *pnewjjdm=nil;
				for(JjdmInfo *pjjdm in ptmplcinfo.jjdminfo)
				{
					if(pjjdm)
					{
						pnewjjdm=[pjjdm deepcopy];
						[pLcinfos.jjdminfo addObject:pnewjjdm];
						[pLcinfos.jjdmdict setObject:pnewjjdm forKey:pnewjjdm.jjdm];
						if(pnewjjdm.njjjyzt==0)
						{
							pLcinfos.nksgjjnum++;
							[pLcinfos.jjsgdminfo addObject:pnewjjdm];
						}
						else if(pnewjjdm.njjjyzt==1)
						{
							pLcinfos.nkrgjjnum++;
							[pLcinfos.jjrgdminfo addObject:pnewjjdm];
						}
						pLcinfos.njjnum++;
					}
				}
			}
		}
		[ptmplcinfo.jjgsinfo removeAllObjects];
		[ptmplcinfo.jjzhinfo removeAllObjects];
		[ptmplcinfo.jjdminfo removeAllObjects];
		[archiver release];
	}
	
	[cachedata release];
	[pool drain];
	return bret;	
	
}

-(void)SaveLoginInfo:(LoginInfo *)plogininfo//保存登录信息
{
	if(plogininfo==nil)
		return;
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	NSMutableData *cachedata=[NSMutableData	alloc];
	NSKeyedArchiver *archiver=[[NSKeyedArchiver alloc] initForWritingWithMutableData:cachedata];
	[archiver encodeObject:plogininfo forKey:@"ClientLoginInfo"];
	[archiver finishEncoding];
	[cachedata writeToFile:logincachefile atomically:YES];
	[archiver release];
	[cachedata release];
	[pool drain];
}

-(LoginInfo *)loadLoginInfo//读取登录信息
{
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	LoginInfo *plogininfo=nil;
	NSData *cachedata=[[NSData alloc]initWithContentsOfFile:logincachefile];
	if(cachedata)
	{
		NSKeyedUnarchiver *archiver=[[NSKeyedUnarchiver alloc] initForReadingWithData:cachedata];
		LoginInfo *ptmplogininfo=[archiver decodeObjectForKey:@"ClientLoginInfo"];
		[archiver finishDecoding];
		
		plogininfo=[ptmplogininfo deepcopy];

		[archiver release];
	}
	[cachedata release];
	[pool drain];
	return plogininfo;
}

-(void)SaveScInfo:(ScInfo *)pScInfo//保存市场信息
{
	if(pScInfo==nil)
		return;
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	pScInfo.savedate=[NSDate date];
	NSMutableData *cachedata=[NSMutableData	alloc];
	NSKeyedArchiver *archiver=[[NSKeyedArchiver alloc] initForWritingWithMutableData:cachedata];
	[archiver encodeObject:pScInfo forKey:@"ClientScInfo"];
	[archiver finishEncoding];
	[cachedata writeToFile:scinfocachefile atomically:YES];
	[archiver release];
	[cachedata release];
	pScInfo.savedate=nil;
	[pool drain];
}

-(BOOL)loadScInfo:(ScInfo *)pScinfos//读取市场信息
{
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	BOOL bret=NO;
	NSData *cachedata=[[NSData alloc]initWithContentsOfFile:scinfocachefile];
	if(cachedata && [cachedata length])
	{
		NSKeyedUnarchiver *archiver=[[NSKeyedUnarchiver alloc] initForReadingWithData:cachedata];
		ScInfo *ptmpscinfo=[archiver decodeObjectForKey:@"ClientScInfo"];
		[archiver finishDecoding];
		
		NSDateFormatter* tempMatter = [[NSDateFormatter alloc]init];
		[tempMatter setDateFormat:@"yyyyMMdd"];
		NSString* strDate1 = [tempMatter stringFromDate:ptmpscinfo.savedate];
		NSString* strDate2 = [tempMatter stringFromDate:[NSDate date]];
		[tempMatter release];
		if([strDate1 isEqualToString:strDate2])
		{
			bret=YES;
			[pScinfos releasescinfos];
			int count=[ptmpscinfo.m_scinfos count];
			if(count)
			{
				pScinfos.m_scinfos=[[NSMutableArray alloc] initWithCapacity:count+1];
				[pScinfos.m_scinfos release];
				for(ScStrucInfo *pscinfos in ptmpscinfo.m_scinfos)
				{
					if(pscinfos)
						[pScinfos.m_scinfos addObject:[pscinfos deepcopy]];
				}
				pScinfos.m_bHasSCStruc=YES;
			}
		}
		[ptmpscinfo.m_scinfos removeAllObjects];
		[archiver release];
	}
	
	[cachedata release];
	[pool drain];
	return bret;	
	
}


-(BOOL)DeleteMultiloginInfo{
	NSError * tempError = nil;
	
	//NSLog(@"%@",multilogincachefile);
	if (multilogincachefile == nil) {
		return NO;
	}
	
	NSFileManager * tempFileManager = [[[NSFileManager alloc]init] autorelease];
	
	if (![tempFileManager fileExistsAtPath:multilogincachefile]) {
		return YES;
	}
	
	if (![tempFileManager isDeletableFileAtPath:multilogincachefile]) {
		return NO;
	}
	
	return [tempFileManager  removeItemAtPath:multilogincachefile error:&tempError];
}

-(BOOL)DeleteLoginInfo{
	NSError * tempError = nil;
	
	//NSLog(@"%@",logincachefile);
	if (logincachefile == nil) {
		return NO;
	}
	
	NSFileManager * tempFileManager = [[[NSFileManager alloc]init] autorelease];
	
	if (![tempFileManager fileExistsAtPath:logincachefile]) {
		return YES;
	}
	
	if (![tempFileManager isDeletableFileAtPath:logincachefile]) {
		return NO;
	}
	
	return [tempFileManager  removeItemAtPath:logincachefile error:&tempError];
}


-(void)SaveMultiloginInfo:(MultizhLogininfo *)pMultizhinfos//保存多账户登录信息
{
	if(pMultizhinfos==nil)
		return;
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	NSMutableData *cachedata=[NSMutableData	alloc];
	NSKeyedArchiver *archiver=[[NSKeyedArchiver alloc] initForWritingWithMutableData:cachedata];
	[archiver encodeObject:pMultizhinfos forKey:@"ClientMultizhLogininfo"];
	[archiver finishEncoding];
	[cachedata writeToFile:multilogincachefile atomically:YES];
	[archiver release];
	[cachedata release];
	[pool release];
	
}

-(BOOL)loadMultiloginInfo:(MultizhLogininfo *)pMultizhinfos//读取多账户登录信息
{
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	BOOL bret=NO;
	NSData *cachedata=[[NSData alloc]initWithContentsOfFile:multilogincachefile];
	if(cachedata && [cachedata length])
	{
		NSKeyedUnarchiver *archiver=[[NSKeyedUnarchiver alloc] initForReadingWithData:cachedata];
		MultizhLogininfo *ptmpzhinfos=[archiver decodeObjectForKey:@"ClientMultizhLogininfo"];
		[archiver finishDecoding];
		bret=YES;
		if(pMultizhinfos.zhinfos)
			[pMultizhinfos releasezhinfos];
		int zhcount=[ptmpzhinfos.zhinfos count];
		if(zhcount)
		{
			pMultizhinfos.zhinfos=[[NSMutableArray alloc] initWithCapacity:zhcount+1];
			[pMultizhinfos.zhinfos release];
			for(LoginInfo *plogininfo in ptmpzhinfos.zhinfos)
			{
				if(plogininfo)
					[pMultizhinfos.zhinfos addObject:[plogininfo deepcopy]];
			}
		}
		[ptmpzhinfos.zhinfos removeAllObjects];
		[archiver release];
	}
	
	[cachedata release];
	[pool release];
	return bret;	
}

-(void)SaveLocalJySite:(TradeSiteInfo *)pSiteInfo//保存交易中心
{
	if(pSiteInfo==nil)
		return;
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	NSMutableData *cachedata=[NSMutableData	alloc];
	NSKeyedArchiver *archiver=[[NSKeyedArchiver alloc] initForWritingWithMutableData:cachedata];
	[archiver encodeObject:pSiteInfo forKey:@"ClientTradeSiteInfo"];
	[archiver finishEncoding];
	[cachedata writeToFile:localjysitecachefile atomically:YES];
	[archiver release];
	[cachedata release];
	[pool drain];
}

-(BOOL)loadLocalJySite:(TradeSiteInfo *)pSiteInfo//读取交易中心
{
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	BOOL bret=NO;
	NSData *cachedata=[[NSData alloc]initWithContentsOfFile:localjysitecachefile];
	if(cachedata && [cachedata length])
	{
		NSKeyedUnarchiver *archiver=[[NSKeyedUnarchiver alloc] initForReadingWithData:cachedata];
		TradeSiteInfo *ptmpSiteInfo=[archiver decodeObjectForKey:@"ClientTradeSiteInfo"];
		[archiver finishDecoding];
		
		bret=YES;
		pSiteInfo.bfindbest=ptmpSiteInfo.bfindbest;
		pSiteInfo.nlastindex=ptmpSiteInfo.nlastindex;
		if(pSiteInfo.tradesites)
			[pSiteInfo releaseSiteinfos];
		int sitecount=[ptmpSiteInfo.tradesites count];
		if(sitecount)
		{
			pSiteInfo.tradesites=[[NSMutableArray alloc] initWithCapacity:sitecount+1];
			[pSiteInfo.tradesites release];
			for(TradeSite *psite in ptmpSiteInfo.tradesites)
			{
				if(psite)
					[pSiteInfo.tradesites addObject:[psite deepcopy]];
			}
		}
		[ptmpSiteInfo.tradesites removeAllObjects];
		[archiver release];
	}
	
	[cachedata release];
	[pool drain];
	return bret;
}

-(void)SaveLocalHqSite:(TradeSiteInfo *)pSiteInfo//保存行情中心
{
	if(pSiteInfo==nil)
		return;
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	NSMutableData *cachedata=[NSMutableData	alloc];
	NSKeyedArchiver *archiver=[[NSKeyedArchiver alloc] initForWritingWithMutableData:cachedata];
	[archiver encodeObject:pSiteInfo forKey:@"ClientHqSiteInfo"];
	[archiver finishEncoding];
	[cachedata writeToFile:localhqsitecachefile atomically:YES];
	[archiver release];
	[cachedata release];
	[pool drain];
}

-(BOOL)loadLocalHqSite:(TradeSiteInfo *)pSiteInfo//读取行情中心
{
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	BOOL bret=NO;
	NSData *cachedata=[[NSData alloc]initWithContentsOfFile:localhqsitecachefile];
	if(cachedata && [cachedata length])
	{
		NSKeyedUnarchiver *archiver=[[NSKeyedUnarchiver alloc] initForReadingWithData:cachedata];
		TradeSiteInfo *ptmpSiteInfo=[archiver decodeObjectForKey:@"ClientHqSiteInfo"];
		[archiver finishDecoding];
		
		bret=YES;
		pSiteInfo.bfindbest=ptmpSiteInfo.bfindbest;
		pSiteInfo.nlastindex=ptmpSiteInfo.nlastindex;
		if(pSiteInfo.tradesites)
			[pSiteInfo releaseSiteinfos];
		int sitecount=[ptmpSiteInfo.tradesites count];
		if(sitecount)
		{
			pSiteInfo.tradesites=[[NSMutableArray alloc] initWithCapacity:sitecount+1];
			[pSiteInfo.tradesites release];
			for(TradeSite *psite in ptmpSiteInfo.tradesites)
			{
				if(psite)
					[pSiteInfo.tradesites addObject:[psite deepcopy]];
			}
		}
		[ptmpSiteInfo.tradesites removeAllObjects];
		[archiver release];
	}
	
	[cachedata release];
	[pool drain];
	return bret;
}

-(void)SaveHqParamInfo:(HqParamInfo *)pHqParamInfo//保存行情参数
{
	if(pHqParamInfo==nil)
		return;
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	NSMutableData *cachedata=[NSMutableData	alloc];
	NSKeyedArchiver *archiver=[[NSKeyedArchiver alloc] initForWritingWithMutableData:cachedata];
	[archiver encodeObject:pHqParamInfo forKey:@"ClientHqParamInfo"];
	[archiver finishEncoding];
	[cachedata writeToFile:localhqparamcachefile atomically:YES];
	[archiver release];
	[cachedata release];
	[pool release];
}

-(HqParamInfo *)loadHqParamInfo//读取行情参数
{
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	HqParamInfo *pHqParamInfo=nil;
	NSData *cachedata=[[NSData alloc]initWithContentsOfFile:localhqparamcachefile];
	if(cachedata && [cachedata length])
	{
		NSKeyedUnarchiver *archiver=[[NSKeyedUnarchiver alloc] initForReadingWithData:cachedata];
		HqParamInfo *ptmpHqParamInfo=[archiver decodeObjectForKey:@"ClientHqParamInfo"];
		[archiver finishDecoding];
		
		pHqParamInfo=[ptmpHqParamInfo deepcopy];
		
		[archiver release];
	}
	[cachedata release];
	[pool drain];
	return pHqParamInfo;
}

-(void)SaveDataLltjInfo:(DataLitj *)pDatainfo//保存流量信息
{
	if(pDatainfo==nil)
		return;
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	pDatainfo.savedate = [NSDate date];
	NSMutableData *cachedata=[NSMutableData	alloc];
	NSKeyedArchiver *archiver=[[NSKeyedArchiver alloc] initForWritingWithMutableData:cachedata];
	[archiver encodeObject:pDatainfo forKey:@"ClientDataLitj"];
	[archiver finishEncoding];
	[cachedata writeToFile:locallltjcachefile atomically:YES];
	[archiver release];
	[cachedata release];
	[pool drain];
}

-(DataLitj *)loadDataLltjInfo//读取流量信息
{
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	DataLitj *pDatainfo=nil;
	NSData *cachedata=[[NSData alloc]initWithContentsOfFile:locallltjcachefile];
	if(cachedata && [cachedata length])
	{
		NSKeyedUnarchiver *archiver=[[NSKeyedUnarchiver alloc] initForReadingWithData:cachedata];
		DataLitj *ptmpDatainfo=[archiver decodeObjectForKey:@"ClientDataLitj"];
		[archiver finishDecoding];
		
		pDatainfo=[ptmpDatainfo deepcopy];
		
		[archiver release];
	}
	[cachedata release];
	[pool drain];
	return pDatainfo;
}


-(void)SaveZxLinkInfo:(ZxLinkInfo *)pZxLinks//保存资讯链接信息
{
	if(pZxLinks==nil)
		return;
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	NSMutableData *cachedata=[NSMutableData	alloc];
	NSKeyedArchiver *archiver=[[NSKeyedArchiver alloc] initForWritingWithMutableData:cachedata];
	[archiver encodeObject:pZxLinks forKey:@"ClientZxLinkInfo"];
	[archiver finishEncoding];
	[cachedata writeToFile:localzxlinkcachefile atomically:YES];
	[archiver release];
	[cachedata release];
	[pool drain];
}

-(BOOL)loadZxLinkInfo:(ZxLinkInfo *)pZxLinks//读取资讯链接信息
{
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	BOOL bret=NO;
	NSData *cachedata=[[NSData alloc]initWithContentsOfFile:localzxlinkcachefile];
	if(cachedata && [cachedata length])
	{
		NSKeyedUnarchiver *archiver=[[NSKeyedUnarchiver alloc] initForReadingWithData:cachedata];
		ZxLinkInfo *ptmpZxLinks=[archiver decodeObjectForKey:@"ClientZxLinkInfo"];
		[archiver finishDecoding];
		
		bret=YES;
		[pZxLinks releaselinks];
		pZxLinks.mainlink=[ptmpZxLinks.mainlink deepcopy];
		[pZxLinks.mainlink release];
		int itemcount=[ptmpZxLinks.linkItems count];
		if(itemcount)
		{
			pZxLinks.linkItems=[[NSMutableArray alloc] initWithCapacity:itemcount+1];
			[pZxLinks.linkItems release];
			for(ZxLinks *plink in ptmpZxLinks.linkItems)
			{
				if(plink)
					[pZxLinks.linkItems addObject:[plink deepcopy]];
			}
		}
		
		[ptmpZxLinks.linkItems removeAllObjects];
		[archiver release];
	}
	
	[cachedata release];
	[pool drain];
	return bret;	
}

-(void)SaveJyParamInfo:(JyParamInfo *)pJyParamInfo//保存交易参数
{
	if(pJyParamInfo==nil)
		return;
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	NSMutableData *cachedata=[NSMutableData	alloc];
	NSKeyedArchiver *archiver=[[NSKeyedArchiver alloc] initForWritingWithMutableData:cachedata];
	[archiver encodeObject:pJyParamInfo forKey:@"ClientJyParamInfo"];
	[archiver finishEncoding];
	[cachedata writeToFile:localjyparamcachefile atomically:YES];
	[archiver release];
	[cachedata release];
	[pool release];
}

-(JyParamInfo *)loadJyParamInfo//读取交易参数
{
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	JyParamInfo *pJyParamInfo=nil;
	NSData *cachedata=[[NSData alloc]initWithContentsOfFile:localjyparamcachefile];
	if(cachedata && [cachedata length])
	{
		NSKeyedUnarchiver *archiver=[[NSKeyedUnarchiver alloc] initForReadingWithData:cachedata];
		JyParamInfo *ptmpJyParamInfo=[archiver decodeObjectForKey:@"ClientJyParamInfo"];
		[archiver finishDecoding];
		
		pJyParamInfo=[ptmpJyParamInfo deepcopy];
		
		[archiver release];
	}
	[cachedata release];
	[pool drain];
	return pJyParamInfo;
}
@end

@implementation Gsdm_Selgd

@synthesize type,gsdm;

-(id)init
{
	self=[super init];
	if(self)
	{
		gsdm=nil;
		type=-1;
	}
	return self;
}

-(void)dealloc
{
	RELEASEOBJ(gsdm)
	[super dealloc];
}
@end


@implementation Tradeccf

@synthesize lcgsdm,exceptlcgsdm,bweaktip,zyckgpdms,nszgzdw,nshgzdw,gsdm_selgds,m_bjjzndtex;

-(id)init
{
	self=[super init];
	if(self)
	{
		bweaktip=NO;
		lcgsdm=nil;
		exceptlcgsdm=nil;
		zyckgpdms=nil;
		nszgzdw=0;
        nshgzdw=0;
#ifdef IMAC_ZSZQ
	nshgzdw=1;
#endif
#ifdef IMAC_GDZQ
        nshgzdw=1;
#endif
#ifdef IMAC_PAZQ
        nshgzdw=1;
#endif
		gsdm_selgds=nil;
		m_bjjzndtex=YES;
        nLSWTJGTS = 31;
	}
	return self;
}

-(void)dealloc
{
	if(lcgsdm)
	{
		for(NSString *tmpstr in lcgsdm)
			RELEASEOBJ(tmpstr)
		[lcgsdm removeAllObjects];
	}
	RELEASEOBJ(lcgsdm)
	if(exceptlcgsdm)
	{
		for(NSString *tmpstr in exceptlcgsdm)
			RELEASEOBJ(tmpstr)
		[exceptlcgsdm removeAllObjects];
	}
	RELEASEOBJ(exceptlcgsdm)
	if(zyckgpdms)
	{
		for(NSString *tmpstr in zyckgpdms)
			RELEASEOBJ(tmpstr)
		[zyckgpdms removeAllObjects];
	}
	RELEASEOBJ(zyckgpdms)
	if(gsdm_selgds)
	{
		for(Gsdm_Selgd *psels in gsdm_selgds)
			RELEASEOBJ(psels)
		[gsdm_selgds removeAllObjects];
	}
	RELEASEOBJ(gsdm_selgds)
	[super dealloc];
}


-(void)loadTradeccf//登录成功后加载
{
	//先写死设置，以后可以读取配置
	self.lcgsdm=[[NSMutableArray alloc] initWithCapacity:2];
	[self.lcgsdm release];
	[self.lcgsdm addObject:@"88"];
	[self.lcgsdm addObject:@"98"];
	self.exceptlcgsdm=[[NSMutableArray alloc] initWithCapacity:1];
	[self.exceptlcgsdm release];
	[self.exceptlcgsdm addObject:@"88"];
	
	//公司代码选择股东
	self.gsdm_selgds=[[NSMutableArray alloc] initWithCapacity:2];
	[self.gsdm_selgds release];
	Gsdm_Selgd *psel=[Gsdm_Selgd new];
	psel.gsdm=[[NSString alloc]  initWithFormat:@"%@",@"98"];
	[psel.gsdm release];
	psel.type=0;
	
	[self.gsdm_selgds addObject:psel];
	
	psel=[Gsdm_Selgd new];
	psel.gsdm=[[NSString alloc]  initWithFormat:@"%@",@"99"];
	[psel.gsdm release];
	psel.type=1;
	
	[self.gsdm_selgds addObject:psel];
	////
	bweaktip=NO;
	m_bjjzndtex=YES;
}

-(BOOL)Islcgsdm:(NSString *)gsdm
{
	for(NSString *tmpstr in lcgsdm)
	{
		if([tmpstr isEqualToString:gsdm])
			return YES;
	}
	return NO;
}

-(BOOL)IsExceptLcgsdm:(NSString *)gsdm
{
	for(NSString *tmpstr in exceptlcgsdm)
	{
		if([tmpstr isEqualToString:gsdm])
			return YES;
	}
	return NO;
}

-(BOOL)IsZyckgpdm:(NSString *)gpdm
{
	NSArray *zydm=[NSArray arrayWithObjects:@"09",@"104",@"105",@"106",@"107",nil];
	
	for(NSString *tmpstr in zydm)
	{
		if([tmpstr isEqualToString:[gpdm substringWithRange:NSMakeRange(0, [tmpstr length])]])
			return YES;
	}
	if(zyckgpdms==nil)
		return NO;
	for(NSString *tmpstr in zyckgpdms)
	{
		if([tmpstr isEqualToString:[gpdm substringWithRange:NSMakeRange(0, [tmpstr length])]])
			return YES;
	}
	return NO;
}

-(int)GetGsType:(NSString *)jjgsdm
{
	int type=-1;
	for(Gsdm_Selgd *psels in gsdm_selgds)
	{
		if([psels.gsdm isEqualToString:jjgsdm])
		{
			type=psels.type;
			break;
		}
	}
	return type;
}
@end

@implementation ZjgfInfoClass

@synthesize stzjgf;

-(id)init
{
	self=[super init];
	if(self)
	{
		memset((char *)&stzjgf,0,sizeof(ST_ZJGFINFO));
	}
	return self;
}

-(void)dealloc
{
	[super dealloc];
}

@end



@implementation ClientInfo

@synthesize gdinfos,m_nQsbs,scinfos,jjinfos,lcinfos,caches,m_zjzh,yhxxs,stzjgf,stzjgfjj,stzjgflc,strawzjgf,strawzjgfjj,strawzjgflc,qsconfigs,m_bonlyinithqinfo,hqParams,dataLltjs,zxLinks,m_blocking,m_DBPHZblocking,m_nlastjyopertime;
@synthesize m_TdxRealBranchID,m_nKhqx,m_bKfsjjflag,m_blcflag,m_bggflag,m_bqhflag,m_bGetMaxBuy,m_bxyjyflag,m_nZhlb,tradeccf,localjysites,localhqsites;
@synthesize m_nRealZjzhNum,m_realzjzh,m_strKhqxmc,m_strTdxWtfs,m_username,m_bgtbs,m_jjzjzh,m_nrealIndex,m_bgpflag,logininfos,multilogininfos,jyParams,dldzxy;
@synthesize styleParams,versionParams,gridCellCache,httpProxyInfo;

-(id) init
{
	self = [super init];
	if(self)
	{
		gdinfos=[GdInfo new];
		scinfos=[ScInfo new];
		yhxxs=[YhxxInfo new];
		jjinfos=[JjInfo new];
		lcinfos=[JjInfo new];
		tradeccf=[Tradeccf new]; 
		versionParams = [VersionParam new];
		logininfos=nil;
		multilogininfos=[MultizhLogininfo new];
		gridCellCache = [gridCellInfoForCache new];
		m_nQsbs=0;
		m_zjzh=nil;
		m_jjzjzh=nil;
		caches=nil;
		m_TdxRealBranchID=0;
		m_nKhqx=0;
		m_bKfsjjflag=YES;
		m_bggflag=YES;
		m_bgpflag=YES;
		m_bqhflag=YES;
		m_blcflag=YES;
		m_bGetMaxBuy=NO;
		m_bxyjyflag=NO;
		m_bgtbs=NO;
		m_nZhlb=0;
		m_nRealZjzhNum=0;
		m_realzjzh=nil;
		m_strKhqxmc=nil;
		m_strTdxWtfs=nil;
		m_username=nil;
		qsconfigs=nil;
		styleParams = nil;
		httpProxyInfo=nil;
		localjysites=[TradeSiteInfo new];
		localhqsites=[TradeSiteInfo new];
		hqParams=nil;
		jyParams=nil;
		m_bonlyinithqinfo=NO;
		dataLltjs=nil;
		zxLinks=[ZxLinkInfo new];
		m_blocking=NO;
        m_DBPHZblocking = YES;//第一次应该锁住
		m_nlastjyopertime=time(NULL);
	}
	
	return self;
}

-(void) dealloc
{
	if(m_realzjzh)
		[m_realzjzh removeAllObjects];
	RELEASEOBJ(gridCellCache)
	RELEASEOBJ(m_realzjzh)
	RELEASEOBJ(m_strKhqxmc)
	RELEASEOBJ(m_strTdxWtfs)
	RELEASEOBJ(m_username)
	RELEASEOBJ(tradeccf)
	RELEASEOBJ(scinfos)
	RELEASEOBJ(gdinfos)
	RELEASEOBJ(yhxxs)
	RELEASEOBJ(jjinfos)
	RELEASEOBJ(lcinfos)
	RELEASEOBJ(caches)
	RELEASEOBJ(m_zjzh)
	RELEASEOBJ(m_jjzjzh)
	RELEASEOBJ(logininfos)
	RELEASEOBJ(multilogininfos)
	RELEASEOBJ(qsconfigs)
	RELEASEOBJ(localjysites)
	RELEASEOBJ(localhqsites)
	RELEASEOBJ(hqParams)
	RELEASEOBJ(jyParams)
	RELEASEOBJ(dataLltjs)
	RELEASEOBJ(zxLinks)
	RELEASEOBJ(httpProxyInfo)
	[super dealloc];
}

#pragma mark imac attributes相关
-(NSMutableDictionary *)getAttributes:(NSString *)_fontName fontSize:(CGFloat)_fontSize theColor:(NSColor *)_theColor theAliment:(int)_theAliment{
	NSMutableDictionary * attributes = [[NSMutableDictionary alloc] init] ;
	
	NSMutableParagraphStyle * tempStyle = [[NSMutableParagraphStyle alloc]init] ;
	[tempStyle setLineBreakMode:NSLineBreakByTruncatingTail];
	[tempStyle setAlignment:_theAliment];
	
	[attributes setObject:[NSFont systemFontOfSize:_fontSize] forKey:NSFontAttributeName];
	[attributes setObject:_theColor forKey:NSForegroundColorAttributeName];
	[attributes setObject:tempStyle forKey:NSParagraphStyleAttributeName];
	
	
	[tempStyle release];
	return [attributes autorelease];
}


//根据股票代码自动切换市场   原则：当前股东所在市场优先
//返回 0:不需要切换 1:切换成功 -1:没有对应市场主帐号
-(GdmxInfo *) AutoChangeGddm:(GdmxInfo *)gdinfo withzqdm:(const char*)code withxyflag:(BOOL) bxyflag withsetcode:(int)nsetcode
{
	short tmp_gpsc = [self GetScNoZS_FromCode:code withsetcode:nsetcode];
	if(tmp_gpsc == -1)
		return gdinfo;
	if (gdinfo && tmp_gpsc==gdinfo.wttype)
	{
		if(bxyflag==gdinfo.bxyjygd)
			return gdinfo;
	}
	if(m_nQsbs==GXZQ_DLL)
		bxyflag=NO;
	switch(tmp_gpsc)
	{
		case SZAG:
		case SZGZ:
		{
			if(bxyflag)
			{
				if (gdinfos.m_SZA_MainxyFlag == 1)
					return gdinfos.m_SZA_MainxyGd;
			}
			else
			{
				if (gdinfos.m_SZA_MainFlag == 1)
					return gdinfos.m_SZA_MainGd;
			}
		}
			break;
		case SZBG:
		{
			if(bxyflag)
			{
				if (gdinfos.m_SZB_MainxyFlag == 1)
					return gdinfos.m_SZB_MainxyGd;
			}
			else
			{
				if (gdinfos.m_SZB_MainFlag == 1)
					return gdinfos.m_SZB_MainGd;
			}
		}
			break;
		case SHAG:
		case SHGZ:
		{
			if(bxyflag)
			{
				if (gdinfos.m_SHA_MainxyFlag == 1)
					return gdinfos.m_SHA_MainxyGd;
			}
			else
			{
				if (gdinfos.m_SHA_MainFlag == 1)
					return gdinfos.m_SHA_MainGd;
			}
		}
			break;
		case SHBG:
		{
			if(bxyflag)
			{
				if (gdinfos.m_SHB_MainxyFlag == 1)
					return gdinfos.m_SHB_MainxyGd;
			}
			else
			{
				if (gdinfos.m_SHB_MainFlag == 1)
					return gdinfos.m_SHB_MainGd;
			}
		}			
			break;
		case SBAG:
		{
			if(bxyflag)
			{
				if (gdinfos.m_SBA_MainxyFlag == 1)
					return gdinfos.m_SBA_MainxyGd;
			}
			else
			{
				if (gdinfos.m_SBA_MainFlag == 1)
					return gdinfos.m_SBA_MainGd;
			}
		}
			break;
		case SBGB:
		{
			if(bxyflag)
			{
				if (gdinfos.m_SBG_MainxyFlag == 1)
					return gdinfos.m_SBG_MainxyGd;
			}
			else
			{
				if (gdinfos.m_SBG_MainFlag == 1)
					return gdinfos.m_SBG_MainGd;
			}
		}
			break;
		case SBBG:
		{
			if(bxyflag)
			{
				if (gdinfos.m_SBB_MainxyFlag == 1)
					return gdinfos.m_SBB_MainxyGd;
			}
			else
			{
				if (gdinfos.m_SBB_MainFlag == 1)
					return gdinfos.m_SBB_MainGd;
			}
		}
			break;
		default:
			break;
	}
	return nil;
}

-(int) GetNowSC:(const char *)code setcode:(int)nsetcode
{
	if(scinfos.m_bHasSCStruc==NO)
		return -1;
	int nLastZqdmLen = -1,ndestlen=0;
	int nScId = -1,i=0;
	NSRange range;
	NSString *tmpstr=[NSString stringWithUTF8String:code];
	for(ScStrucInfo *pscStruc in scinfos.m_scinfos)
	{
		if(pscStruc.setcode==nsetcode || nsetcode==-1)
		{
			range=[tmpstr rangeOfString:[NSString stringWithString:pscStruc.zqdm]];
			if( range.location==0)
			{
				ndestlen= [pscStruc.zqdm length];
				if(ndestlen>nLastZqdmLen )
				{
					nScId = i;
					nLastZqdmLen =ndestlen;
				}
			}
		}	
		i++;
	}
	return nScId;
}

//根据股票代码判断是深市还是沪市
-(int) GetDomainFromCode:(const char*)code withsetcode:(int)nsetcode	//在换版前，如果中间件没有升级，可以买卖一些重码股票可能有问题
{
	if(scinfos.m_bHasSCStruc)
	{
		ScStrucInfo *pscStruc=[self GetScStructInfo:code setcode:nsetcode];
		if(pscStruc)
		{
			return pscStruc.setcode;
		}
	}
	if(strcmp(code,"000696")==0 || strcmp(code,"000896")==0 || strcmp(code,"009704")==0 || strcmp(code,"009905")==0 || strcmp(code,"009908")==0 )	//指定一些股票
		return CODE_SH;
	if(strcmp(code,"100009")==0 || strcmp(code,"100087")==0 || strcmp(code,"100220")==0 || strcmp(code,"100016")==0 || strcmp(code,"100177")==0 || strcmp(code,"100716")==0)	//指定一些股票
		return CODE_SH;
	if(strcmp(code,"100115")==0  || strcmp(code,"126301")==0 || strcmp(code,"100203")==0 || strcmp(code,"100210")==0 || strcmp(code,"100213")==0 || strcmp(code,"100214")==0 || strcmp(code,"100215")==0 || strcmp(code,"100301")==0 || strcmp(code,"100303")==0)	//其它100开头算深圳国债
		return CODE_SZ;
	if(strcmp(code,"111016")==0 || strcmp(code,"111015")==0 || strcmp(code,"111017")==0 || strcmp(code,"111018")==0 || strcmp(code,"111019")==0)
		return CODE_SZ;
	if(strncmp(code,"100",3)==0)
		return CODE_SH;
	
	if(strncmp(code,"009",3)==0 || strncmp(code,"010",3)==0 || strncmp(code,"120",3)==0)
		return CODE_SH;	
	if(strncmp(code,"01",2)==0 || strncmp(code,"02",2)==0)//如果是01或02开始，当成上海股票
		return CODE_SH;
	if(strncmp(code,"500",3)==0 || strncmp(code,"600",3)==0 || strncmp(code,"900",3)==0)//沪A、沪B
		return CODE_SH;
	if(strncmp(code,"201",3)==0 || strncmp(code,"129",3)==0 || strncmp(code,"181",3)==0)
		return CODE_SH;
	if(strncmp(code,"737",3)==0 || strncmp(code,"747",3)==0 || strncmp(code,"799",3)==0 || strncmp(code,"704",3)==0 || strncmp(code,"733",3)==0)
		return CODE_SH;
	if(strncmp(code,"816",3)==0 || strncmp(code,"830",3)==0 || strncmp(code,"11",2)==0 || strncmp(code,"19",2)==0)
		return CODE_SH;
	
	if(strncmp(code,"184",3)==0 || strncmp(code,"188",3)==0)//国债、基金
		return CODE_SZ;
	if(strncmp(code,"200",3)==0)//深B
		return CODE_SZ;
	if(strncmp(code,"00",2)==0)//A股					//如果00开始，当成新版的深A股，因为上海指数不能买卖
		return CODE_SZ;
	if(strncmp(code,"101",3)==0 || strncmp(code,"125",3)==0 || strncmp(code,"080",3)==0 || strncmp(code,"131",3)==0 )
		return CODE_SZ;
	if(strncmp(code,"160",3)==0 || strncmp(code,"161",3)==0)
		return CODE_SZ;
	if(strncmp(code,"42",2)==0)
		return CODE_SZ;
	if(code[0] == '3' || code[0] == '4')	//code[0]='4'表示是三板，归入深圳,code[0]='2'表示是深圳B股
		return CODE_SZ;
	
	if(code[0] == '0' || code[0] == '1')
		return CODE_SZSH;
	return CODE_SH;
}

-(short) GetScNoZS_FromCode:(const char*)code withsetcode:(int)nsetcode
{
	if(scinfos.m_bHasSCStruc)
	{
		ScStrucInfo *pscStruc=[self GetScStructInfo:code setcode:nsetcode];
		if(pscStruc)
			return pscStruc.nzhlb;
	}
	int codetype = [self GetDomainFromCode:code withsetcode:nsetcode];
	switch(codetype)
	{
		case CODE_SZ:
			if(code[0] == '4') 
			{
				if(code[1] == '2')	return SBBG;//三板B股
				else
				{
					if(code[1]=='1') return SBGB;//三板港币
					else				return SBAG;//三板A股   //43 开头
				}
			}
			if(code[0] == '2') return SZBG;//港币
			return SZAG;
		case CODE_SH:
			if(code[0] == '9')		return SHBG;//美元
			return SHAG;
	}
	return -1;
}


-(void)initcache
{
	[caches initWithtoken:[NSString stringWithFormat:@"%i%@",m_nQsbs,m_zjzh]];
}


-(int)GetBzFromZhlb:(int)nzhlb
{
	switch (nzhlb) {
		case SZAG:
		case SHAG:
		case SBAG:
			return 0;
		case SHBG:
		case SBBG:
			return 1;
		case SZBG:
		case SBGB:
			return 2;
	}
	return 0;
}

-(NSString *)GetZjzh
{
	if([m_realzjzh count]>0)
    {
        if(m_nrealIndex>=[m_realzjzh count])
            m_nrealIndex=0;
		return [m_realzjzh objectAtIndex:m_nrealIndex];
    }
	if (m_zjzh == nil) {
		return @"";
	}
    
	return m_zjzh;
}

-(NSString *)GetGdCacheInfo:(NSMutableArray *)showData withparse:(id)pParses StartIndex:(int)nstartindex ReqLines:(int)npagenum withrownum:(int *)ntotalline withsucflag:(BOOL *)bsucflag
{
	(*ntotalline)=gdinfos.m_gdcount;
	(*bsucflag)=YES;
	
	int count=0;
	NSMutableArray * tempArray=nil;
	GdmxInfo *pgdmx=nil;
	ParseRecv *pParse2=(ParseRecv *)pParses;
	CGSize strsize;
	NSString *tmpstr=nil;
	RecvField *pfield=nil;
	for(int i=nstartindex-1,j=0;i<gdinfos.m_gdcount && count<npagenum;i++)
	{
		pgdmx=(GdmxInfo *)[gdinfos.gddms objectAtIndex:i];
		if(!pgdmx)
			continue;
		tempArray = [[NSMutableArray alloc] init];
		
		[tempArray addObject:[NSString stringWithFormat:@"%@%@",pgdmx.gddm,[gdinfos GetMainGdStr:pgdmx.gddm]]];
		[tempArray addObject:[NSString stringWithFormat:@"%@",pgdmx.gdmc]];
		[tempArray addObject:[pgdmx GetWtTypeStr]];
		if([pgdmx.zjzh length] && [pgdmx.zjzh isEqualToString:@"0"]==NO)
			[tempArray addObject:[NSString stringWithFormat:@"%@",pgdmx.zjzh]];
		else 
			[tempArray addObject:[self GetZjzh]];
		
		if(pParse2)
		{
			int colcount=MIN([pParse2.sFieldColstr count],[tempArray count]);
			for(j=0;j<colcount;j++)
			{
				pfield=[pParse2.sFieldColstr objectAtIndex:j];
				if(pfield)
				{
					tmpstr=[tempArray objectAtIndex:j];
					NSDictionary * tempAttributes= [self getAttributes:MAC_CHINESEFONT fontSize:20.0f theColor:[NSColor whiteColor] theAliment:NSCenterTextAlignment];
					NSRect temprect = [tmpstr boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
					strsize = CGSizeMake(temprect.size.width, temprect.size.height);
					if(strsize.width>pfield.maxwidth)
						pfield.maxwidth=strsize.width;
				}
			}
		}
		[tempArray addObject:COLOR_GRID_NORMALCOLOR];
		
		[showData addObject:tempArray];
		[tempArray release];
		count++;
	}
	
	return @"";
}

-(NSColor *)GetUIColorFromJjbs:(int )jjbs
{
	if(jjbs==1)
		return [NSColor redColor];
	else 
		return COLOR_GRID_COMMONCOLOR;
}

-(NSString *)GetJjgsCacheInfo:(NSMutableArray *)showData withparse:(id)pParses StartIndex:(int)nstartindex ReqLines:(int)npagenum withrownum:(int *)ntotalline withsucflag:(BOOL *)bsucflag
{
	(*ntotalline)=[jjinfos.jjgsinfo count];
	(*bsucflag)=YES;
	
	int count=0;
	NSMutableArray * tempArray=nil;
	JjgsInfo *pjjgs=nil;
	ParseRecv *pParse2=(ParseRecv *)pParses;
	CGSize strsize;
	NSString *tmpstr=nil;
	RecvField *pfield=nil;
	for(int i=nstartindex-1,j=0;i<(*ntotalline) && count<npagenum;i++)
	{
		pjjgs=(JjgsInfo *)[jjinfos.jjgsinfo objectAtIndex:i];
		if(!pjjgs)
			continue;
		tempArray = [[NSMutableArray alloc] init];
		
		[tempArray addObject:[NSString stringWithFormat:@"%@",pjjgs.jjgsdm]];
		[tempArray addObject:[NSString stringWithFormat:@"%@",pjjgs.jjgsmc]];
		if(pParse2)
		{
			int colcount=MIN([pParse2.sFieldColstr count],[tempArray count]);
			for(j=0;j<colcount;j++)
			{
				pfield=[pParse2.sFieldColstr objectAtIndex:j];
				if(pfield)
				{
					tmpstr=[tempArray objectAtIndex:j];
					NSDictionary * tempAttributes= [self getAttributes:MAC_CHINESEFONT fontSize:20.0f theColor:[NSColor whiteColor] theAliment:NSCenterTextAlignment];
					NSRect temprect = [tmpstr boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
					strsize = CGSizeMake(temprect.size.width, temprect.size.height);
					
					if(strsize.width>pfield.maxwidth)
						pfield.maxwidth=strsize.width;
				}
			}
		}
		[tempArray addObject:[self GetUIColorFromJjbs:pjjgs.njjbs]];
		
		[showData addObject:tempArray];
		[tempArray release];
		count++;
	}
	
	return @"";
}

-(NSString *)GetJjzhCacheInfo:(NSMutableArray *)showData withparse:(id)pParses StartIndex:(int)nstartindex ReqLines:(int)npagenum withrownum:(int *)ntotalline withsucflag:(BOOL *)bsucflag
{
	(*ntotalline)=[jjinfos.jjzhinfo count];
	(*bsucflag)=YES;
	
	int count=0;
	NSMutableArray * tempArray=nil;
	JjZhInfo *pjjzh=nil;
	ParseRecv *pParse2=(ParseRecv *)pParses;
	CGSize strsize;
	NSString *tmpstr=nil;
	RecvField *pfield=nil;
	for(int i=nstartindex-1,j=0;i<(*ntotalline) && count<npagenum;i++)
	{
		pjjzh=(JjZhInfo *)[jjinfos.jjzhinfo objectAtIndex:i];
		if(!pjjzh)
			continue;
		tempArray = [[NSMutableArray alloc] init];
		
		[tempArray addObject:[NSString stringWithFormat:@"%@",pjjzh.jjgsdm]];
		[tempArray addObject:[NSString stringWithFormat:@"%@",pjjzh.jjgsmc]];
		[tempArray addObject:[NSString stringWithFormat:@"%@",pjjzh.jjzh]];
		[tempArray addObject:[NSString stringWithFormat:@"%@",pjjzh.khmc]];
		[tempArray addObject:[NSString stringWithFormat:@"%@",pjjzh.zjhm]];
		if(pParse2)
		{
			int colcount=MIN([pParse2.sFieldColstr count],[tempArray count]);
			for(j=0;j<colcount;j++)
			{
				pfield=[pParse2.sFieldColstr objectAtIndex:j];
				if(pfield)
				{
					tmpstr=[tempArray objectAtIndex:j];
					NSDictionary * tempAttributes= [self getAttributes:MAC_CHINESEFONT fontSize:20.0f theColor:[NSColor whiteColor] theAliment:NSCenterTextAlignment];
					NSRect temprect = [tmpstr boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
					strsize = CGSizeMake(temprect.size.width, temprect.size.height);
					
					if(strsize.width>pfield.maxwidth)
						pfield.maxwidth=strsize.width;
				}
			}
		}
		[tempArray addObject:COLOR_GRID_COMMONCOLOR];
		
		[showData addObject:tempArray];
		[tempArray release];
		count++;
	}
	
	return @"";
}

-(NSString *)GetJjdmCacheInfo:(NSMutableArray *)showData withparse:(id)pParses StartIndex:(int)nstartindex ReqLines:(int)npagenum withrownum:(int *)ntotalline withsucflag:(BOOL *)bsucflag
{
	(*ntotalline)=[jjinfos.jjdminfo count];
	(*bsucflag)=YES;
	
	int count=0;
	NSMutableArray * tempArray=nil;
	JjdmInfo *pjjdm=nil;
	ParseRecv *pParse2=(ParseRecv *)pParses;
	CGSize strsize;
	NSString *tmpstr=nil;
	RecvField *pfield=nil;
	for(int i=nstartindex-1,j=0;i<(*ntotalline) && count<npagenum;i++)
	{
		pjjdm=(JjdmInfo *)[jjinfos.jjdminfo objectAtIndex:i];
		if(!pjjdm)
			continue;
		tempArray = [[NSMutableArray alloc] init];
			
		[tempArray addObject:[NSString stringWithFormat:@"%@",pjjdm.jjdm]];
		[tempArray addObject:[NSString stringWithFormat:@"%@",pjjdm.jjmc]];
		[tempArray addObject:[NSString stringWithFormat:@"%@",pjjdm.jjgsdm]];
		[tempArray addObject:[NSString stringWithFormat:@"%.3f",pjjdm.jjjz]];
		[tempArray addObject:[NSString stringWithFormat:@"%@",pjjdm.jjjyzt]];
		[tempArray addObject:[NSString stringWithFormat:@"%.3f",pjjdm.grzdsgje]];
		[tempArray addObject:[NSString stringWithFormat:@"%.3f",pjjdm.frzdsgje]];
		[tempArray addObject:[NSString stringWithFormat:@"%.3f",pjjdm.zdcyfe]];
		[tempArray addObject:[NSString stringWithFormat:@"%.2f",pjjdm.zgshfe]];

		if(pParse2)
		{
			int colcount=MIN([pParse2.sFieldColstr count],[tempArray count]);
			for(j=0;j<colcount;j++)
			{
				pfield=[pParse2.sFieldColstr objectAtIndex:j];
				if(pfield)
				{
					tmpstr=[tempArray objectAtIndex:j];
					NSDictionary * tempAttributes= [self getAttributes:MAC_CHINESEFONT fontSize:20.0f theColor:[NSColor whiteColor] theAliment:NSCenterTextAlignment];
					NSRect temprect = [tmpstr boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
					strsize = CGSizeMake(temprect.size.width, temprect.size.height);
					
					if(strsize.width>pfield.maxwidth)
						pfield.maxwidth=strsize.width;
				}
			}
		}
		[tempArray addObject:[self GetUIColorFromJjbs:pjjdm.njjbs]];
		
		[showData addObject:tempArray];
		[tempArray release];
		count++;
	}
	
	return @"";
}

-(NSString *)GetLcgsCacheInfo:(NSMutableArray *)showData withparse:(id)pParses StartIndex:(int)nstartindex ReqLines:(int)npagenum withrownum:(int *)ntotalline withsucflag:(BOOL *)bsucflag
{
	(*ntotalline)=[lcinfos.jjgsinfo count];
	(*bsucflag)=YES;
	
	int count=0;
	NSMutableArray * tempArray=nil;
	JjgsInfo *pjjgs=nil;
	ParseRecv *pParse2=(ParseRecv *)pParses;
	CGSize strsize;
	NSString *tmpstr=nil;
	RecvField *pfield=nil;
	for(int i=nstartindex-1,j=0;i<(*ntotalline) && count<npagenum;i++)
	{
		pjjgs=(JjgsInfo *)[lcinfos.jjgsinfo objectAtIndex:i];
		if(!pjjgs)
			continue;
		tempArray = [[NSMutableArray alloc] init];
		
		[tempArray addObject:[NSString stringWithFormat:@"%@",pjjgs.jjgsdm]];
		[tempArray addObject:[NSString stringWithFormat:@"%@",pjjgs.jjgsmc]];
		if(pParse2)
		{
			int colcount=MIN([pParse2.sFieldColstr count],[tempArray count]);
			for(j=0;j<colcount;j++)
			{
				pfield=[pParse2.sFieldColstr objectAtIndex:j];
				if(pfield)
				{
					tmpstr=[tempArray objectAtIndex:j];
					NSDictionary * tempAttributes= [self getAttributes:MAC_CHINESEFONT fontSize:20.0f theColor:[NSColor whiteColor] theAliment:NSCenterTextAlignment];
					NSRect temprect = [tmpstr boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
					strsize = CGSizeMake(temprect.size.width, temprect.size.height);
					
					if(strsize.width>pfield.maxwidth)
						pfield.maxwidth=strsize.width;
				}
			}
		}
		[tempArray addObject:[self GetUIColorFromJjbs:pjjgs.njjbs]];
		
		[showData addObject:tempArray];
		[tempArray release];
		count++;
	}
	
	return @"";
}

-(NSString *)GetLczhCacheInfo:(NSMutableArray *)showData withparse:(id)pParses StartIndex:(int)nstartindex ReqLines:(int)npagenum withrownum:(int *)ntotalline withsucflag:(BOOL *)bsucflag
{
	(*ntotalline)=[lcinfos.jjzhinfo count];
	(*bsucflag)=YES;
	
	int count=0;
	NSMutableArray * tempArray=nil;
	JjZhInfo *pjjzh=nil;
	ParseRecv *pParse2=(ParseRecv *)pParses;
	CGSize strsize;
	NSString *tmpstr=nil;
	RecvField *pfield=nil;
	for(int i=nstartindex-1,j=0;i<(*ntotalline) && count<npagenum;i++)
	{
		pjjzh=(JjZhInfo *)[lcinfos.jjzhinfo objectAtIndex:i];
		if(!pjjzh)
			continue;
		tempArray = [[NSMutableArray alloc] init];
		
		[tempArray addObject:[NSString stringWithFormat:@"%@",pjjzh.jjgsdm]];
		[tempArray addObject:[NSString stringWithFormat:@"%@",pjjzh.jjgsmc]];
		[tempArray addObject:[NSString stringWithFormat:@"%@",pjjzh.jjzh]];
		[tempArray addObject:[NSString stringWithFormat:@"%@",pjjzh.khmc]];
		[tempArray addObject:[NSString stringWithFormat:@"%@",pjjzh.zjhm]];
		if(pParse2)
		{
			int colcount=MIN([pParse2.sFieldColstr count],[tempArray count]);
			for(j=0;j<colcount;j++)
			{
				pfield=[pParse2.sFieldColstr objectAtIndex:j];
				if(pfield)
				{
					tmpstr=[tempArray objectAtIndex:j];
					NSDictionary * tempAttributes= [self getAttributes:MAC_CHINESEFONT fontSize:20.0f theColor:[NSColor whiteColor] theAliment:NSCenterTextAlignment];
					NSRect temprect = [tmpstr boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
					strsize = CGSizeMake(temprect.size.width, temprect.size.height);
					
					if(strsize.width>pfield.maxwidth)
						pfield.maxwidth=strsize.width;
				}
			}
		}
		[tempArray addObject:COLOR_GRID_COMMONCOLOR];
		
		[showData addObject:tempArray];
		[tempArray release];
		count++;
	}
	
	return @"";
}

-(NSString *)GetLcdmCacheInfo:(NSMutableArray *)showData withparse:(id)pParses StartIndex:(int)nstartindex ReqLines:(int)npagenum withrownum:(int *)ntotalline withsucflag:(BOOL *)bsucflag
{
	(*ntotalline)=[lcinfos.jjdminfo count];
	(*bsucflag)=YES;
	
	int count=0;
	NSMutableArray * tempArray=nil;
	JjdmInfo *pjjdm=nil;
	ParseRecv *pParse2=(ParseRecv *)pParses;
	CGSize strsize;
	NSString *tmpstr=nil;
	RecvField *pfield=nil;
	for(int i=nstartindex-1,j=0;i<(*ntotalline) && count<npagenum;i++)
	{
		pjjdm=(JjdmInfo *)[lcinfos.jjdminfo objectAtIndex:i];
		if(!pjjdm)
			continue;
		tempArray = [[NSMutableArray alloc] init];
		
		[tempArray addObject:[NSString stringWithFormat:@"%@",pjjdm.jjdm]];
		[tempArray addObject:[NSString stringWithFormat:@"%@",pjjdm.jjmc]];
		[tempArray addObject:[NSString stringWithFormat:@"%@",pjjdm.jjgsdm]];
		[tempArray addObject:[NSString stringWithFormat:@"%.3f",pjjdm.jjjz]];
		[tempArray addObject:[NSString stringWithFormat:@"%@",pjjdm.jjjyzt]];
		[tempArray addObject:[NSString stringWithFormat:@"%.3f",pjjdm.grzdsgje]];
		[tempArray addObject:[NSString stringWithFormat:@"%.3f",pjjdm.frzdsgje]];
		[tempArray addObject:[NSString stringWithFormat:@"%.3f",pjjdm.zdcyfe]];
		[tempArray addObject:[NSString stringWithFormat:@"%.2f",pjjdm.zgshfe]];
		
		if(pParse2)
		{
			int colcount=MIN([pParse2.sFieldColstr count],[tempArray count]);
			for(j=0;j<colcount;j++)
			{
				pfield=[pParse2.sFieldColstr objectAtIndex:j];
				if(pfield)
				{
					tmpstr=[tempArray objectAtIndex:j];
					NSDictionary * tempAttributes= [self getAttributes:MAC_CHINESEFONT fontSize:20.0f theColor:[NSColor whiteColor] theAliment:NSCenterTextAlignment];
					NSRect temprect = [tmpstr boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
					strsize = CGSizeMake(temprect.size.width, temprect.size.height);
					
					if(strsize.width>pfield.maxwidth)
						pfield.maxwidth=strsize.width;
				}
			}
		}
		[tempArray addObject:[self GetUIColorFromJjbs:pjjdm.njjbs]];
		
		[showData addObject:tempArray];
		[tempArray release];
		count++;
	}
	
	return @"";
}


-(ScStrucInfo *)GetScStructInfo:(const char *)zqdm setcode:(int)nsetcode
{
	int nowID=[self GetNowSC:zqdm setcode:nsetcode];
	if(nowID>=0 && scinfos.m_bHasSCStruc && scinfos.m_scinfos && [scinfos.m_scinfos count]>nowID)
	{
		ScStrucInfo *pscStruc=[scinfos.m_scinfos objectAtIndex:nowID];
		if(pscStruc)
		{
			return pscStruc;
		}
	}
	return nil;
}

-(NSColor *)GetUIColorFromfdyk:(float )fdyk
{
	if(fdyk>0)
		return [NSColor redColor];
	else if(fdyk<0)
		return COLOR_TRADE_SELLCOLOR;
	else 
		return COLOR_GRID_NORMALCOLOR;
}

-(NSString *)GetBzStr:(int)nbz
{
	switch (nbz) {
		case 0:
			return @"人民币";
		case 1:
			return  @"美元";
		case 2:
			return @"港币";
	}
	return @"人民币";
}

-(BOOL)IsJyAutoLock
{
	if(m_blocking)
		return YES;
	if((time(NULL)-m_nlastjyopertime)>jyParams.nlockscreenspan*60)
	{
		m_blocking=YES;
		return YES;
	}
	return NO;
}

-(void)jyhasoper
{
	if(m_blocking==NO)
		m_nlastjyopertime=time(NULL);
}
@end
