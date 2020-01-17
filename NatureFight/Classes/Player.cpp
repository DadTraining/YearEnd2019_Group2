#include <Player.h>
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
int Player::Level = 1;
int Player::Exp = 0;
int Player::MaxExp;
int Player::m_CurrentStone;
bool Player::haveSword = false;
bool Player::haveSwordFire = false;
bool Player::haveSwordIce = false;
bool Player::haveFireStone = false;
bool Player::haveIceStone = false;
bool Player::haveFirePet = false;
bool Player::haveIceShield = false;
int Player::CountCreep = 0;
Player::Player(cocos2d::Scene* scene)
{
	sceneGame = scene;
	Init();
}
float timeAttack = 0, timeDie = 0, timeShield = 0, timeColorPlayer = 0;;
bool checkAttack = false;
void Player::Update(float deltaTime)
{
	CheckDragon(deltaTime);
	CheckShield(deltaTime);
	if (m_health <= 0) {
		timeDie += deltaTime;
		SetState(ACTION_DIE);
	}
	else {
		CheckAttackAndSkill(deltaTime);
	}
	particleMove->setPosition(m_sprite->getPosition() - Vec2(0, 20));
	if (!(m_sprite->getColor() == ccc3(255, 255, 255))) {
		timeColorPlayer += deltaTime;
		if (timeColorPlayer >= 1) {
			m_sprite->setColor(ccc3(255, 255, 255));
			timeColorPlayer = 0;
		}
	}
	if (onAngry) particlePow->setPosition(m_sprite->getPosition());
}

void Player::Init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto def = UserDefault::sharedUserDefault();
	Level = def->getIntegerForKey("Level",1);

	edgeNode = Node::create();
	sceneGame->addChild(edgeNode);
	m_CurrentStone = 0;

	this->m_sprite = cocos2d::Sprite::create("Sprites/Main/Warrior_animations/Right_Side/PNG_Sequences/Warrior_clothes_empty/Idle_Blinking/0_Warrior_Idle_000.png");
	this->m_sprite->setPosition(50, 50);
	this->m_sprite->setScale(1.5);
	this->sceneGame->addChild(this->m_sprite);
	physicsBody = PhysicsBody::createBox(this->m_sprite->getContentSize() / 3);
	//physicsBody->setDynamic(false);
	physicsBody->setRotationEnable(false);
	physicsBody->setCollisionBitmask(Model::BITMASK_PLAYER);
	physicsBody->setContactTestBitmask(1);

	this->m_sprite->setPhysicsBody(physicsBody);
	this->m_sprite->setTag(playertag);
	physicsBody->setGravityEnable(false);
	m_CurrentState = ACTION_IDLE;
	m_CurrentFace = FACE_DEFAULT;
	m_CurrentSkill = SKILL_DEFAULT;
	updateLevel();
	m_health = MaxHealth;


	particleMove = ParticleSystemQuad::create("Particles/move_fire.plist");
	SetParticleMove();
	ParticlePow();
	dragon = new DragonSkill(sceneGame);

}

void Player::Collision()
{
}

