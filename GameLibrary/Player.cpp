#include "Player.h"
#include "GameEngine.h"
#include <algorithm> //for min/max functions
#include "Timer.h"

/*
Timer which controls the cooldown of the player's attacks.
*/
Uint32 AttackCooldown(Uint32 interval, void* st) {
	Player* temp = (Player*)st;
	temp->SetAttackCD(false);

	return 0;
}

/**
Timer to respawn the player after a set time
*/
Uint32 RespawnTimer(Uint32 interval, void* st) {
	Player* temp = (Player*)st;
	if (temp->GetLives() > 0) {
		temp->Respawn();
		temp->healthBar->UpdateCurrentValue(temp->healthBar->GetMaxValue());
	}

	return 0;
}


Player::Player(SDL_Texture* tex, double x, double y)
	: SpriteExAnimated(tex, x, y - 50, 0, 1, 4, 0.1f)
{
	spriteSrcRect = { 0,0,70,80 };
	spriteDestRect = { (int)(m_X),(int)(m_Y)  ,90,100 };

	initialXVal = spriteDestRect.x;
	initialYVal = spriteDestRect.y;
	m_velX = 1.9f;
	m_velY = 5.5f;
	m_dRadius = 50;

	AddAnimState("Punch", AnimStateDefinition(2, 3, 120));
	AddAnimState("Kick", AnimStateDefinition(6, 5, 120));
	AddAnimState("Roundhouse", AnimStateDefinition(7, 5, 120));
	AddAnimState("Hadouken", AnimStateDefinition(0, 4, 120));
	AddAnimState("Idle", AnimStateDefinition(1, 4, 120, true));
	AddAnimState("Move", AnimStateDefinition(3, 5, 120, true, true));
	AddAnimState("Jump", AnimStateDefinition(8, 7, 120));
	AddAnimState("Crouch", AnimStateDefinition(9, 1, 120, false, false));

	/*
	Registering callback functions and triggered events on frame
	*/
	animStates["Kick"].RegisterActionOnFrame(
		std::bind(&Player::TriggerKickDamage, this), 3);

	animStates["Punch"].RegisterActionOnFrame(
		std::bind(&Player::TriggerPunchDamage, this), 2);

	animStates["Roundhouse"].RegisterActionOnFrame(
		std::bind(&Player::TriggerRoundhouseDamage, this), 3);

	animStates["Kick"].RegisterOnAnimCompleteCallback(
		std::bind(&Player::OnAttackComplete, this));

	animStates["Punch"].RegisterOnAnimCompleteCallback(
		std::bind(&Player::OnAttackComplete, this));

	animStates["Roundhouse"].RegisterOnAnimCompleteCallback(
		std::bind(&Player::OnAttackComplete, this));

	animStates["Hadouken"].RegisterOnAnimCompleteCallback(
		std::bind(&Player::OnAttackComplete, this));

	animStates["Hadouken"].RegisterActionOnFrame(
		std::bind(&Player::TriggerHadouken, this), 3);

	animStates["Jump"].RegisterOnAnimCompleteCallback
	(std::bind(&Player::OnJumpAnimationComplete, this));
	
}

/*
Function to hide the player from screen when set the respawn timer upon death
*/
void Player::HasDied() {
	m_Y = -200;
	this->healthBar->UpdateCurrentValue(0);
	TimerID respawnTimer = Timer::Instance()->StartTimer(300, RespawnTimer, (void*)this);
	if (lives - 1 >= 0) {
		lives -= 1;
	}
}

/*
Function to respawn the player to their initial coordinates and hit point value
*/
void Player::Respawn() {
	SDL_Rect bgDestRect;
	bgDestRect.x = bgDestRect.y = 0;
	SDL_GetWindowSize(GameEngine::Instance()->GetWindow(), &bgDestRect.w, &bgDestRect.h);
	m_X = initialXVal;
	m_Y = initialYVal;
	GameEngine::Instance()->GetAM()->PlayLocalSound("respawn");

	hitPoints = 100;
}

/*
Spawning a new hadouekn, triggered by TriggerHadouken() function
*/
void Player::SpawnHadouken()
{
	hadouken = new Hadouken(texture, m_X, m_Y, 5.5f);
	GameEngine::Instance()->GetAM()->PlayLocalSound("hadouken");

	cout << "spawned hadouken" << endl;

}

/*
Function to trigger the hadouken spawn
*/
void Player::TriggerHadouken() {
	cout << "hadouken triggered" << endl;
	attackCD = true;
	this->SpawnHadouken();
	TimerID playerAttackCDTimer = Timer::Instance()->StartTimer(500, AttackCooldown, (void*)this);
}

/*
Function to trigger damage to the opponent on the specified frame
*/
void Player::TriggerKickDamage() {
	if (GameEngine::Instance()->GetGM()->RectCollisionTest(this->getDestRect(), opponent->getDestRect()))
	{
		cout << "Someone just got KICKED" << endl;

		GameEngine::Instance()->GetGM()->TakeDamage(opponent, -10);
		GameEngine::Instance()->GetAM()->PlayLocalSound("hit");
		dmgDealt += 10;

	}
}

/*
Function to trigger damage to the opponent on the specified frame
*/
void Player::TriggerPunchDamage() {
	if (GameEngine::Instance()->GetGM()->RectCollisionTest(this->getDestRect(), opponent->getDestRect()))
	{
		cout << "Someone just got PUNCHED" << endl;

		GameEngine::Instance()->GetGM()->TakeDamage(opponent, -5);
		GameEngine::Instance()->GetAM()->PlayLocalSound("hit");

		dmgDealt += 5;

	}
}

