#pragma once
#include <vector>
#include "SDL_mixer.h"  //required for audio
#include <iostream>
#include <map>

using namespace std;

class AudioManager
{
private:
	std::map<std::string, Mix_Chunk*> globalSounds;
	std::map<std::string, Mix_Music*> globalMusic;

	std::map<std::string, Mix_Chunk*> localSounds;
	std::map<std::string, Mix_Music*> localMusic;

public:
	AudioManager();
	~AudioManager();
	bool Init();

	//Set volume of the music
	void SetMusicVolume(int volLevel);

	///loops=-1 means infinite
	void PlayGlobalMusic(string id, int loops = -1);

	void PlayGlobalSound(string id, int channel = -1, int loops = 0);

	void PlayLocalMusic(string id, int loops = -1);

	void PlayLocalSound(string id, int channel = -1, int loops = 0);

	void LoadGlobalMusic(const char* path, string id);
	void LoadGlobalSound(const char* path, string id);

	void LoadLocalSound(const char* path, string id);
	void LoadLocalMusic(const char* path, string id);

	void UnloadMusic(string scope);
	void UnloadSounds(string scope);

	//Toggle music:: so that you can pause and resume the current music track
	void ToggleMusic();



};