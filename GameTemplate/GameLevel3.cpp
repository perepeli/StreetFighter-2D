#include "GameLevel3.h"
#include "MainMenuState.h"
#include "ProgressScreen.h"
#include "PauseMenuPopupState.h"
#include "FinalState.h"
#include "GameEngine.h"

/*
Timeout to hide the info message after a set time
*/
Uint32 MessageTimeout3(Uint32 interval, void* st) {
	GameState* temp = (GameState*)st;
	temp->SetRenderMessage(false);
	return 0;
}

/*
A Timeout to go back to the main menu when the player loses
*/
Uint32 MainMenuTimeout3(Uint32 interval, void* st) {
	GameState* temp = (GameState*)st;
	temp->SetRenderMessage(false);
	GameEngine::Instance()->GetFSM()->ChangeState(new MainMenuState());
	return 0;
}


/*
Timeout to go to the next screen when the player wins
*/
Uint32 RoundEndTimeout3(Uint32 interval, void* st) {
	GameState* temp = (GameState*)st;
	temp->SetRenderMessage(false);
	GameEngine::Instance()->GetFSM()->ChangeState(new FinalState());
	return 0;
}

void GameLevel3::Enter()
{
	bgSpriteTex = GameEngine::Instance()->LoadTexture("Img/Levels/SF_Level_3.png");
	mainSpriteTex = GameEngine::Instance()->GetGM()->GetPlayerSpriteTex();
	int temp = rand() % 4 + 1;

	switch (temp) {
	case 1:
		mainSpriteTex2 = GameEngine::Instance()->LoadTexture("Img/Players/Ice.png");
		break;
	case 2:
		mainSpriteTex2 = GameEngine::Instance()->LoadTexture("Img/Players/Fire.png");
		break;
	case 3:
		mainSpriteTex2 = GameEngine::Instance()->LoadTexture("Img/Players/Light.png");
		break;
	case 4:
		mainSpriteTex2 = GameEngine::Instance()->LoadTexture("Img/Players/Dark.png");
		break;
	default:
		mainSpriteTex2 = GameEngine::Instance()->LoadTexture("Img/Players/Ice.png");
	}
	// aoe logic sprite
	aoeSpriteTex = GameEngine::Instance()->LoadTexture("Img/Players/Dark.png");

	msgTex = GameEngine::Instance()->LoadTexture("Img/level3intro.png");

	m_pFont = TTF_OpenFont("Font/LTYPE.TTF", 30);

	SDL_Rect bgSrcRect;
	bgSrcRect.x = bgSrcRect.y = 0;
	SDL_QueryTexture(bgSpriteTex, NULL, NULL, &bgSrcRect.w, &bgSrcRect.h);

	SDL_Rect bgDestRect;
	bgDestRect.x = bgDestRect.y = 0;
	SDL_GetWindowSize(GameEngine::Instance()->GetWindow(), &bgDestRect.w, &bgDestRect.h);

	bg = new SpriteEx(bgSpriteTex, bgSrcRect, bgDestRect);

	userMsg = new SpriteEx(msgTex, { 0, 0, 500, 150 }, { (int)bgDestRect.w / 2 - 250, (int)bgDestRect.h / 2 - 75, 500, 150 });

	enemy = new Enemy(mainSpriteTex2, bgDestRect.w * 0.1, bgDestRect.h - 100, true, 1.2f);
	player = new Player(mainSpriteTex, bgDestRect.w * 0.9, bgDestRect.h - 100);

	progressBarBgTex = GameEngine::Instance()->LoadTexture("Img/progressbarbg.png");

	player->healthBar = new ProgressBar(progressBarBgTex, { 0, 0, 350, 50 }, { int(lroundf(bgDestRect.w - 350)), 0, 350, 50 }, player->GetHitPoints());
	player->healthBar->UpdateCurrentValue(player->GetHitPoints());

	enemy->healthBar = new ProgressBar(progressBarBgTex, { 0, 0, 350, 50 }, { int(lroundf(0)), 0, 350, 50 }, enemy->GetHitPoints());
	enemy->healthBar->UpdateCurrentValue(enemy->GetHitPoints());

	GameEngine::Instance()->GetGM()->SetEnemy(enemy);
	GameEngine::Instance()->GetGM()->SetPlayer(player);

	GameEngine::Instance()->GetAM()->LoadLocalSound("Aud/punch.mp3", "hit");
	GameEngine::Instance()->GetAM()->LoadLocalSound("Aud/jump.wav", "jump");
	GameEngine::Instance()->GetAM()->LoadLocalSound("Aud/thunk.wav", "explode");
	GameEngine::Instance()->GetAM()->LoadLocalSound("Aud/hadouken.wav", "hadouken");
	GameEngine::Instance()->GetAM()->LoadLocalSound("Aud/respawn.wav", "respawn");

	GameEngine::Instance()->GetAM()->LoadLocalMusic("Aud/game.mp3", "gameMusic");
	GameEngine::Instance()->GetAM()->PlayLocalMusic("gameMusic");

	renderMsg = true;
	TimerID messageTimer = Timer::Instance()->StartTimer(3000, MessageTimeout3, (void*)this);
}

