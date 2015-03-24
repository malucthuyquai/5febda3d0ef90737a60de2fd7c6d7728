#include "BulletLayer.h"
#include "PlaneLayer.h"

BulletLayer::BulletLayer(void)
{
	//bulletSpriteFrame=NULL;
	bulletBatchNode=NULL;

	m_pAllBullet=CCArray::create();
	m_pAllBullet->retain();
}

BulletLayer::~BulletLayer(void)
{
	m_pAllBullet->release();
	m_pAllBullet=NULL;
}

bool BulletLayer::init()
{
	bool bRet=false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());

		//bulletSpriteFrame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bullet1.png");

		Texture2D *texture = Director::getInstance()->getTextureCache()->getTextureForKey("ui/shoot.png");
		bulletBatchNode = CCSpriteBatchNode::createWithTexture(texture);
		this->addChild(bulletBatchNode);

		bRet=true;
	} while (0);
	return bRet;
}

void BulletLayer::StartShoot(float delay)
{
	this->schedule(schedule_selector(BulletLayer::AddBullet),0.20f,-1,delay);
}

void BulletLayer::StopShoot()
{
	this->unschedule(schedule_selector(BulletLayer::AddBullet));
}

void BulletLayer::AddBullet(float dt)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/bullet.mp3");
	Sprite* bullet=Sprite::createWithSpriteFrameName("bullet1.png");
	bulletBatchNode->addChild(bullet);
	//this->addChild(bullet);
	this->m_pAllBullet->addObject(bullet);

	Point planePosition=PlaneLayer::sharedPlane->getChildByTag(AIRPLANE)->getPosition();
	Point bulletPosition=Point(planePosition.x,planePosition.y+PlaneLayer::sharedPlane->getChildByTag(AIRPLANE)->getContentSize().height/2);
	bullet->setPosition(bulletPosition);
    
	float length=Director::getInstance()->getWinSize().height+bullet->getContentSize().height/2-bulletPosition.y;
	float velocity=320/1;//320pixel/sec
	float realMoveDuration=length/velocity;

	FiniteTimeAction* actionMove=MoveTo::create(realMoveDuration,Point(bulletPosition.x,Director::getInstance()->getWinSize().height+bullet->getContentSize().height/2));
	FiniteTimeAction* actionDone=CallFuncN::create(this,callfuncN_selector(BulletLayer::bulletMoveFinished));

	Sequence* sequence=Sequence::create(actionMove,actionDone,NULL);
	bullet->runAction(sequence);
}

void BulletLayer::bulletMoveFinished(Node* pSender)
{
	Sprite* bullet=(Sprite*)pSender;
	this->bulletBatchNode->removeChild(bullet,true);
	this->m_pAllBullet->removeObject(bullet);
}

void BulletLayer::RemoveBullet(Sprite* bullet)
{
	if (bullet!=NULL)
	{
		this->bulletBatchNode->removeChild(bullet,true);
		this->m_pAllBullet->removeObject(bullet);
	}
}

