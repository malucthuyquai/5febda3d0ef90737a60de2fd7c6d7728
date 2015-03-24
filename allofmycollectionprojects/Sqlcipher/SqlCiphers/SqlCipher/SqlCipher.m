//
//  SqlCipher.m
//  SqlCipher
//
//  Created by LyGV on 3/13/13.
//  Copyright (c) 2013 LyGV. All rights reserved.
//

#import "SqlCipher.h"

@implementation SqlCipher

-(NSMutableArray*)fetchDataAsArray:(NSString *)query{
    NSMutableArray *array = [NSMutableArray array];
//    FMResultSet *rs = [self executeQuery:query];
//    while ([rs next]) {
//        [array addObject:[rs resultDictionary]];
//    }
    return array;
}

@end
