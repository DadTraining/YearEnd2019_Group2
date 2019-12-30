#include "MapTutorialScene.h"

USING_NS_CC;
#define ATTACK 0
#define RUN 1
#define playertag 1000
#define NpcSolotag 11
#define NpcYolotag 12
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
	addMap();
	//npc zolo
	npcsolo = new Npclv1(this);
	npcsolo->Init();
	npcsolo->m_sprite->setTag(NpcSolotag);
	npcsolo->m_sprite->runAction(npcsolo->Communication());
	//
	npcYolo = new Npclv1(this);
	npcYolo->Init();
	npcYolo->m_sprite->setPosition(Point(visibleSize.width / 2 + 350, visibleSize.height / 2 - 50));
	npcYolo->m_sprite->setTag(NpcYolotag);
	npcYolo->m_sprite->runAction(npcYolo->CommunicationNPCYolo());

	// end  npc

	mainPlayer = new Player(this);
	mainPlayer->Init();
	mainPlayer->m_sprite->runAction(mainPlayer->IdleRight());	
	
	ailv1 = new AiLv1(this);
	ailv1->Init();
	ailv1->m_sprite->runAction(ailv1->MovingRight());

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(MapTutorialScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(MapTutorialScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(MapTutorialScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	

	auto listenerKey = EventListenerKeyboard::create();
	listenerKey->onKeyPressed = CC_CALLBACK_2(MapTutorialScene::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKey, this);

	/*ailv1 = new AiLv1(this);
	ailv1->Init();
	ailv1->m_sprite->runAction(ailv1->MovingRight());*/
	this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	

	auto edgeBody = PhysicsBody::createEdgeBox(visibleSize);
	auto edgeNode = Node::create();
	edgeNode->setPosition(visibleSize/2);
	addChild(edgeNode);
	edgeNode->setPhysicsBody(edgeBody);
	// va cham npc
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(MapTutorialScene::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	Quest(); // Button display quest
	//createPhysicMap();
	//end va cham npc
	menuLayer = new MenuLayer(this->mainPlayer);
	this->addChild(menuLayer, 2);
	return true;
}
void MapTutorialScene::update(float deltaTime)
{
	mainPlayer->Update(deltaTime);
	menuLayer->update();
	this->getDefaultCamera()->setPosition(mainPlayer->m_sprite->getPosition());
	times += deltaTime;

	ailv1->physicsBody1->setVelocity(mainPlayer->physicsBody->getVelocity());
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
	map->setScale(0.7);
	map->setPosition(Vec2(0, 0));
	//physic map
	//mPhysicsLayer = map->getLayer("item_3");
	//mPhysicsLayer->setVisible(true);
	//mPhysicsLayer2 = map->getLayer("land_2");
	//mPhysicsLayer2->setVisible(true);
	//mPhysicsLayer1 = map->getLayer("item_1");
	//mPhysicsLayer1->setVisible(true);
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
//void MapTutorialScene::createPhysicMap()
//{
//	auto visibleSize = Director::getInstance()->getVisibleSize();
//	Vec2 origin = Director::getInstance()->getVisibleOrigin();
//	auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
//	edgeBody->setCollisionBitmask(1);
//	edgeBody->setContactTestBitmask(1);
//
//	auto edgeNode = Node::create();
//	edgeNode->setPosition(visibleSize.width / 2, visibleSize.height / 2);
//	edgeNode->setPhysicsBody(edgeBody);
//	addChild(edgeNode);
//
//
//	Size layerSize = mPhysicsLayer->getLayerSize();
//	for (int i = 0; i < layerSize.width; i++)
//	{
//		for (int j = 0; j < layerSize.height; j++)
//		{
//			auto tileSet = mPhysicsLayer->getTileAt(Vec2(i, j));
//			if (tileSet != NULL)
//			{
//				auto physics = PhysicsBody::createBox(tileSet->getContentSize(), PhysicsMaterial(1.0f, 0.0f, 1.0f));
//				physics->setCollisionBitmask(4);
//				physics->setContactTestBitmask(true);
//				physics->setDynamic(false);
//				//physics->setMass(100);
//				tileSet->setPhysicsBody(physics);
//
//			}
//		}
//	}
//	/*Size layerSize1 = mPhysicsLayer1->getLayerSize();
//	for (int i = 0; i < layerSize1.width; i++)
//	{
//		for (int j = 0; j < layerSize1.height; j++)
//		{
//			auto tileSet = mPhysicsLayer1->getTileAt(Vec2(i, j));
//			if (tileSet != NULL)
//			{
//				auto physics = PhysicsBody::createBox(tileSet->getContentSize(), PhysicsMaterial(1.0f, 0.0f, 1.0f));
//				physics->setCollisionBitmask(5);
//				physics->setContactTestBitmask(true);
//				physics->setDynamic(false);
//				physics->setMass(101);
//				tileSet->setPhysicsBody(physics);
//
//			}
//		}
//	}*/
//
//	Size layerSize2 = mPhysicsLayer2->getLayerSize();
//	for (int i = 0; i < layerSize2.width; i++)
//	{
//		for (int j = 0; j < layerSize2.height; j++)
//		{
//			auto tileSet = mPhysicsLayer2->getTileAt(Vec2(i, j));
//			if (tileSet != NULL)
//			{
//				auto physics = PhysicsBody::createBox(tileSet->getContentSize(), PhysicsMaterial(1.0f, 0.0f, 1.0f));
//				physics->setCollisionBitmask(6);
//				physics->setContactTestBitmask(true);
//				physics->setDynamic(false);
//				physics->setMass(102);
//				tileSet->setPhysicsBody(physics);
//
//			}
//		}
//	}
//}
//end nhan