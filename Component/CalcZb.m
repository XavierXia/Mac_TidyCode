//
//  CalcZb.m
//  tdxiphone
//
//  Created by tdx on 11-4-15.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "CalcZb.h"
@implementation CalcZb
@synthesize m_nDataNum;

-(id)init
{
	self = [super init];
	if(self)
	{
		m_nDataNum=0;
	}
	return self;
}

-(void)dealloc
{
	[super dealloc];
}

-(void)SET_NULL:(float*)buf From:(short)from Num:(short)num
{
	buf=buf+from;
	num=MIN(num,m_nDataNum);
	for(from=0;from<num;from++)
	{
		*buf=MEANLESS_DATA;
		buf++;
	}
}

-(void)SMA:(NSMutableArray*)buffer In:(short)n Parama:(short)_para
{
	short i,j;
	float f;
	float p1,p2;
	short para_1=(short)(_para-1);
	float f_para=(float)_para;
	if(n<=0 || _para>n)
		return;
	if(_para<1)
		return;
	short p1Index=n-1;
	short p2Index=0;
	for(i=(short)(n-1);i>=para_1;i--)
	{
		f=0.0f;
		j=(short)(i-para_1);
		p2Index=j;
        if(p2Index<[buffer count])
            p2=[[buffer objectAtIndex:p2Index] floatValue];
		for(;j<=i;j++)
		{
			if(p2 != MEANLESS_DATA)
				f+=p2;
			p2Index++;
			p2Index=MIN(p2Index,n-1);
            if(p2Index<[buffer  count])
                p2=[[buffer objectAtIndex:p2Index] floatValue];
		}
		p1=f/f_para;
		[buffer replaceObjectAtIndex:p1Index withObject:[NSString stringWithFormat:@"%f",p1]];
		p1Index--;
		p1Index=MAX(p1Index,0);
	}
	
	for(;i>=0 && [buffer count];i--)
	{
		f=0.0f;
		j=0;
		p2Index=0;
		p2=[[buffer objectAtIndex:p2Index] floatValue];
		for(;j<=i;j++)
		{
			if(p2!=MEANLESS_DATA)
				f+=p2;
			p2Index++;
			p2Index=MIN(p2Index,n-1);
            if(p2Index<[buffer count])
                p2=[[buffer objectAtIndex:p2Index] floatValue];
		}
		p1=f/(float)(i+1);
        if(p1Index<[buffer count])
            [buffer replaceObjectAtIndex:p1Index withObject:[NSString stringWithFormat:@"%f",p1]];
		p1Index--;
		p1Index=MAX(p1Index,0);
	}
}

-(void)QLMEMA:(NSMutableArray *)buffer In:(short)n Parama:(short)_para
{

}



-(void)REF:(NSMutableArray *)fOUT In:(NSMutableArray *)INa Parama:(short)_para
{
	if(_para>=0&&_para<m_nDataNum)
	{
		for(int i=0;i<m_nDataNum-_para && i<[INa count] && (_para+i)<[fOUT count];i++)
			[fOUT replaceObjectAtIndex:_para+i withObject:[INa objectAtIndex:i]];
	}
}

-(void)SUM:(NSMutableArray *)fOUT In:(NSMutableArray *)INa Parama:(short)_para
{
	short i=0,j=0;
	_para=_para>0?MIN(m_nDataNum,_para):m_nDataNum;
	i=[self GetMeanlessNum1:INa DataNum:m_nDataNum];
	float sum=0.0f;
	for(;i<m_nDataNum&&j<_para && i<[INa count] && i<[fOUT count];j++,i++)
	{
		sum+=[[INa objectAtIndex:i] floatValue];
		[fOUT replaceObjectAtIndex:i withObject:[NSString stringWithFormat:@"%f",sum]];
	}
	for(;i<m_nDataNum && i<[INa  count] && i<[fOUT count];i++)
	{
		sum+=([[INa objectAtIndex:i] floatValue]-[[INa objectAtIndex:i-_para] floatValue]);
		[fOUT replaceObjectAtIndex:i withObject:[NSString stringWithFormat:@"%f",sum]];
	}
}

