#pragma once

#include"Entity.h"

class Chain
{
public:
	Chain() = default;
	void ApplyLink(Entity& m_entity_1, Entity& m_entity_2);

private:
	float m_target_dst = 22;
};