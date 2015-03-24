#ifndef __TRANSLATE_H__
#define __TRANSLATE_H__

#include "cocos2d.h"


class Translate : public cocos2d::Node
{
public:
    virtual bool init();
    virtual ~Translate();
    
    static Translate *sharedTranslate();
    
    void showiAds(cocos2d::Ref *object);
    void showiAdsAtCenter(cocos2d::Ref *object);
    void showiAdsAtBottom(cocos2d::Ref *object);
    void hideiAds(cocos2d::Ref *object);
    void notificationAdmobShow();
    void notificationAdmobHide();
    
    //Game center
    void authenLocalGCUser(cocos2d::Ref *object);
    void showLeaderBoard(cocos2d::Ref *object);
    void submitGCScore(cocos2d::Ref *object);
    void rate(cocos2d::Ref *object);
    void share(cocos2d::Ref *object);
    void showadmobfull(cocos2d::Ref *object);

    
    CREATE_FUNC(Translate);
};


#endif /* defined(__EggSeed__Translate__) */
