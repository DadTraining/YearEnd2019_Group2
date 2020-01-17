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
	void createSkillIce();
	void createSkillFire();
	void createSkillFireIce();
	void createUpLevelLayer();
	void createPlayerDie(bool);

	void createFlood();

	void Quest(); // nhan

	void setQuestMan2(int);
	void setQuestSolo(int );// nhan
	void setQuestYolo(int);// nhan
	void setD(int );//nhan
	void setC(int);//nhan
	void showItemSword(Vec2, std::string);
	ui::Button* getIcon_Ice();
	ui::Button* getIcon_Fire();
protected:
private:
    Player* mainPlayer;

	cocos2d::ui::LoadingBar* loadhelth;
	cocos2d::ui::LoadingBar* loaddame;

	ui::Button* icon_fire;
	ui::Button* icon_fire2;
	ui::Button* icon_ice;
	ui::Button* icon_ice2;
	ui::Button* icon_fire_ice;
	Sprite* timeIconFire;
	Sprite* timeIconIce;

	void AnimationIconFire();
	void AnimationIconIce();

	Sprite* quest; // nhan
	Label* label1, *label2 , *label3 ; // nhan
	int QuestSolo=0 , QuestYolo = 0;//nhan
	int questman2=0 ;//nhan
	int d = 0, c = 0;//nhan

    SneakyJoystick* leftJoystick;
    cocos2d::Label* _messageLabel;

	ui::Button* ButtonUpLevel;
	ItemLayer* item;

	Sprite*  mPauseLayer1;

};

#endif // __MENU_LAYER__