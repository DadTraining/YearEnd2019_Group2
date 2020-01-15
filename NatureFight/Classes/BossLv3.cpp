#include "BossLv3.h"
#include <vector> 
#include <ResourceManager.h>
BossLv3::BossLv3(cocos2d::Scene* scene)
{
	sceneGame = scene;

	Init();
	//bullet
	Sprite* sprite = Sprite::create("Sprites/Man3/Ice_Dino/IceBall/0_IceBall_001.png");
	sprite->setScale(0.7f);
	mBullet = new Bullet(sceneGame, sprite, Model::BITMASK_MONSTER_BULLET, "IceBall", 121, false);
	mBullet->setScale(0.5f);
	mBullet->setAlive(false);
}
float timeAttackBossLv3 = 0, timeDieAIBossLv3 = 0, timeColorAIBossLv3 = 0;
bool checkAttackAIBossLv3 = false;
void BossLv3::Update(float deltaTime)
{
	if (m_health <= 0) {
		timeDieAIBossLv3 += deltaTime;
		SetState(ACTION_DIE);
		if (timeDieAIBossLv3 >= 5) {
			timeDieAIBossLv3 = 0;
			m_sprite->setPosition(10, 10);
			m_CurrentState = ACTION_DEFAULT;
			m_CurrentFace = FACE_DEFAULT;
			physicsBodyChar->setEnabled(true);
		}
	}
	else {
		if (m_CurrentState == ACTION_ATTACK) checkAttackAIBossLv3 = true;
		if (checkAttackAIBossLv3) timeAttackBossLv3 += deltaTime;
		if (timeAttackBossLv3 > 2.0f) {
			//particle
				if (countSkill < 3) {
					if (!mBullet->isAlive()) {
						mBullet->setAlive(true);
						mBullet->setPosition(this->m_sprite->getPosition());
						mBullet->getPhysicBody()->setVelocity((player->m_sprite->getPosition() - mBullet->getPosition()) * 2);
					}
					countSkill++;
				}
				if(countSkill>=3) {
					auto particleSystem = ParticleIce("Particles/Boss3.plist");
					particleSystem->setPosition(this->m_sprite->getPosition());
					sceneGame->addChild(particleSystem);
					countSkill = 0;
				}
			m_CurrentState = ACTION_DEFAULT;
			timeAttackBossLv3 = 0;
			checkAttackAIBossLv3 = false;
		}
		if (timeAttackBossLv3 > deltaTime) {
		}
		SetFace();
	}
	if (!(m_sprite->getColor() == ccc3(255, 255, 255))) {
		timeColorAIBossLv3 += deltaTime;
		if (timeColorAIBossLv3 >= 1) {
			m_sprite->setColor(ccc3(255, 255, 255));
			timeColorAIBossLv3 = 0;
		}
	}
	
}


void BossLv3::Init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	m_health = 1000;
	this->m_sprite = cocos2d::Sprite::create("Sprites/Man3/Ice_Dino/Idle/0_DinoIdle_000.png");
	this->m_sprite->setPosition(Point(visibleSize.width / 1.2, visibleSize.height / 1.2));
	this->m_sprite->setScale(1.5);
	this->sceneGame->addChild(this->m_sprite);
	physicsBodyChar = PhysicsBody::createBox(this->m_sprite->getContentSize() / 3, PhysicsMaterial(0.1f, 1.0f, 0.0f));
	physicsBodyChar->setDynamic(false);
	physicsBodyChar->setRotationEnable(false);
	physicsBodyChar->setCollisionBitmask(Model::BITMASK_MONSTER);
	physicsBodyChar->setContactTestBitmask(1);
	this->m_sprite->setPhysicsBody(physicsBodyChar);
	physicsBodyChar->setGravityEnable(false);
	this->m_sprite->setTag(Boss3);
	m_CurrentState = ACTION_IDLE;
	m_CurrentFace = FACE_DEFAULT;
	AttackSpeed = 1;
	radius = 0;
	stateAttackIce = false;
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(BossLv3::onContactBegin, this);
	sceneGame->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, sceneGame);
	countSkill = 0;
}

