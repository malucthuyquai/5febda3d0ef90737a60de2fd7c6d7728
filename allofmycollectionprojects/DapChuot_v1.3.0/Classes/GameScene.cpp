#include "GameScene.h"
#include <iostream>
#include <string>
#include "CCPrefix.h"
#include "Chuot.h"

USING_NS_CC;

CCScene* GameScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameScene *layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

GameScene::~GameScene() {
    notify->removeObserver(this, kNotificationAdmobShow);
    notify->removeObserver(this, kNotifyGameOver);
    chuotArray->release();
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    popupFirst = true;
    
    notify->addObserver(this, callfuncO_selector(GameScene::notifyAdmobChange), kNotificationAdmobShow, this);
    notify->addObserver(this, callfuncO_selector(GameScene::gameOver), kNotifyGameOver, this);
    notify->postNotification(kNotifyGCAuthen);
    this->setTouchEnabled(true);
    
    CCSprite *bg = CCSprite::create("images/bg2.png");
    bg->setScale(0.8*bgrScale);
    bg->setPosition(ccp(_W/2, _H/2));
    this->addChild(bg);
    
    CCSprite *bg2 = CCSprite::create("images/bg.png");
    bg2->setScale(0.5*bgrScale);
    bg2->setPosition(ccp(_W/2, _H/2));
    this->addChild(bg2);
    
    float sc = bgrScale>2.0?2.0:bgrScale;
    bar = CCSprite::create("images/bar.png");
    bar->setScale(0.64*bgrScale);
    bar->setScaleY(0.64*sc);
    bar->setPosition(ccp(_W/2, _H - bar->getScaleY()*bar->getContentSize().height/2));
    this->addChild(bar);
    
    CCSprite *scorebg = CCSprite::create("images/scorebg.png");
    scorebg->setScale(0.64*sc);
    scorebg->setPosition(ccp(110/scaleFactor*sc, _H - 90/scaleFactor*sc));
    this->addChild(scorebg);
    
    CCSprite *scorebg2 = CCSprite::create("images/bestscorebg.png");
    scorebg2->setScale(0.64*sc);
    scorebg2->setPosition(ccp(_W - 110/scaleFactor*sc, _H - 90/scaleFactor*sc));
    this->addChild(scorebg2);
    
    std::string fontname = "fonts/Cooper Blk BT Black.ttf";
    if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) {
        fontname = "Cooper Blk BT";
    }
    
    CCLabelTTF *lbl1 = CCLabelTTF::create("Score", fontname.c_str(), 35/scaleFactor*sc, CCSizeZero, kCCTextAlignmentCenter);
    lbl1->setPosition(ccp(120/scaleFactor*sc, _H - 65/scaleFactor*sc));
    lbl1->setColor(ccc3(255, 206, 0));
    this->addChild(lbl1);
    
    CCLabelTTF *lbl2 = CCLabelTTF::create("Best", fontname.c_str(), 35/scaleFactor*sc, CCSizeZero, kCCTextAlignmentCenter);
    lbl2->setPosition(ccp(_W - 110/scaleFactor*sc, _H - 65/scaleFactor*sc));
    lbl2->setColor(ccc3(255, 206, 0));
    this->addChild(lbl2);
    
    scoreLabel = CCLabelTTF::create("0", fontname.c_str(), 35/scaleFactor*sc, CCSizeZero, kCCTextAlignmentCenter);
    scoreLabel->setPosition(ccp(120/scaleFactor*sc, _H - 105/scaleFactor*sc));
    scoreLabel->setColor(ccc3(255, 206, 0));
    this->addChild(scoreLabel);
    
    bestLabel = CCLabelTTF::create("0", fontname.c_str(), 35/scaleFactor*sc, CCSizeZero, kCCTextAlignmentCenter);
    bestLabel->setPosition(ccp(_W - 110/scaleFactor*sc, _H - 105/scaleFactor*sc));
    bestLabel->setColor(ccc3(255, 206, 0));
    this->addChild(bestLabel);
    std::string s = global->decrypt(USER_DF->getStringForKey(kBestScore, "0"));
    bestLabel->setString(s.c_str());
    best = atof(s.c_str());
    
    chuotArray = CCArray::create();
    chuotArray->retain();
    //
    this->addChuot(ccp(_W/2 - 120*realScale, _H/2 + 280*realScale), 0.8);
    this->addChuot(ccp(_W/2 + 120*realScale, _H/2 + 280*realScale), 0.8);
    //
    this->addChuot(ccp(_W/2 - 220*realScale, _H/2 + 190*realScale), 0.85);
    this->addChuot(ccp(_W/2, _H/2 + 190*realScale), 0.85);
    this->addChuot(ccp(_W/2 + 220*realScale, _H/2 + 190*realScale), 0.85);
    //
    this->addChuot(ccp(_W/2 - 130*realScale, _H/2 + 90*realScale), 0.9);
    this->addChuot(ccp(_W/2 + 130*realScale, _H/2 + 90*realScale), 0.9);
    //
    this->addChuot(ccp(_W/2 - 220*realScale, _H/2 + 10*realScale), 0.95);
    this->addChuot(ccp(_W/2, _H/2 - 20/scaleFactor), 0.95);
    this->addChuot(ccp(_W/2 + 220*realScale, _H/2 + 10*realScale), 0.95);
    //
    this->addChuot(ccp(_W/2 - 150*realScale, _H/2 - 120*realScale), 1.0);
    this->addChuot(ccp(_W/2 + 150*realScale, _H/2 - 120*realScale), 1.0);
    
    gameOverlayer = CCLayerColor::create(ccc4(0.0, 0.0, 0.0, 0.5), _W, _H);
    gameOverlayer->setContentSize(CCSizeMake(_W, _H));
    gameOverlayer->setPosition(ccp(0, 0));
    this->addChild(gameOverlayer);
    
    gameOverText = CCSprite::create("images/game_over.png");
    gameOverText->setPosition(ccp(_W/2, _H/2));
    gameOverText->setScale(0.4*bgrScale);
    gameOverText->setVisible(false);
    gameOverlayer->addChild(gameOverText);
    
    game = CCMenuItemImage::create("images/bt_gamecenter.png", "images/bt_gamecenter.png", this, menu_selector(GameScene::menuGameCallback));
    game->setPosition(ccp(-_W/2 + 80/scaleFactor, -_H/2 + 150/scaleFactor));
    game->setVisible(false);
    game->setScale(0.7);
    playitem = CCMenuItemImage::create("images/bt_play.png", "images/bt_play.png", this, menu_selector(GameScene::menuPlayCallback));
    playitem->setPosition(ccp(0, -_H/2 + 150/scaleFactor));
    playitem->setScale(0.7);
    fb = CCMenuItemImage::create("images/bt_facebook.png", "images/bt_facebook.png", this, menu_selector(GameScene::menuShareCallback));
    fb->setPosition(ccp(_W/2 - 80/scaleFactor, -_H/2 + 150/scaleFactor));
    fb->setScale(0.7);
    fb->setVisible(false);
    play = CCMenu::create(game, playitem, fb, NULL);
    gameOverlayer->addChild(play);
    
    scheduleOnce(schedule_selector(GameScene::hideSplash), 0.1);
    
    help = CCSprite::create("images/help.png");
    help->setPosition(ccp(_W/2, _H/2));
    help->setScale(bgrScale);
    this->addChild(help);
    
    return true;
}

