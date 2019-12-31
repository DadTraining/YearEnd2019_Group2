#pragma once
#include "cocos2d.h"
//#include "ObjectParent.h"
class Item 
{
public:

	Item(cocos2d::Scene* scene);
	void Update(float deltaTime);
	void Init();
	void showKiem();
	void showLua();
	void showBang();
	void showItemKiem();
	void showItemLua();
	void showItemBang();
	~Item();

private:
	//cocos2d::Sprite* item_kiem;
	//cocos2d::Sprite* item_lua;
	//cocos2d::Sprite* item_bang;
	cocos2d::Sprite* icon_kiem;
	cocos2d::Sprite* icon_lua;
	cocos2d::Sprite* icon_bang;
	cocos2d::Scene* sceneGame;
};