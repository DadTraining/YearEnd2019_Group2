#include "DragonSkill.h"

DragonSkill::DragonSkill(Scene* scene)
{
	sceneGame = scene;
	Init();
}

void DragonSkill::Update(float deltaTime)
{
	//countTimeExis += deltaTime;
	DragonAttacked += deltaTime;
	if (countTimeExis > 30) {
		m_dragon->stopAllActions();
		m_dragon->runAction(MoveBy::create(2.0f, Vec2(0, 20000)));
		physicsBody->setEnabled(false);
		countTimeExis = 0;
	}
	particleMove->setPosition(m_dragon->getPosition());
}

void DragonSkill::Init()
{
	this->m_dragon = cocos2d::Sprite::create("Sprites/pet/Fire_Dragon_1.png");
	this->m_dragon->setPosition(Vec2(10000, 10000));
	sceneGame->addChild(this->m_dragon,5);
	physicsBody = PhysicsBody::createEdgeBox(this->m_dragon->getContentSize() / 3);
	physicsBody->setContactTestBitmask(Model::BITMASK_PLAYER);
	physicsBody->setCollisionBitmask(false);
	this->m_dragon->setPhysicsBody(physicsBody);
	this->m_dragon->setTag(DRAGONTAG);

	particleMove = ParticleSystemQuad::create("Particles/move_fire.plist");
	sceneGame->addChild(particleMove);

	AnimationDragon();
}

float DragonSkill::Distance(Vec2 A, Vec2 B)
{
	return std::sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
}

void DragonSkill::SetFace(Vec2 move)
{
	if (move.x < m_dragon->getPosition().x && faceRight) {
		m_dragon->setFlipX(true);
		faceRight = !faceRight;
		particleMove->setAngle(0);
	}
	if (move.x > m_dragon->getPosition().x && !faceRight) {
		m_dragon->setFlipX(false);
		faceRight = !faceRight;
		particleMove->setAngle(180);
	}
}
void DragonSkill::AnimationDragon()
{
	cocos2d::SpriteFrameCache* spriteCache;
	spriteCache = ResourceManager::GetInstance()->GetFrameAIById(898);
	cocos2d::Vector<cocos2d::SpriteFrame*> exFrames;
	int i = 1;
	std::string link;
	while (true) {
		link = "Fire_Dragon_" + std::to_string(i) + ".png";
		if (spriteCache->getSpriteFrameByName(link) == nullptr) break;
		exFrames.pushBack(spriteCache->getSpriteFrameByName(link));
		i++;
	}
	auto animation = cocos2d::Animation::createWithSpriteFrames(exFrames, 0.3f);
	auto animate = cocos2d::Animate::create(animation);
	cocos2d::RepeatForever* repeat = cocos2d::RepeatForever::create(animate);
	m_dragon->runAction(repeat);
}

