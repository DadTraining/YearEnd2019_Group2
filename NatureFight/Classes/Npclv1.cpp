#include "Npclv1.h"
#include "SimpleAudioEngine.h"
#define NpcSolotag 11
USING_NS_CC;

//using namespace CocosDenshion;
Npclv1::Npclv1(cocos2d::Scene* scene)
{
	sceneGame = scene;
}

void Npclv1::Update(float deltaTime)
{
	count += deltaTime;

	
}

void Npclv1::Init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	this->m_sprite = cocos2d::Sprite::create("Sprites/Man1/NPC(Solo)/PNG/Front/PNG Sequences/Greeting/0_Citizen_Greeting_000.png");
	this->m_sprite->setScale(0.1);
	this->m_sprite->setAnchorPoint(Vec2(0.5, 0.5));
	this->m_sprite->setPosition(Point(visibleSize.width / 1.5 +150, visibleSize.height / 2));
	this->sceneGame->addChild(this->m_sprite,2);
	auto a = m_sprite->getContentSize().width;
	auto b = m_sprite->getContentSize().height+1000;
	auto Body = PhysicsBody::createBox(cocos2d::Size(a,b));
	this->m_sprite->setPhysicsBody(Body);
	Body->setDynamic(false);
	Body->setGravityEnable(false);
	Body->setRotationEnable(false);
	m_sprite->getPhysicsBody()->setContactTestBitmask(1);
	m_sprite->setTag(NpcSolotag);
	
}

void Npclv1::Collision(/*Sprite main*/)
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
	auto fadeOut = FadeOut::create(3.0f);
	//label1->runAction(fadeOut);
	//label3->runAction(fadeOut);
	mess->runAction(fadeOut);

	auto jumpy = JumpBy::create(1.5, Vec2(-50, -30), 100, 1);
	auto fadehue = FadeOut::create(2.5f);
	auto jumpfade = Spawn::create(jumpy, fadehue, nullptr);
	auto remove = RemoveSelf::create(); // clean up memory
	auto doubletrouble = Sequence::create( remove, nullptr);
	label1->runAction(doubletrouble);

}

cocos2d::RepeatForever * Npclv1::Hello()
{
	auto spriteCache = SpriteFrameCache::getInstance();
	spriteCache->addSpriteFramesWithFile("Sprites/Man1/NPC(Solo)/PNG/Front/PNG Sequences/Greeting/Greeting.plist");
	cocos2d::Vector<cocos2d::SpriteFrame*> exFrames;
	std::string name;
	for (int i = 0; i < 30; i++) {
		if (i<10)
		{
			name = "0_Citizen_Greeting_00" + std::to_string(i) + ".png";
		}
		else {
			name = "0_Citizen_Greeting_0" + std::to_string(i) + ".png";
		}

		exFrames.pushBack(spriteCache->getSpriteFrameByName(name));
	}
	auto animation = cocos2d::Animation::createWithSpriteFrames(exFrames, 0.05f);
	auto animate = cocos2d::Animate::create(animation);
	cocos2d::RepeatForever* repeat = cocos2d::RepeatForever::create(animate);
	return repeat;
}

cocos2d::RepeatForever * Npclv1::Communication()
{
	auto spriteCache = SpriteFrameCache::getInstance();
	spriteCache->addSpriteFramesWithFile("Sprites/Man1/NPC(Solo)/PNG/Front/PNG Sequences/Communication/communication.plist");
	cocos2d::Vector<cocos2d::SpriteFrame*> exFrames;
	std::string name;
	for (int i = 0; i < 30; i++) {
		if (i<10)
		{
			name = "0_Citizen_Communication_00" + std::to_string(i) + ".png";
		}
		else {
			name = "0_Citizen_Communication_0" + std::to_string(i) + ".png";
		}

		exFrames.pushBack(spriteCache->getSpriteFrameByName(name));
	}
	auto animation = cocos2d::Animation::createWithSpriteFrames(exFrames, 0.05f);
	auto animate = cocos2d::Animate::create(animation);
	cocos2d::RepeatForever* repeat = cocos2d::RepeatForever::create(animate);


	return repeat;
}
