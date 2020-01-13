#include "GameSetting.h"

GameSetting* GameSetting::sInstance = nullptr;

GameSetting::GameSetting() :
	Music(true),
	Sound(true),
	Volume(100)
{

}

GameSetting::~GameSetting()
{

}

GameSetting* GameSetting::getInstance()
{
	if (sInstance == nullptr)
	{
		sInstance = new GameSetting();
	}
	return sInstance;
}

void GameSetting::setMusic(bool enable)
{
	Music = enable;
}

bool GameSetting::isMusic()
{
	return Music;
}

void GameSetting::setSound(bool enable)
{
	Sound = enable;
}

bool GameSetting::isSound()
{
	return Sound;
}

void GameSetting::setVolume(int volume)
{
	Volume = volume;
}

int GameSetting::getVolume()
{
	return Volume;
}