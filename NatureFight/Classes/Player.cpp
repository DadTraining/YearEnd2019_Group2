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
	SetFace();
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

	m_CurrentState = ACTION_IDLE;
	m_CurrentFace = FACE_RIGHT;
}

void Player::Collision()
{
}

void Player::updateLevel()
{
	m_health = Level * 100;
	m_dame = Level * 10;
}
void Player::SetIdle(int state) {
	switch (m_CurrentFace) {
	case FACE_RIGHT:
	case FACE_LEFT:
		if (state != m_CurrentState) {
			m_sprite->stopAllActions();
			m_sprite->runAction(IdleRight());
		}
		else if (m_sprite->getNumberOfRunningActions() == 0) {
			m_sprite->runAction(IdleRight());
		}
		break;
	case FACE_UP:
		if (state != m_CurrentState) {
			m_sprite->stopAllActions();
			m_sprite->runAction(IdleUp());
		}
		else if (m_sprite->getNumberOfRunningActions() == 0) {
			m_sprite->runAction(IdleUp());
		}
		break;
	case FACE_DOWN:
		if (state != m_CurrentState) {
			m_sprite->stopAllActions();
			m_sprite->runAction(IdleDown());
		}
		else if (m_sprite->getNumberOfRunningActions() == 0) {
			m_sprite->runAction(IdleDown());
		}
		break;
	}

}
void Player::SetAttack(int state) {
	switch (m_CurrentFace)
	{
	case FACE_LEFT:
	case FACE_RIGHT:
		if (state != m_CurrentState) {
			m_sprite->stopAllActions();
			m_sprite->runAction(AttackDown());
		}
		else if (m_sprite->getNumberOfRunningActions() == 0) {
			m_sprite->runAction(MovingUp());
		}
		break;
	case FACE_UP:

		break;
	case FACE_DOWN:

		break;
	}
}
void Player::SetHurt(int state) {
	switch (m_CurrentFace) {
	case FACE_LEFT:
	case FACE_RIGHT:
		if (state != m_CurrentState) //one time
		{
			m_sprite->stopAllActions();
			m_sprite->runAction(HurtRight());
			m_health -= 10;
			if (m_health <= 0)
			{
				m_sprite->stopAllActions();
				m_sprite->runAction(DieRight());
			}
		}
		break;
	case FACE_UP:
		if (state != m_CurrentState) //one time
		{
			m_sprite->stopAllActions();
			m_sprite->runAction(HurtUp());
			m_health -= 10;
			if (m_health <= 0)
			{
				m_sprite->stopAllActions();
				m_sprite->runAction(DieUp());
			}
		}
		break;
	case FACE_DOWN:
		if (state != m_CurrentState) //one time
		{
			m_sprite->stopAllActions();
			m_sprite->runAction(HurtDown());
			m_health -= 10;
			if (m_health <= 0)
			{
				m_sprite->stopAllActions();
				m_sprite->runAction(DieDown());
			}
		}
		break;
	}
}
void Player::SetState(int state)
{
	if (!((m_CurrentState == ACTION_ATTACK || m_CurrentState == ACTION_ATTACKDOWN || m_CurrentState == ACTION_ATTACKUP)
		&& m_sprite->getNumberOfRunningActions() > 0))
	{
		switch (state) {
		case ACTION_IDLE:
			SetIdle(state);
			break;
		case ACTION_MOVE:
			if (state != m_CurrentState) {
				m_sprite->stopAllActions();
				m_sprite->runAction(MovingRight());
			}
			else if (m_sprite->getNumberOfRunningActions() == 0) {
				m_sprite->runAction(MovingRight());
			}
			break;
		case ACTION_MOVEDOWN:
			if (state != m_CurrentState) {
				m_sprite->stopAllActions();
				m_sprite->runAction(MovingDown());
			}
			else if (m_sprite->getNumberOfRunningActions() == 0) {
				m_sprite->runAction(MovingDown());
			}
			break;
		case ACTION_MOVEUP:
			if (state != m_CurrentState) {
				m_sprite->stopAllActions();
				m_sprite->runAction(MovingUp());
			}
			else if (m_sprite->getNumberOfRunningActions() == 0) {
				m_sprite->runAction(MovingUp());
			}
			break;

		case ACTION_ATTACK:
			SetAttack(state);
			break;
		case ACTION_HURT:
			SetHurt(state);
		}
		m_CurrentState = state;
	}
}

