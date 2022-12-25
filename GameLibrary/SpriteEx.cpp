#include "GameEngine.h"
#include "Timer.h"

void SpriteEx::Render()
{
	if (SDL_RenderCopyEx(GameEngine::Instance()->GetRenderer(), texture,
		//&spriteSrcRect, &spriteDestRect, angle, nullptr, (SpriteEx::isFlipped) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE) == 0)
		&spriteSrcRect, & spriteDestRect, isVertical ? 270 : 0, nullptr, (SpriteEx::isFlipped) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE) == 0)
		
	{
		//	std::cout << "Success...\n";
	}
	else
	{
	}
}


SpriteExAnimated::SpriteExAnimated(SDL_Texture* tex, double x, double y,
	double a, int frameMax, int spriteMax, double speed)
{

	texture = tex;
	m_X = x;
	m_Y = y;
	angle = a;
	m_iFrameMax = frameMax;
	m_iSpriteMax = spriteMax;
	m_dSpeed = speed;

}


void SpriteExAnimated::Animate()
{
	m_iFrame++;

	if (animStates[currentState].TriggerActionOnFrame != nullptr
		&& m_iFrame == animStates[currentState].frameNumToCheckForCB) {
		animStates[currentState].TriggerActionOnFrame();
	}
	if (m_iFrame >= m_iFrameMax)
	{
		isAnimFinished = true;
		m_iFrame = 0;

		//Last thing to do:: invoke the callback function
		if (animStates[currentState].onAnimComplete != nullptr) {
			animStates[currentState].onAnimComplete();
		}
		//reset current state name as long as current 
		//state is completed and we are not in a loopable state
		if (!animStates[currentState].isLoopable)
			currentState = "";

	}


}

void SpriteExAnimated::PlayState(std::string stateName)
{

	if (!animStates[currentState].isLoopable && !isAnimFinished && animStates[currentState].canInterrupt == false)
	{
		AnimateRange(animStates[currentState]);
		return;
	}
	else if (isAnimFinished)
	{
		isAnimFinished = false;
	}

	if (currentState != stateName) //change of state detected
	{
		m_iFrame = 0; //reset frame number to 0.
		currentState = stateName;
	}

	AnimateRange(animStates[stateName]);

}


void SpriteExAnimated::AnimateRange(AnimStateDefinition asd)
{
	// change the row here
	spriteSrcRect.y = (spriteSrcRect.h * asd.rowIndex);

	if (SDL_TICKS_PASSED(SDL_GetTicks(), GetLastTick() + asd.delay))
	{
		UpdateTick();
		m_iFrameMax = asd.frames;
		Animate();

	}
}



void SpriteEx::UpdateDestRect()
{
	spriteDestRect.x = (int)(m_X - spriteDestRect.w * 0.5f);
	spriteDestRect.y = (int)(m_Y - spriteDestRect.h * 0.5f);
}


void SpriteExAnimated::AddAnimState(std::string stateName, AnimStateDefinition asd)
{
	animStates[stateName] = asd;
	//alternate way to do the above:
	//animStates.insert(std::pair<std::string,AnimStateDefinition>(stateName,asd));

}

//examples:
//remove idle from the list
//animStates.erase("idle");
