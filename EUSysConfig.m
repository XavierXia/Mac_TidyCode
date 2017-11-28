//
//  EUSysConfig.m
//  tdxMac
//
//  Created by tdx on 11-12-17.
//  Copyright 2011 武汉. All rights reserved.
//

#import "EUSysConfig.h"
#define HQSITE_COM_FLAG 1
#define JYSITE_COM_FLAG 2
#define COUNT_Text_FLAG 3
#define LOCKSPAN_TEXT_FLAG 4

@implementation EUSysConfig
@synthesize showDelegate,eGetData,hqSiteComboBox,jySiteComboBox,autoRefresh,refreshCountText,autoFindbest;
@synthesize httpAgentFlag,agentAddressText,agentPortText,agentUserText,agentPasswordText,jylabelText,lockspanText;

-(id) initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil eGetData:(EGetData *)_eGetData{
	self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
   	eGetData = _eGetData;
    }
    return self;
}
-(void)showInfo{
	
	
	
	[hqSiteComboBox setTag:HQSITE_COM_FLAG];
	[hqSiteComboBox setDelegate:self];
	[hqSiteComboBox setDataSource:self];
    
    TradeSite *pSite;
	NSString * tempString;
	pSite = [eGetData GetHqLoginSite:YES];
	if (pSite != nil){
#ifdef IMAC_ZSZQ
        tempString = [NSString stringWithFormat:@"%@(%@:%i)",pSite.sname,pSite.ip,pSite.nport];
#else
        tempString = [NSString stringWithFormat:@"%@",pSite.sname];
#endif
		
		[[hqSiteComboBox cell] setTitle:tempString];
	}
    
    if (eGetData.clientinfos.hqParams.bautocheckfast) {
		[autoFindbest setState:NSOnState];
		[hqSiteComboBox setEnabled:NO];
	}
	else {
		[autoFindbest setState:NSOffState];
		[hqSiteComboBox setEnabled:YES];
	}
	
#ifndef IMAC_ONLYHQ
	
	[jySiteComboBox setTag:JYSITE_COM_FLAG];
	[jySiteComboBox setDelegate:self];
	[jySiteComboBox setDataSource:self];
	
    pSite = [eGetData GetJyLoginSite:YES];
	if (pSite != nil) {
#ifdef IMAC_ZSZQ
        tempString = [NSString stringWithFormat:@"%@(%@:%i)",pSite.sname,pSite.ip,pSite.nport];
#else
        tempString = [NSString stringWithFormat:@"%@",pSite.sname];
#endif
        LogIt4(tempString)
		[[jySiteComboBox cell] setTitle:tempString];
	}
    if (eGetData.clientinfos.hqParams.bautocheckfast) {
		[jySiteComboBox setEnabled:NO];
	}
	else {
		[jySiteComboBox setEnabled:YES];
	}
#else
    [jySiteComboBox setEnabled:NO];
    jySiteComboBox.alphaValue=0.0f;
    jylabelText.alphaValue=0.0f;
#endif
	
	
	[refreshCountText setTag:COUNT_Text_FLAG];
	[refreshCountText setDelegate:self];
	customTextFieldFormatter * numFormatt = [[customTextFieldFormatter alloc] init];
	[refreshCountText setFormatter:numFormatt];
	[numFormatt release];
	//刷新
	if (eGetData.clientinfos.hqParams.bautorefreshhq) {
		[autoRefresh setState:NSOnState];
		[refreshCountText setEnabled:YES];
		[[refreshCountText cell] setTitle:[NSString stringWithFormat:@"%i",(int)eGetData.refreshTime]];
	}
	else {
		[autoRefresh setState:NSOffState];
		[refreshCountText setEnabled:NO];
		[[refreshCountText cell] setTitle:@""];
	}
    [lockspanText setTag:LOCKSPAN_TEXT_FLAG];
    [lockspanText setDelegate:self];
    customTextFieldFormatter * numFormatt1 = [[customTextFieldFormatter alloc] init];
    [lockspanText setFormatter:numFormatt1];
    [numFormatt1 release];
    [[lockspanText cell] setTitle:[NSString stringWithFormat:@"%i",(int)eGetData.njylockspan]];
	
	[[agentAddressText cell] setTitle:eGetData.clientinfos.httpProxyInfo.httpProxyAddress];
	[[agentPortText cell]setTitle:eGetData.clientinfos.httpProxyInfo.httpProxyPort];
	[[agentUserText cell]setTitle:eGetData.clientinfos.httpProxyInfo.httpProxyUsername];
	[[agentPasswordText cell]setTitle:eGetData.clientinfos.httpProxyInfo.httpProxyPassword];
	if (eGetData.clientinfos.httpProxyInfo.beUsedFlag) {
		[httpAgentFlag setState:NSOnState];
		[agentAddressText setEnabled:YES];
		[agentPortText setEnabled:YES];
		[agentUserText setEnabled:YES];
		[agentPasswordText setEnabled:YES];
	}
	else {
		[httpAgentFlag setState:NSOffState];
		[agentAddressText setEnabled:NO];
		[agentPortText setEnabled:NO];
		[agentUserText setEnabled:NO];
		[agentPasswordText setEnabled:NO];
	}
}

