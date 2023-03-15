#pragma once

#include"Constraint.h"

class Segment
{
public:
	Segment(std::shared_ptr<Entity>& entity_1, std::shared_ptr<Entity>& entity_2, float length);
	void Update();
private:
	Constraint m_constraints;
};