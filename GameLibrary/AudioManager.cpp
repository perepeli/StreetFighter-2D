
#include <algorithm>
#include "AudioManager.h"


AudioManager::AudioManager()
{

}

bool AudioManager::Init()
{

	if (Mix_Init(MIX_INIT_MP3) == 0)
	{
		cout << "Mixer init failed\n";
		return false;
	}
	else
	{
		Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096);
		Mix_AllocateChannels(16);
		return true;
	}
}

void AudioManager::SetMusicVolume(int volLevel)
{
	int clampedVolume =
		std::clamp(volLevel, 0, 128);

	Mix_VolumeMusic(clampedVolume);

}

void AudioManager::PlayGlobalMusic(string id, int loops)
{
	Mix_PlayMusic(globalMusic[id], loops);

}

void AudioManager::PlayGlobalSound(string id, int channel, int loops)
{
	Mix_PlayChannel(channel, globalSounds[id], loops);
}

void AudioManager::PlayLocalMusic(string id, int loops)
{
	Mix_PlayMusic(localMusic[id], loops);

}

void AudioManager::PlayLocalSound(string id, int channel, int loops)
{
	Mix_PlayChannel(channel, localSounds[id], loops);
}

void AudioManager::LoadGlobalMusic(const char* path, string id)
{
	//check if it is loadable first...
	Mix_Music* t = Mix_LoadMUS(path);
	if (t != nullptr)
	{
		globalMusic[id] = t;
	}
	else
	{
		//error
		cout << "Music load failed. \n";
	}
}

void AudioManager::LoadGlobalSound(const char* path, string id)
{
	Mix_Chunk* t = Mix_LoadWAV(path);
	if (t != nullptr)
		globalSounds[id] = t;
	else
		cout << "Sound load failed. \n";
}

void AudioManager::LoadLocalMusic(const char* path, string id)
{
	//check if it is loadable first...
	Mix_Music* t = Mix_LoadMUS(path);
	if (t != nullptr)
	{
		localMusic[id] = t;
	}
	else
	{
		//error
		cout << "Music load failed. \n";
	}
}

void AudioManager::LoadLocalSound(const char* path, string id)
{
	Mix_Chunk* t = Mix_LoadWAV(path);
	if (t != nullptr)
		localSounds[id] = t;
	else
		cout << "Sound load failed. \n";
}

void AudioManager::ToggleMusic()
{
	//Mix_PausedMusic() returns 1 if paused.
	if (Mix_PausedMusic() == 1)
		Mix_ResumeMusic();
	else
		Mix_PauseMusic();

}

/*
Function to load and unload music based on the specified scope, local or global
*/
void AudioManager::UnloadMusic(string scope)
{
	//how to unload a single music track from memory:
	//Mix_FreeMusic(  )

	//how do you unload the entire vector?
	//iterate through the vector,
	//unload each index, and set its index to nullptr
	//after your do the above, 
	//clear the vector & shrink to fit
	if (scope == "local") {
		for (auto it = localMusic.begin(); it != localMusic.end(); ++it) {
			auto i = it->first;
			Mix_FreeMusic(it->second);
		}
		localMusic.clear();
	}
	else if (scope == "global") {
		for (auto it = globalMusic.begin(); it != globalMusic.end(); ++it) {
			auto i = it->first;
			Mix_FreeMusic(it->second);
		}
		globalMusic.clear();
	}
	else {
		cout << "Invalid input\n";
	}

}

/*
Function to load and unload sounds based on the specified scope, local or global
*/
void AudioManager::UnloadSounds(string scope)
{
	if (scope == "local") {
		for (auto it = localSounds.begin(); it != localSounds.end(); ++it) {
			auto i = it->first;
			Mix_FreeChunk(it->second);
		}
		localSounds.clear();
	}
	else if (scope == "global") {
		for (auto it = globalSounds.begin(); it != globalSounds.end(); ++it) {
			auto i = it->first;
			Mix_FreeChunk(it->second);
		}
		globalSounds.clear();
	}
	else {
		cout << "Invalid input\n";
	}
}


AudioManager::~AudioManager()
{
	UnloadMusic("local");
	UnloadSounds("local");
	UnloadMusic("global");
	UnloadSounds("global");

	Mix_CloseAudio();
	Mix_Quit();
}