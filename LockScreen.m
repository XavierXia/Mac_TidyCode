//
//  LockScreen.m
//  tdxMac
//
//  Created by tdx on 11-11-8.
//  Copyright 2011 武汉. All rights reserved.
//

#import "LockScreen.h"


@implementation LockScreen
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

		tipsLabel = [[NSTextField alloc]init];
		[tipsLabel setEditable:NO];
		[tipsLabel setBackgroundColor:[NSColor clearColor]];
		[tipsLabel setBordered:NO];
		[tipsLabel setFrame:NSMakeRect(0, frame.size.height * 0.6f, frame.size.width, 30)];
		[[tipsLabel cell] setFont:[NSFont systemFontOfSize:16.0f]];
		[[tipsLabel cell] setTextColor:[NSColor blackColor]];
		[[tipsLabel cell] setAlignment:NSCenterTextAlignment];
		[[tipsLabel cell] setTitle:@"交易界面已锁定，请输入交易密码解锁。"];
		[self addSubview:tipsLabel];
		
		float tempFloat = tipsLabel.frame.origin.y - 30;
		
		passwordText = [[CustomSecureTextField alloc]init];
		[passwordText setEditable:YES];
		[passwordText setBackgroundColor:[NSColor whiteColor]];
		[passwordText setBordered:YES];
		[passwordText setBezeled:YES];
		passwordText.focusDelegate = self;
		[passwordText setBezelStyle:NSTextFieldSquareBezel];
		[passwordText setFrame:NSMakeRect(frame.size.width/2-100, tempFloat, 200, 30)];
		[[passwordText cell] setTextColor:[NSColor blackColor]];
		[self addSubview:passwordText];
		
		tempFloat = tempFloat - 40;
		
		doneButton = [[NSButton alloc] init];
		[doneButton setFrame:NSMakeRect(frame.size.width/2-100, tempFloat, 60, 30)];
		[[doneButton cell] setTitle:@"确定"];
		[doneButton setBezelStyle:3];
		[doneButton setTarget:self];
		[doneButton setAction:@selector(doneButtonClick)];
		[self addSubview:doneButton];
		
		cancelButton = [[NSButton alloc] init];
		[cancelButton setFrame:NSMakeRect(frame.size.width/2-30, tempFloat, 60, 30)];
		[[cancelButton cell] setTitle:@"取消"];
		[cancelButton setBezelStyle:3];
		[cancelButton setTarget:self];
		[cancelButton setAction:@selector(cancelButtonClick)];
		[self addSubview:cancelButton];
		
		closeButton = [[NSButton alloc] init];
		[closeButton setFrame:NSMakeRect(frame.size.width/2+40, tempFloat, 60, 30)];
		[[closeButton cell] setTitle:@"退出"];
		[closeButton setBezelStyle:3];
		[closeButton setTarget:self];
		[closeButton setAction:@selector(closeButtonClick)];
		[self addSubview:closeButton];
		
	}
	return self;
}

-(void) setFrame:(NSRect)frame{
	[super setFrame:frame];
	[tipsLabel setFrame:NSMakeRect(0, frame.size.height * 0.6f, frame.size.width, 30)];
	float tempFloat = tipsLabel.frame.origin.y - 30;
	[passwordText setFrame:NSMakeRect(frame.size.width/2-100, tempFloat, 200, 30)];
	tempFloat = tempFloat - 40;
	[doneButton setFrame:NSMakeRect(frame.size.width/2-100, tempFloat, 60, 30)];
	[cancelButton setFrame:NSMakeRect(frame.size.width/2-30, tempFloat, 60, 30)];
	[closeButton setFrame:NSMakeRect(frame.size.width/2+40, tempFloat, 60, 30)];
}

- (void)onviewWillAppear{
	[[self window] makeFirstResponder:passwordText];
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
    [eGetData jyhasoper];
	if([[[passwordText cell]title] isEqualToString:[eGetData GetJymmString]]==NO)
	{
        nerrornum++;
        if(nerrornum>=5)
        {
            nerrornum=0;
            NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
                                             defaultButton: @"确定"
                                           alternateButton:nil
                                               otherButton: nil
                                 informativeTextWithFormat:@"您输入密码的错误次数超过5次,请重新登录!"];
            [alert setDelegate:self];
            NSInteger result = [alert runModal];
            [self handleResult:alert withResult:result withTag:0];
            return;
        }
		NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
										 defaultButton: @"确定"
									   alternateButton: nil
										   otherButton: nil
							 informativeTextWithFormat: [NSString stringWithFormat: @"密码输入错误,请重新输入(您还有%i次尝试机会)!",5-nerrornum]];
		[alert setDelegate:self];
		NSInteger result = [alert runModal];
		[self handleResult:alert withResult:result withTag:1];			
		[[passwordText cell] setTitle:@""];
		return;
	}
    nerrornum=0;
	[[passwordText cell] setTitle:@""];
	eGetData.clientinfos.m_blocking=NO;
	[tradeDelegate unlockButtonClick];
}
-(void) cancelButtonClick{
	[tradeDelegate minButtonClick];
}

-(void) closeButtonClick{
	NSAlert* alert = [NSAlert alertWithMessageText:@"提示"
									 defaultButton: @"确定"
								   alternateButton:@"取消"
									   otherButton: nil
						 informativeTextWithFormat: @"你确定要退出交易系统吗？"];
	[alert setDelegate:self];
	NSInteger result = [alert runModal];
	[self handleResult:alert withResult:result withTag:0];	
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
