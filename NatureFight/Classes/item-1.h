#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
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
	void showItemMau(cocos2d::Sprite* sprite);
	void getpercent(int x);
	~Item();

private:
	cocos2d::ui::LoadingBar* load;
	cocos2d::Sprite* item_mau;
	cocos2d::Sprite* icon_kiem;
	cocos2d::Sprite* icon_lua;
	cocos2d::Sprite* icon_bang;
	cocos2d::Scene* sceneGame;
};