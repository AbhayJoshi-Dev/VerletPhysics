#pragma once

#include<SDL.h>

#include"Vector2.h"
#include"Utils.h"

class Entity
{
public:
	Entity() = default;
	Entity(Vector2 position, float radius);
	void Update(float dt);
	void Render(SDL_Renderer* m_renderer);
	void Constraints();

private:

	Vector2 m_position;
	Vector2 m_last_position;
	float m_radius;
	Vector2 m_acceleration;
};