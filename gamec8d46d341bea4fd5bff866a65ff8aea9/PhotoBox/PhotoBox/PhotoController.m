//
//  PhotoController.m
//  PhotoBox
//
//  Created by LyGV on 11/7/14.
//  Copyright (c) 2014 lygv. All rights reserved.
//

#import "PhotoController.h"
#import "UIImageView+AFNetworking.h"
#import "JTSImageViewController.h"
#import "JTSImageInfo.h"
#import <Parse/Parse.h>

@interface PhotoController ()

@end

@implementation PhotoController
@synthesize photos, index;

- (void)viewDidLoad {
    [super viewDidLoad];
    CGRect r = self.view.frame;
    if ([[[UIDevice currentDevice] systemVersion] floatValue] < 8.0) {
        r.origin.y = 64;
        r.size.height -= 64;
    }
    UICollectionViewFlowLayout *flowLayout = [[UICollectionViewFlowLayout alloc] init];
    [flowLayout setItemSize:CGSizeMake(self.view.frame.size.width, self.view.frame.size.height)];
    [flowLayout setScrollDirection:UICollectionViewScrollDirectionHorizontal];
    [flowLayout setMinimumInteritemSpacing:0.0f];
    [flowLayout setMinimumLineSpacing:0.0f];
    collection = [[UICollectionView alloc] initWithFrame:r collectionViewLayout:flowLayout];
    collection.backgroundColor = [UIColor colorWithRed:240.0/255.0 green:240.0/255.0 blue:240.0/255.0 alpha:1.0];
    collection.delegate = self;
    collection.dataSource = self;
    collection.pagingEnabled = YES;
    collection.showsHorizontalScrollIndicator = NO;
    flowLayout.itemSize = collection.frame.size;
    [self.view addSubview:collection];
    [collection registerClass:[UICollectionViewCell class] forCellWithReuseIdentifier:@"cell"];
    
    UIBarButtonItem *add = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:@"save.png"] style:UIBarButtonItemStyleDone target:self action:@selector(saveImage:)];
    self.navigationItem.rightBarButtonItem = add;
    
    UITapGestureRecognizer *tap = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(tap:)];
    [self.view addGestureRecognizer:tap];
    
    [self setUpAdmob];
}

-(void)setUpAdmob {
    adView = [[GADBannerView alloc] initWithAdSize:kGADAdSizeSmartBannerPortrait];
    adView.rootViewController = self;
    adView.adUnitID = @"ca-app-pub-2391571498010954/7758904647";
    adView.delegate = self;
    [self.view addSubview:adView];
    GADRequest *request = [GADRequest request];
    //request.testDevices = @[GAD_SIMULATOR_ID, @"43274bfdb51c3c88b81d3b9bb446d4a9"];
    [adView loadRequest:request];
}

- (void)adViewDidReceiveAd:(GADBannerView *)view
{
    NSLog(@"%s", __func__);
    CGRect r = view.frame;
    r.origin.y = [UIScreen mainScreen].bounds.size.height - r.size.height;
    r.origin.x = 0;
    adView.frame = r;
}

- (void)adView:(GADBannerView *)view didFailToReceiveAdWithError:(GADRequestError *)error
{
    NSLog(@"%s - %@", __func__, error.description);
}

-(void)showAdmobFull {
    interstitial_ = [[GADInterstitial alloc] init];
    interstitial_.delegate = self;
    interstitial_.adUnitID = @"ca-app-pub-2391571498010954/9235637841";
    GADRequest *request = [GADRequest request];
    //request.testDevices = @[GAD_SIMULATOR_ID, @"5887ac15a60a9fca8d04e095fabdfe7b"];
    [interstitial_ loadRequest:request];
}

- (void)interstitialDidReceiveAd:(GADInterstitial *)ad
{
    NSLog(@"%s", __func__);
    [interstitial_ presentFromRootViewController:self];
}

