#pragma once
#ifndef  _NPC_H_
#define  _NPC_H_
#include"cocos2d.h"
#include"Model.h"
USING_NS_CC;
class Npclv1
{
public:
	cocos2d::Sprite* m_sprite;
	Npclv1(cocos2d::Scene* scene);
	void Update(float deltaTime);
	void Init();
	void Collision(/*Sprite main*/);
	void Collision1(/*Sprite main*/);
	void CollisionFroz();
	void CollisionIce();
	void CollisionWilch();
	cocos2d::RepeatForever* Hello();
	cocos2d::RepeatForever* Communication();
	cocos2d::RepeatForever* CommunicationNPCYolo();
	cocos2d::RepeatForever* CommunicationNPCFroz();
	cocos2d::RepeatForever* CommunicationNPCIce();
	cocos2d::RepeatForever* CommunicationNPCWilch();

	~Npclv1();
private:
	float count=0;
	cocos2d::Scene* sceneGame;
};
#endif