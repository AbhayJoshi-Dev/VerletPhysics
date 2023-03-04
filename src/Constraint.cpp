#include<iostream>

#include"Constraint.h"

Constraint::Constraint():
	m_entity_1(),
	m_entity_2(),
	m_length(0.0f)
{}

Constraint::Constraint(std::shared_ptr<Entity> entity_1, std::shared_ptr<Entity> entity_2, float length):
	m_entity_1(entity_1),
	m_entity_2(entity_2),
	m_length(length)
{}

void Constraint::Update()
{
	Vector2 dir = m_entity_1->GetPosition() - m_entity_2->GetPosition();

	float dst = sqrt(dir.x * dir.x + dir.y * dir.y);

	Vector2 u = dir / dst;
	float delta = m_length - dst;

	if (!m_entity_1->IsPinned())
		m_entity_1->Move(u * delta * 1.f * 0.5f);
	if (!m_entity_2->IsPinned())
		m_entity_2->Move(u * delta * -1.f * 0.5f);
}