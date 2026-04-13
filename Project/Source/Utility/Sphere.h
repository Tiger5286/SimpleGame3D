#pragma once
#include "Vector3.h"

class Sphere
{
public:
	Sphere(float radius);
	virtual ~Sphere();

	void Draw(unsigned int color = kDefaultColor);

	void SetPos(const Vector3& pos) { m_pos = pos; }
	const Vector3& GetPos() const { return m_pos; }

	float GetRadius() const { return m_radius; }

private:
	static constexpr unsigned int kDefaultColor = 0xffff00;

	Vector3 m_pos;
	float m_radius;
};

