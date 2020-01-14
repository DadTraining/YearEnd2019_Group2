#include "BossLv1.h"
#include <vector> 
#include <ResourceManager.h>
BossLv1::BossLv1(cocos2d::Scene* scene)
{
	sceneGame = scene;
	Init();
	for (int i = 0; i < MAX_BULLET; i++) {
		auto sprite = Sprite::create("Bomb/0_boom_000.png");
		sprite->setScale(0.1f);
		mBooms[i] = new Boom(scene, sprite, Model::BITMASK_MONSTER_BULLET);
		mBooms[i]->setIndex(i);
	}
}
float timeAttackBoss = 0, timeDieBoss = 0, timeColorBoss = 0,timeDelayHeal=0;
bool checkAttackBoss = false;
void BossLv1::Update(float deltaTime)
{
	if (m_health <= 0) {
		timeDieBoss += deltaTime;
		SetState(ACTION_DIE);
		if (timeDieBoss >= 0.7) {
			timeDieBoss = 0;
			m_sprite->setVisible(false);
			m_sprite->setPosition(-100, -100);
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
		if (timeColorBoss >= 1) {
			m_sprite->setColor(ccc3(255, 255, 255));
			timeColorBoss = 0;
		}
	}
	if (m_health > 0 && m_health <= 60) {
		timeDelayHeal += deltaTime;
		if (timeDelayHeal > 3) {
			setSkillHeal(true);
			timeDelayHeal = 0;
		}else {
			stateHeal = false;
		}
	}
	if(m_health<=50){
		stateAngry = true;
	}
	else
	{
		stateAngry = false;
	}
}


void BossLv1::Init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	stateHeal = false;
	this->m_sprite = cocos2d::Sprite::create("Sprites/Man1/Ogre/PNG/PNG_Sequences/Idle/0_Ogre_Idle_000.png");
	this->m_sprite->setPosition(Point(visibleSize.width / 1.2, visibleSize.height / 1.2));
	this->m_sprite->setScale(2);
	this->sceneGame->addChild(this->m_sprite);
	physicsBodyChar = PhysicsBody::createBox(this->m_sprite->getContentSize() / 2, PhysicsMaterial(0.1f, 1.0f, 0.0f));
	//physicsBodyChar->setDynamic(false);
	physicsBodyChar->setRotationEnable(false);
	physicsBodyChar->setCollisionBitmask(Model::BITMASK_MONSTER);
	physicsBodyChar->setContactTestBitmask(1);
	this->m_sprite->setPhysicsBody(physicsBodyChar);
	this->m_sprite->setTag(BOSSLV1);
	physicsBodyChar->setGravityEnable(false);
	m_CurrentState = ACTION_IDLE;
	m_CurrentFace = FACE_DEFAULT;
	stateAngry = false;
	AttackSpeed = 1;
	auto edgeBody = PhysicsBody::createEdgeBox(Size(40, 40));
	edgeBody->setContactTestBitmask(Model::BITMASK_MONSTER);
	edgeBody->setCollisionBitmask(false);
	edgeNode = Node::create();
	edgeNode->setPosition(m_sprite->getPosition());
	sceneGame->addChild(edgeNode);
	edgeNode->setPhysicsBody(edgeBody);
	edgeNode->setTag(BOSSATTACK);
}

float timeBoss = 0;
void BossLv1::Collision(Player* player, float deltaTime)
{
	Update(deltaTime);
	timeBoss += deltaTime;
	if (stateAngry) {
		if ((Distance(this->m_sprite->getPosition(), player->m_sprite->getPosition())) <= 200) {
			if (timeBoss > 2.0f) {
				SetState(BossLv1::ACTION_ATTACK);
				for (int i = 0; i < MAX_BULLET; i++)
				{
					if (!mBooms[i]->isAlive()) {
						mBooms[i]->setAlive(true);
						mBooms[i]->setPosition(this->m_sprite->getPosition());
						mBooms[i]->getPhysicBody()->setVelocity((player->m_sprite->getPosition() - mBooms[i]->getPosition()) * 2);
						
						break;
					}
				}
				timeBoss = 0;
			}
		}
		if (Distance(player->m_sprite->getPosition(), this->m_sprite->getPosition()) < 300 && (Distance(this->m_sprite->getPosition(), player->m_sprite->getPosition())) > 200) {
			this->physicsBodyChar->setVelocity(player->m_sprite->getPosition() - this->m_sprite->getPosition());

		}
		else {
			this->physicsBodyChar->setVelocity(Vec2(0, 0));
		}
	}
	else {
		if ((Distance(this->m_sprite->getPosition(), player->m_sprite->getPosition())) <= 70) {
			if (timeBoss > 2.0f) {
				SetState(BossLv1::ACTION_ATTACK);
				timeBoss = 0;
			}
		}
		if (Distance(player->m_sprite->getPosition(), this->m_sprite->getPosition()) < 200 && (Distance(this->m_sprite->getPosition(), player->m_sprite->getPosition())) > 70) {
			this->physicsBodyChar->setVelocity(player->m_sprite->getPosition() - this->m_sprite->getPosition());

		}
		else {
			this->physicsBodyChar->setVelocity(Vec2(0, 0));
		}
	}
	updateBullets(deltaTime);
	//flip boss
	if ((player->m_sprite->getPosition() - this->m_sprite->getPosition()).x>0) {
		m_sprite->setFlipX(false);
	}
	else {
		m_sprite->setFlipX(true);
	}
}

