//
//  Prefix.h
//  EggSeed
//
//  Created by LyGV on 2013/12/11.
//
//
#include "AppDelegate.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Global.h"
#include <iostream>
#include <sstream>
#include <string>
#include "CCConfig.h"

enum GAME_LEVEL {
    LEVEL_NORMAL = 1,
    LEVEL_HARD = 2,
    LEVEL_SUPPERHARD = 3,
    LEVEL_ULTRAHARD = 4
};

#define eggSpeed                2.5

#define ToString(x) dynamic_cast<std::ostringstream&> ((std::ostringstream() << std::dec << x)).str()

#define _X                      Director::getInstance()->getVisibleOrigin().x
#define _Y                      Director::getInstance()->getVisibleOrigin().y
#define _W                      Director::getInstance()->getVisibleSize().width
#define _H                      Director::getInstance()->getVisibleSize().height

//Scale factor
#define scaleFactor             (_W < 640 ? (640.0 / _W) : 1.0)
#define bgrScale                (_W > 640 ? (_W / 640.0) : 1.0)
#define realScale               _W / 640.0
//
#define ratio16d9               _H / _W > 1.5
#define ratio4d3                _H / _W <= 1.5
//Audio
#define audio                   (CocosDenshion::SimpleAudioEngine::getInstance())
//App delegate
#define delegate                ((AppDelegate*)CCApplication::sharedApplication())
//
#define director                (Director::getInstance())
//User default
#define USER_DF                 (UserDefault::getInstance())
//Global
#define global                  Global::sharedGlobal()
//File Utils
#define fileUtils               FileUtils::getInstance()
//Notification Center
#define notify                  __NotificationCenter::getInstance()
//Secue key
#define kBestScore              "vrF6113q51G907Z"
#define kScore_                 "zh6kckMAfGm25zr"
#define kTotalScore_            "1737zR58boc6Z9p"
#define kBestScore1_            "5WVM4SjrPDsUvPW"
#define kBestScore2_            "ZB4r88f8E22h2B1"
#define kBestScore3_            "WKRVa5ozWi1UWJr"
#define kBestScore4_            "48624o3DaVA85u3"
#define kSuperHardUnlocked      "DN38Ujhwv6dKAlt"
#define kUltraHardUnlocked      "v42B97bW5F85o88"
#define kSoundEnabled           "xlLBWPuUJcK8WIL"
#define kGameOverCount          "w359bFX376n2X2d"
//Notification key
#define kNotifyGameOver         "notifygameover"
#define kNotifyShowiAds         "notifyshowiads"
#define kNotifyHideiAds         "notifyhideiads"
#define kNotifyShowiAdsCenter   "notifyshowiadscenter"
#define kNotifyShowiAdsBottom   "notifyshowiadsbottom"
#define kNotifyShareFacebook    "notifysharefacebook"
#define kNotifyFlurryLogEvent   "notifyflurrylogevent"
#define kNotifyGCAuthen         "notifygamecenterauthenuser"
#define kNotifyGCShow           "notifygamecentershowleaderboard"
#define kNotifyGCSubmit         "notifygamecentersubmitscore"
#define kNotificationAdmobShow          "notificationadmobisshow"
#define kNotificationAdmobHide          "notificationadmobishide"
#define kNotificationHideSplash         "notificationhidesplash"
#define kNotificationShowChartBoost     "notificationshowcharboost"
























