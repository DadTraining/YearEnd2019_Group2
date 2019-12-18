#include "MapTutorialScene.h"

USING_NS_CC;
using namespace std;

Scene* MapTutorialScene::createScene()
{
    return MapTutorialScene::create();
}

bool MapTutorialScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	addMap();
	aiLv1 = new Player(this);
	aiLv1->Init();
	aiLv1->m_sprite->runAction(aiLv1->Attack());	
    return true;
}
void MapTutorialScene::update(FLOAT deltaTime)
{
}
void MapTutorialScene::addMap()
{
	auto map = TMXTiledMap::create("Map1/map1.tmx");
	map->setAnchorPoint(Vec2(0, 0));
	map->setScale(0.45);
	map->setPosition(Vec2(0, 0));
	addChild(map);

}
