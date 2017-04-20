#include "AudioDevice.h"
#include "tinyxml\tinyxml.h"

#include <iterator>

AudioDevice::AudioDevice()
{
	musicLibrary = std::map<std::string, Mix_Music*>();
	clipLibrary = std::map<std::string, Mix_Chunk*>();
}

AudioDevice::~AudioDevice()
{

}

bool AudioDevice::Initialize(std::string audioConfigFile)
{
	// Load the audio xml file
	TiXmlDocument audioDoc(audioConfigFile.c_str());
	if (!audioDoc.LoadFile())
	{
		printf("Unable to load audio XML file %s! Tiny XML Error: %s\n", audioConfigFile.c_str(), audioDoc.ErrorDesc());
		return false;
	}

	// Parse the root element
	TiXmlElement* audioRoot = audioDoc.FirstChildElement();
	if (audioRoot == NULL)
		return false;

	// Parse the audio clip elements
	for (TiXmlElement* clipXml = audioRoot->FirstChildElement(); clipXml != NULL; clipXml = clipXml->NextSiblingElement())
	{
		// Query the attributes
		std::string clipName = clipXml->Attribute("name");
		bool isMusic;
		clipXml->QueryBoolAttribute("bg", &isMusic);
		std::string clipPath = clipXml->Attribute("path");

		// Store in appropriate library
		if (isMusic)
		{
			Mix_Music *music = Mix_LoadMUS(clipPath.c_str());
			if (music == NULL)
				return false;
			musicLibrary[clipName] = music;
		}
		else
		{
			Mix_Chunk *chunk = Mix_LoadWAV(clipPath.c_str());
			if (chunk == NULL)
				return false;
			clipLibrary[clipName] = chunk;
		}
	}

	// Allocate some channels to play on
	Mix_AllocateChannels(100);

	return true;
}

bool AudioDevice::Shutdown()
{
	// Free all the chunks
	for (auto chunk : clipLibrary)
	{
		Mix_FreeChunk(chunk.second);
	}

	// Free all the music
	for (auto music : musicLibrary)
	{
		Mix_FreeMusic(music.second);
	}

	return true;
}

Mix_Music * AudioDevice::getBackgroundMusic()
{
	return backgroundMusic;
}

bool AudioDevice::setBackgroundMusic(std::string musicName)
{
	// Try to find the music
	auto musicIter = musicLibrary.find(musicName);
	if (musicIter == musicLibrary.end())
		return false;

	backgroundMusic = musicIter->second;

	Mix_HaltMusic();
	Mix_PlayMusic(backgroundMusic, -1); // Loop the bg music 
	return true;
}

bool AudioDevice::PlayClip(std::string clipName, int loops)
{
	// Try to find the clip/chunk
	auto clipIter = this->clipLibrary.find(clipName);
	if (clipIter == clipLibrary.end())
		return false;

	// Play the clip/chunk
	Mix_PlayChannel(-1, clipIter->second, loops);

	return true;
}

bool AudioDevice::isPlayingMusic()
{
	return Mix_PlayingMusic();
}

bool AudioDevice::isPlayingMusic(std::string musicName)
{
	return (backgroundMusic == musicLibrary[musicName] && Mix_PlayingMusic());
}