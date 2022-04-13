#pragma once

#include<SDL.h>

class IRenderer
{
public:
	virtual ~IRenderer() {}
	virtual void Render(SDL_Renderer* renderer) const = 0;
};