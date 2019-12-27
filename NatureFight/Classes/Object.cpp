#include "Object.h"

Object::Object()
{
}

Object::~Object()
{
}
cocos2d::Sprite* Object::DuplicateSprite(cocos2d::Sprite* sprite)
{
	cocos2d::Sprite* pRet = cocos2d::Sprite::createWithTexture(sprite->getTexture());
	if (sprite->getChildrenCount() > 0)
	{
		for (int child = 0; child < sprite->getChildrenCount(); child++)
		{
			cocos2d::Sprite* spriteChild = (cocos2d::Sprite*)sprite->getChildren().at(child);
			cocos2d::Sprite* clone = DuplicateSprite((cocos2d::Sprite*)spriteChild);
			clone->boundingBox() = spriteChild->boundingBox();
			clone->setContentSize(spriteChild->getContentSize());
			clone->setPosition(spriteChild->getPosition());
			clone->setAnchorPoint(spriteChild->getAnchorPoint());
			pRet->addChild(clone, spriteChild->getZOrder(), spriteChild->getTag());
		}
	}
	return pRet;
}
