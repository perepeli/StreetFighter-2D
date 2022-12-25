#include "FinalState.h"
#include <iostream>
#include "GameEngine.h"
#include "GameLevel1.h"
#include "MainMenuState.h"

using namespace std;

void FinalState::setScore(int s) {
	score = s;
}

// Begin PauseState
void FinalState::Enter()
{
	score = 0;
	m_pFont = TTF_OpenFont("game_over.ttf", 100);

	cout << "Entering FinalState..." << endl;
	btn = new Button("Img/exit.png", { 0,0,400,100 }, { 412,300,200,80 });

}

void FinalState::Update()
{
	// Update buttons. Allows for mouseovers.
	btn->Update();

	//close the pause menu popup
	if (btn->Clicked())
	{

		GameEngine::Instance()->GetFSM()->ChangeState(new MainMenuState());
	}
	//else if exit was clicked, we need to go back to main menu
/*	else if (m_vButtons[btn::exit]->Clicked())
	{
		GameEngine::Instance()->GetFSM()->Clean(); // Clear all states, including GameState on bottom.
		//go back to main menu
		GameEngine::Instance()->GetFSM()->ChangeState(new MainMenuState());
	}*/

}


/**
Rendering the congratulatory message
*/
void FinalState::Render()
{
	SDL_SetRenderDrawColor(GameEngine::Instance()->GetRenderer(), 64, 64, 128, 128);

	SDL_Rect rect = { 256, 128, 512, 512 };
	SDL_RenderFillRect(GameEngine::Instance()->GetRenderer(), &rect);

	btn->Render();

	/*
	for (int i = 0; i < (int)m_vButtons.size(); i++)
		m_vButtons[i]->Render();*/
	string msg = "You beat the game!";
	string pts = "Congratulations!";

	ScreenState::RenderFont(true, pts.c_str(), 320, 150);
	ScreenState::RenderFont(true, msg.c_str(), 350, 200);

	ScreenState::Render();

}


void FinalState::Exit()
{

	cout << "Exiting Pause..." << endl;
	/*
	for (int i = 0; i < (int)m_vButtons.size(); i++)
	{
		delete m_vButtons[i];
		m_vButtons[i] = nullptr;
	}*/

	delete btn;
	btn = nullptr;
	/*
	m_vButtons.clear();
	m_vButtons.shrink_to_fit();*/
}

