#pragma once

#include<SDL.h>

#include"Vector2.h"
#include"Utils.h"

class Entity
{
public:
	Entity() = default;
	Entity(const Vector2& position, float radius, bool pinned);
	void Update(double dt, int steps);
	void Render(SDL_Renderer* m_renderer);
	const Vector2& GetPosition() const;
	const Vector2& GetOldPosition() const;
	const float GetRadius() const;
	void Move(const Vector2& v);
	void ReverseOldX(float x);
	void ReverseOldY(float y);
	const bool IsPinned() const;
	void Pinned(bool pinned);
	//void Constraints();

	bool m_pinned;
private:
	Vector2 m_position;
	float m_radius;
	Vector2 m_old_position;
	Vector2 m_acceleration;
};