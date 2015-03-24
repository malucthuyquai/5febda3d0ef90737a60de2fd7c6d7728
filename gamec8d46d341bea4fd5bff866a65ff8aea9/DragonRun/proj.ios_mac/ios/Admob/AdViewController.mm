//
//  AdViewController.m
//  EggSeed
//
//  Created by LyGV on 2013/12/20.
//
//

#import "AdViewController.h"
#include "Global.h"

@interface AdViewController ()

@end

@implementation AdViewController
@synthesize adView, adView2;
@synthesize bannerIsVisible;

-(void)dealloc {
    NSLog(@"%s", __func__);
    adView.delegate = nil;
    [adView release];
    [super dealloc];
}

- (void)viewDidLoad
{
    NSLog(@"%s", __func__);
    [super viewDidLoad];
    adView = [[GADBannerView alloc] initWithAdSize:kGADAdSizeSmartBannerPortrait];
    adView.rootViewController = self;
    adView.adUnitID = @"ca-app-pub-2391571498010954/7579375045";
    adView.delegate = self;
    adView.tag = 1;
    [self.view addSubview:adView];
    GADRequest *request = [GADRequest request];
    request.testDevices = [NSArray arrayWithObjects:GAD_SIMULATOR_ID, nil];
    [adView loadRequest:request];
    adView.center = CGPointMake([UIScreen mainScreen].bounds.size.width/2, adView.center.y);
    
//    adView2 = [[GADBannerView alloc] initWithAdSize:kGADAdSizeSmartBannerPortrait];
//    adView2.rootViewController = self;
//    adView2.adUnitID = @"a152bd5b1607e5c";
//    adView2.delegate = self;
//    adView2.tag = 2;
//    [self.view addSubview:adView2];
//    GADRequest *request2 = [GADRequest request];
//    //request2.testDevices = [NSArray arrayWithObjects:GAD_SIMULATOR_ID, nil];
//    [adView2 loadRequest:request2];
//    adView2.center = CGPointMake([UIScreen mainScreen].bounds.size.width/2, adView2.center.y);
    
    self.bannerIsVisible = NO;
    
    CGRect adFrame = adView.frame;
    adFrame.origin.y = y = -self.view.frame.size.height;
    adView.frame = adFrame;
    //adView.hidden = YES;
}

- (void)reloadAds {
    Global *g = Global::sharedGlobal();
    if (!g->admobIsLoaded) {
        GADRequest *request = [GADRequest request];
        request.testDevices = [NSArray arrayWithObjects:GAD_SIMULATOR_ID, nil];
        [adView loadRequest:request];
    }
}

- (void)adViewDidReceiveAd:(GADBannerView *)view
{
    NSLog(@"%s", __func__);
    Global *g = Global::sharedGlobal();
    g->admobIsLoaded = true;
    g->admobHeight = 80;
    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) {
        if (g->getWidth() <= 1024) {
            g->admobHeight = 70;
        }
    }
    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone && g->getWidth() <= 320) {
        g->admobHeight = 40;
    }
    if (view.tag == 1) {
        adView.center = CGPointMake([UIScreen mainScreen].bounds.size.width/2, view.frame.size.height/2);
    } else {
        //adView2.center = CGPointMake([UIScreen mainScreen].bounds.size.width/2, [UIScreen mainScreen].bounds.size.height - view.frame.size.height/2);
    }
}

- (void)adView:(GADBannerView *)view didFailToReceiveAdWithError:(GADRequestError *)error
{
    NSLog(@"%s - %@", __func__, error.description);
    Global *g = Global::sharedGlobal();
    g->admobIsLoaded = false;
}

-(void)showAtCenter {
    CGRect adFrame = adView.frame;
    adFrame.origin.y = y = self.view.frame.size.height/2 - adView.frame.size.height/2;
    adView.frame = adFrame;
}

-(void)showAtBottom {
    CGRect adFrame = adView.frame;
    adFrame.origin.y = y = self.view.frame.size.height - adView.frame.size.height;
    adView.frame = adFrame;
}








@end
