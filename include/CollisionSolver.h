#pragma once

#include<vector>
#include<memory>

#include"Vector2.h"
#include"Entity.h"

class CollisionSolver
{
public:
	CollisionSolver() = default;
	CollisionSolver(const Vector2& dimension, int steps);
	void Update(std::vector<std::shared_ptr<Entity>>& entities, float dt);

private:
	void BoundaryCollision(std::vector< std::shared_ptr<Entity>>& entities);
	void EntityCollision(std::vector< std::shared_ptr<Entity>>& entities);

private:
	const Vector2 m_dimension;
	int m_steps;
};