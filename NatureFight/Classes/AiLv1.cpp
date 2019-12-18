#include "AiLv1.h"
#include <vector> 
AiLv1::AiLv1(cocos2d::Scene* scene)
{
	sceneGame = scene;
}

void AiLv1::Update(float deltaTime)
{
}

void AiLv1::Init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//spriteCache ->addSpriteFramesWithFile("Sprites/Man1/Goblin/PNG/PNG Sequences/Slashing/spritesAttackGoblin.plist");
	this->m_sprite= cocos2d::Sprite::create("Sprites/Man1/Goblin/PNG/PNG Sequences/Running/0_Goblin_Running_000.png");
	this->m_sprite->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	this->m_sprite->setScale(0.2);
	this->sceneGame->addChild(this->m_sprite);
}

void AiLv1::Collision()
{
}
cocos2d::RepeatForever* AiLv1::Moving() {
	int numFrame = 12;
	auto spriteCache= SpriteFrameCache::getInstance();
	spriteCache->addSpriteFramesWithFile("Sprites/Man1/Goblin/PNG/PNG Sequences/Running/spritesGobin.plist");
	cocos2d::Vector<cocos2d::SpriteFrame*> exFrames;
	std::string name;
	for (int i = 0; i < numFrame; i++) {
		if (i<10)
		{
			name = "0_Goblin_Running_00" + std::to_string(i) + ".png";
		}
		else {
			name= "0_Goblin_Running_0" + std::to_string(i) + ".png";
		}
	
		exFrames.pushBack(spriteCache->getSpriteFrameByName(name));
	}
	auto animation = cocos2d::Animation::createWithSpriteFrames(exFrames,0.05f);
	auto animate = cocos2d::Animate::create(animation);
	cocos2d::RepeatForever* repeat = cocos2d::RepeatForever::create(animate);
	return repeat;
}
cocos2d::RepeatForever* AiLv1::Attack() {
	int numFrame = 12;
	auto spriteCacheAttack = SpriteFrameCache::getInstance();
	spriteCacheAttack->addSpriteFramesWithFile("Sprites/Man1/Goblin/PNG/PNG Sequences/Slashing/sprites.plist");
	cocos2d::Vector<cocos2d::SpriteFrame*> exFrames;
	std::string name;
	for (int i = 0; i < numFrame; i++) {
		if (i < 10)
		{
			name = "0_Goblin_Slashing_00" + std::to_string(i) + ".png";
		}
		else {
			name = "0_Goblin_Slashing_0" + std::to_string(i) + ".png";
		}
		exFrames.pushBack(spriteCacheAttack->getSpriteFrameByName(name));
	}
	auto animation = cocos2d::Animation::createWithSpriteFrames(exFrames, 0.05f);
	auto animate = cocos2d::Animate::create(animation);
	cocos2d::RepeatForever* repeat = cocos2d::RepeatForever::create(animate);
	return repeat;
}