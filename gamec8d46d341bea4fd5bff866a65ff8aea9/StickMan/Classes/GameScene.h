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
    cocos2d::Color4B getLevelBackground(int level);
    int bottom;
    int level;
    float score;
    float best;
    
    void addTarget(int level_);
    void addTarget1(float dt);
    void addTarget2(float dt);
    void addTarget3(float dt);
    void addTarget4(float dt);
    void addTarget5(float dt);
    void checkCollision(float dt);
    void moveDone(Ref *obj);
    void gameOver();
    void showOverScene(Ref *obj);
    cocos2d::Label *lbScore;
    
    cocos2d::__Array *players;
    cocos2d::__Array *targets;
    cocos2d::__Array *layers;
    
    virtual void onEnter() override;
    virtual void onExit() override;
    void onTouchesBegan(const std::vector<cocos2d::Touch*> &touches, cocos2d::Event* event);
    //void onTouchesMoved(const std::vector<cocos2d::Touch*> &touches, cocos2d::Event* event);
    //void onTouchesEnded(const std::vector<cocos2d::Touch*> &touches, cocos2d::Event* event);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};

#endif // __GameScene_SCENE_H__
