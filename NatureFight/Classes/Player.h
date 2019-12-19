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
	cocos2d::Animate* AttackRight();
	cocos2d::RepeatForever* IdleRight();
	cocos2d::RepeatForever* AttackRightAngry();
	~Player();
private:
	cocos2d::Scene* sceneGame;

};