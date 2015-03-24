#include "GameScene.h"
#include "GameConfig.h"
#include "Global.h"
#include <time.h>
#include "GameOver.h"

#define scale _W/450

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
    
    LayerColor *bg = LayerColor::create(Color4B(76, 141, 166, 255), _W, _H);
    bg->setPosition(0, 0);
    addChild(bg);
    
    bg = LayerColor::create(Color4B(91, 96, 140, 255), 450*scale, 450*scale);
    bg->setPosition(0, _H/2-_W/2);
    addChild(bg);
    
    score = Label::createWithTTF("0", "fonts/ClearSans-Bold.ttf", 70*scale);
    score->setAlignment(TextHAlignment::CENTER, TextVAlignment::CENTER);
    score->setColor(Color3B(240, 240, 240));
    score->setPosition(_W/2, _H-40*scale);
    addChild(score);
    
    LayerColor *bg3 = LayerColor::create(Color4B(240, 240, 240, 255), 350*scale, 350*scale);
    bg3->setPosition(50*scale, 50*scale);
    bg->addChild(bg3);
    
    red_mc = Sprite::create();
    red_mc->setColor(Color3B(240, 78, 90));
    red_mc->setTextureRect(Rect(0, 0, 40*scale, 40*scale));
    red_mc->setPosition(_W/2, _W/2);
    red_mc->setAnchorPoint(Point(0.5, 0.5));
    bg->addChild(red_mc);
    
    blue1_mc = Sprite::create();
    blue1_mc->setColor(Color3B(66, 78, 217));
    blue1_mc->setTextureRect(Rect(0, 0, 60*scale, 60*scale));
    blue1_mc->setPosition(70*scale, 320*scale);
    blue1_mc->setAnchorPoint(Point(0, 0));
    bg->addChild(blue1_mc);
    
    blue2_mc = Sprite::create();
    blue2_mc->setColor(Color3B(66, 78, 217));
    blue2_mc->setTextureRect(Rect(0, 0, 60*scale, 50*scale));
    blue2_mc->setPosition(270*scale, 340*scale);
    blue2_mc->setAnchorPoint(Point(0, 0));
    bg->addChild(blue2_mc);
    
    blue3_mc = Sprite::create();
    blue3_mc->setColor(Color3B(66, 78, 217));
    blue3_mc->setTextureRect(Rect(0, 0, 30*scale, 60*scale));
    blue3_mc->setPosition(70*scale, 70*scale);
    blue3_mc->setAnchorPoint(Point(0, 0));
    bg->addChild(blue3_mc);
    
    blue4_mc = Sprite::create();
    blue4_mc->setColor(Color3B(66, 78, 217));
    blue4_mc->setTextureRect(Rect(0, 0, 100*scale, 20*scale));
    blue4_mc->setPosition(300*scale, 100*scale);
    blue4_mc->setAnchorPoint(Point(0, 0));
    bg->addChild(blue4_mc);
    
    speed = 2*realScale;
    startTime = getTime();
    canMove = true;
    return true;
}

float GameScene::getTime()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec;
}


void GameScene::redMove(float _xmouse, float _ymouse)
{
    if (red_mc->getPositionX() < 50 || red_mc->getPositionX() > 360 || red_mc->getPositionY() < 50 || red_mc->getPositionY() > 360)
    {
        //GameOver();
        canMove = false;
    }
    else if (canMove && _xmouse > 50 && _xmouse < 400 && _ymouse > 50 && _ymouse < 400)
    {
        red_mc->setPositionX(_xmouse - 20);
        red_mc->setPositionY(_ymouse - 20);
    } // end else if
} // End of the function

void GameScene::blue1Move()
{
    blue1_mc->setPositionX(blue1_mc->getPositionX() + blue1X * speed);
    blue1_mc->setPositionY(blue1_mc->getPositionY() + blue1Y * speed);
    if (blue1_mc->getPositionX() < 0 || blue1_mc->getPositionX() > _W - blue1_mc->getContentSize().width)
    {
        blue1X = -blue1X;
    } // end if
    if (blue1_mc->getPositionY() < 0 || blue1_mc->getPositionY() > _W - blue1_mc->getContentSize().height)
    {
        blue1Y = -blue1Y;
    } // end if
} // End of the function

void GameScene::blue2Move()
{
    blue2_mc->setPositionX(blue2_mc->getPositionX() + blue2X * speed);
    blue2_mc->setPositionY(blue2_mc->getPositionY() + blue2Y * speed);
    if (blue2_mc->getPositionX() < 0 || blue2_mc->getPositionX() > _W - blue2_mc->getContentSize().width)
    {
        blue2X = -blue2X;
    } // end if
    if (blue2_mc->getPositionY() < 0 || blue2_mc->getPositionY() > _W - blue2_mc->getContentSize().height)
    {
        blue2Y = -blue2Y;
    } // end if
} // End of the function

void GameScene::blue3Move()
{
    blue3_mc->setPositionX(blue3_mc->getPositionX() + blue3X * speed);
    blue3_mc->setPositionY(blue3_mc->getPositionY() + blue3Y * speed);
    if (blue3_mc->getPositionX() < 0 || blue3_mc->getPositionX() > _W - blue3_mc->getContentSize().width)
    {
        blue3X = -blue3X;
    } // end if
    if (blue3_mc->getPositionY() < 0 || blue3_mc->getPositionY() > _W - blue3_mc->getContentSize().height)
    {
        blue3Y = -blue3Y;
    } // end if
} // End of the function

