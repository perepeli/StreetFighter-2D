#include "GameState.h"
#include "GameEngine.h"
#include "PauseMenuPopupState.h"
#include "Timer.h"

void GameState::Enter()
{
	//	bgSpriteTex = GameEngine::Instance()->LoadTexture("background.png");
	/*	mainSpriteTex = GameEngine::Instance()->LoadTexture("Img/Players/PlayerKenSprite2.png");
		mainSpriteTex2 = GameEngine::Instance()->LoadTexture("Img/Players/PlayerKenSprite.png");

		m_pFont = TTF_OpenFont("Font/LTYPE.TTF", 30);

		SDL_Rect bgSrcRect;
		bgSrcRect.x = bgSrcRect.y = 0;
		SDL_QueryTexture(bgSpriteTex, NULL, NULL, &bgSrcRect.w, &bgSrcRect.h);

		SDL_Rect bgDestRect;
		bgDestRect.x = bgDestRect.y = 0;
		SDL_GetWindowSize(GameEngine::Instance()->GetWindow(), &bgDestRect.w, &bgDestRect.h);

		bg = new SpriteEx(bgSpriteTex, bgSrcRect, bgDestRect);

		player = new Player(mainSpriteTex, bgDestRect.w*0.3, bgDestRect.h - 100);


		GameEngine::Instance()->GetAM()->LoadLocalMusic("Aud/game.mp3", "gameMusic");
		GameEngine::Instance()->GetAM()->PlayLocalMusic("gameMusic");
		GameEngine::Instance()->GetAM()->LoadLocalSound("Aud/explode.wav", "explodeSound");*/

}


void GameState::Update()
{


	//if (player) this->CheckCollision();

}


void GameState::Render()
{
	SDL_SetRenderDrawColor(GameEngine::Instance()->GetRenderer(), 0, 0, 0, 255); //set background window color
	SDL_RenderClear(GameEngine::Instance()->GetRenderer()); //clear the screen

	bg->Render();

	if (renderMsg == true) {
		userMsg->Render();
	}

	if (player) player->Render();

	if (enemy) enemy->Render();

	//aoe logic render
	if (hadoukenAOE) hadoukenAOE->Render();

	ScreenState::Render();


}


void GameState::Exit()
{
	//to-do:: de-allocate memory, texture, surface etc, sound 
	GameEngine::Instance()->GetAM()->UnloadMusic("local");
	GameEngine::Instance()->GetAM()->UnloadSounds("local");
	//GameEngine::Instance()->Clean();
	/*
	delete bg;
	delete userMsg;
	delete player->healthBar;
	delete enemy->healthBar;
	delete player;
	delete enemy;
	delete msgTex;
	delete progressBarBgTex;
	delete mainSpriteTex;
	delete mainSpriteTex2;
	delete m_pFont;
	delete bgSpriteTex;*/

	Timer::Instance()->Clean();


}

