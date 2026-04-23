#include "Player.h"
#include "../System/Input.h"
#include "../Utility/Matrix4x4.h"

namespace
{
	constexpr float kSphereRadius = 50.0f;

	constexpr float kGravity = 1.0f;

	constexpr float kMoveSpeed = 10.0f;
	constexpr float kMoveAccel = 3.0f;
	constexpr float kJumpPower = 15.0f;

	constexpr float kVelocityDecay = 0.7f;
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
	m_vel.x *= kVelocityDecay;
	m_vel.z *= kVelocityDecay;

	Gravity();
	Move();
	Jump();

	m_pos += m_vel;

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
		// 当たったポリゴンの法線
		Vector3 normal = Vector3::FromDxLib(result.Dim[i].Normal);

		// 法線が上向きなら地面なのでy成分を0にする
		if (normal.y > 0.4f)
		{
			m_vel.y = 0.0f;
			normal = Vector3(0.0f, 1.0f, 0.0f);
			m_isGround = true;
		}

		// 当たった位置
		Vector3 hitPos = Vector3::FromDxLib(result.Dim[i].HitPosition);
		// 当たった位置から球の中心までの距離
		float hitDist = (m_sphere.GetPos() - hitPos).Length();

		m_pos += -normal * (hitDist - m_sphere.GetRadius());
	}
}

void Player::Move()
{
	Vector3 moveVec;
	auto lStick = m_input.GetStickInput(LR::Left);
	moveVec.x = lStick.x;
	moveVec.z = lStick.y;
	if (moveVec.SquaredLength() > 1.0f) moveVec.Normalize();
	moveVec *= kMoveAccel;

	moveVec = Matrix4x4::GetRotYMatrix(m_cameraAngle) * moveVec;
	
	// y以外の速度が定数以下なら移動ベクトルを速度に足す
	Vector3 velXZ = m_vel;
	velXZ.y = 0.0f;
	if (velXZ.SquaredLength() < kMoveSpeed * kMoveSpeed)
	{
		m_vel += moveVec;
	}
}

void Player::Gravity()
{
	m_vel.y -= kGravity;
}

void Player::Jump()
{
	bool isInputJump = m_input.IsTriggerd(XINPUT_BUTTON_A);
	if (isInputJump && m_isGround)
	{
		m_vel.y = kJumpPower;
		m_isGround = false;
	}
}
