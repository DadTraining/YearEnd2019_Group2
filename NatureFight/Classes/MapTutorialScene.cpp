#include "MapTutorialScene.h"

USING_NS_CC;
using namespace std;
float times = 0;
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
	mainPlayer = new Player(this);
	mainPlayer->Init();
	mainPlayer->m_sprite->runAction(mainPlayer->IdleRight());	
	
	auto mainPlayer1 = new Player(this);
	mainPlayer1->Init();
	mainPlayer1->m_sprite->runAction(mainPlayer1->MovingDown());

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(MapTutorialScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(MapTutorialScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(MapTutorialScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	Rect joystickBaseDimensions;
	joystickBaseDimensions = Rect(0, 0, 160.0f, 160.0f);

	Point joystickBasePosition;
	joystickBasePosition = Vec2(visibleSize.width * 0.2f, visibleSize.height * 0.2f);

	joystickBase = new SneakyJoystickSkinnedBase();
	joystickBase->init();
	joystickBase->setPosition(joystickBasePosition);
	joystickBase->setBackgroundSprite(Sprite::create("res/joystick_bg.png"));
	joystickBase->setThumbSprite(Sprite::create("res/joystick_center.png"));

	SneakyJoystick* aJoystick = new SneakyJoystick();
	aJoystick->initWithRect(joystickBaseDimensions);

	aJoystick->autorelease();
	joystickBase->setJoystick(aJoystick);
	joystickBase->setPosition(joystickBasePosition);

	leftJoystick = joystickBase->getJoystick();
	leftJoystick->retain();
	this->addChild(joystickBase,10);

	auto listenerKey = EventListenerKeyboard::create();
	listenerKey->onKeyPressed = CC_CALLBACK_2(MapTutorialScene::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKey, this);

	/*ailv1 = new AiLv1(this);
	ailv1->Init();
	ailv1->m_sprite->runAction(ailv1->MovingRight());*/
	this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto followTheSprite = Follow::create(mainPlayer->m_sprite, Rect::ZERO);
	this->runAction(followTheSprite);

	ButtonAttack = ResourceManager::GetInstance()->GetButtonById(5);
	ButtonAttack->setPosition(Vec2(mainPlayer->m_sprite->getPosition())+Vec2(350,-150));
	ButtonAttack->setScale(0.3f);
	ButtonAttack->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
		case ui::Widget::TouchEventType::MOVED:
			if (times > 1.0f) {
				times = 0;
				mainPlayer->SetState(mainPlayer->ACTION_ATTACK);
			//	ailv1->health -= 10;
				CCLOG("123");
			}

			break;
		case ui::Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
	});

	addChild(ButtonAttack,1);

	auto edgeBody = PhysicsBody::createEdgeBox(visibleSize);
	auto edgeNode = Node::create();
	edgeNode->setPosition(visibleSize/2);
	addChild(edgeNode);
	edgeNode->setPhysicsBody(edgeBody);

	return true;
}
void MapTutorialScene::update(FLOAT deltaTime)
{
	mainPlayer->Update(deltaTime);
	mainPlayer->physicsBody->setVelocity(Vect(leftJoystick->getVelocity())*200);
	joystickBase->setPosition(Vec2(mainPlayer->m_sprite->getPosition()) + Vec2(-370, -130));
	ButtonAttack->setPosition(Vec2(mainPlayer->m_sprite->getPosition()) + Vec2(350, -150));
	times += deltaTime;
}
bool MapTutorialScene::onTouchBegan(Touch* touch, Event* event)
{
	return true;
}
bool MapTutorialScene::onTouchEnded(Touch* touch, Event* event)
{
	return true;
}
bool MapTutorialScene::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
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
		mainPlayer->SetState(mainPlayer->ACTION_ATTACK);
	}
	if (Distance(mainPlayer->m_sprite->getPosition(), mainPlayer->m_sprite->getPosition()) < 100.0f)
	{
		mainPlayer->SetState(mainPlayer->ACTION_ATTACK);
	}
}