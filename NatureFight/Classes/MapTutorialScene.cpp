#include "MapTutorialScene.h"
#define ATTACK 0
#define RUN 1
USING_NS_CC;
using namespace std;

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
	// show box physicbody
	this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);	
	schedule(schedule_selector(MapTutorialScene::update));
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	addMap();
	aiLv1 = new AiLv1(this);
	aiLv1->Init();
	aiLv1->m_sprite->runAction(aiLv1->Moving());
	aiLv1->physicsBody->setVelocity(Vec2(10, 0));
	//set velociy and auto move
	float delay = 4.0f;
	this->schedule(schedule_selector(MapTutorialScene::autoMove), delay);
    return true;
}
int reset = 1;
bool auMove=false;
void MapTutorialScene::autoMove(float dt) {
	if (auMove) {
		auto velo = Vec2(50 * reset, 0);
		aiLv1->physicsBody->setVelocity(velo);
		reset *= (-1);

	}
};
int timeCount = 0;
void MapTutorialScene::update(FLOAT deltaTime)
{
		aiLv1->Update(deltaTime);
		if (timeCount == 300) {
			aiLv1->m_sprite->stopActionByTag(RUN);
			aiLv1->m_sprite->runAction(aiLv1->Attack());
		}else if (timeCount==600)
		{
			aiLv1->m_sprite->stopActionByTag(ATTACK);
			aiLv1->m_sprite->runAction(aiLv1->Moving());
			aiLv1->physicsBody->setVelocity(Vec2(10, 0));
		}else if (timeCount>=1000)
		{
			auMove = true;
		}
			timeCount++;
}
void MapTutorialScene::addMap()
{
	auto map = TMXTiledMap::create("Map1/map1.tmx");
	map->setAnchorPoint(Vec2(0, 0));
	map->setScale(0.45);
	map->setPosition(Vec2(0, 0));
	addChild(map);

}
