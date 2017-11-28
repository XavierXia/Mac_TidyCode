//
//  customTextFieldFormatter.m
//  tdxMac
//
//  Created by tdx on 11-10-27.
//  Copyright 2011 武汉. All rights reserved.
//

#import "customTextFieldFormatter.h"


@implementation customTextFieldFormatter
@synthesize maxLength,showDot,showalpha;

-(id) init{
	self=[super init];
    if(self)
    {
        showDot = NO;
        dotNum = NO;
        showalpha=NO;
        maxLength  = 100;
    }
	return self;
}

-(NSString *) stringForObjectValue:(id)obj{
	return (NSString *)obj;
}

-(BOOL) getObjectValue:(id *)obj forString:(NSString *)string errorDescription:(NSString **)error{
	*obj = string;
	return YES;
}

-(BOOL) isPartialStringValid:(NSString *)partialString newEditingString:(NSString **)newString errorDescription:(NSString **)error{
	dotNum = NO;
	int _length = [partialString length];
	
	int index = 0;
	for (index = 0; index<_length; index++) {
		if (_length > maxLength) {
			return NO;
		}
		
		unichar endCharacter = [partialString characterAtIndex:index];
		
		if (endCharacter >= '0' && endCharacter <= '9') {
			continue;
		}
		else {
			if (showDot) {
				if (endCharacter == '.' && !dotNum) {
					dotNum = YES;
					continue;
				}
			}
            if(showalpha)
            {
                if (endCharacter >= 'a' && endCharacter <= 'z')
                    continue;
                if (endCharacter >= 'A' && endCharacter <= 'Z')
                    continue;
            }
			return NO;
		}
	}
	return YES;
}

@end
