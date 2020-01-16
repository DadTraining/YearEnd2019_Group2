#include "ItemLayer.h"

using namespace cocos2d;


void ItemLayer::Init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto table = Sprite::create("settings/table2.png");
	table->setPosition(Vec2(0, visibleSize.height));
	table->setAnchorPoint(Vec2(0, 1));
	table->setScaleX(1.3);
	table->setScaleY(0.5);
	table->setOpacity(-100);
	this->addChild(table);

	Ice = ui::CheckBox::create("Sprites/Item/Stone/DaBang.png", "Sprites/Item/Stone/DaVanNang.png");
	Ice->setScale(0.3f);
	Ice->setPosition(table->getPosition() + Vec2(30, -(table->getContentSize().height / 4)));
	this->addChild(Ice, 1);

	fire = ui::CheckBox::create("Sprites/Item/Stone/DaLua.png", "Sprites/Item/Stone/DaVanNang.png");
	fire->setScale(0.3f);
	fire->setPosition(Ice->getPosition() + Vec2(70, 0));
	this->addChild(fire, 1);

	toxic = Sprite::create("Sprites/Item/Stone/DaDoc.png");
	toxic->setPosition(fire->getPosition() + Vec2(70, 0));
	toxic->setScale(0.5);
	this->addChild(toxic, 1);
	wood = Sprite::create("Sprites/Item/Stone/DaMoc.png");
	wood->setPosition(toxic->getPosition() + Vec2(70, 0));
	wood->setScale(0.5);
	this->addChild(wood, 1);

	auto loadingBarGB = Sprite::create("Sprites/Item/pow/power15_1.png");
	loadingBarGB->setScale(1.5f);
	loadingBarGB->setPosition(Vec2(visibleSize.width - 145, 35));
	addChild(loadingBarGB);

	icon_power = ui::LoadingBar::create("Sprites/Item/pow/power15.png");
	icon_power->setScale(1.5f);
	icon_power->setPercent(0);
	icon_power->setDirection(ui::LoadingBar::Direction::LEFT);
	icon_power->setPosition(loadingBarGB->getPosition());
	this->addChild(icon_power);

	icon_power_bt = Sprite::create("Sprites/Item/pow/power15.png");
	icon_power_bt->setScale(1.5f);
	icon_power_bt->setPosition(loadingBarGB->getPosition());
	AnimatePow();
	icon_power_bt->setVisible(false);
	this->addChild(icon_power_bt, -1);

}
void ItemLayer::showIconSword()
{
	auto fin = FadeIn::create(3.0f);
	icon_power->setTouchEnabled(true);
	icon_power->runAction(fin);
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
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto loadingbar = Sprite::create("loadingbar_bg.png");
	loadingbar->setPosition(Vec2(visibleSize.width * 2 / 3, visibleSize.height - 20));
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
void ItemLayer::AnimatePow()
{
	cocos2d::SpriteFrameCache* spriteCache = ResourceManager::GetInstance()->GetFrameAIById(999);
	cocos2d::Vector<cocos2d::SpriteFrame*> exFrames;
	int i = 1;
	std::string link;
	while (true) {
		link = "power" + std::to_string(i) + ".png";
		if (i >= 10) link = "power" + std::to_string(i) + ".png";
		if (spriteCache->getSpriteFrameByName(link) == nullptr) break;
		exFrames.pushBack(spriteCache->getSpriteFrameByName(link));
		i++;
	}
	auto animation = cocos2d::Animation::createWithSpriteFrames(exFrames, 0.3f);
	auto animate = cocos2d::Animate::create(animation);
	cocos2d::RepeatForever* repeat = cocos2d::RepeatForever::create(animate);
	icon_power_bt->runAction(repeat);
}