#pragma once
#include "Object.h"
class Bullet :
	public ::Object
{
public:
	cocos2d::Scene* sceneGame;
public:
	Bullet(cocos2d::Scene* scene);
	~Bullet();
	void Init();
	void Update(float deltaTime);
	
};

