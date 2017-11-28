//
//  ETradeFuncBarView.m
//  tdxMac
//
//  Created by tdx on 11-10-25.
//  Copyright 2011 武汉. All rights reserved.
//

#import "ETradeFuncBarView.h"
#define PER_BUTTON_WIDTH 40
#define PER_LABEL_WIDTH 70
#define PER_DATE_WIDTH 105
#define PER_LABEL_HEIGHT 25
#define HEIGHTMARIN 2
#define SEPARATE_WIDTH 10
#define ZJLS_COM_FLAG 100000

@implementation ETradeFuncBarView
@synthesize nmaxpage,pageIndex,ntotalline,barViewDelegate;


- (id)initWithFrame:(NSRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code here.
    }
    return self;
}


- (id)initWithData:(NSRect)frame theData:(EGetData *)_eGetData parentView:(id)_parent{
    self = [super initWithData:frame theData:_eGetData];
    if (self) {
		parentView = _parent;
		
        m_zjlsbz=[[NSArray arrayWithObjects:@"所有币种",@"人民币",@"美元",@"港币",nil] retain];
        m_zjlsbzdm=[[NSArray arrayWithObjects:@"3",@"0",@"1",@"2",nil] retain];
        m_bzdm = 3;
        eGetData.saveDate.nzjlsBZ = m_bzdm;
		
		nextPageButton  = [[NSButton alloc] init];
		[nextPageButton setFrame:NSZeroRect];
		[[nextPageButton cell] setTitle:@"下页"];
		[nextPageButton setTarget:parentView];
		[nextPageButton setTag:2];
		[nextPageButton setAction:@selector(buttonClick:)];
		[self addSubview:nextPageButton];
		
		prePageButton  = [[NSButton alloc] init];
		[prePageButton setFrame:NSZeroRect];
		[[prePageButton cell] setTitle:@"上页"];
		[prePageButton setTarget:parentView];
		[prePageButton setTag:3];
		[prePageButton setAction:@selector(buttonClick:)];
		[self addSubview:prePageButton];
		
		firstPageButton  = [[NSButton alloc] init];
		[firstPageButton setFrame:NSZeroRect];
		[[firstPageButton cell] setTitle:@"首页"];
		[firstPageButton setTarget:parentView];
		[firstPageButton setTag:1];
		[firstPageButton setAction:@selector(buttonClick:)];
		[self addSubview:firstPageButton];
		
		lastPageButton  = [[NSButton alloc] init];
		[lastPageButton setFrame:NSZeroRect];
		[[lastPageButton cell] setTitle:@"尾页"];
		[lastPageButton setTarget:parentView];
		[lastPageButton setTag:4];
		[lastPageButton setAction:@selector(buttonClick:)];
		[self addSubview:lastPageButton];
		
		refreshButton  = [[NSButton alloc] init];
		[refreshButton setFrame:NSZeroRect];
		[[refreshButton cell] setTitle:@"刷新"];
		[refreshButton setTarget:parentView];
		[refreshButton setTag:5];
		[refreshButton setTarget:self];
		[refreshButton setAction:@selector(buttonClick:)];
		[self addSubview:refreshButton];
		
		//chedanButton
		chedanButton  = [[NSButton alloc] init];
		[chedanButton setFrame:NSZeroRect];
		[[chedanButton cell] setTitle:@"撤单"];
		[chedanButton setTarget:parentView];
		[chedanButton setTag:6];
		[chedanButton setTarget:self];
		[chedanButton setAction:@selector(buttonClick:)];
		[self addSubview:chedanButton];

		pageInfoLabel  = [[NSTextField alloc]init];
		[pageInfoLabel setEditable:NO];
		[pageInfoLabel setBackgroundColor:[NSColor clearColor]];
		[pageInfoLabel setBordered:NO];
		[pageInfoLabel setFrame:NSZeroRect];
		[[pageInfoLabel cell] setFont:[NSFont systemFontOfSize:13.0f]];
		[[pageInfoLabel cell] setTextColor:[NSColor blackColor]];
		[self addSubview:pageInfoLabel];
		
		
		rmbInfoLabel  = [[NSTextField alloc]init];
		[rmbInfoLabel setEditable:NO];
		[rmbInfoLabel setBackgroundColor:[NSColor clearColor]];
		[rmbInfoLabel setBordered:NO];
		[rmbInfoLabel setFrame:NSZeroRect];
		[[rmbInfoLabel cell] setTextColor:[NSColor blackColor]];
		[self addSubview:rmbInfoLabel];
		
		myInfoLabel  = [[NSTextField alloc]init];
		[myInfoLabel setEditable:NO];
		[myInfoLabel setBackgroundColor:[NSColor clearColor]];
		[myInfoLabel setBordered:NO];
		[myInfoLabel setFrame:NSZeroRect];
		[[myInfoLabel cell] setTextColor:[NSColor blackColor]];
		[self addSubview:myInfoLabel];
        
        gbInfoLabel  = [[NSTextField alloc]init];
        [gbInfoLabel setEditable:NO];
        [gbInfoLabel setBackgroundColor:[NSColor clearColor]];
        [gbInfoLabel setBordered:NO];
        [gbInfoLabel setFrame:NSZeroRect];
        [[gbInfoLabel cell] setTextColor:[NSColor blackColor]];
        [self addSubview:gbInfoLabel];
		
		
		sDate = [[NSDatePicker alloc] init];
		[sDate setFrame:NSZeroRect];
		[sDate setDrawsBackground:YES];
		[sDate setBezeled:YES];
		[self addSubview:sDate];
		[sDate setAction:@selector(sDateChange)];
		[sDate setMaxDate:[NSDate date]];
		
		
		eDate = [[NSDatePicker alloc] init];
		[eDate setFrame:NSZeroRect];
		[eDate setDrawsBackground:YES];
		[eDate setBezeled:YES];
		[eDate setMaxDate:[NSDate date]];
		[eDate setAction:@selector(eDateChange)];
		[self addSubview:eDate];
		
		
		
		sDateLabel  = [[NSTextField alloc]init];
		[sDateLabel setEditable:NO];
		[sDateLabel setBackgroundColor:[NSColor clearColor]];
		[sDateLabel setBordered:NO];
		[sDateLabel setFrame:NSZeroRect];
		[[sDateLabel cell] setTextColor:[NSColor blackColor]];
		[[sDateLabel cell] setTitle:@"起始日期:"];
		[self addSubview:sDateLabel];
		
		eDateLabel  = [[NSTextField alloc]init];
		[eDateLabel setEditable:NO];
		[eDateLabel setBackgroundColor:[NSColor clearColor]];
		[eDateLabel setBordered:NO];
		[eDateLabel setFrame:NSZeroRect];
		[[eDateLabel cell] setTextColor:[NSColor blackColor]];
		[[eDateLabel cell] setTitle:@"终止日期:"];
		[self addSubview:eDateLabel];
		
		
		bankComboBox = [[NSComboBox alloc] initWithFrame:NSZeroRect];
		[bankComboBox setBackgroundColor:[NSColor clearColor]];
		[bankComboBox setEditable:NO];
		[bankComboBox setUsesDataSource:YES];
		[bankComboBox setDelegate:self];
		[bankComboBox setDataSource:self];
		[self addSubview:bankComboBox];
        
        zjlsBzLabel  = [[NSTextField alloc]init];
        [zjlsBzLabel setEditable:NO];
        [zjlsBzLabel setBackgroundColor:[NSColor clearColor]];
        [zjlsBzLabel setBordered:NO];
        [zjlsBzLabel setFrame:NSZeroRect];
        [[zjlsBzLabel cell] setTextColor:[NSColor blackColor]];
        [[zjlsBzLabel cell] setTitle:@"币种:"];
        [self addSubview:zjlsBzLabel];
        
        bzComboBox = [[NSComboBox alloc] initWithFrame:NSZeroRect];
        [bzComboBox setBackgroundColor:[NSColor clearColor]];
        [bzComboBox setEditable:NO];
        [bzComboBox setTag:ZJLS_COM_FLAG];
        [bzComboBox setUsesDataSource:YES];
        [bzComboBox setDelegate:self];
        [bzComboBox setDataSource:self];
        [[bzComboBox cell] setTitle:@"所有币种"];
        [self addSubview:bzComboBox];
        
	}
	return self;
}
-(void)sDateChange{
	//NSLog(@"123");
	NSDateFormatter *dateFormatter = [[[NSDateFormatter alloc] init]autorelease];
	[dateFormatter setDateFormat:@"yyyyMMdd"];
	NSString * currentDate = [dateFormatter stringFromDate:[sDate dateValue]];
	eGetData.saveDate.nStartDate = atoi([currentDate UTF8String]);
	
}
	
