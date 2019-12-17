#ifndef __MAPTUTORIAL_SCENE_H__
#define __MAPTUTORIAL_SCENE_H__

#include "cocos2d.h"#include "ObjectParent.h"
#include "AiLv1.h"
class MapTutorialScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
	void addMap();
    virtual bool init();
    void update(FLOAT deltaTime);
    CREATE_FUNC(MapTutorialScene);

};
#endif // __MAPTUTORIAL_SCENE_H__
