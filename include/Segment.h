#pragma once

#include"Constraint.h"

class Segment
{
public:
	Segment(Entity* entity_1, Entity* entity_2, float length);
	void Update();
private:
	Constraint m_constraints;
};