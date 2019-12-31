#include "ui/CocosGUI.h"
#include "SettingScene.h"
#include "MainMenuScene.h"
#include "MapTutorialScene.h"
Scene* SettingScene::createScene()
{
	return SettingScene::create();
}

bool SettingScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto bg = Sprite::create("settings/bg.png");
	bg->setPosition(Vec2(450, 210));
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

	auto musicbtn = ui::Button::create("settings/95.png", "settings/96.png");
	musicbtn->setPosition(musiclb->getPosition() + Vec2(205, 0));
	musicbtn->setScale(0.6f);
	musicbtn->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:

			break;
		default:
			break;
		}


	});
	addChild(musicbtn, 3);

	auto soundlb = Label::create("SOUND", "Arial", 24);
	soundlb->setPosition(bg->getPosition() + Vec2(-100, 30));
	soundlb->setColor(Color3B::BLACK);
	addChild(soundlb, 2);
	auto soundbtn = ui::Button::create("settings/96.png", "settings/95.png");
	soundbtn->setPosition(soundlb->getPosition() + Vec2(200, 0));
	soundbtn->setScale(0.6f);

	addChild(soundbtn, 3);
	auto volumlb = Label::create("VOLUME", "Arial", 24);
	volumlb->setPosition(bg->getPosition() + Vec2(0, -40));
	volumlb->setColor(Color3B::BLACK);
	addChild(volumlb, 2);

	static auto slider = ui::Slider::create();
	slider->loadBarTexture("slider_bar_bg.png");
	slider->loadSlidBallTextures("slider_ball_normal.png", "slider_ball_pressed.png", "slider_ball_disable.png");
	slider->loadProgressBarTexture("slider_bar_pressed.png");
	slider->setPercent(50);
	slider->setColor(Color3B::ORANGE);
	slider->setPosition(volumlb->getPosition() + Vec2(0, -50));
	slider->addClickEventListener([](Ref* event) {
		log("Slider: %d", slider->getPercent());

	});
	addChild(slider, 2);

	auto closebtn = ui::Button::create("close.png");
	closebtn->setPosition(Vec2(50, 370));
	closebtn->setScale(0.5);
	addChild(closebtn);
	closebtn->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		auto scene = MainMenuScene::createScene();
		Director::getInstance()->replaceScene(scene);
	});
	//scheduleUpdate();
	return true;
}
void SettingScene::update(FLOAT deltaTime)
{
	countT += deltaTime;
	if (countT >= 4) {
		auto scene = MapTutorialScene::createScene();
		Director::getInstance()->replaceScene(scene);
	}
}


