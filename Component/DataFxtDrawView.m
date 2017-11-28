//
//  DataFxtDrawView.m
//  IpadForTDX
//
//  Created by tdx on 11-5-11.
//  Copyright 2011 武汉. All rights reserved.
//

#import "DataFxtDrawView.h"
#import "DataFxtComponent.h"
#define lightPurpleColor colorWithRed:1.0f green:0.0f blue:1.0f alpha:1

#define equfz(x,y) (fabsf(x-y)<0.000001)
#define SAR_LONG	0
#define SAR_SHORT	1

@implementation DataFxtDrawView

@synthesize m_pparent,dataFlag;

- (id)initWithFrame:(NSRect)frame {
    
    self = [super initWithFrame:frame];
    if (self) {

		dataFlag = NO;
    }
    return self;
}

-(void) setFrame:(NSRect)aRect{
	[super setFrame:aRect];
}

-(void)drawTheView{
	[self setNeedsDisplay:YES];
}



-(void) drawRect:(NSRect)rect{
	
	if (dataFlag) {
		CGContextRef context = [[NSGraphicsContext currentContext] graphicsPort];

		[self drawKLine:context];
		
		//画指标
		[self drawVol:context];
		[self drawZb:context];	
	}
}


-(void) drawKLine:(CGContextRef)context
{
}

-(float)getYPos:(float)_value secNum:(int)secNum{
	
	float nRet;
	DataFxtComponent * theParent = m_pparent;
	if (secNum > 0 ) 
	{
		nRet = theParent.kLineRect.origin.y + theParent.kLineRect.size.height - ((_value - theParent.m_MinPrice) * theParent.m_PricePerUnit);
	}
	else
	{
		nRet = (_value / theParent.m_MaxVol) * theParent.m_fPerUnitHeight*2.0f;
		
	}
	return nRet;
	
}

-(float)getZBYPos:(float)_value secNum:(int)secNum{
	
	float nRet;
	DataFxtComponent * theParent = m_pparent;
	if(secNum == 1)
	{
		if (_value>0)
		{
			nRet = theParent.m_fPerUnitHeight + (_value / (theParent.m_MaxZb- theParent.m_MinZb)) * 2.0f*theParent.m_fPerUnitHeight;
		}
		else
		{
			nRet = theParent.m_fPerUnitHeight - ABSOLUTE_VALUE( (_value / (theParent.m_MaxZb- theParent.m_MinZb)) * 2.0f*theParent.m_fPerUnitHeight);
		}
	}
	else if(secNum == 2)
	{
		nRet = ((_value - theParent.m_MinZb) / (theParent.m_MaxZb-theParent.m_MinZb)) * 2.0f*theParent.m_fPerUnitHeight;
	}
	else {
		nRet = 0;
	}

	
	return nRet;
}





-(void)drawVol:(CGContextRef)context
{
	
}

-(void) drawZb:(CGContextRef)context
{
}

-(void) drawBARLine:(CGContextRef)context
{
}

-(CGContextRef)getTheViewContext{
  return m_context; 
}


- (void)dealloc {
	[m_pparent release];
    [super dealloc];
}


@end
