#pragma once
#include <cocos2d.h>

class Object
{
public:
	cocos2d::Sprite* m_sprite;
public:
	Object();
	~Object();
	virtual void Init()=0;
	virtual void Update(float deltaTime) = 0;
	cocos2d::Sprite* DuplicateSprite(cocos2d::Sprite* sprite);
};

