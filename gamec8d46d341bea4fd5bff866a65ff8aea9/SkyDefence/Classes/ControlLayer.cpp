#include "ControlLayer.h"

ControlLayer::ControlLayer(void)
{
	scoreItem=NULL;
	pPauseItem=NULL;
}

ControlLayer::~ControlLayer(void)
{
}

bool ControlLayer::init()
{
	bool bRet=false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());

		Size winSize=Director::getInstance()->getWinSize();

		//加入PauseMenu
		Sprite* normalPause=Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_pause_nor.png"));
		Sprite* pressedPause=Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_pause_pressed.png"));
		pPauseItem=CCMenuItemImage::create("game_pause_nor.png", "game_pause_pressed.png", CC_CALLBACK_1(ControlLayer::menuPauseCallback, this));
		pPauseItem->setPosition(Point(normalPause->getContentSize().width/2+10,winSize.height-normalPause->getContentSize().height/2-10));
		Menu *menuPause=Menu::create(pPauseItem,NULL);
		menuPause->setPosition(Point::ZERO);
		this->addChild(menuPause,101);

		//加入score
		scoreItem=CCLabelBMFont::create("0","font/font.fnt");
		scoreItem->setColor(Color3B(143,146,147));
		scoreItem->setAnchorPoint(Point(0,0.5));
		scoreItem->setPosition(Point(pPauseItem->getPositionX()+normalPause->getContentSize().width/2+5,pPauseItem->getPositionY()));
		this->addChild(scoreItem);

		bRet=true;
	} while (0);

	return bRet;
}

void ControlLayer::menuPauseCallback(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/button.mp3");
	if(!Director::getInstance()->isPaused())
	{
		pPauseItem->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_resume_nor.png"));
		pPauseItem->setSelectedSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_resume_pressed.png"));
		CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
		Director::getInstance()->pause();
		noTouchLayer=NoTouchLayer::create();
		this->addChild(noTouchLayer);
	}
	else
	{
		pPauseItem->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_pause_nor.png"));
		pPauseItem->setSelectedSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_pause_pressed.png"));
		CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		Director::getInstance()->resume();
		this->removeChild(noTouchLayer,true);
	}
}

void ControlLayer::updateScore(int score)
{
	if (score>=0 && score<=MAX_SCORE)
	{
		__String* strScore=__String::createWithFormat("%d",score);
		scoreItem->setString(strScore->getCString());
	}
}
