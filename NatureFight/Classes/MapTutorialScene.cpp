#include "MapTutorialScene.h"

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
	this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	addMap();
	npcsolo = new Npclv1(this);
	npcsolo->Init();
	npcsolo->m_sprite->runAction(npcsolo->Communication());
	aiLv1 = new AiLv1(this);
	aiLv1->Init();
	aiLv1->m_sprite->runAction(aiLv1->Attack());	
	scheduleUpdate();
    return true;
}
void MapTutorialScene::update(FLOAT deltaTime)
{

	
	npcsolo->Update(deltaTime);
	npcsolo->Collision();
}
void MapTutorialScene::addMap()
{
	auto map = TMXTiledMap::create("Map1/map1.tmx");
	map->setAnchorPoint(Vec2(0, 0));
	map->setScale(0.45);
	map->setPosition(Vec2(0, 0));
	addChild(map);

}
