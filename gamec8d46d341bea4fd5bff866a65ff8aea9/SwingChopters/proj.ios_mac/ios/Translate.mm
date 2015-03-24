#include "Translate.h"
#import "AppController.h"
#include "Global.h"
#import "Flurry.h"
#import "GKHWrapperCpp.h"
#import "RootViewController.h"

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
#define kLeaderBoard            @"mobi.smartad.flappyjump"

//Appstore link
#define kAppStoreLink           @"https://itunes.apple.com/us/app/flappy-jump-bird-flappy-flying/id910035783?ls=1&mt=8"
//#define kAppStoreLink             @""

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
    __NotificationCenter *notify = __NotificationCenter::getInstance();
    //iAds
    notify->addObserver(this, callfuncO_selector(Translate::showiAds), kNotifyShowiAds, this);
    notify->addObserver(this, callfuncO_selector(Translate::showiAdsAtCenter), kNotifyShowiAdsCenter, this);
    notify->addObserver(this, callfuncO_selector(Translate::showiAdsAtBottom), kNotifyShowiAdsBottom, this);
    notify->addObserver(this, callfuncO_selector(Translate::hideiAds), kNotifyHideiAds, this);
    //Game center
    notify->addObserver(this, callfuncO_selector(Translate::showLeaderBoard), kNotifyGCShow, this);
    notify->addObserver(this, callfuncO_selector(Translate::authenLocalGCUser), kNotifyGCAuthen, this);
    notify->addObserver(this, callfuncO_selector(Translate::submitGCScore), kNotifyGCSubmit, this);
    
    notify->addObserver(this, callfuncO_selector(Translate::rate), "rate", this);
    notify->addObserver(this, callfuncO_selector(Translate::share), "share", this);
    notify->addObserver(this, callfuncO_selector(Translate::showadmobfull), "showadmobfull", this);
    
    Global *g = Global::sharedGlobal();
    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) {
        g->isIpad = true;
    }
    
    return true;
}

void Translate::showiAds(Ref *object) {

}

void Translate::hideiAds(Ref *object) {

}

void Translate::showiAdsAtCenter(Ref *object) {
    
}

void Translate::showiAdsAtBottom(Ref *object) {

}

void Translate::showLeaderBoard(cocos2d::Ref *object) {
    GKHWrapperCpp *gkh;
    gkh->showLeaderBoard();
}

void Translate::authenLocalGCUser(cocos2d::Ref *object) {
    GKHWrapperCpp *gkh;
    gkh->authenticateLocalPlayer();
}

void Translate::submitGCScore(cocos2d::Ref *object) {
    Global *g = Global::sharedGlobal();
    GKHWrapperCpp *gkh;
    NSString *cat = [NSString stringWithFormat:@"mobi.smartad.flappyjump"];
    gkh->submitScoreToCatagory(g->score, [cat UTF8String]);
}

void Translate::rate(cocos2d::Ref *object) {
    NSURL *url = [NSURL URLWithString:kAppStoreLink];
    [[UIApplication sharedApplication] openURL:url];
}

void Translate::share(cocos2d::Ref *object) {
    Global *g = Global::sharedGlobal();
    NSString *textToShare = [NSString stringWithFormat:@"I scored %.0f points in @flappyjumpbird , can you get higher than me? %@", g->score, kAppStoreLink];
    if (g->score < 2.0) {
        textToShare = [NSString stringWithFormat:@"I scored %.0f point in @flappyjumpbird , can you get higher than me? %@", g->score, kAppStoreLink];
    }
    NSString *filename = [NSHomeDirectory() stringByAppendingFormat:@"/Documents/captured.png"];
    UIImage *imageToShare = [UIImage imageWithData:[NSData dataWithContentsOfFile:filename]];
    NSArray *itemsToShare = @[textToShare, imageToShare];
    UIActivityViewController *activityVC = [[UIActivityViewController alloc] initWithActivityItems:itemsToShare applicationActivities:nil];
    activityVC.excludedActivityTypes = @[UIActivityTypePrint, UIActivityTypeCopyToPasteboard, UIActivityTypeAssignToContact, UIActivityTypeSaveToCameraRoll];
    [[UIApplication sharedApplication].keyWindow.rootViewController presentViewController:activityVC animated:YES completion:nil];
}

void Translate::showadmobfull(Ref *object) {
    NSDate *date1 = [NSDate date];
    NSDateFormatter *dateFormatter = [[[NSDateFormatter alloc] init] autorelease];
    [dateFormatter setDateFormat:@"yyyy-MM-dd HH:mm:ss Z"];
    NSDate *date2 = [dateFormatter dateFromString: @"2014-09-5 00:00:01 GMT-07:00"];
    //if ([date1 compare:date2] == NSOrderedDescending)
    {
        AppController *app = (AppController*)[UIApplication sharedApplication].delegate;
        [app.viewController showAdmobFull];
    }
}

