#include "LoadingScene.h"
#include <ResourceManager.h>
#include "ui/CocosGUI.h"
#include <GamePlayScene.h>
#include <MainMenuScene.h>
using namespace std;
#define TagLoadingbar 1
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
	std::string s = "Data.bin";
	ResourceManager::GetInstance()->Init(s);
	//resource->GetButtonById('1');
	auto loadingBarGB = ResourceManager::GetInstance()->GetSpriteById(6);
	loadingBarGB->setPosition(Vec2(160, 250));
	addChild(loadingBarGB);
	static auto loadingbar = ui::LoadingBar::create("Sprites/Loading/progress.png");
	loadingbar->setPosition(loadingBarGB->getPosition());
	loadingbar->setPercent(0);
	loadingbar->setDirection(ui::LoadingBar::Direction::LEFT);
	addChild(loadingbar);
	auto spritesBackground = ResourceManager::GetInstance()->GetSpriteById(1);
	spritesBackground->setPosition(160, 240);
	addChild(spritesBackground, -1);
	auto updateLoadingBar = CallFunc::create([]() {
		if (loadingbar->getPercent() < 99)
		{
			loadingbar->setPercent(loadingbar->getPercent() + 1);
		}else 
		{
			auto scene = MainMenuScene::createScene();
			Director::getInstance()->replaceScene(scene);
		}
		});
	
	auto sequenceRunUpdateLoadingBar = Sequence::createWithTwoActions(updateLoadingBar, DelayTime::create(0.1f));
	auto repeat = Repeat::create(sequenceRunUpdateLoadingBar, 100);
	loadingbar->runAction(repeat);



}

void LoadingScene::update(FLOAT deltaTime)
{
}

