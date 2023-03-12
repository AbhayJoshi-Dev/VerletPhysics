#include"Entity.h"

#include<iostream>

Entity::Entity(const Vector2& postiton, float radius, bool pinned)
	:m_position(postiton), m_radius(radius), m_old_position(postiton), m_pinned(pinned)
{}

void Entity::Update(double dt, int steps)
{
	if (!m_pinned)
	{
		m_acceleration += Vector2(0.f, 1000.f); //gravity

		Vector2 dv = m_position - m_old_position;

		m_old_position = m_position;

		m_position += dv + m_acceleration * (dt * dt / steps);

		m_acceleration = Vector2(0.f, 0.f);
	}
}

void Entity::Render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	utils::Draw_Circle(renderer, m_position.x, m_position.y, m_radius, 255, 255, 255, 255);
}

const Vector2& Entity::GetPosition() const
{
	return m_position;
}

const Vector2& Entity::GetOldPosition() const
{
	return m_old_position;
}

const float Entity::GetRadius() const
{
	return m_radius;
}

void Entity::Move(const Vector2& v)
{
	m_position += v;
}

void Entity::ReverseOldX(float x)
{
	m_old_position.x = m_position.x + x;
}

void Entity::ReverseOldY(float y)
{
	m_old_position.y = m_position.y + y;
}

const bool Entity::IsPinned() const
{
	return m_pinned;
}

void Entity::Pinned(bool pinned)
{
	m_pinned = pinned;
}

/*void Entity::Constraints()
{
	Vector2 dv = m_position - m_old_position;

	if (m_position.x + (m_radius) >= 800)
	{
		m_position.x = 800 - (m_radius);
		m_last_position.x = m_position.x + dv.x;
	}
	else if (m_position.x - (m_radius) <= 0)
	{
		m_position.x = 0 + (m_radius);
		m_last_position.x = m_position.x + dv.x;
	}
	else if (m_position.y + (m_radius) >= 600)
	{
		m_position.y = 600 - (m_radius);
		m_last_position.y = m_position.y + dv.y;
	}
	else if (m_position.y - (m_radius) <= 0)
	{
		m_position.y = 0 + (m_radius);
		m_last_position.y = m_position.y + dv.y;
	}
}*/