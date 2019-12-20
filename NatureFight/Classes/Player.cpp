#include <Player.h>
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
Player::Player(cocos2d::Scene* scene)
{
	sceneGame = scene;
}

void Player::Update(FLOAT deltaTime)
{
}

void Player::Init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	this->m_sprite = cocos2d::Sprite::create("Sprites/Main/Warrior_animations/Right_Side/PNG Sequences/Warrior_clothes_empty/Idle Blinking/0_Warrior_Idle Blinking_000.png");
	this->m_sprite->setPosition(Point(visibleSize.width / 1.5, visibleSize.height / 2));
	this->m_sprite->setScale(0.2);
	this->sceneGame->addChild(this->m_sprite);

	physicsBody = PhysicsBody::createBox(this->m_sprite->getContentSize());
	physicsBody->setDynamic(false);
	this->m_sprite->setPhysicsBody(physicsBody);
	physicsBody->setGravityEnable(false);
}

void Player::Collision()
{
}
cocos2d::RepeatForever* Player::MovingRight() {
	auto spriteCache= SpriteFrameCache::getInstance();
	spriteCache->addSpriteFramesWithFile("Sprites/Main/Warrior_animations/Right_Side/PNG Sequences/Warrior_clothes_empty/Run/runlist.plist");
	cocos2d::Vector<cocos2d::SpriteFrame*> exFrames;
	for (int i = 0; i <= 14; i++) {
		std::string name = "0_Warrior_Run_00" + std::to_string(i) + ".png";
		if (i >= 10) name = "0_Warrior_Run_0" + std::to_string(i) + ".png";
		exFrames.pushBack(spriteCache->getSpriteFrameByName(name));
	}
	auto animation = cocos2d::Animation::createWithSpriteFrames(exFrames,0.05f);
	auto animate = cocos2d::Animate::create(animation);
	cocos2d::RepeatForever* repeat = cocos2d::RepeatForever::create(animate);
	return repeat;
}
cocos2d::Animate* Player::AttackRight() {
	auto spriteCacheAttack = SpriteFrameCache::getInstance();
	spriteCacheAttack->addSpriteFramesWithFile("Sprites/Main/Warrior_animations/Right_Side/PNG Sequences/Warrior_clothes_empty/Attack_1/sprites.plist");
	cocos2d::Vector<cocos2d::SpriteFrame*> exFrames;
	for (int i = 1; i <= 15; i++) {
		std::string name = "0_Warrior_Attack_ (" + std::to_string(i) + ").png";
		exFrames.pushBack(spriteCacheAttack->getSpriteFrameByName(name));
	}
	auto animation = cocos2d::Animation::createWithSpriteFrames(exFrames, 0.05f);
	auto animate = cocos2d::Animate::create(animation);
	return animate;
}

cocos2d::RepeatForever* Player::IdleRight()
{
	auto spriteCache = SpriteFrameCache::getInstance();
	spriteCache->addSpriteFramesWithFile("Sprites/Main/Warrior_animations/Right_Side/PNG Sequences/Warrior_clothes_empty/Idle Blinking/PlayerSprites.plist");
	cocos2d::Vector<cocos2d::SpriteFrame*> exFrames;
	for (int i = 1; i <= 30; i++) {
		std::string name = "0_Warrior_Idle Blinking_ (" + std::to_string(i) + ").png";
		exFrames.pushBack(spriteCache->getSpriteFrameByName(name));
	}
	auto animation = cocos2d::Animation::createWithSpriteFrames(exFrames, 0.05f);
	auto animate = cocos2d::Animate::create(animation);
	cocos2d::RepeatForever* repeat = cocos2d::RepeatForever::create(animate);
	return repeat;
}

cocos2d::RepeatForever* Player::AttackRightAngry()
{
	auto spriteCache = SpriteFrameCache::getInstance();
	spriteCache->addSpriteFramesWithFile("Sprites/Main/Warrior_animations/Right_Side/PNG Sequences/Warrior_clothes_empty/Idle Blinking/PlayerSprites.plist");
	cocos2d::Vector<cocos2d::SpriteFrame*> exFrames;
	for (int i = 1; i <= 30; i++) {
		std::string name = "0_Warrior_Idle Blinking_ (" + std::to_string(i) + ").png";
		exFrames.pushBack(spriteCache->getSpriteFrameByName(name));
	}
	auto animation = cocos2d::Animation::createWithSpriteFrames(exFrames, 0.05f);
	auto animate = cocos2d::Animate::create(animation);
	cocos2d::RepeatForever* repeat = cocos2d::RepeatForever::create(animate);
	return repeat;
}
