//
//  CreateMenuController.m
//  PhotoBox
//
//  Created by LyGV on 11/6/14.
//  Copyright (c) 2014 lygv. All rights reserved.
//

#import "CreateMenuController.h"
#import <Parse/Parse.h>

@interface CreateMenuController ()

@end

@implementation CreateMenuController

- (void)viewDidLoad {
    [super viewDidLoad];
    CGRect r = self.view.frame;
    r.size.width = 200;
    self.view.frame = r;
    self.view.backgroundColor = [UIColor colorWithRed:61.0/255.0 green:64.0/255.0 blue:71.0/255.0 alpha:1.0];
}

- (IBAction)createMenu:(id)sender
{
    PFObject *album = [PFObject objectWithClassName:@"Albums"];
    album[@"album_name"] = menuname.text;
    [album saveInBackgroundWithBlock:^(BOOL succeeded, NSError *error) {
        if (succeeded) {
            [self.navigationController popViewControllerAnimated:YES];
        }
    }];
}

@end
