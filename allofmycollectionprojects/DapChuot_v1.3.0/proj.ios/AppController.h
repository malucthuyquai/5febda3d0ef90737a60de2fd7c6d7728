#import <UIKit/UIKit.h>
#import "AdViewController.h"
#import "Chartboost.h"
#import "iRate.h"

@class RootViewController;

@interface AppController : NSObject <UIApplicationDelegate, iRateDelegate> {
    UIWindow *window;
    RootViewController    *viewController;
    AdViewController *adView;
    UIImageView *splash;
}

@property (nonatomic, retain) UIWindow *window;
@property (nonatomic, retain) AdViewController *adView;

-(void)showSplash;
-(void)hideSplash;

@end

