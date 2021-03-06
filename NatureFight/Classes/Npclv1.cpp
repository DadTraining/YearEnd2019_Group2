﻿#include "Npclv1.h"


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
	this->m_sprite = cocos2d::Sprite::create("Sprites/Man1/NPC(Solo)/PNG/Front/PNG_Sequences/Greeting/0_Citizen_Greeting_000.png");
	this->m_sprite->setScale(1.1);
	this->m_sprite->setAnchorPoint(Vec2(0.5, 0.5));
	this->m_sprite->setPosition(Point(visibleSize.width / 2 +50, visibleSize.height / 2 - 50));
	this->sceneGame->addChild(this->m_sprite,2);

	// create Physics 
	auto a = m_sprite->getContentSize().width;// -500;
	auto b = m_sprite->getContentSize().height;// +1000;
	auto Body = PhysicsBody::createBox(cocos2d::Size(a/2,b/2));
	this->m_sprite->setPhysicsBody(Body);
	Body->setGravityEnable(false);
	Body->setDynamic(false);
	Body->setRotationEnable(false);
	m_sprite->getPhysicsBody()->setCollisionBitmask(Model::BITMASK_NPC);
	m_sprite->getPhysicsBody()->setContactTestBitmask(1);
	
}

void Npclv1::Collision(/*Sprite main*/)
{
	auto mess = Sprite::create("Sprites/Man1/NPC(Solo)/PNG/mess-removebg-preview.png");
	mess->setPosition(this->m_sprite->getPosition());
	mess->setScale(0.3);
	mess->setAnchorPoint(Vec2(0, 0));
	this->sceneGame->addChild(mess);
	//
	auto label1 = Label::createWithSystemFont("xin chao \n toi la Solo \n ", "Arial", 16);
	label1->setAnchorPoint(Vec2(0, 0));
	label1->setPositionX(mess->getPositionX() + 10);
	label1->setPositionY(mess->getPositionY() +10);
	label1->setTextColor(Color4B::BLACK);
	this->sceneGame->addChild(label1);
	//
	auto label2 = Label::createWithSystemFont("Ban hay danh \n tat ca con quai \n con trong map  ", "Arial", 16);
	label2->setAnchorPoint(Vec2(0, 0));
	label2->setPositionX(mess->getPositionX() + 10);
	label2->setPositionY(mess->getPositionY() + 10);
	label2->setTextColor(Color4B::BLACK);
	this->sceneGame->addChild(label2);

	// action hiden mess
	auto fadeIn = FadeIn::create(5.0f);
	auto fadeOut = FadeOut::create(3.0f);
	mess->runAction(FadeOut::create(14.0f));
	auto fadehue = FadeOut::create(3.0f);
	auto remove = RemoveSelf::create(); // clean up memory
	auto doubletrouble1 = Sequence::create(fadehue, remove, nullptr);
	auto doubletrouble = Sequence::create(fadehue, fadeIn, fadehue, remove, nullptr);
	label1->runAction(doubletrouble1);
	label2->setOpacity(0);
	label2->runAction(doubletrouble);

}

