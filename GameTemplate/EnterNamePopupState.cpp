#include "EnterNamePopupState.h"
#include <iostream>
#include "GameEngine.h"
#include "GameLevel1.h"
#include "LoadingState.h"

using namespace std;

// Begin PauseState
void EnterNamePopupState::Enter()
{
	m_pFont = TTF_OpenFont("game_over.ttf", 100);

	cout << "Entering progress screen..." << endl;

	btn = new Button("Img/play.png", { 0,0,400,100 }, { 412,500,200,80 });

	inputBgTex = GameEngine::Instance()->LoadTexture("Img/progressbarbg.png"); //texture for the player's HP bar's

	inputBox = new UIInputBox(inputBgTex, { 0, 0, 330, 30 }, { 350, 400, 330, 60 });

	SDL_StartTextInput();
}

/*
Change the game level based on the game managers current level
*/
void EnterNamePopupState::Update()
{
	// Update buttons. Allows for mouseovers.
	btn->Update();

	inputBox->Update();

	if (btn->Clicked())
	{
		if (GameEngine::Instance()->GetInputText().length() > 0) {
			GameEngine::Instance()->GetGM()->SetName(GameEngine::Instance()->GetInputText());
			GameEngine::Instance()->GetFSM()->ChangeState(new LoadingState());
		}
	}

}

/**
Render the players total damage for that round
*/
void EnterNamePopupState::Render()
{


	SDL_SetRenderDrawColor(GameEngine::Instance()->GetRenderer(), 64, 64, 128, 128);

	SDL_Rect rect = {256, 128, 512, 512};
	SDL_RenderFillRect(GameEngine::Instance()->GetRenderer(), &rect);

	SDL_SetRenderDrawColor(GameEngine::Instance()->GetRenderer(), 120, 120, 128, 128);

	inputBox->Render();

	btn->Render();


	string msg = "Enter Name:";

	ScreenState::RenderFont(true, msg.c_str(), 400, 350);

	ScreenState::Render();

}


void EnterNamePopupState::Exit()
{

	cout << "Exiting progress..." << endl;
	SDL_StopTextInput();

	delete btn;
	btn = nullptr;
}