-(void)SUB:(float *)buf1 Buf:(float *)buf2 N:(short)n Result:(float *)result
{
	short i;
	for(i=0;i<n;i++)
		result[i]=buf1[i]-buf2[i];
}

-(void)EMA:(NSMutableArray *)buffer In:(short)n Parama:(short)_para
{
	if(_para<1)
		return;
	short p1Index=0,p2Index=1;
	float p1,p2;
	for(short i=1;i<n && p1Index<[buffer count] && p2Index<[buffer count];i++,p1Index++,p2Index++)
	{
		p1=[[buffer objectAtIndex:p1Index] floatValue];
		p2=[[buffer objectAtIndex:p2Index] floatValue];
		p2=(p2+(_para-1)*p1)/_para;
		[buffer replaceObjectAtIndex:p2Index withObject:[NSString stringWithFormat:@"%f",p2]];
	}
}

-(void)EXPMEMA:(NSMutableArray *)buffer In:(short)n Parama:(short)_para
{
	if(_para<1)
		return;
	[self SMA:buffer In:MIN(n,_para) Parama:_para];
	short p1Index=_para-1,p2Index=_para;
	float p1,p2;
	for(short i=_para;i<n && p1Index<[buffer count] && p2Index<[buffer count];i++,p1Index++,p2Index++)
	{
		p1=[[buffer objectAtIndex:p1Index] floatValue];
		p2=[[buffer objectAtIndex:p2Index] floatValue];
		p2=(2.0f*p2+(_para-1)*p1)/(_para+1);
		[buffer replaceObjectAtIndex:p2Index withObject:[NSString stringWithFormat:@"%f",p2]];
	}
}

-(void)EXPMA:(NSMutableArray *)fOUT In:(NSMutableArray*)INa Parama:(short)_para
{
	short j=[self GetMeanlessNum1:fOUT DataNum:m_nDataNum];
	short i=j,num=_para;
	if(num<0||num+i>m_nDataNum)
		return;
    if(i<[fOUT count] && i<[INa count])
        [fOUT replaceObjectAtIndex:i withObject:[INa objectAtIndex:i]];
	float foutEx,fINa,fout;
	for(++i;i<m_nDataNum && i<[INa count] && i<[fOUT count];i++)
	{
		foutEx=[[fOUT objectAtIndex:i-1] floatValue];
		fINa=[[INa objectAtIndex:i] floatValue];
		fout=(2.0f*fINa+(float)(num-1)*foutEx/(float)(num+1));
		[fOUT replaceObjectAtIndex:i withObject:[NSString stringWithFormat:@"%f",fout]];
	}
		
}

-(void)LOW_HIGH:(NSMutableArray *)indatap Current:(short)current N:(short)n theLow:(float *)theLow theHigh:(float *)theHigh
{
	short i=MAX(0,current-n+1);
    if(i>=[indatap count])
        return;
	Analyse_Unit1* tempFxt=[indatap objectAtIndex:i];
	*theHigh = tempFxt.highp;
	*theLow = tempFxt.lowp;
	for(++i;i<=current;i++)
	{
		if(tempFxt.highp>*theHigh)
			*theHigh=tempFxt.highp;
		else if(tempFxt.lowp<*theLow)
			*theLow=tempFxt.lowp;
			
	}
	
}

-(short)GetMeanlessNum1:(NSArray*)fpData DataNum:(short)nDataNum
{
	short i=0;
	for(;i<nDataNum && i<[fpData count];i++)
	{
		if(MEANLESS_DATA!=[[fpData objectAtIndex:i] floatValue])
			break;
	}
	return i;
}

