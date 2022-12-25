#include "Enemy.h"
#include "GameEngine.h"
#include "Timer.h"


Enemy::Enemy(SDL_Texture* tex, double x, double y, bool z, double vel) : Player(tex, x, y)
{
	isBot = z;
	isFlipped = true;
	m_velX = vel;
	initialXVal = spriteDestRect.x;
	initialYVal = spriteDestRect.y;
	m_velY = 5.5f;
}


void Enemy::UpdatePlayer()
{
	if (currentState == ("Jump"))
	{
		Jump();
	}

	if (opponent != nullptr) {
		//1 in 200 chance that the enemy will use hadouken on each loop cycle
		int shouldHadouken = rand() % 200 + 1;
		if (shouldHadouken == 1) {
			SetAttackCD(true);
			this->PlayState("Hadouken");
		}
		else {
			if (opponent->GetX() < m_X - 50) {
				this->isFlipped = true;
				this->MovePlayer(false);
			}
			else if (opponent->GetX() > m_X + 50) {
				this->isFlipped = false;
				this->MovePlayer(true);
			}
			else if (attackCD == false) {
				/*
				Setting the attack cooldown and randomizing the enemy's attacks
				*/
				SetAttackCD(true);
				int rAttack = rand() % 4 + 1;
				switch (rAttack) {
				case 1: this->PlayState("Punch");
				case 2: this->PlayState("Kick");
				case 3: this->PlayState("Roundhouse");
					//case 4: this->PlayState("Hadouken");
				default:
					this->PlayState("Idle");

				}
			}
			else {
				this->PlayState("Idle");
			}
		}
	}
	else {
		this->PlayState("Idle");
	}


	this->spriteSrcRect.x = spriteSrcRect.w * m_iFrame;
	this->UpdateDestRect();
}
