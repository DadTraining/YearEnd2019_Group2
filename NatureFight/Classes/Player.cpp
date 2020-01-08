#include <Player.h>
#include "SimpleAudioEngine.h"
#define ATTACK 0
#define RUN 1
#define playertag 1000
#define ATTACKTAG 8
#define NpcSolotag 11
#define NpcYolotag 12
using namespace CocosDenshion;
int Player::Level;
int Player::Exp;
Player::Player(cocos2d::Scene* scene)
{
	sceneGame = scene;
}
float timeAttack = 0, timeDie = 0;
bool checkAttack = false;
void Player::Update(float deltaTime)
{
	
		SetFace();
}

void Player::Init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Level = 1;
	Exp = 0;
	CCLOG("Player 0******************");
	updateLevel();
	CCLOG("Player 1******************");
	this->m_sprite = cocos2d::Sprite::create("Sprites/Main/Warrior_animations/Right_Side/PNG_Sequences/Warrior_clothes_empty/Idle_Blinking/0_Warrior_Idle_000.png");
	this->m_sprite->setPosition(10, 10);
	this->m_sprite->setScale(0.1);
	this->sceneGame->addChild(this->m_sprite, 1);
	CCLOG("Player 3******************");
	physicsBody = PhysicsBody::createBox(this->m_sprite->getContentSize() / 2);
	//physicsBody->setDynamic(true);
	physicsBody->setRotationEnable(false);
	physicsBody->setCollisionBitmask(Model::BITMASK_PLAYER);
	physicsBody->setContactTestBitmask(1);
	this->m_sprite->setPhysicsBody(physicsBody);
	this->m_sprite->setTag(playertag);
	physicsBody->setGravityEnable(false);
	CCLOG("Player 4******************");
	m_CurrentState = ACTION_IDLE;
	CCLOG("Player 5******************");
	m_CurrentFace = FACE_DEFAULT;
	CCLOG("Player 6******************");

	auto edgeBody = PhysicsBody::createEdgeBox(Size(20, 20));
	edgeBody->setContactTestBitmask(Model::BITMASK_PLAYER);
	edgeBody->setCollisionBitmask(false);
	edgeNode = Node::create();
	CCLOG("Player 7******************");
	edgeNode->setPosition(m_sprite->getPosition());
	sceneGame->addChild(edgeNode);
	CCLOG("Player 8******************");
	edgeNode->setPhysicsBody(edgeBody);
	CCLOG("Player 9******************");
	edgeNode->setTag(ATTACKTAG);
	CCLOG("Player end******************");
}

void Player::Collision()
{
}