-(void)HHV:(NSMutableArray*)fOUT In:(NSMutableArray*)INa Parama:(short)_para
{
	short period=_para,nMax=0,i,j=2;
	period=period<=0?m_nDataNum:period;
	nMax=[self GetMeanlessNum1:INa DataNum:m_nDataNum];
	
	for(i=(short)(nMax+1);i<m_nDataNum&&j<period && i<[INa count] && nMax<[INa count];i++,j++)
	{
		if([[INa objectAtIndex:i] floatValue]>=[[INa objectAtIndex:nMax] floatValue])
			nMax=i;
		if(period==m_nDataNum && i<[fOUT count])
			[fOUT replaceObjectAtIndex:i withObject:[INa objectAtIndex:nMax]];
	}
	for(;i<m_nDataNum && i<[INa count] && nMax<[INa count];i++)
	{
		if(i-nMax<period)
			nMax=[[INa objectAtIndex:i] floatValue]<[[INa objectAtIndex:nMax] floatValue]?nMax:i;
		else
		{
			for(j=(short)((nMax=(short)(i-period+1))+1) && j<[INa count] && nMax<[INa count];j<=i;j++)
				nMax=[[INa objectAtIndex:j] floatValue]<[[INa objectAtIndex:nMax] floatValue]?nMax:j;
		}
        if(i<[fOUT count])
            [fOUT replaceObjectAtIndex:i withObject:[INa objectAtIndex:nMax]];

	}
}

-(void)LLV:(NSMutableArray *)fOUT In:(NSMutableArray *)INa Parama:(short)_para
{
	short period=_para,nMin=0,i,j=2;
	period=period<=0?m_nDataNum:period;
	nMin=[self GetMeanlessNum1:INa DataNum:m_nDataNum];
	for(i=(short)(nMin+1);i<m_nDataNum&&j<period && i<[INa count] && nMin<[INa count];i++,j++)
	{
		if([[INa objectAtIndex:i] floatValue]<=[[INa objectAtIndex:nMin] floatValue])
			nMin=i;
		if(period==m_nDataNum && i<[fOUT count])
			[fOUT replaceObjectAtIndex:i withObject:[INa objectAtIndex:nMin]];
	}
	for(;i<m_nDataNum && i<[INa count];i++)
	{
		if(i-nMin<period)
			nMin=[[INa objectAtIndex:i] floatValue]>[[INa objectAtIndex:nMin] floatValue]?nMin:i;
		else
			for(j=(short)((nMin=(short)(i-period+1))+1);j<=i;j++)
				nMin=[[INa objectAtIndex:j] floatValue]>[[INa objectAtIndex:nMin] floatValue]?nMin:j;
        if(i<[fOUT count])
            [fOUT replaceObjectAtIndex:i withObject:[INa objectAtIndex:nMin]];
	}
}



-(short) GetMeanlessNum:(float*)fpData DataNum:(short)nDataNum
{
	short i=0;
	for(;i<nDataNum;i++)
	{
		if(MEANLESS_DATA!=fpData[i])
			break;
	}
	return(i);
}

-(void)AVEDEV:(NSMutableArray *)fOUT In:(NSMutableArray *)INa Parama:(short)_para
{
	short num=(short)_para,i=0,j=0,k=0;
	i=[self GetMeanlessNum1:INa DataNum:m_nDataNum];
	if(num<=0||num*i>m_nDataNum)
		return;
	float E=0.0f,DEV=0.0f;
	for(;i<m_nDataNum&&j<num && i<[INa count];i++,j++)
		E+=([[INa objectAtIndex:i] floatValue]/(float)num);
	if(j==num)
	{
		for(;k<num && (i-k-1)<[INa count];k++)
			DEV+=(float)fabsf([[INa objectAtIndex:(i-k-1)] floatValue]-E);
        if((i-1)<[fOUT count])
           [fOUT replaceObjectAtIndex:(i-1) withObject:[NSString stringWithFormat:@"%f",DEV/(float)num]];
	}
	for(;i<m_nDataNum && i<[INa count];i++)
	{
		E+=(([[INa objectAtIndex:i] floatValue]-[[INa objectAtIndex:(i-num)] floatValue])/(float)num);
		for(DEV=0.0f,k=0;k<num && (i-k)<[INa  count];k++)
			DEV+=(float)fabsf([[INa objectAtIndex:(i-k)] floatValue]-E);
        if(i<[fOUT count])
            [fOUT replaceObjectAtIndex:i withObject:[NSString stringWithFormat:@"%f",DEV/(float)num]];
	}
}

