#ifndef _BULLET_H_
#define _BULLET_H_

#include "Model.h"
#include "ResourceManager.h"
#include "cocos2d.h"
#include <Player.h>
#define SCREEN_W 912
#define SCREEN_H 432
class Bullet : public Model
{

public:
	bool stateBulletFollow;
public:
	Bullet(cocos2d::Scene* scene, cocos2d::Sprite* sprite, int owner, std::string nameAction, int idAction,bool stateFolow);
	~Bullet();


	void update(float deltaTime, Player* player);
	RepeatForever* AnimationObjectRepeat(int id, std::string name, float speed);
};
#endif