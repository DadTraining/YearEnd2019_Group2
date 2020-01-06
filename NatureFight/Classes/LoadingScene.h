#ifndef  _LOADING_SCENE_H_
#define  _LOADING_SCENE_H_
#include "cocos2d.h"
#include"ResourceManager.h"
USING_NS_CC;

class LoadingScene : public cocos2d::Scene
{
public:
	float countT = 0;
	static cocos2d::Scene* createScene();
	virtual bool init();
	void update(FLOAT deltaTime);
	CREATE_FUNC(LoadingScene);
};
#endif
