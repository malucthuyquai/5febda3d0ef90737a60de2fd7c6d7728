#include "Translate.h"
#import "AppController.h"
#include "Global.h"
#import <Social/Social.h>
#import <Accounts/Accounts.h>
#import "Flurry.h"
#import "GCHelper.h"
#import "Chartboost.h"

enum GAME_LEVEL {
    LEVEL_NORMAL = 1,
    LEVEL_HARD = 2,
    LEVEL_SUPPERHARD = 3,
    LEVEL_ULTRAHARD = 4
};

//Notification key
#define kNotifyShowiAds         "notifyshowiads"
#define kNotifyHideiAds         "notifyhideiads"
#define kNotifyShowiAdsCenter   "notifyshowiadscenter"
#define kNotifyShowiAdsBottom   "notifyshowiadsbottom"
#define kNotifyShareFacebook    "notifysharefacebook"
#define kNotifyFlurryLogEvent   "notifyflurrylogevent"
#define kNotifyGCAuthen         "notifygamecenterauthenuser"
#define kNotifyGCShow           "notifygamecentershowleaderboard"
#define kNotifyGCSubmit         "notifygamecentersubmitscore"
#define kNotifyHideSplash       "notificationhidesplash"

//GameCenter
#define kLeaderBoard            @"mobi.smartad.beatmouse.leaderboard"

//Appstore link
#define kAppStoreLink           @"https://itunes.apple.com/us/app/beat-mouse/id838675263?ls=1&mt=8"
#define kAppOtaLink             @"http://appstore.vn/ios/tai-game-iphone/dap-chuot/26485"

USING_NS_CC;

static Translate* _translate;

Translate* Translate::sharedTranslate(){
    if (!_translate) {
        _translate = Translate::create();
    }
    return _translate;
}

Translate::~Translate() {
    //CCNotificationCenter *notify = CCNotificationCenter::sharedNotificationCenter();
    //notify->removeAllObservers(this);
}

bool Translate::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCNode::init() )
    {
        return false;
    }
    CCNotificationCenter *notify = CCNotificationCenter::sharedNotificationCenter();
    //iAds
    notify->addObserver(this, callfuncO_selector(Translate::showiAds), kNotifyShowiAds, this);
    notify->addObserver(this, callfuncO_selector(Translate::showiAdsAtCenter), kNotifyShowiAdsCenter, this);
    notify->addObserver(this, callfuncO_selector(Translate::showiAdsAtBottom), kNotifyShowiAdsBottom, this);
    notify->addObserver(this, callfuncO_selector(Translate::hideiAds), kNotifyHideiAds, this);
    //ChartBoost
    notify->addObserver(this, callfuncO_selector(Translate::showCharboot), kNotificationShowChartBoost, this);
    //Facebook
    notify->addObserver(this, callfuncO_selector(Translate::shareFacebook), kNotifyShareFacebook, this);
    //Game center
    notify->addObserver(this, callfuncO_selector(Translate::showLeaderBoard), kNotifyGCShow, this);
    notify->addObserver(this, callfuncO_selector(Translate::authenLocalGCUser), kNotifyGCAuthen, this);
    notify->addObserver(this, callfuncO_selector(Translate::submitGCScore), kNotifyGCSubmit, this);
    notify->addObserver(this, callfuncO_selector(Translate::notificationHideSplash), kNotifyHideSplash, this);
    return true;
}

void Translate::showiAds(CCObject *object) {

}

void Translate::hideiAds(CCObject *object) {

}

void Translate::showiAdsAtCenter(CCObject *object) {
    
}

void Translate::showiAdsAtBottom(CCObject *object) {

}

void Translate::notificationHideSplash() {
    [appController hideSplash];
}

void Translate::flurryLogEvent(cocos2d::CCObject *object) {
    [Flurry logEvent:[NSString stringWithUTF8String:Global::sharedGlobal()->flurryEventName.c_str()]];
}

void Translate::showLeaderBoard(cocos2d::CCObject *object) {
    [[GCHelper shared] showLeaderBoard:kLeaderBoard];
}

void Translate::authenLocalGCUser(cocos2d::CCObject *object) {
    [[GCHelper shared] authenticateLocalUser];
}

void Translate::submitGCScore(cocos2d::CCObject *object) {
    Global *g = Global::sharedGlobal();
    NSString *category = kLeaderBoard;
    [[GCHelper shared] submitScore:g->score total:g->total category:category];
}

void Translate::showCharboot(cocos2d::CCObject *object) {
    //Chartboost
    NSLog(@"show charboot");
    Chartboost *cb = [Chartboost sharedChartboost];
    cb.appId = kcbAppId;
    cb.appSignature = kcbSignature;
    [cb startSession];
    [cb showInterstitial];
}

void Translate::shareFacebook(CCObject *object) {
    if (!NSClassFromString(@"SLComposeViewController")
        || ![SLComposeViewController instanceMethodForSelector:@selector(isAvailableForServiceType:)]) {
        
        return;
    }
    SLComposeViewController *compose = [SLComposeViewController composeViewControllerForServiceType:SLServiceTypeFacebook];
    //Global *g = Global::sharedGlobal();
    NSString *link = kAppOtaLink;
    if (kAppStore == 1) {
        link = kAppStoreLink;
    }
    NSString *path = [NSHomeDirectory() stringByAppendingPathComponent:@"Documents/screenshot.png"];
    
    //NSString *score = [NSString stringWithUTF8String:CCString::createWithFormat("%.0f", g->score)->getCString()];
    [compose setInitialText:[NSString stringWithFormat:@"The best funny game! Check out at %@", link]];
    [compose addImage:[UIImage imageWithData:[NSData dataWithContentsOfURL:[NSURL fileURLWithPath:path]]]];
    UIWindow *window = [[UIApplication sharedApplication].windows objectAtIndex:0];
    [window.rootViewController presentViewController:compose animated:YES completion:nil];
    
    [compose setCompletionHandler:^(SLComposeViewControllerResult result) {
        NSString *output;
        switch (result) {
            case SLComposeViewControllerResultCancelled:
                output = @"Action Cancelled";
                break;
            case SLComposeViewControllerResultDone:
                output = @"Post Successfull";
                break;
            default:
                break;
        }
        //UIAlertView *alert = [[[UIAlertView alloc] initWithTitle:@"Facebook" message:output delegate:nil cancelButtonTitle:@"Ok" otherButtonTitles:nil] autorelease];
        //[alert show];
    }];
}



