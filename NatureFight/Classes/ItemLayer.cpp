#include "ItemLayer.h"

using namespace cocos2d;


void ItemLayer::Init()
{
	//auto visibleSize = Director::getInstance()->getVisibleSize();

	auto table = Sprite::create("settings/table2.png");
	table->setPosition(140, 400);
	table->setScaleX(1.3);
	table->setOpacity(-100);
	table->setAnchorPoint(Vec2(0.5, 0.5));
	this->addChild(table);

	Ice = ui::CheckBox::create("Sprites/Item/Stone/DaBang.png", "Sprites/Item/Stone/DaVanNang.png");
	Ice->setPosition(Vec2(45, 400));
	this->addChild(Ice,1);

	fire = ui::CheckBox::create("Sprites/Item/Stone/DaLua.png", "Sprites/Item/Stone/DaVanNang.png");
	fire->setPosition(Vec2(105, 400));
	this->addChild(fire, 1);

	 toxic = ui::CheckBox::create("Sprites/Item/Stone/DaDoc.png", "Sprites/Item/Stone/DaVanNang.png");
	toxic->setPosition(Vec2(165, 400));
	this->addChild(toxic, 1);

	wood = ui::CheckBox::create("Sprites/Item/Stone/DaMoc.png", "Sprites/Item/Stone/DaVanNang.png");
	wood->setPosition(Vec2(225, 400));
	this->addChild(wood, 1);

	icon_power = ui::Button::create("Sprites/Item/icon-kiem.png", "Sprites/Item/icon-kiem.png");
	icon_power->setScale(0.3);
	icon_power->setTouchEnabled(false);
	icon_power->setOpacity(-150);
	icon_power->setPosition(Vec2(760, 40));
	icon_power->setRotation(-60);
	this->addChild(icon_power);

}
void ItemLayer::showIconSword()
{
	auto fin = FadeIn::create(3.0f);
	icon_power->setTouchEnabled(true);
	icon_power->runAction(fin);
}


void ItemLayer::showItemSword()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto item_kiem = Sprite::create("./Sprites/Item/Sword.png");
	item_kiem->setPosition(Point(visibleSize.width / 1.5, visibleSize.height / 2));
	addChild(item_kiem, 1);
	item_kiem->setScale(0.2); item_kiem->setRotation(45);
	auto moveby = MoveBy::create(0.5, Vec2(20, 20));
	auto move_ease_out = EaseBackOut::create(moveby->clone());
	auto move = MoveBy::create(0.5, Vec2(20, -60));
	auto move_ease_in = EaseBounceOut::create(move->clone());
	auto sequence = Sequence::create(move_ease_out, move_ease_in, nullptr);
	item_kiem->runAction(sequence);
}

void ItemLayer::showItemFire()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto item_kiem = Sprite::create("./Sprites/Item/Stone/DaLua.png");
	item_kiem->setPosition(Point(visibleSize.width / 1.5, visibleSize.height / 2));
	addChild(item_kiem, 1);
	item_kiem->setScale(0.2); item_kiem->setRotation(45);
	auto moveby = MoveBy::create(1, Vec2(60, 20));
	auto move_ease_out = EaseBackOut::create(moveby->clone());
	auto move = MoveBy::create(1, Vec2(40, -90));
	auto move_ease_in = EaseBounceOut::create(move->clone());
	auto sequence = Sequence::create(move_ease_out, move_ease_in, nullptr);
	item_kiem->runAction(sequence);
}

void ItemLayer::showItemIce()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto item_kiem = Sprite::create("./Sprites/Item/Stone/DaBang.png");
	item_kiem->setPosition(Point(visibleSize.width / 1.5, visibleSize.height / 2));
	addChild(item_kiem, 1);
	item_kiem->setScale(0.2); item_kiem->setRotation(45);
	auto moveby = MoveBy::create(1, Vec2(60, 20));
	auto move_ease_out = EaseBackOut::create(moveby->clone());
	auto move = MoveBy::create(1, Vec2(40, -90));
	auto move_ease_in = EaseBounceOut::create(move->clone());
	auto sequence = Sequence::create(move_ease_out, move_ease_in, nullptr);
	item_kiem->runAction(sequence);
}

void ItemLayer::showItemBlood(/*cocos2d::Sprite* sprite*/)
{
	auto loadingbar = Sprite::create("loadingbar_bg.png");
	loadingbar->setPosition(/*sprite->getPosition()+*/Vec2(600,415));
	loadingbar->setScaleX(1.6f);
	loadingbar->setAnchorPoint(Vec2(0.5, 0.5));
	addChild(loadingbar, 1);
	load = ui::LoadingBar::create("progress.png");
	load->setPercent(100);
	load->setScaleX(1.65);
	load->setPosition(loadingbar->getPosition());
	addChild(load, 2);
	load->setDirection(ui::LoadingBar::Direction::LEFT);
}
void ItemLayer::getpercentBlood(int x)
{
	load->setPercent(load->getPercent() + x);
}

void ItemLayer::showIce()
{
	auto rotateBy = RotateBy::create(10, 360);
	auto emitter = ParticleGalaxy::create();
	emitter->setPosition(Ice->getPosition());
	emitter->setScale(0.5f);
	addChild(emitter);
	Ice->runAction(RepeatForever::create(rotateBy));;
}

void ItemLayer::showFire()
{
	auto rotateBy = RotateBy::create(15, 360);
	auto emitter = ParticleSun::create();
	emitter->setPosition(fire->getPosition());
	addChild(emitter);
	fire->runAction(RepeatForever::create(rotateBy));;
}

void ItemLayer::showToxic()
{
	auto rotateBy = RotateBy::create(15, 360);
	auto emitter = ParticleSun::create();
	emitter->setPosition(toxic->getPosition());
	addChild(emitter);
	toxic->runAction(RepeatForever::create(rotateBy));;
}

void ItemLayer::showWood()
{
	auto rotateBy = RotateBy::create(15, 360);
	auto emitter = ParticleGalaxy::create();
	emitter->setPosition(wood->getPosition());
	emitter->setScale(0.5f);
	addChild(emitter);
	wood->runAction(RepeatForever::create(rotateBy));;
}
