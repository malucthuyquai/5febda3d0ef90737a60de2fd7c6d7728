#include "UFOLayer.h"

UFOLayer::UFOLayer(void)
{
	m_pAllMutiBullets=CCArray::create();
	m_pAllMutiBullets->retain();
	m_pAllBigBoom=CCArray::create();
	m_pAllBigBoom->retain();
}

UFOLayer::~UFOLayer(void)
{
	m_pAllMutiBullets->release();
	m_pAllMutiBullets=NULL;
	m_pAllBigBoom->release();
	m_pAllBigBoom=NULL;
}

bool UFOLayer::init()
{
	bool bRet=false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());

		this->schedule(schedule_selector(UFOLayer::AddMutiBullets),20.0);
		this->schedule(schedule_selector(UFOLayer::AddBigBoom),20.0,-1,5.0);
		bRet=true;
	} while (0);

	return bRet;
}

void UFOLayer::AddMutiBullets(float dt)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/out_porp.mp3");
	Sprite* mutiBullets=Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("ufo1.png"));

	Size mutiBlletsSize=mutiBullets->getContentSize();
	Size winSize=Director::getInstance()->getWinSize();
	int minX=mutiBlletsSize.width/2;
	int maxX=winSize.width-mutiBlletsSize.width/2;
	int rangeX=maxX-minX;
	int actualX=(rand()%rangeX)+minX;

	mutiBullets->setPosition(Point(actualX,winSize.height+mutiBlletsSize.height/2));
	this->addChild(mutiBullets);
	this->m_pAllMutiBullets->addObject(mutiBullets);

	MoveBy* move1 = MoveBy::create(0.5f, Point(0, -150));
	MoveBy* move2 = MoveBy::create(0.3f, Point(0, 100));
	MoveBy* move3 = MoveBy::create(1.0f, Point(0,0-winSize.height-mutiBlletsSize.height/2));
	CallFuncN* moveDone = CallFuncN::create(this,callfuncN_selector(UFOLayer::mutiBulletsMoveFinished));

	FiniteTimeAction* sequence = Sequence::create(move1,move2,move3,moveDone,NULL);
	mutiBullets->runAction(sequence);

}

void UFOLayer::mutiBulletsMoveFinished(Node* pSender)
{
	Sprite* mutiBullets=(Sprite*)pSender;
	this->removeChild(mutiBullets,true);//从屏幕中移除
	this->m_pAllMutiBullets->removeObject(mutiBullets);//从数组中移除
}

void UFOLayer::AddBigBoom(float dt)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/out_porp.mp3");
	Sprite* bigBoom=Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("ufo2.png"));

	Size bigBoomSize=bigBoom->getContentSize();
	Size winSize=Director::getInstance()->getWinSize();
	int minX=bigBoomSize.width/2;
	int maxX=winSize.width-bigBoomSize.width/2;
	int rangeX=maxX-minX;
	int actualX=(rand()%rangeX)+minX;

	bigBoom->setPosition(Point(actualX,winSize.height+bigBoomSize.height/2));
	this->addChild(bigBoom);
	this->m_pAllBigBoom->addObject(bigBoom);

	MoveBy* move1 = MoveBy::create(0.5, Point(0, -150));
	MoveBy* move2 = MoveBy::create(0.3, Point(0, 100));
	MoveBy* move3 = MoveBy::create(1.0, Point(0,0-winSize.height-bigBoomSize.height/2));
	CallFuncN* moveDone = CallFuncN::create(this,callfuncN_selector(UFOLayer::bigBoomMoveFinished));

	FiniteTimeAction* sequence = Sequence::create(move1,move2,move3,moveDone,NULL);
	bigBoom->runAction(sequence);
}

void UFOLayer::bigBoomMoveFinished(Node* pSender)
{
	Sprite* bigBoom=(Sprite*)pSender;
	this->removeChild(bigBoom,true);
	this->m_pAllBigBoom->removeObject(bigBoom);
}

void UFOLayer::RemoveMutiBullets(Sprite* mutiBullets)
{
	this->removeChild(mutiBullets,true);
	this->m_pAllMutiBullets->removeObject(mutiBullets);
}

void UFOLayer::RemoveBigBoom(Sprite* bigBoom)
{
	this->removeChild(bigBoom,true);
	this->m_pAllBigBoom->removeObject(bigBoom);
}