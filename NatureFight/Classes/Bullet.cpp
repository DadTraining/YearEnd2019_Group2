#include "Bullet.h"
#include <ResourceManager.h>




Bullet::Bullet(cocos2d::Scene* scene)
{
	sceneGame = scene;
	this->m_sprite = DuplicateSprite(ResourceManager::GetInstance()->GetSpriteById(3));
	auto move = cocos2d::MoveBy::create(1, Vec2(0, 480));
	m_sprite->runAction(move);
}

Bullet::~Bullet()
{
}

void Bullet::Init()
{
}

void Bullet::Update(float deltaTime)
{
}