-(void)interstitial:(GADInterstitial *)ad didFailToReceiveAdWithError:(GADRequestError *)error {
    NSLog(@"%s - %@", __func__, error.description);
}

-(void)viewWillAppear:(BOOL)animated {
    [collection reloadData];
    [super viewWillAppear:animated];
}

- (void)tap:(UIPinchGestureRecognizer *)recognizer
{
    if ([[collection visibleCells] count] == 1) {
        UICollectionViewCell *cell = [[collection visibleCells] objectAtIndex:0];
        UIImageView *img = (UIImageView*)[cell.contentView viewWithTag:98];
        if (img.image != nil) {
            // Create image info
            JTSImageInfo *imageInfo = [[JTSImageInfo alloc] init];
            imageInfo.image = img.image;
            imageInfo.referenceRect = img.frame;
            imageInfo.referenceView = img.superview;
            imageInfo.referenceContentMode = img.contentMode;
            imageInfo.referenceCornerRadius = img.layer.cornerRadius;
            // Setup view controller
            JTSImageViewController *imageViewer = [[JTSImageViewController alloc]
                                                   initWithImageInfo:imageInfo
                                                   mode:JTSImageViewControllerMode_Image
                                                   backgroundStyle:JTSImageViewControllerBackgroundOption_Scaled];
            // Present the view controller.
            [imageViewer showFromViewController:self transition:JTSImageViewControllerTransition_FromOriginalPosition];
        }
    }
}

-(void)saveImage:(id)sender {
    UICollectionViewCell *cell = [collection cellForItemAtIndexPath:currentIndex];
    UIImageView *imgview = (UIImageView*)[cell.contentView viewWithTag:98];
    if (imgview.image == nil) {
        [[[UIAlertView alloc] initWithTitle:nil message:@"Image still loading!" delegate:nil cancelButtonTitle:@"OK" otherButtonTitles: nil] show];
        return;
    }
    UIImageWriteToSavedPhotosAlbum(imgview.image, self, @selector(image:didFinishSavingWithError:contextInfo:), nil);
}

- (void)image:(UIImage*)image didFinishSavingWithError:(NSError *)error contextInfo:(void *)contextInfo {
    [[[UIAlertView alloc] initWithTitle:nil message:@"Save complete!" delegate:nil cancelButtonTitle:@"OK" otherButtonTitles: nil] show];
}

- (void)viewDidLayoutSubviews {
    if (!initialScrollDone) {
        initialScrollDone = YES;
        [collection scrollToItemAtIndexPath:index atScrollPosition:UICollectionViewScrollPositionRight animated:NO];
    }
}

-(NSInteger)numberOfSectionsInCollectionView:(UICollectionView *)collectionView {
    return 1;
}

-(NSInteger)collectionView:(UICollectionView *)collectionView numberOfItemsInSection:(NSInteger)section {
    return photos.count;
}

-(UICollectionViewCell*)collectionView:(UICollectionView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath {
    UICollectionViewCell *cell = [collectionView dequeueReusableCellWithReuseIdentifier:@"cell" forIndexPath:indexPath];
    if (cell == nil) {
        cell = [[UICollectionViewCell alloc] init];
    }
    PFObject *photo = [photos objectAtIndex:indexPath.row];
    UIImageView *img = (UIImageView*)[cell.contentView viewWithTag:98];
    if(img == nil) img = [[UIImageView alloc] init];
    img.tag = 98;
    img.frame = cell.contentView.frame;
    [img setContentMode:UIViewContentModeScaleAspectFit];
    [img setImage:nil];
    [img setImageWithURL:[NSURL URLWithString:photo[@"image_url"]]];
    [cell.contentView addSubview:img];
    currentIndex = indexPath;
    
    if (rand() % 50 == 1) {
        [self showAdmobFull];
    }
    
    return cell;
}

-(void)collectionView:(UICollectionView *)collectionView didSelectItemAtIndexPath:(NSIndexPath *)indexPath {
    
}





@end
