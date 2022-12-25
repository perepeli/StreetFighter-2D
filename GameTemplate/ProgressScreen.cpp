#include "ProgressScreen.h"
#include <iostream>
#include "GameEngine.h"
#include "GameLevel1.h"
#include "GameLevel2.h"
#include "GameLevel3.h"
#include "MainMenuState.h"
#include "FinalState.h"


using namespace std;

// Begin PauseState
void ProgressScreen::Enter()
{
	score = 0;
	m_pFont = TTF_OpenFont("game_over.ttf", 100);

	cout << "Entering progress screen..." << endl;

	btn = new Button("Img/play.png", { 0,0,400,100 }, { 412,300,200,80 });

}

/*
Change the game level based on the game managers current level
*/
void ProgressScreen::Update()
{
	// Update buttons. Allows for mouseovers.
	btn->Update();

	if (btn->Clicked())
	{
		switch (GameEngine::Instance()->GetGM()->GetLevel()) {
		case 2:
			GameEngine::Instance()->GetFSM()->ChangeState(new GameLevel2());
			break;
		case 3:
			GameEngine::Instance()->GetFSM()->ChangeState(new GameLevel3());
			break;
		default:
			GameEngine::Instance()->GetFSM()->ChangeState(new FinalState());
		}
		//GameEngine::Instance()->GetFSM()->PopState();
	}
	/*for (int i = 0; i < (int)m_vButtons.size(); i++)
		m_vButtons[i]->Update();

	if (m_vButtons[btn::play]->Clicked())
	{
		GameEngine::Instance()->GetFSM()->PopState();
	}
	*/
}

/**
Render the players total damage for that round
*/
void ProgressScreen::Render()
{
	SDL_SetRenderDrawColor(GameEngine::Instance()->GetRenderer(), 64, 64, 128, 128);

	SDL_Rect rect = { 256, 128, 512, 512 };
	SDL_RenderFillRect(GameEngine::Instance()->GetRenderer(), &rect);

	btn->Render();

	string intro = "Round Result:";
	string msg = "";

	if (GameEngine::Instance()->GetGM()->GetPlayer() != nullptr) {
		msg = "Total Damage: " + to_string(GameEngine::Instance()->GetGM()->GetPlayer()->GetDmgDealt());

	}
	ScreenState::RenderFont(true, intro.c_str(), 400, 150);

	ScreenState::RenderFont(true, msg.c_str(), 350, 200);

	ScreenState::Render();

}


void ProgressScreen::Exit()
{

	cout << "Exiting progress..." << endl;

	delete btn;
	btn = nullptr;
}

