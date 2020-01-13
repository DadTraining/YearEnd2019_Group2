#ifndef __ITEM_LAYER_H__
#define __ITEM_LAYER_H__

#include "ui/CocosGUI.h"
#include "cocos2d.h"

class ItemLayer : public cocos2d::Layer
{
public:
	void Init();
	//
	void showIconSword();
	//
	void showItemSword();
	void showItemFire();
	void showItemIce();
	void showItemBlood(/*cocos2d::Sprite* sprite*/);
	//
	void getpercentBlood(int x);
	//da
	void showFire();
	void showIce();
	void showToxic();
	void showWood();


public:
	cocos2d::ui::LoadingBar* load;
	cocos2d::ui::Button* item_blood;
	cocos2d::ui::Button* icon_power;
	cocos2d::ui::Button* icon_fire;
	cocos2d::ui::Button* icon_ice;

	cocos2d::ui::CheckBox* Ice;
	cocos2d::ui::CheckBox* fire;
	cocos2d::ui::CheckBox* wood;
	cocos2d::ui::CheckBox* toxic;
};
#endif