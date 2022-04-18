#include"Transform.h"

Transform::Transform(const Vector& position)
	:m_position(position)
{}

Vector Transform::GetPosition() const 
{
	return m_position;
}

void Transform::SetPosition(const Vector& position)
{
	m_position = position;
}

Vector Transform::GetScale() const
{
	return m_scale;
}

void Transform::SetScale(const float& scale)
{
	m_scale.SetX(scale);
	m_scale.SetY(scale);
}