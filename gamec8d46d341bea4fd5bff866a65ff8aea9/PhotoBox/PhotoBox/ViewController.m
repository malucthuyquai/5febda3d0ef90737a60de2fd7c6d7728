//
//  ViewController.m
//  PhotoBox
//
//  Created by LyGV on 11/5/14.
//  Copyright (c) 2014 lygv. All rights reserved.
//

#import "ViewController.h"
#import "JASidePanelController.h"
#import "RightController.h"
#import "CenterController.h"
#import <FacebookSDK/FacebookSDK.h>
#import <Parse/Parse.h>

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    UIStoryboard *mainStoryboard = [UIStoryboard storyboardWithName:@"Main" bundle:[NSBundle mainBundle]];
    CenterController *center = [mainStoryboard instantiateViewControllerWithIdentifier:@"CenterController"];
    RightController *right = [mainStoryboard instantiateViewControllerWithIdentifier:@"RightController"];
    [right viewDidLoad];
    JASidePanelController *slide = [[JASidePanelController alloc] init];
    UINavigationController *centernav = [[UINavigationController alloc] initWithRootViewController:center];
    centernav.navigationBar.barTintColor = [UIColor colorWithRed:34.0/255.0 green:192.0/255.0 blue:100.0/255.0 alpha:1.0];
    slide.centerPanel = centernav;
    UINavigationController *rightnav = [[UINavigationController alloc] initWithRootViewController:right];
    rightnav.navigationBar.barTintColor = [UIColor colorWithRed:61.0/255.0 green:64.0/255.0 blue:71.0/255.0 alpha:1.0];
    slide.leftPanel = rightnav;
    slide.leftFixedWidth = 200;
    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) {
        slide.leftFixedWidth = 300;
    }
    slide.shouldDelegateAutorotateToVisiblePanel = NO;
    [self.navigationController pushViewController:slide animated:YES];
}

-(void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
