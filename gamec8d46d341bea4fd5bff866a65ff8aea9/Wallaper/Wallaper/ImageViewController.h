//
//  ImageViewController.h
//  Wallaper
//
//  Created by LyGV on 7/24/14.
//  Copyright (c) 2014 lygv. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ImageViewController : UIViewController {
    IBOutlet UIImageView *imageView;
}

@property (nonatomic, retain) NSString *imageName;
-(IBAction)close:(id)sender;
-(IBAction)save:(id)sender;

@end