void GameScene::hideSplash() {
    notify->postNotification(kNotificationHideSplash);
}

void GameScene::menuGameCallback(cocos2d::CCObject *pSender) {
    global->logEvent("Open Game Center");
    notify->postNotification(kNotifyGCShow);
    audio->playEffect("sounds/sfx_tap.mp3");
    global->showLeaderBoard();
}

void GameScene::menuPlayCallback(cocos2d::CCObject *pSender) {
    help->setVisible(false);
    popupFirst = true;;
    audio->playEffect("sounds/sfx_tap.mp3");
    gameOverred = false;
    inteval = 1.5;
    schedule(schedule_selector(GameScene::increaseLevel), 2.0, -1, 0.0);
    gameOverlayer->setVisible(false);
    score = 0.0;
    scoreLabel->setString(CCString::createWithFormat("%.0f", score)->getCString());
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("images/start.plist");
    CCAnimation *animation = CCAnimation::create();
    animation->setDelayPerUnit(0.05f);
    std::string animationFramePrefix = "start";
    
    std::string  animationFrames = "00,01,02,03,04,05,06,07,08,09,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42";
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
    CCSprite *sprite = CCSprite::create("images/bt_play.png");
    sprite->setPosition(ccp(_W/2, _H/2));
    this->addChild(sprite, 100);
    sprite->setScale(bgrScale);
    sprite->runAction(animationAction);
}

void GameScene::menuShareCallback(cocos2d::CCObject *pSender) {
    this->saveScreenShot();
    notify->postNotification(kNotifyShareFacebook);
    global->logEvent("Share Facebook");
    audio->playEffect("sounds/sfx_tap.mp3");
    std::string path = CCFileUtils::sharedFileUtils()->getWritablePath() + "screenshot.png";
    global->shareFacebook(path);
}

