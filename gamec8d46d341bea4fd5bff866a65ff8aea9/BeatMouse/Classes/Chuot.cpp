//
//  Chuot.cpp
//  HelloCpp
//
//  Created by LyGV on 2014/02/15.
//
//

#include "Chuot.h"
#include "CCPrefix.h"

USING_NS_CC;
using namespace std;

Chuot* Chuot::sprite()
{
    Sprite* sprite = Chuot::create();
    return (Chuot*)sprite;
}

// on "init" you need to initialize your instance
bool Chuot::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCSprite::init() )
    {
        return false;
    }
    Texture2D *texture = director->getTextureCache()->addImage("images/anim01.png");
    this->setTexture(texture);
    this->setTextureRect(Rect(0, 0, 220/scaleFactor, 160/scaleFactor));
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images/anim01.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images/anim02.plist");

    return true;
}

void Chuot::playAnimationPopup(bool first) {
    this->unscheduleAllSelectors();
    this->stopAllActions();
    isShowing = true;
    hitEnable = true;
    Animation *animation = Animation::create();
    animation->setDelayPerUnit(0.05f);
    const char *animationFramePrefix = "anim01";
    int i = arc4random() % 2;
    isEating = false;
    if (i == 1 || first) {
        animationFramePrefix = "anim02";
        isEating = true;
    }
    const char *animationFrames = "00,01,02,03,04,05,06,07,08,09,10,11,12,13,14,15,00";
    Animate *animationAction = global->createAnimate("images/anim01.plist", animationFrames, animationFramePrefix);
    this->runAction(Sequence::create(animationAction, DelayTime::create(0.2), CallFuncN::create(CC_CALLBACK_1(Chuot::disableHit, this)), DelayTime::create(0), CallFuncN::create(CC_CALLBACK_1(Chuot::popDownEnd, this)), CallFuncN::create(CC_CALLBACK_1(Chuot::setHide, this)),  NULL));
}

void Chuot::popDownEnd(Ref *obj) {
    if (isEating) {
        //notify->postNotification(kNotifyGameOver);
    }
}

void Chuot::enableHit(Ref *obj) {
    hitEnable = true;
}

void Chuot::disableHit(Ref *obj) {
    hitEnable = false;
}

void Chuot::setHide(Ref *obj) {
    isShowing = false;
}

void Chuot::playAnimationHit() {
    hitEnable = false;
    isShowing = true;
    if (isEating) {
        audio->playEffect("sounds/sfx_hit.mp3");
    } else {
        audio->playEffect("sounds/sfx_fail.mp3");
    }
    this->unscheduleAllSelectors();
    this->stopAllActions();
    Animation *animation = Animation::create();
    animation->setDelayPerUnit(0.05f);
    const char * animationFrames = "16,17,18,19,20,21,22,23,24,25,26,27,28,29";
    Animate *animationAction = global->createAnimate("images/anim01.plist", animationFrames, "anim01");
    this->runAction(Sequence::create(animationAction, DelayTime::create(1.0), CallFuncN::create(CC_CALLBACK_1(Chuot::setHide, this)),  NULL));
}





