#pragma once
#include "cocos2d.h"
#include "ObjectParent.h"
#include <vector> 
class Npclv1
{
public:
	cocos2d::Sprite* m_sprite;
	Npclv1(cocos2d::Scene* scene);
	void Update(float deltaTime);
	void Init();
	void Collision(/*Sprite main*/);
	void Collision1(/*Sprite main*/);
	cocos2d::RepeatForever* Hello();
	cocos2d::RepeatForever* Communication();
	cocos2d::RepeatForever* CommunicationNPCYolo();
	~Npclv1();
private:
	float count=0;
	cocos2d::Scene* sceneGame;
};