-(void)changeAutoRefresh:(id)sender{
	if ([autoRefresh state] == NSOnState) {
		[refreshCountText setEnabled:YES];
		[[refreshCountText cell] setTitle:[NSString stringWithFormat:@"%i",(int)eGetData.refreshTime]];
	}
	else {
		[refreshCountText setEnabled:NO];
	}

}

-(IBAction)changeFindBest:(id)sender{
	if ([autoFindbest state] == NSOnState) {
		[hqSiteComboBox setEnabled:NO];
	}
	else {
		[hqSiteComboBox setEnabled:YES];
	}
#ifndef IMAC_ONLYHQ
    if ([autoFindbest state] == NSOnState) {
		[jySiteComboBox setEnabled:NO];
	}
	else {
		[jySiteComboBox setEnabled:YES];
	}
#endif
}

-(IBAction)changeHttpAgentFlag:(id)sender{
	if ([httpAgentFlag state] == NSOnState) {
		[agentAddressText setEnabled:YES];
		[agentPortText setEnabled:YES];
		[agentUserText setEnabled:YES];
		[agentPasswordText setEnabled:YES];
	}
	else {
		[agentAddressText setEnabled:NO];
		[agentPortText setEnabled:NO];
		[agentUserText setEnabled:NO];
		[agentPasswordText setEnabled:NO];
	}
}

-(void)saveRefreshPara{
	eGetData.clientinfos.hqParams.bautorefreshhq = [autoRefresh state];
	eGetData.clientinfos.hqParams.nhqrefreshspan = eGetData.refreshTime;
    eGetData.clientinfos.hqParams.njylockspan = eGetData.njylockspan;
	eGetData.clientinfos.hqParams.bautocheckfast = [autoFindbest state];
	[eGetData.clientinfos.caches SaveHqParamInfo:eGetData.clientinfos.hqParams];
	
	eGetData.clientinfos.localhqsites.bfindbest = eGetData.clientinfos.hqParams.bautocheckfast;
#ifndef IMAC_ONLYHQ
	eGetData.clientinfos.localjysites.bfindbest = eGetData.clientinfos.hqParams.bautocheckfast;
#endif
	
	eGetData.clientinfos.httpProxyInfo.beUsedFlag = [httpAgentFlag state];
	eGetData.clientinfos.httpProxyInfo.httpProxyAddress = [[agentAddressText cell] title];
	eGetData.clientinfos.httpProxyInfo.httpProxyPort=[[agentPortText cell] title];
	eGetData.clientinfos.httpProxyInfo.httpProxyUsername=[[agentUserText cell] title];
	eGetData.clientinfos.httpProxyInfo.httpProxyPassword=[[agentPasswordText cell]title];
	[eGetData.clientinfos.caches SaveHttpProxyInfo:eGetData.clientinfos.httpProxyInfo];
}


#pragma mark  textfield Delegate相关

-(void) controlTextDidChange:(NSNotification *)obj{
	int tempInt;
	NSTextField * tempText = [obj object];
	if ([tempText tag] == COUNT_Text_FLAG) {
		if ([[[tempText cell] title] length] > 0) {
			tempInt = [[[tempText cell] title] intValue];
			if (tempInt >=5) {
			}
			
		}
	}
}

-(void) controlTextDidEndEditing:(NSNotification *)obj{
	NSTextField * tempText = [obj object];
	int tempInt;
	if ([tempText tag] == COUNT_Text_FLAG) {
		if ([[[tempText cell] title] length] > 0) {
			tempInt = [[[tempText cell] title] intValue];
			if (tempInt >=5) {
				eGetData.refreshTime = tempInt;
			}
			else {
				eGetData.refreshTime = 5;
				[[tempText cell] setTitle:@"5"];
			}

			
		}
	}
    if ([tempText tag] == LOCKSPAN_TEXT_FLAG) {
        if ([[[tempText cell] title] length] > 0) {
            tempInt = [[[tempText cell] title] intValue];
            if (tempInt >=1) {
                eGetData.njylockspan = tempInt;
            }
            else {
                eGetData.njylockspan = 1;
                [[tempText cell] setTitle:@"1"];
            }
        }
    }
}
#pragma mark  button相关

-(IBAction)cancelButtonClick:(id)sender{
	[showDelegate closeSysConfig];
}