void GameScene::notifyAdmobChange(cocos2d::CCObject *pSender) {
    game->setPosition(ccp(-_W/2 + 80/scaleFactor, -_H/2 + game->getContentSize().height/2 + (global->admobHeight)/scaleFactor));
    playitem->setPosition(ccp(0, -_H/2 + playitem->getContentSize().height/2 + (global->admobHeight)/scaleFactor));
    fb->setPosition(ccp(_W/2 - 80/scaleFactor, -_H/2 + fb->getContentSize().height/2 + (global->admobHeight)/scaleFactor));
}

void GameScene::increaseLevel() {
    inteval -= 0.1;
    if (inteval < 0.3) {
        inteval = 0.3;
        this->unschedule(schedule_selector(GameScene::increaseLevel));
    }
    this->unschedule(schedule_selector(GameScene::popUpChuot));
    schedule(schedule_selector(GameScene::popUpChuot), inteval);
}

void GameScene::addChuot(cocos2d::CCPoint p, float scale) {
    Chuot *sp = Chuot::sprite();
    sp->setPosition(p);
    sp->setScale(bgrScale*scale);
    this->addChild(sp);
    chuotArray->addObject(sp);
}

void GameScene::registerWithTouchDispatcher(){
    director->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool GameScene::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    CCLOG("%s", __FUNCTION__);
    if (gameOverred) {
        return false;
    }
    CCPoint p = pTouch->getLocation();
    CCObject *obj = NULL;
    CCARRAY_FOREACH(chuotArray, obj) {
        Chuot *chuot = (Chuot*)obj;
        float scale = chuot->getScale()/bgrScale;
        scale = chuot->getScale()/scale;
        CCRect r = CCRectMake(chuot->getPosition().x - chuot->getContentSize().width*scale/2, chuot->getPosition().y - chuot->getContentSize().height*scale/2, chuot->getContentSize().width*scale, chuot->getContentSize().height*scale);
        if (r.containsPoint(p)) {
            if (chuot->hitEnable) {
                chuot->playAnimationHit();
                
                CCParticleSystemQuad *emitter = CCParticleSystemQuad::create("images/star.plist");
                emitter->setPosition(chuot->getPosition());
                emitter->setScaleY(0.5);
                emitter->setAutoRemoveOnFinish(true);
                this->addChild(emitter);
                
                if (chuot->isEating) {
                    score = score + 1.0;
                    global->score = score;
                    scoreLabel->setString(CCString::createWithFormat("%.0f", score)->getCString());
                    if (score > best) {
                        best = score;
                        bestLabel->setString(CCString::createWithFormat("%.0f", best)->getCString());
                        USER_DF->setStringForKey(kBestScore, global->encrypt(bestLabel->getString()));
                        USER_DF->flush();
                    }
                } else {
                    //this->gameOver();
                }
                break;
            }
        }
    }
    return true;
}

void GameScene::saveScreenShot() {
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCRenderTexture* texture = CCRenderTexture::create((int)size.width, (int)size.height);
    texture->setPosition(ccp(size.width/2, size.height/2));
    texture->begin();
    CCDirector::sharedDirector()->getRunningScene()->visit();
    texture->end();
    std::string path = CCFileUtils::sharedFileUtils()->getWritablePath() + "screenshot.png";
    CCLOG("%s", path.c_str());
    texture->saveToFile("screenshot.png", kCCImageFormatPNG);
}

void GameScene::gameOver() {
    if(gameOverred) return;
    audio->playEffect("sounds/sfx_over.mp3");
    gameOverred = true;
    this->unschedule(schedule_selector(GameScene::popUpChuot));
    this->unschedule(schedule_selector(GameScene::increaseLevel));
    gameOverText->setVisible(true);
    gameOverlayer->setVisible(true);
    game->setVisible(true);
    fb->setVisible(true);
    notify->postNotification(kNotifyGCSubmit);
    global->submitScore();
}

void GameScene::popUpChuot(float dt) {
    int i = arc4random() % chuotArray->count();
    Chuot *chuot = (Chuot*)chuotArray->objectAtIndex(i);
    while (chuot->isShowing || i == index) {
        i = arc4random() % chuotArray->count();
        chuot = (Chuot*)chuotArray->objectAtIndex(i);
    }
    index = i;
    ((Chuot*)chuotArray->objectAtIndex(index))->playAnimationPopup(popupFirst);
    popupFirst = false;
}


