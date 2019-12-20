#include "Npclv1.h"
#include <vector> 
#include "SimpleAudioEngine.h"
USING_NS_CC;

//using namespace CocosDenshion;
Npclv1::Npclv1(cocos2d::Scene* scene)
{
	sceneGame = scene;
}

void Npclv1::Update(float deltaTime)
{
	count += deltaTime;

	auto mess = Sprite::create("Sprites/Man1/NPC(Solo)/PNG/mess-removebg-preview.png");
	mess->setPosition(this->m_sprite->getPosition());
	mess->setScale(0.3);
	mess->setAnchorPoint(Vec2(0, 0));
	this->sceneGame->addChild(mess);
	auto label1 = Label::createWithSystemFont("xin ", "Arial", 16);
	label1->setPositionX(mess->getPositionX() + 25);
	label1->setPositionY(mess->getPositionY() + 60);
	label1->setTextColor(Color4B::BLACK);
	this->sceneGame->addChild(label1);
	if (count >= 1) {
		auto label2 = Label::createWithSystemFont("chao ", "Arial", 16);
		label2->setPositionX(mess->getPositionX() + 55);
		label2->setPositionY(mess->getPositionY() + 60);
		label2->setTextColor(Color4B::BLACK);
		this->sceneGame->addChild(label2);
	}
	if (count >= 1.5) {
		auto label3 = Label::createWithSystemFont("moi ", "Arial", 16);
		label3->setPositionX(mess->getPositionX() + 25);
		label3->setPositionY(mess->getPositionY() + 40);
		label3->setTextColor(Color4B::BLACK);
		this->sceneGame->addChild(label3);
	}
	if (count >= 2) {
		auto label4 = Label::createWithSystemFont("nguoi !", "Arial", 16);
		label4->setPositionX(mess->getPositionX() + 60);
		label4->setPositionY(mess->getPositionY() + 40);
		label4->setTextColor(Color4B::BLACK);
		this->sceneGame->addChild(label4);
	}

}

void Npclv1::Init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	this->m_sprite = cocos2d::Sprite::create("Sprites/Man1/NPC(Solo)/PNG/Front/PNG Sequences/Greeting/0_Citizen_Greeting_000.png");
	this->m_sprite->setScale(0.2);
	this->m_sprite->setAnchorPoint(Vec2(0.5, 0.5));
	this->m_sprite->setPosition(Point(visibleSize.width / 1.5, visibleSize.height / 2));
	this->sceneGame->addChild(this->m_sprite,2);
	auto Body = PhysicsBody::createBox(m_sprite->getContentSize());
	this->m_sprite->setPhysicsBody(Body);
	Body->setDynamic(false);
	Body->setGravityEnable(false);
	
}

void Npclv1::Collision(/*Sprite main*/)
{



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
