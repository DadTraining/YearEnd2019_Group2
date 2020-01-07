#include "ui/CocosGUI.h"
#include "MainMenuScene.h"
#include "MapTutorialScene.h"
#include "SettingScene.h"

#include "SimpleAudioEngine.h"
Scene* MainMenuScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MainMenuScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

using namespace CocosDenshion;
bool MainMenuScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto audio = SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("melodyloops.mp3", true);
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
			Director::getInstance()->replaceScene(MapTutorialScene::createScene());
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
			Director::getInstance()->replaceScene(SettingScene::createScene());
		}
	});

	return true;
}
void MainMenuScene::update(FLOAT deltaTime)
{
}


