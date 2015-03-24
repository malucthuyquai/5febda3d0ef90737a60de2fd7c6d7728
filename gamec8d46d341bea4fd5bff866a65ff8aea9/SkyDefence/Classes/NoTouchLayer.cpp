#include "NoTouchLayer.h"

bool NoTouchLayer::init(){  
	if (!Layer::init() )  
	{  
		return false;  
	}
	return true;  
}

void NoTouchLayer::onEnter()
{
    Layer::onEnter();
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(NoTouchLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(NoTouchLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(NoTouchLayer::onTouchEnded, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void NoTouchLayer::onExit()
{
    Layer::onExit();
}


bool NoTouchLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{     
	return true;  
}  

void NoTouchLayer::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{  
}  

void NoTouchLayer::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{  
}  