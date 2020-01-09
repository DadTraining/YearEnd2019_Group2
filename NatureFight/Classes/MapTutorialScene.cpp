#include "MapTutorialScene.h"

using namespace std;
float times = 0;



Scene* MapTutorialScene::createScene()
{
	CCLOG("Create Scene******************");
    return MapTutorialScene::create();
}

bool MapTutorialScene::init()
{
    if ( !Scene::initWithPhysics() )
    {
        return false;
    }
	CCLOG("LoadMapTutorial 1******************");
	schedule(schedule_selector(MapTutorialScene::update));
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//create map
	addMap();
	CCLOG("LoadMapTutorial 2******************");
	//create Physics 
	createPhysicMap();
	CCLOG("LoadMapTutorial 3******************");
	
	
	CCLOG("LoadMapTutorial 400******************");
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(MapTutorialScene::onTouchBegan, this);
	CCLOG("LoadMapTutorial 40******************");
	listener->onTouchMoved = CC_CALLBACK_2(MapTutorialScene::onTouchMoved, this);
	CCLOG("LoadMapTutorial 41******************");
	listener->onTouchEnded = CC_CALLBACK_2(MapTutorialScene::onTouchEnded, this);
	CCLOG("LoadMapTutorial 42******************");
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	CCLOG("LoadMapTutorial 44******************");
	

	auto listenerKey = EventListenerKeyboard::create();
	listenerKey->onKeyPressed = CC_CALLBACK_2(MapTutorialScene::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKey, this);

	CCLOG("LoadMapTutorial 5******************");
	//this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	this->getPhysicsWorld()->setSubsteps(7);
	
	// va cham npc
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(MapTutorialScene::onContactBegin, this);
	contactListener->onContactPreSolve = CC_CALLBACK_1(MapTutorialScene::onContactPreSolve, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(MapTutorialScene::onContactSeparate, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
	CCLOG("LoadMapTutorial 6******************");
	//Quest(); // Button display quest
	//end va cham npc
	CCLOG("LoadMapTutorial 7******************");
	

	
	menuLayer = new MenuLayer(this->mainPlayer);
	this->addChild(menuLayer, 2);
	CCLOG("LoadMapTutorial 8******************");
	return true;
}

void MapTutorialScene::update(float deltaTime)
{
	mainPlayer->Update(deltaTime);
	menuLayer->update(deltaTime);
	this->getDefaultCamera()->setPosition(mainPlayer->m_sprite->getPosition());
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
	map = TMXTiledMap::create("Map1/map1.tmx");
	map->setAnchorPoint(Vec2(0, 0));
	map->setPosition(Vec2(0, 0));
	MapBackGround = TMXTiledMap::create("Map1/BackGround2.tmx");
	//physic map
	mObjectGroup = map->getObjectGroup("colision");
	mObjectGroup1 = map->getObjectGroup("event");
	mPhysicsLayer = map->getLayer("item_3");
	mPhysicsLayer->setVisible(true);
	addChild(map,20);
	addChild(MapBackGround);
	

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
//nhan

bool MapTutorialScene::onContactBegin(const PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA && nodeB)
	{
		if (nodeA->getTag() == playertag & nodeB->getTag() == NpcSolotag || nodeB->getTag() == playertag & nodeA->getTag() == NpcSolotag)
		{
			questSolo = 2;
			npcsolo->Collision();
			c += 1;

		}
		if (nodeA->getTag() == playertag & nodeB->getTag() == NpcYolotag || nodeB->getTag() == playertag & nodeA->getTag() == NpcYolotag)
		{
			npcYolo->Collision1();
			questYolo = 1;
			d += 1;
		}
		/*if (nodeA->getTag() == AILV1 & nodeB->getTag() == ATTACKTAG || nodeB->getTag() == AILV1 & nodeA->getTag() == ATTACKTAG)
		{
			CCLOG("KILL");
			ailv1->m_sprite->stopAllActions();
			ailv1->m_sprite->runAction(ailv1->HurtRight());
			ailv1->health -= 10;
			if (ailv1->health <= 0) {
				ailv1->m_sprite->runAction(ailv1->DieRight());
				ailv1->physicsBodyChar->setEnabled(false);
				mainPlayer->Exp += 20;
			}
		}*/
	}
	return true;

}

bool MapTutorialScene::onContactPreSolve(const PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA && nodeB)
	{
	}

	return true;
}

bool MapTutorialScene::onContactSeparate(const PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA && nodeB)
	{
	}

	return true;
}


