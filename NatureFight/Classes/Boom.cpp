#include "Boom.h"
#include "Defines.h"

USING_NS_CC;

Boom::Boom(Scene* scene, Sprite* sprite, int owner)
{
	mSprite = sprite;
	CurExplosionState = false;
	//physics body
	mPhysicsBody = PhysicsBody::createBox(Size(40, 40));
	mPhysicsBody->setRotationEnable(false);
	mPhysicsBody->setGravityEnable(false);
	mPhysicsBody->setCollisionBitmask(owner);
	mPhysicsBody->setContactTestBitmask(true);
	explotion = Node::create();
	scene->addChild(explotion);
	mSprite->setPhysicsBody(mPhysicsBody);
	setAlive(false);
	scene->addChild(mSprite,3);

}

Boom::~Boom()
{
}

void Boom::SetExplo(bool exState)
{
	if ((exState==true)&&(exState!=CurExplosionState)) {
		this->mSprite->stopAllActions();
		this->mSprite->getPhysicsBody()->setVelocity(Vec2(0, 0));
		this->mSprite->runAction(Explosion());
		auto edgeBody= PhysicsBody::createEdgeBox(Size(70, 70));
		edgeBody->setContactTestBitmask(Model::BITMASK_MONSTER);
		edgeBody->setCollisionBitmask(false);
		this->explotion->setPhysicsBody(edgeBody);
		this->explotion->setPosition(mSprite->getPosition());
		this->explotion->setTag(BoomEx);
	}
	CurExplosionState = exState;
}

float timeBullet=0;
void Boom::update(float deltaTime)
{
	if (isAlive())
	{
		timeBullet += deltaTime;
		//time Live
		if (timeBullet>1&& timeBullet < 2)
		{
			SetExplo(true);
		}else if (timeBullet > 2) {
			SetExplo(false);
			this->mSprite->stopAllActions();
			setAlive(false);
			this->mSprite->runAction(defautBombAction(111, 1));
			timeBullet = 0;
		}
	}
}
cocos2d::Animate* Boom::Explosion() {
	return AnimationObjectOnce(111, "boom", 1);
}
cocos2d::Animate* Boom::AnimationObjectOnce(int id, std::string name, float speed)
{
	auto spriteCache = ResourceManager::GetInstance()->GetFrameAIById(id);
	cocos2d::Vector<cocos2d::SpriteFrame*> exFrames;
	int i = 0;
	std::string link;
	while (true) {
		link = "0_" + name + "_00" + std::to_string(i) + ".png";
		if (i >= 10) link = "0_" + name + "_0" + std::to_string(i) + ".png";
		if (spriteCache->getSpriteFrameByName(link) == nullptr) break;
		exFrames.pushBack(spriteCache->getSpriteFrameByName(link));
		i++;
	}
	auto animation = cocos2d::Animation::createWithSpriteFrames(exFrames, 0.05 / speed);
	auto animate = cocos2d::Animate::create(animation);
	return animate;
}
cocos2d::Animate* Boom::defautBombAction(int id, float speed)
{
	auto spriteCache = ResourceManager::GetInstance()->GetFrameAIById(id);
	cocos2d::Vector<cocos2d::SpriteFrame*> exFrames;
	std::string name = "boom";
	int i = 0;
	std::string link;
	while (i<2) {
		link = "0_" + name + "_00" + std::to_string(i) + ".png";
		if (i >= 10) link = "0_" + name + "_0" + std::to_string(i) + ".png";
		if (spriteCache->getSpriteFrameByName(link) == nullptr) break;
		exFrames.pushBack(spriteCache->getSpriteFrameByName(link));
		i++;
	}
	auto animation = cocos2d::Animation::createWithSpriteFrames(exFrames, 0.05 / speed);
	auto animate = cocos2d::Animate::create(animation);
	return animate;
}
