#pragma once
#include "G:\gameLoft\Cocos2dX-GameLoft\SpaceGame\cocos2d\cocos\2d\CCScene.h"
#include "cocos2d.h"
#include <iostream>
USING_NS_CC;
class MainMenuScene :
	public cocos2d::Scene
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(MainMenuScene);
};

