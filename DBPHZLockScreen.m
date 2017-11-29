//
//  DBPHZLockScreen.h
//  tdxMac
//
//  Created by xiawenxing on 16-09-06.
//  Copyright 2017 武汉. All rights reserved.
//

#import "DBPHZLockScreen.h"


@implementation DBPHZLockScreen
@synthesize tradeDelegate;
- (id)initWithFrame:(NSRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code here.
    }
    return self;
}

- (id)initWithData:(NSRect)frame theData:(EGetData *)_eGetData{
	self = [super initWithData:frame theData:_eGetData];
	if (self) {
		self.tradeindex = [_eGetData.g_TradeComm.areceiver SetWinobjs:self];
		float tempFloat = frame.size.height * 0.6f;
        
        nameLabel1 = [[NSTextField alloc]init];
        [nameLabel1 setEditable:NO];
        [nameLabel1 setBackgroundColor:[NSColor clearColor]];
        [nameLabel1 setBordered:NO];
        [nameLabel1 setFrame:NSMakeRect(frame.size.width/2-130, tempFloat, 120, 30)];
        [[nameLabel1 cell] setFont:[NSFont systemFontOfSize:16.0f]];
        [[nameLabel1 cell] setTextColor:[NSColor blackColor]];
        [[nameLabel1 cell] setAlignment:NSCenterTextAlignment];
        [[nameLabel1 cell] setTitle:@"普通资金帐号: "];
        [self addSubview:nameLabel1];
        
        ptGDDMText = [[NSTextField alloc]init];
        [ptGDDMText setEditable:YES];
        [ptGDDMText setBackgroundColor:[NSColor clearColor]];
        [ptGDDMText setBordered:YES];
        [ptGDDMText setBezeled:YES];
        [ptGDDMText setBezelStyle:NSTextFieldSquareBezel];
        [ptGDDMText setFrame:NSMakeRect(frame.size.width/2,tempFloat,130,30)];
        [[ptGDDMText cell] setTextColor:[NSColor blackColor]];
        [self addSubview:ptGDDMText];
        
        
		tempFloat = tempFloat - 40;
        
        nameLabel2 = [[NSTextField alloc]init];
        [nameLabel2 setEditable:NO];
        [nameLabel2 setBackgroundColor:[NSColor clearColor]];
        [nameLabel2 setBordered:NO];
        [nameLabel2 setFrame:NSMakeRect(frame.size.width/2-130, tempFloat, 120, 30)];
        [[nameLabel2 cell] setFont:[NSFont systemFontOfSize:16.0f]];
        [[nameLabel2 cell] setTextColor:[NSColor blackColor]];
        [[nameLabel2 cell] setAlignment:NSCenterTextAlignment];
        [[nameLabel2 cell] setTitle:@"普通帐号密码: "];
        [self addSubview:nameLabel2];
        
		passwordText = [[CustomSecureTextField alloc]init];
		[passwordText setEditable:YES];
		[passwordText setBackgroundColor:[NSColor whiteColor]];
		[passwordText setBordered:YES];
		[passwordText setBezeled:YES];
		[passwordText setBezelStyle:NSTextFieldSquareBezel];
		[passwordText setFrame:NSMakeRect(frame.size.width/2, tempFloat, 130, 30)];
		[[passwordText cell] setTextColor:[NSColor blackColor]];
		[self addSubview:passwordText];
		
		tempFloat = tempFloat - 40;
        
		doneButton = [[NSButton alloc] init];
		[doneButton setFrame:NSMakeRect(frame.size.width/2-20, tempFloat, 80, 30)];
		[[doneButton cell] setTitle:@"确定"];
		[doneButton setBezelStyle:3];
		[doneButton setTarget:self];
		[doneButton setAction:@selector(doneButtonClick)];
		[self addSubview:doneButton];
	}
	return self;
}

-(void) setFrame:(NSRect)frame{
	[super setFrame:frame];
    float tempFloat = frame.size.height * 0.6f;
	[nameLabel1 setFrame:NSMakeRect(frame.size.width/2-120, tempFloat, 120, 30)];
	[ptGDDMText setFrame:NSMakeRect(frame.size.width/2,tempFloat,130,30)];
	tempFloat = tempFloat - 40;
    [nameLabel2 setFrame:NSMakeRect(frame.size.width/2-120, tempFloat, 120, 30)];
    [passwordText setFrame:NSMakeRect(frame.size.width/2, tempFloat, 130, 30)];
    tempFloat = tempFloat - 40;
	[doneButton setFrame:NSMakeRect(frame.size.width/2-20, tempFloat, 80, 30)];
}

