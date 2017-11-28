//
//  DataFxtComponent.m
//  tdxiphone
//
//  Created by 魏 文敏 on 09-12-30.
//  Copyright 2009 武汉. All rights reserved.
//

#import "DataFxtComponent.h"
#define lightPurpleColor colorWithRed:1.0f green:0.0f blue:1.0f alpha:1
#define KGRIDCOLOR  colorWithRed:190/255.0f green:1.0f blue:1.0f alpha:1

#define BLANKHEIGHT 40
#define DETAILBLANKHEIGHT 20
#define RIGHTBLANKHEIGHT 50
#define LEFTBLANKHEIGHT 0
#define TEXTWIDTH 50
#define IMAGEWIDTH 40
#define BTN_WIDTH 40
#define DETAILVIEWWIDTH  140
#define DETAILVIEWHEIGHT 220


#define GREENCOLOR  [NSColor colorWithCalibratedRed:84/255.0f green:1.0f blue:1.0f alpha:1.0f]

#define DAY_TITLE_TAG 1
#define ZAF_TITLE_TAG 2
#define ZAD_TITLE_TAG 3
#define OPEN_TITLE_TAG 4
#define MAX_TITLE_TAG 5
#define VOL_TITLE_TAG 6
#define CLOSE_TITLE_TAG 7
#define MIN_TITLE_TAG 8
#define AMOUNT_TITLE_TAG 9

#define FXT_LEFT 0
#define FXT_RIGHT 1
#define RELEASE(object) if(object != nil) {[object release];object=nil;}

#define MAIN_FONT_SIZE 15


#define equfz(x,y) (fabsf(x-y)<0.000001)
#define SAR_LONG	0
#define SAR_SHORT	1

@implementation DataFxtComponent
@synthesize currInfo,fxtCross,m_AnalyseData,m_ZbData,axisArray,periodArray,zbArray,drawNumArray,m_DrawNum,m_LeftNum,m_ReadNum,m_PerReadNum;
@synthesize periodIndex,zbIndex,drawIndex,cursor,dPer,m_dWidth,m_dDistance,dataFlag,moveFlag;
@synthesize m_MaxPrice,m_MinPrice,m_MaxVol,m_MaxZb,m_MinZb,m_PricePerUnit,m_MaxIndex,m_MinIndex;
@synthesize viewWidth,viewHeight,perSecWidth,perSecHeight,myDelegate,isAllData,fqFlag;
@synthesize titleHeight,dateHeight,btnHeight,titleFont,btnFont,detailDelegate,myActionDelegate,moreFxtFlag;
@synthesize myCalcZb,positionArray,kLineRect,volRect,zbRect,InfoRect,m_fPerUnitHeight,theOffset,m_nZoomfreshConunt;

#pragma mark 页面显示相关
- (id)initWithFrame:(NSRect)aRect theData:(EGetData *)_eGetData titleHeight:(float)_titleHeight dateHeight:(float)_dateHeight btnHeight:(float)_btnHeight titleFont:(float)_titleFont btnFont:(float)_btnFont{
	self = [super initWithFrame:aRect ];
	if(self != nil){
		eGetData = _eGetData;
		originalTransform = CGAffineTransformIdentity;
		aniFlag = NO;
	
        self.dataFlag = NO;
		self.moveFlag = NO;
		m_nShowStyle = FXT_LEFT;
		changeZb = NO;
		freshFlag = NO;
		moreFxtFlag = NO;
		isAllData = NO;
		isZoom = 0;
		fqFlag = 0;
		

        titleHeight= _titleHeight;
		dateHeight = _dateHeight;
		btnHeight = _btnHeight;
		titleFont = _titleFont;
		btnFont = _btnFont;
		
		
		drawView = [[DataFxtDrawView alloc] initWithFrame:NSMakeRect(0, 0, aRect.size.width, aRect.size.height)];
		drawView.m_pparent = self;
		
        [self addSubview:drawView];
		
		
		viewWidth = aRect.size.width;
		viewHeight = aRect.size.height;
		perSecHeight = (viewHeight - 5*BLANKHEIGHT-DETAILBLANKHEIGHT) /8.0f;
		perSecWidth = viewWidth  / 3.0f;
		
		drawWidth = aRect.size.width - RIGHTBLANKHEIGHT;
		
		m_fPerUnitHeight = (aRect.size.height - titleHeight*4.0f - dateHeight) /10.0f;

        kLineRect= CGRectMake(0.0f, aRect.size.height - m_fPerUnitHeight*6-titleHeight*2, drawWidth*1.0f, m_fPerUnitHeight*6.0f);
		volRect = CGRectMake(0.0f, dateHeight+m_fPerUnitHeight*2.0f+titleHeight, drawWidth, m_fPerUnitHeight*2.0f+titleHeight);
		zbRect = CGRectMake(0.0f, dateHeight, drawWidth, m_fPerUnitHeight*2.0f+titleHeight);
		
		
		
		leftDetailRect = NSMakeRect(kLineRect.origin.x, kLineRect.origin.y+kLineRect.size.height-DETAILVIEWHEIGHT, DETAILVIEWWIDTH, DETAILVIEWHEIGHT);
		rightDetailRect = NSMakeRect(kLineRect.origin.x+kLineRect.size.width-DETAILVIEWWIDTH, kLineRect.origin.y+kLineRect.size.height-DETAILVIEWHEIGHT, DETAILVIEWWIDTH, DETAILVIEWHEIGHT);
		
		
		fxtCross = [[CrossView alloc] initWithFrame:NSMakeRect(0, 0, aRect.size.width, aRect.size.height) PerRowHeight:perSecHeight];
		//crossView.alpha = 0;
		fxtCross.titleHeight = titleHeight;
		fxtCross.topRect = kLineRect;
		fxtCross.midRect = volRect;
		fxtCross.btmRect = zbRect;
		fxtCross.typeFlag  = 2;
		[self addSubview:fxtCross];
		
		detailView = [[DataFxtDetailComponent alloc]initWithFrame:leftDetailRect];

        
		//初始化参数
		m_PerReadNum = 280;
		m_ReadNum = 0;
		periodIndex= 4;
		zbIndex = 0;
		drawIndex = 2;
		myCalcZb = [[CalcZb alloc]init];
		m_AnalyseData = [[NSMutableArray alloc] init];
		m_ZbData = [[NSMutableArray alloc] init];
		positionArray=[[NSMutableArray alloc]init];
		axisArray = [[NSMutableArray alloc] init];

        periodArray = [[NSMutableArray alloc] initWithObjects:@"5分钟",@"15分钟",@"30分钟",@"60分钟",@"日线",@"周线",@"月线",nil];
		zbArray = [[NSMutableArray alloc] initWithObjects:@"MACD(平滑异同平均)",@"KDJ(经典版KDJ)",@"RSI(相对强弱指标)",@"BIAS(乖离率)",@"DMA(趋向指标)",@"OBV(累积能量线)",@"ROC(变动率指标)",@"MTM(动量线)",
				   @"CR(带状能量线)",@"DMI(趋向指标)",@"BRAR(情绪指标)",@"VR(成交量变动率)",@"TRIX(三重指数平均线)",@"EMV(简易波动指标)",@"WR(威廉指标)",@"CCI(商品路径指标)",@"PSY(心理线)",@"DPO(区间震荡线)",@"BOLL(布林线)",@"ASI(振动升降指标)",@"SAR(抛物线指标)",nil];
		drawNumArray = [[NSMutableArray alloc] initWithObjects:@"5",@"15",@"50",@"60",nil] ;
		
		m_nOffset = 0;
		m_nStartPosX = 0;
		m_nDirection = 0;
		m_nLeftPos = 0;
		m_nZoomfreshConunt = 0;
		titleArray = [[NSMutableArray alloc] initWithCapacity:4];
		[self layoutLabel];
		pickIndex=0;
		nSelectIndex=0;

        
	}	
	
	return self;
}

-(void) setShowStyle:(short)_showStyle
{
	m_nShowStyle = _showStyle;
	
	if (m_nShowStyle == FXT_LEFT)
	{
		kLineRect = CGRectMake(0.0f, 2.0f*titleHeight, drawWidth, m_fPerUnitHeight*6.0f);
		volRect = CGRectMake(0.0f, m_fPerUnitHeight*6.0f + 2.0f*titleHeight, drawWidth, m_fPerUnitHeight*2.0f+titleHeight);
		zbRect = CGRectMake(0.0f, titleHeight*3.0f+m_fPerUnitHeight*8.0f, drawWidth, m_fPerUnitHeight*2.0f+titleHeight);
		InfoRect = CGRectMake(0.0f,1.0f, self.bounds.size.width - 2.0f*btnHeight, titleHeight);
	}
	else if(m_nShowStyle == FXT_RIGHT)
	{
		kLineRect = CGRectMake(self.bounds.size.width - drawWidth, 2.0f*titleHeight, drawWidth-2, m_fPerUnitHeight*6.0f);
		volRect = CGRectMake(self.bounds.size.width - drawWidth, m_fPerUnitHeight*6.0f + 2.0f*titleHeight, drawWidth-2, m_fPerUnitHeight*2.0f+titleHeight);
		zbRect = CGRectMake(self.bounds.size.width- drawWidth, titleHeight*3.0f+m_fPerUnitHeight*8.0f, drawWidth-2, m_fPerUnitHeight*2.0f+titleHeight);
		InfoRect = CGRectMake(self.bounds.size.width - drawWidth,1.0f, self.bounds.size.width - 2.0f*btnHeight, dateHeight+5.0f);
	}

    fxtCross.topRect = kLineRect;
	fxtCross.midRect = volRect;
	fxtCross.btmRect = zbRect;

}

-(void) setFrame:(NSRect)aRect{
	
	[super setFrame:aRect];

    viewWidth = aRect.size.width;
	viewHeight = aRect.size.height;
	perSecHeight = (viewHeight - BLANKHEIGHT*5-DETAILBLANKHEIGHT) /8.0f;
	perSecWidth = viewWidth  / 3.0f;	
	
    drawWidth = aRect.size.width - RIGHTBLANKHEIGHT;
	
	m_fPerUnitHeight = (aRect.size.height - titleHeight*4.0f - dateHeight) /10.0f;

    kLineRect= CGRectMake(0.0f, aRect.size.height - m_fPerUnitHeight*6-titleHeight*2, drawWidth*1.0f, m_fPerUnitHeight*6.0f);
	volRect = CGRectMake(0.0f, dateHeight+m_fPerUnitHeight*2.0f+titleHeight, drawWidth, m_fPerUnitHeight*2.0f+titleHeight);
	zbRect = CGRectMake(0.0f, dateHeight, drawWidth, m_fPerUnitHeight*2.0f+titleHeight);
	
	
    leftDetailRect = NSMakeRect(kLineRect.origin.x, kLineRect.origin.y+kLineRect.size.height-DETAILVIEWHEIGHT, DETAILVIEWWIDTH, DETAILVIEWHEIGHT);
	rightDetailRect = NSMakeRect(kLineRect.origin.x+kLineRect.size.width-DETAILVIEWWIDTH, kLineRect.origin.y+kLineRect.size.height-DETAILVIEWHEIGHT, DETAILVIEWWIDTH, DETAILVIEWHEIGHT);
	
	
	
	
	[nameField setFrame:NSMakeRect(0, viewHeight-2*titleHeight+titleHeight/4, 120, titleHeight+titleHeight/2)];
	[pMA5 setFrame:NSMakeRect([nameField frame].origin.x+[nameField frame].size.width, viewHeight-2*titleHeight+titleHeight/4, 100, titleHeight+titleHeight/2)];
	[pMA10 setFrame:NSMakeRect([pMA5 frame].origin.x+[pMA5 frame].size.width, viewHeight-2*titleHeight+titleHeight/4, 100, titleHeight+titleHeight/2)];
	[pMA20 setFrame:NSMakeRect(0, viewHeight-3*titleHeight-6*m_fPerUnitHeight, 100, titleHeight)];
	[vol1 setFrame:NSMakeRect([nameField frame].origin.x+[nameField frame].size.width, viewHeight-3*titleHeight-6*m_fPerUnitHeight, 100, titleHeight)];
	[vol2 setFrame:NSMakeRect([vol1 frame].origin.x+[vol1 frame].size.width, viewHeight-3*titleHeight-6*m_fPerUnitHeight, 100, titleHeight)];
	[vol3 setFrame:NSMakeRect([vol2 frame].origin.x+[vol2 frame].size.width, viewHeight-2*titleHeight+titleHeight/4, 100, titleHeight)];
	[zb1 setFrame:NSMakeRect(0, titleHeight+2*m_fPerUnitHeight, 100, titleHeight)];
	[zb2 setFrame:NSMakeRect([zb1 frame].origin.x+[zb1 frame].size.width, titleHeight+2*m_fPerUnitHeight, 100, titleHeight)];
	[zb3 setFrame:NSMakeRect([zb2 frame].origin.x+[zb2 frame].size.width, titleHeight+2*m_fPerUnitHeight, 100, titleHeight)];
	[zb4 setFrame:NSMakeRect([zb3 frame].origin.x+[zb3 frame].size.width, titleHeight+2*m_fPerUnitHeight, 100, titleHeight)];
	
	
	for (int i =0 ; i < [axisArray count]; i++)
	{
		NSTextField * tempLabel = [axisArray objectAtIndex:i];
		
		if(i < 6)
		{
			[tempLabel setFrame:NSMakeRect(drawWidth+2.0f,kLineRect.origin.y+kLineRect.size.height- i*m_fPerUnitHeight-10.0f, RIGHTBLANKHEIGHT-3, 20.0f)];
		}	
		else if((i >=6) && (i<8))
		{
			[tempLabel setFrame:NSMakeRect(drawWidth+2.0f,volRect.origin.y+volRect.size.height-titleHeight- (i-6)*m_fPerUnitHeight-10.0f, RIGHTBLANKHEIGHT-3, 20.0f)];
		}
		else if(i==8)
		{
			[tempLabel setFrame:NSMakeRect(drawWidth+2.0f,volRect.origin.y+1, 40, 20.0f-2.0f)];
		}
		else
		{
			[tempLabel setFrame:NSMakeRect(drawWidth+2.0f,zbRect.origin.y+zbRect.size.height-titleHeight- (i-9)*m_fPerUnitHeight-10.0f, RIGHTBLANKHEIGHT-3, 20.0f)];
		}
	}	
	
	NSRect buttonFrame;
	buttonFrame.origin.x = zbRect.size.width - 100 ;
	buttonFrame.origin.y = dateHeight+2*m_fPerUnitHeight;
	buttonFrame.size.width = 100;
	buttonFrame.size.height = 20;
	[zbButton setFrame:buttonFrame];
	buttonFrame.origin.x = kLineRect.size.width - 100 ;
	buttonFrame.origin.y = viewHeight-2*titleHeight+titleHeight/4;
	buttonFrame.size.width = 100;
	buttonFrame.size.height = titleHeight+titleHeight/2;
	[zqButton setFrame:buttonFrame];
	
	buttonFrame.origin.x = volRect.size.width - 100 ;
	buttonFrame.origin.y =  dateHeight+titleHeight+4*m_fPerUnitHeight;
	buttonFrame.size.width = 100;
	buttonFrame.size.height = 20;
	[fqButton setFrame:buttonFrame];
	
	
	fxtCross.perRowHeight = perSecHeight;
	[fxtCross setFrame:NSMakeRect(0, 0, aRect.size.width, aRect.size.height)];
	fxtCross.topRect = kLineRect;
	fxtCross.midRect = volRect;
	fxtCross.btmRect = zbRect;

    [self calDataEx];
	[self calIt];
	
    [self setNeedsDisplay:YES];
	
}

-(void)DrawRect:(CGRect)rect Context:(CGContextRef)context
{
	CGContextMoveToPoint(context, rect.origin.x, rect.origin.y);
	CGContextAddLineToPoint(context, rect.origin.x+rect.size.width, rect.origin.y);
	CGContextMoveToPoint(context, rect.origin.x+rect.size.width, rect.origin.y+1.0f);
	CGContextAddLineToPoint(context, rect.origin.x+rect.size.width, rect.origin.y+rect.size.height);
	CGContextMoveToPoint(context, rect.origin.x+rect.size.width-1.0f, rect.origin.y+rect.size.height);
	CGContextAddLineToPoint(context, rect.origin.x, rect.origin.y+rect.size.height);
	CGContextMoveToPoint(context, rect.origin.x, rect.origin.y+rect.size.height-1.0f);
	CGContextAddLineToPoint(context, rect.origin.x, rect.origin.y+1.0f);
	CGContextStrokePath(context);
}



- (void)drawRect:(NSRect)rect
{

    CGContextRef context = [[NSGraphicsContext currentContext] graphicsPort];
	m_context = context;
	//画外框
	
    [[NSColor colorWithCalibratedRed:190/255.0f green:0.0f blue:0.0f alpha:1.0f] set];
	CGContextSetLineWidth(context, 1.0f);
	CGContextSetAllowsAntialiasing(context, FALSE);
	[self DrawRect:kLineRect Context:context];
	[self DrawRect:volRect Context:context];
	[self DrawRect:zbRect Context:context];
	if(m_nShowStyle==FXT_LEFT)
		[self DrawRect:CGRectMake(drawWidth+1.0f, volRect.origin.y ,  50.0f-5.0f, 20.0f) Context:context];
	else if(m_nShowStyle==FXT_RIGHT)
		[self DrawRect:CGRectMake(2.0f, volRect.origin.y + titleHeight +2* m_fPerUnitHeight-10.0f,  50.0f-5.0f, 12.0f) Context:context];

    CGContextMoveToPoint(context, 0, 1);
	CGContextAddLineToPoint(context, viewWidth, 1);
	
	CGContextMoveToPoint(context, viewWidth-1, 1);
	CGContextAddLineToPoint(context, viewWidth-1, viewHeight);
	
	CGContextStrokePath(context);
	
	CGFloat dash[] = {2.0f, 5.0f};
	//	
	CGContextSetLineDash(context, 0.0, dash, 1);
	for (int i=1; i<6; i++)
	{
		CGContextMoveToPoint(context, kLineRect.origin.x, kLineRect.origin.y+i*m_fPerUnitHeight);
		CGContextAddLineToPoint(context, kLineRect.origin.x+kLineRect.size.width-1.0f,  kLineRect.origin.y+i*m_fPerUnitHeight);
	}
	
	for (int i=0; i<3; i++)
	{
		CGContextMoveToPoint(context, volRect.origin.x, volRect.origin.y  + i*m_fPerUnitHeight);
		CGContextAddLineToPoint(context, volRect.origin.x+volRect.size.width-1.0f, volRect.origin.y  +i* m_fPerUnitHeight);
	}
	
	for (int i=0; i<3; i++)
	{
		CGContextMoveToPoint(context, zbRect.origin.x, zbRect.origin.y  + i*m_fPerUnitHeight);
		CGContextAddLineToPoint(context, zbRect.origin.x+zbRect.size.width-1.0f, zbRect.origin.y  +i* m_fPerUnitHeight);
	}
	CGContextStrokePath(context);
	
	//	
	CGContextSetLineDash(context, 0.0, dash, 0);
	CGContextSetAllowsAntialiasing(context, TRUE);
	if(dataFlag)
	{
		NSString * tempString;
		switch (periodIndex) {
			case 0:
				tempString = [NSString stringWithFormat:@"%@(5分钟)",currInfo.gpname];
				break;
			case 1:
				tempString = [NSString stringWithFormat:@"%@(15分钟)",currInfo.gpname];
				break;	
			case 2:
				tempString = [NSString stringWithFormat:@"%@(30分钟)",currInfo.gpname];
				break;
			case 3:
				tempString = [NSString stringWithFormat:@"%@(60分钟)",currInfo.gpname];
				break;
			case 4:
				tempString = [NSString stringWithFormat:@"%@(日线)",currInfo.gpname];
				break;
			case 5:
				tempString = [NSString stringWithFormat:@"%@(周线)",currInfo.gpname];
				break;	
			case 6:
				tempString = [NSString stringWithFormat:@"%@(月线)",currInfo.gpname];
				break;		
			default:
				break;
		}
		
		[zqButton selectItemAtIndex:periodIndex];
		[[nameField cell] setTitle:tempString];
		
		[zbButton selectItemAtIndex:zbIndex];
		
		

        [self drawKLine:context];

        //		//画指标
		[self drawVol:context];
		[self drawZb:context];	
		
		[self calVol];
		[self calZB];

        [self drawAxis];

        
		[self drawCaption];

        
		if (fxtCross.showFlag) {
			if (cursor< m_LeftNum) {
				return;
			}
			
			int tempInt = cursor - m_LeftNum;
			fxtCross.xPos = m_dWidth*0.5f + dPer*tempInt;
            if(cursor>=0 && cursor<[m_AnalyseData count])
            {
                Analyse_Unit * tempAna = [m_AnalyseData objectAtIndex:cursor];
                fxtCross.yPos = [self  getYPos:tempAna.closep secNum:1];
                
                [fxtCross refreshShow];
            }
			
		}
 	}	
}	

-(void) drawBARLine:(CGContextRef)context
{
	float yClose, yOpen, yHigh, yLow ,xPos;
	float off =  m_dWidth * 0.5;

    Analyse_Unit * tempAna;
	float ZbButtom = zbRect.origin.y;
	for (int i = 0; i < m_DrawNum && (i + m_LeftNum)<[m_AnalyseData count]; i++)
	{

        tempAna = [m_AnalyseData objectAtIndex:(i + m_LeftNum)];
		yClose = ZbButtom -[self  getZBYPos:tempAna.closep secNum:2];
		yOpen = ZbButtom -[self  getZBYPos:tempAna.openp secNum:2];
		yHigh = ZbButtom -[self  getZBYPos:tempAna.highp secNum:2];
		yLow = ZbButtom -[self  getZBYPos:tempAna.lowp secNum:2];
		if (tempAna.closep >tempAna.openp) 
		{

            
			xPos = zbRect.origin.x + m_dWidth * 0.5 + dPer * i;
			
			[[NSColor redColor] set];

            CGContextSetLineWidth(context, 1.0f);
			

            CGContextMoveToPoint(context, xPos,yClose);
			CGContextAddLineToPoint(context, xPos+off, yClose);
			CGContextMoveToPoint(context, xPos, yHigh);
			CGContextAddLineToPoint(context, xPos,  yLow);
			CGContextMoveToPoint(context, xPos, yOpen);
			CGContextAddLineToPoint(context, xPos-off,  yOpen);
			
			CGContextStrokePath(context);
		}
		else if(tempAna.closep < tempAna.openp)//阴线
		{

            [GREENCOLOR set];
			CGContextSetLineWidth(context, 1.0f);
			

            
			xPos = zbRect.origin.x + 0.5 * m_dWidth + dPer * i;
			

            CGContextMoveToPoint(context, xPos,yClose);
			CGContextAddLineToPoint(context, xPos+off, yClose);
			CGContextMoveToPoint(context, xPos, yHigh);
			CGContextAddLineToPoint(context, xPos,  yLow);
			CGContextMoveToPoint(context, xPos, yOpen);
			CGContextAddLineToPoint(context, xPos-off,  yOpen);
			CGContextStrokePath(context);
			
		}	
		else//平线
		{
			[[NSColor whiteColor] set];
			CGContextSetLineWidth(context, 1.0);
			

            xPos = zbRect.origin.x + 0.5 * m_dWidth + dPer * i;
			
			CGContextMoveToPoint(context, xPos,yClose);
			CGContextAddLineToPoint(context, xPos+off, yClose);
			CGContextMoveToPoint(context, xPos, yHigh);
			CGContextAddLineToPoint(context, xPos,  yLow);
			CGContextMoveToPoint(context, xPos, yOpen);
			CGContextAddLineToPoint(context, xPos-off,  yOpen);
			CGContextStrokePath(context);
		}
	}
}

-(void) drawKLine:(CGContextRef)context
{
	float yClose, yOpen, yHigh, yLow ,xPos;
	float off =  self.m_dWidth * 0.5;
	float x0,y0,x1,y1;
	Analyse_Unit * tempAna;

    
	for (int i = 0; i < self.m_DrawNum; i++) 
	{
		if ((i+m_LeftNum) >= [m_AnalyseData count] ) {
			return;
		}
		
		tempAna = [self.m_AnalyseData objectAtIndex:(i + self.m_LeftNum)];
		if (tempAna.closep >tempAna.openp) 
		{
			yClose = [self  getYPos:tempAna.closep secNum:1];
			yOpen = [self  getYPos:tempAna.openp secNum:1];
			yHigh = [self  getYPos:tempAna.highp secNum:1];
			yLow = [self  getYPos:tempAna.lowp secNum:1];
			
			xPos = self.kLineRect.origin.x + self.m_dWidth * 0.5 + self.dPer * i;
			

            [[NSColor redColor] set];
			CGContextSetLineWidth(context, 1.0f);
			
			CGContextAddRect(context, CGRectMake(xPos-off, yOpen, 2.0f * off, ABSOLUTE_VALUE(yClose - yOpen)));
			
			
			CGContextMoveToPoint(context, xPos, MAX_VALUE(yHigh,yClose));
			CGContextAddLineToPoint(context, xPos,  yClose);
			CGContextMoveToPoint(context, xPos, yOpen);
			CGContextAddLineToPoint(context, xPos,  MIN_VALUE(yLow,yOpen));
			
			CGContextStrokePath(context);
		}
		else if(tempAna.closep < tempAna.openp)//阴线
		{
	
            [GREENCOLOR set];
			CGContextSetLineWidth(context, 1.0f);
			
			yClose = [self  getYPos:tempAna.closep secNum:1];
			yOpen = [self  getYPos:tempAna.openp secNum:1];
			yHigh = [self  getYPos:tempAna.highp secNum:1];
			yLow = [self  getYPos:tempAna.lowp secNum:1];
			
			xPos = self.kLineRect.origin.x + 0.5 * self.m_dWidth + self.dPer * i;
			
			
			CGContextAddRect(context, CGRectMake(xPos-off, MIN_VALUE(yOpen,yClose), 2.0f * off,ABSOLUTE_VALUE(yClose - yOpen)));
			
			CGContextMoveToPoint(context, xPos, yLow);
			CGContextAddLineToPoint(context, xPos,  yHigh);
			
			CGContextStrokePath(context);
			CGContextFillPath(context);
			CGContextFillRect(context,CGRectMake(xPos-off, MIN_VALUE(yOpen,yClose), 2.0f * off,ABSOLUTE_VALUE(yClose - yOpen)));
			
		}	
		else//平线
		{
		
            [[NSColor whiteColor] set];
			CGContextSetLineWidth(context, 1.0);
			
			yClose = [self  getYPos:tempAna.closep secNum:1];
		
            yHigh = [self  getYPos:tempAna.highp secNum:1];
			yLow = [self  getYPos:tempAna.lowp secNum:1];
			xPos = self.kLineRect.origin.x + 0.5 * self.m_dWidth + self.dPer * i;
			
			CGContextMoveToPoint(context, xPos-off, yClose);
			CGContextAddLineToPoint(context,xPos+off,  yClose);
			CGContextMoveToPoint(context, xPos, yLow);
			CGContextAddLineToPoint(context,xPos ,   yHigh);
			CGContextStrokePath(context);
		}
	}
	
	//画均线
	//5日均线

    [[NSColor whiteColor] set];
	
    BOOL bisFirst = YES;
	
    for (int i = 0; i < m_DrawNum; i++)
	{

        if(i+m_LeftNum<5)
		{
			continue;
		}
        if((i + m_LeftNum)>=[m_AnalyseData count])
            continue;
		
		tempAna = [m_AnalyseData objectAtIndex:(i + m_LeftNum)];
		if(bisFirst)
		{
			x0 = kLineRect.origin.x + m_dWidth * 0.5 + dPer * i;
			y0 = [self  getYPos:tempAna.maFive secNum:1];
			bisFirst=NO;
			continue;
		}
		x1 = kLineRect.origin.x + m_dWidth * 0.5 + dPer * i;
		y1 = [self getYPos:tempAna.maFive secNum:1];
		if (y0 <= 0.1)
			[self  getYPos:tempAna.closep secNum:1];
		CGContextMoveToPoint(context, x0, y0);
		CGContextAddLineToPoint(context, x1, y1);
		CGContextStrokePath(context);
		
		x0 = x1;
		y0= y1;
		
		
	}	
	
	//10日均线
	
    [[NSColor yellowColor] set];
	
	
    bisFirst = YES;
	for (int i = 0; i < m_DrawNum; i++) 
	{

        
		if(i+m_LeftNum<10)
		{
			continue;
		}
        if((i + m_LeftNum)>=[m_AnalyseData count])
            continue;
		tempAna = [m_AnalyseData objectAtIndex:(i + m_LeftNum)];
		if(bisFirst)
		{
			x0 = kLineRect.origin.x + m_dWidth * 0.5 + dPer * i;
			y0 = [self  getYPos:tempAna.maTen secNum:1];
			bisFirst=NO;
			continue;
		}
		
		x1 = kLineRect.origin.x + m_dWidth * 0.5 + dPer * i;
		y1 = [self getYPos:tempAna.maTen secNum:1];
		if (y0 <= 0.1)
			[self  getYPos:tempAna.closep secNum:1];
		CGContextMoveToPoint(context, x0, y0);
		CGContextAddLineToPoint(context, x1, y1);
		CGContextStrokePath(context);
		
		x0 = x1;
		y0= y1;
	}	
	
	//20日均线
	[[NSColor purpleColor] set];
	bisFirst = YES;
	for (int i = 0; i < m_DrawNum; i++) 
	{

        if(i+m_LeftNum<20)
		{
			continue;
		}
        if((i + m_LeftNum)>=[m_AnalyseData count])
            continue;
		tempAna = [m_AnalyseData objectAtIndex:(i + m_LeftNum)];
		if(bisFirst)
		{
			x0 = kLineRect.origin.x + m_dWidth * 0.5 + dPer * i;
			y0 = [self  getYPos:tempAna.maTwn secNum:1];
			bisFirst=NO;
			continue;
		}
		x1 = kLineRect.origin.x + m_dWidth * 0.5 + dPer * i;
		y1 = [self getYPos:tempAna.maTwn secNum:1];
		if (y0 <= 0.1)
			[self  getYPos:tempAna.closep secNum:1];
		CGContextMoveToPoint(context, x0, y0);
		CGContextAddLineToPoint(context, x1, y1);
		CGContextStrokePath(context);
		
		x0 = x1;
		y0= y1;
	}
}

