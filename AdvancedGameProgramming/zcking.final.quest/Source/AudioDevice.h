#pragma once

#include "SDL_mixer.h"

#include <map>
#include <string>

class AudioDevice
{
public:
	AudioDevice();
	~AudioDevice();

	// Startup and shutdown
	bool Initialize(std::string audioConfigFile);
	bool Shutdown();

	Mix_Music* getBackgroundMusic();

	bool PlayClip(std::string clipName, int loops=0);
	bool setBackgroundMusic(std::string musicName);
	bool isPlayingMusic();
	bool isPlayingMusic(std::string);

private:
	std::map<std::string, Mix_Chunk*> clipLibrary;
	std::map<std::string, Mix_Music*> musicLibrary;
	Mix_Music* backgroundMusic;
};