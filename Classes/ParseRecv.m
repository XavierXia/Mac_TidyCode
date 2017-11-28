//
//  ParseRecv.m
//  tdxiphone
//
//  Created by 魏 文敏 on 10-1-21.
//  Copyright 2010 武汉. All rights reserved.
//

#import "ParseRecv.h"
#import "des.h"
#define TOKEN_LENTH 1

@implementation ParseRecv

@synthesize nrownum,ncolnum,psErrorNum,psErrorData,sData,sFieldColstr,nvisiblecolnum,coldict,sessionID,psErrorSign,nJls,bsucflag,rawlen,compresslen,bencrypted,bcompressed;
@synthesize btipflag,m_nqsid,nreqindex;

- (id) init
{
	self = [super init];
	if (self != nil) {
		sData=nil;
		sFieldColstr=nil;
		nrownum=0;
		ncolnum=0;
		bsucflag=NO;
		psErrorNum=nil;
		psErrorData=nil;
		coldict=nil;
		sessionID=0;
		psErrorSign=nil;
		nJls=0;
		rawlen=0;
		compresslen=0;
		bencrypted=0;
		bcompressed=0;
		btipflag=YES;
	}
	return self;
}

- (void) dealloc
{
	[psErrorSign release];
	[psErrorNum release];
	[psErrorData release];
	[coldict removeAllObjects];
	[coldict release];
	if(sData)
	{
		for(NSMutableArray *prow in sData)
		{
			if(prow)
			{
				for(NSString *pstr in prow)
					[pstr release];
			}
			[prow removeAllObjects];
			[prow release];
		}
		[sData removeAllObjects];
	}
	[sData release];
	if(sFieldColstr)
	{
		for(RecvField *pcol in sFieldColstr)
		{
			if(pcol)
				[pcol release];
		}
		[sFieldColstr removeAllObjects];
	}
	[sFieldColstr release];
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

-(BOOL) cleanHalfCharacter:(unsigned char*) sz len:(long) nlenth
{
    int nUnitLenth=0,nPos=0;
    while(nPos<nlenth)
    {
        nUnitLenth=0;
        
        if(sz[nPos]<=0x7F)
        {
            nUnitLenth=1;
        }
        if(nUnitLenth==0&&sz[nPos]>=0xA0&&sz[nPos]<=0xFE&&nPos<nlenth-1&&sz[nPos+1]>=0xA0&&sz[nPos+1]<=0xFE)
        {
            nUnitLenth=2;
        }
        if(nUnitLenth==0&&sz[nPos]>=0xB0&&sz[nPos]<=0xF7&&nPos<nlenth-1&&sz[nPos+1]>=0xA0&&sz[nPos+1]<=0xFE)
        {
            nUnitLenth=2;
        }
        if(nUnitLenth==0&&sz[nPos]>=0x81&&sz[nPos]<=0xFE)
        {
            if(nPos<nlenth-1&&((sz[nPos+1]>=0x40&&sz[nPos+1]<=0x7E)||(sz[nPos+1]>=0x80&&sz[nPos+1]<=0xFE)))
                nUnitLenth=2;
            else if(sz[nPos+1]>=0x30&&sz[nPos+1]<=0x39)
            {
                if(nPos<nUnitLenth-3&&sz[nPos+2]>=0x81&&sz[nPos+2]<=0xFE&&sz[nPos+3]>=0x30&&sz[nPos+3]<=39)
                    nUnitLenth=4;
            }
        }
        if(nUnitLenth>0)
            nPos+=nUnitLenth;
        else
            sz[nPos]=0;
        
    }
    return YES;
}

-(int)parseit:(NSData *)recvdata
{
	NSString *tempString=nil,*tempString1=nil,*tempString2=nil;
	
	[recvdata getTdxBytes:&sessionID range:NSMakeRange(SESSION_INDEX, sizeof(UInt64))];
	if(bencrypted == 1)
	{
		if(bcompressed == 1){
			int _length = [recvdata length]-HEADER_LEN ;
			unsigned char temp2char[_length*2];
			memset(temp2char,0,_length*2);
			memcpy(temp2char, [recvdata bytes]+HEADER_LEN, _length);
			unsigned char * pbySrc = temp2char;
			_length = (_length+23)/24 * 24;
			newDecrypt(pbySrc, _length);
			
			NSMutableData *tempData = [[NSMutableData alloc] initWithBytes:pbySrc length:_length];
			tempString = [self getDepress:tempData BodyFlag:0 RawLength:rawlen];
			[tempData release];
		}
		else
			tempString = [self getDecrypt:(NSMutableData *)recvdata BodyFlag:HEADER_LEN];
	}
	else if((bencrypted == 0)&&(bcompressed == 1))
		tempString = [self getDepress:(NSMutableData *)recvdata BodyFlag:HEADER_LEN RawLength:rawlen];
	else 
	{
		NSData *data=[recvdata subdataWithRange:NSMakeRange(HEADER_LEN, [recvdata length]-HEADER_LEN)];
		tempString = [[NSString alloc] initWithData:data encoding:CFStringConvertEncodingToNSStringEncoding (kCFStringEncodingGB_18030_2000)];
        
        if(tempString==nil)
        {
            unsigned char* sz=malloc([recvdata length]-HEADER_LEN+1024);
            memset(sz, 0, [recvdata length]-HEADER_LEN+1024);
            [data getBytes:sz];
            [self cleanHalfCharacter:sz len:[recvdata length]-HEADER_LEN];
            free(sz);
            tempString = [[NSString alloc] initWithCString:(const char*)sz encoding:CFStringConvertEncodingToNSStringEncoding (kCFStringEncodingGB_18030_2000)];
            
        }

	}
	//NSLog(@"%@",tempString);
	if(tempString==nil)
	{
		[psErrorSign release];
		psErrorSign=[[NSString alloc] initWithString:@"S"];
		[psErrorNum release];
		psErrorNum=[[NSString alloc] initWithString:@"-104"];
		[psErrorData release];
		psErrorData=[[NSString alloc] initWithString:@"应答包处理失败"];
		return 3;
	}
    if((nreqindex==TDX_SSLTOUCH || nreqindex==TDX_SSLSHAKE) && [tempString characterAtIndex:0]=='I')
        bsucflag=NO;
	else if([tempString characterAtIndex:0]=='0')
		bsucflag=YES;
 	else 
		bsucflag=NO;
	
	NSRange subrange,subrange1,subrange2,subrange3,tmprange,errorrange;
	NSUInteger nstrlength=[tempString length];
    errorrange = [tempString rangeOfString:@"F"];
	subrange=[tempString rangeOfString:@"\r\n"];
	subrange1.location=0;
	subrange1.length=0;
	nrownum=0;
	ncolnum=0;
	int nvisibleindex=0,colindex=0;
	int index=0;
	CGSize strsize;
	if(bsucflag)
		sData=[[NSMutableArray alloc] init];
	
	if((subrange.location!=NSNotFound && subrange.length>0) && (errorrange.location != 0) && bsucflag)
	{
		while (subrange.location!=NSNotFound&& subrange.location<[tempString length] && subrange.length>0)
		{
			subrange1.length=subrange.location;
			tempString1=[tempString substringWithRange:subrange1];
			//////////分析/////////////////
			if(index==0)//列
			{
				if(bsucflag==YES)//列
				{
					
				}			
			}
			else if(index==1 && bsucflag==YES)
			{
				sFieldColstr=[[NSMutableArray alloc] initWithCapacity:10];
				coldict=[[NSMutableDictionary alloc] initWithCapacity:10];
				subrange3.location=0;
				subrange3.length=0;
				subrange2=[tempString1 rangeOfString:@"|"];
				while(subrange2.location!=NSNotFound && subrange2.location<[tempString1 length]&& subrange2.length>0)
				{
					RecvField *pfield=[RecvField new];
					pfield.index=ncolnum;
					ncolnum++;
					if(subrange2.location!=NSNotFound && subrange2.location<[tempString1 length]&& subrange2.length>0)
						pfield.m_dwFieldId=[[tempString1 substringWithRange:NSMakeRange((subrange3.location+subrange3.length+1), (subrange2.location-subrange3.location-subrange3.length))] intValue];
					switch (pfield.m_dwFieldId) {
						case TDX_ID_XT_POSITIONSTRING:
						case TDX_ID_TOTALLINE:
						case TDX_ID_MMBZ:
						case TDX_ID_SCFLAG:
						case TDX_ID_WTFS:
						case TDX_ID_KCDBZ:
						case TDX_ID_YWDM:
						case TDX_ID_ZHLB:
						case TDX_ID_XT_DISPLAYCOLOR:
                        case TDX_ID_XT_HANDLE:
							pfield.m_bvisible=NO;
							break;
						default:
							break;
					}
                    subrange3=[[tempString1 substringFromIndex:(subrange2.location+subrange2.length)] rangeOfString:@"|"];
                    if(subrange3.location!=NSNotFound && subrange3.location<[tempString1 length] && subrange3.length>0)
                        pfield.m_sFieldName=[[NSString alloc] initWithFormat:@"%@",[tempString1 substringWithRange:NSMakeRange((subrange2.location+subrange2.length), subrange3.location)]];
                    else
                        pfield.m_sFieldName=[[NSString alloc] initWithFormat:@"%@",@"未知字段"];
                    [pfield.m_sFieldName release];
                    NSDictionary * tempAttributes= [self getAttributes:MAC_CHINESEFONT fontSize:20.0f theColor:[NSColor whiteColor] theAliment:NSCenterTextAlignment];
                    NSRect temprect = [pfield.m_sFieldName boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
                    strsize = CGSizeMake(temprect.size.width, temprect.size.height);
                    
#ifdef IMAC_HXZQ
                    if([pfield.m_sFieldName isEqualToString:@"参考保本价"])
                    {
                        pfield.m_bvisible=NO;
                    }
                    
#endif
					if(pfield.m_bvisible)
					{
						pfield.nvisibleindex=nvisibleindex;
						nvisibleindex++;
					}
					
					
					
					if(strsize.width>pfield.maxwidth)
						pfield.maxwidth=strsize.width;
					subrange2.location+=(subrange2.length+subrange3.location);
					subrange2.length=subrange3.length;
					subrange3=[[tempString1 substringFromIndex:(subrange2.location+subrange2.length)] rangeOfString:@"|"];
					if(subrange3.location!=NSNotFound && subrange3.location<[tempString1 length] && subrange3.length>0)
					{
						pfield.m_cFieldType=[[tempString1 substringWithRange:NSMakeRange((subrange2.location+subrange2.length), subrange3.location)] intValue];
						subrange2.location+=(subrange2.length+subrange3.location);
						subrange2.length=subrange3.length;
						subrange3=[[tempString1 substringFromIndex:(subrange2.location+subrange2.length)] rangeOfString:@"|"];
						if(subrange3.location!=NSNotFound  && subrange3.location<[tempString1 length]&& subrange3.length>0)
						{
							tmprange=subrange2;
							subrange2.location+=(subrange2.length+subrange3.location);
							subrange2.length=subrange3.length;
							subrange3=tmprange;
						}
						else 
						{
							[pfield release];
							break;
						}
					}
					else 
					{
						[pfield release];
						break;
					}
					[sFieldColstr addObject:pfield];
					[coldict setObject:pfield forKey:[NSString stringWithFormat:@"%i",pfield.m_dwFieldId]];
				};				
			}
			else //内容
			{
				NSMutableArray *prowdata=[[NSMutableArray alloc] initWithCapacity:ncolnum+1];
				subrange3.location=0;
				subrange3.length=0;
				subrange2=[tempString1 rangeOfString:@"|"];
				colindex=0;
				while(subrange2.location!=NSNotFound && subrange2.location<[tempString1 length] && subrange.length>0)
				{
					tempString2=[[NSString alloc]  initWithFormat:@"%@",[tempString1 substringWithRange:NSMakeRange((subrange3.location+subrange3.length), (subrange2.location-subrange3.location-subrange3.length))]];
					[prowdata addObject:tempString2];		
					
					if(colindex<[sFieldColstr count])
					{
						RecvField *pfield=[sFieldColstr objectAtIndex:colindex];
						if(pfield)
						{
							NSDictionary * tempAttributes= [self getAttributes:MAC_CHINESEFONT fontSize:20.0f theColor:[NSColor whiteColor] theAliment:NSCenterTextAlignment];
							NSRect temprect = [tempString2 boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
							strsize = CGSizeMake(temprect.size.width, temprect.size.height);
						
							if(strsize.width>pfield.maxwidth)
								pfield.maxwidth=strsize.width;
						}
					}
					colindex++;
																											 
					subrange3=[[tempString1 substringFromIndex:(subrange2.location+subrange2.length)] rangeOfString:@"|"];
					if(subrange3.location!=NSNotFound && subrange3.location<[tempString1 length] && subrange3.length>0)
					{
						tmprange=subrange2;
						subrange2.location+=(subrange2.length+subrange3.location);
						subrange2.length=subrange3.length;
						subrange3=tmprange;
					}
					else 
						break;
				};
				if([prowdata count])
				{
					[sData addObject:prowdata];
					nrownum++;
				}
				else 
					[prowdata release];
			}
			
			//////////分析/////////////////
			
			subrange1.location=(subrange1.length+subrange1.location+subrange.length);
			subrange=[[tempString substringFromIndex:subrange1.location]rangeOfString:@"\r\n"];
			index++;
			if(subrange.location==NSNotFound)
			{
				subrange1.length=(nstrlength-subrange1.location);
				if(subrange1.length>0)
				{
					tempString1=[tempString substringWithRange:subrange1];
					//////////分析内容/////////////////
					colindex=0;
					NSMutableArray *prowdata=[[NSMutableArray alloc] initWithCapacity:ncolnum+1];
					subrange3.location=0;
					subrange3.length=0;
					subrange2=[tempString1 rangeOfString:@"|"];
					while(subrange2.location!=NSNotFound && subrange2.location<[tempString1 length] && subrange2.length>0)
					{
						tempString2=[[NSString alloc]  initWithFormat:@"%@",[tempString1 substringWithRange:NSMakeRange((subrange3.location+subrange3.length), (subrange2.location-subrange3.location-subrange3.length))]];
						[prowdata addObject:tempString2];	
						
						if(colindex<[sFieldColstr count])
						{
							RecvField *pfield=[sFieldColstr objectAtIndex:colindex];
							if(pfield)
							{
								NSDictionary * tempAttributes= [self getAttributes:MAC_CHINESEFONT fontSize:20.0f theColor:[NSColor whiteColor] theAliment:NSCenterTextAlignment];
								NSRect temprect = [tempString2 boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
								strsize = CGSizeMake(temprect.size.width, temprect.size.height);
								
						
								if(strsize.width>pfield.maxwidth)
									pfield.maxwidth=strsize.width;
							}
						}
						colindex++;
					
						subrange3=[[tempString1 substringFromIndex:(subrange2.location+subrange2.length)] rangeOfString:@"|"];
						if(subrange3.location!=NSNotFound && subrange3.location<[tempString1 length] && subrange3.length>0)
						{
							tmprange=subrange2;
							subrange2.location+=(subrange2.length+subrange3.location);
							subrange2.length=subrange3.length;
							subrange3=tmprange;
						}
						else 
							break; 
					};
					if([prowdata count])
					{
						[sData addObject:prowdata];
						nrownum++;
					}
					else 
						[prowdata release];
				//////////分析内容/////////////////
				}
				break;
			}
		};
	}
	else //错误信息
	{
		subrange2=[tempString rangeOfString:@"|"];
		BOOL berrflag=YES;
		if(subrange2.location!=NSNotFound  && subrange2.location<[tempString length] && subrange2.length>0)
		{
			berrflag=YES;
			[psErrorSign release];
			psErrorSign=[[NSString alloc] initWithFormat:@"%@",[tempString substringWithRange:NSMakeRange(0, subrange2.location)]];
			
			subrange3=[[tempString substringFromIndex:(subrange2.location+subrange2.length)] rangeOfString:@"|"];
			if(subrange3.location!=NSNotFound && subrange3.location<[tempString length]&& subrange3.length>0)
			{
				[psErrorNum release];
				psErrorNum=[[NSString alloc] initWithFormat:@"%@",[tempString substringWithRange:NSMakeRange((subrange2.location+subrange2.length), subrange3.location)]];
			
				subrange2.location+=(subrange2.length+subrange3.location);
				subrange2.length=subrange3.length;
				subrange3=[[tempString substringFromIndex:(subrange2.location+subrange2.length)] rangeOfString:@"|"];	
				[psErrorData release];
				if(subrange3.location!=NSNotFound && subrange3.location<[tempString length])
					psErrorData=[[NSString alloc] initWithFormat:@"%@",[tempString substringWithRange:NSMakeRange((subrange2.location+subrange2.length), subrange3.location)]];
				else 
					psErrorData=[[NSString alloc] initWithFormat:@"%@",[tempString substringFromIndex:(subrange2.location+subrange2.length)]];
			}
			else 
				berrflag=NO;
		}
		else 
			berrflag=NO;
		if(berrflag==NO) 
		{
			[psErrorSign release];
			psErrorSign=[[NSString alloc] initWithString:@"S"];
			[psErrorNum release];
			psErrorNum=[[NSString alloc] initWithString:@"-104"];
			[psErrorData release];
			psErrorData=[[NSString alloc] initWithString:@"应答包错误信息处理失败"];
			return 3;
		}
	}
	
	[tempString release];
	return 0;
}

-(NSString *)getFieldData:(int)nrow fieldFlag:(int)nFlag
{
	if(sData==nil)
		return @"";
	if([sData count]<=nrow)
		return @"";
	RecvField *pfield=[coldict objectForKey:[NSString stringWithFormat:@"%i",nFlag]];
	if(pfield==nil)
		return @"";
	NSMutableArray *rows=[sData objectAtIndex:nrow];
	if(rows && [rows count]>pfield.index)
		return [NSString stringWithFormat:@"%@", [rows objectAtIndex:pfield.index]];
	return @"";
}

-(int)getTdxIdIndex:(int)ntdxid
{
	RecvField *pfield=[coldict objectForKey:[NSString stringWithFormat:@"%i",ntdxid]];
	if(pfield==nil)
		return -1;
	return pfield.nvisibleindex;
}

-(int)getRecvJx:(NSString *)theString{
		return 0;
}

-(int)setField{
	return 1;
}

-(void) getStockId:(int)nGdid{
	return;
}

-(char *)GetSFieldColStr:(int)index
{
	return "";
}


-(NSColor *)GetUIColorFromMmbz:(NSString *)mmbz
{
	if([mmbz isEqualToString:@"A"]==YES)
		return COLOR_TRADE_SELLCOLOR;
	else if([mmbz isEqualToString:@"V"]==YES)
		return [NSColor redColor];
	else {
		int nmmbz=[mmbz intValue];
		switch (nmmbz) {
			case 0:
			case 6:
				return [NSColor redColor];
				break;
			case 1:
			case 7:
			case 3:
			case 4:
			case 5:
				return COLOR_TRADE_SELLCOLOR;
				break;
			case 2:
			case 8:
				return COLOR_GRID_NORMALCOLOR;
				break;
			default:
				break;
		}
	}
	return COLOR_GRID_NORMALCOLOR;
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

-(NSColor *)GetUIColorFromJjbs:(int )jjbs
{
	if(jjbs==1)
		return [NSColor redColor];
	else 
		return COLOR_GRID_NORMALCOLOR;
}

-(NSColor *)GetUIColorFromBZ:(int)nbz
{
	switch (nbz) {
		case 0:
			return [NSColor redColor];
			break;
		case 1:
			//return [NSColor greenColor];	
			return COLOR_TRADE_SELLCOLOR;
			break;
		case 2:
			return COLOR_GRID_NORMALCOLOR;
		default:
			break;
	}
	return COLOR_GRID_NORMALCOLOR;
}

-(NSColor *)GetUIColorFromDisplayColor:(int)rgb
{
	return [NSColor redColor];

}

-(NSMutableArray * )getItemData1:(NSMutableArray *)theData Index:(int)nRow TDX_Choise:(int)nChoise withflag:(BOOL *)bflag
{
	(*bflag)=YES;
	NSString * tempString;
	switch (nChoise) {
		case TDX_JJWT:
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_WTRQ];		//委托日期
			
			NSDateFormatter* dateFormatter = [[NSDateFormatter alloc] init];
			[dateFormatter setDateFormat:@"yyyyMMdd"];
			NSString *currentDate = [dateFormatter stringFromDate: [NSDate date]];
			[dateFormatter release];
			if([currentDate isEqualToString:tempString]==NO)//以后可以根据配置决定是否显示历史委托 
			{
				(*bflag)=NO;
				return theData;
			}
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_MMBZ];//买卖标志
			[theData addObject:tempString];
			[theData addObject:[self GetUIColorFromMmbz:tempString]];
			return theData;
			break;			
	}
	[theData addObject:COLOR_GRID_COMMONCOLOR];
	return theData;
}

-(NSMutableArray * )getItemData2:(NSMutableArray *)theData Index:(int)nRow TDX_Choise:(int)nChoise withclientinfo:(ClientInfo *)pclientinfo withzjgf:(ZjgfInfoClass *)zjgfclass
{
	NSString * tempString;
	switch (nChoise) {
		case TDX_ZJYE://"币种",@"余额",@"可用",@"参考市值",@"资产",@"盈亏"
		{
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_BZ];//"币种" // 币种 0:RMB 1:MY 2:GB
			int nbz=[tempString intValue];
			if(nbz == 0)
				[theData addObject:@"人民币"];
			else if(nbz == 1)
				[theData addObject:@"美元"];
			else
				[theData addObject:@"港币"];
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_KQZJ];//"余额"
			ST_ZJGFINFO tmpzjgf=zjgfclass.stzjgf;
			tmpzjgf.kqzj[nbz]=[tempString doubleValue];
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_ZJYE];//"余额"
			tmpzjgf.ye[nbz]=[tempString doubleValue];
			if(nbz==1)
				tempString=[NSString stringWithFormat:@"%.3f",tmpzjgf.ye[nbz]];
			else 
				tempString=[NSString stringWithFormat:@"%.2f",tmpzjgf.ye[nbz]];
			[theData addObject:tempString];
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_KYZJ];//"可用"
			tmpzjgf.keyong[nbz]=[tempString doubleValue];
			if(nbz==1)
				tempString=[NSString stringWithFormat:@"%.3f",tmpzjgf.keyong[nbz]];
			else 
				tempString=[NSString stringWithFormat:@"%.2f",tmpzjgf.keyong[nbz]];
			tmpzjgf.zzc[nbz]=tmpzjgf.keyong[nbz];
			
			[theData addObject:tempString];
			if(nbz==1)
				tempString=[NSString stringWithFormat:@"%.3f",tmpzjgf.zsz[nbz]];//"参考市值"
			else 
				tempString=[NSString stringWithFormat:@"%.2f",tmpzjgf.zsz[nbz]];//"参考市值"
			[theData addObject:tempString];
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_DJZJ];//"冻结"
			tmpzjgf.djzj[nbz]=[tempString doubleValue];
			tmpzjgf.zzc[nbz]+=tmpzjgf.djzj[nbz];
			
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_ZTZJ];//"在途"
			tmpzjgf.ztzj[nbz]=[tempString doubleValue];
			if(m_nqsid!=SYWG_DLL)
				tmpzjgf.zzc[nbz]+=tmpzjgf.ztzj[nbz];
			
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_GTZZC];//"资产"
			tmpzjgf.gtzzc[nbz]=[tempString doubleValue];
