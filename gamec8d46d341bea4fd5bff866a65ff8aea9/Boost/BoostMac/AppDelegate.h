//
//  AppDelegate.h
//  BoostMac
//
//  Created by lygv on 8/24/14.
//  Copyright (c) 2014 smartad. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface AppDelegate : NSObject <NSApplicationDelegate> {
    int countdownload;
    int max;
    NSString *appname;
    NSString *applink;
    IBOutlet NSTextField *text;
}

@property (assign) IBOutlet NSWindow *window;

@end
