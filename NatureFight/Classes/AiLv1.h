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
	cocos2d::RepeatForever* MovingRight();
	cocos2d::Animate* AttackRight();
	cocos2d::RepeatForever* IdleRight();
	cocos2d::RepeatForever* AttackRightAngry();
	cocos2d::Animate* HurtRight();
	cocos2d::RepeatForever* DieRight();
	~AiLv1();
private:
	cocos2d::Scene* sceneGame;
};
#endif // __HERO_SCENE_H__