-(void)eDateChange{
	//NSLog(@"456");
	NSDateFormatter* dateFormatter = [[[NSDateFormatter alloc] init]autorelease];
	[dateFormatter setDateFormat:@"yyyyMMdd"];
	NSString * currentDate = [dateFormatter stringFromDate:[eDate dateValue]];
	eGetData.saveDate.nEndDate = atoi([currentDate UTF8String]);
}

-(void)buttonClick:(id)sender{
	[barViewDelegate getButtonClick:[sender tag]];
}

-(void)clearAllView{
	[nextPageButton setFrame:NSZeroRect];
	[prePageButton setFrame:NSZeroRect];
	[firstPageButton setFrame:NSZeroRect];
	[lastPageButton setFrame:NSZeroRect];
	[refreshButton setFrame:NSZeroRect];
	[chedanButton setFrame:NSZeroRect];
	
	[pageInfoLabel setFrame:NSZeroRect];
	[rmbInfoLabel setFrame:NSZeroRect];
	[gbInfoLabel setFrame:NSZeroRect];
	[myInfoLabel setFrame:NSZeroRect];
	
	[sDateLabel setFrame:NSZeroRect];
	[eDateLabel setFrame:NSZeroRect];
	[sDate setFrame:NSZeroRect];
	[eDate setFrame:NSZeroRect];
    [zjlsBzLabel setFrame:NSZeroRect];
    
    [bzComboBox setFrame:NSZeroRect];
	[bankComboBox setFrame:NSZeroRect];
}

-(void) setFrame:(NSRect)frameRect{
	[super setFrame:frameRect];
	viewRect = frameRect;
}

