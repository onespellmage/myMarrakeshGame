#pragma once
#include <SDL_mixer.h>
#include <iostream>
#include <map>

enum sound_type
{
	SOUND_MUSIC = 0,
	SOUND_SFX = 1
};

class SoundManager
{
public:
	bool load(std::string fileName, std::string id, sound_type type);             //загрузка файлов музыки и звуков в соответствующие контейнера
	void playSound(std::string id, int loop);                                     //проигрывание музыки
	void playMusic(std::string id, int loop);                                     //проигрывание звуков
	void VolumeMusic(int vol);
	void VolumeSound(int vol);
	void StopMusic();
	SoundManager();
	~SoundManager();

private:
	std::map<std::string, Mix_Chunk*> m_sfxs;                                     //контейнер звуков
	std::map<std::string, Mix_Music*> m_music;                                    //контейнер музыки

	SoundManager(const SoundManager&);
};
typedef SoundManager TheSoundManager;
