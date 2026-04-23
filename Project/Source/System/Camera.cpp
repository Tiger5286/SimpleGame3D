#include "Camera.h"
#include <cmath>
#include "EffekseerForDXLib.h"
#include "../Utility/Matrix4x4.h"
#include "../System/Input.h"

namespace
{
	// カメラの初期位置と初期注視点
	const Vector3 kFirstPos = { 0.0f,300.0f,-700.0f };
	const Vector3 kFirstTarget = { 0.0f,0.0f,0.0f };
	// 視野角
	constexpr float kFov = DX_PI_F / 3.0f;	// 60度
	// NearFar
	constexpr float kNear = 100.0f;
	constexpr float kFar = 5000.0f;

	// オフセット
	const Vector3 kTargetOffset = { 0.0f,100.0f,0.0f };
	const Vector3 kPosOffset = { 0.0f,400.0f,0.0f };

	// 注視点との距離
	constexpr float kTargetDis = 700.0f;

	// カメラの回転速度
	constexpr float kRotSpeed = 0.05f;

	// カメラのX軸回転の上限と下限
	constexpr float kMaxAngleX = DX_PI_F / 2.0f - 0.1f;
	constexpr float kMinAngleX = -DX_PI_F / 10.0f;
}

Camera::Camera(Input& input):
	m_input(input)
{
}

Camera::~Camera()
{
}

void Camera::Init()
{
	// カメラの初期設定
	m_pos = kFirstPos;
	m_target = kFirstTarget;
	SetCameraPositionAndTarget_UpVecY(m_pos.ToDxLib(), m_target.ToDxLib());
	SetupCamera_Perspective(kFov);
	SetCameraNearFar(kNear, kFar);
	// DXライブラリのカメラとEffekseerのカメラを同期する。
	Effekseer_Sync3DSetting();

	// 角度を補正
	if (m_angleY < 0.0f) m_angleY += DX_TWO_PI_F;
	if (m_angleY > DX_TWO_PI_F) m_angleY -= DX_TWO_PI_F;
}

void Camera::Update()
{
	// スティック入力に応じて角度を更新
	auto rightStick = m_input.GetStickInput(LR::Right);
	m_angleY += rightStick.x * kRotSpeed;
	if (m_angleY < 0.0f) m_angleY += DX_TWO_PI_F;
	if (m_angleY > DX_TWO_PI_F) m_angleY -= DX_TWO_PI_F;
	m_angleX -= rightStick.y * kRotSpeed;
	if (m_angleX > kMaxAngleX) m_angleX = kMaxAngleX;
	if (m_angleX < kMinAngleX) m_angleX = kMinAngleX;

	// プレイヤーの位置をもとにカメラの位置と注視点を設定
	
	// 注視点を設定
	m_target = m_playerPos + kTargetOffset;
	// 位置を設定
	// 適当なベクトルを生成
	Vector3 pos = { 0,0,-1 };
	pos.Normalize();
	// ベクトルの長さを注視点との距離にする
	pos *= kTargetDis;
	// 変形用の行列を生成
	auto rotYMtx = Matrix4x4::GetRotY(m_angleY);
	auto rotXMtx = Matrix4x4::GetRotX(m_angleX);
	auto transMtx = Matrix4x4::GetTranslate(m_playerPos + kPosOffset);
	// 行列を合成
	auto mtx = transMtx * rotYMtx * rotXMtx;
	// ベクトルを変形
	pos = mtx * pos;
	m_pos = pos;

	// 位置と注視点を反映
	SetCameraPositionAndTarget_UpVecY(m_pos.ToDxLib(), m_target.ToDxLib());
	// DXライブラリのカメラとEffekseerのカメラを同期する。
	Effekseer_Sync3DSetting();
}