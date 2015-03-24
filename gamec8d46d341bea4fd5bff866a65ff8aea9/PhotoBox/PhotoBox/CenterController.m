//
//  CenterController.m
//  PhotoBox
//
//  Created by LyGV on 11/5/14.
//  Copyright (c) 2014 lygv. All rights reserved.
//

#import "CenterController.h"
#import "UploadController.h"
#import "PhotoController.h"
#import "AppDelegate.h"
#import "RightController.h"
#import "JASidePanelController.h"
#import "UIImageView+AFNetworking.h"
#import <Parse/Parse.h>

#define  pagesize 100

@interface CenterController ()

@end

@implementation CenterController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.title = @"new";
    photos = [NSMutableArray array];
    self.view.backgroundColor = [UIColor colorWithRed:240.0/255.0 green:240.0/255.0 blue:240.0/255.0 alpha:1.0];
    
    CGRect r = self.view.frame;
    if ([[[UIDevice currentDevice] systemVersion] floatValue] < 8.0) {
        r.origin.y = 64;
        r.size.height -= 64;
    }
    UICollectionViewFlowLayout *flowLayout = [[UICollectionViewFlowLayout alloc] init];
    [flowLayout setItemSize:CGSizeMake(320/3, 320/3)];
    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) {
        [flowLayout setItemSize:CGSizeMake(420/3, 420/3)];
    }
    [flowLayout setScrollDirection:UICollectionViewScrollDirectionVertical];
    [flowLayout setMinimumInteritemSpacing:0.0f];
    [flowLayout setMinimumLineSpacing:0.0f];
    collection = [[UICollectionView alloc] initWithFrame:r collectionViewLayout:flowLayout];
    collection.backgroundColor = [UIColor colorWithRed:240.0/255.0 green:240.0/255.0 blue:240.0/255.0 alpha:1.0];
    collection.delegate = self;
    collection.dataSource = self;
    collection.showsVerticalScrollIndicator = NO;
    [self.view addSubview:collection];
    [collection registerClass:[UICollectionViewCell class] forCellWithReuseIdentifier:@"cell"];
    
    refreshControl = [[UIRefreshControl alloc] init];
    [collection addSubview:refreshControl];
    [refreshControl addTarget:self action:@selector(reloadPhoto) forControlEvents:UIControlEventValueChanged];
    
    if (TARGET_IPHONE_SIMULATOR) {
        UIBarButtonItem *add = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:@"plus.png"] style:UIBarButtonItemStyleDone target:self action:@selector(addImage:)];
        self.navigationItem.rightBarButtonItem = add;
    }

    pageIndex = 0;
    [self loadPhoto];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(applicationEnterForeground:) name:UIApplicationWillEnterForegroundNotification object:nil];
    [self setUpAdmob];
    [self showAdmobFull];
}

-(void)applicationEnterForeground:(NSNotification*)notification {
    [self performSelectorOnMainThread:@selector(showAdmobFull) withObject:nil waitUntilDone:NO];
}

-(void)setUpAdmob {
    adView = [[GADBannerView alloc] initWithAdSize:kGADAdSizeSmartBannerPortrait];
    adView.rootViewController = self;
    adView.adUnitID = @"ca-app-pub-2391571498010954/7758904647";
    adView.delegate = self;
    [self.view addSubview:adView];
    GADRequest *request = [GADRequest request];
    //request.testDevices = @[GAD_SIMULATOR_ID, @"5887ac15a60a9fca8d04e095fabdfe7b"];
    [adView loadRequest:request];
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

-(void)viewWillAppear:(BOOL)animated {
    [collection reloadData];
    [super viewWillAppear:animated];
}

-(void)reloadPhoto {
    pageIndex = 0;
    [self loadPhoto];
}

-(void)loadPhoto {
    PFQuery *query = [PFQuery queryWithClassName:@"Photos"];
    query.skip = pageIndex*pagesize;
    query.limit = pagesize;
    [query orderByDescending:@"createdAt"];
    if (menuid != nil) {
        [query whereKey:@"album_id" equalTo:menuid];
    } else {
        PFQuery *mquery = [PFQuery queryWithClassName:@"Albums"];
        [mquery orderByAscending:@"order"];
        [mquery whereKey:@"visible" equalTo:[NSNumber numberWithBool:YES]];
        [query whereKey:@"album_id" matchesKey:@"objectId" inQuery:mquery];
    }
    [query findObjectsInBackgroundWithBlock:^(NSArray *objects, NSError *error) {
        if(pageIndex == 0) [photos removeAllObjects];
        [photos addObjectsFromArray:objects];
        NSLog(@"count %lu", (unsigned long)photos.count);
        [collection reloadData];
        [refreshControl endRefreshing];
    }];
}

-(void)addImage:(id)sender {
    UIStoryboard *mainStoryboard = [UIStoryboard storyboardWithName:@"Main" bundle:[NSBundle mainBundle]];
    UploadController *center = [mainStoryboard instantiateViewControllerWithIdentifier:@"UploadController"];
    center.albumid = menuid;
    [self.navigationController pushViewController:center animated:YES];
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
    UIImageView *img = (UIImageView*)[cell.contentView viewWithTag:1];
    if(img == nil) img = [[UIImageView alloc] init];
    img.tag = 1;
    img.frame = CGRectMake(0, 0, 321/3, 320/3);
    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) {
        img.frame = CGRectMake(0, 0, 421/3, 420/3);
    }
    [img setImage:nil];
    [img setContentMode:UIViewContentModeScaleAspectFit];
    [img setImageWithURL:[NSURL URLWithString:photo[@"icon_url"]]];
    [cell.contentView addSubview:img];
    if (indexPath.row == photos.count - 1 && photos.count % pagesize == 0) {
        pageIndex++;
        [self loadPhoto];
    }
    return cell;
}

-(void)collectionView:(UICollectionView *)collectionView didSelectItemAtIndexPath:(NSIndexPath *)indexPath {
    UIStoryboard *mainStoryboard = [UIStoryboard storyboardWithName:@"Main" bundle:[NSBundle mainBundle]];
    PhotoController *center = [mainStoryboard instantiateViewControllerWithIdentifier:@"PhotoController"];
    center.photos = photos;
    center.index = indexPath;
    [self.navigationController pushViewController:center animated:YES];
}

-(void) setMenuId:(NSString *)mid title:(NSString *)title {
    menuid = mid;
    menutitle = title;
    self.title = title;
    [self performSelectorOnMainThread:@selector(reloadPhoto) withObject:nil waitUntilDone:NO];
}



@end