- (void)onviewWillAppear{
	[[self window] makeFirstResponder:ptGDDMText];
}

- (void)drawRect:(NSRect)dirtyRect {
	[BGCOLOR_GRAY set];
	NSRectFill(dirtyRect);

	
	CGContextRef context = [[NSGraphicsContext currentContext] graphicsPort];
	CGContextSetAllowsAntialiasing(context, FALSE);
	[[NSColor lightGrayColor] set];
	CGContextSetLineWidth(context, 2.0f);
	
	CGContextMoveToPoint(context, 0, 1);
	CGContextAddLineToPoint(context, dirtyRect.size.width, 1);
	
	
	CGContextStrokePath(context);
	CGContextSetAllowsAntialiasing(context, TRUE);
}

#pragma mark focusDelegate
-(void)getFocus:(int)_tag{

}


-(void)getEnter:(int)_tag{
	[[self window] makeFirstResponder:doneButton];
	[self doneButtonClick];
}

-(void)getEsc:(int)_tag{
}
-(void)getKeyUp:(NSEvent *)theEvent{
}
#pragma mark 按钮相关
-(void) doneButtonClick{
    eGetData.saveDate.DBPHZ_dfkhh = [[ptGDDMText cell] title];
    eGetData.saveDate.DBPHZ_dfmm = [[passwordText cell] title];
    
    [eGetData sendTradeQueryData:TDX_GDCX_DBPHZ objIndex:self.tradeindex Session:eGetData.inputSave.sessionID];
    
}

-(BOOL)OnReceiveData:(int)reqIndex parser:(id)pParse
{
    ParseRecv *pParsers=(ParseRecv *)pParse;
    if(!pParsers)
        return YES;
    if(eGetData.gddmDBPHZ.count > 0)
    {
        [eGetData.gddmDBPHZ removeAllObjects];
    }

    switch (reqIndex)
    {
        case TDX_GDCX_DBPHZ:
        {
            if(pParsers.nrownum>0)
            {
                for(int i=0;i<pParsers.nrownum;i++)
                {
                    NSMutableDictionary* dict = [NSMutableDictionary dictionaryWithCapacity:4];
                    [dict setObject:[pParsers getFieldData:i fieldFlag:123] forKey:@"gddm"];
                    [dict setObject:[pParsers getFieldData:i fieldFlag:121] forKey:@"zjzh"];
                    [dict setObject:[pParsers getFieldData:i fieldFlag:125] forKey:@"zhlb"];
                    [dict setObject:[pParsers getFieldData:i fieldFlag:173] forKey:@"xw"];
                    
                    [eGetData.gddmDBPHZ addObject:dict];
                }
                
                eGetData.clientinfos.m_DBPHZblocking=NO;
                [tradeDelegate tradeDBPHZunlockscreen];
                [tradeDelegate tradeDBPHZinputGDDM];
            }
        }
            break;
    }
    return YES;
}

#pragma mark alert相关
-(void)handleResult:(NSAlert *)alert withResult:(NSInteger)result withTag:(int)_tag
{
	switch(result)
	{

		case NSAlertDefaultReturn:
			if (_tag == 0) {
                nerrornum=0;
				[tradeDelegate closeButtonClick];
			}
			else {
				[self performSelector:@selector(dealErrorFocus:) withObject:[NSString stringWithFormat:@"%i",_tag] afterDelay:0.1f];
			}
			break;
			
		case NSAlertAlternateReturn:
			break;
			
		case NSAlertOtherReturn:
			break;
            
        default:
            break;
	}
	
}

-(void)dealErrorFocus:(NSString *)_tag{
	switch ([_tag intValue]) {
		case 1:
			[[self window] makeFirstResponder:passwordText];
			break;
		default:
			break;
	}
}

-(void)SetPassFocus
{
	
}

-(void)unlock
{
}

-(void)quitjy
{

}

-(void)onCancel
{
}


@end
