#include "ResourceManager.h"
ResourceManager* ResourceManager::s_instance;
ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

ResourceManager* ResourceManager::GetInstance()
{
	if (!s_instance)
	{
		s_instance = new ResourceManager();
	}
	return s_instance;
}

void ResourceManager::Init(const string path)
{
	Load(path);

}

void ResourceManager::Load(string fileName)
{
	int count = 0;

	std::string path = FileUtils::getInstance()->getStringFromFile(fileName);

	while (!path.empty()) {
		std::string line = path.substr(0, path.find("\n"));
		std::istringstream is(line);
		int num;
		std::string text, text2;
		is >> num >> text >> text2;
		path.erase(0, path.find("\n") + 1);

		if (num == 0) {

			count++;

			continue;

		}



		if (count == 1) {

			auto sprite = Sprite::create(text);
			sprite->retain();
			m_sprites.insert({ (char)num,sprite });

			continue;

		}

		if (count == 2) {

			auto button = ui::Button::create(text, text2);
			button->retain();
			m_buttons.insert({ (char)num,button });
			continue;

		}

		if (count == 3) {

			auto label = Label::createWithTTF("Hello", text, 20);
			label->retain();
			m_labels.insert({ (char)num,label });
		}

	}
}

Sprite* ResourceManager::GetSpriteById(char id)
{
	return m_sprites.find(id)->second;
}

ui::Button* ResourceManager::GetButtonById(char id)
{
	return  m_buttons.find(id)->second;
}

Label* ResourceManager::GetLabelById(char id)
{
	return m_labels.find(id)->second;
}


