#include "SceneMain.h"
#include "DxLib.h"
#include "../System/Camera.h"
#include "../System/Input.h"
#include "../Game/Player.h"
#include "../Utility/Matrix4x4.h"

SceneMain::SceneMain() :
	m_frameCount(0)
{
}

SceneMain::~SceneMain()
{
	MV1DeleteModel(m_mapHandle);
}

void SceneMain::Init()
{
	SetBackgroundColor(0,255,255);

	m_mapHandle = MV1LoadModel(L"data/map.mv1");
	MV1SetupCollInfo(m_mapHandle);

	m_pInput = std::make_shared<Input>();

	m_pCamera = std::make_shared<Camera>(*m_pInput);
	m_pCamera->Init();

	m_pPlayer = std::make_shared<Player>(*m_pInput);
	m_pPlayer->SetMapHandle(m_mapHandle);
	m_pPlayer->Init();
}

void SceneMain::Update()
{
	m_frameCount++;

	// 各クラスの更新処理
	m_pInput->Update();

	m_pPlayer->SetCameraAngle(m_pCamera->GetAngleY());
	m_pPlayer->Update();

	m_pCamera->SetPlayerPos(m_pPlayer->GetPos());
	m_pCamera->Update();

	// 当たり判定
	auto playerSpherePos = m_pPlayer->GetSphere().GetPos();
	auto playerSphereRadius = m_pPlayer->GetSphere().GetRadius();
	auto result = MV1CollCheck_Sphere(m_mapHandle, -1, playerSpherePos.ToDxLib(), playerSphereRadius);
	if (result.HitNum > 0)
	{
		m_pPlayer->OnHitModel(result);
	}
	MV1CollResultPolyDimTerminate(result);

	// ライトの方向を設定
	auto lightDir = Vector3(0.0f, -1.5f, 1.0f);
	lightDir = Matrix4x4::GetRotY(m_pCamera->GetAngleY()) * lightDir;
	SetLightDirection(lightDir.ToDxLib());
}

void SceneMain::Draw()
{
#ifdef _DEBUG
	DrawGrid();
#endif

	MV1DrawModel(m_mapHandle);

	m_pPlayer->Draw();

#ifdef _DEBUG
	DrawString(0,0,L"SceneMain",0xffffff);
	DrawFormatString(0, 16, 0xffffff, L"FRAME:%d", m_frameCount);
#endif
}

void SceneMain::DrawGrid()
{
	// 直線の始点と終点
	VECTOR startPos;
	VECTOR endPos;

	for (int z = -300; z <= 300; z += 100)
	{
		startPos = VGet(-300.0f, 0.0f, static_cast<float>(z));
		endPos = VGet(300.0f, 0.0f, static_cast<float>(z));
		DrawLine3D(startPos, endPos, 0xff0000);
	}
	for (int x = -300; x <= 300; x += 100)
	{
		startPos = VGet(static_cast<float>(x), 0.0f, -300.0f);
		endPos = VGet(static_cast<float>(x), 0.0f, 300.0f);
		DrawLine3D(startPos, endPos, 0x0000ff);
	}
}
