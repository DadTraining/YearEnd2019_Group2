#include "AiLv1.h"
#include <vector> 
#include <ResourceManager.h>
AiLv1::AiLv1(cocos2d::Scene* scene)
{
	sceneGame = scene;
}
void AiLv1::Update(float deltaTime)
{
	
	if (this->m_sprite->getPhysicsBody()->getVelocity().x < 0) {
		faceRight = false;
	}
	else if (this->m_sprite->getPhysicsBody()->getVelocity().x > 0)
	{
		faceRight = true;

	}
	if (faceRight == true) {
		this->m_sprite->setFlippedX(false);
	}
	else
	{
		this->m_sprite->setFlipX(true);
	}

}

void AiLv1::Init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	this->m_sprite = cocos2d::Sprite::create("Sprites/Main/Warrior_animations/Right_Side/PNG_Sequences/Warrior_clothes_empty/Idle_Blinking/0_Warrior_Idle_000.png");
	this->m_sprite->setPosition(Point(visibleSize.width / 1.2, visibleSize.height / 1.2));
	faceRight = true;
	this->m_sprite->setScale(0.1);
	this->sceneGame->addChild(this->m_sprite);
	physicsBodyChar = PhysicsBody::createBox(this->m_sprite->getContentSize()/3, PhysicsMaterial(0.1f, 1.0f, 0.0f));
	physicsBodyChar->setDynamic(false);
	physicsBodyChar->setRotationEnable(false);
	physicsBodyChar->setCollisionBitmask(Model::BITMASK_MONSTER);
	physicsBodyChar->setContactTestBitmask(1);
	this->m_sprite->setPhysicsBody(physicsBodyChar);
	physicsBodyChar->setGravityEnable(false);
}
float timem = 0;
void AiLv1::Collision(Player* player, float deltaTime)
{

	if ((Distance(this->m_sprite->getPosition(),player->m_sprite->getPosition()))<=80) {
		timem += deltaTime;
		if (timem >= 1.5) {
			m_sprite->stopAllActions();
			physicsBodyChar->setVelocity(Vec2(0, 0));
			m_sprite->runAction(AttackAi());
			timem = 0;
		}
	} else if ((Distance(this->m_sprite->getPosition(), player->m_sprite->getPosition())) < 100 && (Distance(this->m_sprite->getPosition(), player->m_sprite->getPosition())) > 80) {
		this->physicsBodyChar->setVelocity((player->m_sprite->getPosition() - this->m_sprite->getPosition())/2);
		timem += deltaTime;
		if (timem >= 1) {
			m_sprite->stopAllActions();
			m_sprite->runAction(MovingRight());
			timem = 0;
		}
	}else
	{
		timem += deltaTime;
		if (timem >= 1) {
			m_sprite->stopAllActions();
			m_sprite->runAction(IdleRight());
			physicsBodyChar->setVelocity(Vec2(0, 0));
			timem = 0;
		}
	}
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
cocos2d::RepeatForever* AiLv1::AttackAi()
{
	return ObjectParent::AnimationObjectRepeat(6, "Warrior_Attack_2");
}
cocos2d::Animate* AiLv1::HurtRight() { return ObjectParent::AnimationObjectOnce(3, "Warrior_Hurt"); }
cocos2d::RepeatForever* AiLv1::MovingUp()
{
	return ObjectParent::AnimationObjectRepeat(8, "Warrior_Run");
}
cocos2d::Animate* AiLv1::AttackUp()
{
	return ObjectParent::AnimationObjectOnce(12, "Warrior_Attack_1");
}
cocos2d::RepeatForever* AiLv1::IdleUp()
{
	return ObjectParent::AnimationObjectRepeat(7, "Warrior_Idle");
}
cocos2d::Animate* AiLv1::AttackUpAngry()
{
	return ObjectParent::AnimationObjectOnce(11, "Warrior_Attack_2");
}
cocos2d::Animate* AiLv1::HurtUp()
{
	return ObjectParent::AnimationObjectOnce(9, "Warrior_Hurt");
}
cocos2d::RepeatForever* AiLv1::DieUp()
{
	return ObjectParent::AnimationObjectRepeat(10, "Warrior_Died");
}
cocos2d::RepeatForever* AiLv1::MovingDown()
{
	return ObjectParent::AnimationObjectRepeat(14, "Warrior_Run");
}
cocos2d::Animate* AiLv1::AttackDown()
{
	return ObjectParent::AnimationObjectOnce(18, "Warrior_Attack_1");
}
cocos2d::RepeatForever* AiLv1::IdleDown()
{
	return ObjectParent::AnimationObjectRepeat(13, "Warrior_Idle");
}
cocos2d::Animate* AiLv1::AttackDownAngry()
{
	return ObjectParent::AnimationObjectOnce(17, "Warrior_Attack_2");
}
cocos2d::Animate* AiLv1::HurtDown()
{
	return ObjectParent::AnimationObjectOnce(15, "Warrior_Hurt");
}
cocos2d::RepeatForever* AiLv1::DieDown()
{
	return ObjectParent::AnimationObjectRepeat(16, "Warrior_Died");
}

float AiLv1::Distance(Vec2 A, Vec2 C) {
	return std::sqrt((A.x - C.x) * (A.x - C.x) + (A.y - C.y) * (A.y - C.y));
}

void AiLv1::SetFace()
{
}
