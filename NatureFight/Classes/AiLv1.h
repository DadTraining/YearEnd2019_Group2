#pragma once
#ifndef _HERO_SCENE_H_
#define _HERO_SCENE_H_
#include "ObjectParent.h"
#include <list>
#include <vector> 
#include "cocos2d.h"
#include <Player.h>
#define CREEPTAG 11
#define CREEPATTACK 111
USING_NS_CC;
class AiLv1 :
	public ObjectParent
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
	PhysicsBody* physicsBodyChar;
	int m_health = 100;
	Node* edgeNode;
	int m_CurrentFace;
	int m_CurrentState;
	float AttackSpeed;
	Player* player;
public:
	AiLv1(cocos2d::Scene* scene);
	void Update(float deltaTime);
	void Init();
	void Collision(Player* player, float deltaTime);
	float Distance(Vec2 A, Vec2 C);
	bool onContactBegin(const PhysicsContact& contact);

	void SetFace();
	void SetState(int);
	void SetIdle(int);
	void SetDie(int);
	void SetAttack(int state);
	void SetHurt(int state);
	void SetMove(int state);

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
	~AiLv1();
private:
	cocos2d::Scene* sceneGame;
};
#endif // _HERO_SCENE_H_