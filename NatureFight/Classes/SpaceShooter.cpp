#include "SpaceShooter.h"
#include <Bullet.h>
#include <ResourceManager.h>
#include <GameOverScene.h>
#include <GamePlayScene.h>

SpaceShooter::SpaceShooter(cocos2d::Scene* scene)
{
	sceneGame = scene;
}

SpaceShooter::~SpaceShooter()
{
}

void SpaceShooter::Init()
{
}

void SpaceShooter::Update(float deltaTime)
{
}

void SpaceShooter::Shoot()
{
	Bullet* bullet = new Bullet(sceneGame);
	cocos2d::Vec2 posShip = this->m_sprite->getPosition();
	bullet->m_sprite->setPosition(posShip);
	m_bullet.push_back(bullet);
}
int point = 0;
void SpaceShooter::Collision(std::vector<Rock*> rocks)
{
	auto Size = cocos2d::Director::getInstance()->getVisibleSize();

	cocos2d::Vec2 originVis = cocos2d::Director::getInstance()->getVisibleOrigin();

	for (std::vector<Rock*>::iterator it = rocks.begin(); it != rocks.end(); ++it) {

		if (m_sprite->getBoundingBox().containsPoint((*it)->m_sprite->getPosition()))
		{
			//game over
			auto scene = GameOverScene::createScene();
			Director::getInstance()->replaceScene(scene);
			point++;
		}
		else {
			for (std::list<Object*>::iterator bullet = m_bullet.begin(); bullet != m_bullet.end(); ++bullet) {
				if ((*it)->m_sprite->getBoundingBox().containsPoint((*bullet)->m_sprite->getPosition()) || (*it)->m_sprite->getPosition().y <= 0)
				{
					if ((*it)->m_sprite->getPosition().y > 0||(*bullet)->m_sprite->getPosition().y>500) {

						auto spriteCache = SpriteFrameCache::getInstance();
						spriteCache->addSpriteFramesWithFile("Sprites/Blue/sprites.plist");
						auto spriteFrame = spriteCache->getSpriteFrameByName("ex0.png");
						auto exPlosion = Sprite::createWithSpriteFrame(spriteFrame);
						exPlosion->setPosition((*it)->m_sprite->getPosition());
						sceneGame->addChild(exPlosion);
						Vector<SpriteFrame*> exFrames;
						for (int i = 1; i <= 16; i++) {
							std::string name = "0" + std::to_string(i) + ".png";
							spriteFrame = spriteCache->getSpriteFrameByName(name);
							exFrames.pushBack(spriteFrame);
						}
						auto animation = Animation::createWithSpriteFrames(exFrames, 0.1f);
						auto animate = Animate::create(animation);
						exPlosion->runAction(animate);
						(*bullet)->m_sprite->removeFromParent();
						delete (*bullet);
						m_bullet.remove((*bullet));
						bullet = m_bullet.begin();

					}
					int xM = cocos2d::RandomHelper::random_int(-300, 300);
					auto move = cocos2d::MoveBy::create(3, Vec2(-xM, -480));
					//set move
					(*it)->m_sprite->stopAllActions();
					int x = cocos2d::RandomHelper::random_int(0, (int)(originVis.x + Size.width));
					(*it)->m_sprite->setPosition(x, originVis.y + Size.height);
					(*it)->m_sprite->runAction(move);
					if (m_bullet.size() == 0) {
						break;
					}

				}
			}
		}
	}
}
