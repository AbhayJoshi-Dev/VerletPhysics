#include"Ball.h"

#include<iostream>

Ball::Ball(const AssetManager& assetManager, const Vector& position)
{
	m_texture = assetManager.Get("Ball");
	this->SetPosition(position);
	m_textureRect.x = 0;
	m_textureRect.y = 0;

	SDL_QueryTexture(m_texture, NULL, NULL, &m_textureRect.w, &m_textureRect.h);

	m_velocity.SetLength(0.f);
	m_gravity.SetLength(0.05f);
	m_gravity.SetAngle((float)(90.0 * 3.141593 / 180.0));

	m_bounce = -0.9f;
}

void Ball::Update()
{
	this->SetPosition(GetPosition() + m_velocity);

	m_velocity.AddTo(m_gravity);

	CheckEdgeCollision();
}

void Ball::HandleEvents(SDL_Event& event)
{
	switch (event.type)
	{
	default:
		break;
	}
}

void Ball::Render(SDL_Renderer* renderer) const
{
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = m_textureRect.w;
	src.h = m_textureRect.h;

	SDL_Rect dst;
	dst.x = (int)this->GetPosition().GetX();
	dst.y = (int)this->GetPosition().GetY();
	dst.w = src.w;
	dst.h = src.h;

	SDL_RenderCopy(renderer, m_texture, &src, &dst);
}

void Ball::CheckEdgeCollision()
{
	Vector tempPosition = this->GetPosition();

	if (tempPosition.GetX() >= 1920.f / 2.f - (float)m_textureRect.w)
	{
		SetPosition(Vector(1920.f / 2.f - (float)m_textureRect.w, tempPosition.GetY()));

		m_velocity.SetX(m_velocity.GetX() * m_bounce);
	}
	else if (tempPosition.GetX() <= 0.f)
	{
		SetPosition(Vector(0.f, tempPosition.GetY()));

		m_velocity.SetX(m_velocity.GetX() * m_bounce);
	}

	if (tempPosition.GetY() >= 1080.f / 2.f - (float)m_textureRect.h)
	{
		SetPosition(Vector(tempPosition.GetX(), 1080.f / 2.f - (float)m_textureRect.h));

		m_velocity.SetY(m_velocity.GetY() * m_bounce);
	}
	else if (tempPosition.GetY() <= 0.f)
	{
		SetPosition(Vector(tempPosition.GetX(), 0.f));

		m_velocity.SetY(m_velocity.GetY() * m_bounce);
	}
}