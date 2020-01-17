#include "BossEnd.h"
#include <vector> 
#include <ResourceManager.h>
BossEnd::BossEnd(cocos2d::Scene* scene)
{
	sceneGame = scene;

	Init();
	stateHeal = false;
	stateRain = 0;
	//bullet
	Sprite* sprite = Sprite::create("Sprites/Man3/Ice_Dino/IceBall/0_IceBall_001.png");
	sprite->setScale(0.7f);
	mBullet = new Bullet(sceneGame, sprite, Model::BITMASK_MONSTER_BULLET, "IceBall", 121, false);
	mBullet->setScale(0.5f);
	mBullet->setAlive(false);
	//tonato
	for (int i = 0; i < MAX_BULLET; i++) {
		Sprite* sprite = Sprite::create("Sprites/Boss/SkillTonato/Tonato/0_Tonato_001.png");
		sprite->setScale(1.0f);
		mBullets[i] = new Bullet(sceneGame, sprite, Model::BITMASK_MONSTER_TONATO, "Tonato", 126, false);
		mBullets[i]->setIndex(i);
	}
}

void BossEnd::Update(float deltaTime)
{
	loadingbar->setPosition(Vec2(m_sprite->getPosition() + Vec2(0, 30)));
	load->setPosition(loadingbar->getPosition());
	load->setPercent((setHealth()*100)/ max_health);
	if (m_health <= 0) {
		timeDieAIBossLv3 += deltaTime;
		SetState(ACTION_DIE);
		if (timeDieAIBossLv3 >= 4) {
			stateRain = 3;
			timeDieAIBossLv3 = 0;
			m_sprite->setPosition(10, 10);
			m_CurrentState = ACTION_DEFAULT;
			m_CurrentFace = FACE_DEFAULT;
			physicsBodyChar->setEnabled(true);
			this->m_sprite->setVisible(false);
			this->loadingbar->setVisible(false);
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
			if (countSkill == 3) {
				auto particleSystem = ParticleIce("Particles/BossEnd.plist");
				particleSystem->setPosition(this->m_sprite->getPosition());
				sceneGame->addChild(particleSystem);
				countSkill ++;
			}
			else if (countSkill == 4) {
				for (int i = 0; i < MAX_BULLET; i++)
				{
					if (!mBullets[i]->isAlive()) {
						mBullets[i]->setAlive(true);
						mBullets[i]->setPosition(this->m_sprite->getPosition());
						if (i == 0) mBullets[i]->getPhysicBody()->setVelocity(Vec2(0, SpeedTonato));
						else if(i==1) mBullets[i]->getPhysicBody()->setVelocity(Vec2(SpeedTonato, SpeedTonato));
						else if(i==2) mBullets[i]->getPhysicBody()->setVelocity(Vec2(SpeedTonato, 0));
						else if (i == 3) mBullets[i]->getPhysicBody()->setVelocity(Vec2(SpeedTonato, -SpeedTonato));
						else if (i == 4) mBullets[i]->getPhysicBody()->setVelocity(Vec2(0, -SpeedTonato));
						else if (i == 5) mBullets[i]->getPhysicBody()->setVelocity(Vec2(-SpeedTonato, -SpeedTonato));
						else if (i == 6) mBullets[i]->getPhysicBody()->setVelocity(Vec2(-SpeedTonato, 0));
						else if (i == 7) mBullets[i]->getPhysicBody()->setVelocity(Vec2(-SpeedTonato, SpeedTonato));
					}
				}
				countSkill=0;
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
	//heal
	if (m_health > 0 && m_health <= 80) {
		timeDelayHeal += deltaTime;
		if (timeDelayHeal > 4) {
			setSkillHeal(true);
			timeDelayHeal = 0;
		}
		else {
			stateHeal = false;
		}
	}
	if (m_health > 0 && m_health <= 150&&stateRain==0) {
		stateRain = 1;
		player->m_dame -= m_dame/2;
		ParticleRain("Particles/Rain.plist");
	}
	if (stateRain == 1) {
		timeHealRain += deltaTime;
		if (timeHealRain > 4) {
			timeHealRain = 0;
			player->m_health -= m_dame;
		}
	}

}


void BossEnd::Init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	m_health = 200;
	this->m_sprite = cocos2d::Sprite::create("Sprites/Boss/Idle/0_BossEnd_Idle_000.png");
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

	//loaddinghealth
	loadingbar = ui::LoadingBar::create("loadingbar_bg.png");
	loadingbar->setScale(0.2);
	loadingbar->setPercent(100);
	this->sceneGame->addChild(loadingbar, 1);
	load = ui::LoadingBar::create("progress.png");
	load->setScale(0.21);
	this->sceneGame->addChild(load, 2);
	load->setDirection(ui::LoadingBar::Direction::LEFT);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(BossEnd::onContactBegin, this);
	sceneGame->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, sceneGame);
	countSkill = 0;
	m_dame = 50;
}


void BossEnd::Collision(Player* player, float deltaTime)
{
	this->player = player;
	Update(deltaTime);
	timeBoss3 += deltaTime;
	if ((Distance(this->m_sprite->getPosition(), player->m_sprite->getPosition())) <= 200) {
		if (timeBoss3 > 2.0f) {
			SetState(BossEnd::ACTION_ATTACK);
			this->physicsBodyChar->setVelocity(Vec2(0, 0));
			timeBoss3 = 0;
		}
	}
	if (Distance(player->m_sprite->getPosition(), this->m_sprite->getPosition()) < 300 && (Distance(this->m_sprite->getPosition(), player->m_sprite->getPosition())) > 200)
		this->physicsBodyChar->setVelocity((player->m_sprite->getPosition() - this->m_sprite->getPosition()) / 3);
	else this->physicsBodyChar->setVelocity(Vec2(0, 0));
	if (Distance(player->m_sprite->getPosition(), this->m_sprite->getPosition()) <= radius * 6.4) {
		//colistion here
		player->m_health -= m_dame;
		player->m_sprite->setColor(ccc3(0, 0, 230));
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
	updateBullets(deltaTime,player);
}

void BossEnd::SetIdle(int state) {
	if (state != m_CurrentState) {
		m_sprite->stopAllActions();
		m_sprite->runAction(IdleRight());
	}
	else if (m_sprite->getNumberOfRunningActions() == 0) {
		m_sprite->runAction(IdleRight());
	}

}
void BossEnd::SetDie(int state)
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
void BossEnd::SetAttack(int state) {
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
void BossEnd::SetHurt(int state)
{
}
void BossEnd::SetHurtAi(int state, int skill) {
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
void BossEnd::SetMove(int state)
{
	if (state != m_CurrentState) {
		m_sprite->stopAllActions();
		m_sprite->runAction(MovingRight());
	}
	else if (m_sprite->getNumberOfRunningActions() == 0) {
		m_sprite->runAction(MovingRight());
	}
}

void BossEnd::SetState(int state)
{
	if (m_CurrentState != ACTION_DIE)
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

void BossEnd::SetFace()
{
	float radian = std::atan2f(physicsBodyChar->getVelocity().y, physicsBodyChar->getVelocity().x);
	if (physicsBodyChar->getVelocity().x == 0 && physicsBodyChar->getVelocity().y == 0) {
		SetState(BossEnd::ACTION_IDLE);
	}
	else {
		if (radian >= -M_PI / 4 && radian <= M_PI / 4) m_CurrentFace = FACE_RIGHT;
		else if (radian >= M_PI / 4 && radian <= 3 * M_PI / 4) m_CurrentFace = FACE_UP;
		else if ((radian >= 3 * M_PI / 4 && radian <= M_PI) || (radian <= -3 * M_PI / 4 && radian >= -M_PI)) m_CurrentFace = FACE_LEFT;
		else if (radian >= -3 * M_PI / 4 && radian <= -M_PI / 4) m_CurrentFace = FACE_DOWN;
		if (physicsBodyChar->getVelocity().x > 0) m_sprite->setFlipX(true);
		else m_sprite->setFlipX(false);
		SetState(BossEnd::ACTION_MOVE);
	}
}

cocos2d::RepeatForever* BossEnd::MovingRight() {
	return ObjectParent::AnimationObjectRepeat(124, "BossEnd_Walk", AttackSpeed);
}
cocos2d::Animate* BossEnd::AttackRight() {
	return ObjectParent::AnimationObjectOnce(123, "BossEnd", 0.5);
}
cocos2d::RepeatForever* BossEnd::IdleRight() {
	return ObjectParent::AnimationObjectRepeat(125, "BossEnd_Idle", AttackSpeed);
}
cocos2d::Animate* BossEnd::AttackRightAngry() {
	return ObjectParent::AnimationObjectOnce(105, "Goblin_Kicking", AttackSpeed);
}
cocos2d::Animate* BossEnd::DieRight() {
	return ObjectParent::AnimationObjectOnce(131, "Boss_dead", AttackSpeed);
}
cocos2d::Animate* BossEnd::HurtRight() {
	return ObjectParent::AnimationObjectOnce(103, "Goblin_Hurt", AttackSpeed);
}
cocos2d::RepeatForever* BossEnd::MovingUp() { return NULL; }
cocos2d::Animate* BossEnd::AttackUp() { return NULL; }
cocos2d::RepeatForever* BossEnd::IdleUp() { return NULL; }
cocos2d::Animate* BossEnd::AttackUpAngry() { return NULL; }
cocos2d::Animate* BossEnd::HurtUp() { return NULL; }
cocos2d::RepeatForever* BossEnd::DieUp() { return NULL; }
cocos2d::RepeatForever* BossEnd::MovingDown() { return NULL; }
cocos2d::Animate* BossEnd::AttackDown() { return NULL; }
cocos2d::RepeatForever* BossEnd::IdleDown() { return NULL; }
cocos2d::Animate* BossEnd::AttackDownAngry() { return NULL; }
cocos2d::Animate* BossEnd::HurtDown() { return NULL; }
cocos2d::RepeatForever* BossEnd::DieDown() { return NULL; }

float BossEnd::Distance(Vec2 A, Vec2 C) {
	return std::sqrt((A.x - C.x) * (A.x - C.x) + (A.y - C.y) * (A.y - C.y));
}
bool BossEnd::onContactBegin(const PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA->getTag() == m_sprite->getTag() & (nodeB->getTag() == ATTACK_ICE | nodeB->getTag() == ATTACK_FIRE | nodeB->getTag() == NORMALSKILL)
		|| nodeB->getTag() == m_sprite->getTag() & (nodeA->getTag() == ATTACK_ICE | nodeA->getTag() == ATTACK_FIRE | nodeA->getTag() == NORMALSKILL))
	{

		m_health -= player->m_dame;
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
	if (((nodeA->getPhysicsBody()->getCollisionBitmask() == Model::BITMASK_MONSTER_BULLET) ||
		(nodeB->getPhysicsBody()->getCollisionBitmask() == Model::BITMASK_MONSTER_BULLET)) && (!(nodeA->getTag() == Boss3 || nodeB->getTag() == Boss3))) {
		if (nodeA->getPhysicsBody()->getCollisionBitmask() == Model::BITMASK_MONSTER_BULLET)
		{
			this->bulletHasCollision();
		}
		if (nodeB->getPhysicsBody()->getCollisionBitmask() == Model::BITMASK_MONSTER_BULLET)
		{
			this->bulletHasCollision();
		}
	}
	if ((nodeA->getPhysicsBody()->getCollisionBitmask() == Model::BITMASK_MONSTER_BULLET && nodeB->getTag() == playertag) ||
		(nodeA->getTag() == playertag && nodeB->getPhysicsBody()->getCollisionBitmask() == Model::BITMASK_MONSTER_BULLET)) {
		if (nodeA->getPhysicsBody()->getCollisionBitmask() == Model::BITMASK_MONSTER_BULLET)
		{
			this->bulletHasCollision();
			this->player->m_sprite->setColor(ccc3(132, 112, 255));
			this->player->m_health -= m_dame/2;
		}
		if (nodeB->getPhysicsBody()->getCollisionBitmask() == Model::BITMASK_MONSTER_BULLET)
		{
			this->bulletHasCollision();
			this->player->m_sprite->setColor(ccc3(132, 112, 255));
			this->player->m_health -= m_dame/2;
		}
	}
	if ((nodeA->getPhysicsBody()->getCollisionBitmask() == Model::BITMASK_MONSTER_TONATO && nodeB->getTag() == playertag) ||
		(nodeA->getTag() == playertag && nodeB->getPhysicsBody()->getCollisionBitmask() == Model::BITMASK_MONSTER_TONATO)) {
		if (nodeA->getPhysicsBody()->getCollisionBitmask() == Model::BITMASK_MONSTER_TONATO)
		{
			this->player->m_sprite->setColor(ccc3(0, 238, 238));
			this->player->m_health -= m_dame+10;
			this->tonatoHasCollision(nodeA->getPhysicsBody()->getGroup());
		}
		if (nodeB->getPhysicsBody()->getCollisionBitmask() == Model::BITMASK_MONSTER_TONATO)
		{
			this->player->m_sprite->setColor(ccc3(0, 238, 238));
			this->player->m_health -= m_dame+10;
			this->tonatoHasCollision(nodeB->getPhysicsBody()->getGroup());
		}
	}
	return true;
}
cocos2d::ParticleSystemQuad* BossEnd::ParticleIce(std::string name)
{
	this->setStateAttackIce(true);
	auto particleSystem = ParticleSystemQuad::create(name);
	particleSystem->setScale(0.5f);
	particleSystem->setDuration(0.2f);
	return particleSystem;
}
void BossEnd::setStateAttackIce(bool state) {
	stateAttackIce = state;
}
void BossEnd::bulletHasCollision()
{
	mBullet->setAlive(false);
}
float BossEnd::setHealth()
{
	return m_health;
}
void BossEnd::setSkillHeal(bool sHeal) {
	if (sHeal != stateHeal) {
		auto particleSystem = ParticleHeal("Particles/BossHealler.plist");
		m_health += 10;
		particleSystem->setPosition(this->m_sprite->getPosition());
		sceneGame->addChild(particleSystem);
	}
	stateHeal = sHeal;
}
cocos2d::ParticleSystemQuad* BossEnd::ParticleHeal(std::string name)
{
	auto particleSystem = ParticleSystemQuad::create(name);
	particleSystem->setScale(1.0f);
	particleSystem->setDuration(0.15f);
	return particleSystem;
}
void BossEnd::ParticleRain(std::string name)
{

	auto particleMove = ParticleSystemQuad::create(name);
	particleMove->setScale(5.0f);
	particleMove->setStartSize(5);
	particleMove->setSpeed(-100);
	particleMove->setAngle(90);
	particleMove->setPosition(m_sprite->getPosition() + Vec2(0, 100));
	particleMove->setDuration(ParticleSystem::DURATION_INFINITY);
	sceneGame->addChild(particleMove);

}
void BossEnd::updateBullets(float deltaTime, Player* player)
{
	for (int i = 0; i < MAX_BULLET; i++)
	{
		mBullets[i]->update(deltaTime,player);
	}
}
void BossEnd::tonatoHasCollision(int bulletIndex)
{
	mBullets[bulletIndex]->setAlive(false);
}