#include "ResourceManager.h"
int ResourceManager::LevelPlayer = 1;
ResourceManager* ResourceManager::s_instance;
ResourceManager::ResourceManager()
{
	//s_instance = new ResourceManager[10];
	/*m_sprites = new std::map<char, Sprite*>[10];
	m_buttons = new std::map<char, ui::Button*>;
	m_labels = new std::map<char, Label*>;*/
}

ResourceManager::~ResourceManager()
{
}

ResourceManager* ResourceManager::GetInstance()
{
	if (s_instance==nullptr) {
		s_instance = new ResourceManager();
	}
	return s_instance;
}



void ResourceManager::Init(const std::string path)
{
	m_dataFolderPath = FileUtils::getInstance()->getStringFromFile(path);
	Load(m_dataFolderPath);
}

void ResourceManager::Load(std::string fileName)
{
	m_framecachePlayer.clear();
	CCLOG("Load 1****************** %s: ", fileName.c_str());
	int count = 0;
	while (!m_dataFolderPath.empty()) {
		std::string line = m_dataFolderPath.substr(0, m_dataFolderPath.find("\n"));
		std::istringstream is(line);
		int num;
		std::string text, text2;
		is >> num >> text >> text2;
		m_dataFolderPath.erase(0, m_dataFolderPath.find("\n") + 1);
		if (num == 0) {
			count++;
			continue;
		}

		if (count == 1) {
			CCLOG("Load 2******************");
			auto sprite = Sprite::create(text);
			CCLOG("Load 3******************");
			sprite->retain();
			CCLOG("Load 4******************");
			m_sprites.insert({ num,sprite });
			CCLOG("Load 5******************");
			continue;
		}
		if (count == 2) {
			auto button = ui::Button::create(text, text2);
			CCLOG("Load 6******************");
			button->retain();
			CCLOG("Load 7******************");
			m_buttons.insert({ num,button });
			continue;
		}
		if (count == 3) {
			auto label = Label::createWithTTF("temp", text, 20);
			CCLOG("Load 8******************");
			label->retain();
			CCLOG("Load 9******************");
			m_labels.insert({ num,label });
		}
		if (count == 4) {
			auto spriteCache = SpriteFrameCache::getInstance();
			spriteCache->addSpriteFramesWithFile(text);
			CCLOG("Load 10******************");
			spriteCache->retain();
			CCLOG("Load 11******************");
			m_framecachePlayer.insert({ num,spriteCache });
			spriteCache->destroyInstance();
			CCLOG("Load 12******************");
		}
		if (count == 5) {
			auto spriteCache = SpriteFrameCache::getInstance();
			spriteCache->addSpriteFramesWithFile(text);
			CCLOG("Load 10******************");
			spriteCache->retain();
			CCLOG("Load 11******************");
			m_framecacheAI.insert({ num,spriteCache });
			spriteCache->destroyInstance();
			CCLOG("Load 12******************");
		}
	}
	CCLOG("Load END******************");
}

Sprite* ResourceManager::GetSpriteById(int id)
{
	auto sprite = m_sprites.find(id)->second;
	return sprite;
}

ui::Button* ResourceManager::GetButtonById(int id)
{
	auto button = m_buttons.find(id)->second;
	return button;
}

Label* ResourceManager::GetLabelById(int id)
{
	auto label = m_labels.find(id)->second;
	return label;
}
SpriteFrameCache* ResourceManager::GetFramePlayerById(int id)
{
	auto frame = m_framecachePlayer.find(id)->second;
	return frame;
}
SpriteFrameCache* ResourceManager::GetFrameAIById(int id)
{
	auto frame = m_framecacheAI.find(id)->second;
	return frame;
}
void ResourceManager::SetLevelPlayer(int level)
{
	LevelPlayer = level;
}
Sprite* ResourceManager::DuplicateSprite(Sprite* sprite)
{
	Sprite* pRet = Sprite::createWithTexture(sprite->getTexture());
	if (sprite->getChildrenCount() > 0)
	{
		for (int child = 0; child < sprite->getChildrenCount(); child++)
		{
			Sprite* spriteChild = (Sprite*)sprite->getChildren().at(child);
			Sprite* clone = DuplicateSprite((Sprite*)spriteChild);
			clone->boundingBox() = spriteChild->boundingBox();
			clone->setContentSize(spriteChild->getContentSize());
			clone->setPosition(spriteChild->getPosition());
			clone->setAnchorPoint(spriteChild->getAnchorPoint());
			pRet->addChild(clone, spriteChild->getZOrder(), spriteChild->getTag());
		}
	}
	return pRet;
}


