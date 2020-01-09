#ifndef  __MENU_LAYER__
#define  __MENU_LAYER__
#include<ResourceManager.h>
#include<Player.h>
#include<SneakyJoystick.h>
#include<SneakyJoystickSkinnedBase.h>
#include <vector>
#include<ItemLayer.h>
#include<MainMenuScene.h>
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
	
	void Quest(); // nhan
	void setQuestSolo(int );// nhan
	void setQuestYolo(int);// nhan
	void setD(int );//nhan
	void setC(int);//nhan

protected:
private:
    Player* mainPlayer;
	
	Sprite* quest; // nhan
	Label* label1, *label2; // nhan
	int QuestSolo=0 ;//nhan
	int QuestYolo=0 ;//nhan
	int d = 0, c = 0;//nhan

    SneakyJoystick* leftJoystick;
    cocos2d::Label* _messageLabel;


	ItemLayer* item;
};

#endif // __MENU_LAYER__