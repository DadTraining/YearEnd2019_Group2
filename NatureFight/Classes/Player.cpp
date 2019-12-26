#include <Player.h>
#include "SimpleAudioEngine.h"
using namespace CocosDenshion; 
int Player::Level;
int Player::Exp;
Player::Player(cocos2d::Scene* scene)
{
	sceneGame = scene;
}

void Player::Update(FLOAT deltaTime)
{

}

void Player::Init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	this->m_sprite = cocos2d::Sprite::create("Sprites/Main/Warrior_animations/Right_Side/PNG Sequences/Warrior_clothes_empty/Idle Blinking/0_Warrior_Idle Blinking_000.png");
	this->m_sprite->setPosition(Point(visibleSize.width / 1.5, visibleSize.height / 2));
	this->m_sprite->setScale(0.2);
	this->sceneGame->addChild(this->m_sprite);

	physicsBody = PhysicsBody::createBox(this->m_sprite->getContentSize());
	physicsBody->setDynamic(false);
	this->m_sprite->setPhysicsBody(physicsBody);
	physicsBody->setGravityEnable(false);
}

void Player::Collision()
{
}
cocos2d::RepeatForever* Player::MovingRight() {	return ObjectParent::AnimationObjectRepeat(2, "Warrior_Run");}
cocos2d::Animate* Player::AttackRight() { return ObjectParent::AnimationObjectOnce(6, "Warrior_Attack_2");}
cocos2d::RepeatForever* Player::IdleRight(){ return ObjectParent::AnimationObjectRepeat(1,"Warrior_Idle");}
cocos2d::RepeatForever* Player::AttackRightAngry(){	return ObjectParent::AnimationObjectRepeat(5, "Warrior_Attack_2");}
cocos2d::RepeatForever* Player::DieRight(){	return ObjectParent::AnimationObjectRepeat(4, "Warrior_Died");}
cocos2d::Animate* Player::HurtRight(){	return ObjectParent::AnimationObjectOnce(3, "Warrior_Hurt");}

void Player::updateLevel()
{
	health = Level * 100;
	dame = Level * 10;
}
