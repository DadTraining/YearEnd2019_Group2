#pragma once
#include "cocos2d.h"
#include "ObjectParent.h"
#include <vector> 
#include<Model.h>
#include<DragonSkill.h>
#define ATTACK 0
#define RUN 1
#define playertag 1000

#define NORMALSKILL 8
#define ATTACK_FIRE 9
#define ATTACK_ICE 10
#define ATTACK_ICE 10
#define ATTACK_FIRE_ICE 11

#define NpcSolotag 11
#define NpcYolotag 12
class Player :
	public ObjectParent
{
public:
	static const int SKILL_DEFAULT = -1;
	static const int SKILL_FIRE = 1;
	static const int SKILL_FIRE_2 = 2;
	static const int SKILL_ICE = 3;
	static const int SKILL_ICE_2 = 4;
	static const int SKILL_FIRE_ICE = 5;

	static const int STONE_CBN = 2;
	static const int STONE_FIRE = 3;
	static const int STONE_ICE = 5;
	static const int STONE_FIRE_ICE = STONE_FIRE + STONE_ICE;

public:
	PhysicsBody* physicsBody;
	DragonSkill* dragon;
	Node* edgeNode;
	int m_CurrentSkill;
	int Armor;
	static int CountCreep;
	static int Level;
	static int Exp;
	static int MaxExp;

	static 	bool haveSword;
	static bool haveSwordFire;
	static bool haveSwordIce;

	static 	bool haveFireStone;
	static bool haveIceStone;

	static bool haveFirePet;
	static bool haveIceShield;

public:
	cocos2d::Scene* sceneGame;
	static int m_CurrentStone;
	ParticleSystemQuad* particleMove;

	bool onShield = false;
	bool onDragon = false;
	bool onDragonAttack = false;
	bool onAngry = false;

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
	void SetSkillFireIce();
	void SetSkillDefault();

	void UseStone(int);
	~Player();

	cocos2d::RepeatForever* MovingRight();
	cocos2d::Animate* AttackRight();
	cocos2d::RepeatForever* IdleRight();
	cocos2d::Animate* AttackRightAngry();
	cocos2d::Animate* HurtRight();
	cocos2d::RepeatForever* DieRight1();
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

	cocos2d::ParticleSystemQuad* ParticleAttack(std::string name);
	cocos2d::ParticleSystemQuad* particlePow;
	void SetParticleMove();
	void ParticlePow();

	void CheckShield(float);
	void CheckDragon(float);
	void CheckAttackAndSkill(float);
};