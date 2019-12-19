#ifndef __MAPTUTORIAL_SCENE_H__
#define __MAPTUTORIAL_SCENE_H__
#include "cocos2d.h"
#include<ObjectParent.h>
#include <proj.win32\AiLv1.h>
#include <iostream>
USING_NS_CC;
class MapTutorialScene : public cocos2d::Scene
{

public:
	void autoMove(float dt);
    static cocos2d::Scene* createScene();
    virtual bool init();
    void update(FLOAT deltaTime);
    CREATE_FUNC(MapTutorialScene);
	void addMap();
	AiLv1* aiLv1;
};
#endif // __MAPTUTORIAL_SCENE_H__
