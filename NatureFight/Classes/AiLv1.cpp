#include "AiLv1.h"
#include <vector> 
#include <ResourceManager.h>
AiLv1::AiLv1(cocos2d::Scene* scene)
{
	sceneGame = scene;
}

void AiLv1::Update(float deltaTime)
{
}

void AiLv1::Init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	this->m_sprite = cocos2d::Sprite::create("Sprites/Main/Warrior_animations/Right_Side/PNG_Sequences/Warrior_clothes_empty/Idle_Blinking/0_Warrior_Idle_000.png");
	this->m_sprite->setPosition(Point(visibleSize.width / 1.5, visibleSize.height / 2));
	this->m_sprite->setScale(0.1);
	this->sceneGame->addChild(this->m_sprite);
	physicsBody1 = PhysicsBody::createBox(this->m_sprite->getContentSize());
	physicsBody1->setDynamic(false);
	physicsBody1->setRotationEnable(false);
	physicsBody1->setCollisionBitmask(101);
	physicsBody1->setContactTestBitmask(1);
	this->m_sprite->setPhysicsBody(physicsBody1);
	physicsBody1->setGravityEnable(false);
}

void AiLv1::Collision()
{

}
bool AiLv1::StartAttack(int)
{
	return false;
}
cocos2d::RepeatForever* AiLv1::MovingRight() { return ObjectParent::AnimationObjectRepeat(2, "Warrior_Run"); }
cocos2d::Animate* AiLv1::AttackRight() { return ObjectParent::AnimationObjectOnce(6, "Warrior_Attack_2"); }
cocos2d::RepeatForever* AiLv1::IdleRight() { return ObjectParent::AnimationObjectRepeat(1, "Warrior_Idle"); }
cocos2d::Animate* AiLv1::AttackRightAngry() { return ObjectParent::AnimationObjectOnce(5, "Warrior_Attack_2"); }
cocos2d::RepeatForever* AiLv1::DieRight() { return ObjectParent::AnimationObjectRepeat(4, "Warrior_Died"); }
cocos2d::RepeatForever* AiLv1::MovingUp()
{
	return nullptr;
}
cocos2d::Animate* AiLv1::AttackUp()
{
	return nullptr;
}
cocos2d::RepeatForever* AiLv1::IdleUp()
{
	return nullptr;
}
cocos2d::Animate* AiLv1::AttackUpAngry()
{
	return nullptr;
}
cocos2d::Animate* AiLv1::HurtUp()
{
	return nullptr;
}
cocos2d::RepeatForever* AiLv1::DieUp()
{
	return nullptr;
}
cocos2d::RepeatForever* AiLv1::MovingDown()
{
	return nullptr;
}
cocos2d::Animate* AiLv1::AttackDown()
{
	return nullptr;
}
cocos2d::RepeatForever* AiLv1::IdleDown()
{
	return nullptr;
}
cocos2d::Animate* AiLv1::AttackDownAngry()
{
	return nullptr;
}
cocos2d::Animate* AiLv1::HurtDown()
{
	return nullptr;
}
cocos2d::RepeatForever* AiLv1::DieDown()
{
	return nullptr;
}
cocos2d::Animate* AiLv1::HurtRight() { return ObjectParent::AnimationObjectOnce(3, "Warrior_Hurt"); }
