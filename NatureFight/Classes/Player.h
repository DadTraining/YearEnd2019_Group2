#pragma once
#include "cocos2d.h"
#include "ObjectParent.h"
#include <vector> 
class Player :
	public ObjectParent
{

public:
	Player(cocos2d::Scene* scene);
	void Update(FLOAT deltaTime);
	void Init();
	void Collision();
	cocos2d::RepeatForever* Moving();
	cocos2d::RepeatForever* Attack();
	~Player();
private:
	cocos2d::Scene* sceneGame;

};