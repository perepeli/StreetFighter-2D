#pragma once
#
#include "SpriteEx.h"
#include "GameEngine.h"
#include <iostream>

using namespace std;

class UIInputBox : public SpriteEx
{
private:
	string text;
	SDL_Texture* inputBoxTex;

	SDL_Rect inputBoxSrc;
	SDL_Rect inputBoxDest;

	TTF_Font* m_pFont;

	SDL_Texture* m_pFontTexture;
	SDL_Rect m_rFontRect;

protected:
	
public:
	UIInputBox(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
	void SetText(string text) { this->text = text; }
	string GetText() { return this->text; }
	~UIInputBox();
	void Render();

	void Update();
	void UpdateInputBox();
};

