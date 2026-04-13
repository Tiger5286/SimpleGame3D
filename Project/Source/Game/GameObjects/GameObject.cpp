#include "GameObject.h"
#include "../../Game.h"

namespace
{
	constexpr float kGravity = 1.0f;
	constexpr float kMaxFallSpeed = 10.0f;

	constexpr float kResistance = 0.3f;
}

GameObject::GameObject(float sphereRadius):
	m_sphere(sphereRadius)
{
}

GameObject::~GameObject()
{
	MV1DeleteModel(m_modelHandle);
}

void GameObject::SetHandle(int handle)
{
	m_modelHandle = handle;
}

void GameObject::Gravity()
{
	m_vel.y -= kGravity;
	if (m_vel.y < -kMaxFallSpeed)
	{
		m_vel.y = -kMaxFallSpeed;
	}

	m_pos += m_vel;
	if (m_pos.y < 0.0f)
	{
		m_pos.y = 0.0f;
		m_vel.y = 0.0f;
	}
}

void GameObject::Resistance()
{
	// 速度と逆向きのベクトルを生成
	Vector3 resist = -m_vel;
	// Y方向には抵抗を適用しない
	resist.y = 0.0f;
	// 長さをkResistanceに補正
	resist.Normalize();
	resist *= kResistance;
	// 速度に抵抗を加算し減速
	m_vel += resist;
}

Vector3 GameObject::GetPos() const
{
	return m_pos;
}
