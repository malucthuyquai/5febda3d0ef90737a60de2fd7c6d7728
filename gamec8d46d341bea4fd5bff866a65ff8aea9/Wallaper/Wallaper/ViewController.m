//
//  ViewController.m
//  Wallaper
//
//  Created by LyGV on 7/24/14.
//  Copyright (c) 2014 lygv. All rights reserved.
//

#import "ViewController.h"
#import "NibCell.h"
#import "CustomLayout.h"
#import "ImageViewController.h"

@interface ViewController () {
    UICollectionView *clView;
}
@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    
    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) {
        CustomLayout *flowlayout = [[CustomLayout alloc] init];
        [flowlayout setItemSize:CGSizeMake(240, 200)];
        [flowlayout setMinimumInteritemSpacing:0];
        [flowlayout setMinimumLineSpacing:15];
        [flowlayout setSectionInset:UIEdgeInsetsMake(10, 10, 10, 0)];
        [flowlayout setScrollDirection:UICollectionViewScrollDirectionVertical];
        CGRect r = self.view.frame;
        clView = [[UICollectionView alloc] initWithFrame:r collectionViewLayout:flowlayout];
        clView.dataSource = self;
        clView.delegate = self;
        [self.view addSubview:clView];
        UINib *cellNib = [UINib nibWithNibName:@"NibCell_iPad" bundle:nil];
        [clView registerNib:cellNib forCellWithReuseIdentifier:@"Cell"];
    } else {
        CustomLayout *flowlayout = [[CustomLayout alloc] init];
        [flowlayout setItemSize:CGSizeMake(100, 100)];
        [flowlayout setMinimumInteritemSpacing:0];
        [flowlayout setMinimumLineSpacing:5];
        [flowlayout setSectionInset:UIEdgeInsetsMake(6, 5, 5, 0)];
        [flowlayout setScrollDirection:UICollectionViewScrollDirectionVertical];
        CGRect r = self.view.frame;
        clView = [[UICollectionView alloc] initWithFrame:r collectionViewLayout:flowlayout];
        clView.dataSource = self;
        clView.delegate = self;
        [self.view addSubview:clView];
        UINib *cellNib = [UINib nibWithNibName:@"NibCell" bundle:nil];
        [clView registerNib:cellNib forCellWithReuseIdentifier:@"Cell"];
    }
}


-(UICollectionViewCell*)collectionView:(UICollectionView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath {
    NibCell *cell = [collectionView dequeueReusableCellWithReuseIdentifier:@"Cell" forIndexPath:indexPath];
    UIImage *img = [UIImage imageNamed:[NSString stringWithFormat:@"%ld.jpg", (long)indexPath.row + 1]];
    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) {
        cell.image.image = [self imageWithImage:img scaledToMaxWidth:150 maxHeight:150];
    } else {
        cell.image.image = [self imageWithImage:img scaledToMaxWidth:100 maxHeight:100];
    }
    cell.delegate = (id<CellDelegate>)self;
    cell.imageName = [NSString stringWithFormat:@"%ld.jpg", (long)indexPath.row + 1];
    return cell;
}

-(void)selectCell:(id)cell_ {
    NibCell *cell = (NibCell*)cell_;
    ImageViewController *vc;
    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) {
        vc = [[ImageViewController alloc] initWithNibName:@"ImageViewController_iPad" bundle:nil];
    } else {
        vc = [[ImageViewController alloc] init];
    }
    vc.imageName = cell.imageName;
    [self presentViewController:vc animated:YES completion:nil];
}

-(NSInteger)collectionView:(UICollectionView *)collectionView numberOfItemsInSection:(NSInteger)section {
    return 106;
}

-(NSInteger)numberOfSectionsInCollectionView:(UICollectionView *)collectionView {
    return 1;
}


-(UIImage *)imageWithImage:(UIImage *)image scaledToSize:(CGSize)size {
    if ([[UIScreen mainScreen] respondsToSelector:@selector(scale)]) {
        UIGraphicsBeginImageContextWithOptions(size, NO, [[UIScreen mainScreen] scale]);
    } else {
        UIGraphicsBeginImageContext(size);
    }
    [image drawInRect:CGRectMake(0, 0, size.width, size.height)];
    UIImage *newImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    
    return newImage;
}

-(UIImage *)imageWithImage:(UIImage *)image scaledToMaxWidth:(CGFloat)width maxHeight:(CGFloat)height {
    CGFloat oldWidth = image.size.width;
    CGFloat oldHeight = image.size.height;
    
    CGFloat scaleFactor = (oldWidth > oldHeight) ? width / oldWidth : height / oldHeight;
    
    CGFloat newHeight = oldHeight * scaleFactor;
    CGFloat newWidth = oldWidth * scaleFactor;
    CGSize newSize = CGSizeMake(newWidth, newHeight);
    
    return [self imageWithImage:image scaledToSize:newSize];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