void MapTutorialScene::createPhysicMap()
{
	// set physics map
	auto objects = mObjectGroup->getObjects();
	CCLOG("LoadMapTutorial 31******************");
	for (int i = 0; i < objects.size(); i++)
	{
		auto object = objects.at(i);
		CCLOG("LoadMapTutorial 32******************");
		auto properties = object.asValueMap();
		CCLOG("LoadMapTutorial 33******************");
		float posX = properties.at("x").asFloat();
		CCLOG("LoadMapTutorial 34******************");
		float posY = properties.at("y").asFloat();
		CCLOG("LoadMapTutorial 35******************");
		int type = object.asValueMap().at("type").asInt();
		CCLOG("LoadMapTutorial 36******************");
		if (type == 1)
		{

			auto physics = PhysicsBody::createBox(Size(properties.at("width").asFloat(), properties.at("height").asFloat()), PhysicsMaterial(1.0f, 0.0f, 1.0f));
			CCLOG("LoadMapTutorial 37******************");
			physics->setDynamic(false);
			physics->setCollisionBitmask(Model::BITMASK_GROUND);
			physics->setContactTestBitmask(true);
			auto x = properties.at("width").asFloat() / 2 + posX;
			CCLOG("LoadMapTutorial 38******************");
			auto y = properties.at("height").asFloat() / 2 + posY;
			CCLOG("LoadMapTutorial 3******************");
			auto node = Node::create();
			node->setPosition(Vec2(x, y));
			this->addChild(node);
			CCLOG("LoadMapTutorial 39******************");
			node->setPhysicsBody(physics);
		}
		if (type == 2)
		{

			auto edgeBody = PhysicsBody::createEdgeBox(Size(properties.at("width").asFloat(), properties.at("height").asFloat()), PhysicsMaterial(1.0f, 0.0f, 1.0f));
			auto edgeNode = Node::create();
			edgeNode->setPosition(Vec2(properties.at("width").asFloat() / 2 + posX, properties.at("height").asFloat() / 2 + posY));
			addChild(edgeNode);
			edgeNode->setPhysicsBody(edgeBody);
			CCLOG("LoadMapTutorial 311******************");
		}
	}

	// set position main
	auto objects1 = mObjectGroup1->getObjects();
	CCLOG("LoadMapTutorial 312******************");
	for (int i = 0; i < objects1.size(); i++)
	{
		auto object1 = objects1.at(i);
		auto properties = object1.asValueMap();
		float posX = properties.at("x").asFloat();
		float posY = properties.at("y").asFloat();
		int type = object1.asValueMap().at("type").asInt();
		CCLOG("LoadMapTutorial 313******************");
		if (type == 2)
		{
			//
			mainPlayer = new Player(this);
			CCLOG("LoadMapTutorial 314******************");
			mainPlayer->Init();
			CCLOG("LoadMapTutorial 315******************");
			mainPlayer->m_sprite->runAction(mainPlayer->IdleRight());
			CCLOG("LoadMapTutorial 316******************");
			mainPlayer->m_sprite->setPosition(Vec2(posX, posY));
			CCLOG("LoadMapTutorial 317******************");
		}
		if (type == 3)
		{
			//npc zolo
			npcsolo = new Npclv1(this);
			CCLOG("LoadMapTutorial 318******************");
			npcsolo->Init();
			CCLOG("LoadMapTutorial 319******************");
			npcsolo->m_sprite->setTag(NpcSolotag);
			npcsolo->m_sprite->runAction(npcsolo->Communication());
			CCLOG("LoadMapTutorial 320******************");
			npcsolo->m_sprite->setPosition(Vec2(posX, posY));
			CCLOG("LoadMapTutorial 321******************");
		}
		if (type == 4)
		{
			//
			npcYolo = new Npclv1(this);
			CCLOG("LoadMapTutorial 322******************");
			npcYolo->Init();
			CCLOG("LoadMapTutorial 323******************");
			npcYolo->m_sprite->setTag(NpcYolotag);
			npcYolo->m_sprite->runAction(npcYolo->CommunicationNPCYolo());
			CCLOG("LoadMapTutorial 324******************");
			npcYolo->m_sprite->setPosition(Vec2(posX, posY));
			CCLOG("LoadMapTutorial 325******************");
		}
		/*if (type == 1)
		{
			ailv1 = new AiLv1(this);
			ailv1->Init();
			ailv1->m_sprite->runAction(ailv1->MovingRight());
			ailv1->m_sprite->setTag(AILV1);
			ailv1->m_sprite->setPosition(Vec2(posX, posY));
		}*/
	}
	CCLOG("LoadMapTutorial 3 END******************");
}


//end nhan