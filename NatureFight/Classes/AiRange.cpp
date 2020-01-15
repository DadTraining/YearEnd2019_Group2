#include "AiRange.h"
#include <vector> 
#include <ResourceManager.h>
AiRange::AiRange(cocos2d::Scene* scene)
{
	sceneGame = scene;
	Init();
	//bullet
	Sprite* sprite = Sprite::create("FireBall/0_FireBall_000.png");
	sprite->setScale(0.7f);
	mBullet = new Bullet(sceneGame, sprite, Model::BITMASK_MONSTER_BULLET,"FireBall",116,true);
	mBullet->setScale(0.5f);
	mBullet->setAlive(false);
}
float timeAttackRange = 0, timeDieRange = 0, timeColorRange = 0, timeDelayHealRange = 0;
bool checkAttackRange = false;
void AiRange::Update(float deltaTime)
{
	loadingbar->setPosition(Vec2(m_sprite->getPosition() + Vec2(0, 30)));
	load->setPosition(loadingbar->getPosition());
	load->setPercent(setHealth());

	if (m_health <= 0) {
		timeDieRange += deltaTime;
		SetState(ACTION_DIE);
		if (timeDieRange >= 0.7) {
			timeDieRange = 0;
			m_sprite->setVisible(false);
			m_sprite->setPosition(-100, -100);
			m_CurrentState = ACTION_DEFAULT;
			m_CurrentFace = FACE_DEFAULT;
			physicsBodyChar->setEnabled(true);
		}
	}
	else {
		if (m_CurrentState == ACTION_ATTACK) checkAttackRange = true;
		if (checkAttackRange) timeAttackRange += deltaTime;
		if (timeAttackRange > 1.0f) {
			m_CurrentState = ACTION_DEFAULT;
			timeAttackRange = 0;
			checkAttackRange = false;
		}
		if (timeAttackRange > deltaTime) {		}
		SetFace();
	}
	if (!(m_sprite->getColor() == ccc3(255, 255, 255))) {
		timeColorRange += deltaTime;
		if (timeColorRange >= 1) {
			m_sprite->setColor(ccc3(255, 255, 255));
			timeColorRange = 0;
		}
	}
}


void AiRange::Init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	this->m_sprite = cocos2d::Sprite::create("Sprites/Man2/Golem_3/PNG/PNG_Sequences/Idle/0_Golem_Idle_000.png");
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

	//loaddinghealth
	loadingbar = ui::LoadingBar::create("loadingbar_bg.png");
	loadingbar->setScale(0.2);
	loadingbar->setPercent(100);
	this->sceneGame->addChild(loadingbar, 1);
	load = ui::LoadingBar::create("progress.png");
	load->setScale(0.21);
	this->sceneGame->addChild(load, 2);
	load->setDirection(ui::LoadingBar::Direction::LEFT);


	AttackSpeed = 1;
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(AiRange::onContactBegin, this);
	sceneGame->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, sceneGame);
}

float timeRange = 0;
void AiRange::Collision(Player* player, float deltaTime)
{
	Update(deltaTime);
	timeRange += deltaTime;
		if ((Distance(this->m_sprite->getPosition(), player->m_sprite->getPosition())) <= 200) {
			if (timeRange > 2.0f) {
				SetState(AiRange::ACTION_ATTACK);
					if (!mBullet->isAlive()) {
						mBullet->setAlive(true);
						mBullet->setPosition(this->m_sprite->getPosition());
						mBullet->getPhysicBody()->setVelocity((player->m_sprite->getPosition() - mBullet->getPosition()) * 2);
					}
				timeRange = 0;
			}
		}
		if (Distance(player->m_sprite->getPosition(), this->m_sprite->getPosition()) < 300 && (Distance(this->m_sprite->getPosition(), player->m_sprite->getPosition())) > 200) {
			this->physicsBodyChar->setVelocity((player->m_sprite->getPosition() - this->m_sprite->getPosition())/5);

		}
		else {
			this->physicsBodyChar->setVelocity(Vec2(0, 0));
		}
	//flip boss
	if ((player->m_sprite->getPosition() - this->m_sprite->getPosition()).x > 0) {
		m_sprite->setFlipX(false);
	}
	else {
		m_sprite->setFlipX(true);
	}
	mBullet->update(deltaTime,player);
}

