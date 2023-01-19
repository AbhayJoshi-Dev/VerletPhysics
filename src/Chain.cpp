#include"Chain.h"

void Chain::ApplyLink(Entity& m_entity_1, Entity& m_entity_2)
{
	Vector2 axis = m_entity_1.m_position - m_entity_2.m_position;

	float dst = sqrt(axis.m_x * axis.m_x + axis.m_y * axis.m_y);

	Vector2 norm = axis / dst;
	float delta = m_target_dst - dst;

	if (!m_entity_1.m_pinned)
		m_entity_1.m_position = m_entity_1.m_position + norm * 0.5 * delta;
	if (!m_entity_2.m_pinned)
		m_entity_2.m_position = m_entity_2.m_position - norm * 0.5 * delta;
}