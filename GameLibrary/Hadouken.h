#pragma once
#include "SpriteEx.h"

/*
Hadouken object launched by player
member of the player class (player has a hadouken)
*/
class Hadouken : public SpriteExAnimated
{
protected:
	double m_velX = 0;
public:
	Hadouken(SDL_Texture* tex, double x, double y, double vel);
	~Hadouken();


	void Update();
};