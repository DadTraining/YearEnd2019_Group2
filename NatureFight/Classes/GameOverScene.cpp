#include "GameOverScene.h"
#include <ResourceManager.h>
#include <GamePlayScene.h>

Scene* GameOverScene::createScene()
{
	return GameOverScene::create();
}
void replayScene() {
	auto scene = GamePlayScene::createScene();
	Director::getInstance()->replaceScene(scene);
}
bool GameOverScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto resButton = ResourceManager::GetInstance()->GetButtonById(2);
	resButton->setPosition(Vec2(160, 240));
	resButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			replayScene();
			break;
		default:
			break;
		}
		});
	resButton->removeFromParent();
	addChild(resButton);
	return true;
}
