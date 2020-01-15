#ifndef _GAME_SETTING_H_
#define _GAME_SETTING_H_

class GameSetting
{
public:
	static GameSetting* sInstance;
	bool Music;
	bool Sound;
	int Volume;
private:
	GameSetting();

public:
	~GameSetting();

	static GameSetting* getInstance();

	void setMusic(bool enable);

	bool isMusic();

	void setSound(bool enable);

	bool isSound();

	void setVolume(int volume);

	int getVolume();
};

#endif