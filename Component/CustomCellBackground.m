//
//  CustomCellBackground.m
//  CoolTable
//
//  Created by Ray Wenderlich on 9/29/10.
//  Copyright 2010 Ray Wenderlich. All rights reserved.
//

#import "CustomCellBackground.h"
#import "Commondraw.h"

@implementation CustomCellBackground

@synthesize bshowyzm,bcoloryzm;

- (id)initWithFrame:(NSRect)frame {
    if ((self = [super initWithFrame:frame])) {
        bshowyzm=NO;
        bcoloryzm=NO;
        m_yzmstr=nil;
    }
    return self;
}

- (void)drawRect:(NSRect)rect {
	CGContextRef context = [[NSGraphicsContext currentContext] graphicsPort];

    CGColorRef whiteColor = CGColorCreateDeviceRGBFromNSColor([NSColor colorWithDeviceRed:1.0 green:1.0 blue:1.0 alpha:1.0]);
	CGColorRef lightGrayColor = CGColorCreateDeviceRGBFromNSColor([NSColor colorWithDeviceRed:128.0/255.0 green:230.0/255.0 blue:230.0/255.0 alpha:1.0]);
    CGColorRef separatorColor = CGColorCreateDeviceRGBFromNSColor([NSColor colorWithDeviceRed:208.0/255.0 green:208.0/255.0 blue:208.0/255.0 alpha:1.0]);
    
    CGRect paperRect = CGRectMake(rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);

    drawLinearGradient(context, paperRect, whiteColor, lightGrayColor);
    
    CGRect strokeRect = paperRect;
    strokeRect.size.height -= 1;
    strokeRect = rectFor1PxStroke(strokeRect);

    CGContextSetStrokeColorWithColor(context, whiteColor);
    CGContextSetLineWidth(context, 1.0);
    CGContextStrokeRect(context, strokeRect);
    
    CGPoint startPoint = CGPointMake(paperRect.origin.x, paperRect.origin.y + paperRect.size.height - 1);
    CGPoint endPoint = CGPointMake(paperRect.origin.x + paperRect.size.width - 1, paperRect.origin.y + paperRect.size.height - 1);
    draw1PxStroke(context, startPoint, endPoint, separatorColor); 
    
	
	CGColorRelease(whiteColor);
	CGColorRelease(lightGrayColor);
	CGColorRelease(separatorColor);
   [self  DrawYzm:context withrect:paperRect];
}

- (void)dealloc {
    [m_yzmstr release];
    [super dealloc];
}

-(void)GenYzm
{
	static BOOL bsyncflag=NO;
	if(bsyncflag)
		return;
	bsyncflag=YES;
	srand([[NSDate date] timeIntervalSince1970]);
	[m_yzmstr release];
	m_yzmstr=[[NSString alloc] initWithFormat:@"%i%i%i%i",rand()%10,rand()%10,rand()%10,rand()%10];
	[self setNeedsDisplay:YES];
	bsyncflag=NO;
}

-(void)DrawYzm:(CGContextRef)context withrect:(CGRect)rect
{
	if(m_yzmstr==nil)
		[self GenYzm];
	int len=[m_yzmstr length];
	CGRect rect1=rect;
	
	rect1.origin.x=25;
	rect1.origin.y+=rect1.size.height/2;
	rect1.size.width=10;
	for(int i=0;i<len;i++)
	{
		[self DrawNumber:context withrect:rect1 withnumber:[[m_yzmstr substringWithRange:NSMakeRange(i, 1)] intValue]];
		rect1.origin.x+=15;
	}
	//增加混淆////
	[self drawMhdot:context withrect:rect];
}

