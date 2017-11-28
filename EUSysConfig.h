//
//  EUSysConfig.h
//  tdxMac
//
//  Created by tdx on 11-12-17.
//  Copyright 2011 武汉. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "EGetData.h"
#import "Delegate.h"
#import "customTextFieldFormatter.h"

@interface EUSysConfig : NSViewController <NSComboBoxDelegate,NSComboBoxDataSource,NSTextFieldDelegate>{
	EGetData * eGetData;
	id <showBodyDelegate> showDelegate;
	
	IBOutlet NSComboBox * hqSiteComboBox;
	IBOutlet NSComboBox * jySiteComboBox;
	IBOutlet NSButton * autoRefresh;
	IBOutlet NSButton * autoFindbest;
	IBOutlet NSTextField * refreshCountText;
	IBOutlet NSTextField * jylabelText;
	IBOutlet NSButton * httpAgentFlag;
	IBOutlet NSTextField * agentAddressText;
	IBOutlet NSTextField * agentPortText;
	IBOutlet NSTextField * agentUserText;
	IBOutlet NSTextField * agentPasswordText;
    IBOutlet NSTextField * lockspanText;
}
@property (nonatomic,assign) id <showBodyDelegate> showDelegate;
@property (nonatomic,retain) EGetData * eGetData;
@property (nonatomic,retain) IBOutlet NSComboBox * hqSiteComboBox;
@property (nonatomic,retain) IBOutlet NSComboBox * jySiteComboBox;
@property (nonatomic,retain) IBOutlet NSButton * autoRefresh;
@property (nonatomic,retain) IBOutlet NSTextField * refreshCountText;
@property (nonatomic,retain) IBOutlet NSButton * autoFindbest;
@property (nonatomic,retain) IBOutlet NSTextField * lockspanText;;
@property (nonatomic,retain) IBOutlet NSButton * httpAgentFlag;
@property (nonatomic,retain) IBOutlet NSTextField * agentAddressText;
@property (nonatomic,retain) IBOutlet NSTextField * jylabelText;
@property (nonatomic,retain) IBOutlet NSTextField * agentPortText;
@property (nonatomic,retain) IBOutlet NSTextField * agentUserText;
@property (nonatomic,retain) IBOutlet NSTextField * agentPasswordText;

-(id) initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil eGetData:(EGetData *)_eGetData;
-(IBAction)cancelButtonClick:(id)sender;
-(IBAction)doneButtonClick:(id)sender;
-(IBAction)changeAutoRefresh:(id)sender;
-(IBAction)changeFindBest:(id)sender;
-(IBAction)changeHttpAgentFlag:(id)sender;
-(void)showInfo;
-(void)saveRefreshPara;
@end
