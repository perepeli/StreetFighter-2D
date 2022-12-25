#pragma once
#include "ProgressBar.h"
#include "ScreenState.h"

class LoadingState : public ScreenState
{

private:
	ProgressBar* progressBar;
	SDL_Texture* progressBarBgTex;
	int progressCounter = 0;
	bool progressCooldown = true;
public:
	LoadingState() { }
	void SetProgressCooldown(bool b) { this->progressCooldown = b; }
	bool GetProgressCooldown() { return this->progressCooldown; }

	void Enter();
	void Exit();
	void Update();
	void Render();
	void Resume() {}
};