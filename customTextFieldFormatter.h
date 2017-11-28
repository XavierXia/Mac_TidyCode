//
//  customTextFieldFormatter.h
//  tdxMac
//
//  Created by tdx on 11-10-27.
//  Copyright 2011 武汉. All rights reserved.
//

#import <Cocoa/Cocoa.h>


@interface customTextFieldFormatter : NSFormatter {
	int maxLength;
	BOOL showDot;
	BOOL dotNum;
    BOOL showalpha;
}

@property int maxLength;
@property BOOL showDot;
@property BOOL showalpha;

@end
