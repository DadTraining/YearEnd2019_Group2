#include "ui/CocosGUI.h"
#include "SettingScene.h"
#include "GameSetting.h"
#include "MainMenuScene.h"
#include "MapTutorialScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;
ui::CheckBox* musicbtn;
ui::CheckBox* soundbtn;
ui::Slider* slvolume;
Scene* SettingScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = SettingScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool SettingScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	//auto turn = GameSetting::getInstance()->isMusic();
	//if (turn == true)
	//{
	//	auto audio = SimpleAudioEngine::getInstance();
	//	log("asd");
	//	audio->playBackgroundMusic("melodyloops.mp3", true);
	//	log("2");
	//}


	auto bgimg = Sprite::create("settings/bgmain.jpg");
	bgimg->setScale(0.80);
	bgimg->setOpacity(-150);
	bgimg->setAnchorPoint(Vec2(0.5, 0.5));
	bgimg->setPosition(Director::getInstance()->getVisibleSize() / 2);
	addChild(bgimg);
	auto bg = Sprite::create("settings/bg.png");
	bg->setPosition(Director::getInstance()->getVisibleSize() / 2);
	bg->setScale(0.45);
	addChild(bg, 1);
	auto bglb = Sprite::create("settings/92.png");
	bglb->setPosition(Vec2(450, 370));
	bglb->setScale(0.45f);
	addChild(bglb, 3);
	auto table = Sprite::create("settings/table.png");
	table->setPosition(bg->getPosition());
	table->setScale(0.45);
	addChild(table, 2);
	auto musiclb = Label::create("MUSIC", "Arial", 24);
	musiclb->setPosition(bg->getPosition() + Vec2(-105, 80));
	musiclb->setColor(Color3B::BLACK);
	addChild(musiclb, 2);
	musicbtn = ui::CheckBox::create("settings/96.png","settings/95.png");
	musicbtn->setPosition(musiclb->getPosition() + Vec2(205, 0));
	musicbtn->setScale(0.6f);
	musicbtn->setSelected(!GameSetting::getInstance()->isMusic());
	musicbtn->addClickEventListener([&](Ref* event) {

		if (musicbtn->isSelected())
		{
			GameSetting::getInstance()->setMusic(true);
			SimpleAudioEngine::getInstance()->playBackgroundMusic("melodyloops.mp3", true);
		}
		else
		{
			GameSetting::getInstance()->setMusic(false);
			SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		}
	});
	addChild(musicbtn, 3);

	auto soundlb = Label::create("SOUND", "Arial", 24);
	soundlb->setPosition(bg->getPosition() + Vec2(-100, 30));
	soundlb->setColor(Color3B::BLACK);
	addChild(soundlb, 2);
	soundbtn = ui::CheckBox::create("settings/96.png", "settings/95.png");
	soundbtn->setPosition(soundlb->getPosition() + Vec2(200, 0));
	soundbtn->setScale(0.6f);
	soundbtn->setSelected(!GameSetting::getInstance()->isSound());
	soundbtn->addClickEventListener([&](Ref* event) {
		
		if (soundbtn->isSelected())
		{
			GameSetting::getInstance()->setSound(true);
		}
		else
		{
			GameSetting::getInstance()->setSound(false);
			SimpleAudioEngine::getInstance()->stopAllEffects();

		}
	});
	addChild(soundbtn, 3);
	auto volumlb = Label::create("VOLUME", "Arial", 24);
	volumlb->setPosition(bg->getPosition() + Vec2(0, -40));
	volumlb->setColor(Color3B::BLACK);
	addChild(volumlb, 2);

	slvolume = ui::Slider::create();
	slvolume->loadBarTexture("slider_bar_bg.png");
	slvolume->loadSlidBallTextures("slider_ball_normal.png", "slider_ball_pressed.png", "slider_ball_disable.png");
	slvolume->loadProgressBarTexture("slider_bar_pressed.png");
	slvolume->setPercent(50);
	slvolume->setColor(Color3B::ORANGE);
	slvolume->setPosition(volumlb->getPosition() + Vec2(0, -50));
	slvolume->addTouchEventListener([](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::ENDED:
			break;
		}
	});
	if (!musicbtn->isSelected() && !soundbtn->isSelected())
	{
		slvolume->setEnabled(false);
	}
	addChild(slvolume, 2);
	auto closebtn = ui::Button::create("close.png");
	closebtn->setPosition(bg->getPosition() + Vec2(200, 140));
	closebtn->setScale(0.3);
	addChild(closebtn,3);
	closebtn->addClickEventListener([&](Ref* event)
	{
		auto turn = GameSetting::getInstance()->isSound();
		if (turn == true)
		{
			auto audio = SimpleAudioEngine::getInstance();
			//log("asd");
			audio->playEffect("sounds/212.mp3", false);
			log("2");
		}
		Director::getInstance()->replaceScene(MainMenuScene::create());
	});
	//scheduleUpdate();
	return true;
}
void SettingScene::update(float deltaTime)
{
	countT += deltaTime;
	if (countT >= 4) {
		Director::getInstance()->replaceScene(MapTutorialScene::createScene());
	}
}


