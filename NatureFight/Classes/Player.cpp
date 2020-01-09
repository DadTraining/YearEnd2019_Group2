#include <Player.h>
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
int Player::Level;
int Player::Exp;
int Player::m_CurrentStone;
Player::Player(cocos2d::Scene* scene)
{
	sceneGame = scene;
}
float timeAttack = 0, timeDie = 0;
bool checkAttack = false;
void Player::Update(float deltaTime)
{
	if (m_health <= 0) {
		timeDie += deltaTime;
		SetState(ACTION_DIE);
		if (timeDie >= 5) {
			timeDie = 0;
			m_sprite->setPosition(10, 10);
			updateLevel();
			m_CurrentState = ACTION_DEFAULT;
			m_CurrentFace = FACE_DEFAULT;
			edgeNode->setPosition(Vec2(1000, 1000));
			physicsBody->setEnabled(true);
		}
	}
	else {
		if (m_CurrentState == ACTION_ATTACK) checkAttack = true;
		if(checkAttack) timeAttack += deltaTime;
		if (timeAttack > 2.0f-AttackSpeed) {
			m_CurrentState = ACTION_DEFAULT;
			timeAttack = 0;
			checkAttack = false;
		}
		if (timeAttack > deltaTime && m_CurrentSkill == SKILL_DEFAULT) {
			edgeNode->setPosition(Vec2(1000, 1000));
		}
		if (timeAttack > 0.15 && m_CurrentSkill == SKILL_FIRE) {
			edgeNode->setPosition(Vec2(1000, 1000));
		}
		if (timeAttack > 0.4 && m_CurrentSkill == SKILL_ICE) {
			edgeNode->setPosition(Vec2(1000, 1000));
		}
		SetFace();
	}
}

void Player::Init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Level = 1;
	Exp = 0;
	updateLevel();

	this->m_sprite = cocos2d::Sprite::create("Sprites/Main/Warrior_animations/Right_Side/PNG_Sequences/Warrior_clothes_empty/Idle_Blinking/0_Warrior_Idle_000.png");
	this->m_sprite->setPosition(10,10);
	this->m_sprite->setScale(0.1);
	this->sceneGame->addChild(this->m_sprite);
	physicsBody = PhysicsBody::createBox(this->m_sprite->getContentSize()/2);
	physicsBody->setDynamic(false);
	physicsBody->setRotationEnable(false);
	physicsBody->setCollisionBitmask(101);
	physicsBody->setContactTestBitmask(1);
	this->m_sprite->setPhysicsBody(physicsBody);
	this->m_sprite->setTag(playertag);
	physicsBody->setGravityEnable(false);
	m_CurrentState = ACTION_IDLE;
	m_CurrentFace = FACE_DEFAULT;
	m_CurrentSkill = SKILL_DEFAULT;

	edgeNode = Node::create();
	sceneGame->addChild(edgeNode);

}

void Player::Collision()
{
}