-(void)drawVol:(CGContextRef)context
{
	[self calVol];
	zb_Unit * tempZb;
	Analyse_Unit * tempAna;
	Analyse_Unit * tempAnaEx;
	float x0,y0,x1,y1;
	float yVolumn,xPos;
	float off =  m_dWidth * 0.5;
	int nfoffset=1.0f;
	if (([m_AnalyseData count] < 1) || ([m_AnalyseData count] < m_DrawNum+m_LeftNum)){
		return;
	}
	
	for (int i = 0; i < m_DrawNum; i++) 
	{

        if((i + m_LeftNum)>=[m_AnalyseData count])
            continue;
        tempAna = [m_AnalyseData objectAtIndex:(i + m_LeftNum)];
		//阳线
        if(tempAna.volumn<1)
            continue;
		if (tempAna.closep >tempAna.openp) {
			yVolumn = [self  getYPos:tempAna.volumn secNum:0];
            if(yVolumn<=0.0f)
                continue;
            else if(yVolumn<=nfoffset)
                yVolumn+=nfoffset;
			xPos = volRect.origin.x + m_dWidth * 0.5 + dPer * i;
			
		
            [[NSColor redColor] set];
			CGContextSetLineWidth(context, 1.0);
			
            CGContextAddRect(context, CGRectMake(xPos-off, volRect.origin.y, 2.0f * off, yVolumn));
			CGContextStrokePath(context);
		}
		
		//阴线
		else if(tempAna.closep < tempAna.openp)
		{
			
            [GREENCOLOR set];
			CGContextSetLineWidth(context, 1.0);
			
			yVolumn = [self  getYPos:tempAna.volumn secNum:0];
            if(yVolumn<=0.0f)
                continue;
            else if(yVolumn<=nfoffset)
                yVolumn+=nfoffset;
			xPos = volRect.origin.x + 0.5 * m_dWidth + dPer * i;
			
			
			CGContextAddRect(context, CGRectMake(xPos-off, volRect.origin.y, 2.0f * off, yVolumn));
			
			CGContextStrokePath(context);
			CGContextFillPath(context);
			CGContextFillRect(context, CGRectMake(xPos-off, volRect.origin.y, 2.0f * off, yVolumn));
			
		}	
		
		//平线
		else{
			
            [[NSColor whiteColor] set];
			CGContextSetLineWidth(context, 1.0);
			
			yVolumn = [self  getYPos:tempAna.volumn secNum:0];
            if(yVolumn<=0.0f)
                continue;
            else if(yVolumn<=nfoffset)
                yVolumn+=nfoffset;
			xPos = volRect.origin.x + 0.5 * m_dWidth + dPer * i;
			
			if (i + m_LeftNum -1 > -1) {

                if((i + m_LeftNum-1)>=[m_AnalyseData count])
                    continue;
				tempAnaEx =  [m_AnalyseData objectAtIndex:i + m_LeftNum -1];
				if (tempAna.closep > tempAnaEx.closep) {
					[[NSColor redColor] set];
				}
				else{
					[GREENCOLOR set];
				}
				CGContextAddRect(context, CGRectMake(xPos-off, volRect.origin.y, 2.0f * off, yVolumn));
				CGContextStrokePath(context);
				if (tempAna.closep > tempAnaEx.closep) {}
				else{
					CGContextFillPath(context);
					CGContextFillRect(context,CGRectMake(xPos-off, volRect.origin.y, 2.0f * off, yVolumn));
				}
			}			
		
			
		}
	}
	
	if (([m_ZbData count] < 1) || ([m_ZbData count] < m_DrawNum+m_LeftNum)){
		return;
	}
	
	if(m_LeftNum>=[m_ZbData count])
        return;
	//画均线
	//5日均线
	[[NSColor whiteColor] set];
	tempZb = [m_ZbData objectAtIndex:m_LeftNum];
	x0 = volRect.origin.x + m_dWidth * 0.5  ;
	y0 = volRect.origin.y+[self  getYPos:tempZb.vol_Five secNum:0];
    y0=MAX_VALUE(y0, volRect.origin.y+titleHeight);
    y0=MIN_VALUE(y0, volRect.origin.y+volRect.size.height-1.0);
	for (int i = 1; i < m_DrawNum; i++)
	{
        if((i + m_LeftNum)>=[m_ZbData count])
            continue;
		tempZb = [m_ZbData objectAtIndex:(i + m_LeftNum)];
        if(tempZb.vol_Five<1)
            continue;
		x1 = volRect.origin.x + m_dWidth * 0.5 + dPer * i;
		y1 = volRect.origin.y+[self getYPos:tempZb.vol_Five secNum:0];
        y1=MAX_VALUE(y1, volRect.origin.y+titleHeight);
        y1=MIN_VALUE(y1, volRect.origin.y+volRect.size.height-1.0);
		CGContextMoveToPoint(context, x0, y0);
		CGContextAddLineToPoint(context, x1, y1);
		CGContextStrokePath(context);
		
		x0 = x1;
		y0= y1;
	}	
	
	//10日均线
    if(m_LeftNum>=[m_ZbData count])
        return;
	[[NSColor yellowColor] set];
	tempZb = [m_ZbData objectAtIndex:m_LeftNum];
	x0 = volRect.origin.x+m_dWidth * 0.5  ;
	y0 = volRect.origin.y+[self  getYPos:tempZb.vol_Ten secNum:0];
    y0=MAX_VALUE(y0, volRect.origin.y+titleHeight);
    y0=MIN_VALUE(y0, volRect.origin.y+volRect.size.height-1.0);
	for (int i = 1; i < m_DrawNum; i++)
	{
        if((i + m_LeftNum)>=[m_ZbData count])
            continue;
		tempZb = [m_ZbData objectAtIndex:(i + m_LeftNum)];
        if(tempZb.vol_Ten<1)
            continue;
		x1 = volRect.origin.x+m_dWidth * 0.5 + dPer * i;
		y1 = volRect.origin.y+[self getYPos:tempZb.vol_Ten secNum:0];
        y1=MAX_VALUE(y1, volRect.origin.y+titleHeight);
        y1=MIN_VALUE(y1, volRect.origin.y+volRect.size.height-1.0);
		CGContextMoveToPoint(context, x0, y0);
		CGContextAddLineToPoint(context, x1, y1);
		CGContextStrokePath(context);
		
		x0 = x1;
		y0= y1;
	}	
	
}

-(void) drawZb:(CGContextRef)context
{
	[self calZB];
	zb_Unit * tempZb;
	float ZbButtom = zbRect.origin.y;
	float x0,y0,x1,y1;
	
	if (([m_ZbData count] < 1) || (m_LeftNum>=[m_ZbData count]) || m_LeftNum<0){
		return;
	}
	
	switch (zbIndex) 
	{
		case 0: //画macd
		{
			[[NSColor whiteColor] set];
			tempZb = [m_ZbData objectAtIndex:m_LeftNum];
			x0 = zbRect.origin.x+m_dWidth * 0.5  ;
			y0 = zbRect.origin.y+[self  getZBYPos:tempZb.macd_DIF secNum:1 ];
			
			
			for (int i = 1; i < m_DrawNum && (i+m_LeftNum)<[m_ZbData count]; i++) {
				tempZb = [m_ZbData objectAtIndex:(i + m_LeftNum)];
				
				x1 = zbRect.origin.x+m_dWidth * 0.5 + dPer * i;
				y1 = ZbButtom  +[self getZBYPos:tempZb.macd_DIF  secNum:1 ];
				
				CGContextMoveToPoint(context, x0, y0);
				CGContextAddLineToPoint(context, x1, y1);
				CGContextStrokePath(context);
				
				x0 = x1;
				y0= y1;
			}	
			
			//画dEA
			[[NSColor yellowColor] set];
			tempZb = [m_ZbData objectAtIndex:m_LeftNum];
			x0 = zbRect.origin.x+m_dWidth * 0.5  ;
			y0 = ZbButtom+[self  getZBYPos:tempZb.macd_DEF  secNum:1 ] ;
			
			for (int i = 1; i < m_DrawNum && (i+m_LeftNum)<[m_ZbData count]; i++) {
				tempZb = [m_ZbData objectAtIndex:(i + m_LeftNum)];
				
				x1 = zbRect.origin.x+m_dWidth * 0.5 + dPer * i;
				y1 = ZbButtom +[self getZBYPos:tempZb.macd_DEF  secNum:1 ];
				
				CGContextMoveToPoint(context, x0, y0);
				CGContextAddLineToPoint(context, x1, y1);
				CGContextStrokePath(context);
				
				x0 = x1;
				y0= y1;
			}
			
			
			//画MACD
			for (int i = 0; i < m_DrawNum && (i+m_LeftNum)<[m_ZbData count]; i++) {
				if([m_ZbData count] > i+m_LeftNum)	{
					tempZb = [m_ZbData objectAtIndex:(i + m_LeftNum)];	
					if (tempZb.macd_MACD > 0) {
						[[NSColor redColor] set];
					} else {
						[GREENCOLOR set];
					}
					
					x1 = zbRect.origin.x+m_dWidth * 0.5 + dPer * i;
					y1 =  ZbButtom + [self getZBYPos:tempZb.macd_MACD  secNum:1 ];
					
					CGContextMoveToPoint(context, x1, ZbButtom+m_fPerUnitHeight);
					CGContextAddLineToPoint(context, x1, y1);
					CGContextStrokePath(context);
				}
			}
		}
			break;
		case 1: //画kdj
		{
			//画K
			[[NSColor whiteColor] set];
			tempZb = [m_ZbData objectAtIndex:m_LeftNum];
			x0 = zbRect.origin.x+m_dWidth * 0.5  ;
			y0 = ZbButtom-[self  getZBYPos:tempZb.kdj_K secNum:2 ];
			
			for (int i = 1; i < m_DrawNum && (i+m_LeftNum)<[m_ZbData count]; i++) {
				tempZb = [m_ZbData objectAtIndex:(i + m_LeftNum)];
				
				x1 = zbRect.origin.x+m_dWidth * 0.5 + dPer * i;
				y1 = ZbButtom-[self getZBYPos:tempZb.kdj_K  secNum:2 ];
				
				CGContextMoveToPoint(context, x0, y0);
				CGContextAddLineToPoint(context, x1, y1);
				CGContextStrokePath(context);
				
				x0 = x1;
				y0= y1;
			}	
			
			//画d
			[[NSColor yellowColor] set];
			tempZb = [m_ZbData objectAtIndex:m_LeftNum];
			x0 = zbRect.origin.x+m_dWidth * 0.5  ;
			y0 = ZbButtom-[self  getZBYPos:tempZb.kdj_D secNum:2 ];
			
			for (int i = 1; i < m_DrawNum && (i+m_LeftNum)<[m_ZbData count]; i++) {
				tempZb = [m_ZbData objectAtIndex:(i + m_LeftNum)];
				
				x1 = zbRect.origin.x+m_dWidth * 0.5 + dPer * i;
				y1 = ZbButtom-[self getZBYPos:tempZb.kdj_D  secNum:2 ];
				
				CGContextMoveToPoint(context, x0, y0);
				CGContextAddLineToPoint(context, x1, y1);
				CGContextStrokePath(context);
				
				x0 = x1;
				y0= y1;
			}	
			
			//画j
			[[NSColor purpleColor] set];
			tempZb = [m_ZbData objectAtIndex:m_LeftNum];
			x0 = zbRect.origin.x+ m_dWidth * 0.5  ;
			y0 = ZbButtom-[self  getZBYPos:tempZb.kdj_J secNum:2 ];
			
			for (int i = 1; i < m_DrawNum && (i+m_LeftNum)<[m_ZbData count]; i++) {
				tempZb = [m_ZbData objectAtIndex:(i + m_LeftNum)];
				
				x1 = zbRect.origin.x+m_dWidth * 0.5 + dPer * i;
				y1 = ZbButtom-[self getZBYPos:tempZb.kdj_J  secNum:2 ];
				
				CGContextMoveToPoint(context, x0, y0);
				CGContextAddLineToPoint(context, x1, y1);
				CGContextStrokePath(context);
				
				x0 = x1;
				y0= y1;
			}	
			
		}
			break;
		case 2://画rsi
		{
			//画rsi1
			[[NSColor whiteColor] set];
			int j;
			for (j =0; j<m_ReadNum && (j+m_LeftNum)<[m_ZbData count]; j++) {
				tempZb = [m_ZbData objectAtIndex:m_LeftNum+j];
				if (tempZb.rsi_RSI1 >0) {
					break;
				}
			}
            BOOL  bx0flag=NO;
            if((j+m_LeftNum)<[m_ZbData count])
            {
                bx0flag=YES;
                tempZb = [m_ZbData objectAtIndex:m_LeftNum+j];
        
                x0 = zbRect.origin.x+m_dWidth * 0.5  ;
                y0 = ZbButtom-[self  getZBYPos:tempZb.rsi_RSI1 secNum:2 ];
            }
			
			for (int i = j+1; i < m_DrawNum && (i+m_LeftNum)<[m_ZbData count]; i++) {
				tempZb = [m_ZbData objectAtIndex:(i + m_LeftNum)];
				
                if(bx0flag)
                {
                    x1 = zbRect.origin.x+m_dWidth * 0.5 + dPer * i;
                    y1 = ZbButtom-[self getZBYPos:tempZb.rsi_RSI1  secNum:2 ];
                }
                else
                {
                    x0 = zbRect.origin.x+m_dWidth * 0.5  ;
                    y0 = ZbButtom-[self  getZBYPos:tempZb.rsi_RSI1 secNum:2 ];
                    continue;
                }
				
				CGContextMoveToPoint(context, x0, y0);
				CGContextAddLineToPoint(context, x1, y1);
				CGContextStrokePath(context);
				
				x0 = x1;
				y0= y1;
			}	
			//画rsi2
			[[NSColor yellowColor] set];
			
            bx0flag=NO;
            if((j+m_LeftNum)<[m_ZbData count])
            {
                bx0flag=YES;
                tempZb = [m_ZbData objectAtIndex:m_LeftNum+j];
                
                x0 = zbRect.origin.x+m_dWidth * 0.5  ;
                if (tempZb.rsi_RSI2 > 0) {
                    y0 = ZbButtom-[self getZBYPos:tempZb.rsi_RSI2  secNum:2 ];
                }
                else {
                    y0 = ZbButtom-[self getZBYPos:tempZb.rsi_RSI1  secNum:2 ];
                }
            }
			
			for (int i = j+1; i < m_DrawNum && (i+m_LeftNum)<[m_ZbData count]; i++) {
				tempZb = [m_ZbData objectAtIndex:(i + m_LeftNum)];
				
                if(bx0flag)
                {
                    x1 = zbRect.origin.x+m_dWidth * 0.5 + dPer * i;
                    if (tempZb.rsi_RSI2 > 0) {
                        y1 = ZbButtom-[self getZBYPos:tempZb.rsi_RSI2  secNum:2 ];
                    }
                    else {
                        y1 = ZbButtom-[self getZBYPos:tempZb.rsi_RSI1  secNum:2 ];
                    }
                }
                else
                {
                    x0 = zbRect.origin.x+m_dWidth * 0.5  ;
                    if (tempZb.rsi_RSI2 > 0) {
                        y0 = ZbButtom-[self getZBYPos:tempZb.rsi_RSI2  secNum:2 ];
                    }
                    else {
                        y0 = ZbButtom-[self getZBYPos:tempZb.rsi_RSI1  secNum:2 ];
                    }
                    continue;
                }

				
				CGContextMoveToPoint(context, x0, y0);
				CGContextAddLineToPoint(context, x1, y1);
				CGContextStrokePath(context);
				
				x0 = x1;
				y0= y1;
			}	
			//画rsi3
			[[NSColor purpleColor] set];
			
            bx0flag=NO;
            if((j+m_LeftNum)<[m_ZbData count])
            {
                bx0flag=YES;
                tempZb = [m_ZbData objectAtIndex:m_LeftNum+j];
                x0 =zbRect.origin.x+ m_dWidth * 0.5  ;
                if (tempZb.rsi_RSI3 > 0) {
                    y0 = ZbButtom-[self getZBYPos:tempZb.rsi_RSI3  secNum:2 ];
                }
                else {
                    y0 = ZbButtom-[self getZBYPos:tempZb.rsi_RSI1  secNum:2 ];
                }
            }
			
			for (int i = j+1; i < m_DrawNum && (i+m_LeftNum)<[m_ZbData count]; i++) {
				tempZb = [m_ZbData objectAtIndex:(i + m_LeftNum)];
				
                if(bx0flag)
                {
                    x1 = zbRect.origin.x+m_dWidth * 0.5 + dPer * i;
                    if (tempZb.rsi_RSI3 > 0) {
                        y1 = ZbButtom-[self getZBYPos:tempZb.rsi_RSI3  secNum:2 ];
                    }
                    else {
                        y1 = ZbButtom-[self getZBYPos:tempZb.rsi_RSI1  secNum:2 ];
                    }
                }
                else
                {
                    x0 =zbRect.origin.x+ m_dWidth * 0.5  ;
                    if (tempZb.rsi_RSI3 > 0) {
                        y0 = ZbButtom-[self getZBYPos:tempZb.rsi_RSI3  secNum:2 ];
                    }
                    else {
                        y0 = ZbButtom-[self getZBYPos:tempZb.rsi_RSI1  secNum:2 ];
                    }
                    continue;
                }
				
				CGContextMoveToPoint(context, x0, y0);
				CGContextAddLineToPoint(context, x1, y1);
				CGContextStrokePath(context);
				
				x0 = x1;
				y0= y1;
			}	
			
		}
			break;
		case 3://画bias
		{
			//画bias1
			[[NSColor whiteColor] set];
			tempZb = [m_ZbData objectAtIndex:m_LeftNum];
			x0 = zbRect.origin.x+m_dWidth * 0.5  ;
			y0 = ZbButtom-[self  getZBYPos:tempZb.bias_BIAS1 secNum:2 ];
			
			for (int i = 1; i < m_DrawNum && (i+m_LeftNum)<[m_ZbData count]; i++) {
				tempZb = [m_ZbData objectAtIndex:(i + m_LeftNum)];
				
				x1 = zbRect.origin.x+m_dWidth * 0.5 + dPer * i;
				y1 = ZbButtom-[self getZBYPos:tempZb.bias_BIAS1  secNum:2 ];
				
				CGContextMoveToPoint(context, x0, y0);
				CGContextAddLineToPoint(context, x1, y1);
				CGContextStrokePath(context);
				
				x0 = x1;
				y0= y1;
			}	
			//画bias2
			[[NSColor yellowColor] set];
			tempZb = [m_ZbData objectAtIndex:m_LeftNum];
			
			x0 = zbRect.origin.x+ m_dWidth * 0.5  ;
			y0 = ZbButtom-[self  getZBYPos:tempZb.bias_BIAS2 secNum:2 ];
			
			for (int i = 1; i < m_DrawNum && (i+m_LeftNum)<[m_ZbData count]; i++) {
				tempZb = [m_ZbData objectAtIndex:(i + m_LeftNum)];
				
				x1 = zbRect.origin.x+m_dWidth * 0.5 + dPer * i;
				y1 = ZbButtom-[self getZBYPos:tempZb.bias_BIAS2  secNum:2 ];
				
				CGContextMoveToPoint(context, x0, y0);
				CGContextAddLineToPoint(context, x1, y1);
				CGContextStrokePath(context);
				
				x0 = x1;
				y0= y1;
			}	
			//画bias3
			[[NSColor purpleColor] set];
			tempZb = [m_ZbData objectAtIndex:m_LeftNum];
			x0 = zbRect.origin.x+m_dWidth * 0.5  ;
			y0 = ZbButtom-[self  getZBYPos:tempZb.bias_BIAS3 secNum:2 ];
			
			for (int i = 1; i < m_DrawNum && (i+m_LeftNum)<[m_ZbData count]; i++) {
				tempZb = [m_ZbData objectAtIndex:(i + m_LeftNum)];
				
				x1 = zbRect.origin.x+m_dWidth * 0.5 + dPer * i;
				y1 = ZbButtom-[self getZBYPos:tempZb.bias_BIAS3  secNum:2 ];
				
				CGContextMoveToPoint(context, x0, y0);
				CGContextAddLineToPoint(context, x1, y1);
				CGContextStrokePath(context);
				
				x0 = x1;
				y0= y1;
			}	
			
		}
			break;
		case 10:
		{
			[[NSColor whiteColor] set];
			CGFloat dash[] = {2.0f, 5.0f};
			CGContextSetLineDash(context, 0.0f, dash, 1);
			if(m_MaxZb > 450.0f)
			{
				
				y0 = ZbButtom-[self  getZBYPos:40.0f secNum:2 ];
				CGContextMoveToPoint(context, zbRect.origin.x, y0);
				CGContextAddLineToPoint(context, zbRect.origin.x+zbRect.size.width, y0);
			}
			if(m_MinZb<40.0f)
			{
				CGContextSetLineDash(context, 0.0f, dash, 1);
				y0 = ZbButtom-[self  getZBYPos:400.0f secNum:2 ];
				CGContextMoveToPoint(context, zbRect.origin.x, y0);
				CGContextAddLineToPoint(context, zbRect.origin.x+zbRect.size.width, y0);
			}
			CGContextStrokePath(context);
			
			CGContextSetLineDash(context, 0.0, dash, 0);
			
		}
		case 4://画DMA
		{
			//画dif
			[[NSColor whiteColor] set];
			tempZb = [m_ZbData objectAtIndex:m_LeftNum];
			x0 = zbRect.origin.x+m_dWidth * 0.5  ;
			y0 = ZbButtom-[self  getZBYPos:tempZb.zb_1 secNum:2 ];
			
			for (int i = 1; i < m_DrawNum && (i+m_LeftNum)<[m_ZbData count]; i++)
			{
				tempZb = [m_ZbData objectAtIndex:(i + m_LeftNum)];
				
				x1 = zbRect.origin.x+m_dWidth * 0.5 + dPer * i;
				y1 = ZbButtom -[self getZBYPos:tempZb.zb_1  secNum:2 ];
				
				CGContextMoveToPoint(context, x0, y0);
				CGContextAddLineToPoint(context, x1, y1);
				CGContextStrokePath(context);
				
				x0 = x1;
				y0= y1;
			}
			
			//画AMA
			[[NSColor yellowColor] set];
			tempZb = [m_ZbData objectAtIndex:m_LeftNum];
			x0 = zbRect.origin.x+m_dWidth * 0.5  ;
			y0 = ZbButtom-[self  getZBYPos:tempZb.zb_2 secNum:2 ];
			
			for (int i = 1; i < m_DrawNum && (i+m_LeftNum)<[m_ZbData count]; i++)
			{
				tempZb = [m_ZbData objectAtIndex:(i + m_LeftNum)];
				
				x1 = zbRect.origin.x+m_dWidth * 0.5 + dPer * i;
				y1 = ZbButtom -[self getZBYPos:tempZb.zb_2  secNum:2 ];
				
				CGContextMoveToPoint(context, x0, y0);
				CGContextAddLineToPoint(context, x1, y1);
				CGContextStrokePath(context);
				
				x0 = x1;
				y0= y1;
			}
		}
			break;
		case 7://MTM
		{
			if(m_MaxZb > 110.0f && m_MinZb<90.0f)
			{
				[[NSColor whiteColor] set];
				CGFloat dash[] = {2.0f, 5.0f};
				CGContextSetLineDash(context, 0.0, dash, 1);
				y0 = ZbButtom-[self  getZBYPos:100.0f secNum:2 ];
				CGContextMoveToPoint(context, zbRect.origin.x, y0);
				CGContextAddLineToPoint(context, zbRect.origin.x+zbRect.size.width, y0);
				CGContextStrokePath(context);
				
				CGContextSetLineDash(context, 0.0, dash, 0);
			}
		}
		case 5://画OBV BRAR
		{
			//画OBV MTM BR
			[[NSColor whiteColor] set];
			tempZb = [m_ZbData objectAtIndex:m_LeftNum];
			x0 = zbRect.origin.x+m_dWidth * 0.5  ;
			y0 = ZbButtom-[self  getZBYPos:tempZb.zb_1 secNum:2 ];
			
			for (int i = 1; i < m_DrawNum && (i+m_LeftNum)<[m_ZbData count]; i++)
			{
				tempZb = [m_ZbData objectAtIndex:(i + m_LeftNum)];
				
				x1 = zbRect.origin.x+m_dWidth * 0.5 + dPer * i;
				y1 = ZbButtom -[self getZBYPos:tempZb.zb_1  secNum:2 ];
				
				CGContextMoveToPoint(context, x0, y0);
				CGContextAddLineToPoint(context, x1, y1);
				CGContextStrokePath(context);
				
				x0 = x1;
				y0= y1;
			}
			
			//画MAOBV MAMTM AR
			[[NSColor yellowColor] set];
			tempZb = [m_ZbData objectAtIndex:m_LeftNum];
			x0 = zbRect.origin.x+m_dWidth * 0.5  ;
			y0 = ZbButtom-[self  getZBYPos:tempZb.zb_2 secNum:2 ];
			
			for (int i = 1; i < m_DrawNum && (i+m_LeftNum)<[m_ZbData count]; i++)
			{
				tempZb = [m_ZbData objectAtIndex:(i + m_LeftNum)];
				
				x1 = zbRect.origin.x+m_dWidth * 0.5 + dPer * i;
				y1 = ZbButtom -[self getZBYPos:tempZb.zb_2  secNum:2 ];
				
				CGContextMoveToPoint(context, x0, y0);
				CGContextAddLineToPoint(context, x1, y1);
				CGContextStrokePath(context);
				
				x0 = x1;
				y0= y1;
			}
		}
			break;
		case 6:
		{
			//画ROC
			[[NSColor whiteColor] set];
			tempZb = [m_ZbData objectAtIndex:m_LeftNum];
			x0 = zbRect.origin.x+m_dWidth * 0.5  ;
			y0 = ZbButtom-[self  getZBYPos:tempZb.zb_1 secNum:2 ];
			
			for (int i = 1; i < m_DrawNum && (i+m_LeftNum)<[m_ZbData count]; i++)
			{
				tempZb = [m_ZbData objectAtIndex:(i + m_LeftNum)];
				
				x1 = zbRect.origin.x+m_dWidth * 0.5 + dPer * i;
				y1 = ZbButtom -[self getZBYPos:tempZb.zb_1  secNum:2 ];
				
				CGContextMoveToPoint(context, x0, y0);
				CGContextAddLineToPoint(context, x1, y1);
				CGContextStrokePath(context);
				
				x0 = x1;
				y0= y1;
			}
			
			//画MAROC
			[[NSColor yellowColor] set];
			tempZb = [m_ZbData objectAtIndex:m_LeftNum];
			x0 = zbRect.origin.x+m_dWidth * 0.5;
			y0 = ZbButtom-[self  getZBYPos:tempZb.zb_2 secNum:2 ];
			
			for (int i = 1; i < m_DrawNum && (i+m_LeftNum)<[m_ZbData count]; i++)
			{
				tempZb = [m_ZbData objectAtIndex:(i + m_LeftNum)];
				
				x1 = zbRect.origin.x+m_dWidth * 0.5 + dPer * i;
				y1 = ZbButtom -[self getZBYPos:tempZb.zb_2  secNum:2 ];
				
				CGContextMoveToPoint(context, x0, y0);
				CGContextAddLineToPoint(context, x1, y1);
				CGContextStrokePath(context);
				
				x0 = x1;
				y0= y1;
			}
			if(m_MaxZb > 7.0f && m_MinZb<-7.0f)
			{
				[[NSColor whiteColor] set];
				CGFloat dash[] = {2.0f, 5.0f};
				CGContextSetLineDash(context, 0.0, dash, 1);
				y0 = ZbButtom-[self  getZBYPos:-6.5f secNum:2 ];
				CGContextMoveToPoint(context, zbRect.origin.x, y0);
				CGContextAddLineToPoint(context, zbRect.origin.x+zbRect.size.width, y0);
				
				y0 = ZbButtom-[self  getZBYPos:0.0f secNum:2 ];
				CGContextMoveToPoint(context, zbRect.origin.x, y0);
				CGContextAddLineToPoint(context, zbRect.origin.x+zbRect.size.width, y0);
				
				y0 = ZbButtom-[self  getZBYPos:6.5f secNum:2 ];
				CGContextMoveToPoint(context, zbRect.origin.x, y0);
				CGContextAddLineToPoint(context, zbRect.origin.x+zbRect.size.width, y0);
				CGContextStrokePath(context);
				
				CGContextSetLineDash(context, 0.0, dash, 0);
			}
			
		}
			break;
		case 8:
		{
			//CR
			[[NSColor whiteColor] set];
			tempZb = [m_ZbData objectAtIndex:m_LeftNum];
			x0 = zbRect.origin.x+m_dWidth * 0.5  ;
			y0 = ZbButtom-[self  getZBYPos:tempZb.zb_1 secNum:2 ];
			
			for (int i = 1; i < m_DrawNum && (i+m_LeftNum)<[m_ZbData count]; i++)
			{
				tempZb = [m_ZbData objectAtIndex:(i + m_LeftNum)];
				
				x1 = zbRect.origin.x+m_dWidth * 0.5 + dPer * i;
				y1 = ZbButtom -[self getZBYPos:tempZb.zb_1  secNum:2 ];
				
				CGContextMoveToPoint(context, x0, y0);
				CGContextAddLineToPoint(context, x1, y1);
				CGContextStrokePath(context);
				
				x0 = x1;
				y0= y1;
			}
			
			//画CR ma1
			[[NSColor yellowColor] set];
			tempZb = [m_ZbData objectAtIndex:m_LeftNum];
			x0 = zbRect.origin.x+m_dWidth * 0.5  ;
			y0 = ZbButtom-[self  getZBYPos:tempZb.zb_2 secNum:2 ];
			
			for (int i = 1; i < m_DrawNum && (i+m_LeftNum)<[m_ZbData count]; i++)
			{
				tempZb = [m_ZbData objectAtIndex:(i + m_LeftNum)];
				
				x1 = zbRect.origin.x+m_dWidth * 0.5 + dPer * i;
				y1 = ZbButtom -[self getZBYPos:tempZb.zb_2  secNum:2 ];
				
				CGContextMoveToPoint(context, x0, y0);
				CGContextAddLineToPoint(context, x1, y1);
				CGContextStrokePath(context);
				
				x0 = x1;
				y0= y1;
			}
			
			[[NSColor purpleColor] set];
			tempZb = [m_ZbData objectAtIndex:m_LeftNum];
			x0 = zbRect.origin.x+m_dWidth * 0.5  ;
			y0 = ZbButtom-[self  getZBYPos:tempZb.zb_3 secNum:2 ];
			
			for (int i = 1; i < m_DrawNum && (i+m_LeftNum)<[m_ZbData count]; i++)
			{
				tempZb = [m_ZbData objectAtIndex:(i + m_LeftNum)];
				
				x1 = zbRect.origin.x+m_dWidth * 0.5 + dPer * i;
				y1 = ZbButtom -[self getZBYPos:tempZb.zb_3  secNum:2 ];
				
				CGContextMoveToPoint(context, x0, y0);
				CGContextAddLineToPoint(context, x1, y1);
				CGContextStrokePath(context);
				
				x0 = x1;
				y0= y1;
			}
		}
			break;
			
		case 9:
		{
			//PDI
			[[NSColor whiteColor] set];
			tempZb = [m_ZbData objectAtIndex:m_LeftNum];
			x0 = zbRect.origin.x+m_dWidth * 0.5  ;
			y0 = ZbButtom-[self  getZBYPos:tempZb.zb_1 secNum:2 ];
			
			for (int i = 1; i < m_DrawNum && (i+m_LeftNum)<[m_ZbData count]; i++)
			{
				tempZb = [m_ZbData objectAtIndex:(i + m_LeftNum)];
				
				x1 = zbRect.origin.x+m_dWidth * 0.5 + dPer * i;
				y1 = ZbButtom -[self getZBYPos:tempZb.zb_1  secNum:2 ];
				
				CGContextMoveToPoint(context, x0, y0);
				CGContextAddLineToPoint(context, x1, y1);
				CGContextStrokePath(context);
				
				x0 = x1;
				y0= y1;
			}
			
			//画MDI
			[[NSColor yellowColor] set];
			tempZb = [m_ZbData objectAtIndex:m_LeftNum];
			x0 = zbRect.origin.x+m_dWidth * 0.5  ;
			y0 = ZbButtom-[self  getZBYPos:tempZb.zb_2 secNum:2 ];
			
			for (int i = 1; i < m_DrawNum && (i+m_LeftNum)<[m_ZbData count]; i++)
			{
				tempZb = [m_ZbData objectAtIndex:(i + m_LeftNum)];
				
				x1 = zbRect.origin.x+m_dWidth * 0.5 + dPer * i;
				y1 = ZbButtom -[self getZBYPos:tempZb.zb_2  secNum:2 ];
				
				CGContextMoveToPoint(context, x0, y0);
				CGContextAddLineToPoint(context, x1, y1);
				CGContextStrokePath(context);
				
				x0 = x1;
				y0= y1;
			}
			//ADX
			[[NSColor purpleColor] set];
			tempZb = [m_ZbData objectAtIndex:m_LeftNum];
			x0 = zbRect.origin.x+m_dWidth * 0.5  ;
			y0 = ZbButtom-[self  getZBYPos:tempZb.zb_3 secNum:2 ];
			
			for (int i = 1; i < m_DrawNum && (i+m_LeftNum)<[m_ZbData count]; i++)
			{
				tempZb = [m_ZbData objectAtIndex:(i + m_LeftNum)];
				
				x1 = zbRect.origin.x+m_dWidth * 0.5 + dPer * i;
				y1 = ZbButtom -[self getZBYPos:tempZb.zb_3  secNum:2 ];
				
				CGContextMoveToPoint(context, x0, y0);
				CGContextAddLineToPoint(context, x1, y1);
				CGContextStrokePath(context);
				
				x0 = x1;
				y0= y1;
			}
			
			//ADXR
			[GREENCOLOR set];
			tempZb = [m_ZbData objectAtIndex:m_LeftNum];
			x0 = zbRect.origin.x+m_dWidth * 0.5  ;
			y0 = ZbButtom-[self  getZBYPos:tempZb.zb_4 secNum:2 ];
			
			for (int i = 1; i < m_DrawNum && (i+m_LeftNum)<[m_ZbData count]; i++)
			{
				tempZb = [m_ZbData objectAtIndex:(i + m_LeftNum)];
				
				x1 = zbRect.origin.x+m_dWidth * 0.5 + dPer * i;
				y1 = ZbButtom -[self getZBYPos:tempZb.zb_4  secNum:2 ];
				
				CGContextMoveToPoint(context, x0, y0);
				CGContextAddLineToPoint(context, x1, y1);
				CGContextStrokePath(context);
				
				x0 = x1;
				y0= y1;
			}
		}
			break;
		case 12: //TRIX
		case 11:
		{
			[[NSColor whiteColor] set];
			CGFloat dash[] = {2.0f, 5.0f};
			CGContextSetLineDash(context, 0.0f, dash, 1);
			if(m_MaxZb > 450.0f)
			{
				
				y0 = ZbButtom-[self  getZBYPos:400.0f secNum:2 ];
				CGContextMoveToPoint(context, zbRect.origin.x, y0);
				CGContextAddLineToPoint(context, zbRect.origin.x+zbRect.size.width, y0);
			}
			if(m_MinZb<40.0f)
			{
				CGContextSetLineDash(context, 0.0f, dash, 1);
				y0 = ZbButtom-[self  getZBYPos:40.0f secNum:2 ];
				CGContextMoveToPoint(context, zbRect.origin.x, y0);
				CGContextAddLineToPoint(context, zbRect.origin.x+zbRect.size.width, y0);
			}
			CGContextStrokePath(context);
			
			CGContextSetLineDash(context, 0.0, dash, 0);
			
			//画VR TRIX
			[[NSColor whiteColor] set];
			tempZb = [m_ZbData objectAtIndex:m_LeftNum];
			x0 = zbRect.origin.x+m_dWidth * 0.5  ;
			y0 = ZbButtom-[self  getZBYPos:tempZb.zb_1 secNum:2 ];
			
			for (int i = 1; i < m_DrawNum && (i+m_LeftNum)<[m_ZbData count]; i++)
			{
				tempZb = [m_ZbData objectAtIndex:(i + m_LeftNum)];
				
				x1 = zbRect.origin.x+m_dWidth * 0.5 + dPer * i;
				y1 = ZbButtom -[self getZBYPos:tempZb.zb_1  secNum:2 ];
				
				CGContextMoveToPoint(context, x0, y0);
				CGContextAddLineToPoint(context, x1, y1);
				CGContextStrokePath(context);
				
				x0 = x1;
				y0= y1;
			}
			
			//画MRVR MATIRX
			[[NSColor yellowColor] set];
			tempZb = [m_ZbData objectAtIndex:m_LeftNum];
			x0 = zbRect.origin.x+m_dWidth * 0.5  ;
			y0 = ZbButtom-[self  getZBYPos:tempZb.zb_2 secNum:2 ];
			
			for (int i = 1; i < m_DrawNum && (i+m_LeftNum)<[m_ZbData count]; i++)
			{
				tempZb = [m_ZbData objectAtIndex:(i + m_LeftNum)];
				
				x1 = zbRect.origin.x+m_dWidth * 0.5 + dPer * i;
				y1 = ZbButtom -[self getZBYPos:tempZb.zb_2  secNum:2 ];
				CGContextMoveToPoint(context, x0, y0);
				CGContextAddLineToPoint(context, x1, y1);
				CGContextStrokePath(context);
				
				x0 = x1;
				y0= y1;
			}
		}
			break;
		case 17://DPO	
		case 13://EMV
		{
			
			if(m_MaxZb > 0.0f&&m_MinZb<0.0f)
			{
				[[NSColor whiteColor] set];
				CGFloat dash[] = {2.0f, 5.0f};
				CGContextSetLineDash(context, 0.0f, dash, 1);
				y0 = ZbButtom-[self  getZBYPos:0.0f secNum:2 ];
				CGContextMoveToPoint(context, zbRect.origin.x, y0);
				CGContextAddLineToPoint(context, zbRect.origin.x+zbRect.size.width, y0);
				CGContextStrokePath(context);
				
				CGContextSetLineDash(context, 0.0, dash, 0);
			}
			
			
			//EMV DPO
			[[NSColor whiteColor] set];
			tempZb = [m_ZbData objectAtIndex:m_LeftNum];
			x0 = zbRect.origin.x+m_dWidth * 0.5  ;
			y0 = ZbButtom-[self  getZBYPos:tempZb.zb_1 secNum:2 ];
			
			for (int i = 1; i < m_DrawNum && (i+m_LeftNum)<[m_ZbData count]; i++)
			{
				tempZb = [m_ZbData objectAtIndex:(i + m_LeftNum)];
				
				x1 = zbRect.origin.x+m_dWidth * 0.5 + dPer * i;
				y1 = ZbButtom -[self getZBYPos:tempZb.zb_1  secNum:2 ];
				
				CGContextMoveToPoint(context, x0, y0);
				CGContextAddLineToPoint(context, x1, y1);
				CGContextStrokePath(context);
				
				x0 = x1;
				y0= y1;
			}
			 
			//画MAEMV MADPO
			[[NSColor yellowColor] set];
			tempZb = [m_ZbData objectAtIndex:m_LeftNum];
			x0 = zbRect.origin.x+m_dWidth * 0.5  ;
			y0 = ZbButtom-[self  getZBYPos:tempZb.zb_2 secNum:2 ];
			
			for (int i = 1; i < m_DrawNum && (i+m_LeftNum)<[m_ZbData count]; i++)
			{
				tempZb = [m_ZbData objectAtIndex:(i + m_LeftNum)];
				
				x1 = zbRect.origin.x+m_dWidth * 0.5 + dPer * i;
				y1 = ZbButtom -[self getZBYPos:tempZb.zb_2  secNum:2 ];
				CGContextMoveToPoint(context, x0, y0);
				CGContextAddLineToPoint(context, x1, y1);
				CGContextStrokePath(context);
				
				x0 = x1;
				y0= y1;
			}
		}
			break;
		case 16:
		{
			if(m_MaxZb > 75.0&&m_MinZb<75.0f)
			{
				[[NSColor whiteColor] set];
				CGFloat dash[] = {2.0f, 5.0f};
				CGContextSetLineDash(context, 0.0f, dash, 1);
				y0 = ZbButtom-[self  getZBYPos:75.0f secNum:2 ];
				CGContextMoveToPoint(context, zbRect.origin.x, y0);
				CGContextAddLineToPoint(context, zbRect.origin.x+zbRect.size.width, y0);
				CGContextStrokePath(context);
				
				CGContextSetLineDash(context, 0.0, dash, 0);
			}
			if(m_MaxZb > 25.0&&m_MinZb<25.0f)
			{
				[[NSColor whiteColor] set];
				CGFloat dash[] = {2.0f, 5.0f};
				CGContextSetLineDash(context, 0.0f, dash, 1);
				y0 = ZbButtom-[self  getZBYPos:25.0f secNum:2 ];
				CGContextMoveToPoint(context, zbRect.origin.x, y0);
				CGContextAddLineToPoint(context, zbRect.origin.x+zbRect.size.width, y0);
				CGContextStrokePath(context);
				
				CGContextSetLineDash(context, 0.0, dash, 0);
			}
			
		}
		
		case 19://ASI
		case 14://WR
		{
			//WR1 ASI
			[[NSColor whiteColor] set];
			tempZb = [m_ZbData objectAtIndex:m_LeftNum];
			x0 = zbRect.origin.x+m_dWidth * 0.5  ;
			y0 = ZbButtom-[self  getZBYPos:tempZb.zb_1 secNum:2 ];
			
			for (int i = 1; i < m_DrawNum && (i+m_LeftNum)<[m_ZbData count]; i++)
			{
				tempZb = [m_ZbData objectAtIndex:(i + m_LeftNum)];
				
				x1 = zbRect.origin.x+m_dWidth * 0.5 + dPer * i;
				y1 = ZbButtom -[self getZBYPos:tempZb.zb_1  secNum:2 ];
				
				CGContextMoveToPoint(context, x0, y0);
				CGContextAddLineToPoint(context, x1, y1);
				CGContextStrokePath(context);
				
				x0 = x1;
				y0= y1;
			}
			
			//画WR2 ASI
			[[NSColor yellowColor] set];
			tempZb = [m_ZbData objectAtIndex:m_LeftNum];
			x0 = zbRect.origin.x+m_dWidth * 0.5  ;
			y0 = ZbButtom-[self  getZBYPos:tempZb.zb_2 secNum:2 ];
			
			for (int i = 1; i < m_DrawNum && (i+m_LeftNum)<[m_ZbData count]; i++)
			{
				tempZb = [m_ZbData objectAtIndex:(i + m_LeftNum)];
				
				x1 = zbRect.origin.x+m_dWidth * 0.5 + dPer * i;
				y1 = ZbButtom -[self getZBYPos:tempZb.zb_2  secNum:2 ];
				//				NSLog(@"zb_2%d = %f",i,tempZb.zb_2);
				CGContextMoveToPoint(context, x0, y0);
				CGContextAddLineToPoint(context, x1, y1);
				CGContextStrokePath(context);
				
				x0 = x1;
				y0= y1;
			}
		}
			break;
		case 15://CCI
		{
			if(m_MaxZb > 0.0f&&m_MinZb<0.0f)
			{
				[[NSColor whiteColor] set];
				CGFloat dash[] = {2.0f, 5.0f};
				CGContextSetLineDash(context, 0.0f, dash, 1);
				y0 = ZbButtom-[self  getZBYPos:0.0f secNum:2 ];
				CGContextMoveToPoint(context, zbRect.origin.x, y0);
				CGContextAddLineToPoint(context, zbRect.origin.x+zbRect.size.width, y0);
				CGContextStrokePath(context);
				
				CGContextSetLineDash(context, 0.0, dash, 0);
			}
			if(m_MaxZb>100.0f)
			{
				[[NSColor whiteColor] set];
				CGFloat dash[] = {2.0f, 5.0f};
				CGContextSetLineDash(context, 0.0f, dash, 1);
				y0 = ZbButtom-[self  getZBYPos:100.0f secNum:2 ];
				CGContextMoveToPoint(context, zbRect.origin.x, y0);
				CGContextAddLineToPoint(context, zbRect.origin.x+zbRect.size.width, y0);
				CGContextStrokePath(context);
				
				CGContextSetLineDash(context, 0.0, dash, 0);
			}
			
			if(m_MinZb<-100.0f)
			{
				[[NSColor whiteColor] set];
				CGFloat dash[] = {2.0f, 5.0f};
				CGContextSetLineDash(context, 0.0f, dash, 1);
				y0 = ZbButtom-[self  getZBYPos:-100.0f secNum:2 ];
				CGContextMoveToPoint(context, zbRect.origin.x, y0);
				CGContextAddLineToPoint(context, zbRect.origin.x+zbRect.size.width, y0);
				CGContextStrokePath(context);
				
				CGContextSetLineDash(context, 0.0, dash, 0);
			}
			[[NSColor whiteColor] set];
			tempZb = [m_ZbData objectAtIndex:m_LeftNum];
			x0 = zbRect.origin.x+m_dWidth * 0.5  ;
			y0 = ZbButtom-[self  getZBYPos:tempZb.zb_1 secNum:2 ];
			
			for (int i = 1; i < m_DrawNum && (i+m_LeftNum)<[m_ZbData count]; i++)
			{
				tempZb = [m_ZbData objectAtIndex:(i + m_LeftNum)];
				
				x1 = zbRect.origin.x+m_dWidth * 0.5 + dPer * i;
				y1 = ZbButtom -[self getZBYPos:tempZb.zb_1  secNum:2 ];
				
				CGContextMoveToPoint(context, x0, y0);
				CGContextAddLineToPoint(context, x1, y1);
				CGContextStrokePath(context);
				
				x0 = x1;
				y0= y1;
			}
			
		}
			break;
		case 18://BOLL
		{
			[[NSColor whiteColor] set];
			tempZb = [m_ZbData objectAtIndex:m_LeftNum];
			x0 = zbRect.origin.x+m_dWidth * 0.5  ;
			y0 = ZbButtom-[self  getZBYPos:tempZb.zb_1 secNum:2 ];
			
			for (int i = 1; i < m_DrawNum && (i+m_LeftNum)<[m_ZbData count]; i++)
			{
				tempZb = [m_ZbData objectAtIndex:(i + m_LeftNum)];
				
				x1 = zbRect.origin.x+m_dWidth * 0.5 + dPer * i;
				y1 = ZbButtom -[self getZBYPos:tempZb.zb_1  secNum:2 ];
				
				CGContextMoveToPoint(context, x0, y0);
				CGContextAddLineToPoint(context, x1, y1);
				CGContextStrokePath(context);
				
				x0 = x1;
				y0= y1;
			}
			
			//画UPper
			[[NSColor yellowColor] set];
			tempZb = [m_ZbData objectAtIndex:m_LeftNum];
			x0 = zbRect.origin.x+m_dWidth * 0.5  ;
			y0 = ZbButtom-[self  getZBYPos:tempZb.zb_2 secNum:2 ];
			
			for (int i = 0; i < m_DrawNum && (i+m_LeftNum)<[m_ZbData count]; i++)
			{
				tempZb = [m_ZbData objectAtIndex:(i + m_LeftNum)];
				
				x1 = zbRect.origin.x+m_dWidth * 0.5 + dPer * i;
				y1 = ZbButtom -[self getZBYPos:tempZb.zb_2  secNum:2 ];
				
				CGContextMoveToPoint(context, x0, y0);
				CGContextAddLineToPoint(context, x1, y1);
				CGContextStrokePath(context);
				
				x0 = x1;
				y0= y1;
			}
			//Lower
			[[NSColor purpleColor] set];
			tempZb = [m_ZbData objectAtIndex:m_LeftNum];
			x0 = zbRect.origin.x+m_dWidth * 0.5  ;
			y0 = ZbButtom-[self  getZBYPos:tempZb.zb_3 secNum:2 ];
			
			for (int i = 0; i < m_DrawNum && (i+m_LeftNum)<[m_ZbData count]; i++)
			{
				tempZb = [m_ZbData objectAtIndex:(i + m_LeftNum)];
				
				x1 = zbRect.origin.x+m_dWidth * 0.5 + dPer * i;
				y1 = ZbButtom -[self getZBYPos:tempZb.zb_3  secNum:2 ];
				
				CGContextMoveToPoint(context, x0, y0);
				CGContextAddLineToPoint(context, x1, y1);
				CGContextStrokePath(context);
				
				x0 = x1;
				y0= y1;
			}
			
			//BAR
			[self drawBARLine:m_context];
		}
			break;
		case 20://SAR
		{
			[self drawBARLine:context];
			//SAR
			[[NSColor whiteColor] set];
			for (int i = 0; i < m_DrawNum && (i+m_LeftNum)<[m_ZbData count]; i++)
			{
				if(i<4)
					continue;
				tempZb = [m_ZbData objectAtIndex:m_LeftNum+i];
				x1 = zbRect.origin.x+m_dWidth * 0.5 + dPer * i;
				y1 = ZbButtom -[self getZBYPos:tempZb.zb_1  secNum:2 ];
				short position=[[positionArray objectAtIndex:i+m_LeftNum] intValue];
				if(position==SAR_LONG)
				{
					CGContextSetRGBStrokeColor(context, 1.0f, 0.0f, 0.0f, 1.0);
					CGContextSetRGBFillColor(context, 1.0f, 0.0f, 0.0f, 1.0);
				}
				else if(position==SAR_SHORT)
				{
					CGContextSetRGBStrokeColor(context, 0.0f, 1.0f, 0.0f, 1.0f);
					CGContextSetRGBFillColor(context, 0.0f, 1.0f, 0.0f, 1.0f);
				}
				CGContextSetLineWidth(context, 1.0f);
				CGContextAddEllipseInRect(context, CGRectMake(x1-2.0f, y1-2.0f, 4.0f, 4.0f));
				CGContextFillEllipseInRect(context, CGRectMake(x1-2.0f, y1-2.0f, 4.0f, 4.0f));
				CGContextStrokePath(context);
				
			}
			
		}
			break;	
		default:
			break;
	}
}

