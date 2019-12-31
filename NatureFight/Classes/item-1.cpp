#include "item-1.h"
#include <vector> 
#include "SimpleAudioEngine.h"
//#include <ResourceManager.h>
USING_NS_CC;

//using namespace CocosDenshion;
Item::Item(cocos2d::Scene* scene)
{
	sceneGame = scene;
}

void Item::Update(float deltaTime)
{
	
}

void Item::Init()
{
	icon_kiem = Sprite::create("Sprites/Item/icon-kiem.png");
	icon_kiem->setScale(0.3);
	icon_kiem->setOpacity(-150);
	icon_kiem->setPosition(760, 40);
	icon_kiem->setRotation(-60);
	this->sceneGame->addChild(icon_kiem);
	 icon_lua = Sprite::create("Sprites/Item/icon-lua.png");
	icon_lua->setScale(0.3);
	icon_lua->setOpacity(-150);
	icon_lua->setRotation(-45);
	icon_lua->setPosition(800, 100);
	this->sceneGame->addChild(icon_lua);
	 icon_bang = Sprite::create("Sprites/Item/icon-bang.png");
	icon_bang->setScale(0.3);
	icon_bang->setOpacity(-150);
	icon_bang->setRotation(-25);
	icon_bang->setPosition(870, 140);
	this->sceneGame->addChild(icon_bang);

}

void Item::showKiem()
{
	auto fin = FadeIn::create(3.0f);
	icon_kiem->runAction(fin);
}

void Item::showLua()
{
	auto fin = FadeIn::create(3.0f);
	icon_lua->runAction(fin);
}

void Item::showBang()
{
	auto fin = FadeIn::create(3.0f);
	icon_bang->runAction(fin);
}

void Item::showItemKiem()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto item_kiem = Sprite::create("./Sprites/Item/Sword.png");
	item_kiem->setPosition(Point(visibleSize.width / 1.5, visibleSize.height / 2));
	this->sceneGame->addChild(item_kiem,1);
	item_kiem->setScale(0.2); item_kiem->setRotation(45);
	auto moveby = MoveBy::create(1, Vec2(60, 20));
	auto move_ease_out = EaseBackOut::create(moveby->clone());
	auto move = MoveBy::create(1, Vec2(40, -90));
	auto move_ease_in = EaseBounceOut::create(move->clone());
	auto sequence = Sequence::create(move_ease_out, move_ease_in, nullptr);
	item_kiem->runAction(sequence);
}

void Item::showItemLua()
{
}

void Item::showItemBang()
{
}



