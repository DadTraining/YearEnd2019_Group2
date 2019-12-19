#pragma once
#include "cocos2d.h"
#include "ObjectParent.h"
#include <vector> 
class Player :
	public ObjectParent
{
public: 
	PhysicsBody* physicsBody;
public:
	Player(cocos2d::Scene* scene);
	void Update(FLOAT deltaTime);
	void Init();
	void Collision();
	cocos2d::RepeatForever* MovingRight();
	cocos2d::RepeatForever* AttackRight();
	cocos2d::RepeatForever* IdleRight();
	~Player();
private:
	cocos2d::Scene* sceneGame;

};