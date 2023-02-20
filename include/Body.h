#pragma once

#include<vector>

#include"Entity.h"

struct Stick
{
	int m_index_1;
	int m_index_2;

	float m_length;

	void Update(std::vector<Entity>& entities)
	{
		float dx = entities[m_index_2].m_position.m_x - entities[m_index_1].m_position.m_x;
		float dy = entities[m_index_2].m_position.m_y - entities[m_index_1].m_position.m_y;

		float dst = sqrt(dx * dx + dy * dy);

		float diff = m_length - dst;
		float per = diff / dst / 2;
		float offset_x = dx * per;
		float offset_y = dy * per;

		entities[m_index_1].m_position.m_x -= offset_x;
		entities[m_index_1].m_position.m_y -= offset_y;

		entities[m_index_2].m_position.m_x += offset_x;
		entities[m_index_2].m_position.m_y += offset_y;
	}

	void Render(SDL_Renderer* renderer, std::vector<Entity>& entities)
	{
		SDL_RenderDrawLine(renderer, entities[m_index_1].m_position.m_x, entities[m_index_1].m_position.m_y, entities[m_index_2].m_position.m_x, entities[m_index_2].m_position.m_y);
	}

};

class Body
{
public:
	Body();
	void Update(std::vector<Entity>& entities);
	void Render(SDL_Renderer* renderer, std::vector<Entity>& entities);

public:
	std::vector<Stick> m_sticks;
};