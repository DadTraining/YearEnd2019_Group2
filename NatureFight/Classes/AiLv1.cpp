#include "AiLv1.h"
#include <vector> 
#include <ResourceManager.h>
AiLv1::AiLv1(cocos2d::Scene* scene)
{
	sceneGame = scene;
}
float timeAttackAI = 0, timeDieAI = 0;
bool checkAttackAI = false;
void AiLv1::Update(float deltaTime)
{
	if (m_health <= 0) {
		timeDieAI += deltaTime;
		SetState(ACTION_DIE);
		if (timeDieAI >= 5) {
			timeDieAI = 0;
			m_sprite->setPosition(10, 10);
			m_CurrentState = ACTION_DEFAULT;
			m_CurrentFace = FACE_DEFAULT;
			edgeNode->setPosition(Vec2(1000, 1000));
			physicsBodyChar->setEnabled(true);
		}
	}
	else {
		if (m_CurrentState == ACTION_ATTACK) checkAttackAI = true;
		if (checkAttackAI) timeAttackAI += deltaTime;
		if (timeAttackAI > 1.0f) {
			m_CurrentState = ACTION_DEFAULT;
			timeAttackAI = 0;
			checkAttackAI = false;
		}
		if (timeAttackAI > deltaTime) {
			edgeNode->setPosition(Vec2(1000, 1000));
		}
		SetFace();
	}
}


void AiLv1::Init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->m_sprite = cocos2d::Sprite::create("Sprites/Main/Warrior_animations/Right_Side/PNG_Sequences/Warrior_clothes_empty/Idle_Blinking/0_Warrior_Idle_000.png");
	this->m_sprite->setPosition(Point(visibleSize.width / 1.2, visibleSize.height / 1.2));
	this->m_sprite->setScale(0.1);
	this->sceneGame->addChild(this->m_sprite);
	physicsBodyChar = PhysicsBody::createBox(this->m_sprite->getContentSize() / 3, PhysicsMaterial(0.1f, 1.0f, 0.0f));
	physicsBodyChar->setDynamic(true);
	physicsBodyChar->setRotationEnable(false);
	physicsBodyChar->setCollisionBitmask(101);
	physicsBodyChar->setContactTestBitmask(1);
	this->m_sprite->setPhysicsBody(physicsBodyChar);
	this->m_sprite->setTag(CREEPTAG);
	physicsBodyChar->setGravityEnable(false);
	m_CurrentState = ACTION_IDLE;
	m_CurrentFace = FACE_DEFAULT;

	auto edgeBody = PhysicsBody::createEdgeBox(Size(20, 20));
	edgeBody->setContactTestBitmask(1);
	edgeNode = Node::create();
	edgeNode->setPosition(m_sprite->getPosition());
	sceneGame->addChild(edgeNode);
	edgeNode->setPhysicsBody(edgeBody);
	edgeNode->setTag(CREEPATTACK);
}

float timem = 0;
void AiLv1::Collision(Player* player, float deltaTime)
{
	Update(deltaTime);
	if ((Distance(this->m_sprite->getPosition(), player->m_sprite->getPosition())) <= 80) {
		timem += deltaTime;
		if (timem >= 1.5) {
			SetState(AiLv1::ACTION_ATTACK);
			timem = 0;
		}
	}
	else if ((Distance(this->m_sprite->getPosition(), player->m_sprite->getPosition())) < 100 && (Distance(this->m_sprite->getPosition(), player->m_sprite->getPosition())) > 80) {
		this->physicsBodyChar->setVelocity((player->m_sprite->getPosition() - this->m_sprite->getPosition()) / 2);
		timem += deltaTime;
		if (timem >= 1) {
			SetState(AiLv1::ACTION_MOVE);
		}
	}
	else
	{
		timem += deltaTime;
		if (timem >= 1) {
			SetState(AiLv1::ACTION_IDLE);
			timem = 0;
		}
	}
}

