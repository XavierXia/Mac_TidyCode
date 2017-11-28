//
//  EUWebView.h
//  tdxMac
//
//  Created by tdx on 11-11-8.
//  Copyright 2011 武汉. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <WebKit/WebKit.h>
#import <WebKit/WebResourceLoadDelegate.h>
#import "EUBase.h"

@interface EUWebView : EUBase {
	NSButton * backButton;
	NSButton * forwardButton;
	NSButton * refreshButton;
	NSButton * cancelButton;
	
	NSTextField * tipField;
	
	WebView * webView1;
	NSView * toolView;
	NSRect viewRect;
}
@property (nonatomic,retain) WebView * webView1;

-(void) setFrame:(NSRect)frameRect;
-(void)showWeb:(NSString *)_url;
@end
