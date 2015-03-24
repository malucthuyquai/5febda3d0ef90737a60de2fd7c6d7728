//
//  NibCell.h
//  Wallaper
//
//  Created by LyGV on 7/24/14.
//  Copyright (c) 2014 lygv. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol CellDelegate <NSObject>

@optional
-(void)selectCell:(id)cell;

@end

@interface NibCell : UICollectionViewCell {

    IBOutlet UIImageView *image;
}

@property(nonatomic, retain) IBOutlet UIImageView *image;
@property(nonatomic, retain) NSString *imageName;
@property(nonatomic, assign) id<CellDelegate> delegate;
-(IBAction)select:(id)sender;

@end
