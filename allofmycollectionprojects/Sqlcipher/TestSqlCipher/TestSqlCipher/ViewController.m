//
//  ViewController.m
//  TestSqlCipher
//
//  Created by LyGV on 3/13/13.
//  Copyright (c) 2013 LyGV. All rights reserved.
//

#import "ViewController.h"
#import <SqlCipher/SqlCipher.h>

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    NSString *p = [[NSBundle mainBundle] pathForResource:@"masterdata.sqlite3" ofType:nil];
    SqlCipher *sql = [SqlCipher databaseWithPath:p andKey:@"21fc123678edfd999aaab4f378b9110d"];
    if ([sql tableExists:@"cards"]) {
        NSLog(@"%@", [sql fetchDataAsArray:@"select * from skill"]);
    }
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
