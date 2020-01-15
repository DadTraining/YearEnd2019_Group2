#pragma once
#ifndef _RANGE_SCENE_H_
#define _RANGE_SCENE_H_
#include "ObjectParent.h"
#include <list>
#include <vector> 
#include "cocos2d.h"
#include "Model.h"
#include <Player.h>
#include "Bullet.h"
#include <Boom.h>
#define CREEPTAG 11
#define CREEPATTACK 111
#define CREEPTAG 11
#define BOSSATTACK 112
#define SKILLICE 1
#define SKILLFIRE 2
#define NORMALSKILL 0
#define AILV1 13
#define BOSSLV1 14
#define ATTACKTAG 8
#define AIRANGE 200
USING_NS_CC;
class AiRange :
	public ObjectParent
{
public:
	static const int GOBIN_TAG = 1;
	static const int ACTION_HURT_ICE = 11;
	static const int ACTION_HURT_FIRE = 12;
	static const int MAX_BULLET = 10;
private:
	int tagAI;

public:
	PhysicsBody* physicsBodyChar;
	int maxHealth = 100;
	int m_health = 100;
	int m_CurrentFace;
	int m_CurrentState;
	float AttackSpeed;
	Bullet* mBullet;
	bool mIsMcLeft;
public:
	AiRange(cocos2d::Scene* scene);
	void Update(float deltaTime);
	void Init();
	void Collision(Player* player, float deltaTime);
	float Distance(Vec2 A, Vec2 C);
	bool onContactBegin(const PhysicsContact& contact);
	void bulletHasCollision();
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

	cocos2d::ParticleSystemQuad* ParticleHeal(std::string name);
	~AiRange();
private:
	cocos2d::Scene* sceneGame;
	Player* player;


	cocos2d::ui::LoadingBar* loadingbar;
	cocos2d::ui::LoadingBar* load;
};

#endif // _BOSS_SCENE_H_