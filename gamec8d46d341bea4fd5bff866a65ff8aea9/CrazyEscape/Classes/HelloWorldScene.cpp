#include "HelloWorldScene.h"
#include "GameConfig.h"
#include "GameScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    LayerColor* background = LayerColor::create(Color4B(240, 240, 240, 255));
    addChild(background);
    
    auto *title = Label::createWithTTF("CRAZY ESCAPE", "fonts/ClearSans-Bold.ttf", 80*realScale);
    title->setColor(Color3B(40,40,40));
    title->setScale(0.5);
    title->setPosition(_W/2, _H/2 + 160*realScale);
    addChild(title);
    //=======================EASY
    LayerColor *leasy = LayerColor::create(getLevelBackground(0), 320*realScale, 80*realScale);
    leasy->setPosition(_W/2 - 160*realScale, _H/2);
    addChild(leasy);
    auto *lbl1 = Label::createWithTTF("START", "fonts/ClearSans-Bold.ttf", 70*realScale);
    lbl1->setColor(Color3B(240,240,240));
    lbl1->setScale(0.5);
    lbl1->setPosition(160*realScale, 55*realScale);
    leasy->addChild(lbl1);
    const char *best = __String::createWithFormat("BEST: %.0f", USER_DF->getFloatForKey("best", 0))->getCString();
    auto *best1 = Label::createWithTTF(best, "fonts/ClearSans-Bold.ttf", 50*realScale);
    best1->setColor(Color3B(240,240,240));
    best1->setScale(0.5);
    best1->setPosition(160*realScale, 22*realScale);
    leasy->addChild(best1);
    Sprite *easy = Sprite::create();
    easy->setTextureRect(Rect(0, 0, 320*realScale, 80*realScale));
    auto *item1 = MenuItemSprite::create(easy, easy, CC_CALLBACK_1(HelloWorld::easy, this));
    item1->setTag(2);
    item1->setAnchorPoint(Point(0,0));
    item1->setOpacity(0);
    auto *menu = Menu::createWithItem(item1);
    menu->setPosition(0, 0);
    leasy->addChild(menu);
    //=======================Leader board
    leasy = LayerColor::create(getLevelBackground(2), 320*realScale, 80*realScale);
    leasy->setPosition(_W/2 - 160*realScale, _H/2 - 100*realScale);
    addChild(leasy);
    lbl1 = Label::createWithTTF("LEADERBOARDS", "fonts/ClearSans-Bold.ttf", 70*realScale);
    lbl1->setColor(Color3B(240,240,240));
    lbl1->setScale(0.5);
    lbl1->setPosition(160*realScale, 40*realScale);
    leasy->addChild(lbl1);
    easy = Sprite::create();
    easy->setTextureRect(Rect(0, 0, 320*realScale, 80*realScale));
    item1 = MenuItemSprite::create(easy, easy, CC_CALLBACK_1(HelloWorld::leaderboard, this));
    item1->setTag(6);
    item1->setAnchorPoint(Point(0,0));
    item1->setOpacity(0);
    menu = Menu::createWithItem(item1);
    menu->setPosition(0, 0);
    leasy->addChild(menu);
    //=======================RATE
    leasy = LayerColor::create(getLevelBackground(4), 320*realScale, 80*realScale);
    leasy->setPosition(_W/2 - 160*realScale, _H/2 - 200*realScale);
    addChild(leasy);
    lbl1 = Label::createWithTTF("RATE", "fonts/ClearSans-Bold.ttf", 70*realScale);
    lbl1->setColor(Color3B(240,240,240));
    lbl1->setScale(0.5);
    lbl1->setPosition(160*realScale, 40*realScale);
    leasy->addChild(lbl1);
    easy = Sprite::create();
    easy->setTextureRect(Rect(0, 0, 320*realScale, 80*realScale));
    item1 = MenuItemSprite::create(easy, easy, CC_CALLBACK_1(HelloWorld::rate, this));
    item1->setTag(7);
    item1->setAnchorPoint(Point(0,0));
    item1->setOpacity(0);
    menu = Menu::createWithItem(item1);
    menu->setPosition(0, 0);
    leasy->addChild(menu);
    
    return true;
}

void HelloWorld::easy(cocos2d::Ref *object) {
    audio->playEffect("sounds/sfx_wing.caf");
    auto scene = GameScene::createScene();
    director->replaceScene(TransitionFade::create(0.5, scene));
}

void HelloWorld::leaderboard(cocos2d::Ref *object) {
    audio->playEffect("sounds/sfx_wing.caf");
    notify->postNotification("notifygamecentershowleaderboard");
}

void HelloWorld::rate(cocos2d::Ref *object) {
    audio->playEffect("sounds/sfx_wing.caf");
    notify->postNotification("rate");
}

Color4B HelloWorld::getLevelBackground(int level) {
    if(level == 0) return Color4B(250, 110, 105, 255);
    if(level == 1) return Color4B(255, 206, 116, 255);
    if(level == 2) return Color4B(76, 141, 166, 255);
    if(level == 3) return Color4B(151, 209, 122, 255);
    return Color4B(91, 96, 140, 255);
}


