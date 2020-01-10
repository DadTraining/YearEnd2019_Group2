#ifndef  _OBJECT_H_
#define  _OBJECT_H_
#include "cocos2d.h"
#include <ResourceManager.h>
#define M_PI 3.14159265358979323846 
USING_NS_CC;
class ObjectParent
{
public:
	static const int FACE_DEFAULT = 0;
	static const int FACE_DOWN = 1;
	static const int FACE_LEFT = 2;
	static const int FACE_RIGHT = 3;
	static const int FACE_UP = 4;

	static const int ACTION_DEFAULT = -1;
	static const int ACTION_MOVE = 0;
	static const int ACTION_MOVEDOWN = 1;
	static const int ACTION_MOVEUP = 2;
	static const int ACTION_ATTACK = 3;
	static const int ACTION_IDLE = 6;
	static const int ACTION_HURT = 9;
	static const int ACTION_DIE = 10;

public:
	cocos2d::Sprite* m_sprite; // image Object
	int m_CurrentFace;
	int m_CurrentState;

	float AttackSpeed;
	float MoveSpeed;
	int m_health;
	int m_dame;
public:
	ObjectParent();
	~ObjectParent();
	virtual void Init() = 0; //	handles all game objects logic
	virtual void Update(float deltaTime) = 0; // setup initial values for object

	virtual void SetFace() = 0;
	virtual void SetState(int) = 0;
	virtual void SetIdle(int) = 0;
	virtual void SetDie(int) = 0;
	virtual void SetAttack(int state) = 0;
	virtual void SetHurt(int state) = 0;
	virtual void SetMove(int state) = 0;

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