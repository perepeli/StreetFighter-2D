#pragma once
#include "HadoukenAOE.h"
//#include "Player.h"

HadoukenAOE::HadoukenAOE(SDL_Texture* tex, double x, double y, double vel)

	: SpriteExAnimated(tex, x, y, 0, 1, 4, 20.00f)
{
	m_DX = 1;
	spriteSrcRect = { 0,0,70,80 };
	spriteDestRect = { (int)(isFlipped ? m_X + 50 : m_X - 50), (int)(m_Y)  ,100,120 };
	m_dRadius = 8;
	m_velX = vel;
	m_velY = vel;
	AddAnimState("Projectile", AnimStateDefinition(4, 2, 120, true));

	//
	isFlipped = true;
	// vertical
	isVertical = true;
}

void HadoukenAOE::Update()
{
	if (!isFlipped) {
		m_Y -= m_velY;
	}
	else {
		m_Y += m_velY;
	}



	this->spriteSrcRect.x = spriteSrcRect.w * m_iFrame;
	this->UpdateDestRect();

	this->PlayState("Projectile");
}

void HadoukenAOE::Render()
{
	this->SpriteExAnimated::Render();
	
}

HadoukenAOE::~HadoukenAOE()
{

}
	