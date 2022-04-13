#pragma once

#include"Vector.h"

class Transform
{
public:
	Transform() = default;
	Transform(const Vector& position);
	virtual ~Transform() = default;

	Vector GetPosition() const;
	void SetPosition(const Vector& position);

	Vector GetScale() const;
	void SetScale(const float& scale);

private:
	Vector m_position;
	Vector m_scale = {1.f, 1.f};
};