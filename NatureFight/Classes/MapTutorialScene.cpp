#include "MapTutorialScene.h"
#define ATTACK 0
#define RUN 1
#define playertag 1000
#define NpcSolotag 11
#define NpcYolotag 12
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

	this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	addMap();
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
	// Goblin ai
	aiLv1 = new AiLv1(this);
	aiLv1->Init();
	aiLv1->m_sprite->runAction(aiLv1->Moving());
	aiLv1->physicsBody->setVelocity(Vec2(10, 0));
	//set velociy and auto move
	float delay = 4.0f;
	this->schedule(schedule_selector(MapTutorialScene::autoMove), delay);
	scheduleUpdate();
	schedule(schedule_selector(MapTutorialScene::update));
	addMap();
	mainPlayer = new Player(this);
	mainPlayer->Init();
	mainPlayer->m_sprite->runAction(mainPlayer->IdleRight());
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
				mainPlayer->m_sprite->runAction(mainPlayer->AttackRight());
			}

			break;
		case ui::Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
	});

	addChild(ButtonAttack);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(MapTutorialScene::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	Quest(); // Button display quest
	

    return true;
}
//goblin
int reset = 1;
bool auMove = false;
void MapTutorialScene::autoMove(float dt) {
	if (auMove) {
		auto velo = Vec2(50 * reset, 0);
		aiLv1->physicsBody->setVelocity(velo);
		reset *= (-1);

	}
};

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
	mainPlayer->m_sprite->stopAllActions();
	mainPlayer->m_sprite->runAction(mainPlayer->IdleRight());
	mainPlayer->physicsBody->setVelocity(Vec2(0,0));
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
		mainPlayer->m_sprite->setFlipX(true);
		faceRight = !faceRight;
	}
	if (touch->getLocation().x > 120 && faceRight==false) {
		mainPlayer->m_sprite->setFlipX(false);
		faceRight = !faceRight;
	}
	if (Distance(Vec2(120, 100), touch->getLocation()) > 100) {
		MoveJoyStick = Vec2(120, 100);
	}
	auto mt = MoveTo::create(0, MoveJoyStick);
	JoyStick->runAction(mt);
	mainPlayer->m_sprite->stopAllActions();
	mainPlayer->m_sprite->runAction(mainPlayer->MovingRight());
	mainPlayer->physicsBody->setVelocity((MoveJoyStick - Vec2(120, 100))*2.5f);
	return false;

}
void MapTutorialScene::addMap()
{
	auto map = TMXTiledMap::create("Map1/map1.tmx");
	map->setAnchorPoint(Vec2(0, 0));
	map->setScale(0.7);
	map->setPosition(Vec2(0, 0));
	addChild(map);
}
float MapTutorialScene::Distance(Vec2 A, Vec2 C) {
	return std::sqrt((A.x - C.x) * (A.x - C.x) + (A.y - C.y) * (A.y - C.y));
}
int questYolo = 0,questSolo;
int c = -1, d = -1;
bool MapTutorialScene::onContactBegin(const PhysicsContact & contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA && nodeB)
	{
		if (nodeA->getTag() == playertag&nodeB->getTag()== NpcSolotag|| nodeB->getTag() == playertag&nodeA->getTag() == NpcSolotag)
		{
			questSolo = 2;
			npcsolo->Collision();
			c+=1;
			
		}	
		if (nodeA->getTag() == playertag&nodeB->getTag() == NpcYolotag || nodeB->getTag() == playertag&nodeA->getTag() == NpcYolotag)
		{
			npcYolo->Collision1();
			questYolo = 1;
			d += 1;
		}
	}
	
	return true;

}
void MapTutorialScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (times > 2.0f && keyCode == EventKeyboard::KeyCode::KEY_SPACE) {
		times = 0;
		mainPlayer->m_sprite->runAction(mainPlayer->AttackRight());
	}
}
Sprite* quest;
Label* label1,*label2;
int count1 = 0;
vector<Label*> vlabel, vlabel1;
void MapTutorialScene::Quest()
{
	quest = Sprite::create("frames/paused2.png");
	quest->setPosition(600, 400);
	quest->setScale(0.2);
	quest->setAnchorPoint(Point(0.0f, 1.0f));
	addChild(quest, 80);
	quest->setOpacity(0);
	//
	//Quest 1 of Yolo
	for (int i = 0; i < 4; i++)
	{
		label1 = Label::createWithSystemFont("Danh 3 con quai Goblin ("+std::to_string(i)+" / 3)", "Arial", 16);
		label1->setAnchorPoint(Vec2(0, 1));
		label1->setPositionX(quest->getPositionX() + 20);
		label1->setPositionY(quest->getPositionY() - 20);
		label1->setTextColor(Color4B::BLACK);
		label1->setVisible(false);
		this->addChild(label1, 97+i);
		vlabel1.push_back(label1);
	}
	//Quest 2 of Solo
	
	for (int i = 0; i <=6; i++)
	{
		label2 = Label::createWithSystemFont("Danh 6 con quai Goblin (" + std::to_string(i) + " / 6)", "Arial", 16);
		label2->setAnchorPoint(Vec2(0, 1));
		label2->setPositionX(quest->getPositionX() + 20);
		label2->setPositionY(label1->getPositionY() - 30);
		label2->setTextColor(Color4B::BLACK);
		label2->setVisible(false);
		this->addChild(label2, 102+i);
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
						else if (d == i && i>0) {
							vlabel1[i]->setVisible(true);
							vlabel1[i - 1]->setVisible(false);
						}
					}

					
				}
				if (questSolo == 2) {
					for (int i = 0; i < 7; i++)
					{
						if (c == 0 && i==0)
						{
							vlabel[i]->setVisible(true);
						}
						else if(c ==i && i>0) {
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
int timeCount = 0;
void MapTutorialScene::update(FLOAT deltaTime)
{
	//	npcsolo->Update(deltaTime);
	//npcsolo->Collision();
	times += deltaTime;
	// goblin
	aiLv1->Update(deltaTime);
	if (timeCount == 300) {
		aiLv1->m_sprite->stopActionByTag(RUN);
		aiLv1->m_sprite->runAction(aiLv1->Attack());
	}
	else if (timeCount == 600)
	{
		aiLv1->m_sprite->stopActionByTag(ATTACK);
		aiLv1->m_sprite->runAction(aiLv1->Moving());
		aiLv1->physicsBody->setVelocity(Vec2(10, 0));
	}
	else if (timeCount >= 1000)
	{
		auMove = true;
	}
	timeCount++;

}