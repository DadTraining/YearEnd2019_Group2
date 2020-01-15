#include "AiLv1.h"
#include <vector> 
#include <ResourceManager.h>
AiLv1::AiLv1(cocos2d::Scene* scene)
{
	sceneGame = scene;
	Init();
}
float timeAttackAI = 0, timeDieAI = 0, timeColor = 0;
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
	if (!(m_sprite->getColor() == ccc3(255, 255, 255))) {
		timeColor += deltaTime;
		if (timeColor >= 1) {
			m_sprite->setColor(ccc3(255, 255, 255));
			timeColor = 0;
		}
	}
}


void AiLv1::Init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	m_health = 30;
	this->m_sprite = cocos2d::Sprite::create("Sprites/Main/Warrior_animations/Right_Side/PNG_Sequences/Warrior_clothes_empty/Idle_Blinking/0_Warrior_Idle_000.png");
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
	m_CurrentState = ACTION_IDLE;
	m_CurrentFace = FACE_DEFAULT;
	AttackSpeed = 1;
	auto edgeBody = PhysicsBody::createEdgeBox(Size(20, 20));
	edgeBody->setContactTestBitmask(Model::BITMASK_MONSTER);
	edgeBody->setCollisionBitmask(false);
	edgeNode = Node::create();
	edgeNode->setPosition(m_sprite->getPosition());
	sceneGame->addChild(edgeNode);
	edgeNode->setPhysicsBody(edgeBody);
	edgeNode->setTag(CREEPATTACK);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(AiLv1::onContactBegin, this);
	sceneGame->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, sceneGame);
}

float timem = 0;
void AiLv1::Collision(Player* player, float deltaTime)
{
	this->player = player;
	Update(deltaTime);
	timem += deltaTime;
	if ((Distance(this->m_sprite->getPosition(), player->m_sprite->getPosition())) <= 80) {
		if (timem > 0.3f) {
			SetState(AiLv1::ACTION_ATTACK);
			this->physicsBodyChar->setVelocity(Vec2(0, 0));
			timem = 0;
		}
	}
	if (Distance(player->m_sprite->getPosition(), this->m_sprite->getPosition()) < 100 && (Distance(this->m_sprite->getPosition(), player->m_sprite->getPosition())) > 80)
		this->physicsBodyChar->setVelocity(player->m_sprite->getPosition() - this->m_sprite->getPosition());
	else this->physicsBodyChar->setVelocity(Vec2(0, 0));
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
void AiLv1::SetHurt(int state)
{
}
void AiLv1::SetHurtAi(int state, int skill) {
	if (state != m_CurrentState) {
		m_sprite->stopAllActions();
		if (skill == NORMALSKILL) {
			m_sprite->setColor(ccc3(255, 0, 0));
		}
		else if (skill == ATTACK_ICE) {
			m_sprite->setColor(ccc3(0, 0, 255));
		}
		else if (skill == ATTACK_FIRE) {
			m_sprite->setColor(ccc3(255, 0, 0));
		}
	}
	else if (m_sprite->getNumberOfRunningActions() == 0) {
		m_sprite->runAction(HurtRight());
	}
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
	return ObjectParent::AnimationObjectRepeat(101, "Goblin_Running", AttackSpeed);
}
cocos2d::Animate* AiLv1::AttackRight() {
	return ObjectParent::AnimationObjectOnce(102, "Goblin_Slashing", AttackSpeed);
}
cocos2d::RepeatForever* AiLv1::IdleRight() {
	return ObjectParent::AnimationObjectRepeat(100, "Goblin_Idle", AttackSpeed);
}
cocos2d::Animate* AiLv1::AttackRightAngry() {
	return ObjectParent::AnimationObjectOnce(105, "Goblin_Kicking", AttackSpeed);
}
cocos2d::RepeatForever* AiLv1::DieRight() {
	return ObjectParent::AnimationObjectRepeat(104, "Goblin_Dying", AttackSpeed);
}
cocos2d::Animate* AiLv1::HurtRight() {
	return ObjectParent::AnimationObjectOnce(103, "Goblin_Hurt", AttackSpeed);
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
bool AiLv1::onContactBegin(const PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA->getTag() == m_sprite->getTag() & (nodeB->getTag() == ATTACK_ICE | nodeB->getTag() == ATTACK_FIRE | nodeB->getTag() == NORMALSKILL)
		|| nodeB->getTag() == m_sprite->getTag() & (nodeA->getTag() == ATTACK_ICE | nodeA->getTag() == ATTACK_FIRE | nodeA->getTag() == NORMALSKILL))
	{
		m_health -= 10;
		if (player->edgeNode->getTag() == NORMALSKILL)	SetState(ACTION_HURT);
		else if (player->edgeNode->getTag() == ATTACK_ICE) SetState(ACTION_HURT_ICE);
		else if (player->edgeNode->getTag() == ATTACK_FIRE) SetState(ACTION_HURT_FIRE);
		if (m_health == 0) {
			m_sprite->runAction(DieRight());
			physicsBodyChar->setEnabled(false);
			player->Exp += 20;
			CCLOG("exp: %d", player->Exp);
		}
	}
	if (nodeA->getTag() == DRAGONTAG & nodeB->getTag() == m_sprite->getTag() || nodeB->getTag() == DRAGONTAG & nodeA->getTag() == m_sprite->getTag()) {
		std::srand(time(NULL));
		int x = std::rand() % 25 + 50;
		int y = std::rand() % 25 + 50;
		int x1 = std::rand() % 25 + 50;
		int y1 = std::rand() % 25 + 50;
		x = x > x1?x:-x1;
		y = y > y1?y:-y1;
		Vec2 temp = m_sprite->getPosition() - player->dragon->m_dragon->getPosition();
		float s = Distance(Vec2(x,y), Vec2(0,0));
		if ((int)temp.x<=10 && (int)temp.y<=10 ) {
			SetState(ACTION_HURT_FIRE);
			m_health -= 10;
			player->dragon->m_dragon->runAction(MoveBy::create(s/70, Vec2(x, y)));
			player->onDragonAttack = false;
			player->dragon->SetFace(Vec2(x, y)+ player->dragon->m_dragon->getPosition());
			if (m_health == 0) {
				m_sprite->runAction(DieRight());
				physicsBodyChar->setEnabled(false);
				player->Exp += 20;
				CCLOG("exp: %d", player->Exp);
			}
		}
	}
	return true;
}
