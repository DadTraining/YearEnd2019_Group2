#ifndef  _SETTING_SCENE_H_
#define  _SETTING_SCENE_H_
#include "cocos2d.h"
#include"ResourceManager.h"
USING_NS_CC;

class SettingScene : public cocos2d::Scene
{
public:
	float countT = 0;
	static cocos2d::Scene* createScene();
	virtual bool init();
	void update(float deltaTime);
	CREATE_FUNC(SettingScene);
	void ClickItemSetting(Ref* pSender);
	void ClickItemPlay(Ref* pSender);
};
#endif