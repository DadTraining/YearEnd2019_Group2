#ifndef __MAPBOSSMAN2_SCENE_H__
#define __MAPBOSSMAN2_SCENE_H__

#include "cocos2d.h"
#include<ObjectParent.h>
#include <iostream>
#include <Player.h>
#include <ui/CocosGUI.h>
#include <ResourceManager.h>
#include <SneakyJoystickSkinnedBase.h>
#include <MenuLayer.h>
#include<BossLv1.h>
#include<Map_3.h>
USING_NS_CC;
#define ATTACK 0
#define RUN 1
#define playertag 1000
#define AILV1 13
#define ATTACKTAG 8
#define GATEtag 400
class MapBossMan2Scene : public cocos2d::Scene
{
private: bool gate, alreadyItem;
public:
	Player* mainPlayer;
	TMXTiledMap* map,*MapBackGround;
	TMXLayer* mPhysicsLayer, *mPhysicsLayer1, *mPhysicsLayer2;
	MenuLayer* menuLayer;
	TMXObjectGroup* mObjectGroup , *mObjectGroup1;

	ui::Button* ButtonAttack;
	SneakyJoystick* leftJoystick;

	BossLv1* bosslv1;
	int countCreepDie=0;
public:
    static cocos2d::Scene* createScene();
	void addMap();
    virtual bool init();
    void update(float deltaTime);
    CREATE_FUNC(MapBossMan2Scene);
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
};
#endif // __MAPBOSSMAN2_SCENE_H__
