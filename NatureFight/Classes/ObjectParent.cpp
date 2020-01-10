#include "ObjectParent.h"

ObjectParent::ObjectParent()
{
}

ObjectParent::~ObjectParent()
{
}

cocos2d::RepeatForever* ObjectParent::AnimationObjectRepeat(int id, std::string name, float speed)
{
	auto spriteCache = ResourceManager::GetInstance()->GetFrameById(id);
	cocos2d::Vector<cocos2d::SpriteFrame*> exFrames;
	int i = 0;
	std::string link;
	while (true) {
		link = "0_" + name + "_00" + std::to_string(i) + ".png";
		if (i >= 10) link = "0_" + name + "_0" + std::to_string(i) + ".png";
		if (spriteCache->getSpriteFrameByName(link) == nullptr) break;
		exFrames.pushBack(spriteCache->getSpriteFrameByName(link));
		i++;
	}
	auto animation = cocos2d::Animation::createWithSpriteFrames(exFrames, 0.05 / speed);
	auto animate = cocos2d::Animate::create(animation);
	cocos2d::RepeatForever* repeat = cocos2d::RepeatForever::create(animate);
	return repeat;
}

cocos2d::Animate* ObjectParent::AnimationObjectOnce(int id, std::string name, float speed)
{
	auto spriteCache = ResourceManager::GetInstance()->GetFrameById(id);
	cocos2d::Vector<cocos2d::SpriteFrame*> exFrames;
	int i = 0;
	std::string link;
	while (true) {
		link = "0_" + name + "_00" + std::to_string(i) + ".png";
		if (i >= 10) link = "0_" + name + "_0" + std::to_string(i) + ".png";
		if (spriteCache->getSpriteFrameByName(link) == nullptr) break;
		exFrames.pushBack(spriteCache->getSpriteFrameByName(link));
		i++;
	}
	auto animation = cocos2d::Animation::createWithSpriteFrames(exFrames, 0.05 / speed);
	auto animate = cocos2d::Animate::create(animation);
	return animate;
}