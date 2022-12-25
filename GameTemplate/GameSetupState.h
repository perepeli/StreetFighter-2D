#pragma once
#include "ScreenState.h"
#include <vector>
#include <iostream>
#include "Button.h"
using namespace std;

class GameSetupState :
    public ScreenState
{
private:
	vector<Button*> m_vButtons;
	enum btn { fire, ice,
		dark, light };

public:
	GameSetupState() { }

	void Enter();
	void Exit();
	void Update();
	void Render();
	void Resume() {}

};

