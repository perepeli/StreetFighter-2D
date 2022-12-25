#pragma once
#include "Hadouken.h"
#include "Player.h"

Hadouken::Hadouken(SDL_Texture* tex, double x, double y, double vel)

	: SpriteExAnimated(tex, x, y, 0, 1, 4, 20.00f)
{
	m_DX = 1;
	spriteSrcRect = { 0,0,70,80 };
	spriteDestRect = { (int)(isFlipped ? m_X + 50 : m_X - 50), (int)(m_Y)  ,100,120 };
	m_dRadius = 8;
	m_velX = vel;
	AddAnimState("Projectile", AnimStateDefinition(4, 2, 120, true));

}

void Hadouken::Update()
{
	if (isFlipped) {
		m_X -= m_velX;
	}
	else {
		m_X += m_velX;
	}

	this->spriteSrcRect.x = spriteSrcRect.w * m_iFrame;

	this->UpdateDestRect();
}

Hadouken::~Hadouken()
{


}
