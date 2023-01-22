#pragma once

#include<vector>

#include"Entity.h"

struct Link
{
	int m_index_1;
	int m_index_2;

	//Entity& m_entity_1;
	//Entity& m_entity_2;

	float m_target_dst = 22;

	void ApplyLink(std::vector<Entity>& entities)//Entity& m_entity_1, Entity& m_entity_2
	{
		Vector2 axis = entities[m_index_1].m_position - entities[m_index_2].m_position;

		float dst = sqrt(axis.m_x * axis.m_x + axis.m_y * axis.m_y);

		Vector2 norm = axis / dst;
		float delta = m_target_dst - dst;

		if (!entities[m_index_1].m_pinned)
			entities[m_index_1].m_position = entities[m_index_1].m_position + norm * 0.5 * delta;
		if (!entities[m_index_2].m_pinned)
			entities[m_index_2].m_position = entities[m_index_2].m_position - norm * 0.5 * delta;
	}
};

class Chain
{
public:
	Chain();
	void Update(std::vector<Entity>& entities);

public:
	std::vector<Link> m_links;
};