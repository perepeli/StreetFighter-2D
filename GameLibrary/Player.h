#pragma once

#include "SpriteEx.h"
#include <vector>
#include "Hadouken.h"
#include "ProgressBar.h"
using namespace std;

/*
Player has 100 hit points to start, and 3 lives
Callback functions are applied on the players attack animations
The play has an immune status if they are crouched
Player also has attack cooldown, and subsequently enemy
Player had member variables for damage dealt, for progression
as well as a variable for their opponent, player performs actions on opponent,
while game manager handles logic behind the actions
*/
class Player : public SpriteExAnimated
{
private:

protected:
	double m_velX = 0,
		m_velY = 0,
		m_velMax = 10;
	double initialYVal;
	double initialXVal;
	bool attackCD = false;
	int hitPoints = 100;
	int lives = 3;

	bool isImmune;
	int dmgDealt = 0;
	Player* opponent;
	Hadouken* hadouken;
	virtual void UpdatePlayer();
	bool isBot = false;
	void OnJumpAnimationComplete();
	void OnSomethingComplete(int x);
	void Jump();
	void OnAttackFrame();
	void TriggerKickDamage();
	void TriggerPunchDamage();
	void TriggerRoundhouseDamage();
	void TriggerHadouken();
	void OnAttackComplete();

public:
	bool GetImmuneStatus() { return isImmune; }
	void SetImmuneStatus(bool b) { this->isImmune = b; }
	ProgressBar* healthBar;
	void SetBotStatus(bool bot) { this->isBot = bot; }
	bool GetBotStatus() { return isBot; }
	virtual void Respawn();
	void HasDied();
	Player(SDL_Texture* tex, double x, double y);
	~Player();
	virtual	void Update(Player* player);
	void SetAttackCD(bool t) { attackCD = t; }
	bool GetAttackCD() { return attackCD; }
	void MovePlayer(bool isFwd);
	void Render();
	int GetHitPoints() { return hitPoints; }
	void SetHitPoints(int pts) { this->hitPoints = pts; }
	void SpawnHadouken();
	void UpdateHadouken();
	void AddDmgDealt(int dmg) { this->dmgDealt += dmg; }
	int GetDmgDealt() { return dmgDealt; }
	void setDmgDealt(int dmg) { this->dmgDealt = dmg; }
	void SetLives(int l) { this->lives = l; }
	int GetLives() { return lives; }
	//	void SetIdle();

};