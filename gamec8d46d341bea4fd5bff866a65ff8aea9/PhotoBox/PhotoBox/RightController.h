//
//  RightController.h
//  PhotoBox
//
//  Created by LyGV on 11/5/14.
//  Copyright (c) 2014 lygv. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface RightController : UIViewController <UITableViewDataSource, UITableViewDelegate> {
    NSMutableArray *menuItems;
    UITableView *tableview;
    UIRefreshControl *refreshControl;
}

@property(nonatomic, retain) NSMutableArray *menuItems;

@end
