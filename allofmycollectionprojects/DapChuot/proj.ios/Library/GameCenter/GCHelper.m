//
//  GCHelper.m
//  EggSeed
//
//  Created by LyGV on 2014/01/02.
//
//

#import "GCHelper.h"
#import "AppController.h"


static GCHelper *gcHelper;

@implementation GCHelper

+(GCHelper*)shared {
    if (!gcHelper) {
        gcHelper = [[GCHelper alloc] init];
    }
    return gcHelper;
}

-(void)authenticateLocalUser {
    if ([[GKLocalPlayer class] instancesRespondToSelector:@selector(setAuthenticateHandler:)]) {
        [[GKLocalPlayer localPlayer] setAuthenticateHandler:^(UIViewController *loginViewController, NSError *error) {
            if (loginViewController) {
                [appController.window.rootViewController presentViewController:loginViewController animated:YES completion:^{
                    userAuthenticated = YES;
                }];
            } else {
                userAuthenticated = YES;
            }
        }];
    } else { // alternative for iOS < 6
        [[GKLocalPlayer localPlayer] authenticateWithCompletionHandler:^(NSError *error) {
            if (!error) {
                userAuthenticated = YES;
            }
        }];
    }
}

-(void)showLeaderBoard:(NSString*)leaderBoardId {
    ldView = [[[GKLeaderboardViewController alloc] init] autorelease];
    if (ldView != NULL) {
        ldView.category = nil;;
        ldView.timeScope = GKLeaderboardTimeScopeWeek;
        ldView.leaderboardDelegate = self;
        if(!viewController) {
            viewController = [[UIViewController alloc] init];
        }
        [appController.window addSubview:viewController.view];
        [viewController presentModalViewController:ldView animated:YES];
    }
}

-(void)submitScore:(int64_t)score total:(int64_t)total category:(NSString *)category {
    NSLog(@"");
    if (!userAuthenticated) {
        //return;
    }
    GKScore* gkScore = [[[GKScore alloc] initWithCategory:category] autorelease];
    gkScore.value = score;
    [gkScore reportScoreWithCompletionHandler:^(NSError* error) {
        if (error) {
            NSLog(@"Submit score Error %@", error);
        } else {
            NSLog(@"Submit score 2 success");
        }
    }];
}

-(void)leaderboardViewControllerDidFinish:(GKLeaderboardViewController *)viewController_ {
    NSLog(@"");
    [ldView dismissViewControllerAnimated:YES completion:^{
        [viewController.view removeFromSuperview];
        [viewController release];
        viewController = nil;
    }];
}

@end
