#include "PauseMenuPopupState.h"
#include <iostream>
#include "GameEngine.h"
#include "MainMenuState.h"
using namespace std;

// Begin PauseState
void PauseMenuPopupState::Enter()
{
	cout << "Entering Pause..." << endl;
	m_vButtons.push_back(new Button("Img/resume.png", { 0,0,200,80 }, { 412,200,200,80 }));
	m_vButtons.push_back(new Button("Img/exit.png", { 0,0,400,100 }, { 412,400,200,80 }));
	//pause music
	GameEngine::Instance()->GetAM()->ToggleMusic();
}

void PauseMenuPopupState::Update()
{
	// Update buttons. Allows for mouseovers.
	for (int i = 0; i < (int)m_vButtons.size(); i++)
		m_vButtons[i]->Update();

	//close the pause menu popup
	if (m_vButtons[btn::resume]->Clicked())
	{
		GameEngine::Instance()->GetFSM()->PopState();
	}
	//else if exit was clicked, we need to go back to main menu
	else if (m_vButtons[btn::exit]->Clicked())
	{
		GameEngine::Instance()->GetFSM()->Clean(); // Clear all states, including GameState on bottom.
		//go back to main menu
		GameEngine::Instance()->GetFSM()->ChangeState(new MainMenuState());
	}


}


void PauseMenuPopupState::Render()
{

	//GameEngine::Instance()->GetFSM()->GetStates().front()->Render();
	//SDL_SetRenderDrawBlendMode(GameEngine::Instance()->GetRenderer(), SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(GameEngine::Instance()->GetRenderer(), 64, 64, 128, 128);

	//draw background 
	SDL_Rect rect = { 256, 128, 512, 512 };
	SDL_RenderFillRect(GameEngine::Instance()->GetRenderer(), &rect);

	//draw the buttons
	for (int i = 0; i < (int)m_vButtons.size(); i++)
		m_vButtons[i]->Render();


	ScreenState::Render();

}


void PauseMenuPopupState::Exit()
{

	cout << "Exiting Pause..." << endl;

	//resume music
	GameEngine::Instance()->GetAM()->ToggleMusic();

	for (int i = 0; i < (int)m_vButtons.size(); i++)
	{
		delete m_vButtons[i];
		m_vButtons[i] = nullptr;
	}
	m_vButtons.clear();
	m_vButtons.shrink_to_fit();
}

