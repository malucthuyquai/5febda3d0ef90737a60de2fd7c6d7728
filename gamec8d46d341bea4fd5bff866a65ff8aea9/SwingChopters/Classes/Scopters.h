//
//  Scopters.h
//  FlappyJump
//
//  Created by LyGV on 8/22/14.
//
//

#ifndef __FlappyJump__Scopters__
#define __FlappyJump__Scopters__

#include <iostream>
#include "cocos2d.h"
#include "GameConfig.h"

USING_NS_CC;

class Scopters : public cocos2d::Sprite
{
public:
    
    static Scopters *createScopters();
    
    virtual void update(float dt);
    
    CREATE_FUNC(Scopters);
};

#endif /* defined(__FlappyJump__Scopters__) */