void Npclv1::Collision1()
{
	auto mess = Sprite::create("Sprites/Man1/NPC(Solo)/PNG/mess-removebg-preview.png");
	mess->setPosition(this->m_sprite->getPosition());
	mess->setScale(0.3);
	mess->setAnchorPoint(Vec2(0, 0));
	this->sceneGame->addChild(mess);
	//
	auto label1 = Label::createWithSystemFont("xin chao \n toi la Yolo \n   ", "Arial", 16);
	label1->setAnchorPoint(Vec2(0, 0));
	label1->setPositionX(mess->getPositionX() + 10);
	label1->setPositionY(mess->getPositionY() + 10);
	label1->setTextColor(Color4B::BLACK);
	this->sceneGame->addChild(label1);
	//
	auto label2 = Label::createWithSystemFont("Ban hay danh \n 3 con Goblin \n de nhan kiem  ", "Arial", 16);
	label2->setAnchorPoint(Vec2(0, 0));
	label2->setPositionX(mess->getPositionX() + 10);
	label2->setPositionY(mess->getPositionY() + 10);
	label2->setTextColor(Color4B::BLACK);
	this->sceneGame->addChild(label2);

	// action hiden mess
	auto fadeIn = FadeIn::create(5.0f);
	auto fadeOut = FadeOut::create(3.0f);
	mess->runAction(FadeOut::create(14.0f));
	auto fadehue = FadeOut::create(3.0f);
	auto remove = RemoveSelf::create(); // clean up memory
	auto doubletrouble1 = Sequence::create(fadehue,remove, nullptr);
	auto doubletrouble = Sequence::create(fadehue,fadeIn, fadehue, remove , nullptr);
	label1->runAction(doubletrouble1);
	label2->setOpacity(0);
	label2->runAction(doubletrouble);
	
	
}

void Npclv1::CollisionFroz()
{
	auto mess = Sprite::create("Sprites/Man1/NPC(Solo)/PNG/mess-removebg-preview.png");
	mess->setPosition(this->m_sprite->getPosition());
	mess->setScale(0.3);
	mess->setAnchorPoint(Vec2(0, 0));
	this->sceneGame->addChild(mess);
	//
	auto label1 = Label::createWithSystemFont("xin chao \n toi la Froz \n  \n ", "Arial", 16);
	label1->setAnchorPoint(Vec2(0, 0));
	label1->setPositionX(mess->getPositionX() + 10);
	label1->setPositionY(mess->getPositionY() + 10);
	label1->setTextColor(Color4B::BLACK);
	this->sceneGame->addChild(label1);
	//
	auto label2 = Label::createWithSystemFont("Ban hay den \n cho cua Ice \n de biet them  ", "Arial", 16);
	label2->setAnchorPoint(Vec2(0, 0));
	label2->setPositionX(mess->getPositionX() + 10);
	label2->setPositionY(mess->getPositionY() + 10);
	label2->setTextColor(Color4B::BLACK);
	this->sceneGame->addChild(label2);

	// action hiden mess
	auto fadeIn = FadeIn::create(5.0f);
	auto fadeOut = FadeOut::create(3.0f);
	mess->runAction(FadeOut::create(14.0f));
	auto fadehue = FadeOut::create(3.0f);
	auto remove = RemoveSelf::create(); // clean up memory
	auto doubletrouble1 = Sequence::create(fadehue, remove, nullptr);
	auto doubletrouble = Sequence::create(fadehue, fadeIn, fadehue, remove, nullptr);
	label1->runAction(doubletrouble1);
	label2->setOpacity(0);
	label2->runAction(doubletrouble);
}

void Npclv1::CollisionIce()
{
	auto mess = Sprite::create("Sprites/Man1/NPC(Solo)/PNG/mess-removebg-preview.png");
	mess->setPosition(this->m_sprite->getPosition());
	mess->setScale(0.3);
	mess->setAnchorPoint(Vec2(0, 0));
	this->sceneGame->addChild(mess);
	//
	auto label1 = Label::createWithSystemFont("xin chao \n toi la Ice \n \n  ", "Arial", 16);
	label1->setAnchorPoint(Vec2(0, 0));
	label1->setPositionX(mess->getPositionX() + 10);
	label1->setPositionY(mess->getPositionY() + 10);
	label1->setTextColor(Color4B::BLACK);
	this->sceneGame->addChild(label1);
	//
	auto label2 = Label::createWithSystemFont("Ban hay danh \n 10 con goblin  \n de nhan skill ice  ", "Arial", 16);
	label2->setAnchorPoint(Vec2(0, 0));
	label2->setPositionX(mess->getPositionX() + 10);
	label2->setPositionY(mess->getPositionY() + 10);
	label2->setTextColor(Color4B::BLACK);
	this->sceneGame->addChild(label2);

	// action hiden mess
	auto fadeIn = FadeIn::create(5.0f);
	auto fadeOut = FadeOut::create(3.0f);
	mess->runAction(FadeOut::create(14.0f));
	auto fadehue = FadeOut::create(3.0f);
	auto remove = RemoveSelf::create(); // clean up memory
	auto doubletrouble1 = Sequence::create(fadehue, remove, nullptr);
	auto doubletrouble = Sequence::create(fadehue, fadeIn, fadehue, remove, nullptr);
	label1->runAction(doubletrouble1);
	label2->setOpacity(0);
	label2->runAction(doubletrouble);
}

