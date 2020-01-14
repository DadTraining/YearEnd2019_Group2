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


private:
	cocos2d::ui::LoadingBar* load;
	cocos2d::ui::Button* item_blood;
	cocos2d::ui::Button* icon_sword;
	cocos2d::ui::Button* icon_fire;
	cocos2d::ui::Button* icon_ice;
	cocos2d::Sprite* Ice;
	cocos2d::Sprite* fire;
	cocos2d::Sprite* wood;
	cocos2d::Sprite* toxic;
};
#endif