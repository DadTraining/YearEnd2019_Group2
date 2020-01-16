#ifndef __MAPBOSSEND_SCENE_H__
#define __MAPBOSSEND_SCENE_H__

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
#include<BossLv1.h>
#include <BossEnd.h>
USING_NS_CC;
#define ATTACK 0
#define RUN 1
#define playertag 1000
#define NpcSolotag 11
#define NpcYolotag 12
#define AILV1 13
#define ATTACKTAG 8
class MapBossEndScene : public cocos2d::Scene
{
public:
	Player* mainPlayer;
	Npclv1* npcsolo, *npcYolo;
	TMXTiledMap* map,*MapBackGround;
	TMXLayer* mPhysicsLayer, *mPhysicsLayer1, *mPhysicsLayer2;
	MenuLayer* menuLayer;
	TMXObjectGroup* mObjectGroup , *mObjectGroup1;
	std::vector<AiLv1*> ai;

	ui::Button* ButtonAttack;
	SneakyJoystick* leftJoystick;

	BossLv1* bosslv1;
	int countCreepDie=0;
	BossEnd* bossEnd;
public:
    static cocos2d::Scene* createScene();
	void addMap();
    virtual bool init();
    void update(float deltaTime);
    CREATE_FUNC(MapBossEndScene);
	virtual bool onTouchBegan(Touch*, Event*);
	virtual bool onTouchEnded(Touch*, Event*);
	virtual bool onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	float Distance(Vec2 A, Vec2 C);
	void createPhysicMap();
	bool onContactBegin(const PhysicsContact& contact);
	bool onContactPreSolve(const PhysicsContact& contact);
	bool onContactSeparate(const PhysicsContact& contact);
};
#endif // __MAPBOSSMAN2_SCENE_H__