void Npclv1::CollisionWilch()
{
	auto mess = Sprite::create("Sprites/Man1/NPC(Solo)/PNG/mess-removebg-preview.png");
	mess->setPosition(this->m_sprite->getPosition());
	mess->setScale(0.3);
	mess->setAnchorPoint(Vec2(0, 0));
	this->sceneGame->addChild(mess);
	//
	auto label1 = Label::createWithSystemFont("xin chao \n toi la Wilch \n \n   ", "Arial", 16);
	label1->setAnchorPoint(Vec2(0, 0));
	label1->setPositionX(mess->getPositionX() + 10);
	label1->setPositionY(mess->getPositionY() + 10);
	label1->setTextColor(Color4B::BLACK);
	this->sceneGame->addChild(label1);
	//
	auto label2 = Label::createWithSystemFont("Den cong de qua\nman", "Arial", 16);
	label2->setAnchorPoint(Vec2(0, 0));
	label2->setPositionX(mess->getPositionX() + 10);
	label2->setPositionY(mess->getPositionY() + 10);
	label2->setTextColor(Color4B::BLACK);
	this->sceneGame->addChild(label2);

	// action hiden mess
	auto fadeIn = FadeIn::create(5.0f);
	auto fadeOut = FadeOut::create(3.0f);
	mess->runAction(FadeOut::create(14.0f));
	auto fadehue = FadeOut::create(3.0f);
	auto remove = RemoveSelf::create(); // clean up memory
	auto doubletrouble1 = Sequence::create(fadehue, remove, nullptr);
	auto doubletrouble = Sequence::create(fadehue, fadeIn, fadehue, remove, nullptr);
	label1->runAction(doubletrouble1);
	label2->setOpacity(0);
	label2->runAction(doubletrouble);
}

void Npclv1::CollisionFireWilth()
{
	auto mess = Sprite::create("Sprites/Man1/NPC(Solo)/PNG/mess-removebg-preview.png");
	mess->setPosition(this->m_sprite->getPosition());
	mess->setScale(0.3);
	mess->setAnchorPoint(Vec2(0, 0));
	this->sceneGame->addChild(mess);
	//
	auto label1 = Label::createWithSystemFont("xin chao \n toi la Fire Wilth \n \n   ", "Arial", 16);
	label1->setAnchorPoint(Vec2(0, 0));
	label1->setPositionX(mess->getPositionX() + 10);
	label1->setPositionY(mess->getPositionY() + 10);
	label1->setTextColor(Color4B::BLACK);
	this->sceneGame->addChild(label1);
	//
	auto label2 = Label::createWithSystemFont("ban hay danh  \n 6 con quai ", "Arial", 16);
	label2->setAnchorPoint(Vec2(0, 0));
	label2->setPositionX(mess->getPositionX() + 10);
	label2->setPositionY(mess->getPositionY() + 10);
	label2->setTextColor(Color4B::BLACK);
	this->sceneGame->addChild(label2);

	// action hiden mess
	auto fadeIn = FadeIn::create(5.0f);
	auto fadeOut = FadeOut::create(3.0f);
	mess->runAction(FadeOut::create(14.0f));
	auto fadehue = FadeOut::create(3.0f);
	auto remove = RemoveSelf::create(); // clean up memory
	auto doubletrouble1 = Sequence::create(fadehue, remove, nullptr);
	auto doubletrouble = Sequence::create(fadehue, fadeIn, fadehue, remove, nullptr);
	label1->runAction(doubletrouble1);
	label2->setOpacity(0);
	label2->runAction(doubletrouble);
}

