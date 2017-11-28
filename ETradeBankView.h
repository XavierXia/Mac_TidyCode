//
//  ETradeBankView.h
//  tdxMac
//
//  Created by tdx on 11-11-8.
//  Copyright 2011 武汉. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "EUBase.h"
#import "CustomSecureTextField.h"
#import "CustonTextField.h"
#import "customTextFieldFormatter.h"
@interface ETradeBankView : EUBase <NSComboBoxDelegate,NSComboBoxDataSource,NSTextFieldDelegate,getFocusDelegate,NSAlertDelegate>{
	int  tag;
	int textIndex;
	int pickIndex;
	NSString * selectedName;
	Yhxxmx  *m_pyhmx;
	
	NSArray * moneyTypeArray;
	NSArray *zzfxArray;
	BOOL  m_bfirstflag;
	BOOL       m_bfirstviewflag;
	BOOL       m_bediting;
	int    nSelectyhIndex;
	
	BOOL m_bButtonshowflag;
	
	BOOL  m_bbusy;
	BOOL  m_bfirstyhyeflag;
	BOOL m_bhasbankpass,m_bhassecpass;
	BOOL baddflag;//是否已被加载addsubview
	BOOL m_bselzzfx;
	
	BOOL  m_btitleflag;
	BOOL  m_bselbz;
	BOOL m_bfirstalertflag;
	int ntotalrow;
	BOOL m_bleftarrowflag;
    int nZJZZ;
	
	NSRect viewRect;
	
	
	NSTextField * zzfsLabel;
	NSTextField * xzyhLabel;
	NSTextField * zjmmLabel;
	NSTextField * yhmmLabel;
	NSTextField * zzjeLabel;
	NSTextField * xzbzLabel;
	NSTextField * yhyeLabel;
    NSTextField * zczhLabel;
    NSTextField * zrzhLabel;
	
	NSComboBox * zzfsComboBox;
	NSComboBox * xzyhComboBox;
	NSComboBox * xzbzComboBox;
    NSComboBox * zczhComboBox;
    NSComboBox * zrzhComboBox;
	CustomSecureTextField * zjmmText;
	CustomSecureTextField * yhmmText;
	CustonTextField * zzjeText;
	NSTextField * yhyeText;
	
	NSButton * doneButton;
    NSButton * doneButton1;
    NSButton * doneButton2;
    NSString *stryhlsh;
    int nyhyecount;
}

@property(nonatomic) BOOL m_bleftarrowflag;
@property(nonatomic) BOOL m_bselbz;
@property(nonatomic) BOOL m_bselzzfx;
@property(nonatomic) BOOL baddflag;
@property (nonatomic) int tag;
@property BOOL m_bButtonshowflag;


- (void)onviewWillAppear;
-(void)dealOutLook;
-(void) setFrame:(NSRect)frameRect;
-(void)cleanscreen;
-(void)doYzzz;
-(void)doYzzz1;
-(void)doYzzz2;
-(void)doYzzz3;
-(void)doYzzz4;
-(void)startanimate;
-(void)stopanimate;
-(BOOL)IsCanQueryOther;
-(int)GetBzIndex:(NSString *)bzstr;
-(int)GetZzfxIndex:(NSString *)zzfxstr;
-(void)handleResult:(NSAlert *)alert withResult:(NSInteger)result withTag:(int)_tag;
-(void)QueryYhye;
-(void)cleardsdata;
@end
