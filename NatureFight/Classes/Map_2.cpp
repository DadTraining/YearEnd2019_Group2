#include "Map_2.h"

using namespace std;
float times2 = 0;
int x2 = 1;//nhan


Scene* Map_2::createScene()
{
	x2 = 1;
    return Map_2::create();
}

bool Map_2::init()
{
    if ( !Scene::initWithPhysics() )
    {
        return false;
    }
	gate = false;
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
	menuLayer->getIcon_Ice()->setEnabled(true);
	
	//gate -> MapBossMan2
	createMoveScene();

	return true;
}

void Map_2::update(float deltaTime)
{
	mainPlayer->Update(deltaTime);
	menuLayer->update(deltaTime);
	this->getDefaultCamera()->setPosition(mainPlayer->m_sprite->getPosition());
	times2 += deltaTime;
//	boss->Collision(mainPlayer, deltaTime);
	for (int i = 0; i < ai.size(); i++) {
		ai[i]->Collision(mainPlayer, deltaTime);
	}
	for (int i = 0; i < aiRange.size(); i++) {
		aiRange[i]->Collision(mainPlayer, deltaTime);
	}
	if (x2 == 3) {
		menuLayer->setC(mainPlayer->CountCreep);
	}
	if (isCreepDie()) {
		if (times >= 4) {
			ai.clear();
			aiRange.clear();
			createCreepScene();
		}
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
	MapBackGround->setScale(1.6);
	MapBackGround->setAnchorPoint(Vec2(0.2,0.2));
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
			if (x2 == 1) {
				npcFroz->CollisionFroz();
				
				mainPlayer->haveSwordIce = true;
				x2 += 1;
			}
		}
		else if (nodeA->getTag() == playertag & nodeB->getTag() == NpcIcetag || nodeB->getTag() == playertag & nodeA->getTag() == NpcIcetag)
		{
			if (x2 == 2) {
				npcIce->CollisionIce();
				mainPlayer->CountCreep = 0;
				menuLayer->setQuestMan2(2);
				x2 += 1;
			}
			if (x2 == 3) {
				if (mainPlayer->CountCreep == 10)
				{
					menuLayer->showItemSword(mainPlayer->m_sprite->getPosition(), "Sprites/Item/KiemBang.png");
					mainPlayer->haveFireStone = true;
					x2 += 1;
				}
			}
		}
		else if (nodeA->getTag() == playertag & nodeB->getTag() == NpcWilchtag || nodeB->getTag() == playertag & nodeA->getTag() == NpcWilchtag)
		{
			if (x2 == 4) {
				npcWilch->CollisionWilch();
				mainPlayer->haveFirePet = true;
				gate = true;
				x2 += 1;
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
			if (gate == true) {
				auto def = UserDefault::sharedUserDefault();
				def->setIntegerForKey("Level", mainPlayer->Level);
				def->setIntegerForKey("Exp", mainPlayer->Exp);
				def->setBoolForKey("haveSwordIce", mainPlayer->haveSwordIce);
				def->setBoolForKey("haveIceShield", mainPlayer->haveIceShield);

				Director::getInstance()->replaceScene(MapBossMan2Scene::createScene());
			}
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
			AiLv2* ailv = new AiLv2(this);
			ailv->m_sprite->setTag(AILV2+i);
			ailv->m_sprite->setPosition(Vec2(posx2, posY));
			ai.push_back(ailv);
		}
		if (type == 6)
		{
			AiRange* ailv = new AiRange(this);
			ailv->m_sprite->setPosition(Vec2(posx2, posY));
			ailv->m_sprite->setTag(AIRANGE+i);
			aiRange.push_back(ailv);
			
		}
	}
}


//end nhan

cocos2d::ParticleSystemQuad* Map_2::Particletele(std::string name)
{
	auto particleSystem = ParticleSystemQuad::create(name);
	particleSystem->setScale(0.6f);
	return particleSystem;
}
bool Map_2::isCreepDie()
{
	for (int i = 0; i < ai.size(); i++)
	{
		for (int j = 0; j < aiRange.size(); j++)
		{
			if (aiRange[j]->m_sprite->isVisible()) return false;
		}
		if (ai[i]->m_sprite->isVisible() == true) return false;
	}
	return true;
}
void Map_2::createMoveScene()
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

void Map_2::createCreepScene()
{
	auto objects1 = mObjectGroup1->getObjects();
	for (int i = 0; i < objects1.size(); i++)
	{
		auto object1 = objects1.at(i);
		auto properties = object1.asValueMap();
		float posx2 = properties.at("x").asFloat();
		float posY = properties.at("y").asFloat();
		int type = object1.asValueMap().at("type").asInt();
			if (type == 1)
			{
				AiLv2* ailv = new AiLv2(this);
				ailv->m_sprite->setTag(AILV2 + i);
				ailv->m_sprite->setPosition(Vec2(posx2, posY));
				ai.push_back(ailv);
			}
			if (type == 6)
			{
				AiRange* ailv = new AiRange(this);
				ailv->m_sprite->setPosition(Vec2(posx2, posY));
				ailv->m_sprite->setTag(AIRANGE + i);
				aiRange.push_back(ailv);

			}
		
	}
}