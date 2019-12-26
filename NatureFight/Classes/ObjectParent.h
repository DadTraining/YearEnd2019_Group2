#ifndef  _OBJECT_H_
#define  _OBJECT_H_
#include "cocos2d.h"
#include <ResourceManager.h>

USING_NS_CC;
class ObjectParent
{
public:
	cocos2d::Sprite* m_sprite; // image Object
public:
	ObjectParent();
	~ObjectParent();
	virtual void Init() = 0; //	handles all game objects logic
	virtual void Update(FLOAT deltaTime) = 0; // setup initial values for object
	cocos2d::RepeatForever* AnimationObjectRepeat(int id, std::string name);
	cocos2d::Animate* AnimationObjectOnce(int id, std::string name);

	virtual cocos2d::RepeatForever* MovingRight()=0;
	virtual cocos2d::Animate* AttackRight()=0;
	virtual cocos2d::RepeatForever* IdleRight()=0;
	virtual cocos2d::RepeatForever* AttackRightAngry()=0;
	virtual cocos2d::Animate* HurtRight()=0;
	virtual cocos2d::RepeatForever* DieRight()=0;
};
#endif // _OBJECT_H_

