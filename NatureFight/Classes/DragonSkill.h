#pragma once
#include "cocos2d.h"
#include<Model.h>
#include<ResourceManager.h>
class DragonSkill
{
private:
	cocos2d::Scene* sceneGame;
public:
	PhysicsBody* physicsBody;
public:
	Sprite* m_dragon;
	ParticleSystemQuad* particleMove;

	float DragonAttacked = 0;
	float countTimeExis = 0;

	bool faceRight = true;
public:
	void Update(float deltaTime);
	void Init();
	DragonSkill(Scene*);

	float Distance(Vec2, Vec2);
	void SetFace(Vec2);
	void AnimationDragon();
};