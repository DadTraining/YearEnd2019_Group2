#ifndef  _RESOURCE_MANAGER_H_
#define  _RESOURCE_MANAGER_H_
#include "cocos2d.h"
#include<string>
#include<map>
#include <ui\CocosGUI.h>
USING_NS_CC;

class ResourceManager
{
public:
	ResourceManager* s_instance;
	std::string m_dataFolderPath;
	std::map<int, Sprite*> m_sprites;
	std::map<int, ui::Button*> m_buttons;
	std::map<int, Label*> m_labels;
	static int LevelPlayer;
public:
	void SetLevelPlayer(int);
	Sprite* DuplicateSprite(Sprite* sprite);
	ResourceManager();
	~ResourceManager();
	static ResourceManager* GetInstance();
	void Init(const std::string path);
	void Load(std::string fileName);
	Sprite* GetSpriteById(int id);
	ui::Button* GetButtonById(int id);
	Label* GetLabelById(int id);
};
#endif

