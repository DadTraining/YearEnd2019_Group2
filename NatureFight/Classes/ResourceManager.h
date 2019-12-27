#pragma once
#include <string>
#include <cocos2d.h>
#include <cocos\ui\UIButton.h>
using namespace std;
USING_NS_CC;
class ResourceManager
{
private:
	ResourceManager();
	static ResourceManager* s_instance;
	 string m_dataFolderPath;
	 map<char, cocos2d::Sprite*> m_sprites;
	 map<char, ui::Button*> m_buttons;
	 map<char, Label*> m_labels;
	 
public:
	
	~ResourceManager();
	static ResourceManager* GetInstance();
	 void Init(const string path);
	 void Load(string fileName);
	 Sprite* GetSpriteById(char id);
	 ui::Button* GetButtonById(char id);
	 Label* GetLabelById(char id);


};