void AiLv1::SetIdle(int state) {
	if (state != m_CurrentState) {
		m_sprite->stopAllActions();
		m_sprite->runAction(IdleRight());
	}
	else if (m_sprite->getNumberOfRunningActions() == 0) {
		m_sprite->runAction(IdleRight());
	}

}
void AiLv1::SetDie(int state)
{
	if (state != m_CurrentState) {
		m_sprite->stopAllActions();
		m_sprite->runAction(DieRight());
	}
	else if (m_sprite->getNumberOfRunningActions() == 0) {
		m_sprite->runAction(DieRight());
	}
	physicsBodyChar->setEnabled(false);
}
void AiLv1::SetAttack(int state) {
	switch (m_CurrentFace)
	{
	case FACE_LEFT:
		if (state != m_CurrentState) {
			m_sprite->stopAllActions();
			m_sprite->runAction(AttackRight());
			edgeNode->setPosition(m_sprite->getPosition() + Vec2(-20, 0));
		}
		else if (m_sprite->getNumberOfRunningActions() == 0) {
			m_sprite->runAction(AttackRight());
			edgeNode->setPosition(m_sprite->getPosition() + Vec2(-20, 0));
		}
		break;
	case FACE_RIGHT:
		if (state != m_CurrentState) {
			m_sprite->stopAllActions();
			m_sprite->runAction(AttackRight());
			edgeNode->setPosition(m_sprite->getPosition() + Vec2(20, 0));

		}
		else if (m_sprite->getNumberOfRunningActions() == 0) {
			m_sprite->runAction(AttackRight());
			edgeNode->setPosition(m_sprite->getPosition() + Vec2(20, 0));
		}
		break;
	case FACE_UP:
		if (state != m_CurrentState) {
			m_sprite->stopAllActions();
			m_sprite->runAction(AttackRight());
			edgeNode->setPosition(m_sprite->getPosition() + Vec2(0, 20));
		}
		else if (m_sprite->getNumberOfRunningActions() == 0) {
			m_sprite->runAction(AttackRight());
			edgeNode->setPosition(m_sprite->getPosition() + Vec2(0, 20));
		}
		break;
	case FACE_DOWN:
		if (state != m_CurrentState) {
			m_sprite->stopAllActions();
			m_sprite->runAction(AttackRight());
			edgeNode->setPosition(m_sprite->getPosition() + Vec2(0, -20));
		}
		else if (m_sprite->getNumberOfRunningActions() == 0) {
			m_sprite->runAction(AttackRight());
			edgeNode->setPosition(m_sprite->getPosition() + Vec2(0, -20));
		}
		break;
	}
}
void AiLv1::SetHurt(int state) {
	m_sprite->stopAllActions();
	m_sprite->runAction(HurtRight());
	m_health -= 10;
	CCLOG("%d", m_health);
}
void AiLv1::SetMove(int state)
{
	if (state != m_CurrentState) {
		m_sprite->stopAllActions();
		m_sprite->runAction(MovingRight());
	}
	else if (m_sprite->getNumberOfRunningActions() == 0) {
		m_sprite->runAction(MovingRight());
	}
}
void AiLv1::SetState(int state)
{
	if (!((m_CurrentState == ACTION_ATTACK) && m_sprite->getNumberOfRunningActions() > 0))
	{
		switch (state) {
		case ACTION_IDLE:
			SetIdle(state);
			break;
		case ACTION_MOVE:
			SetMove(state);
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

void AiLv1::SetFace()
{
	float radian = std::atan2f(physicsBodyChar->getVelocity().y, physicsBodyChar->getVelocity().x);
	if (physicsBodyChar->getVelocity().x == 0 && physicsBodyChar->getVelocity().y == 0) {
		SetState(AiLv1::ACTION_IDLE);
	}
	else {
		if (radian >= -M_PI / 4 && radian <= M_PI / 4) m_CurrentFace = FACE_RIGHT;
		else if (radian >= M_PI / 4 && radian <= 3 * M_PI / 4) m_CurrentFace = FACE_UP;
		else if ((radian >= 3 * M_PI / 4 && radian <= M_PI) || (radian <= -3 * M_PI / 4 && radian >= -M_PI)) m_CurrentFace = FACE_LEFT;
		else if (radian >= -3 * M_PI / 4 && radian <= -M_PI / 4) m_CurrentFace = FACE_DOWN;
		if (physicsBodyChar->getVelocity().x > 0) m_sprite->setFlipX(false);
		else m_sprite->setFlipX(true);
		SetState(AiLv1::ACTION_MOVE);
	}
}

cocos2d::RepeatForever* AiLv1::MovingRight() {
	return ObjectParent::AnimationObjectRepeat(2, "Warrior_Run");
}
cocos2d::Animate* AiLv1::AttackRight() {
	return ObjectParent::AnimationObjectOnce(6, "Warrior_Attack_2");
}
cocos2d::RepeatForever* AiLv1::IdleRight() {
	return ObjectParent::AnimationObjectRepeat(1, "Warrior_Idle");
}
cocos2d::Animate* AiLv1::AttackRightAngry() {
	return ObjectParent::AnimationObjectOnce(5, "Warrior_Attack_2");
}
cocos2d::RepeatForever* AiLv1::DieRight() {
	return ObjectParent::AnimationObjectRepeat(4, "Warrior_Died");
}
cocos2d::Animate* AiLv1::HurtRight() {
	return ObjectParent::AnimationObjectOnce(3, "Warrior_Hurt");
}
cocos2d::RepeatForever* AiLv1::MovingUp() { return NULL; }
cocos2d::Animate* AiLv1::AttackUp() { return NULL; }
cocos2d::RepeatForever* AiLv1::IdleUp() { return NULL; }
cocos2d::Animate* AiLv1::AttackUpAngry() { return NULL; }
cocos2d::Animate* AiLv1::HurtUp() { return NULL; }
cocos2d::RepeatForever* AiLv1::DieUp() { return NULL; }
cocos2d::RepeatForever* AiLv1::MovingDown() { return NULL; }
cocos2d::Animate* AiLv1::AttackDown() { return NULL; }
cocos2d::RepeatForever* AiLv1::IdleDown() { return NULL; }
cocos2d::Animate* AiLv1::AttackDownAngry() { return NULL; }
cocos2d::Animate* AiLv1::HurtDown() { return NULL; }
cocos2d::RepeatForever* AiLv1::DieDown() { return NULL; }

float AiLv1::Distance(Vec2 A, Vec2 C) {
	return std::sqrt((A.x - C.x) * (A.x - C.x) + (A.y - C.y) * (A.y - C.y));
}