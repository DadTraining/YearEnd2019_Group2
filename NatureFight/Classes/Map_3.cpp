#include "Map_3.h"

using namespace std;
float times3 = 0;
int x3 = 1;//nhan


Scene* Map_3::createScene()
{
    return Map_3::create();
}

bool Map_3::init()
{
    if ( !Scene::initWithPhysics() )
    {
        return false;
    }
	schedule(schedule_selector(Map_3::update));
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//create map
	addMap();
	//create Physics 
	createPhysicMap();
	
	

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Map_3::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(Map_3::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(Map_3::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	

	auto listenerKey = EventListenerKeyboard::create();
	listenerKey->onKeyPressed = CC_CALLBACK_2(Map_3::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKey, this);

	this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	this->getPhysicsWorld()->setSubsteps(7);
	
	// va cham npc
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Map_3::onContactBegin, this);
	contactListener->onContactPreSolve = CC_CALLBACK_1(Map_3::onContactPreSolve, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(Map_3::onContactSeparate, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
	//end va cham npc
	
	menuLayer = new MenuLayer(this->mainPlayer);
	this->addChild(menuLayer, 2);
	return true;
}

void Map_3::update(float deltaTime)
{
	mainPlayer->Update(deltaTime);
	menuLayer->update(deltaTime);
	this->getDefaultCamera()->setPosition(mainPlayer->m_sprite->getPosition());
	times3 += deltaTime;
//	boss->Collision(mainPlayer, deltaTime);
	for (int i = 0; i < ai.size(); i++) {
		ai[i]->Collision(mainPlayer, deltaTime);
		if (Distance(mainPlayer->m_sprite->getPosition(), ai[i]->m_sprite->getPosition()) < 100)
			ai[i]->physicsBodyChar->setVelocity(mainPlayer->m_sprite->getPosition() - ai[i]->m_sprite->getPosition());
		else ai[i]->physicsBodyChar->setVelocity(Vec2(0, 0));

	}
	if (x3 == 2) {
		menuLayer->setD(mainPlayer->CountCreep);
	}
	if (x3 == 4) {
		
		menuLayer->setC(mainPlayer->CountCreep);
	}
}
bool Map_3::onTouchBegan(Touch* touch, Event* event)
{
	return true;
}
bool Map_3::onTouchEnded(Touch* touch, Event* event)
{
	return true;
}
bool Map_3::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
	return false;
}
void Map_3::addMap()
{
	map = TMXTiledMap::create("map3/map3.tmx");
	map->setAnchorPoint(Vec2(0, 0));
	map->setPosition(Vec2(0, 0));
	MapBackGround = TMXTiledMap::create("map3/BackGroundMap3.tmx");
	//physic map
	mObjectGroup = map->getObjectGroup("colision");
	mObjectGroup1 = map->getObjectGroup("event");
	addChild(map,20);
	addChild(MapBackGround);
	

}
float Map_3::Distance(Vec2 A, Vec2 C) {
	return std::sqrt((A.x - C.x) * (A.x - C.x) + (A.y - C.y) * (A.y - C.y));
}
void Map_3::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (times3 > 2.0f && keyCode == EventKeyboard::KeyCode::KEY_SPACE) {
		times3 = 0;
		mainPlayer->SetState(mainPlayer->ACTION_ATTACK);
	}
	if (Distance(mainPlayer->m_sprite->getPosition(), mainPlayer->m_sprite->getPosition()) < 100.0f)
	{
		mainPlayer->SetState(mainPlayer->ACTION_ATTACK);
	}
}
//nhan

bool Map_3::onContactBegin(const PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA && nodeB)
	{
		if (nodeA->getTag() == playertag & nodeB->getTag() == NpcSolotag || nodeB->getTag() == playertag & nodeA->getTag() == NpcSolotag)
		{
			if (x3 == 3) {
				menuLayer->setQuestSolo(2);
				npcsolo->Collision();
				x3 += 1;
			}
			if (x3 == 4) {
				if (mainPlayer->CountCreep >= 6) {
					menuLayer->showItemSword(npcYolo->m_sprite->getPosition());
					mainPlayer->CountCreep = 0;
				}
			}
		}
		else if (nodeA->getTag() == playertag & nodeB->getTag() == NpcYolotag || nodeB->getTag() == playertag & nodeA->getTag() == NpcYolotag)
		{
			if (x3 == 1) {
				npcYolo->Collision1();
				menuLayer->setQuestYolo(1);
				mainPlayer->CountCreep = 0;
				x3 += 1;
			}
			if (x3 == 2) {
				if (mainPlayer->CountCreep >= 3) {
					menuLayer->showItemSword(npcYolo->m_sprite->getPosition());
					menuLayer->setD(4);
					mainPlayer->CountCreep = 0;
					x3 += 1;
				}
			}

		}
		
	}
	return true;

}

