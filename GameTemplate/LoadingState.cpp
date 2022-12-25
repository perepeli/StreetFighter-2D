#include "LoadingState.h"
#include "GameEngine.h"
#include "GameLevel1.h"
#include "GameSetupState.h"

Uint32 ProgressDelay(Uint32 interval, void* st) {
	LoadingState* temp = (LoadingState*)st;
	temp->SetProgressCooldown(false);

	return 0;
}


void LoadingState::Enter()
{
	cout << "Entering MainMenu...\n";

	SDL_Rect bgDestRect;
	bgDestRect.x = bgDestRect.y = 0;
	SDL_GetWindowSize(GameEngine::Instance()->GetWindow(), &bgDestRect.w, &bgDestRect.h);
	progressBarBgTex = GameEngine::Instance()->LoadTexture("Img/progressbarbg.png");
	m_pFont = TTF_OpenFont("game_over.ttf", 100);

	progressBar = new ProgressBar(progressBarBgTex, { 0, 0, 350, 50 }
	, { int(lroundf(bgDestRect.w / 2 - 175)), int(lroundf(bgDestRect.h / 2 - 25)), 350, 50 }
	, 6);
	progressBar->UpdateCurrentValue(0);

	TimerID progessDelaytimer = Timer::Instance()->StartTimer(1000, ProgressDelay, (void*)this);
}


void LoadingState::Update()
{
	progressBar->Update();

	if(progressCounter <= 6) {
		if (progressCooldown == false) {
			progressCounter++;
			progressBar->UpdateCurrentValue(progressCounter);
			cout << progressCounter << endl;
			progressCooldown = true;
			TimerID progessDelaytimer = Timer::Instance()->StartTimer(1000, ProgressDelay, (void*)this);

		}
	}
	else {
		GameEngine::Instance()->GetFSM()->ChangeState(new GameLevel1());
	}
}

void LoadingState::Render()
{
	
	SDL_SetRenderDrawColor(GameEngine::Instance()->GetRenderer(), 255, 128, 0, 255);
	SDL_RenderClear(GameEngine::Instance()->GetRenderer());

	progressBar->Render();
	
	string msg = "Loading...";

	ScreenState::RenderFont(true, msg.c_str(), 425, 300);

	ScreenState::Render();

}

void LoadingState::Exit()
{
	cout << "Exiting MainMenu...\n";

	progressBar = nullptr;
	delete progressBar;
}