-(void) drawAxis
{
	NSTextField * tempLabel;
	NSString * tempString;
	float tempFloat;
	for (int i =0 ; i < [axisArray count]; i++)
	{
		tempLabel = [axisArray objectAtIndex:i];
		
		if(i < 6)
		{
			tempFloat =  (m_MaxPrice - m_MinPrice) / 6.0f;
			if(currInfo.zsflag)
				tempString = [NSString stringWithFormat:@"%.0f",m_MaxPrice - tempFloat*(i)];
			else
			{
				if(currInfo.dataPre == 2)
					tempString = [NSString stringWithFormat:@"%.2f",m_MaxPrice - tempFloat*(i)];
				else
					tempString = [NSString stringWithFormat:@"%.3f",m_MaxPrice - tempFloat*(i)];
			}
			[[tempLabel cell] setTitle:tempString];
		}	
		else if(i >=6 && i<8)
		{
			if ((m_MaxVol/100.0) >= 1000000000.0f)
			{
				fVolUnit = 10000.0f;
				tempFloat = (m_MaxVol/100.0) /fVolUnit;
				if(currInfo.dataPre == 2)
					tempString = [NSString stringWithFormat:@"%.0f",tempFloat * (1 - (i-6)*0.5)];
				else
					tempString = [NSString stringWithFormat:@"%.0f",tempFloat * (1 - (i-6)*0.5)];
			}
			else if((m_MaxVol/100.0) >= 10000000.0f && (m_MaxVol/100.0)<100000000.0f)
			{
				fVolUnit = 1000.0f;
				tempFloat = (m_MaxVol/100.0) /fVolUnit;
				if(currInfo.dataPre == 2)
					tempString = [NSString stringWithFormat:@"%.0f",tempFloat * (1 - (i-6)*0.5)];
				else
					tempString = [NSString stringWithFormat:@"%.0f",tempFloat * (1 - (i-6)*0.5)];
				
			}
			else if((m_MaxVol/100.0) >= 1000000.0f && (m_MaxVol/100.0)<10000000.0f)
			{
				fVolUnit = 100.0f;
				tempFloat = (m_MaxVol/100.0) /fVolUnit;
				if(currInfo.dataPre == 2)
					tempString = [NSString stringWithFormat:@"%.0f",tempFloat * (1 - (i-6)*0.5)];
				else
					tempString = [NSString stringWithFormat:@"%.0f",tempFloat * (1 - (i-6)*0.5)];
				
			}
			else if((m_MaxVol/100.0) >= 100000.0f && (m_MaxVol/100.0)<1000000.0f)
			{
				fVolUnit =10.0f;
				tempFloat = (m_MaxVol/100.0) /fVolUnit;
				if(currInfo.dataPre == 2)
					tempString = [NSString stringWithFormat:@"%.0f",tempFloat * (1 - (i-6)*0.5)];
				else
					tempString = [NSString stringWithFormat:@"%.0f",tempFloat * (1 - (i-6)*0.5)];
			}
			else
			{
				tempFloat = (m_MaxVol/100.0);
				if(currInfo.dataPre == 2)
					tempString = [NSString stringWithFormat:@"%.0f",tempFloat * (1 - (i-6)*0.5)];
				else
					tempString = [NSString stringWithFormat:@"%.0f",tempFloat * (1 - (i-6)*0.5)];
			}
			[[tempLabel cell] setTitle:tempString];
		}
		else if(i==8)
		{
			if ((m_MaxVol/100.0) >= 1000000000.0f)
			{
				tempString = @"X10000";
			}
			else if((m_MaxVol/100.0) >= 10000000.0f && (m_MaxVol/100.0)<100000000.0f)
			{
				tempString = @"X1000";
			}
			else if((m_MaxVol/100.0) >= 1000000.0f && (m_MaxVol/100.0)<10000000.0f)
			{
				tempString = @"X100";
			}
			else if((m_MaxVol/100.0) >= 100000.0f && (m_MaxVol/100.0)<1000000.0f)
			{
				tempString = @"X10";
			}
			else
			{
                tempString=@"X1";
			}
			[[tempLabel cell] setTitle:tempString];
		}
		else
		{
			
			switch (zbIndex)
			{
				case 0://macd
				{
					tempString = [NSString stringWithFormat:@"%.1f",m_MaxZb * (1 - (i-9)*1)];
					[[tempLabel cell] setTitle:tempString];
					
				}
					break;
				case 1: //kdj
				{
					if(currInfo.dataPre == 2)
						tempString = [NSString stringWithFormat:@"%.2f",m_MaxZb  - (i-9)*(m_MaxZb - m_MinZb)*0.5];
					else
						tempString = [NSString stringWithFormat:@"%.3f",m_MaxZb  - (i-9)*(m_MaxZb - m_MinZb)*0.5];
					[[tempLabel cell] setTitle:tempString];
				}
					break;
				case 2://rsi
				{
					if(currInfo.dataPre == 2)
						tempString = [NSString stringWithFormat:@"%.2f",m_MaxZb  - (i-9)*(m_MaxZb - m_MinZb)*0.5];
					else
						tempString = [NSString stringWithFormat:@"%.3f",m_MaxZb  - (i-9)*(m_MaxZb - m_MinZb)*0.5];
					[[tempLabel cell] setTitle:tempString];
				}
					break;
				case 3://bias
				{
					if(currInfo.dataPre == 2)
						tempString = [NSString stringWithFormat:@"%.2f",m_MaxZb  - (i-9)*(m_MaxZb - m_MinZb)*0.5];
					else
						tempString = [NSString stringWithFormat:@"%.3f",m_MaxZb  - (i-9)*(m_MaxZb - m_MinZb)*0.5];
					[[tempLabel cell] setTitle:tempString];
				}
					break;
				case 4:
				{
					if(currInfo.dataPre == 2)
						tempString = [NSString stringWithFormat:@"%.2f",m_MaxZb  - (i-9)*(m_MaxZb - m_MinZb)*0.5];
					else
						tempString = [NSString stringWithFormat:@"%.3f",m_MaxZb  - (i-9)*(m_MaxZb - m_MinZb)*0.5];
					[[tempLabel cell] setTitle:tempString];
				}
					break;
				case 5:
				{
					float ftemp = m_MaxZb-(i-9)*(m_MaxZb - m_MinZb)*0.5;
					if(currInfo.dataPre == 2)
					{
						if(ftemp>100000000.0f)
							tempString = [NSString stringWithFormat:@"%.0f百万",ftemp/1000000.0f];
						else if(ftemp>1000000.0f&&ftemp<=100000000.0f)
							tempString = [NSString stringWithFormat:@"%.2f万",ftemp/10000.0f];
						else 
							tempString = [NSString stringWithFormat:@"%.2f",ftemp];
							
					}
					else
					{
						if(ftemp>100000000.0f)
							tempString = [NSString stringWithFormat:@"%.0f百万",ftemp/1000000.0f];
						else if(ftemp>1000000.0f&&ftemp<=100000000.0f)
							tempString = [NSString stringWithFormat:@"%.3f万",ftemp/10000.0f];
						else 
							tempString = [NSString stringWithFormat:@"%.3f",ftemp];
					}
					[[tempLabel cell] setTitle:tempString];
				}
					break;
				
				case 6:
				case 7:
				case 10:
				case 11:
				case 12:
				case 13:
				case 14:
				case 15:
				case 16:
				case 17:
				case 18:
				case 19:
				case 20:
				{
					if(currInfo.dataPre == 2)
						tempString = [NSString stringWithFormat:@"%.2f",m_MaxZb-(i-9)*(m_MaxZb - m_MinZb)*0.5];
					else
						tempString = [NSString stringWithFormat:@"%.3f",m_MaxZb-(i-9)*(m_MaxZb - m_MinZb)*0.5];
					[[tempLabel cell] setTitle:tempString];
				}
					break;
					
				case 8:
				{
					if(currInfo.dataPre == 2)
						tempString = [NSString stringWithFormat:@"%.2f",m_MaxZb-(i-9)*(m_MaxZb - m_MinZb)*0.5];
					else
						tempString = [NSString stringWithFormat:@"%.3f",m_MaxZb-(i-9)*(m_MaxZb - m_MinZb)*0.5];
					[[tempLabel cell] setTitle:tempString];
				}
					break;
					
				case 9:
				{
					if(currInfo.dataPre == 2)
						tempString = [NSString stringWithFormat:@"%.2f",m_MaxZb-(i-9)*(m_MaxZb - m_MinZb)*0.5];
					else
						tempString = [NSString stringWithFormat:@"%.3f",m_MaxZb-(i-9)*(m_MaxZb - m_MinZb)*0.5];
					[[tempLabel cell] setTitle:tempString];
				}
					break;
				default:
					break;
			}
		}
	}
	
	if ([m_AnalyseData count] <1) {
		return;
	}
}

