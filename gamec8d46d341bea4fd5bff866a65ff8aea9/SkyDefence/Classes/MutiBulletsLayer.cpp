#include "MutiBulletsLayer.h"
#include "PlaneLayer.h"

MutiBulletsLayer::MutiBulletsLayer(void)
{
	//mutiBulletsSpriteFrame=NULL;
	mutiBullesBatchNode=NULL;

	m_pAllMutiBullets=CCArray::create();
	m_pAllMutiBullets->retain();
}

MutiBulletsLayer::~MutiBulletsLayer(void)
{
	m_pAllMutiBullets->release();
	m_pAllMutiBullets=NULL;
}

bool MutiBulletsLayer::init()
{
	bool bRet=false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());

		//mutiBulletsSpriteFrame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bullet2.png");

		Texture2D *texture = Director::getInstance()->getTextureCache()->getTextureForKey("ui/shoot.png");
		mutiBullesBatchNode = CCSpriteBatchNode::createWithTexture(texture);
		this->addChild(mutiBullesBatchNode);

		bRet=true;
	} while (0);
	return bRet;
}

void MutiBulletsLayer::StartShoot()
{
	this->schedule(schedule_selector(MutiBulletsLayer::AddMutiBullets),0.2f,30,0.0f);
}

void MutiBulletsLayer::StopShoot()
{
	this->unschedule(schedule_selector(MutiBulletsLayer::AddMutiBullets));
}

void MutiBulletsLayer::AddMutiBullets(float dt)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/bullet.mp3");

	Sprite* bulletLeft=Sprite::createWithSpriteFrameName("bullet2.png");
	Sprite* bulletRight=Sprite::createWithSpriteFrameName("bullet2.png");
	mutiBullesBatchNode->addChild(bulletLeft);
	mutiBullesBatchNode->addChild(bulletRight);
	this->m_pAllMutiBullets->addObject(bulletLeft);
	this->m_pAllMutiBullets->addObject(bulletRight);

	Point planePosition=PlaneLayer::sharedPlane->getChildByTag(AIRPLANE)->getPosition();
	Point bulletLeftPosition=Point(planePosition.x-33,planePosition.y+35);
	Point bulletRightPosition=Point(planePosition.x+33,planePosition.y+35);
	bulletLeft->setPosition(bulletLeftPosition);
	bulletRight->setPosition(bulletRightPosition);

	float length=Director::getInstance()->getWinSize().height+bulletLeft->getContentSize().height/2-bulletLeftPosition.y;
	float velocity=420/1;//420pixel/sec
	float realMoveDuration=length/velocity;

	FiniteTimeAction* actionLeftMove=MoveTo::create(realMoveDuration,Point(bulletLeftPosition.x,Director::getInstance()->getWinSize().height+bulletLeft->getContentSize().height/2));
	FiniteTimeAction* actionLeftDone=CallFuncN::create(this,callfuncN_selector(MutiBulletsLayer::mutiBulletsMoveFinished));
	Sequence* sequenceLeft=CCSequence::create(actionLeftMove,actionLeftDone,NULL);
	
	FiniteTimeAction* actionRightMove=MoveTo::create(realMoveDuration,Point(bulletRightPosition.x,CCDirector::sharedDirector()->getWinSize().height+bulletRight->getContentSize().height/2));
	FiniteTimeAction* actionRightDone=CallFuncN::create(this,callfuncN_selector(MutiBulletsLayer::mutiBulletsMoveFinished));
	Sequence* sequenceRight=CCSequence::create(actionRightMove,actionRightDone,NULL);

	bulletLeft->runAction(sequenceLeft);
	bulletRight->runAction(sequenceRight);
}

void MutiBulletsLayer::mutiBulletsMoveFinished(Node* pSender)
{
	Sprite* mutiBullets=(Sprite*)pSender;
	m_pAllMutiBullets->removeObject(mutiBullets);
	this->mutiBullesBatchNode->removeChild(mutiBullets,true);
	CCLOG("MutiBUlletsCount=%zd",m_pAllMutiBullets->count());
}

void MutiBulletsLayer::RemoveMutiBullets(Sprite* mutiBullets)
{
	if (mutiBullets!=NULL)
	{
		this->m_pAllMutiBullets->removeObject(mutiBullets);
		this->mutiBullesBatchNode->removeChild(mutiBullets,true);
	}
}
