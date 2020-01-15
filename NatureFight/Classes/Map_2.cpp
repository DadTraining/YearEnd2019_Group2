#include "Map_2.h"


using namespace std;
float times2 = 0;
int x2 = 1;//nhan


Scene* Map_2::createScene()
{
    return Map_2::create();
}

bool Map_2::init()
{
    if ( !Scene::initWithPhysics() )
    {
        return false;
    }
	schedule(schedule_selector(Map_2::update));
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//create map
	addMap();
	//create Physics 
	createPhysicMap();
	
	

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Map_2::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(Map_2::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(Map_2::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	

	auto listenerKey = EventListenerKeyboard::create();
	listenerKey->onKeyPressed = CC_CALLBACK_2(Map_2::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKey, this);

	this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	this->getPhysicsWorld()->setSubsteps(7);
	
	// va cham npc
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Map_2::onContactBegin, this);
	contactListener->onContactPreSolve = CC_CALLBACK_1(Map_2::onContactPreSolve, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(Map_2::onContactSeparate, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
	//end va cham npc
	
	menuLayer = new MenuLayer(this->mainPlayer);
	this->addChild(menuLayer, 2);
	return true;
}

void Map_2::update(float deltaTime)
{
	mainPlayer->Update(deltaTime);
	menuLayer->update(deltaTime);
	this->getDefaultCamera()->setPosition(mainPlayer->m_sprite->getPosition());
	airan->Collision(mainPlayer, deltaTime);
	bossLv3->Collision(mainPlayer, deltaTime);
	times2 += deltaTime;
//	boss->Collision(mainPlayer, deltaTime);
	for (int i = 0; i < ai.size(); i++) {
		ai[i]->Collision(mainPlayer, deltaTime);

	}
	if (x2 == 2) {
		menuLayer->setD(mainPlayer->CountCreep);
	}
	if (x2 == 4) {
		
		menuLayer->setC(mainPlayer->CountCreep);
	}
}
bool Map_2::onTouchBegan(Touch* touch, Event* event)
{
	return true;
}
bool Map_2::onTouchEnded(Touch* touch, Event* event)
{
	return true;
}
bool Map_2::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
	return false;
}
void Map_2::addMap()
{
	map = TMXTiledMap::create("map2/map2.tmx");
	map->setAnchorPoint(Vec2(0, 0));
	map->setPosition(Vec2(0, 0));
	MapBackGround = TMXTiledMap::create("map2/BackGroundMap2.tmx");
	//physic map
	mObjectGroup = map->getObjectGroup("colision");
	mObjectGroup1 = map->getObjectGroup("event");
	addChild(map,20);
	addChild(MapBackGround);
	

}
float Map_2::Distance(Vec2 A, Vec2 C) {
	return std::sqrt((A.x - C.x) * (A.x - C.x) + (A.y - C.y) * (A.y - C.y));
}
void Map_2::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (times2 > 2.0f && keyCode == EventKeyboard::KeyCode::KEY_SPACE) {
		times2 = 0;
		mainPlayer->SetState(mainPlayer->ACTION_ATTACK);
	}
	if (Distance(mainPlayer->m_sprite->getPosition(), mainPlayer->m_sprite->getPosition()) < 100.0f)
	{
		mainPlayer->SetState(mainPlayer->ACTION_ATTACK);
	}
}
//nhan

bool Map_2::onContactBegin(const PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA && nodeB)
	{
		if (nodeA->getTag() == playertag & nodeB->getTag() == NpcFroztag || nodeB->getTag() == playertag & nodeA->getTag() == NpcFroztag)
		{
			npcFroz->CollisionFroz();

		}
		else if (nodeA->getTag() == playertag & nodeB->getTag() == NpcIcetag || nodeB->getTag() == playertag & nodeA->getTag() == NpcIcetag)
		{
			
			npcIce->CollisionIce();
		}
		else if (nodeA->getTag() == playertag & nodeB->getTag() == NpcWilchtag || nodeB->getTag() == playertag & nodeA->getTag() == NpcWilchtag)
		{
			npcWilch->CollisionWilch();
		}

	}
	return true;

}

bool Map_2::onContactPreSolve(const PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA && nodeB)
	{
	}

	return true;
}

bool Map_2::onContactSeparate(const PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA && nodeB)
	{
	}

	return true;
}


void Map_2::createPhysicMap()
{
	// set physics map
	auto objects = mObjectGroup->getObjects();
	for (int i = 0; i < objects.size(); i++)
	{
		auto object = objects.at(i);
		auto properties = object.asValueMap();
		float posx2 = properties.at("x").asFloat();
		float posY = properties.at("y").asFloat();
		int type = object.asValueMap().at("type").asInt();
		if (type == 1)
		{

			auto physics = PhysicsBody::createBox(Size(properties.at("width").asFloat(), properties.at("height").asFloat()), PhysicsMaterial(1.0f, 0.0f, 0));
			physics->setDynamic(false);
			physics->setCollisionBitmask(Model::BITMASK_GROUND);
			physics->setContactTestBitmask(true);
			auto x2 = properties.at("width").asFloat() / 2 + posx2;
			auto y = properties.at("height").asFloat() / 2 + posY;
			auto node = Node::create();
			node->setPosition(Vec2(x2, y));
			this->addChild(node);
			node->setPhysicsBody(physics);
		}
		if (type == 2)
		{

			auto edgeBody = PhysicsBody::createEdgeBox(Size(properties.at("width").asFloat(), properties.at("height").asFloat()), PhysicsMaterial(1.0f, 0.0f, 0));
			auto edgeNode = Node::create();
			edgeNode->setPosition(Vec2(properties.at("width").asFloat() / 2 + posx2, properties.at("height").asFloat() / 2 + posY));
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
		float posx2 = properties.at("x").asFloat();
		float posY = properties.at("y").asFloat();
		int type = object1.asValueMap().at("type").asInt();
		if (type == 2)
		{
			//
			mainPlayer = new Player(this);
			mainPlayer->m_sprite->setPosition(Vec2(posx2, posY));
			airan = new AiRange(this);
			airan->m_sprite->setPosition(Vec2(posx2 - 100, posY - 100));
			bossLv3 = new BossLv3(this);
			bossLv3->m_sprite->setPosition(Vec2(posx2 - 200, posY + 100));

		}
		if (type == 3)
		{
			//npc froz
			npcFroz = new Npclv1(this);
			npcFroz->Init();
			npcFroz->m_sprite->setTag(NpcFroztag);
			npcFroz->m_sprite->runAction(npcFroz->CommunicationNPCFroz());
			npcFroz->m_sprite->setPosition(Vec2(posx2, posY));
		}
		if (type == 4)
		{
			//
			npcIce = new Npclv1(this);
			npcIce->Init();
			npcIce->m_sprite->setTag(NpcIcetag);
			npcIce->m_sprite->runAction(npcIce->CommunicationNPCIce());
			npcIce->m_sprite->setPosition(Vec2(posx2, posY));
		}
		if (type == 5)
		{
			//
			npcWilch = new Npclv1(this);
			npcWilch->Init();
			npcWilch->m_sprite->setTag(NpcWilchtag);
			npcWilch->m_sprite->runAction(npcWilch->CommunicationNPCWilch());
			npcWilch->m_sprite->setPosition(Vec2(posx2, posY));

		}

		if (type == 1)
		{
			AiLv1* ailv = new AiLv1(this);
			ailv->m_sprite->setTag(AILV1+i);
			ailv->m_sprite->setPosition(Vec2(posx2, posY));
			ai.push_back(ailv);
		}
	}
}


//end nhan