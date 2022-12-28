#include <cmath>

#include "Vector2.h"

Vector2::Vector2(float p_x, float p_y)
	: x(p_x), y(p_y)
{
}

void Vector2::SetX(float value)
{
	x = value;
}

void Vector2::SetY(float value)
{
	y = value;
}

float Vector2::GetX() const
{
	return x;
}

float Vector2::GetY() const
{
	return y;
}

void Vector2::SetAngle(float angle)
{
	float length = GetLength();
	x = std::cos(angle) * length;
	y = std::sin(angle) * length;
}

float Vector2::GetAngle() const
{
	return std::atan2(y, x);
}

void Vector2::SetLength(float len)
{
	float angle = GetAngle();
	x = std::cos(angle) * len;
	y = std::sin(angle) * len;
}

float Vector2::GetLength() const
{
	return std::sqrt(x * x + y * y);
}

void Vector2::AddTo(const Vector2& v)
{
	x += v.x;
	y += v.y;
}

void Vector2::SubTo(const Vector2& v)
{
	x -= v.x;
	y -= v.y;
}

void Vector2::Scale(float factor)
{
	x *= factor;
	y *= factor;
}

void Vector2::Scale(float x, float y)
{
	x *= x;
	y *= y;
}

float Vector2::Dot(const Vector2& other) const
{
	return (x * other.x + y * other.y);
}

Vector2 Vector2::operator+(const Vector2& other) const
{
	return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-(const Vector2& other) const
{
	return Vector2(x - other.x, y - other.y);
}
