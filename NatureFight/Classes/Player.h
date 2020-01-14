#pragma once
#include "cocos2d.h"
#include "ObjectParent.h"
#include <vector> 
#include<Model.h>
#define ATTACK 0
#define RUN 1
#define playertag 1000
#define NORMALSKILL 8
#define ATTACK_FIRE 9
#define ATTACK_ICE 10
#define NpcSolotag 11
#define NpcYolotag 12
class Player :
	public ObjectParent
{
public:
	static const int SKILL_DEFAULT = -1;
	static const int SKILL_FIRE = 1;
	static const int SKILL_ICE = 2;

	static const int STONE_CBN = 1;
	static const int STONE_FIRE = 2;

public:
	PhysicsBody* physicsBody;
	Node* edgeNode;
	int m_CurrentSkill;
	int CountCreep=0;

	static int Level;
	static int Exp;
	static int MaxExp;

	bool haveSword;
	bool haveMagicSword;

	bool haveHeatBalanceStone;
	bool haveFireStone;

	bool haveMask;

private:
	cocos2d::Scene* sceneGame;
	static int m_CurrentStone;
public:
	Player(cocos2d::Scene* scene);
	void Update(float deltaTime);
	void updateLevel();
	void Init();
	void Collision();
	void SetFace(Vec2);
	void SetState(int);
	void SetIdle(int);
	void SetDie(int);
	void SetAttack(int state);
	void SetHurt(int state);
	void SetMove(int state);

	void SetSkill();
	void SetSkillFire();
	void SetSkillIce();
	void SetSkillDefault();

	float setHealth();
	float setDame();

	void UseStone(int);
	~Player();

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

	cocos2d::ParticleSystemQuad* ParticleAttack(std::string name);

};