int Player::SetAction()
{
	return 0;
}

void Player::SetFace()
{
	if (physicsBody->getVelocity().x <= 100 && physicsBody->getVelocity().x >= -100 && physicsBody->getVelocity().y < 0) {
		if (m_CurrentFace != FACE_DOWN) {
			m_CurrentFace = FACE_DOWN;
			SetState(Player::ACTION_MOVEDOWN);
		}
	}
	else if (physicsBody->getVelocity().x <= 100 && physicsBody->getVelocity().x >= -100 && physicsBody->getVelocity().y > 0) {
		if (m_CurrentFace != FACE_UP) {
			m_CurrentFace = FACE_UP;
			SetState(Player::ACTION_MOVEUP);
		}
	}
	else if (physicsBody->getVelocity().x < 0) {
		if (m_CurrentFace != FACE_LEFT) {
			m_sprite->setFlipX(true);
			m_CurrentFace = FACE_LEFT;
			SetState(Player::ACTION_MOVE);
		}
	}
	else if (physicsBody->getVelocity().x > 0) {
		if (m_CurrentFace != FACE_RIGHT) {
			m_sprite->setFlipX(false);
			m_CurrentFace = FACE_RIGHT;
			SetState(Player::ACTION_MOVE);
		}
	}
	else if (physicsBody->getVelocity().x == 0 && physicsBody->getVelocity().x == 0) {
		SetState(Player::ACTION_IDLE);
	}
}
cocos2d::RepeatForever* Player::MovingRight() { return ObjectParent::AnimationObjectRepeat(2, "Warrior_Run"); }
cocos2d::Animate* Player::AttackRight() { return ObjectParent::AnimationObjectOnce(6, "Warrior_Attack_2"); }
cocos2d::RepeatForever* Player::IdleRight() { return ObjectParent::AnimationObjectRepeat(1, "Warrior_Idle"); }
cocos2d::Animate* Player::AttackRightAngry() { return ObjectParent::AnimationObjectOnce(5, "Warrior_Attack_2"); }
cocos2d::RepeatForever* Player::DieRight() { return ObjectParent::AnimationObjectRepeat(4, "Warrior_Died"); }
cocos2d::Animate* Player::HurtRight() { return ObjectParent::AnimationObjectOnce(3, "Warrior_Hurt"); }
cocos2d::RepeatForever* Player::MovingUp()
{
	return ObjectParent::AnimationObjectRepeat(8, "Warrior_Run");
}
cocos2d::Animate* Player::AttackUp()
{
	return ObjectParent::AnimationObjectOnce(12, "Warrior_Attack_1");
}
cocos2d::RepeatForever* Player::IdleUp()
{
	return ObjectParent::AnimationObjectRepeat(7, "Warrior_Idle");
}
cocos2d::Animate* Player::AttackUpAngry()
{
	return ObjectParent::AnimationObjectOnce(11, "Warrior_Attack_2");
}
cocos2d::Animate* Player::HurtUp()
{
	return ObjectParent::AnimationObjectOnce(9, "Warrior_Hurt");
}
cocos2d::RepeatForever* Player::DieUp()
{
	return ObjectParent::AnimationObjectRepeat(10, "Warrior_Died");
}
cocos2d::RepeatForever* Player::MovingDown()
{
	return ObjectParent::AnimationObjectRepeat(14, "Warrior_Run");
}
cocos2d::Animate* Player::AttackDown()
{
	return ObjectParent::AnimationObjectOnce(18, "Warrior_Attack_1");
}
cocos2d::RepeatForever* Player::IdleDown()
{
	return ObjectParent::AnimationObjectRepeat(13, "Warrior_Idle");
}
cocos2d::Animate* Player::AttackDownAngry()
{
	return ObjectParent::AnimationObjectOnce(17, "Warrior_Attack_2");
}
cocos2d::Animate* Player::HurtDown()
{
	return ObjectParent::AnimationObjectOnce(15, "Warrior_Hurt");
}
cocos2d::RepeatForever* Player::DieDown()
{
	return ObjectParent::AnimationObjectRepeat(16, "Warrior_Died");
}
