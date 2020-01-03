#pragma once
#include "cocos2d.h"
#include "ObjectParent.h"
#include <vector> 
class Player :
	public ObjectParent
{
public:
	static const int FACE_UP = 0;
	static const int FACE_DOWN = 1;
	static const int FACE_LEFT = 2;
	static const int FACE_RIGHT = 3;

	static const int ACTION_MOVE = 0;
	static const int ACTION_MOVEDOWN = 1;
	static const int ACTION_MOVEUP = 2;
	static const int ACTION_ATTACK = 3;
	static const int ACTION_ATTACKDOWN = 4;
	static const int ACTION_ATTACKUP = 5;
	static const int ACTION_IDLE = 6;
	static const int ACTION_IDLEDOWN = 7;
	static const int ACTION_IDLEUP = 8;
	static const int ACTION_HURT = 9;
	static const int ACTION_HURTUP = 10;
	static const int ACTION_HURTDOWN = 11;

public: 
	PhysicsBody* physicsBody;
	Node* edgeNode;
	static int Level;
	static int Exp;
private:
	int m_CurrentFace;
	int m_CurrentState;
	cocos2d::Scene* sceneGame;
	int m_health = 100;
	int m_dame = 10;
public:
	Player(cocos2d::Scene* scene);
	void Update(float deltaTime);
	void updateLevel();
	void Init();
	void Collision();
	void SetFace();
	void SetAlive();
	void SetState(int);
	void SetIdle(int);
	void SetAttack(int state);
	void SetHurt(int state);
	void SetMove(int state);
	int SetAction();
	~Player();

	bool StartAttack(int);

	cocos2d::RepeatForever* MovingRight();
	cocos2d::Animate* AttackRight();
	cocos2d::RepeatForever* IdleRight();
	cocos2d::Animate* AttackRightAngry();
	cocos2d::Animate* HurtRight();
	cocos2d::RepeatForever* DieRight();

	cocos2d::RepeatForever* MovingUp();
	cocos2d::Animate* AttackUp();
	cocos2d::RepeatForever* IdleUp();
	cocos2d::Animate* AttackUpAngry();
	cocos2d::Animate* HurtUp();
	cocos2d::RepeatForever* DieUp();

	cocos2d::RepeatForever* MovingDown();
	cocos2d::Animate* AttackDown();
	cocos2d::RepeatForever* IdleDown();
	cocos2d::Animate* AttackDownAngry();
	cocos2d::Animate* HurtDown();
	cocos2d::RepeatForever* DieDown();
};