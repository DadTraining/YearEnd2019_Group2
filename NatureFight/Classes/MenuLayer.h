#pragma once 
#include "cocos2d.h"
#include <ui\CocosGUI.h>
#include<ResourceManager.h>
#include <SneakyJoystickSkinnedBase.h>
#include <Player.h>
#ifndef  __MENU_LAYER__
#define  __MENU_LAYER__
USING_NS_CC;
class MenuLayer : public cocos2d::Layer
{
public:
    MenuLayer(Player* mainPlayer);
    ~MenuLayer();
    void createQuest();
    virtual bool init();
    void update();
    void createButtonLayer();
    void createJoyStickLayer();
    void createLabelLayer();
protected:
private:
    Player* mainPlayer;
    SneakyJoystick* leftJoystick;
    cocos2d::Label* _messageLabel;
};

#endif // __MENU_LAYER__