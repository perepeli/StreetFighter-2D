#include <iostream>
#include "GameEngine.h"

using namespace std;

//Singleton pattern for Game class 
//is defined as follows
GameEngine* GameEngine::Instance()
{
	static GameEngine* instance = new GameEngine();
	return instance;
}

bool GameEngine::Init(const char* title, const int xPos, const int yPos, const int width, const int height,
	const int flags)
{
	//0 means success
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		cout << "SDL Initialization successful\n";

		sdlWindow = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
		if (sdlWindow == nullptr)
		{
			cout << "Window initialization failed.\n";
			return false;
		}
		cout << "Window successfully created.\n";
		sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, 0);
		if (sdlRenderer == nullptr)
		{
			cout << "renderer initialization failed.\n";
			return false;
		}
	}
	else
	{
		cout << "SDL Initialization failed\n";
		return false;
	}


	if (TTF_Init() == 0) //font init is succesful
	{
		cout << "Font init success!\n";
	}
	else
	{
		cout << "Font init fail!\n";
		return false;
	}

	m_pAM = new AudioManager();
	//if you are not able to initialize, return false

	if (!m_pAM->Init())
		return false;
	//set to lower volume so we can hear sfx as well
	m_pAM->SetMusicVolume(10);
//	m_pAM->LoadGlobalSound("Aud/button.wav", "btnSound");

	m_iKeystates = SDL_GetKeyboardState(nullptr);
	isAppRunning = true;

	m_pFSM = new StateMachine();

	gm = new GameManager();

	inputText = "";

	return true;
}



SDL_Texture* GameEngine::LoadTexture(const char* path)
{
	SDL_Surface* surface = IMG_Load(path);
	return SDL_CreateTextureFromSurface(sdlRenderer, surface);

}


bool GameEngine::IsRunning()
{
	return isAppRunning;
}

//check whether a specific key, passed as argument 'c'
//is pressed down
bool GameEngine::KeyDown(SDL_Scancode c)
{
	if (m_iKeystates == nullptr)
		return false;

	if (m_iKeystates[c] == 1)
		return true;
	else return false;
}

bool GameEngine::KeyUp(SDL_Scancode c)
{
	if (m_iKeystates == nullptr)
		return false;

	if (m_iKeystates[c] == 0)
		return true;
	else return false;
}



void GameEngine::Update()
{

	GetFSM()->Update();
}


void GameEngine::HandleEvents()
{
	SDL_Event event;

	//SDL_Color textColor = { 0, 0, 0, 0xFF };

	//The current input text.
	//std::string inputText = "Some Text";
	//GameEngine::loadFromRenderedText(inputText.c_str(), textColor);

	//Enable text input
	//SDL_StartTextInput();


	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			isAppRunning = false;
			break;

		case SDL_MOUSEMOTION:
			SDL_GetMouseState(&m_iMouseX, &m_iMouseY);
			break;

		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
				m_bLeftMouse = true;
			break;

		case SDL_MOUSEBUTTONUP:
		{
			if (event.button.button == SDL_BUTTON_LEFT)
				m_bLeftMouse = false;

			//if (event.button.button == SDL_BUTTON_LEFT && player)
			//{
			//	//do something...  such as fire a bullet/missile
			//	//and play sound
			//	Mix_PlayChannel(-1, fireSound, 0); //-1 means we ask the mixer to play on the first available channel. the third argument: 0, means we play it just once (no looping)
			//	player->SpawnBullet();
			//}
			break;
		}
		case SDL_KEYDOWN: {
			//Handle backspace
			if (event.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0)
			{
				//lop off character
				inputText.pop_back();
			}
			else if (event.key.keysym.sym == SDL_SCANCODE_RETURN) {
				SDL_StopTextInput();
			}
			break;
		}
		case SDL_TEXTINPUT: {
		}
			if (inputText.length() < 16) {
				inputText += event.text.text;
				cout << inputText << endl;
			}

			break;
		}
	}
}


void GameEngine::Render()
{
	GetFSM()->Render();
}

void GameEngine::Clean()
{
	cout << "Cleaning up and shutting down engine...\n";
	m_pFSM->Clean();
	gm->CleanUp();

	delete m_pFSM;
	delete m_pAM;
	delete gm;
	SDL_DestroyWindow(sdlWindow);
	SDL_DestroyRenderer(sdlRenderer);

	//TTF_CloseFont(m_pFont);
	TTF_Quit();

	IMG_Quit();

	SDL_Quit();

}


