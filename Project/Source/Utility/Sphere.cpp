#include "Sphere.h"

namespace
{
	constexpr int kDivNum = 8;
}

Sphere::Sphere(float radius):
	m_radius(radius)
{
}

Sphere::~Sphere()
{
}

void Sphere::Draw(unsigned int color)
{
	DrawSphere3D(m_pos.ToDxLib(), m_radius, kDivNum, color, color, false);
}