float timeBoss3 = 0;
void BossLv3::Collision(Player* player, float deltaTime)
{
	this->player = player;
	Update(deltaTime);
	timeBoss3 += deltaTime;
	if ((Distance(this->m_sprite->getPosition(), player->m_sprite->getPosition())) <= 200) {
		if (timeBoss3 > 2.0f) {
			SetState(BossLv3::ACTION_ATTACK);
			this->physicsBodyChar->setVelocity(Vec2(0, 0));
			timeBoss3 = 0;
		}
	}
	if (Distance(player->m_sprite->getPosition(), this->m_sprite->getPosition()) < 300 && (Distance(this->m_sprite->getPosition(), player->m_sprite->getPosition())) > 200)
		this->physicsBodyChar->setVelocity((player->m_sprite->getPosition() - this->m_sprite->getPosition())/3);
	else this->physicsBodyChar->setVelocity(Vec2(0, 0));
	if (Distance(player->m_sprite->getPosition(), this->m_sprite->getPosition()) <= radius*6.4) {
		//colistion here
		m_health-=20;
		player->m_sprite->setColor(ccc3(0, 0, 255));
		CCLOG("%d", m_health);
		this->setStateAttackIce(false);
		radius = 0;
	}
	if (radius >= 40) {
		radius = 0;
		this->setStateAttackIce(false);
	}
	if (stateAttackIce == true) {
		auto a = Distance(player->m_sprite->getPosition(), this->m_sprite->getPosition());
		radius++;
	}
	mBullet->update(deltaTime, player);
}

void BossLv3::SetIdle(int state) {
	if (state != m_CurrentState) {
		m_sprite->stopAllActions();
		m_sprite->runAction(IdleRight());
	}
	else if (m_sprite->getNumberOfRunningActions() == 0) {
		m_sprite->runAction(IdleRight());
	}

}
void BossLv3::SetDie(int state)
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
void BossLv3::SetAttack(int state) {
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
			m_sprite->runAction(AttackRight());
		}
		else if (m_sprite->getNumberOfRunningActions() == 0) {
			m_sprite->runAction(AttackRight());
		}
		break;
	case FACE_DOWN:
		if (state != m_CurrentState) {
			m_sprite->stopAllActions();
			m_sprite->runAction(AttackRight());
		}
		else if (m_sprite->getNumberOfRunningActions() == 0) {
			m_sprite->runAction(AttackRight());
		}
		break;
	}
}
void BossLv3::SetHurt(int state)
{
}
void BossLv3::SetHurtAi(int state, int skill) {
	if (state != m_CurrentState) {
		if (skill == NORMALSKILL) {
			m_sprite->setColor(ccc3(255, 0, 0));
			m_health -= player->m_dame;
		}
		else if (skill == ATTACK_ICE) {
			m_sprite->setColor(ccc3(0, 0, 255));
			m_health -= player->m_dame;
		}
		else if (skill == ATTACK_FIRE) {
			m_sprite->setColor(ccc3(255, 0, 0));
			m_health -= player->m_dame;
		}
	}

	CCLOG("%d", m_health);
}
void BossLv3::SetMove(int state)
{
	if (state != m_CurrentState) {
		m_sprite->stopAllActions();
		m_sprite->runAction(MovingRight());
	}
	else if (m_sprite->getNumberOfRunningActions() == 0) {
		m_sprite->runAction(MovingRight());
	}
}

void BossLv3::SetState(int state)
{
	if(m_CurrentState!= ACTION_DIE)
	if (!((m_CurrentState == ACTION_ATTACK) && m_sprite->getNumberOfRunningActions() > 0) || state == ACTION_HURT_ICE || state == ACTION_HURT_FIRE)
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
			SetHurtAi(state, NORMALSKILL);
			break;
		case ACTION_DIE:
			SetDie(state);
			break;
		case ACTION_HURT_ICE:
			SetHurtAi(state, ATTACK_ICE);
			break;
		case ACTION_HURT_FIRE:
			SetHurtAi(state, ATTACK_FIRE);
			break;
		}

		m_CurrentState = state;
	}
}

void BossLv3::SetFace()
{
	float radian = std::atan2f(physicsBodyChar->getVelocity().y, physicsBodyChar->getVelocity().x);
	if (physicsBodyChar->getVelocity().x == 0 && physicsBodyChar->getVelocity().y == 0) {
		SetState(BossLv3::ACTION_IDLE);
	}
	else {
		if (radian >= -M_PI / 4 && radian <= M_PI / 4) m_CurrentFace = FACE_RIGHT;
		else if (radian >= M_PI / 4 && radian <= 3 * M_PI / 4) m_CurrentFace = FACE_UP;
		else if ((radian >= 3 * M_PI / 4 && radian <= M_PI) || (radian <= -3 * M_PI / 4 && radian >= -M_PI)) m_CurrentFace = FACE_LEFT;
		else if (radian >= -3 * M_PI / 4 && radian <= -M_PI / 4) m_CurrentFace = FACE_DOWN;
		if (physicsBodyChar->getVelocity().x > 0) m_sprite->setFlipX(true);
		else m_sprite->setFlipX(false);
		SetState(BossLv3::ACTION_MOVE);
	}
}

