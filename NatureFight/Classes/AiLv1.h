#pragma once
#ifndef _HERO_SCENE_H_
#define _HERO_SCENE_H_
#include "ObjectParent.h"
#include <list>
#include <vector> 
#include "cocos2d.h"
#include "Model.h"
#include <Player.h>
#include <ctime>
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
#define CREEPTAG 11
#define CREEPATTACK 111
#define CREEPTAG 11
#define CREEPATTACK 111
#define AILV1 13
#define ATTACKSPEED 1
USING_NS_CC;
class AiLv1 :
	public ObjectParent
{
public:
	static const int GOBIN_TAG = 1;
	static const int ACTION_HURT_ICE = 11;
	static const int ACTION_HURT_FIRE = 12;
private:
	int tagAI;
	float timeAttackAI = 0, timeDieAI = 0, timeColor = 0, timem = 0;
	float speedAtt;
	bool stateIce;
	bool checkAttackAI = false;
public:

	PhysicsBody* physicsBodyChar;
	int m_health = 100;
	Node* edgeNode;
	int m_CurrentFace;
	int m_CurrentState;
	float AttackSpeed;

public:
	void resetStateIce();
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
	void SetHurtAi(int state, int skill);
	void SetMove(int state);
	void SetTagAI(int);
	void setIndex(int index);

	float setHealth();

	cocos2d::RepeatForever* MovingRight();
	cocos2d::Animate* AttackRight();
	cocos2d::RepeatForever* IdleRight();
	cocos2d::Animate* AttackRightAngry();
	cocos2d::Animate* HurtRight();
	cocos2d::Animate* DieRight();

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
	Player* player;

	cocos2d::ui::LoadingBar* loadingbar;
	cocos2d::ui::LoadingBar* load;
};
#endif // _HERO_SCENE_H_