void Player::updateLevel()
{
	AttackSpeed = 1.0f + (Level-1)*0.5;
	MoveSpeed = 1.0f;
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
		}
		else if (m_sprite->getNumberOfRunningActions() == 0) {
			m_sprite->runAction(AttackRight());
		}
		break;
	case FACE_RIGHT:
		if (state != m_CurrentState) {
			m_sprite->stopAllActions();
			m_sprite->runAction(AttackRight());
		}
		else if (m_sprite->getNumberOfRunningActions() == 0) {
			m_sprite->runAction(AttackRight());
		}
		break;
	case FACE_UP:
		if (state != m_CurrentState) {
			m_sprite->stopAllActions();
			m_sprite->runAction(AttackUp());
		}
		else if (m_sprite->getNumberOfRunningActions() == 0) {
			m_sprite->runAction(AttackUp());
		}
		break;
	case FACE_DOWN:
		if (state != m_CurrentState) {
			m_sprite->stopAllActions();
			m_sprite->runAction(AttackDown());
		}
		else if (m_sprite->getNumberOfRunningActions() == 0) {
			m_sprite->runAction(AttackDown());
		}
		break;
	}
	m_CurrentSkill = SKILL_DEFAULT;
	if(Level>=1) SetSkill();
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
void Player::SetSkill()
{
	switch (m_CurrentSkill)
	{
	case SKILL_FIRE:
		SetSkillFire();
		break;
	case SKILL_ICE:
		SetSkillIce();
		break;
	default:
		SetSkillDefault();
		break;
	}
}
void Player::SetSkillFire()
{
	if (edgeNode->getTag() != ATTACK_FIRE) {
		auto edgeBody = PhysicsBody::createEdgeBox(Size(70, 70));
		edgeBody->setContactTestBitmask(1);
		edgeNode->setPhysicsBody(edgeBody);
		edgeNode->setPosition(m_sprite->getPosition());
		edgeNode->setTag(ATTACK_FIRE);
	}
	auto particleSystem = ParticleAttack("Particles/skill_fire.plist");
	particleSystem->setPosition(edgeNode->getPosition());
	sceneGame->addChild(particleSystem);
}
void Player::SetSkillIce()
{
	if (edgeNode->getTag() != ATTACK_ICE) {
		auto edgeBody = PhysicsBody::createEdgeBox(Size(30, 70));
		edgeBody->setContactTestBitmask(1);
		edgeNode->setPhysicsBody(edgeBody);
		edgeNode->setPosition(m_sprite->getPosition());
		edgeNode->setTag(ATTACK_ICE);
	}
	switch (m_CurrentFace)
	{
	case FACE_RIGHT:
		edgeNode->runAction(MoveBy::create(0.3f, Vec2(60, 0)));
		break;
	case FACE_UP:
		edgeNode->runAction(MoveBy::create(0.3f, Vec2(0, 60)));
		break;
	case FACE_DOWN:
		edgeNode->runAction(MoveBy::create(0.3f, Vec2(0, -60)));
		break;
	case FACE_LEFT:
		edgeNode->runAction(MoveBy::create(0.3f, Vec2(-60, 0)));
		break;
	}
	auto particleSystem = ParticleAttack("Particles/skill_ice.plist");
	particleSystem->setPosition(edgeNode->getPosition());
	sceneGame->addChild(particleSystem);
}
void Player::SetSkillDefault()
{
	if (edgeNode->getTag() != ATTACKTAG) {
		auto edgeBody = PhysicsBody::createEdgeBox(Size(25, 55));
		edgeBody->setContactTestBitmask(1);
		edgeNode->setPhysicsBody(edgeBody);
		edgeNode->setTag(ATTACKTAG);
	}
	auto particleSystem = ParticleAttack("Particles/PlayerAttack.plist");
	particleSystem->setPosition(edgeNode->getPosition());
	sceneGame->addChild(particleSystem);
}
void Player::UseStone(int stone)
{
	m_CurrentStone = stone;
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
	return ObjectParent::AnimationObjectRepeat(2, "Warrior_Run", AttackSpeed);
}
cocos2d::Animate* Player::AttackRight() {
	return ObjectParent::AnimationObjectOnce(6, "Warrior_Attack_1", AttackSpeed);
}
cocos2d::RepeatForever* Player::IdleRight() {
	return ObjectParent::AnimationObjectRepeat(1, "Warrior_Idle", AttackSpeed);
}
cocos2d::Animate* Player::AttackRightAngry() {
	return ObjectParent::AnimationObjectOnce(5, "Warrior_Attack_2", AttackSpeed);
}
cocos2d::RepeatForever* Player::DieRight() {
	return ObjectParent::AnimationObjectRepeat(4, "Warrior_Died", AttackSpeed);
}
cocos2d::Animate* Player::HurtRight() {
	return ObjectParent::AnimationObjectOnce(3, "Warrior_Hurt", AttackSpeed);
}
cocos2d::RepeatForever* Player::MovingUp()
{
	return ObjectParent::AnimationObjectRepeat(8, "Warrior_Run", AttackSpeed);
}
cocos2d::Animate* Player::AttackUp()
{
	return ObjectParent::AnimationObjectOnce(12, "Warrior_Attack_1", AttackSpeed);
}
cocos2d::RepeatForever* Player::IdleUp()
{
	return ObjectParent::AnimationObjectRepeat(7, "Warrior_Idle", AttackSpeed);
}
cocos2d::Animate* Player::AttackUpAngry()
{
	return ObjectParent::AnimationObjectOnce(11, "Warrior_Attack_2", AttackSpeed);
}
cocos2d::Animate* Player::HurtUp()
{
	return ObjectParent::AnimationObjectOnce(9, "Warrior_Hurt", AttackSpeed);
}
cocos2d::RepeatForever* Player::DieUp()
{
	return ObjectParent::AnimationObjectRepeat(10, "Warrior_Died", AttackSpeed);
}
cocos2d::RepeatForever* Player::MovingDown()
{
	return ObjectParent::AnimationObjectRepeat(14, "Warrior_Run", AttackSpeed);
}
cocos2d::Animate* Player::AttackDown()
{
	return ObjectParent::AnimationObjectOnce(18, "Warrior_Attack_1", AttackSpeed);
}
cocos2d::RepeatForever* Player::IdleDown()
{
	return ObjectParent::AnimationObjectRepeat(13, "Warrior_Idle", AttackSpeed);
}
cocos2d::Animate* Player::AttackDownAngry()
{
	return ObjectParent::AnimationObjectOnce(17, "Warrior_Attack_2", AttackSpeed);
}
cocos2d::Animate* Player::HurtDown()
{
	return ObjectParent::AnimationObjectOnce(15, "Warrior_Hurt", AttackSpeed);
}
cocos2d::RepeatForever* Player::DieDown()
{
	return ObjectParent::AnimationObjectRepeat(16, "Warrior_Died", AttackSpeed);
}

cocos2d::ParticleSystemQuad* Player::ParticleAttack(std::string name)
{
	auto particleSystem = ParticleSystemQuad::create(name);
	particleSystem->setScale(0.2f);
	particleSystem->setDuration(0.15f);
	switch (m_CurrentFace)
	{
	case FACE_LEFT:
		particleSystem->setAngle(180);
		edgeNode->setRotation(0);
		edgeNode->setPosition(m_sprite->getPosition() + Vec2(-20, 0));
		break;
	case FACE_RIGHT:
		edgeNode->setRotation(0);
		edgeNode->setPosition(m_sprite->getPosition() + Vec2(20, 0));
		break;
	case FACE_UP:
		particleSystem->setPosVar(Vec2(particleSystem->getPosVar().y, particleSystem->getPosVar().x));
		particleSystem->setGravity(Vec2(particleSystem->getGravity().y, particleSystem->getGravity().x));
		particleSystem->setAngle(90);
		edgeNode->setRotation(90);
		edgeNode->setPosition(m_sprite->getPosition() + Vec2(0, 20));
		break;
	case FACE_DOWN:
		particleSystem->setPosVar(Vec2(particleSystem->getPosVar().y, particleSystem->getPosVar().x));
		particleSystem->setGravity(Vec2(particleSystem->getGravity().y, particleSystem->getGravity().x));
		particleSystem->setAngle(-90);
		edgeNode->setRotation(90);
		edgeNode->setPosition(m_sprite->getPosition() + Vec2(0, -20));
		break;
	}
	return particleSystem;
}