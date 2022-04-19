#pragma once

#include"Vector.h"
#include"Entity.h"
#include"IRenderer.h"

class Wall : public Entity, public IRenderer
{
public:
	Wall(const Vector& position, const Vector& start, const Vector& end, float angle, float length);
	void Update() override final;
	void Render(SDL_Renderer* renderer) const override final;
public:
	Vector m_position;
	Vector m_start;
	Vector m_end;
	float m_angle;
	float m_length;
};