void GameScene::blue4Move()
{
    blue4_mc->setPositionX(blue4_mc->getPositionX() + blue4X * speed);
    blue4_mc->setPositionY(blue4_mc->getPositionY() + blue4Y * speed);
    if (blue4_mc->getPositionX() < 0 || blue4_mc->getPositionX() > _W - blue4_mc->getContentSize().width)
    {
        blue4X = -blue4X;
    } // end if
    if (blue4_mc->getPositionY() < 0 || blue4_mc->getPositionY() > _W - blue4_mc->getContentSize().height)
    {
        blue4Y = -blue4Y;
    } // end if
} // End of the function

void GameScene::hitTest()
{
    Point redp = red_mc->getPosition();
    Size reds = red_mc->getContentSize();
    Rect redr = Rect(redp.x-reds.width/2, redp.y-reds.height/2, reds.width, reds.height);
    Point bluep = blue1_mc->getPosition();
    Size blues = blue1_mc->getContentSize();
    Rect bluer = Rect(bluep.x, bluep.y, blues.width, blues.height);
    if (redr.intersectsRect(bluer)) {
        GameOver();
        return;
    }
    bluep = blue2_mc->getPosition();
    blues = blue2_mc->getContentSize();
    bluer = Rect(bluep.x, bluep.y, blues.width, blues.height);
    if (redr.intersectsRect(bluer)) {
        GameOver();
        return;
    }
    bluep = blue3_mc->getPosition();
    blues = blue3_mc->getContentSize();
    bluer = Rect(bluep.x, bluep.y, blues.width, blues.height);
    if (redr.intersectsRect(bluer)) {
        GameOver();
        return;
    }
    bluep = blue4_mc->getPosition();
    blues = blue4_mc->getContentSize();
    bluer = Rect(bluep.x, bluep.y, blues.width, blues.height);
    if (redr.intersectsRect(bluer)) {
        GameOver();
        return;
    }
    if (redp.x-reds.width/2 < 50*scale) {
        GameOver();
        return;
    }
    if (redp.y-reds.height/2 < 50*scale) {
        GameOver();
        return;
    }
    if (redp.x+reds.width/2 > 400*scale) {
        GameOver();
        return;
    }
    if (redp.y+reds.height/2 > 400*scale) {
        GameOver();
        return;
    }
} // End of the function

void GameScene::GameOver()
{
    canMove = false;
    audio->playEffect("sounds/sfx_over.mp3");
    notify->postNotification("notifygamecentersubmitscore");
    runAction(Sequence::create(DelayTime::create(0.5), CallFuncN::create(CC_CALLBACK_1(GameScene::showOverScene, this)), NULL));
} // End of the function

void GameScene::showOverScene(Ref *dt) {
    utils::captureScreen(NULL, "captured.png");
    auto scene = GameOver::createScene();
    director->replaceScene(TransitionFade::create(0.5, scene));
}

void GameScene::update(float dt)
{
    if(canMove == false) return;
    time_ += dt;
    global->score = time_;
    std::string _loc3 = __String::createWithFormat("%.0f", time_)->getCString();
    if (time_> 0 && _loc3 != score->getString()) {
        audio->playEffect("sounds/sfx_point.aif");
    }
//    if (_loc3.length() < 6 && time_ > 1.0)
//    {
//        int loop = 6 - (int)_loc3.length();
//        for (int _loc2 = 0; _loc2 < loop; _loc2++)
//        {
//            _loc3 = "0" + _loc3;
//        } // end of for
//    } // end if
//    CCLOG("time %s", _loc3.c_str());
    score->setString(_loc3.c_str());
    if (time_ > 1.0000 && time_ < 2.0000)
    {
        speed = 3*realScale;;
    }
    else if (time_ > 2.0000 && time_ < 3.0000)
    {
        speed = 4*realScale;;
    }
    else if (time_ > 3.0000 && time_ < 4.0000)
    {
        speed = 5*realScale;;
    }
    else if (time_ > 4.0000 && time_ < 5.0000)
    {
        speed = 6*realScale;;
    } // end else if
    if (time <= 0)
    {
        startTime = getTime();
    } // end if
    blue1Move();
    blue2Move();
    blue3Move();
    blue4Move();
    hitTest();
} // End of the function

//_root.timeTxt = "";
void GameScene::red_mc_pressed()
{
    if (time <= 0)
    {
        startTime = getTime();
    } // end if
    canMove = true;
    //onEnterFrame = function ()
    {
        hitTest();
        getTime();
        //redMove();
        blue1Move();
        blue2Move();
        blue3Move();
        blue4Move();
    };
};

void GameScene::onEnter()
{
    Layer::onEnter();
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void GameScene::onExit()
{
    Layer::onExit();
}

bool GameScene::onTouchBegan(cocos2d::Touch* touch, Event* event)
{
    schedule(schedule_selector(GameScene::update));
    return true;
}

void GameScene::onTouchMoved(cocos2d::Touch* touch, Event* event)
{
    if(canMove == false) return;
    Point p1 = touch->getPreviousLocationInView();
    Point p2 = touch->getLocationInView();
    p2.subtract(p1);
    p2.y = -p2.y;
    red_mc->runAction(MoveBy::create(0, Point(p2.x*2.0,p2.y*2.0)));
}

void GameScene::onTouchEnded(cocos2d::Touch* touch, Event* event)
{

}

void GameScene::red_mc_release()
{
    canMove = false;
};

