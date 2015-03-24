//
//  Scopters.cpp
//  FlappyJump
//
//  Created by LyGV on 8/22/14.
//
//

#include "Scopters.h"
USING_NS_CC;

// on "init" you need to initialize your instance
Scopters* Scopters::createScopters()
{
    Scopters *scop = (Scopters*)Sprite::create("images/cop.png");
    
    for (int i=1; i<=4; i++) {
        
    }
    
    Animation *animation = Animation::create();
    animation->setDelayPerUnit(0.05f);
    for (int i=1; i<=4; i++) {
        const char *name = __String::createWithFormat("images/fan%d.png", i)->getCString();
        Sprite *sp = Sprite::create(name);
        animation->addSpriteFrame(sp->getSpriteFrame());
    }
    for (int i=3; i>=2; i--) {
        const char *name = __String::createWithFormat("images/fan%d.png", i)->getCString();
        Sprite *sp = Sprite::create(name);
        animation->addSpriteFrame(sp->getSpriteFrame());
    }
    Animate *animationAction = Animate::create(animation);
    Sprite *fan = Sprite::create();
    fan->runAction(RepeatForever::create(animationAction));
    fan->setPosition(scop->getContentSize().width/2, scop->getContentSize().height + 10);
    scop->addChild(fan);
    
    return scop;
}