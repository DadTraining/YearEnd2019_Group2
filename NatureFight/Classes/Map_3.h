#ifndef __Map3_SCENE_H__
#define __Map3_SCENE_H__

#include "cocos2d.h"
#include<ObjectParent.h>
#include <iostream>
#include <Player.h>
#include <Npclv1.h>
#include <ui/CocosGUI.h>
#include <ResourceManager.h>
#include <SneakyJoystickSkinnedBase.h>
#include <MenuLayer.h>
#include<AiLv1.h>
#include <BossLv3.h>
#include <AiRange.h>
#include <MapBossMan3Scene.h>
USING_NS_CC;
#define ATTACK 0
#define RUN 1
#define playertag 1000
#define NpcFireWilthtag 511
#define NpcJoetag 512
#define AILV1 13
#define ATTACKTAG 8
#define GATEtag 400
class Map_3 : public cocos2d::Scene
{
public:
	Player* mainPlayer;
	Npclv1* npcFireWilth , *npcJoe;
	TMXTiledMap* map,*MapBackGround;
	TMXLayer* mPhysicsLayer, *mPhysicsLayer1, *mPhysicsLayer2;
	MenuLayer* menuLayer;
	TMXObjectGroup* mObjectGroup , *mObjectGroup1;
	std::vector<AiLv1*> ai;

	ui::Button* ButtonAttack;
	SneakyJoystick* leftJoystick;

	BossLv3* bosslv3;
	int countCreepDie=0;
public:
    static cocos2d::Scene* createScene();
	void addMap();
    virtual bool init();
    void update(float deltaTime);
    CREATE_FUNC(Map_3);
	virtual bool onTouchBegan(Touch*, Event*);
	virtual bool onTouchEnded(Touch*, Event*);
	virtual bool onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	float Distance(Vec2 A, Vec2 C);
	void createPhysicMap();
	bool onContactBegin(const PhysicsContact& contact);
	bool onContactPreSolve(const PhysicsContact& contact);
	bool onContactSeparate(const PhysicsContact& contact);

	void createMoveScene();
	cocos2d::ParticleSystemQuad* Particletele(std::string name);

	void createCreepScene();
	bool isCreepDie();
};
#endif // __Map2_SCENE_H__
