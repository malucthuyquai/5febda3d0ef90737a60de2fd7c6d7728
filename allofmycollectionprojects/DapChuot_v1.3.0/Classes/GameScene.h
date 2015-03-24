#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

class GameScene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    virtual ~GameScene();
    
    //
    virtual void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    //virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    //virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    void popUpChuot(float dt);
    void addChuot(cocos2d::CCPoint p, float scale);
    void increaseLevel();
    void gameOver();
    void notifyAdmobChange(cocos2d::CCObject *pSender);
    void menuPlayCallback(cocos2d::CCObject* pSender);
    void menuGameCallback(cocos2d::CCObject* pSender);
    void menuShareCallback(cocos2d::CCObject* pSender);
    void hideSplash();
    void saveScreenShot();
    void admobShow();
    
    float inteval;
    int index;
    cocos2d::CCLabelTTF *scoreLabel;
    cocos2d::CCLabelTTF *bestLabel;
    cocos2d::CCSprite *bar;
    cocos2d::CCSprite *help;
    cocos2d::CCMenuItemImage *game;
    cocos2d::CCMenuItemImage *fb;
    cocos2d::CCMenuItemImage *playitem;
    float score;
    float best;
    bool gameOverred;
    bool popupFirst;
    
    cocos2d::CCLayerColor *gameOverlayer;
    cocos2d::CCSprite *gameOverText;
    cocos2d::CCMenu *play;
    cocos2d::CCArray *chuotArray;
    
    // implement the "static node()" method manually
    CREATE_FUNC(GameScene);
};

#endif // __GAME_SCENE_H__
