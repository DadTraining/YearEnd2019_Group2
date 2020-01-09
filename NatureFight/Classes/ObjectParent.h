#ifndef  _OBJECT_H_
#define  _OBJECT_H_
#include "cocos2d.h"
#include <ResourceManager.h>
#define M_PI 3.14159265358979323846 
USING_NS_CC;
class ObjectParent
{
public:
	cocos2d::Sprite* m_sprite; // image Object
public:
	ObjectParent();
	~ObjectParent();
	virtual void Init() = 0; //	handles all game objects logic
	virtual void Update(float deltaTime) = 0; // setup initial values for object
	cocos2d::RepeatForever* AnimationObjectRepeat(int id, std::string name, float speed);
	cocos2d::Animate* AnimationObjectOnce(int id, std::string name, float speed);

	virtual cocos2d::RepeatForever* MovingRight() = 0;
	virtual cocos2d::Animate* AttackRight() = 0;
	virtual cocos2d::RepeatForever* IdleRight() = 0;
	virtual cocos2d::Animate* AttackRightAngry() = 0;
	virtual cocos2d::Animate* HurtRight() = 0;
	virtual cocos2d::RepeatForever* DieRight() = 0;

	virtual cocos2d::RepeatForever* MovingUp() = 0;
	virtual cocos2d::Animate* AttackUp() = 0;
	virtual cocos2d::RepeatForever* IdleUp() = 0;
	virtual cocos2d::Animate* AttackUpAngry() = 0;
	virtual cocos2d::Animate* HurtUp() = 0;
	virtual cocos2d::RepeatForever* DieUp() = 0;

	virtual cocos2d::RepeatForever* MovingDown() = 0;
	virtual cocos2d::Animate* AttackDown() = 0;
	virtual cocos2d::RepeatForever* IdleDown() = 0;
	virtual cocos2d::Animate* AttackDownAngry() = 0;
	virtual cocos2d::Animate* HurtDown() = 0;
	virtual cocos2d::RepeatForever* DieDown() = 0;
};
#endif // _OBJECT_H_

