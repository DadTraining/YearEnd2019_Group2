#pragma once
#ifndef __HERO_SCENE_H__
#define __HERO_SCENE_H__
#include "ObjectParent.h"
#include <list>
#include <vector> 
#include "cocos2d.h"
#include <Player.h>
USING_NS_CC;
class AiLv1 :
	public ObjectParent
{
public: 
	PhysicsBody* physicsBodyChar;
	bool faceRight;
	int health = 100;
public:
	AiLv1(cocos2d::Scene* scene);
	void Update(float deltaTime);
	void Init();
	void Collision(Player* player,float deltaTime);
	bool StartAttack(int);
	float Distance(Vec2 A, Vec2 C);
	void AiLv1::SetFace();
	cocos2d::RepeatForever* MovingRight();
	cocos2d::Animate* AttackRight();
	cocos2d::RepeatForever* IdleRight();
	cocos2d::Animate* AttackRightAngry();
	cocos2d::Animate* HurtRight();
	cocos2d::RepeatForever* DieRight();
	cocos2d::RepeatForever* AiLv1::AttackAi();
	cocos2d::RepeatForever* MovingUp();
	cocos2d::Animate* AttackUp();
	cocos2d::RepeatForever* IdleUp();
	cocos2d::Animate* AttackUpAngry();
	cocos2d::Animate* HurtUp();
	cocos2d::RepeatForever* DieUp();

	cocos2d::RepeatForever* MovingDown();
	cocos2d::Animate* AttackDown();
	cocos2d::RepeatForever* IdleDown();
	cocos2d::Animate* AttackDownAngry();
	cocos2d::Animate* HurtDown();
	cocos2d::RepeatForever* DieDown();
	~AiLv1();
private:
	cocos2d::Scene* sceneGame;
};
#endif // __HERO_SCENE_H__