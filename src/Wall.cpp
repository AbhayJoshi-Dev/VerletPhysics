#include"Wall.h"

Wall::Wall(const Vector& position, const Vector& start, const Vector& end, float angle, float length)
	:m_position(position), m_start(start), m_end(end), m_angle(angle), m_length(length)
{

}

void Wall::Update()
{

}

void Wall::Render(SDL_Renderer* renderer) const
{
	SDL_RenderDrawLine(renderer, m_start.GetX(), m_start.GetY(), m_end.GetX(), m_end.GetY());
}