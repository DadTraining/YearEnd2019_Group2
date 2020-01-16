#ifndef _MODEL_H_
#define _MODEL_H_

#include "cocos2d.h"
USING_NS_CC;
class Model
{
public:
	static const int BITMASK_WORLD = 100;
	static const int BITMASK_PLAYER = BITMASK_WORLD + 1;
	static const int BITMASK_GROUND = BITMASK_PLAYER + 1;
	static const int BITMASK_MONSTER = BITMASK_GROUND + 1;
	static const int BITMASK_NPC = BITMASK_MONSTER + 1;
	static const int MODLE_TYPE_MAIN_CHARACTER = 1;
	static const int MODLE_TYPE_MONSTER = 2;
	static const int BITMASK_MONSTER_BULLET = BITMASK_NPC + 1;
	static const int BITMASK_MONSTER_BULLET_FIREBALL = BITMASK_MONSTER_BULLET + 1;
	static const int BITMASK_MONSTER_TONATO = BITMASK_MONSTER_BULLET_FIREBALL + 1;
protected:
	cocos2d::Sprite* mSprite;
	cocos2d::PhysicsBody* mPhysicsBody;
	bool mIsALive;
	bool mIsRunLeftToRight; //use to flip sprite: use one sprite to run left or right

public:
	Model();
	~Model();

	bool isMoveRight();

	void setAlive(bool alive);

	bool isAlive();

	void setPosition(cocos2d::Vec2 pos);

	void setScale(float scale);

	void setIndex(int index);

	int getIndex();

	cocos2d::PhysicsBody* getPhysicBody();
	cocos2d::Vec2 getPosition();

	cocos2d::Size getContentSize();	
};
#endif