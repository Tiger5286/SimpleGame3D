#include "Player.h"
#include "../System/Input.h"
#include "../Utility/Matrix4x4.h"

namespace
{
	constexpr float kSphereRadius = 50.0f;

	constexpr float kMoveSpeed = 10.0f;
}

Player::Player(Input& input) :
	m_input(input),
	m_sphere(kSphereRadius)
{
}

Player::~Player()
{
}

void Player::Init()
{
}

void Player::End()
{
}

void Player::Update()
{
	Move();

	m_sphere.SetPos(m_pos + Vector3(0.0f, kSphereRadius, 0.0f));
}

void Player::Draw()
{
#ifdef _DEBUG
	m_sphere.Draw();
#endif
}

void Player::OnHitModel(MV1_COLL_RESULT_POLY_DIM result)
{
	for (int i = 0;i < result.HitNum; i++)
	{
		float distance = (Vector3::FromDxLib(result.Dim[i].HitPosition) - m_pos).Length();
		distance = (m_sphere.GetRadius() - distance) + 0.01f;

		Vector3 norm = Vector3::FromDxLib(result.Dim[i].Normal);
		Vector3 pushVec = norm * distance;
		m_pos += pushVec;
	}
}

void Player::Move()
{
	Vector3 moveVec;
	auto lStick = m_input.GetStickInput(LR::Left);
	moveVec.x = lStick.x;
	moveVec.z = lStick.y;
	if (moveVec.SquaredLength() > 1.0f) moveVec.Normalize();
	moveVec *= kMoveSpeed;

	moveVec = Matrix4x4::GetRotYMatrix(m_cameraAngle) * moveVec;
	
	m_pos += moveVec;
}