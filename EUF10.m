//
//  EUF10.m
//  tdxMac
//
//  Created by tdx on 11-10-22.
//  Copyright 2011 武汉. All rights reserved.
//

#import "EUF10.h"
#define TITLE_HEIGHT 70
#define PER_TITLE_HEIGHT 30
#define PER_TITLE_WIDTH 70
#define SPACE_VALUE 1

@implementation EUF10


- (id)initWithFrame:(NSRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        
    }
    return self;
}


- (id)initWithData:(NSRect)frame theData:(EGetData *)_eGetData{
	self = [super initWithData:frame theData:_eGetData];
	if (self) {
		// Initialization code here.
        titleArray = [[NSMutableArray alloc] initWithCapacity:16];
		viewRect = frame;
		
        
		NSTextField * tempField;
		for (int i = 0; i < 16; i++) {
			tempField = [[NSTextField alloc]init];
			[tempField setEditable:NO];
			[tempField setBackgroundColor:[NSColor blackColor]];
			[tempField setBordered:NO];
			[tempField setTag:i];
			[tempField setFrame:NSZeroRect];
			[[tempField cell] setFont:[NSFont systemFontOfSize:15.0f]];
			[self addSubview:tempField];
			
			[titleArray addObject:tempField];
			[tempField release];
		}
		
		NSRect textRect;
		textRect.origin.x  = 0;
		textRect.origin.y = 0;
		textRect.size.width = viewRect.size.width;
		textRect.size.height = viewRect.size.height - TITLE_HEIGHT;
        
        
		textView = [[CustonTextView alloc] initWithFrame:textRect];
        
        
		[textView setEditable:NO];
		[textView setBackgroundColor:[NSColor blackColor]];
        
        
		[textView setFont:[NSFont systemFontOfSize:15.0f]];
        
        
		[textView setTextColor:HQCOLOR_F10TEXT];

		textView.focusDelegate = self;
		
		scrollView=[[NSScrollView alloc] initWithFrame:textRect];
		[scrollView setHasHorizontalScroller:NO];
		[scrollView setHorizontalScroller:nil];
		[scrollView setHasVerticalScroller:YES];
		[scrollView setDrawsBackground:NO];
		
		[scrollView setDocumentView:textView];
		[scrollView setBackgroundColor:[NSColor clearColor]];
		[self addSubview:scrollView];
		
	}
	
	return self;
}	

-(void) setFrame:(NSRect)frameRect{
	[super setFrame:frameRect];
	viewRect = frameRect;
	
	self.offset_X = frameRect.origin.x;
	self.offset_Y = frameRect.origin.y;
	
	NSRect textRect;
	textRect.origin.x  = 0;
	textRect.origin.y = 0;
	textRect.size.width = viewRect.size.width;
	textRect.size.height = viewRect.size.height - TITLE_HEIGHT;
	
	[scrollView setFrame:textRect];
	[textView setFrame:textRect];
	
	[self layoutTitle];
	
}


- (void)drawRect:(NSRect)dirtyRect {
    // Drawing code here.
	[super drawRect:viewRect];
	
	CGContextRef context = [[NSGraphicsContext currentContext] graphicsPort];
	CGContextSetAllowsAntialiasing(context, FALSE);
	CGContextSetLineWidth(context, 1.0f);
	[HQCOLOR_F10TITLE set];
	for (int i = 0 ; i<[titleArray count]; i++) {
		NSTextField * tempField = [titleArray objectAtIndex:i];
		NSRect tempRect = tempField.frame;
		if ((tempRect.size.width > 0)&&(tempRect.size.height > 0)) {
			CGContextAddRect(context, CGRectMake(tempRect.origin.x-1, tempRect.origin.y-1, tempRect.size.width+2,tempRect.size.height+2));
			CGContextStrokePath(context);
		}
	}
	CGContextSetAllowsAntialiasing(context, TRUE);
}

