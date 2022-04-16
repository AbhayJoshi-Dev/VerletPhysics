#pragma once

#include"Entity.h"
#include"IRenderer.h"
#include"Transform.h"
#include"AssetManager.h"

class Ball : public Entity, public IRenderer, public Transform
{
public:
	Ball(const AssetManager& assetManager, const Vector& position, float scale = 1.0f);
	void Update() override final;
	void HandleEvents(SDL_Event& event) override final;
	void Render(SDL_Renderer* renderer) const override final;
	float GetRadius();
private:
	void CheckEdgeCollision();
public:
	Vector m_velocity;
	float m_bounce;
	float m_mass;
	SDL_Rect m_textureRect;
private:
	SDL_Texture* m_texture;

	float m_gravity;
	float m_radius;
};