#include "MapTutorialScene.h"

USING_NS_CC;
using namespace std;

Scene* MapTutorialScene::createScene()
{
    return MapTutorialScene::create();
}

bool MapTutorialScene::init()
{
    if ( !Scene::initWithPhysics() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	addMap();
	aiLv1 = new Player(this);
	aiLv1->Init();
	aiLv1->m_sprite->runAction(aiLv1->IdleRight());	
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(MapTutorialScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(MapTutorialScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(MapTutorialScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	JoyStick = Sprite::create("circle-icon-3.jpg");
	JoyStick->setScale(0.4);
	JoyStick->setPosition(120, 100);
	addChild(JoyStick);
    return true;
}
void MapTutorialScene::update(FLOAT deltaTime)
{
}
bool MapTutorialScene::onTouchBegan(Touch* touch, Event* event)
{
	auto mt = MoveTo::create(0, Vec2(touch->getLocation()));
	JoyStick->runAction(mt);
	return true;
}
bool MapTutorialScene::onTouchEnded(Touch* touch, Event* event)
{
	auto mt = MoveTo::create(0, Vec2(120,100));
	JoyStick->runAction(mt);
	aiLv1->m_sprite->stopAllActions();
	aiLv1->m_sprite->runAction(aiLv1->IdleRight());
	aiLv1->physicsBody->setVelocity(Vec2(0,0));
	return true;
}
bool MapTutorialScene::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
	Vec2 MoveJoyStick = touch->getLocation();
	/*if (Distance(Vec2(120, 100), touch->getLocation()) > 100) {
		CCLOG("%f %f", MoveJoyStick.x, MoveJoyStick.y);
		float JoyStickPositionY = 100 + 80 / (std::sqrt(1 + (touch->getLocation().x - 120) * (touch->getLocation().x - 120)
			/ (touch->getLocation().y - 100) * (touch->getLocation().y - 100)));
		float JoyStickPositionX = 120 + ((touch->getLocation().x - 120) / (touch->getLocation().y - 100)) * JoyStickPositionY;
	MoveJoyStick = Vec2(JoyStickPositionX, JoyStickPositionY);
	CCLOG("%f %f",JoyStickPositionX,JoyStickPositionY);
	}*/
	if (Distance(Vec2(120, 100), touch->getLocation()) > 100) {
		MoveJoyStick = Vec2(120, 100);
	}
	auto mt = MoveTo::create(0, MoveJoyStick);
	JoyStick->runAction(mt);
	aiLv1->m_sprite->stopAllActions();
	aiLv1->m_sprite->runAction(aiLv1->MovingRight());
	aiLv1->physicsBody->setVelocity(MoveJoyStick-Vec2(120,100));
	return false;
}
void MapTutorialScene::addMap()
{
	auto map = TMXTiledMap::create("Map1/map1.tmx");
	map->setAnchorPoint(Vec2(0, 0));
	map->setScale(0.45);
	map->setPosition(Vec2(0, 0));
	addChild(map);
}
float MapTutorialScene::Distance(Vec2 A, Vec2 C) {
	return std::sqrt((A.x - C.x) * (A.x - C.x) + (A.y - C.y) * (A.y - C.y));
}