void BossLv1::SetIdle(int state) {
	if (state != m_CurrentState) {
		m_sprite->stopAllActions();
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
	if (!stateAngry) {
		switch (m_CurrentFace)
		{
		case FACE_LEFT:
			if (state != m_CurrentState) {
				m_sprite->stopAllActions();
				m_sprite->runAction(AttackRight());
				edgeNode->setPosition(m_sprite->getPosition() + Vec2(-30, 0));
			}
			else if (m_sprite->getNumberOfRunningActions() == 0) {
				m_sprite->runAction(AttackRight());
				edgeNode->setPosition(m_sprite->getPosition() + Vec2(-30, 0));
			}
			break;
		case FACE_RIGHT:
			if (state != m_CurrentState) {
				m_sprite->stopAllActions();
				m_sprite->runAction(AttackRight());
				edgeNode->setPosition(m_sprite->getPosition() + Vec2(30, 0));

			}
			else if (m_sprite->getNumberOfRunningActions() == 0) {
				m_sprite->runAction(AttackRight());
				edgeNode->setPosition(m_sprite->getPosition() + Vec2(30, 0));
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
	else {
		switch (m_CurrentFace)
		{
		case FACE_LEFT:
			if (state != m_CurrentState) {
				m_sprite->stopAllActions();
				m_sprite->runAction(AttackRightAngry());
				edgeNode->setPosition(m_sprite->getPosition() + Vec2(-30, 0));
			}
			else if (m_sprite->getNumberOfRunningActions() == 0) {
				m_sprite->runAction(AttackRightAngry());
				edgeNode->setPosition(m_sprite->getPosition() + Vec2(-30, 0));
			}
			break;
		case FACE_RIGHT:
			if (state != m_CurrentState) {
				m_sprite->stopAllActions();
				m_sprite->runAction(AttackRightAngry());
				edgeNode->setPosition(m_sprite->getPosition() + Vec2(30, 0));

			}
			else if (m_sprite->getNumberOfRunningActions() == 0) {
				m_sprite->runAction(AttackRightAngry());
				edgeNode->setPosition(m_sprite->getPosition() + Vec2(30, 0));
			}
			break;
		case FACE_UP:
			if (state != m_CurrentState) {
				m_sprite->stopAllActions();
				m_sprite->runAction(AttackRightAngry());
				edgeNode->setPosition(m_sprite->getPosition() + Vec2(0, 20));
			}
			else if (m_sprite->getNumberOfRunningActions() == 0) {
				m_sprite->runAction(AttackRightAngry());
				edgeNode->setPosition(m_sprite->getPosition() + Vec2(0, 20));
			}
			break;
		case FACE_DOWN:
			if (state != m_CurrentState) {
				m_sprite->stopAllActions();
				m_sprite->runAction(AttackRightAngry());
				edgeNode->setPosition(m_sprite->getPosition() + Vec2(0, -20));
			}
			else if (m_sprite->getNumberOfRunningActions() == 0) {
				m_sprite->runAction(AttackRightAngry());
				edgeNode->setPosition(m_sprite->getPosition() + Vec2(0, -20));
			}
			break;
		}
	}
	
}
void BossLv1::SetHurt(int state)
{
}
void BossLv1::SetHurtAi(int state, int skill) {
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
	//else if (m_sprite->getNumberOfRunningActions() == 0) {
	//	m_sprite->runAction(HurtRight());
	//	m_health -= 10;
	//}
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
			SetHurtAi(state, SKILLICE);
			break;
		case ACTION_HURT_FIRE:
			SetHurtAi(state, SKILLFIRE);
			break;
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
	return ObjectParent::AnimationObjectOnce(112, "Ogre_Throwing", AttackSpeed);
}
cocos2d::RepeatForever* BossLv1::DieRight() {
	return ObjectParent::AnimationObjectRepeat(109, "Ogre_Dying", AttackSpeed);
}
cocos2d::Animate* BossLv1::HurtRight() {
	return ObjectParent::AnimationObjectOnce(103, "Goblin_Hurt", AttackSpeed);
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
void BossLv1::setIndex(int index)
{
	this->m_sprite->getPhysicsBody()->setGroup(index);
}
float BossLv1::Distance(Vec2 A, Vec2 C) {
	return std::sqrt((A.x - C.x) * (A.x - C.x) + (A.y - C.y) * (A.y - C.y));
}
void BossLv1::updateBullets(float deltaTime)
{
	for (int i = 0; i < MAX_BULLET; i++)
	{
		mBooms[i]->update(deltaTime);
	}
}
void BossLv1::bulletHasCollision(int bulletIndex)
{
	//mBullets[bulletIndex]->setAlive(false);
	mBooms[bulletIndex]->SetExplo(true);
}
void BossLv1::setSkillHeal(bool sHeal) {
	if (sHeal != stateHeal) {
		auto particleSystem = ParticleHeal("Particles/BossHealler.plist");
		m_health += 10;
		particleSystem->setPosition(this->m_sprite->getPosition());
		sceneGame->addChild(particleSystem);
	}
	stateHeal = sHeal;
}
cocos2d::ParticleSystemQuad* BossLv1::ParticleHeal(std::string name)
{
	auto particleSystem = ParticleSystemQuad::create(name);
	particleSystem->setScale(1.0f);
	particleSystem->setDuration(0.15f);
	return particleSystem;
}