-(void)layoutTitle{
	int i;
	int _length = [titleArray count];
	NSTextField * tempField;
	F10Title_Unit * tempUnit ;
	for (i = 0 ; i<_length; i++) {
		tempField = [titleArray objectAtIndex:i];
		[tempField setFrame:NSZeroRect];
	}
	
	for (i = 0; i<MIN([titleValue count],_length); i++) {
		tempField = [titleArray objectAtIndex:i];
		tempUnit  = [titleValue objectAtIndex:i];
		if (i>=0 && i<4) {
			[tempField setFrame:NSMakeRect(viewRect.size.width/2 - (4-i)*PER_TITLE_WIDTH+SPACE_VALUE, viewRect.size.height - PER_TITLE_HEIGHT-SPACE_VALUE, PER_TITLE_WIDTH-2*SPACE_VALUE, PER_TITLE_HEIGHT-2*SPACE_VALUE)];
		}
		if (i>=4 && i<8) {
			[tempField setFrame:NSMakeRect(viewRect.size.width/2 + (i-4)*PER_TITLE_WIDTH+SPACE_VALUE, viewRect.size.height - PER_TITLE_HEIGHT-SPACE_VALUE, PER_TITLE_WIDTH-2*SPACE_VALUE, PER_TITLE_HEIGHT-2*SPACE_VALUE)];
		}
		
		if (i>=8 && i<12) {
			[tempField setFrame:NSMakeRect(viewRect.size.width/2 - (12-i)*PER_TITLE_WIDTH+SPACE_VALUE, viewRect.size.height -2* PER_TITLE_HEIGHT-SPACE_VALUE, PER_TITLE_WIDTH-2*SPACE_VALUE, PER_TITLE_HEIGHT-2*SPACE_VALUE)];
		}
		
		if (i>=12 && i<16) {
			[tempField setFrame:NSMakeRect(viewRect.size.width/2 + (i-12)*PER_TITLE_WIDTH+SPACE_VALUE, viewRect.size.height - 2*PER_TITLE_HEIGHT-SPACE_VALUE, PER_TITLE_WIDTH-2*SPACE_VALUE, PER_TITLE_HEIGHT-2*SPACE_VALUE)];
		}
		
		if (selectIndex == i) {
			[[tempField cell] setTextColor:HQCOLOR_F10TITLE_SEL];
		}
		else {
			[[tempField cell] setTextColor:HQCOLOR_F10TITLE];
		}
		[[tempField cell] setTitle:tempUnit.sTitle];
	}
	
	[self setNeedsDisplay:YES];
}

#pragma mark 鼠标响应相关
-(void) mouseDown:(NSEvent *)theEvent{
	int tempInt,index;
	NSPoint  p = [theEvent locationInWindow];
	float tempX = p.x - self.offset_X;
	float tempY = p.y - self.offset_Y;
	if ((tempX > viewRect.size.width/2 - 4*PER_TITLE_WIDTH+SPACE_VALUE)&&(tempX < viewRect.size.width/2 + 4*PER_TITLE_WIDTH+SPACE_VALUE)&&(tempY > viewRect.size.height - TITLE_HEIGHT)&&(tempY < viewRect.size.height)) {
		NSLog(@"click");
		if ((tempY > viewRect.size.height - TITLE_HEIGHT/2)&&(tempY < viewRect.size.height)) { //第一排
			if((tempX - viewRect.size.width/2)<0){
				tempInt = (viewRect.size.width/2 - tempX) / PER_TITLE_WIDTH;
				index = 4- (tempInt+1) ;
			}
			else {
				tempInt = ( tempX-viewRect.size.width/2 ) / PER_TITLE_WIDTH;
				index = tempInt +4;

			}

		}
		else {//第二排
			if((tempX - viewRect.size.width/2)<0){
				tempInt = (viewRect.size.width/2 - tempX) / PER_TITLE_WIDTH;
				index = 4- (tempInt+1) +8;
			}
			else {
				tempInt = ( tempX-viewRect.size.width/2 ) / PER_TITLE_WIDTH;
				index = tempInt +4+8;
				
			}
		}
		
		if (index < [titleValue count] ) {
			[self dealSelectedTitleChange:index];
		}
	}
}

-(void)dealSelectedTitleChange:(int)_index{
	if (selectIndex == _index) {
		return;
	}
	int i;
	int _length = [titleArray count];
	NSTextField * tempField;
	F10Title_Unit * tempUnit ;
	selectIndex = _index;
	for (i = 0 ; i<_length && i<[titleArray count]; i++) {
		tempField = [titleArray objectAtIndex:i];
		if (selectIndex == i) {
			[[tempField cell] setTextColor:HQCOLOR_F10TITLE_SEL];
		}
		else {
			[[tempField cell] setTextColor:HQCOLOR_F10TITLE];
		}
	}
	if(selectIndex>=0 && selectIndex<[titleValue count])
    {
        tempUnit  = [titleValue objectAtIndex:selectIndex];
        NSMutableData * theData = [eGetData getF10TxtReqEx:self.gpcode setcode:self.setcode which:0 path:tempUnit.sFilePath nOffset:tempUnit.nOffset nLength:tempUnit.nLength];
        [eGetData.g_pEComm AsyncSendData:theData length:[theData length] withobjIndex:self.windindex withreqIndex:1];
    }
}