cocos2d::RepeatForever* BossLv3::MovingRight() {
	return ObjectParent::AnimationObjectRepeat(120, "DinoRun", AttackSpeed);
}
cocos2d::Animate* BossLv3::AttackRight() {
	return ObjectParent::AnimationObjectOnce(118, "DinoAttack", 0.5);
}
cocos2d::RepeatForever* BossLv3::IdleRight() {
	return ObjectParent::AnimationObjectRepeat(117, "DinoIdle", AttackSpeed);
}
cocos2d::Animate* BossLv3::AttackRightAngry() {
	return ObjectParent::AnimationObjectOnce(105, "Goblin_Kicking", AttackSpeed);
}
cocos2d::Animate* BossLv3::DieRight() {
	return ObjectParent::AnimationObjectOnce(119, "DinoDead", AttackSpeed);
}
cocos2d::Animate* BossLv3::HurtRight() {
	return ObjectParent::AnimationObjectOnce(103, "Goblin_Hurt", AttackSpeed);
}
cocos2d::RepeatForever* BossLv3::MovingUp() { return NULL; }
cocos2d::Animate* BossLv3::AttackUp() { return NULL; }
cocos2d::RepeatForever* BossLv3::IdleUp() { return NULL; }
cocos2d::Animate* BossLv3::AttackUpAngry() { return NULL; }
cocos2d::Animate* BossLv3::HurtUp() { return NULL; }
cocos2d::RepeatForever* BossLv3::DieUp() { return NULL; }
cocos2d::RepeatForever* BossLv3::MovingDown() { return NULL; }
cocos2d::Animate* BossLv3::AttackDown() { return NULL; }
cocos2d::RepeatForever* BossLv3::IdleDown() { return NULL; }
cocos2d::Animate* BossLv3::AttackDownAngry() { return NULL; }
cocos2d::Animate* BossLv3::HurtDown() { return NULL; }
cocos2d::RepeatForever* BossLv3::DieDown() { return NULL; }

float BossLv3::Distance(Vec2 A, Vec2 C) {
	return std::sqrt((A.x - C.x) * (A.x - C.x) + (A.y - C.y) * (A.y - C.y));
}
bool BossLv3::onContactBegin(const PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA->getTag() == m_sprite->getTag() & (nodeB->getTag() == ATTACK_ICE | nodeB->getTag() == ATTACK_FIRE | nodeB->getTag() == NORMALSKILL) 
		|| nodeB->getTag() == m_sprite->getTag() & (nodeA->getTag() == ATTACK_ICE | nodeA->getTag() == ATTACK_FIRE | nodeA->getTag() == NORMALSKILL))
	{
		if (player->edgeNode->getTag() == NORMALSKILL)	SetHurtAi(ACTION_HURT, NORMALSKILL);
		else if (player->edgeNode->getTag() == ATTACK_ICE) SetHurtAi(ACTION_HURT_ICE, ATTACK_ICE);
		else if (player->edgeNode->getTag() == ATTACK_FIRE) SetHurtAi(ACTION_HURT_FIRE, ATTACK_FIRE);
		if (m_health == 0) {
			m_sprite->runAction(DieRight());
			physicsBodyChar->setEnabled(false);
			player->Exp += 20;
			player->CountCreep += 1;
			CCLOG("exp: %d", player->Exp);
		}
	}
	//creepCollistionSkill(nodeA, nodeB);
	if (((nodeA->getPhysicsBody()->getCollisionBitmask() == Model::BITMASK_MONSTER_BULLET ) ||
		(nodeB->getPhysicsBody()->getCollisionBitmask() == Model::BITMASK_MONSTER_BULLET))&&(!(nodeA->getTag() == Boss3||nodeB->getTag()==Boss3))) {
		if (nodeA->getPhysicsBody()->getCollisionBitmask() == Model::BITMASK_MONSTER_BULLET)
		{
			this->bulletHasCollision();
		}
		if (nodeB->getPhysicsBody()->getCollisionBitmask() == Model::BITMASK_MONSTER_BULLET)
		{
			this->bulletHasCollision();
		}
	}
	return true;
}
cocos2d::ParticleSystemQuad* BossLv3::ParticleIce(std::string name)
{
	this->setStateAttackIce(true);
	auto particleSystem = ParticleSystemQuad::create(name);
	particleSystem->setScale(0.5f);
	particleSystem->setDuration(0.2f);
	return particleSystem;
}
void BossLv3::setStateAttackIce(bool state) {
		stateAttackIce = state;
}
void BossLv3::bulletHasCollision()
{
	mBullet->setAlive(false);
}