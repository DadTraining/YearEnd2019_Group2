#pragma once
#ifndef __HERO_SCENE_H__
#define __HERO_SCENE_H__
#include "ObjectParent.h"
#include <list>
#include <vector> 
class AiLv1 :
	public ObjectParent
{

public:
	AiLv1(cocos2d::Scene* scene);
	void Update(float deltaTime);
	void Init();
	void Collision();
	cocos2d::RepeatForever* Moving();
	cocos2d::RepeatForever* Attack();
	~AiLv1();
private:
	cocos2d::Scene* sceneGame;
	cocos2d::SpriteFrame* spriteFrame;
	cocos2d::SpriteFrameCache* spriteCache;

};
#endif // __HERO_SCENE_H__