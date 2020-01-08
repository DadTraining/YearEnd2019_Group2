#ifndef __ITEM_LAYER_H__
#define __ITEM_LAYER_H__

#include "ui/CocosGUI.h"
#include "cocos2d.h"

class ItemLayer : public cocos2d::Layer
{
public:
	void Init();
	void showKiem();
	void showLua();
	void showBang();
	void showItemKiem();
	void showItemLua();
	void showItemBang();
	void showItemMau(cocos2d::Sprite* sprite);
	void getpercent(int x);

private:
	cocos2d::ui::LoadingBar* load;
	cocos2d::Sprite* item_mau;
	cocos2d::Sprite* icon_kiem;
	cocos2d::Sprite* icon_lua;
	cocos2d::Sprite* icon_bang;
};
#endif