//
//  NibCell.m
//  Wallaper
//
//  Created by LyGV on 7/24/14.
//  Copyright (c) 2014 lygv. All rights reserved.
//

#import "NibCell.h"

@implementation NibCell
@synthesize image, delegate, imageName;

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
    }
    return self;
}

-(IBAction)select:(id)sender{
    if ([delegate respondsToSelector:@selector(selectCell:)]) {
        [delegate selectCell:self];
    }
}

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
}
*/

@end
