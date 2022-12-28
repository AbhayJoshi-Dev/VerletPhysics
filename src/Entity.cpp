#include"Entity.h"

Entity::Entity(Vector2 postiton, float radius)
	:m_position(postiton), m_radius(radius), m_last_position(postiton)
{}

void Entity::Update()
{
	Vector2 dv = m_position - m_last_position;

	m_last_position = m_position;

	m_position = m_position + dv + m_acceleration; // add delta time (dt)
}

void Entity::Render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	utils::FillCircle(renderer, m_position.GetX(), m_position.GetY(), m_radius);
}