#include "MainMenuScene.h"
#include <cocos\ui\UIButton.h>
#include <ResourceManager.h>
#include <GamePlayScene.h>
using namespace std;
Scene* MainMenuScene::createScene()
{
	return MainMenuScene::create();
}
void changeScene() {
	auto scene = GamePlayScene::createScene();
	Director::getInstance()->replaceScene(scene);
}
bool MainMenuScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto playButton = ResourceManager::GetInstance()->GetButtonById(1);
	playButton->setPosition(Vec2(160, 240));
	playButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			changeScene();
			break;
		default:
			break;
		}
		});
	playButton->removeFromParent();
	addChild(playButton);
	return true;

}
