#include "MapTutorialScene.h"

USING_NS_CC;
using namespace std;
float times = 0;
bool faceRight = true;
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
	schedule(schedule_selector(MapTutorialScene::update));
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

	auto listenerKey = EventListenerKeyboard::create();
	listenerKey->onKeyPressed = CC_CALLBACK_2(MapTutorialScene::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKey, this);
	JoyStick = Sprite::create("circle-icon-3.jpg");
	JoyStick->setScale(0.4);
	JoyStick->setPosition(120, 100);
	addChild(JoyStick);

	/*auto followTheSprite = Follow::create(aiLv1->m_sprite, Rect::ZERO);
	this->runAction(followTheSprite);*/

	auto ButtonAttack = ui::Button::create("Button_Attack_Normal.png", "Button_Attack_Selected.png");
	ButtonAttack->setPosition(Vec2(800, 100));
	ButtonAttack->setScale(0.3f);
	ButtonAttack->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
		case ui::Widget::TouchEventType::MOVED:
			if (times > 2.0f) {
				times = 0;
				aiLv1->m_sprite->runAction(aiLv1->AttackRight());
			}

			break;
		case ui::Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
	});

	addChild(ButtonAttack);

    return true;
}
void MapTutorialScene::update(FLOAT deltaTime)
{
	times += deltaTime;
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
	if (touch->getLocation().x < 120 && faceRight) {
		aiLv1->m_sprite->setFlipX(true);
		faceRight = !faceRight;
	}
	if (touch->getLocation().x > 120 && faceRight==false) {
		aiLv1->m_sprite->setFlipX(false);
		faceRight = !faceRight;
	}
	if (Distance(Vec2(120, 100), touch->getLocation()) > 100) {
		MoveJoyStick = Vec2(120, 100);
	}
	auto mt = MoveTo::create(0, MoveJoyStick);
	JoyStick->runAction(mt);
	aiLv1->m_sprite->stopAllActions();
	aiLv1->m_sprite->runAction(aiLv1->MovingRight());
	aiLv1->physicsBody->setVelocity((MoveJoyStick - Vec2(120, 100))*2.5f);
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
void MapTutorialScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (times > 2.0f && keyCode == EventKeyboard::KeyCode::KEY_SPACE) {
		times = 0;
		aiLv1->m_sprite->runAction(aiLv1->AttackRight());
	}
}