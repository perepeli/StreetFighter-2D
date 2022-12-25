#pragma once
#include "SpriteEx.h"

/*
The progress bar tracks the players health points
player has a progress bar.
*/
class ProgressBar : public SpriteEx
{
protected:
	float maxVal;
	float currentVal;
	SDL_Texture* fill;
	SDL_Rect fillSrc;
	SDL_Rect fillDest;
	void UpdateProgressBar();
public:
	ProgressBar(SDL_Texture* bg, SDL_Rect src, SDL_Rect dest, float max);
	~ProgressBar();
	void UpdateCurrentValue(float val);
	float GetCurrentValue();
	void SetMaxValue(float max);
	float GetMaxValue();
	virtual void Update();
	void Render();
};

