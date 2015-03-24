#import <UIKit/UIKit.h>
#import "AdViewController.h"

@class RootViewController;

@interface AppController : NSObject <UIApplicationDelegate> {
    UIWindow *window;
}

@property(nonatomic, readonly) RootViewController* viewController;
@property (nonatomic, retain) AdViewController *adView;

@end

