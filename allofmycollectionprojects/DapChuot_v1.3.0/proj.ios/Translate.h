#ifndef __TRANSLATE_H__
#define __TRANSLATE_H__

#include "cocos2d.h"


class Translate : public cocos2d::CCNode
{
public:
    virtual bool init();
    virtual ~Translate();
    
    static Translate *sharedTranslate();
    
    void showiAds(cocos2d::CCObject *object);
    void showiAdsAtCenter(cocos2d::CCObject *object);
    void showiAdsAtBottom(cocos2d::CCObject *object);
    void hideiAds(cocos2d::CCObject *object);
    void notificationAdmobShow();
    void notificationAdmobHide();
    void notificationHideSplash();
    
    //Facebook
    void shareFacebook(cocos2d::CCObject *object);
    //Flurry
    void flurryLogEvent(cocos2d::CCObject *object);
    //Chartboot
    void showCharboot(cocos2d::CCObject *object);
    
    //Game center
    void authenLocalGCUser(cocos2d::CCObject *object);
    void showLeaderBoard(cocos2d::CCObject *object);
    void submitGCScore(cocos2d::CCObject *object);
    
    CREATE_FUNC(Translate);
};


#endif /* defined(__EggSeed__Translate__) */
