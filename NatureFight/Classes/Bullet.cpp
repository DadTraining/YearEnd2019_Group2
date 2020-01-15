#include "Bullet.h"
#include "Defines.h"
USING_NS_CC;

Bullet::Bullet(Scene* scene, Sprite *sprite, int owner, std::string nameAction, int idAction, bool stateFolow)
{
	stateBulletFollow = stateFolow;
	mSprite = sprite; 
	//physics body
	mPhysicsBody = PhysicsBody::createBox(Size(60, 60));
	mPhysicsBody->setRotationEnable(false);
	mPhysicsBody->setGravityEnable(false);
	mPhysicsBody->setCollisionBitmask(owner);
	mPhysicsBody->setContactTestBitmask(true);	
	mSprite->setPhysicsBody(mPhysicsBody);
	mSprite->runAction(AnimationObjectRepeat(idAction, nameAction, 1));
	setAlive(false);
	scene->addChild(mSprite,3);
}

Bullet::~Bullet()
{
}


float timeBul = 0;
void Bullet::update(float deltaTime,Player* player)
{
	
	if (isAlive()) 
	{
		timeBul += deltaTime;
		if (timeBul > 1) {
			timeBul = 0;
			this->setAlive(false);
		}
	}
	if (stateBulletFollow) {
		mSprite->getPhysicsBody()->setVelocity((player->m_sprite->getPosition() - this->mSprite->getPosition())*3);
	}
}
cocos2d::RepeatForever* Bullet::AnimationObjectRepeat(int id, std::string name, float speed)
{
	cocos2d::SpriteFrameCache* spriteCache;
	if (id >= 100) {
		spriteCache = ResourceManager::GetInstance()->GetFrameAIById(id);
	}
	else spriteCache = ResourceManager::GetInstance()->GetFramePlayerById(id);
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
	cocos2d::RepeatForever* repeat = cocos2d::RepeatForever::create(animate);
	return repeat;
}
