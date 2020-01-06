#ifndef  __MENU_LAYER__
#define  __MENU_LAYER__
#include<ResourceManager.h>
#include<Player.h>
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
protected:
private:
    Player* mainPlayer;
    SneakyJoystick* leftJoystick;
    cocos2d::Label* _messageLabel;
};

#endif // __MENU_LAYER__