-(void) drawCaption
{
	if (m_ReadNum < 1) {
		return;
	}
	
	
	
	NSString * tempString;
	Analyse_Unit * tempAna ;
	Analyse_Unit * tempAnaEx ;
	
	if ((cursor >= [m_AnalyseData count]) || ([m_AnalyseData count] == 0)){
		return;
	}
	
	tempAna = [m_AnalyseData objectAtIndex:cursor];
	if (fxtCross.showFlag) {
		
		if((cursor - 1) > 0){
			tempAnaEx= [m_AnalyseData objectAtIndex:cursor-1];
		}
		else{
			tempAnaEx = [[[Analyse_Unit alloc] init] autorelease];
			tempAnaEx.closep = currInfo.closeP;
		}
		
		int tempInt = cursor - m_LeftNum;
		float tempX = m_dWidth*0.5f + dPer*tempInt;
		
		if (tempX > drawWidth / 2) {
			[detailView setFrame:leftDetailRect];
		}
		else {
			[detailView setFrame:rightDetailRect];
		}
		
		
		[detailView showDetail:tempAna preInfo:tempAnaEx];
		[detailView setNeedsDisplay:YES];
		
	}
	
	NSDictionary * tempAttributes= [eGetData getAttributes:@"Arial" fontSize:15.0f theColor:[NSColor whiteColor] theAliment:NSLeftTextAlignment];

	tempString = @"MA5: ";
	if(currInfo.dataPre == 2)
		tempString = [tempString stringByAppendingString:[NSString stringWithFormat:@"%.2f",tempAna.maFive]];
	else
		tempString = [tempString stringByAppendingString:[NSString stringWithFormat:@"%.3f",tempAna.maFive]];
	NSRect temprect = [tempString boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
	[pMA5 setFrame:NSMakeRect([nameField frame].origin.x+[nameField frame].size.width, viewHeight-2*titleHeight+titleHeight/4, temprect.size.width, titleHeight+titleHeight/2)];
	[[pMA5 cell] setTitle:tempString];
	
	
	tempString = @"MA10:";
	if(currInfo.dataPre == 2)
		tempString = [tempString stringByAppendingString:[NSString stringWithFormat:@"%.2f",tempAna.maTen]];
	else
		tempString = [tempString stringByAppendingString:[NSString stringWithFormat:@"%.3f",tempAna.maTen]];
	temprect = [tempString boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
	[pMA10 setFrame:NSMakeRect([pMA5 frame].origin.x+[pMA5 frame].size.width,viewHeight-2*titleHeight+titleHeight/4,temprect.size.width,titleHeight+titleHeight/2)];
	[[pMA10 cell] setTitle:tempString];
	
	tempString = @"MA20:";
	if(currInfo.dataPre == 2)
		tempString = [tempString stringByAppendingString:[NSString stringWithFormat:@"%.2f",tempAna.maTwn]];
	else
		tempString = [tempString stringByAppendingString:[NSString stringWithFormat:@"%.3f",tempAna.maTwn]];
	temprect = [tempString boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
	[pMA20 setFrame:NSMakeRect([pMA10 frame].origin.x+[pMA10 frame].size.width,viewHeight-2*titleHeight+titleHeight/4,temprect.size.width,titleHeight+titleHeight/2)];
	[[pMA20 cell] setTitle:tempString];
	
	
	
	
	tempString = @"VOL:";
	if (fVolUnit>0) {
		tempString= [tempString stringByAppendingString: [NSString stringWithFormat:@"%.2f",tempAna.volumn/100.0]];
		temprect = [tempString boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
		[vol1 setFrame:NSMakeRect(volRect.origin.x,viewHeight-3*titleHeight-6*m_fPerUnitHeight,temprect.size.width,titleHeight)];
	}
	[[vol1 cell] setTitle:tempString];
	
	zb_Unit * tempVol ;
	if([m_ZbData count]>0){
		tempVol = [m_ZbData objectAtIndex:MIN(cursor,[m_ZbData count]-1)];
		
		tempString = @"VOL5:";
		if (fVolUnit > 0) {
			tempString =[tempString stringByAppendingString: [NSString stringWithFormat:@"%.2f",tempVol.vol_Five/100.0]];
			temprect = [tempString boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
			[vol2 setFrame:NSMakeRect(vol1.frame.origin.x+vol1.bounds.size.width+5.0f,viewHeight-3*titleHeight-6*m_fPerUnitHeight,temprect.size.width,titleHeight)];
		}
		[[vol2 cell] setTitle:tempString];
		
		tempString = @"VOL10:";
		if (fVolUnit > 0) {
			tempString =[tempString stringByAppendingString: [NSString stringWithFormat:@"%.2f",tempVol.vol_Ten/100.0]];
			temprect = [tempString boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
			[vol3 setFrame:NSMakeRect(vol2.frame.origin.x+vol2.bounds.size.width+5.0f,viewHeight-3*titleHeight-6*m_fPerUnitHeight,temprect.size.width,titleHeight)];
			
		}
		[[vol3 cell] setTitle:tempString];
	}
	

	if ([m_ZbData count] < 1 || cursor>=[m_ZbData count]) {
		return;
	}	
	
	switch (zbIndex)
	{
			zb_Unit * tempzb ;
		case 0: //画macd
		{
			if([m_ZbData count]>0){
				tempzb = [m_ZbData objectAtIndex:MIN(cursor,[m_ZbData count]-1)];
				
				tempString = @"DIF:";
				tempString= [tempString stringByAppendingString: [NSString stringWithFormat:@"%.2f",tempzb.macd_DIF]];
				temprect = [tempString boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
				[zb1 setFrame:NSMakeRect(zbRect.origin.x,dateHeight+2*m_fPerUnitHeight,temprect.size.width,titleHeight)];
				[[zb1 cell] setTitle:tempString];
				tempString = @"DEA:";
				tempString =[tempString stringByAppendingString: [NSString stringWithFormat:@"%.2f",tempzb.macd_DEF]];
				temprect = [tempString boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
				[zb2 setFrame:NSMakeRect(zb1.frame.origin.x+zb1.bounds.size.width+5.0f,dateHeight+2*m_fPerUnitHeight,temprect.size.width,titleHeight)];
				[[zb2 cell] setTitle:tempString];
				tempString = @"MACD:";
				tempString =[tempString stringByAppendingString: [NSString stringWithFormat:@"%.2f",tempzb.macd_MACD]];
				temprect = [tempString boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
				[zb3 setFrame:NSMakeRect(zb2.frame.origin.x+zb2.bounds.size.width+5.0f,dateHeight+2*m_fPerUnitHeight,temprect.size.width,titleHeight)];
				[[zb3 cell] setTitle:tempString];
				[zb4 setFrame:NSMakeRect(zb3.frame.origin.x+zb3.bounds.size.width+5.0f,dateHeight+2*m_fPerUnitHeight,temprect.size.width,titleHeight)];
				[[zb4 cell] setTitle:@""];
			}
			
		}
			break;	
		case 1: //画kdj
		{
			tempzb = [m_ZbData objectAtIndex:cursor];
			
			tempString = @"K:";
			tempString= [tempString stringByAppendingString: [NSString stringWithFormat:@"%.2f",tempzb.kdj_K]];
			temprect = [tempString boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
			[zb1 setFrame:NSMakeRect(zbRect.origin.x,dateHeight+2*m_fPerUnitHeight,temprect.size.width,titleHeight)];
			[[zb1 cell] setTitle:tempString];
			
			tempString = @"D:";
			tempString =[tempString stringByAppendingString: [NSString stringWithFormat:@"%.2f",tempzb.kdj_D]];
			temprect = [tempString boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
			[zb2 setFrame:NSMakeRect(zb1.frame.origin.x+zb1.bounds.size.width+5.0f,dateHeight+2*m_fPerUnitHeight,temprect.size.width,titleHeight)];
			[[zb2 cell] setTitle:tempString];
			
			tempString = @"J:";
			tempString =[tempString stringByAppendingString: [NSString stringWithFormat:@"%.2f",tempzb.kdj_J]];
			temprect = [tempString boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
			[zb3 setFrame:NSMakeRect(zb2.frame.origin.x+zb2.bounds.size.width+5.0f,dateHeight+2*m_fPerUnitHeight,temprect.size.width,titleHeight)];
			[[zb3 cell] setTitle:tempString];
			
			[zb4 setFrame:NSMakeRect(zb3.frame.origin.x+zb3.bounds.size.width+5.0f,dateHeight+2*m_fPerUnitHeight,temprect.size.width,titleHeight)];
			[[zb4 cell] setTitle:@""];
		}
			break;
		case 2://画rsi
		{
			tempzb = [m_ZbData objectAtIndex:cursor];
			
			tempString = @"RSI1:";
			tempString= [tempString stringByAppendingString: [NSString stringWithFormat:@"%.2f",tempzb.rsi_RSI1]];
			temprect = [tempString boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
			[zb1 setFrame:NSMakeRect(zbRect.origin.x,dateHeight+2*m_fPerUnitHeight,temprect.size.width,titleHeight)];
			[[zb1 cell] setTitle:tempString];
			
			tempString = @"RSI2:";
			tempString =[tempString stringByAppendingString: [NSString stringWithFormat:@"%.2f",tempzb.rsi_RSI2]];
			temprect = [tempString boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
			[zb2 setFrame:NSMakeRect(zb1.frame.origin.x+zb1.bounds.size.width+5.0f,dateHeight+2*m_fPerUnitHeight,temprect.size.width,titleHeight)];
			[[zb2 cell] setTitle:tempString];
			
			tempString = @"RSI3:";
			tempString =[tempString stringByAppendingString: [NSString stringWithFormat:@"%.2f",tempzb.rsi_RSI3]];
			temprect = [tempString boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
			[zb3 setFrame:NSMakeRect(zb2.frame.origin.x+zb2.bounds.size.width+5.0f,dateHeight+2*m_fPerUnitHeight,temprect.size.width,titleHeight)];
			[[zb3 cell] setTitle:tempString];
			
			[zb4 setFrame:NSMakeRect(zb3.frame.origin.x+zb3.bounds.size.width+5.0f,dateHeight+2*m_fPerUnitHeight,temprect.size.width,titleHeight)];
			[[zb4 cell] setTitle:@""];
		}
			break;
		case 3://画bias
		{
			tempzb = [m_ZbData objectAtIndex:cursor];
			
			tempString = @"BIAS1:";
			tempString= [tempString stringByAppendingString: [NSString stringWithFormat:@"%.2f",tempzb.bias_BIAS1]];
			temprect = [tempString boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
			[zb1 setFrame:NSMakeRect(zbRect.origin.x,dateHeight+2*m_fPerUnitHeight,temprect.size.width,titleHeight)];
			[[zb1 cell] setTitle:tempString];
			
			tempString = @"BIAS2:";
			tempString =[tempString stringByAppendingString: [NSString stringWithFormat:@"%.2f",tempzb.bias_BIAS2]];
			temprect = [tempString boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
			[zb2 setFrame:NSMakeRect(zb1.frame.origin.x+zb1.bounds.size.width+5.0f,dateHeight+2*m_fPerUnitHeight,temprect.size.width,titleHeight)];
			[[zb2 cell] setTitle:tempString];
			
			tempString = @"BIAS3:";
			tempString =[tempString stringByAppendingString: [NSString stringWithFormat:@"%.2f",tempzb.bias_BIAS3]];
			temprect = [tempString boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
			[zb3 setFrame:NSMakeRect(zb2.frame.origin.x+zb2.bounds.size.width+5.0f,dateHeight+2*m_fPerUnitHeight,temprect.size.width,titleHeight)];
			[[zb3 cell] setTitle:tempString];
			
			[zb4 setFrame:NSMakeRect(zb3.frame.origin.x+zb3.bounds.size.width+5.0f,dateHeight+2*m_fPerUnitHeight,temprect.size.width,titleHeight)];
			[[zb4 cell] setTitle:@""];
		}
			break;
		case 4://画DMA
		{
			tempzb = [m_ZbData objectAtIndex:cursor];
			
			tempString = @"DIF:";
			tempString= [tempString stringByAppendingString: [NSString stringWithFormat:@"%.2f",tempzb.zb_1]];
			temprect = [tempString boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
			[zb1 setFrame:NSMakeRect(zbRect.origin.x,dateHeight+2*m_fPerUnitHeight,temprect.size.width,titleHeight)];
			[[zb1 cell] setTitle:tempString];
			
			tempString = @"AMA:";
			tempString =[tempString stringByAppendingString: [NSString stringWithFormat:@"%.2f",tempzb.zb_2]];
			temprect = [tempString boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
			[zb2 setFrame:NSMakeRect(zb1.frame.origin.x+zb1.bounds.size.width+5.0f,dateHeight+2*m_fPerUnitHeight,temprect.size.width,titleHeight)];
			[[zb2 cell] setTitle:tempString];
			
			[zb3 setFrame:NSZeroRect];
			[zb4 setFrame:NSZeroRect];
			[[zb3 cell] setTitle:@""];
			[[zb4 cell] setTitle:@""];
		}
			break;
			
		case 5://画OBV
		{
			tempzb = [m_ZbData objectAtIndex:cursor];
			
			tempString = @"OBV:";
			tempString= [tempString stringByAppendingString: [NSString stringWithFormat:@"%.2f",tempzb.zb_1]];
			temprect = [tempString boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
			[zb1 setFrame:NSMakeRect(zbRect.origin.x,dateHeight+2*m_fPerUnitHeight,temprect.size.width,titleHeight)];
			[[zb1 cell] setTitle:tempString];
			
			tempString = @"MAOBV:";
			tempString =[tempString stringByAppendingString: [NSString stringWithFormat:@"%.2f",tempzb.zb_2]];
			temprect = [tempString boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
			[zb2 setFrame:NSMakeRect(zb1.frame.origin.x+zb1.bounds.size.width+5.0f,dateHeight+2*m_fPerUnitHeight,temprect.size.width,titleHeight)];
			[[zb2 cell] setTitle:tempString];
			
			[zb3 setFrame:NSZeroRect];
			[zb4 setFrame:NSZeroRect];
			[[zb3 cell] setTitle:@""];
			[[zb4 cell] setTitle:@""];
		}
			break;
		case 6://画ROC
		{
			tempzb = [m_ZbData objectAtIndex:cursor];
			
			tempString = @"ROC:";
			tempString= [tempString stringByAppendingString: [NSString stringWithFormat:@"%.2f",tempzb.zb_1]];
			temprect = [tempString boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
			[zb1 setFrame:NSMakeRect(zbRect.origin.x,dateHeight+2*m_fPerUnitHeight,temprect.size.width,titleHeight)];
			[[zb1 cell] setTitle:tempString];
			
			tempString = @"MAROC:";
			tempString =[tempString stringByAppendingString: [NSString stringWithFormat:@"%.2f",tempzb.zb_2]];
			temprect = [tempString boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
			[zb2 setFrame:NSMakeRect(zb1.frame.origin.x+zb1.bounds.size.width+5.0f,dateHeight+2*m_fPerUnitHeight,temprect.size.width,titleHeight)];
			[[zb2 cell] setTitle:tempString];
			
			[zb3 setFrame:NSZeroRect];
			[zb4 setFrame:NSZeroRect];
			[[zb3 cell] setTitle:@""];
			[[zb4 cell] setTitle:@""];
		}
			break;
		case 7://画MTM
		{
			tempzb = [m_ZbData objectAtIndex:cursor];
			
			tempString = @"MTM:";
			tempString= [tempString stringByAppendingString: [NSString stringWithFormat:@"%.2f",tempzb.zb_1]];
			temprect = [tempString boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
			[zb1 setFrame:NSMakeRect(zbRect.origin.x,dateHeight+2*m_fPerUnitHeight,temprect.size.width,titleHeight)];
			[[zb1 cell] setTitle:tempString];
			
			tempString = @"MAMTM:";
			tempString =[tempString stringByAppendingString: [NSString stringWithFormat:@"%.2f",tempzb.zb_2]];
			temprect = [tempString boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
			[zb2 setFrame:NSMakeRect(zb1.frame.origin.x+zb1.bounds.size.width+5.0f,dateHeight+2*m_fPerUnitHeight,temprect.size.width,titleHeight)];
			[[zb2 cell] setTitle:tempString];
			
			[zb3 setFrame:NSZeroRect];
			[zb4 setFrame:NSZeroRect];
			[[zb3 cell] setTitle:@""];
			[[zb4 cell] setTitle:@""];
		}
			break;
		case 8://画CR
		{
			tempzb = [m_ZbData objectAtIndex:cursor];
			
			tempString = @"CR:";
			tempString= [tempString stringByAppendingString: [NSString stringWithFormat:@"%.2f",tempzb.zb_1]];
			temprect = [tempString boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
			[zb1 setFrame:NSMakeRect(zbRect.origin.x,dateHeight+2*m_fPerUnitHeight,temprect.size.width,titleHeight)];
			[[zb1 cell] setTitle:tempString];
			
			tempString = @"MA1:";
			tempString =[tempString stringByAppendingString: [NSString stringWithFormat:@"%.2f",tempzb.zb_2]];
			temprect = [tempString boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
			[zb2 setFrame:NSMakeRect(zb1.frame.origin.x+zb1.bounds.size.width+5.0f,dateHeight+2*m_fPerUnitHeight,temprect.size.width,titleHeight)];
			[[zb2 cell] setTitle:tempString];
			
			tempString = @"MA2:";
			tempString =[tempString stringByAppendingString: [NSString stringWithFormat:@"%.2f",tempzb.zb_3]];
			temprect = [tempString boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
			[zb3 setFrame:NSMakeRect(zb2.frame.origin.x+zb2.bounds.size.width+5.0f,dateHeight+2*m_fPerUnitHeight,temprect.size.width,titleHeight)];
			[[zb3 cell] setTitle:tempString];
			

			[zb4 setFrame:NSZeroRect];
			[[zb4 cell] setTitle:@""];
		}
			break;
		case 9://画DMI
		{
			tempzb = [m_ZbData objectAtIndex:cursor];
			
			tempString = @"PDI:";
			tempString= [tempString stringByAppendingString: [NSString stringWithFormat:@"%.2f",tempzb.zb_1]];
			temprect = [tempString boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
			[zb1 setFrame:NSMakeRect(zbRect.origin.x,dateHeight+2*m_fPerUnitHeight,temprect.size.width,titleHeight)];
			[[zb1 cell] setTitle:tempString];
			
			tempString = @"MDI:";
			tempString =[tempString stringByAppendingString: [NSString stringWithFormat:@"%.2f",tempzb.zb_2]];
			temprect = [tempString boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
			[zb2 setFrame:NSMakeRect(zb1.frame.origin.x+zb1.bounds.size.width+5.0f,dateHeight+2*m_fPerUnitHeight,temprect.size.width,titleHeight)];
			[[zb2 cell] setTitle:tempString];
			
			tempString = @"ADX:";
			tempString =[tempString stringByAppendingString: [NSString stringWithFormat:@"%.2f",tempzb.zb_3]];
			temprect = [tempString boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
			[zb3 setFrame:NSMakeRect(zb2.frame.origin.x+zb2.bounds.size.width+5.0f,dateHeight+2*m_fPerUnitHeight,temprect.size.width,titleHeight)];
			[[zb3 cell] setTitle:tempString];
			
			tempString = @"ADXR:";
			tempString =[tempString stringByAppendingString: [NSString stringWithFormat:@"%.2f",tempzb.zb_4]];
			temprect = [tempString boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
			[zb4 setFrame:NSMakeRect(zb3.frame.origin.x+zb3.bounds.size.width+5.0f,dateHeight+2*m_fPerUnitHeight,temprect.size.width,titleHeight)];
			[[zb4 cell] setTitle:tempString];
		}
			break;
		case 10://画OBV
		{
			tempzb = [m_ZbData objectAtIndex:cursor];
			
			tempString = @"BR:";
			tempString= [tempString stringByAppendingString: [NSString stringWithFormat:@"%.2f",tempzb.zb_1]];
			temprect = [tempString boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
			[zb1 setFrame:NSMakeRect(zbRect.origin.x,dateHeight+2*m_fPerUnitHeight,temprect.size.width,titleHeight)];
			[[zb1 cell] setTitle:tempString];
			
			tempString = @"AR:";
			tempString =[tempString stringByAppendingString: [NSString stringWithFormat:@"%.2f",tempzb.zb_2]];
			temprect = [tempString boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
			[zb2 setFrame:NSMakeRect(zb1.frame.origin.x+zb1.bounds.size.width+5.0f,dateHeight+2*m_fPerUnitHeight,temprect.size.width,titleHeight)];
			[[zb2 cell] setTitle:tempString];
			
			
			[zb3 setFrame:NSZeroRect];
			[zb4 setFrame:NSZeroRect];
			[[zb3 cell] setTitle:@""];
			[[zb4 cell] setTitle:@""];
		}
			break;
		case 11://画VR
		{
			tempzb = [m_ZbData objectAtIndex:cursor];
			
			tempString = @"VR:";
			tempString= [tempString stringByAppendingString: [NSString stringWithFormat:@"%.2f",tempzb.zb_1]];
			temprect = [tempString boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
			[zb1 setFrame:NSMakeRect(zbRect.origin.x,dateHeight+2*m_fPerUnitHeight,temprect.size.width,titleHeight)];
			[[zb1 cell] setTitle:tempString];
			
			tempString = @"MAVR:";
			tempString =[tempString stringByAppendingString: [NSString stringWithFormat:@"%.2f",tempzb.zb_2]];
			temprect = [tempString boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
			[zb2 setFrame:NSMakeRect(zb1.frame.origin.x+zb1.bounds.size.width+5.0f,dateHeight+2*m_fPerUnitHeight,temprect.size.width,titleHeight)];
			[[zb2 cell] setTitle:tempString];
			
			[[zb3 cell] setTitle:@""];
			[[zb4 cell] setTitle:@""];
		}
			break;	
		case 12://画TRIX
		{
			tempzb = [m_ZbData objectAtIndex:cursor];
			
			tempString = @"TRIX:";
			tempString= [tempString stringByAppendingString: [NSString stringWithFormat:@"%.2f",tempzb.zb_1]];
			temprect = [tempString boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
			[zb1 setFrame:NSMakeRect(zbRect.origin.x,dateHeight+2*m_fPerUnitHeight,temprect.size.width,titleHeight)];
			[[zb1 cell] setTitle:tempString];
			
			tempString = @"MATRIX:";
			tempString =[tempString stringByAppendingString: [NSString stringWithFormat:@"%.2f",tempzb.zb_2]];
			temprect = [tempString boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
			[zb2 setFrame:NSMakeRect(zb1.frame.origin.x+zb1.bounds.size.width+5.0f,dateHeight+2*m_fPerUnitHeight,temprect.size.width,titleHeight)];
			[[zb2 cell] setTitle:tempString];
			
			
			[zb3 setFrame:NSZeroRect];
			[zb4 setFrame:NSZeroRect];
			[[zb3 cell] setTitle:@""];
			[[zb4 cell] setTitle:@""];
		}
			break;
		case 13://画EMV
		{
			tempzb = [m_ZbData objectAtIndex:cursor];
			
			tempString = @"EMV:";
			tempString= [tempString stringByAppendingString: [NSString stringWithFormat:@"%.2f",tempzb.zb_1]];
			temprect = [tempString boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
			[zb1 setFrame:NSMakeRect(zbRect.origin.x,dateHeight+2*m_fPerUnitHeight,temprect.size.width,titleHeight)];
			[[zb1 cell] setTitle:tempString];
			
			tempString = @"MAEMV:";
			tempString =[tempString stringByAppendingString: [NSString stringWithFormat:@"%.2f",tempzb.zb_2]];
			temprect = [tempString boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
			[zb2 setFrame:NSMakeRect(zb1.frame.origin.x+zb1.bounds.size.width+5.0f,dateHeight+2*m_fPerUnitHeight,temprect.size.width,titleHeight)];
			[[zb2 cell] setTitle:tempString];
			
			[zb3 setFrame:NSZeroRect];
			[zb4 setFrame:NSZeroRect];
			[[zb3 cell] setTitle:@""];
			[[zb4 cell] setTitle:@""];
		}
			break;
		case 14://画WR
		{
			tempzb = [m_ZbData objectAtIndex:cursor];
			
			tempString = @"WR1:";
			tempString= [tempString stringByAppendingString: [NSString stringWithFormat:@"%.2f",tempzb.zb_1]];
			temprect = [tempString boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
			[zb1 setFrame:NSMakeRect(zbRect.origin.x,dateHeight+2*m_fPerUnitHeight,temprect.size.width,titleHeight)];
			[[zb1 cell] setTitle:tempString];
			
			tempString = @"WR2:";
			tempString =[tempString stringByAppendingString: [NSString stringWithFormat:@"%.2f",tempzb.zb_2]];
			temprect = [tempString boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
			[zb2 setFrame:NSMakeRect(zb1.frame.origin.x+zb1.bounds.size.width+5.0f,dateHeight+2*m_fPerUnitHeight,temprect.size.width,titleHeight)];
			[[zb2 cell] setTitle:tempString];
			
			[zb3 setFrame:NSZeroRect];
			[zb4 setFrame:NSZeroRect];
			[[zb3 cell] setTitle:@""];
			[[zb4 cell] setTitle:@""];
		}
			break;	
		case 15://画CCI
		{
			tempzb = [m_ZbData objectAtIndex:cursor];
			
			tempString = @"CCI:";
			tempString= [tempString stringByAppendingString: [NSString stringWithFormat:@"%.2f",tempzb.zb_1]];
			temprect = [tempString boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
			[zb1 setFrame:NSMakeRect(zbRect.origin.x,dateHeight+2*m_fPerUnitHeight,temprect.size.width,titleHeight)];
			[[zb1 cell] setTitle:tempString];
			[zb2 setFrame:NSZeroRect];
			[[zb2 cell] setTitle:@""];
			
			[zb3 setFrame:NSZeroRect];
			[zb4 setFrame:NSZeroRect];
			[[zb3 cell] setTitle:@""];
			[[zb4 cell] setTitle:@""];
		}
			break;	
		case 16://PSY
		{
			tempzb = [m_ZbData objectAtIndex:cursor];
			
			tempString = @"PSY:";
			tempString= [tempString stringByAppendingString: [NSString stringWithFormat:@"%.2f",tempzb.zb_1]];
			temprect = [tempString boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
			[zb1 setFrame:NSMakeRect(zbRect.origin.x,dateHeight+2*m_fPerUnitHeight,temprect.size.width,titleHeight)];
			[[zb1 cell] setTitle:tempString];
			
			tempString = @"MAPSY:";
			tempString =[tempString stringByAppendingString: [NSString stringWithFormat:@"%.2f",tempzb.zb_2]];
			temprect = [tempString boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
			[zb2 setFrame:NSMakeRect(zb1.frame.origin.x+zb1.bounds.size.width+5.0f,dateHeight+2*m_fPerUnitHeight,temprect.size.width,titleHeight)];
			[[zb2 cell] setTitle:tempString];
			
			[zb3 setFrame:NSZeroRect];
			[zb4 setFrame:NSZeroRect];
			[[zb3 cell] setTitle:@""];
			[[zb4 cell] setTitle:@""];
		}
		case 17://DPO
		{
			tempzb = [m_ZbData objectAtIndex:cursor];
			
			tempString = @"DPO:";
			tempString= [tempString stringByAppendingString: [NSString stringWithFormat:@"%.2f",tempzb.zb_1]];
			temprect = [tempString boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
			[zb1 setFrame:NSMakeRect(zbRect.origin.x,dateHeight+2*m_fPerUnitHeight,temprect.size.width,titleHeight)];
			[[zb1 cell] setTitle:tempString];
			
			tempString = @"MADOP:";
			tempString =[tempString stringByAppendingString: [NSString stringWithFormat:@"%.2f",tempzb.zb_2]];
			temprect = [tempString boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
			[zb2 setFrame:NSMakeRect(zb1.frame.origin.x+zb1.bounds.size.width+5.0f,dateHeight+2*m_fPerUnitHeight,temprect.size.width,titleHeight)];
			[[zb2 cell] setTitle:tempString];
			
			[zb3 setFrame:NSZeroRect];
			[zb4 setFrame:NSZeroRect];
			[[zb3 cell] setTitle:@""];
			[[zb4 cell] setTitle:@""];
		}
			break;
		case 18://画boll
		{
			tempzb = [m_ZbData objectAtIndex:cursor];
			
			tempString = @"BOLL:";
			tempString= [tempString stringByAppendingString: [NSString stringWithFormat:@"%.2f",tempzb.zb_1]];
			temprect = [tempString boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
			[zb1 setFrame:NSMakeRect(zbRect.origin.x,dateHeight+2*m_fPerUnitHeight,temprect.size.width,titleHeight)];
			[[zb1 cell] setTitle:tempString];
			
			tempString = @"UPPER:";
			tempString =[tempString stringByAppendingString: [NSString stringWithFormat:@"%.2f",tempzb.zb_2]];
			temprect = [tempString boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
			[zb2 setFrame:NSMakeRect(zb1.frame.origin.x+zb1.bounds.size.width+5.0f,dateHeight+2*m_fPerUnitHeight,temprect.size.width,titleHeight)];
			[[zb2 cell] setTitle:tempString];
			
			tempString = @"LOWER:";
			tempString =[tempString stringByAppendingString: [NSString stringWithFormat:@"%.2f",tempzb.zb_3]];
			temprect = [tempString boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
			[zb3 setFrame:NSMakeRect(zb2.frame.origin.x+zb2.bounds.size.width+5.0f,dateHeight+2*m_fPerUnitHeight,temprect.size.width,titleHeight)];
			[[zb3 cell] setTitle:tempString];
			
			[zb4 setFrame:NSMakeRect(zb3.frame.origin.x+zb3.bounds.size.width+5.0f,dateHeight+2*m_fPerUnitHeight,temprect.size.width,titleHeight)];
			[[zb4 cell] setTitle:@""];
		}
			break;
		case 19://画ASI
		{
			tempzb = [m_ZbData objectAtIndex:cursor];
			
			tempString = @"ASI:";
			tempString= [tempString stringByAppendingString: [NSString stringWithFormat:@"%.2f",tempzb.zb_1]];
			temprect = [tempString boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
			[zb1 setFrame:NSMakeRect(zbRect.origin.x,dateHeight+2*m_fPerUnitHeight,temprect.size.width,titleHeight)];
			[[zb1 cell] setTitle:tempString];
			
			tempString = @"MAASI:";
			tempString =[tempString stringByAppendingString: [NSString stringWithFormat:@"%.2f",tempzb.zb_2]];
			temprect = [tempString boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
			[zb2 setFrame:NSMakeRect(zb1.frame.origin.x+zb1.bounds.size.width+5.0f,dateHeight+2*m_fPerUnitHeight,temprect.size.width,titleHeight)];
			[[zb2 cell] setTitle:tempString];
			
			[zb3 setFrame:NSZeroRect];
			[zb4 setFrame:NSZeroRect];
			[[zb3 cell] setTitle:@""];
			[[zb4 cell] setTitle:@""];
		}
			break;
		case 20://画SAR
		{
			tempzb = [m_ZbData objectAtIndex:cursor];
			
			tempString = @"SAR:";
			tempString= [tempString stringByAppendingString: [NSString stringWithFormat:@"%.2f",tempzb.zb_1]];
			temprect = [tempString boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
			[zb1 setFrame:NSMakeRect(zbRect.origin.x,dateHeight+2*m_fPerUnitHeight,temprect.size.width,titleHeight)];
			[[zb1 cell] setTitle:tempString];
			[[zb2 cell] setTitle:@""];
			
			[zb3 setFrame:NSZeroRect];
			[zb4 setFrame:NSZeroRect];
			[[zb3 cell] setTitle:@""];
			[[zb4 cell] setTitle:@""];
		}
		default:
			break;
	}
	
}

-(void)layoutLabel{
	nameField = [[NSTextField alloc]init];
	[nameField setEditable:NO];
	[nameField setBackgroundColor:[NSColor blackColor]];
	[nameField setBordered:NO];
	[nameField setFrame:NSMakeRect(0, viewHeight-2*titleHeight+titleHeight/4, 120, titleHeight+titleHeight/2)];
	[[nameField cell] setFont:[NSFont systemFontOfSize:15.0f]];
	[[nameField cell] setTextColor:[NSColor whiteColor]];
	[self addSubview:nameField];
	
	
	pMA5 = [[NSTextField alloc]init];
	[pMA5 setEditable:NO];
	[pMA5 setBackgroundColor:[NSColor blackColor]];
	[pMA5 setBordered:NO];
	[pMA5 setFrame:NSMakeRect([nameField frame].origin.x+[nameField frame].size.width, viewHeight-2*titleHeight+titleHeight/4, 100, titleHeight+titleHeight/2)];
	[[pMA5 cell] setFont:[NSFont systemFontOfSize:13.0f]];
	[[pMA5 cell] setAlignment:NSLeftTextAlignment];
	[[pMA5 cell] setTextColor:[NSColor whiteColor]];
	[self addSubview:pMA5];
	
	pMA10 = [[NSTextField alloc]init];
	[pMA10 setEditable:NO];
	[pMA10 setBackgroundColor:[NSColor blackColor]];
	[pMA10 setBordered:NO];
	[pMA10 setFrame:NSMakeRect([pMA5 frame].origin.x+[pMA5 frame].size.width, viewHeight-2*titleHeight+titleHeight/4, 100, titleHeight+titleHeight/2)];
	[[pMA10 cell] setFont:[NSFont systemFontOfSize:13.0f]];
	[[pMA10 cell] setAlignment:NSLeftTextAlignment];
	[[pMA10 cell] setTextColor:[NSColor yellowColor]];
	[self addSubview:pMA10];
	
	pMA20 = [[NSTextField alloc]init];
	[pMA20 setEditable:NO];
	[pMA20 setBackgroundColor:[NSColor blackColor]];
	[pMA20 setBordered:NO];
	[pMA20 setFrame:NSMakeRect(0, viewHeight-3*titleHeight-6*m_fPerUnitHeight, 100, titleHeight)];
	[[pMA20 cell] setFont:[NSFont systemFontOfSize:13.0f]];
	[[pMA20 cell] setAlignment:NSLeftTextAlignment];
	[[pMA20 cell] setTextColor:[NSColor purpleColor]];
	[self addSubview:pMA20];
	
	
	
	vol1 = [[NSTextField alloc]init];
	[vol1 setEditable:NO];
	[vol1 setBackgroundColor:[NSColor blackColor]];
	[vol1 setBordered:NO];
	[vol1 setFrame:NSMakeRect([nameField frame].origin.x+[nameField frame].size.width, viewHeight-3*titleHeight-6*m_fPerUnitHeight, 100, titleHeight)];
	[[vol1 cell] setFont:[NSFont systemFontOfSize:13.0f]];
	[[vol1 cell] setAlignment:NSLeftTextAlignment];
	[[vol1 cell] setTextColor:[NSColor whiteColor]];
	[self addSubview:vol1];
	
	vol2 = [[NSTextField alloc]init];
	[vol2 setEditable:NO];
	[vol2 setBackgroundColor:[NSColor blackColor]];
	[vol2 setBordered:NO];
	[vol2 setFrame:NSMakeRect([vol1 frame].origin.x+[vol1 frame].size.width, viewHeight-3*titleHeight-6*m_fPerUnitHeight, 100, titleHeight)];
	[[vol2 cell] setFont:[NSFont systemFontOfSize:13.0f]];
	[[vol2 cell] setAlignment:NSLeftTextAlignment];
	[[vol2 cell] setTextColor:[NSColor yellowColor]];
	[self addSubview:vol2];
	
	vol3 = [[NSTextField alloc]init];
	[vol3 setEditable:NO];
	[vol3 setBackgroundColor:[NSColor blackColor]];
	[vol3 setBordered:NO];
	[vol3 setFrame:NSMakeRect([vol2 frame].origin.x+[vol2 frame].size.width, viewHeight-2*titleHeight+titleHeight/4, 100, titleHeight)];
	[[vol3 cell] setFont:[NSFont systemFontOfSize:13.0f]];
	[[vol3 cell] setAlignment:NSLeftTextAlignment];
	[[vol3 cell] setTextColor:[NSColor purpleColor]];
	[self addSubview:vol3];
	
	
	zb1 = [[NSTextField alloc]init];
	[zb1 setEditable:NO];
	[zb1 setBackgroundColor:[NSColor blackColor]];
	[zb1 setBordered:NO];
	[zb1 setFrame:NSMakeRect(0, titleHeight+2*m_fPerUnitHeight, 100, titleHeight)];
	[[zb1 cell] setFont:[NSFont systemFontOfSize:13.0f]];
	[[zb1 cell] setAlignment:NSLeftTextAlignment];
	[[zb1 cell] setTextColor:[NSColor whiteColor]];
	[self addSubview:zb1];
	
	zb2 = [[NSTextField alloc]init];
	[zb2 setEditable:NO];
	[zb2 setBackgroundColor:[NSColor blackColor]];
	[zb2 setBordered:NO];
	[zb2 setFrame:NSMakeRect([zb1 frame].origin.x+[zb1 frame].size.width, titleHeight+2*m_fPerUnitHeight, 100, titleHeight)];
	[[zb2 cell] setFont:[NSFont systemFontOfSize:13.0f]];
	[[zb2 cell] setAlignment:NSLeftTextAlignment];
	[[zb2 cell] setTextColor:[NSColor yellowColor]];
	[self addSubview:zb2];
	
	zb3 = [[NSTextField alloc]init];
	[zb3 setEditable:NO];
	[zb3 setBackgroundColor:[NSColor blackColor]];
	[zb3 setBordered:NO];
	[zb3 setFrame:NSMakeRect([zb2 frame].origin.x+[zb2 frame].size.width, titleHeight+2*m_fPerUnitHeight, 100, titleHeight)];
	[[zb3 cell] setFont:[NSFont systemFontOfSize:13.0f]];
	[[zb3 cell] setAlignment:NSLeftTextAlignment];
	[[zb3 cell] setTextColor:[NSColor purpleColor]];
	[self addSubview:zb3];
	
	zb4 = [[NSTextField alloc]init];
	[zb4 setEditable:NO];
	[zb4 setBackgroundColor:[NSColor blackColor]];
	[zb4 setBordered:NO];
	[zb4 setFrame:NSMakeRect([zb3 frame].origin.x+[zb3 frame].size.width, titleHeight+2*m_fPerUnitHeight, 100, titleHeight)];
	[[zb4 cell] setFont:[NSFont systemFontOfSize:13.0f]];
	[[zb4 cell] setAlignment:NSLeftTextAlignment];
	[[zb4 cell] setTextColor:[NSColor greenColor]];
	[self addSubview:zb4];
	
	
	
	
	//axis
	[axisArray removeAllObjects];
	NSTextField * lTemp;
	for (int i = 0; i< 6; i++) 
	{
		lTemp = [[NSTextField alloc]init];
		[lTemp setEditable:NO];
		[lTemp setBackgroundColor:[NSColor blackColor]];
		[lTemp setBordered:NO];
		[lTemp setFrame:NSMakeRect(drawWidth+2.0f,kLineRect.origin.y+kLineRect.size.height- i*m_fPerUnitHeight-10.0f, RIGHTBLANKHEIGHT-3, 20.0f)];
		[[lTemp cell] setFont:[NSFont systemFontOfSize:13.0f]];
		[[lTemp cell] setAlignment:NSRightTextAlignment];
		[[lTemp cell] setTextColor:[NSColor redColor]];
		[[lTemp cell] setTitle:@""];
		[axisArray addObject:lTemp];
		[self addSubview:lTemp];		
		[lTemp release];
		lTemp=nil;
	}
	
	for (int i = 0; i< 2; i++) 
	{
		lTemp = [[NSTextField alloc]init];
		[lTemp setEditable:NO];
		[lTemp setBackgroundColor:[NSColor blackColor]];
		[lTemp setBordered:NO];
		[lTemp setFrame:NSMakeRect(drawWidth+2.0f,volRect.origin.y+volRect.size.height-titleHeight- i*m_fPerUnitHeight-10.0f, RIGHTBLANKHEIGHT-3, 20.0f)];
		[[lTemp cell] setFont:[NSFont systemFontOfSize:13.0f]];
		[[lTemp cell] setAlignment:NSRightTextAlignment];
		[[lTemp cell] setTextColor:[NSColor redColor]];
		[[lTemp cell] setTitle:@""];
		[axisArray addObject:lTemp];
		[self addSubview:lTemp];		
		[lTemp release];
		lTemp=nil;
	}
	lTemp = [[NSTextField alloc]init];
	[lTemp setEditable:NO];
	[lTemp setBackgroundColor:[NSColor blackColor]];
	[lTemp setBordered:NO];
	[lTemp setFrame:NSMakeRect(drawWidth+2.0f,volRect.origin.y+1, 40, 20.0f-2.0f)];
	[[lTemp cell] setFont:[NSFont systemFontOfSize:10.0f]];
	[[lTemp cell] setAlignment:NSRightTextAlignment];
	[[lTemp cell] setTextColor:[NSColor redColor]];
	[[lTemp cell] setTitle:@""];
	lTemp.tag = 12;
	[axisArray addObject:lTemp];
	[self addSubview:lTemp];		
	[lTemp release];
	lTemp=nil;
	
	
	for (int i = 0; i< 3; i++)
	{
		
		lTemp = [[NSTextField alloc]init];
		[lTemp setEditable:NO];
		[lTemp setBackgroundColor:[NSColor blackColor]];
		[lTemp setBordered:NO];
		[lTemp setFrame:NSMakeRect(drawWidth+2.0f,zbRect.origin.y+zbRect.size.height-titleHeight- i*m_fPerUnitHeight-10.0f, RIGHTBLANKHEIGHT-3, 20.0f)];
		[[lTemp cell] setFont:[NSFont systemFontOfSize:13.0f]];
		[[lTemp cell] setAlignment:NSRightTextAlignment];
		[[lTemp cell] setTextColor:[NSColor redColor]];
		[[lTemp cell] setTitle:@""];
		[axisArray addObject:lTemp];
		[self addSubview:lTemp];		
		[lTemp release];
		lTemp=nil;

	}
	
	
	NSRect buttonFrame;
	buttonFrame.origin.x = zbRect.size.width - 100 ;
	buttonFrame.origin.y = dateHeight+2*m_fPerUnitHeight;
	buttonFrame.size.width = 100;
	buttonFrame.size.height = 20;
	zbButton = [[NSPopUpButton alloc]initWithFrame:buttonFrame pullsDown:NO];
    
	NSMenu * sortMenu = [[NSMenu allocWithZone:[NSMenu menuZone]] initWithTitle:@""];
	NSMenuItem * newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"MACD" action:@selector(zbClickAction:) keyEquivalent:@""];
	[newItem setEnabled:NO];
	[newItem setTarget:self];
	[newItem setTag:0];
	[sortMenu addItem:newItem];
	[newItem release];
	
	
	
	newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"KDJ" action:@selector(zbClickAction:) keyEquivalent:@""];
	[newItem setEnabled:YES];
	[newItem setTarget:self];
	[newItem setTag:1];
	[sortMenu addItem:newItem];
	[newItem release];
	
	newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"RSI" action:@selector(zbClickAction:) keyEquivalent:@""];
	[newItem setEnabled:YES];
	[newItem setTarget:self];
	[newItem setTag:2];
	[sortMenu addItem:newItem];
	[newItem release];
	
	newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"BIAS" action:@selector(zbClickAction:) keyEquivalent:@""];
	[newItem setEnabled:YES];
	[newItem setTarget:self];
	[newItem setTag:3];
	[sortMenu addItem:newItem];
	[newItem release];
	
	newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"DMA" action:@selector(zbClickAction:) keyEquivalent:@""];
	[newItem setEnabled:YES];
	[newItem setTarget:self];
	[newItem setTag:4];
	[sortMenu addItem:newItem];
	[newItem release];
	
	newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"OBV" action:@selector(zbClickAction:) keyEquivalent:@""];
	[newItem setEnabled:YES];
	[newItem setTarget:self];
	[newItem setTag:5];
	[sortMenu addItem:newItem];
	[newItem release];
	
	newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"ROC" action:@selector(zbClickAction:) keyEquivalent:@""];
	[newItem setEnabled:YES];
	[newItem setTarget:self];
	[newItem setTag:6];
	[sortMenu addItem:newItem];
	[newItem release];
	
	//
	newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"MTM" action:@selector(zbClickAction:) keyEquivalent:@""];
	[newItem setEnabled:YES];
	[newItem setTarget:self];
	[newItem setTag:7];
	[sortMenu addItem:newItem];
	[newItem release];
	
	newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"CR" action:@selector(zbClickAction:) keyEquivalent:@""];
	[newItem setEnabled:YES];
	[newItem setTarget:self];
	[newItem setTag:8];
	[sortMenu addItem:newItem];
	[newItem release];
	
	newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"DMI" action:@selector(zbClickAction:) keyEquivalent:@""];
	[newItem setEnabled:YES];
	[newItem setTarget:self];
	[newItem setTag:9];
	[sortMenu addItem:newItem];
	[newItem release];
	
	newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"BRAR" action:@selector(zbClickAction:) keyEquivalent:@""];
	[newItem setEnabled:YES];
	[newItem setTarget:self];
	[newItem setTag:10];
	[sortMenu addItem:newItem];
	[newItem release];
	
	newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"VR" action:@selector(zbClickAction:) keyEquivalent:@""];
	[newItem setEnabled:YES];
	[newItem setTarget:self];
	[newItem setTag:11];
	[sortMenu addItem:newItem];
	[newItem release];
	
	newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"TRIX" action:@selector(zbClickAction:) keyEquivalent:@""];
	[newItem setEnabled:YES];
	[newItem setTarget:self];
	[newItem setTag:12];
	[sortMenu addItem:newItem];
	[newItem release];
	
	newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"EMV" action:@selector(zbClickAction:) keyEquivalent:@""];
	[newItem setEnabled:YES];
	[newItem setTarget:self];
	[newItem setTag:13];
	[sortMenu addItem:newItem];
	[newItem release];
	
	newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"WR" action:@selector(zbClickAction:) keyEquivalent:@""];
	[newItem setEnabled:YES];
	[newItem setTarget:self];
	[newItem setTag:14];
	[sortMenu addItem:newItem];
	[newItem release];
	
	newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"CCI" action:@selector(zbClickAction:) keyEquivalent:@""];
	[newItem setEnabled:YES];
	[newItem setTarget:self];
	[newItem setTag:15];
	[sortMenu addItem:newItem];
	[newItem release];
	
	newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"PSY" action:@selector(zbClickAction:) keyEquivalent:@""];
	[newItem setEnabled:YES];
	[newItem setTarget:self];
	[newItem setTag:16];
	[sortMenu addItem:newItem];
	[newItem release];
	
	newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"DPO" action:@selector(zbClickAction:) keyEquivalent:@""];
	[newItem setEnabled:YES];
	[newItem setTarget:self];
	[newItem setTag:17];
	[sortMenu addItem:newItem];
	[newItem release];
	
	newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"BOLL" action:@selector(zbClickAction:) keyEquivalent:@""];
	[newItem setEnabled:YES];
	[newItem setTarget:self];
	[newItem setTag:18];
	[sortMenu addItem:newItem];
	[newItem release];
	
	newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"ASI" action:@selector(zbClickAction:) keyEquivalent:@""];
	[newItem setEnabled:YES];
	[newItem setTarget:self];
	[newItem setTag:19];
	[sortMenu addItem:newItem];
	[newItem release];
	
	newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"SAR" action:@selector(zbClickAction:) keyEquivalent:@""];
	[newItem setEnabled:YES];
	[newItem setTarget:self];
	[newItem setTag:20];
	[sortMenu addItem:newItem];
	[newItem release];
	
	[zbButton setMenu:sortMenu];
	[self addSubview:zbButton];
	[zbButton release];
	
	
	buttonFrame.origin.x = kLineRect.size.width - 100 ;
	buttonFrame.origin.y = viewHeight-2*titleHeight+titleHeight/4;
	buttonFrame.size.width = 100;
	buttonFrame.size.height = titleHeight+titleHeight/2;
	zqButton = [[NSPopUpButton alloc]initWithFrame:buttonFrame pullsDown:NO];
	NSMenuItem* item = [[NSMenuItem allocWithZone:[self zone]] initWithTitle:@"周期" action:NULL keyEquivalent:@""];
	[[zqButton cell] setMenuItem:item];
	[item release];
	
	sortMenu = [[NSMenu allocWithZone:[NSMenu menuZone]] initWithTitle:@""];
	
	newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"5分钟线" action:@selector(periodClickAction:) keyEquivalent:@""];
	[newItem setEnabled:YES];
	[newItem setTarget:self];
	[newItem setTag:0];
	[sortMenu addItem:newItem];
	[newItem release];
	
	newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"15分钟线" action:@selector(periodClickAction:) keyEquivalent:@""];
	[newItem setEnabled:YES];
	[newItem setTarget:self];
	[newItem setTag:1];
	[sortMenu addItem:newItem];
	[newItem release];
	
	newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"30分钟线" action:@selector(periodClickAction:) keyEquivalent:@""];
	[newItem setEnabled:YES];
	[newItem setTarget:self];
	[newItem setTag:2];
	[sortMenu addItem:newItem];
	[newItem release];
	
	newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"60分钟线" action:@selector(periodClickAction:) keyEquivalent:@""];
	[newItem setEnabled:YES];
	[newItem setTarget:self];
	[newItem setTag:3];
	[sortMenu addItem:newItem];
	[newItem release];
	

	
	newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"日线" action:@selector(periodClickAction:) keyEquivalent:@""];
	[newItem setEnabled:YES];
	[newItem setTarget:self];
	[newItem setTag:4];
	[sortMenu addItem:newItem];
	[newItem release];
	
	newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"周线" action:@selector(periodClickAction:) keyEquivalent:@""];
	[newItem setEnabled:YES];
	[newItem setTarget:self];
	[newItem setTag:5];
	[sortMenu addItem:newItem];
	[newItem release];
	
	newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"月线" action:@selector(periodClickAction:) keyEquivalent:@""];
	[newItem setEnabled:YES];
	[newItem setTarget:self];
	[newItem setTag:6];
	[sortMenu addItem:newItem];
	[newItem release];
	
		
	[zqButton setMenu:sortMenu];
	[self addSubview:zqButton];
	[zqButton release];
	
	
	
	
	buttonFrame.origin.x = kLineRect.size.width - 100 ;
	buttonFrame.origin.y =  dateHeight+titleHeight+4*m_fPerUnitHeight;
	buttonFrame.size.width = 100;
	buttonFrame.size.height = 20;
	fqButton = [[NSPopUpButton alloc]initWithFrame:buttonFrame pullsDown:NO];
	
    item = [[NSMenuItem allocWithZone:[self zone]] initWithTitle:@"不复权" action:NULL keyEquivalent:@""];
	[[fqButton cell] setMenuItem:item];
	[item release];
	
	sortMenu = [[NSMenu allocWithZone:[NSMenu menuZone]] initWithTitle:@""];
	
	newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"不复权" action:@selector(fqClickAction:) keyEquivalent:@""];
	[newItem setEnabled:YES];
	[newItem setTarget:self];
	[newItem setTag:0];
	[sortMenu addItem:newItem];
	[newItem release];
	
	newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"前复权" action:@selector(fqClickAction:) keyEquivalent:@""];
	[newItem setEnabled:YES];
	[newItem setTarget:self];
	[newItem setTag:1];
	[sortMenu addItem:newItem];
	[newItem release];
	
	newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"后复权" action:@selector(fqClickAction:) keyEquivalent:@""];
	[newItem setEnabled:YES];
	[newItem setTarget:self];
	[newItem setTag:2];
	[sortMenu addItem:newItem];
	[newItem release];
	
		
	
	[fqButton setMenu:sortMenu];
	[self addSubview:fqButton];
	[fqButton release];
	
	
}

-(float)getYPos:(float)_value secNum:(int)secNum{
	float nRet;
	if (secNum > 0 ) 
	{
		nRet = viewHeight-titleHeight*2 - ((m_MaxPrice - _value) * m_PricePerUnit);
	}
	else
	{
        if(m_MaxVol==0)
            nRet=m_fPerUnitHeight*2.0f;
        else
            nRet = (_value / m_MaxVol) * m_fPerUnitHeight*2.0f;
		
	}
	return nRet;
	
}

-(float)getZBYPos:(float)_value secNum:(int)secNum{
	float nRet;
	
	if(secNum == 1)
	{
		if (_value>0)
		{
            if((m_MaxZb- m_MinZb)==0)
                nRet = m_fPerUnitHeight +  2.0f*m_fPerUnitHeight;
            else
                nRet = m_fPerUnitHeight + (_value / (m_MaxZb- m_MinZb)) * 2.0f*m_fPerUnitHeight;
		}
		else
		{
            if( (m_MaxZb- m_MinZb)==0)
                nRet = m_fPerUnitHeight -  2.0f*m_fPerUnitHeight;
            else
                nRet = m_fPerUnitHeight - ABSOLUTE_VALUE( (_value / (m_MaxZb- m_MinZb)) * 2.0f*m_fPerUnitHeight);
		}
	}
	else if(secNum == 2)
	{
        if((m_MaxZb-m_MinZb)==0)
            nRet = 2.0f*m_fPerUnitHeight;
        else
            nRet = ((_value - m_MinZb) / (m_MaxZb-m_MinZb)) * 2.0f*m_fPerUnitHeight;
		nRet = nRet * (-1);
	}
	else {
		nRet = 0.0f;
	}

	
	return nRet;
}

#pragma mark 事件相关
- (BOOL) isMultipleTouchEnabled 
{
	return YES;
}

-(CGFloat) distanceBetweenTwoPoints:(CGPoint)fromPoint toPoint:(CGPoint)toPoint {
	
    float lengthX = fromPoint.x - toPoint.x;
    float lengthY = fromPoint.y - toPoint.y;
    return sqrt((lengthX * lengthX) + (lengthY * lengthY));	
}


- (void)periodClickAction:(id)sender{
	periodIndex = [sender tag];
	m_ReadNum = 0;
	[myDelegate changeFXTPara];
	
	
}
- (void)zbClickAction:(id)sender{
	
	zbIndex = [sender tag];
	[self setNeedsDisplay:YES];
}

//fqClickAction
- (void)fqClickAction:(id)sender{
	if (fqFlag != [sender tag]) {
		fqFlag = [sender tag];
		m_ReadNum = 0;
		[myDelegate changeFXTPara];
		
		if (fqFlag == 2) {
			NSAlert* alert = [NSAlert alertWithMessageText: [NSString stringWithFormat:@"注意：当前操作将进行后复权（不推荐后复权，推荐使用前复权）。后复权时，最后的分析数据不进行盘中动态维护"]
											 defaultButton: @"确定"
										   alternateButton: nil
											   otherButton: nil
								 informativeTextWithFormat: @""];
			[alert runModal];
		}
	}
}	


-(void)hisClickAction:(id)sender{

}

#pragma mark tradeSlideDelegate相关
-(void)dealTheDirection:(int)_direction
{
}


#pragma mark actionSheet相关
-(void)OnActionOk:(int)ntag
{
	if(ntag!=1)
		return;
	[self changeZb:nSelectIndex];
}

-(void)OnActionDateOk:(int)ntag date:(NSDate *)seldate
{
	
}


-(void)changeZb:(NSInteger)buttonIndex
{
	if (buttonIndex == 0){
		if(zbIndex != 0){
			zbIndex = 0;
			[self setNeedsDisplay:YES];
		}	
	}
	
	if (buttonIndex == 1){
		if(zbIndex != 1){
			zbIndex = 1;
			[self setNeedsDisplay:YES];
		}	
	}
	
	if (buttonIndex == 2){
		if(zbIndex != 2){
			zbIndex = 2;
			[self setNeedsDisplay:YES];
		}	
	}
	
	if (buttonIndex == 3){
		if(zbIndex != 3){
			zbIndex = 3;
			[self setNeedsDisplay:YES];
		}	
	}
	
	if (buttonIndex == 4)
	{
		if(zbIndex != 4){
			zbIndex = 4;
			[self setNeedsDisplay:YES];
		}	
	}
	if (buttonIndex == 5)
	{
		if(zbIndex != 5){
			zbIndex = 5;
			[self setNeedsDisplay:YES];
		}	
	}
	if (buttonIndex == 6)
	{
		if(zbIndex != 6){
			zbIndex = 6;
			[self setNeedsDisplay:YES];
		}	
	}
	if (buttonIndex == 7)
	{
		if(zbIndex != 7){
			zbIndex = 7;
			[self setNeedsDisplay:YES];
		}	
	}
	if (buttonIndex == 8)
	{
		if(zbIndex != 8){
			zbIndex = 8;
			[self setNeedsDisplay:YES];
		}	
	}
	if (buttonIndex == 9)
	{
		if(zbIndex != 9){
			zbIndex = 9;
			[self setNeedsDisplay:YES];
		}	
	}
	if (buttonIndex == 10)
	{
		if(zbIndex != 10){
			zbIndex = 10;
			[self setNeedsDisplay:YES];
		}	
	}
	if (buttonIndex == 11)
	{
		if(zbIndex != 11){
			zbIndex = 11;
			[self setNeedsDisplay:YES];
		}	
	}
	if (buttonIndex == 12)
	{
		if(zbIndex != 12){
			zbIndex = 12;
			[self setNeedsDisplay:YES];
		}	
	}
	if (buttonIndex == 13)
	{
		if(zbIndex != 13){
			zbIndex = 13;
			[self setNeedsDisplay:YES];
		}	
	}
	if (buttonIndex == 14)
	{
		if(zbIndex != 14){
			zbIndex = 14;
			[self setNeedsDisplay:YES];
		}	
	}
	if (buttonIndex == 15)
	{
		if(zbIndex != 15){
			zbIndex = 15;
			[self setNeedsDisplay:YES];
		}	
	}
	if (buttonIndex == 16)
	{
		if(zbIndex != 16){
			zbIndex = 16;
			[self setNeedsDisplay:YES];
		}	
	}
	if (buttonIndex == 17)
	{
		if(zbIndex != 17){
			zbIndex = 17;
			[self setNeedsDisplay:YES];
		}	
	}
	if (buttonIndex == 18)
	{
		if(zbIndex != 18){
			zbIndex = 18;
			[self setNeedsDisplay:YES];
		}	
	}
	if (buttonIndex == 19)
	{
		if(zbIndex != 19){
			zbIndex = 19;
			[self setNeedsDisplay:YES];
		}	
	}
	if (buttonIndex == 20)
	{
		if(zbIndex != 20){
			zbIndex = 20;
			[self setNeedsDisplay:YES];
		}	
	}
}


#pragma mark 协议显示相关

-(void)showAnalyse:(NSMutableArray *)m_RecAnalyseData currInfo:(SinHqInfo *)_currInfo{
	self.dataFlag = YES;
	cursor = 0;
	m_DrawNum = 0;
	if (currInfo != nil) {
		[currInfo release],currInfo = nil;
		;
	}
	
	currInfo = [_currInfo deepCopy];
	
	[detailView setCurrInfo:currInfo];
	[detailView setShowType:periodIndex];
	
	NSString * tempString;
	switch (periodIndex) {
		case 0:
			tempString = [NSString stringWithFormat:@"%@(5分钟)",currInfo.gpname];
			break;
		case 1:
			tempString = [NSString stringWithFormat:@"%@(15分钟)",currInfo.gpname];
			break;	
		case 2:
			tempString = [NSString stringWithFormat:@"%@(30分钟)",currInfo.gpname];
			break;
		case 3:
			tempString = [NSString stringWithFormat:@"%@(60分钟)",currInfo.gpname];
			break;
		case 4:
			tempString = [NSString stringWithFormat:@"%@(日线)",currInfo.gpname];
			break;
		case 5:
			tempString = [NSString stringWithFormat:@"%@(周线)",currInfo.gpname];
			break;	
		case 6:
			tempString = [NSString stringWithFormat:@"%@(月线)",currInfo.gpname];
			break;		
		default:
			break;
	}
	
	[zqButton selectItemAtIndex:periodIndex];
	[[nameField cell] setTitle:tempString];
	
	[zbButton selectItemAtIndex:zbIndex];
	
	
	oriAmount = currInfo.amount;
	oriVol = currInfo.volume;
	fxtCross.showFlag = FALSE;
	isAllData = NO;
	[fxtCross refreshShow];
	if(m_ReadNum == 0)
	{
		if (m_AnalyseData != nil) {
			[m_AnalyseData removeAllObjects];
			[m_AnalyseData release];
		}
		m_nZoomfreshConunt = 0 ;
		m_AnalyseData = [[NSMutableArray alloc] initWithArray:m_RecAnalyseData];
		[m_ZbData removeAllObjects];
		m_ReadNum = m_ReadNum + [m_RecAnalyseData count];
	}
	else{
	}

	[self prepareData];
	[self calMA];
	[self calIt];
	dataFlag = TRUE;
	[self setNeedsDisplay:YES];
}

//准备画图数据 
-(void)calData
{
	m_LeftNum = 0;
	if (m_DrawNum + m_LeftNum > m_ReadNum) {
		m_DrawNum = m_ReadNum - m_LeftNum;
	}
	
	if(m_ReadNum < m_DrawNum)
		m_DrawNum = m_ReadNum;
	m_LeftNum = MAX(m_ReadNum - m_DrawNum,0);
	cursor = m_LeftNum + m_DrawNum -1;
	dPer  = drawWidth / (float)m_DrawNum;
	
	if(m_DrawNum<10.0f)
		dPer = drawWidth/10.0f;
	if (dPer > 54)
	{
		dPer = 54.0f;
		m_dWidth = dPer * 0.55;
		m_dDistance = dPer * 0.45;
	}
	else if(dPer * 0.55 < 1)
	{
		m_dWidth = dPer -1.0f;
		m_dDistance = 1.0f;
	}
	else
	{
		m_dWidth = dPer * 0.55;
		m_dDistance = dPer * 0.45;
	}
}

-(void)calDataEx
{
		
	if (m_DrawNum + m_LeftNum > m_ReadNum) {
		m_DrawNum = m_ReadNum - m_LeftNum;
	}
	
	if(m_ReadNum < m_DrawNum)
		m_DrawNum = m_ReadNum;

	dPer  = drawWidth / (float)m_DrawNum;
	
	if(m_DrawNum<10.0f)
		dPer = drawWidth/10.0f;
	if (dPer > 54)
	{
		dPer = 54.0f;
		m_dWidth = dPer * 0.55;
		m_dDistance = dPer * 0.45;
	}
	else if(dPer * 0.55 < 1)
	{
		m_dWidth = dPer -1.0f;
		m_dDistance = 1.0f;
	}
	else
	{
		m_dWidth = dPer * 0.55;
		m_dDistance = dPer * 0.45;
	}
}

-(void)calDataZoom
{
	if(m_ReadNum < m_DrawNum)
		m_DrawNum = m_ReadNum;
	cursor = m_LeftNum + m_DrawNum -1;
	dPer  = drawWidth / (float)m_DrawNum;
	
	if(m_DrawNum<20.0f)
		dPer = drawWidth/20.0f;
	if (dPer > 54)
	{
		dPer = 54.0f;
		m_dWidth = dPer * 0.55;
		m_dDistance = dPer * 0.45;
	}
	else if(dPer * 0.55 < 1)
	{
		m_dWidth = dPer -1.0f;
		m_dDistance = 1.0f;
	}
	else
	{
		m_dWidth = dPer * 0.55;
		m_dDistance = dPer * 0.45;
	}
}


-(void)prepareData{
    if(drawIndex>=[drawNumArray count])
        return;
	m_DrawNum = [[drawNumArray objectAtIndex:drawIndex] intValue];
	
	[self calData];
}

//计算均线
-(void)calMA{
	Analyse_Unit * tempFxtUnit;
	Analyse_Unit * tempFxtUnitEx;
	float fxtFive,fxtTen,fxtTwenty,tempFxtSum;
	
	//5日
	for (int i =0; i<m_ReadNum && i<[m_AnalyseData count]; i++)
	{
		
		tempFxtUnit = [m_AnalyseData objectAtIndex:i];
		if ((i-3)>0)
		{
			tempFxtSum=0;
			for (int j= i -4; j<i+1 && j<[m_AnalyseData count]; j++) {
				tempFxtUnitEx = [m_AnalyseData objectAtIndex:j];
				tempFxtSum = tempFxtSum+tempFxtUnitEx.closep;
			}
			fxtFive = tempFxtSum /5;
		}
		else
		{
			fxtFive = 0.00001;
		}
		tempFxtUnit.maFive = fxtFive;
	}
	//十日
	for (int i =0; i<m_ReadNum && i<[m_AnalyseData count]; i++)
	{
		tempFxtUnit = [m_AnalyseData objectAtIndex:i];
		if ((i-8)>0)
		{
			tempFxtUnitEx = [m_AnalyseData objectAtIndex:i-5];
			
			tempFxtSum = tempFxtUnit.maFive+tempFxtUnitEx.maFive;
			
			fxtTen = tempFxtSum /2;
		} 
		else
		{
			fxtTen = 0.00001;
		}
		tempFxtUnit.maTen = fxtTen;
	}
	//20日
	for (int i=0; i<m_ReadNum && i<[m_AnalyseData count]; i++)
	{
		tempFxtUnit = [m_AnalyseData objectAtIndex:i];
		if ((i-18)>0)
		{
			tempFxtUnitEx = [m_AnalyseData objectAtIndex:i-10];
			
			tempFxtSum = tempFxtUnit.maTen+tempFxtUnitEx.maTen;
			
			
			fxtTwenty = tempFxtSum /2;
			
		}
		else
		{
			fxtTwenty = 0.00001;
		}
		tempFxtUnit.maTwn = fxtTwenty;
	}
	
}
//计算成交量
-(void)calVol
{
	zb_Unit * tempZb;
	zb_Unit * tempZbEx;
	Analyse_Unit * tempFxtUnit;
	
	if([m_ZbData count] < m_ReadNum)
	{
		[m_ZbData removeAllObjects];
		for (int i =0; i<m_ReadNum; i++)
		{
			tempZb = [[zb_Unit alloc] init];
			[m_ZbData addObject:tempZb];
			[tempZb release];
		}
	}
	float colFive,colTen,tempColSum;
	//5日
	for (int i =0; i<m_ReadNum && i<[m_ZbData count] && i<[m_AnalyseData count]; i++)
	{
		//
		tempZb = [m_ZbData objectAtIndex:i];
		if ((i-3)>0) {
			tempColSum=0;
			for (int j= i -4; j<i+1 && j<[m_AnalyseData count]; j++) {
				tempFxtUnit = [m_AnalyseData objectAtIndex:j];
				
				tempColSum = tempColSum+tempFxtUnit.volumn;
			}
			colFive = tempColSum /5;
		}
		else
		{
			tempFxtUnit = [m_AnalyseData objectAtIndex:i];
			colFive = tempFxtUnit.volumn;
		}
		tempZb.vol_Five = colFive;
	}
	//十日
	for (int i =0; i<m_ReadNum && i<[m_ZbData count] && i<[m_AnalyseData count]; i++)
	{
		tempZb = [m_ZbData objectAtIndex:i];
		if ((i-8)>0)
		{
			tempZbEx = [m_ZbData objectAtIndex:i-5];
			
			tempColSum = tempZb.vol_Five+tempZbEx.vol_Five;
			
			colTen = tempColSum /2;
		}
		else
		{
			tempFxtUnit = [m_AnalyseData objectAtIndex:i];
			colTen = tempFxtUnit.volumn;
		}
		tempZb.vol_Ten = colTen;
	}
}


//计算指标数据
-(void)calZB{
	
    zb_Unit * tempZb;
	zb_Unit * tempZbEx;
	Analyse_Unit * tempFxtUnit;
	Analyse_Unit * tempFxtUnitEx;
	myCalcZb.m_nDataNum = m_ReadNum;
	short nCount =MIN(m_ReadNum,[m_AnalyseData count]);
	if([m_ZbData count] < m_ReadNum)
	{
		[m_ZbData removeAllObjects];
		for (int i =0; i<m_ReadNum; i++)
		{
			tempZb = [[zb_Unit alloc] init];
			[m_ZbData addObject:tempZb];
			[tempZb release];
		}
	}
	
	switch (zbIndex)
	{
		case 0://MACD
		{
			for (int i =0; i<nCount && i<[m_ZbData count] && i<[m_AnalyseData count]; i++)
			{
				tempZb = [m_ZbData objectAtIndex:i];
				tempFxtUnit = [m_AnalyseData objectAtIndex:i];
				if(i>0)
				{
					tempZbEx = [m_ZbData objectAtIndex:i -1];
					tempZb.macd_Short = ((tempFxtUnit.closep)*2.0f+(tempZbEx.macd_Short)*11.0f)/13.0f;
					tempZb.macd_Long = ((tempFxtUnit.closep)*2.0f+(tempZbEx.macd_Long)*25.0f)/27.0f;

					tempZb.macd_DIF = tempZb.macd_Short -  tempZb.macd_Long;
				}
				else
				{
					tempZb.macd_Short = tempFxtUnit.closep;
					tempZb.macd_Long = tempFxtUnit.closep;
					tempZb.macd_DIF = 0.00001;
				}
			}
			
			for (int i =0; i<nCount && i<[m_ZbData count]; i++)
			{

				tempZb = [m_ZbData objectAtIndex:i];
				
				if (i>0) {
					tempZbEx = [m_ZbData objectAtIndex:i -1];
					tempZb.macd_DEF = ((tempZb.macd_DIF)*2.0f + (tempZbEx.macd_DEF)*8.0f)/10.0f;
				} else {
					tempZb.macd_DEF = 0.00001;
				}
				tempZb.macd_MACD = (tempZb.macd_DIF - tempZb.macd_DEF)*2.0f;
			}
			short nZbData = [m_ZbData count];
			if(nZbData>(m_LeftNum-1) && nZbData > 0)
			{
				tempZb  =[m_ZbData objectAtIndex:MAX_VALUE(m_LeftNum-1,0)];
				m_MaxZb= MAX_VALUE(MAX_VALUE(tempZb.macd_DIF,tempZb.macd_DEF),tempZb.macd_MACD);
				m_MinZb= MIN_VALUE(MIN_VALUE(tempZb.macd_DIF,tempZb.macd_DEF),tempZb.macd_MACD);
				
				for (int i = m_LeftNum; i < m_LeftNum+m_DrawNum && i<[m_ZbData count] && i<[m_AnalyseData count]; i++) {
					if([m_ZbData count] > i ){
						tempZb  =[m_ZbData objectAtIndex:i];
						m_MaxZb= MAX_VALUE(MAX_VALUE(MAX_VALUE(tempZb.macd_DIF,tempZb.macd_DEF),tempZb.macd_MACD),m_MaxZb);
						m_MinZb= MIN_VALUE(MIN_VALUE(MIN_VALUE(tempZb.macd_DIF,tempZb.macd_DEF),tempZb.macd_MACD),m_MinZb);
					}
				}
				
				float m_MACDValue = MAX_VALUE(ABSOLUTE_VALUE(m_MaxZb),ABSOLUTE_VALUE(m_MinZb));
				if(m_MACDValue>=0.5)     m_MACDValue = floor(m_MACDValue)+1;
				else if(m_MACDValue>=0.25 && m_MACDValue<0.5)  m_MACDValue = 0.5;
				else if(m_MACDValue>=0.1 && m_MACDValue<0.25)  m_MACDValue = 0.3;
				else if(m_MACDValue>=0.05 && m_MACDValue<0.1)  m_MACDValue = 0.1;
				else if(m_MACDValue>=0.025 && m_MACDValue<0.05)  m_MACDValue = 0.05;
				else if(m_MACDValue>=0.001 && m_MACDValue<0.0025)  m_MACDValue = 0.003;
				else if(m_MACDValue<0.001)  m_MACDValue = 0.001;
				else ;
				
				m_MaxZb = m_MACDValue;
				m_MinZb = m_MACDValue *(-1);
			}
		}
			break;
		case 1://kdj
		{
			NSMutableArray* tempArrayH = [[NSMutableArray alloc]initWithCapacity:nCount+1];
			NSMutableArray* tempArrayL = [[NSMutableArray alloc]initWithCapacity:nCount+1];
			NSMutableArray* OutArrayH = [[NSMutableArray alloc]initWithCapacity:nCount+1];
			NSMutableArray* OutArrayL = [[NSMutableArray alloc]initWithCapacity:nCount+1];
			for(int i=0;i<nCount && i<[m_AnalyseData count];i++)
			{
				[tempArrayH addObject:[NSString stringWithFormat:@"%f",[[m_AnalyseData objectAtIndex:i] highp]]];
				[tempArrayL addObject:[NSString stringWithFormat:@"%f",[[m_AnalyseData objectAtIndex:i] lowp]]];
				[OutArrayH addObject:[NSString stringWithFormat:@"%f",MEANLESS_DATA]];
				[OutArrayL addObject:[NSString stringWithFormat:@"%f",MEANLESS_DATA]];
			}
			[myCalcZb HHV:OutArrayH In:tempArrayH Parama:9];
			[myCalcZb LLV:OutArrayL In:tempArrayL Parama:9];
			[tempArrayH release];
			[tempArrayL release];
			float fllv=0.0f,fhhv=0.0f;
			for (int i=0; i<nCount && i<[m_ZbData count] && i<[OutArrayH count] && i<[OutArrayL count] && i<[m_AnalyseData count]; i++)
			{
				tempZb=[m_ZbData objectAtIndex:i];
				tempFxtUnit=[m_AnalyseData objectAtIndex:i];
				
				fhhv = [[OutArrayH objectAtIndex:i] floatValue];
				fllv = [[OutArrayL objectAtIndex:i] floatValue];
				if( fllv< MEANLESS_DATA&&fhhv< MEANLESS_DATA)
				{
					if (fabs(fhhv-fllv)<0.00001)
						tempZb.kdj_RSV=50.0f;
					else
						tempZb.kdj_RSV=(tempFxtUnit.closep - fllv)*100.0f/(fhhv-fllv);
				}
                else if(tempFxtUnit.highp-tempFxtUnit.lowp>0.0001)
                    tempZb.kdj_RSV = (tempFxtUnit.closep-tempFxtUnit.lowp)*100.0f/(tempFxtUnit.highp-tempFxtUnit.lowp);
                else
                    tempZb.kdj_RSV=0;
		
			}
			[OutArrayH release];
			[OutArrayL release];
			
			for (int i =0; i<nCount && i<[m_ZbData count]; i++) {
				tempZb = [m_ZbData objectAtIndex:i];
				if (i>0) {
					tempZbEx = [m_ZbData objectAtIndex:i-1];
					tempZb.kdj_K = (tempZb.kdj_RSV + (tempZbEx.kdj_K)*2)/3;
					tempZb.kdj_D = (tempZb.kdj_K + (tempZbEx.kdj_D)*2)/3;
					tempZb.kdj_J =  tempZb.kdj_K*3 - tempZb.kdj_D*2;
				}	
				else {
					tempZb.kdj_K = tempZb.kdj_RSV;
					tempZb.kdj_D = tempZb.kdj_K;
					tempZb.kdj_J =  tempZb.kdj_K*3 - tempZb.kdj_D*2;
				}
			}
			//计算最值
			short nZbData = [m_ZbData count];
			if(nZbData>(m_LeftNum-1))
			{
                if (MAX_VALUE(m_LeftNum-1,7) > [m_ZbData count] -1) {
                    return;
                }
				tempZb  =[m_ZbData objectAtIndex:MAX_VALUE(m_LeftNum-1,7)];
				m_MaxZb= MAX_VALUE(MAX_VALUE(tempZb.kdj_K,tempZb.kdj_D),tempZb.kdj_J);
				m_MinZb= MIN_VALUE(MIN_VALUE(tempZb.kdj_K,tempZb.kdj_D),tempZb.kdj_J);
				
				for (int i = MAX(m_LeftNum,8); i < MAX(m_LeftNum,7)+m_DrawNum && i<[m_AnalyseData count]; i++)
                {
					if([m_ZbData count] > i ){
						tempZb  =[m_ZbData objectAtIndex:i];
						m_MaxZb= MAX_VALUE(MAX_VALUE(MAX_VALUE(tempZb.kdj_K,tempZb.kdj_D),tempZb.kdj_J),m_MaxZb);
						m_MinZb= MIN_VALUE(MIN_VALUE(MIN_VALUE(tempZb.kdj_K,tempZb.kdj_D),tempZb.kdj_J),m_MinZb);
					}
				}
			}
		}
			break;
		case 2://rsi
		{
			tempZb = [m_ZbData objectAtIndex:0];
			tempZb.rsi_RSI1 = 0;
			tempZb.rsi_RSI2 = 0;
			tempZb.rsi_RSI3 = 0;
			for (int i =1; i<nCount; i++) {
				tempFxtUnit = [m_AnalyseData objectAtIndex:i];
				tempFxtUnitEx = [m_AnalyseData objectAtIndex:i-1];
				tempZb = [m_ZbData objectAtIndex:i];
				tempZb.rsi_max = MAX_VALUE((tempFxtUnit.closep - tempFxtUnitEx.closep),0);
				tempZb.rsi_abs = ABSOLUTE_VALUE(tempFxtUnit.closep -tempFxtUnitEx.closep);
			
			}
			
			for (int i =1; i<nCount; i++) {
				tempZb = [m_ZbData objectAtIndex:i];
				
				if (i>1) {
					tempZbEx = [m_ZbData objectAtIndex:i-1];
					tempZb.rsi_max6 = (tempZb.rsi_max+(tempZbEx.rsi_max6)*5)/6;
					tempZb.rsi_abs6 = (tempZb.rsi_abs+(tempZbEx.rsi_abs6)*5)/6;
					tempZb.rsi_RSI1 = (tempZb.rsi_max6*100)/tempZb.rsi_abs6;
					if ((tempZb.rsi_RSI1 < 0.01)||(tempZb.rsi_RSI1>100)){
						tempZb.rsi_RSI1 = 0;
					}
					
					tempZb.rsi_max12 = (tempZb.rsi_max+(tempZbEx.rsi_max12)*11)/12;
					tempZb.rsi_abs12 = (tempZb.rsi_abs+(tempZbEx.rsi_abs12)*11)/12;
					tempZb.rsi_RSI2 = (tempZb.rsi_max12*100)/tempZb.rsi_abs12;
					if ((tempZb.rsi_RSI2 < 0.01)||(tempZb.rsi_RSI2>100)){
						tempZb.rsi_RSI2 = 0;
					}
					
					tempZb.rsi_max24 = (tempZb.rsi_max+(tempZbEx.rsi_max24)*23)/24;
					tempZb.rsi_abs24 = (tempZb.rsi_abs+(tempZbEx.rsi_abs24)*23)/24;
					tempZb.rsi_RSI3 = (tempZb.rsi_max24*100)/tempZb.rsi_abs24;
					if ((tempZb.rsi_RSI3 < 0.01)||(tempZb.rsi_RSI3>100)){
						tempZb.rsi_RSI3 = 0;
					}
				} else {
					tempZb.rsi_max6= tempZb.rsi_max12=tempZb.rsi_max24 = tempZb.rsi_max;
					tempZb.rsi_abs6=tempZb.rsi_abs6=tempZb.rsi_abs6=tempZb.rsi_abs;
					
					tempZb.rsi_RSI1 = (tempZb.rsi_max*100)/tempZb.rsi_abs;
					tempZb.rsi_RSI2 = (tempZb.rsi_max*100)/tempZb.rsi_abs;
					tempZb.rsi_RSI3 = (tempZb.rsi_max*100)/tempZb.rsi_abs;
					
					if ((tempZb.rsi_RSI1 < 0.01)||(tempZb.rsi_RSI1>100)){
						tempZb.rsi_RSI1 = 0;
						tempZb.rsi_RSI2 = 0;
						tempZb.rsi_RSI3 = 0;
					}
				}	
			}
			
			//计算最值
			short nZbData = [m_ZbData count];
			if(nZbData>(m_LeftNum-1))
			{
				tempZb  =[m_ZbData objectAtIndex:MAX_VALUE(m_LeftNum-1,0)];
				m_MaxZb= MAX_VALUE(MAX_VALUE(tempZb.rsi_RSI1,tempZb.rsi_RSI2),tempZb.rsi_RSI3);
				m_MinZb= MIN_VALUE(MIN_VALUE(tempZb.rsi_RSI1,tempZb.rsi_RSI2),tempZb.rsi_RSI3);
				
				for (int i = m_LeftNum; i < m_LeftNum+m_DrawNum ; i++) {
					if([m_ZbData count] > i )
					{
						tempZb  =[m_ZbData objectAtIndex:i];
						m_MaxZb= MAX_VALUE(MAX_VALUE(MAX_VALUE(tempZb.rsi_RSI1,tempZb.rsi_RSI2),tempZb.rsi_RSI3),m_MaxZb);
						m_MinZb= MIN_VALUE(MIN_VALUE(MIN_VALUE(tempZb.rsi_RSI1,tempZb.rsi_RSI2),tempZb.rsi_RSI3),m_MinZb);
					}
				}
			}
		}
			break;
		case 3://BIAS
		{
			
			float tempBiasSum;
			for (int i =0; i<nCount; i++) {
				tempZb = [m_ZbData objectAtIndex:i];
				tempFxtUnit = [m_AnalyseData objectAtIndex:i];
				if ((i-4)>0) 
				{
					tempBiasSum=0;
					for (int j= i -5; j<i+1; j++)
					{
						tempFxtUnitEx = [m_AnalyseData objectAtIndex:j];
						tempBiasSum = tempBiasSum+tempFxtUnitEx.closep;
					}
					tempZb.bias_Six = tempBiasSum /6;
					tempZb.bias_BIAS1 = (tempFxtUnit.closep - tempZb.bias_Six)*100/tempZb.bias_Six;
				} else {
					tempZb.bias_Six = 0;
					tempZb.bias_BIAS1 = 0;
				}
			}
			
			for (int i =0; i<nCount; i++) {
				tempZb = [m_ZbData objectAtIndex:i];
				tempFxtUnit = [m_AnalyseData objectAtIndex:i];
				if ((i-10)>0) {
					tempZbEx = [m_ZbData objectAtIndex:i-6];
					tempBiasSum = tempZb.bias_Six+tempZbEx.bias_Six;
					tempZb.bias_Twe = tempBiasSum /2;
					tempZb.bias_BIAS2 = (tempFxtUnit.closep - tempZb.bias_Twe)*100/tempZb.bias_Twe;
					
				} else {
					tempZb.bias_Twe = 0;
					tempZb.bias_BIAS2 = 0;
				}
			}
			
			for (int i =0; i<nCount; i++) {
				tempZb = [m_ZbData objectAtIndex:i];
				tempFxtUnit = [m_AnalyseData objectAtIndex:i];
				
				if ((i-22)>0) {
					tempZbEx = [m_ZbData objectAtIndex:i-12];
					
					tempBiasSum = tempZb.bias_Twe+tempZbEx.bias_Twe;
					tempZb.bias_Twf = tempBiasSum /2;
					
					tempZb.bias_BIAS3 = (tempFxtUnit.closep - tempZb.bias_Twf)*100/tempZb.bias_Twf;
				} else {
					tempZb.bias_Twf = 0;
					tempZb.bias_Twf = 0;
				}
			}
			//计算最值
			short nZbData = [m_ZbData count];
			if(nZbData>(m_LeftNum-1))
			{
				tempZb  =[m_ZbData objectAtIndex:MAX_VALUE(m_LeftNum-1,0)];
				m_MaxZb= MAX_VALUE(MAX_VALUE(tempZb.bias_BIAS1,tempZb.bias_BIAS2),tempZb.bias_BIAS3);
				m_MinZb= MIN_VALUE(MIN_VALUE(tempZb.bias_BIAS1,tempZb.bias_BIAS2),tempZb.bias_BIAS3);
				
				for (int i = m_LeftNum; i < m_LeftNum+m_DrawNum ; i++) {
					if([m_ZbData count] > i ){
						tempZb  =[m_ZbData objectAtIndex:i];
						m_MaxZb= MAX_VALUE(MAX_VALUE(MAX_VALUE(tempZb.bias_BIAS1,tempZb.bias_BIAS2),tempZb.bias_BIAS3),m_MaxZb);
						m_MinZb= MIN_VALUE(MIN_VALUE(MIN_VALUE(tempZb.bias_BIAS1,tempZb.bias_BIAS2),tempZb.bias_BIAS3),m_MinZb);
					}
				}
			}
		}
			break;
		case 4://DMA
		{
			NSMutableArray* DIFArray=[[NSMutableArray alloc] initWithCapacity:nCount+1];
			NSMutableArray* OutArray=[[NSMutableArray alloc] initWithCapacity:nCount+1];
			
			for(int i=0;i<nCount;i++)
			{
				tempFxtUnit = [m_AnalyseData objectAtIndex:i];
				[OutArray addObject:[NSString stringWithFormat:@"%f",tempFxtUnit.closep]];
				
			}
			NSMutableArray* OutArray1=[[NSMutableArray alloc] initWithArray:OutArray];
			[myCalcZb SMA:OutArray In:nCount Parama:10];
			[myCalcZb SMA:OutArray1 In:nCount Parama:50];
			NSString* strtemp=nil;
			for(int i= 0;i<nCount;i++)
			{
				tempZb = [m_ZbData objectAtIndex:i];
				strtemp=[NSString stringWithFormat:@"%f",[[OutArray objectAtIndex:i] floatValue]-[[OutArray1 objectAtIndex:i] floatValue]];
				[DIFArray addObject:strtemp];
				tempZb.zb_1=[strtemp floatValue];
			}
			NSMutableArray* AMAArray=[[NSMutableArray alloc] initWithArray:DIFArray];
			[myCalcZb SMA:AMAArray In:nCount Parama:10];
			for(int i= 0;i<nCount;i++)
			{
				tempZb = [m_ZbData objectAtIndex:i];
				tempZb.zb_2=[[AMAArray objectAtIndex:i] floatValue];
			}
			[OutArray release];
			[OutArray1 release];
			[DIFArray release];
			[AMAArray release];
			//计算最值
			short nZbData = [m_ZbData count];
			if(nZbData>(m_LeftNum-1))
			{
				tempZb  =[m_ZbData objectAtIndex:MAX_VALUE(m_LeftNum-1,0)];
				m_MaxZb= MAX_VALUE(tempZb.zb_1,tempZb.zb_2);
				m_MinZb= MIN_VALUE(tempZb.zb_1,tempZb.zb_2);
				
				for (int i = m_LeftNum; i < m_LeftNum+m_DrawNum ; i++) {
					if([m_ZbData count] > i ){
						tempZb  =[m_ZbData objectAtIndex:i];
						m_MaxZb= MAX_VALUE(MAX_VALUE(tempZb.zb_1,tempZb.zb_2),m_MaxZb);
						m_MinZb= MIN_VALUE(MIN_VALUE(tempZb.zb_1,tempZb.zb_2),m_MinZb);
					}
				}
			}
		}
			break;
		case 5://OBV
		{
			NSMutableArray* CloseArray=[[NSMutableArray alloc] initWithCapacity:nCount+1];
			for(int i=0;i<nCount;i++)
			{
				tempFxtUnit=[m_AnalyseData objectAtIndex:i];
				[CloseArray addObject:[NSString stringWithFormat:@"%f",tempFxtUnit.closep]];
			}
			NSMutableArray* REFArray=[[NSMutableArray alloc] initWithArray:CloseArray];
			[myCalcZb REF:REFArray In:CloseArray Parama:1];
			
			NSMutableArray* VAArray=[[NSMutableArray alloc] init];
			float fclose,fRef;
			for(int i=0;i<nCount;i++)
			{
				tempFxtUnit=[m_AnalyseData objectAtIndex:i];
				fclose=[[CloseArray objectAtIndex:i] floatValue];
				fRef=[[REFArray objectAtIndex:i] floatValue];
				if(fclose-fRef >0.01)
					[VAArray addObject:[NSString stringWithFormat:@"%d",tempFxtUnit.volumn]];
				else if(fabs(fclose-fRef)<=0.01)
					[VAArray addObject:[NSString stringWithFormat:@"%d",0]];
				else
					[VAArray addObject:[NSString stringWithFormat:@"%d",0-tempFxtUnit.volumn]];
			}
			[REFArray release];
			[CloseArray release];
			NSMutableArray* OBVArray=[[NSMutableArray alloc] initWithArray:VAArray];
			[myCalcZb SUM:OBVArray In:VAArray Parama:0];
			[VAArray release];
			NSMutableArray* MAOBVArray=[[NSMutableArray alloc] initWithArray:OBVArray];
			[myCalcZb SMA:MAOBVArray In:nCount Parama:30];
			for(int i=0;i<nCount;i++)
			{
				tempZb=[m_ZbData objectAtIndex:i];
				tempZb.zb_1=[[OBVArray objectAtIndex:i] intValue];
				tempZb.zb_2=[[MAOBVArray objectAtIndex:i] intValue];
			}
			[OBVArray release];
			[MAOBVArray release];
			
			short nZbData = [m_ZbData count];
			if(nZbData>(m_LeftNum-1))
			{
				tempZb  =[m_ZbData objectAtIndex:MAX_VALUE(m_LeftNum-1,0)];
				m_MaxZb= MAX_VALUE(tempZb.zb_1,tempZb.zb_2);
				m_MinZb= MIN_VALUE(tempZb.zb_1,tempZb.zb_2);
				
				for (int i = m_LeftNum; i < m_LeftNum+m_DrawNum ; i++) {
					if([m_ZbData count] > i ){
						tempZb  =[m_ZbData objectAtIndex:i];
						m_MaxZb= MAX_VALUE(MAX_VALUE(tempZb.zb_1,tempZb.zb_2),m_MaxZb);
						m_MinZb= MIN_VALUE(MIN_VALUE(tempZb.zb_1,tempZb.zb_2),m_MinZb);
					}
				}
			}
		}
			break;
		case 6://ROC
		{
			NSMutableArray* closeArray = [[NSMutableArray alloc]init];
			for (tempFxtUnit in m_AnalyseData)
			{
				[closeArray addObject:[NSString stringWithFormat:@"%f",tempFxtUnit.closep]];
			}
			NSMutableArray* REFArray1=[[NSMutableArray alloc]initWithArray:closeArray];
			NSMutableArray* REFArray2=[[NSMutableArray alloc]initWithArray:closeArray];
			[myCalcZb REF:REFArray1 In:closeArray Parama:12];
			[myCalcZb REF:REFArray2 In:closeArray Parama:12];
			NSMutableArray* ROCArray=[[NSMutableArray alloc]initWithCapacity:nCount+1];
			float fRoc;
			NSString* strtemp;
			for(int i=0;i<nCount;i++)
			{
				tempZb=[m_ZbData objectAtIndex:i];
				fRoc=100.0f*([[closeArray objectAtIndex:i] floatValue]-[[REFArray1 objectAtIndex:i] floatValue])/[[REFArray2 objectAtIndex:i] floatValue];
				strtemp=[NSString stringWithFormat:@"%f",fRoc];
				tempZb.zb_1 = fRoc;
				[ROCArray addObject:strtemp];
			}
			[closeArray release];
			[REFArray1 release];
			[REFArray2 release];
			NSMutableArray* MAROCArray=[[NSMutableArray alloc]initWithArray:ROCArray];
			[ROCArray release];
			[myCalcZb SMA:MAROCArray In:nCount Parama:6];
			for (int i=0; i<nCount; i++)
			{
				tempZb=[m_ZbData objectAtIndex:i];
				tempZb.zb_2=[[MAROCArray objectAtIndex:i] floatValue];
			}
			[MAROCArray release];
			
			short nZbData = [m_ZbData count];
			if(nZbData>(m_LeftNum-1))
			{
				tempZb  =[m_ZbData objectAtIndex:MAX_VALUE(m_LeftNum-1,0)];
				m_MaxZb= MAX_VALUE(tempZb.zb_1,tempZb.zb_2);
				m_MinZb= MIN_VALUE(tempZb.zb_1,tempZb.zb_2);
				
				for (int i = m_LeftNum; i < m_LeftNum+m_DrawNum ; i++) {
					if([m_ZbData count] > i ){
						tempZb  =[m_ZbData objectAtIndex:i];
						m_MaxZb= MAX_VALUE(MAX_VALUE(tempZb.zb_1,tempZb.zb_2),m_MaxZb);
						m_MinZb= MIN_VALUE(MIN_VALUE(tempZb.zb_1,tempZb.zb_2),m_MinZb);
					}
				}
			}
		}
			break;
		case 7://MTM
		{
			NSMutableArray* closeArray=[[NSMutableArray alloc]initWithCapacity:nCount+1];
			for (tempFxtUnit in m_AnalyseData)
				[closeArray addObject:[NSString stringWithFormat:@"%f",tempFxtUnit.closep]];
			NSMutableArray* REFArray=[[NSMutableArray alloc]initWithArray:closeArray];
			[myCalcZb REF:REFArray In:closeArray Parama:12];
			NSMutableArray* MTMArray=[[NSMutableArray alloc] initWithCapacity:nCount+1];
			float fMTM;
			for(int i=0;i<nCount;i++)
			{
				tempZb=[m_ZbData objectAtIndex:i];
				fMTM=[[closeArray objectAtIndex:i] floatValue]-[[REFArray objectAtIndex:i] floatValue];
				[MTMArray addObject:[NSString stringWithFormat:@"%f",fMTM]];
				tempZb.zb_1=fMTM;
			}
			[closeArray release];
			[REFArray release];
			
			NSMutableArray* MAMTM=[[NSMutableArray alloc]initWithArray:MTMArray];
			[MTMArray release];
			[myCalcZb SMA:MAMTM In:nCount Parama:6];
			for (int i=0; i<nCount;i++)
			{
				tempZb=[m_ZbData objectAtIndex:i];
				tempZb.zb_2=[[MAMTM objectAtIndex:i] floatValue];
			}
			[MAMTM release];
			
			short nZbData = [m_ZbData count];
			if(nZbData>(m_LeftNum-1))
			{
				tempZb  =[m_ZbData objectAtIndex:MAX_VALUE(m_LeftNum-1,0)];
				m_MaxZb= MAX_VALUE(tempZb.zb_1,tempZb.zb_2);
				m_MinZb= MIN_VALUE(tempZb.zb_1,tempZb.zb_2);
				
				for (int i = m_LeftNum; i < m_LeftNum+m_DrawNum ; i++) {
					if([m_ZbData count] > i ){
						tempZb  =[m_ZbData objectAtIndex:i];
						m_MaxZb= MAX_VALUE(MAX_VALUE(tempZb.zb_1,tempZb.zb_2),m_MaxZb);
						m_MinZb= MIN_VALUE(MIN_VALUE(tempZb.zb_1,tempZb.zb_2),m_MinZb);
					}
				}
			}
		}
			break;
		case 8://CR
		{
			NSMutableArray* HighArray=[[NSMutableArray alloc]initWithCapacity:nCount+1];
			NSMutableArray* LowArray=[[NSMutableArray alloc]initWithCapacity:nCount+1];
			NSMutableArray* HLArray=[[NSMutableArray alloc]initWithCapacity:nCount+1];
			NSString* tempString;
			for(tempFxtUnit in m_AnalyseData)
			{
				tempString=[NSString stringWithFormat:@"%f",tempFxtUnit.highp];
				[HighArray addObject:tempString];
				tempString=[NSString stringWithFormat:@"%f",tempFxtUnit.lowp];
				[LowArray addObject:tempString];
				tempString=[NSString stringWithFormat:@"%f",tempFxtUnit.highp+tempFxtUnit.lowp];
				[HLArray addObject:tempString];
			}
			
			NSMutableArray* REFArray=[[NSMutableArray alloc]initWithArray:HLArray];
			[myCalcZb REF:REFArray In:HLArray Parama:1];
			[HLArray release];
			NSMutableArray* MIDArray=[[NSMutableArray alloc]init];
			float fMid;
			for(int i=0;i<nCount;i++)
			{
				fMid=[[REFArray objectAtIndex:i] floatValue]/2.0f;
				[MIDArray addObject:[NSString stringWithFormat:@"%f",fMid]];
			}
			NSMutableArray* MAXArray1=[[NSMutableArray alloc]initWithCapacity:nCount+1];
			NSMutableArray* MAXArray2=[[NSMutableArray alloc]initWithCapacity:nCount+1];
			float fmax;
			for(int i=0;i<nCount;i++)
			{
				fmax=MAX(0.0f,[[HighArray objectAtIndex:i] floatValue]-[[MIDArray objectAtIndex:i] floatValue]);
				[MAXArray1 addObject:[NSString stringWithFormat:@"%f",fmax]];
				fmax=MAX(0.0f,[[MIDArray objectAtIndex:i] floatValue]-[[LowArray objectAtIndex:i] floatValue]);
				[MAXArray2 addObject:[NSString stringWithFormat:@"%f",fmax]];
			}
			[HighArray release];
			[LowArray release];
			[MIDArray release];
			NSMutableArray* SUMArray1=[[NSMutableArray alloc]initWithArray:MAXArray1];
			NSMutableArray* SUMArray2=[[NSMutableArray alloc]initWithArray:MAXArray2];
			[myCalcZb SUM:SUMArray1 In:MAXArray1 Parama:26];
			[myCalcZb SUM:SUMArray2 In:MAXArray2 Parama:26];
			for(int i=0;i<nCount;i++)
			{
			}
			[MAXArray1 release];
			[MAXArray2 release];
			NSMutableArray* CRArray=[[NSMutableArray alloc] init];
			float fCR;
			for(int i=0;i<nCount;i++)
			{
				tempZb=[m_ZbData objectAtIndex:i];
				fCR=[[SUMArray1 objectAtIndex:i] floatValue]/[[SUMArray2 objectAtIndex:i] floatValue]*100.0f;

				tempZb.zb_1=fCR;
				[CRArray addObject:[NSString stringWithFormat:@"%f",fCR]];
			}
			[SUMArray1 release];
			[SUMArray2 release];
			NSMutableArray* MAArray=[[NSMutableArray alloc]initWithArray:CRArray];
			[CRArray release];
			[myCalcZb SMA:MAArray In:nCount Parama:10];
			[myCalcZb REF:REFArray In:MAArray Parama:(short)(1.0f+10.0f/2.5f)];
			for(int i=0;i<nCount;i++)
			{
				tempZb=[m_ZbData objectAtIndex:i];
				tempZb.zb_2=[[REFArray objectAtIndex:i] floatValue];
			}
			[myCalcZb SMA:MAArray In:nCount Parama:20];
			[myCalcZb REF:REFArray In:MAArray Parama:(short)(1.0f+20.0f/2.5f)];
			for(int i=0;i<nCount;i++)
			{
				tempZb=[m_ZbData objectAtIndex:i];
				tempZb.zb_3=[[REFArray objectAtIndex:i] floatValue];
			}
			[REFArray release];
			[MAArray release];
			
			short nZbData = [m_ZbData count];
			if(nZbData>(m_LeftNum-1))
			{
				tempZb  =[m_ZbData objectAtIndex:MAX_VALUE(m_LeftNum-1,0)];
				m_MaxZb= MAX_VALUE(MAX_VALUE(tempZb.zb_1,tempZb.zb_2),tempZb.zb_3);
				m_MinZb= MIN_VALUE(MIN_VALUE(tempZb.zb_1,tempZb.zb_2),tempZb.zb_3);
				
				for (int i = m_LeftNum; i < m_LeftNum+m_DrawNum ; i++) {
					if([m_ZbData count] > i ){
						tempZb  =[m_ZbData objectAtIndex:i];
						m_MaxZb= MAX_VALUE(MAX_VALUE(MAX_VALUE(tempZb.zb_1,tempZb.zb_2),tempZb.zb_3),m_MaxZb);
						m_MinZb= MIN_VALUE(MIN_VALUE(MIN_VALUE(tempZb.zb_1,tempZb.zb_2),tempZb.zb_3),m_MinZb);
					}
				}
			}
			
		}
			break;
		case 9:
		{
			NSMutableArray* closeArray=[[NSMutableArray alloc]initWithCapacity:nCount+1];
			NSMutableArray* HighArray=[[NSMutableArray alloc]initWithCapacity:nCount+1];
			NSMutableArray* LowArray=[[NSMutableArray alloc]initWithCapacity:nCount+1];
			for(int i=0;i<nCount;i++)
			{
				tempFxtUnit=[m_AnalyseData objectAtIndex:i];
				[closeArray addObject:[NSString stringWithFormat:@"%f",tempFxtUnit.closep]];
				[HighArray addObject:[NSString stringWithFormat:@"%f",tempFxtUnit.highp]];
				[LowArray addObject:[NSString stringWithFormat:@"%f",tempFxtUnit.lowp]];
			}
			NSMutableArray* REFArray=[[NSMutableArray alloc]initWithArray:closeArray];
			[myCalcZb REF:REFArray In:closeArray Parama:1];
			[closeArray release];
			NSMutableArray* EXPMEMA=[[NSMutableArray alloc]init];
			float fABS1,fABS2,fExpmema;
			for(int i=0;i<MIN(m_ReadNum,[m_AnalyseData count]) && i<[REFArray  count];i++)
			{
				tempFxtUnit=[m_AnalyseData objectAtIndex:i];
				fABS1=fabsf(tempFxtUnit.highp-[[REFArray objectAtIndex:i] floatValue]);
				fABS2=fabsf([[REFArray objectAtIndex:i] floatValue]-tempFxtUnit.lowp);
				fExpmema=(MAX(MAX(tempFxtUnit.highp-tempFxtUnit.lowp,fABS1),fABS2));
				[EXPMEMA addObject:[NSString stringWithFormat:@"%f",fExpmema]];
			}
			if(nCount > 14)
				[myCalcZb EXPMEMA:EXPMEMA In:m_ReadNum Parama:14];
			NSMutableArray* MTR=[[NSMutableArray alloc]initWithArray:EXPMEMA];
			NSMutableArray* HDArray=[[NSMutableArray alloc]init];
			[myCalcZb REF:REFArray In:HighArray Parama:1];
			float fHD;
			for(int i=0;i<MIN(m_ReadNum,[m_AnalyseData count]) && i<[HighArray count] && i<[REFArray count];i++)
			{
				fHD=[[HighArray objectAtIndex:i] floatValue]-[[REFArray objectAtIndex:i] floatValue];
				[HDArray addObject:[NSString stringWithFormat:@"%f",fHD]];
			}
			[HighArray release];
			[myCalcZb REF:REFArray In:LowArray Parama:1];
			NSMutableArray* LDArray=[[NSMutableArray alloc]initWithCapacity:m_ReadNum+1];
			float fLD;
			for(int i=0;i<MIN(m_ReadNum,[m_AnalyseData count]) && i<[LowArray count] && i<[REFArray count];i++)
			{
				fLD=[[REFArray objectAtIndex:i] floatValue]-[[LowArray objectAtIndex:i] floatValue];
				[LDArray addObject:[NSString stringWithFormat:@"%f",fLD]];
			}
			[LowArray release];
			[REFArray release];
			NSMutableArray* DMP=[[NSMutableArray alloc]initWithCapacity:nCount+1];
			NSMutableArray* DMM=[[NSMutableArray alloc]initWithCapacity:nCount+1];
			for(int i=0;i<MIN(m_ReadNum,[m_AnalyseData count]) && i<[HDArray count] && i<[LDArray count];i++)
			{
				fHD=[[HDArray objectAtIndex:i] floatValue];
				fLD=[[LDArray objectAtIndex:i] floatValue];
				if(fHD>0&&fHD>fLD)
					[DMP addObject:[NSString stringWithFormat:@"%f",fHD]];
				else
					[DMP addObject:[NSString stringWithFormat:@"%f",0.0f]];
				if(fLD>0&&fLD>fHD)
					[DMM addObject:[NSString stringWithFormat:@"%f",fLD]];
				else
					[DMM addObject:[NSString stringWithFormat:@"%f",0.0f]];

			}
			[LDArray release];
			[HDArray release];
			if(nCount > 14)
			{
				[myCalcZb EXPMEMA:DMP In:nCount Parama:14];
				[myCalcZb EXPMEMA:DMM In:nCount Parama:14];
			}

			for (int i=0; i<MIN(m_ReadNum,[m_AnalyseData count]) && i<[m_ZbData count] && i<[DMP count] && i<[MTR count] && i<[DMM count]; i++)
			{
				tempZb = [m_ZbData objectAtIndex:i];
				tempZb.zb_1=[[DMP objectAtIndex:i] floatValue]*100.0f/[[MTR objectAtIndex:i] floatValue];
				tempZb.zb_2=[[DMM objectAtIndex:i] floatValue]*100.0f/[[MTR objectAtIndex:i] floatValue];
			}
			[DMM release];
			[MTR release];
			[DMP release];
			NSMutableArray* ADX=[[NSMutableArray alloc] initWithCapacity:nCount+1];
			float fadx;
			for(int i=0;i<MIN(m_ReadNum,[m_AnalyseData count]) && i<[m_ZbData count];i++)
			{
				tempZb=[m_ZbData objectAtIndex:i];
				fadx=fabsf(tempZb.zb_2-tempZb.zb_1)/(tempZb.zb_1+tempZb.zb_2)*100.0f;
				[ADX addObject:[NSString stringWithFormat:@"%f",fadx]];
			}
			[myCalcZb EXPMEMA:ADX In:nCount Parama:6];
			NSMutableArray* ADXR=[[NSMutableArray alloc]initWithArray:ADX];
			if(nCount > 6)
			[myCalcZb EXPMEMA:ADXR In:nCount Parama:6];
			[EXPMEMA release];
			for(int i=0;i<MIN(m_ReadNum,[m_AnalyseData count]) && i<[m_ZbData count] && i<[ADX count] && i<[ADXR count];i++)
			{
				tempZb=[m_ZbData objectAtIndex:i];
				tempZb.zb_3=[[ADX objectAtIndex:i] floatValue];
				tempZb.zb_4=[[ADXR objectAtIndex:i]floatValue];
			}
			[ADX release];
			[ADXR release];
			
			short nZbData = [m_ZbData count];
			if(nZbData>(m_LeftNum-1))
			{
				tempZb  =[m_ZbData objectAtIndex:MAX_VALUE(m_LeftNum-1,0)];
				m_MaxZb= MAX_VALUE( MAX_VALUE(MAX_VALUE(tempZb.zb_1,tempZb.zb_2),tempZb.zb_3),tempZb.zb_4);
				m_MinZb= MIN_VALUE( MIN_VALUE(MIN_VALUE(tempZb.zb_1,tempZb.zb_2),tempZb.zb_3),tempZb.zb_4);
				
				for (int i = m_LeftNum; i < MIN(m_LeftNum+m_DrawNum,[m_AnalyseData count]) ; i++) {
					if([m_ZbData count] > i ){
						tempZb  =[m_ZbData objectAtIndex:i];
						m_MaxZb= MAX_VALUE(MAX_VALUE( MAX_VALUE(MAX_VALUE(tempZb.zb_1,tempZb.zb_2),tempZb.zb_3),tempZb.zb_4),m_MaxZb);
						m_MinZb= MIN_VALUE(MIN_VALUE( MIN_VALUE(MIN_VALUE(tempZb.zb_1,tempZb.zb_2),tempZb.zb_3),tempZb.zb_4),m_MinZb);
					}
				}
			}
			
		}
			break;
		case 10://BRAR
		{
			NSMutableArray* closeArray=[[NSMutableArray alloc]initWithCapacity:nCount+1];
			NSMutableArray* HighArray=[[NSMutableArray alloc]initWithCapacity:nCount+1];
			NSMutableArray* LowArray=[[NSMutableArray alloc]initWithCapacity:nCount+1];
			NSMutableArray* OpenArray=[[NSMutableArray alloc]initWithCapacity:nCount+1];
			for(int i=0;i<MIN(m_ReadNum,[m_AnalyseData count]);i++)
			{
				tempFxtUnit=[m_AnalyseData objectAtIndex:i];
				[closeArray addObject:[NSString stringWithFormat:@"%f",tempFxtUnit.closep]];
				[HighArray addObject:[NSString stringWithFormat:@"%f",tempFxtUnit.highp]];
				[LowArray addObject:[NSString stringWithFormat:@"%f",tempFxtUnit.lowp]];
				[OpenArray addObject:[NSString stringWithFormat:@"%f",tempFxtUnit.openp]];
			}
			NSMutableArray* REFArray=[[NSMutableArray alloc]initWithArray:closeArray];
			[myCalcZb REF:REFArray In:closeArray Parama:1];
			[closeArray release];
			NSMutableArray* MAX1 =[[NSMutableArray alloc]initWithCapacity:nCount+1];
			NSMutableArray* MAX2 =[[NSMutableArray alloc]initWithCapacity:nCount+1];
			float fSum1,fSum2;
			for(int i=0;i<nCount && i<[HighArray count] && i<[REFArray count] && i<[LowArray count];i++)
			{
				fSum1=MAX_VALUE(0.0f,[[HighArray objectAtIndex:i] floatValue]-[[REFArray objectAtIndex:i] floatValue]);
				fSum2=MAX_VALUE(0.0f,[[REFArray objectAtIndex:i]floatValue]-[[LowArray objectAtIndex:i] floatValue]);
				[MAX1 addObject:[NSString stringWithFormat:@"%f",fSum1]];
				[MAX2 addObject:[NSString stringWithFormat:@"%f",fSum2]];
			}
			[REFArray release];
			NSMutableArray* SUM1 =[[NSMutableArray alloc]initWithArray:MAX1];
			NSMutableArray* SUM2 =[[NSMutableArray alloc]initWithArray:MAX2];
			[myCalcZb SUM:SUM1 In:MAX1 Parama:26];
			[myCalcZb SUM:SUM2 In:MAX2 Parama:26];
			[MAX1 release];
			[MAX2 release];
			float fBR;
			for(int i=0;i<nCount && i<[m_ZbData count] && i<[SUM1 count] && i<[SUM2 count];i++)
			{
				tempZb=[m_ZbData objectAtIndex:i];
				fBR=[[SUM1 objectAtIndex:i] floatValue]/[[SUM2 objectAtIndex:i] floatValue]*100.0f;
				tempZb.zb_1=fBR;
			}
			NSMutableArray* HOArray=[[NSMutableArray alloc]initWithCapacity:nCount+1];
			NSMutableArray* OLArray=[[NSMutableArray alloc]initWithCapacity:nCount+1];
			for(int i=0;i<nCount && i<[HighArray count] && i<[OpenArray count] && i<[LowArray count] ;i++)
			{
				[HOArray addObject:[NSString stringWithFormat:@"%f",[[HighArray objectAtIndex:i] floatValue]-[[OpenArray objectAtIndex:i] floatValue]]];
				[OLArray addObject:[NSString stringWithFormat:@"%f",[[OpenArray objectAtIndex:i] floatValue]-[[LowArray objectAtIndex:i] floatValue]]];
			}
			[HighArray release];
			[LowArray release];
			[OpenArray release];
			[myCalcZb SUM:SUM1 In:HOArray Parama:26];
			[myCalcZb SUM:SUM2 In:OLArray Parama:26];
			[HOArray release];
			[OLArray release];
			float fAR;
			for(int i=0;i<nCount && i<[m_ZbData count] && i<[SUM1 count] && i<[SUM2 count];i++)
			{
				tempZb=[m_ZbData objectAtIndex:i];
				fAR = [[SUM1 objectAtIndex:i] floatValue]/[[SUM2 objectAtIndex:i] floatValue]*100.0f;
				tempZb.zb_2=fAR;
			}
			[SUM1 release];
			[SUM2 release];
			short nZbData = [m_ZbData count];
			if(nZbData>(m_LeftNum-1))
			{
				tempZb  =[m_ZbData objectAtIndex:MAX_VALUE(m_LeftNum-1,0)];
				m_MaxZb= MAX_VALUE(tempZb.zb_1,tempZb.zb_2);
				m_MinZb= MIN_VALUE(tempZb.zb_1,tempZb.zb_2);
				
				for (int i = m_LeftNum; i < m_LeftNum+m_DrawNum ; i++) {
					if([m_ZbData count] > i ){
						tempZb  =[m_ZbData objectAtIndex:i];
						m_MaxZb= MAX_VALUE(MAX_VALUE(tempZb.zb_1,tempZb.zb_2),m_MaxZb);
						m_MinZb= MIN_VALUE(MIN_VALUE(tempZb.zb_1,tempZb.zb_2),m_MinZb);
					}
				}
			}
		}
			break;
		case 11:
		{
			NSMutableArray* closeArray=[[NSMutableArray alloc]initWithCapacity:nCount+1];
			NSMutableArray* VolArray=[[NSMutableArray alloc]initWithCapacity:nCount+1];
			for(tempFxtUnit in m_AnalyseData)
			{
				[closeArray addObject:[NSString stringWithFormat:@"%f",tempFxtUnit.closep]];
				[VolArray addObject:[NSString stringWithFormat:@"%d",tempFxtUnit.volumn]];
			}
			NSMutableArray* REFArray=[[NSMutableArray alloc]initWithArray:closeArray];
			[myCalcZb REF:REFArray In:closeArray Parama:1];
			NSMutableArray* SUM = [[NSMutableArray alloc]initWithCapacity:nCount+1];
			float fSum;
			for(int i=0;i<nCount && i<[closeArray  count] && i<[REFArray count] && i<[VolArray count];i++)
			{
				if([[closeArray objectAtIndex:i]floatValue]>[[REFArray objectAtIndex:i] floatValue])
					fSum=(float)[[VolArray objectAtIndex:i] intValue];
				else
					fSum=0.0f;
				[SUM addObject:[NSString stringWithFormat:@"%f",fSum]];
			}
			NSMutableArray* THArray=[[NSMutableArray alloc]initWithArray:SUM];
			[myCalcZb SUM:THArray In:SUM Parama:26];
			[SUM removeAllObjects];
			for(int i=0;i<nCount && i<[closeArray count] && i<[REFArray count] && i<[VolArray count];i++)
			{
				if([[closeArray objectAtIndex:i]floatValue]<[[REFArray objectAtIndex:i] floatValue])
					fSum=(float)[[VolArray objectAtIndex:i] intValue];
				else
					fSum=0.0f;
				[SUM addObject:[NSString stringWithFormat:@"%f",fSum]];
			}
			NSMutableArray* TLArray=[[NSMutableArray alloc]initWithArray:SUM];
			[myCalcZb SUM:TLArray In:SUM Parama:26];
			[SUM removeAllObjects];
			for(int i=0;i<nCount && i<[closeArray count] && i<[REFArray count] && i<[VolArray count];i++)
			{
				if([[closeArray objectAtIndex:i]floatValue]==[[REFArray objectAtIndex:i] floatValue])
					fSum=(float)[[VolArray objectAtIndex:i] intValue];
				else
					fSum=0.0f;
				[SUM addObject:[NSString stringWithFormat:@"%f",fSum]];
			}
			[REFArray release];
			[VolArray release];
			[closeArray release];
			NSMutableArray* TQArray=[[NSMutableArray alloc]initWithArray:SUM];
			[myCalcZb SUM:TQArray In:SUM Parama:26];
			[SUM release];
			NSMutableArray* VRArray=[[NSMutableArray alloc]initWithCapacity:nCount+1];
			float fVR;
			for(int i=0;i<nCount && i<[m_ZbData count] && i<[THArray count] && i<[TQArray count] && i<[TLArray count];i++)
			{
				tempZb=[m_ZbData objectAtIndex:i];
				fVR = 100.0f*([[THArray objectAtIndex:i] floatValue]*2.0f +[[TQArray objectAtIndex:i] floatValue])/([[TLArray objectAtIndex:i] floatValue]*2.0f+[[TQArray objectAtIndex:i] floatValue]);
				[VRArray addObject:[NSString stringWithFormat:@"%f",fVR]];
				tempZb.zb_1=fVR;

			}
			[THArray release];
			[TLArray release];
			[TQArray release];
			NSMutableArray*MAVR = [[NSMutableArray alloc]initWithArray:VRArray];
			[VRArray release];
			
			[myCalcZb SMA:MAVR In:nCount Parama:6];
			for(int i=0;i<nCount && i<[m_ZbData count] && i<[MAVR count];i++)
			{
				tempZb=[m_ZbData objectAtIndex:i];
				tempZb.zb_2=[[MAVR objectAtIndex:i]floatValue];
			}
			[MAVR release];
			short nZbData = [m_ZbData count];
			if(nZbData>(m_LeftNum-1))
			{
				tempZb  =[m_ZbData objectAtIndex:MAX_VALUE(m_LeftNum-1,0)];
				m_MaxZb= MAX_VALUE(tempZb.zb_1,tempZb.zb_2);
				m_MinZb= MIN_VALUE(tempZb.zb_1,tempZb.zb_2);
				
				for (int i = m_LeftNum; i < m_LeftNum+m_DrawNum ; i++) {
					if([m_ZbData count] > i ){
						tempZb  =[m_ZbData objectAtIndex:i];
						m_MaxZb= MAX_VALUE(MAX_VALUE(tempZb.zb_1,tempZb.zb_2),m_MaxZb);
						m_MinZb= MIN_VALUE(MIN_VALUE(tempZb.zb_1,tempZb.zb_2),m_MinZb);
					}
				}
			}
		}
			break;
			
		case 12:
		{
			NSMutableArray* closeArray=[[NSMutableArray alloc]initWithCapacity:nCount+1];
			for(tempFxtUnit in m_AnalyseData)
				[closeArray addObject:[NSString stringWithFormat:@"%f",tempFxtUnit.closep]];
			NSMutableArray* EMA=[[NSMutableArray alloc]initWithArray:closeArray];
			[closeArray release];
			[myCalcZb EMA:EMA In:nCount Parama:12];
			[myCalcZb EMA:EMA In:nCount Parama:12];
			[myCalcZb EMA:EMA In:nCount Parama:12];
			NSMutableArray* MTR=[[NSMutableArray alloc]initWithArray:EMA];
			[EMA release];
			NSMutableArray* REFArray=[[NSMutableArray alloc]initWithArray:MTR];
			[myCalcZb REF:REFArray In:MTR Parama:1];
			NSMutableArray* TRIX=[[NSMutableArray alloc] initWithCapacity:nCount+1];
			float fTRIX;
			for(int i=0;i<nCount && i<[m_ZbData  count] && i<[MTR count] && i<[REFArray count] ;i++)
			{
				fTRIX=([[MTR objectAtIndex:i] floatValue]-[[REFArray objectAtIndex:i] floatValue])/[[REFArray objectAtIndex:i] floatValue]*100.0f;
				tempZb = [m_ZbData objectAtIndex:i];
				tempZb.zb_1=fTRIX;
				[TRIX addObject:[NSString stringWithFormat:@"%f",fTRIX]];
			}
			[REFArray release];
			[MTR release];
			NSMutableArray* MATRIX=[[NSMutableArray alloc]initWithArray:TRIX];
			[TRIX release];
			[myCalcZb SMA:MATRIX In:nCount Parama:9];
			for(int i=0;i<nCount && i<[m_ZbData count] && i<[MATRIX count];i++)
			{
				tempZb=[m_ZbData objectAtIndex:i];
				tempZb.zb_2=[[MATRIX objectAtIndex:i] floatValue];
			}
			[MATRIX release];
			short nZbData = [m_ZbData count];
			if(nZbData>(m_LeftNum-1))
			{
				tempZb  =[m_ZbData objectAtIndex:MAX_VALUE(m_LeftNum-1,0)];
				m_MaxZb= MAX_VALUE(tempZb.zb_1,tempZb.zb_2);
				m_MinZb= MIN_VALUE(tempZb.zb_1,tempZb.zb_2);
				
				for (int i = m_LeftNum; i < m_LeftNum+m_DrawNum ; i++) {
					if([m_ZbData count] > i ){
						tempZb  =[m_ZbData objectAtIndex:i];
						m_MaxZb= MAX_VALUE(MAX_VALUE(tempZb.zb_1,tempZb.zb_2),m_MaxZb);
						m_MinZb= MIN_VALUE(MIN_VALUE(tempZb.zb_1,tempZb.zb_2),m_MinZb);
					}
				}
			}
			
		}
			break;
		case 13://EMV
		{
			NSMutableArray* VolArray=[[NSMutableArray alloc]initWithCapacity:nCount+1];
			NSMutableArray* HALArray=[[NSMutableArray alloc]initWithCapacity:nCount+1];
			NSMutableArray* HSLArray=[[NSMutableArray alloc]initWithCapacity:nCount+1];
			for(int i=0;i<nCount && i<[m_AnalyseData count];i++)
			{
				tempFxtUnit=[m_AnalyseData objectAtIndex:i];
				[VolArray addObject:[NSString stringWithFormat:@"%f",(float)tempFxtUnit.volumn]];
				[HALArray addObject:[NSString stringWithFormat:@"%f",tempFxtUnit.lowp+tempFxtUnit.highp]];
				[HSLArray addObject:[NSString stringWithFormat:@"%f",tempFxtUnit.highp-tempFxtUnit.lowp]];
			}
			NSMutableArray* SMA=[[NSMutableArray alloc]initWithArray:VolArray];
			[myCalcZb SMA:SMA In:nCount Parama:14];
			NSMutableArray* VOLUME=[[NSMutableArray alloc]initWithCapacity:nCount+1];
			float fVolume;
			for(int i=0;i<nCount && i<[SMA count] && i<[VolArray count];i++)
			{
				fVolume=[[SMA objectAtIndex:i] floatValue]/(float)[[VolArray objectAtIndex:i]intValue];
				[VOLUME addObject:[NSString stringWithFormat:@"%f",fVolume]];
			}
			[VolArray release];
			NSMutableArray* REFArray=[[NSMutableArray alloc]initWithArray:HALArray];
			[myCalcZb REF:REFArray In:HALArray Parama:1];
			NSMutableArray* MID=[[NSMutableArray alloc] initWithCapacity:nCount+1];
			float fMID;
			for(int i=0;i<nCount && i<[HALArray count] && i<[REFArray count] && i<[HALArray count];i++)
			{
				fMID=100.0f*([[HALArray objectAtIndex:i] floatValue]-[[REFArray objectAtIndex:i] floatValue])/[[HALArray objectAtIndex:i] floatValue];
				[MID addObject:[NSString stringWithFormat:@"%f",fMID]];
			}
			[HALArray release];
			[REFArray release];

			[SMA removeAllObjects];
			[SMA addObjectsFromArray:HSLArray];
			[myCalcZb SMA:SMA In:nCount Parama:14];
			NSMutableArray* EMV=[[NSMutableArray alloc] initWithCapacity:nCount+1];
			float fEMV;
			for(int i=0;i<nCount && i<[MID count] && i<[VOLUME count] && i<[HSLArray count] && i<[SMA count];i++)
			{
				fEMV=[[MID objectAtIndex:i] floatValue]*[[VOLUME objectAtIndex:i] floatValue]*[[HSLArray objectAtIndex:i] floatValue]/[[SMA objectAtIndex:i] floatValue];
				[EMV addObject:[NSString stringWithFormat:@"%f",fEMV]];
			}
			[MID release];
			[HSLArray release];
			[SMA release];
			[VOLUME release];
			[myCalcZb SMA:EMV In:nCount Parama:14];
			NSMutableArray* MAEMV =[[NSMutableArray alloc]initWithArray:EMV];
			[myCalcZb SMA:MAEMV In:nCount Parama:9];
			
			for(int i=0;i<nCount && i<[m_ZbData count] && i<[EMV count] && i<[MAEMV count];i++)
			{
				tempZb=[m_ZbData objectAtIndex:i];
				tempZb.zb_1=[[EMV objectAtIndex:i] floatValue];
				tempZb.zb_2=[[MAEMV objectAtIndex:i] floatValue];
			}
			[EMV release];
			[MAEMV release];
			short nZbData = [m_ZbData count];
			if(nZbData>(m_LeftNum-1))
			{
				tempZb  =[m_ZbData objectAtIndex:MAX_VALUE(m_LeftNum-1,0)];
				m_MaxZb= MAX_VALUE(tempZb.zb_1,tempZb.zb_2);
				m_MinZb= MIN_VALUE(tempZb.zb_1,tempZb.zb_2);
				
				for (int i = m_LeftNum; i < m_LeftNum+m_DrawNum ; i++) {
					if([m_ZbData count] > i ){
						tempZb  =[m_ZbData objectAtIndex:i];
						m_MaxZb= MAX_VALUE(MAX_VALUE(tempZb.zb_1,tempZb.zb_2),m_MaxZb);
						m_MinZb= MIN_VALUE(MIN_VALUE(tempZb.zb_1,tempZb.zb_2),m_MinZb);
					}
				}
			}
			
		}
			break;
			
		case 14://WR
		{
			NSMutableArray* closeArray=[[NSMutableArray alloc]initWithCapacity:nCount+1];
			NSMutableArray* HighArray=[[NSMutableArray alloc]initWithCapacity:nCount+1];
			NSMutableArray* LowArray=[[NSMutableArray alloc]initWithCapacity:nCount+1];
			for(int i=0;i<nCount && i<[m_AnalyseData count];i++)
			{
				tempFxtUnit=[m_AnalyseData objectAtIndex:i];
				[closeArray addObject:[NSString stringWithFormat:@"%f",tempFxtUnit.closep]];
				[HighArray addObject:[NSString stringWithFormat:@"%f",tempFxtUnit.highp]];
				[LowArray addObject:[NSString stringWithFormat:@"%f",tempFxtUnit.lowp]];
			}
			
			NSMutableArray* HHVArray1=[[NSMutableArray alloc]initWithArray:HighArray];
			NSMutableArray* HHVArray2=[[NSMutableArray alloc]initWithArray:HighArray];
			NSMutableArray* LLVArray1=[[NSMutableArray alloc]initWithArray:LowArray];
			NSMutableArray* LLVArray2=[[NSMutableArray alloc]initWithArray:LowArray];
			[myCalcZb HHV:HHVArray1 In:HighArray Parama:10];
			[myCalcZb LLV:LLVArray1 In:LowArray Parama:10];
			[myCalcZb HHV:HHVArray2 In:HighArray Parama:6];
			[myCalcZb LLV:LLVArray2 In:LowArray Parama:6];
			[HighArray release];
			[LowArray release];
			float fWR1,fWR2,fhhv1,fhhv2,fllv1,fllv2,fclose;
			for(int i=0;i<nCount && i<[HHVArray1 count] && i<[HHVArray2 count] && i<[LLVArray1 count] && i<[LLVArray2 count] && i<[closeArray count];i++)
			{
				fhhv1=[[HHVArray1 objectAtIndex:i] floatValue];
				fhhv2=[[HHVArray2 objectAtIndex:i] floatValue];
				fllv1=[[LLVArray1 objectAtIndex:i] floatValue];
				fllv2=[[LLVArray2 objectAtIndex:i] floatValue];
				fclose=[[closeArray objectAtIndex:i] floatValue];
				fWR1=100.0f*(fhhv1-fclose)/(fhhv1-fllv1);
				fWR2=100.0f*(fhhv2-fclose)/(fhhv2-fllv2);
				tempZb=[m_ZbData objectAtIndex:i];
				tempZb.zb_1=fWR1;
				tempZb.zb_2=fWR2;
			}
			[closeArray release];
			[HHVArray1 release];
			[HHVArray2 release];
			[LLVArray1 release];
			[LLVArray2 release];
			
			short nZbData = [m_ZbData count];
			if(nZbData>(m_LeftNum-1))
			{
				tempZb  =[m_ZbData objectAtIndex:MAX_VALUE(m_LeftNum-1,0)];
				m_MaxZb= MAX_VALUE(tempZb.zb_1,tempZb.zb_2);
				m_MinZb= MIN_VALUE(tempZb.zb_1,tempZb.zb_2);
				
				for (int i = m_LeftNum; i < m_LeftNum+m_DrawNum ; i++) {
					if([m_ZbData count] > i ){
						tempZb  =[m_ZbData objectAtIndex:i];
						m_MaxZb= MAX_VALUE(MAX_VALUE(tempZb.zb_1,tempZb.zb_2),m_MaxZb);
						m_MinZb= MIN_VALUE(MIN_VALUE(tempZb.zb_1,tempZb.zb_2),m_MinZb);
					}
				}
			}
			
		}
			break;
			
		case 15:
		{
			NSMutableArray* TYP=[[NSMutableArray alloc]initWithCapacity:nCount+1];
			float fTyp;
			for(int i=0;i<nCount && i<[m_AnalyseData count];i++)
			{
				tempFxtUnit=[m_AnalyseData objectAtIndex:i];
				fTyp=(tempFxtUnit.closep+tempFxtUnit.lowp+tempFxtUnit.highp)/3.0f;
				[TYP addObject:[NSString stringWithFormat:@"%f",fTyp]];
			}
			NSMutableArray* SMAArray=[[NSMutableArray alloc]initWithArray:TYP];
			[myCalcZb SMA:SMAArray In:nCount Parama:14];
			
			NSMutableArray* AVEDEVArray=[[NSMutableArray alloc]initWithArray:TYP];
			[myCalcZb AVEDEV:AVEDEVArray In:TYP Parama:14];
			float CCI;
			for(int i=0;i<nCount && i<[m_ZbData count] && i<[TYP count] && i<[SMAArray count] && i<[AVEDEVArray count];i++)
			{
				CCI = ([[TYP objectAtIndex:i] floatValue]-[[SMAArray objectAtIndex:i] floatValue])/(0.015*[[AVEDEVArray objectAtIndex:i] floatValue]);
				tempZb=[m_ZbData objectAtIndex:i];
				tempZb.zb_1=CCI;
			}
			[TYP release];
			[SMAArray release];
			[AVEDEVArray release];
			short nZbData = [m_ZbData count];
			if(nZbData>(m_LeftNum-1))
			{
				tempZb  =[m_ZbData objectAtIndex:MAX_VALUE(m_LeftNum-1,0)];
				m_MaxZb= tempZb.zb_1;
				m_MinZb= tempZb.zb_1;
				
				for (int i = m_LeftNum; i < m_LeftNum+m_DrawNum ; i++) {
					if([m_ZbData count] > i ){
						tempZb  =[m_ZbData objectAtIndex:i];
						m_MaxZb= MAX_VALUE(tempZb.zb_1,m_MaxZb);
						m_MinZb= MIN_VALUE(tempZb.zb_1,m_MinZb);
					}
				}
			}
			
		}
			break;
			
		case 16://PSY
		{
			NSMutableArray* closeArray=[[NSMutableArray alloc]initWithCapacity:nCount+1];
			for(tempFxtUnit in m_AnalyseData)
				[closeArray addObject:[NSString stringWithFormat:@"%f",tempFxtUnit.closep]];
			NSMutableArray* REFArray=[[NSMutableArray alloc] initWithArray:closeArray];
			[myCalcZb REF:REFArray In:closeArray Parama:1];

			NSMutableArray* RefArray=[[NSMutableArray alloc]initWithCapacity:nCount+1];
			for(int i=0;i<nCount && i<[closeArray count] && i<[REFArray count];i++)
			{
				if([[closeArray objectAtIndex:i] floatValue]-[[REFArray objectAtIndex:i]floatValue]>0.0001)
					[RefArray addObject:[NSString stringWithFormat:@"%f",1.0f]];
				else
					[RefArray addObject:[NSString stringWithFormat:@"%f",0.0f]];
			}
			[closeArray release];
			
			NSMutableArray* COUNTArray=[[NSMutableArray alloc]initWithArray:RefArray];
			[myCalcZb COUNT:COUNTArray In:RefArray Parama:12];
			
			[RefArray release];
			[REFArray release];
			NSMutableArray* PSYArray=[[NSMutableArray alloc]initWithCapacity:nCount+1];
			float fPSY;
			for(int i=0;i<nCount && i<[m_ZbData count] && i<[COUNTArray count];i++)
			{
				fPSY=[[COUNTArray objectAtIndex:i] floatValue]/12.0f*100.0f;
				[PSYArray addObject:[NSString stringWithFormat:@"%f",fPSY]];
				tempZb=[m_ZbData objectAtIndex:i];
				tempZb.zb_1=fPSY;
			}
			[COUNTArray release];
			NSMutableArray* SMAArray=[[NSMutableArray alloc]initWithArray:PSYArray];
			[PSYArray release];
			[myCalcZb SMA:SMAArray In:nCount Parama:6];
			for(int i=0;i<nCount && i<[SMAArray count] && i<[m_ZbData count];i++)
			{
				tempZb=[m_ZbData objectAtIndex:i];
				tempZb.zb_2=[[SMAArray objectAtIndex:i] floatValue];
			}
			[SMAArray release];
			short nZbData = [m_ZbData count];
			if(nZbData>(m_LeftNum-1))
			{
				tempZb  =[m_ZbData objectAtIndex:MAX_VALUE(m_LeftNum-1,0)];
				m_MaxZb= MAX_VALUE(tempZb.zb_1,tempZb.zb_2);
				m_MinZb= MIN_VALUE(tempZb.zb_1,tempZb.zb_2);
				
				for (int i = m_LeftNum; i < m_LeftNum+m_DrawNum ; i++) {
					if([m_ZbData count] > i ){
						tempZb  =[m_ZbData objectAtIndex:i];
						m_MaxZb= MAX_VALUE(MAX_VALUE(tempZb.zb_1,tempZb.zb_2),m_MaxZb);
						m_MinZb= MIN_VALUE(MIN_VALUE(tempZb.zb_1,tempZb.zb_2),m_MinZb);
					}
				}
			}
		}
			break;
		case 17://DPO
		{
			NSMutableArray* closeArray=[[NSMutableArray alloc]initWithCapacity:nCount+1];
			for(tempFxtUnit in m_AnalyseData)
				[closeArray addObject:[NSString stringWithFormat:@"%f",tempFxtUnit.closep]];
			NSMutableArray* SMAArray=[[NSMutableArray alloc]initWithArray:closeArray];
			[myCalcZb SMA:SMAArray In:nCount Parama:20];
			NSMutableArray*REFArray=[[NSMutableArray alloc] initWithArray:SMAArray];
			[myCalcZb REF:REFArray In:SMAArray Parama:11];
			[SMAArray release];
			NSMutableArray* OPOArray=[[NSMutableArray alloc]initWithCapacity:nCount+1];
			float fOPO;
			for(int i=0;i<nCount && i<[closeArray  count] && i<[REFArray count];i++)
			{
				fOPO=[[closeArray objectAtIndex:i] floatValue]-[[REFArray objectAtIndex:i] floatValue];
				[OPOArray addObject:[NSString stringWithFormat:@"%f",fOPO]];
			}
			[REFArray release];
			[closeArray release];
			NSMutableArray* MAOPOArray=[[NSMutableArray alloc]initWithArray:OPOArray];
			[myCalcZb SMA:MAOPOArray In:nCount Parama:6];
			for(int i=0;i<nCount && i<[m_ZbData count] && i<[OPOArray count] && i<[MAOPOArray count];i++)
			{
				tempZb=[m_ZbData objectAtIndex:i];
				tempZb.zb_1=[[OPOArray objectAtIndex:i] floatValue];
				tempZb.zb_2=[[MAOPOArray objectAtIndex:i] floatValue];
			}
			[OPOArray release];
			[MAOPOArray release];
			short nZbData = [m_ZbData count];
			if(nZbData>(m_LeftNum-1))
			{
				tempZb  =[m_ZbData objectAtIndex:MAX_VALUE(m_LeftNum-1,0)];
				m_MaxZb= MAX_VALUE(tempZb.zb_1,tempZb.zb_2);
				m_MinZb= MIN_VALUE(tempZb.zb_1,tempZb.zb_2);
				
				for (int i = m_LeftNum; i < m_LeftNum+m_DrawNum ; i++) {
					if([m_ZbData count] > i ){
						tempZb  =[m_ZbData objectAtIndex:i];
						m_MaxZb= MAX_VALUE(MAX_VALUE(tempZb.zb_1,tempZb.zb_2),m_MaxZb);
						m_MinZb= MIN_VALUE(MIN_VALUE(tempZb.zb_1,tempZb.zb_2),m_MinZb);
					}
				}
			}
		}
			break;
		
		case 18://boll
		{
			NSMutableArray* closeArray=[[NSMutableArray alloc]initWithCapacity:nCount+1];
			for(tempFxtUnit in m_AnalyseData)
				[closeArray addObject:[NSString stringWithFormat:@"%f",tempFxtUnit.closep]];
			NSMutableArray* SMAArray=[[NSMutableArray alloc]initWithArray:closeArray];
			[myCalcZb SMA:SMAArray In:nCount Parama:20];
			NSMutableArray* STDArray=[[NSMutableArray alloc]initWithArray:closeArray];
			[myCalcZb STD:STDArray In:closeArray Parama:20];
			[closeArray release];
			float fUpper,fLower,fBoll;
			for(int i=0;i<nCount && i<[m_ZbData count] && i<[SMAArray count] && i<[STDArray count];i++)
			{
				fBoll = [[SMAArray objectAtIndex:i]floatValue];
				fUpper = fBoll+2.0f*[[STDArray objectAtIndex:i] floatValue];
				fLower = fBoll-2.0f*[[STDArray objectAtIndex:i] floatValue];
				tempZb = [m_ZbData objectAtIndex:i];
				tempZb.zb_1=fBoll;
				tempZb.zb_2=fUpper;
				tempZb.zb_3=fLower;
			}
			[SMAArray release];
			[STDArray release];
			short nZbData = [m_ZbData count];
			if(nZbData>(m_LeftNum-1))
			{
				m_MaxZb=  m_MaxPrice;
				m_MinZb=  m_MinPrice;
				
				for (int i = m_LeftNum; i < m_LeftNum+m_DrawNum ; i++)
				{
					if([m_ZbData count] > i )
					{
						tempZb  =[m_ZbData objectAtIndex:i];
						if (i<19)
						{
							tempZb.zb_2=[[m_AnalyseData objectAtIndex:i] highp];
							tempZb.zb_3=[[m_AnalyseData objectAtIndex:i] lowp];
						}
						m_MaxZb= MAX_VALUE(MAX_VALUE( MAX_VALUE(MAX_VALUE(tempZb.zb_1,tempZb.zb_2),tempZb.zb_3),m_MaxZb),m_MaxPrice);
						m_MinZb= MIN_VALUE(MIN_VALUE( MIN_VALUE(MIN_VALUE(tempZb.zb_1,tempZb.zb_2),tempZb.zb_3),m_MinZb),m_MinPrice);
					}
				}
			}
		}
			break;
		case 19:
		{
			NSMutableArray* ASIArray=[[NSMutableArray alloc]initWithCapacity:nCount+1];
			
			[ASIArray addObject:[NSString stringWithFormat:@"%f",0.0f]];
			float A,B,C,D,E,M,R,SI;
			for(short i=1;i<nCount && i<[m_AnalyseData count] && i<=[ASIArray  count];i++)
			{
				tempFxtUnit=[m_AnalyseData objectAtIndex:i];
				tempFxtUnitEx=[m_AnalyseData objectAtIndex:i-1];
				A=fabsf(tempFxtUnit.highp-tempFxtUnitEx.closep);
				B=fabsf(tempFxtUnit.lowp-tempFxtUnitEx.closep);
				C=fabsf(tempFxtUnit.highp-tempFxtUnitEx.lowp);
				D=fabsf(tempFxtUnitEx.closep-tempFxtUnitEx.openp);
				E=MAX_VALUE(A,B);
				M=MAX_VALUE(E,C);
				if(equfz(M,A))
					R=A+B/2.0f+D/4.0f;
				else if(equfz(M,B))
					R=B+A/2.0f+D/4.0f;
				else if(equfz(M,C))
					R=C+D/4.0f;
				
				if(equfz(R,0.0f))
					SI=0.0f;
				else
					SI=50.0f*(tempFxtUnit.closep-tempFxtUnitEx.closep+(tempFxtUnit.closep-tempFxtUnit.openp)/2.0f+tempFxtUnitEx.closep-tempFxtUnitEx.openp)/R*E/6.0f;
				[ASIArray addObject:[NSString stringWithFormat:@"%f",[[ASIArray objectAtIndex:i-1] floatValue]+SI]];
			}
			NSMutableArray* MAASIArray=[[NSMutableArray alloc]initWithArray:ASIArray];
			[myCalcZb SMA:MAASIArray In:nCount Parama:6];
			for(int i=0;i<nCount && i<[m_ZbData count] && i<[ASIArray count] && i<[MAASIArray count];i++)
			{
				tempZb=[m_ZbData objectAtIndex:i];
				tempZb.zb_1=[[ASIArray objectAtIndex:i] floatValue];
				tempZb.zb_2=[[MAASIArray objectAtIndex:i] floatValue];
			}
			[ASIArray release];
			[MAASIArray release];
			short nZbData = [m_ZbData count];
			if(nZbData>(m_LeftNum-1))
			{
				tempZb  =[m_ZbData objectAtIndex:MAX_VALUE(m_LeftNum-1,0)];
				m_MaxZb= MAX_VALUE(tempZb.zb_1,tempZb.zb_2);
				m_MinZb= MIN_VALUE(tempZb.zb_1,tempZb.zb_2);
				
				for (int i = m_LeftNum; i < m_LeftNum+m_DrawNum ; i++) {
					if([m_ZbData count] > i ){
						tempZb  =[m_ZbData objectAtIndex:i];
						m_MaxZb= MAX_VALUE(MAX_VALUE(tempZb.zb_1,tempZb.zb_2),m_MaxZb);
						m_MinZb= MIN_VALUE(MIN_VALUE(tempZb.zb_1,tempZb.zb_2),m_MinZb);
					}
				}
			}
		}
			break;
		case 20://SAR
		{
			[positionArray removeAllObjects];
			NSMutableArray* closeArray=[[NSMutableArray alloc]initWithCapacity:nCount+1];
			for(tempFxtUnit in m_AnalyseData)
				[closeArray addObject:[NSString stringWithFormat:@"%f",tempFxtUnit.closep]];
			
			short param=4,position=SAR_LONG,i=0;
			
			float AF,NEXTSAR,yesterdatSIP,SIP;
			float theHigh;
			float theLow;
			if(nCount<param){
				[closeArray release];
				return;
			}
			[myCalcZb LOW_HIGH:m_AnalyseData Current:param-1 N:param theLow:&theLow theHigh:&theHigh];
			NSMutableArray* SARArray=[[NSMutableArray alloc]initWithArray:closeArray];
			[closeArray release];
			[SARArray replaceObjectAtIndex:param-1 withObject:[NSString stringWithFormat:@"%f",theLow]];
            if([m_AnalyseData  count])
                tempFxtUnit=[m_AnalyseData objectAtIndex:0];
            else
                tempFxtUnit=nil;
			SIP=tempFxtUnit.highp;
			AF=2.0f/100.0f;
			for(int i=0;i<param && i<[m_ZbData count];i++){
				tempZb = [m_ZbData objectAtIndex:i];
				tempZb.zb_1 = theHigh;
				[positionArray addObject:[NSString stringWithFormat:@"%d",SAR_LONG]];
			}
			for(i=param;i<nCount && i<[m_AnalyseData count] && i<[m_ZbData count] && i<=[SARArray count];i++)
			{
				yesterdatSIP=SIP;
				tempFxtUnit=[m_AnalyseData objectAtIndex:i];
				tempFxtUnitEx=[m_AnalyseData objectAtIndex:i-1];
				
				if(position==SAR_LONG)
				{
					if(tempFxtUnit.lowp-[[SARArray objectAtIndex:i-1] floatValue]<-0.00001)
					{
						position=SAR_SHORT;
						SIP=tempFxtUnit.lowp;
						AF=(float)2.0f/100.0f;
						NEXTSAR=MAX_VALUE(tempFxtUnit.highp,tempFxtUnitEx.highp);
						NEXTSAR=MAX_VALUE(NEXTSAR,yesterdatSIP+AF*(SIP-yesterdatSIP));
					}
					else
					{
						position=SAR_LONG;
						if(tempFxtUnit.highp-yesterdatSIP>0.00001)
						{
							SIP=tempFxtUnit.highp;
							AF=MIN_VALUE(AF+2.0f/100.0f,20.0/100.0f);
						}
						NEXTSAR=MIN_VALUE(tempFxtUnit.lowp,tempFxtUnitEx.lowp);
						NEXTSAR=MIN_VALUE(NEXTSAR,[[SARArray objectAtIndex:i-1] floatValue]+AF*(SIP-[[SARArray objectAtIndex:i-1] floatValue]));
					}

				}
				else if(position==SAR_SHORT)
				{
					if(tempFxtUnit.highp-[[SARArray objectAtIndex:i-1] floatValue]>0.00001)
					{
						position=SAR_LONG;
						SIP=tempFxtUnit.highp;
						AF=2.0/100.0f;
						NEXTSAR=MIN_VALUE(tempFxtUnit.lowp,tempFxtUnitEx.lowp);
						NEXTSAR=MIN_VALUE(NEXTSAR,[[SARArray objectAtIndex:i-1] floatValue]+AF*(SIP-yesterdatSIP));
					}
					else
					{
						position=SAR_SHORT;
						if(tempFxtUnit.lowp-yesterdatSIP<-0.00001)
						{
							SIP=tempFxtUnit.lowp;
							AF=MIN_VALUE(AF+2.0f/100.0f,20.0f/100.0f);
						}
						NEXTSAR=MAX_VALUE(tempFxtUnit.highp,tempFxtUnitEx.highp);
						NEXTSAR=MAX_VALUE(NEXTSAR,[[SARArray objectAtIndex:i-1] floatValue]+AF*(SIP-[[SARArray objectAtIndex:i-1] floatValue]));
					}
				}
				[SARArray replaceObjectAtIndex:i withObject:[NSString stringWithFormat:@"%f",NEXTSAR]];
				[positionArray addObject:[NSString stringWithFormat:@"%d",position]];
				tempZb=[m_ZbData objectAtIndex:i];
				tempZb.zb_1=NEXTSAR;
			}
			[SARArray release];
			short nZbData = [m_ZbData count];
			if(nZbData>(m_LeftNum-1))
			{
				tempZb  =[m_ZbData objectAtIndex:MAX_VALUE(m_LeftNum-1,0)];
				m_MaxZb= tempZb.zb_1;
				m_MinZb= tempZb.zb_1;
				
				for (int i = m_LeftNum; i < m_LeftNum+m_DrawNum ; i++) {
					if([m_ZbData count] > i ){
						tempZb  =[m_ZbData objectAtIndex:i];
						m_MaxZb= MAX_VALUE( MAX_VALUE(tempZb.zb_1,m_MaxZb),m_MaxPrice);
						m_MinZb= MIN_VALUE( MIN_VALUE(tempZb.zb_1,m_MinZb),m_MinPrice);
					}
				}
			}
		}
			break;
		default:
			break;
	}

}
//计算最值 坐标
-(void)calIt
{
	Analyse_Unit * tempAna;
	float  maxPrice,minPrice,theMaxPrice,theMinPrice;
	int maxVol;
	
	if((m_LeftNum >= 0)&&(m_LeftNum < [m_AnalyseData count]))
	{
		tempAna = [m_AnalyseData objectAtIndex:m_LeftNum];
		theMaxPrice = tempAna.highp;
		theMinPrice = tempAna.lowp;
		maxPrice = tempAna.highp;
		minPrice = tempAna.lowp;
		maxVol = tempAna.volumn;
		m_MaxIndex = m_LeftNum;
		m_MinIndex = m_LeftNum;
	
		for ( int i = m_LeftNum; i < m_LeftNum + m_DrawNum && i<[m_AnalyseData count]; i++)
		{
			tempAna = [m_AnalyseData objectAtIndex:i];
			
			if (tempAna.highp > theMaxPrice) 
			{
				theMaxPrice = tempAna.highp ;
				m_MaxIndex = i; 
			}
			if (tempAna.lowp < theMinPrice) 
			{
				m_MinIndex = i;
				theMinPrice = tempAna.lowp;
			}
			maxPrice = MAX_VALUE(maxPrice,tempAna.highp);
			minPrice = MIN_VALUE(minPrice,tempAna.lowp);
			
			if(i>=5)
			{
				maxPrice = MAX_VALUE(maxPrice ,tempAna.maFive);
				minPrice = MIN_VALUE(minPrice, tempAna.maFive);
			}
			
			if(i>=10)
			{
				maxPrice = MAX_VALUE(maxPrice, tempAna.maTen);
				minPrice = MIN_VALUE(minPrice, tempAna.maTen);
			}
			
			if(i>=20)
			{
				maxPrice = MAX_VALUE(maxPrice, tempAna.maTwn);
				minPrice = MIN_VALUE(minPrice, tempAna.maTwn);
			}
			if (tempAna.volumn > maxVol)
			{
				maxVol = tempAna.volumn;
			}
		}
		theMaxPrice = MAX_VALUE(theMaxPrice,maxPrice);
		theMinPrice = MIN_VALUE(theMinPrice,minPrice);
	}
	m_MaxPrice = maxPrice * 1.02f;

	if(m_MinPrice < 0.01)
		m_MinPrice = theMinPrice *0.98f;
	else
		m_MinPrice = minPrice * 0.98f;
	
	m_MaxVol = maxVol *1.01f;
	if (m_MaxVol > 1000000.0f)
	{
		fVolUnit = 10000.0f;
	}
	else if(m_MaxVol >= 100000.0f && m_MaxVol<1000000.0f)
	{
		fVolUnit = 1000.0f;
	}
	else if(m_MaxVol >= 10000.0f && m_MaxVol<100000.0f)
	{
		fVolUnit = 100.0f;		
	}
	else if(m_MaxVol >= 1000.0f && m_MaxVol<10000.0f)
	{
		fVolUnit =10.0f;
	}
	else
	{
	}

	
	m_PricePerUnit = 6.0f*m_fPerUnitHeight / (m_MaxPrice - m_MinPrice);
	m_PricePerUnitZB = 2.0f*m_fPerUnitHeight/(m_MaxPrice - m_MinPrice);
}


-(void) updateKLine:(NSMutableArray *)m_RecAnalyseData
{
	if ([m_RecAnalyseData count] > 0) {
		NSArray* tempArray = [[NSArray alloc] initWithArray:m_AnalyseData];
		[m_AnalyseData removeAllObjects];
		[m_AnalyseData release],m_AnalyseData=nil;
		
		m_AnalyseData = [[NSMutableArray alloc] initWithArray:m_RecAnalyseData];
        for(int i=0; i < [tempArray count] && i<[tempArray count]; i++)
		{
			[m_AnalyseData addObject:[tempArray objectAtIndex:i]];
		}
		[tempArray release];
	}
	
	
	[m_ZbData removeAllObjects];
	m_ReadNum = m_ReadNum + [m_RecAnalyseData count];

	
	m_LeftNum = m_ReadNum- m_DrawNum;
	[self calDataEx];
	[self calMA];
	[self calZB];
	[self calIt];
	dataFlag = TRUE;
	moreFxtFlag = NO;
	
	
	//刷新十字游标
	if (fxtCross.showFlag) {
		cursor = cursor + [m_RecAnalyseData count];
		
		int tempInt = cursor - m_LeftNum;
		fxtCross.xPos = m_dWidth*0.5f + dPer*tempInt;
        if(cursor>=[m_AnalyseData count])
            cursor=[m_AnalyseData count]-1;
		Analyse_Unit * tempAna = [m_AnalyseData objectAtIndex:cursor];
		fxtCross.yPos = [self  getYPos:tempAna.closep secNum:1];
		[fxtCross refreshShow];
	}
}

- (void) dealloc
{
	[drawView release];
	[eGetData release];
	[fxtCross release];
	[currInfo release];
	[m_AnalyseData release];
	[m_ZbData release];
	[periodArray release];
	[zbArray release];
	[drawNumArray release];
	[axisArray release];
	[titleArray release];
	[positionArray release];
	[super dealloc];
}


#pragma mark 键盘事件相关


-(void) dealKeyBoardEvent:(NSEvent *)theEvent{
	if (m_DrawNum + m_LeftNum > m_ReadNum) {
		m_DrawNum = m_ReadNum - m_LeftNum;
	}
	
	Analyse_Unit * tempAna;
	int tempInt;
	switch ([theEvent keyCode]) {
			
		case MAC_KEY_ARROWDOWN:{
			if (moreFxtFlag) {
				return;
			}
			m_nLeftPos= m_LeftNum;
			m_DrawNum += 20;
			m_nLeftPos -= 20;
			m_nLeftPos = MAX(m_nLeftPos,0);
			
			m_LeftNum = MAX(m_nLeftPos ,0);
			
			if(m_LeftNum <= 40 && m_LeftNum >= 0 )
			{
				
				if (!isAllData) {
					[myDelegate getMoreFXTData];
				}
				else {
					[self calDataEx];
					[self calIt];
					[self setNeedsDisplay:YES];
					
					
					
				}

			}
			else{
				if (m_LeftNum > 0) {
					[self calDataEx];
					[self calIt];
					[self setNeedsDisplay:YES];
				}
				
			}
			
			
		}
			break;
		case MAC_KEY_ARROWUP:{
			//放大
			if (moreFxtFlag) {
				return;
			}
			
			m_nLeftPos= m_LeftNum;
			m_DrawNum -= 20;
			m_nLeftPos += 20;
			
			if (m_DrawNum < 20)
			{
				int tempInt = 20 - m_DrawNum;
				m_DrawNum = 20;
				m_nLeftPos -= tempInt;
				m_nLeftPos = MAX(m_nLeftPos,0);
			}
			
			m_LeftNum = MAX(m_nLeftPos ,0);
			
			
			[self calDataEx];
			[self calIt];
			[self setNeedsDisplay:YES];
		}
			break;	
		case MAC_KEY_ARROWLEFT:{
			if (moreFxtFlag) {
				return;
			}
			
			
			if (fxtCross.showFlag) {
				if (cursor ==0) {
					return;
				}
				cursor = cursor - 1;
				
				if (cursor < m_LeftNum - 2) {
					cursor = m_LeftNum;
				}
				
				if (cursor < m_LeftNum) {
					m_LeftNum = m_LeftNum - 1;
					
					if (m_LeftNum > 30) {
						
					}
					else {
						[myDelegate getMoreFXTData];
					}

					
					[self calIt];
					[self setNeedsDisplay:YES];
				}
				else {
                    if(cursor>=[m_AnalyseData count])
                        cursor=[m_AnalyseData count]-1;
					tempAna = [m_AnalyseData objectAtIndex:cursor];
					fxtCross.yPos = [self  getYPos:tempAna.closep secNum:1];
					tempInt = cursor - m_LeftNum;
					fxtCross.xPos = m_dWidth*0.5f + dPer*tempInt;
					[fxtCross refreshShow];
					[self drawCaption];
				}
			}
			else {
								
				cursor=m_LeftNum+m_DrawNum-1;
                if(cursor>=[m_AnalyseData count])
                    cursor=[m_AnalyseData count]-1;
				tempAna = [m_AnalyseData objectAtIndex:cursor];
				fxtCross.showFlag = TRUE;
				fxtCross.yPos = [self  getYPos:tempAna.closep secNum:1];
				tempInt = cursor - m_LeftNum;
				fxtCross.xPos = m_dWidth*0.5f + dPer*tempInt;
				[fxtCross refreshShow];
				[self showFxtDetail];
				[self drawCaption];
			}

			
			
		}
			break;
		case MAC_KEY_ARROWRIGHT:{
			if (moreFxtFlag) {
				return;
			}
			
			if (fxtCross.showFlag) {
				if (cursor == [m_AnalyseData count] - 1) {
					return;
				}
				cursor = cursor +1;
				
				if (cursor < m_LeftNum - 2) {
					cursor = m_LeftNum;
				}
				
				if (cursor >m_LeftNum+m_DrawNum-1) {
					if (m_LeftNum+m_DrawNum-1 < [m_AnalyseData count] - 1) {
						m_LeftNum = m_LeftNum +1;
						[self calIt];
						[self setNeedsDisplay:YES];
					}
					else {
						return;
					}

					
				}
                if(cursor>=[m_AnalyseData count])
                    cursor=[m_AnalyseData count]-1;
				tempAna = [m_AnalyseData objectAtIndex:cursor];
				fxtCross.yPos = [self  getYPos:tempAna.closep secNum:1];
				tempInt = cursor - m_LeftNum;
				fxtCross.xPos = m_dWidth*0.5f + dPer*tempInt;
				[fxtCross refreshShow];
				[self drawCaption];
			}
			else {
				cursor=m_LeftNum+m_DrawNum-1;
                if(cursor>=[m_AnalyseData count])
                    cursor=[m_AnalyseData count]-1;
				tempAna = [m_AnalyseData objectAtIndex:cursor];
				fxtCross.showFlag = TRUE;
				fxtCross.yPos = [self  getYPos:tempAna.closep secNum:1];
				tempInt = cursor - m_LeftNum;
				fxtCross.xPos = m_dWidth*0.5f + dPer*tempInt;
				[fxtCross refreshShow];
				[self showFxtDetail];
				[self drawCaption];
				
			}			
		}
			
			
			break;
		case MAC_KEY_F8:
		case MAC_KEY_CHAR_RIGHT:
			periodIndex = periodIndex + 1;
			if (periodIndex > 6) {
				periodIndex = 0;
			}
			m_ReadNum = 0;
			[zqButton selectItemAtIndex:periodIndex];
			
			[myDelegate changeFXTPara];
			break;
		case MAC_KEY_CHAR_LEFT:
			periodIndex = periodIndex - 1;
			if (periodIndex < 0) {
				periodIndex = 6;
			}
			m_ReadNum = 0;
			[zqButton selectItemAtIndex:periodIndex];
			
			[myDelegate changeFXTPara];
			
			break;
			
		default:
			break;
	}
}


#pragma mark touche事件相关
-(void)showFxtDetail{
	[self addSubview:detailView];
}
-(void)hideFxtDetail{
	[detailView removeFromSuperview];
}


-(void) mouseDown:(NSEvent *)theEvent{
	[[self window] makeFirstResponder:[self superview]];
	moveFlag = NO;
	
	NSPoint  p = [theEvent locationInWindow];
	m_nStartPosX = p.x;
}



-(void) mouseMoved:(NSEvent *)theEvent{
	Analyse_Unit * tempAna;
	moveFlag = TRUE;
	if(fxtCross.showFlag)
	{
		if (moreFxtFlag) {
			return;
		}
		
		float tempX  = [theEvent locationInWindow].x;
		int tempInt;
		
		if(tempX > drawWidth)
			tempX = drawWidth-1;
		tempInt = tempX / dPer;
		
		fxtCross.xPos = m_dWidth*0.5f + dPer*tempInt;	
		int tempCursor = tempInt+m_LeftNum;
		if(tempCursor > ([m_AnalyseData count] -1))
			tempCursor = [m_AnalyseData count] - 1;
		tempAna = [m_AnalyseData objectAtIndex:tempCursor];
		cursor = tempCursor;
		fxtCross.yPos = [self  getYPos:tempAna.closep secNum:1];
		fxtCross.xPos = tempX;
		[fxtCross refreshShow];
		[self drawCaption];
		[fxtCross refreshShow];

	}
}

-(void) mouseDragged:(NSEvent *)theEvent{

}

-(void) rightMouseDown:(NSEvent *)theEvent{
	[[self superview] rightMouseDown:theEvent];
}

-(void) mouseUp:(NSEvent *)theEvent{
	float tempX,tempY;
	if ([theEvent clickCount] != 2) {
		return;
	}
	tempX  = [theEvent locationInWindow].x;
	tempY  = [theEvent locationInWindow].y;
	if ((tempX > drawWidth)&&(tempX < viewWidth)){
		[operProcessDelegate getHQProcess:@"" gpSetcode:-1 typeID:MAC_SWITCH_FUNC pareOne:-1 paraTwo:-1];
		return;
	}
	
	
	Analyse_Unit * tempAna;
	if(fxtCross.showFlag)
	{
		if(!moveFlag){
			fxtCross.showFlag = NO;
		}
		[fxtCross refreshShow];
		[self hideFxtDetail];
	}else{
		if(!moveFlag)
		{
			tempX  = [theEvent locationInWindow].x;
			if(tempX > drawWidth)  tempX = drawWidth-1;
			
			int tempInt = tempX / dPer;
			fxtCross.xPos = m_dWidth * 0.5 + dPer * tempInt;
			int tempCursor = tempInt+m_LeftNum;
			if(tempCursor > ([m_AnalyseData count] -1))  tempCursor = [m_AnalyseData count] - 1;
			if (tempCursor < [m_AnalyseData count]) {
				tempAna = [m_AnalyseData objectAtIndex:tempCursor];
				cursor = tempInt+ m_LeftNum;
				fxtCross.yPos = [self  getYPos:tempAna.closep secNum:1];
				fxtCross.showFlag = YES;
				[fxtCross refreshShow];
				[self showFxtDetail];
				[self drawCaption];
			}
        }
	}
	
	
	moveFlag=NO;
}



#pragma mark 定时动态维护相关
-(int) getTodayCursor:(int)_ymd nowMinute:(int)_nowMinute{
	int nowCursor = [m_AnalyseData count] -1;
	Analyse_Unit * tempAna;
	for (int i = nowCursor; i>-1; i--) {
		tempAna = [m_AnalyseData objectAtIndex:i];
		if ((tempAna.date == _ymd) && (tempAna.time == _nowMinute)){
			return i;
		}
	}
	
	
	return -1;
}


-(BOOL)refreshAnalyse:(SinHqInfo *) _currInfo nowDate:(int)_nowDate nowHour:(int)_nowHour nowMinute:(int)_nowMinute{
	
	if (moreFxtFlag) {
		return YES;
	}
	
	if (fqFlag == 2) {
		return YES;
	}
	Analyse_Unit * tempAna;
	Analyse_Unit * newAna;
	int nowCursor;
	
	if ([m_AnalyseData count] < 1) {
		return YES;
	}
	
	if (periodIndex == 4) { //日线
		nowCursor = [m_AnalyseData count] - 1;
		tempAna = [m_AnalyseData objectAtIndex:nowCursor];
		if (_currInfo.zsflag) {  //指数
			if (_nowDate == tempAna.date) {
				if (_currInfo.maxP > 0.01)  tempAna.highp = _currInfo.maxP;
				if (_currInfo.minP > 0.01)  tempAna.lowp = _currInfo.minP;
				if (_currInfo.nowP > 0.01)  tempAna.closep = _currInfo.nowP;
				tempAna.amount =  _currInfo.amount;
				tempAna.volumn = _currInfo.volume;
			}
		}
		else {
			if (_nowDate == tempAna.date) {
				if (_currInfo.maxP > 0.01)  tempAna.highp = _currInfo.maxP;
				if (_currInfo.minP > 0.01)  tempAna.lowp = _currInfo.minP;
				if (_currInfo.nowP > 0.01)  tempAna.closep = _currInfo.nowP;
				tempAna.amount =  _currInfo.amount;
				tempAna.volumn = _currInfo.volume*100;
			}
		}

	}
	
	else if(periodIndex == 5 || periodIndex == 6) {
		nowCursor = [m_AnalyseData count] - 1;
		tempAna = [m_AnalyseData objectAtIndex:nowCursor];
		float amountDiff = _currInfo.amount - oriAmount;
		float volDiff = _currInfo.volume  - oriVol;
		oriAmount = _currInfo.amount;
		oriVol = _currInfo.volume;
		
		NSLog(@"amountDiff is %f and volDiff id %f",amountDiff,volDiff);
		if (_currInfo.zsflag) {  //指数
			if (_nowDate == tempAna.date) {
				if ((_currInfo.maxP > 0.01)&&(_currInfo.maxP > tempAna.highp))  tempAna.highp = _currInfo.maxP;
				if ((_currInfo.minP > 0.01)&&(_currInfo.minP < tempAna.lowp) ) tempAna.lowp = _currInfo.minP;
				if (_currInfo.nowP > 0.01)  tempAna.closep = _currInfo.nowP;
				tempAna.amount =  tempAna.amount + amountDiff;
				tempAna.volumn =  tempAna.volumn + volDiff;
			}
		}
		else {
			if (_nowDate == tempAna.date) {
				if ((_currInfo.maxP > 0.01)&&(_currInfo.maxP > tempAna.highp))  tempAna.highp = _currInfo.maxP;
				if ((_currInfo.minP > 0.01)&&(_currInfo.minP < tempAna.lowp) ) tempAna.lowp = _currInfo.minP;
				if (_currInfo.nowP > 0.01)  tempAna.closep = _currInfo.nowP;
				tempAna.amount =  tempAna.amount + amountDiff;
				tempAna.volumn =  tempAna.volumn + volDiff*100;
			}
		}
	}

	else if(periodIndex == 0 || periodIndex == 1||periodIndex == 2 || periodIndex == 3){
		int i ;
		int todayCursor,startCursor,disCursor;
		int nowMinute,lastMinute;
		float tempVol,tempAmount;
		
		if(periodIndex == 0)
		{
			startCursor = 575;
			disCursor = 5;
		}
		
		if(periodIndex == 1)
		{
			startCursor = 585;
			disCursor = 15;
		}
		
		if(periodIndex == 2)
		{
			startCursor = 600;
			disCursor = 30;
		}
		
		if(periodIndex == 3)
		{
			startCursor = 630;
			disCursor = 60;
		}
		
		nowCursor = [m_AnalyseData count] - 1;
		todayCursor = [self getTodayCursor:_nowDate nowMinute:startCursor];
		
		if (todayCursor > -1) {
			int tempInt = [eGetData getTdxMinute:_nowHour theMinute:_nowMinute];
			nowMinute = [eGetData getMinuteFromFZ:tempInt -1 fzNum:1];
			tempAna = [m_AnalyseData objectAtIndex:nowCursor];
			lastMinute = tempAna.time;
			
			
			if (nowMinute > lastMinute) {
				newAna = [[Analyse_Unit alloc] init];
				if (_currInfo.zsflag) {
					newAna.date = _nowDate;
					newAna.time = lastMinute + disCursor;
					newAna.openp = _currInfo.nowP;
					newAna.highp = _currInfo.nowP;
					newAna.lowp = _currInfo.nowP;
					newAna.closep = _currInfo.closeP;
					
					tempAmount = _currInfo.amount;
					
					for (i=todayCursor; i<nowCursor+1 && i<[m_AnalyseData count]; i++) {
						tempAna = [m_AnalyseData objectAtIndex:i];
						tempAmount = tempAmount - tempAna.amount;
					}
					newAna.amount = tempAmount;
					newAna.volumn = tempAmount/100;
				}
				else {
					newAna.date = _nowDate;
					newAna.time = lastMinute + disCursor;
					newAna.openp = _currInfo.nowP;
					newAna.highp = _currInfo.nowP;
					newAna.lowp = _currInfo.nowP;
					newAna.closep = _currInfo.closeP;
					
					tempAmount = _currInfo.amount;
					tempVol = _currInfo.volume *100;
					for (i=todayCursor; i<nowCursor+1 && i<[m_AnalyseData count]; i++) {
						tempAna = [m_AnalyseData objectAtIndex:i];
						tempAmount = tempAmount - tempAna.amount;
						tempVol = tempVol - tempAna.volumn;
					}
					newAna.amount = tempAmount;
					newAna.volumn = tempVol;
				}

				[m_AnalyseData addObject:newAna];
				[newAna release];
				m_ReadNum = m_ReadNum+1;
				m_LeftNum = m_ReadNum - m_DrawNum;
				cursor = m_LeftNum + m_DrawNum -1;
			}
			else {
				tempAna = [m_AnalyseData objectAtIndex:nowCursor];
				Analyse_Unit * tempAna2;
				if (_currInfo.zsflag) {
					if ((_currInfo.nowP > 0.01)&&(_currInfo.nowP > tempAna.highp))  tempAna.highp = _currInfo.nowP;
					if ((_currInfo.nowP > 0.01)&&(_currInfo.nowP < tempAna.lowp) ) tempAna.lowp = _currInfo.nowP;
					if (_currInfo.nowP > 0.01)  tempAna.closep = _currInfo.nowP;
					tempAmount = _currInfo.amount;
					
					for (i=todayCursor; i<nowCursor && i<[m_AnalyseData count]; i++) {
						tempAna2 = [m_AnalyseData objectAtIndex:i];
						tempAmount = tempAmount - tempAna2.amount;
					}
					tempAna.amount = tempAmount;
					tempAna.volumn = tempAmount/100;
				}
				else {
					if ((_currInfo.nowP > 0.01)&&(_currInfo.nowP > tempAna.highp))  tempAna.highp = _currInfo.nowP;
					if ((_currInfo.nowP > 0.01)&&(_currInfo.nowP < tempAna.lowp) ) tempAna.lowp = _currInfo.nowP;
					if (_currInfo.nowP > 0.01)  tempAna.closep = _currInfo.nowP;
					tempAmount = _currInfo.amount;
					tempVol = _currInfo.volume *100;
					for (i=todayCursor; i<nowCursor && i<[m_AnalyseData count]; i++) {
						tempAna2 = [m_AnalyseData objectAtIndex:i];
						tempAmount = tempAmount - tempAna2.amount;
						tempVol = tempVol - tempAna2.volumn;
					}
					tempAna.amount = tempAmount;
					tempAna.volumn = tempVol;
				}

			}

		}
	}
	
	
	[self calDataEx];
	[self calMA];
	[self calIt];
	dataFlag = TRUE;
	[self setNeedsDisplay:YES];
	
	return YES;
}



#pragma mark pickview相关


@end
