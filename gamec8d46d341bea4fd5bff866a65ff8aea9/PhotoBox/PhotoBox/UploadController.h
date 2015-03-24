//
//  UploadController.h
//  PhotoBox
//
//  Created by LyGV on 11/6/14.
//  Copyright (c) 2014 lygv. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ELCImagePickerHeader.h"

@interface UploadController : UIViewController <ELCImagePickerControllerDelegate, UINavigationControllerDelegate> {
    int uploadIndex;
    UILabel *status;
}

@property (nonatomic, copy) NSArray *chosenImages;
@property (nonatomic, retain) NSString *albumid;


@end
