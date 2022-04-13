#pragma once

#include<SDL.h>

class Entity
{
public:
	Entity();
	virtual ~Entity() = default;
	virtual void Update();
	virtual void HandleEvents(SDL_Event& event);
};