void Player::updateLevel()
{
	if (Level == 3) {
		auto particleSystem = ParticleSystemQuad::create("Particles/uplevel.plist");
		particleSystem->setPosition(m_sprite->getPosition());
		particleSystem->setScale(0.7f);
		sceneGame->addChild(particleSystem);
		ResourceManager::GetInstance()->Init("DataPlayerLv2.bin");
		SetState(ACTION_ATTACK);
	}
	if(Level>=5) {
		auto particleSystem = ParticleSystemQuad::create("Particles/uplevel.plist");
		particleSystem->setPosition(m_sprite->getPosition());
		particleSystem->setScale(0.7f);
		sceneGame->addChild(particleSystem);
		ResourceManager::GetInstance()->Init("DataPlayerLv3.bin");
		SetState(ACTION_ATTACK);
	}
	MaxExp += Level * 50;
	AttackSpeed = 1.0f + (Level - 1) * 0.05;
	MoveSpeed = 1.0f;
	MaxHealth = Level * 300;
	m_dame = Level * 30;
	Armor = Level * 5;
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
	if(state != m_CurrentState)
	switch (m_CurrentFace) {
	case FACE_RIGHT:
	case FACE_LEFT:
		if (state != m_CurrentState) {
			m_sprite->stopAllActions();
			m_sprite->runAction(DieRight1());
		}
		else if (m_sprite->getNumberOfRunningActions() == 0) {
			m_sprite->runAction(DieRight1());
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
			if(onAngry) m_sprite->runAction(AttackRightAngry());
			else m_sprite->runAction(AttackRight());
		}
		else if (m_sprite->getNumberOfRunningActions() == 0) {
			
			if(onAngry) m_sprite->runAction(AttackRightAngry());
			else m_sprite->runAction(AttackRight());
		}
		break;
	case FACE_RIGHT:
		if (state != m_CurrentState) {
			m_sprite->stopAllActions();
			if (onAngry) m_sprite->runAction(AttackRightAngry());
			else m_sprite->runAction(AttackRight());
		}
		else if (m_sprite->getNumberOfRunningActions() == 0) {
			if (onAngry) m_sprite->runAction(AttackRightAngry());
			else m_sprite->runAction(AttackRight());
		}
		break;
	case FACE_UP:
		if (state != m_CurrentState) {
			m_sprite->stopAllActions();
			if (onAngry) m_sprite->runAction(AttackUpAngry());
			else m_sprite->runAction(AttackUp());
		}
		else if (m_sprite->getNumberOfRunningActions() == 0) {
			if (onAngry) m_sprite->runAction(AttackUpAngry());
			else m_sprite->runAction(AttackUp());
		}
		break;
	case FACE_DOWN:
		if (state != m_CurrentState) {
			m_sprite->stopAllActions();
			if (onAngry) m_sprite->runAction(AttackDownAngry());
			else m_sprite->runAction(AttackDown());
		}
		else if (m_sprite->getNumberOfRunningActions() == 0) {
			if (onAngry) m_sprite->runAction(AttackDownAngry());
			else m_sprite->runAction(AttackDown());
		}
		break;
	}
	if (Level >= 1) SetSkill();
}
void Player::SetHurt(int state) {
	if (state != m_CurrentState)
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
void Player::SetMove(int state)
{
}
void Player::SetSkill()
{
	switch (m_CurrentSkill)
	{
	case SKILL_FIRE:
		SetSkillFire();
		break;
	case SKILL_FIRE_2:
   		onDragon = true;
		dragon->physicsBody->setEnabled(true);
		dragon->m_dragon->setPosition(m_sprite->getPosition() + Vec2(-20, 30));
		break;
	case SKILL_ICE:
		SetSkillIce();
		break;
	case SKILL_ICE_2:
		onShield = true;
		Armor += Level * 30;
		break;
	case SKILL_FIRE_ICE:
		SetSkillFireIce();
	default:
		SetSkillDefault();
		break;
	}
}
void Player::SetSkillFire()
{
	if (edgeNode->getTag() != ATTACK_FIRE) {
		auto edgeBody = PhysicsBody::createEdgeBox(Size(70, 70)); 
		edgeBody->setContactTestBitmask(Model::BITMASK_PLAYER);
		edgeBody->setCollisionBitmask(false);
		edgeNode->setPhysicsBody(edgeBody);
		edgeNode->setPosition(m_sprite->getPosition());
		edgeNode->setTag(ATTACK_FIRE);
	}
	auto particleSystem = ParticleAttack("Particles/skill_fire.plist");
	particleSystem->setPosition(edgeNode->getPosition());
	sceneGame->addChild(particleSystem);
}

void Player::SetSkillFireIce()
{
	if (edgeNode->getTag() != ATTACK_FIRE_ICE) {
		auto edgeBody = PhysicsBody::createEdgeBox(Size(350, 350));
		edgeBody->setContactTestBitmask(Model::BITMASK_PLAYER);
		edgeBody->setCollisionBitmask(false);
		edgeNode->setPhysicsBody(edgeBody);
		edgeNode->setPosition(m_sprite->getPosition());
		edgeNode->setTag(ATTACK_FIRE_ICE);
	}
	auto particleSystem = ParticleSystemQuad::create("Particles/skill_fire_ice.plist");
	particleSystem->setPosition(edgeNode->getPosition());
	sceneGame->addChild(particleSystem);
}

void Player::SetSkillIce()
{
 	if (edgeNode->getTag() != ATTACK_ICE) {
		PhysicsBody* edgeBody;
		if (edgeNode->getRotation() == 0) edgeBody = PhysicsBody::createEdgeBox(Size(30, 70));
		else edgeBody = PhysicsBody::createEdgeBox(Size(70, 30));
		edgeBody->setContactTestBitmask(Model::BITMASK_PLAYER);
		edgeBody->setCollisionBitmask(false);
		edgeNode->setPhysicsBody(edgeBody);
		edgeNode->setPosition(m_sprite->getPosition());
		edgeNode->setTag(ATTACK_ICE);
	}
	auto particleSystem = ParticleAttack("Particles/skill_ice.plist");
	particleSystem->setPosition(edgeNode->getPosition());
	sceneGame->addChild(particleSystem);
	switch (m_CurrentFace)
	{
	case FACE_RIGHT:
		edgeNode->runAction(MoveBy::create(0.3f, Vec2(60, 0)+physicsBody->getVelocity()/3));
		particleSystem->runAction(MoveBy::create(0.3f, Vec2(60, 0)+physicsBody->getVelocity()/2));
		break;
	case FACE_UP:
		edgeNode->runAction(MoveBy::create(0.3f, Vec2(0, 60) + physicsBody->getVelocity() / 3));
		particleSystem->runAction(MoveBy::create(0.3f, Vec2(0, 60) + physicsBody->getVelocity() / 2));
		break;
	case FACE_DOWN:
		edgeNode->runAction(MoveBy::create(0.3f, Vec2(0, -60) + physicsBody->getVelocity() / 3));
		particleSystem->runAction(MoveBy::create(0.3f, Vec2(0, -60) + physicsBody->getVelocity() / 2));
		break;
	case FACE_LEFT:
		edgeNode->runAction(MoveBy::create(0.3f, Vec2(-60, 0) + physicsBody->getVelocity() / 3));
		particleSystem->runAction(MoveBy::create(0.3f, Vec2(-60, 0) + physicsBody->getVelocity() / 2));
		break;
	}
}
void Player::SetSkillDefault()
{
	if (edgeNode->getTag() != NORMALSKILL) {
		auto edgeBody = PhysicsBody::createEdgeBox(Size(25, 55));
		edgeBody->setContactTestBitmask(Model::BITMASK_PLAYER);
		edgeBody->setCollisionBitmask(false);
		edgeNode->setPhysicsBody(edgeBody);
		edgeNode->setTag(NORMALSKILL);
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
	if(m_CurrentState != ACTION_DIE)
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
	if (timeDie >= 5) {
		timeDie = 0;
		m_sprite->setPosition(100, 100);
		updateLevel();
		m_health = MaxHealth;
		m_CurrentState = ACTION_DEFAULT;
		m_CurrentFace = FACE_DEFAULT;
		SetFace(Vec2(0, 0));
		edgeNode->setPosition(Vec2(1000, 1000));
		physicsBody->setEnabled(true);
	}
}

void Player::SetFace(Vec2 velocity)
{
	float radian = std::atan2f(velocity.y, velocity.x);
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
	return ObjectParent::AnimationObjectOnce(6, "Warrior_Attack_2", AttackSpeed);
}
cocos2d::RepeatForever* Player::IdleRight() {
	return ObjectParent::AnimationObjectRepeat(1, "Warrior_Idle", AttackSpeed);
}
cocos2d::Animate* Player::AttackRightAngry() {
	return ObjectParent::AnimationObjectOnce(5, "Warrior_Attack_2", AttackSpeed);
}
cocos2d::RepeatForever* Player::DieRight1() {
	return ObjectParent::AnimationObjectRepeat(4, "Warrior_Died", AttackSpeed);
}
cocos2d::Animate* Player::DieRight() {
	return NULL;
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
void Player::SetParticleMove() {
	CCLOG("%d", m_CurrentStone);
	std::string name;
	switch (m_CurrentStone)
	{
	case STONE_FIRE:
		name = "Particles/move_fire.plist";
		break;
	case STONE_ICE:
		name = "Particles/move_ice.plist";
		break;
	case STONE_FIRE_ICE:
		name = "Particles/moveee.plist";
		break;
	default:
		name = "Particles/move_fire.plist";
		break;
	}
	particleMove->removeFromParentAndCleanup(true);
	particleMove = ParticleSystemQuad::create(name);
	particleMove->setScale(0.3f);
	particleMove->setSpeed(100);
	if(m_CurrentStone == STONE_FIRE_ICE) {
		particleMove->setSpeed(0);
		particleMove->setScale(0.2f);
	}
	particleMove->setAngle(90);
	particleMove->setPosition(m_sprite->getPosition()-Vec2(0,20));
	particleMove->setDuration(ParticleSystem::DURATION_INFINITY);
	sceneGame->addChild(particleMove,-1);
}
int temp = 0;
void Player::CheckShield(float deltaTime)
{
	if (onShield) {
		timeShield += deltaTime*2;
		if ((int)timeShield % 2 == 0 && (int)timeShield != temp) {
			m_health += Level * 50;
			auto particleSystem = ParticleSystemQuad::create("Particles/up_heal.plist");
			particleSystem->setScale(0.3f);
			particleSystem->setPosition(m_sprite->getPosition());
			sceneGame->addChild(particleSystem);
			temp = (int)timeShield;
		}
		if (timeShield >= 10) {
			timeShield = 0;
			onShield = false;
		}
	}
}

void Player::CheckDragon(float deltaTime)
{
	if (onDragon) {
		dragon->Update(deltaTime);
		if (dragon->countTimeExis > 20) onDragon = false;
	}

}

void Player::CheckAttackAndSkill(float deltaTime)
{
	if (m_CurrentState == ACTION_ATTACK) checkAttack = true;
	if (checkAttack) timeAttack += deltaTime;
	if (timeAttack > 2.0f - AttackSpeed) {
		m_CurrentState = ACTION_DEFAULT;
		timeAttack = 0;
		checkAttack = false;
	}
	if (timeAttack > deltaTime&& m_CurrentSkill == SKILL_DEFAULT) {
		edgeNode->setPosition(Vec2(10000, 10000));
	}
	if (timeAttack > 0.15 && m_CurrentSkill == SKILL_FIRE) {
		edgeNode->setPosition(Vec2(10000, 10000));
	}
	if (timeAttack > 0.4 && m_CurrentSkill == SKILL_ICE) {
		edgeNode->setPosition(Vec2(10000, 10000));
	}
	if (timeAttack > 0.4 && m_CurrentSkill == SKILL_FIRE_ICE) {
		edgeNode->setPosition(Vec2(10000, 10000));
	}
}
void Player::ParticlePow() {
	particlePow = ParticleSystemQuad::create("Particles/power.plist");
	particlePow->setScale(0.3f);
	particlePow->setVisible(false);
	sceneGame->addChild(particlePow, -1);
}