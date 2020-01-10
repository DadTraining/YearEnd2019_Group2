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
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto audio = SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("melodyloops.mp3", true);
	auto titlelb = Label::createWithTTF("Nature Fight", "fonts/Blazed.ttf", 70);
	titlelb->setPosition(Vec2(visibleSize.width/2,visibleSize.height-visibleSize.height/4));
	titlelb->setColor(Color3B::RED);
	addChild(titlelb,1);
	auto bgimg = Sprite::create("settings/bgmain.jpg");
	bgimg->setScale(0.80);
	bgimg->setAnchorPoint(Vec2(0.5, 0.5));
	bgimg->setPosition(Director::getInstance()->getVisibleSize() / 2);
	addChild(bgimg);
	auto play = ui::Button::create("settings/playbtn.png");
	play->setPosition(Vec2(visibleSize.width/2,visibleSize.height/3));
	play->setScale(0.5);
	play->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED) {
			Director::getInstance()->replaceScene(MapTutorialScene::createScene());
		}
	});
	addChild(play);

	auto setting = ui::Button::create("settings/setting.png");
	setting->setPosition(Vec2(visibleSize));
	setting->setAnchorPoint(Vec2(1, 1));
	setting->setScale(0.4);
	addChild(setting);
	setting->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED) {
			Director::getInstance()->replaceScene(SettingScene::createScene());
		}
	});

	return true;
}
void MainMenuScene::update(float deltaTime)
{
}