#include "GameOver.h"
#include "GameConfig.h"
#include "GameLayer.h"
#include "HelloWorldScene.h"
#include "Global.h"

USING_NS_CC;

Scene* GameOver::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameOver::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameOver::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    Sprite* background = Sprite::create("images/background.png");
    addChild(background);
    background->setPosition(Point(_W * 0.5f, _H * 0.5f));
    
    auto *title = Label::createWithTTF("GAME OVER", "fonts/ClearSans-Bold.ttf", 80*realScale);
    title->setColor(Color3B(40,40,40));
    title->setScale(0.5);
    title->setPosition(_W/2, _H/2 + 280*realScale);
    addChild(title);
    //=======================EASY
    LayerColor *leasy = LayerColor::create(getLevelBackground(2), 320*realScale, 240*realScale);
    leasy->setPosition(_W/2 - 160*realScale, _H/2 + 0*realScale);
    addChild(leasy);
    auto *best1 = Label::createWithTTF("SCORE", "fonts/ClearSans-Bold.ttf", 40*realScale);
    best1->setScale(0.5);
    best1->setColor(Color3B(240,240,240));
    best1->setPosition(160*realScale, 200*realScale);
    leasy->addChild(best1);
    const char *scorestr = __String::createWithFormat("%.0f", global->score)->getCString();
    auto *lbl1 = Label::createWithTTF(scorestr, "fonts/ClearSans-Bold.ttf", 120*realScale);
    lbl1->setScale(0.5);
    lbl1->setColor(Color3B(240,240,240));
    lbl1->setPosition(160*realScale, 150*realScale);
    leasy->addChild(lbl1);
    best1 = Label::createWithTTF("BEST", "fonts/ClearSans-Bold.ttf", 40*realScale);
    best1->setScale(0.5);
    best1->setColor(Color3B(240,240,240));
    best1->setPosition(160*realScale, 100*realScale);
    leasy->addChild(best1);
    const char *best = __String::createWithFormat("%.0f", USER_DF->getFloatForKey("best", 0))->getCString();
    lbl1 = Label::createWithTTF(best, "fonts/ClearSans-Bold.ttf", 120*realScale);
    lbl1->setScale(0.5);
    lbl1->setColor(Color3B(240,240,240));
    lbl1->setPosition(160*realScale, 50*realScale);
    leasy->addChild(lbl1);
    Sprite *easy = Sprite::create();
    easy->setTextureRect(Rect(0, 0, 320*realScale, 80*realScale));
    auto *item1 = MenuItemSprite::create(easy, easy, CC_CALLBACK_1(GameOver::reStart, this));
    item1->setTag(2);
    item1->setAnchorPoint(Point(0,0));
    item1->setOpacity(0);
    auto *menu = Menu::createWithItem(item1);
    menu->setPosition(0, 0);
    leasy->addChild(menu);
    //=======================SHARE
    leasy = LayerColor::create(getLevelBackground(3), 320*realScale, 80*realScale);
    leasy->setPosition(_W/2 - 160*realScale, _H/2 - 100*realScale);
    addChild(leasy);
    lbl1 = Label::createWithTTF("SHARE", "fonts/ClearSans-Bold.ttf", 70*realScale);
    lbl1->setScale(0.5);
    lbl1->setColor(Color3B(240,240,240));
    lbl1->setPosition(160*realScale, 40*realScale);
    leasy->addChild(lbl1);
    easy = Sprite::create();
    easy->setTextureRect(Rect(0, 0, 320*realScale, 80*realScale));
    item1 = MenuItemSprite::create(easy, easy, CC_CALLBACK_1(GameOver::share, this));
    item1->setTag(3);
    item1->setAnchorPoint(Point(0,0));
    item1->setOpacity(0);
    menu = Menu::createWithItem(item1);
    menu->setPosition(0, 0);
    leasy->addChild(menu);
    //=======================RESTART
    leasy = LayerColor::create(getLevelBackground(2), 320*realScale, 80*realScale);
    leasy->setPosition(_W/2 - 160*realScale, _H/2 - 200*realScale);
    addChild(leasy);
    lbl1 = Label::createWithTTF("TRY AGAIN", "fonts/ClearSans-Bold.ttf", 70*realScale);
    lbl1->setScale(0.5);
    lbl1->setColor(Color3B(240,240,240));
    lbl1->setPosition(160*realScale, 40*realScale);
    leasy->addChild(lbl1);
    easy = Sprite::create();
    easy->setTextureRect(Rect(0, 0, 320*realScale, 80*realScale));
    item1 = MenuItemSprite::create(easy, easy, CC_CALLBACK_1(GameOver::reStart, this));
    item1->setTag(4);
    item1->setAnchorPoint(Point(0,0));
    item1->setOpacity(0);
    menu = Menu::createWithItem(item1);
    menu->setPosition(0, 0);
    leasy->addChild(menu);
    //=======================GO HOME
    leasy = LayerColor::create(getLevelBackground(4), 320*realScale, 80*realScale);
    leasy->setPosition(_W/2 - 160*realScale, _H/2 - 300*realScale);
    addChild(leasy);
    lbl1 = Label::createWithTTF("BACK HOME", "fonts/ClearSans-Bold.ttf", 70*realScale);
    lbl1->setScale(0.5);
    lbl1->setColor(Color3B(240,240,240));
    lbl1->setPosition(160*realScale, 40*realScale);
    leasy->addChild(lbl1);
    easy = Sprite::create();
    easy->setTextureRect(Rect(0, 0, 320*realScale, 80*realScale));
    item1 = MenuItemSprite::create(easy, easy, CC_CALLBACK_1(GameOver::gohome, this));
    item1->setTag(4);
    item1->setAnchorPoint(Point(0,0));
    item1->setOpacity(0);
    menu = Menu::createWithItem(item1);
    menu->setPosition(0, 0);
    leasy->addChild(menu);
    
    if (rand() % 9 == 0) {
        notify->postNotification("showadmobfull");
    }
    
    return true;
}

void GameOver::share(cocos2d::Ref *object) {
    audio->playEffect("sounds/sfx_wing.caf");
    notify->postNotification("share");
}

void GameOver::reStart(cocos2d::Ref *object) {
    audio->playEffect("sounds/sfx_wing.caf");
    auto scene = GameLayer::scene();
    director->replaceScene(TransitionFade::create(0.5, scene));
}

void GameOver::gohome(cocos2d::Ref *object) {
    audio->playEffect("sounds/sfx_wing.caf");
    auto scene = HelloWorld::createScene();
    director->replaceScene(TransitionFade::create(0.5, scene));
}

Color4B GameOver::getLevelBackground(int level) {
    if(level == 0) return Color4B(250, 110, 105, 255);
    if(level == 1) return Color4B(255, 206, 116, 255);
    if(level == 2) return Color4B(76, 141, 166, 255);
    if(level == 3) return Color4B(151, 209, 122, 255);
    return Color4B(91, 96, 140, 255);
}


