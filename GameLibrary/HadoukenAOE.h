#pragma once
#include "SpriteEx.h"

/*
Hadouken object AOE
*/
class HadoukenAOE : public SpriteExAnimated
{
protected:
	double m_velX = 0;
	double m_velY = 0;
public:
	HadoukenAOE(SDL_Texture* tex, double x, double y, double vel);
	~HadoukenAOE();


	void Update();
	void Render();
};