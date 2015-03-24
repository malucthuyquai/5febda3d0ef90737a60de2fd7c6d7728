//
//  Chuot.h
//  HelloCpp
//
//  Created by LyGV on 2014/02/15.
//
//

#ifndef __HelloCpp__Chuot__
#define __HelloCpp__Chuot__

#include <iostream>

#include "cocos2d.h"

class Chuot : public cocos2d::Sprite
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static Chuot* sprite();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    void playAnimationPopup(bool first);
    void playAnimationHit();
    void popDownEnd(Ref *obj);
    
    // a selector callback
    void enableHit(Ref *obj);
    void disableHit(Ref *obj);
    void setHide(Ref *obj);
    
    bool hitEnable;
    bool isShowing;
    bool isEating;
    
    // implement the "static create()" method manually
    CREATE_FUNC(Chuot);
};

#endif /* defined(__HelloCpp__Chuot__) */
