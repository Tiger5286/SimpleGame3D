#include "Player.h"
#include "../System/Input.h"
#include "../Utility/Matrix4x4.h"
#include <cmath>

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
	m_modelHandle = MV1LoadModel(L"data/Player.mv1");
	MV1AttachAnim(m_modelHandle, 1);
}

void Player::End()
{
	MV1DeleteModel(m_modelHandle);
}

void Player::Update()
{
	// y以外の速度を減衰させる
	m_vel.x *= kVelocityDecay;
	m_vel.z *= kVelocityDecay;

	// 重力処理
	Gravity();
	// 移動処理
	Move();
	// ジャンプ処理
	Jump();

	// 位置に速度を足す
	m_pos += m_vel;

	// 行列を生成
	auto rotMtx = Matrix4x4::GetRotY(m_angle);
	auto transMtx = Matrix4x4::GetTranslate(m_pos);
	// 行列を合成
	auto mtx = transMtx * rotMtx;
	// 行列をモデルに適用
	MV1SetMatrix(m_modelHandle, mtx.ToDxLib());

	// 当たり判定の位置を設定
	m_sphere.SetPos(m_pos + Vector3(0.0f, kSphereRadius, 0.0f));
}

void Player::Draw()
{
	MV1DrawModel(m_modelHandle);
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
	// 移動ベクトルを準備
	Vector3 moveVec;
	// 左スティックの入力を取得
	auto lStick = m_input.GetStickInput(LR::Left);
	// 左スティックの入力を向きに反映する
	if (lStick.SquaredLength() > 0.0f)
	{
		m_angle = -atan2f(lStick.y, lStick.x) - DX_PI_F / 2 + m_cameraAngle;
	}
	// 移動ベクトルに入力を反映
	moveVec.x = lStick.x;
	moveVec.z = lStick.y;
	// 大きさが1以上なら1に補正
	if (moveVec.SquaredLength() > 1.0f) moveVec.Normalize();
	// 大きさを補正
	moveVec *= kMoveAccel;

	// 移動ベクトルをカメラの向きに回転
	moveVec = Matrix4x4::GetRotY(m_cameraAngle) * moveVec;
	
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