//			if(!([tempString length] && [tempString isEqualToString:@"－"]==NO))
//			{
				if(nbz==1)
					tempString=[NSString stringWithFormat:@"%.3f",tmpzjgf.zzc[nbz]];//"总资产"
				else	
					tempString=[NSString stringWithFormat:@"%.2f",tmpzjgf.zzc[nbz]];//"总资产"
//			}
            
			[theData addObject:tempString];
			if(nbz==1)
				tempString=[NSString stringWithFormat:@"%.3f",tmpzjgf.fdyk[nbz]];//"浮动盈亏"
			else 
				tempString=[NSString stringWithFormat:@"%.2f",tmpzjgf.fdyk[nbz]];//"浮动盈亏"
			[theData addObject:tempString];
			[theData addObject:[self GetUIColorFromfdyk:tmpzjgf.fdyk[nbz]]];
			zjgfclass.stzjgf=tmpzjgf;
			return theData;
		}
			break;
		case TDX_ZJYE2://"币种",@"余额",@"可用",@"参考市值",@"资产",@"盈亏"
		{
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_BZ];//"币种" // 币种 0:RMB 1:MY 2:GB
			int nbz=[tempString intValue];
			if(nbz == 0)
				[theData addObject:@"人民币"];
			else if(nbz == 1)
				[theData addObject:@"美元"];
			else
				[theData addObject:@"港币"];
			ST_ZJGFINFO tmpzjgf=zjgfclass.stzjgf;
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_KQZJ];//"余额"
			tmpzjgf.kqzj[nbz]=[tempString doubleValue];
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_ZJYE];//"余额"
			tmpzjgf.ye[nbz]=[tempString doubleValue];
			if(nbz==1)
				tempString=[NSString stringWithFormat:@"%.3f",tmpzjgf.ye[nbz]];
			else 
				tempString=[NSString stringWithFormat:@"%.2f",tmpzjgf.ye[nbz]];
			[theData addObject:tempString];
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_KYZJ];//"可用"
			tmpzjgf.keyong[nbz]=[tempString doubleValue];
			if(nbz==1)
				tempString=[NSString stringWithFormat:@"%.3f",tmpzjgf.keyong[nbz]];
			else 
				tempString=[NSString stringWithFormat:@"%.2f",tmpzjgf.keyong[nbz]];
			tmpzjgf.jjzzc[nbz]+=tmpzjgf.keyong[nbz];
			
			[theData addObject:tempString];
			if(nbz==1)
				tempString=[NSString stringWithFormat:@"%.3f",tmpzjgf.jjzsz[nbz]];//"参考市值"
			else 
				tempString=[NSString stringWithFormat:@"%.2f",tmpzjgf.jjzsz[nbz]];//"参考市值"
			[theData addObject:tempString];
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_DJZJ];//"冻结"
			tmpzjgf.djzj[nbz]=[tempString doubleValue];
			tmpzjgf.jjzzc[nbz]+=tmpzjgf.djzj[nbz];
			
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_ZTZJ];//"在途"
			tmpzjgf.ztzj[nbz]=[tempString doubleValue];
			if(m_nqsid!=SYWG_DLL)
				tmpzjgf.jjzzc[nbz]+=tmpzjgf.ztzj[nbz];
			
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_GTZZC];//"资产"
			tmpzjgf.gtzzc[nbz]=[tempString doubleValue];
			if(!([tempString length] && [tempString isEqualToString:@"－"]==NO))
			{
				if(nbz==1)
					tempString=[NSString stringWithFormat:@"%.3f",tmpzjgf.jjzzc[nbz]];//"总资产"
				else	
					tempString=[NSString stringWithFormat:@"%.2f",tmpzjgf.jjzzc[nbz]];//"总资产"
			}
			[theData addObject:tempString];
			if(nbz==1)
				tempString=[NSString stringWithFormat:@"%.3f",tmpzjgf.jjfdyk[nbz]];//"浮动盈亏"
			else 
				tempString=[NSString stringWithFormat:@"%.2f",tmpzjgf.jjfdyk[nbz]];//"浮动盈亏"
			[theData addObject:tempString];
			[theData addObject:[self GetUIColorFromfdyk:tmpzjgf.jjfdyk[nbz]]];
			zjgfclass.stzjgf=tmpzjgf;
			return theData;
		}
			break;
		case TDX_ZJYE3://"币种",@"余额",@"可用",@"参考市值",@"资产",@"盈亏"
		{
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_BZ];//"币种" // 币种 0:RMB 1:MY 2:GB
			int nbz=[tempString intValue];
			if(nbz == 0)
				[theData addObject:@"人民币"];
			else if(nbz == 1)
				[theData addObject:@"美元"];
			else
				[theData addObject:@"港币"];
			ST_ZJGFINFO tmpzjgf=zjgfclass.stzjgf;
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_KQZJ];//"余额"
			tmpzjgf.kqzj[nbz]=[tempString doubleValue];
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_ZJYE];//"余额"
			tmpzjgf.ye[nbz]=[tempString doubleValue];
			if(nbz==1)
				tempString=[NSString stringWithFormat:@"%.3f",tmpzjgf.ye[nbz]];
			else 
				tempString=[NSString stringWithFormat:@"%.2f",tmpzjgf.ye[nbz]];
			[theData addObject:tempString];
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_KYZJ];//"可用"
			tmpzjgf.keyong[nbz]=[tempString doubleValue];
			if(nbz==1)
				tempString=[NSString stringWithFormat:@"%.3f",tmpzjgf.keyong[nbz]];
			else 
				tempString=[NSString stringWithFormat:@"%.2f",tmpzjgf.keyong[nbz]];
			tmpzjgf.lczzc[nbz]+=tmpzjgf.keyong[nbz];
			
			[theData addObject:tempString];
			if(nbz==1)
				tempString=[NSString stringWithFormat:@"%.3f",tmpzjgf.lczsz[nbz]];//"参考市值"
			else 
				tempString=[NSString stringWithFormat:@"%.2f",tmpzjgf.lczsz[nbz]];//"参考市值"
			[theData addObject:tempString];
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_DJZJ];//"冻结"
			tmpzjgf.djzj[nbz]=[tempString doubleValue];
			tmpzjgf.lczzc[nbz]+=tmpzjgf.djzj[nbz];
			
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_ZTZJ];//"在途"
			tmpzjgf.ztzj[nbz]=[tempString doubleValue];
			if(m_nqsid!=SYWG_DLL)
				tmpzjgf.lczzc[nbz]+=tmpzjgf.ztzj[nbz];
			
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_GTZZC];//"资产"
			tmpzjgf.gtzzc[nbz]=[tempString doubleValue];
			if(!([tempString length] && [tempString isEqualToString:@"－"]==NO))
			{
				if(nbz==1)
					tempString=[NSString stringWithFormat:@"%.3f",tmpzjgf.lczzc[nbz]];//"总资产"
				else	
					tempString=[NSString stringWithFormat:@"%.2f",tmpzjgf.lczzc[nbz]];//"总资产"
			}
			[theData addObject:tempString];
			if(nbz==1)
				tempString=[NSString stringWithFormat:@"%.3f",tmpzjgf.lcfdyk[nbz]];//"浮动盈亏"
			else 
				tempString=[NSString stringWithFormat:@"%.2f",tmpzjgf.lcfdyk[nbz]];//"浮动盈亏"
			[theData addObject:tempString];
			[theData addObject:[self GetUIColorFromfdyk:tmpzjgf.lcfdyk[nbz]]];
			zjgfclass.stzjgf=tmpzjgf;
			return theData;
		}
			break;
		case TDX_GDCX:
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_GDDM];		//“股东代码”
			[theData addObject:[NSString stringWithFormat:@"%@%@",tempString,[pclientinfo.gdinfos GetMainGdStr:tempString]]];
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_GDMC];		//“股东名称”
			[theData addObject:tempString];
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_ZHLB];		//“市场”
			[theData addObject:[GdmxInfo GetWtTypeStr2:[tempString intValue]]];
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_ZJZH];		//“资金账户”
			if(!([tempString length] && [tempString isEqualToString:@"－"]==NO && [tempString isEqualToString:@"0"]==NO))
				[theData addObject:[pclientinfo GetZjzh]];
			else 
				[theData addObject:tempString];
			break;			
	}
	[theData addObject:COLOR_GRID_COMMONCOLOR];
	return theData;
}

