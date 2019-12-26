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
	//spriteCache ->addSpriteFramesWithFile("Sprites/Man1/Goblin/PNG/PNG Sequences/Slashing/spritesAttackGoblin.plist");
	this->m_sprite = ResourceManager::GetInstance()->GetSpriteById(1);
	this->m_sprite->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	this->m_sprite->setScale(0.2);
	this->sceneGame->addChild(this->m_sprite);
}

void AiLv1::Collision()
{
}
cocos2d::RepeatForever* AiLv1::MovingRight() { return ObjectParent::AnimationObjectRepeat(2, "Warrior_Run"); }
cocos2d::Animate* AiLv1::AttackRight() { return ObjectParent::AnimationObjectOnce(6, "Warrior_Attack_2"); }
cocos2d::RepeatForever* AiLv1::IdleRight() { return ObjectParent::AnimationObjectRepeat(1, "Warrior_Idle"); }
cocos2d::RepeatForever* AiLv1::AttackRightAngry() { return ObjectParent::AnimationObjectRepeat(5, "Warrior_Attack_2"); }
cocos2d::RepeatForever* AiLv1::DieRight() { return ObjectParent::AnimationObjectRepeat(4, "Warrior_Died"); }
cocos2d::Animate* AiLv1::HurtRight() { return ObjectParent::AnimationObjectOnce(3, "Warrior_Hurt"); }
