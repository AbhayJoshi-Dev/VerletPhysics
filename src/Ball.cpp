#include"Ball.h"

#include<iostream>

Ball::Ball(const AssetManager& assetManager, const Vector& position, float scale)
{
	m_texture = assetManager.Get("Ball");
	this->SetPosition(position);
	m_textureRect.x = 0;
	m_textureRect.y = 0;

	SDL_QueryTexture(m_texture, NULL, NULL, &m_textureRect.w, &m_textureRect.h);

	this->SetScale(scale);
	m_velocity.SetLength(0.f);

	m_gravity = 0.1f;

	m_bounce = 0.75f;
	m_mass = 1.f;
	m_radius = 1.f;
}

void Ball::Update()
{
	this->SetPosition(GetPosition() + m_velocity);

	m_velocity.AddTo(Vector(0.f, m_gravity));
	CheckEdgeCollision();

	m_radius = m_textureRect.w * this->GetScale().GetX() / 2;
}

void Ball::HandleEvents(SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		m_velocity.AddTo(Vector(1.f, -5.f));
		break;
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
	dst.w = src.w * this->GetScale().GetX();
	dst.h = src.h * this->GetScale().GetY();

	SDL_RenderCopy(renderer, m_texture, &src, &dst);
}

float Ball::GetRadius()
{
	return m_radius;
}

void Ball::CheckEdgeCollision()
{
	Vector tempPosition = this->GetPosition();

	if (tempPosition.GetX() >= 1920.f / 2.f - (m_radius * 2))
	{
		SetPosition(Vector(1920.f / 2.f - (m_radius * 2), tempPosition.GetY()));

		m_velocity.SetX(m_velocity.GetX() * -m_bounce);
	}
	else if (tempPosition.GetX() <= 0.f)
	{
		SetPosition(Vector(0.f, tempPosition.GetY()));

		m_velocity.SetX(m_velocity.GetX() * -m_bounce);
	}

	if (tempPosition.GetY() > 1080.f / 2.f - (m_radius * 2))
	{
		SetPosition(Vector(tempPosition.GetX(), 1080.f / 2.f - (m_radius * 2)));

		m_velocity.SetY(m_velocity.GetY() * -m_bounce);
	}
	else if (tempPosition.GetY() <= 0.f)
	{
		SetPosition(Vector(tempPosition.GetX(), 0.f));

		m_velocity.SetY(m_velocity.GetY() * -m_bounce);
	}
}