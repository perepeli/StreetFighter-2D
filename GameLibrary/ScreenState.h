#pragma once

#include <SDL.h>
#include <sdl_ttf.h>
#include <map>
#include <iostream>
#include "SDL_mixer.h"  //required for audio
#include "Button.h"

class ScreenState // This is the abstract base class for all specific states.
{
protected:
	TTF_Font* m_pFont;
	SDL_Texture* m_pFontTexture;
	SDL_Rect m_rFontRect;
	Button* btn;

public:
	virtual void Update() = 0; // A 'pure virtual' method.
	virtual void Render();
	void RenderFont(bool isRefreshText, const char* text, int x, int y);
	virtual void Enter() = 0;
	virtual void Exit() = 0;
	virtual void Resume() = 0;
};