bool Map_3::onContactPreSolve(const PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA && nodeB)
	{
	}

	return true;
}

bool Map_3::onContactSeparate(const PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA && nodeB)
	{
	}

	return true;
}


void Map_3::createPhysicMap()
{
	// set physics map
	auto objects = mObjectGroup->getObjects();
	for (int i = 0; i < objects.size(); i++)
	{
		auto object = objects.at(i);
		auto properties = object.asValueMap();
		float posx3 = properties.at("x").asFloat();
		float posY = properties.at("y").asFloat();
		int type = object.asValueMap().at("type").asInt();
		if (type == 1)
		{

			auto physics = PhysicsBody::createBox(Size(properties.at("width").asFloat(), properties.at("height").asFloat()), PhysicsMaterial(1.0f, 0.0f, 0));
			physics->setDynamic(false);
			physics->setCollisionBitmask(Model::BITMASK_GROUND);
			physics->setContactTestBitmask(true);
			auto x3 = properties.at("width").asFloat() / 2 + posx3;
			auto y = properties.at("height").asFloat() / 2 + posY;
			auto node = Node::create();
			node->setPosition(Vec2(x3, y));
			this->addChild(node);
			node->setPhysicsBody(physics);
		}
		if (type == 2)
		{

			auto edgeBody = PhysicsBody::createEdgeBox(Size(properties.at("width").asFloat(), properties.at("height").asFloat()), PhysicsMaterial(1.0f, 0.0f, 0));
			auto edgeNode = Node::create();
			edgeNode->setPosition(Vec2(properties.at("width").asFloat() / 2 + posx3, properties.at("height").asFloat() / 2 + posY));
			addChild(edgeNode);
			edgeNode->setPhysicsBody(edgeBody);
		}
	}

	// set position main
	auto objects1 = mObjectGroup1->getObjects();
	for (int i = 0; i < objects1.size(); i++)
	{
		auto object1 = objects1.at(i);
		auto properties = object1.asValueMap();
		float posx3 = properties.at("x").asFloat();
		float posY = properties.at("y").asFloat();
		int type = object1.asValueMap().at("type").asInt();
		if (type == 2)
		{
			//
			mainPlayer = new Player(this);
			mainPlayer->m_sprite->setPosition(Vec2(posx3, posY));
		}
		if (type == 3)
		{
			//npc zolo
			npcsolo = new Npclv1(this);
			npcsolo->Init();
			npcsolo->m_sprite->setTag(NpcSolotag);
			npcsolo->m_sprite->runAction(npcsolo->Communication());
			npcsolo->m_sprite->setPosition(Vec2(posx3, posY));
		}
		if (type == 4)
		{
			//
			npcYolo = new Npclv1(this);
			npcYolo->Init();
			npcYolo->m_sprite->setTag(NpcYolotag);
			npcYolo->m_sprite->runAction(npcYolo->CommunicationNPCYolo());
			npcYolo->m_sprite->setPosition(Vec2(posx3, posY));
		}
		if (type == 1)
		{
			AiLv1* ailv = new AiLv1(this);
			ailv->m_sprite->setTag(AILV1+i);
			ailv->m_sprite->setPosition(Vec2(posx3, posY));
			ai.push_back(ailv);
		}
	}
}


//end nhan