#include "BossLv1.h"
#include <vector> 
#include <ResourceManager.h>
BossLv1::BossLv1(cocos2d::Scene* scene)
{
	sceneGame = scene;
}
float timeAttackBoss = 0, timeDieBoss = 0, timeColorBoss = 0;
bool checkAttackBoss = false;
void BossLv1::Update(float deltaTime)
{
	if (m_health <= 0) {
		timeDieBoss += deltaTime;
		SetState(ACTION_DIE);
		if (timeDieBoss >= 5) {
			timeDieBoss = 0;
			m_sprite->setPosition(10, 10);
			m_CurrentState = ACTION_DEFAULT;
			m_CurrentFace = FACE_DEFAULT;
			edgeNode->setPosition(Vec2(1000, 1000));
			physicsBodyChar->setEnabled(true);
		}
	}
	else {
		if (m_CurrentState == ACTION_ATTACK) checkAttackBoss = true;
		if (checkAttackBoss) timeAttackBoss += deltaTime;
		if (timeAttackBoss > 1.0f) {
			m_CurrentState = ACTION_DEFAULT;
			timeAttackBoss = 0;
			checkAttackBoss = false;
		}
		if (timeAttackBoss > deltaTime) {
			edgeNode->setPosition(Vec2(1000, 1000));
		}
		SetFace();
	}
	if (!(m_sprite->getColor() == ccc3(255, 255, 255))) {
		timeColorBoss += deltaTime;
		if (timeColorBoss >= 2) {
			m_sprite->setColor(ccc3(255, 255, 255));
			timeColorBoss = 0;
		}
	}

}


void BossLv1::Init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->m_sprite = cocos2d::Sprite::create("Sprites/Man1/Ogre/PNG/PNG_Sequences/Idle/0_Ogre_Idle_000.png");
	this->m_sprite->setPosition(Point(visibleSize.width , visibleSize.height ));
	this->m_sprite->setScale(0.1);
	this->sceneGame->addChild(this->m_sprite);
	physicsBodyChar = PhysicsBody::createBox(this->m_sprite->getContentSize() / 3, PhysicsMaterial(0.1f, 1.0f, 0.0f));
	physicsBodyChar->setDynamic(true);
	physicsBodyChar->setRotationEnable(false);
	physicsBodyChar->setCollisionBitmask(101);
	physicsBodyChar->setContactTestBitmask(1);
	this->m_sprite->setPhysicsBody(physicsBodyChar);
	this->m_sprite->setTag(BOSSTAG);
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

float timeAtt = 0;
void BossLv1::Collision(Player* player, float deltaTime)
{
	Update(deltaTime);
	timeAtt += deltaTime;
	if ((Distance(this->m_sprite->getPosition(), player->m_sprite->getPosition())) <= 80) {
		this->m_sprite->getPhysicsBody()->setVelocity(Vec2(0, 0));
		if (timeAtt >= 2)
		{
			SetState(BossLv1::ACTION_ATTACK);
			timeAtt = 0;
		}
	}
	else if ((Distance(this->m_sprite->getPosition(), player->m_sprite->getPosition())) < 100 && (Distance(this->m_sprite->getPosition(), player->m_sprite->getPosition())) > 80) {
		this->physicsBodyChar->setVelocity((player->m_sprite->getPosition() - this->m_sprite->getPosition()) / 2);
		SetState(BossLv1::ACTION_MOVE);
	}
	else
	{
		SetState(BossLv1::ACTION_IDLE);
	}
	//if (this->m_health <= 0) {
	//	this->SetState(AiLv1::ACTION_DIE);
	//	this->physicsBodyChar->setEnabled(false);
	//	player->Exp += 20;
	//}
}

