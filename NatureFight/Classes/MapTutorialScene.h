#ifndef __MAPTUTORIAL_SCENE_H__
#define __MAPTUTORIAL_SCENE_H__

#include "cocos2d.h"
#include<ObjectParent.h>
#include <AiLv1.h>
#include <iostream>
#include <Player.h>
#include <ui/CocosGUI.h>
#include <ResourceManager.h>
#include <SneakyJoystickSkinnedBase.h>
USING_NS_CC;
class MapTutorialScene : public cocos2d::Scene
{
public:
	Player* mainPlayer;
	AiLv1* ailv1;
	ui::Button* ButtonAttack;
	SneakyJoystick* leftJoystick;
	SneakyJoystickSkinnedBase* joystickBase;
public:
    static cocos2d::Scene* createScene();
	void addMap();
    virtual bool init();
    void update(FLOAT deltaTime);
    CREATE_FUNC(MapTutorialScene);
	virtual bool onTouchBegan(Touch*, Event*);
	virtual bool onTouchEnded(Touch*, Event*);
	virtual bool onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	float Distance(Vec2 A, Vec2 C);
	void MovePlayer();
};
#endif // __MAPTUTORIAL_SCENE_H__