/*
Function to trigger damage to the opponent on the specified frame
*/
void Player::TriggerRoundhouseDamage() {
	if (GameEngine::Instance()->GetGM()->RectCollisionTest(this->getDestRect(), opponent->getDestRect()))
	{
		cout << "Someone just got ROUNDHOUSED" << endl;

		GameEngine::Instance()->GetGM()->TakeDamage(opponent, -15);
		GameEngine::Instance()->GetAM()->PlayLocalSound("hit");

		dmgDealt += 15;

	}
}
/*
Callback function to reset the attack cooldown timer
*/
void Player::OnAttackComplete()
{
	SetAttackCD(true);
	TimerID playerAttackCDTimer = Timer::Instance()->StartTimer(500, AttackCooldown, (void*)this);
}

Player::~Player()
{


}


void Player::Render()
{

	this->SpriteExAnimated::Render(); //invoke the base class's Render()
	if (hadouken != nullptr) {
		this->hadouken->Render();
	}

	if (healthBar != nullptr) {
		this->healthBar->Render();
	}
}


/*
Updating the players health bar, hadouken, and player itself
*/
void Player::Update(Player* player)
{
	if (opponent == nullptr) {
		if (player != nullptr) {
			opponent = player;
		}
	}

	this->UpdatePlayer();
	this->UpdateHadouken();
	this->healthBar->Update();
}


void Player::Jump()
{
	if (m_iFrame < 3)
		m_Y -= m_velY;
	else if (m_iFrame > 3)
	{
		m_Y += m_velY;
		if (m_Y > initialYVal)
			m_Y = initialYVal;

		//the alternative to use callback, would have been to do the following:	
			//if (m_iFrame >= animStates[currentState].frames)
				//m_Y = preJumpYVal;

	}


}

//Engine must call this function when our jump animation is completed.
void Player::OnJumpAnimationComplete()
{
	cout << "Jump animation is completed. TODO: reset player back to pre-jump Y position.\n";

	if (m_Y > initialYVal)
		m_Y = initialYVal;

}


void Player::MovePlayer(bool isFwd)
{

	if (isFwd)
		m_X += m_velX;
	else
		m_X -= m_velX;

	this->PlayState("Move");
}

/**
 Function to update the hadouken launched by the player
*/
void Player::UpdateHadouken() {
	if (hadouken != nullptr) {
		if (opponent->GetX() < hadouken->GetX()) {
			hadouken->isFlipped = true;
		}
		else {
			hadouken->isFlipped = false;
		}
		if (m_X > 1000 || m_X < 0) {
			delete hadouken;
			hadouken = nullptr;
			return;

		}
		else if (GameEngine::Instance()->GetGM()->RectCollisionTest(hadouken->getDestRect(), opponent->getDestRect()))
		{
			cout << "someone got HADOUKEN'D" << endl;

			GameEngine::Instance()->GetGM()->TakeDamage(opponent, -30);
			GameEngine::Instance()->GetAM()->PlayLocalSound("explode");

			dmgDealt += 30;
			delete hadouken;
			hadouken = nullptr;
			return;
		}

		hadouken->PlayState("Projectile");
		hadouken->Update();

	}
}



void Player::UpdatePlayer()
{
	/*
	Checking to see the opponents x value in relation to the players
	to know whether to flip the sprite so players are facing eachother
	*/
	if (opponent != nullptr) {
		if (opponent->GetX() < m_X) {
			this->isFlipped = true;
		}
		else if (opponent->GetX() > m_X) {
			this->isFlipped = false;
		}

	}

	//if the player crouches, they are immune
	if (this->currentState == "Crouch") {
		isImmune = true;
	}
	else {
		isImmune = false;
	}

	if (GameEngine::Instance()->KeyDown(SDL_SCANCODE_D))
	{
		this->MovePlayer(true);

	}
	else if (GameEngine::Instance()->KeyDown(SDL_SCANCODE_A))
	{
		this->MovePlayer(false);
	}
	else if (GameEngine::Instance()->KeyDown(SDL_SCANCODE_K) && attackCD == false) {
		this->PlayState("Kick");
	}
	else if (GameEngine::Instance()->KeyDown(SDL_SCANCODE_S))
	{
		this->PlayState("Crouch");
	}
	else if (GameEngine::Instance()->KeyDown(SDL_SCANCODE_SPACE))
	{
		this->PlayState("Jump");
	}
	else if (GameEngine::Instance()->KeyDown(SDL_SCANCODE_P) && attackCD == false)
	{
		this->PlayState("Punch");
	}
	else if (GameEngine::Instance()->KeyDown(SDL_SCANCODE_R) && attackCD == false)
	{
		this->PlayState("Roundhouse");
	}
	else if (GameEngine::Instance()->KeyDown(SDL_SCANCODE_H) && attackCD == false)
	{
		this->PlayState("Hadouken");
	}
	else {
		this->PlayState("Idle");
	}

	////compare and see if we are in jump state, and if yes, call Jump....
	if (currentState == ("Jump"))
	{

		Jump();
	}


	this->spriteSrcRect.x = spriteSrcRect.w * m_iFrame;
	this->UpdateDestRect();

}

