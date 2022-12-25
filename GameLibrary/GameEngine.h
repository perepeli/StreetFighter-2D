#pragma once
#include "SpriteEx.h"
#include "SDL.h"
#include "SDL_image.h"
#include "GameManager.h"

#include <vector>
#include "SDL_ttf.h"
#include <string>

#include "StateMachine.h"
#include "AudioManager.h"

using namespace std;

class GameEngine
{
private:
	string inputText;
	bool isAppRunning;
	SDL_Window* sdlWindow;
	SDL_Renderer* sdlRenderer;
	const Uint8* m_iKeystates; //manages keystates

	StateMachine* m_pFSM;
	AudioManager* m_pAM; //pointer to the audio manager

	bool m_bLeftMouse = false; // Keeps track of left mouse button state.
	int m_iMouseX, m_iMouseY;  // Variables to hold mouse positions.
	GameManager* gm;

public:
	static GameEngine* Instance(); //singleton instance reference
	SDL_Window* GetWindow() { return sdlWindow; }
	SDL_Renderer* GetRenderer() { return sdlRenderer; }
	SDL_Texture* LoadTexture(const char* path);
	GameManager* GetGM() { return gm; }

	//window initialization happens here
	bool Init(const char* title, const int xPos,
		const int yPos, const int width, const int height,
		const int flags);

	void QuitGame() { isAppRunning = false; }

	//Is the Application running
	bool IsRunning();
	//Check for 'KeyDown' press
	bool KeyDown(SDL_Scancode c);
	bool KeyUp(SDL_Scancode c);

	//The update loop
	void Update();
	//Handles input events
	void HandleEvents();
	//handles rendering
	void Render();
	//clean-up code
	void Clean();

	int GetMouseX() { return m_iMouseX; }
	int GetMouseY() { return m_iMouseY; }
	int GetLeftMouse() { return m_bLeftMouse; }
	void SetLeftMouse(bool b) { m_bLeftMouse = b; }
	string GetInputText() { return this->inputText; }
	StateMachine* GetFSM() { return m_pFSM; }
	AudioManager* GetAM() { return m_pAM; }

};