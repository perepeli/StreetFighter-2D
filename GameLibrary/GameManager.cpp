#pragma once
#include "GameManager.h"
#include "GameEngine.h"
#include "Timer.h"

Uint32 ResetStance(Uint32 interval, void* st) {
	Player* temp = (Player*)st;
	//temp->PlayState("Idle");
	temp->SetAttackCD(false);

	return 0;
}

GameManager::GameManager() {

	/*mainSpriteTex = GameEngine::Instance()->LoadTexture("Img/Players/PlayerKenSprite2.png");
	mainSpriteTex2 = GameEngine::Instance()->LoadTexture("Img/Players/PlayerKenSprite.png");
	enemy = new Enemy(mainSpriteTex2, bgDestRect.w * 0.3, bgDestRect.h - 100, false);
	player = new Player(mainSpriteTex, bgDestRect.w * 0.6, bgDestRect.h - 100);*/
}

/*
Collision detection between two rectangles
*/
bool GameManager::RectCollisionTest(SDL_Rect* a, SDL_Rect* b) {

	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	int bufferZone = 20;
	leftA = a->x;
	rightA = a->x + a->w;
	topA = a->y;
	bottomA = a->y + a->h;

	leftB = b->x;
	rightB = b->x + b->w;
	topB = b->y;
	bottomB = b->y + b->h;

	leftA, rightA, leftB, rightB -= bufferZone;

	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	return true;
}

/*
If we play against a bot enemy, they have a defence mechanism, randomly
decides whether to take damage or defend, as well as whether the
defence is by jump, or crouch
*/
void GameManager::TakeDamage(Player* player, int dmg) {

	if (player->GetBotStatus() == true) {
		int temp = rand() % 4 + 1;
		if (temp == 2) {
			int temp2 = rand() % 2 + 1;
			if (temp2 == 2) {
				player->PlayState("Crouch");
			}
			else {
				player->PlayState("Jump");
			}

			TimerID resetStanceTimer = Timer::Instance()->StartTimer(1500, ResetStance, (void*)player);

			GameEngine::Instance()->GetAM()->PlayLocalSound("immune");
			return;
		}
	}
	/*
	The player also has an immunity feature, if they crouch they will not take damage
	*/
	if (player->GetImmuneStatus() != true) {
		if (player->GetHitPoints() + dmg > 0) {
			player->SetHitPoints(player->GetHitPoints() + dmg);
			player->healthBar->UpdateCurrentValue(player->GetHitPoints());
		}
		else {
			player->HasDied();
		}
	}
	else {
		GameEngine::Instance()->GetAM()->PlayLocalSound("immune");
	}
}

void GameManager::CleanUp() {
	enemy = nullptr;
	delete enemy;
	player = nullptr;
	delete player;
}