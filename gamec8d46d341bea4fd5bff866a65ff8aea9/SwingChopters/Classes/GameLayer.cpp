//
//  GameLayer.cpp
//  TweeJumpCocos2dx
//
//  Created by Carlos Pinan on 13/10/13.
//
//

#include "GameLayer.h"
#include "GameOver.h"
#include "Global.h"
#include "Scopters.h"

#define _SCALE 0.8
#define _BAR_SPEED 5.0
#define _SCOPTER_SPEED 2.0

using namespace cocos2d;

Scene* GameLayer::scene()
{
    Scene* scene = Scene::create();
    GameLayer* gameLayer = new GameLayer();
    gameLayer->autorelease();
    scene->addChild(gameLayer);
    return scene;
}

void GameLayer::onAcceleration(cocos2d::Acceleration* acc, cocos2d::Event* event)
{
    float accel_filter = 0.1f;
    bird_velocity.x = bird_velocity.x * accel_filter + acc->x * (1.0f - accel_filter) * 500.0f;
}

GameLayer::GameLayer()
{
    targets = __Array::create();
    targets->retain();
    
    SpriteFrameCache::getInstance()->addSpriteFrame(SpriteFrame::create("images/xa.png", Rect(0, 0, 408, 33)), "xa.png");
    SpriteFrameCache::getInstance()->addSpriteFrame(SpriteFrame::create("images/bua.png", Rect(0, 0, 63, 96)), "bua.png");
    
    bot1 = Sprite::create("images/botbg.png");
    bot1->setScale(_W/bot1->getContentSize().width);
    bot1->setPosition(_W/2, bot1->getContentSize().height*bot1->getScale()/2-60);
    addChild(bot1, 2);
    bot2 = Sprite::create("images/botbg2.png");
    bot2->setScale(_W/bot2->getContentSize().width);
    bot2->setPosition(_W/2, bot2->getContentSize().height*bot2->getScale()/2-60);
    addChild(bot2, 5);
    
    int x = 20 + rand()%100;
    bar1 = createReba(0);
    bar1->setAnchorPoint(Point(1.0, 0.5));
    bar1->setPosition(x, _H-30);
    addChild(bar1, 3);
    targets->addObject(bar1);
    
    bar2 = createReba(1);
    bar2->setPosition(x + 330, _H-30);
    addChild(bar2, 3);
    targets->addObject(bar2);
    
    scopters = Scopters::createScopters();
    scopters->setPosition(_W/2, 117);
    scopters->setScale(_SCALE);
    addChild(scopters, 4, kBird);
    
    Label* scoreLabel = Label::createWithTTF("0", "fonts/ClearSans-Bold.ttf", 80);
    scoreLabel->setScale(0.5);
    scoreLabel->setColor(Color3B(255, 102, 0));
    addChild(scoreLabel, 5, kScoreLabel);
    scoreLabel->setPosition(Point(160, _H - 50));
    best = USER_DF->getIntegerForKey("best", 0);
    
    //setAccelerometerEnabled(true);
    playing = false;
    direction = 0;
}

void GameLayer::addBar(Ref *obj) {
    Sprite *reba = createReba(0);
    int x = 20 + rand()%100;
    reba->setPosition(x, _H + 100);
    reba->setAnchorPoint(Point(1.0, 0.5));
    addChild(reba, 3);
    targets->addObject(reba);
    MoveTo *m1 = MoveTo::create(_BAR_SPEED/_H*230, Point(reba->getPositionX(), _H - 130));
    CallFuncN *fn1 = CallFuncN::create(CC_CALLBACK_1(GameLayer::addBar, this));
    MoveTo *m2 = MoveTo::create(_BAR_SPEED/_H*(_H - 130 + reba->getContentSize().height), Point(reba->getPositionX(), -reba->getContentSize().height));
    CallFuncN *fn2 = CallFuncN::create(CC_CALLBACK_1(GameLayer::removeBar, this));
    reba->runAction(Sequence::create(m1, fn1, m2, fn2, NULL));
    
    reba = createReba(1);
    reba->setPosition(x + 330, _H + 100);
    addChild(reba, 3);
    targets->addObject(reba);
    m1 = MoveTo::create(_BAR_SPEED/_H*230, Point(reba->getPositionX(), _H - 130));
    m2 = MoveTo::create(_BAR_SPEED/_H*(_H - 130 + reba->getContentSize().height), Point(reba->getPositionX(), -reba->getContentSize().height));
    fn2 = CallFuncN::create(CC_CALLBACK_1(GameLayer::removeBar, this));
    reba->runAction(Sequence::create(m1, m2, fn2, NULL));
}

void GameLayer::removeBar(Ref *obj) {
    Sprite *bar = (Sprite*)obj;
    bar->stopAllActions();
    bar->removeFromParentAndCleanup(true);
}

