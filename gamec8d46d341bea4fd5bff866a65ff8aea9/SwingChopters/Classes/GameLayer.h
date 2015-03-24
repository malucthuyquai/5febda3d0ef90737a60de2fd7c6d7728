//
//  GameLayer.h
//  TweeJumpCocos2dx
//
//  Created by Carlos Pinan on 13/10/13.
//
//

#ifndef __TweeJumpCocos2dx__GameLayer__
#define __TweeJumpCocos2dx__GameLayer__

#include "MainLayer.h"
#include "Scopters.h"

class GameLayer : public MainLayer
{
public:
    GameLayer();
    void update(float dt);
    static cocos2d::Scene* scene();
    bool playing;
    int direction;
    
    virtual void onEnter() override;
    virtual void onExit() override;
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    
    virtual void onAcceleration(cocos2d::Acceleration* acc, cocos2d::Event* event);
    
    void addBar(Ref *obj);
    void removeBar(Ref *obj);
    void gameOver();
    cocos2d::Sprite* createReba(int dir);
    cocos2d::Sprite* bot1;
    cocos2d::Sprite* bot2;
    cocos2d::Sprite* bar1;
    cocos2d::Sprite* bar2;
    
    cocos2d::Rect getRectSprite(Sprite* sp);
    
    __Array *targets;
    
    cocos2d::Point bird_position;
    cocos2d::Vec2 bird_velocity;
    cocos2d::Vec2 bird_acceleration;
    Scopters *scopters;
    float speed;
    
    int score;
    int best;
    
    void startGame();
    
};

#endif /* defined(__TweeJumpCocos2dx__GameLayer__) */
