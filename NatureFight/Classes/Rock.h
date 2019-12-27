#pragma once
#include "Object.h"
class Rock :
	public ::Object
{
private:
	cocos2d::Scene* gameScene;
public:
	Rock(cocos2d::Scene* scene);
	~Rock();
	void Init();
	void Update(float deltaTime);
};