-(NSMutableArray * )getItemData:(NSMutableArray *)theData Index:(int)nRow TDX_Choise:(int)nChoise{
	NSString * tempString;
	switch (nChoise) {
		case TDX_LXCX:
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_KHMC];		//"客户名称"0
			[theData addObject:tempString];
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_USERADDRESS];	//"地址"1
			[theData addObject:tempString];
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_USERPHONE];	//"联系电话"2
			[theData addObject:tempString];
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_USEREMAIL];	//"用户邮箱"3
			[theData addObject:tempString];
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_KHTYPE];		//"开户类型"4
			[theData addObject:tempString];
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_ZJHM];		//"证件号码"5
			[theData addObject:tempString];
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_MOBILEPHONE];	//"移动电话"6
			[theData addObject:tempString];
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_HOMEPHONE];	//"住宅电话"7
			[theData addObject:tempString];
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_WORKPHONE];	//"单位电话"8
			[theData addObject:tempString];
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_FAX];			//"传真"9
			[theData addObject:tempString];
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_EDU];			//"教育程度"10
			[theData addObject:tempString];
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_SALARY];		//"年收入"11
			[theData addObject:tempString];
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_VOCATION];	//"职业"12
			[theData addObject:tempString];
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_DZDBZ];		//"对账单标志"13
			[theData addObject:tempString];
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_SEX];			//"性别"14
			[theData addObject:tempString];
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_POSTALCODE];	//"邮编"15
			[theData addObject:tempString];
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_KFSJJ_JJZH];	//"基金账户"16
			[theData addObject:tempString];
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_WTBH];		//"委托编号"17
			[theData addObject:tempString];
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_ZJLB];		//"证件类别"18
			[theData addObject:tempString];
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_SFFS];		//"收费方式"19
			[theData addObject:tempString];
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_KFSJJ_DIVIDENMETHOD];		//"分红方式"20
			[theData addObject:tempString];
			return theData;
			break;
		case TDX_CDCX://"证券名称","买卖标志","状态说明","委托价格","委托数量","成交价格","成交数量"
        case TDX_DBPHZCDCX:
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_SCFLAG];//买卖标志
			[theData addObject:tempString];
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_MMBZ];//买卖标志
			[theData addObject:tempString];
			[theData addObject:[self GetUIColorFromMmbz:tempString]];
			return theData;
			break;
		case TDX_GFCX://@"证券名称",@"证券数量",@"成本价",@"浮动盈亏",@"可卖数量"
					  //@"最新市值",@"当前价",@"今买数量",@"证券代码",@"股东代码"
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_FDYK];//"浮动盈亏"
			float  fdyk=[tempString floatValue];
			[theData addObject:[self GetUIColorFromfdyk:fdyk]];
			return theData;
			break;
