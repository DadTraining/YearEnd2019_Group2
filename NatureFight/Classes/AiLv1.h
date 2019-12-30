#pragma once
#ifndef __HERO_SCENE_H__
#define __HERO_SCENE_H__
#include "ObjectParent.h"
#include <list>
#include <vector> 
#include "cocos2d.h"
class AiLv1 :
	public ObjectParent
{
public: 
	int health = 100;
public:
	AiLv1(cocos2d::Scene* scene);
	void Update(float deltaTime);
	void Init();
	void Collision();
	virtual bool StartAttack(int) = 0;

	virtual cocos2d::RepeatForever* MovingRight() = 0;
	virtual cocos2d::Animate* AttackRight() = 0;
	virtual cocos2d::RepeatForever* IdleRight() = 0;
	virtual cocos2d::Animate* AttackRightAngry() = 0;
	virtual cocos2d::Animate* HurtRight() = 0;
	virtual cocos2d::RepeatForever* DieRight() = 0;

	virtual cocos2d::RepeatForever* MovingUp() = 0;
	virtual cocos2d::Animate* AttackUp() = 0;
	virtual cocos2d::RepeatForever* IdleUp() = 0;
	virtual cocos2d::Animate* AttackUpAngry() = 0;
	virtual cocos2d::Animate* HurtUp() = 0;
	virtual cocos2d::RepeatForever* DieUp() = 0;

	virtual cocos2d::RepeatForever* MovingDown() = 0;
	virtual cocos2d::Animate* AttackDown() = 0;
	virtual cocos2d::RepeatForever* IdleDown() = 0;
	virtual cocos2d::Animate* AttackDownAngry() = 0;
	virtual cocos2d::Animate* HurtDown() = 0;
	virtual cocos2d::RepeatForever* DieDown() = 0;
	~AiLv1();
private:
	cocos2d::Scene* sceneGame;
};
#endif // __HERO_SCENE_H__