void AiRange::SetIdle(int state) {
	if (state != m_CurrentState) {
		m_sprite->stopAllActions();
		m_sprite->runAction(IdleRight());
	}
	else if (m_sprite->getNumberOfRunningActions() == 0) {
		m_sprite->runAction(IdleRight());
	}

}
void AiRange::SetDie(int state)
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
void AiRange::SetAttack(int state) {

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

void AiRange::SetHurt(int state)
{
}
void AiRange::SetHurtAi(int state, int skill) {
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
void AiRange::SetMove(int state)
{
	if (state != m_CurrentState) {
		m_sprite->stopAllActions();
		m_sprite->runAction(MovingRight());
	}
	else if (m_sprite->getNumberOfRunningActions() == 0) {
		m_sprite->runAction(MovingRight());
	}
}
void AiRange::SetTagAI(int)
{
}
void AiRange::SetState(int state)
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

void AiRange::SetFace()
{
	float radian = std::atan2f(physicsBodyChar->getVelocity().y, physicsBodyChar->getVelocity().x);
	if (physicsBodyChar->getVelocity().x == 0 && physicsBodyChar->getVelocity().y == 0) {
		SetState(AiRange::ACTION_IDLE);
	}
	else {
		if (radian >= -M_PI / 4 && radian <= M_PI / 4) m_CurrentFace = FACE_RIGHT;
		else if (radian >= M_PI / 4 && radian <= 3 * M_PI / 4) m_CurrentFace = FACE_UP;
		else if ((radian >= 3 * M_PI / 4 && radian <= M_PI) || (radian <= -3 * M_PI / 4 && radian >= -M_PI)) m_CurrentFace = FACE_LEFT;
		else if (radian >= -3 * M_PI / 4 && radian <= -M_PI / 4) m_CurrentFace = FACE_DOWN;
		if (physicsBodyChar->getVelocity().x > 0) m_sprite->setFlipX(false);
		else m_sprite->setFlipX(true);
		SetState(AiRange::ACTION_MOVE);
	}
}
bool AiRange::onContactBegin(const PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA->getTag() == BOSSLV1 & nodeB->getTag() == ATTACKTAG || nodeB->getTag() == BOSSLV1 & nodeA->getTag() == ATTACKTAG)
	{
		if (nodeA->getTag() == BOSSLV1)
		{
			this->SetState(AiRange::ACTION_HURT);
		}
		else
		{
			this->SetState(AiRange::ACTION_HURT);
		}
	}
	if (nodeA->getTag() == BOSSLV1 & nodeB->getTag() == ATTACK_ICE || nodeB->getTag() == BOSSLV1 & nodeA->getTag() == ATTACK_ICE)
	{
		if (nodeA->getTag() == BOSSLV1)
		{
			this->SetState(AiRange::ACTION_HURT_ICE);
		}
		else
		{
			this->SetState(AiRange::ACTION_HURT_ICE);
		}
	}
	if (nodeA->getTag() == BOSSLV1 & nodeB->getTag() == ATTACK_FIRE || nodeB->getTag() == BOSSLV1 & nodeA->getTag() == ATTACK_FIRE)
	{
		if (nodeA->getTag() == BOSSLV1)
		{
			this->SetState(AiRange::ACTION_HURT_FIRE);
		}
		else
		{
			this->SetState(AiRange::ACTION_HURT_FIRE);
		}
	}
	//creepCollistionSkill(nodeA, nodeB);
	if ((nodeA->getPhysicsBody()->getCollisionBitmask() == Model::BITMASK_MONSTER_BULLET && nodeB->getTag() == playertag) ||
		(nodeA->getTag() == playertag && nodeB->getPhysicsBody()->getCollisionBitmask() == Model::BITMASK_MONSTER_BULLET)) {
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

cocos2d::RepeatForever* AiRange::MovingRight() {
	return ObjectParent::AnimationObjectRepeat(113, "Golem_Running", AttackSpeed);
}
cocos2d::Animate* AiRange::AttackRight() {
	return ObjectParent::AnimationObjectOnce(114, "Golem_Throwing", AttackSpeed);
}
cocos2d::RepeatForever* AiRange::IdleRight() {
	return ObjectParent::AnimationObjectRepeat(115, "Golem_Idle", AttackSpeed);
}
cocos2d::Animate* AiRange::AttackRightAngry() {
	return ObjectParent::AnimationObjectOnce(112, "Ogre_Throwing", AttackSpeed);
}
cocos2d::Animate* AiRange::DieRight() {
	return ObjectParent::AnimationObjectOnce(109, "Ogre_Dying", AttackSpeed);
}
cocos2d::Animate* AiRange::HurtRight() {
	return ObjectParent::AnimationObjectOnce(103, "Goblin_Hurt", AttackSpeed);
}
cocos2d::RepeatForever* AiRange::MovingUp() { return NULL; }
cocos2d::Animate* AiRange::AttackUp() { return NULL; }
cocos2d::RepeatForever* AiRange::IdleUp() { return NULL; }
cocos2d::Animate* AiRange::AttackUpAngry() { return NULL; }
cocos2d::Animate* AiRange::HurtUp() { return NULL; }
cocos2d::RepeatForever* AiRange::DieUp() { return NULL; }
cocos2d::RepeatForever* AiRange::MovingDown() { return NULL; }
cocos2d::Animate* AiRange::AttackDown() { return NULL; }
cocos2d::RepeatForever* AiRange::IdleDown() { return NULL; }
cocos2d::Animate* AiRange::AttackDownAngry() { return NULL; }
cocos2d::Animate* AiRange::HurtDown() { return NULL; }
cocos2d::RepeatForever* AiRange::DieDown() { return NULL; }
void AiRange::setIndex(int index)
{
	this->m_sprite->getPhysicsBody()->setGroup(index);
}
float AiRange::Distance(Vec2 A, Vec2 C) {
	return std::sqrt((A.x - C.x) * (A.x - C.x) + (A.y - C.y) * (A.y - C.y));
}

void AiRange::bulletHasCollision()
{
	mBullet->setAlive(false);
}

cocos2d::ParticleSystemQuad* AiRange::ParticleHeal(std::string name)
{
	auto particleSystem = ParticleSystemQuad::create(name);
	particleSystem->setScale(1.0f);
	particleSystem->setDuration(0.15f);
	return particleSystem;
}
float AiRange::setHealth()
{
	return m_health;
}