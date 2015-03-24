//
//  RightController.m
//  PhotoBox
//
//  Created by LyGV on 11/5/14.
//  Copyright (c) 2014 lygv. All rights reserved.
//

#import "RightController.h"
#import "JASidePanelController.h"
#import "CreateMenuController.h"
#import "CenterController.h"
#import <Parse/Parse.h>

@interface RightController ()

@end

@implementation RightController
@synthesize menuItems;


- (void)viewDidLoad {
    [super viewDidLoad];
    CGRect r = self.view.frame;
    r.origin.y = 64;
    r.size.height -= 64;
    r.size.width = 200;
    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) {
        r.size.width = 300;
    }
    tableview = [[UITableView alloc] initWithFrame:r style:UITableViewStylePlain];
    tableview.delegate = self;
    tableview.dataSource = self;
    [tableview setSeparatorInset:UIEdgeInsetsZero];
    tableview.backgroundColor = [UIColor colorWithRed:61.0/255.0 green:64.0/255.0 blue:71.0/255.0 alpha:1.0];
    tableview.separatorColor = [UIColor colorWithRed:75.0/255.0 green:75.0/255.0 blue:75.0/255.0 alpha:1.0];
    tableview.separatorStyle = UITableViewCellSelectionStyleNone;
    tableview.tableFooterView = [UIView new];
    [self.view addSubview:tableview];
    
    refreshControl = [[UIRefreshControl alloc] init];
    [tableview addSubview:refreshControl];
    [refreshControl addTarget:self action:@selector(loadMenu) forControlEvents:UIControlEventValueChanged];
    
    [self loadMenu];
}

-(void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    [self loadMenu];
}

-(void)loadMenu {
    PFQuery *query = [PFQuery queryWithClassName:@"Albums"];
    [query orderByAscending:@"order"];
    [query whereKey:@"visible" equalTo:[NSNumber numberWithBool:YES]];
    [query findObjectsInBackgroundWithBlock:^(NSArray *objects, NSError *error) {
        menuItems = [NSMutableArray arrayWithArray:objects];
        PFObject *new = [PFObject objectWithClassName:@"Albums"];
        [new setValue:@"new" forKey:@"album_name"];
        [menuItems insertObject:new atIndex:0];
        [tableview reloadData];
        [refreshControl endRefreshing];
    }];
}

-(NSInteger)numberOfSectionsInTableView:(UITableView *)tableView { return 1; }
-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    if (TARGET_IPHONE_SIMULATOR) {
        return  menuItems.count + 1;
    }
    return  menuItems.count;
}
-(UITableViewCell*)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"cell"];
    if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"cell"];
    }
    cell.contentView.backgroundColor = [UIColor colorWithRed:61.0/255.0 green:64.0/255.0 blue:71.0/255.0 alpha:1.0];
    if (indexPath.row < menuItems.count) {
        cell.textLabel.text = menuItems[indexPath.row][@"album_name"];
    } else {
        cell.textLabel.text = @"create new album";
    }
    cell.textLabel.textColor = [UIColor colorWithRed:240.0/255.0 green:240.0/255.0 blue:240.0/255.0 alpha:1.0];
    cell.textLabel.font = [UIFont boldSystemFontOfSize:14];
    
    UIView *v = [[UIView alloc] initWithFrame:CGRectMake(0, cell.frame.size.height-1, cell.frame.size.width, 1)];
    v.backgroundColor = [UIColor colorWithRed:75.0/255.0 green:75.0/255.0 blue:75.0/255.0 alpha:1.0];
    [cell.contentView addSubview:v];
    return cell;
}
-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (indexPath.row == menuItems.count) {
        UIStoryboard *mainStoryboard = [UIStoryboard storyboardWithName:@"Main" bundle:[NSBundle mainBundle]];
        CreateMenuController *center = [mainStoryboard instantiateViewControllerWithIdentifier:@"CreateMenuController"];
        [self.navigationController pushViewController:center animated:YES];
        return;
    }
    [tableview deselectRowAtIndexPath:indexPath animated:NO];
    JASidePanelController *side = (JASidePanelController*)self.navigationController.parentViewController;
    [side toggleLeftPanel:self];
    UINavigationController *centernav = (UINavigationController*)side.centerPanel;
    CenterController *center = (CenterController*)centernav.viewControllers[0];
    PFObject *obj = menuItems[indexPath.row];
    [center setMenuId:obj.objectId title:obj[@"album_name"]];
}


@end
