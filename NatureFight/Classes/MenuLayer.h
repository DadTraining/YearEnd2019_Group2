#ifndef  __MENU_LAYER__
#define  __MENU_LAYER__
#include<ResourceManager.h>
#include<Player.h>
#include<item-1.h>
#include "ui/CocosGUI.h"
#include<SneakyJoystick.h>
#include<SneakyJoystickSkinnedBase.h>
class MenuLayer : public cocos2d::Layer
{
public:
    MenuLayer(Player* mainPlayer);
    ~MenuLayer();
    void createQuest();
    virtual bool init();
    void update(float);
    void createButtonLayer();
    void createJoyStickLayer();
    void createLabelLayer();
	void showItemMau(cocos2d::Sprite * sprite);
protected:
private:
	cocos2d::ui::LoadingBar* load;
    Player* mainPlayer;
    SneakyJoystick* leftJoystick;
    cocos2d::Label* _messageLabel;
	Item* item;
};

#endif // __MENU_LAYER__