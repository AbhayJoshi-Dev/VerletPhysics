#include <cmath>

#include "Vector2.h"

Vector2::Vector2(float p_x, float p_y)
	: m_x(p_x), m_y(p_y)
{
}

void Vector2::SetAngle(float angle)
{
	float length = GetLength();
	m_x = std::cos(angle) * length;
	m_y = std::sin(angle) * length;
}

float Vector2::GetAngle() const
{
	return std::atan2(m_y, m_x);
}

void Vector2::SetLength(float len)
{
	float angle = GetAngle();
	m_x = std::cos(angle) * len;
	m_y = std::sin(angle) * len;
}

float Vector2::GetLength() const
{
	return std::sqrt(m_x * m_x + m_y * m_y);
}

void Vector2::AddTo(const Vector2& v)
{
	m_x += v.m_x;
	m_y += v.m_y;
}

void Vector2::SubTo(const Vector2& v)
{
	m_x -= v.m_x;
	m_y -= v.m_y;
}

void Vector2::Scale(float factor)
{
	m_x *= factor;
	m_y *= factor;
}

void Vector2::Scale(float x, float y)
{
	x *= x;
	y *= y;
}

float Vector2::Dot(const Vector2& other) const
{
	return (m_x * other.m_x + m_y * other.m_y);
}

Vector2 Vector2::operator+(const Vector2& other) const
{
	return Vector2(m_x + other.m_x, m_y + other.m_y);
}

Vector2 Vector2::operator-(const Vector2& other) const
{
	return Vector2(m_x - other.m_x, m_y - other.m_y);
}

Vector2 Vector2::operator*(const float& value) const
{
	return Vector2(m_x * value, m_y * value);
}

Vector2 Vector2::operator/(const float& value) const
{
	return Vector2(m_x / value, m_y / value);
}
