#include"Segment.h"

Segment::Segment(std::shared_ptr<Entity>& entity_1, std::shared_ptr<Entity>& entity_2, float length)
	:m_constraints(entity_1, entity_2, length)
{}

void Segment::Update()
{
	m_constraints.Update();
}