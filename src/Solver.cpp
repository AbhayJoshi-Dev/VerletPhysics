#include"Solver.h"

Solver::Solver(const Vector2& dimension, float entity_raduis, const Vector2& gravity)
	:m_dimension(dimension)
{}

void Solver::Update(float dt, int steps)
{
	//collision solver upadte
	//constraints solver upadte
	for(int i = 0; i < steps; i++)
		for (Entity& entity : m_entities)
			entity.Update(dt, steps);
}

Entity Solver::AddEntity(const Vector2& position, float radius, bool pinned)
{
	m_entities.emplace_back(position, radius, pinned);

	return m_entities[m_entities.size() - 1];
}

const std::vector<Entity>& Solver::GetEntities() const
{
	return m_entities;
}