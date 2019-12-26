#pragma once
#include "cocos2d.h"
#include "ObjectParent.h"
#include <vector> 
class Player :
	public ObjectParent
{
public: 
	PhysicsBody* physicsBody;
	static int Level;
	static int Exp;
public:
	Player(cocos2d::Scene* scene);
	void Update(FLOAT deltaTime);
	void Init();
	void Collision();
	cocos2d::RepeatForever* MovingRight();
	cocos2d::Animate* AttackRight();
	cocos2d::RepeatForever* IdleRight();
	cocos2d::RepeatForever* AttackRightAngry();
	cocos2d::Animate* HurtRight();
	cocos2d::RepeatForever* DieRight();
	void updateLevel();
	~Player();
private:
	cocos2d::Scene* sceneGame;
	int health = 100;
	int dame = 10;
};