//@"证券代码",@"证券名称",@"股票持有(股数)",@"预期持有(股数)",@"市场价",@"前收市价",@"帐号类别",@"前收市值"
		case TDX_GFCX_HK:
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_FDYK];//浮动盈亏
			[theData addObject:[self GetUIColorFromfdyk:[tempString floatValue]]];
			return theData;
			break;
//@"证券代码",@"证券名称",@"委托时间",@"买卖标志",@"委托价格",@"委托数量",@"成交均价",@"成交数量",
//@"未成交数量",@"报价方式",@"状态说明",@"客户号",@"下单来源",@"委托编号",@"可改单标志"
		case TDX_DRWT_HK:
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_MMBZ];//买卖标志
			[theData addObject:[self GetUIColorFromMmbz:tempString]];
			return theData;
			break;
		case TDX_DRWT://"证券名称","买卖标志","状态说明","委托价格","委托数量","成交价格","成交数量"
			//,"委托时间","委托编号","证券代码","股东代码","报价方式"
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_SCFLAG];//买卖标志
			[theData addObject:tempString];
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_MMBZ];//买卖标志
			[theData addObject:tempString];
			[theData addObject:[self GetUIColorFromMmbz:tempString]];
			return theData;
			break;
		case TDX_LSWT://"证券名称","买卖标志","状态说明","委托价格","委托数量","成交价格","成交数量"
			//,"委托时间","委托编号","证券代码","股东代码","报价方式"
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_MMBZ];//买卖标志
			[theData addObject:[self GetUIColorFromMmbz:tempString]];
			return theData;
			break;
		case TDX_DRCJ://"证券名称",@"成交时间",@"买卖标志",@"成交价格",@"成交数量",
			//@"成交金额",@"成交编号",@"委托编号",@"证券代码",@"股东代码"
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_MMBZ];//"股东代码"
			[theData addObject:tempString];
			[theData addObject:[self GetUIColorFromMmbz:tempString]];
			return theData;
			break;
		case TDX_LSCJ://"证券名称",@"成交时间",@"买卖标志",@"成交价格",@"成交数量",
			//@"成交金额",@"成交编号",@"委托编号",@"证券代码",@"股东代码"
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_MMBZ];//"股东代码"
			[theData addObject:tempString];
			[theData addObject:[self GetUIColorFromMmbz:tempString]];
			return theData;
			break;
		case TDX_CJHZ://"证券名称",@"成交时间",@"买卖标志",@"成交价格",@"成交数量",
			//@"成交金额",@"成交编号",@"委托编号",@"证券代码",@"股东代码"
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_MMBZ];//"股东代码"
			[theData addObject:tempString];
			[theData addObject:[self GetUIColorFromMmbz:tempString]];
			return theData;
			break;
		case TDX_ZJLS://"证券名称",@"成交时间",@"买卖标志",@"成交价格",@"成交数量",
			//@"成交金额",@"成交编号",@"委托编号",@"证券代码",@"股东代码"
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_ZJLS_FSJE];//"成交金额"
			float fsje=[tempString floatValue];
			if(fsje<=0)
			{
				tempString = [self getFieldData:nRow fieldFlag:TDX_ID_QSJE];
				fsje=[tempString floatValue];
			}
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_XT_DISPLAYCOLOR];
			if([tempString length])
				[theData addObject:[self GetUIColorFromDisplayColor:[tempString intValue]]];
			else 
				[theData addObject:[self GetUIColorFromfdyk:fsje]];
			return theData;
			break;
		case TDX_PHCX://"证券名称",@"成交时间",@"买卖标志",@"成交价格",@"成交数量",
        case TDX_IPOSGED:
			//@"成交金额",@"成交编号",@"委托编号",@"证券代码",@"股东代码"
			[theData addObject:[NSColor redColor]];
			return theData;
			break;
		case TDX_DRCJ_HK:
//			@"委托时间",@"证券代码",@"买卖标志说明",@"证券名称",@"委托价格",@"委托数量",@"成交均价",@"成交数量",
			//@"未成交数量",@"报价方式",@"状态说明",@"客户号",@"下单来源",@"委托编号"
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_MMBZ];//买卖标志
			[theData addObject:[self GetUIColorFromMmbz:tempString]];
			return theData;
			break;
		case TDX_ZJYE://"币种",@"余额",@"可用",@"参考市值",@"资产",@"盈亏"
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_BZ];//"币种" // 币种 0:RMB 1:MY 2:GB
			int nbz=[tempString intValue];
			if(nbz == 0)
				[theData addObject:@"人民币"];
			else if(nbz == 1)
				[theData addObject:@"美元"];
			else
				[theData addObject:@"港币"];
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_ZJYE];//"余额"
			[theData addObject:tempString];
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_KYZJ];//"可用"
			[theData addObject:tempString];
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_ZXSZ];//"参考市值"
			[theData addObject:tempString];
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_GTZZC];//"资产"
			[theData addObject:tempString];
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_FDYK];//"盈亏"
			[theData addObject:tempString];
			[theData addObject:[self GetUIColorFromfdyk:[tempString floatValue]]];
			return theData;
			break;
		case TDX_FECX://@"基金代码",@"基金名称",@"当前数量",@"可用份额",@"冻结数量",@"最新市值",
			//@"分红标志",@"分红方式",@"基金公司代码",@"基金公司名称"
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_FDYK];//浮动盈亏
			[theData addObject:[self GetUIColorFromfdyk:[tempString floatValue]]];
			return theData;
			break;
		case TDX_LCFECX://@"基金代码",@"基金名称",@"当前数量",@"可用份额",@"冻结数量",@"最新市值",
			//@"分红标志",@"分红方式",@"基金公司代码",@"基金公司名称"
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_FDYK];//浮动盈亏
			[theData addObject:[self GetUIColorFromfdyk:[tempString floatValue]]];
			return theData;
			break;
		case TDX_DMCX://@"基金代码",@"基金名称",@"基金公司代码",@"基金净值",@"基金状态",@"状态说明",
					  //@"个人最低认购金额",@"法人最低认购金额",@"最低持有份额",@"最高赎回份额"
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_KFSJJ_JJBS];//基金标志
			[theData addObject:[self GetUIColorFromJjbs:[tempString intValue]]];
			return theData;
			break;
		case TDX_CJCX_HK://@"委托时间",@"证券代码",@"买卖标志",@"证券名称",@"成交价格",@"成交数量",
			//@"成交金额",@"报价方式",@"状态说明",@"客户号",@"委托编码",@"下单来源"
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_KFSJJ_MMBZ];//买卖标志
			[theData addObject:[self GetUIColorFromMmbz:tempString]];
			return theData;
			break;
		case TDX_CJCX://@"基金账户",@"基金代码",@"基金名称",@"公司代码",@"公司名称",@"成交编号",@"委托编号",@"业务代码",@"业务名称",@"委托日期",@"交易金额",@"委托份额",@"成交日期",@"成交金额",@"成交份额"
		case TDX_JJLSCJCX:
		case TDX_JJDRWTCX:
		case TDX_JJFJYDRWTCX:
		case TDX_JJFJYLSWTCX:
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_KFSJJ_MMBZ];//买卖标志
			if(nChoise==TDX_JJDRWTCX)
				[theData addObject:tempString];
			[theData addObject:[self GetUIColorFromMmbz:tempString]];
			return theData;
			break;
		case TDX_GSCX://@"基金公司代码",@"基金公司名称"
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_KFSJJ_JJBS];//基金标志
			[theData addObject:[self GetUIColorFromJjbs:[tempString intValue]]];
			return theData;
			break;
		case TDX_ZHCX:
			break;
		case TDX_WTCX_HK:
//			@"委托时间",@"证券代码",@"买卖标志",@"证券名称",@"委托价格",@"委托数量",@"成交数量",
			//@"未成交数量",@"报价方式",@"客户号",@"委托编号",@"状态说明",@"下单来源"
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_MMBZ];//买卖标志
			[theData addObject:[self GetUIColorFromMmbz:tempString]];
			return theData;
			break;
		case TDX_WTCX:
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_KFSJJ_MMBZ];//买卖标志
			[theData addObject:[self GetUIColorFromMmbz:tempString]];
			return theData;
			break;
		case TDX_JJDQSGCX:
		case TDX_LCDQSGCX:
			[theData addObject:[NSColor redColor]];
			return theData;
			break;
		case TDX_LCWTCX:
		case TDX_LCLSWTCX:
		case TDX_LCCJCX:
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_KFSJJ_MMBZ];//买卖标志
			[theData addObject:[self GetUIColorFromMmbz:tempString]];
			return theData;
			break;
		case TDX_JJWT:
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_KFSJJ_MMBZ];//买卖标志
			[theData addObject:tempString];
			[theData addObject:[self GetUIColorFromMmbz:tempString]];
			return theData;
			break;
		case TDX_GFBD_HK:
			//@"存／取",@"交收日期",@"交易日期",@"证券代码",@"证券名称",@"证券数量"
			break;
		case TDX_ZJLS_HK://@"流水号",@"申请日期",@"业务名称",@"币种",@"金额",@"证券帐号",@"状态说明"
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_JE];			//金额
			float jyje=[tempString floatValue];
			[theData addObject:[self GetUIColorFromfdyk:jyje]];
			return theData;
			break;
		case TDX_IPOLB_HK://@"首次公开募股号",@"证券代码",@"证券名称",@"内部募股截止日期",@"申请截止日期",@"上市日期"
			break;
		case TDX_IPOPH_HK://@"证券代码",@"申请编号",@"申请类型",@"申请费用",@"申请股数",@"金额总数",
			//@"中签数量",@"申请状况"
			break;
		case TDX_ZZCX:
			tempString = [self getFieldData:nRow fieldFlag:TDX_ID_BZ];
			[theData addObject:[self GetUIColorFromBZ:[tempString intValue]]];
			return theData;
			break;

		default:
			break;
	}
	[theData addObject:COLOR_GRID_COMMONCOLOR];
	return theData;
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