-(void)drawMhdot:(CGContextRef)context withrect:(CGRect)rect
{
	return;
	CGContextSaveGState(context);
	CGContextSetLineCap(context, kCGLineCapSquare);
	
	CGContextSetLineWidth(context, 1.0);
	
	CGColorRef yzmcolor = CGColorCreateDeviceRGBFromNSColor([NSColor blackColor]);
    
	CGFloat x=0.0f,y=0.0f;
	int width=(int)rect.size.width;
	int height=(int)rect.size.height;
	for(int i=0;i<15;i++)
	{
		srandom(time(NULL));
		if(bcoloryzm)
		{
			int index=rand()%6;
			switch (index) {
				case 0:
					yzmcolor=CGColorCreateDeviceRGBFromNSColor([NSColor colorWithDeviceRed:255.0/255.0 green:0.0/255.0 blue:0.0/255.0 alpha:1.0]);
					break;
				case 1:
					yzmcolor=CGColorCreateDeviceRGBFromNSColor([NSColor colorWithDeviceRed:238.0/255.0 green:0.0/255.0 blue:0.0/255.0 alpha:1.0]);
					break;
				case 2:
					yzmcolor=CGColorCreateDeviceRGBFromNSColor([NSColor colorWithDeviceRed:0.0/255.0 green:0.0/255.0 blue:0.0/255.0 alpha:1.0]);
					break;
				case 3:
					yzmcolor=CGColorCreateDeviceRGBFromNSColor([NSColor colorWithDeviceRed:0.0/255.0 green:153.0/255.0 blue:255.0/255.0 alpha:1.0]);
					break;
				case 4:
					yzmcolor=CGColorCreateDeviceRGBFromNSColor([NSColor colorWithDeviceRed:255.0/255.0 green:128.0/255.0 blue:0.0/255.0 alpha:1.0]);
					break;
				case 5:
					yzmcolor=CGColorCreateDeviceRGBFromNSColor([NSColor colorWithDeviceRed:0.0/255.0 green:128.0/255.0 blue:0.0/255.0 alpha:1.0]);
					break;
				default:
					break;
			}
		}
		CGContextSetStrokeColorWithColor(context, yzmcolor);
		x=(rand()%width)*1.0f;
		y=(rand()%height)*1.0f;
		if(i==3)
		{
			CGContextMoveToPoint(context, x,y);
			CGContextAddLineToPoint(context, x+20,y);
		}
		else if(i==9)
		{
			CGContextMoveToPoint(context, x,y);
			CGContextAddLineToPoint(context, x+15,y-8);
		}
		else if(i==12)
		{
			CGContextMoveToPoint(context, x,y);
			CGContextAddLineToPoint(context, x-10,y+13);
		}
		else 
		{
			CGContextMoveToPoint(context, x,y);
			CGContextAddLineToPoint(context, x,y+2);
		}
		CGContextStrokePath(context);
	}
	
	CGColorRelease(yzmcolor);
	
	CGContextRestoreGState(context);
}