-(void)COUNT:(NSMutableArray *)fOUT In:(NSMutableArray *)INa Parama:(short)_para
{
	short period=(short)_para,days=0,i=0,j=0;
	period=period<=0?m_nDataNum:period;
	i=[self GetMeanlessNum1:INa DataNum:m_nDataNum];
	for(;i<m_nDataNum&&j<period && i<[INa count];i++,j++)
	{
		if([[INa objectAtIndex:i] floatValue]>0.000001)
			days=(short)(days+1);
        if(i<[fOUT count])
            [fOUT replaceObjectAtIndex:i withObject:[NSString stringWithFormat:@"%d",days]];
	}
	for(;i<m_nDataNum && i<[INa count];i++)
	{
		if([[INa objectAtIndex:(i-period)] floatValue]>0.0001f&&days>0)
			days--;
		if([[INa objectAtIndex:i]floatValue] >0.000001f)
			days=(short)(days+1);
        if(i<[fOUT count])
            [fOUT replaceObjectAtIndex:i withObject:[NSString stringWithFormat:@"%d",days]];
	}
}

-(void)STD:(NSMutableArray*)fOUT In:(NSMutableArray*)INa Parama:(short)_para
{
	short num=_para,i=0,j=0,k=0;
	for(;i<m_nDataNum && i<[INa count];i++)
	{
		if([[INa objectAtIndex:i] floatValue]!=MEANLESS_DATA)
			break;
	}
	if(num<=0 || num+i>m_nDataNum)
		return;
	float E=0.0f,DEV=0.0f;
	for(;i<m_nDataNum&&j<num && i<[INa count];i++,j++)
		E+=[[INa objectAtIndex:i] floatValue]/(float)num;
	if(j==num)
	{
		for(i--;k<num && (i-k)<[INa count];k++)
			DEV+=([[INa objectAtIndex:(i-k)] floatValue]-E)*([[INa objectAtIndex:(i-k)] floatValue]-E);
        if((i+1)<[fOUT count])
            [fOUT replaceObjectAtIndex:i++ withObject:[NSString stringWithFormat:@"%f",sqrtf(DEV/(float)num)]];
	}
	for(;i<m_nDataNum && i<[INa count];i++)
	{
		E+=([[INa objectAtIndex:i] floatValue]-[[INa objectAtIndex:i-num] floatValue])/(float)num;
		for(DEV=0,k=0;k<num && (i-k)<[INa count];k++)
			DEV+=([[INa objectAtIndex:i-k] floatValue]-E)*([[INa objectAtIndex:i-k] floatValue]-E);
        if(i<[fOUT count])
            [fOUT replaceObjectAtIndex:i withObject:[NSString stringWithFormat:@"%f",sqrtf(DEV/(float)num)]];
	}
}

-(void) Dma:(NSMutableArray*)fOUT In:(NSMutableArray*)INa Parama:(NSMutableArray*)INb
{
	short i=0;
	for(;i<m_nDataNum && i<[INa count] && i<[INb count];i++)
	{
		if(fabsf([[INa objectAtIndex:i] floatValue]-MEANLESS_DATA)>0.00001)
			break;
		if(fabsf([[INb objectAtIndex:i] floatValue]-MEANLESS_DATA)>0.00001)
			break;
		for(++i;i<m_nDataNum && i<[INa count] && i<[fOUT count] && i<[INb count];i++)
		{
			float fINa=[[INa objectAtIndex:i]floatValue];
			float foutEx=[[fOUT objectAtIndex:i-1] floatValue];
			float fINb=[[INb objectAtIndex:i] floatValue];
			float fout=(fINb-1.0f<0.00001)?fINb*fINa+(1-fINb)*foutEx:fINa;
			[fOUT replaceObjectAtIndex:i withObject:[NSString stringWithFormat:@"%f",fout]];
		}
	}
}
@end



