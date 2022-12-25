#include "UIInputBox.h"


UIInputBox::UIInputBox(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest)
	: SpriteEx(tex, src, dest) 
{
	/*inputBoxSrc = src;
	inputBoxDest = dest;
	inputBoxTex = tex;*/
	m_pFont = TTF_OpenFont("game_over.ttf", 100);

}


UIInputBox::~UIInputBox()
{


}


void UIInputBox::Render()
{
	this->SpriteEx::Render(); //invoke the base class's Render

	if (GameEngine::Instance()->GetInputText().length() > 0) {
		SDL_Color textColor = { 255,255,255,0 };//white color
		SDL_Surface* fontSurface = TTF_RenderText_Blended_Wrapped(m_pFont, GameEngine::Instance()->GetInputText().c_str(),
			textColor, spriteDestRect.w);

		SDL_DestroyTexture(m_pFontTexture); //need to de-allocate previous font texture
		m_pFontTexture = SDL_CreateTextureFromSurface(GameEngine::Instance()->GetRenderer(), fontSurface);
		m_rFontRect = { spriteDestRect.x, spriteDestRect.y, fontSurface->w, fontSurface->h };


		SDL_RenderCopy(GameEngine::Instance()->GetRenderer(), m_pFontTexture, 0, &m_rFontRect);
	}

	/*SDL_RenderCopy(GameEngine::Instance()->GetRenderer(), inputBoxTex, &inputBoxSrc, &inputBoxDest); */
}


void UIInputBox::Update()
{
	this->UpdateInputBox();
}

/*
Update the progress bar based on the player's current and max values
*/
void UIInputBox::UpdateInputBox()
{
	//this->SetText(GameEngine::Instance()->GetInputText());
}
 
