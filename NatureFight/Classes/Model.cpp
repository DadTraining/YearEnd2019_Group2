#include "Model.h"
Model::Model()
{
	mIsALive = true;
}

Model::~Model()
{	
}

cocos2d::PhysicsBody* Model::getPhysicBody()
{
	return mPhysicsBody;
}

void Model::setAlive(bool alive)
{
	mIsALive = alive;
	mSprite->setVisible(mIsALive);
	mPhysicsBody->setEnabled(alive);
}

bool Model::isAlive()
{
	return mIsALive;
}

void Model::setIndex(int index)
{
	mPhysicsBody->setGroup(index);
}

int Model::getIndex()
{
	return mPhysicsBody->getGroup();
}

bool Model::isMoveRight()
{
	return mIsRunLeftToRight;
}

void Model::setPosition(cocos2d::Vec2 pos)
{
	mSprite->setPosition(pos);
}

void Model::setScale(float scale)
{
	mSprite->setScale(scale);
}

Vec2 Model::getPosition()
{
	return mSprite->getPosition();
}

Size Model::getContentSize()
{
	return mSprite->getContentSize();
}