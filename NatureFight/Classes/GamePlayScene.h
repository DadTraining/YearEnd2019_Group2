#pragma once
#include "G:\gameLoft\Cocos2dX-GameLoft\SpaceGame\cocos2d\cocos\2d\CCScene.h"
#include "Rock.h"
#include "SpaceShooter.h"
#include "cocos2d.h"
#include <iostream>
USING_NS_CC;
class GamePlayScene :
	public cocos2d::Scene
{
public:
	std::vector<Rock*> m_rocks;
	SpaceShooter* m_spaceShip;
public:
	static Scene* createScene();
	virtual bool init();
	void update(FLOAT deltaTime);
	void GenerateRock();
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	bool onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, Event* event);
	CREATE_FUNC(GamePlayScene);
	
};

