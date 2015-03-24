//
//  UploadController.m
//  PhotoBox
//
//  Created by LyGV on 11/6/14.
//  Copyright (c) 2014 lygv. All rights reserved.
//

#import "UploadController.h"
#import <MobileCoreServices/UTCoreTypes.h>
#import <FacebookSDK/FacebookSDK.h>
#import <Parse/Parse.h>

@interface UploadController ()

@end

@implementation UploadController

- (void)viewDidLoad {
    [super viewDidLoad];
    UIBarButtonItem *add = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:@"plus.png"] style:UIBarButtonItemStyleDone target:self action:@selector(addImage:)];
    self.navigationItem.rightBarButtonItem = add;
    
    FBLoginView *loginView = [[FBLoginView alloc] init];
    CGPoint p = self.view.center;
    p.y = self.view.frame.size.height - 25;
    loginView.center = p;
    [self.view addSubview:loginView];
    
    status = [[UILabel alloc] initWithFrame:CGRectMake(0, 50, self.view.frame.size.width, 50)];
    [self.view addSubview:status];
}

-(void)addImage:(id)sender {
    if (!self.albumid) {
        [[[UIAlertView alloc] initWithTitle:nil message:@"Choose album first" delegate:nil cancelButtonTitle:@"OK" otherButtonTitles: nil] show];
        return;
    }
    ELCImagePickerController *elcPicker = [[ELCImagePickerController alloc] initImagePicker];
    elcPicker.maximumImagesCount = 100; //Set the maximum number of images to select to 100
    elcPicker.returnsOriginalImage = YES; //Only return the fullScreenImage, not the fullResolutionImage
    elcPicker.returnsImage = YES; //Return UIimage if YES. If NO, only return asset location information
    elcPicker.onOrder = YES; //For multiple image selection, display and return order of selected images
    elcPicker.mediaTypes = @[(NSString *)kUTTypeImage, (NSString *)kUTTypeMovie]; //Supports image and movie types
    elcPicker.imagePickerDelegate = self;
    [self presentViewController:elcPicker animated:YES completion:nil];
}

#pragma mark ELCImagePickerControllerDelegate Methods
- (void)elcImagePickerController:(ELCImagePickerController *)picker didFinishPickingMediaWithInfo:(NSArray *)info
{
    uploadIndex = 0;
    [self dismissViewControllerAnimated:YES completion:nil];
    NSMutableArray *images = [NSMutableArray arrayWithCapacity:[info count]];
    for (NSDictionary *dict in info) {
        if ([dict objectForKey:UIImagePickerControllerMediaType] == ALAssetTypePhoto){
            if ([dict objectForKey:UIImagePickerControllerOriginalImage]){
                UIImage* image=[dict objectForKey:UIImagePickerControllerOriginalImage];
                [images addObject:image];
            } else {
                NSLog(@"UIImagePickerControllerReferenceURL2 = %@", dict);
            }
        } else if ([dict objectForKey:UIImagePickerControllerMediaType] == ALAssetTypeVideo){
            if ([dict objectForKey:UIImagePickerControllerOriginalImage]){
                UIImage* image=[dict objectForKey:UIImagePickerControllerOriginalImage];
                [images addObject:image];
            } else {
                NSLog(@"UIImagePickerControllerReferenceURL4 = %@", dict);
            }
        } else {
            NSLog(@"Uknown asset type");
        }
    }
    self.chosenImages = images;

    NSArray *permissionsNeeded = @[@"public_profile", @"user_photos", @"publish_actions"];
    [FBRequestConnection startWithGraphPath:@"/me/permissions" completionHandler:^(FBRequestConnection *connection, id result, NSError *error) {
        if (!error){
            BOOL photopermission = false;
            for (NSDictionary *p in (NSArray *)[result data]) {
                if ([[p objectForKey:@"permission"] isEqualToString:@"publish_actions"]) {
                    photopermission = true;
                }
            }
            if (photopermission == false){
                [FBSession.activeSession
                 requestNewReadPermissions:permissionsNeeded
                 completionHandler:^(FBSession *session, NSError *error) {
                     if (!error) {
                         [self uploadPhoto];
                     }
                 }];
            } else {
                [self uploadPhoto];
            }
        }
    }];
}

-(void)uploadPhoto {
    if (uploadIndex >= self.chosenImages.count) {
        NSLog(@"Finish");
        status.text = @"Upload complete!";
        return;
    }
    NSLog(@"Uploading photo %d/%d", uploadIndex, self.chosenImages.count);
    status.text = [NSString stringWithFormat:@"Uploading photo %d/%d", uploadIndex + 1, self.chosenImages.count];
    UIImage *image = [self.chosenImages objectAtIndex:uploadIndex];
    uploadIndex++;
    NSMutableDictionary<FBGraphObject> *obj = [FBGraphObject graphObject];
    obj[@"picture"] = UIImageJPEGRepresentation(image, 1.0);
    NSMutableDictionary* params = [[NSMutableDictionary alloc] init];
    [params setObject:UIImagePNGRepresentation(image) forKey:@"picture"];
    [FBRequestConnection startWithGraphPath:@"me/photos" parameters:params HTTPMethod:@"POST" completionHandler:^(FBRequestConnection *connection, id result, NSError *error) {
         if (error) {
             NSLog(@"Error: %@", error);
             [self performSelectorOnMainThread:@selector(uploadPhoto) withObject:nil waitUntilDone:NO];
         } else {
             NSLog(@"Result: %@", result);
             NSString *pid = [result objectForKey:@"id"];
             [FBRequestConnection startWithGraphPath:pid completionHandler:^(FBRequestConnection *connection, id result, NSError *error) {
                 if (error) {
                     NSLog(@"Error: %@", error);
                     [self performSelectorOnMainThread:@selector(uploadPhoto) withObject:nil waitUntilDone:NO];
                 } else {
                     NSArray *imgs = [result objectForKey:@"images"];
                     PFObject *photo = [PFObject objectWithClassName:@"Photos"];
                     photo[@"image_url"] = [[imgs firstObject] objectForKey:@"source"];
                     photo[@"icon_url"] = [[imgs lastObject] objectForKey:@"source"];
                     photo[@"album_id"] = self.albumid;
                     [photo saveInBackgroundWithBlock:^(BOOL succeeded, NSError *error) {
                         if (succeeded) {
                             NSLog(@"success");
                             [self performSelectorOnMainThread:@selector(uploadPhoto) withObject:nil waitUntilDone:NO];
                         } else {
                             NSLog(@"Error %@", error);
                             [self performSelectorOnMainThread:@selector(uploadPhoto) withObject:nil waitUntilDone:NO];
                         }
                     }];
                 }
             }];
         }
     }];
}

- (void)elcImagePickerControllerDidCancel:(ELCImagePickerController *)picker
{
    [self dismissViewControllerAnimated:YES completion:nil];
}



@end
