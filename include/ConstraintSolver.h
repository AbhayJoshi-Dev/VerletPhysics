#pragma once

#include<vector>

#include"Constraint.h"

class ConstraintSolver
{
public:
	ConstraintSolver() = default;

	void Update(std::vector<Constraint*>& constraints)
	{
		int steps = 4;

		for (int i = 0; i < steps; i++)
			for (Constraint* constraint : constraints)
				constraint->Update();
	}
};