-(void)setShowType:(int)_showType{
	NSTimeInterval tstart;
	NSDateFormatter* dateFormatter;
	NSString * currentDate;
	showType= _showType;
    int nspanday=7;
#ifdef IMAC_ZXZQ
    nspanday=1;
#endif
	[self clearAllView];
	switch (showType) {
		case TDX_ZJYE:
		case TDX_GFCX:
			[[refreshButton cell] setTitle:@"刷新"];
			break;
		case TDX_CDCX:
			[[refreshButton cell] setTitle:@"刷新"];
			break;
		case TDX_DRWT:
			[[refreshButton cell] setTitle:@"刷新"];
			;
			break;
		case TDX_DRCJ:
			[[refreshButton cell] setTitle:@"刷新"];
			;
			break;
		case TDX_LSWT:
			[[refreshButton cell] setTitle:@"查询"];
            if([self.barViewDelegate IsLscxFlag])
            {
                [sDateLabel setFrame:NSMakeRect(0, HEIGHTMARIN, PER_LABEL_WIDTH, viewRect.size.height - 4*HEIGHTMARIN)];
                [sDate setFrame:NSMakeRect(PER_LABEL_WIDTH, HEIGHTMARIN, PER_DATE_WIDTH, viewRect.size.height - 2*HEIGHTMARIN)];
                [eDateLabel setFrame:NSMakeRect(PER_LABEL_WIDTH+PER_DATE_WIDTH+SEPARATE_WIDTH, HEIGHTMARIN, PER_LABEL_WIDTH, viewRect.size.height - 4*HEIGHTMARIN)];
                [eDate setFrame:NSMakeRect(PER_LABEL_WIDTH*2+PER_DATE_WIDTH+SEPARATE_WIDTH, HEIGHTMARIN, PER_DATE_WIDTH, viewRect.size.height - 2*HEIGHTMARIN)];
            }
			
			tstart=[[NSDate date] timeIntervalSince1970];
			[sDate setDateValue:[[NSDate alloc] initWithTimeIntervalSince1970:tstart-nspanday*24*3600]];
			[eDate setDateValue:[NSDate date]];
			dateFormatter = [[[NSDateFormatter alloc] init]autorelease];
			[dateFormatter setDateFormat:@"yyyyMMdd"];
			currentDate = [dateFormatter stringFromDate:[sDate dateValue]];
			eGetData.saveDate.nStartDate = atoi([currentDate UTF8String]);
			currentDate = [dateFormatter stringFromDate:[eDate dateValue]];
			eGetData.saveDate.nEndDate = atoi([currentDate UTF8String]);
			break;
		case TDX_LSCJ:
			[[refreshButton cell] setTitle:@"查询"];
            if([self.barViewDelegate IsLscxFlag])
            {
                [sDateLabel setFrame:NSMakeRect(0, HEIGHTMARIN, PER_LABEL_WIDTH, viewRect.size.height - 4*HEIGHTMARIN)];
                [sDate setFrame:NSMakeRect(PER_LABEL_WIDTH, HEIGHTMARIN, PER_DATE_WIDTH, viewRect.size.height - 2*HEIGHTMARIN)];
                [eDateLabel setFrame:NSMakeRect(PER_LABEL_WIDTH+PER_DATE_WIDTH+SEPARATE_WIDTH, HEIGHTMARIN, PER_LABEL_WIDTH, viewRect.size.height - 4*HEIGHTMARIN)];
                [eDate setFrame:NSMakeRect(PER_LABEL_WIDTH*2+PER_DATE_WIDTH+SEPARATE_WIDTH, HEIGHTMARIN, PER_DATE_WIDTH, viewRect.size.height - 2*HEIGHTMARIN)];
            }
			
			tstart=[[NSDate date] timeIntervalSince1970];
			[sDate setDateValue:[[NSDate alloc] initWithTimeIntervalSince1970:tstart-nspanday*24*3600]];
			[eDate setDateValue:[[NSDate alloc] initWithTimeIntervalSince1970:tstart-24*3600]];
			dateFormatter = [[[NSDateFormatter alloc] init]autorelease];
			[dateFormatter setDateFormat:@"yyyyMMdd"];
			currentDate = [dateFormatter stringFromDate:[sDate dateValue]];
			eGetData.saveDate.nStartDate = atoi([currentDate UTF8String]);
			currentDate = [dateFormatter stringFromDate:[eDate dateValue]];
			eGetData.saveDate.nEndDate = atoi([currentDate UTF8String]);
			
			break;
		case TDX_GDCX:
        case TDX_IPOSGED:
			[[refreshButton cell] setTitle:@"刷新"];
			;
			break;
        case TDX_ZJLS:
			[[refreshButton cell] setTitle:@"查询"];
            
            if([self.barViewDelegate IsLscxFlag])
            {
                [sDateLabel setFrame:NSMakeRect(0, HEIGHTMARIN, PER_LABEL_WIDTH, viewRect.size.height - 4*HEIGHTMARIN)];
                [sDate setFrame:NSMakeRect(PER_LABEL_WIDTH, HEIGHTMARIN, PER_DATE_WIDTH, viewRect.size.height - 2*HEIGHTMARIN)];
                [eDateLabel setFrame:NSMakeRect(PER_LABEL_WIDTH+PER_DATE_WIDTH+SEPARATE_WIDTH, HEIGHTMARIN, PER_LABEL_WIDTH, viewRect.size.height - 4*HEIGHTMARIN)];
                [eDate setFrame:NSMakeRect(PER_LABEL_WIDTH*2+PER_DATE_WIDTH+SEPARATE_WIDTH, HEIGHTMARIN, PER_DATE_WIDTH, viewRect.size.height - 2*HEIGHTMARIN)];
#ifdef IMAC_PAZQ
                [zjlsBzLabel setFrame:NSMakeRect(PER_LABEL_WIDTH*3+PER_DATE_WIDTH+SEPARATE_WIDTH+50, HEIGHTMARIN, PER_LABEL_WIDTH, viewRect.size.height - 4*HEIGHTMARIN)];
                [bzComboBox setFrame:NSMakeRect(PER_LABEL_WIDTH*4+PER_DATE_WIDTH+SEPARATE_WIDTH+20, HEIGHTMARIN-4, PER_DATE_WIDTH, viewRect.size.height - 2*HEIGHTMARIN+6)];
#endif
            }
			
			tstart=[[NSDate date] timeIntervalSince1970];
			[sDate setDateValue:[[NSDate alloc] initWithTimeIntervalSince1970:tstart-nspanday*24*3600]];
			[eDate setDateValue:[NSDate date]];
			dateFormatter = [[[NSDateFormatter alloc] init]autorelease];
			[dateFormatter setDateFormat:@"yyyyMMdd"];
			currentDate = [dateFormatter stringFromDate:[sDate dateValue]];
			eGetData.saveDate.nStartDate = atoi([currentDate UTF8String]);
			currentDate = [dateFormatter stringFromDate:[eDate dateValue]];
			eGetData.saveDate.nEndDate = atoi([currentDate UTF8String]);
			
			;
			break;
        case TDX_XGZQCX:
            [[refreshButton cell] setTitle:@"查询"];
            
            [sDateLabel setFrame:NSMakeRect(0, HEIGHTMARIN, PER_LABEL_WIDTH, viewRect.size.height - 4*HEIGHTMARIN)];
            [sDate setFrame:NSMakeRect(PER_LABEL_WIDTH, HEIGHTMARIN, PER_DATE_WIDTH, viewRect.size.height - 2*HEIGHTMARIN)];
            [eDateLabel setFrame:NSMakeRect(PER_LABEL_WIDTH+PER_DATE_WIDTH+SEPARATE_WIDTH, HEIGHTMARIN, PER_LABEL_WIDTH, viewRect.size.height - 4*HEIGHTMARIN)];
            [eDate setFrame:NSMakeRect(PER_LABEL_WIDTH*2+PER_DATE_WIDTH+SEPARATE_WIDTH, HEIGHTMARIN, PER_DATE_WIDTH, viewRect.size.height - 2*HEIGHTMARIN)];
            
            tstart=[[NSDate date] timeIntervalSince1970];
            [sDate setDateValue:[[NSDate alloc] initWithTimeIntervalSince1970:tstart-nspanday*24*3600]];
            [eDate setDateValue:[NSDate date]];
            dateFormatter = [[[NSDateFormatter alloc] init]autorelease];
            [dateFormatter setDateFormat:@"yyyyMMdd"];
            currentDate = [dateFormatter stringFromDate:[sDate dateValue]];
            eGetData.saveDate.nStartDate = atoi([currentDate UTF8String]);
            currentDate = [dateFormatter stringFromDate:[eDate dateValue]];
            eGetData.saveDate.nEndDate = atoi([currentDate UTF8String]);
            
            ;
            break;
		case TDX_CJHZ:
			[[refreshButton cell] setTitle:@"刷新"];
			;
			break;
		case TDX_PHCX:
			[[refreshButton cell] setTitle:@"查询"];
            if([self.barViewDelegate IsLscxFlag])
            {
                [sDateLabel setFrame:NSMakeRect(0, HEIGHTMARIN, PER_LABEL_WIDTH, viewRect.size.height - 4*HEIGHTMARIN)];
                [sDate setFrame:NSMakeRect(PER_LABEL_WIDTH, HEIGHTMARIN, PER_DATE_WIDTH, viewRect.size.height - 2*HEIGHTMARIN)];
                [eDateLabel setFrame:NSMakeRect(PER_LABEL_WIDTH+PER_DATE_WIDTH+SEPARATE_WIDTH, HEIGHTMARIN, PER_LABEL_WIDTH, viewRect.size.height - 4*HEIGHTMARIN)];
                [eDate setFrame:NSMakeRect(PER_LABEL_WIDTH*2+PER_DATE_WIDTH+SEPARATE_WIDTH, HEIGHTMARIN, PER_DATE_WIDTH, viewRect.size.height - 2*HEIGHTMARIN)];
            }
			
			tstart=[[NSDate date] timeIntervalSince1970];
			[sDate setDateValue:[[NSDate alloc] initWithTimeIntervalSince1970:tstart-nspanday*24*3600]];
			[eDate setDateValue:[NSDate date]];
			dateFormatter = [[[NSDateFormatter alloc] init]autorelease];
			[dateFormatter setDateFormat:@"yyyyMMdd"];
			currentDate = [dateFormatter stringFromDate:[sDate dateValue]];
			eGetData.saveDate.nStartDate = atoi([currentDate UTF8String]);
			currentDate = [dateFormatter stringFromDate:[eDate dateValue]];
			eGetData.saveDate.nEndDate = atoi([currentDate UTF8String]);
			
			;
			break;	
		case TDX_ZZCX:
			[[refreshButton cell] setTitle:@"查询"];
            signed char byhcomboflag=YES;
#ifdef IMAC_ZXZQ
            byhcomboflag=NO;
#endif
            
#ifdef IMAC_PAZQ
            byhcomboflag=NO;
#endif
            int nleft=0;
            if(byhcomboflag)
            {
                [bankComboBox setFrame:NSMakeRect(nleft, 0, 200,  viewRect.size.height)];
                nleft+=200;
            }
            else
                [bankComboBox setFrame:NSZeroRect];
			if(m_pyhmx==nil)
			{
				if(eGetData.clientinfos.yhxxs.yhmxs && [eGetData.clientinfos.yhxxs.yhmxs count])
				{
					m_pyhmx=[eGetData.clientinfos.yhxxs.yhmxs objectAtIndex:0];
					if(m_pyhmx)
					{
						NSString *tmpstr=[NSString stringWithFormat:@"%@  %@",m_pyhmx.yhdm,m_pyhmx.yhmc];
						[[bankComboBox cell] setTitle:tmpstr];
						eGetData.inputSave.yhdm=m_pyhmx.yhdm;
					}
				}
			}
			if([self.barViewDelegate IsLscxFlag])
            {
                [sDateLabel setFrame:NSMakeRect(nleft, HEIGHTMARIN, PER_LABEL_WIDTH, viewRect.size.height - 4*HEIGHTMARIN)];
                [sDate setFrame:NSMakeRect(nleft+PER_LABEL_WIDTH, HEIGHTMARIN, PER_DATE_WIDTH, viewRect.size.height - 2*HEIGHTMARIN)];
                [eDateLabel setFrame:NSMakeRect(nleft+PER_LABEL_WIDTH+PER_DATE_WIDTH+SEPARATE_WIDTH, HEIGHTMARIN, PER_LABEL_WIDTH, viewRect.size.height - 4*HEIGHTMARIN)];
                [eDate setFrame:NSMakeRect(nleft+PER_LABEL_WIDTH*2+PER_DATE_WIDTH+SEPARATE_WIDTH, HEIGHTMARIN, PER_DATE_WIDTH, viewRect.size.height - 2*HEIGHTMARIN)];
            }
			
			tstart=[[NSDate date] timeIntervalSince1970];
			[sDate setDateValue:[[NSDate alloc] initWithTimeIntervalSince1970:tstart-nspanday*24*3600]];
			[eDate setDateValue:[NSDate date]];
			dateFormatter = [[[NSDateFormatter alloc] init]autorelease];
			[dateFormatter setDateFormat:@"yyyyMMdd"];
			currentDate = [dateFormatter stringFromDate:[sDate dateValue]];
			eGetData.saveDate.nStartDate = atoi([currentDate UTF8String]);
			currentDate = [dateFormatter stringFromDate:[eDate dateValue]];
			eGetData.saveDate.nEndDate = atoi([currentDate UTF8String]);
			;
			break;
	
		default:
			break;
	}
}
#pragma mark combobox Delegate相关
-(NSInteger) numberOfItemsInComboBox:(NSComboBox *)aComboBox{

    if(aComboBox.tag == ZJLS_COM_FLAG)
    {
        return [m_zjlsbz count];
    }
    else
    {
        return [eGetData.clientinfos.yhxxs.yhmxs count];
    }
}

