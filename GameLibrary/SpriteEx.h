#pragma once
#include "SDL.h"
#include <iostream>
#include <map>
#include <functional>

struct AnimStateDefinition
{
	short rowIndex;
	short frames;
	short delay;
	//if this animation loopable?
	bool isLoopable=false;

	//can this animation state be interrupted?
	//if false, then this animation state will have to play 
	//fully before we switch to another state
	bool canInterrupt=false;  //not being used currently but you can add this functionality yourself by modifying PlayState function

	//call-back function reference
	std::function<void()> onAnimComplete;
	std::function<void()> TriggerActionOnFrame;
	std::function<void(int)> onSomethingComplete;

	void RegisterOnSomethingCompletedCallback(std::function<void(int)> cb)
	{
		onSomethingComplete = cb;
	}


//if our function was returning int, and taking one argument of bool type
//std::function<int(bool)> 
//if our function returned int, and took int two ints:
//std::function<int(int,int)>  


	void RegisterOnAnimCompleteCallback(std::function<void()> cb)
	{
		onAnimComplete = cb;
	}
	
	/*Potential solution for Lab 4*/
	std::function<void()> onAnimFrameComplete;

	int frameNumToCheckForCB;

	void RegisterActionOnFrame(std::function<void()> cb, int frameNumberToCheck)
	{
		TriggerActionOnFrame = cb;
		frameNumToCheckForCB = frameNumberToCheck;
	}



	AnimStateDefinition(){}
	AnimStateDefinition(short rm, short cm, short del,bool loop = false, bool interrupt = false)
		: rowIndex(rm), frames(cm), delay(del), isLoopable(loop), canInterrupt(interrupt) {}

};

//this base class will render just one static sprite
class SpriteEx
{
protected:
	SDL_Rect spriteSrcRect; //which part of the spritesheet we would like to render
	SDL_Rect spriteDestRect; //the position on the screen we would like to render this sprite at
	SDL_Texture *texture;
	double angle;//the angle to display sprite (in degrees)
	double m_X, //x coord
		m_Y, //Y coord
		m_DX, //the change in x coord
		m_DY, //the change in Y coordinate
		m_dSpeed; //speed in pixels to move per change

	double m_dRadius; //radius of the sprite's circle bounds
public:
	SpriteEx() {}
	SpriteEx(SDL_Texture *tex, SDL_Rect srcRect, SDL_Rect dstRect)
	{
		texture = tex;
		spriteSrcRect = srcRect;
		spriteDestRect = dstRect;
	}

	SDL_Rect* getDestRect() {
		return &spriteDestRect;
	}

	bool isFlipped = false;
	
	//aoe logic
	bool isVertical = false;

	void Render();

	void UpdateDestRect();

	double GetRadius() { return m_dRadius; }
	double GetX() { return m_X; }
	double GetY() { return m_Y; }
};
 
//this is the animated version of the Sprite class
class SpriteExAnimated : public SpriteEx
{
private:
	void AnimateRange(AnimStateDefinition asd);

	bool isAnimFinished = false;
	
protected:

	int m_iSprite = 0, //which sprite to display for animation
		m_iSpriteMax, //how many sprites in total for this animation
		m_iFrame = 0, //which frame we are at now
		m_iFrameMax; //number of frames for this sprite

	std::string currentState;

//Stores various animation states for this spritesheet
	std::map<std::string, AnimStateDefinition> animStates;
	
	unsigned int _LastTick = SDL_GetTicks();

	unsigned int GetLastTick() { return _LastTick; }
	void UpdateTick() { _LastTick = SDL_GetTicks(); }

public:
	void Animate();


	void AddAnimState(std::string stateName, AnimStateDefinition asd);

void PlayState(std::string stateName);

	SpriteExAnimated(SDL_Texture* tex, double x, double y,
		double a, int frameMax, int spriteMax, double speed);


};