void Player::updateLevel()
{
	m_health = Level * 300;
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
void Player::SetDie(int state)
{
	switch (m_CurrentFace) {
	case FACE_RIGHT:
	case FACE_LEFT:
		if (state != m_CurrentState) {
			m_sprite->stopAllActions();
			m_sprite->runAction(DieRight());
		}
		else if (m_sprite->getNumberOfRunningActions() == 0) {
			m_sprite->runAction(DieRight());
		}
		break;
	case FACE_UP:
		if (state != m_CurrentState) {
			m_sprite->stopAllActions();
			m_sprite->runAction(DieUp());
		}
		else if (m_sprite->getNumberOfRunningActions() == 0) {
			m_sprite->runAction(DieUp());
		}
		break;
	case FACE_DOWN:
		if (state != m_CurrentState) {
			m_sprite->stopAllActions();
			m_sprite->runAction(DieDown());
		}
		else if (m_sprite->getNumberOfRunningActions() == 0) {
			m_sprite->runAction(DieDown());
		}
		break;
	}
	physicsBody->setEnabled(false);
}
void Player::SetAttack(int state) {
	switch (m_CurrentFace)
	{
	case FACE_LEFT:
		if (state != m_CurrentState) {
			m_sprite->stopAllActions();
			m_sprite->runAction(AttackRight());
			edgeNode->setRotation(0);
			edgeNode->setPosition(m_sprite->getPosition() + Vec2(-20, 0));
		}
		else if (m_sprite->getNumberOfRunningActions() == 0) {
			m_sprite->runAction(AttackRight());
			edgeNode->setRotation(0);
			edgeNode->setPosition(m_sprite->getPosition() + Vec2(-20, 0));
		}
		break;
	case FACE_RIGHT:
		if (state != m_CurrentState) {
			m_sprite->stopAllActions();
			m_sprite->runAction(AttackRight());
			edgeNode->setRotation(0);
			edgeNode->setPosition(m_sprite->getPosition() + Vec2(20, 0));

		}
		else if (m_sprite->getNumberOfRunningActions() == 0) {
			m_sprite->runAction(AttackRight());
			edgeNode->setRotation(0);
			edgeNode->setPosition(m_sprite->getPosition() + Vec2(20, 0));
		}
		break;
	case FACE_UP:
		if (state != m_CurrentState) {
			m_sprite->stopAllActions();
			m_sprite->runAction(AttackUp());
			edgeNode->setRotation(90);
			edgeNode->setPosition(m_sprite->getPosition() + Vec2(0, 20));
		}
		else if (m_sprite->getNumberOfRunningActions() == 0) {
			m_sprite->runAction(AttackUp());
			edgeNode->setRotation(90);
			edgeNode->setPosition(m_sprite->getPosition() + Vec2(0, 20));
		}
		break;
	case FACE_DOWN:
		if (state != m_CurrentState) {
			m_sprite->stopAllActions();
			m_sprite->runAction(AttackDown());
			edgeNode->setRotation(90);
			edgeNode->setPosition(m_sprite->getPosition() + Vec2(0, -20));
		}
		else if (m_sprite->getNumberOfRunningActions() == 0) {
			m_sprite->runAction(AttackDown());
			edgeNode->setRotation(90);
			edgeNode->setPosition(m_sprite->getPosition() + Vec2(0, -20));
		}
		break;
	}
	auto particleSystem = ParticleSystemQuad::create("Particles/power.plist");
	particleSystem->setPosition(edgeNode->getPosition());
	particleSystem->setDuration(ParticleSystem::DURATION_INFINITY);
	particleSystem->setScale(0.3f);
	sceneGame->addChild(particleSystem, 10);
}
void Player::SetHurt(int state) {
	switch (m_CurrentFace) {
	case FACE_LEFT:
	case FACE_RIGHT:
		m_sprite->stopAllActions();
		m_sprite->runAction(HurtRight());
		m_health -= 10;
		break;
	case FACE_UP:
		m_sprite->stopAllActions();
		m_sprite->runAction(HurtUp());
		m_health -= 10;
		break;
	case FACE_DOWN:
		m_sprite->stopAllActions();
		m_sprite->runAction(HurtDown());
		m_health -= 10;
	}
	CCLOG("%d", m_health);
}
void Player::SetState(int state)
{
	if (!((m_CurrentState == ACTION_ATTACK) && m_sprite->getNumberOfRunningActions() > 0))
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
			break;
		case ACTION_DIE:
			SetDie(state);
		}
		m_CurrentState = state;
	}
}

void Player::SetFace()
{
	float radian = std::atan2f(physicsBody->getVelocity().y, physicsBody->getVelocity().x);
	if (physicsBody->getVelocity().x == 0 && physicsBody->getVelocity().y == 0) {
		SetState(Player::ACTION_IDLE);
	}
	else if (radian >= -M_PI / 4 && radian <= M_PI / 4) {
		m_sprite->setFlipX(false);
		m_CurrentFace = FACE_RIGHT;
		SetState(Player::ACTION_MOVE);
	}
	else if (radian >= M_PI / 4 && radian <= 3 * M_PI / 4) {
		m_CurrentFace = FACE_UP;
		SetState(Player::ACTION_MOVEUP);
	}
	else if ((radian >= 3 * M_PI / 4 && radian <= M_PI) || (radian <= -3 * M_PI / 4 && radian >= -M_PI)) {
		m_sprite->setFlipX(true);
		m_CurrentFace = FACE_LEFT;
		SetState(Player::ACTION_MOVE);
	}
	else if (radian >= -3 * M_PI / 4 && radian <= -M_PI / 4) {
		m_CurrentFace = FACE_DOWN;
		SetState(Player::ACTION_MOVEDOWN);
	}
}

cocos2d::RepeatForever* Player::MovingRight() {
	return ObjectParent::AnimationObjectRepeat(2, "Warrior_Run");
}
cocos2d::Animate* Player::AttackRight() {
	return ObjectParent::AnimationObjectOnce(6, "Warrior_Attack_1");
}
cocos2d::RepeatForever* Player::IdleRight() {
	return ObjectParent::AnimationObjectRepeat(1, "Warrior_Idle");
}
cocos2d::Animate* Player::AttackRightAngry() {
	return ObjectParent::AnimationObjectOnce(5, "Warrior_Attack_2");
}
cocos2d::RepeatForever* Player::DieRight() {
	return ObjectParent::AnimationObjectRepeat(4, "Warrior_Died");
}
cocos2d::Animate* Player::HurtRight() {
	return ObjectParent::AnimationObjectOnce(3, "Warrior_Hurt");
}
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
