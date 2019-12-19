#pragma once
#include "cocos2d.h"
#include "ObjectParent.h"
#include <vector> 
class Npclv1 :
	public ObjectParent
{

public:
	Npclv1(cocos2d::Scene* scene);
	void Update(float deltaTime);
	void Init();
	void Collision(/*Sprite main*/);
	cocos2d::RepeatForever* Hello();
	cocos2d::RepeatForever* Communication();
	~Npclv1();
private:
	float count=0;
	cocos2d::Scene* sceneGame;
};