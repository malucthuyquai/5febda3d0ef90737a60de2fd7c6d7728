//
//  PhotoController.h
//  PhotoBox
//
//  Created by LyGV on 11/7/14.
//  Copyright (c) 2014 lygv. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "GADBannerView.h"
#import "GADBannerViewDelegate.h"
#import "GADInterstitial.h"

@interface PhotoController : UIViewController<UICollectionViewDelegate, UICollectionViewDataSource, GADBannerViewDelegate, GADInterstitialDelegate> {
    UICollectionView *collection;
    BOOL initialScrollDone;
    NSIndexPath *currentIndex;
    GADBannerView *adView;
    GADInterstitial *interstitial_;
}

@property(nonatomic, assign) NSArray *photos;
@property(nonatomic, assign) NSIndexPath *index;

@end
