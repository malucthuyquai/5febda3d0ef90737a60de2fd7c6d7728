#ifndef __GameScene_SCENE_H__
#define __GameScene_SCENE_H__

#include "cocos2d.h"

class GameScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    virtual void onEnter() override;
    virtual void onExit() override;
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    
    bool canMove = false;
    float speed = 2.0;
    float startTime = 0.0;
    float endTime = 0.0;
    float time_ = 0.0;
    
    float blue1X  = 1.700000;
    float blue1Y  = 1.100000;
    float blue2X  = -1.0;
    float blue2Y  = 1.200000;
    float blue3X  = 1.500000;
    float blue3Y  = -1.300000;
    float blue4X  = -1.200000;
    float blue4Y  = -2.0;
    
    cocos2d::Sprite *red_mc;
    cocos2d::Sprite *blue1_mc;
    cocos2d::Sprite *blue2_mc;
    cocos2d::Sprite *blue3_mc;
    cocos2d::Sprite *blue4_mc;
    cocos2d::Label *score;
    
    void redMove(float _xmouse, float _ymouse);
    void blue1Move();
    void blue2Move();
    void blue3Move();
    void blue4Move();
    void hitTest();
    void GameOver();
    void update(float dt);
    void red_mc_pressed();
    void red_mc_release();
    float getTime();
    void captureScreen(cocos2d::Ref *obj);
    void showOverScene(cocos2d::Ref *obj);
    
    // a selector callback
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};

#endif // __GameScene_SCENE_H__
