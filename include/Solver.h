#pragma once

#include<vector>
#include<memory>

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
	std::shared_ptr<Entity>& AddEntity(const Vector2& position, float radius, bool pinned);
	const std::vector<std::shared_ptr<Entity>>& GetEntities() const;
	std::shared_ptr<Constraint>& AddConstraint(std::shared_ptr<Entity>& entity_1, std::shared_ptr<Entity>& entity_2, float length);

private:
	Vector2 m_dimension;
	std::vector<std::shared_ptr<Entity>> m_entities;
	CollisionSolver m_collision_solver;
	std::vector<std::shared_ptr<Constraint>> m_constraints;
	ConstraintSolver m_constraint_solver;
};