#pragma once
#include "../Utility/Vector3.h"

class Input;
class Player;

class Camera
{
public:
	Camera(Input& input);
	virtual ~Camera();

	void Init();
	void Update();

	float GetAngleY() const { return m_angleY; }
	Vector3 GetPos() const { return m_pos; }
	void SetPos(const Vector3& pos) { m_pos = pos; }

	void SetPlayerPos(const Vector3& playerPos) { m_playerPos = playerPos; }

private:
	Input& m_input;
	Vector3 m_playerPos;

	Vector3 m_pos;
	Vector3 m_target;
	float m_angleY = 0.0f;
	float m_angleX = 0.0f;
};

