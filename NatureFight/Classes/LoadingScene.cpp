
#include "LoadingScene.h"
#include "MainMenuScene.h"
Scene* LoadingScene::createScene()
{
	return LoadingScene::create();
}

bool LoadingScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
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
			load->setPercent(load->getPercent() + 3);
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

