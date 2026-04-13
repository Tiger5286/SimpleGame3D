#include "SkyBox.h"
#include <string>
#include <array>
#include "Dxlib.h"
#include <cassert>

#include "../Utility/Vector3.h"
#include "../System/Camera.h"

namespace
{
	const std::array<std::wstring,6> kFileNames = {
		L"data/Graphs/skybox_front.png",
		L"data/Graphs/skybox_back.png",
		L"data/Graphs/skybox_left.png",
		L"data/Graphs/skybox_right.png",
		L"data/Graphs/skybox_up.png",
		L"data/Graphs/skybox_down.png",
	};
}

SkyBox::SkyBox()
{
}

SkyBox::~SkyBox()
{
}

void SkyBox::Init()
{
	for (int i = 0; i < kFileNames.size(); i++)
	{
		m_graphHandles[i] = LoadGraph(kFileNames[i].c_str());
		assert(m_graphHandles[i] != -1 && "スカイボックスの画像が正しく読み込まれませんでした");
	}
}

void SkyBox::End()
{
	for (auto& handle : m_graphHandles)
	{
		DeleteGraph(handle);
	}
}

void SkyBox::Update()
{
}

void SkyBox::Draw()
{
	constexpr float size = 200.0f;

	SetWriteZBuffer3D(false);
	SetUseLighting(false);

	// front
	DrawSquare(m_pos + Vector3(-size, size, size),	// lt
		m_pos + Vector3(size, size, size),	// rt
		m_pos + Vector3(size, -size, size),	// rb
		m_pos + Vector3(-size, -size, size),	// lb
		m_graphHandles[static_cast<int>(SkyBoxFace::Front)]);
	// back
	DrawSquare(m_pos + Vector3(size, size, -size),	// lt
		m_pos + Vector3(-size, size, -size),	// rt
		m_pos + Vector3(-size, -size, -size),	// rb
		m_pos + Vector3(size, -size, -size),	// lb
		m_graphHandles[static_cast<int>(SkyBoxFace::Back)]);
	// left
	DrawSquare(m_pos + Vector3(-size, size, -size),	// lt
		m_pos + Vector3(-size, size, size),	// rt
		m_pos + Vector3(-size, -size, size),	// rb
		m_pos + Vector3(-size, -size, -size),	// lb
		m_graphHandles[static_cast<int>(SkyBoxFace::Left)]);
	// right
	DrawSquare(m_pos + Vector3(size, size, size),	// lt
		m_pos + Vector3(size, size, -size),	// rt
		m_pos + Vector3(size, -size, -size),	// rb
		m_pos + Vector3(size, -size, size),	// lb
		m_graphHandles[static_cast<int>(SkyBoxFace::Right)]);
	// up
	DrawSquare(m_pos + Vector3(-size, size, -size),	// lt
		m_pos + Vector3(size, size, -size),	// rt
		m_pos + Vector3(size, size, size),	// rb
		m_pos + Vector3(-size, size, size),	// lb
		m_graphHandles[static_cast<int>(SkyBoxFace::Up)]);
	// down
	DrawSquare(m_pos + Vector3(-size, -size, size),	// lt
		m_pos + Vector3(size, -size, size),	// rt
		m_pos + Vector3(size, -size, -size),	// rb
		m_pos + Vector3(-size, -size, -size),	// lb
		m_graphHandles[static_cast<int>(SkyBoxFace::Down)]);


	SetWriteZBuffer3D(true);
	SetUseLighting(true);
}

void SkyBox::DrawSquare(const Vector3& lt, const Vector3& rt, const Vector3& rb, const Vector3& lb, int graphHandle)
{
	VERTEX3D v[4] = {};
	v[0].pos = lt.ToDxLib(); v[0].u = 0.0f; v[0].v = 0.0f;
	v[1].pos = rt.ToDxLib(); v[1].u = 1.0f; v[1].v = 0.0f;
	v[2].pos = rb.ToDxLib(); v[2].u = 1.0f; v[2].v = 1.0f;
	v[3].pos = lb.ToDxLib(); v[3].u = 0.0f; v[3].v = 1.0f;

	int size = sizeof(v) / sizeof(VERTEX3D);
	for (int i = 0; i < size; i++)
	{
		v[i].dif = GetColorU8(255, 255, 255, 255);
	}

	unsigned short index[] = { 0,2,3, 0,1,2 };
	DrawPolygonIndexed3D(v, size, index, 2, graphHandle, true);
}