-(id) comboBox:(NSComboBox *)aComboBox objectValueForItemAtIndex:(NSInteger)index{
    if(aComboBox.tag == ZJLS_COM_FLAG)
    {
        if(index >= 0)
        {
            return [m_zjlsbz objectAtIndex:index];
        }
    }
    else
    {
        Yhxxmx * tempYhxx;
        if( (index >= [eGetData.clientinfos.yhxxs.yhmxs count])||(index <0) ){
            return nil;
        }
        else {
            tempYhxx = [eGetData.clientinfos.yhxxs.yhmxs objectAtIndex:index];
            
            if(tempYhxx)
            {
                NSString *tmpstr=[NSString stringWithFormat:@"%@  %@",tempYhxx.yhdm,tempYhxx.yhmc];
                return tmpstr;
            }
            else {
                return nil;
            }
        }
    }


	
	return nil;
}

-(void) comboBoxSelectionDidChange:(NSNotification *)notification{
    NSComboBox * tempCombobox = [notification object];
    if(tempCombobox.tag == ZJLS_COM_FLAG)
    {
        int tempInt = [tempCombobox indexOfSelectedItem];
        if(index >= 0)
        {
            m_bzdm = [[m_zjlsbzdm objectAtIndex:tempInt] intValue];
            //NSLog(@"m_bzdm:%d",m_bzdm);
            eGetData.saveDate.nzjlsBZ = m_bzdm;
        }
    }
    else
    {
        int tempInt = [bankComboBox indexOfSelectedItem];
        if(tempInt>=0 && tempInt<[eGetData.clientinfos.yhxxs.yhmxs count])
            m_pyhmx=[eGetData.clientinfos.yhxxs.yhmxs objectAtIndex:tempInt];
        else
            m_pyhmx=nil;
        if(m_pyhmx)
        {
            eGetData.inputSave.yhdm=m_pyhmx.yhdm;
        }
        [barViewDelegate getButtonClick:5];
    }

}


