#pragma once

#include<memory>

#include"Entity.h"

class Constraint
{
public:
	Constraint();
	Constraint(std::shared_ptr<Entity>& entity_1, std::shared_ptr<Entity>& entity_2, float length);
	void Update();

private:
	std::shared_ptr<Entity> m_entity_1;
	std::shared_ptr<Entity> m_entity_2;
	float m_length;
};