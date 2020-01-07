
#include "LoadingScene.h"
#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;
Scene* LoadingScene::createScene()
{
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = LoadingScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool LoadingScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	//load sound
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("melodyloops.mp3");


	auto loadingbar = Sprite::create("loadingbg.png");
	loadingbar->setPosition(450, 200);
	loadingbar->setAnchorPoint(Vec2(0.5, 0.5));
	loadingbar->setScale(1.0f);
	addChild(loadingbar, 1);
	static auto load = ui::LoadingBar::create("loadingbar.png");
	load->setPercent(0);
	load->setPosition(loadingbar->getPosition() + Vec2(-40, 25));
	load->setScaleX(2.3f);
	load->setDirection(ui::LoadingBar::Direction::LEFT);
	addChild(load, 0);

	auto updateLoadingBar = CallFunc::create([]() {
		if (load->getPercent() < 100)
		{
			load->setPercent(load->getPercent() + 2.5);
		}

	});
	auto sqLoad = Sequence::createWithTwoActions(updateLoadingBar, DelayTime::create(0.1f));
	auto repeat = Repeat::create(sqLoad, 100);
	load->runAction(repeat);

	scheduleUpdate();
	return true;
}
void LoadingScene::update(float deltaTime)
{
	countT += deltaTime;
	if (countT >= 4) {
		auto scene = MainMenuScene::createScene();
		Director::getInstance()->replaceScene(scene);
	}
}

