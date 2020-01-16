#ifndef _BOOM_H_
#define _BOOM_H_

#include "Model.h"
#include "cocos2d.h"
#include <Player.h>
#define SCREEN_W 912
#define SCREEN_H 432
#define BoomEx 100
class Boom : public Model
{
private:
	const int RUN_STEP = 20;
public:
	bool CurExplosionState;
	cocos2d::Node* explotion;
public:
	Boom(cocos2d::Scene* scene, cocos2d::Sprite* sprite, int owner);
	~Boom();

	void SetExplo(bool); 

	void update(float deltaTime);
	Animate* Explosion();
	Animate* defautBombAction(int id, float speed);
	Animate* AnimationObjectOnce(int id, std::string name, float speed);
	
};
#endif