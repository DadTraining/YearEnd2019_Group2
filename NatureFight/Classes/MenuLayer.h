#ifndef  __MENU_LAYER__
#define  __MENU_LAYER__
#include<ResourceManager.h>
#include<Player.h>
#include<SneakyJoystick.h>
#include<SneakyJoystickSkinnedBase.h>
#include <vector>
#include<ItemLayer.h>
#include<MainMenuScene.h>
#include <SettingScene.h>
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
	void createSkillIce();
	void createSkillFire();
	void createUpLevelLayer();

	void createGameOver();


	void createFlood();
	
	void Quest(); // nhan
	void setQuestSolo(int );// nhan
	void setQuestYolo(int);// nhan
	void setD(int );//nhan
	void setC(int);//nhan
	void showItemSword(Vec2);

protected:
private:
    Player* mainPlayer;
	cocos2d::ui::LoadingBar* loadhelth;
	cocos2d::ui::LoadingBar* loaddame;

	Sprite* quest; // nhan
	Label* label1, *label2; // nhan
	int QuestSolo=0 ;//nhan
	int QuestYolo=0 ;//nhan
	int d = 0, c = 0;//nhan

    SneakyJoystick* leftJoystick;
    cocos2d::Label* _messageLabel;

	ui::Button* ButtonUpLevel;
	ItemLayer* item;
};

#endif // __MENU_LAYER__