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
    CCSprite* sprite = Chuot::create();
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
    
    CCTexture2D *texture = textureCache->addImage("images/anim01.png");
    this->setTexture(texture);
    this->setTextureRect(CCRectMake(0, 0, 220/scaleFactor, 160/scaleFactor));
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("images/anim01.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("images/anim02.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("images/Mouse.plist");

    return true;
}

void Chuot::playAnimationPopup(bool first) {
    this->unscheduleAllSelectors();
    this->stopAllActions();
    isShowing = true;
    hitEnable = true;
    CCAnimation *animation = CCAnimation::create();
    animation->setDelayPerUnit(0.05f);
    string animationFramePrefix = "Mouse";
    int i = arc4random() % 2;
    isEating = false;
    if (i == 1 || first) {
        animationFramePrefix = "Mouse";
        isEating = true;
    }
    string  animationFrames = "00,01,02,03,04,05,06,07,08,09,10,11,12,13,14,15,00";
    char *strArr=new char[animationFrames.size()+1];
    strArr[animationFrames.size()]=0;
    memcpy(strArr,animationFrames.c_str(),animationFrames.size());
    const char* p;
    for (p = strtok(strArr, "," );  p;  p = strtok( NULL, "," ))
    {
        std::string frameName = animationFramePrefix + "_00000" + p + ".png";
        CCSpriteFrame* sprite =  CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName.c_str());
        animation->addSpriteFrame(sprite);
    }
    CCAnimate *animationAction = CCAnimate::create(animation);
    this->runAction(CCSequence::create(animationAction, CCDelayTime::create(0.2), CCCallFunc::create(this, callfunc_selector(Chuot::disableHit)), CCCallFunc::create(this, callfunc_selector(Chuot::popDownEnd)), CCDelayTime::create(0), CCCallFunc::create(this, callfunc_selector(Chuot::setHide)),  NULL));
}

void Chuot::popDownEnd() {
    if (isEating) {
        //notify->postNotification(kNotifyGameOver);
    }
}

void Chuot::enableHit() {
    hitEnable = true;
}

void Chuot::disableHit() {
    hitEnable = false;
}

void Chuot::setHide() {
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
    CCAnimation *animation = CCAnimation::create();
    animation->setDelayPerUnit(0.05f);
    string animationFramePrefix = "Mouse";
    string  animationFrames = "16,17,18,19,20,21,22,23,24,25,26,27,28,29";
    char *strArr=new char[animationFrames.size()+1];
    strArr[animationFrames.size()]=0;
    memcpy(strArr,animationFrames.c_str(),animationFrames.size());
    const char* p;
    for (p = strtok(strArr, "," );  p;  p = strtok( NULL, "," ))
    {
        std::string frameName = animationFramePrefix + "_00000" + p + ".png";
        CCSpriteFrame* sprite =  CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName.c_str());
        animation->addSpriteFrame(sprite);
    }
    CCAnimate *animationAction = CCAnimate::create(animation);
    this->runAction(CCSequence::create(animationAction, CCDelayTime::create(1.0), CCCallFunc::create(this, callfunc_selector(Chuot::setHide)),  NULL));
}





