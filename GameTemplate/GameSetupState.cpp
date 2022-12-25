#include "GameSetupState.h"
#include "GameEngine.h"
#include "EnterNamePopupState.h"
#include "GameLevel1.h"


void GameSetupState::Enter()
{
	cout << "Entering Game Setup State...\n";
	GameEngine::Instance()->SetLeftMouse(false);

	SDL_Rect bgDestRect;
	bgDestRect.x = bgDestRect.y = 0;
	SDL_GetWindowSize(GameEngine::Instance()->GetWindow(), &bgDestRect.w, &bgDestRect.h);

	m_vButtons.push_back(new Button("Img/Players/FireBtn.png", { 0,0,80,120 }, { (int)(bgDestRect.w  * 0.2 - 80), (int)(bgDestRect.h / 2 - 120), 160, 240 }));
	m_vButtons.push_back(new Button("Img/Players/IceBtn.png", { 0,0,80,120 }, { (int)(bgDestRect.w * 0.4 - 80), (int)(bgDestRect.h / 2 - 120), 160, 240 }));
	m_vButtons.push_back(new Button("Img/Players/DarkBtn.png", { 0,0,80,120 }, { (int)(bgDestRect.w * 0.6 - 80), (int)(bgDestRect.h / 2 - 120), 160, 240 }));
	m_vButtons.push_back(new Button("Img/Players/LightBtn.png", { 0,0,80,120 }, { (int)(bgDestRect.w * 0.8 - 80), (int)(bgDestRect.h / 2 - 120), 160, 240 }));
}

void GameSetupState::Update()
{

	// Update buttons. Allows for mouseovers.
	for (int i = 0; i < (int)m_vButtons.size(); i++)
		m_vButtons[i]->Update();

	if (m_vButtons[btn::fire]->Clicked())
	{
		GameEngine::Instance()->GetGM()->SetPlayerSpriteTex(GameEngine::Instance()->LoadTexture("Img/Players/Fire.png"));
		GameEngine::Instance()->GetFSM()->ChangeState(new EnterNamePopupState());

	}

	else if (m_vButtons[btn::ice]->Clicked())
	{
		GameEngine::Instance()->GetGM()->SetPlayerSpriteTex(GameEngine::Instance()->LoadTexture("Img/Players/Ice.png"));
		GameEngine::Instance()->GetFSM()->ChangeState(new EnterNamePopupState());

	}
	else if (m_vButtons[btn::dark]->Clicked()) {
		GameEngine::Instance()->GetGM()->SetPlayerSpriteTex(GameEngine::Instance()->LoadTexture("Img/Players/Dark.png"));
		GameEngine::Instance()->GetFSM()->ChangeState(new EnterNamePopupState());

	}
	else if (m_vButtons[btn::light]->Clicked()) {
		GameEngine::Instance()->GetGM()->SetPlayerSpriteTex(GameEngine::Instance()->LoadTexture("Img/Players/Light.png"));
		GameEngine::Instance()->GetFSM()->ChangeState(new EnterNamePopupState());

	}



}

void GameSetupState::Render()
{

	SDL_SetRenderDrawColor(GameEngine::Instance()->GetRenderer(), 255, 128, 0, 255);
	SDL_RenderClear(GameEngine::Instance()->GetRenderer());
	for (int i = 0; i < (int)m_vButtons.size(); i++)
		m_vButtons[i]->Render();

	ScreenState::Render();
}

void GameSetupState::Exit()
{
	cout << "Exiting Game Setup State...\n";

	for (int i = 0; i < (int)m_vButtons.size(); i++)
	{
		delete m_vButtons[i];
		m_vButtons[i] = nullptr;
	}
	m_vButtons.clear();
	m_vButtons.shrink_to_fit();
}