void GameLevel3::Update() {
	if (isGameOver) {
		SDL_Rect bgDestRect;
		bgDestRect.x = bgDestRect.y = 0;
		SDL_GetWindowSize(GameEngine::Instance()->GetWindow(), &bgDestRect.w, &bgDestRect.h);

		if (player->GetLives() > enemy->GetLives()) {
			msgTex = GameEngine::Instance()->LoadTexture("Img/winnermsg.png");
			userMsg = new SpriteEx(msgTex, { 0, 0, 500, 150 }, { (int)bgDestRect.w / 2 - 250, (int)bgDestRect.h / 2 - 75, 500, 150 });
			TimerID roundEndTimeout = Timer::Instance()->StartTimer(3000, RoundEndTimeout3, (void*)this);
		}
		else {
			msgTex = GameEngine::Instance()->LoadTexture("Img/losermsg.png");
			userMsg = new SpriteEx(msgTex, { 0, 0, 600, 150 }, { (int)bgDestRect.w / 2 - 250, (int)bgDestRect.h / 2 - 75, 600, 150 });
			TimerID messageTimer = Timer::Instance()->StartTimer(3000, MainMenuTimeout3, (void*)this);

		}

		renderMsg = true;
		return;
	}
	else {
		if (enemy != nullptr && player != nullptr) {
			if (enemy->GetLives() == 0 || player->GetLives() == 0) {
				isGameOver = true;
			}
			else {
				if (GameEngine::Instance()->KeyDown(SDL_SCANCODE_ESCAPE) == 1)
				{
					GameEngine::Instance()->GetFSM()->PushState(new PauseMenuPopupState());
					return; //to make sure we don't run the game in background while pause menu shows
				}

				// aoe logic
				if (hadoukenAOE == nullptr) {
					int randomX = 9 + (rand() % (int)(990 - 9 + 1));
					hadoukenAOE = new HadoukenAOE(aoeSpriteTex, randomX, -100, 10.0f);
				}
				else
				{
					hadoukenAOE->Update();

					bool playerWasDamagedByAOE = false;

					if (GameEngine::Instance()->GetGM()->RectCollisionTest(player->getDestRect(), hadoukenAOE->getDestRect())) { // check AOE collision for player
						playerWasDamagedByAOE = true;
						GameEngine::Instance()->GetAM()->PlayLocalSound("explode");
						GameEngine::Instance()->GetGM()->TakeDamage(player, -50);
					}


					if (playerWasDamagedByAOE || hadoukenAOE->GetY() < -100 || hadoukenAOE->GetY() > 800) {
						delete hadoukenAOE;
						hadoukenAOE = nullptr;

					}
				}

				enemy->Update(player);
				player->Update(enemy);

			}
		}

	}
}
