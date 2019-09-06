#include "stdafx.h"
#include "SoundManager.h"


SoundManager::SoundManager()
{
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, AUDIO_S16, 2, 4096);                               //инициализация аудиосистемы
}


SoundManager::~SoundManager()
{
	Mix_CloseAudio();                                                                       //закрытие аудиосистемы
}

bool SoundManager::load(std::string fileName, std::string id, sound_type type)
{
	if (type == SOUND_MUSIC)
	{
		Mix_Music* pMusic = Mix_LoadMUS(fileName.c_str());                                  //загрузка аудиофайла музыки
		if (pMusic == 0)
		{
			std::cout << "Could not load music: ERROR - "<< Mix_GetError() << std::endl;    //если файл не загружен то выдает ошибку и выходит
			return false;
		}
		m_music[id] = pMusic;                                                               //елси файл загружен то запись музыки в контейнер
		return true;
	}
	else if (type == SOUND_SFX)
	{
		Mix_Chunk* pChunk = Mix_LoadWAV(fileName.c_str());                                  //загрузка аудиофайла звука
		if (pChunk == 0)
		{
			std::cout << "Could not load SFX: ERROR - " << Mix_GetError() << std::endl;     //если файл не загружен то выдает ошибку и выходит
			return false;
		}
		m_sfxs[id] = pChunk;                                                                //елси файл загружен то запись звука в контейнер
		return true;
	}
	return false;
}

void SoundManager::playMusic(std::string id, int loop)
{
		Mix_PlayMusic(m_music[id], loop); //воспризведение музыки
}

void SoundManager::VolumeMusic(int vol)
{
	Mix_VolumeMusic(vol);
}

void SoundManager::VolumeSound(int vol)
{
	Mix_Volume(-1, vol);
}

void SoundManager::StopMusic()
{
	Mix_HaltMusic();
}

void SoundManager::playSound(std::string id, int loop)
{
	Mix_PlayChannel(-1, m_sfxs[id], loop);                                                  //воспризведение музыки
}
