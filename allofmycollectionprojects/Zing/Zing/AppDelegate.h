//
//  AppDelegate.h
//  Zing
//
//  Created by LyGV on 4/8/13.
//  Copyright (c) 2013 LyGV. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface AppDelegate : NSObject <NSApplicationDelegate>{
    int pageindex;
    int songindex;
    NSMutableArray *songarray;
}

@property (assign) IBOutlet NSWindow *window;

@property (assign) IBOutlet NSTextField *page;
@property (assign) IBOutlet NSTextField *song;
@property (assign) IBOutlet NSTextField *title;
@property (assign) IBOutlet NSTextField *percent;
@property (assign) IBOutlet NSTextField *pageinput;

-(IBAction)start:(id)sender;


@end
