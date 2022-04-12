#pragma once

#include<SDL.h>
#include<SDL_image.h>
#include<iostream>

#include"Utils.h"

class Game
{
public:
	Game();
	virtual ~Game();
	void CreateWindow(const char* title, int width, int height);
	void GameLoop();
	void Update();
	void Render();
private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;

	const char* TITLE = "Ball Simulator";
	const int SCREEN_WIDTH = 1920 / 2;
	const int SCREEN_HEIGHT = 1080 / 2;

	SDL_Event m_event;
	bool m_gameRunning;

	const float TIMESTEP = 0.01f;
	float m_accumulator = 0.f;
	float m_currentTime = 0.f;
	float m_newTime = 0.f;
	float m_frameTime = 0.f;
	float m_alpha = 0.f;
	int m_startTicks;
	int m_frameTicks;
};