#pragma mark 解密解压

-(NSString * )getDecrypt:(NSMutableData *) theData BodyFlag:(int)flag {
	int _length = [theData length]-flag ;
	unsigned char temp2char[_length*2];
	memset(temp2char,0,_length*2);
	memcpy(temp2char, [theData bytes]+flag, _length);
	unsigned char * pbySrc = temp2char;
	_length = (_length+23)/24 * 24;
	newDecrypt(pbySrc, _length);
	if(bcompressed==0 && rawlen>0 && rawlen<_length)
		pbySrc[rawlen]='\0';
	NSString * theString = [[NSString alloc] initWithCString:(char *)pbySrc encoding:CFStringConvertEncodingToNSStringEncoding(kCFStringEncodingGB_18030_2000)];
	return theString;
}

-(NSString *) getDepress:(NSMutableData *)theData  BodyFlag:(int)flag RawLength:(int) rawLen {
	int _length = [theData length];
	
	unsigned char rawChar[rawLen+1024];
	unsigned long  getLength = _length-flag;
	unsigned char  getChar[getLength];
	unsigned long  rawLength=rawLen+1024  ;
	
	memcpy(getChar, [theData bytes]+flag, getLength);
	httpgzdecompress(getChar, getLength, rawChar, &rawLength);
	rawChar[rawLen] = '\0';
	NSString * theString = [[NSString alloc] initWithCString:(char *)rawChar encoding:CFStringConvertEncodingToNSStringEncoding(kCFStringEncodingGB_18030_2000)] ;
	return theString;
}

