#include "GameScene.h"
#include <iostream>
#include "CCPrefix.h"

#define kBgSpeed 5
#define kBgPosistionY 200/scaleFactor

USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("anim/klnau.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("anim/klnau2.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("anim/klnau3.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("anim/kltim.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("anim/kltim2.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("anim/kltim3.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("anim/klxanh.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("anim/klxanh2.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("anim/klxanh3.plist");
    audio->preloadBackgroundMusic("sounds/bgm.mp3");
    audio->preloadEffect("sounds/hita.mp3");
    audio->preloadEffect("sounds/hitb.mp3");
    audio->preloadEffect("sounds/hitc.mp3");
    audio->preloadEffect("sounds/over.mp3");
    audio->preloadEffect("sounds/wrong.mp3");
    
    //audio->playBackgroundMusic("sounds/bgm.mp3", true);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    //Point origin = Director::getInstance()->getVisibleOrigin();
    
    Sprite *bg = Sprite::create("images/background.png");
    bg->setPosition(0, 0);
    bg->setScale(2);
    bg->setAnchorPoint(Point(0, 0));
    addChild(bg, 0, 0);
    
    clouds = __Array::create();
    clouds->retain();
    khunglong = __Array::create();
    khunglong->retain();
    
    for (int i=0; i<6; i++) {
        Sprite *cloud1 = Sprite::create("images/cloud.png");
        cloud1->setPosition(30/scaleFactor+arc4random()%(int)visibleSize.width-60/scaleFactor, visibleSize.height-arc4random()%400/scaleFactor + 30/scaleFactor);
        cloud1->setAnchorPoint(Point(0, 0));
        addChild(cloud1, 1, 0);
        clouds->addObject(cloud1);
        cloud1->runAction(Sequence::create(MoveTo::create(kBgSpeed*2*bgrScale*(visibleSize.width-cloud1->getPositionX())/visibleSize.width, Point(visibleSize.width, cloud1->getPositionY())), CallFuncN::create(CC_CALLBACK_1(GameScene::backgroundMoveEnd, this)), NULL));
    }
    
    Sprite *bg1 = Sprite::create("images/background01.png");
    bg1->setPosition(0, kBgPosistionY);
    bg1->setAnchorPoint(Point(0, 0));
    addChild(bg1, 2, 1);
    bg1->runAction(Sequence::create(MoveTo::create(kBgSpeed, Point(bg1->getContentSize().width, kBgPosistionY)), CallFuncN::create(CC_CALLBACK_1(GameScene::backgroundMoveEnd, this)), NULL));
    Sprite *bg2 = Sprite::create("images/background02.png");
    bg2->setPosition(-bg2->getContentSize().width, kBgPosistionY);
    bg2->setAnchorPoint(Point(0, 0));
    addChild(bg2, 2, 2);
    bg2->runAction(Sequence::create(MoveTo::create(kBgSpeed*2, Point(bg2->getContentSize().width, kBgPosistionY)), CallFuncN::create(CC_CALLBACK_1(GameScene::backgroundMoveEnd, this)), NULL));
    
    const char *frames = "00,01,02,03,04,05,06,07";
    Animate *anim = Global::sharedGlobal()->createAnimate("anim/khunglong.plist", frames, "khunglong");
    kldich = Sprite::create();
    int x = visibleSize.width - 590/scaleFactor;
    if(visibleSize.width/2 > 590/scaleFactor) x = visibleSize.width/2;
    kldich->setPosition(x, 360/scaleFactor);
    kldich->setAnchorPoint(Point(0, 0));
    addChild(kldich, 3);
    kldich->runAction(RepeatForever::create(anim));
    
    Sprite *bar = Sprite::create("images/bar.png");
    bar->setPosition(visibleSize.width/2, 0);
    bar->setAnchorPoint(Point(0.5, 0));
    bar->setScale(1.2);
    addChild(bar, 4, 0);
    
    Sprite *bom1 = Sprite::create("images/bom.png");
    Sprite *bom2 = Sprite::create("images/bom.png");
    bom2->setScale(0.9);
    bom2->setPosition(8/scaleFactor, 8/scaleFactor);
    MenuItemSprite *bom = MenuItemSprite::create(bom1, bom2, CC_CALLBACK_1(GameScene::bom, this));
    bom->setPosition(bar->getContentSize().width/2-100/scaleFactor, 80/scaleFactor);
    bom->setScale(0.7);
    Sprite *gun1 = Sprite::create("images/gun.png");
    Sprite *gun2 = Sprite::create("images/gun.png");
    gun2->setScale(0.9);
    gun2->setPosition(8/scaleFactor, 8/scaleFactor);
    MenuItemSprite *gun = MenuItemSprite::create(gun1, gun2, CC_CALLBACK_1(GameScene::shut, this));
    gun->setPosition(bar->getContentSize().width/2-5/scaleFactor, 80/scaleFactor);
    gun->setScale(0.7);
    Sprite *riu1 = Sprite::create("images/riu.png");
    Sprite *riu2 = Sprite::create("images/riu.png");
    riu2->setScale(0.9);
    riu2->setPosition(8/scaleFactor, 8/scaleFactor);
    MenuItemSprite *riu = MenuItemSprite::create(riu1, riu2, CC_CALLBACK_1(GameScene::chem, this));
    riu->setPosition(bar->getContentSize().width/2+90/scaleFactor, 80/scaleFactor);
    riu->setScale(0.7);
    Menu *menu = Menu::create(bom, gun, riu, NULL);
    menu->setPosition(0, 0);
    menu->setAnchorPoint(Point(0, 0));
    bar->addChild(menu);
    
    Sprite *scorebg = Sprite::create("images/score.png");
    scorebg->setScale(0.5*bgrScale);
    scorebg->setPosition(0, visibleSize.height - 160/scaleFactor);
    scorebg->setAnchorPoint(Point(0, 1.0));
    addChild(scorebg, 4);
    lblscore = Label::createWithTTF("0", "fonts/VNI-Vari.TTF", 40/scaleFactor, Size(200/scaleFactor, 20/scaleFactor), TextHAlignment::RIGHT, TextVAlignment::CENTER);
    lblscore->setColor(Color3B(247, 28, 93));
    lblscore->setPosition(70/scaleFactor, 55/scaleFactor);
    lblscore->setAnchorPoint(Point(0, 0));
    scorebg->addChild(lblscore);
    Sprite *bestbg = Sprite::create("images/best.png");
    bestbg->setScale(0.5*bgrScale);
    bestbg->setPosition(visibleSize.width, visibleSize.height - 160/scaleFactor);
    bestbg->setAnchorPoint(Point(1.0, 1.0));
    addChild(bestbg, 4);
    best = UserDefault::getInstance()->getFloatForKey("BEST", 0.0);
    const char *str = __String::createWithFormat("%.0f", best)->getCString();
    lblbest = Label::createWithTTF(str, "fonts/VNI-Vari.TTF", 40/scaleFactor, Size(200/scaleFactor, 20/scaleFactor), TextHAlignment::RIGHT, TextVAlignment::CENTER);
    lblbest->setColor(Color3B(247, 28, 93));
    lblbest->setPosition(70/scaleFactor, 55/scaleFactor);
    lblbest->setAnchorPoint(Point(0, 0));
    bestbg->addChild(lblbest);
    
    gameover = Sprite::create("images/gameover.png");
    gameover->setPosition(visibleSize.width + 400, visibleSize.height/2);
    addChild(gameover, 4, 0);
    lblscore2 = Label::createWithTTF("0", "fonts/VNI-Vari.TTF", 50/scaleFactor, Size(200/scaleFactor, 20/scaleFactor), TextHAlignment::RIGHT, TextVAlignment::CENTER);
    lblscore2->setColor(Color3B(247, 28, 93));
    lblscore2->setPosition(190/scaleFactor, 95/scaleFactor);
    lblscore2->setAnchorPoint(Point(0, 0));
    gameover->addChild(lblscore2);
    
    Sprite *start1 = Sprite::create("images/start.png");
    Sprite *start2 = Sprite::create("images/start.png");
    start2->setPosition(3, 3);
    start2->setScale(0.95);
    MenuItemSprite *start = MenuItemSprite::create(start1, start2, CC_CALLBACK_1(GameScene::start, this));
    Menu *menu2 = Menu::create(start, NULL);
    menu2->setPosition(gameover->getContentSize().width/2, -60/scaleFactor);
    gameover->addChild(menu2);
    
    help = Sprite::create("images/instruction.png");
    help->setPosition(visibleSize.width/2, visibleSize.height/2);
    addChild(help, 4, 0);
    
    start1 = Sprite::create("images/start.png");
    start2 = Sprite::create("images/start.png");
    start2->setPosition(3, 3);
    start2->setScale(0.95);
    start = MenuItemSprite::create(start1, start2, CC_CALLBACK_1(GameScene::start, this));
    menu2 = Menu::create(start, NULL);
    menu2->setPosition(help->getContentSize().width/2, -60/scaleFactor);
    help->addChild(menu2);
    
    interval = 2.0;
    duration = 10;
    score = 0.1;
    //schedule(schedule_selector(GameScene::addKhungLong), interval);
    //schedule(schedule_selector(GameScene::increaseLevel), 3.0, -1, 0.0);
    //schedule(schedule_selector(GameScene::checkOver));
    isGameOver = false;
    
    return true;
}

void GameScene::monsterDie(Ref *obj, Sprite *monster) {
    monster->removeFromParentAndCleanup(true);
}

void GameScene::start(Ref *object) {
    Size size = Director::getInstance()->getVisibleSize();
    gameover->setPositionX(size.width + 400);
    kldich->setVisible(true);
    
    MoveTo *move = MoveTo::create(0.5, Point(size.width + 400, size.height/2));
    EaseInOut *ease = EaseInOut::create(move, 5.0);
    help->runAction(ease);
    
    Ref *obj = NULL;
    CCARRAY_FOREACH(khunglong, obj) {
        Sprite *kl = dynamic_cast<Sprite*>(obj);
        kl->removeFromParentAndCleanup(true);
    }
    khunglong->removeAllObjects();
    lblscore->setString("0");
    lblscore2->setString("0");
    
    interval = 2.0;
    duration = 10;
    score = 0.1;
    schedule(schedule_selector(GameScene::addKhungLong), interval);
    schedule(schedule_selector(GameScene::increaseLevel), 3.0, -1, 0.0);
    schedule(schedule_selector(GameScene::checkOver));
    isGameOver = false;
}

void GameScene::bom(Ref *obj) {
    if(isGameOver) return;
    if (khunglong->count() > 0) {
        Sprite *kl = dynamic_cast<Sprite*>(khunglong->getObjectAtIndex(0));
        if (kl->getTag() == 2) {
            const char *name = "klxanh3";
            const char *plist = __String::createWithFormat("anim/%s.plist", name)->getCString();
            const char *frames = "00,01,02,03,04,05,06,07,08";
            Animate *anim = Global::sharedGlobal()->createAnimate(plist, frames, name);
            kl->stopAllActions();
            kl->runAction(Sequence::create(anim, CallFuncN::create(CC_CALLBACK_1(GameScene::monsterDie, this, kl)), NULL));
            kl->setPositionX(kl->getPositionX() - 20);
            khunglong->removeObjectAtIndex(0);
            score = score + 1.0;
            lblscore->setString(__String::createWithFormat("%.0f", score)->getCString());
            lblscore2->setString(__String::createWithFormat("%.0f", score)->getCString());
            if (score > best) {
                best = score;
                lblbest->setString(__String::createWithFormat("%.0f", score)->getCString());
                UserDefault::getInstance()->setFloatForKey("BEST", best);
                UserDefault::getInstance()->flush();
            }
            audio->playEffect("sounds/hita.mp3");
        } else {
            audio->playEffect("sounds/wrong.mp3");
        }
    }
}

void GameScene::shut(Ref *obj) {
    if(isGameOver) return;
    if (khunglong->count() > 0) {
        Sprite *kl = dynamic_cast<Sprite*>(khunglong->getObjectAtIndex(0));
        if (kl->getTag() == 1) {
            const char *name = "kltim3";
            const char *plist = __String::createWithFormat("anim/%s.plist", name)->getCString();
            const char *frames = "00,01,02,03,04,05,06,07,08";
            Animate *anim = Global::sharedGlobal()->createAnimate(plist, frames, name);
            kl->stopAllActions();
            kl->runAction(Sequence::create(anim, CallFuncN::create(CC_CALLBACK_1(GameScene::monsterDie, this, kl)), NULL));
            kl->setPositionX(kl->getPositionX() - 100);
            khunglong->removeObjectAtIndex(0);
            score = score + 1.0;
            lblscore->setString(__String::createWithFormat("%.0f", score)->getCString());
            lblscore2->setString(__String::createWithFormat("%.0f", score)->getCString());
            if (score > best) {
                best = score;
                lblbest->setString(__String::createWithFormat("%.0f", score)->getCString());
                UserDefault::getInstance()->setFloatForKey("BEST", best);
                UserDefault::getInstance()->flush();
            }
            audio->playEffect("sounds/jump.mp3");
        } else {
            audio->playEffect("sounds/wrong.mp3");
        }
    }
}

void GameScene::chem(Ref *obj) {
    if(isGameOver) return;
    if (khunglong->count() > 0) {
        Sprite *kl = dynamic_cast<Sprite*>(khunglong->getObjectAtIndex(0));
        if (kl->getTag() == 0) {
            const char *name = "klnau3";
            const char *plist = __String::createWithFormat("anim/%s.plist", name)->getCString();
            const char *frames = "00,01,02,03,04,05,06,07";
            Animate *anim = Global::sharedGlobal()->createAnimate(plist, frames, name);
            kl->stopAllActions();
            kl->runAction(Sequence::create(anim, CallFuncN::create(CC_CALLBACK_1(GameScene::monsterDie, this, kl)), NULL));
            kl->setPositionX(kl->getPositionX() - 80);
            kl->setPositionY(kl->getPositionY() + 30);
            khunglong->removeObjectAtIndex(0);
            score = score + 1.0;
            lblscore->setString(__String::createWithFormat("%.0f", score)->getCString());
            lblscore2->setString(__String::createWithFormat("%.0f", score)->getCString());
            if (score > best) {
                best = score;
                lblbest->setString(__String::createWithFormat("%.0f", score)->getCString());
                UserDefault::getInstance()->setFloatForKey("BEST", best);
                UserDefault::getInstance()->flush();
            }
            audio->playEffect("sounds/hitc.mp3");
        } else {
            audio->playEffect("sounds/wrong.mp3");
        }
    }
}

void GameScene::checkOver(float dt) {
    Ref *obj = NULL;
    Rect r2 = Rect(kldich->getPositionX(), kldich->getPositionY(), 55, 75);
    CCARRAY_FOREACH(khunglong, obj) {
        Sprite *kl = dynamic_cast<Sprite*>(obj);
        Rect r = Rect(kl->getPositionX(), kl->getPositionY(), 80, 95);
        int t = kl->getTag();
        if(t == 1) r = Rect(kl->getPositionX(), kl->getPositionY(), 50, 70);
        if(t == 2) r = Rect(kl->getPositionX(), kl->getPositionY(), 85, 100);
        if (r2.intersectsRect(r)) {
            gameOver(kl);
            break;
        }
    }
}

void GameScene::gameOver(Sprite *monster) {
    isGameOver = true;
    Size size = Director::getInstance()->getVisibleSize();
    unschedule(schedule_selector(GameScene::checkOver));
    unschedule(schedule_selector(GameScene::addKhungLong));
    unschedule(schedule_selector(GameScene::increaseLevel));
    Ref *obj = NULL;
    CCARRAY_FOREACH(khunglong, obj) {
        Sprite *kl = dynamic_cast<Sprite*>(obj);
        kl->stopActionByTag(2);
    }
    const char *name = "";
    int r = monster->getTag();
    if(r == 0) name = "klnau2";
    if(r == 1) name = "kltim2";
    if(r == 2) name = "klxanh2";
    const char *plist = __String::createWithFormat("anim/%s.plist", name)->getCString();
    const char *frames = "00,01,02,03,04,05,06,07";
    Animate *anim = Global::sharedGlobal()->createAnimate(plist, frames, name);
    monster->stopAllActions();
    monster->runAction(RepeatForever::create(anim));
    
    kldich->setVisible(false);
    
    MoveTo *move = MoveTo::create(0.5, Point(size.width/2, size.height/2));
    EaseInOut *ease = EaseInOut::create(move, 5.0);
    gameover->runAction(ease);
    
    audio->playEffect("sounds/over.mp3");
}

void GameScene::increaseLevel(float dt) {
    interval -= 0.1;
    duration -= 0.5;
    if (interval < 0.5) {
        interval = 0.5;
        this->unschedule(schedule_selector(GameScene::increaseLevel));
    }
    schedule(schedule_selector(GameScene::addKhungLong), interval);
}

void GameScene::addKhungLong(float dt) {
    if(isGameOver) return;
    if(interval <= 1.0) {
        if(arc4random()%3==0) {
            schedule(schedule_selector(GameScene::addKhungLong), arc4random()%3);
            return;
        }
    }
    schedule(schedule_selector(GameScene::addKhungLong), interval);
    Size size = Director::getInstance()->getVisibleSize();
    const char *frames = "00,01,02,03,04,05,06,07";
    const char *name = "";
    int r = arc4random()%3;
    if(r == 0) name = "klnau";
    if(r == 1) name = "kltim";
    if(r == 2) name = "klxanh";
    const char *plist = __String::createWithFormat("anim/%s.plist", name)->getCString();
    Animate *anim = Global::sharedGlobal()->createAnimate(plist, frames, name);
    Sprite *monster = Sprite::create();
    monster->setTag(r);
    monster->setPosition(size.width, 360/scaleFactor);
    monster->setAnchorPoint(Point(0, 0));
    addChild(monster, 3);
    monster->runAction(RepeatForever::create(anim));
    MoveTo *move = CCMoveTo::create(duration, Point(-200, 360/scaleFactor));
    move->setTag(2);
    monster->runAction(move);
    khunglong->addObject(monster);
}

void GameScene::backgroundMoveEnd(cocos2d::Ref *pSender) {
    Sprite *bg1 = (Sprite*)getChildByTag(1);
    Sprite *bg2 = (Sprite*)getChildByTag(2);
    if (bg1->getPositionX() >= bg1->getContentSize().width) {
        bg1->setPositionX(50-bg1->getContentSize().width);
        bg1->runAction(Sequence::create(MoveTo::create(kBgSpeed*2, Point(bg1->getContentSize().width, kBgPosistionY)), CallFuncN::create(CC_CALLBACK_1(GameScene::backgroundMoveEnd, this)), NULL));
    } else if (bg2->getPositionX() >= bg2->getContentSize().width) {
        bg2->setPositionX(50-bg2->getContentSize().width);
        bg2->runAction(Sequence::create(MoveTo::create(kBgSpeed*2, Point(bg2->getContentSize().width, kBgPosistionY)), CallFuncN::create(CC_CALLBACK_1(GameScene::backgroundMoveEnd, this)), NULL));
    }
    Ref *obj = NULL;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    CCARRAY_FOREACH(clouds, obj) {
        Sprite *cloud1 = dynamic_cast<Sprite*>(obj);
        if(cloud1->getPositionX()>=visibleSize.width) {
            cloud1->setPositionX(-cloud1->getContentSize().width);
            cloud1->runAction(Sequence::create(MoveTo::create(kBgSpeed*2*bgrScale, Point(visibleSize.width, cloud1->getPositionY())), CallFuncN::create(CC_CALLBACK_1(GameScene::backgroundMoveEnd, this)), NULL));
        }
    }
}
