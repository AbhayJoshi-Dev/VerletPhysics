#pragma once

#include<iostream>
#include<SDL.h>
#include<vector>

#include"Timer.h"
#include"Entity.h"
#include"Solver.h"


class Core
{
public:
	Core();
	~Core();

	void Loop();
	void Update();
	void Render();
	void CreateChain();

private:

	SDL_Window* m_window;
	SDL_Renderer* m_renderer;

	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;

	const int SCREEN_FPS = 60;
	const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

	bool m_quit;

	SDL_Event m_event;

	Timer m_fps_timer;
	Timer m_cap_timer;

	int m_counted_frames;

	std::vector<Entity> m_entities;

	bool m_is_left_mouse_pressed;
	bool m_is_right_mouse_pressed;

	int m_max_objects;
	Timer m_spawn_timer;

	int m_steps;

	Vector2 m_previous_pos;

	std::vector<std::shared_ptr<Entity>> m_temp_entities;

	Solver m_solver;

};