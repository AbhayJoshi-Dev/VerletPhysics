#pragma once

#include<iostream>
#include<SDL.h>

class Core
{
public:
	Core();
	~Core();

	void Loop();
	void Update();
	void Render();

private:

	SDL_Window* m_window;
	SDL_Renderer* m_renderer;

	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;

	bool m_quit;

	SDL_Event m_event;

};