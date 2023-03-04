#include"CollisionSolver.h"

CollisionSolver::CollisionSolver(const Vector2& dimension, int steps):
	m_dimension(dimension),
	m_steps(steps)
{}

void CollisionSolver::Update(std::vector<std::shared_ptr<Entity>>& entities, float dt)
{
	BoundaryCollision(entities);
	EntityCollision(entities);
}

void CollisionSolver::BoundaryCollision(std::vector<std::shared_ptr<Entity>>& entities)
{
	for (std::shared_ptr<Entity>& entity : entities)
	{
		Vector2 position = entity->GetPosition();
		Vector2 old_position = entity->GetOldPosition();
		float radius = entity->GetRadius();

		Vector2 dv = position - old_position;

		if (position.x + radius > m_dimension.x)
		{
			entity->Move({ m_dimension.x - radius - position.x, 0.f});
			entity->ReverseOldX(dv.x);
		}
		else if (position.x - radius < 0)
		{
			entity->Move({ radius - position.x, 0.f });
			entity->ReverseOldX(dv.x);
		}

		if (position.y + radius > m_dimension.y)
		{
			entity->Move({ 0.f, m_dimension.y - radius - position.y });
			entity->ReverseOldY(dv.y);
		}
		else if (position.y - radius < 0)
		{
			entity->Move({ 0, radius - position.y });
			entity->ReverseOldY(dv.y);
		}
	}
}

void CollisionSolver::EntityCollision(std::vector<std::shared_ptr<Entity>>& entities)
{
	for (int i = 0; i < entities.size(); i++)
	{
		std::shared_ptr<Entity>& entity_1 = entities[i];

		for (int j = i + 1; j < entities.size(); j++)
		{
			std::shared_ptr<Entity>& entity_2 = entities[j];

			Vector2 dv = entity_1->GetPosition() - entity_2->GetPosition();
			float dst = sqrt(dv.x * dv.x + dv.y * dv.y);

			float radius_1 = entity_1->GetRadius();
			float radius_2 = entity_2->GetRadius();

			float collision_dst = radius_1 + radius_2;

			if (dst <= collision_dst)
			{
				Vector2 u_dv = dv / dst; // unit vector

				float mass_ratio_1 = radius_1 / (radius_1 + radius_2);
				float mass_ratio_2 = radius_2 / (radius_1 + radius_2);

				float delta = 0.5f * 0.75f * (dst - collision_dst);

				if (!entity_1->IsPinned())
					entity_1->Move(u_dv * (mass_ratio_2 * delta) * -1.f);
				if (!entity_2->IsPinned())
					entity_2->Move(u_dv * (mass_ratio_1 * delta) * 1.f);
			}
		}
	}
}