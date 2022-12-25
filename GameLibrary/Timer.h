#pragma once
#include <SDL_timer.h>
#include <vector>
#include <SDL.h>

const float FPS = 60.0f;
const float FRAME_PER_SECOND = FPS / 1000.0f;

const float FRAME_DELAY = 1000.0f / FPS;
const float MAX_DELTA_TIME = 1.5f;

using TimerID = SDL_TimerID;
using T_Callback = SDL_TimerCallback;

/*
Using SDL timer callbacks for various timed functionality (attack cooldowns, respawn timer, transition timers, etc
*/
class Timer
{
public:
	Timer();
	void Tick();
	inline const float DeltaTime() { return m_DeltaTime; }

	inline static Timer* Instance() {
		return s_Instance = (s_Instance != nullptr) ? s_Instance : new Timer();
	}

	inline void Clean() {
		for (TimerID id : m_TimerRegistry)
			SDL_RemoveTimer(id);
	}

	inline TimerID StartTimer(Uint32 interval, T_Callback callback, void* data) {
		TimerID id = SDL_AddTimer(interval, callback, data);
		m_TimerRegistry.push_back(id);
		return id;
	}

	inline void Removetimer(TimerID id) {
		SDL_RemoveTimer(id);
	}


private:
	float m_DeltaTime;
	float m_LastTime;
	std::vector<TimerID> m_TimerRegistry;

	static Timer* s_Instance;
};

