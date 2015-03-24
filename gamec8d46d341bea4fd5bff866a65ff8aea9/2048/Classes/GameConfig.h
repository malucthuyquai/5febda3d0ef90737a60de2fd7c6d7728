//
//  GameConfig.h
//  TweeJumpCocos2dx
//
//  Created by Carlos Pinan on 13/10/13.
//
//

#ifndef TweeJumpCocos2dx_GameConfig_h
#define TweeJumpCocos2dx_GameConfig_h

#include <ctime>
#include <cstdlib>

#define ToString(x) dynamic_cast<std::ostringstream&> ((std::ostringstream() << std::dec << x)).str()

#define _X                      Director::getInstance()->getVisibleOrigin().x
#define _Y                      Director::getInstance()->getVisibleOrigin().y
#define _W                      Director::getInstance()->getVisibleSize().width
#define _H                      Director::getInstance()->getVisibleSize().height

//Scale factor
#define scaleFactor             (_W < 640 ? (640.0 / _W) : 1.0)
#define bgrScale                (_W > 640 ? (_W / 640.0) : 1.0)
#define realScale               _W / 640.0
#define ratio16d9               _H / _W > 1.5
#define ratio4d3                _H / _W <= 1.5
#define audio                   (CocosDenshion::SimpleAudioEngine::getInstance())
#define delegate                ((AppDelegate*)CCApplication::sharedApplication())
#define director                (Director::getInstance())
#define textureCache            (TextureCache::getInstance())
#define USER_DF                 (UserDefault::getInstance())
#define global                  Global::sharedGlobal()
#define fileUtils               FileUtils::getInstance()
#define notify                  __NotificationCenter::getInstance()

#define RANDOM_SEED() srand((int)time(0))

// #define RESET_DEFAULTS

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 480
#define DISPLAY_STATS true

#define K_NUM_CLOUDS 12
#define K_MIN_PLATFORM_STEP 50
#define K_MAX_PLATFORM_STEP 300
#define K_NUM_PLATFORMS 15
#define K_PLATFORM_TOP_PADDING 0

#define K_MIN_BONUS_STEP 30
#define K_MAX_BONUS_STEP 50

enum {
    kSpriteManager = 0,
    kBird,
    kScoreLabel,
    kCloudsStartTag = 1000,
    kPlatformsStartTag = 2000,
    kBonusStartTag = 3000,
    kPopUpPlayerTag = 10000,
    kPopUpEditBoxTag = 150000
};

enum
{
    kBonus5 = 0,
    kBonus10,
    kBonus50,
    kBonus100,
    kNumBonuses
};

#endif
