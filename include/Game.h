#pragma once

#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include<vector>
#include<imgui.h>
#include<imgui_impl_sdl.h>
#include<imgui_impl_sdlrenderer.h>

#include"AssetManager.h"
#include"Utils.h"
#include"Entity.h"
#include"Ball.h"
#include"Wall.h"

class Game
{
public:
	Game();
	virtual ~Game();
	void CreateWindow(const char* title, int width, int height);
	void GameLoop();
	void Update();
	void Render();
	void CheckBallToBallCollision();
	bool IsCollisionBetweenBalls(Ball* b1, Ball* b2);
	void BallCollision(Ball* b1, Ball* b2);
	void CheckIfBallCollidesFurther(Ball* b);
	void DrawBallWithMouse();
	void DrawWall();
	void CheckBallToWallCollision();
	bool IsCollisionBetweenBallAndWall(Ball* b, Wall* w);
	void CollideBallWithWall(Ball* b, Wall* ws);
private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;

	const char* TITLE = "Ball Simulator";
	const int SCREEN_WIDTH = 1920 / 2;
	const int SCREEN_HEIGHT = 1080 / 2;

	SDL_Event m_event;
	bool m_gameRunning;

	std::unique_ptr<AssetManager> m_assetManager;
	std::vector<std::unique_ptr<Entity>> m_entities;
	std::vector<std::unique_ptr<Wall>> m_walls;

	const float TIMESTEP = 0.01f;
	float m_accumulator = 0.f;
	float m_currentTime = 0.f;
	float m_newTime = 0.f;
	float m_frameTime = 0.f;
	float m_alpha = 0.f;
	int m_startTicks;
	int m_frameTicks;

	int m_previousMouseX = 0;
	int m_previousMouseY = 0;

	bool m_drawingBall;
	bool m_ballDrawnSuccessfully;

	bool m_drawingWall;
	bool m_wallDrawnSuccessfully;

	std::unique_ptr<Entity> m_entity;

	bool m_drawBallCheckBox;
	bool m_drawWallCheckBox;
};