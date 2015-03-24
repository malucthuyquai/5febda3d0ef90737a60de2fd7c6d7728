#ifndef __GameScene_SCENE_H__
#define __GameScene_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d;

class GameScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void backgroundMoveEnd(cocos2d::Ref* pSender);
    
    Sprite *kldich;
    
    __Array *clouds;
    __Array *khunglong;
    
    float score;
    float best;
    float interval;
    float duration;
    bool isGameOver;
    void increaseLevel(float dt);
    void monsterDie(Ref *obj, Sprite *monster);
    
    void addKhungLong(float dt);
    
    void bom(Ref *obj);
    void shut(Ref *obj);
    void chem(Ref *obj);
    void start(Ref *obj);
    
    void checkOver(float dt);
    
    void gameOver(Sprite *monster);
    
    Label *lblscore;
    Label *lblscore2;
    Label *lblbest;
    
    Sprite *gameover;
    Sprite *help;
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};

#endif // __GameScene_SCENE_H__
