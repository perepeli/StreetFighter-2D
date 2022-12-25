#pragma once
#include "GameManager.h"
#include "Player.h"
#include "SDL_mixer.h"
#include "Enemy.h"

#include <iostream>
using namespace std;

/*
GameManager has a player and opponent, exists on the Game Instance scope (member of Game class)
manages functionality for collision detection, damage logic, as well as keeping a state of the current level
*/
class GameManager
{
protected:
	string playerName;
	Player* player;
	Enemy* enemy;
	int level = 1;
	SDL_Texture* playerSpriteTex;
public:
	GameManager();
	void SetPlayerSpriteTex(SDL_Texture* tex) { this->playerSpriteTex = tex; }
	SDL_Texture* GetPlayerSpriteTex() { return this->playerSpriteTex; }
	Player* GetPlayer() { return player; }
	Enemy* GetEnemy() { return enemy; }
	string GetName() { return this->playerName; }
	void SetName(string name) { this->playerName = name; }
	void SetPlayer(Player* player) { this->player = player; }
	void SetEnemy(Enemy* enemy) { this->enemy = enemy; }
	void SetLevel(int lvl) { this->level = lvl; }
	int GetLevel() { return this->level; }
	void TakeDamage(Player* player, int dmg);
	void CleanUp();
	void CheckCollision();
	bool RectCollisionTest(SDL_Rect* rect, SDL_Rect* rec);

};
