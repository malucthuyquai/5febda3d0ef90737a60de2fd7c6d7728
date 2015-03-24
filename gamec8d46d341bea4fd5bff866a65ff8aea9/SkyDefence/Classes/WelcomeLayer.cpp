#include "WelcomeLayer.h"
#include "GameScene.h"
#include "GameOverLayer.h"

WelcomeLayer::WelcomeLayer(void)
{
}

WelcomeLayer::~WelcomeLayer(void)
{
}

bool WelcomeLayer::init()
{
	bool bRet=false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());

		//png加入全局cache中
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/shoot_background.plist");
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/shoot.plist");

		CCSize winSize=CCDirector::sharedDirector()->getWinSize();

		//加入background
		CCSprite* background=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("background.png"));
		background->setPosition(ccp(winSize.width/2,winSize.height/2));
		this->addChild(background);

		//加入copyright
		CCSprite* copyright=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("shoot_copyright.png"));
		copyright->setAnchorPoint(ccp(0.5,0));
		copyright->setPosition(ccp(winSize.width/2,winSize.height/2));
		this->addChild(copyright);

		//加入loading
		CCSprite* loading=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading1.png"));
		loading->setPosition(ccp(winSize.width/2,winSize.height/2-40));
		this->addChild(loading);

		CCAnimation* animation=CCAnimation::create();
		animation->setDelayPerUnit(0.2f);
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading1.png"));
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading2.png"));
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading3.png"));
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading4.png"));

		CCAnimate* animate=CCAnimate::create(animation);
		CCRepeat* repeat=CCRepeat::create(animate,2);
		CCCallFuncN* repeatdone=CCCallFuncN::create(this,callfuncN_selector(WelcomeLayer::loadingDone));
		CCSequence* sequence=CCSequence::create(repeat,repeatdone,NULL);
		loading->runAction(sequence);
		
		getHighestHistorySorce();

		this->setKeypadEnabled(true);

		bRet=true;
	} while (0);

	return bRet;
}

void WelcomeLayer::loadingDone(Node* pNode)
{
	Scene* pScene=GameScene::create();
	TransitionMoveInB *animateScene=TransitionMoveInB::create(0.5f,pScene);
	Director::getInstance()->replaceScene(animateScene);
}

//void WelcomeLayer::keyBackClicked()
//{
//	CCDirector::sharedDirector()->end();
//}

bool WelcomeLayer::isHaveSaveFile()
{
	if(!UserDefault::getInstance()->getBoolForKey("isHaveSaveFileXml"))
	{
		UserDefault::getInstance()->setBoolForKey("isHaveSaveFileXml", true);
		UserDefault::getInstance()->setIntegerForKey("HighestScore",0);
		UserDefault::getInstance()->flush();
		return false;
	}
	else
	{
		return true;
	}
}

void WelcomeLayer::getHighestHistorySorce()
{
	if (isHaveSaveFile())
	{
		GameOverLayer::highestHistoryScore=UserDefault::getInstance()->getIntegerForKey("HighestScore",0);
	}
}