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
	menuLayer->getIcon_Fire()->setEnabled(true);
	menuLayer->getIcon_Ice()->setEnabled(true);

	createMoveScene();
	return true;
}

void Map_3::update(float deltaTime)
{
	mainPlayer->Update(deltaTime);
	menuLayer->update(deltaTime);
	this->getDefaultCamera()->setPosition(mainPlayer->m_sprite->getPosition());
	times3 += deltaTime;
	for (int i = 0; i < ai.size(); i++) {
		ai[i]->Collision(mainPlayer, deltaTime);
	}
	if (x3 == 2) {
		menuLayer->setD(mainPlayer->CountCreep);
	}
	if (x3 == 4) {

		menuLayer->setC(mainPlayer->CountCreep);
	}
	if (isCreepDie()) {
		if (times3 >= 4) {
			ai.clear();
			createCreepScene();
		}
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
	MapBackGround->setScale(1.6);
	MapBackGround->setAnchorPoint(Vec2(0.2,0.2));
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
		if (nodeA->getTag() == playertag & nodeB->getTag() == NpcFireWilthtag || nodeB->getTag() == playertag & nodeA->getTag() == NpcFireWilthtag)
		{
			if (x3 == 3) {
				menuLayer->setQuestSolo(2);
				npcJoe->CollisionFireWilth();
				x3 += 1;
			}
			if (x3 == 4) {
				if (mainPlayer->CountCreep >= 6) {
					mainPlayer->CountCreep = 0;
					mainPlayer->haveSwordFire = true;
					menuLayer->showItemSword(mainPlayer->m_sprite->getPosition(),"Sprites/Item/KiemBang.png");
				}
			}
		}
		else if (nodeA->getTag() == playertag & nodeB->getTag() == NpcJoetag || nodeB->getTag() == playertag & nodeA->getTag() == NpcJoetag)
		{
			if (x3 == 1) {
				npcFireWilth->CollisionJoe();
				menuLayer->setQuestYolo(1);
				mainPlayer->CountCreep = 0;
				x3 += 1;
			}
			if (x3 == 2) {
				if (mainPlayer->CountCreep >= 3) {
					menuLayer->showItemSword(mainPlayer->m_sprite->getPosition(), "Sprites/Item/Lua.png");
					mainPlayer->haveIceShield = true;
					mainPlayer->CountCreep = 0;
					x3 += 1;
				}
				
			}

		}
		else if (nodeA->getTag() == CREEPATTACK & nodeB->getTag() == playertag || nodeA->getTag() == playertag & nodeB->getTag() == CREEPATTACK)
		{
			mainPlayer->m_sprite->setColor(ccc3(200, 0, 0));
			mainPlayer->SetState(Player::ACTION_HURT);
			CCLOG("mau :%d", mainPlayer->m_health);
			CCLOG(" ********* ");
		}
		else if (nodeA->getTag() == playertag & nodeB->getTag() == GATEtag || nodeB->getTag() == playertag & nodeA->getTag() == GATEtag)
		{
			Director::getInstance()->replaceScene(MapBossMan3Scene::createScene());
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
			npcFireWilth = new Npclv1(this);
			npcFireWilth->Init();
			npcFireWilth->m_sprite->setTag(NpcFireWilthtag);
			npcFireWilth->m_sprite->runAction(npcFireWilth->CommunicationNPCFireWilth());
			npcFireWilth->m_sprite->setPosition(Vec2(posx3, posY));
		}
		if (type == 4)
		{
			//
			npcJoe = new Npclv1(this);
			npcJoe->Init();
			npcJoe->m_sprite->setTag(NpcJoetag);
			npcJoe->m_sprite->runAction(npcJoe->CommunicationNPCJoe());
			npcJoe->m_sprite->setPosition(Vec2(posx3, posY));
		}
		if (type == 1)
		{
			AiLv1* ailv = new AiLv1(this);
			ailv->m_sprite->setTag(AILV1+i);
			ailv->m_sprite->setPosition(Vec2(posx3, posY));
			ai.push_back(ailv);
		}
		if (type == 5)
		{
			/*bosslv3 = new BossLv3(this);
			bosslv3->m_sprite->setPosition(Vec2(posx3, posY));*/
		}
	}
}


//end nhan

cocos2d::ParticleSystemQuad* Map_3::Particletele(std::string name)
{
	auto particleSystem = ParticleSystemQuad::create(name);
	particleSystem->setScale(0.6f);
	return particleSystem;
}

void Map_3::createMoveScene()
{
	auto objects = mObjectGroup->getObjects();
	for (int i = 0; i < objects.size(); i++)
	{
		auto object = objects.at(i);
		auto properties = object.asValueMap();
		float posX = properties.at("x").asFloat();
		float posY = properties.at("y").asFloat();
		int type = object.asValueMap().at("type").asInt();
		if (object.asValueMap().at("type").asInt() == 5)
		{
			auto particleSystem = Particletele("Particles/partic.plist");
			particleSystem->setPosition(Vec2(posX, posY));
			this->addChild(particleSystem);

			auto physics = PhysicsBody::createBox(particleSystem->getContentSize(), PhysicsMaterial(1.0f, 0.0f, 0));
			physics->setDynamic(false);
			physics->setCollisionBitmask(Model::BITMASK_GROUND);
			physics->setContactTestBitmask(true);
			particleSystem->setTag(GATEtag);
			particleSystem->setPhysicsBody(physics);

			auto emitter = ParticleGalaxy::create();
			emitter->setPosition(Vec2(posX, posY));
			emitter->setScale(0.7f);
			this->addChild(emitter);
		}
	}
}
bool Map_3::isCreepDie()
{
	for (int i = 0; i < ai.size(); i++)
	{
		if (ai[i]->m_sprite->isVisible() == true) return false;
	}
	return true;
}
void Map_3::createCreepScene()
{
	auto objects1 = mObjectGroup1->getObjects();
	for (int i = 0; i < objects1.size(); i++)
	{
		auto object1 = objects1.at(i);
		auto properties = object1.asValueMap();
		float posx3 = properties.at("x").asFloat();
		float posY = properties.at("y").asFloat();
		int type = object1.asValueMap().at("type").asInt();
		if (type == 1)
		{
			AiLv1* ailv = new AiLv1(this);
			ailv->m_sprite->setTag(AILV1 + i);
			ailv->m_sprite->setPosition(Vec2(posx3, posY));
			ai.push_back(ailv);
		}

	}
}
