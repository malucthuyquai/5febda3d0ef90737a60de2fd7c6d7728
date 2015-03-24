//
//  GCHelper.h
//  EggSeed
//
//  Created by LyGV on 2014/01/02.
//
//

#import <Foundation/Foundation.h>
#import <GameKit/GameKit.h>

@interface GCHelper : NSObject <GKLeaderboardViewControllerDelegate> {
    BOOL userAuthenticated;
    GKLeaderboardViewController *ldView;
    UIViewController *viewController;
}

+(GCHelper*)shared;

-(void)authenticateLocalUser;
-(void)showLeaderBoard:(NSString*)leaderBoardId;
-(void)submitScore:(int64_t)score total:(int64_t)total category:(NSString*)category;

@end
