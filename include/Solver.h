#pragma once

#include<vector>

#include"Vector2.h"
#include"Entity.h"

class Solver
{
public:
	Solver() = default;
	Solver(const Vector2& dimension, float entity_radius, const Vector2& gravity);
	void Update(float dt, int steps);
	Entity AddEntity(const Vector2& position, float radius, bool pinned);
	const std::vector<Entity>& GetEntities() const;

private:
	Vector2 m_dimension;
	std::vector<Entity> m_entities;
};