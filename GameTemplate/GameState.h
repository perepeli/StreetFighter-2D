#pragma once
#include "Player.h"
#include "SDL_mixer.h"
#include "Enemy.h"
#include "ScreenState.h"
#include "ProgressBar.h"
#include "Timer.h"

//aoe logic
#include "HadoukenAOE.h"

#include <iostream>
using namespace std;

class GameState : public ScreenState
{
protected:
	SDL_Texture* mainSpriteTex;//load and store the main sprite texture
	SDL_Texture* mainSpriteTex2;//load and store the main sprite texture

	//aoe logic sprite
	SDL_Texture* aoeSpriteTex;

	SDL_Texture* bgSpriteTex; //load and store background sprite tex
	SDL_Texture* progressBarBgTex;
	SDL_Texture* msgTex;
	bool renderMsg = true;
	SpriteEx* bg;
	SpriteEx* userMsg;
	bool isGameOver = false;
	Player* player;
	Enemy* enemy;

	//aoe logic
	HadoukenAOE* hadoukenAOE;


public:
	void SetRenderMessage(bool b) { this->renderMsg = b; }
	bool isMessageRendered() { return renderMsg; }
	GameState() {}
	virtual void Update();
	void Render();
	virtual void Enter();
	void Exit();
	void Resume() { cout << "Resuming Game..." << endl; }
};