-(void)getF10Data:(NSString *)_gpcode setcode:(int)_setcode  reloadFlag:(BOOL)_reloadFlag{
	if (self.gpcode != nil) {
		[gpcode release],gpcode = nil;
	}
	self.gpcode = [NSString stringWithFormat:@"%@",_gpcode];
	self.setcode = _setcode;
	selectIndex = 0;
	[operProcessDelegate getTheTitleName:[eGetData searchStockName:self.gpcode gpSetcode:self.setcode]];
	
	NSMutableData * theData = [eGetData getF10CFGReq_ALL:gpcode setcode:setcode];	
	[eGetData.g_pEComm AsyncSendData:theData length:[theData length] withobjIndex:self.windindex withreqIndex:1];

}

-(void)OnReceiveData:(int)reqIndex FuncID:(int)_funcID HqResult:(HqResultData *)_hqResult{
	if (_hqResult.resultStat < 1) {
		return;
	}
	switch (reqIndex) {
		case F10CFG_ALL:{
			if (titleValue != nil) {
				[titleValue removeAllObjects];
				[titleValue release],titleValue = nil;
			}
			titleValue = [[NSMutableArray alloc] init];
			
			[eGetData getF10CFGAsn_ALL:_hqResult DataArray:titleValue];
			
			if ([titleValue count] > 0) {
				[self layoutTitle];
				selectIndex = 0;
				
				F10Title_Unit * tempUnit  = [titleValue objectAtIndex:selectIndex];
				NSMutableData * theData = [eGetData getF10TxtReqEx:self.gpcode setcode:self.setcode which:0 path:tempUnit.sFilePath nOffset:tempUnit.nOffset nLength:tempUnit.nLength];	
				[eGetData.g_pEComm AsyncSendData:theData length:[theData length] withobjIndex:self.windindex withreqIndex:1];
			}
				
		}	
			break;
		case F10TXT_ALL:
			if (textValue != nil) {
				[textValue release],textValue = nil;
			}
			
			textValue = [eGetData getF10TxtAsnEx:_hqResult DataString:nil];
			
			if ([textValue length] > 0) {
				[textView setString:textValue];
			}
			else {
				[textView setString:@"暂无数据"];
			}

			
			break;
	
		default:
			break;
	}
}



#pragma mark 键盘响应
-(void) dealKeyBoardEvent:(NSEvent *)theEvent{
	switch ([theEvent keyCode]) {
		case MAC_KEY_ARROWDOWN:{
	
		}
			break;
		case MAC_KEY_ARROWUP:{

		}
			break;	
		case MAC_KEY_F5:
		{
			[operProcessDelegate getHQProcess:gpcode gpSetcode:setcode typeID:MAC_ZST_FUNC pareOne:-1 paraTwo:-1];
		}
			break;
		case MAC_KEY_CHAR_Z:{
			break;
		}	
		case MAC_KEY_SPACE:{
			int tempInt ;
			tempInt = selectIndex;
			tempInt = tempInt + 1;
			if (tempInt > [titleValue count]- 1) {
				tempInt = 0;
			}
			[self dealSelectedTitleChange:tempInt];
			break;
		}	
		case MAC_KEY_DEL:{
			int tempInt ;
			tempInt = selectIndex;
			tempInt = tempInt - 1;
			if (tempInt < 0) {
				tempInt = [titleValue count]- 1;
			}
			[self dealSelectedTitleChange:tempInt];
		}	
			break;
		case MAC_KEY_ESC:
			[operProcessDelegate getHQProcess:gpcode gpSetcode:setcode typeID:eGetData.bakFunc pareOne:-1 paraTwo:-1];
			break;
	
		default:
			break;
	}
}

-(void)getFocus:(int)_tag{
}
-(void)getEnter:(int)_tag{
}
-(void)getEsc:(int)_tag{
}
-(void)getKeyUp:(NSEvent *)theEvent{
	[self dealKeyBoardEvent:theEvent];
}


-(void) dealloc{
	[super dealloc];
	[titleArray release];
	[textView release];
	[titleValue release];
}

@end
