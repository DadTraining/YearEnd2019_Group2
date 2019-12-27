#include "Rock.h"
#include <ResourceManager.h>


Rock::Rock(cocos2d::Scene* scene)
{
	gameScene = scene;
	this->m_sprite = DuplicateSprite(ResourceManager::GetInstance()->GetSpriteById(4));
	int x = cocos2d::RandomHelper::random_int(0, 300);
	auto move = cocos2d::MoveBy::create(1, Vec2(-x, -500));
	this->m_sprite->runAction(move);
}

Rock::~Rock()
{
	delete m_sprite;
}

void Rock::Init()
{
}

void Rock::Update(float deltaTime)
{
}