-(void)DrawNumber:(CGContextRef)context withrect:(CGRect)rect withnumber:(int)flag
{
    NSString *tmpstr=[NSString stringWithFormat:@"%i",flag];

    NSMutableParagraphStyle *textStyle = [[NSMutableParagraphStyle defaultParagraphStyle] mutableCopy];
    textStyle.lineBreakMode = NSLineBreakByWordWrapping;
    textStyle.alignment = NSTextAlignmentCenter;
     NSFont *textFont = [NSFont systemFontOfSize:16];
    [tmpstr drawInRect:NSMakeRect(rect.origin.x-10,rect.origin.y-18,rect.size.width,rect.size.height) withAttributes:@{NSFontAttributeName:textFont, NSParagraphStyleAttributeName:textStyle}];
    
    return;
    
	CGColorRef yzmcolor = CGColorCreateDeviceRGBFromNSColor([NSColor blackColor]);
	if(bcoloryzm)
	{
		int index=rand()%6;
		switch (index) {
			case 0:
				yzmcolor=CGColorCreateDeviceRGBFromNSColor([NSColor colorWithDeviceRed:255.0/255.0 green:0.0/255.0 blue:0.0/255.0 alpha:1.0]);
				break;
			case 1:
				yzmcolor=CGColorCreateDeviceRGBFromNSColor([NSColor colorWithDeviceRed:238.0/255.0 green:0.0/255.0 blue:0.0/255.0 alpha:1.0]);
				break;
			case 2:
				yzmcolor=CGColorCreateDeviceRGBFromNSColor([NSColor colorWithDeviceRed:0.0/255.0 green:0.0/255.0 blue:0.0/255.0 alpha:1.0]);
				break;
			case 3:
				yzmcolor=CGColorCreateDeviceRGBFromNSColor([NSColor colorWithDeviceRed:0.0/255.0 green:153.0/255.0 blue:255.0/255.0 alpha:1.0]);
				break;
			case 4:
				yzmcolor=CGColorCreateDeviceRGBFromNSColor([NSColor colorWithDeviceRed:255.0/255.0 green:128.0/255.0 blue:0.0/255.0 alpha:1.0]);
				break;
			case 5:
				yzmcolor=CGColorCreateDeviceRGBFromNSColor([NSColor colorWithDeviceRed:0.0/255.0 green:128.0/255.0 blue:0.0/255.0 alpha:1.0]);
				break;
			default:
				break;
		}
	}
	CGContextSaveGState(context);
	CGContextSetLineCap(context, kCGLineCapSquare);
	CGContextSetStrokeColorWithColor(context, yzmcolor);
	CGContextSetLineWidth(context, 1.0);
	int nX=0,nY=0,x=0,y=0,i=0,xStart=0,yStart=0;
	int top=rect.origin.y-rect.size.height/2;
	int bottom=rect.origin.y+rect.size.height/2;
	int height=rect.size.height;
	int halfheight=height/2;
	
	switch (flag) {
		case 0:
			{
				[self GetYzmOffset:(int *)&nX :(int *)&nY :2 :3];
				x=rect.origin.x+nX;
				y=top+3+nY;
				
				for(i=0;i<3;i++)
				{
					CGContextMoveToPoint(context, x,y);
					CGContextAddLineToPoint(context, x,y+2);
					x--;
					y++;
				}
				CGContextMoveToPoint(context, x,y);
				CGContextAddLineToPoint(context, x,bottom-6);
				y=bottom-6;
				x++;
				for(i=0;i<3;i++)
				{
					CGContextMoveToPoint(context, x,y);
					CGContextAddLineToPoint(context, x,y+2);
					x++;
					y++;
				}
				///////////右半边////////////
				x=rect.origin.x;
				y=top+3;
				for(i=0;i<3;i++)
				{
					CGContextMoveToPoint(context, x,y);
					CGContextAddLineToPoint(context, x,y+2);
					x++;
					y++;
				}
				CGContextMoveToPoint(context, x,y);
				CGContextAddLineToPoint(context, x,bottom-6);
				y=bottom-6;
				x--;
				for(i=0;i<3;i++)
				{
					CGContextMoveToPoint(context, x,y);
					CGContextAddLineToPoint(context, x,y+2);
					x--;
					y++;
				}
			}
			break;
		case 1:
			{
				[self GetYzmOffset:(int *)&nX :(int *)&nY :2 :3];
				x=rect.origin.x+nX;
				y=top+nY;
				CGContextMoveToPoint(context, x-1,y+4);
				CGContextAddLineToPoint(context, x,y+3);
				CGContextAddLineToPoint(context, x,bottom-3);
				CGContextAddLineToPoint(context, x-1,bottom-3);
				CGContextAddLineToPoint(context, x+2,bottom-3);
			}
			break;
		case 2:
			{
				[self GetYzmOffset:(int *)&nX :(int *)&nY :2 :3];
				xStart=rect.origin.x+nX;
				yStart=height-(top-nY);
				
				CGContextMoveToPoint(context, xStart-3,yStart-3);
				CGContextAddLineToPoint(context, xStart-3,yStart-6);
				CGContextMoveToPoint(context, xStart-4,yStart-4);
				CGContextAddLineToPoint(context, xStart-4,yStart-6);
				CGContextMoveToPoint(context, xStart-3,yStart-3);
				CGContextAddLineToPoint(context, xStart+3,yStart-3);
				CGContextMoveToPoint(context, xStart+3,yStart-3);
				CGContextAddLineToPoint(context, xStart+3,yStart-7);
				CGContextMoveToPoint(context, xStart+4,yStart-4);
				CGContextAddLineToPoint(context, xStart+4,yStart-7);
				
				x=xStart+3;
				y=yStart-7;
				
				for(i=0;i<7;i++)
				{
					CGContextMoveToPoint(context, x,y);
					CGContextAddLineToPoint(context, x,y-1);
					x--;
					y--;
				}
				CGContextMoveToPoint(context, x,y);
				CGContextAddLineToPoint(context, x,y-2);
				CGContextAddLineToPoint(context, xStart+5,y-2);
				CGContextAddLineToPoint(context, xStart+5,y);
			}
			break;
		case 3:
			{
				[self GetYzmOffset:(int *)&nX :(int *)&nY :2 :3];
				xStart=rect.origin.x+nX;
				yStart=top+nY;
				
				CGContextMoveToPoint(context, xStart-3,yStart+3);
				CGContextAddLineToPoint(context, xStart-3,yStart+6);
				CGContextMoveToPoint(context, xStart-4,yStart+4);
				CGContextAddLineToPoint(context, xStart-4,yStart+6);
				CGContextMoveToPoint(context, xStart-3,yStart+3);
				CGContextAddLineToPoint(context, xStart+3,yStart+3);
				CGContextMoveToPoint(context, xStart+3,yStart+3);
				CGContextAddLineToPoint(context, xStart+3,yStart+halfheight);
				CGContextMoveToPoint(context, xStart+4,yStart+4);
				CGContextAddLineToPoint(context, xStart+4,yStart+halfheight-1);
				
				CGContextMoveToPoint(context, xStart+3,yStart+halfheight);
				CGContextAddLineToPoint(context, xStart-3,yStart+halfheight);
				
				CGContextMoveToPoint(context, xStart+3,yStart+halfheight);
				CGContextAddLineToPoint(context, xStart+3,bottom-3);
				CGContextMoveToPoint(context, xStart+4,yStart+halfheight+1);
				CGContextAddLineToPoint(context, xStart+4,bottom-4);
				
				CGContextMoveToPoint(context, xStart+3,bottom-3);
				CGContextAddLineToPoint(context, xStart-3,bottom-3);
				
				CGContextMoveToPoint(context, xStart-3,bottom-3);
				CGContextAddLineToPoint(context, xStart-3,bottom-6);
				
				CGContextMoveToPoint(context, xStart-4,bottom-4);
				CGContextAddLineToPoint(context, xStart-4,bottom-6);
			}
			break;
		case 4:
			{
				[self GetYzmOffset:(int *)&nX :(int *)&nY :2 :3];
				xStart=rect.origin.x+nX;
				yStart=height-(top+nY);
				
				CGContextMoveToPoint(context, xStart-3,yStart-3);
				CGContextAddLineToPoint(context, xStart-3,yStart-halfheight+1);
				CGContextMoveToPoint(context, xStart-4,yStart+3);
				CGContextAddLineToPoint(context, xStart-4,yStart-halfheight);
				CGContextMoveToPoint(context, xStart-5,yStart-halfheight+1);
				CGContextAddLineToPoint(context, xStart-5,yStart-halfheight);
				
				CGContextMoveToPoint(context, xStart-5,yStart-halfheight);
				CGContextAddLineToPoint(context, xStart+5,yStart-halfheight);
				
				CGContextMoveToPoint(context, xStart,yStart+5);
				CGContextAddLineToPoint(context, xStart,2);
				
				CGContextMoveToPoint(context, xStart+1,yStart+5);
				CGContextAddLineToPoint(context, xStart+1,2);
			}
			break;
		case 5:
			{
				[self GetYzmOffset:(int *)&nX :(int *)&nY :2 :3];
				xStart=rect.origin.x+nX;
				yStart=height-(top+nY);
				
				CGContextMoveToPoint(context, xStart-3,yStart-3);
				CGContextAddLineToPoint(context, xStart-3,yStart-halfheight);
				CGContextMoveToPoint(context, xStart-4,yStart-3);
				CGContextAddLineToPoint(context, xStart-4,yStart-halfheight);
				
				CGContextMoveToPoint(context, xStart-2,yStart-3);
				CGContextAddLineToPoint(context, xStart+3,yStart-3);
				CGContextMoveToPoint(context, xStart-2,yStart-halfheight);
				CGContextAddLineToPoint(context, xStart+2,yStart-halfheight);
				CGContextAddLineToPoint(context, xStart+2,yStart-halfheight-3);
				
				CGContextMoveToPoint(context, xStart+3,yStart-halfheight-1);
				CGContextAddLineToPoint(context, xStart+3,yStart-halfheight-3);
				
				x=xStart+2;
				y=yStart-halfheight-3;
				
				for(i=0;i<3;i++)
				{
					CGContextMoveToPoint(context, x,y);
					CGContextAddLineToPoint(context, x,y-1);
					x--;
					y--;
				}
				CGContextAddLineToPoint(context, xStart-4,y);
			}
			break;
		case 6:
			{
				[self GetYzmOffset:(int *)&nX :(int *)&nY :2 :3];
				xStart=rect.origin.x+nX;
				yStart=height-top+nY;
				
				x=xStart;
				y=yStart-16;
				
				for(i=0;i<8;i++)
				{
					CGContextMoveToPoint(context, x,y);
					CGContextAddLineToPoint(context, x,y+2);
					x++;
					y++;
				}
				////////////左半边//////////
				x=xStart;
				y=yStart-16;
				for(i=0;i<3;i++)
				{
					CGContextMoveToPoint(context, x,y);
					CGContextAddLineToPoint(context, x,y-2);
					x--;
					y--;
				}
				CGContextMoveToPoint(context, x,y);
				CGContextAddLineToPoint(context, x,0+4);
				y=0+4;
				x+=1;
				for(i=0;i<3;i++)
				{
					CGContextMoveToPoint(context, x,y);
					CGContextAddLineToPoint(context, x,y-2);
					x++;
					y--;
				}
				//////////右半边//////////////////
				x=xStart;
				y=yStart-16;
				for(i=0;i<3;i++)
				{
					CGContextMoveToPoint(context, x,y);
					CGContextAddLineToPoint(context, x,y-2);
					x++;
					y--;
				}
				CGContextMoveToPoint(context, x,y);
				CGContextAddLineToPoint(context, x,0+4);
				y=0+4;
				x--;
				for(i=0;i<3;i++)
				{
					CGContextMoveToPoint(context, x,y);
					CGContextAddLineToPoint(context, x,y-2);
					x--;
					y--;
				}
			}
			break;
		case 7:
			{
				[self GetYzmOffset:(int *)&nX :(int *)&nY :2 :3];
				xStart=rect.origin.x+nX;
				yStart=height-(top+nY);
				
				CGContextMoveToPoint(context, xStart-4,yStart-2);
				CGContextAddLineToPoint(context, xStart+4,yStart-2);
				
				x=xStart+4;
				y=yStart-2;
				
				for(i=0;i<5;i++)
				{
					CGContextMoveToPoint(context, x,y);
					CGContextAddLineToPoint(context, x,y+4);
					x--;
					y-=3;
				}
			}
			break;
		case 8:
			{
				[self GetYzmOffset:(int *)&nX :(int *)&nY :2 :3];
				xStart=rect.origin.x+nX;
				yStart=top+nY;
				
				CGContextMoveToPoint(context, xStart-3,yStart+3);
				CGContextAddLineToPoint(context, xStart+3,yStart+3);
				CGContextAddLineToPoint(context, xStart+3,yStart+halfheight);
				CGContextMoveToPoint(context, xStart+4,yStart+4);
				CGContextAddLineToPoint(context, xStart+4,yStart+halfheight-1);
				CGContextMoveToPoint(context, xStart-3,yStart+3);
				CGContextAddLineToPoint(context, xStart-3,yStart+halfheight);
				CGContextMoveToPoint(context, xStart-4,yStart+4);
				CGContextAddLineToPoint(context, xStart-4,yStart+halfheight-1);
				
				CGContextMoveToPoint(context, xStart-3,yStart+halfheight);
				CGContextAddLineToPoint(context, xStart+3,yStart+halfheight);
				
				CGContextMoveToPoint(context, xStart-3,bottom-3);
				CGContextAddLineToPoint(context, xStart+3,bottom-3);
				CGContextAddLineToPoint(context, xStart+3,bottom-halfheight);
				CGContextMoveToPoint(context, xStart+4,bottom-4);
				CGContextAddLineToPoint(context, xStart+4,bottom-halfheight+1);
				CGContextMoveToPoint(context, xStart-3,bottom-3);
				CGContextAddLineToPoint(context, xStart-3,bottom-halfheight);
				CGContextMoveToPoint(context, xStart-4,bottom-4);
				CGContextAddLineToPoint(context, xStart-4,bottom-halfheight+1);
			}
			break;
		case 9:
			{	
				[self GetYzmOffset:(int *)&nX :(int *)&nY :2 :3];
				xStart=rect.origin.x+nX;
				yStart=height-top+nY-4;
				x=xStart;
				y=yStart-2;
				
				/////////////////左半边//////////////
				for(i=0;i<3;i++)
				{
					CGContextMoveToPoint(context, x,y);
					CGContextAddLineToPoint(context, x,y-2);
					x--;
					y--;
				}
				CGContextMoveToPoint(context, x,y);
				CGContextAddLineToPoint(context, x,0+25);
				y=0+25;
				x+=1;
				for(i=0;i<3;i++)
				{
					CGContextMoveToPoint(context, x,y);
					CGContextAddLineToPoint(context, x,y-2);
					x++;
					y--;
				}
				for(i=0;i<8;i++)
				{
					CGContextMoveToPoint(context, x,y);
					CGContextAddLineToPoint(context, x,y-3);
					x--;
					y-=2;
				}
			}
			break;
		default:
			break;
	}
	
	CGColorRelease(yzmcolor);
	CGContextStrokePath(context);
       CGContextRestoreGState(context);   
}


-(void) GetYzmOffset:(int *)nRetX :(int*)nRetY :(int)nX :(int)nY
{
	int nAddFlag=1;
	if(nX==0 || nY==0)	return;
	
	(*nRetX) = rand()%nX;
	(*nRetY) = rand()%nY;
	if((*nRetX)<(*nRetY))	nAddFlag=-1;
	
	(*nRetX) = (*nRetX)*nAddFlag;
	(*nRetY) = (*nRetY)*nAddFlag;
}

-(BOOL)IsValidYzm:(NSString *)inputyzm
{
	if(bshowyzm==NO)
		return NO;
	if(m_yzmstr==nil || inputyzm==nil)
		return NO;
	return [m_yzmstr isEqualToString:inputyzm];
}

#pragma mark touches相关
-(void) mouseUp:(NSEvent *)theEvent{
	[self GenYzm];
}

@end