void GameLayer::startGame() {
    MoveTo *m1 = MoveTo::create(_BAR_SPEED/_H*70, Point(bar1->getPositionX(), _H - 100));
    CallFuncN *fn1 = CallFuncN::create(CC_CALLBACK_1(GameLayer::addBar, this));
    MoveTo *m2 = MoveTo::create(_BAR_SPEED/_H*(_H - 100 + bar1->getContentSize().height), Point(bar1->getPositionX(), -bar1->getContentSize().height));
    CallFuncN *fn2 = CallFuncN::create(CC_CALLBACK_1(GameLayer::removeBar, this));
    bar1->runAction(Sequence::create(m1, fn1, m2, fn2, NULL));
    
    m1 = MoveTo::create(_BAR_SPEED/_H*70, Point(bar2->getPositionX(), _H - 100));
    m2 = MoveTo::create(_BAR_SPEED/_H*(_H - 100 + bar2->getContentSize().height), Point(bar2->getPositionX(), -bar2->getContentSize().height));
    fn2 = CallFuncN::create(CC_CALLBACK_1(GameLayer::removeBar, this));
    bar2->runAction(Sequence::create(m1, m2, fn2, NULL));
    
    m2 = MoveTo::create(_BAR_SPEED/_H*(bot1->getPositionY() + bot1->getContentSize().height), Point(bot1->getPositionX(), -bot1->getContentSize().height));
    fn2 = CallFuncN::create(CC_CALLBACK_1(GameLayer::removeBar, this));
    bot1->runAction(Sequence::create(m2, fn2, NULL));
    
    m2 = MoveTo::create(_BAR_SPEED/_H*(bot2->getPositionY() + bot2->getContentSize().height), Point(bot2->getPositionX(), -bot2->getContentSize().height));
    fn2 = CallFuncN::create(CC_CALLBACK_1(GameLayer::removeBar, this));
    bot2->runAction(Sequence::create(m2, fn2, NULL));
    
    scopters->runAction(RotateTo::create(0.2, 20));
    scheduleUpdate();
}

void GameLayer::update(float dt)
{
    MainLayer::update(dt);
    if (scopters->getPositionX() > 0 && scopters->getPositionY() < _W) {
        if (direction == 0) {
            speed -= 0.6;
            scopters->setPosition(scopters->getPositionX() + 3*speed, scopters->getPositionY());
        } else {
            speed += 0.6;
            scopters->setPosition(scopters->getPositionX() + 3*speed, scopters->getPositionY());
        }
    }
    Ref *obj = NULL;
    CCARRAY_FOREACH(targets, obj) {
        Sprite *sp = (Sprite*)obj;
        Rect r1 = getRectSprite(sp);
        Rect r2 = getRectSprite(scopters);
        if (r1.intersectsRect(r2)) {
            gameOver();
        }
        
    }
}

void GameLayer::gameOver() {
    audio->playEffect("sounds/sfx_wing.caf");
    auto scene = GameOver::createScene();
    director->replaceScene(TransitionFade::create(0.5, scene));
}

void GameLayer::onEnter()
{
    Layer::onEnter();
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
    director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void GameLayer::onExit()
{
    Layer::onExit();
}

bool GameLayer::onTouchBegan(cocos2d::Touch* touch, Event* event)
{
    if (playing == false) {
        startGame();
        playing = true;
    }
    if (direction == 0) {
        scopters->stopActionByTag(1);
        RotateTo *rt = RotateTo::create(0.4, 15);
        rt->setTag(1);
        scopters->runAction(rt);
        direction = 1;
    } else {
        scopters->stopActionByTag(1);
        RotateTo *rt = RotateTo::create(0.4, -15);
        rt->setTag(1);
        scopters->runAction(rt);
        direction = 0;
    }
    return true;
}

void GameLayer::onTouchMoved(cocos2d::Touch* touch, Event* event)
{
    
}

void GameLayer::onTouchEnded(cocos2d::Touch* touch, Event* event)
{
    
}

Sprite* GameLayer::createReba(int dir)
{
    Sprite *reba = Sprite::createWithSpriteFrameName("xa.png");
    reba->setTag(2);
    Sprite *bua = Sprite::createWithSpriteFrameName("bua.png");
    bua->setTag(3);
    bua->setPosition(reba->getContentSize().width - 25, 5);
    bua->setAnchorPoint(Point(0.5, 1.1));
    if (dir == 1) {
        bua->setPosition(25, 5);
    }
    reba->addChild(bua);
    bua->setRotation(20);
    RotateBy *r1 = RotateBy::create(1.0, -40);
    RotateBy *r2 = r1->reverse();
    bua->runAction(RepeatForever::create(Sequence::create(r1, DelayTime::create(0.1), r2, DelayTime::create(0.1), NULL)));
    reba->setScale(_SCALE);
    return reba;
}

Rect GameLayer::getRectSprite(cocos2d::Sprite *sp) {
    Point p = sp->getPosition();
    Size s = sp->getContentSize();
    float sc = sp->getScale();
    if (sp->getAnchorPoint().x < 0.5) {
        if (sp->getAnchorPoint().y < 0.5) {
            return Rect(p.x, p.y, s.width*sc, s.height*sc);
        } else if (sp->getAnchorPoint().y > 0.5) {
            return Rect(p.x, p.y-s.height*sc, s.width*sc, s.height*sc);
        } else {
            return Rect(p.x, p.y-s.height*sc/2, s.width*sc, s.height*sc);
        }
    } else if (sp->getAnchorPoint().x > 0.5) {
        if (sp->getAnchorPoint().y < 0.5) {
            return Rect(p.x-s.width*sc, p.y, s.width*sc, s.height*sc);
        } else if (sp->getAnchorPoint().y > 0.5) {
            return Rect(p.x-s.width*sc, p.y-s.height*sc, s.width*sc, s.height*sc);
        } else {
            return Rect(p.x-s.width, p.y-s.height/2, s.width, s.height);
        }
    } else {
        if (sp->getAnchorPoint().y < 0.5) {
            return Rect(p.x-s.width*sc/2, p.y, s.width*sc, s.height*sc);
        } else if (sp->getAnchorPoint().y > 0.5) {
            return Rect(p.x-s.width*sc/2, p.y-s.height*sc, s.width*sc, s.height*sc);
        } else {
            return Rect(p.x-s.width*sc/2, p.y-s.height*sc/2, s.width*sc, s.height*sc);
        }
    }
}


