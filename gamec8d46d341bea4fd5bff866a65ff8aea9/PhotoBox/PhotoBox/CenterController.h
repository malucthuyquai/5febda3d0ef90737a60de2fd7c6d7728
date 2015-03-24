//
//  CenterController.h
//  PhotoBox
//
//  Created by LyGV on 11/5/14.
//  Copyright (c) 2014 lygv. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "GADBannerView.h"
#import "GADBannerViewDelegate.h"
#import "GADInterstitial.h"

@interface CenterController : UIViewController <UICollectionViewDelegate, UICollectionViewDataSource, GADBannerViewDelegate, GADInterstitialDelegate> {
    UICollectionView *collection;
    NSString *menuid;
    NSString *menutitle;
    NSMutableArray *photos;
    UIRefreshControl *refreshControl;
    NSInteger pageIndex;
    GADBannerView *adView;
    GADInterstitial *interstitial_;
}

-(void)setMenuId:(NSString*)mid title:(NSString*)title;

@end