-(BOOL)IsTimeOut
{
	if(bsucflag==NO && [psErrorSign isEqualToString:@"T"] && [psErrorNum isEqualToString:@"-100"])
		return YES;
	if(bsucflag==NO && [psErrorSign isEqualToString:@"R"] && [psErrorNum isEqualToString:@"-101"])
		return YES;
	if(bsucflag==NO && [psErrorSign isEqualToString:@"R"] && [psErrorNum isEqualToString:@"-102"])
		return YES;
	if(bsucflag==NO && [psErrorSign isEqualToString:@"R"] && [psErrorNum isEqualToString:@"-103"])
		return YES;
	if(bsucflag==NO && [psErrorSign isEqualToString:@"F"] && [psErrorNum isEqualToString:@"423"])
		return YES;
	return NO;
}

-(BOOL)IsTimeOut2
{
	if(bsucflag==NO && [psErrorSign isEqualToString:@"T"] && [psErrorNum isEqualToString:@"-100"])
		return YES;
	return NO;
}

-(void)generror
{
	[psErrorSign release];
	psErrorSign=[[NSString alloc] initWithString:@"S"];
	[psErrorNum release];
	psErrorNum=[[NSString alloc] initWithString:@"-104"];
	[psErrorData release];
	psErrorData=[[NSString alloc] initWithString:@"应答包处理失败"];
}
@end
