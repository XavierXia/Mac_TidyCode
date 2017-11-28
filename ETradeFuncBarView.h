//
//  ETradeFuncBarView.h
//  tdxMac
//
//  Created by tdx on 11-10-25.
//  Copyright 2011 武汉. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "EUBase.h"
#import "Delegate.h"
@interface ETradeFuncBarView : EUBase <NSComboBoxDelegate,NSComboBoxDataSource>{
	id parentView;
	int showType;
	
	int nmaxpage;
	int pageIndex;
	int ntotalline;
    int m_bzdm; //币种代表的字段值
	NSRect viewRect;
	
	NSButton * nextPageButton;
	NSButton * prePageButton;
	NSButton * firstPageButton;
	NSButton * lastPageButton;
	NSButton * refreshButton;
	NSButton * chedanButton;
	
	NSTextField * pageInfoLabel;
	
	NSTextField * rmbInfoLabel;
	NSTextField * gbInfoLabel;
	NSTextField * myInfoLabel;
	
	NSDatePicker * sDate;
	NSDatePicker * eDate;
	NSTextField * sDateLabel;
	NSTextField * eDateLabel;
    NSTextField * zjlsBzLabel;
    NSArray* m_zjlsbz;
    NSArray* m_zjlsbzdm;
	
	id<barViewDelegate> barViewDelegate;
	
	NSComboBox * bankComboBox;
    NSComboBox * bzComboBox;
	Yhxxmx *m_pyhmx;
}
@property(nonatomic, assign) id<barViewDelegate> barViewDelegate;
@property int nmaxpage;
@property int pageIndex;
@property int ntotalline;

- (id)initWithData:(NSRect)frame theData:(EGetData *)_eGetData parentView:(id)_parent;
-(void)clearAllView;
-(void)setShowType:(int)_showType;
-(void) setFrame:(NSRect)frameRect;
-(void)resetbarView;

@end
