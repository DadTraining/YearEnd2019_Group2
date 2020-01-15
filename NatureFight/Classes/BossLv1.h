#pragma once
#ifndef _BOSS_SCENE_H_
#define _BOSS_SCENE_H_
#include "ObjectParent.h"
#include <list>
#include <vector> 
#include "cocos2d.h"
#include "Model.h"
#include <Player.h>
#include <Boom.h>
#include <GameSetting.h>
#include <SimpleAudioEngine.h>
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
USING_NS_CC;
class BossLv1 :
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
	Node* edgeNode;
	int m_CurrentFace;
	int m_CurrentState;
	float AttackSpeed;
	Boom* mBooms[MAX_BULLET];
	bool stateHeal;
	bool stateAngry;
public:
	BossLv1(cocos2d::Scene* scene);
	void Update(float deltaTime);
	void Init();
	void Collision(Player* player, float deltaTime);
	float Distance(Vec2 A, Vec2 C);
	bool onContactBegin(const PhysicsContact& contact);
	void bulletHasCollision(int bulletIndex);
	void updateBullets(float deltaTime);
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
	void setSkillHeal(bool sHeal);
	float setHealth();//suong

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

	cocos2d::Sprite* loadingbar;
	cocos2d::ui::LoadingBar* load;



	cocos2d::ParticleSystemQuad* ParticleHeal(std::string name);
	~BossLv1();
private:
	cocos2d::Scene* sceneGame;
	Player* player;
};

#endif // _BOSS_SCENE_H_