void Npclv1::CollisionJoe()
{
	auto mess = Sprite::create("Sprites/Man1/NPC(Solo)/PNG/mess-removebg-preview.png");
	mess->setPosition(this->m_sprite->getPosition());
	mess->setScale(0.3);
	mess->setAnchorPoint(Vec2(0, 0));
	this->sceneGame->addChild(mess);
	//
	auto label1 = Label::createWithSystemFont("xin chao \n toi la Joe \n \n   ", "Arial", 16);
	label1->setAnchorPoint(Vec2(0, 0));
	label1->setPositionX(mess->getPositionX() + 10);
	label1->setPositionY(mess->getPositionY() + 10);
	label1->setTextColor(Color4B::BLACK);
	this->sceneGame->addChild(label1);
	//
	auto label2 = Label::createWithSystemFont("Ban hay danh bai \n 6 con quai \n co trong map ", "Arial", 16);
	label2->setAnchorPoint(Vec2(0, 0));
	label2->setPositionX(mess->getPositionX() + 10);
	label2->setPositionY(mess->getPositionY() + 10);
	label2->setTextColor(Color4B::BLACK);
	this->sceneGame->addChild(label2);

	// action hiden mess
	auto fadeIn = FadeIn::create(5.0f);
	auto fadeOut = FadeOut::create(3.0f);
	mess->runAction(FadeOut::create(14.0f));
	auto fadehue = FadeOut::create(3.0f);
	auto remove = RemoveSelf::create(); // clean up memory
	auto doubletrouble1 = Sequence::create(fadehue, remove, nullptr);
	auto doubletrouble = Sequence::create(fadehue, fadeIn, fadehue, remove, nullptr);
	label1->runAction(doubletrouble1);
	label2->setOpacity(0);
	label2->runAction(doubletrouble);
}

