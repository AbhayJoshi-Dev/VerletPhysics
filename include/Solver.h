#pragma once

#include<vector>

#include"Vector2.h"
#include"Entity.h"
#include"CollisionSolver.h"
#include"Constraint.h"
#include"ConstraintSolver.h"

class Solver
{
public:
	Solver() = default;
	Solver(const Vector2& dimension, float entity_radius, const Vector2& gravity, int steps);
	void Update(float dt, int steps);
	Entity AddEntity(const Vector2& position, float radius, bool pinned);
	const std::vector<Entity>& GetEntities() const;
	Constraint AddConstraint(Entity& entity_1, Entity& entity_2, float length);

private:
	Vector2 m_dimension;
	std::vector<Entity> m_entities;
	CollisionSolver m_collision_solver;
	std::vector<Constraint> m_constraints;
	ConstraintSolver m_constraint_solver;
};