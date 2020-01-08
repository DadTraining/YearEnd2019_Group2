#ifndef  _MENU_SCENE_H_
#define  _MENU_SCENE_H_
#include "cocos2d.h"
#include"ResourceManager.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

class MainMenuScene : public cocos2d::Scene
{
private: 
public:
	float countT = 0;
	static cocos2d::Scene* createScene();
	virtual bool init();
	void update(float deltaTime);
	CREATE_FUNC(MainMenuScene);
	void ClickItemSetting(Ref* pSender);
	void ClickItemPlay(Ref* pSender);

};
#endif _MENU_SCENE_H_
