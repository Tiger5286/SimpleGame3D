#pragma once
#include "../Utility/Vector3.h"

class Camera;

class SkyBox
{
public:
	SkyBox();
	virtual ~SkyBox();

	void Init();
	void End();
	void Update();
	void Draw();

	void SetCameraPos(const Vector3& pos) { m_pos = pos; }

private:
	void DrawSquare(const Vector3& lt, const Vector3& rt, const Vector3& rb, const Vector3& lb, int graphHandle);

private:
	enum class SkyBoxFace
	{
		Front,
		Back,
		Left,
		Right,
		Up,
		Down,

		Num
	};

private:
	int m_graphHandles[static_cast<int>(SkyBoxFace::Num)] = { -1 };

	Vector3 m_pos;
};

