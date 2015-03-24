#include "GameScene.h"
#include "CCPrefix.h"
#include "GameOver.h"

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
    targets = __Array::create();
    targets->retain();
    players = __Array::create();
    players->retain();
    layers = __Array::create();
    layers->retain();
    bottom = 100;
    if (global->isIpad && _H > 1024) {
        bottom = 200;
    }
    int h = _H - bottom;
    score = 0.012345;
    global->score = score;
    level = global->level;
    if(level < 2) level = 2;
    if(level > 5) level = 5;
    const char *bestkey = __String::createWithFormat("best%d", level)->getCString();
    best = USER_DF->getFloatForKey(bestkey, 0.0123);
    
    //LayerColor *layer = LayerColor::create(Color4B(40, 40, 40, 255), _W, _H);
    //addChild(layer);
    
    lbScore = Label::createWithTTF("0", "fonts/ClearSans-Bold.ttf", 65*realScale);
    lbScore->setColor(Color3B(40,40,40));
    lbScore->setPosition(_W/2, _H - 50*realScale);
    addChild(lbScore, 8);
    
    for (int i=0; i<level; i++) {
        LayerColor *layer = LayerColor::create(getLevelBackground(i), _W, h/level);
        layer->setPosition(Point(0, bottom + h/level*i));
        layers->addObject(layer);
        addChild(layer, 5 - i, i + 1);
        
        Sprite *sprite = Sprite::create();
        layer->addChild(sprite, 1, i + 1);
        players->addObject(sprite);
        sprite->setTag(i + 1);
        sprite->setScale(0.4*realScale);
        sprite->setAnchorPoint(Point(0, 0));
        sprite->setPosition(10, 0);
        const char *frame = "00,01,02,03,04,05,06,07,08";
        Animate *anim = global->createAnimate("anims/jump.plist", frame, "jump");
        sprite->runAction(RepeatForever::create(anim));
        if (i == 0) {
            schedule(schedule_selector(GameScene::addTarget1), 1, -1, 1.0 + rand()%4/10.0);
        }
        if (i == 1) {
            schedule(schedule_selector(GameScene::addTarget2), 1, -1, 1.0 + rand()%4/10.0);
        }
        if (i == 2) {
            schedule(schedule_selector(GameScene::addTarget3), 1, -1, 1.0 + rand()%4/10.0);
        }
        if (i == 3) {
            schedule(schedule_selector(GameScene::addTarget4), 1, -1, 1.0 + rand()%4/10.0);
        }
        if (i == 4) {
            schedule(schedule_selector(GameScene::addTarget5), 1, -1, 1.0 + rand()%4/10.0);
        }
    }
    schedule(schedule_selector(GameScene::checkCollision));
    
    return true;
}

void GameScene::checkCollision(float dt) {
    Ref *obj = NULL;
    CCARRAY_FOREACH(players, obj) {
        Sprite *player = (Sprite*)obj;
        Point p1 = player->getPosition();
        Size s1 = player->getContentSize();
        Ref *obj2 = NULL;
        CCARRAY_FOREACH(targets, obj2) {
            Sprite *target = (Sprite*)obj2;
            if (player->getTag() == target->getTag()) {
                Point p2 = target->getPosition();
                Size s2 = target->getContentSize();
                Rect r1 = Rect(p1.x, p1.y, s1.width*player->getScale() - 35*realScale, s1.height*player->getScale());
                Rect r2 = Rect(p2.x, p2.y, s2.width*target->getScale() - 35*realScale, s2.height*target->getScale() - 10*realScale);
                if (r2.origin.x + r2.size.width < r1.origin.x) {
                    score = score + 1.0;
                    global->score = score;
                    if (score > best) {
                        best = score;
                        const char *bestkey = __String::createWithFormat("best%d", level)->getCString();
                        USER_DF->setFloatForKey(bestkey, best);
                        USER_DF->flush();
                    }
                    lbScore->setString(__String::createWithFormat("%.0f", score)->getCString());
                    target->setTag(0);
                    audio->playEffect("sounds/score.wav");
                }
                if (r1.intersectsRect(r2)) {
                    gameOver();
                    unscheduleAllSelectors();
                    return;
                }
            }
        }
    }
}

void GameScene::gameOver() {
    Ref *obj = NULL;
    CCARRAY_FOREACH(players, obj) {
        Sprite *player = (Sprite*)obj;
        player->stopAllActions();
    }
    Ref *obj2 = NULL;
    CCARRAY_FOREACH(targets, obj2) {
        Sprite *target = (Sprite*)obj2;
        target->stopAllActions();
    }
    director->getEventDispatcher()->removeAllEventListeners();
    runAction(Sequence::create(DelayTime::create(2.0), CallFuncN::create(CC_CALLBACK_1(GameScene::showOverScene, this)), NULL));
    notify->postNotification("notifygamecentersubmitscore");
    utils::captureScreen(NULL, "captured.png");
}

