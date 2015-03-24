//
//  SqlCipher.h
//  SqlCipher
//
//  Created by LyGV on 3/13/13.
//  Copyright (c) 2013 LyGV. All rights reserved.
//

#import <Foundation/Foundation.h>
//#import "FMDatabase.h"

@interface SqlCipher// : FMDatabase

-(NSMutableArray*)fetchDataAsArray:(NSString*)query;

@end
