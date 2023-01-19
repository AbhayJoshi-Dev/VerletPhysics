#include"Entity.h"

#include<iostream>

Entity::Entity(Vector2 postiton, float radius, bool pinned, bool chain_part)
	:m_position(postiton), m_radius(radius), m_last_position(postiton), m_pinned(pinned), m_chain_part(chain_part)
{}

void Entity::Update(double dt, int steps)
{
	if (!m_pinned)
	{
		m_acceleration = m_acceleration + Vector2(0.f, 1000.f); //gravity

		Vector2 dv = m_position - m_last_position;

		m_last_position = m_position;

		m_position = m_position + dv + m_acceleration * (dt * dt / steps);
		Constraints();

		m_acceleration = Vector2(0.f, 0.f);
	}
}

void Entity::Render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	utils::Draw_Circle(renderer, m_position.m_x, m_position.m_y, m_radius, 255, 255, 255, 255);
	//utils::FillCircle(renderer, m_position.m_x, m_position.m_y, m_radius);
}

void Entity::Constraints()
{
	Vector2 dv = m_position - m_last_position;

	if (m_position.m_x + (m_radius) >= 800)
	{
		m_position.m_x = 800 - (m_radius);
		m_last_position.m_x = m_position.m_x + dv.m_x;
	}
	else if (m_position.m_x - (m_radius) <= 0)
	{
		m_position.m_x = 0 + (m_radius);
		m_last_position.m_x = m_position.m_x + dv.m_x;
	}
	else if (m_position.m_y + (m_radius) >= 600)
	{
		m_position.m_y = 600 - (m_radius);
		m_last_position.m_y = m_position.m_y + dv.m_y;
	}
	else if (m_position.m_y - (m_radius) <= 0)
	{
		m_position.m_y = 0 + (m_radius);
		m_last_position.m_y = m_position.m_y + dv.m_y;
	}
}