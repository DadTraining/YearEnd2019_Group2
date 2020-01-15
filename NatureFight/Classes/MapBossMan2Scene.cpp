#include "MapBossMan2Scene.h"

using namespace std;
float times4 = 0;


Scene* MapBossMan2Scene::createScene()
{
    return MapBossMan2Scene::create();
}

bool MapBossMan2Scene::init()
{
    if ( !Scene::initWithPhysics() )
    {
        return false;
    }
	schedule(schedule_selector(MapBossMan2Scene::update));
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//create map
	addMap();
	//create Physics 
	createPhysicMap();
	
	

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(MapBossMan2Scene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(MapBossMan2Scene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(MapBossMan2Scene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	

	auto listenerKey = EventListenerKeyboard::create();
	listenerKey->onKeyPressed = CC_CALLBACK_2(MapBossMan2Scene::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKey, this);

	this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	this->getPhysicsWorld()->setSubsteps(7);
	
	// va cham npc
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(MapBossMan2Scene::onContactBegin, this);
	contactListener->onContactPreSolve = CC_CALLBACK_1(MapBossMan2Scene::onContactPreSolve, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(MapBossMan2Scene::onContactSeparate, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
	//end va cham npc
	
	menuLayer = new MenuLayer(this->mainPlayer);
	this->addChild(menuLayer, 2);
	menuLayer->getIcon_Fire()->setEnabled(true);
	menuLayer->getIcon_Ice()->setEnabled(true);

	return true;
}

void MapBossMan2Scene::update(float deltaTime)
{
	mainPlayer->Update(deltaTime);
	menuLayer->update(deltaTime);
	this->getDefaultCamera()->setPosition(mainPlayer->m_sprite->getPosition());
	times4 += deltaTime;

	bosslv1->Collision(mainPlayer, deltaTime);
}
bool MapBossMan2Scene::onTouchBegan(Touch* touch, Event* event)
{
	return true;
}
bool MapBossMan2Scene::onTouchEnded(Touch* touch, Event* event)
{
	return true;
}
bool MapBossMan2Scene::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
	return false;
}
void MapBossMan2Scene::addMap()
{
	map = TMXTiledMap::create("mapBossLv1/tiled.tmx");
	map->setAnchorPoint(Vec2(0, 0));
	map->setPosition(Vec2(0, 0));
	//physic map
	mObjectGroup = map->getObjectGroup("colision");
	addChild(map,20);

	MapBackGround = TMXTiledMap::create("mapBossLv1/BackGround.tmx");
	addChild(MapBackGround);
	

}
float MapBossMan2Scene::Distance(Vec2 A, Vec2 C) {
	return std::sqrt((A.x - C.x) * (A.x - C.x) + (A.y - C.y) * (A.y - C.y));
}
void MapBossMan2Scene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (times4 > 2.0f && keyCode == EventKeyboard::KeyCode::KEY_SPACE) {
		times4 = 0;
		mainPlayer->SetState(mainPlayer->ACTION_ATTACK);
	}
	if (Distance(mainPlayer->m_sprite->getPosition(), mainPlayer->m_sprite->getPosition()) < 100.0f)
	{
		mainPlayer->SetState(mainPlayer->ACTION_ATTACK);
	}
}
//nhan

bool MapBossMan2Scene::onContactBegin(const PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA && nodeB)
	{
		if (nodeA->getTag() == CREEPATTACK & nodeB->getTag() == playertag || nodeA->getTag() == playertag & nodeB->getTag() == CREEPATTACK)
		{
			mainPlayer->m_sprite->setColor(ccc3(200, 0, 0));
			mainPlayer->SetState(Player::ACTION_HURT);
			CCLOG("mau :%d", mainPlayer->m_health);
			CCLOG(" ********* ");
		}
		
	}
	return true;

}

bool MapBossMan2Scene::onContactPreSolve(const PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA && nodeB)
	{
	}

	return true;
}

bool MapBossMan2Scene::onContactSeparate(const PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA && nodeB)
	{
	}

	return true;
}


void MapBossMan2Scene::createPhysicMap()
{
	// set physics map
	auto objects = mObjectGroup->getObjects();
	for (int i = 0; i < objects.size(); i++)
	{
		auto object = objects.at(i);
		auto properties = object.asValueMap();
		float posx4 = properties.at("x").asFloat();
		float posY = properties.at("y").asFloat();
		int type = object.asValueMap().at("type").asInt();
		if (type == 1)
		{

			auto physics = PhysicsBody::createBox(Size(properties.at("width").asFloat(), properties.at("height").asFloat()), PhysicsMaterial(1.0f, 0.0f, 0));
			physics->setDynamic(false);
			physics->setCollisionBitmask(Model::BITMASK_GROUND);
			physics->setContactTestBitmask(true);
			auto x4 = properties.at("width").asFloat() / 2 + posx4;
			auto y = properties.at("height").asFloat() / 2 + posY;
			auto node = Node::create();
			node->setPosition(Vec2(x4, y));
			this->addChild(node);
			node->setPhysicsBody(physics);
		}
		if (type == 2)
		{

			auto edgeBody = PhysicsBody::createEdgeBox(Size(properties.at("width").asFloat(), properties.at("height").asFloat()), PhysicsMaterial(1.0f, 0.0f, 0));
			auto edgeNode = Node::create();
			edgeNode->setPosition(Vec2(properties.at("width").asFloat() / 2 + posx4, properties.at("height").asFloat() / 2 + posY));
			addChild(edgeNode);
			edgeNode->setPhysicsBody(edgeBody);
		}
		if (type == 3)
		{
			bosslv1 = new BossLv1(this);
			bosslv1->m_sprite->setPosition(Vec2(posx4, posY));
		}
		if (type == 4)
		{
			mainPlayer = new Player(this);
			mainPlayer->m_sprite->setPosition(Vec2(posx4 , posY));
		}
	}

}


//end nhan