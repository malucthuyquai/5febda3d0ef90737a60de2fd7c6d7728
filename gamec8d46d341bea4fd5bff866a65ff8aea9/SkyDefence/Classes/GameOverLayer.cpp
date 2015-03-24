#include "GameOverLayer.h"
#include "GameScene.h"

int GameOverLayer::highestHistoryScore=0;

GameOverLayer::GameOverLayer(void)
{
	score=0;
	highestScore=NULL;
}

GameOverLayer::~GameOverLayer(void)
{
}

GameOverLayer* GameOverLayer::create(int passScore)
{
	GameOverLayer *pRet = new GameOverLayer();
	pRet->score=passScore;
	if (pRet && pRet->init())
	{ 
		pRet->autorelease(); 
		return pRet; 
	} 
	else 
	{ 
		delete pRet; 
		pRet = NULL; 
		return NULL; 
	} 
}

bool GameOverLayer::init()
{
	bool bRet=false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());

		if (CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		}
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/game_over.mp3");

		Size winSize=Director::getInstance()->getWinSize();

		//����gameover_background
	    Sprite* background=Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("gameover.png"));
		background->setPosition(Point(winSize.width/2,winSize.height/2));
		this->addChild(background);

		//����BackMenu
		Sprite* normalBackToGame=Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("btn_finish.png"));
		Sprite* pressedBackToGame=Sprite::createWithSpriteFrame(CCSpriteFrameCache::getInstance()->getSpriteFrameByName("btn_finish.png"));
		MenuItemImage* pBackItem=MenuItemImage::create("btn_finish.png", "btn_finish.png", CC_CALLBACK_1(GameOverLayer::menuBackCallback, this));
		pBackItem->setPosition(Point(winSize.width-normalBackToGame->getContentSize().width/2-10,normalBackToGame->getContentSize().height/2+10));
		Menu *menuBack=Menu::create(pBackItem,NULL);
		menuBack->setPosition(Point::ZERO);
		this->addChild(menuBack);

		//����score
		__String* strScore=__String::createWithFormat("%d",score);
		LabelBMFont* finalScore=LabelBMFont::create(strScore->getCString(),"font/font.fnt");
		finalScore->setColor(Color3B(143,146,147));
		finalScore->setPosition(Point(winSize.width/2,winSize.height/2));
		this->addChild(finalScore);

		DelayTime* delay=DelayTime::create(1.0f);
		ScaleTo* scalebig=ScaleTo::create(1.0f,3.0f);
		ScaleTo* scalelittle=ScaleTo::create(0.3f,2.0f);
		CallFunc* showAD=CallFunc::create(this,callfunc_selector(GameOverLayer::showAD));
		FiniteTimeAction* sequence=Sequence::create(delay,scalebig,scalelittle,showAD,NULL);
		finalScore->runAction(sequence);

		//����tip
		//CCLabelTTF* tip=CCLabelTTF::create("Congratulations! Your Score is","Monaco",20);
		//tip->setColor(ccc3(143,146,147));
		//tip->setPosition(ccp(finalScore->getPosition().x,finalScore->getPosition().y+finalScore->getContentSize().height+50));
		//this->addChild(tip);
		__String* strHighestScore=__String::createWithFormat("%d",highestHistoryScore);
		highestScore=CCLabelBMFont::create(strHighestScore->getCString(),"font/font.fnt");
		highestScore->setColor(Color3B(143,146,147));
		highestScore->setAnchorPoint(Point(0,0.5));
		highestScore->setPosition(Point(140,winSize.height-30));
		this->addChild(highestScore);

		if (score>highestHistoryScore)
		{
			UserDefault::getInstance()->setIntegerForKey("HighestScore",score);
			highestHistoryScore=score;
			DelayTime* delayChange=DelayTime::create(1.3f);
			MoveBy* moveOut=MoveBy::create(0.1f,Point(0,100));
			CallFuncN* beginChange=CallFuncN::create(this,callfuncN_selector(GameOverLayer::beginChangeHighestScore));
			MoveBy* moveIn=MoveBy::create(0.1f,Point(0,-100));
			FiniteTimeAction* sequence=Sequence::create(delayChange,moveOut,beginChange,moveIn,NULL);
			highestScore->runAction(sequence);
		}

		this->setKeypadEnabled(true);

		bRet=true;
	} while (0);
	return bRet;
}

void GameOverLayer::menuBackCallback(Ref* pSender)
{
	Scene* pScene=GameScene::create();
	TransitionSlideInL* animateScene=TransitionSlideInL::create(1.0f,pScene);
	Director::getInstance()->replaceScene(animateScene);
}

//void GameOverLayer::keyBackClicked()
//{
//	CCDirector::sharedDirector()->end();
//}

void GameOverLayer::beginChangeHighestScore(Node* pNode)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/achievement.mp3");
	__String* changeScore=__String::createWithFormat("%d",score);
	highestScore->setString(changeScore->getCString());
}

void GameOverLayer::showAD()
{
	
}
