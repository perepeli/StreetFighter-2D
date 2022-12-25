
#include "SDL.h"
#include "GameEngine.h"
#include "MainMenuState.h"

int main(int argc, char* argv[])
{
	//in a non-singleton world, we would have had to create a game object like this
	//and we would have used game->Init() or game->HandleEvents() etc
	//but when using a singleton, we don't create an object explicitly..
	//we instead use 'Instance()' function and access the class members via it

	if (!GameEngine::Instance()->Init("SDL Framework", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 1024, 768, 0))
		return -1; //close the application if initialization fails

	GameEngine::Instance()->GetFSM()->ChangeState(new MainMenuState());

	while (GameEngine::Instance()->IsRunning())
	{
		GameEngine::Instance()->HandleEvents();
		GameEngine::Instance()->Update();
		GameEngine::Instance()->Render();
		SDL_Delay(10); //delay of 10 ms after every loop iteration
	}

	GameEngine::Instance()->Clean();

	return 0;

}