cocos2d::RepeatForever * Npclv1::Hello()
{
	auto spriteCache = SpriteFrameCache::getInstance();
	spriteCache->addSpriteFramesWithFile("Sprites/Man1/NPC(Solo)/PNG/Front/PNG_Sequences/Greeting/Greeting.plist");
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
	spriteCache->addSpriteFramesWithFile("Sprites/Man1/NPC(Solo)/PNG/Front/PNG_Sequences/Communication/Communication.plist");
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

cocos2d::RepeatForever * Npclv1::CommunicationNPCYolo()
{
	auto spriteCache = SpriteFrameCache::getInstance();
	spriteCache->addSpriteFramesWithFile("Sprites/Man1/NPC(Yolo)/PNG/PNG_Sequences/Communication/Communication.plist");
	cocos2d::Vector<cocos2d::SpriteFrame*> exFrames;
	std::string name;
	for (int i = 0; i < 30; i++) {
		if (i<10)
		{

			name = "0_Blacksmith_Communication_00" + std::to_string(i) + ".png";
		}
		else {
			name = "0_Blacksmith_Communication_0" + std::to_string(i) + ".png";
		}

		exFrames.pushBack(spriteCache->getSpriteFrameByName(name));
	}
	auto animation = cocos2d::Animation::createWithSpriteFrames(exFrames, 0.05f);
	auto animate = cocos2d::Animate::create(animation);
	cocos2d::RepeatForever* repeat = cocos2d::RepeatForever::create(animate);

	return repeat;
}

cocos2d::RepeatForever * Npclv1::CommunicationNPCFroz()
{
	auto spriteCache = SpriteFrameCache::getInstance();
	spriteCache->addSpriteFramesWithFile("Sprites/Man2/NPC(Froz)/PNG/PNG_Sequences/Communication/Communication.plist");
	cocos2d::Vector<cocos2d::SpriteFrame*> exFrames;
	std::string name;
	for (int i = 0; i < 30; i++) {
		if (i<10)
		{

			name = "0_Blacksmith_Communication_00" + std::to_string(i) + ".png";
		}
		else {
			name = "0_Blacksmith_Communication_0" + std::to_string(i) + ".png";
		}

		exFrames.pushBack(spriteCache->getSpriteFrameByName(name));
	}
	auto animation = cocos2d::Animation::createWithSpriteFrames(exFrames, 0.05f);
	auto animate = cocos2d::Animate::create(animation);
	cocos2d::RepeatForever* repeat = cocos2d::RepeatForever::create(animate);

	return repeat;
}

cocos2d::RepeatForever * Npclv1::CommunicationNPCIce()
{
	auto spriteCache = SpriteFrameCache::getInstance();
	spriteCache->addSpriteFramesWithFile("Sprites/Man2/NPC(Ice)/PNG/PNG_Sequences/Communication/Communication.plist");
	cocos2d::Vector<cocos2d::SpriteFrame*> exFrames;
	std::string name;
	for (int i = 0; i < 30; i++) {
		if (i<10)
		{

			name = "0_Hunter_Communication_00" + std::to_string(i) + ".png";
		}
		else {
			name = "0_Hunter_Communication_0" + std::to_string(i) + ".png";
		}

		exFrames.pushBack(spriteCache->getSpriteFrameByName(name));
	}
	auto animation = cocos2d::Animation::createWithSpriteFrames(exFrames, 0.05f);
	auto animate = cocos2d::Animate::create(animation);
	cocos2d::RepeatForever* repeat = cocos2d::RepeatForever::create(animate);

	return repeat;
}

cocos2d::RepeatForever * Npclv1::CommunicationNPCWilch()
{
	auto spriteCache = SpriteFrameCache::getInstance();
	spriteCache->addSpriteFramesWithFile("Sprites/Man2/NPC(Wilch)/PNG/PNG Sequences/Communication/Communication.plist");
	cocos2d::Vector<cocos2d::SpriteFrame*> exFrames;
	std::string name;
	for (int i = 0; i < 30; i++) {
		if (i<10)
		{

			name = "0_Herbalist_Communication_00" + std::to_string(i) + ".png";
		}
		else {
			name = "0_Herbalist_Communication_0" + std::to_string(i) + ".png";
		}

		exFrames.pushBack(spriteCache->getSpriteFrameByName(name));
	}
	auto animation = cocos2d::Animation::createWithSpriteFrames(exFrames, 0.05f);
	auto animate = cocos2d::Animate::create(animation);
	cocos2d::RepeatForever* repeat = cocos2d::RepeatForever::create(animate);

	return repeat;
}

cocos2d::RepeatForever * Npclv1::CommunicationNPCFireWilth()
{
	auto spriteCache = SpriteFrameCache::getInstance();
	spriteCache->addSpriteFramesWithFile("Sprites/Man3/NPC(FireWilth)/PNG/Front/PNG_Sequences/Communication/Communication.plist");
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

cocos2d::RepeatForever * Npclv1::CommunicationNPCJoe()
{
	auto spriteCache = SpriteFrameCache::getInstance();
	spriteCache->addSpriteFramesWithFile("Sprites/Man3/NPC(Joe)/PNG/PNG_Sequences/Communication/Communication.plist");
	cocos2d::Vector<cocos2d::SpriteFrame*> exFrames;
	std::string name;
	for (int i = 0; i < 30; i++) {
		if (i<10)
		{

			name = "0_Warlord_Communication_00" + std::to_string(i) + ".png";
		}
		else {
			name = "0_Warlord_Communication_0" + std::to_string(i) + ".png";
		}

		exFrames.pushBack(spriteCache->getSpriteFrameByName(name));
	}
	auto animation = cocos2d::Animation::createWithSpriteFrames(exFrames, 0.05f);
	auto animate = cocos2d::Animate::create(animation);
	cocos2d::RepeatForever* repeat = cocos2d::RepeatForever::create(animate);

	return repeat;
}
