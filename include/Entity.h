#pragma once

#include<SDL.h>

class Entity
{
	Entity();
	virtual ~Entity() = default;
	virtual void Update();
	virtual void HandleEvents(SDL_Event& event);
};