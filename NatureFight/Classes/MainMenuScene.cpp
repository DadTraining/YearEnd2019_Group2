#include "ui/CocosGUI.h"
#include "MainMenuScene.h"
#include "MapTutorialScene.h"
#include "SettingScene.h"

#include "SimpleAudioEngine.h"
Scene* MainMenuScene::createScene()
{
	return MainMenuScene::create();
}

using namespace CocosDenshion;
bool MainMenuScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	ResourceManager::GetInstance()->Init("DataPlayer.bin");
	ResourceManager::GetInstance()->Init("DataCreep.bin");
	auto audio = SimpleAudioEngine::getInstance();
	audio->preloadBackgroundMusic("melodyloops.mp3");
	audio->playBackgroundMusic("melodyloops.mp3", true);
	audio->setBackgroundMusicVolume(0.6f);
	auto titlelb= Label::createWithTTF("Nature Fight", "fonts/MONSTAR.otf", 70);
	titlelb->setPosition(450, 300);
	titlelb->setColor(Color3B::RED);
	addChild(titlelb,1);
	auto bgimg = Sprite::create("Battleground3.png");
	bgimg->setScale(0.55);
	bgimg->setAnchorPoint(Vec2(0.5,0.5));
	bgimg->setPosition(450, 220);
	addChild(bgimg);
	auto play = ui::Button::create("play.png");
	play->setPosition(Vec2(450, 150));
	play->setScale(0.5);
	play->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED) {
			auto scene = MapTutorialScene::createScene();
			Director::getInstance()->replaceScene(scene);
		}
	});
	addChild(play);
	auto setting = ui::Button::create("settings.png");
	setting->setPosition(Vec2(850, 370));
	setting->setScale(0.5);
	addChild(setting);
	setting->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED) {
			auto scene = SettingScene::createScene();
			Director::getInstance()->replaceScene(scene);
		}
	});

	return true;
}
void MainMenuScene::update(FLOAT deltaTime)
{
}