void GameScene::showOverScene(Ref *dt) {
    auto scene = GameOver::createScene();
    director->replaceScene(TransitionFade::create(0.5, scene));
}

void GameScene::moveDone(cocos2d::Ref *obj) {
    Sprite *target = (Sprite*)obj;
    target->removeFromParentAndCleanup(true);
}

void GameScene::addTarget(int level_) {
    LayerColor *layer = (LayerColor*)layers->getObjectAtIndex(level_);
    Sprite *sprite = Sprite::create();
    sprite->setColor(Color3B::BLACK);
    sprite->setPosition(_W, 0);
    sprite->setAnchorPoint(Point(0, 0));
    int w = (rand() % 25 + 25)*realScale;
    int h = (rand() % 30 + 30)*realScale;
    sprite->setTextureRect(Rect(0, 0, w, h));
    layer->addChild(sprite, 1, level_ + 1);
    targets->addObject(sprite);
    sprite->runAction(Sequence::create(MoveTo::create(1.2, Point(-w, sprite->getPositionY())), CallFuncN::create(CC_CALLBACK_1(GameScene::moveDone, this)), NULL));
}

void GameScene::addTarget1(float dt) {
    addTarget(0);
    unschedule(schedule_selector(GameScene::addTarget1));
    schedule(schedule_selector(GameScene::addTarget1), 1, -1, 0.68 + rand()%80/100.0);
}

void GameScene::addTarget2(float dt) {
    addTarget(1);
    unschedule(schedule_selector(GameScene::addTarget2));
    schedule(schedule_selector(GameScene::addTarget2), 1, -1, 0.68 + rand()%80/100.0);
}

void GameScene::addTarget3(float dt) {
    addTarget(2);
    unschedule(schedule_selector(GameScene::addTarget3));
    schedule(schedule_selector(GameScene::addTarget3), 1, -1, 0.68 + rand()%80/100.0);
}

void GameScene::addTarget4(float dt) {
    addTarget(3);
    unschedule(schedule_selector(GameScene::addTarget4));
    schedule(schedule_selector(GameScene::addTarget4), 1, -1, 0.68 + rand()%80/100.0);
}

void GameScene::addTarget5(float dt) {
    addTarget(4);
    unschedule(schedule_selector(GameScene::addTarget5));
    schedule(schedule_selector(GameScene::addTarget5), 1, -1, 0.68 + rand()%80/100.0);
}


Color4B GameScene::getLevelBackground(int level) {
    if(level == 0) return Color4B(250, 110, 105, 255);
    if(level == 1) return Color4B(255, 206, 116, 255);
    if(level == 2) return Color4B(76, 141, 166, 255);
    if(level == 3) return Color4B(151, 209, 122, 255);
    return Color4B(91, 96, 140, 255);
}

void GameScene::onEnter()
{
    Layer::onEnter();
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(GameScene::onTouchesBegan, this);
    //listener->onTouchesMoved = CC_CALLBACK_2(GameScene::onTouchesMoved, this);
    //listener->onTouchesEnded = CC_CALLBACK_2(GameScene::onTouchesEnded, this);
    director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void GameScene::onExit()
{
    Layer::onExit();
}

void GameScene::onTouchesBegan(const std::vector<Touch*> &touches, Event* event)
{
    for(auto touch : touches) {
        Point point = touch->getLocation();
        Ref *obj = NULL;
        CCARRAY_FOREACH(layers, obj) {
            LayerColor *layer = (LayerColor*)obj;
            Point p = layer->getPosition();
            Size s = layer->getContentSize();
            Rect r = Rect(p.x, p.y, s.width, s.height);
            if (r.containsPoint(point)) {
                Ref *obj2 = NULL;
                CCARRAY_FOREACH(players, obj2) {
                    Sprite *player = (Sprite*)obj2;
                    if (player->getTag() == layer->getTag() && player->getPositionY() < 5) {
                        audio->playEffect("sounds/up.wav");
                        auto m1 = MoveBy::create(0.25, Vec2(0, 120*realScale));
                        auto m2 = MoveBy::create(0.35, Vec2(0, -120*realScale));
                        player->runAction(Sequence::create(m1, m2, NULL));
                    }
                }
            }
        }
    }
}

//void GameScene::onTouchesMoved(const std::vector<Touch*> &touches, Event* event)
//{
//
//}
//
//void GameScene::onTouchesEnded(const std::vector<Touch*> &touches, Event* event)
//{
//
//}

