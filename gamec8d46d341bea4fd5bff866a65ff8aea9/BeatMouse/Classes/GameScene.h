#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

class GameScene : public cocos2d::Layer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    virtual ~GameScene();
    static cocos2d::Scene* createScene();
    //
    void onTouchesBegan(const std::vector<cocos2d::Touch*> &touches, cocos2d::Event* event);

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* scene();
    void popUpChuot(float dt);
    void addChuot(cocos2d::Point p, float scale);
    void increaseLevel(float dt);
    void gameOver();
    void notifyAdmobChange(cocos2d::Ref *pSender);
    void menuPlayCallback(cocos2d::Ref* pSender);
    void menuGameCallback(cocos2d::Ref* pSender);
    void menuShareCallback(cocos2d::Ref* pSender);
    void hideSplash(float dt);
    void saveScreenShot();
    void admobShow();
    
    float inteval;
    int index;
    cocos2d::Label *scoreLabel;
    cocos2d::Label *bestLabel;
    cocos2d::Sprite *bar;
    cocos2d::Sprite *help;
    cocos2d::MenuItemImage *game;
    cocos2d::MenuItemImage *fb;
    cocos2d::MenuItemImage *playitem;
    float score;
    float best;
    bool gameOverred;
    bool popupFirst;
    
    virtual void onEnter() override;
    virtual void onExit() override;
    
    cocos2d::LayerColor *gameOverlayer;
    cocos2d::Sprite *gameOverText;
    cocos2d::Menu *play;
    cocos2d::__Array *chuotArray;
    
    // implement the "static node()" method manually
    CREATE_FUNC(GameScene);
};

#endif // __GAME_SCENE_H__
