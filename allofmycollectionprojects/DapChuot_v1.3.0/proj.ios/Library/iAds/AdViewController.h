//
//  AdViewController.h
//  EggSeed
//
//  Created by LyGV on 2013/12/20.
//
//

#import <UIKit/UIKit.h>
#import <iAd/iAd.h>
#import "GADBannerView.h"
#import "GADBannerViewDelegate.h"

@interface AdViewController : UIViewController<GADBannerViewDelegate> {
    GADBannerView *adView;
    GADBannerView *adView2;
    bool bannerIsVisible;
    float y;
}

@property (nonatomic, retain) GADBannerView *adView;
@property (nonatomic, retain) GADBannerView *adView2;
@property bool bannerIsVisible;

-(void)showAtCenter;
-(void)showAtBottom;
-(void)reloadAds;

@end








