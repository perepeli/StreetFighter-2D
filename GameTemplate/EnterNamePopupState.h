#pragma once
#include <iostream>
#include "ScreenState.h"
#include <vector>
#include "UIInputBox.h"
#include "Button.h"

using namespace std;

/*
The progress screen renders the players total damage for that round.
Intermission screen between game level transitions
*/
class EnterNamePopupState : public ScreenState
{
private:
	string name;
	SDL_Texture* inputBgTex;
	UIInputBox* inputBox;

protected:

public:

	EnterNamePopupState() {}
	void Update(); // Method prototype.
	void Render();
	void Enter();
	void Exit();
	void Resume() { cout << "Resuming Game..." << endl; }

};