#include "ProgressBar.h"
#include "GameEngine.h"
#include <algorithm> //for min/max functions



ProgressBar::ProgressBar(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, float max)
	: SpriteEx(tex, src, dest)
{
	//this->currentVal = max;
	this->SetMaxValue(max);
	fillSrc = { 0, 0, 330, 30 };
	fillDest = { dest.x + 10, dest.y + 10, (int)((330 / max) * currentVal), 30 };
	fill = GameEngine::Instance()->LoadTexture("Img/progressbarfill.png");
}

ProgressBar::~ProgressBar()
{


}


void ProgressBar::Render()
{
	this->SpriteEx::Render(); //invoke the base class's Render
	SDL_RenderCopy(GameEngine::Instance()->GetRenderer(), fill, &fillSrc, &fillDest);
}


void ProgressBar::Update()
{
	this->UpdateProgressBar();
}

/*
Update the progress bar based on the player's current and max values
*/
void ProgressBar::UpdateProgressBar()
{
	int temp1 = fillDest.x;
	int temp2 = fillDest.y;
	this->fillDest = SDL_Rect{ temp1, temp2, int(lroundf((330 / maxVal) * currentVal)), 30 };
}

void ProgressBar::UpdateCurrentValue(float val)
{
	this->currentVal = val;
}

void ProgressBar::SetMaxValue(float max) {
	maxVal = max;
	cout << "The max value has been set: " << maxVal << "\n";
}


float ProgressBar::GetCurrentValue()
{
	return currentVal;
}

float ProgressBar::GetMaxValue() {
	return maxVal;
}
