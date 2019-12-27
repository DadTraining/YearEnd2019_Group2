#include "GamePlayScene.h"
#include <ResourceManager.h>
#include <Bullet.h>
#include "Object.h"
using namespace std;

Scene* GamePlayScene::createScene()
{
	return GamePlayScene::create();
}
bool GamePlayScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	scheduleUpdate();
	//get spire and animation
	auto spriteCache = SpriteFrameCache::getInstance();
	spriteCache->addSpriteFramesWithFile("Sprites/SpaceShip/ship.plist");
	auto spriteFrame = spriteCache->getSpriteFrameByName("1.png");
	m_spaceShip = new SpaceShooter(this);
	m_spaceShip->m_sprite = Sprite::createWithSpriteFrame(spriteFrame);
	m_spaceShip->m_sprite->setPosition(50, 50);
	addChild(m_spaceShip->m_sprite);
	Vector<SpriteFrame*> animFrames;
	animFrames.pushBack(spriteCache->getSpriteFrameByName("1.png"));
	animFrames.pushBack(spriteCache->getSpriteFrameByName("2.png"));
	animFrames.pushBack(spriteCache->getSpriteFrameByName("3.png"));
	animFrames.pushBack(spriteCache->getSpriteFrameByName("4.png"));
	animFrames.pushBack(spriteCache->getSpriteFrameByName("5.png"));
	animFrames.pushBack(spriteCache->getSpriteFrameByName("6.png"));
	animFrames.pushBack(spriteCache->getSpriteFrameByName("7.png"));

	//animation
	auto animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
	auto animate = Animate::create(animation);

	//ship animation
	m_spaceShip->m_sprite->runAction(RepeatForever::create(animate));
	// end animation
	//sign touch
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GamePlayScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GamePlayScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GamePlayScene::onTouchEnded, this);
	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(GamePlayScene::onKeyPressed, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(GamePlayScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

	//get background
	auto spritesBackground = ResourceManager::GetInstance()->GetSpriteById(1);
	spritesBackground->setPosition(160,240);
	spritesBackground->removeFromParent();
	addChild(spritesBackground, -1);
	return true;
}
bool GamePlayScene::onTouchBegan(Touch* touch, Event* event)
{
	Vec2 shipPos = touch->getLocation();
	auto moveTo = MoveTo::create(1.0f, shipPos);
	m_spaceShip->m_sprite->runAction(moveTo);
	return true;
}
void GamePlayScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	auto moveBy = MoveBy::create(1.0f, Vec2(0, 0));
	auto repeatForever = cocos2d::RepeatForever::create(moveBy);

	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		moveBy = MoveBy::create(1.0f, Vec2(-100, 0));
		repeatForever = cocos2d::RepeatForever::create(moveBy);
		repeatForever->setTag(999);
		m_spaceShip->m_sprite->runAction(repeatForever);
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		moveBy = MoveBy::create(1.0f, Vec2(100, 0));
		repeatForever = cocos2d::RepeatForever::create(moveBy);
		repeatForever->setTag(999);
		m_spaceShip->m_sprite->runAction(repeatForever);
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		moveBy = MoveBy::create(1.0f, Vec2(0, 100));
		repeatForever = cocos2d::RepeatForever::create(moveBy);
		repeatForever->setTag(999);
		m_spaceShip->m_sprite->runAction(repeatForever);
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		moveBy = MoveBy::create(1.0f, Vec2(0, -100));
		repeatForever = cocos2d::RepeatForever::create(moveBy);
		repeatForever->setTag(999);
		m_spaceShip->m_sprite->runAction(repeatForever);
	}

}
void GamePlayScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	m_spaceShip->m_sprite->stopActionByTag(999);

}
void GamePlayScene::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{

}

bool GamePlayScene::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
	return true;
}

int countTime = 0;
int rockTime = 0;
void GamePlayScene::update(FLOAT deltaTime)
{

	if (countTime == 20)
	{
		m_spaceShip->Shoot();
		auto bulletInList = this->m_spaceShip->m_bullet.back()->m_sprite;
		addChild(bulletInList);
		
		countTime=0;
	}
	else
	{
		countTime++;
	}
	m_spaceShip->Collision(m_rocks);
	if (rockTime == 100) {
		GenerateRock();
		rockTime = 0;
	}
	else
	{
		rockTime++;
	}
}

void GamePlayScene::GenerateRock()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	int x = cocos2d::RandomHelper::random_int(0, (int)(origin.x + visibleSize.width));
	if(m_rocks.size()<10){
		Rock* rock = new Rock(this);
		m_rocks.push_back(rock);
		rock->m_sprite->setPosition(x, origin.y + visibleSize.height);
		this->addChild(rock->m_sprite);
	}
}
