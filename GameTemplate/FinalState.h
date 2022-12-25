#pragma once
#include <iostream>
#include "ScreenState.h"
#include <vector>
#include "Button.h"
using namespace std;

class FinalState : public ScreenState
{
private:
	vector<Button*> m_vButtons;
	int score;
public:
	FinalState() {}
	void Update(); // Method prototype.
	void Render();
	void Enter();
	void Exit();
	void setScore(int s);
	void Resume() { cout << "Resuming Game..." << endl; }

};