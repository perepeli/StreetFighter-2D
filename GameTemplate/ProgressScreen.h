#pragma once
#include <iostream>
#include "ScreenState.h"
#include <vector>
#include "Button.h"
using namespace std;

/*
The progress screen renders the players total damage for that round.
Intermission screen between game level transitions
*/
class ProgressScreen : public ScreenState
{
private:
	vector<Button*> m_vButtons;
	int score;
protected:

public:

	ProgressScreen() {}
	void Update(); // Method prototype.
	void Render();
	void Enter();
	void Exit();
	void Resume() { cout << "Resuming Game..." << endl; }

};