#include <Player.h>
#include "SimpleAudioEngine.h"
#define playertag 1000
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
	this->m_sprite = cocos2d::Sprite::create("Sprites/Main/Warrior_animations/Right_Side/PNG_Sequences/Warrior_clothes_empty/Idle Blinking/0_Warrior_Idle Blinking_000.png");
	this->m_sprite->setPosition(Point(visibleSize.width / 1.5, visibleSize.height / 2));
	this->m_sprite->setScale(0.1);
	this->sceneGame->addChild(this->m_sprite,12);

	auto a = m_sprite->getContentSize().width/2;
	auto b = m_sprite->getContentSize().height/2;
	physicsBody = PhysicsBody::createBox(Size(a, b));
	/*physicsBody->setDynamic(false);
	this->m_sprite->setPhysicsBody(physicsBody);
	m_sprite->getPhysicsBody()->setContactTestBitmask(true);
	m_sprite->setTag(playertag);
	physicsBody->setCollisionBitmask(5);
	physicsBody->setGravityEnable(false);*/
	//physicsBody->setDynamic(false); //false :  cho xuyen quan nhau
	physicsBody->setGravityEnable(false);
	physicsBody->setRotationEnable(false);
	m_sprite->setTag(playertag);
	//physicsBody->setMass(100);
	physicsBody->setCollisionBitmask(101);
	physicsBody->setContactTestBitmask(1);
	m_sprite->setPhysicsBody(physicsBody);

}

void Player::Collision()
{
}
cocos2d::RepeatForever* Player::MovingRight() {
	auto spriteCache= SpriteFrameCache::getInstance();
	spriteCache->addSpriteFramesWithFile("Sprites/Main/Warrior_animations/Right_Side/PNG Sequences/Warrior_clothes_1/Run/Main.plist");
	cocos2d::Vector<cocos2d::SpriteFrame*> exFrames;
	for (int i = 0; i <= 14; i++) {
		std::string name;
		if (i < 10) name = "0_Warrior_Run_00" + std::to_string(i) + ".png";
		if (i >= 10) name = "0_Warrior_Run_0" + std::to_string(i) + ".png";
		exFrames.pushBack(spriteCache->getSpriteFrameByName(name));
	}
	auto animation = cocos2d::Animation::createWithSpriteFrames(exFrames,0.03f);
	auto animate = cocos2d::Animate::create(animation);
	cocos2d::RepeatForever* repeat = cocos2d::RepeatForever::create(animate);
	return repeat;
}
cocos2d::Animate* Player::AttackRight() {
	auto spriteCacheAttack = SpriteFrameCache::getInstance();
	spriteCacheAttack->addSpriteFramesWithFile("Sprites/Main/Warrior_animations/Right_Side/PNG Sequences/Warrior_clothes_1/Attack_1/Main.plist");
	cocos2d::Vector<cocos2d::SpriteFrame*> exFrames;
	for (int i = 1; i <= 14; i++) {
		std::string name;
		if (i < 10) name = "0_Warrior_Attack_1_00" + std::to_string(i) + ".png";
		if (i >= 10) name = "0_Warrior_Attack_1_0" + std::to_string(i) + ".png";
		exFrames.pushBack(spriteCacheAttack->getSpriteFrameByName(name));
	}
	auto animation = cocos2d::Animation::createWithSpriteFrames(exFrames, 0.03f);
	auto animate = cocos2d::Animate::create(animation);
	return animate;
}

cocos2d::RepeatForever* Player::IdleRight()
{
	auto spriteCache = SpriteFrameCache::getInstance();
	spriteCache->addSpriteFramesWithFile("Sprites/Main/Warrior_animations/Right_Side/PNG Sequences/Warrior_clothes_1/Idle Blinking/Main.plist");
	cocos2d::Vector<cocos2d::SpriteFrame*> exFrames;
	std::string name;
	for (int i = 1; i < 30; i++) {
		
		if (i < 10) name = "0_Warrior_Idle Blinking_00" + std::to_string(i) + ".png";
		if (i >= 10) name = "0_Warrior_Idle Blinking_0" + std::to_string(i) + ".png";

		exFrames.pushBack(spriteCache->getSpriteFrameByName(name));
	}
	auto animation = cocos2d::Animation::createWithSpriteFrames(exFrames, 0.03f);
	auto animate = cocos2d::Animate::create(animation);
	cocos2d::RepeatForever* repeat = cocos2d::RepeatForever::create(animate);
	return repeat;
}

cocos2d::RepeatForever* Player::AttackRightAngry()
{
	auto spriteCache = SpriteFrameCache::getInstance();
	spriteCache->addSpriteFramesWithFile("Sprites/Main/Warrior_animations/Right_Side/PNG Sequences/Warrior_clothes_1/Idle Blinking/Main.plist");
	cocos2d::Vector<cocos2d::SpriteFrame*> exFrames;
	for (int i = 1; i <= 30; i++) {
		std::string name;
		if (i < 10) name = "0_Warrior_Idle Blinking_00" + std::to_string(i) + ".png";
		if (i >= 10) name = "0_Warrior_Idle Blinking_0" + std::to_string(i) + ".png";

		exFrames.pushBack(spriteCache->getSpriteFrameByName(name));
	}
	auto animation = cocos2d::Animation::createWithSpriteFrames(exFrames, 0.03f);
	auto animate = cocos2d::Animate::create(animation);
	cocos2d::RepeatForever* repeat = cocos2d::RepeatForever::create(animate);
	return repeat;
}
