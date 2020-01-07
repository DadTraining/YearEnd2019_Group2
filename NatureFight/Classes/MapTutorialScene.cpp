#include "MapTutorialScene.h"

using namespace std;
float times = 0;
Sprite* quest;
Label* label1, * label2;
int count1 = 0;
vector<Label*> vlabel, vlabel1;
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
	//create map
	addMap();

	//create Physics 
	createPhysicMap();
	
	
	

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(MapTutorialScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(MapTutorialScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(MapTutorialScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	

	auto listenerKey = EventListenerKeyboard::create();
	listenerKey->onKeyPressed = CC_CALLBACK_2(MapTutorialScene::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKey, this);


	this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	this->getPhysicsWorld()->setSubsteps(7);
	
	// va cham npc
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(MapTutorialScene::onContactBegin, this);
	contactListener->onContactPreSolve = CC_CALLBACK_1(MapTutorialScene::onContactPreSolve, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(MapTutorialScene::onContactSeparate, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	Quest(); // Button display quest
	//end va cham npc

	

	
	menuLayer = new MenuLayer(this->mainPlayer);
	this->addChild(menuLayer, 2);
	return true;
}

void MapTutorialScene::update(float deltaTime)
{
	ailv1->Collision(mainPlayer,deltaTime);
	mainPlayer->Update(deltaTime);
	menuLayer->update(deltaTime);
	this->getDefaultCamera()->setPosition(mainPlayer->m_sprite->getPosition());
	times += deltaTime;
	if (Distance(mainPlayer->m_sprite->getPosition(), ailv1->m_sprite->getPosition()) < 100)
		ailv1->physicsBodyChar->setVelocity(mainPlayer->m_sprite->getPosition() - ailv1->m_sprite->getPosition());
	else ailv1->physicsBodyChar->setVelocity(Vec2(0, 0));
	ailv1->Collision(mainPlayer,deltaTime);

	ailv1->Update(deltaTime);

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
	
	//physic map
	mObjectGroup = map->getObjectGroup("colision");
	mObjectGroup1 = map->getObjectGroup("event");
	/*mPhysicsLayer = map->getLayer("item_3");
	mPhysicsLayer->setVisible(true);
	mPhysicsLayer2 = map->getLayer("land_2");
	mPhysicsLayer2->setVisible(true);
	mPhysicsLayer1 = map->getLayer("item_1");
	mPhysicsLayer1->setVisible(true);*/
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
//nhan
int questYolo = 0, questSolo;
int c = -1, d = -1;
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
		if (nodeA->getTag() == AILV1 & nodeB->getTag() == ATTACKTAG || nodeB->getTag() == AILV1 & nodeA->getTag() == ATTACKTAG)
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
		}
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

void MapTutorialScene::Quest()
{
	quest = Sprite::create("frames/paused3.png");
	quest->setPosition(600, 400);
	quest->setScale(0.2);
	quest->setAnchorPoint(Point(0.0f, 1.0f));
	addChild(quest, 80);
	quest->setOpacity(0);
	//
	//Quest 1 of Yolo
	for (int i = 0; i < 4; i++)
	{
		label1 = Label::createWithSystemFont("Danh 3 con quai Goblin (" + std::to_string(i) + " / 3)", "Arial", 16);
		label1->setAnchorPoint(Vec2(0, 1));
		label1->setPositionX(quest->getPositionX() + 20);
		label1->setPositionY(quest->getPositionY() - 20);
		label1->setTextColor(Color4B::BLACK);
		label1->setVisible(false);
		this->addChild(label1, 97 + i);
		vlabel1.push_back(label1);
	}
	//Quest 2 of Solo

	for (int i = 0; i <= 6; i++)
	{
		label2 = Label::createWithSystemFont("Danh 6 con quai Goblin (" + std::to_string(i) + " / 6)", "Arial", 16);
		label2->setAnchorPoint(Vec2(0, 1));
		label2->setPositionX(quest->getPositionX() + 20);
		label2->setPositionY(label1->getPositionY() - 30);
		label2->setTextColor(Color4B::BLACK);
		label2->setVisible(false);
		this->addChild(label2, 102 + i);
		vlabel.push_back(label2);
	}


	auto button = ui::Button::create("Button/buttons/normal/records.png", "Button/buttons/click/records.png", "Button/buttons/hover/records.png");
	button->setPosition(Vec2(890, 400));
	button->setScale(0.06);
	button->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
		{
			count1 += 1;
			break;
		}

		case ui::Widget::TouchEventType::ENDED:
		{
			auto fadeIn = FadeIn::create(0.1f);
			auto fadeOut = FadeOut::create(0.1f);
			if (count1 == 1) {

				quest->runAction(fadeIn);
				if (questYolo == 1) {
					for (int i = 0; i < 4; i++)
					{
						if (d == 0 && i == 0)
						{
							vlabel1[i]->setVisible(true);
						}
						else if (d == i && i > 0) {
							vlabel1[i]->setVisible(true);
							vlabel1[i - 1]->setVisible(false);
						}
					}


				}
				if (questSolo == 2) {
					for (int i = 0; i < 7; i++)
					{
						if (c == 0 && i == 0)
						{
							vlabel[i]->setVisible(true);
						}
						else if (c == i && i > 0) {
							vlabel[i]->setVisible(true);
							vlabel[i - 1]->setVisible(false);
						}
					}

				}
			}
			else {

				quest->runAction(fadeOut);
				//label1->setVisible(false);
				for (int i = 0; i <= 6; i++)
				{

					vlabel[i]->setVisible(false);
				}
				for (int i = 0; i <= 3; i++)
				{

					vlabel1[i]->setVisible(false);
				}
				count1 = 0;
			}
			break;
		}
		default:
			break;
		}
		});
	addChild(button);

}

void MapTutorialScene::createPhysicMap()
{
	// set physics map
	auto objects = mObjectGroup->getObjects();

	for (int i = 0; i < objects.size(); i++)
	{
		auto object = objects.at(i);
		auto properties = object.asValueMap();
		float posX = properties.at("x").asFloat();
		float posY = properties.at("y").asFloat();
		int type = object.asValueMap().at("type").asInt();
		if (type == 1)
		{

			auto physics = PhysicsBody::createBox(Size(properties.at("width").asFloat(), properties.at("height").asFloat()), PhysicsMaterial(1.0f, 0.0f, 1.0f));
			physics->setDynamic(false);
			physics->setCollisionBitmask(Model::BITMASK_GROUND);
			physics->setContactTestBitmask(true);
			auto x = properties.at("width").asFloat() / 2 + posX;
			auto y = properties.at("height").asFloat() / 2 + posY;
			auto node = Node::create();
			node->setPosition(Vec2(x, y));
			this->addChild(node);
			node->setPhysicsBody(physics);
		}
		if (type == 2)
		{

			auto edgeBody = PhysicsBody::createEdgeBox(Size(properties.at("width").asFloat(), properties.at("height").asFloat()), PhysicsMaterial(1.0f, 0.0f, 1.0f));
			auto edgeNode = Node::create();
			edgeNode->setPosition(Vec2(properties.at("width").asFloat() / 2 + posX, properties.at("height").asFloat() / 2 + posY));
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
		float posX = properties.at("x").asFloat();
		float posY = properties.at("y").asFloat();
		int type = object1.asValueMap().at("type").asInt();
		if (type == 2)
		{
			//
			mainPlayer = new Player(this);
			mainPlayer->Init();
			mainPlayer->m_sprite->runAction(mainPlayer->IdleRight());
			mainPlayer->m_sprite->setPosition(Vec2(posX, posY));
		}
		if (type == 3)
		{
			//npc zolo
			npcsolo = new Npclv1(this);
			npcsolo->Init();
			npcsolo->m_sprite->setTag(NpcSolotag);
			npcsolo->m_sprite->runAction(npcsolo->Communication());
			npcsolo->m_sprite->setPosition(Vec2(posX, posY));
		}
		if (type == 4)
		{
			//
			npcYolo = new Npclv1(this);
			npcYolo->Init();
			//npcYolo->m_sprite->setPosition(Point(visibleSize.width / 2 + 350, visibleSize.height / 2 - 50));
			npcYolo->m_sprite->setTag(NpcYolotag);
			npcYolo->m_sprite->runAction(npcYolo->CommunicationNPCYolo());
			npcYolo->m_sprite->setPosition(Vec2(posX, posY));
		}
		if (type == 1)
		{
			ailv1 = new AiLv1(this);
			ailv1->Init();
			ailv1->m_sprite->runAction(ailv1->MovingRight());
			ailv1->m_sprite->setTag(AILV1);
			ailv1->m_sprite->setPosition(Vec2(posX, posY));
		}
	}
}


//end nhan