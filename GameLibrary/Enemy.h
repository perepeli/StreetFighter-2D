#pragma once
#include "Player.h"

class Enemy : public Player
{
public:
	Enemy(SDL_Texture* tex, double x, double y, bool z, double vel);
	//Over-ride the base player class's Update functionality
	void UpdatePlayer() override;

};