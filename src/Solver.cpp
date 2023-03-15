#include"Solver.h"

Solver::Solver(const Vector2& dimension, float entity_raduis, const Vector2& gravity, int steps) :
	m_dimension(dimension),
	m_collision_solver(dimension, steps)
{}

void Solver::Update(float dt, int steps)
{
	for (int i = 0; i < steps; i++)
	{
		m_collision_solver.Update(m_entities, dt);
		m_constraint_solver.Update(m_constraints);

		for (std::shared_ptr<Segment>& segement : m_segments)
			segement->Update();

		for (std::shared_ptr<Entity>& entity : m_entities)
			entity->Update(dt, steps);
	}
}

std::shared_ptr<Entity>& Solver::AddEntity(const Vector2& position, float radius, bool pinned)
{
	m_entities.emplace_back(std::make_shared<Entity>(position, radius, pinned));

	return m_entities[m_entities.size() - 1];
}

const std::vector<std::shared_ptr<Entity>>& Solver::GetEntities() const
{
	return m_entities;
}

std::shared_ptr<Constraint>& Solver::AddConstraint(std::shared_ptr<Entity>& entity_1, std::shared_ptr<Entity>& entity_2, float length)
{
	m_constraints.emplace_back(std::make_shared<Constraint>(entity_1, entity_2, length));

	return m_constraints[m_constraints.size() - 1];
}

std::shared_ptr<Segment>& Solver::AddSegment(std::shared_ptr<Entity>& entity_1, std::shared_ptr<Entity>& entity_2, float length)
{
	m_segments.emplace_back(std::make_shared<Segment>(entity_1, entity_2, length));

	return m_segments[m_segments.size() - 1];
}