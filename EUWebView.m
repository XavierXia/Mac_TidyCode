//
//  EUWebView.m
//  tdxMac
//
//  Created by tdx on 11-11-8.
//  Copyright 2011 武汉. All rights reserved.
//

#import "EUWebView.h"
#define TOOL_HEIGHT 20
#define TOOL_WIDTH 40
#define SEPARATE_WIDTH 4
@implementation EUWebView

@synthesize webView1;

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
		viewRect = frame;
		self.webView1 = [[WebView alloc] initWithFrame:NSMakeRect(0, 0, frame.size.width, frame.size.height-TOOL_HEIGHT)];
		[self addSubview:self.webView1];
	//	[webView1 setPolicyDelegate:self];
		[self.webView1 setFrameLoadDelegate:self];
		
		
		toolView = [[NSView alloc] initWithFrame:NSMakeRect(0, frame.size.height-TOOL_HEIGHT, frame.size.width, TOOL_HEIGHT)];
		[self addSubview:toolView];
		
		
		backButton = [[NSButton alloc] init];
		[backButton setBezelStyle:12];
		[[backButton cell] setTitle:@"后退"];
		[[backButton cell] setBackgroundColor:[NSColor clearColor]];
		[backButton setTag:0];
		[backButton setTarget:self];
		[backButton setAction:@selector(buttonClick:)];
		[backButton setFrame:NSMakeRect(0,0,TOOL_WIDTH,TOOL_HEIGHT)];
		[toolView addSubview:backButton];
		
		forwardButton = [[NSButton alloc] init];
		[forwardButton setBezelStyle:12];
		[[forwardButton cell] setTitle:@"前进"];
		[[forwardButton cell] setBackgroundColor:[NSColor clearColor]];
		[forwardButton setTag:1];
		[forwardButton setTarget:self];
		[forwardButton setAction:@selector(buttonClick:)];
		[forwardButton setFrame:NSMakeRect(TOOL_WIDTH+SEPARATE_WIDTH,0,TOOL_WIDTH,TOOL_HEIGHT)];
		[toolView addSubview:forwardButton];
		
		refreshButton = [[NSButton alloc] init];
		[refreshButton setBezelStyle:12];
		[[refreshButton cell] setTitle:@"刷新"];
		[[refreshButton cell] setBackgroundColor:[NSColor clearColor]];
		[refreshButton setTag:2];
		[refreshButton setTarget:self];
		[refreshButton setAction:@selector(buttonClick:)];
		[refreshButton setFrame:NSMakeRect((TOOL_WIDTH+SEPARATE_WIDTH)*2,0,TOOL_WIDTH,TOOL_HEIGHT)];
		[toolView addSubview:refreshButton];
		
		cancelButton = [[NSButton alloc] init];
		[cancelButton setBezelStyle:12];
		[[cancelButton cell] setTitle:@"关闭"];
		[[cancelButton cell] setBackgroundColor:[NSColor clearColor]];
		[cancelButton setTag:3];
		[cancelButton setTarget:self];
		[cancelButton setAction:@selector(buttonClick:)];
		[cancelButton setFrame:NSMakeRect((TOOL_WIDTH+SEPARATE_WIDTH)*3,0,TOOL_WIDTH,TOOL_HEIGHT)];
		[toolView addSubview:cancelButton];
		
		
		tipField = [[NSTextField alloc]init];
		[tipField setEditable:NO];
		[tipField setBackgroundColor:[NSColor clearColor]];
		[tipField setBordered:NO];
		[tipField setFrame:NSMakeRect((TOOL_WIDTH +SEPARATE_WIDTH)*4,0,200,TOOL_HEIGHT)];
		[[tipField cell] setTextColor:[NSColor blackColor]];
		[toolView addSubview:tipField];

	}
	return self;
}


#pragma mark  WebResourceDelegate
-(void) webView:(WebView *)sender didStartProvisionalLoadForFrame:(WebFrame *)frame{
	[[tipField cell] setTitle:@"正在加载页面数据......"];
}

-(void) webView:(WebView *)sender didFinishLoadForFrame:(WebFrame *)frame{
	[[tipField cell] setTitle:@"页面加载完成"];
	[self performSelector:@selector(clearTips) withObject:nil afterDelay:0.5f];
}

//-(void) webView:(WebView *)webView decidePolicyForNewWindowAction:(NSDictionary *)actionInformation request:(NSURLRequest *)request newFrameName:(NSString *)frameName decisionListener:(id <WebPolicyDecisionListener>)listener{
//	[listener ignore];
//	[[webView mainFrame] loadRequest:[NSURLRequest requestWithURL:[request URL]]];
//	
//}


-(void)clearTips{
	[[tipField cell] setTitle:@""];
}

-(void)buttonClick:(id)sender{
	switch ([sender tag]) {
		case 0:
			[self.webView1 goBack];
			break;
		case 1:
			[self.webView1 goForward];
			break;
		case 2:
			[self.webView1 reload:self.webView1];
            [self performSelector:@selector(clearTips) withObject:nil afterDelay:0.5f];
			break;
		case 3:
			[self.operProcessDelegate getHQProcess:@"" gpSetcode:-1 typeID:MAC_CANCEL_WEB_FUNC pareOne:-1 paraTwo:-1];
			break;

		default:
			break;
	}
}

-(void) setFrame:(NSRect)frameRect{
	[super setFrame:frameRect];
	viewRect = frameRect;
	[self.webView1 setFrame:NSMakeRect(0, 0, viewRect.size.width, viewRect.size.height-TOOL_HEIGHT)];
	[toolView setFrame:NSMakeRect(0, viewRect.size.height-TOOL_HEIGHT, viewRect.size.width, TOOL_HEIGHT)];
}

- (void)drawRect:(NSRect)dirtyRect {
    [[NSColor whiteColor] set];
	NSRectFill(viewRect);

}

-(void)showWeb:(NSString *)_url{
	
    NSURL *url1 = [NSURL URLWithString:_url];
    NSURLRequest *urlRequest = [NSURLRequest requestWithURL:url1];
	[[self.webView1 mainFrame] loadRequest:urlRequest];

}

@end
