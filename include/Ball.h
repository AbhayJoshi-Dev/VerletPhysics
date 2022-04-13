#pragma once

#include"Entity.h"
#include"IRenderer.h"
#include"Transform.h"
#include"AssetManager.h"

class Ball : public Entity, public IRenderer, public Transform
{
public:
	Ball(const AssetManager& assetManager, const Vector& position);
	void Update() override final;
	void HandleEvents(SDL_Event& event) override final;
	void Render(SDL_Renderer* renderer) const override final;
private:
	void CheckEdgeCollision();
private:
	SDL_Texture* m_texture;
	SDL_Rect m_textureRect;

	Vector m_velocity;
	Vector m_gravity;

	float m_bounce;
};