#include "AiLv1.h"

#define ATTACK 0
#define RUN 1

AiLv1::AiLv1(cocos2d::Scene* scene)
{
	sceneGame = scene;
}

void AiLv1::Update(float deltaTime)
{
	if (physicsBody->getVelocity().x < 0)
	{
		faceRight = false;

	}
	else
	{
		faceRight = true;

	}
	if (faceRight) {
		m_sprite->setFlippedX(false);
	}
	else
	{
		m_sprite->setFlippedX(true);
	}
}

void AiLv1::Init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//spriteCache ->addSpriteFramesWithFile("Sprites/Man1/Goblin/PNG/PNG Sequences/Slashing/spritesAttackGoblin.plist");
	this->m_sprite = cocos2d::Sprite::create("Sprites/Man1/Goblin/PNG/PNG Sequences/Running/0_Goblin_Running_000.png");
	this->m_sprite->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	this->m_sprite->setScale(0.1);
	this->sceneGame->addChild(this->m_sprite,2);
	//create physic
	physicsBody = PhysicsBody::createBox(m_sprite->getContentSize());
	m_sprite->setTag(2);
	//add physicsBody 
	m_sprite->setPhysicsBody(physicsBody);
	//dynamic=false is  hold character
	physicsBody->setDynamic(false);
	//set trong luc = false 
	physicsBody->setGravityEnable(false);
	physicsBody->setRotationEnable(false);
	m_sprite->getPhysicsBody()->setContactTestBitmask(1);
}
void AiLv1::Collision()
{
	auto mess = Sprite::create("Sprites/Man1/NPC(Solo)/PNG/mess-removebg-preview.png");
	mess->setPosition(this->m_sprite->getPosition());
	mess->setScale(0.3);
	mess->setAnchorPoint(Vec2(0, 0));
	this->sceneGame->addChild(mess);
	auto label1 = Label::createWithSystemFont("xin chao ", "Arial", 16);
	label1->setAnchorPoint(Vec2(0, 0));
	label1->setPositionX(mess->getPositionX() + 25);
	label1->setPositionY(mess->getPositionY() + 60);
	label1->setTextColor(Color4B::BLACK);
	this->sceneGame->addChild(label1);
	auto label3 = Label::createWithSystemFont("Toi la NPC ", "Arial", 16);
	label3->setAnchorPoint(Vec2(0, 0));
	label3->setPositionX(mess->getPositionX() + 25);
	label3->setPositionY(mess->getPositionY() + 40);
	label3->setTextColor(Color4B::BLACK);
	this->sceneGame->addChild(label3);
}
cocos2d::RepeatForever* AiLv1::Moving() {
	int numFrame = 12;
	auto spriteCache = SpriteFrameCache::getInstance();
	spriteCache->addSpriteFramesWithFile("Sprites/Man1/Goblin/PNG/PNG Sequences/Running/Running.plist");
	cocos2d::Vector<cocos2d::SpriteFrame*> exFrames;
	std::string name;
	for (int i = 0; i < numFrame; i++) {
		if (i < 10)
		{
			name = "0_Goblin_Running_00" + std::to_string(i) + ".png";
		}
		else {
			name = "0_Goblin_Running_0" + std::to_string(i) + ".png";
		}

		exFrames.pushBack(spriteCache->getSpriteFrameByName(name));
	}
	auto animation = cocos2d::Animation::createWithSpriteFrames(exFrames, 0.05f);
	auto animate = cocos2d::Animate::create(animation);
	cocos2d::RepeatForever* repeat = cocos2d::RepeatForever::create(animate);
	repeat->setTag(RUN);
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
	repeat->setTag(ATTACK);
	physicsBody->setVelocity(Vec2(0, 0));
	return repeat;
}