-(void)resetbarView{
	if (showType == TDX_GFCX) {
		ST_ZJGFINFO tmpzjgf=eGetData.clientinfos.stzjgf;
        signed char bflag=NO;
        
        [refreshButton setFrame:NSMakeRect(viewRect.size.width-PER_BUTTON_WIDTH, HEIGHTMARIN, PER_BUTTON_WIDTH, viewRect.size.height - 2*HEIGHTMARIN)];
        float tempFloat = refreshButton.frame.origin.x-PER_BUTTON_WIDTH;
        
        
        if(self.nmaxpage<=1){
            ;
        }
        else if(self.nmaxpage==2){
            if(self.pageIndex==1){
                [prePageButton setFrame:NSMakeRect(tempFloat, HEIGHTMARIN, PER_BUTTON_WIDTH, viewRect.size.height - 2*HEIGHTMARIN)];
                [nextPageButton setFrame:NSMakeRect(0, 0, 0, 0)];
                tempFloat = tempFloat - PER_BUTTON_WIDTH;
            }
            else {
                [prePageButton setFrame:NSMakeRect(0, 0, 0, 0)];
                [nextPageButton setFrame:NSMakeRect(tempFloat, HEIGHTMARIN, PER_BUTTON_WIDTH, viewRect.size.height - 2*HEIGHTMARIN)];
                tempFloat = tempFloat - PER_BUTTON_WIDTH;
            }
        }
        else{
            
            [nextPageButton setFrame:NSMakeRect(tempFloat, HEIGHTMARIN, PER_BUTTON_WIDTH, viewRect.size.height - 2*HEIGHTMARIN)];
            tempFloat = tempFloat - PER_BUTTON_WIDTH;
            [prePageButton setFrame:NSMakeRect(tempFloat, HEIGHTMARIN, PER_BUTTON_WIDTH, viewRect.size.height - 2*HEIGHTMARIN)];
            tempFloat = tempFloat - PER_BUTTON_WIDTH;
            
            if(self.pageIndex>=(self.nmaxpage-1))
                [nextPageButton setFrame:NSMakeRect(0, 0, 0, 0)];
            else if(self.pageIndex==0)
                [prePageButton setFrame:NSMakeRect(0, 0, 0, 0)];
        }
        
        
        NSString * tempString ;
        if (nmaxpage == 0) {
            tempString = @"共0条";
        }
        else if(nmaxpage == -1){
            tempString =@"";
        }
        else {
#ifdef QUERY_LOOPEND
            tempString=[NSString stringWithFormat:@"共%i条",ntotalline];
#else
            tempString=[NSString stringWithFormat:@"%i/%i页,共%i条",pageIndex+1,nmaxpage,ntotalline];
#endif
        }
        
        NSDictionary * tempAttributes= [eGetData getAttributes:MAC_CHINESEFONT fontSize:18.0f theColor:[NSColor whiteColor] theAliment:NSCenterTextAlignment];
        NSRect temprect = [tempString boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
        int nleft=tempFloat+PER_BUTTON_WIDTH-temprect.size.width;
        
        [[pageInfoLabel cell] setTitle:tempString];
        
        
        tempFloat = viewRect.size.height-PER_LABEL_HEIGHT;
        NSString* displayString = @"";
        
		if(tmpzjgf.zzc[0]>0) {
            bflag=YES;
			[rmbInfoLabel setFrame:NSMakeRect(0, tempFloat, viewRect.size.width-200, PER_LABEL_HEIGHT)];
			tempFloat = tempFloat  - PER_LABEL_HEIGHT;
			
			[[rmbInfoLabel cell] setTextColor:COLOR_GRID_NORMALCOLOR];
            displayString = [NSString stringWithFormat:@"人民币: 余额:%.2f  可用:%.2f  可取:%.2f  股票市值:%.2f  资产:%.2f  盈亏:%.2f",tmpzjgf.ye[0],tmpzjgf.keyong[0],tmpzjgf.kqzj[0],tmpzjgf.zsz[0],tmpzjgf.zzc[0],tmpzjgf.fdyk[0]];
            
#ifdef  IMAC_ZXJT
            displayString = [NSString stringWithFormat:@"人民币: 余额:%.2f  可用:%.2f  股票市值:%.2f  资产:%.2f  盈亏:%.2f",tmpzjgf.ye[0],tmpzjgf.keyong[0],tmpzjgf.zsz[0],tmpzjgf.zzc[0],tmpzjgf.fdyk[0]];
#endif
            
#ifdef  IMAC_ZTZQ
            displayString = [NSString stringWithFormat:@"人民币: 余额:%.2f  可用:%.2f  参考市值:%.2f  资产:%.2f  参考盈亏:%.2f",tmpzjgf.ye[0],tmpzjgf.keyong[0],tmpzjgf.zsz[0],tmpzjgf.zzc[0],tmpzjgf.fdyk[0]];
#endif
            
#ifdef  IMAC_PAZQ
            displayString = [NSString stringWithFormat:@"人民币: 余额:%.2f 可用:%.2f 可取:%.2f 在途:%.2f 参考市值:%.2f  资产:%.2f  参考盈亏:%.2f",tmpzjgf.ye[0],tmpzjgf.keyong[0],tmpzjgf.kqzj[0],tmpzjgf.ztzj[0],tmpzjgf.zsz[0],tmpzjgf.zzc[0],tmpzjgf.fdyk[0]];
#endif
            
            [[rmbInfoLabel cell] setTitle:displayString];
		}
		if(tmpzjgf.zzc[1]>0)  {
            bflag=YES;
			[myInfoLabel setFrame:NSMakeRect(0, tempFloat, viewRect.size.width-200, PER_LABEL_HEIGHT)];
			tempFloat = tempFloat  - PER_LABEL_HEIGHT;
			
			
			[[myInfoLabel cell] setTextColor:COLOR_GRID_NORMALCOLOR];
            
            displayString = [NSString stringWithFormat:@"美  元 : 余额:%.3f  可用:%.3f  可取:%.3f  股票市值:%.3f  资产:%.3f  盈亏:%.3f",tmpzjgf.ye[1],tmpzjgf.keyong[1],tmpzjgf.kqzj[1],tmpzjgf.zsz[1],tmpzjgf.zzc[1],tmpzjgf.fdyk[1]];
#ifdef  IMAC_ZXJT
            displayString = [NSString stringWithFormat:@"美  元 : 余额:%.3f  可用:%.3f  股票市值:%.3f  资产:%.3f  盈亏:%.3f",tmpzjgf.ye[1],tmpzjgf.keyong[1],tmpzjgf.zsz[1],tmpzjgf.zzc[1],tmpzjgf.fdyk[1]];
#endif
            
#ifdef  IMAC_ZTZQ
            displayString = [NSString stringWithFormat:@"美  元 : 余额:%.3f  可用:%.3f  参考市值:%.3f  资产:%.3f  参考盈亏:%.3f",tmpzjgf.ye[1],tmpzjgf.keyong[1],tmpzjgf.zsz[1],tmpzjgf.zzc[1],tmpzjgf.fdyk[1]];
#endif
#ifdef  IMAC_PAZQ
            displayString = [NSString stringWithFormat:@"美  元 : 余额:%.2f 可用:%.2f 可取:%.2f 在途:%.2f 参考市值:%.2f  资产:%.2f  参考盈亏:%.2f",tmpzjgf.ye[1],tmpzjgf.keyong[1],tmpzjgf.kqzj[1],tmpzjgf.ztzj[1],tmpzjgf.zsz[1],tmpzjgf.zzc[1],tmpzjgf.fdyk[1]];
#endif
            [[myInfoLabel cell] setTitle:displayString];
		}
		
		if(tmpzjgf.zzc[2]>0)  {
            bflag=YES;
			[gbInfoLabel setFrame:NSMakeRect(0, tempFloat, viewRect.size.width-200, PER_LABEL_HEIGHT)];
			tempFloat = tempFloat  - PER_LABEL_HEIGHT;
			
			[[gbInfoLabel cell] setTextColor:COLOR_GRID_NORMALCOLOR];
            displayString = [NSString stringWithFormat:@"港  币 : 余额:%.2f  可用:%.2f  可取:%.2f  股票市值:%.2f  资产:%.2f  盈亏:%.2f",tmpzjgf.ye[2],tmpzjgf.keyong[2],tmpzjgf.kqzj[2],tmpzjgf.zsz[2],tmpzjgf.zzc[2],tmpzjgf.fdyk[2]];
#ifdef  IMAC_ZXJT
            displayString = [NSString stringWithFormat:@"港  币 : 余额:%.2f  可用:%.2f  股票市值:%.2f  资产:%.2f  盈亏:%.2f",tmpzjgf.ye[2],tmpzjgf.keyong[2],tmpzjgf.zsz[2],tmpzjgf.zzc[2],tmpzjgf.fdyk[2]];
#endif
#ifdef  IMAC_ZTZQ
            displayString = [NSString stringWithFormat:@"港  币 : 余额:%.2f  可用:%.2f  参考市值:%.2f  资产:%.2f  参考盈亏:%.2f",tmpzjgf.ye[2],tmpzjgf.keyong[2],tmpzjgf.zsz[2],tmpzjgf.zzc[2],tmpzjgf.fdyk[2]];
#endif
#ifdef  IMAC_PAZQ
            displayString = [NSString stringWithFormat:@"港  币 : 余额:%.2f 可用:%.2f 可取:%.2f 在途:%.2f 参考市值:%.2f  资产:%.2f  参考盈亏:%.2f",tmpzjgf.ye[2],tmpzjgf.keyong[2],tmpzjgf.kqzj[2],tmpzjgf.ztzj[2],tmpzjgf.zsz[2],tmpzjgf.zzc[2],tmpzjgf.fdyk[2]];
#endif
            [[gbInfoLabel cell] setTitle:displayString];
		}
        if (bflag==NO) {
            [rmbInfoLabel setFrame:NSMakeRect(0, tempFloat, viewRect.size.width-200, PER_LABEL_HEIGHT)];
            tempFloat = tempFloat  - PER_LABEL_HEIGHT;
            
            [[rmbInfoLabel cell] setTextColor:COLOR_GRID_NORMALCOLOR];
#ifdef  IMAC_ZXJT
            displayString = [NSString stringWithFormat:@"人民币: 余额:%.2f  可用:%.2f  股票市值:%.2f  资产:%.2f  盈亏:%.2f",tmpzjgf.ye[0],tmpzjgf.keyong[0],tmpzjgf.zsz[0],tmpzjgf.zzc[0],tmpzjgf.fdyk[0]]];
#else
            displayString = [NSString stringWithFormat:@"人民币: 余额:%.2f  可用:%.2f  可取:%.2f  股票市值:%.2f  资产:%.2f  盈亏:%.2f",tmpzjgf.ye[0],tmpzjgf.keyong[0],tmpzjgf.kqzj[0],tmpzjgf.zsz[0],tmpzjgf.zzc[0],tmpzjgf.fdyk[0]];
#endif
#ifdef  IMAC_ZTZQ
            displayString = [NSString stringWithFormat:@"人民币: 余额:%.2f  可用:%.2f  参考市值:%.2f  资产:%.2f  参考盈亏:%.2f",tmpzjgf.ye[0],tmpzjgf.keyong[0],tmpzjgf.zsz[0],tmpzjgf.zzc[0],tmpzjgf.fdyk[0]];
#endif
            
            [[rmbInfoLabel cell] setTitle:displayString];
        }
        
        [refreshButton setFrame:NSMakeRect(viewRect.size.width-PER_BUTTON_WIDTH, tempFloat+PER_LABEL_HEIGHT+2, PER_BUTTON_WIDTH, PER_LABEL_HEIGHT)];
        [pageInfoLabel setFrame:NSMakeRect(nleft, tempFloat+PER_LABEL_HEIGHT, temprect.size.width, PER_LABEL_HEIGHT)];
        
	}
	else {
		[refreshButton setFrame:NSMakeRect(viewRect.size.width-PER_BUTTON_WIDTH, HEIGHTMARIN, PER_BUTTON_WIDTH, viewRect.size.height - 2*HEIGHTMARIN)];		
		float tempFloat = refreshButton.frame.origin.x-PER_BUTTON_WIDTH;
		
		if (showType == TDX_CDCX || showType == TDX_DBPHZCDCX) {
			[chedanButton setFrame:NSMakeRect(tempFloat, HEIGHTMARIN, PER_BUTTON_WIDTH, viewRect.size.height - 2*HEIGHTMARIN)];
			tempFloat = tempFloat - PER_BUTTON_WIDTH;
		}
		
		if(self.nmaxpage<=1){
			;
		}
		else if(self.nmaxpage==2){
			if(self.pageIndex==1){
				[prePageButton setFrame:NSMakeRect(tempFloat, HEIGHTMARIN, PER_BUTTON_WIDTH, viewRect.size.height - 2*HEIGHTMARIN)];
                [nextPageButton setFrame:NSMakeRect(0, 0, 0, 0)];
				tempFloat = tempFloat - PER_BUTTON_WIDTH;
			}
			else {
                [prePageButton setFrame:NSMakeRect(0, 0, 0, 0)];
				[nextPageButton setFrame:NSMakeRect(tempFloat, HEIGHTMARIN, PER_BUTTON_WIDTH, viewRect.size.height - 2*HEIGHTMARIN)];
				tempFloat = tempFloat - PER_BUTTON_WIDTH;
			}
		}
		else{
            
            [nextPageButton setFrame:NSMakeRect(tempFloat, HEIGHTMARIN, PER_BUTTON_WIDTH, viewRect.size.height - 2*HEIGHTMARIN)];
            tempFloat = tempFloat - PER_BUTTON_WIDTH;
            [prePageButton setFrame:NSMakeRect(tempFloat, HEIGHTMARIN, PER_BUTTON_WIDTH, viewRect.size.height - 2*HEIGHTMARIN)];
            tempFloat = tempFloat - PER_BUTTON_WIDTH;
    
			if(self.pageIndex>=(self.nmaxpage-1))
				[nextPageButton setFrame:NSMakeRect(0, 0, 0, 0)];
			else if(self.pageIndex==0)
                [prePageButton setFrame:NSMakeRect(0, 0, 0, 0)];
		}
		
		
		NSString * tempString ;
		if (nmaxpage == 0) {
			tempString = @"共0条";
		}
		else if(nmaxpage == -1){
			tempString =@"";
		}
		else {
#ifdef QUERY_LOOPEND
            tempString=[NSString stringWithFormat:@"共%i条",ntotalline];
#else
            tempString=[NSString stringWithFormat:@"%i/%i页,共%i条",pageIndex+1,nmaxpage,ntotalline];
#endif
		}
		
		NSDictionary * tempAttributes= [eGetData getAttributes:MAC_CHINESEFONT fontSize:18.0f theColor:[NSColor whiteColor] theAliment:NSCenterTextAlignment];
		NSRect temprect = [tempString boundingRectWithSize:NSMakeSize(0, 0) options:NSStringDrawingUsesLineFragmentOrigin attributes:tempAttributes];
		
		[pageInfoLabel setFrame:NSMakeRect(tempFloat+PER_BUTTON_WIDTH-temprect.size.width, HEIGHTMARIN, temprect.size.width, viewRect.size.height - 2*HEIGHTMARIN)];
		[[pageInfoLabel cell] setTitle:tempString];
	}

}

- (void)drawRect:(NSRect)dirtyRect {

	[COLOR_TRADEBAR_BACKGROUND set];
	NSRectFill(dirtyRect);
}

@end
