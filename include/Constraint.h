#pragma once

#include<memory>

#include"Entity.h"

class Constraint
{
public:
	Constraint();
	Constraint(Entity* entity_1, Entity* entity_2, float length);
	void Update();

private:
	Entity* m_entity_1;
	Entity* m_entity_2;
	float m_length;
};