-(IBAction)doneButtonClick:(id)sender{
    int tempInt;
	if ([refreshCountText tag] == COUNT_Text_FLAG) {
        if ([[[refreshCountText cell] title] length] > 0) {
            tempInt = [[[refreshCountText cell] title] intValue];
            if (tempInt >=5) {
                eGetData.refreshTime = tempInt;
            }
            else {
                eGetData.refreshTime = 5;
                [[refreshCountText cell] setTitle:@"5"];
            }
            
            
        }
    }
    
    if ([[[lockspanText cell] title] length] > 0) {
        tempInt = [[[lockspanText cell] title] intValue];
        if (tempInt >=1) {
            eGetData.njylockspan = tempInt;
        }
        else {
            eGetData.njylockspan =1;
            [[lockspanText cell] setTitle:@"1"];
        }
        
        
    }
    if(eGetData.clientinfos.hqParams.bautocheckfast==NO)
    {
        NSString *phqstr=[[hqSiteComboBox cell] title],*phqstr1=@"";
        LogIt4(phqstr)
        int nindex=0;
        for(TradeSite *psite in eGetData.clientinfos.localhqsites.tradesites)
        {
#ifdef IMAC_ZSZQ
            phqstr1 = [NSString stringWithFormat:@"%@(%@:%i)",psite.sname,psite.ip,psite.nport];
#else
            phqstr1 = [NSString stringWithFormat:@"%@",psite.sname];
#endif
            if([phqstr isEqualToString:phqstr1])
            {
                if (eGetData.clientinfos.localhqsites.nlastindex != nindex)
                {
                    eGetData.clientinfos.localhqsites.nlastindex = nindex;
                    LogIt(51)
                    [eGetData.clientinfos.caches SaveLocalHqSite:eGetData.clientinfos.localhqsites];
                    [eGetData changeHQHost];
                }
                break;
            }
            nindex++;
        }
        
        NSString *pjystr=[[jySiteComboBox cell] title],*pjystr1=@"";
        LogIt4(pjystr)
        nindex=0;
        for(TradeSite *psite in eGetData.clientinfos.localjysites.tradesites)
        {
#ifdef IMAC_ZSZQ
            pjystr1 = [NSString stringWithFormat:@"%@(%@:%i)",psite.sname,psite.ip,psite.nport];
#else
            pjystr1 = [NSString stringWithFormat:@"%@",psite.sname];
#endif
            if([pjystr isEqualToString:pjystr1])
            {
                if (eGetData.clientinfos.localjysites.nlastindex != nindex)
                {
                    eGetData.clientinfos.localjysites.nlastindex = nindex;
                    LogIt(61)
                    [eGetData.clientinfos.caches SaveLocalJySite:eGetData.clientinfos.localjysites];
                    [eGetData changeJYHost];
                }
                break;
            }
            nindex++;
        }
    }
    
    
    [showDelegate closeSysConfig];
	[self saveRefreshPara];
}

#pragma mark combobox Delegate相关
-(NSInteger) numberOfItemsInComboBox:(NSComboBox *)aComboBox{
	//return 1;
    if (aComboBox.tag == HQSITE_COM_FLAG) {
		return [eGetData.clientinfos.localhqsites.tradesites count];
	}
	
	else if(aComboBox.tag == JYSITE_COM_FLAG){
		return [eGetData.clientinfos.localjysites.tradesites count];
		
	}
	
	
	return 0;
}

-(id) comboBox:(NSComboBox *)aComboBox objectValueForItemAtIndex:(NSInteger)index{
	TradeSite *pSite;
	NSString * tempString;
	if (aComboBox.tag == HQSITE_COM_FLAG) {
		pSite =[eGetData.clientinfos.localhqsites.tradesites objectAtIndex:index];
#ifdef IMAC_ZSZQ
        tempString = [NSString stringWithFormat:@"%@(%@:%i)",pSite.sname,pSite.ip,pSite.nport];
#else
        tempString = [NSString stringWithFormat:@"%@",pSite.sname];
#endif
		
		return tempString;
	}
	else if (aComboBox.tag == JYSITE_COM_FLAG){
		pSite =[eGetData.clientinfos.localjysites.tradesites objectAtIndex:index];
#ifdef IMAC_ZSZQ
        tempString = [NSString stringWithFormat:@"%@(%@:%i)",pSite.sname,pSite.ip,pSite.nport];
#else
        tempString = [NSString stringWithFormat:@"%@",pSite.sname];
#endif
		
		return tempString;
	}

	
	return nil;
}

-(void) comboBoxSelectionDidChange:(NSNotification *)notification{
    NSComboBox * tempCombobox = [notification object];
    LogIt(41)
	int tempInt;
	if (tempCombobox == hqSiteComboBox) {
		
		tempInt = [hqSiteComboBox indexOfSelectedItem];
		if (eGetData.clientinfos.localhqsites.nlastindex != tempInt)
        {
			eGetData.clientinfos.localhqsites.nlastindex = tempInt;
			[eGetData.clientinfos.caches SaveLocalHqSite:eGetData.clientinfos.localhqsites];
			[eGetData changeHQHost];
		}
	}
	else if (tempCombobox == jySiteComboBox){
        LogIt(31)
		tempInt = [jySiteComboBox indexOfSelectedItem];
        NSString *strlog=[NSString stringWithFormat:@"32 tempInt=%i",tempInt];
        LogIt4(strlog)
		if (eGetData.clientinfos.localjysites.nlastindex != tempInt)
        {
			eGetData.clientinfos.localjysites.nlastindex = tempInt;
            LogIt(1)
      		[eGetData.clientinfos.caches SaveLocalJySite:eGetData.clientinfos.localjysites];
			[eGetData changeJYHost];
		}
		
	}

}


@end
