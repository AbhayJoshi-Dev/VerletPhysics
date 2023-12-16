#include"Segment.h"

Segment::Segment(Entity* entity_1, Entity* entity_2, float length)
	:m_constraints(entity_1, entity_2, length)
{}

void Segment::Update()
{
	m_constraints.Update();
}