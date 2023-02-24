#include"CollisionSolver.h"

CollisionSolver::CollisionSolver(const Vector2& dimension, int steps):
	m_dimension(dimension),
	m_steps(steps)
{}

void CollisionSolver::Update(std::vector<Entity>& entities, float dt)
{
	for (int i = 0; i < m_steps; i++)
	{

	}
}

void CollisionSolver::BoundaryCollision(std::vector<Entity>& entities)
{
	for (Entity& entity : entities)
	{
		Vector2 position = entity.GetPosition();
		Vector2 old_position = entity.GetOldPosition();
		float radius = entity.GetRadius();

		Vector2 dv = position - old_position;

		if (position.x + (radius) >= 800)
		{
			position.x = 800 - (radius);
			old_position.x = position.x + dv.x;
		}
		else if (position.x - (radius) <= 0)
		{
			position.x = 0 + (radius);
			old_position.x = position.x + dv.x;
		}
		else if (position.y + (radius) >= 600)
		{
			position.y = 600 - (radius);
			old_position.y = position.y + dv.y;
		}
		else if (position.y - (radius) <= 0)
		{
			position.y = 0 + (radius);
			old_position.y = position.y + dv.y;
		}
	}
}