void BossLv1::SetIdle(int state) {
	if (state != m_CurrentState) {
		m_sprite->stopAllActions();
		m_sprite->getPhysicsBody()->setVelocity(Vec2(0, 0));
		m_sprite->runAction(IdleRight());
	}
	else if (m_sprite->getNumberOfRunningActions() == 0) {
		m_sprite->runAction(IdleRight());
	}

}
void BossLv1::SetDie(int state)
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
void BossLv1::SetAttack(int state) {
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
void BossLv1::SetHurt(int state, int skill) {
	if (state != m_CurrentState) {
		m_sprite->stopAllActions();
		m_health -= 10;
		if (skill == NORMALSKILL) {
			m_sprite->setColor(ccc3(255, 0, 0));
		}
		else if (skill == SKILLICE) {
			m_sprite->setColor(ccc3(0, 0, 255));
		}
		else if (skill == SKILLFIRE) {
			m_sprite->setColor(ccc3(255, 0, 0));
		}
	}
	else if (m_sprite->getNumberOfRunningActions() == 0) {
		m_sprite->runAction(HurtRight());
		m_health -= 10;
	}
	CCLOG("%d", m_health);
}
void BossLv1::SetMove(int state)
{
	if (state != m_CurrentState) {
		m_sprite->stopAllActions();
		m_sprite->runAction(MovingRight());
	}
	else if (m_sprite->getNumberOfRunningActions() == 0) {
		m_sprite->runAction(MovingRight());
	}
}
void BossLv1::SetState(int state)
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
			SetHurt(state, NORMALSKILL);
			break;
		case ACTION_DIE:
			SetDie(state);
		case ACTION_HURT_ICE:
			SetHurt(state, SKILLICE);
		}
		m_CurrentState = state;
	}
}

void BossLv1::SetFace()
{
	float radian = std::atan2f(physicsBodyChar->getVelocity().y, physicsBodyChar->getVelocity().x);
	if (physicsBodyChar->getVelocity().x == 0 && physicsBodyChar->getVelocity().y == 0) {
		SetState(BossLv1::ACTION_IDLE);
	}
	else {
		if (radian >= -M_PI / 4 && radian <= M_PI / 4) m_CurrentFace = FACE_RIGHT;
		else if (radian >= M_PI / 4 && radian <= 3 * M_PI / 4) m_CurrentFace = FACE_UP;
		else if ((radian >= 3 * M_PI / 4 && radian <= M_PI) || (radian <= -3 * M_PI / 4 && radian >= -M_PI)) m_CurrentFace = FACE_LEFT;
		else if (radian >= -3 * M_PI / 4 && radian <= -M_PI / 4) m_CurrentFace = FACE_DOWN;
		if (physicsBodyChar->getVelocity().x > 0) m_sprite->setFlipX(false);
		else m_sprite->setFlipX(true);
		SetState(BossLv1::ACTION_MOVE);
	}
}

cocos2d::RepeatForever* BossLv1::MovingRight() {
	return ObjectParent::AnimationObjectRepeat(107, "Ogre_Running", AttackSpeed);
}
cocos2d::Animate* BossLv1::AttackRight() {
	return ObjectParent::AnimationObjectOnce(108, "Ogre_Slashing", AttackSpeed);
}
cocos2d::RepeatForever* BossLv1::IdleRight() {
	return ObjectParent::AnimationObjectRepeat(106, "Ogre_Idle", AttackSpeed);
}
cocos2d::Animate* BossLv1::AttackRightAngry() {
	return ObjectParent::AnimationObjectOnce(105, "Ogre_Kicking", AttackSpeed);
}
cocos2d::RepeatForever* BossLv1::DieRight() {
	return ObjectParent::AnimationObjectRepeat(104, "Ogre_Dying", AttackSpeed);
}
cocos2d::Animate* BossLv1::HurtRight() {
	return ObjectParent::AnimationObjectOnce(103, "Ogre_Hurt",AttackSpeed);
}
cocos2d::RepeatForever* BossLv1::MovingUp() { return NULL; }
cocos2d::Animate* BossLv1::AttackUp() { return NULL; }
cocos2d::RepeatForever* BossLv1::IdleUp() { return NULL; }
cocos2d::Animate* BossLv1::AttackUpAngry() { return NULL; }
cocos2d::Animate* BossLv1::HurtUp() { return NULL; }
cocos2d::RepeatForever* BossLv1::DieUp() { return NULL; }
cocos2d::RepeatForever* BossLv1::MovingDown() { return NULL; }
cocos2d::Animate* BossLv1::AttackDown() { return NULL; }
cocos2d::RepeatForever* BossLv1::IdleDown() { return NULL; }
cocos2d::Animate* BossLv1::AttackDownAngry() { return NULL; }
cocos2d::Animate* BossLv1::HurtDown() { return NULL; }
cocos2d::RepeatForever* BossLv1::DieDown() { return NULL; }

float BossLv1::Distance(Vec2 A, Vec2 C) {
	return std::sqrt((A.x - C.x) * (A.x - C.x) + (A.y - C.y) * (A.y - C.y));
}