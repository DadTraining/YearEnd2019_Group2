#pragma once
#ifndef _BOSS_SCENE_H_
#define _BOSS_SCENE_H_
#include "ObjectParent.h"
#include <list>
#include <vector> 
#include "cocos2d.h"
#include "Model.h"
#include <Player.h>
#include <Bullet.h>
#define CREEPTAG 11
#define CREEPATTACK 111
#define CREEPTAG 11
#define CREEPATTACK 111
#define AILV1 13
#define Boss3 50
USING_NS_CC;
class BossLv3 :
	public ObjectParent
{
public:
	static const int GOBIN_TAG = 1;
	static const int ACTION_HURT_ICE = 11;
	static const int ACTION_HURT_FIRE = 12;
private:
	int tagAI;

public:
	PhysicsBody* physicsBodyChar;
	int m_health = 100;
	int m_CurrentFace;
	int m_CurrentState;
	float AttackSpeed;
	int radius;
	bool stateAttackIce;
	int countSkill;
	Bullet* mBullet;

public:
	BossLv3(cocos2d::Scene* scene);
	void Update(float deltaTime);
	void Init();
	void setStateAttackIce(bool state);
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
	cocos2d::ParticleSystemQuad* ParticleIce(std::string name);
	~BossLv3();
private:
	cocos2d::Scene* sceneGame;
	Player* player;
};
#endif // _HERO_SCENE_H_